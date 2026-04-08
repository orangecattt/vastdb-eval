// Minimal reproducible example for dialog_changed function
// Compile with: clang++ -c bad.cpp

#include <cstring>
#include <cstdio>

// ============================================================================
// Type definitions
// ============================================================================

// from: src/vim.h:359
typedef unsigned char	char_u;

// from: src/vim.h:1827
typedef long	linenr_T;

// from: src/structs.h:648
typedef struct {
    int		cmod_flags;
} cmdmod_T;

// from: src/structs.h:89
typedef struct {
    int		sc_sid;
    int		sc_lnum;
    int		sc_version;
} sctx_T;

// Forward declaration
// from: src/structs.h:63
typedef struct file_buffer	buf_T;

// from: src/ex_cmds.h:89
typedef struct exarg exarg_T;

// from: src/structs.h:104
typedef void (*ex_func_T) (exarg_T *eap);

// from: src/ex_cmds.h:104
struct exarg {
    char_u	*arg;
    int		forceit;
    int		append;
    ex_func_T	ex_func;
};

// from: src/structs.h:98
typedef struct {
    buf_T   *br_buf;
    int	    br_fnum;
    int	    br_buf_free_count;
} bufref_T;

// from: src/structs.h:3014
struct file_buffer
{
    // memline_T	b_ml;		// simplified
    struct {
        linenr_T	ml_line_count;
    } b_ml;

    buf_T	*b_next;
    buf_T	*b_prev;
    int		b_nwindows;
    int		b_flags;
    int		b_locked;
    int		b_locked_split;
    char_u	*b_ffname;
    char_u	*b_sfname;
    char_u	*b_fname;
    int		b_fnum;
    int		b_changed;
    int		b_p_ro;
};

// ============================================================================
// Global variables (declarations only)
// ============================================================================

// from: src/globals.h:1046
extern buf_T	*firstbuf;

// from: src/globals.h:1048
extern buf_T	*curbuf;

// from: src/globals.h:1463
extern cmdmod_T	cmdmod;

// from: src/option.h:513
extern int	p_confirm;

// from: src/option.h:1113
extern int	p_wa;

// from: src/option.h:537
extern char_u	*p_cpo;

// from: src/option.h:566
extern char_u	*p_dir;

// from: src/vim.h:1494
extern int	highlight_attr[];

// from: src/errors.h:34
extern char e_file_exists[];

// from: src/errors.h:45
extern char e_str_is_directory[];

// from: src/errors.h:1958
extern char e_swap_file_exists_str_silent_overrides[];

// from: src/globals.h:1471
extern int	emsg_silent;

// ============================================================================
// Macros
// ============================================================================

// from: src/vim.h:754
#if !(defined(OK) && (OK == 1))
# define OK			1
#endif

// from: src/vim.h:758
#define FAIL			0

// from: src/ascii.h:18
#define NUL		'\000'

// from: src/vim.h:1240
#define VIM_QUESTION	4

// from: src/vim.h:1246
#define VIM_YES		2

// from: src/vim.h:1247
#define VIM_NO		3

// from: src/vim.h:1249
#define VIM_ALL		5

// from: src/vim.h:1250
#define VIM_DISCARDALL  6

// from: src/vim.h:1646
#define DIALOG_MSG_SIZE 1000

// from: src/vim.h:1724
#define CLEAR_FIELD(field)  vim_memset(&(field), 0, sizeof(field))

// from: src/macros.h:462
#define FOR_ALL_BUFFERS(buf) \
    for ((buf) = firstbuf; (buf) != NULL; (buf) = (buf)->b_next)

// from: src/vim.h:1732
#define STRCPY(d, s)	    strcpy((char *)(d), (char *)(s))

// from: src/option.h:198
#define CPO_OVERNEW	'O'

// from: src/vim.h:768
#define BF_NOTEDITED	0x08

// from: src/vim.h:771
#define BF_NEW		0x10

// from: src/vim.h:773
#define BF_READERR	0x40

// from: src/structs.h:682
#define CMOD_BROWSE	    0x0040

// from: src/structs.h:683
#define CMOD_CONFIRM	    0x0080

// from: src/vim.h:1466
typedef enum
{
    HLF_W = 27
} highlight_T;

// from: src/vim.h:1890
#define HL_ATTR(n)	highlight_attr[(int)(n)]

// from: src/vim.h:595
#define _(x) ((char *)(x))

// from: src/vim.h:597
#define N_(x) x

// from: src/vim.h:1721
#define vim_memset(ptr, c, size)  memset((ptr), (c), (size))

// from: src/vim.h:74
#define TRUE			1

// from: src/vim.h:75
#define FALSE			0

// from: src/macros.h:361
#define VIM_CLEAR(p) \
    do { \
	if ((p) != NULL) \
	{ \
	    vim_free(p); \
	    (p) = NULL; \
	} \
    } while (0)

// from: src/os_win32.h:111
#define MAXPATHL	1024

// from: src/macros.h:114
#define VIM_ISDIGIT(c) ((unsigned)(c) - '0' < 10)

// from: src/macros.h:118
#define ASCII_ISLOWER(c) ((unsigned)(c) - 'a' < 26)

// from: src/macros.h:119
#define ASCII_ISUPPER(c) ((unsigned)(c) - 'A' < 26)

// from: src/macros.h:120
#define ASCII_ISALPHA(c) (ASCII_ISUPPER(c) || ASCII_ISLOWER(c))

// from: src/vim.h:1731
#define STRLEN(s)	    strlen((char *)(s))

// ============================================================================
// Function declarations
// ============================================================================

// from: src/alloc.c:149
char_u *alloc(size_t size);

// from: src/alloc.c:609
void vim_free(void *x);

// from: src/buffer.c:408
void set_bufref(bufref_T *bufref, buf_T *buf);

// from: src/buffer.c:423
int bufref_valid(bufref_T *bufref);

// from: src/buffer.c:3072
buf_T *buflist_findnr(int nr);

// from: src/buffer.c:5390
void fname_expand(buf_T *buf, char_u **ffname, char_u **sfname);

// from: src/buffer.c:5345
char_u *fix_fname(char_u *fname);

// from: src/filepath.c:3146
char_u *FullName_save(char_u *fname, int force);

// from: src/filepath.c:4302
int vim_isAbsName(char_u *name);

// from: src/filepath.c:4313
int vim_FullName(char_u *fname, char_u *buf, int len, int force);

// from: src/misc1.c:2733
int path_with_url(char_u *fname);

// from: src/os_unix.c:2828
int mch_isFullName(char_u *fname);

// from: src/buffer.c:5867
int bt_nofilename(buf_T *buf);

// from: src/buffer.c:5904
int bt_dontwrite(buf_T *buf);

// from: src/bufwrite.c:627
int buf_write(buf_T *buf, char_u *fname, char_u *sfname, linenr_T start, linenr_T end, exarg_T *eap, int append, int forceit, int reset_changed, int filtering);

// from: src/ex_cmds.c:2127
int check_overwrite(exarg_T *eap, buf_T *buf, char_u *fname, char_u *ffname, int other);

// from: src/ex_cmds2.c:136
void browse_save_fname(buf_T *buf);

// from: src/ex_cmds2.c:450
int buf_write_all(buf_T *buf, int forceit);

// from: src/filepath.c:3173
int vim_fexists(char_u *fname);

// from: src/message.c:100
int msg(char *s);

// from: src/message.c:522
void msg_source(int attr);

// from: src/message.c:785
int emsg(char *s);

// from: src/message.c:802
void semsg(char *fmt, ...);

// from: src/message.c:4425
int vim_dialog_yesno(int type, char_u *title, char_u *message, int dflt);

// from: src/message.c:4440
int vim_dialog_yesnocancel(int type, char_u *title, char_u *message, int dflt);

// from: src/message.c:4458
int vim_dialog_yesnoallcancel(int type, char_u *title, char_u *message, int dflt);

// from: src/misc2.c:741
void copy_option_part(char_u **option, char_u *buf, int buflen, const char *sep);

// from: src/memline.c:4655
char_u *makeswapname(char_u *fname, char_u *ffname, buf_T *buf, char_u *dir);

// from: src/strings.c:599
char_u *vim_strchr(char_u *string, int c);

// from: src/strings.c:2215
int vim_snprintf(char *str, size_t str_m, const char *fmt, ...);

// from: src/undo.c:3598
int bufIsChanged(buf_T *buf);

// from: src/change.c:908
void unchanged(buf_T *buf, int ff, int always_inc_changedtick);

// from: src/ex_docmd.c:9813
void dialog_msg(char_u *buff, char *format, char_u *fname);

// from: src/os_unix.c:3334
int mch_isdir(char_u *name);

// from: src/strings.c:21
char_u *vim_strsave(char_u *string);

// from: src/ex_cmds2.c:450
int
buf_write_all(buf_T *buf, int forceit)
{
    int	    retval;
    buf_T	*old_curbuf = curbuf;

    retval = (buf_write(buf, buf->b_ffname, buf->b_fname,
				   (linenr_T)1, buf->b_ml.ml_line_count, NULL,
						  FALSE, forceit, TRUE, FALSE));
    if (curbuf != old_curbuf)
    {
	msg_source(HL_ATTR(HLF_W));
	msg(_("Warning: Entered other buffer unexpectedly (check autocommands)"));
    }
    return retval;
}

// from: src/ex_cmds.c:2127
int
check_overwrite(
    exarg_T	*eap,
    buf_T	*buf,
    char_u	*fname,	    // file name to be used (can differ from
			    // buf->ffname)
    char_u	*ffname,    // full path version of fname
    int		other)	    // writing under other name
{
    /*
     * Write to another file or b_flags set or not writing the whole file:
     * overwriting only allowed with '!'.
     * If "other" is FALSE and bt_nofilename(buf) is TRUE, this must be
     * writing an "acwrite" buffer to the same file as its b_ffname, and
     * buf_write() will only allow writing with BufWriteCmd autocommands,
     * so there is no need for an overwrite check.
     */
    if (       (other
		|| (!bt_nofilename(buf)
		    && ((buf->b_flags & BF_NOTEDITED)
			|| ((buf->b_flags & BF_NEW)
			    && vim_strchr(p_cpo, CPO_OVERNEW) == NULL)
			|| (buf->b_flags & BF_READERR))))
	    && !p_wa
	    && vim_fexists(ffname))
    {
	if (!eap->forceit && !eap->append)
	{
#ifdef UNIX
	    // with UNIX it is possible to open a directory
	    if (mch_isdir(ffname))
	    {
		semsg(_(e_str_is_directory), ffname);
		return FAIL;
	    }
#endif
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
	    if (p_confirm || (cmdmod.cmod_flags & CMOD_CONFIRM))
	    {
		char_u	buff[DIALOG_MSG_SIZE];

		dialog_msg(buff, _("Overwrite existing file \"%s\"?"), fname);
		if (vim_dialog_yesno(VIM_QUESTION, NULL, buff, 2) != VIM_YES)
		    return FAIL;
		eap->forceit = TRUE;
	    }
	    else
#endif
	    {
		emsg(_(e_file_exists));
		return FAIL;
	    }
	}

	// For ":w! filename" check that no swap file exists for "filename".
	if (other && !emsg_silent)
	{
	    char_u	*dir;
	    char_u	*p;
	    int		r;
	    char_u	*swapname;

	    // We only try the first entry in 'directory', without checking if
	    // it's writable.  If the "." directory is not writable the write
	    // will probably fail anyway.
	    // Use 'shortname' of the current buffer, since there is no buffer
	    // for the written file.
	    if (*p_dir == NUL)
	    {
		dir = alloc(5);
		if (dir == NULL)
		    return FAIL;
		STRCPY(dir, ".");
	    }
	    else
	    {
		dir = alloc(MAXPATHL);
		if (dir == NULL)
		    return FAIL;
		p = p_dir;
		copy_option_part(&p, dir, MAXPATHL, ",");
	    }
	    swapname = makeswapname(fname, ffname, curbuf, dir);
	    vim_free(dir);
	    r = vim_fexists(swapname);
	    if (r)
	    {
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
		if (p_confirm || (cmdmod.cmod_flags & CMOD_CONFIRM))
		{
		    char_u	buff[DIALOG_MSG_SIZE];

		    dialog_msg(buff,
			    _("Swap file \"%s\" exists, overwrite anyway?"),
								    swapname);
		    if (vim_dialog_yesno(VIM_QUESTION, NULL, buff, 2)
								   != VIM_YES)
		    {
			vim_free(swapname);
			return FAIL;
		    }
		    eap->forceit = TRUE;
		}
		else
#endif
		{
		    semsg(_(e_swap_file_exists_str_silent_overrides), swapname);
		    vim_free(swapname);
		    return FAIL;
		}
	    }
	    vim_free(swapname);
	}
    }
    return OK;
}

// from: src/buffer.c:3606
void
buf_set_name(int fnum, char_u *name)
{
    buf_T	*buf;

    buf = buflist_findnr(fnum);
    if (buf == NULL)
	return;

    if (buf->b_sfname != buf->b_ffname)
	vim_free(buf->b_sfname);
    vim_free(buf->b_ffname);
    buf->b_ffname = vim_strsave(name);
    buf->b_sfname = NULL;
    // Allocate ffname and expand into full path.  Also resolves .lnk
    // files on Win32.
    fname_expand(buf, &buf->b_ffname, &buf->b_sfname);
    buf->b_fname = buf->b_sfname;
}

// from: src/ex_docmd.c:9813
void
dialog_msg(char_u *buff, char *format, char_u *fname)
{
    if (fname == NULL)
	fname = (char_u *)_("Untitled");
    vim_snprintf((char *)buff, DIALOG_MSG_SIZE, format, fname);
}

// from: src/buffer.c:5390
void
fname_expand(
    buf_T	*buf,
    char_u	**ffname,
    char_u	**sfname)
{
    if (*ffname == NULL)
	return;
    if (*sfname == NULL)
	*sfname = *ffname;
    *ffname = fix_fname(*ffname);
}

// from: src/buffer.c:5345
char_u *
fix_fname(char_u *fname)
{
#ifdef UNIX
    return FullName_save(fname, TRUE);
#else
    if (!vim_isAbsName(fname)
	    || strstr((char *)fname, "..") != NULL
	    || strstr((char *)fname, "//") != NULL
	    )
	return FullName_save(fname, FALSE);

    fname = vim_strsave(fname);
    return fname;
#endif
}

// from: src/filepath.c:3146
char_u *
FullName_save(
    char_u	*fname,
    int		force)
{
    char_u	*buf;
    char_u	*new_fname = NULL;

    if (fname == NULL)
	return NULL;

    buf = alloc(MAXPATHL);
    if (buf == NULL)
	return NULL;

    if (vim_FullName(fname, buf, MAXPATHL, force) != FAIL)
	new_fname = vim_strsave(buf);
    else
	new_fname = vim_strsave(fname);
    vim_free(buf);
    return new_fname;
}

// from: src/filepath.c:4302
int
vim_isAbsName(char_u *name)
{
    return (path_with_url(name) != 0 || mch_isFullName(name));
}

// from: src/misc1.c:2733
int
path_with_url(char_u *fname)
{
    char_u *p;

    if (!ASCII_ISALPHA(*fname))
	return 0;

    for (p = fname + 1; (ASCII_ISALPHA(*p) || (*p == '-')); ++p)
	;

    if (*p == ':' && p[1] == '/' && p[2] == '/')
	return (*p == ':' && p[1] == '/' && p[2] == '/');

    return 0;
}

// from: src/os_unix.c:2828
int
mch_isFullName(char_u *fname)
{
    return (*fname == '/' || *fname == '~');
}

// from: src/filepath.c:4313
int
vim_FullName(
    char_u	*fname,
    char_u	*buf,
    int		len,
    int		force)
{
    int		retval = OK;

    *buf = NUL;
    if (fname == NULL)
	return FAIL;

    if (!force && mch_isFullName(fname))
    {
	if ((int)STRLEN(fname) >= len)
	    return FAIL;
	STRCPY(buf, fname);
	return OK;
    }

    retval = FAIL;
    return retval;
}

// from: src/ex_cmds2.c:159
void
dialog_changed(
    buf_T	*buf,
    int		checkall)	// may abandon all changed buffers
{
    char_u	buff[DIALOG_MSG_SIZE];
    int		ret;
    buf_T	*buf2;
    exarg_T	ea;

    dialog_msg(buff, _("Save changes to \"%s\"?"), buf->b_fname);
    if (checkall)
	ret = vim_dialog_yesnoallcancel(VIM_QUESTION, NULL, buff, 1);
    else
	ret = vim_dialog_yesnocancel(VIM_QUESTION, NULL, buff, 1);

    // Init ea pseudo-structure, this is needed for the check_overwrite()
    // function.
    CLEAR_FIELD(ea);

    if (ret == VIM_YES)
    {
	int	empty_bufname;

#ifdef FEAT_BROWSE
	// May get file name, when there is none
	browse_save_fname(buf);
#endif
	empty_bufname = buf->b_fname == NULL ? TRUE : FALSE;
	if (empty_bufname)
	    buf_set_name(buf->b_fnum, (char_u *)"Untitled");

	if (check_overwrite(&ea, buf, buf->b_fname, buf->b_ffname, FALSE) == OK)
	{
	    // didn't hit Cancel
	    if (buf_write_all(buf, FALSE) == OK)
		return;
	}

	// restore to empty when write failed
	if (empty_bufname)
	{
		if (buf->b_sfname != buf->b_ffname)
		VIM_CLEAR(buf->b_sfname);
	    buf->b_fname = NULL;
	    VIM_CLEAR(buf->b_ffname);
	    unchanged(buf, TRUE, FALSE);
	}
    }
    else if (ret == VIM_NO)
    {
	unchanged(buf, TRUE, FALSE);
    }
    else if (ret == VIM_ALL)
    {
	/*
	 * Write all modified files that can be written.
	 * Skip readonly buffers, these need to be confirmed
	 * individually.
	 */
	FOR_ALL_BUFFERS(buf2)
	{
	    if (bufIsChanged(buf2)
		    && (buf2->b_ffname != NULL
#ifdef FEAT_BROWSE
			|| (cmdmod.cmod_flags & CMOD_BROWSE)
#endif
			)
		    && !bt_dontwrite(buf2)
		    && !buf2->b_p_ro)
	    {
		bufref_T bufref;

		set_bufref(&bufref, buf2);
#ifdef FEAT_BROWSE
		// May get file name, when there is none
		browse_save_fname(buf2);
#endif
		if (buf2->b_fname != NULL && check_overwrite(&ea, buf2,
				  buf2->b_fname, buf2->b_ffname, FALSE) == OK)
		    // didn't hit Cancel
		    (void)buf_write_all(buf2, FALSE);

		// an autocommand may have deleted the buffer
		if (!bufref_valid(&bufref))
		    buf2 = firstbuf;
	    }
	}
    }
    else if (ret == VIM_DISCARDALL)
    {
	/*
	 * mark all buffers as unchanged
	 */
	FOR_ALL_BUFFERS(buf2)
	    unchanged(buf2, TRUE, FALSE);
    }
}
