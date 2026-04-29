#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>

/* === Macros === */
#define _(x) (x)
#define ATTRIBUTE_UNUSED __attribute__((__unused__))
#define ISDIGIT(c) (((c) >= '0' && (c) <= '9') ? 1 : 0)
#define ISUPPER(c) (((c) >= 'A' && (c) <= 'Z') ? 1 : 0)
#define ISLOWER(c) (((c) >= 'a' && (c) <= 'z') ? 1 : 0)
#define ISSLASH(C) ((C) == '/')
#define IS_ABSOLUTE_FILE_NAME(Filename) ISSLASH((Filename)[0])
#define IS_ABSOLUTE_PATH IS_ABSOLUTE_FILE_NAME

#define N_FN        0x1f
#define N_FN_SEQ    0x0C
#define N_SO        0x64
#define N_LBRAC     0xc0
#define N_RBRAC     0xe0
#define N_SOL       0x84
#define N_BINCL     0x82
#define N_EINCL     0xa2
#define N_EXCL      0xc2
#define N_SLINE     0x44
#define N_BCOMM     0xe2
#define N_ECOMM     0xe4
#define N_FUN       0x24
#define N_OPT       0x3c
#define N_OBJ       0x38
#define N_ENDM      0x62
#define N_MAIN      0x2a
#define N_WARNING   0x1e
#define N_STSYM     0x26
#define N_LCSYM     0x28
#define N_ROSYM     0x2c
#define SEC_HAS_CONTENTS 0x100
#define DEBUG_LINENO_COUNT 10
#define STAB_TYPES_SLOTS 16
#define XCOFF_TYPE_COUNT 34
#define SAVE_STABS_COUNT 64
#define VOFFSET_STATIC_METHOD ((bfd_vma) -1)
#define DEBUG_METHOD_NULL ((debug_method) NULL)
#define DEBUG_METHOD_VARIANT_NULL ((debug_method_variant) NULL)
#define DEBUG_BASECLASS_NULL ((debug_baseclass) NULL)

/* === BFD Types === */
typedef uint64_t bfd_vma;
typedef int64_t bfd_signed_vma;
typedef uint64_t bfd_size_type;
typedef uint8_t bfd_byte;
typedef int64_t file_ptr;
typedef uint32_t flagword;
typedef struct bfd bfd;
typedef struct bfd_section asection;
typedef struct bfd_symbol asymbol;

struct bfd_section {
  const char *name; struct bfd_section *next; struct bfd_section *prev;
  unsigned int id, section_id, index; flagword flags;
  unsigned int user_set_vma:1, linker_mark:1, linker_has_input:1, gc_mark:1, compress_status:2;
  unsigned int segment_mark:1, sec_info_type:3, use_rela_p:1, mmapped_p:1, alloced:1;
  unsigned int sec_flg0:1, sec_flg1:1, sec_flg2:1, sec_flg3:1, sec_flg4:1, sec_flg5:1;
  bfd_vma vma, lma; bfd_size_type size, rawsize, compressed_size; bfd_vma output_offset;
  struct bfd_section *output_section; void *relocation, *orelocation; unsigned reloc_count;
  unsigned int alignment_power; file_ptr filepos, rel_filepos, line_filepos;
  void *userdata; bfd_byte *contents; void *lineno; unsigned int lineno_count, entsize;
  void *kept_section; file_ptr moving_line_filepos; int target_index;
  void *used_by_bfd, *constructor_chain; bfd *owner; void *symbol;
  union { void *link_order; struct bfd_section *s; const char *linked_to_symbol_name; } map_head, map_tail;
  struct bfd_section *already_assigned; unsigned int type;
};
static inline flagword bfd_section_flags(const asection *sec) { return sec->flags; }
static inline bfd_size_type bfd_section_size(const asection *sec) { return sec->size; }

struct bfd_symbol { struct bfd *the_bfd; const char *name; uint64_t value; flagword flags; struct bfd_section *section; union { void *p; bfd_vma i; } udata; };
struct bfd_target { const char *name; };
struct bfd { const char *filename; struct bfd_target *xvec; unsigned int flags; };
static inline const char *bfd_get_filename(const bfd *abfd) { return abfd->filename; }

/* === Debug Types === */
enum debug_type_kind {
  DEBUG_KIND_ILLEGAL, DEBUG_KIND_INDIRECT, DEBUG_KIND_VOID, DEBUG_KIND_INT,
  DEBUG_KIND_FLOAT, DEBUG_KIND_COMPLEX, DEBUG_KIND_BOOL, DEBUG_KIND_STRUCT,
  DEBUG_KIND_UNION, DEBUG_KIND_CLASS, DEBUG_KIND_UNION_CLASS, DEBUG_KIND_ENUM,
  DEBUG_KIND_POINTER, DEBUG_KIND_FUNCTION, DEBUG_KIND_REFERENCE, DEBUG_KIND_RANGE,
  DEBUG_KIND_ARRAY, DEBUG_KIND_SET, DEBUG_KIND_OFFSET, DEBUG_KIND_METHOD,
  DEBUG_KIND_CONST, DEBUG_KIND_VOLATILE, DEBUG_KIND_NAMED, DEBUG_KIND_TAGGED
};
enum debug_var_kind { DEBUG_VAR_ILLEGAL, DEBUG_GLOBAL, DEBUG_STATIC, DEBUG_LOCAL_STATIC, DEBUG_LOCAL, DEBUG_REGISTER };
enum debug_parm_kind { DEBUG_PARM_ILLEGAL, DEBUG_PARM_STACK, DEBUG_PARM_REG, DEBUG_PARM_REFERENCE, DEBUG_PARM_REF_REG };
enum debug_visibility { DEBUG_VISIBILITY_PUBLIC, DEBUG_VISIBILITY_PROTECTED, DEBUG_VISIBILITY_PRIVATE, DEBUG_VISIBILITY_IGNORE };

typedef struct debug_type_s *debug_type;
#define DEBUG_TYPE_NULL ((debug_type) NULL)
typedef struct debug_field_s *debug_field;
#define DEBUG_FIELD_NULL ((debug_field) NULL)
typedef struct debug_baseclass_s *debug_baseclass;
typedef struct debug_method_s *debug_method;
typedef struct debug_method_variant_s *debug_method_variant;

struct debug_indirect_type; struct debug_class_type; struct debug_enum_type; struct debug_function_type;
struct debug_range_type; struct debug_array_type; struct debug_set_type; struct debug_offset_type;
struct debug_method_type; struct debug_named_type; struct debug_unit; struct debug_file;
struct debug_function; struct debug_block; struct debug_lineno; struct debug_namespace;
struct debug_name; struct debug_parameter; struct debug_variable; struct debug_typed_constant;
struct debug_class_id; struct debug_type_compare_list; struct debug_type_real_list;
struct stab_handle; struct stab_tag; struct stab_pending_var; struct stab_types; struct bincl_file;
struct debug_write_fns;

struct debug_type_s {
  enum debug_type_kind kind; unsigned int size; unsigned int mark; debug_type pointer;
  union {
    struct debug_indirect_type *kindirect; bool kint; struct debug_class_type *kclass;
    struct debug_enum_type *kenum; struct debug_type_s *kpointer; struct debug_function_type *kfunction;
    struct debug_type_s *kreference; struct debug_range_type *krange; struct debug_array_type *karray;
    struct debug_set_type *kset; struct debug_offset_type *koffset; struct debug_method_type *kmethod;
    struct debug_type_s *kconst; struct debug_type_s *kvolatile; struct debug_named_type *knamed;
  } u;
};
struct debug_indirect_type { debug_type *slot; const char *tag; };
struct debug_class_type { debug_field *fields; unsigned int mark, id; debug_baseclass *baseclasses; debug_method *methods; debug_type vptrbase; };
struct debug_enum_type { const char **names; bfd_signed_vma *values; };
struct debug_function_type { debug_type return_type; debug_type *arg_types; bool varargs; };
struct debug_range_type { debug_type type; bfd_signed_vma lower, upper; };
struct debug_array_type { debug_type element_type, range_type; bfd_signed_vma lower, upper; bool stringp; };
struct debug_set_type { debug_type type; bool bitstringp; };
struct debug_offset_type { debug_type base_type, target_type; };
struct debug_method_type { debug_type return_type, domain_type; debug_type *arg_types; bool varargs; };
struct debug_named_type { struct debug_name *name; debug_type type; };

struct debug_field_s {
  const char *name; struct debug_type_s *type; enum debug_visibility visibility; bool static_member;
  union { struct { unsigned int bitpos, bitsize; } f; struct { const char *physname; } s; } u;
};
struct debug_baseclass_s { struct debug_type_s *type; unsigned int bitpos; bool is_virtual; enum debug_visibility visibility; };
struct debug_method_s { const char *name; struct debug_method_variant_s **variants; };
struct debug_method_variant_s { const char *physname; struct debug_type_s *type; enum debug_visibility visibility; bool constp, volatilep; bfd_vma voffset; struct debug_type_s *context; };
struct debug_variable { enum debug_var_kind kind; debug_type type; bfd_vma val; };
struct debug_function { debug_type return_type; struct debug_parameter *parameters; struct debug_block *blocks; };
struct debug_parameter { struct debug_parameter *next; const char *name; debug_type type; enum debug_parm_kind kind; bfd_vma val; };
struct debug_typed_constant { debug_type type; bfd_vma val; };
struct debug_block { struct debug_block *next, *parent, *children; bfd_vma start, end; struct debug_namespace *locals; };
struct debug_lineno { struct debug_lineno *next; struct debug_file *file; unsigned long linenos[DEBUG_LINENO_COUNT]; bfd_vma addrs[DEBUG_LINENO_COUNT]; };
struct debug_namespace { struct debug_name *list; struct debug_name **tail; };
enum debug_object_kind { DEBUG_OBJECT_TYPE, DEBUG_OBJECT_TAG, DEBUG_OBJECT_VARIABLE, DEBUG_OBJECT_FUNCTION, DEBUG_OBJECT_INT_CONSTANT, DEBUG_OBJECT_FLOAT_CONSTANT, DEBUG_OBJECT_TYPED_CONSTANT };
enum debug_object_linkage { DEBUG_LINKAGE_AUTOMATIC, DEBUG_LINKAGE_STATIC, DEBUG_LINKAGE_GLOBAL, DEBUG_LINKAGE_NONE };
struct debug_name {
  struct debug_name *next; const char *name; unsigned int mark;
  enum debug_object_kind kind; enum debug_object_linkage linkage;
  union { struct debug_type_s *type, *tag; struct debug_variable *variable; struct debug_function *function; bfd_vma int_constant; double float_constant; struct debug_typed_constant *typed_constant; } u;
};
struct debug_unit { struct debug_unit *next; struct debug_file *files; struct debug_lineno *linenos; };
struct debug_file { struct debug_file *next; const char *filename; struct debug_namespace *globals; };
struct debug_handle {
  bfd *abfd; struct debug_unit *units, *current_unit; struct debug_file *current_file;
  struct debug_function *current_function; struct debug_block *current_block; struct debug_lineno *current_lineno;
  unsigned int mark, class_id, base_id; struct debug_lineno *current_write_lineno;
  unsigned int current_write_lineno_index; struct debug_class_id *id_list; struct debug_type_compare_list *compare_list;
};
struct debug_class_id { struct debug_class_id *next; struct debug_type_s *type; const char *tag; };
struct debug_type_compare_list { struct debug_type_compare_list *next; struct debug_type_s *t1, *t2; };
struct debug_type_real_list { struct debug_type_real_list *next; struct debug_type_s *t; };

struct stab_pending_var { struct stab_pending_var *next; const char *name; debug_type type; enum debug_var_kind kind; bfd_vma val; };
struct stab_types { struct stab_types *next; unsigned int base_index; debug_type types[STAB_TYPES_SLOTS]; };
struct stab_tag { struct stab_tag *next; const char *name; enum debug_type_kind kind; debug_type slot, type; };
struct bincl_file { struct bincl_file *next, *next_stack; const char *name; bfd_vma hash; unsigned int file; struct stab_types *file_types; };
struct stab_handle {
  bfd *abfd; bool sections; asymbol **syms; long symcount; char *so_string; bfd_vma so_value;
  bfd_vma file_start_offset, function_start_offset; int gcc_compiled; bool n_opt_found;
  char *main_filename; struct bincl_file *bincl_stack, *bincl_list;
  bool within_function; bfd_vma function_end; int block_depth; struct stab_pending_var *pending;
  unsigned int files; struct stab_types **file_types; debug_type xcoff_types[XCOFF_TYPE_COUNT];
  struct stab_tag *tags; bool self_crossref;
};

struct debug_write_fns {
  bool (*start_compilation_unit)(void *, const char *); bool (*start_source)(void *, const char *);
  bool (*empty_type)(void *); bool (*void_type)(void *); bool (*int_type)(void *, unsigned int, bool);
  bool (*float_type)(void *, unsigned int); bool (*complex_type)(void *, unsigned int);
  bool (*bool_type)(void *, unsigned int); bool (*enum_type)(void *, const char *, const char **, bfd_signed_vma *);
  bool (*pointer_type)(void *); bool (*function_type)(void *, int, bool); bool (*reference_type)(void *);
  bool (*range_type)(void *, bfd_signed_vma, bfd_signed_vma); bool (*array_type)(void *, bfd_signed_vma, bfd_signed_vma, bool);
  bool (*set_type)(void *, bool); bool (*offset_type)(void *); bool (*method_type)(void *, bool, int, bool);
  bool (*const_type)(void *); bool (*volatile_type)(void *);
  bool (*start_struct_type)(void *, const char *, unsigned int, bool, unsigned int);
  bool (*struct_field)(void *, const char *, bfd_vma, bfd_vma, enum debug_visibility);
  bool (*end_struct_type)(void *);
  bool (*start_class_type)(void *, const char *, unsigned int, bool, unsigned int, bool, bool);
  bool (*class_static_member)(void *, const char *, const char *, enum debug_visibility);
  bool (*class_baseclass)(void *, bfd_vma, bool, enum debug_visibility);
  bool (*class_start_method)(void *, const char *);
  bool (*class_method_variant)(void *, const char *, enum debug_visibility, bool, bool, bfd_vma, bool);
  bool (*class_static_method_variant)(void *, const char *, enum debug_visibility, bool, bool);
  bool (*class_end_method)(void *); bool (*end_class_type)(void *);
  bool (*typedef_type)(void *, const char *); bool (*tag_type)(void *, const char *, unsigned int, enum debug_type_kind);
  bool (*typdef)(void *, const char *); bool (*tag)(void *, const char *);
  bool (*int_constant)(void *, const char *, bfd_vma); bool (*float_constant)(void *, const char *, double);
  bool (*typed_constant)(void *, const char *, bfd_vma);
  bool (*variable)(void *, const char *, enum debug_var_kind, bfd_vma);
  bool (*start_function)(void *, const char *, bool);
  bool (*function_parameter)(void *, const char *, enum debug_parm_kind, bfd_vma);
  bool (*start_block)(void *, bfd_vma); bool (*end_block)(void *, bfd_vma);
  bool (*end_function)(void *); bool (*lineno)(void *, const char *, unsigned long, bfd_vma);
};

/* === Stub types for dump_bfd references === */
struct elf_backend_data { struct { int arch_size; } *s; bool sign_extend_vma; };
struct separate_info { struct separate_info *next; bfd *handle; };
struct pr_stack { struct pr_stack *next; char *type, *method, *parents; };
struct pr_handle { FILE *f; int indent; struct pr_stack *stack; int parameter; char *filename; bfd *abfd; asymbol **syms; char *(*demangler)(struct bfd *, const char *, int); };

static struct separate_info *first_separate_info = NULL;
static int do_follow_links=0, process_links=0, dump_debugging_tags=0, suppress_bfd_header=0;
static int dump_ar_hdrs=0, dump_file_header=0, dump_private_headers=0;
static void *dump_private_options=NULL;
static int dump_section_headers=0, dump_symtab=0, dump_dynamic_symtab=0;
static int dump_reloc_info=0, dump_dynamic_reloc_info=0, disassemble=0;
static int dump_debugging=0, dump_dwarf_section_info=0;
static int dump_ctf_section_info=0, dump_sframe_section_info=0, dump_stab_section_info=0, dump_section_contents=0;
static const char *dump_ctf_section_name=NULL, *dump_ctf_parent_name=NULL, *dump_ctf_parent_section_name=NULL;
static const char *dump_sframe_section_name=NULL;
static uint64_t start_address=0, stop_address=0; static int64_t adjust_section_vma=0;
static asymbol **syms=NULL; static long symcount=0;
static asymbol **dynsyms=NULL; static long dynsymcount=0;
static void *synthsyms=NULL; static long synthcount=0;
static const char *(*byte_get)(const unsigned char *, int)=NULL;
static int exit_status=0;
static const struct debug_write_fns tg_fns={0};
static const struct debug_write_fns pr_fns={0};

/* === Static helper functions used by bad.c (need forward decls + stubs) === */
static void debug_error(const char *);
static struct debug_name *debug_add_to_namespace(struct debug_handle *, struct debug_namespace **, const char *, enum debug_object_kind, enum debug_object_linkage);

/* === External function declarations (declarations only, not definitions) === */
void *debug_xalloc(void *, size_t);
void *debug_xzalloc(void *, size_t);
bool debug_set_filename(void *, const char *);
bool debug_start_source(void *, const char *);
bool debug_end_function(void *, bfd_vma);
bool debug_start_block(void *, bfd_vma);
bool debug_end_block(void *, bfd_vma);
bool debug_record_line(void *, unsigned long, bfd_vma);
bool debug_start_common_block(void *, const char *);
bool debug_end_common_block(void *, const char *);
debug_type debug_make_indirect_type(void *, debug_type *, const char *);
debug_type debug_make_void_type(void *);
debug_type debug_make_int_type(void *, unsigned int, bool);
debug_type debug_make_float_type(void *, unsigned int);
debug_type debug_make_bool_type(void *, unsigned int);
debug_type debug_make_complex_type(void *, unsigned int);
debug_type debug_make_struct_type(void *, bool, bfd_vma, debug_field *);
debug_type debug_make_object_type(void *, bool, bfd_vma, debug_field *, debug_baseclass *, debug_method *, debug_type, bool);
debug_type debug_make_pointer_type(void *, debug_type);
debug_type debug_make_function_type(void *, debug_type, debug_type *, bool);
debug_type debug_make_reference_type(void *, debug_type);
debug_type debug_make_range_type(void *, debug_type, bfd_signed_vma, bfd_signed_vma);
debug_type debug_make_array_type(void *, debug_type, debug_type, bfd_signed_vma, bfd_signed_vma, bool);
debug_type debug_make_set_type(void *, debug_type, bool);
debug_type debug_make_offset_type(void *, debug_type, debug_type);
debug_type debug_make_method_type(void *, debug_type, debug_type, debug_type *, bool);
debug_type debug_make_const_type(void *, debug_type);
debug_type debug_make_volatile_type(void *, debug_type);
debug_type debug_make_enum_type(void *, const char **, bfd_signed_vma *);
debug_field debug_make_field(void *, const char *, debug_type, bfd_vma, bfd_vma, enum debug_visibility);
debug_field debug_make_static_member(void *, const char *, debug_type, const char *, enum debug_visibility);
debug_baseclass debug_make_baseclass(void *, debug_type, bfd_vma, bool, enum debug_visibility);
debug_method debug_make_method(void *, const char *, debug_method_variant *);
debug_method_variant debug_make_method_variant(void *, const char *, debug_type, enum debug_visibility, bool, bool, bfd_vma, debug_type);
debug_method_variant debug_make_static_method_variant(void *, const char *, debug_type, enum debug_visibility, bool, bool);
debug_type debug_tag_type(void *, const char *, debug_type);
debug_type debug_make_undefined_tagged_type(void *, const char *, enum debug_type_kind);
bool debug_record_type_size(void *, debug_type, unsigned int);
debug_type debug_find_tagged_type(void *, const char *, enum debug_type_kind);
debug_type debug_find_named_type(void *, const char *);
enum debug_type_kind debug_get_type_kind(void *, debug_type);
const char *debug_get_type_name(void *, debug_type);
bfd_vma debug_get_type_size(void *, debug_type);
debug_type debug_get_return_type(void *, debug_type);
const debug_type *debug_get_parameter_types(void *, debug_type, bool *);
debug_type debug_get_target_type(void *, debug_type);
const debug_field *debug_get_fields(void *, debug_type);
debug_type debug_get_field_type(void *, debug_field);
const char *debug_get_field_name(void *, debug_field);
bfd_vma debug_get_field_bitpos(void *, debug_field);
bfd_vma debug_get_field_bitsize(void *, debug_field);
enum debug_visibility debug_get_field_visibility(void *, debug_field);
const char *debug_get_field_physname(void *, debug_field);
bool debug_write(void *, const struct debug_write_fns *, void *);
bool debug_record_variable(void *, const char *, debug_type, enum debug_var_kind, bfd_vma);
bool debug_record_function(void *, const char *, debug_type, bool, bfd_vma);
bool debug_record_parameter(void *, const char *, debug_type, enum debug_parm_kind, bfd_vma);
bool debug_record_label(void *, const char *, debug_type, bfd_vma);
bool debug_record_int_const(void *, const char *, bfd_vma);
bool debug_record_float_const(void *, const char *, double);
bool debug_record_typed_const(void *, const char *, debug_type, bfd_vma);
debug_type debug_name_type(void *, const char *, debug_type);
void *debug_init(bfd *);

void *start_stab(void *, bfd *, bool, asymbol **, long);
bool finish_stab(void *, void *, bool);
bool parse_stab(void *, void *, int, int, bfd_vma, const char *);

static void save_stab(int, int, bfd_vma, const char *);
static void stab_context(void);
static void free_saved_stabs(void);
static char *savestring(void *, const char *, size_t);
static bfd_vma parse_number(const char **, bool *, const char *);
static void bad_stab(const char *);
static void warn_stab(const char *, const char *);
static bool parse_stab_type_number(const char **, int *, const char *);
static debug_type stab_find_type(void *, struct stab_handle *, const int *);
static debug_type *stab_find_slot(void *, struct stab_handle *, const int *);
static bool stab_record_type(void *, struct stab_handle *, const int *, debug_type);
static debug_type stab_xcoff_builtin_type(void *, struct stab_handle *, unsigned int);
static debug_type stab_find_tagged_type(void *, struct stab_handle *, const char *, int, enum debug_type_kind);
static bool stab_emit_pending_vars(void *, struct stab_handle *);
static void push_bincl(void *, struct stab_handle *, const char *, bfd_vma);
static const char *pop_bincl(struct stab_handle *);
static bool find_excl(struct stab_handle *, const char *, bfd_vma);
static debug_type parse_stab_type(void *, struct stab_handle *, const char *, const char **, debug_type **, const char *);
static debug_type parse_stab_range_type(void *, struct stab_handle *, const char *, const char **, const int *, const char *);
static debug_type parse_stab_sun_builtin_type(void *, const char **, const char *);
static debug_type parse_stab_sun_floating_type(void *, const char **, const char *);
static debug_type parse_stab_enum_type(void *, const char **, const char *);
static debug_type parse_stab_struct_type(void *, struct stab_handle *, const char *, const char **, bool, const int *, const char *);
static bool parse_stab_baseclasses(void *, struct stab_handle *, const char **, debug_baseclass **, const char *);
static bool parse_stab_struct_fields(void *, struct stab_handle *, const char **, debug_field **, bool *, const char *);
static bool parse_stab_cpp_abbrev(void *, struct stab_handle *, const char **, debug_field *, const char *);
static bool parse_stab_one_struct_field(void *, struct stab_handle *, const char **, const char *, debug_field *, bool *, const char *);
static bool parse_stab_members(void *, struct stab_handle *, const char *, const char **, const int *, debug_method **, const char *);
static debug_type parse_stab_argtypes(void *, struct stab_handle *, debug_type, const char *, const char *, debug_type, const char *, bool, bool, const char **);
static bool parse_stab_tilde_field(void *, struct stab_handle *, const char **, const int *, debug_type *, bool *, const char *);
static debug_type parse_stab_array_type(void *, struct stab_handle *, const char **, bool, const char *);
static bool parse_stab_string(void *, struct stab_handle *, int, int, bfd_vma, const char *, const char *);

void *xmalloc(size_t);
void *xrealloc(void *, size_t);
char *xstrdup(const char *);
char *concat(const char *, ...);
static bool startswith(const char *, const char *);
static int filename_cmp(const char *, const char *);
static bool might_need_separate_debug_info(bool);
static void load_separate_debug_files(bfd *, const char *);
static void dump_bfd(bfd *, bool);
static void free_debug_memory(void);
static void dump_headers(bfd *);
static asymbol **slurp_symtab(bfd *);
static asymbol **slurp_dynamic_symtab(bfd *);
static void dump_symbols(bfd *, bool);
static void dump_relocs(bfd *);
static void dump_dynamic_relocs(bfd *);
static void dump_data(bfd *);
static void disassemble_data(bfd *);
static void dump_dwarf(bfd *, bool);
static void dump_ctf(bfd *, const char *, const char *, const char *);
static void dump_sframe_section(bfd *, const char *, bool);
static void dump_stabs(bfd *);
static void print_arelt_descr(FILE *, bfd *, bool, bool);
static void dump_bfd_header(bfd *);
static void dump_bfd_private_header(bfd *);
static void dump_target_specific(bfd *);
static void adjust_addresses(bfd *, asection *, void *);
static void bfd_map_over_sections(bfd *, void (*)(bfd *, asection *, void *), void *);
static const struct elf_backend_data *get_elf_backend_data(bfd *);
static uint64_t sign_extend_address(bfd *, uint64_t, int);
static char *sanitize_string(const char *);
static void dwarf_select_sections_all(void);
static char *bfd_demangle(struct bfd *, const char *, int);
static void non_fatal(const char *, ...);
static const char *byte_get_big_endian(const unsigned char *, int);
static const char *byte_get_little_endian(const unsigned char *, int);
static bool debug_write_class_type(struct debug_handle *, const struct debug_write_fns *, void *, struct debug_type_s *, const char *);
static bool debug_write_function(struct debug_handle *, const struct debug_write_fns *, void *, const char *, enum debug_object_linkage, struct debug_function *);
static bool debug_write_linenos(struct debug_handle *, const struct debug_write_fns *, void *, bfd_vma);
static bool debug_write_block(struct debug_handle *, const struct debug_write_fns *, void *, struct debug_block *);
static bool debug_write_name(struct debug_handle *, const struct debug_write_fns *, void *, struct debug_name *);
static bool debug_write_type(struct debug_handle *, const struct debug_write_fns *, void *, struct debug_type_s *, struct debug_name *);
static bool debug_set_class_id(struct debug_handle *, const char *, struct debug_type_s *);
static bool debug_type_samep(struct debug_handle *, struct debug_type_s *, struct debug_type_s *);
static bool debug_class_type_samep(struct debug_handle *, struct debug_type_s *, struct debug_type_s *);
static struct debug_type_s *debug_get_real_type(void *, debug_type, struct debug_type_real_list *);
bool bfd_big_endian(bfd *);
bool bfd_little_endian(bfd *);
unsigned int bfd_get_32(bfd *, const bfd_byte *);
unsigned int bfd_get_8(bfd *, const bfd_byte *);
unsigned int bfd_get_16(bfd *, const bfd_byte *);
asection *bfd_get_section_by_name(bfd *, const char *);
bool bfd_malloc_and_get_section(bfd *, asection *, bfd_byte **);
const char *bfd_errmsg(int);
int bfd_get_error(void);
bool bfd_check_format(bfd *, int);
bool bfd_get_section_contents(bfd *, asection *, void *, file_ptr, bfd_size_type);
uint64_t bfd_scan_vma(const char *, const char **, int);
void *bfd_make_debug_symbol(bfd *, void *, unsigned long);
bool core_file_matches_executable_p(bfd *, bfd *);
bool bfd_core_file_failing_command(bfd *);
bool bfd_core_file_failing_signal(bfd *);
bool bfd_core_file_pid(bfd *);
int bfd_get_flavour(bfd *);
long bfd_get_dynamic_symtab_upper_bound(bfd *);
long bfd_get_synthetic_symtab(bfd *, long, asymbol **, long, asymbol **, asymbol **);
void *read_debugging_info(bfd *, asymbol **, long, bool);
#define bfd_target_elf_flavour 2
#define HAS_RELOC 0x01

/* === Stub implementations === */
void *xmalloc(size_t s) { return malloc(s); }
void *xrealloc(void *p, size_t s) { return realloc(p, s); }
char *xstrdup(const char *s) { size_t l = strlen(s)+1; char *r = malloc(l); memcpy(r, s, l); return r; }
char *concat(const char *s, ...) { va_list ap; va_start(ap, s); const char *p; size_t len = strlen(s)+1; for(p=va_arg(ap,const char*);p;p=va_arg(ap,const char*)) len+=strlen(p); va_end(ap); char *r=malloc(len); va_start(ap,s); strcpy(r,s); for(p=va_arg(ap,const char*);p;p=va_arg(ap,const char*)) strcat(r,p); va_end(ap); return r; }
static bool startswith(const char *s, const char *p) { return strncmp(s, p, strlen(p)) == 0; }
static int filename_cmp(const char *a, const char *b) { return strcmp(a, b); }
static bool might_need_separate_debug_info(bool is_mainfile) { return false; }
static void load_separate_debug_files(bfd *abfd, const char *filename) {}
static void free_debug_memory(void) {}
static void dump_headers(bfd *abfd) {}
static asymbol **slurp_symtab(bfd *abfd) { return NULL; }
static asymbol **slurp_dynamic_symtab(bfd *abfd) { return NULL; }
static void dump_symbols(bfd *abfd, bool dynamic) {}
static void dump_relocs(bfd *abfd) {}
static void dump_dynamic_relocs(bfd *abfd) {}
static void dump_data(bfd *abfd) {}
static void disassemble_data(bfd *abfd) {}
static void dump_dwarf(bfd *abfd, bool is_mainfile) {}
static void dump_ctf(bfd *abfd, const char *a, const char *b, const char *c) {}
static void dump_sframe_section(bfd *abfd, const char *a, bool b) {}
static void dump_stabs(bfd *abfd) {}
static void print_arelt_descr(FILE *f, bfd *abfd, bool v, bool r) {}
static void dump_bfd_header(bfd *abfd) {}
static void dump_bfd_private_header(bfd *abfd) {}
static void dump_target_specific(bfd *abfd) {}
static void adjust_addresses(bfd *abfd, asection *section, void *arg) {}
static void bfd_map_over_sections(bfd *abfd, void (*func)(bfd *, asection *, void *), void *arg) {}
static const struct elf_backend_data *get_elf_backend_data(bfd *abfd) { return NULL; }
static uint64_t sign_extend_address(bfd *abfd, uint64_t addr, int arch_size) { return addr; }
static char *sanitize_string(const char *s) { return (char *)s; }
static void dwarf_select_sections_all(void) {}
static char *bfd_demangle(struct bfd *abfd, const char *name, int options) { return NULL; }
static void non_fatal(const char *fmt, ...) { va_list ap; va_start(ap, fmt); vfprintf(stderr, fmt, ap); va_end(ap); }
static const char *byte_get_big_endian(const unsigned char *p, int n) { return NULL; }
static const char *byte_get_little_endian(const unsigned char *p, int n) { return NULL; }
asection *bfd_get_section_by_name(bfd *abfd, const char *name) { return NULL; }
bool bfd_malloc_and_get_section(bfd *abfd, asection *sec, bfd_byte **buf) { return false; }
const char *bfd_errmsg(int err) { return ""; }
int bfd_get_error(void) { return 0; }
bool bfd_check_format(bfd *abfd, int format) { return true; }
bool bfd_get_section_contents(bfd *abfd, asection *sec, void *loc, file_ptr offset, bfd_size_type count) { return false; }
uint64_t bfd_scan_vma(const char *string, const char **end, int base) { return 0; }
void *bfd_make_debug_symbol(bfd *abfd, void *ptr, unsigned long size) { return NULL; }
bool core_file_matches_executable_p(bfd *core_bfd, bfd *exec_bfd) { return false; }
bool bfd_core_file_failing_command(bfd *abfd) { return false; }
bool bfd_core_file_failing_signal(bfd *abfd) { return false; }
bool bfd_core_file_pid(bfd *abfd) { return false; }
int bfd_get_flavour(bfd *abfd) { return 0; }
long bfd_get_dynamic_symtab_upper_bound(bfd *abfd) { return 0; }
long bfd_get_synthetic_symtab(bfd *abfd, long symcount, asymbol **syms, long dynsymcount, asymbol **dynsyms, asymbol **synthsyms) { return 0; }
void *read_debugging_info(bfd *abfd, asymbol **syms, long symcount, bool do_follow_links) { return NULL; }
bool bfd_big_endian(bfd *abfd) { return false; }
bool bfd_little_endian(bfd *abfd) { return true; }
unsigned int bfd_get_32(bfd *abfd, const bfd_byte *p) { return (p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3]; }
unsigned int bfd_get_8(bfd *abfd, const bfd_byte *p) { return p[0]; }
unsigned int bfd_get_16(bfd *abfd, const bfd_byte *p) { return (p[0]<<8)|p[1]; }
static void debug_error(const char *message) { fprintf(stderr, "%s\n", message); }
static struct debug_name *debug_add_to_namespace(struct debug_handle *info, struct debug_namespace **nsp, const char *name, enum debug_object_kind kind, enum debug_object_linkage linkage) {
  struct debug_name *n; struct debug_namespace *ns;
  n = debug_xzalloc(info, sizeof(*n)); n->name = name; n->kind = kind; n->linkage = linkage;
  ns = *nsp; if (ns == NULL) { ns = debug_xzalloc(info, sizeof(*ns)); ns->tail = &ns->list; *nsp = ns; }
  *ns->tail = n; ns->tail = &n->next; return n;
}


static struct debug_type_s *debug_make_type(struct debug_handle *info,
                                            enum debug_type_kind kind,
                                            unsigned int size) {
  struct debug_type_s *t;

  t = debug_xzalloc(info, sizeof(*t));

  t->kind = kind;
  t->size = size;

  return t;
}

debug_type
debug_tag_type (void *handle, const char *name, debug_type type)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type_s *t;
  struct debug_named_type *n;
  struct debug_name *nm;

  if (name == NULL || type == NULL)
    return DEBUG_TYPE_NULL;

  if (info->current_file == NULL)
    {
      debug_error (_("debug_tag_type: no current file"));
      return DEBUG_TYPE_NULL;
    }

  if (type->kind == DEBUG_KIND_TAGGED)
    {
      if (strcmp (type->u.knamed->name->name, name) == 0)
	return type;
      debug_error (_("debug_tag_type: extra tag attempted"));
      return DEBUG_TYPE_NULL;
    }

  t = debug_make_type (info, DEBUG_KIND_TAGGED, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  n = debug_xzalloc (info, sizeof (*n));

  n->type = type;

  t->u.knamed = n;

  /* We keep a global namespace of tags for each compilation unit.  I
     don't know if that is the right thing to do.  */

  nm = debug_add_to_namespace (info, &info->current_file->globals, name,
			       DEBUG_OBJECT_TAG, DEBUG_LINKAGE_NONE);
  if (nm == NULL)
    return DEBUG_TYPE_NULL;

  nm->u.tag = t;

  n->name = nm;

  return t;
}

debug_type debug_make_undefined_tagged_type(void *handle, const char *name,
                                            enum debug_type_kind kind) {
  struct debug_handle *info = (struct debug_handle *)handle;
  struct debug_type_s *t;

  if (name == NULL)
    return DEBUG_TYPE_NULL;

  switch (kind) {
  case DEBUG_KIND_STRUCT:
  case DEBUG_KIND_UNION:
  case DEBUG_KIND_CLASS:
  case DEBUG_KIND_UNION_CLASS:
  case DEBUG_KIND_ENUM:
    break;

  default:
    debug_error(_("debug_make_undefined_type: unsupported kind"));
    return DEBUG_TYPE_NULL;
  }

  t = debug_make_type(info, kind, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  return debug_tag_type(handle, name, t);
}

bool finish_stab(void *dhandle, void *handle, bool emit) {
  struct stab_handle *info = (struct stab_handle *)handle;
  struct stab_tag *st;
  bool ret = true;

  if (emit && info->within_function) {
    if (!stab_emit_pending_vars(dhandle, info) ||
        !debug_end_function(dhandle, info->function_end))
      ret = false;
  }

  if (emit && ret)
    for (st = info->tags; st != NULL; st = st->next) {
      enum debug_type_kind kind;

      kind = st->kind;
      if (kind == DEBUG_KIND_ILLEGAL)
        kind = DEBUG_KIND_STRUCT;
      st->slot = debug_make_undefined_tagged_type(dhandle, st->name, kind);
      if (st->slot == DEBUG_TYPE_NULL) {
        ret = false;
        break;
      }
    }

  free(info->file_types);
  free(info->so_string);
  free(info);
  return ret;
}


static debug_type stab_find_tagged_type(void *dhandle, struct stab_handle *info,
                                        const char *p, int len,
                                        enum debug_type_kind kind) {
  char *name;
  debug_type dtype;
  struct stab_tag *st;

  name = savestring(dhandle, p, len);

  /* We pass DEBUG_KIND_ILLEGAL because we want all tags in the same
     namespace.  This is right for C, and I don't know how to handle
     other languages.  FIXME.  */
  dtype = debug_find_tagged_type(dhandle, name, DEBUG_KIND_ILLEGAL);
  if (dtype != DEBUG_TYPE_NULL)
    return dtype;

  /* We need to allocate an entry on the undefined tag list.  */
  for (st = info->tags; st != NULL; st = st->next) {
    if (st->name[0] == name[0] && strcmp(st->name, name) == 0) {
      if (st->kind == DEBUG_KIND_ILLEGAL)
        st->kind = kind;
      break;
    }
  }
  if (st == NULL) {
    st = debug_xzalloc(dhandle, sizeof(*st));

    st->next = info->tags;
    st->name = name;
    st->kind = kind;
    st->slot = DEBUG_TYPE_NULL;
    st->type = debug_make_indirect_type(dhandle, &st->slot, name);
    info->tags = st;
  }

  return st->type;
}

static debug_type parse_stab_type(void *dhandle, struct stab_handle *info,
                                  const char *type_name, const char **pp,
                                  debug_type **slotp, const char *p_end) {
  const char *orig;
  int typenums[2];
  int size;
  bool stringp;
  int descriptor;
  debug_type dtype;

  if (slotp != NULL)
    *slotp = NULL;

  orig = *pp;
  if (orig >= p_end)
    return DEBUG_TYPE_NULL;

  size = -1;
  stringp = false;

  info->self_crossref = false;

  /* Read type number if present.  The type number may be omitted.
     for instance in a two-dimensional array declared with type
     "ar1;1;10;ar1;1;10;4".  */
  if (!ISDIGIT(**pp) && **pp != '(' && **pp != '-') {
    /* 'typenums=' not present, type is anonymous.  Read and return
       the definition, but don't put it in the type vector.  */
    typenums[0] = typenums[1] = -1;
  } else {
    if (!parse_stab_type_number(pp, typenums, p_end))
      return DEBUG_TYPE_NULL;

    if (**pp != '=')
      /* Type is not being defined here.  Either it already
         exists, or this is a forward reference to it.  */
      return stab_find_type(dhandle, info, typenums);

    /* Only set the slot if the type is being defined.  This means
       that the mapping from type numbers to types will only record
       the name of the typedef which defines a type.  If we don't do
       this, then something like
           typedef int foo;
           int i;
       will record that i is of type foo.  Unfortunately, stabs
       information is ambiguous about variable types.  For this code,
           typedef int foo;
           int i;
           foo j;
       the stabs information records both i and j as having the same
       type.  This could be fixed by patching the compiler.  */
    if (slotp != NULL && typenums[0] >= 0 && typenums[1] >= 0)
      *slotp = stab_find_slot(dhandle, info, typenums);

    /* Type is being defined here.  */
    /* Skip the '='.  */
    ++*pp;

    while (**pp == '@') {
      const char *p = *pp + 1;
      const char *attr;

      if (ISDIGIT(*p) || *p == '(' || *p == '-')
        /* Member type.  */
        break;

      /* Type attributes.  */
      attr = p;

      for (; *p != ';'; ++p) {
        if (*p == '\0') {
          bad_stab(orig);
          return DEBUG_TYPE_NULL;
        }
      }
      *pp = p + 1;

      switch (*attr) {
      case 's':
        size = atoi(attr + 1);
        size /= 8; /* Size is in bits.  We store it in bytes.  */
        if (size <= 0)
          size = -1;
        break;

      case 'S':
        stringp = true;
        break;

      case 0:
        bad_stab(orig);
        return DEBUG_TYPE_NULL;

      default:
        /* Ignore unrecognized type attributes, so future
           compilers can invent new ones.  */
        break;
      }
    }
  }

  descriptor = **pp;
  ++*pp;

  switch (descriptor) {
  case 'x': {
    enum debug_type_kind code;
    const char *q1, *q2, *p;

    /* A cross reference to another type.  */
    switch (**pp) {
    case 's':
      code = DEBUG_KIND_STRUCT;
      break;
    case 'u':
      code = DEBUG_KIND_UNION;
      break;
    case 'e':
      code = DEBUG_KIND_ENUM;
      break;
    case 0:
      bad_stab(orig);
      return DEBUG_TYPE_NULL;

    default:
      /* Complain and keep going, so compilers can invent new
         cross-reference types.  */
      warn_stab(orig, _("unrecognized cross reference type"));
      code = DEBUG_KIND_STRUCT;
      break;
    }
    ++*pp;

    q1 = strchr(*pp, '<');
    p = strchr(*pp, ':');
    if (p == NULL) {
      bad_stab(orig);
      return DEBUG_TYPE_NULL;
    }
    if (q1 != NULL && p > q1 && p[1] == ':') {
      int nest = 0;

      for (q2 = q1; *q2 != '\0'; ++q2) {
        if (*q2 == '<')
          ++nest;
        else if (*q2 == '>')
          --nest;
        else if (*q2 == ':' && nest == 0)
          break;
      }
      p = q2;
      if (*p != ':') {
        bad_stab(orig);
        return DEBUG_TYPE_NULL;
      }
    }

    /* Some versions of g++ can emit stabs like
           fleep:T20=xsfleep:
       which define structures in terms of themselves.  We need to
       tell the caller to avoid building a circular structure.  */
    if (type_name != NULL && strncmp(type_name, *pp, p - *pp) == 0 &&
        type_name[p - *pp] == '\0')
      info->self_crossref = true;

    dtype = stab_find_tagged_type(dhandle, info, *pp, p - *pp, code);

    *pp = p + 1;
  } break;

  case '-':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '(': {
    const char *hold;
    int xtypenums[2];

    /* This type is defined as another type.  */
    (*pp)--;
    hold = *pp;

    /* Peek ahead at the number to detect void.  */
    if (!parse_stab_type_number(pp, xtypenums, p_end))
      return DEBUG_TYPE_NULL;

    if (typenums[0] == xtypenums[0] && typenums[1] == xtypenums[1]) {
      /* This type is being defined as itself, which means that
         it is void.  */
      dtype = debug_make_void_type(dhandle);
    } else {
      *pp = hold;

      /* Go back to the number and have parse_stab_type get it.
         This means that we can deal with something like
         t(1,2)=(3,4)=... which the Lucid compiler uses.  */
      dtype = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                              (debug_type **)NULL, p_end);
      if (dtype == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;
    }

    if (typenums[0] != -1) {
      if (!stab_record_type(dhandle, info, typenums, dtype))
        return DEBUG_TYPE_NULL;
    }

    break;
  }

  case '*':
    dtype = debug_make_pointer_type(
        dhandle, parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                 (debug_type **)NULL, p_end));
    break;

  case '&':
    /* Reference to another type.  */
    dtype = (debug_make_reference_type(
        dhandle, parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                 (debug_type **)NULL, p_end)));
    break;

  case 'f':
    /* Function returning another type.  */
    /* FIXME: gdb checks os9k_stabs here.  */
    dtype = (debug_make_function_type(
        dhandle,
        parse_stab_type(dhandle, info, (const char *)NULL, pp,
                        (debug_type **)NULL, p_end),
        (debug_type *)NULL, false));
    break;

  case 'k':
    /* Const qualifier on some type (Sun).  */
    /* FIXME: gdb accepts 'c' here if os9k_stabs.  */
    dtype = debug_make_const_type(
        dhandle, parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                 (debug_type **)NULL, p_end));
    break;

  case 'B':
    /* Volatile qual on some type (Sun).  */
    /* FIXME: gdb accepts 'i' here if os9k_stabs.  */
    dtype = (debug_make_volatile_type(
        dhandle, parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                 (debug_type **)NULL, p_end)));
    break;

  case '@':
    /* Offset (class & variable) type.  This is used for a pointer
       relative to an object.  */
    {
      debug_type domain;
      debug_type memtype;

      /* Member type.  */

      domain = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                               (debug_type **)NULL, p_end);
      if (domain == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;

      if (**pp != ',') {
        bad_stab(orig);
        return DEBUG_TYPE_NULL;
      }
      ++*pp;

      memtype = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                (debug_type **)NULL, p_end);
      if (memtype == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;

      dtype = debug_make_offset_type(dhandle, domain, memtype);
    }
    break;

  case '#':
    /* Method (class & fn) type.  */
    if (**pp == '#') {
      debug_type return_type;

      ++*pp;
      return_type = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                    (debug_type **)NULL, p_end);
      if (return_type == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;
      if (**pp != ';') {
        bad_stab(orig);
        return DEBUG_TYPE_NULL;
      }
      ++*pp;
      dtype = debug_make_method_type(dhandle, return_type, DEBUG_TYPE_NULL,
                                     (debug_type *)NULL, false);
    } else {
      debug_type domain;
      debug_type return_type;
      debug_type *args, *xargs;
      unsigned int n;
      unsigned int alloc;
      bool varargs;

      domain = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                               (debug_type **)NULL, p_end);
      if (domain == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;

      if (**pp != ',') {
        bad_stab(orig);
        return DEBUG_TYPE_NULL;
      }
      ++*pp;

      return_type = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                    (debug_type **)NULL, p_end);
      if (return_type == DEBUG_TYPE_NULL)
        return DEBUG_TYPE_NULL;

      alloc = 10;
      args = xmalloc(alloc * sizeof(*args));
      n = 0;
      while (**pp != ';') {
        if (**pp != ',') {
          bad_stab(orig);
          free(args);
          return DEBUG_TYPE_NULL;
        }
        ++*pp;

        if (n + 1 >= alloc) {
          alloc += 10;
          args = xrealloc(args, alloc * sizeof(*args));
        }

        args[n] = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                                  (debug_type **)NULL, p_end);
        if (args[n] == DEBUG_TYPE_NULL) {
          free(args);
          return DEBUG_TYPE_NULL;
        }
        ++n;
      }
      ++*pp;

      /* If the last type is not void, then this function takes a
         variable number of arguments.  Otherwise, we must strip
         the void type.  */
      if (n == 0 ||
          debug_get_type_kind(dhandle, args[n - 1]) != DEBUG_KIND_VOID)
        varargs = true;
      else {
        --n;
        varargs = false;
      }

      args[n] = DEBUG_TYPE_NULL;
      xargs = debug_xalloc(dhandle, (n + 1) * sizeof(*args));
      memcpy(xargs, args, (n + 1) * sizeof(*args));
      free(args);

      dtype =
          debug_make_method_type(dhandle, return_type, domain, xargs, varargs);
    }
    break;

  case 'r':
    /* Range type.  */
    dtype =
        parse_stab_range_type(dhandle, info, type_name, pp, typenums, p_end);
    break;

  case 'b':
    /* FIXME: gdb checks os9k_stabs here.  */
    /* Sun ACC builtin int type.  */
    dtype = parse_stab_sun_builtin_type(dhandle, pp, p_end);
    break;

  case 'R':
    /* Sun ACC builtin float type.  */
    dtype = parse_stab_sun_floating_type(dhandle, pp, p_end);
    break;

  case 'e':
    /* Enumeration type.  */
    dtype = parse_stab_enum_type(dhandle, pp, p_end);
    break;

  case 's':
  case 'u':
    /* Struct or union type.  */
    dtype = parse_stab_struct_type(dhandle, info, type_name, pp,
                                   descriptor == 's', typenums, p_end);
    break;

  case 'a':
    /* Array type.  */
    if (**pp != 'r') {
      bad_stab(orig);
      return DEBUG_TYPE_NULL;
    }
    ++*pp;

    dtype = parse_stab_array_type(dhandle, info, pp, stringp, p_end);
    break;

  case 'S':
    dtype =
        debug_make_set_type(dhandle,
                            parse_stab_type(dhandle, info, (const char *)NULL,
                                            pp, (debug_type **)NULL, p_end),
                            stringp);
    break;

  default:
    bad_stab(orig);
    return DEBUG_TYPE_NULL;
  }

  if (dtype == DEBUG_TYPE_NULL)
    return DEBUG_TYPE_NULL;

  if (typenums[0] != -1) {
    if (!stab_record_type(dhandle, info, typenums, dtype))
      return DEBUG_TYPE_NULL;
  }

  if (size != -1) {
    if (!debug_record_type_size(dhandle, dtype, (unsigned int)size))
      return DEBUG_TYPE_NULL;
  }

  return dtype;
}

static bool parse_stab_one_struct_field(void *dhandle, struct stab_handle *info,
                                        const char **pp, const char *p,
                                        debug_field *retp, bool *staticsp,
                                        const char *p_end) {
  const char *orig;
  char *name;
  enum debug_visibility visibility;
  debug_type type;
  bfd_vma bitpos;
  bfd_vma bitsize;

  orig = *pp;
  if (orig >= p_end)
    return false;

  /* FIXME: gdb checks ARM_DEMANGLING here.  */

  name = savestring(dhandle, *pp, p - *pp);

  *pp = p + 1;

  if (**pp != '/')
    visibility = DEBUG_VISIBILITY_PUBLIC;
  else {
    ++*pp;
    switch (**pp) {
    case '0':
      visibility = DEBUG_VISIBILITY_PRIVATE;
      break;
    case '1':
      visibility = DEBUG_VISIBILITY_PROTECTED;
      break;
    case '2':
      visibility = DEBUG_VISIBILITY_PUBLIC;
      break;
    case 0:
      bad_stab(orig);
      return false;
    default:
      warn_stab(orig, _("unknown visibility character for field"));
      visibility = DEBUG_VISIBILITY_PUBLIC;
      break;
    }
    ++*pp;
  }

  type = parse_stab_type(dhandle, info, (const char *)NULL, pp,
                         (debug_type **)NULL, p_end);
  if (type == DEBUG_TYPE_NULL)
    return false;

  if (**pp == ':') {
    char *varname;

    /* This is a static class member.  */
    ++*pp;
    p = strchr(*pp, ';');
    if (p == NULL) {
      bad_stab(orig);
      return false;
    }

    varname = savestring(dhandle, *pp, p - *pp);

    *pp = p + 1;

    *retp = debug_make_static_member(dhandle, name, type, varname, visibility);
    *staticsp = true;

    return true;
  }

  if (**pp != ',') {
    bad_stab(orig);
    return false;
  }
  ++*pp;

  bitpos = parse_number(pp, (bool *)NULL, p_end);
  if (**pp != ',') {
    bad_stab(orig);
    return false;
  }
  ++*pp;

  bitsize = parse_number(pp, (bool *)NULL, p_end);
  if (**pp != ';') {
    bad_stab(orig);
    return false;
  }
  ++*pp;

  if (bitpos == 0 && bitsize == 0) {
    /* This can happen in two cases: (1) at least for gcc 2.4.5 or
       so, it is a field which has been optimized out.  The correct
       stab for this case is to use VISIBILITY_IGNORE, but that is a
       recent invention.  (2) It is a 0-size array.  For example
       union { int num; char str[0]; } foo.  Printing "<no value>"
       for str in "p foo" is OK, since foo.str (and thus foo.str[3])
       will continue to work, and a 0-size array as a whole doesn't
       have any contents to print.

       I suspect this probably could also happen with gcc -gstabs
       (not -gstabs+) for static fields, and perhaps other C++
       extensions.  Hopefully few people use -gstabs with gdb, since
       it is intended for dbx compatibility.  */
    visibility = DEBUG_VISIBILITY_IGNORE;
  }

  /* FIXME: gdb does some stuff here to mark fields as unpacked.  */

  *retp = debug_make_field(dhandle, name, type, bitpos, bitsize, visibility);

  return true;
}

static bool parse_stab_struct_fields(void *dhandle, struct stab_handle *info,
                                     const char **pp, debug_field **retp,
                                     bool *staticsp, const char *p_end) {
  const char *orig;
  const char *p;
  debug_field *fields, *xfields;
  unsigned int c;
  unsigned int alloc;

  *retp = NULL;
  *staticsp = false;

  orig = *pp;
  if (orig >= p_end)
    return false;

  c = 0;
  alloc = 10;
  fields = xmalloc(alloc * sizeof(*fields));
  while (**pp != ';') {
    /* FIXME: gdb checks os9k_stabs here.  */

    p = *pp;

    /* Add 1 to c to leave room for NULL pointer at end.  */
    if (c + 1 >= alloc) {
      alloc += 10;
      fields = xrealloc(fields, alloc * sizeof(*fields));
    }

    /* If it starts with CPLUS_MARKER it is a special abbreviation,
       unless the CPLUS_MARKER is followed by an underscore, in
       which case it is just the name of an anonymous type, which we
       should handle like any other type name.  We accept either '$'
       or '.', because a field name can never contain one of these
       characters except as a CPLUS_MARKER.  */

    if ((*p == '$' || *p == '.') && p[1] != '_') {
      ++*pp;
      if (!parse_stab_cpp_abbrev(dhandle, info, pp, fields + c, p_end)) {
        free(fields);
        return false;
      }
      ++c;
      continue;
    }

    /* Look for the ':' that separates the field name from the field
       values.  Data members are delimited by a single ':', while member
       functions are delimited by a pair of ':'s.  When we hit the member
       functions (if any), terminate scan loop and return.  */

    p = strchr(p, ':');
    if (p == NULL) {
      bad_stab(orig);
      free(fields);
      return false;
    }

    if (p[1] == ':')
      break;

    if (!parse_stab_one_struct_field(dhandle, info, pp, p, fields + c, staticsp,
                                     p_end)) {
      free(fields);
      return false;
    }

    ++c;
  }

  fields[c] = DEBUG_FIELD_NULL;
  xfields = debug_xalloc(dhandle, (c + 1) * sizeof(*fields));
  memcpy(xfields, fields, (c + 1) * sizeof(*fields));
  free(fields);

  *retp = xfields;

  return true;
}

static debug_type parse_stab_struct_type(void *dhandle,
                                         struct stab_handle *info,
                                         const char *tagname, const char **pp,
                                         bool structp, const int *typenums,
                                         const char *p_end) {
  bfd_vma size;
  debug_baseclass *baseclasses;
  debug_field *fields = NULL;
  bool statics;
  debug_method *methods;
  debug_type vptrbase;
  bool ownvptr;

  /* Get the size.  */
  size = parse_number(pp, (bool *)NULL, p_end);

  /* Get the other information.  */
  if (!parse_stab_baseclasses(dhandle, info, pp, &baseclasses, p_end) ||
      !parse_stab_struct_fields(dhandle, info, pp, &fields, &statics, p_end) ||
      !parse_stab_members(dhandle, info, tagname, pp, typenums, &methods,
                          p_end) ||
      !parse_stab_tilde_field(dhandle, info, pp, typenums, &vptrbase, &ownvptr,
                              p_end))
    return DEBUG_TYPE_NULL;

  if (!statics && baseclasses == NULL && methods == NULL &&
      vptrbase == DEBUG_TYPE_NULL && !ownvptr)
    return debug_make_struct_type(dhandle, structp, size, fields);

  return debug_make_object_type(dhandle, structp, size, fields, baseclasses,
                                methods, vptrbase, ownvptr);
}

bool parse_stab(void *dhandle, void *handle, int type, int desc, bfd_vma value,
                const char *string) {
  const char *string_end;
  struct stab_handle *info = (struct stab_handle *)handle;
  char *copy;
  size_t len;

  /* gcc will emit two N_SO strings per compilation unit, one for the
     directory name and one for the file name.  We just collect N_SO
     strings as we see them, and start the new compilation unit when
     we see a non N_SO symbol.  */
  if (info->so_string != NULL &&
      (type != N_SO || *string == '\0' || value != info->so_value)) {
    len = strlen(info->so_string) + 1;
    copy = debug_xalloc(dhandle, len);
    memcpy(copy, info->so_string, len);
    if (!debug_set_filename(dhandle, copy))
      return false;
    info->main_filename = copy;

    free(info->so_string);
    info->so_string = NULL;

    info->gcc_compiled = 0;
    info->n_opt_found = false;

    /* Generally, for stabs in the symbol table, the N_LBRAC and
       N_RBRAC symbols are relative to the N_SO symbol value.  */
    if (!info->sections)
      info->file_start_offset = info->so_value;

    /* We need to reset the mapping from type numbers to types.  We
       can only free the file_types array, not the stab_types
       list entries due to the use of debug_make_indirect_type.  */
    info->files = 1;
    info->file_types = xrealloc(info->file_types, sizeof(*info->file_types));
    info->file_types[0] = NULL;

    /* Now process whatever type we just got.  */
  }

  string_end = string + strlen(string);

  switch (type) {
  case N_FN:
  case N_FN_SEQ:
    break;

  case N_LBRAC:
    /* Ignore extra outermost context from SunPRO cc and acc.  */
    if (info->n_opt_found && desc == 1)
      break;

    if (!info->within_function) {
      fprintf(stderr, _("N_LBRAC not within function\n"));
      return false;
    }

    /* Start an inner lexical block.  */
    if (!debug_start_block(dhandle, (value + info->file_start_offset +
                                     info->function_start_offset)))
      return false;

    /* Emit any pending variable definitions.  */
    if (!stab_emit_pending_vars(dhandle, info))
      return false;

    ++info->block_depth;
    break;

  case N_RBRAC:
    /* Ignore extra outermost context from SunPRO cc and acc.  */
    if (info->n_opt_found && desc == 1)
      break;

    /* We shouldn't have any pending variable definitions here, but,
       if we do, we probably need to emit them before closing the
       block.  */
    if (!stab_emit_pending_vars(dhandle, info))
      return false;

    /* End an inner lexical block.  */
    if (!debug_end_block(dhandle, (value + info->file_start_offset +
                                   info->function_start_offset)))
      return false;

    --info->block_depth;
    if (info->block_depth < 0) {
      fprintf(stderr, _("Too many N_RBRACs\n"));
      return false;
    }
    break;

  case N_SO:
    /* This always ends a function.  */
    if (info->within_function) {
      bfd_vma endval;

      endval = value;
      if (*string != '\0' && info->function_end != (bfd_vma)-1 &&
          info->function_end < endval)
        endval = info->function_end;
      if (!stab_emit_pending_vars(dhandle, info) ||
          !debug_end_function(dhandle, endval))
        return false;
      info->within_function = false;
      info->function_end = (bfd_vma)-1;
    }

    /* An empty string is emitted by gcc at the end of a compilation
       unit.  */
    if (*string == '\0')
      return true;

    /* Just accumulate strings until we see a non N_SO symbol.  If
       the string starts with a directory separator or some other
       form of absolute path specification, we discard the previously
       accumulated strings.  */
    if (info->so_string == NULL)
      info->so_string = xstrdup(string);
    else {
      char *f;

      f = info->so_string;

      if (IS_ABSOLUTE_PATH(string))
        info->so_string = xstrdup(string);
      else
        info->so_string = concat(info->so_string, string, (const char *)NULL);
      free(f);
    }

    info->so_value = value;

    break;

  case N_SOL:
    /* Start an include file.  */
    len = strlen(string) + 1;
    copy = debug_xalloc(dhandle, len);
    memcpy(copy, string, len);
    if (!debug_start_source(dhandle, copy))
      return false;
    break;

  case N_BINCL:
    /* Start an include file which may be replaced.  */
    len = strlen(string) + 1;
    copy = debug_xalloc(dhandle, len);
    memcpy(copy, string, len);
    push_bincl(dhandle, info, copy, value);
    if (!debug_start_source(dhandle, copy))
      return false;
    break;

  case N_EINCL:
    /* End an N_BINCL include.  */
    if (!debug_start_source(dhandle, pop_bincl(info)))
      return false;
    break;

  case N_EXCL:
    /* This is a duplicate of a header file named by N_BINCL which
       was eliminated by the linker.  */
    if (!find_excl(info, string, value))
      return false;
    break;

  case N_SLINE:
    if (!debug_record_line(
            dhandle, desc,
            value + (info->within_function ? info->function_start_offset : 0)))
      return false;
    break;

  case N_BCOMM:
    if (!debug_start_common_block(dhandle, string))
      return false;
    break;

  case N_ECOMM:
    if (!debug_end_common_block(dhandle, string))
      return false;
    break;

  case N_FUN:
    if (*string == '\0') {
      if (info->within_function) {
        /* This always marks the end of a function; we don't
           need to worry about info->function_end.  */
        if (info->sections)
          value += info->function_start_offset;
        if (!stab_emit_pending_vars(dhandle, info) ||
            !debug_end_function(dhandle, value))
          return false;
        info->within_function = false;
        info->function_end = (bfd_vma)-1;
      }
      break;
    }

    /* A const static symbol in the .text section will have an N_FUN
       entry.  We need to use these to mark the end of the function,
       in case we are looking at gcc output before it was changed to
       always emit an empty N_FUN.  We can't call debug_end_function
       here, because it might be a local static symbol.  */
    if (info->within_function &&
        (info->function_end == (bfd_vma)-1 || value < info->function_end))
      info->function_end = value;

    /* Fall through.  */
    /* FIXME: gdb checks the string for N_STSYM, N_LCSYM or N_ROSYM
       symbols, and if it does not start with :S, gdb relocates the
       value to the start of the section.  gcc always seems to use
       :S, so we don't worry about this.  */
    /* Fall through.  */
  default: {
    const char *colon;

    colon = strchr(string, ':');
    if (colon != NULL && (colon[1] == 'f' || colon[1] == 'F')) {
      if (info->within_function) {
        bfd_vma endval;

        endval = value;
        if (info->function_end != (bfd_vma)-1 && info->function_end < endval)
          endval = info->function_end;
        if (!stab_emit_pending_vars(dhandle, info) ||
            !debug_end_function(dhandle, endval))
          return false;
        info->function_end = (bfd_vma)-1;
      }
      /* For stabs in sections, line numbers and block addresses
         are offsets from the start of the function.  */
      if (info->sections)
        info->function_start_offset = value;
      info->within_function = true;
    }

    if (!parse_stab_string(dhandle, info, type, desc, value, string,
                           string_end))
      return false;
  } break;

  case N_OPT:
    if (string != NULL && strcmp(string, "gcc2_compiled.") == 0)
      info->gcc_compiled = 2;
    else if (string != NULL && strcmp(string, "gcc_compiled.") == 0)
      info->gcc_compiled = 1;
    else
      info->n_opt_found = true;
    break;

  case N_OBJ:
  case N_ENDM:
  case N_MAIN:
  case N_WARNING:
    break;
  }

  return true;
}

static bool read_section_stabs_debugging_info(bfd *abfd, asymbol **syms,
                                              long symcount, void *dhandle,
                                              bool *pfound) {
  static struct {
    const char *secname;
    const char *strsecname;
  } names[] = {{".stab", ".stabstr"},
               {"LC_SYMTAB.stabs", "LC_SYMTAB.stabstr"},
               {"$GDB_SYMBOLS$", "$GDB_STRINGS$"}};
  unsigned int i;
  void *shandle;
  bool ret = false;

  *pfound = false;
  shandle = NULL;

  for (i = 0; i < sizeof names / sizeof names[0]; i++) {
    asection *sec, *strsec;

    sec = bfd_get_section_by_name(abfd, names[i].secname);
    strsec = bfd_get_section_by_name(abfd, names[i].strsecname);
    if (sec != NULL && (bfd_section_flags(sec) & SEC_HAS_CONTENTS) != 0 &&
        bfd_section_size(sec) >= 12 && strsec != NULL &&
        (bfd_section_flags(strsec) & SEC_HAS_CONTENTS) != 0) {
      bfd_size_type stabsize, strsize;
      bfd_byte *stabs, *strings;
      bfd_byte *stab;
      bfd_size_type stroff, next_stroff;

      if (!bfd_malloc_and_get_section(abfd, sec, &stabs)) {
        fprintf(stderr, "%s: %s: %s\n", bfd_get_filename(abfd),
                names[i].secname, bfd_errmsg(bfd_get_error()));
        goto out;
      }

      if (!bfd_malloc_and_get_section(abfd, strsec, &strings)) {
        fprintf(stderr, "%s: %s: %s\n", bfd_get_filename(abfd),
                names[i].strsecname, bfd_errmsg(bfd_get_error()));
        free(stabs);
        goto out;
      }
      /* Zero terminate the strings table, just in case.  */
      strsize = bfd_section_size(strsec);
      if (strsize != 0)
        strings[strsize - 1] = 0;
      if (shandle == NULL) {
        shandle = start_stab(dhandle, abfd, true, syms, symcount);
        if (shandle == NULL) {
          free(strings);
          free(stabs);
          goto out;
        }
      }

      *pfound = true;

      stroff = 0;
      next_stroff = 0;
      stabsize = bfd_section_size(sec);
      /* PR 17512: file: 078-60391-0.001:0.1.  */
      for (stab = stabs; stab <= (stabs + stabsize) - 12; stab += 12) {
        unsigned int strx;
        int type;
        int other ATTRIBUTE_UNUSED;
        int desc;
        bfd_vma value;

        /* This code presumes 32 bit values.  */

        strx = bfd_get_32(abfd, stab);
        type = bfd_get_8(abfd, stab + 4);
        other = bfd_get_8(abfd, stab + 5);
        desc = bfd_get_16(abfd, stab + 6);
        value = bfd_get_32(abfd, stab + 8);

        if (type == 0) {
          /* Special type 0 stabs indicate the offset to the
             next string table.  */
          stroff = next_stroff;
          next_stroff += value;
        } else {
          size_t len;
          char *f, *s;

          if (stroff + strx >= strsize) {
            fprintf(stderr,
                    _("%s: %s: stab entry %ld is corrupt, strx = 0x%x, type = "
                      "%d\n"),
                    bfd_get_filename(abfd), names[i].secname,
                    (long)(stab - stabs) / 12, strx, type);
            continue;
          }

          s = (char *)strings + stroff + strx;
          f = NULL;

          /* PR 17512: file: 002-87578-0.001:0.1.
             It is possible to craft a file where, without the 'strlen (s) > 0',
             an attempt to read the byte before 'strings' would occur.  */
          while ((len = strlen(s)) > 0 && s[len - 1] == '\\' &&
                 stab + 16 <= stabs + stabsize) {
            char *p;

            stab += 12;
            p = s + len - 1;
            *p = '\0';
            strx = stroff + bfd_get_32(abfd, stab);
            if (strx >= strsize) {
              fprintf(stderr, _("%s: %s: stab entry %ld is corrupt\n"),
                      bfd_get_filename(abfd), names[i].secname,
                      (long)(stab - stabs) / 12);
              break;
            }

            s = concat(s, (char *)strings + strx, (const char *)NULL);

            /* We have to restore the backslash, because, if
               the linker is hashing stabs strings, we may
               see the same string more than once.  */
            *p = '\\';

            free(f);
            f = s;
          }

          save_stab(type, desc, value, s);

          if (!parse_stab(dhandle, shandle, type, desc, value, s)) {
            stab_context();
            free_saved_stabs();
            free(f);
            free(stabs);
            free(strings);
            goto out;
          }

          free(f);
        }
      }

      free_saved_stabs();
      free(stabs);
      free(strings);
    }
  }
  ret = true;

out:
  if (shandle != NULL) {
    if (!finish_stab(dhandle, shandle, ret))
      return false;
  }

  return ret;
}


static struct debug_type_s *
debug_get_real_type(void *handle, debug_type type,
                    struct debug_type_real_list *list) {
  struct debug_type_real_list *l;
  struct debug_type_real_list rl;

  switch (type->kind) {
  default:
    return type;

  case DEBUG_KIND_INDIRECT:
  case DEBUG_KIND_NAMED:
  case DEBUG_KIND_TAGGED:
    break;
  }

  for (l = list; l != NULL; l = l->next) {
    if (l->t == type || l == l->next) {
      fprintf(stderr,
              _("debug_get_real_type: circular debug information for %s\n"),
              debug_get_type_name(handle, type));
      return NULL;
    }
  }

  rl.next = list;
  rl.t = type;

  switch (type->kind) {
    /* The default case is just here to avoid warnings.  */
  default:
  case DEBUG_KIND_INDIRECT:
    /* A valid non-self-referencing indirect type.  */
    if (*type->u.kindirect->slot != NULL && *type->u.kindirect->slot != type)
      return debug_get_real_type(handle, *type->u.kindirect->slot, &rl);
    return type;
  case DEBUG_KIND_NAMED:
  case DEBUG_KIND_TAGGED:
    return debug_get_real_type(handle, type->u.knamed->type, &rl);
  }
  /*NOTREACHED*/
}

static bool debug_type_samep(struct debug_handle *info, struct debug_type_s *t1, struct debug_type_s *t2);

static bool debug_class_type_samep(struct debug_handle *info,
                                   struct debug_type_s *t1,
                                   struct debug_type_s *t2) {
  struct debug_class_type *c1, *c2;

  c1 = t1->u.kclass;
  c2 = t2->u.kclass;

  if ((c1->fields == NULL) != (c2->fields == NULL) ||
      (c1->baseclasses == NULL) != (c2->baseclasses == NULL) ||
      (c1->methods == NULL) != (c2->methods == NULL) ||
      (c1->vptrbase == NULL) != (c2->vptrbase == NULL))
    return false;

  if (c1->fields != NULL) {
    struct debug_field_s **pf1, **pf2;

    for (pf1 = c1->fields, pf2 = c2->fields; *pf1 != NULL && *pf2 != NULL;
         pf1++, pf2++) {
      struct debug_field_s *f1, *f2;

      f1 = *pf1;
      f2 = *pf2;
      if (f1->name[0] != f2->name[0] || f1->visibility != f2->visibility ||
          f1->static_member != f2->static_member)
        return false;
      if (f1->static_member) {
        if (strcmp(f1->u.s.physname, f2->u.s.physname) != 0)
          return false;
      } else {
        if (f1->u.f.bitpos != f2->u.f.bitpos ||
            f1->u.f.bitsize != f2->u.f.bitsize)
          return false;
      }
      /* We do the checks which require function calls last.  We
         don't require that the types of fields have the same
         names, since that sometimes fails in the presence of
         typedefs and we really don't care.  */
      if (strcmp(f1->name, f2->name) != 0 || f1->type == NULL ||
          f2->type == NULL ||
          !debug_type_samep(info,
                            debug_get_real_type((void *)info, f1->type, NULL),
                            debug_get_real_type((void *)info, f2->type, NULL)))
        return false;
    }
    if (*pf1 != NULL || *pf2 != NULL)
      return false;
  }

  if (c1->vptrbase != NULL) {
    if (!debug_type_samep(info, c1->vptrbase, c2->vptrbase))
      return false;
  }

  if (c1->baseclasses != NULL) {
    struct debug_baseclass_s **pb1, **pb2;

    for (pb1 = c1->baseclasses, pb2 = c2->baseclasses;
         *pb1 != NULL && *pb2 != NULL; ++pb1, ++pb2) {
      struct debug_baseclass_s *b1, *b2;

      b1 = *pb1;
      b2 = *pb2;
      if (b1->bitpos != b2->bitpos || b1->is_virtual != b2->is_virtual ||
          b1->visibility != b2->visibility ||
          !debug_type_samep(info, b1->type, b2->type))
        return false;
    }
    if (*pb1 != NULL || *pb2 != NULL)
      return false;
  }

  if (c1->methods != NULL) {
    struct debug_method_s **pm1, **pm2;

    for (pm1 = c1->methods, pm2 = c2->methods; *pm1 != NULL && *pm2 != NULL;
         ++pm1, ++pm2) {
      struct debug_method_s *m1, *m2;

      m1 = *pm1;
      m2 = *pm2;
      if (m1->name[0] != m2->name[0] || strcmp(m1->name, m2->name) != 0 ||
          (m1->variants == NULL) != (m2->variants == NULL))
        return false;
      if (m1->variants != NULL) {
        struct debug_method_variant_s **pv1, **pv2;

        for (pv1 = m1->variants, pv2 = m2->variants;
             *pv1 != NULL && *pv2 != NULL; ++pv1, ++pv2) {
          struct debug_method_variant_s *v1, *v2;

          v1 = *pv1;
          v2 = *pv2;
          if (v1->physname[0] != v2->physname[0] ||
              v1->visibility != v2->visibility || v1->constp != v2->constp ||
              v1->volatilep != v2->volatilep || v1->voffset != v2->voffset ||
              (v1->context == NULL) != (v2->context == NULL) ||
              strcmp(v1->physname, v2->physname) != 0 ||
              !debug_type_samep(info, v1->type, v2->type))
            return false;
          if (v1->context != NULL) {
            if (!debug_type_samep(info, v1->context, v2->context))
              return false;
          }
        }
        if (*pv1 != NULL || *pv2 != NULL)
          return false;
      }
    }
    if (*pm1 != NULL || *pm2 != NULL)
      return false;
  }

  return true;
}

static bool
debug_type_samep (struct debug_handle *info, struct debug_type_s *t1,
		  struct debug_type_s *t2)
{
  struct debug_type_compare_list *l;
  struct debug_type_compare_list top;
  bool ret;

  if (t1 == NULL)
    return t2 == NULL;
  if (t2 == NULL)
    return false;

  while (t1->kind == DEBUG_KIND_INDIRECT)
    {
      t1 = *t1->u.kindirect->slot;
      if (t1 == NULL)
	return false;
    }
  while (t2->kind == DEBUG_KIND_INDIRECT)
    {
      t2 = *t2->u.kindirect->slot;
      if (t2 == NULL)
	return false;
    }

  if (t1 == t2)
    return true;

  /* As a special case, permit a typedef to match a tag, since C++
     debugging output will sometimes add a typedef where C debugging
     output will not.  */
  if (t1->kind == DEBUG_KIND_NAMED
      && t2->kind == DEBUG_KIND_TAGGED)
    return debug_type_samep (info, t1->u.knamed->type, t2);
  else if (t1->kind == DEBUG_KIND_TAGGED
	   && t2->kind == DEBUG_KIND_NAMED)
    return debug_type_samep (info, t1, t2->u.knamed->type);

  if (t1->kind != t2->kind
      || t1->size != t2->size)
    return false;

  /* Get rid of the trivial cases first.  */
  switch (t1->kind)
    {
    default:
      break;
    case DEBUG_KIND_VOID:
    case DEBUG_KIND_FLOAT:
    case DEBUG_KIND_COMPLEX:
    case DEBUG_KIND_BOOL:
      return true;
    case DEBUG_KIND_INT:
      return t1->u.kint == t2->u.kint;
    }

  /* We have to avoid an infinite recursion.  We do this by keeping a
     list of types which we are comparing.  We just keep the list on
     the stack.  If we encounter a pair of types we are currently
     comparing, we just assume that they are equal.  */
  for (l = info->compare_list; l != NULL; l = l->next)
    {
      if (l->t1 == t1 && l->t2 == t2)
	return true;
    }

  top.t1 = t1;
  top.t2 = t2;
  top.next = info->compare_list;
  info->compare_list = &top;

  switch (t1->kind)
    {
    default:
      abort ();
      ret = false;
      break;

    case DEBUG_KIND_STRUCT:
    case DEBUG_KIND_UNION:
    case DEBUG_KIND_CLASS:
    case DEBUG_KIND_UNION_CLASS:
      if (t1->u.kclass == NULL)
	ret = t2->u.kclass == NULL;
      else if (t2->u.kclass == NULL)
	ret = false;
      else if (t1->u.kclass->id > info->base_id
	       && t1->u.kclass->id == t2->u.kclass->id)
	ret = true;
      else
	ret = debug_class_type_samep (info, t1, t2);
      break;

    case DEBUG_KIND_ENUM:
      if (t1->u.kenum == NULL)
    ret = t2->u.kenum == NULL;
      else if (t2->u.kenum == NULL)
    ret = false;
      else if (t1->u.kenum->names == NULL)
	ret = t2->u.kenum->names == NULL;
      else if (t2->u.kenum->names == NULL)
	ret = false;
      else
	{
	  const char **pn1, **pn2;
	  bfd_signed_vma *pv1, *pv2;

	  pn1 = t1->u.kenum->names;
	  pn2 = t2->u.kenum->names;
	  pv1 = t1->u.kenum->values;
	  pv2 = t2->u.kenum->values;
	  while (*pn1 != NULL && *pn2 != NULL)
	    {
	      if (**pn1 != **pn2
		  || *pv1 != *pv2
		  || strcmp (*pn1, *pn2) != 0)
		break;
	      ++pn1;
	      ++pn2;
	      ++pv1;
	      ++pv2;
	    }
	  ret = *pn1 == NULL && *pn2 == NULL;
	}
      break;

    case DEBUG_KIND_POINTER:
      ret = debug_type_samep (info, t1->u.kpointer, t2->u.kpointer);
      break;

    case DEBUG_KIND_FUNCTION:
      if (t1->u.kfunction->varargs != t2->u.kfunction->varargs
	  || ! debug_type_samep (info, t1->u.kfunction->return_type,
				 t2->u.kfunction->return_type)
	  || ((t1->u.kfunction->arg_types == NULL)
	      != (t2->u.kfunction->arg_types == NULL)))
	ret = false;
      else if (t1->u.kfunction->arg_types == NULL)
	ret = true;
      else
	{
	  struct debug_type_s **a1, **a2;

	  a1 = t1->u.kfunction->arg_types;
	  a2 = t2->u.kfunction->arg_types;
	  while (*a1 != NULL && *a2 != NULL)
	    {
	      if (! debug_type_samep (info, *a1, *a2))
		break;
	      ++a1;
	      ++a2;
	    }
	  ret = *a1 == NULL && *a2 == NULL;
	}
      break;

    case DEBUG_KIND_REFERENCE:
      ret = debug_type_samep (info, t1->u.kreference, t2->u.kreference);
      break;

    case DEBUG_KIND_RANGE:
      ret = (t1->u.krange->lower == t2->u.krange->lower
	     && t1->u.krange->upper == t2->u.krange->upper
	     && debug_type_samep (info, t1->u.krange->type,
				  t2->u.krange->type));
      break;

    case DEBUG_KIND_ARRAY:
      ret = (t1->u.karray->lower == t2->u.karray->lower
	     && t1->u.karray->upper == t2->u.karray->upper
	     && t1->u.karray->stringp == t2->u.karray->stringp
	     && debug_type_samep (info, t1->u.karray->element_type,
				  t2->u.karray->element_type));
      break;

    case DEBUG_KIND_SET:
      ret = (t1->u.kset->bitstringp == t2->u.kset->bitstringp
	     && debug_type_samep (info, t1->u.kset->type, t2->u.kset->type));
      break;

    case DEBUG_KIND_OFFSET:
      ret = (debug_type_samep (info, t1->u.koffset->base_type,
			       t2->u.koffset->base_type)
	     && debug_type_samep (info, t1->u.koffset->target_type,
				  t2->u.koffset->target_type));
      break;

    case DEBUG_KIND_METHOD:
      if (t1->u.kmethod->varargs != t2->u.kmethod->varargs
	  || ! debug_type_samep (info, t1->u.kmethod->return_type,
				 t2->u.kmethod->return_type)
	  || ! debug_type_samep (info, t1->u.kmethod->domain_type,
				 t2->u.kmethod->domain_type)
	  || ((t1->u.kmethod->arg_types == NULL)
	      != (t2->u.kmethod->arg_types == NULL)))
	ret = false;
      else if (t1->u.kmethod->arg_types == NULL)
	ret = true;
      else
	{
	  struct debug_type_s **a1, **a2;

	  a1 = t1->u.kmethod->arg_types;
	  a2 = t2->u.kmethod->arg_types;
	  while (*a1 != NULL && *a2 != NULL)
	    {
	      if (! debug_type_samep (info, *a1, *a2))
		break;
	      ++a1;
	      ++a2;
	    }
	  ret = *a1 == NULL && *a2 == NULL;
	}
      break;

    case DEBUG_KIND_CONST:
      ret = debug_type_samep (info, t1->u.kconst, t2->u.kconst);
      break;

    case DEBUG_KIND_VOLATILE:
      ret = debug_type_samep (info, t1->u.kvolatile, t2->u.kvolatile);
      break;

    case DEBUG_KIND_NAMED:
    case DEBUG_KIND_TAGGED:
      ret = (strcmp (t1->u.knamed->name->name, t2->u.knamed->name->name) == 0
	     && debug_type_samep (info, t1->u.knamed->type,
				  t2->u.knamed->type));
      break;
    }

  info->compare_list = top.next;

  return ret;
}

static bool
debug_set_class_id (struct debug_handle *info, const char *tag,
		    struct debug_type_s *type)
{
  struct debug_class_type *c;
  struct debug_class_id *l;

  assert (type->kind == DEBUG_KIND_STRUCT
	  || type->kind == DEBUG_KIND_UNION
	  || type->kind == DEBUG_KIND_CLASS
	  || type->kind == DEBUG_KIND_UNION_CLASS);

  c = type->u.kclass;

  if (c->id > info->base_id)
    return true;

  for (l = info->id_list; l != NULL; l = l->next)
    {
      if (l->type->kind != type->kind)
	continue;

      if (tag == NULL)
	{
	  if (l->tag != NULL)
	    continue;
	}
      else
	{
	  if (l->tag == NULL
	      || l->tag[0] != tag[0]
	      || strcmp (l->tag, tag) != 0)
	    continue;
	}

      if (debug_type_samep (info, l->type, type))
	{
	  c->id = l->type->u.kclass->id;
	  return true;
	}
    }

  /* There are no identical types.  Use a new ID, and add it to the
     list.  */
  ++info->class_id;
  c->id = info->class_id;

  l = debug_xzalloc (info, sizeof (*l));

  l->type = type;
  l->tag = tag;

  l->next = info->id_list;
  info->id_list = l;

  return true;
}

static bool
debug_write_type (struct debug_handle *info,
		  const struct debug_write_fns *fns, void *fhandle,
		  struct debug_type_s *type, struct debug_name *name)
{
  unsigned int i;
  int is;
  const char *tag = NULL;

  if (type == DEBUG_TYPE_NULL)
    return (*fns->empty_type) (fhandle);

  /* Mark the type so that we don't define a type in terms of itself.  */
  type->mark = info->mark;

  /* If we have a name for this type, just output it.  We only output
     typedef names after they have been defined.  We output type tags
     whenever we are not actually defining them.  */
  if ((type->kind == DEBUG_KIND_NAMED
       || type->kind == DEBUG_KIND_TAGGED)
      && (type->u.knamed->name->mark == info->mark
	  || (type->kind == DEBUG_KIND_TAGGED
	      && type->u.knamed->name != name)))
    {
      if (type->kind == DEBUG_KIND_NAMED)
	return (*fns->typedef_type) (fhandle, type->u.knamed->name->name);
      else
	{
	  struct debug_type_s *real;
	  unsigned int id;

	  real = debug_get_real_type ((void *) info, type, NULL);
	  if (real == NULL)
	    return (*fns->empty_type) (fhandle);
	  id = 0;
	  if ((real->kind == DEBUG_KIND_STRUCT
	       || real->kind == DEBUG_KIND_UNION
	       || real->kind == DEBUG_KIND_CLASS
	       || real->kind == DEBUG_KIND_UNION_CLASS)
	      && real->u.kclass != NULL)
	    {
	      if (real->u.kclass->id <= info->base_id)
		{
		  if (! debug_set_class_id (info,
					    type->u.knamed->name->name,
					    real))
		    return false;
		}
	      id = real->u.kclass->id;
	    }

	  return (*fns->tag_type) (fhandle, type->u.knamed->name->name, id,
				   real->kind);
	}
    }

  /* Mark the name after we have already looked for a known name, so
     that we don't just define a type in terms of itself.  We need to
     mark the name here so that a struct containing a pointer to
     itself will work.  */
  if (name != NULL)
    name->mark = info->mark;

  if (name != NULL
      && type->kind != DEBUG_KIND_NAMED
      && type->kind != DEBUG_KIND_TAGGED)
    {
      assert (name->kind == DEBUG_OBJECT_TAG);
      tag = name->name;
    }

  switch (type->kind)
    {
    case DEBUG_KIND_ILLEGAL:
      debug_error (_("debug_write_type: illegal type encountered"));
      return false;
    case DEBUG_KIND_INDIRECT:
      /* Prevent infinite recursion.  */
      if (*type->u.kindirect->slot != DEBUG_TYPE_NULL
	  && (*type->u.kindirect->slot)->mark == info->mark)
	return (*fns->empty_type) (fhandle);
      return debug_write_type (info, fns, fhandle, *type->u.kindirect->slot,
			       name);
    case DEBUG_KIND_VOID:
      return (*fns->void_type) (fhandle);
    case DEBUG_KIND_INT:
      return (*fns->int_type) (fhandle, type->size, type->u.kint);
    case DEBUG_KIND_FLOAT:
      return (*fns->float_type) (fhandle, type->size);
    case DEBUG_KIND_COMPLEX:
      return (*fns->complex_type) (fhandle, type->size);
    case DEBUG_KIND_BOOL:
      return (*fns->bool_type) (fhandle, type->size);
    case DEBUG_KIND_STRUCT:
    case DEBUG_KIND_UNION:
      if (type->u.kclass != NULL)
	{
	  if (type->u.kclass->id <= info->base_id)
	    {
	      if (! debug_set_class_id (info, tag, type))
		return false;
	    }

	  if (info->mark == type->u.kclass->mark)
	    {
	      /* We are currently outputting this struct, or we have
		 already output it.  I don't know if this can happen,
		 but it can happen for a class.  */
	      assert (type->u.kclass->id > info->base_id);
	      return (*fns->tag_type) (fhandle, tag, type->u.kclass->id,
				       type->kind);
	    }
	  type->u.kclass->mark = info->mark;
	}

      if (! (*fns->start_struct_type) (fhandle, tag,
				       (type->u.kclass != NULL
					? type->u.kclass->id
					: 0),
				       type->kind == DEBUG_KIND_STRUCT,
				       type->size))
	return false;
      if (type->u.kclass != NULL
	  && type->u.kclass->fields != NULL)
	{
	  for (i = 0; type->u.kclass->fields[i] != NULL; i++)
	    {
	      struct debug_field_s *f;

	      f = type->u.kclass->fields[i];
	      if (! debug_write_type (info, fns, fhandle, f->type,
				      (struct debug_name *) NULL)
		  || ! (*fns->struct_field) (fhandle, f->name, f->u.f.bitpos,
					     f->u.f.bitsize, f->visibility))
		return false;
	    }
	}
      return (*fns->end_struct_type) (fhandle);
    case DEBUG_KIND_CLASS:
    case DEBUG_KIND_UNION_CLASS:
      return debug_write_class_type (info, fns, fhandle, type, tag);
    case DEBUG_KIND_ENUM:
      return (*fns->enum_type) (fhandle, tag, type->u.kenum->names,
				type->u.kenum->values);
    case DEBUG_KIND_POINTER:
      if (! debug_write_type (info, fns, fhandle, type->u.kpointer,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->pointer_type) (fhandle);
    case DEBUG_KIND_FUNCTION:
      if (! debug_write_type (info, fns, fhandle,
			      type->u.kfunction->return_type,
			      (struct debug_name *) NULL))
	return false;
      if (type->u.kfunction->arg_types == NULL)
	is = -1;
      else
	{
	  for (is = 0; type->u.kfunction->arg_types[is] != NULL; is++)
	    if (! debug_write_type (info, fns, fhandle,
				    type->u.kfunction->arg_types[is],
				    (struct debug_name *) NULL))
	      return false;
	}
      return (*fns->function_type) (fhandle, is,
				    type->u.kfunction->varargs);
    case DEBUG_KIND_REFERENCE:
      if (! debug_write_type (info, fns, fhandle, type->u.kreference,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->reference_type) (fhandle);
    case DEBUG_KIND_RANGE:
      if (! debug_write_type (info, fns, fhandle, type->u.krange->type,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->range_type) (fhandle, type->u.krange->lower,
				 type->u.krange->upper);
    case DEBUG_KIND_ARRAY:
      if (! debug_write_type (info, fns, fhandle, type->u.karray->element_type,
			      (struct debug_name *) NULL)
	  || ! debug_write_type (info, fns, fhandle,
				 type->u.karray->range_type,
				 (struct debug_name *) NULL))
	return false;
      return (*fns->array_type) (fhandle, type->u.karray->lower,
				 type->u.karray->upper,
				 type->u.karray->stringp);
    case DEBUG_KIND_SET:
      if (! debug_write_type (info, fns, fhandle, type->u.kset->type,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->set_type) (fhandle, type->u.kset->bitstringp);
    case DEBUG_KIND_OFFSET:
      if (! debug_write_type (info, fns, fhandle, type->u.koffset->base_type,
			      (struct debug_name *) NULL)
	  || ! debug_write_type (info, fns, fhandle,
				 type->u.koffset->target_type,
				 (struct debug_name *) NULL))
	return false;
      return (*fns->offset_type) (fhandle);
    case DEBUG_KIND_METHOD:
      if (! debug_write_type (info, fns, fhandle,
			      type->u.kmethod->return_type,
			      (struct debug_name *) NULL))
	return false;
      if (type->u.kmethod->arg_types == NULL)
	is = -1;
      else
	{
	  for (is = 0; type->u.kmethod->arg_types[is] != NULL; is++)
	    if (! debug_write_type (info, fns, fhandle,
				    type->u.kmethod->arg_types[is],
				    (struct debug_name *) NULL))
	      return false;
	}
      if (type->u.kmethod->domain_type != NULL)
	{
	  if (! debug_write_type (info, fns, fhandle,
				  type->u.kmethod->domain_type,
				  (struct debug_name *) NULL))
	    return false;
	}
      return (*fns->method_type) (fhandle,
				  type->u.kmethod->domain_type != NULL,
				  is,
				  type->u.kmethod->varargs);
    case DEBUG_KIND_CONST:
      if (! debug_write_type (info, fns, fhandle, type->u.kconst,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->const_type) (fhandle);
    case DEBUG_KIND_VOLATILE:
      if (! debug_write_type (info, fns, fhandle, type->u.kvolatile,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->volatile_type) (fhandle);
    case DEBUG_KIND_NAMED:
      return debug_write_type (info, fns, fhandle, type->u.knamed->type,
			       (struct debug_name *) NULL);
    case DEBUG_KIND_TAGGED:
      return debug_write_type (info, fns, fhandle, type->u.knamed->type,
			       type->u.knamed->name);
    default:
      abort ();
      return false;
    }
}

static bool
debug_write_name (struct debug_handle *info,
		  const struct debug_write_fns *fns, void *fhandle,
		  struct debug_name *n)
{
  switch (n->kind)
    {
    case DEBUG_OBJECT_TYPE:
      if (! debug_write_type (info, fns, fhandle, n->u.type, n)
	  || ! (*fns->typdef) (fhandle, n->name))
	return false;
      return true;
    case DEBUG_OBJECT_TAG:
      if (! debug_write_type (info, fns, fhandle, n->u.tag, n))
	return false;
      return (*fns->tag) (fhandle, n->name);
    case DEBUG_OBJECT_VARIABLE:
      if (! debug_write_type (info, fns, fhandle, n->u.variable->type,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->variable) (fhandle, n->name, n->u.variable->kind,
			       n->u.variable->val);
    case DEBUG_OBJECT_FUNCTION:
      return debug_write_function (info, fns, fhandle, n->name,
				   n->linkage, n->u.function);
    case DEBUG_OBJECT_INT_CONSTANT:
      return (*fns->int_constant) (fhandle, n->name, n->u.int_constant);
    case DEBUG_OBJECT_FLOAT_CONSTANT:
      return (*fns->float_constant) (fhandle, n->name, n->u.float_constant);
    case DEBUG_OBJECT_TYPED_CONSTANT:
      if (! debug_write_type (info, fns, fhandle, n->u.typed_constant->type,
			      (struct debug_name *) NULL))
	return false;
      return (*fns->typed_constant) (fhandle, n->name,
				     n->u.typed_constant->val);
    default:
      abort ();
      return false;
    }
  /*NOTREACHED*/
}

bool debug_write(void *handle, const struct debug_write_fns *fns,
                 void *fhandle) {
  struct debug_handle *info = (struct debug_handle *)handle;
  struct debug_unit *u;

  /* We use a mark to tell whether we have already written out a
     particular name.  We use an integer, so that we don't have to
     clear the mark fields if we happen to write out the same
     information more than once.  */
  ++info->mark;

  /* The base_id field holds an ID value which will never be used, so
     that we can tell whether we have assigned an ID during this call
     to debug_write.  */
  info->base_id = info->class_id;

  /* We keep a linked list of classes for which was have assigned ID's
     during this call to debug_write.  */
  info->id_list = NULL;

  for (u = info->units; u != NULL; u = u->next) {
    struct debug_file *f;
    bool first_file;

    info->current_write_lineno = u->linenos;
    info->current_write_lineno_index = 0;

    if (!(*fns->start_compilation_unit)(fhandle, u->files->filename))
      return false;

    first_file = true;
    for (f = u->files; f != NULL; f = f->next) {
      struct debug_name *n;

      if (first_file)
        first_file = false;
      else if (!(*fns->start_source)(fhandle, f->filename))
        return false;

      if (f->globals != NULL)
        for (n = f->globals->list; n != NULL; n = n->next)
          if (!debug_write_name(info, fns, fhandle, n))
            return false;
    }

    /* Output any line number information which hasn't already been
       handled.  */
    if (!debug_write_linenos(info, fns, fhandle, (bfd_vma)-1))
      return false;
  }

  return true;
}

bool print_debugging_info(FILE *f, void *dhandle, bfd *abfd, asymbol **syms,
                          char *(*demangler)(struct bfd *, const char *, int),
                          bool as_tags) {
  struct pr_handle info;

  info.f = f;
  info.indent = 0;
  info.stack = NULL;
  info.parameter = 0;
  info.filename = NULL;
  info.abfd = abfd;
  info.syms = syms;
  info.demangler = demangler;

  if (as_tags) {
    fputs("!_TAG_FILE_FORMAT\t2\t/extended format/\n", f);
    fputs("!_TAG_FILE_SORTED\t0\t/0=unsorted, 1=sorted/\n", f);
    fputs("!_TAG_PROGRAM_AUTHOR\tIan Lance Taylor, Salvador E. Tropea and "
          "others\t//\n",
          f);
    fputs("!_TAG_PROGRAM_NAME\tobjdump\t/From GNU binutils/\n", f);
  }

  bool ret = debug_write(dhandle, as_tags ? &tg_fns : &pr_fns, &info);
  while (info.stack != NULL) {
    struct pr_stack *s = info.stack;
    info.stack = s->next;
    free(s->type);
    free(s->method);
    free(s->parents);
    free(s);
  }
  free(info.filename);
  return ret;
}


static void dump_bfd(bfd *abfd, bool is_mainfile) {
  const struct elf_backend_data *bed;

  if (bfd_big_endian(abfd))
    byte_get = byte_get_big_endian;
  else if (bfd_little_endian(abfd))
    byte_get = byte_get_little_endian;
  else
    byte_get = NULL;

  /* Load any separate debug information files.  */
  if (byte_get != NULL && might_need_separate_debug_info(is_mainfile)) {
    load_separate_debug_files(abfd, bfd_get_filename(abfd));

    /* If asked to do so, recursively dump the separate files.  */
    if (do_follow_links) {
      struct separate_info *i;

      for (i = first_separate_info; i != NULL; i = i->next)
        dump_bfd(i->handle, false);
    }
  }

  /* Adjust user-specified start and stop limits for targets that use
     signed addresses.  */
  if (bfd_get_flavour(abfd) == bfd_target_elf_flavour &&
      (bed = get_elf_backend_data(abfd)) != NULL && bed->sign_extend_vma) {
    start_address = sign_extend_address(abfd, start_address, bed->s->arch_size);
    stop_address = sign_extend_address(abfd, stop_address, bed->s->arch_size);
  }

  /* If we are adjusting section VMA's, change them all now.  Changing
     the BFD information is a hack.  However, we must do it, or
     bfd_find_nearest_line will not do the right thing.  */
  if (adjust_section_vma != 0) {
    bool has_reloc = (abfd->flags & HAS_RELOC);
    bfd_map_over_sections(abfd, adjust_addresses, &has_reloc);
  }

  if (is_mainfile || process_links) {
    if (!dump_debugging_tags && !suppress_bfd_header)
      printf(_("\n%s:     file format %s\n"),
             sanitize_string(bfd_get_filename(abfd)), abfd->xvec->name);
    if (dump_ar_hdrs)
      print_arelt_descr(stdout, abfd, true, false);
    if (dump_file_header)
      dump_bfd_header(abfd);
    if (dump_private_headers)
      dump_bfd_private_header(abfd);
    if (dump_private_options != NULL)
      dump_target_specific(abfd);
    if (!dump_debugging_tags && !suppress_bfd_header)
      putchar('\n');
  }

  if (dump_symtab || dump_reloc_info || disassemble || dump_debugging ||
      dump_dwarf_section_info) {
    syms = slurp_symtab(abfd);

    /* If following links, load any symbol tables from the linked files as well.
     */
    if (do_follow_links && is_mainfile) {
      struct separate_info *i;

      for (i = first_separate_info; i != NULL; i = i->next) {
        asymbol **extra_syms;
        long old_symcount = symcount;

        extra_syms = slurp_symtab(i->handle);

        if (extra_syms) {
          if (old_symcount == 0) {
            free(syms);
            syms = extra_syms;
          } else {
            syms = xrealloc(
                syms, ((symcount + old_symcount + 1) * sizeof(asymbol *)));
            memcpy(syms + old_symcount, extra_syms,
                   (symcount + 1) * sizeof(asymbol *));
            free(extra_syms);
          }
        }

        symcount += old_symcount;
      }
    }
  }

  if (is_mainfile || process_links) {
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
      dump_symbols(abfd, false);
    if (dump_dynamic_symtab)
      dump_symbols(abfd, true);
  }
  if (dump_dwarf_section_info)
    dump_dwarf(abfd, is_mainfile);
  if (is_mainfile || process_links) {
    if (dump_ctf_section_info)
      dump_ctf(abfd, dump_ctf_section_name, dump_ctf_parent_name,
               dump_ctf_parent_section_name);
    if (dump_sframe_section_info)
      dump_sframe_section(abfd, dump_sframe_section_name, is_mainfile);
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
  }

  if (dump_debugging) {
    void *dhandle;

    dhandle = read_debugging_info(abfd, syms, symcount, true);
    if (dhandle != NULL) {
      if (!print_debugging_info(stdout, dhandle, abfd, syms, bfd_demangle,
                                dump_debugging_tags != 0)) {
        non_fatal(_("%s: printing debugging information failed"),
                  bfd_get_filename(abfd));
        exit_status = 1;
      }
    }
    /* PR 6483: If there was no STABS debug info in the file, try
       DWARF instead.  */
    else if (!dump_dwarf_section_info) {
      dwarf_select_sections_all();
      dump_dwarf(abfd, is_mainfile);
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

  if (is_mainfile)
    free_debug_memory();
}
