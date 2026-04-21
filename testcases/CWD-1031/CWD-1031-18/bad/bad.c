#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

typedef unsigned char	char_u;
typedef long		linenr_T;
typedef int		colnr_T;
typedef char		schar_T;
typedef unsigned short	sattr_T;
typedef unsigned short	short_u;
typedef unsigned int	u8char_T;
typedef long            blocknr_T;
typedef int		int_T;
typedef unsigned int	UINT32_TYPEDEF;
typedef long            time_T;
typedef off_t           off_T;
typedef long long_T;
typedef long_T          varnumber_T;

typedef int		guicolor_T;
#define INVALCOLOR ((guicolor_T)0x1ffffff)
#define CTERMCOLOR ((guicolor_T)0x1fffffe)

typedef struct window_S		win_T;
typedef struct wininfo_S	wininfo_T;
typedef struct frame_S		frame_T;
typedef int			scid_T;
typedef struct file_buffer	buf_T;
typedef struct terminal_S	term_T;
typedef struct tabpage_S	tabpage_T;

#define EXTERN extern

#define TRUE    1
#define FALSE   0

#define OK              1
#define FAIL            0
#define NOTDONE         2

typedef struct growarray
{
    int	    ga_len;
    int	    ga_maxlen;
    int	    ga_itemsize;
    int	    ga_growsize;
    void    *ga_data;
} garray_T;

#define GA_EMPTY    {0, 0, 0, 0, NULL}

typedef struct
{
    linenr_T	lnum;
    colnr_T	col;
    colnr_T	coladd;
} pos_T;

typedef struct
{
    linenr_T	lnum;
    colnr_T	col;
} lpos_T;

typedef struct {
    buf_T   *br_buf;
    int	    br_fnum;
    int	    br_buf_free_count;
} bufref_T;

typedef struct
{
    pos_T	vi_start;
    pos_T	vi_end;
    int		vi_mode;
    colnr_T	vi_curswant;
} visualinfo_T;

typedef struct foldinfo
{
    int		fi_level;
    int		fi_lnum;
    int		fi_low_level;
} foldinfo_T;

typedef struct synblock_S
{
    int dummy;
} synblock_T;

typedef struct winopt_S
{
    int dummy;
} winopt_T;

typedef struct memfile	    memfile_T;
typedef struct block_hdr    bhdr_T;

typedef struct memline
{
    linenr_T	ml_line_count;
    memfile_T	*ml_mfp;
    void	*ml_stack;
    int		ml_stack_top;
    int		ml_stack_size;
    int		ml_flags;
    colnr_T	ml_line_len;
    linenr_T	ml_line_lnum;
    char_u	*ml_line_ptr;
    bhdr_T	*ml_locked;
    linenr_T	ml_locked_low;
    linenr_T	ml_locked_high;
    int		ml_locked_lineadd;
} memline_T;

typedef struct {
    char_u	*ul_line;
    long	ul_len;
} undoline_T;

typedef struct u_entry u_entry_T;
typedef struct u_header u_header_T;

struct u_header
{
    union {
	u_header_T *ptr;
	long	   seq;
    } uh_next;
    union {
	u_header_T *ptr;
	long	   seq;
    } uh_prev;
    union {
	u_header_T *ptr;
	long	   seq;
    } uh_alt_next;
    union {
	u_header_T *ptr;
	long	   seq;
    } uh_alt_prev;
    long	uh_seq;
    int		uh_walk;
    u_entry_T	*uh_entry;
    u_entry_T	*uh_getbot_entry;
    pos_T	uh_cursor;
    long	uh_cursor_vcol;
    int		uh_flags;
    pos_T	uh_namedm[28];
    visualinfo_T uh_visual;
    time_T	uh_time;
    long	uh_save_nr;
};

struct wininfo_S
{
    wininfo_T	*wi_next;
    wininfo_T	*wi_prev;
    win_T	*wi_win;
    pos_T	wi_fpos;
    int		wi_optset;
    winopt_T	wi_opt;
#ifdef FEAT_FOLDING
    int		wi_fold_manual;
    garray_T	wi_folds;
#endif
};

typedef struct w_line
{
    linenr_T	wl_lnum;
    short_u	wl_size;
    char	wl_valid;
#ifdef FEAT_FOLDING
    char	wl_folded;
    linenr_T	wl_lastlnum;
#endif
} wline_T;

struct frame_S
{
    char	fr_layout;
    int		fr_width;
    int		fr_newwidth;
    int		fr_height;
    int		fr_newheight;
    frame_T	*fr_parent;
    frame_T	*fr_next;
    frame_T	*fr_prev;
    frame_T	*fr_child;
    win_T	*fr_win;
};

#define FR_LEAF	0
#define FR_ROW	1
#define FR_COL	2

struct window_S
{
    int		w_id;
    buf_T	*w_buffer;
    win_T	*w_prev;
    win_T	*w_next;
#if defined(FEAT_SYN_HL) || defined(FEAT_SPELL)
    synblock_T	*w_s;
#endif
    int		w_closing;
    frame_T	*w_frame;
    pos_T	w_cursor;
    colnr_T	w_curswant;
    int		w_set_curswant;
#ifdef FEAT_SYN_HL
    linenr_T	w_last_cursorline;
#endif
    char	w_old_visual_mode;
    linenr_T	w_old_cursor_lnum;
    colnr_T	w_old_cursor_fcol;
    colnr_T	w_old_cursor_lcol;
    linenr_T	w_old_visual_lnum;
    colnr_T	w_old_visual_col;
    colnr_T	w_old_curswant;
    linenr_T	w_topline;
    char	w_topline_was_set;
    linenr_T	w_botline;
#ifdef FEAT_DIFF
    int		w_topfill;
    int		w_old_topfill;
    int		w_botfill;
    int		w_old_botfill;
#endif
    colnr_T	w_leftcol;
    colnr_T	w_skipcol;
    int		w_empty_rows;
#ifdef FEAT_DIFF
    int		w_filler_rows;
#endif
    int		w_winrow;
    int		w_height;
    int		w_status_height;
    int		w_wincol;
    int		w_width;
    int		w_vsep_width;
    void	*w_save_cursor;
#ifdef FEAT_PROP_POPUP
    int		w_popup_flags;
    int		w_popup_handled;
    char_u	*w_popup_title;
    void	*w_popup_pos;
    int		w_popup_fixed;
    int		w_popup_prop_type;
    win_T	*w_popup_prop_win;
    int		w_popup_prop_id;
    int		w_zindex;
    int		w_minheight;
    int		w_minwidth;
    int		w_maxheight;
    int		w_maxwidth;
    int		w_maxwidth_opt;
    int		w_wantline;
    int		w_wantcol;
    int		w_firstline;
    int		w_want_scrollbar;
    int		w_has_scrollbar;
    char_u	*w_scrollbar_highlight;
    char_u	*w_thumb_highlight;
    int		w_popup_padding[4];
    int		w_popup_border[4];
    char_u	*w_border_highlight[4];
    int		w_border_char[8];
    int		w_popup_leftoff;
    int		w_popup_rightoff;
    varnumber_T	w_popup_last_changedtick;
    varnumber_T	w_popup_prop_changedtick;
    int		w_popup_prop_topline;
    linenr_T	w_popup_last_curline;
    void	*w_close_cb;
    void	*w_filter_cb;
    int		w_filter_errors;
    int		w_filter_mode;
    win_T	*w_popup_curwin;
    linenr_T	w_popup_lnum;
    colnr_T	w_popup_mincol;
    colnr_T	w_popup_maxcol;
    int		w_popup_mouse_row;
    int		w_popup_mouse_mincol;
    int		w_popup_mouse_maxcol;
    int		w_popup_close;
    void	*w_popup_mask;
    char_u	*w_popup_mask_cells;
    int		w_popup_mask_height;
    int		w_popup_mask_width;
# ifdef FEAT_TIMERS
    void	*w_popup_timer;
# endif
    int		w_flags;
#endif
    int		w_valid;
    pos_T	w_valid_cursor;
    colnr_T	w_valid_leftcol;
    int		w_cline_height;
#ifdef FEAT_FOLDING
    int		w_cline_folded;
#endif
    int		w_cline_row;
    colnr_T	w_virtcol;
    int		w_wrow, w_wcol;
    int		w_lines_valid;
    wline_T	*w_lines;
#ifdef FEAT_FOLDING
    garray_T	w_folds;
    char	w_fold_manual;
    char	w_foldinvalid;
#endif
#ifdef FEAT_LINEBREAK
    int		w_nrwidth;
#endif
    int		w_redr_type;
    int		w_upd_rows;
    linenr_T	w_redraw_top;
    linenr_T	w_redraw_bot;
    int		w_redr_status;
#ifdef FEAT_CMDL_INFO
    pos_T	w_ru_cursor;
    colnr_T	w_ru_virtcol;
    linenr_T	w_ru_topline;
    linenr_T	w_ru_line_count;
# ifdef FEAT_DIFF
    int		w_ru_topfill;
# endif
    char	w_ru_empty;
#endif
    int		w_alt_fnum;
    void	*w_alist;
    int		w_arg_idx;
    int		w_arg_idx_invalid;
    char_u	*w_localdir;
    char_u	*w_prevdir;
#ifdef FEAT_MENU
    void	*w_winbar;
    void	*w_winbar_items;
    int		w_winbar_height;
#endif
    winopt_T	w_onebuf_opt;
    winopt_T	w_allbuf_opt;
#ifdef FEAT_STL_OPT
    long_u	w_p_stl_flags;
#endif
};

typedef unsigned long long_u;

struct tabpage_S
{
    int		tp_local_locked;
    int		tp_locked;
    tabpage_T *tp_next;
    tabpage_T *tp_prev;
    win_T	*tp_firstwin;
    win_T	*tp_lastwin;
    win_T	*tp_curwin;
    win_T	*tp_prevwin;
    win_T	*tp_first_popupwin;
    int		tp_topnr;
    int		tp_prev_topnr;
    int		tp_firstwin_nr;
    frame_T	*tp_firstframe;
    frame_T	*tp_topframe;
    long	tp_old_Rows;
    long	tp_old_Columns;
    long	tp_ch_used;
#ifdef FEAT_GUI
    int		tp_prev_which_scrollbars[3];
#endif
    char_u	*tp_localdir;
    char_u	*tp_prevdir;
#ifdef FEAT_DIFF
    void	*tp_first_diff;
    buf_T	*(tp_diffbuf[8]);
    int		tp_diff_invalid;
    int		tp_diff_update;
#endif
    frame_T	*(tp_snapshot[2]);
#ifdef FEAT_EVAL
    void	*tp_winvar;
    void	*tp_vars;
#endif
#ifdef FEAT_PYTHON
    void	*tp_python_ref;
#endif
#ifdef FEAT_PYTHON3
    void	*tp_python3_ref;
#endif
};

struct file_buffer
{
    memline_T	b_ml;
    buf_T	*b_next;
    buf_T	*b_prev;
    int		b_nwindows;
    int		b_flags;
    int		b_locked;
    char_u	*b_ffname;
    char_u	*b_sfname;
    char_u	*b_fname;
#ifdef UNIX
    int		b_dev_valid;
    void	b_dev;
    void	b_ino;
#endif
#ifdef VMS
    char	 b_fab_rfm;
    char	 b_fab_rat;
    unsigned int b_fab_mrs;
#endif
    int		b_fnum;
    char_u	b_key[33];
    int		b_changed;
    varnumber_T	b_ct_di;
    varnumber_T	b_last_changedtick;
    varnumber_T	b_last_changedtick_pum;
    int		b_saving;
    int		b_mod_set;
    linenr_T	b_mod_top;
    linenr_T	b_mod_bot;
    long	b_mod_xlines;
    wininfo_T	*b_wininfo;
    long	b_mtime;
    long	b_mtime_read;
    off_T	b_orig_size;
    int		b_orig_mode;
#ifdef FEAT_VIMINFO
    time_T	b_last_used;
#endif
    pos_T	b_namedm[28];
    visualinfo_T b_visual;
#ifdef FEAT_EVAL
    int		b_visual_mode_eval;
#endif
    pos_T	b_last_cursor;
    pos_T	b_last_insert;
    pos_T	b_last_change;
#ifdef FEAT_JUMPLIST
    pos_T	b_changelist[100];
    int		b_changelistlen;
    int		b_new_change;
#endif
    char_u	b_chartab[32];
    void	*(b_maphash[256]);
    void	*b_first_abbr;
    garray_T	b_ucmds;
    pos_T	b_op_start;
    pos_T	b_op_start_orig;
    pos_T	b_op_end;
#ifdef FEAT_VIMINFO
    int		b_marks_read;
#endif
    u_header_T	*b_u_oldhead;
    u_header_T	*b_u_newhead;
    u_header_T	*b_u_curhead;
    int		b_u_numhead;
    int		b_u_synced;
    long	b_u_seq_last;
    long	b_u_save_nr_last;
    long	b_u_seq_cur;
    time_T	b_u_time_cur;
    long	b_u_save_nr_cur;
    undoline_T	b_u_line_ptr;
    linenr_T	b_u_line_lnum;
    colnr_T	b_u_line_colnr;
    int		b_scanned;
    long	b_p_iminsert;
    long	b_p_imsearch;
#define B_IMODE_USE_INSERT -1
#define B_IMODE_NONE 0
#define B_IMODE_LMAP 1
#define B_IMODE_IM 2
#define B_IMODE_LAST 2
#ifdef FEAT_KEYMAP
    short	b_kmap_state;
    garray_T	b_kmap_ga;
#endif
    int		b_p_initialized;
#ifdef FEAT_EVAL
    void	b_p_script_ctx[65];
#endif
#ifdef FEAT_SYN_HL
    synblock_T b_s;
#endif
    int         b_help;
    int		b_p_ai;
    int		b_p_ai_nopaste;
    char_u	*b_p_bkc;
    unsigned	b_bkc_flags;
    int		b_p_ci;
    int		b_p_bin;
    int		b_p_bomb;
    char_u	*b_p_bh;
    char_u	*b_p_bt;
#ifdef FEAT_QUICKFIX
    int		b_has_qf_entry;
#endif
    int		b_p_bl;
#ifdef FEAT_CINDENT
    int		b_p_cin;
    char_u	*b_p_cino;
    char_u	*b_p_cink;
#endif
#if defined(FEAT_CINDENT) || defined(FEAT_SMARTINDENT)
    char_u	*b_p_cinw;
#endif
    char_u	*b_p_com;
#ifdef FEAT_FOLDING
    char_u	*b_p_cms;
#endif
    char_u	*b_p_cpt;
#ifdef BACKSLASH_IN_FILENAME
    char_u	*b_p_csl;
#endif
#ifdef FEAT_COMPL_FUNC
    char_u	*b_p_cfu;
    char_u	*b_p_ofu;
#endif
#ifdef FEAT_EVAL
    char_u	*b_p_tfu;
#endif
    int		b_p_eol;
    int		b_p_fixeol;
    int		b_p_et;
    int		b_p_et_nobin;
    int		b_p_et_nopaste;
    char_u	*b_p_fenc;
    char_u	*b_p_ff;
    char_u	*b_p_ft;
    char_u	*b_p_fo;
    char_u	*b_p_flp;
    int		b_p_inf;
    char_u	*b_p_isk;
#ifdef FEAT_FIND_ID
    char_u	*b_p_def;
    char_u	*b_p_inc;
# ifdef FEAT_EVAL
    char_u	*b_p_inex;
    long_u	b_p_inex_flags;
# endif
#endif
#if defined(FEAT_CINDENT) && defined(FEAT_EVAL)
    char_u	*b_p_inde;
    long_u	b_p_inde_flags;
    char_u	*b_p_indk;
#endif
    char_u	*b_p_fp;
#if defined(FEAT_EVAL)
    char_u	*b_p_fex;
    long_u	b_p_fex_flags;
#endif
#ifdef FEAT_CRYPT
    char_u	*b_p_key;
#endif
    char_u	*b_p_kp;
#ifdef FEAT_LISP
    int		b_p_lisp;
#endif
    char_u	*b_p_menc;
    char_u	*b_p_mps;
    int		b_p_ml;
    int		b_p_ml_nobin;
    int		b_p_ma;
    char_u	*b_p_nf;
    int		b_p_pi;
#ifdef FEAT_TEXTOBJ
    char_u	*b_p_qe;
#endif
    int		b_p_ro;
    long	b_p_sw;
    int		b_p_sn;
#ifdef FEAT_SMARTINDENT
    int		b_p_si;
#endif
    long	b_p_sts;
    long	b_p_sts_nopaste;
#ifdef FEAT_SEARCHPATH
    char_u	*b_p_sua;
#endif
    int		b_p_swf;
#ifdef FEAT_SYN_HL
    long	b_p_smc;
    char_u	*b_p_syn;
#endif
    long	b_p_ts;
    int		b_p_tx;
    long	b_p_tw;
    long	b_p_tw_nobin;
    long	b_p_tw_nopaste;
    long	b_p_wm;
    long	b_p_wm_nobin;
    long	b_p_wm_nopaste;
#ifdef FEAT_VARTABS
    char_u	*b_p_vsts;
    int		*b_p_vsts_array;
    char_u	*b_p_vsts_nopaste;
    char_u	*b_p_vts;
#endif
    char_u	*b_p_ww;
    char_u	*b_p_keymap;
    int		b_p_lbr;
    int		b_p_list;
    int		b_p_nu;
    int		b_p_rnu;
    colnr_T	b_p_ts_nopaste;
#ifdef FEAT_FOLDING
    int		b_p_fen;
    int		b_p_fen_save;
    char_u	*b_p_fdi;
    char_u	*b_p_fdm;
    char_u	*b_p_fdn;
    char_u	*b_p_fml;
    long	b_p_fmr;
    char_u	*b_p_fdt;
    int		b_p_mfd;
    char_u	*b_p_fdm_expr;
    char_u	*b_p_fdm_syntax;
#endif
#ifdef FEAT_CRYPT
    void	*b_crypt_state;
#endif
#ifdef FEAT_PROP_POPUP
    void	*b_prop_types;
    int		b_next_prop_type_id;
    int		b_text_prop_count;
#endif
    term_T	*b_term;
#ifdef FEAT_DIFF
    int		b_diff_failed;
#endif
};

struct terminal_S
{
    int		trivial;
};

typedef enum auto_event
{
    EVENT_NONE = 0,
    EVENT_BUFADD,
    EVENT_BUFDELETE,
    EVENT_BUFENTER,
    EVENT_BIFF,
    EVENT_BUFHIDDEN,
    EVENT_BUFLEAVE,
    EVENT_BUFMODIFIEDSET,
    EVENT_BUFNEW,
    EVENT_BUFNEWFILE,
    EVENT_BUFREADCMD,
    EVENT_BUFREADPOST,
    EVENT_BUFREADPRE,
    EVENT_BUFUNLOAD,
    EVENT_BUFWIPEOUT,
    EVENT_BUFWINENTER,
    EVENT_BUFWINLEAVE,
    EVENT_BUFWRITECMD,
    EVENT_BUFWRITEPOST,
    EVENT_BUFWRITEPRE,
    EVENT_COUNT
} event_T;

#define DOBUF_GOTO	0
#define DOBUF_SPLIT	1
#define DOBUF_UNLOAD	2
#define DOBUF_DEL	3
#define DOBUF_WIPE	4
#define DOBUF_WIPE_REUSE 5

#define DOBUF_CURRENT	0
#define DOBUF_FIRST	1
#define DOBUF_LAST	2
#define DOBUF_MOD	3

#define BF_RECOVERED	0x01
#define BF_CHECK_RO	0x02
#define BF_NEVERLOADED	0x04
#define BF_NOTEDITED	0x08
#define BF_NEW		0x10
#define BF_NEW_W	0x20
#define BF_READERR	0x40
#define BF_DUMMY	0x80
#define BF_PRESERVED	0x100
#define BF_SYN_SET	0x200
#define BF_NO_SEA	0x400
#define BF_WRITE_MASK	(BF_NOTEDITED + BF_NEW + BF_READERR)

#define BFA_DEL		 1
#define BFA_WIPE	 2
#define BFA_KEEP_UNDO	 4
#define BFA_IGNORE_ABORT 8

#define SWB_USEOPEN		0x001
#define SWB_USETAB		0x002
#define SWB_SPLIT		0x004
#define SWB_NEWTAB		0x008
#define SWB_VSPLIT		0x010
#define SWB_USELAST		0x020

#define FORWARD		 1
#define BACKWARD	(-1)

EXTERN win_T	*firstwin;
EXTERN win_T	*lastwin;
EXTERN win_T	*curwin;
EXTERN win_T	*prevwin;
EXTERN win_T	*aucmd_win;
EXTERN int	aucmd_win_used;

EXTERN tabpage_T    *first_tabpage;
EXTERN tabpage_T    *curtab;
EXTERN tabpage_T    *lastused_tabpage;

EXTERN buf_T	*firstbuf;
EXTERN buf_T	*lastbuf;
EXTERN buf_T	*curbuf;

EXTERN bufref_T	au_new_curbuf;
EXTERN buf_T	*au_pending_free_buf;
EXTERN win_T	*au_pending_free_win;

EXTERN int	autocmd_busy;
EXTERN unsigned	swb_flags;

EXTERN int	VIsual_active;
EXTERN int	VIsual_reselect;
EXTERN char	VIsual_mode;

EXTERN frame_T	*topframe;

#ifdef FEAT_PROP_POPUP
EXTERN win_T    *first_popupwin;
EXTERN int	popup_visible;
#endif

#define ONE_WINDOW (firstwin == lastwin)
#define FOR_ALL_BUFFERS(buf) \
    for ((buf) = firstbuf; (buf) != NULL; (buf) = (buf)->b_next)
#define FOR_ALL_WINDOWS(wp) for (wp = firstwin; wp != NULL; wp = wp->w_next)

#define CHECK_CURBUF

#ifdef ABORT_ON_INTERNAL_ERROR
# define CHECK_CURBUF_ACTIVE if (curwin != NULL && curwin->w_buffer != curbuf) \
	iemsg("curbuf != curwin->w_buffer")
#else
# define CHECK_CURBUF_ACTIVE
#endif

#define VIM_CLEAR(p) \
    do { \
	if ((p) != NULL) { \
	    vim_free(p); \
	    (p) = NULL; \
	} \
    } while (0)

#define GA_GROW(gap, n) (((gap)->ga_maxlen - (gap)->ga_len < n) ? ga_grow_inner((gap), (n)) : 1)

#define _(x) (x)
#define N_(x) (x)

static const char *e_auabort = "E855: Autocommands deleted the buffer";
static const char *e_nobufnr = "E86: Buffer %ld does not exist";

typedef struct {
    int cmod_flags;
} cmdmod_T;

#define CMOD_KEEPALT 0x01

EXTERN cmdmod_T cmdmod;

void vim_free(void *x);
int ga_grow(garray_T *gap, int n);
int ga_grow_inner(garray_T *gap, int n);
void ga_init2(garray_T *gap, int itemsize, int growsize);

void set_bufref(bufref_T *bufref, buf_T *buf);
int bufref_valid(bufref_T *bufref);
int buf_valid(buf_T *buf);
void close_buffer(win_T *win, buf_T *buf, int action, int abort_if_last, int ignore_abort);
void buf_clear_file(buf_T *buf);
void buf_freeall(buf_T *buf, int flags);
void free_wininfo(wininfo_T *wip);
int do_buffer(int action, int start, int dir, int count, int forceit);
void set_curbuf(buf_T *buf, int action);
int one_window(void);
int win_valid(win_T *win);
int win_valid_any_tab(win_T *win);
void end_visual_mode(void);
void set_last_cursor(win_T *win);
void buflist_setfpos(buf_T *buf, win_T *win, linenr_T lnum, colnr_T col, int copy_options);
void close_windows(buf_T *buf, int keep_curwin);
void goto_tabpage_win(tabpage_T *tp, win_T *wp);
void block_autocmds(void);
void unblock_autocmds(void);
int apply_autocmds(event_T event, char_u *fname, char_u *fname_io, int force, buf_T *buf);
int aborting(void);
void vim_beep(void);
int bt_terminal(buf_T *buf);
void free_terminal(buf_T *buf);
int term_job_running(term_T *term);
int can_unload_buffer(buf_T *buf);
int empty_curbuf(int close_curwin, int forceit, int action);
void free_buffer(buf_T *buf);
void free_buffer_stuff(buf_T *buf, int free_options);
int buf_hide(buf_T *buf);
int bufIsChanged(buf_T *buf);
void reset_synblock(win_T *wp);
void u_sync(int force);
void ex_winresizer(void);
int diffopt_hiddenoff(void);
void diff_buf_delete(buf_T *buf);
void setpcmark(void);
void buflist_altfpos(win_T *win);
void check_colorcolumn(win_T *wp);
void enter_buffer(buf_T *buf);
int win_close(win_T *win, int free_buf);
buf_T *buflist_findnr(int nr);
int buf_jump_open_win(buf_T *buf);
int buf_jump_open_tab(buf_T *buf);
int win_split(int size, int flags);
int can_abandon(buf_T *buf, int forceit);
void dialog_changed(buf_T *buf, int guess);
void no_write_message(void);
void RESET_BINDING(win_T *wp);

void semsg(const char *fmt, ...);
void iemsg(const char *fmt, ...);
void siemsg(const char *fmt, ...);
void emsg(const char *fmt, ...);
void emsgv(const char *fmt, ...);

win_T	*firstwin = NULL;
win_T	*lastwin = NULL;
win_T	*curwin = NULL;
win_T	*prevwin = NULL;
win_T	*aucmd_win = NULL;
int	aucmd_win_used = 0;

tabpage_T    *first_tabpage = NULL;
tabpage_T    *curtab = NULL;
tabpage_T    *lastused_tabpage = NULL;

buf_T	*firstbuf = NULL;
buf_T	*lastbuf = NULL;
buf_T	*curbuf = NULL;

bufref_T	au_new_curbuf = {NULL, 0, 0};
buf_T	*au_pending_free_buf = NULL;
win_T	*au_pending_free_win = NULL;

int	autocmd_busy = 0;
unsigned	swb_flags = 0;

int	VIsual_active = 0;
int	VIsual_reselect = 0;
char	VIsual_mode = 'v';

frame_T	*topframe = NULL;

#ifdef FEAT_PROP_POPUP
win_T    *first_popupwin = NULL;
int	popup_visible = 0;
#endif

cmdmod_T cmdmod = {0};

static garray_T buf_reuse = GA_EMPTY;

    void
close_buffer(
    win_T	*win,		// if not NULL, set b_last_cursor
    buf_T	*buf,
    int		action,
    int		abort_if_last,
    int		ignore_abort)
{
    int		is_curbuf;
    int		nwindows;
    bufref_T	bufref;
    int		is_curwin = (curwin != NULL && curwin->w_buffer == buf);
    win_T	*the_curwin = curwin;
    tabpage_T	*the_curtab = curtab;
    int		unload_buf = (action != 0);
    int		wipe_buf = (action == DOBUF_WIPE || action == DOBUF_WIPE_REUSE);
    int		del_buf = (action == DOBUF_DEL || wipe_buf);

    CHECK_CURBUF;
    /*
     * Force unloading or deleting when 'bufhidden' says so.
     * The caller must take care of NOT deleting/freeing when 'bufhidden' is
     * "hide" (otherwise we could never free or delete a buffer).
     */
    if (buf->b_p_bh[0] == 'd')		// 'bufhidden' == "delete"
    {
	del_buf = TRUE;
	unload_buf = TRUE;
    }
    else if (buf->b_p_bh[0] == 'w')	// 'bufhidden' == "wipe"
    {
	del_buf = TRUE;
	unload_buf = TRUE;
	wipe_buf = TRUE;
    }
    else if (buf->b_p_bh[0] == 'u')	// 'bufhidden' == "unload"
	unload_buf = TRUE;

#ifdef FEAT_TERMINAL
    if (bt_terminal(buf) && (buf->b_nwindows == 1 || del_buf))
    {
	CHECK_CURBUF;
	if (term_job_running(buf->b_term))
	{
	    if (wipe_buf || unload_buf)
	    {
		if (!can_unload_buffer(buf))
		    return;

		// Wiping out or unloading a terminal buffer kills the job.
		free_terminal(buf);
	    }
	    else
	    {
		// The job keeps running, hide the buffer.
		del_buf = FALSE;
		unload_buf = FALSE;
	    }
	}
	else if (buf->b_p_bh[0] == 'h' && !del_buf)
	{
	    // Hide a terminal buffer.
	    unload_buf = FALSE;
	}
	else
	{
	    // A terminal buffer is wiped out if the job has finished.
	    del_buf = TRUE;
	    unload_buf = TRUE;
	    wipe_buf = TRUE;
	}
	CHECK_CURBUF;
    }
#endif

    // Disallow deleting the buffer when it is locked (already being closed or
    // halfway a command that relies on it). Unloading is allowed.
    if ((del_buf || wipe_buf) && !can_unload_buffer(buf))
	return;

    // check no autocommands closed the window
    if (win != NULL && win_valid_any_tab(win))
    {
	// Set b_last_cursor when closing the last window for the buffer.
	// Remember the last cursor position and window options of the buffer.
	// This used to be only for the current window, but then options like
	// 'foldmethod' may be lost with a ":only" command.
	if (buf->b_nwindows == 1)
	    set_last_cursor(win);
	buflist_setfpos(buf, win,
			win->w_cursor.lnum == 1 ? 0 : win->w_cursor.lnum,
			win->w_cursor.col, TRUE);
    }

    set_bufref(&bufref, buf);

    // When the buffer is no longer in a window, trigger BufWinLeave
    if (buf->b_nwindows == 1)
    {
	++buf->b_locked;
	if (apply_autocmds(EVENT_BUFWINLEAVE, buf->b_fname, buf->b_fname,
								  FALSE, buf)
		&& !bufref_valid(&bufref))
	{
	    // Autocommands deleted the buffer.
aucmd_abort:
	    emsg(_(e_auabort));
	    return;
	}
	--buf->b_locked;
	if (abort_if_last && one_window())
	    // Autocommands made this the only window.
	    goto aucmd_abort;

	// When the buffer becomes hidden, but is not unloaded, trigger
	// BufHidden
	if (!unload_buf)
	{
	    ++buf->b_locked;
	    if (apply_autocmds(EVENT_BUFHIDDEN, buf->b_fname, buf->b_fname,
								  FALSE, buf)
		    && !bufref_valid(&bufref))
		// Autocommands deleted the buffer.
		goto aucmd_abort;
	    --buf->b_locked;
	    if (abort_if_last && one_window())
		// Autocommands made this the only window.
		goto aucmd_abort;
	}
#ifdef FEAT_EVAL
	// autocmds may abort script processing
	if (!ignore_abort && aborting())
	    return;
#endif
    }

    // If the buffer was in curwin and the window has changed, go back to that
    // window, if it still exists.  This avoids that ":edit x" triggering a
    // "tabnext" BufUnload autocmd leaves a window behind without a buffer.
    if (is_curwin && curwin != the_curwin &&  win_valid_any_tab(the_curwin))
    {
	block_autocmds();
	goto_tabpage_win(the_curtab, the_curwin);
	unblock_autocmds();
    }

    nwindows = buf->b_nwindows;

    // decrease the link count from windows (unless not in any window)
    if (buf->b_nwindows > 0)
	--buf->b_nwindows;

#ifdef FEAT_DIFF
    if (diffopt_hiddenoff() && !unload_buf && buf->b_nwindows == 0)
	diff_buf_delete(buf);	// Clear 'diff' for hidden buffer.
#endif

    // Return when a window is displaying the buffer or when it's not
    // unloaded.
    if (buf->b_nwindows > 0 || !unload_buf)
	return;

    // Always remove the buffer when there is no file name.
    if (buf->b_ffname == NULL)
	del_buf = TRUE;

    // When closing the current buffer stop Visual mode before freeing
    // anything.
    if (buf == curbuf && VIsual_active
#if defined(EXITFREE)
	    && !entered_free_all_mem
#endif
	    )
	end_visual_mode();

    /*
     * Free all things allocated for this buffer.
     * Also calls the "BufDelete" autocommands when del_buf is TRUE.
     */
    // Remember if we are closing the current buffer.  Restore the number of
    // windows, so that autocommands in buf_freeall() don't get confused.
    is_curbuf = (buf == curbuf);
    buf->b_nwindows = nwindows;

    buf_freeall(buf, (del_buf ? BFA_DEL : 0)
		       + (wipe_buf ? BFA_WIPE : 0)
		       + (ignore_abort ? BFA_IGNORE_ABORT : 0));

    // Autocommands may have deleted the buffer.
    if (!bufref_valid(&bufref))
	return;
#ifdef FEAT_EVAL
    // autocmds may abort script processing
    if (!ignore_abort && aborting())
	return;
#endif

    /*
     * It's possible that autocommands change curbuf to the one being deleted.
     * This might cause the previous curbuf to be deleted unexpectedly.  But
     * in some cases it's OK to delete the curbuf, because a new one is
     * obtained anyway.  Therefore only return if curbuf changed to the
     * deleted buffer.
     */
    if (buf == curbuf && !is_curbuf)
	return;

    if (win_valid_any_tab(win) && win->w_buffer == buf)
	win->w_buffer = NULL;  // make sure we don't use the buffer now

    // Autocommands may have opened or closed windows for this buffer.
    // Decrement the count for the close we do here.
    if (buf->b_nwindows > 0)
	--buf->b_nwindows;

    /*
     * Remove the buffer from the list.
     */
    if (wipe_buf)
    {
	if (action == DOBUF_WIPE_REUSE)
	{
	    // we can re-use this buffer number, store it
	    if (buf_reuse.ga_itemsize == 0)
		ga_init2(&buf_reuse, sizeof(int), 50);
	    if (ga_grow(&buf_reuse, 1) == OK)
		((int *)buf_reuse.ga_data)[buf_reuse.ga_len++] = buf->b_fnum;
	}
	if (buf->b_sfname != buf->b_ffname)
	    VIM_CLEAR(buf->b_sfname);
	else
	    buf->b_sfname = NULL;
	VIM_CLEAR(buf->b_ffname);
	if (buf->b_prev == NULL)
	    firstbuf = buf->b_next;
	else
	    buf->b_prev->b_next = buf->b_next;
	if (buf->b_next == NULL)
	    lastbuf = buf->b_prev;
	else
	    buf->b_next->b_prev = buf->b_prev;
	free_buffer(buf);
    }
    else
    {
	if (del_buf)
	{
	    // Free all internal variables and reset option values, to make
	    // ":bdel" compatible with Vim 5.7.
	    free_buffer_stuff(buf, TRUE);

	    // Make it look like a new buffer.
	    buf->b_flags = BF_CHECK_RO | BF_NEVERLOADED;

	    // Init the options when loaded again.
	    buf->b_p_initialized = FALSE;
	}
	buf_clear_file(buf);
	if (del_buf)
	    buf->b_p_bl = FALSE;
    }
    // NOTE: at this point "curbuf" may be invalid!
}

    void
set_curbuf(buf_T *buf, int action)
{
    buf_T	*prevbuf;
    int		unload = (action == DOBUF_UNLOAD || action == DOBUF_DEL
			|| action == DOBUF_WIPE || action == DOBUF_WIPE_REUSE);
#ifdef FEAT_SYN_HL
    long	old_tw = curbuf->b_p_tw;
#endif
    bufref_T	newbufref;
    bufref_T	prevbufref;

    setpcmark();
    if ((cmdmod.cmod_flags & CMOD_KEEPALT) == 0)
	curwin->w_alt_fnum = curbuf->b_fnum; // remember alternate file
    buflist_altfpos(curwin);			 // remember curpos

    // Don't restart Select mode after switching to another buffer.
    VIsual_reselect = FALSE;

    // close_windows() or apply_autocmds() may change curbuf and wipe out "buf"
    prevbuf = curbuf;
    set_bufref(&prevbufref, prevbuf);
    set_bufref(&newbufref, buf);

    // Autocommands may delete the current buffer and/or the buffer we want to go
    // to.  In those cases don't close the buffer.
    if (!apply_autocmds(EVENT_BUFLEAVE, NULL, NULL, FALSE, curbuf)
	    || (bufref_valid(&prevbufref)
		&& bufref_valid(&newbufref)
#ifdef FEAT_EVAL
		&& !aborting()
#endif
	       ))
    {
#ifdef FEAT_SYN_HL
	if (prevbuf == curwin->w_buffer)
	    reset_synblock(curwin);
#endif
	if (unload)
	    close_windows(prevbuf, FALSE);
#if defined(FEAT_EVAL)
	if (bufref_valid(&prevbufref) && !aborting())
#else
	if (bufref_valid(&prevbufref))
#endif
	{
	    win_T  *previouswin = curwin;

	    if (prevbuf == curbuf)
		u_sync(FALSE);
	    close_buffer(prevbuf == curwin->w_buffer ? curwin : NULL, prevbuf,
		    unload ? action : (action == DOBUF_GOTO
			&& !buf_hide(prevbuf)
			&& !bufIsChanged(prevbuf)) ? DOBUF_UNLOAD : 0,
		    FALSE, FALSE);
	    if (curwin != previouswin && win_valid(previouswin))
	      // autocommands changed curwin, Grr!
	      curwin = previouswin;
	}
    }
    // An autocommand may have deleted "buf", already entered it (e.g., when
    // it did ":bunload") or aborted the script processing.
    // If curwin->w_buffer is null, enter_buffer() will make it valid again
    if ((buf_valid(buf) && buf != curbuf
#ifdef FEAT_EVAL
		&& !aborting()
#endif
	) || curwin->w_buffer == NULL)
    {
	enter_buffer(buf);
#ifdef FEAT_SYN_HL
	if (old_tw != curbuf->b_p_tw)
	    check_colorcolumn(curwin);
#endif
    }
}

    int
do_buffer(
    int		action,
    int		start,
    int		dir,		// FORWARD or BACKWARD
    int		count,		// buffer number or number of buffers
    int		forceit)	// TRUE for :...!
{
    buf_T	*buf;
    buf_T	*bp;
    int		unload = (action == DOBUF_UNLOAD || action == DOBUF_DEL
			|| action == DOBUF_WIPE || action == DOBUF_WIPE_REUSE);

    switch (start)
    {
	case DOBUF_FIRST:   buf = firstbuf; break;
	case DOBUF_LAST:    buf = lastbuf;  break;
	default:	    buf = curbuf;   break;
    }
    if (start == DOBUF_MOD)	    // find next modified buffer
    {
	while (count-- > 0)
	{
	    do
	    {
		buf = buf->b_next;
		if (buf == NULL)
		    buf = firstbuf;
	    }
	    while (buf != curbuf && !bufIsChanged(buf));
	}
	if (!bufIsChanged(buf))
	{
	    emsg(_("E84: No modified buffer found"));
	    return FAIL;
	}
    }
    else if (start == DOBUF_FIRST && count) // find specified buffer number
    {
	while (buf != NULL && buf->b_fnum != count)
	    buf = buf->b_next;
    }
    else
    {
	bp = NULL;
	while (count > 0 || (!unload && !buf->b_p_bl && bp != buf))
	{
	    // remember the buffer where we start, we come back there when all
	    // buffers are unlisted.
	    if (bp == NULL)
		bp = buf;
	    if (dir == FORWARD)
	    {
		buf = buf->b_next;
		if (buf == NULL)
		    buf = firstbuf;
	    }
	    else
	    {
		buf = buf->b_prev;
		if (buf == NULL)
		    buf = lastbuf;
	    }
	    // don't count unlisted buffers
	    if (unload || buf->b_p_bl)
	    {
		 --count;
		 bp = NULL;	// use this buffer as new starting point
	    }
	    if (bp == buf)
	    {
		// back where we started, didn't find anything.
		emsg(_("E85: There is no listed buffer"));
		return FAIL;
	    }
	}
    }

    if (buf == NULL)	    // could not find it
    {
	if (start == DOBUF_FIRST)
	{
	    // don't warn when deleting
	    if (!unload)
		semsg(_(e_nobufnr), count);
	}
	else if (dir == FORWARD)
	    emsg(_("E87: Cannot go beyond last buffer"));
	else
	    emsg(_("E88: Cannot go before first buffer"));
	return FAIL;
    }

#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif

    /*
     * delete buffer buf from memory and/or the list
     */
    if (unload)
    {
	int	forward;
	bufref_T bufref;

	if (!can_unload_buffer(buf))
	    return FAIL;

	set_bufref(&bufref, buf);

	// When unloading or deleting a buffer that's already unloaded and
	// unlisted: fail silently.
	if (action != DOBUF_WIPE && action != DOBUF_WIPE_REUSE
					   && buf->b_ml.ml_mfp == NULL && !buf->b_p_bl)
	    return FAIL;

	if (!forceit && bufIsChanged(buf))
	{
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
	    if ((p_confirm || (cmdmod.cmod_flags & CMOD_CONFIRM)) && p_write)
	    {
		dialog_changed(buf, FALSE);
		if (!bufref_valid(&bufref))
		    // Autocommand deleted buffer, oops! It's not changed
		    // now.
		    return FAIL;
		// If it's still changed fail silently, the dialog already
		// mentioned why it fails.
		if (bufIsChanged(buf))
		    return FAIL;
	    }
	    else
#endif
	    {
		semsg(_("E89: No write since last change for buffer %d (add ! to override)"),
								     buf->b_fnum);
		return FAIL;
	    }
	}

	// When closing the current buffer stop Visual mode.
	if (buf == curbuf && VIsual_active)
	    end_visual_mode();

	/*
	 * If deleting the last (listed) buffer, make it empty.
	 * The last (listed) buffer cannot be unloaded.
	 */
	FOR_ALL_BUFFERS(bp)
	    if (bp->b_p_bl && bp != buf)
		break;
	if (bp == NULL && buf == curbuf)
	    return empty_curbuf(TRUE, forceit, action);

	/*
	 * If the deleted buffer is the current one, close the current window
	 * (unless it's the only window).  Repeat this so long as we end up in
	 * a window with this buffer.
	 */
	while (buf == curbuf
		   && !(curwin->w_closing || curwin->w_buffer->b_locked > 0)
		   && (!ONE_WINDOW || first_tabpage->tp_next != NULL))
	{
	    if (win_close(curwin, FALSE) == FAIL)
		break;
	}

	/*
	 * If the buffer to be deleted is not the current one, delete it here.
	 */
	if (buf != curbuf)
	{
	    close_windows(buf, FALSE);
	    if (buf != curbuf && bufref_valid(&bufref) && buf->b_nwindows <= 0)
		    close_buffer(NULL, buf, action, FALSE, FALSE);
	    return OK;
	}

	/*
	 * Deleting the current buffer: Need to find another buffer to go to.
	 * There should be another, otherwise it would have been handled
	 * above.  However, autocommands may have deleted all buffers.
	 * First use au_new_curbuf.br_buf, if it is valid.
	 * Then prefer the buffer we most recently visited.
	 * Else try to find one that is loaded, after the current buffer,
	 * then before the current buffer.
	 * Finally use any buffer.
	 */
	buf = NULL;	// selected buffer
	bp = NULL;	// used when no loaded buffer found
	if (au_new_curbuf.br_buf != NULL && bufref_valid(&au_new_curbuf))
	    buf = au_new_curbuf.br_buf;
#ifdef FEAT_JUMPLIST
	else if (curwin->w_jumplistlen > 0)
	{
	    int     jumpidx;

	    jumpidx = curwin->w_jumplistidx - 1;
	    if (jumpidx < 0)
		jumpidx = curwin->w_jumplistlen - 1;

	    forward = jumpidx;
	    while (jumpidx != curwin->w_jumplistidx)
	    {
		buf = buflist_findnr(curwin->w_jumplist[jumpidx].fmark.fnum);
		if (buf != NULL)
		{
		    if (buf == curbuf || !buf->b_p_bl)
			buf = NULL;	// skip current and unlisted bufs
		    else if (buf->b_ml.ml_mfp == NULL)
		    {
			// skip unloaded buf, but may keep it for later
			if (bp == NULL)
			    bp = buf;
			buf = NULL;
		    }
		}
		if (buf != NULL)   // found a valid buffer: stop searching
		    break;
		// advance to older entry in jump list
		if (!jumpidx && curwin->w_jumplistidx == curwin->w_jumplistlen)
		    break;
		if (--jumpidx < 0)
		    jumpidx = curwin->w_jumplistlen - 1;
		if (jumpidx == forward)		// List exhausted for sure
		    break;
	    }
	}
#endif

	if (buf == NULL)	// No previous buffer, Try 2'nd approach
	{
	    forward = TRUE;
	    buf = curbuf->b_next;
	    for (;;)
	    {
		if (buf == NULL)
		{
		    if (!forward)	// tried both directions
			break;
		    buf = curbuf->b_prev;
		    forward = FALSE;
		    continue;
		}
		// in non-help buffer, try to skip help buffers, and vv
		if (buf->b_help == curbuf->b_help && buf->b_p_bl)
		{
		    if (buf->b_ml.ml_mfp != NULL)   // found loaded buffer
			break;
		    if (bp == NULL)	// remember unloaded buf for later
			bp = buf;
		}
		if (forward)
		    buf = buf->b_next;
		else
		    buf = buf->b_prev;
	    }
	}
	if (buf == NULL)	// No loaded buffer, use unloaded one
	    buf = bp;
	if (buf == NULL)	// No loaded buffer, find listed one
	{
	    FOR_ALL_BUFFERS(buf)
		if (buf->b_p_bl && buf != curbuf)
		    break;
	}
	if (buf == NULL)	// Still no buffer, just take one
	{
	    if (curbuf->b_next != NULL)
		buf = curbuf->b_next;
	    else
		buf = curbuf->b_prev;
	}
    }

    if (buf == NULL)
    {
	// Autocommands must have wiped out all other buffers.  Only option
	// now is to make the current buffer empty.
	return empty_curbuf(FALSE, forceit, action);
    }

    /*
     * make buf current buffer
     */
    if (action == DOBUF_SPLIT)	    // split window first
    {
	// If 'switchbuf' contains "useopen": jump to first window containing
	// "buf" if one exists
	if ((swb_flags & SWB_USEOPEN) && buf_jump_open_win(buf))
	    return OK;
	// If 'switchbuf' contains "usetab": jump to first window in any tab
	// page containing "buf" if one exists
	if ((swb_flags & SWB_USETAB) && buf_jump_open_tab(buf))
	    return OK;
	if (win_split(0, 0) == FAIL)
	    return FAIL;
    }

    // go to current buffer - nothing to do
    if (buf == curbuf)
	return OK;

    /*
     * Check if the current buffer may be abandoned.
     */
    if (action == DOBUF_GOTO && !can_abandon(curbuf, forceit))
    {
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
	if ((p_confirm || (cmdmod.cmod_flags & CMOD_CONFIRM)) && p_write)
	{
	    bufref_T bufref;

	    set_bufref(&bufref, buf);
	    dialog_changed(curbuf, FALSE);
	    if (!bufref_valid(&bufref))
		// Autocommand deleted buffer, oops!
		return FAIL;
	}
	if (bufIsChanged(curbuf))
#endif
	{
	    no_write_message();
	    return FAIL;
	}
    }

    // Go to the other buffer.
    set_curbuf(buf, action);

    if (action == DOBUF_SPLIT)
	RESET_BINDING(curwin);	// reset 'scrollbind' and 'cursorbind'

#if defined(FEAT_EVAL)
    if (aborting())	    // autocmds may abort script processing
	return FAIL;
#endif

    return OK;
}
