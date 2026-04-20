#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUL		'\000'
#define BELL		'\007'
#define BS		'\010'
#define TAB		'\011'
#define NL		'\012'
#define FF		'\014'
#define CAR		'\015'
#define ESC		'\033'
#define Ctrl_H		8

#define K_SPECIAL		(0x80)

#ifndef TRUE
# define FALSE	0
# define TRUE	1
#endif

#define FAIL			0

#define REGSUB_COPY	    1
#define REGSUB_MAGIC	    2
#define REGSUB_BACKSLASH    4

#define NUMBUFLEN 65

#define RE_MAGIC	1
#define RE_STRING	2

#define STRLEN(s)	    strlen((char *)(s))
#define STRCPY(d, s)	    strcpy((char *)(d), (char *)(s))

#define VIM_CLEAR(p) \
    do { \
	if ((p) != NULL) { \
	    vim_free(p); \
	    (p) = NULL; \
	} \
    } while (0)

#define CLEAR_FIELD(field)  memset(&(field), 0, sizeof(field))

#define MB_PTR_ADV(p)	    p += mb_ptr2len(p)

typedef unsigned char	char_u;
typedef long		linenr_T;
typedef int		colnr_T;
typedef double	float_T;

typedef struct window_S		win_T;
typedef struct file_buffer	buf_T;
typedef struct listvar_S list_T;
typedef struct dictvar_S dict_T;
typedef struct partial_S partial_T;
typedef struct blobvar_S blob_T;
typedef struct ufunc_S ufunc_T;
typedef struct type_S type_T;
typedef struct object_S object_T;

typedef union
{
    long	    v_number;
    float_T	    v_float;
    char_u	   *v_string;
    partial_T	   *v_partial;
    list_T	   *v_list;
    dict_T	   *v_dict;
    blob_T	   *v_blob;
} typval_T_vval;

typedef enum
{
    VAR_UNKNOWN = 0,
    VAR_ANY,
    VAR_VOID,
    VAR_BOOL,
    VAR_SPECIAL,
    VAR_NUMBER,
    VAR_FLOAT,
    VAR_STRING,
    VAR_BLOB,
    VAR_FUNC,
    VAR_PARTIAL,
    VAR_LIST,
    VAR_DICT,
    VAR_JOB,
    VAR_CHANNEL,
    VAR_INSTR,
    VAR_CLASS,
    VAR_OBJECT,
} vartype_T;

typedef struct typval_S typval_T;

struct typval_S
{
    vartype_T	    v_type;
    typval_T_vval   vval;
};

typedef struct listitem_S listitem_T;
struct listitem_S
{
    listitem_T	*li_next;
    listitem_T	*li_prev;
    typval_T	li_tv;
};

typedef struct
{
    linenr_T	lnum;
    colnr_T	col;
} lpos_T;

typedef struct growarray
{
    int	    ga_len;
    int	    ga_maxlen;
    int	    ga_itemsize;
    int	    ga_growsize;
    void    *ga_data;
} garray_T;

struct listvar_S
{
    list_T	*lv_used_next;
    list_T	*lv_used_prev;
    int		lv_refcount;
    int		lv_len;
    int		lv_with_items;
    int		lv_copyID;
    char	lv_lock;
};

typedef struct {
    list_T	sl_list;
    listitem_T	sl_items[10];
} staticList10_T;

typedef struct hashtab_S hashtab_T;
struct hashtab_S { int dummy; };

struct dictvar_S
{
    char	dv_lock;
    char	dv_scope;
    int		dv_refcount;
    int		dv_copyID;
    hashtab_T	dv_hashtab;
    type_T	*dv_type;
    dict_T	*dv_copydict;
    dict_T	*dv_used_next;
    dict_T	*dv_used_prev;
};

struct partial_S
{
    char_u	*pt_name;
    int		pt_refcount;
    int		pt_argc;
    typval_T	*pt_argv;
    dict_T	*pt_dict;
    int		pt_computed;
};

struct blobvar_S
{
    garray_T	bv_ga;
    int		bv_refcount;
    char	bv_lock;
};

typedef struct {
    int		(* fe_argv_func)(int, typval_T *, int, ufunc_T *);
    linenr_T	fe_firstline;
    linenr_T	fe_lastline;
    int		*fe_doesrange;
    int		fe_evaluate;
    partial_T	*fe_partial;
    dict_T	*fe_selfdict;
    object_T	*fe_object;
    typval_T	*fe_basetv;
    type_T	*fe_check_type;
    int		fe_found_var;
} funcexe_T;

struct type_S { vartype_T tt_type; };
struct ufunc_S { int dummy; };
struct object_S { int dummy; };
struct window_S { int dummy; };
struct file_buffer { int dummy; };
struct ectx_S { int dummy; };
struct isn_S { int dummy; };

#define NSUBEXP  10

typedef struct regengine regengine_T;
struct regengine { int dummy; };

typedef struct regprog
{
    regengine_T		*engine;
    unsigned		regflags;
    unsigned		re_engine;
    unsigned		re_flags;
    int			re_in_use;
} regprog_T;

typedef struct
{
    regprog_T		*regprog;
    char_u		*startp[NSUBEXP];
    char_u		*endp[NSUBEXP];
    colnr_T		rm_matchcol;
    int			rm_ic;
} regmatch_T;

typedef struct
{
    regprog_T		*regprog;
    lpos_T		startpos[NSUBEXP];
    lpos_T		endpos[NSUBEXP];
    colnr_T		rmm_matchcol;
    int			rmm_ic;
    colnr_T		rmm_maxcol;
} regmmatch_T;

typedef struct
{
    regmatch_T		*reg_match;
    regmmatch_T		*reg_mmatch;
    linenr_T		reg_firstlnum;
    linenr_T		reg_maxline;
    int			reg_line_lbr;
    buf_T		*reg_buf;
} regexec_T;

typedef void (*(*fptr_T)(int *, int));

typedef struct {
    regmatch_T	*sm_match;
    regmmatch_T	*sm_mmatch;
    linenr_T	sm_firstlnum;
    linenr_T	sm_maxline;
    int		sm_line_lbr;
} regsubmatch_T;

static regexec_T	rex;
static int		rex_in_use = FALSE;
#define REG_MULTI	(rex.reg_match == NULL)

static int can_f_submatch = FALSE;
static regsubmatch_T rsm;

#define MAX_REGSUB_NESTING 4
static char_u   *eval_result[MAX_REGSUB_NESTING] = {NULL, NULL, NULL, NULL};

struct subs_expr_S {
    struct ectx_S	*subs_ectx;
    struct isn_S	*subs_instr;
    int			subs_status;
};
static struct subs_expr_S	*substitute_instr = NULL;

static buf_T	curbuf_storage;
buf_T		*curbuf = &curbuf_storage;
int		enc_utf8 = FALSE;
int		has_mbyte = 0;
int		p_ic = FALSE;
char_u		empty_option_storage[1] = {NUL};
char_u		*empty_option = empty_option_storage;
char_u		p_cpo_storage[1] = {NUL};
char_u		*p_cpo = p_cpo_storage;

char e_null_argument[] = "E38: Null argument";
char e_substitute_nesting_too_deep[] = "E1290: substitute nesting too deep";
char e_damaged_match_string[] = "E43: Damaged match string";

static int prog_magic_wrong(void);
static char_u *reg_getline(linenr_T lnum);
static fptr_T do_upper(int *d, int c);
static fptr_T do_Upper(int *d, int c);
static fptr_T do_lower(int *d, int c);
static fptr_T do_Lower(int *d, int c);
static int fill_submatch_list(int argc, typval_T *argv, int argskip, ufunc_T *fp);

extern void emsg(char *s);
extern void iemsg(char *s);
extern char *_(char *str);
extern char_u *vim_strsave(char_u *s);
extern char_u *vim_strsave_escaped(char_u *s, char_u *esc_chars);
extern void vim_free(void *x);
extern char_u *vim_strchr(char_u *string, int c);
extern void ga_init2(garray_T *gap, int itemsize, int growsize);
extern int ga_grow(garray_T *gap, int n);
extern void ga_clear(garray_T *gap);
extern void set_option_value_give_err(char_u *name, long val, char_u *valstr, int opt_flags);
extern void free_string_option(char_u *s);
extern regprog_T *vim_regcomp(char_u *expr, int flags);
extern void vim_regfree(regprog_T *prog);
extern int vim_regexec_nl(regmatch_T *rmp, char_u *line, colnr_T col);
extern void init_static_list(staticList10_T *list);
extern void clear_submatch_list(staticList10_T *list);
extern char_u *partial_name(partial_T *pt);
extern char_u *eval_to_string(char_u *arg, int use_trunc, int silent);
extern int call_func(char_u *func, int len, typval_T *rettv, int argcount, typval_T *argv, funcexe_T *funcexe);
extern void clear_tv(typval_T *tv);
extern char_u *tv_get_string_buf_chk(typval_T *tv, char_u *buf);
extern void exe_typval_instr(typval_T *tv, typval_T *rettv);
extern char_u *exe_substitute_instr(void);
extern int mb_ptr2len(const char_u *p);
extern int mb_ptr2char(const char_u *p);
extern int mb_char2len(int c);
extern void mb_char2bytes(int c, char_u *buf);
extern int utf_ptr2len(const char_u *p);
extern void mch_memmove(char_u *dst, const char_u *src, size_t n);

void emsg(char *s);
void iemsg(char *s);
char *_(char *str);
char_u *vim_strsave(char_u *s);
char_u *vim_strsave_escaped(char_u *s, char_u *esc_chars);
void vim_free(void *x);
char_u *vim_strchr(char_u *string, int c);
void ga_init2(garray_T *gap, int itemsize, int growsize);
int ga_grow(garray_T *gap, int n);
void ga_clear(garray_T *gap);
void set_option_value_give_err(char_u *name, long val, char_u *valstr, int opt_flags);
void free_string_option(char_u *s);
regprog_T *vim_regcomp(char_u *expr, int flags);
void vim_regfree(regprog_T *prog);
int vim_regexec_nl(regmatch_T *rmp, char_u *line, colnr_T col);
void init_static_list(staticList10_T *list);
void clear_submatch_list(staticList10_T *list);
char_u *partial_name(partial_T *pt);
char_u *eval_to_string(char_u *arg, int use_trunc, int silent);
int call_func(char_u *func, int len, typval_T *rettv, int argcount, typval_T *argv, funcexe_T *funcexe);
void clear_tv(typval_T *tv);
char_u *tv_get_string_buf_chk(typval_T *tv, char_u *buf);
void exe_typval_instr(typval_T *tv, typval_T *rettv);
char_u *exe_substitute_instr(void);
int mb_ptr2len(const char_u *p);
int mb_ptr2char(const char_u *p);
int mb_char2len(int c);
void mb_char2bytes(int c, char_u *buf);
int utf_ptr2len(const char_u *p);
void mch_memmove(char_u *dst, const char_u *src, size_t n);

static int prog_magic_wrong(void);
static char_u *reg_getline(linenr_T lnum);
static fptr_T do_upper(int *d, int c);
static fptr_T do_Upper(int *d, int c);
static fptr_T do_lower(int *d, int c);
static fptr_T do_Lower(int *d, int c);
static int fill_submatch_list(int argc, typval_T *argv, int argskip, ufunc_T *fp);

    static int
vim_regsub_both(
    char_u	*source,
    typval_T	*expr,
    char_u	*dest,
    int		destlen,
    int		flags)
{
    char_u	*src;
    char_u	*dst;
    char_u	*s;
    int		c;
    int		cc;
    int		no = -1;
    fptr_T	func_all = (fptr_T)NULL;
    fptr_T	func_one = (fptr_T)NULL;
    linenr_T	clnum = 0;	// init for GCC
    int		len = 0;	// init for GCC
#ifdef FEAT_EVAL
    static int  nesting = 0;
    int		nested;
#endif
    int		copy = flags & REGSUB_COPY;

    // Be paranoid...
    if ((source == NULL && expr == NULL) || dest == NULL)
    {
	emsg(_(e_null_argument));
	return 0;
    }
    if (prog_magic_wrong())
	return 0;
#ifdef FEAT_EVAL
    if (nesting == MAX_REGSUB_NESTING)
    {
	emsg(_(e_substitute_nesting_too_deep));
	return 0;
    }
    nested = nesting;
#endif
    src = source;
    dst = dest;

    /*
     * When the substitute part starts with "\=" evaluate it as an expression.
     */
    if (expr != NULL || (source[0] == '\\' && source[1] == '='))
    {
#ifdef FEAT_EVAL
	// To make sure that the length doesn't change between checking the
	// length and copying the string, and to speed up things, the
	// resulting string is saved from the call with
	// "flags & REGSUB_COPY" == 0 to the call with
	// "flags & REGSUB_COPY" != 0.
	if (copy)
	{
	    if (eval_result[nested] != NULL)
	    {
		STRCPY(dest, eval_result[nested]);
		dst += STRLEN(eval_result[nested]);
		VIM_CLEAR(eval_result[nested]);
	    }
	}
	else
	{
	    int		    prev_can_f_submatch = can_f_submatch;
	    regsubmatch_T   rsm_save;

	    VIM_CLEAR(eval_result[nested]);

	    // The expression may contain substitute(), which calls us
	    // recursively.  Make sure submatch() gets the text from the first
	    // level.
	    if (can_f_submatch)
		rsm_save = rsm;
	    can_f_submatch = TRUE;
	    rsm.sm_match = rex.reg_match;
	    rsm.sm_mmatch = rex.reg_mmatch;
	    rsm.sm_firstlnum = rex.reg_firstlnum;
	    rsm.sm_maxline = rex.reg_maxline;
	    rsm.sm_line_lbr = rex.reg_line_lbr;

	    // Although unlikely, it is possible that the expression invokes a
	    // substitute command (it might fail, but still).  Therefore keep
	    // an array of eval results.
	    ++nesting;

	    if (expr != NULL)
	    {
		typval_T	argv[2];
		char_u		buf[NUMBUFLEN];
		typval_T	rettv;
		staticList10_T	matchList;
		funcexe_T	funcexe;

		rettv.v_type = VAR_STRING;
		rettv.vval.v_string = NULL;
		argv[0].v_type = VAR_LIST;
		argv[0].vval.v_list = &matchList.sl_list;
		matchList.sl_list.lv_len = 0;
		CLEAR_FIELD(funcexe);
		funcexe.fe_argv_func = fill_submatch_list;
		funcexe.fe_evaluate = TRUE;
		if (expr->v_type == VAR_FUNC)
		{
		    s = expr->vval.v_string;
		    call_func(s, -1, &rettv, 1, argv, &funcexe);
		}
		else if (expr->v_type == VAR_PARTIAL)
		{
		    partial_T   *partial = expr->vval.v_partial;

		    s = partial_name(partial);
		    funcexe.fe_partial = partial;
		    call_func(s, -1, &rettv, 1, argv, &funcexe);
		}
		else if (expr->v_type == VAR_INSTR)
		{
		    exe_typval_instr(expr, &rettv);
		}
		if (matchList.sl_list.lv_len > 0)
		    // fill_submatch_list() was called
		    clear_submatch_list(&matchList);

		if (rettv.v_type == VAR_UNKNOWN)
		    // something failed, no need to report another error
		    eval_result[nested] = NULL;
		else
		{
		    eval_result[nested] = tv_get_string_buf_chk(&rettv, buf);
		    if (eval_result[nested] != NULL)
			eval_result[nested] = vim_strsave(eval_result[nested]);
		}
		clear_tv(&rettv);
	    }
	    else if (substitute_instr != NULL)
		// Execute instructions from ISN_SUBSTITUTE.
		eval_result[nested] = exe_substitute_instr();
	    else
		eval_result[nested] = eval_to_string(source + 2, TRUE, FALSE);
	    --nesting;

	    if (eval_result[nested] != NULL)
	    {
		int had_backslash = FALSE;

		for (s = eval_result[nested]; *s != NUL; MB_PTR_ADV(s))
		{
		    // Change NL to CR, so that it becomes a line break,
		    // unless called from vim_regexec_nl().
		    // Skip over a backslashed character.
		    if (*s == NL && !rsm.sm_line_lbr)
			*s = CAR;
		    else if (*s == '\\' && s[1] != NUL)
		    {
			++s;
			/* Change NL to CR here too, so that this works:
			 * :s/abc\\\ndef/\="aaa\\\nbbb"/  on text:
			 *   abc\
			 *   def
			 * Not when called from vim_regexec_nl().
			 */
			if (*s == NL && !rsm.sm_line_lbr)
			    *s = CAR;
			had_backslash = TRUE;
		    }
		}
		if (had_backslash && (flags & REGSUB_BACKSLASH))
		{
		    // Backslashes will be consumed, need to double them.
		    s = vim_strsave_escaped(eval_result[nested], (char_u *)"\\");
		    if (s != NULL)
		    {
			vim_free(eval_result[nested]);
			eval_result[nested] = s;
		    }
		}

		dst += STRLEN(eval_result[nested]);
	    }

	    can_f_submatch = prev_can_f_submatch;
	    if (can_f_submatch)
		rsm = rsm_save;
	}
#endif
    }
    else
      while ((c = *src++) != NUL)
      {
	if (c == '&' && (flags & REGSUB_MAGIC))
	    no = 0;
	else if (c == '\\' && *src != NUL)
	{
	    if (*src == '&' && !(flags & REGSUB_MAGIC))
	    {
		++src;
		no = 0;
	    }
	    else if ('0' <= *src && *src <= '9')
	    {
		no = *src++ - '0';
	    }
	    else if (vim_strchr((char_u *)"uUlLeE", *src))
	    {
		switch (*src++)
		{
		case 'u':   func_one = (fptr_T)do_upper;
			    continue;
		case 'U':   func_all = (fptr_T)do_Upper;
			    continue;
		case 'l':   func_one = (fptr_T)do_lower;
			    continue;
		case 'L':   func_all = (fptr_T)do_Lower;
			    continue;
		case 'e':
		case 'E':   func_one = func_all = (fptr_T)NULL;
			    continue;
		}
	    }
	}
	if (no < 0)	      // Ordinary character.
	{
	    if (c == K_SPECIAL && src[0] != NUL && src[1] != NUL)
	    {
		// Copy a special key as-is.
		if (copy)
		{
		    if (dst + 3 > dest + destlen)
		    {
			iemsg("vim_regsub_both(): not enough space");
			return 0;
		    }
		    *dst++ = c;
		    *dst++ = *src++;
		    *dst++ = *src++;
		}
		else
		{
		    dst += 3;
		    src += 2;
		}
		continue;
	    }

	    if (c == '\\' && *src != NUL)
	    {
		// Check for abbreviations -- webb
		switch (*src)
		{
		    case 'r':	c = CAR;	++src;	break;
		    case 'n':	c = NL;		++src;	break;
		    case 't':	c = TAB;	++src;	break;
		 // Oh no!  \e already has meaning in subst pat :-(
		 // case 'e':   c = ESC;	++src;	break;
		    case 'b':	c = Ctrl_H;	++src;	break;

		    // If "backslash" is TRUE the backslash will be removed
		    // later.  Used to insert a literal CR.
		    default:	if (flags & REGSUB_BACKSLASH)
				{
				    if (copy)
				    {
					if (dst + 1 > dest + destlen)
					{
					    iemsg("vim_regsub_both(): not enough space");
					    return 0;
					}
					*dst = '\\';
				    }
				    ++dst;
				}
				c = *src++;
		}
	    }
	    else if (has_mbyte)
		c = mb_ptr2char(src - 1);

	    // Write to buffer, if copy is set.
	    if (func_one != (fptr_T)NULL)
		// Turbo C complains without the typecast
		func_one = (fptr_T)(func_one(&cc, c));
	    else if (func_all != (fptr_T)NULL)
		// Turbo C complains without the typecast
		func_all = (fptr_T)(func_all(&cc, c));
	    else // just copy
		cc = c;

	    if (has_mbyte)
	    {
		int totlen = mb_ptr2len(src - 1);
		int charlen = mb_char2len(cc);

		if (copy)
		{
		    if (dst + charlen > dest + destlen)
		    {
			iemsg("vim_regsub_both(): not enough space");
			return 0;
		    }
		    mb_char2bytes(cc, dst);
		}
		dst += charlen - 1;
		if (enc_utf8)
		{
		    int clen = utf_ptr2len(src - 1);

		    // If the character length is shorter than "totlen", there
		    // are composing characters; copy them as-is.
		    if (clen < totlen)
		    {
			if (copy)
			{
			    if (dst + totlen - clen > dest + destlen)
			    {
				iemsg("vim_regsub_both(): not enough space");
				return 0;
			    }
			    mch_memmove(dst + 1, src - 1 + clen,
							     (size_t)(totlen - clen));
			}
			dst += totlen - clen;
		    }
		}
		src += totlen - 1;
	    }
	    else if (copy)
	    {
		if (dst + 1 > dest + destlen)
		{
		    iemsg("vim_regsub_both(): not enough space");
		    return 0;
		}
		*dst = cc;
	    }
	    dst++;
	}
	else
	{
	    if (REG_MULTI)
	    {
		clnum = rex.reg_mmatch->startpos[no].lnum;
		if (clnum < 0 || rex.reg_mmatch->endpos[no].lnum < 0)
		    s = NULL;
		else
		{
		    s = reg_getline(clnum) + rex.reg_mmatch->startpos[no].col;
		    if (rex.reg_mmatch->endpos[no].lnum == clnum)
			len = rex.reg_mmatch->endpos[no].col
						    - rex.reg_mmatch->startpos[no].col;
		    else
			len = (int)STRLEN(s);
		}
	    }
	    else
	    {
		s = rex.reg_match->startp[no];
		if (rex.reg_match->endp[no] == NULL)
		    s = NULL;
		else
		    len = (int)(rex.reg_match->endp[no] - s);
	    }
	    if (s != NULL)
	    {
		for (;;)
		{
		    if (len == 0)
		    {
			if (REG_MULTI)
			{
			    if (rex.reg_mmatch->endpos[no].lnum == clnum)
				break;
			    if (copy)
			    {
				if (dst + 1 > dest + destlen)
				{
				    iemsg("vim_regsub_both(): not enough space");
				    return 0;
				}
				*dst = CAR;
			    }
			    ++dst;
			    s = reg_getline(++clnum);
			    if (rex.reg_mmatch->endpos[no].lnum == clnum)
				len = rex.reg_mmatch->endpos[no].col;
			    else
				len = (int)STRLEN(s);
			}
			else
			    break;
		    }
		    else if (*s == NUL) // we hit NUL.
		    {
			if (copy)
			    iemsg(_(e_damaged_match_string));
			goto exit;
		    }
		    else
		    {
			if ((flags & REGSUB_BACKSLASH)
							  && (*s == CAR || *s == '\\'))
			{
			    /*
			     * Insert a backslash in front of a CR, otherwise
			     * it will be replaced by a line break.
			     * Number of backslashes will be halved later,
			     * double them here.
			     */
			    if (copy)
			    {
				if (dst + 2 > dest + destlen)
				{
				    iemsg("vim_regsub_both(): not enough space");
				    return 0;
				}
				dst[0] = '\\';
				dst[1] = *s;
			    }
			    dst += 2;
			}
			else
			{
			    if (has_mbyte)
				c = mb_ptr2char(s);
			    else
				c = *s;

			    if (func_one != (fptr_T)NULL)
				// Turbo C complains without the typecast
				func_one = (fptr_T)(func_one(&cc, c));
			    else if (func_all != (fptr_T)NULL)
				// Turbo C complains without the typecast
				func_all = (fptr_T)(func_all(&cc, c));
			    else // just copy
				cc = c;

			    if (has_mbyte)
			    {
				int l;
				int charlen;

				// Copy composing characters separately, one
				// at a time.
				if (enc_utf8)
				    l = utf_ptr2len(s) - 1;
				else
				    l = mb_ptr2len(s) - 1;

				s += l;
				len -= l;
				charlen = mb_char2len(cc);
				if (copy)
				{
				    if (dst + charlen > dest + destlen)
				    {
					iemsg("vim_regsub_both(): not enough space");
					return 0;
				    }
				    mb_char2bytes(cc, dst);
				}
				dst += charlen - 1;
			    }
			    else if (copy)
			    {
				if (dst + 1 > dest + destlen)
				{
				    iemsg("vim_regsub_both(): not enough space");
				    return 0;
				}
				*dst = cc;
			    }
			    dst++;
			}

			++s;
			--len;
		    }
		}
	    }
	    no = -1;
	}
      }
    if (copy)
	*dst = NUL;

exit:
    return (int)((dst - dest) + 1);
}

    int
vim_regsub(
    regmatch_T	*rmp,
    char_u	*source,
    typval_T	*expr,
    char_u	*dest,
    int		destlen,
    int		flags)
{
    int		result;
    regexec_T	rex_save;
    int		rex_in_use_save = rex_in_use;

    if (rex_in_use)
	// Being called recursively, save the state.
	rex_save = rex;
    rex_in_use = TRUE;

    rex.reg_match = rmp;
    rex.reg_mmatch = NULL;
    rex.reg_maxline = 0;
    rex.reg_buf = curbuf;
    rex.reg_line_lbr = TRUE;
    result = vim_regsub_both(source, expr, dest, destlen, flags);

    rex_in_use = rex_in_use_save;
    if (rex_in_use)
	rex = rex_save;

    return result;
}

    char_u *
do_string_sub(
    char_u	*str,
    char_u	*pat,
    char_u	*sub,
    typval_T	*expr,
    char_u	*flags)
{
    int		sublen;
    regmatch_T	regmatch;
    int		i;
    int		do_all;
    char_u	*tail;
    char_u	*end;
    garray_T	ga;
    char_u	*ret;
    char_u	*save_cpo;
    char_u	*zero_width = NULL;

    // Make 'cpoptions' empty, so that the 'l' flag doesn't work here
    save_cpo = p_cpo;
    p_cpo = empty_option;

    ga_init2(&ga, 1, 200);

    do_all = (flags[0] == 'g');

    regmatch.rm_ic = p_ic;
    regmatch.regprog = vim_regcomp(pat, RE_MAGIC + RE_STRING);
    if (regmatch.regprog != NULL)
    {
	tail = str;
	end = str + STRLEN(str);
	while (vim_regexec_nl(&regmatch, str, (colnr_T)(tail - str)))
	{
	    // Skip empty match except for first match.
	    if (regmatch.startp[0] == regmatch.endp[0])
	    {
		if (zero_width == regmatch.startp[0])
		{
		    // avoid getting stuck on a match with an empty string
		    i = mb_ptr2len(tail);
		    mch_memmove((char_u *)ga.ga_data + ga.ga_len, tail,
									   (size_t)i);
		    ga.ga_len += i;
		    tail += i;
		    continue;
		}
		zero_width = regmatch.startp[0];
	    }

	    /*
	     * Get some space for a temporary buffer to do the substitution
	     * into.  It will contain:
	     * - The text up to where the match is.
	     * - The substituted text.
	     * - The text after the match.
	     */
	    sublen = vim_regsub(&regmatch, sub, expr, tail, 0, REGSUB_MAGIC);
	    if (ga_grow(&ga, (int)((end - tail) + sublen -
			    (regmatch.endp[0] - regmatch.startp[0]))) == FAIL)
	    {
		ga_clear(&ga);
		break;
	    }

	    // copy the text up to where the match is
	    i = (int)(regmatch.startp[0] - tail);
	    mch_memmove((char_u *)ga.ga_data + ga.ga_len, tail, (size_t)i);
	    // add the substituted text
	    (void)vim_regsub(&regmatch, sub, expr,
				  (char_u *)ga.ga_data + ga.ga_len + i, sublen,
				  REGSUB_COPY | REGSUB_MAGIC);
	    ga.ga_len += i + sublen - 1;
	    tail = regmatch.endp[0];
	    if (*tail == NUL)
		break;
	    if (!do_all)
		break;
	}

	if (ga.ga_data != NULL)
	    STRCPY((char *)ga.ga_data + ga.ga_len, tail);

	vim_regfree(regmatch.regprog);
    }

    ret = vim_strsave(ga.ga_data == NULL ? str : (char_u *)ga.ga_data);
    ga_clear(&ga);
    if (p_cpo == empty_option)
	p_cpo = save_cpo;
    else
    {
	// Darn, evaluating {sub} expression or {expr} changed the value.
	// If it's still empty it was changed and restored, need to restore in
	// the complicated way.
	if (*p_cpo == NUL)
	    set_option_value_give_err((char_u *)"cpo", 0L, save_cpo, 0);
	free_string_option(save_cpo);
    }

    return ret;
}
