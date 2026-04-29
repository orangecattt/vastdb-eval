#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* ATTRIBUTE_HIDDEN and other attribute macros */
#ifndef ATTRIBUTE_HIDDEN
#define ATTRIBUTE_HIDDEN __attribute__((visibility("hidden")))
#endif
#ifndef ATTRIBUTE_PRINTF_1
#define ATTRIBUTE_PRINTF_1 __attribute__((format(printf, 1, 2)))
#endif
#ifndef ATTRIBUTE_NORETURN
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#endif
#ifndef ENUM_BITFIELD
#define ENUM_BITFIELD(TYPE) enum TYPE
#endif

/* Basic BFD types */
typedef uint64_t bfd_vma;
typedef int64_t bfd_signed_vma;
typedef uint64_t bfd_size_type;
typedef uint64_t symvalue;
typedef int64_t file_ptr;
typedef uint64_t ufile_ptr;
typedef uint32_t flagword;
typedef uint8_t bfd_byte;

/* Forward declarations */
typedef struct bfd bfd;
struct bfd_link_info;
struct bfd_link_hash_entry;
typedef struct bfd_section *sec_ptr;
typedef struct bfd_section asection;
typedef struct reloc_cache_entry arelent;
struct orl;

/* BFD direction enum */
enum bfd_direction {
  no_direction = 0,
  read_direction = 1,
  write_direction = 2,
  both_direction = 3
};

/* BFD last IO enum */
enum bfd_last_io {
  bfd_io_seek = 0,
  bfd_io_read = 1,
  bfd_io_write = 2,
  bfd_io_force = 3
};

/* BFD format enum */
typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

/* BFD error type enum */
typedef enum bfd_error {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_target,
  bfd_error_wrong_format,
  bfd_error_wrong_object_format,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_no_armap,
  bfd_error_no_more_archived_files,
  bfd_error_malformed_archive,
  bfd_error_missing_dso,
  bfd_error_file_not_recognized,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_sorry,
  bfd_error_on_input,
  bfd_error_invalid_error_code
} bfd_error_type;

/* Link hash type enum */
enum bfd_link_hash_type {
  bfd_link_hash_new,
  bfd_link_hash_undefined,
  bfd_link_hash_undefweak,
  bfd_link_hash_defined,
  bfd_link_hash_defweak,
  bfd_link_hash_common,
  bfd_link_hash_indirect,
  bfd_link_hash_warning
};

/* Output type enum */
enum output_type {
  type_pde,
  type_pie,
  type_relocatable,
  type_dll,
};

/* Strip enum */
enum bfd_link_strip { strip_none, strip_all, strip_some };

/* Discard enum */
enum bfd_link_discard { discard_all, discard_l, discard_all_but_local };

/* Common skip ar symbols enum */
enum bfd_link_common_skip_ar_symbols {
  bfd_link_common_skip_none,
  bfd_link_common_skip_text,
  bfd_link_common_skip_data,
  bfd_link_common_skip_all
};

/* Report method enum */
enum report_method {
  RM_NOT_YET_SET = 0,
  RM_IGNORE,
  RM_DIAGNOSE,
};

/* Textrel check method enum */
enum textrel_check_method {
  textrel_check_none,
  textrel_check_warning,
  textrel_check_error
};

/* ELF STT common enum */
enum bfd_link_elf_stt_common { unchanged, elf_stt_common, no_elf_stt_common };

/* Hash table type enum */
enum bfd_link_hash_table_type {
  bfd_link_generic_hash_table,
  bfd_link_elf_hash_table
};

/* Section flags */
#define SEC_NO_FLAGS 0x0
#define SEC_ALLOC 0x1
#define SEC_LOAD 0x2
#define SEC_RELOC 0x4
#define SEC_READONLY 0x8
#define SEC_CODE 0x10
#define SEC_DATA 0x20
#define SEC_ROM 0x40
#define SEC_CONSTRUCTOR 0x80
#define SEC_HAS_CONTENTS 0x100
#define SEC_NEVER_LOAD 0x200
#define SEC_THREAD_LOCAL 0x400
#define SEC_FIXED_SIZE 0x800
#define SEC_IS_COMMON 0x1000
#define SEC_DEBUGGING 0x2000
#define SEC_IN_MEMORY 0x4000
#define SEC_EXCLUDE 0x8000
#define SEC_SORT_ENTRIES 0x10000
#define SEC_LINK_ONCE 0x20000
#define SEC_LINK_DUPLICATES 0xc0000
#define SEC_LINK_DUPLICATES_DISCARD 0x0
#define SEC_LINK_DUPLICATES_ONE_ONLY 0x40000
#define SEC_LINK_DUPLICATES_SAME_SIZE 0x80000
#define SEC_LINK_DUPLICATES_SAME_CONTENTS                                      \
  (SEC_LINK_DUPLICATES_ONE_ONLY | SEC_LINK_DUPLICATES_SAME_SIZE)
#define SEC_LINKER_CREATED 0x100000
#define SEC_KEEP 0x200000
#define SEC_SMALL_DATA 0x400000
#define SEC_MERGE 0x800000
#define SEC_STRINGS 0x1000000
#define SEC_GROUP 0x2000000

/* BFD flags */
#define BFD_NO_FLAGS 0x0
#define HAS_RELOC 0x1
#define EXEC_P 0x2
#define HAS_LINENO 0x4
#define HAS_DEBUG 0x08
#define HAS_SYMS 0x10
#define HAS_LOCALS 0x20
#define DYNAMIC 0x40
#define WP_TEXT 0x80
#define D_PAGED 0x100
#define BFD_IS_RELAXABLE 0x200
#define BFD_TRADITIONAL_FORMAT 0x400
#define BFD_IN_MEMORY 0x800
#define BFD_LINKER_CREATED 0x1000

/* BSF flags */
#define BSF_NO_FLAGS 0
#define BSF_LOCAL (1 << 0)
#define BSF_GLOBAL (1 << 1)
#define BSF_EXPORT BSF_GLOBAL
#define BSF_DEBUGGING (1 << 2)
#define BSF_FUNCTION (1 << 3)
#define BSF_KEEP (1 << 5)
#define BSF_ELF_COMMON (1 << 6)
#define BSF_WEAK (1 << 7)
#define BSF_SECTION_SYM (1 << 8)
#define BSF_OLD_COMMON (1 << 9)
#define BSF_NOT_AT_END (1 << 10)
#define BSF_CONSTRUCTOR (1 << 11)
#define BSF_WARNING (1 << 12)
#define BSF_INDIRECT (1 << 13)
#define BSF_FILE (1 << 14)
#define BSF_DYNAMIC (1 << 15)
#define BSF_OBJECT (1 << 16)
#define BSF_DEBUGGING_RELOC (1 << 17)
#define BSF_THREAD_LOCAL (1 << 18)
#define BSF_RELC (1 << 19)
#define BSF_SRELC (1 << 20)
#define BSF_SYNTHETIC (1 << 21)
#define BSF_GNU_INDIRECT_FUNCTION (1 << 22)
#define BSF_GNU_UNIQUE (1 << 23)
#define BSF_SECTION_SYM_USED (1 << 24)

/* Cache flag enum */
enum cache_flag {
  CACHE_NORMAL = 0,
  CACHE_NO_OPEN = 1,
  CACHE_NO_SEEK = 2,
  CACHE_NO_SEEK_ERROR = 4
};

/* BFD assert function */
extern void bfd_assert(const char *, int) ATTRIBUTE_HIDDEN;

#define BFD_ASSERT(x)                                                          \
  do {                                                                         \
    if (!(x))                                                                  \
      bfd_assert(__FILE__, __LINE__);                                          \
  } while (0)

/* bfd_write_p macro */
#define bfd_read_p(abfd)                                                       \
  ((abfd)->direction == read_direction || (abfd)->direction == both_direction)
#define bfd_write_p(abfd)                                                      \
  ((abfd)->direction == write_direction || (abfd)->direction == both_direction)

/* Forward declarations of hash table structures */
struct bfd_hash_entry {
  struct bfd_hash_entry *next;
  const char *string;
};

struct bfd_hash_table {
  struct bfd_hash_entry **table;
  unsigned int size;
  unsigned int count;
  struct bfd_hash_entry *(*newfunc)(struct bfd_hash_entry *,
                                    struct bfd_hash_table *, const char *);
  unsigned int alloced;
  bfd_size_type memory;
};

/* Common symbol entry */
struct bfd_link_hash_common_entry {
  unsigned int alignment_power;
  asection *section;
};

/* Link hash entry */
struct bfd_link_hash_entry {
  struct bfd_hash_entry root;
  ENUM_BITFIELD(bfd_link_hash_type) type : 8;
  unsigned int non_ir_ref_regular : 1;
  unsigned int non_ir_ref_dynamic : 1;
  unsigned int ref_real : 1;
  unsigned int wrapper_symbol : 1;
  unsigned int linker_def : 1;
  unsigned int ldscript_def : 1;
  unsigned int rel_from_abs : 1;
  union {
    struct {
      struct bfd_link_hash_entry *next;
      bfd *abfd;
    } undef;
    struct {
      struct bfd_link_hash_entry *next;
      asection *section;
      bfd_vma value;
    } def;
    struct {
      struct bfd_link_hash_entry *next;
      struct bfd_link_hash_entry *link;
      const char *warning;
    } i;
    struct {
      struct bfd_link_hash_entry *next;
      struct bfd_link_hash_common_entry *p;
      bfd_size_type size;
    } c;
  } u;
};

/* Link hash table */
struct bfd_link_hash_table {
  struct bfd_hash_table table;
  struct bfd_link_hash_entry *undefs;
  struct bfd_link_hash_entry *undefs_tail;
  void (*hash_table_free)(bfd *);
  enum bfd_link_hash_table_type type;
};

/* Symbol chain */
struct bfd_sym_chain {
  struct bfd_sym_chain *next;
  const char *name;
};

/* Flag info list */
struct flag_info_list {
  enum flag_type { with_flags, without_flags } with;
  const char *name;
  bool valid;
  struct flag_info_list *next;
};

/* Flag info */
struct flag_info {
  flagword only_with_flags;
  flagword not_with_flags;
  struct flag_info_list *flag_list;
  bool flags_initialized;
};

/* Link callbacks - forward declaration */
struct bfd_link_callbacks;

/* Dynamic list and version tree - forward declarations */
struct bfd_elf_dynamic_list;
struct bfd_elf_version_tree;

/* Link info structure (simplified - only fields used in bad.c) */
struct bfd_link_info {
  ENUM_BITFIELD(output_type) type : 2;
  unsigned int symbolic : 1;
  unsigned int export_dynamic : 1;
  unsigned int create_default_symver : 1;
  unsigned int gc_sections : 1;
  unsigned int gc_keep_exported : 1;
  unsigned int notice_all : 1;
  unsigned int lto_plugin_active : 1;
  unsigned int lto_all_symbols_read : 1;
  unsigned int strip_discarded : 1;
  unsigned int dynamic_data : 1;
  unsigned int resolve_section_groups : 1;
  unsigned int big_endian : 1;
  ENUM_BITFIELD(bfd_link_strip) strip : 2;
  ENUM_BITFIELD(bfd_link_discard) discard : 2;
  ENUM_BITFIELD(bfd_link_elf_stt_common) elf_stt_common : 2;
  ENUM_BITFIELD(bfd_link_common_skip_ar_symbols) common_skip_ar_symbols : 2;
  ENUM_BITFIELD(report_method) unresolved_syms_in_objects : 2;
  ENUM_BITFIELD(report_method) unresolved_syms_in_shared_libs : 2;
  unsigned int warn_unresolved_syms : 1;
  unsigned int static_link : 1;
  unsigned int keep_memory : 1;
  unsigned int emitrelocations : 1;
  unsigned int relro : 1;
  unsigned int enable_dt_relr : 1;
  unsigned int separate_code : 1;
  unsigned int one_rosegment : 1;
  unsigned int memory_seal : 1;
  unsigned int eh_frame_hdr_type : 2;
  ENUM_BITFIELD(textrel_check_method) textrel_check : 2;
  unsigned int emit_hash : 1;
  unsigned int emit_gnu_hash : 1;
  unsigned int reduce_memory_overheads : 1;
  unsigned int traditional_format : 1;
  unsigned int combreloc : 1;
  unsigned int default_imported_symver : 1;
  unsigned int new_dtags : 1;
  unsigned int no_ld_generated_unwind_info : 1;
  unsigned int task_link : 1;
  unsigned int allow_multiple_definition : 1;
  unsigned int prohibit_multiple_definition_absolute : 1;
  unsigned int warn_multiple_definition : 1;
  unsigned int allow_undefined_version : 1;
  unsigned int dynamic : 1;
  unsigned int execstack : 1;
  unsigned int noexecstack : 1;
  unsigned int warn_execstack : 2;
  unsigned int error_execstack : 1;
  unsigned int no_warn_rwx_segments : 1;
  unsigned int user_warn_rwx_segments : 1;
  unsigned int warn_is_error_for_rwx_segments : 1;
  unsigned int default_execstack : 1;
  unsigned int optimize : 1;
  unsigned int print_gc_sections : 1;
  unsigned int warn_alternate_em : 1;
  unsigned int user_phdrs : 1;
  unsigned int load_phdrs : 1;
  unsigned int check_relocs_after_open_input : 1;
  unsigned int nointerp : 1;
  unsigned int inhibit_common_definition : 1;
  unsigned int has_map_file : 1;
  unsigned int non_contiguous_regions : 1;
  unsigned int non_contiguous_regions_warnings : 1;
  unsigned int unique_symbol : 1;
  unsigned int maxpagesize_is_set : 1;
  unsigned int commonpagesize_is_set : 1;
  char wrap_char;
  char path_separator;
  bfd_signed_vma stacksize;
  signed int disable_target_specific_optimizations;
  const struct bfd_link_callbacks *callbacks;
  struct bfd_link_hash_table *hash;
  struct bfd_hash_table *keep_hash;
  struct bfd_hash_table *notice_hash;
  struct bfd_hash_table *wrap_hash;
  struct bfd_hash_table *ignore_hash;
  bfd *output_bfd;
  bfd *out_implib_bfd;
  bfd *input_bfds;
  bfd **input_bfds_tail;
  asection *create_object_symbols_section;
  struct bfd_sym_chain *gc_sym_list;
  void *base_file;
  const char *init_function;
  const char *fini_function;
  int relax_pass;
  int relax_trip;
  int extern_protected_data;
  int dynamic_undefined_weak;
  int pei386_auto_import;
  int pei386_runtime_pseudo_reloc;
  unsigned int spare_dynamic_tags;
  int indirect_extern_access;
  int nocopyreloc;
  bfd_byte *needed_1_p;
  bfd_vma flags;
  bfd_vma flags_1;
  bfd_vma gnu_flags_1;
  int start_stop_gc;
  unsigned int start_stop_visibility;
  bfd_vma maxpagesize;
};

#define bfd_link_relocatable(info) ((info)->type == type_relocatable)

/* Build ID */
struct bfd_build_id {
  bfd_size_type size;
  bfd_byte data[1];
};

/* Mmapped entry */
struct bfd_mmapped_entry {
  void *addr;
  size_t size;
};

struct bfd_mmapped {
  struct bfd_mmapped *next;
  unsigned int max_entry;
  unsigned int next_entry;
  struct bfd_mmapped_entry entries[1];
};

/* I/O vector */
struct bfd_iovec {
  file_ptr (*bread)(struct bfd *abfd, void *ptr, file_ptr nbytes);
  file_ptr (*bwrite)(struct bfd *abfd, const void *ptr, file_ptr nbytes);
  file_ptr (*btell)(struct bfd *abfd);
  int (*bseek)(struct bfd *abfd, file_ptr offset, int whence);
  int (*bclose)(struct bfd *abfd);
  int (*bflush)(struct bfd *abfd);
  int (*bstat)(struct bfd *abfd, struct stat *sb);
  void *(*bmmap)(struct bfd *abfd, void *addr, size_t len, int prot, int flags,
                 file_ptr offset, void **map_addr, size_t *map_len);
};

/* Target vector - forward declaration */
struct bfd_target;

/* Section structure */
typedef struct bfd_section {
  const char *name;
  struct bfd_section *next;
  struct bfd_section *prev;
  unsigned int id;
  unsigned int section_id;
  unsigned int index;
  flagword flags;
  unsigned int user_set_vma : 1;
  unsigned int linker_mark : 1;
  unsigned int linker_has_input : 1;
  unsigned int gc_mark : 1;
  unsigned int compress_status : 2;
  unsigned int segment_mark : 1;
  unsigned int sec_info_type : 3;
  unsigned int use_rela_p : 1;
  unsigned int mmapped_p : 1;
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
  bfd_vma output_offset;
  struct bfd_section *output_section;
  struct reloc_cache_entry *relocation;
  struct reloc_cache_entry **orelocation;
  unsigned reloc_count;
  unsigned int alignment_power;
  file_ptr filepos;
  file_ptr rel_filepos;
  file_ptr line_filepos;
  void *userdata;
  bfd_byte *contents;
  struct bfd_symbol *lineno;
  unsigned int lineno_count;
  unsigned int entsize;
  struct bfd_section *kept_section;
  file_ptr moving_line_filepos;
  int target_index;
  void *used_by_bfd;
  struct relent_chain *constructor_chain;
  bfd *owner;
  struct bfd_symbol *symbol;
  union {
    struct bfd_link_order *link_order;
    const char *linked_to_symbol_name;
  } map_head;
  union {
    struct bfd_link_order *link_order;
    const char *linked_to_symbol_name;
  } map_tail;
  unsigned int reloc_done : 1;
  unsigned int output_reloc_done : 1;
} asection;

/* Relocation cache entry - forward declaration */
struct reloc_cache_entry {
  asection *sym_section;
};

/* Relent chain - forward declaration */
struct relent_chain {
  struct relent_chain *next;
  arelent relent;
};

/* Link order type enum */
enum bfd_link_order_type {
  bfd_undefined_link_order,
  bfd_indirect_link_order,
  bfd_data_link_order,
  bfd_section_reloc_link_order,
  bfd_symbol_reloc_link_order
};

/* Link order reloc */
struct bfd_link_order_reloc {
  int reloc;
  union {
    asection *section;
    const char *name;
  } u;
  bfd_vma addend;
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
      unsigned int size;
      bfd_byte *contents;
    } data;
    struct {
      struct bfd_link_order_reloc *p;
    } reloc;
  } u;
};

/* Symbol structure */
typedef struct bfd_symbol {
  struct bfd *the_bfd;
  const char *name;
  symvalue value;
  flagword flags;
  struct bfd_section *section;
  union {
    void *p;
    bfd_vma i;
  } udata;
} asymbol;

/* Archive plugin file descriptor info */
struct bfd_plugin_file_handle;

/* BFD structure */
struct bfd {
  const char *filename;
  const struct bfd_target *xvec;
  void *iostream;
  const struct bfd_iovec *iovec;
  struct bfd *lru_prev, *lru_next;
  ufile_ptr where;
  long mtime;
  unsigned int id;
  flagword flags;
  unsigned int iformat : 2;
  unsigned int lto_type : 3;
  unsigned int direction : 2;
  unsigned int compress : 2;
  enum bfd_last_io last_io : 2;
  unsigned int has_armap : 1;
  unsigned int is_thin_archive : 1;
  unsigned int no_export : 1;
  unsigned int lto_output : 1;
  unsigned int output_has_begun : 1;
  unsigned int has_encrypt_init : 1;
  unsigned int is_linker_input : 1;
  unsigned int relocatable : 1;
  unsigned int in_format_matches : 1;
  unsigned int plugin_format : 2;
  unsigned int plugin_dummy_bfd_created : 1;
  unsigned int cacheable : 1;
  unsigned int force_writeable : 1;
  unsigned int opened_by_opener : 1;
  unsigned int mtime_set : 1;
  unsigned int no_paged_vmas : 1;
  unsigned int lto_slim : 1;
  unsigned int lto_ir : 1;
  unsigned int lto_needs_native : 1;
  unsigned int lto_needs_native_set : 1;
  unsigned int lto_needs_offload : 1;
  unsigned int lto_needs_offload_set : 1;
  unsigned int lto_needs_offload_wrapper : 1;
  unsigned int lto_needs_offload_wrapper_set : 1;
  unsigned int lto_needs_offload_wrapper_set_by_user : 1;
  unsigned int lto_needs_offload_set_by_user : 1;
  unsigned int lto_needs_native_set_by_user : 1;
  unsigned int lto_ir_set_by_user : 1;
  unsigned int lto_slim_set_by_user : 1;
  unsigned int lto_needs_offload_wrapper_set_by_user_unused : 1;
  bfd *plugin_dummy_bfd;
  ufile_ptr origin;
  ufile_ptr proxy_origin;
  struct bfd_hash_table section_htab;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  struct bfd_section *object_only_section;
  unsigned int section_count;
  int archive_plugin_fd;
  unsigned int archive_plugin_fd_open_count;
  int archive_pass;
  bfd_size_type alloc_size;
  bfd_vma start_address;
  struct bfd_symbol **outsymbols;
  unsigned int symcount;
  unsigned int dynsymcount;
  const struct bfd_arch_info *arch_info;
  ufile_ptr size;
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
    void *any;
  } tdata;
  void *usrdata;
  void *memory;
  const struct bfd_build_id *build_id;
  struct bfd_mmapped *mmapped;
};

/* Architecture info - forward declaration */
enum bfd_architecture { bfd_arch_unknown, bfd_arch_last };

enum bfd_flavour {
  bfd_target_unknown_flavour,
  bfd_target_aout_flavour,
  bfd_target_coff_flavour,
  bfd_target_ecoff_flavour,
  bfd_target_elf_flavour,
  bfd_target_ieee_flavour,
  bfd_target_nlm_flavour,
  bfd_target_oasys_flavour,
  bfd_target_tekhex_flavour,
  bfd_target_srec_flavour,
  bfd_target_ihex_flavour,
  bfd_target_som_flavour,
  bfd_target_os9k_flavour,
  bfd_target_msdos_flavour,
  bfd_target_evax_flavour,
  bfd_target_mmo_flavour,
  bfd_target_mach_o_flavour,
  bfd_target_pef_flavour,
  bfd_target_pef_xlib_flavour,
  bfd_target_sym_flavour,
  bfd_target_vms_flavour,
  bfd_target_xcoff_flavour,
  bfd_target_xcoff_and_bigobj_flavour,
  bfd_target_msdos_flavour2,
  bfd_target_plugin_flavour
};

enum bfd_endian { BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE, BFD_ENDIAN_UNKNOWN };

struct bfd_arch_info {
  unsigned int mach;
  const char *arch_name;
  const char *printable_name;
  unsigned int bits_per_address;
  unsigned int bits_per_byte;
  enum bfd_architecture arch;
  bool (*compatible)(const struct bfd_arch_info *,
                     const struct bfd_arch_info *);
  const char *(*scan)(const char *, const char *);
  const char *(*next)(const struct bfd_arch_info *,
                      const struct bfd_arch_info *);
  bool (*merge)(const struct bfd_arch_info *, const struct bfd_arch_info *);
  unsigned long bfd_arch_enum;
};

/* Target vector */
struct bfd_target {
  const char *name;
  enum bfd_flavour flavour;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  flagword object_flags;
  flagword section_flags;
  char ar_pad_char;
  unsigned short ar_max_namelen;
  bfd_vma (*get_flags)(int);
  const struct bfd_target *const *target_vector;
};

/* Standard sections */
extern asection _bfd_std_section[4];

#define bfd_com_section_ptr (&_bfd_std_section[0])
#define bfd_und_section_ptr (&_bfd_std_section[1])
#define bfd_abs_section_ptr (&_bfd_std_section[2])
#define bfd_ind_section_ptr (&_bfd_std_section[3])

/* Function declarations */
extern bool bfd_lock(void) ATTRIBUTE_HIDDEN;
extern bool bfd_unlock(void) ATTRIBUTE_HIDDEN;
extern FILE *bfd_cache_lookup_worker(bfd *abfd, enum cache_flag flag);
extern void bfd_set_error(bfd_error_type error_tag);
extern int bfd_seek(bfd *, file_ptr, int);
extern const char *bfd_get_target(const bfd *abfd);
extern bool bfd_generic_link_read_symbols(bfd *);
extern bfd_byte *bfd_get_relocated_section_contents(bfd *,
                                                    struct bfd_link_info *,
                                                    struct bfd_link_order *,
                                                    bfd_byte *, bool,
                                                    asymbol **);
extern bool bfd_set_section_contents(bfd *abfd, asection *section,
                                     const void *data, file_ptr offset,
                                     bfd_size_type count);
extern unsigned int bfd_octets_per_byte(const bfd *abfd, const asection *sec);
extern void _bfd_error_handler(const char *fmt, ...) ATTRIBUTE_PRINTF_1;
extern struct bfd_link_hash_entry *
bfd_wrapped_link_hash_lookup(bfd *, struct bfd_link_info *, const char *, bool,
                             bool, bool);
extern struct bfd_link_hash_entry *
bfd_link_hash_lookup(struct bfd_link_hash_table *, const char *, bool, bool,
                     bool);
extern void bfd_assert(const char *, int) ATTRIBUTE_HIDDEN;

/* Inline functions */
static inline bool bfd_is_thin_archive(const bfd *abfd) {
  return abfd->is_thin_archive;
}

static inline flagword bfd_section_flags(const asection *sec) {
  return sec->flags;
}

static inline bool bfd_is_com_section(const asection *sec) {
  return (sec->flags & SEC_IS_COMMON) != 0;
}

static inline bool bfd_is_und_section(const asection *sec) {
  return sec == bfd_und_section_ptr;
}

static inline bool bfd_is_ind_section(const asection *sec) {
  return sec == bfd_ind_section_ptr;
}

static inline asection *bfd_asymbol_section(const asymbol *sy) {
  return sy->section;
}

static inline const char *bfd_asymbol_name(const asymbol *sy) {
  return sy->name;
}

/* Gettext macro */
#ifndef _
#define _(String) String
#endif

/* set_symbol_from_hash function */
static void set_symbol_from_hash(asymbol *sym, struct bfd_link_hash_entry *h) {
  switch (h->type) {
  default:
    abort();
    break;
  case bfd_link_hash_new:
    if (sym->section != NULL) {
      BFD_ASSERT((sym->flags & BSF_CONSTRUCTOR) != 0);
    } else {
      sym->flags |= BSF_CONSTRUCTOR;
      sym->section = bfd_abs_section_ptr;
      sym->value = 0;
    }
    break;
  case bfd_link_hash_undefined:
    sym->section = bfd_und_section_ptr;
    sym->value = 0;
    break;
  case bfd_link_hash_undefweak:
    sym->section = bfd_und_section_ptr;
    sym->value = 0;
    sym->flags |= BSF_WEAK;
    break;
  case bfd_link_hash_defined:
    sym->section = h->u.def.section;
    sym->value = h->u.def.value;
    break;
  case bfd_link_hash_defweak:
    sym->flags |= BSF_WEAK;
    sym->section = h->u.def.section;
    sym->value = h->u.def.value;
    break;
  case bfd_link_hash_common:
    sym->value = h->u.c.size;
    if (sym->section == NULL)
      sym->section = bfd_com_section_ptr;
    else if (!bfd_is_com_section(sym->section)) {
      BFD_ASSERT(bfd_is_und_section(sym->section));
      sym->section = bfd_com_section_ptr;
    }
    break;
  case bfd_link_hash_indirect:
  case bfd_link_hash_warning:
    break;
  }
}

/* Macro for bfd_cache_lookup */
extern bfd *bfd_last_cache;

#define bfd_cache_lookup(x, flag)                                              \
  ((x) == bfd_last_cache ? (FILE *)(bfd_last_cache->iostream)                  \
                         : bfd_cache_lookup_worker(x, flag))

/* Macros for linker symbol access */
#define _bfd_generic_link_get_symbols(abfd) ((abfd)->outsymbols)
#define _bfd_generic_link_get_symcount(abfd) ((abfd)->symcount)

/* Original content from bad.c */
static file_ptr cache_bwrite(struct bfd *abfd, const void *from,
                             file_ptr nbytes) {
  if (!bfd_lock())
    return -1;
  file_ptr nwrite;
  FILE *f = bfd_cache_lookup(abfd, CACHE_NORMAL);

  if (f == NULL) {
    if (!bfd_unlock())
      return -1;
    return 0;
  }
  nwrite = fwrite(from, 1, nbytes, f);
  if (nwrite < nbytes && ferror(f)) {
    bfd_set_error(bfd_error_system_call);
    bfd_unlock();
    return -1;
  }
  if (!bfd_unlock())
    return -1;
  return nwrite;
}

bfd_size_type bfd_write(const void *ptr, bfd_size_type size, bfd *abfd) {
  file_ptr nwrote;

  while (abfd->my_archive != NULL && !bfd_is_thin_archive(abfd->my_archive))
    abfd = abfd->my_archive;

  if (abfd->iovec == NULL) {
    bfd_set_error(bfd_error_invalid_operation);
    return -1;
  }

  if (abfd->last_io == bfd_io_read) {
    abfd->last_io = bfd_io_force;
    if (bfd_seek(abfd, 0, SEEK_CUR) != 0)
      return -1;
  }
  abfd->last_io = bfd_io_write;

  nwrote = cache_bwrite(abfd, ptr, size);
  if (nwrote != -1)
    abfd->where += nwrote;
  if ((bfd_size_type)nwrote != size) {
#ifdef ENOSPC
    errno = ENOSPC;
#endif
    bfd_set_error(bfd_error_system_call);
  }
  return nwrote;
}

bool _bfd_generic_set_section_contents(bfd *abfd, sec_ptr section,
                                       const void *location, file_ptr offset,
                                       bfd_size_type count) {
  if (count == 0)
    return true;

  if (bfd_seek(abfd, section->filepos + offset, SEEK_SET) != 0 ||
      bfd_write(location, count, abfd) != count)
    return false;

  return true;
}

bool bfd_set_section_contents(bfd *abfd, sec_ptr section, const void *location,
                              file_ptr offset, bfd_size_type count) {
  bfd_size_type sz;

  if (!(bfd_section_flags(section) & SEC_HAS_CONTENTS)) {
    bfd_set_error(bfd_error_no_contents);
    return false;
  }

  sz = section->size;
  if ((bfd_size_type)offset > sz || count > sz - offset ||
      count != (size_t)count) {
    bfd_set_error(bfd_error_bad_value);
    return false;
  }

  if (!bfd_write_p(abfd)) {
    bfd_set_error(bfd_error_invalid_operation);
    return false;
  }

  /* Record a copy of the data in memory if desired.  */
  if (section->contents && location != section->contents + offset)
    memcpy(section->contents + offset, location, (size_t)count);

  if (_bfd_generic_set_section_contents(abfd, section, location, offset,
                                        count)) {
    abfd->output_has_begun = true;
    return true;
  }

  return false;
}

bool default_indirect_link_order(bfd *output_bfd, struct bfd_link_info *info,
                                 asection *output_section,
                                 struct bfd_link_order *link_order,
                                 bool generic_linker) {
  asection *input_section;
  bfd *input_bfd;
  bfd_byte *alloced = NULL;
  bfd_byte *new_contents;
  file_ptr loc;

  BFD_ASSERT((output_section->flags & SEC_HAS_CONTENTS) != 0);

  input_section = link_order->u.indirect.section;
  input_bfd = input_section->owner;
  if (input_section->size == 0)
    return true;

  BFD_ASSERT(input_section->output_section == output_section);
  BFD_ASSERT(input_section->output_offset == link_order->offset);
  BFD_ASSERT(input_section->size == link_order->size);

  if (bfd_link_relocatable(info) && input_section->reloc_count > 0 &&
      output_section->orelocation == NULL) {
    /* Space has not been allocated for the output relocations.
       This can happen when we are called by a specific backend
       because somebody is attempting to link together different
       types of object files.  Handling this case correctly is
       difficult, and sometimes impossible.  */
    _bfd_error_handler
        /* xgettext:c-format */
        (_("attempt to do relocatable link with %s input and %s output"),
         bfd_get_target(input_bfd), bfd_get_target(output_bfd));
    bfd_set_error(bfd_error_wrong_format);
    return false;
  }

  if (!generic_linker) {
    asymbol **sympp;
    asymbol **symppend;

    /* Get the canonical symbols.  The generic linker will always
       have retrieved them by this point, but we are being called by
       a specific linker, presumably because we are linking
       different types of object files together.  */
    if (!bfd_generic_link_read_symbols(input_bfd))
      return false;

    /* Since we have been called by a specific linker, rather than
       the generic linker, the values of the symbols will not be
       right.  They will be the values as seen in the input file,
       not the values of the final link.  We need to fix them up
       before we can relocate the section.  */
    sympp = _bfd_generic_link_get_symbols(input_bfd);
    symppend = sympp + _bfd_generic_link_get_symcount(input_bfd);
    for (; sympp < symppend; sympp++) {
      asymbol *sym;
      struct bfd_link_hash_entry *h;

      sym = *sympp;

      if ((sym->flags & (BSF_INDIRECT | BSF_WARNING | BSF_GLOBAL |
                         BSF_CONSTRUCTOR | BSF_WEAK)) != 0 ||
          bfd_is_und_section(bfd_asymbol_section(sym)) ||
          bfd_is_com_section(bfd_asymbol_section(sym)) ||
          bfd_is_ind_section(bfd_asymbol_section(sym))) {
        /* sym->udata may have been set by
           generic_link_add_symbol_list.  */
        if (sym->udata.p != NULL)
          h = (struct bfd_link_hash_entry *)sym->udata.p;
        else if (bfd_is_und_section(bfd_asymbol_section(sym)))
          h = bfd_wrapped_link_hash_lookup(
              output_bfd, info, bfd_asymbol_name(sym), false, false, true);
        else
          h = bfd_link_hash_lookup(info->hash, bfd_asymbol_name(sym), false,
                                   false, true);
        if (h != NULL)
          set_symbol_from_hash(sym, h);
      }
    }
  }

  if ((output_section->flags & (SEC_GROUP | SEC_LINKER_CREATED)) == SEC_GROUP &&
      input_section->size != 0) {
    /* Group section contents are set by bfd_elf_set_group_contents.  */
    if (!output_bfd->output_has_begun) {
      /* FIXME: This hack ensures bfd_elf_set_group_contents is called.  */
      if (!bfd_set_section_contents(output_bfd, output_section, "", 0, 1))
        goto error_return;
    }
    new_contents = output_section->contents;
    BFD_ASSERT(input_section->output_offset == 0);
  } else {
    /* Get and relocate the section contents.  */
    new_contents = (bfd_get_relocated_section_contents(
        output_bfd, info, link_order, NULL, bfd_link_relocatable(info),
        _bfd_generic_link_get_symbols(input_bfd)));
    alloced = new_contents;
    if (!new_contents)
      goto error_return;
  }

  /* Output the section contents.  */
  loc = (input_section->output_offset *
         bfd_octets_per_byte(output_bfd, output_section));
  if (!bfd_set_section_contents(output_bfd, output_section, new_contents, loc,
                                input_section->size))
    goto error_return;

  free(alloced);
  return true;

error_return:
  free(alloced);
  return false;
}
