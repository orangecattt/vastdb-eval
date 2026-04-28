#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* BFD basic types */
typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

typedef unsigned char bfd_byte;
typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;
typedef unsigned long bfd_size_type;

typedef long long bfd_int64_t;
typedef unsigned long long bfd_uint64_t;

/* Forward declarations */
typedef struct bfd bfd;
typedef struct asection asection;
typedef struct bfd_symbol asymbol;

/* BFD error types */
typedef enum bfd_error {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_invalid_target,
  bfd_error_next_malformed_file,
  bfd_error_no_more_archived_files,
  bfd_error_malformed_archive,
  bfd_error_file_not_recognized,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_on_input,
  bfd_error_invalid_error_code
} bfd_error_type;

/* BFD hash table structures */
struct bfd_hash_entry {
  struct bfd_hash_entry *next;
  const char *string;
  unsigned long hash;
};

struct bfd_hash_table {
  struct bfd_hash_entry **table;
  unsigned int size;
  struct bfd_hash_entry *(*newfunc)(struct bfd_hash_entry *,
                                    struct bfd_hash_table *, const char *);
  struct bfd_hash_entry *(*newfunc_with_arg)(struct bfd_hash_entry *,
                                             struct bfd_hash_table *,
                                             const char *);
  void *memory;
};

extern struct bfd_hash_entry *bfd_hash_lookup(struct bfd_hash_table *,
                                              const char *, bfd_boolean create,
                                              bfd_boolean copy);
extern struct bfd_hash_entry *bfd_hash_insert(struct bfd_hash_table *,
                                              const char *, unsigned long);
extern void *bfd_hash_allocate(struct bfd_hash_table *, bfd_size_type);

/* BFD memory allocation functions */
extern void *bfd_malloc(bfd_size_type);
extern void *bfd_realloc(void *, bfd_size_type);
extern void *bfd_alloc(bfd *, bfd_size_type);
extern void *bfd_zalloc(bfd *, bfd_size_type);

/* BFD error handling */
extern void bfd_set_error(bfd_error_type error_tag, ...);
extern void _bfd_error_handler(const char *, ...);

/* objalloc structure */
struct objalloc {
  void *current_chunk;
  void *chunks;
};

extern void *_objalloc_alloc(struct objalloc *, unsigned long);
#define objalloc_alloc(o, l) _objalloc_alloc((o), (l))

/* DWARF form enum */
enum dwarf_form {
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
  DW_FORM_strx = 0x1a,
  DW_FORM_addrx = 0x1b,
  DW_FORM_ref_sup4 = 0x1c,
  DW_FORM_strp_sup = 0x1d,
  DW_FORM_data16 = 0x1e,
  DW_FORM_line_strp = 0x1f,
  DW_FORM_implicit_const = 0x21,
  DW_FORM_loclistx = 0x22,
  DW_FORM_rnglistx = 0x23,
  DW_FORM_ref_sup8 = 0x24,
  DW_FORM_GNU_addr_index = 0x1f01,
  DW_FORM_GNU_str_index = 0x1f02,
  DW_FORM_GNU_ref_alt = 0x1f20,
  DW_FORM_GNU_strp_alt = 0x1f21
};

/* DWARF attribute enum */
enum dwarf_attribute {
  DW_AT_sibling = 0x01,
  DW_AT_location = 0x02,
  DW_AT_name = 0x03,
  DW_AT_ordering = 0x09,
  DW_AT_subscr_data = 0x0a,
  DW_AT_byte_size = 0x0b,
  DW_AT_bit_offset = 0x0c,
  DW_AT_bit_size = 0x0d,
  DW_AT_element_list = 0x0f,
  DW_AT_stmt_list = 0x10,
  DW_AT_low_pc = 0x11,
  DW_AT_high_pc = 0x12,
  DW_AT_language = 0x13,
  DW_AT_member = 0x14,
  DW_AT_discr = 0x15,
  DW_AT_discr_value = 0x16,
  DW_AT_string_length = 0x19,
  DW_AT_common_reference = 0x1a,
  DW_AT_comp_dir = 0x1b,
  DW_AT_const_value = 0x1c,
  DW_AT_containing_type = 0x1d,
  DW_AT_default_value = 0x1e,
  DW_AT_inline = 0x20,
  DW_AT_is_optional = 0x21,
  DW_AT_lower_bound = 0x22,
  DW_AT_producer = 0x25,
  DW_AT_prototyped = 0x27,
  DW_AT_return_addr = 0x2a,
  DW_AT_abstract_origin = 0x31,
  DW_AT_start_scope = 0x2c,
  DW_AT_bit_stride = 0x2e,
  DW_AT_upper_bound = 0x2f,
  DW_AT_call_file = 0x5a,
  DW_AT_call_line = 0x5b,
  DW_AT_linkage_name = 0x6e,
  DW_AT_MIPS_linkage_name = 0x2007,
  DW_AT_decl_file = 0x3a,
  DW_AT_decl_line = 0x3b,
  DW_AT_external = 0x3f,
  DW_AT_specification = 0x47,
  DW_AT_ranges = 0x55
};

/* DWARF tag enum */
enum dwarf_tag {
  DW_TAG_array_type = 0x01,
  DW_TAG_class_type = 0x02,
  DW_TAG_entry_point = 0x03,
  DW_TAG_enumeration_type = 0x04,
  DW_TAG_formal_parameter = 0x05,
  DW_TAG_imported_declaration = 0x08,
  DW_TAG_label = 0x0a,
  DW_TAG_lexical_block = 0x0b,
  DW_TAG_member = 0x0d,
  DW_TAG_pointer_type = 0x0f,
  DW_TAG_reference_type = 0x10,
  DW_TAG_compile_unit = 0x11,
  DW_TAG_string_type = 0x12,
  DW_TAG_structure_type = 0x13,
  DW_TAG_subroutine_type = 0x15,
  DW_TAG_typedef = 0x16,
  DW_TAG_union_type = 0x17,
  DW_TAG_unspecified_parameters = 0x18,
  DW_TAG_variant = 0x19,
  DW_TAG_common_block = 0x1a,
  DW_TAG_common_inclusion = 0x1b,
  DW_TAG_inheritance = 0x1c,
  DW_TAG_inlined_subroutine = 0x1d,
  DW_TAG_module = 0x1e,
  DW_TAG_ptr_to_member_type = 0x1f,
  DW_TAG_set_type = 0x20,
  DW_TAG_subrange_type = 0x21,
  DW_TAG_with_stmt = 0x22,
  DW_TAG_access_declaration = 0x23,
  DW_TAG_base_type = 0x24,
  DW_TAG_catch_block = 0x25,
  DW_TAG_const_type = 0x26,
  DW_TAG_constant = 0x27,
  DW_TAG_enumerator = 0x28,
  DW_TAG_file_type = 0x29,
  DW_TAG_friend = 0x2a,
  DW_TAG_namelist = 0x2b,
  DW_TAG_namelist_item = 0x2c,
  DW_TAG_packed_type = 0x2d,
  DW_TAG_subprogram = 0x2e,
  DW_TAG_template_type_param = 0x2f,
  DW_TAG_template_value_param = 0x30,
  DW_TAG_thrown_type = 0x31,
  DW_TAG_try_block = 0x32,
  DW_TAG_variant_part = 0x33,
  DW_TAG_variable = 0x34,
  DW_TAG_volatile_type = 0x35
};

/* DWARF location atom enum */
enum dwarf_location_atom {
  DW_OP_addr = 0x03,
  DW_OP_deref = 0x06,
  DW_OP_const1u = 0x08,
  DW_OP_const1s = 0x09,
  DW_OP_const2u = 0x0a,
  DW_OP_const2s = 0x0b,
  DW_OP_const4u = 0x0c,
  DW_OP_const4s = 0x0d,
  DW_OP_const8u = 0x0e,
  DW_OP_const8s = 0x0f,
  DW_OP_constu = 0x10,
  DW_OP_consts = 0x11,
  DW_OP_dup = 0x12,
  DW_OP_drop = 0x13,
  DW_OP_over = 0x14,
  DW_OP_pick = 0x15,
  DW_OP_swap = 0x16,
  DW_OP_rot = 0x17,
  DW_OP_xderef = 0x18,
  DW_OP_abs = 0x19,
  DW_OP_and = 0x1a,
  DW_OP_div = 0x1b,
  DW_OP_minus = 0x1c,
  DW_OP_mod = 0x1d,
  DW_OP_mul = 0x1e,
  DW_OP_neg = 0x1f,
  DW_OP_not = 0x20,
  DW_OP_or = 0x21,
  DW_OP_plus = 0x22,
  DW_OP_plus_uconst = 0x23,
  DW_OP_shl = 0x24,
  DW_OP_shr = 0x25,
  DW_OP_shra = 0x26,
  DW_OP_xor = 0x27,
  DW_OP_bra = 0x28,
  DW_OP_eq = 0x29,
  DW_OP_ge = 0x2a,
  DW_OP_gt = 0x2b,
  DW_OP_le = 0x2c,
  DW_OP_lt = 0x2d,
  DW_OP_ne = 0x2e,
  DW_OP_skip = 0x2f,
  DW_OP_lit0 = 0x30,
  DW_OP_reg0 = 0x50,
  DW_OP_breg0 = 0x70,
  DW_OP_regx = 0x90,
  DW_OP_fbreg = 0x91,
  DW_OP_bregx = 0x92,
  DW_OP_piece = 0x93,
  DW_OP_deref_size = 0x94,
  DW_OP_xderef_size = 0x95,
  DW_OP_nop = 0x96,
  DW_OP_push_object_address = 0x97,
  DW_OP_call2 = 0x98,
  DW_OP_call4 = 0x99,
  DW_OP_call_ref = 0x9a,
  DW_OP_form_tls_address = 0x9b,
  DW_OP_call_frame_cfa = 0x9c,
  DW_OP_bit_piece = 0x9d,
  DW_OP_implicit_value = 0x9e,
  DW_OP_stack_value = 0x9f,
  DW_OP_GNU_push_tls_address = 0xe0
};

/* DWARF blocks */
struct dwarf_block {
  unsigned int size;
  bfd_byte *data;
};

/* Attribute structure - must be before forward declarations that use it */
struct attribute {
  enum dwarf_attribute name;
  enum dwarf_form form;
  union {
    char *str;
    struct dwarf_block *blk;
    bfd_uint64_t val;
    bfd_int64_t sval;
  } u;
};

/* BFD hash info structures */
struct info_list_node {
  struct info_list_node *next;
  void *info;
};

struct info_hash_entry {
  struct bfd_hash_entry root;
  struct info_list_node *head;
};

struct info_hash_table {
  struct bfd_hash_table base;
};

/* Abbreviation structures */
struct attr_abbrev {
  enum dwarf_attribute name;
  enum dwarf_form form;
  bfd_vma implicit_const;
};

struct abbrev_info {
  unsigned int number;
  enum dwarf_tag tag;
  int has_children;
  unsigned int num_attrs;
  struct attr_abbrev *attrs;
  struct abbrev_info *next;
};

/* Range structure */
struct arange {
  struct arange *next;
  bfd_vma low;
  bfd_vma high;
};

/* Line info table forward declaration */
struct line_info_table;

/* Function info structure */
struct funcinfo {
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

/* Variable info structure */
struct varinfo {
  struct varinfo *prev_var;
  char *file;
  int line;
  int tag;
  char *name;
  bfd_vma addr;
  asection *sec;
  unsigned int stack : 1;
};

/* Lookup function info structure */
struct lookup_funcinfo {
  struct funcinfo *funcinfo;
  bfd_vma low_addr;
  bfd_vma high_addr;
};

/* Compilation unit structure */
struct comp_unit {
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
  bfd_byte *sec_info_ptr;
  unsigned long line_offset;
  bfd_byte *first_child_die_ptr;
  bfd_byte *end_ptr;
  struct line_info_table *line_table;
  struct funcinfo *function_table;
  struct lookup_funcinfo *lookup_funcinfo_table;
  bfd_size_type number_of_functions;
  struct varinfo *variable_table;
  struct dwarf2_debug *stash;
  int version;
  unsigned char addr_size;
  unsigned char offset_size;
  bfd_vma base_address;
  bfd_boolean cached;
};

/* DWARF2 debug stash structure */
struct dwarf2_debug {
  struct comp_unit *all_comp_units;
  struct comp_unit *last_comp_unit;
  const void *debug_sections;
  bfd_byte *info_ptr;
  bfd_byte *info_ptr_end;
  bfd *orig_bfd;
  bfd *bfd_ptr;
  asection *sec;
  bfd_byte *sec_info_ptr;
  bfd *alt_bfd_ptr;
  bfd_byte *alt_dwarf_str_buffer;
  bfd_size_type alt_dwarf_str_size;
  bfd_byte *alt_dwarf_info_buffer;
  bfd_size_type alt_dwarf_info_size;
  bfd_byte *info_ptr_memory;
  asymbol **syms;
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
  struct funcinfo *inliner_chain;
  bfd_vma *sec_vma;
  int adjusted_section_count;
  void *adjusted_sections;
  int info_hash_count;
  struct info_hash_table *funcinfo_hash_table;
  struct info_hash_table *varinfo_hash_table;
  struct comp_unit *hash_units_head;
  int info_hash_status;
  bfd_boolean close_on_cleanup;
};

#define STASH_INFO_HASH_OFF 0
#define STASH_INFO_HASH_ON 1
#define STASH_INFO_HASH_DISABLED 2

/* BFD assertion macro */
#define BFD_ASSERT(x) ((void)0)

/* Gettext macro */
#define _(String) (String)

/* LEB128 reading */
extern bfd_vma _bfd_safe_read_leb128(bfd *, bfd_byte *, unsigned int *,
                                     bfd_boolean, bfd_byte *);

/* Byte reading functions */
extern bfd_vma read_1_byte(bfd *, bfd_byte *, bfd_byte *);
extern bfd_vma read_2_bytes(bfd *, bfd_byte *, bfd_byte *);
extern bfd_vma read_4_bytes(bfd *, bfd_byte *, bfd_byte *);
extern bfd_vma read_8_bytes(bfd *, bfd_byte *, bfd_byte *);
extern bfd_byte *read_n_bytes(bfd *, bfd_byte *, bfd_byte *, bfd_size_type);
extern char *read_string(bfd *, bfd_byte *, bfd_byte *, unsigned int *);

/* Address and string reading functions */
extern bfd_vma read_address(struct comp_unit *, bfd_byte *, bfd_byte *);
extern char *read_indirect_string(struct comp_unit *, bfd_byte *, bfd_byte *,
                                  unsigned int *);
extern char *read_indirect_line_string(struct comp_unit *, bfd_byte *,
                                       bfd_byte *, unsigned int *);
extern char *read_alt_indirect_string(struct comp_unit *, bfd_byte *,
                                      bfd_byte *, unsigned int *);

/* Abbreviation lookup */
extern struct abbrev_info *lookup_abbrev(unsigned int, struct abbrev_info **);

/* Abstract instance name resolution */
extern bfd_boolean find_abstract_instance_name(struct comp_unit *, bfd_byte *,
                                               struct attribute *,
                                               const char **, bfd_boolean *);

/* Range list reading */
extern bfd_boolean read_rangelist(struct comp_unit *, struct arange *, bfd_vma);

/* Range addition */
extern bfd_boolean arange_add(const struct comp_unit *, struct arange *,
                              bfd_vma, bfd_vma);

/* Line info decoding */
extern struct line_info_table *decode_line_info(struct comp_unit *,
                                                struct dwarf2_debug *);

/* Filename concatenation */
extern char *concat_filename(struct line_info_table *, unsigned int);

/* Language check */
extern bfd_boolean non_mangled(int);

/* List reversal functions */
extern struct funcinfo *reverse_funcinfo_list(struct funcinfo *);
extern struct varinfo *reverse_varinfo_list(struct varinfo *);

/* BFD byte reading functions and macros */
extern bfd_vma bfd_get_8(bfd *, const void *);
extern bfd_vma bfd_get_16(bfd *, const void *);
extern bfd_vma bfd_get_32(bfd *, const void *);
extern bfd_vma bfd_get_64(bfd *, const void *);

#define bfd_get(bits, abfd, ptr)                                               \
  ((bits) == 8    ? (bfd_vma)bfd_get_8(abfd, ptr)                              \
   : (bits) == 16 ? bfd_get_16(abfd, ptr)                                      \
   : (bits) == 32 ? bfd_get_32(abfd, ptr)                                      \
   : (bits) == 64 ? bfd_get_64(abfd, ptr)                                      \
                  : (abort(), (bfd_vma) - 1))

static inline unsigned long bfd_hash_hash(const char *string,
                                          unsigned int *lenp) {
  const unsigned char *s;
  unsigned long hash;
  unsigned int len;
  unsigned int c;

  hash = 0;
  len = 0;
  s = (const unsigned char *)string;
  while ((c = *s++) != '\0') {
    hash += c + (c << 17);
    hash ^= hash >> 2;
  }
  len = (s - (const unsigned char *)string) - 1;
  hash += len + (len << 17);
  hash ^= hash >> 2;
  if (lenp != NULL)
    *lenp = len;
  return hash;
}

struct bfd_hash_entry *bfd_hash_lookup(struct bfd_hash_table *table,
                                       const char *string, bfd_boolean create,
                                       bfd_boolean copy) {
  unsigned long hash;
  struct bfd_hash_entry *hashp;
  unsigned int len;
  unsigned int _index;

  hash = bfd_hash_hash(string, &len);
  _index = hash % table->size;
  for (hashp = table->table[_index]; hashp != NULL; hashp = hashp->next) {
    if (hashp->hash == hash && strcmp(hashp->string, string) == 0)
      return hashp;
  }

  if (!create)
    return NULL;

  if (copy) {
    char *new_string;

    new_string =
        (char *)objalloc_alloc((struct objalloc *)table->memory, len + 1);
    if (!new_string) {
      bfd_set_error(bfd_error_no_memory);
      return NULL;
    }
    memcpy(new_string, string, len + 1);
    string = new_string;
  }

  return bfd_hash_insert(table, string, hash);
}

static bfd_boolean insert_info_hash_table(struct info_hash_table *hash_table,
                                          const char *key, void *info,
                                          bfd_boolean copy_p) {
  struct info_hash_entry *entry;
  struct info_list_node *node;

  entry = (struct info_hash_entry *)bfd_hash_lookup(&hash_table->base, key,
                                                    TRUE, copy_p);
  if (!entry)
    return FALSE;

  node = (struct info_list_node *)bfd_hash_allocate(&hash_table->base,
                                                    sizeof(*node));
  if (!node)
    return FALSE;

  node->info = info;
  node->next = entry->head;
  entry->head = node;

  return TRUE;
}

static inline bfd_boolean is_str_attr(enum dwarf_form form) {
  return (form == DW_FORM_string || form == DW_FORM_strp ||
          form == DW_FORM_line_strp || form == DW_FORM_GNU_strp_alt);
}

static bfd_byte *read_attribute_value(struct attribute *attr, unsigned form,
                                      bfd_vma implicit_const,
                                      struct comp_unit *unit,
                                      bfd_byte *info_ptr,
                                      bfd_byte *info_ptr_end) {
  bfd *abfd = unit->abfd;
  unsigned int bytes_read;
  struct dwarf_block *blk;
  bfd_size_type amt;

  if (info_ptr >= info_ptr_end && form != DW_FORM_flag_present) {
    _bfd_error_handler(
        _("Dwarf Error: Info pointer extends beyond end of attributes"));
    bfd_set_error(bfd_error_bad_value);
    return info_ptr;
  }

  attr->form = (enum dwarf_form)form;

  switch (form) {
  case DW_FORM_ref_addr:
    /* DW_FORM_ref_addr is an address in DWARF2, and an offset in
       DWARF3.  */
    if (unit->version == 3 || unit->version == 4) {
      if (unit->offset_size == 4)
        attr->u.val = read_4_bytes(unit->abfd, info_ptr, info_ptr_end);
      else
        attr->u.val = read_8_bytes(unit->abfd, info_ptr, info_ptr_end);
      info_ptr += unit->offset_size;
      break;
    }
    /* FALLTHROUGH */
  case DW_FORM_addr:
    attr->u.val = read_address(unit, info_ptr, info_ptr_end);
    info_ptr += unit->addr_size;
    break;
  case DW_FORM_GNU_ref_alt:
  case DW_FORM_sec_offset:
    if (unit->offset_size == 4)
      attr->u.val = read_4_bytes(unit->abfd, info_ptr, info_ptr_end);
    else
      attr->u.val = read_8_bytes(unit->abfd, info_ptr, info_ptr_end);
    info_ptr += unit->offset_size;
    break;
  case DW_FORM_block2:
    amt = sizeof(struct dwarf_block);
    blk = (struct dwarf_block *)bfd_alloc(abfd, amt);
    if (blk == NULL)
      return NULL;
    blk->size = read_2_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 2;
    blk->data = read_n_bytes(abfd, info_ptr, info_ptr_end, blk->size);
    info_ptr += blk->size;
    attr->u.blk = blk;
    break;
  case DW_FORM_block4:
    amt = sizeof(struct dwarf_block);
    blk = (struct dwarf_block *)bfd_alloc(abfd, amt);
    if (blk == NULL)
      return NULL;
    blk->size = read_4_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 4;
    blk->data = read_n_bytes(abfd, info_ptr, info_ptr_end, blk->size);
    info_ptr += blk->size;
    attr->u.blk = blk;
    break;
  case DW_FORM_data2:
    attr->u.val = read_2_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 2;
    break;
  case DW_FORM_data4:
    attr->u.val = read_4_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 4;
    break;
  case DW_FORM_data8:
    attr->u.val = read_8_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 8;
    break;
  case DW_FORM_string:
    attr->u.str = read_string(abfd, info_ptr, info_ptr_end, &bytes_read);
    info_ptr += bytes_read;
    break;
  case DW_FORM_strp:
    attr->u.str =
        read_indirect_string(unit, info_ptr, info_ptr_end, &bytes_read);
    info_ptr += bytes_read;
    break;
  case DW_FORM_line_strp:
    attr->u.str =
        read_indirect_line_string(unit, info_ptr, info_ptr_end, &bytes_read);
    info_ptr += bytes_read;
    break;
  case DW_FORM_GNU_strp_alt:
    attr->u.str =
        read_alt_indirect_string(unit, info_ptr, info_ptr_end, &bytes_read);
    info_ptr += bytes_read;
    break;
  case DW_FORM_exprloc:
  case DW_FORM_block:
    amt = sizeof(struct dwarf_block);
    blk = (struct dwarf_block *)bfd_alloc(abfd, amt);
    if (blk == NULL)
      return NULL;
    blk->size =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, FALSE, info_ptr_end);
    info_ptr += bytes_read;
    blk->data = read_n_bytes(abfd, info_ptr, info_ptr_end, blk->size);
    info_ptr += blk->size;
    attr->u.blk = blk;
    break;
  case DW_FORM_block1:
    amt = sizeof(struct dwarf_block);
    blk = (struct dwarf_block *)bfd_alloc(abfd, amt);
    if (blk == NULL)
      return NULL;
    blk->size = read_1_byte(abfd, info_ptr, info_ptr_end);
    info_ptr += 1;
    blk->data = read_n_bytes(abfd, info_ptr, info_ptr_end, blk->size);
    info_ptr += blk->size;
    attr->u.blk = blk;
    break;
  case DW_FORM_data1:
    attr->u.val = read_1_byte(abfd, info_ptr, info_ptr_end);
    info_ptr += 1;
    break;
  case DW_FORM_flag:
    attr->u.val = read_1_byte(abfd, info_ptr, info_ptr_end);
    info_ptr += 1;
    break;
  case DW_FORM_flag_present:
    attr->u.val = 1;
    break;
  case DW_FORM_sdata:
    attr->u.sval =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, TRUE, info_ptr_end);
    info_ptr += bytes_read;
    break;
  case DW_FORM_udata:
    attr->u.val =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, FALSE, info_ptr_end);
    info_ptr += bytes_read;
    break;
  case DW_FORM_ref1:
    attr->u.val = read_1_byte(abfd, info_ptr, info_ptr_end);
    info_ptr += 1;
    break;
  case DW_FORM_ref2:
    attr->u.val = read_2_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 2;
    break;
  case DW_FORM_ref4:
    attr->u.val = read_4_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 4;
    break;
  case DW_FORM_ref8:
    attr->u.val = read_8_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 8;
    break;
  case DW_FORM_ref_sig8:
    attr->u.val = read_8_bytes(abfd, info_ptr, info_ptr_end);
    info_ptr += 8;
    break;
  case DW_FORM_ref_udata:
    attr->u.val =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, FALSE, info_ptr_end);
    info_ptr += bytes_read;
    break;
  case DW_FORM_indirect:
    form =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, FALSE, info_ptr_end);
    info_ptr += bytes_read;
    if (form == DW_FORM_implicit_const) {
      implicit_const = _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, TRUE,
                                             info_ptr_end);
      info_ptr += bytes_read;
    }
    info_ptr = read_attribute_value(attr, form, implicit_const, unit, info_ptr,
                                    info_ptr_end);
    break;
  case DW_FORM_implicit_const:
    attr->form = DW_FORM_sdata;
    attr->u.sval = implicit_const;
    break;
  default:
    _bfd_error_handler(_("Dwarf Error: Invalid or unhandled FORM value: %#x."),
                       form);
    bfd_set_error(bfd_error_bad_value);
    return NULL;
  }
  return info_ptr;
}

static bfd_byte *read_attribute(struct attribute *attr,
                                struct attr_abbrev *abbrev,
                                struct comp_unit *unit, bfd_byte *info_ptr,
                                bfd_byte *info_ptr_end) {
  attr->name = abbrev->name;
  info_ptr = read_attribute_value(attr, abbrev->form, abbrev->implicit_const,
                                  unit, info_ptr, info_ptr_end);
  return info_ptr;
}

static bfd_boolean scan_unit_for_symbols(struct comp_unit *unit) {
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr = unit->first_child_die_ptr;
  bfd_byte *info_ptr_end = unit->stash->info_ptr_end;
  int nesting_level = 0;
  struct nest_funcinfo {
    struct funcinfo *func;
  } *nested_funcs;
  int nested_funcs_size;

  /* Maintain a stack of in-scope functions and inlined functions, which we
     can use to set the caller_func field.  */
  nested_funcs_size = 32;
  nested_funcs = (struct nest_funcinfo *)bfd_malloc(nested_funcs_size *
                                                    sizeof(*nested_funcs));
  if (nested_funcs == NULL)
    return FALSE;
  nested_funcs[nesting_level].func = 0;

  while (nesting_level >= 0) {
    unsigned int abbrev_number, bytes_read, i;
    struct abbrev_info *abbrev;
    struct attribute attr;
    struct funcinfo *func;
    struct varinfo *var;
    bfd_vma low_pc = 0;
    bfd_vma high_pc = 0;
    bfd_boolean high_pc_relative = FALSE;

    /* PR 17512: file: 9f405d9d.  */
    if (info_ptr >= info_ptr_end)
      goto fail;

    abbrev_number =
        _bfd_safe_read_leb128(abfd, info_ptr, &bytes_read, FALSE, info_ptr_end);
    info_ptr += bytes_read;

    if (!abbrev_number) {
      nesting_level--;
      continue;
    }

    abbrev = lookup_abbrev(abbrev_number, unit->abbrevs);
    if (!abbrev) {
      static unsigned int previous_failed_abbrev = -1U;

      /* Avoid multiple reports of the same missing abbrev.  */
      if (abbrev_number != previous_failed_abbrev) {
        _bfd_error_handler(_("Dwarf Error: Could not find abbrev number %u."),
                           abbrev_number);
        previous_failed_abbrev = abbrev_number;
      }
      bfd_set_error(bfd_error_bad_value);
      goto fail;
    }

    var = NULL;
    if (abbrev->tag == DW_TAG_subprogram || abbrev->tag == DW_TAG_entry_point ||
        abbrev->tag == DW_TAG_inlined_subroutine) {
      bfd_size_type amt = sizeof(struct funcinfo);
      func = (struct funcinfo *)bfd_zalloc(abfd, amt);
      if (func == NULL)
        goto fail;
      func->tag = abbrev->tag;
      func->prev_func = unit->function_table;
      unit->function_table = func;
      unit->number_of_functions++;
      BFD_ASSERT(!unit->cached);

      if (func->tag == DW_TAG_inlined_subroutine)
        for (i = nesting_level; i-- != 0;)
          if (nested_funcs[i].func) {
            func->caller_func = nested_funcs[i].func;
            break;
          }
      nested_funcs[nesting_level].func = func;
    } else {
      func = NULL;
      if (abbrev->tag == DW_TAG_variable) {
        bfd_size_type amt = sizeof(struct varinfo);
        var = (struct varinfo *)bfd_zalloc(abfd, amt);
        if (var == NULL)
          goto fail;
        var->tag = abbrev->tag;
        var->stack = 1;
        var->prev_var = unit->variable_table;
        unit->variable_table = var;
        /* PR 18205: Missing debug information can cause this
           var to be attached to an already cached unit.  */
      }

      /* No inline function in scope at this nesting level.  */
      nested_funcs[nesting_level].func = 0;
    }

    for (i = 0; i < abbrev->num_attrs; ++i) {
      info_ptr = read_attribute(&attr, &abbrev->attrs[i], unit, info_ptr,
                                info_ptr_end);
      if (info_ptr == NULL)
        goto fail;

      if (func) {
        switch (attr.name) {
        case DW_AT_call_file:
          func->caller_file = concat_filename(unit->line_table, attr.u.val);
          break;

        case DW_AT_call_line:
          func->caller_line = attr.u.val;
          break;

        case DW_AT_abstract_origin:
        case DW_AT_specification:
          if (!find_abstract_instance_name(unit, info_ptr, &attr, &func->name,
                                           &func->is_linkage))
            goto fail;
          break;

        case DW_AT_name:
          /* Prefer DW_AT_MIPS_linkage_name or DW_AT_linkage_name
             over DW_AT_name.  */
          if (func->name == NULL && is_str_attr(attr.form)) {
            func->name = attr.u.str;
            if (non_mangled(unit->lang))
              func->is_linkage = TRUE;
          }
          break;

        case DW_AT_linkage_name:
        case DW_AT_MIPS_linkage_name:
          /* PR 16949:  Corrupt debug info can place
             non-string forms into these attributes.  */
          if (is_str_attr(attr.form)) {
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
          if (!read_rangelist(unit, &func->arange, attr.u.val))
            goto fail;
          break;

        case DW_AT_decl_file:
          func->file = concat_filename(unit->line_table, attr.u.val);
          break;

        case DW_AT_decl_line:
          func->line = attr.u.val;
          break;

        default:
          break;
        }
      } else if (var) {
        switch (attr.name) {
        case DW_AT_name:
          var->name = attr.u.str;
          break;

        case DW_AT_decl_file:
          var->file = concat_filename(unit->line_table, attr.u.val);
          break;

        case DW_AT_decl_line:
          var->line = attr.u.val;
          break;

        case DW_AT_external:
          if (attr.u.val != 0)
            var->stack = 0;
          break;

        case DW_AT_location:
          switch (attr.form) {
          case DW_FORM_block:
          case DW_FORM_block1:
          case DW_FORM_block2:
          case DW_FORM_block4:
          case DW_FORM_exprloc:
            if (attr.u.blk->data != NULL && *attr.u.blk->data == DW_OP_addr) {
              var->stack = 0;

              /* Verify that DW_OP_addr is the only opcode in the
                 location, in which case the block size will be 1
                 plus the address size.  */
              /* ??? For TLS variables, gcc can emit
                 DW_OP_addr <addr> DW_OP_GNU_push_tls_address
                 which we don't handle here yet.  */
              if (attr.u.blk->size == unit->addr_size + 1U)
                var->addr = bfd_get(unit->addr_size * 8, unit->abfd,
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

    if (func && high_pc != 0) {
      if (!arange_add(unit, &func->arange, low_pc, high_pc))
        goto fail;
    }

    if (abbrev->has_children) {
      nesting_level++;

      if (nesting_level >= nested_funcs_size) {
        struct nest_funcinfo *tmp;

        nested_funcs_size *= 2;
        tmp = (struct nest_funcinfo *)bfd_realloc(
            nested_funcs, nested_funcs_size * sizeof(*nested_funcs));
        if (tmp == NULL)
          goto fail;
        nested_funcs = tmp;
      }
      nested_funcs[nesting_level].func = 0;
    }
  }

  free(nested_funcs);
  return TRUE;

fail:
  free(nested_funcs);
  return FALSE;
}

static bfd_boolean
comp_unit_maybe_decode_line_info(struct comp_unit *unit,
                                 struct dwarf2_debug *stash) {
  if (unit->error)
    return FALSE;

  if (!unit->line_table) {
    if (!unit->stmtlist) {
      unit->error = 1;
      return FALSE;
    }

    unit->line_table = decode_line_info(unit, stash);

    if (!unit->line_table) {
      unit->error = 1;
      return FALSE;
    }

    if (unit->first_child_die_ptr < unit->end_ptr &&
        !scan_unit_for_symbols(unit)) {
      unit->error = 1;
      return FALSE;
    }
  }

  return TRUE;
}

static bfd_boolean
comp_unit_hash_info(struct dwarf2_debug *stash, struct comp_unit *unit,
                    struct info_hash_table *funcinfo_hash_table,
                    struct info_hash_table *varinfo_hash_table) {
  struct funcinfo *each_func;
  struct varinfo *each_var;
  bfd_boolean okay = TRUE;

  BFD_ASSERT(stash->info_hash_status != STASH_INFO_HASH_DISABLED);

  if (!comp_unit_maybe_decode_line_info(unit, stash))
    return FALSE;

  BFD_ASSERT(!unit->cached);

  /* To preserve the original search order, we went to visit the function
     infos in the reversed order of the list.  However, making the list
     bi-directional use quite a bit of extra memory.  So we reverse
     the list first, traverse the list in the now reversed order and
     finally reverse the list again to get back the original order.  */
  unit->function_table = reverse_funcinfo_list(unit->function_table);
  for (each_func = unit->function_table; each_func && okay;
       each_func = each_func->prev_func) {
    /* Skip nameless functions.  */
    if (each_func->name)
      /* There is no need to copy name string into hash table as
         name string is either in the dwarf string buffer or
         info in the stash.  */
      okay = insert_info_hash_table(funcinfo_hash_table, each_func->name,
                                    (void *)each_func, FALSE);
  }
  unit->function_table = reverse_funcinfo_list(unit->function_table);
  if (!okay)
    return FALSE;

  /* We do the same for variable infos.  */
  unit->variable_table = reverse_varinfo_list(unit->variable_table);
  for (each_var = unit->variable_table; each_var && okay;
       each_var = each_var->prev_var) {
    /* Skip stack vars and vars with no files or names.  */
    if (each_var->stack == 0 && each_var->file != NULL &&
        each_var->name != NULL)
      /* There is no need to copy name string into hash table as
         name string is either in the dwarf string buffer or
         info in the stash.  */
      okay = insert_info_hash_table(varinfo_hash_table, each_var->name,
                                    (void *)each_var, FALSE);
  }

  unit->variable_table = reverse_varinfo_list(unit->variable_table);
  unit->cached = TRUE;
  return okay;
}
