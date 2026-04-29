#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct evalarg_S evalarg_T;
typedef struct ufunc_S ufunc_T;
typedef struct partial_S partial_T;
typedef struct tuple_S tuple_T;
typedef struct cctx_S cctx_T;
typedef struct cstack_S cstack_T;
typedef struct typval_S typval_T;
typedef struct type_S type_T;

typedef unsigned char char_u;
typedef signed char int8_T;
typedef double float_T;
typedef long varnumber_T;
typedef long linenr_T;
typedef int colnr_T;

typedef struct {
    int	    ga_len;		    // number of items used
    int	    ga_maxlen;	    // maximum number of items possible
    int	    ga_itemsize;	    // sizeof(item)
    int	    ga_growsize;	    // number of items to grow each time
    void    *ga_data;		    // pointer to the first item
} garray_T;

typedef enum {
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
    VAR_TYPEALIAS,
    VAR_TUPLE
} vartype_T;

struct typval_S {
    vartype_T	v_type;
    char	v_lock;
    union {
	varnumber_T	v_number;
	float_T		v_float;
	char_u		*v_string;
	void		*v_list;
	void		*v_dict;
	partial_T	*v_partial;
	void		*v_blob;
	void		*v_tuple;
    }		vval;
};

typedef enum {
    EXPR_UNKNOWN = 0,
    EXPR_EQUAL,
    EXPR_NEQUAL,
    EXPR_GREATER,
    EXPR_GEQUAL,
    EXPR_SMALLER,
    EXPR_SEQUAL,
    EXPR_MATCH,
    EXPR_NOMATCH,
    EXPR_IS,
    EXPR_ISNOT,
    EXPR_ADD,
    EXPR_SUB,
    EXPR_MULT,
    EXPR_DIV,
    EXPR_REM,
    EXPR_LSHIFT,
    EXPR_RSHIFT,
    EXPR_COPY,
    EXPR_APPEND,
} exprtype_T;

struct type_S {
    vartype_T	    tt_type;
    int8_T	    tt_argcount;
    int8_T	    tt_min_argcount;
    char_u	    tt_flags;
    void	    *tt_member;
    void	    *tt_class;
    void	    **tt_args;
};
typedef struct type_S type_T;

struct partial_S {
    ufunc_T	*pt_func;	// function
    void	*pt_data;	// dummy
};

struct ufunc_S {
    type_T	*uf_ret_type;	// return type
    void	*uf_data;	// dummy
};

struct tuple_S {
    garray_T	tv_items;	// items in the tuple
};

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
typedef struct evalarg_S evalarg_T;

#define NUL		'\000'
#define OK		1
#define FAIL		0
#define NOTDONE		2
#define TRUE		1
#define FALSE		0
#define VVAL_TRUE	1L
#define VVAL_FALSE	0L
#define CLEAR_POINTER(ptr)  memset((ptr), 0, sizeof(*(ptr)))
#define CLEAR_FIELD(field)  memset(&(field), 0, sizeof(field))
#define VIM_ISWHITE(x)		((x) == ' ' || (x) == '\t')
#define IS_WHITE_OR_NUL(x)	((x) == ' ' || (x) == '\t' || (x) == NUL)
#define SAFE_isdigit(c)  (isdigit ((unsigned char)(c)))
#define STRNCMP(d, s, n)    strncmp((char *)(d), (char *)(s), (size_t)(n))
#define EVAL_EVALUATE	    1
#define TVTT_DO_MEMBER	    1
#define TTFLAG_BOOL_OK	    0x02
#define TUPLE_LEN(t)	    ((t)->tv_items.ga_len)
#define TUPLE_ITEM(t, i)    ((typval_T **)(t)->tv_items.ga_data)[i]
#define WHERE_INIT {NULL, 0, 0}
#define WT_UNKNOWN 0

#define _(x) ((char *)(x))

#define e_missing_closing_paren "E110: Missing ')'"
#define e_missing_colon_after_questionmark "E109: Missing ':' after '?'"
#define e_bitshift_ops_must_be_number "E112: Bitshift operators must be number"
#define e_invalid_expression_str "E113: Invalid expression: %s"
#define e_white_space_required_after_str_str "E114: White space required after '%s'"
#define e_no_white_space_allowed_before_str_str "E115: No white space allowed before '%s'"
#define e_missing_comma_in_tuple_str "E116: Missing comma in tuple: %s"
#define e_missing_end_of_tuple_rsp_str "E117: Missing ')' in tuple: %s"
#define e_expression_too_recursive_str "E118: Expression too recursive: %s"

extern int in_free_unref_items;
extern linenr_T SOURCING_LNUM;
extern int p_ic;
extern type_T t_unknown;
extern int in_vim9script(void);

#define IS_WHITE_NL_OR_NUL(x)	((x) == ' ' || (x) == '\t' || (x) == '\n' || (x) == '\r' || (x) == NUL)
#define e_missing_gt "E111: Missing '>'"

void emsg(const char *msg);
char *tv_get_string_chk(typval_T *tv);
int eval_multdiv_number(typval_T *tv1, typval_T *tv2, int op);
int eval_isnamec1(char c);
void ga_init2(garray_T *gap, int itemsize, int growsize);
typedef struct { char *w_where; int w_len; int w_type; } where_T;
tuple_T *tuple_alloc(void);

static int eval9_nested_expr(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int evaluate);
int eval1(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval2(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval3(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval4(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval5(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval6(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
static int eval7(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int want_string);
static int eval8(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int want_string);
static int eval9(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int want_string);
int eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error);
static int eval_leader(char_u **arg, int vim9script);
static int eval9_leader(typval_T *rettv, int, char_u *start_leader, char_u **end_leader);
int tuple_append_tv(tuple_T *tuple, typval_T *tv);
void tuple_set_item(tuple_T *tuple, int idx, typval_T *tv);
void tuple_free(tuple_T *tuple);
static void tuple_free_contents(tuple_T *tuple);
int check_typval_is_value(typval_T *tv);
int get_compare_type(char_u *p, int *len, int *type_is);
int typval_compare(typval_T *tv1, typval_T *tv2, exprtype_T type, int ic);
int eval_shift_number(typval_T *tv1, typval_T *tv2, exprtype_T type);
int eval_concat_str(typval_T *tv1, typval_T *tv2);
void eval_addblob(typval_T *tv1, typval_T *tv2);
int eval_addlist(typval_T *tv1, typval_T *tv2);
int eval_addtuple(typval_T *tv1, typval_T *tv2);
int eval_addsub_number(typval_T *tv1, typval_T *tv2, int op);
type_T *parse_type(char_u **arg, garray_T *type_list, int);
void clear_type_list(garray_T *type_list);
type_T *typval2type(typval_T *tv, int copyID, garray_T *type_list, int flags);
int equal_type(type_T *type1, type_T *type2, int);
int check_type(type_T *want_type, type_T *actual, int, where_T where);
int handle_subscript(char_u **arg, char_u *name_start, typval_T *rettv, evalarg_T *evalarg, int evaluate);
int eval9_var_func_name(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int evaluate, char_u **name_start);
void eval9_reg_contents(char_u **arg, typval_T *rettv, int evaluate);
int eval_env_var(char_u **arg, typval_T *rettv, int evaluate);
int eval_interp_string(char_u **arg, typval_T *rettv, int evaluate);
int eval_option(char_u **arg, typval_T *rettv, int evaluate);
int eval_dict(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int);
int eval_lit_dict(char_u **arg, typval_T *rettv, evalarg_T *evalarg);
int eval_list(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int);
int eval_lit_string(char_u **arg, typval_T *rettv, int evaluate, int);
int eval_string(char_u **arg, typval_T *rettv, int evaluate, int);
int eval_number(char_u **arg, typval_T *rettv, int evaluate, int want_string);
int in_old_script(int version);
int init_evalarg(evalarg_T *evalarg);
void clear_evalarg(evalarg_T *evalarg, void *);
int get_copyID(void);
void semsg(const char *msg, ...);
int tv2bool(typval_T *tv);
int check_compare_types(exprtype_T type, typval_T *tv1, typval_T *tv2);
int tv_get_bool_chk(typval_T *tv, int *error);
int tv_get_number_chk(typval_T *tv, int *error);
void error_white_both(char_u *arg, int len);
char_u *eval_next_non_blank(char_u *arg, evalarg_T *evalarg, int *getnext);
char_u *eval_next_line(char_u *arg, evalarg_T *evalarg);
char_u *skipwhite(char_u *arg);
char_u *skipwhite_and_linebreak(char_u *arg, evalarg_T *evalarg);
int get_lambda_tv(char_u **arg, typval_T *rettv, int, evalarg_T *evalarg);
int compile_def_function(ufunc_T *ufunc, int, type_T *, void *);
type_T *get_compile_type(ufunc_T *ufunc);
void clear_tv(typval_T *tv);
int rettv_tuple_set(typval_T *rettv, tuple_T *tuple);
int ga_grow(garray_T *gap, int n);
void tuple_free_list(tuple_T *tuple);
void ga_clear(garray_T *gap);

    static int
eval9_nested_expr(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		evaluate)
{
    int		ret = NOTDONE;
    int		vim9script = in_vim9script();

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
	if (**arg == ')')
	    // empty tuple
	    ret = eval_tuple(arg, rettv, evalarg, TRUE);
	else
	{
	    ret = eval1(arg, rettv, evalarg);	// recursive!
      if (ret != OK)
		return ret;

	    *arg = skipwhite_and_linebreak(*arg, evalarg);

	    if (**arg == ',')
		// tuple
		ret = eval_tuple(arg, rettv, evalarg, TRUE);
	    else if (**arg == ')')
		++*arg;
	    else if (ret == OK)
	    {
		emsg(_(e_missing_closing_paren));
		clear_tv(rettv);
		ret = FAIL;
	    }
	}
    }

    return ret;
}

    int
eval1(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    char_u  *p;
    int	    getnext;

    CLEAR_POINTER(rettv);

    /*
     * Get the first variable.
     */
    if (eval2(arg, rettv, evalarg) == FAIL)
	return FAIL;

    p = eval_next_non_blank(*arg, evalarg, &getnext);
    if (*p == '?')
    {
	int		op_falsy = p[1] == '?';
	int		result;
	typval_T	var2;
	evalarg_T	*evalarg_used = evalarg;
	evalarg_T	local_evalarg;
	int		orig_flags;
	int		evaluate;
	int		vim9script = in_vim9script();

	if (evalarg == NULL)
	{
	    init_evalarg(&local_evalarg);
	    evalarg_used = &local_evalarg;
	}
	orig_flags = evalarg_used->eval_flags;
	evaluate = evalarg_used->eval_flags & EVAL_EVALUATE;

	if (getnext)
	    *arg = eval_next_line(*arg, evalarg_used);
	else
	{
	    if (evaluate && vim9script && !VIM_ISWHITE(p[-1]))
	    {
		error_white_both(p, op_falsy ? 2 : 1);
		clear_tv(rettv);
		return FAIL;
	    }
	    *arg = p;
	}

	result = FALSE;
	if (evaluate)
	{
	    int		error = FALSE;

	    if (op_falsy)
		result = tv2bool(rettv);
	    else if (vim9script)
		result = tv_get_bool_chk(rettv, &error);
	    else if (tv_get_number_chk(rettv, &error) != 0)
		result = TRUE;
	    if (error || !op_falsy || !result)
		clear_tv(rettv);
	    if (error)
		return FAIL;
	}

	/*
	 * Get the second variable.  Recursive!
	 */
	if (op_falsy)
	    ++*arg;
	if (evaluate && vim9script && !IS_WHITE_OR_NUL((*arg)[1]))
	{
	    error_white_both(*arg - (op_falsy ? 1 : 0), op_falsy ? 2 : 1);
	    clear_tv(rettv);
	    return FAIL;
	}
	*arg = skipwhite_and_linebreak(*arg + 1, evalarg_used);
	evalarg_used->eval_flags = (op_falsy ? !result : result)
				  ? orig_flags : (orig_flags & ~EVAL_EVALUATE);
	if (eval1(arg, &var2, evalarg_used) == FAIL)
	{
	    evalarg_used->eval_flags = orig_flags;
	    return FAIL;
	}
	if (!op_falsy || !result)
	    *rettv = var2;

	if (!op_falsy)
	{
	    /*
	     * Check for the ":".
	     */
	    p = eval_next_non_blank(*arg, evalarg_used, &getnext);
	    if (*p != ':')
	    {
		emsg(_(e_missing_colon_after_questionmark));
		if (evaluate && result)
		    clear_tv(rettv);
		evalarg_used->eval_flags = orig_flags;
		return FAIL;
	    }
	    if (getnext)
		*arg = eval_next_line(*arg, evalarg_used);
	    else
	    {
		if (evaluate && vim9script && !VIM_ISWHITE(p[-1]))
		{
		    error_white_both(p, 1);
		    clear_tv(rettv);
		    evalarg_used->eval_flags = orig_flags;
		    return FAIL;
		}
		*arg = p;
	    }

	    /*
	     * Get the third variable.  Recursive!
	     */
	    if (evaluate && vim9script && !IS_WHITE_OR_NUL((*arg)[1]))
	    {
		error_white_both(*arg, 1);
		clear_tv(rettv);
		evalarg_used->eval_flags = orig_flags;
		return FAIL;
	    }
	    *arg = skipwhite_and_linebreak(*arg + 1, evalarg_used);
	    evalarg_used->eval_flags = !result ? orig_flags
					       : (orig_flags & ~EVAL_EVALUATE);
	    if (eval1(arg, &var2, evalarg_used) == FAIL)
	    {
		if (evaluate && result)
		    clear_tv(rettv);
		evalarg_used->eval_flags = orig_flags;
		return FAIL;
	    }
	    if (evaluate && !result)
		*rettv = var2;
	}

	if (evalarg == NULL)
	    clear_evalarg(&local_evalarg, NULL);
	else
	    evalarg->eval_flags = orig_flags;
    }

    return OK;
}

    static int
eval2(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    char_u	*p;
    int		getnext;

    /*
     * Get the first expression.
     */
    if (eval3(arg, rettv, evalarg) == FAIL)
	return FAIL;

    /*
     * Handle the  "||" operator.
     */
    p = eval_next_non_blank(*arg, evalarg, &getnext);
    if (p[0] == '|' && p[1] == '|')
    {
	evalarg_T   *evalarg_used = evalarg;
	evalarg_T   local_evalarg;
	int	    evaluate;
	int	    orig_flags;
	long	    result = FALSE;
	typval_T    var2;
	int	    error = FALSE;
	int	    vim9script = in_vim9script();

	if (evalarg == NULL)
	{
	    init_evalarg(&local_evalarg);
	    evalarg_used = &local_evalarg;
	}
	orig_flags = evalarg_used->eval_flags;
	evaluate = orig_flags & EVAL_EVALUATE;
	if (evaluate)
	{
	    if (vim9script)
		result = tv_get_bool_chk(rettv, &error);
	    else if (tv_get_number_chk(rettv, &error) != 0)
		result = TRUE;
	    clear_tv(rettv);
	    if (error)
		return FAIL;
	}

	/*
	 * Repeat until there is no following "||".
	 */
	while (p[0] == '|' && p[1] == '|')
	{
	    if (getnext)
		*arg = eval_next_line(*arg, evalarg_used);
	    else
	    {
		if (evaluate && vim9script && !VIM_ISWHITE(p[-1]))
		{
		    error_white_both(p, 2);
		    clear_tv(rettv);
		    return FAIL;
		}
		*arg = p;
	    }

	    /*
	     * Get the second variable.
	     */
	    if (evaluate && vim9script && !IS_WHITE_OR_NUL((*arg)[2]))
	    {
		error_white_both(*arg, 2);
		clear_tv(rettv);
		return FAIL;
	    }
	    *arg = skipwhite_and_linebreak(*arg + 2, evalarg_used);
	    evalarg_used->eval_flags = !result ? orig_flags
					       : (orig_flags & ~EVAL_EVALUATE);
	    if (eval3(arg, &var2, evalarg_used) == FAIL)
		return FAIL;

	    /*
	     * Compute the result.
	     */
	    if (evaluate && !result)
	    {
		if (vim9script)
		    result = tv_get_bool_chk(&var2, &error);
		else if (tv_get_number_chk(&var2, &error) != 0)
		    result = TRUE;
		clear_tv(&var2);
		if (error)
		    return FAIL;
	    }
	    if (evaluate)
	    {
		if (vim9script)
		{
		    rettv->v_type = VAR_BOOL;
		    rettv->vval.v_number = result ? VVAL_TRUE : VVAL_FALSE;
		}
		else
		{
		    rettv->v_type = VAR_NUMBER;
		    rettv->vval.v_number = result;
		}
	    }

	    p = eval_next_non_blank(*arg, evalarg_used, &getnext);
	}

	if (evalarg == NULL)
	    clear_evalarg(&local_evalarg, NULL);
	else
	    evalarg->eval_flags = orig_flags;
    }

    return OK;
}

    static int
eval3(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    char_u	*p;
    int		getnext;

    /*
     * Get the first expression.
     */
    if (eval4(arg, rettv, evalarg) == FAIL)
	return FAIL;

    /*
     * Handle the "&&" operator.
     */
    p = eval_next_non_blank(*arg, evalarg, &getnext);
    if (p[0] == '&' && p[1] == '&')
    {
	evalarg_T   *evalarg_used = evalarg;
	evalarg_T   local_evalarg;
	int	    orig_flags;
	int	    evaluate;
	long	    result = TRUE;
	typval_T    var2;
	int	    error = FALSE;
	int	    vim9script = in_vim9script();

	if (evalarg == NULL)
	{
	    init_evalarg(&local_evalarg);
	    evalarg_used = &local_evalarg;
	}
	orig_flags = evalarg_used->eval_flags;
	evaluate = orig_flags & EVAL_EVALUATE;
	if (evaluate)
	{
	    if (vim9script)
		result = tv_get_bool_chk(rettv, &error);
	    else if (tv_get_number_chk(rettv, &error) == 0)
		result = FALSE;
	    clear_tv(rettv);
	    if (error)
		return FAIL;
	}

	/*
	 * Repeat until there is no following "&&".
	 */
	while (p[0] == '&' && p[1] == '&')
	{
	    if (getnext)
		*arg = eval_next_line(*arg, evalarg_used);
	    else
	    {
		if (evaluate && vim9script && !VIM_ISWHITE(p[-1]))
		{
		    error_white_both(p, 2);
		    clear_tv(rettv);
		    return FAIL;
		}
		*arg = p;
	    }

	    /*
	     * Get the second variable.
	     */
	    if (evaluate && vim9script && !IS_WHITE_OR_NUL((*arg)[2]))
	    {
		error_white_both(*arg, 2);
		clear_tv(rettv);
		return FAIL;
	    }
	    *arg = skipwhite_and_linebreak(*arg + 2, evalarg_used);
	    evalarg_used->eval_flags = result ? orig_flags
					      : (orig_flags & ~EVAL_EVALUATE);
	    CLEAR_FIELD(var2);
	    if (eval4(arg, &var2, evalarg_used) == FAIL)
		return FAIL;

	    /*
	     * Compute the result.
	     */
	    if (evaluate && result)
	    {
		if (vim9script)
		    result = tv_get_bool_chk(&var2, &error);
		else if (tv_get_number_chk(&var2, &error) == 0)
		    result = FALSE;
		clear_tv(&var2);
		if (error)
		    return FAIL;
	    }
	    if (evaluate)
	    {
		if (vim9script)
		{
		    rettv->v_type = VAR_BOOL;
		    rettv->vval.v_number = result ? VVAL_TRUE : VVAL_FALSE;
		}
		else
		{
		    rettv->v_type = VAR_NUMBER;
		    rettv->vval.v_number = result;
		}
	    }

	    p = eval_next_non_blank(*arg, evalarg_used, &getnext);
	}

	if (evalarg == NULL)
	    clear_evalarg(&local_evalarg, NULL);
	else
	    evalarg->eval_flags = orig_flags;
    }

    return OK;
}

    static int
eval4(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    char_u	*p;
    int		getnext;
    exprtype_T	type = EXPR_UNKNOWN;
    int		len = 2;
    int		type_is = FALSE;

    /*
     * Get the first expression.
     */
    if (eval5(arg, rettv, evalarg) == FAIL)
	return FAIL;

    p = eval_next_non_blank(*arg, evalarg, &getnext);

    type = get_compare_type(p, &len, &type_is);

    /*
     * If there is a comparative operator, use it.
     */
    if (type != EXPR_UNKNOWN)
    {
	typval_T    var2;
	int	    ic;
	int	    vim9script = in_vim9script();
	int	    evaluate = evalarg == NULL
				   ? 0 : (evalarg->eval_flags & EVAL_EVALUATE);
	long	    comp_lnum = SOURCING_LNUM;

	if (getnext)
	{
	    *arg = eval_next_line(*arg, evalarg);
	    p = *arg;
	}
	else if (evaluate && vim9script && !VIM_ISWHITE(**arg))
	{
	    error_white_both(*arg, len);
	    clear_tv(rettv);
	    return FAIL;
	}

	if (vim9script && type_is && (p[len] == '?' || p[len] == '#'))
	{
	    semsg(_(e_invalid_expression_str), p);
	    clear_tv(rettv);
	    return FAIL;
	}

	// extra question mark appended: ignore case
	if (p[len] == '?')
	{
	    ic = TRUE;
	    ++len;
	}
	// extra '#' appended: match case
	else if (p[len] == '#')
	{
	    ic = FALSE;
	    ++len;
	}
	// nothing appended: use 'ignorecase' if not in Vim script
	else
	    ic = vim9script ? FALSE : p_ic;

	/*
	 * Get the second variable.
	 */
	if (evaluate && vim9script && !IS_WHITE_OR_NUL(p[len]))
	{
	    error_white_both(p, len);
	    clear_tv(rettv);
	    return FAIL;
	}
	*arg = skipwhite_and_linebreak(p + len, evalarg);
	if (eval5(arg, &var2, evalarg) == FAIL)
	{
	    clear_tv(rettv);
	    return FAIL;
	}
	if (evaluate)
	{
	    int ret;

	    // use the line of the comparison for messages
	    SOURCING_LNUM = comp_lnum;
	    if (vim9script && check_compare_types(type, rettv, &var2) == FAIL)
	    {
		ret = FAIL;
		clear_tv(rettv);
	    }
	    else
		ret = typval_compare(rettv, &var2, type, ic);
	    clear_tv(&var2);
	    return ret;
	}
    }

    return OK;
}

    static int
eval5(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    /*
     * Get the first expression.
     */
    if (eval6(arg, rettv, evalarg) == FAIL)
	return FAIL;

    /*
     * Repeat computing, until no '<<' or '>>' is following.
     */
    for (;;)
    {
	char_u		*p;
	int		getnext;
	exprtype_T	exprtype;
	int		evaluate;
	typval_T	var2;
	int		vim9script;

	p = eval_next_non_blank(*arg, evalarg, &getnext);
	if (p[0] == '<' && p[1] == '<')
	    exprtype = EXPR_LSHIFT;
	else if (p[0] == '>' && p[1] == '>')
	    exprtype = EXPR_RSHIFT;
	else
	    return OK;

	// Handle a bitwise left or right shift operator
	evaluate = evalarg == NULL ? 0 : (evalarg->eval_flags & EVAL_EVALUATE);
	if (evaluate && rettv->v_type != VAR_NUMBER)
	{
	    // left operand should be a number
	    emsg(_(e_bitshift_ops_must_be_number));
	    clear_tv(rettv);
	    return FAIL;
	}

	vim9script = in_vim9script();
	if (getnext)
	{
	    *arg = eval_next_line(*arg, evalarg);
	    p = *arg;
	}
	else if (evaluate && vim9script && !VIM_ISWHITE(**arg))
	{
	    error_white_both(*arg, 2);
	    clear_tv(rettv);
	    return FAIL;
	}

	/*
	 * Get the second variable.
	 */
	if (evaluate && vim9script && !IS_WHITE_OR_NUL(p[2]))
	{
	    error_white_both(p, 2);
	    clear_tv(rettv);
	    return FAIL;
	}
	*arg = skipwhite_and_linebreak(p + 2, evalarg);
	if (eval6(arg, &var2, evalarg) == FAIL)
	{
	    clear_tv(rettv);
	    return FAIL;
	}

	if (evaluate)
	{
	    if (eval_shift_number(rettv, &var2, exprtype) == FAIL)
		return FAIL;
	}

	clear_tv(&var2);
    }

    return OK;
}

    static int
eval6(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    /*
     * Get the first expression.
     */
    if (eval7(arg, rettv, evalarg, FALSE) == FAIL)
	return FAIL;

    /*
     * Repeat computing, until no '+', '-' or '.' is following.
     */
    for (;;)
    {
	int	    evaluate;
	int	    getnext;
	char_u	    *p;
	int	    op;
	int	    oplen;
	int	    concat;
	typval_T    var2;
	int	    vim9script = in_vim9script();
	long	    op_lnum = SOURCING_LNUM;

	// "." is only string concatenation when scriptversion is 1
	// "+=", "-=" and "..=" are assignments
	// "++" and "--" on the next line are a separate command.
	p = eval_next_non_blank(*arg, evalarg, &getnext);
	op = *p;
	concat = op == '.' && (*(p + 1) == '.' || in_old_script(2));
	if ((op != '+' && op != '-' && !concat) || p[1] == '='
					       || (p[1] == '.' && p[2] == '='))
	    break;
	if (getnext && (op == '+' || op == '-') && p[0] == p[1])
	    break;

	evaluate = evalarg == NULL ? 0 : (evalarg->eval_flags & EVAL_EVALUATE);
	oplen = (concat && p[1] == '.') ? 2 : 1;
	if (getnext)
	    *arg = eval_next_line(*arg, evalarg);
	else
	{
	    if (evaluate && vim9script && !VIM_ISWHITE(**arg))
	    {
		error_white_both(*arg, oplen);
		clear_tv(rettv);
		return FAIL;
	    }
	    *arg = p;
	}
	if ((op != '+' || (rettv->v_type != VAR_LIST
						&& rettv->v_type != VAR_TUPLE
						&& rettv->v_type != VAR_BLOB))
		&& (op == '.' || rettv->v_type != VAR_FLOAT)
		&& evaluate)
	{
	    int		error = FALSE;

	    // For "list + ...", an illegal use of the first operand as
	    // a number cannot be determined before evaluating the 2nd
	    // operand: if this is also a list, all is ok.
	    // For "something . ...", "something - ..." or "non-list + ...",
	    // we know that the first operand needs to be a string or number
	    // without evaluating the 2nd operand.  So check before to avoid
	    // side effects after an error.
	    if (op != '.')
		tv_get_number_chk(rettv, &error);
	    if ((op == '.' && tv_get_string_chk(rettv) == NULL) || error)
	    {
		clear_tv(rettv);
		return FAIL;
	    }
	}

	/*
	 * Get the second variable.
	 */
	if (evaluate && vim9script && !IS_WHITE_OR_NUL((*arg)[oplen]))
	{
	    error_white_both(*arg, oplen);
	    clear_tv(rettv);
	    return FAIL;
	}
	*arg = skipwhite_and_linebreak(*arg + oplen, evalarg);
	if (eval7(arg, &var2, evalarg, !vim9script && op == '.') == FAIL)
	{
	    clear_tv(rettv);
	    return FAIL;
	}

	if (evaluate)
	{
	    /*
	     * Compute the result.
	     */
	    // use the line of the operation for messages
	    SOURCING_LNUM = op_lnum;
	    if (op == '.')
	    {
		if (eval_concat_str(rettv, &var2) == FAIL)
		    return FAIL;
	    }
	    else if (op == '+' && rettv->v_type == VAR_BLOB
						   && var2.v_type == VAR_BLOB)
		eval_addblob(rettv, &var2);
	    else if (op == '+' && rettv->v_type == VAR_LIST
						   && var2.v_type == VAR_LIST)
	    {
		if (eval_addlist(rettv, &var2) == FAIL)
		    return FAIL;
	    }
	    else if (op == '+' && rettv->v_type == VAR_TUPLE
					   && var2.v_type == VAR_TUPLE)
	    {
		if (eval_addtuple(rettv, &var2) == FAIL)
		    return FAIL;
	    }
	    else
	    {
		if (eval_addsub_number(rettv, &var2, op) == FAIL)
		    return FAIL;
	    }
	    clear_tv(&var2);
	}
    }
    return OK;
}

    static int
eval7(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		want_string)  // after "." operator
{
    /*
     * Get the first expression.
     */
    if (eval8(arg, rettv, evalarg, want_string) == FAIL)
	return FAIL;

    /*
     * Repeat computing, until no '*', '/' or '%' is following.
     */
    for (;;)
    {
	int	    evaluate;
	int	    getnext;
	typval_T    var2;
	char_u	    *p;
	int	    op;

	// "*=", "/=" and "%=" are assignments
	p = eval_next_non_blank(*arg, evalarg, &getnext);
	op = *p;
	if ((op != '*' && op != '/' && op != '%') || p[1] == '=')
	    break;

	evaluate = evalarg == NULL ? 0 : (evalarg->eval_flags & EVAL_EVALUATE);
	if (getnext)
	    *arg = eval_next_line(*arg, evalarg);
	else
	{
	    if (evaluate && in_vim9script() && !VIM_ISWHITE(**arg))
	    {
		error_white_both(*arg, 1);
		clear_tv(rettv);
		return FAIL;
	    }
	    *arg = p;
	}

	/*
	 * Get the second variable.
	 */
	if (evaluate && in_vim9script() && !IS_WHITE_OR_NUL((*arg)[1]))
	{
	    error_white_both(*arg, 1);
	    clear_tv(rettv);
	    return FAIL;
	}
	*arg = skipwhite_and_linebreak(*arg + 1, evalarg);
	if (eval8(arg, &var2, evalarg, FALSE) == FAIL)
	    return FAIL;

	if (evaluate)
	    // Compute the result.
	    if (eval_multdiv_number(rettv, &var2, op) == FAIL)
		return FAIL;
    }

    return OK;
}

    static int
eval8(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		want_string)	// after "." operator
{
    type_T	*want_type = NULL;
    garray_T	type_list;	    // list of pointers to allocated types
    int		res;
    int		evaluate = evalarg == NULL ? 0
				       : (evalarg->eval_flags & EVAL_EVALUATE);

    // Recognize <type> in Vim9 script only.
    if (in_vim9script() && **arg == '<' && eval_isnamec1((*arg)[1])
					     && STRNCMP(*arg, "<SNR>", 5) != 0)
    {
	++*arg;
	ga_init2(&type_list, sizeof(type_T *), 10);
	want_type = parse_type(arg, &type_list, TRUE);
	if (want_type == NULL && (evaluate || **arg != '>'))
	{
	    clear_type_list(&type_list);
	    return FAIL;
	}

	if (**arg != '>')
	{
	    if (*skipwhite(*arg) == '>')
		semsg(_(e_no_white_space_allowed_before_str_str), ">", *arg);
	    else
		emsg(_(e_missing_gt));
	    clear_type_list(&type_list);
	    return FAIL;
	}
	++*arg;
	*arg = skipwhite_and_linebreak(*arg, evalarg);
    }

    res = eval9(arg, rettv, evalarg, want_string);

    if (want_type != NULL && evaluate)
    {
	if (res == OK)
	{
	    type_T *actual = typval2type(rettv, get_copyID(), &type_list,
							       TVTT_DO_MEMBER);

	    if (!equal_type(want_type, actual, 0))
	    {
		if (want_type->tt_type == VAR_BOOL
					&& actual->tt_type != VAR_BOOL
					&& (actual->tt_flags & TTFLAG_BOOL_OK))
		{
		    int n = tv2bool(rettv);

		    // can use "0" and "1" for boolean in some places
		    clear_tv(rettv);
		    rettv->v_type = VAR_BOOL;
		    rettv->vval.v_number = n ? VVAL_TRUE : VVAL_FALSE;
		}
		else
		{
		    where_T where = WHERE_INIT;

		    res = check_type(want_type, actual, TRUE, where);
		}
	    }
	}
	clear_type_list(&type_list);
    }

    return res;
}

    static int
eval9(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		want_string)	// after "." operator
{
    int		evaluate = evalarg != NULL
				      && (evalarg->eval_flags & EVAL_EVALUATE);
    char_u	*name_start = NULL;
    char_u	*start_leader, *end_leader;
    int		ret = OK;
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

    if (**arg == '.' && (!SAFE_isdigit(*(*arg + 1)) || in_old_script(2)))
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
     * Literal Dictionary: #{key: val, key: val}
     */
    case '#':	ret = eval_lit_dict(arg, rettv, evalarg);
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
    case '@':	eval9_reg_contents(arg, rettv, evaluate);
		break;

    /*
     * nested expression: (expression).
     * or lambda: (arg) => expr
     * or tuple
     */
    case '(':	ret = eval9_nested_expr(arg, rettv, evalarg, evaluate);
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
	ret = eval9_var_func_name(arg, rettv, evalarg, evaluate, &name_start);
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

    int
eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error)
{
    int		evaluate = evalarg == NULL ? FALSE
					 : evalarg->eval_flags & EVAL_EVALUATE;
    tuple_T	*tuple = NULL;
    typval_T	tv;
    int		vim9script = in_vim9script();
    int		had_comma;

    if (check_typval_is_value(rettv) == FAIL)
    {
	// the first item is not a valid value type
	clear_tv(rettv);
	return FAIL;
    }

    if (evaluate)
    {
	tuple = tuple_alloc();
	if (tuple == NULL)
	    return FAIL;

	if (rettv->v_type != VAR_UNKNOWN)
	{
	    // Add the first item to the tuple from "rettv"
	    if (tuple_append_tv(tuple, rettv) == FAIL)
		return FAIL;
	}
    }

    if (**arg == ')')
	// empty tuple
	goto done;

    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
    {
	semsg(_(e_white_space_required_after_str_str), ",", *arg);
	goto failret;
    }

    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
    while (**arg != ')' && **arg != NUL)
    {
	if (eval1(arg, &tv, evalarg) == FAIL)	// recursive!
	    goto failret;
	if (check_typval_is_value(&tv) == FAIL)
	{
	    if (evaluate)
		clear_tv(&tv);
	    goto failret;
	}

	if (evaluate)
	{
	    if (tuple_append_tv(tuple, &tv) == FAIL)
	    {
		clear_tv(&tv);
		goto failret;
	    }
	}

	if (!vim9script)
	    *arg = skipwhite(*arg);

	// the comma must come after the value
	had_comma = **arg == ',';
	if (had_comma)
	{
	    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
	    {
		semsg(_(e_white_space_required_after_str_str), ",", *arg);
		goto failret;
	    }
	    *arg = skipwhite(*arg + 1);
	}

	// The ")" can be on the next line.  But a double quoted string may
	// follow, not a comment.
	*arg = skipwhite_and_linebreak(*arg, evalarg);
	if (**arg == ')')
	    break;

	if (!had_comma)
	{
	    if (do_error)
	    {
		if (**arg == ',')
		    semsg(_(e_no_white_space_allowed_before_str_str),
								    ",", *arg);
		else
		    semsg(_(e_missing_comma_in_tuple_str), *arg);
	    }
	    goto failret;
	}
    }

    if (**arg != ')')
    {
	if (do_error)
	    semsg(_(e_missing_end_of_tuple_rsp_str), *arg);
failret:
	if (evaluate)
	    tuple_free(tuple);
	return FAIL;
    }

done:
    *arg += 1;
    if (evaluate)
	rettv_tuple_set(rettv, tuple);

    return OK;
}

    int
tuple_append_tv(tuple_T *tuple, typval_T *tv)
{
    if (ga_grow(&tuple->tv_items, 1) == FAIL)
	return FAIL;

    tuple_set_item(tuple, TUPLE_LEN(tuple), tv);

    return OK;
}

    void
tuple_set_item(tuple_T *tuple, int idx, typval_T *tv)
{
    *TUPLE_ITEM(tuple, idx) = *tv;
    tuple->tv_items.ga_len++;
}

    void
tuple_free(tuple_T *tuple)
{
    if (in_free_unref_items)
	return;

    tuple_free_contents(tuple);
    tuple_free_list(tuple);
}

    static void
tuple_free_contents(tuple_T *tuple)
{
    for (int i = 0; i < TUPLE_LEN(tuple); i++)
	clear_tv(TUPLE_ITEM(tuple, i));

    ga_clear(&tuple->tv_items);
}
