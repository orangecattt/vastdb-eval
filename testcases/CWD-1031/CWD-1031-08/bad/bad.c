// FROM: vim/src/vim9class.c
// FROM: vim/src/eval.c
// FROM: vim/src/typval.c
// FROM: vim/src/list.c
// FROM: vim/src/dict.c
// FROM: vim/src/userfunc.c
// FROM: vim/src/structs.h
// FROM: vim/src/globals.h

#include <stddef.h>
#include <stdint.h>

// Basic type definitions
typedef unsigned char char_u;
typedef long varnumber_T;
typedef double float_T;
typedef int colnr_T;
typedef long linenr_T;

// Forward declarations
typedef struct typval_S typval_T;
typedef struct listvar_S list_T;
typedef struct dictvar_S dict_T;
typedef struct partial_S partial_T;
typedef struct blobvar_S blob_T;
typedef struct class_S class_T;
typedef struct object_S object_T;
typedef struct ufunc_S ufunc_T;
typedef struct type_S type_T;
typedef struct evalarg_S evalarg_T;
typedef struct cctx_S cctx_T;
typedef struct cstack_S cstack_T;
typedef struct scriptitem_S scriptitem_T;
typedef struct svar_S svar_T;
typedef struct dictitem_S dictitem_T;
typedef struct garray_S garray_T;
typedef struct sctx_S sctx_T;
typedef struct listitem_S listitem_T;
typedef struct listwatch_S listwatch_T;

// FROM: vim/src/structs.h
typedef enum {
    VAR_UNKNOWN = 0,
    VAR_NUMBER,
    VAR_STRING,
    VAR_FUNC,
    VAR_LIST,
    VAR_DICT,
    VAR_FLOAT,
    VAR_PARTIAL,
    VAR_BOOL,
    VAR_SPECIAL,
    VAR_BLOB,
    VAR_JOB,
    VAR_CHANNEL,
    VAR_VOID,
    VAR_ANY,
    VAR_INSTR,
    VAR_CLASS,
    VAR_OBJECT,
} vartype_T;

// FROM: vim/src/structs.h
struct typval_S
{
    vartype_T	v_type;
    char	v_lock;
    union
    {
	varnumber_T	v_number;
	float_T		v_float;
	char_u		*v_string;
	list_T		*v_list;
	dict_T		*v_dict;
	partial_T	*v_partial;
	blob_T		*v_blob;
	void		*v_instr;
	class_T		*v_class;
	object_T	*v_object;
    }		vval;
};

// FROM: vim/src/structs.h
typedef struct {
    char_u	*ocm_name;
    int		ocm_access;
    type_T	*ocm_type;
    char_u	*ocm_init;
} ocmember_T;

// FROM: vim/src/structs.h
struct garray_S
{
    void	*ga_data;
    int		ga_len;
    int		ga_maxlen;
    int		ga_itemsize;
    int		(*ga_growsize)(void *gap, int minlen);
};

// FROM: vim/src/structs.h
struct sctx_S
{
    int		sc_sid;
    int		sc_lnum;
    int         sc_version;
};

// FROM: vim/src/structs.h
struct class_S
{
    char_u	*class_name;
    int		class_flags;
    int		class_refcount;
    int		class_copyID;
    class_T	*class_extends;
    int		class_interface_count;
    char_u	**class_interfaces;
    class_T	**class_interfaces_cl;
    void	*class_itf2class;
    int		class_class_member_count;
    ocmember_T	*class_class_members;
    typval_T	*class_members_tv;
    int		class_class_function_count;
    int		class_class_function_count_child;
    ufunc_T	**class_class_functions;
    int		class_obj_member_count;
    ocmember_T	*class_obj_members;
    int		class_obj_method_count;
    int		class_obj_method_count_child;
    ufunc_T	**class_obj_methods;
    garray_T	class_type_list;
    type_T	*class_type;
    type_T	*class_object_type;
};

// FROM: vim/src/structs.h
struct object_S
{
    class_T	*obj_class;
    int		obj_refcount;
    object_T	*obj_next_used;
    object_T	*obj_prev_used;
    int		obj_copyID;
};

// FROM: vim/src/structs.h
typedef enum { UF_NOT_COMPILED = 0 } def_status_T;

// FROM: vim/src/structs.h
struct ufunc_S
{
    int		uf_varargs;
    int		uf_flags;
    int		uf_calls;
    int		uf_cleared;
    def_status_T	uf_def_status;
    int		uf_dfunc_idx;
    class_T	*uf_class;
    garray_T	uf_args;
    garray_T	uf_def_args;
    int		uf_args_visible;
    type_T	**uf_arg_types;
    type_T	*uf_ret_type;
    garray_T	uf_type_list;
    partial_T	*uf_partial;
    char_u	*uf_va_name;
    type_T	*uf_va_type;
    type_T	*uf_func_type;
    int		uf_block_depth;
    int		*uf_block_ids;
    garray_T	uf_lines;
    int		uf_debug_tick;
    int		uf_has_breakpoint;
    sctx_T	uf_script_ctx;
    int		uf_script_ctx_version;
    int		uf_refcount;
    void	*uf_scoped;
    char_u	*uf_name_exp;
    char_u	uf_name[4];
};

// FROM: vim/src/structs.h
struct evalarg_S {
    int		eval_flags;
    int		eval_break_count;
    char_u	*(*eval_getline)(int, void *, int, int);
    void	*eval_cookie;
    cctx_T	*eval_cctx;
    cstack_T	*eval_cstack;
    garray_T	eval_ga;
    garray_T	eval_freega;
    char_u	*eval_tofree;
    garray_T	eval_tofree_ga;
    int		eval_using_cmdline;
    char_u	*eval_tofree_lambda;
};

// FROM: vim/src/structs.h
struct dictitem_S
{
    char_u	*di_key;
    typval_T	di_tv;
};

// FROM: vim/src/structs.h
struct listitem_S {
    listitem_T *li_next;
    listitem_T *li_prev;
    typval_T li_tv;
};

// FROM: vim/src/structs.h
struct listwatch_S {
    listitem_T *lw_item;
    listwatch_T *lw_next;
};

// FROM: vim/src/structs.h
struct listvar_S {
    listitem_T *lv_first;
    listwatch_T *lv_watch;
    void *lv_u;
    type_T *lv_type;
    list_T *lv_copylist;
    list_T *lv_used_next;
    list_T *lv_used_prev;
    int lv_refcount;
    int lv_len;
    int lv_with_items;
    int lv_copyID;
    char lv_lock;
};

// FROM: vim/src/structs.h
struct dictvar_S {
    void *dv_first;
    void *dv_watch;
    void *dv_copydict;
    void *dv_used_next;
    void *dv_used_prev;
    int dv_refcount;
    int dv_copyID;
    char dv_lock;
    int dv_scope;
};

// FROM: vim/src/structs.h
struct partial_S {
    void *pt_func;
    int pt_refcount;
    int pt_auto;
    dict_T *pt_dict;
    void *pt_argv;
};

// FROM: vim/src/structs.h
struct blobvar_S {
    garray_T bv_ga;
    int bv_refcount;
};

// FROM: vim/src/structs.h
struct type_S {
    int tt_type;
    int tt_flags;
    void *tt_data;
};

// FROM: vim/src/structs.h
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

// FROM: vim/src/structs.h
struct svar_S {
    char_u *sv_name;
    typval_T *sv_tv;
    int sv_flags;
};

// FROM: vim/src/structs.h
struct scriptitem_S {
    char_u *sn_name;
    garray_T sn_var_vals;
    int sn_refcount;
};

// FROM: vim/src/structs.h
struct cctx_S { int dummy; };
struct cstack_S { int dummy; };
typedef struct { int dummy; } hashtab_T;

// FROM: vim/src/globals.h
#define OK 1
#define FAIL 0
#define NOTDONE 2
#define TRUE 1
#define FALSE 0

#define MAX_FUNC_ARGS 20
#define NUMBUFLEN 40

#define VAR_LOCKED 1
#define VAR_FIXED 2

#define EVAL_EVALUATE 1
#define EVAL_CONSTANT 2
#define EVAL_VAR_VERBOSE 1
#define EVAL_VAR_IMPORT 2

#define GREG_EXPR_SRC 0

#define FC_LAMBDA 0x2000
#define FC_NOARGS 0x200
#define FC_CLOSURE 0x08
#define FC_SANDBOX 0x40

#define FSK_KEYCODE 1
#define FSK_IN_STRING 2
#define FSK_SIMPLIFY 4

#define STR2NR_NO_OCT 1
#define STR2NR_QUOTE 2
#define STR2NR_ALL 4

#define BS 8
#define ESC 27
#define FF 12
#define NL 10
#define CAR 13
#define TAB 9

#define DICT_MAXNEST 100

#define NUL 0
#define UNUSED __attribute__((unused))
#define FNE_CHECK_START 1
#define CLEAR_FIELD(field) __builtin_memset(&(field), 0, sizeof(field))
#define FCERR_NONE 0

// External function declarations
extern int VIM_ISWHITE(int c);
extern int IS_WHITE_OR_NUL(int c);
extern int ASCII_ISALPHA(int c);
extern int vim_isdigit(int c);
extern int vim_isxdigit(int c);
extern char_u *skipwhite(char_u *p);
extern char_u *skipwhite_and_linebreak(char_u *p, evalarg_T *evalarg);
extern char_u *skipdigits(char_u *p);
extern char_u *vim_strsave(char_u *str);
extern char_u *vim_strnsave(char_u *str, size_t len);
extern char_u *vim_strncpy(char_u *dst, char_u *src, size_t n);
extern char_u *vim_strchr(char_u *str, int c);
extern void *vim_memset(void *s, int c, size_t n);
extern int STRNCMP(char_u *s1, char_u *s2, size_t n);
extern int toupper(int c);
extern int isdigit(int c);

extern void semsg(char *fmt, ...);
extern void emsg(char *str);
extern void iemsg(char *str);
extern char *_(char *str);

extern char_u *find_name_end(char_u *name, char_u **end, char_u **start, int flags);
extern int get_func_arguments(char_u **arg, evalarg_T *evalarg, int flags, typval_T *argvars, int *argcount);
extern int call_user_func_check(ufunc_T *fp, int argcount, typval_T *argvars, typval_T *rettv, funcexe_T *funcexe, void *funcstate);
extern void user_func_error(int error, char_u *name, int found_var);
extern char_u *printable_func_name(ufunc_T *fp);
extern void clear_tv(typval_T *varp);
extern void copy_tv(typval_T *from, typval_T *to);
extern void object_unref(object_T *obj);
extern void class_unref(class_T *cl);

extern char_u *eval_next_non_blank(char_u *arg, evalarg_T *evalarg, int *getnext);
extern char_u *eval_next_line(char_u *arg, evalarg_T *evalarg);
extern int eval_isdictc(int c);
extern int eval_isnamec(int c);
extern int in_vim9script(void);
extern int in_old_script(int version);
extern int aborting(void);
extern int eval_lambda(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int verbose);
extern int eval_method(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int verbose);
extern int eval_index(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int verbose);
extern dict_T *make_partial(dict_T *dict, typval_T *rettv);
extern void dict_unref(dict_T *dict);

extern int find_exported(varnumber_T script_id, char_u *name, ufunc_T **ufunc, type_T **type, cctx_T *cctx, cstack_T *cstack, int verbose);
#define SCRIPT_ITEM(id) ((scriptitem_T *)(uintptr_t)(id))
extern int call_func_rettv(char_u **arg, evalarg_T *evalarg, typval_T *rettv, int evaluate, dict_T *selfdict, typval_T *basetv);
extern char_u *get_reg_contents(int reg, int flags);
extern int valid_yank_reg(int reg, int writing);
extern void emsg_invreg(int reg);

extern int get_name_len(char_u **arg, char_u **alias, int evaluate, int check);
extern int eval_func(char_u **arg, evalarg_T *evalarg, char_u *name, int len, typval_T *rettv, int flags, typval_T *basetv);
extern int handle_predefined(char_u *name, int len, typval_T *rettv);
extern int eval_variable(char_u *name, int len, int flags, typval_T *rettv, dict_T *d, int verbose);
extern void check_vars(char_u *name, int len);

extern int eval_number(char_u **arg, typval_T *rettv, int evaluate, int want_string);
extern int eval_string(char_u **arg, typval_T *rettv, int evaluate, int interpolate);
extern int eval_lit_string(char_u **arg, typval_T *rettv, int evaluate, int interpolate);
extern int eval_list(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error);
extern int eval_dict(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int literal);
extern int get_lambda_tv(char_u **arg, typval_T *rettv, int types_optional, evalarg_T *evalarg);
extern int eval_option(char_u **arg, typval_T *rettv, int evaluate);
extern int eval_interp_string(char_u **arg, typval_T *rettv, int evaluate);
extern int eval_env_var(char_u **arg, typval_T *rettv, int evaluate);
extern int eval1(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
extern int eval2(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
extern int eval_leader(char_u **arg, int vim9);
extern int eval9_leader(typval_T *rettv, int numeric_only, char_u *start_leader, char_u **end_leaderp);

extern int vim9_bad_comment(char_u *p);
extern type_T *get_compile_type(ufunc_T *fp);
extern int compile_def_function(ufunc_T *fp, int silent, type_T *type, void *cctx);
extern void vim_free(void *ptr);

extern char *e_no_white_space_allowed_after_str_str;
extern char *e_using_null_object;
extern char *e_method_not_found_on_class_str_str;
extern char *e_cannot_access_private_member_str;
extern char *e_member_not_found_on_object_str_str;
extern char *e_member_not_found_on_class_str_str;
extern char *e_expected_dot_after_name_str;
extern char *e_no_white_space_allowed_after_dot;
extern char *e_no_white_space_allowed_before_parenthesis;
extern char *e_invalid_expression_str;
extern char *e_expression_too_recursive_str;
extern char *e_missing_double_quote_str;
extern char *e_stray_closing_curly_str;
extern char *e_missing_single_quote_str;
extern char *e_blob_literal_should_have_an_even_number_of_hex_characters;
extern char *e_white_space_required_after_str_str;
extern char *e_missing_comma_in_list_str;
extern char *e_missing_end_of_list_rsb_str;
extern char *e_no_white_space_allowed_before_str_str;
extern char *e_missing_colon_in_dictionary_str;
extern char *e_duplicate_key_in_dictionary_str;
extern char *e_missing_dict_end_str;
extern char *e_cannot_use_default_values_in_lambda;
extern char *e_expected_right_curly_str;
extern char *e_option_name_missing_str;
extern char *e_unknown_option_str;
extern char *e_syntax_error_at_str;
extern char *e_cannot_use_underscore_here;
extern char *e_cannot_use_s_colon_in_vim9_script_str;
extern char *e_closing_paren_expected_str;
extern char *e_missing_closing_paren;
extern char *e_missing_colon_after_questionmark;
extern char *e_variable_nested_too_deep_for_making_copy;
extern char *e_missing_matching_bracket_after_dict_key;

extern long SOURCING_LNUM;
extern int has_mbyte;
extern int got_int;
extern int echo_attr;
extern int need_clr_eos;
extern int did_emsg;
extern int called_emsg;
extern int emsg_skip;
extern int sandbox;
extern void *current_sctx;
extern void *current_funccal;
extern void *func_hashtab;
extern int *eval_lavars_used;
extern type_T t_unknown;

// FROM: vim/src/vim9class.c
    int
class_object_index(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		verbose UNUSED)	// give error messages
{
    if (VIM_ISWHITE((*arg)[1]))
    {
	semsg(_(e_no_white_space_allowed_after_str_str), ".", *arg);
	return FAIL;
    }

    ++*arg;
    char_u *name = *arg;
    char_u *name_end = find_name_end(name, NULL, NULL, FNE_CHECK_START);
    if (name_end == name)
	return FAIL;
    size_t len = name_end - name;

    class_T *cl;
    if (rettv->v_type == VAR_CLASS)
	cl = rettv->vval.v_class;
    else // VAR_OBJECT
    {
	if (rettv->vval.v_object == NULL)
	{
	    emsg(_(e_using_null_object));
	    return FAIL;
	}
	cl = rettv->vval.v_object->obj_class;
    }

    if (*name_end == '(')
    {
	int on_class = rettv->v_type == VAR_CLASS;
	int count = on_class ? cl->class_class_function_count
			     : cl->class_obj_method_count;
	for (int i = 0; i < count; ++i)
	{
	    ufunc_T *fp = on_class ? cl->class_class_functions[i]
				   : cl->class_obj_methods[i];
	    // Use a separate pointer to avoid that ASAN complains about
	    // uf_name[] only being 4 characters.
	    char_u *ufname = (char_u *)fp->uf_name;
	    if (STRNCMP(name, ufname, len) == 0 && ufname[len] == NUL)
	    {
		typval_T    argvars[MAX_FUNC_ARGS + 1];
		int	    argcount = 0;

		char_u *argp = name_end;
		int ret = get_func_arguments(&argp, evalarg, 0,
							   argvars, &argcount);
		if (ret == FAIL)
		    return FAIL;

		funcexe_T   funcexe;
		CLEAR_FIELD(funcexe);
		funcexe.fe_evaluate = TRUE;
		if (rettv->v_type == VAR_OBJECT)
		{
		    funcexe.fe_object = rettv->vval.v_object;
		    ++funcexe.fe_object->obj_refcount;
		}

		// Clear the class or object after calling the function, in
		// case the refcount is one.
		typval_T tv_tofree = *rettv;
		rettv->v_type = VAR_UNKNOWN;

		// Call the user function.  Result goes into rettv;
		int error = call_user_func_check(fp, argcount, argvars,
							rettv, &funcexe, NULL);

		// Clear the previous rettv and the arguments.
		clear_tv(&tv_tofree);
		for (int idx = 0; idx < argcount; ++idx)
		    clear_tv(&argvars[idx]);

		if (error != FCERR_NONE)
		{
		    user_func_error(error, printable_func_name(fp),
							 funcexe.fe_found_var);
		    return FAIL;
		}
		*arg = argp;
		return OK;
	    }
	}

	semsg(_(e_method_not_found_on_class_str_str), cl->class_name, name);
    }

    else if (rettv->v_type == VAR_OBJECT)
    {
	for (int i = 0; i < cl->class_obj_member_count; ++i)
	{
	    ocmember_T *m = &cl->class_obj_members[i];
	    if (STRNCMP(name, m->ocm_name, len) == 0 && m->ocm_name[len] == NUL)
	    {
		if (*name == '_')
		{
		    semsg(_(e_cannot_access_private_member_str), m->ocm_name);
		    return FAIL;
		}

		// The object only contains a pointer to the class, the member
		// values array follows right after that.
		object_T *obj = rettv->vval.v_object;
		typval_T *tv = (typval_T *)(obj + 1) + i;
		copy_tv(tv, rettv);
		object_unref(obj);

		*arg = name_end;
		return OK;
	    }
	}

	semsg(_(e_member_not_found_on_object_str_str), cl->class_name, name);
    }

    else if (rettv->v_type == VAR_CLASS)
    {
	// class member
	for (int i = 0; i < cl->class_class_member_count; ++i)
	{
	    ocmember_T *m = &cl->class_class_members[i];
	    if (STRNCMP(name, m->ocm_name, len) == 0 && m->ocm_name[len] == NUL)
	    {
		if (*name == '_')
		{
		    semsg(_(e_cannot_access_private_member_str), m->ocm_name);
		    return FAIL;
		}

		typval_T *tv = &cl->class_members_tv[i];
		copy_tv(tv, rettv);
		class_unref(cl);

		*arg = name_end;
		return OK;
	    }
	}

	semsg(_(e_member_not_found_on_class_str_str), cl->class_name, name);
    }

    return FAIL;
}

// FROM: vim/src/eval.c
    int
handle_subscript(
    char_u	**arg,
    char_u	*name_start,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		verbose)	// give error messages
{
    int		evaluate = evalarg != NULL
				      && (evalarg->eval_flags & EVAL_EVALUATE);
    int		ret = OK;
    dict_T	*selfdict = NULL;
    int		check_white = TRUE;
    int		getnext;
    char_u	*p;

    while (ret == OK)
    {
	// When at the end of the line and ".name" or "->{" or "->X" follows in
	// the next line then consume the line break.
	p = eval_next_non_blank(*arg, evalarg, &getnext);
	if (getnext
	    && ((*p == '.'
		    && ((rettv->v_type == VAR_DICT && eval_isdictc(p[1]))
			|| rettv->v_type == VAR_CLASS
			|| rettv->v_type == VAR_OBJECT))
		|| (p[0] == '-' && p[1] == '>' && (p[2] == '{'
			|| ASCII_ISALPHA(in_vim9script() ? *skipwhite(p + 2)
								    : p[2])))))
	{
	    *arg = eval_next_line(*arg, evalarg);
	    p = *arg;
	    check_white = FALSE;
	}

	if (rettv->v_type == VAR_ANY)
	{
	    char_u	*exp_name;
	    int		cc;
	    int		idx;
	    ufunc_T	*ufunc;
	    type_T	*type;

	    // Found script from "import {name} as name", script item name must
	    // follow.  "rettv->vval.v_number" has the script ID.
	    if (**arg != '.')
	    {
		if (verbose)
		    semsg(_(e_expected_dot_after_name_str),
					name_start != NULL ? name_start: *arg);
		ret = FAIL;
		break;
	    }
	    ++*arg;
	    if (IS_WHITE_OR_NUL(**arg))
	    {
		if (verbose)
		    emsg(_(e_no_white_space_allowed_after_dot));
		ret = FAIL;
		break;
	    }

	    // isolate the name
	    exp_name = *arg;
	    while (eval_isnamec(**arg))
		++*arg;
	    cc = **arg;
	    **arg = NUL;

	    idx = find_exported(rettv->vval.v_number, exp_name, &ufunc, &type,
		       evalarg == NULL ? NULL : evalarg->eval_cctx,
		       evalarg == NULL ? NULL : evalarg->eval_cstack, verbose);
	    **arg = cc;

	    if (idx < 0 && ufunc == NULL)
	    {
		ret = FAIL;
		break;
	    }
	    if (idx >= 0)
	    {
		scriptitem_T    *si = SCRIPT_ITEM(rettv->vval.v_number);
		svar_T		*sv = ((svar_T *)si->sn_var_vals.ga_data) + idx;

		copy_tv(sv->sv_tv, rettv);
	    }
	    else
	    {
		rettv->v_type = VAR_FUNC;
		rettv->vval.v_string = vim_strsave(ufunc->uf_name);
	    }
	    continue;
	}

	if ((**arg == '(' && (!evaluate || rettv->v_type == VAR_FUNC
			    || rettv->v_type == VAR_PARTIAL))
		    && (!check_white || !VIM_ISWHITE(*(*arg - 1))))
	{
	    ret = call_func_rettv(arg, evalarg, rettv, evaluate,
							       selfdict, NULL);

	    // Stop the expression evaluation when immediately aborting on
	    // error, or when an interrupt occurred or an exception was thrown
	    // but not caught.
	    if (aborting())
	    {
		if (ret == OK)
		    clear_tv(rettv);
		ret = FAIL;
	    }
	    dict_unref(selfdict);
	    selfdict = NULL;
	}
	else if (p[0] == '-' && p[1] == '>')
	{
	    if (in_vim9script())
		*arg = skipwhite(p + 2);
	    else
		*arg = p + 2;
	    if (VIM_ISWHITE(**arg))
	    {
		emsg(_(e_no_white_space_allowed_before_parenthesis));
		ret = FAIL;
	    }
	    else if ((**arg == '{' && !in_vim9script()) || **arg == '(')
		// expr->{lambda}() or expr->(lambda)()
		ret = eval_lambda(arg, rettv, evalarg, verbose);
	    else
		// expr->name()
		ret = eval_method(arg, rettv, evalarg, verbose);
	}
	// "." is ".name" lookup when we found a dict or when evaluating and
	// scriptversion is at least 2, where string concatenation is "..".
	else if (**arg == '['
		|| (**arg == '.' && (rettv->v_type == VAR_DICT
			|| (!evaluate
			    && (*arg)[1] != '.'
			    && !in_old_script(2)))))
	{
	    dict_unref(selfdict);
	    if (rettv->v_type == VAR_DICT)
	    {
		selfdict = rettv->vval.v_dict;
		if (selfdict != NULL)
		    ++selfdict->dv_refcount;
	    }
	    else
		selfdict = NULL;
	    if (eval_index(arg, rettv, evalarg, verbose) == FAIL)
	    {
		clear_tv(rettv);
		ret = FAIL;
	    }
	}
	else if (**arg == '.' && (rettv->v_type == VAR_CLASS
					       || rettv->v_type == VAR_OBJECT))
	{
	    // class member: SomeClass.varname
	    // class method: SomeClass.SomeMethod()
	    // class constructor: SomeClass.new()
	    // object member: someObject.varname
	    // object method: someObject.SomeMethod()
	    if (class_object_index(arg, rettv, evalarg, verbose) == FAIL)
	    {
		clear_tv(rettv);
		ret = FAIL;
	    }
	}
	else
	    break;
    }

    // Turn "dict.Func" into a partial for "Func" bound to "dict".
    // Don't do this when "Func" is already a partial that was bound
    // explicitly (pt_auto is FALSE).
    if (selfdict != NULL
	    && (rettv->v_type == VAR_FUNC
		|| (rettv->v_type == VAR_PARTIAL
		    && (rettv->vval.v_partial->pt_auto
			|| rettv->vval.v_partial->pt_dict == NULL))))
	selfdict = make_partial(selfdict, rettv);

    dict_unref(selfdict);
    return ret;
}

// FROM: vim/src/eval.c
    static int
eval9(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		want_string)	// after "." operator
{
    int		evaluate = evalarg != NULL
				      && (evalarg->eval_flags & EVAL_EVALUATE);
    int		len;
    char_u	*s;
    char_u	*name_start = NULL;
    char_u	*start_leader, *end_leader;
    int		ret = OK;
    char_u	*alias;
    static int	recurse = 0;
    int		vim9script = in_vim9script();

    /*
     * Initialise variable so that clear_tv() can't mistake this for a
     * string and free a string that isn't there.
     */
    rettv->v_type = VAR_UNKNOWN;

    /*
     * Skip '!', '-' and '+' characters.  They are handled later.
     */
    start_leader = *arg;
    if (eval_leader(arg, vim9script) == FAIL)
	return FAIL;
    end_leader = *arg;

    if (**arg == '.' && (!isdigit(*(*arg + 1)) || in_old_script(2)))
    {
	semsg(_(e_invalid_expression_str), *arg);
	++*arg;
	return FAIL;
    }

    // Limit recursion to 1000 levels.  At least at 10000 we run out of stack
    // and crash.  With MSVC the stack is smaller.
    if (recurse ==
#ifdef _MSC_VER
		    300
#else
		    1000
#endif
		    )
    {
	semsg(_(e_expression_too_recursive_str), *arg);
	return FAIL;
    }
    ++recurse;

    switch (**arg)
    {
    /*
     * Number constant.
     */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':	ret = eval_number(arg, rettv, evaluate, want_string);

		// Apply prefixed "-" and "+" now.  Matters especially when
		// "->" follows.
		if (ret == OK && evaluate && end_leader > start_leader
						  && rettv->v_type != VAR_BLOB)
		    ret = eval9_leader(rettv, TRUE, start_leader, &end_leader);
		break;

    /*
     * String constant: "string".
     */
    case '"':	ret = eval_string(arg, rettv, evaluate, FALSE);
		break;

    /*
     * Literal string constant: 'str''ing'.
     */
    case '\'':	ret = eval_lit_string(arg, rettv, evaluate, FALSE);
		break;

    /*
     * List: [expr, expr]
     */
    case '[':	ret = eval_list(arg, rettv, evalarg, TRUE);
		break;

    /*
     * Dictionary: #{key: val, key: val}
     */
    case '#':	if (vim9script)
		{
		    ret = vim9_bad_comment(*arg) ? FAIL : NOTDONE;
		}
		else if ((*arg)[1] == '{')
		{
		    ++*arg;
		    ret = eval_dict(arg, rettv, evalarg, TRUE);
		}
		else
		    ret = NOTDONE;
		break;

    /*
     * Lambda: {arg, arg -> expr}
     * Dictionary: {'key': val, 'key': val}
     */
    case '{':	if (vim9script)
		    ret = NOTDONE;
		else
		    ret = get_lambda_tv(arg, rettv, vim9script, evalarg);
		if (ret == NOTDONE)
		    ret = eval_dict(arg, rettv, evalarg, FALSE);
		break;

    /*
     * Option value: &name
     */
    case '&':	ret = eval_option(arg, rettv, evaluate);
		break;

    /*
     * Environment variable: $VAR.
     * Interpolated string: $"string" or $'string'.
     */
    case '$':	if ((*arg)[1] == '"' || (*arg)[1] == '\'')
		    ret = eval_interp_string(arg, rettv, evaluate);
		else
		    ret = eval_env_var(arg, rettv, evaluate);
		break;

    /*
     * Register contents: @r.
     */
    case '@':	++*arg;
		if (evaluate)
		{
		    if (vim9script && IS_WHITE_OR_NUL(**arg))
			semsg(_(e_syntax_error_at_str), *arg);
		    else if (vim9script && !valid_yank_reg(**arg, FALSE))
			emsg_invreg(**arg);
		    else
		    {
			rettv->v_type = VAR_STRING;
			rettv->vval.v_string = get_reg_contents(**arg,
								GREG_EXPR_SRC);
		    }
		}
		if (**arg != NUL)
		    ++*arg;
		break;

    /*
     * nested expression: (expression).
     * or lambda: (arg) => expr
     */
    case '(':	ret = NOTDONE;
		if (vim9script)
		{
		    ret = get_lambda_tv(arg, rettv, TRUE, evalarg);
		    if (ret == OK && evaluate)
		    {
			ufunc_T *ufunc = rettv->vval.v_partial->pt_func;

			// Compile it here to get the return type.  The return
			// type is optional, when it's missing use t_unknown.
			// This is recognized in compile_return().
			if (ufunc->uf_ret_type->tt_type == VAR_VOID)
			    ufunc->uf_ret_type = &t_unknown;
			if (compile_def_function(ufunc, FALSE,
					get_compile_type(ufunc), NULL) == FAIL)
			{
			    clear_tv(rettv);
			    ret = FAIL;
			}
		    }
		}
		if (ret == NOTDONE)
		{
		    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
		    ret = eval1(arg, rettv, evalarg);	// recursive!

		    *arg = skipwhite_and_linebreak(*arg, evalarg);
		    if (**arg == ')')
			++*arg;
		    else if (ret == OK)
		    {
			emsg(_(e_missing_closing_paren));
			clear_tv(rettv);
			ret = FAIL;
		    }
		}
		break;

    default:	ret = NOTDONE;
		break;
    }

    if (ret == NOTDONE)
    {
	/*
	 * Must be a variable or function name.
	 * Can also be a curly-braces kind of name: {expr}.
	 */
	s = *arg;
	len = get_name_len(arg, &alias, evaluate, TRUE);
	if (alias != NULL)
	    s = alias;

	if (len <= 0)
	    ret = FAIL;
	else
	{
	    int	    flags = evalarg == NULL ? 0 : evalarg->eval_flags;

	    if (evaluate && vim9script && len == 1 && *s == '_')
	    {
		emsg(_(e_cannot_use_underscore_here));
		ret = FAIL;
	    }
	    else if (evaluate && vim9script && len > 2
						 && s[0] == 's' && s[1] == ':')
	    {
		semsg(_(e_cannot_use_s_colon_in_vim9_script_str), s);
		ret = FAIL;
	    }
	    else if ((vim9script ? **arg : *skipwhite(*arg)) == '(')
	    {
		// "name(..."  recursive!
		*arg = skipwhite(*arg);
		ret = eval_func(arg, evalarg, s, len, rettv, flags, NULL);
	    }
	    else if (flags & EVAL_CONSTANT)
		ret = FAIL;
	    else if (evaluate)
	    {
		// get the value of "true", "false", etc. or a variable
		ret = FAIL;
		if (vim9script)
		    ret = handle_predefined(s, len, rettv);
		if (ret == FAIL)
		{
		    name_start = s;
		    ret = eval_variable(s, len, 0, rettv, NULL,
					   EVAL_VAR_VERBOSE + EVAL_VAR_IMPORT);
		}
	    }
	    else
	    {
		// skip the name
		check_vars(s, len);
		ret = OK;
	    }
	}
	vim_free(alias);
    }

    // Handle following '[', '(' and '.' for expr[expr], expr.name,
    // expr(expr), expr->name(expr)
    if (ret == OK)
	ret = handle_subscript(arg, name_start, rettv, evalarg, evaluate);

    /*
     * Apply logical NOT and unary '-', from right to left, ignore '+'.
     */
    if (ret == OK && evaluate && end_leader > start_leader)
	ret = eval9_leader(rettv, FALSE, start_leader, &end_leader);

    --recurse;
    return ret;
}
