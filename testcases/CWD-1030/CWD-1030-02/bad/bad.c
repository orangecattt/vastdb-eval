#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

typedef uint64_t bfd_vma;
typedef uint64_t bfd_size_type;
typedef int64_t file_ptr;
typedef struct bfd_section asection;

#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))

#define BYTE_GET(field)		byte_get (field, sizeof (field))
#define BYTE_GET_SIGNED(field)	byte_get_signed (field, sizeof (field))

#define LONG_HEX LONG_HEX

#define EI_DATA		5
#define ELFDATA2MSB	2

#define ET_DYN		3
#define ET_EXEC		2

#define SHT_PROGBITS	1

#define STT_SECTION	3
#define STT_GNU_IFUNC	10
#define ELF_ST_TYPE(val)		((val) & 0xF)
#define ELF64_MIPS_R_TYPE3(i) (((i) >> 16) & 0xff)
#define ELF64_MIPS_R_TYPE2(i) (((i) >> 8) & 0xff)
#define ELF64_R_TYPE_DATA(info)	(((info) >> 32) & 0xfffffff)

#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_JMPREL	23
#define DT_PLTRELSZ	2
#define DT_RELRSZ	35
#define DT_RELR		36
#define DT_RELRENT	37
#define DT_PLTREL	20
#define DT_RELENT	19
#define DT_RELAENT	9

#define EM_NONE		  0
#define EM_386		  3
#define EM_68K		  4
#define EM_860		  7
#define EM_MIPS		  8
#define EM_MIPS_RS3_LE	 10
#define EM_OLD_SPARCV9	 11
#define EM_SPARC32PLUS	 18
#define EM_960		 19
#define EM_PARISC	 15
#define EM_PPC		 20
#define EM_PPC64	 21
#define EM_S390		 22
#define EM_S390_OLD	 22
#define EM_SPU		 23
#define EM_V800		 36
#define EM_MCORE	 39
#define EM_ARM		 40
#define EM_SH		 42
#define EM_SPARCV9	 43
#define EM_ARC		 45
#define EM_H8_300	 46
#define EM_H8_300H	 47
#define EM_H8S		 48
#define EM_ALPHA	 41
#define EM_AARCH64	 183
#define EM_M32R		 88
#define EM_CYGNUS_M32R	 88
#define EM_68HC11	 70
#define EM_68HC12	 53
#define EM_S12Z		 164
#define EM_AVR		 83
#define EM_AVR_OLD	 83
#define EM_SPARC	 2
#define EM_V850		 87
#define EM_CYGNUS_V850	 87
#define EM_D10V		 84
#define EM_CYGNUS_D10V	 84
#define EM_D30V		 85
#define EM_CYGNUS_D30V	 85
#define EM_DLX		 0x5aa5
#define EM_MN10300	 89
#define EM_CYGNUS_MN10300 89
#define EM_MN10200	 90
#define EM_CYGNUS_MN10200 90
#define EM_FR30		 91
#define EM_CYGNUS_FR30	 91
#define EM_CYGNUS_FRV	 0x5441
#define EM_CSKY		 252
#define EM_FT32		 0x10
#define EM_MSP430	 105
#define EM_MSP430_OLD	 105
#define EM_NDS32	 167
#define EM_RISCV	 243
#define EM_ARC_COMPACT	 93
#define EM_ARC_COMPACT2	 195
#define EM_ARC_COMPACT3	 231
#define EM_ARC_COMPACT3_64 232
#define EM_H8_300H	 47
#define EM_OR1K		 92
#define EM_PJ		 95
#define EM_PJ_OLD		 95
#define EM_IA_64	 50
#define EM_KVX		 255
#define EM_CRIS		 76
#define EM_X86_64	 62
#define EM_L1OM		 184
#define EM_K1OM		 185
#define EM_S370		 9
#define EM_SCORE	 135
#define EM_XSTORMY16	 177
#define EM_CRX		 114
#define EM_VAX		 75
#define EM_VISIUM	 178
#define EM_BPF		 247
#define EM_ADAPTEVA_EPIPHANY 168
#define EM_IP2K		 101
#define EM_IP2K_OLD	 101
#define EM_IQ2000	 113
#define EM_XTENSA	 94
#define EM_XTENSA_OLD	 94
#define EM_LATTICEMICO32 111
#define EM_M32C		 118
#define EM_MT		 179
#define EM_MMIX		 80
#define EM_MOXIE        223
#define EM_BLACKFIN	 106
#define EM_CYGNUS_MEP	 0x1992
#define EM_CR16		 115
#define EM_MICROBLAZE	 189
#define EM_RL78		 197
#define EM_RX		 198
#define EM_METAG		 174
#define EM_TI_C6000	 140
#define EM_MICROBLAZE_OLD 0xbaab
#define EM_TILEGX	 191
#define EM_TILEPRO	 188
#define EM_WEBASSEMBLY	 161
#define EM_XGATE	 156
#define EM_ALTERA_NIOS2 113
#define EM_TI_PRU	 144
#define EM_NFP		 199
#define EM_Z80		 249
#define EM_LOONGARCH	 258
#define EM_AMDGPU	 236
#define EM_IAMCU	 6
#define EM_M32C_OLD	 118

#define E_NFP_MACH_3200 0x10
#define EF_NFP_MACH(flags) ((flags) & 0xff)

#define LITUSE_ALPHA_ADDR 0
#define LITUSE_ALPHA_BASE 1
#define LITUSE_ALPHA_BYTOFF 2
#define LITUSE_ALPHA_JSR 3
#define LITUSE_ALPHA_TLSGD 4
#define LITUSE_ALPHA_TLSLDM 5
#define LITUSE_ALPHA_JSRDIRECT 6



typedef enum print_mode
{
  HEX,
  HEX_5,
  DEC,
  DEC_5,
  UNSIGNED,
  UNSIGNED_5,
  PREFIX_HEX,
  PREFIX_HEX_5,
  FULL_HEX,
  LONG_HEX,
  ZERO_HEX,
  OCTAL,
  OCTAL_5
} print_mode;

typedef struct elf_internal_sym {
  bfd_vma	st_value;
  bfd_vma	st_size;
  unsigned long	st_name;
  unsigned char	st_info;
  unsigned char	st_other;
  unsigned char st_target_internal;
  unsigned int  st_shndx;
} Elf_Internal_Sym;

typedef struct elf_internal_rela {
  bfd_vma	r_offset;
  bfd_vma	r_info;
  bfd_vma	r_addend;
} Elf_Internal_Rela;

typedef struct {
  unsigned char r_offset[4];
  unsigned char	r_info[4];
  unsigned char	r_addend[4];
} Elf32_External_Rela;

typedef struct {
  unsigned char r_offset[8];
  unsigned char	r_info[8];
  unsigned char	r_addend[8];
} Elf64_External_Rela;

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

typedef struct elf_internal_ehdr {
  unsigned char		e_ident[16];
  bfd_vma		e_entry;
  bfd_size_type		e_phoff;
  bfd_size_type		e_shoff;
  unsigned long		e_version;
  unsigned long		e_flags;
  unsigned short	e_type;
  unsigned short	e_machine;
  unsigned int		e_ehsize;
  unsigned int		e_phentsize;
  unsigned int		e_phnum;
  unsigned int		e_shentsize;
  unsigned int		e_shnum;
  unsigned int		e_shstrndx;
} Elf_Internal_Ehdr;

typedef struct elf_internal_phdr Elf_Internal_Phdr;

typedef struct elf_internal_dyn {
  bfd_vma d_tag;
  union {
    bfd_vma	d_val;
    bfd_vma	d_ptr;
  } d_un;
} Elf_Internal_Dyn;

typedef struct
{
  unsigned short int 	si_boundto;
  unsigned short int	si_flags;
} Elf_Internal_Syminfo;

typedef enum
{
  reltype_unknown,
  reltype_rel,
  reltype_rela,
  reltype_relr
} relocation_type;

enum versioned_symbol_info
{
  symbol_undefined,
  symbol_hidden,
  symbol_public
};

typedef struct elf_relocation
{
  bfd_vma r_offset;
  bfd_vma r_addend;
  const char *r_name;
  char *r_symbol;
  relocation_type r_type;
} elf_relocation;

typedef struct elf_section_list
{
  Elf_Internal_Shdr *        hdr;
  struct elf_section_list *  next;
} elf_section_list;

typedef unsigned char dump_type;

struct dump_data
{
  dump_type *          dump_sects;
  unsigned int         num_dump_sects;
};

typedef struct filedata
{
  const char *         file_name;
  bool                 is_separate;
  FILE *               handle;
  uint64_t             file_size;
  Elf_Internal_Ehdr    file_header;
  uint64_t             archive_file_offset;
  uint64_t             archive_file_size;
  Elf_Internal_Shdr *  section_headers;
  Elf_Internal_Phdr *  program_headers;
  char *               string_table;
  uint64_t             string_table_length;
  uint64_t             dynamic_addr;
  uint64_t             dynamic_size;
  uint64_t             dynamic_nent;
  Elf_Internal_Dyn *   dynamic_section;
  Elf_Internal_Shdr *  dynamic_strtab_section;
  char *               dynamic_strings;
  uint64_t             dynamic_strings_length;
  Elf_Internal_Shdr *  dynamic_symtab_section;
  uint64_t             num_dynamic_syms;
  Elf_Internal_Sym *   dynamic_symbols;
  uint64_t             version_info[16];
  unsigned int         dynamic_syminfo_nent;
  Elf_Internal_Syminfo * dynamic_syminfo;
  uint64_t             dynamic_syminfo_offset;
  uint64_t             nbuckets;
  uint64_t             nchains;
  uint64_t *           buckets;
  uint64_t *           chains;
  uint64_t             ngnubuckets;
  uint64_t             ngnuchains;
  uint64_t *           gnubuckets;
  uint64_t *           gnuchains;
  uint64_t *           mipsxlat;
  uint64_t             gnusymidx;
  char *               program_interpreter;
  uint64_t             dynamic_info[DT_RELRENT + 1];
  uint64_t             dynamic_info_DT_GNU_HASH;
  uint64_t             dynamic_info_DT_MIPS_XHASH;
  elf_section_list *   symtab_shndx_list;
  size_t               group_count;
  struct group *       section_groups;
  struct group **      section_headers_groups;
  struct dump_data     dump;
} Filedata;

struct group_list
{
  struct group_list *  next;
  unsigned int         section_index;
};

struct group
{
  struct group_list *  root;
  unsigned int         group_index;
};

typedef struct separate_info
{
  void *                  handle;
  const char *            filename;
  struct separate_info *  next;
} separate_info;

static bool do_got_section_contents = false;
static bool do_wide = false;
static bool is_32bit_elf = false;
static bool do_reloc = false;
static bool do_using_dynamic = false;
static bool do_arch = false;
static bool do_dump = false;
static bool do_syms = false;
static bool do_dyn_syms = false;
static bool do_unwind = false;
static bool do_version = false;
static bool process_links = false;
static bool show_name = false;

static elf_relocation *all_relocations_root;
static elf_relocation *all_relocations;
static size_t all_relocations_count;

static separate_info *first_separate_info;

static struct
{
  const char * name;
  int reloc;
  int size;
  relocation_type rel_type;
}
  dynamic_relocations [] =
{
  { "REL", DT_REL, DT_RELSZ, reltype_rel },
  { "RELA", DT_RELA, DT_RELASZ, reltype_rela },
  { "RELR", DT_RELR, DT_RELRSZ, reltype_relr },
  { "PLT", DT_JMPREL, DT_PLTRELSZ, reltype_unknown }
};

extern void *xmalloc (size_t);
extern void *xrealloc (void *, size_t);
extern void *cmalloc (size_t, size_t);
extern char *xstrdup (const char *);
extern char *concat (const char *, ...);

extern void *get_data (void *, Filedata *, uint64_t, uint64_t, uint64_t, const char *);
extern unsigned char *get_section_contents (Elf_Internal_Shdr *, Filedata *);
extern void error (const char *, ...);
extern const char *_(const char *);

extern int64_t byte_get_signed (const void *, size_t);
extern uint64_t byte_get (const void *, size_t);

extern const char *printable_section_name (Filedata *, Elf_Internal_Shdr *);
extern const char *printable_section_name_from_index (Filedata *, unsigned int, const char *);

extern bool get_file_header (Filedata *);
extern bool get_section_headers (Filedata *, bool);
extern bool process_file_header (Filedata *);
extern bool process_section_headers (Filedata *);
extern bool process_section_groups (Filedata *);
extern bool process_program_headers (Filedata *);
extern bool process_dynamic_section (Filedata *);
static bool process_relocs (Filedata *);
extern bool process_unwind (Filedata *);
extern bool process_symbol_table (Filedata *);
extern bool process_lto_symbol_tables (Filedata *);
extern bool process_syminfo (Filedata *);
extern bool process_version_sections (Filedata *);
extern bool process_notes (Filedata *);
extern bool process_gnu_liblist (Filedata *);
extern bool process_arch_specific (Filedata *);
extern bool process_section_contents (Filedata *);
extern bool display_relocations (Elf_Internal_Shdr *, Filedata *, bool);
extern bool process_mips_specific (Filedata *, bool);
extern bool process_ia64_vms_dynamic_relocs (Filedata *);
extern bool is_ia64_vms (Filedata *);
extern bool might_need_separate_debug_info (Filedata *);
extern bool load_separate_debug_files (Filedata *, const char *);
extern bool slurp_rel_relocs (Filedata *, uint64_t, uint64_t, Elf_Internal_Rela **, uint64_t *);
extern bool guess_is_rela (unsigned int);
extern void dump_relr_relocations (Filedata *, uint64_t, uint64_t, uint64_t, uint64_t *, Elf_Internal_Sym *, uint64_t, char *, uint64_t, bool);
extern bool uses_msp430x_relocs (Filedata *);

extern void initialise_dump_sects (Filedata *);
extern void initialise_dumps_byname (Filedata *);
extern void free_filedata (Filedata *);
extern void free_debug_memory (void);

extern uint64_t offset_from_vma (Filedata *, uint64_t, uint64_t);

extern void print_vma (uint64_t, print_mode);
extern unsigned int print_symbol_name (unsigned int, const char *);
extern void display_elf_relocation_at (uint64_t, uint64_t);

extern const char *get_symbol_version_string (Filedata *, bool, const char *, size_t, unsigned, Elf_Internal_Sym *, enum versioned_symbol_info *, unsigned short *);

extern uint64_t get_reloc_type (Filedata *, uint64_t);
extern uint64_t get_reloc_symindex (uint64_t);
extern int elf_relocation_cmp (const void *, const void *);

extern bool startswith (const char *, const char *);
extern int streq (const char *, const char *);

extern const char *elf_aarch64_reloc_type (uint64_t);
extern const char *elf_alpha_reloc_type (uint64_t);
extern const char *elf_amdgpu_reloc_type (uint64_t);
extern const char *elf_arc_reloc_type (uint64_t);
extern const char *elf_arm_reloc_type (uint64_t);
extern const char *elf_avr_reloc_type (uint64_t);
extern const char *elf_bfin_reloc_type (uint64_t);
extern const char *elf_bpf_reloc_type (uint64_t);
extern const char *elf_cr16_reloc_type (uint64_t);
extern const char *elf_cris_reloc_type (uint64_t);
extern const char *elf_crx_reloc_type (uint64_t);
extern const char *elf_csky_reloc_type (uint64_t);
extern const char *elf_d10v_reloc_type (uint64_t);
extern const char *elf_d30v_reloc_type (uint64_t);
extern const char *elf_dlx_reloc_type (uint64_t);
extern const char *elf_epiphany_reloc_type (uint64_t);
extern const char *elf_fr30_reloc_type (uint64_t);
extern const char *elf_frv_reloc_type (uint64_t);
extern const char *elf_ft32_reloc_type (uint64_t);
extern const char *elf_h8_reloc_type (uint64_t);
extern const char *elf_hppa_reloc_type (uint64_t);
extern const char *elf_i386_reloc_type (uint64_t);
extern const char *elf_i860_reloc_type (uint64_t);
extern const char *elf_i960_reloc_type (uint64_t);
extern const char *elf_ia64_reloc_type (uint64_t);
extern const char *elf_ip2k_reloc_type (uint64_t);
extern const char *elf_iq2000_reloc_type (uint64_t);
extern const char *elf_kvx_reloc_type (uint64_t);
extern const char *elf_lm32_reloc_type (uint64_t);
extern const char *elf_loongarch_reloc_type (uint64_t);
extern const char *elf_m32c_reloc_type (uint64_t);
extern const char *elf_m32r_reloc_type (uint64_t);
extern const char *elf_m68hc11_reloc_type (uint64_t);
extern const char *elf_m68k_reloc_type (uint64_t);
extern const char *elf_mcore_reloc_type (uint64_t);
extern const char *elf_mep_reloc_type (uint64_t);
extern const char *elf_metag_reloc_type (uint64_t);
extern const char *elf_microblaze_reloc_type (uint64_t);
extern const char *elf_mips_reloc_type (uint64_t);
extern const char *elf_mmix_reloc_type (uint64_t);
extern const char *elf_mn10200_reloc_type (uint64_t);
extern const char *elf_mn10300_reloc_type (uint64_t);
extern const char *elf_moxie_reloc_type (uint64_t);
extern const char *elf_msp430_reloc_type (uint64_t);
extern const char *elf_msp430x_reloc_type (uint64_t);
extern const char *elf_mt_reloc_type (uint64_t);
extern const char *elf_nds32_reloc_type (uint64_t);
extern const char *elf_nfp_reloc_type (uint64_t);
extern const char *elf_nfp3200_reloc_type (uint64_t);
extern const char *elf_nios2_reloc_type (uint64_t);
extern const char *elf_or1k_reloc_type (uint64_t);
extern const char *elf_pj_reloc_type (uint64_t);
extern const char *elf_ppc_reloc_type (uint64_t);
extern const char *elf_ppc64_reloc_type (uint64_t);
extern const char *elf_pru_reloc_type (uint64_t);
extern const char *elf_riscv_reloc_type (uint64_t);
extern const char *elf_rl78_reloc_type (uint64_t);
extern const char *elf_rx_reloc_type (uint64_t);
extern const char *elf_s12z_reloc_type (uint64_t);
extern const char *elf_s390_reloc_type (uint64_t);
extern const char *elf_score_reloc_type (uint64_t);
extern const char *elf_sh_reloc_type (uint64_t);
extern const char *elf_sparc_reloc_type (uint64_t);
extern const char *elf_spu_reloc_type (uint64_t);
extern const char *elf_tic6x_reloc_type (uint64_t);
extern const char *elf_tilegx_reloc_type (uint64_t);
extern const char *elf_tilepro_reloc_type (uint64_t);
extern const char *elf_vax_reloc_type (uint64_t);
extern const char *elf_visium_reloc_type (uint64_t);
extern const char *elf_wasm32_reloc_type (uint64_t);
extern const char *elf_x86_64_reloc_type (uint64_t);
extern const char *elf_xgate_reloc_type (uint64_t);
extern const char *elf_xstormy16_reloc_type (uint64_t);
extern const char *elf_xtensa_reloc_type (uint64_t);
extern const char *elf_z80_reloc_type (uint64_t);
extern const char *i370_reloc_type (uint64_t);
extern const char *v800_reloc_type (uint64_t);
extern const char *v850_reloc_type (uint64_t);

extern const char *elf_s12z_reloc_type (uint64_t);

static void
update_all_relocations (size_t nentries)
{
  size_t sz;

  if (!do_got_section_contents)
    return;

  if (!all_relocations_root)
    {
      sz = nentries * sizeof (elf_relocation);
      all_relocations_root = (elf_relocation *) xmalloc (sz);
      all_relocations = all_relocations_root;
      all_relocations_count = nentries;
    }
  else
    {
      size_t orig_count = all_relocations_count;
      sz = (orig_count + nentries) * sizeof (elf_relocation);
      all_relocations_root = (elf_relocation *)
	xrealloc (all_relocations_root, sz);
      all_relocations = all_relocations_root + orig_count;
      all_relocations_count += nentries;
    }
}

static bool
slurp_rela_relocs (Filedata *filedata,
		   uint64_t rel_offset,
		   uint64_t rel_size,
		   Elf_Internal_Rela **relasp,
		   uint64_t *nrelasp)
{
  Elf_Internal_Rela * relas;
  uint64_t nrelas;
  unsigned int i;

  if (is_32bit_elf)
    {
      Elf32_External_Rela * erelas;

      erelas = (Elf32_External_Rela *) get_data (NULL, filedata, rel_offset, 1,
                                                 rel_size, _("32-bit relocation data"));
      if (!erelas)
	return false;

      nrelas = rel_size / sizeof (Elf32_External_Rela);

      relas = (Elf_Internal_Rela *) cmalloc (nrelas,
                                             sizeof (Elf_Internal_Rela));

      if (relas == NULL)
	{
	  free (erelas);
	  error (_("out of memory parsing relocs\n"));
	  return false;
	}

      for (i = 0; i < nrelas; i++)
	{
	  relas[i].r_offset = BYTE_GET (erelas[i].r_offset);
	  relas[i].r_info   = BYTE_GET (erelas[i].r_info);
	  relas[i].r_addend = BYTE_GET_SIGNED (erelas[i].r_addend);
	}

      free (erelas);
    }
  else
    {
      Elf64_External_Rela * erelas;

      erelas = (Elf64_External_Rela *) get_data (NULL, filedata, rel_offset, 1,
                                                 rel_size, _("64-bit relocation data"));
      if (!erelas)
	return false;

      nrelas = rel_size / sizeof (Elf64_External_Rela);

      relas = (Elf_Internal_Rela *) cmalloc (nrelas,
                                             sizeof (Elf_Internal_Rela));

      if (relas == NULL)
	{
	  free (erelas);
	  error (_("out of memory parsing relocs\n"));
	  return false;
	}

      for (i = 0; i < nrelas; i++)
	{
	  relas[i].r_offset = BYTE_GET (erelas[i].r_offset);
	  relas[i].r_info   = BYTE_GET (erelas[i].r_info);
	  relas[i].r_addend = BYTE_GET_SIGNED (erelas[i].r_addend);

	  if (filedata->file_header.e_machine == EM_MIPS
	      && filedata->file_header.e_ident[EI_DATA] != ELFDATA2MSB)
	    {
	      /* In little-endian objects, r_info isn't really a
		 64-bit little-endian value: it has a 32-bit
		 little-endian symbol index followed by four
		 individual byte fields.  Reorder INFO
		 accordingly.  */
	      uint64_t inf = relas[i].r_info;
	      inf = (((inf & 0xffffffff) << 32)
		      | ((inf >> 56) & 0xff)
		      | ((inf >> 40) & 0xff00)
		      | ((inf >> 24) & 0xff0000)
		      | ((inf >> 8) & 0xff000000));
	      relas[i].r_info = inf;
	    }
	}

      free (erelas);
    }

  *relasp = relas;
  *nrelasp = nrelas;
  return true;
}

static bool
dump_relocations (Filedata *          filedata,
		  uint64_t            rel_offset,
		  uint64_t            rel_size,
		  Elf_Internal_Sym *  symtab,
		  uint64_t            nsyms,
		  char *              strtab,
		  uint64_t            strtablen,
		  relocation_type     rel_type,
		  bool                is_dynsym,
		  bool                dump_reloc)
{
  size_t i;
  Elf_Internal_Rela * rels;
  bool res = true;

  if (rel_type == reltype_unknown)
    rel_type = guess_is_rela (filedata->file_header.e_machine) ? reltype_rela : reltype_rel;

  if (rel_type == reltype_rela)
    {
      if (!slurp_rela_relocs (filedata, rel_offset, rel_size, &rels, &rel_size))
	return false;
    }
  else if (rel_type == reltype_rel)
    {
      if (!slurp_rel_relocs (filedata, rel_offset, rel_size, &rels, &rel_size))
	return false;
    }
  else if (rel_type == reltype_relr)
    {
      /* This should have been handled by display_relocations().  */
      return false;
    }

  if (dump_reloc)
    {
      if (is_32bit_elf)
	{
	  if (rel_type == reltype_rela)
	    {
	      if (do_wide)
		printf (_(" Offset     Info    Type                Sym. Value  Symbol's Name + Addend\n"));
	      else
		printf (_(" Offset     Info    Type            Sym.Value  Sym. Name + Addend\n"));
	    }
	  else
	    {
	      if (do_wide)
		printf (_(" Offset     Info    Type                Sym. Value  Symbol's Name\n"));
	      else
		printf (_(" Offset     Info    Type            Sym.Value  Sym. Name\n"));
	    }
	}
      else if (rel_type == reltype_rela)
	{
	  if (do_wide)
	    printf (_("    Offset             Info             Type               Symbol's Value  Symbol's Name + Addend\n"));
	  else
	    printf (_("  Offset          Info           Type           Sym. Value    Sym. Name + Addend\n"));
	}
      else
	{
	  if (do_wide)
	    printf (_("    Offset             Info             Type               Symbol's Value  Symbol's Name\n"));
	  else
	    printf (_("  Offset          Info           Type           Sym. Value    Sym. Name\n"));
	}
    }

  for (i = 0; i < rel_size; i++)
    {
      const char * rtype;
      uint64_t offset;
      uint64_t inf;
      uint64_t symtab_index;
      uint64_t type;

      offset = rels[i].r_offset;
      inf    = rels[i].r_info;

      type = get_reloc_type (filedata, inf);
      symtab_index = get_reloc_symindex  (inf);

      if (dump_reloc)
	{
	  if (is_32bit_elf)
	    printf ("%8.8" PRIx32 "  %8.8" PRIx32 " ",
		    (uint32_t) offset, (uint32_t) inf);
	  else
	    printf (do_wide
		    ? "%16.16" PRIx64 "  %16.16" PRIx64 " "
		    : "%12.12" PRIx64 "  %12.12" PRIx64 " ",
		    offset, inf);
	}

      switch (filedata->file_header.e_machine)
	{
	default:
	  rtype = NULL;
	  break;

	case EM_AARCH64:
	  rtype = elf_aarch64_reloc_type (type);
	  break;

	case EM_M32R:
	  rtype = elf_m32r_reloc_type (type);
	  break;

	case EM_386:
	case EM_IAMCU:
	  rtype = elf_i386_reloc_type (type);
	  break;

	case EM_68HC11:
	case EM_68HC12:
	  rtype = elf_m68hc11_reloc_type (type);
	  break;

	case EM_S12Z:
	  rtype = elf_s12z_reloc_type (type);
	  break;

	case EM_68K:
	  rtype = elf_m68k_reloc_type (type);
	  break;

	case EM_960:
	  rtype = elf_i960_reloc_type (type);
	  break;

	case EM_AVR:
	  rtype = elf_avr_reloc_type (type);
	  break;

	case EM_OLD_SPARCV9:
	case EM_SPARC32PLUS:
	case EM_SPARCV9:
	case EM_SPARC:
	  rtype = elf_sparc_reloc_type (type);
	  break;

	case EM_SPU:
	  rtype = elf_spu_reloc_type (type);
	  break;

	case EM_V800:
	  rtype = v800_reloc_type (type);
	  break;
	case EM_V850:
	  rtype = v850_reloc_type (type);
	  break;

	case EM_D10V:
	  rtype = elf_d10v_reloc_type (type);
	  break;

	case EM_D30V:
	  rtype = elf_d30v_reloc_type (type);
	  break;

	case EM_DLX:
	  rtype = elf_dlx_reloc_type (type);
	  break;

	case EM_SH:
	  rtype = elf_sh_reloc_type (type);
	  break;

	case EM_MN10300:
	  rtype = elf_mn10300_reloc_type (type);
	  break;

	case EM_MN10200:
	  rtype = elf_mn10200_reloc_type (type);
	  break;

	case EM_FR30:
	  rtype = elf_fr30_reloc_type (type);
	  break;

	case EM_CYGNUS_FRV:
	  rtype = elf_frv_reloc_type (type);
	  break;

	case EM_CSKY:
	  rtype = elf_csky_reloc_type (type);
	  break;

	case EM_FT32:
	  rtype = elf_ft32_reloc_type (type);
	  break;

	case EM_MCORE:
	  rtype = elf_mcore_reloc_type (type);
	  break;

	case EM_MMIX:
	  rtype = elf_mmix_reloc_type (type);
	  break;

	case EM_MOXIE:
	  rtype = elf_moxie_reloc_type (type);
	  break;

	case EM_MSP430:
	  if (uses_msp430x_relocs (filedata))
	    {
	      rtype = elf_msp430x_reloc_type (type);
	      break;
	    }
	  rtype = elf_msp430_reloc_type (type);
	  break;

	case EM_NDS32:
	  rtype = elf_nds32_reloc_type (type);
	  break;

	case EM_PPC:
	  rtype = elf_ppc_reloc_type (type);
	  break;

	case EM_PPC64:
	  rtype = elf_ppc64_reloc_type (type);
	  break;

	case EM_MIPS:
	case EM_MIPS_RS3_LE:
	  rtype = elf_mips_reloc_type (type);
	  break;

	case EM_RISCV:
	  rtype = elf_riscv_reloc_type (type);
	  break;

	case EM_ALPHA:
	  rtype = elf_alpha_reloc_type (type);
	  break;

	case EM_ARM:
	  rtype = elf_arm_reloc_type (type);
	  break;

	case EM_ARC:
	case EM_ARC_COMPACT:
	case EM_ARC_COMPACT2:
	case EM_ARC_COMPACT3:
	case EM_ARC_COMPACT3_64:
	  rtype = elf_arc_reloc_type (type);
	  break;

	case EM_PARISC:
	  rtype = elf_hppa_reloc_type (type);
	  break;

	case EM_H8_300:
	case EM_H8_300H:
	case EM_H8S:
	  rtype = elf_h8_reloc_type (type);
	  break;

	case EM_OR1K:
	  rtype = elf_or1k_reloc_type (type);
	  break;

	case EM_PJ:
	  rtype = elf_pj_reloc_type (type);
	  break;
	case EM_IA_64:
	  rtype = elf_ia64_reloc_type (type);
	  break;

	case EM_KVX:
	  rtype = elf_kvx_reloc_type (type);
	  break;

	case EM_CRIS:
	  rtype = elf_cris_reloc_type (type);
	  break;

	case EM_860:
	  rtype = elf_i860_reloc_type (type);
	  break;

	case EM_X86_64:
	case EM_L1OM:
	case EM_K1OM:
	  rtype = elf_x86_64_reloc_type (type);
	  break;

	case EM_S370:
	  rtype = i370_reloc_type (type);
	  break;

	case EM_S390:
	  rtype = elf_s390_reloc_type (type);
	  break;

	case EM_SCORE:
	  rtype = elf_score_reloc_type (type);
	  break;

	case EM_XSTORMY16:
	  rtype = elf_xstormy16_reloc_type (type);
	  break;

	case EM_CRX:
	  rtype = elf_crx_reloc_type (type);
	  break;

	case EM_VAX:
	  rtype = elf_vax_reloc_type (type);
	  break;

	case EM_VISIUM:
	  rtype = elf_visium_reloc_type (type);
	  break;

        case EM_BPF:
          rtype = elf_bpf_reloc_type (type);
          break;

	case EM_ADAPTEVA_EPIPHANY:
	  rtype = elf_epiphany_reloc_type (type);
	  break;

	case EM_IP2K:
	  rtype = elf_ip2k_reloc_type (type);
	  break;

	case EM_IQ2000:
	  rtype = elf_iq2000_reloc_type (type);
	  break;

	case EM_XTENSA:
	  rtype = elf_xtensa_reloc_type (type);
	  break;

	case EM_LATTICEMICO32:
	  rtype = elf_lm32_reloc_type (type);
	  break;

	case EM_M32C:
	  rtype = elf_m32c_reloc_type (type);
	  break;

	case EM_MT:
	  rtype = elf_mt_reloc_type (type);
	  break;

	case EM_BLACKFIN:
	  rtype = elf_bfin_reloc_type (type);
	  break;

	case EM_CYGNUS_MEP:
	  rtype = elf_mep_reloc_type (type);
	  break;

	case EM_CR16:
	  rtype = elf_cr16_reloc_type (type);
	  break;

	case EM_MICROBLAZE:
	case EM_MICROBLAZE_OLD:
	  rtype = elf_microblaze_reloc_type (type);
	  break;

	case EM_RL78:
	  rtype = elf_rl78_reloc_type (type);
	  break;

	case EM_RX:
	  rtype = elf_rx_reloc_type (type);
	  break;

	case EM_METAG:
	  rtype = elf_metag_reloc_type (type);
	  break;

	case EM_TI_C6000:
	  rtype = elf_tic6x_reloc_type (type);
	  break;

	case EM_TILEGX:
	  rtype = elf_tilegx_reloc_type (type);
	  break;

	case EM_TILEPRO:
	  rtype = elf_tilepro_reloc_type (type);
	  break;

	case EM_WEBASSEMBLY:
	  rtype = elf_wasm32_reloc_type (type);
	  break;

	case EM_XGATE:
	  rtype = elf_xgate_reloc_type (type);
	  break;

	case EM_TI_PRU:
	  rtype = elf_pru_reloc_type (type);
	  break;

	case EM_NFP:
	  if (EF_NFP_MACH (filedata->file_header.e_flags) == E_NFP_MACH_3200)
	    rtype = elf_nfp3200_reloc_type (type);
	  else
	    rtype = elf_nfp_reloc_type (type);
	  break;

	case EM_Z80:
	  rtype = elf_z80_reloc_type (type);
	  break;

	case EM_LOONGARCH:
	  rtype = elf_loongarch_reloc_type (type);
	  break;

	case EM_AMDGPU:
	  rtype = elf_amdgpu_reloc_type (type);
	  break;
	}

      char *symbol_name = NULL;
      if (dump_reloc)
	{
	  if (rtype == NULL)
	    printf (_("unrecognized: %-7lx"),
		    (unsigned long) type & 0xffffffff);
	  else
	    printf (do_wide ? "%-22s" : "%-17.17s", rtype);
	}

      if (filedata->file_header.e_machine == EM_ALPHA
	  && rtype != NULL
	  && streq (rtype, "R_ALPHA_LITUSE")
	  && rel_type == reltype_rela)
	{
	  switch (rels[i].r_addend)
	    {
	    case LITUSE_ALPHA_ADDR:   rtype = "ADDR";   break;
	    case LITUSE_ALPHA_BASE:   rtype = "BASE";   break;
	    case LITUSE_ALPHA_BYTOFF: rtype = "BYTOFF"; break;
	    case LITUSE_ALPHA_JSR:    rtype = "JSR";    break;
	    case LITUSE_ALPHA_TLSGD:  rtype = "TLSGD";  break;
	    case LITUSE_ALPHA_TLSLDM: rtype = "TLSLDM"; break;
	    case LITUSE_ALPHA_JSRDIRECT: rtype = "JSRDIRECT"; break;
	    default: rtype = NULL;
	    }

	  if (dump_reloc)
	    {
	      if (rtype)
		printf (" (%s)", rtype);
	      else
		{
		  putchar (' ');
		  printf (_("<unknown addend: %" PRIx64 ">"),
			  rels[i].r_addend);
		  res = false;
		}
	    }
	}
      else if (symtab_index)
	{
	  if (symtab == NULL || symtab_index >= nsyms)
	    {
	      if (dump_reloc)
		{
		  error (_(" bad symbol index: %08lx in reloc\n"),
			 (unsigned long) symtab_index);
		  res = false;
		}
	    }
	  else
	    {
	      Elf_Internal_Sym * psym;
	      const char * version_string;
	      enum versioned_symbol_info sym_info;
	      unsigned short vna_other;

	      psym = symtab + symtab_index;

	      version_string
		= get_symbol_version_string (filedata, is_dynsym,
					     strtab, strtablen,
					     symtab_index,
					     psym,
					     &sym_info,
					     &vna_other);

	      if (dump_reloc)
		printf (" ");

	      if (ELF_ST_TYPE (psym->st_info) == STT_GNU_IFUNC)
		{
		  const char * name;
		  unsigned int len;
		  unsigned int width = is_32bit_elf ? 8 : 14;

		  /* Relocations against GNU_IFUNC symbols do not use the value
		     of the symbol as the address to relocate against.  Instead
		     they invoke the function named by the symbol and use its
		     result as the address for relocation.

		     To indicate this to the user, do not display the value of
		     the symbol in the "Symbols's Value" field.  Instead show
		     its name followed by () as a hint that the symbol is
		     invoked.  */

		  if (strtab == NULL
		      || psym->st_name == 0
		      || psym->st_name >= strtablen)
		    name = "??";
		  else
		    name = strtab + psym->st_name;

		  if (do_got_section_contents)
		    symbol_name = concat (name,
					      sym_info == symbol_public
					      ? "@@" : "@",
					      version_string, NULL);
		  else
		    symbol_name = xstrdup (name);

		  if (dump_reloc)
		    {
		      len = print_symbol_name (width, name);
		      if (version_string)
			printf (sym_info == symbol_public
				? "@@%s" : "@%s",
				version_string);
		      printf ("()%-*s",
			      len <= width ? (width + 1) - len : 1,
			      " ");
		    }
		}
	      else if (dump_reloc)
		{
		  print_vma (psym->st_value, LONG_HEX);

		  printf (is_32bit_elf ? "   " : " ");
		}

	      if (psym->st_name == 0)
		{
		  const char * sec_name = "<null>";

		  if (ELF_ST_TYPE (psym->st_info) == STT_SECTION)
		    sec_name = printable_section_name_from_index
		      (filedata, psym->st_shndx, NULL);

		  if (do_got_section_contents)
		    symbol_name = xstrdup (sec_name);
		  if (dump_reloc)
		    print_symbol_name (22, sec_name);
		}
	      else if (strtab == NULL)
		{
		  if (dump_reloc)
		    printf (_("<string table index: %3ld>"),
			    psym->st_name);
		}
	      else if (psym->st_name >= strtablen)
		{
		  if (dump_reloc)
		    {
		      error (_("<corrupt string table index: %3ld>\n"),
			     psym->st_name);
		      res = false;
		    }
		}
	      else
		{
		  if (dump_reloc)
		    {
		      print_symbol_name (22, strtab + psym->st_name);
		      if (version_string)
			printf (sym_info == symbol_public
				? "@@%s" : "@%s",
				version_string);
		    }
		  if (do_got_section_contents)
		    {
		      if (version_string)
			symbol_name = concat (strtab + psym->st_name,
					      sym_info == symbol_public
					      ? "@@" : "@",
					      version_string, NULL);
		      else
			symbol_name = xstrdup (strtab + psym->st_name);
		    }
		}

	      if (dump_reloc && rel_type == reltype_rela)
		{
		  uint64_t off = rels[i].r_addend;

		  if ((int64_t) off < 0)
		    printf (" - %" PRIx64, -off);
		  else
		    printf (" + %" PRIx64, off);
		}
	    }
	}
      else if (dump_reloc && rel_type == reltype_rela)
	{
	  uint64_t off = rels[i].r_addend;

	  printf ("%*c", is_32bit_elf ? 12 : 20, ' ');
	  if ((int64_t) off < 0)
	    printf ("-%" PRIx64, -off);
	  else
	    printf ("%" PRIx64, off);
	}

      if (do_got_section_contents)
	{
	  all_relocations[i].r_offset = offset;
	  all_relocations[i].r_name = rtype;
	  all_relocations[i].r_symbol = symbol_name;
	  all_relocations[i].r_addend = rels[i].r_addend;
	  all_relocations[i].r_type = rel_type;
	}

      if (dump_reloc)
	{
	  if (filedata->file_header.e_machine == EM_SPARCV9
	      && rtype != NULL
	      && streq (rtype, "R_SPARC_OLO10"))
	    printf (" + %" PRIx64, ELF64_R_TYPE_DATA (inf));

	  putchar ('\n');

	  if (! is_32bit_elf
	      && filedata->file_header.e_machine == EM_MIPS)
	    {
	      uint64_t type2 = ELF64_MIPS_R_TYPE2 (inf);
	      uint64_t type3 = ELF64_MIPS_R_TYPE3 (inf);
	      const char * rtype2 = elf_mips_reloc_type (type2);
	      const char * rtype3 = elf_mips_reloc_type (type3);

	      printf ("                    Type2: ");

	      if (rtype2 == NULL)
		printf (_("unrecognized: %-7lx"),
			(unsigned long) type2 & 0xffffffff);
	      else
		printf ("%-17.17s", rtype2);

	      printf ("\n                    Type3: ");

	      if (rtype3 == NULL)
		printf (_("unrecognized: %-7lx"),
			(unsigned long) type3 & 0xffffffff);
	      else
		printf ("%-17.17s", rtype3);

	      putchar ('\n');
	    }
	}
    }

  free (rels);

  return res;
}

static bool
process_relocs (Filedata * filedata)
{
  uint64_t rel_size;
  uint64_t rel_offset;
  unsigned int rel_entsz;

  if (!do_reloc && !do_got_section_contents)
    return true;

  if (do_using_dynamic)
    {
      relocation_type rel_type;
      const char * name;
      const char * entsz_name;
      bool  has_dynamic_reloc;
      unsigned int i;

      has_dynamic_reloc = false;

      for (i = 0; i < ARRAY_SIZE (dynamic_relocations); i++)
	{
	  rel_size = filedata->dynamic_info[dynamic_relocations [i].size];

	  if (!rel_size)
	    continue;

      has_dynamic_reloc = true;

	  rel_type = dynamic_relocations [i].rel_type;
	  name = dynamic_relocations [i].name;
	  rel_offset = filedata->dynamic_info[dynamic_relocations [i].reloc];

	  if (rel_type == reltype_unknown)
	    {
	      if (dynamic_relocations [i].reloc != DT_JMPREL)
		abort ();
	      switch (filedata->dynamic_info[DT_PLTREL])
		{
		case DT_REL:
		  rel_type = reltype_rel;
		  break;
		case DT_RELA:
		  rel_type = reltype_rela;
		  break;
		}
	    }

	  switch (rel_type)
	    {
	    default:
	      abort ();
	    case reltype_rel:
	      rel_entsz = filedata->dynamic_info[DT_RELENT];
	      entsz_name = "DT_RELENT";
	      break;
	    case reltype_rela:
	      rel_entsz = filedata->dynamic_info[DT_RELAENT];
	      entsz_name = "DT_RELAENT";
	      break;
	    case reltype_relr:
	      rel_entsz = filedata->dynamic_info[DT_RELRENT];
	      entsz_name = "DT_RELRENT";
	      break;
	    }

	  if (do_reloc)
	    {
	      if (filedata->is_separate)
		printf
		  (_("\nIn linked file '%s' section '%s' at offset"
		     "%#" PRIx64 " contains %" PRId64 " bytes:\n"),
		   filedata->file_name, name, rel_offset, rel_size);
	      else
		printf
		  (_("\n'%s' relocation section at offset %#" PRIx64
		     " contains %" PRId64 " bytes:\n"),
		   name, rel_offset, rel_size);
	    }

	  if (rel_type == reltype_relr)
	    dump_relr_relocations (filedata,
				   filedata->dynamic_info[DT_RELRSZ],
				   filedata->dynamic_info[DT_RELRENT],
				   filedata->dynamic_info[DT_RELR],
				   NULL,
				   filedata->dynamic_symbols,
				   filedata->num_dynamic_syms,
				   filedata->dynamic_strings,
				   filedata->dynamic_strings_length,
				   do_reloc);
	  else
	    {
	      if (rel_entsz == 0)
		{
		  printf (_("<missing or corrupt dynamic tag: %s>\n"),
			  entsz_name);
		  continue;
		}

	      update_all_relocations (rel_size / rel_entsz);

	      dump_relocations (filedata,
				offset_from_vma (filedata, rel_offset,
						 rel_size),
				rel_size,
				filedata->dynamic_symbols,
				filedata->num_dynamic_syms,
				filedata->dynamic_strings,
				filedata->dynamic_strings_length,
				rel_type, true /* is_dynamic */,
				do_reloc);
	    }
	}

      if (is_ia64_vms (filedata)
	  && process_ia64_vms_dynamic_relocs (filedata))
	has_dynamic_reloc = true;

      if (do_reloc && ! has_dynamic_reloc)
	{
	  if (filedata->is_separate)
	    printf (_("\nThere are no dynamic relocations in linked file '%s'.\n"),
		    filedata->file_name);
	  else
	    printf (_("\nThere are no dynamic relocations in this file.\n"));
	}
    }
  else
    {
      Elf_Internal_Shdr * section;
      size_t i;
      bool found = false;

      section = filedata->section_headers;
      if (section != NULL)
	for (i = 0; i < filedata->file_header.e_shnum; i++, section++)
	  if (display_relocations (section, filedata, do_reloc))
	    found = true;

      if (do_reloc && ! found)
	{
	  /* Users sometimes forget the -D option, so try to be helpful.  */
	  for (i = 0; i < ARRAY_SIZE (dynamic_relocations); i++)
	    {
	      if (filedata->dynamic_info[dynamic_relocations [i].size])
		{
		  if (filedata->is_separate)
		    printf (_("\nThere are no static relocations in linked file '%s'."),
			    filedata->file_name);
		  else
		    printf (_("\nThere are no static relocations in this file."));
		  printf (_("\nTo see the dynamic relocations add --use-dynamic to the command line.\n"));

		  break;
		}
	    }
	  if (i == ARRAY_SIZE (dynamic_relocations))
	    {
	      if (filedata->is_separate)
		printf (_("\nThere are no relocations in linked file '%s'.\n"),
			filedata->file_name);
	      else
		printf (_("\nThere are no relocations in this file.\n"));
	    }
	}
    }

  return true;
}

static bool
process_got_section_contents (Filedata * filedata)
{
  Elf_Internal_Shdr * section;
  unsigned int i;
  uint64_t entries;
  unsigned char *data;
  bool res = true;
  bool found = false;

  if (!do_got_section_contents)
    return res;

  switch (filedata->file_header.e_type)
    {
    case ET_DYN:
    case ET_EXEC:
      break;
    default:
      goto out;
    }

  switch (filedata->file_header.e_machine)
    {
    case EM_MIPS:
    case EM_MIPS_RS3_LE:
      /* process_mips_specific also displays GOT related contents.  */
      if (!do_arch)
	res = process_mips_specific (filedata, true);
      found = true;
      goto out;
    }

  if (all_relocations_count > 1)
    qsort (all_relocations_root, all_relocations_count,
	   sizeof (elf_relocation), elf_relocation_cmp);

  initialise_dumps_byname (filedata);

  for (i = 0, section = filedata->section_headers;
       i < filedata->file_header.e_shnum;
       i++, section++)
    if (section->sh_type == SHT_PROGBITS
	&& section->sh_size != 0)
      {
	const char *name = printable_section_name (filedata, section);

	if (!startswith (name, ".got"))
	  continue;

	found = true;

	data = (unsigned char *) get_section_contents (section,
						       filedata);
	if (data == NULL)
	  {
	    res = false;
	    goto out;
	  }

	uint32_t entsz = section->sh_entsize;
	/* NB: Gold, lld and mold set sh_entsize to 0 on .got and
	   .got.plt sections.  */
	if (entsz == 0)
	  {
	    if (is_32bit_elf)
	      switch (filedata->file_header.e_machine)
		{
		default:
		  entsz = 4;
		  break;
		case EM_X86_64:
		  /* x32 uses 8 byte GOT sh_entsize.  */
		  entsz = 8;
		  break;
		}
	    else
	      entsz = 8;
	  }

	entries = section->sh_size / entsz;
	if (entries == 1)
	  printf (_("\nGlobal Offset Table '%s' contains 1 entry:\n"),
		  name);
	else
	  printf (_("\nGlobal Offset Table '%s' contains %" PRIu64
		    " entries:\n"), name, entries);

	uint64_t g;

	if (is_32bit_elf)
	  {
	    uint32_t j, n = entries;
	    uint32_t addr;
	    struct got32
	      {
		unsigned char bytes[4];
	      } *got;

	    if (do_wide)
	      printf (_("   Index:  Address      Reloc             Sym. Name + Addend/Value\n"));
		      /* |---9---| |---8--| |---------22---------| |...........  */
	    else
	      printf (_(" Index:  Address      Reloc        Sym. Name + Addend/Value\n"));
		    /* |--7--| |---8--| |-------17------| |...........  */

	    addr = section->sh_addr;
	    got = (struct got32 *) data;
	    for (j = 0; j < n; j++)
	      {
		g = BYTE_GET (got[j].bytes);
		if (do_wide)
		  printf ("%8" PRIu32 ": %8.8" PRIx32, j, addr);
		else
		  printf ("%6" PRIu32 ": %8.8" PRIx32, j, addr);
		display_elf_relocation_at (addr, g);
		putchar ('\n');
		addr += entsz;
	      }
	  }
	else
	  {
	    uint64_t j, addr;
	    struct got64
	      {
		unsigned char bytes[4];
	      } *got;

	    if (do_wide)
	      printf (_("   Index:      Address          Reloc             Sym. Name + Addend/Value\n"));
		      /* |---9---| |------16------| |---------22---------| |...........  */
	    else
	      printf (_(" Index:    Address       Reloc         Sym. Name + Addend/Value\n"));
		      /* |--7--| |----12----| |------17-------| |...........  */

	    addr = section->sh_addr;
	    got = (struct got64 *) data;
	    for (j = 0; j < entries; j++)
	      {
		g = BYTE_GET (got[j].bytes);
		if (do_wide)
		  printf ("%8" PRIu64 ": %16.16" PRIx64, j, addr);
		else
		  printf ("%6" PRIu64 ": %12.12" PRIx64, j, addr);
		display_elf_relocation_at (addr, g);
		putchar ('\n');
		addr += entsz;
	      }
	  }

	free (data);
      }

 out:
  if (! found)
    {
      if (filedata->is_separate)
	printf (_("\nThere is no GOT section in linked file '%s'.\n"),
		filedata->file_name);
      else
	printf (_("\nThere is no GOT section in this file.\n"));
    }

  for (size_t j = 0; j < all_relocations_count; j++)
    free (all_relocations_root[j].r_symbol);
  free (all_relocations_root);
  all_relocations_root = NULL;
  all_relocations = NULL;
  all_relocations_count = 0;
  return res;
}

static bool
process_object (Filedata * filedata)
{
  bool have_separate_files;
  unsigned int i;
  bool res;

  if (! get_file_header (filedata))
    {
      error (_("%s: Failed to read file header\n"), filedata->file_name);
      return false;
    }

  /* Initialise per file variables.  */
  for (i = ARRAY_SIZE (filedata->version_info); i--;)
    filedata->version_info[i] = 0;

  for (i = ARRAY_SIZE (filedata->dynamic_info); i--;)
    filedata->dynamic_info[i] = 0;
  filedata->dynamic_info_DT_GNU_HASH = 0;
  filedata->dynamic_info_DT_MIPS_XHASH = 0;

  /* Process the file.  */
  if (show_name)
    printf (_("\nFile: %s\n"), filedata->file_name);

  initialise_dump_sects (filedata);

  /* There may be some extensions in the first section header.  Don't
     bomb if we can't read it.  */
  get_section_headers (filedata, true);

  if (! process_file_header (filedata))
    {
      res = false;
      goto out;
    }

  /* Throw away the single section header read above, so that we
     re-read the entire set.  */
  free (filedata->section_headers);
  filedata->section_headers = NULL;

  if (! process_section_headers (filedata))
    {
      /* Without loaded section headers we cannot process lots of things.  */
      do_unwind = do_version = do_dump = do_arch = false;

      if (! do_using_dynamic)
	do_syms = do_dyn_syms = do_reloc = false;
    }

  if (! process_section_groups (filedata))
    /* Without loaded section groups we cannot process unwind.  */
    do_unwind = false;

  process_program_headers (filedata);

  res = process_dynamic_section (filedata);

  if (! process_relocs (filedata))
    res = false;

  if (! process_unwind (filedata))
    res = false;

  if (! process_symbol_table (filedata))
    res = false;

  if (! process_lto_symbol_tables (filedata))
    res = false;

  if (! process_syminfo (filedata))
    res = false;

  if (! process_version_sections (filedata))
    res = false;

  if (might_need_separate_debug_info (filedata))
    have_separate_files = load_separate_debug_files (filedata, filedata->file_name);
  else
    have_separate_files = false;

  if (! process_section_contents (filedata))
    res = false;

  if (! process_got_section_contents (filedata))
    res = false;

  if (have_separate_files)
    {
      separate_info * d;

      for (d = first_separate_info; d != NULL; d = d->next)
	{
	  initialise_dump_sects (d->handle);

	  if (process_links && ! process_file_header (d->handle))
	    res = false;
	  else if (! process_section_headers (d->handle))
	    res = false;
	  else if (! process_section_contents (d->handle))
	    res = false;
	  else if (process_links)
	    {
	      if (! process_section_groups (d->handle))
		res = false;
	      process_program_headers (d->handle);
	      if (! process_dynamic_section (d->handle))
		res = false;
	      if (! process_relocs (d->handle))
		res = false;
	      if (! process_unwind (d->handle))
		res = false;
	      if (! process_symbol_table (d->handle))
		res = false;
	      if (! process_lto_symbol_tables (d->handle))
		res = false;
	      if (! process_syminfo (d->handle))
		res = false;
	      if (! process_version_sections (d->handle))
		res = false;
	      if (! process_notes (d->handle))
		res = false;
	    }
	}

      /* The file handles are closed by the call to free_debug_memory() below.  */
    }

  if (! process_notes (filedata))
    res = false;

  if (! process_gnu_liblist (filedata))
    res = false;

  if (! process_arch_specific (filedata))
    res = false;

 out:
  free_filedata (filedata);

  free_debug_memory ();

  return res;
}
