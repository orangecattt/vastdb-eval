#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define ut64 uint64_t
#define st64 int64_t
#define ut32 uint32_t
#define st32 int32_t
#define ut16 uint16_t
#define st16 int16_t
#define ut8 uint8_t
#define st8 int8_t

#define R_ALIGNED(x) __attribute__((aligned(x)))
typedef R_ALIGNED(1) ut16 uut16;
typedef R_ALIGNED(1) ut32 uut32;
typedef R_ALIGNED(1) ut64 uut64;

#define UT16_MAX ((uint16_t)0xFFFF)
#define UT32_MAX ((uint32_t)0xFFFFFFFF)
#define UT64_MAX ((uint64_t)0xFFFFFFFFFFFFFFFFULL)

#ifndef R_API
#define R_API __attribute__((visibility("default")))
#endif
#ifndef R_IPI
#define R_IPI
#endif

#define R_PERM_R	4
#define R_PERM_W	2
#define R_PERM_X	1
#define R_PERM_RW	(R_PERM_R|R_PERM_W)
#define R_PERM_RX	(R_PERM_R|R_PERM_X)
#define R_PERM_RWX	(R_PERM_R|R_PERM_W|R_PERM_X)

#ifdef R_NEW
#undef R_NEW
#endif
#ifdef R_NEW0
#undef R_NEW0
#endif
#ifdef R_FREE
#undef R_FREE
#endif

#define R_NEW0(x) (x*)calloc(1, sizeof (x))
#define R_NEW(x) (x*)malloc(sizeof (x))
#define R_FREE(x) do { free((void*)(x)); (x) = NULL; } while(0)

#ifndef PFMT64d
#define PFMT64d PRId64
#endif

#define R_SYS_BITS_PACK(x) (x)

#define R_LIST_FREE if (x) { r_list_free (x); (x) = NULL; }

typedef void (*RListFree)(void *ptr);

typedef struct r_list_iter_t {
	void *data;
	struct r_list_iter_t *n, *p;
} RListIter;

typedef struct r_list_t {
	RListIter *head;
	RListIter *tail;
	RListFree free;
	int length;
	bool sorted;
} RList;

typedef int (*RListComparator)(const void *a, const void *b);

#define r_list_foreach(list, it, pos)\
	if (list)\
		for (it = list->head; it && (pos = it->data, 1); it = it->n)

R_API RList *r_list_new(void);
R_API RList *r_list_newf(RListFree f);
R_API RListIter *r_list_append(RList *list, void *data);
R_API void *r_list_get_n(const RList *list, int n);
R_API void r_list_free(RList *list);
R_API RListIter *r_list_find(const RList *list, const void *p, RListComparator cmp);

static inline ut16 r_read_le16(const void *src) {
	if (!src) {
		return UT16_MAX;
	}
	const ut8 *s = (const ut8*)src;
	return (((ut16)s[1]) << 8) | (((ut16)s[0]) << 0);
}

typedef struct r_buf_t RBuffer;

R_API ut64 r_buf_size(RBuffer *b);
R_API ut8 r_buf_read8_at(RBuffer *b, ut64 addr);
R_API st64 r_buf_read_at(RBuffer *b, ut64 addr, ut8 *buf, ut64 len);
R_API st64 r_buf_fread_at(RBuffer *b, ut64 addr, ut8 *buf, const char *fmt, int n);

static inline ut16 r_buf_read_le16_at(RBuffer *b, ut64 addr) {
	ut8 buf[sizeof (ut16)];
	int r = (int) r_buf_read_at (b, addr, buf, sizeof (buf));
	return r == sizeof (buf)? r_read_le16 (buf): UT16_MAX;
}

R_API char *r_str_newf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#define R_BIN_BIND_GLOBAL_STR "GLOBAL"

typedef struct r_bin_name_t {
	char *name;
	char *oname;
	char *fname;
} RBinName;

typedef struct r_bin_addr_t {
	ut64 vaddr;
	ut64 paddr;
	ut64 hvaddr;
	ut64 hpaddr;
	int type;
	int bits;
} RBinAddr;

typedef struct r_bin_section_t {
	char *name;
	ut64 size;
	ut64 vsize;
	ut64 vaddr;
	ut64 paddr;
	ut32 perm;
	ut32 flags;
	const char *type;
	const char *arch;
	char *format;
	int bits;
	bool has_strings;
	bool add;
	bool is_data;
	bool is_segment;
	int backing_fd;
} RBinSection;

typedef struct r_bin_symbol_t {
	RBinName *name;
	char *classname;
	char *libname;
	const char *forwarder;
	const char *bind;
	const char *type;
	const char *rtype;
	bool is_imported;
	ut64 vaddr;
	ut64 paddr;
	ut32 size;
	ut32 ordinal;
	int lang;
	int bits;
	int dup_count;
} RBinSymbol;

R_API RBinName *r_bin_name_new_from(const char *name);

typedef struct r_bin_object_t {
  void *bin_obj;
} RBinObject;

typedef struct r_bin_file_t {
	char *file;
	int fd;
	ut64 size;
	int rawstr;
	int strmode;
	ut32 id;
	RBuffer *buf;
	ut64 offset;
	RBinObject *bo;
	void *xtr_obj;
	ut64 user_baddr;
	ut64 loadaddr;
	int minstrlen;
	int maxstrlen;
	int narch;
	struct r_bin_xtr_plugin_t *curxtr;
	RList *xtr_data;
	void *sdb;
	void *sdb_info;
	void *sdb_addrinfo;
	void *addrline;
	void *addrinfo_priv;
	struct r_bin_t *rbin;
	int string_count;
	void *options;
} RBinFile;

enum {
	LOBYTE = 0,
	SEL_16 = 2,
	POI_32 = 3,
	OFF_16 = 5,
	POI_48 = 11,
	OFF_32 = 13
};

enum {
	INTERNAL_REF = 0,
	IMPORTED_ORD = 1,
	IMPORTED_NAME = 2,
	OSFIXUP = 3,
	ADDITIVE = 4
};

typedef struct _RELOC {
	ut8 type;
	ut8 flags;
	ut16 offset;
	union {
		ut16 index;
		struct {
			ut8 segnum;
			ut8 zero;
			ut16 segoff;
		};
		struct {
			ut16 ignore;
			ut16 entry_ordinal;
		};
		struct {
			ut16 align1;
			ut16 func_ord;
		};
		struct {
			ut16 align2;
			ut16 name_off;
		};
	};
} NE_image_reloc_item;

enum {
	IS_DATA = 1,
	IS_MOVEABLE = 0x10,
	IS_SHAREABLE = 0x20,
	IS_PRELOAD = 0x40,
	RELOCINFO = 0x100,
	IS_RX = 0x1000
};

enum {
	NOAUTODATA = 0,
	SINGLEDATA = 1,
	LINKERROR = 0x2000,
	LIBRARY = 0x8000
};

typedef struct _SEGMENT {
	ut16 offset;
	ut16 length;
	ut16 flags;
	ut16 minAllocSz;
} NE_image_segment_entry;

/* --- From ne.h --- */
typedef struct {
	char *name;
	ut32 offset;
	ut32 size;
} r_ne_resource_entry;

typedef struct {
	char *name;
	RList *entry;
} r_ne_resource;

typedef struct {
	char sig[2];
	ut8 MajLinkerVersion;
	ut8 MinLinkerVersion;
	ut16 EntryTableOffset;
	ut16 EntryTableLength;
	ut32 FileLoadCRC;
	ut8 ProgFlags;
	ut8 ApplFlags;
	ut8 AutoDataSegIndex;
	ut16 InitHeapSize;
	ut16 InitStackSize;
	ut16 ipEntryPoint;
	ut16 csEntryPoint;
	ut32 InitStack;
	ut16 SegCount;
	ut16 ModRefs;
	ut16 NoResNamesTabSiz;
	ut16 SegTableOffset;
	ut16 ResTableOffset;
	ut16 ResidNamTable;
	ut16 ModRefTable;
	ut16 ImportNameTable;
	ut32 OffStartNonResTab;
	ut16 MovEntryCount;
	ut16 FileAlnSzShftCnt;
	ut16 nResTabEntries;
	ut8 targOS;
	ut8 OS2EXEFlags;
	ut16 retThunkOffset;
	ut16 segrefthunksoff;
	ut16 mincodeswap;
	ut8 expctwinver[2];
} NE_image_header;


typedef struct {
	NE_image_header *ne_header;
	ut16 header_offset;
	ut16 alignment;
	NE_image_segment_entry *segment_entries;
	ut8 *entry_table;
	ut8 *resident_name_table;
	RBuffer *buf;
	RList *segments;
	RList *entries;
	RList *resources;
	RList *imports;
	RList *symbols;
	char *os;
} r_bin_ne_obj_t;

RList *r_bin_ne_get_segments(r_bin_ne_obj_t *bin);
RList *r_bin_ne_get_entrypoints(r_bin_ne_obj_t *bin);
RList *r_bin_ne_get_symbols(r_bin_ne_obj_t *bin);

static int __translate_perms(int flags);
static int __find_symbol_by_paddr(const void *paddr, const void *sym);

RList *r_bin_ne_get_segments(r_bin_ne_obj_t *bin) {
	int i;
	if (!bin || !bin->segment_entries) {
		return NULL;
	}
	RList *segments = r_list_newf (free);
	for (i = 0; i < bin->ne_header->SegCount; i++) {
		RBinSection *bs = R_NEW0 (RBinSection);
		if (!bs) {
			return segments;
		}
		NE_image_segment_entry *se = &bin->segment_entries[i];
		bs->size = se->length;
		bs->vsize = se->minAllocSz ? se->minAllocSz : 64000;
		bs->bits = R_SYS_BITS_PACK (16);
		bs->is_data = se->flags & IS_DATA;
		bs->perm = __translate_perms (se->flags);
		bs->paddr = (ut64)se->offset * bin->alignment;
		bs->name = r_str_newf ("%s.%" PFMT64d, se->flags & IS_MOVEABLE ? "MOVEABLE" : "FIXED", bs->paddr);
		bs->is_segment = true;
		r_list_append (segments, bs);
	}
	bin->segments = segments;
	return segments;
}

RList *r_bin_ne_get_entrypoints(r_bin_ne_obj_t *bin) {
	if (!bin->entry_table) {
		return NULL;
	}
	RList *entries = r_list_newf (free);
	if (!entries) {
		return NULL;
	}
	RList *segments = r_bin_ne_get_segments (bin);
	if (!segments) {
		r_list_free (entries);
		return NULL;
	}
	if (bin->ne_header->csEntryPoint) {
		RBinAddr *entry = R_NEW0 (RBinAddr);
		if (!entry) {
			r_list_free (entries);
			return NULL;
		}
		entry->bits = 16;
		ut32 entry_cs = bin->ne_header->csEntryPoint;
		RBinSection *s = r_list_get_n (segments, entry_cs - 1);
		entry->paddr = bin->ne_header->ipEntryPoint + (s? s->paddr: 0);

		r_list_append (entries, entry);
	}
	int off = 0;
	size_t tableat = bin->header_offset + bin->ne_header->EntryTableOffset;
	while (off < bin->ne_header->EntryTableLength) {
		if (tableat + off >= r_buf_size (bin->buf)) {
			break;
		}
		ut8 bundle_length = *(ut8 *)(bin->entry_table + off);
		if (!bundle_length) {
			break;
		}
		off++;
		ut8 bundle_type = *(ut8 *)(bin->entry_table + off);
		off++;
		int i;
		for (i = 0; i < bundle_length; i++) {
			if (tableat + off + 4 >= r_buf_size (bin->buf)) {
				break;
			}
			RBinAddr *entry = R_NEW0 (RBinAddr);
			if (!entry) {
				r_list_free (entries);
				return NULL;
			}
			off++;
			if (!bundle_type) { // Skip
				off--;
				free (entry);
				break;
			} else if (bundle_type == 0xff) { // moveable
				off += 2;
				ut8 segnum = *(bin->entry_table + off);
				off++;
				if (off > bin->ne_header->EntryTableLength) {
					free (entry);
					break;
				}
				ut16 segoff = r_read_le16 (bin->entry_table + off);
				if (segnum > 0 && segnum < bin->ne_header->SegCount) {
					entry->paddr = (ut64)bin->segment_entries[segnum - 1].offset * bin->alignment + segoff;
				}
			} else { // Fixed
				if (off + 2 >= bin->ne_header->EntryTableLength) {
					free (entry);
					break;
				}
				ut16 delta = r_read_le16 (bin->entry_table + off);
				if (bundle_type < bin->ne_header->SegCount) {
					entry->paddr = (ut64)bin->segment_entries[bundle_type - 1].offset
						* bin->alignment + delta;
				}
			}
			off += 2;
			r_list_append (entries, entry);
		}
	}
	r_list_free (segments);
	bin->entries = entries;
	return entries;
}

RList *r_bin_ne_get_symbols(r_bin_ne_obj_t *bin) {
	RBinSymbol *sym;
	ut16 off = bin->ne_header->ResidNamTable + bin->header_offset;
	RList *symbols = r_list_newf (free);
	if (!symbols) {
		return NULL;
	}
	RList *entries = r_bin_ne_get_entrypoints (bin);
	bool resident = true, first = true;
	while (entries) {
		ut8 sz = r_buf_read8_at (bin->buf, off);
		if (!sz) {
			first = true;
			if (resident) {
				resident = false;
				off = bin->ne_header->OffStartNonResTab;
				sz = r_buf_read8_at (bin->buf, off);
				if (!sz) {
					break;
				}
			} else {
				break;
			}
		}
		char *name = malloc ((ut64)sz + 1);
		if (!name) {
			break;
		}
		off++;
		r_buf_read_at (bin->buf, off, (ut8 *)name, sz);
		name[sz] = '\0';
		off += sz;
		sym = R_NEW0 (RBinSymbol);
		if (!sym) {
			break;
		}
		sym->name = r_bin_name_new_from (name);
		if (!first) {
			sym->bind = R_BIN_BIND_GLOBAL_STR;
		}
		ut16 entry_off = r_buf_read_le16_at (bin->buf, off);
		off += 2;
		RBinAddr *entry = r_list_get_n (entries, entry_off);
		if (entry) {
			sym->paddr = entry->paddr;
		} else {
			sym->paddr = -1;
		}
		sym->ordinal = entry_off;
		r_list_append (symbols, sym);
		first = false;
	}
	RListIter *it;
	RBinAddr *en;
	int i = 1;
	r_list_foreach (entries, it, en) {
		if (!r_list_find (symbols, &en->paddr, __find_symbol_by_paddr)) {
			sym = R_NEW0 (RBinSymbol);
			if (!sym) {
				break;
			}
			sym->name = r_bin_name_new_from (r_str_newf ("entry%d", i - 1));
			sym->paddr = en->paddr;
			sym->bind = R_BIN_BIND_GLOBAL_STR;
			sym->ordinal = i;
			r_list_append (symbols, sym);
		}
		i++;
	}
	bin->symbols = symbols;
	return symbols;
}

static RList *symbols(RBinFile *bf) {
	return r_bin_ne_get_symbols (bf->bo->bin_obj);
}
