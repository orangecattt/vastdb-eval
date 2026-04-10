#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define AV_STRINGIFY(x) AV_TOSTRING(x)
#define AV_TOSTRING(x) #x

#define AVERROR(e) (-(e))
#define AVERROR_EOF (-('E' << 24 | 'O' << 16 | 'F' << 8 | ' '))
#define AVERROR_INVALIDDATA (-('I' << 24 | 'N' << 16 | 'D' << 8 | 'A'))
#define AVERROR_EINVAL AVERROR(22)
#define AVERROR_ENOMEM AVERROR(12)
#define AVERROR_EAGAIN AVERROR(11)
#define AVERROR_ENOSYS AVERROR(38)

#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define MKTAG(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_DEBUG    48

#define AV_NOPTS_VALUE ((int64_t)0x8000000000000000ULL)

#define AV_OPT_FLAG_AUDIO_PARAM  1
#define AV_OPT_FLAG_FILTERING_PARAM 2
#define AV_OPT_FLAG_RUNTIME_PARAM 4

#define AV_OPT_TYPE_STRING 3
#define AV_OPT_TYPE_DOUBLE 4
#define AV_OPT_TYPE_INT    1
#define AV_OPT_TYPE_BOOL   6

#define AVFILTER_FLAG_DYNAMIC_INPUTS  (1 << 0)
#define AVFILTER_FLAG_DYNAMIC_OUTPUTS (1 << 1)

#define AV_MEDIA_TYPE_AUDIO 1

#define AV_SAMPLE_FMT_FLTP 2

#define AV_CHANNEL_ORDER_NATIVE 1

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef enum {
    AV_CLASS_CATEGORY_NA = 0,
    AV_CLASS_CATEGORY_INPUT,
    AV_CLASS_CATEGORY_OUTPUT,
    AV_CLASS_CATEGORY_MUXER,
    AV_CLASS_CATEGORY_DEMUXER,
    AV_CLASS_CATEGORY_ENCODER,
    AV_CLASS_CATEGORY_DECODER,
    AV_CLASS_CATEGORY_FILTER,
    AV_CLASS_CATEGORY_BITSTREAM_FILTER,
    AV_CLASS_CATEGORY_SWSCALER,
    AV_CLASS_CATEGORY_SWRESAMPLER,
    AV_CLASS_CATEGORY_HWDEVICE,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT = 40,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT,
    AV_CLASS_CATEGORY_DEVICE_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_INPUT,
    AV_CLASS_CATEGORY_NB
} AVClassCategory;

typedef struct AVFilter AVFilter;
typedef struct AVFilterPad AVFilterPad;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterLink AVFilterLink;
typedef struct AVClass AVClass;
typedef struct AVOption AVOption;

typedef struct AVChannelLayout {
    int order;
    int nb_channels;
    union {
        uint64_t mask;
        void *u;
    } u;
} AVChannelLayout;

struct AVClass {
    const char *class_name;
    const char * (*item_name)(void *ctx);
    const AVOption *option;
    int version;
    AVClassCategory category;
};

typedef struct AVFilterContext {
    const AVClass *av_class;
    const AVFilter *filter;
    char *name;
    AVFilterPad *input_pads;
    AVFilterLink **inputs;
    unsigned nb_inputs;
    AVFilterPad *output_pads;
    AVFilterLink **outputs;
    unsigned nb_outputs;
    void *priv;
    struct AVFilterGraph *graph;
    int thread_type;
    int nb_threads;
    int is_disabled;
} AVFilterContext;

struct AVFilterLink {
    AVFilterContext *src;
    AVFilterPad *srcpad;
    AVFilterContext *dst;
    AVFilterPad *dstpad;
    int type;
    int format;
    int w;
    int h;
    int sample_rate;
    AVChannelLayout ch_layout;
    AVRational time_base;
};

#define FFMAX(a, b) ((a) > (b) ? (a) : (b))
#define FFMIN(a, b) ((a) < (b) ? (a) : (b))

static inline int64_t av_rescale_q(int64_t a, int num, int den) {
    return (int64_t)((double)a * num / den);
}

static inline int av_make_q(int num, int den) {
    return (num << 16) | (den & 0xFFFF);
}

static inline double av_q2d(int q) {
    return (double)(q >> 16) / (q & 0xFFFF);
}

static inline void *av_malloc(size_t size) {
    return malloc(size);
}

static inline void *av_malloc_array(size_t nmemb, size_t size) {
    size_t result;
    if (__builtin_mul_overflow(nmemb, size, &result))
        return NULL;
    return av_malloc(result);
}

static inline void *av_calloc(size_t nmemb, size_t size) {
    size_t result;
    if (__builtin_mul_overflow(nmemb, size, &result))
        return NULL;
    void *ptr = av_malloc(result);
    if (ptr)
        memset(ptr, 0, result);
    return ptr;
}

static inline void *av_strdup(const char *s) {
    return strdup(s);
}

static inline void av_free(void *ptr) {
    free(ptr);
}

static inline void av_freep(void *ptr) {
    void **p = (void **)ptr;
    if (*p) {
        free(*p);
        *p = NULL;
    }
}

void av_log(void *avcl, int level, const char *fmt, ...);

#define av_assert0(cond) ((void)0)

typedef struct AVComplexFloat {
    float re, im;
} AVComplexFloat;

typedef struct AVTXContext AVTXContext;

enum AVTXType {
    AV_TX_FLOAT_FFT  = 0,
    AV_TX_DOUBLE_FFT = 2,
    AV_TX_INT32_FFT  = 4,
    AV_TX_FLOAT_MDCT  = 1,
    AV_TX_DOUBLE_MDCT = 3,
    AV_TX_INT32_MDCT  = 5,
    AV_TX_FLOAT_RDFT  = 6,
    AV_TX_DOUBLE_RDFT = 7,
    AV_TX_INT32_RDFT  = 8,
    AV_TX_FLOAT_DCT  = 9,
    AV_TX_DOUBLE_DCT = 10,
    AV_TX_INT32_DCT  = 11,
    AV_TX_FLOAT_DCT_I  = 12,
    AV_TX_DOUBLE_DCT_I = 13,
    AV_TX_INT32_DCT_I  = 14,
    AV_TX_FLOAT_DST_I  = 15,
    AV_TX_DOUBLE_DST_I = 16,
    AV_TX_INT32_DST_I  = 17,
    AV_TX_NB,
};

typedef void (*av_tx_fn)(AVTXContext *s, void *out, void *in, ptrdiff_t stride);

int av_tx_init(AVTXContext **ctx, av_tx_fn *tx, enum AVTXType type,
                             int inv, int len, const void *scale, uint64_t flags);

void av_tx_uninit(AVTXContext **ctx);

static inline FILE *avpriv_fopen_utf8(const char *path, const char *mode) {
    return fopen(path, mode);
}

typedef struct AVExpr AVExpr;

int av_expr_parse_and_eval(double *res, const char *s,
                                         const char * const *const_names, const double *const_values,
                                         const char * const *func1_names, double (* const *funcs1)(void *, double),
                                         const char * const *func2_names, double (* const *funcs2)(void *, double, double),
                                         void *opaque, int log_offset, void *log_ctx);

int av_expr_parse(AVExpr **expr, const char *s,
                                const char * const *const_names,
                                const char * const *func1_names, double (* const *funcs1)(void *, double),
                                const char * const *func2_names, double (* const *funcs2)(void *, double, double),
                                int log_offset, void *log_ctx);

double av_expr_eval(AVExpr *e, const double *const_values, void *opaque);
void av_expr_free(AVExpr *e);

int av_channel_layout_channel_from_index(const AVChannelLayout *layout, int index);

#define RDFT_BITS_MIN 4
#define RDFT_BITS_MAX 16

enum WindowFunc {
    WFUNC_RECTANGULAR,
    WFUNC_HANN,
    WFUNC_HAMMING,
    WFUNC_BLACKMAN,
    WFUNC_NUTTALL3,
    WFUNC_MNUTTALL3,
    WFUNC_NUTTALL,
    WFUNC_BNUTTALL,
    WFUNC_BHARRIS,
    WFUNC_TUKEY,
    NB_WFUNC
};

enum Scale {
    SCALE_LINLIN,
    SCALE_LINLOG,
    SCALE_LOGLIN,
    SCALE_LOGLOG,
    NB_SCALE
};

#define NB_GAIN_ENTRY_MAX 4096

typedef struct GainEntry {
    double freq;
    double gain;
} GainEntry;

typedef struct OverlapIndex {
    int buf_idx;
    int overlap_idx;
} OverlapIndex;

typedef struct FIREqualizerContext {
    const AVClass *class;

    AVTXContext   *analysis_rdft;
    av_tx_fn      analysis_rdft_fn;
    AVTXContext   *analysis_irdft;
    av_tx_fn      analysis_irdft_fn;
    AVTXContext   *rdft;
    av_tx_fn      rdft_fn;
    AVTXContext   *irdft;
    av_tx_fn      irdft_fn;
    AVTXContext   *fft_ctx;
    av_tx_fn      fft_fn;
    AVTXContext   *cepstrum_rdft;
    av_tx_fn      cepstrum_rdft_fn;
    AVTXContext   *cepstrum_irdft;
    av_tx_fn      cepstrum_irdft_fn;
    int           analysis_rdft_len;
    int           rdft_len;
    int           cepstrum_len;

    float         *analysis_buf;
    float         *analysis_tbuf;
    float         *dump_buf;
    float         *kernel_tmp_buf;
    float         *kernel_tmp_tbuf;
    float         *kernel_buf;
    float         *tx_buf;
    float         *cepstrum_buf;
    float         *cepstrum_tbuf;
    float         *conv_buf;
    OverlapIndex  *conv_idx;
    int           fir_len;
    int           nsamples_max;
    int64_t       next_pts;
    int           frame_nsamples_max;
    int           remaining;

    char          *gain_cmd;
    char          *gain_entry_cmd;
    const char    *gain;
    const char    *gain_entry;
    double        delay;
    double        accuracy;
    int           wfunc;
    int           fixed;
    int           multi;
    int           zero_phase;
    int           scale;
    char          *dumpfile;
    int           dumpscale;
    int           fft2;
    int           min_phase;

    int           nb_gain_entry;
    int           gain_entry_err;
    GainEntry     gain_entry_tbl[NB_GAIN_ENTRY_MAX];
} FIREqualizerContext;

typedef struct AVFrame {
    uint8_t **data;
    int *linesize;
    int nb_samples;
    int64_t pts;
    int format;
} AVFrame;

#define OFFSET(x) offsetof(FIREqualizerContext, x)

#define SELECT_GAIN(s) (s->gain_cmd ? s->gain_cmd : s->gain)
#define SELECT_GAIN_ENTRY(s) (s->gain_entry_cmd ? s->gain_entry_cmd : s->gain_entry)

enum VarOffset {
    VAR_F,
    VAR_SR,
    VAR_CH,
    VAR_CHID,
    VAR_CHS,
    VAR_CHLAYOUT,
    VAR_NB
};

static const char *const var_names[] = {
    "f",
    "sr",
    "ch",
    "chid",
    "chs",
    "chlayout",
    NULL
};

typedef struct FilterLink {
    AVFilterLink pub;

    struct AVFilterGraph *graph;
    int64_t current_pts;

    int min_samples;
    int max_samples;
} FilterLink;

static inline FilterLink* ff_filter_link(AVFilterLink *link) {
    return (FilterLink*)link;
}

static void common_uninit(FIREqualizerContext *s) {
    av_tx_uninit(&s->analysis_rdft);
    av_tx_uninit(&s->analysis_irdft);
    av_tx_uninit(&s->rdft);
    av_tx_uninit(&s->irdft);
    av_tx_uninit(&s->fft_ctx);
    av_tx_uninit(&s->cepstrum_rdft);
    av_tx_uninit(&s->cepstrum_irdft);
    s->analysis_rdft = s->analysis_irdft = s->rdft = s->irdft = NULL;
    s->fft_ctx = NULL;
    s->cepstrum_rdft = NULL;
    s->cepstrum_irdft = NULL;

    av_freep(&s->analysis_buf);
    av_freep(&s->analysis_tbuf);
    av_freep(&s->dump_buf);
    av_freep(&s->kernel_tmp_buf);
    av_freep(&s->kernel_tmp_tbuf);
    av_freep(&s->kernel_buf);
    av_freep(&s->tx_buf);
    av_freep(&s->cepstrum_buf);
    av_freep(&s->cepstrum_tbuf);
    av_freep(&s->conv_buf);
    av_freep(&s->conv_idx);
}

static AVFrame *ff_get_audio_buffer(AVFilterLink *link, int nb_samples) {
    AVFrame *frame = av_malloc(sizeof(AVFrame));
    if (!frame)
        return NULL;
    frame->nb_samples = nb_samples;
    frame->pts = AV_NOPTS_VALUE;
    return frame;
}

static int ff_request_frame(AVFilterLink *link) {
    return AVERROR_EOF;
}

static int ff_filter_frame(AVFilterLink *link, AVFrame *frame) {
    av_free(frame);
    return 0;
}

static AVFrame *ff_default_get_audio_buffer(AVFilterLink *link, int nb_samples) {
    return ff_get_audio_buffer(link, nb_samples);
}

static double entry_func(void *p, double freq, double gain) {
    AVFilterContext *ctx = p;
    FIREqualizerContext *s = ctx->priv;

    if (s->nb_gain_entry >= NB_GAIN_ENTRY_MAX) {
        av_log(ctx, AV_LOG_ERROR, "entry table overflow.\n");
        s->gain_entry_err = AVERROR_EINVAL;
        return 0;
    }

    if (isnan(freq)) {
        av_log(ctx, AV_LOG_ERROR, "nan frequency (%g, %g).\n", freq, gain);
        s->gain_entry_err = AVERROR_EINVAL;
        return 0;
    }

    if (s->nb_gain_entry > 0 && freq <= s->gain_entry_tbl[s->nb_gain_entry - 1].freq) {
        av_log(ctx, AV_LOG_ERROR, "unsorted frequency (%g, %g).\n", freq, gain);
        s->gain_entry_err = AVERROR_EINVAL;
        return 0;
    }

    s->gain_entry_tbl[s->nb_gain_entry].freq = freq;
    s->gain_entry_tbl[s->nb_gain_entry].gain = gain;
    s->nb_gain_entry++;
    return 0;
}

static int gain_entry_compare(const void *key, const void *memb) {
    const double *freq = key;
    const GainEntry *entry = memb;

    if (*freq < entry[0].freq)
        return -1;
    if (*freq > entry[1].freq)
        return 1;
    return 0;
}

static double gain_interpolate_func(void *p, double freq) {
    AVFilterContext *ctx = p;
    FIREqualizerContext *s = ctx->priv;
    GainEntry *res;
    double d0, d1, d;

    if (isnan(freq))
        return freq;

    if (!s->nb_gain_entry)
        return 0;

    if (freq <= s->gain_entry_tbl[0].freq)
        return s->gain_entry_tbl[0].gain;

    if (freq >= s->gain_entry_tbl[s->nb_gain_entry-1].freq)
        return s->gain_entry_tbl[s->nb_gain_entry-1].gain;

    res = bsearch(&freq, &s->gain_entry_tbl, s->nb_gain_entry - 1, sizeof(*res), gain_entry_compare);
    av_assert0(res);

    d  = res[1].freq - res[0].freq;
    d0 = freq - res[0].freq;
    d1 = res[1].freq - freq;

    if (d0 && d1)
        return (d0 * res[1].gain + d1 * res[0].gain) / d;

    if (d0)
        return res[1].gain;

    return res[0].gain;
}

static double cubic_interpolate_func(void *p, double freq) {
    AVFilterContext *ctx = p;
    FIREqualizerContext *s = ctx->priv;
    GainEntry *res;
    double x, x2, x3;
    double a, b, c, d;
    double m0, m1, m2, msum, unit;

    if (!s->nb_gain_entry)
        return 0;

    if (freq <= s->gain_entry_tbl[0].freq)
        return s->gain_entry_tbl[0].gain;

    if (freq >= s->gain_entry_tbl[s->nb_gain_entry-1].freq)
        return s->gain_entry_tbl[s->nb_gain_entry-1].gain;

    res = bsearch(&freq, &s->gain_entry_tbl, s->nb_gain_entry - 1, sizeof(*res), gain_entry_compare);
    av_assert0(res);

    unit = res[1].freq - res[0].freq;
    m0 = res != s->gain_entry_tbl ?
         unit * (res[0].gain - res[-1].gain) / (res[0].freq - res[-1].freq) : 0;
    m1 = res[1].gain - res[0].gain;
    m2 = res != s->gain_entry_tbl + s->nb_gain_entry - 2 ?
         unit * (res[2].gain - res[1].gain) / (res[2].freq - res[1].freq) : 0;

    msum = fabs(m0) + fabs(m1);
    m0 = msum > 0 ? (fabs(m0) * m1 + fabs(m1) * m0) / msum : 0;
    msum = fabs(m1) + fabs(m2);
    m1 = msum > 0 ? (fabs(m1) * m2 + fabs(m2) * m1) / msum : 0;

    d = res[0].gain;
    c = m0;
    b = 3 * res[1].gain - m1 - 2 * c - 3 * d;
    a = res[1].gain - b - c - d;

    x = (freq - res[0].freq) / unit;
    x2 = x * x;
    x3 = x2 * x;

    return a * x3 + b * x2 + c * x + d;
}

static void generate_min_phase_kernel(FIREqualizerContext *s, float *rdft_buf) {
    int k, cepstrum_len = s->cepstrum_len, rdft_len = s->rdft_len;
    double norm = 2.0 / cepstrum_len;
    double minval = 1e-7 / rdft_len;

    memset(s->cepstrum_buf, 0, cepstrum_len * sizeof(*s->cepstrum_buf));
    memset(s->cepstrum_tbuf, 0, (cepstrum_len + 2) * sizeof(*s->cepstrum_tbuf));
    memcpy(s->cepstrum_buf, rdft_buf, rdft_len/2 * sizeof(*rdft_buf));
    memcpy(s->cepstrum_buf + cepstrum_len - rdft_len/2, rdft_buf + rdft_len/2, rdft_len/2  * sizeof(*rdft_buf));

    s->cepstrum_rdft_fn(s->cepstrum_rdft, s->cepstrum_tbuf, s->cepstrum_buf, sizeof(float));

    for (k = 0; k < cepstrum_len + 2; k += 2) {
        s->cepstrum_tbuf[k] = log(FFMAX(s->cepstrum_tbuf[k], minval));
        s->cepstrum_tbuf[k+1] = 0;
    }

    s->cepstrum_irdft_fn(s->cepstrum_irdft, s->cepstrum_buf, s->cepstrum_tbuf, sizeof(AVComplexFloat));

    memset(s->cepstrum_buf + cepstrum_len/2 + 1, 0, (cepstrum_len/2 - 1) * sizeof(*s->cepstrum_buf));
    for (k = 1; k <= cepstrum_len/2; k++)
        s->cepstrum_buf[k] *= 2;

    s->cepstrum_rdft_fn(s->cepstrum_rdft, s->cepstrum_tbuf, s->cepstrum_buf, sizeof(float));

    for (k = 0; k < cepstrum_len + 2; k += 2) {
        double mag = exp(s->cepstrum_tbuf[k] * norm) * norm;
        double ph = s->cepstrum_tbuf[k+1] * norm;
        s->cepstrum_tbuf[k] = mag * cos(ph);
        s->cepstrum_tbuf[k+1] = mag * sin(ph);
    }

    s->cepstrum_irdft_fn(s->cepstrum_irdft, s->cepstrum_buf, s->cepstrum_tbuf, sizeof(AVComplexFloat));
    memset(rdft_buf, 0, s->rdft_len * sizeof(*rdft_buf));
    memcpy(rdft_buf, s->cepstrum_buf, s->fir_len * sizeof(*rdft_buf));

    if (s->dumpfile) {
        memset(s->analysis_buf, 0, (s->analysis_rdft_len + 2) * sizeof(*s->analysis_buf));
        memcpy(s->analysis_buf, s->cepstrum_buf, s->fir_len * sizeof(*s->analysis_buf));
    }
}

static void dump_fir(AVFilterContext *ctx, FILE *fp, int ch)
{
    FIREqualizerContext *s = ctx->priv;
    int rate = ctx->inputs[0]->sample_rate;
    int xlog = s->dumpscale == SCALE_LOGLIN || s->dumpscale == SCALE_LOGLOG;
    int ylog = s->dumpscale == SCALE_LINLOG || s->dumpscale == SCALE_LOGLOG;
    int x;
    int center = s->fir_len / 2;
    double delay = s->zero_phase ? 0.0 : (double) center / rate;
    double vx, ya, yb;

    if (!s->min_phase) {
        s->analysis_buf[0] *= s->rdft_len/2;
        for (x = 1; x <= center; x++) {
            s->analysis_buf[x] *= s->rdft_len/2;
            s->analysis_buf[s->analysis_rdft_len - x] *= s->rdft_len/2;
        }
    } else {
        for (x = 0; x < s->fir_len; x++)
            s->analysis_buf[x] *= s->rdft_len/2;
    }

    if (ch)
        fprintf(fp, "\n\n");

    fprintf(fp, "# time[%d] (time amplitude)\n", ch);

    if (!s->min_phase) {
    for (x = center; x > 0; x--)
        fprintf(fp, "%15.10f %15.10f\n", delay - (double) x / rate, (double) s->analysis_buf[s->analysis_rdft_len - x]);

    for (x = 0; x <= center; x++)
        fprintf(fp, "%15.10f %15.10f\n", delay + (double)x / rate , (double) s->analysis_buf[x]);
    } else {
        for (x = 0; x < s->fir_len; x++)
            fprintf(fp, "%15.10f %15.10f\n", (double)x / rate, (double) s->analysis_buf[x]);
    }

    s->analysis_rdft_fn(s->analysis_rdft, s->analysis_tbuf, s->analysis_buf, sizeof(float));

    fprintf(fp, "\n\n# freq[%d] (frequency desired_gain actual_gain)\n", ch);

    for (x = 0; x <= s->analysis_rdft_len/2; x++) {
        int i = 2 * x;
        vx = (double)x * rate / s->analysis_rdft_len;
        if (xlog)
            vx = log2(0.05*vx);
        ya = s->dump_buf[i];
        yb = s->min_phase ? hypotf(s->analysis_tbuf[i], s->analysis_tbuf[i+1]) : s->analysis_tbuf[i];
        if (s->min_phase)
            yb = fabs(yb);
        if (ylog) {
            ya = 20.0 * log10(fabs(ya));
            yb = 20.0 * log10(fabs(yb));
        }
        fprintf(fp, "%17.10f %17.10f %17.10f\n", vx, ya, yb);
    }
}

static int generate_kernel(AVFilterContext *ctx, const char *gain, const char *gain_entry)
{
    FIREqualizerContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    const char *gain_entry_func_names[] = { "entry", NULL };
    const char *gain_func_names[] = { "gain_interpolate", "cubic_interpolate", NULL };
    double (*gain_entry_funcs[])(void *, double, double) = { entry_func, NULL };
    double (*gain_funcs[])(void *, double) = { gain_interpolate_func, cubic_interpolate_func, NULL };
    double vars[VAR_NB];
    AVExpr *gain_expr;
    int ret, k, center, ch;
    int xlog = s->scale == SCALE_LOGLIN || s->scale == SCALE_LOGLOG;
    int ylog = s->scale == SCALE_LINLOG || s->scale == SCALE_LOGLOG;
    FILE *dump_fp = NULL;

    s->nb_gain_entry = 0;
    s->gain_entry_err = 0;
    if (gain_entry) {
        double result = 0.0;
        ret = av_expr_parse_and_eval(&result, gain_entry, NULL, NULL, NULL, NULL,
                                     gain_entry_func_names, gain_entry_funcs, ctx, 0, ctx);
        if (ret < 0)
            return ret;
        if (s->gain_entry_err < 0)
            return s->gain_entry_err;
    }

    av_log(ctx, AV_LOG_DEBUG, "nb_gain_entry = %d.\n", s->nb_gain_entry);

    ret = av_expr_parse(&gain_expr, gain, var_names,
                        gain_func_names, gain_funcs, NULL, NULL, 0, ctx);
    if (ret < 0)
        return ret;

    if (s->dumpfile && (!s->dump_buf || !s->analysis_rdft || !(dump_fp = avpriv_fopen_utf8(s->dumpfile, "w"))))
        av_log(ctx, AV_LOG_WARNING, "dumping failed.\n");

    vars[VAR_CHS] = inlink->ch_layout.nb_channels;
    vars[VAR_CHLAYOUT] = inlink->ch_layout.order == AV_CHANNEL_ORDER_NATIVE ?
                         inlink->ch_layout.u.mask : 0;
    vars[VAR_SR] = inlink->sample_rate;
    for (ch = 0; ch < inlink->ch_layout.nb_channels; ch++) {
        float *rdft_buf = s->kernel_tmp_buf + ch * (s->rdft_len * 2);
        float *rdft_tbuf = s->kernel_tmp_tbuf;
        double result;
        vars[VAR_CH] = ch;
        vars[VAR_CHID] = av_channel_layout_channel_from_index(&inlink->ch_layout, ch);

        for (k = 0; k <= s->analysis_rdft_len/2; k++) {
            vars[VAR_F] = k * ((double)inlink->sample_rate /(double)s->analysis_rdft_len);
            if (xlog)
                vars[VAR_F] = log2(0.05 * vars[VAR_F]);
            result = av_expr_eval(gain_expr, vars, ctx);
            s->analysis_tbuf[2*k] = ylog ? pow(10.0, 0.05 * result) : s->min_phase ? fabs(result) : result;
            s->analysis_tbuf[2*k+1] = 0.0;
        }

        if (s->dump_buf)
            memcpy(s->dump_buf, s->analysis_tbuf, (s->analysis_rdft_len + 2) * sizeof(*s->analysis_tbuf));

        s->analysis_irdft_fn(s->analysis_irdft, s->analysis_buf, s->analysis_tbuf, sizeof(AVComplexFloat));
        center = s->fir_len / 2;

        for (k = 0; k <= center; k++) {
            double u = k * (M_PI/center);
            double win;
            switch (s->wfunc) {
            case WFUNC_RECTANGULAR:
                win = 1.0;
                break;
            case WFUNC_HANN:
                win = 0.5 + 0.5 * cos(u);
                break;
            case WFUNC_HAMMING:
                win = 0.53836 + 0.46164 * cos(u);
                break;
            case WFUNC_BLACKMAN:
                win = 0.42 + 0.5 * cos(u) + 0.08 * cos(2*u);
                break;
            case WFUNC_NUTTALL3:
                win = 0.40897 + 0.5 * cos(u) + 0.09103 * cos(2*u);
                break;
            case WFUNC_MNUTTALL3:
                win = 0.4243801 + 0.4973406 * cos(u) + 0.0782793 * cos(2*u);
                break;
            case WFUNC_NUTTALL:
                win = 0.355768 + 0.487396 * cos(u) + 0.144232 * cos(2*u) + 0.012604 * cos(3*u);
                break;
            case WFUNC_BNUTTALL:
                win = 0.3635819 + 0.4891775 * cos(u) + 0.1365995 * cos(2*u) + 0.0106411 * cos(3*u);
                break;
            case WFUNC_BHARRIS:
                win = 0.35875 + 0.48829 * cos(u) + 0.14128 * cos(2*u) + 0.01168 * cos(3*u);
                break;
            case WFUNC_TUKEY:
                win = (u <= 0.5 * M_PI) ? 1.0 : (0.5 + 0.5 * cos(2*u - M_PI));
                break;
            default:
                av_assert0(0);
            }
            s->analysis_buf[k] *= (2.0/s->analysis_rdft_len) * (2.0/s->rdft_len) * win;
            if (k)
                s->analysis_buf[s->analysis_rdft_len - k] = s->analysis_buf[k];
        }

        memset(s->analysis_buf + center + 1, 0, (s->analysis_rdft_len - s->fir_len) * sizeof(*s->analysis_buf));
        memcpy(rdft_tbuf, s->analysis_buf, s->rdft_len/2 * sizeof(*s->analysis_buf));
        memcpy(rdft_tbuf + s->rdft_len/2, s->analysis_buf + s->analysis_rdft_len - s->rdft_len/2, s->rdft_len/2 * sizeof(*s->analysis_buf));
        if (s->min_phase)
            generate_min_phase_kernel(s, rdft_tbuf);
        s->rdft_fn(s->rdft, rdft_buf, rdft_tbuf, sizeof(float));

        for (k = 0; k < s->rdft_len + 2; k++) {
            if (isnan(rdft_buf[k]) || isinf(rdft_buf[k])) {
                av_log(ctx, AV_LOG_ERROR, "filter kernel contains nan or infinity.\n");
                av_expr_free(gain_expr);
                if (dump_fp)
                    fclose(dump_fp);
                return AVERROR_EINVAL;
            }
        }

        if (!s->min_phase) {
            for (k = 0; k <= s->rdft_len/2; k++)
                rdft_buf[k] = rdft_buf[2*k];
        }

        if (dump_fp)
            dump_fir(ctx, dump_fp, ch);

        if (!s->multi)
            break;
    }

    memcpy(s->kernel_buf, s->kernel_tmp_buf, (s->multi ? inlink->ch_layout.nb_channels : 1) * (s->rdft_len * 2) * sizeof(*s->kernel_buf));
    av_expr_free(gain_expr);
    if (dump_fp)
        fclose(dump_fp);
    return 0;
}

#define FFMAX(a, b) ((a) > (b) ? (a) : (b))
#define FFMIN(a, b) ((a) < (b) ? (a) : (b))

static int config_input(AVFilterLink *inlink)
{
    FilterLink *l = ff_filter_link(inlink);
    AVFilterContext *ctx = inlink->dst;
    FIREqualizerContext *s = ctx->priv;
    float iscale, scale = 1.f;
    int rdft_bits, ret;

    common_uninit(s);

    s->next_pts = 0;
    s->frame_nsamples_max = 0;

    s->fir_len = FFMAX(2 * (int)(inlink->sample_rate * s->delay) + 1, 3);
    s->remaining = s->fir_len - 1;

    for (rdft_bits = RDFT_BITS_MIN; rdft_bits <= RDFT_BITS_MAX; rdft_bits++) {
        s->rdft_len = 1 << rdft_bits;
        s->nsamples_max = s->rdft_len - s->fir_len + 1;
        if (s->nsamples_max * 2 >= s->fir_len)
            break;
    }

    if (rdft_bits > RDFT_BITS_MAX) {
        av_log(ctx, AV_LOG_ERROR, "too large delay, please decrease it.\n");
        return AVERROR_EINVAL;
    }

    iscale = 0.5f;
    if (((ret = av_tx_init(&s->rdft,  &s->rdft_fn,  AV_TX_FLOAT_RDFT, 0, 1 << rdft_bits, &scale,  0)) < 0) ||
        ((ret = av_tx_init(&s->irdft, &s->irdft_fn, AV_TX_FLOAT_RDFT, 1, 1 << rdft_bits, &iscale, 0)) < 0))
        return ret;

    scale = 1.f;
    if (s->fft2 && !s->multi && inlink->ch_layout.nb_channels > 1 &&
        ((ret = av_tx_init(&s->fft_ctx, &s->fft_fn, AV_TX_FLOAT_FFT, 0, 1 << rdft_bits, &scale, 0)) < 0))
        return ret;

    if (s->min_phase) {
        int cepstrum_bits = rdft_bits + 2;
        if (cepstrum_bits > RDFT_BITS_MAX) {
            av_log(ctx, AV_LOG_ERROR, "too large delay, please decrease it.\n");
            return AVERROR_EINVAL;
        }

        cepstrum_bits = FFMIN(RDFT_BITS_MAX, cepstrum_bits + 1);
        scale = 1.f;
        ret = av_tx_init(&s->cepstrum_rdft,  &s->cepstrum_rdft_fn,  AV_TX_FLOAT_RDFT, 0, 1 << cepstrum_bits, &scale, 0);
        if (ret < 0)
            return ret;

        iscale = 0.5f;
        ret = av_tx_init(&s->cepstrum_irdft, &s->cepstrum_irdft_fn, AV_TX_FLOAT_RDFT, 1, 1 << cepstrum_bits, &iscale, 0);
        if (ret < 0)
            return ret;

        s->cepstrum_len = 1 << cepstrum_bits;
        s->cepstrum_buf = av_malloc_array(s->cepstrum_len, sizeof(*s->cepstrum_buf));
        if (!s->cepstrum_buf)
            return AVERROR_ENOMEM;
        s->cepstrum_tbuf = av_malloc_array(s->cepstrum_len + 2, sizeof(*s->cepstrum_tbuf));
        if (!s->cepstrum_tbuf)
            return AVERROR_ENOMEM;
    }

    for ( ; rdft_bits <= RDFT_BITS_MAX; rdft_bits++) {
        s->analysis_rdft_len = 1 << rdft_bits;
        if (inlink->sample_rate <= s->accuracy * s->analysis_rdft_len)
            break;
    }

    if (rdft_bits > RDFT_BITS_MAX) {
        av_log(ctx, AV_LOG_ERROR, "too small accuracy, please increase it.\n");
        return AVERROR_EINVAL;
    }

    iscale = 0.5f;
    if ((ret = av_tx_init(&s->analysis_irdft, &s->analysis_irdft_fn, AV_TX_FLOAT_RDFT, 1, 1 << rdft_bits, &iscale, 0)) < 0)
        return ret;

    if (s->dumpfile) {
        scale = 1.f;
        if ((ret = av_tx_init(&s->analysis_rdft, &s->analysis_rdft_fn, AV_TX_FLOAT_RDFT, 0, 1 << rdft_bits, &scale, 0)) < 0)
            return ret;
        s->dump_buf = av_malloc_array(s->analysis_rdft_len + 2, sizeof(*s->dump_buf));
        if (!s->dump_buf)
            return AVERROR_ENOMEM;
    }

    s->analysis_buf = av_malloc_array((s->analysis_rdft_len + 2), sizeof(*s->analysis_buf));
    s->analysis_tbuf = av_malloc_array(s->analysis_rdft_len + 2, sizeof(*s->analysis_tbuf));
    s->kernel_tmp_buf = av_malloc_array((s->rdft_len * 2) * (s->multi ? inlink->ch_layout.nb_channels : 1), sizeof(*s->kernel_tmp_buf));
    s->kernel_tmp_tbuf = av_malloc_array(s->rdft_len, sizeof(*s->kernel_tmp_tbuf));
    s->kernel_buf = av_malloc_array((s->rdft_len * 2) * (s->multi ? inlink->ch_layout.nb_channels : 1), sizeof(*s->kernel_buf));
    s->tx_buf = av_malloc_array(2 * (s->rdft_len + 2), sizeof(*s->kernel_buf));
    s->conv_buf   = av_calloc(2 * s->rdft_len * inlink->ch_layout.nb_channels, sizeof(*s->conv_buf));
    s->conv_idx   = av_calloc(inlink->ch_layout.nb_channels, sizeof(*s->conv_idx));
    if (!s->analysis_buf || !s->analysis_tbuf || !s->kernel_tmp_buf || !s->kernel_buf || !s->conv_buf || !s->conv_idx || !s->kernel_tmp_tbuf || !s->tx_buf)
        return AVERROR_ENOMEM;

    av_log(ctx, AV_LOG_DEBUG, "sample_rate = %d, channels = %d, analysis_rdft_len = %d, rdft_len = %d, fir_len = %d, nsamples_max = %d.\n",
           inlink->sample_rate, inlink->ch_layout.nb_channels, s->analysis_rdft_len, s->rdft_len, s->fir_len, s->nsamples_max);
    
    if (s->fixed)
        l->min_samples = l->max_samples = s->nsamples_max;

    return generate_kernel(ctx, SELECT_GAIN(s), SELECT_GAIN_ENTRY(s));
}
