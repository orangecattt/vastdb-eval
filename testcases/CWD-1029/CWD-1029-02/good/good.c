#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BFD_HOST_U_64_BIT unsigned long long
#define BFD_HOST_64_BIT long long

#define FALSE 0
#define TRUE 1

#define _(x) (x)

typedef int bfd_boolean;
typedef unsigned long long bfd_vma;
typedef long long bfd_signed_vma;
typedef unsigned long long bfd_size_type;
typedef unsigned long bfd_hostptr_t;
typedef unsigned int flagword;
typedef unsigned char bfd_byte;
typedef long file_ptr;
typedef unsigned long ufile_ptr;

typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef asection *sec_ptr;

typedef struct bfd_symbol asymbol;

enum bfd_direction
  {
    no_direction = 0,
    read_direction = 1,
    write_direction = 2,
    both_direction = 3
  };

enum bfd_format
  {
    bfd_unknown = 0,
    bfd_object,
    bfd_archive,
    bfd_core,
    bfd_type_end
  };

enum bfd_plugin_format
  {
    bfd_plugin_unknown = 0,
    bfd_plugin_yes = 1,
    bfd_plugin_no = 2
  };

struct bfd_build_id
  {
    bfd_size_type size;
    bfd_byte data[1];
  };

struct bfd_iovec;
struct bfd_target;

enum complain_overflow
{
  complain_overflow_dont,
  complain_overflow_bitfield,
  complain_overflow_signed,
  complain_overflow_unsigned
};

typedef enum bfd_reloc_code_real
{
  _dummy_first_bfd_reloc_code_real
} bfd_reloc_code_real_type;

typedef enum bfd_reloc_status
{
  bfd_reloc_ok,
  bfd_reloc_notfound,
  bfd_reloc_overflow,
  bfd_reloc_outofrange,
  bfd_reloc_continue,
  bfd_reloc_notsupported,
  bfd_reloc_other,
  bfd_reloc_undefined,
  bfd_reloc_dangerous
} bfd_reloc_status_type;

struct arelent;

typedef struct reloc_howto_struct
{
  unsigned int type;
  unsigned int size:3;
  unsigned int bitsize:7;
  unsigned int rightshift:6;
  unsigned int bitpos:6;
  enum complain_overflow complain_on_overflow:2;
  unsigned int negate:1;
  unsigned int pc_relative:1;
  unsigned int partial_inplace:1;
  unsigned int pcrel_offset:1;
  bfd_vma src_mask;
  bfd_vma dst_mask;
  bfd_reloc_status_type (*special_function)
    (bfd *, struct arelent *, struct bfd_symbol *, void *, asection *,
     bfd *, char **);
  char *name;
} reloc_howto_type;

typedef struct reloc_cache_entry
{
  struct bfd_symbol **sym_ptr_ptr;
  bfd_size_type address;
  bfd_vma addend;
  reloc_howto_type *howto;
} arelent;

typedef struct reloc_cache_entry arelent_chain;

struct bfd_symbol
{
  const char *name;
  bfd_vma value;
  flagword flags;
  asection *section;
  bfd *the_bfd;
  void *udata;
};

#define bfd_asymbol_name(x) ((x)->name)

struct bfd_section
{
  const char *name;
  int id;
  bfd_size_type size;
  bfd_size_type rawsize;
  bfd_vma vma;
  bfd_vma lma;
  bfd_size_type filepos;
  bfd_size_type rel_filepos;
  bfd_size_type line_filepos;
  bfd_size_type userdata;
  unsigned int alignment_power;
  unsigned long reloc_count;
  unsigned long symbol_count;
  unsigned long lineno_count;
  unsigned long has_lineno_reloc;
  flagword flags;
  bfd_vma output_offset;
  asection *output_section;
  bfd *owner;
  void *used_by_bfd;
  struct bfd_section *next;
  struct bfd_section *prev;
  arelent *relocation;
  arelent **orelocation;
  struct bfd_symbol **symbol_ptr_ptr;
  void *contents;
  struct bfd_section *kept_section;
  bfd_boolean user_set_vma;
  bfd_boolean linker_has_input;
  bfd_boolean gc_mark;
  bfd_boolean sec_info_type;
  unsigned int segment_mark;
  bfd_vma compressed_size;
};

#define bfd_get_section_name(bfd, ptr) ((void) bfd, (ptr)->name)
#define bfd_get_symcount(abfd) ((abfd)->symcount)
#define bfd_get_dynamic_symcount(abfd) ((abfd)->dynsymcount)

#define SEC_RELOC                         0x4
#define SEC_EXCLUDE                       0x40
#define SEC_DEBUGGING                     0x800000
#define EXEC_P                      0x2
#define DYNAMIC                    0x40

#define discarded_section(sec)				\
  (((sec)->flags & SEC_EXCLUDE) != 0			\
   || (sec)->output_section == bfd_abs_section_ptr)

extern asection _bfd_std_section[4];
#define bfd_com_section_ptr (&_bfd_std_section[0])
#define bfd_und_section_ptr (&_bfd_std_section[1])
#define bfd_abs_section_ptr (&_bfd_std_section[2])
#define bfd_ind_section_ptr (&_bfd_std_section[3])

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
  bfd_target_versados_flavour,
  bfd_target_msdos_flavour,
  bfd_target_evax_flavour,
  bfd_target_elf64_flavour
};

enum bfd_endian { BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE, BFD_ENDIAN_UNKNOWN };

struct bfd_target {
  const char *name;
  enum bfd_flavour flavour;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  flagword object_flags;
  flagword section_flags;
  char ar_pad_char;
  unsigned short ar_max_namelen;
  unsigned char match_priority;
  void *backend_data;
};

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
  enum bfd_format format : 3;
  enum bfd_direction direction : 2;
  flagword flags : 20;
  unsigned int cacheable : 1;
  unsigned int target_defaulted : 1;
  unsigned int lru_head : 1;
  unsigned int has_armap : 1;
  unsigned int allow_thin_archives : 1;
  unsigned int usyms : 1;
  unsigned int is_thin_archive : 1;
  unsigned int selective_search : 1;
  unsigned int link_next : 1;
  unsigned int no_export : 1;
  unsigned int lto_output : 1;
  unsigned int plugin_format : 2;
  unsigned int plugin_dummy : 1;
  unsigned int no_pdd : 1;
  unsigned int mtime_set : 1;
  unsigned int symbol_at_eof : 1;
  unsigned int output_has_begun : 1;
  unsigned int is_linker_input : 1;
  unsigned int is_linker_output : 1;
  unsigned int is_linker_output_claimed : 1;
  asection *sections;
  asection *section_last;
  unsigned int section_count;
  unsigned int type;
  struct bfd_section *section_tail;
  asymbol **outsymbols;
  struct bfd *archive_next;
  struct bfd *archive_head;
  struct bfd *nested_archives;
  void *tdata;
  void *usrdata;
  void *memory;
  bfd_size_type symcount;
  bfd_size_type dynsymcount;
  struct bfd_build_id *build_id;
};

typedef enum bfd_error_type
{
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_invalid_target,
  bfd_error_wrong_format,
  bfd_error_wrong_object_format,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_on_input,
  bfd_error_malformed_archive,
  bfd_error_missing_dso,
  bfd_error_invalid_error_code
} bfd_error_type;

extern void bfd_set_error (bfd_error_type error_tag);

extern void _bfd_error_handler (const char *fmt, ...);

extern void *bfd_malloc (bfd_size_type size);
extern void *bfd_alloc (bfd *abfd, bfd_size_type wanted);
extern bfd_size_type bfd_bread (void *ptr, bfd_size_type size, bfd *abfd);
extern int bfd_seek (bfd *abfd, file_ptr pos, int direction);
extern bfd_boolean bfd_get_full_section_contents
  (bfd *abfd, asection *section, bfd_byte **ptr);
extern long bfd_get_reloc_upper_bound (bfd *abfd, asection *sect);
extern long bfd_canonicalize_reloc
  (bfd *abfd, asection *sect, arelent **location, asymbol **symbols);
extern unsigned int bfd_octets_per_byte (bfd *abfd);

extern bfd_reloc_status_type bfd_perform_relocation
  (bfd *abfd, arelent *reloc_entry, void *data, asection *input_section,
   bfd *output_bfd, char **error_message);

#define H_GET_64  bfd_h_get_64
#define H_GET_32  bfd_h_get_32
#define H_GET_S64 bfd_h_get_signed_64
#define H_GET_S32 bfd_h_get_signed_32

#ifdef BFD64
#define H_GET_WORD		H_GET_64
#define H_GET_SIGNED_WORD	H_GET_S64
#else
#define H_GET_WORD		H_GET_32
#define H_GET_SIGNED_WORD	H_GET_S32
#endif

extern bfd_vma bfd_h_get_64 (bfd *abfd, const void *p);
extern bfd_vma bfd_h_get_32 (bfd *abfd, const void *p);
extern bfd_signed_vma bfd_h_get_signed_64 (bfd *abfd, const void *p);
extern bfd_signed_vma bfd_h_get_signed_32 (bfd *abfd, const void *p);

#define BFD_ASSERT(x) \
  do { if (!(x)) bfd_assert (__FILE__, __LINE__); } while (0)
extern void bfd_assert (const char *file, int line);

typedef struct elf_internal_shdr {
  unsigned int	sh_name;
  unsigned int	sh_type;
  bfd_vma	sh_flags;
  bfd_vma	sh_addr;
  file_ptr	sh_offset;
  bfd_size_type	sh_size;
  unsigned int	sh_link;
  unsigned int	sh_info;
  bfd_vma	sh_addralign;
  bfd_size_type	sh_entsize;
  asection *	bfd_section;
  unsigned char *contents;
} Elf_Internal_Shdr;

typedef struct elf_internal_rela {
  bfd_vma	r_offset;
  bfd_vma	r_info;
  bfd_vma	r_addend;
} Elf_Internal_Rela;

typedef struct {
  unsigned char r_offset[4];
  unsigned char	r_info[4];
} Elf32_External_Rel;

typedef struct {
  unsigned char r_offset[4];
  unsigned char	r_info[4];
  unsigned char	r_addend[4];
} Elf32_External_Rela;

typedef struct {
  unsigned char r_offset[8];
  unsigned char	r_info[8];
} Elf64_External_Rel;

typedef struct {
  unsigned char r_offset[8];
  unsigned char	r_info[8];
  unsigned char	r_addend[8];
} Elf64_External_Rela;

#ifdef BFD64
#define Elf_External_Rel	Elf64_External_Rel
#define Elf_External_Rela	Elf64_External_Rela
#else
#define Elf_External_Rel	Elf32_External_Rel
#define Elf_External_Rela	Elf32_External_Rela
#endif

#define NUM_SHDR_ENTRIES(shdr) ((shdr)->sh_entsize > 0 ? (shdr)->sh_size / (shdr)->sh_entsize : 0)

#define ELF64_R_SYM(val) ((val) >> 32)
#define ELF32_R_SYM(val) ((val) >> 8)

#ifdef BFD64
#define ELF_R_SYM(X)	ELF64_R_SYM(X)
#else
#define ELF_R_SYM(X)	ELF32_R_SYM(X)
#endif

#define STN_UNDEF	0

struct bfd_elf_section_reloc_data
{
  Elf_Internal_Shdr *hdr;
  unsigned int count;
  int idx;
  void **hashes;
};

struct bfd_elf_section_data
{
  Elf_Internal_Shdr this_hdr;
  void *section_flag_info;
  struct bfd_elf_section_reloc_data rel, rela;
  int this_idx;
  int dynindx;
  asection *linked_to;
  Elf_Internal_Rela *relocs;
  void *local_dynrel;
  asection *sreloc;
  union {
    const char *name;
    struct bfd_symbol *id;
  } group;
  asection *sec_group;
  asection *next_in_group;
  void *fde_list;
  asection *eh_frame_entry;
  void *sec_info;
};

#define elf_section_data(sec) ((struct bfd_elf_section_data*)(sec)->used_by_bfd)

struct elf_size_info {
  unsigned char sizeof_ehdr, sizeof_phdr, sizeof_shdr;
  unsigned char sizeof_rel, sizeof_rela, sizeof_sym, sizeof_dyn, sizeof_note;
  unsigned char sizeof_hash_entry;
  unsigned char int_rels_per_ext_rel;
  unsigned char arch_size, log_file_align;
  unsigned char elfclass, ev_current;
  int (*write_out_phdrs) (void *, const void *, unsigned int);
  bfd_boolean (*write_shdrs_and_ehdr) (bfd *);
  bfd_boolean (*checksum_contents) (bfd *, void (*) (const void *, size_t, void *), void *);
  void (*write_relocs) (bfd *, asection *, void *);
  bfd_boolean (*swap_symbol_in) (bfd *, const void *, const void *, void *);
  void (*swap_symbol_out) (bfd *, const void *, void *, void *);
  bfd_boolean (*slurp_reloc_table) (bfd *, asection *, asymbol **, bfd_boolean);
  long (*slurp_symbol_table) (bfd *, asymbol **, bfd_boolean);
  void (*swap_dyn_in) (bfd *, const void *, void *);
  void (*swap_dyn_out) (bfd *, const void *, void *);
  void (*swap_reloc_in) (bfd *, const bfd_byte *, Elf_Internal_Rela *);
  void (*swap_reloc_out) (bfd *, const Elf_Internal_Rela *, bfd_byte *);
  void (*swap_reloca_in) (bfd *, const bfd_byte *, Elf_Internal_Rela *);
  void (*swap_reloca_out) (bfd *, const Elf_Internal_Rela *, bfd_byte *);
};

struct bfd_link_order {
  union {
    struct {
      asection *section;
    } indirect;
  } u;
};

struct bfd_link_info;

struct bfd_link_callbacks {
  void (*einfo) (const char *fmt, ...);
  void (*undefined_symbol)
    (struct bfd_link_info *info, const char *name, bfd *abfd,
     asection *section, bfd_vma address, bfd_boolean fatal);
  void (*reloc_dangerous)
    (struct bfd_link_info *info, const char *message, bfd *abfd,
     asection *section, bfd_vma address);
  void (*reloc_overflow)
    (struct bfd_link_info *info, const char *name, const char *symbol_name,
     const char *reloc_name, bfd_vma addend, bfd *abfd, asection *section,
     bfd_vma address);
};

struct bfd_link_info {
  struct bfd *input_bfds;
  struct bfd *output_bfd;
  struct bfd_link_callbacks *callbacks;
};

struct elf_backend_data
{
  int arch;
  int target_id;
  int elf_machine_code;
  int elf_osabi;
  bfd_vma maxpagesize;
  bfd_vma minpagesize;
  bfd_vma commonpagesize;
  bfd_vma relropagesize;
  flagword dynamic_sec_flags;
  const void *arch_data;
  bfd_boolean (*elf_info_to_howto) (bfd *, arelent *, Elf_Internal_Rela *);
  bfd_boolean (*elf_info_to_howto_rel) (bfd *, arelent *, Elf_Internal_Rela *);
  const struct elf_size_info *s;
  const void *special_sections;
  bfd_vma got_header_size;
  unsigned static_tls_alignment;
  unsigned stack_align;
  unsigned long elf_strtab_flags;
  unsigned int rel_hdr_size;
  unsigned int rela_hdr_size;
  unsigned int arch_size;
  int (*sign_extend_vma);
};

#define xvec_get_elf_backend_data(xvec) \
  ((const struct elf_backend_data *) (xvec)->backend_data)
#define get_elf_backend_data(abfd) \
  xvec_get_elf_backend_data ((abfd)->xvec)

#define HOWTO(type, right, size, bits, pcrel, left, ovf, func, name,   \
              inplace, src_mask, dst_mask, pcrel_off)                  \
  { (unsigned) type, size < 0 ? -size : size, bits, right, left, ovf,  \
    size < 0, pcrel, inplace, pcrel_off, src_mask, dst_mask, func, name }

extern unsigned int bfd_get_reloc_size (reloc_howto_type *);

extern bfd_boolean bfd_reloc_offset_in_range
  (reloc_howto_type *howto, bfd *abfd, asection *section, bfd_size_type offset);

extern void elf_swap_reloc_in(bfd *abfd, const bfd_byte *s, Elf_Internal_Rela *dst);
extern void elf_swap_reloca_in(bfd *abfd, const bfd_byte *s, Elf_Internal_Rela *dst);

extern bfd_boolean elf_slurp_reloc_table(bfd *abfd, asection *asect, asymbol **symbols,
                                         bfd_boolean dynamic);

extern long _bfd_elf_canonicalize_reloc(bfd *abfd, sec_ptr section, arelent **relptr,
                                        asymbol **symbols);

extern bfd_reloc_status_type _bfd_clear_contents(reloc_howto_type *howto, bfd *input_bfd,
                                                asection *input_section, bfd_byte *data, bfd_vma offset);

extern bfd_byte *bfd_generic_get_relocated_section_contents
  (bfd *abfd, struct bfd_link_info *link_info,
   struct bfd_link_order *link_order, bfd_byte *data, bfd_boolean relocatable,
   asymbol **symbols);

extern bfd_vma bfd_get_8 (bfd *abfd, bfd_byte *data);
extern bfd_vma bfd_get_16 (bfd *abfd, bfd_byte *data);
extern bfd_vma bfd_get_32 (bfd *abfd, bfd_byte *data);
extern bfd_vma bfd_get_64 (bfd *abfd, bfd_byte *data);
extern bfd_vma bfd_get_24 (bfd *abfd, bfd_byte *data);

extern void write_reloc (bfd *abfd, bfd_vma x, bfd_byte *data, reloc_howto_type *howto);

#define bfd_get_section_limit_octets(bfd, sec)			\
  ((bfd)->direction != write_direction && (sec)->rawsize != 0	\
   ? (sec)->rawsize : (sec)->size)

unsigned int
bfd_get_reloc_size (reloc_howto_type *howto)
{
  switch (howto->size)
    {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 0;
    case 4: return 8;
    case 5: return 3;
    default: abort ();
    }
}

bfd_boolean bfd_reloc_offset_in_range(reloc_howto_type *howto, bfd *abfd,
                                      asection *section, bfd_size_type octet) {
  bfd_size_type octet_end = bfd_get_section_limit_octets(abfd, section);
  bfd_size_type reloc_size = bfd_get_reloc_size(howto);

  /* The reloc field must be contained entirely within the section.
     Allow zero length fields (marker relocs or NONE relocs where no
     relocation will be performed) at the end of the section.  */
  return octet <= octet_end && octet + reloc_size <= octet_end;
}

void elf_swap_reloc_in(bfd *abfd, const bfd_byte *s, Elf_Internal_Rela *dst) {
  const Elf_External_Rel *src = (const Elf_External_Rel *)s;
  dst->r_offset = H_GET_WORD(abfd, src->r_offset);
  dst->r_info = H_GET_WORD(abfd, src->r_info);
  dst->r_addend = 0;
}

void elf_swap_reloca_in(bfd *abfd, const bfd_byte *s, Elf_Internal_Rela *dst) {
  const Elf_External_Rela *src = (const Elf_External_Rela *)s;
  dst->r_offset = H_GET_WORD(abfd, src->r_offset);
  dst->r_info = H_GET_WORD(abfd, src->r_info);
  dst->r_addend = H_GET_SIGNED_WORD(abfd, src->r_addend);
}

static bfd_boolean
elf_slurp_reloc_table_from_section(bfd *abfd, asection *asect,
                                   Elf_Internal_Shdr *rel_hdr,
                                   bfd_size_type reloc_count, arelent *relents,
                                   asymbol **symbols, bfd_boolean dynamic) {
  const struct elf_backend_data *const ebd = get_elf_backend_data(abfd);
  void *allocated = NULL;
  bfd_byte *native_relocs;
  arelent *relent;
  unsigned int i;
  int entsize;
  unsigned int symcount;

  allocated = bfd_malloc(rel_hdr->sh_size);
  if (allocated == NULL)
    goto error_return;

  if (bfd_seek(abfd, rel_hdr->sh_offset, SEEK_SET) != 0 ||
      (bfd_bread(allocated, rel_hdr->sh_size, abfd) != rel_hdr->sh_size))
    goto error_return;

  native_relocs = (bfd_byte *)allocated;

  entsize = rel_hdr->sh_entsize;
  BFD_ASSERT(entsize == sizeof(Elf_External_Rel) ||
             entsize == sizeof(Elf_External_Rela));

  if (dynamic)
    symcount = bfd_get_dynamic_symcount(abfd);
  else
    symcount = bfd_get_symcount(abfd);

  for (i = 0, relent = relents; i < reloc_count;
       i++, relent++, native_relocs += entsize) {
    bfd_boolean res;
    Elf_Internal_Rela rela;

    if (entsize == sizeof(Elf_External_Rela))
      elf_swap_reloca_in(abfd, native_relocs, &rela);
    else
      elf_swap_reloc_in(abfd, native_relocs, &rela);

    /* The address of an ELF reloc is section relative for an object
       file, and absolute for an executable file or shared library.
       The address of a normal BFD reloc is always section relative,
       and the address of a dynamic reloc is absolute..  */
    if ((abfd->flags & (EXEC_P | DYNAMIC)) == 0 || dynamic)
      relent->address = rela.r_offset;
    else
      relent->address = rela.r_offset - asect->vma;

    if (ELF_R_SYM(rela.r_info) == STN_UNDEF)
      /* FIXME: This and the error case below mean that we have a
         symbol on relocs that is not elf_symbol_type.  */
      relent->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;
    else if (ELF_R_SYM(rela.r_info) > symcount) {
      _bfd_error_handler
          /* xgettext:c-format */
          (_("%pB(%pA): relocation %d has invalid symbol index %ld"), abfd,
           asect, i, (long)ELF_R_SYM(rela.r_info));
      bfd_set_error(bfd_error_bad_value);
      relent->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;
    } else {
      asymbol **ps;

      ps = symbols + ELF_R_SYM(rela.r_info) - 1;

      relent->sym_ptr_ptr = ps;
    }

    relent->addend = rela.r_addend;

    if ((entsize == sizeof(Elf_External_Rela) &&
         ebd->elf_info_to_howto != NULL) ||
        ebd->elf_info_to_howto_rel == NULL)
      res = ebd->elf_info_to_howto(abfd, relent, &rela);
    else
      res = ebd->elf_info_to_howto_rel(abfd, relent, &rela);

    if (!res || relent->howto == NULL)
      goto error_return;
  }

  if (allocated != NULL)
    free(allocated);
  return TRUE;

error_return:
  if (allocated != NULL)
    free(allocated);
  return FALSE;
}

bfd_boolean elf_slurp_reloc_table(bfd *abfd, asection *asect, asymbol **symbols,
                                  bfd_boolean dynamic) {
  struct bfd_elf_section_data *const d = elf_section_data(asect);
  Elf_Internal_Shdr *rel_hdr;
  Elf_Internal_Shdr *rel_hdr2;
  bfd_size_type reloc_count;
  bfd_size_type reloc_count2;
  arelent *relents;
  bfd_size_type amt;

  if (asect->relocation != NULL)
    return TRUE;

  if (!dynamic) {
    if ((asect->flags & SEC_RELOC) == 0 || asect->reloc_count == 0)
      return TRUE;

    rel_hdr = d->rel.hdr;
    reloc_count = rel_hdr ? NUM_SHDR_ENTRIES(rel_hdr) : 0;
    rel_hdr2 = d->rela.hdr;
    reloc_count2 = rel_hdr2 ? NUM_SHDR_ENTRIES(rel_hdr2) : 0;

    /* PR 17512: file: 0b4f81b7.  */
    if (asect->reloc_count != reloc_count + reloc_count2)
      return FALSE;
    BFD_ASSERT((rel_hdr && asect->rel_filepos == rel_hdr->sh_offset) ||
               (rel_hdr2 && asect->rel_filepos == rel_hdr2->sh_offset));

  } else {
    /* Note that ASECT->RELOC_COUNT tends not to be accurate in this
       case because relocations against this section may use the
       dynamic symbol table, and in that case bfd_section_from_shdr
       in elf.c does not update the RELOC_COUNT.  */
    if (asect->size == 0)
      return TRUE;

    rel_hdr = &d->this_hdr;
    reloc_count = NUM_SHDR_ENTRIES(rel_hdr);
    rel_hdr2 = NULL;
    reloc_count2 = 0;
  }

  amt = (reloc_count + reloc_count2) * sizeof(arelent);
  relents = (arelent *)bfd_alloc(abfd, amt);
  if (relents == NULL)
    return FALSE;

  if (rel_hdr &&
      !elf_slurp_reloc_table_from_section(abfd, asect, rel_hdr, reloc_count,
                                          relents, symbols, dynamic))
    return FALSE;

  if (rel_hdr2 && !elf_slurp_reloc_table_from_section(
                      abfd, asect, rel_hdr2, reloc_count2,
                      relents + reloc_count, symbols, dynamic))
    return FALSE;

  asect->relocation = relents;
  return TRUE;
}

long _bfd_elf_canonicalize_reloc(bfd *abfd, sec_ptr section, arelent **relptr,
                                 asymbol **symbols) {
  arelent *tblptr;
  unsigned int i;
  const struct elf_backend_data *bed = get_elf_backend_data(abfd);

  if (!bed->s->slurp_reloc_table(abfd, section, symbols, FALSE))
    return -1;

  tblptr = section->relocation;
  for (i = 0; i < section->reloc_count; i++)
    *relptr++ = tblptr++;

  *relptr = NULL;

  return section->reloc_count;
}

long bfd_canonicalize_reloc(bfd *abfd, sec_ptr asect, arelent **location,
                            asymbol **symbols) {
  if (abfd->format != bfd_object) {
    bfd_set_error(bfd_error_invalid_operation);
    return -1;
  }

  return _bfd_elf_canonicalize_reloc(abfd, asect, location, symbols);
}

static bfd_vma
read_reloc (bfd *abfd, bfd_byte *data, reloc_howto_type *howto)
{
  switch (howto->size)
    {
    case 0:
      return bfd_get_8 (abfd, data);

    case 1:
      return bfd_get_16 (abfd, data);

    case 2:
      return bfd_get_32 (abfd, data);

    case 3:
      break;

#ifdef BFD64
    case 4:
      return bfd_get_64 (abfd, data);
#endif

    case 5:
      return bfd_get_24 (abfd, data);

    default:
      abort ();
    }
  return 0;
}

bfd_reloc_status_type _bfd_clear_contents(reloc_howto_type *howto, bfd *input_bfd,
                         asection *input_section, bfd_byte *data, bfd_vma offset) {
  bfd_vma x;
  bfd_byte *location;

  if (!bfd_reloc_offset_in_range(howto, input_bfd, input_section, offset)) {
    return bfd_reloc_outofrange;
  }

  /* Get the value we are going to relocate.  */
  location = data + offset;
  x = read_reloc(input_bfd, location, howto);

  /* Zero out the unwanted bits of X.  */
  x &= ~howto->dst_mask;

  /* For a range list, use 1 instead of 0 as placeholder.  0
     would terminate the list, hiding any later entries.  */
  if (strcmp(bfd_get_section_name(input_bfd, input_section), ".debug_ranges") ==
          0 &&
      (howto->dst_mask & 1) != 0)
    x |= 1;

  /* Put the relocated value back in the object file.  */
  write_reloc(input_bfd, x, location, howto);
  return bfd_reloc_ok;
}

bfd_byte *bfd_generic_get_relocated_section_contents(
    bfd *abfd, struct bfd_link_info *link_info,
    struct bfd_link_order *link_order, bfd_byte *data, bfd_boolean relocatable,
    asymbol **symbols) {
  bfd *input_bfd = link_order->u.indirect.section->owner;
  asection *input_section = link_order->u.indirect.section;
  long reloc_size;
  arelent **reloc_vector;
  long reloc_count;

  reloc_size = bfd_get_reloc_upper_bound(input_bfd, input_section);
  if (reloc_size < 0)
    return NULL;

  /* Read in the section.  */
  if (!bfd_get_full_section_contents(input_bfd, input_section, &data))
    return NULL;

  if (data == NULL)
    return NULL;

  if (reloc_size == 0)
    return data;

  reloc_vector = (arelent **)bfd_malloc(reloc_size);
  if (reloc_vector == NULL)
    return NULL;

  reloc_count =
      bfd_canonicalize_reloc(input_bfd, input_section, reloc_vector, symbols);
  if (reloc_count < 0)
    goto error_return;

  if (reloc_count > 0) {
    arelent **parent;

    for (parent = reloc_vector; *parent != NULL; parent++) {
      char *error_message = NULL;
      asymbol *symbol;
      bfd_reloc_status_type r;

      symbol = *(*parent)->sym_ptr_ptr;
      /* PR ld/19628: A specially crafted input file
         can result in a NULL symbol pointer here.  */
      if (symbol == NULL) {
        link_info->callbacks->einfo
            /* xgettext:c-format */
            (_("%X%P: %pB(%pA): error: relocation for offset %V has no "
               "value\n"),
             abfd, input_section, (*parent)->address);
        goto error_return;
      }

      /* Zap reloc field when the symbol is from a discarded
         section, ignoring any addend.  Do the same when called
         from bfd_simple_get_relocated_section_contents for
         undefined symbols in debug sections.  This is to keep
         debug info reasonably sane, in particular so that
         DW_FORM_ref_addr to another file's .debug_info isn't
         confused with an offset into the current file's
         .debug_info.  */
      if ((symbol->section != NULL && discarded_section(symbol->section)) ||
          (symbol->section == bfd_und_section_ptr &&
           (input_section->flags & SEC_DEBUGGING) != 0 &&
           link_info->input_bfds == link_info->output_bfd)) {
        bfd_vma off;
        static reloc_howto_type none_howto =
            HOWTO(0, 0, 0, 0, FALSE, 0, complain_overflow_dont, NULL, "unused",
                  FALSE, 0, 0, FALSE);

        off = (*parent)->address * bfd_octets_per_byte(input_bfd);
        _bfd_clear_contents((*parent)->howto, input_bfd, input_section, data, off);
        (*parent)->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;
        (*parent)->addend = 0;
        (*parent)->howto = &none_howto;
        r = bfd_reloc_ok;
      } else
        r = bfd_perform_relocation(input_bfd, *parent, data, input_section,
                                   relocatable ? abfd : NULL, &error_message);

      if (relocatable) {
        asection *os = input_section->output_section;

        /* A partial link, so keep the relocs.  */
        os->orelocation[os->reloc_count] = *parent;
        os->reloc_count++;
      }

      if (r != bfd_reloc_ok) {
        switch (r) {
        case bfd_reloc_undefined:
          (*link_info->callbacks->undefined_symbol)(
              link_info, bfd_asymbol_name(*(*parent)->sym_ptr_ptr), input_bfd,
              input_section, (*parent)->address, TRUE);
          break;
        case bfd_reloc_dangerous:
          BFD_ASSERT(error_message != NULL);
          (*link_info->callbacks->reloc_dangerous)(link_info, error_message,
                                                   input_bfd, input_section,
                                                   (*parent)->address);
          break;
        case bfd_reloc_overflow:
          (*link_info->callbacks->reloc_overflow)(
              link_info, NULL, bfd_asymbol_name(*(*parent)->sym_ptr_ptr),
              (*parent)->howto->name, (*parent)->addend, input_bfd,
              input_section, (*parent)->address);
          break;
        case bfd_reloc_outofrange:
          /* PR ld/13730:
             This error can result when processing some partially
             complete binaries.  Do not abort, but issue an error
             message instead.  */
          link_info->callbacks->einfo
              /* xgettext:c-format */
              (_("%X%P: %pB(%pA): relocation \"%pR\" goes out of range\n"),
               abfd, input_section, *parent);
          goto error_return;

        case bfd_reloc_notsupported:
          /* PR ld/17512
             This error can result when processing a corrupt binary.
             Do not abort.  Issue an error message instead.  */
          link_info->callbacks->einfo
              /* xgettext:c-format */
              (_("%X%P: %pB(%pA): relocation \"%pR\" is not supported\n"), abfd,
               input_section, *parent);
          goto error_return;

        default:
          /* PR 17512; file: 90c2a92e.
             Report unexpected results, without aborting.  */
          link_info->callbacks->einfo
              /* xgettext:c-format */
              (_("%X%P: %pB(%pA): relocation \"%pR\" returns an unrecognized "
                 "value %x\n"),
               abfd, input_section, *parent, r);
          break;
        }
      }
    }
  }

  free(reloc_vector);
  return data;

error_return:
  free(reloc_vector);
  return NULL;
}
