/* Self-compilable output file extracted from bad.c
 * Dependencies from binutils-gdb codebase */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro definitions from include/symcat.h */
#define CONCAT2(a, b) a##b
#define CONCAT3(a, b, c) a##b##c

/* Macro definitions from include/ansidecl.h */
#define ATTRIBUTE_UNUSED __attribute__((__unused__))

/* Basic type definitions from bfd/bfd-in.h */
typedef int bfd_boolean;
#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE 1

typedef unsigned long bfd_vma;
typedef unsigned long bfd_size_type;
typedef long file_ptr;
typedef unsigned int flagword;
typedef unsigned char bfd_byte;

typedef enum bfd_format {
  bfd_unknown = 0,
  bfd_object,
  bfd_archive,
  bfd_core,
  bfd_type_end
} bfd_format;

typedef enum bfd_endian {
  BFD_ENDIAN_UNKNOWN,
  BFD_ENDIAN_BIG,
  BFD_ENDIAN_LITTLE
} bfd_endian;

typedef enum bfd_flavour {
  bfd_target_unknown_flavour,
  bfd_target_aout_flavour,
  bfd_target_coff_flavour,
  bfd_target_coff_go32_flavour,
  bfd_target_elf_flavour,
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
  bfd_target_mmo_flavour
} bfd_flavour;

typedef enum bfd_architecture {
  bfd_arch_unknown,
  bfd_arch_obscure,
  bfd_arch_m68k,
  bfd_arch_i386,
  bfd_arch_x86_64,
  bfd_arch_i960,
  bfd_arch_or1k,
  bfd_arch_sparc,
  bfd_arch_spu,
  bfd_arch_mips,
  bfd_arch_i370,
  bfd_arch_m10200,
  bfd_arch_m10300,
  bfd_arch_a29k,
  bfd_arch_avr,
  bfd_arch_bpf,
  bfd_arch_cr16,
  bfd_arch_crx,
  bfd_arch_csky,
  bfd_arch_d10v,
  bfd_arch_d30v,
  bfd_arch_dlx,
  bfd_arch_epiphany,
  bfd_arch_fr30,
  bfd_arch_ft32,
  bfd_arch_frv,
  bfd_arch_h8300,
  bfd_arch_hppa,
  bfd_arch_ia64,
  bfd_arch_ip2k,
  bfd_arch_iq2000,
  bfd_arch_loongarch,
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
  bfd_arch_mmix,
  bfd_arch_mn10200,
  bfd_arch_mn10300,
  bfd_arch_msp430,
  bfd_arch_nds32,
  bfd_arch_nfp,
  bfd_arch_nios2,
  bfd_arch_ns32k,
  bfd_arch_or32,
  bfd_arch_pdp11,
  bfd_arch_pj,
  bfd_arch_powerpc,
  bfd_arch_pru,
  bfd_arch_rx,
  bfd_arch_s390,
  bfd_arc_arch,
  bfd_arch_score,
  bfd_arch_sh,
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
  bfd_arch_xc16x,
  bfd_arch_xgate,
  bfd_arch_xstormy16,
  bfd_arch_xtensa,
  bfd_arch_z80,
  bfd_arch_z8k,
  bfd_arch_aarch64,
  bfd_arch_sparc32plus,
  bfd_arch_amdgcn,
  bfd_arch_last
} bfd_architecture;

/* Forward declarations */
typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef struct bfd_section *sec_ptr;
typedef struct bfd_symbol asymbol;
typedef struct reloc_howto_struct reloc_howto_type;
typedef const struct reloc_howto_struct *const_reloc_howto_type;
typedef struct lineno_cache_entry alent;
typedef struct reloc_cache_entry arelent;
typedef struct arelent_chain arelent_chain;
typedef struct bfd_arch_info_type bfd_arch_info_type;
typedef struct bfd_target bfd_target;
typedef struct bfd_hash_entry bfd_hash_entry;
typedef struct bfd_hash_table bfd_hash_table;
struct bfd_window {
  bfd_byte *data;
  bfd_size_type size;
};
typedef struct bfd_window bfd_window;
typedef struct _symbol_info symbol_info;

typedef enum bfd_print_symbol_type {
  bfd_print_symbol_name,
  bfd_print_symbol_info,
  bfd_print_symbol_all
} bfd_print_symbol_type;

typedef enum bfd_reloc_code_real {
  BFD_RELOC_8,
  BFD_RELOC_16,
  BFD_RELOC_32,
  BFD_RELOC_64,
  BFD_RELOC_HI22,
  BFD_RELOC_LO10,
  BFD_RELOC_32_PCREL_S2,
  BFD_RELOC_SPARC_WDISP22,
  BFD_RELOC_SPARC13,
  BFD_RELOC_SPARC_GOT10,
  BFD_RELOC_SPARC_BASE13,
  BFD_RELOC_SPARC_GOT13,
  BFD_RELOC_SPARC_GOT22,
  BFD_RELOC_SPARC_PC10,
  BFD_RELOC_SPARC_PC22,
  BFD_RELOC_SPARC_WPLT30,
  BFD_RELOC_SPARC_REV32,
  BFD_RELOC_CTOR,
  BFD_RELOC_NONE
} bfd_reloc_code_real_type;
typedef enum bfd_reloc_code_real bfd_reloc_code_real_type;

typedef enum bfd_error {
  bfd_error_no_error,
  bfd_error_system_call,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_invalid_target,
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

#define bfd_error_invalid_operation bfd_error_invalid_operation
#define bfd_error_no_error bfd_error_no_error

/* Section flags from bfd/bfd-in2.h */
#define SEC_NO_FLAGS 0x000
#define SEC_ALLOC 0x001
#define SEC_LOAD 0x002
#define SEC_RELOC 0x004
#define SEC_READONLY 0x010
#define SEC_DATA 0x020
#define SEC_ROM 0x040
#define SEC_CONSTRUCTOR 0x080
#define SEC_HAS_CONTENTS 0x100
#define SEC_NEVER_LOAD 0x200
#define SEC_COFF_SHARED_LIBRARY 0x400
#define SEC_THREAD_LOCAL 0x800
#define SEC_HIDDEN_L 0x1000
#define SEC_GROUP 0x2000
#define SEC_LINKER_CREATED 0x4000

/* Symbol flags */
#define BSF_LOCAL 0x01
#define BSF_GLOBAL 0x02
#define BSF_DEBUGGING 0x04
#define BSF_FUNCTION 0x08
#define BSF_KEEP 0x10
#define BSF_WEAK 0x20
#define BSF_SYNTHETIC 0x40

/* BFD_ALIGN macro */
#define BFD_ALIGN(addr, align)                                                 \
  (((addr) + ((bfd_vma)(align) - 1)) & ~((bfd_vma)(align) - 1))

/* sprintf_vma macro */
#define sprintf_vma(s, x) sprintf(s, "%08lx", (unsigned long)x)

/* a.out section indices from include/bout.h */
#define N_ABS 2
#define N_TEXT 4
#define N_DATA 6
#define N_BSS 8
#define N_EXT 1

/* Relocation bits from include/aout/aout64.h */
#define BYTES_IN_WORD 4

#define RELOC_STD_BITS_PCREL_BIG ((unsigned int)0x80)
#define RELOC_STD_BITS_PCREL_LITTLE ((unsigned int)0x01)
#define RELOC_STD_BITS_LENGTH_BIG ((unsigned int)0x60)
#define RELOC_STD_BITS_LENGTH_SH_BIG 5
#define RELOC_STD_BITS_LENGTH_LITTLE ((unsigned int)0x06)
#define RELOC_STD_BITS_LENGTH_SH_LITTLE 1
#define RELOC_STD_BITS_EXTERN_BIG ((unsigned int)0x10)
#define RELOC_STD_BITS_EXTERN_LITTLE ((unsigned int)0x08)
#define RELOC_STD_BITS_BASEREL_BIG ((unsigned int)0x08)
#define RELOC_STD_BITS_BASEREL_LITTLE ((unsigned int)0x10)
#define RELOC_STD_BITS_JMPTABLE_BIG ((unsigned int)0x04)
#define RELOC_STD_BITS_JMPTABLE_LITTLE ((unsigned int)0x20)
#define RELOC_STD_BITS_RELATIVE_BIG ((unsigned int)0x02)
#define RELOC_STD_BITS_RELATIVE_LITTLE ((unsigned int)0x40)
#define RELOC_STD_SIZE (BYTES_IN_WORD + 3 + 1)

#define RELOC_EXT_SIZE (BYTES_IN_WORD + 3 + 1 + BYTES_IN_WORD)

/* External reloc structures */
struct reloc_std_external {
  bfd_byte r_address[BYTES_IN_WORD];
  bfd_byte r_index[3];
  bfd_byte r_type[1];
};

struct reloc_ext_external {
  bfd_byte r_address[BYTES_IN_WORD];
  bfd_byte r_index[3];
  bfd_byte r_type[1];
  bfd_byte r_addend[BYTES_IN_WORD];
};

/* HOWTO macros */
#define HOWTO(type, rs, size, bsz, pcrel, bitpos, ovrf, sf, name, part_inpl,   \
              readmask, setmask, pcdone)                                       \
  {                                                                            \
    type, rs, size, bsz, pcrel, bitpos, ovrf, sf, name, part_inpl, readmask,   \
        setmask, pcdone                                                        \
  }
#define EMPTY_HOWTO(n)                                                         \
  HOWTO(n, 0, 0, 0, FALSE, 0, complain_overflow_dont, 0, "empty", FALSE, 0, 0, \
        FALSE)

/* Complain types */
typedef enum {
  complain_overflow_dont,
  complain_overflow_bitfield,
  complain_overflow_signed,
  complain_overflow_unsigned
} complain_type;

/* reloc_howto_struct definition */
struct reloc_howto_struct {
  unsigned int type;
  int rightshift;
  int size;
  unsigned int bitsize;
  bfd_boolean pc_relative;
  int bitpos;
  complain_type complain_on_overflow;
  void (*special_function)(bfd *, struct reloc_cache_entry *,
                           struct bfd_symbol *, bfd_byte *, bfd_boolean,
                           bfd_vma);
  const char *name;
  bfd_boolean partial_inplace;
  bfd_vma src_mask;
  bfd_vma dst_mask;
  bfd_boolean pcrel_offset;
};

/* arelent (reloc_cache_entry) definition */
struct reloc_cache_entry {
  bfd_vma address;
  struct bfd_symbol **sym_ptr_ptr;
  bfd_size_type addend;
  struct reloc_howto_struct *howto;
};

/* asymbol (bfd_symbol) definition */
struct bfd_symbol {
  bfd *the_bfd;
  const char *name;
  bfd_vma value;
  flagword flags;
  struct bfd_section *section;
  union {
    void *p;
    int i;
  } udata;
};

#define KEEPIT udata.i

/* internal_exec definition */
struct internal_exec {
  long a_info;
  bfd_vma a_text;
  bfd_vma a_data;
  bfd_vma a_bss;
  bfd_vma a_syms;
  bfd_vma a_entry;
  bfd_vma a_trsize;
  bfd_vma a_drsize;
  bfd_vma a_tload;
  bfd_vma a_dload;
  unsigned char a_talign;
  unsigned char a_dalign;
  unsigned char a_balign;
  char a_relaxable;
};

/* aoutdata definition from bfd/libaout.h */
struct aoutdata {
  struct internal_exec *hdr;
  void *symbols;
  asection *textsec;
  asection *datasec;
  asection *bsssec;
  file_ptr sym_filepos;
  file_ptr str_filepos;
  unsigned reloc_entry_size;
  unsigned symbol_entry_size;
  unsigned long page_size;
  unsigned long segment_size;
  unsigned long zmagic_disk_block_size;
  unsigned exec_bytes_size;
  unsigned vma_adjusted;
  enum aout_subformat {
    default_format = 0,
    gnu_encap_format,
    q_magic_format
  } subformat;
  enum aout_magic { undecided_magic = 0, z_magic, o_magic, n_magic } magic;
  char *line_buf;
  void *external_syms;
  bfd_size_type external_sym_count;
  struct bfd_window sym_window;
  char *external_strings;
  bfd_size_type external_string_size;
  struct bfd_window string_window;
  void *sym_hashes;
  void *dynamic_info;
  bfd_vma *local_got_offsets;
};

struct aout_data_struct {
  struct aoutdata a;
  struct internal_exec e;
};

/* bfd_section (asection) definition */
struct bfd_section {
  const char *name;
  int id;
  int index;
  struct bfd_section *next;
  struct bfd_section *prev;
  struct bfd_section *output_section;
  bfd_vma output_offset;
  bfd_vma vma;
  bfd_size_type size;
  bfd_vma lma;
  unsigned int alignment_power;
  flagword flags;
  bfd *owner;
  struct bfd_symbol *symbol;
  struct bfd_symbol **symbol_ptr_ptr;
  struct reloc_cache_entry *relocation;
  struct reloc_cache_entry **orelocation;
  long reloc_count;
  unsigned int target_index;
  bfd_size_type entsize;
  int compress_status;
  struct arelent_chain *constructor_chain;
  struct bfd_hash_entry *group_id;
  void *used_by_bfd;
  file_ptr rel_filepos;
  void *target_internal;
};

/* bfd_hash_entry definition */
struct bfd_hash_entry {
  struct bfd_hash_entry *next;
};

/* bfd_hash_table definition */
struct bfd_hash_table {
  struct bfd_hash_entry **table;
  unsigned int size;
  unsigned int entsize;
};

/* section_hash_entry definition */
struct section_hash_entry {
  struct bfd_hash_entry root;
  asection section;
};

/* bfd_window already defined above */

/* symbol_info definition */
typedef struct _symbol_info {
  bfd_vma value;
  char type;
  char bind;
  unsigned char name[1];
} symbol_info;

/* bfd_arch_info_type definition */
struct bfd_arch_info_type {
  unsigned long mach;
  const char *printable_name;
  unsigned int section_align_power;
  enum bfd_architecture arch;
};

/* bfd_target definition */
struct bfd_target {
  const char *name;
  enum bfd_flavour flavour;
  enum bfd_endian byteorder;
  enum bfd_endian header_byteorder;
  flagword object_flags;
  flagword section_flags;
  const struct bfd_arch_info_type *arch_info;
  bfd_boolean (*_bfd_close_and_cleanup)(bfd *);
};

/* bfd tdata union */
union bfd_tdata {
  struct aout_data_struct *aout_data;
  struct pe_data_struct *pe_obj_data;
  void *elf_obj_data;
};

/* bfd definition */
struct bfd {
  const char *filename;
  const bfd_target *xvec;
  union bfd_tdata tdata;
  struct bfd_section *sections;
  struct bfd_section *section_last;
  unsigned int section_count;
  struct bfd_hash_table section_htab;
  bfd_boolean output_has_begun;
  bfd_boolean target_defaulted;
  void *cache;
  long symcount;
  bfd_format format;
  bfd_vma start_address;
  flagword flags;
  struct bfd_arch_info_type *arch_info;
};

/* external_exec definition */
struct external_exec {
  bfd_byte e_info[4];
  bfd_byte e_text[BYTES_IN_WORD];
  bfd_byte e_data[BYTES_IN_WORD];
  bfd_byte e_bss[BYTES_IN_WORD];
  bfd_byte e_syms[BYTES_IN_WORD];
  bfd_byte e_entry[BYTES_IN_WORD];
  bfd_byte e_trsize[BYTES_IN_WORD];
  bfd_byte e_drsize[BYTES_IN_WORD];
};

#define EXEC_BYTES_SIZE (4 + BYTES_IN_WORD * 7)

/* arelent_chain definition */
struct arelent_chain {
  struct reloc_cache_entry relent;
  struct arelent_chain *next;
};

/* aout macros from bfd/libaout.h */
#define H_GET_32 bfd_h_get_32
#define H_PUT_32 bfd_h_put_32
#define adata(bfd) ((bfd)->tdata.aout_data->a)
#define exec_hdr(bfd) (adata(bfd).hdr)
#define obj_textsec(bfd) (adata(bfd).textsec)
#define obj_datasec(bfd) (adata(bfd).datasec)
#define obj_bsssec(bfd) (adata(bfd).bsssec)
#define obj_reloc_entry_size(bfd) (adata(bfd).reloc_entry_size)

/* NAME macro for 32-bit */
#define NAME(x, y) CONCAT3(x, _32_, y)

/* BFD accessor macros */
#define bfd_get_symcount(abfd) ((abfd)->symcount)
#define bfd_get_format(abfd) ((abfd)->format)
#define bfd_get_arch_macro(abfd) ((abfd)->arch_info->arch)
#define bfd_get_mach_macro(abfd) ((abfd)->arch_info->mach)
#define bfd_get_start_address(abfd) ((abfd)->start_address)
#define bfd_get_file_flags(abfd) ((abfd)->flags)
#define bfd_get_target(abfd) ((abfd)->xvec->name)
#define bfd_get_filename(abfd) ((abfd)->filename)
#define bfd_count_sections(abfd) ((abfd)->section_count)
#define bfd_get_flavour(abfd) ((abfd)->xvec->flavour)
#define bfd_get_section_flags(abfd, sec) ((sec)->flags)
#define bfd_section_size(abfd, sec) ((sec)->size)
#define bfd_get_section_size(sec) ((sec)->size)
#define bfd_section_vma(abfd, sec) ((sec)->vma)
#define bfd_section_lma(abfd, sec) ((sec)->lma)
#define bfd_section_alignment(abfd, sec) ((sec)->alignment_power)
#define bfd_section_name(abfd, sec) ((sec)->name)
#define bfd_get_reloc_upper_bound(abfd, sec)                                   \
  ((sec)->reloc_count * sizeof(arelent *))
#define bfd_asymbol_name(sym) ((sym)->name)

#define bfd_header_big_endian(abfd) ((abfd)->xvec->byteorder == BFD_ENDIAN_BIG)

/* PE data macros */
#define pe_data(abfd) ((struct pe_data_struct *)((abfd)->tdata.pe_obj_data))
#define bfd_pei_p(abfd) (0)

/* ELF internal header */
struct elf_internal_ehdr {
  unsigned int e_machine;
};

/* ELF macros */
#define elf_section_type(sec) (*(unsigned int *)&(sec)->target_internal)
#define elf_group_id(sec) ((sec)->group_id)
#define elf_elfheader(abfd)                                                    \
  ((struct elf_internal_ehdr *)((abfd)->tdata.elf_obj_data))

/* BFD_SEND macros simplified */
extern bfd_boolean bfd_set_format(bfd *, bfd_format);
#define bfd_set_start_address(abfd, addr) ((abfd)->start_address = (addr), TRUE)
#define bfd_set_file_flags(abfd, flags) ((abfd)->flags = (flags), TRUE)
#define bfd_applicable_file_flags(abfd) (~0)
#define bfd_set_arch_mach(abfd, a, m)                                          \
  ((abfd)->arch_info->arch = (enum bfd_architecture)(a),                       \
   (abfd)->arch_info->mach = (m), TRUE)
#define bfd_set_section_size(abfd, sec, sz) ((sec)->size = (sz), TRUE)
#define bfd_set_section_vma(abfd, sec, v) ((sec)->vma = (v), TRUE)
#define bfd_set_section_alignment(abfd, sec, a)                                \
  ((sec)->alignment_power = (a), TRUE)
#define bfd_set_reloc(abfd, sec, rel, cnt)                                     \
  ((sec)->relocation = (rel), (sec)->reloc_count = (cnt), TRUE)
#define bfd_copy_private_section_data(ibfd, isec, obfd, osec) (TRUE)
#define bfd_copy_private_bfd_data(ibfd, obfd) (TRUE)
#define bfd_set_section_contents(abfd, sec, loc, off, len) (TRUE)
#define bfd_set_symtab(abfd, syms, count) (TRUE)
#define bfd_write_p(abfd) (1)

/* Section predicates */
#define bfd_is_com_section(sec) ((sec) == bfd_com_section_ptr)
#define bfd_is_abs_section(sec) ((sec) == bfd_abs_section_ptr)
#define bfd_is_und_section(sec) ((sec) == bfd_und_section_ptr)

/* BFD_ASSERT macro */
#define BFD_ASSERT(expr) ((void)0)

/* HAS_RELOC flag */
#define HAS_RELOC 0x1

/* GNU_BUILD_ATTRS_SECTION_NAME */
#define GNU_BUILD_ATTRS_SECTION_NAME ".note.gnu.build-id"

/* FOPEN_WB */
#define FOPEN_WB "wb"

/* EXTERNAL_NLIST_SIZE */
#define EXTERNAL_NLIST_SIZE 12

/* N_SYMOFF, N_TRELOFF, N_DRELOFF */
#define N_SYMOFF(exec) ((exec)->a_text + (exec)->a_data + (exec)->a_syms)
#define N_TRELOFF(exec) ((exec)->a_text + (exec)->a_data)
#define N_DRELOFF(exec) ((exec)->a_text + (exec)->a_data + (exec)->a_trsize)

/* N_SET_MACHTYPE */
#define N_SET_MACHTYPE(execp, machtype)                                        \
  ((execp)->a_info =                                                           \
       ((execp)->a_info & 0xff00ffff) | ((((int)(machtype)) & 0xff) << 16))

/* M_386 machine type */
#define M_386 100

/* Section context flags */
#define SECTION_CONTEXT_SET_FLAGS 0x1
#define SECTION_CONTEXT_SET_VMA 0x2
#define SECTION_CONTEXT_ALTER_VMA 0x4
#define SECTION_CONTEXT_SET_LMA 0x8
#define SECTION_CONTEXT_ALTER_LMA 0x10

/* Strip modes */
enum strip_mode {
  STRIP_NONE = 0,
  STRIP_DEBUG,
  STRIP_UNNEEDED,
  STRIP_ALL,
  STRIP_NONDEBUG,
  STRIP_DWO,
  STRIP_NONDWO
};

/* Discard locals */
enum discard_mode { LOCALS_UNDEF = 0, LOCALS_ALL, LOCALS_KEEP };

/* Debug section options */
enum debug_section_mode {
  no_debug_sections = 0,
  compress = 1,
  compress_zlib = 2,
  compress_gnu_zlib = 4,
  compress_gabi_zlib = 8,
  decompress = 16
};

/* ELF STT common options */
enum elf_stt_common_mode {
  elf_stt_common_unset = 0,
  elf_stt_common,
  no_elf_stt_common
};

/* BFD flags */
#define BFD_COMPRESS 0x1000
#define BFD_COMPRESS_GABI 0x2000
#define BFD_DECOMPRESS 0x4000
#define BFD_CONVERT_ELF_COMMON 0x8000
#define BFD_USE_ELF_STT_COMMON 0x10000

/* External variable declarations from binutils/objcopy.c */
extern int status;
extern asymbol **isympp;
extern asymbol **osympp;
extern bfd_vma change_section_address;
extern const char *prefix_alloc_sections_string;
extern const char *prefix_sections_string;
extern enum strip_mode strip_symbols;
extern int copy_byte;
extern int interleave;
extern int copy_width;
extern bfd_boolean extract_symbol;
extern bfd_vma change_start;
extern bfd_boolean set_start_set;
extern bfd_vma set_start;
extern flagword bfd_flags_to_set;
extern flagword bfd_flags_to_clear;
extern enum debug_section_mode do_debug_sections;
extern bfd_boolean do_elf_stt_common;
extern bfd_boolean verbose;
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
extern bfd_byte *merged_notes;
extern bfd_size_type merged_size;
extern bfd_boolean merge_notes;
extern const char *gnu_debuglink_filename;
extern struct section_add *add_sections;
extern struct section_add *update_sections;
extern struct section_add *dump_sections;
extern bfd_boolean convert_debugging;
extern bfd_boolean localize_hidden;
extern void *strip_specific_htab;
extern void *keep_specific_htab;
extern void *localize_specific_htab;
extern void *globalize_specific_htab;
extern void *keepglobal_specific_htab;
extern void *weaken_specific_htab;
extern void *redefine_specific_htab;
extern const char *prefix_symbols_string;
extern bfd_boolean sections_removed;
extern bfd_boolean sections_copied;
extern void *section_rename_list;
extern bfd_boolean weaken;
extern long add_symbols;
extern enum discard_mode discard_locals;
extern int gap_fill;
extern bfd_boolean gap_fill_set;
extern bfd_vma pad_to;
extern bfd_boolean pad_to_set;
extern bfd_boolean is_strip;
extern bfd_boolean change_leading_char;
extern bfd_boolean remove_leading_char;
extern long use_alt_mach_code;
extern int long_section_names;
extern bfd_boolean force_output_target;
extern const char *input_target;
extern const char *output_target;
extern const bfd_arch_info_type *input_arch;
extern char **obj_matching;

/* howto tables - declared with size for TABLE_SIZE macro */
extern reloc_howto_type howto_table_std[48];
extern reloc_howto_type howto_table_ext[32];

/* Absolute/undefined/common section pointers */
extern asection *bfd_abs_section_ptr;
extern asection *bfd_und_section_ptr;
extern asection *bfd_com_section_ptr;

/* Section ID */
extern int section_id;

/* PE data structure */
struct internal_pe_opt_header {
  bfd_vma FileAlignment;
  bfd_vma SizeOfHeapCommit;
  bfd_vma SizeOfHeapReserve;
  bfd_vma ImageBase;
  bfd_vma SectionAlignment;
  bfd_vma SizeOfStackCommit;
  bfd_vma SizeOfStackReserve;
  int Subsystem;
  int MajorSubsystemVersion;
  int MinorSubsystemVersion;
};

struct pe_data_struct {
  struct internal_pe_opt_header pe_opthdr;
};

typedef struct pe_data_struct pe_data_type;

/* PE defaults */
#define PE_DEF_FILE_ALIGNMENT 0x200
#define PE_DEF_SECTION_ALIGNMENT 0x1000

/* SHT_NOBITS */
#define SHT_NOBITS 8

/* Function declarations */
extern void *xmalloc(size_t);
extern void *bfd_malloc(bfd_size_type);
extern void *bfd_zmalloc(bfd_size_type);
extern void *bfd_zalloc(bfd *, bfd_size_type);
extern void bfd_release(bfd *, void *);
extern bfd_size_type bfd_bread(void *, bfd_size_type, bfd *);
extern bfd_size_type bfd_bwrite(const void *, bfd_size_type, bfd *);
extern int bfd_seek(bfd *, file_ptr, int);
extern bfd_vma bfd_h_get_32(bfd *, const void *);
extern void bfd_h_put_32(bfd *, bfd_vma, void *);
extern void bfd_put_word(bfd *, bfd_vma, void *);
#define PUT_WORD(abfd, val, dst) bfd_h_put_32(abfd, val, dst)

extern long bfd_get_symtab_upper_bound(bfd *);
extern long bfd_canonicalize_symtab(bfd *, asymbol **);
extern long bfd_canonicalize_reloc(bfd *, sec_ptr, arelent **, asymbol **);
extern bfd_boolean bfd_get_full_section_contents(bfd *, sec_ptr, bfd_byte **);
extern bfd_boolean bfd_malloc_and_get_section(bfd *, sec_ptr, bfd_byte **);
extern asection *bfd_create_gnu_debuglink_section(bfd *, const char *);
extern bfd_boolean bfd_fill_in_gnu_debuglink_section(bfd *, asection *,
                                                     const char *);
extern bfd_boolean bfd_close_all_done(bfd *);
extern bfd_boolean bfd_alt_mach_code(bfd *, long);
/* bfd_set_format is defined as macro above */
extern bfd_error_type bfd_get_error(void);
extern void bfd_set_error(bfd_error_type);

extern bfd_architecture bfd_get_arch(bfd *);
extern unsigned long bfd_get_mach(bfd *);
extern const bfd_arch_info_type *bfd_get_arch_info(bfd *);
extern const char *bfd_printable_arch_mach(enum bfd_architecture,
                                           unsigned long);

extern void bfd_nonfatal_message(const char *, bfd *, asection *, const char *,
                                 ...);
extern const char *bfd_get_archive_filename(bfd *);
extern void _bfd_error_handler(const char *, ...);
extern void non_fatal(const char *, ...);

extern struct section_hash_entry *section_hash_lookup(struct bfd_hash_table *,
                                                      const char *, bfd_boolean,
                                                      bfd_boolean);
extern struct bfd_hash_entry *bfd_section_hash_newfunc(struct bfd_hash_entry *,
                                                       struct bfd_hash_table *,
                                                       const char *);
extern bfd_boolean _bfd_generic_new_section_hook(bfd *, asection *);
extern void _bfd_generic_set_reloc(bfd *, sec_ptr, arelent **, unsigned int);

extern asymbol *group_signature(asection *);
extern bfd_boolean is_strip_section(bfd *, asection *);
extern bfd_boolean skip_section(bfd *, asection *, bfd_boolean);
extern bfd_boolean discard_relocations(bfd *, asection *);
extern const char *find_section_rename(const char *, flagword *);
extern struct section_list *find_section_list(const char *, bfd_boolean, int);
extern bfd_boolean is_nondebug_keep_contents_section(bfd *, asection *);
extern bfd_boolean is_merged_note_section(bfd *, asection *);
extern bfd_size_type merge_gnu_build_notes(bfd *, asection *, bfd_size_type,
                                           bfd_byte *);
extern void *read_debugging_info(bfd *, asymbol **, long, bfd_boolean);
extern bfd_boolean write_debugging_info(bfd *, void *, long *, asymbol ***);
extern long filter_symbols(bfd *, bfd *, asymbol **, asymbol **, long);
extern void mark_symbols_used_in_relocations(bfd *, asection *, void *);
extern void copy_section(bfd *, asection *, void *);
extern void get_sections(bfd *, asection *, void *);
extern int compare_section_lma(const void *, const void *);
extern void setup_bfd_headers(bfd *, bfd *);
extern bfd_boolean is_specified_symbol(const char *, void *);
extern long htab_elements(void *);

extern sec_ptr bfd_make_section_anyway_with_flags(bfd *, const char *,
                                                  flagword);
extern sec_ptr bfd_make_section_with_flags(bfd *, const char *, flagword);
extern asection *bfd_get_section_by_name(bfd *, const char *);

extern bfd_size_type bfd_convert_section_size(bfd *, sec_ptr, bfd *,
                                              bfd_size_type);

extern void MY_swap_ext_reloc_in(bfd *, struct reloc_ext_external *, arelent *,
                                 asymbol **, bfd_size_type);
extern void MY_swap_std_reloc_in(bfd *, struct reloc_std_external *, arelent *,
                                 asymbol **, bfd_size_type);
extern void MY_swap_ext_reloc_out(bfd *, arelent *,
                                  struct reloc_ext_external *);
extern void MY_swap_std_reloc_out(bfd *, arelent *,
                                  struct reloc_std_external *);

/* Stub declarations for functions used but not defined */
extern void aout_32_swap_ext_reloc_in(bfd *, struct reloc_ext_external *,
                                      arelent *, asymbol **, bfd_size_type);
extern void aout_32_swap_ext_reloc_out(bfd *, arelent *,
                                       struct reloc_ext_external *);
extern bfd_boolean aout_32_adjust_sizes_and_vmas(bfd *);
extern void aout_32_swap_exec_header_out(bfd *, struct internal_exec *,
                                         struct external_exec *);
extern bfd_boolean aout_32_write_syms(bfd *);
extern bfd *bfd_openr(const char *, const char *);
extern bfd *bfd_openw(const char *, const char *);
extern bfd_boolean bfd_check_format(bfd *, bfd_format);
extern bfd_boolean bfd_check_format_matches(bfd *, bfd_format, char ***);
extern void set_long_section_mode(bfd *, bfd *, int);
extern void copy_archive(bfd *, bfd *, const char *, bfd_boolean,
                         const bfd_arch_info_type *);
extern off_t get_file_size(const char *);
extern asymbol **bfd_get_outsymbols(bfd *);
extern void list_matching_formats(char **);

#define MY_swap_ext_reloc_in NAME(aout, swap_ext_reloc_in)
#define MY_swap_std_reloc_in NAME(aout, swap_std_reloc_in)
#define MY_swap_ext_reloc_out NAME(aout, swap_ext_reloc_out)
#define MY_swap_std_reloc_out NAME(aout, swap_std_reloc_out)

/* gettext macro */
#define _(String) String

/* bfd_section_list_append macro */
#define bfd_section_list_append(ABFD, S)                                       \
  do {                                                                         \
    asection *_s = S;                                                          \
    bfd *_abfd = ABFD;                                                         \
    _s->next = NULL;                                                           \
    if (_abfd->section_last) {                                                 \
      _s->prev = _abfd->section_last;                                          \
      _abfd->section_last->next = _s;                                          \
    } else {                                                                   \
      _s->prev = NULL;                                                         \
      _abfd->sections = _s;                                                    \
    }                                                                          \
    _abfd->section_last = _s;                                                  \
  } while (0)

/* section_list and section_add structures from binutils/objcopy.c */
struct section_list {
  const char *name;
  flagword flags;
  int context;
  bfd_vma vma_val;
  bfd_vma lma_val;
  struct section_list *next;
};

struct section_add {
  const char *name;
  const char *filename;
  bfd_size_type size;
  bfd_byte *contents;
  asection *section;
  struct section_add *next;
};

/* TABLE_SIZE macro */
#define TABLE_SIZE(TABLE) (sizeof(TABLE) / sizeof(TABLE[0]))


#define NAME(x, y) CONCAT3(x, _32_, y)

#define MOVE_ADDRESS(ad)                                                       \
  if (r_extern) {                                                              \
    /* Undefined symbol.  */                                                   \
    cache_ptr->sym_ptr_ptr = symbols + r_index;                                \
    cache_ptr->addend = ad;                                                    \
  } else {                                                                     \
    /* Defined, section relative.  Replace symbol with pointer to              \
       symbol which points to section.  */                                     \
    switch (r_index) {                                                         \
    case N_TEXT:                                                               \
    case N_TEXT | N_EXT:                                                       \
      cache_ptr->sym_ptr_ptr = obj_textsec(abfd)->symbol_ptr_ptr;              \
      cache_ptr->addend = ad - su->textsec->vma;                               \
      break;                                                                   \
    case N_DATA:                                                               \
    case N_DATA | N_EXT:                                                       \
      cache_ptr->sym_ptr_ptr = obj_datasec(abfd)->symbol_ptr_ptr;              \
      cache_ptr->addend = ad - su->datasec->vma;                               \
      break;                                                                   \
    case N_BSS:                                                                \
    case N_BSS | N_EXT:                                                        \
      cache_ptr->sym_ptr_ptr = obj_bsssec(abfd)->symbol_ptr_ptr;               \
      cache_ptr->addend = ad - su->bsssec->vma;                                \
      break;                                                                   \
    default:                                                                   \
    case N_ABS:                                                                \
    case N_ABS | N_EXT:                                                        \
      cache_ptr->sym_ptr_ptr = bfd_abs_section_ptr->symbol_ptr_ptr;            \
      cache_ptr->addend = ad;                                                  \
      break;                                                                   \
    }                                                                          \
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



void NAME(aout, swap_std_reloc_in)(bfd *abfd, struct reloc_std_external *bytes,
                                   arelent *cache_ptr, asymbol **symbols,
                                   bfd_size_type symcount) {
  unsigned int r_index;
  int r_extern;
  unsigned int r_length;
  int r_pcrel;
  int r_baserel, r_jmptable, r_relative;
  struct aoutdata *su = &(abfd->tdata.aout_data->a);
  unsigned int howto_idx;

  cache_ptr->address = H_GET_32(abfd, bytes->r_address);

  /* Now the fun stuff.  */
  if (bfd_header_big_endian(abfd)) {
    r_index = (((unsigned int)bytes->r_index[0] << 16) |
               ((unsigned int)bytes->r_index[1] << 8) | bytes->r_index[2]);
    r_extern = (0 != (bytes->r_type[0] & RELOC_STD_BITS_EXTERN_BIG));
    r_pcrel = (0 != (bytes->r_type[0] & RELOC_STD_BITS_PCREL_BIG));
    r_baserel = (0 != (bytes->r_type[0] & RELOC_STD_BITS_BASEREL_BIG));
    r_jmptable = (0 != (bytes->r_type[0] & RELOC_STD_BITS_JMPTABLE_BIG));
    r_relative = (0 != (bytes->r_type[0] & RELOC_STD_BITS_RELATIVE_BIG));
    r_length = ((bytes->r_type[0] & RELOC_STD_BITS_LENGTH_BIG) >>
                RELOC_STD_BITS_LENGTH_SH_BIG);
  } else {
    r_index = (((unsigned int)bytes->r_index[2] << 16) |
               ((unsigned int)bytes->r_index[1] << 8) | bytes->r_index[0]);
    r_extern = (0 != (bytes->r_type[0] & RELOC_STD_BITS_EXTERN_LITTLE));
    r_pcrel = (0 != (bytes->r_type[0] & RELOC_STD_BITS_PCREL_LITTLE));
    r_baserel = (0 != (bytes->r_type[0] & RELOC_STD_BITS_BASEREL_LITTLE));
    r_jmptable = (0 != (bytes->r_type[0] & RELOC_STD_BITS_JMPTABLE_LITTLE));
    r_relative = (0 != (bytes->r_type[0] & RELOC_STD_BITS_RELATIVE_LITTLE));
    r_length = ((bytes->r_type[0] & RELOC_STD_BITS_LENGTH_LITTLE) >>
                RELOC_STD_BITS_LENGTH_SH_LITTLE);
  }

  howto_idx = (r_length + 4 * r_pcrel + 8 * r_baserel + 16 * r_jmptable +
               32 * r_relative);
  if (howto_idx < TABLE_SIZE(howto_table_std)) {
    cache_ptr->howto = howto_table_std + howto_idx;
    if (cache_ptr->howto->type == (unsigned int)-1)
      cache_ptr->howto = NULL;
  } else
    cache_ptr->howto = NULL;

  /* Base relative relocs are always against the symbol table,
     regardless of the setting of r_extern.  r_extern just reflects
     whether the symbol the reloc is against is local or global.  */
  if (r_baserel)
    r_extern = 1;

  if (r_extern && r_index > symcount) {
    /* We could arrange to return an error, but it might be useful
       to see the file even if it is bad.  */
    r_extern = 0;
    r_index = N_ABS;
  }

  MOVE_ADDRESS(0);
}



bfd_boolean NAME(aout, slurp_reloc_table)(bfd *abfd, sec_ptr asect,
                                          asymbol **symbols) {
  bfd_size_type count;
  bfd_size_type reloc_size;
  void *relocs;
  arelent *reloc_cache;
  size_t each_size;
  unsigned int counter = 0;
  arelent *cache_ptr;
  bfd_size_type amt;

  if (asect->relocation)
    return TRUE;

  if (asect->flags & SEC_CONSTRUCTOR)
    return TRUE;

  if (asect == obj_datasec(abfd))
    reloc_size = exec_hdr(abfd)->a_drsize;
  else if (asect == obj_textsec(abfd))
    reloc_size = exec_hdr(abfd)->a_trsize;
  else if (asect == obj_bsssec(abfd))
    reloc_size = 0;
  else {
    bfd_set_error(bfd_error_invalid_operation);
    return FALSE;
  }

  if (reloc_size == 0)
    return TRUE; /* Nothing to be done.  */

  if (bfd_seek(abfd, asect->rel_filepos, SEEK_SET) != 0)
    return FALSE;

  each_size = obj_reloc_entry_size(abfd);

  count = reloc_size / each_size;
  if (count == 0)
    return TRUE; /* Nothing to be done.  */

  amt = count * sizeof(arelent);
  reloc_cache = (arelent *)bfd_zmalloc(amt);
  if (reloc_cache == NULL)
    return FALSE;

  relocs = bfd_malloc(reloc_size);
  if (relocs == NULL) {
    free(reloc_cache);
    return FALSE;
  }

  if (bfd_bread(relocs, reloc_size, abfd) != reloc_size) {
    free(relocs);
    free(reloc_cache);
    return FALSE;
  }

  cache_ptr = reloc_cache;
  if (each_size == RELOC_EXT_SIZE) {
    struct reloc_ext_external *rptr = (struct reloc_ext_external *)relocs;

    for (; counter < count; counter++, rptr++, cache_ptr++)
      MY_swap_ext_reloc_in(abfd, rptr, cache_ptr, symbols,
                           (bfd_size_type)bfd_get_symcount(abfd));
  } else {
    struct reloc_std_external *rptr = (struct reloc_std_external *)relocs;

    for (; counter < count; counter++, rptr++, cache_ptr++)
      MY_swap_std_reloc_in(abfd, rptr, cache_ptr, symbols,
                           (bfd_size_type)bfd_get_symcount(abfd));
  }

  free(relocs);

  asect->relocation = reloc_cache;
  asect->reloc_count = cache_ptr - reloc_cache;

  return TRUE;
}



long NAME(aout, canonicalize_reloc)(bfd *abfd, sec_ptr section,
                                    arelent **relptr, asymbol **symbols) {
  arelent *tblptr = section->relocation;
  unsigned int count;

  if (section == obj_bsssec(abfd)) {
    *relptr = NULL;
    return 0;
  }

  if (!(tblptr || NAME(aout, slurp_reloc_table)(abfd, section, symbols)))
    return -1;

  if (section->flags & SEC_CONSTRUCTOR) {
    arelent_chain *chain = section->constructor_chain;
    for (count = 0; count < section->reloc_count; count++) {
      *relptr++ = &chain->relent;
      chain = chain->next;
    }
  } else {
    tblptr = section->relocation;

    for (count = 0; count++ < section->reloc_count;) {
      *relptr++ = tblptr++;
    }
  }
  *relptr = 0;

  return section->reloc_count;
}





void _bfd_generic_set_reloc(bfd *abfd ATTRIBUTE_UNUSED, sec_ptr section,
                            arelent **relptr, unsigned int count) {
  section->orelocation = relptr;
  section->reloc_count = count;
}





bfd_boolean NAME(aout, new_section_hook)(bfd *abfd, asection *newsect) {
  /* Align to double at least.  */
  newsect->alignment_power = bfd_get_arch_info(abfd)->section_align_power;

  if (bfd_get_format(abfd) == bfd_object) {
    if (obj_textsec(abfd) == NULL && !strcmp(newsect->name, ".text")) {
      obj_textsec(abfd) = newsect;
      newsect->target_index = N_TEXT;
    } else if (obj_datasec(abfd) == NULL && !strcmp(newsect->name, ".data")) {
      obj_datasec(abfd) = newsect;
      newsect->target_index = N_DATA;
    } else if (obj_bsssec(abfd) == NULL && !strcmp(newsect->name, ".bss")) {
      obj_bsssec(abfd) = newsect;
      newsect->target_index = N_BSS;
    }
  }

  /* We allow more than three sections internally.  */
  return _bfd_generic_new_section_hook(abfd, newsect);
}

#define bfd_section_list_append(ABFD, S)                                       \
  do {                                                                         \
    asection *_s = S;                                                          \
    bfd *_abfd = ABFD;                                                         \
    _s->next = NULL;                                                           \
    if (_abfd->section_last) {                                                 \
      _s->prev = _abfd->section_last;                                          \
      _abfd->section_last->next = _s;                                          \
    } else {                                                                   \
      _s->prev = NULL;                                                         \
      _abfd->sections = _s;                                                    \
    }                                                                          \
    _abfd->section_last = _s;                                                  \
  } while (0)

static asection *bfd_section_init(bfd *abfd, asection *newsect) {
  newsect->id = section_id;
  newsect->index = abfd->section_count;
  newsect->owner = abfd;

  if (!NAME(aout, new_section_hook)(abfd, newsect))
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

static void setup_section(bfd *ibfd, sec_ptr isection, void *obfdarg) {
  bfd *obfd = (bfd *)obfdarg;
  struct section_list *p;
  sec_ptr osection;
  bfd_size_type size;
  bfd_vma vma;
  bfd_vma lma;
  flagword flags;
  const char *err;
  const char *name;
  char *prefix = NULL;
  bfd_boolean make_nobits;

  if (is_strip_section(ibfd, isection))
    return;

  /* Get the, possibly new, name of the output section.  */
  name = bfd_section_name(ibfd, isection);
  flags = bfd_get_section_flags(ibfd, isection);
  name = find_section_rename(name, &flags);

  /* Prefix sections.  */
  if ((prefix_alloc_sections_string) &&
      (bfd_get_section_flags(ibfd, isection) & SEC_ALLOC))
    prefix = prefix_alloc_sections_string;
  else if (prefix_sections_string)
    prefix = prefix_sections_string;

  if (prefix) {
    char *n;

    n = (char *)xmalloc(strlen(prefix) + strlen(name) + 1);
    strcpy(n, prefix);
    strcat(n, name);
    name = n;
  }

  make_nobits = FALSE;

  p = find_section_list(bfd_section_name(ibfd, isection), FALSE,
                        SECTION_CONTEXT_SET_FLAGS);
  if (p != NULL)
    flags = p->flags | (flags & (SEC_HAS_CONTENTS | SEC_RELOC));
  else if (strip_symbols == STRIP_NONDEBUG &&
           (flags & (SEC_ALLOC | SEC_GROUP)) != 0 &&
           !is_nondebug_keep_contents_section(ibfd, isection)) {
    flags &= ~(SEC_HAS_CONTENTS | SEC_LOAD | SEC_GROUP);
    if (obfd->xvec->flavour == bfd_target_elf_flavour) {
      make_nobits = TRUE;

      /* Twiddle the input section flags so that it seems to
         elf.c:copy_private_bfd_data that section flags have not
         changed between input and output sections.  This hack
         prevents wholesale rewriting of the program headers.  */
      isection->flags &= ~(SEC_HAS_CONTENTS | SEC_LOAD | SEC_GROUP);
    }
  }

  osection = bfd_make_section_anyway_with_flags(obfd, name, flags);

  if (osection == NULL) {
    err = _("failed to create output section");
    goto loser;
  }

  if (make_nobits)
    elf_section_type(osection) = SHT_NOBITS;

  size = bfd_section_size(ibfd, isection);
  size = bfd_convert_section_size(ibfd, isection, obfd, size);
  if (copy_byte >= 0)
    size = (size + interleave - 1) / interleave * copy_width;
  else if (extract_symbol)
    size = 0;
  if (!bfd_set_section_size(obfd, osection, size)) {
    err = _("failed to set size");
    goto loser;
  }

  vma = bfd_section_vma(ibfd, isection);
  p = find_section_list(bfd_section_name(ibfd, isection), FALSE,
                        SECTION_CONTEXT_ALTER_VMA | SECTION_CONTEXT_SET_VMA);
  if (p != NULL) {
    if (p->context & SECTION_CONTEXT_SET_VMA)
      vma = p->vma_val;
    else
      vma += p->vma_val;
  } else
    vma += change_section_address;

  if (!bfd_set_section_vma(obfd, osection, vma)) {
    err = _("failed to set vma");
    goto loser;
  }

  lma = isection->lma;
  p = find_section_list(bfd_section_name(ibfd, isection), FALSE,
                        SECTION_CONTEXT_ALTER_LMA | SECTION_CONTEXT_SET_LMA);
  if (p != NULL) {
    if (p->context & SECTION_CONTEXT_ALTER_LMA)
      lma += p->lma_val;
    else
      lma = p->lma_val;
  } else
    lma += change_section_address;

  osection->lma = lma;

  /* FIXME: This is probably not enough.  If we change the LMA we
     may have to recompute the header for the file as well.  */
  if (!bfd_set_section_alignment(obfd, osection,
                                 bfd_section_alignment(ibfd, isection))) {
    err = _("failed to set alignment");
    goto loser;
  }

  /* Copy merge entity size.  */
  osection->entsize = isection->entsize;

  /* Copy compress status.  */
  osection->compress_status = isection->compress_status;

  /* This used to be mangle_section; we do here to avoid using
     bfd_get_section_by_name since some formats allow multiple
     sections with the same name.  */
  isection->output_section = osection;
  isection->output_offset = 0;

  if ((isection->flags & SEC_GROUP) != 0) {
    asymbol *gsym = group_signature(isection);

    if (gsym != NULL) {
      gsym->flags |= BSF_KEEP;
      if (ibfd->xvec->flavour == bfd_target_elf_flavour)
        elf_group_id(isection) = gsym;
    }
  }

  /* Allow the BFD backend to copy any private data it understands
     from the input section to the output section.  */
  if (!bfd_copy_private_section_data(ibfd, isection, obfd, osection)) {
    err = _("failed to copy private data");
    goto loser;
  }

  /* All went well.  */
  return;

loser:
  status = 1;
  bfd_nonfatal_message(NULL, obfd, osection, err);
}


static void copy_relocations_in_section(bfd *ibfd, sec_ptr isection,
                                        void *obfdarg) {
  bfd *obfd = (bfd *)obfdarg;
  long relsize;
  arelent **relpp;
  long relcount;
  sec_ptr osection;

  if (skip_section(ibfd, isection, FALSE))
    return;

  osection = isection->output_section;

  /* Core files and DWO files do not need to be relocated.  */
  if (bfd_get_format(obfd) == bfd_core || strip_symbols == STRIP_NONDWO ||
      discard_relocations(ibfd, isection))
    relsize = 0;
  else {
    relsize = bfd_get_reloc_upper_bound(ibfd, isection);

    if (relsize < 0) {
      /* Do not complain if the target does not support relocations.  */
      if (relsize == -1 && bfd_get_error() == bfd_error_invalid_operation)
        relsize = 0;
      else {
        status = 1;
        bfd_nonfatal_message(NULL, ibfd, isection, NULL);
        return;
      }
    }
  }

  if (relsize == 0) {
    bfd_set_reloc(obfd, osection, NULL, 0);
    osection->flags &= ~SEC_RELOC;
  } else {
    if (isection->orelocation != NULL) {
      /* Some other function has already set up the output relocs
         for us, so scan those instead of the default relocs.  */
      relcount = isection->reloc_count;
      relpp = isection->orelocation;
    } else {
      relpp = (arelent **)xmalloc(relsize);
      relcount = bfd_canonicalize_reloc(ibfd, isection, relpp, isympp);
      if (relcount < 0) {
        status = 1;
        bfd_nonfatal_message(NULL, ibfd, isection,
                             _("relocation count is negative"));
        return;
      }
    }

    if (strip_symbols == STRIP_ALL) {
      /* Remove relocations which are not in
         keep_strip_specific_list.  */
      arelent **temp_relpp;
      long temp_relcount = 0;
      long i;

      temp_relpp = (arelent **)xmalloc(relsize);
      for (i = 0; i < relcount; i++) {
        /* PR 17512: file: 9e907e0c.  */
        if (relpp[i]->sym_ptr_ptr
            /* PR 20096 */
            && *relpp[i]->sym_ptr_ptr)
          if (is_specified_symbol(bfd_asymbol_name(*relpp[i]->sym_ptr_ptr),
                                  keep_specific_htab))
            temp_relpp[temp_relcount++] = relpp[i];
      }
      relcount = temp_relcount;
      if (isection->orelocation == NULL)
        free(relpp);
      relpp = temp_relpp;
    }

    bfd_set_reloc(obfd, osection, relcount == 0 ? NULL : relpp, relcount);
    if (relcount == 0) {
      osection->flags &= ~SEC_RELOC;
      free(relpp);
    }
  }
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


void NAME(aout, swap_std_reloc_out)(bfd *abfd, arelent *g,
                                    struct reloc_std_external *natptr) {
  int r_index;
  asymbol *sym = *(g->sym_ptr_ptr);
  int r_extern;
  unsigned int r_length;
  int r_pcrel;
  int r_baserel, r_jmptable, r_relative;
  asection *output_section = sym->section->output_section;

  PUT_WORD(abfd, g->address, natptr->r_address);

  BFD_ASSERT(g->howto != NULL);
  r_length = g->howto->size;            /* Size as a power of two.  */
  r_pcrel = (int)g->howto->pc_relative; /* Relative to PC?  */
  /* XXX This relies on relocs coming from a.out files.  */
  r_baserel = (g->howto->type & 8) != 0;
  r_jmptable = (g->howto->type & 16) != 0;
  r_relative = (g->howto->type & 32) != 0;

  /* Name was clobbered by aout_write_syms to be symbol index.  */

  /* If this relocation is relative to a symbol then set the
     r_index to the symbols index, and the r_extern bit.

     Absolute symbols can come in in two ways, either as an offset
     from the abs section, or as a symbol which has an abs value.
     check for that here.  */

  if (bfd_is_com_section(output_section) ||
      bfd_is_abs_section(output_section) ||
      bfd_is_und_section(output_section)
      /* PR gas/3041  a.out relocs against weak symbols
         must be treated as if they were against externs.  */
      || (sym->flags & BSF_WEAK)) {
    if (bfd_abs_section_ptr->symbol == sym) {
      /* Whoops, looked like an abs symbol, but is
         really an offset from the abs section.  */
      r_index = N_ABS;
      r_extern = 0;
    } else {
      /* Fill in symbol.  */
      r_extern = 1;
      r_index = (*(g->sym_ptr_ptr))->KEEPIT;
    }
  } else {
    /* Just an ordinary section.  */
    r_extern = 0;
    r_index = output_section->target_index;
  }

  /* Now the fun stuff.  */
  if (bfd_header_big_endian(abfd)) {
    natptr->r_index[0] = r_index >> 16;
    natptr->r_index[1] = r_index >> 8;
    natptr->r_index[2] = r_index;
    natptr->r_type[0] = ((r_extern ? RELOC_STD_BITS_EXTERN_BIG : 0) |
                         (r_pcrel ? RELOC_STD_BITS_PCREL_BIG : 0) |
                         (r_baserel ? RELOC_STD_BITS_BASEREL_BIG : 0) |
                         (r_jmptable ? RELOC_STD_BITS_JMPTABLE_BIG : 0) |
                         (r_relative ? RELOC_STD_BITS_RELATIVE_BIG : 0) |
                         (r_length << RELOC_STD_BITS_LENGTH_SH_BIG));
  } else {
    natptr->r_index[2] = r_index >> 16;
    natptr->r_index[1] = r_index >> 8;
    natptr->r_index[0] = r_index;
    natptr->r_type[0] = ((r_extern ? RELOC_STD_BITS_EXTERN_LITTLE : 0) |
                         (r_pcrel ? RELOC_STD_BITS_PCREL_LITTLE : 0) |
                         (r_baserel ? RELOC_STD_BITS_BASEREL_LITTLE : 0) |
                         (r_jmptable ? RELOC_STD_BITS_JMPTABLE_LITTLE : 0) |
                         (r_relative ? RELOC_STD_BITS_RELATIVE_LITTLE : 0) |
                         (r_length << RELOC_STD_BITS_LENGTH_SH_LITTLE));
  }
}

bfd_boolean NAME(aout, squirt_out_relocs)(bfd *abfd, asection *section) {
  arelent **generic;
  unsigned char *native, *natptr;
  size_t each_size;

  unsigned int count = section->reloc_count;
  bfd_size_type natsize;

  if (count == 0 || section->orelocation == NULL)
    return TRUE;

  each_size = obj_reloc_entry_size(abfd);
  natsize = (bfd_size_type)each_size * count;
  native = (unsigned char *)bfd_zalloc(abfd, natsize);
  if (!native)
    return FALSE;

  generic = section->orelocation;

  if (each_size == RELOC_EXT_SIZE) {
    for (natptr = native; count != 0; --count, natptr += each_size, ++generic) {
      /* PR 20921: If the howto field has not been initialised then skip
         this reloc.
         PR 20929: Similarly for the symbol field.  */
      if ((*generic)->howto == NULL || (*generic)->sym_ptr_ptr == NULL) {
        bfd_set_error(bfd_error_invalid_operation);
        _bfd_error_handler(_("\
%pB: attempt to write out unknown reloc type"),
                           abfd);
        return FALSE;
      }
      MY_swap_ext_reloc_out(abfd, *generic,
                            (struct reloc_ext_external *)natptr);
    }
  } else {
    for (natptr = native; count != 0; --count, natptr += each_size, ++generic) {
      if ((*generic)->howto == NULL || (*generic)->sym_ptr_ptr == NULL) {
        bfd_set_error(bfd_error_invalid_operation);
        _bfd_error_handler(_("\
%pB: attempt to write out unknown reloc type"),
                           abfd);
        return FALSE;
      }
      MY_swap_std_reloc_out(abfd, *generic,
                            (struct reloc_std_external *)natptr);
    }
  }

  if (bfd_bwrite((void *)native, natsize, abfd) != natsize) {
    bfd_release(abfd, native);
    return FALSE;
  }
  bfd_release(abfd, native);

  return TRUE;
}

#define WRITE_HEADERS(abfd, execp)                                             \
  {                                                                            \
    if (adata(abfd).magic == undecided_magic)                                  \
      NAME(aout, adjust_sizes_and_vmas)(abfd);                                 \
                                                                               \
    execp->a_syms = bfd_get_symcount(abfd) * EXTERNAL_NLIST_SIZE;              \
    execp->a_entry = bfd_get_start_address(abfd);                              \
                                                                               \
    execp->a_trsize =                                                          \
        ((obj_textsec(abfd)->reloc_count) * obj_reloc_entry_size(abfd));       \
    execp->a_drsize =                                                          \
        ((obj_datasec(abfd)->reloc_count) * obj_reloc_entry_size(abfd));       \
    NAME(aout, swap_exec_header_out)(abfd, execp, &exec_bytes);                \
                                                                               \
    if (bfd_seek(abfd, (file_ptr)0, SEEK_SET) != 0 ||                          \
        bfd_bwrite(&exec_bytes, (bfd_size_type)EXEC_BYTES_SIZE, abfd) !=       \
            EXEC_BYTES_SIZE)                                                   \
      return FALSE;                                                            \
    /* Now write out reloc info, followed by syms and strings.  */             \
                                                                               \
    if (bfd_get_outsymbols(abfd) != NULL && bfd_get_symcount(abfd) != 0) {     \
      if (bfd_seek(abfd, (file_ptr)(N_SYMOFF(execp)), SEEK_SET) != 0)          \
        return FALSE;                                                          \
                                                                               \
      if (!NAME(aout, write_syms)(abfd))                                       \
        return FALSE;                                                          \
    }                                                                          \
                                                                               \
    if (bfd_seek(abfd, (file_ptr)(N_TRELOFF(execp)), SEEK_SET) != 0)           \
      return FALSE;                                                            \
    if (!NAME(aout, squirt_out_relocs)(abfd, obj_textsec(abfd)))               \
      return FALSE;                                                            \
                                                                               \
    if (bfd_seek(abfd, (file_ptr)(N_DRELOFF(execp)), SEEK_SET) != 0)           \
      return FALSE;                                                            \
    if (!NAME(aout, squirt_out_relocs)(abfd, obj_datasec(abfd)))               \
      return FALSE;                                                            \
  }

static bfd_boolean i386linux_write_object_contents(bfd *abfd) {
  struct external_exec exec_bytes;
  struct internal_exec *execp = exec_hdr(abfd);

  N_SET_MACHTYPE(execp, M_386);

  obj_reloc_entry_size(abfd) = RELOC_STD_SIZE;

  WRITE_HEADERS(abfd, execp);

  return TRUE;
}

bfd_boolean bfd_close(bfd *abfd) {
  if (bfd_write_p(abfd)) {
    if (!i386linux_write_object_contents(abfd))
      return FALSE;
  }

  return bfd_close_all_done(abfd);
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
