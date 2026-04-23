#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef unsigned long long dwarf_vma;
typedef long long          dwarf_signed_vma;
typedef unsigned long long dwarf_size_type;
typedef unsigned long long elf_vma;

enum dwarf_section_display_enum
{
  abbrev = 0,
  aranges,
  frame,
  info,
  line,
  pubnames,
  gnu_pubnames,
  eh_frame,
  macinfo,
  macro,
  str,
  line_str,
  loc,
  loclists,
  pubtypes,
  gnu_pubtypes,
  ranges,
  rnglists,
  static_func,
  static_vars,
  types,
  weaknames,
  gdb_index,
  debug_names,
  trace_info,
  trace_abbrev,
  trace_aranges,
  info_dwo,
  abbrev_dwo,
  types_dwo,
  line_dwo,
  loc_dwo,
  macro_dwo,
  macinfo_dwo,
  str_dwo,
  str_index,
  str_index_dwo,
  debug_addr,
  dwp_cu_index,
  dwp_tu_index,
  gnu_debuglink,
  gnu_debugaltlink,
  debug_sup,
  separate_debug_str,
  note_gnu_build_id,
  max
};

struct dwarf_section
{
  const char *                     uncompressed_name;
  const char *                     compressed_name;
  const char *                     xcoff_name;
  const char *                     name;
  const char *                     filename;
  unsigned char *                  start;
  dwarf_vma                        address;
  dwarf_size_type                  size;
  enum dwarf_section_display_enum  abbrev_sec;
  void *                           reloc_info;
  unsigned long                    num_relocs;
};

struct dwarf_section_display
{
  struct dwarf_section section;
  int (*display) (struct dwarf_section *, void *);
  int *enabled;
  bool relocate;
};

extern struct dwarf_section_display debug_displays [];

typedef struct
{
  uint64_t   signature;
  dwarf_vma  section_offsets[8];
  size_t     section_sizes[8];
} cu_tu_set;

typedef struct
{
  unsigned int   pointer_size;
  unsigned int   offset_size;
  int            dwarf_version;
  dwarf_vma	 cu_offset;
  dwarf_vma	 base_address;
  dwarf_vma	 addr_base;
  dwarf_vma	 ranges_base;
  dwarf_vma *    loc_offsets;
  dwarf_vma *    loc_views;
  int *          have_frame_base;
  unsigned int   num_loc_offsets;
  unsigned int   max_loc_offsets;
  unsigned int   num_loc_views;
  dwarf_vma      loclists_base;
  dwarf_vma *    range_lists;
  unsigned int   num_range_lists;
  unsigned int   max_range_lists;
  dwarf_vma      rnglists_base;
  dwarf_vma      str_offsets_base;
} debug_info;

typedef struct
{
  dwarf_vma	 cu_length;
  unsigned short cu_version;
  dwarf_vma	 cu_abbrev_offset;
  unsigned char  cu_pointer_size;
  unsigned int   cu_unit_type;
} DWARF2_Internal_CompUnit;

typedef struct abbrev_attr
{
  unsigned long          attribute;
  unsigned long          form;
  dwarf_signed_vma       implicit_const;
  struct abbrev_attr *   next;
} abbrev_attr;

typedef struct abbrev_entry
{
  unsigned long          number;
  unsigned long          tag;
  int                    children;
  struct abbrev_attr *   first_attr;
  struct abbrev_attr *   last_attr;
  struct abbrev_entry *  next;
} abbrev_entry;

typedef struct abbrev_list
{
  abbrev_entry *        first_abbrev;
  abbrev_entry *        last_abbrev;
  dwarf_vma             abbrev_base;
  dwarf_vma             abbrev_offset;
  struct abbrev_list *  next;
  unsigned char *       start_of_next_abbrevs;
} abbrev_list;

typedef struct abbrev_map
{
  dwarf_vma      start;
  dwarf_vma      end;
  abbrev_list *  list;
} abbrev_map;

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
  DW_TAG_template_type_parameter = 0x2f,
  DW_TAG_template_value_parameter = 0x30,
  DW_TAG_thrown_type = 0x31,
  DW_TAG_try_block = 0x32,
  DW_TAG_variant_part = 0x33,
  DW_TAG_variable = 0x34,
  DW_TAG_volatile_type = 0x35,
  DW_TAG_dwarf_procedure = 0x36,
  DW_TAG_restrict_type = 0x37,
  DW_TAG_interface_type = 0x38,
  DW_TAG_namespace = 0x39,
  DW_TAG_imported_module = 0x3a,
  DW_TAG_unspecified_type = 0x3b,
  DW_TAG_partial_unit = 0x3c,
  DW_TAG_imported_unit = 0x3d,
  DW_TAG_skeleton_unit = 0x3e,
  DW_TAG_subtype = 0x3f,
  DW_TAG_lo_user = 0x4080,
  DW_TAG_hi_user = 0xffff,
  DW_TAG_GNU_call_site = 0x4109,
  DW_TAG_GNU_call_site_parameter = 0x410a
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
  DW_FORM_ref_sup4 = 0x1c,
  DW_FORM_strp_sup = 0x1d,
  DW_FORM_data16 = 0x1e,
  DW_FORM_line_strp = 0x1f,
  DW_FORM_ref_sig8 = 0x20,
  DW_FORM_implicit_const = 0x21,
  DW_FORM_loclistx = 0x22,
  DW_FORM_rnglistx = 0x23,
  DW_FORM_ref_sup8 = 0x24,
  DW_FORM_strx1 = 0x25,
  DW_FORM_strx2 = 0x26,
  DW_FORM_strx3 = 0x27,
  DW_FORM_strx4 = 0x28,
  DW_FORM_addrx1 = 0x29,
  DW_FORM_addrx2 = 0x2a,
  DW_FORM_addrx3 = 0x2b,
  DW_FORM_addrx4 = 0x2c,
  DW_FORM_GNU_addr_index = 0x1f01,
  DW_FORM_GNU_str_index = 0x1f02,
  DW_FORM_GNU_ref_alt = 0x1f20,
  DW_FORM_GNU_strp_alt = 0x1f21
};

enum dwarf_attribute {
  DW_AT_sibling = 0x01,
  DW_AT_location = 0x02,
  DW_AT_name = 0x03,
  DW_AT_ordering = 0x09,
  DW_AT_byte_size = 0x0b,
  DW_AT_bit_offset = 0x0c,
  DW_AT_bit_size = 0x0d,
  DW_AT_stmt_list = 0x10,
  DW_AT_low_pc = 0x11,
  DW_AT_high_pc = 0x12,
  DW_AT_language = 0x13,
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
  DW_AT_lo_user = 0x2000,
  DW_AT_hi_user = 0x3fff,
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
  DW_AT_MIPS_assumed_shape_dopetype = 0x2010,
  DW_AT_MIPS_assumed_size = 0x2011,
  DW_AT_sf_names = 0x2101,
  DW_AT_src_info = 0x2102,
  DW_AT_mac_info = 0x2103,
  DW_AT_src_coords = 0x2104,
  DW_AT_body_begin = 0x2105,
  DW_AT_body_end = 0x2106,
  DW_AT_GNU_vector = 0x2107,
  DW_AT_GNU_template_name = 0x2110,
  DW_AT_GNU_odr_signature = 0x210f,
  DW_AT_GNU_call_site_value = 0x2111,
  DW_AT_GNU_call_site_data_value = 0x2112,
  DW_AT_GNU_call_site_target = 0x2113,
  DW_AT_GNU_call_site_target_clobbered = 0x2114,
  DW_AT_GNU_locviews = 0x2137,
  DW_AT_GNU_entry_view = 0x2138,
  DW_AT_GNU_dwo_name = 0x2130,
  DW_AT_GNU_dwo_id = 0x2131,
  DW_AT_GNU_ranges_base = 0x2132,
  DW_AT_GNU_addr_base = 0x2133,
  DW_AT_GNU_pubnames = 0x2134,
  DW_AT_GNU_pubtypes = 0x2135,
  DW_AT_stride = 0x2136,
  DW_AT_bit_stride = 0x2137
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
  DW_OP_deref_size = 0x40,
  DW_OP_xderef_size = 0x41,
  DW_OP_nop = 0x42,
  DW_OP_push_object_address = 0x43,
  DW_OP_call2 = 0x44,
  DW_OP_call4 = 0x45,
  DW_OP_call_ref = 0x46,
  DW_OP_form_tls_address = 0x47,
  DW_OP_call_frame_cfa = 0x48,
  DW_OP_bit_piece = 0x49,
  DW_OP_implicit_value = 0x4a,
  DW_OP_stack_value = 0x4b,
  DW_OP_implicit_pointer = 0x4c,
  DW_OP_addrx = 0x4d,
  DW_OP_constx = 0x4e,
  DW_OP_entry_value = 0x4f,
  DW_OP_const_type = 0x50,
  DW_OP_regval_type = 0x51,
  DW_OP_deref_type = 0x52,
  DW_OP_xderef_type = 0x53,
  DW_OP_convert = 0x54,
  DW_OP_reinterpret = 0x55,
  DW_OP_lo_user = 0xe0,
  DW_OP_hi_user = 0xff,
  DW_OP_GNU_push_tls_address = 0xe0,
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
  DW_OP_GNU_addr_index = 0xfb,
  DW_OP_GNU_const_index = 0xfc,
  DW_OP_GNU_const_implicit_pointer = 0xfd,
  DW_OP_GNU_implicit_pointer_tag = 0xfe
};

enum dwarf_type {
  DW_ATE_void = 0x00,
  DW_ATE_address = 0x01,
  DW_ATE_boolean = 0x02,
  DW_ATE_complex_float = 0x03,
  DW_ATE_float = 0x04,
  DW_ATE_signed = 0x05,
  DW_ATE_signed_char = 0x06,
  DW_ATE_unsigned = 0x07,
  DW_ATE_unsigned_char = 0x08,
  DW_ATE_imaginary_float = 0x09,
  DW_ATE_packed_decimal = 0x0a,
  DW_ATE_numeric_string = 0x0b,
  DW_ATE_edited = 0x0c,
  DW_ATE_signed_fixed = 0x0d,
  DW_ATE_unsigned_fixed = 0x0e,
  DW_ATE_decimal_float = 0x0f,
  DW_ATE_UTF = 0x10,
  DW_ATE_UCS = 0x11,
  DW_ATE_ASCII = 0x12,
  DW_ATE_lo_user = 0x80,
  DW_ATE_hi_user = 0xff,
  DW_ATE_HP_float80 = 0x80,
  DW_ATE_HP_complex_float80 = 0x81,
  DW_ATE_HP_float128 = 0x82,
  DW_ATE_HP_complex_float128 = 0x83,
  DW_ATE_HP_floathpintel = 0x84,
  DW_ATE_HP_imaginary_float80 = 0x85,
  DW_ATE_HP_imaginary_float128 = 0x86
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
  DW_LANG_RenderScript = 0x0024,
  DW_LANG_lo_user = 0x8000,
  DW_LANG_hi_user = 0xffff,
  DW_LANG_Mips_Assembler = 0x8001,
  DW_LANG_Upc = 0x8765
};

enum dwarf_inline_attribute {
  DW_INL_not_inlined = 0,
  DW_INL_inlined = 1,
  DW_INL_declared_not_inlined = 2,
  DW_INL_declared_inlined = 3
};

enum dwarf_access_attribute {
  DW_ACCESS_public = 1,
  DW_ACCESS_protected = 2,
  DW_ACCESS_private = 3
};

enum dwarf_visibility_attribute {
  DW_VIS_local = 1,
  DW_VIS_exported = 2,
  DW_VIS_qualified = 3
};

enum dwarf_endianity_encoding {
  DW_END_default = 0x00,
  DW_END_big = 0x01,
  DW_END_little = 0x02,
  DW_END_lo_user = 0x40,
  DW_END_hi_user = 0xff
};

enum dwarf_virtuality_attribute {
  DW_VIRTUALITY_none = 0,
  DW_VIRTUALITY_virtual = 1,
  DW_VIRTUALITY_pure_virtual = 2
};

enum dwarf_id_case {
  DW_ID_case_sensitive = 0,
  DW_ID_up_case = 1,
  DW_ID_down_case = 2,
  DW_ID_case_insensitive = 3
};

enum dwarf_calling_convention {
  DW_CC_normal = 0x1,
  DW_CC_program = 0x2,
  DW_CC_nocall = 0x3,
  DW_CC_pass_by_reference = 0x4,
  DW_CC_pass_by_value = 0x5,
  DW_CC_lo_user = 0x40,
  DW_CC_hi_user = 0xff,
  DW_CC_GNU_renesas_sh = 0x40,
  DW_CC_GNU_borland_fastcall_i386 = 0x41
};

enum dwarf_decimal_sign_encoding {
  DW_DS_unsigned = 0x01,
  DW_DS_leading_overpunch = 0x02,
  DW_DS_trailing_overpunch = 0x03,
  DW_DS_leading_separate = 0x04,
  DW_DS_trailing_separate = 0x05
};

enum dwarf_defaulted_attribute {
  DW_DEFAULTED_no = 0x00,
  DW_DEFAULTED_in_class = 0x01,
  DW_DEFAULTED_out_of_class = 0x02
};

enum dwarf_unit_type {
  DW_UT_compile = 0x01,
  DW_UT_type = 0x02,
  DW_UT_partial = 0x03,
  DW_UT_skeleton = 0x04,
  DW_UT_split_compile = 0x05,
  DW_UT_split_type = 0x06,
  DW_UT_lo_user = 0x80,
  DW_UT_hi_user = 0xff
};

enum dwarf_sect {
  DW_SECT_INFO = 1,
  DW_SECT_TYPES = 2,
  DW_SECT_ABBREV = 3,
  DW_SECT_LINE = 4,
  DW_SECT_LOC = 5,
  DW_SECT_STR_OFFSETS = 6,
  DW_SECT_MACINFO = 7,
  DW_SECT_MACRO = 8,
  DW_SECT_MAX = 8
};

#define DW_EH_PE_signed		0x08
#define DW_EH_PE_pcrel		0x10

#define _(X) (X)

#define ENABLE_CHECKING 0

#define ARRAY_SIZE(x) (sizeof (x) / sizeof ((x)[0]))

#define MAX_CU_NESTING (1 << 8)

#define DEBUG_INFO_UNAVAILABLE  (unsigned int) -1

extern elf_vma (*byte_get) (const unsigned char *, unsigned int);
extern elf_vma byte_get_little_endian (const unsigned char *, unsigned int);
extern elf_vma byte_get_signed (const unsigned char *, unsigned int);

extern void error (const char *, ...);
extern void warn (const char *, ...);

extern void * cmalloc (size_t, size_t);
extern void * xcrealloc (void *, size_t, size_t);

extern const char *get_DW_TAG_name (unsigned int tag);
extern const char *get_DW_AT_name (unsigned int attr);
extern const char *get_DW_FORM_name (unsigned int form);
extern const char *get_DW_OP_name (unsigned int op);
extern const char *get_DW_ATE_name (unsigned int enc);
extern const char *get_DW_CFA_name (unsigned int opc);
extern const char *get_DW_IDX_name (unsigned int idx);
extern const char *get_DW_UT_name (unsigned int ut);

static const char *get_TAG_name (unsigned long tag)
{
  const char *name = get_DW_TAG_name ((unsigned int) tag);
  if (name == NULL)
    {
      static char buffer[100];
      if (tag >= DW_TAG_lo_user && tag <= DW_TAG_hi_user)
	snprintf (buffer, sizeof (buffer), "User TAG value: %#lx", tag);
      else
	snprintf (buffer, sizeof (buffer), "Unknown TAG value: %#lx", tag);
      return buffer;
    }
  return name;
}

static const char *get_FORM_name (unsigned long form)
{
  const char *name;
  if (form == 0)
    return "DW_FORM value: 0";
  name = get_DW_FORM_name (form);
  if (name == NULL)
    {
      static char buffer[100];
      snprintf (buffer, sizeof (buffer), "Unknown FORM value: %lx", form);
      return buffer;
    }
  return name;
}

static const char *get_AT_name (unsigned long attribute)
{
  const char *name = get_DW_AT_name ((unsigned int) attribute);
  if (name == NULL)
    {
      static char buffer[100];
      snprintf (buffer, sizeof (buffer), "Unknown AT value: %lx", attribute);
      return buffer;
    }
  return name;
}

#define DWARF_VMA_FMT_LONG	"%16.16llx"

static const char *dwarf_vmatoa_1 (const char *fmtch, dwarf_vma value, unsigned num_bytes)
{
  static int buf_pos = 0;
  static struct { char place[64]; } buf[16];
  char *ret;
  ret = buf[buf_pos++].place;
  buf_pos %= 16;
  if (num_bytes)
    {
      snprintf (ret, sizeof (buf[0].place), DWARF_VMA_FMT_LONG, value);
      if (num_bytes > 8)
	num_bytes = 8;
      return ret + (16 - 2 * num_bytes);
    }
  else
    {
      char fmt[32];
      if (fmtch)
	sprintf (fmt, "%%%s%s", "ll", fmtch);
      else
	sprintf (fmt, "%%%s", "ll");
      snprintf (ret, sizeof (buf[0].place), fmt, value);
      return ret;
    }
}

static inline const char *dwarf_vmatoa (const char * fmtch, dwarf_vma value)
{
  return dwarf_vmatoa_1 (fmtch, value, 0);
}

extern dwarf_vma read_leb128 (unsigned char *, const unsigned char *const, bool, unsigned int *, int *);

static inline void report_leb_status (int status)
{
  if ((status & 1) != 0)
    error ("end of data encountered whilst reading LEB\n");
  else if ((status & 2) != 0)
    error ("read LEB value is too large to store in destination variable\n");
}

#define READ_ULEB(var, start, end)				\
  do								\
    {								\
      dwarf_vma _val;						\
      unsigned int _len;					\
      int _status;						\
      _val = read_leb128 (start, end, false, &_len, &_status);	\
      start += _len;						\
      (var) = _val;						\
      if ((var) != _val)					\
	_status |= 2;						\
      report_leb_status (_status);				\
    }								\
  while (0)

#define READ_SLEB(var, start, end)				\
  do								\
    {								\
      dwarf_signed_vma _val;					\
      unsigned int _len;					\
      int _status;						\
      _val = read_leb128 (start, end, true, &_len, &_status);	\
      start += _len;						\
      (var) = _val;						\
      if ((var) != _val)					\
	_status |= 2;						\
      report_leb_status (_status);				\
    }								\
  while (0)

#define SAFE_BYTE_GET_INTERNAL(VAL, PTR, AMOUNT, END, FUNC, INC)	\
  do									\
    {									\
      size_t amount = (AMOUNT);						\
      if (sizeof (VAL) < amount)					\
	{								\
	  error ("internal error: attempt to read %d bytes of data in to %d sized variable", \
		 (int) amount, (int) sizeof (VAL));			\
	  amount = sizeof (VAL);					\
	}								\
      if (ENABLE_CHECKING)						\
	assert ((PTR) <= (END));					\
      size_t avail = (END) - (PTR);					\
      if ((PTR) > (END))						\
	avail = 0;							\
      if (amount > avail)						\
	amount = avail;							\
      if (amount == 0)							\
	(VAL) = 0;							\
      else								\
	(VAL) = (FUNC) ((PTR), amount);					\
      if (INC)								\
	(PTR) += amount;						\
    }									\
  while (0)

#define SAFE_BYTE_GET(VAL, PTR, AMOUNT, END)	\
  SAFE_BYTE_GET_INTERNAL (VAL, PTR, AMOUNT, END, byte_get, false)

#define SAFE_BYTE_GET_AND_INC(VAL, PTR, AMOUNT, END)	\
  SAFE_BYTE_GET_INTERNAL (VAL, PTR, AMOUNT, END, byte_get, true)

extern int do_debug_loc;
extern int do_debug_ranges;
extern int do_debug_info;
extern int do_wide;
extern int dwarf_cutoff_level;
extern unsigned long dwarf_start_die;

extern debug_info *debug_information;
extern unsigned int num_debug_info_entries;
extern unsigned int alloc_num_debug_info_entries;

static int have_frame_base;
static int need_base_address;
static bool need_dwo_info;
static bool level_type_signed[MAX_CU_NESTING];
static const dwarf_vma vm1 = -1;

extern abbrev_map *cu_abbrev_map;
extern unsigned long next_free_abbrev_map_entry;

extern cu_tu_set *find_cu_tu_set_v2 (unsigned int, bool);
extern abbrev_list *find_abbrev_list_by_abbrev_offset (dwarf_vma, dwarf_vma);
extern abbrev_list *new_abbrev_list (dwarf_vma, dwarf_vma);
extern unsigned char *process_abbrev_set (struct dwarf_section *, dwarf_vma, size_t, dwarf_vma, abbrev_list *);
extern void record_abbrev_list_for_cu (dwarf_vma, dwarf_vma, abbrev_list *);
extern void free_all_abbrevs (void);

extern bool load_debug_section_with_follow (enum dwarf_section_display_enum, void *);
extern void introduce (struct dwarf_section *, bool);

extern const char *fetch_indirect_string (dwarf_vma);
extern const char *fetch_indirect_line_string (dwarf_vma);
extern const char *fetch_alt_indirect_string (dwarf_vma);
extern const char *fetch_indexed_string (dwarf_vma, cu_tu_set *, unsigned int, bool, dwarf_vma);
extern dwarf_vma fetch_indexed_addr (dwarf_vma, uint32_t);
extern dwarf_vma fetch_indexed_value (dwarf_vma, enum dwarf_section_display_enum);

extern dwarf_vma check_uvalue (const unsigned char *, dwarf_vma, const unsigned char *);
extern unsigned char *display_block (unsigned char *, dwarf_vma, const unsigned char *, char);
extern int decode_location_expression (unsigned char *, unsigned int, unsigned int, int, dwarf_vma, dwarf_vma, struct dwarf_section *);
extern void display_discr_list (unsigned long, dwarf_vma, unsigned char *, int);

extern abbrev_entry *get_type_abbrev_from_form (unsigned long, dwarf_vma, dwarf_vma, const unsigned char *, struct dwarf_section *, unsigned long *, unsigned char **, abbrev_map **);
extern void get_type_signedness (abbrev_entry *, struct dwarf_section *, unsigned char *, const unsigned char *, dwarf_vma, unsigned int, unsigned int, int, bool *, int);

extern void add_dwo_name (const char *, dwarf_vma);
extern void add_dwo_dir (const char *, dwarf_vma);
extern void add_dwo_id (const char *, dwarf_vma);

static unsigned char *
read_and_display_attr_value (unsigned long           attribute,
			     unsigned long           form,
			     dwarf_signed_vma        implicit_const,
			     unsigned char *         start,
			     unsigned char *         data,
			     unsigned char *         end,
			     dwarf_vma               cu_offset,
			     dwarf_vma               pointer_size,
			     dwarf_vma               offset_size,
			     int                     dwarf_version,
			     debug_info *            debug_info_p,
			     int                     do_loc,
			     struct dwarf_section *  section,
			     cu_tu_set *      this_set,
			     char                    delimiter,
			     int                     level)
{
  dwarf_signed_vma svalue;
  dwarf_vma uvalue = 0;
  dwarf_vma uvalue_hi = 0;
  unsigned char *block_start = NULL;
  unsigned char *orig_data = data;

  if (data > end || (data == end && form != DW_FORM_flag_present))
    {
      warn (_("Corrupt attribute\n"));
      return data;
    }

  if (do_wide && ! do_loc)
    {
      /* PR 26847: Display the name of the form.  */
      const char * name = get_FORM_name (form);

      /* For convenience we skip the DW_FORM_ prefix to the name.  */
      if (name[0] == 'D')
	name += 8; /* strlen ("DW_FORM_")  */
      printf ("%c(%s)", delimiter, name);
    }

  switch (form)
    {
    case DW_FORM_ref_addr:
      if (dwarf_version == 2)
	SAFE_BYTE_GET_AND_INC (uvalue, data, pointer_size, end);
      else if (dwarf_version > 2)
	SAFE_BYTE_GET_AND_INC (uvalue, data, offset_size, end);
      else
	error (_("Internal error: DW_FORM_ref_addr is not supported in DWARF version 1.\n"));
      break;

    case DW_FORM_addr:
      SAFE_BYTE_GET_AND_INC (uvalue, data, pointer_size, end);
      break;

    case DW_FORM_strp_sup:
    case DW_FORM_strp:
    case DW_FORM_line_strp:
    case DW_FORM_sec_offset:
    case DW_FORM_GNU_ref_alt:
    case DW_FORM_GNU_strp_alt:
      SAFE_BYTE_GET_AND_INC (uvalue, data, offset_size, end);
      break;

    case DW_FORM_flag_present:
      uvalue = 1;
      break;

    case DW_FORM_ref1:
    case DW_FORM_flag:
    case DW_FORM_data1:
    case DW_FORM_strx1:
    case DW_FORM_addrx1:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 1, end);
      break;

    case DW_FORM_ref2:
    case DW_FORM_data2:
    case DW_FORM_strx2:
    case DW_FORM_addrx2:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 2, end);
      break;

    case DW_FORM_strx3:
    case DW_FORM_addrx3:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 3, end);
      break;

    case DW_FORM_ref_sup4:
    case DW_FORM_ref4:
    case DW_FORM_data4:
    case DW_FORM_strx4:
    case DW_FORM_addrx4:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 4, end);
      break;

    case DW_FORM_ref_sup8:
    case DW_FORM_ref8:
    case DW_FORM_data8:
    case DW_FORM_ref_sig8:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 8, end);
      break;

    case DW_FORM_data16:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 8, end);
      SAFE_BYTE_GET_AND_INC (uvalue_hi, data, 8, end);
      if (byte_get != byte_get_little_endian)
	{
	  dwarf_vma utmp = uvalue;
	  uvalue = uvalue_hi;
	  uvalue_hi = utmp;
	}
      break;

    case DW_FORM_sdata:
      READ_SLEB (svalue, data, end);
      uvalue = svalue;
      break;

    case DW_FORM_GNU_str_index:
    case DW_FORM_strx:
    case DW_FORM_ref_udata:
    case DW_FORM_udata:
    case DW_FORM_GNU_addr_index:
    case DW_FORM_addrx:
    case DW_FORM_loclistx:
    case DW_FORM_rnglistx:
      READ_ULEB (uvalue, data, end);
      break;

    case DW_FORM_indirect:
      READ_ULEB (form, data, end);
      if (!do_loc)
	printf ("%c%s", delimiter, get_FORM_name (form));
      if (form == DW_FORM_implicit_const)
	READ_SLEB (implicit_const, data, end);
      return read_and_display_attr_value (attribute, form, implicit_const,
					  start, data, end,
					  cu_offset, pointer_size,
					  offset_size, dwarf_version,
					  debug_info_p, do_loc,
					  section, this_set, delimiter, level);

    case DW_FORM_implicit_const:
      uvalue = implicit_const;
      break;

    default:
      break;
    }

  switch (form)
    {
    case DW_FORM_ref_addr:
      if (!do_loc)
	printf ("%c<0x%s>", delimiter, dwarf_vmatoa ("x", uvalue));
      break;

    case DW_FORM_GNU_ref_alt:
      if (!do_loc)
	{
	  if (do_wide)
	    /* We have already printed the form name.  */
	    printf ("%c<0x%s>", delimiter, dwarf_vmatoa ("x", uvalue));
	  else
	    printf ("%c<alt 0x%s>", delimiter, dwarf_vmatoa ("x", uvalue));
	}
      /* FIXME: Follow the reference...  */
      break;

    case DW_FORM_ref1:
    case DW_FORM_ref2:
    case DW_FORM_ref4:
    case DW_FORM_ref_sup4:
    case DW_FORM_ref_udata:
      if (!do_loc)
	printf ("%c<0x%s>", delimiter, dwarf_vmatoa ("x", uvalue + cu_offset));
      break;

    case DW_FORM_data4:
    case DW_FORM_addr:
    case DW_FORM_sec_offset:
      if (!do_loc)
	printf ("%c0x%s", delimiter, dwarf_vmatoa ("x", uvalue));
      break;

    case DW_FORM_flag_present:
    case DW_FORM_flag:
    case DW_FORM_data1:
    case DW_FORM_data2:
    case DW_FORM_sdata:
      if (!do_loc)
	printf ("%c%s", delimiter, dwarf_vmatoa ("d", uvalue));
      break;

    case DW_FORM_udata:
      if (!do_loc)
	printf ("%c%s", delimiter, dwarf_vmatoa ("u", uvalue));
      break;

    case DW_FORM_implicit_const:
      if (!do_loc)
	printf ("%c%s", delimiter, dwarf_vmatoa ("d", implicit_const));
      break;

    case DW_FORM_ref_sup8:
    case DW_FORM_ref8:
    case DW_FORM_data8:
      if (!do_loc)
	{
	  dwarf_vma utmp = uvalue;
	  if (form == DW_FORM_ref8)
	    utmp += cu_offset;
	  printf ("%c0x%s", delimiter, dwarf_vmatoa ("x", utmp));
	}
      break;

    case DW_FORM_data16:
      if (!do_loc)
	printf (" 0x%s%s",
		uvalue_hi == 0 ? "" : dwarf_vmatoa ("x", uvalue_hi),
		dwarf_vmatoa_1 ("x", uvalue, uvalue_hi == 0 ? 0 : 8));
      break;

    case DW_FORM_string:
      if (!do_loc)
	printf ("%c%.*s", delimiter, (int) (end - data), data);
      data += strnlen ((char *) data, end - data);
      if (data < end)
	data++;
      break;

    case DW_FORM_block:
    case DW_FORM_exprloc:
      READ_ULEB (uvalue, data, end);
    do_block:
      block_start = data;
      if (block_start >= end)
	{
	  warn (_("Block ends prematurely\n"));
	  uvalue = 0;
	  block_start = end;
	}

      uvalue = check_uvalue (block_start, uvalue, end);

      data = block_start + uvalue;
      if (!do_loc)
	{
	  unsigned char op;

	  SAFE_BYTE_GET (op, block_start, sizeof (op), end);
	  if (op != DW_OP_addrx)
	    data = display_block (block_start, uvalue, end, delimiter);
	}
      break;

    case DW_FORM_block1:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 1, end);
      goto do_block;

    case DW_FORM_block2:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 2, end);
      goto do_block;

    case DW_FORM_block4:
      SAFE_BYTE_GET_AND_INC (uvalue, data, 4, end);
      goto do_block;

    case DW_FORM_strp:
      if (!do_loc)
	{
	  if (do_wide)
	    /* We have already displayed the form name.  */
	    printf (_("%c(offset: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_indirect_string (uvalue));
	  else
	    printf (_("%c(indirect string, offset: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_indirect_string (uvalue));
	}
      break;

    case DW_FORM_line_strp:
      if (!do_loc)
	{
	  if (do_wide)
	    /* We have already displayed the form name.  */
	    printf (_("%c(offset: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_indirect_line_string (uvalue));
	  else
	    printf (_("%c(indirect line string, offset: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_indirect_line_string (uvalue));
	}
      break;

    case DW_FORM_GNU_str_index:
    case DW_FORM_strx:
    case DW_FORM_strx1:
    case DW_FORM_strx2:
    case DW_FORM_strx3:
    case DW_FORM_strx4:
      if (!do_loc)
	{
	  const char *suffix = section ? strrchr (section->name, '.') : NULL;
	  bool dwo = suffix && strcmp (suffix, ".dwo") == 0;
    const char *strng;
    strng = fetch_indexed_string (uvalue, this_set, offset_size, dwo,
                                     debug_info_p ? debug_info_p->str_offsets_base : 0);

	  if (do_wide)
	    /* We have already displayed the form name.  */
	    printf (_("%c(offset: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue), strng);
	  else
	    printf (_("%c(indexed string: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue), strng);
	}
      break;

    case DW_FORM_GNU_strp_alt:
      if (!do_loc)
	{
	  if (do_wide)
	    /* We have already displayed the form name.  */
	    printf (_("%c(offset: 0x%s) %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_alt_indirect_string (uvalue));
	  else
	    printf (_("%c(alt indirect string, offset: 0x%s) %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    fetch_alt_indirect_string (uvalue));
	}
      break;

    case DW_FORM_indirect:
      /* Handled above.  */
      break;

    case DW_FORM_ref_sig8:
      if (!do_loc)
	printf ("%c%s: 0x%s", delimiter, do_wide ? "" : "signature",
		dwarf_vmatoa ("x", uvalue));
      break;

    case DW_FORM_GNU_addr_index:
    case DW_FORM_addrx:
    case DW_FORM_addrx1:
    case DW_FORM_addrx2:
    case DW_FORM_addrx3:
    case DW_FORM_addrx4:
    case DW_FORM_loclistx:
    case DW_FORM_rnglistx:
      if (!do_loc)
	{
	  dwarf_vma base;
	  dwarf_vma offset;

	  if (debug_info_p == NULL)
	    base = 0;
	  else if (debug_info_p->addr_base == DEBUG_INFO_UNAVAILABLE)
	    base = 0;
	  else
	    base = debug_info_p->addr_base;

	  offset = base + uvalue * pointer_size;

	  if (do_wide)
	    /* We have already displayed the form name.  */
	    printf (_("%c(index: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    dwarf_vmatoa ("x", fetch_indexed_addr (offset, pointer_size)));
	  else
	    printf (_("%c(addr_index: 0x%s): %s"), delimiter,
		    dwarf_vmatoa ("x", uvalue),
		    dwarf_vmatoa ("x", fetch_indexed_addr (offset, pointer_size)));
	}
      break;

    case DW_FORM_strp_sup:
      if (!do_loc)
	printf ("%c<0x%s>", delimiter, dwarf_vmatoa ("x", uvalue + cu_offset));
      break;
      
    default:
      warn (_("Unrecognized form: 0x%lx\n"), form);
      /* What to do?  Consume a byte maybe?  */
      ++data;
      break;
    }

  if ((do_loc || do_debug_loc || do_debug_ranges || do_debug_info)
      && num_debug_info_entries == 0
      && debug_info_p != NULL)
    {
      switch (attribute)
	{
	case DW_AT_loclists_base:
	  if (debug_info_p->loclists_base)
	    warn (_("CU @ 0x%s has multiple loclists_base values"),
		  dwarf_vmatoa ("x", debug_info_p->cu_offset));
	  debug_info_p->loclists_base = uvalue;
	  break;
	case DW_AT_rnglists_base:
	  if (debug_info_p->rnglists_base)
	    warn (_("CU @ 0x%s has multiple rnglists_base values"),
	          dwarf_vmatoa ("x", debug_info_p->cu_offset));
	  debug_info_p->rnglists_base = uvalue;
	  break;
	case DW_AT_str_offsets_base:
	  if (debug_info_p->str_offsets_base)
	    warn (_("CU @ 0x%s has multiple str_offsets_base values"),
		  dwarf_vmatoa ("x", debug_info_p->cu_offset));
	  debug_info_p->str_offsets_base = uvalue;
	  break;

	case DW_AT_frame_base:
	  have_frame_base = 1;
	  /* Fall through.  */
	case DW_AT_location:
	case DW_AT_GNU_locviews:
	case DW_AT_string_length:
	case DW_AT_return_addr:
	case DW_AT_data_member_location:
	case DW_AT_vtable_elem_location:
	case DW_AT_segment:
	case DW_AT_static_link:
	case DW_AT_use_location:
	case DW_AT_call_value:
	case DW_AT_GNU_call_site_value:
	case DW_AT_call_data_value:
	case DW_AT_GNU_call_site_data_value:
	case DW_AT_call_target:
	case DW_AT_GNU_call_site_target:
	case DW_AT_call_target_clobbered:
	case DW_AT_GNU_call_site_target_clobbered:
	  if ((dwarf_version < 4
	       && (form == DW_FORM_data4 || form == DW_FORM_data8))
	      || form == DW_FORM_sec_offset
	      || form == DW_FORM_loclistx)
	    {
	      /* Process location list.  */
	      unsigned int lmax = debug_info_p->max_loc_offsets;
	      unsigned int num = debug_info_p->num_loc_offsets;

	      if (lmax == 0 || num >= lmax)
		{
		  lmax += 1024;
		  debug_info_p->loc_offsets = (dwarf_vma *)
		    xcrealloc (debug_info_p->loc_offsets,
			       lmax, sizeof (*debug_info_p->loc_offsets));
		  debug_info_p->loc_views = (dwarf_vma *)
		    xcrealloc (debug_info_p->loc_views,
			       lmax, sizeof (*debug_info_p->loc_views));
		  debug_info_p->have_frame_base = (int *)
		    xcrealloc (debug_info_p->have_frame_base,
			       lmax, sizeof (*debug_info_p->have_frame_base));
		  debug_info_p->max_loc_offsets = lmax;
		}

	      if (form == DW_FORM_loclistx)
		uvalue = fetch_indexed_value (uvalue, loclists);
	      else if (this_set != NULL)
		uvalue += this_set->section_offsets [DW_SECT_LOC];

	      debug_info_p->have_frame_base [num] = have_frame_base;
	      if (attribute != DW_AT_GNU_locviews)
		{
		  uvalue += debug_info_p->loclists_base;

		  /* Corrupt DWARF info can produce more offsets than views.
		     See PR 23062 for an example.  */
		  if (debug_info_p->num_loc_offsets
		      > debug_info_p->num_loc_views)
		    warn (_("More location offset attributes than DW_AT_GNU_locview attributes\n"));
		  else
		    {
		      debug_info_p->loc_offsets [num] = uvalue;
		      debug_info_p->num_loc_offsets++;
		    }
		}
	      else
		{
		  assert (debug_info_p->num_loc_views <= num);
		  num = debug_info_p->num_loc_views;
		  if (num > debug_info_p->num_loc_offsets)
		    warn (_("More DW_AT_GNU_locview attributes than location offset attributes\n"));
		  else
		    {
		      debug_info_p->loc_views [num] = uvalue;
		      debug_info_p->num_loc_views++;
		    }
		}
	    }
	  break;

	case DW_AT_low_pc:
	  if (need_base_address)
	    debug_info_p->base_address = uvalue;
	  break;

	case DW_AT_GNU_addr_base:
	case DW_AT_addr_base:
	  debug_info_p->addr_base = uvalue;
	  break;

	case DW_AT_GNU_ranges_base:
	  debug_info_p->ranges_base = uvalue;
	  break;

	case DW_AT_ranges:
	  if ((dwarf_version < 4
	       && (form == DW_FORM_data4 || form == DW_FORM_data8))
	      || form == DW_FORM_sec_offset
	      || form == DW_FORM_rnglistx)
	    {
	      /* Process range list.  */
	      unsigned int lmax = debug_info_p->max_range_lists;
	      unsigned int num = debug_info_p->num_range_lists;

	      if (lmax == 0 || num >= lmax)
		{
		  lmax += 1024;
		  debug_info_p->range_lists = (dwarf_vma *)
		    xcrealloc (debug_info_p->range_lists,
			       lmax, sizeof (*debug_info_p->range_lists));
		  debug_info_p->max_range_lists = lmax;
		}

	      if (form == DW_FORM_rnglistx)
		uvalue = fetch_indexed_value (uvalue, rnglists);

	      debug_info_p->range_lists [num] = uvalue;
	      debug_info_p->num_range_lists++;
	    }
	  break;

	case DW_AT_GNU_dwo_name:
	case DW_AT_dwo_name:
	  if (need_dwo_info)
	    switch (form)
	      {
	      case DW_FORM_strp:
		add_dwo_name ((const char *) fetch_indirect_string (uvalue), cu_offset);
		break;
	      case DW_FORM_GNU_strp_alt:
		add_dwo_name ((const char *) fetch_alt_indirect_string (uvalue), cu_offset);
		break;
	      case DW_FORM_GNU_str_index:
	      case DW_FORM_strx:
	      case DW_FORM_strx1:
	      case DW_FORM_strx2:
	      case DW_FORM_strx3:
	      case DW_FORM_strx4:
		add_dwo_name (fetch_indexed_string (uvalue, this_set, offset_size, false,
		                                    debug_info_p->str_offsets_base),
			      cu_offset);
		break;
	      case DW_FORM_string:
		add_dwo_name ((const char *) orig_data, cu_offset);
		break;
	      default:
		warn (_("Unsupported form (%s) for attribute %s\n"),
		      get_FORM_name (form), get_AT_name (attribute));
		break;
	      }
	  break;

	case DW_AT_comp_dir:
	  /* FIXME: Also extract a build-id in a CU/TU.  */
	  if (need_dwo_info)
	    switch (form)
	      {
	      case DW_FORM_strp:
		add_dwo_dir ((const char *) fetch_indirect_string (uvalue), cu_offset);
		break;
	      case DW_FORM_GNU_strp_alt:
		add_dwo_dir (fetch_alt_indirect_string (uvalue), cu_offset);
		break;
	      case DW_FORM_line_strp:
		add_dwo_dir ((const char *) fetch_indirect_line_string (uvalue), cu_offset);
		break;
	      case DW_FORM_GNU_str_index:
	      case DW_FORM_strx:
	      case DW_FORM_strx1:
	      case DW_FORM_strx2:
	      case DW_FORM_strx3:
	      case DW_FORM_strx4:
		add_dwo_dir (fetch_indexed_string (uvalue, this_set, offset_size, false,
		                                   debug_info_p->str_offsets_base),
			     cu_offset);
		break;
	      case DW_FORM_string:
		add_dwo_dir ((const char *) orig_data, cu_offset);
		break;
	      default:
		warn (_("Unsupported form (%s) for attribute %s\n"),
		      get_FORM_name (form), get_AT_name (attribute));
		break;
	      }
	  break;

	case DW_AT_GNU_dwo_id:
	  if (need_dwo_info)
	    switch (form)
	      {
	      case DW_FORM_data8:
		/* FIXME: Record the length of the ID as well ?  */
		add_dwo_id ((const char *) (data - 8), cu_offset);
		break;
	      default:
		warn (_("Unsupported form (%s) for attribute %s\n"),
		      get_FORM_name (form), get_AT_name (attribute));
		break;
	      }
	  break;

	default:
	  break;
	}
    }

  if (do_loc || attribute == 0)
    return data;

  /* For some attributes we can display further information.  */
  switch (attribute)
    {
    case DW_AT_type:
      if (level >= 0 && level < MAX_CU_NESTING
	  && uvalue < (size_t) (end - start))
	{
	  bool is_signed = false;
	  abbrev_entry *type_abbrev;
	  unsigned char *type_data;
	  abbrev_map *map;

	  type_abbrev = get_type_abbrev_from_form (form, uvalue,
						   cu_offset, end,
						   section, NULL,
						   &type_data, &map);
	  if (type_abbrev != NULL)
	    {
	      get_type_signedness (type_abbrev, section, type_data,
				   map ? section->start + map->end : end,
				   map ? map->start : cu_offset,
				   pointer_size, offset_size, dwarf_version,
				   & is_signed, 0);
	    }
	  level_type_signed[level] = is_signed;
	}
      break;

    case DW_AT_inline:
      printf ("\t");
      switch (uvalue)
	{
	case DW_INL_not_inlined:
	  printf (_("(not inlined)"));
	  break;
	case DW_INL_inlined:
	  printf (_("(inlined)"));
	  break;
	case DW_INL_declared_not_inlined:
	  printf (_("(declared as inline but ignored)"));
	  break;
	case DW_INL_declared_inlined:
	  printf (_("(declared as inline and inlined)"));
	  break;
	default:
	  printf (_("  (Unknown inline attribute value: %s)"),
		  dwarf_vmatoa ("x", uvalue));
	  break;
	}
      break;

    case DW_AT_language:
      printf ("\t");
      switch (uvalue)
	{
	  /* Ordered by the numeric value of these constants.  */
	case DW_LANG_C89:		printf ("(ANSI C)"); break;
	case DW_LANG_C:			printf ("(non-ANSI C)"); break;
	case DW_LANG_Ada83:		printf ("(Ada)"); break;
	case DW_LANG_C_plus_plus:	printf ("(C++)"); break;
	case DW_LANG_Cobol74:		printf ("(Cobol 74)"); break;
	case DW_LANG_Cobol85:		printf ("(Cobol 85)"); break;
	case DW_LANG_Fortran77:		printf ("(FORTRAN 77)"); break;
	case DW_LANG_Fortran90:		printf ("(Fortran 90)"); break;
	case DW_LANG_Pascal83:		printf ("(ANSI Pascal)"); break;
	case DW_LANG_Modula2:		printf ("(Modula 2)"); break;
	  /* DWARF 2.1 values.	*/
	case DW_LANG_Java:		printf ("(Java)"); break;
	case DW_LANG_C99:		printf ("(ANSI C99)"); break;
	case DW_LANG_Ada95:		printf ("(ADA 95)"); break;
	case DW_LANG_Fortran95:		printf ("(Fortran 95)"); break;
	  /* DWARF 3 values.  */
	case DW_LANG_PLI:		printf ("(PLI)"); break;
	case DW_LANG_ObjC:		printf ("(Objective C)"); break;
	case DW_LANG_ObjC_plus_plus:	printf ("(Objective C++)"); break;
	case DW_LANG_UPC:		printf ("(Unified Parallel C)"); break;
	case DW_LANG_D:			printf ("(D)"); break;
	  /* DWARF 4 values.  */
	case DW_LANG_Python:		printf ("(Python)"); break;
	  /* DWARF 5 values.  */
	case DW_LANG_OpenCL:		printf ("(OpenCL)"); break;
	case DW_LANG_Go:		printf ("(Go)"); break;
	case DW_LANG_Modula3:		printf ("(Modula 3)"); break;
	case DW_LANG_Haskell:		printf ("(Haskell)"); break;
	case DW_LANG_C_plus_plus_03:	printf ("(C++03)"); break;
	case DW_LANG_C_plus_plus_11:	printf ("(C++11)"); break;
	case DW_LANG_OCaml:		printf ("(OCaml)"); break;
	case DW_LANG_Rust:		printf ("(Rust)"); break;
	case DW_LANG_C11:		printf ("(C11)"); break;
	case DW_LANG_Swift:		printf ("(Swift)"); break;
	case DW_LANG_Julia:		printf ("(Julia)"); break;
	case DW_LANG_Dylan:		printf ("(Dylan)"); break;
	case DW_LANG_C_plus_plus_14:	printf ("(C++14)"); break;
	case DW_LANG_Fortran03:		printf ("(Fortran 03)"); break;
	case DW_LANG_Fortran08:		printf ("(Fortran 08)"); break;
	case DW_LANG_RenderScript:	printf ("(RenderScript)"); break;
	  /* MIPS extension.  */
	case DW_LANG_Mips_Assembler:	printf ("(MIPS assembler)"); break;
	  /* UPC extension.  */
	case DW_LANG_Upc:		printf ("(Unified Parallel C)"); break;
	default:
	  if (uvalue >= DW_LANG_lo_user && uvalue <= DW_LANG_hi_user)
	    printf (_("(implementation defined: %s)"),
		    dwarf_vmatoa ("x", uvalue));
	  else
	    printf (_("(Unknown: %s)"), dwarf_vmatoa ("x", uvalue));
	  break;
	}
      break;

    case DW_AT_encoding:
      printf ("\t");
      switch (uvalue)
	{
	case DW_ATE_void:		printf ("(void)"); break;
	case DW_ATE_address:		printf ("(machine address)"); break;
	case DW_ATE_boolean:		printf ("(boolean)"); break;
	case DW_ATE_complex_float:	printf ("(complex float)"); break;
	case DW_ATE_float:		printf ("(float)"); break;
	case DW_ATE_signed:		printf ("(signed)"); break;
	case DW_ATE_signed_char:	printf ("(signed char)"); break;
	case DW_ATE_unsigned:		printf ("(unsigned)"); break;
	case DW_ATE_unsigned_char:	printf ("(unsigned char)"); break;
	  /* DWARF 2.1 values:  */
	case DW_ATE_imaginary_float:	printf ("(imaginary float)"); break;
	case DW_ATE_decimal_float:	printf ("(decimal float)"); break;
	  /* DWARF 3 values:  */
	case DW_ATE_packed_decimal:	printf ("(packed_decimal)"); break;
	case DW_ATE_numeric_string:	printf ("(numeric_string)"); break;
	case DW_ATE_edited:		printf ("(edited)"); break;
	case DW_ATE_signed_fixed:	printf ("(signed_fixed)"); break;
	case DW_ATE_unsigned_fixed:	printf ("(unsigned_fixed)"); break;
	  /* DWARF 4 values:  */
	case DW_ATE_UTF:		printf ("(unicode string)"); break;
	  /* DWARF 5 values:  */
	case DW_ATE_UCS:		printf ("(UCS)"); break;
	case DW_ATE_ASCII:		printf ("(ASCII)"); break;

	  /* HP extensions:  */
	case DW_ATE_HP_float80:		printf ("(HP_float80)"); break;
	case DW_ATE_HP_complex_float80:	printf ("(HP_complex_float80)"); break;
	case DW_ATE_HP_float128:	printf ("(HP_float128)"); break;
	case DW_ATE_HP_complex_float128:printf ("(HP_complex_float128)"); break;
	case DW_ATE_HP_floathpintel:	printf ("(HP_floathpintel)"); break;
	case DW_ATE_HP_imaginary_float80:	printf ("(HP_imaginary_float80)"); break;
	case DW_ATE_HP_imaginary_float128:	printf ("(HP_imaginary_float128)"); break;

	default:
	  if (uvalue >= DW_ATE_lo_user
	      && uvalue <= DW_ATE_hi_user)
	    printf (_("(user defined type)"));
	  else
	    printf (_("(unknown type)"));
	  break;
	}
      break;

    case DW_AT_accessibility:
      printf ("\t");
      switch (uvalue)
	{
	case DW_ACCESS_public:		printf ("(public)"); break;
	case DW_ACCESS_protected:	printf ("(protected)"); break;
	case DW_ACCESS_private:		printf ("(private)"); break;
	default:
	  printf (_("(unknown accessibility)"));
	  break;
	}
      break;

    case DW_AT_visibility:
      printf ("\t");
      switch (uvalue)
	{
	case DW_VIS_local:		printf ("(local)"); break;
	case DW_VIS_exported:		printf ("(exported)"); break;
	case DW_VIS_qualified:		printf ("(qualified)"); break;
	default:			printf (_("(unknown visibility)")); break;
	}
      break;

    case DW_AT_endianity:
      printf ("\t");
      switch (uvalue)
	{
	case DW_END_default:		printf ("(default)"); break;
	case DW_END_big:		printf ("(big)"); break;
	case DW_END_little:		printf ("(little)"); break;
	default:
	  if (uvalue >= DW_END_lo_user && uvalue <= DW_END_hi_user)
	    printf (_("(user specified)"));
	  else
	    printf (_("(unknown endianity)"));
	  break;
	}
      break;

    case DW_AT_virtuality:
      printf ("\t");
      switch (uvalue)
	{
	case DW_VIRTUALITY_none:	printf ("(none)"); break;
	case DW_VIRTUALITY_virtual:	printf ("(virtual)"); break;
	case DW_VIRTUALITY_pure_virtual:printf ("(pure_virtual)"); break;
	default:			printf (_("(unknown virtuality)")); break;
	}
      break;

    case DW_AT_identifier_case:
      printf ("\t");
      switch (uvalue)
	{
	case DW_ID_case_sensitive:	printf ("(case_sensitive)"); break;
	case DW_ID_up_case:		printf ("(up_case)"); break;
	case DW_ID_down_case:		printf ("(down_case)"); break;
	case DW_ID_case_insensitive:	printf ("(case_insensitive)"); break;
	default:			printf (_("(unknown case)")); break;
	}
      break;

    case DW_AT_calling_convention:
      printf ("\t");
      switch (uvalue)
	{
	case DW_CC_normal:	printf ("(normal)"); break;
	case DW_CC_program:	printf ("(program)"); break;
	case DW_CC_nocall:	printf ("(nocall)"); break;
	case DW_CC_pass_by_reference: printf ("(pass by ref)"); break;
	case DW_CC_pass_by_value: printf ("(pass by value)"); break;
	case DW_CC_GNU_renesas_sh: printf ("(Rensas SH)"); break;
	case DW_CC_GNU_borland_fastcall_i386: printf ("(Borland fastcall i386)"); break;
	default:
	  if (uvalue >= DW_CC_lo_user
	      && uvalue <= DW_CC_hi_user)
	    printf (_("(user defined)"));
	  else
	    printf (_("(unknown convention)"));
	}
      break;

    case DW_AT_ordering:
      printf ("\t");
      switch (uvalue)
	{
	case 255:
	case -1: printf (_("(undefined)")); break;
	case 0:  printf ("(row major)"); break;
	case 1:  printf ("(column major)"); break;
	}
      break;

    case DW_AT_decimal_sign:
      printf ("\t");
      switch (uvalue)
	{
	case DW_DS_unsigned:            printf (_("(unsigned)")); break;
	case DW_DS_leading_overpunch:   printf (_("(leading overpunch)")); break;
	case DW_DS_trailing_overpunch:  printf (_("(trailing overpunch)")); break;
	case DW_DS_leading_separate:    printf (_("(leading separate)")); break;
	case DW_DS_trailing_separate:   printf (_("(trailing separate)")); break;
	default:                        printf (_("(unrecognised)")); break;
	}
      break;

    case DW_AT_defaulted:
      printf ("\t");
      switch (uvalue)
	{
	case DW_DEFAULTED_no:           printf (_("(no)")); break;
	case DW_DEFAULTED_in_class:     printf (_("(in class)")); break;
	case DW_DEFAULTED_out_of_class: printf (_("(out of class)")); break;
	default:                        printf (_("(unrecognised)")); break;
	}
      break;

    case DW_AT_discr_list:
      printf ("\t");
      display_discr_list (form, uvalue, data, level);
      break;

    case DW_AT_frame_base:
      have_frame_base = 1;
      /* Fall through.  */
    case DW_AT_location:
    case DW_AT_loclists_base:
    case DW_AT_rnglists_base:
    case DW_AT_str_offsets_base:
    case DW_AT_string_length:
    case DW_AT_return_addr:
    case DW_AT_data_member_location:
    case DW_AT_vtable_elem_location:
    case DW_AT_segment:
    case DW_AT_static_link:
    case DW_AT_use_location:
    case DW_AT_call_value:
    case DW_AT_GNU_call_site_value:
    case DW_AT_call_data_value:
    case DW_AT_GNU_call_site_data_value:
    case DW_AT_call_target:
    case DW_AT_GNU_call_site_target:
    case DW_AT_call_target_clobbered:
    case DW_AT_GNU_call_site_target_clobbered:
      if ((dwarf_version < 4
	   && (form == DW_FORM_data4 || form == DW_FORM_data8))
	  || form == DW_FORM_sec_offset
	  || form == DW_FORM_loclistx)
	{
	  if (attribute != DW_AT_rnglists_base
	      && attribute != DW_AT_str_offsets_base)
	    printf (_(" (location list)"));
	}
      /* Fall through.  */
    case DW_AT_allocated:
    case DW_AT_associated:
    case DW_AT_data_location:
    case DW_AT_stride:
    case DW_AT_upper_bound:
    case DW_AT_lower_bound:
      if (block_start)
	{
	  int need_frame_base;

	  printf ("\t(");
	  need_frame_base = decode_location_expression (block_start,
							pointer_size,
							offset_size,
							dwarf_version,
							uvalue,
							cu_offset, section);
	  printf (")");
	  if (need_frame_base && !have_frame_base)
	    printf (_(" [without DW_AT_frame_base]"));
	}
      break;

    case DW_AT_data_bit_offset:
    case DW_AT_byte_size:
    case DW_AT_bit_size:
    case DW_AT_string_length_byte_size:
    case DW_AT_string_length_bit_size:
    case DW_AT_bit_stride:
      if (form == DW_FORM_exprloc)
	{
	  printf ("\t(");
	  (void) decode_location_expression (block_start, pointer_size,
					     offset_size, dwarf_version,
					     uvalue, cu_offset, section);
	  printf (")");
	}
      break;

    case DW_AT_import:
      {
	unsigned long abbrev_number;
	abbrev_entry *entry;

	entry = get_type_abbrev_from_form (form, uvalue, cu_offset, end,
					   section, & abbrev_number, NULL, NULL);
	if (entry == NULL)
	  {
	    if (form != DW_FORM_GNU_ref_alt)
	      warn (_("Offset %s used as value for DW_AT_import attribute of DIE at offset 0x%lx is too big.\n"),
		    dwarf_vmatoa ("x", uvalue),
		    (unsigned long) (orig_data - section->start));
	  }
	else
	  {
	    printf (_("\t[Abbrev Number: %ld"), abbrev_number);
	    printf (" (%s)", get_TAG_name (entry->tag));
	    printf ("]");
	  }
      }
      break;

    default:
      break;
    }

  return data;
}

static unsigned char *
read_and_display_attr (unsigned long           attribute,
		       unsigned long           form,
		       dwarf_signed_vma        implicit_const,
		       unsigned char *         start,
		       unsigned char *         data,
		       unsigned char *         end,
		       dwarf_vma               cu_offset,
		       dwarf_vma               pointer_size,
		       dwarf_vma               offset_size,
		       int                     dwarf_version,
		       debug_info *            debug_info_p,
		       int                     do_loc,
		       struct dwarf_section *  section,
		       cu_tu_set *      this_set,
		       int                     level)
{
  if (!do_loc)
    printf ("   %-18s:", get_AT_name (attribute));
  data = read_and_display_attr_value (attribute, form, implicit_const,
				      start, data, end,
				      cu_offset, pointer_size, offset_size,
				      dwarf_version, debug_info_p,
				      do_loc, section, this_set, ' ', level);
  if (!do_loc)
    printf ("\n");
  return data;
}

bool process_debug_info (struct dwarf_section * section,
		    void *file,
		    enum dwarf_section_display_enum abbrev_sec,
		    bool do_loc,
		    bool do_types)
{
  unsigned char *start = section->start;
  unsigned char *end = start + section->size;
  unsigned char *section_begin;
  unsigned int unit;
  unsigned int num_units = 0;

  /* First scan the section to get the number of comp units.
     Length sanity checks are done here.  */
  for (section_begin = start, num_units = 0; section_begin < end;
       num_units ++)
    {
      dwarf_vma length;

      /* Read the first 4 bytes.  For a 32-bit DWARF section, this
	 will be the length.  For a 64-bit DWARF section, it'll be
	 the escape code 0xffffffff followed by an 8 byte length.  */
      SAFE_BYTE_GET_AND_INC (length, section_begin, 4, end);

      if (length == 0xffffffff)
	SAFE_BYTE_GET_AND_INC (length, section_begin, 8, end);
      else if (length >= 0xfffffff0 && length < 0xffffffff)
	{
	  warn (_("Reserved length value (0x%s) found in section %s\n"),
		dwarf_vmatoa ("x", length), section->name);
	  return false;
	}

      /* Negative values are illegal, they may even cause infinite
	 looping.  This can happen if we can't accurately apply
	 relocations to an object file, or if the file is corrupt.  */
      if (length > (size_t) (end - section_begin))
	{
	  warn (_("Corrupt unit length (got 0x%s expected at most 0x%s) in section %s\n"),
		dwarf_vmatoa ("x", length),
		dwarf_vmatoa ("x", end - section_begin),
		section->name);
	  return false;
	}
      section_begin += length;
    }

  if (num_units == 0)
    {
      error (_("No comp units in %s section ?\n"), section->name);
      return false;
    }

  if ((do_loc || do_debug_loc || do_debug_ranges || do_debug_info)
      && num_debug_info_entries == 0
      && ! do_types)
    {

      /* Then allocate an array to hold the information.  */
      debug_information = (debug_info *) cmalloc (num_units,
						  sizeof (* debug_information));
      if (debug_information == NULL)
	{
	  error (_("Not enough memory for a debug info array of %u entries\n"),
		 num_units);
	  alloc_num_debug_info_entries = num_debug_info_entries = 0;
	  return false;
	}

      /* PR 17531: file: 92ca3797.
	 We cannot rely upon the debug_information array being initialised
	 before it is used.  A corrupt file could easily contain references
	 to a unit for which information has not been made available.  So
	 we ensure that the array is zeroed here.  */
      memset (debug_information, 0, num_units * sizeof (*debug_information));

      alloc_num_debug_info_entries = num_units;
    }

  if (!do_loc)
    {
      load_debug_section_with_follow (str, file);
      load_debug_section_with_follow (line_str, file);
      load_debug_section_with_follow (str_dwo, file);
      load_debug_section_with_follow (str_index, file);
      load_debug_section_with_follow (str_index_dwo, file);
      load_debug_section_with_follow (debug_addr, file);
    }

  load_debug_section_with_follow (abbrev_sec, file);
  load_debug_section_with_follow (loclists, file);
  load_debug_section_with_follow (rnglists, file);
  
  if (debug_displays [abbrev_sec].section.start == NULL)
    {
      warn (_("Unable to locate %s section!\n"),
	    debug_displays [abbrev_sec].section.uncompressed_name);
      return false;
    }

  if (!do_loc && dwarf_start_die == 0)
    introduce (section, false);

  free_all_abbrevs ();
  free (cu_abbrev_map);
  cu_abbrev_map = NULL;
  next_free_abbrev_map_entry = 0;

  /* In order to be able to resolve DW_FORM_ref_attr forms we need
     to load *all* of the abbrevs for all CUs in this .debug_info
     section.  This does effectively mean that we (partially) read
     every CU header twice.  */
  for (section_begin = start; start < end;)
    {
      DWARF2_Internal_CompUnit  compunit;
      unsigned char *           hdrptr;
      dwarf_vma                 abbrev_base;
      size_t                    abbrev_size;
      dwarf_vma                 cu_offset;
      unsigned int              offset_size;
      cu_tu_set *        this_set;
      abbrev_list *             list;
      unsigned char *end_cu;

      hdrptr = start;
      cu_offset = start - section_begin;

      SAFE_BYTE_GET_AND_INC (compunit.cu_length, hdrptr, 4, end);

      if (compunit.cu_length == 0xffffffff)
	{
	  SAFE_BYTE_GET_AND_INC (compunit.cu_length, hdrptr, 8, end);
	  offset_size = 8;
	}
      else
	offset_size = 4;
      end_cu = hdrptr + compunit.cu_length;

      SAFE_BYTE_GET_AND_INC (compunit.cu_version, hdrptr, 2, end_cu);

      this_set = find_cu_tu_set_v2 (cu_offset, do_types);

      if (compunit.cu_version < 5)
	{
	  compunit.cu_unit_type = DW_UT_compile;
	  /* Initialize it due to a false compiler warning.  */
	  compunit.cu_pointer_size = -1;
	}
      else
	{
	  SAFE_BYTE_GET_AND_INC (compunit.cu_unit_type, hdrptr, 1, end_cu);
	  do_types = (compunit.cu_unit_type == DW_UT_type);

	  SAFE_BYTE_GET_AND_INC (compunit.cu_pointer_size, hdrptr, 1, end_cu);
	}

      SAFE_BYTE_GET_AND_INC (compunit.cu_abbrev_offset, hdrptr, offset_size,
			     end_cu);

      if (compunit.cu_unit_type == DW_UT_split_compile
	  || compunit.cu_unit_type == DW_UT_skeleton)
	{
	  uint64_t dwo_id;
	  SAFE_BYTE_GET_AND_INC (dwo_id, hdrptr, 8, end_cu);
	}

      if (this_set == NULL)
	{
	  abbrev_base = 0;
	  abbrev_size = debug_displays [abbrev_sec].section.size;
	}
      else
	{
	  abbrev_base = this_set->section_offsets [DW_SECT_ABBREV];
	  abbrev_size = this_set->section_sizes [DW_SECT_ABBREV];
	}

      list = find_abbrev_list_by_abbrev_offset (abbrev_base,
						compunit.cu_abbrev_offset);
      if (list == NULL)
	{
	  unsigned char *  next;

	  list = new_abbrev_list (abbrev_base,
				  compunit.cu_abbrev_offset);
	  next = process_abbrev_set (&debug_displays[abbrev_sec].section,
				     abbrev_base, abbrev_size,
				     compunit.cu_abbrev_offset, list);
	  list->start_of_next_abbrevs = next;
	}

      start = end_cu;
      record_abbrev_list_for_cu (cu_offset, start - section_begin, list);
    }

  for (start = section_begin, unit = 0; start < end; unit++)
    {
      DWARF2_Internal_CompUnit compunit;
      unsigned char *hdrptr;
      unsigned char *tags;
      int level, last_level, saved_level;
      dwarf_vma cu_offset;
      unsigned int offset_size;
      dwarf_vma signature = 0;
      dwarf_vma type_offset = 0;
      cu_tu_set *this_set;
      dwarf_vma abbrev_base;
      size_t abbrev_size;
      abbrev_list * list = NULL;
      unsigned char *end_cu;

      hdrptr = start;
      cu_offset = start - section_begin;

      SAFE_BYTE_GET_AND_INC (compunit.cu_length, hdrptr, 4, end);

      if (compunit.cu_length == 0xffffffff)
	{
	  SAFE_BYTE_GET_AND_INC (compunit.cu_length, hdrptr, 8, end);
	  offset_size = 8;
	}
      else
	offset_size = 4;
      end_cu = hdrptr + compunit.cu_length;

      SAFE_BYTE_GET_AND_INC (compunit.cu_version, hdrptr, 2, end_cu);

      this_set = find_cu_tu_set_v2 (cu_offset, do_types);

      if (compunit.cu_version < 5)
	{
	  compunit.cu_unit_type = DW_UT_compile;
	  /* Initialize it due to a false compiler warning.  */
	  compunit.cu_pointer_size = -1;
	}
      else
	{
	  SAFE_BYTE_GET_AND_INC (compunit.cu_unit_type, hdrptr, 1, end_cu);
	  do_types = (compunit.cu_unit_type == DW_UT_type);

	  SAFE_BYTE_GET_AND_INC (compunit.cu_pointer_size, hdrptr, 1, end_cu);
	}

      SAFE_BYTE_GET_AND_INC (compunit.cu_abbrev_offset, hdrptr, offset_size, end_cu);

      if (this_set == NULL)
	{
	  abbrev_base = 0;
	  abbrev_size = debug_displays [abbrev_sec].section.size;
	}
      else
	{
	  abbrev_base = this_set->section_offsets [DW_SECT_ABBREV];
	  abbrev_size = this_set->section_sizes [DW_SECT_ABBREV];
	}

      if (compunit.cu_version < 5)
	SAFE_BYTE_GET_AND_INC (compunit.cu_pointer_size, hdrptr, 1, end_cu);

      bool do_dwo_id = false;
      uint64_t dwo_id = 0;
      if (compunit.cu_unit_type == DW_UT_split_compile
	  || compunit.cu_unit_type == DW_UT_skeleton)
	{
	  SAFE_BYTE_GET_AND_INC (dwo_id, hdrptr, 8, end_cu);
	  do_dwo_id = true;
	}

      /* PR 17512: file: 001-108546-0.001:0.1.  */
      if (compunit.cu_pointer_size < 2 || compunit.cu_pointer_size > 8)
	{
	  warn (_("Invalid pointer size (%d) in compunit header, using %d instead\n"),
		compunit.cu_pointer_size, offset_size);
	  compunit.cu_pointer_size = offset_size;
	}

      if (do_types)
	{
	  SAFE_BYTE_GET_AND_INC (signature, hdrptr, 8, end_cu);
	  SAFE_BYTE_GET_AND_INC (type_offset, hdrptr, offset_size, end_cu);
	}

      if (dwarf_start_die >= (size_t) (end_cu - section_begin))
	{
	  start = end_cu;
	  continue;
	}

      if ((do_loc || do_debug_loc || do_debug_ranges || do_debug_info)
	  && num_debug_info_entries == 0
	  && alloc_num_debug_info_entries > unit
	  && ! do_types)
	{
	  debug_information [unit].cu_offset = cu_offset;
	  debug_information [unit].pointer_size
	    = compunit.cu_pointer_size;
	  debug_information [unit].offset_size = offset_size;
	  debug_information [unit].dwarf_version = compunit.cu_version;
	  debug_information [unit].base_address = 0;
	  debug_information [unit].addr_base = DEBUG_INFO_UNAVAILABLE;
	  debug_information [unit].ranges_base = DEBUG_INFO_UNAVAILABLE;
	  debug_information [unit].loc_offsets = NULL;
	  debug_information [unit].have_frame_base = NULL;
	  debug_information [unit].max_loc_offsets = 0;
	  debug_information [unit].num_loc_offsets = 0;
	  debug_information [unit].loclists_base = 0;
	  debug_information [unit].range_lists = NULL;
	  debug_information [unit].max_range_lists= 0;
	  debug_information [unit].num_range_lists = 0;
	  debug_information [unit].rnglists_base = 0;
	  debug_information [unit].str_offsets_base = 0;
	}

      if (!do_loc && dwarf_start_die == 0)
	{
	  printf (_("  Compilation Unit @ offset 0x%s:\n"),
		  dwarf_vmatoa ("x", cu_offset));
	  printf (_("   Length:        0x%s (%s)\n"),
		  dwarf_vmatoa ("x", compunit.cu_length),
		  offset_size == 8 ? "64-bit" : "32-bit");
	  printf (_("   Version:       %d\n"), compunit.cu_version);
	  if (compunit.cu_version >= 5)
	    {
	      const char *name = get_DW_UT_name (compunit.cu_unit_type);

	      printf (_("   Unit Type:     %s (%x)\n"),
		      name ? name : "???",
		      compunit.cu_unit_type);
	    }
	  printf (_("   Abbrev Offset: 0x%s\n"),
		  dwarf_vmatoa ("x", compunit.cu_abbrev_offset));
	  printf (_("   Pointer Size:  %d\n"), compunit.cu_pointer_size);
	  if (do_types)
	    {
	      printf (_("   Signature:     0x%s\n"),
		      dwarf_vmatoa ("x", signature));
	      printf (_("   Type Offset:   0x%s\n"),
		      dwarf_vmatoa ("x", type_offset));
	    }
	  if (do_dwo_id)
	    printf (_("   DWO ID:        0x%s\n"), dwarf_vmatoa ("x", dwo_id));
	  if (this_set != NULL)
	    {
	      dwarf_vma *offsets = this_set->section_offsets;
	      size_t *sizes = this_set->section_sizes;

	      printf (_("   Section contributions:\n"));
	      printf (_("    .debug_abbrev.dwo:       0x%s  0x%s\n"),
		      dwarf_vmatoa ("x", offsets [DW_SECT_ABBREV]),
		      dwarf_vmatoa ("x", sizes [DW_SECT_ABBREV]));
	      printf (_("    .debug_line.dwo:         0x%s  0x%s\n"),
		      dwarf_vmatoa ("x", offsets [DW_SECT_LINE]),
		      dwarf_vmatoa ("x", sizes [DW_SECT_LINE]));
	      printf (_("    .debug_loc.dwo:          0x%s  0x%s\n"),
		      dwarf_vmatoa ("x", offsets [DW_SECT_LOC]),
		      dwarf_vmatoa ("x", sizes [DW_SECT_LOC]));
	      printf (_("    .debug_str_offsets.dwo:  0x%s  0x%s\n"),
		      dwarf_vmatoa ("x", offsets [DW_SECT_STR_OFFSETS]),
		      dwarf_vmatoa ("x", sizes [DW_SECT_STR_OFFSETS]));
	    }
	}

      tags = hdrptr;
      start = end_cu;

      if (compunit.cu_version < 2 || compunit.cu_version > 5)
	{
	  warn (_("CU at offset %s contains corrupt or "
		  "unsupported version number: %d.\n"),
		dwarf_vmatoa ("x", cu_offset), compunit.cu_version);
	  continue;
	}

      if (compunit.cu_unit_type != DW_UT_compile
	  && compunit.cu_unit_type != DW_UT_partial
	  && compunit.cu_unit_type != DW_UT_type
	  && compunit.cu_unit_type != DW_UT_split_compile
	  && compunit.cu_unit_type != DW_UT_skeleton)
	{
	  warn (_("CU at offset %s contains corrupt or "
		  "unsupported unit type: %d.\n"),
		dwarf_vmatoa ("x", cu_offset), compunit.cu_unit_type);
	  continue;
	}

      /* Process the abbrevs used by this compilation unit.  */
      list = find_abbrev_list_by_abbrev_offset (abbrev_base,
						compunit.cu_abbrev_offset);
      if (list == NULL)
	{
	  unsigned char *next;

	  list = new_abbrev_list (abbrev_base,
				  compunit.cu_abbrev_offset);
	  next = process_abbrev_set (&debug_displays[abbrev_sec].section,
				     abbrev_base, abbrev_size,
				     compunit.cu_abbrev_offset, list);
	  list->start_of_next_abbrevs = next;
	}

      level = 0;
      last_level = level;
      saved_level = -1;
      while (tags < start)
	{
	  unsigned long abbrev_number;
	  unsigned long die_offset;
	  abbrev_entry *entry;
	  abbrev_attr *attr;
	  int do_printing = 1;

	  die_offset = tags - section_begin;

	  READ_ULEB (abbrev_number, tags, start);

	  /* A null DIE marks the end of a list of siblings or it may also be
	     a section padding.  */
	  if (abbrev_number == 0)
	    {
	      /* Check if it can be a section padding for the last CU.  */
	      if (level == 0 && start == end)
		{
		  unsigned char *chk;

		  for (chk = tags; chk < start; chk++)
		    if (*chk != 0)
		      break;
		  if (chk == start)
		    break;
		}

	      if (!do_loc && die_offset >= dwarf_start_die
		  && (dwarf_cutoff_level == -1
		      || level < dwarf_cutoff_level))
		printf (_(" <%d><%lx>: Abbrev Number: 0\n"),
			level, die_offset);

	      --level;
	      if (level < 0)
		{
		  static unsigned num_bogus_warns = 0;

		  if (num_bogus_warns < 3)
		    {
		      warn (_("Bogus end-of-siblings marker detected at offset %lx in %s section\n"),
			    die_offset, section->name);
		      num_bogus_warns ++;
		      if (num_bogus_warns == 3)
			warn (_("Further warnings about bogus end-of-sibling markers suppressed\n"));
		    }
		}
	      if (dwarf_start_die != 0 && level < saved_level)
		return true;
	      continue;
	    }

	  if (!do_loc)
	    {
	      if (dwarf_start_die != 0 && die_offset < dwarf_start_die)
		do_printing = 0;
	      else
		{
		  if (dwarf_start_die != 0 && die_offset == dwarf_start_die)
		    saved_level = level;
		  do_printing = (dwarf_cutoff_level == -1
				 || level < dwarf_cutoff_level);
		  if (do_printing)
		    printf (_(" <%d><%lx>: Abbrev Number: %lu"),
			    level, die_offset, abbrev_number);
		  else if (dwarf_cutoff_level == -1
			   || last_level < dwarf_cutoff_level)
		    printf (_(" <%d><%lx>: ...\n"), level, die_offset);
		  last_level = level;
		}
	    }

	  /* Scan through the abbreviation list until we reach the
	     correct entry.  */
	  if (list == NULL)
	    continue;

	  for (entry = list->first_abbrev; entry != NULL; entry = entry->next)
	    if (entry->number == abbrev_number)
	      break;

	  if (entry == NULL)
	    {
	      if (!do_loc && do_printing)
		{
		  printf ("\n");
		  fflush (stdout);
		}
	      warn (_("DIE at offset 0x%lx refers to abbreviation number %lu which does not exist\n"),
		    die_offset, abbrev_number);
	      return false;
	    }

	  if (!do_loc && do_printing)
	    printf (" (%s)\n", get_TAG_name (entry->tag));

	  switch (entry->tag)
	    {
	    default:
	      need_base_address = 0;
	      break;
	    case DW_TAG_compile_unit:
	      need_base_address = 1;	
	      need_dwo_info = do_loc;
	      break;
	    case DW_TAG_entry_point:
	    case DW_TAG_subprogram:
	      need_base_address = 0;
	      /* Assuming that there is no DW_AT_frame_base.  */
	      have_frame_base = 0;
	      break;
	    }

	  debug_info *debug_info_p =
	    (debug_information && unit < alloc_num_debug_info_entries)
	    ? debug_information + unit : NULL;

	  assert (!debug_info_p
		  || (debug_info_p->num_loc_offsets
		      == debug_info_p->num_loc_views));

	  for (attr = entry->first_attr;
	       attr && attr->attribute;
	       attr = attr->next)
	    {
	      if (! do_loc && do_printing)
		/* Show the offset from where the tag was extracted.  */
		printf ("    <%lx>", (unsigned long)(tags - section_begin));
	      tags = read_and_display_attr (attr->attribute,
					    attr->form,
					    attr->implicit_const,
					    section_begin,
					    tags,
					    start,
					    cu_offset,
					    compunit.cu_pointer_size,
					    offset_size,
					    compunit.cu_version,
					    debug_info_p,
					    do_loc || ! do_printing,
					    section,
					    this_set,
					    level);
	    }

	  /* If a locview attribute appears before a location one,
	     make sure we don't associate it with an earlier
	     loclist. */
	  if (debug_info_p)
	    switch (debug_info_p->num_loc_offsets - debug_info_p->num_loc_views)
	      {
	      case 1:
		debug_info_p->loc_views [debug_info_p->num_loc_views] = vm1;
		debug_info_p->num_loc_views++;
		assert (debug_info_p->num_loc_views
			== debug_info_p->num_loc_offsets);
		break;

	      case 0:
		break;

	      case -1:
		warn(_("DIE has locviews without loclist\n"));
		debug_info_p->num_loc_views--;
		break;

	      default:
		assert (0);
	    }

	  if (entry->children)
	    ++level;
	}
    }

  /* Set num_debug_info_entries here so that it can be used to check if
     we need to process .debug_loc and .debug_ranges sections.  */
  if ((do_loc || do_debug_loc || do_debug_ranges || do_debug_info)
      && num_debug_info_entries == 0
      && ! do_types)
    {
      if (num_units > alloc_num_debug_info_entries)
	num_debug_info_entries = alloc_num_debug_info_entries;
      else
	num_debug_info_entries = num_units;
    }

  if (!do_loc)
    printf ("\n");

  return true;
}
