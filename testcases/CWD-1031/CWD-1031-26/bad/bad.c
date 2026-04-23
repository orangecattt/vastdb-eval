/* === DEPENDENCIES === */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

/* ATTRIBUTE_UNUSED macro */
#ifndef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED __attribute__((unused))
#endif

/* Boolean type */
typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

/* bfd_vma type */
typedef unsigned long bfd_vma;
typedef long bfd_signed_vma;

/* bfd_size_type */
typedef unsigned long bfd_size_type;

/* file_ptr and ufile_ptr */
typedef long file_ptr;
typedef unsigned long ufile_ptr;

/* flagword */
typedef unsigned int flagword;

/* bfd_byte */
typedef unsigned char bfd_byte;

/* bfd_format enum */
typedef enum bfd_format
{
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

/* bfd_direction enum */
enum bfd_direction
{
  no_direction = 0,
  read_direction = 1,
  write_direction = 2,
  both_direction = 3
};

/* bfd_error_type enum */
typedef enum bfd_error
{
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

/* bfd_plugin_format enum */
enum bfd_plugin_format
{
  bfd_plugin_unknown = 0,
  bfd_plugin_yes = 1,
  bfd_plugin_no = 2
};

/* bfd_endian enum */
enum bfd_endian { BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE, BFD_ENDIAN_UNKNOWN };

/* bfd_flavour enum */
enum bfd_flavour
{
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
  bfd_target_elf64_flavour,
  bfd_target_wasm_flavour,
  bfd_target_pef_flavour,
  bfd_target_pef_xlib_flavour,
  bfd_target_sym_flavour
};

/* ENUM_BITFIELD macro */
#ifndef ENUM_BITFIELD
#define ENUM_BITFIELD(x) enum x
#endif

/* Forward declarations */
typedef struct bfd bfd;
typedef struct bfd_target bfd_target;
typedef struct bfd_section asection;
typedef struct bfd_symbol asymbol;
typedef struct bfd_arch_info bfd_arch_info;
typedef struct bfd_link_hash_table bfd_link_hash_table;
typedef struct relax_table relax_table;
typedef struct reloc_cache_entry reloc_cache_entry;
typedef struct bfd_comdat_info bfd_comdat_info;

/* bfd_hash_entry struct */
struct bfd_hash_entry
{
  struct bfd_hash_entry *next;
  const char *string;
};

/* bfd_hash_table struct */
struct bfd_hash_table
{
  struct bfd_hash_entry **table;
  unsigned int size;
  unsigned int count;
  unsigned int entsize;
};

/* bfd_section struct */
typedef struct bfd_section
{
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
  unsigned int sec_info_type:3;
  unsigned int use_rela_p:1;
  unsigned int sec_flg0:1;
  unsigned int sec_flg1:1;
  unsigned int sec_flg2:1;
  unsigned int sec_flg3:1;
  unsigned int sec_flg4:1;
  unsigned int sec_flg5:1;
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
  void *lineno;
  unsigned lineno_count;
  unsigned long relocation_count;
  union {
    void *p;
    bfd_size_type i;
  } kept_section;
  void *moving_line_filepos;
  void *target_index;
  void *used_by_bfd;
  struct bfd_section *group_sec;
  struct bfd_comdat_info *comdat_info;
} asection;

/* areltdata struct */
struct areltdata
{
  char * arch_header;
  bfd_size_type parsed_size;
  bfd_size_type extra_size;
  char *filename;
  file_ptr origin;
  void *parent_cache;
  file_ptr key;
};

#define arelt_size(bfd) (((struct areltdata *)((bfd)->arelt_data))->parsed_size)

/* bfd_target struct */
typedef struct bfd_target
{
  const char *name;
  enum bfd_flavour flavour;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  flagword object_flags;
  flagword section_flags;
  char symbol_leading_char;
  char ar_pad_char;
  unsigned char ar_max_namelen;
  unsigned char match_priority;
} bfd_target;

/* bfd_iovec struct */
struct bfd_iovec
{
  file_ptr (*bread) (struct bfd *abfd, void *ptr, file_ptr nbytes);
  file_ptr (*bwrite) (struct bfd *abfd, const void *ptr, file_ptr nbytes);
  file_ptr (*btell) (struct bfd *abfd);
  int (*bseek) (struct bfd *abfd, file_ptr offset, int whence);
  int (*bclose) (struct bfd *abfd);
  int (*bflush) (struct bfd *abfd);
  int (*bstat) (struct bfd *abfd, struct stat *sb);
  void *(*bmmap) (struct bfd *abfd, void *addr, bfd_size_type len,
                  int prot, int flags, file_ptr offset,
                  void **map_addr, bfd_size_type *map_len);
};

/* bfd_build_id struct */
struct bfd_build_id
{
  bfd_size_type size;
  bfd_byte data[1];
};

/* bfd struct */
struct bfd
{
  const char *filename;
  const struct bfd_target *xvec;
  void *iostream;
  const struct bfd_iovec *iovec;
  struct bfd *lru_prev, *lru_next;
  ufile_ptr where;
  long mtime;
  unsigned int id;
  ENUM_BITFIELD (bfd_format) format : 3;
  ENUM_BITFIELD (bfd_direction) direction : 2;
  flagword flags;
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
  ENUM_BITFIELD (bfd_plugin_format) plugin_format : 2;
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
  struct bfd_symbol  **outsymbols;
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
};

/* cache_flag enum */
enum cache_flag {
  CACHE_NORMAL = 0,
  CACHE_NO_OPEN = 1,
  CACHE_NO_SEEK = 2,
  CACHE_NO_SEEK_ERROR = 4
};

/* FOPEN_RB */
#define FOPEN_RB "rb"

/* bfd_pef_loader_header */
struct bfd_pef_loader_header
{
  long main_section;
  unsigned long main_offset;
  long init_section;
  unsigned long init_offset;
  long term_section;
  unsigned long term_offset;
  unsigned long imported_library_count;
  unsigned long total_imported_symbol_count;
  unsigned long reloc_section_count;
  unsigned long reloc_instr_offset;
  unsigned long loader_strings_offset;
  unsigned long export_hash_offset;
  unsigned long export_hash_table_power;
  unsigned long exported_symbol_count;
};
typedef struct bfd_pef_loader_header bfd_pef_loader_header;

/* BFD_ASSERT macro */
extern void bfd_assert (const char*, int);
#define BFD_ASSERT(x) \
  do { if (!(x)) bfd_assert(__FILE__,__LINE__); } while (0)

/* Global variables */
static int open_files;
static bfd *bfd_last_cache = NULL;

/* Function declarations */
extern void bfd_set_error (bfd_error_type error_tag);
extern int bfd_seek (bfd *, file_ptr, int);
extern asection *bfd_get_section_by_name (bfd *abfd, const char *name);
extern void *bfd_malloc (bfd_size_type);
extern bfd * _bfd_new_bfd (void);
extern void _bfd_delete_bfd (bfd *abfd);
extern FILE *_bfd_real_fopen (const char *, const char *);
extern char *bfd_strdup (const char *str);
extern const bfd_target *bfd_find_target (const char *target_name, bfd *abfd);
extern int bfd_pef_parse_loader_header (bfd *, unsigned char *, size_t, bfd_pef_loader_header *);

/* bfd_is_thin_archive */
static inline bfd_boolean
bfd_is_thin_archive (const bfd *abfd)
{
  return abfd->is_thin_archive;
}

/* bfd_set_cacheable */
static inline bfd_boolean
bfd_set_cacheable (bfd * abfd, bfd_boolean val)
{
  abfd->cacheable = val;
  return TRUE;
}

/* bfd_cache_max_open */
static int max_open_files = 0;

static int
bfd_cache_max_open (void)
{
  if (max_open_files == 0)
    {
      int max = 10;
      max_open_files = max < 10 ? 10 : max;
    }
  return max_open_files;
}

/* insert function */
static void
insert (bfd *abfd)
{
  if (bfd_last_cache == NULL)
    {
      abfd->lru_next = abfd;
      abfd->lru_prev = abfd;
    }
  else
    {
      abfd->lru_next = bfd_last_cache;
      abfd->lru_prev = bfd_last_cache->lru_prev;
      abfd->lru_prev->lru_next = abfd;
      abfd->lru_next->lru_prev = abfd;
    }
  bfd_last_cache = abfd;
}

/* bfd_cache_lookup_worker */
static FILE *
bfd_cache_lookup_worker (bfd *abfd, enum cache_flag flag)
{
  if (abfd->iostream != NULL)
    {
      if (abfd != bfd_last_cache)
        {
          abfd->lru_next = bfd_last_cache;
          abfd->lru_prev = bfd_last_cache->lru_prev;
          abfd->lru_prev->lru_next = abfd;
          abfd->lru_next->lru_prev = abfd;
          bfd_last_cache = abfd;
        }
      return (FILE *) abfd->iostream;
    }
  return NULL;
}

/* bfd_cache_lookup macro */
#define bfd_cache_lookup(x, flag) \
  ((x) == bfd_last_cache			\
   ? (FILE *) (bfd_last_cache->iostream)	\
   : bfd_cache_lookup_worker (x, flag))

/* cache_bread_1 */
static file_ptr
cache_bread_1 (FILE *f, void *buf, file_ptr nbytes)
{
  file_ptr nread;
  nread = fread (buf, 1, nbytes, f);
  if (nread < nbytes && ferror (f))
    {
      bfd_set_error (bfd_error_system_call);
      return nread;
    }
  if (nread < nbytes)
    bfd_set_error (bfd_error_file_truncated);
  return nread;
}

/* cache_bwrite */
static file_ptr
cache_bwrite (struct bfd *abfd, const void *from, file_ptr nbytes)
{
  file_ptr nwrite;
  FILE *f = bfd_cache_lookup (abfd, CACHE_NORMAL);
  if (f == NULL)
    return 0;
  nwrite = fwrite (from, 1, nbytes, f);
  if (nwrite < nbytes && ferror (f))
    {
      bfd_set_error (bfd_error_system_call);
      return -1;
    }
  return nwrite;
}

/* cache_btell */
static file_ptr
cache_btell (struct bfd *abfd)
{
  FILE *f = bfd_cache_lookup (abfd, CACHE_NORMAL);
  if (f == NULL)
    return -1;
  return ftell (f);
}

/* cache_bseek */
static int
cache_bseek (struct bfd *abfd, file_ptr offset, int whence)
{
  FILE *f = bfd_cache_lookup (abfd, whence != SEEK_CUR ? CACHE_NO_SEEK : CACHE_NORMAL);
  if (f == NULL)
    return -1;
  return fseek (f, offset, whence);
}

/* cache_bclose */
static int
cache_bclose (struct bfd *abfd)
{
  if (abfd->iostream != NULL)
    return fclose ((FILE *) abfd->iostream);
  return 0;
}

/* cache_bflush */
static int
cache_bflush (struct bfd *abfd)
{
  FILE *f = bfd_cache_lookup (abfd, CACHE_NORMAL);
  if (f == NULL)
    return 0;
  return fflush (f);
}

/* cache_bstat */
static int
cache_bstat (struct bfd *abfd, struct stat *sb)
{
  FILE *f = bfd_cache_lookup (abfd, CACHE_NO_SEEK_ERROR);
  if (f == NULL)
    return -1;
  return fstat (fileno (f), sb);
}

/* cache_bmmap */
static void *
cache_bmmap (struct bfd *abfd ATTRIBUTE_UNUSED,
             void *addr ATTRIBUTE_UNUSED,
             bfd_size_type len ATTRIBUTE_UNUSED,
             int prot ATTRIBUTE_UNUSED,
             int flags ATTRIBUTE_UNUSED,
             file_ptr offset ATTRIBUTE_UNUSED,
             void **map_addr ATTRIBUTE_UNUSED,
             bfd_size_type *map_len ATTRIBUTE_UNUSED)
{
  return (void *) -1;
}

/* close_one */
static bfd_boolean
close_one (void)
{
  register bfd *to_kill;
  if (bfd_last_cache == NULL)
    to_kill = NULL;
  else
    {
      for (to_kill = bfd_last_cache->lru_prev;
           ! to_kill->cacheable;
           to_kill = to_kill->lru_prev)
        {
          if (to_kill == bfd_last_cache)
            {
              to_kill = NULL;
              break;
            }
        }
    }
  if (to_kill == NULL)
    return TRUE;
  to_kill->where = ftell ((FILE *) to_kill->iostream);
  if (to_kill->iostream != NULL)
    fclose ((FILE *) to_kill->iostream);
  to_kill->iostream = NULL;
  return TRUE;
}

/* Forward declaration for cache_bread */
static file_ptr cache_bread (struct bfd *abfd, void *buf, file_ptr nbytes);

/* cache_iovec */
static const struct bfd_iovec cache_iovec =
{
  &cache_bread, &cache_bwrite, &cache_btell, &cache_bseek,
  &cache_bclose, &cache_bflush, &cache_bstat, &cache_bmmap
};

/* === ORIGINAL CODE === */

static file_ptr
cache_bread (struct bfd *abfd, void *buf, file_ptr nbytes)
{
  file_ptr nread = 0;
  FILE *f;

  f = bfd_cache_lookup (abfd, CACHE_NORMAL);
  if (f == NULL)
    return -1;

  /* Some filesystems are unable to handle reads that are too large
     (for instance, NetApp shares with oplocks turned off).  To avoid
     hitting this limitation, we read the buffer in chunks of 8MB max.  */
  while (nread < nbytes)
    {
      const file_ptr max_chunk_size = 0x800000;
      file_ptr chunk_size = nbytes - nread;
      file_ptr chunk_nread;

      if (chunk_size > max_chunk_size)
	chunk_size = max_chunk_size;

      chunk_nread = cache_bread_1 (f, (char *) buf + nread, chunk_size);

      /* Update the nread count.

	 We just have to be careful of the case when cache_bread_1 returns
	 a negative count:  If this is our first read, then set nread to
	 that negative count in order to return that negative value to the
	 caller.  Otherwise, don't add it to our total count, or we would
	 end up returning a smaller number of bytes read than we actually
	 did.  */
      if (nread == 0 || chunk_nread > 0)
	nread += chunk_nread;

      if (chunk_nread < chunk_size)
	break;
    }

  return nread;
}

bfd_size_type
bfd_bread (void *ptr, bfd_size_type size, bfd *abfd)
{
  file_ptr nread;
  bfd *element_bfd = abfd;
  ufile_ptr offset = 0;

  while (abfd->my_archive != NULL
	 && !bfd_is_thin_archive (abfd->my_archive))
    {
      offset += abfd->origin;
      abfd = abfd->my_archive;
    }

  /* If this is an archive element, don't read past the end of
     this element.  */
  if (element_bfd->arelt_data != NULL)
    {
      bfd_size_type maxbytes = arelt_size (element_bfd);

      if (abfd->where < offset || abfd->where - offset >= maxbytes)
	{
	  bfd_set_error (bfd_error_invalid_operation);
	  return -1;
	}
      if (abfd->where - offset + size > maxbytes)
	size = maxbytes - (abfd->where - offset);
    }

  if (abfd->iovec == NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  nread = abfd->iovec->bread (abfd, ptr, size);
  if (nread != -1)
    abfd->where += nread;

  return nread;
}

void *
bfd_malloc (bfd_size_type size)
{
  void *ptr;
  size_t sz = (size_t) size;

  if (size != sz
      /* This is to pacify memory checkers like valgrind.  */
      || sz > SSIZE_MAX)
    {
      bfd_set_error (bfd_error_no_memory);
      return NULL;
    }

  ptr = malloc (sz);
  if (ptr == NULL && sz != 0)
    bfd_set_error (bfd_error_no_memory);

  return ptr;
}

int
bfd_pef_scan_start_address (bfd *abfd)
{
  struct bfd_pef_loader_header header;
  asection *section;

  asection *loadersec = NULL;
  unsigned char *loaderbuf = NULL;
  size_t loaderlen = 0;
  int ret;

  loadersec = bfd_get_section_by_name (abfd, "loader");
  if (loadersec == NULL)
    goto end;

  loaderlen = loadersec->size;
  loaderbuf = bfd_malloc (loaderlen);
  if (bfd_seek (abfd, loadersec->filepos, SEEK_SET) < 0)
    goto error;
  if (bfd_bread ((void *) loaderbuf, loaderlen, abfd) != loaderlen)
    goto error;

  if (loaderlen < 56)
    goto error;
  ret = bfd_pef_parse_loader_header (abfd, loaderbuf, 56, &header);
  if (ret < 0)
    goto error;

  if (header.main_section < 0)
    goto end;

  for (section = abfd->sections; section != NULL; section = section->next)
    if ((long) (section->index + 1) == header.main_section)
      break;

  if (section == NULL)
    goto error;

  abfd->start_address = section->vma + header.main_offset;

 end:
  if (loaderbuf != NULL)
    free (loaderbuf);
  return 0;

 error:
  if (loaderbuf != NULL)
    free (loaderbuf);
  return -1;
}

bfd_boolean
bfd_cache_init (bfd *abfd)
{
  BFD_ASSERT (abfd->iostream != NULL);
  if (open_files >= bfd_cache_max_open ())
    {
      if (! close_one ())
	return FALSE;
    }
  abfd->iovec = &cache_iovec;
  insert (abfd);
  ++open_files;
  return TRUE;
}

bfd *
bfd_fopen (const char *filename, const char *target, const char *mode, int fd)
{
  bfd *nbfd;
  const bfd_target *target_vec;

  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    {
      if (fd != -1)
	close (fd);
      return NULL;
    }

  target_vec = bfd_find_target (target, nbfd);
  if (target_vec == NULL)
    {
      if (fd != -1)
	close (fd);
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

#ifdef HAVE_FDOPEN
  if (fd != -1)
    nbfd->iostream = fdopen (fd, mode);
  else
#endif
    nbfd->iostream = _bfd_real_fopen (filename, mode);
  if (nbfd->iostream == NULL)
    {
      bfd_set_error (bfd_error_system_call);
      if (fd != -1)
	close (fd);
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  /* OK, put everything where it belongs.  */

  /* PR 11983: Do not cache the original filename, but
     rather make a copy - the original might go away.  */
  nbfd->filename = bfd_strdup (filename);
  if (nbfd->filename == NULL)
    {
      fclose (nbfd->iostream);
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  /* Figure out whether the user is opening the file for reading,
     writing, or both, by looking at the MODE argument.  */
  if ((mode[0] == 'r' || mode[0] == 'w' || mode[0] == 'a')
      && mode[1] == '+')
    nbfd->direction = both_direction;
  else if (mode[0] == 'r')
    nbfd->direction = read_direction;
  else
    nbfd->direction = write_direction;

  if (!bfd_cache_init (nbfd))
    {
      fclose (nbfd->iostream);
      _bfd_delete_bfd (nbfd);
      return NULL;
    }
  nbfd->opened_once = TRUE;

  /* If we opened the file by name, mark it cacheable; we can close it
     and reopen it later. However, if a file descriptor was provided,
     then it may have been opened with special flags that make it
     unsafe to close and reopen the file.  */
  if (fd == -1)
    (void) bfd_set_cacheable (nbfd, TRUE);

  return nbfd;
}

bfd *
bfd_openr (const char *filename, const char *target)
{
  return bfd_fopen (filename, target, FOPEN_RB, -1);
}

int
test (const char *filename)
{
  bfd *abfd;

  abfd = bfd_openr (filename, NULL);
  if (abfd == NULL)
    return -1;

  return bfd_pef_scan_start_address (abfd);
}
