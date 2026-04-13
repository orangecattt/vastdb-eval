#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>

#define AV_HAVE_BIGENDIAN 0

#define av_cold
#define av_alloc_size(...)
#define av_malloc_attrib
#define av_always_inline inline
#define av_restrict restrict
#define av_unused __attribute__((unused))
#define av_const const
#define av_clip(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
#define av_printf_format(fmtp, first) __attribute__((format(printf, fmtp, first)))

#define AV_ERROR_MAX_STRING_SIZE 64
#define AVERROR_INVALIDDATA (-1094995529)
#define AVERROR_EOF (-541478725)
#define AVERROR_EAGAIN (-11)
#define AVERROR_ENOMEM (-12)

#define FFMIN(a,b) ((a) < (b) ? (a) : (b))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

typedef union {
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8 [8];
    double   f64;
    float    f32[2];
} av_alias64;

typedef union {
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8 [4];
    float    f32;
} av_alias32;

typedef union {
    uint16_t u16;
    uint8_t  u8 [2];
} av_alias16;

#if AV_HAVE_BIGENDIAN
#   define AV_RL16(p) av_bswap16(*(const uint16_t*)(p))
#   define AV_RL32(p) av_bswap32(*(const uint32_t*)(p))
#   define AV_RL64(p) av_bswap64(*(const uint64_t*)(p))
#else
#   define AV_RL16(p) (*(const uint16_t*)(p))
#   define AV_RL32(p) (*(const uint32_t*)(p))
#   define AV_RL64(p) (*(const uint64_t*)(p))
#endif

#define AV_RN16(p) AV_RL16(p)
#define AV_RN32(p) AV_RL32(p)
#define AV_RN64(p) AV_RL64(p)

static inline uint16_t av_bswap16(uint16_t x) {
    return (x >> 8) | ((x & 0xff) << 8);
}

static inline uint32_t av_bswap32(uint32_t x) {
    return (av_bswap16(x & 0xffff) << 16) | av_bswap16(x >> 16);
}

static inline uint64_t av_bswap64(uint64_t x) {
    return ((uint64_t)av_bswap32(x & 0xffffffff) << 32) | av_bswap32(x >> 32);
}

typedef struct AVClass {
    const char* class_name;
    const char* (*item_name)(void*);
} AVClass;

#define AV_LOG_QUIET    -8
#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48

#define av_log(a, b, c, ...) do { fprintf(stderr, c, ##__VA_ARGS__); } while(0)

#define av_free(p) free(p)
#define av_freep(p) do { free(*(p)); *(p) = NULL; } while(0)

static inline void *av_malloc_impl(size_t size) {
    void *ptr = malloc(size);
    return ptr;
}

static inline void *av_mallocz_impl(size_t size) {
    void *ptr = calloc(1, size);
    return ptr;
}

static inline void *av_malloc_array_impl(size_t nmemb, size_t size) {
    if (nmemb <= 0 || size <= 0 || nmemb > INT_MAX / size)
        return NULL;
    return av_malloc_impl(nmemb * size);
}

#define av_malloc(size) av_malloc_impl(size)
#define av_mallocz(size) av_mallocz_impl(size)
#define av_malloc_array(nmemb, size) av_malloc_array_impl(nmemb, size)

typedef int64_t time_t_compat;

#define LIBAVFORMAT_VERSION_MAJOR 59
#define LIBAVFORMAT_VERSION_MINOR 27
#define LIBAVFORMAT_VERSION_MICRO 100

#define AV_TIME_BASE            1000000
#define AV_NOPTS_VALUE          ((int64_t)UINT64_C(0x8000000000000000))

#define AVSEEK_SIZE 0x10000
#define AVSEEK_FORCE 0x20000

#define AVFMTCTX_NOHEADER      0x0001
#define AVFMTCTX_UNSEEKABLE    0x0002

#define AVINDEX_KEYFRAME 0x0001
#define AVINDEX_DISCARD_FRAME  0x0002

typedef enum AVIODataMarkerType {
    AVIO_DATA_MARKER_HEADER,
    AVIO_DATA_MARKER_SYNC_POINT,
    AVIO_DATA_MARKER_BOUNDARY_POINT,
    AVIO_DATA_MARKER_UNKNOWN,
    AVIO_DATA_MARKER_TRAILER,
    AVIO_DATA_MARKER_FLUSH_POINT,
} AVIODataMarkerType;

typedef struct AVIOContext {
    const AVClass *av_class;
    unsigned char *buffer;
    int buffer_size;
    unsigned char *buf_ptr;
    unsigned char *buf_end;
    void *opaque;
    int (*read_packet)(void *opaque, uint8_t *buf, int buf_size);
    int (*write_packet)(void *opaque, uint8_t *buf, int buf_size);
    int64_t (*seek)(void *opaque, int64_t offset, int whence);
    int64_t pos;
    int eof_reached;
    int write_flag;
    int max_packet_size;
    unsigned long checksum;
    unsigned char *checksum_ptr;
    unsigned long (*update_checksum)(unsigned long checksum, const uint8_t *buf, unsigned int size);
    int error;
    int (*read_pause)(void *opaque, int pause);
    int64_t (*read_seek)(void *opaque, int stream_index, int64_t timestamp, int flags);
    int seekable;
    int64_t maxsize;
    int direct;
    int64_t bytes_read;
    int seek_count;
    int writeout_count;
    int orig_buffer_size;
    int short_seek_threshold;
    const char *protocol_whitelist;
    const char *protocol_blacklist;
    int (*write_data_type)(void *opaque, uint8_t *buf, int buf_size, int type, int64_t time);
    int ignore_boundary_point;
    enum AVIODataMarkerType current_type;
    int64_t last_time;
    int (*short_seek_get)(void *opaque);
    int64_t written;
    unsigned char *buf_ptr_max;
    int min_packet_size;
} AVIOContext;

typedef struct AVIndexEntry {
    int64_t pos;
    int64_t timestamp;
    int size;
    int distance;
    int flags;
} AVIndexEntry;

typedef enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
} AVMediaType;

typedef struct AVStream {
    int index;
    int id;
    char *codecpar;
    void *internal;
    int64_t time_base_num;
    int64_t time_base_den;
    int64_t start_time;
    int64_t duration;
    int64_t nb_frames;
    int discard;
    char codec_name[32];
    enum AVMediaType codec_type;
    AVIndexEntry *index_entries;
    int nb_index_entries;
    unsigned int index_entries_allocated_size;
} AVStream;

typedef struct AVFormatInternal {
    int nb_interleaved_streams;
    void *packet_buffer;
    void *packet_buffer_end;
    int64_t data_offset;
    void *raw_packet_buffer;
    void *raw_packet_buffer_end;
    void *parse_queue;
    void *parse_queue_end;
    int raw_packet_buffer_remaining_size;
} AVFormatInternal;

typedef struct AVFormatContext {
    const AVClass *av_class;
    struct AVInputFormat *iformat;
    struct AVOutputFormat *oformat;
    AVIOContext *pb;
    AVStream **streams;
    unsigned int nb_streams;
    int ctx_flags;
    unsigned char *priv_data;
    struct AVFormatInternal *internal;
} AVFormatContext;

typedef struct AVPacket {
    int64_t pts;
    int64_t dts;
    int64_t pos;
    int size;
    int stream_index;
    int flags;
    int64_t duration;
} AVPacket;

AVIOContext *avio_alloc_context(
                  unsigned char *buffer,
                  int buffer_size,
                  int write_flag,
                  void *opaque,
                  int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int64_t (*seek)(void *opaque, int64_t offset, int whence));

void avio_context_free(AVIOContext **s);
int64_t avio_seek(AVIOContext *s, int64_t offset, int whence);
int64_t avio_skip(AVIOContext *s, int64_t offset);
int64_t avio_tell(AVIOContext *s);
int64_t avio_size(AVIOContext *s);
int avio_feof(AVIOContext *s);
int avio_read(AVIOContext *s, unsigned char *buf, int size);
unsigned int avio_rl16(AVIOContext *s);
unsigned int avio_rl32(AVIOContext *s);
uint64_t avio_rl64(AVIOContext *s);
void avio_wl64(AVIOContext *s, uint64_t val);
void avio_wl32(AVIOContext *s, unsigned int val);
void avio_wl16(AVIOContext *s, unsigned int val);
int avio_printf(AVIOContext *s, const char *fmt, ...);
void avio_flush(AVIOContext *s);
int avio_close(AVIOContext *s);

#define WTV_SECTOR_BITS    12
#define WTV_SECTOR_SIZE    (1 << WTV_SECTOR_BITS)
#define WTV_BIGSECTOR_BITS 18
#define WTV_PAD8(x) (((x) + 7) & ~7)

int ff_add_index_entry(AVIndexEntry **index_entries,
                       int *nb_index_entries,
                       unsigned int *index_entries_allocated_size,
                       int64_t pos, int64_t timestamp,
                       int size, int distance, int flags);

typedef uint8_t ff_asf_guid[16];

#define FF_PRI_GUID \
    "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x " \
    "{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}"

#define FF_ARG_GUID(g) \
    g[0], g[1], g[2],  g[3],  g[4],  g[5],  g[6],  g[7], \
    g[8], g[9], g[10], g[11], g[12], g[13], g[14], g[15],\
    g[3], g[2], g[1],  g[0],  g[5],  g[4],  g[7],  g[6], \
    g[9], g[8], g[11], g[10], g[13], g[12], g[15], g[14]

#define PRI_PRETTY_GUID \
    "%08"PRIx32"-%04"PRIx16"-%04"PRIx16"-%02x%02x%02x%02x%02x%02x%02x%02x"

#define ARG_PRETTY_GUID(g) \
    AV_RL32(g),AV_RL16(g+4),AV_RL16(g+6),g[8],g[9],g[10],g[11],g[12],g[13],g[14],g[15]

#define LEN_PRETTY_GUID 34

static inline int ff_guidcmp(const void *g1, const void *g2)
{
    return memcmp(g1, g2, sizeof(ff_asf_guid));
}

#define WTV_SECTOR_BITS    12
#define WTV_SECTOR_SIZE    (1 << WTV_SECTOR_BITS)
#define WTV_BIGSECTOR_BITS 18
#define WTV_PAD8(x) (((x) + 7) & ~7)

extern const uint8_t ff_timeline_le16[];
extern const uint8_t ff_timeline_table_0_entries_Events_le16[];
extern const uint8_t ff_table_0_entries_legacy_attrib_le16[];
extern const uint8_t ff_table_0_entries_time_le16[];

extern const ff_asf_guid ff_dir_entry_guid;
extern const ff_asf_guid ff_wtv_guid;

int ffio_init_context(AVIOContext *s,
                  unsigned char *buffer,
                  int buffer_size,
                  int write_flag,
                  void *opaque,
                  int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int64_t (*seek)(void *opaque, int64_t offset, int whence));

const ff_asf_guid ff_dir_entry_guid =
    {0x92,0xB7,0x74,0x91,0x59,0x70,0x70,0x44,0x88,0xDF,0x06,0x3B,0x82,0xCC,0x21,0x3D};
const ff_asf_guid ff_wtv_guid =
    {0xB7,0xD8,0x00,0x20,0x37,0x49,0xDA,0x11,0xA6,0x4E,0x00,0x07,0xE9,0x5E,0xAD,0x8D};

const uint8_t ff_timeline_le16[] =
    {'t','i','m','e','l','i','n','e', 0};
const uint8_t ff_timeline_table_0_entries_Events_le16[] =
    {'t','i','m','e','l','i','n','e','.','t','a','b','l','e','.','0','.','e','n','t','r','i','e','s','.','E','v','e','n','t','s', 0};
const uint8_t ff_table_0_entries_legacy_attrib_le16[] =
    {'t','a','b','l','e','.','0','.','e','n','t','r','i','e','s','.','l','e','g','a','c','y','_','a','t','t','r','i','b', 0};
const uint8_t ff_table_0_entries_time_le16[] =
    {'t','a','b','l','e','.','0','.','e','n','t','r','i','e','s','.','t','i','m','e', 0};

typedef struct WtvFile {
    AVIOContext *pb_filesystem;
    int sector_bits;
    uint32_t *sectors;
    int nb_sectors;
    int error;
    int64_t position;
    int64_t length;
} WtvFile;

typedef struct WtvContext {
    AVIOContext *pb;
    int64_t epoch;
    int64_t pts;
    int64_t last_valid_pts;
    AVIndexEntry *index_entries;
    int nb_index_entries;
    unsigned int index_entries_allocated_size;
} WtvContext;

static inline int64_t avio_tell_impl(AVIOContext *s);
static inline unsigned int avio_rl16_impl(AVIOContext *s);
static inline unsigned int avio_rl32_impl(AVIOContext *s);
static inline uint64_t avio_rl64_impl(AVIOContext *s);
static inline int avio_read_impl(AVIOContext *s, unsigned char *buf, int size);
static inline int avio_feof_impl(AVIOContext *s);
static inline int64_t avio_seek_impl(AVIOContext *s, int64_t offset, int whence);
static inline int64_t avio_skip_impl(AVIOContext *s, int64_t offset);
static inline int64_t avio_size_impl(AVIOContext *s);
static inline void avio_close_impl(AVIOContext **s);

int64_t seek_by_sector(AVIOContext *pb, int64_t sector, int64_t offset);

static int read_ints(AVIOContext *pb, uint32_t *data, int count)
{
    int i, total = 0;
    for (i = 0; i < count; i++) {
        if ((data[total] = avio_rl32(pb)))
           total++;
    }
    return total;
}

static int wtvfile_read_packet(void *opaque, uint8_t *buf, int buf_size)
{
    WtvFile *wf = opaque;
    AVIOContext *pb = wf->pb_filesystem;
    int nread = 0;

    if (wf->error || pb->error)
        return -1;
    if (wf->position >= wf->length || avio_feof(pb))
        return -1;

    buf_size = FFMIN(buf_size, wf->length - wf->position);
    while(nread < buf_size) {
        int n;
        int remaining_in_sector = (1 << wf->sector_bits) - (wf->position & ((1 << wf->sector_bits) - 1));
        int read_request        = FFMIN(buf_size - nread, remaining_in_sector);

        n = avio_read(pb, buf, read_request);
        if (n <= 0)
            break;
        nread += n;
        buf += n;
        wf->position += n;
        if (n == remaining_in_sector) {
            int i = wf->position >> wf->sector_bits;
            if (i >= wf->nb_sectors ||
                (wf->sectors[i] != wf->sectors[i - 1] + (1 << (wf->sector_bits - WTV_SECTOR_BITS)) &&
                seek_by_sector(pb, wf->sectors[i], 0) < 0)) {
                wf->error = 1;
                break;
            }
        }
    }
    return nread;
}

static int64_t wtvfile_seek(void *opaque, int64_t offset, int whence)
{
    WtvFile *wf = opaque;
    AVIOContext *pb = wf->pb_filesystem;

    if (whence == AVSEEK_SIZE)
        return wf->length;
    else if (whence == SEEK_CUR)
        offset = wf->position + offset;
    else if (whence == SEEK_END)
        offset = wf->length;

    wf->error = offset < 0 || offset >= wf->length ||
                seek_by_sector(pb, wf->sectors[offset >> wf->sector_bits],
                               offset & ((1 << wf->sector_bits) - 1)) < 0;
    wf->position = offset;
    return offset;
}

static void wtvfile_close(AVIOContext *pb)
{
    WtvFile *wf = pb->opaque;
    av_freep(&wf->sectors);
    av_freep(&pb->opaque);
    av_freep(&pb->buffer);
    avio_context_free(&pb);
}

int ffio_init_context(AVIOContext *s,
                  unsigned char *buffer,
                  int buffer_size,
                  int write_flag,
                  void *opaque,
                  int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int64_t (*seek)(void *opaque, int64_t offset, int whence))
{
    memset(s, 0, sizeof(*s));
    s->buffer = buffer;
    s->buffer_size = buffer_size;
    s->buf_ptr = buffer;
    s->buf_end = buffer + buffer_size;
    s->write_flag = write_flag;
    s->opaque = opaque;
    s->read_packet = read_packet;
    s->write_packet = write_packet;
    s->seek = seek;
    return 0;
}

void avio_context_free(AVIOContext **s);

AVIOContext *avio_alloc_context(
                  unsigned char *buffer,
                  int buffer_size,
                  int write_flag,
                  void *opaque,
                  int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int64_t (*seek)(void *opaque, int64_t offset, int whence))
{
    AVIOContext *s = av_malloc(sizeof(AVIOContext));
    if (!s)
        return NULL;
    ffio_init_context(s, buffer, buffer_size, write_flag, opaque,
                  read_packet, write_packet, seek);
    return s;
}

int ff_add_index_entry(AVIndexEntry **index_entries,
                       int *nb_index_entries,
                       unsigned int *index_entries_allocated_size,
                       int64_t pos, int64_t timestamp,
                       int size, int distance, int flags)
{
    AVIndexEntry *entries;
    size_t size_needed;

    size_needed = (*nb_index_entries + 1) * sizeof(AVIndexEntry);
    if (*index_entries_allocated_size < size_needed) {
        size_t new_size = FFMAX(size_needed, 2 * *index_entries_allocated_size);
        entries = realloc(*index_entries, new_size);
        if (!entries)
            return -1;
        *index_entries = entries;
        *index_entries_allocated_size = new_size;
    }

    entries = *index_entries;
    entries[(*nb_index_entries)].pos = pos;
    entries[(*nb_index_entries)].timestamp = timestamp;
    entries[(*nb_index_entries)].size = size;
    entries[(*nb_index_entries)].distance = distance;
    entries[(*nb_index_entries)].flags = flags;
    (*nb_index_entries)++;

    return 0;
}

static AVIOContext * wtvfile_open_sector(unsigned first_sector, uint64_t length, int depth, AVFormatContext *s)
{
    AVIOContext *pb;
    WtvFile *wf;
    uint8_t *buffer;
    int64_t size;

    if (seek_by_sector(s->pb, first_sector, 0) < 0)
        return NULL;

    wf = av_mallocz(sizeof(WtvFile));
    if (!wf)
        return NULL;

    if (depth == 0) {
        wf->sectors = av_malloc(sizeof(uint32_t));
        if (!wf->sectors) {
            av_free(wf);
            return NULL;
        }
        wf->sectors[0]  = first_sector;
        wf->nb_sectors  = 1;
    } else if (depth == 1) {
        wf->sectors = av_malloc(WTV_SECTOR_SIZE);
        if (!wf->sectors) {
            av_free(wf);
            return NULL;
        }
        wf->nb_sectors  = read_ints(s->pb, wf->sectors, WTV_SECTOR_SIZE / 4);
    } else if (depth == 2) {
        uint32_t sectors1[WTV_SECTOR_SIZE / 4];
        int nb_sectors1 = read_ints(s->pb, sectors1, WTV_SECTOR_SIZE / 4);
        int i;

        wf->sectors = av_malloc_array(nb_sectors1, 1 << WTV_SECTOR_BITS);
        if (!wf->sectors) {
            av_free(wf);
            return NULL;
        }
        wf->nb_sectors = 0;
        for (i = 0; i < nb_sectors1; i++) {
            if (seek_by_sector(s->pb, sectors1[i], 0) < 0)
                break;
            wf->nb_sectors += read_ints(s->pb, wf->sectors + i * WTV_SECTOR_SIZE / 4, WTV_SECTOR_SIZE / 4);
        }
    } else {
        av_log(s, AV_LOG_ERROR, "unsupported file allocation table depth (0x%x)\n", depth);
        av_free(wf);
        return NULL;
    }
    wf->sector_bits = length & (1ULL<<63) ? WTV_SECTOR_BITS : WTV_BIGSECTOR_BITS;

    if (!wf->nb_sectors) {
        av_freep(&wf->sectors);
        av_freep(&wf);
        return NULL;
    }

    size = avio_size(s->pb);
    if (size >= 0 && (int64_t)wf->sectors[wf->nb_sectors - 1] << WTV_SECTOR_BITS > size)
        av_log(s, AV_LOG_WARNING, "truncated file\n");

    /* check length */
    length &= 0xFFFFFFFFFFFF;
    if (length > ((int64_t)wf->nb_sectors << wf->sector_bits)) {
        av_log(s, AV_LOG_WARNING, "reported file length (0x%"PRIx64") exceeds number of available sectors (0x%"PRIx64")\n", length, (int64_t)wf->nb_sectors << wf->sector_bits);
        length = (int64_t)wf->nb_sectors <<  wf->sector_bits;
    }
    wf->length = length;

    /* seek to initial sector */
    wf->position = 0;
    if (seek_by_sector(s->pb, wf->sectors[0], 0) < 0) {
        av_freep(&wf->sectors);
        av_freep(&wf);
        return NULL;
    }

    wf->pb_filesystem = s->pb;
    buffer = av_malloc(1 << wf->sector_bits);
    if (!buffer) {
        av_freep(&wf->sectors);
        av_freep(&wf);
        return NULL;
    }

    pb = avio_alloc_context(buffer, 1 << wf->sector_bits, 0, wf,
                           wtvfile_read_packet, NULL, wtvfile_seek);
    if (!pb) {
        av_freep(&buffer);
        av_freep(&wf->sectors);
        av_freep(&wf);
    }
    return pb;
}

static AVIOContext * wtvfile_open2(AVFormatContext *s, const uint8_t *buf, int buf_size, const uint8_t *filename, int filename_size)
{
    const uint8_t *buf_end = buf + buf_size;

    while(buf + 48 <= buf_end) {
        int dir_length, name_size, first_sector, depth;
        uint64_t file_length;
        const uint8_t *name;
        if (ff_guidcmp(buf, ff_dir_entry_guid)) {
            av_log(s, AV_LOG_ERROR, "unknown guid "FF_PRI_GUID", expected dir_entry_guid; "
                   "remaining directory entries ignored\n", FF_ARG_GUID(buf));
            break;
        }
        dir_length  = AV_RL16(buf + 16);
        file_length = AV_RL64(buf + 24);
        name_size   = 2 * AV_RL32(buf + 32);
        if (name_size < 0) {
            av_log(s, AV_LOG_ERROR,
                   "bad filename length, remaining directory entries ignored\n");
            break;
        }
        if (48 + (int64_t)name_size > buf_end - buf) {
            av_log(s, AV_LOG_ERROR, "filename exceeds buffer size; remaining directory entries ignored\n");
            break;
        }
        first_sector = AV_RL32(buf + 40 + name_size);
        depth        = AV_RL32(buf + 44 + name_size);

        /* compare file name; test optional null terminator */
        name = buf + 40;
        if (name_size >= filename_size &&
            !memcmp(name, filename, filename_size) &&
            (name_size < filename_size + 2 || !AV_RN16(name + filename_size)))
            return wtvfile_open_sector(first_sector, file_length, depth, s);

        buf += dir_length;
    }
    return 0;
}

#define wtvfile_open(s, buf, buf_size, filename) \
    wtvfile_open2(s, buf, buf_size, filename, sizeof(filename))

int parse_chunks(AVFormatContext *s, int seek_action, int64_t wanted_timestamp, int flags);
void parse_legacy_attrib(AVFormatContext *s, AVIOContext *pb);

static int read_header(AVFormatContext *s)
{
    WtvContext *wtv = (WtvContext *)s->priv_data;
    unsigned root_sector;
    int root_size;
    uint8_t root[WTV_SECTOR_SIZE];
    AVIOContext *pb;
    int64_t timeline_pos;
    int64_t ret;

    wtv->epoch          =
    wtv->pts            =
    wtv->last_valid_pts = AV_NOPTS_VALUE;

    /* read root directory sector */
    avio_skip(s->pb, 0x30);
    root_size = avio_rl32(s->pb);
    if (root_size > sizeof(root)) {
        av_log(s, AV_LOG_ERROR, "root directory size exceeds sector size\n");
        return AVERROR_INVALIDDATA;
    }
    avio_skip(s->pb, 4);
    root_sector = avio_rl32(s->pb);

    ret = seek_by_sector(s->pb, root_sector, 0);
    if (ret < 0)
        return ret;
    root_size = avio_read(s->pb, root, root_size);
    if (root_size < 0)
        return AVERROR_INVALIDDATA;

    /* parse chunks up until first data chunk */
    wtv->pb = wtvfile_open(s, root, root_size, ff_timeline_le16);
    if (!wtv->pb) {
        av_log(s, AV_LOG_ERROR, "timeline data missing\n");
        return AVERROR_INVALIDDATA;
    }

    ret = parse_chunks(s, 0, 0, 0);
    if (ret < 0)
        return ret;
    avio_seek(wtv->pb, -32, SEEK_CUR);

    timeline_pos = avio_tell(s->pb);

    /* read metadata */
    pb = wtvfile_open(s, root, root_size, ff_table_0_entries_legacy_attrib_le16);
    if (pb) {
        parse_legacy_attrib(s, pb);
        wtvfile_close(pb);
    }

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    /* read seek index */
    if (s->nb_streams) {
        AVStream *st = s->streams[0];
        pb = wtvfile_open(s, root, root_size, ff_table_0_entries_time_le16);
        if (pb) {
            while(1) {
                uint64_t timestamp = avio_rl64(pb);
                uint64_t frame_nb  = avio_rl64(pb);
                if (avio_feof(pb))
                    break;
                ff_add_index_entry(&wtv->index_entries, &wtv->nb_index_entries, &wtv->index_entries_allocated_size,
                                   0, timestamp, frame_nb, 0, AVINDEX_KEYFRAME);
            }
            wtvfile_close(pb);

            if (wtv->nb_index_entries) {
                pb = wtvfile_open(s, root, root_size, ff_timeline_table_0_entries_Events_le16);
                if (pb) {
                    AVIndexEntry *e = wtv->index_entries;
                    AVIndexEntry *e_end = wtv->index_entries + wtv->nb_index_entries - 1;
                    uint64_t last_position = 0;
                    while (1) {
                        uint64_t frame_nb = avio_rl64(pb);
                        uint64_t position = avio_rl64(pb);
                        while (e <= e_end && frame_nb > e->size) {
                            e->pos = last_position;
                            e++;
                        }
                        if (avio_feof(pb))
                            break;
                        last_position = position;
                    }
                    e_end->pos = last_position;
                    wtvfile_close(pb);
                    st->duration = e_end->timestamp;
                }
            }
        }
    }

    avio_seek(s->pb, timeline_pos, SEEK_SET);
    return 0;
}

static int read_close(AVFormatContext *s)
{
    WtvContext *wtv = s->priv_data;
    av_freep(&wtv->index_entries);
    wtvfile_close(wtv->pb);
    return 0;
}
