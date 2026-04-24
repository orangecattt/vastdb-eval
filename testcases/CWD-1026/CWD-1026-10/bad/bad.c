#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SARMAG 8
#define ARFMAG "`\012"

#define FALSE 0
#define TRUE 1

#define const_strneq(a,b) (strncmp ((a), (b), sizeof (b) - 1) == 0)

#define IS_DIR_SEPARATOR_1(dos_based, c)				\
  (((c) == '/')								\
   || (((c) == '\\') && (dos_based)))

#define HAS_DRIVE_SPEC_1(dos_based, f)			\
  ((f)[0] && ((f)[1] == ':') && (dos_based))

#define IS_ABSOLUTE_PATH_1(dos_based, f)			\
  (IS_DIR_SEPARATOR_1 (dos_based, (f)[0])			\
   || HAS_DRIVE_SPEC_1 (dos_based, f))

#define IS_UNIX_ABSOLUTE_PATH(f) IS_ABSOLUTE_PATH_1 (0, f)
#define IS_ABSOLUTE_PATH(f) IS_UNIX_ABSOLUTE_PATH (f)

#define _(String) (String)
#define ngettext(Msgid1, Msgid2, n) \
  (n == 1 ? Msgid1 : Msgid2)

typedef int bfd_boolean;

typedef unsigned long elf_vma;

typedef enum print_mode
{
  HEX,
  DEC,
  DEC_5,
  UNSIGNED,
  PREFIX_HEX,
  FULL_HEX,
  LONG_HEX
}
print_mode;

struct ar_hdr
{
  char ar_name[16];
  char ar_date[12];
  char ar_uid[6];
  char ar_gid[6];
  char ar_mode[8];
  char ar_size[10];
  char ar_fmag[2];
};

struct archive_info
{
  char * file_name;
  FILE * file;
  elf_vma index_num;
  elf_vma * index_array;
  char * sym_table;
  unsigned long sym_size;
  char * longnames;
  unsigned long longnames_size;
  unsigned long nested_member_origin;
  unsigned long next_arhdr_offset;
  bfd_boolean is_thin_archive;
  bfd_boolean uses_64bit_indices;
  struct ar_hdr arhdr;
};

typedef struct filedata
{
  const char *         file_name;
  FILE *               handle;
  size_t               file_size;
  void *               section_headers;
  void *               program_headers;
  char *               string_table;
  unsigned long        string_table_length;
  void *               dump_sects;
  unsigned int         num_dump_sects;
} Filedata;

extern char * program_name;
static bfd_boolean show_name = FALSE;
static bfd_boolean do_archive_index = FALSE;
static unsigned long archive_file_offset;
static unsigned long archive_file_size;
static bfd_boolean do_dynamic = FALSE;
static bfd_boolean do_syms = FALSE;
static bfd_boolean do_dyn_syms = FALSE;
static bfd_boolean do_reloc = FALSE;
static bfd_boolean do_sections = FALSE;
static bfd_boolean do_section_groups = FALSE;
static bfd_boolean do_segments = FALSE;
static bfd_boolean do_unwind = FALSE;
static bfd_boolean do_header = FALSE;
static bfd_boolean do_dump = FALSE;
static bfd_boolean do_version = FALSE;
static bfd_boolean do_histogram = FALSE;
static bfd_boolean do_debugging = FALSE;
static bfd_boolean do_arch = FALSE;
static bfd_boolean do_notes = FALSE;

extern const char *lbasename (const char *);
extern int process_archive_index_and_symbols (struct archive_info *, unsigned int, bfd_boolean);
extern bfd_boolean process_object (Filedata *);
extern Filedata * open_file (const char *);
extern void close_file (Filedata *);
extern char * get_archive_member_name (struct archive_info *, struct archive_info *);
extern char * get_archive_member_name_at (struct archive_info *, unsigned long, struct archive_info *);
extern unsigned int print_vma (elf_vma, print_mode);
extern void release_archive (struct archive_info *);

void
error (const char *message, ...)
{
  va_list args;

  /* Try to keep error messages in sync with the program's normal output.  */
  fflush (stdout);

  va_start (args, message);
  fprintf (stderr, _("%s: Error: "), program_name);
  vfprintf (stderr, message, args);
  va_end (args);
}

char *
make_qualified_name (struct archive_info * arch,
		     struct archive_info * nested_arch,
		     const char *member_name)
{
  const char * error_name = _("<corrupt>");
  size_t len;
  char * name;

  len = strlen (arch->file_name) + strlen (member_name) + 3;
  if (arch->is_thin_archive
      && arch->nested_member_origin != 0)
    {
      /* PR 15140: Allow for corrupt thin archives.  */
      if (nested_arch->file_name)
	len += strlen (nested_arch->file_name) + 2;
      else
	len += strlen (error_name) + 2;
    }

  name = (char *) malloc (len);
  if (name == NULL)
    {
      error (_("Out of memory\n"));
      return NULL;
    }

  if (arch->is_thin_archive
      && arch->nested_member_origin != 0)
    {
      if (nested_arch->file_name)
	snprintf (name, len, "%s[%s(%s)]", arch->file_name,
		  nested_arch->file_name, member_name);
      else
	snprintf (name, len, "%s[%s(%s)]", arch->file_name,
		  error_name, member_name);
    }
  else if (arch->is_thin_archive)
    snprintf (name, len, "%s[%s]", arch->file_name, member_name);
  else
    snprintf (name, len, "%s(%s)", arch->file_name, member_name);

  return name;
}

char *
adjust_relative_path (const char *file_name, const char *name,
		      unsigned long name_len)
{
  char * member_file_name;
  const char * base_name = lbasename (file_name);
  size_t amt;

  /* This is a proxy entry for a thin archive member.
     If the extended name table contains an absolute path
     name, or if the archive is in the current directory,
     use the path name as given.  Otherwise, we need to
     find the member relative to the directory where the
     archive is located.  */
  if (IS_ABSOLUTE_PATH (name) || base_name == file_name)
    {
      amt = name_len + 1;
      if (amt == 0)
	return NULL;
      member_file_name = (char *) malloc (amt);
      if (member_file_name == NULL)
        {
          error (_("Out of memory\n"));
          return NULL;
        }
      memcpy (member_file_name, name, name_len);
      member_file_name[name_len] = '\0';
    }
  else
    {
      /* Concatenate the path components of the archive file name
         to the relative path name from the extended name table.  */
      size_t prefix_len = base_name - file_name;

      amt = prefix_len + name_len + 1;
      /* PR 17531: file: 2896dc8b
	 Catch wraparound.  */
      if (amt < prefix_len || amt < name_len)
	{
	  error (_("Abnormal length of thin archive member name: %lx\n"),
		 name_len);
	  return NULL;
	}

      member_file_name = (char *) malloc (amt);
      if (member_file_name == NULL)
        {
          error (_("Out of memory\n"));
          return NULL;
        }
      memcpy (member_file_name, file_name, prefix_len);
      memcpy (member_file_name + prefix_len, name, name_len);
      member_file_name[prefix_len + name_len] = '\0';
    }
  return member_file_name;
}

int
setup_archive (struct archive_info *arch, const char *file_name,
	       FILE *file, bfd_boolean is_thin_archive,
	       bfd_boolean read_symbols)
{
  size_t got;

  arch->file_name = strdup (file_name);
  arch->file = file;
  arch->index_num = 0;
  arch->index_array = NULL;
  arch->sym_table = NULL;
  arch->sym_size = 0;
  arch->longnames = NULL;
  arch->longnames_size = 0;
  arch->nested_member_origin = 0;
  arch->is_thin_archive = is_thin_archive;
  arch->uses_64bit_indices = FALSE;
  arch->next_arhdr_offset = SARMAG;

  /* Read the first archive member header.  */
  if (fseek (file, SARMAG, SEEK_SET) != 0)
    {
      error (_("%s: failed to seek to first archive header\n"), file_name);
      return 1;
    }
  got = fread (&arch->arhdr, 1, sizeof arch->arhdr, file);
  if (got != sizeof arch->arhdr)
    {
      if (got == 0)
	return 0;

      error (_("%s: failed to read archive header\n"), file_name);
      return 1;
    }

  /* See if this is the archive symbol table.  */
  if (const_strneq (arch->arhdr.ar_name, "/               "))
    {
      if (! process_archive_index_and_symbols (arch, 4, read_symbols))
	return 1;
    }
  else if (const_strneq (arch->arhdr.ar_name, "/SYM64/         "))
    {
      arch->uses_64bit_indices = TRUE;
      if (! process_archive_index_and_symbols (arch, 8, read_symbols))
	return 1;
    }
  else if (read_symbols)
    printf (_("%s has no archive index\n"), file_name);

  if (const_strneq (arch->arhdr.ar_name, "//              "))
    {
      /* This is the archive string table holding long member names.  */
      char fmag_save = arch->arhdr.ar_fmag[0];
      arch->arhdr.ar_fmag[0] = 0;
      arch->longnames_size = strtoul (arch->arhdr.ar_size, NULL, 10);
      arch->arhdr.ar_fmag[0] = fmag_save;
      /* PR 17531: file: 01068045.  */
      if (arch->longnames_size < 8)
	{
	  error (_("%s: long name table is too small, (size = %ld)\n"),
		 file_name, arch->longnames_size);
	  return 1;
	}
      /* PR 17531: file: 639d6a26.  */
      if ((signed long) arch->longnames_size < 0)
	{
	  error (_("%s: long name table is too big, (size = 0x%lx)\n"),
		 file_name, arch->longnames_size);
	  return 1;
	}

      arch->next_arhdr_offset += sizeof arch->arhdr + arch->longnames_size;

      /* Plus one to allow for a string terminator.  */
      arch->longnames = (char *) malloc (arch->longnames_size + 1);
      if (arch->longnames == NULL)
	{
	  error (_("Out of memory reading long symbol names in archive\n"));
	  return 1;
	}

      if (fread (arch->longnames, arch->longnames_size, 1, file) != 1)
	{
	  free (arch->longnames);
	  arch->longnames = NULL;
	  error (_("%s: failed to read long symbol name string table\n"),
		 file_name);
	  return 1;
	}

      if ((arch->longnames_size & 1) != 0)
	getc (file);

      arch->longnames[arch->longnames_size] = 0;
    }

  return 0;
}

static bfd_boolean
process_archive (Filedata * filedata, bfd_boolean is_thin_archive)
{
  struct archive_info arch;
  struct archive_info nested_arch;
  size_t got;
  bfd_boolean ret = TRUE;

  show_name = TRUE;

  /* The ARCH structure is used to hold information about this archive.  */
  arch.file_name = NULL;
  arch.file = NULL;
  arch.index_array = NULL;
  arch.sym_table = NULL;
  arch.longnames = NULL;

  /* The NESTED_ARCH structure is used as a single-item cache of information
     about a nested archive (when members of a thin archive reside within
     another regular archive file).  */
  nested_arch.file_name = NULL;
  nested_arch.file = NULL;
  nested_arch.index_array = NULL;
  nested_arch.sym_table = NULL;
  nested_arch.longnames = NULL;

  if (setup_archive (&arch, filedata->file_name, filedata->handle,
		     is_thin_archive, do_archive_index) != 0)
    {
      ret = FALSE;
      goto out;
    }

  if (do_archive_index)
    {
      if (arch.sym_table == NULL)
	error (_("%s: unable to dump the index as none was found\n"), filedata->file_name);
      else
	{
	  unsigned long i, l;
	  unsigned long current_pos;

	  printf (_("Index of archive %s: (%lu entries, 0x%lx bytes in the symbol table)\n"),
		  filedata->file_name, (unsigned long) arch.index_num, arch.sym_size);

	  current_pos = ftell (filedata->handle);

	  for (i = l = 0; i < arch.index_num; i++)
	    {
	      if ((i == 0) || ((i > 0) && (arch.index_array[i] != arch.index_array[i - 1])))
	        {
	          char * member_name;

		  member_name = get_archive_member_name_at (&arch, arch.index_array[i], &nested_arch);

                  if (member_name != NULL)
                    {
	              char * qualified_name = make_qualified_name (&arch, &nested_arch, member_name);

                      if (qualified_name != NULL)
                        {
		          printf (_("Contents of binary %s at offset "), qualified_name);
			  (void) print_vma (arch.index_array[i], PREFIX_HEX);
			  putchar ('\n');
		          free (qualified_name);
		        }
		    }
		}

	      if (l >= arch.sym_size)
		{
		  error (_("%s: end of the symbol table reached before the end of the index\n"),
			 filedata->file_name);
		  ret = FALSE;
		  break;
		}
	      /* PR 17531: file: 0b6630b2.  */
	      printf ("\t%.*s\n", (int) (arch.sym_size - l), arch.sym_table + l);
	      l += strnlen (arch.sym_table + l, arch.sym_size - l) + 1;
	    }

	  if (arch.uses_64bit_indices)
	    l = (l + 7) & ~ 7;
	  else
	    l += l & 1;

	  if (l < arch.sym_size)
	    {
	      error (ngettext ("%s: %ld byte remains in the symbol table, "
			       "but without corresponding entries in "
			       "the index table\n",
			       "%s: %ld bytes remain in the symbol table, "
			       "but without corresponding entries in "
			       "the index table\n",
			       arch.sym_size - l),
		     filedata->file_name, arch.sym_size - l);
	      ret = FALSE;
	    }

	  if (fseek (filedata->handle, current_pos, SEEK_SET) != 0)
	    {
	      error (_("%s: failed to seek back to start of object files in the archive\n"),
		     filedata->file_name);
	      ret = FALSE;
	      goto out;
	    }
	}

      if (!do_dynamic && !do_syms && !do_reloc && !do_unwind && !do_sections
	  && !do_segments && !do_header && !do_dump && !do_version
	  && !do_histogram && !do_debugging && !do_arch && !do_notes
	  && !do_section_groups && !do_dyn_syms)
	{
	  ret = TRUE; /* Archive index only.  */
	  goto out;
	}
    }

  while (1)
    {
      char * name;
      size_t namelen;
      char * qualified_name;

      /* Read the next archive header.  */
      if (fseek (filedata->handle, arch.next_arhdr_offset, SEEK_SET) != 0)
        {
          error (_("%s: failed to seek to next archive header\n"), filedata->file_name);
          return FALSE;
        }
      got = fread (&arch.arhdr, 1, sizeof arch.arhdr, filedata->handle);
      if (got != sizeof arch.arhdr)
        {
          if (got == 0)
	    break;
          error (_("%s: failed to read archive header\n"), filedata->file_name);
          ret = FALSE;
          break;
        }
      if (memcmp (arch.arhdr.ar_fmag, ARFMAG, 2) != 0)
        {
          error (_("%s: did not find a valid archive header\n"), arch.file_name);
          ret = FALSE;
          break;
        }

      arch.next_arhdr_offset += sizeof arch.arhdr;

      archive_file_size = strtoul (arch.arhdr.ar_size, NULL, 10);
      if (archive_file_size & 01)
        ++archive_file_size;

      name = get_archive_member_name (&arch, &nested_arch);
      if (name == NULL)
	{
	  error (_("%s: bad archive file name\n"), filedata->file_name);
	  ret = FALSE;
	  break;
	}
      namelen = strlen (name);

      qualified_name = make_qualified_name (&arch, &nested_arch, name);
      if (qualified_name == NULL)
	{
	  error (_("%s: bad archive file name\n"), filedata->file_name);
	  ret = FALSE;
	  break;
	}

      if (is_thin_archive && arch.nested_member_origin == 0)
        {
          /* This is a proxy for an external member of a thin archive.  */
          Filedata * member_filedata;
          char * member_file_name = adjust_relative_path
	    (filedata->file_name, name, namelen);

          if (member_file_name == NULL)
            {
              ret = FALSE;
              break;
            }

          member_filedata = open_file (member_file_name);
          if (member_filedata == NULL)
            {
              error (_("Input file '%s' is not readable.\n"), member_file_name);
              free (member_file_name);
              ret = FALSE;
              break;
            }

          archive_file_offset = arch.nested_member_origin;
	  member_filedata->file_name = qualified_name;

          if (! process_object (member_filedata))
	    ret = FALSE;

          close_file (member_filedata);
          free (member_file_name);
        }
      else if (is_thin_archive)
        {
          Filedata thin_filedata;

          memset (&thin_filedata, 0, sizeof (thin_filedata));

	  /* PR 15140: Allow for corrupt thin archives.  */
	  if (nested_arch.file == NULL)
	    {
	      error (_("%s: contains corrupt thin archive: %s\n"),
		     filedata->file_name, name);
	      ret = FALSE;
	      break;
	    }

          /* This is a proxy for a member of a nested archive.  */
          archive_file_offset = arch.nested_member_origin + sizeof arch.arhdr;

          /* The nested archive file will have been opened and setup by
             get_archive_member_name.  */
          if (fseek (nested_arch.file, archive_file_offset, SEEK_SET) != 0)
            {
              error (_("%s: failed to seek to archive member.\n"), nested_arch.file_name);
              ret = FALSE;
              break;
            }

	  thin_filedata.handle = nested_arch.file;
	  thin_filedata.file_name = qualified_name;
	  
          if (! process_object (& thin_filedata))
	    ret = FALSE;
        }
      else
        {
          archive_file_offset = arch.next_arhdr_offset;
          arch.next_arhdr_offset += archive_file_size;

	  filedata->file_name = qualified_name;
          if (! process_object (filedata))
	    ret = FALSE;
        }

      if (filedata->dump_sects != NULL)
	{
	  free (filedata->dump_sects);
	  filedata->dump_sects = NULL;
	  filedata->num_dump_sects = 0;
	}

      free (qualified_name);
    }

 out:
  if (nested_arch.file != NULL)
    fclose (nested_arch.file);
  release_archive (&nested_arch);
  release_archive (&arch);

  return ret;
}
