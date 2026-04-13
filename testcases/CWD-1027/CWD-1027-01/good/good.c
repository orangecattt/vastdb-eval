#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <errno.h>

#define AV_HAVE_BIGENDIAN 0

#define LIBAVUTIL_VERSION_MAJOR 57
#define LIBAVUTIL_VERSION_MINOR 28
#define LIBAVUTIL_VERSION_MICRO 100

#if defined(__GNUC__) || defined(__clang__)
    #define av_malloc_attrib __attribute__((__malloc__))
    #define av_alloc_size(...) __attribute__((alloc_size(__VA_ARGS__)))
    #define av_printf_format(fmtp, firstp) __attribute__((format(__printf__, fmtp, firstp)))
    #define av_used __attribute__((unused))
    #define av_cold __attribute__((cold))
#else
    #define av_malloc_attrib
    #define av_alloc_size(...)
    #define av_printf_format(fmtp, firstp)
    #define av_used
    #define av_cold
#endif

#define AVERROR(e) (-(e))
#define ENOMEM 12
#define EINVAL 22

#define MKTAG(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

#define AVERROR_BUG                (-MKTAG( 'B','U','G','!'))
#define AVERROR_BUFFER_TOO_SMALL   (-MKTAG( 'B','U','F','S'))
#define AVERROR_DECODER_NOT_FOUND  (-MKTAG(0xF8,'D','E','C'))
#define AVERROR_DEMUXER_NOT_FOUND  (-MKTAG(0xF8,'D','E','M'))
#define AVERROR_ENCODER_NOT_FOUND  (-MKTAG(0xF8,'E','N','C'))
#define AVERROR_EOF                (-MKTAG( 'E','O','F',' '))
#define AVERROR_EXIT               (-MKTAG( 'E','X','I','T'))
#define AVERROR_EXTERNAL           (-MKTAG( 'E','X','T',' '))
#define AVERROR_FILTER_NOT_FOUND   (-MKTAG(0xF8,'F','I','L'))
#define AVERROR_INVALIDDATA        (-MKTAG( 'I','N','D','A'))
#define AVERROR_MUXER_NOT_FOUND    (-MKTAG(0xF8,'M','U','X'))
#define AVERROR_OPTION_NOT_FOUND   (-MKTAG(0xF8,'O','P','T'))
#define AVERROR_PATCHWELCOME       (-MKTAG( 'P','A','W','E'))
#define AVERROR_PROTOCOL_NOT_FOUND (-MKTAG(0xF8,'P','R','O'))
#define AVERROR_STREAM_NOT_FOUND   (-MKTAG(0xF8,'S','T','R'))
#define AVERROR_BUG2               (-MKTAG( 'B','U','G',' '))
#define AVERROR_UNKNOWN            (-MKTAG( 'U','N','K','N'))

#define AV_ERROR_MAX_STRING_SIZE 64

#ifndef M_E
#define M_E            2.7182818284590452354
#endif
#ifndef M_LN2
#define M_LN2          0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10         2.30258509299404568402
#endif
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2         1.57079632679489661923
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2      0.70710678118654752440
#endif
#ifndef M_SQRT2
#define M_SQRT2        1.41421356237309504880
#endif

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_YUYV422,
    AV_PIX_FMT_RGB24,
    AV_PIX_FMT_BGR24,
    AV_PIX_FMT_YUV422P,
    AV_PIX_FMT_YUV444P,
};

enum AVPictureType {
    AV_PICTURE_TYPE_NONE = 0,
    AV_PICTURE_TYPE_I,
    AV_PICTURE_TYPE_P,
    AV_PICTURE_TYPE_B,
    AV_PICTURE_TYPE_S,
    AV_PICTURE_TYPE_SI,
    AV_PICTURE_TYPE_SP,
    AV_PICTURE_TYPE_BI,
};

enum AVColorRange {
    AVCOL_RANGE_NB = 0,
};

enum AVColorPrimaries {
    AVCOL_PRI_NB = 0,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_NB = 0,
};

enum AVColorSpace {
    AVCOL_SPC_NB = 0,
};

enum AVChromaLocation {
    AVCHROMA_LOC_NB = 0,
};

typedef struct AVRational{
    int num;
    int den;
} AVRational;

typedef struct AVOption AVOption;

typedef struct AVClass {
    const char* class_name;
    const char* (*item_name)(void* ctx);
    const struct AVOption *option;
    int version;
    int log_level_offset_offset;
    int parent_log_context_offset;
    void* (*child_next)(void *obj, void *prev);
    const struct AVClass* (*child_class_next)(const struct AVClass *prev);
    int category;
    int (*get_category)(void* ctx);
    int (*query_ranges)(void **, void *obj, const char *key, int flags);
} AVClass;

typedef struct AVBuffer AVBuffer;
typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    size_t size;
    int flags;
} AVBufferRef;

typedef struct AVDictionary AVDictionary;

typedef struct AVFrame {
    uint8_t *data[8];
    int linesize[8];
    uint8_t **extended_data;
    int width, height;
    int nb_samples;
    int format;
    int key_frame;
    enum AVPictureType pict_type;
    enum AVColorRange color_range;
    enum AVColorPrimaries color_primaries;
    enum AVColorTransferCharacteristic color_trc;
    enum AVColorSpace colorspace;
    enum AVChromaLocation chroma_location;
    int channel_layout;
    int channels;
    int sample_rate;
    struct AVFrame **side_data;
    int nb_side_data;
    int64_t pts;
    int64_t pkt_dts;
    int64_t coded_picture_number;
    int64_t display_picture_number;
    int quality;
    struct AVBufferRef *private_ref;
} AVFrame;

#define LIBAVFILTER_VERSION_MAJOR 8
#define LIBAVFILTER_VERSION_MINOR 44
#define LIBAVFILTER_VERSION_MICRO 100

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterInternal AVFilterInternal;
typedef struct AVFilterCommand AVFilterCommand;

struct AVFilterPad {
    const char *name;
    enum AVMediaType type;
    AVFrame *(*get_video_buffer)(AVFilterLink *link, int w, int h);
    AVFrame *(*get_audio_buffer)(AVFilterLink *link, int nb_samples);
    int (*filter_frame)(AVFilterLink *link, AVFrame *frame);
    int (*poll_frame)(AVFilterLink *link);
    int (*request_frame)(AVFilterLink *link);
    int (*config_props)(AVFilterLink *link);
    int needs_fifo;
    int needs_writable;
};

struct AVFilterContext {
    const AVClass *av_class;
    const struct AVFilter *filter;
    char *name;
    AVFilterPad   *input_pads;
    AVFilterLink **inputs;
    unsigned    nb_inputs;
    AVFilterPad   *output_pads;
    AVFilterLink **outputs;
    unsigned    nb_outputs;
    void *priv;
    struct AVFilterGraph *graph;
    int thread_type;
    AVFilterInternal *internal;
    AVFilterCommand *command_queue;
    char *enable_str;
    void *enable;
    double *var_values;
    int is_disabled;
    AVBufferRef *hw_device_ctx;
    int nb_threads;
    unsigned ready;
    int extra_hw_frames;
};

struct AVFilterLink {
    AVFilterContext *src;
    AVFilterPad *srcpad;
    AVFilterContext *dst;
    AVFilterPad *dstpad;
    enum AVMediaType type;
    int w;
    int h;
    AVRational sample_aspect_ratio;
    uint64_t channel_layout;
    int sample_rate;
    int format;
    AVRational time_base;
    AVFilterFormats *in_formats;
    AVFilterFormats *out_formats;
    AVFilterFormats  *in_samplerates;
    AVFilterFormats *out_samplerates;
    struct AVFilterChannelLayouts  *in_channel_layouts;
    struct AVFilterChannelLayouts *out_channel_layouts;
    int request_samples;
    enum {
        AVLINK_UNINIT = 0,
        AVLINK_STARTINIT,
        AVLINK_INIT
    } init_state;
    struct AVFilterGraph *graph;
    int64_t current_pts;
    int64_t current_pts_us;
    int age_index;
    AVRational frame_rate;
    AVFrame *partial_buf;
    int partial_buf_size;
    int min_samples;
    int max_samples;
    int channels;
    unsigned flags;
    int64_t frame_count_in, frame_count_out;
    void *frame_pool;
    int frame_wanted_out;
};

typedef struct AVFilter {
    const char *name;
    const char *description;
    const AVFilterPad *inputs;
    const AVFilterPad *outputs;
    const AVClass *priv_class;
    int flags;
    int (*preinit)(AVFilterContext *ctx);
    int (*init)(AVFilterContext *ctx);
    int (*init_dict)(AVFilterContext *ctx, AVDictionary **options);
    void (*uninit)(AVFilterContext *ctx);
    int (*query_formats)(AVFilterContext *);
    int priv_size;
    int flags_internal;
    struct AVFilter *next;
    int (*process_command)(AVFilterContext *, const char *cmd, const char *arg, char *res, int res_len, int flags);
    int (*init_opaque)(AVFilterContext *ctx, void *opaque);
    int (*activate)(AVFilterContext *ctx);
} AVFilter;

struct AVFilterInternal {
    void *execute;
};

struct AVFilterCommand {
    double time;
    char *command;
    char *arg;
    int flags;
    struct AVFilterCommand *next;
};

int ff_insert_pad(unsigned idx, unsigned *count, size_t padidx_off,
                   AVFilterPad **pads, AVFilterLink ***links,
                   AVFilterPad *newpad);

static inline int ff_insert_outpad(AVFilterContext *f, unsigned index,
                                    AVFilterPad *p)
{
    return ff_insert_pad(index, &f->nb_outputs, 8,
                  &f->output_pads, &f->outputs, p);
}

void *av_malloc(size_t size) av_malloc_attrib av_alloc_size(1);
void *av_mallocz(size_t size) av_malloc_attrib av_alloc_size(1);
av_alloc_size(1, 2) void *av_malloc_array(size_t nmemb, size_t size);
av_alloc_size(1, 2) void *av_mallocz_array(size_t nmemb, size_t size);
void *av_calloc(size_t nmemb, size_t size) av_malloc_attrib;
void *av_realloc(void *ptr, size_t size) av_alloc_size(2);
int av_reallocp(void *ptr, size_t size);
void *av_realloc_f(void *ptr, size_t nelem, size_t elsize);
av_alloc_size(2, 3) void *av_realloc_array(void *ptr, size_t nmemb, size_t size);
int av_reallocp_array(void *ptr, size_t nmemb, size_t size);
void *av_fast_realloc(void *ptr, unsigned int *size, size_t min_size);
void av_fast_malloc(void *ptr, unsigned int *size, size_t min_size);
void av_fast_mallocz(void *ptr, unsigned int *size, size_t min_size);
void av_free(void *ptr);
void av_freep(void *ptr);
char *av_strdup(const char *s) av_malloc_attrib;
char *av_strndup(const char *s, size_t len) av_malloc_attrib;
void *av_memdup(const void *p, size_t size);
void av_memcpy_backptr(uint8_t *dst, int back, int cnt);

char *av_asprintf(const char *fmt, ...) av_printf_format(1, 2);
char *av_strtok(char *s, const char *delim, char **saveptr);
int av_sscanf(const char *string, const char *format, ...);

#define AV_LOG_QUIET    -8
#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48

void av_log(void *avcl, int level, const char *fmt, ...) av_printf_format(3, 4);

#define MAX_SPLITS 16
#define MAX_BANDS (MAX_SPLITS + 1)

typedef struct BiquadContext {
    double a0, a1, a2;
    double b1, b2;
    double i1, i2;
    double o1, o2;
} BiquadContext;

typedef struct CrossoverChannel {
    BiquadContext lp[MAX_BANDS][4];
    BiquadContext hp[MAX_BANDS][4];
} CrossoverChannel;

typedef struct AudioCrossoverContext {
    const AVClass *class;
    char *splits_str;
    int order;
    int filter_count;
    int nb_splits;
    float *splits;
    CrossoverChannel *xover;
} AudioCrossoverContext;

static void set_lp(BiquadContext *b, float fc, float q, float sr);
static void set_hp(BiquadContext *b, float fc, float q, float sr);

static void set_lp(BiquadContext *b, float fc, float q, float sr)
{
    double omega = (2.0 * M_PI * fc / sr);
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = (sn / (2 * q));
    double inv = (1.0 / (1.0 + alpha));

    b->a2 = b->a0 = (inv * (1.0 - cs) * 0.5);
    b->a1 = b->a0 + b->a0;
    b->b1 = -2. * cs * inv;
    b->b2 = (1. - alpha) * inv;
}

static void set_hp(BiquadContext *b, float fc, float q, float sr)
{
    double omega = 2 * M_PI * fc / sr;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn / (2 * q);
    double inv = 1.0 / (1.0 + alpha);

    b->a0 = (inv * (1.0 + cs) * 0.5);
    b->a1 = -2. * b->a0;
    b->a2 = b->a0;
    b->b1 = -2. * cs * inv;
    b->b2 = (1. - alpha) * inv;
}

static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioCrossoverContext *s = ctx->priv;
    int ch, band, sample_rate = inlink->sample_rate;
    double q;

    s->xover = av_calloc(inlink->channels, sizeof(*s->xover));
    if (!s->xover)
        return AVERROR(ENOMEM);

    switch (s->order) {
    case 0:
        q = 0.5;
        s->filter_count = 1;
        break;
    case 1:
        q = M_SQRT1_2;
        s->filter_count = 2;
        break;
    case 2:
        q = 0.54;
        s->filter_count = 4;
        break;
    }

    for (ch = 0; ch < inlink->channels; ch++) {
        for (band = 0; band <= s->nb_splits; band++) {
            set_lp(&s->xover[ch].lp[band][0], s->splits[band], q, sample_rate);
            set_hp(&s->xover[ch].hp[band][0], s->splits[band], q, sample_rate);

            if (s->order > 1) {
                set_lp(&s->xover[ch].lp[band][1], s->splits[band], 1.34, sample_rate);
                set_hp(&s->xover[ch].hp[band][1], s->splits[band], 1.34, sample_rate);
                set_lp(&s->xover[ch].lp[band][2], s->splits[band],    q, sample_rate);
                set_hp(&s->xover[ch].hp[band][2], s->splits[band],    q, sample_rate);
                set_lp(&s->xover[ch].lp[band][3], s->splits[band], 1.34, sample_rate);
                set_hp(&s->xover[ch].hp[band][3], s->splits[band], 1.34, sample_rate);
            } else {
                set_lp(&s->xover[ch].lp[band][1], s->splits[band], q, sample_rate);
                set_hp(&s->xover[ch].hp[band][1], s->splits[band], q, sample_rate);
            }
        }
    }

    return 0;
}

static av_cold int init(AVFilterContext *ctx)
{
    AudioCrossoverContext *s = ctx->priv;
    char *p, *arg, *saveptr = NULL;
    int i, ret = 0;

    s->splits = av_calloc(MAX_SPLITS, sizeof(*s->splits));
    if (!s->splits)
        return AVERROR(ENOMEM);

    p = s->splits_str;
    for (i = 0; i < MAX_SPLITS; i++) {
        float freq;

        if (!(arg = av_strtok(p, " |", &saveptr)))
            break;

        p = NULL;

        av_sscanf(arg, "%f", &freq);
        if (freq <= 0) {
            av_log(ctx, AV_LOG_ERROR, "Frequency %f must be positive number.\n", freq);
            return AVERROR(EINVAL);
        }

        if (i > 0 && freq <= s->splits[i-1]) {
            av_log(ctx, AV_LOG_ERROR, "Frequency %f must be in increasing order.\n", freq);
            return AVERROR(EINVAL);
        }

        s->splits[i] = freq;
    }

    s->nb_splits = i;

    for (i = 0; i <= s->nb_splits; i++) {
        AVFilterPad pad  = { 0 };
        char *name;

        pad.type = AVMEDIA_TYPE_AUDIO;
        name = av_asprintf("out%d", ctx->nb_outputs);
        if (!name)
            return AVERROR(ENOMEM);
        pad.name = name;

        if ((ret = ff_insert_outpad(ctx, i, &pad)) < 0) {
            av_freep(&pad.name);
            return ret;
        }
    }

    return ret;
}

static av_cold void uninit(AVFilterContext *ctx)
{
    AudioCrossoverContext *s = ctx->priv;
    int i;

    av_freep(&s->splits);
    av_freep(&s->xover);

    for (i = 0; i < ctx->nb_outputs; i++)
        av_freep(&ctx->output_pads[i].name);
}
