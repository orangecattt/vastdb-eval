#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long bfd_vma;
typedef uint64_t bfd_uint64_t;
typedef int64_t bfd_int64_t;
typedef unsigned long bfd_size_type;
typedef unsigned char bfd_byte;
typedef int bfd_boolean;

#define TRUE 1
#define FALSE 0

#define IS_ABSOLUTE_PATH(f) ((f)[0] == '/')

#define BFD_ASSERT(x) do { if (!(x)) abort(); } while (0)

typedef struct bfd bfd;
typedef struct asection asection;
typedef struct symbol asymbol;

struct dwarf_block
{
  unsigned int size;
  bfd_byte *data;
};

enum dwarf_attribute
{
  DW_AT_name = 0x03,
  DW_AT_stmt_list = 0x10,
  DW_AT_comp_dir = 0x1b,
  DW_AT_abstract_origin = 0x31,
  DW_AT_linkage_name = 0x6e,
  DW_AT_MIPS_linkage_name = 0x2007,
  DW_AT_specification = 0x47,
  DW_AT_decl_file = 0x3a,
  DW_AT_decl_line = 0x3b,
  DW_AT_call_file = 0x58,
  DW_AT_call_line = 0x59,
  DW_AT_low_pc = 0x11,
  DW_AT_high_pc = 0x12,
  DW_AT_ranges = 0x55,
  DW_AT_external = 0x3f,
  DW_AT_location = 0x02
};

enum dwarf_form
{
  DW_FORM_addr = 0x01,
  DW_FORM_block2 = 0x03,
  DW_FORM_block4 = 0x04,
  DW_FORM_data2 = 0x05,
  DW_FORM_data4 = 0x06,
  DW_FORM_data8 = 0x07,
  DW_FORM_string = 0x08,
  DW_FORM_block = 0x09,
  DW_FORM_block1 = 0x0a,
  DW_FORM_data1 = 0x0b,
  DW_FORM_flag = 0x0c,
  DW_FORM_sdata = 0x0d,
  DW_FORM_strp = 0x0e,
  DW_FORM_udata = 0x0f,
  DW_FORM_ref_addr = 0x10,
  DW_FORM_ref1 = 0x11,
  DW_FORM_ref2 = 0x12,
  DW_FORM_ref4 = 0x13,
  DW_FORM_ref8 = 0x14,
  DW_FORM_ref_udata = 0x15,
  DW_FORM_indirect = 0x16,
  DW_FORM_sec_offset = 0x17,
  DW_FORM_exprloc = 0x18,
  DW_FORM_flag_present = 0x19,
  DW_FORM_ref_sig8 = 0x20,
  DW_FORM_GNU_strp_alt = 0x1f21,
  DW_FORM_line_strp = 0x1f22,
  DW_FORM_GNU_ref_alt = 0x1f20,
  DW_FORM_implicit_const = 0x21
};

enum dwarf_tag
{
  DW_TAG_subprogram = 0x2e,
  DW_TAG_entry_point = 0x3a,
  DW_TAG_inlined_subroutine = 0x3d,
  DW_TAG_variable = 0x34
};

enum dwarf_location_atom
{
  DW_OP_addr = 0x03,
  DW_OP_GNU_push_tls_address = 0xe0
};

struct attribute
{
  enum dwarf_attribute name;
  enum dwarf_form form;
  union
  {
    char *str;
    struct dwarf_block *blk;
    bfd_uint64_t val;
    bfd_int64_t sval;
  }
  u;
};

struct attr_abbrev
{
  enum dwarf_attribute name;
  enum dwarf_form form;
  bfd_vma implicit_const;
};

struct abbrev_info
{
  unsigned int         number;
  enum dwarf_tag       tag;
  bfd_boolean          has_children;
  unsigned int         num_attrs;
  struct attr_abbrev * attrs;
  struct abbrev_info * next;
};

struct arange
{
  struct arange *next;
  bfd_vma low;
  bfd_vma high;
};

struct lookup_funcinfo
{
  struct funcinfo *funcinfo;
  bfd_vma low_addr;
  bfd_vma high_addr;
  unsigned int idx;
};

struct dwarf2_debug_file
{
  bfd *bfd_ptr;
  asymbol **syms;
  bfd_byte *info_ptr;
  bfd_byte *dwarf_info_buffer;
  bfd_size_type dwarf_info_size;
  bfd_byte *dwarf_abbrev_buffer;
  bfd_size_type dwarf_abbrev_size;
  bfd_byte *dwarf_line_buffer;
  bfd_size_type dwarf_line_size;
  bfd_byte *dwarf_str_buffer;
  bfd_size_type dwarf_str_size;
  bfd_byte *dwarf_line_str_buffer;
  bfd_size_type dwarf_line_str_size;
  bfd_byte *dwarf_ranges_buffer;
  bfd_size_type dwarf_ranges_size;
  struct comp_unit *all_comp_units;
  struct comp_unit *last_comp_unit;
  struct line_info_table *line_table;
  void *abbrev_offsets;
};

struct dwarf2_debug
{
  const void *debug_sections;
  struct dwarf2_debug_file f, alt;
  bfd *orig_bfd;
  struct funcinfo *inliner_chain;
  bfd_vma *sec_vma;
  unsigned int sec_vma_count;
  int adjusted_section_count;
  void *adjusted_sections;
  int info_hash_count;
  void *funcinfo_hash_table;
  void *varinfo_hash_table;
  struct comp_unit *hash_units_head;
  int info_hash_status;
  bfd_boolean close_on_cleanup;
};

struct comp_unit
{
  struct comp_unit *next_unit;
  struct comp_unit *prev_unit;
  bfd *abfd;
  struct arange arange;
  char *name;
  struct abbrev_info **abbrevs;
  int lang;
  int error;
  char *comp_dir;
  int stmtlist;
  bfd_byte *info_ptr_unit;
  unsigned long line_offset;
  bfd_byte *first_child_die_ptr;
  bfd_byte *end_ptr;
  struct line_info_table *line_table;
  struct funcinfo *function_table;
  struct lookup_funcinfo *lookup_funcinfo_table;
  bfd_size_type number_of_functions;
  struct varinfo *variable_table;
  struct dwarf2_debug *stash;
  struct dwarf2_debug_file *file;
  int version;
  unsigned char addr_size;
  unsigned char offset_size;
  bfd_vma base_address;
  bfd_boolean cached;
};

struct funcinfo
{
  struct funcinfo *prev_func;
  struct funcinfo *caller_func;
  char *caller_file;
  char *file;
  int caller_line;
  int line;
  int tag;
  bfd_boolean is_linkage;
  const char *name;
  struct arange arange;
  asection *sec;
};

struct fileinfo
{
  char *name;
  unsigned int dir;
  unsigned int time;
  unsigned int size;
};

struct line_sequence
{
  bfd_vma low_pc;
  struct line_sequence* prev_sequence;
  void *last_line;
  void **line_info_lookup;
  bfd_size_type num_lines;
};

struct line_info_table
{
  bfd *abfd;
  unsigned int num_files;
  unsigned int num_dirs;
  unsigned int num_sequences;
  char *comp_dir;
  char **dirs;
  struct fileinfo *files;
  struct line_sequence *sequences;
  void *lcl_head;
};

struct varinfo {
  struct varinfo *prev_var;
  bfd_uint64_t unit_offset;
  char *file;
  int line;
  int tag;
  char *name;
  bfd_vma addr;
  asection *sec;
  bfd_boolean stack;
};

enum bfd_error_type { bfd_error_no_error, bfd_error_system_call, bfd_error_no_memory, bfd_error_wrong_format, bfd_error_invalid_operation, bfd_error_nonrepresentable_section, bfd_error_bad_value, bfd_error_file_truncated, bfd_error_file_too_big, bfd_error_no_contents, bfd_error_malformed_archive };

void *bfd_alloc (bfd *abfd, bfd_size_type size);
void *bfd_malloc (bfd_size_type size);
void *bfd_realloc (void *ptr, bfd_size_type size);
void *bfd_zalloc (bfd *abfd, bfd_size_type size);
void _bfd_error_handler (const char *fmt, ...);
char *gettext (const char *msgid);
#define _(String) gettext (String)
bfd_vma _bfd_safe_read_leb128 (bfd *abfd, const bfd_byte *buf, unsigned int *bytes_read, int sign, const bfd_byte *buf_end);
struct abbrev_info *lookup_abbrev (unsigned int number, struct abbrev_info **abbrevs);
bfd_byte *read_attribute (struct attribute *attr, struct attr_abbrev *abbrev, struct comp_unit *unit, bfd_byte *info_ptr, bfd_byte *info_ptr_end);
bfd_boolean is_str_attr (enum dwarf_form form);
bfd_boolean non_mangled (int lang);
bfd_boolean read_rangelist (struct comp_unit *unit, struct arange *arange, bfd_uint64_t offset);
bfd_boolean arange_add (const struct comp_unit *unit, struct arange *first_arange, bfd_vma low_pc, bfd_vma high_pc);
struct line_info_table *decode_line_info (struct comp_unit *unit);
struct comp_unit *stash_comp_unit (struct dwarf2_debug *stash, struct dwarf2_debug_file *file);
void bfd_set_error (enum bfd_error_type error_tag);
bfd_vma bfd_get (int bits, bfd *abfd, const bfd_byte *addr);
bfd_byte *read_alt_indirect_ref (struct comp_unit *unit, bfd_uint64_t offset);
static char *concat_filename (struct line_info_table *table, unsigned int file);
static bfd_boolean find_abstract_instance (struct comp_unit *unit, struct attribute *attr_ptr, unsigned int recur_count, const char **pname, bfd_boolean *is_linkage, char **filename_ptr, int *linenumber_ptr);
static struct varinfo *lookup_var_by_offset (bfd_uint64_t offset, struct varinfo *table);
static bfd_boolean comp_unit_maybe_decode_line_info (struct comp_unit *unit);
static bfd_boolean scan_unit_for_symbols (struct comp_unit *unit);

void *
bfd_zalloc (bfd *abfd, bfd_size_type size)
{
  void *res;

  res = bfd_alloc (abfd, size);
  if (res)
    memset (res, 0, (size_t) size);
  return res;
}

static char *
concat_filename (struct line_info_table *table, unsigned int file)
{
  char *filename;

  if (table == NULL || file - 1 >= table->num_files)
    {
      /* FILE == 0 means unknown.  */
      if (file)
	_bfd_error_handler
	  (_("DWARF error: mangled line number section (bad file number)"));
      return strdup ("<unknown>");
    }

  filename = table->files[file - 1].name;
  if (filename == NULL)
    return strdup ("<unknown>");

  if (!IS_ABSOLUTE_PATH (filename))
    {
      char *dir_name = NULL;
      char *subdir_name = NULL;
      char *name;
      size_t len;

      if (table->files[file - 1].dir
	  /* PR 17512: file: 0317e960.  */
	  && table->files[file - 1].dir <= table->num_dirs
	  /* PR 17512: file: 7f3d2e4b.  */
	  && table->dirs != NULL)
	subdir_name = table->dirs[table->files[file - 1].dir - 1];

      if (!subdir_name || !IS_ABSOLUTE_PATH (subdir_name))
	dir_name = table->comp_dir;

      if (!dir_name)
	{
	  dir_name = subdir_name;
	  subdir_name = NULL;
	}

      if (!dir_name)
	return strdup (filename);

      len = strlen (dir_name) + strlen (filename) + 2;

      if (subdir_name)
	{
	  len += strlen (subdir_name) + 1;
	  name = (char *) bfd_malloc (len);
	  if (name)
	    sprintf (name, "%s/%s/%s", dir_name, subdir_name, filename);
	}
      else
	{
	  name = (char *) bfd_malloc (len);
	  if (name)
	    sprintf (name, "%s/%s", dir_name, filename);
	}

      return name;
    }

  return strdup (filename);
}

static bfd_boolean
find_abstract_instance (struct comp_unit *unit,
			struct attribute *attr_ptr,
			unsigned int recur_count,
			const char **pname,
			bfd_boolean *is_linkage,
			char **filename_ptr,
			int *linenumber_ptr)
{
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr = NULL;
  bfd_byte *info_ptr_end;
  unsigned int abbrev_number, bytes_read, i;
  struct abbrev_info *abbrev;
  bfd_uint64_t die_ref = attr_ptr->u.val;
  struct attribute attr;
  const char *name = NULL;

  if (recur_count == 100)
    {
      _bfd_error_handler
	(_("DWARF error: abstract instance recursion detected"));
      bfd_set_error (bfd_error_bad_value);
      return FALSE;
    }

  /* DW_FORM_ref_addr can reference an entry in a different CU. It
     is an offset from the .debug_info section, not the current CU.  */
  if (attr_ptr->form == DW_FORM_ref_addr)
    {
      /* We only support DW_FORM_ref_addr within the same file, so
	 any relocations should be resolved already.  Check this by
	 testing for a zero die_ref;  There can't be a valid reference
	 to the header of a .debug_info section.
	 DW_FORM_ref_addr is an offset relative to .debug_info.
	 Normally when using the GNU linker this is accomplished by
	 emitting a symbolic reference to a label, because .debug_info
	 sections are linked at zero.  When there are multiple section
	 groups containing .debug_info, as there might be in a
	 relocatable object file, it would be reasonable to assume that
	 a symbolic reference to a label in any .debug_info section
	 might be used.  Since we lay out multiple .debug_info
	 sections at non-zero VMAs (see place_sections), and read
	 them contiguously into dwarf_info_buffer, that means the
	 reference is relative to dwarf_info_buffer.  */
      size_t total;

      info_ptr = unit->file->dwarf_info_buffer;
      info_ptr_end = info_ptr + unit->file->dwarf_info_size;
      total = info_ptr_end - info_ptr;
      if (!die_ref)
	return TRUE;
      else if (die_ref >= total)
	{
	  _bfd_error_handler
	    (_("DWARF error: invalid abstract instance DIE ref"));
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      info_ptr += die_ref;
    }
  else if (attr_ptr->form == DW_FORM_GNU_ref_alt)
    {
      bfd_boolean first_time = unit->stash->alt.dwarf_info_buffer == NULL;

      info_ptr = read_alt_indirect_ref (unit, die_ref);
      if (first_time)
	unit->stash->alt.info_ptr = unit->stash->alt.dwarf_info_buffer;
      if (info_ptr == NULL)
	{
	  _bfd_error_handler
	    (_("DWARF error: unable to read alt ref %" PRIu64),
	     (uint64_t) die_ref);
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      info_ptr_end = (unit->stash->alt.dwarf_info_buffer
		      + unit->stash->alt.dwarf_info_size);
      if (unit->stash->alt.all_comp_units)
	unit = unit->stash->alt.all_comp_units;
    }

  if (attr_ptr->form == DW_FORM_ref_addr
      || attr_ptr->form == DW_FORM_GNU_ref_alt)
    {
      /* Now find the CU containing this pointer.  */
      if (info_ptr >= unit->info_ptr_unit && info_ptr < unit->end_ptr)
	info_ptr_end = unit->end_ptr;
      else
	{
	  /* Check other CUs to see if they contain the abbrev.  */
	  struct comp_unit *u;

	  for (u = unit->prev_unit; u != NULL; u = u->prev_unit)
	    if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
	      break;

	  if (u == NULL)
	    for (u = unit->next_unit; u != NULL; u = u->next_unit)
	      if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
		break;

	  if (u == NULL)
	    while (u == NULL)
	      {
		u = stash_comp_unit (unit->stash, &unit->stash->f);
		if (u == NULL)
		  break;
		if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
		  break;
		u = NULL;
	      }

	  if (attr_ptr->form == DW_FORM_GNU_ref_alt)
	    while (u == NULL)
	      {
		u = stash_comp_unit (unit->stash, &unit->stash->alt);
		if (u == NULL)
		  break;
		if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
		  break;
		u = NULL;
	      }

	  if (u == NULL)
	    {
	      _bfd_error_handler
		(_("DWARF error: unable to locate abstract instance DIE ref %"
		   PRIu64), (uint64_t) die_ref);
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }
	  unit = u;
	  info_ptr_end = unit->end_ptr;
	}
    }
  else
    {
      /* DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4, DW_FORM_ref8 or
	 DW_FORM_ref_udata.  These are all references relative to the
	 start of the current CU.  */
      size_t total;

      info_ptr = unit->info_ptr_unit;
      info_ptr_end = unit->end_ptr;
      total = info_ptr_end - info_ptr;
      if (!die_ref || die_ref >= total)
	{
	  _bfd_error_handler
	    (_("DWARF error: invalid abstract instance DIE ref"));
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      info_ptr += die_ref;
    }

  abbrev_number = _bfd_safe_read_leb128 (abfd, info_ptr, &bytes_read,
					 FALSE, info_ptr_end);
  info_ptr += bytes_read;

  if (abbrev_number)
    {
      abbrev = lookup_abbrev (abbrev_number, unit->abbrevs);
      if (! abbrev)
	{
	  _bfd_error_handler
	    (_("DWARF error: could not find abbrev number %u"), abbrev_number);
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      else
	{
	  for (i = 0; i < abbrev->num_attrs; ++i)
	    {
	      info_ptr = read_attribute (&attr, &abbrev->attrs[i], unit,
					 info_ptr, info_ptr_end);
	      if (info_ptr == NULL)
		break;
	      switch (attr.name)
		{
		case DW_AT_name:
		  /* Prefer DW_AT_MIPS_linkage_name or DW_AT_linkage_name
		     over DW_AT_name.  */
		  if (name == NULL && is_str_attr (attr.form))
		    {
		      name = attr.u.str;
		      if (non_mangled (unit->lang))
			*is_linkage = TRUE;
		    }
		  break;
		case DW_AT_specification:
		  if (!find_abstract_instance (unit, &attr, recur_count + 1,
					       &name, is_linkage,
					       filename_ptr, linenumber_ptr))
		    return FALSE;
		  break;
		case DW_AT_linkage_name:
		case DW_AT_MIPS_linkage_name:
		  /* PR 16949:  Corrupt debug info can place
		     non-string forms into these attributes.  */
		  if (is_str_attr (attr.form))
		    {
		      name = attr.u.str;
		      *is_linkage = TRUE;
		    }
		  break;
		case DW_AT_decl_file:
		  if (!comp_unit_maybe_decode_line_info (unit))
		    return FALSE;
		  *filename_ptr = concat_filename (unit->line_table,
						   attr.u.val);
		  break;
		case DW_AT_decl_line:
		  *linenumber_ptr = attr.u.val;
		  break;
		default:
		  break;
		}
	    }
	}
    }
  *pname = name;
  return TRUE;
}

static struct varinfo *
lookup_var_by_offset (bfd_uint64_t offset, struct varinfo * table)
{
  while (table)
    {
      if (table->unit_offset == offset)
	return table;
      table = table->prev_var;
    }

  return NULL;
}

static bfd_boolean
comp_unit_maybe_decode_line_info (struct comp_unit *unit)
{
  if (unit->error)
    return FALSE;

  if (! unit->line_table)
    {
      if (! unit->stmtlist)
	{
	  unit->error = 1;
	  return FALSE;
	}

      unit->line_table = decode_line_info (unit);

      if (! unit->line_table)
	{
	  unit->error = 1;
	  return FALSE;
	}

      if (unit->first_child_die_ptr < unit->end_ptr
	  && ! scan_unit_for_symbols (unit))
	{
	  unit->error = 1;
	  return FALSE;
	}
    }

  return TRUE;
}

static bfd_boolean
scan_unit_for_symbols (struct comp_unit *unit)
{
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr = unit->first_child_die_ptr;
  bfd_byte *info_ptr_end = unit->end_ptr;
  int nesting_level = 0;
  struct nest_funcinfo {
    struct funcinfo *func;
  } *nested_funcs;
  int nested_funcs_size;

  /* Maintain a stack of in-scope functions and inlined functions, which we
     can use to set the caller_func field.  */
  nested_funcs_size = 32;
  nested_funcs = (struct nest_funcinfo *)
    bfd_malloc (nested_funcs_size * sizeof (*nested_funcs));
  if (nested_funcs == NULL)
    return FALSE;
  nested_funcs[nesting_level].func = 0;

  while (nesting_level >= 0)
    {
      unsigned int abbrev_number, bytes_read, i;
      struct abbrev_info *abbrev;
      struct attribute attr;
      struct funcinfo *func;
      struct varinfo *var;
      bfd_vma low_pc = 0;
      bfd_vma high_pc = 0;
      bfd_boolean high_pc_relative = FALSE;
      bfd_uint64_t current_offset;

      /* PR 17512: file: 9f405d9d.  */
      if (info_ptr >= info_ptr_end)
	goto fail;

      current_offset = info_ptr - unit->info_ptr_unit;
      abbrev_number = _bfd_safe_read_leb128 (abfd, info_ptr, &bytes_read,
					     FALSE, info_ptr_end);
      info_ptr += bytes_read;

      if (! abbrev_number)
	{
	  nesting_level--;
	  continue;
	}

      abbrev = lookup_abbrev (abbrev_number, unit->abbrevs);
      if (! abbrev)
	{
	  static unsigned int previous_failed_abbrev = -1U;

	  /* Avoid multiple reports of the same missing abbrev.  */
	  if (abbrev_number != previous_failed_abbrev)
	    {
	      _bfd_error_handler
		(_("DWARF error: could not find abbrev number %u"),
		 abbrev_number);
	      previous_failed_abbrev = abbrev_number;
	    }
	  bfd_set_error (bfd_error_bad_value);
	  goto fail;
	}

      if (abbrev->tag == DW_TAG_subprogram
	  || abbrev->tag == DW_TAG_entry_point
	  || abbrev->tag == DW_TAG_inlined_subroutine)
	{
	  size_t amt = sizeof (struct funcinfo);

	  var = NULL;
	  func = (struct funcinfo *) bfd_zalloc (abfd, amt);
	  if (func == NULL)
	    goto fail;
	  func->tag = abbrev->tag;
	  func->prev_func = unit->function_table;
	  unit->function_table = func;
	  unit->number_of_functions++;
	  BFD_ASSERT (!unit->cached);

	  if (func->tag == DW_TAG_inlined_subroutine)
	    for (i = nesting_level; i-- != 0; )
	      if (nested_funcs[i].func)
		{
		  func->caller_func = nested_funcs[i].func;
		  break;
		}
	  nested_funcs[nesting_level].func = func;
	}
      else
	{
	  func = NULL;
	  if (abbrev->tag == DW_TAG_variable)
	    {
	      size_t amt = sizeof (struct varinfo);
	      var = (struct varinfo *) bfd_zalloc (abfd, amt);
	      if (var == NULL)
		goto fail;
	      var->tag = abbrev->tag;
	      var->stack = TRUE;
	      var->prev_var = unit->variable_table;
	      unit->variable_table = var;
	      var->unit_offset = current_offset;
	      /* PR 18205: Missing debug information can cause this
		 var to be attached to an already cached unit.  */
	    }
	  else
	    var = NULL;

	  /* No inline function in scope at this nesting level.  */
	  nested_funcs[nesting_level].func = 0;
	}

      for (i = 0; i < abbrev->num_attrs; ++i)
	{
	  info_ptr = read_attribute (&attr, &abbrev->attrs[i],
				     unit, info_ptr, info_ptr_end);
	  if (info_ptr == NULL)
	    goto fail;

	  if (func)
	    {
	      switch (attr.name)
		{
		case DW_AT_call_file:
		  func->caller_file = concat_filename (unit->line_table,
						       attr.u.val);
		  break;

		case DW_AT_call_line:
		  func->caller_line = attr.u.val;
		  break;

		case DW_AT_abstract_origin:
		case DW_AT_specification:
		  if (!find_abstract_instance (unit, &attr, 0,
					       &func->name,
					       &func->is_linkage,
					       &func->file,
					       &func->line))
		    goto fail;
		  break;

		case DW_AT_name:
		  /* Prefer DW_AT_MIPS_linkage_name or DW_AT_linkage_name
		     over DW_AT_name.  */
		  if (func->name == NULL && is_str_attr (attr.form))
		    {
		      func->name = attr.u.str;
		      if (non_mangled (unit->lang))
			func->is_linkage = TRUE;
		    }
		  break;

		case DW_AT_linkage_name:
		case DW_AT_MIPS_linkage_name:
		  /* PR 16949:  Corrupt debug info can place
		     non-string forms into these attributes.  */
		  if (is_str_attr (attr.form))
		    {
		      func->name = attr.u.str;
		      func->is_linkage = TRUE;
		    }
		  break;

		case DW_AT_low_pc:
		  low_pc = attr.u.val;
		  break;

		case DW_AT_high_pc:
		  high_pc = attr.u.val;
		  high_pc_relative = attr.form != DW_FORM_addr;
		  break;

		case DW_AT_ranges:
		  if (!read_rangelist (unit, &func->arange, attr.u.val))
		    goto fail;
		  break;

		case DW_AT_decl_file:
		  func->file = concat_filename (unit->line_table,
						attr.u.val);
		  break;

		case DW_AT_decl_line:
		  func->line = attr.u.val;
		  break;

		default:
		  break;
		}
	    }
	  else if (var)
	    {
	      switch (attr.name)
		{
		case DW_AT_specification:
		  if (attr.u.val)
		    {
		      struct varinfo * spec_var;

		      spec_var = lookup_var_by_offset (attr.u.val,
						       unit->variable_table);
		      if (spec_var == NULL)
			{	
			  _bfd_error_handler (_("DWARF error: could not find "
						"variable specification "
						"at offset %lx"),
					      (unsigned long) attr.u.val);
			  break;
			}

		      if (var->name == NULL)
			var->name = spec_var->name;
		      if (var->file == NULL)
			var->file = strdup (spec_var->file);
		      if (var->line == 0)
			var->line = spec_var->line;
		      if (var->sec == NULL)
			var->sec = spec_var->sec;
		    }
		  break;

		case DW_AT_name:
		  if (is_str_attr (attr.form))
		    var->name = attr.u.str;
		  break;

		case DW_AT_decl_file:
		  var->file = concat_filename (unit->line_table,
					       attr.u.val);
		  break;

		case DW_AT_decl_line:
		  var->line = attr.u.val;
		  break;

		case DW_AT_external:
		  if (attr.u.val != 0)
		    var->stack = FALSE;
		  break;

		case DW_AT_location:
		  switch (attr.form)
		    {
		    case DW_FORM_block:
		    case DW_FORM_block1:
		    case DW_FORM_block2:
		    case DW_FORM_block4:
		    case DW_FORM_exprloc:
		      if (attr.u.blk->data != NULL
			  && *attr.u.blk->data == DW_OP_addr)
			{
			  var->stack = FALSE;

			  /* Verify that DW_OP_addr is the only opcode in the
			     location, in which case the block size will be 1
			     plus the address size.  */
			  /* ??? For TLS variables, gcc can emit
			     DW_OP_addr <addr> DW_OP_GNU_push_tls_address
			     which we don't handle here yet.  */
			  if (attr.u.blk->size == unit->addr_size + 1U)
			    var->addr = bfd_get (unit->addr_size * 8,
						 unit->abfd,
						 attr.u.blk->data + 1);
			}
		      break;

		    default:
		      break;
		    }
		  break;

		default:
		  break;
		}
	    }
	}

      if (high_pc_relative)
	high_pc += low_pc;

      if (func && high_pc != 0)
	{
	  if (!arange_add (unit, &func->arange, low_pc, high_pc))
	    goto fail;
	}

      if (abbrev->has_children)
	{
	  nesting_level++;

	  if (nesting_level >= nested_funcs_size)
	    {
	      struct nest_funcinfo *tmp;

	      nested_funcs_size *= 2;
	      tmp = (struct nest_funcinfo *)
		bfd_realloc (nested_funcs,
			     nested_funcs_size * sizeof (*nested_funcs));
	      if (tmp == NULL)
		goto fail;
	      nested_funcs = tmp;
	    }
	  nested_funcs[nesting_level].func = 0;
	}
    }

  free (nested_funcs);
  return TRUE;

 fail:
  free (nested_funcs);
  return FALSE;
}
