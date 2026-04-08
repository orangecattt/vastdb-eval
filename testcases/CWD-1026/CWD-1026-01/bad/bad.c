#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FROM: libavutil/common.h
#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))

// FROM: libavutil/error.h
#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#endif
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A')
#define AVERROR_EOF                FFERRTAG( 'E','O','F',' ')

// FROM: libavutil/avutil.h
enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

#define AV_NOPTS_VALUE          ((int64_t)UINT64_C(0x8000000000000000))
#define AV_TIME_BASE            1000000

// FROM: libavutil/log.h
#define AV_LOG_QUIET    -8
#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48
#define AV_LOG_TRACE    56

// FROM: libavutil/rational.h
typedef struct AVRational{
    int num;
    int den;
} AVRational;

// FROM: libavutil/intreadwrite.h
#ifndef AV_RL32
#   define AV_RL32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[3] << 24) |    \
               (((const uint8_t*)(x))[2] << 16) |    \
               (((const uint8_t*)(x))[1] <<  8) |    \
                ((const uint8_t*)(x))[0])
#endif

// FROM: libavformat/version.h
#define FF_API_R_FRAME_RATE            1

// FROM: libavformat/avio.h
#define AVIO_SEEKABLE_NORMAL (1 << 0)

// FROM: libavformat/avformat.h
#define AVFMT_FLAG_IGNIDX       0x0002

// FROM: libavcodec/avcodec.h
#define AV_EF_EXPLODE   (1<<3)

// FROM: libavcodec/avcodec.h (partial, for AVCodecID enum values used)
enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_RV10,
    AV_CODEC_ID_RV20,
    AV_CODEC_ID_RV30,
    AV_CODEC_ID_RV40,
    AV_CODEC_ID_AC3,
    AV_CODEC_ID_RA_144,
    AV_CODEC_ID_RA_288,
    AV_CODEC_ID_COOK,
    AV_CODEC_ID_ATRAC3,
    AV_CODEC_ID_SIPR,
    AV_CODEC_ID_AAC,
    AV_CODEC_ID_RALF,
    AV_CODEC_ID_CLEARVIDEO,
};

// FROM: libavformat/internal.h
typedef struct AVCodecTag {
    enum AVCodecID id;
    unsigned int tag;
} AVCodecTag;

// FROM: libavutil/dict.h
typedef struct AVDictionary AVDictionary;

// FROM: libavcodec/avcodec.h (partial, for AVCodec)
typedef struct AVCodec AVCodec;

// FROM: libavcodec/avcodec.h (partial, for AVCodecParameters)
typedef struct AVCodecParameters {
    enum AVMediaType codec_type;
    enum AVCodecID codec_id;
    unsigned int codec_tag;
    int bit_rate;
    int width;
    int height;
    int sample_rate;
    int channels;
    int64_t channel_layout;
    int block_align;
    uint8_t *extradata;
    int extradata_size;
} AVCodecParameters;

// FROM: libavutil/buffer.h
typedef struct AVBufferRef AVBufferRef;

// FROM: libavcodec/packet.h (partial, for AVPacket)
typedef struct AVPacket {
    AVBufferRef *buf;
    int64_t pts;
    int64_t dts;
    uint8_t *data;
    int   size;
    int   stream_index;
    int   flags;
    int64_t pos;
} AVPacket;

// FROM: libavformat/avio.h
typedef struct AVIOContext {
    const void *av_class;
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
    int current_type;
    int64_t last_time;
    int (*short_seek_get)(void *opaque);
    int64_t written;
    unsigned char *buf_ptr_max;
    int min_packet_size;
} AVIOContext;

// FROM: libavformat/avformat.h (partial, for AVStreamParseType)
enum AVStreamParseType {
    AVSTREAM_PARSE_NONE,
    AVSTREAM_PARSE_FULL,
    AVSTREAM_PARSE_HEADERS,
    AVSTREAM_PARSE_TIMESTAMPS,
    AVSTREAM_PARSE_FULL_ONCE,
    AVSTREAM_PARSE_FULL_RAW,
};

// FROM: libavformat/avformat.h (partial, for AVStream)
typedef struct AVStream {
    int index;
    int id;
    void *priv_data;
    AVRational time_base;
    int64_t start_time;
    int64_t duration;
    int64_t first_dts;
    int64_t cur_dts;
    int64_t last_IP_pts;
    int last_IP_duration;
    int nb_decoded_frames;
    int64_t mux_ts_offset;
    int64_t pts_wrap_reference;
    int pts_wrap_behavior;
    int status_reached;
    AVCodecParameters *codecpar;
    enum AVStreamParseType need_parsing;
    AVRational avg_frame_rate;
#if FF_API_R_FRAME_RATE
    AVRational r_frame_rate;
#endif
    AVRational sample_aspect_ratio;
} AVStream;

// FROM: libavformat/avformat.h (partial, for AVInputFormat)
typedef struct AVInputFormat AVInputFormat;

// FROM: libavformat/avformat.h (partial, for AVFormatInternal)
typedef struct AVFormatInternal AVFormatInternal;

// FROM: libavformat/avformat.h (partial, for AVFormatContext)
typedef struct AVFormatContext {
    const void *av_class;
    AVInputFormat *iformat;
    void *priv_data;
    AVIOContext *pb;
    unsigned int nb_streams;
    AVStream **streams;
    char url[1024];
    int64_t start_time;
    int64_t duration;
    int64_t bit_rate;
    unsigned int packet_size;
    int max_delay;
    int flags;
    int error_recognition;
    AVDictionary *metadata;
    AVFormatInternal *internal;
} AVFormatContext;

// FROM: libavformat/rmdec.c
struct RMStream {
    AVPacket pkt;
    int videobufsize;
    int videobufpos;
    int curpic_num;
    int cur_slice, slices;
    int64_t pktpos;
    int64_t audiotimestamp;
    int sub_packet_cnt;
    int sub_packet_size, sub_packet_h, coded_framesize;
    int audio_framesize;
    int sub_packet_lengths[16];
    int32_t deint_id;
};

// FROM: libavformat/rm.h
typedef struct RMStream RMStream;

// FROM: libavformat/rmdec.c
typedef struct RMDemuxContext {
    int nb_packets;
    int old_format;
    int current_stream;
    int remaining_len;
    int audio_stream_num;
    int audio_pkt_cnt;
    int data_end;
} RMDemuxContext;

// FROM: libavformat/rm.c
extern const char * const ff_rm_metadata[4];
const char * const ff_rm_metadata[4] = {
    "title",
    "author",
    "copyright",
    "comment"
};

// FROM: libavformat/rm.c
extern const AVCodecTag ff_rm_codec_tags[];
const AVCodecTag ff_rm_codec_tags[] = {
    { AV_CODEC_ID_RV10,   MKTAG('R','V','1','0') },
    { AV_CODEC_ID_RV20,   MKTAG('R','V','2','0') },
    { AV_CODEC_ID_RV20,   MKTAG('R','V','T','R') },
    { AV_CODEC_ID_RV30,   MKTAG('R','V','3','0') },
    { AV_CODEC_ID_RV40,   MKTAG('R','V','4','0') },
    { AV_CODEC_ID_AC3,    MKTAG('d','n','e','t') },
    { AV_CODEC_ID_RA_144, MKTAG('l','p','c','J') },
    { AV_CODEC_ID_RA_288, MKTAG('2','8','_','8') },
    { AV_CODEC_ID_COOK,   MKTAG('c','o','o','k') },
    { AV_CODEC_ID_ATRAC3, MKTAG('a','t','r','c') },
    { AV_CODEC_ID_SIPR,   MKTAG('s','i','p','r') },
    { AV_CODEC_ID_AAC,    MKTAG('r','a','a','c') },
    { AV_CODEC_ID_AAC,    MKTAG('r','a','c','p') },
    { AV_CODEC_ID_RALF,   MKTAG('L','S','D',':') },
    { AV_CODEC_ID_CLEARVIDEO, MKTAG('C','L','V','1') },
    { AV_CODEC_ID_NONE },
};

// External function declarations (from FFmpeg libraries)
void avpriv_set_pts_info(AVStream *s, int pts_wrap_bits, unsigned int pts_num, unsigned int pts_den);
int64_t avio_tell(AVIOContext *s);
unsigned int avio_rb32(AVIOContext *s);
unsigned int avio_rb16(AVIOContext *s);
int avio_r8(AVIOContext *s);
uint64_t avio_rb64(AVIOContext *s);
unsigned int avio_rl32(AVIOContext *s);
int64_t avio_seek(AVIOContext *s, int64_t offset, int whence);
int64_t avio_skip(AVIOContext *s, int64_t offset);
int avio_feof(AVIOContext *s);
int avio_get_str(AVIOContext *pb, int maxlen, char *buf, int buflen);
void av_log(void *avcl, int level, const char *fmt, ...);
int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags);
int av_reduce(int *dst_num, int *dst_den, int64_t num, int64_t den, int64_t max);
AVStream *avformat_new_stream(AVFormatContext *s, const AVCodec *c);
void avpriv_request_sample(void *avc, const char *msg, ...);
char *av_fourcc_make_string(char *buf, uint32_t fourcc);
int64_t av_rescale(int64_t a, int64_t b, int64_t c);
int ffio_ensure_seekback(AVIOContext *s, int64_t buf_size);
void ff_free_stream(AVFormatContext *s, AVStream *st);
enum AVCodecID ff_codec_get_id(const AVCodecTag *tags, unsigned int tag);
RMStream *ff_rm_alloc_rmstream(void);
void ff_rm_free_rmstream(RMStream *rms);
int ff_get_extradata(AVFormatContext *s, AVCodecParameters *par, AVIOContext *pb, int size);
int64_t avio_size(AVIOContext *s);

// FROM: libavformat/rmdec.c
static int rm_read_close(AVFormatContext *s);
static int rm_read_audio_stream_info(AVFormatContext *s, AVIOContext *pb, AVStream *st, RMStream *ast, int read_all);
static int rm_read_multi(AVFormatContext *s, AVIOContext *pb, AVStream *st, char *mime);
static int rm_read_header_old(AVFormatContext *s);
static int rm_read_index(AVFormatContext *s);

// FROM: libavformat/rmdec.c
static inline void get_strl(AVIOContext *pb, char *buf, int buf_size, int len)
{
    int read = avio_get_str(pb, len, buf, buf_size);

    if (read > 0)
        avio_skip(pb, len - read);
}

// FROM: libavformat/rmdec.c
static void get_str8(AVIOContext *pb, char *buf, int buf_size)
{
    get_strl(pb, buf, buf_size, avio_r8(pb));
}

// FROM: libavformat/rmdec.c
static int rm_read_extradata(AVFormatContext *s, AVIOContext *pb, AVCodecParameters *par, unsigned size)
{
    if (size >= 1<<24) {
        av_log(s, AV_LOG_ERROR, "extradata size %u too large\n", size);
        return -1;
    }
    if (ff_get_extradata(s, par, pb, size) < 0)
        return AVERROR(ENOMEM);
    return 0;
}

// FROM: libavformat/rmdec.c
static void rm_read_metadata(AVFormatContext *s, AVIOContext *pb, int wide)
{
    char buf[1024];
    int i;

    for (i=0; i<FF_ARRAY_ELEMS(ff_rm_metadata); i++) {
        int len = wide ? avio_rb16(pb) : avio_r8(pb);
        if (len > 0) {
            get_strl(pb, buf, sizeof(buf), len);
            av_dict_set(&s->metadata, ff_rm_metadata[i], buf, 0);
        }
    }
}

// FROM: libavformat/rmdec.c
static int rm_read_header_old(AVFormatContext *s)
{
    RMDemuxContext *rm = s->priv_data;
    AVStream *st;

    rm->old_format = 1;
    st = avformat_new_stream(s, NULL);
    if (!st)
        return -1;
    st->priv_data = ff_rm_alloc_rmstream();
    if (!st->priv_data)
        return AVERROR(ENOMEM);
    return rm_read_audio_stream_info(s, s->pb, st, st->priv_data, 1);
}

// FROM: libavformat/rmdec.c
static int rm_read_audio_stream_info(AVFormatContext *s, AVIOContext *pb,
                                     AVStream *st, RMStream *ast, int read_all)
{
    char buf[256];
    uint32_t version;
    int ret;

    /* ra type header */
    version = avio_rb16(pb); /* version */
    if (version == 3) {
        unsigned bytes_per_minute;
        int header_size = avio_rb16(pb);
        int64_t startpos = avio_tell(pb);
        avio_skip(pb, 8);
        bytes_per_minute = avio_rb16(pb);
        avio_skip(pb, 4);
        rm_read_metadata(s, pb, 0);
        if ((startpos + header_size) >= avio_tell(pb) + 2) {
            avio_r8(pb);
            get_str8(pb, buf, sizeof(buf));
        }
        if ((startpos + header_size) > avio_tell(pb))
            avio_skip(pb, header_size + startpos - avio_tell(pb));
        if (bytes_per_minute)
            st->codecpar->bit_rate = 8LL * bytes_per_minute / 60;
        st->codecpar->sample_rate = 8000;
        st->codecpar->channels = 1;
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = AV_CODEC_ID_RA_144;
    } else {
        int flavor, sub_packet_h, coded_framesize, sub_packet_size;
        int codecdata_length;
        unsigned bytes_per_minute;
        avio_skip(pb, 2); /* unused */
        avio_rb32(pb); /* .ra4 */
        avio_rb32(pb); /* data size */
        avio_rb16(pb); /* version2 */
        avio_rb32(pb); /* header size */
        flavor= avio_rb16(pb); /* add codec info / flavor */
        ast->coded_framesize = coded_framesize = avio_rb32(pb); /* coded frame size */
        avio_rb32(pb); /* ??? */
        bytes_per_minute = avio_rb32(pb);
        if (version == 4) {
            if (bytes_per_minute)
                st->codecpar->bit_rate = 8LL * bytes_per_minute / 60;
        }
        avio_rb32(pb); /* ??? */
        ast->sub_packet_h = sub_packet_h = avio_rb16(pb); /* 1 */
        st->codecpar->block_align= avio_rb16(pb); /* frame size */
        ast->sub_packet_size = sub_packet_size = avio_rb16(pb); /* sub packet size */
        avio_rb16(pb); /* ??? */
        if (version == 5) {
            avio_rb16(pb); avio_rb16(pb); avio_rb16(pb);
        }
        st->codecpar->sample_rate = avio_rb16(pb);
        avio_rb32(pb);
        st->codecpar->channels = avio_rb16(pb);
        if (version == 5) {
            ast->deint_id = avio_rl32(pb);
            avio_r8(pb);
            avio_r8(pb);
            avio_r8(pb);
            avio_r8(pb);
        } else {
            get_str8(pb, buf, sizeof(buf)); /* desc */
            ast->deint_id = AV_RL32(buf);
            get_str8(pb, buf, sizeof(buf)); /* desc */
        }
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_tag  = AV_RL32(buf);
        st->codecpar->codec_id   = ff_codec_get_id(ff_rm_codec_tags,
                                                   st->codecpar->codec_tag);

        switch (st->codecpar->codec_id) {
        case AV_CODEC_ID_AC3:
            st->need_parsing = AVSTREAM_PARSE_FULL;
            break;
        case AV_CODEC_ID_RA_288:
            st->codecpar->extradata_size= 0;
            ast->audio_framesize = st->codecpar->block_align;
            st->codecpar->block_align = coded_framesize;
            break;
        case AV_CODEC_ID_COOK:
            st->need_parsing = AVSTREAM_PARSE_HEADERS;
        case AV_CODEC_ID_ATRAC3:
        case AV_CODEC_ID_SIPR:
            if (read_all) {
                codecdata_length = 0;
            } else {
                avio_rb16(pb); avio_r8(pb);
                if (version == 5)
                    avio_r8(pb);
                codecdata_length = avio_rb32(pb);
                if(codecdata_length + (1U << 16) <= (unsigned)codecdata_length){
                    av_log(s, AV_LOG_ERROR, "codecdata_length too large\n");
                    return -1;
                }
            }

            ast->audio_framesize = st->codecpar->block_align;
            if (st->codecpar->codec_id == AV_CODEC_ID_SIPR) {
                if (flavor > 3) {
                    av_log(s, AV_LOG_ERROR, "bad SIPR file flavor %d\n",
                           flavor);
                    return -1;
                }
                st->need_parsing = AVSTREAM_PARSE_FULL_RAW;
            } else {
                if(sub_packet_size <= 0){
                    av_log(s, AV_LOG_ERROR, "sub_packet_size is invalid\n");
                    return -1;
                }
                st->codecpar->block_align = ast->sub_packet_size;
            }
            if ((ret = rm_read_extradata(s, pb, st->codecpar, codecdata_length)) < 0)
                return ret;

            break;
        case AV_CODEC_ID_AAC:
            avio_rb16(pb); avio_r8(pb);
            if (version == 5)
                avio_r8(pb);
            codecdata_length = avio_rb32(pb);
            if(codecdata_length + (1U << 16) <= (unsigned)codecdata_length){
                av_log(s, AV_LOG_ERROR, "codecdata_length too large\n");
                return -1;
            }
            if (codecdata_length >= 1) {
                avio_r8(pb);
                if ((ret = rm_read_extradata(s, pb, st->codecpar, codecdata_length - 1)) < 0)
                    return ret;
            }
            break;
        }
        if (read_all) {
            avio_r8(pb);
            avio_r8(pb);
            avio_r8(pb);
            rm_read_metadata(s, pb, 0);
        }
    }
    return 0;
}

// FROM: libavformat/rmdec.c
static int rm_read_index(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    unsigned int size, n_pkts, str_id, next_off, n, pos, pts;
    AVStream *st;

    do {
        if (avio_rl32(pb) != MKTAG('I','N','D','X'))
            return -1;
        size     = avio_rb32(pb);
        if (size < 20)
            return -1;
        avio_skip(pb, 2);
        n_pkts   = avio_rb32(pb);
        str_id   = avio_rb16(pb);
        next_off = avio_rb32(pb);
        for (n = 0; n < s->nb_streams; n++)
            if (s->streams[n]->id == str_id) {
                st = s->streams[n];
                break;
            }
        if (n == s->nb_streams) {
            av_log(s, AV_LOG_ERROR,
                   "Invalid stream index %d for index at pos %"PRId64"\n",
                   str_id, avio_tell(pb));
            goto skip;
        } else if ((avio_size(pb) - avio_tell(pb)) / 14 < n_pkts) {
            av_log(s, AV_LOG_ERROR,
                   "Nr. of packets in packet index for stream index %d "
                   "exceeds filesize (%"PRId64" at %"PRId64" = %"PRId64")\n",
                   str_id, avio_size(pb), avio_tell(pb),
                   (avio_size(pb) - avio_tell(pb)) / 14);
            goto skip;
        }

        for (n = 0; n < n_pkts; n++) {
            avio_skip(pb, 2);
            pts = avio_rb32(pb);
            pos = avio_rb32(pb);
            avio_skip(pb, 4); /* packet no. */
        }

skip:
        if (next_off && avio_tell(pb) < next_off &&
            avio_seek(pb, next_off, SEEK_SET) < 0) {
            av_log(s, AV_LOG_ERROR,
                   "Non-linear index detected, not supported\n");
            return -1;
        }
    } while (next_off);

    return 0;
}

// FROM: libavformat/rmdec.c
static int rm_read_close(AVFormatContext *s)
{
    int i;

    for (i=0;i<s->nb_streams;i++)
        ff_rm_free_rmstream(s->streams[i]->priv_data);

    return 0;
}

// FROM: libavformat/rmdec.c
int ff_rm_read_mdpr_codecdata(AVFormatContext *s, AVIOContext *pb,
                              AVStream *st, RMStream *rst,
                              unsigned int codec_data_size, const uint8_t *mime)
{
    unsigned int v;
    int size;
    int64_t codec_pos;
    int ret;

    if (codec_data_size > INT_MAX)
        return AVERROR_INVALIDDATA;
    if (codec_data_size == 0)
        return 0;

    avpriv_set_pts_info(st, 64, 1, 1000);
    codec_pos = avio_tell(pb);
    v = avio_rb32(pb);

    if (v == MKTAG(0xfd, 'a', 'r', '.')) {
        /* ra type header */
        if (rm_read_audio_stream_info(s, pb, st, rst, 0))
            return -1;
    } else if (v == MKBETAG('L', 'S', 'D', ':')) {
        avio_seek(pb, -4, SEEK_CUR);
        if ((ret = rm_read_extradata(s, pb, st->codecpar, codec_data_size)) < 0)
            return ret;

        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_tag  = AV_RL32(st->codecpar->extradata);
        st->codecpar->codec_id   = ff_codec_get_id(ff_rm_codec_tags,
                                                st->codecpar->codec_tag);
    } else if(mime && !strcmp(mime, "logical-fileinfo")){
        int stream_count, rule_count, property_count, i;
        ff_free_stream(s, st);
        if (avio_rb16(pb) != 0) {
            av_log(s, AV_LOG_WARNING, "Unsupported version\n");
            goto skip;
        }
        stream_count = avio_rb16(pb);
        avio_skip(pb, 6*stream_count);
        rule_count = avio_rb16(pb);
        avio_skip(pb, 2*rule_count);
        property_count = avio_rb16(pb);
        for(i=0; i<property_count; i++){
            uint8_t name[128], val[128];
            avio_rb32(pb);
            if (avio_rb16(pb) != 0) {
                av_log(s, AV_LOG_WARNING, "Unsupported Name value property version\n");
                goto skip; //FIXME skip just this one
            }
            get_str8(pb, name, sizeof(name));
            switch(avio_rb32(pb)) {
            case 2: get_strl(pb, val, sizeof(val), avio_rb16(pb));
                av_dict_set(&s->metadata, name, val, 0);
                break;
            default: avio_skip(pb, avio_rb16(pb));
            }
        }
    } else {
        int fps;
        if (avio_rl32(pb) != MKTAG('V', 'I', 'D', 'O')) {
        fail1:
            av_log(s, AV_LOG_WARNING, "Unsupported stream type %08x\n", v);
            goto skip;
        }
        st->codecpar->codec_tag = avio_rl32(pb);
        st->codecpar->codec_id  = ff_codec_get_id(ff_rm_codec_tags,
                                                  st->codecpar->codec_tag);
        av_log(s, AV_LOG_TRACE, "%"PRIX32" %X\n",
               st->codecpar->codec_tag, MKTAG('R', 'V', '2', '0'));
        if (st->codecpar->codec_id == AV_CODEC_ID_NONE)
            goto fail1;
        st->codecpar->width  = avio_rb16(pb);
        st->codecpar->height = avio_rb16(pb);
        avio_skip(pb, 2); // looks like bits per sample
        avio_skip(pb, 4); // always zero?
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->need_parsing = AVSTREAM_PARSE_TIMESTAMPS;
        fps = avio_rb32(pb);

        if ((ret = rm_read_extradata(s, pb, st->codecpar, codec_data_size - (avio_tell(pb) - codec_pos))) < 0)
            return ret;

        if (fps > 0) {
            av_reduce(&st->avg_frame_rate.den, &st->avg_frame_rate.num,
                      0x10000, fps, (1 << 30) - 1);
#if FF_API_R_FRAME_RATE
            st->r_frame_rate = st->avg_frame_rate;
#endif
        } else if (s->error_recognition & AV_EF_EXPLODE) {
            av_log(s, AV_LOG_ERROR, "Invalid framerate\n");
            return AVERROR_INVALIDDATA;
        }
    }

skip:
    /* skip codec info */
    size = avio_tell(pb) - codec_pos;
    if (codec_data_size >= size) {
        avio_skip(pb, codec_data_size - size);
    } else {
        av_log(s, AV_LOG_WARNING, "codec_data_size %u < size %d\n", codec_data_size, size);
    }

    return 0;
}

// FROM: libavformat/rmdec.c
static int rm_read_multi(AVFormatContext *s, AVIOContext *pb,
                         AVStream *st, char *mime)
{
    int number_of_streams = avio_rb16(pb);
    int number_of_mdpr;
    int i, ret;
    unsigned size2;
    for (i = 0; i<number_of_streams; i++)
        avio_rb16(pb);
    number_of_mdpr = avio_rb16(pb);
    if (number_of_mdpr != 1) {
        avpriv_request_sample(s, "MLTI with multiple (%d) MDPR", number_of_mdpr);
    }
    for (i = 0; i < number_of_mdpr; i++) {
        AVStream *st2;
        if (i > 0) {
            st2 = avformat_new_stream(s, NULL);
            if (!st2) {
                ret = AVERROR(ENOMEM);
                return ret;
            }
            st2->id = st->id + (i<<16);
            st2->codecpar->bit_rate = st->codecpar->bit_rate;
            st2->start_time = st->start_time;
            st2->duration   = st->duration;
            st2->codecpar->codec_type = AVMEDIA_TYPE_DATA;
            st2->priv_data = ff_rm_alloc_rmstream();
            if (!st2->priv_data)
                return AVERROR(ENOMEM);
        } else
            st2 = st;

        size2 = avio_rb32(pb);
        ret = ff_rm_read_mdpr_codecdata(s, s->pb, st2, st2->priv_data,
                                        size2, mime);
        if (ret < 0)
            return ret;
    }
    return 0;
}

// FROM: libavformat/rmdec.c
static int rm_read_header(AVFormatContext *s)
{
    RMDemuxContext *rm = s->priv_data;
    AVStream *st;
    AVIOContext *pb = s->pb;
    unsigned int tag;
    int tag_size;
    unsigned int start_time, duration;
    unsigned int data_off = 0, indx_off = 0;
    char buf[128], mime[128];
    int flags = 0;
    int ret = -1;
    unsigned size, v;
    int64_t codec_pos;

    tag = avio_rl32(pb);
    if (tag == MKTAG('.', 'r', 'a', 0xfd)) {
        /* very old .ra format */
        return rm_read_header_old(s);
    } else if (tag != MKTAG('.', 'R', 'M', 'F')) {
        return AVERROR(EIO);
    }

    tag_size = avio_rb32(pb);
    avio_skip(pb, tag_size - 8);

    for(;;) {
        if (avio_feof(pb))
            goto fail;
        tag = avio_rl32(pb);
        tag_size = avio_rb32(pb);
        avio_rb16(pb);
        av_log(s, AV_LOG_TRACE, "tag=%s size=%d\n",
               av_fourcc_make_string((char[32]){0}, tag), tag_size);
        if (tag_size < 10 && tag != MKTAG('D', 'A', 'T', 'A'))
            goto fail;
        switch(tag) {
        case MKTAG('P', 'R', 'O', 'P'):
            /* file header */
            avio_rb32(pb); /* max bit rate */
            avio_rb32(pb); /* avg bit rate */
            avio_rb32(pb); /* max packet size */
            avio_rb32(pb); /* avg packet size */
            avio_rb32(pb); /* nb packets */
            duration = avio_rb32(pb); /* duration */
            s->duration = av_rescale(duration, AV_TIME_BASE, 1000);
            avio_rb32(pb); /* preroll */
            indx_off = avio_rb32(pb); /* index offset */
            data_off = avio_rb32(pb); /* data offset */
            avio_rb16(pb); /* nb streams */
            flags = avio_rb16(pb); /* flags */
            break;
        case MKTAG('C', 'O', 'N', 'T'):
            rm_read_metadata(s, pb, 1);
            break;
        case MKTAG('M', 'D', 'P', 'R'):
            st = avformat_new_stream(s, NULL);
            if (!st) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            st->id = avio_rb16(pb);
            avio_rb32(pb); /* max bit rate */
            st->codecpar->bit_rate = avio_rb32(pb); /* bit rate */
            avio_rb32(pb); /* max packet size */
            avio_rb32(pb); /* avg packet size */
            start_time = avio_rb32(pb); /* start time */
            avio_rb32(pb); /* preroll */
            duration = avio_rb32(pb); /* duration */
            st->start_time = start_time;
            st->duration = duration;
            if(duration>0)
                s->duration = AV_NOPTS_VALUE;
            get_str8(pb, buf, sizeof(buf)); /* desc */
            get_str8(pb, mime, sizeof(mime)); /* mimetype */
            st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
            st->priv_data = ff_rm_alloc_rmstream();
            if (!st->priv_data)
                return AVERROR(ENOMEM);

            size = avio_rb32(pb);
            codec_pos = avio_tell(pb);

            ffio_ensure_seekback(pb, 4);
            v = avio_rb32(pb);
            if (v == MKBETAG('M', 'L', 'T', 'I')) {
                ret = rm_read_multi(s, s->pb, st, mime);
                if (ret < 0)
                    goto fail;
                avio_seek(pb, codec_pos + size, SEEK_SET);
            } else {
                avio_skip(pb, -4);
                if (ff_rm_read_mdpr_codecdata(s, s->pb, st, st->priv_data,
                                              size, mime) < 0)
                    goto fail;
            }

            break;
        case MKTAG('D', 'A', 'T', 'A'):
            goto header_end;
        default:
            /* unknown tag: skip it */
            avio_skip(pb, tag_size - 10);
            break;
        }
    }
 header_end:
    rm->nb_packets = avio_rb32(pb); /* number of packets */
    if (!rm->nb_packets && (flags & 4))
        rm->nb_packets = 3600 * 25;
    avio_rb32(pb); /* next data header */

    if (!data_off)
        data_off = avio_tell(pb) - 18;
    if (indx_off && (pb->seekable & AVIO_SEEKABLE_NORMAL) &&
        !(s->flags & AVFMT_FLAG_IGNIDX) &&
        avio_seek(pb, indx_off, SEEK_SET) >= 0) {
        rm_read_index(s);
        avio_seek(pb, data_off + 18, SEEK_SET);
    }

    return 0;

fail:
    rm_read_close(s);
    return ret;
}

// FROM: libavformat/rmdec.c
static int ivr_read_header(AVFormatContext *s)
{
    unsigned tag, type, len, tlen, value;
    int i, j, n, count, nb_streams = 0, ret;
    uint8_t key[256], val[256];
    AVIOContext *pb = s->pb;
    AVStream *st;
    int64_t pos, offset, temp;

    pos = avio_tell(pb);
    tag = avio_rl32(pb);
    if (tag == MKTAG('.','R','1','M')) {
        if (avio_rb16(pb) != 1)
            return AVERROR_INVALIDDATA;
        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;
        len = avio_rb32(pb);
        avio_skip(pb, len);
        avio_skip(pb, 5);
        temp = avio_rb64(pb);
        while (!avio_feof(pb) && temp) {
            offset = temp;
            temp = avio_rb64(pb);
        }
        avio_skip(pb, offset - avio_tell(pb));
        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;
        len = avio_rb32(pb);
        avio_skip(pb, len);
        if (avio_r8(pb) != 2)
            return AVERROR_INVALIDDATA;
        avio_skip(pb, 16);
        pos = avio_tell(pb);
        tag = avio_rl32(pb);
    }

    if (tag != MKTAG('.','R','E','C'))
        return AVERROR_INVALIDDATA;

    if (avio_r8(pb) != 0)
        return AVERROR_INVALIDDATA;
    count = avio_rb32(pb);
    for (i = 0; i < count; i++) {
        if (avio_feof(pb))
            return AVERROR_INVALIDDATA;

        type = avio_r8(pb);
        tlen = avio_rb32(pb);
        avio_get_str(pb, tlen, key, sizeof(key));
        len = avio_rb32(pb);
        if (type == 5) {
            avio_get_str(pb, len, val, sizeof(val));
            av_log(s, AV_LOG_DEBUG, "%s = '%s'\n", key, val);
        } else if (type == 4) {
            av_log(s, AV_LOG_DEBUG, "%s = '0x", key);
            for (j = 0; j < len; j++) {
                if (avio_feof(pb))
                    return AVERROR_INVALIDDATA;
                av_log(s, AV_LOG_DEBUG, "%X", avio_r8(pb));
            }
            av_log(s, AV_LOG_DEBUG, "'\n");
        } else if (len == 4 && type == 3 && !strncmp(key, "StreamCount", tlen)) {
            nb_streams = value = avio_rb32(pb);
        } else if (len == 4 && type == 3) {
            value = avio_rb32(pb);
            av_log(s, AV_LOG_DEBUG, "%s = %d\n", key, value);
        } else {
            av_log(s, AV_LOG_DEBUG, "Skipping unsupported key: %s\n", key);
            avio_skip(pb, len);
        }
    }

    for (n = 0; n < nb_streams; n++) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        st->priv_data = ff_rm_alloc_rmstream();
        if (!st->priv_data)
            return AVERROR(ENOMEM);

        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;

        count = avio_rb32(pb);
        for (i = 0; i < count; i++) {
            if (avio_feof(pb))
                return AVERROR_INVALIDDATA;

            type = avio_r8(pb);
            tlen  = avio_rb32(pb);
            avio_get_str(pb, tlen, key, sizeof(key));
            len  = avio_rb32(pb);
            if (type == 5) {
                avio_get_str(pb, len, val, sizeof(val));
                av_log(s, AV_LOG_DEBUG, "%s = '%s'\n", key, val);
            } else if (type == 4 && !strncmp(key, "OpaqueData", tlen)) {
                ret = ffio_ensure_seekback(pb, 4);
                if (ret < 0)
                    return ret;
                if (avio_rb32(pb) == MKBETAG('M', 'L', 'T', 'I')) {
                    ret = rm_read_multi(s, pb, st, NULL);
                } else {
                    avio_seek(pb, -4, SEEK_CUR);
                    ret = ff_rm_read_mdpr_codecdata(s, pb, st, st->priv_data, len, NULL);
                }

                if (ret < 0)
                    return ret;
            } else if (type == 4) {
                int j;

                av_log(s, AV_LOG_DEBUG, "%s = '0x", key);
                for (j = 0; j < len; j++)
                    av_log(s, AV_LOG_DEBUG, "%X", avio_r8(pb));
                av_log(s, AV_LOG_DEBUG, "'\n");
            } else if (len == 4 && type == 3 && !strncmp(key, "Duration", tlen)) {
                st->duration = avio_rb32(pb);
            } else if (len == 4 && type == 3) {
                value = avio_rb32(pb);
                av_log(s, AV_LOG_DEBUG, "%s = %d\n", key, value);
            } else {
                av_log(s, AV_LOG_DEBUG, "Skipping unsupported key: %s\n", key);
                avio_skip(pb, len);
            }
        }
    }

    if (avio_r8(pb) != 6)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 12);
    avio_skip(pb, avio_rb64(pb) + pos - avio_tell(s->pb));
    if (avio_r8(pb) != 8)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 8);

    return 0;
}
