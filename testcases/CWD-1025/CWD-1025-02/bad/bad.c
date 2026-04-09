// Standard library includes
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Basic type definitions
typedef unsigned char char_u;
typedef long long_u;
typedef long linenr_T;
typedef int colnr_T;
typedef long long varnumber_T;
typedef long long time_T;
typedef long long proftime_T;
typedef long guicolor_T;
typedef unsigned int guint32;
typedef void* Display;
typedef volatile int sig_atomic_t;

// Forward declarations
typedef struct window_S		win_T;
typedef struct wininfo_S	wininfo_T;
typedef struct file_buffer	buf_T;
typedef struct tabpage_S	tabpage_T;
typedef struct frame_S		frame_T;
typedef struct listvar_S	list_T;
typedef struct alist_S		alist_T;
typedef struct diff_S		diff_T;
typedef struct term_S		term_T;
typedef struct timer_S		timer_T;
struct scrollbar_S
{
    int		id;
};
typedef struct scrollbar_S	scrollbar_T;

// from: src/structs.h:103
typedef struct
{
    int		fnum;
    linenr_T	lnum;
    colnr_T	col;
} fmark_T;

// from: src/structs.h:163
typedef struct taggy
{
    char_u	*tagname;
    fmark_T	fmark;
    int		cur_match;
    int		cur_fnum;
    char_u	*user_data;
} taggy_T;

// from: src/structs.h:177
typedef struct
{
    int		wo_arab;
} winopt_T;

// from: src/structs.h:344
struct wininfo_S
{
    wininfo_T	*wi_next;
    wininfo_T	*wi_prev;
    win_T	*wi_win;
    fmark_T	wi_fpos;
    winopt_T	wi_opt;
    int		wi_optset;
#ifdef FEAT_FOLDING
    int		wi_fold_manual;
    void*	wi_folds;
#endif
    int		wi_changelistidx;
};

// from: src/structs.h:936
typedef struct alist_S
{
    void*	al_ga;
    int		al_ga_len;
} alist_T;

// from: src/structs.h:99
typedef struct
{
    buf_T   *br_buf;
    int	    br_fnum;
} bufref_T;

// from: src/structs.h:1459
typedef struct callback_S
{
    int cb_type;
} callback_T;

// from: src/structs.h:1649
typedef struct dict_S
{
    void*	dv_hashtab;
} dict_T;

// from: src/structs.h:1637
typedef struct
{
    dict_T	*di_dict;
    void*	di_tv;
} dictitem16_T;

// from: src/structs.h:1445
struct listvar_S
{
    list_T	*lv_copylist;
    list_T	*lv_used_next;
    list_T	*lv_used_prev;
    int		lv_refcount;
    int		lv_len;
    void*	lv_first;
    void*	lv_last;
    int		lv_u;
    int		lv_lock;
    void*	lv_watch;
    int		lv_insertidx;
};

// from: src/structs.h:3014
struct file_buffer
{
    void*	b_ml;
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
    char_u	b_key[9];
    int		b_changed;
    dictitem16_T b_ct_di;
    varnumber_T	b_last_changedtick;
    varnumber_T	b_last_changedtick_pum;
    varnumber_T	b_last_changedtick_i;
    int		b_saving;
    int		b_mod_set;
    linenr_T	b_mod_top;
    linenr_T	b_mod_bot;
    long	b_mod_xlines;
    wininfo_T	*b_wininfo;
    long	b_mtime;
    long	b_mtime_ns;
    long	b_mtime_read;
    long	b_mtime_read_ns;
    long	b_orig_size;
    int		b_orig_mode;
    time_T	b_last_used;
    void*	b_namedm[10];
    void*	b_visual;
    void*	b_last_cursor;
    void*	b_last_insert;
    void*	b_last_change;
    int		b_p_bl;
    char_u	b_p_bh[10];
    int		b_p_initialized;
#ifdef FEAT_TERMINAL
    term_T	*b_term;
#endif
    void*	b_cfu_cb;
    void*	b_ofu_cb;
    void*	b_tfu_cb;
    void*	b_tsrfu_cb;
    void*	b_prompt_callback;
    void*	b_prompt_interrupt;
    list_T	*b_recorded_changes;
    void*	b_s;
    int		b_shortname;
    int		b_p_eof;
    int		b_start_eof;
    int		b_p_eol;
    int		b_start_eol;
    int		b_p_bomb;
    int		b_start_bomb;
    void*	b_ml_mfp;
    int		b_ml_flags;
    int		b_u_synced;
    int		b_u_needs_sync;
    int		b_u_oldhead;
    int		b_u_newhead;
    int		b_u_curhead;
    int		b_u_numhead;
    int		b_u_save_nr;
    int		b_u_sync_nr;
    int		b_u_dirty;
    void*	b_u_head;
    void*	b_u_tail;
    int		b_u_line_count;
    int		b_u_save_count;
    void*	b_arab_m;
    void*	b_spyal;
    void*	b_garray;
    int		b_refcount;
    int		b_prompt_insert;
    void*	b_kmap_state;
    void*	b_wsetlist;
    int		b_wsetlist_count;
    int		b_mapped_ctrl_c;
    int		b_p_ma;
    int		b_p_ro;
    int		b_p_sw;
    int		b_p_ts;
    int		b_p_sts;
    int		b_p_et;
    void*	b_p_vsts;
    void*	b_p_vts;
    void*	b_p_lcs;
    void*	b_p_fcs;
    void*	b_p_cinopts;
    void*	b_p_indk;
    void*	b_p_fo;
    void*	b_p_flp;
    void*	b_p_cot;
    void*	b_p_cpt;
    void*	b_p_ise;
    void*	b_p_def;
    void*	b_p_inc;
    void*	b_p_inex;
    void*	b_p_inde;
    void*	b_p_cino;
    void*	b_p_cinsd;
    void*	b_p_cinkeys;
    void*	b_p_cinwords;
    void*	b_p_lisp;
    void*	b_p_lop;
    void*	b_p_ft;
    void*	b_p_kp;
    void*	b_p_mps;
};

// from: src/structs.h:3775
struct window_S
{
    int		w_id;
    buf_T	*w_buffer;
    win_T	*w_prev;
    win_T	*w_next;
    int		w_closing;
    void*	w_frame;
    void*	w_cursor;
    void*	w_s;
    int		w_popup_flags;
    timer_T	*w_popup_timer;
    void*	w_border_highlight[4];
    char_u	*w_scrollbar_highlight;
    char_u	*w_thumb_highlight;
    char_u	*w_popup_title;
    list_T	*w_popup_mask;
    char_u	*w_popup_mask_cells;
    char_u	*w_p_cc_cols;
    alist_T	*w_alist;
    dict_T	*w_vars;
    winopt_T	w_onebuf_opt;
    winopt_T	w_allbuf_opt;
    void*	w_lcs_chars;
    void*	w_fill_chars;
    scrollbar_T	w_scrollbars[2];
    callback_T	w_close_cb;
    callback_T	w_filter_cb;
    int		w_tagstacklen;
    taggy_T	w_tagstack[50];
    int		w_tagstackidx;
    char_u	*w_localdir;
    char_u	*w_prevdir;
    fmark_T	w_jumplist[100];
    int		w_jumplistlen;
    int		w_jumplistidx;
    linenr_T	w_cursor_lnum;
    colnr_T	w_cursor_col;
    int		w_wants_cursor_lnum;
    int		w_wants_cursor_col;
};

// from: src/structs.h:3556
struct tabpage_S
{
    tabpage_T	    *tp_next;
    frame_T	    *tp_topframe;
    win_T	    *tp_curwin;
    win_T	    *tp_prevwin;
    win_T	    *tp_firstwin;
    win_T	    *tp_lastwin;
#ifdef FEAT_PROP_POPUP
    win_T	    *tp_first_popupwin;
#endif
    long	    tp_old_Rows;
    long	    tp_old_Columns;
    long	    tp_ch_used;
#ifdef FEAT_GUI
    int		    tp_prev_which_scrollbars[3];
#endif
    char_u	    *tp_localdir;
    char_u	    *tp_prevdir;
#ifdef FEAT_DIFF
    diff_T	    *tp_first_diff;
    buf_T	    *(tp_diffbuf[5]);
    int		    tp_diff_invalid;
    int		    tp_diff_update;
#endif
    void*	    tp_snapshot[2];
#ifdef FEAT_EVAL
    void*	    tp_winvar;
    dict_T	    *tp_vars;
#endif
#ifdef FEAT_PYTHON
    void*	    tp_python_ref;
#endif
#ifdef FEAT_PYTHON3
    void*	    tp_python3_ref;
#endif
};

// from: src/gui.h:456
typedef struct
{
    int		in_use;
    Display*	dpy;
    int		char_width;
    int		char_height;
    int		char_ascent;
    int		border_offset;
    guicolor_T	back_pixel;
    guicolor_T	norm_pixel;
    guicolor_T	def_back_pixel;
    guicolor_T	def_norm_pixel;
    guicolor_T	menu_fg_pixel;
    guicolor_T	menu_bg_pixel;
    guicolor_T	scroll_fg_pixel;
    guicolor_T	scroll_bg_pixel;
    void*	rsrc_font_name;
    guint32	event_time;
    int		currFgColor;
    int		currBgColor;
    int		currSpColor;
    guicolor_T	tooltip_fg_pixel;
    guicolor_T	tooltip_bg_pixel;
} gui_T;

// from: src/structs.h:964
typedef struct eslist_elem
{
    struct eslist_elem *next;
    void	*csp;
} eslist_T;

// from: src/structs.h:1046
typedef struct msglist
{
    struct msglist	*next;
    char_u	*msg;
    int		throw_msg_id;
} msglist_T;

// from: src/structs.h:2785
typedef struct timer_S
{
    callback_T	tr_callback;
    int		tr_interval;
    int		tr_repeat;
    int		tr_count;
    int		tr_active;
    int		tr_paused;
    int		tr_stop;
    timer_T*	tr_next;
    timer_T*	tr_prev;
    int		tr_id;
} timer_T;

// from: src/structs.h:3643
typedef struct frame_S
{
    win_T	*fr_win;
    frame_T	*fr_next;
    frame_T	*fr_prev;
    frame_T	*fr_child;
    frame_T	*fr_parent;
    int		fr_layout;
    int		fr_width;
    int		fr_height;
    int		fr_x;
    int		fr_y;
    int		fr_id;
} frame_T;

// from: src/structs.h:3581
typedef struct diff_S
{
    int		df_lnum;
    int		df_count;
    int		df_size;
    diff_T*	df_next;
    diff_T*	df_prev;
} diff_T;

// from: src/structs.h:2464
typedef struct term_S
{
    void*	t_job;
    int		t_status;
} term_T;

// Global variables
win_T	*firstwin = NULL;
win_T	*lastwin = NULL;
win_T	*prevwin = NULL;
win_T	*curwin = NULL;
tabpage_T    *first_tabpage = NULL;
tabpage_T    *curtab = NULL;
buf_T	*firstbuf = NULL;
buf_T	*lastbuf = NULL;
buf_T	*curbuf = NULL;
int	autocmd_busy = 0;
win_T	*au_pending_free_win = NULL;
int	really_exiting = 0;
gui_T gui = {0};
alist_T	global_alist = {0};
msglist_T **msg_list = NULL;
void* buf_reuse = NULL;
int	p_tgc = 0;

// Constants
#define DOBUF_DEL	3
#define DOBUF_WIPE	4
#define DOBUF_WIPE_REUSE 5

#define BFA_DEL		 1
#define BFA_WIPE	 2
#define BFA_IGNORE_ABORT 8

#define TRUE 1
#define FALSE 0
#define OK 1
#define FAIL 0

#define VIM_CLEAR(p) \
    do { \
	if ((p) != NULL) \
	{ \
	    vim_free(p); \
	    (p) = NULL; \
	} \
    } while (0)

#define FOR_ALL_TABPAGES(tp) \
    for ((tp) = first_tabpage; (tp) != NULL; (tp) = (tp)->tp_next)

#define FOR_ALL_BUFFERS(buf) \
    for ((buf) = firstbuf; (buf) != NULL; (buf) = (buf)->b_next)

#define FOR_ALL_BUF_WININFO(buf, wip) \
    for ((wip) = (buf)->b_wininfo; (wip) != NULL; (wip) = (wip)->wi_next)

#define FOR_ALL_TAB_WINDOWS(tp, wp) \
    for ((tp) = first_tabpage; (tp) != NULL; (tp) = (tp)->tp_next) \
	for ((wp) = ((tp) == first_tabpage) \
		? firstwin : (tp)->tp_firstwin; (wp); (wp) = (wp)->w_next)

#define CHECK_CURBUF \
    do { if (msg_list != NULL && *msg_list != NULL) return FALSE; } while (0)

#define mch_memmove(to, from, len) memmove((char*)(to), (char*)(from), (size_t)(len))

#define SBAR_LEFT 0
#define SBAR_RIGHT 1

#define TAGSTACKSIZE 50

#define DB_COUNT 5

#define SNAP_COUNT 2

#define BF_CHECK_RO	0x08
#define BF_NEVERLOADED	0x20

// Function declarations
void vim_free(void *x);
void win_free_popup(win_T *win);
int close_buffer(win_T *win, buf_T *buf, int action, int abort_if_last, int ignore_abort);
int bt_popup(buf_T *buf);
void mark_forget_file(win_T *wp, int fnum);
void tagstack_clear_entry(taggy_T *item);
void win_free_lsize(win_T *wp);
void free_wininfo(wininfo_T *wip);
void clear_matches(win_T *wp);
void free_jumplist(win_T *wp);
void qf_free_all(win_T *wp);
void remove_winbar(win_T *wp);
void free_callback(callback_T *callback);
void list_unref(list_T *l);
int win_valid_any_tab(win_T *win);
void win_remove(win_T *wp, tabpage_T *tp);
void clearFolding(win_T *win);
void alist_unlink(alist_T *al);
void block_autocmds(void);
void unblock_autocmds(void);
void clear_winopt(winopt_T *wop);
void vars_clear(void *ht);
void hash_init(void *ht);
void unref_var_dict(dict_T *dict);
int timer_valid(timer_T *timer);
void stop_timer(timer_T *timer);
void set_bufref(bufref_T *bufref, buf_T *buf);
int bufref_valid(bufref_T *bufref);
int apply_autocmds(int event, char_u *fname, char_u *fname_io, int force, buf_T *buf);
int one_window(void);
void set_last_cursor(win_T *win);
void buflist_setfpos(buf_T *buf, win_T *win, linenr_T lnum, colnr_T col, int copy_options);
void goto_tabpage_win(tabpage_T *tp, win_T *wp);
int diffopt_hiddenoff(void);
void diff_buf_delete(buf_T *buf);
void end_visual_mode(void);
void buf_freeall(buf_T *buf, int flags);
void ga_init2(void *gap, size_t itemsize, int growsize);
int ga_grow(void *gap, int n);
int aborting(void);
void gui_mch_destroy_scrollbar(scrollbar_T *sb);
void free_terminal(buf_T *buf);
int term_job_running(term_T *term);
int bt_terminal(buf_T *buf);
void emsg(const char *str);
void win_close_buffer(win_T *win, int action, int ignore_abort);
int can_unload_buffer(buf_T *buf);
void free_buffer(buf_T *buf);
void free_buffer_stuff(buf_T *buf, int free_options);
void buf_clear_file(buf_T *buf);

// from: src/alloc.c:608
void vim_free(void *x)
{
    if (x != NULL && !really_exiting)
    {
#ifdef MEM_PROFILE
	mem_pre_free(&x);
#endif
	free(x);
    }
}

// from: src/window.c:5768
/*
 * Remove window 'wp' from the window list and free the structure.
 */
    static void
win_free(
    win_T	*wp,
    tabpage_T	*tp)		// tab page "win" is in, NULL for current
{
    int		i;
    buf_T	*buf;
    wininfo_T	*wip;

#ifdef FEAT_FOLDING
    clearFolding(wp);
#endif

    alist_unlink(wp->w_alist);

    block_autocmds();

#ifdef FEAT_LUA
    lua_window_free(wp);
#endif

#ifdef FEAT_MZSCHEME
    mzscheme_window_free(wp);
#endif

#ifdef FEAT_PERL
    perl_win_free(wp);
#endif

#ifdef FEAT_PYTHON
    python_window_free(wp);
#endif

#ifdef FEAT_PYTHON3
    python3_window_free(wp);
#endif

#ifdef FEAT_TCL
    tcl_window_free(wp);
#endif

#ifdef FEAT_RUBY
    ruby_window_free(wp);
#endif

    clear_winopt(&wp->w_onebuf_opt);
    clear_winopt(&wp->w_allbuf_opt);

    vim_free(((char**)wp->w_lcs_chars)[0]);
    vim_free(((char**)wp->w_lcs_chars)[1]);

#ifdef FEAT_EVAL
    vars_clear(&wp->w_vars->dv_hashtab);
    hash_init(&wp->w_vars->dv_hashtab);
    unref_var_dict(wp->w_vars);
#endif

    {
	tabpage_T	*ttp;

	if (prevwin == wp)
	    prevwin = NULL;
	FOR_ALL_TABPAGES(ttp)
	    if (ttp->tp_prevwin == wp)
		ttp->tp_prevwin = NULL;
    }
    win_free_lsize(wp);

    for (i = 0; i < wp->w_tagstacklen; ++i)
    {
	vim_free(wp->w_tagstack[i].tagname);
	vim_free(wp->w_tagstack[i].user_data);
    }
    vim_free(wp->w_localdir);
    vim_free(wp->w_prevdir);

    FOR_ALL_BUFFERS(buf)
	FOR_ALL_BUF_WININFO(buf, wip)
	    if (wip->wi_win == wp)
	    {
		wininfo_T	*wip2;

		FOR_ALL_BUF_WININFO(buf, wip2)
		    if (wip2 != wip && wip2->wi_win == NULL)
		    {
			if (wip2->wi_next != NULL)
			    wip2->wi_next->wi_prev = wip2->wi_prev;
			if (wip2->wi_prev == NULL)
			    buf->b_wininfo = wip2->wi_next;
			else
			    wip2->wi_prev->wi_next = wip2->wi_next;
			free_wininfo(wip2);
			break;
		    }

		wip->wi_win = NULL;
	    }

#ifdef FEAT_SEARCH_EXTRA
    clear_matches(wp);
#endif

    free_jumplist(wp);

#ifdef FEAT_QUICKFIX
    qf_free_all(wp);
#endif

#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui_mch_destroy_scrollbar(&wp->w_scrollbars[SBAR_LEFT]);
	gui_mch_destroy_scrollbar(&wp->w_scrollbars[SBAR_RIGHT]);
    }
#endif

#ifdef FEAT_MENU
    remove_winbar(wp);
#endif
#ifdef FEAT_PROP_POPUP
    free_callback(&wp->w_close_cb);
    free_callback(&wp->w_filter_cb);
    for (i = 0; i < 4; ++i)
	VIM_CLEAR(wp->w_border_highlight[i]);
    vim_free(wp->w_scrollbar_highlight);
    vim_free(wp->w_thumb_highlight);
    vim_free(wp->w_popup_title);
    list_unref(wp->w_popup_mask);
    vim_free(wp->w_popup_mask_cells);
#endif

#ifdef FEAT_SYN_HL
    vim_free(wp->w_p_cc_cols);
#endif

    if (win_valid_any_tab(wp))
	win_remove(wp, tp);
    if (autocmd_busy)
    {
	wp->w_next = au_pending_free_win;
	au_pending_free_win = wp;
    }
    else
	vim_free(wp);

    unblock_autocmds();
}

// from: src/window.c:5936
    void
win_free_popup(win_T *win)
{
    if (win->w_buffer != NULL)
    {
	if (bt_popup(win->w_buffer))
	    win_close_buffer(win, DOBUF_WIPE_REUSE, FALSE);
	else
	    close_buffer(win, win->w_buffer, 0, FALSE, FALSE);
    }
# if defined(FEAT_TIMERS)
    if (timer_valid(win->w_popup_timer))
	stop_timer(win->w_popup_timer);
# endif
    vim_free(win->w_frame);
    win_free(win, NULL);
}

// from: src/buffer.c:522
    int
close_buffer(
    win_T	*win,
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

    if (buf->b_p_bh[0] == 'd')
    {
	del_buf = TRUE;
	unload_buf = TRUE;
    }
    else if (buf->b_p_bh[0] == 'w')
    {
	del_buf = TRUE;
	unload_buf = TRUE;
	wipe_buf = TRUE;
    }
    else if (buf->b_p_bh[0] == 'u')
	unload_buf = TRUE;

#ifdef FEAT_TERMINAL
    if (bt_terminal(buf) && (buf->b_nwindows <= 1 || del_buf))
    {
	CHECK_CURBUF;
	if (term_job_running(buf->b_term))
	{
	    if (wipe_buf || unload_buf)
	    {
		if (!can_unload_buffer(buf))
		    return FALSE;

		free_terminal(buf);

		del_buf = TRUE;
		unload_buf = TRUE;
		wipe_buf = TRUE;
	    }
	    else
	    {
		del_buf = FALSE;
		unload_buf = FALSE;
	    }
	}
	else if (buf->b_p_bh[0] == 'h' && !del_buf)
	{
	    unload_buf = FALSE;
	}
	else
	{
	    if (del_buf || unload_buf)
	    {
		del_buf = TRUE;
		unload_buf = TRUE;
		wipe_buf = TRUE;
	    }
	}
	CHECK_CURBUF;
    }
#endif

    if ((del_buf || wipe_buf) && !can_unload_buffer(buf))
	return FALSE;

    if (win != NULL && win_valid_any_tab(win))
    {
	if (buf->b_nwindows == 1)
	    set_last_cursor(win);
	buflist_setfpos(buf, win, 0, 0, TRUE);
    }

    set_bufref(&bufref, buf);

    if (buf->b_nwindows == 1)
    {
	++buf->b_locked;
	++buf->b_locked_split;
	if (apply_autocmds(0, buf->b_fname, buf->b_fname, FALSE, buf)
		&& !bufref_valid(&bufref))
	{
aucmd_abort:
	    emsg("autocommands caused command to abort");
	    return FALSE;
	}
	--buf->b_locked;
	--buf->b_locked_split;
	if (abort_if_last && one_window())
	    goto aucmd_abort;

	if (!unload_buf)
	{
	    ++buf->b_locked;
	    ++buf->b_locked_split;
	    if (apply_autocmds(0, buf->b_fname, buf->b_fname, FALSE, buf)
		    && !bufref_valid(&bufref))
		goto aucmd_abort;
	    --buf->b_locked;
	    --buf->b_locked_split;
	    if (abort_if_last && one_window())
		goto aucmd_abort;
	}
#ifdef FEAT_EVAL
	if (!ignore_abort && aborting())
	    return FALSE;
#endif
    }

    if (is_curwin && curwin != the_curwin &&  win_valid_any_tab(the_curwin))
    {
	block_autocmds();
	goto_tabpage_win(the_curtab, the_curwin);
	unblock_autocmds();
    }

    nwindows = buf->b_nwindows;

    if (buf->b_nwindows > 0)
	--buf->b_nwindows;

#ifdef FEAT_DIFF
    if (diffopt_hiddenoff() && !unload_buf && buf->b_nwindows == 0)
	diff_buf_delete(buf);
#endif

    if (buf->b_nwindows > 0 || !unload_buf)
	return FALSE;

    if (buf->b_ffname == NULL)
	del_buf = TRUE;

    if (buf == curbuf)
	end_visual_mode();

    is_curbuf = (buf == curbuf);
    buf->b_nwindows = nwindows;

    buf_freeall(buf, (del_buf ? BFA_DEL : 0)
		   + (wipe_buf ? BFA_WIPE : 0)
		   + (ignore_abort ? BFA_IGNORE_ABORT : 0));

    if (!bufref_valid(&bufref))
	return FALSE;
#ifdef FEAT_EVAL
    if (!ignore_abort && aborting())
	return FALSE;
#endif

    if (buf == curbuf && !is_curbuf)
	return FALSE;

    if (win_valid_any_tab(win) && win->w_buffer == buf)
	win->w_buffer = NULL;

    if (buf->b_nwindows > 0)
	--buf->b_nwindows;

    if (wipe_buf)
    {
	tabpage_T	*tp;
	win_T		*wp;

	if (buf->b_nwindows > 0)
	    return FALSE;

	FOR_ALL_TAB_WINDOWS(tp, wp)
	    mark_forget_file(wp, buf->b_fnum);

	if (action == DOBUF_WIPE_REUSE)
	{
	    if (buf_reuse == NULL)
		ga_init2(&buf_reuse, sizeof(int), 50);
	    if (ga_grow(&buf_reuse, 1) == OK)
		((int *)buf_reuse)[0] = buf->b_fnum;
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
	    free_buffer_stuff(buf, TRUE);

	    buf->b_flags = BF_CHECK_RO | BF_NEVERLOADED;

	    buf->b_p_initialized = FALSE;
	}
	buf_clear_file(buf);
	if (del_buf)
	    buf->b_p_bl = FALSE;
    }
    return TRUE;
}

// from: src/mark.c:136
void
mark_forget_file(win_T *wp, int fnum)
{
    int		i;

    for (i = wp->w_jumplistlen - 1; i >= 0; --i)
	if (wp->w_jumplist[i].fnum == fnum)
	{
	    if (wp->w_jumplistidx > i)
		--wp->w_jumplistidx;
	    --wp->w_jumplistlen;
	    mch_memmove(&wp->w_jumplist[i], &wp->w_jumplist[i + 1],
			(wp->w_jumplistlen - i) * sizeof(wp->w_jumplist[i]));
	}

    for (i = wp->w_tagstacklen - 1; i >= 0; --i)
	if (wp->w_tagstack[i].fmark.fnum == fnum)
	{
	    tagstack_clear_entry(&wp->w_tagstack[i]);
	    if (wp->w_tagstackidx > i)
		--wp->w_tagstackidx;
	    --wp->w_tagstacklen;
	    mch_memmove(&wp->w_tagstack[i], &wp->w_tagstack[i + 1],
			(wp->w_tagstacklen - i) * sizeof(wp->w_tagstack[i]));
	}
}

// from: src/tag.c:4240
void
tagstack_clear_entry(taggy_T *item)
{
    VIM_CLEAR(item->tagname);
    VIM_CLEAR(item->user_data);
}
