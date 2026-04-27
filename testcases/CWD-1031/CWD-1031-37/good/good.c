/* === Extracted Dependencies === */

#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Macros */
#define ATTRIBUTE_UNUSED __attribute__((unused))
#define FALSE 0
#define TRUE 1
#define BFD_VMA_FMT "l"
#define sprintf_vma(s, x) sprintf(s, "%016" BFD_VMA_FMT "x", x)
#define fprintf_vma(f, x) fprintf(f, "%016" BFD_VMA_FMT "x", x)
#define printf_vma(x) fprintf_vma(stdout, x)
#define bfd_printf_vma(abfd, x) bfd_fprintf_vma(abfd, stdout, x)
#define CONST_STRNEQ(STR1, STR2)                                               \
  (strncmp((STR1), (STR2), sizeof(STR2) - 1) == 0)
#define streq(a, b) (strcmp((a), (b)) == 0)
#define BFD_SEND(bfd, message, arglist) ((*((bfd)->xvec->message))arglist)
#define FOPEN_RB "rb"
#define bfd_get_section_name(bfd, ptr) ((void)bfd, (ptr)->name)
#define bfd_get_section_vma(bfd, ptr) ((void)bfd, (ptr)->vma)
#define bfd_get_filename(abfd) ((abfd)->filename)
#define bfd_big_endian(abfd) ((abfd)->xvec->byteorder == BFD_ENDIAN_BIG)
#define bfd_little_endian(abfd) ((abfd)->xvec->byteorder == BFD_ENDIAN_LITTLE)
#define bfd_get_section_size(sec) ((sec)->size)
#define bfd_get_symtab_upper_bound(abfd)                                       \
  BFD_SEND(abfd, _bfd_get_symtab_upper_bound, (abfd))
extern long _bfd_get_symtab_upper_bound(struct bfd *abfd);
#define bfd_canonicalize_symtab(abfd, location)                                \
  BFD_SEND(abfd, _bfd_canonicalize_symtab, (abfd, location))
#define obj_conv_table_size(abfd) ((abfd)->tdata.coff_obj_data->conv_table_size)
#define obj_convert(abfd) ((abfd)->tdata.coff_obj_data->convert)
#define CALC_ADDEND(abfd, ptr, reloc, cache_ptr) ((cache_ptr)->addend = 0)
#define RTYPE2HOWTO(cache_ptr, dst) ((cache_ptr)->howto = NULL)

/* Forward declarations */
typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef struct bfd_section *sec_ptr;
typedef struct bfd_symbol asymbol;
typedef const struct reloc_howto_struct reloc_howto_type;
typedef struct reloc_cache_entry arelent;
typedef struct relent_chain arelent_chain;
struct bfd_link_hash_entry;
struct bfd_link_hash_table;
struct bfd_arch_info;
struct bfd_build_id;
struct bfd_iovec;
struct relax_table;

struct bfd_hash_entry {
  struct bfd_hash_entry *next;
};

struct bfd_hash_table {
  struct bfd_hash_entry **table;
  unsigned int table_size;
  unsigned int count;
};

/* Basic types */
typedef int bfd_boolean;
typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;
typedef unsigned long bfd_size_type;
typedef unsigned long symvalue;
typedef long file_ptr;
typedef unsigned long ufile_ptr;
typedef unsigned int flagword;
typedef unsigned char bfd_byte;
typedef unsigned long symindex;

/* Enums */
enum bfd_endian { BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE, BFD_ENDIAN_UNKNOWN };

typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

typedef enum bfd_error {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_target,
  bfd_error_wrong_format,
  bfd_error_wrong_object_format,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_invalid_format,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_bad_value,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_on_input,
  bfd_error_invalid_error_code
} bfd_error_type;

enum dwarf_section_display_enum {
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
  separate_debug_str,
  max
};

typedef enum bfd_architecture {
  bfd_arch_unknown,
  bfd_arch_obscure,
  bfd_arch_m68k,
  bfd_arch_i386,
  bfd_arch_x86_64,
  bfd_arch_a29k,
  bfd_arch_avr,
  bfd_arch_cr16,
  bfd_arch_cris,
  bfd_arch_crx,
  bfd_arch_d10v,
  bfd_arch_d30v,
  bfd_arch_dlx,
  bfd_arch_epiphany,
  bfd_arch_fr30,
  bfd_arch_frv,
  bfd_arch_moxie,
  bfd_arch_h8300,
  bfd_arch_hppa,
  bfd_arch_hppa20w,
  bfd_arch_iamcu,
  bfd_arch_i960,
  bfd_arch_ip2k,
  bfd_arch_iq2000,
  bfd_arch_lm32,
  bfd_arch_m32c,
  bfd_arch_m32r,
  bfd_arch_m68hc11,
  bfd_arch_m68hc12,
  bfd_arch_m9s12x,
  bfd_arch_m9s12xg,
  bfd_arch_mcore,
  bfd_arch_mep,
  bfd_arch_metag,
  bfd_arch_microblaze,
  bfd_arch_mips,
  bfd_arch_mmix,
  bfd_arch_mn10200,
  bfd_arch_mn10300,
  bfd_arch_msp430,
  bfd_arch_mt,
  bfd_arch_nds32,
  bfd_arch_nios2,
  bfd_arch_ns32k,
  bfd_arch_or1k,
  bfd_arch_pdp11,
  bfd_arch_pj,
  bfd_arch_powerpc,
  bfd_arch_pru,
  bfd_arch_riscv,
  bfd_arch_rl78,
  bfd_arch_rx,
  bfd_arch_s390,
  bfd_arch_score,
  bfd_arch_sh,
  bfd_arch_sparc,
  bfd_arch_spu,
  bfd_arch_tic30,
  bfd_arch_tic4x,
  bfd_arch_tic54x,
  bfd_arch_tic6x,
  bfd_arch_tic80,
  bfd_arch_tilegx,
  bfd_arch_tilepro,
  bfd_arch_v850,
  bfd_arch_vax,
  bfd_arch_visium,
  bfd_arch_wasm32,
  bfd_arch_xgate,
  bfd_arch_xc16x,
  bfd_arch_xstormy16,
  bfd_arch_xtensa,
  bfd_arch_z80,
  bfd_arch_z8k,
  bfd_arch_aarch64,
  bfd_arch_bpf,
  bfd_arch_csky,
  bfd_arch_loongarch,
  bfd_arch_arc,
  bfd_arch_last
} bfd_architecture;

typedef enum bfd_direction {
  no_direction,
  read_direction,
  write_direction,
  both_direction,
  write_append
} bfd_direction;

typedef enum bfd_plugin_format {
  bfd_plugin_unknown,
  bfd_plugin_yes,
  bfd_plugin_no
} bfd_plugin_format;

typedef enum bfd_flavour {
  bfd_target_unknown_flavour,
  bfd_target_aout_flavour,
  bfd_target_coff_flavour,
  bfd_target_ecoff_flavour,
  bfd_target_xcoff_flavour,
  bfd_target_elf_flavour,
  bfd_target_ieee_flavour,
  bfd_target_nlm_flavour,
  bfd_target_oasys_flavour,
  bfd_target_tekhex_flavour,
  bfd_target_srec_flavour,
  bfd_target_verilog_flavour,
  bfd_target_ihex_flavour,
  bfd_target_som_flavour,
  bfd_target_os9k_flavour,
  bfd_target_versados_flavour,
  bfd_target_msdos_flavour,
  bfd_target_ovax_flavour,
  bfd_target_evax_flavour,
  bfd_target_mmo_flavour,
  bfd_target_mach_o_flavour,
  bfd_target_pef_flavour,
  bfd_target_pef_xlib_flavour,
  bfd_target_sym_flavour
} bfd_flavour;

enum bfd_link_order_type {
  bfd_undefined_link_order,
  bfd_indirect_link_order,
  bfd_data_link_order,
  bfd_section_reloc_link_order,
  bfd_symbol_reloc_link_order
};

/* Section flags */
#define SEC_NO_FLAGS 0x000
#define SEC_ALLOC 0x001
#define SEC_LOAD 0x002
#define SEC_RELOC 0x004
#define SEC_READONLY 0x008
#define SEC_CODE 0x010
#define SEC_DATA 0x020
#define SEC_ROM 0x040
#define SEC_CONSTRUCTOR 0x080
#define SEC_HAS_CONTENTS 0x100

#define BFD_NO_FLAGS 0x00
#define HAS_RELOC 0x01
#define EXEC_P 0x02
#define HAS_LINENO 0x04
#define HAS_DEBUG 0x08
#define HAS_SYMS 0x10
#define HAS_LOCALS 0x20
#define DYNAMIC 0x40

/* Architecture constants */
#define bfd_arch_i386 bfd_arch_i386
#define bfd_arch_iamcu bfd_arch_iamcu
#define bfd_arch_aarch64 bfd_arch_aarch64
#define bfd_arch_s390 bfd_arch_s390

#define bfd_mach_x86_64 64
#define bfd_mach_x86_64_intel_syntax 65
#define bfd_mach_x86_64_nacl 66
#define bfd_mach_x64_32 67
#define bfd_mach_x64_32_intel_syntax 68
#define bfd_mach_x64_32_nacl 69

/* Dwarf types */
typedef unsigned long dwarf_vma;
typedef unsigned int dwarf_size_type;

struct dwarf_section {
  const char *uncompressed_name;
  const char *compressed_name;
  const char *name;
  const char *filename;
  unsigned char *start;
  dwarf_vma address;
  dwarf_size_type size;
  enum dwarf_section_display_enum abbrev_sec;
  void *reloc_info;
  unsigned long num_relocs;
  void *user_data;
};

typedef int (*dwarf_display_func)(struct dwarf_section *, void *);

struct dwarf_section_display {
  struct dwarf_section section;
  dwarf_display_func display;
  int *enabled;
  int relocate;
};

/* COFF types */
struct external_reloc {
  char r_vaddr[4];
  char r_symndx[4];
  char r_type[2];
};

#define RELOC struct external_reloc

struct internal_reloc {
  bfd_vma r_vaddr;
  long r_symndx;
  unsigned short r_type;
  unsigned char r_size;
  unsigned char r_extern;
  unsigned long r_offset;
};

/* Relocation cache entry */
struct reloc_cache_entry {
  struct bfd_symbol **sym_ptr_ptr;
  bfd_size_type address;
  bfd_vma addend;
  struct reloc_howto_struct *howto;
};

struct relent_chain {
  arelent relent;
  struct relent_chain *next;
};

/* Link order */
struct bfd_link_order {
  struct bfd_link_order *next;
  enum bfd_link_order_type type;
  bfd_vma offset;
  bfd_size_type size;
  union {
    struct {
      asection *section;
    } indirect;
    struct {
      bfd_size_type size;
      bfd_byte *contents;
    } data;
  } u;
};

/* Link info (must come before callbacks) */
struct bfd_link_info {
  bfd *output_bfd;
  bfd *input_bfds;
  struct bfd **input_bfds_tail;
  struct bfd_link_hash_table *hash;
  struct bfd_link_callbacks *callbacks;
};

/* Link callbacks */
struct bfd_link_callbacks {
  void (*add_archive_element)(struct bfd_link_info *info, bfd *abfd);
  void (*multiple_definition)(struct bfd_link_info *info,
                              struct bfd_link_hash_entry *h, bfd *nbfd,
                              asection *nsec, bfd_vma nval);
  void (*multiple_common)(struct bfd_link_info *info, const char *name,
                          bfd *abfd, asection *nsec, bfd_vma nval);
  void (*add_to_set)(struct bfd_link_info *info, struct bfd_link_hash_entry *h,
                     bfd *abfd, asection *nsec, bfd_vma nval);
  void (*constructor)(struct bfd_link_info *info, const char *name, bfd *abfd,
                      asection *nsec, bfd_vma nval);
  void (*warning)(struct bfd_link_info *info, const char *warning,
                  const char *symbol, bfd *abfd, asection *section,
                  bfd_vma address);
  void (*undefined_symbol)(struct bfd_link_info *info, const char *name,
                           bfd *abfd, asection *section, bfd_vma address,
                           bfd_boolean fatal);
  void (*reloc_overflow)(struct bfd_link_info *info,
                         struct bfd_link_hash_entry *entry, const char *name,
                         const char *reloc_name, bfd_vma addend, bfd *abfd,
                         asection *section, bfd_vma address);
  void (*reloc_dangerous)(struct bfd_link_info *info, const char *message,
                          bfd *abfd, asection *section, bfd_vma address);
  void (*unattached_reloc)(struct bfd_link_info *info, const char *name,
                           bfd *abfd, asection *section, bfd_vma address);
  void (*notice)(struct bfd_link_info *info, struct bfd_link_hash_entry *h,
                 bfd *abfd, asection *section, bfd_vma address);
  void (*einfo)(const char *fmt, ...);
  void (*info)(const char *fmt, ...);
  void (*minfo)(const char *fmt, ...);
};

/* Saved offsets */
struct saved_output_info {
  bfd_vma offset;
  asection *section;
};

struct saved_offsets {
  unsigned int section_count;
  struct saved_output_info *sections;
};

/* Section structure */
struct bfd_section {
  const char *name;
  unsigned int id;
  unsigned int index;
  struct bfd_section *next;
  struct bfd_section *prev;
  flagword flags;
  unsigned int user_set_vma : 1;
  unsigned int linker_mark : 1;
  unsigned int linker_has_input : 1;
  unsigned int gc_mark : 1;
  unsigned int compress_status : 2;
  unsigned int segment_mark : 1;
  unsigned int sec_info_type : 3;
  unsigned int use_rela_p : 1;
  unsigned int sec_flg0 : 1;
  unsigned int sec_flg1 : 1;
  unsigned int sec_flg2 : 1;
  unsigned int sec_flg3 : 1;
  unsigned int sec_flg4 : 1;
  unsigned int sec_flg5 : 1;
  bfd_vma vma;
  bfd_vma lma;
  bfd_size_type size;
  bfd_size_type rawsize;
  bfd_size_type compressed_size;
  struct relax_table *relax;
  int relax_count;
  bfd_vma output_offset;
  struct bfd_section *output_section;
  unsigned int alignment_power;
  struct reloc_cache_entry *relocation;
  struct reloc_cache_entry **orelocation;
  unsigned reloc_count;
  file_ptr filepos;
  file_ptr rel_filepos;
  file_ptr line_filepos;
  void *userdata;
  unsigned char *contents;
  struct relent_chain *constructor_chain;
  bfd *owner;
  struct bfd_symbol *symbol;
  struct bfd_symbol **symbol_ptr_ptr;
  union {
    struct bfd_link_order *link_order;
    struct bfd_section *s;
  } map_head, map_tail;
};

/* Symbol structure */
struct bfd_symbol {
  struct bfd *the_bfd;
  const char *name;
  symvalue value;
  flagword flags;
  asection *section;
  union {
    void *p;
    bfd_vma i;
  } udata;
  struct bfd_symbol **symbol_ptr_ptr;
};

/* COFF tdata */
struct coff_tdata {
  void *conv_table;
  unsigned int conv_table_size;
  long *convert;
};

struct bfd_target {
  const char *name;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  long (*_get_reloc_upper_bound)(bfd *, sec_ptr);
  long (*_bfd_canonicalize_reloc)(bfd *, sec_ptr, arelent **,
                                  struct bfd_symbol **);
  long (*_bfd_get_symtab_upper_bound)(bfd *);
  long (*_bfd_canonicalize_symtab)(bfd *, struct bfd_symbol **);
};

/* Main BFD structure */
struct bfd {
  const char *filename;
  const struct bfd_target *xvec;
  void *iostream;
  const struct bfd_iovec *iovec;
  struct bfd *lru_prev, *lru_next;
  ufile_ptr where;
  long mtime;
  unsigned int id;
  enum bfd_format format : 3;
  enum bfd_direction direction : 2;
  flagword flags : 20;
  unsigned int cacheable : 1;
  unsigned int target_defaulted : 1;
  unsigned int opened_once : 1;
  unsigned int mtime_set : 1;
  unsigned int no_export : 1;
  unsigned int output_has_begun : 1;
  unsigned int has_armap : 1;
  unsigned int is_thin_archive : 1;
  unsigned int selective_search : 1;
  unsigned int is_linker_output : 1;
  unsigned int is_linker_input : 1;
  enum bfd_plugin_format plugin_format : 2;
  unsigned int lto_output : 1;
  bfd *plugin_dummy_bfd;
  ufile_ptr origin;
  ufile_ptr proxy_origin;
  struct bfd_hash_table section_htab;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  int archive_pass;
  bfd_vma start_address;
  struct bfd_symbol **outsymbols;
  unsigned int symcount;
  unsigned int dynsymcount;
  const struct bfd_arch_info *arch_info;
  void *arelt_data;
  struct bfd *my_archive;
  struct bfd *archive_next;
  struct bfd *archive_head;
  struct bfd *nested_archives;
  union {
    struct bfd *next;
    struct bfd_link_hash_table *hash;
  } link;
  union {
    struct coff_tdata *coff_obj_data;
    void *any;
  } tdata;
  void *usrdata;
  void *memory;
  const struct bfd_build_id *build_id;
};

/* Target match structure */
struct targmatch {
  const char *triplet;
  const struct bfd_target *vector;
};

/* Variables */
extern struct dwarf_section_display debug_displays[];
extern bfd_boolean is_relocatable;
extern int eh_addr_size;
extern bfd_byte *(*byte_get)(unsigned char *, int);
extern bfd_byte *byte_get_big_endian(unsigned char *, int);
extern bfd_byte *byte_get_little_endian(unsigned char *, int);
extern int dump_dwarf_section_info;
extern const struct targmatch bfd_target_match[];
extern const struct bfd_target arm_coff_be_vec;
extern const struct bfd_target arm_coff_le_vec;
extern const struct bfd_target arm_elf32_be_vec;
extern const struct bfd_target arm_elf32_le_vec;
extern const struct bfd_target i386_aout_vec;
extern const struct bfd_target i386_aout_bsd_vec;
extern const struct bfd_target i386_aout_nbsd_vec;
extern const struct bfd_target i386_aout_os9k_vec;
extern const struct bfd_target *const *bfd_target_vector;
extern const struct bfd_target *const *bfd_default_vector;
extern asymbol *bfd_abs_section_ptr;

/* Function Declarations */
extern bfd_boolean coff_slurp_symbol_table(bfd *abfd);
extern void *buy_and_read(bfd *abfd, file_ptr offset, bfd_size_type size);
extern void coff_swap_reloc_in(bfd *abfd, void *src,
                               struct internal_reloc *dst);
extern void _bfd_error_handler(const char *fmt, ...);
extern void bfd_set_error(bfd_error_type error_tag);
extern struct bfd_link_hash_table *
_bfd_generic_link_hash_table_create(bfd *abfd);
extern void _bfd_generic_link_hash_table_free(bfd *abfd);
extern bfd_boolean _bfd_generic_link_add_symbols(bfd *abfd,
                                                 struct bfd_link_info *info);
extern bfd_byte *
bfd_get_relocated_section_contents(bfd *abfd, struct bfd_link_info *link_info,
                                   struct bfd_link_order *link_order,
                                   bfd_byte *data, bfd_boolean relocatable,
                                   struct bfd_symbol **symbols);
extern void *bfd_malloc(bfd_size_type size);
extern void *bfd_alloc(bfd *abfd, bfd_size_type size);
extern void free_debug_section(enum dwarf_section_display_enum debug);
extern void bfd_cache_section_contents(asection *sec, bfd_byte *contents);
extern long bfd_get_reloc_upper_bound(bfd *abfd, asection *asect);
extern bfd *_bfd_new_bfd(void);
extern void _bfd_delete_bfd(bfd *abfd);
extern bfd_boolean bfd_cache_init(bfd *abfd);
extern char *xstrdup(const char *s);
extern void *_bfd_real_fopen(const char *filename, const char *modes);
extern bfd_boolean bfd_set_cacheable(bfd *abfd, bfd_boolean cacheable);
extern bfd_boolean bfd_get_full_section_contents(bfd *abfd, asection *section,
                                                 bfd_byte **pdata);
extern long bfd_canonicalize_reloc(bfd *abfd, sec_ptr asect, arelent **location,
                                   asymbol **symbols);
extern bfd_byte *bfd_simple_get_relocated_section_contents(
    bfd *abfd, asection *sec, bfd_byte *outbuf, asymbol **symbol_table);
extern void bfd_map_over_sections(bfd *abfd,
                                  void (*operation)(bfd *, asection *, void *),
                                  void *user_storage);
extern void simple_save_output_info(bfd *abfd, asection *section, void *arg);
extern void simple_restore_output_info(bfd *abfd, asection *section, void *arg);
extern bfd *load_separate_debug_file(bfd *abfd, const char *filename);
extern void free_debug_memory(void);
extern bfd_boolean bfd_check_format_matches(bfd *abfd, bfd_format format,
                                            char ***matching);
extern asymbol **slurp_symtab(bfd *abfd);
extern int bfd_arch_bits_per_address(bfd *abfd);
extern enum bfd_architecture bfd_get_arch(bfd *abfd);
extern unsigned long bfd_get_mach(bfd *abfd);
extern void init_dwarf_regnames_x86_64(void);
extern void init_dwarf_regnames_i386(void);
extern void init_dwarf_regnames_iamcu(void);
extern void init_dwarf_regnames_aarch64(void);
extern void init_dwarf_regnames_s390(void);
extern void warn(const char *fmt, ...);
extern const char *_(const char *msgid);
extern void *xmalloc(size_t size);
extern long bfd_coff_relsz(bfd *abfd);
extern long coff_get_reloc_upper_bound(bfd *, sec_ptr);
extern long coff_canonicalize_symtab(bfd *abfd, asymbol **alocation);
extern void bfd_fprintf_vma(bfd *abfd, void *stream, bfd_vma vma);
extern long coff_get_symtab_upper_bound(bfd *abfd);
extern void simple_dummy_warning(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    const char *warning ATTRIBUTE_UNUSED, const char *symbol ATTRIBUTE_UNUSED,
    bfd *abfd ATTRIBUTE_UNUSED, asection *section ATTRIBUTE_UNUSED,
    bfd_vma address ATTRIBUTE_UNUSED);
extern void simple_dummy_undefined_symbol(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    const char *name ATTRIBUTE_UNUSED, bfd *abfd ATTRIBUTE_UNUSED,
    asection *section ATTRIBUTE_UNUSED, bfd_vma address ATTRIBUTE_UNUSED,
    bfd_boolean fatal ATTRIBUTE_UNUSED);
extern void simple_dummy_reloc_overflow(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    struct bfd_link_hash_entry *entry ATTRIBUTE_UNUSED,
    const char *name ATTRIBUTE_UNUSED, const char *reloc_name ATTRIBUTE_UNUSED,
    bfd_vma addend ATTRIBUTE_UNUSED, bfd *abfd ATTRIBUTE_UNUSED,
    asection *section ATTRIBUTE_UNUSED, bfd_vma address ATTRIBUTE_UNUSED);
extern void simple_dummy_reloc_dangerous(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    const char *message ATTRIBUTE_UNUSED, bfd *abfd ATTRIBUTE_UNUSED,
    asection *section ATTRIBUTE_UNUSED, bfd_vma address ATTRIBUTE_UNUSED);
extern void simple_dummy_unattached_reloc(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    const char *name ATTRIBUTE_UNUSED, bfd *abfd ATTRIBUTE_UNUSED,
    asection *section ATTRIBUTE_UNUSED, bfd_vma address ATTRIBUTE_UNUSED);
extern void simple_dummy_multiple_definition(
    struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
    struct bfd_link_hash_entry *h ATTRIBUTE_UNUSED, bfd *nbfd ATTRIBUTE_UNUSED,
    asection *nsec ATTRIBUTE_UNUSED, bfd_vma nval ATTRIBUTE_UNUSED);
extern void simple_dummy_einfo(const char *fmt ATTRIBUTE_UNUSED, ...);

static asymbol **syms;

static bfd_boolean coff_slurp_reloc_table(bfd *abfd, sec_ptr asect,
                                          asymbol **symbols) {
  RELOC *native_relocs;
  arelent *reloc_cache;
  arelent *cache_ptr;
  unsigned int idx;
  bfd_size_type amt;

  if (asect->relocation)
    return TRUE;
  if (asect->reloc_count == 0)
    return TRUE;
  if (asect->flags & SEC_CONSTRUCTOR)
    return TRUE;
  if (!coff_slurp_symbol_table(abfd))
    return FALSE;

  amt = (bfd_size_type)bfd_coff_relsz(abfd) * asect->reloc_count;
  native_relocs = (RELOC *)buy_and_read(abfd, asect->rel_filepos, amt);
  amt = (bfd_size_type)asect->reloc_count * sizeof(arelent);
  reloc_cache = (arelent *)bfd_alloc(abfd, amt);

  if (reloc_cache == NULL || native_relocs == NULL)
    return FALSE;

  for (idx = 0; idx < asect->reloc_count; idx++) {
    struct internal_reloc dst;
    struct external_reloc *src;
#ifndef RELOC_PROCESSING
    asymbol *ptr;
#endif

    cache_ptr = reloc_cache + idx;
    src = native_relocs + idx;

    dst.r_offset = 0;
    coff_swap_reloc_in(abfd, src, &dst);

#ifdef RELOC_PROCESSING
    RELOC_PROCESSING(cache_ptr, &dst, symbols, abfd, asect);
#else
    cache_ptr->address = dst.r_vaddr;

    if (dst.r_symndx != -1 && symbols != NULL) {
      if (dst.r_symndx < 0 || dst.r_symndx >= obj_conv_table_size(abfd)) {
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%B: warning: illegal symbol index %ld in relocs"), abfd,
             dst.r_symndx);
        cache_ptr->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;
        ptr = NULL;
      } else {
        cache_ptr->sym_ptr_ptr = (symbols + obj_convert(abfd)[dst.r_symndx]);
        ptr = *(cache_ptr->sym_ptr_ptr);
      }
    } else {
      cache_ptr->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;
      ptr = NULL;
    }

    /* The symbols definitions that we have read in have been
       relocated as if their sections started at 0. But the offsets
       refering to the symbols in the raw data have not been
       modified, so we have to have a negative addend to compensate.

       Note that symbols which used to be common must be left alone.  */

    /* Calculate any reloc addend by looking at the symbol.  */
    CALC_ADDEND(abfd, ptr, dst, cache_ptr);
    (void)ptr;

    cache_ptr->address -= asect->vma;
    /* !! cache_ptr->section = NULL;*/

    /* Fill in the cache_ptr->howto field from dst.r_type.  */
    RTYPE2HOWTO(cache_ptr, &dst);
#endif /* RELOC_PROCESSING */

    if (cache_ptr->howto == NULL) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%B: illegal relocation type %d at address %#Lx"), abfd,
           dst.r_type, dst.r_vaddr);
      bfd_set_error(bfd_error_bad_value);
      return FALSE;
    }
  }

  asect->relocation = reloc_cache;
  return TRUE;
}

static long coff_canonicalize_reloc(bfd *abfd, sec_ptr section,
                                    arelent **relptr, asymbol **symbols) {
  arelent *tblptr = section->relocation;
  unsigned int count = 0;

  if (section->flags & SEC_CONSTRUCTOR) {
    /* This section has relocs made up by us, they are not in the
       file, so take them out of their chain and place them into
       the data area provided.  */
    arelent_chain *chain = section->constructor_chain;

    for (count = 0; count < section->reloc_count; count++) {
      *relptr++ = &chain->relent;
      chain = chain->next;
    }
  } else {
    if (!coff_slurp_reloc_table(abfd, section, symbols))
      return -1;

    tblptr = section->relocation;

    for (; count++ < section->reloc_count;)
      *relptr++ = tblptr++;
  }
  *relptr = 0;
  return section->reloc_count;
}

long bfd_canonicalize_reloc(bfd *abfd, sec_ptr asect, arelent **location,
                            asymbol **symbols) {
  if (abfd->format != bfd_object) {
    bfd_set_error(bfd_error_invalid_operation);
    return -1;
  }

  return BFD_SEND(abfd, _bfd_canonicalize_reloc,
                  (abfd, asect, location, symbols));
}

bfd_byte *bfd_simple_get_relocated_section_contents(bfd *abfd, asection *sec,
                                                    bfd_byte *outbuf,
                                                    asymbol **symbol_table) {
  struct bfd_link_info link_info;
  struct bfd_link_order link_order;
  struct bfd_link_callbacks callbacks;
  bfd_byte *contents, *data;
  int storage_needed;
  struct saved_offsets saved_offsets;
  bfd *link_next;

  /* Don't apply relocation on executable and shared library.  See
     PR 4756.  */
  if ((abfd->flags & (HAS_RELOC | EXEC_P | DYNAMIC)) != HAS_RELOC ||
      !(sec->flags & SEC_RELOC)) {
    contents = outbuf;
    if (!bfd_get_full_section_contents(abfd, sec, &contents))
      return NULL;
    return contents;
  }

  /* In order to use bfd_get_relocated_section_contents, we need
     to forge some data structures that it expects.  */

  /* Fill in the bare minimum number of fields for our purposes.  */
  memset(&link_info, 0, sizeof(link_info));
  link_info.output_bfd = abfd;
  link_info.input_bfds = abfd;
  link_info.input_bfds_tail = &abfd->link.next;

  link_next = abfd->link.next;
  abfd->link.next = NULL;
  link_info.hash = _bfd_generic_link_hash_table_create(abfd);
  link_info.callbacks = &callbacks;
  callbacks.warning = simple_dummy_warning;
  callbacks.undefined_symbol = simple_dummy_undefined_symbol;
  callbacks.reloc_overflow = simple_dummy_reloc_overflow;
  callbacks.reloc_dangerous = simple_dummy_reloc_dangerous;
  callbacks.unattached_reloc = simple_dummy_unattached_reloc;
  callbacks.multiple_definition = simple_dummy_multiple_definition;
  callbacks.einfo = simple_dummy_einfo;

  memset(&link_order, 0, sizeof(link_order));
  link_order.next = NULL;
  link_order.type = bfd_indirect_link_order;
  link_order.offset = 0;
  link_order.size = sec->size;
  link_order.u.indirect.section = sec;

  data = NULL;
  if (outbuf == NULL) {
    bfd_size_type amt = sec->rawsize > sec->size ? sec->rawsize : sec->size;
    data = (bfd_byte *)bfd_malloc(amt);
    if (data == NULL) {
      _bfd_generic_link_hash_table_free(abfd);
      abfd->link.next = link_next;
      return NULL;
    }
    outbuf = data;
  }

  saved_offsets.section_count = abfd->section_count;
  saved_offsets.sections =
      malloc(sizeof(*saved_offsets.sections) * saved_offsets.section_count);
  if (saved_offsets.sections == NULL) {
    if (data)
      free(data);
    _bfd_generic_link_hash_table_free(abfd);
    abfd->link.next = link_next;
    return NULL;
  }
  bfd_map_over_sections(abfd, simple_save_output_info, &saved_offsets);

  if (symbol_table == NULL) {
    _bfd_generic_link_add_symbols(abfd, &link_info);

    storage_needed = bfd_get_symtab_upper_bound(abfd);
    symbol_table = (asymbol **)bfd_malloc(storage_needed);
    bfd_canonicalize_symtab(abfd, symbol_table);
  } else
    storage_needed = 0;

  contents = bfd_get_relocated_section_contents(abfd, &link_info, &link_order,
                                                outbuf, 0, symbol_table);
  if (contents == NULL && data != NULL)
    free(data);

  bfd_map_over_sections(abfd, simple_restore_output_info, &saved_offsets);
  free(saved_offsets.sections);

  _bfd_generic_link_hash_table_free(abfd);
  abfd->link.next = link_next;
  return contents;
}

static bfd_boolean
load_specific_debug_section(enum dwarf_section_display_enum debug,
                            asection *sec, void *file) {
  struct dwarf_section *section = &debug_displays[debug].section;
  bfd *abfd = (bfd *)file;
  bfd_byte *contents;

  if (section->start != NULL) {
    /* If it is already loaded, do nothing.  */
    if (streq(section->filename, bfd_get_filename(abfd)))
      return TRUE;
    free(section->start);
  }

  section->filename = bfd_get_filename(abfd);
  section->reloc_info = NULL;
  section->num_relocs = 0;
  section->address = bfd_get_section_vma(abfd, sec);
  section->size = bfd_get_section_size(sec);
  section->start = contents = malloc(section->size + 1);
  section->user_data = sec;
  if (section->start == NULL ||
      !bfd_get_full_section_contents(abfd, sec, &contents)) {
    free_debug_section(debug);
    printf(_("\nCan't get contents for section '%s'.\n"), section->name);
    return FALSE;
  }
  /* Ensure any string section has a terminating NUL.  */
  section->start[section->size] = 0;

  if (is_relocatable && debug_displays[debug].relocate) {
    long reloc_size;
    bfd_boolean ret;

    bfd_cache_section_contents(sec, section->start);

    ret = bfd_simple_get_relocated_section_contents(abfd, sec, section->start,
                                                    syms) != NULL;

    if (!ret) {
      free_debug_section(debug);
      printf(_("\nCan't get contents for section '%s'.\n"), section->name);
      return FALSE;
    }

    reloc_size = bfd_get_reloc_upper_bound(abfd, sec);
    if (reloc_size > 0) {
      unsigned long reloc_count;
      arelent **relocs;

      relocs = (arelent **)xmalloc(reloc_size);

      reloc_count = bfd_canonicalize_reloc(abfd, sec, relocs, NULL);
      if (reloc_count == 0)
        free(relocs);
      else {
        section->reloc_info = relocs;
        section->num_relocs = reloc_count;
      }
    }
  }

  return TRUE;
}

/* struct bfd_target already defined in dependencies section above */
typedef struct bfd_target bfd_target;

#define BFD_JUMP_TABLE_RELOCS(NAME)                                            \
  NAME##_get_reloc_upper_bound, NAME##_canonicalize_reloc

#define BFD_JUMP_TABLE_SYMBOLS(NAME)                                           \
  NAME##_get_symtab_upper_bound, NAME##_canonicalize_symtab

const bfd_target i386_coff_vec = {
    "coff-i386", BFD_ENDIAN_LITTLE, BFD_ENDIAN_LITTLE,
    BFD_JUMP_TABLE_RELOCS(coff), BFD_JUMP_TABLE_SYMBOLS(coff)};

static const bfd_target *const _bfd_target_vector[] = {
    &arm_coff_be_vec,    &arm_coff_le_vec,
    &arm_elf32_be_vec,   &arm_elf32_le_vec,
    &i386_aout_vec,      &i386_aout_bsd_vec,
    &i386_aout_nbsd_vec, &i386_aout_os9k_vec,
    &i386_coff_vec,      NULL /* end of list marker */
};

const bfd_target *const *bfd_target_vector = _bfd_target_vector;

static const bfd_target *find_target(const char *name) {
  const bfd_target *const *target;
  const struct targmatch *match;

  for (target = &bfd_target_vector[0]; *target != NULL; target++)
    if (strcmp(name, (*target)->name) == 0)
      return *target;

  /* If we couldn't match on the exact name, try matching on the
     configuration triplet.  FIXME: We should run the triplet through
     config.sub first, but that is hard.  */
  for (match = &bfd_target_match[0]; match->triplet != NULL; match++) {
    if (fnmatch(match->triplet, name, 0) == 0) {
      while (match->vector == NULL)
        ++match;
      return match->vector;
    }
  }

  bfd_set_error(bfd_error_invalid_target);
  return NULL;
}

const bfd_target *bfd_find_target(const char *target_name, bfd *abfd) {
  const char *targname;
  const bfd_target *target;

  if (target_name != NULL)
    targname = target_name;
  else
    targname = getenv("GNUTARGET");

  /* This is safe; the vector cannot be null.  */
  if (targname == NULL || strcmp(targname, "default") == 0) {
    if (bfd_default_vector[0] != NULL)
      target = bfd_default_vector[0];
    else
      target = bfd_target_vector[0];
    if (abfd) {
      abfd->xvec = target;
      abfd->target_defaulted = TRUE;
    }
    return target;
  }

  if (abfd)
    abfd->target_defaulted = FALSE;

  target = find_target(targname);
  if (target == NULL)
    return NULL;

  if (abfd)
    abfd->xvec = target;
  return target;
}

bfd *bfd_fopen(const char *filename, const char *target, const char *mode,
               int fd) {
  bfd *nbfd;
  const bfd_target *target_vec;

  nbfd = _bfd_new_bfd();
  if (nbfd == NULL) {
    if (fd != -1)
      close(fd);
    return NULL;
  }

  target_vec = bfd_find_target(target, nbfd);
  if (target_vec == NULL) {
    if (fd != -1)
      close(fd);
    _bfd_delete_bfd(nbfd);
    return NULL;
  }

#ifdef HAVE_FDOPEN
  if (fd != -1)
    nbfd->iostream = fdopen(fd, mode);
  else
#endif
    nbfd->iostream = _bfd_real_fopen(filename, mode);
  if (nbfd->iostream == NULL) {
    bfd_set_error(bfd_error_system_call);
    _bfd_delete_bfd(nbfd);
    return NULL;
  }

  /* OK, put everything where it belongs.  */

  /* PR 11983: Do not cache the original filename, but
     rather make a copy - the original might go away.  */
  nbfd->filename = xstrdup(filename);

  /* Figure out whether the user is opening the file for reading,
     writing, or both, by looking at the MODE argument.  */
  if ((mode[0] == 'r' || mode[0] == 'w' || mode[0] == 'a') && mode[1] == '+')
    nbfd->direction = both_direction;
  else if (mode[0] == 'r')
    nbfd->direction = read_direction;
  else
    nbfd->direction = write_direction;

  if (!bfd_cache_init(nbfd)) {
    _bfd_delete_bfd(nbfd);
    return NULL;
  }
  nbfd->opened_once = TRUE;

  /* If we opened the file by name, mark it cacheable; we can close it
     and reopen it later.  However, if a file descriptor was provided,
     then it may have been opened with special flags that make it
     unsafe to close and reopen the file.  */
  if (fd == -1)
    (void)bfd_set_cacheable(nbfd, TRUE);

  return nbfd;
}

bfd *bfd_openr(const char *filename, const char *target) {
  return bfd_fopen(filename, target, FOPEN_RB, -1);
}

static void dump_dwarf_section(bfd *abfd, asection *section,
                               void *arg ATTRIBUTE_UNUSED) {
  const char *name = bfd_get_section_name(abfd, section);
  const char *match;
  int i;

  if (CONST_STRNEQ(name, ".gnu.linkonce.wi."))
    match = ".debug_info";
  else
    match = name;

  for (i = 0; i < max; i++)
    if ((strcmp(debug_displays[i].section.uncompressed_name, match) == 0 ||
         strcmp(debug_displays[i].section.compressed_name, match) == 0) &&
        debug_displays[i].enabled != NULL && *debug_displays[i].enabled) {
      struct dwarf_section *sec = &debug_displays[i].section;

      if (strcmp(sec->uncompressed_name, match) == 0)
        sec->name = sec->uncompressed_name;
      else
        sec->name = sec->compressed_name;
      if (load_specific_debug_section((enum dwarf_section_display_enum)i,
                                      section, abfd)) {
        debug_displays[i].display(sec, abfd);

        if (i != info && i != abbrev)
          free_debug_section((enum dwarf_section_display_enum)i);
      }
      break;
    }
}

void bfd_map_over_sections(bfd *abfd,
                           void (*operation)(bfd *, asection *, void *),
                           void *user_storage) {
  asection *sect;
  unsigned int i = 0;

  for (sect = abfd->sections; sect != NULL; i++, sect = sect->next)
    (*operation)(abfd, sect, user_storage);

  if (i != abfd->section_count) /* Debugging */
    abort();
}

static void dump_dwarf(bfd *abfd) {
  bfd *separates;

  is_relocatable = (abfd->flags & (EXEC_P | DYNAMIC)) == 0;

  eh_addr_size = bfd_arch_bits_per_address(abfd) / 8;

  if (bfd_big_endian(abfd))
    byte_get = byte_get_big_endian;
  else if (bfd_little_endian(abfd))
    byte_get = byte_get_little_endian;
  else
  /* PR 17512: file: objdump-s-endless-loop.tekhex.  */
  {
    warn(_("File %s does not contain any dwarf debug information\n"),
         bfd_get_filename(abfd));
    return;
  }

  switch (bfd_get_arch(abfd)) {
  case bfd_arch_i386:
    switch (bfd_get_mach(abfd)) {
    case bfd_mach_x86_64:
    case bfd_mach_x86_64_intel_syntax:
    case bfd_mach_x86_64_nacl:
    case bfd_mach_x64_32:
    case bfd_mach_x64_32_intel_syntax:
    case bfd_mach_x64_32_nacl:
      init_dwarf_regnames_x86_64();
      break;

    default:
      init_dwarf_regnames_i386();
      break;
    }
    break;

  case bfd_arch_iamcu:
    init_dwarf_regnames_iamcu();
    break;

  case bfd_arch_aarch64:
    init_dwarf_regnames_aarch64();
    break;

  case bfd_arch_s390:
    init_dwarf_regnames_s390();
    break;

  default:
    break;
  }

  separates = load_separate_debug_file(abfd, bfd_get_filename(abfd));

  bfd_map_over_sections(abfd, dump_dwarf_section, NULL);

  if (separates)
    bfd_map_over_sections(separates, dump_dwarf_section, NULL);

  free_debug_memory();
}

static void dump_bfd(bfd *abfd) {
  if (dump_dwarf_section_info)
    syms = slurp_symtab(abfd);

  dump_dwarf(abfd);
}

static void display_object_bfd(bfd *abfd) {
  char **matching;

  if (bfd_check_format_matches(abfd, bfd_object, &matching))
    dump_bfd(abfd);
}

static void display_any_bfd(bfd *file, int level) { display_object_bfd(file); }

static void display_file(char *filename, char *target, bfd_boolean last_file) {
  bfd *file;

  file = bfd_openr(filename, target);
  if (file == NULL)
    return;

  display_any_bfd(file, 0);
}
