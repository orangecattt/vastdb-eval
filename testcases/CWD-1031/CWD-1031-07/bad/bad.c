#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <inttypes.h>

// FROM: libavutil/macros.h
#define AV_STRINGIFY(s)         AV_TOSTRING(s)
#define AV_TOSTRING(s)          #s
#define MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

// FROM: libavutil/common.h
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

// FROM: libavutil/error.h
#define AVERROR(e) (-(e))
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A')
#define AVERROR_ENOSYS AVERROR(ENOSYS)
#define AVERROR_ENOMEM AVERROR(ENOMEM)
#define AVERROR_EOF AVERROR('E','O','F',' ')

// FROM: libavutil/avutil.h
#define AV_NOPTS_VALUE          ((int64_t)UINT64_C(0x8000000000000000))
#define AV_TIME_BASE            1000000
#define AV_TIME_BASE_Q          (AVRational){1, AV_TIME_BASE}
#define av_const const

// FROM: libavutil/log.h
#define AV_LOG_PANIC     0
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48

// FROM: libavutil/attributes.h
#define av_always_inline __attribute__((always_inline)) inline

// FROM: libavutil/rational.h
typedef struct AVRational{
    int num;
    int den;
} AVRational;

// FROM: libavutil/mem.h
void *av_malloc(size_t size);
void *av_malloc_array(size_t nmemb, size_t size);
void *av_mallocz(size_t size);
void *av_calloc(size_t nmemb, size_t size);
void *av_realloc_array(void *ptr, size_t nmemb, size_t size);
void av_freep(void *ptr);

// FROM: libavutil/avassert.h
#define av_assert0(cond) do {                                           \
    if (!(cond)) {                                                      \
        av_log(NULL, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} while (0)

// FROM: libavutil/mathematics.h
int64_t av_gcd(int64_t a, int64_t b);

// FROM: libavutil/log.h
void av_log(void *avcl, int level, const char *fmt, ...);

// FROM: libavcodec/codec_id.h
enum AVCodecID {
    AV_CODEC_ID_NONE,
};

// FROM: libavutil/avutil.h
enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
};

// FROM: libavformat/internal.h
typedef struct AVCodecTag {
    enum AVCodecID id;
    unsigned int tag;
} AVCodecTag;

// Forward declarations
typedef struct AVCodec AVCodec;
typedef struct AVCodecContext AVCodecContext;
typedef struct AVIOContext AVIOContext;
typedef struct AVClass AVClass;
typedef struct AVCodecParameters AVCodecParameters;
typedef struct AVBSFContext AVBSFContext;
typedef struct AVTreeNode AVTreeNode;
typedef struct AVPacket AVPacket;
typedef struct AVDictionary AVDictionary;
typedef struct AVMetadataConv AVMetadataConv;
typedef struct AVInputFormat AVInputFormat;

// FROM: libavcodec/codec_par.h
struct AVCodecParameters {
    enum AVCodecID codec_id;
    enum AVMediaType codec_type;
    unsigned int codec_tag;
    int extradata_size;
    uint8_t *extradata;
    int width;
    int height;
    int sample_rate;
    int channels;
    int video_delay;
};

// FROM: libavformat/avformat.h
typedef struct AVStream {
    int index;
    int id;
    AVCodecParameters *codecpar;
    AVRational time_base;
    int64_t start_time;
    int64_t duration;
    AVRational sample_aspect_ratio;
    AVRational r_frame_rate;
    int event_flags;
    int discard;
    int disposition;
} AVStream;

// FROM: libavformat/avformat.h
typedef struct AVFormatContext {
    const AVClass *av_class;
    AVStream **streams;
    unsigned int nb_streams;
    int64_t duration;
    int event_flags;
    int max_streams;
    int max_probe_packets;
    struct AVIOContext *pb;
    const AVInputFormat *iformat;
    void *priv_data;
} AVFormatContext;

// FROM: libavformat/internal.h
typedef struct FFFormatContext {
    AVFormatContext pub;
    int64_t data_offset;
    int inject_global_side_data;
} FFFormatContext;

// FROM: libavformat/internal.h
typedef struct FFStream {
    AVStream pub;
    int64_t cur_dts;
    int64_t first_dts;
    int64_t last_IP_pts;
    int64_t last_dts_for_order_check;
    int64_t pts_buffer[16 + 1];
    int64_t pts_wrap_reference;
    int pts_wrap_behavior;
    int probe_packets;
    AVCodecContext *avctx;
    struct {
        int64_t last_dts;
        int64_t fps_first_dts;
        int64_t fps_last_dts;
    } *info;
} FFStream;

// FROM: libavformat/avio.h
struct AVIOContext {
    int seekable;
    int eof_reached;
};

// FROM: libavformat/internal.h
#define RELATIVE_TS_BASE (INT64_MAX - (1LL << 48))

// FROM: libavformat/avformat.h
#define AVINDEX_KEYFRAME 0x0001
#define AV_DISPOSITION_DEFAULT              (1 << 0)
#define AVSEEK_FLAG_BACKWARD 1
#define AVFMT_SEEK_TO_PTS   0x4000000
#define AVSTREAM_EVENT_FLAG_METADATA_UPDATED 0x0001
#define AVFMT_EVENT_FLAG_METADATA_UPDATED 0x0001
#define AVFMT_GENERIC_INDEX 0x0100
#define AVFMT_GLOBALHEADER  0x0040
#define AVFMT_TS_DISCONT    0x0200
#define AVPROBE_SCORE_MAX       100
#define AV_PTS_WRAP_IGNORE 0

// FROM: libavcodec/packet.h
#define AV_PKT_FLAG_KEY     0x0001
#define AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_COUNT  0x0001
#define AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_LAYOUT 0x0002
#define AV_SIDE_DATA_PARAM_CHANGE_SAMPLE_RATE    0x0004
#define AV_SIDE_DATA_PARAM_CHANGE_DIMENSIONS     0x0008

// FROM: libavformat/avformat.h
#define AVFMT_NOFILE        0x0001
#define AVFMT_NOBINSEARCH   0x2000
#define AVFMT_NOGENSEARCH   0x4000
#define AVFMT_NO_BYTE_SEEK  0x8000
#define AVFMT_ALLOW_FLUSH  0x10000

// FROM: libavformat/internal.h
#define FF_FMT_INIT_CLEANUP                             (1 << 0)

// FROM: libavformat/avio.h
#define AVIO_SEEKABLE_NORMAL (1 << 0)

// FROM: libavformat/internal.h
static av_always_inline FFFormatContext *ffformatcontext(AVFormatContext *s)
{
    return (FFFormatContext*)s;
}

static av_always_inline FFStream *ffstream(AVStream *st)
{
    return (FFStream*)st;
}

// FROM: libavformat/nut.h
#define      MAIN_STARTCODE (0x7A561F5F04ADULL + (((uint64_t)('N'<<8) + 'M')<<48))
#define    STREAM_STARTCODE (0x11405BF2F9DBULL + (((uint64_t)('N'<<8) + 'S')<<48))
#define SYNCPOINT_STARTCODE (0xE4ADEECA4569ULL + (((uint64_t)('N'<<8) + 'K')<<48))
#define     INDEX_STARTCODE (0xDD672F23E64EULL + (((uint64_t)('N'<<8) + 'X')<<48))
#define      INFO_STARTCODE (0xAB68B596BA78ULL + (((uint64_t)('N'<<8) + 'I')<<48))

#define MAX_DISTANCE (1024*32-1)
#define NUT_MAX_VERSION 4
#define NUT_STABLE_VERSION 3
#define NUT_MIN_VERSION 2
#define NUT_MAX_STREAMS 256

// FROM: libavformat/nut.h
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

// FROM: libavformat/nut.h
typedef struct FrameCode {
    uint16_t flags;
    uint8_t  stream_id;
    uint16_t size_mul;
    uint16_t size_lsb;
    int16_t  pts_delta;
    uint8_t  reserved_count;
    uint8_t  header_idx;
} FrameCode;

// FROM: libavformat/nut.h
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

// FROM: libavformat/nut.h
typedef struct ChapterContext {
    AVRational *time_base;
} ChapterContext;

// FROM: libavformat/nut.h
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

// FROM: libavformat/nut.h
extern const AVCodecTag ff_nut_subtitle_tags[];
extern const AVCodecTag ff_nut_video_tags[];
extern const AVCodecTag ff_nut_audio_tags[];
extern const AVCodecTag ff_nut_audio_extra_tags[];
extern const AVCodecTag ff_nut_data_tags[];

// FROM: libavformat/nut.h
typedef struct Dispositions {
    char str[9];
    int flag;
} Dispositions;

// FROM: libavformat/nut.h
extern const Dispositions ff_nut_dispositions[];

// FROM: libavformat/metadata.h
struct AVMetadataConv {
    const char *native;
    const char *generic;
};

extern const AVMetadataConv ff_nut_metadata_conv[];

// FROM: libavformat/nut.h
void ff_nut_reset_ts(NUTContext *nut, AVRational time_base, int64_t val);
int64_t ff_lsb2full(StreamContext *stream, int64_t lsb);
int ff_nut_sp_pos_cmp(const void *a, const void *b);
int ff_nut_sp_pts_cmp(const void *a, const void *b);
int ff_nut_add_sp(NUTContext *nut, int64_t pos, int64_t back_ptr, int64_t ts);
void ff_nut_free_sp(NUTContext *nut);

// FROM: libavformat/nutdec.c
static int decode_info_header(NUTContext *nut);
static int find_and_decode_index(NUTContext *nut);

// FROM: libavformat/avio_internal.h
uint64_t ffio_read_varlen(AVIOContext *bc);
void ffio_init_checksum(AVIOContext *s,
                        unsigned long (*update_checksum)(unsigned long c, const uint8_t *p, unsigned int len),
                        unsigned long checksum);
unsigned long ffio_get_checksum(AVIOContext *s);
unsigned long ff_crc04C11DB7_update(unsigned long checksum, const uint8_t *buf,
                                    unsigned int len);

// FROM: libavformat/internal.h
int ff_get_extradata(AVFormatContext *s, AVCodecParameters *par, AVIOContext *pb, int size);
void avpriv_set_pts_info(AVStream *st, int pts_wrap_bits,
                         unsigned int pts_num, unsigned int pts_den);
enum AVCodecID ff_codec_get_id(const AVCodecTag *tags, unsigned int tag);
enum AVCodecID av_codec_get_id(const struct AVCodecTag * const *tags, unsigned int tag);
int64_t ff_gen_search(AVFormatContext *s, int stream_index,
                      int64_t target_ts, int64_t pos_min,
                      int64_t pos_max, int64_t pos_limit,
                      int64_t ts_min, int64_t ts_max,
                      int flags, int64_t *ts_ret,
                      int64_t (*read_timestamp)(struct AVFormatContext *, int , int64_t *, int64_t ));
int ff_find_last_ts(AVFormatContext *s, int stream_index, int64_t *ts, int64_t *pos,
                    int64_t (*read_timestamp)(struct AVFormatContext *, int , int64_t *, int64_t ));
int av_index_search_timestamp(AVStream *st, int64_t timestamp, int flags);
int av_add_index_entry(AVStream *st, int64_t pos, int64_t timestamp,
                       int size, int distance, int flags);

// FROM: libavformat/metadata.h
void ff_metadata_conv_ctx(AVFormatContext *ctx, const AVMetadataConv *d_conv,
                                                 const AVMetadataConv *s_conv);

// FROM: libavformat/riff.h
extern const AVCodecTag ff_codec_bmp_tags[];
extern const AVCodecTag ff_codec_wav_tags[];

// FROM: libavformat/isom.h
extern const AVCodecTag ff_codec_movvideo_tags[];

// FROM: libavformat/avformat.h
AVStream *avformat_new_stream(AVFormatContext *s, const AVCodec *c);

// FROM: libavformat/avio.h
int64_t avio_tell(AVIOContext *s);
int64_t avio_seek(AVIOContext *s, int64_t offset, int whence);
int avio_r8(AVIOContext *s);
int avio_feof(AVIOContext *s);
int avio_read(AVIOContext *s, unsigned char *buf, int size);
int avio_skip(AVIOContext *s, int64_t offset);
int64_t avio_size(AVIOContext *s);
uint32_t avio_rb32(AVIOContext *s);
uint64_t avio_rb64(AVIOContext *s);
uint16_t avio_rl16(AVIOContext *s);
uint32_t avio_rl32(AVIOContext *s);
void avio_wl32(AVIOContext *s, unsigned int val);
uint64_t av_be2ne64(uint64_t x);

// FROM: libavformat/nutdec.c
#define GET_V(dst, check)                                                     \
    do {                                                                      \
        tmp = ffio_read_varlen(bc);                                           \
        if (!(check)) {                                                       \
            av_log(s, AV_LOG_ERROR, "Error " #dst " is (%"PRId64")\n", tmp);  \
            ret = AVERROR_INVALIDDATA;                                        \
            goto fail;                                                        \
        }                                                                     \
        dst = tmp;                                                            \
    } while (0)

// FROM: libavformat/nutdec.c
static int64_t get_s(AVIOContext *bc)
{
    int64_t v = ffio_read_varlen(bc) + 1;

    if (v & 1)
        return -(v >> 1);
    else
        return  (v >> 1);
}

// FROM: libavformat/nutdec.c
static uint64_t get_fourcc(AVIOContext *bc)
{
    unsigned int len = ffio_read_varlen(bc);

    if (len == 2)
        return avio_rl16(bc);
    else if (len == 4)
        return avio_rl32(bc);
    else {
        av_log(NULL, AV_LOG_ERROR, "Unsupported fourcc length %d\n", len);
        return -1;
    }
}

// FROM: libavformat/nutdec.c
static int get_packetheader(NUTContext *nut, AVIOContext *bc,
                            int calculate_checksum, uint64_t startcode)
{
    int64_t size;

    startcode = av_be2ne64(startcode);
    startcode = ff_crc04C11DB7_update(0, (uint8_t*) &startcode, 8);

    ffio_init_checksum(bc, ff_crc04C11DB7_update, startcode);
    size = ffio_read_varlen(bc);
    if (size > 4096)
        avio_rb32(bc);
    if (ffio_get_checksum(bc) && size > 4096)
        return -1;

    ffio_init_checksum(bc, calculate_checksum ? ff_crc04C11DB7_update : NULL, 0);

    return size;
}

// FROM: libavformat/nutdec.c
static uint64_t find_any_startcode(AVIOContext *bc, int64_t pos)
{
    uint64_t state = 0;

    if (pos >= 0)
        avio_seek(bc, pos, SEEK_SET);
    while (!avio_feof(bc)) {
        state = (state << 8) | avio_r8(bc);
        if ((state >> 56) != 'N')
            continue;
        switch (state) {
        case MAIN_STARTCODE:
        case STREAM_STARTCODE:
        case SYNCPOINT_STARTCODE:
        case INFO_STARTCODE:
        case INDEX_STARTCODE:
            return state;
        }
    }

    return 0;
}

// FROM: libavformat/nutdec.c
static int64_t find_startcode(AVIOContext *bc, uint64_t code, int64_t pos)
{
    for (;;) {
        uint64_t startcode = find_any_startcode(bc, pos);
        if (startcode == code)
            return avio_tell(bc) - 8;
        else if (startcode == 0)
            return -1;
        pos = -1;
    }
}

// FROM: libavformat/nutdec.c
static int skip_reserved(AVIOContext *bc, int64_t pos)
{
    pos -= avio_tell(bc);
    if (pos < 0) {
        avio_seek(bc, pos, SEEK_CUR);
        return AVERROR_INVALIDDATA;
    } else {
        while (pos--) {
            if (bc->eof_reached)
                return AVERROR_INVALIDDATA;
            avio_r8(bc);
        }
        return 0;
    }
}

// FROM: libavformat/nutdec.c
static int decode_main_header(NUTContext *nut)
{
    AVFormatContext *s = nut->avf;
    AVIOContext *bc    = s->pb;
    uint64_t tmp, end, length;
    unsigned int stream_count;
    int i, j, count, ret;
    int tmp_stream, tmp_mul, tmp_pts, tmp_size, tmp_res, tmp_head_idx;

    length = get_packetheader(nut, bc, 1, MAIN_STARTCODE);
    end = length + avio_tell(bc);

    nut->version = ffio_read_varlen(bc);
    if (nut->version < NUT_MIN_VERSION ||
        nut->version > NUT_MAX_VERSION) {
        av_log(s, AV_LOG_ERROR, "Version %d not supported.\n",
               nut->version);
        return AVERROR(ENOSYS);
    }
    if (nut->version > 3)
        nut->minor_version = ffio_read_varlen(bc);

    GET_V(stream_count, tmp > 0 && tmp <= NUT_MAX_STREAMS);

    nut->max_distance = ffio_read_varlen(bc);
    if (nut->max_distance > 65536) {
        av_log(s, AV_LOG_DEBUG, "max_distance %d\n", nut->max_distance);
        nut->max_distance = 65536;
    }

    GET_V(nut->time_base_count, tmp > 0 && tmp < INT_MAX / sizeof(AVRational) && tmp < length/2);
    nut->time_base = av_malloc_array(nut->time_base_count, sizeof(AVRational));
    if (!nut->time_base)
        return AVERROR(ENOMEM);

    for (i = 0; i < nut->time_base_count; i++) {
        GET_V(nut->time_base[i].num, tmp > 0 && tmp < (1ULL << 31));
        GET_V(nut->time_base[i].den, tmp > 0 && tmp < (1ULL << 31));
        if (av_gcd(nut->time_base[i].num, nut->time_base[i].den) != 1) {
            av_log(s, AV_LOG_ERROR, "invalid time base %d/%d\n",
                   nut->time_base[i].num,
                   nut->time_base[i].den);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
    }
    tmp_pts      = 0;
    tmp_mul      = 1;
    tmp_stream   = 0;
    tmp_head_idx = 0;
    for (i = 0; i < 256;) {
        int tmp_flags  = ffio_read_varlen(bc);
        int tmp_fields = ffio_read_varlen(bc);

        if (tmp_fields > 0)
            tmp_pts = get_s(bc);
        if (tmp_fields > 1)
            tmp_mul = ffio_read_varlen(bc);
        if (tmp_fields > 2)
            tmp_stream = ffio_read_varlen(bc);
        if (tmp_fields > 3)
            tmp_size = ffio_read_varlen(bc);
        else
            tmp_size = 0;
        if (tmp_fields > 4)
            tmp_res = ffio_read_varlen(bc);
        else
            tmp_res = 0;
        if (tmp_fields > 5)
            count = ffio_read_varlen(bc);
        else
            count = tmp_mul - (unsigned)tmp_size;
        if (tmp_fields > 6)
            get_s(bc);
        if (tmp_fields > 7)
            tmp_head_idx = ffio_read_varlen(bc);

        while (tmp_fields-- > 8) {
            if (bc->eof_reached) {
                av_log(s, AV_LOG_ERROR, "reached EOF while decoding main header\n");
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            ffio_read_varlen(bc);
        }

        if (count <= 0 || count > 256 - (i <= 'N') - i) {
            av_log(s, AV_LOG_ERROR, "illegal count %d at %d\n", count, i);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        if (tmp_stream >= stream_count) {
            av_log(s, AV_LOG_ERROR, "illegal stream number %d >= %d\n",
                   tmp_stream, stream_count);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        if (tmp_size < 0 || tmp_size > INT_MAX - count) {
            av_log(s, AV_LOG_ERROR, "illegal size\n");
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        for (j = 0; j < count; j++, i++) {
            if (i == 'N') {
                nut->frame_code[i].flags = FLAG_INVALID;
                j--;
                continue;
            }
            nut->frame_code[i].flags          = tmp_flags;
            nut->frame_code[i].pts_delta      = tmp_pts;
            nut->frame_code[i].stream_id      = tmp_stream;
            nut->frame_code[i].size_mul       = tmp_mul;
            nut->frame_code[i].size_lsb       = tmp_size + j;
            nut->frame_code[i].reserved_count = tmp_res;
            nut->frame_code[i].header_idx     = tmp_head_idx;
        }
    }
    av_assert0(nut->frame_code['N'].flags == FLAG_INVALID);

    if (end > avio_tell(bc) + 4) {
        int rem = 1024;
        GET_V(nut->header_count, tmp < 128U);
        nut->header_count++;
        for (i = 1; i < nut->header_count; i++) {
            uint8_t *hdr;
            GET_V(nut->header_len[i], tmp > 0 && tmp < 256);
            if (rem < nut->header_len[i]) {
                av_log(s, AV_LOG_ERROR,
                       "invalid elision header %d : %d > %d\n",
                       i, nut->header_len[i], rem);
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            rem -= nut->header_len[i];
            hdr = av_malloc(nut->header_len[i]);
            if (!hdr) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            avio_read(bc, hdr, nut->header_len[i]);
            nut->header[i] = hdr;
        }
        av_assert0(nut->header_len[0] == 0);
    }

    if (nut->version > 3 && end > avio_tell(bc) + 4) {
        nut->flags = ffio_read_varlen(bc);
    }

    if (skip_reserved(bc, end) || ffio_get_checksum(bc)) {
        av_log(s, AV_LOG_ERROR, "main header checksum mismatch\n");
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    nut->stream = av_calloc(stream_count, sizeof(StreamContext));
    if (!nut->stream) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    for (i = 0; i < stream_count; i++)
        avformat_new_stream(s, NULL);

    return 0;
fail:
    av_freep(&nut->time_base);
    for (i = 1; i < nut->header_count; i++) {
        av_freep(&nut->header[i]);
    }
    nut->header_count = 0;
    return ret;
}

// FROM: libavformat/nutdec.c
static int decode_stream_header(NUTContext *nut)
{
    AVFormatContext *s = nut->avf;
    AVIOContext *bc    = s->pb;
    StreamContext *stc;
    int class, stream_id, ret;
    uint64_t tmp, end;
    AVStream *st = NULL;

    end  = get_packetheader(nut, bc, 1, STREAM_STARTCODE);
    end += avio_tell(bc);

    GET_V(stream_id, tmp < s->nb_streams && !nut->stream[tmp].time_base);
    stc = &nut->stream[stream_id];
    st  = s->streams[stream_id];
    if (!st)
        return AVERROR(ENOMEM);

    class                = ffio_read_varlen(bc);
    tmp                  = get_fourcc(bc);
    st->codecpar->codec_tag = tmp;
    switch (class) {
    case 0:
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = av_codec_get_id((const AVCodecTag * const []) {
                                                    ff_nut_video_tags,
                                                    ff_codec_bmp_tags,
                                                    ff_codec_movvideo_tags,
                                                    0
                                                },
                                                tmp);
        break;
    case 1:
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id   = av_codec_get_id((const AVCodecTag * const []) {
                                                    ff_nut_audio_tags,
                                                    ff_codec_wav_tags,
                                                    ff_nut_audio_extra_tags,
                                                    0
                                                },
                                                tmp);
        break;
    case 2:
        st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
        st->codecpar->codec_id   = ff_codec_get_id(ff_nut_subtitle_tags, tmp);
        break;
    case 3:
        st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
        st->codecpar->codec_id   = ff_codec_get_id(ff_nut_data_tags, tmp);
        break;
    default:
        av_log(s, AV_LOG_ERROR, "unknown stream class (%d)\n", class);
        return AVERROR(ENOSYS);
    }
    if (class < 3 && st->codecpar->codec_id == AV_CODEC_ID_NONE)
        av_log(s, AV_LOG_ERROR,
               "Unknown codec tag '0x%04x' for stream number %d\n",
               (unsigned int) tmp, stream_id);

    GET_V(stc->time_base_id, tmp < nut->time_base_count);
    GET_V(stc->msb_pts_shift, tmp < 16);
    stc->max_pts_distance = ffio_read_varlen(bc);
    GET_V(stc->decode_delay, tmp < 1000);
    st->codecpar->video_delay = stc->decode_delay;
    ffio_read_varlen(bc);

    GET_V(st->codecpar->extradata_size, tmp < (1 << 30));
    if (st->codecpar->extradata_size) {
        ret = ff_get_extradata(s, st->codecpar, bc,
                               st->codecpar->extradata_size);
        if (ret < 0)
            return ret;
    }

    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        GET_V(st->codecpar->width,  tmp > 0);
        GET_V(st->codecpar->height, tmp > 0);
        st->sample_aspect_ratio.num = ffio_read_varlen(bc);
        st->sample_aspect_ratio.den = ffio_read_varlen(bc);
        if ((!st->sample_aspect_ratio.num) != (!st->sample_aspect_ratio.den)) {
            av_log(s, AV_LOG_ERROR, "invalid aspect ratio %d/%d\n",
                   st->sample_aspect_ratio.num, st->sample_aspect_ratio.den);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        ffio_read_varlen(bc);
    } else if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        GET_V(st->codecpar->sample_rate, tmp > 0);
        ffio_read_varlen(bc);
        GET_V(st->codecpar->channels, tmp > 0);
    }
    if (skip_reserved(bc, end) || ffio_get_checksum(bc)) {
        av_log(s, AV_LOG_ERROR,
               "stream header %d checksum mismatch\n", stream_id);
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }
    stc->time_base = &nut->time_base[stc->time_base_id];
    avpriv_set_pts_info(s->streams[stream_id], 63, stc->time_base->num,
                        stc->time_base->den);
    return 0;
fail:
    if (st && st->codecpar) {
        av_freep(&st->codecpar->extradata);
        st->codecpar->extradata_size = 0;
    }
    return ret;
}

// FROM: libavformat/nutdec.c
static int nut_read_header(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    AVIOContext *bc = s->pb;
    int64_t pos;
    int initialized_stream_count;

    nut->avf = s;

    pos = 0;
    do {
        pos = find_startcode(bc, MAIN_STARTCODE, pos) + 1;
        if (pos < 0 + 1) {
            av_log(s, AV_LOG_ERROR, "No main startcode found.\n");
            return AVERROR_INVALIDDATA;
        }
    } while (decode_main_header(nut) < 0);

    pos = 0;
    for (initialized_stream_count = 0; initialized_stream_count < s->nb_streams;) {
        pos = find_startcode(bc, STREAM_STARTCODE, pos) + 1;
        if (pos < 0 + 1) {
            av_log(s, AV_LOG_ERROR, "Not all stream headers found.\n");
            return AVERROR_INVALIDDATA;
        }
        if (decode_stream_header(nut) >= 0)
            initialized_stream_count++;
    }

    pos = 0;
    for (;;) {
        uint64_t startcode = find_any_startcode(bc, pos);
        pos = avio_tell(bc);

        if (startcode == 0) {
            av_log(s, AV_LOG_ERROR, "EOF before video frames\n");
            return AVERROR_INVALIDDATA;
        } else if (startcode == SYNCPOINT_STARTCODE) {
            nut->next_startcode = startcode;
            break;
        } else if (startcode != INFO_STARTCODE) {
            continue;
        }

        decode_info_header(nut);
    }

    ffformatcontext(s)->data_offset = pos - 8;

    if (bc->seekable & AVIO_SEEKABLE_NORMAL) {
        int64_t orig_pos = avio_tell(bc);
        find_and_decode_index(nut);
        avio_seek(bc, orig_pos, SEEK_SET);
    }
    av_assert0(nut->next_startcode == SYNCPOINT_STARTCODE);

    ff_metadata_conv_ctx(s, NULL, ff_nut_metadata_conv);

    return 0;
}
