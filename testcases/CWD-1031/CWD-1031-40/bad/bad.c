#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Basic types */
typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;
typedef unsigned long bfd_size_type;
typedef unsigned long symvalue;
typedef unsigned int flagword;
typedef unsigned char bfd_byte;
typedef long file_ptr;
typedef unsigned long ufile_ptr;

#define BFD_VMA_FMT "l"
#define sprintf_vma(s, x) sprintf(s, "%08" BFD_VMA_FMT "x", x)
#define fprintf_vma(f, x) fprintf(f, "%08" BFD_VMA_FMT "x", x)
#define printf_vma(x) fprintf_vma(stdout, x)

/* ATTRIBUTE_UNUSED macro */
#define ATTRIBUTE_UNUSED

/* Endian enum */
enum bfd_endian { BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE, BFD_ENDIAN_UNKNOWN };

/* File format enum */
typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

/* BFD error type */
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
  bfd_error_on_input,
  bfd_error_invalid_error_code
} bfd_error_type;

/* BFD flags */
#define BFD_NO_FLAGS 0x00
#define HAS_RELOC 0x01
#define EXEC_P 0x02
#define HAS_LINENO 0x04
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
#define BFD_DETERMINISTIC_OUTPUT 0x2000
#define BFD_COMPRESS 0x4000
#define BFD_DECOMPRESS 0x8000
#define BFD_PLUGIN 0x10000
#define BFD_COMPRESS_GABI 0x20000
#define BFD_CONVERT_ELF_COMMON 0x40000
#define BFD_USE_ELF_STT_COMMON 0x80000

/* Section flags */
#define SEC_NO_FLAGS 0x000
#define SEC_ALLOC 0x001
#define SEC_LOAD 0x002
#define SEC_RELOC 0x004
#define SEC_READONLY 0x008
#define SEC_CODE 0x010
#define SEC_DATA 0x020
#define SEC_ROM 0x040
#define SEC_HAS_CONTENTS 0x100
#define SEC_NEVER_LOAD 0x200
#define SEC_THREAD_LOCAL 0x400
#define SEC_DEBUGGING 0x2000

/* FOPEN_RB */
#define FOPEN_RB "rb"

/* BFD direction enum */
enum bfd_direction {
  no_direction,
  read_direction,
  write_direction,
  both_direction
};

/* Forward declarations */
typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef struct bfd_section *sec_ptr;
struct bfd_symbol;
typedef struct bfd_symbol asymbol;
typedef struct bfd_target bfd_target;
struct reloc_cache_entry;

/* Relax table */
struct relax_table {
  bfd_vma addr;
  int size;
};

/* Relocation howto */
typedef enum complain_overflow {
  complain_overflow_dont,
  complain_overflow_bitfield,
  complain_overflow_signed,
  complain_overflow_unsigned
} complain_overflow_type;

typedef enum bfd_reloc_status {
  bfd_reloc_ok,
  bfd_reloc_notfound,
  bfd_reloc_overflow,
  bfd_reloc_outofrange,
  bfd_reloc_continue,
  bfd_reloc_notsupported,
  bfd_reloc_other,
  bfd_reloc_dangerous
} bfd_reloc_status_type;

struct reloc_howto_struct {
  unsigned int type;
  unsigned int rightshift;
  int size;
  unsigned int bitsize;
  bfd_boolean pc_relative;
  unsigned int bitpos;
  enum complain_overflow complain_on_overflow;
  bfd_reloc_status_type (*special_function)(bfd *, struct reloc_cache_entry *,
                                            struct bfd_symbol *, void *,
                                            asection *, bfd *, char **);
  char *name;
  bfd_boolean partial_inplace;
  bfd_vma src_mask;
  bfd_vma dst_mask;
  bfd_boolean pcrel_offset;
};
typedef const struct reloc_howto_struct reloc_howto_type;

/* Relocation cache entry */
typedef struct reloc_cache_entry {
  struct bfd_symbol **sym_ptr_ptr;
  bfd_size_type address;
  bfd_vma addend;
  reloc_howto_type *howto;
} arelent;

/* Symbol flags */
#define BSF_NO_FLAGS 0x00
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

/* Symbol structure */
struct bfd_symbol {
  struct bfd *the_bfd;
  const char *name;
  symvalue value;
  flagword flags;
  struct bfd_section *section;
  union {
    void *p;
    bfd_vma i;
  } udata;
};

/* Section structure */
struct bfd_section {
  const char *name;
  unsigned int id;
  unsigned int index;
  struct bfd_section *next;
  struct bfd_section *prev;
  flagword flags;
  bfd_vma vma;
  bfd_vma lma;
  bfd_vma size;
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
  struct bfd_symbol **symbol_ptr_ptr;
  bfd *owner;
  bfd_vma used_by_bfd;
  struct reloc_cache_entry *constructor_chain;
  unsigned int lineno_count;
  unsigned int entsize;
  struct bfd_section *kept_section;
  file_ptr moving_line_filepos;
  int target_index;
  void *used_by_bfd2;
  struct bfd_symbol *symbol;
  union {
    void *link_order;
    struct bfd_section *s;
  } map_head, map_tail;
  bfd_boolean user_set_vma;
};

/* BFD structure */
struct bfd {
  const char *filename;
  const struct bfd_target *xvec;
  void *iostream;
  bfd_boolean cacheable;
  bfd_boolean target_defaulted;
  bfd_boolean opened_once;
  bfd_boolean mtime_set;
  bfd_boolean no_export;
  bfd_boolean output_has_begun;
  bfd_boolean has_armap;
  bfd_boolean is_thin_archive;
  bfd_boolean selective_search;
  bfd_boolean is_linker_output;
  bfd_boolean is_linker_input;
  flagword flags;
  enum bfd_direction direction;
  ufile_ptr origin;
  ufile_ptr proxy_origin;
  void *memory;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  int archive_pass;
  bfd_vma start_address;
  struct bfd_symbol **outsymbols;
  unsigned int symcount;
  unsigned int dynsymcount;
  void *arelt_data;
  struct bfd *my_archive;
  struct bfd *archive_next;
  struct bfd *archive_head;
  struct bfd *nested_archives;
  union {
    struct bfd *next;
    void *hash;
  } link;
  void *tdata;
  void *usrdata;
};

/* Simplified bfd_target definition (preserved as requested) */
struct bfd_target {
  const char *name;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  long (*_bfd_get_synthetic_symtab)(bfd *, long, struct bfd_symbol **, long,
                                    struct bfd_symbol **, struct bfd_symbol **);
  long (*_bfd_canonicalize_dynamic_reloc)(bfd *, arelent **, asymbol **);
};

/* Relocation types for x86_64 */
#define R_X86_64_NONE 0
#define R_X86_64_64 1
#define R_X86_64_PC32 2
#define R_X86_64_GOT32 3
#define R_X86_64_PLT32 4
#define R_X86_64_COPY 5
#define R_X86_64_GLOB_DAT 6
#define R_X86_64_JUMP_SLOT 7
#define R_X86_64_RELATIVE 8
#define R_X86_64_GOTPCREL 9
#define R_X86_64_32 10
#define R_X86_64_32S 11
#define R_X86_64_16 12
#define R_X86_64_PC16 13
#define R_X86_64_8 14
#define R_X86_64_PC8 15
#define R_X86_64_DTPMOD64 16
#define R_X86_64_DTPOFF64 17
#define R_X86_64_TPOFF64 18
#define R_X86_64_TLSGD 19
#define R_X86_64_TLSLD 20
#define R_X86_64_DTPOFF32 21
#define R_X86_64_GOTTPOFF 22
#define R_X86_64_TPOFF32 23
#define R_X86_64_PC64 24
#define R_X86_64_GOTOFF64 25
#define R_X86_64_GOTPC32 26
#define R_X86_64_GOT64 27
#define R_X86_64_GOTPCREL64 28
#define R_X86_64_GOTPC64 29
#define R_X86_64_GOTPLT64 30
#define R_X86_64_PLTOFF64 31
#define R_X86_64_GOTPC32_TLSDESC 34
#define R_X86_64_TLSDESC_CALL 35
#define R_X86_64_TLSDESC 36
#define R_X86_64_IRELATIVE 37

/* Section type constants */
#define SHT_REL 4
#define SHT_RELA 4

/* x86_64 PLT types */
enum elf_x86_64_plt_type {
  plt_non_lazy = 0,
  plt_lazy = 1 << 0,
  plt_second = 1 << 1,
  plt_unknown = -1
};

/* x86_64 PLT layout structures */
struct elf_x86_64_lazy_plt_layout {
  const bfd_byte *plt0_entry;
  const bfd_byte *plt_entry;
  unsigned int plt_entry_size;
  unsigned int plt0_got1_offset;
  unsigned int plt0_got2_offset;
  unsigned int plt0_got2_insn_end;
  unsigned int plt_got_offset;
  unsigned int plt_reloc_offset;
  unsigned int plt_plt_offset;
  unsigned int plt_got_insn_size;
  unsigned int plt_plt_insn_end;
  unsigned int plt_lazy_offset;
  const bfd_byte *eh_frame_plt;
  unsigned int eh_frame_plt_size;
};

struct elf_x86_64_non_lazy_plt_layout {
  const bfd_byte *plt_entry;
  unsigned int plt_entry_size;
  unsigned int plt_got_offset;
  unsigned int plt_got_insn_size;
  const bfd_byte *eh_frame_plt;
  unsigned int eh_frame_plt_size;
};

struct elf_x86_64_plt {
  const char *name;
  asection *sec;
  bfd_byte *contents;
  enum elf_x86_64_plt_type type;
  unsigned int plt_got_offset;
  unsigned int plt_got_insn_size;
  unsigned int plt_entry_size;
  long count;
};

/* ELF section header */
struct elf_internal_shdr {
  unsigned long sh_link;
  unsigned long sh_type;
  unsigned long sh_entsize;
};

/* ELF section data for backend */
struct elf_obj_tdata {
  unsigned int elfclass;
  bfd_boolean (*slurp_reloc_table)(bfd *, asection *, asymbol **, bfd_boolean);
};

/* ELF backend data */
struct elf_backend_data {
  void *arch_data;
  struct elf_obj_tdata *s;
};

struct elf_x86_64_backend_data {
  enum { is_normal, is_nacl } os;
};

#define get_elf_backend_data(abfd) ((struct elf_backend_data *)((abfd)->tdata))
#define get_elf_x86_64_arch_data(bed)                                          \
  ((const struct elf_x86_64_backend_data *)(bed)->arch_data)
#define get_elf_x86_64_backend_data(abfd)                                      \
  get_elf_x86_64_arch_data(get_elf_backend_data(abfd))

#define ABI_64_P(abfd) (get_elf_backend_data(abfd)->s->elfclass == 2)

/* ELF section data */
struct elf_section_data {
  struct elf_internal_shdr this_hdr;
};
#define elf_section_data(sec) ((struct elf_section_data *)((sec)->used_by_bfd2))

/* dynsymtab */
#define elf_dynsymtab(abfd) ((abfd)->dynsymcount)

/* H_GET_32 macro */
#define H_GET_32 bfd_h_get_32

/* Internationalization macro */
#define _(x) (x)

/* BFD_SEND macro */
#define BFD_SEND(bfd, message, arglist) ((*((bfd)->xvec->message))arglist)

/* BFD macros */
#define bfd_canonicalize_dynamic_reloc(abfd, arels, asyms)                     \
  BFD_SEND(abfd, _bfd_canonicalize_dynamic_reloc, (abfd, arels, asyms))
#define bfd_get_synthetic_symtab(abfd, count, syms, dyncount, dynsyms, ret)    \
  BFD_SEND(abfd, _bfd_get_synthetic_symtab,                                    \
           (abfd, count, syms, dyncount, dynsyms, ret))

/* External variables (preserved simplified definitions) */
const bfd_target x86_64_elf64_vec = {"elf64-x86-64", BFD_ENDIAN_LITTLE,
                                     BFD_ENDIAN_LITTLE, 0, 0};

extern const bfd_target *i386_coff_vec;
extern const bfd_target *bfd_default_vector[];
extern const bfd_target *bfd_target_vector[];

static const bfd_target *const _bfd_target_vector[] = {&x86_64_elf64_vec, NULL};

/* PLT layout external variables */
extern const struct elf_x86_64_lazy_plt_layout elf_x86_64_lazy_plt;
extern const struct elf_x86_64_non_lazy_plt_layout elf_x86_64_non_lazy_plt;
extern const struct elf_x86_64_lazy_plt_layout elf_x86_64_lazy_bnd_plt;
extern const struct elf_x86_64_non_lazy_plt_layout elf_x86_64_non_lazy_bnd_plt;
extern const struct elf_x86_64_lazy_plt_layout elf_x86_64_lazy_ibt_plt;
extern const struct elf_x86_64_non_lazy_plt_layout elf_x86_64_non_lazy_ibt_plt;
extern const struct elf_x86_64_lazy_plt_layout elf_x32_lazy_ibt_plt;
extern const struct elf_x86_64_non_lazy_plt_layout elf_x32_non_lazy_ibt_plt;
extern const struct elf_x86_64_lazy_plt_layout elf_x86_64_nacl_plt;

/* Function declarations */
extern void bfd_set_error(bfd_error_type error_tag, ...);
extern bfd_error_type bfd_get_error(void);
extern void *bfd_malloc(bfd_size_type size);
extern void *bfd_zmalloc(bfd_size_type size);
extern bfd_vma bfd_h_get_32(bfd *, const void *);
extern long bfd_get_dynamic_reloc_upper_bound(bfd *abfd);
extern long bfd_get_dynamic_symtab_upper_bound(bfd *abfd);
extern asection *bfd_get_section_by_name(bfd *abfd, const char *name);
extern bfd_boolean bfd_get_section_contents(bfd *abfd, asection *section,
                                            void *location, file_ptr offset,
                                            bfd_size_type count);
extern const char *bfd_get_filename(bfd *abfd);
extern bfd *bfd_openr(const char *filename, const char *target);
extern bfd_boolean bfd_close(bfd *abfd);
extern bfd_boolean bfd_close_all_done(bfd *abfd);
extern bfd_boolean bfd_check_format(bfd *abfd, bfd_format format);
extern bfd_boolean bfd_check_format_matches(bfd *abfd, bfd_format format,
                                            char ***matching);
extern bfd *bfd_openr_next_archived_file(bfd *archive, bfd *previous);
extern void bfd_map_over_sections(bfd *abfd,
                                  void (*operation_func)(bfd *, asection *,
                                                         void *),
                                  void *user_storage);
extern bfd_boolean bfd_set_cacheable(bfd *abfd, bfd_boolean val);
extern char *xstrdup(const char *s);
extern int close(int fd);
extern void free(void *ptr);
extern void qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));
extern int memcmp(const void *s1, const void *s2, size_t n);
extern size_t strlen(const char *s);
extern void *memcpy(void *dest, const void *src, size_t n);
extern char *getenv(const char *name);
extern int strcmp(const char *s1, const char *s2);

/* Internal BFD functions */
extern bfd *_bfd_new_bfd(void);
extern void _bfd_delete_bfd(bfd *abfd);
extern bfd_boolean bfd_cache_init(bfd *abfd);

/* ELF functions */
extern long _bfd_elf_canonicalize_dynamic_reloc(bfd *abfd, arelent **storage,
                                                asymbol **syms);

/* objdump global variables */
extern int adjust_section_vma;
extern int dump_debugging_tags;
extern int suppress_bfd_header;
extern int dump_ar_hdrs;
extern int dump_file_header;
extern int dump_private_headers;
extern void *dump_private_options;
extern int dump_symtab;
extern int dump_reloc_info;
extern int disassemble;
extern int dump_debugging;
extern int dump_dwarf_section_info;
extern int dump_section_headers;
extern int dump_dynamic_symtab;
extern int dump_dynamic_reloc_info;
extern int dump_section_contents;
extern int dump_stab_section_info;
extern asymbol **syms;
extern asymbol **dynsyms;
extern asymbol *synthsyms;
extern long symcount;
extern long dynsymcount;
extern long synthcount;

/* objdump functions */
extern void adjust_addresses(bfd *abfd, asection *section, void *arg);
extern void print_arelt_descr(FILE *stream, bfd *abfd, bfd_boolean verbose);
extern void dump_bfd_header(bfd *abfd);
extern void dump_bfd_private_header(bfd *abfd);
extern void dump_target_specific(bfd *abfd);
extern asymbol **slurp_symtab(bfd *abfd);
extern void dump_headers(bfd *abfd);
extern asymbol **slurp_dynamic_symtab(bfd *abfd);
extern void dump_symbols(bfd *abfd, bfd_boolean dynamic);
extern void dump_dwarf(bfd *abfd);
extern void dump_stabs(bfd *abfd);
extern void dump_relocs(bfd *abfd);
extern void dump_dynamic_relocs(bfd *abfd);
extern void dump_data(bfd *abfd);
extern void disassemble_data(bfd *abfd);
extern void *read_debugging_info(bfd *abfd, asymbol **syms, long symcount,
                                 bfd_boolean dynamic);
extern bfd_boolean
print_debugging_info(FILE *stream, void *dhandle, bfd *abfd, asymbol **syms,
                     char *(*demangler)(bfd *, const char *, int),
                     bfd_boolean include_tagname);
extern char *bfd_demangle(bfd *, const char *, int);
extern void non_fatal(const char *message, ...);
extern void fatal(const char *message, ...);
extern void nonfatal(const char *message);
extern void list_matching_formats(char **matching);
extern long get_file_size(const char *file_name);
extern int compare_relocs(const void *ap, const void *bp);
extern int exit_status;
extern void dwarf_select_sections_all(void);

/* bfd_sprintf_vma */
extern void bfd_sprintf_vma(bfd *, char *, bfd_vma);

/* find_target */
extern const bfd_target *find_target(const char *name);

/* File operations */
extern FILE *_bfd_real_fopen(const char *filename, const char *mode);
extern FILE *fdopen(int fd, const char *mode);

/* Original code from bad.c */
long _bfd_elf_canonicalize_dynamic_reloc(bfd *abfd, arelent **storage,
                                         asymbol **syms) {
  bfd_boolean (*slurp_relocs)(bfd *, asection *, asymbol **, bfd_boolean);
  asection *s;
  long ret;

  if (elf_dynsymtab(abfd) == 0) {
    bfd_set_error(bfd_error_invalid_operation);
    return -1;
  }

  slurp_relocs = get_elf_backend_data(abfd)->s->slurp_reloc_table;
  ret = 0;
  for (s = abfd->sections; s != NULL; s = s->next) {
    if (elf_section_data(s)->this_hdr.sh_link == elf_dynsymtab(abfd) &&
        (elf_section_data(s)->this_hdr.sh_type == SHT_REL ||
         elf_section_data(s)->this_hdr.sh_type == SHT_RELA)) {
      arelent *p;
      long count, i;

      if (!(*slurp_relocs)(abfd, s, syms, TRUE))
        return -1;
      count = s->size / elf_section_data(s)->this_hdr.sh_entsize;
      p = s->relocation;
      for (i = 0; i < count; i++)
        *storage++ = p++;
      ret += count;
    }
  }

  *storage = NULL;

  return ret;
}

static long _bfd_elf_get_synthetic_symtab(bfd *abfd,
                                          long symcount ATTRIBUTE_UNUSED,
                                          asymbol **syms ATTRIBUTE_UNUSED,
                                          long dynsymcount, asymbol **dynsyms,
                                          asymbol **ret) {
  long size, count, i, n;
  int j;
  unsigned int plt_got_offset, plt_entry_size, plt_got_insn_size;
  asymbol *s;
  bfd_byte *plt_contents;
  long dynrelcount, relsize;
  arelent **dynrelbuf;
  const struct elf_x86_64_lazy_plt_layout *lazy_plt;
  const struct elf_x86_64_non_lazy_plt_layout *non_lazy_plt;
  const struct elf_x86_64_lazy_plt_layout *lazy_bnd_plt;
  const struct elf_x86_64_non_lazy_plt_layout *non_lazy_bnd_plt;
  const struct elf_x86_64_lazy_plt_layout *lazy_ibt_plt;
  const struct elf_x86_64_non_lazy_plt_layout *non_lazy_ibt_plt;
  asection *plt;
  char *names;
  enum elf_x86_64_plt_type plt_type;
  struct elf_x86_64_plt plts[] = {
      {".plt", NULL, NULL, plt_unknown, 0, 0, 0, 0},
      {".plt.got", NULL, NULL, plt_non_lazy, 0, 0, 0, 0},
      {".plt.sec", NULL, NULL, plt_second, 0, 0, 0, 0},
      {".plt.bnd", NULL, NULL, plt_second, 0, 0, 0, 0},
      {NULL, NULL, NULL, plt_non_lazy, 0, 0, 0, 0}};

  *ret = NULL;

  if ((abfd->flags & (DYNAMIC | EXEC_P)) == 0)
    return 0;

  if (dynsymcount <= 0)
    return 0;

  relsize = bfd_get_dynamic_reloc_upper_bound(abfd);
  if (relsize <= 0)
    return -1;

  dynrelbuf = (arelent **)bfd_malloc(relsize);
  if (dynrelbuf == NULL)
    return -1;

  dynrelcount = bfd_canonicalize_dynamic_reloc(abfd, dynrelbuf, dynsyms);
  if (dynrelcount < 0)
    return -1;

  /* Sort the relocs by address.  */
  qsort(dynrelbuf, dynrelcount, sizeof(arelent *), compare_relocs);

  if (get_elf_x86_64_backend_data(abfd)->os == is_normal) {
    lazy_plt = &elf_x86_64_lazy_plt;
    non_lazy_plt = &elf_x86_64_non_lazy_plt;
    lazy_bnd_plt = &elf_x86_64_lazy_bnd_plt;
    non_lazy_bnd_plt = &elf_x86_64_non_lazy_bnd_plt;
    if (ABI_64_P(abfd)) {
      lazy_ibt_plt = &elf_x86_64_lazy_ibt_plt;
      non_lazy_ibt_plt = &elf_x86_64_non_lazy_ibt_plt;
    } else {
      lazy_ibt_plt = &elf_x32_lazy_ibt_plt;
      non_lazy_ibt_plt = &elf_x32_non_lazy_ibt_plt;
    }
  } else {
    lazy_plt = &elf_x86_64_nacl_plt;
    non_lazy_plt = NULL;
    lazy_bnd_plt = NULL;
    non_lazy_bnd_plt = NULL;
    lazy_ibt_plt = NULL;
    non_lazy_ibt_plt = NULL;
  }

  count = 0;
  for (j = 0; plts[j].name != NULL; j++) {
    plt = bfd_get_section_by_name(abfd, plts[j].name);
    if (plt == NULL || plt->size == 0)
      continue;

    /* Get the PLT section contents.  */
    plt_contents = (bfd_byte *)bfd_malloc(plt->size);
    if (plt_contents == NULL)
      break;
    if (!bfd_get_section_contents(abfd, (asection *)plt, plt_contents, 0,
                                  plt->size)) {
      free(plt_contents);
      break;
    }

    /* Check what kind of PLT it is.  */
    plt_type = plt_unknown;
    if (plts[j].type == plt_unknown &&
        (plt->size >= (lazy_plt->plt_entry_size + lazy_plt->plt_entry_size))) {
      /* Match lazy PLT first.  Need to check the first two
         instructions.   */
      if ((memcmp(plt_contents, lazy_plt->plt0_entry,
                  lazy_plt->plt0_got1_offset) == 0) &&
          (memcmp(plt_contents + 6, lazy_plt->plt0_entry + 6, 2) == 0))
        plt_type = plt_lazy;
      else if (lazy_bnd_plt != NULL &&
               (memcmp(plt_contents, lazy_bnd_plt->plt0_entry,
                       lazy_bnd_plt->plt0_got1_offset) == 0) &&
               (memcmp(plt_contents + 6, lazy_bnd_plt->plt0_entry + 6, 3) ==
                0)) {
        plt_type = plt_lazy | plt_second;
        /* The fist entry in the lazy IBT PLT is the same as the
           lazy BND PLT.  */
        if ((memcmp(plt_contents + lazy_ibt_plt->plt_entry_size,
                    lazy_ibt_plt->plt_entry,
                    lazy_ibt_plt->plt_got_offset) == 0))
          lazy_plt = lazy_ibt_plt;
        else
          lazy_plt = lazy_bnd_plt;
      }
    }

    if (non_lazy_plt != NULL &&
        (plt_type == plt_unknown || plt_type == plt_non_lazy) &&
        plt->size >= non_lazy_plt->plt_entry_size) {
      /* Match non-lazy PLT.  */
      if (memcmp(plt_contents, non_lazy_plt->plt_entry,
                 non_lazy_plt->plt_got_offset) == 0)
        plt_type = plt_non_lazy;
    }

    if (plt_type == plt_unknown || plt_type == plt_second) {
      if (non_lazy_bnd_plt != NULL &&
          plt->size >= non_lazy_bnd_plt->plt_entry_size &&
          (memcmp(plt_contents, non_lazy_bnd_plt->plt_entry,
                  non_lazy_bnd_plt->plt_got_offset) == 0)) {
        /* Match BND PLT.  */
        plt_type = plt_second;
        non_lazy_plt = non_lazy_bnd_plt;
      } else if (non_lazy_ibt_plt != NULL &&
                 plt->size >= non_lazy_ibt_plt->plt_entry_size &&
                 (memcmp(plt_contents, non_lazy_ibt_plt->plt_entry,
                         non_lazy_ibt_plt->plt_got_offset) == 0)) {
        /* Match IBT PLT.  */
        plt_type = plt_second;
        non_lazy_plt = non_lazy_ibt_plt;
      }
    }

    if (plt_type == plt_unknown)
      continue;

    plts[j].sec = plt;
    plts[j].type = plt_type;

    if ((plt_type & plt_lazy)) {
      plts[j].plt_got_offset = lazy_plt->plt_got_offset;
      plts[j].plt_got_insn_size = lazy_plt->plt_got_insn_size;
      plts[j].plt_entry_size = lazy_plt->plt_entry_size;
      /* Skip PLT0 in lazy PLT.  */
      i = 1;
    } else {
      plts[j].plt_got_offset = non_lazy_plt->plt_got_offset;
      plts[j].plt_got_insn_size = non_lazy_plt->plt_got_insn_size;
      plts[j].plt_entry_size = non_lazy_plt->plt_entry_size;
      i = 0;
    }

    /* Skip lazy PLT when the second PLT is used.  */
    if (plt_type == (plt_lazy | plt_second))
      plts[j].count = 0;
    else {
      n = plt->size / plts[j].plt_entry_size;
      plts[j].count = n;
      count += n - i;
    }

    plts[j].contents = plt_contents;
  }

  if (count == 0)
    return -1;

  size = count * sizeof(asymbol);
  s = *ret = (asymbol *)bfd_zmalloc(size);
  if (s == NULL) {
  bad_return:
    for (j = 0; plts[j].name != NULL; j++)
      if (plts[j].contents != NULL)
        free(plts[j].contents);
    free(dynrelbuf);
    return -1;
  }

  /* Check for each PLT section.  */
  size = 0;
  n = 0;
  for (j = 0; plts[j].name != NULL; j++)
    if ((plt_contents = plts[j].contents) != NULL) {
      long k;
      bfd_vma offset;

      plt_got_offset = plts[j].plt_got_offset;
      plt_got_insn_size = plts[j].plt_got_insn_size;
      plt_entry_size = plts[j].plt_entry_size;

      plt = plts[j].sec;

      if ((plts[j].type & plt_lazy)) {
        /* Skip PLT0 in lazy PLT.  */
        k = 1;
        offset = plt_entry_size;
      } else {
        k = 0;
        offset = 0;
      }

      /* Check each PLT entry against dynamic relocations.  */
      for (; k < plts[j].count; k++) {
        int off;
        bfd_vma got_vma;
        long min, max, mid;
        arelent *p;

        /* Get the PC-relative offset, a signed 32-bit integer.  */
        off = H_GET_32(abfd, (plt_contents + offset + plt_got_offset));
        got_vma = plt->vma + offset + off + plt_got_insn_size;

        /* Binary search.  */
        p = dynrelbuf[0];
        min = 0;
        max = dynrelcount;
        while ((min + 1) < max) {
          arelent *r;

          mid = (min + max) / 2;
          r = dynrelbuf[mid];
          if (got_vma > r->address)
            min = mid;
          else if (got_vma < r->address)
            max = mid;
          else {
            p = r;
            break;
          }
        }

        /* Skip unknown relocation.  PR 17512: file: bc9d6cf5.  */
        if (got_vma == p->address && p->howto != NULL &&
            (p->howto->type == R_X86_64_JUMP_SLOT ||
             p->howto->type == R_X86_64_GLOB_DAT ||
             p->howto->type == R_X86_64_IRELATIVE)) {
          *s = **p->sym_ptr_ptr;
          /* Undefined syms won't have BSF_LOCAL or BSF_GLOBAL
             set.  Since we are defining a symbol, ensure one
             of them is set.  */
          if ((s->flags & BSF_LOCAL) == 0)
            s->flags |= BSF_GLOBAL;
          s->flags |= BSF_SYNTHETIC;
          /* This is no longer a section symbol.  */
          s->flags &= ~BSF_SECTION_SYM;
          s->section = plt;
          s->the_bfd = plt->owner;
          s->value = offset;
          /* Store relocation for later use.  */
          s->udata.p = p;
          /* Add @plt to function name later.  */
          size += strlen(s->name) + sizeof("@plt");
          if (p->addend != 0)
            size += sizeof("+0x") - 1 + 8 + 8 * ABI_64_P(abfd);
          n++;
          s++;
        }
        offset += plt_entry_size;
      }
    }

  /* PLT entries with R_X86_64_TLSDESC relocations are skipped.  */
  if (n == 0)
    goto bad_return;

  count = n;

  /* Allocate space for @plt suffixes.  */
  names = (char *)bfd_malloc(size);
  if (s == NULL)
    goto bad_return;

  s = *ret;
  for (i = 0; i < count; i++) {
    /* Add @plt to function name.  */
    arelent *p = (arelent *)s->udata.p;
    /* Clear it now.  */
    s->udata.p = NULL;
    size = strlen(s->name);
    memcpy(names, s->name, size);
    s->name = names;
    names += size;
    if (p->addend != 0) {
      char buf[30], *a;

      memcpy(names, "+0x", sizeof("+0x") - 1);
      names += sizeof("+0x") - 1;
      bfd_sprintf_vma(abfd, buf, p->addend);
      for (a = buf; *a == '0'; ++a)
        ;
      size = strlen(a);
      memcpy(names, a, size);
      names += size;
    }
    memcpy(names, "@plt", sizeof("@plt"));
    names += sizeof("@plt");
    s++;
  }

  for (j = 0; plts[j].name != NULL; j++)
    if (plts[j].contents != NULL)
      free(plts[j].contents);

  free(dynrelbuf);

  return count;
}

static void dump_bfd(bfd *abfd) {
  /* If we are adjusting section VMA's, change them all now.  Changing
     the BFD information is a hack.  However, we must do it, or
     bfd_find_nearest_line will not do the right thing.  */
  if (adjust_section_vma != 0) {
    bfd_boolean has_reloc = (abfd->flags & HAS_RELOC);
    bfd_map_over_sections(abfd, adjust_addresses, &has_reloc);
  }

  if (!dump_debugging_tags && !suppress_bfd_header)
    printf(_("\n%s:     file format %s\n"), bfd_get_filename(abfd),
           abfd->xvec->name);
  if (dump_ar_hdrs)
    print_arelt_descr(stdout, abfd, TRUE);
  if (dump_file_header)
    dump_bfd_header(abfd);
  if (dump_private_headers)
    dump_bfd_private_header(abfd);
  if (dump_private_options != NULL)
    dump_target_specific(abfd);
  if (!dump_debugging_tags && !suppress_bfd_header)
    putchar('\n');

  if (dump_symtab || dump_reloc_info || disassemble || dump_debugging ||
      dump_dwarf_section_info)
    syms = slurp_symtab(abfd);

  if (dump_section_headers)
    dump_headers(abfd);

  if (dump_dynamic_symtab || dump_dynamic_reloc_info ||
      (disassemble && bfd_get_dynamic_symtab_upper_bound(abfd) > 0))
    dynsyms = slurp_dynamic_symtab(abfd);
  if (disassemble) {
    synthcount = bfd_get_synthetic_symtab(abfd, symcount, syms, dynsymcount,
                                          dynsyms, &synthsyms);
    if (synthcount < 0)
      synthcount = 0;
  }

  if (dump_symtab)
    dump_symbols(abfd, FALSE);
  if (dump_dynamic_symtab)
    dump_symbols(abfd, TRUE);
  if (dump_dwarf_section_info)
    dump_dwarf(abfd);
  if (dump_stab_section_info)
    dump_stabs(abfd);
  if (dump_reloc_info && !disassemble)
    dump_relocs(abfd);
  if (dump_dynamic_reloc_info && !disassemble)
    dump_dynamic_relocs(abfd);
  if (dump_section_contents)
    dump_data(abfd);
  if (disassemble)
    disassemble_data(abfd);

  if (dump_debugging) {
    void *dhandle;

    dhandle = read_debugging_info(abfd, syms, symcount, TRUE);
    if (dhandle != NULL) {
      if (!print_debugging_info(stdout, dhandle, abfd, syms, bfd_demangle,
                                dump_debugging_tags ? TRUE : FALSE)) {
        non_fatal(_("%s: printing debugging information failed"),
                  bfd_get_filename(abfd));
        exit_status = 1;
      }
    }
    /* PR 6483: If there was no STABS or IEEE debug
       info in the file, try DWARF instead.  */
    else if (!dump_dwarf_section_info) {
      dwarf_select_sections_all();
      dump_dwarf(abfd);
    }
  }

  if (syms) {
    free(syms);
    syms = NULL;
  }

  if (dynsyms) {
    free(dynsyms);
    dynsyms = NULL;
  }

  if (synthsyms) {
    free(synthsyms);
    synthsyms = NULL;
  }

  symcount = 0;
  dynsymcount = 0;
  synthcount = 0;
}

static void display_object_bfd(bfd *abfd) {
  char **matching;

  if (bfd_check_format_matches(abfd, bfd_object, &matching)) {
    dump_bfd(abfd);
    return;
  }

  if (bfd_get_error() == bfd_error_file_ambiguously_recognized) {
    nonfatal(bfd_get_filename(abfd));
    list_matching_formats(matching);
    free(matching);
    return;
  }

  if (bfd_get_error() != bfd_error_file_not_recognized) {
    nonfatal(bfd_get_filename(abfd));
    return;
  }

  if (bfd_check_format_matches(abfd, bfd_core, &matching)) {
    dump_bfd(abfd);
    return;
  }

  nonfatal(bfd_get_filename(abfd));

  if (bfd_get_error() == bfd_error_file_ambiguously_recognized) {
    list_matching_formats(matching);
    free(matching);
  }
}

static void display_any_bfd(bfd *file, int level) {
  /* Decompress sections unless dumping the section contents.  */
  if (!dump_section_contents)
    file->flags |= BFD_DECOMPRESS;

  /* If the file is an archive, process all of its elements.  */
  if (bfd_check_format(file, bfd_archive)) {
    bfd *arfile = NULL;
    bfd *last_arfile = NULL;

    if (level == 0)
      printf(_("In archive %s:\n"), bfd_get_filename(file));
    else if (level > 100) {
      /* Prevent corrupted files from spinning us into an
         infinite loop.  100 is an arbitrary heuristic.  */
      fatal(_("Archive nesting is too deep"));
      return;
    } else
      printf(_("In nested archive %s:\n"), bfd_get_filename(file));

    for (;;) {
      bfd_set_error(bfd_error_no_error);

      arfile = bfd_openr_next_archived_file(file, arfile);
      if (arfile == NULL) {
        if (bfd_get_error() != bfd_error_no_more_archived_files)
          nonfatal(bfd_get_filename(file));
        break;
      }

      display_any_bfd(arfile, level + 1);

      if (last_arfile != NULL) {
        bfd_close(last_arfile);
        /* PR 17512: file: ac585d01.  */
        if (arfile == last_arfile) {
          last_arfile = NULL;
          break;
        }
      }
      last_arfile = arfile;
    }

    if (last_arfile != NULL)
      bfd_close(last_arfile);
  } else
    display_object_bfd(file);
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

static void display_file(char *filename, char *target, bfd_boolean last_file) {
  bfd *file;

  if (get_file_size(filename) < 1) {
    exit_status = 1;
    return;
  }

  file = bfd_openr(filename, target);
  if (file == NULL) {
    nonfatal(filename);
    return;
  }

  display_any_bfd(file, 0);

  /* This is an optimization to improve the speed of objdump, especially when
     dumping a file with lots of associated debug informatiom.  Calling
     bfd_close on such a file can take a non-trivial amount of time as there
     are lots of lists to walk and buffers to free.  This is only really
     necessary however if we are about to load another file and we need the
     memory back.  Otherwise, if we are about to exit, then we can save (a lot
     of) time by only doing a quick close, and allowing the OS to reclaim the
     memory for us.  */
  if (!last_file)
    bfd_close(file);
  else
    bfd_close_all_done(file);
}
