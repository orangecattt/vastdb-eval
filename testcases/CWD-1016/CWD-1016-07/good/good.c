#include <stdint.h>
#include <stddef.h>

#define AV_NOPTS_VALUE          (-0x8000000000000000ULL)
#define AV_TIME_BASE            1000000
#define AV_TIME_BASE_Q          (AVRational){1, AV_TIME_BASE}
#define AVERROR_EOF             (-('E' | ('O' << 8) | ('F' << 16) | (0x54 << 24)))
#define AVERROR(code)           (-(code))
#define AVERROR_EAGAIN          11
#define AVERROR_ENOMEM          12
#define AVERROR_EINVAL          22
#define AV_LOG_ERROR            16
#define ENOMEM                  12

#define NULL_IF_CONFIG_SMALL(x) x

#define M_PI 3.14159265358979323846

typedef struct AVRational {
    int num;
    int den;
} AVRational;

static inline int FFMIN(int a, int b) { return ((a) < (b) ? (a) : (b)); }

#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define MKTAG(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

enum AVSampleFormat {
    AV_SAMPLE_FMT_NONE = -1,
    AV_SAMPLE_FMT_U8,
    AV_SAMPLE_FMT_S16,
    AV_SAMPLE_FMT_S32,
    AV_SAMPLE_FMT_FLT,
    AV_SAMPLE_FMT_DBL,
    AV_SAMPLE_FMT_U8P,
    AV_SAMPLE_FMT_S16P,
    AV_SAMPLE_FMT_S32P,
    AV_SAMPLE_FMT_FLTP,
    AV_SAMPLE_FMT_DBLP,
};

typedef struct AVFrame {
    uint8_t *data[8];
    uint8_t **extended_data;
    int nb_samples;
    int channels;
    int64_t pts;
    int format;
} AVFrame;

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterGraph   AVFilterGraph;
typedef struct FFFrameQueue    FFFrameQueue;

typedef struct FFFrameBucket {
    AVFrame *frame;
} FFFrameBucket;

typedef struct FFFrameQueueGlobal {
    char dummy;
} FFFrameQueueGlobal;

struct FFFrameQueue {
    FFFrameBucket *queue;
    size_t allocated;
    size_t tail;
    size_t queued;
    FFFrameBucket first_bucket;
    uint64_t total_frames_head;
    uint64_t total_frames_tail;
    uint64_t total_samples_head;
    uint64_t total_samples_tail;
    int samples_skipped;
};

struct AVFilterPad {
    const char *name;
    enum AVMediaType type;
    AVFrame *(*get_audio_buffer)(AVFilterLink *link, int nb_samples);
    int (*filter_frame)(AVFilterLink *link, AVFrame *frame);
    int (*poll_frame)(AVFilterLink *link);
    int (*request_frame)(AVFilterLink *link);
    int (*config_props)(AVFilterLink *link);
    int needs_fifo;
    int needs_writable;
};

struct AVFilterContext {
    const void *av_class;
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
    void *internal;
    struct AVFilterCommand *command_queue;
    char *enable_str;
    void *enable;
    double *var_values;
    int is_disabled;
    void *hw_device_ctx;
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
    void *in_formats;
    void *out_formats;
    void *in_samplerates;
    void *out_samplerates;
    void *in_channel_layouts;
    void *out_channel_layouts;
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
    void *hw_frames_ctx;
    /* Internal fields for FIFO */
    FFFrameQueue fifo;
    int status_in;
    int64_t status_in_pts;
    int status_out;
};

AVFrame *ff_get_audio_buffer(AVFilterLink *link, int nb_samples);

#define FFERROR_NOT_READY FFERRTAG('N','R','D','Y')

void ff_filter_set_ready(AVFilterContext *filter, unsigned priority);
int ff_inlink_process_commands(AVFilterLink *link, const AVFrame *frame);
int ff_inlink_evaluate_timeline_at_frame(AVFilterLink *link, const AVFrame *frame);
size_t ff_inlink_queued_frames(AVFilterLink *link);
int ff_inlink_check_available_frame(AVFilterLink *link);
int ff_inlink_queued_samples(AVFilterLink *link);
int ff_inlink_check_available_samples(AVFilterLink *link, unsigned min);
int ff_inlink_consume_frame(AVFilterLink *link, AVFrame **rframe);
int ff_inlink_consume_samples(AVFilterLink *link, unsigned min, unsigned max, AVFrame **rframe);
AVFrame *ff_inlink_peek_frame(AVFilterLink *link, size_t idx);
int ff_inlink_make_frame_writable(AVFilterLink *link, AVFrame **rframe);
int ff_inlink_acknowledge_status(AVFilterLink *link, int *rstatus, int64_t *rpts);
void ff_inlink_request_frame(AVFilterLink *link);
void ff_inlink_set_status(AVFilterLink *link, int status);
int ff_outlink_frame_wanted(AVFilterLink *link);
int ff_outlink_get_status(AVFilterLink *link);
void ff_outlink_set_status(AVFilterLink *link, int status, int64_t pts);
void ff_avfilter_link_set_in_status(AVFilterLink *link, int status, int64_t pts);

#define FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink) do { \
    int ret = ff_outlink_get_status(outlink); \
    if (ret) { \
        ff_inlink_set_status(inlink, ret); \
        return 0; \
    } \
} while (0)

#define FF_FILTER_FORWARD_STATUS_BACK_ALL(outlink, filter) do { \
    int ret = ff_outlink_get_status(outlink); \
    if (ret) { \
        unsigned i; \
        for (i = 0; i < filter->nb_inputs; i++) \
            ff_inlink_set_status(filter->inputs[i], ret); \
        return 0; \
    } \
} while (0)

#define FF_FILTER_FORWARD_STATUS(inlink, outlink) do { \
    int status; \
    int64_t pts; \
    if (ff_inlink_acknowledge_status(inlink, &status, &pts)) { \
        ff_outlink_set_status(outlink, status, pts); \
        return 0; \
    } \
} while (0)

#define FF_FILTER_FORWARD_STATUS_ALL(inlink, filter) do { \
    int status; \
    int64_t pts; \
    if (ff_inlink_acknowledge_status(inlink, &status, &pts)) { \
        unsigned i; \
        for (i = 0; i < filter->nb_outputs; i++) \
            ff_outlink_set_status(filter->outputs[i], status, pts); \
        return 0; \
    } \
} while (0)

#define FF_FILTER_FORWARD_WANTED(outlink, inlink) do { \
    if (ff_outlink_frame_wanted(outlink)) { \
        ff_inlink_request_frame(inlink); \
        return 0; \
    } \
} while (0)

int ff_filter_frame(AVFilterLink *link, AVFrame *frame);

enum CurveType { TRI, QSIN, ESIN, HSIN, LOG, IPAR, QUA, CUB, SQU, CBR, PAR, EXP, IQSIN, IHSIN, DESE, DESI, LOSI, NONE, NB_CURVES };

typedef struct AudioFadeContext {
    const void *class;
    int type;
    int curve, curve2;
    int64_t nb_samples;
    int64_t start_sample;
    int64_t duration;
    int64_t start_time;
    int overlap;
    int cf0_eof;
    int crossfade_is_over;
    int64_t pts;

    void (*fade_samples)(uint8_t **dst, uint8_t * const *src,
                         int nb_samples, int channels, int direction,
                         int64_t start, int64_t range, int curve);
    void (*crossfade_samples)(uint8_t **dst, uint8_t * const *cf0,
                              uint8_t * const *cf1,
                              int nb_samples, int channels,
                              int curve0, int curve1);
} AudioFadeContext;

static double fade_gain(int curve, int64_t index, int64_t range);

#define av_assert1(cond) ((void)0)

#define AV_OPT_FLAG_AUDIO_PARAM    0x0002
#define AV_OPT_FLAG_FILTERING_PARAM 0x1000
#define AV_OPT_TYPE_INT            1
#define AV_OPT_TYPE_INT64          2
#define AV_OPT_TYPE_DURATION       3
#define AV_OPT_TYPE_CONST          4
#define AV_OPT_TYPE_BOOL           5

#define OFFSET(x) offsetof(AudioFadeContext, x)
#define FLAGS AV_OPT_FLAG_AUDIO_PARAM|AV_OPT_FLAG_FILTERING_PARAM

static inline double av_clipd(double a, double amin, double amax) {
    if (a < amin) return amin;
    if (a > amax) return amax;
    return a;
}

static inline int64_t av_rescale(int64_t a, int64_t b, int64_t c) {
    return a * b / c;
}

static inline int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq) {
    return av_rescale(a, bq.num * (int64_t)cq.den, bq.den * (int64_t)cq.num);
}

static inline void av_frame_free(AVFrame **frame) {
    if (frame && *frame) {
        *frame = NULL;
    }
}

static inline int av_frame_is_writable(const AVFrame *frame) {
    return 1;
}

static int take_samples(AVFilterLink *link, unsigned min, unsigned max, AVFrame **rframe);
static void consume_update(AVFilterLink *link, const AVFrame *frame);

#define CROSSFADE_PLANAR(name, type)                                           \
static void crossfade_samples_## name ##p(uint8_t **dst, uint8_t * const *cf0, \
                                          uint8_t * const *cf1,                \
                                          int nb_samples, int channels,        \
                                          int curve0, int curve1)              \
{                                                                              \
    int i, c;                                                                  \
                                                                               \
    for (i = 0; i < nb_samples; i++) {                                         \
        double gain0 = fade_gain(curve0, nb_samples - 1 - i, nb_samples);      \
        double gain1 = fade_gain(curve1, i, nb_samples);                       \
        for (c = 0; c < channels; c++) {                                       \
            type *d = (type *)dst[c];                                          \
            const type *s0 = (type *)cf0[c];                                   \
            const type *s1 = (type *)cf1[c];                                   \
                                                                               \
            d[i] = s0[i] * gain0 + s1[i] * gain1;                              \
        }                                                                      \
    }                                                                          \
}

#define CROSSFADE(name, type)                                               \
static void crossfade_samples_## name (uint8_t **dst, uint8_t * const *cf0, \
                                       uint8_t * const *cf1,                \
                                       int nb_samples, int channels,        \
                                       int curve0, int curve1)              \
{                                                                           \
    type *d = (type *)dst[0];                                               \
    const type *s0 = (type *)cf0[0];                                        \
    const type *s1 = (type *)cf1[0];                                        \
    int i, c, k = 0;                                                        \
                                                                            \
    for (i = 0; i < nb_samples; i++) {                                      \
        double gain0 = fade_gain(curve0, nb_samples - 1 - i, nb_samples);   \
        double gain1 = fade_gain(curve1, i, nb_samples);                    \
        for (c = 0; c < channels; c++, k++)                                 \
            d[k] = s0[k] * gain0 + s1[k] * gain1;                           \
    }                                                                       \
}

CROSSFADE_PLANAR(dbl, double)
CROSSFADE_PLANAR(flt, float)
CROSSFADE_PLANAR(s16, int16_t)
CROSSFADE_PLANAR(s32, int32_t)

CROSSFADE(dbl, double)
CROSSFADE(flt, float)
CROSSFADE(s16, int16_t)
CROSSFADE(s32, int32_t)

static inline uint64_t ff_framequeue_queued_samples(const FFFrameQueue *fq)
{
    return fq->total_samples_head - fq->total_samples_tail;
}

int ff_inlink_queued_samples(AVFilterLink *link)
{
    return ff_framequeue_queued_samples(&link->fifo);
}

int ff_inlink_consume_samples(AVFilterLink *link, unsigned min, unsigned max,
                            AVFrame **rframe)
{
    AVFrame *frame;
    int ret;

    av_assert1(min);
    *rframe = NULL;
    if (!ff_inlink_check_available_samples(link, min))
        return 0;
    if (link->status_in)
        min = FFMIN(min, ff_framequeue_queued_samples(&link->fifo));
    ret = take_samples(link, min, max, &frame);
    if (ret < 0)
        return ret;
    consume_update(link, frame);
    *rframe = frame;
    return 1;
}

static int activate(AVFilterContext *ctx)
{
    AudioFadeContext *s   = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *in = NULL, *out, *cf[2] = { NULL };
    int ret = 0, nb_samples, status;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(outlink, ctx);

    if (s->crossfade_is_over) {
        ret = ff_inlink_consume_frame(ctx->inputs[1], &in);
        if (ret < 0) {
            return ret;
        } else if (ff_inlink_acknowledge_status(ctx->inputs[1], &status, &pts)) {
            ff_outlink_set_status(ctx->outputs[0], status, pts);
            return 0;
        } else {
            if (ff_outlink_frame_wanted(ctx->outputs[0]) && !in) {
                ff_inlink_request_frame(ctx->inputs[1]);
                return 0;
            }
        }
        in->pts = s->pts;
        s->pts += av_rescale_q(in->nb_samples,
            (AVRational){ 1, outlink->sample_rate }, outlink->time_base);
        return ff_filter_frame(outlink, in);
    }

    if (ff_inlink_queued_samples(ctx->inputs[0]) > s->nb_samples) {
        nb_samples = ff_inlink_queued_samples(ctx->inputs[0]) - s->nb_samples;
        if (nb_samples > 0) {
            ret = ff_inlink_consume_samples(ctx->inputs[0], nb_samples, nb_samples, &in);
            if (ret < 0) {
                return ret;
            }
        }
        in->pts = s->pts;
        s->pts += av_rescale_q(in->nb_samples,
            (AVRational){ 1, outlink->sample_rate }, outlink->time_base);
        return ff_filter_frame(outlink, in);
    } else if (ff_inlink_queued_samples(ctx->inputs[1]) >= s->nb_samples &&
               ff_inlink_queued_samples(ctx->inputs[1]) >= s->nb_samples) {
        if (s->overlap) {
            out = ff_get_audio_buffer(outlink, s->nb_samples);
            if (!out)
                return AVERROR(ENOMEM);

            ret = ff_inlink_consume_samples(ctx->inputs[0], s->nb_samples, s->nb_samples, &cf[0]);
            if (ret < 0) {
                av_frame_free(&out);
                return ret;
            }

            ret = ff_inlink_consume_samples(ctx->inputs[1], s->nb_samples, s->nb_samples, &cf[1]);
            if (ret < 0) {
                av_frame_free(&out);
                return ret;
            }

            s->crossfade_samples(out->extended_data, cf[0]->extended_data,
                                 cf[1]->extended_data,
                                 s->nb_samples, out->channels,
                                 s->curve, s->curve2);
            out->pts = s->pts;
            s->pts += av_rescale_q(s->nb_samples,
                (AVRational){ 1, outlink->sample_rate }, outlink->time_base);
            s->crossfade_is_over = 1;
            av_frame_free(&cf[0]);
            av_frame_free(&cf[1]);
            return ff_filter_frame(outlink, out);
        } else {
            out = ff_get_audio_buffer(outlink, s->nb_samples);
            if (!out)
                return AVERROR(ENOMEM);

            ret = ff_inlink_consume_samples(ctx->inputs[0], s->nb_samples, s->nb_samples, &cf[0]);
            if (ret < 0) {
                av_frame_free(&out);
                return ret;
            }

            s->fade_samples(out->extended_data, cf[0]->extended_data, s->nb_samples,
                            outlink->channels, -1, s->nb_samples - 1, s->nb_samples, s->curve);
            out->pts = s->pts;
            s->pts += av_rescale_q(s->nb_samples,
                (AVRational){ 1, outlink->sample_rate }, outlink->time_base);
            av_frame_free(&cf[0]);
            ret = ff_filter_frame(outlink, out);
            if (ret < 0)
                return ret;

            out = ff_get_audio_buffer(outlink, s->nb_samples);
            if (!out)
                return AVERROR(ENOMEM);

            ret = ff_inlink_consume_samples(ctx->inputs[1], s->nb_samples, s->nb_samples, &cf[1]);
            if (ret < 0) {
                av_frame_free(&out);
                return ret;
            }

            s->fade_samples(out->extended_data, cf[1]->extended_data, s->nb_samples,
                            outlink->channels, 1, 0, s->nb_samples, s->curve2);
            out->pts = s->pts;
            s->pts += av_rescale_q(s->nb_samples,
                (AVRational){ 1, outlink->sample_rate }, outlink->time_base);
            s->crossfade_is_over = 1;
            av_frame_free(&cf[1]);
            return ff_filter_frame(outlink, out);
        }
    } else if (ff_outlink_frame_wanted(ctx->outputs[0])) {
        if (!s->cf0_eof && ff_outlink_get_status(ctx->inputs[0])) {
            s->cf0_eof = 1;
        }
        if (ff_outlink_get_status(ctx->inputs[1])) {
            ff_outlink_set_status(ctx->outputs[0], AVERROR_EOF, AV_NOPTS_VALUE);
            return 0;
        }
        if (!s->cf0_eof)
            ff_inlink_request_frame(ctx->inputs[0]);
        else
            ff_inlink_request_frame(ctx->inputs[1]);
        return 0;
    }

    return ret;
}
