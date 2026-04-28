#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

extern void free(void *ptr);
extern void *malloc(size_t size);
extern void *calloc(size_t nmemb, size_t size);
extern void *realloc(void *ptr, size_t size);
extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memset(void *s, int c, size_t n);
extern int fprintf(FILE *stream, const char *format, ...);
extern int sprintf(char *str, const char *format, ...);
extern int fflush(FILE *stream);
extern int printf(const char *format, ...);
extern FILE *fopen(const char *pathname, const char *mode);
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
extern int fclose(FILE *stream);
extern void qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));
extern int strncmp(const char *s1, const char *s2, size_t n);
extern int strcmp(const char *s1, const char *s2);
extern char *strerror(int errnum);
#define PRId64 "ld"

#define PACKAGE "binutils"
#define PACKAGE_VERSION "2.31"
#define HAVE_INTTYPES_H 1
#define HAVE_STRINGIZE 1
#define BFD_HOST_64BIT_LONG 1
#define BFD_HOST_64_BIT_DEFINED 1
#define BFD_HOST_64_BIT long
#define BFD_HOST_U_64_BIT unsigned long
#define BFD_HOSTPTR_T long
#define bfd_file_ptr long
#define wordsize 64
#define bfd_default_target_size 64
#define supports_plugins 0

#define STRING_COMMA_LEN(STR) (STR), (sizeof(STR) - 1)
#define CONST_STRNEQ(STR1, STR2)                                               \
  (strncmp((STR1), (STR2), sizeof(STR2) - 1) == 0)
#define INLINE __inline__
#define BFD64
#define BFD_ARCH_SIZE 64
#define ARCH_SIZE 64

typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;

typedef struct bfd bfd;
typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;
typedef unsigned long bfd_size_type;
typedef unsigned long symvalue;
typedef long bfd_int64_t;
typedef unsigned long bfd_uint64_t;
#define BFD_VMA_FMT "l"
#define sprintf_vma(s, x) sprintf(s, "%016" BFD_VMA_FMT "x", x)
#define fprintf_vma(f, x) fprintf(f, "%016" BFD_VMA_FMT "x", x)
#define printf_vma(x) fprintf_vma(stdout, x)

typedef long file_ptr;
typedef unsigned long ufile_ptr;
typedef unsigned int flagword;
typedef unsigned char bfd_byte;

typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

#define BSF_NO_FLAGS 0x00
#define BSF_LOCAL 0x01
#define BSF_GLOBAL 0x02
#define BSF_EXPORT BSF_GLOBAL
#define BSF_DEBUGGING 0x04
#define BSF_FUNCTION 0x08
#define BSF_KEEP 0x10
#define BSF_KEEP_G 0x20
#define BSF_WEAK 0x40
#define BSF_SECTION_SYM 0x80
#define BSF_OLD_COMMON 0x100
#define BSF_NOT_AT_END 0x200
#define BSF_CONSTRUCTOR 0x400
#define BSF_WARNING 0x800
#define BSF_INDIRECT 0x1000
#define BSF_FILE 0x2000
#define BSF_DYNAMIC 0x4000
#define BSF_GNU_UNIQUE 0x8000
#define BSF_OBJECT 0x10000
#define BSF_THREAD_LOCAL 0x20000
#define BSF_RELC 0x40000
#define BSF_SRELC 0x80000
#define BSF_GNU_INDIRECT_FUNCTION 0x100000
#define BSF_ELF_COMMON 0x200000

#define SEC_NO_FLAGS 0x000
#define SEC_ALLOC 0x001
#define SEC_LOAD 0x002
#define SEC_RELOC 0x004
#define SEC_READONLY 0x010
#define SEC_CODE 0x020
#define SEC_DATA 0x040
#define SEC_ROM 0x080
#define SEC_CONSTRUCTOR 0x100
#define SEC_HAS_CONTENTS 0x200
#define SEC_NEVER_LOAD 0x400
#define SEC_THREAD_LOCAL 0x1000
#define SEC_EXCLUDE 0x4000
#define SEC_SORT_ENTRIES 0x8000
#define SEC_LINK_ONCE 0x10000
#define SEC_LINK_DUPLICATES 0x20000
#define SEC_LINK_DUPLICATES_DISCARD 0x100000
#define SEC_DEBUGGING 0x400000
#define SEC_IN_MEMORY 0x800000
#define SEC_IS_COMMON 0x8000000
#define SEC_SMALL_DATA 0x10000000
#define SEC_MERGE 0x20000000
#define SEC_STRINGS 0x40000000
#define SEC_GROUP 0x80000000
#define SEC_ELF_RENAME 0x100000000ULL
#define SEC_LINKER_CREATED 0x200000000ULL
#define SEC_KEEP 0x400000000ULL
#define STRIP_ALL 1
#define STRIP_DEBUG 2
#define STRIP_UNNEEDED 3
#define STRIP_NONDEBUG 4
#define STRIP_DWO 5
#define STRIP_NONDWO 6
#define LOCALS_UNDEF 0

struct bfd_section;
struct bfd_symbol;
struct bfd_target;
struct bfd_arch_info;
struct elf_obj_tdata;
struct bfd_elf_section_data;
struct elf_backend_data;
struct elf_strtab_hash;
struct elf_section_list;
struct bfd_link_info;

typedef struct bfd_hash_entry {
  struct bfd_hash_entry *next;
  const char *string;
  unsigned long hash;
} bfd_hash_entry;

struct bfd_hash_table;

typedef struct bfd_hash_table {
  struct bfd_hash_entry **table;
  unsigned long size;
  unsigned long count;
  struct bfd_hash_entry *(*newfunc)(struct bfd_hash_entry *,
                                    struct bfd_hash_table *, const char *);
  unsigned int frozen;
  void *memory;
} bfd_hash_table;

typedef struct {
  unsigned char e_ident[16];
  unsigned int e_type;
  unsigned int e_machine;
  unsigned long e_version;
  bfd_vma e_entry;
  bfd_vma e_phoff;
  bfd_vma e_shoff;
  unsigned long e_flags;
  unsigned int e_ehsize;
  unsigned int e_phentsize;
  unsigned int e_phnum;
  unsigned int e_shentsize;
  unsigned int e_shnum;
  unsigned int e_shstrndx;
} Elf_Internal_Ehdr;

typedef struct {
  unsigned int p_type;
  unsigned int p_flags;
  bfd_vma p_offset;
  bfd_vma p_vaddr;
  bfd_vma p_paddr;
  bfd_size_type p_filesz;
  bfd_size_type p_memsz;
  bfd_vma p_align;
} Elf_Internal_Phdr;

typedef struct {
  unsigned int sh_name;
  unsigned int sh_type;
  bfd_vma sh_flags;
  bfd_vma sh_addr;
  bfd_vma sh_offset;
  bfd_vma sh_size;
  unsigned int sh_link;
  unsigned int sh_info;
  bfd_vma sh_addralign;
  bfd_vma sh_entsize;
  bfd_byte *contents;
  unsigned int sh_num;
  struct bfd_section *bfd_section;
} Elf_Internal_Shdr;

typedef struct {
  unsigned int st_name;
  bfd_vma st_value;
  bfd_size_type st_size;
  unsigned char st_info;
  unsigned char st_other;
  unsigned int st_shndx;
  unsigned int st_target_internal;
} Elf_Internal_Sym;

typedef struct {
  unsigned short vs_versym;
  unsigned short vs_vers;
} Elf_Internal_Versym;

typedef struct {
  unsigned char e_ident[16];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_External_Ehdr;

typedef struct {
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_External_Phdr;

typedef struct {
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_External_Shdr;

typedef struct {
  Elf32_Word st_name;
  Elf32_Addr st_value;
  Elf32_Word st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Half st_shndx;
} Elf32_External_Sym;

typedef struct {
  Elf32_Half shndx;
} Elf32_External_Sym_Shndx;

typedef struct {
  Elf32_Half vs_versym;
} Elf32_External_Versym;

#define Elf_External_Ehdr Elf32_External_Ehdr
#define Elf_External_Phdr Elf32_External_Phdr
#define Elf_External_Shdr Elf32_External_Shdr
#define Elf_External_Sym Elf32_External_Sym
#define Elf_External_Sym_Shndx Elf32_External_Sym_Shndx
#define Elf_External_Versym Elf32_External_Versym

struct elf_obj_tdata {
  Elf_Internal_Shdr symtab_hdr;
  Elf_Internal_Shdr strtab_hdr;
  Elf_Internal_Shdr shstrtab_hdr;
  Elf_Internal_Shdr dynsymtab_hdr;
  Elf_Internal_Shdr dynstrtab_hdr;
  Elf_Internal_Shdr dynverdef_hdr;
  Elf_Internal_Shdr dynversym_hdr;
  Elf_Internal_Shdr dynverref_hdr;
  Elf_Internal_Shdr gnu_debuglink_hdr;
  unsigned int num_elf_sections;
  Elf_Internal_Shdr **elf_sect_ptr;
  unsigned int symtab_section;
  unsigned int dynsymtab_section;
  unsigned int dynversym_section;
  unsigned int dynverdef_section;
  unsigned int dynverref_section;
  unsigned int strtab_sec;
  unsigned int shstrtab_sec;
  void *section_syms;
  unsigned int num_section_syms;
  file_ptr next_file_pos;
  void *shstrtab_ptr;
  void *fake_sections;
  void *parse_notes;
  struct elf_section_list *symtab_shndx_list;
  Elf_Internal_Phdr *phdr;
  unsigned int num_phdrs;
  void *verdef;
  void *verref;
  struct elf_strtab_hash *shstrtab;
  flagword elf_strtab_flags;
  struct {
    struct {
      bfd_boolean (*after_write_object_contents)(bfd *);
    } build_id;
  } *o;
};

union bfd_tdata {
  struct elf_obj_tdata *elf_obj_data;
  void *coff_obj_data;
  void *any;
};

struct bfd_section {
  const char *name;
  int index;
  struct bfd_section *next;
  struct bfd_section *prev;
  bfd_vma id;
  bfd_vma alignment_power;
  struct bfd *owner;
  struct bfd_section *output_section;
  bfd_vma output_offset;
  bfd_size_type size;
  bfd_vma vma;
  bfd_vma lma;
  bfd_size_type rawsize;
  bfd_vma filepos;
  void *userdata;
  flagword flags;
  bfd_byte *contents;
  struct bfd_symbol **symbol;
  void *used_by_bfd;
  unsigned long reloc_count;
  bfd_vma rel_filepos;
  bfd_vma line_filepos;
  struct reloc_cache_entry *relocation;
  bfd_boolean use_rela_p;
  Elf_Internal_Shdr *this_hdr;
  bfd_vma entsize;
  struct bfd_section *next_in_group;
  unsigned int sh_type;
  bfd_vma sh_flags;
};
typedef struct bfd_section asection;
typedef struct bfd_section *sec_ptr;

union bfd_symbol_udata {
  long i;
  void *p;
};

struct bfd_symbol {
  const char *name;
  bfd_vma value;
  flagword flags;
  struct bfd_section *section;
  struct bfd *the_bfd;
  union bfd_symbol_udata udata;
};
typedef struct bfd_symbol asymbol;

typedef enum bfd_flavour {
  bfd_unknown_flavour = 0,
  bfd_aout_flavour,
  bfd_coff_flavour,
  bfd_elf_flavour,
  bfd_ieee_flavour,
  bfd_nlm_flavour,
  bfd_oasys_flavour,
  bfd_tekhex_flavour,
  bfd_srec_flavour,
  bfd_ihex_flavour,
  bfd_som_flavour,
  bfd_os9k_flavour,
  bfd_msdos_flavour,
  bfd_plugin_flavour,
  bfd_target_coff_flavour = bfd_coff_flavour,
  bfd_target_elf_flavour = bfd_elf_flavour
} bfd_flavour;

typedef enum bfd_endian {
  BFD_ENDIAN_BIG,
  BFD_ENDIAN_LITTLE,
  BFD_ENDIAN_UNKNOWN
} bfd_endian;

typedef enum bfd_architecture {
  bfd_arch_unknown,
  bfd_arch_obscure,
  bfd_arch_m68k,
  bfd_arch_i386,
  bfd_arch_x86_64,
  bfd_arch_i860,
  bfd_arch_i960,
  bfd_arch_sparc,
  bfd_arch_sparc64,
  bfd_arch_arm,
  bfd_arch_ns32k,
  bfd_arch_pdp11,
  bfd_arch_romp,
  bfd_arch_we32k,
  bfd_arch_tahoe,
  bfd_arch_i88,
  bfd_arch_i370,
  bfd_arch_m68hc11,
  bfd_arch_m68hc12,
  bfd_arch_z8k,
  bfd_arch_h8300,
  bfd_arch_hppa,
  bfd_arch_a29k,
  bfd_arch_avr,
  bfd_arch_d10v,
  bfd_arch_d30v,
  bfd_arch_v850,
  bfd_arch_arc,
  bfd_arch_m32r,
  bfd_arch_mn10200,
  bfd_arch_mn10300,
  bfd_arch_cris,
  bfd_arch_fr30,
  bfd_arch_ip2k,
  bfd_arch_iq2000,
  bfd_arch_m32c,
  bfd_arch_mcore,
  bfd_arch_mep,
  bfd_arch_metag,
  bfd_arch_microblaze,
  bfd_arch_mips,
  bfd_arch_moxie,
  bfd_arch_msp430,
  bfd_arch_mt,
  bfd_arch_nds32,
  bfd_arch_nios2,
  bfd_arch_or1k,
  bfd_arch_powerpc,
  bfd_arch_rl78,
  bfd_arch_rs6000,
  bfd_arch_rx,
  bfd_arch_s390,
  bfd_arch_score,
  bfd_arch_sh,
  bfd_arch_spu,
  bfd_arch_tilegx,
  bfd_arch_tilepro,
  bfd_arch_tic30,
  bfd_arch_tic4x,
  bfd_arch_tic54x,
  bfd_arch_tic6x,
  bfd_arch_tic80,
  bfd_arch_tricore,
  bfd_arch_v850_rh850,
  bfd_arch_xc16x,
  bfd_arch_xgate,
  bfd_arch_xstormy16,
  bfd_arch_xtensa,
  bfd_arch_z80,
  bfd_arch_bpf,
  bfd_arch_cr16,
  bfd_arch_crx,
  bfd_arch_ft32,
  bfd_arch_last
} bfd_architecture;

struct bfd_target {
  const char *name;
  enum bfd_flavour flavour;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  flagword object_flags;
  flagword section_flags;
  const char symbol_leading_char;
  char ar_pad_char;
  unsigned short ar_max_namelen;
  unsigned char match_priority;
  const struct bfd_target *(*_bfd_check_format)(bfd *);
  bfd_boolean (*_bfd_set_format[bfd_type_end])(bfd *);
  bfd_boolean (*_new_section_hook)(bfd *, struct bfd_section *);
  bfd_boolean (*_bfd_write_contents)(bfd *);
};
typedef struct bfd_target bfd_target;

typedef enum bfd_error_type {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_wrong_object_format,
  bfd_error_wrong_object_format_for_symbol,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_on_input,
  bfd_error_invalid_input_file,
  bfd_error_invalid_target,
  bfd_error_file_not_recognized,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_matching_archive_symbol,
  bfd_error_no_error_section,
  bfd_error_wrong_format,
  bfd_error_missing_dso,
  bfd_error_non_fatal_runtime_error,
  bfd_error_no_more_archived_files,
  bfd_error_malformed_archive,
  bfd_error_file_is_ambiguous,
  bfd_error_invalid_archive_member,
  bfd_error_no_armap,
  bfd_error_plugin_no_symbol,
  bfd_error_invalid_archive_index,
  bfd_error_invalid_comdat,
  bfd_error_mixed_spec,
  bfd_error_multiple_symbol_sections,
  bfd_error_symbols_missing,
  bfd_error_invalid_section_index,
  bfd_error_section_mismatch,
  bfd_error_reloc_overflow,
  bfd_error_reloc_truncated,
  bfd_error_bad_reloc,
  bfd_error_no_section_group,
  bfd_error_invalid_section_type,
  bfd_error_missing_section_group,
  bfd_error_section_too_large,
  bfd_error_section_alignment_mismatch,
  bfd_error_section_overlap,
  bfd_error_section_misalignment,
  bfd_error_section_size_mismatch,
  bfd_error_section_contents_mismatch,
  bfd_error_section_flags_mismatch,
  bfd_error_section_name_mismatch,
  bfd_error_section_type_mismatch,
  bfd_error_section_linker_mismatch,
  bfd_error_section_reloc_mismatch,
  bfd_error_section_symtab_mismatch,
  bfd_error_section_strtab_mismatch,
  bfd_error_section_shndx_mismatch,
  bfd_error_section_versym_mismatch,
  bfd_error_section_verdef_mismatch,
  bfd_error_section_verneed_mismatch,
  bfd_error_section_hash_mismatch,
  bfd_error_section_dynamic_mismatch,
  bfd_error_section_dynsym_mismatch,
  bfd_error_section_gnu_hash_mismatch,
  bfd_error_section_gnu_versym_mismatch,
  bfd_error_section_gnu_verdef_mismatch,
  bfd_error_section_gnu_verneed_mismatch,
  bfd_error_section_gnu_attributes_mismatch,
  bfd_error_section_gnu_debuglink_mismatch,
  bfd_error_section_gnu_debugaltlink_mismatch,
  bfd_error_section_gnu_build_id_mismatch,
  bfd_error_section_gnu_note_mismatch,
  bfd_error_section_gnu_property_mismatch,
  bfd_error_section_gnu_stack_mismatch,
  bfd_error_section_gnu_relro_mismatch,
  bfd_error_section_gnu_eh_frame_mismatch,
  bfd_error_section_gnu_frame_mismatch,
  bfd_error_section_gnu_init_array_mismatch,
  bfd_error_section_gnu_fini_array_mismatch,
  bfd_error_section_gnu_preinit_array_mismatch,
  bfd_error_section_gnu_liblist_mismatch,
  bfd_error_section_gnu_conflict_mismatch
} bfd_error_type;

struct bfd_arch_info {
  unsigned long mach;
  const char *arch_name;
  const char *printable_name;
  unsigned int bits_per_word;
  unsigned int bits_per_address;
  unsigned int bits_per_byte;
  enum bfd_architecture arch;
  bfd_boolean (*compatible)(const struct bfd_arch_info *,
                            const struct bfd_arch_info *);
  bfd_boolean (*scan)(const char *, const char *);
  char *(*mangle)(const struct bfd_arch_info *, const char *);
};
typedef struct bfd_arch_info bfd_arch_info_type;

struct bfd {
  const char *filename;
  const bfd_target *xvec;
  void *iostream;
  void *cache;
  bfd_boolean cacheable;
  void *arelt_data;
  struct bfd *my_archive;
  struct bfd *next;
  struct bfd *archive_head;
  struct bfd *nested_archives;
  enum bfd_format format;
  enum bfd_flavour flavour;
  enum bfd_direction {
    no_direction,
    read_direction,
    write_direction,
    both_direction
  } direction;
  file_ptr where;
  bfd_boolean opened_by_me;
  bfd_boolean has_armap;
  bfd_boolean is_thin_archive;
  bfd_boolean no_arname;
  bfd_boolean is_linker_input;
  bfd_boolean target_defaulted;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  unsigned int type;
  unsigned int archive_pass;
  struct bfd_symbol **outsymbols;
  struct bfd_symbol **symdefs;
  union bfd_tdata tdata;
  const struct bfd_arch_info *arch_info;
  bfd_size_type symcount;
  unsigned int flags;
  bfd_vma start_address;
  unsigned int symtab_header;
  void *usrdata;
  unsigned int output_has_begun;
  struct bfd *lru_prev;
  struct bfd *lru_next;
  file_ptr mtime;
  bfd_size_type filesize;
  void *section_htab;
};

struct bfd_elf_section_data {
  Elf_Internal_Shdr this_hdr;
  Elf_Internal_Shdr rel_hdr;
  Elf_Internal_Shdr rel_hdr2;
  unsigned int rel_count;
  unsigned int rel_count2;
  unsigned int reloc_done;
  unsigned int reloc_done2;
  bfd_vma sec_shndx;
  void *tdata;
  struct bfd_elf_section_data *next;
  struct bfd_elf_section_data *prev;
  unsigned int this_idx;
  unsigned int rel_idx;
  unsigned int rel_idx2;
  unsigned int kept_section;
  struct {
    Elf_Internal_Shdr hdr;
  } rela;
  struct {
    Elf_Internal_Shdr hdr;
  } rel;
};

struct elf_symbol_struct {
  asymbol symbol;
  Elf_Internal_Sym internal_elf_sym;
  asection *section;
  bfd_vma symbol_count;
  void *got;
  void *plt;
  void *tlsdesc;
  unsigned int htab;
  unsigned int non_elf;
  unsigned int versioned;
  unsigned int symbolic;
  unsigned int ref_regular;
  unsigned int def_regular;
  unsigned int ref_dynamic;
  unsigned int def_dynamic;
  unsigned int needs_plt;
  unsigned int pointer_equality_needed;
  unsigned int unique_global;
  unsigned int dynamic_weak;
  unsigned int no_export;
  unsigned int forced_local;
  unsigned int hidden;
  unsigned int protected;
  unsigned int dynamic;
  unsigned int needs_copy;
  unsigned int non_got_ref;
  unsigned int non_got_ref_from_readonly;
  unsigned int non_got_ref_from_non_shared;
  unsigned int ref_non_irregular;
  unsigned int def_non_irregular;
  unsigned short version;
};
typedef struct elf_symbol_struct elf_symbol_type;
#define elf_symbol_from(abfd, sym) ((elf_symbol_type *)(sym))

struct elf_size_info {
  unsigned int sizeof_sym;
  unsigned int sizeof_rel;
  unsigned int sizeof_rela;
  unsigned int sizeof_versym;
  unsigned int log_file_align;
  unsigned int arch_size;
  unsigned int int_rels_per_ext_rel;
  void (*swap_symbol_out)(bfd *, Elf_Internal_Sym *, void *, void *);
  void (*write_relocs)(bfd *, struct bfd_section *, void *);
  bfd_boolean (*write_shdrs_and_ehdr)(bfd *);
  long (*slurp_symbol_table)(bfd *, asymbol **, bfd_boolean);
};

struct elf_backend_data {
  struct elf_size_info *s;
  bfd_boolean (*elf_backend_name_local_section_symbols)(bfd *);
  bfd_boolean (*elf_backend_section_flags)(flagword *, Elf_Internal_Shdr *);
  bfd_boolean (*elf_backend_section_from_shdr)(bfd *, Elf_Internal_Shdr *,
                                               const char *, unsigned int);
  bfd_boolean (*elf_backend_object_p)(bfd *);
  bfd_boolean (*elf_backend_begin_write_processing)(bfd *, void *);
  bfd_boolean (*elf_backend_post_process_headers)(bfd *, void *);
  bfd_boolean (*elf_backend_section_processing)(bfd *, Elf_Internal_Shdr *);
  void (*elf_backend_final_write_processing)(bfd *, bfd_boolean);
  void (*elf_backend_symbol_processing)(bfd *, asymbol *);
  void (*elf_backend_symbol_table_processing)(bfd *, elf_symbol_type *,
                                              unsigned int);
  int (*elf_backend_get_symbol_type)(Elf_Internal_Sym *, int);
  void (*swap_symbol_out)(bfd *, Elf_Internal_Sym *, void *, void *);
  void (*write_relocs)(bfd *, struct bfd_section *, void *);
  bfd_boolean (*write_shdrs_and_ehdr)(bfd *);
  long (*slurp_symbol_table)(bfd *, asymbol **, bfd_boolean);
  unsigned int elf_machine_code;
  unsigned int elf_machine_alt1;
  unsigned int elf_machine_alt2;
  unsigned int elf_osabi;
  unsigned int arch;
  unsigned int minpagesize;
  unsigned int obj_attrs_section_type;
  flagword elf_strtab_flags;
};

struct elf_sym_strtab {
  Elf_Internal_Sym sym;
  bfd_size_type dest_index;
  bfd_size_type destshndx_index;
};

struct elf_section_list {
  unsigned int ndx;
  Elf_Internal_Shdr hdr;
  struct elf_section_list *next;
};
typedef struct elf_section_list elf_section_list;

struct reloc_cache_entry {
  bfd_vma address;
  asymbol *sym_ptr;
  bfd_vma addend;
};

struct section_add {
  const char *name;
  const char *filename;
  asection *section;
  bfd_size_type size;
  void *contents;
  struct section_add *next;
};

struct section_list {
  const char *name;
  flagword flags;
  bfd_vma vma_val;
  bfd_vma lma_val;
  struct section_list *next;
};

struct section_hash_entry {
  struct bfd_hash_entry root;
  asection section;
};

struct fake_section_arg {
  bfd_boolean failed;
  void *link_info;
};

struct pe_tdata {
  struct {
    unsigned int FileAlignment;
    unsigned int SizeOfHeapCommit;
    unsigned int SizeOfHeapReserve;
    bfd_vma ImageBase;
    unsigned int SectionAlignment;
    unsigned int SizeOfStackCommit;
    unsigned int SizeOfStackReserve;
    int Subsystem;
    int MajorSubsystemVersion;
    int MinorSubsystemVersion;
  } pe_opthdr;
  void *sections;
  void *symtab;
  void *aux;
  int symcount;
  int num_sections;
  int timestamp;
  int pointer_to_symbol_table;
  int number_of_symbols;
  int size_of_optional_header;
  int characteristics;
};
typedef struct pe_tdata pe_data_type;
#define pe_data(abfd) ((pe_data_type *)(abfd)->tdata.coff_obj_data)
#define PE_DEF_FILE_ALIGNMENT 0x200
#define PE_DEF_SECTION_ALIGNMENT 0x1000

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_GNU_HASH 0x6ffffff6
#define SHT_GNU_versym 0x6fffffff
#define SHT_GNU_verdef 0x6ffffffd
#define SHT_GNU_verneed 0x6ffffffe
#define SHT_GNU_ATTRIBUTES 0x6ffffff5
#define SHT_GNU_LIBLIST 0x6ffffff7
#define SHT_LOOS 0x60000000
#define SHT_HIOS 0x6fffffff
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0x8fffffff

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MERGE 0x10
#define SHF_STRINGS 0x20
#define SHF_INFO_LINK 0x40
#define SHF_OS_NONCONFORMING 0x100
#define SHF_GROUP 0x200
#define SHF_TLS 0x400
#define SHF_EXCLUDE 0x80000000

#define SHN_UNDEF 0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC 0xff00
#define SHN_HIPROC 0xff1f
#define SHN_LOOS 0xff20
#define SHN_HIOS 0xff3f
#define SHN_ABS 0xfff1
#define SHN_COMMON 0xfff2
#define SHN_XINDEX 0xffff
#define SHN_BAD (unsigned)-1

#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_COMMON 5
#define STT_TLS 6
#define STT_RELC 8
#define STT_SRELC 9
#define STT_GNU_IFUNC 10

#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_GNU_UNIQUE 10

#define ELF_ST_BIND(val) (((unsigned int)(val)) >> 4)
#define ELF_ST_TYPE(val) ((val) & 0xf)
#define ELF_ST_INFO(bind, type) (((bind) << 4) + ((type) & 0xf))

#define EM_NONE 0
#define EM_386 3
#define EM_SPARC 2
#define EM_SPARC32PLUS 18
#define EM_SPARCV9 43
#define EM_OLD_SPARCV9 44
#define EM_X86_64 62
#define EM_IAMCU 6

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4

#define EV_NONE 0
#define EV_CURRENT 1

#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_OSABI 7
#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2
#define ELFCLASS ELFCLASS64
#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2
#define ELFOSABI_NONE 0

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_TLS 7

#define ELF_SECTION_IN_SEGMENT(sec, seg)                                       \
  (((sec)->sh_addr >= (seg)->p_vaddr) &&                                       \
   ((sec)->sh_addr + (sec)->sh_size <= (seg)->p_vaddr + (seg)->p_memsz))

#define IS_VALID_GROUP_SECTION_HEADER(hdr, entry_size)                         \
  ((hdr)->sh_type == SHT_GROUP && (hdr)->sh_info != 0 &&                       \
   (hdr)->sh_info < elf_numsections(abfd))

#define NUM_SHDR_ENTRIES(x) elf_numsections(abfd)
#define PN_XNUM 0xffff
#define GRP_ENTRY_SIZE 4
#define GNU_BUILD_ATTRS_SECTION_NAME ".gnu.build.attributes"

#define elf_elfheader(x) ((Elf_Internal_Ehdr *)(x)->tdata.elf_obj_data)
#define elf_elfsections(x) ((x)->tdata.elf_obj_data->elf_sect_ptr)
#define elf_numsections(x) ((x)->tdata.elf_obj_data->num_elf_sections)
#define elf_symtab_hdr(x) ((x)->tdata.elf_obj_data->symtab_hdr)
#define elf_strtab_sec(x) ((x)->tdata.elf_obj_data->strtab_sec)
#define elf_shstrtab_sec(x) ((x)->tdata.elf_obj_data->shstrtab_sec)
#define elf_symtab_shndx_list(x) ((x)->tdata.elf_obj_data->symtab_shndx_list)
#define elf_onesymtab(x) ((x)->tdata.elf_obj_data->symtab_section)
#define elf_dynsymtab(x) ((x)->tdata.elf_obj_data->dynsymtab_section)
#define elf_dynversym(x) ((x)->tdata.elf_obj_data->dynversym_section)
#define elf_dynverdef(x) ((x)->tdata.elf_obj_data->dynverdef_section)
#define elf_dynverref(x) ((x)->tdata.elf_obj_data->dynverref_section)
#define elf_tdata(x) ((x)->tdata.elf_obj_data)
#define elf_section_type(sec) ((sec)->sh_type)
#define elf_section_flags(sec) ((sec)->sh_flags)
#define elf_section_list(x) ((x)->tdata.elf_obj_data->elf_sect_ptr)
#define elf_section_syms(x) ((x)->tdata.elf_obj_data->section_syms)
#define elf_num_section_syms(x) ((x)->tdata.elf_obj_data->num_section_syms)
#define elf_next_file_pos(x) ((x)->tdata.elf_obj_data->next_file_pos)
#define elf_shstrtab(x) ((x)->tdata.elf_obj_data->shstrtab_ptr)

#define elf_section_data(sec)                                                  \
  ((struct bfd_elf_section_data *)(sec)->used_by_bfd)

#define BFD_SEND(bfd, message, arglist) (((bfd)->xvec->message)arglist)
#define BFD_SEND_FMT(bfd, message, arglist) (((bfd)->xvec->message)arglist)
#define BFD_ALIGN(this, boundary)                                              \
  ((((bfd_vma)(this) + (boundary) - 1) & (~((bfd_vma)(boundary) - 1))))
#define BFD_ASSERT(x)                                                          \
  do {                                                                         \
    if (!(x))                                                                  \
      bfd_assert(__FILE__, __LINE__);                                          \
  } while (0)
#define BFD_PLUGIN 0x100000
#define BFD_COMPRESS 0x4000
#define BFD_COMPRESS_GABI 0x20000
#define BFD_DECOMPRESS 0x8000
#define BFD_CONVERT_ELF_COMMON 0x10000
#define BFD_USE_ELF_STT_COMMON 0x20000

#define D_PAGED 0x100
#define DYNAMIC 0x40
#define HAS_RELOC 0x1
#define HAS_SYMS 0x10
#define EXEC_P 0x2

#define SECTION_CONTEXT_SET_VMA 0x1
#define SECTION_CONTEXT_SET_LMA 0x2
#define SECTION_CONTEXT_ALTER_VMA 0x4
#define SECTION_CONTEXT_ALTER_LMA 0x8
#define SECTION_CONTEXT_SET_FLAGS 0x10

#define MAP_STRTAB 0
#define MAP_SYM_SHNDX 1
#define MAP_ONESYMTAB 2
#define MAP_DYNSYMTAB 3
#define MAP_SHSTRTAB 4

#define FOPEN_WB "wb"

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

extern const bfd_target *const *bfd_target_vector;
extern const bfd_target *const *bfd_default_vector;
extern const bfd_target *const *bfd_associated_vector;
extern unsigned int _bfd_target_vector_entries;
extern const bfd_target binary_vec;
extern asection *bfd_abs_section_ptr;
extern asection *bfd_com_section_ptr;
extern asection *bfd_und_section_ptr;
extern flagword bfd_flags_to_clear;
extern flagword bfd_flags_to_set;

extern bfd_hash_entry *bfd_hash_newfunc(bfd_hash_entry *entry,
                                        bfd_hash_table *table,
                                        const char *string);
extern bfd_hash_entry *bfd_hash_allocate(bfd_hash_table *table,
                                         unsigned int size);
extern unsigned long bfd_hash_hash(const char *string, unsigned long *hashp);

struct objalloc;
extern void *objalloc_alloc(struct objalloc *, unsigned long);
extern unsigned long higher_prime_number(unsigned long);

struct bfd_preserve {
  void *marker;
  void *tdata;
  bfd_format format;
  void *arelt_data;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  struct bfd_symbol **outsymbols;
  bfd_size_type symcount;
  unsigned int flags;
  bfd_vma start_address;
  unsigned int output_has_begun;
};

extern bfd_boolean bfd_check_format(bfd *abfd, bfd_format format);
extern bfd_boolean bfd_check_format_matches(bfd *abfd, bfd_format format,
                                            char ***matching);
extern bfd_boolean bfd_set_format(bfd *abfd, bfd_format format);
extern bfd_format bfd_get_format(bfd *abfd);
extern const char *bfd_get_target(bfd *abfd);
extern const char *bfd_get_filename(bfd *abfd);
extern char *bfd_get_archive_filename(bfd *abfd);
extern enum bfd_flavour bfd_get_flavour(bfd *abfd);
extern bfd_boolean bfd_close(bfd *abfd);
extern bfd_boolean bfd_close_all_done(bfd *abfd);
extern bfd *bfd_openr(const char *filename, const char *target);
extern bfd *bfd_openw(const char *filename, const char *target);
extern bfd_boolean bfd_set_arch_mach(bfd *abfd, enum bfd_architecture arch,
                                     unsigned long mach);
extern bfd_boolean bfd_default_set_arch_mach(bfd *abfd,
                                             enum bfd_architecture arch,
                                             unsigned long mach);
extern const struct bfd_arch_info *bfd_get_arch_info(bfd *abfd);
extern enum bfd_architecture bfd_get_arch(bfd *abfd);
extern unsigned long bfd_get_mach(bfd *abfd);
extern unsigned int bfd_get_symcount(bfd *abfd);
extern asymbol **bfd_get_outsymbols(bfd *abfd);
extern long bfd_get_symtab_upper_bound(bfd *abfd);
extern long bfd_canonicalize_symtab(bfd *abfd, asymbol **location);
extern bfd_size_type bfd_get_section_size(const asection *sec);
extern bfd_vma bfd_get_section_vma(bfd *abfd, const asection *sec);
extern flagword bfd_get_section_flags(bfd *abfd, const asection *sec);
extern bfd_boolean bfd_set_section_size(bfd *abfd, asection *sec,
                                        bfd_size_type val);
extern bfd_boolean bfd_set_section_vma(bfd *abfd, asection *sec, bfd_vma val);
extern bfd_boolean bfd_set_section_flags(bfd *abfd, asection *sec,
                                         flagword flags);
extern bfd_boolean bfd_set_section_alignment(bfd *abfd, asection *sec,
                                             unsigned int val);
extern bfd_boolean bfd_set_section_contents(bfd *abfd, asection *sec,
                                            const void *loc, file_ptr offset,
                                            bfd_size_type count);
extern bfd_boolean bfd_get_full_section_contents(bfd *abfd, asection *sec,
                                                 bfd_byte **location);
extern bfd_byte *bfd_malloc_and_get_section(bfd *abfd, asection *sec,
                                            bfd_size_type *size);
extern asection *bfd_get_section_by_name(bfd *abfd, const char *name);
extern asection *bfd_make_section_with_flags(bfd *, const char *name,
                                             flagword flags);
extern void bfd_map_over_sections(
    bfd *abfd, void (*func)(bfd *abfd, asection *sect, void *obj), void *obj);
extern unsigned int bfd_count_sections(bfd *abfd);
extern bfd_vma bfd_get_start_address(bfd *abfd);
extern bfd_boolean bfd_set_start_address(bfd *abfd, bfd_vma vma);
extern bfd_boolean bfd_set_symtab(bfd *abfd, asymbol **location,
                                  unsigned int count);
extern bfd_boolean bfd_set_file_flags(bfd *abfd, flagword flags);
extern flagword bfd_get_file_flags(bfd *abfd);
extern bfd_size_type bfd_get_arch_size(bfd *abfd);
extern int bfd_get_sign_extend_vma(bfd *abfd);
extern bfd_boolean bfd_has_map(bfd *abfd);
extern bfd_boolean bfd_is_abs_section(const asection *sec);
extern bfd_boolean bfd_is_und_section(const asection *sec);
extern bfd_boolean bfd_is_com_section(const asection *sec);
extern bfd_boolean bfd_is_const_section(const asection *sec);
extern void bfd_assert(const char *file, int line);
extern void _bfd_error_handler(const char *fmt, ...);
extern void bfd_set_error(bfd_error_type error_tag);
extern bfd_error_type bfd_get_error(void);
extern void bfd_nonfatal_message(const char *filename, const char *routine,
                                 const char *explanation, ...);
extern void bfd_perror(const char *message);
extern char *bfd_printable_arch_mach(enum bfd_architecture arch,
                                     unsigned long mach);
extern bfd_boolean bfd_reinit(bfd *abfd);
extern bfd_boolean bfd_seek(bfd *abfd, file_ptr position, int direction);
extern file_ptr bfd_tell(bfd *abfd);
extern bfd_size_type bfd_bread(void *ptr, bfd_size_type size, bfd *abfd);
extern bfd_size_type bfd_bwrite(const void *ptr, bfd_size_type size, bfd *abfd);
extern bfd_boolean bfd_read_p(bfd *abfd);
extern bfd_boolean bfd_write_p(bfd *abfd);
extern void *bfd_malloc(bfd_size_type size);
extern void *bfd_alloc(bfd *abfd, bfd_size_type size);
extern void *bfd_alloc2(bfd *abfd, bfd_size_type nmemb, bfd_size_type size);
extern void *bfd_zalloc2(bfd *abfd, bfd_size_type nmemb, bfd_size_type size);
extern void bfd_release(bfd *abfd, void *all);
extern bfd_boolean bfd_alt_mach_code(bfd *abfd, int alternative);
extern flagword bfd_applicable_file_flags(bfd *abfd);
extern bfd_boolean bfd_copy_private_bfd_data(bfd *ibfd, bfd *obfd);
extern bfd_boolean bfd_preserve_save(bfd *abfd, void *preserve);
extern void bfd_preserve_restore(bfd *abfd, void *preserve);
extern void bfd_preserve_finish(bfd *abfd, void *preserve);
extern void bfd_rename_section(bfd *abfd, asection *sec, const char *newname);
extern void bfd_section_list_append(bfd *abfd, asection *newsect);
extern bfd_vma bfd_section_lma(bfd *abfd, const asection *sec);
extern bfd_vma bfd_section_lma(bfd *abfd, const asection *sec);
extern bfd_boolean bfd_init_section_compress_status(bfd *abfd, asection *sec);
extern bfd_boolean bfd_init_section_decompress_status(bfd *abfd, asection *sec);
extern asection *bfd_create_gnu_debuglink_section(bfd *abfd,
                                                  const char *filename);
extern bfd_boolean bfd_fill_in_gnu_debuglink_section(bfd *abfd, asection *sec,
                                                     const char *filename);
extern unsigned int bfd_log2(bfd_vma x);
extern void bfd_elf_set_group_contents(bfd *abfd, asection *sec,
                                       void *location);
extern char *bfd_elf_string_from_elf_section(bfd *abfd, unsigned shindex,
                                             unsigned str_offset);
extern Elf_Internal_Sym *
bfd_elf_get_elf_syms(bfd *abfd, Elf_Internal_Shdr *symtab_hdr,
                     bfd_size_type symcount, bfd_size_type local_symcount,
                     asymbol **syms, void *psymnum, void *pvernum);
extern void bfd_sprintf_vma(bfd *abfd, char *buf, bfd_vma value);
extern void bfd_fprintf_vma(bfd *abfd, void *stream, bfd_vma value);
extern bfd_boolean bfd_pei_p(bfd *abfd);

extern struct elf_strtab_hash *_bfd_elf_strtab_init(void);
extern void _bfd_elf_strtab_free(struct elf_strtab_hash *);
extern bfd_size_type _bfd_elf_strtab_add(struct elf_strtab_hash *, const char *,
                                         bfd_boolean);
extern void _bfd_elf_strtab_finalize(struct elf_strtab_hash *);
extern bfd_size_type _bfd_elf_strtab_size(struct elf_strtab_hash *);
extern bfd_size_type _bfd_elf_strtab_offset(struct elf_strtab_hash *,
                                            bfd_size_type);
extern bfd_boolean _bfd_elf_strtab_emit(bfd *abfd, struct elf_strtab_hash *);

extern const struct elf_backend_data *get_elf_backend_data(bfd *abfd);
extern void elf_swap_ehdr_in(bfd *, const Elf_External_Ehdr *,
                             Elf_Internal_Ehdr *);
extern void elf_swap_shdr_in(bfd *, const Elf_External_Shdr *,
                             Elf_Internal_Shdr *);
extern void elf_swap_phdr_in(bfd *, const Elf_External_Phdr *,
                             Elf_Internal_Phdr *);
extern void _bfd_elf_swap_versym_in(bfd *, const Elf_External_Versym *,
                                    Elf_Internal_Versym *);
extern bfd_boolean _bfd_elf_setup_sections(bfd *abfd);
extern bfd_boolean _bfd_elf_slurp_version_tables(bfd *abfd, bfd_boolean);
extern unsigned int _bfd_elf_section_from_bfd_section(bfd *, asection *);
extern bfd_boolean _bfd_elf_parse_attributes(bfd *, Elf_Internal_Shdr *);
extern file_ptr _bfd_elf_assign_file_position_for_section(Elf_Internal_Shdr *,
                                                          file_ptr,
                                                          bfd_boolean);
extern bfd_boolean _bfd_elf_assign_file_positions_for_non_load(bfd *);

extern bfd_boolean sym_is_global(bfd *abfd, asymbol *sym);

extern void *bfd_zalloc(bfd *abfd, bfd_size_type size);
extern char *convert_zdebug_to_debug(bfd *abfd, const char *name);
extern off_t get_file_size(const char *filename);
extern void non_fatal(const char *fmt, ...);
extern void list_matching_formats(char **matching);
extern void set_long_section_mode(bfd *obfd, bfd *ibfd, bfd_boolean long_names);
extern bfd_boolean copy_archive(bfd *ibfd, bfd *obfd, const char *output_target,
                                bfd_boolean force_output,
                                const bfd_arch_info_type *input_arch);
extern char *_(const char *msgid);
extern bfd_boolean elf_file_p(Elf_Internal_Ehdr *ehdr);
extern bfd_boolean bfd_header_big_endian(bfd *abfd);
extern bfd_boolean bfd_header_little_endian(bfd *abfd);
extern bfd_boolean elf_parse_notes(bfd *abfd, char *contents,
                                   bfd_size_type size, file_ptr offset,
                                   bfd_vma alignment);
extern bfd_boolean
bfd_is_section_compressed_with_header(bfd *abfd, asection *sec,
                                      int *compression_header_size,
                                      bfd_size_type *uncompressed_size);
extern char *bfd_elf_sym_name(bfd *abfd, Elf_Internal_Shdr *symtab_hdr,
                              Elf_Internal_Sym *sym, asection *sec);
extern bfd_boolean bfd_section_from_shdr(bfd *abfd, unsigned int shindex);
extern bfd_boolean setup_group(bfd *abfd, Elf_Internal_Shdr *hdr,
                               asection *sec);
extern asection *bfd_section_from_elf_index(bfd *abfd, unsigned int sec_index);
extern bfd_boolean _bfd_elf_make_section_from_shdr(bfd *abfd,
                                                   Elf_Internal_Shdr *hdr,
                                                   const char *name,
                                                   int shindex);
extern bfd_boolean
_bfd_elf_compute_section_file_positions(bfd *abfd,
                                        struct bfd_link_info *link_info);
extern bfd_boolean _bfd_elf_write_object_contents(bfd *abfd);
extern bfd_boolean _bfd_elf_assign_file_positions_for_non_load(bfd *abfd);
extern bfd_boolean assign_file_positions_except_relocs(bfd *abfd,
                                                       void *link_info);
extern bfd_boolean assign_section_numbers(bfd *abfd, void *link_info);
extern void elf_fake_sections(bfd *abfd, asection *sec, void *arg);
extern bfd_boolean prep_headers(bfd *abfd);
extern bfd_boolean elf_linker(bfd *abfd);
extern bfd_boolean bfd_write_p(bfd *abfd);
extern bfd_boolean bfd_read_p(bfd *abfd);
extern bfd_boolean bfd_close_all_done(bfd *abfd);
extern void *xmalloc(bfd_size_type size);
extern int verbose;
extern int extract_symbol;
extern int strip_symbols;
extern int discard_locals;
extern int localize_hidden;
extern int convert_debugging;
extern int add_symbols;
extern int change_leading_char;
extern int remove_leading_char;
extern int weaken;
extern int use_alt_mach_code;
extern int is_strip;
extern bfd_vma set_start;
extern bfd_boolean set_start_set;
extern bfd_vma change_start;
extern bfd_vma pe_file_alignment;
extern bfd_vma pe_heap_commit;
extern bfd_vma pe_heap_reserve;
extern bfd_vma pe_image_base;
extern bfd_vma pe_section_alignment;
extern bfd_vma pe_stack_commit;
extern bfd_vma pe_stack_reserve;
extern int pe_subsystem;
extern int pe_major_subsystem_version;
extern int pe_minor_subsystem_version;
extern bfd_vma pad_to;
extern bfd_boolean pad_to_set;
extern bfd_boolean gap_fill_set;
extern int gap_fill;
extern asymbol **isympp;
extern asymbol **osympp;
extern bfd_byte *merged_notes;
extern bfd_size_type merged_size;
extern bfd_boolean merge_notes;
extern char *gnu_debuglink_filename;
extern struct section_add *add_sections;
extern struct section_add *update_sections;
extern struct section_add *dump_sections;
extern struct section_list *section_rename_list;
extern void *strip_specific_htab;
extern void *keep_specific_htab;
extern void *localize_specific_htab;
extern void *globalize_specific_htab;
extern void *keepglobal_specific_htab;
extern void *weaken_specific_htab;
extern void *redefine_specific_htab;
extern char *prefix_symbols_string;
extern void *sections_removed;
extern void *sections_copied;
extern bfd_vma section_id;
extern int status;
extern enum {
  debug_none,
  compress,
  compress_zlib,
  compress_gnu_zlib,
  compress_gabi_zlib,
  decompress,
  compressed
} do_debug_sections;
extern enum { stt_none, elf_stt_common, no_elf_stt_common } do_elf_stt_common;
extern bfd_boolean long_section_names;
extern const char *input_filename;
extern const char *output_filename;
extern const char *input_target;
extern const char *output_target;
extern const bfd_arch_info_type *input_arch;
extern bfd_boolean force_output_target;

extern void setup_section(bfd *ibfd, asection *isection, void *obfd);
extern void setup_bfd_headers(bfd *ibfd, bfd *obfd);
extern struct section_list *
find_section_list(const char *name, bfd_boolean create, flagword context);
extern long filter_symbols(bfd *ibfd, bfd *obfd, asymbol **osyms,
                           asymbol **isyms, long symcount);
extern void *read_debugging_info(bfd *abfd, asymbol **syms, long symcount,
                                 bfd_boolean include_local);
extern bfd_boolean write_debugging_info(bfd *abfd, void *dhandle,
                                        long *symcount, asymbol ***syms);
extern void mark_symbols_used_in_relocations(bfd *abfd, asection *sec,
                                             void *syms);
extern void copy_relocations_in_section(bfd *ibfd, asection *isection,
                                        void *obfd);
extern void copy_section(bfd *ibfd, asection *isection, void *obfd);
extern void get_sections(bfd *abfd, asection *sec, void *set);
extern int compare_section_lma(const void *arg1, const void *arg2);
extern bfd_boolean is_merged_note_section(bfd *abfd, asection *sec);
extern bfd_size_type merge_gnu_build_notes(bfd *abfd, asection *sec,
                                           bfd_size_type size, bfd_byte *notes);
extern unsigned long htab_elements(void *htab);
extern struct section_hash_entry *section_hash_lookup(void *table,
                                                      const char *string,
                                                      bfd_boolean create,
                                                      bfd_boolean copy);

extern bfd_vma bfd_section_size(bfd *abfd, const asection *sec);
extern bfd_vma bfd_section_lma(bfd *abfd, const asection *sec);
extern bfd_vma bfd_section_alignment(bfd *abfd, const asection *sec);

#define elf_next_in_group(sec) ((sec)->next_in_group)
#define bfd_get_symcount(abfd) ((abfd)->symcount)
#define bfd_get_outsymbols(abfd) ((abfd)->outsymbols)
#define bfd_get_format(abfd) ((abfd)->format)
#define bfd_get_file_flags(abfd) ((abfd)->flags)
#define bfd_get_start_address(abfd) ((abfd)->start_address)
#define bfd_get_arch(abfd) ((abfd)->arch_info->arch)
#define bfd_get_mach(abfd) ((abfd)->arch_info->mach)
#define bfd_get_arch_info(abfd) ((abfd)->arch_info)
#define bfd_get_target(abfd) ((abfd)->xvec->name)
#define bfd_get_filename(abfd) ((abfd)->filename)
#define bfd_get_archive_filename(abfd) ((abfd)->filename)
#define bfd_get_flavour(abfd) ((abfd)->flavour)
#define bfd_section_alignment(abfd, sec) ((sec)->alignment_power)
#define bfd_section_size(abfd, sec) ((sec)->size)
#define bfd_section_lma(abfd, sec) ((sec)->lma)
#define bfd_section_vma(abfd, sec) ((sec)->vma)
#define bfd_get_section_size(sec) ((sec)->size)
#define bfd_get_section_vma(abfd, sec) ((sec)->vma)
#define bfd_get_section_flags(abfd, sec) ((sec)->flags)
#define bfd_elf_string_from_elf_section(abfd, shindex, offset) ((char *)0)

/* === Original bad.c content === */


static bfd_boolean ignore_section_sym(bfd *abfd, asymbol *sym) {
  elf_symbol_type *type_ptr;

  if ((sym->flags & BSF_SECTION_SYM) == 0)
    return FALSE;

  type_ptr = elf_symbol_from(abfd, sym);
  return ((type_ptr != NULL && type_ptr->internal_elf_sym.st_shndx != 0 &&
           bfd_is_abs_section(sym->section)) ||
          !(sym->section->owner == abfd ||
            (sym->section->output_section != NULL &&
             sym->section->output_section->owner == abfd &&
             sym->section->output_offset == 0) ||
            bfd_is_abs_section(sym->section)));
}

static bfd_boolean elf_map_symbols(bfd *abfd, unsigned int *pnum_locals) {
  unsigned int symcount = bfd_get_symcount(abfd);
  asymbol **syms = bfd_get_outsymbols(abfd);
  asymbol **sect_syms;
  unsigned int num_locals = 0;
  unsigned int num_globals = 0;
  unsigned int num_locals2 = 0;
  unsigned int num_globals2 = 0;
  unsigned int max_index = 0;
  unsigned int idx;
  asection *asect;
  asymbol **new_syms;

#ifdef DEBUG
  fprintf(stderr, "elf_map_symbols\n");
  fflush(stderr);
#endif

  for (asect = abfd->sections; asect; asect = asect->next) {
    if (max_index < asect->index)
      max_index = asect->index;
  }

  max_index++;
  sect_syms = (asymbol **)bfd_zalloc2(abfd, max_index, sizeof(asymbol *));
  if (sect_syms == NULL)
    return FALSE;
  elf_section_syms(abfd) = sect_syms;
  elf_num_section_syms(abfd) = max_index;

  /* Init sect_syms entries for any section symbols we have already
     decided to output.  */
  for (idx = 0; idx < symcount; idx++) {
    asymbol *sym = syms[idx];

    if ((sym->flags & BSF_SECTION_SYM) != 0 && sym->value == 0 &&
        !ignore_section_sym(abfd, sym) && !bfd_is_abs_section(sym->section)) {
      asection *sec = sym->section;

      if (sec->owner != abfd)
        sec = sec->output_section;

      sect_syms[sec->index] = syms[idx];
    }
  }

  /* Classify all of the symbols.  */
  for (idx = 0; idx < symcount; idx++) {
    if (sym_is_global(abfd, syms[idx]))
      num_globals++;
    else if (!ignore_section_sym(abfd, syms[idx]))
      num_locals++;
  }

  /* We will be adding a section symbol for each normal BFD section.  Most
     sections will already have a section symbol in outsymbols, but
     eg. SHT_GROUP sections will not, and we need the section symbol mapped
     at least in that case.  */
  for (asect = abfd->sections; asect; asect = asect->next) {
    if (sect_syms[asect->index] == NULL) {
      if (!sym_is_global(abfd, asect->symbol))
        num_locals++;
      else
        num_globals++;
    }
  }

  /* Now sort the symbols so the local symbols are first.  */
  new_syms =
      (asymbol **)bfd_alloc2(abfd, num_locals + num_globals, sizeof(asymbol *));

  if (new_syms == NULL)
    return FALSE;

  for (idx = 0; idx < symcount; idx++) {
    asymbol *sym = syms[idx];
    unsigned int i;

    if (sym_is_global(abfd, sym))
      i = num_locals + num_globals2++;
    else if (!ignore_section_sym(abfd, sym))
      i = num_locals2++;
    else
      continue;
    new_syms[i] = sym;
    sym->udata.i = i + 1;
  }
  for (asect = abfd->sections; asect; asect = asect->next) {
    if (sect_syms[asect->index] == NULL) {
      asymbol *sym = asect->symbol;
      unsigned int i;

      sect_syms[asect->index] = sym;
      if (!sym_is_global(abfd, sym))
        i = num_locals2++;
      else
        i = num_locals + num_globals2++;
      new_syms[i] = sym;
      sym->udata.i = i + 1;
    }
  }

  bfd_set_symtab(abfd, new_syms, num_locals + num_globals);

  *pnum_locals = num_locals;
  return TRUE;
}

static bfd_boolean swap_out_syms(bfd *abfd, struct elf_strtab_hash **sttp,
                                 int relocatable_p) {
  const struct elf_backend_data *bed;
  int symcount;
  asymbol **syms;
  struct elf_strtab_hash *stt;
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Shdr *symtab_shndx_hdr;
  Elf_Internal_Shdr *symstrtab_hdr;
  struct elf_sym_strtab *symstrtab;
  bfd_byte *outbound_syms;
  bfd_byte *outbound_shndx;
  unsigned long outbound_syms_index;
  unsigned long outbound_shndx_index;
  int idx;
  unsigned int num_locals;
  bfd_size_type amt;
  bfd_boolean name_local_sections;

  if (!elf_map_symbols(abfd, &num_locals))
    return FALSE;

  /* Dump out the symtabs.  */
  stt = _bfd_elf_strtab_init();
  if (stt == NULL)
    return FALSE;

  bed = get_elf_backend_data(abfd);
  symcount = bfd_get_symcount(abfd);
  symtab_hdr = &elf_tdata(abfd)->symtab_hdr;
  symtab_hdr->sh_type = SHT_SYMTAB;
  symtab_hdr->sh_entsize = bed->s->sizeof_sym;
  symtab_hdr->sh_size = symtab_hdr->sh_entsize * (symcount + 1);
  symtab_hdr->sh_info = num_locals + 1;
  symtab_hdr->sh_addralign = (bfd_vma)1 << bed->s->log_file_align;

  symstrtab_hdr = &elf_tdata(abfd)->strtab_hdr;
  symstrtab_hdr->sh_type = SHT_STRTAB;

  /* Allocate buffer to swap out the .strtab section.  */
  symstrtab =
      (struct elf_sym_strtab *)bfd_malloc((symcount + 1) * sizeof(*symstrtab));
  if (symstrtab == NULL) {
    _bfd_elf_strtab_free(stt);
    return FALSE;
  }

  outbound_syms =
      (bfd_byte *)bfd_alloc2(abfd, 1 + symcount, bed->s->sizeof_sym);
  if (outbound_syms == NULL) {
  error_return:
    _bfd_elf_strtab_free(stt);
    free(symstrtab);
    return FALSE;
  }
  symtab_hdr->contents = outbound_syms;
  outbound_syms_index = 0;

  outbound_shndx = NULL;
  outbound_shndx_index = 0;

  if (elf_symtab_shndx_list(abfd)) {
    symtab_shndx_hdr = &elf_symtab_shndx_list(abfd)->hdr;
    if (symtab_shndx_hdr->sh_name != 0) {
      amt = (bfd_size_type)(1 + symcount) * sizeof(Elf_External_Sym_Shndx);
      outbound_shndx = (bfd_byte *)bfd_zalloc2(abfd, 1 + symcount,
                                               sizeof(Elf_External_Sym_Shndx));
      if (outbound_shndx == NULL)
        goto error_return;

      symtab_shndx_hdr->contents = outbound_shndx;
      symtab_shndx_hdr->sh_type = SHT_SYMTAB_SHNDX;
      symtab_shndx_hdr->sh_size = amt;
      symtab_shndx_hdr->sh_addralign = sizeof(Elf_External_Sym_Shndx);
      symtab_shndx_hdr->sh_entsize = sizeof(Elf_External_Sym_Shndx);
    }
    /* FIXME: What about any other headers in the list ?  */
  }

  /* Now generate the data (for "contents").  */
  {
    /* Fill in zeroth symbol and swap it out.  */
    Elf_Internal_Sym sym;
    sym.st_name = 0;
    sym.st_value = 0;
    sym.st_size = 0;
    sym.st_info = 0;
    sym.st_other = 0;
    sym.st_shndx = SHN_UNDEF;
    sym.st_target_internal = 0;
    symstrtab[0].sym = sym;
    symstrtab[0].dest_index = outbound_syms_index;
    symstrtab[0].destshndx_index = outbound_shndx_index;
    outbound_syms_index++;
    if (outbound_shndx != NULL)
      outbound_shndx_index++;
  }

  name_local_sections = (bed->elf_backend_name_local_section_symbols &&
                         bed->elf_backend_name_local_section_symbols(abfd));

  syms = bfd_get_outsymbols(abfd);
  for (idx = 0; idx < symcount;) {
    Elf_Internal_Sym sym;
    bfd_vma value = syms[idx]->value;
    elf_symbol_type *type_ptr;
    flagword flags = syms[idx]->flags;
    int type;

    if (!name_local_sections &&
        (flags & (BSF_SECTION_SYM | BSF_GLOBAL)) == BSF_SECTION_SYM) {
      /* Local section symbols have no name.  */
      sym.st_name = (unsigned long)-1;
    } else {
      /* Call _bfd_elf_strtab_offset after _bfd_elf_strtab_finalize
         to get the final offset for st_name.  */
      sym.st_name =
          (unsigned long)_bfd_elf_strtab_add(stt, syms[idx]->name, FALSE);
      if (sym.st_name == (unsigned long)-1)
        goto error_return;
    }

    type_ptr = elf_symbol_from(abfd, syms[idx]);

    if ((flags & BSF_SECTION_SYM) == 0 &&
        bfd_is_com_section(syms[idx]->section)) {
      /* ELF common symbols put the alignment into the `value' field,
         and the size into the `size' field.  This is backwards from
         how BFD handles it, so reverse it here.  */
      sym.st_size = value;
      if (type_ptr == NULL || type_ptr->internal_elf_sym.st_value == 0)
        sym.st_value = value >= 16 ? 16 : (1 << bfd_log2(value));
      else
        sym.st_value = type_ptr->internal_elf_sym.st_value;
      sym.st_shndx =
          _bfd_elf_section_from_bfd_section(abfd, syms[idx]->section);
    } else {
      asection *sec = syms[idx]->section;
      unsigned int shndx;

      if (sec->output_section) {
        value += sec->output_offset;
        sec = sec->output_section;
      }

      /* Don't add in the section vma for relocatable output.  */
      if (!relocatable_p)
        value += sec->vma;
      sym.st_value = value;
      sym.st_size = type_ptr ? type_ptr->internal_elf_sym.st_size : 0;

      if (bfd_is_abs_section(sec) && type_ptr != NULL &&
          type_ptr->internal_elf_sym.st_shndx != 0) {
        /* This symbol is in a real ELF section which we did
           not create as a BFD section.  Undo the mapping done
           by copy_private_symbol_data.  */
        shndx = type_ptr->internal_elf_sym.st_shndx;
        switch (shndx) {
        case MAP_ONESYMTAB:
          shndx = elf_onesymtab(abfd);
          break;
        case MAP_DYNSYMTAB:
          shndx = elf_dynsymtab(abfd);
          break;
        case MAP_STRTAB:
          shndx = elf_strtab_sec(abfd);
          break;
        case MAP_SHSTRTAB:
          shndx = elf_shstrtab_sec(abfd);
          break;
        case MAP_SYM_SHNDX:
          if (elf_symtab_shndx_list(abfd))
            shndx = elf_symtab_shndx_list(abfd)->ndx;
          break;
        default:
          shndx = SHN_ABS;
          break;
        }
      } else {
        shndx = _bfd_elf_section_from_bfd_section(abfd, sec);

        if (shndx == SHN_BAD) {
          asection *sec2;

          /* Writing this would be a hell of a lot easier if
             we had some decent documentation on bfd, and
             knew what to expect of the library, and what to
             demand of applications.  For example, it
             appears that `objcopy' might not set the
             section of a symbol to be a section that is
             actually in the output file.  */
          sec2 = bfd_get_section_by_name(abfd, sec->name);
          if (sec2 != NULL)
            shndx = _bfd_elf_section_from_bfd_section(abfd, sec2);
          if (shndx == SHN_BAD) {
            /* xgettext:c-format */
            _bfd_error_handler(
                _("unable to find equivalent output section"
                  " for symbol '%s' from section '%s'"),
                syms[idx]->name ? syms[idx]->name : "<Local sym>", sec->name);
            bfd_set_error(bfd_error_invalid_operation);
            goto error_return;
          }
        }
      }

      sym.st_shndx = shndx;
    }

    if ((flags & BSF_THREAD_LOCAL) != 0)
      type = STT_TLS;
    else if ((flags & BSF_GNU_INDIRECT_FUNCTION) != 0)
      type = STT_GNU_IFUNC;
    else if ((flags & BSF_FUNCTION) != 0)
      type = STT_FUNC;
    else if ((flags & BSF_OBJECT) != 0)
      type = STT_OBJECT;
    else if ((flags & BSF_RELC) != 0)
      type = STT_RELC;
    else if ((flags & BSF_SRELC) != 0)
      type = STT_SRELC;
    else
      type = STT_NOTYPE;

    if (syms[idx]->section->flags & SEC_THREAD_LOCAL)
      type = STT_TLS;

    /* Processor-specific types.  */
    if (type_ptr != NULL && bed->elf_backend_get_symbol_type)
      type = ((*bed->elf_backend_get_symbol_type)(&type_ptr->internal_elf_sym,
                                                  type));

    if (flags & BSF_SECTION_SYM) {
      if (flags & BSF_GLOBAL)
        sym.st_info = ELF_ST_INFO(STB_GLOBAL, STT_SECTION);
      else
        sym.st_info = ELF_ST_INFO(STB_LOCAL, STT_SECTION);
    } else if (bfd_is_com_section(syms[idx]->section)) {
      if (type != STT_TLS) {
        if ((abfd->flags & BFD_CONVERT_ELF_COMMON))
          type = ((abfd->flags & BFD_USE_ELF_STT_COMMON) ? STT_COMMON
                                                         : STT_OBJECT);
        else
          type = ((flags & BSF_ELF_COMMON) != 0 ? STT_COMMON : STT_OBJECT);
      }
      sym.st_info = ELF_ST_INFO(STB_GLOBAL, type);
    } else if (bfd_is_und_section(syms[idx]->section))
      sym.st_info =
          ELF_ST_INFO(((flags & BSF_WEAK) ? STB_WEAK : STB_GLOBAL), type);
    else if (flags & BSF_FILE)
      sym.st_info = ELF_ST_INFO(STB_LOCAL, STT_FILE);
    else {
      int bind = STB_LOCAL;

      if (flags & BSF_LOCAL)
        bind = STB_LOCAL;
      else if (flags & BSF_GNU_UNIQUE)
        bind = STB_GNU_UNIQUE;
      else if (flags & BSF_WEAK)
        bind = STB_WEAK;
      else if (flags & BSF_GLOBAL)
        bind = STB_GLOBAL;

      sym.st_info = ELF_ST_INFO(bind, type);
    }

    if (type_ptr != NULL) {
      sym.st_other = type_ptr->internal_elf_sym.st_other;
      sym.st_target_internal = type_ptr->internal_elf_sym.st_target_internal;
    } else {
      sym.st_other = 0;
      sym.st_target_internal = 0;
    }

    idx++;
    symstrtab[idx].sym = sym;
    symstrtab[idx].dest_index = outbound_syms_index;
    symstrtab[idx].destshndx_index = outbound_shndx_index;

    outbound_syms_index++;
    if (outbound_shndx != NULL)
      outbound_shndx_index++;
  }

  /* Finalize the .strtab section.  */
  _bfd_elf_strtab_finalize(stt);

  /* Swap out the .strtab section.  */
  for (idx = 0; idx <= symcount; idx++) {
    struct elf_sym_strtab *elfsym = &symstrtab[idx];
    if (elfsym->sym.st_name == (unsigned long)-1)
      elfsym->sym.st_name = 0;
    else
      elfsym->sym.st_name = _bfd_elf_strtab_offset(stt, elfsym->sym.st_name);
    bed->s->swap_symbol_out(
        abfd, &elfsym->sym,
        (outbound_syms + (elfsym->dest_index * bed->s->sizeof_sym)),
        (outbound_shndx +
         (elfsym->destshndx_index * sizeof(Elf_External_Sym_Shndx))));
  }
  free(symstrtab);

  *sttp = stt;
  symstrtab_hdr->sh_size = _bfd_elf_strtab_size(stt);
  symstrtab_hdr->sh_type = SHT_STRTAB;
  symstrtab_hdr->sh_flags = bed->elf_strtab_flags;
  symstrtab_hdr->sh_addr = 0;
  symstrtab_hdr->sh_entsize = 0;
  symstrtab_hdr->sh_link = 0;
  symstrtab_hdr->sh_info = 0;
  symstrtab_hdr->sh_addralign = 1;

  return TRUE;
}

bfd_boolean
_bfd_elf_compute_section_file_positions(bfd *abfd,
                                        struct bfd_link_info *link_info) {
  const struct elf_backend_data *bed = get_elf_backend_data(abfd);
  struct fake_section_arg fsargs;
  bfd_boolean failed;
  struct elf_strtab_hash *strtab = NULL;
  Elf_Internal_Shdr *shstrtab_hdr;
  bfd_boolean need_symtab;

  if (abfd->output_has_begun)
    return TRUE;

  /* Do any elf backend specific processing first.  */
  if (bed->elf_backend_begin_write_processing)
    (*bed->elf_backend_begin_write_processing)(abfd, link_info);

  if (!prep_headers(abfd))
    return FALSE;

  /* Post process the headers if necessary.  */
  (*bed->elf_backend_post_process_headers)(abfd, link_info);

  fsargs.failed = FALSE;
  fsargs.link_info = link_info;
  bfd_map_over_sections(abfd, elf_fake_sections, &fsargs);
  if (fsargs.failed)
    return FALSE;

  if (!assign_section_numbers(abfd, link_info))
    return FALSE;

  /* The backend linker builds symbol table information itself.  */
  need_symtab =
      (link_info == NULL &&
       (bfd_get_symcount(abfd) > 0 ||
        ((abfd->flags & (EXEC_P | DYNAMIC | HAS_RELOC)) == HAS_RELOC)));
  if (need_symtab) {
    /* Non-zero if doing a relocatable link.  */
    int relocatable_p = !(abfd->flags & (EXEC_P | DYNAMIC));

    if (!swap_out_syms(abfd, &strtab, relocatable_p))
      return FALSE;
  }

  failed = FALSE;
  if (link_info == NULL) {
    bfd_map_over_sections(abfd, bfd_elf_set_group_contents, &failed);
    if (failed)
      return FALSE;
  }

  shstrtab_hdr = &elf_tdata(abfd)->shstrtab_hdr;
  /* sh_name was set in prep_headers.  */
  shstrtab_hdr->sh_type = SHT_STRTAB;
  shstrtab_hdr->sh_flags = bed->elf_strtab_flags;
  shstrtab_hdr->sh_addr = 0;
  /* sh_size is set in _bfd_elf_assign_file_positions_for_non_load.  */
  shstrtab_hdr->sh_entsize = 0;
  shstrtab_hdr->sh_link = 0;
  shstrtab_hdr->sh_info = 0;
  /* sh_offset is set in _bfd_elf_assign_file_positions_for_non_load.  */
  shstrtab_hdr->sh_addralign = 1;

  if (!assign_file_positions_except_relocs(abfd, link_info))
    return FALSE;

  if (need_symtab) {
    file_ptr off;
    Elf_Internal_Shdr *hdr;

    off = elf_next_file_pos(abfd);

    hdr = &elf_symtab_hdr(abfd);
    off = _bfd_elf_assign_file_position_for_section(hdr, off, TRUE);

    if (elf_symtab_shndx_list(abfd) != NULL) {
      hdr = &elf_symtab_shndx_list(abfd)->hdr;
      if (hdr->sh_size != 0)
        off = _bfd_elf_assign_file_position_for_section(hdr, off, TRUE);
      /* FIXME: What about other symtab_shndx sections in the list ?  */
    }

    hdr = &elf_tdata(abfd)->strtab_hdr;
    off = _bfd_elf_assign_file_position_for_section(hdr, off, TRUE);

    elf_next_file_pos(abfd) = off;

    /* Now that we know where the .strtab section goes, write it
       out.  */
    if (bfd_seek(abfd, hdr->sh_offset, SEEK_SET) != 0 ||
        !_bfd_elf_strtab_emit(abfd, strtab))
      return FALSE;
    _bfd_elf_strtab_free(strtab);
  }

  abfd->output_has_begun = TRUE;

  return TRUE;
}

bfd_boolean _bfd_elf_write_object_contents(bfd *abfd) {
  const struct elf_backend_data *bed = get_elf_backend_data(abfd);
  Elf_Internal_Shdr **i_shdrp;
  bfd_boolean failed;
  unsigned int count, num_sec;
  struct elf_obj_tdata *t;

  if (!abfd->output_has_begun &&
      !_bfd_elf_compute_section_file_positions(abfd, NULL))
    return FALSE;

  i_shdrp = elf_elfsections(abfd);

  failed = FALSE;
  bfd_map_over_sections(abfd, bed->s->write_relocs, &failed);
  if (failed)
    return FALSE;

  if (!_bfd_elf_assign_file_positions_for_non_load(abfd))
    return FALSE;

  /* After writing the headers, we need to write the sections too...  */
  num_sec = elf_numsections(abfd);
  for (count = 1; count < num_sec; count++) {
    i_shdrp[count]->sh_name =
        _bfd_elf_strtab_offset(elf_shstrtab(abfd), i_shdrp[count]->sh_name);
    if (bed->elf_backend_section_processing)
      if (!(*bed->elf_backend_section_processing)(abfd, i_shdrp[count]))
        return FALSE;
    if (i_shdrp[count]->contents) {
      bfd_size_type amt = i_shdrp[count]->sh_size;

      if (bfd_seek(abfd, i_shdrp[count]->sh_offset, SEEK_SET) != 0 ||
          bfd_bwrite(i_shdrp[count]->contents, amt, abfd) != amt)
        return FALSE;
    }
  }

  /* Write out the section header names.  */
  t = elf_tdata(abfd);
  if (elf_shstrtab(abfd) != NULL &&
      (bfd_seek(abfd, t->shstrtab_hdr.sh_offset, SEEK_SET) != 0 ||
       !_bfd_elf_strtab_emit(abfd, elf_shstrtab(abfd))))
    return FALSE;

  if (bed->elf_backend_final_write_processing)
    (*bed->elf_backend_final_write_processing)(abfd, elf_linker(abfd));

  if (!bed->s->write_shdrs_and_ehdr(abfd))
    return FALSE;

  /* This is last since write_shdrs_and_ehdr can touch i_shdrp[0].  */
  if (t->o->build_id.after_write_object_contents != NULL)
    return (*t->o->build_id.after_write_object_contents)(abfd);

  return TRUE;
}

bfd_boolean bfd_close(bfd *abfd) {
  if (bfd_write_p(abfd)) {
    if (!BFD_SEND_FMT(abfd, _bfd_write_contents, (abfd)))
      return FALSE;
  }

  return bfd_close_all_done(abfd);
}


asection *bfd_section_from_elf_index(bfd *abfd, unsigned int sec_index) {
  if (sec_index >= elf_numsections(abfd))
    return NULL;
  return elf_elfsections(abfd)[sec_index]->bfd_section;
}

long elf_slurp_symbol_table(bfd *abfd, asymbol **symptrs, bfd_boolean dynamic) {
  Elf_Internal_Shdr *hdr;
  Elf_Internal_Shdr *verhdr;
  unsigned long symcount;   /* Number of external ELF symbols */
  elf_symbol_type *sym;     /* Pointer to current bfd symbol */
  elf_symbol_type *symbase; /* Buffer for generated bfd symbols */
  Elf_Internal_Sym *isym;
  Elf_Internal_Sym *isymend;
  Elf_Internal_Sym *isymbuf = NULL;
  Elf_External_Versym *xver;
  Elf_External_Versym *xverbuf = NULL;
  const struct elf_backend_data *ebd;
  bfd_size_type amt;

  /* Read each raw ELF symbol, converting from external ELF form to
     internal ELF form, and then using the information to create a
     canonical bfd symbol table entry.

     Note that we allocate the initial bfd canonical symbol buffer
     based on a one-to-one mapping of the ELF symbols to canonical
     symbols.  We actually use all the ELF symbols, so there will be no
     space left over at the end.  When we have all the symbols, we
     build the caller's pointer vector.  */

  if (!dynamic) {
    hdr = &elf_tdata(abfd)->symtab_hdr;
    verhdr = NULL;
  } else {
    hdr = &elf_tdata(abfd)->dynsymtab_hdr;
    if (elf_dynversym(abfd) == 0)
      verhdr = NULL;
    else
      verhdr = &elf_tdata(abfd)->dynversym_hdr;
    if ((elf_dynverdef(abfd) != 0 && elf_tdata(abfd)->verdef == NULL) ||
        (elf_dynverref(abfd) != 0 && elf_tdata(abfd)->verref == NULL)) {
      if (!_bfd_elf_slurp_version_tables(abfd, FALSE))
        return -1;
    }
  }

  ebd = get_elf_backend_data(abfd);
  symcount = hdr->sh_size / sizeof(Elf_External_Sym);
  if (symcount == 0)
    sym = symbase = NULL;
  else {
    isymbuf = bfd_elf_get_elf_syms(abfd, hdr, symcount, 0, NULL, NULL, NULL);
    if (isymbuf == NULL)
      return -1;

    amt = symcount;
    amt *= sizeof(elf_symbol_type);
    symbase = (elf_symbol_type *)bfd_zalloc(abfd, amt);
    if (symbase == (elf_symbol_type *)NULL)
      goto error_return;

    /* Read the raw ELF version symbol information.  */
    if (verhdr != NULL &&
        verhdr->sh_size / sizeof(Elf_External_Versym) != symcount) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB: version count (%" PRId64 ")"
             " does not match symbol count (%ld)"),
           abfd, (int64_t)(verhdr->sh_size / sizeof(Elf_External_Versym)),
           symcount);

      /* Slurp in the symbols without the version information,
         since that is more helpful than just quitting.  */
      verhdr = NULL;
    }

    if (verhdr != NULL) {
      if (bfd_seek(abfd, verhdr->sh_offset, SEEK_SET) != 0)
        goto error_return;

      xverbuf = (Elf_External_Versym *)bfd_malloc(verhdr->sh_size);
      if (xverbuf == NULL && verhdr->sh_size != 0)
        goto error_return;

      if (bfd_bread(xverbuf, verhdr->sh_size, abfd) != verhdr->sh_size)
        goto error_return;
    }

    /* Skip first symbol, which is a null dummy.  */
    xver = xverbuf;
    if (xver != NULL)
      ++xver;
    isymend = isymbuf + symcount;
    for (isym = isymbuf + 1, sym = symbase; isym < isymend; isym++, sym++) {
      memcpy(&sym->internal_elf_sym, isym, sizeof(Elf_Internal_Sym));

      sym->symbol.the_bfd = abfd;
      sym->symbol.name = bfd_elf_sym_name(abfd, hdr, isym, NULL);
      sym->symbol.value = isym->st_value;

      if (isym->st_shndx == SHN_UNDEF) {
        sym->symbol.section = bfd_und_section_ptr;
      } else if (isym->st_shndx == SHN_ABS) {
        sym->symbol.section = bfd_abs_section_ptr;
      } else if (isym->st_shndx == SHN_COMMON) {
        sym->symbol.section = bfd_com_section_ptr;
        if ((abfd->flags & BFD_PLUGIN) != 0) {
          asection *xc = bfd_get_section_by_name(abfd, "COMMON");

          if (xc == NULL) {
            flagword flags =
                (SEC_ALLOC | SEC_IS_COMMON | SEC_KEEP | SEC_EXCLUDE);
            xc = bfd_make_section_with_flags(abfd, "COMMON", flags);
            if (xc == NULL)
              goto error_return;
          }
          sym->symbol.section = xc;
        }
        /* Elf puts the alignment into the `value' field, and
           the size into the `size' field.  BFD wants to see the
           size in the value field, and doesn't care (at the
           moment) about the alignment.  */
        sym->symbol.value = isym->st_size;
      } else {
        sym->symbol.section = bfd_section_from_elf_index(abfd, isym->st_shndx);
        if (sym->symbol.section == NULL) {
          /* This symbol is in a section for which we did not
             create a BFD section.  Just use bfd_abs_section,
             although it is wrong.  FIXME.  */
          sym->symbol.section = bfd_abs_section_ptr;
        }
      }

      /* If this is a relocatable file, then the symbol value is
         already section relative.  */
      if ((abfd->flags & (EXEC_P | DYNAMIC)) != 0)
        sym->symbol.value -= sym->symbol.section->vma;

      switch (ELF_ST_BIND(isym->st_info)) {
      case STB_LOCAL:
        sym->symbol.flags |= BSF_LOCAL;
        break;
      case STB_GLOBAL:
        if (isym->st_shndx != SHN_UNDEF && isym->st_shndx != SHN_COMMON)
          sym->symbol.flags |= BSF_GLOBAL;
        break;
      case STB_WEAK:
        sym->symbol.flags |= BSF_WEAK;
        break;
      case STB_GNU_UNIQUE:
        sym->symbol.flags |= BSF_GNU_UNIQUE;
        break;
      }

      switch (ELF_ST_TYPE(isym->st_info)) {
      case STT_SECTION:
        sym->symbol.flags |= BSF_SECTION_SYM | BSF_DEBUGGING;
        break;
      case STT_FILE:
        sym->symbol.flags |= BSF_FILE | BSF_DEBUGGING;
        break;
      case STT_FUNC:
        sym->symbol.flags |= BSF_FUNCTION;
        break;
      case STT_COMMON:
        /* FIXME: Do we have to put the size field into the value field
           as we do with symbols in SHN_COMMON sections (see above) ?  */
        sym->symbol.flags |= BSF_ELF_COMMON;
        /* Fall through.  */
      case STT_OBJECT:
        sym->symbol.flags |= BSF_OBJECT;
        break;
      case STT_TLS:
        sym->symbol.flags |= BSF_THREAD_LOCAL;
        break;
      case STT_RELC:
        sym->symbol.flags |= BSF_RELC;
        break;
      case STT_SRELC:
        sym->symbol.flags |= BSF_SRELC;
        break;
      case STT_GNU_IFUNC:
        sym->symbol.flags |= BSF_GNU_INDIRECT_FUNCTION;
        break;
      }

      if (dynamic)
        sym->symbol.flags |= BSF_DYNAMIC;

      if (xver != NULL) {
        Elf_Internal_Versym iversym;

        _bfd_elf_swap_versym_in(abfd, xver, &iversym);
        sym->version = iversym.vs_vers;
        xver++;
      }

      /* Do some backend-specific processing on this symbol.  */
      if (ebd->elf_backend_symbol_processing)
        (*ebd->elf_backend_symbol_processing)(abfd, &sym->symbol);
    }
  }

  /* Do some backend-specific processing on this symbol table.  */
  if (ebd->elf_backend_symbol_table_processing)
    (*ebd->elf_backend_symbol_table_processing)(abfd, symbase, symcount);

  /* We rely on the zalloc to clear out the final symbol entry.  */

  symcount = sym - symbase;

  /* Fill in the user's symbol pointer vector if needed.  */
  if (symptrs) {
    long l = symcount;

    sym = symbase;
    while (l-- > 0) {
      *symptrs++ = &sym->symbol;
      sym++;
    }
    *symptrs = 0; /* Final null pointer */
  }

  if (xverbuf != NULL)
    free(xverbuf);
  if (isymbuf != NULL && hdr->contents != (unsigned char *)isymbuf)
    free(isymbuf);
  return symcount;

error_return:
  if (xverbuf != NULL)
    free(xverbuf);
  if (isymbuf != NULL && hdr->contents != (unsigned char *)isymbuf)
    free(isymbuf);
  return -1;
}

long _bfd_elf_canonicalize_symtab(bfd *abfd, asymbol **allocation) {
  const struct elf_backend_data *bed = get_elf_backend_data(abfd);
  long symcount = bed->s->slurp_symbol_table(abfd, allocation, FALSE);

  if (symcount >= 0)
    bfd_get_symcount(abfd) = symcount;
  return symcount;
}

bfd_boolean bfd_set_symtab(bfd *abfd, asymbol **location,
                           unsigned int symcount) {
  if (abfd->format != bfd_object || bfd_read_p(abfd)) {
    bfd_set_error(bfd_error_invalid_operation);
    return FALSE;
  }

  bfd_get_outsymbols(abfd) = location;
  bfd_get_symcount(abfd) = symcount;
  return TRUE;
}

static bfd_boolean copy_object(bfd *ibfd, bfd *obfd,
                               const bfd_arch_info_type *input_arch) {
  bfd_vma start;
  long symcount;
  asection **osections = NULL;
  asection *osec;
  asection *gnu_debuglink_section = NULL;
  bfd_size_type *gaps = NULL;
  bfd_size_type max_gap = 0;
  long symsize;
  void *dhandle;
  enum bfd_architecture iarch;
  unsigned int imach;
  unsigned int c, i;

  if (ibfd->xvec->byteorder != obfd->xvec->byteorder &&
      ibfd->xvec->byteorder != BFD_ENDIAN_UNKNOWN &&
      obfd->xvec->byteorder != BFD_ENDIAN_UNKNOWN) {
    /* PR 17636: Call non-fatal so that we return to our parent who
       may need to tidy temporary files.  */
    non_fatal(_("Unable to change endianness of input file(s)"));
    return FALSE;
  }

  if (!bfd_set_format(obfd, bfd_get_format(ibfd))) {
    bfd_nonfatal_message(NULL, obfd, NULL, NULL);
    return FALSE;
  }

  if (ibfd->sections == NULL) {
    non_fatal(_("error: the input file '%s' has no sections"),
              bfd_get_archive_filename(ibfd));
    return FALSE;
  }

  if (ibfd->xvec->flavour != bfd_target_elf_flavour) {
    if ((do_debug_sections & compress) != 0 && do_debug_sections != compress) {
      non_fatal(_("--compress-debug-sections=[zlib|zlib-gnu|zlib-gabi] is "
                  "unsupported on `%s'"),
                bfd_get_archive_filename(ibfd));
      return FALSE;
    }

    if (do_elf_stt_common) {
      non_fatal(_("--elf-stt-common=[yes|no] is unsupported on `%s'"),
                bfd_get_archive_filename(ibfd));
      return FALSE;
    }
  }

  if (verbose)
    printf(_("copy from `%s' [%s] to `%s' [%s]\n"),
           bfd_get_archive_filename(ibfd), bfd_get_target(ibfd),
           bfd_get_filename(obfd), bfd_get_target(obfd));

  if (extract_symbol)
    start = 0;
  else {
    if (set_start_set)
      start = set_start;
    else
      start = bfd_get_start_address(ibfd);
    start += change_start;
  }

  /* Neither the start address nor the flags
     need to be set for a core file.  */
  if (bfd_get_format(obfd) != bfd_core) {
    flagword flags;

    flags = bfd_get_file_flags(ibfd);
    flags |= bfd_flags_to_set;
    flags &= ~bfd_flags_to_clear;
    flags &= bfd_applicable_file_flags(obfd);

    if (strip_symbols == STRIP_ALL)
      flags &= ~HAS_RELOC;

    if (!bfd_set_start_address(obfd, start) ||
        !bfd_set_file_flags(obfd, flags)) {
      bfd_nonfatal_message(NULL, ibfd, NULL, NULL);
      return FALSE;
    }
  }

  /* Copy architecture of input file to output file.  */
  iarch = bfd_get_arch(ibfd);
  imach = bfd_get_mach(ibfd);
  if (input_arch) {
    if (bfd_get_arch_info(ibfd) == NULL ||
        bfd_get_arch_info(ibfd)->arch == bfd_arch_unknown) {
      iarch = input_arch->arch;
      imach = input_arch->mach;
    } else
      non_fatal(_("Input file `%s' ignores binary architecture parameter."),
                bfd_get_archive_filename(ibfd));
  }
  if (!bfd_set_arch_mach(obfd, iarch, imach) &&
      (ibfd->target_defaulted || bfd_get_arch(ibfd) != bfd_get_arch(obfd))) {
    if (bfd_get_arch(ibfd) == bfd_arch_unknown)
      non_fatal(_("Unable to recognise the format of the input file `%s'"),
                bfd_get_archive_filename(ibfd));
    else
      non_fatal(
          _("Output file cannot represent architecture `%s'"),
          bfd_printable_arch_mach(bfd_get_arch(ibfd), bfd_get_mach(ibfd)));
    return FALSE;
  }

  if (!bfd_set_format(obfd, bfd_get_format(ibfd))) {
    bfd_nonfatal_message(NULL, ibfd, NULL, NULL);
    return FALSE;
  }

  if (bfd_get_flavour(obfd) == bfd_target_coff_flavour && bfd_pei_p(obfd)) {
    /* Set up PE parameters.  */
    pe_data_type *pe = pe_data(obfd);

    /* Copy PE parameters before changing them.  */
    if (ibfd->xvec->flavour == bfd_target_coff_flavour && bfd_pei_p(ibfd))
      pe->pe_opthdr = pe_data(ibfd)->pe_opthdr;

    if (pe_file_alignment != (bfd_vma)-1)
      pe->pe_opthdr.FileAlignment = pe_file_alignment;
    else
      pe_file_alignment = PE_DEF_FILE_ALIGNMENT;

    if (pe_heap_commit != (bfd_vma)-1)
      pe->pe_opthdr.SizeOfHeapCommit = pe_heap_commit;

    if (pe_heap_reserve != (bfd_vma)-1)
      pe->pe_opthdr.SizeOfHeapCommit = pe_heap_reserve;

    if (pe_image_base != (bfd_vma)-1)
      pe->pe_opthdr.ImageBase = pe_image_base;

    if (pe_section_alignment != (bfd_vma)-1)
      pe->pe_opthdr.SectionAlignment = pe_section_alignment;
    else
      pe_section_alignment = PE_DEF_SECTION_ALIGNMENT;

    if (pe_stack_commit != (bfd_vma)-1)
      pe->pe_opthdr.SizeOfStackCommit = pe_stack_commit;

    if (pe_stack_reserve != (bfd_vma)-1)
      pe->pe_opthdr.SizeOfStackCommit = pe_stack_reserve;

    if (pe_subsystem != -1)
      pe->pe_opthdr.Subsystem = pe_subsystem;

    if (pe_major_subsystem_version != -1)
      pe->pe_opthdr.MajorSubsystemVersion = pe_major_subsystem_version;

    if (pe_minor_subsystem_version != -1)
      pe->pe_opthdr.MinorSubsystemVersion = pe_minor_subsystem_version;

    if (pe_file_alignment > pe_section_alignment) {
      char file_alignment[20], section_alignment[20];

      sprintf_vma(file_alignment, pe_file_alignment);
      sprintf_vma(section_alignment, pe_section_alignment);
      non_fatal(_("warning: file alignment (0x%s) > section alignment (0x%s)"),

                file_alignment, section_alignment);
    }
  }

  if (isympp)
    free(isympp);

  if (osympp != isympp)
    free(osympp);

  isympp = NULL;
  osympp = NULL;

  symsize = bfd_get_symtab_upper_bound(ibfd);
  if (symsize < 0) {
    bfd_nonfatal_message(NULL, ibfd, NULL, NULL);
    return FALSE;
  }

  osympp = isympp = (asymbol **)xmalloc(symsize);
  symcount = bfd_canonicalize_symtab(ibfd, isympp);
  if (symcount < 0) {
    bfd_nonfatal_message(NULL, ibfd, NULL, NULL);
    return FALSE;
  }
  /* PR 17512: file:  d6323821
     If the symbol table could not be loaded do not pretend that we have
     any symbols.  This trips us up later on when we load the relocs.  */
  if (symcount == 0) {
    free(isympp);
    osympp = isympp = NULL;
  }

  /* BFD mandates that all output sections be created and sizes set before
     any output is done.  Thus, we traverse all sections multiple times.  */
  bfd_map_over_sections(ibfd, setup_section, obfd);

  if (!extract_symbol)
    setup_bfd_headers(ibfd, obfd);

  if (add_sections != NULL) {
    struct section_add *padd;
    struct section_list *pset;

    for (padd = add_sections; padd != NULL; padd = padd->next) {
      flagword flags;

      pset = find_section_list(padd->name, FALSE, SECTION_CONTEXT_SET_FLAGS);
      if (pset != NULL)
        flags = pset->flags | SEC_HAS_CONTENTS;
      else
        flags = SEC_HAS_CONTENTS | SEC_READONLY | SEC_DATA;

      /* bfd_make_section_with_flags() does not return very helpful
         error codes, so check for the most likely user error first.  */
      if (bfd_get_section_by_name(obfd, padd->name)) {
        bfd_nonfatal_message(NULL, obfd, NULL, _("can't add section '%s'"),
                             padd->name);
        return FALSE;
      } else {
        /* We use LINKER_CREATED here so that the backend hooks
           will create any special section type information,
           instead of presuming we know what we're doing merely
           because we set the flags.  */
        padd->section = bfd_make_section_with_flags(obfd, padd->name,
                                                    flags | SEC_LINKER_CREATED);
        if (padd->section == NULL) {
          bfd_nonfatal_message(NULL, obfd, NULL, _("can't create section `%s'"),
                               padd->name);
          return FALSE;
        }
      }

      if (!bfd_set_section_size(obfd, padd->section, padd->size)) {
        bfd_nonfatal_message(NULL, obfd, padd->section, NULL);
        return FALSE;
      }

      pset = find_section_list(padd->name, FALSE,
                               SECTION_CONTEXT_SET_VMA |
                                   SECTION_CONTEXT_ALTER_VMA);
      if (pset != NULL &&
          !bfd_set_section_vma(obfd, padd->section, pset->vma_val)) {
        bfd_nonfatal_message(NULL, obfd, padd->section, NULL);
        return FALSE;
      }

      pset = find_section_list(padd->name, FALSE,
                               SECTION_CONTEXT_SET_LMA |
                                   SECTION_CONTEXT_ALTER_LMA);
      if (pset != NULL) {
        padd->section->lma = pset->lma_val;

        if (!bfd_set_section_alignment(
                obfd, padd->section,
                bfd_section_alignment(obfd, padd->section))) {
          bfd_nonfatal_message(NULL, obfd, padd->section, NULL);
          return FALSE;
        }
      }
    }
  }

  if (update_sections != NULL) {
    struct section_add *pupdate;

    for (pupdate = update_sections; pupdate != NULL; pupdate = pupdate->next) {
      pupdate->section = bfd_get_section_by_name(ibfd, pupdate->name);
      if (pupdate->section == NULL) {
        non_fatal(_("error: %s not found, can't be updated"), pupdate->name);
        return FALSE;
      }

      osec = pupdate->section->output_section;
      if (!bfd_set_section_size(obfd, osec, pupdate->size)) {
        bfd_nonfatal_message(NULL, obfd, osec, NULL);
        return FALSE;
      }
    }
  }

  if (merge_notes) {
    /* This palaver is necessary because we must set the output
       section size first, before its contents are ready.  */
    osec = bfd_get_section_by_name(ibfd, GNU_BUILD_ATTRS_SECTION_NAME);
    if (osec && is_merged_note_section(ibfd, osec)) {
      bfd_size_type size;

      size = bfd_get_section_size(osec);
      if (size == 0) {
        bfd_nonfatal_message(NULL, ibfd, osec,
                             _("warning: note section is empty"));
        merge_notes = FALSE;
      } else if (!bfd_get_full_section_contents(ibfd, osec, &merged_notes)) {
        bfd_nonfatal_message(NULL, ibfd, osec,
                             _("warning: could not load note section"));
        free(merged_notes);
        merged_notes = NULL;
        merge_notes = FALSE;
      } else {
        merged_size = merge_gnu_build_notes(ibfd, osec, size, merged_notes);
        if (merged_size == size) {
          /* Merging achieves nothing.  */
          free(merged_notes);
          merged_notes = NULL;
          merge_notes = FALSE;
          merged_size = 0;
        } else {
          if (osec->output_section == NULL ||
              !bfd_set_section_size(obfd, osec->output_section, merged_size)) {
            bfd_nonfatal_message(NULL, obfd, osec,
                                 _("warning: failed to set merged notes size"));
            free(merged_notes);
            merged_notes = NULL;
            merge_notes = FALSE;
            merged_size = 0;
          }
        }
      }
    }
  }

  if (dump_sections != NULL) {
    struct section_add *pdump;

    for (pdump = dump_sections; pdump != NULL; pdump = pdump->next) {
      osec = bfd_get_section_by_name(ibfd, pdump->name);
      if (osec == NULL) {
        bfd_nonfatal_message(NULL, ibfd, NULL,
                             _("can't dump section '%s' - it does not exist"),
                             pdump->name);
        continue;
      }

      if ((bfd_get_section_flags(ibfd, osec) & SEC_HAS_CONTENTS) == 0) {
        bfd_nonfatal_message(NULL, ibfd, osec,
                             _("can't dump section - it has no contents"));
        continue;
      }

      bfd_size_type size = bfd_get_section_size(osec);
      if (size == 0) {
        bfd_nonfatal_message(NULL, ibfd, osec,
                             _("can't dump section - it is empty"));
        continue;
      }

      FILE *f;
      f = fopen(pdump->filename, FOPEN_WB);
      if (f == NULL) {
        bfd_nonfatal_message(pdump->filename, NULL, NULL,
                             _("could not open section dump file"));
        continue;
      }

      bfd_byte *contents;
      if (bfd_malloc_and_get_section(ibfd, osec, &contents)) {
        if (fwrite(contents, 1, size, f) != size) {
          non_fatal(_("error writing section contents to %s (error: %s)"),
                    pdump->filename, strerror(errno));
          free(contents);
          return FALSE;
        }
      } else
        bfd_nonfatal_message(NULL, ibfd, osec,
                             _("could not retrieve section contents"));

      fclose(f);
      free(contents);
    }
  }

  if (gnu_debuglink_filename != NULL) {
    /* PR 15125: Give a helpful warning message if
       the debuglink section already exists, and
       allow the rest of the copy to complete.  */
    if (bfd_get_section_by_name(obfd, ".gnu_debuglink")) {
      non_fatal(_("%s: debuglink section already exists"),
                bfd_get_filename(obfd));
      gnu_debuglink_filename = NULL;
    } else {
      gnu_debuglink_section =
          bfd_create_gnu_debuglink_section(obfd, gnu_debuglink_filename);

      if (gnu_debuglink_section == NULL) {
        bfd_nonfatal_message(NULL, obfd, NULL,
                             _("cannot create debug link section `%s'"),
                             gnu_debuglink_filename);
        return FALSE;
      }

      /* Special processing for PE format files.  We
         have no way to distinguish PE from COFF here.  */
      if (bfd_get_flavour(obfd) == bfd_target_coff_flavour) {
        bfd_vma debuglink_vma;
        asection *highest_section;

        /* The PE spec requires that all sections be adjacent and sorted
           in ascending order of VMA.  It also specifies that debug
           sections should be last.  This is despite the fact that debug
           sections are not loaded into memory and so in theory have no
           use for a VMA.

           This means that the debuglink section must be given a non-zero
           VMA which makes it contiguous with other debug sections.  So
           walk the current section list, find the section with the
           highest VMA and start the debuglink section after that one.  */
        for (osec = obfd->sections, highest_section = NULL; osec != NULL;
             osec = osec->next)
          if (osec->vma > 0 &&
              (highest_section == NULL || osec->vma > highest_section->vma))
            highest_section = osec;

        if (highest_section)
          debuglink_vma =
              BFD_ALIGN(highest_section->vma + highest_section->size,
                        /* FIXME: We ought to be using
                           COFF_PAGE_SIZE here or maybe
                           bfd_get_section_alignment() (if it
                           was set) but since this is for PE
                           and we know the required alignment
                           it is easier just to hard code it.  */
                        0x1000);
        else
          /* Umm, not sure what to do in this case.  */
          debuglink_vma = 0x1000;

        bfd_set_section_vma(obfd, gnu_debuglink_section, debuglink_vma);
      }
    }
  }

  c = bfd_count_sections(obfd);
  if (c != 0 && (gap_fill_set || pad_to_set)) {
    asection **set;

    /* We must fill in gaps between the sections and/or we must pad
       the last section to a specified address.  We do this by
       grabbing a list of the sections, sorting them by VMA, and
       increasing the section sizes as required to fill the gaps.
       We write out the gap contents below.  */

    osections = (asection **)xmalloc(c * sizeof(asection *));
    set = osections;
    bfd_map_over_sections(obfd, get_sections, &set);

    qsort(osections, c, sizeof(asection *), compare_section_lma);

    gaps = (bfd_size_type *)xmalloc(c * sizeof(bfd_size_type));
    memset(gaps, 0, c * sizeof(bfd_size_type));

    if (gap_fill_set) {
      for (i = 0; i < c - 1; i++) {
        flagword flags;
        bfd_size_type size;
        bfd_vma gap_start, gap_stop;

        flags = bfd_get_section_flags(obfd, osections[i]);
        if ((flags & SEC_HAS_CONTENTS) == 0 || (flags & SEC_LOAD) == 0)
          continue;

        size = bfd_section_size(obfd, osections[i]);
        gap_start = bfd_section_lma(obfd, osections[i]) + size;
        gap_stop = bfd_section_lma(obfd, osections[i + 1]);
        if (gap_start < gap_stop) {
          if (!bfd_set_section_size(obfd, osections[i],
                                    size + (gap_stop - gap_start))) {
            bfd_nonfatal_message(NULL, obfd, osections[i],
                                 _("Can't fill gap after section"));
            status = 1;
            break;
          }
          gaps[i] = gap_stop - gap_start;
          if (max_gap < gap_stop - gap_start)
            max_gap = gap_stop - gap_start;
        }
      }
    }

    if (pad_to_set) {
      bfd_vma lma;
      bfd_size_type size;

      lma = bfd_section_lma(obfd, osections[c - 1]);
      size = bfd_section_size(obfd, osections[c - 1]);
      if (lma + size < pad_to) {
        if (!bfd_set_section_size(obfd, osections[c - 1], pad_to - lma)) {
          bfd_nonfatal_message(NULL, obfd, osections[c - 1],
                               _("can't add padding"));
          status = 1;
        } else {
          gaps[c - 1] = pad_to - (lma + size);
          if (max_gap < pad_to - (lma + size))
            max_gap = pad_to - (lma + size);
        }
      }
    }
  }

  /* Symbol filtering must happen after the output sections
     have been created, but before their contents are set.  */
  dhandle = NULL;
  if (convert_debugging)
    dhandle = read_debugging_info(ibfd, isympp, symcount, FALSE);

  if (strip_symbols == STRIP_DEBUG || strip_symbols == STRIP_ALL ||
      strip_symbols == STRIP_UNNEEDED || strip_symbols == STRIP_NONDEBUG ||
      strip_symbols == STRIP_DWO || strip_symbols == STRIP_NONDWO ||
      discard_locals != LOCALS_UNDEF || localize_hidden ||
      htab_elements(strip_specific_htab) != 0 ||
      htab_elements(keep_specific_htab) != 0 ||
      htab_elements(localize_specific_htab) != 0 ||
      htab_elements(globalize_specific_htab) != 0 ||
      htab_elements(keepglobal_specific_htab) != 0 ||
      htab_elements(weaken_specific_htab) != 0 ||
      htab_elements(redefine_specific_htab) != 0 || prefix_symbols_string ||
      sections_removed || sections_copied || convert_debugging ||
      change_leading_char || remove_leading_char || section_rename_list ||
      weaken || add_symbols) {
    /* Mark symbols used in output relocations so that they
       are kept, even if they are local labels or static symbols.

       Note we iterate over the input sections examining their
       relocations since the relocations for the output sections
       haven't been set yet.  mark_symbols_used_in_relocations will
       ignore input sections which have no corresponding output
       section.  */
    if (strip_symbols != STRIP_ALL) {
      bfd_set_error(bfd_error_no_error);
      bfd_map_over_sections(ibfd, mark_symbols_used_in_relocations, isympp);
      if (bfd_get_error() != bfd_error_no_error) {
        status = 1;
        return FALSE;
      }
    }

    osympp =
        (asymbol **)xmalloc((symcount + add_symbols + 1) * sizeof(asymbol *));
    symcount = filter_symbols(ibfd, obfd, osympp, isympp, symcount);
  }

  if (convert_debugging && dhandle != NULL) {
    if (!write_debugging_info(obfd, dhandle, &symcount, &osympp)) {
      status = 1;
      return FALSE;
    }
  }

  bfd_set_symtab(obfd, osympp, symcount);

  /* This has to happen before section positions are set.  */
  bfd_map_over_sections(ibfd, copy_relocations_in_section, obfd);

  /* This has to happen after the symbol table has been set.  */
  bfd_map_over_sections(ibfd, copy_section, obfd);

  if (add_sections != NULL) {
    struct section_add *padd;

    for (padd = add_sections; padd != NULL; padd = padd->next) {
      if (!bfd_set_section_contents(obfd, padd->section, padd->contents, 0,
                                    padd->size)) {
        bfd_nonfatal_message(NULL, obfd, padd->section, NULL);
        return FALSE;
      }
    }
  }

  if (update_sections != NULL) {
    struct section_add *pupdate;

    for (pupdate = update_sections; pupdate != NULL; pupdate = pupdate->next) {
      osec = pupdate->section->output_section;
      if (!bfd_set_section_contents(obfd, osec, pupdate->contents, 0,
                                    pupdate->size)) {
        bfd_nonfatal_message(NULL, obfd, osec, NULL);
        return FALSE;
      }
    }
  }

  if (merge_notes) {
    osec = bfd_get_section_by_name(obfd, GNU_BUILD_ATTRS_SECTION_NAME);
    if (osec && is_merged_note_section(obfd, osec)) {
      if (!bfd_set_section_contents(obfd, osec, merged_notes, 0, merged_size)) {
        bfd_nonfatal_message(
            NULL, obfd, osec,
            _("error: failed to copy merged notes into output"));
        return FALSE;
      }
    } else if (!is_strip)
      bfd_nonfatal_message(NULL, obfd, osec,
                           _("could not find any mergeable note sections"));
    free(merged_notes);
    merged_notes = NULL;
    merge_notes = FALSE;
  }

  if (gnu_debuglink_filename != NULL) {
    if (!bfd_fill_in_gnu_debuglink_section(obfd, gnu_debuglink_section,
                                           gnu_debuglink_filename)) {
      bfd_nonfatal_message(NULL, obfd, NULL,
                           _("cannot fill debug link section `%s'"),
                           gnu_debuglink_filename);
      return FALSE;
    }
  }

  if (gap_fill_set || pad_to_set) {
    bfd_byte *buf;

    /* Fill in the gaps.  */
    if (max_gap > 8192)
      max_gap = 8192;
    buf = (bfd_byte *)xmalloc(max_gap);
    memset(buf, gap_fill, max_gap);

    c = bfd_count_sections(obfd);
    for (i = 0; i < c; i++) {
      if (gaps[i] != 0) {
        bfd_size_type left;
        file_ptr off;

        left = gaps[i];
        off = bfd_section_size(obfd, osections[i]) - left;

        while (left > 0) {
          bfd_size_type now;

          if (left > 8192)
            now = 8192;
          else
            now = left;

          if (!bfd_set_section_contents(obfd, osections[i], buf, off, now)) {
            bfd_nonfatal_message(NULL, obfd, osections[i], NULL);
            return FALSE;
          }

          left -= now;
          off += now;
        }
      }
    }
  }

  /* Allow the BFD backend to copy any private data it understands
     from the input BFD to the output BFD.  This is done last to
     permit the routine to look at the filtered symbol table, which is
     important for the ECOFF code at least.  */
  if (!bfd_copy_private_bfd_data(ibfd, obfd)) {
    bfd_nonfatal_message(NULL, obfd, NULL, _("error copying private BFD data"));
    return FALSE;
  }

  /* Switch to the alternate machine code.  We have to do this at the
     very end, because we only initialize the header when we create
     the first section.  */
  if (use_alt_mach_code != 0) {
    if (!bfd_alt_mach_code(obfd, use_alt_mach_code)) {
      non_fatal(_("this target does not support %lu alternative machine codes"),
                use_alt_mach_code);
      if (bfd_get_flavour(obfd) == bfd_target_elf_flavour) {
        non_fatal(
            _("treating that number as an absolute e_machine value instead"));
        elf_elfheader(obfd)->e_machine = use_alt_mach_code;
      } else
        non_fatal(_("ignoring the alternative value"));
    }
  }

  return TRUE;
}


struct bfd_hash_entry *bfd_section_hash_newfunc(struct bfd_hash_entry *entry,
                                                struct bfd_hash_table *table,
                                                const char *string) {
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL) {
    entry = (struct bfd_hash_entry *)bfd_hash_allocate(
        table, sizeof(struct section_hash_entry));
    if (entry == NULL)
      return entry;
  }

  /* Call the allocation method of the superclass.  */
  entry = bfd_hash_newfunc(entry, table, string);
  if (entry != NULL)
    memset(&((struct section_hash_entry *)entry)->section, 0, sizeof(asection));

  return entry;
}

struct bfd_hash_entry *bfd_hash_insert(struct bfd_hash_table *table,
                                       const char *string, unsigned long hash) {
  struct bfd_hash_entry *hashp;
  unsigned int _index;

  hashp = (*table->newfunc)(NULL, table, string);
  if (hashp == NULL)
    return NULL;
  hashp->string = string;
  hashp->hash = hash;
  _index = hash % table->size;
  hashp->next = table->table[_index];
  table->table[_index] = hashp;
  table->count++;

  if (!table->frozen && table->count > table->size * 3 / 4) {
    unsigned long newsize = higher_prime_number(table->size);
    struct bfd_hash_entry **newtable;
    unsigned int hi;
    unsigned long alloc = newsize * sizeof(struct bfd_hash_entry *);

    /* If we can't find a higher prime, or we can't possibly alloc
       that much memory, don't try to grow the table.  */
    if (newsize == 0 || alloc / sizeof(struct bfd_hash_entry *) != newsize) {
      table->frozen = 1;
      return hashp;
    }

    newtable = ((struct bfd_hash_entry **)objalloc_alloc(
        (struct objalloc *)table->memory, alloc));
    if (newtable == NULL) {
      table->frozen = 1;
      return hashp;
    }
    memset(newtable, 0, alloc);

    for (hi = 0; hi < table->size; hi++)
      while (table->table[hi]) {
        struct bfd_hash_entry *chain = table->table[hi];
        struct bfd_hash_entry *chain_end = chain;

        while (chain_end->next && chain_end->next->hash == chain->hash)
          chain_end = chain_end->next;

        table->table[hi] = chain_end->next;
        _index = chain->hash % newsize;
        chain_end->next = newtable[_index];
        newtable[_index] = chain;
      }
    table->table = newtable;
    table->size = newsize;
  }

  return hashp;
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

static asection *bfd_section_init(bfd *abfd, asection *newsect) {
  newsect->id = section_id;
  newsect->index = abfd->section_count;
  newsect->owner = abfd;

  if (!BFD_SEND(abfd, _new_section_hook, (abfd, newsect)))
    return NULL;

  section_id++;
  abfd->section_count++;
  bfd_section_list_append(abfd, newsect);
  return newsect;
}

sec_ptr bfd_make_section_anyway_with_flags(bfd *abfd, const char *name,
                                           flagword flags) {
  struct section_hash_entry *sh;
  asection *newsect;

  if (abfd->output_has_begun) {
    bfd_set_error(bfd_error_invalid_operation);
    return NULL;
  }

  sh = section_hash_lookup(&abfd->section_htab, name, TRUE, FALSE);
  if (sh == NULL)
    return NULL;

  newsect = &sh->section;
  if (newsect->name != NULL) {
    /* We are making a section of the same name.  Put it in the
       section hash table.  Even though we can't find it directly by a
       hash lookup, we'll be able to find the section by traversing
       sh->root.next quicker than looking at all the bfd sections.  */
    struct section_hash_entry *new_sh;
    new_sh = (struct section_hash_entry *)bfd_section_hash_newfunc(
        NULL, &abfd->section_htab, name);
    if (new_sh == NULL)
      return NULL;

    new_sh->root = sh->root;
    sh->root.next = &new_sh->root;
    newsect = &new_sh->section;
  }

  newsect->flags = flags;
  newsect->name = name;
  return bfd_section_init(abfd, newsect);
}

sec_ptr bfd_make_section_anyway(bfd *abfd, const char *name) {
  return bfd_make_section_anyway_with_flags(abfd, name, 0);
}

bfd_boolean _bfd_elf_make_section_from_shdr(bfd *abfd, Elf_Internal_Shdr *hdr,
                                            const char *name, int shindex) {
  asection *newsect;
  flagword flags;
  const struct elf_backend_data *bed;

  if (hdr->bfd_section != NULL)
    return TRUE;

  newsect = bfd_make_section_anyway(abfd, name);
  if (newsect == NULL)
    return FALSE;

  hdr->bfd_section = newsect;
  elf_section_data(newsect)->this_hdr = *hdr;
  elf_section_data(newsect)->this_idx = shindex;

  /* Always use the real type/flags.  */
  elf_section_type(newsect) = hdr->sh_type;
  elf_section_flags(newsect) = hdr->sh_flags;

  newsect->filepos = hdr->sh_offset;

  if (!bfd_set_section_vma(abfd, newsect, hdr->sh_addr) ||
      !bfd_set_section_size(abfd, newsect, hdr->sh_size) ||
      !bfd_set_section_alignment(abfd, newsect, bfd_log2(hdr->sh_addralign)))
    return FALSE;

  flags = SEC_NO_FLAGS;
  if (hdr->sh_type != SHT_NOBITS)
    flags |= SEC_HAS_CONTENTS;
  if (hdr->sh_type == SHT_GROUP)
    flags |= SEC_GROUP;
  if ((hdr->sh_flags & SHF_ALLOC) != 0) {
    flags |= SEC_ALLOC;
    if (hdr->sh_type != SHT_NOBITS)
      flags |= SEC_LOAD;
  }
  if ((hdr->sh_flags & SHF_WRITE) == 0)
    flags |= SEC_READONLY;
  if ((hdr->sh_flags & SHF_EXECINSTR) != 0)
    flags |= SEC_CODE;
  else if ((flags & SEC_LOAD) != 0)
    flags |= SEC_DATA;
  if ((hdr->sh_flags & SHF_MERGE) != 0) {
    flags |= SEC_MERGE;
    newsect->entsize = hdr->sh_entsize;
  }
  if ((hdr->sh_flags & SHF_STRINGS) != 0)
    flags |= SEC_STRINGS;
  if (hdr->sh_flags & SHF_GROUP)
    if (!setup_group(abfd, hdr, newsect))
      return FALSE;
  if ((hdr->sh_flags & SHF_TLS) != 0)
    flags |= SEC_THREAD_LOCAL;
  if ((hdr->sh_flags & SHF_EXCLUDE) != 0)
    flags |= SEC_EXCLUDE;

  if ((flags & SEC_ALLOC) == 0) {
    /* The debugging sections appear to be recognized only by name,
       not any sort of flag.  Their SEC_ALLOC bits are cleared.  */
    if (name[0] == '.') {
      const char *p;
      int n;
      if (name[1] == 'd')
        p = ".debug", n = 6;
      else if (name[1] == 'g' && name[2] == 'n')
        p = ".gnu.linkonce.wi.", n = 17;
      else if (name[1] == 'g' && name[2] == 'd')
        p = ".gdb_index", n = 11; /* yes we really do mean 11.  */
      else if (name[1] == 'l')
        p = ".line", n = 5;
      else if (name[1] == 's')
        p = ".stab", n = 5;
      else if (name[1] == 'z')
        p = ".zdebug", n = 7;
      else
        p = NULL, n = 0;
      if (p != NULL && strncmp(name, p, n) == 0)
        flags |= SEC_DEBUGGING;
    }
  }

  /* As a GNU extension, if the name begins with .gnu.linkonce, we
     only link a single copy of the section.  This is used to support
     g++.  g++ will emit each template expansion in its own section.
     The symbols will be defined as weak, so that multiple definitions
     are permitted.  The GNU linker extension is to actually discard
     all but one of the sections.  */
  if (CONST_STRNEQ(name, ".gnu.linkonce") && elf_next_in_group(newsect) == NULL)
    flags |= SEC_LINK_ONCE | SEC_LINK_DUPLICATES_DISCARD;

  bed = get_elf_backend_data(abfd);
  if (bed->elf_backend_section_flags)
    if (!bed->elf_backend_section_flags(&flags, hdr))
      return FALSE;

  if (!bfd_set_section_flags(abfd, newsect, flags))
    return FALSE;

  /* We do not parse the PT_NOTE segments as we are interested even in the
     separate debug info files which may have the segments offsets corrupted.
     PT_NOTEs from the core files are currently not parsed using BFD.  */
  if (hdr->sh_type == SHT_NOTE) {
    bfd_byte *contents;

    if (!bfd_malloc_and_get_section(abfd, newsect, &contents))
      return FALSE;

    elf_parse_notes(abfd, (char *)contents, hdr->sh_size, hdr->sh_offset,
                    hdr->sh_addralign);
    free(contents);
  }

  if ((flags & SEC_ALLOC) != 0) {
    Elf_Internal_Phdr *phdr;
    unsigned int i, nload;

    /* Some ELF linkers produce binaries with all the program header
       p_paddr fields zero.  If we have such a binary with more than
       one PT_LOAD header, then leave the section lma equal to vma
       so that we don't create sections with overlapping lma.  */
    phdr = elf_tdata(abfd)->phdr;
    for (nload = 0, i = 0; i < elf_elfheader(abfd)->e_phnum; i++, phdr++)
      if (phdr->p_paddr != 0)
        break;
      else if (phdr->p_type == PT_LOAD && phdr->p_memsz != 0)
        ++nload;
    if (i >= elf_elfheader(abfd)->e_phnum && nload > 1)
      return TRUE;

    phdr = elf_tdata(abfd)->phdr;
    for (i = 0; i < elf_elfheader(abfd)->e_phnum; i++, phdr++) {
      if (((phdr->p_type == PT_LOAD && (hdr->sh_flags & SHF_TLS) == 0) ||
           phdr->p_type == PT_TLS) &&
          ELF_SECTION_IN_SEGMENT(hdr, phdr)) {
        if ((flags & SEC_LOAD) == 0)
          newsect->lma = (phdr->p_paddr + hdr->sh_addr - phdr->p_vaddr);
        else
          /* We used to use the same adjustment for SEC_LOAD
             sections, but that doesn't work if the segment
             is packed with code from multiple VMAs.
             Instead we calculate the section LMA based on
             the segment LMA.  It is assumed that the
             segment will contain sections with contiguous
             LMAs, even if the VMAs are not.  */
          newsect->lma = (phdr->p_paddr + hdr->sh_offset - phdr->p_offset);

        /* With contiguous segments, we can't tell from file
           offsets whether a section with zero size should
           be placed at the end of one segment or the
           beginning of the next.  Decide based on vaddr.  */
        if (hdr->sh_addr >= phdr->p_vaddr &&
            (hdr->sh_addr + hdr->sh_size <= phdr->p_vaddr + phdr->p_memsz))
          break;
      }
    }
  }

  /* Compress/decompress DWARF debug sections with names: .debug_* and
     .zdebug_*, after the section flags is set.  */
  if ((flags & SEC_DEBUGGING) && ((name[1] == 'd' && name[6] == '_') ||
                                  (name[1] == 'z' && name[7] == '_'))) {
    enum { nothing, compress, decompress } action = nothing;
    int compression_header_size;
    bfd_size_type uncompressed_size;
    bfd_boolean compressed = bfd_is_section_compressed_with_header(
        abfd, newsect, &compression_header_size, &uncompressed_size);

    if (compressed) {
      /* Compressed section.  Check if we should decompress.  */
      if ((abfd->flags & BFD_DECOMPRESS))
        action = decompress;
    }

    /* Compress the uncompressed section or convert from/to .zdebug*
       section.  Check if we should compress.  */
    if (action == nothing) {
      if (newsect->size != 0 && (abfd->flags & BFD_COMPRESS) &&
          compression_header_size >= 0 && uncompressed_size > 0 &&
          (!compressed || ((compression_header_size > 0) !=
                           ((abfd->flags & BFD_COMPRESS_GABI) != 0))))
        action = compress;
      else
        return TRUE;
    }

    if (action == compress) {
      if (!bfd_init_section_compress_status(abfd, newsect)) {
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%pB: unable to initialize compress status for section %s"),
             abfd, name);
        return FALSE;
      }
    } else {
      if (!bfd_init_section_decompress_status(abfd, newsect)) {
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%pB: unable to initialize decompress status for section %s"),
             abfd, name);
        return FALSE;
      }
    }

    if (abfd->is_linker_input) {
      if (name[1] == 'z' &&
          (action == decompress ||
           (action == compress && (abfd->flags & BFD_COMPRESS_GABI) != 0))) {
        /* Convert section name from .zdebug_* to .debug_* so
           that linker will consider this section as a debug
           section.  */
        char *new_name = convert_zdebug_to_debug(abfd, name);
        if (new_name == NULL)
          return FALSE;
        bfd_rename_section(abfd, newsect, new_name);
      }
    } else
      /* For objdump, don't rename the section.  For objcopy, delay
         section rename to elf_fake_sections.  */
      newsect->flags |= SEC_ELF_RENAME;
  }

  return TRUE;
}

bfd_boolean bfd_section_from_shdr(bfd *abfd, unsigned int shindex) {
  Elf_Internal_Shdr *hdr;
  Elf_Internal_Ehdr *ehdr;
  const struct elf_backend_data *bed;
  const char *name;
  bfd_boolean ret = TRUE;
  static bfd_boolean *sections_being_created = NULL;
  static bfd *sections_being_created_abfd = NULL;
  static unsigned int nesting = 0;

  if (shindex >= elf_numsections(abfd))
    return FALSE;

  if (++nesting > 3) {
    /* PR17512: A corrupt ELF binary might contain a recursive group of
       sections, with each the string indicies pointing to the next in the
       loop.  Detect this here, by refusing to load a section that we are
       already in the process of loading.  We only trigger this test if
       we have nested at least three sections deep as normal ELF binaries
       can expect to recurse at least once.

       FIXME: It would be better if this array was attached to the bfd,
       rather than being held in a static pointer.  */

    if (sections_being_created_abfd != abfd)
      sections_being_created = NULL;
    if (sections_being_created == NULL) {
      /* FIXME: It would be more efficient to attach this array to the bfd
       * somehow.  */
      sections_being_created = (bfd_boolean *)bfd_zalloc(
          abfd, elf_numsections(abfd) * sizeof(bfd_boolean));
      sections_being_created_abfd = abfd;
    }
    if (sections_being_created[shindex]) {
      _bfd_error_handler(
          _("%pB: warning: loop in section dependencies detected"), abfd);
      return FALSE;
    }
    sections_being_created[shindex] = TRUE;
  }

  hdr = elf_elfsections(abfd)[shindex];
  ehdr = elf_elfheader(abfd);
  name = bfd_elf_string_from_elf_section(abfd, ehdr->e_shstrndx, hdr->sh_name);
  if (name == NULL)
    goto fail;

  bed = get_elf_backend_data(abfd);
  switch (hdr->sh_type) {
  case SHT_NULL:
    /* Inactive section. Throw it away.  */
    goto success;

  case SHT_PROGBITS:      /* Normal section with contents.  */
  case SHT_NOBITS:        /* .bss section.  */
  case SHT_HASH:          /* .hash section.  */
  case SHT_NOTE:          /* .note section.  */
  case SHT_INIT_ARRAY:    /* .init_array section.  */
  case SHT_FINI_ARRAY:    /* .fini_array section.  */
  case SHT_PREINIT_ARRAY: /* .preinit_array section.  */
  case SHT_GNU_LIBLIST:   /* .gnu.liblist section.  */
  case SHT_GNU_HASH:      /* .gnu.hash section.  */
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_DYNAMIC: /* Dynamic linking information.  */
    if (!_bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex))
      goto fail;

    if (hdr->sh_link > elf_numsections(abfd)) {
      /* PR 10478: Accept Solaris binaries with a sh_link
         field set to SHN_BEFORE or SHN_AFTER.  */
      switch (bfd_get_arch(abfd)) {
      case bfd_arch_i386:
      case bfd_arch_sparc:
        if (hdr->sh_link == (SHN_LORESERVE & 0xffff) /* SHN_BEFORE */
            || hdr->sh_link == ((SHN_LORESERVE + 1) & 0xffff) /* SHN_AFTER */)
          break;
        /* Otherwise fall through.  */
      default:
        goto fail;
      }
    } else if (elf_elfsections(abfd)[hdr->sh_link] == NULL)
      goto fail;
    else if (elf_elfsections(abfd)[hdr->sh_link]->sh_type != SHT_STRTAB) {
      Elf_Internal_Shdr *dynsymhdr;

      /* The shared libraries distributed with hpux11 have a bogus
         sh_link field for the ".dynamic" section.  Find the
         string table for the ".dynsym" section instead.  */
      if (elf_dynsymtab(abfd) != 0) {
        dynsymhdr = elf_elfsections(abfd)[elf_dynsymtab(abfd)];
        hdr->sh_link = dynsymhdr->sh_link;
      } else {
        unsigned int i, num_sec;

        num_sec = elf_numsections(abfd);
        for (i = 1; i < num_sec; i++) {
          dynsymhdr = elf_elfsections(abfd)[i];
          if (dynsymhdr->sh_type == SHT_DYNSYM) {
            hdr->sh_link = dynsymhdr->sh_link;
            break;
          }
        }
      }
    }
    goto success;

  case SHT_SYMTAB: /* A symbol table.  */
    if (elf_onesymtab(abfd) == shindex)
      goto success;

    if (hdr->sh_entsize != bed->s->sizeof_sym)
      goto fail;

    if (hdr->sh_info * hdr->sh_entsize > hdr->sh_size) {
      if (hdr->sh_size != 0)
        goto fail;
      /* Some assemblers erroneously set sh_info to one with a
         zero sh_size.  ld sees this as a global symbol count
         of (unsigned) -1.  Fix it here.  */
      hdr->sh_info = 0;
      goto success;
    }

    /* PR 18854: A binary might contain more than one symbol table.
       Unusual, but possible.  Warn, but continue.  */
    if (elf_onesymtab(abfd) != 0) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB: warning: multiple symbol tables detected"
             " - ignoring the table in section %u"),
           abfd, shindex);
      goto success;
    }
    elf_onesymtab(abfd) = shindex;
    elf_symtab_hdr(abfd) = *hdr;
    elf_elfsections(abfd)[shindex] = hdr = &elf_symtab_hdr(abfd);
    abfd->flags |= HAS_SYMS;

    /* Sometimes a shared object will map in the symbol table.  If
       SHF_ALLOC is set, and this is a shared object, then we also
       treat this section as a BFD section.  We can not base the
       decision purely on SHF_ALLOC, because that flag is sometimes
       set in a relocatable object file, which would confuse the
       linker.  */
    if ((hdr->sh_flags & SHF_ALLOC) != 0 && (abfd->flags & DYNAMIC) != 0 &&
        !_bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex))
      goto fail;

    /* Go looking for SHT_SYMTAB_SHNDX too, since if there is one we
       can't read symbols without that section loaded as well.  It
       is most likely specified by the next section header.  */
    {
      elf_section_list *entry;
      unsigned int i, num_sec;

      for (entry = elf_symtab_shndx_list(abfd); entry != NULL;
           entry = entry->next)
        if (entry->hdr.sh_link == shindex)
          goto success;

      num_sec = elf_numsections(abfd);
      for (i = shindex + 1; i < num_sec; i++) {
        Elf_Internal_Shdr *hdr2 = elf_elfsections(abfd)[i];

        if (hdr2->sh_type == SHT_SYMTAB_SHNDX && hdr2->sh_link == shindex)
          break;
      }

      if (i == num_sec)
        for (i = 1; i < shindex; i++) {
          Elf_Internal_Shdr *hdr2 = elf_elfsections(abfd)[i];

          if (hdr2->sh_type == SHT_SYMTAB_SHNDX && hdr2->sh_link == shindex)
            break;
        }

      if (i != shindex)
        ret = bfd_section_from_shdr(abfd, i);
      /* else FIXME: we have failed to find the symbol table - should we issue
       * an error ? */
      goto success;
    }

  case SHT_DYNSYM: /* A dynamic symbol table.  */
    if (elf_dynsymtab(abfd) == shindex)
      goto success;

    if (hdr->sh_entsize != bed->s->sizeof_sym)
      goto fail;

    if (hdr->sh_info * hdr->sh_entsize > hdr->sh_size) {
      if (hdr->sh_size != 0)
        goto fail;

      /* Some linkers erroneously set sh_info to one with a
         zero sh_size.  ld sees this as a global symbol count
         of (unsigned) -1.  Fix it here.  */
      hdr->sh_info = 0;
      goto success;
    }

    /* PR 18854: A binary might contain more than one dynamic symbol table.
       Unusual, but possible.  Warn, but continue.  */
    if (elf_dynsymtab(abfd) != 0) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB: warning: multiple dynamic symbol tables detected"
             " - ignoring the table in section %u"),
           abfd, shindex);
      goto success;
    }
    elf_dynsymtab(abfd) = shindex;
    elf_tdata(abfd)->dynsymtab_hdr = *hdr;
    elf_elfsections(abfd)[shindex] = hdr = &elf_tdata(abfd)->dynsymtab_hdr;
    abfd->flags |= HAS_SYMS;

    /* Besides being a symbol table, we also treat this as a regular
       section, so that objcopy can handle it.  */
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_SYMTAB_SHNDX: /* Symbol section indices when >64k sections.  */
  {
    elf_section_list *entry;

    for (entry = elf_symtab_shndx_list(abfd); entry != NULL;
         entry = entry->next)
      if (entry->ndx == shindex)
        goto success;

    entry = bfd_alloc(abfd, sizeof *entry);
    if (entry == NULL)
      goto fail;
    entry->ndx = shindex;
    entry->hdr = *hdr;
    entry->next = elf_symtab_shndx_list(abfd);
    elf_symtab_shndx_list(abfd) = entry;
    elf_elfsections(abfd)[shindex] = &entry->hdr;
    goto success;
  }

  case SHT_STRTAB: /* A string table.  */
    if (hdr->bfd_section != NULL)
      goto success;

    if (ehdr->e_shstrndx == shindex) {
      elf_tdata(abfd)->shstrtab_hdr = *hdr;
      elf_elfsections(abfd)[shindex] = &elf_tdata(abfd)->shstrtab_hdr;
      goto success;
    }

    if (elf_elfsections(abfd)[elf_onesymtab(abfd)]->sh_link == shindex) {
    symtab_strtab:
      elf_tdata(abfd)->strtab_hdr = *hdr;
      elf_elfsections(abfd)[shindex] = &elf_tdata(abfd)->strtab_hdr;
      goto success;
    }

    if (elf_elfsections(abfd)[elf_dynsymtab(abfd)]->sh_link == shindex) {
    dynsymtab_strtab:
      elf_tdata(abfd)->dynstrtab_hdr = *hdr;
      hdr = &elf_tdata(abfd)->dynstrtab_hdr;
      elf_elfsections(abfd)[shindex] = hdr;
      /* We also treat this as a regular section, so that objcopy
         can handle it.  */
      ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
      goto success;
    }

    /* If the string table isn't one of the above, then treat it as a
       regular section.  We need to scan all the headers to be sure,
       just in case this strtab section appeared before the above.  */
    if (elf_onesymtab(abfd) == 0 || elf_dynsymtab(abfd) == 0) {
      unsigned int i, num_sec;

      num_sec = elf_numsections(abfd);
      for (i = 1; i < num_sec; i++) {
        Elf_Internal_Shdr *hdr2 = elf_elfsections(abfd)[i];
        if (hdr2->sh_link == shindex) {
          /* Prevent endless recursion on broken objects.  */
          if (i == shindex)
            goto fail;
          if (!bfd_section_from_shdr(abfd, i))
            goto fail;
          if (elf_onesymtab(abfd) == i)
            goto symtab_strtab;
          if (elf_dynsymtab(abfd) == i)
            goto dynsymtab_strtab;
        }
      }
    }
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_REL:
  case SHT_RELA:
    /* *These* do a lot of work -- but build no sections!  */
    {
      asection *target_sect;
      Elf_Internal_Shdr *hdr2, **p_hdr;
      unsigned int num_sec = elf_numsections(abfd);
      struct bfd_elf_section_data *esdt;

      if (hdr->sh_entsize != (bfd_size_type)(hdr->sh_type == SHT_REL
                                                 ? bed->s->sizeof_rel
                                                 : bed->s->sizeof_rela))
        goto fail;

      /* Check for a bogus link to avoid crashing.  */
      if (hdr->sh_link >= num_sec) {
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%pB: invalid link %u for reloc section %s (index %u)"), abfd,
             hdr->sh_link, name, shindex);
        ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
        goto success;
      }

      /* For some incomprehensible reason Oracle distributes
         libraries for Solaris in which some of the objects have
         bogus sh_link fields.  It would be nice if we could just
         reject them, but, unfortunately, some people need to use
         them.  We scan through the section headers; if we find only
         one suitable symbol table, we clobber the sh_link to point
         to it.  I hope this doesn't break anything.

         Don't do it on executable nor shared library.  */
      if ((abfd->flags & (DYNAMIC | EXEC_P)) == 0 &&
          elf_elfsections(abfd)[hdr->sh_link]->sh_type != SHT_SYMTAB &&
          elf_elfsections(abfd)[hdr->sh_link]->sh_type != SHT_DYNSYM) {
        unsigned int scan;
        int found;

        found = 0;
        for (scan = 1; scan < num_sec; scan++) {
          if (elf_elfsections(abfd)[scan]->sh_type == SHT_SYMTAB ||
              elf_elfsections(abfd)[scan]->sh_type == SHT_DYNSYM) {
            if (found != 0) {
              found = 0;
              break;
            }
            found = scan;
          }
        }
        if (found != 0)
          hdr->sh_link = found;
      }

      /* Get the symbol table.  */
      if ((elf_elfsections(abfd)[hdr->sh_link]->sh_type == SHT_SYMTAB ||
           elf_elfsections(abfd)[hdr->sh_link]->sh_type == SHT_DYNSYM) &&
          !bfd_section_from_shdr(abfd, hdr->sh_link))
        goto fail;

      /* If this reloc section does not use the main symbol table we
         don't treat it as a reloc section.  BFD can't adequately
         represent such a section, so at least for now, we don't
         try.  We just present it as a normal section.  We also
         can't use it as a reloc section if it points to the null
         section, an invalid section, another reloc section, or its
         sh_link points to the null section.  */
      if (hdr->sh_link != elf_onesymtab(abfd) || hdr->sh_link == SHN_UNDEF ||
          hdr->sh_info == SHN_UNDEF || hdr->sh_info >= num_sec ||
          elf_elfsections(abfd)[hdr->sh_info]->sh_type == SHT_REL ||
          elf_elfsections(abfd)[hdr->sh_info]->sh_type == SHT_RELA) {
        ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
        goto success;
      }

      if (!bfd_section_from_shdr(abfd, hdr->sh_info))
        goto fail;

      target_sect = bfd_section_from_elf_index(abfd, hdr->sh_info);
      if (target_sect == NULL)
        goto fail;

      esdt = elf_section_data(target_sect);
      if (hdr->sh_type == SHT_RELA)
        p_hdr = &esdt->rela.hdr;
      else
        p_hdr = &esdt->rel.hdr;

      /* PR 17512: file: 0b4f81b7.  */
      if (*p_hdr != NULL)
        goto fail;
      hdr2 = (Elf_Internal_Shdr *)bfd_alloc(abfd, sizeof(*hdr2));
      if (hdr2 == NULL)
        goto fail;
      *hdr2 = *hdr;
      *p_hdr = hdr2;
      elf_elfsections(abfd)[shindex] = hdr2;
      target_sect->reloc_count +=
          (NUM_SHDR_ENTRIES(hdr) * bed->s->int_rels_per_ext_rel);
      target_sect->flags |= SEC_RELOC;
      target_sect->relocation = NULL;
      target_sect->rel_filepos = hdr->sh_offset;
      /* In the section to which the relocations apply, mark whether
         its relocations are of the REL or RELA variety.  */
      if (hdr->sh_size != 0) {
        if (hdr->sh_type == SHT_RELA)
          target_sect->use_rela_p = 1;
      }
      abfd->flags |= HAS_RELOC;
      goto success;
    }

  case SHT_GNU_verdef:
    elf_dynverdef(abfd) = shindex;
    elf_tdata(abfd)->dynverdef_hdr = *hdr;
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_GNU_versym:
    if (hdr->sh_entsize != sizeof(Elf_External_Versym))
      goto fail;

    elf_dynversym(abfd) = shindex;
    elf_tdata(abfd)->dynversym_hdr = *hdr;
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_GNU_verneed:
    elf_dynverref(abfd) = shindex;
    elf_tdata(abfd)->dynverref_hdr = *hdr;
    ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
    goto success;

  case SHT_SHLIB:
    goto success;

  case SHT_GROUP:
    if (!IS_VALID_GROUP_SECTION_HEADER(hdr, GRP_ENTRY_SIZE))
      goto fail;

    if (!_bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex))
      goto fail;

    goto success;

  default:
    /* Possibly an attributes section.  */
    if (hdr->sh_type == SHT_GNU_ATTRIBUTES ||
        hdr->sh_type == bed->obj_attrs_section_type) {
      if (!_bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex))
        goto fail;
      _bfd_elf_parse_attributes(abfd, hdr);
      goto success;
    }

    /* Check for any processor-specific section types.  */
    if (bed->elf_backend_section_from_shdr(abfd, hdr, name, shindex))
      goto success;

    if (hdr->sh_type >= SHT_LOUSER && hdr->sh_type <= SHT_HIUSER) {
      if ((hdr->sh_flags & SHF_ALLOC) != 0)
        /* FIXME: How to properly handle allocated section reserved
           for applications?  */
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%pB: unknown type [%#x] section `%s'"), abfd, hdr->sh_type,
             name);
      else {
        /* Allow sections reserved for applications.  */
        ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
        goto success;
      }
    } else if (hdr->sh_type >= SHT_LOPROC && hdr->sh_type <= SHT_HIPROC)
      /* FIXME: We should handle this section.  */
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB: unknown type [%#x] section `%s'"), abfd, hdr->sh_type, name);
    else if (hdr->sh_type >= SHT_LOOS && hdr->sh_type <= SHT_HIOS) {
      /* Unrecognised OS-specific sections.  */
      if ((hdr->sh_flags & SHF_OS_NONCONFORMING) != 0)
        /* SHF_OS_NONCONFORMING indicates that special knowledge is
           required to correctly process the section and the file should
           be rejected with an error message.  */
        _bfd_error_handler
            /* xgettext:c-format */
            (_("%pB: unknown type [%#x] section `%s'"), abfd, hdr->sh_type,
             name);
      else {
        /* Otherwise it should be processed.  */
        ret = _bfd_elf_make_section_from_shdr(abfd, hdr, name, shindex);
        goto success;
      }
    } else
      /* FIXME: We should handle this section.  */
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB: unknown type [%#x] section `%s'"), abfd, hdr->sh_type, name);

    goto fail;
  }

fail:
  ret = FALSE;
success:
  if (sections_being_created && sections_being_created_abfd == abfd)
    sections_being_created[shindex] = FALSE;
  if (--nesting == 0) {
    sections_being_created = NULL;
    sections_being_created_abfd = abfd;
  }
  return ret;
}

const bfd_target *elf_object_p(bfd *abfd) {
  Elf_External_Ehdr x_ehdr;   /* Elf file header, external form */
  Elf_Internal_Ehdr *i_ehdrp; /* Elf file header, internal form */
  Elf_External_Shdr x_shdr;   /* Section header table entry, external form */
  Elf_Internal_Shdr i_shdr;
  Elf_Internal_Shdr *i_shdrp; /* Section header table, internal form */
  unsigned int shindex;
  const struct elf_backend_data *ebd;
  asection *s;
  bfd_size_type amt;
  const bfd_target *target;

  /* Read in the ELF header in external format.  */

  if (bfd_bread(&x_ehdr, sizeof(x_ehdr), abfd) != sizeof(x_ehdr)) {
    if (bfd_get_error() != bfd_error_system_call)
      goto got_wrong_format_error;
    else
      goto got_no_match;
  }

  /* Now check to see if we have a valid ELF file, and one that BFD can
     make use of.  The magic number must match, the address size ('class')
     and byte-swapping must match our XVEC entry, and it must have a
     section header table (FIXME: See comments re sections at top of this
     file).  */

  if (!elf_file_p(&x_ehdr) || x_ehdr.e_ident[EI_VERSION] != EV_CURRENT ||
      x_ehdr.e_ident[EI_CLASS] != ELFCLASS)
    goto got_wrong_format_error;

  /* Check that file's byte order matches xvec's */
  switch (x_ehdr.e_ident[EI_DATA]) {
  case ELFDATA2MSB: /* Big-endian */
    if (!bfd_header_big_endian(abfd))
      goto got_wrong_format_error;
    break;
  case ELFDATA2LSB: /* Little-endian */
    if (!bfd_header_little_endian(abfd))
      goto got_wrong_format_error;
    break;
  case ELFDATANONE: /* No data encoding specified */
  default:          /* Unknown data encoding specified */
    goto got_wrong_format_error;
  }

  target = abfd->xvec;

  /* Allocate an instance of the elf_obj_tdata structure and hook it up to
     the tdata pointer in the bfd.  */

  if (!(*target->_bfd_set_format[bfd_object])(abfd))
    goto got_no_match;

  /* Now that we know the byte order, swap in the rest of the header */
  i_ehdrp = elf_elfheader(abfd);
  elf_swap_ehdr_in(abfd, &x_ehdr, i_ehdrp);
#if DEBUG & 1
  elf_debug_file(i_ehdrp);
#endif

  /* Reject ET_CORE (header indicates core file, not object file) */
  if (i_ehdrp->e_type == ET_CORE)
    goto got_wrong_format_error;

  /* If this is a relocatable file and there is no section header
     table, then we're hosed.  */
  if (i_ehdrp->e_shoff == 0 && i_ehdrp->e_type == ET_REL)
    goto got_wrong_format_error;

  /* As a simple sanity check, verify that what BFD thinks is the
     size of each section header table entry actually matches the size
     recorded in the file, but only if there are any sections.  */
  if (i_ehdrp->e_shentsize != sizeof(x_shdr) && i_ehdrp->e_shnum != 0)
    goto got_wrong_format_error;

  /* Further sanity check.  */
  if (i_ehdrp->e_shoff == 0 && i_ehdrp->e_shnum != 0)
    goto got_wrong_format_error;

  ebd = get_elf_backend_data(abfd);
  if (ebd->s->arch_size != ARCH_SIZE)
    goto got_wrong_format_error;

  /* Check that the ELF e_machine field matches what this particular
     BFD format expects.  */
  if (ebd->elf_machine_code != i_ehdrp->e_machine &&
      (ebd->elf_machine_alt1 == 0 ||
       i_ehdrp->e_machine != ebd->elf_machine_alt1) &&
      (ebd->elf_machine_alt2 == 0 ||
       i_ehdrp->e_machine != ebd->elf_machine_alt2) &&
      ebd->elf_machine_code != EM_NONE)
    goto got_wrong_format_error;

  if (i_ehdrp->e_type == ET_EXEC)
    abfd->flags |= EXEC_P;
  else if (i_ehdrp->e_type == ET_DYN)
    abfd->flags |= DYNAMIC;

  if (i_ehdrp->e_phnum > 0)
    abfd->flags |= D_PAGED;

  if (!bfd_default_set_arch_mach(abfd, ebd->arch, 0)) {
    /* It's OK if this fails for the generic target.  */
    if (ebd->elf_machine_code != EM_NONE)
      goto got_no_match;
  }

  if (ebd->elf_machine_code != EM_NONE &&
      i_ehdrp->e_ident[EI_OSABI] != ebd->elf_osabi &&
      ebd->elf_osabi != ELFOSABI_NONE)
    goto got_wrong_format_error;

  if (i_ehdrp->e_shoff != 0) {
    file_ptr where = (file_ptr)i_ehdrp->e_shoff;

    /* Seek to the section header table in the file.  */
    if (bfd_seek(abfd, where, SEEK_SET) != 0)
      goto got_no_match;

    /* Read the first section header at index 0, and convert to internal
       form.  */
    if (bfd_bread(&x_shdr, sizeof x_shdr, abfd) != sizeof(x_shdr))
      goto got_no_match;
    elf_swap_shdr_in(abfd, &x_shdr, &i_shdr);

    /* If the section count is zero, the actual count is in the first
       section header.  */
    if (i_ehdrp->e_shnum == SHN_UNDEF) {
      i_ehdrp->e_shnum = i_shdr.sh_size;
      if (i_ehdrp->e_shnum >= SHN_LORESERVE ||
          i_ehdrp->e_shnum != i_shdr.sh_size || i_ehdrp->e_shnum == 0)
        goto got_wrong_format_error;
    }

    /* And similarly for the string table index.  */
    if (i_ehdrp->e_shstrndx == (SHN_XINDEX & 0xffff)) {
      i_ehdrp->e_shstrndx = i_shdr.sh_link;
      if (i_ehdrp->e_shstrndx != i_shdr.sh_link)
        goto got_wrong_format_error;
    }

    /* And program headers.  */
    if (i_ehdrp->e_phnum == PN_XNUM && i_shdr.sh_info != 0) {
      i_ehdrp->e_phnum = i_shdr.sh_info;
      if (i_ehdrp->e_phnum != i_shdr.sh_info)
        goto got_wrong_format_error;
    }

    /* Sanity check that we can read all of the section headers.
       It ought to be good enough to just read the last one.  */
    if (i_ehdrp->e_shnum != 1) {
      /* Check that we don't have a totally silly number of sections.  */
      if (i_ehdrp->e_shnum > (unsigned int)-1 / sizeof(x_shdr) ||
          i_ehdrp->e_shnum > (unsigned int)-1 / sizeof(i_shdr))
        goto got_wrong_format_error;

      where += (i_ehdrp->e_shnum - 1) * sizeof(x_shdr);
      if ((bfd_size_type)where <= i_ehdrp->e_shoff)
        goto got_wrong_format_error;

      if (bfd_seek(abfd, where, SEEK_SET) != 0)
        goto got_no_match;
      if (bfd_bread(&x_shdr, sizeof x_shdr, abfd) != sizeof(x_shdr))
        goto got_no_match;

      /* Back to where we were.  */
      where = i_ehdrp->e_shoff + sizeof(x_shdr);
      if (bfd_seek(abfd, where, SEEK_SET) != 0)
        goto got_no_match;
    }
  }

  /* Allocate space for a copy of the section header table in
     internal form.  */
  if (i_ehdrp->e_shnum != 0) {
    Elf_Internal_Shdr *shdrp;
    unsigned int num_sec;

#ifndef BFD64
    if (i_ehdrp->e_shnum > ((bfd_size_type)-1) / sizeof(*i_shdrp))
      goto got_wrong_format_error;
#endif
    amt = sizeof(*i_shdrp) * (bfd_size_type)i_ehdrp->e_shnum;
    i_shdrp = (Elf_Internal_Shdr *)bfd_alloc(abfd, amt);
    if (!i_shdrp)
      goto got_no_match;
    num_sec = i_ehdrp->e_shnum;
    elf_numsections(abfd) = num_sec;
    amt = sizeof(i_shdrp) * num_sec;
    elf_elfsections(abfd) = (Elf_Internal_Shdr **)bfd_alloc(abfd, amt);
    if (!elf_elfsections(abfd))
      goto got_no_match;

    memcpy(i_shdrp, &i_shdr, sizeof(*i_shdrp));
    for (shdrp = i_shdrp, shindex = 0; shindex < num_sec; shindex++)
      elf_elfsections(abfd)[shindex] = shdrp++;

    /* Read in the rest of the section header table and convert it
       to internal form.  */
    for (shindex = 1; shindex < i_ehdrp->e_shnum; shindex++) {
      if (bfd_bread(&x_shdr, sizeof x_shdr, abfd) != sizeof(x_shdr))
        goto got_no_match;
      elf_swap_shdr_in(abfd, &x_shdr, i_shdrp + shindex);

      /* Sanity check sh_link and sh_info.  */
      if (i_shdrp[shindex].sh_link >= num_sec) {
        /* PR 10478: Accept Solaris binaries with a sh_link
           field set to SHN_BEFORE or SHN_AFTER.  */
        switch (ebd->elf_machine_code) {
        case EM_386:
        case EM_IAMCU:
        case EM_X86_64:
        case EM_OLD_SPARCV9:
        case EM_SPARC32PLUS:
        case EM_SPARCV9:
        case EM_SPARC:
          if (i_shdrp[shindex].sh_link ==
                  (SHN_LORESERVE & 0xffff) /* SHN_BEFORE */
              || i_shdrp[shindex].sh_link ==
                     ((SHN_LORESERVE + 1) & 0xffff) /* SHN_AFTER */)
            break;
          /* Otherwise fall through.  */
        default:
          goto got_wrong_format_error;
        }
      }

      if (((i_shdrp[shindex].sh_flags & SHF_INFO_LINK) ||
           i_shdrp[shindex].sh_type == SHT_RELA ||
           i_shdrp[shindex].sh_type == SHT_REL) &&
          i_shdrp[shindex].sh_info >= num_sec)
        goto got_wrong_format_error;

      /* If the section is loaded, but not page aligned, clear
         D_PAGED.  */
      if (i_shdrp[shindex].sh_size != 0 &&
          (i_shdrp[shindex].sh_flags & SHF_ALLOC) != 0 &&
          i_shdrp[shindex].sh_type != SHT_NOBITS &&
          (((i_shdrp[shindex].sh_addr - i_shdrp[shindex].sh_offset) %
            ebd->minpagesize) != 0))
        abfd->flags &= ~D_PAGED;
    }
  }

  /* A further sanity check.  */
  if (i_ehdrp->e_shnum != 0) {
    if (i_ehdrp->e_shstrndx >= elf_numsections(abfd)) {
      /* PR 2257:
         We used to just goto got_wrong_format_error here
         but there are binaries in existance for which this test
         will prevent the binutils from working with them at all.
         So we are kind, and reset the string index value to 0
         so that at least some processing can be done.  */
      i_ehdrp->e_shstrndx = SHN_UNDEF;
      _bfd_error_handler(
          _("warning: %pB has a corrupt string table index - ignoring"), abfd);
    }
  } else if (i_ehdrp->e_shstrndx != SHN_UNDEF)
    goto got_wrong_format_error;

  /* Read in the program headers.  */
  if (i_ehdrp->e_phnum == 0)
    elf_tdata(abfd)->phdr = NULL;
  else {
    Elf_Internal_Phdr *i_phdr;
    unsigned int i;

#ifndef BFD64
    if (i_ehdrp->e_phnum > ((bfd_size_type)-1) / sizeof(*i_phdr))
      goto got_wrong_format_error;
#endif
    amt = (bfd_size_type)i_ehdrp->e_phnum * sizeof(*i_phdr);
    elf_tdata(abfd)->phdr = (Elf_Internal_Phdr *)bfd_alloc(abfd, amt);
    if (elf_tdata(abfd)->phdr == NULL)
      goto got_no_match;
    if (bfd_seek(abfd, (file_ptr)i_ehdrp->e_phoff, SEEK_SET) != 0)
      goto got_no_match;
    i_phdr = elf_tdata(abfd)->phdr;
    for (i = 0; i < i_ehdrp->e_phnum; i++, i_phdr++) {
      Elf_External_Phdr x_phdr;

      if (bfd_bread(&x_phdr, sizeof x_phdr, abfd) != sizeof x_phdr)
        goto got_no_match;
      elf_swap_phdr_in(abfd, &x_phdr, i_phdr);
    }
  }

  if (i_ehdrp->e_shstrndx != 0 && i_ehdrp->e_shoff != 0) {
    unsigned int num_sec;

    /* Once all of the section headers have been read and converted, we
       can start processing them.  Note that the first section header is
       a dummy placeholder entry, so we ignore it.  */
    num_sec = elf_numsections(abfd);
    for (shindex = 1; shindex < num_sec; shindex++)
      if (!bfd_section_from_shdr(abfd, shindex))
        goto got_no_match;

    /* Set up ELF sections for SHF_GROUP and SHF_LINK_ORDER.  */
    if (!_bfd_elf_setup_sections(abfd))
      goto got_wrong_format_error;
  }

  /* Let the backend double check the format and override global
     information.  */
  if (ebd->elf_backend_object_p) {
    if (!(*ebd->elf_backend_object_p)(abfd))
      goto got_wrong_format_error;
  }

  /* Remember the entry point specified in the ELF file header.  */
  bfd_set_start_address(abfd, i_ehdrp->e_entry);

  /* If we have created any reloc sections that are associated with
     debugging sections, mark the reloc sections as debugging as well.  */
  for (s = abfd->sections; s != NULL; s = s->next) {
    if ((elf_section_data(s)->this_hdr.sh_type == SHT_REL ||
         elf_section_data(s)->this_hdr.sh_type == SHT_RELA) &&
        elf_section_data(s)->this_hdr.sh_info > 0) {
      unsigned long targ_index;
      asection *targ_sec;

      targ_index = elf_section_data(s)->this_hdr.sh_info;
      targ_sec = bfd_section_from_elf_index(abfd, targ_index);
      if (targ_sec != NULL && (targ_sec->flags & SEC_DEBUGGING) != 0)
        s->flags |= SEC_DEBUGGING;
    }
  }
  return target;

got_wrong_format_error:
  bfd_set_error(bfd_error_wrong_format);

got_no_match:
  return NULL;
}

bfd_boolean bfd_check_format_matches(bfd *abfd, bfd_format format,
                                     char ***matching) {
  extern const bfd_target binary_vec;
#if BFD_SUPPORTS_PLUGINS
  extern const bfd_target plugin_vec;
#endif
  const bfd_target *const *target;
  const bfd_target **matching_vector = NULL;
  const bfd_target *save_targ, *right_targ, *ar_right_targ, *match_targ;
  int match_count, best_count, best_match;
  int ar_match_index;
  struct bfd_preserve preserve;

  if (matching != NULL)
    *matching = NULL;

  if (!bfd_read_p(abfd) ||
      (unsigned int)abfd->format >= (unsigned int)bfd_type_end) {
    bfd_set_error(bfd_error_invalid_operation);
    return FALSE;
  }

  if (abfd->format != bfd_unknown)
    return abfd->format == format;

  if (matching != NULL || *bfd_associated_vector != NULL) {
    bfd_size_type amt;

    amt = sizeof(*matching_vector) * 2 * _bfd_target_vector_entries;
    matching_vector = (const bfd_target **)bfd_malloc(amt);
    if (!matching_vector)
      return FALSE;
  }

  /* Presume the answer is yes.  */
  abfd->format = format;
  save_targ = abfd->xvec;
  preserve.marker = NULL;

  /* If the target type was explicitly specified, just check that target.  */
  if (!abfd->target_defaulted) {
    if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0) /* rewind! */
      goto err_ret;

    right_targ = BFD_SEND_FMT(abfd, _bfd_check_format, (abfd));

    if (right_targ)
      goto ok_ret;

    /* For a long time the code has dropped through to check all
       targets if the specified target was wrong.  I don't know why,
       and I'm reluctant to change it.  However, in the case of an
       archive, it can cause problems.  If the specified target does
       not permit archives (e.g., the binary target), then we should
       not allow some other target to recognize it as an archive, but
       should instead allow the specified target to recognize it as an
       object.  When I first made this change, it broke the PE target,
       because the specified pei-i386 target did not recognize the
       actual pe-i386 archive.  Since there may be other problems of
       this sort, I changed this test to check only for the binary
       target.  */
    if (format == bfd_archive && save_targ == &binary_vec)
      goto err_unrecog;
  }

  /* Since the target type was defaulted, check them all in the hope
     that one will be uniquely recognized.  */
  right_targ = NULL;
  ar_right_targ = NULL;
  match_targ = NULL;
  best_match = 256;
  best_count = 0;
  match_count = 0;
  ar_match_index = _bfd_target_vector_entries;

  for (target = bfd_target_vector; *target != NULL; target++) {
    const bfd_target *temp;

    /* Don't check the default target twice.  */
    if (*target == &binary_vec ||
        (!abfd->target_defaulted && *target == save_targ) ||
        (*target)->match_priority > best_match)
      continue;

    /* If we already tried a match, the bfd is modified and may
       have sections attached, which will confuse the next
       _bfd_check_format call.  */
    bfd_reinit(abfd);

    /* Change BFD's target temporarily.  */
    abfd->xvec = *target;

    if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0)
      goto err_ret;

    /* If _bfd_check_format neglects to set bfd_error, assume
       bfd_error_wrong_format.  We didn't used to even pay any
       attention to bfd_error, so I suspect that some
       _bfd_check_format might have this problem.  */
    bfd_set_error(bfd_error_wrong_format);

    temp = BFD_SEND_FMT(abfd, _bfd_check_format, (abfd));
    if (temp) {
      int match_priority = temp->match_priority;
#if BFD_SUPPORTS_PLUGINS
      /* If this object can be handled by a plugin, give that the
         lowest priority; objects both handled by a plugin and
         with an underlying object format will be claimed
         separately by the plugin.  */
      if (*target == &plugin_vec)
        match_priority = (*target)->match_priority;
#endif

      match_targ = temp;
      if (preserve.marker != NULL)
        bfd_preserve_finish(abfd, &preserve);

      if (abfd->format != bfd_archive ||
          (bfd_has_map(abfd) &&
           bfd_get_error() != bfd_error_wrong_object_format)) {
        /* This format checks out as ok!  */
        right_targ = temp;

        /* If this is the default target, accept it, even if
           other targets might match.  People who want those
           other targets have to set the GNUTARGET variable.  */
        if (temp == bfd_default_vector[0])
          goto ok_ret;

        if (matching_vector)
          matching_vector[match_count] = temp;
        match_count++;

        if (match_priority < best_match) {
          best_match = match_priority;
          best_count = 0;
        }
        best_count++;
      } else {
        /* An archive with no armap or objects of the wrong
           type.  We want this target to match if we get no
           better matches.  */
        if (ar_right_targ != bfd_default_vector[0])
          ar_right_targ = *target;
        if (matching_vector)
          matching_vector[ar_match_index] = *target;
        ar_match_index++;
      }

      if (!bfd_preserve_save(abfd, &preserve))
        goto err_ret;
    } else if (bfd_get_error() != bfd_error_wrong_format)
      goto err_ret;
  }

  if (best_count == 1)
    match_count = 1;

  if (match_count == 0) {
    /* Try partial matches.  */
    right_targ = ar_right_targ;

    if (right_targ == bfd_default_vector[0]) {
      match_count = 1;
    } else {
      match_count = ar_match_index - _bfd_target_vector_entries;

      if (matching_vector && match_count > 1)
        memcpy(matching_vector, matching_vector + _bfd_target_vector_entries,
               sizeof(*matching_vector) * match_count);
    }
  }

  /* We have more than one equally good match.  If any of the best
     matches is a target in config.bfd targ_defvec or targ_selvecs,
     choose it.  */
  if (match_count > 1) {
    const bfd_target *const *assoc = bfd_associated_vector;

    while ((right_targ = *assoc++) != NULL) {
      int i = match_count;

      while (--i >= 0)
        if (matching_vector[i] == right_targ &&
            right_targ->match_priority <= best_match)
          break;

      if (i >= 0) {
        match_count = 1;
        break;
      }
    }
  }

  /* We still have more than one equally good match, and at least some
     of the targets support match priority.  Choose the first of the
     best matches.  */
  if (matching_vector && match_count > 1 && best_count != match_count) {
    int i;

    for (i = 0; i < match_count; i++) {
      right_targ = matching_vector[i];
      if (right_targ->match_priority <= best_match)
        break;
    }
    match_count = 1;
  }

  /* There is way too much undoing of half-known state here.  We
     really shouldn't iterate on live bfd's.  Note that saving the
     whole bfd and restoring it would be even worse; the first thing
     you notice is that the cached bfd file position gets out of sync.  */
  if (preserve.marker != NULL)
    bfd_preserve_restore(abfd, &preserve);

  if (match_count == 1) {
    abfd->xvec = right_targ;
    /* If we come out of the loop knowing that the last target that
       matched is the one we want, then ABFD should still be in a usable
       state (except possibly for XVEC).  */
    if (match_targ != right_targ) {
      bfd_reinit(abfd);
      if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0)
        goto err_ret;
      match_targ = BFD_SEND_FMT(abfd, _bfd_check_format, (abfd));
      BFD_ASSERT(match_targ != NULL);
    }

  ok_ret:
    /* If the file was opened for update, then `output_has_begun'
       some time ago when the file was created.  Do not recompute
       sections sizes or alignments in _bfd_set_section_contents.
       We can not set this flag until after checking the format,
       because it will interfere with creation of BFD sections.  */
    if (abfd->direction == both_direction)
      abfd->output_has_begun = TRUE;

    if (matching_vector)
      free(matching_vector);

    /* File position has moved, BTW.  */
    return TRUE;
  }

  if (match_count == 0) {
  err_unrecog:
    bfd_set_error(bfd_error_file_not_recognized);
  err_ret:
    abfd->xvec = save_targ;
    abfd->format = bfd_unknown;
    if (matching_vector)
      free(matching_vector);
    if (preserve.marker != NULL)
      bfd_preserve_restore(abfd, &preserve);
    return FALSE;
  }

  /* Restore original target type and format.  */
  abfd->xvec = save_targ;
  abfd->format = bfd_unknown;
  bfd_set_error(bfd_error_file_ambiguously_recognized);

  if (matching) {
    *matching = (char **)matching_vector;
    matching_vector[match_count] = NULL;
    /* Return target names.  This is a little nasty.  Maybe we
       should do another bfd_malloc?  */
    while (--match_count >= 0) {
      const char *name = matching_vector[match_count]->name;
      *(const char **)&matching_vector[match_count] = name;
    }
  }
  return FALSE;
}


static void copy_file(const char *input_filename, const char *output_filename,
                      const char *input_target, const char *output_target,
                      const bfd_arch_info_type *input_arch) {
  bfd *ibfd;
  char **obj_matching;
  char **core_matching;
  off_t size = get_file_size(input_filename);

  if (size < 1) {
    if (size == 0)
      non_fatal(_("error: the input file '%s' is empty"), input_filename);
    status = 1;
    return;
  }

  /* To allow us to do "strip *" without dying on the first
     non-object file, failures are nonfatal.  */
  ibfd = bfd_openr(input_filename, input_target);
  if (ibfd == NULL) {
    bfd_nonfatal_message(input_filename, NULL, NULL, NULL);
    status = 1;
    return;
  }

  switch (do_debug_sections) {
  case compress:
  case compress_zlib:
  case compress_gnu_zlib:
  case compress_gabi_zlib:
    ibfd->flags |= BFD_COMPRESS;
    /* Don't check if input is ELF here since this information is
       only available after bfd_check_format_matches is called.  */
    if (do_debug_sections != compress_gnu_zlib)
      ibfd->flags |= BFD_COMPRESS_GABI;
    break;
  case decompress:
    ibfd->flags |= BFD_DECOMPRESS;
    break;
  default:
    break;
  }

  switch (do_elf_stt_common) {
  case elf_stt_common:
    ibfd->flags |= BFD_CONVERT_ELF_COMMON | BFD_USE_ELF_STT_COMMON;
    break;
    break;
  case no_elf_stt_common:
    ibfd->flags |= BFD_CONVERT_ELF_COMMON;
    break;
  default:
    break;
  }

  if (bfd_check_format(ibfd, bfd_archive)) {
    bfd_boolean force_output_target;
    bfd *obfd;

    /* bfd_get_target does not return the correct value until
       bfd_check_format succeeds.  */
    if (output_target == NULL) {
      output_target = bfd_get_target(ibfd);
      force_output_target = FALSE;
    } else
      force_output_target = TRUE;

    obfd = bfd_openw(output_filename, output_target);
    if (obfd == NULL) {
      bfd_nonfatal_message(output_filename, NULL, NULL, NULL);
      status = 1;
      return;
    }
    /* This is a no-op on non-Coff targets.  */
    set_long_section_mode(obfd, ibfd, long_section_names);

    copy_archive(ibfd, obfd, output_target, force_output_target, input_arch);
  } else if (bfd_check_format_matches(ibfd, bfd_object, &obj_matching)) {
    bfd *obfd;
  do_copy:

    /* bfd_get_target does not return the correct value until
       bfd_check_format succeeds.  */
    if (output_target == NULL)
      output_target = bfd_get_target(ibfd);

    obfd = bfd_openw(output_filename, output_target);
    if (obfd == NULL) {
      bfd_nonfatal_message(output_filename, NULL, NULL, NULL);
      status = 1;
      return;
    }
    /* This is a no-op on non-Coff targets.  */
    set_long_section_mode(obfd, ibfd, long_section_names);

    if (!copy_object(ibfd, obfd, input_arch))
      status = 1;

    /* PR 17512: file: 0f15796a.
       If the file could not be copied it may not be in a writeable
       state.  So use bfd_close_all_done to avoid the possibility of
       writing uninitialised data into the file.  */
    if (!(status ? bfd_close_all_done(obfd) : bfd_close(obfd))) {
      status = 1;
      bfd_nonfatal_message(output_filename, NULL, NULL, NULL);
      return;
    }

    if (!bfd_close(ibfd)) {
      status = 1;
      bfd_nonfatal_message(input_filename, NULL, NULL, NULL);
      return;
    }
  } else {
    bfd_error_type obj_error = bfd_get_error();
    bfd_error_type core_error;

    if (bfd_check_format_matches(ibfd, bfd_core, &core_matching)) {
      /* This probably can't happen..  */
      if (obj_error == bfd_error_file_ambiguously_recognized)
        free(obj_matching);
      goto do_copy;
    }

    core_error = bfd_get_error();
    /* Report the object error in preference to the core error.  */
    if (obj_error != core_error)
      bfd_set_error(obj_error);

    bfd_nonfatal_message(input_filename, NULL, NULL, NULL);

    if (obj_error == bfd_error_file_ambiguously_recognized) {
      list_matching_formats(obj_matching);
      free(obj_matching);
    }
    if (core_error == bfd_error_file_ambiguously_recognized) {
      list_matching_formats(core_matching);
      free(core_matching);
    }

    status = 1;
  }
}
