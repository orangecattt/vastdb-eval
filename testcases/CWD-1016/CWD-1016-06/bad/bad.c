#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __GNUC__
#    define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#endif

#ifndef av_always_inline
#if AV_GCC_VERSION_AT_LEAST(3,1)
#    define av_always_inline __attribute__((always_inline)) inline
#else
#    define av_always_inline inline
#endif
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_const __attribute__((const))
#else
#    define av_const
#endif

#if AV_GCC_VERSION_AT_LEAST(2,6) || defined(__clang__)
#    define av_cold __attribute__((cold))
#else
#    define av_cold
#endif

#if defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#else
#    define av_builtin_constant_p(x) 0
#endif

#ifndef attribute_deprecated
#if defined(__GNUC__) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#else
#    define attribute_deprecated
#endif
#endif

#ifndef av_alloc_size
#if AV_GCC_VERSION_AT_LEAST(3,1)
#    define av_alloc_size(...) __attribute__((alloc_size(__VA_ARGS__)))
#else
#    define av_alloc_size(...)
#endif
#endif

#define FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

#define AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))

#define AV_NOPTS_VALUE          ((int64_t)UINT64_C(0x8000000000000000))

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

typedef struct AVRational{
    int num;
    int den;
} AVRational;

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
    AV_PIX_FMT_YUVJ420P,
    AV_PIX_FMT_YUVJ422P,
    AV_PIX_FMT_YUVJ444P,
    AV_PIX_FMT_YUVJ440P,
    AV_PIX_FMT_YUVJ411P,
    AV_PIX_FMT_YUVA420P,
    AV_PIX_FMT_YUVA422P,
    AV_PIX_FMT_YUVA444P,
    AV_PIX_FMT_GBRP,
    AV_PIX_FMT_GBRAP,
    AV_PIX_FMT_YUV420P9,
    AV_PIX_FMT_YUV422P9,
    AV_PIX_FMT_YUV444P9,
    AV_PIX_FMT_YUV420P10,
    AV_PIX_FMT_YUV422P10,
    AV_PIX_FMT_YUV444P10,
    AV_PIX_FMT_YUV420P12,
    AV_PIX_FMT_YUV422P12,
    AV_PIX_FMT_YUV444P12,
    AV_PIX_FMT_YUV420P14,
    AV_PIX_FMT_YUV422P14,
    AV_PIX_FMT_YUV444P14,
    AV_PIX_FMT_GBRP9,
    AV_PIX_FMT_GBRP10,
    AV_PIX_FMT_GBRP12,
    AV_PIX_FMT_GBRP14,
    AV_PIX_FMT_GBRP16,
    AV_PIX_FMT_GBRAP16,
};

typedef struct AVComponentDescriptor {
    int plane;
    int step;
    int offset;
    int shift;
    int depth;
    attribute_deprecated int step_minus1;
    attribute_deprecated int depth_minus1;
    attribute_deprecated int offset_plus1;
} AVComponentDescriptor;

typedef struct AVPixFmtDescriptor {
    const char *name;
    uint8_t nb_components;
    uint8_t log2_chroma_w;
    uint8_t log2_chroma_h;
    uint64_t flags;
    AVComponentDescriptor comp[4];
    const char *alias;
} AVPixFmtDescriptor;

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);
int av_pix_fmt_count_planes(enum AVPixelFormat pix_fmt);

static av_always_inline av_const int av_clip_c(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}

#define av_clip av_clip_c

#if EDOM > 0
#define AVERROR(e) (-(e))
#define AVUNERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#define AVUNERROR(e) (e)
#endif

typedef struct AVBuffer AVBuffer;
typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    int      size;
    void    (*free)(void *opaque, uint8_t *data);
    void    *opaque;
} AVBufferRef;

typedef struct AVDictionary AVDictionary;

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

enum AVFrameSideDataType {
    AV_FRAME_DATA_PANSCAN,
    AV_FRAME_DATA_A53_CC,
    AV_FRAME_DATA_STEREO3D,
    AV_FRAME_DATA_MATRIXENCODING,
    AV_FRAME_DATA_DOWNMIX_INFO,
    AV_FRAME_DATA_REPLAYGAIN,
    AV_FRAME_DATA_DISPLAYMATRIX,
    AV_FRAME_DATA_AFD,
    AV_FRAME_DATA_MOTION_VECTORS,
    AV_FRAME_DATA_AUDIO_SERVICE_TYPE,
    AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
    AV_FRAME_DATA_GOP_TIMECODE,
    AV_FRAME_DATA_SPHERICAL,
    AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
    AV_FRAME_DATA_ICC_PROFILE,
    AV_FRAME_DATA_QP_TABLE_PROPERTIES,
    AV_FRAME_DATA_QP_TABLE_DATA,
    AV_FRAME_DATA_S12M_TIMECODE,
    AV_FRAME_DATA_DYNAMIC_HDR_PLUS,
    AV_FRAME_DATA_REGIONS_OF_INTEREST,
};

typedef struct AVFrameSideData {
    enum AVFrameSideDataType type;
    uint8_t *data;
    int      size;
    AVDictionary *metadata;
    AVBufferRef *buf;
} AVFrameSideData;

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1,
    AVCOL_RANGE_JPEG        = 2,
    AVCOL_RANGE_NB          = 3,
};

enum AVColorPrimaries {
    AVCOL_PRI_RESERVED0   = 0,
    AVCOL_PRI_BT709       = 1,
    AVCOL_PRI_UNSPECIFIED = 2,
    AVCOL_PRI_BT470M      = 4,
    AVCOL_PRI_BT470BG     = 5,
    AVCOL_PRI_SMPTE170M   = 6,
    AVCOL_PRI_SMPTE240M   = 7,
    AVCOL_PRI_FILM        = 8,
    AVCOL_PRI_BT2020      = 9,
    AVCOL_PRI_NB          = 10,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_RESERVED0    = 0,
    AVCOL_TRC_BT709        = 1,
    AVCOL_TRC_UNSPECIFIED  = 2,
    AVCOL_TRC_GAMMA22      = 4,
    AVCOL_TRC_GAMMA28      = 5,
    AVCOL_TRC_SMPTE170M    = 6,
    AVCOL_TRC_SMPTE240M    = 7,
    AVCOL_TRC_LINEAR       = 8,
    AVCOL_TRC_LOG          = 9,
    AVCOL_TRC_LOG_SQRT     = 10,
    AVCOL_TRC_IEC61966_2_4 = 11,
    AVCOL_TRC_BT1361_ECG   = 12,
    AVCOL_TRC_IEC61966_2_1 = 13,
    AVCOL_TRC_BT2020_10    = 14,
    AVCOL_TRC_BT2020_12    = 15,
    AVCOL_TRC_NB           = 16,
};

enum AVColorSpace {
    AVCOL_SPC_RGB         = 0,
    AVCOL_SPC_BT709       = 1,
    AVCOL_SPC_UNSPECIFIED = 2,
    AVCOL_SPC_FCC         = 4,
    AVCOL_SPC_BT470BG     = 5,
    AVCOL_SPC_SMPTE170M   = 6,
    AVCOL_SPC_SMPTE240M   = 7,
    AVCOL_SPC_YCOCG       = 8,
    AVCOL_SPC_BT2020_NCL  = 9,
    AVCOL_SPC_BT2020_CL   = 10,
    AVCOL_SPC_NB          = 11,
};

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1,
    AVCHROMA_LOC_CENTER      = 2,
    AVCHROMA_LOC_TOPLEFT     = 3,
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_NB          = 6,
};

#define AV_NUM_DATA_POINTERS 8

typedef struct AVFrame {
    uint8_t *data[AV_NUM_DATA_POINTERS];
    int linesize[AV_NUM_DATA_POINTERS];
    uint8_t **extended_data;
    int width, height;
    int nb_samples;
    int format;
    int key_frame;
    enum AVPictureType pict_type;
    AVRational sample_aspect_ratio;
    int64_t pts;
    int64_t pkt_dts;
    int coded_picture_number;
    int display_picture_number;
    int quality;
    void *opaque;
    int repeat_pict;
    int interlaced_frame;
    int top_field_first;
    int palette_has_changed;
    int64_t reordered_opaque;
    int sample_rate;
    uint64_t channel_layout;
    AVBufferRef *buf[AV_NUM_DATA_POINTERS];
    AVBufferRef **extended_buf;
    int        nb_extended_buf;
    AVFrameSideData **side_data;
    int            nb_side_data;
#define AV_FRAME_FLAG_CORRUPT       (1 << 0)
#define AV_FRAME_FLAG_DISCARD   (1 << 2)
    int flags;
    enum AVColorRange color_range;
    enum AVColorPrimaries color_primaries;
    enum AVColorTransferCharacteristic color_trc;
    enum AVColorSpace colorspace;
    enum AVChromaLocation chroma_location;
    int64_t best_effort_timestamp;
    int64_t pkt_pos;
    int64_t pkt_duration;
    AVDictionary *metadata;
    int decode_error_flags;
    int channels;
    int pkt_size;
    AVBufferRef *hw_frames_ctx;
    AVBufferRef *opaque_ref;
    size_t crop_top;
    size_t crop_bottom;
    size_t crop_left;
    size_t crop_right;
    AVBufferRef *private_ref;
} AVFrame;

AVFrame *av_frame_alloc(void);
void av_frame_free(AVFrame **frame);
int av_frame_ref(AVFrame *dst, const AVFrame *src);
AVFrame *av_frame_clone(const AVFrame *src);
void av_frame_unref(AVFrame *frame);
int av_frame_copy(AVFrame *dst, const AVFrame *src);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
void *av_calloc(size_t nmemb, size_t size) av_alloc_size(1, 2);
#define av_malloc_attrib
void av_freep(void *ptr);
int av_image_fill_linesizes(int linesizes[4], enum AVPixelFormat pix_fmt, int width);

#define ARCH_X86 1

typedef struct AVClass AVClass;
typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterInternal AVFilterInternal;
typedef struct AVFilterGraph   AVFilterGraph;
typedef struct AVFilterCommand AVFilterCommand;
typedef struct AVFilter AVFilter;

struct AVFilter {
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
    AVFilter *next;
    int (*process_command)(AVFilterContext *, const char *cmd, const char *arg, char *res, int res_len, int flags);
    int (*init_opaque)(AVFilterContext *ctx, void *opaque);
    int (*activate)(AVFilterContext *ctx);
};

#define AVFILTER_FLAG_DYNAMIC_INPUTS        (1 << 0)
#define AVFILTER_FLAG_DYNAMIC_OUTPUTS       (1 << 1)
#define AVFILTER_FLAG_SLICE_THREADS         (1 << 2)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC  (1 << 16)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL (1 << 17)
#define AVFILTER_FLAG_SUPPORT_TIMELINE (AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC | AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL)

typedef int (avfilter_action_func)(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs);
typedef int (avfilter_execute_func)(AVFilterContext *ctx, avfilter_action_func *func,
                                    void *arg, int *ret, int nb_jobs);

struct AVFilterInternal {
    avfilter_execute_func *execute;
};

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
    struct AVFilterGraph *graph;
    int thread_type;
    AVFilterInternal *internal;
    struct AVFilterCommand *command_queue;
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
    AVBufferRef *hw_frames_ctx;
    char reserved[0xF000];
};

int ff_filter_get_nb_threads(AVFilterContext *ctx);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);

typedef struct W3FDIFDSPContext {
    void (*filter_simple_low)(int32_t *work_line,
                              uint8_t *in_lines_cur[2],
                              const int16_t *coef, int linesize);
    void (*filter_complex_low)(int32_t *work_line,
                               uint8_t *in_lines_cur[4],
                               const int16_t *coef, int linesize);
    void (*filter_simple_high)(int32_t *work_line,
                               uint8_t *in_lines_cur[3],
                               uint8_t *in_lines_adj[3],
                               const int16_t *coef, int linesize);
    void (*filter_complex_high)(int32_t *work_line,
                                uint8_t *in_lines_cur[5],
                                uint8_t *in_lines_adj[5],
                                const int16_t *coef, int linesize);
    void (*filter_scale)(uint8_t *out_pixel, const int32_t *work_pixel,
                         int linesize, int max);
} W3FDIFDSPContext;

void ff_w3fdif_init_x86(W3FDIFDSPContext *dsp, int depth);

typedef struct W3FDIFContext {
    const AVClass *class;
    int filter;
    int deint;
    int linesize[4];
    int planeheight[4];
    int field;
    int eof;
    int nb_planes;
    AVFrame *prev, *cur, *next;
    int32_t **work_line;
    int nb_threads;
    int max;
    W3FDIFDSPContext dsp;
} W3FDIFContext;

typedef struct ThreadData {
    AVFrame *out, *cur, *adj;
    int plane;
} ThreadData;

static const int8_t   n_coef_lf[2] = { 2, 4 };
static const int16_t coef_lf[2][4] = {{ 16384, 16384,     0,    0},
                                      {  -852, 17236, 17236, -852}};
static const int8_t   n_coef_hf[2] = { 3, 5 };
static const int16_t coef_hf[2][5] = {{ -2048,  4096, -2048,     0,    0},
                                      {  1016, -3801,  5570, -3801, 1016}};

void filter_simple_low(int32_t *work_line, uint8_t *in_lines_cur[2], const int16_t *coef, int linesize);
void filter_complex_low(int32_t *work_line, uint8_t *in_lines_cur[4], const int16_t *coef, int linesize);
void filter_simple_high(int32_t *work_line, uint8_t *in_lines_cur[3], uint8_t *in_lines_adj[3], const int16_t *coef, int linesize);
void filter_complex_high(int32_t *work_line, uint8_t *in_lines_cur[5], uint8_t *in_lines_adj[5], const int16_t *coef, int linesize);
void filter_scale(uint8_t *out_pixel, const int32_t *work_pixel, int linesize, int max);
void filter16_simple_low(int32_t *work_line, uint8_t *in_lines_cur8[2], const int16_t *coef, int linesize);
void filter16_simple_high(int32_t *work_line, uint8_t *in_lines_cur8[3], uint8_t *in_lines_adj8[3], const int16_t *coef, int linesize);
void filter16_complex_high(int32_t *work_line, uint8_t *in_lines_cur8[5], uint8_t *in_lines_adj8[5], const int16_t *coef, int linesize);
void filter16_scale(uint8_t *out_pixel8, const int32_t *work_pixel, int linesize, int max);

static void filter16_complex_low(int32_t *work_line,
                                 uint8_t *in_lines_cur8[4],
                                 const int16_t *coef, int linesize)
{
    uint16_t *in_lines_cur[4] = { (uint16_t *)in_lines_cur8[0],
                                  (uint16_t *)in_lines_cur8[1],
                                  (uint16_t *)in_lines_cur8[2],
                                  (uint16_t *)in_lines_cur8[3] };
    int i;

    linesize /= 2;
    for (i = 0; i < linesize; i++) {
        *work_line    = *in_lines_cur[0]++ * coef[0];
        *work_line   += *in_lines_cur[1]++ * coef[1];
        *work_line   += *in_lines_cur[2]++ * coef[2];
        *work_line++ += *in_lines_cur[3]++ * coef[3];
    }
}

static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    W3FDIFContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int ret, i, depth;

    if ((ret = av_image_fill_linesizes(s->linesize, inlink->format, inlink->w)) < 0)
        return ret;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);
    s->nb_threads = ff_filter_get_nb_threads(ctx);
    s->work_line = av_calloc(s->nb_threads, sizeof(*s->work_line));
    if (!s->work_line)
        return AVERROR(ENOMEM);

    for (i = 0; i < s->nb_threads; i++) {
        s->work_line[i] = av_calloc(FFALIGN(s->linesize[0], 32), sizeof(*s->work_line[0]));
        if (!s->work_line[i])
            return AVERROR(ENOMEM);
    }

    depth = desc->comp[0].depth;
    s->max = ((1 << depth) - 1) * 256 * 128;
    if (depth <= 8) {
        s->dsp.filter_simple_low   = filter_simple_low;
        s->dsp.filter_complex_low  = filter_complex_low;
        s->dsp.filter_simple_high  = filter_simple_high;
        s->dsp.filter_complex_high = filter_complex_high;
        s->dsp.filter_scale        = filter_scale;
    } else {
        s->dsp.filter_simple_low   = filter16_simple_low;
        s->dsp.filter_complex_low  = filter16_complex_low;
        s->dsp.filter_simple_high  = filter16_simple_high;
        s->dsp.filter_complex_high = filter16_complex_high;
        s->dsp.filter_scale        = filter16_scale;
    }

    if (ARCH_X86)
        ff_w3fdif_init_x86(&s->dsp, depth);

    return 0;
}

static int deinterlace_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    W3FDIFContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *out = td->out;
    AVFrame *cur = td->cur;
    AVFrame *adj = td->adj;
    const int plane = td->plane;
    const int filter = s->filter;
    uint8_t *in_line, *in_lines_cur[5], *in_lines_adj[5];
    uint8_t *out_line, *out_pixel;
    int32_t *work_line, *work_pixel;
    uint8_t *cur_data = cur->data[plane];
    uint8_t *adj_data = adj->data[plane];
    uint8_t *dst_data = out->data[plane];
    const int linesize = s->linesize[plane];
    const int height   = s->planeheight[plane];
    const int cur_line_stride = cur->linesize[plane];
    const int adj_line_stride = adj->linesize[plane];
    const int dst_line_stride = out->linesize[plane];
    const int start = (height * jobnr) / nb_jobs;
    const int end = (height * (jobnr+1)) / nb_jobs;
    const int max = s->max;
    int j, y_in, y_out;

    /* copy unchanged the lines of the field */
    y_out = start + ((s->field == cur->top_field_first) ^ (start & 1));

    in_line  = cur_data + (y_out * cur_line_stride);
    out_line = dst_data + (y_out * dst_line_stride);

    while (y_out < end) {
        memcpy(out_line, in_line, linesize);
        y_out += 2;
        in_line  += cur_line_stride * 2;
        out_line += dst_line_stride * 2;
    }

    /* interpolate other lines of the field */
    y_out = start + ((s->field != cur->top_field_first) ^ (start & 1));

    out_line = dst_data + (y_out * dst_line_stride);

    while (y_out < end) {
        /* get low vertical frequencies from current field */
        for (j = 0; j < n_coef_lf[filter]; j++) {
            y_in = (y_out + 1) + (j * 2) - n_coef_lf[filter];

            while (y_in < 0)
                y_in += 2;
            while (y_in >= height)
                y_in -= 2;

            in_lines_cur[j] = cur_data + (y_in * cur_line_stride);
        }

        work_line = s->work_line[jobnr];
        switch (n_coef_lf[filter]) {
        case 2:
            s->dsp.filter_simple_low(work_line, in_lines_cur,
                                     coef_lf[filter], linesize);
            break;
        case 4:
            s->dsp.filter_complex_low(work_line, in_lines_cur,
                                      coef_lf[filter], linesize);
        }

        /* get high vertical frequencies from adjacent fields */
        for (j = 0; j < n_coef_hf[filter]; j++) {
            y_in = (y_out + 1) + (j * 2) - n_coef_hf[filter];

            while (y_in < 0)
                y_in += 2;
            while (y_in >= height)
                y_in -= 2;

            in_lines_cur[j] = cur_data + (y_in * cur_line_stride);
            in_lines_adj[j] = adj_data + (y_in * adj_line_stride);
        }

        work_line = s->work_line[jobnr];
        switch (n_coef_hf[filter]) {
        case 3:
            s->dsp.filter_simple_high(work_line, in_lines_cur, in_lines_adj,
                                      coef_hf[filter], linesize);
            break;
        case 5:
            s->dsp.filter_complex_high(work_line, in_lines_cur, in_lines_adj,
                                       coef_hf[filter], linesize);
        }

        /* save scaled result to the output frame, scaling down by 256 * 128 */
        work_pixel = s->work_line[jobnr];
        out_pixel = out_line;

        s->dsp.filter_scale(out_pixel, work_pixel, linesize, max);

        /* move on to next line */
        y_out += 2;
        out_line += dst_line_stride * 2;
    }

    return 0;
}

static int filter(AVFilterContext *ctx, int is_second)
{
    W3FDIFContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out, *adj;
    ThreadData td;
    int plane;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out)
        return AVERROR(ENOMEM);
    av_frame_copy_props(out, s->cur);
    out->interlaced_frame = 0;

    if (!is_second) {
        if (out->pts != AV_NOPTS_VALUE)
            out->pts *= 2;
    } else {
        int64_t cur_pts  = s->cur->pts;
        int64_t next_pts = s->next->pts;

        if (next_pts != AV_NOPTS_VALUE && cur_pts != AV_NOPTS_VALUE) {
            out->pts = cur_pts + next_pts;
        } else {
            out->pts = AV_NOPTS_VALUE;
        }
    }

    adj = s->field ? s->next : s->prev;
    td.out = out; td.cur = s->cur; td.adj = adj;
    for (plane = 0; plane < s->nb_planes; plane++) {
        td.plane = plane;
        ctx->internal->execute(ctx, deinterlace_slice, &td, NULL, FFMIN(s->planeheight[plane], s->nb_threads));
    }

    s->field = !s->field;

    return ff_filter_frame(outlink, out);
}

static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    W3FDIFContext *s = ctx->priv;
    int ret;

    av_frame_free(&s->prev);
    s->prev = s->cur;
    s->cur  = s->next;
    s->next = frame;

    if (!s->cur) {
        s->cur = av_frame_clone(s->next);
        if (!s->cur)
            return AVERROR(ENOMEM);
    }

    if ((s->deint && !s->cur->interlaced_frame) || ctx->is_disabled) {
        AVFrame *out = av_frame_clone(s->cur);
        if (!out)
            return AVERROR(ENOMEM);

        av_frame_free(&s->prev);
        if (out->pts != AV_NOPTS_VALUE)
            out->pts *= 2;
        return ff_filter_frame(ctx->outputs[0], out);
    }

    if (!s->prev)
        return 0;

    ret = filter(ctx, 0);
    if (ret < 0)
        return ret;

    return filter(ctx, 1);
}
