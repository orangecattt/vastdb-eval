/* === Dependency Declarations === */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#ifndef INT_MAX
# define INT_MAX       (int)(((unsigned int) ~0) >> 1)
#endif

#define min(X,Y) (((X) < (Y)) ? (X) : (Y))

#define INTBUF_SIZE 32

typedef struct string {
  char *b;
  char *p;
  char *e;
} string;

enum demangling_styles {
  no_demangling = -1,
  unknown_demangling = 0,
  auto_demangling = 1 << 8,
  gnu_demangling = 1 << 9,
  lucid_demangling = 1 << 10,
  arm_demangling = 1 << 11,
  hp_demangling = 1 << 12,
  edg_demangling = 1 << 13,
  gnu_v3_demangling = 1 << 14,
  java_demangling = 1 << 2,
  gnat_demangling = 1 << 15,
  dlang_demangling = 1 << 16,
  rust_demangling = 1 << 17
};

extern enum demangling_styles current_demangling_style;

#define DMGL_NO_OPTS    0
#define DMGL_PARAMS     (1 << 0)
#define DMGL_ANSI       (1 << 1)
#define DMGL_JAVA       (1 << 2)
#define DMGL_AUTO       (1 << 8)
#define DMGL_GNU        (1 << 9)
#define DMGL_LUCID      (1 << 10)
#define DMGL_ARM        (1 << 11)
#define DMGL_HP         (1 << 12)
#define DMGL_EDG        (1 << 13)
#define DMGL_GNU_V3     (1 << 14)

#define CURRENT_DEMANGLING_STYLE current_demangling_style
#define AUTO_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_AUTO)
#define GNU_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_GNU)
#define LUCID_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_LUCID)
#define ARM_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_ARM)
#define HP_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_HP)
#define EDG_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_EDG)
#define JAVA_DEMANGLING (((int) CURRENT_DEMANGLING_STYLE) & DMGL_JAVA)

#define PRINT_ANSI_QUALIFIERS (work -> options & DMGL_ANSI)
#define PRINT_ARG_TYPES       (work -> options & DMGL_PARAMS)

#define STRING_EMPTY(str)	((str) -> b == (str) -> p)
#define APPEND_BLANK(str)	{if (!STRING_EMPTY(str)) string_append(str, " ");}
#define LEN_STRING(str)         ( (STRING_EMPTY(str))?0:((str)->p - (str)->b))

#define SCOPE_STRING(work) ((work->options & DMGL_JAVA) ? "." : "::")

#define TYPE_UNQUALIFIED   0x0
#define TYPE_QUAL_CONST    0x1
#define TYPE_QUAL_VOLATILE 0x2
#define TYPE_QUAL_RESTRICT 0x4

typedef enum type_kind_t {
  tk_none,
  tk_pointer,
  tk_reference,
  tk_rvalue_reference,
  tk_integral,
  tk_bool,
  tk_char,
  tk_real
} type_kind_t;

struct work_stuff {
  int options;
  char **typevec;
  char **ktypevec;
  char **btypevec;
  int numk;
  int numb;
  int ksize;
  int bsize;
  int ntypes;
  int typevec_size;
  int constructor;
  int destructor;
  int static_type;
  int temp_start;
  int type_quals;
  int dllimported;
  char **tmpl_argvec;
  int ntmpl_args;
  int forgetting_types;
  string* previous_argument;
  int nrepeats;
  int *proctypevec;
  int proctypevec_size;
  int nproctypes;
};

#define ISDIGIT(c)  ((c) >= '0' && (c) <= '9')

extern void xmalloc_failed (int) __attribute__((noreturn));
extern void *xmalloc (size_t);
extern void *xrealloc (void *, size_t);
extern void *xmemdup (const void *, size_t, size_t);
extern char *xstrdup (const char *);

#define XNEW(T)			((T *) xmalloc (sizeof (T)))
#define XNEWVEC(T, N)		((T *) xmalloc (sizeof (T) * (N)))
#define XRESIZEVEC(T, P, N)	((T *) xrealloc ((void *) (P), sizeof (T) * (N)))
#define XDUPVEC(T, P, N)	((T *) xmemdup ((P), sizeof (T) * (N), sizeof (T) * (N)))

static char cplus_markers[] = {'$', '.', '$', '\0'};

static void forget_types (struct work_stuff *work);
static void forget_B_and_K_types (struct work_stuff *work);
static void squangle_mop_up (struct work_stuff *work);
static void string_delete (string *s);
static void string_init (string *s);
static void string_clear (string *s);
static void string_append (string *p, const char *s);
static void string_appends (string *p, string *s);
static void string_appendn (string *p, const char *s, int n);
static void string_prepend (string *p, const char *s);
static void string_prepends (string *p, string *s);
static void string_prependn (string *p, const char *s, int n);
static void string_append_template_idx (string *s, int idx);
static int consume_count (const char **type);
static int consume_count_with_underscores (const char**mangled);
static int get_count (const char **type, int *count);
static int demangle_template (struct work_stuff *work, const char **, string *, string *, int, int);
static int demangle_qualified (struct work_stuff *, const char **, string *, int, int);
static int demangle_function_name (struct work_stuff *, const char **, string *, const char *);
static int demangle_signature (struct work_stuff *, const char **, string *);
static int demangle_nested_args (struct work_stuff*, const char**, string*);
static int demangle_arm_hp_template (struct work_stuff *, const char **, int, string *);
static int arm_special (const char **, string *);
static int do_type (struct work_stuff *, const char **, string *);
static int demangle_fund_type (struct work_stuff *, const char **, string *);
static int demangle_class_name (struct work_stuff *, const char **, string *);
static int demangle_template_value_parm (struct work_stuff*, const char**, string*, type_kind_t);
static void push_processed_type (struct work_stuff *, int);
static void pop_processed_type (struct work_stuff *);
static void remember_Btype (struct work_stuff *, const char *, int, int);
static int register_Btype (struct work_stuff *);
static void remember_Ktype (struct work_stuff *, const char *, int);
static const char* demangle_qualifier (int);
static const char* qualifier_string (int);
static int code_for_qualifier (int);
static char *internal_cplus_demangle (struct work_stuff *, const char *);
static void delete_work_stuff (struct work_stuff *);
static void work_stuff_copy_to_from (struct work_stuff *, struct work_stuff *);
static int iterate_demangle_function (struct work_stuff *, const char **, string *, const char *);
static int demangle_prefix (struct work_stuff *, const char **, string *);
static int gnu_special (struct work_stuff *, const char **, string *);

//% cleanup, assign
/* Delete dynamic stuff in work_stuff that is not to be re-used.  */

static void
delete_non_B_K_work_stuff (struct work_stuff *work)
{
  /* Discard the remembered types, if any.  */

  forget_types (work);
  if (work->typevec != NULL)
    {
      free ((char *) work->typevec);
      work->typevec = NULL;
      work->typevec_size = 0;
    }
  if (work->proctypevec != NULL)
    {
      free (work->proctypevec);
      work->proctypevec = NULL;
      work->proctypevec_size = 0;
    }
  if (work->tmpl_argvec)
    {
      int i;

      for (i = 0; i < work->ntmpl_args; i++)
	free ((char*) work->tmpl_argvec[i]);

      free ((char*) work->tmpl_argvec);
      work->tmpl_argvec = NULL;
    }
  if (work->previous_argument)
    {
      string_delete (work->previous_argument);
      free ((char*) work->previous_argument);
      work->previous_argument = NULL;
    }
}

/* Delete all dynamic storage in work_stuff.  */
static void
delete_work_stuff (struct work_stuff *work)
{
  delete_non_B_K_work_stuff (work);
  squangle_mop_up (work);
}

static void
squangle_mop_up (struct work_stuff *work)
{
  /* clean up the B and K type mangling types. */
  forget_B_and_K_types (work);
  if (work -> btypevec != NULL)
    {
      free ((char *) work -> btypevec);
      work->btypevec = NULL;
      work->bsize = 0;
      work->numb = 0;
    }
  if (work -> ktypevec != NULL)
    {
      free ((char *) work -> ktypevec);
      work->ktypevec = NULL;
      work->ksize = 0;
      work->numk = 0;
    }
}

/* Remember a K type class qualifier. */
static void
remember_Ktype (struct work_stuff *work, const char *start, int len)
{
  char *tem;

  if (work -> numk >= work -> ksize)
    {
      if (work -> ksize == 0)
	{
	  work -> ksize = 5;
	  work -> ktypevec = XNEWVEC (char *, work->ksize);
	}
      else
	{
          if (work -> ksize > INT_MAX / 2)
	    xmalloc_failed (INT_MAX);
	  work -> ksize *= 2;
	  work -> ktypevec
	    = XRESIZEVEC (char *, work->ktypevec, work->ksize);
	}
    }
  tem = XNEWVEC (char, len + 1);
  memcpy (tem, start, len);
  tem[len] = '\0';
  work -> ktypevec[work -> numk++] = tem;
}

/* Register a B code, and get an index for it. B codes are registered
   as they are seen, rather than as they are completed, so map<temp<char> >
   registers map<temp<char> > as B0, and temp<char> as B1 */

static int
register_Btype (struct work_stuff *work)
{
  int ret;

  if (work -> numb >= work -> bsize)
    {
      if (work -> bsize == 0)
	{
	  work -> bsize = 5;
	  work -> btypevec = XNEWVEC (char *, work->bsize);
	}
      else
	{
          if (work -> bsize > INT_MAX / 2)
	    xmalloc_failed (INT_MAX);
	  work -> bsize *= 2;
	  work -> btypevec
	    = XRESIZEVEC (char *, work->btypevec, work->bsize);
	}
    }
  ret = work -> numb++;
  work -> btypevec[ret] = NULL;
  return(ret);
}

static void
remember_Btype (struct work_stuff *work, const char *start,
                int len, int index)
{
  char *tem;

  tem = XNEWVEC (char, len + 1);
  if (len > 0)
    memcpy (tem, start, len);
  tem[len] = '\0';
  work -> btypevec[index] = tem;
}

//% null.assign
static int
demangle_class_name (struct work_stuff *work, const char **mangled,
                     string *declp)
{
  int n;
  int success = 0;

  n = consume_count (mangled);
  if (n == -1)
    return 0;
  if ((int) strlen (*mangled) >= n)
    {
      demangle_arm_hp_template (work, mangled, n, declp);
      success = 1;
    }

  return (success);
}

static int
demangle_fund_type (struct work_stuff *work,
                    const char **mangled, string *result)
{
  int done = 0;
  int success = 1;
  char buf[INTBUF_SIZE + 5 /* 'int%u_t' */];
  unsigned int dec = 0;
  type_kind_t tk = tk_integral;

  /* First pick off any type qualifiers.  There can be more than one.  */

  while (!done)
    {
      switch (**mangled)
	{
	case 'C':
	case 'V':
	case 'u':
	  if (PRINT_ANSI_QUALIFIERS)
	    {
              if (!STRING_EMPTY (result))
                string_prepend (result, " ");
	      string_prepend (result, demangle_qualifier (**mangled));
	    }
	  (*mangled)++;
	  break;
	case 'U':
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "unsigned");
	  break;
	case 'S': /* signed char only */
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "signed");
	  break;
	case 'J':
	  (*mangled)++;
	  APPEND_BLANK (result);
	  string_append (result, "__complex");
	  break;
	default:
	  done = 1;
	  break;
	}
    }

  /* Now pick off the fundamental type.  There can be only one.  */

  switch (**mangled)
    {
    case '\0':
    case '_':
      break;
    case 'v':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "void");
      break;
    case 'x':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long long");
      break;
    case 'l':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long");
      break;
    case 'i':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "int");
      break;
    case 's':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "short");
      break;
    case 'b':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "bool");
      tk = tk_bool;
      break;
    case 'c':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "char");
      tk = tk_char;
      break;
    case 'w':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "wchar_t");
      tk = tk_char;
      break;
    case 'r':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "long double");
      tk = tk_real;
      break;
    case 'd':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "double");
      tk = tk_real;
      break;
    case 'f':
      (*mangled)++;
      APPEND_BLANK (result);
      string_append (result, "float");
      tk = tk_real;
      break;
    case 'G':
      (*mangled)++;
      if (!ISDIGIT ((unsigned char)**mangled))
	{
	  success = 0;
	  break;
	}
      /* fall through */
    case 'I':
      (*mangled)++;
      if (**mangled == '_')
	{
	  int i;
	  (*mangled)++;
	  for (i = 0;
	       i < (long) sizeof (buf) - 1 && **mangled && **mangled != '_';
	       (*mangled)++, i++)
	    buf[i] = **mangled;
	  if (**mangled != '_')
	    {
	      success = 0;
	      break;
	    }
	  buf[i] = '\0';
	  (*mangled)++;
	}
      else
	{
	  strncpy (buf, *mangled, 2);
	  buf[2] = '\0';
	  *mangled += min (strlen (*mangled), 2);
	}
      sscanf (buf, "%x", &dec);
      sprintf (buf, "int%u_t", dec);
      APPEND_BLANK (result);
      string_append (result, buf);
      break;

      /* fall through */
      /* An explicit type, such as "6mytype" or "7integer" */
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
      {
        int bindex = register_Btype (work);
        string btype;
        string_init (&btype);
        if (demangle_class_name (work, mangled, &btype)) {
          remember_Btype (work, btype.b, LEN_STRING (&btype), bindex);
          APPEND_BLANK (result);
          string_appends (result, &btype);
        }
        else
          success = 0;
        string_delete (&btype);
        break;
      }
    case 't':
      {
        string btype;
        string_init (&btype);
        success = demangle_template (work, mangled, &btype, 0, 1, 1);
        string_appends (result, &btype);
        string_delete (&btype);
        break;
      }
    default:
      success = 0;
      break;
    }

  return success ? ((int) tk) : 0;
}

static int
do_type (struct work_stuff *work, const char **mangled, string *result)
{
  int n;
  int i;
  int is_proctypevec;
  int done;
  int success;
  string decl;
  const char *remembered_type;
  int type_quals;
  type_kind_t tk = tk_none;

  string_init (&decl);
  string_init (result);

  done = 0;
  success = 1;
  is_proctypevec = 0;
  while (success && !done)
    {
      int member;
      switch (**mangled)
	{

	  /* A pointer type */
	case 'P':
	case 'p':
	  (*mangled)++;
	  if (! (work -> options & DMGL_JAVA))
	    string_prepend (&decl, "*");
	  if (tk == tk_none)
	    tk = tk_pointer;
	  break;

	  /* A reference type */
	case 'R':
	  (*mangled)++;
	  string_prepend (&decl, "&");
	  if (tk == tk_none)
	    tk = tk_reference;
	  break;

	  /* An rvalue reference type */
	case 'O':
	  (*mangled)++;
	  string_prepend (&decl, "&&");
	  if (tk == tk_none)
	    tk = tk_rvalue_reference;
	  break;

	  /* An array */
	case 'A':
	  {
	    ++(*mangled);
	    if (!STRING_EMPTY (&decl)
		&& (decl.b[0] == '*' || decl.b[0] == '&'))
	      {
		string_prepend (&decl, "(");
		string_append (&decl, ")");
	      }
	    string_append (&decl, "[");
	    if (**mangled != '_')
	      success = demangle_template_value_parm (work, mangled, &decl,
						      tk_integral);
	    if (**mangled == '_')
	      ++(*mangled);
	    string_append (&decl, "]");
	    break;
	  }

	/* A back reference to a previously seen type */
	case 'T':
	  (*mangled)++;
	  if (!get_count (mangled, &n) || n < 0 || n >= work -> ntypes)
	    {
	      success = 0;
	    }
	  else
	    for (i = 0; i < work->nproctypes; i++)
	      if (work -> proctypevec [i] == n)
	        success = 0;

	  if (success)
	    {    
	      is_proctypevec = 1;
	      push_processed_type (work, n);
	      remembered_type = work->typevec[n];
	      mangled = &remembered_type;
	    }
	  break;

	  /* A function */
	case 'F':
	  (*mangled)++;
	    if (!STRING_EMPTY (&decl)
		&& (decl.b[0] == '*' || decl.b[0] == '&'))
	    {
	      string_prepend (&decl, "(");
	      string_append (&decl, ")");
	    }
	  /* After picking off the function args, we expect to either find the
	     function return type (preceded by an '_') or the end of the
	     string.  */
	  if (!demangle_nested_args (work, mangled, &decl)
	      || (**mangled != '_' && **mangled != '\0'))
	    {
	      success = 0;
	      break;
	    }
	  if (success && (**mangled == '_'))
	    (*mangled)++;
	  break;

	case 'M':
	  {
	    type_quals = TYPE_UNQUALIFIED;

	    member = **mangled == 'M';
	    (*mangled)++;

	    string_append (&decl, ")");

	    /* We don't need to prepend `::' for a qualified name;
	       demangle_qualified will do that for us.  */
	    if (**mangled != 'Q')
	      string_prepend (&decl, SCOPE_STRING (work));

	    if (ISDIGIT ((unsigned char)**mangled))
	      {
		n = consume_count (mangled);
		if (n == -1
		    || (int) strlen (*mangled) < n)
		  {
		    success = 0;
		    break;
		  }
		string_prependn (&decl, *mangled, n);
		*mangled += n;
	      }
	    else if (**mangled == 'X' || **mangled == 'Y')
	      {
		string temp;
		do_type (work, mangled, &temp);
		string_prepends (&decl, &temp);
		string_delete (&temp);
	      }
	    else if (**mangled == 't')
	      {
		string temp;
		string_init (&temp);
		success = demangle_template (work, mangled, &temp,
					     NULL, 1, 1);
		if (success)
		  {
		    string_prependn (&decl, temp.b, temp.p - temp.b);
		    string_delete (&temp);
		  }
		else
		  {
		    string_delete (&temp);
		    break;
		  }
	      }
	    else if (**mangled == 'Q')
	      {
		success = demangle_qualified (work, mangled, &decl,
					      /*isfuncnam=*/0, 
					      /*append=*/0);
		if (!success)
		  break;
	      }
	    else
	      {
		success = 0;
		break;
	      }

	    string_prepend (&decl, "(");
	    if (member)
	      {
		switch (**mangled)
		  {
		  case 'C':
		  case 'V':
		  case 'u':
		    type_quals |= code_for_qualifier (**mangled);
		    (*mangled)++;
		    break;

		  default:
		    break;
		  }

		if (*(*mangled) != 'F')
		  {
		    success = 0;
		    break;
		  }
		(*mangled)++;
	      }
	    if ((member && !demangle_nested_args (work, mangled, &decl))
		|| **mangled != '_')
	      {
		success = 0;
		break;
	      }
	    (*mangled)++;
	    if (! PRINT_ANSI_QUALIFIERS)
	      {
		break;
	      }
	    if (type_quals != TYPE_UNQUALIFIED)
	      {
		APPEND_BLANK (&decl);
		string_append (&decl, qualifier_string (type_quals));
	      }
	    break;
	  }
        case 'G':
	  (*mangled)++;
	  break;

	case 'C':
	case 'V':
	case 'u':
	  if (PRINT_ANSI_QUALIFIERS)
	    {
	      if (!STRING_EMPTY (&decl))
		string_prepend (&decl, " ");

	      string_prepend (&decl, demangle_qualifier (**mangled));
	    }
	  (*mangled)++;
	  break;
	  /*
	    }
	    */

	  /* fall through */
	default:
	  done = 1;
	  break;
	}
    }

  if (success) switch (**mangled)
    {
      /* A qualified name, such as "Outer::Inner".  */
    case 'Q':
    case 'K':
      {
        success = demangle_qualified (work, mangled, result, 0, 1);
        break;
      }

    /* A back reference to a previously seen squangled type */
    case 'B':
      (*mangled)++;
      if (!get_count (mangled, &n) || n < 0 || n >= work -> numb)
	success = 0;
      else
	string_append (result, work->btypevec[n]);
      break;

    case 'X':
    case 'Y':
      /* A template parm.  We substitute the corresponding argument. */
      {
	int idx;

	(*mangled)++;
	idx = consume_count_with_underscores (mangled);

	if (idx == -1
	    || (work->tmpl_argvec && idx >= work->ntmpl_args)
	    || consume_count_with_underscores (mangled) == -1)
	  {
	    success = 0;
	    break;
	  }

	if (work->tmpl_argvec)
	  string_append (result, work->tmpl_argvec[idx]);
	else
	  string_append_template_idx (result, idx);

	success = 1;
      }
    break;

    default:
      success = demangle_fund_type (work, mangled, result);
      if (tk == tk_none)
	tk = (type_kind_t) success;
      break;
    }

  if (success)
    {
      if (!STRING_EMPTY (&decl))
	{
	  string_append (result, " ");
	  string_appends (result, &decl);
	}
    }
  else
    string_delete (result);
  string_delete (&decl);

  if (is_proctypevec)
    pop_processed_type (work); 

  if (success)
    /* Assume an integral type, if we're not sure.  */
    return (int) ((tk == tk_none) ? tk_integral : tk);
  else
    return 0;
}

static int
gnu_special (struct work_stuff *work, const char **mangled, string *declp)
{
  int n;
  int success = 1;
  const char *p;

  if ((*mangled)[0] == '_' && (*mangled)[1] != '\0'
      && strchr (cplus_markers, (*mangled)[1]) != NULL
      && (*mangled)[2] == '_')
    {
      /* Found a GNU style destructor, get past "_<CPLUS_MARKER>_" */
      (*mangled) += 3;
      work -> destructor += 1;
    }
  else if ((*mangled)[0] == '_'
	   && (((*mangled)[1] == '_'
		&& (*mangled)[2] == 'v'
		&& (*mangled)[3] == 't'
		&& (*mangled)[4] == '_')
	       || ((*mangled)[1] == 'v'
		   && (*mangled)[2] == 't' && (*mangled)[3] != '\0'
		   && strchr (cplus_markers, (*mangled)[3]) != NULL)))
    {
      /* Found a GNU style virtual table, get past "_vt<CPLUS_MARKER>"
         and create the decl.  Note that we consume the entire mangled
	 input string, which means that demangle_signature has no work
	 to do.  */
      if ((*mangled)[2] == 'v')
	(*mangled) += 5; /* New style, with thunks: "__vt_" */
      else
	(*mangled) += 4; /* Old style, no thunks: "_vt<CPLUS_MARKER>" */
      while (**mangled != '\0')
	{
	  switch (**mangled)
	    {
	    case 'Q':
	    case 'K':
	      success = demangle_qualified (work, mangled, declp, 0, 1);
	      break;
	    case 't':
	      success = demangle_template (work, mangled, declp, 0, 1,
					   1);
	      break;
	    default:
	      if (ISDIGIT((unsigned char)*mangled[0]))
		{
		  n = consume_count(mangled);
		  /* We may be seeing a too-large size, or else a
		     ".<digits>" indicating a static local symbol.  In
		     any case, declare victory and move on; *don't try
		     to use n to allocate.  */
		  if (n > (int) strlen (*mangled))
		    {
		      success = 1;
		      break;
		    }
		  else if (n == -1)
		    {
		      success = 0;
		      break;
		    }
		}
	      else
		{
		  n = strcspn (*mangled, cplus_markers);
		}
	      string_appendn (declp, *mangled, n);
	      (*mangled) += n;
	    }

	  p = strpbrk (*mangled, cplus_markers);
	  if (success && ((p == NULL) || (p == *mangled)))
	    {
	      if (p != NULL)
		{
		  string_append (declp, SCOPE_STRING (work));
		  (*mangled)++;
		}
	    }
	  else
	    {
	      success = 0;
	      break;
	    }
	}
      if (success)
	string_append (declp, " virtual table");
    }
  else if ((*mangled)[0] == '_'
	   && (strchr("0123456789Qt", (*mangled)[1]) != NULL)
	   && (p = strpbrk (*mangled, cplus_markers)) != NULL)
    {
      /* static data member, "_3foo$varname" for example */
      (*mangled)++;
      switch (**mangled)
	{
	case 'Q':
	case 'K':
	  success = demangle_qualified (work, mangled, declp, 0, 1);
	  break;
	case 't':
	  success = demangle_template (work, mangled, declp, 0, 1, 1);
	  break;
	default:
	  n = consume_count (mangled);
	  if (n < 0 || n > (long) strlen (*mangled))
	    {
	      success = 0;
	      break;
	    }

	  if (n > 10 && strncmp (*mangled, "_GLOBAL_", 8) == 0
	      && (*mangled)[9] == 'N'
	      && (*mangled)[8] == (*mangled)[10]
	      && strchr (cplus_markers, (*mangled)[8]))
	    {
	      /* A member of the anonymous namespace.  There's information
		 about what identifier or filename it was keyed to, but
		 it's just there to make the mangled name unique; we just
		 step over it.  */
	      string_append (declp, "{anonymous}");
	      (*mangled) += n;

	      /* Now p points to the marker before the N, so we need to
		 update it to the first marker after what we consumed.  */
	      p = strpbrk (*mangled, cplus_markers);
	      break;
	    }

	  string_appendn (declp, *mangled, n);
	  (*mangled) += n;
	}
      if (success && (p == *mangled))
	{
	  /* Consumed everything up to the cplus_marker, append the
	     variable name.  */
	  (*mangled)++;
	  string_append (declp, SCOPE_STRING (work));
	  n = strlen (*mangled);
	  string_appendn (declp, *mangled, n);
	  (*mangled) += n;
	}
      else
	{
	  success = 0;
	}
    }
  else if (strncmp (*mangled, "__thunk_", 8) == 0)
    {
      int delta;

      (*mangled) += 8;
      delta = consume_count (mangled);
      if (delta == -1)
	success = 0;
      else if (**mangled != '_')
        success = 0;
      else
	{
	  char *method = internal_cplus_demangle (work, ++*mangled);

	  if (method)
	    {
	      char buf[50];
	      sprintf (buf, "virtual function thunk (delta:%d) for ", -delta);
	      string_append (declp, buf);
	      string_append (declp, method);
	      free (method);
	      n = strlen (*mangled);
	      (*mangled) += n;
	    }
	  else
	    {
	      success = 0;
	    }
	}
    }
  else if (strncmp (*mangled, "__t", 3) == 0
	   && ((*mangled)[3] == 'i' || (*mangled)[3] == 'f'))
    {
      p = (*mangled)[3] == 'i' ? " type_info node" : " type_info function";
      (*mangled) += 4;
      switch (**mangled)
	{
	case 'Q':
	case 'K':
	  success = demangle_qualified (work, mangled, declp, 0, 1);
	  break;
	case 't':
	  success = demangle_template (work, mangled, declp, 0, 1, 1);
	  break;
	default:
	  success = do_type (work, mangled, declp);
	  break;
	}
      if (success && **mangled != '\0')
	success = 0;
      if (success)
	string_append (declp, p);
    }
  else
    {
      success = 0;
    }
  return (success);
}

static void
work_stuff_copy_to_from (struct work_stuff *to, struct work_stuff *from)
{
  int i;

  delete_work_stuff (to);

  /* Shallow-copy scalars.  */
  memcpy (to, from, sizeof (*to));

  /* Deep-copy dynamic storage.  */
  if (from->typevec_size)
    to->typevec = XNEWVEC (char *, from->typevec_size);

  for (i = 0; i < from->ntypes; i++)
    {
      int len = strlen (from->typevec[i]) + 1;

      to->typevec[i] = XNEWVEC (char, len);
      memcpy (to->typevec[i], from->typevec[i], len);
    }

  if (from->ksize)
    to->ktypevec = XNEWVEC (char *, from->ksize);

  for (i = 0; i < from->numk; i++)
    {
      int len;

      if (from->ktypevec[i] == NULL) {
        to->ktypevec[i] = NULL;
        continue;
      }

      len = strlen (from->ktypevec[i]) + 1;

      to->ktypevec[i] = XNEWVEC (char, len);
      memcpy (to->ktypevec[i], from->ktypevec[i], len);
    }

  if (from->bsize)
    to->btypevec = XNEWVEC (char *, from->bsize);

  for (i = 0; i < from->numb; i++)
    {
      int len;
      
      if (from->btypevec[i] == NULL){
            to->btypevec[i] = NULL;
            continue;
      }

      len = strlen (from->btypevec[i]) + 1;

      to->btypevec[i] = XNEWVEC (char , len);
      memcpy (to->btypevec[i], from->btypevec[i], len);
    }

  if (from->proctypevec)
    to->proctypevec =
      XDUPVEC (int, from->proctypevec, from->proctypevec_size);

  if (from->ntmpl_args)
    to->tmpl_argvec = XNEWVEC (char *, from->ntmpl_args);

  for (i = 0; i < from->ntmpl_args; i++)
    {
      int len = strlen (from->tmpl_argvec[i]) + 1;

      to->tmpl_argvec[i] = XNEWVEC (char, len);
      memcpy (to->tmpl_argvec[i], from->tmpl_argvec[i], len);
    }

  if (from->previous_argument)
    {
      to->previous_argument = XNEW (string);
      string_init (to->previous_argument);
      string_appends (to->previous_argument, from->previous_argument);
    }
}

static int
iterate_demangle_function (struct work_stuff *work, const char **mangled,
                           string *declp, const char *scan)
{
  const char *mangle_init = *mangled;
  int success = 0;
  string decl_init;
  struct work_stuff work_init;

  if (*(scan + 2) == '\0')
    return 0;

  /* Do not iterate for some demangling modes, or if there's only one
     "__"-sequence.  This is the normal case.  */
  if (ARM_DEMANGLING || LUCID_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING
      || strstr (scan + 2, "__") == NULL)
    return demangle_function_name (work, mangled, declp, scan);

  /* Save state so we can restart if the guess at the correct "__" was
     wrong.  */
  string_init (&decl_init);
  string_appends (&decl_init, declp);
  memset (&work_init, 0, sizeof work_init);
  work_stuff_copy_to_from (&work_init, work);

  /* Iterate over occurrences of __, allowing names and types to have a
     "__" sequence in them.  We must start with the first (not the last)
     occurrence, since "__" most often occur between independent mangled
     parts, hence starting at the last occurence inside a signature
     might get us a "successful" demangling of the signature.  */

  while (scan[2])
    {
      if (demangle_function_name (work, mangled, declp, scan))
	{
	  success = demangle_signature (work, mangled, declp);
	  if (success)
	    break;
	}

      /* Reset demangle state for the next round.  */
      *mangled = mangle_init;
      string_clear (declp);
      string_appends (declp, &decl_init);
      work_stuff_copy_to_from (work, &work_init);

      /* Leave this underscore-sequence.  */
      scan += 2;

      /* Scan for the next "__" sequence.  */
      while (*scan && (scan[0] != '_' || scan[1] != '_'))
	scan++;

      /* Move to last "__" in this sequence.  */
      while (*scan && *scan == '_')
	scan++;
      scan -= 2;
    }

  /* Delete saved state.  */
  delete_work_stuff (&work_init);
  string_delete (&decl_init);

  return success;
}

// caller
static int
demangle_prefix (struct work_stuff *work, const char **mangled,
                 string *declp)
{
  int success = 1;
  const char *scan;
  int i;

  if (strlen(*mangled) > 6
      && (strncmp(*mangled, "_imp__", 6) == 0
          || strncmp(*mangled, "__imp_", 6) == 0))
    {
      /* it's a symbol imported from a PE dynamic library. Check for both
         new style prefix _imp__ and legacy __imp_ used by older versions
	 of dlltool. */
      (*mangled) += 6;
      work->dllimported = 1;
    }
  else if (strlen(*mangled) >= 11 && strncmp(*mangled, "_GLOBAL_", 8) == 0)
    {
      char *marker = strchr (cplus_markers, (*mangled)[8]);
      if (marker != NULL && *marker == (*mangled)[10])
	{
	  if ((*mangled)[9] == 'D')
	    {
	      /* it's a GNU global destructor to be executed at program exit */
	      (*mangled) += 11;
	      work->destructor = 2;
	      if (gnu_special (work, mangled, declp))
		return success;
	    }
	  else if ((*mangled)[9] == 'I')
	    {
	      /* it's a GNU global constructor to be executed at program init */
	      (*mangled) += 11;
	      work->constructor = 2;
	      if (gnu_special (work, mangled, declp))
		return success;
	    }
	}
    }
  else if ((ARM_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING) && strncmp(*mangled, "__std__", 7) == 0)
    {
      /* it's a ARM global destructor to be executed at program exit */
      (*mangled) += 7;
      work->destructor = 2;
    }
  else if ((ARM_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING) && strncmp(*mangled, "__sti__", 7) == 0)
    {
      /* it's a ARM global constructor to be executed at program initial */
      (*mangled) += 7;
      work->constructor = 2;
    }

  /*  This block of code is a reduction in strength time optimization
      of:
      scan = strstr (*mangled, "__"); */

  {
    scan = *mangled;

    do {
      scan = strchr (scan, '_');
    } while (scan != NULL && *++scan != '_');

    if (scan != NULL) --scan;
  }

  if (scan != NULL)
    {
      /* We found a sequence of two or more '_', ensure that we start at
	 the last pair in the sequence.  */
      i = strspn (scan, "_");
      if (i > 2)
	{
	  scan += (i - 2);
	}
    }

  if (scan == NULL)
    {
      success = 0;
    }
  else if (work -> static_type)
    {
      if (!ISDIGIT ((unsigned char)scan[0]) && (scan[0] != 't'))
	{
	  success = 0;
	}
    }
  else if ((scan == *mangled)
	   && (ISDIGIT ((unsigned char)scan[2]) || (scan[2] == 'Q')
	       || (scan[2] == 't') || (scan[2] == 'K') || (scan[2] == 'H')))
    {
      /* The ARM says nothing about the mangling of local variables.
	 But cfront mangles local variables by prepending __<nesting_level>
	 to them. As an extension to ARM demangling we handle this case.  */
      if ((LUCID_DEMANGLING || ARM_DEMANGLING || HP_DEMANGLING)
	  && ISDIGIT ((unsigned char)scan[2]))
	{
	  *mangled = scan + 2;
	  consume_count (mangled);
	  string_append (declp, *mangled);
	  *mangled += strlen (*mangled);
	  success = 1;
	}
      else
	{
	  /* A GNU style constructor starts with __[0-9Qt].  But cfront uses
	     names like __Q2_3foo3bar for nested type names.  So don't accept
	     this style of constructor for cfront demangling.  A GNU
	     style member-template constructor starts with 'H'. */
	  if (!(LUCID_DEMANGLING || ARM_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING))
	    work -> constructor += 1;
	  *mangled = scan + 2;
	}
    }
  else if (ARM_DEMANGLING && scan[2] == 'p' && scan[3] == 't')
    {
      /* Cfront-style parameterized type.  Handled later as a signature. */
      success = 1;

      /* ARM template? */
      demangle_arm_hp_template (work, mangled, strlen (*mangled), declp);
    }
  else if (EDG_DEMANGLING && ((scan[2] == 't' && scan[3] == 'm')
                              || (scan[2] == 'p' && scan[3] == 's')
                              || (scan[2] == 'p' && scan[3] == 't')))
    {
      /* EDG-style parameterized type.  Handled later as a signature. */
      success = 1;

      /* EDG template? */
      demangle_arm_hp_template (work, mangled, strlen (*mangled), declp);
    }
  else if ((scan == *mangled) && !ISDIGIT ((unsigned char)scan[2])
	   && (scan[2] != 't'))
    {
      /* Mangled name starts with "__".  Skip over any leading '_' characters,
	 then find the next "__" that separates the prefix from the signature.
	 */
      if (!(ARM_DEMANGLING || LUCID_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING)
	  || (arm_special (mangled, declp) == 0))
	{
	  while (*scan == '_')
	    {
	      scan++;
	    }
	  if ((scan = strstr (scan, "__")) == NULL || (*(scan + 2) == '\0'))
	    {
	      /* No separator (I.E. "__not_mangled"), or empty signature
		 (I.E. "__not_mangled_either__") */
	      success = 0;
	    }
	  else
	    return iterate_demangle_function (work, mangled, declp, scan);
	}
    }
  else if (*(scan + 2) != '\0')
    {
      /* Mangled name does not start with "__" but does have one somewhere
	 in there with non empty stuff after it.  Looks like a global
	 function name.  Iterate over all "__":s until the right
	 one is found.  */
      return iterate_demangle_function (work, mangled, declp, scan);
    }
  else
    {
      /* Doesn't look like a mangled name */
      success = 0;
    }

  if (!success && (work->constructor == 2 || work->destructor == 2))
    {
      string_append (declp, *mangled);
      *mangled += strlen (*mangled);
      success = 1;
    }
  return (success);
}
