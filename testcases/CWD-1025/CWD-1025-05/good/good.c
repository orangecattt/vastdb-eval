#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HOST_WIDEST_INT int64_t

#define _(x) (x)
#define ngettext(s1, s2, n) ((n) == 1 ? (s1) : (s2))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define streq(a, b) (strcmp((a), (b)) == 0)

typedef uint64_t bfd_vma;
typedef uint64_t bfd_size_type;
typedef uint64_t elf_vma;
typedef int bfd_boolean;
typedef void *PTR;
#define FALSE 0
#define TRUE 1

typedef struct {
  unsigned char e_ident[16];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  bfd_vma e_entry;
  bfd_vma e_phoff;
  bfd_vma e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
} Elf_Internal_Ehdr;

typedef struct {
  uint32_t sh_name;
  uint32_t sh_type;
  bfd_vma sh_flags;
  bfd_vma sh_addr;
  bfd_vma sh_offset;
  bfd_vma sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  bfd_vma sh_addralign;
  bfd_vma sh_entsize;
} Elf_Internal_Shdr;

typedef struct {
  uint32_t p_type;
  uint32_t p_flags;
  bfd_vma p_offset;
  bfd_vma p_vaddr;
  bfd_vma p_paddr;
  bfd_vma p_filesz;
  bfd_vma p_memsz;
  bfd_vma p_align;
} Elf_Internal_Phdr;

typedef struct {
  bfd_vma d_tag;
  union {
    bfd_vma d_val;
    bfd_vma d_ptr;
  } d_un;
} Elf_Internal_Dyn;

typedef struct {
  uint32_t st_name;
  bfd_vma st_value;
  bfd_vma st_size;
  unsigned char st_info;
  unsigned char st_other;
  uint16_t st_shndx;
} Elf_Internal_Sym;

typedef struct {
  uint16_t si_boundto;
  uint16_t si_flags;
} Elf_Internal_Syminfo;

typedef struct {
  unsigned char si_boundto;
  unsigned char si_flags;
} Elf_External_Syminfo;

typedef unsigned char dump_type;
#define HEX_DUMP (1 << 0)
#define DISASS_DUMP (1 << 1)
#define DEBUG_DUMP (1 << 2)
#define STRING_DUMP (1 << 3)
#define RELOC_DUMP (1 << 4)
#define CTF_DUMP (1 << 5)

typedef struct filedata {
  const char *file_name;
  FILE *handle;
  bfd_size_type file_size;
  Elf_Internal_Ehdr file_header;
  Elf_Internal_Shdr *section_headers;
  Elf_Internal_Phdr *program_headers;
  char *string_table;
  unsigned long string_table_length;
  dump_type *dump_sects;
  unsigned int num_dump_sects;
} Filedata;

typedef struct elf_section_list {
  Elf_Internal_Shdr *hdr;
  struct elf_section_list *next;
} elf_section_list;

struct group_list {
  struct group_list *next;
  unsigned int section_index;
};

struct group {
  struct group_list *root;
  unsigned int group_index;
};

typedef struct separate_info {
  void *handle;
  const char *filename;
  struct separate_info *next;
} separate_info;

typedef enum print_mode {
  HEX,
  DEC,
  DEC_5,
  UNSIGNED,
  PREFIX_HEX,
  FULL_HEX,
  LONG_HEX
} print_mode;

#define DT_ENCODING 32
#define DT_NULL 0
#define DT_NEEDED 1
#define DT_PLTRELSZ 2
#define DT_PLTGOT 3
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_STRSZ 10
#define DT_SYMENT 11
#define DT_INIT 12
#define DT_FINI 13
#define DT_SONAME 14
#define DT_RPATH 15
#define DT_SYMBOLIC 16
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_PLTREL 20
#define DT_DEBUG 21
#define DT_TEXTREL 22
#define DT_JMPREL 23
#define DT_BIND_NOW 24
#define DT_RUNPATH 29
#define DT_FLAGS 30
#define DT_PREINIT_ARRAY 32
#define DT_PREINIT_ARRAYSZ 33
#define DT_AUXILIARY 0x7ffffffd
#define DT_FILTER 0x7fffffff
#define DT_CONFIG 0x1fffffe1
#define DT_DEPAUDIT 0x1ffffef0
#define DT_AUDIT 0x1ffff7a9
#define DT_FEATURE 0x1fffffe5
#define DT_POSFLAG_1 0x1ffffefd
#define DT_FLAGS_1 0x6ffffffb
#define DT_VERDEFNUM 0x6ffffffc
#define DT_VERNEEDNUM 0x6ffffffe
#define DT_RELACOUNT 0x6ffffff9
#define DT_RELCOUNT 0x6ffffffa
#define DT_PLTPADSZ 0x6ffffef6
#define DT_MOVEENT 0x6fffffea
#define DT_MOVESZ 0x6ffffefb
#define DT_INIT_ARRAYSZ 0x6ffffef9
#define DT_FINI_ARRAYSZ 0x6ffffefa
#define DT_GNU_CONFLICTSZ 0x6ffffef2
#define DT_GNU_LIBLISTSZ 0x6ffffef3
#define DT_USED 0x6ffffff0
#define DT_INIT_ARRAY 0x6ffffef7
#define DT_FINI_ARRAY 0x6ffffef8
#define DT_GNU_PRELINKED 0x6ffffdf5
#define DT_VERSYM 0x6ffffff0
#define DT_VERNEED 0x6ffffffe
#define DT_SYMINENT 0x6ffffeff
#define DT_SYMINSZ 0x6ffffefe
#define DT_SYMINFO 0x6ffffef0
#define DT_GNU_HASH 0x6ffffef5
#define DT_MIPS_XHASH 0x70000034
#define DT_VERSIONTAGIDX(tag) (18 - (tag))

#define EM_ALPHA 0x18
#define EM_S390 0x16
#define EM_S390_OLD 0xa390
#define EM_MIPS 0x8
#define EM_MIPS_RS3_LE 0x35
#define EM_AARCH64 0xb7
#define EM_PARISC 0x0f
#define EM_IA_64 0x32
#define ELFCLASS64 2
#define PT_LOAD 1
#define SHN_UNDEF 0
#define SHT_SYMTAB 2
#define SHT_DYNSYM 11

#define BYTE_GET(field) byte_get(field, sizeof(field))
#define VALID_DYNAMIC_NAME(offset)                                             \
  (dynamic_strings != NULL && (offset) < dynamic_strings_length)
#define GET_DYNAMIC_NAME(offset) (dynamic_strings + (offset))
#define GET_ELF_SYMBOLS(file, section, sym_count)                              \
  (is_32bit_elf ? get_32bit_elf_symbols(file, section, sym_count)              \
                : get_64bit_elf_symbols(file, section, sym_count))
#define GNU_HASH_SECTION_NAME                                                  \
  (dynamic_info_DT_MIPS_XHASH ? ".MIPS.xhash" : ".gnu.hash")

#define DTF_1_PARINIT 0x1
#define DTF_1_CONFEXP 0x2
#define DF_P1_LAZYLOAD 0x1
#define DF_P1_GROUPPERM 0x2
#define DF_1_NOW 0x1
#define DF_1_GLOBAL 0x2
#define DF_1_GROUP 0x4
#define DF_1_NODELETE 0x8
#define DF_1_LOADFLTR 0x10
#define DF_1_INITFIRST 0x20
#define DF_1_NOOPEN 0x40
#define DF_1_ORIGIN 0x80
#define DF_1_DIRECT 0x100
#define DF_1_TRANS 0x200
#define DF_1_INTERPOSE 0x400
#define DF_1_NODEFLIB 0x800
#define DF_1_NODUMP 0x1000
#define DF_1_CONFALT 0x2000
#define DF_1_ENDFILTEE 0x4000
#define DF_1_DISPRELDNE 0x8000
#define DF_1_DISPRELPND 0x10000
#define DF_1_NODIRECT 0x20000
#define DF_1_IGNMULDEF 0x40000
#define DF_1_NOKSYMS 0x80000
#define DF_1_NOHDR 0x100000
#define DF_1_EDITED 0x200000
#define DF_1_NORELOC 0x400000
#define DF_1_SYMINTPOSE 0x800000
#define DF_1_GLOBAUDIT 0x1000000
#define DF_1_SINGLETON 0x2000000
#define DF_1_STUB 0x4000000
#define DF_1_PIE 0x8000000
#define DF_1_KMOD 0x10000000
#define DF_1_WEAKFILTER 0x20000000
#define DF_1_NOCOMMON 0x40000000

#define PATH_MAX 4096

extern void error(const char *, ...);
extern void warn(const char *, ...);
extern elf_vma byte_get(const unsigned char *, int);
static const char *bfd_vmatoa(char *, bfd_vma);

#define BFD_VMA_FMT "l"
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static const char *bfd_vmatoa(char *fmtch, bfd_vma value) {
  static int buf_pos = 0;
  static struct bfd_vmatoa_buf {
    char place[64];
  } buf[4];
  char *ret;
  char fmt[32];

  ret = buf[buf_pos++].place;
  buf_pos %= ARRAY_SIZE(buf);

  sprintf(fmt, "%%%s%s", BFD_VMA_FMT, fmtch);
  snprintf(ret, sizeof(buf[0].place), fmt, value);
  return ret;
}
extern void *xcmalloc(size_t, size_t);
extern void xmalloc_failed(size_t);
extern void xmalloc_set_program_name(const char *);
extern void *xmalloc(size_t);
extern void *xrealloc(void *, size_t);
extern void *xcalloc(size_t, size_t);
extern char *xstrdup(const char *);
extern void free_debug_memory(void);
extern Elf_Internal_Sym *get_32bit_elf_symbols(Filedata *, Elf_Internal_Shdr *,
                                               unsigned long *);
extern Elf_Internal_Sym *get_64bit_elf_symbols(Filedata *, Elf_Internal_Shdr *,
                                               unsigned long *);
extern bfd_boolean get_file_header(Filedata *);
extern bfd_boolean process_file_header(Filedata *);
extern bfd_boolean process_section_headers(Filedata *);
extern bfd_boolean process_section_groups(Filedata *);
extern bfd_boolean process_program_headers(Filedata *);
extern bfd_boolean get_program_headers(Filedata *);
extern bfd_boolean process_relocs(Filedata *);
extern bfd_boolean process_unwind(Filedata *);
extern bfd_boolean process_syminfo(Filedata *);
extern bfd_boolean process_version_sections(Filedata *);
extern bfd_boolean process_section_contents(Filedata *);
extern bfd_boolean process_notes(Filedata *);
extern bfd_boolean process_gnu_liblist(Filedata *);
extern bfd_boolean process_arch_specific(Filedata *);
extern bfd_boolean load_separate_debug_files(Filedata *, const char *);
extern const char *printable_section_name(Filedata *,
                                          const Elf_Internal_Shdr *);
extern void print_dynamic_symbol(Filedata *, unsigned long, Elf_Internal_Sym *,
                                 Elf_Internal_Shdr *, char *, unsigned long);
extern void request_dump_bynumber(Filedata *, unsigned int, dump_type);
extern const char *get_dynamic_type(Filedata *, unsigned long);
extern void print_dynamic_flags(bfd_vma);
extern unsigned int print_vma(bfd_vma, print_mode);
extern void dynamic_section_aarch64_val(Elf_Internal_Dyn *);
extern void dynamic_section_mips_val(Elf_Internal_Dyn *);
extern void dynamic_section_parisc_val(Elf_Internal_Dyn *);
extern void dynamic_section_ia64_val(Elf_Internal_Dyn *);
extern bfd_boolean get_32bit_dynamic_section(Filedata *);
extern bfd_boolean get_64bit_dynamic_section(Filedata *);
extern long offset_from_vma(Filedata *, bfd_vma, bfd_size_type);
extern void *get_data(void *, Filedata *, unsigned long, bfd_size_type,
                      bfd_size_type, const char *);
static bfd_boolean process_symbol_table(Filedata *);

extern unsigned long archive_file_offset;
static unsigned long dynamic_addr;
static bfd_size_type dynamic_size;
static size_t dynamic_nent;
static char *dynamic_strings;
static unsigned long dynamic_strings_length;
static unsigned long num_dynamic_syms;
static bfd_size_type nbuckets;
static bfd_size_type nchains;
static bfd_vma *buckets;
static bfd_vma *chains;
static bfd_vma ngnubuckets;
static bfd_vma *gnubuckets;
static bfd_vma *gnuchains;
static bfd_vma *mipsxlat;
static bfd_size_type ngnuchains;
static bfd_vma gnusymidx;
static Elf_Internal_Sym *dynamic_symbols;
static Elf_Internal_Syminfo *dynamic_syminfo;
static unsigned long dynamic_syminfo_offset;
static unsigned int dynamic_syminfo_nent;
static char program_interpreter[PATH_MAX];
static bfd_vma dynamic_info[DT_ENCODING];
static bfd_vma dynamic_info_DT_GNU_HASH;
static bfd_vma dynamic_info_DT_MIPS_XHASH;
static bfd_vma version_info[16];
static Elf_Internal_Dyn *dynamic_section;
static elf_section_list *symtab_shndx_list;
static bfd_boolean show_name = FALSE;
static bfd_boolean do_dynamic = FALSE;
static bfd_boolean do_syms = FALSE;
static bfd_boolean do_dyn_syms = FALSE;
static bfd_boolean do_reloc = FALSE;
static bfd_boolean do_unwind = FALSE;
static bfd_boolean do_using_dynamic = FALSE;
static bfd_boolean do_dump = FALSE;
static bfd_boolean do_version = FALSE;
static bfd_boolean do_histogram = FALSE;
static bfd_boolean do_arch = FALSE;
static bfd_boolean is_32bit_elf = FALSE;
static size_t group_count;
static struct group *section_groups;
static struct group **section_headers_groups;
static Filedata cmdline;
extern separate_info *first_separate_info;

#define EI_CLASS 4

static bfd_vma *chains;

PTR xmalloc(size_t size) {
  PTR newmem;

  if (size == 0)
    size = 1;
  newmem = malloc(size);
  if (!newmem)
    xmalloc_failed(size);

  return (newmem);
}

void *cmalloc(size_t nmemb, size_t size) {
  /* Check for overflow.  */
  if (nmemb >= ~(size_t)0 / size)
    return NULL;

  return xmalloc(nmemb * size);
}

static bfd_vma *get_dynamic_data(Filedata *filedata, bfd_size_type number,
                                 unsigned int ent_size) {
  unsigned char *e_data;
  bfd_vma *i_data;

  /* If the size_t type is smaller than the bfd_size_type, eg because
     you are building a 32-bit tool on a 64-bit host, then make sure
     that when (number) is cast to (size_t) no information is lost.  */
  if (sizeof(size_t) < sizeof(bfd_size_type) &&
      (bfd_size_type)((size_t)number) != number) {
    error(_("Size truncation prevents reading %s elements of size %u\n"),
          bfd_vmatoa("u", number), ent_size);
    return NULL;
  }

  /* Be kind to memory checkers (eg valgrind, address sanitizer) by not
     attempting to allocate memory when the read is bound to fail.  */
  if (ent_size * number > filedata->file_size) {
    error(_("Invalid number of dynamic entries: %s\n"),
          bfd_vmatoa("u", number));
    return NULL;
  }

  e_data = (unsigned char *)cmalloc((size_t)number, ent_size);
  if (e_data == NULL) {
    error(_("Out of memory reading %s dynamic entries\n"),
          bfd_vmatoa("u", number));
    return NULL;
  }

  if (fread(e_data, ent_size, (size_t)number, filedata->handle) != number) {
    error(_("Unable to read in %s bytes of dynamic data\n"),
          bfd_vmatoa("u", number * ent_size));
    free(e_data);
    return NULL;
  }

  i_data = (bfd_vma *)cmalloc((size_t)number, sizeof(*i_data));
  if (i_data == NULL) {
    error(_("Out of memory allocating space for %s dynamic entries\n"),
          bfd_vmatoa("u", number));
    free(e_data);
    return NULL;
  }

  while (number--)
    i_data[number] = byte_get(e_data + number * ent_size, ent_size);

  free(e_data);

  return i_data;
}

static unsigned long get_num_dynamic_syms(Filedata *filedata) {
  unsigned long num_of_syms = 0;

  if (!do_histogram && (!do_using_dynamic || do_dyn_syms))
    return num_of_syms;

  if (dynamic_info[DT_HASH]) {
    unsigned char nb[8];
    unsigned char nc[8];
    unsigned int hash_ent_size = 4;

    if ((filedata->file_header.e_machine == EM_ALPHA ||
         filedata->file_header.e_machine == EM_S390 ||
         filedata->file_header.e_machine == EM_S390_OLD) &&
        filedata->file_header.e_ident[EI_CLASS] == ELFCLASS64)
      hash_ent_size = 8;

    if (fseek(filedata->handle,
              (archive_file_offset + offset_from_vma(filedata,
                                                     dynamic_info[DT_HASH],
                                                     sizeof nb + sizeof nc)),
              SEEK_SET)) {
      error(_("Unable to seek to start of dynamic information\n"));
      goto no_hash;
    }

    if (fread(nb, hash_ent_size, 1, filedata->handle) != 1) {
      error(_("Failed to read in number of buckets\n"));
      goto no_hash;
    }

    if (fread(nc, hash_ent_size, 1, filedata->handle) != 1) {
      error(_("Failed to read in number of chains\n"));
      goto no_hash;
    }

    nbuckets = byte_get(nb, hash_ent_size);
    nchains = byte_get(nc, hash_ent_size);
    num_of_syms = nchains;

    buckets = get_dynamic_data(filedata, nbuckets, hash_ent_size);
    chains = get_dynamic_data(filedata, nchains, hash_ent_size);

  no_hash:
    if (num_of_syms == 0) {
      if (buckets) {
        free(buckets);
        buckets = NULL;
      }
      if (chains) {
        
        free(chains);
        chains = NULL;
      }
      nbuckets = 0;
    }
  }

  if (dynamic_info_DT_GNU_HASH) {
    unsigned char nb[16];
    bfd_vma i, maxchain = 0xffffffff, bitmaskwords;
    bfd_vma buckets_vma;
    unsigned long hn;
    bfd_boolean gnu_hash_error = FALSE;

    if (fseek(filedata->handle,
              (archive_file_offset +
               offset_from_vma(filedata, dynamic_info_DT_GNU_HASH, sizeof nb)),
              SEEK_SET)) {
      error(_("Unable to seek to start of dynamic information\n"));
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    if (fread(nb, 16, 1, filedata->handle) != 1) {
      error(_("Failed to read in number of buckets\n"));
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    ngnubuckets = byte_get(nb, 4);
    gnusymidx = byte_get(nb + 4, 4);
    bitmaskwords = byte_get(nb + 8, 4);
    buckets_vma = dynamic_info_DT_GNU_HASH + 16;
    if (is_32bit_elf)
      buckets_vma += bitmaskwords * 4;
    else
      buckets_vma += bitmaskwords * 8;

    if (fseek(filedata->handle,
              (archive_file_offset + offset_from_vma(filedata, buckets_vma, 4)),
              SEEK_SET)) {
      error(_("Unable to seek to start of dynamic information\n"));
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    gnubuckets = get_dynamic_data(filedata, ngnubuckets, 4);

    if (gnubuckets == NULL) {
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    for (i = 0; i < ngnubuckets; i++)
      if (gnubuckets[i] != 0) {
        if (gnubuckets[i] < gnusymidx) {
          gnu_hash_error = TRUE;
          return FALSE;
        }

        if (maxchain == 0xffffffff || gnubuckets[i] > maxchain)
          maxchain = gnubuckets[i];
      }

    if (maxchain == 0xffffffff) {
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    maxchain -= gnusymidx;

    if (fseek(filedata->handle,
              (archive_file_offset +
               offset_from_vma(filedata,
                               buckets_vma + 4 * (ngnubuckets + maxchain), 4)),
              SEEK_SET)) {
      error(_("Unable to seek to start of dynamic information\n"));
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    do {
      if (fread(nb, 4, 1, filedata->handle) != 1) {
        error(_("Failed to determine last chain length\n"));
        gnu_hash_error = TRUE;
        goto no_gnu_hash;
      }

      if (maxchain + 1 == 0) {
        gnu_hash_error = TRUE;
        goto no_gnu_hash;
      }

      ++maxchain;
    } while ((byte_get(nb, 4) & 1) == 0);

    if (fseek(filedata->handle,
              (archive_file_offset +
               offset_from_vma(filedata, buckets_vma + 4 * ngnubuckets, 4)),
              SEEK_SET)) {
      error(_("Unable to seek to start of dynamic information\n"));
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    gnuchains = get_dynamic_data(filedata, maxchain, 4);
    ngnuchains = maxchain;

    if (gnuchains == NULL) {
      gnu_hash_error = TRUE;
      goto no_gnu_hash;
    }

    if (dynamic_info_DT_MIPS_XHASH) {
      if (fseek(filedata->handle,
                (archive_file_offset +
                 offset_from_vma(filedata,
                                 (buckets_vma + 4 * (ngnubuckets + maxchain)),
                                 4)),
                SEEK_SET)) {
        error(_("Unable to seek to start of dynamic information\n"));
        gnu_hash_error = TRUE;
        goto no_gnu_hash;
      }

      mipsxlat = get_dynamic_data(filedata, maxchain, 4);
    }

    for (hn = 0; hn < ngnubuckets; ++hn)
      if (gnubuckets[hn] != 0) {
        bfd_vma si = gnubuckets[hn];
        bfd_vma off = si - gnusymidx;

        do {
          if (dynamic_info_DT_MIPS_XHASH) {
            if (mipsxlat[off] >= num_of_syms)
              num_of_syms = mipsxlat[off] + 1;
          } else {
            if (si >= num_of_syms)
              num_of_syms = si + 1;
          }
          si++;
        } while (off < ngnuchains && (gnuchains[off++] & 1) == 0);
      }

  no_gnu_hash:
    if (gnu_hash_error) {
      if (mipsxlat) {
        free(mipsxlat);
        mipsxlat = NULL;
      }
      if (gnuchains) {
        free(gnuchains);
        gnuchains = NULL;
      }
      if (gnubuckets) {
        free(gnubuckets);
        gnubuckets = NULL;
      }
      ngnubuckets = 0;
      ngnuchains = 0;
    }
  }

  return num_of_syms;
}

static bfd_boolean process_dynamic_section(Filedata *filedata) {
  Elf_Internal_Dyn *entry;

  if (dynamic_size == 0) {
    if (do_dynamic)
      printf(_("\nThere is no dynamic section in this file.\n"));

    return TRUE;
  }

  if (is_32bit_elf) {
    if (!get_32bit_dynamic_section(filedata))
      return FALSE;
  } else {
    if (!get_64bit_dynamic_section(filedata))
      return FALSE;
  }

  /* Find the appropriate symbol table.  */
  if (dynamic_symbols == NULL || do_histogram) {
    for (entry = dynamic_section; entry < dynamic_section + dynamic_nent;
         ++entry)
      if (entry->d_tag == DT_SYMTAB)
        dynamic_info[DT_SYMTAB] = entry->d_un.d_val;
      else if (entry->d_tag == DT_SYMENT)
        dynamic_info[DT_SYMENT] = entry->d_un.d_val;
      else if (entry->d_tag == DT_HASH)
        dynamic_info[DT_HASH] = entry->d_un.d_val;
      else if (entry->d_tag == DT_GNU_HASH)
        dynamic_info_DT_GNU_HASH = entry->d_un.d_val;
      else if ((filedata->file_header.e_machine == EM_MIPS ||
                filedata->file_header.e_machine == EM_MIPS_RS3_LE) &&
               entry->d_tag == DT_MIPS_XHASH) {
        dynamic_info_DT_MIPS_XHASH = entry->d_un.d_val;
        dynamic_info_DT_GNU_HASH = entry->d_un.d_val;
      }

    if (dynamic_info[DT_SYMTAB] && dynamic_info[DT_SYMENT]) {
      Elf_Internal_Phdr *seg;
      bfd_vma vma = dynamic_info[DT_SYMTAB];

      if (!get_program_headers(filedata)) {
        error(
            _("Cannot interpret virtual addresses without program headers.\n"));
        return FALSE;
      }

      for (seg = filedata->program_headers;
           seg < filedata->program_headers + filedata->file_header.e_phnum;
           ++seg) {
        unsigned long num_of_syms;

        if (seg->p_type != PT_LOAD)
          continue;

        if ((seg->p_offset + seg->p_filesz) > filedata->file_size) {
          /* See PR 21379 for a reproducer.  */
          error(_("Invalid PT_LOAD entry\n"));
          return FALSE;
        }

        if (vma >= (seg->p_vaddr & -seg->p_align) &&
            vma <= seg->p_vaddr + seg->p_filesz &&
            (num_of_syms = get_num_dynamic_syms(filedata))) {
          /* Since we do not know how big the symbol table is,
             we default to reading in up to the end of PT_LOAD
             segment and processing that.  This is overkill, I
             know, but it should work.  */
          Elf_Internal_Shdr section;
          section.sh_offset = (vma - seg->p_vaddr + seg->p_offset);
          section.sh_size = (num_of_syms * dynamic_info[DT_SYMENT]);
          section.sh_entsize = dynamic_info[DT_SYMENT];
          section.sh_name = filedata->string_table_length;
          dynamic_symbols =
              GET_ELF_SYMBOLS(filedata, &section, &num_dynamic_syms);
          if (dynamic_symbols == NULL || num_dynamic_syms != num_of_syms) {
            error(_("Corrupt DT_SYMTAB dynamic entry\n"));
            return FALSE;
          }
        }
      }
    }
  }

  /* Similarly find a string table.  */
  if (dynamic_strings == NULL)
    for (entry = dynamic_section; entry < dynamic_section + dynamic_nent;
         ++entry) {
      if (entry->d_tag == DT_STRTAB)
        dynamic_info[DT_STRTAB] = entry->d_un.d_val;

      if (entry->d_tag == DT_STRSZ)
        dynamic_info[DT_STRSZ] = entry->d_un.d_val;

      if (dynamic_info[DT_STRTAB] && dynamic_info[DT_STRSZ]) {
        unsigned long offset;
        bfd_size_type str_tab_len = dynamic_info[DT_STRSZ];

        offset =
            offset_from_vma(filedata, dynamic_info[DT_STRTAB], str_tab_len);
        dynamic_strings = (char *)get_data(
            NULL, filedata, offset, 1, str_tab_len, _("dynamic string table"));
        if (dynamic_strings == NULL) {
          error(_("Corrupt DT_STRTAB dynamic entry\n"));
          break;
        }

        dynamic_strings_length = str_tab_len;
        break;
      }
    }

  /* And find the syminfo section if available.  */
  if (dynamic_syminfo == NULL) {
    unsigned long syminsz = 0;

    for (entry = dynamic_section; entry < dynamic_section + dynamic_nent;
         ++entry) {
      if (entry->d_tag == DT_SYMINENT) {
        /* Note: these braces are necessary to avoid a syntax
           error from the SunOS4 C compiler.  */
        /* PR binutils/17531: A corrupt file can trigger this test.
           So do not use an assert, instead generate an error message.  */
        if (sizeof(Elf_External_Syminfo) != entry->d_un.d_val)
          error(_("Bad value (%d) for SYMINENT entry\n"),
                (int)entry->d_un.d_val);
      } else if (entry->d_tag == DT_SYMINSZ)
        syminsz = entry->d_un.d_val;
      else if (entry->d_tag == DT_SYMINFO)
        dynamic_syminfo_offset =
            offset_from_vma(filedata, entry->d_un.d_val, syminsz);
    }

    if (dynamic_syminfo_offset != 0 && syminsz != 0) {
      Elf_External_Syminfo *extsyminfo;
      Elf_External_Syminfo *extsym;
      Elf_Internal_Syminfo *syminfo;

      /* There is a syminfo section.  Read the data.  */
      extsyminfo = (Elf_External_Syminfo *)get_data(
          NULL, filedata, dynamic_syminfo_offset, 1, syminsz,
          _("symbol information"));
      if (!extsyminfo)
        return FALSE;

      if (dynamic_syminfo != NULL) {
        error(_("Multiple dynamic symbol information sections found\n"));
        free(dynamic_syminfo);
      }
      dynamic_syminfo = (Elf_Internal_Syminfo *)malloc(syminsz);
      if (dynamic_syminfo == NULL) {
        error(_("Out of memory allocating %lu byte for dynamic symbol info\n"),
              (unsigned long)syminsz);
        return FALSE;
      }

      dynamic_syminfo_nent = syminsz / sizeof(Elf_External_Syminfo);
      for (syminfo = dynamic_syminfo, extsym = extsyminfo;
           syminfo < dynamic_syminfo + dynamic_syminfo_nent;
           ++syminfo, ++extsym) {
        syminfo->si_boundto = extsym->si_boundto;
        syminfo->si_flags = extsym->si_flags;
      }

      free(extsyminfo);
    }
  }

  if (do_dynamic && dynamic_addr)
    printf(ngettext("\nDynamic section at offset 0x%lx "
                    "contains %lu entry:\n",
                    "\nDynamic section at offset 0x%lx "
                    "contains %lu entries:\n",
                    dynamic_nent),
           dynamic_addr, (unsigned long)dynamic_nent);
  if (do_dynamic)
    printf(_("  Tag        Type                         Name/Value\n"));

  for (entry = dynamic_section; entry < dynamic_section + dynamic_nent;
       entry++) {
    if (do_dynamic) {
      const char *dtype;

      putchar(' ');
      print_vma(entry->d_tag, FULL_HEX);
      dtype = get_dynamic_type(filedata, entry->d_tag);
      printf(" (%s)%*s", dtype, ((is_32bit_elf ? 27 : 19) - (int)strlen(dtype)),
             " ");
    }

    switch (entry->d_tag) {
    case DT_FLAGS:
      if (do_dynamic)
        print_dynamic_flags(entry->d_un.d_val);
      break;

    case DT_AUXILIARY:
    case DT_FILTER:
    case DT_CONFIG:
    case DT_DEPAUDIT:
    case DT_AUDIT:
      if (do_dynamic) {
        switch (entry->d_tag) {
        case DT_AUXILIARY:
          printf(_("Auxiliary library"));
          break;

        case DT_FILTER:
          printf(_("Filter library"));
          break;

        case DT_CONFIG:
          printf(_("Configuration file"));
          break;

        case DT_DEPAUDIT:
          printf(_("Dependency audit library"));
          break;

        case DT_AUDIT:
          printf(_("Audit library"));
          break;
        }

        if (VALID_DYNAMIC_NAME(entry->d_un.d_val))
          printf(": [%s]\n", GET_DYNAMIC_NAME(entry->d_un.d_val));
        else {
          printf(": ");
          print_vma(entry->d_un.d_val, PREFIX_HEX);
          putchar('\n');
        }
      }
      break;

    case DT_FEATURE:
      if (do_dynamic) {
        printf(_("Flags:"));

        if (entry->d_un.d_val == 0)
          printf(_(" None\n"));
        else {
          unsigned long int val = entry->d_un.d_val;

          if (val & DTF_1_PARINIT) {
            printf(" PARINIT");
            val ^= DTF_1_PARINIT;
          }
          if (val & DTF_1_CONFEXP) {
            printf(" CONFEXP");
            val ^= DTF_1_CONFEXP;
          }
          if (val != 0)
            printf(" %lx", val);
          puts("");
        }
      }
      break;

    case DT_POSFLAG_1:
      if (do_dynamic) {
        printf(_("Flags:"));

        if (entry->d_un.d_val == 0)
          printf(_(" None\n"));
        else {
          unsigned long int val = entry->d_un.d_val;

          if (val & DF_P1_LAZYLOAD) {
            printf(" LAZYLOAD");
            val ^= DF_P1_LAZYLOAD;
          }
          if (val & DF_P1_GROUPPERM) {
            printf(" GROUPPERM");
            val ^= DF_P1_GROUPPERM;
          }
          if (val != 0)
            printf(" %lx", val);
          puts("");
        }
      }
      break;

    case DT_FLAGS_1:
      if (do_dynamic) {
        printf(_("Flags:"));
        if (entry->d_un.d_val == 0)
          printf(_(" None\n"));
        else {
          unsigned long int val = entry->d_un.d_val;

          if (val & DF_1_NOW) {
            printf(" NOW");
            val ^= DF_1_NOW;
          }
          if (val & DF_1_GLOBAL) {
            printf(" GLOBAL");
            val ^= DF_1_GLOBAL;
          }
          if (val & DF_1_GROUP) {
            printf(" GROUP");
            val ^= DF_1_GROUP;
          }
          if (val & DF_1_NODELETE) {
            printf(" NODELETE");
            val ^= DF_1_NODELETE;
          }
          if (val & DF_1_LOADFLTR) {
            printf(" LOADFLTR");
            val ^= DF_1_LOADFLTR;
          }
          if (val & DF_1_INITFIRST) {
            printf(" INITFIRST");
            val ^= DF_1_INITFIRST;
          }
          if (val & DF_1_NOOPEN) {
            printf(" NOOPEN");
            val ^= DF_1_NOOPEN;
          }
          if (val & DF_1_ORIGIN) {
            printf(" ORIGIN");
            val ^= DF_1_ORIGIN;
          }
          if (val & DF_1_DIRECT) {
            printf(" DIRECT");
            val ^= DF_1_DIRECT;
          }
          if (val & DF_1_TRANS) {
            printf(" TRANS");
            val ^= DF_1_TRANS;
          }
          if (val & DF_1_INTERPOSE) {
            printf(" INTERPOSE");
            val ^= DF_1_INTERPOSE;
          }
          if (val & DF_1_NODEFLIB) {
            printf(" NODEFLIB");
            val ^= DF_1_NODEFLIB;
          }
          if (val & DF_1_NODUMP) {
            printf(" NODUMP");
            val ^= DF_1_NODUMP;
          }
          if (val & DF_1_CONFALT) {
            printf(" CONFALT");
            val ^= DF_1_CONFALT;
          }
          if (val & DF_1_ENDFILTEE) {
            printf(" ENDFILTEE");
            val ^= DF_1_ENDFILTEE;
          }
          if (val & DF_1_DISPRELDNE) {
            printf(" DISPRELDNE");
            val ^= DF_1_DISPRELDNE;
          }
          if (val & DF_1_DISPRELPND) {
            printf(" DISPRELPND");
            val ^= DF_1_DISPRELPND;
          }
          if (val & DF_1_NODIRECT) {
            printf(" NODIRECT");
            val ^= DF_1_NODIRECT;
          }
          if (val & DF_1_IGNMULDEF) {
            printf(" IGNMULDEF");
            val ^= DF_1_IGNMULDEF;
          }
          if (val & DF_1_NOKSYMS) {
            printf(" NOKSYMS");
            val ^= DF_1_NOKSYMS;
          }
          if (val & DF_1_NOHDR) {
            printf(" NOHDR");
            val ^= DF_1_NOHDR;
          }
          if (val & DF_1_EDITED) {
            printf(" EDITED");
            val ^= DF_1_EDITED;
          }
          if (val & DF_1_NORELOC) {
            printf(" NORELOC");
            val ^= DF_1_NORELOC;
          }
          if (val & DF_1_SYMINTPOSE) {
            printf(" SYMINTPOSE");
            val ^= DF_1_SYMINTPOSE;
          }
          if (val & DF_1_GLOBAUDIT) {
            printf(" GLOBAUDIT");
            val ^= DF_1_GLOBAUDIT;
          }
          if (val & DF_1_SINGLETON) {
            printf(" SINGLETON");
            val ^= DF_1_SINGLETON;
          }
          if (val & DF_1_STUB) {
            printf(" STUB");
            val ^= DF_1_STUB;
          }
          if (val & DF_1_PIE) {
            printf(" PIE");
            val ^= DF_1_PIE;
          }
          if (val & DF_1_KMOD) {
            printf(" KMOD");
            val ^= DF_1_KMOD;
          }
          if (val & DF_1_WEAKFILTER) {
            printf(" WEAKFILTER");
            val ^= DF_1_WEAKFILTER;
          }
          if (val & DF_1_NOCOMMON) {
            printf(" NOCOMMON");
            val ^= DF_1_NOCOMMON;
          }
          if (val != 0)
            printf(" %lx", val);
          puts("");
        }
      }
      break;

    case DT_PLTREL:
      dynamic_info[entry->d_tag] = entry->d_un.d_val;
      if (do_dynamic)
        puts(get_dynamic_type(filedata, entry->d_un.d_val));
      break;

    case DT_NULL:
    case DT_NEEDED:
    case DT_PLTGOT:
    case DT_HASH:
    case DT_STRTAB:
    case DT_SYMTAB:
    case DT_RELA:
    case DT_INIT:
    case DT_FINI:
    case DT_SONAME:
    case DT_RPATH:
    case DT_SYMBOLIC:
    case DT_REL:
    case DT_DEBUG:
    case DT_TEXTREL:
    case DT_JMPREL:
    case DT_RUNPATH:
      dynamic_info[entry->d_tag] = entry->d_un.d_val;

      if (do_dynamic) {
        char *name;

        if (VALID_DYNAMIC_NAME(entry->d_un.d_val))
          name = GET_DYNAMIC_NAME(entry->d_un.d_val);
        else
          name = NULL;

        if (name) {
          switch (entry->d_tag) {
          case DT_NEEDED:
            printf(_("Shared library: [%s]"), name);

            if (streq(name, program_interpreter))
              printf(_(" program interpreter"));
            break;

          case DT_SONAME:
            printf(_("Library soname: [%s]"), name);
            break;

          case DT_RPATH:
            printf(_("Library rpath: [%s]"), name);
            break;

          case DT_RUNPATH:
            printf(_("Library runpath: [%s]"), name);
            break;

          default:
            print_vma(entry->d_un.d_val, PREFIX_HEX);
            break;
          }
        } else
          print_vma(entry->d_un.d_val, PREFIX_HEX);

        putchar('\n');
      }
      break;

    case DT_PLTRELSZ:
    case DT_RELASZ:
    case DT_STRSZ:
    case DT_RELSZ:
    case DT_RELAENT:
    case DT_SYMENT:
    case DT_RELENT:
      dynamic_info[entry->d_tag] = entry->d_un.d_val;
      /* Fall through.  */
    case DT_PLTPADSZ:
    case DT_MOVEENT:
    case DT_MOVESZ:
    case DT_INIT_ARRAYSZ:
    case DT_FINI_ARRAYSZ:
    case DT_GNU_CONFLICTSZ:
    case DT_GNU_LIBLISTSZ:
      if (do_dynamic) {
        print_vma(entry->d_un.d_val, UNSIGNED);
        printf(_(" (bytes)\n"));
      }
      break;

    case DT_VERDEFNUM:
    case DT_VERNEEDNUM:
    case DT_RELACOUNT:
    case DT_RELCOUNT:
      if (do_dynamic) {
        print_vma(entry->d_un.d_val, UNSIGNED);
        putchar('\n');
      }
      break;

    case DT_SYMINSZ:
    case DT_SYMINENT:
    case DT_SYMINFO:
    case DT_USED:
    case DT_INIT_ARRAY:
    case DT_FINI_ARRAY:
      if (do_dynamic) {
        if (entry->d_tag == DT_USED && VALID_DYNAMIC_NAME(entry->d_un.d_val)) {
          char *name = GET_DYNAMIC_NAME(entry->d_un.d_val);

          if (*name) {
            printf(_("Not needed object: [%s]\n"), name);
            break;
          }
        }

        print_vma(entry->d_un.d_val, PREFIX_HEX);
        putchar('\n');
      }
      break;

    case DT_BIND_NOW:
      /* The value of this entry is ignored.  */
      if (do_dynamic)
        putchar('\n');
      break;

    case DT_GNU_PRELINKED:
      if (do_dynamic) {
        struct tm *tmp;
        time_t atime = entry->d_un.d_val;

        tmp = gmtime(&atime);
        /* PR 17533 file: 041-1244816-0.004.  */
        if (tmp == NULL)
          printf(_("<corrupt time val: %lx"), (unsigned long)atime);
        else
          printf("%04u-%02u-%02uT%02u:%02u:%02u\n", tmp->tm_year + 1900,
                 tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min,
                 tmp->tm_sec);
      }
      break;

    case DT_GNU_HASH:
      dynamic_info_DT_GNU_HASH = entry->d_un.d_val;
      if (do_dynamic) {
        print_vma(entry->d_un.d_val, PREFIX_HEX);
        putchar('\n');
      }
      break;

    default:
      if ((entry->d_tag >= DT_VERSYM) && (entry->d_tag <= DT_VERNEEDNUM))
        version_info[DT_VERSIONTAGIDX(entry->d_tag)] = entry->d_un.d_val;

      if (do_dynamic) {
        switch (filedata->file_header.e_machine) {
        case EM_AARCH64:
          dynamic_section_aarch64_val(entry);
          break;
        case EM_MIPS:
        case EM_MIPS_RS3_LE:
          dynamic_section_mips_val(entry);
          break;
        case EM_PARISC:
          dynamic_section_parisc_val(entry);
          break;
        case EM_IA_64:
          dynamic_section_ia64_val(entry);
          break;
        default:
          print_vma(entry->d_un.d_val, PREFIX_HEX);
          putchar('\n');
        }
      }
      break;
    }
  }

  return TRUE;
}

static bfd_boolean process_object(Filedata *filedata) {
  bfd_boolean have_separate_files;
  unsigned int i;
  bfd_boolean res = TRUE;

  if (!get_file_header(filedata)) {
    error(_("%s: Failed to read file header\n"), filedata->file_name);
    return FALSE;
  }

  /* Initialise per file variables.  */
  for (i = ARRAY_SIZE(version_info); i--;)
    version_info[i] = 0;

  for (i = ARRAY_SIZE(dynamic_info); i--;)
    dynamic_info[i] = 0;
  dynamic_info_DT_GNU_HASH = 0;
  dynamic_info_DT_MIPS_XHASH = 0;

  /* Process the file.  */
  if (show_name)
    printf(_("\nFile: %s\n"), filedata->file_name);

  /* Initialise the dump_sects array from the cmdline_dump_sects array.
     Note we do this even if cmdline_dump_sects is empty because we
     must make sure that the dump_sets array is zeroed out before each
     object file is processed.  */
  if (filedata->num_dump_sects > cmdline.num_dump_sects)
    memset(filedata->dump_sects, 0,
           filedata->num_dump_sects * sizeof(*filedata->dump_sects));

  if (cmdline.num_dump_sects > 0) {
    if (filedata->num_dump_sects == 0)
      /* A sneaky way of allocating the dump_sects array.  */
      request_dump_bynumber(filedata, cmdline.num_dump_sects, 0);

    assert(filedata->num_dump_sects >= cmdline.num_dump_sects);
    memcpy(filedata->dump_sects, cmdline.dump_sects,
           cmdline.num_dump_sects * sizeof(*filedata->dump_sects));
  }

  if (!process_file_header(filedata))
    return FALSE;

  if (!process_section_headers(filedata)) {
    /* Without loaded section headers we cannot process lots of things.  */
    do_unwind = do_version = do_dump = do_arch = FALSE;

    if (!do_using_dynamic)
      do_syms = do_dyn_syms = do_reloc = FALSE;
  }

  if (!process_section_groups(filedata))
    /* Without loaded section groups we cannot process unwind.  */
    do_unwind = FALSE;

  if (process_program_headers(filedata))
    process_dynamic_section(filedata);
  else
    res = FALSE;

  if (!process_relocs(filedata))
    res = FALSE;

  if (!process_unwind(filedata))
    res = FALSE;

  if (!process_symbol_table(filedata))
    res = FALSE;

  if (!process_syminfo(filedata))
    res = FALSE;

  if (!process_version_sections(filedata))
    res = FALSE;

  if (filedata->file_header.e_shstrndx != SHN_UNDEF)
    have_separate_files =
        load_separate_debug_files(filedata, filedata->file_name);
  else
    have_separate_files = FALSE;

  if (!process_section_contents(filedata))
    res = FALSE;

  if (have_separate_files) {
    separate_info *d;

    for (d = first_separate_info; d != NULL; d = d->next) {
      if (!process_section_headers(d->handle))
        res = FALSE;
      else if (!process_section_contents(d->handle))
        res = FALSE;
    }

    /* The file handles are closed by the call to free_debug_memory() below.  */
  }

  if (!process_notes(filedata))
    res = FALSE;

  if (!process_gnu_liblist(filedata))
    res = FALSE;

  if (!process_arch_specific(filedata))
    res = FALSE;

  free(filedata->program_headers);
  filedata->program_headers = NULL;

  free(filedata->section_headers);
  filedata->section_headers = NULL;

  free(filedata->string_table);
  filedata->string_table = NULL;
  filedata->string_table_length = 0;

  if (filedata->dump_sects != NULL) {
    free(filedata->dump_sects);
    filedata->dump_sects = NULL;
    filedata->num_dump_sects = 0;
  }

  if (dynamic_strings) {
    free(dynamic_strings);
    dynamic_strings = NULL;
    dynamic_strings_length = 0;
  }

  if (dynamic_symbols) {
    free(dynamic_symbols);
    dynamic_symbols = NULL;
    num_dynamic_syms = 0;
  }

  if (dynamic_syminfo) {
    free(dynamic_syminfo);
    dynamic_syminfo = NULL;
  }

  if (dynamic_section) {
    free(dynamic_section);
    dynamic_section = NULL;
  }

  while (symtab_shndx_list != NULL) {
    elf_section_list *next = symtab_shndx_list->next;
    free(symtab_shndx_list);
    symtab_shndx_list = next;
  }

  if (section_headers_groups) {
    free(section_headers_groups);
    section_headers_groups = NULL;
  }

  if (section_groups) {
    struct group_list *g;
    struct group_list *next;

    for (i = 0; i < group_count; i++) {
      for (g = section_groups[i].root; g != NULL; g = next) {
        next = g->next;
        free(g);
      }
    }

    free(section_groups);
    section_groups = NULL;
  }

  free_debug_memory();

  return res;
}

static bfd_boolean process_symbol_table(Filedata *filedata) {
  Elf_Internal_Shdr *section;

  if (!do_syms && !do_dyn_syms && !do_histogram)
    return TRUE;

  if ((dynamic_info[DT_HASH] || dynamic_info_DT_GNU_HASH) && do_syms &&
      do_using_dynamic && dynamic_strings != NULL && dynamic_symbols != NULL) {
    unsigned long si;

    printf(ngettext("\nSymbol table for image contains %lu entry:\n",
                    "\nSymbol table for image contains %lu entries:\n",
                    num_dynamic_syms),
           num_dynamic_syms);
    if (is_32bit_elf)
      printf(_("   Num:    Value  Size Type    Bind   Vis      Ndx Name\n"));
    else
      printf(_(
          "   Num:    Value          Size Type    Bind   Vis      Ndx Name\n"));

    for (si = 0; si < num_dynamic_syms; si++)
      print_dynamic_symbol(filedata, si, dynamic_symbols, NULL, dynamic_strings,
                           dynamic_strings_length);
  } else if ((do_dyn_syms || (do_syms && !do_using_dynamic)) &&
             filedata->section_headers != NULL) {
    unsigned int i;

    for (i = 0, section = filedata->section_headers;
         i < filedata->file_header.e_shnum; i++, section++) {
      char *strtab = NULL;
      unsigned long int strtab_size = 0;
      Elf_Internal_Sym *symtab;
      unsigned long si, num_syms;

      if ((section->sh_type != SHT_SYMTAB && section->sh_type != SHT_DYNSYM) ||
          (!do_syms && section->sh_type == SHT_SYMTAB))
        continue;

      if (section->sh_entsize == 0) {
        printf(_("\nSymbol table '%s' has a sh_entsize of zero!\n"),
               printable_section_name(filedata, section));
        continue;
      }

      num_syms = section->sh_size / section->sh_entsize;
      printf(ngettext("\nSymbol table '%s' contains %lu entry:\n",
                      "\nSymbol table '%s' contains %lu entries:\n", num_syms),
             printable_section_name(filedata, section), num_syms);

      if (is_32bit_elf)
        printf(_("   Num:    Value  Size Type    Bind   Vis      Ndx Name\n"));
      else
        printf(_("   Num:    Value          Size Type    Bind   Vis      Ndx "
                 "Name\n"));

      symtab = GET_ELF_SYMBOLS(filedata, section, &num_syms);
      if (symtab == NULL)
        continue;

      if (section->sh_link == filedata->file_header.e_shstrndx) {
        strtab = filedata->string_table;
        strtab_size = filedata->string_table_length;
      } else if (section->sh_link < filedata->file_header.e_shnum) {
        Elf_Internal_Shdr *string_sec;

        string_sec = filedata->section_headers + section->sh_link;

        strtab = (char *)get_data(NULL, filedata, string_sec->sh_offset, 1,
                                  string_sec->sh_size, _("string table"));
        strtab_size = strtab != NULL ? string_sec->sh_size : 0;
      }

      for (si = 0; si < num_syms; si++)
        print_dynamic_symbol(filedata, si, symtab, section, strtab,
                             strtab_size);

      free(symtab);
      if (strtab != filedata->string_table)
        free(strtab);
    }
  } else if (do_syms)
    printf(_("\nDynamic symbol information is not available for displaying "
             "symbols.\n"));

  if (do_histogram && buckets != NULL) {
    unsigned long *lengths;
    unsigned long *counts;
    unsigned long hn;
    bfd_vma si;
    unsigned long maxlength = 0;
    unsigned long nzero_counts = 0;
    unsigned long nsyms = 0;
    char *visited;

    printf(ngettext("\nHistogram for bucket list length "
                    "(total of %lu bucket):\n",
                    "\nHistogram for bucket list length "
                    "(total of %lu buckets):\n",
                    (unsigned long)nbuckets),
           (unsigned long)nbuckets);

    lengths = (unsigned long *)calloc(nbuckets, sizeof(*lengths));
    if (lengths == NULL) {
      error(_("Out of memory allocating space for histogram buckets\n"));
      goto err_out;
    }
    visited = xcmalloc(nchains, 1);
    memset(visited, 0, nchains);

    printf(_(" Length  Number     %% of total  Coverage\n"));
    for (hn = 0; hn < nbuckets; ++hn) {
      for (si = buckets[hn]; si > 0; si = chains[si]) {
        ++nsyms;
        if (maxlength < ++lengths[hn])
          ++maxlength;
        if (si >= nchains || visited[si]) {
          error(_("histogram chain is corrupt\n"));
          break;
        }
        visited[si] = 1;
      }
    }
    free(visited);

    counts = (unsigned long *)calloc(maxlength + 1, sizeof(*counts));
    if (counts == NULL) {
      free(lengths);
      error(_("Out of memory allocating space for histogram counts\n"));
      goto err_out;
    }

    for (hn = 0; hn < nbuckets; ++hn)
      ++counts[lengths[hn]];

    if (nbuckets > 0) {
      unsigned long i;
      printf("      0  %-10lu (%5.1f%%)\n", counts[0],
             (counts[0] * 100.0) / nbuckets);
      for (i = 1; i <= maxlength; ++i) {
        nzero_counts += counts[i] * i;
        printf("%7lu  %-10lu (%5.1f%%)    %5.1f%%\n", i, counts[i],
               (counts[i] * 100.0) / nbuckets, (nzero_counts * 100.0) / nsyms);
      }
    }

    free(counts);
    free(lengths);
  }

  free(buckets);
  buckets = NULL;
  
  free(chains);
  chains = NULL;

  if (do_histogram && gnubuckets != NULL) {
    unsigned long *lengths;
    unsigned long *counts;
    unsigned long hn;
    unsigned long maxlength = 0;
    unsigned long nzero_counts = 0;
    unsigned long nsyms = 0;

    printf(ngettext("\nHistogram for `%s' bucket list length "
                    "(total of %lu bucket):\n",
                    "\nHistogram for `%s' bucket list length "
                    "(total of %lu buckets):\n",
                    (unsigned long)ngnubuckets),
           GNU_HASH_SECTION_NAME, (unsigned long)ngnubuckets);

    lengths = (unsigned long *)calloc(ngnubuckets, sizeof(*lengths));
    if (lengths == NULL) {
      error(_("Out of memory allocating space for gnu histogram buckets\n"));
      goto err_out;
    }

    printf(_(" Length  Number     %% of total  Coverage\n"));

    for (hn = 0; hn < ngnubuckets; ++hn)
      if (gnubuckets[hn] != 0) {
        bfd_vma off, length = 1;

        for (off = gnubuckets[hn] - gnusymidx;
             /* PR 17531 file: 010-77222-0.004.  */
             off < ngnuchains && (gnuchains[off] & 1) == 0; ++off)
          ++length;
        lengths[hn] = length;
        if (length > maxlength)
          maxlength = length;
        nsyms += length;
      }

    counts = (unsigned long *)calloc(maxlength + 1, sizeof(*counts));
    if (counts == NULL) {
      free(lengths);
      error(_("Out of memory allocating space for gnu histogram counts\n"));
      goto err_out;
    }

    for (hn = 0; hn < ngnubuckets; ++hn)
      ++counts[lengths[hn]];

    if (ngnubuckets > 0) {
      unsigned long j;
      printf("      0  %-10lu (%5.1f%%)\n", counts[0],
             (counts[0] * 100.0) / ngnubuckets);
      for (j = 1; j <= maxlength; ++j) {
        nzero_counts += counts[j] * j;
        printf("%7lu  %-10lu (%5.1f%%)    %5.1f%%\n", j, counts[j],
               (counts[j] * 100.0) / ngnubuckets,
               (nzero_counts * 100.0) / nsyms);
      }
    }

    free(counts);
    free(lengths);
  }
  free(gnubuckets);
  free(gnuchains);
  free(mipsxlat);
  return TRUE;

err_out:
  free(gnubuckets);
  free(gnuchains);
  free(mipsxlat);
  free(buckets);
  free(chains);
  return FALSE;
}
