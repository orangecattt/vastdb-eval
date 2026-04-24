/* === Dependency declarations (must come before original code) === */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Basic type definitions */
typedef void *PTR;
typedef unsigned int hashval_t;
typedef int bfd_boolean;
#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)

/* file_ptr type */
typedef long file_ptr;
typedef unsigned long ufile_ptr;

/* BFD format enum */
typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

/* BFD direction enum */
typedef enum bfd_direction {
  no_direction = 0,
  read_direction = 1,
  write_direction = 2,
  both_direction = 3,
  read_append_direction = 4
} bfd_direction_type;

/* BFD error enum (partial) */
typedef enum bfd_error {
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_invalid_target,
  bfd_error_file_not_recognized,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_invalid_error_code,
  bfd_error_malformed_archive,
  bfd_error_no_more_archived_files
} bfd_error_type;

/* Forward declarations */
typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef struct bfd_hash_entry bfd_hash_entry;
typedef struct bfd_hash_table bfd_hash_table;
typedef struct objalloc objalloc;
typedef struct bfd_target bfd_target;
typedef struct bfd_iovec bfd_iovec;
typedef struct artdata artdata;
typedef struct areltdata areltdata;
typedef struct ar_cache ar_cache;
typedef struct prime_ent prime_ent;

/* Hash table callback types */
typedef int (*htab_trav)(void **, void *);
typedef hashval_t (*htab_hash)(const void *);
typedef int (*htab_eq)(const void *, const void *);
typedef void (*htab_del)(void *);

/* Hash table structure */
struct htab {
  htab_hash hash_f;
  htab_eq eq_f;
  htab_del del_f;
  void **entries;
  size_t size;
  size_t n_elements;
  size_t n_deleted;
  unsigned int searches;
  unsigned int collisions;
  void *alloc_f;
  void *free_f;
  void *alloc_arg;
  void *alloc_with_arg_f;
  void *free_with_arg_f;
  unsigned int size_prime_index;
};

typedef struct htab *htab_t;

/* Hash table insert option */
enum insert_option { NO_INSERT, INSERT };

/* Hash table macros */
#define HTAB_EMPTY_ENTRY ((PTR)0)
#define HTAB_DELETED_ENTRY ((PTR)1)

/* BFD types */
typedef unsigned long bfd_size_type;

/* BFD hash entry */
struct bfd_hash_entry {
  struct bfd_hash_entry *next;
  const char *string;
  unsigned long hash;
};

/* BFD hash table */
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

/* objalloc - opaque */
struct objalloc;

/* areltdata structure */
struct areltdata {
  char *arch_header;
  bfd_size_type parsed_size;
  bfd_size_type extra_size;
  char *filename;
  file_ptr origin;
  void *parent_cache;
  file_ptr key;
};

/* artdata structure */
struct artdata {
  file_ptr first_file_filepos;
  htab_t cache;
  bfd *archive_head;
  void *symdefs;
  long symdef_count;
  char *extended_names;
  bfd_size_type extended_names_size;
  long armap_timestamp;
  file_ptr armap_datepos;
  void *tdata;
};

/* ar_cache structure */
struct ar_cache {
  file_ptr ptr;
  bfd *arbfd;
};

/* BFD iovec structure */
struct bfd_iovec {
  bfd_size_type (*bread)(bfd *, void *, bfd_size_type);
  bfd_size_type (*bwrite)(bfd *, const void *, bfd_size_type);
  file_ptr (*btell)(bfd *);
  int (*bseek)(bfd *, file_ptr, int);
  int (*bclose)(bfd *);
  int (*bflush)(bfd *);
  int (*bstat)(bfd *, struct stat *);
  void *(*bmmap)(bfd *, void *, bfd_size_type, int, file_ptr);
};

/* BFD target vector (partial) */
struct bfd_target {
  const char *name;
  int flavour;
  int byteorder;
  int header_byteorder;
  int object_flags;
  int section_flags;
  char ar_pad_char;
  unsigned short ar_max_namelen;
  void *archive_functions[4];
  void *core_functions[4];
  void *write_functions[4];
  void *link_functions[10];
  void *dynamic_functions[10];
  void *_check_format[4];
  void *_set_format[4];
  void *_close_and_cleanup[4];
  void *_bfd_free_cached_info[4];
  void *_new_section_hook[4];
  void *_get_section_contents[4];
  void *_get_section_contents_in_window[4];
  void *_bfd_copy_private_bfd_data[4];
  void *_bfd_merge_private_bfd_data[4];
  void *_bfd_set_private_flags[4];
  void *_bfd_copy_private_section_data[4];
  void *_bfd_copy_private_symbol_data[4];
  void *_bfd_copy_private_header_data[4];
  void *_bfd_print_private_bfd_data[4];
  void *_bfd_core_file_failing_command[4];
  void *_core_file_failing_signal[4];
  void *_core_file_matches_executable_p[4];
  void *_core_file_pid[4];
  void *_bfd_slurp_armap[4];
  void *_bfd_slurp_extended_name_table[4];
  void *_bfd_construct_extended_name_table[4];
  void *_bfd_truncate_arname[4];
  void *_bfd_write_armap[4];
  void *(*_bfd_read_ar_hdr_fn[4])(bfd *);
  void *_bfd_write_ar_hdr[4];
  void *_bfd_openr_next_archived_file[4];
  void *_bfd_get_elt_at_index[4];
  void *_bfd_stat_arch_elt[4];
  void *_bfd_update_armap_timestamp[4];
  void *_bfd_get_symbol_info[4];
  void *_bfd_is_local_label_name[4];
  void *_bfd_get_lineno[4];
  void *_bfd_find_nearest_line[4];
  void *_bfd_find_line[4];
  void *_bfd_find_inliner_info[4];
  void *_bfd_make_debug_symbol[4];
  void *_bfd_read_minisymbols[4];
  void *_bfd_minisymbol_to_symbol[4];
  void *_bfd_get_relocated_section_contents[4];
  void *_bfd_relax_section[4];
  void *_bfd_gc_sections[4];
  void *_bfd_lookup_section_flags[4];
  void *_bfd_merge_sections[4];
  void *_bfd_is_group_section[4];
  void *_bfd_discard_group[4];
  void *_bfd_link_hash_table_create[4];
  void *_bfd_link_add_symbols[4];
  void *_bfd_link_just_syms[4];
  void *_bfd_copy_link_hash_symbol_type[4];
  void *_bfd_final_link[4];
  void *_bfd_link_split_section[4];
  void *_bfd_section_already_linked[4];
  void *_bfd_define_common_symbol[4];
  void *_bfd_define_start_stop[4];
  void *_bfd_link_check_relocs[4];
  bfd_boolean (*_bfd_write_contents[4])(bfd *);
  void *_bfd_get_dynamic_symtab_upper_bound[4];
  void *_bfd_canonicalize_dynamic_symtab[4];
  void *_bfd_get_synthetic_symtab[4];
  void *_bfd_get_dynamic_reloc_upper_bound[4];
  void *_bfd_canonicalize_dynamic_reloc[4];
  void *_bfd_bfd_is_target_special_symbol[4];
  const char *(*bfd_get_symbol_version_string)(void);
};

/* BFD union for tdata */
union bfd_tdata {
  struct artdata *aout_ar_data;
  void *any;
};

/* BFD link hash structure */
struct bfd_link_hash_entry;
struct bfd_link_hash_table {
  struct bfd_hash_table table;
  struct bfd_link_hash_entry *head;
  unsigned int table_creation_size;
  void (*hash_table_free)(bfd *);
};

/* BFD link structure */
struct bfd_link {
  struct bfd_link_hash_table *hash;
};

/* Main BFD structure (partial) */
struct bfd {
  const char *filename;
  const struct bfd_target *xvec;
  union bfd_tdata tdata;
  void *arelt_data;
  void *memory;
  void *iostream;
  const struct bfd_iovec *iovec;
  int direction;
  int format;
  unsigned int flags;
  int target_defaulted;
  int cacheable;
  int lto_output;
  int no_export;
  int is_thin_archive;
  int has_armap;
  bfd *archive_next;
  bfd *nested_archives;
  bfd *archive_head;
  bfd *my_archive;
  ufile_ptr proxy_origin;
  ufile_ptr origin;
  struct bfd_hash_table section_htab;
  int section_count;
  unsigned long symcount;
  void **outsymbols;
  unsigned int dynsymcount;
  void *usrdata;
  unsigned long start_address;
  struct bfd_link link;
  int is_linker_input;
  void *is_linker_output;
  void *linker_output;
};

/* BFD flag definitions */
#define BFD_COMPRESS 0x4000
#define BFD_DECOMPRESS 0x8000
#define BFD_COMPRESS_GABI 0x20000
#define EXEC_P 0x20
#define DYNAMIC 0x40

/* BFD direction macros */
#define bfd_read_p(abfd) ((abfd)->direction == 1 || (abfd)->direction == 3)
#define bfd_write_p(abfd) ((abfd)->direction == 2 || (abfd)->direction == 3)

/* BFD macros */
#define BFD_SEND(bfd, message, arglist) ((*((bfd)->xvec->message))arglist)
#define bfd_ardata(bfd) ((bfd)->tdata.aout_ar_data)
#define arch_eltdata(bfd) ((struct areltdata *)((bfd)->arelt_data))
#define htab_size(htab) ((htab)->size)
#define arelt_size(bfd) (((struct areltdata *)((bfd)->arelt_data))->parsed_size)
#define bfd_is_thin_archive(abfd) ((abfd)->is_thin_archive)
#define bfd_get_format(abfd) ((abfd)->format)
#define bfd_get_filename(abfd) ((char *)(abfd)->filename)
#define bfd_get_error() bfd_error_no_error
#define _bfd_read_ar_hdr(abfd) BFD_SEND(abfd, _bfd_read_ar_hdr_fn, (abfd))

/* BFD_SEND_FMT macro */
#define BFD_SEND_FMT(bfd, message, arglist)                                    \
  (((bfd)->xvec->message[(int)((bfd)->format)])arglist)

/* BFD assert and abort */
void bfd_assert(const char *, int);
void _bfd_abort(const char *, int, const char *);
#define BFD_ASSERT(x)                                                          \
  do {                                                                         \
    if (!(x))                                                                  \
      bfd_assert(__FILE__, __LINE__);                                          \
  } while (0)
#undef abort
#define abort() _bfd_abort(__FILE__, __LINE__, __PRETTY_FUNCTION__)

/* ATTRIBUTE_UNUSED */
#define ATTRIBUTE_UNUSED __attribute__((__unused__))

/* IS_ABSOLUTE_PATH (Unix) */
#define IS_ABSOLUTE_PATH(f) ((f)[0] == '/')

/* SEEK_SET */
#ifndef SEEK_SET
#define SEEK_SET 0
#endif

/* External variables */
extern int dump_section_contents;
extern int exit_status;
extern const struct bfd_iovec cache_iovec;

/* Prime table for hash functions */
struct prime_ent {
  unsigned long prime;
  unsigned long inv;
  unsigned long inv_m2;
  int shift;
};
extern const struct prime_ent prime_tab[];

/* Hash function helpers */
static hashval_t htab_mod_1(hashval_t x, hashval_t y, hashval_t inv,
                            int shift) {
  hashval_t t1, t2, t3, t4, q, r;
  t1 = ((hashval_t)1 << shift) - y;
  t2 = x - t1;
  t3 = t1 * t2;
  t4 = t3 * inv;
  t4 >>= shift;
  q = t4;
  t1 = q * y;
  t2 = x - t1;
  r = t2;
  return r >= y ? r - y : r;
}

static inline hashval_t htab_mod(hashval_t hash, htab_t htab) {
  const struct prime_ent *p = &prime_tab[htab->size_prime_index];
  return htab_mod_1(hash, p->prime, p->inv, p->shift);
}

static inline hashval_t htab_mod_m2(hashval_t hash, htab_t htab) {
  const struct prime_ent *p = &prime_tab[htab->size_prime_index];
  return 1 + htab_mod_1(hash, p->prime - 2, p->inv_m2, p->shift);
}

/* Hash table function declarations */
extern void **htab_find_slot(htab_t, const void *, enum insert_option);
extern void htab_delete(htab_t);
extern void htab_traverse_noresize(htab_t, htab_trav, void *);
extern void htab_clear_slot(htab_t, void **);

/* BFD function declarations */
extern bfd_boolean bfd_cache_close(bfd *abfd);
extern bfd_boolean bfd_cache_delete(bfd *abfd);
extern void bfd_hash_table_free(struct bfd_hash_table *);
extern bfd_boolean bfd_check_format(bfd *, bfd_format);
extern void bfd_set_error(bfd_error_type);
extern bfd *bfd_openr(const char *, const char *);
extern int bfd_seek(bfd *, file_ptr, int);
extern file_ptr bfd_tell(bfd *);
extern bfd_boolean _bfd_add_bfd_to_archive_cache(bfd *, file_ptr, bfd *);
extern bfd *_bfd_look_for_bfd_in_cache(bfd *, file_ptr);
extern bfd *_bfd_create_empty_archive_element_shell(bfd *);
extern void *_bfd_generic_read_ar_hdr(bfd *);
extern bfd *bfd_generic_openr_next_archived_file(bfd *, bfd *);
extern bfd_boolean _bfd_archive_close_and_cleanup(bfd *);
extern char *xstrdup(const char *);
extern void objalloc_free(struct objalloc *);
extern char *_bfd_append_relative_path(bfd *, char *);

/* Filename comparison */
extern int filename_cmp(const char *s1, const char *s2);

/* binutils common functions */
extern off_t get_file_size(const char *);
extern void fatal(const char *, ...) __attribute__((__noreturn__));
extern void nonfatal(const char *);
extern void display_object_bfd(bfd *abfd);

/* gettext _ macro */
#define _(String) String

/* Static functions from archive.c */
static bfd *open_nested_file(const char *filename, bfd *archive);
static bfd *find_nested_archive(const char *filename, bfd *arch_bfd);

/* Static function from opncls.c */
static inline void _maybe_make_executable(bfd *abfd);

/* open_nested_file implementation */
static bfd *open_nested_file(const char *filename, bfd *archive) {
  const char *target;
  bfd *n_bfd;

  target = NULL;
  if (!archive->target_defaulted)
    target = archive->xvec->name;
  n_bfd = bfd_openr(filename, target);
  if (n_bfd != NULL) {
    n_bfd->lto_output = archive->lto_output;
    n_bfd->no_export = archive->no_export;
    n_bfd->my_archive = archive;
  }
  return n_bfd;
}

/* find_nested_archive implementation */
static bfd *find_nested_archive(const char *filename, bfd *arch_bfd) {
  bfd *abfd;

  if (filename_cmp(filename, arch_bfd->filename) == 0) {
    bfd_set_error(bfd_error_malformed_archive);
    return NULL;
  }

  for (abfd = arch_bfd->nested_archives; abfd != NULL;
       abfd = abfd->archive_next) {
    if (filename_cmp(filename, abfd->filename) == 0)
      return abfd;
  }
  abfd = open_nested_file(filename, arch_bfd);
  if (abfd) {
    abfd->archive_next = arch_bfd->nested_archives;
    arch_bfd->nested_archives = abfd;
  }
  return abfd;
}

/* _maybe_make_executable implementation */
static inline void _maybe_make_executable(bfd *abfd) {
  if (abfd->direction == 2 && (abfd->flags & (0x20 | 0x40)) != 0) {
    struct stat buf;

    if (stat(abfd->filename, &buf) == 0 && (buf.st_mode & 0170000) == 0100000) {
      unsigned int mask = umask(0);
      umask(mask);
      chmod(abfd->filename,
            (0777 & (buf.st_mode | ((0100 | 0010 | 0001) & ~mask))));
    }
  }
}

/* === Original bad.c content === */
#define BFD_SEND(bfd, message, arglist) ((*((bfd)->xvec->message))arglist)
#define bfd_ardata(bfd) ((bfd)->tdata.aout_ar_data)
#define arch_eltdata(bfd) ((struct areltdata *)((bfd)->arelt_data))
#define htab_size(htab) ((htab)->size)

PTR htab_find_with_hash(htab_t htab, const PTR element, hashval_t hash) {
  hashval_t index, hash2;
  size_t size;
  PTR entry;

  htab->searches++;
  size = htab_size(htab);
  index = htab_mod(hash, htab);

  entry = htab->entries[index];
  if (entry == HTAB_EMPTY_ENTRY ||
      (entry != HTAB_DELETED_ENTRY && (*htab->eq_f)(entry, element)))
    return entry;

  hash2 = htab_mod_m2(hash, htab);
  for (;;) {
    htab->collisions++;
    index += hash2;
    if (index >= size)
      index -= size;

    entry = htab->entries[index];
    if (entry == HTAB_EMPTY_ENTRY ||
        (entry != HTAB_DELETED_ENTRY && (*htab->eq_f)(entry, element)))
      return entry;
  }
}

/* Like htab_find_slot_with_hash, but compute the hash value from the
   element.  */

PTR htab_find(htab_t htab, const PTR element) {
  return htab_find_with_hash(htab, element, (*htab->hash_f)(element));
}

void htab_clear_slot(htab_t htab, PTR *slot) {
  if (slot < htab->entries || slot >= htab->entries + htab_size(htab) ||
      *slot == HTAB_EMPTY_ENTRY || *slot == HTAB_DELETED_ENTRY)
    abort();

  if (htab->del_f)
    (*htab->del_f)(*slot);

  *slot = HTAB_DELETED_ENTRY;
  htab->n_deleted++;
}

void _bfd_unlink_from_archive_parent(bfd *abfd) {
  if (arch_eltdata(abfd) != NULL) {
    struct areltdata *ared = arch_eltdata(abfd);
    htab_t htab = (htab_t)ared->parent_cache;

    if (htab) {
      struct ar_cache ent;
      void **slot;

      ent.ptr = ared->key;
      slot = htab_find_slot(htab, &ent, NO_INSERT);
      if (slot != NULL) {
        BFD_ASSERT(((struct ar_cache *)*slot)->arbfd == abfd);
        htab_clear_slot(htab, slot);
      }
    }
  }
}

//% free
static void _bfd_delete_bfd(bfd *abfd) {
  if (abfd->memory) {
    bfd_hash_table_free(&abfd->section_htab);
    objalloc_free((struct objalloc *)abfd->memory);
  }

  if (abfd->filename)
    free((char *)abfd->filename);
  free(abfd->arelt_data);
  free(abfd);
}

bfd_boolean bfd_close(bfd *abfd);

bfd *_bfd_look_for_bfd_in_cache(bfd *arch_bfd, file_ptr filepos) {
  htab_t hash_table = bfd_ardata(arch_bfd)->cache;
  struct ar_cache m;

  m.ptr = filepos;

  if (hash_table) {
    struct ar_cache *entry = (struct ar_cache *)htab_find(hash_table, &m);
    if (!entry)
      return NULL;

    /* Unfortunately this flag is set after checking that we have
       an archive, and checking for an archive means one element has
       sneaked into the cache.  */
    entry->arbfd->no_export = arch_bfd->no_export;
    return entry->arbfd;
  } else
    return NULL;
}

bfd *_bfd_get_elt_at_filepos(bfd *archive, file_ptr filepos) {
  struct areltdata *new_areldata;
  bfd *n_bfd;
  char *filename;

  n_bfd = _bfd_look_for_bfd_in_cache(archive, filepos);
  if (n_bfd)
    return n_bfd;

  if (0 > bfd_seek(archive, filepos, SEEK_SET))
    return NULL;

  if ((new_areldata = (struct areltdata *)_bfd_read_ar_hdr(archive)) == NULL)
    return NULL;

  filename = new_areldata->filename;

  if (bfd_is_thin_archive(archive)) {
    /* This is a proxy entry for an external file.  */
    if (!IS_ABSOLUTE_PATH(filename)) {
      filename = _bfd_append_relative_path(archive, filename);
      if (filename == NULL) {
        free(new_areldata);
        return NULL;
      }
    }

    if (new_areldata->origin > 0) {
      /* This proxy entry refers to an element of a nested archive.
         Locate the member of that archive and return a bfd for it.  */
      bfd *ext_arch = find_nested_archive(filename, archive);

      if (ext_arch == NULL || !bfd_check_format(ext_arch, bfd_archive)) {
        free(new_areldata);
        return NULL;
      }
      n_bfd = _bfd_get_elt_at_filepos(ext_arch, new_areldata->origin);
      if (n_bfd == NULL) {
        free(new_areldata);
        return NULL;
      }
      n_bfd->proxy_origin = bfd_tell(archive);
      return n_bfd;
    }

    /* It's not an element of a nested archive;
       open the external file as a bfd.  */
    n_bfd = open_nested_file(filename, archive);
    if (n_bfd == NULL)
      bfd_set_error(bfd_error_malformed_archive);
  } else {
    n_bfd = _bfd_create_empty_archive_element_shell(archive);
  }

  if (n_bfd == NULL) {
    free(new_areldata);
    return NULL;
  }

  n_bfd->proxy_origin = bfd_tell(archive);

  if (bfd_is_thin_archive(archive)) {
    n_bfd->origin = 0;
  } else {
    n_bfd->origin = n_bfd->proxy_origin;
    n_bfd->filename = xstrdup(filename);
  }

  n_bfd->arelt_data = new_areldata;

  /* Copy BFD_COMPRESS, BFD_DECOMPRESS and BFD_COMPRESS_GABI flags.  */
  n_bfd->flags |=
      archive->flags & (BFD_COMPRESS | BFD_DECOMPRESS | BFD_COMPRESS_GABI);

  /* Copy is_linker_input.  */
  n_bfd->is_linker_input = archive->is_linker_input;

  if (_bfd_add_bfd_to_archive_cache(archive, filepos, n_bfd))
    return n_bfd;

  free(new_areldata);
  n_bfd->arelt_data = NULL;
  return NULL;
}

bfd *bfd_generic_openr_next_archived_file(bfd *archive, bfd *last_file) {
  ufile_ptr filestart;

  if (!last_file)
    filestart = bfd_ardata(archive)->first_file_filepos;
  else {
    filestart = last_file->proxy_origin;
    if (!bfd_is_thin_archive(archive)) {
      bfd_size_type size = arelt_size(last_file);

      filestart += size;
      /* Pad to an even boundary...
         Note that last_file->origin can be odd in the case of
         BSD-4.4-style element with a long odd size.  */
      filestart += filestart % 2;
      if (filestart < last_file->proxy_origin) {
        /* Prevent looping.  See PR19256.  */
        bfd_set_error(bfd_error_malformed_archive);
        return NULL;
      }
    }
  }

  return _bfd_get_elt_at_filepos(archive, filestart);
}

bfd *bfd_openr_next_archived_file(bfd *archive, bfd *last_file) {
  if ((bfd_get_format(archive) != bfd_archive) ||
      (archive->direction == write_direction)) {
    bfd_set_error(bfd_error_invalid_operation);
    return NULL;
  }

  return bfd_generic_openr_next_archived_file(archive, last_file);
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

//% use
bfd_boolean bfd_cache_close(bfd *abfd) {
  if (abfd->iovec != &cache_iovec)
    return TRUE;

  if (abfd->iostream == NULL)
    /* Previously closed.  */
    return TRUE;

  return bfd_cache_delete(abfd);
}

bfd_boolean bfd_close_all_done(bfd *abfd) {
  bfd_boolean ret;

  ret = bfd_cache_close(abfd);

  if (ret)
    _maybe_make_executable(abfd);

  _bfd_delete_bfd(abfd);

  return ret;
}

static int archive_close_worker(void **slot, void *inf ATTRIBUTE_UNUSED) {
  struct ar_cache *ent = (struct ar_cache *)*slot;

  bfd_close_all_done(ent->arbfd);
  return 1;
}

void htab_traverse_noresize(htab_t htab, htab_trav callback, PTR info) {
  PTR *slot;
  PTR *limit;

  slot = htab->entries;
  limit = slot + htab_size(htab);

  do {
    PTR x = *slot;

    if (x != HTAB_EMPTY_ENTRY && x != HTAB_DELETED_ENTRY)
      if (!(*callback)(slot, info))
        break;
  } while (++slot < limit);
}

bfd_boolean _bfd_archive_close_and_cleanup(bfd *abfd) {
  if (bfd_read_p(abfd) && abfd->format == bfd_archive) {
    bfd *nbfd;
    bfd *next;
    htab_t htab;

    /* Close nested archives (if this bfd is a thin archive).  */
    for (nbfd = abfd->nested_archives; nbfd; nbfd = next) {
      next = nbfd->archive_next;
      bfd_close(nbfd);
    }

    htab = bfd_ardata(abfd)->cache;
    if (htab) {
      htab_traverse_noresize(htab, archive_close_worker, NULL);
      htab_delete(htab);
      bfd_ardata(abfd)->cache = NULL;
    }
  }
  _bfd_unlink_from_archive_parent(abfd);
  if (abfd->is_linker_output)
    (*abfd->link.hash->hash_table_free)(abfd);

  return TRUE;
}

bfd_boolean bfd_close(bfd *abfd) {
  bfd_boolean ret;

  if (bfd_write_p(abfd)) {
    if (!BFD_SEND_FMT(abfd, _bfd_write_contents, (abfd)))
      return FALSE;
  }

  if (_bfd_archive_close_and_cleanup(abfd))
    return FALSE;

  ret = abfd->iovec->bclose(abfd) == 0;

  if (ret)
    _maybe_make_executable(abfd);

  _bfd_delete_bfd(abfd);

  return ret;
}

//% caller
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
