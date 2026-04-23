#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SSIZE_MAX
#define SSIZE_MAX ((size_t)1 << (8 * sizeof(size_t) - 1))
#endif

#ifndef PRIu64
#define PRIu64 "lu"
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;
typedef unsigned long bfd_size_type;
typedef long file_ptr;
typedef unsigned long ufile_ptr;
typedef long bfd_hostptr_t;

typedef unsigned int flagword;
typedef unsigned char bfd_byte;

typedef void (*bfd_cleanup)(void);
extern bfd_cleanup _bfd_no_cleanup;

struct bfd;
typedef struct bfd bfd;

#define SYMNMLEN 8
#define FILNMLEN 14
#define DIMNUM 4
#define SCNNMLEN 8

struct internal_syment {
  union {
    char _n_name[SYMNMLEN];
    struct {
      bfd_hostptr_t _n_zeroes;
      bfd_hostptr_t _n_offset;
    } _n_n;
    char *_n_nptr[2];
  } _n;
  bfd_vma n_value;
  int n_scnum;
  unsigned short n_flags;
  unsigned short n_type;
  unsigned char n_sclass;
  unsigned char n_numaux;
};

#define n_name _n._n_name
#define n_zeroes _n._n_n._n_zeroes
#define n_offset _n._n_n._n_offset

typedef struct external_syment {
  union {
    char e_name[SYMNMLEN];
    struct {
      unsigned long e_zeroes;
      unsigned long e_offset;
    } e;
  } e;
  unsigned long e_value;
  short e_scnum;
  unsigned short e_type;
  unsigned char e_sclass;
  unsigned char e_numaux;
} SYMENT;

#define N_UNDEF ((int)0)
#define N_ABS ((int)-1)
#define N_DEBUG ((int)-2)
#define N_BTMASK 017
#define N_TMASK 060
#define N_BTSHFT 4

#define T_NULL 0
#define BTYPE(x) ((x) & N_BTMASK)

struct coff_ptr_struct;

union internal_auxent {
  struct {
    union {
      long l;
      struct coff_ptr_struct *p;
    } x_tagndx;
    union {
      struct {
        unsigned short x_lnno;
        unsigned short x_size;
      } x_lnsz;
      long x_fsize;
    } x_misc;
    union {
      struct {
        bfd_vma x_fcnend;
        unsigned char x_scnlen;
        unsigned char x_nreloc;
      } x_fcn;
      struct {
        unsigned short x_scnlen;
        unsigned short x_nreloc;
      } x_entry;
    } x_fcnary;
    unsigned short x_tvndx;
  } x_sym;
  union {
    char x_fname[FILNMLEN];
    struct {
      union {
        bfd_hostptr_t _n_zeroes;
        bfd_hostptr_t _n_offset;
      } _n;
      unsigned char x_zeroes;
      char x_n[FILNMLEN];
      bfd_hostptr_t x_offset;
    } x_n;
    char _x_offset[4];
  } x_file;
  struct {
    bfd_vma x_scnlen;
    unsigned short x_nreloc;
    unsigned short x_comdat;
  } x_scn;
};

typedef struct coff_ptr_struct {
  unsigned int offset;
  unsigned int fix_value : 1;
  unsigned int fix_tag : 1;
  unsigned int fix_end : 1;
  unsigned int fix_scnlen : 1;
  unsigned int fix_line : 1;
  union {
    union internal_auxent auxent;
    struct internal_syment syment;
  } u;
  bfd_boolean is_sym;
} combined_entry_type;

struct bfd_hash_entry {
  struct bfd_hash_entry *next;
  const char *string;
  unsigned long hash;
};

struct bfd_hash_table {
  struct bfd_hash_entry **table;
  struct bfd_hash_entry *(*newfunc)(struct bfd_hash_entry *,
                                    struct bfd_hash_table *, const char *);
  void *memory;
  unsigned int size;
  unsigned int count;
  unsigned int entsize;
  unsigned int frozen : 1;
};

struct objalloc;

#define CONST_STRNEQ(STR1, STR2)                                               \
  (strncmp((STR1), (STR2), sizeof(STR2) - 1) == 0)

#define H_GET_32(abfd, ptr) bfd_h_get_32(abfd, (const void *)(ptr))
#define H_GET_16(abfd, ptr) bfd_h_get_16(abfd, (const void *)(ptr))
#define H_GET_8(abfd, ptr) bfd_h_get_8(abfd, (const void *)(ptr))

extern bfd_vma bfd_h_get_32(bfd *abfd, const void *p);
extern bfd_vma bfd_h_get_16(bfd *abfd, const void *p);
extern bfd_vma bfd_h_get_8(bfd *abfd, const void *p);

enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
};

enum bfd_direction {
  no_direction = 0,
  read_direction = 1,
  write_direction = 2,
  both_direction = 3
};

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
#define BFD_DETERMINISTIC_OUTPUT 0x2000
#define BFD_COMPRESS 0x4000
#define BFD_DECOMPRESS 0x8000

#define SEC_READONLY 0x001
#define SEC_CODE 0x002
#define SEC_DATA 0x004
#define SEC_ALLOC 0x008
#define SEC_LOAD 0x010
#define SEC_RELOC 0x020
#define SEC_HAS_CONTENTS 0x040
#define SEC_DEBUGGING 0x080
#define SEC_EXCLUDE 0x100
#define SEC_LINK_ONCE 0x200
#define SEC_LINK_DUPLICATES_DISCARD 0x0000400
#define SEC_LINK_DUPLICATES_SAME_SIZE 0x0000800
#define SEC_LINK_DUPLICATES_SAME_CONTENTS 0x0001000
#define SEC_LINK_DUPLICATES_ONE_ONLY 0x0002000
#define SEC_SMALL_DATA 0x0004000
#define SEC_COFF_NOREAD 0x40000000
#define SEC_COFF_SHARED 0x01000000
#define SEC_COFF_SHARED_LIBRARY 0x02000000
#define SEC_IS_COMMON 0x0008000
#define SEC_NEVER_LOAD 0x0000100

#define COMPRESS_SECTION_NONE 0
#define COMPRESS_SECTION_DONE 1
#define DECOMPRESS_SECTION_SIZED 2

struct bfd_section;
typedef struct bfd_section asection;
typedef struct bfd_section *sec_ptr;

struct bfd_section {
  const char *name;
  int id;
  unsigned int index;
  struct bfd_section *next;
  struct bfd_section *prev;
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
  file_ptr filepos;
  file_ptr rel_filepos;
  file_ptr line_filepos;
  void *userdata;
  unsigned char *contents;
  void *lineno;
  unsigned int lineno_count;
  unsigned int entsize;
  struct bfd_section *kept_section;
  file_ptr moving_line_filepos;
  int target_index;
  void *used_by_bfd;
  void *constructor_chain;
  bfd *owner;
  void *symbol;
  void **symbol_ptr_ptr;
  union {
    void *link_order;
    struct bfd_section *s;
    const char *linked_to_symbol_name;
  } map_head, map_tail;
  struct bfd_section *already_assigned;
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
  flagword flags;
};

struct section_hash_entry {
  struct bfd_hash_entry root;
  asection section;
};

struct bfd_target;
struct bfd_iovec;
struct bfd_arch_info;
struct bfd_symbol;
struct bfd_link_hash_table;
struct bfd_link_order;
struct reloc_cache_entry;
struct lineno_cache_entry;
struct relent_chain;
struct relax_table;
struct coff_link_hash_entry;
struct internal_reloc;
struct reloc_howto_struct;
struct coff_symbol_struct;
struct bfd_link_info;

struct internal_extra_pe_aouthdr {
  unsigned long ImageBase;
  unsigned long SizeOfStackReserve;
  unsigned long SizeOfStackCommit;
  unsigned long SizeOfHeapReserve;
  unsigned long SizeOfHeapCommit;
  unsigned long LoaderFlags;
  unsigned long NumberOfRvaAndSizes;
};

struct bfd_build_id {
  bfd_size_type size;
  bfd_byte data[1];
};

enum bfd_plugin_format {
  bfd_plugin_unknown = 0,
  bfd_plugin_yes = 1,
  bfd_plugin_no = 2
};

struct coff_comdat_info {
  const char *name;
  long symbol;
};

struct coff_section_tdata {
  struct internal_reloc *relocs;
  bfd_boolean keep_relocs;
  bfd_byte *contents;
  bfd_boolean keep_contents;
  bfd_boolean saved_bias;
  bfd_signed_vma bias;
  bfd_vma offset;
  unsigned int i;
  const char *function;
  struct coff_comdat_info *comdat;
  int line_base;
  void *stab_info;
  void *tdata;
};

#define coff_section_data(abfd, sec)                                           \
  ((struct coff_section_tdata *)(sec)->used_by_bfd)

struct internal_scnhdr {
  char s_name[SCNNMLEN];
  bfd_vma s_vaddr;
  bfd_vma s_paddr;
  bfd_size_type s_size;
  bfd_vma s_scnptr;
  bfd_vma s_relptr;
  bfd_vma s_lnnoptr;
  unsigned short s_nreloc;
  unsigned short s_nlnno;
  unsigned long s_flags;
};

typedef struct coff_tdata {
  struct coff_symbol_struct *symbols;
  unsigned int *conversion_table;
  int conv_table_size;
  file_ptr sym_filepos;
  struct coff_ptr_struct *raw_syments;
  unsigned long raw_syment_count;
  unsigned long int relocbase;
  unsigned local_n_btmask;
  unsigned local_n_btshft;
  unsigned local_n_tmask;
  unsigned local_n_tshift;
  unsigned local_symesz;
  unsigned local_auxesz;
  unsigned local_linesz;
  void *external_syms;
  bfd_boolean keep_syms;
  char *strings;
  bfd_size_type strings_len;
  bfd_boolean keep_strings;
  bfd_boolean strings_written;
  int pe;
  struct coff_link_hash_entry **sym_hashes;
  int *local_toc_sym_map;
  struct bfd_link_info *link_info;
  void *line_info;
  void *dwarf2_find_line_info;
  long timestamp;
  flagword flags;
  bfd_boolean go32;
  char *stub;
  bfd_size_type stub_size;
} coff_data_type;

typedef struct pe_tdata {
  coff_data_type coff;
  struct internal_extra_pe_aouthdr pe_opthdr;
  int dll;
  int has_reloc_section;
  int dont_strip_reloc;
  int dos_message[16];
  int timestamp;
  bfd_boolean (*in_reloc_p)(bfd *, struct reloc_howto_struct *);
  flagword real_flags;
  struct {
    bfd_boolean (*after_write_object_contents)(bfd *);
    const char *style;
    asection *sec;
  } build_id;
} pe_data_type;

#define coff_data(bfd) ((bfd)->tdata.coff_obj_data)
#define obj_coff_external_syms(bfd) (coff_data(bfd)->external_syms)
#define obj_coff_keep_syms(bfd) (coff_data(bfd)->keep_syms)
#define obj_coff_strings(bfd) (coff_data(bfd)->strings)
#define obj_coff_strings_len(bfd) (coff_data(bfd)->strings_len)
#define obj_coff_keep_strings(bfd) (coff_data(bfd)->keep_strings)
#define obj_sym_filepos(bfd) (coff_data(bfd)->sym_filepos)
#define obj_raw_syments(bfd) (coff_data(bfd)->raw_syments)
#define obj_raw_syment_count(bfd) (coff_data(bfd)->raw_syment_count)

union bfd_tdata {
  void *any;
  struct coff_tdata *coff_obj_data;
  struct pe_tdata *pe_obj_data;
};

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
  enum bfd_format format : 3;
  enum bfd_direction direction : 2;
  unsigned int cacheable : 1;
  unsigned int target_defaulted : 1;
  unsigned int opened_once : 1;
  unsigned int mtime_set : 1;
  unsigned int no_export : 1;
  unsigned int output_has_begun : 1;
  unsigned int has_armap : 1;
  unsigned int is_thin_archive : 1;
  unsigned int no_element_cache : 1;
  unsigned int selective_search : 1;
  unsigned int is_linker_output : 1;
  unsigned int is_linker_input : 1;
  enum bfd_plugin_format plugin_format : 2;
  unsigned int lto_output : 1;
  unsigned int lto_slim_object : 1;
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
  union bfd_tdata tdata;
  struct bfd_build_id *build_id;
};

#define bfd_family_coff(abfd)                                                  \
  ((abfd) != NULL && (abfd)->xvec != NULL && (abfd)->xvec->flavour == 2)

struct bfd_target {
  int flavour;
};

#define F_RELFLG (0000001)
#define F_EXEC (0000002)
#define F_LNNO (0000004)
#define F_LSYMS (0000010)

#define STYP_DSECT (01)
#define STYP_GROUP (0100000)
#define STYP_COPY (02000000)
#define STYP_OVER (040000000)
#define STYP_NOLOAD (0100000000)

#define IMAGE_SCN_MEM_WRITE (0x80000000)
#define IMAGE_SCN_MEM_READ (0x40000000)
#define IMAGE_SCN_MEM_EXECUTE (0x20000000)
#define IMAGE_SCN_MEM_SHARED (0x10000000)
#define IMAGE_SCN_MEM_DISCARDABLE (0x02000000)
#define IMAGE_SCN_TYPE_NO_PAD (0x00000010)
#define IMAGE_SCN_LNK_OTHER (0x00000100)
#define IMAGE_SCN_MEM_NOT_CACHED (0x04000000)
#define IMAGE_SCN_MEM_NOT_PAGED (0x08000000)
#define IMAGE_SCN_LNK_REMOVE (0x00000800)
#define IMAGE_SCN_LNK_INFO (0x00000200)
#define IMAGE_SCN_LNK_COMDAT (0x00001000)
#define IMAGE_SCN_CNT_CODE (0x00000020)
#define IMAGE_SCN_CNT_INITIALIZED_DATA (0x00000040)
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA (0x00000080)

#define IMAGE_COMDAT_SELECT_NODUPLICATES 1
#define IMAGE_COMDAT_SELECT_ANY 2
#define IMAGE_COMDAT_SELECT_SAME_SIZE 3
#define IMAGE_COMDAT_SELECT_EXACT_MATCH 4
#define IMAGE_COMDAT_SELECT_ASSOCIATIVE 5

#define C_EXT 2
#define C_STAT 3
#define C_FILE 107
#define C_SECTION 104

#define IMAGE_DOS_SIGNATURE 0x5A4D

#define STRING_SIZE_SIZE 4

#define DOT_DEBUG ".debug"
#define DOT_ZDEBUG ".zdebug"
#define GNU_LINKONCE_WI ".gnu.linkonce.wi"
#define GNU_LINKONCE_WT ".gnu.linkonce.wt"

void bfd_assert(const char *, int);
#define BFD_ASSERT(x)                                                          \
  do {                                                                         \
    if (!(x))                                                                  \
      bfd_assert(__FILE__, __LINE__);                                          \
  } while (0)

void _bfd_abort(const char *, int, const char *);
#undef abort
#define abort() _bfd_abort(__FILE__, __LINE__, __PRETTY_FUNCTION__)

typedef enum bfd_error_enum {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_target,
  bfd_error_wrong_format,
  bfd_error_wrong_object_format,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_symtab_error,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_ambiguously_new,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_plugin_file,
  bfd_error_file_not_recognized,
  bfd_error_file_too_big,
  bfd_error_on_input,
  bfd_error_invalid_error_code
} bfd_error_type;

extern bfd_error_type bfd_error;

extern void bfd_set_error(bfd_error_type error_tag);
extern bfd_error_type bfd_get_error(void);

extern void (*_bfd_error_handler)(const char *, ...);
#define _(String) String

typedef struct external_DOS_hdr {
  unsigned char e_magic[2];
  unsigned char e_cblp[2];
  unsigned char e_cp[2];
  unsigned char e_crlc[2];
  unsigned char e_cparhdr[2];
  unsigned char e_minalloc[2];
  unsigned char e_maxalloc[2];
  unsigned char e_ss[2];
  unsigned char e_sp[2];
  unsigned char e_csum[2];
  unsigned char e_ip[2];
  unsigned char e_cs[2];
  unsigned char e_lfarlc[2];
  unsigned char e_ovno[2];
  unsigned char e_res[8];
  unsigned char e_oemid[2];
  unsigned char e_oeminfo[2];
  unsigned char e_res2[20];
  unsigned char e_lfanew[4];
  int dos_message[16];
} external_DOS_hdr;

typedef struct external_PEI_IMAGE_hdr {
  unsigned char nt_signature[4];
  unsigned char f_magic[2];
  unsigned char f_nscns[2];
  unsigned char f_timdat[4];
  unsigned char f_symptr[4];
  unsigned char f_nsyms[4];
  unsigned char f_opthdr[2];
  unsigned char f_flags[2];
} external_PEI_IMAGE_hdr;

struct internal_filehdr {
  unsigned short f_magic;
  unsigned short f_nscns;
  unsigned long f_timdat;
  file_ptr f_symptr;
  long f_nsyms;
  unsigned short f_opthdr;
  unsigned short f_flags;
  struct {
    int dos_message[16];
    unsigned long pe_opthdr;
  } pe;
};

struct internal_aouthdr {
  unsigned short magic;
  unsigned short vstamp;
  unsigned long tsize;
  unsigned long dsize;
  unsigned long bsize;
  unsigned long entry;
  unsigned long text_start;
  unsigned long data_start;
};

typedef struct {
  unsigned short Magic;
  unsigned short MajorLinkerVersion;
  unsigned short MinorLinkerVersion;
  unsigned long SizeOfCode;
  unsigned long SizeOfInitializedData;
  unsigned long SizeOfUninitializedData;
  unsigned long AddressOfEntryPoint;
  unsigned long BaseOfCode;
  unsigned long BaseOfData;
  unsigned long ImageBase;
  unsigned long SectionAlignment;
  unsigned long FileAlignment;
  unsigned short MajorOperatingSystemVersion;
  unsigned short MinorOperatingSystemVersion;
  unsigned short MajorImageVersion;
  unsigned short MinorImageVersion;
  unsigned short MajorSubsystemVersion;
  unsigned short MinorSubsystemVersion;
  unsigned long Win32VersionValue;
  unsigned long SizeOfImage;
  unsigned long SizeOfHeaders;
  unsigned long CheckSum;
  unsigned short Subsystem;
  unsigned short DllCharacteristics;
  unsigned long SizeOfStackReserve;
  unsigned long SizeOfStackCommit;
  unsigned long SizeOfHeapReserve;
  unsigned long SizeOfHeapCommit;
  unsigned long LoaderFlags;
  unsigned long NumberOfRvaAndSizes;
} PEAOUTHDR;

extern void *bfd_malloc(bfd_size_type size);
extern void *bfd_alloc(bfd *abfd, bfd_size_type wanted);
extern void *bfd_zalloc(bfd *abfd, bfd_size_type wanted);
extern void bfd_release(bfd *abfd, void *all);
extern void *_bfd_alloc_and_read(bfd *abfd, bfd_size_type asize,
                                 bfd_size_type rsize);

extern file_ptr bfd_seek(bfd *abfd, file_ptr offset, int direction);
extern file_ptr bfd_bread(void *ptr, bfd_size_type size, bfd *abfd);
extern ufile_ptr bfd_get_file_size(bfd *abfd);

extern bfd_boolean _bfd_coff_free_symbols(bfd *abfd);
extern const char *_bfd_coff_read_string_table(bfd *abfd);
extern bfd_boolean _bfd_coff_get_external_symbols(bfd *abfd);
extern const char *
_bfd_coff_internal_syment_name(bfd *, const struct internal_syment *, char *);

extern void bfd_coff_swap_sym_in(bfd *, void *, void *);
extern void bfd_coff_swap_aux_in(bfd *, void *, int, int, int, int, void *);
extern void bfd_coff_swap_scnhdr_in(bfd *, void *, void *);
extern void bfd_coff_swap_filehdr_in(bfd *, void *, void *);
extern void bfd_coff_swap_aouthdr_in(bfd *, void *, void *);

extern bfd_boolean bfd_coff_styp_to_sec_flags_hook(bfd *, void *, const char *,
                                                   asection *, flagword *);
extern void bfd_coff_set_alignment_hook(bfd *, asection *, void *);
extern bfd_boolean bfd_coff_set_long_section_names(bfd *, bfd_boolean);
extern bfd_boolean bfd_coff_long_section_names(bfd *);
extern void *bfd_coff_mkobject_hook(bfd *, void *, void *);
extern bfd_boolean bfd_coff_set_arch_mach_hook(bfd *, void *);
extern unsigned int bfd_coff_scnhsz(bfd *);
extern unsigned int bfd_coff_symesz(bfd *);
extern unsigned int bfd_coff_aoutsz(bfd *);
extern unsigned int bfd_coff_filnmlen(bfd *);
extern bfd_boolean bfd_coff_symname_in_debug(bfd *, struct internal_syment *);
extern bfd_boolean bfd_coff_bad_format_hook(bfd *, void *);

extern asection *bfd_make_section_anyway(bfd *, const char *);
extern asection *bfd_make_section_anyway_with_flags(bfd *, const char *,
                                                    flagword);
extern asection *bfd_get_section_by_name(bfd *, const char *);
extern flagword bfd_applicable_section_flags(bfd *abfd);

extern bfd_boolean bfd_is_section_compressed(bfd *, const asection *);
extern bfd_boolean bfd_init_section_compress_status(bfd *, asection *);
extern bfd_boolean bfd_init_section_decompress_status(bfd *, asection *);
extern void bfd_rename_section(asection *, const char *);

extern bfd_vma bfd_get_start_address(bfd *);

extern unsigned int _bfd_section_id;
extern void bfd_section_list_append(bfd *abfd, asection *s);

static asection *bfd_section_init(bfd *abfd, asection *newsect) {
  newsect->id = _bfd_section_id;
  newsect->index = abfd->section_count;
  newsect->owner = abfd;
  _bfd_section_id++;
  abfd->section_count++;
  bfd_section_list_append(abfd, newsect);
  return newsect;
}

extern struct bfd_hash_entry *bfd_hash_insert(struct bfd_hash_table *,
                                              const char *, unsigned long);
extern struct bfd_hash_entry *bfd_hash_lookup(struct bfd_hash_table *,
                                              const char *, bfd_boolean create,
                                              bfd_boolean copy);
extern unsigned long bfd_hash_hash(const char *, unsigned int *len);
extern unsigned long higher_prime_number(unsigned long);
extern void *objalloc_alloc(struct objalloc *, unsigned long);
extern struct bfd_hash_entry *bfd_section_hash_newfunc(struct bfd_hash_entry *,
                                                       struct bfd_hash_table *,
                                                       const char *);

extern bfd_cleanup _bfd_no_cleanup;
extern bfd_cleanup pe_ILF_object_p(bfd *);
extern void pe_bfd_read_buildid(bfd *);
extern char *build_debug_section(bfd *, asection **);
extern char *copy_name(bfd *, const char *, size_t);
extern void coff_pointerize_aux(bfd *, combined_entry_type *,
                                combined_entry_type *, unsigned int,
                                combined_entry_type *, combined_entry_type *);

#define obj_coff_strings(bfd) (coff_data(bfd)->strings)

bfd_boolean _bfd_coff_free_symbols(bfd *abfd) {
  if (!bfd_family_coff(abfd))
    return FALSE;

  if (obj_coff_external_syms(abfd) != NULL && !obj_coff_keep_syms(abfd)) {
    free(obj_coff_external_syms(abfd));
    obj_coff_external_syms(abfd) = NULL;
  }

  if (obj_coff_strings(abfd) != NULL && !obj_coff_keep_strings(abfd)) {
    free(obj_coff_strings(abfd));
    obj_coff_strings(abfd) = NULL;
    obj_coff_strings_len(abfd) = 0;
  }

  return TRUE;
}


void *bfd_malloc(bfd_size_type size) {
  void *ptr;
  size_t sz = (size_t)size;

  if (size != sz
      /* This is to pacify memory checkers like valgrind.  */
      || sz > SSIZE_MAX) {
    bfd_set_error(bfd_error_no_memory);
    return NULL;
  }

  ptr = malloc(sz);
  if (ptr == NULL && sz != 0)
    bfd_set_error(bfd_error_no_memory);

  return ptr;
}

const char *_bfd_coff_read_string_table(bfd *abfd) {
  char extstrsize[STRING_SIZE_SIZE];
  bfd_size_type strsize;
  char *strings;
  file_ptr pos;
  ufile_ptr filesize;

  if (obj_coff_strings(abfd) != NULL)
    return obj_coff_strings(abfd);

  if (obj_sym_filepos(abfd) == 0) {
    bfd_set_error(bfd_error_no_symbols);
    return NULL;
  }

  pos = obj_sym_filepos(abfd);
  pos += obj_raw_syment_count(abfd) * bfd_coff_symesz(abfd);
  if (bfd_seek(abfd, pos, SEEK_SET) != 0)
    return NULL;

  if (bfd_bread(extstrsize, (bfd_size_type)sizeof extstrsize, abfd) !=
      sizeof extstrsize) {
    if (bfd_get_error() != bfd_error_file_truncated)
      return NULL;

    /* There is no string table.  */
    strsize = STRING_SIZE_SIZE;
  } else {
#if STRING_SIZE_SIZE == 4
    strsize = H_GET_32(abfd, extstrsize);
#else
#error Change H_GET_32
#endif
  }

  filesize = bfd_get_file_size(abfd);
  if (strsize < STRING_SIZE_SIZE || (filesize != 0 && strsize > filesize)) {
    _bfd_error_handler
        /* xgettext: c-format */
        (_("%pB: bad string table size %" PRIu64), abfd, (uint64_t)strsize);
    bfd_set_error(bfd_error_bad_value);
    return NULL;
  }

  strings = (char *)bfd_malloc(strsize + 1);
  if (strings == NULL)
    return NULL;

  /* PR 17521 file: 079-54929-0.004.
     A corrupt file could contain an index that points into the first
     STRING_SIZE_SIZE bytes of the string table, so make sure that
     they are zero.  */
  memset(strings, 0, STRING_SIZE_SIZE);

  if (bfd_bread(strings + STRING_SIZE_SIZE, strsize - STRING_SIZE_SIZE, abfd) !=
      strsize - STRING_SIZE_SIZE) {
    free(strings);
    return NULL;
  }

  
  obj_coff_strings(abfd) = strings;
  obj_coff_strings_len(abfd) = strsize;
  /* Terminate the string table, just in case.  */
  strings[strsize] = 0;
  return strings;
}

const char *_bfd_coff_internal_syment_name(bfd *abfd,
                                           const struct internal_syment *sym,
                                           char *buf) {
  /* FIXME: It's not clear this will work correctly if sizeof
     (_n_zeroes) != 4.  */
  if (sym->_n._n_n._n_zeroes != 0 || sym->_n._n_n._n_offset == 0) {
    memcpy(buf, sym->_n._n_name, SYMNMLEN);
    buf[SYMNMLEN] = '\0';
    return buf;
  } else {
    const char *strings;

    BFD_ASSERT(sym->_n._n_n._n_offset >= STRING_SIZE_SIZE);
    strings = obj_coff_strings(abfd);
    if (strings == NULL) {
      strings = _bfd_coff_read_string_table(abfd);
      if (strings == NULL)
        return NULL;
    }
    /* PR 17910: Only check for string overflow if the length has been set.
       Some DLLs, eg those produced by Visual Studio, may not set the length
       field.  */
    if (obj_coff_strings_len(abfd) > 0 &&
        sym->_n._n_n._n_offset >= obj_coff_strings_len(abfd))
      return NULL;
    return strings + sym->_n._n_n._n_offset;
  }
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

#define section_hash_lookup(table, string, create, copy)                       \
  ((struct section_hash_entry *)bfd_hash_lookup((table), (string), (create),   \
                                                (copy)))

asection *bfd_get_section_by_name(bfd *abfd, const char *name) {
  struct section_hash_entry *sh;

  sh = section_hash_lookup(&abfd->section_htab, name, FALSE, FALSE);
  if (sh != NULL)
    return &sh->section;

  return NULL;
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

void _bfd_XXi_swap_sym_in(bfd *abfd, void *ext1, void *in1) {
  SYMENT *ext = (SYMENT *)ext1;
  struct internal_syment *in = (struct internal_syment *)in1;

  if (ext->e.e_name[0] == 0) {
    in->_n._n_n._n_zeroes = 0;
    in->_n._n_n._n_offset = H_GET_32(abfd, ext->e.e.e_offset);
  } else
    memcpy(in->_n._n_name, ext->e.e_name, SYMNMLEN);

  in->n_value = H_GET_32(abfd, ext->e_value);
  in->n_scnum = (short)H_GET_16(abfd, ext->e_scnum);

  if (sizeof(ext->e_type) == 2)
    in->n_type = H_GET_16(abfd, ext->e_type);
  else
    in->n_type = H_GET_32(abfd, ext->e_type);

  in->n_sclass = H_GET_8(abfd, ext->e_sclass);
  in->n_numaux = H_GET_8(abfd, ext->e_numaux);

#ifndef STRICT_PE_FORMAT
  /* This is for Gnu-created DLLs.  */

  /* The section symbols for the .idata$ sections have class 0x68
     (C_SECTION), which MS documentation indicates is a section
     symbol.  Unfortunately, the value field in the symbol is simply a
     copy of the .idata section's flags rather than something useful.
     When these symbols are encountered, change the value to 0 so that
     they will be handled somewhat correctly in the bfd code.  */
  if (in->n_sclass == C_SECTION) {
    char namebuf[SYMNMLEN + 1];
    const char *name = NULL;

    in->n_value = 0x0;

    /* Create synthetic empty sections as needed.  DJ */
    if (in->n_scnum == 0) {
      asection *sec;

      name = _bfd_coff_internal_syment_name(abfd, in, namebuf);
      if (name == NULL) {
        _bfd_error_handler(_("%pB: unable to find name for empty section"),
                           abfd);
        bfd_set_error(bfd_error_invalid_target);
        return;
      }

      
      sec = bfd_get_section_by_name(abfd, name);
      if (sec != NULL)
        in->n_scnum = sec->target_index;
    }

    if (in->n_scnum == 0) {
      int unused_section_number = 0;
      asection *sec;
      flagword flags;

      for (sec = abfd->sections; sec; sec = sec->next)
        if (unused_section_number <= sec->target_index)
          unused_section_number = sec->target_index + 1;

      if (name == namebuf) {
        name = (const char *)bfd_alloc(abfd, strlen(namebuf) + 1);
        if (name == NULL) {
          _bfd_error_handler(
              _("%pB: out of memory creating name for empty section"), abfd);
          return;
        }
        strcpy((char *)name, namebuf);
      }

      flags = SEC_HAS_CONTENTS | SEC_ALLOC | SEC_DATA | SEC_LOAD;
      sec = bfd_make_section_anyway_with_flags(abfd, name, flags);
      if (sec == NULL) {
        _bfd_error_handler(_("%pB: unable to create fake empty section"), abfd);
        return;
      }

      sec->vma = 0;
      sec->lma = 0;
      sec->size = 0;
      sec->filepos = 0;
      sec->rel_filepos = 0;
      sec->reloc_count = 0;
      sec->line_filepos = 0;
      sec->lineno_count = 0;
      sec->userdata = NULL;
      sec->next = NULL;
      sec->alignment_power = 2;

      sec->target_index = unused_section_number;

      in->n_scnum = unused_section_number;
    }
    in->n_sclass = C_STAT;
  }
#endif

#ifdef coff_swap_sym_in_hook
  /* This won't work in peigen.c, but since it's for PPC PE, it's not
     worth fixing.  */
  coff_swap_sym_in_hook(abfd, ext1, in1);
#endif
}

static flagword handle_COMDAT(bfd *abfd, flagword sec_flags, void *hdr,
                              const char *name, asection *section) {
  struct internal_scnhdr *internal_s = (struct internal_scnhdr *)hdr;
  bfd_byte *esymstart, *esym, *esymend;
  int seen_state = 0;
  char *target_name = NULL;

  sec_flags |= SEC_LINK_ONCE;

  /* Unfortunately, the PE format stores essential information in
     the symbol table, of all places.  We need to extract that
     information now, so that objdump and the linker will know how
     to handle the section without worrying about the symbols.  We
     can't call slurp_symtab, because the linker doesn't want the
     swapped symbols.  */

  /* COMDAT sections are special.  The first symbol is the section
     symbol, which tells what kind of COMDAT section it is.  The
     second symbol is the "comdat symbol" - the one with the
     unique name.  GNU uses the section symbol for the unique
     name; MS uses ".text" for every comdat section.  Sigh.  - DJ */

  /* This is not mirrored in sec_to_styp_flags(), but there
     doesn't seem to be a need to, either, and it would at best be
     rather messy.  */

  if (!_bfd_coff_get_external_symbols(abfd))
    return sec_flags;

  esymstart = esym = (bfd_byte *)obj_coff_external_syms(abfd);
  esymend = esym + obj_raw_syment_count(abfd) * bfd_coff_symesz(abfd);

  while (esym < esymend) {
    struct internal_syment isym;
    char buf[SYMNMLEN + 1];
    const char *symname;

    bfd_coff_swap_sym_in(abfd, esym, &isym);

    BFD_ASSERT(sizeof(internal_s->s_name) <= SYMNMLEN);

    if (isym.n_scnum == section->target_index) {
      /* According to the MSVC documentation, the first
         TWO entries with the section # are both of
         interest to us.  The first one is the "section
         symbol" (section name).  The second is the comdat
         symbol name.  Here, we've found the first
         qualifying entry; we distinguish it from the
         second with a state flag.

         In the case of gas-generated (at least until that
         is fixed) .o files, it isn't necessarily the
         second one.  It may be some other later symbol.

         Since gas also doesn't follow MS conventions and
         emits the section similar to .text$<name>, where
         <something> is the name we're looking for, we
         distinguish the two as follows:

         If the section name is simply a section name (no
         $) we presume it's MS-generated, and look at
         precisely the second symbol for the comdat name.
         If the section name has a $, we assume it's
         gas-generated, and look for <something> (whatever
         follows the $) as the comdat symbol.  */

      /* All 3 branches use this.  */
      symname = _bfd_coff_internal_syment_name(abfd, &isym, buf);

      /* PR 17512 file: 078-11867-0.004  */
      if (symname == NULL) {
        _bfd_error_handler(_("%pB: unable to load COMDAT section name"), abfd);
        break;
      }

      switch (seen_state) {
      case 0: {
        /* The first time we've seen the symbol.  */
        union internal_auxent aux;

        /* If it isn't the stuff we're expecting, die;
           The MS documentation is vague, but it
           appears that the second entry serves BOTH
           as the comdat symbol and the defining
           symbol record (either C_STAT or C_EXT,
           possibly with an aux entry with debug
           information if it's a function.)  It
           appears the only way to find the second one
           is to count.  (On Intel, they appear to be
           adjacent, but on Alpha, they have been
           found separated.)

           Here, we think we've found the first one,
           but there's some checking we can do to be
           sure.  */

        if (!((isym.n_sclass == C_STAT || isym.n_sclass == C_EXT) &&
              BTYPE(isym.n_type) == T_NULL && isym.n_value == 0)) {
          /* Malformed input files can trigger this test.
             cf PR 21781.  */
          _bfd_error_handler(
              _("%pB: error: unexpected symbol '%s' in COMDAT section"), abfd,
              symname);
          goto breakloop;
        }

        /* FIXME LATER: MSVC generates section names
           like .text for comdats.  Gas generates
           names like .text$foo__Fv (in the case of a
           function).  See comment above for more.  */

        if (isym.n_sclass == C_STAT && strcmp(name, symname) != 0)
          /* xgettext:c-format */
          _bfd_error_handler(_("%pB: warning: COMDAT symbol '%s'"
                               " does not match section name '%s'"),
                             abfd, symname, name);

        seen_state = 1;

        /* PR 17512: file: e2cfe54f.  */
        if (esym + bfd_coff_symesz(abfd) >= esymend) {
          /* xgettext:c-format */
          _bfd_error_handler(_("%pB: warning: no symbol for"
                               " section '%s' found"),
                             abfd, symname);
          break;
        }
        /* This is the section symbol.  */
        bfd_coff_swap_aux_in(abfd, (esym + bfd_coff_symesz(abfd)), isym.n_type,
                             isym.n_sclass, 0, isym.n_numaux, &aux);

        target_name = strchr(name, '$');
        if (target_name != NULL) {
          /* Gas mode.  */
          seen_state = 2;
          /* Skip the `$'.  */
          target_name += 1;
        }

        /* FIXME: Microsoft uses NODUPLICATES and
           ASSOCIATIVE, but gnu uses ANY and
           SAME_SIZE.  Unfortunately, gnu doesn't do
           the comdat symbols right.  So, until we can
           fix it to do the right thing, we are
           temporarily disabling comdats for the MS
           types (they're used in DLLs and C++, but we
           don't support *their* C++ libraries anyway
           - DJ.  */

        /* Cygwin does not follow the MS style, and
           uses ANY and SAME_SIZE where NODUPLICATES
           and ASSOCIATIVE should be used.  For
           Interix, we just do the right thing up
           front.  */

        switch (aux.x_scn.x_comdat) {
        case IMAGE_COMDAT_SELECT_NODUPLICATES:
#ifdef STRICT_PE_FORMAT
          sec_flags |= SEC_LINK_DUPLICATES_ONE_ONLY;
#else
          sec_flags &= ~SEC_LINK_ONCE;
#endif
          break;

        case IMAGE_COMDAT_SELECT_ANY:
          sec_flags |= SEC_LINK_DUPLICATES_DISCARD;
          break;

        case IMAGE_COMDAT_SELECT_SAME_SIZE:
          sec_flags |= SEC_LINK_DUPLICATES_SAME_SIZE;
          break;

        case IMAGE_COMDAT_SELECT_EXACT_MATCH:
          /* Not yet fully implemented ??? */
          sec_flags |= SEC_LINK_DUPLICATES_SAME_CONTENTS;
          break;

          /* debug$S gets this case; other
             implications ??? */

          /* There may be no symbol... we'll search
             the whole table... Is this the right
             place to play this game? Or should we do
             it when reading it in.  */
        case IMAGE_COMDAT_SELECT_ASSOCIATIVE:
#ifdef STRICT_PE_FORMAT
          /* FIXME: This is not currently implemented.  */
          sec_flags |= SEC_LINK_DUPLICATES_DISCARD;
#else
          sec_flags &= ~SEC_LINK_ONCE;
#endif
          break;

        default: /* 0 means "no symbol" */
          /* debug$F gets this case; other
             implications ??? */
          sec_flags |= SEC_LINK_DUPLICATES_DISCARD;
          break;
        }
      } break;

      case 2:
        /* Gas mode: the first matching on partial name.  */

#ifndef TARGET_UNDERSCORE
#define TARGET_UNDERSCORE 0
#endif
        /* Is this the name we're looking for ?  */
        if (strcmp(target_name, symname + (TARGET_UNDERSCORE ? 1 : 0)) != 0) {
          /* Not the name we're looking for */
          esym += (isym.n_numaux + 1) * bfd_coff_symesz(abfd);
          continue;
        }
        /* Fall through.  */
      case 1:
        /* MSVC mode: the lexically second symbol (or
           drop through from the above).  */
        {
          char *newname;
          size_t amt;

          /* This must the second symbol with the
             section #.  It is the actual symbol name.
             Intel puts the two adjacent, but Alpha (at
             least) spreads them out.  */

          amt = sizeof(struct coff_comdat_info);
          coff_section_data(abfd, section)->comdat =
              (struct coff_comdat_info *)bfd_alloc(abfd, amt);
          if (coff_section_data(abfd, section)->comdat == NULL)
            abort();

          coff_section_data(abfd, section)->comdat->symbol =
              (esym - esymstart) / bfd_coff_symesz(abfd);

          amt = strlen(symname) + 1;
          newname = (char *)bfd_alloc(abfd, amt);
          if (newname == NULL)
            abort();

          strcpy(newname, symname);
          coff_section_data(abfd, section)->comdat->name = newname;
        }

        goto breakloop;
      }
    }

    esym += (isym.n_numaux + 1) * bfd_coff_symesz(abfd);
  }

breakloop:
  return sec_flags;
}

static bfd_boolean styp_to_sec_flags(bfd *abfd, void *hdr, const char *name,
                                     asection *section, flagword *flags_ptr) {
  struct internal_scnhdr *internal_s = (struct internal_scnhdr *)hdr;
  unsigned long styp_flags = internal_s->s_flags;
  flagword sec_flags;
  bfd_boolean result = TRUE;
  bfd_boolean is_dbg = FALSE;

  if (CONST_STRNEQ(name, DOT_DEBUG) || CONST_STRNEQ(name, DOT_ZDEBUG)
#ifdef COFF_LONG_SECTION_NAMES
      || CONST_STRNEQ(name, GNU_LINKONCE_WI) ||
      CONST_STRNEQ(name, GNU_LINKONCE_WT)
  /* FIXME: These definitions ought to be in a header file.  */
#define GNU_DEBUGLINK ".gnu_debuglink"
#define GNU_DEBUGALTLINK ".gnu_debugaltlink"
      || CONST_STRNEQ(name, GNU_DEBUGLINK) ||
      CONST_STRNEQ(name, GNU_DEBUGALTLINK)
#endif
      || CONST_STRNEQ(name, ".stab"))
    is_dbg = TRUE;
  /* Assume read only unless IMAGE_SCN_MEM_WRITE is specified.  */
  sec_flags = SEC_READONLY;

  /* If section disallows read, then set the NOREAD flag. */
  if ((styp_flags & IMAGE_SCN_MEM_READ) == 0)
    sec_flags |= SEC_COFF_NOREAD;

  /* Process each flag bit in styp_flags in turn.  */
  while (styp_flags) {
    unsigned long flag = styp_flags & -styp_flags;
    char *unhandled = NULL;

    styp_flags &= ~flag;

    /* We infer from the distinct read/write/execute bits the settings
       of some of the bfd flags; the actual values, should we need them,
       are also in pei_section_data (abfd, section)->pe_flags.  */

    switch (flag) {
    case STYP_DSECT:
      unhandled = "STYP_DSECT";
      break;
    case STYP_GROUP:
      unhandled = "STYP_GROUP";
      break;
    case STYP_COPY:
      unhandled = "STYP_COPY";
      break;
    case STYP_OVER:
      unhandled = "STYP_OVER";
      break;
#ifdef SEC_NEVER_LOAD
    case STYP_NOLOAD:
      sec_flags |= SEC_NEVER_LOAD;
      break;
#endif
    case IMAGE_SCN_MEM_READ:
      sec_flags &= ~SEC_COFF_NOREAD;
      break;
    case IMAGE_SCN_TYPE_NO_PAD:
      /* Skip.  */
      break;
    case IMAGE_SCN_LNK_OTHER:
      unhandled = "IMAGE_SCN_LNK_OTHER";
      break;
    case IMAGE_SCN_MEM_NOT_CACHED:
      unhandled = "IMAGE_SCN_MEM_NOT_CACHED";
      break;
    case IMAGE_SCN_MEM_NOT_PAGED:
      /* Generate a warning message rather using the 'unhandled'
         variable as this will allow some .sys files generate by
         other toolchains to be processed.  See bugzilla issue 196.  */
      /* xgettext:c-format */
      _bfd_error_handler(_("%pB: warning: ignoring section flag"
                           " %s in section %s"),
                         abfd, "IMAGE_SCN_MEM_NOT_PAGED", name);
      break;
    case IMAGE_SCN_MEM_EXECUTE:
      sec_flags |= SEC_CODE;
      break;
    case IMAGE_SCN_MEM_WRITE:
      sec_flags &= ~SEC_READONLY;
      break;
    case IMAGE_SCN_MEM_DISCARDABLE:
      /* The MS PE spec says that debug sections are DISCARDABLE,
         but the presence of a DISCARDABLE flag does not necessarily
         mean that a given section contains debug information.  Thus
         we only set the SEC_DEBUGGING flag on sections that we
         recognise as containing debug information.  */
      if (is_dbg
#ifdef _COMMENT
          || strcmp(name, _COMMENT) == 0
#endif
      ) {
        sec_flags |= SEC_DEBUGGING | SEC_READONLY;
      }
      break;
    case IMAGE_SCN_MEM_SHARED:
      sec_flags |= SEC_COFF_SHARED;
      break;
    case IMAGE_SCN_LNK_REMOVE:
      if (!is_dbg)
        sec_flags |= SEC_EXCLUDE;
      break;
    case IMAGE_SCN_CNT_CODE:
      sec_flags |= SEC_CODE | SEC_ALLOC | SEC_LOAD;
      break;
    case IMAGE_SCN_CNT_INITIALIZED_DATA:
      if (is_dbg)
        sec_flags |= SEC_DEBUGGING;
      else
        sec_flags |= SEC_DATA | SEC_ALLOC | SEC_LOAD;
      break;
    case IMAGE_SCN_CNT_UNINITIALIZED_DATA:
      sec_flags |= SEC_ALLOC;
      break;
    case IMAGE_SCN_LNK_INFO:
      /* We mark these as SEC_DEBUGGING, but only if COFF_PAGE_SIZE is
         defined.  coff_compute_section_file_positions uses
         COFF_PAGE_SIZE to ensure that the low order bits of the
         section VMA and the file offset match.  If we don't know
         COFF_PAGE_SIZE, we can't ensure the correct correspondence,
         and demand page loading of the file will fail.  */
#ifdef COFF_PAGE_SIZE
      sec_flags |= SEC_DEBUGGING;
#endif
      break;
    case IMAGE_SCN_LNK_COMDAT:
      /* COMDAT gets very special treatment.  */
      sec_flags = handle_COMDAT(abfd, sec_flags, hdr, name, section);
      break;
    default:
      /* Silently ignore for now.  */
      break;
    }

    /* If the section flag was not handled, report it here.  */
    if (unhandled != NULL) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB (%s): section flag %s (%#lx) ignored"), abfd, name, unhandled,
           flag);
      result = FALSE;
    }
  }

  if ((bfd_applicable_section_flags(abfd) & SEC_SMALL_DATA) != 0 &&
      (CONST_STRNEQ(name, ".sbss") || CONST_STRNEQ(name, ".sdata")))
    sec_flags |= SEC_SMALL_DATA;

#if defined(COFF_LONG_SECTION_NAMES) && defined(COFF_SUPPORT_GNU_LINKONCE)
  /* As a GNU extension, if the name begins with .gnu.linkonce, we
     only link a single copy of the section.  This is used to support
     g++.  g++ will emit each template expansion in its own section.
     The symbols will be defined as weak, so that multiple definitions
     are permitted.  The GNU linker extension is to actually discard
     all but one of the sections.  */
  if (CONST_STRNEQ(name, ".gnu.linkonce"))
    sec_flags |= SEC_LINK_ONCE | SEC_LINK_DUPLICATES_DISCARD;
#endif

  if (flags_ptr)
    *flags_ptr = sec_flags;

  return result;
}

static bfd_boolean make_a_section_from_file(bfd *abfd,
                                            struct internal_scnhdr *hdr,
                                            unsigned int target_index) {
  asection *return_section;
  char *name;
  bfd_boolean result = TRUE;
  flagword flags;

  name = NULL;

  /* Handle long section names as in PE.  On reading, we want to
    accept long names if the format permits them at all, regardless
    of the current state of the flag that dictates if we would generate
    them in outputs; this construct checks if that is the case by
    attempting to set the flag, without changing its state; the call
    will fail for formats that do not support long names at all.  */
  if (bfd_coff_set_long_section_names(abfd,
                                      bfd_coff_long_section_names(abfd)) &&
      hdr->s_name[0] == '/') {
    char buf[SCNNMLEN];
    long strindex;
    char *p;
    const char *strings;

    /* Flag that this BFD uses long names, even though the format might
       expect them to be off by default.  This won't directly affect the
       format of any output BFD created from this one, but the information
       can be used to decide what to do.  */
    bfd_coff_set_long_section_names(abfd, TRUE);
    memcpy(buf, hdr->s_name + 1, SCNNMLEN - 1);
    buf[SCNNMLEN - 1] = '\0';
    strindex = strtol(buf, &p, 10);
    if (*p == '\0' && strindex >= 0) {
      strings = _bfd_coff_read_string_table(abfd);
      if (strings == NULL)
        return FALSE;
      if ((bfd_size_type)(strindex + 2) >= obj_coff_strings_len(abfd))
        return FALSE;
      strings += strindex;
      name = (char *)bfd_alloc(abfd, (bfd_size_type)strlen(strings) + 1 + 1);
      if (name == NULL)
        return FALSE;
      strcpy(name, strings);
    }
  }

  if (name == NULL) {
    /* Assorted wastage to null-terminate the name, thanks AT&T! */
    name = (char *)bfd_alloc(abfd, (bfd_size_type)sizeof(hdr->s_name) + 1 + 1);
    if (name == NULL)
      return FALSE;
    strncpy(name, (char *)&hdr->s_name[0], sizeof(hdr->s_name));
    name[sizeof(hdr->s_name)] = 0;
  }

  return_section = bfd_make_section_anyway(abfd, name);
  if (return_section == NULL)
    return FALSE;

  return_section->vma = hdr->s_vaddr;
  return_section->lma = hdr->s_paddr;
  return_section->size = hdr->s_size;
  return_section->filepos = hdr->s_scnptr;
  return_section->rel_filepos = hdr->s_relptr;
  return_section->reloc_count = hdr->s_nreloc;

  bfd_coff_set_alignment_hook(abfd, return_section, hdr);

  return_section->line_filepos = hdr->s_lnnoptr;

  return_section->lineno_count = hdr->s_nlnno;
  return_section->userdata = NULL;
  return_section->next = NULL;
  return_section->target_index = target_index;

  if (!bfd_coff_styp_to_sec_flags_hook(abfd, hdr, name, return_section, &flags))
    result = FALSE;

  return_section->flags = flags;

  /* At least on i386-coff, the line number count for a shared library
     section must be ignored.  */
  if ((return_section->flags & SEC_COFF_SHARED_LIBRARY) != 0)
    return_section->lineno_count = 0;

  if (hdr->s_nreloc != 0)
    return_section->flags |= SEC_RELOC;
  /* FIXME: should this check 'hdr->s_size > 0'.  */
  if (hdr->s_scnptr != 0)
    return_section->flags |= SEC_HAS_CONTENTS;

  /* Compress/decompress DWARF debug sections with names: .debug_* and
     .zdebug_*, after the section flags is set.  */
  if ((flags & SEC_DEBUGGING) && strlen(name) > 7 &&
      ((name[1] == 'd' && name[6] == '_') ||
       (strlen(name) > 8 && name[1] == 'z' && name[7] == '_'))) {
    enum { nothing, compress, decompress } action = nothing;
    char *new_name = NULL;

    if (bfd_is_section_compressed(abfd, return_section)) {
      /* Compressed section.  Check if we should decompress.  */
      if ((abfd->flags & BFD_DECOMPRESS))
        action = decompress;
    } else if (!bfd_is_section_compressed(abfd, return_section)) {
      /* Normal section.  Check if we should compress.  */
      if ((abfd->flags & BFD_COMPRESS) && return_section->size != 0)
        action = compress;
    }

    switch (action) {
    case nothing:
      break;
    case compress:
      if (!bfd_init_section_compress_status(abfd, return_section)) {
        _bfd_error_handler
            /* xgettext: c-format */
            (_("%pB: unable to initialize compress status for section %s"),
             abfd, name);
        return FALSE;
      }
      if (return_section->compress_status == COMPRESS_SECTION_DONE) {
        if (name[1] != 'z') {
          unsigned int len = strlen(name);

          new_name = bfd_alloc(abfd, len + 2);
          if (new_name == NULL)
            return FALSE;
          new_name[0] = '.';
          new_name[1] = 'z';
          memcpy(new_name + 2, name + 1, len);
        }
      }
      break;
    case decompress:
      if (!bfd_init_section_decompress_status(abfd, return_section)) {
        _bfd_error_handler
            /* xgettext: c-format */
            (_("%pB: unable to initialize decompress status for section %s"),
             abfd, name);
        return FALSE;
      }
      if (name[1] == 'z') {
        unsigned int len = strlen(name);

        new_name = bfd_alloc(abfd, len);
        if (new_name == NULL)
          return FALSE;
        new_name[0] = '.';
        memcpy(new_name + 1, name + 2, len - 1);
      }
      break;
    }
    if (new_name != NULL)
      bfd_rename_section(return_section, new_name);
  }

  return result;
}


bfd_cleanup coff_real_object_p(bfd *abfd, unsigned nscns,
                               struct internal_filehdr *internal_f,
                               struct internal_aouthdr *internal_a) {
  flagword oflags = abfd->flags;
  bfd_vma ostart = bfd_get_start_address(abfd);
  void *tdata;
  void *tdata_save;
  bfd_size_type readsize; /* Length of file_info.  */
  unsigned int scnhsz;
  char *external_sections;

  if (!(internal_f->f_flags & F_RELFLG))
    abfd->flags |= HAS_RELOC;
  if ((internal_f->f_flags & F_EXEC))
    abfd->flags |= EXEC_P;
  if (!(internal_f->f_flags & F_LNNO))
    abfd->flags |= HAS_LINENO;
  if (!(internal_f->f_flags & F_LSYMS))
    abfd->flags |= HAS_LOCALS;

  /* FIXME: How can we set D_PAGED correctly?  */
  if ((internal_f->f_flags & F_EXEC) != 0)
    abfd->flags |= D_PAGED;

  abfd->symcount = internal_f->f_nsyms;
  if (internal_f->f_nsyms)
    abfd->flags |= HAS_SYMS;

  if (internal_a != (struct internal_aouthdr *)NULL)
    abfd->start_address = internal_a->entry;
  else
    abfd->start_address = 0;

  /* Set up the tdata area.  ECOFF uses its own routine, and overrides
     abfd->flags.  */
  tdata_save = abfd->tdata.any;
  tdata = bfd_coff_mkobject_hook(abfd, (void *)internal_f, (void *)internal_a);
  if (tdata == NULL)
    goto fail2;

  scnhsz = bfd_coff_scnhsz(abfd);
  readsize = (bfd_size_type)nscns * scnhsz;
  external_sections = (char *)_bfd_alloc_and_read(abfd, readsize, readsize);
  if (!external_sections)
    goto fail;

  /* Set the arch/mach *before* swapping in sections; section header swapping
     may depend on arch/mach info.  */
  if (!bfd_coff_set_arch_mach_hook(abfd, (void *)internal_f))
    goto fail;

  /* Now copy data as required; construct all asections etc.  */
  if (nscns != 0) {
    unsigned int i;
    for (i = 0; i < nscns; i++) {
      struct internal_scnhdr tmp;
      bfd_coff_swap_scnhdr_in(abfd, (void *)(external_sections + i * scnhsz),
                              (void *)&tmp);
      if (!make_a_section_from_file(abfd, &tmp, i + 1))
        goto fail;
    }
  }

  
  _bfd_coff_free_symbols(abfd);
  return _bfd_no_cleanup;

fail:
  _bfd_coff_free_symbols(abfd);
  bfd_release(abfd, tdata);
fail2:
  abfd->tdata.any = tdata_save;
  abfd->flags = oflags;
  abfd->start_address = ostart;
  return NULL;
}

static bfd_cleanup pe_bfd_object_p(bfd *abfd) {
  bfd_byte buffer[6];
  struct external_DOS_hdr dos_hdr;
  struct external_PEI_IMAGE_hdr image_hdr;
  struct internal_filehdr internal_f;
  struct internal_aouthdr internal_a;
  bfd_size_type opt_hdr_size;
  file_ptr offset;
  bfd_cleanup result;

  /* Detect if this a Microsoft Import Library Format element.  */
  /* First read the beginning of the header.  */
  if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0 ||
      bfd_bread(buffer, (bfd_size_type)6, abfd) != 6) {
    if (bfd_get_error() != bfd_error_system_call)
      bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  /* Then check the magic and the version (only 0 is supported).  */
  if (H_GET_32(abfd, buffer) == 0xffff0000 && H_GET_16(abfd, buffer + 4) == 0)
    return pe_ILF_object_p(abfd);

  if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0 ||
      bfd_bread(&dos_hdr, (bfd_size_type)sizeof(dos_hdr), abfd) !=
          sizeof(dos_hdr)) {
    if (bfd_get_error() != bfd_error_system_call)
      bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  /* There are really two magic numbers involved; the magic number
     that says this is a NT executable (PEI) and the magic number that
     determines the architecture.  The former is IMAGE_DOS_SIGNATURE, stored in
     the e_magic field.  The latter is stored in the f_magic field.
     If the NT magic number isn't valid, the architecture magic number
     could be mimicked by some other field (specifically, the number
     of relocs in section 3).  Since this routine can only be called
     correctly for a PEI file, check the e_magic number here, and, if
     it doesn't match, clobber the f_magic number so that we don't get
     a false match.  */
  if (H_GET_16(abfd, dos_hdr.e_magic) != IMAGE_DOS_SIGNATURE) {
    bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  offset = H_GET_32(abfd, dos_hdr.e_lfanew);
  if (bfd_seek(abfd, offset, SEEK_SET) != 0 ||
      (bfd_bread(&image_hdr, (bfd_size_type)sizeof(image_hdr), abfd) !=
       sizeof(image_hdr))) {
    if (bfd_get_error() != bfd_error_system_call)
      bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  if (H_GET_32(abfd, image_hdr.nt_signature) != 0x4550) {
    bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  /* Swap file header, so that we get the location for calling
     real_object_p.  */
  bfd_coff_swap_filehdr_in(abfd, &image_hdr, &internal_f);

  if (!bfd_coff_bad_format_hook(abfd, &internal_f) ||
      internal_f.f_opthdr > bfd_coff_aoutsz(abfd)) {
    bfd_set_error(bfd_error_wrong_format);
    return NULL;
  }

  memcpy(internal_f.pe.dos_message, dos_hdr.dos_message,
         sizeof(internal_f.pe.dos_message));

  /* Read the optional header, which has variable size.  */
  opt_hdr_size = internal_f.f_opthdr;

  if (opt_hdr_size != 0) {
    bfd_size_type amt = opt_hdr_size;
    void *opthdr;

    /* PR 17521 file: 230-131433-0.004.  */
    if (amt < sizeof(PEAOUTHDR))
      amt = sizeof(PEAOUTHDR);

    opthdr = _bfd_alloc_and_read(abfd, amt, opt_hdr_size);
    if (opthdr == NULL)
      return NULL;
    if (amt > opt_hdr_size)
      memset(opthdr + opt_hdr_size, 0, amt - opt_hdr_size);

    bfd_set_error(bfd_error_no_error);
    bfd_coff_swap_aouthdr_in(abfd, opthdr, &internal_a);
    if (bfd_get_error() != bfd_error_no_error)
      return NULL;
  }

  result = coff_real_object_p(
      abfd, internal_f.f_nscns, &internal_f,
      (opt_hdr_size != 0 ? &internal_a : (struct internal_aouthdr *)NULL));

  if (result) {
    /* Now the whole header has been processed, see if there is a build-id */
    pe_bfd_read_buildid(abfd);
  }

  return result;
}


combined_entry_type *coff_get_normalized_symtab(bfd *abfd) {
  combined_entry_type *internal;
  combined_entry_type *internal_ptr;
  combined_entry_type *symbol_ptr;
  combined_entry_type *internal_end;
  size_t symesz;
  char *raw_src;
  char *raw_end;
  const char *string_table = NULL;
  asection *debug_sec = NULL;
  char *debug_sec_data = NULL;
  bfd_size_type size;

  if (obj_raw_syments(abfd) != NULL)
    return obj_raw_syments(abfd);

  if (!_bfd_coff_get_external_symbols(abfd))
    return NULL;

  size = obj_raw_syment_count(abfd);
  /* Check for integer overflow.  */
  if (size > (bfd_size_type)-1 / sizeof(combined_entry_type))
    return NULL;
  size *= sizeof(combined_entry_type);
  internal = (combined_entry_type *)bfd_zalloc(abfd, size);
  if (internal == NULL && size != 0)
    return NULL;
  internal_end = internal + obj_raw_syment_count(abfd);

  raw_src = (char *)obj_coff_external_syms(abfd);

  /* Mark the end of the symbols.  */
  symesz = bfd_coff_symesz(abfd);
  raw_end = (char *)raw_src + obj_raw_syment_count(abfd) * symesz;

  /* FIXME SOMEDAY.  A string table size of zero is very weird, but
     probably possible.  If one shows up, it will probably kill us.  */

  /* Swap all the raw entries.  */
  for (internal_ptr = internal; raw_src < raw_end;
       raw_src += symesz, internal_ptr++) {
    unsigned int i;

    bfd_coff_swap_sym_in(abfd, (void *)raw_src,
                         (void *)&internal_ptr->u.syment);
    symbol_ptr = internal_ptr;
    internal_ptr->is_sym = TRUE;

    for (i = 0; i < symbol_ptr->u.syment.n_numaux; i++) {
      internal_ptr++;
      raw_src += symesz;

      /* PR 17512: Prevent buffer overrun.  */
      if (raw_src >= raw_end || internal_ptr >= internal_end) {
        bfd_release(abfd, internal);
        return NULL;
      }

      bfd_coff_swap_aux_in(abfd, (void *)raw_src, symbol_ptr->u.syment.n_type,
                           symbol_ptr->u.syment.n_sclass, (int)i,
                           symbol_ptr->u.syment.n_numaux,
                           &(internal_ptr->u.auxent));

      internal_ptr->is_sym = FALSE;
      coff_pointerize_aux(abfd, internal, symbol_ptr, i, internal_ptr,
                          internal_end);
    }
  }

  /* Free the raw symbols.  */
  if (obj_coff_external_syms(abfd) != NULL && !obj_coff_keep_syms(abfd)) {
    free(obj_coff_external_syms(abfd));
    obj_coff_external_syms(abfd) = NULL;
  }

  for (internal_ptr = internal; internal_ptr < internal_end; internal_ptr++) {
    BFD_ASSERT(internal_ptr->is_sym);

    if (internal_ptr->u.syment.n_sclass == C_FILE &&
        internal_ptr->u.syment.n_numaux > 0) {
      combined_entry_type *aux = internal_ptr + 1;

      /* Make a file symbol point to the name in the auxent, since
         the text ".file" is redundant.  */
      BFD_ASSERT(!aux->is_sym);

      if (aux->u.auxent.x_file.x_n.x_zeroes == 0) {
        /* The filename is a long one, point into the string table.  */
        if (string_table == NULL) {
          string_table = _bfd_coff_read_string_table(abfd);
          if (string_table == NULL)
            return NULL;
        }

        if ((bfd_size_type)(aux->u.auxent.x_file.x_n.x_offset) >=
            obj_coff_strings_len(abfd))
          internal_ptr->u.syment._n._n_n._n_offset =
              (bfd_hostptr_t)_("<corrupt>");
        else
          internal_ptr->u.syment._n._n_n._n_offset =
              (bfd_hostptr_t)(string_table +
                              (aux->u.auxent.x_file.x_n.x_offset));
      } else {
        /* Ordinary short filename, put into memory anyway.  The
           Microsoft PE tools sometimes store a filename in
           multiple AUX entries.  */
        if (internal_ptr->u.syment.n_numaux > 1 && coff_data(abfd)->pe)
          internal_ptr->u.syment._n._n_n._n_offset = (bfd_hostptr_t)copy_name(
              abfd, aux->u.auxent.x_file.x_fname,
              internal_ptr->u.syment.n_numaux * symesz);
        else
          internal_ptr->u.syment._n._n_n._n_offset =
              ((bfd_hostptr_t)copy_name(abfd, aux->u.auxent.x_file.x_fname,
                                        (size_t)bfd_coff_filnmlen(abfd)));
      }
    } else {
      if (internal_ptr->u.syment._n._n_n._n_zeroes != 0) {
        /* This is a "short" name.  Make it long.  */
        size_t i;
        char *newstring;

        /* Find the length of this string without walking into memory
           that isn't ours.  */
        for (i = 0; i < 8; ++i)
          if (internal_ptr->u.syment._n._n_name[i] == '\0')
            break;

        newstring = (char *)bfd_zalloc(abfd, (bfd_size_type)(i + 1));
        if (newstring == NULL)
          return NULL;
        strncpy(newstring, internal_ptr->u.syment._n._n_name, i);
        internal_ptr->u.syment._n._n_n._n_offset = (bfd_hostptr_t)newstring;
        internal_ptr->u.syment._n._n_n._n_zeroes = 0;
      } else if (internal_ptr->u.syment._n._n_n._n_offset == 0)
        internal_ptr->u.syment._n._n_n._n_offset = (bfd_hostptr_t) "";
      else if (!bfd_coff_symname_in_debug(abfd, &internal_ptr->u.syment)) {
        /* Long name already.  Point symbol at the string in the
           table.  */
        if (string_table == NULL) {
          string_table = _bfd_coff_read_string_table(abfd);
          if (string_table == NULL)
            return NULL;
        }
        if (internal_ptr->u.syment._n._n_n._n_offset >=
                obj_coff_strings_len(abfd) ||
            string_table + internal_ptr->u.syment._n._n_n._n_offset <
                string_table)
          internal_ptr->u.syment._n._n_n._n_offset =
              (bfd_hostptr_t)_("<corrupt>");
        else
          internal_ptr->u.syment._n._n_n._n_offset =
              ((bfd_hostptr_t)(string_table +
                               internal_ptr->u.syment._n._n_n._n_offset));
      } else {
        /* Long name in debug section.  Very similar.  */
        if (debug_sec_data == NULL)
          debug_sec_data = build_debug_section(abfd, &debug_sec);
        if (debug_sec_data != NULL) {
          BFD_ASSERT(debug_sec != NULL);
          /* PR binutils/17512: Catch out of range offsets into the debug data.
           */
          if (internal_ptr->u.syment._n._n_n._n_offset > debug_sec->size ||
              debug_sec_data + internal_ptr->u.syment._n._n_n._n_offset <
                  debug_sec_data)
            internal_ptr->u.syment._n._n_n._n_offset =
                (bfd_hostptr_t)_("<corrupt>");
          else
            internal_ptr->u.syment._n._n_n._n_offset =
                (bfd_hostptr_t)(debug_sec_data +
                                internal_ptr->u.syment._n._n_n._n_offset);
        } else
          internal_ptr->u.syment._n._n_n._n_offset = (bfd_hostptr_t) "";
      }
    }
    internal_ptr += internal_ptr->u.syment.n_numaux;
  }

  obj_raw_syments(abfd) = internal;
  BFD_ASSERT(obj_raw_syment_count(abfd) ==
             (unsigned int)(internal_ptr - internal));

  return internal;
}

void display_file(bfd *abfd) {
  pe_bfd_object_p(abfd);
  coff_get_normalized_symtab(abfd);
}
