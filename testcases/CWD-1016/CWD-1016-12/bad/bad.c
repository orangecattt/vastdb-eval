#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>

typedef unsigned char char_u;
typedef long linenr_T;
typedef unsigned long long_u;
typedef int getline_opt_T;

#define NUL		'\000'
#define TRUE		1
#define FALSE		0
#define OK		1
#define FAIL		0
#define IOSIZE		(1024 + 1)
#define VIM_ISWHITE(x)	((x) == ' ' || (x) == '\t')
#define VIM_ISDIGIT(c)	((unsigned)(c) - '0' < 10)
#define ASCII_ISUPPER(c) ((unsigned)(c) - 'A' < 26)
#define ASCII_ISALNUM(c) (ASCII_ISUPPER(c) || (((unsigned)(c) - 'a' < 26) || VIM_ISDIGIT(c)))
#define STRMOVE(d, s)	memcpy((d), (s), STRLEN(s) + 1)
#define MB_COPY_CHAR(f, t) do { if (has_mbyte) mb_copy_char(&(f), &(t)); else *(t)++ = *(f)++; } while (0)
#define CLEAR_FIELD(field) memset(&(field), 0, sizeof(field))
#define STRLEN(s)	strlen((char *)(s))
#define STRCPY(d, s)	strcpy((char *)(d), (char *)(s))
#define STRCAT(d, s)	strcat((char *)(d), (char *)(s))
#define _(x)		(x)
#define IS_USER_CMDIDX(idx) ((int)(idx) < 0)
#define vim_free(x)	free(x)

#define EX_RANGE	0x001
#define EX_BANG		0x002
#define EX_EXTRA	0x004
#define EX_XFILE	0x008
#define EX_NOSPC	0x010
#define EX_DFLALL	0x020
#define EX_WHOLEFOLD	0x040
#define EX_NEEDARG	0x080
#define EX_TRLBAR	0x100
#define EX_REGSTR	0x200
#define EX_COUNT	0x400
#define EX_NOTRLCOM	0x800
#define EX_ZEROR	0x1000
#define EX_CTRLV	0x2000
#define EX_CMDARG	0x4000
#define EX_BUFNAME	0x8000
#define EX_BUFUNL	0x10000
#define EX_ARGOPT	0x20000
#define EX_SBOXOK	0x40000
#define EX_CMDWIN	0x80000
#define EX_MODIFY	0x100000
#define EX_FLAGS	0x200000
#define EX_RESTRICT	0x400000
#define EX_EXPAND	0x800000
#define EX_LOCK_OK	0x1000000
#define EX_NONWHITE_OK	0x2000000
#define EX_KEEPSCRIPT	0x4000000
#define EX_EXPR_ARG	0x8000000
#define EX_WHOLE	0x10000000

#define DOCMD_VERBOSE	0x01
#define DOCMD_RANGEOK	0x02
#define EVENT_CMDUNDEFINED 0

#define e_ambiguous_use_of_user_defined_command "ambiguous use of user-defined command"
#define e_argument_required "argument required"
#define e_backwards_range_given "backwards range given"
#define e_cannot_make_changes_modifiable_is_off "modifiable is off"
#define e_colon_required_before_range_str "colon required before range: %s"
#define e_command_not_allowed_in_rvim "command not allowed in rvim"
#define e_invalid_argument "invalid argument"
#define e_invalid_in_cmdline_window "invalid in cmdline window"
#define e_invalid_register_name "invalid register name"
#define e_no_bang_allowed "no ! allowed"
#define e_no_range_allowed "no range allowed"
#define e_not_allowed_in_sandbox "not allowed in sandbox"
#define e_not_an_editor_command "not an editor command"
#define e_positive_count_required "positive count required"
#define e_trailing_characters_str "trailing characters: %s"
#define e_use_w_or_w_gt_gt "use w or w>>"

static int has_mbyte;
static int enc_utf8;
static int reg_executing;
static int pending_end_reg_executing;
static int did_emsg;
static int got_int;
static int did_throw;
static int emsg_silent;
static int if_level;
static int did_emsg_syntax;
static int restricted;
static char_u IObuff[IOSIZE];

typedef enum {
    ADDR_NONE = 0,
    ADDR_LINES,
    ADDR_OTHER
} cmd_addr_T;

typedef enum {
    CMD_SIZE = 0,
    CMD_aboveleft,
    CMD_and,
    CMD_bang,
    CMD_bdelete,
    CMD_belowright,
    CMD_botright,
    CMD_browse,
    CMD_bunload,
    CMD_bwipeout,
    CMD_call,
    CMD_catch,
    CMD_cc,
    CMD_checktime,
    CMD_confirm,
    CMD_const,
    CMD_def,
    CMD_delfunction,
    CMD_djump,
    CMD_dlist,
    CMD_dsearch,
    CMD_dsplit,
    CMD_echo,
    CMD_echoerr,
    CMD_echomsg,
    CMD_echon,
    CMD_edit,
    CMD_else,
    CMD_elseif,
    CMD_endfor,
    CMD_endif,
    CMD_endtry,
    CMD_endwhile,
    CMD_eval,
    CMD_execute,
    CMD_file,
    CMD_filter,
    CMD_final,
    CMD_finally,
    CMD_for,
    CMD_function,
    CMD_global,
    CMD_help,
    CMD_hide,
    CMD_if,
    CMD_ijump,
    CMD_ilist,
    CMD_isearch,
    CMD_isplit,
    CMD_keepalt,
    CMD_keepjumps,
    CMD_keepmarks,
    CMD_keeppatterns,
    CMD_leftabove,
    CMD_let,
    CMD_ll,
    CMD_lockmarks,
    CMD_lockvar,
    CMD_lshift,
    CMD_lua,
    CMD_match,
    CMD_mzscheme,
    CMD_noautocmd,
    CMD_noswapfile,
    CMD_perl,
    CMD_psearch,
    CMD_put,
    CMD_py3,
    CMD_python,
    CMD_python3,
    CMD_read,
    CMD_return,
    CMD_rightbelow,
    CMD_rshift,
    CMD_ruby,
    CMD_silent,
    CMD_smagic,
    CMD_snomagic,
    CMD_substitute,
    CMD_syntax,
    CMD_tab,
    CMD_tcl,
    CMD_terminal,
    CMD_throw,
    CMD_tilde,
    CMD_topleft,
    CMD_try,
    CMD_unlet,
    CMD_unlockvar,
    CMD_update,
    CMD_var,
    CMD_verbose,
    CMD_vertical,
    CMD_vglobal,
    CMD_while,
    CMD_wincmd,
    CMD_write
} cmdidx_T;

typedef struct exarg exarg_T;
typedef void (*ex_func_T)(exarg_T *eap);

typedef struct {
    int		cmod_did_esilent;
} cmdmod_T;

typedef int event_T;

typedef struct {
    int b_p_ma;
    struct {
        linenr_T ml_line_count;
    } b_ml;
} buf_T;

typedef struct {
    struct {
        linenr_T lnum;
        int col;
    } w_cursor;
} win_T;

static buf_T *curbuf;
static win_T *curwin;
static int global_busy;
static int msg_silent;
static int exmode_active;
static int KeyTyped;
static int updating_screen;
static cmdmod_T cmdmod;

typedef struct {
    linenr_T	lnum;
    int		col;
} pos_T;

struct cmdname
{
    char_u	*cmd_name;
    ex_func_T	cmd_func;
    long_u	cmd_argt;
    cmd_addr_T	cmd_addr_type;
};
extern struct cmdname cmdnames[];

struct exarg
{
    char_u	*arg;
    char_u	*nextcmd;
    char_u	*cmd;
    char_u	**cmdlinep;
    cmdidx_T	cmdidx;
    long	argt;
    int		skip;
    int		forceit;
    int		addr_count;
    linenr_T	line1;
    linenr_T	line2;
    cmd_addr_T	addr_type;
    int		flags;
    char_u	*do_ecmd_cmd;
    linenr_T	do_ecmd_lnum;
    int		append;
    int		usefilter;
    int		amount;
    int		regname;
    int		force_bin;
    int		read_edit;
    int		force_ff;
    int		force_enc;
    int		bad_char;
    int		useridx;
    char	*errmsg;
    char_u	*(*getline)(int, void *, int, getline_opt_T);
    void	*cookie;
};

char	*invalid_range(exarg_T *eap);
char_u	*replace_makeprg(exarg_T *eap, char_u *p, char_u **cmdlinep);
char_u	*getargcmd(char_u **);
char_u	*skipwhite(char_u *q);
char_u	*skipdigits(char_u *q);
char_u	*skiptowhite_esc(char_u *p);
int	parse_command_modifiers(exarg_T *eap, char **errormsg, cmdmod_T *cmod, int skip_only);
void	apply_cmdmod(cmdmod_T *cmod);
int	in_vim9script(void);
char_u	*skip_range(char_u *cmd_start, int skip_star, int *ctx);
char_u	*find_ex_command(exarg_T *eap, int *full, int (*lookup)(char_u *, size_t, int cmd, void *), void *cctx);
char	*semsg(const char *fmt, ...);
char	*ex_errmsg(char *msg, char_u *arg);
void	dbg_check_breakpoint(exarg_T *eap);
int	do_intthrow(void *cstack);
char_u	*vim_strnsave(char_u *string, size_t len);
char_u	*check_nextcmd(char_u *p);
char	*ex_range_without_command(exarg_T *eap);
char	*uc_fun_cmd(void);
char_u	*getnextac(int c, void *cookie, int indent, getline_opt_T options);
int	getline_equal(char_u *(*fgetline)(int, void *, int, getline_opt_T), void *cookie, char_u *(*func)(int, void *, int, getline_opt_T));
void	*getline_cookie(char_u *(*fgetline)(int, void *, int, getline_opt_T), void *cookie);
int	bt_quickfix(void *buf);
int	curbuf_locked(void);
int	text_locked(void);
int	valid_yank_reg(int reg, int writing);
char	*get_text_locked_msg(void);
int	mb_copy_char(char_u **fp, char_u **tp);
int	mb_ptr2len(char_u *p);
int	apply_autocmds(event_T event, char_u *fname, char_u *fname_io, int force, void *buf);
void	ex_ni(exarg_T *eap);
void	get_wincmd_addr_type(char_u *arg, exarg_T *eap);
int	parse_cmd_address(exarg_T *eap, char **errormsg, int silent);
int	comment_start(char_u *p, int starts_with_colon);
int	has_cmdundefined(void);
int	ask_yesno(char_u *str, int direct);
void	correct_range(exarg_T *eap);
int	getargopt(exarg_T *eap);
void	separate_nextcmd(exarg_T *eap, int keep_backslash);
long	getdigits_quoted(char_u **pp);
void	address_default_all(exarg_T *eap);
void	get_flags(exarg_T *eap);
int	expand_filename(exarg_T *eap, char_u **cmdlinep, char **errormsgp);
linenr_T	buflist_findpat(char_u *pattern, char_u *pattern_end, int unlisted, int diffmode, int curtab_only);
void	do_ucmd(exarg_T *eap);
void	emsg(char *s);
void	undo_cmdmod(cmdmod_T *cmod);

static int	quitmore = 0;
static int	ex_pressedreturn = FALSE;
#ifndef FEAT_PRINTER
# define ex_hardcopy	ex_ni
#endif

#ifdef FEAT_EVAL
static char_u	*do_one_cmd(char_u **, int, cstack_T *, char_u *(*fgetline)(int, void *, int, getline_opt_T), void *cookie);
#else
static char_u	*do_one_cmd(char_u **, int, char_u *(*fgetline)(int, void *, int, getline_opt_T), void *cookie);
static int	if_level = 0;		// depth in :if
#endif
static void	append_command(char_u *cmd);

    static void
append_command(char_u *cmd)
{
    char_u *s = cmd;
    char_u *d;

    STRCAT(IObuff, ": ");
    d = IObuff + STRLEN(IObuff);
    while (*s != NUL && d - IObuff + 5 < IOSIZE)
    {
	if (enc_utf8 ? (s[0] == 0xc2 && s[1] == 0xa0) : *s == 0xa0)
	{
	    s += enc_utf8 ? 2 : 1;
	    STRCPY(d, "<a0>");
	    d += 4;
	}
	else if (d - IObuff + (*mb_ptr2len)(s) + 1 >= IOSIZE)
	    break;
	else
	    MB_COPY_CHAR(s, d);
    }
    *d = NUL;
}

    static char_u *
do_one_cmd(
    char_u	**cmdlinep,
    int		flags,
#ifdef FEAT_EVAL
    cstack_T	*cstack,
#endif
    char_u	*(*fgetline)(int, void *, int, getline_opt_T),
    void	*cookie)		// argument for fgetline()
{
    char_u	*p;
    linenr_T	lnum;
    long	n;
    char	*errormsg = NULL;	// error message
    char_u	*after_modifier = NULL;
    exarg_T	ea;			// Ex command arguments
    cmdmod_T	save_cmdmod;
    int		save_reg_executing = reg_executing;
    int		save_pending_end_reg_executing = pending_end_reg_executing;
    int		ni;			// set when Not Implemented
    char_u	*cmd;
    int		starts_with_colon = FALSE;
#ifdef FEAT_EVAL
    int		may_have_range;
    int		vim9script;
    int		did_set_expr_line = FALSE;
#endif
    int		sourcing = flags & DOCMD_VERBOSE;

    CLEAR_FIELD(ea);
    ea.line1 = 1;
    ea.line2 = 1;
#ifdef FEAT_EVAL
    ++ex_nesting_level;
#endif

    // When the last file has not been edited :q has to be typed twice.
    if (quitmore
#ifdef FEAT_EVAL
	    // avoid that a function call in 'statusline' does this
	    && !getline_equal(fgetline, cookie, get_func_line)
#endif
	    // avoid that an autocommand, e.g. QuitPre, does this
	    && !getline_equal(fgetline, cookie, getnextac))
	--quitmore;

    /*
     * Reset browse, confirm, etc..  They are restored when returning, for
     * recursive calls.
     */
    save_cmdmod = cmdmod;

    // "#!anything" is handled like a comment.
    if ((*cmdlinep)[0] == '#' && (*cmdlinep)[1] == '!')
	goto doend;

/*
 * 1. Skip comment lines and leading white space and colons.
 * 2. Handle command modifiers.
 */
    // The "ea" structure holds the arguments that can be used.
    ea.cmd = *cmdlinep;
    ea.cmdlinep = cmdlinep;
    ea.getline = fgetline;
    ea.cookie = cookie;
#ifdef FEAT_EVAL
    ea.cstack = cstack;
    starts_with_colon = *skipwhite(ea.cmd) == ':';
#endif
    if (parse_command_modifiers(&ea, &errormsg, &cmdmod, FALSE) == FAIL)
	goto doend;
    apply_cmdmod(&cmdmod);
#ifdef FEAT_EVAL
    vim9script = in_vim9script();
#endif
    after_modifier = ea.cmd;

#ifdef FEAT_EVAL
    ea.skip = did_emsg || got_int || did_throw || (cstack->cs_idx >= 0
			 && !(cstack->cs_flags[cstack->cs_idx] & CSF_ACTIVE));
#else
    ea.skip = (if_level > 0);
#endif

/*
 * 3. Skip over the range to find the command.  Let "p" point to after it.
 *
 * We need the command to know what kind of range it uses.
 */
    cmd = ea.cmd;
#ifdef FEAT_EVAL
    // In Vim9 script a colon is required before the range.  This may also be
    // after command modifiers.
    if (vim9script && (flags & DOCMD_RANGEOK) == 0)
    {
	may_have_range = FALSE;
	for (p = ea.cmd; p >= *cmdlinep; --p)
	{
	    if (*p == ':')
		may_have_range = TRUE;
	    if (p < ea.cmd && !VIM_ISWHITE(*p))
		break;
	}
    }
    else
	may_have_range = TRUE;
    if (may_have_range)
#endif
	ea.cmd = skip_range(ea.cmd, TRUE, NULL);

#ifdef FEAT_EVAL
    if (vim9script && !may_have_range)
    {
	if (ea.cmd == cmd + 1 && *cmd == '$')
	    // should be "$VAR = val"
	    --ea.cmd;
	p = find_ex_command(&ea, NULL, lookup_scriptitem, NULL);
	if (ea.cmdidx == CMD_SIZE)
	{
	    char_u *ar = skip_range(ea.cmd, TRUE, NULL);

	    // If a ':' before the range is missing, give a clearer error
	    // message.
	    if (ar > ea.cmd && !ea.skip)
	    {
		semsg(_(e_colon_required_before_range_str), ea.cmd);
		goto doend;
	    }
	}
    }
    else
#endif
	p = find_ex_command(&ea, NULL, NULL, NULL);

#ifdef FEAT_EVAL
# ifdef FEAT_PROFILE
    // Count this line for profiling if skip is TRUE.
    if (do_profiling == PROF_YES
	    && (!ea.skip || cstack->cs_idx == 0 || (cstack->cs_idx > 0
		     && (cstack->cs_flags[cstack->cs_idx - 1] & CSF_ACTIVE))))
    {
	int skip = did_emsg || got_int || did_throw;

	if (ea.cmdidx == CMD_catch)
	    skip = !skip && !(cstack->cs_idx >= 0
			  && (cstack->cs_flags[cstack->cs_idx] & CSF_THROWN)
			  && !(cstack->cs_flags[cstack->cs_idx] & CSF_CAUGHT));
	else if (ea.cmdidx == CMD_else || ea.cmdidx == CMD_elseif)
	    skip = skip || !(cstack->cs_idx >= 0
			  && !(cstack->cs_flags[cstack->cs_idx]
						  & (CSF_ACTIVE | CSF_TRUE)));
	else if (ea.cmdidx == CMD_finally)
	    skip = FALSE;
	else if (ea.cmdidx != CMD_endif
		&& ea.cmdidx != CMD_endfor
		&& ea.cmdidx != CMD_endtry
		&& ea.cmdidx != CMD_endwhile)
	    skip = ea.skip;

	if (!skip)
	{
	    if (getline_equal(fgetline, cookie, get_func_line))
		func_line_exec(getline_cookie(fgetline, cookie));
	    else if (getline_equal(fgetline, cookie, getsourceline))
		script_line_exec();
	}
    }
# endif

    // May go to debug mode.  If this happens and the ">quit" debug command is
    // used, throw an interrupt exception and skip the next command.
    dbg_check_breakpoint(&ea);
    if (!ea.skip && got_int)
    {
	ea.skip = TRUE;
	(void)do_intthrow(cstack);
    }
#endif

/*
 * 4. parse a range specifier of the form: addr [,addr] [;addr] ..
 *
 * where 'addr' is:
 *
 * %	      (entire file)
 * $  [+-NUM]
 * 'x [+-NUM] (where x denotes a currently defined mark)
 * .  [+-NUM]
 * [+-NUM]..
 * NUM
 *
 * The ea.cmd pointer is updated to point to the first character following the
 * range spec. If an initial address is found, but no second, the upper bound
 * is equal to the lower.
 */

    // ea.addr_type for user commands is set by find_ucmd
    if (!IS_USER_CMDIDX(ea.cmdidx))
    {
	if (ea.cmdidx != CMD_SIZE)
	    ea.addr_type = cmdnames[(int)ea.cmdidx].cmd_addr_type;
	else
	    ea.addr_type = ADDR_LINES;

	// :wincmd range depends on the argument.
	if (ea.cmdidx == CMD_wincmd && p != NULL)
	    get_wincmd_addr_type(skipwhite(p), &ea);
#ifdef FEAT_QUICKFIX
	// :.cc in quickfix window uses line number
	if ((ea.cmdidx == CMD_cc || ea.cmdidx == CMD_ll) && bt_quickfix(curbuf))
	    ea.addr_type = ADDR_OTHER;
#endif
    }

    ea.cmd = cmd;
#ifdef FEAT_EVAL
    if (!may_have_range)
	ea.line1 = ea.line2 = default_address(&ea);
    else
#endif
	if (parse_cmd_address(&ea, &errormsg, FALSE) == FAIL)
	    goto doend;

/*
 * 5. Parse the command.
 */

    /*
     * Skip ':' and any white space
     */
    ea.cmd = skipwhite(ea.cmd);
    while (*ea.cmd == ':')
	ea.cmd = skipwhite(ea.cmd + 1);

    /*
     * If we got a line, but no command, then go to the line.
     * If we find a '|' or '\n' we set ea.nextcmd.
     */
    if (*ea.cmd == NUL || comment_start(ea.cmd, starts_with_colon)
			       || (ea.nextcmd = check_nextcmd(ea.cmd)) != NULL)
    {
	/*
	 * strange vi behaviour:
	 * ":3"		jumps to line 3
	 * ":3|..."	prints line 3  (not in Vim9 script)
	 * ":|"		prints current line  (not in Vim9 script)
	 */
	if (ea.skip)	    // skip this if inside :if
	    goto doend;
	errormsg = ex_range_without_command(&ea);
	goto doend;
    }

    // If this looks like an undefined user command and there are CmdUndefined
    // autocommands defined, trigger the matching autocommands.
    if (p != NULL && ea.cmdidx == CMD_SIZE && !ea.skip
	    && ASCII_ISUPPER(*ea.cmd)
	    && has_cmdundefined())
    {
	int ret;

	p = ea.cmd;
	while (ASCII_ISALNUM(*p))
	    ++p;
	p = vim_strnsave(ea.cmd, p - ea.cmd);
	ret = apply_autocmds(EVENT_CMDUNDEFINED, p, p, TRUE, NULL);
	vim_free(p);
	// If the autocommands did something and didn't cause an error, try
	// finding the command again.
	p = (ret
#ifdef FEAT_EVAL
		&& !aborting()
#endif
		) ? find_ex_command(&ea, NULL, NULL, NULL) : ea.cmd;
    }

    if (p == NULL)
    {
	if (!ea.skip)
	    errormsg = _(e_ambiguous_use_of_user_defined_command);
	goto doend;
    }
    // Check for wrong commands.
    if (*p == '!' && ea.cmd[1] == 0151 && ea.cmd[0] == 78
	    && !IS_USER_CMDIDX(ea.cmdidx))
    {
	errormsg = uc_fun_cmd();
	goto doend;
    }

    if (ea.cmdidx == CMD_SIZE)
    {
	if (!ea.skip)
	{
	    STRCPY(IObuff, _(e_not_an_editor_command));
	    if (!sourcing)
	    {
		// If the modifier was parsed OK the error must be in the
		// following command
		if (after_modifier != NULL)
		    append_command(after_modifier);
		else
		    append_command(*cmdlinep);
	    }
	    errormsg = (char *)IObuff;
	    did_emsg_syntax = TRUE;
	}
	goto doend;
    }

    ni = (!IS_USER_CMDIDX(ea.cmdidx)
	    && (cmdnames[ea.cmdidx].cmd_func == ex_ni
#ifdef HAVE_EX_SCRIPT_NI
	     || cmdnames[ea.cmdidx].cmd_func == ex_script_ni
#endif
	     ));

#ifndef FEAT_EVAL
    /*
     * When the expression evaluation is disabled, recognize the ":if" and
     * ":endif" commands and ignore everything in between it.
     */
    if (ea.cmdidx == CMD_if)
	++if_level;
    if (if_level)
    {
	if (ea.cmdidx == CMD_endif)
	    --if_level;
	goto doend;
    }

#endif

    // forced commands
    if (*p == '!' && ea.cmdidx != CMD_substitute
	    && ea.cmdidx != CMD_smagic && ea.cmdidx != CMD_snomagic)
    {
	++p;
	ea.forceit = TRUE;
    }
    else
	ea.forceit = FALSE;

/*
 * 6. Parse arguments.  Then check for errors.
 */
    if (!IS_USER_CMDIDX(ea.cmdidx))
	ea.argt = (long)cmdnames[(int)ea.cmdidx].cmd_argt;

    if (!ea.skip)
    {
#ifdef HAVE_SANDBOX
	if (sandbox != 0 && !(ea.argt & EX_SBOXOK))
	{
	    // Command not allowed in sandbox.
	    errormsg = _(e_not_allowed_in_sandbox);
	    goto doend;
	}
#endif
	if (restricted != 0 && (ea.argt & EX_RESTRICT))
	{
	    errormsg = _(e_command_not_allowed_in_rvim);
	    goto doend;
	}
	if (!curbuf->b_p_ma && (ea.argt & EX_MODIFY))
	{
	    // Command not allowed in non-'modifiable' buffer
	    errormsg = _(e_cannot_make_changes_modifiable_is_off);
	    goto doend;
	}

	if (!IS_USER_CMDIDX(ea.cmdidx))
	{
#ifdef FEAT_CMDWIN
	    if (cmdwin_type != 0 && !(ea.argt & EX_CMDWIN))
	    {
		// Command not allowed in the command line window
		errormsg = _(e_invalid_in_cmdline_window);
		goto doend;
	    }
#endif
	    if (text_locked() && !(ea.argt & EX_LOCK_OK))
	    {
		// Command not allowed when text is locked
		errormsg = _(get_text_locked_msg());
		goto doend;
	    }
	}

	// Disallow editing another buffer when "curbuf_lock" is set.
	// Do allow ":checktime" (it is postponed).
	// Do allow ":edit" (check for an argument later).
	// Do allow ":file" with no arguments (check for an argument later).
	if (!(ea.argt & (EX_CMDWIN | EX_LOCK_OK))
		&& ea.cmdidx != CMD_checktime
		&& ea.cmdidx != CMD_edit
		&& ea.cmdidx != CMD_file
		&& !IS_USER_CMDIDX(ea.cmdidx)
		&& curbuf_locked())
	    goto doend;

	if (!ni && !(ea.argt & EX_RANGE) && ea.addr_count > 0)
	{
	    errormsg = _(e_no_range_allowed);
	    goto doend;
	}
    }

    if (!ni && !(ea.argt & EX_BANG) && ea.forceit)
    {
	errormsg = _(e_no_bang_allowed);
	goto doend;
    }

    /*
     * Don't complain about the range if it is not used
     * (could happen if line_count is accidentally set to 0).
     */
    if (!ea.skip && !ni && (ea.argt & EX_RANGE))
    {
	/*
	 * If the range is backwards, ask for confirmation and, if given, swap
	 * ea.line1 & ea.line2 so it's forwards again.
	 * When global command is busy, don't ask, will fail below.
	 */
	if (!global_busy && ea.line1 > ea.line2)
	{
	    if (msg_silent == 0)
	    {
		if (sourcing || exmode_active)
		{
		    errormsg = _(e_backwards_range_given);
		    goto doend;
		}
		if (ask_yesno((char_u *)
			_("Backwards range given, OK to swap"), FALSE) != 'y')
		    goto doend;
	    }
	    lnum = ea.line1;
	    ea.line1 = ea.line2;
	    ea.line2 = lnum;
	}
	if ((errormsg = invalid_range(&ea)) != NULL)
	    goto doend;
    }

    if ((ea.addr_type == ADDR_OTHER) && ea.addr_count == 0)
	// default is 1, not cursor
	ea.line2 = 1;

    correct_range(&ea);

#ifdef FEAT_FOLDING
    if (((ea.argt & EX_WHOLEFOLD) || ea.addr_count >= 2) && !global_busy
	    && ea.addr_type == ADDR_LINES)
    {
	// Put the first line at the start of a closed fold, put the last line
	// at the end of a closed fold.
	(void)hasFolding(ea.line1, &ea.line1, NULL);
	(void)hasFolding(ea.line2, NULL, &ea.line2);
    }
#endif

#ifdef FEAT_QUICKFIX
    /*
     * For the ":make" and ":grep" commands we insert the 'makeprg'/'grepprg'
     * option here, so things like % get expanded.
     */
    p = replace_makeprg(&ea, p, cmdlinep);
    if (p == NULL)
	goto doend;
#endif

    /*
     * Skip to start of argument.
     * Don't do this for the ":!" command, because ":!! -l" needs the space.
     */
    if (ea.cmdidx == CMD_bang)
	ea.arg = p;
    else
	ea.arg = skipwhite(p);

    // ":file" cannot be run with an argument when "curbuf_lock" is set
    if (ea.cmdidx == CMD_file && *ea.arg != NUL && curbuf_locked())
	goto doend;

    /*
     * Check for "++opt=val" argument.
     * Must be first, allow ":w ++enc=utf8 !cmd"
     */
    if (ea.argt & EX_ARGOPT)
	while (ea.arg[0] == '+' && ea.arg[1] == '+')
	    if (getargopt(&ea) == FAIL && !ni)
	    {
		errormsg = _(e_invalid_argument);
		goto doend;
	    }

    if (ea.cmdidx == CMD_write || ea.cmdidx == CMD_update)
    {
	if (*ea.arg == '>')			// append
	{
	    if (*++ea.arg != '>')		// typed wrong
	    {
		errormsg = _(e_use_w_or_w_gt_gt);
		goto doend;
	    }
	    ea.arg = skipwhite(ea.arg + 1);
	    ea.append = TRUE;
	}
	else if (*ea.arg == '!' && ea.cmdidx == CMD_write)  // :w !filter
	{
	    ++ea.arg;
	    ea.usefilter = TRUE;
	}
    }

    if (ea.cmdidx == CMD_read)
    {
	if (ea.forceit)
	{
	    ea.usefilter = TRUE;		// :r! filter if ea.forceit
	    ea.forceit = FALSE;
	}
	else if (*ea.arg == '!')		// :r !filter
	{
	    ++ea.arg;
	    ea.usefilter = TRUE;
	}
    }

    if (ea.cmdidx == CMD_lshift || ea.cmdidx == CMD_rshift)
    {
	ea.amount = 1;
	while (*ea.arg == *ea.cmd)		// count number of '>' or '<'
	{
	    ++ea.arg;
	    ++ea.amount;
	}
	ea.arg = skipwhite(ea.arg);
    }

    /*
     * Check for "+command" argument, before checking for next command.
     * Don't do this for ":read !cmd" and ":write !cmd".
     */
    if ((ea.argt & EX_CMDARG) && !ea.usefilter)
	ea.do_ecmd_cmd = getargcmd(&ea.arg);

    /*
     * For commands that do not use '|' inside their argument: Check for '|' to
     * separate commands and '"' or '#' to start comments.
     *
     * Otherwise: Check for <newline> to end a shell command.
     * Also do this for ":read !cmd", ":write !cmd" and ":global".
     * Also do this inside a { - } block after :command and :autocmd.
     * Any others?
     */
    if ((ea.argt & EX_TRLBAR) && !ea.usefilter)
    {
	separate_nextcmd(&ea, FALSE);
    }
    else if (ea.cmdidx == CMD_bang
	    || ea.cmdidx == CMD_terminal
	    || ea.cmdidx == CMD_global
	    || ea.cmdidx == CMD_vglobal
	    || ea.usefilter
#ifdef FEAT_EVAL
	    || inside_block(&ea)
#endif
	    )
    {
	for (p = ea.arg; *p; ++p)
	{
	    // Remove one backslash before a newline, so that it's possible to
	    // pass a newline to the shell and also a newline that is preceded
	    // with a backslash.  This makes it impossible to end a shell
	    // command in a backslash, but that doesn't appear useful.
	    // Halving the number of backslashes is incompatible with previous
	    // versions.
	    if (*p == '\\' && p[1] == '\n')
		STRMOVE(p, p + 1);
	    else if (*p == '\n' && !(ea.argt & EX_EXPR_ARG))
	    {
		ea.nextcmd = p + 1;
		*p = NUL;
		break;
	    }
	}
    }

    if ((ea.argt & EX_DFLALL) && ea.addr_count == 0)
	address_default_all(&ea);

    // accept numbered register only when no count allowed (:put)
    if (       (ea.argt & EX_REGSTR)
	    && *ea.arg != NUL
	       // Do not allow register = for user commands
	    && (!IS_USER_CMDIDX(ea.cmdidx) || *ea.arg != '=')
	    && !((ea.argt & EX_COUNT) && VIM_ISDIGIT(*ea.arg)))
    {
#ifndef FEAT_CLIPBOARD
	// check these explicitly for a more specific error message
	if (*ea.arg == '*' || *ea.arg == '+')
	{
	    errormsg = _(e_invalid_register_name);
	    goto doend;
	}
#endif
	if (valid_yank_reg(*ea.arg, (ea.cmdidx != CMD_put
					      && !IS_USER_CMDIDX(ea.cmdidx))))
	{
	    ea.regname = *ea.arg++;
#ifdef FEAT_EVAL
	    // for '=' register: accept the rest of the line as an expression
	    if (ea.arg[-1] == '=' && ea.arg[0] != NUL)
	    {
		if (!ea.skip)
		{
		    set_expr_line(vim_strsave(ea.arg), &ea);
		    did_set_expr_line = TRUE;
		}
		ea.arg += STRLEN(ea.arg);
	    }
#endif
	    ea.arg = skipwhite(ea.arg);
	}
    }

    /*
     * Check for a count.  When accepting a EX_BUFNAME, don't use "123foo" as a
     * count, it's a buffer name.
     */
    if ((ea.argt & EX_COUNT) && VIM_ISDIGIT(*ea.arg)
	    && (!(ea.argt & EX_BUFNAME) || *(p = skipdigits(ea.arg + 1)) == NUL
							  || VIM_ISWHITE(*p)))
    {
	n = getdigits_quoted(&ea.arg);
	ea.arg = skipwhite(ea.arg);
	if (n <= 0 && !ni && (ea.argt & EX_ZEROR) == 0)
	{
	    errormsg = _(e_positive_count_required);
	    goto doend;
	}
	if (ea.addr_type != ADDR_LINES)	// e.g. :buffer 2, :sleep 3
	{
	    ea.line2 = n;
	    if (ea.addr_count == 0)
		ea.addr_count = 1;
	}
	else
	{
	    ea.line1 = ea.line2;
	    if (ea.line2 >= LONG_MAX - (n - 1))
		ea.line2 = LONG_MAX;  // avoid overflow
	    else
		ea.line2 += n - 1;
	    ++ea.addr_count;
	    /*
	     * Be vi compatible: no error message for out of range.
	     */
	    if (ea.line2 > curbuf->b_ml.ml_line_count)
		ea.line2 = curbuf->b_ml.ml_line_count;
	}
    }

    /*
     * Check for flags: 'l', 'p' and '#'.
     */
    if (ea.argt & EX_FLAGS)
	get_flags(&ea);
    if (!ni && !(ea.argt & EX_EXTRA) && *ea.arg != NUL
	    && *ea.arg != '"' && (*ea.arg != '|' || (ea.argt & EX_TRLBAR) == 0))
    {
	// no arguments allowed but there is something
	errormsg = ex_errmsg(e_trailing_characters_str, ea.arg);
	goto doend;
    }

    if (!ni && (ea.argt & EX_NEEDARG) && *ea.arg == NUL)
    {
	errormsg = _(e_argument_required);
	goto doend;
    }

#ifdef FEAT_EVAL
    /*
     * Skip the command when it's not going to be executed.
     * The commands like :if, :endif, etc. always need to be executed.
     * Also make an exception for commands that handle a trailing command
     * themselves.
     */
    if (ea.skip)
    {
	switch (ea.cmdidx)
	{
	    // commands that need evaluation
	    case CMD_while:
	    case CMD_endwhile:
	    case CMD_for:
	    case CMD_endfor:
	    case CMD_if:
	    case CMD_elseif:
	    case CMD_else:
	    case CMD_endif:
	    case CMD_try:
	    case CMD_catch:
	    case CMD_finally:
	    case CMD_endtry:
	    case CMD_function:
	    case CMD_def:
				break;

	    // Commands that handle '|' themselves.  Check: A command should
	    // either have the EX_TRLBAR flag, appear in this list or appear in
	    // the list at ":help :bar".
	    case CMD_aboveleft:
	    case CMD_and:
	    case CMD_belowright:
	    case CMD_botright:
	    case CMD_browse:
	    case CMD_call:
	    case CMD_confirm:
	    case CMD_const:
	    case CMD_delfunction:
	    case CMD_djump:
	    case CMD_dlist:
	    case CMD_dsearch:
	    case CMD_dsplit:
	    case CMD_echo:
	    case CMD_echoerr:
	    case CMD_echomsg:
	    case CMD_echon:
	    case CMD_eval:
	    case CMD_execute:
	    case CMD_filter:
	    case CMD_final:
	    case CMD_help:
	    case CMD_hide:
	    case CMD_ijump:
	    case CMD_ilist:
	    case CMD_isearch:
	    case CMD_isplit:
	    case CMD_keepalt:
	    case CMD_keepjumps:
	    case CMD_keepmarks:
	    case CMD_keeppatterns:
	    case CMD_leftabove:
	    case CMD_let:
	    case CMD_lockmarks:
	    case CMD_lockvar:
	    case CMD_lua:
	    case CMD_match:
	    case CMD_mzscheme:
	    case CMD_noautocmd:
	    case CMD_noswapfile:
	    case CMD_perl:
	    case CMD_psearch:
	    case CMD_py3:
	    case CMD_python3:
	    case CMD_python:
	    case CMD_return:
	    case CMD_rightbelow:
	    case CMD_ruby:
	    case CMD_silent:
	    case CMD_smagic:
	    case CMD_snomagic:
	    case CMD_substitute:
	    case CMD_syntax:
	    case CMD_tab:
	    case CMD_tcl:
	    case CMD_throw:
	    case CMD_tilde:
	    case CMD_topleft:
	    case CMD_unlet:
	    case CMD_unlockvar:
	    case CMD_var:
	    case CMD_verbose:
	    case CMD_vertical:
	    case CMD_wincmd:
				break;

	    default:		goto doend;
	}
    }
#endif

    if (ea.argt & EX_XFILE)
    {
	if (expand_filename(&ea, cmdlinep, &errormsg) == FAIL)
	    goto doend;
    }

    /*
     * Accept buffer name.  Cannot be used at the same time with a buffer
     * number.  Don't do this for a user command.
     */
    if ((ea.argt & EX_BUFNAME) && *ea.arg != NUL && ea.addr_count == 0
	    && !IS_USER_CMDIDX(ea.cmdidx))
    {
	/*
	 * :bdelete, :bwipeout and :bunload take several arguments, separated
	 * by spaces: find next space (skipping over escaped characters).
	 * The others take one argument: ignore trailing spaces.
	 */
	if (ea.cmdidx == CMD_bdelete || ea.cmdidx == CMD_bwipeout
						  || ea.cmdidx == CMD_bunload)
	    p = skiptowhite_esc(ea.arg);
	else
	{
	    p = ea.arg + STRLEN(ea.arg);
	    while (p > ea.arg && VIM_ISWHITE(p[-1]))
		--p;
	}
	ea.line2 = buflist_findpat(ea.arg, p, (ea.argt & EX_BUFUNL) != 0,
								FALSE, FALSE);
	if (ea.line2 < 0)	    // failed
	    goto doend;
	ea.addr_count = 1;
	ea.arg = skipwhite(p);
    }

    // The :try command saves the emsg_silent flag, reset it here when
    // ":silent! try" was used, it should only apply to :try itself.
    if (ea.cmdidx == CMD_try && cmdmod.cmod_did_esilent > 0)
    {
	emsg_silent -= cmdmod.cmod_did_esilent;
	if (emsg_silent < 0)
	    emsg_silent = 0;
	cmdmod.cmod_did_esilent = 0;
    }

/*
 * 7. Execute the command.
 */

    if (IS_USER_CMDIDX(ea.cmdidx))
    {
	/*
	 * Execute a user-defined command.
	 */
	do_ucmd(&ea);
    }
    else
    {
	/*
	 * Call the function to execute the builtin command.
	 */
	ea.errmsg = NULL;
	(cmdnames[ea.cmdidx].cmd_func)(&ea);
	if (ea.errmsg != NULL)
	    errormsg = ea.errmsg;
    }

#ifdef FEAT_EVAL
    // Set flag that any command was executed, used by ex_vim9script().
    // Not if this was a command that wasn't executed or :endif.
    if (sourcing_a_script(&ea)
	    && current_sctx.sc_sid > 0
	    && ea.cmdidx != CMD_endif
	    && (cstack->cs_idx < 0
		    || (cstack->cs_flags[cstack->cs_idx] & CSF_ACTIVE)))
	SCRIPT_ITEM(current_sctx.sc_sid)->sn_state = SN_STATE_HAD_COMMAND;

    /*
     * If the command just executed called do_cmdline(), any throw or ":return"
     * or ":finish" encountered there must also check the cstack of the still
     * active do_cmdline() that called this do_one_cmd().  Rethrow an uncaught
     * exception, or reanimate a returned function or finished script file and
     * return or finish it again.
     */
    if (need_rethrow)
	do_throw(cstack);
    else if (check_cstack)
    {
	if (source_finished(fgetline, cookie))
	    do_finish(&ea, TRUE);
	else if (getline_equal(fgetline, cookie, get_func_line)
						   && current_func_returned())
	    do_return(&ea, TRUE, FALSE, NULL);
    }
    need_rethrow = check_cstack = FALSE;
#endif

doend:
    if (curwin->w_cursor.lnum == 0)	// can happen with zero line number
    {
	curwin->w_cursor.lnum = 1;
	curwin->w_cursor.col = 0;
    }

    if (errormsg != NULL && *errormsg != NUL && !did_emsg)
    {
	if (sourcing || !KeyTyped)
	{
	    if (errormsg != (char *)IObuff)
	    {
		STRCPY(IObuff, errormsg);
		errormsg = (char *)IObuff;
	    }
	    append_command(*cmdlinep);
	}
	emsg(errormsg);
    }
#ifdef FEAT_EVAL
    do_errthrow(cstack,
	    (ea.cmdidx != CMD_SIZE && !IS_USER_CMDIDX(ea.cmdidx))
			? cmdnames[(int)ea.cmdidx].cmd_name : (char_u *)NULL);

    if (did_set_expr_line)
	set_expr_line(NULL, NULL);
#endif

    undo_cmdmod(&cmdmod);
    cmdmod = save_cmdmod;
    reg_executing = save_reg_executing;
    pending_end_reg_executing = save_pending_end_reg_executing;

    if (ea.nextcmd && *ea.nextcmd == NUL)	// not really a next command
	ea.nextcmd = NULL;

#ifdef FEAT_EVAL
    --ex_nesting_level;
    vim_free(ea.cmdline_tofree);
#endif

    return ea.nextcmd;
}
