#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// FROM: vim.h
typedef unsigned char	char_u;
typedef int	colnr_T;
typedef long	linenr_T;
typedef unsigned int	int_u;

// FROM: vim.h
#define TRUE		1
#define FALSE		0
#define OK			1
#define FAIL			0

// FROM: ascii.h
#define NUL		'\000'

// FROM: vim.h
#define STRLEN(s)	    strlen((char *)(s))
#define STRCPY(d, s)	    strcpy((char *)(d), (char *)(s))
#define STRNCMP(d, s, n)    strncmp((char *)(d), (char *)(s), (size_t)(n))

#define ALLOC_MULT(type, count)  (type *)alloc(sizeof(type) * (count))

// FROM: vim.h
#define _(x) ((char *)(x))

// FROM: globals.h
#define EXTERN

// FROM: vim.h - macros for buffer/window iteration
#define FOR_ALL_BUFS_FROM_LAST(buf) \
    for ((buf) = lastbuf; (buf) != NULL; (buf) = (buf)->b_prev)

#define FOR_ALL_BUFFERS(buf) \
    for ((buf) = firstbuf; (buf) != NULL; (buf) = (buf)->b_next)

#define FOR_ALL_WINDOWS(wp) for ((wp) = firstwin; (wp) != NULL; (wp) = (wp)->w_next)

// FROM: macros.h
#define WILD_HOME_REPLACE	0x02

// FROM: structs.h
typedef struct
{
    linenr_T	lnum;	// line number
    colnr_T	col;	// column number
} lpos_T;

typedef struct window_S		win_T;
typedef struct file_buffer	buf_T;

// FROM: regexp.h
#define NSUBEXP  10

#define	    AUTOMATIC_ENGINE	0
#define	    BACKTRACKING_ENGINE	1
#define	    NFA_ENGINE		2

#define NFA_TOO_EXPENSIVE (-1)

typedef struct regengine regengine_T;

typedef struct regprog
{
    regengine_T		*engine;
    unsigned		regflags;
    unsigned		re_engine;   // automatic, backtracking or nfa engine
    unsigned		re_flags;    // second argument for vim_regcomp()
    int			re_in_use;   // prog is being executed
} regprog_T;

typedef struct
{
    regprog_T		*regprog;
    char_u		*startp[NSUBEXP];
    char_u		*endp[NSUBEXP];
    int			rm_ic;
} regmatch_T;

// FROM: structs.h
typedef struct {
    int		idx;
    char_u	*str;
    int		score;
} fuzmatch_str_T;

#ifdef FEAT_VIMINFO
typedef struct {
    buf_T   *buf;
    char_u  *match;
} bufmatch_T;
#endif

// FROM: regexp.h
typedef struct
{
    regprog_T		*regprog;
    lpos_T		startpos[NSUBEXP];
    lpos_T		endpos[NSUBEXP];
    int			rmm_ic;
    colnr_T		rmm_maxcol;	// when not zero: maximum column
} regmmatch_T;

// FROM: vim.h
typedef int proftime_T;

// FROM: regexp.h - nfa_state_T forward declaration
typedef struct nfa_state nfa_state_T;

// FROM: regexp.h - nfa_regprog_T structure
typedef struct nfa_regprog
{
    regengine_T		*engine;
    unsigned		regflags;
    unsigned		re_engine;
    unsigned		re_flags;
    int			re_in_use;

    nfa_state_T		*start;		// points into state[]

    int			reganch;	// pattern starts with ^
    int			regstart;	// char at start of pattern
    char_u		*match_text;	// plain text to match with

    int			has_zend;	// pattern contains \ze
    int			has_backref;	// pattern contains \1 .. \9
#ifdef FEAT_SYN_HL
    int			reghasz;
#endif
    char_u		*pattern;
    int			nsubexp;	// number of ()
    int			nstate;
    nfa_state_T		*state;		// pointer to state array
} nfa_regprog_T;

// FROM: regexp.h - regexec_T structure
typedef struct regexec_T regexec_T;
struct regexec_T
{
    regmatch_T	*reg_match;
    regmmatch_T	*reg_mmatch;
    buf_T	*reg_buf;
    linenr_T	reg_firstlnum;
    linenr_T	reg_maxline;
    char_u	**reg_startp;
    char_u	**reg_endp;
    lpos_T	*reg_startpos;
    lpos_T	*reg_endpos;
    int		reg_maxcol;
    int		reg_line_lbr;
#ifdef FEAT_SYN_HL
    reg_extmatch_T	*reg_extmatch;
    reg_extmatch_T	*zsubexpr;
#endif
    int nfa_has_backref;
    int nfa_nsubexpr;
    int nfa_listid;
    int nfa_alt_listid;
#ifdef FEAT_SYN_HL
    int nfa_has_zsubexpr;
#endif
};

struct regengine
{
    regprog_T	*(*regcomp)(char_u*, int);
    void	(*regfree)(regprog_T *);
    int		(*regexec_nl)(regmatch_T *, char_u *, colnr_T, int);
    long	(*regexec_multi)(regmmatch_T *, win_T *, buf_T *, linenr_T, colnr_T, proftime_T *, int *);
};

// FROM: option.h
EXTERN int	p_fic;		// 'fileignorecase'
EXTERN int	p_wic;		// 'wildignorecase'
EXTERN long	p_re;		// 'regexpengine'

// FROM: globals.h
EXTERN win_T	*curwin;
EXTERN buf_T	*curbuf;
EXTERN buf_T	*firstbuf;
EXTERN buf_T	*lastbuf;
EXTERN win_T	*firstwin;

// FROM: errors.h
EXTERN char e_cannot_use_pattern_recursively[];
EXTERN char e_percent_hash_can_only_be_followed_by_zero_one_two_automatic_engine_will_be_used[];
EXTERN char e_more_than_one_match_for_str[];
EXTERN char e_no_matching_buffer_for_str[];

// FROM: regexp.c
static regexec_T	rex;
static int		rex_in_use = FALSE;

// FROM: regexp.c
static int called_emsg = 0;
static int regexp_engine = 0;

// FROM: regexp.h - RE_MAGIC and RE_AUTO
#define RE_MAGIC 1
#define RE_AUTO 2

// FROM: buffer.c - buf_T structure (partial, only needed fields)
struct file_buffer
{
    char_u	*b_sfname;	// short file name
    char_u	*b_ffname;	// full file name
    int		b_fnum;		// buffer number
    int		b_p_bl;		// 'buflisted'
#ifdef FEAT_DIFF
    int		w_p_diff;
#endif
    buf_T	*b_next;
    buf_T	*b_prev;
};

// FROM: structs.h - win_T structure (partial, only needed fields)
struct window_S
{
    buf_T	*w_buffer;
    int		w_alt_fnum;
#ifdef FEAT_DIFF
    int		w_p_diff;
#endif
    win_T	*w_next;
};

// External function declarations
extern void *alloc(size_t size);
extern void vim_free(void *x);
extern char_u *vim_strsave(char_u *string);
extern char_u *home_replace_save(buf_T *buf, char_u *src);
extern int fuzzy_match_str(char_u *str, char_u *pat);
extern int cmdline_fuzzy_complete(char_u *fuzzystr);
extern int buf_compare(const void *s1, const void *s2);
extern int fuzzymatches_to_strmatches(fuzmatch_str_T *fuzmatch, char_u ***matches, int count, int funcsort);
extern char_u *file_pat_to_reg_pat(char_u *pat, char_u *pat_end, char *allow_dirs, int no_bslash);
extern int in_vim9script(void);
extern buf_T *buflist_findnr(int nr);
extern int diff_mode_buf(buf_T *buf);
extern int magic_isset(void);
extern void emsg(char *s);
extern void semsg(const char *fmt, ...);
extern regprog_T *vim_regcomp(char_u *expr_arg, int re_flags);
extern void vim_regfree(regprog_T *prog);
extern int vim_iswordc_buf(int c, buf_T *buf);
extern char_u *ml_get_buf(buf_T *buf, linenr_T lnum, int x);
extern void report_re_switch(char_u *pat);

// Forward declarations for regex engines
extern regengine_T bt_regengine;
extern regengine_T nfa_regengine;

// FROM: regexp.c
    static int
vim_regexec_string(
    regmatch_T	*rmp,
    char_u	*line,  // string to match against
    colnr_T	col,    // column to start looking for match
    int		nl)
{
    int		result;
    regexec_T	rex_save;
    int		rex_in_use_save = rex_in_use;

    // Cannot use the same prog recursively, it contains state.
    if (rmp->regprog->re_in_use)
    {
	emsg(_(e_cannot_use_pattern_recursively));
	return FALSE;
    }
    rmp->regprog->re_in_use = TRUE;

    if (rex_in_use)
	// Being called recursively, save the state.
	rex_save = rex;
    rex_in_use = TRUE;

    rex.reg_startp = NULL;
    rex.reg_endp = NULL;
    rex.reg_startpos = NULL;
    rex.reg_endpos = NULL;

    result = rmp->regprog->engine->regexec_nl(rmp, line, col, nl);
    rmp->regprog->re_in_use = FALSE;

    // NFA engine aborted because it's very slow.
    if (rmp->regprog->re_engine == AUTOMATIC_ENGINE
					       && result == NFA_TOO_EXPENSIVE)
    {
	int    save_p_re = p_re;
	int    re_flags = rmp->regprog->re_flags;
	char_u *pat = vim_strsave(((nfa_regprog_T *)rmp->regprog)->pattern);

	p_re = BACKTRACKING_ENGINE;
	vim_regfree(rmp->regprog);
	if (pat != NULL)
	{
#ifdef FEAT_EVAL
	    report_re_switch(pat);
#endif
	    rmp->regprog = vim_regcomp(pat, re_flags);
	    if (rmp->regprog != NULL)
	    {
		rmp->regprog->re_in_use = TRUE;
		result = rmp->regprog->engine->regexec_nl(rmp, line, col, nl);
		rmp->regprog->re_in_use = FALSE;
	    }
	    vim_free(pat);
	}

	p_re = save_p_re;
    }

    rex_in_use = rex_in_use_save;
    if (rex_in_use)
	rex = rex_save;

    return result > 0;
}

// FROM: regexp.c
    int
vim_regexec(regmatch_T *rmp, char_u *line, colnr_T col)
{
    return vim_regexec_string(rmp, line, col, FALSE);
}

// FROM: buffer.c
    static char_u *
fname_match(
    regmatch_T	*rmp,
    char_u	*name,
    int		ignore_case)  // when TRUE ignore case, when FALSE use 'fic'
{
    char_u	*match = NULL;
    char_u	*p;

    if (name != NULL && rmp->regprog != NULL)
    {
	// Ignore case when 'fileignorecase' or the argument is set.
	rmp->rm_ic = p_fic || ignore_case;
	if (vim_regexec(rmp, name, (colnr_T)0))
	    match = name;
	else if (rmp->regprog != NULL)
	{
	    // Replace $(HOME) with '~' and try matching again.
	    p = home_replace_save(NULL, name);
	    if (p != NULL && vim_regexec(rmp, p, (colnr_T)0))
		match = name;
	    vim_free(p);
	}
    }

    return match;
}

// FROM: buffer.c
    static char_u *
buflist_match(
    regmatch_T	*rmp,
    buf_T	*buf,
    int		ignore_case)  // when TRUE ignore case, when FALSE use 'fic'
{
    char_u	*match;

    // First try the short file name, then the long file name.
    match = fname_match(rmp, buf->b_sfname, ignore_case);
    if (match == NULL && rmp->regprog != NULL)
	match = fname_match(rmp, buf->b_ffname, ignore_case);

    return match;
}

// FROM: buffer.c
    int
ExpandBufnames(
    char_u	*pat,
    int		*num_file,
    char_u	***file,
    int		options)
{
    int		count = 0;
    buf_T	*buf;
    int		round;
    char_u	*p;
    int		attempt;
    char_u	*patc = NULL;
#ifdef FEAT_VIMINFO
    bufmatch_T	*matches = NULL;
#endif
    int		fuzzy;
    fuzmatch_str_T  *fuzmatch = NULL;

    *num_file = 0;		    // return values in case of FAIL
    *file = NULL;

#ifdef FEAT_DIFF
    if ((options & BUF_DIFF_FILTER) && !curwin->w_p_diff)
	return FAIL;
#endif

    fuzzy = cmdline_fuzzy_complete(pat);

    // Make a copy of "pat" and change "^" to "\(^\|[\/]\)" (if doing regular
    // expression matching)
    if (!fuzzy)
    {
	if (*pat == '^')
	{
	    patc = alloc(STRLEN(pat) + 11);
	    if (patc == NULL)
		return FAIL;
	    STRCPY(patc, "\\(^\\|[\\/]\\)");
	    STRCPY(patc + 11, pat + 1);
	}
	else
	    patc = pat;
    }

    // attempt == 0: try match with    '\<', match at start of word
    // attempt == 1: try match without '\<', match anywhere
    for (attempt = 0; attempt <= (fuzzy ? 0 : 1); ++attempt)
    {
	regmatch_T	regmatch;
	int		score = 0;

	if (!fuzzy)
	{
	    if (attempt > 0 && patc == pat)
		break;	// there was no anchor, no need to try again
	    regmatch.regprog = vim_regcomp(patc + attempt * 11, RE_MAGIC);
	}

	// round == 1: Count the matches.
	// round == 2: Build the array to keep the matches.
	for (round = 1; round <= 2; ++round)
	{
	    count = 0;
	    FOR_ALL_BUFFERS(buf)
	    {
		if (!buf->b_p_bl)	// skip unlisted buffers
		    continue;
#ifdef FEAT_DIFF
		if (options & BUF_DIFF_FILTER)
		    // Skip buffers not suitable for
		    // :diffget or :diffput completion.
		    if (buf == curbuf || !diff_mode_buf(buf))
			continue;
#endif

		if (!fuzzy)
    {
        if (regmatch.regprog == NULL)
		    {
			// invalid pattern, possibly after recompiling
			if (patc != pat)
			    vim_free(patc);
			return FAIL;
		    }
		    p = buflist_match(&regmatch, buf, p_wic);
    }
    else
		{
		    p = NULL;
		    // first try matching with the short file name
		    if ((score = fuzzy_match_str(buf->b_sfname, pat)) != 0)
			p = buf->b_sfname;
		    if (p == NULL)
		    {
			// next try matching with the full path file name
			if ((score = fuzzy_match_str(buf->b_ffname, pat)) != 0)
			    p = buf->b_ffname;
		    }
		}

		if (p == NULL)
		    continue;

		if (round == 1)
		{
		    ++count;
		    continue;
		}

		if (options & WILD_HOME_REPLACE)
		    p = home_replace_save(buf, p);
		else
		    p = vim_strsave(p);

		if (!fuzzy)
		{
#ifdef FEAT_VIMINFO
		    if (matches != NULL)
		    {
			matches[count].buf = buf;
			matches[count].match = p;
			count++;
		    }
		    else
#endif
			(*file)[count++] = p;
		}
		else
		{
		    fuzmatch[count].idx = count;
		    fuzmatch[count].str = p;
		    fuzmatch[count].score = score;
		    count++;
		}
	    }
	    if (count == 0)	// no match found, break here
		break;
	    if (round == 1)
	    {
		if (!fuzzy)
		{
		    *file = ALLOC_MULT(char_u *, count);
		    if (*file == NULL)
		    {
			vim_regfree(regmatch.regprog);
			if (patc != pat)
			    vim_free(patc);
			return FAIL;
		    }
#ifdef FEAT_VIMINFO
		    if (options & WILD_BUFLASTUSED)
			matches = ALLOC_MULT(bufmatch_T, count);
#endif
		}
		else
		{
		    fuzmatch = ALLOC_MULT(fuzmatch_str_T, count);
		    if (fuzmatch == NULL)
		    {
			*num_file = 0;
			*file = NULL;
			return FAIL;
		    }
		}
	    }
	}

	if (!fuzzy)
	{
	    vim_regfree(regmatch.regprog);
	    if (count)		// match(es) found, break here
		break;
	}
    }

    if (!fuzzy && patc != pat)
	vim_free(patc);

#ifdef FEAT_VIMINFO
    if (!fuzzy)
    {
	if (matches != NULL)
	{
	    int i;
	    if (count > 1)
		qsort(matches, count, sizeof(bufmatch_T), buf_compare);
	    // if the current buffer is first in the list, place it at the end
	    if (matches[0].buf == curbuf)
	    {
		for (i = 1; i < count; i++)
		    (*file)[i-1] = matches[i].match;
		(*file)[count-1] = matches[0].match;
	    }
	    else
	    {
		for (i = 0; i < count; i++)
		    (*file)[i] = matches[i].match;
	    }
	    vim_free(matches);
	}
    }
    else
    {
	if (fuzzymatches_to_strmatches(fuzmatch, file, count, FALSE) == FAIL)
	    return FAIL;
    }
#endif

    *num_file = count;
    return (count == 0 ? FAIL : OK);
}

// FROM: regexp.c
    regprog_T *
vim_regcomp(char_u *expr_arg, int re_flags)
{
    regprog_T   *prog = NULL;
    char_u	*expr = expr_arg;
    int		called_emsg_before;

    regexp_engine = p_re;

    // Check for prefix "\%#=", that sets the regexp engine
    if (STRNCMP(expr, "\\%#=", 4) == 0)
    {
	int newengine = expr[4] - '0';

	if (newengine == AUTOMATIC_ENGINE
	    || newengine == BACKTRACKING_ENGINE
	    || newengine == NFA_ENGINE)
	{
	    regexp_engine = expr[4] - '0';
	    expr += 5;
#ifdef DEBUG
	    smsg("New regexp mode selected (%d): %s",
					   regexp_engine, regname[newengine]);
#endif
	}
	else
	{
	    emsg(_(e_percent_hash_can_only_be_followed_by_zero_one_two_automatic_engine_will_be_used));
	    regexp_engine = AUTOMATIC_ENGINE;
	}
    }
#ifdef DEBUG
    bt_regengine.expr = expr;
    nfa_regengine.expr = expr;
#endif
    // reg_iswordc() uses rex.reg_buf
    rex.reg_buf = curbuf;

    /*
     * First try the NFA engine, unless backtracking was requested.
     */
    called_emsg_before = called_emsg;
    if (regexp_engine != BACKTRACKING_ENGINE)
	prog = nfa_regengine.regcomp(expr,
		re_flags + (regexp_engine == AUTOMATIC_ENGINE ? RE_AUTO : 0));
    else
	prog = bt_regengine.regcomp(expr, re_flags);

    // Check for error compiling regexp with initial engine.
    if (prog == NULL)
    {
#ifdef BT_REGEXP_DEBUG_LOG
	if (regexp_engine == BACKTRACKING_ENGINE)   // debugging log for BT engine
	{
	    FILE *f;
	    f = fopen(BT_REGEXP_DEBUG_LOG_NAME, "a");
	    if (f)
	    {
		fprintf(f, "Syntax error in \"%s\"\n", expr);
		fclose(f);
	    }
	    else
		semsg("(NFA) Could not open \"%s\" to write !!!",
			BT_REGEXP_DEBUG_LOG_NAME);
	}
#endif
	/*
	 * If the NFA engine failed, try the backtracking engine.
	 * The NFA engine also fails for patterns that it can't handle well
	 * but are still valid patterns, thus a retry should work.
	 * But don't try if an error message was given.
	 */
	if (regexp_engine == AUTOMATIC_ENGINE
					  && called_emsg == called_emsg_before)
	{
	    regexp_engine = BACKTRACKING_ENGINE;
#ifdef FEAT_EVAL
	    report_re_switch(expr);
#endif
	    prog = bt_regengine.regcomp(expr, re_flags);
	}
    }

    if (prog != NULL)
    {
	// Store the info needed to call regcomp() again when the engine turns
	// out to be very slow when executing it.
	prog->re_engine = regexp_engine;
	prog->re_flags  = re_flags;
    }

    return prog;
}

// FROM: buffer.c
    int
buflist_findpat(
    char_u	*pattern,
    char_u	*pattern_end,	// pointer to first char after pattern
    int		unlisted,	// find unlisted buffers
    int		diffmode, // find diff-mode buffers only
    int		curtab_only)	// find buffers in current tab only
{
    buf_T	*buf;
    int		match = -1;
    int		find_listed;
    char_u	*pat;
    char_u	*patend;
    int		attempt;
    char_u	*p;
    int		toggledollar;

    // "%" is current file, "%%" or "#" is alternate file
    if ((pattern_end == pattern + 1 && (*pattern == '%' || *pattern == '#'))
	    || (in_vim9script() && pattern_end == pattern + 2
				    && pattern[0] == '%' && pattern[1] == '%'))
    {
	if (*pattern == '#' || pattern_end == pattern + 2)
	    match = curwin->w_alt_fnum;
	else
	    match = curbuf->b_fnum;
#ifdef FEAT_DIFF
	if (diffmode && !diff_mode_buf(buflist_findnr(match)))
	    match = -1;
#endif
    }

    /*
     * Try four ways of matching a listed buffer:
     * attempt == 0: without '^' or '$' (at any position)
     * attempt == 1: with '^' at start (only at position 0)
     * attempt == 2: with '$' at end (only match at end)
     * attempt == 3: with '^' at start and '$' at end (only full match)
     * Repeat this for finding an unlisted buffer if there was no matching
     * listed buffer.
     */
    else
    {
	pat = file_pat_to_reg_pat(pattern, pattern_end, NULL, FALSE);
	if (pat == NULL)
	    return -1;
	patend = pat + STRLEN(pat) - 1;
	toggledollar = (patend > pat && *patend == '$');

	// First try finding a listed buffer.  If not found and "unlisted"
	// is TRUE, try finding an unlisted buffer.
	find_listed = TRUE;
	for (;;)
	{
	    for (attempt = 0; attempt <= 3; ++attempt)
	    {
		regmatch_T	regmatch;

		// may add '^' and '$'
		if (toggledollar)
		    *patend = (attempt < 2) ? NUL : '$'; // add/remove '$'
		p = pat;
		if (*p == '^' && !(attempt & 1))	 // add/remove '^'
		    ++p;
		regmatch.regprog = vim_regcomp(p, magic_isset() ? RE_MAGIC : 0);

		FOR_ALL_BUFS_FROM_LAST(buf)
    {
        if (regmatch.regprog == NULL)
		    {
			// invalid pattern, possibly after switching engine
			vim_free(pat);
			return -1;
		    }
		    if (buf->b_p_bl == find_listed
#ifdef FEAT_DIFF
			    && (!diffmode || diff_mode_buf(buf))
#endif
			    && buflist_match(&regmatch, buf, FALSE) != NULL)
		    {
			if (curtab_only)
			{
			    // Ignore the match if the buffer is not open in
			    // the current tab.
			    win_T	*wp;

			    FOR_ALL_WINDOWS(wp)
				if (wp->w_buffer == buf)
				    break;
			    if (wp == NULL)
				continue;
			}
			if (match >= 0)		// already found a match
			{
			    match = -2;
			    break;
			}
			match = buf->b_fnum;	// remember first match
		    }
    }

		vim_regfree(regmatch.regprog);
		if (match >= 0)			// found one match
		    break;
	    }

	    // Only search for unlisted buffers if there was no match with
	    // a listed buffer.
	    if (!unlisted || !find_listed || match != -1)
		break;
	    find_listed = FALSE;
	}

	vim_free(pat);
    }

    if (match == -2)
	semsg(_(e_more_than_one_match_for_str), pattern);
    else if (match < 0)
	semsg(_(e_no_matching_buffer_for_str), pattern);
    return match;
}
