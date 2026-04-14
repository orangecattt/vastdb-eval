#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define inline __inline__
#define av_always_inline inline
#define av_const const

#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#define AV_CEIL_RSHIFT(a,b) (((a) + (1<<(b)) - 1) >> (b))

#define AVERROR(e) (-(e))
#define EINVAL 22
#define AV_LOG_ERROR 16
#define ARCH_X86 1

static av_always_inline av_const int av_clip_c(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}

#define av_clip av_clip_c

void emms_c(void);

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVBuffer AVBuffer;
typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    size_t   size;
} AVBufferRef;

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_YUYV422,
    AV_PIX_FMT_RGB24,
    AV_PIX_FMT_BGR24,
    AV_PIX_FMT_YUV422P,
    AV_PIX_FMT_YUV444P,
    AV_PIX_FMT_YUV410P,
    AV_PIX_FMT_YUV411P,
    AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_MONOWHITE,
    AV_PIX_FMT_MONOBLACK,
    AV_PIX_FMT_PAL8,
    AV_PIX_FMT_YUVJ420P,
    AV_PIX_FMT_YUVJ422P,
    AV_PIX_FMT_YUVJ444P,
    AV_PIX_FMT_UYVY422,
    AV_PIX_FMT_UYYVYY411,
    AV_PIX_FMT_BGR8,
    AV_PIX_FMT_BGR4,
    AV_PIX_FMT_BGR4_BYTE,
    AV_PIX_FMT_RGB8,
    AV_PIX_FMT_RGB4,
    AV_PIX_FMT_RGB4_BYTE,
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_NV21,
    AV_PIX_FMT_GRAY16BE,
    AV_PIX_FMT_GRAY16LE,
    AV_PIX_FMT_YUV440P,
    AV_PIX_FMT_YUVJ440P,
    AV_PIX_FMT_YUVA420P,
    AV_PIX_FMT_YUVA422P,
    AV_PIX_FMT_RGB48BE,
    AV_PIX_FMT_RGB48LE,
    AV_PIX_FMT_RGB565BE,
    AV_PIX_FMT_RGB565LE,
    AV_PIX_FMT_RGB555BE,
    AV_PIX_FMT_RGB555LE,
    AV_PIX_FMT_BGR565BE,
    AV_PIX_FMT_BGR565LE,
    AV_PIX_FMT_BGR555BE,
    AV_PIX_FMT_BGR555LE,
    AV_PIX_FMT_YUV420P16LE,
    AV_PIX_FMT_YUV420P16BE,
    AV_PIX_FMT_YUV422P16LE,
    AV_PIX_FMT_YUV422P16BE,
    AV_PIX_FMT_YUV444P16LE,
    AV_PIX_FMT_YUV444P16BE,
    AV_PIX_FMT_RGB444LE,
    AV_PIX_FMT_RGB444BE,
    AV_PIX_FMT_BGR444LE,
    AV_PIX_FMT_BGR444BE,
    AV_PIX_FMT_YA8,
    AV_PIX_FMT_YA16BE,
    AV_PIX_FMT_YA16LE,
    AV_PIX_FMT_GBRP,
    AV_PIX_FMT_GBRP9BE,
    AV_PIX_FMT_GBRP9LE,
    AV_PIX_FMT_GBRP10BE,
    AV_PIX_FMT_GBRP10LE,
    AV_PIX_FMT_GBRP16BE,
    AV_PIX_FMT_GBRP16LE,
    AV_PIX_FMT_YUVA444P,
    AV_PIX_FMT_YUV420P9LE,
    AV_PIX_FMT_YUV420P9BE,
    AV_PIX_FMT_YUV420P10LE,
    AV_PIX_FMT_YUV420P10BE,
    AV_PIX_FMT_YUV422P9LE,
    AV_PIX_FMT_YUV422P9BE,
    AV_PIX_FMT_YUV422P10LE,
    AV_PIX_FMT_YUV422P10BE,
    AV_PIX_FMT_YUV444P9LE,
    AV_PIX_FMT_YUV444P9BE,
    AV_PIX_FMT_YUV444P10LE,
    AV_PIX_FMT_YUV444P10BE,
    AV_PIX_FMT_GBRP12BE,
    AV_PIX_FMT_GBRP12LE,
    AV_PIX_FMT_GBRAP,
    AV_PIX_FMT_GBRAP16BE,
    AV_PIX_FMT_GBRAP16LE,
    AV_PIX_FMT_YUVJ411P,
    AV_PIX_FMT_BAYER_BGGR8,
    AV_PIX_FMT_BAYER_RGGB8,
    AV_PIX_FMT_BAYER_GBRG8,
    AV_PIX_FMT_BAYER_GRBG8,
    AV_PIX_FMT_GBRP14BE,
    AV_PIX_FMT_GBRP14LE,
    AV_PIX_FMT_YUV420P12BE,
    AV_PIX_FMT_YUV420P12LE,
    AV_PIX_FMT_YUV420P14BE,
    AV_PIX_FMT_YUV420P14LE,
    AV_PIX_FMT_YUV422P12BE,
    AV_PIX_FMT_YUV422P12LE,
    AV_PIX_FMT_YUV422P14BE,
    AV_PIX_FMT_YUV422P14LE,
    AV_PIX_FMT_YUV444P12BE,
    AV_PIX_FMT_YUV444P12LE,
    AV_PIX_FMT_YUV444P14BE,
    AV_PIX_FMT_YUV444P14LE,
};

enum AVColorSpace {
    AVCOL_SPC_UNSPECIFIED   =  0,
    AVCOL_SPC_RGB           =  1,
    AVCOL_SPC_BT470M        =  2,
    AVCOL_SPC_BT470BG       =  3,
    AVCOL_SPC_SMPTE170M     =  4,
    AVCOL_SPC_SMPTE240M     =  5,
    AVCOL_SPC_YCOCG         =  6,
    AVCOL_SPC_BT2020_NCL    =  7,
    AVCOL_SPC_BT2020_CL     =  8,
    AVCOL_SPC_NB,
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED =  0,
    AVCOL_RANGE_MPEG        =  1,
    AVCOL_RANGE_JPEG        =  2,
    AVCOL_RANGE_NB,
};

enum AVColorPrimaries {
    AVCOL_PRI_UNSPECIFIED   =  0,
    AVCOL_PRI_BT709         =  1,
    AVCOL_PRI_BT470M        =  2,
    AVCOL_PRI_BT470BG       =  3,
    AVCOL_PRI_SMPTE170M     =  4,
    AVCOL_PRI_SMPTE240M     =  5,
    AVCOL_PRI_FILM          =  6,
    AVCOL_PRI_BT2020        =  7,
    AVCOL_PRI_NB,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_UNSPECIFIED   =  0,
    AVCOL_TRC_BT709         =  1,
    AVCOL_TRC_GAMMA22       =  2,
    AVCOL_TRC_GAMMA28       =  3,
    AVCOL_TRC_SMPTE170M     =  4,
    AVCOL_TRC_SMPTE240M     =  5,
    AVCOL_TRC_LINEAR        =  6,
    AVCOL_TRC_LOG           =  7,
    AVCOL_TRC_LOG_SQRT      =  8,
    AVCOL_TRC_IEC61966_2_4  =  9,
    AVCOL_TRC_NB,
};

typedef struct AVFrame {
    uint8_t *data[8];
    int      linesize[8];
    uint8_t **extended_data;
    int      width, height;
    int      nb_samples;
    int      key_frame;
    enum AVPixelFormat format;
    int64_t pts;
    int64_t pkt_dts;
    int64_t pkt_pos;
    int64_t pkt_duration;
    int      pict_type;
    int      sample_rate;
    int      coded_width;
    int      coded_height;
    enum AVColorSpace colorspace;
    enum AVColorRange color_range;
    AVBufferRef *hw_frames_ctx;
    int      decode_error_flags;
    int      flags;
    int      best_effort_timestamp;
    int64_t  reordered_opaque;
    int      display_picture_number;
    int      repeat_pict;
    enum AVColorPrimaries color_primaries;
    enum AVColorTransferCharacteristic color_trc;
    int      chroma_location;
} AVFrame;

typedef struct AVComponentDescriptor {
    unsigned plane  : 2;
    unsigned step   : 4;
    unsigned offset : 8;
    unsigned shift  : 4;
    unsigned depth  : 6;
} AVComponentDescriptor;

typedef struct AVPixFmtDescriptor {
    const char *name;
    uint8_t nb_components;
    uint8_t log2_chroma_w;
    uint8_t log2_chroma_h;
    uint8_t flags;
    AVComponentDescriptor comp[4];
} AVPixFmtDescriptor;

typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVClass AVClass;
typedef struct AVFilter AVFilter;
typedef struct AVFilterCommand AVFilterCommand;
typedef struct AVDictionary AVDictionary;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterInternal AVFilterInternal;

struct AVFilterLink;

struct AVFilterContext {
    const AVClass *av_class;
    const AVFilter *filter;
    char *name;
    AVFilterPad   *input_pads;
    AVFilterLink **inputs;
    unsigned    nb_inputs;
    AVFilterPad   *output_pads;
    AVFilterLink **outputs;
    unsigned    nb_outputs;
    void *priv;
    AVFilterGraph *graph;
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

struct AVFilterInternal {
    int (*execute)(struct AVFilterContext *ctx, int (*func)(struct AVFilterContext *, void *, int, int),
                   void *arg, int *ret, int nb_jobs);
};

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

struct AVFilterLink {
    struct AVFilterContext *src;
    AVFilterPad *srcpad;
    struct AVFilterContext *dst;
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
    AVFilterGraph *graph;
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
    AVBufferRef *hw_frames_ctx;
    char reserved[0xF000];
};

enum YADIFMode {
    YADIF_MODE_SEND_FRAME           = 0,
    YADIF_MODE_SEND_FIELD           = 1,
    YADIF_MODE_SEND_FRAME_NOSPATIAL = 2,
    YADIF_MODE_SEND_FIELD_NOSPATIAL = 3,
};

enum YADIFParity {
    YADIF_PARITY_TFF  =  0,
    YADIF_PARITY_BFF  =  1,
    YADIF_PARITY_AUTO = -1,
};

enum YADIFDeint {
    YADIF_DEINT_ALL        = 0,
    YADIF_DEINT_INTERLACED = 1,
};

enum YADIFCurrentField {
    YADIF_FIELD_BACK_END = -1,
    YADIF_FIELD_END      =  0,
    YADIF_FIELD_NORMAL   =  1,
};

typedef struct YADIFContext {
    const AVClass *class;
    int mode;
    int parity;
    int deint;
    int frame_pending;
    AVFrame *cur;
    AVFrame *next;
    AVFrame *prev;
    AVFrame *out;
    void (*filter)(struct AVFilterContext *ctx, AVFrame *dstpic, int parity, int tff);
    void (*filter_line)(void *dst, void *prev, void *cur, void *next, int w, int prefs, int mrefs, int parity, int mode);
    void (*filter_edges)(void *dst, void *prev, void *cur, void *next, int w, int prefs, int mrefs, int parity, int mode);
    const AVPixFmtDescriptor *csp;
    int eof;
    uint8_t *temp_line;
    int temp_line_size;
    int current_field;
} YADIFContext;

typedef struct BWDIFContext {
    YADIFContext yadif;
    void (*filter_intra)(void *dst1, void *cur1, int w, int prefs, int mrefs,
                         int prefs3, int mrefs3, int parity, int clip_max);
    void (*filter_line)(void *dst, void *prev, void *cur, void *next,
                        int w, int prefs, int mrefs, int prefs2, int mrefs2,
                        int prefs3, int mrefs3, int prefs4, int mrefs4,
                        int parity, int clip_max);
    void (*filter_edge)(void *dst, void *prev, void *cur, void *next,
                        int w, int prefs, int mrefs, int prefs2, int mrefs2,
                        int parity, int clip_max, int spat);
} BWDIFContext;

typedef struct ThreadData {
    AVFrame *frame;
    int plane;
    int w, h;
    int parity;
    int tff;
} ThreadData;

static const uint16_t coef_sp[2] = { 5077, 981 };

AVRational av_mul_q(AVRational b, AVRational c);

void av_log(void *avcl, int level, const char *fmt, ...);

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);

int ff_filter_get_nb_threads(struct AVFilterContext *ctx);

void ff_bwdif_init_x86(BWDIFContext *bwdif);

static void filter_intra(void *dst1, void *cur1, int w, int prefs, int mrefs,
                         int prefs3, int mrefs3, int parity, int clip_max);
static void filter_line_c(void *dst1, void *prev1, void *cur1, void *next1,
                          int w, int prefs, int mrefs, int prefs2, int mrefs2,
                          int prefs3, int mrefs3, int prefs4, int mrefs4,
                          int parity, int clip_max);
static void filter_edge(void *dst1, void *prev1, void *cur1, void *next1,
                        int w, int prefs, int mrefs, int prefs2, int mrefs2,
                        int parity, int clip_max, int spat);
static void filter_intra_16bit(void *dst1, void *cur1, int w, int prefs, int mrefs,
                               int prefs3, int mrefs3, int parity, int clip_max);
static void filter_line_c_16bit(void *dst1, void *prev1, void *cur1, void *next1,
                                int w, int prefs, int mrefs, int prefs2, int mrefs2,
                                int prefs3, int mrefs3, int prefs4, int mrefs4,
                                int parity, int clip_max);
static void filter_edge_16bit(void *dst1, void *prev1, void *cur1, void *next1,
                              int w, int prefs, int mrefs, int prefs2, int mrefs2,
                              int parity, int clip_max, int spat);
static int filter_slice(struct AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs);
static void filter(struct AVFilterContext *ctx, AVFrame *dstpic, int parity, int tff);
static int config_props(struct AVFilterLink *link);

#define FILTER_INTRA() \
    for (x = 0; x < w; x++) { \
        interpol = (coef_sp[0] * (cur[mrefs] + cur[prefs]) - coef_sp[1] * (cur[mrefs3] + cur[prefs3])) >> 13; \
        dst[0] = av_clip(interpol, 0, clip_max); \
 \
        dst++; \
        cur++; \
    }

static void filter_intra(void *dst1, void *cur1, int w, int prefs, int mrefs,
                         int prefs3, int mrefs3, int parity, int clip_max)
{
    uint8_t *dst = dst1;
    uint8_t *cur = cur1;
    int interpol, x;

    FILTER_INTRA()
}

static int config_props(struct AVFilterLink *link)
{
    struct AVFilterContext *ctx = link->src;
    BWDIFContext *s = link->src->priv;
    YADIFContext *yadif = &s->yadif;

    link->time_base.num = link->src->inputs[0]->time_base.num;
    link->time_base.den = link->src->inputs[0]->time_base.den * 2;
    link->w             = link->src->inputs[0]->w;
    link->h             = link->src->inputs[0]->h;

    if(yadif->mode&1)
        link->frame_rate = av_mul_q(link->src->inputs[0]->frame_rate, (AVRational){2,1});

    if (link->w < 3 || link->h < 4) {
        av_log(ctx, AV_LOG_ERROR, "Video of less than 3 columns or 4 lines is not supported\n");
        return AVERROR(EINVAL);
    }

    yadif->csp = av_pix_fmt_desc_get(link->format);
    yadif->filter = filter;
    if (yadif->csp->comp[0].depth > 8) {
        s->filter_intra = filter_intra_16bit;
        s->filter_line  = filter_line_c_16bit;
        s->filter_edge  = filter_edge_16bit;
    } else {
        s->filter_intra = filter_intra;
        s->filter_line  = filter_line_c;
        s->filter_edge  = filter_edge;
    }

    if (ARCH_X86)
        ff_bwdif_init_x86(s);

    return 0;
}

static int filter_slice(struct AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    BWDIFContext *s = ctx->priv;
    YADIFContext *yadif = &s->yadif;
    ThreadData *td  = arg;
    int linesize = yadif->cur->linesize[td->plane];
    int clip_max = (1 << (yadif->csp->comp[td->plane].depth)) - 1;
    int df = (yadif->csp->comp[td->plane].depth + 7) / 8;
    int refs = linesize / df;
    int slice_start = (td->h *  jobnr   ) / nb_jobs;
    int slice_end   = (td->h * (jobnr+1)) / nb_jobs;
    int y;

    for (y = slice_start; y < slice_end; y++) {
        if ((y ^ td->parity) & 1) {
            uint8_t *prev = &yadif->prev->data[td->plane][y * linesize];
            uint8_t *cur  = &yadif->cur ->data[td->plane][y * linesize];
            uint8_t *next = &yadif->next->data[td->plane][y * linesize];
            uint8_t *dst  = &td->frame->data[td->plane][y * td->frame->linesize[td->plane]];
            if (yadif->current_field == YADIF_FIELD_END) {
                s->filter_intra(dst, cur, td->w, (y + df) < td->h ? refs : -refs,
                                y > (df - 1) ? -refs : refs,
                                (y + 3*df) < td->h ? 3 * refs : -refs,
                                y > (3*df - 1) ? -3 * refs : refs,
                                td->parity ^ td->tff, clip_max);
            } else if ((y < 4) || ((y + 5) > td->h)) {
                s->filter_edge(dst, prev, cur, next, td->w,
                               (y + df) < td->h ? refs : -refs,
                               y > (df - 1) ? -refs : refs,
                               refs << 1, -(refs << 1),
                               td->parity ^ td->tff, clip_max,
                               (y < 2) || ((y + 3) > td->h) ? 0 : 1);
            } else {
                s->filter_line(dst, prev, cur, next, td->w,
                               refs, -refs, refs << 1, -(refs << 1),
                               3 * refs, -3 * refs, refs << 2, -(refs << 2),
                               td->parity ^ td->tff, clip_max);
            }
        } else {
            memcpy(&td->frame->data[td->plane][y * td->frame->linesize[td->plane]],
                   &yadif->cur->data[td->plane][y * linesize], td->w * df);
        }
    }
    return 0;
}

static void filter(struct AVFilterContext *ctx, AVFrame *dstpic,
                   int parity, int tff)
{
    BWDIFContext *bwdif = ctx->priv;
    YADIFContext *yadif = &bwdif->yadif;
    ThreadData td = { .frame = dstpic, .parity = parity, .tff = tff };
    int i;

    for (i = 0; i < yadif->csp->nb_components; i++) {
        int w = dstpic->width;
        int h = dstpic->height;

        if (i == 1 || i == 2) {
            w = AV_CEIL_RSHIFT(w, yadif->csp->log2_chroma_w);
            h = AV_CEIL_RSHIFT(h, yadif->csp->log2_chroma_h);
        }

        td.w     = w;
        td.h     = h;
        td.plane = i;

        ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(h, ff_filter_get_nb_threads(ctx)));
    }
    if (yadif->current_field == YADIF_FIELD_END) {
        yadif->current_field = YADIF_FIELD_NORMAL;
    }

    emms_c();
}
