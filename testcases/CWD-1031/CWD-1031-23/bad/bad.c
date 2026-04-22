#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t ut64;
typedef int64_t st64;
typedef uint32_t ut32;
typedef uint16_t ut16;
typedef uint8_t ut8;
typedef int8_t st8;

#define UT64_MAX ((ut64)0xFFFFFFFFFFFFFFFFULL)
#define UT32_MAX 0xFFFFFFFFU

#define R_API

#define R_RETURN_IF_FAIL(expr) do { if (!(expr)) { return; } } while (0)
#define R_RETURN_VAL_IF_FAIL(expr, val) do { if (!(expr)) { return (val); } } while (0)

#define R_NEW0(x) (x*)calloc(1, sizeof (x))
#define R_NEWS0(x,y) (x*)calloc(y, sizeof (x))
#define R_FREE(x) { free((void *)x); x = NULL; }

typedef int (*PrintfCallback)(const char *str, ...);

typedef enum r_log_level {
	R_LOG_LEVEL_FATAL = 0,
	R_LOG_LEVEL_ERROR = 1,
	R_LOG_LEVEL_INFO = 2,
	R_LOG_LEVEL_WARN = 3,
	R_LOG_LEVEL_TODO = 4,
	R_LOG_LEVEL_DEBUG = 5,
	R_LOG_LEVEL_LAST = 7,
} RLogLevel;

#define R_LOG_ORIGIN __FUNCTION__

static inline bool r_log_match(int level, const char *origin) { (void)level; (void)origin; return true; }
static inline void r_log_message(RLogLevel level, const char *origin, const char *func, int line, const char *fmt, ...) { (void)level; (void)origin; (void)func; (void)line; (void)fmt; }

#define R_LOG_ERROR(f,...) if (r_log_match (R_LOG_LEVEL_ERROR, R_LOG_ORIGIN)) {r_log_message (R_LOG_LEVEL_ERROR, R_LOG_ORIGIN, __FILE__, __LINE__, f, ##__VA_ARGS__);}

#define HAVE_PTRACE 1

#if HAVE_PTRACE
typedef long r_ptrace_request_t;
typedef void * r_ptrace_data_t;
#define R_PTRACE_NODATA NULL
#endif

typedef struct r_list_t RList;
typedef struct r_event_t REvent;
typedef struct sdb_list_t SdbList;
typedef struct r_pvector_t RPVector;
typedef struct r_rbtree_t RRBTree;
typedef struct r_rbnode_t RRBNode;
typedef struct r_queue_t RQueue;
typedef struct ht_up_t HtUP;
typedef struct ht_su_t HtSU;
typedef struct r_cons_t RCons;
typedef bool (*RConsIsBreaked)(RCons *cons);
typedef struct r_bin_t RBin;
typedef struct r_bin_object_t RBinObject;
typedef struct r_bin_xtr_plugin_t RBinXtrPlugin;
typedef struct r_bin_plugin_t RBinPlugin;
typedef struct r_bin_file_options_t RBinFileOptions;
typedef struct r_itv_t RInterval;
typedef struct r_plugin_meta_t RPluginMeta;
typedef struct r_buf_t RBuffer;
typedef struct r_bin_file_t RBinFile;

typedef void (*RListFree)(void *ptr);

struct r_itv_t {
	ut64 addr;
	ut64 size;
};

struct r_plugin_meta_t {
	const char *name;
	const char *desc;
	const char *author;
	const char *version;
	const char *license;
};

typedef struct r_list_iter_t {
	void *data;
	struct r_list_iter_t *next, *prev;
} RListIter;

struct r_list_t {
	RListIter *head;
	RListIter *tail;
	RListFree free;
	int length;
};

struct r_vector_t {
	void *a;
	size_t len;
	size_t capacity;
	size_t elem_size;
	void *elem_free;
};

struct r_vec_r_bin_symbol_t {
	void *a;
	size_t len;
	size_t capacity;
	size_t elem_size;
	void *elem_free;
};

typedef void *(*RConsNew)(void);
typedef void (*RConsFree)(void *);
typedef char *(*RConsReadline)(const char *);
typedef void *(*RConsSleepBegin)(void);
typedef void (*RConsSleepEnd)(void *);
typedef bool (*RConsIsBreakedFn)(void *);

struct r_cons_bind_t {
	RConsNew cons_new;
	RConsFree cons_free;
	RConsReadline readline;
	RConsSleepBegin sleep_begin;
	RConsSleepEnd sleep_end;
	RConsIsBreakedFn is_breaked;
	RCons *cons;
};
typedef struct r_cons_bind_t RConsBind;

typedef int (*RCoreCmd)(void *core, const char *cmd);
typedef int (*RCoreCmdf)(void *core, const char *fmt, ...);

struct r_core_bind_t {
	void *core;
	RCoreCmd cmd;
	RCoreCmdf cmdf;
};
typedef struct r_core_bind_t RCoreBind;

typedef struct r_io_plugin_t RIOPlugin;

typedef struct r_io_desc_t {
	int fd;
	int perm;
	char *uri;
	char *name;
	char *referer;
	HtUP *cache;
	void *data;
	RIOPlugin *plugin;
	struct r_io_t *io;
} RIODesc;

typedef struct r_io_t RIO;
typedef struct r_io_map_t RIOMap;
typedef struct r_io_bank_t RIOBank;

typedef bool (*RIODescUse)(RIO *io, int fd);
typedef RIODesc *(*RIODescGet)(RIO *io, int fd);
typedef ut64(*RIODescSize)(RIODesc *desc);
typedef RIODesc *(*RIOOpen)(RIO *io, const char *uri, int flags, int mode);
typedef RIODesc *(*RIOOpenAt)(RIO *io, const  char *uri, int flags, int mode, ut64 at);
typedef bool (*RIOClose)(RIO *io, int fd);
typedef bool (*RIOReadAt)(RIO *io, ut64 addr, ut8 *buf, int len);
typedef bool (*RIOWriteAt)(RIO *io, ut64 addr, const ut8 *buf, int len);
typedef bool (*RIOOverlayWriteAt)(RIO *io, ut64 addr, const ut8 *buf, int len);
typedef char *(*RIOSystem)(RIO *io, const char* cmd);
typedef int (*RIOFdOpen)(RIO *io, const char *uri, int flags, int mode);
typedef bool (*RIOFdClose)(RIO *io, int fd);
typedef ut64 (*RIOFdSeek)(RIO *io, int fd, ut64 addr, int whence);
typedef ut64 (*RIOFdSize)(RIO *io, int fd);
typedef bool (*RIOFdResize)(RIO *io, int fd, ut64 newsize);
typedef bool (*RIOP2V)(RIO *io, ut64 p, ut64 *v);
typedef ut64 (*RIOV2P)(RIO *io, ut64 va);
typedef int (*RIOFdRead)(RIO *io, int fd, ut8 *buf, int len);
typedef int (*RIOFdWrite)(RIO *io, int fd, const ut8 *buf, int len);
typedef int (*RIOFdReadAt)(RIO *io, int fd, ut64 addr, ut8 *buf, int len);
typedef int (*RIOFdWriteAt)(RIO *io, int fd, ut64 addr, const ut8 *buf, int len);
typedef bool (*RIOFdIsDbg)(RIO *io, int fd);
typedef const char *(*RIOFdGetName)(RIO *io, int fd);
typedef RList *(*RIOFdGetMap)(RIO *io, int fd);
typedef bool (*RIOFdRemap)(RIO *io, int fd, ut64 addr);
typedef bool (*RIOIsValidOff)(RIO *io, ut64 addr, int hasperm);
typedef RIOBank *(*RIOBankGet)(RIO *io, ut32 bankid);
typedef bool (*RIOBankUse)(RIO *io, ut32 bankid);
typedef RIOMap *(*RIOMapGet)(RIO *io, ut32 id);
typedef RIOMap *(*RIOMapGetAt)(RIO *io, ut64 addr);
typedef RIOMap *(*RIOMapGetPaddr)(RIO *io, ut64 paddr);
typedef bool (*RIOAddrIsMapped)(RIO *io, ut64 addr);
typedef RIOMap *(*RIOMapAdd)(RIO *io, int fd, int flags, ut64 delta, ut64 addr, ut64 size);
#if HAVE_PTRACE
typedef long (*RIOPtraceFn)(RIO *io, r_ptrace_request_t request, int pid, void *addr, r_ptrace_data_t data);
typedef void *(*RIOPtraceFuncFn)(RIO *io, void *(*func)(void *), void *user);
#endif

typedef struct r_id_pool_t {
	ut32 start_id;
	ut32 last_id;
	ut32 next_id;
	RQueue *freed_ids;
} RIDPool;

typedef struct r_id_storage_t {
	RIDPool *pool;
	void **data;
	ut32 top_id;
	ut32 size;
} RIDStorage;

typedef struct r_buf_methods_t RBufferMethods;
typedef enum r_buf_type_t {
	R_BUF_MMAP, R_BUF_BYTES, R_BUF_FILE, R_BUF_IO, R_BUF_SPARSE, R_BUF_REF, R_BUF_CACHE
} RBufferType;

typedef struct r_buf_ref_t {
	struct r_buf_t *buf;
	ut64 offset;
	ut64 size;
} RBufferRef;

struct r_buf_t {
	const RBufferMethods *methods;
	union {
		RBufferRef *rb_ref;
	};
	ut8 *whole_buf;
	bool readonly;
	ut8 Oxff_priv;
	int refctr;
	RBufferType type;
};

struct r_io_t {
	RIODesc *desc;
	ut64 off;
	ut32 bank;
	int bits;
	int va;
	bool ff;
	ut8 Oxff;
	size_t addrbytes;
	bool autofd;
	bool overlay;
	bool cachemode;
	ut32 p_cache;
	ut64 mts;
	RIDStorage files;
	RIDStorage maps;
	RIDStorage banks;
	void *cache;
	ut8 *write_mask;
	int write_mask_len;
	ut64 mask;
	void *undo;
	SdbList *plugins;
	bool nodup;
	char *runprofile;
	char *envprofile;
	char *args;
	REvent *event;
	PrintfCallback cb_printf;
	RCoreBind coreb;
	bool want_ptrace_wrap;
};

struct r_io_bind_t {
	int init;
	RIO *io;
	RIODescUse desc_use;
	RIODescGet desc_get;
	RIODescSize desc_size;
	RIOOpen open;
	RIOOpenAt open_at;
	RIOClose close;
	RIOReadAt read_at;
	RIOWriteAt write_at;
	RIOOverlayWriteAt overlay_write_at;
	RIOSystem system;
	RIOFdOpen fd_open;
	RIOFdClose fd_close;
	RIOFdSeek fd_seek;
	RIOFdSize fd_size;
	RIOFdResize fd_resize;
	RIOFdRead fd_read;
	RIOFdWrite fd_write;
	RIOFdReadAt fd_read_at;
	RIOFdWriteAt fd_write_at;
	RIOFdIsDbg fd_is_dbg;
	RIOFdGetName fd_get_name;
	RIOFdGetMap fd_get_map;
	RIOFdRemap fd_remap;
	RIOIsValidOff is_valid_offset;
	RIOAddrIsMapped addr_is_mapped;
	RIOBankGet bank_get;
	RIOBankUse bank_use;
	RIOMapGet map_get;
	RIOMapGetAt map_get_at;
	RIOMapGetPaddr map_get_paddr;
	RIOMapAdd map_add;
	RIOV2P v2p;
	RIOP2V p2v;
#if HAVE_PTRACE
	RIOPtraceFn ptrace;
	RIOPtraceFuncFn ptrace_func;
#endif
};

typedef struct r_io_bind_t RIOBind;

struct r_io_plugin_t {
	RPluginMeta meta;
	void *data;
	const char *uris;
	int (*listener)(RIODesc *io);
	bool isdbg;
	char *(*system)(RIO *io, RIODesc *fd, const char *);
	RIODesc* (*open)(RIO *io, const char *, int perm, int mode);
	void *open_many;
	int (*read)(RIO *io, RIODesc *fd, ut8 *buf, int count);
	ut64 (*seek)(RIO *io, RIODesc *fd, ut64 offset, int whence);
	int (*write)(RIO *io, RIODesc *fd, const ut8 *buf, int count);
	bool (*close)(RIODesc *desc);
	bool (*is_blockdevice)(RIODesc *desc);
	bool (*is_chardevice)(RIODesc *desc);
	int (*getpid)(RIODesc *desc);
	int (*gettid)(RIODesc *desc);
	bool (*getbase)(RIODesc *desc, ut64 *base);
	bool (*resize)(RIO *io, RIODesc *fd, ut64 size);
	bool (*extend)(RIO *io, RIODesc *fd, ut64 size);
	bool (*accept)(RIO *io, RIODesc *desc, int fd);
	int (*create)(RIO *io, const char *file, int mode, int type);
	bool (*check)(RIO *io, const char *, bool many);
};

struct r_bin_file_t {
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
	RBinXtrPlugin *curxtr;
	RList *xtr_data;
	void *sdb;
	void *sdb_info;
	void *sdb_addrinfo;
	void *addrline;
	void *addrinfo_priv;
	struct r_bin_t *rbin;
	int string_count;
	RBinFileOptions *options;
};

struct r_bin_object_t {
	void *bin_obj;
	struct r_vec_r_bin_symbol_t symbols_vec;
};

struct r_bin_t {
	RIOBind iob;
	RConsBind consb;
	void *cb_printf;
	void *options;
};

typedef struct {
	char magic[16];
	ut32 mappingOffset;
	ut32 mappingCount;
	ut32 imagesOffset;
	ut32 imagesCount;
	ut64 dyldBaseAddress;
	ut64 codeSignatureOffset;
	ut64 codeSignatureSize;
	ut64 slideInfoOffset;
	ut64 slideInfoSize;
	ut64 localSymbolsOffset;
	ut64 localSymbolsSize;
	ut8 uuid[16];
	ut64 cacheType;
	ut64 branchPoolsOffset;
	ut64 branchPoolsCount;
	ut64 accelerateInfoAddr;
	ut64 accelerateInfoSize;
	ut64 imagesTextOffset;
	ut64 imagesTextCount;
} cache_hdr_t;

typedef struct {
	ut64 address;
	ut64 size;
	ut64 fileOffset;
	int initProt;
	int maxProt;
} cache_map_t;

typedef struct {
	ut32 version;
	ut32 imageExtrasCount;
	ut32 imagesExtrasOffset;
	ut32 bottomUpListOffset;
	ut32 dylibTrieOffset;
	ut32 dylibTrieSize;
	ut32 initializersOffset;
	ut32 initializersCount;
	ut32 dofSectionsOffset;
	ut32 dofSectionsCount;
	ut32 reExportListOffset;
	ut32 reExportCount;
	ut32 depListOffset;
	ut32 depListCount;
	ut32 rangeTableOffset;
	ut32 rangeTableCount;
	ut64 dyldSectionAddr;
} cache_accel_t;

typedef struct {
	ut64 local_symbols_offset;
	ut64 nlists_offset;
	ut64 nlists_count;
	ut64 strings_offset;
	ut64 strings_size;
} RDyldLocSym;

typedef struct objc_cache_opt_info objc_cache_opt_info;

typedef struct _r_dyldcache {
	cache_hdr_t *hdr;
	ut64 *hdr_offset;
	ut64 *hdr_overhead;
	ut32 *maps_index;
	ut64 *maps_flags;
	ut32 n_hdr;
	cache_map_t *maps;
	ut32 n_maps;
	RList *bins;
	HtUP *bin_by_pa;
	RBuffer *buf;
	int (*original_io_read)(RIO *io, RIODesc *fd, ut8 *buf, int count);
	cache_accel_t *accel;
	RDyldLocSym *locsym;
	objc_cache_opt_info *oi;
	bool objc_opt_info_loaded;
	bool images_are_global;
} RDyldCache;

R_API bool r_io_use_fd(RIO *io, int fd);
R_API RIODesc *r_io_desc_get(RIO *io, int fd);
R_API ut64 r_io_desc_size(RIODesc *desc);
R_API bool r_io_p2v(RIO *io, ut64 p, ut64 *v);
R_API ut64 r_io_v2p(RIO *io, ut64 va);
R_API RIODesc *r_io_open_nomap(RIO *io, const char *uri, int flags, int mode);
R_API RIODesc *r_io_open_at(RIO *io, const char *uri, int flags, int mode, ut64 at);
R_API bool r_io_fd_close(RIO *io, int fd);
R_API bool r_io_read_at(RIO *io, ut64 addr, ut8 *buf, int len);
R_API bool r_io_write_at(RIO *io, ut64 addr, const ut8 *buf, int len);
R_API bool r_io_vwrite_to_overlay_at(RIO *io, ut64 caddr, const ut8 *buf, int len);
R_API char *r_io_system(RIO *io, const char* cmd);
R_API int r_io_fd_open(RIO *io, const char *uri, int flags, int mode);
R_API ut64 r_io_fd_seek(RIO *io, int fd, ut64 addr, int whence);
R_API ut64 r_io_fd_size(RIO *io, int fd);
R_API bool r_io_fd_resize(RIO *io, int fd, ut64 newsize);
R_API int r_io_fd_read(RIO *io, int fd, ut8 *buf, int len);
R_API int r_io_fd_write(RIO *io, int fd, const ut8 *buf, int len);
R_API int r_io_fd_read_at(RIO *io, int fd, ut64 addr, ut8 *buf, int len);
R_API int r_io_fd_write_at(RIO *io, int fd, ut64 addr, const ut8 *buf, int len);
R_API bool r_io_fd_is_dbg(RIO *io, int fd);
R_API const char *r_io_fd_get_name(RIO *io, int fd);
R_API RList *r_io_map_get_by_fd(RIO *io, int fd);
R_API bool r_io_map_remap_fd(RIO *io, int fd, ut64 addr);
R_API bool r_io_is_valid_offset(RIO *io, ut64 offset, int hasperm);
R_API RIOBank *r_io_bank_get(RIO *io, const ut32 bankid);
R_API bool r_io_bank_use(RIO *io, ut32 bankid);
R_API RIOMap *r_io_map_get(RIO *io, ut32 id);
R_API RIOMap *r_io_map_get_at(RIO *io, ut64 vaddr);
R_API RIOMap *r_io_map_get_paddr(RIO *io, ut64 paddr);
R_API bool r_io_addr_is_mapped(RIO *io, ut64 vaddr);
R_API RIOMap *r_io_map_add(RIO *io, int fd, int flags, ut64 delta, ut64 addr, ut64 size);
R_API void r_io_bind(RIO *io, RIOBind *bnd);
#if HAVE_PTRACE
R_API long r_io_ptrace(RIO *io, r_ptrace_request_t request, int pid, void *addr, r_ptrace_data_t data);
R_API void *r_io_ptrace_func(RIO *io, void *(*func)(void *), void *user);
#endif

R_API RBuffer *r_buf_ref(RBuffer *b);

static void populate_cache_headers(RDyldCache *cache);
static void populate_cache_maps(RDyldCache *cache);
static cache_accel_t *read_cache_accel(RBuffer *cache_buf, cache_hdr_t *hdr, cache_map_t *maps, int n_maps);
static void create_cache_bins(RBinFile *bf, RDyldCache *cache);
static RDyldLocSym *r_dyld_locsym_new(RDyldCache *cache);
static void r_dyldcache_free(RDyldCache *cache);

R_API void* r_id_storage_get(RIDStorage* storage, ut32 id) {
	R_RETURN_VAL_IF_FAIL (storage, false);
	if (id < storage->size) {
		return storage->data[id];
	}
	return NULL;
}

R_API RIODesc* r_io_desc_get(RIO* io, int fd) {
	R_RETURN_VAL_IF_FAIL (io, NULL);
	return (RIODesc *)r_id_storage_get (&io->files, fd);
}

R_API void r_io_bind(RIO *io, RIOBind *bnd) {
	R_RETURN_IF_FAIL (io && bnd);

	bnd->io = io;
	bnd->init = true;
	bnd->desc_use = r_io_use_fd;
	bnd->desc_get = r_io_desc_get;
	bnd->desc_size = r_io_desc_size;
	bnd->p2v = r_io_p2v;
	bnd->v2p = r_io_v2p;
	bnd->open = r_io_open_nomap;
	bnd->open_at = r_io_open_at;
	bnd->close = r_io_fd_close;
	bnd->read_at = r_io_read_at;
	bnd->write_at = r_io_write_at;
	bnd->overlay_write_at = r_io_vwrite_to_overlay_at;
	bnd->system = r_io_system;
	bnd->fd_open = r_io_fd_open;
	bnd->fd_close = r_io_fd_close;
	bnd->fd_seek = r_io_fd_seek;
	bnd->fd_size = r_io_fd_size;
	bnd->fd_resize = r_io_fd_resize;
	bnd->fd_read = r_io_fd_read;
	bnd->fd_write = r_io_fd_write;
	bnd->fd_read_at = r_io_fd_read_at;
	bnd->fd_write_at = r_io_fd_write_at;
	bnd->fd_is_dbg = r_io_fd_is_dbg;
	bnd->fd_get_name = r_io_fd_get_name;
	bnd->fd_get_map = r_io_map_get_by_fd;
	bnd->fd_remap = r_io_map_remap_fd;
	bnd->is_valid_offset = r_io_is_valid_offset;
	bnd->bank_get = r_io_bank_get;
	bnd->bank_use = r_io_bank_use;
	bnd->map_get = r_io_map_get;
	bnd->map_get_at = r_io_map_get_at;
	bnd->map_get_paddr = r_io_map_get_paddr;
	bnd->addr_is_mapped = r_io_addr_is_mapped;
	bnd->map_add = r_io_map_add;
#if HAVE_PTRACE
	bnd->ptrace = r_io_ptrace;
	bnd->ptrace_func = r_io_ptrace_func;
#endif
}

static bool load(RBinFile *bf, RBuffer *buf, ut64 loadaddr) {
	if (!bf || !bf->rbin || !bf->rbin->iob.desc_get) {
		return false;
	}
	const char * io_plugin_name = bf->rbin->iob.desc_get (bf->rbin->iob.io, bf->fd)->plugin->meta.name;
	if (strcmp (io_plugin_name, "dsc") != 0) {
		R_LOG_ERROR ("Use dsc:// for dyld caches");
		return false;
	}

	RDyldCache *cache = R_NEW0 (RDyldCache);
	if (!cache) {
		return false;
	}
	cache->buf = r_buf_ref (buf);
	populate_cache_headers (cache);
	if (!cache->hdr) {
		r_dyldcache_free (cache);
		return false;
	}
	populate_cache_maps (cache);
	if (!cache->maps) {
		r_dyldcache_free (cache);
		return false;
	}
	cache->accel = read_cache_accel (cache->buf, cache->hdr, cache->maps, cache->n_maps);
	create_cache_bins (bf, cache);
	if (!cache->bins) {
		r_dyldcache_free (cache);
		return false;
	}
	cache->locsym = r_dyld_locsym_new (cache);
	bf->bo->bin_obj = cache;
	return true;
}
