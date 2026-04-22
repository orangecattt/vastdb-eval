#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define _(x) (x)
#define ngettext(s1, s2, n) ((n) == 1 ? (s1) : (s2))
#define streq(a,b) (strcmp ((a), (b)) == 0)
#define ARRAY_SIZE(arr) (sizeof (arr) / sizeof (arr)[0])

typedef struct {
  unsigned char	sh_name[4];
  unsigned char	sh_type[4];
  unsigned char	sh_flags[4];
  unsigned char	sh_addr[4];
  unsigned char	sh_offset[4];
  unsigned char	sh_size[4];
  unsigned char	sh_link[4];
  unsigned char	sh_info[4];
  unsigned char	sh_addralign[4];
  unsigned char	sh_entsize[4];
} Elf32_External_Shdr;

typedef struct {
  unsigned char	sh_name[4];
  unsigned char	sh_type[4];
  unsigned char	sh_flags[8];
  unsigned char	sh_addr[8];
  unsigned char	sh_offset[8];
  unsigned char	sh_size[8];
  unsigned char	sh_link[4];
  unsigned char	sh_info[4];
  unsigned char	sh_addralign[8];
  unsigned char	sh_entsize[8];
} Elf64_External_Shdr;

typedef struct elf_internal_ehdr {
  unsigned char		e_ident[16];
  uint64_t		e_entry;
  uint64_t		e_phoff;
  uint64_t		e_shoff;
  unsigned long		e_version;
  unsigned long		e_flags;
  unsigned short	e_type;
  unsigned short	e_machine;
  unsigned int		e_ehsize;
  unsigned int		e_phentsize;
  unsigned int		e_shentsize;
  unsigned int		e_phnum;
  unsigned int		e_shnum;
  unsigned int		e_shstrndx;
} Elf_Internal_Ehdr;

struct dump_data
{
  unsigned char *          dump_sects;
  unsigned int             num_dump_sects;
};

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

typedef struct elf_internal_shdr {
  unsigned int	sh_name;
  unsigned int	sh_type;
  uint64_t	sh_flags;
  uint64_t	sh_addr;
  int64_t	sh_offset;
  uint64_t	sh_size;
  unsigned int	sh_link;
  unsigned int	sh_info;
  uint64_t	sh_addralign;
  uint64_t	sh_entsize;
  void *	bfd_section;
  unsigned char *contents;
} Elf_Internal_Shdr;

struct elf_internal_sym {
  uint64_t	st_value;
  uint64_t	st_size;
  unsigned long	st_name;
  unsigned char	st_info;
  unsigned char	st_other;
  unsigned char st_target_internal;
  unsigned int  st_shndx;
};

typedef struct elf_internal_sym Elf_Internal_Sym;

typedef struct elf_internal_chdr {
  unsigned int	ch_type;
  uint64_t	ch_size;
  uint64_t	ch_addralign;
} Elf_Internal_Chdr;

typedef struct {
  unsigned char	st_name[4];
  unsigned char	st_info[1];
  unsigned char	st_other[1];
  unsigned char	st_shndx[2];
  unsigned char	st_value[8];
  unsigned char	st_size[8];
} Elf64_External_Sym;

typedef struct {
  unsigned char est_shndx[4];
} Elf_External_Sym_Shndx;

typedef struct {
  unsigned char	st_name[4];
  unsigned char	st_value[4];
  unsigned char	st_size[4];
  unsigned char	st_info[1];
  unsigned char	st_other[1];
  unsigned char	st_shndx[2];
} Elf32_External_Sym;

typedef struct {
  unsigned char r_offset[4];
  unsigned char	r_info[4];
} Elf32_External_Rel;

typedef struct {
  unsigned char r_offset[8];
  unsigned char	r_info[8];
} Elf64_External_Rel;

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

typedef struct {
  unsigned char r_data[4];
} Elf32_External_Relr;

typedef struct {
  unsigned char r_data[8];
} Elf64_External_Relr;

typedef struct {
  unsigned char	ch_type[4];
  unsigned char	ch_reserved[4];
  unsigned char	ch_size[8];
  unsigned char	ch_addralign[8];
} Elf64_External_Chdr;

typedef struct elf_section_list
{
  Elf_Internal_Shdr *        hdr;
  struct elf_section_list *  next;
} elf_section_list;

typedef enum
{
  reltype_unknown,
  reltype_rel,
  reltype_rela,
  reltype_relr
} relocation_type;

typedef struct separate_info
{
  void *                  handle;
  const char *            filename;
  struct separate_info *  next;
} separate_info;

typedef struct filedata
{
  const char *         file_name;
  bool                 is_separate;
  void *               handle;
  uint64_t             file_size;
  Elf_Internal_Ehdr    file_header;
  uint64_t             archive_file_offset;
  uint64_t             archive_file_size;
  Elf_Internal_Shdr *  section_headers;
  void *               program_headers;
  char *               string_table;
  uint64_t             string_table_length;
  uint64_t             dynamic_addr;
  uint64_t             dynamic_size;
  uint64_t             dynamic_nent;
  void *               dynamic_section;
  Elf_Internal_Shdr *  dynamic_strtab_section;
  char *               dynamic_strings;
  uint64_t             dynamic_strings_length;
  Elf_Internal_Shdr *  dynamic_symtab_section;
  uint64_t             num_dynamic_syms;
  Elf_Internal_Sym *   dynamic_symbols;
  uint64_t             version_info[16];
  unsigned int         dynamic_syminfo_nent;
  void *               dynamic_syminfo;
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
  uint64_t             dynamic_info[38];
  uint64_t             dynamic_info_DT_GNU_HASH;
  uint64_t             dynamic_info_DT_MIPS_XHASH;
  elf_section_list *   symtab_shndx_list;
  size_t               group_count;
  void *               section_groups;
  void **              section_headers_groups;
  struct dump_data     dump;
} Filedata;

#define BYTE_GET(field)	byte_get (field, sizeof (field))

#define SHN_UNDEF	0
#define SHN_LORESERVE	0xFF00
#define SHN_XINDEX	0xFFFF
#define SHN_BEFORE	SHN_LORESERVE
#define SHN_AFTER	(SHN_LORESERVE + 1)

#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_DYNSYM	11
#define SHT_INIT_ARRAY	  14
#define SHT_FINI_ARRAY	  15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP	  17
#define SHT_SYMTAB_SHNDX  18
#define SHT_RELR	  19
#define SHT_LOOS	0x60000000
#define SHT_GNU_SFRAME	0x6ffffff4
#define SHT_GNU_HASH	0x6ffffff6
#define SHT_GNU_LIBLIST	0x6ffffff7
#define SHT_GNU_verdef	0x6ffffffd
#define SHT_GNU_verneed	0x6ffffffe
#define SHT_GNU_versym	0x6fffffff

#define SHF_WRITE	(1 << 0)
#define SHF_ALLOC	(1 << 1)
#define SHF_EXECINSTR	(1 << 2)
#define SHF_MERGE	(1 << 4)
#define SHF_STRINGS	(1 << 5)
#define SHF_INFO_LINK	(1 << 6)
#define SHF_LINK_ORDER	(1 << 7)
#define SHF_OS_NONCONFORMING (1 << 8)
#define SHF_GROUP	(1 << 9)
#define SHF_TLS		(1 << 10)
#define SHF_COMPRESSED	(1 << 11)
#define SHF_GNU_MBIND	(1 << 24)

#define ET_EXEC		2
#define ET_DYN		3

#define EM_NONE		  0
#define EM_SPARC	  2
#define EM_386		  3
#define EM_IAMCU	  6
#define EM_68K		  4
#define EM_MIPS		  8
#define EM_MIPS_RS3_LE	 10
#define EM_OLD_SPARCV9	 11
#define EM_SPARC32PLUS	 18
#define EM_PPC		 20
#define EM_ARM		 40
#define EM_SPARCV9	 43
#define EM_H8_300	 46
#define EM_H8_300H	 47
#define EM_IA_64	 50
#define EM_X86_64	 62
#define EM_M32C_OLD		0xFEB0
#define EM_M32C		120
#define EM_L1OM		180
#define EM_K1OM		181

#define EI_OSABI	7
#define ELFOSABI_NONE	      0
#define ELFOSABI_GNU	      3
#define ELFOSABI_FREEBSD      9

#define DT_NULL		0
#define DT_PLTRELSZ	2
#define DT_JMPREL	23
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_RELENT	19
#define DT_RELRSZ	35
#define DT_RELR		36
#define DT_RELRENT	37
#define DT_PLTREL	20

#define GRP_ENTRY_SIZE		4

enum
{
  ch_compress_zlib = 1,
  ch_compress_zstd = 2
};

#define DEBUG_DUMP	(1 << 2)

#define EF_MIPS_ABI	0x0000F000
#define EF_MIPS_ABI_EABI64	0x00004000
#define EF_H8_MACH	0x0000FFFF
#define E_H8_MACH_H8300		0x0001
#define E_H8_MACH_H8300HN	0x0002
#define E_H8_MACH_H8300SN	0x0003
#define E_H8_MACH_H8300SXN	0x0004
#define E_H8_MACH_H8300H	0x0010
#define E_H8_MACH_H8300S	0x0020
#define E_H8_MACH_H8300SX	0x0030
#define EF_M32C_CPU_MASK	0x000000FF
#define EF_M32C_CPU_M16C	0x00000001

extern bool is_32bit_elf;
extern bool do_sections;
extern bool do_header;
extern bool do_reloc;
extern bool do_got_section_contents;
extern bool do_using_dynamic;
extern bool do_checks;
extern bool do_debugging;
extern int do_debug_info;
extern int do_debug_abbrevs;
extern int do_debug_lines;
extern int do_debug_pubnames;
extern int do_debug_pubtypes;
extern int do_debug_aranges;
extern int do_debug_ranges;
extern int do_debug_frames;
extern int do_debug_macinfo;
extern int do_debug_str;
extern int do_debug_str_offsets;
extern int do_debug_loc;
extern int do_gdb_index;
extern int do_trace_info;
extern int do_trace_abbrevs;
extern int do_trace_aranges;
extern int do_debug_addr;
extern int do_debug_cu_index;
extern int do_wide;
extern int do_debug_links;
extern bool do_section_details;
extern bool process_links;
extern bool show_name;
extern unsigned int eh_addr_size;
extern separate_info * first_separate_info;

struct dynamic_reloc_entry
{
  const char * name;
  int reloc;
  int size;
  relocation_type rel_type;
};

static struct dynamic_reloc_entry dynamic_relocations [] =
{
  { "REL", DT_REL, DT_RELSZ, reltype_rel },
  { "RELA", DT_RELA, DT_RELASZ, reltype_rela },
  { "RELR", DT_RELR, DT_RELRSZ, reltype_relr },
  { "PLT", DT_JMPREL, DT_PLTRELSZ, reltype_unknown }
};

extern uint64_t (*byte_get) (const unsigned char *, unsigned int);

extern void * get_data (void *, Filedata *, uint64_t, uint64_t, uint64_t, const char *);
extern void error (const char *, ...);
extern void warn (const char *, ...);
extern void * cmalloc (uint64_t, size_t);
extern const char * printable_section_name (Filedata *, Elf_Internal_Shdr *);
extern const char * printable_string (const char *, int);
extern void request_dump_bynumber (struct dump_data *, unsigned int, unsigned char);
extern const char * get_section_type_name (Filedata *, unsigned int);
extern unsigned int print_vma (uint64_t, print_mode);
extern const char * get_elf_section_flags (Filedata *, uint64_t);
extern int get_compression_header (Elf_Internal_Chdr *, unsigned char *, unsigned int);
extern relocation_type rel_type_from_sh_type (unsigned int);
extern uint64_t count_relr_relocations (Filedata *, Elf_Internal_Shdr *, uint64_t **);
extern void update_all_relocations (uint64_t);
extern Elf_Internal_Shdr * find_section_by_name (Filedata *, const char *);
extern bool get_symtab (Filedata *, Elf_Internal_Shdr *, Elf_Internal_Sym **, uint64_t *, char **, uint64_t *);
extern bool dump_relr_relocations (Filedata *, uint64_t, uint64_t, uint64_t, uint64_t *, Elf_Internal_Sym *, uint64_t, char *, uint64_t, bool);
extern bool dump_relocations (Filedata *, uint64_t, uint64_t, Elf_Internal_Sym *, uint64_t, char *, uint64_t, relocation_type, bool, bool);
extern bool process_ia64_vms_dynamic_relocs (Filedata *);
extern uint64_t offset_from_vma (Filedata *, uint64_t, uint64_t);
extern bool get_file_header (Filedata *);
extern void initialise_dump_sects (Filedata *);
extern bool process_file_header (Filedata *);
extern bool process_section_groups (Filedata *);
extern void process_program_headers (Filedata *);
extern bool process_dynamic_section (Filedata *);
extern bool process_unwind (Filedata *);
extern bool process_symbol_table (Filedata *);
extern bool process_lto_symbol_tables (Filedata *);
extern bool process_syminfo (Filedata *);
extern bool process_version_sections (Filedata *);
extern bool might_need_separate_debug_info (Filedata *);
extern bool load_separate_debug_files (Filedata *, const char *);
extern bool process_section_contents (Filedata *);
extern bool process_got_section_contents (Filedata *);
extern bool process_notes (Filedata *);
extern bool process_gnu_liblist (Filedata *);
extern bool process_arch_specific (Filedata *);
extern void free_filedata (Filedata *);
extern void free_debug_memory (void);
extern Elf_Internal_Shdr * find_section (Filedata *, const char *);
extern int startswith (const char *, const char *);
extern Elf_Internal_Sym * get_elf_symbols (Filedata *, Elf_Internal_Shdr *, uint64_t *);
extern void * xmalloc (size_t);
extern void print_symbol_name (int, const char *);
extern bool is_ia64_vms (Filedata *);

extern bool do_unwind;
extern bool do_version;
extern bool do_dump;
extern bool do_arch;
extern bool do_syms;
extern bool do_dyn_syms;

static bool
get_32bit_section_headers (Filedata * filedata, bool probe)
{
  Elf32_External_Shdr * shdrs;
  Elf_Internal_Shdr *   internal;
  unsigned int          i;
  unsigned int          size = filedata->file_header.e_shentsize;
  unsigned int          num = probe ? 1 : filedata->file_header.e_shnum;

  /* PR binutils/17531: Cope with unexpected section header sizes.  */
  if (size == 0 || num == 0)
    return false;

  /* The section header cannot be at the start of the file - that is
     where the ELF file header is located.  A file with absolutely no
     sections in it will use a shoff of 0.  */
  if (filedata->file_header.e_shoff == 0)
    return false;

  if (size < sizeof * shdrs)
    {
      if (! probe)
	error (_("The e_shentsize field in the ELF header is less than the size of an ELF section header\n"));
      return false;
    }
  if (!probe && size > sizeof * shdrs)
    warn (_("The e_shentsize field in the ELF header is larger than the size of an ELF section header\n"));

  shdrs = (Elf32_External_Shdr *) get_data (NULL, filedata, filedata->file_header.e_shoff,
                                            size, num,
					    probe ? NULL : _("section headers"));
  if (shdrs == NULL)
    return false;

  filedata->section_headers = (Elf_Internal_Shdr *)
    cmalloc (num, sizeof (Elf_Internal_Shdr));
  if (filedata->section_headers == NULL)
    {
      if (!probe)
	error (_("Out of memory reading %u section headers\n"), num);
      free (shdrs);
      return false;
    }

  for (i = 0, internal = filedata->section_headers;
       i < num;
       i++, internal++)
    {
      internal->sh_name      = BYTE_GET (shdrs[i].sh_name);
      internal->sh_type      = BYTE_GET (shdrs[i].sh_type);
      internal->sh_flags     = BYTE_GET (shdrs[i].sh_flags);
      internal->sh_addr      = BYTE_GET (shdrs[i].sh_addr);
      internal->sh_offset    = BYTE_GET (shdrs[i].sh_offset);
      internal->sh_size      = BYTE_GET (shdrs[i].sh_size);
      internal->sh_link      = BYTE_GET (shdrs[i].sh_link);
      internal->sh_info      = BYTE_GET (shdrs[i].sh_info);
      internal->sh_addralign = BYTE_GET (shdrs[i].sh_addralign);
      internal->sh_entsize   = BYTE_GET (shdrs[i].sh_entsize);
      if (!probe && internal->sh_link > num)
	warn (_("Section %u has an out of range sh_link value of %u\n"), i, internal->sh_link);
      if (!probe && internal->sh_flags & SHF_INFO_LINK && internal->sh_info > num)
	warn (_("Section %u has an out of range sh_info value of %u\n"), i, internal->sh_info);
    }

  free (shdrs);
  return true;
}

static bool
get_64bit_section_headers (Filedata * filedata, bool probe)
{
  Elf64_External_Shdr *  shdrs;
  Elf_Internal_Shdr *    internal;
  unsigned int           i;
  unsigned int           size = filedata->file_header.e_shentsize;
  unsigned int           num = probe ? 1 : filedata->file_header.e_shnum;

  /* PR binutils/17531: Cope with unexpected section header sizes.  */
  if (size == 0 || num == 0)
    return false;

  /* The section header cannot be at the start of the file - that is
     where the ELF file header is located.  A file with absolutely no
     sections in it will use a shoff of 0.  */
  if (filedata->file_header.e_shoff == 0)
    return false;

  if (size < sizeof * shdrs)
    {
      if (! probe)
	error (_("The e_shentsize field in the ELF header is less than the size of an ELF section header\n"));
      return false;
    }

  if (! probe && size > sizeof * shdrs)
    warn (_("The e_shentsize field in the ELF header is larger than the size of an ELF section header\n"));

  shdrs = (Elf64_External_Shdr *) get_data (NULL, filedata,
					    filedata->file_header.e_shoff,
                                            size, num,
					    probe ? NULL : _("section headers"));
  if (shdrs == NULL)
    return false;

  filedata->section_headers = (Elf_Internal_Shdr *)
    cmalloc (num, sizeof (Elf_Internal_Shdr));
  if (filedata->section_headers == NULL)
    {
      if (! probe)
	error (_("Out of memory reading %u section headers\n"), num);
      free (shdrs);
      return false;
    }

  for (i = 0, internal = filedata->section_headers;
       i < num;
       i++, internal++)
    {
      internal->sh_name      = BYTE_GET (shdrs[i].sh_name);
      internal->sh_type      = BYTE_GET (shdrs[i].sh_type);
      internal->sh_flags     = BYTE_GET (shdrs[i].sh_flags);
      internal->sh_addr      = BYTE_GET (shdrs[i].sh_addr);
      internal->sh_size      = BYTE_GET (shdrs[i].sh_size);
      internal->sh_entsize   = BYTE_GET (shdrs[i].sh_entsize);
      internal->sh_link      = BYTE_GET (shdrs[i].sh_link);
      internal->sh_info      = BYTE_GET (shdrs[i].sh_info);
      internal->sh_offset    = BYTE_GET (shdrs[i].sh_offset);
      internal->sh_addralign = BYTE_GET (shdrs[i].sh_addralign);
      if (!probe && internal->sh_link > num)
	warn (_("Section %u has an out of range sh_link value of %u\n"), i, internal->sh_link);
      if (!probe && internal->sh_flags & SHF_INFO_LINK && internal->sh_info > num)
	warn (_("Section %u has an out of range sh_info value of %u\n"), i, internal->sh_info);
    }

  free (shdrs);
  return true;
}

static bool
get_section_headers (Filedata *filedata, bool probe)
{
  if (filedata->section_headers != NULL)
    return true;

  if (is_32bit_elf)
    return get_32bit_section_headers (filedata, probe);
  else
    return get_64bit_section_headers (filedata, probe);
}

static bool
process_section_headers (Filedata * filedata)
{
  Elf_Internal_Shdr * section;
  unsigned int i;

  if (filedata->file_header.e_shnum == 0)
    {
      /* PR binutils/12467.  */
      if (filedata->file_header.e_shoff != 0)
	{
	  warn (_("possibly corrupt ELF file header - it has a non-zero"
		  " section header offset, but no section headers\n"));
	  return false;
	}
      else if (do_sections)
	printf (_("\nThere are no sections in this file.\n"));

      return true;
    }

  if (do_sections && !do_header)
    {
      if (filedata->is_separate && process_links)
	printf (_("In linked file '%s': "),
		printable_string (filedata->file_name, 0));
      if (! filedata->is_separate || process_links)
	printf (ngettext ("There is %d section header, "
			  "starting at offset %#" PRIx64 ":\n",
			  "There are %d section headers, "
			  "starting at offset %#" PRIx64 ":\n",
			  filedata->file_header.e_shnum),
		filedata->file_header.e_shnum,
		filedata->file_header.e_shoff);
    }

  if (!get_section_headers (filedata, false))
    return false;

  /* Read in the string table, so that we have names to display.  */
  if (filedata->string_table == NULL
      && filedata->file_header.e_shstrndx != SHN_UNDEF
      && filedata->file_header.e_shstrndx < filedata->file_header.e_shnum)
    {
      section = filedata->section_headers + filedata->file_header.e_shstrndx;

      if (section->sh_size != 0)
	{
	  filedata->string_table = (char *) get_data (NULL, filedata, section->sh_offset,
						      1, section->sh_size,
						      _("string table"));

	  filedata->string_table_length = filedata->string_table != NULL ? section->sh_size : 0;
	}
    }

  /* Scan the sections for the dynamic symbol table
     and dynamic string table and debug sections.  */
  eh_addr_size = is_32bit_elf ? 4 : 8;
  switch (filedata->file_header.e_machine)
    {
    case EM_MIPS:
    case EM_MIPS_RS3_LE:
      /* The 64-bit MIPS EABI uses a combination of 32-bit ELF and 64-bit
	 FDE addresses.  However, the ABI also has a semi-official ILP32
	 variant for which the normal FDE address size rules apply.

	 GCC 4.0 marks EABI64 objects with a dummy .gcc_compiled_longXX
	 section, where XX is the size of longs in bits.  Unfortunately,
	 earlier compilers provided no way of distinguishing ILP32 objects
	 from LP64 objects, so if there's any doubt, we should assume that
	 the official LP64 form is being used.  */
      if ((filedata->file_header.e_flags & EF_MIPS_ABI) == EF_MIPS_ABI_EABI64
	  && find_section (filedata, ".gcc_compiled_long32") == NULL)
	eh_addr_size = 8;
      break;

    case EM_H8_300:
    case EM_H8_300H:
      switch (filedata->file_header.e_flags & EF_H8_MACH)
	{
	case E_H8_MACH_H8300:
	case E_H8_MACH_H8300HN:
	case E_H8_MACH_H8300SN:
	case E_H8_MACH_H8300SXN:
	  eh_addr_size = 2;
	  break;
	case E_H8_MACH_H8300H:
	case E_H8_MACH_H8300S:
	case E_H8_MACH_H8300SX:
	  eh_addr_size = 4;
	  break;
	}
      break;

    case EM_M32C_OLD:
    case EM_M32C:
      switch (filedata->file_header.e_flags & EF_M32C_CPU_MASK)
	{
	case EF_M32C_CPU_M16C:
	  eh_addr_size = 2;
	  break;
	}
      break;
    }

#define CHECK_ENTSIZE_VALUES(section, i, size32, size64)		\
  do									\
    {									\
      uint64_t expected_entsize = is_32bit_elf ? size32 : size64;	\
      if (section->sh_entsize != expected_entsize)			\
	{								\
	  error (_("Section %d has invalid sh_entsize of %" PRIx64 "\n"), \
		 i, section->sh_entsize);				\
	  error (_("(Using the expected size of %" PRIx64 " for the rest of this dump)\n"), \
		 expected_entsize);					\
	  section->sh_entsize = expected_entsize;			\
	}								\
    }									\
  while (0)

#define CHECK_ENTSIZE(section, i, type)					\
  CHECK_ENTSIZE_VALUES (section, i, sizeof (Elf32_External_##type),	\
			sizeof (Elf64_External_##type))

  for (i = 0, section = filedata->section_headers;
       i < filedata->file_header.e_shnum;
       i++, section++)
    {
      const char *name = printable_section_name (filedata, section);

      /* Run some sanity checks on the headers and
	 possibly fill in some file data as well.  */
      switch (section->sh_type)
	{
	case SHT_DYNSYM:
	  if (filedata->dynamic_symbols != NULL)
	    {
	      error (_("File contains multiple dynamic symbol tables\n"));
	      continue;
	    }

	  CHECK_ENTSIZE (section, i, Sym);
	  filedata->dynamic_symbols
	    = get_elf_symbols (filedata, section, &filedata->num_dynamic_syms);
	  filedata->dynamic_symtab_section = section;
	  break;

	case SHT_STRTAB:
	  if (streq (name, ".dynstr"))
	    {
	      if (filedata->dynamic_strings != NULL)
		{
		  error (_("File contains multiple dynamic string tables\n"));
		  continue;
		}

	      filedata->dynamic_strings
		= (char *) get_data (NULL, filedata, section->sh_offset,
				     1, section->sh_size, _("dynamic strings"));
	      filedata->dynamic_strings_length
		= filedata->dynamic_strings == NULL ? 0 : section->sh_size;
	      filedata->dynamic_strtab_section = section;
	    }
	  break;

	case SHT_SYMTAB_SHNDX:
	  {
	    elf_section_list * entry = xmalloc (sizeof * entry);

	    entry->hdr = section;
	    entry->next = filedata->symtab_shndx_list;
	    filedata->symtab_shndx_list = entry;
	  }
	  break;

	case SHT_SYMTAB:
	  CHECK_ENTSIZE (section, i, Sym);
	  break;

	case SHT_GROUP:
	  CHECK_ENTSIZE_VALUES (section, i, GRP_ENTRY_SIZE, GRP_ENTRY_SIZE);
	  break;

	case SHT_REL:
	  CHECK_ENTSIZE (section, i, Rel);
	  if (do_checks && section->sh_size == 0)
	    warn (_("Section '%s': zero-sized relocation section\n"), name);
	  break;

	case SHT_RELA:
	  CHECK_ENTSIZE (section, i, Rela);
	  if (do_checks && section->sh_size == 0)
	    warn (_("Section '%s': zero-sized relocation section\n"), name);
	  break;

	case SHT_RELR:
	  CHECK_ENTSIZE (section, i, Relr);
	  break;

	case SHT_NOTE:
	case SHT_PROGBITS:
	case SHT_GNU_SFRAME:
	  /* Having a zero sized section is not illegal according to the
	     ELF standard, but it might be an indication that something
	     is wrong.  So issue a warning if we are running in lint mode.  */
	  if (do_checks && section->sh_size == 0)
	    warn (_("Section '%s': has a size of zero - is this intended ?\n"), name);
	  break;

	default:
	  break;
	}

      if ((do_debugging || do_debug_info || do_debug_abbrevs
	   || do_debug_lines || do_debug_pubnames || do_debug_pubtypes
	   || do_debug_aranges || do_debug_frames || do_debug_macinfo
	   || do_debug_str || do_debug_str_offsets || do_debug_loc
	   || do_debug_ranges
	   || do_debug_addr || do_debug_cu_index || do_debug_links)
	  && (startswith (name, ".debug_")
	      || startswith (name, ".zdebug_")))
	{
          if (name[1] == 'z')
            name += sizeof (".zdebug_") - 1;
          else
            name += sizeof (".debug_") - 1;

	  if (do_debugging
	      || (do_debug_info     && startswith (name, "info"))
	      || (do_debug_info     && startswith (name, "types"))
	      || (do_debug_abbrevs  && startswith (name, "abbrev"))
	      || (do_debug_lines    && strcmp (name, "line") == 0)
	      || (do_debug_lines    && startswith (name, "line."))
	      || (do_debug_pubnames && startswith (name, "pubnames"))
	      || (do_debug_pubtypes && startswith (name, "pubtypes"))
	      || (do_debug_pubnames && startswith (name, "gnu_pubnames"))
	      || (do_debug_pubtypes && startswith (name, "gnu_pubtypes"))
	      || (do_debug_aranges  && startswith (name, "aranges"))
	      || (do_debug_ranges   && startswith (name, "ranges"))
	      || (do_debug_ranges   && startswith (name, "rnglists"))
	      || (do_debug_frames   && startswith (name, "frame"))
	      || (do_debug_macinfo  && startswith (name, "macinfo"))
	      || (do_debug_macinfo  && startswith (name, "macro"))
	      || (do_debug_str      && startswith (name, "str"))
	      || (do_debug_links    && startswith (name, "sup"))
	      || (do_debug_str_offsets && startswith (name, "str_offsets"))
	      || (do_debug_loc      && startswith (name, "loc"))
	      || (do_debug_loc      && startswith (name, "loclists"))
	      || (do_debug_addr     && startswith (name, "addr"))
	      || (do_debug_cu_index && startswith (name, "cu_index"))
	      || (do_debug_cu_index && startswith (name, "tu_index"))
	      )
	    request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
	}
      /* Linkonce section to be combined with .debug_info at link time.  */
      else if ((do_debugging || do_debug_info)
	       && startswith (name, ".gnu.linkonce.wi."))
	request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
      else if (do_debug_frames && streq (name, ".eh_frame"))
	request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
      else if (do_debug_frames && streq (name, ".eh_frame_hdr"))
	request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
      else if (do_gdb_index && (streq (name, ".gdb_index")
				|| streq (name, ".debug_names")))
	request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
      /* Trace sections for Itanium VMS.  */
      else if ((do_debugging || do_trace_info || do_trace_abbrevs
                || do_trace_aranges)
	       && startswith (name, ".trace_"))
	{
          name += sizeof (".trace_") - 1;

	  if (do_debugging
	      || (do_trace_info     && streq (name, "info"))
	      || (do_trace_abbrevs  && streq (name, "abbrev"))
	      || (do_trace_aranges  && streq (name, "aranges"))
	      )
	    request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
	}
      else if ((do_debugging || do_debug_links)
	       && (startswith (name, ".gnu_debuglink")
		   || startswith (name, ".gnu_debugaltlink")))
	request_dump_bynumber (&filedata->dump, i, DEBUG_DUMP);
    }

  if (! do_sections)
    return true;

  if (filedata->is_separate && ! process_links)
    return true;

  if (filedata->is_separate)
    printf (_("\nSection Headers in linked file '%s':\n"),
	    printable_string (filedata->file_name, 0));
  else if (filedata->file_header.e_shnum > 1)
    printf (_("\nSection Headers:\n"));
  else
    printf (_("\nSection Header:\n"));

  if (is_32bit_elf)
    {
      if (do_section_details)
	{
	  printf (_("  [Nr] Name\n"));
	  printf (_("       Type            Addr     Off    Size   ES   Lk Inf Al\n"));
	}
      else
	printf
	  (_("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n"));
    }
  else if (do_wide)
    {
      if (do_section_details)
	{
	  printf (_("  [Nr] Name\n"));
	  printf (_("       Type            Address          Off    Size   ES   Lk Inf Al\n"));
	}
      else
	printf
	  (_("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n"));
    }
  else
    {
      if (do_section_details)
	{
	  printf (_("  [Nr] Name\n"));
	  printf (_("       Type              Address          Offset            Link\n"));
	  printf (_("       Size              EntSize          Info              Align\n"));
	}
      else
	{
	  printf (_("  [Nr] Name              Type             Address           Offset\n"));
	  printf (_("       Size              EntSize          Flags  Link  Info  Align\n"));
	}
    }

  if (do_section_details)
    printf (_("       Flags\n"));

  for (i = 0, section = filedata->section_headers;
       i < filedata->file_header.e_shnum;
       i++, section++)
    {
      /* Run some sanity checks on the section header.  */

      /* Check the sh_link field.  */
      switch (section->sh_type)
	{
	case SHT_REL:
	case SHT_RELR:
	case SHT_RELA:
	  if (section->sh_link == 0
	      && (filedata->file_header.e_type == ET_EXEC
		  || filedata->file_header.e_type == ET_DYN))
	    /* A dynamic relocation section where all entries use a
	       zero symbol index need not specify a symtab section.  */
	    break;
	  /* Fall through.  */
	case SHT_SYMTAB_SHNDX:
	case SHT_GROUP:
	case SHT_HASH:
	case SHT_GNU_HASH:
	case SHT_GNU_versym:
	  if (section->sh_link == 0
	      || section->sh_link >= filedata->file_header.e_shnum
	      || (filedata->section_headers[section->sh_link].sh_type != SHT_SYMTAB
		  && filedata->section_headers[section->sh_link].sh_type != SHT_DYNSYM))
	    warn (_("[%2u]: Link field (%u) should index a symtab section.\n"),
		  i, section->sh_link);
	  break;

	case SHT_DYNAMIC:
	case SHT_SYMTAB:
	case SHT_DYNSYM:
	case SHT_GNU_verneed:
	case SHT_GNU_verdef:
	case SHT_GNU_LIBLIST:
	  if (section->sh_link == 0
	      || section->sh_link >= filedata->file_header.e_shnum
	      || filedata->section_headers[section->sh_link].sh_type != SHT_STRTAB)
	    warn (_("[%2u]: Link field (%u) should index a string section.\n"),
		  i, section->sh_link);
	  break;

	case SHT_INIT_ARRAY:
	case SHT_FINI_ARRAY:
	case SHT_PREINIT_ARRAY:
	  if (section->sh_type < SHT_LOOS && section->sh_link != 0)
	    warn (_("[%2u]: Unexpected value (%u) in link field.\n"),
		  i, section->sh_link);
	  break;

	default:
	  /* FIXME: Add support for target specific section types.  */
#if 0 	  /* Currently we do not check other section types as there are too
	     many special cases.  Stab sections for example have a type
	     of SHT_PROGBITS but an sh_link field that links to the .stabstr
	     section.  */
	  if (section->sh_type < SHT_LOOS && section->sh_link != 0)
	    warn (_("[%2u]: Unexpected value (%u) in link field.\n"),
		  i, section->sh_link);
#endif
	  break;
	}

      /* Check the sh_info field.  */
      switch (section->sh_type)
	{
	case SHT_REL:
	case SHT_RELA:
	  if (section->sh_info == 0
	      && (filedata->file_header.e_type == ET_EXEC
		  || filedata->file_header.e_type == ET_DYN))
	    /* Dynamic relocations apply to segments, so they do not
	       need to specify the section they relocate.  */
	    break;
	  if (section->sh_info == 0
	      || section->sh_info >= filedata->file_header.e_shnum
	      || (filedata->section_headers[section->sh_info].sh_type != SHT_PROGBITS
		  && filedata->section_headers[section->sh_info].sh_type != SHT_NOBITS
		  && filedata->section_headers[section->sh_info].sh_type != SHT_NOTE
		  && filedata->section_headers[section->sh_info].sh_type != SHT_INIT_ARRAY
		  && filedata->section_headers[section->sh_info].sh_type != SHT_FINI_ARRAY
		  && filedata->section_headers[section->sh_info].sh_type != SHT_PREINIT_ARRAY
		  /* FIXME: Are other section types valid ?  */
		  && filedata->section_headers[section->sh_info].sh_type < SHT_LOOS))
	    warn (_("[%2u]: Info field (%u) should index a relocatable section.\n"),
		  i, section->sh_info);
	  break;

	case SHT_DYNAMIC:
	case SHT_HASH:
	case SHT_SYMTAB_SHNDX:
	case SHT_INIT_ARRAY:
	case SHT_FINI_ARRAY:
	case SHT_PREINIT_ARRAY:
	  if (section->sh_info != 0)
	    warn (_("[%2u]: Unexpected value (%u) in info field.\n"),
		  i, section->sh_info);
	  break;

	case SHT_GROUP:
	case SHT_SYMTAB:
	case SHT_DYNSYM:
	  /* A symbol index - we assume that it is valid.  */
	  break;

	default:
	  /* FIXME: Add support for target specific section types.  */
	  if (section->sh_type == SHT_NOBITS)
	    /* NOBITS section headers with non-zero sh_info fields can be
	       created when a binary is stripped of everything but its debug
	       information.  The stripped sections have their headers
	       preserved but their types set to SHT_NOBITS.  So do not check
	       this type of section.  */
	    ;
	  else if (section->sh_flags & SHF_INFO_LINK)
	    {
	      if (section->sh_info < 1 || section->sh_info >= filedata->file_header.e_shnum)
		warn (_("[%2u]: Expected link to another section in info field"), i);
	    }
	  else if (section->sh_type < SHT_LOOS
		   && (section->sh_flags & SHF_GNU_MBIND) == 0
		   && section->sh_info != 0)
	    warn (_("[%2u]: Unexpected value (%u) in info field.\n"),
		  i, section->sh_info);
	  break;
	}

      /* Check the sh_size field.  */
      if (section->sh_size > filedata->file_size
	  && section->sh_type != SHT_NOBITS
	  && section->sh_type != SHT_NULL
	  && section->sh_type < SHT_LOOS)
	warn (_("Size of section %u is larger than the entire file!\n"), i);

      printf ("  [%2u] ", i);
      if (do_section_details)
	printf ("%s\n      ", printable_section_name (filedata, section));
      else
	print_symbol_name (-17, printable_section_name (filedata, section));

      printf (do_wide ? " %-15s " : " %-15.15s ",
	      get_section_type_name (filedata, section->sh_type));

      if (is_32bit_elf)
	{
	  const char * link_too_big = NULL;

	  print_vma (section->sh_addr, LONG_HEX);

	  printf ( " %6.6lx %6.6lx %2.2lx",
		   (unsigned long) section->sh_offset,
		   (unsigned long) section->sh_size,
		   (unsigned long) section->sh_entsize);

	  if (do_section_details)
	    fputs ("  ", stdout);
	  else
	    printf (" %3s ", get_elf_section_flags (filedata, section->sh_flags));

	  if (section->sh_link >= filedata->file_header.e_shnum)
	    {
	      link_too_big = "";
	      /* The sh_link value is out of range.  Normally this indicates
		 an error but it can have special values in Solaris binaries.  */
	      switch (filedata->file_header.e_machine)
		{
		case EM_386:
		case EM_IAMCU:
		case EM_X86_64:
		case EM_L1OM:
		case EM_K1OM:
		case EM_OLD_SPARCV9:
		case EM_SPARC32PLUS:
		case EM_SPARCV9:
		case EM_SPARC:
		  if (section->sh_link == (SHN_BEFORE & 0xffff))
		    link_too_big = "BEFORE";
		  else if (section->sh_link == (SHN_AFTER & 0xffff))
		    link_too_big = "AFTER";
		  break;
		default:
		  break;
		}
	    }

	  if (do_section_details)
	    {
	      if (link_too_big != NULL && * link_too_big)
		printf ("<%s> ", link_too_big);
	      else
		printf ("%2u ", section->sh_link);
	      printf ("%3u %2lu\n", section->sh_info,
		      (unsigned long) section->sh_addralign);
	    }
	  else
	    printf ("%2u %3u %2lu\n",
		    section->sh_link,
		    section->sh_info,
		    (unsigned long) section->sh_addralign);

	  if (link_too_big && ! * link_too_big)
	    warn (_("section %u: sh_link value of %u is larger than the number of sections\n"),
		  i, section->sh_link);
	}
      else if (do_wide)
	{
	  print_vma (section->sh_addr, LONG_HEX);

	  if ((long) section->sh_offset == section->sh_offset)
	    printf (" %6.6lx", (unsigned long) section->sh_offset);
	  else
	    {
	      putchar (' ');
	      print_vma (section->sh_offset, LONG_HEX);
	    }

	  if ((unsigned long) section->sh_size == section->sh_size)
	    printf (" %6.6lx", (unsigned long) section->sh_size);
	  else
	    {
	      putchar (' ');
	      print_vma (section->sh_size, LONG_HEX);
	    }

	  if ((unsigned long) section->sh_entsize == section->sh_entsize)
	    printf (" %2.2lx", (unsigned long) section->sh_entsize);
	  else
	    {
	      putchar (' ');
	      print_vma (section->sh_entsize, LONG_HEX);
	    }

	  if (do_section_details)
	    fputs ("  ", stdout);
	  else
	    printf (" %3s ", get_elf_section_flags (filedata, section->sh_flags));

	  printf ("%2u %3u ", section->sh_link, section->sh_info);

	  if ((unsigned long) section->sh_addralign == section->sh_addralign)
	    printf ("%2lu\n", (unsigned long) section->sh_addralign);
	  else
	    {
	      print_vma (section->sh_addralign, DEC);
	      putchar ('\n');
	    }
	}
      else if (do_section_details)
	{
	  putchar (' ');
	  print_vma (section->sh_addr, LONG_HEX);
	  if ((long) section->sh_offset == section->sh_offset)
	    printf ("  %16.16lx", (unsigned long) section->sh_offset);
	  else
	    {
	      printf ("  ");
	      print_vma (section->sh_offset, LONG_HEX);
	    }
	  printf ("  %u\n       ", section->sh_link);
	  print_vma (section->sh_size, LONG_HEX);
	  putchar (' ');
	  print_vma (section->sh_entsize, LONG_HEX);

	  printf ("  %-16u  %lu\n",
		  section->sh_info,
		  (unsigned long) section->sh_addralign);
	}
      else
	{
	  putchar (' ');
	  print_vma (section->sh_addr, LONG_HEX);
	  if ((long) section->sh_offset == section->sh_offset)
	    printf ("  %8.8lx", (unsigned long) section->sh_offset);
	  else
	    {
	      printf ("  ");
	      print_vma (section->sh_offset, LONG_HEX);
	    }
	  printf ("\n       ");
	  print_vma (section->sh_size, LONG_HEX);
	  printf ("  ");
	  print_vma (section->sh_entsize, LONG_HEX);

	  printf (" %3s ", get_elf_section_flags (filedata, section->sh_flags));

	  printf ("     %2u   %3u     %lu\n",
		  section->sh_link,
		  section->sh_info,
		  (unsigned long) section->sh_addralign);
	}

      if (do_section_details)
	{
	  printf ("       %s\n", get_elf_section_flags (filedata, section->sh_flags));
	  if ((section->sh_flags & SHF_COMPRESSED) != 0)
	    {
	      /* Minimum section size is 12 bytes for 32-bit compression
		 header + 12 bytes for compressed data header.  */
	      unsigned char buf[24];

	      assert (sizeof (buf) >= sizeof (Elf64_External_Chdr));
	      if (get_data (&buf, filedata, section->sh_offset, 1,
			    sizeof (buf), _("compression header")))
		{
		  Elf_Internal_Chdr chdr;

		  if (get_compression_header (&chdr, buf, sizeof (buf)) == 0)
		    printf (_("       [<corrupt>]\n"));
		  else
		    {
		      if (chdr.ch_type == ch_compress_zlib)
			printf ("       ZLIB, ");
		      else if (chdr.ch_type == ch_compress_zstd)
			printf ("       ZSTD, ");
		      else
			printf (_("       [<unknown>: 0x%x], "),
				chdr.ch_type);
		      print_vma (chdr.ch_size, LONG_HEX);
		      printf (", %lu\n", (unsigned long) chdr.ch_addralign);
		    }
		}
	    }
	}
    }

  if (!do_section_details)
    {
      /* The ordering of the letters shown here matches the ordering of the
	 corresponding SHF_xxx values, and hence the order in which these
	 letters will be displayed to the user.  */
      printf (_("Key to Flags:\n\
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n\
  L (link order), O (extra OS processing required), G (group), T (TLS),\n\
  C (compressed), x (unknown), o (OS specific), E (exclude),\n  "));
      switch (filedata->file_header.e_ident[EI_OSABI])
	{
	case ELFOSABI_GNU:
	case ELFOSABI_FREEBSD:
	  printf (_("R (retain), "));
	  /* Fall through */
	case ELFOSABI_NONE:
	  printf (_("D (mbind), "));
	  break;
	default:
	  break;
	}
      if (filedata->file_header.e_machine == EM_X86_64
	  || filedata->file_header.e_machine == EM_L1OM
	  || filedata->file_header.e_machine == EM_K1OM)
	printf (_("l (large), "));
      else if (filedata->file_header.e_machine == EM_ARM)
	printf (_("y (purecode), "));
      else if (filedata->file_header.e_machine == EM_PPC)
	printf (_("v (VLE), "));
      printf ("p (processor specific)\n");
    }

  return true;
}

static bool
display_relocations (Elf_Internal_Shdr *  section,
		     Filedata *           filedata,
		     bool                 dump_reloc)
{
  relocation_type rel_type = rel_type_from_sh_type (section->sh_type);

  if (rel_type == reltype_unknown)
    return false;

  uint64_t rel_size = section->sh_size;

  if (rel_size == 0)
    return false;

  if (dump_reloc)
    {
      if (filedata->is_separate)
	printf (_("\nIn linked file '%s' relocation section "),
		printable_string (filedata->file_name, 0));
      else
	printf (_("\nRelocation section "));

      if (filedata->string_table == NULL)
	printf ("%d", section->sh_name);
      else
	printf ("'%s'", printable_section_name (filedata, section));
    }

  uint64_t rel_offset = section->sh_offset;
  uint64_t num_rela = rel_size / section->sh_entsize;
  uint64_t num_reloc;
  uint64_t *relrs = NULL;

  if (rel_type == reltype_relr)
    {
      /* Just stating the 'number of entries' in a RELR section can be
	 misleading, since this is not the number of locations relocated, but
	 the number of words in the compressed RELR format.  So also provide
	 the number of locations affected.  */

      num_reloc = count_relr_relocations (filedata, section, &relrs);

      if (dump_reloc)
	{
	  printf (_(" at offset %#" PRIx64), rel_offset);
	  printf (ngettext (" contains %" PRIu64 " entry which relocates",
			    " contains %" PRIu64 " entries which relocate",
			    num_rela), num_rela);
	  printf (ngettext (" %" PRIu64 " location:\n",
			    " %" PRIu64 " locations:\n",
			    num_reloc), num_reloc);
	}
    }
  else
    {
      num_reloc = num_rela;
      if (dump_reloc)
	printf (ngettext (" at offset %#" PRIx64
			  " contains %" PRIu64 " entry:\n",
			  " at offset %#" PRIx64
			  " contains %" PRIu64 " entries:\n",
			  num_rela),
		rel_offset, num_rela);
    }

  update_all_relocations (num_reloc);

  Elf_Internal_Shdr * symsec;
  Elf_Internal_Sym *  symtab = NULL;
  uint64_t            nsyms = 0;
  uint64_t            strtablen = 0;
  char *              strtab = NULL;

  if (section->sh_link == 0
      || section->sh_link >= filedata->file_header.e_shnum)
    {
      /* Symbol data not available.
	 This can happen, especially with RELR relocs.
	 See if there is a .symtab section present.
	 If so then use it.  */
      symsec = find_section_by_name (filedata, ".symtab");
    }
  else
    {
      symsec = filedata->section_headers + section->sh_link;

      if (symsec->sh_type != SHT_SYMTAB
	  && symsec->sh_type != SHT_DYNSYM)
	{
	  free (relrs);
	  return false;
	}
    }

  if (symsec != NULL
      && !get_symtab (filedata, symsec, &symtab, &nsyms, &strtab, &strtablen))
    {
      free (relrs);
      return false;
    }

  bool res;

  if (rel_type == reltype_relr)
    {
      res = dump_relr_relocations (filedata, section->sh_size,
				   section->sh_entsize,
				   section->sh_offset,
				   relrs,
				   symtab, nsyms, strtab, strtablen,
				   dump_reloc);
      free (relrs);
    }
  else
    res = dump_relocations (filedata, rel_offset, rel_size,
			    symtab, nsyms, strtab, strtablen,
			    rel_type,
			    symsec == NULL
			    ? false : symsec->sh_type == SHT_DYNSYM,
			    dump_reloc);
  free (strtab);
  free (symtab);

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

      for (i = 0, section = filedata->section_headers;
	   i < filedata->file_header.e_shnum;
	   i++, section++)
	{
	  	section = filedata->section_headers;
		if (section != NULL)
			for (i = 0; i < filedata->file_header.e_shnum; i++, section++)
          		if (display_relocations (section, filedata, do_reloc))
            		found = true;
	}

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
