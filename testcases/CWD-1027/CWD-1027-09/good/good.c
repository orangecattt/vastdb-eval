#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>

#define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#if AV_GCC_VERSION_AT_LEAST(3,1)
    #define av_malloc_attrib __attribute__((__malloc__))
#else
    #define av_malloc_attrib
#endif
#if AV_GCC_VERSION_AT_LEAST(4,3)
    #define av_alloc_size(...) __attribute__((alloc_size(__VA_ARGS__)))
#else
    #define av_alloc_size(...)
#endif

#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#endif

typedef struct AVClass AVClass;
typedef struct AVIOContext AVIOContext;
typedef struct AVInputFormat AVInputFormat;
typedef struct AVOutputFormat AVOutputFormat;
typedef struct AVStream AVStream;
typedef struct AVProgram AVProgram;
typedef struct AVChapter AVChapter;
typedef struct AVFormatContext AVFormatContext;
typedef struct AVTreeNode AVTreeNode;

enum AVCodecID {
    AV_CODEC_ID_NONE,
};
enum AVDurationEstimationMethod {
    AVFMT_DURATION_FROM_PTS,
    AVFMT_DURATION_FROM_STREAM,
    AVFMT_DURATION_FROM_BITRATE
};

void *av_malloc(size_t size) av_malloc_attrib av_alloc_size(1);
void *av_mallocz(size_t size) av_malloc_attrib av_alloc_size(1);
void av_free(void *ptr);

int ffio_init_context(AVIOContext *s,
                  unsigned char *buffer,
                  int buffer_size,
                  int write_flag,
                  void *opaque,
                  int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                  int64_t (*seek)(void *opaque, int64_t offset, int whence));

void ffio_init_checksum(AVIOContext *s,
                        unsigned long (*update_checksum)(unsigned long c, const uint8_t *p, unsigned int len),
                        unsigned long checksum);
unsigned long ffio_get_checksum(AVIOContext *s);
unsigned long ff_crc04C11DB7_update(unsigned long checksum, const uint8_t *buf, unsigned int len);

int avio_close_dyn_buf(AVIOContext *s, uint8_t **pbuffer);
void avio_wb64(AVIOContext *s, uint64_t val);
void avio_wl32(AVIOContext *s, unsigned int val);
void avio_write(AVIOContext *s, const unsigned char *buf, int size);

void ff_put_v(AVIOContext *bc, uint64_t val);

enum AVIODataMarkerType {
    AVIO_DATA_MARKER_HEADER,
    AVIO_DATA_MARKER_SYNC_POINT,
    AVIO_DATA_MARKER_BOUNDARY_POINT,
    AVIO_DATA_MARKER_UNKNOWN,
    AVIO_DATA_MARKER_TRAILER,
    AVIO_DATA_MARKER_FLUSH_POINT,
};

typedef enum{
    FLAG_KEY        =   1,
    FLAG_EOR        =   2,
    FLAG_CODED_PTS  =   8,
    FLAG_STREAM_ID  =  16,
    FLAG_SIZE_MSB   =  32,
    FLAG_CHECKSUM   =  64,
    FLAG_RESERVED   = 128,
    FLAG_SM_DATA    = 256,
    FLAG_HEADER_IDX =1024,
    FLAG_MATCH_TIME =2048,
    FLAG_CODED      =4096,
    FLAG_INVALID    =8192,
} Flag;

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct FrameCode {
    uint16_t flags;
    uint8_t  stream_id;
    uint16_t size_mul;
    uint16_t size_lsb;
    int16_t  pts_delta;
    uint8_t  reserved_count;
    uint8_t  header_idx;
} FrameCode;

typedef struct StreamContext {
    int last_flags;
    int skip_until_key_frame;
    int64_t last_pts;
    int time_base_id;
    AVRational *time_base;
    int msb_pts_shift;
    int max_pts_distance;
    int decode_delay;
    int64_t *keyframe_pts;
} StreamContext;

typedef struct ChapterContext {
    AVRational *time_base;
} ChapterContext;

typedef struct NUTContext {
    const AVClass *av_class;
    AVFormatContext *avf;
    FrameCode frame_code[256];
    uint8_t header_len[128];
    const uint8_t *header[128];
    uint64_t next_startcode;
    StreamContext *stream;
    ChapterContext *chapter;
    unsigned int max_distance;
    unsigned int time_base_count;
    int64_t last_syncpoint_pos;
    int64_t last_resync_pos;
    int header_count;
    AVRational *time_base;
    struct AVTreeNode *syncpoints;
    int sp_count;
    int write_index;
    int64_t max_pts;
    AVRational *max_pts_tb;
    int flags;
    int version;
    int minor_version;
} NUTContext;

typedef struct DynBuffer {
    int pos, size, allocated_size;
    uint8_t *buffer;
    int io_buffer_size;
    uint8_t io_buffer[1];
} DynBuffer;

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
    int (*write_data_type)(void *opaque, uint8_t *buf, int buf_size,
                           enum AVIODataMarkerType type, int64_t time);
    int ignore_boundary_point;
    enum AVIODataMarkerType current_type;
    int64_t last_time;
    int (*short_seek_get)(void *opaque);
    int64_t written;
    unsigned char *buf_ptr_max;
    int min_packet_size;
} AVIOContext;

typedef struct AVIOInterruptCB {
    int (*callback)(void*);
    void *opaque;
} AVIOInterruptCB;

typedef struct AVFormatContext {
    const AVClass *av_class;
    AVInputFormat *iformat;
    AVOutputFormat *oformat;
    void *priv_data;
    AVIOContext *pb;
    int ctx_flags;
    unsigned int nb_streams;
    AVStream **streams;
    char *url;
    int64_t start_time;
    int64_t duration;
    int64_t bit_rate;
    unsigned int packet_size;
    int max_delay;
    int flags;
    int64_t probesize;
    int64_t max_analyze_duration;
    const uint8_t *key;
    int keylen;
    unsigned int nb_programs;
    AVProgram **programs;
    enum AVCodecID video_codec_id;
    enum AVCodecID audio_codec_id;
    enum AVCodecID subtitle_codec_id;
    unsigned int max_index_size;
    unsigned int max_picture_buffer;
    unsigned int nb_chapters;
    AVChapter **chapters;
    int64_t metadata;
    int64_t start_time_realtime;
    int fps_probe_size;
    int error_recognition;
    AVIOInterruptCB interrupt_callback;
    int debug;
    int64_t max_interleave_delta;
    int strict_std_compliance;
    int event_flags;
    int max_ts_probe;
    int avoid_negative_ts;
    int ts_id;
    int audio_preload;
    int max_chunk_duration;
    int max_chunk_size;
    int use_wallclock_as_timestamps;
    int avio_flags;
    enum AVDurationEstimationMethod duration_estimation_method;
} AVFormatContext;

static int write_headers(AVFormatContext *avctx, AVIOContext *bc);
static void write_index(NUTContext *nut, AVIOContext *bc);

#define av_assert1(cond) ((void)0)

static int dyn_packet_buf_write(void *opaque, uint8_t *buf, int buf_size);
static int dyn_buf_write(void *opaque, uint8_t *buf, int buf_size);
static int64_t dyn_buf_seek(void *opaque, int64_t offset, int whence);

#define MAIN_STARTCODE (0x7A561F5F04ADULL + (((uint64_t)('N'<<8) + 'M')<<48))
#define STREAM_STARTCODE (0x11405BF2F9DBULL + (((uint64_t)('N'<<8) + 'S')<<48))
#define SYNCPOINT_STARTCODE (0xE4ADEECA4569ULL + (((uint64_t)('N'<<8) + 'K')<<48))
#define INDEX_STARTCODE (0xDD672F23E64EULL + (((uint64_t)('N'<<8) + 'X')<<48))
#define INFO_STARTCODE (0xAB68B596BA78ULL + (((uint64_t)('N'<<8) + 'I')<<48))

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

static int url_open_dyn_buf_internal(AVIOContext **s, int max_packet_size)
{
    DynBuffer *d;
    unsigned io_buffer_size = max_packet_size ? max_packet_size : 1024;

    if (sizeof(DynBuffer) + io_buffer_size < io_buffer_size)
        return -1;
    d = av_mallocz(sizeof(DynBuffer) + io_buffer_size);
    if (!d)
        return AVERROR(ENOMEM);
    d->io_buffer_size = io_buffer_size;
    *s = avio_alloc_context(d->io_buffer, d->io_buffer_size, 1, d, NULL,
                            max_packet_size ? dyn_packet_buf_write : dyn_buf_write,
                            max_packet_size ? NULL : dyn_buf_seek);
    if(!*s) {
        av_free(d);
        return AVERROR(ENOMEM);
    }
    (*s)->max_packet_size = max_packet_size;
    return 0;
}

int avio_open_dyn_buf(AVIOContext **s)
{
    return url_open_dyn_buf_internal(s,0);
}

static void put_packet(NUTContext *nut, AVIOContext *bc, AVIOContext *dyn_bc,
                       int calculate_checksum, uint64_t startcode)
{
    uint8_t *dyn_buf = NULL;
    int dyn_size     = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    int forw_ptr     = dyn_size + 4 * calculate_checksum;

    if (forw_ptr > 4096)
        ffio_init_checksum(bc, ff_crc04C11DB7_update, 0);
    avio_wb64(bc, startcode);
    ff_put_v(bc, forw_ptr);
    if (forw_ptr > 4096)
        avio_wl32(bc, ffio_get_checksum(bc));

    if (calculate_checksum)
        ffio_init_checksum(bc, ff_crc04C11DB7_update, 0);
    avio_write(bc, dyn_buf, dyn_size);
    if (calculate_checksum)
        avio_wl32(bc, ffio_get_checksum(bc));

    av_free(dyn_buf);
}

static int nut_write_trailer(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    AVIOContext *bc = s->pb, *dyn_bc;
    int ret;

    while (nut->header_count < 3)
        write_headers(s, bc);

    if (!nut->sp_count)
        return 0;

    ret = avio_open_dyn_buf(&dyn_bc);
    if (ret >= 0) {
        av_assert1(nut->write_index); // sp_count should be 0 if no index is going to be written
        write_index(nut, dyn_bc);
        put_packet(nut, bc, dyn_bc, 1, INDEX_STARTCODE);
    }

    return 0;
}
