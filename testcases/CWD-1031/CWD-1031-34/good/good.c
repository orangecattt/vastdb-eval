#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int bfd_boolean;
typedef unsigned char bfd_byte;
typedef unsigned long bfd_vma;
typedef unsigned long bfd_size_type;
typedef unsigned long bfd_uint64_t;
typedef long bfd_int64_t;

typedef struct bfd_symbol {
  const char *name;
  unsigned int flags;
  struct bfd_section *section;
  bfd_vma value;
  struct bfd *the_bfd;
  const char *udata;
} asymbol;

typedef struct bfd_section {
  const char *name;
  unsigned int id;
  unsigned int index;
  struct bfd_section *next;
  struct bfd_section *prev;
  unsigned int flags;
  unsigned int user_set_vma;
  unsigned int linker_mark;
  unsigned int linker_has_input;
  unsigned int gc_mark;
  unsigned int compress_status;
  unsigned int segment_mark;
  unsigned int sec_info_type;
  unsigned int use_rela_p;
  unsigned int sec_flg0;
  unsigned int sec_flg1;
  unsigned int sec_flg2;
  unsigned int sec_flg3;
  unsigned int sec_flg4;
  unsigned int sec_flg5;
  bfd_vma vma;
  bfd_vma lma;
  bfd_size_type size;
  bfd_size_type rawsize;
  bfd_size_type compressed_size;
  void *relax;
  int relax_count;
  bfd_vma output_offset;
  struct bfd_section *output_section;
  unsigned int alignment_power;
  void *relocation;
  void **orelocation;
  unsigned reloc_count;
  long filepos;
  long rel_filepos;
  long line_filepos;
  void *userdata;
  unsigned char *contents;
  void *lineno;
  unsigned int lineno_count;
  unsigned int entsize;
  struct bfd_section *kept_section;
  long moving_line_filepos;
  int target_index;
  void *used_by_bfd;
  void *constructor_chain;
  struct bfd *owner;
  struct bfd_symbol *symbol;
  struct bfd_symbol **symbol_ptr_ptr;
  union {
    void *link_order;
    struct bfd_section *s;
  } map_head, map_tail;
} asection;

typedef struct bfd {
  const char *filename;
  const struct bfd_target *xvec;
  void *iostream;
  void *cacheable;
  void *target_defaulted;
  void *direction;
  void *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  void *archive_pass;
  unsigned int has_armap;
  void *arelt_data;
  struct bfd *my_archive;
  struct bfd *next;
  struct bfd *archive_head;
  struct bfd *nested_archives;
  void *usrdata;
  unsigned int flags;
  unsigned int format;
  unsigned int origin;
  unsigned int where;
  unsigned int iovec;
  void *mtime;
  long mtime_set;
  void *archive_plugin;
  void *plugin_format;
  void *plugin_dummy_bfd;
  unsigned int no_export;
  void *tdata;
  void *used_by_bfd;
  void *archive_data;
  void *archive_search;
  void *archive_next;
  void *archive_pass_count;
  void *archive_pass_done;
  void *archive_pass_total;
} bfd;

#define bfd_get_section(x) ((x)->section)

#define bfd_get_8(abfd, ptr) (*(ptr))
#define bfd_get_16(abfd, ptr) (((unsigned int)((ptr)[0]) << 8) | ((unsigned int)((ptr)[1])))
#define bfd_get_32(abfd, ptr) (((unsigned int)((ptr)[0]) << 24) | ((unsigned int)((ptr)[1]) << 16) | ((unsigned int)((ptr)[2]) << 8) | ((unsigned int)((ptr)[3])))
#define bfd_get_64(abfd, ptr) (((bfd_uint64_t)((ptr)[0]) << 56) | ((bfd_uint64_t)((ptr)[1]) << 48) | ((bfd_uint64_t)((ptr)[2]) << 40) | ((bfd_uint64_t)((ptr)[3]) << 32) | ((bfd_uint64_t)((ptr)[4]) << 24) | ((bfd_uint64_t)((ptr)[5]) << 16) | ((bfd_uint64_t)((ptr)[6]) << 8) | ((bfd_uint64_t)((ptr)[7])))
#define bfd_get(abfd, bits, ptr) ((bits) == 8 ? bfd_get_8(abfd, ptr) : (bits) == 16 ? bfd_get_16(abfd, ptr) : (bits) == 32 ? bfd_get_32(abfd, ptr) : bfd_get_64(abfd, ptr))
#define bfd_get_signed_8(abfd, ptr) ((int)(signed char)(*(ptr)))

#define ATTRIBUTE_UNUSED __attribute__((unused))
#define ATTRIBUTE_PRINTF_1 __attribute__((format(printf, 1, 2)))

extern void *bfd_malloc (bfd_size_type);
extern void *bfd_realloc (void *, bfd_size_type);
extern void *bfd_alloc (bfd *, bfd_size_type);
extern void *bfd_zalloc (bfd *, bfd_size_type);
extern void _bfd_error_handler (const char *s, ...) ATTRIBUTE_PRINTF_1;
extern void bfd_set_error (int error_tag);
extern unsigned int _bfd_safe_read_leb128 (bfd *, const bfd_byte *, unsigned int *, int, const bfd_byte *);

#define bfd_error_bad_value 13

#define _(String) String
#define N_(String) String

#define IS_ABSOLUTE_PATH(f) ((f)[0] == '/')

enum dwarf_tag {
  DW_TAG_array_type = 1,
  DW_TAG_class_type = 2,
  DW_TAG_entry_point = 3,
  DW_TAG_enumeration_type = 4,
  DW_TAG_formal_parameter = 5,
  DW_TAG_imported_declaration = 8,
  DW_TAG_label = 10,
  DW_TAG_lexical_block = 11,
  DW_TAG_member = 13,
  DW_TAG_pointer_type = 15,
  DW_TAG_reference_type = 16,
  DW_TAG_compile_unit = 17,
  DW_TAG_string_type = 19,
  DW_TAG_structure_type = 20,
  DW_TAG_subroutine_type = 21,
  DW_TAG_typedef = 22,
  DW_TAG_union_type = 23,
  DW_TAG_unspecified_parameters = 24,
  DW_TAG_variant = 25,
  DW_TAG_common_block = 26,
  DW_TAG_common_inclusion = 27,
  DW_TAG_inheritance = 28,
  DW_TAG_inlined_subroutine = 29,
  DW_TAG_module = 30,
  DW_TAG_ptr_to_member_type = 31,
  DW_TAG_set_type = 32,
  DW_TAG_subrange_type = 33,
  DW_TAG_with_stmt = 34,
  DW_TAG_access_declaration = 35,
  DW_TAG_base_type = 36,
  DW_TAG_catch_block = 37,
  DW_TAG_const_type = 38,
  DW_TAG_constant = 39,
  DW_TAG_enumerator = 40,
  DW_TAG_file_type = 41,
  DW_TAG_friend = 42,
  DW_TAG_namelist = 43,
  DW_TAG_namelist_item = 44,
  DW_TAG_packed_type = 45,
  DW_TAG_subprogram = 46,
  DW_TAG_template_type_parameter = 47,
  DW_TAG_template_value_parameter = 48,
  DW_TAG_thrown_type = 49,
  DW_TAG_try_block = 50,
  DW_TAG_variant_part = 51,
  DW_TAG_variable = 52,
  DW_TAG_volatile_type = 53,
  DW_TAG_dwarf_procedure = 54,
  DW_TAG_restrict_type = 55,
  DW_TAG_interface_type = 56,
  DW_TAG_namespace = 57,
  DW_TAG_imported_module = 58,
  DW_TAG_unspecified_type = 59,
  DW_TAG_partial_unit = 60,
  DW_TAG_imported_unit = 61,
  DW_TAG_condition = 63,
  DW_TAG_shared_type = 64,
  DW_TAG_type_unit = 65,
  DW_TAG_rvalue_reference_type = 66,
  DW_TAG_template_alias = 67,
  DW_TAG_coarray_type = 68,
  DW_TAG_generic_subrange = 69,
  DW_TAG_dynamic_type = 70,
  DW_TAG_atomic_type = 71,
  DW_TAG_call_site = 72,
  DW_TAG_call_site_parameter = 73,
  DW_TAG_skeleton_unit = 74,
  DW_TAG_immutable_type = 75,
  DW_TAG_lo_user = 0x4080,
  DW_TAG_hi_user = 0xffff
};

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
  DW_FORM_strx = 0x1a,
  DW_FORM_addrx = 0x1b,
  DW_FORM_ref_sig8 = 0x20,
  DW_FORM_implicit_const = 0x21,
  DW_FORM_loclistx = 0x22,
  DW_FORM_rnglistx = 0x23,
  DW_FORM_ref_sup4 = 0x24,
  DW_FORM_strp_sup = 0x25,
  DW_FORM_data16 = 0x26,
  DW_FORM_line_strp = 0x27,
  DW_FORM_GNU_ref_alt = 0x1f21,
  DW_FORM_GNU_strp_alt = 0x1f22,
  DW_FORM_GNU_addr_index = 0x1f01,
  DW_FORM_GNU_str_index = 0x1f02
};

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
  DW_AT_visibility = 0x17,
  DW_AT_import = 0x18,
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
  DW_AT_start_scope = 0x2c,
  DW_AT_stride_size = 0x2e,
  DW_AT_upper_bound = 0x2f,
  DW_AT_abstract_origin = 0x31,
  DW_AT_accessibility = 0x32,
  DW_AT_address_class = 0x33,
  DW_AT_artificial = 0x34,
  DW_AT_base_types = 0x35,
  DW_AT_calling_convention = 0x36,
  DW_AT_count = 0x37,
  DW_AT_data_member_location = 0x38,
  DW_AT_decl_column = 0x39,
  DW_AT_decl_file = 0x3a,
  DW_AT_decl_line = 0x3b,
  DW_AT_declaration = 0x3c,
  DW_AT_discr_list = 0x3d,
  DW_AT_encoding = 0x3e,
  DW_AT_external = 0x3f,
  DW_AT_frame_base = 0x40,
  DW_AT_friend = 0x41,
  DW_AT_identifier_case = 0x42,
  DW_AT_macro_info = 0x43,
  DW_AT_namelist_item = 0x44,
  DW_AT_priority = 0x45,
  DW_AT_segment = 0x46,
  DW_AT_specification = 0x47,
  DW_AT_static_link = 0x48,
  DW_AT_type = 0x49,
  DW_AT_use_location = 0x4a,
  DW_AT_variable_parameter = 0x4b,
  DW_AT_virtuality = 0x4c,
  DW_AT_vtable_elem_location = 0x4d,
  DW_AT_allocated = 0x4e,
  DW_AT_associated = 0x4f,
  DW_AT_data_location = 0x50,
  DW_AT_byte_stride = 0x51,
  DW_AT_entry_pc = 0x52,
  DW_AT_use_UTF8 = 0x53,
  DW_AT_extension = 0x54,
  DW_AT_ranges = 0x55,
  DW_AT_trampoline = 0x56,
  DW_AT_call_column = 0x57,
  DW_AT_call_file = 0x58,
  DW_AT_call_line = 0x59,
  DW_AT_description = 0x5a,
  DW_AT_binary_scale = 0x5b,
  DW_AT_decimal_scale = 0x5c,
  DW_AT_small = 0x5d,
  DW_AT_decimal_sign = 0x5e,
  DW_AT_digit_count = 0x5f,
  DW_AT_picture_string = 0x60,
  DW_AT_mutable = 0x61,
  DW_AT_threads_scaled = 0x62,
  DW_AT_explicit = 0x63,
  DW_AT_object_pointer = 0x64,
  DW_AT_endianity = 0x65,
  DW_AT_elemental = 0x66,
  DW_AT_pure = 0x67,
  DW_AT_recursive = 0x68,
  DW_AT_signature = 0x69,
  DW_AT_main_subprogram = 0x6a,
  DW_AT_data_bit_offset = 0x6b,
  DW_AT_const_expr = 0x6c,
  DW_AT_enum_class = 0x6d,
  DW_AT_linkage_name = 0x6e,
  DW_AT_string_length_bit_size = 0x6f,
  DW_AT_string_length_byte_size = 0x70,
  DW_AT_rank = 0x71,
  DW_AT_str_offsets_base = 0x72,
  DW_AT_addr_base = 0x73,
  DW_AT_rnglists_base = 0x74,
  DW_AT_dwo_name = 0x76,
  DW_AT_reference = 0x77,
  DW_AT_rvalue_reference = 0x78,
  DW_AT_macros = 0x79,
  DW_AT_call_all_calls = 0x7a,
  DW_AT_call_all_source_calls = 0x7b,
  DW_AT_call_all_tail_calls = 0x7c,
  DW_AT_call_return_pc = 0x7d,
  DW_AT_call_value = 0x7e,
  DW_AT_call_origin = 0x7f,
  DW_AT_call_parameter = 0x80,
  DW_AT_call_pc = 0x81,
  DW_AT_call_tail_call = 0x82,
  DW_AT_call_target = 0x83,
  DW_AT_call_target_clobbered = 0x84,
  DW_AT_call_data_location = 0x85,
  DW_AT_call_data_value = 0x86,
  DW_AT_noreturn = 0x87,
  DW_AT_alignment = 0x88,
  DW_AT_export_symbols = 0x89,
  DW_AT_deleted = 0x8a,
  DW_AT_defaulted = 0x8b,
  DW_AT_loclists_base = 0x8c,
  DW_AT_MIPS_fde = 0x2001,
  DW_AT_MIPS_loop_begin = 0x2002,
  DW_AT_MIPS_tail_loop_begin = 0x2003,
  DW_AT_MIPS_epilog_begin = 0x2004,
  DW_AT_MIPS_loop_unroll_factor = 0x2005,
  DW_AT_MIPS_software_pipeline_depth = 0x2006,
  DW_AT_MIPS_linkage_name = 0x2007,
  DW_AT_MIPS_stride = 0x2008,
  DW_AT_MIPS_abstract_name = 0x2009,
  DW_AT_MIPS_clone_origin = 0x200a,
  DW_AT_MIPS_has_inlines = 0x200b,
  DW_AT_MIPS_stride_byte = 0x200c,
  DW_AT_MIPS_stride_elem = 0x200d,
  DW_AT_MIPS_ptr_dopetype = 0x200e,
  DW_AT_MIPS_allocatable_dopetype = 0x200f,
  DW_AT_MIPS_assumed_shape = 0x2010,
  DW_AT_MIPS_assumed_size = 0x2011
};

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
  DW_OP_lit1 = 0x31,
  DW_OP_lit2 = 0x32,
  DW_OP_lit3 = 0x33,
  DW_OP_lit4 = 0x34,
  DW_OP_lit5 = 0x35,
  DW_OP_lit6 = 0x36,
  DW_OP_lit7 = 0x37,
  DW_OP_lit8 = 0x38,
  DW_OP_lit9 = 0x39,
  DW_OP_lit10 = 0x3a,
  DW_OP_lit11 = 0x3b,
  DW_OP_lit12 = 0x3c,
  DW_OP_lit13 = 0x3d,
  DW_OP_lit14 = 0x3e,
  DW_OP_lit15 = 0x3f,
  DW_OP_lit16 = 0x40,
  DW_OP_lit17 = 0x41,
  DW_OP_lit18 = 0x42,
  DW_OP_lit19 = 0x43,
  DW_OP_lit20 = 0x44,
  DW_OP_lit21 = 0x45,
  DW_OP_lit22 = 0x46,
  DW_OP_lit23 = 0x47,
  DW_OP_lit24 = 0x48,
  DW_OP_lit25 = 0x49,
  DW_OP_lit26 = 0x4a,
  DW_OP_lit27 = 0x4b,
  DW_OP_lit28 = 0x4c,
  DW_OP_lit29 = 0x4d,
  DW_OP_lit30 = 0x4e,
  DW_OP_lit31 = 0x4f,
  DW_OP_reg0 = 0x50,
  DW_OP_reg1 = 0x51,
  DW_OP_reg2 = 0x52,
  DW_OP_reg3 = 0x53,
  DW_OP_reg4 = 0x54,
  DW_OP_reg5 = 0x55,
  DW_OP_reg6 = 0x56,
  DW_OP_reg7 = 0x57,
  DW_OP_reg8 = 0x58,
  DW_OP_reg9 = 0x59,
  DW_OP_reg10 = 0x5a,
  DW_OP_reg11 = 0x5b,
  DW_OP_reg12 = 0x5c,
  DW_OP_reg13 = 0x5d,
  DW_OP_reg14 = 0x5e,
  DW_OP_reg15 = 0x5f,
  DW_OP_reg16 = 0x60,
  DW_OP_reg17 = 0x61,
  DW_OP_reg18 = 0x62,
  DW_OP_reg19 = 0x63,
  DW_OP_reg20 = 0x64,
  DW_OP_reg21 = 0x65,
  DW_OP_reg22 = 0x66,
  DW_OP_reg23 = 0x67,
  DW_OP_reg24 = 0x68,
  DW_OP_reg25 = 0x69,
  DW_OP_reg26 = 0x6a,
  DW_OP_reg27 = 0x6b,
  DW_OP_reg28 = 0x6c,
  DW_OP_reg29 = 0x6d,
  DW_OP_reg30 = 0x6e,
  DW_OP_reg31 = 0x6f,
  DW_OP_breg0 = 0x70,
  DW_OP_breg1 = 0x71,
  DW_OP_breg2 = 0x72,
  DW_OP_breg3 = 0x73,
  DW_OP_breg4 = 0x74,
  DW_OP_breg5 = 0x75,
  DW_OP_breg6 = 0x76,
  DW_OP_breg7 = 0x77,
  DW_OP_breg8 = 0x78,
  DW_OP_breg9 = 0x79,
  DW_OP_breg10 = 0x7a,
  DW_OP_breg11 = 0x7b,
  DW_OP_breg12 = 0x7c,
  DW_OP_breg13 = 0x7d,
  DW_OP_breg14 = 0x7e,
  DW_OP_breg15 = 0x7f,
  DW_OP_breg16 = 0x80,
  DW_OP_breg17 = 0x81,
  DW_OP_breg18 = 0x82,
  DW_OP_breg19 = 0x83,
  DW_OP_breg20 = 0x84,
  DW_OP_breg21 = 0x85,
  DW_OP_breg22 = 0x86,
  DW_OP_breg23 = 0x87,
  DW_OP_breg24 = 0x88,
  DW_OP_breg25 = 0x89,
  DW_OP_breg26 = 0x8a,
  DW_OP_breg27 = 0x8b,
  DW_OP_breg28 = 0x8c,
  DW_OP_breg29 = 0x8d,
  DW_OP_breg30 = 0x8e,
  DW_OP_breg31 = 0x8f,
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
  DW_OP_implicit_pointer = 0xa0,
  DW_OP_addrx = 0xa1,
  DW_OP_constx = 0xa2,
  DW_OP_entry_value = 0xa3,
  DW_OP_const_type = 0xa4,
  DW_OP_regval_type = 0xa5,
  DW_OP_deref_type = 0xa6,
  DW_OP_xderef_type = 0xa7,
  DW_OP_convert = 0xa8,
  DW_OP_reinterpret = 0xa9,
  DW_OP_lo_user = 0xe0,
  DW_OP_hi_user = 0xff,
  DW_OP_GNU_push_tls_address = 0x4e,
  DW_OP_GNU_uninit = 0xf0,
  DW_OP_GNU_encoded_addr = 0xf1,
  DW_OP_GNU_implicit_pointer = 0xf2,
  DW_OP_GNU_entry_value = 0xf3,
  DW_OP_GNU_const_type = 0xf4,
  DW_OP_GNU_regval_type = 0xf5,
  DW_OP_GNU_deref_type = 0xf6,
  DW_OP_GNU_convert = 0xf7,
  DW_OP_GNU_reinterpret = 0xf9,
  DW_OP_GNU_parameter_ref = 0xfa,
  DW_OP_GNU_variable_value = 0xfb
};

enum dwarf_line_number_ops {
  DW_LNS_extended_op = 0,
  DW_LNS_copy = 1,
  DW_LNS_advance_pc = 2,
  DW_LNS_advance_line = 3,
  DW_LNS_set_file = 4,
  DW_LNS_set_column = 5,
  DW_LNS_negate_stmt = 6,
  DW_LNS_set_basic_block = 7,
  DW_LNS_const_add_pc = 8,
  DW_LNS_fixed_advance_pc = 9
};

enum dwarf_line_number_x_ops {
  DW_LNE_end_sequence = 1,
  DW_LNE_set_address = 2,
  DW_LNE_define_file = 3,
  DW_LNE_set_discriminator = 4,
  DW_LNE_HP_source_file_correlation = 0x80
};

enum dwarf_unit_type {
  DW_UT_compile = 0x01,
  DW_UT_type = 0x02,
  DW_UT_partial = 0x03,
  DW_UT_skeleton = 0x04,
  DW_UT_split_compile = 0x05,
  DW_UT_split_type = 0x06
};

enum dwarf_source_language {
  DW_LANG_C89 = 0x0001,
  DW_LANG_C = 0x0002,
  DW_LANG_Ada83 = 0x0003,
  DW_LANG_C_plus_plus = 0x0004,
  DW_LANG_Cobol74 = 0x0005,
  DW_LANG_Cobol85 = 0x0006,
  DW_LANG_Fortran77 = 0x0007,
  DW_LANG_Fortran90 = 0x0008,
  DW_LANG_Pascal83 = 0x0009,
  DW_LANG_Modula2 = 0x000a,
  DW_LANG_Java = 0x000b,
  DW_LANG_C99 = 0x000c,
  DW_LANG_Ada95 = 0x000d,
  DW_LANG_Fortran95 = 0x000e,
  DW_LANG_PLI = 0x000f,
  DW_LANG_ObjC = 0x0010,
  DW_LANG_ObjC_plus_plus = 0x0011,
  DW_LANG_UPC = 0x0012,
  DW_LANG_D = 0x0013,
  DW_LANG_Python = 0x0014,
  DW_LANG_OpenCL = 0x0015,
  DW_LANG_Go = 0x0016,
  DW_LANG_Modula3 = 0x0017,
  DW_LANG_Haskell = 0x0018,
  DW_LANG_C_plus_plus_03 = 0x0019,
  DW_LANG_C_plus_plus_11 = 0x001a,
  DW_LANG_OCaml = 0x001b,
  DW_LANG_Rust = 0x001c,
  DW_LANG_C11 = 0x001d,
  DW_LANG_Swift = 0x001e,
  DW_LANG_Julia = 0x001f,
  DW_LANG_Dylan = 0x0020,
  DW_LANG_C_plus_plus_14 = 0x0021,
  DW_LANG_Fortran03 = 0x0022,
  DW_LANG_Fortran08 = 0x0023,
  DW_LANG_RenderScript = 0x0024
};

#define BFD_ASSERT(x) do { if (!(x)) abort(); } while (0)

#define BSF_FUNCTION 0x10
#define BSF_GLOBAL 0x08
#define BSF_SECTION_SYM 0x40

#define SEC_CODE 0x10

#define EXEC_P 0x02
#define DYNAMIC 0x40

enum dwarf_debug_section_enum {
  debug_abbrev = 0,
  debug_aranges,
  debug_frame,
  debug_info,
  debug_info_alt,
  debug_line,
  debug_loc,
  debug_macinfo,
  debug_macro,
  debug_pubnames,
  debug_pubtypes,
  debug_ranges,
  debug_static_func,
  debug_static_vars,
  debug_str,
  debug_str_alt,
  debug_line_str,
  debug_types,
  debug_sfnames,
  debug_srcinfo,
  debug_funcnames,
  debug_typenames,
  debug_varnames,
  debug_weaknames,
  debug_max
};

struct dwarf_debug_section {
  const char *uncompressed_name;
  const char *compressed_name;
};

struct dwarf_block {
  unsigned int size;
  bfd_byte *data;
};

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

struct attr_abbrev {
  enum dwarf_attribute name;
  enum dwarf_form form;
  bfd_vma implicit_const;
};

struct arange {
  struct arange *next;
  bfd_vma low;
  bfd_vma high;
};

struct line_head {
  bfd_vma total_length;
  unsigned short version;
  bfd_vma prologue_length;
  unsigned char minimum_instruction_length;
  unsigned char maximum_ops_per_insn;
  unsigned char default_is_stmt;
  int line_base;
  unsigned char line_range;
  unsigned char opcode_base;
  unsigned char *standard_opcode_lengths;
};

struct abbrev_info {
  unsigned int number;
  enum dwarf_tag tag;
  int has_children;
  unsigned int num_attrs;
  struct attr_abbrev *attrs;
  struct abbrev_info *next;
};

struct fileinfo {
  char *name;
  unsigned int dir;
  unsigned int time;
  unsigned int size;
};

struct line_info {
  struct line_info *prev_line;
  bfd_vma address;
  char *filename;
  unsigned int line;
  unsigned int column;
  unsigned int discriminator;
  unsigned char op_index;
  unsigned char end_sequence;
};

struct line_sequence {
  bfd_vma low_pc;
  struct line_sequence *prev_sequence;
  struct line_info *last_line;
  struct line_info **line_info_lookup;
  bfd_size_type num_lines;
};

struct line_info_table {
  bfd *abfd;
  unsigned int num_files;
  unsigned int num_dirs;
  unsigned int num_sequences;
  char *comp_dir;
  char **dirs;
  struct fileinfo *files;
  struct line_sequence *sequences;
  struct line_info *lcl_head;
};

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

struct lookup_funcinfo {
  struct funcinfo *funcinfo;
  bfd_vma low_addr;
  bfd_vma high_addr;
};

struct varinfo {
  struct varinfo *prev_var;
  char *file;
  int line;
  int tag;
  char *name;
  bfd_vma addr;
  asection *sec;
  unsigned int stack: 1;
};

struct adjusted_section {
  asection *section;
  bfd_vma adj_vma;
};

struct info_hash_table;

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

#define STASH_INFO_HASH_OFF 0
#define STASH_INFO_HASH_ON 1

struct dwarf2_debug {
  struct comp_unit *all_comp_units;
  struct comp_unit *last_comp_unit;
  const struct dwarf_debug_section *debug_sections;
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
  struct adjusted_section *adjusted_sections;
  int info_hash_count;
  struct info_hash_table *funcinfo_hash_table;
  struct info_hash_table *varinfo_hash_table;
  struct comp_unit *hash_units_head;
  int info_hash_status;
  bfd_boolean close_on_cleanup;
};

/* External function declarations */
extern bfd_boolean read_section (bfd *abfd, const struct dwarf_debug_section *debug_section, asymbol **syms, unsigned long offset, bfd_byte **buffer, bfd_size_type *size);
extern bfd_boolean read_rangelist (struct comp_unit *unit, struct arange *arange, bfd_uint64_t offset);
extern bfd_boolean read_formatted_entries (struct comp_unit *unit, bfd_byte **bufp, bfd_byte *buf_end, struct line_info_table *table, bfd_boolean (*callback) (struct line_info_table *table, char *cur_file, unsigned int dir, unsigned int time, unsigned int size));
extern bfd_boolean line_info_add_include_dir (struct line_info_table *table, char *cur_dir);
extern bfd_boolean line_info_add_file_name (struct line_info_table *table, char *cur_file, unsigned int dir, unsigned int xtime, unsigned int size);
extern bfd_boolean line_info_add_include_dir_stub (struct line_info_table *table, char *cur_dir, unsigned int dir, unsigned int xtime, unsigned int size);
extern bfd_boolean add_line_info (struct line_info_table *table, bfd_vma address, unsigned char op_index, char *filename, unsigned int line, unsigned int column, unsigned int discriminator, int end_sequence);
extern bfd_boolean sort_line_sequences (struct line_info_table *table);
extern bfd_boolean arange_add (const struct comp_unit *unit, struct arange *first_arange, bfd_vma low_pc, bfd_vma high_pc);
extern bfd_boolean lookup_address_in_function_table (struct comp_unit *unit, bfd_vma addr, struct funcinfo **function_ptr);
extern bfd_vma lookup_address_in_line_info_table (struct line_info_table *table, bfd_vma addr, const char **filename_ptr, unsigned int *linenumber_ptr, unsigned int *discriminator_ptr);
extern bfd_boolean lookup_symbol_in_function_table (struct comp_unit *unit, asymbol *sym, bfd_vma addr, const char **filename_ptr, unsigned int *linenumber_ptr);
extern bfd_boolean lookup_symbol_in_variable_table (struct comp_unit *unit, asymbol *sym, bfd_vma addr, const char **filename_ptr, unsigned int *linenumber_ptr);
extern bfd_boolean comp_unit_contains_address (struct comp_unit *unit, bfd_vma addr);
extern asection *find_debug_info (bfd *abfd, const struct dwarf_debug_section *debug_sections, asection *after_sec);
extern bfd_boolean stash_find_line_fast (struct dwarf2_debug *stash, asymbol *sym, bfd_vma addr, const char **filename_ptr, unsigned int *linenumber_ptr);
extern void stash_maybe_enable_info_hash_tables (bfd *abfd, struct dwarf2_debug *stash);
extern bfd_boolean stash_maybe_update_info_hash_tables (struct dwarf2_debug *stash);
extern bfd_boolean _bfd_dwarf2_slurp_debug_info (bfd *abfd, bfd *debug_bfd, const struct dwarf_debug_section *debug_sections, asymbol **symbols, void **pinfo, bfd_boolean keep_sections);
extern asymbol *_bfd_elf_find_function (bfd *abfd, asymbol **symbols, asection *section, bfd_vma offset, const char **filename_ptr, const char **functionname_ptr);
extern void unset_sections (struct dwarf2_debug *stash);
extern bfd_byte *read_attribute (struct attribute *attr, struct attr_abbrev *abbrev, struct comp_unit *unit, bfd_byte *info_ptr, bfd_byte *info_ptr_end);
extern bfd_byte *read_alt_indirect_ref (struct comp_unit *unit, bfd_uint64_t offset);
extern bfd_uint64_t read_address (struct comp_unit *unit, bfd_byte *buf, bfd_byte *buf_end);
extern struct abbrev_info *lookup_abbrev (unsigned int number, struct abbrev_info **abbrevs);
extern struct abbrev_info **read_abbrevs (bfd *abfd, bfd_uint64_t offset, struct dwarf2_debug *stash);
extern char *read_string (bfd *abfd, bfd_byte *buf, bfd_byte *buf_end, unsigned int *bytes_read_ptr);
extern unsigned int read_1_byte (bfd *abfd, bfd_byte *buf, bfd_byte *end);
extern int read_1_signed_byte (bfd *abfd, bfd_byte *buf, bfd_byte *end);
extern unsigned int read_2_bytes (bfd *abfd, bfd_byte *buf, bfd_byte *end);
extern unsigned int read_4_bytes (bfd *abfd, bfd_byte *buf, bfd_byte *end);
extern bfd_uint64_t read_8_bytes (bfd *abfd, bfd_byte *buf, bfd_byte *end);
extern bfd_boolean is_str_attr (enum dwarf_form form);
extern bfd_boolean non_mangled (int lang);
extern bfd_byte *bfd_get_section_contents (bfd *abfd, asection *section, bfd_byte *location, bfd_vma offset, bfd_size_type count);

/* Forward declarations for static functions defined later */
static char *concat_filename (struct line_info_table *table, unsigned int file);
static bfd_boolean scan_unit_for_symbols (struct comp_unit *unit);




static struct line_info_table*
decode_line_info (struct comp_unit *unit, struct dwarf2_debug *stash)
{
  bfd *abfd = unit->abfd;
  struct line_info_table* table;
  bfd_byte *line_ptr;
  bfd_byte *line_end;
  struct line_head lh;
  unsigned int i, bytes_read, offset_size;
  char *cur_file, *cur_dir;
  unsigned char op_code, extended_op, adj_opcode;
  unsigned int exop_len;
  bfd_size_type amt;

  if (! read_section (abfd, &stash->debug_sections[debug_line],
		      stash->syms, unit->line_offset,
		      &stash->dwarf_line_buffer, &stash->dwarf_line_size))
    return NULL;

  amt = sizeof (struct line_info_table);
  table = (struct line_info_table *) bfd_alloc (abfd, amt);
  if (table == NULL)
    return NULL;
  table->abfd = abfd;
  table->comp_dir = unit->comp_dir;

  table->num_files = 0;
  table->files = NULL;

  table->num_dirs = 0;
  table->dirs = NULL;

  table->num_sequences = 0;
  table->sequences = NULL;

  table->lcl_head = NULL;

  if (stash->dwarf_line_size < 16)
    {
      _bfd_error_handler
	(_("DWARF error: line info section is too small (%" PRId64 ")"),
	 (int64_t) stash->dwarf_line_size);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }
  line_ptr = stash->dwarf_line_buffer + unit->line_offset;
  line_end = stash->dwarf_line_buffer + stash->dwarf_line_size;

  /* Read in the prologue.  */
  lh.total_length = read_4_bytes (abfd, line_ptr, line_end);
  line_ptr += 4;
  offset_size = 4;
  if (lh.total_length == 0xffffffff)
    {
      lh.total_length = read_8_bytes (abfd, line_ptr, line_end);
      line_ptr += 8;
      offset_size = 8;
    }
  else if (lh.total_length == 0 && unit->addr_size == 8)
    {
      /* Handle (non-standard) 64-bit DWARF2 formats.  */
      lh.total_length = read_4_bytes (abfd, line_ptr, line_end);
      line_ptr += 4;
      offset_size = 8;
    }

  if (lh.total_length > (size_t) (line_end - line_ptr))
    {
      _bfd_error_handler
	/* xgettext: c-format */
	(_("DWARF error: line info data is bigger (%#" PRIx64 ")"
	   " than the space remaining in the section (%#lx)"),
	 (uint64_t) lh.total_length, (unsigned long) (line_end - line_ptr));
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  line_end = line_ptr + lh.total_length;

  lh.version = read_2_bytes (abfd, line_ptr, line_end);
  if (lh.version < 2 || lh.version > 5)
    {
      _bfd_error_handler
	(_("DWARF error: unhandled .debug_line version %d"), lh.version);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }
  line_ptr += 2;

  if (line_ptr + offset_size + (lh.version >= 5 ? 8 : (lh.version >= 4 ? 6 : 5))
      >= line_end)
    {
      _bfd_error_handler
	(_("DWARF error: ran out of room reading prologue"));
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  if (lh.version >= 5)
    {
      unsigned int segment_selector_size;

      /* Skip address size.  */
      read_1_byte (abfd, line_ptr, line_end);
      line_ptr += 1;

      segment_selector_size = read_1_byte (abfd, line_ptr, line_end);
      line_ptr += 1;
      if (segment_selector_size != 0)
	{
	  _bfd_error_handler
	    (_("DWARF error: line info unsupported segment selector size %u"),
	     segment_selector_size);
	  bfd_set_error (bfd_error_bad_value);
	  return NULL;
	}
    }

  if (offset_size == 4)
    lh.prologue_length = read_4_bytes (abfd, line_ptr, line_end);
  else
    lh.prologue_length = read_8_bytes (abfd, line_ptr, line_end);
  line_ptr += offset_size;

  lh.minimum_instruction_length = read_1_byte (abfd, line_ptr, line_end);
  line_ptr += 1;

  if (lh.version >= 4)
    {
      lh.maximum_ops_per_insn = read_1_byte (abfd, line_ptr, line_end);
      line_ptr += 1;
    }
  else
    lh.maximum_ops_per_insn = 1;

  if (lh.maximum_ops_per_insn == 0)
    {
      _bfd_error_handler
	(_("DWARF error: invalid maximum operations per instruction"));
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  lh.default_is_stmt = read_1_byte (abfd, line_ptr, line_end);
  line_ptr += 1;

  lh.line_base = read_1_signed_byte (abfd, line_ptr, line_end);
  line_ptr += 1;

  lh.line_range = read_1_byte (abfd, line_ptr, line_end);
  line_ptr += 1;

  lh.opcode_base = read_1_byte (abfd, line_ptr, line_end);
  line_ptr += 1;

  if (line_ptr + (lh.opcode_base - 1) >= line_end)
    {
      _bfd_error_handler (_("DWARF error: ran out of room reading opcodes"));
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  amt = lh.opcode_base * sizeof (unsigned char);
  lh.standard_opcode_lengths = (unsigned char *) bfd_alloc (abfd, amt);

  lh.standard_opcode_lengths[0] = 1;

  for (i = 1; i < lh.opcode_base; ++i)
    {
      lh.standard_opcode_lengths[i] = read_1_byte (abfd, line_ptr, line_end);
      line_ptr += 1;
    }

  if (lh.version >= 5)
    {
      /* Read directory table.  */
      if (!read_formatted_entries (unit, &line_ptr, line_end, table,
				   line_info_add_include_dir_stub))
	goto fail;

      /* Read file name table.  */
      if (!read_formatted_entries (unit, &line_ptr, line_end, table,
				   line_info_add_file_name))
	goto fail;
    }
  else
    {
      /* Read directory table.  */
      while ((cur_dir = read_string (abfd, line_ptr, line_end, &bytes_read)) != NULL)
	{
	  line_ptr += bytes_read;

	  if (!line_info_add_include_dir (table, cur_dir))
	    goto fail;
	}

      line_ptr += bytes_read;

      /* Read file name table.  */
      while ((cur_file = read_string (abfd, line_ptr, line_end, &bytes_read)) != NULL)
	{
	  unsigned int dir, xtime, size;

	  line_ptr += bytes_read;

	  dir = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read, FALSE, line_end);
	  line_ptr += bytes_read;
	  xtime = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read, FALSE, line_end);
	  line_ptr += bytes_read;
	  size = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read, FALSE, line_end);
	  line_ptr += bytes_read;

	  if (!line_info_add_file_name (table, cur_file, dir, xtime, size))
	    goto fail;
	}

      line_ptr += bytes_read;
    }

  /* Read the statement sequences until there's nothing left.  */
  while (line_ptr < line_end)
    {
      /* State machine registers.  */
      bfd_vma address = 0;
      unsigned char op_index = 0;
      char * filename = table->num_files ? concat_filename (table, 1) : NULL;
      unsigned int line = 1;
      unsigned int column = 0;
      unsigned int discriminator = 0;
      int is_stmt = lh.default_is_stmt;
      int end_sequence = 0;
      unsigned int dir, xtime, size;
      /* eraxxon@alumni.rice.edu: Against the DWARF2 specs, some
	 compilers generate address sequences that are wildly out of
	 order using DW_LNE_set_address (e.g. Intel C++ 6.0 compiler
	 for ia64-Linux).  Thus, to determine the low and high
	 address, we must compare on every DW_LNS_copy, etc.  */
      bfd_vma low_pc  = (bfd_vma) -1;
      bfd_vma high_pc = 0;

      /* Decode the table.  */
      while (!end_sequence && line_ptr < line_end)
	{
	  op_code = read_1_byte (abfd, line_ptr, line_end);
	  line_ptr += 1;

	  if (op_code >= lh.opcode_base)
	    {
	      /* Special operand.  */
	      adj_opcode = op_code - lh.opcode_base;
	      if (lh.line_range == 0)
		goto line_fail;
	      if (lh.maximum_ops_per_insn == 1)
		address += (adj_opcode / lh.line_range
			    * lh.minimum_instruction_length);
	      else
		{
		  address += ((op_index + adj_opcode / lh.line_range)
			      / lh.maximum_ops_per_insn
			      * lh.minimum_instruction_length);
		  op_index = ((op_index + adj_opcode / lh.line_range)
			      % lh.maximum_ops_per_insn);
		}
	      line += lh.line_base + (adj_opcode % lh.line_range);
	      /* Append row to matrix using current values.  */
	      if (!add_line_info (table, address, op_index, filename,
				  line, column, discriminator, 0))
		goto line_fail;
	      discriminator = 0;
	      if (address < low_pc)
		low_pc = address;
	      if (address > high_pc)
		high_pc = address;
	    }
	  else switch (op_code)
	    {
	    case DW_LNS_extended_op:
	      exop_len = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
						FALSE, line_end);
	      line_ptr += bytes_read;
	      extended_op = read_1_byte (abfd, line_ptr, line_end);
	      line_ptr += 1;

	      switch (extended_op)
		{
		case DW_LNE_end_sequence:
		  end_sequence = 1;
		  if (!add_line_info (table, address, op_index, filename, line,
				      column, discriminator, end_sequence))
		    goto line_fail;
		  discriminator = 0;
		  if (address < low_pc)
		    low_pc = address;
		  if (address > high_pc)
		    high_pc = address;
		  if (!arange_add (unit, &unit->arange, low_pc, high_pc))
		    goto line_fail;
		  break;
		case DW_LNE_set_address:
		  address = read_address (unit, line_ptr, line_end);
		  op_index = 0;
		  line_ptr += unit->addr_size;
		  break;
		case DW_LNE_define_file:
		  cur_file = read_string (abfd, line_ptr, line_end, &bytes_read);
		  line_ptr += bytes_read;
		  dir = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
					       FALSE, line_end);
		  line_ptr += bytes_read;
		  xtime = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
						 FALSE, line_end);
		  line_ptr += bytes_read;
		  size = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
						FALSE, line_end);
		  line_ptr += bytes_read;
		  if (!line_info_add_file_name (table, cur_file, dir,
						xtime, size))
		    goto line_fail;
		  break;
		case DW_LNE_set_discriminator:
		  discriminator =
		    _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
					   FALSE, line_end);
		  line_ptr += bytes_read;
		  break;
		case DW_LNE_HP_source_file_correlation:
		  line_ptr += exop_len - 1;
		  break;
		default:
		  _bfd_error_handler
		    (_("DWARF error: mangled line number section"));
		  bfd_set_error (bfd_error_bad_value);
		line_fail:
		  if (filename != NULL)
		    free (filename);
		  goto fail;
		}
	      break;
	    case DW_LNS_copy:
	      if (!add_line_info (table, address, op_index,
				  filename, line, column, discriminator, 0))
		goto line_fail;
	      discriminator = 0;
	      if (address < low_pc)
		low_pc = address;
	      if (address > high_pc)
		high_pc = address;
	      break;
	    case DW_LNS_advance_pc:
	      if (lh.maximum_ops_per_insn == 1)
		address += (lh.minimum_instruction_length
			    * _bfd_safe_read_leb128 (abfd, line_ptr,
						     &bytes_read,
						     FALSE, line_end));
	      else
		{
		  bfd_vma adjust = _bfd_safe_read_leb128 (abfd, line_ptr,
							  &bytes_read,
							  FALSE, line_end);
		  address = ((op_index + adjust) / lh.maximum_ops_per_insn
			     * lh.minimum_instruction_length);
		  op_index = (op_index + adjust) % lh.maximum_ops_per_insn;
		}
	      line_ptr += bytes_read;
	      break;
	    case DW_LNS_advance_line:
	      line += _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
					     TRUE, line_end);
	      line_ptr += bytes_read;
	      break;
	    case DW_LNS_set_file:
	      {
		unsigned int file;

		/* The file and directory tables are 0
		   based, the references are 1 based.  */
		file = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
					      FALSE, line_end);
		line_ptr += bytes_read;
		if (filename)
		  free (filename);
		filename = concat_filename (table, file);
		break;
	      }
	    case DW_LNS_set_column:
	      column = _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
					      FALSE, line_end);
	      line_ptr += bytes_read;
	      break;
	    case DW_LNS_negate_stmt:
	      is_stmt = (!is_stmt);
	      break;
	    case DW_LNS_set_basic_block:
	      break;
	    case DW_LNS_const_add_pc:
	      if (lh.line_range == 0)
		goto line_fail;
	      if (lh.maximum_ops_per_insn == 1)
		address += (lh.minimum_instruction_length
			    * ((255 - lh.opcode_base) / lh.line_range));
	      else
		{
		  bfd_vma adjust = ((255 - lh.opcode_base) / lh.line_range);
		  address += (lh.minimum_instruction_length
			      * ((op_index + adjust)
				 / lh.maximum_ops_per_insn));
		  op_index = (op_index + adjust) % lh.maximum_ops_per_insn;
		}
	      break;
	    case DW_LNS_fixed_advance_pc:
	      address += read_2_bytes (abfd, line_ptr, line_end);
	      op_index = 0;
	      line_ptr += 2;
	      break;
	    default:
	      /* Unknown standard opcode, ignore it.  */
	      for (i = 0; i < lh.standard_opcode_lengths[op_code]; i++)
		{
		  (void) _bfd_safe_read_leb128 (abfd, line_ptr, &bytes_read,
						FALSE, line_end);
		  line_ptr += bytes_read;
		}
	      break;
	    }
	}

      if (filename)
	free (filename);
    }

  if (sort_line_sequences (table))
    return table;

 fail:
  while (table->sequences != NULL)
    {
      struct line_sequence* seq = table->sequences;
      table->sequences = table->sequences->prev_sequence;
      free (seq);
    }
  if (table->files != NULL)
    free (table->files);
  if (table->dirs != NULL)
    free (table->dirs);
  return NULL;
}

static bfd_vma
comp_unit_find_nearest_line (struct comp_unit *unit,
			     bfd_vma addr,
			     const char **filename_ptr,
			     struct funcinfo **function_ptr,
			     unsigned int *linenumber_ptr,
			     unsigned int *discriminator_ptr,
			     struct dwarf2_debug *stash)
{
  bfd_boolean func_p;

  if (unit->error)
    return FALSE;

  if (! unit->line_table)
    {
      if (! unit->stmtlist)
	{
	  unit->error = 1;
	  return FALSE;
	}

      unit->line_table = decode_line_info (unit, stash);

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

  *function_ptr = NULL;
  func_p = lookup_address_in_function_table (unit, addr, function_ptr);
  if (func_p && (*function_ptr)->tag == DW_TAG_inlined_subroutine)
    stash->inliner_chain = *function_ptr;

  return lookup_address_in_line_info_table (unit->line_table, addr,
					    filename_ptr,
					    linenumber_ptr,
					    discriminator_ptr);
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
find_abstract_instance (struct comp_unit *   unit,
			bfd_byte *           orig_info_ptr,
			struct attribute *   attr_ptr,
			const char **        pname,
			bfd_boolean *        is_linkage,
			char **              filename_ptr,
			int *                linenumber_ptr)
{
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr;
  bfd_byte *info_ptr_end;
  unsigned int abbrev_number, bytes_read, i;
  struct abbrev_info *abbrev;
  bfd_uint64_t die_ref = attr_ptr->u.val;
  struct attribute attr;
  const char *name = NULL;

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
	 them contiguously into stash->info_ptr_memory, that means
	 the reference is relative to stash->info_ptr_memory.  */
      size_t total;

      info_ptr = unit->stash->info_ptr_memory;
      info_ptr_end = unit->stash->info_ptr_end;
      total = info_ptr_end - info_ptr;
      if (!die_ref || die_ref >= total)
	{
	  _bfd_error_handler
	    (_("DWARF error: invalid abstract instance DIE ref"));
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      info_ptr += die_ref;

      /* Now find the CU containing this pointer.  */
      if (info_ptr >= unit->info_ptr_unit && info_ptr < unit->end_ptr)
	info_ptr_end = unit->end_ptr;
      else
	{
	  /* Check other CUs to see if they contain the abbrev.  */
	  struct comp_unit * u;

	  for (u = unit->prev_unit; u != NULL; u = u->prev_unit)
	    if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
	      break;

	  if (u == NULL)
	    for (u = unit->next_unit; u != NULL; u = u->next_unit)
	      if (info_ptr >= u->info_ptr_unit && info_ptr < u->end_ptr)
		break;

	  if (u)
	    {
	      unit = u;
	      info_ptr_end = unit->end_ptr;
	    }
	  /* else FIXME: What do we do now ?  */
	}
    }
  else if (attr_ptr->form == DW_FORM_GNU_ref_alt)
    {
      info_ptr = read_alt_indirect_ref (unit, die_ref);
      if (info_ptr == NULL)
	{
	  _bfd_error_handler
	    (_("DWARF error: unable to read alt ref %" PRIu64),
	     (uint64_t) die_ref);
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      info_ptr_end = (unit->stash->alt_dwarf_info_buffer
		      + unit->stash->alt_dwarf_info_size);

      /* FIXME: Do we need to locate the correct CU, in a similar
	 fashion to the code in the DW_FORM_ref_addr case above ?  */
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
	      /* It doesn't ever make sense for DW_AT_specification to
		 refer to the same DIE.  Stop simple recursion.  */
	      if (info_ptr == orig_info_ptr)
		{
		  _bfd_error_handler
		    (_("DWARF error: abstract instance recursion detected"));
		  bfd_set_error (bfd_error_bad_value);
		  return FALSE;
		}
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
		  if (!find_abstract_instance (unit, info_ptr, &attr,
					       pname, is_linkage,
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

static bfd_boolean
scan_unit_for_symbols (struct comp_unit *unit)
{
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

      /* PR 17512: file: 9f405d9d.  */
      if (info_ptr >= info_ptr_end)
	goto fail;

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

      var = NULL;
      if (abbrev->tag == DW_TAG_subprogram
	  || abbrev->tag == DW_TAG_entry_point
	  || abbrev->tag == DW_TAG_inlined_subroutine)
	{
	  bfd_size_type amt = sizeof (struct funcinfo);
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
	      bfd_size_type amt = sizeof (struct varinfo);
	      var = (struct varinfo *) bfd_zalloc (abfd, amt);
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
		  if (!find_abstract_instance (unit, info_ptr, &attr,
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
		    var->stack = 0;
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
			  var->stack = 0;

			  /* Verify that DW_OP_addr is the only opcode in the
			     location, in which case the block size will be 1
			     plus the address size.  */
			  /* ??? For TLS variables, gcc can emit
			     DW_OP_addr <addr> DW_OP_GNU_push_tls_address
			     which we don't handle here yet.  */
			  if (attr.u.blk->size == unit->addr_size + 1U)
			    var->addr = bfd_get (unit->abfd, unit->addr_size * 8,
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

static bfd_boolean
comp_unit_maybe_decode_line_info (struct comp_unit *unit,
				  struct dwarf2_debug *stash)
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

      unit->line_table = decode_line_info (unit, stash);

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
comp_unit_find_line (struct comp_unit *unit,
		     asymbol *sym,
		     bfd_vma addr,
		     const char **filename_ptr,
		     unsigned int *linenumber_ptr,
		     struct dwarf2_debug *stash)
{
  if (!comp_unit_maybe_decode_line_info (unit, stash))
    return FALSE;

  if (sym->flags & BSF_FUNCTION)
    return lookup_symbol_in_function_table (unit, sym, addr,
					    filename_ptr,
					    linenumber_ptr);

  return lookup_symbol_in_variable_table (unit, sym, addr,
					  filename_ptr,
					  linenumber_ptr);
}


static struct comp_unit *
parse_comp_unit (struct dwarf2_debug *stash,
		 bfd_vma unit_length,
		 bfd_byte *info_ptr_unit,
		 unsigned int offset_size)
{
  struct comp_unit* unit;
  unsigned int version;
  bfd_uint64_t abbrev_offset = 0;
  /* Initialize it just to avoid a GCC false warning.  */
  unsigned int addr_size = -1;
  struct abbrev_info** abbrevs;
  unsigned int abbrev_number, bytes_read, i;
  struct abbrev_info *abbrev;
  struct attribute attr;
  bfd_byte *info_ptr = stash->info_ptr;
  bfd_byte *end_ptr = info_ptr + unit_length;
  bfd_size_type amt;
  bfd_vma low_pc = 0;
  bfd_vma high_pc = 0;
  bfd *abfd = stash->bfd_ptr;
  bfd_boolean high_pc_relative = FALSE;
  enum dwarf_unit_type unit_type;

  version = read_2_bytes (abfd, info_ptr, end_ptr);
  info_ptr += 2;
  if (version < 2 || version > 5)
    {
      /* PR 19872: A version number of 0 probably means that there is padding
	 at the end of the .debug_info section.  Gold puts it there when
	 performing an incremental link, for example.  So do not generate
	 an error, just return a NULL.  */
      if (version)
	{
	  _bfd_error_handler
	    (_("DWARF error: found dwarf version '%u', this reader"
	       " only handles version 2, 3, 4 and 5 information"), version);
	  bfd_set_error (bfd_error_bad_value);
	}
      return NULL;
    }

  if (version < 5)
    unit_type = DW_UT_compile;
  else
    {
      unit_type = read_1_byte (abfd, info_ptr, end_ptr);
      info_ptr += 1;

      addr_size = read_1_byte (abfd, info_ptr, end_ptr);
      info_ptr += 1;
    }

  BFD_ASSERT (offset_size == 4 || offset_size == 8);
  if (offset_size == 4)
    abbrev_offset = read_4_bytes (abfd, info_ptr, end_ptr);
  else
    abbrev_offset = read_8_bytes (abfd, info_ptr, end_ptr);
  info_ptr += offset_size;

  if (version < 5)
    {
      addr_size = read_1_byte (abfd, info_ptr, end_ptr);
      info_ptr += 1;
    }

  if (unit_type == DW_UT_type)
    {
      /* Skip type signature.  */
      info_ptr += 8;

      /* Skip type offset.  */
      info_ptr += offset_size;
    }

  if (addr_size > sizeof (bfd_vma))
    {
      _bfd_error_handler
	/* xgettext: c-format */
	(_("DWARF error: found address size '%u', this reader"
	   " can not handle sizes greater than '%u'"),
	 addr_size,
	 (unsigned int) sizeof (bfd_vma));
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  if (addr_size != 2 && addr_size != 4 && addr_size != 8)
    {
      _bfd_error_handler
	("DWARF error: found address size '%u', this reader"
	 " can only handle address sizes '2', '4' and '8'", addr_size);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  /* Read the abbrevs for this compilation unit into a table.  */
  abbrevs = read_abbrevs (abfd, abbrev_offset, stash);
  if (! abbrevs)
    return NULL;

  abbrev_number = _bfd_safe_read_leb128 (abfd, info_ptr, &bytes_read,
					 FALSE, end_ptr);
  info_ptr += bytes_read;
  if (! abbrev_number)
    {
      /* PR 19872: An abbrev number of 0 probably means that there is padding
	 at the end of the .debug_abbrev section.  Gold puts it there when
	 performing an incremental link, for example.  So do not generate
	 an error, just return a NULL.  */
      return NULL;
    }

  abbrev = lookup_abbrev (abbrev_number, abbrevs);
  if (! abbrev)
    {
      _bfd_error_handler (_("DWARF error: could not find abbrev number %u"),
			  abbrev_number);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  amt = sizeof (struct comp_unit);
  unit = (struct comp_unit *) bfd_zalloc (abfd, amt);
  if (unit == NULL)
    return NULL;
  unit->abfd = abfd;
  unit->version = version;
  unit->addr_size = addr_size;
  unit->offset_size = offset_size;
  unit->abbrevs = abbrevs;
  unit->end_ptr = end_ptr;
  unit->stash = stash;
  unit->info_ptr_unit = info_ptr_unit;

  for (i = 0; i < abbrev->num_attrs; ++i)
    {
      info_ptr = read_attribute (&attr, &abbrev->attrs[i], unit, info_ptr, end_ptr);
      if (info_ptr == NULL)
	return NULL;

      /* Store the data if it is of an attribute we want to keep in a
	 partial symbol table.  */
      switch (attr.name)
	{
	case DW_AT_stmt_list:
	  unit->stmtlist = 1;
	  unit->line_offset = attr.u.val;
	  break;

	case DW_AT_name:
	  if (is_str_attr (attr.form))
	    unit->name = attr.u.str;
	  break;

	case DW_AT_low_pc:
	  low_pc = attr.u.val;
	  /* If the compilation unit DIE has a DW_AT_low_pc attribute,
	     this is the base address to use when reading location
	     lists or range lists.  */
	  if (abbrev->tag == DW_TAG_compile_unit)
	    unit->base_address = low_pc;
	  break;

	case DW_AT_high_pc:
	  high_pc = attr.u.val;
	  high_pc_relative = attr.form != DW_FORM_addr;
	  break;

	case DW_AT_ranges:
	  if (!read_rangelist (unit, &unit->arange, attr.u.val))
	    return NULL;
	  break;

	case DW_AT_comp_dir:
	  {
	    char *comp_dir = attr.u.str;

	    /* PR 17512: file: 1fe726be.  */
	    if (! is_str_attr (attr.form))
	      {
		_bfd_error_handler
		  (_("DWARF error: DW_AT_comp_dir attribute encountered with a non-string form"));
		comp_dir = NULL;
	      }

	    if (comp_dir)
	      {
		/* Irix 6.2 native cc prepends <machine>.: to the compilation
		   directory, get rid of it.  */
		char *cp = strchr (comp_dir, ':');

		if (cp && cp != comp_dir && cp[-1] == '.' && cp[1] == '/')
		  comp_dir = cp + 1;
	      }
	    unit->comp_dir = comp_dir;
	    break;
	  }

	case DW_AT_language:
	  unit->lang = attr.u.val;
	  break;

	default:
	  break;
	}
    }
  if (high_pc_relative)
    high_pc += low_pc;
  if (high_pc != 0)
    {
      if (!arange_add (unit, &unit->arange, low_pc, high_pc))
	return NULL;
    }

  unit->first_child_die_ptr = info_ptr;
  return unit;
}


bfd_boolean
_bfd_dwarf2_find_nearest_line (bfd *abfd,
			       asymbol **symbols,
			       asymbol *symbol,
			       asection *section,
			       bfd_vma offset,
			       const char **filename_ptr,
			       const char **functionname_ptr,
			       unsigned int *linenumber_ptr,
			       unsigned int *discriminator_ptr,
			       const struct dwarf_debug_section *debug_sections,
			       unsigned int addr_size,
			       void **pinfo)
{
  /* Read each compilation unit from the section .debug_info, and check
     to see if it contains the address we are searching for.  If yes,
     lookup the address, and return the line number info.  If no, go
     on to the next compilation unit.

     We keep a list of all the previously read compilation units, and
     a pointer to the next un-read compilation unit.  Check the
     previously read units before reading more.  */
  struct dwarf2_debug *stash;
  /* What address are we looking for?  */
  bfd_vma addr;
  struct comp_unit* each;
  struct funcinfo *function = NULL;
  bfd_boolean found = FALSE;
  bfd_boolean do_line;

  *filename_ptr = NULL;
  if (functionname_ptr != NULL)
    *functionname_ptr = NULL;
  *linenumber_ptr = 0;
  if (discriminator_ptr)
    *discriminator_ptr = 0;

  if (! _bfd_dwarf2_slurp_debug_info (abfd, NULL, debug_sections,
				      symbols, pinfo,
				      (abfd->flags & (EXEC_P | DYNAMIC)) == 0))
    return FALSE;

  stash = (struct dwarf2_debug *) *pinfo;

  do_line = symbol != NULL;
  if (do_line)
    {
      BFD_ASSERT (section == NULL && offset == 0 && functionname_ptr == NULL);
      section = bfd_get_section (symbol);
      addr = symbol->value;
    }
  else
    {
      BFD_ASSERT (section != NULL && functionname_ptr != NULL);
      addr = offset;

      /* If we have no SYMBOL but the section we're looking at is not a
	 code section, then take a look through the list of symbols to see
	 if we have a symbol at the address we're looking for.  If we do
	 then use this to look up line information.  This will allow us to
	 give file and line results for data symbols.  We exclude code
	 symbols here, if we look up a function symbol and then look up the
	 line information we'll actually return the line number for the
	 opening '{' rather than the function definition line.  This is
	 because looking up by symbol uses the line table, in which the
	 first line for a function is usually the opening '{', while
	 looking up the function by section + offset uses the
	 DW_AT_decl_line from the function DW_TAG_subprogram for the line,
	 which will be the line of the function name.  */
      if (symbols != NULL && (section->flags & SEC_CODE) == 0)
	{
	  asymbol **tmp;

	  for (tmp = symbols; (*tmp) != NULL; ++tmp)
	    if ((*tmp)->the_bfd == abfd
		&& (*tmp)->section == section
		&& (*tmp)->value == offset
		&& ((*tmp)->flags & BSF_SECTION_SYM) == 0)
	      {
		symbol = *tmp;
		do_line = TRUE;
		/* For local symbols, keep going in the hope we find a
		   global.  */
		if ((symbol->flags & BSF_GLOBAL) != 0)
		  break;
	      }
	}
    }

  if (section->output_section)
    addr += section->output_section->vma + section->output_offset;
  else
    addr += section->vma;

  /* A null info_ptr indicates that there is no dwarf2 info
     (or that an error occured while setting up the stash).  */
  if (! stash->info_ptr)
    return FALSE;

  stash->inliner_chain = NULL;

  /* Check the previously read comp. units first.  */
  if (do_line)
    {
      /* The info hash tables use quite a bit of memory.  We may not want to
	 always use them.  We use some heuristics to decide if and when to
	 turn it on.  */
      if (stash->info_hash_status == STASH_INFO_HASH_OFF)
	stash_maybe_enable_info_hash_tables (abfd, stash);

      /* Keep info hash table up to date if they are available.  Note that we
	 may disable the hash tables if there is any error duing update.  */
      if (stash->info_hash_status == STASH_INFO_HASH_ON)
	stash_maybe_update_info_hash_tables (stash);

      if (stash->info_hash_status == STASH_INFO_HASH_ON)
	{
	  found = stash_find_line_fast (stash, symbol, addr, filename_ptr,
					linenumber_ptr);
	  if (found)
	    goto done;
	}
      else
	{
	  /* Check the previously read comp. units first.  */
	  for (each = stash->all_comp_units; each; each = each->next_unit)
	    if ((symbol->flags & BSF_FUNCTION) == 0
		|| each->arange.high == 0
		|| comp_unit_contains_address (each, addr))
	      {
		found = comp_unit_find_line (each, symbol, addr, filename_ptr,
					     linenumber_ptr, stash);
		if (found)
		  goto done;
	      }
	}
    }
  else
    {
      bfd_vma min_range = (bfd_vma) -1;
      const char * local_filename = NULL;
      struct funcinfo *local_function = NULL;
      unsigned int local_linenumber = 0;
      unsigned int local_discriminator = 0;

      for (each = stash->all_comp_units; each; each = each->next_unit)
	{
	  bfd_vma range = (bfd_vma) -1;

	  found = ((each->arange.high == 0
		    || comp_unit_contains_address (each, addr))
		   && (range = comp_unit_find_nearest_line (each, addr,
							    & local_filename,
							    & local_function,
							    & local_linenumber,
							    & local_discriminator,
							    stash)) != 0);
	  if (found)
	    {
	      /* PRs 15935 15994: Bogus debug information may have provided us
		 with an erroneous match.  We attempt to counter this by
		 selecting the match that has the smallest address range
		 associated with it. (We are assuming that corrupt debug info
		 will tend to result in extra large address ranges rather than
		 extra small ranges).

		 This does mean that we scan through all of the CUs associated
		 with the bfd each time this function is called.  But this does
		 have the benefit of producing consistent results every time the
		 function is called.  */
	      if (range <= min_range)
		{
		  if (filename_ptr && local_filename)
		    * filename_ptr = local_filename;
		  if (local_function)
		    function = local_function;
		  if (discriminator_ptr && local_discriminator)
		    * discriminator_ptr = local_discriminator;
		  if (local_linenumber)
		    * linenumber_ptr = local_linenumber;
		  min_range = range;
		}
	    }
	}

      if (* linenumber_ptr)
	{
	  found = TRUE;
	  goto done;
	}
    }

  /* The DWARF2 spec says that the initial length field, and the
     offset of the abbreviation table, should both be 4-byte values.
     However, some compilers do things differently.  */
  if (addr_size == 0)
    addr_size = 4;
  BFD_ASSERT (addr_size == 4 || addr_size == 8);

  /* Read each remaining comp. units checking each as they are read.  */
  while (stash->info_ptr < stash->info_ptr_end)
    {
      bfd_vma length;
      unsigned int offset_size = addr_size;
      bfd_byte *info_ptr_unit = stash->info_ptr;

      length = read_4_bytes (stash->bfd_ptr, stash->info_ptr, stash->info_ptr_end);
      /* A 0xffffff length is the DWARF3 way of indicating
	 we use 64-bit offsets, instead of 32-bit offsets.  */
      if (length == 0xffffffff)
	{
	  offset_size = 8;
	  length = read_8_bytes (stash->bfd_ptr, stash->info_ptr + 4, stash->info_ptr_end);
	  stash->info_ptr += 12;
	}
      /* A zero length is the IRIX way of indicating 64-bit offsets,
	 mostly because the 64-bit length will generally fit in 32
	 bits, and the endianness helps.  */
      else if (length == 0)
	{
	  offset_size = 8;
	  length = read_4_bytes (stash->bfd_ptr, stash->info_ptr + 4, stash->info_ptr_end);
	  stash->info_ptr += 8;
	}
      /* In the absence of the hints above, we assume 32-bit DWARF2
	 offsets even for targets with 64-bit addresses, because:
	   a) most of the time these targets will not have generated
	      more than 2Gb of debug info and so will not need 64-bit
	      offsets,
	 and
	   b) if they do use 64-bit offsets but they are not using
	      the size hints that are tested for above then they are
	      not conforming to the DWARF3 standard anyway.  */
      else if (addr_size == 8)
	{
	  offset_size = 4;
	  stash->info_ptr += 4;
	}
      else
	stash->info_ptr += 4;

      if (length > 0)
	{
	  bfd_byte * new_ptr;

	  /* PR 21151  */
	  if (stash->info_ptr + length > stash->info_ptr_end)
	    return FALSE;

	  each = parse_comp_unit (stash, length, info_ptr_unit,
				  offset_size);
	  if (!each)
	    /* The dwarf information is damaged, don't trust it any
	       more.  */
	    break;

	  new_ptr = stash->info_ptr + length;
	  /* PR 17512: file: 1500698c.  */
	  if (new_ptr < stash->info_ptr)
	    {
	      /* A corrupt length value - do not trust the info any more.  */
	      found = FALSE;
	      break;
	    }
	  else
	    stash->info_ptr = new_ptr;

	  if (stash->all_comp_units)
	    stash->all_comp_units->prev_unit = each;
	  else
	    stash->last_comp_unit = each;

	  each->next_unit = stash->all_comp_units;
	  stash->all_comp_units = each;

	  /* DW_AT_low_pc and DW_AT_high_pc are optional for
	     compilation units.  If we don't have them (i.e.,
	     unit->high == 0), we need to consult the line info table
	     to see if a compilation unit contains the given
	     address.  */
	  if (do_line)
	    found = (((symbol->flags & BSF_FUNCTION) == 0
		      || each->arange.high == 0
		      || comp_unit_contains_address (each, addr))
		     && comp_unit_find_line (each, symbol, addr,
					     filename_ptr,
					     linenumber_ptr,
					     stash));
	  else
	    found = ((each->arange.high == 0
		      || comp_unit_contains_address (each, addr))
		     && comp_unit_find_nearest_line (each, addr,
						     filename_ptr,
						     &function,
						     linenumber_ptr,
						     discriminator_ptr,
						     stash) != 0);

	  if ((bfd_vma) (stash->info_ptr - stash->sec_info_ptr)
	      == stash->sec->size)
	    {
	      stash->sec = find_debug_info (stash->bfd_ptr, debug_sections,
					    stash->sec);
	      stash->sec_info_ptr = stash->info_ptr;
	    }

	  if (found)
	    goto done;
	}
    }

 done:
  if (function)
    {
      if (!function->is_linkage)
	{
	  asymbol *fun;
	  bfd_vma sec_vma;

	  fun = _bfd_elf_find_function (abfd, symbols, section, offset,
					*filename_ptr ? NULL : filename_ptr,
					functionname_ptr);
	  sec_vma = section->vma;
	  if (section->output_section != NULL)
	    sec_vma = section->output_section->vma + section->output_offset;
	  if (fun != NULL
	      && fun->value + sec_vma == function->arange.low)
	    function->name = *functionname_ptr;
	  /* Even if we didn't find a linkage name, say that we have
	     to stop a repeated search of symbols.  */
	  function->is_linkage = TRUE;
	}
      *functionname_ptr = function->name;
    }
  if ((abfd->flags & (EXEC_P | DYNAMIC)) == 0)
    unset_sections (stash);

  return found;
}
