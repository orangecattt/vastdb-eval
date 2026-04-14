#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)

#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#endif

#define AV_NUM_DATA_POINTERS 8

#define BIT_SHIFT 15

static const float FILTER_5[5] = {
    0.054488685,
    0.244201342,
    0.402619947,
    0.244201342,
    0.054488685
};

typedef struct AVRational{
    int num;
    int den;
} AVRational;

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

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1,
    AVCOL_RANGE_JPEG        = 2,
    AVCOL_RANGE_NB,
};

enum AVColorPrimaries {
    AVCOL_PRI_RESERVED0   = 0,
    AVCOL_PRI_BT709       = 1,
    AVCOL_PRI_UNSPECIFIED = 2,
    AVCOL_PRI_RESERVED    = 3,
    AVCOL_PRI_BT470M      = 4,
    AVCOL_PRI_BT470BG     = 5,
    AVCOL_PRI_SMPTE170M   = 6,
    AVCOL_PRI_SMPTE240M   = 7,
    AVCOL_PRI_FILM        = 8,
    AVCOL_PRI_BT2020      = 9,
    AVCOL_PRI_SMPTE428    = 10,
    AVCOL_PRI_SMPTEST428_1 = AVCOL_PRI_SMPTE428,
    AVCOL_PRI_SMPTE431    = 11,
    AVCOL_PRI_SMPTE432    = 12,
    AVCOL_PRI_EBU3213     = 22,
    AVCOL_PRI_JEDEC_P22   = AVCOL_PRI_EBU3213,
    AVCOL_PRI_NB,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_RESERVED0    = 0,
    AVCOL_TRC_BT709        = 1,
    AVCOL_TRC_UNSPECIFIED  = 2,
    AVCOL_TRC_RESERVED     = 3,
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
    AVCOL_TRC_SMPTE2084    = 16,
    AVCOL_TRC_SMPTEST2084  = AVCOL_TRC_SMPTE2084,
    AVCOL_TRC_SMPTE428     = 17,
    AVCOL_TRC_SMPTEST428_1 = AVCOL_TRC_SMPTE428,
    AVCOL_TRC_ARIB_STD_B67 = 18,
    AVCOL_TRC_NB,
};

enum AVColorSpace {
    AVCOL_SPC_RGB         = 0,
    AVCOL_SPC_BT709       = 1,
    AVCOL_SPC_UNSPECIFIED = 2,
    AVCOL_SPC_RESERVED    = 3,
    AVCOL_SPC_FCC         = 4,
    AVCOL_SPC_BT470BG     = 5,
    AVCOL_SPC_SMPTE170M   = 6,
    AVCOL_SPC_SMPTE240M   = 7,
    AVCOL_SPC_YCGCO       = 8,
    AVCOL_SPC_YCOCG       = AVCOL_SPC_YCGCO,
    AVCOL_SPC_BT2020_NCL  = 9,
    AVCOL_SPC_BT2020_CL   = 10,
    AVCOL_SPC_SMPTE2085   = 11,
    AVCOL_SPC_CHROMA_DERIVED_NCL = 12,
    AVCOL_SPC_CHROMA_DERIVED_CL = 13,
    AVCOL_SPC_ICTCP       = 14,
    AVCOL_SPC_NB,
};

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1,
    AVCHROMA_LOC_CENTER      = 2,
    AVCHROMA_LOC_TOPLEFT     = 3,
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_BOTTOM      = 6,
    AVCHROMA_LOC_NB,
};

typedef struct AVBuffer AVBuffer;

typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    size_t size;
} AVBufferRef;

typedef struct AVDictionaryEntry {
    char *key;
    char *value;
} AVDictionaryEntry;

typedef struct AVDictionary AVDictionary;

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
    void **side_data;
    int            nb_side_data;
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
    int64_t pkt_size;
} AVFrame;

typedef struct AVComponentDescriptor {
    int plane;
    int step;
    int offset;
    int shift;
    int depth;
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

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;

typedef struct AVFilterFormatsConfig {
    AVFilterFormats *formats;
    AVFilterFormats  *samplerates;
    AVFilterChannelLayouts  *channel_layouts;
} AVFilterFormatsConfig;

struct AVFilterLink {
    AVFilterContext *src;
    AVFilterPad *srcpad;
    AVFilterContext *dst;
    AVFilterPad *dstpad;
    enum AVPixelFormat type;
    int w;
    int h;
    AVRational sample_aspect_ratio;
    uint64_t channel_layout;
    int sample_rate;
    int format;
    AVRational time_base;
    AVFilterFormatsConfig incfg;
    AVFilterFormatsConfig outcfg;
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
    int64_t frame_count_in, frame_count_out;
    void *frame_pool;
    int frame_wanted_out;
    AVBufferRef *hw_frames_ctx;
    char reserved[0xF000];
};

struct AVFilterContext {
    const void *av_class;
    const void *filter;
    char *name;
    AVFilterPad   *input_pads;
    AVFilterLink **inputs;
    unsigned    nb_inputs;
    AVFilterPad   *output_pads;
    AVFilterLink **outputs;
    unsigned    nb_outputs;
    void *priv;
    void *graph;
    int thread_type;
    void *internal;
    void *command_queue;
    char *enable_str;
    void *enable;
    double *var_values;
    int is_disabled;
    AVBufferRef *hw_device_ctx;
    int nb_threads;
    unsigned ready;
    int extra_hw_frames;
};

typedef struct VMAFMotionDSPContext {
    uint64_t (*sad)(const uint16_t *img1, const uint16_t *img2, int w, int h,
                    ptrdiff_t img1_stride, ptrdiff_t img2_stride);
    void (*convolution_x)(const uint16_t *filter, int filt_w, const uint16_t *src,
                          uint16_t *dst, int w, int h, ptrdiff_t src_stride,
                          ptrdiff_t dst_stride);
    void (*convolution_y)(const uint16_t *filter, int filt_w, const uint8_t *src,
                          uint16_t *dst, int w, int h, ptrdiff_t src_stride,
                          ptrdiff_t dst_stride);
} VMAFMotionDSPContext;

typedef struct VMAFMotionData {
    uint16_t filter[5];
    int width;
    int height;
    ptrdiff_t stride;
    uint16_t *blur_data[2 /* cur, prev */];
    uint16_t *temp_data;
    double motion_sum;
    uint64_t nb_frames;
    VMAFMotionDSPContext vmafdsp;
} VMAFMotionData;

typedef struct VMAFMotionContext {
    const void *class;
    VMAFMotionData data;
    FILE *stats_file;
    char *stats_file_str;
} VMAFMotionContext;

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);
void *av_malloc(size_t size);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);
int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags);

static uint64_t image_sad(const uint16_t *img1, const uint16_t *img2, int w,
                          int h, ptrdiff_t _img1_stride, ptrdiff_t _img2_stride)
{
    ptrdiff_t img1_stride = _img1_stride / sizeof(*img1);
    ptrdiff_t img2_stride = _img2_stride / sizeof(*img2);
    uint64_t sum = 0;
    int i, j;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            sum += abs(img1[j] - img2[j]);
        }
        img1 += img1_stride;
        img2 += img2_stride;
    }

    return sum;
}

static void convolution_x(const uint16_t *filter, int filt_w, const uint16_t *src,
                          uint16_t *dst, int w, int h, ptrdiff_t _src_stride,
                          ptrdiff_t _dst_stride)
{
    ptrdiff_t src_stride = _src_stride / sizeof(*src);
    ptrdiff_t dst_stride = _dst_stride / sizeof(*dst);
    int radius = filt_w / 2;
    int borders_left = radius;
    int borders_right = w - (filt_w - radius);
    int i, j, k;
    int sum = 0;

    for (i = 0; i < h; i++) {
        for (j = 0; j < borders_left; j++) {
            sum = 0;
            for (k = 0; k < filt_w; k++) {
                int j_tap = FFABS(j - radius + k);
                if (j_tap >= w) {
                    j_tap = w - (j_tap - w + 1);
                }
                sum += filter[k] * src[i * src_stride + j_tap];
            }
            dst[i * dst_stride + j] = sum >> BIT_SHIFT;
        }

        for (j = borders_left; j < borders_right; j++) {
            int sum = 0;
            for (k = 0; k < filt_w; k++) {
                sum += filter[k] * src[i * src_stride + j - radius + k];
            }
            dst[i * dst_stride + j] = sum >> BIT_SHIFT;
        }

        for (j = borders_right; j < w; j++) {
            sum = 0;
            for (k = 0; k < filt_w; k++) {
                int j_tap = FFABS(j - radius + k);
                if (j_tap >= w) {
                    j_tap = w - (j_tap - w + 1);
                }
                sum += filter[k] * src[i * src_stride + j_tap];
            }
            dst[i * dst_stride + j] = sum >> BIT_SHIFT;
        }
    }
}

static void vmafmotiondsp_init(VMAFMotionDSPContext *dsp, int bpp);

static void set_meta(AVDictionary **metadata, const char *key, float d)
{
    char value[128];
    snprintf(value, sizeof(value), "%0.2f", d);
    av_dict_set(metadata, key, value, 0);
}

int ff_vmafmotion_init(VMAFMotionData *s,
                       int w, int h, enum AVPixelFormat fmt)
{
    size_t data_sz;
    int i;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);

    if (w < 3 || h < 3)
        return AVERROR(EINVAL);

    s->width = w;
    s->height = h;
    s->stride = FFALIGN(w * sizeof(uint16_t), 32);

    data_sz = (size_t) s->stride * h;
    if (!(s->blur_data[0] = av_malloc(data_sz)) ||
        !(s->blur_data[1] = av_malloc(data_sz)) ||
        !(s->temp_data    = av_malloc(data_sz))) {
        return AVERROR(ENOMEM);
    }

    for (i = 0; i < 5; i++) {
        s->filter[i] = lrint(FILTER_5[i] * (1 << BIT_SHIFT));
    }

    vmafmotiondsp_init(&s->vmafdsp, desc->comp[0].depth);

    return 0;
}

static int config_input_ref(AVFilterLink *inlink)
{
    AVFilterContext *ctx  = inlink->dst;
    VMAFMotionContext *s = ctx->priv;

    return ff_vmafmotion_init(&s->data, ctx->inputs[0]->w,
                              ctx->inputs[0]->h, ctx->inputs[0]->format);
}

#define conv_y_fn(type, bits) \
static void convolution_y_##bits##bit(const uint16_t *filter, int filt_w, \
                                      const uint8_t *_src, uint16_t *dst, \
                                      int w, int h, ptrdiff_t _src_stride, \
                                      ptrdiff_t _dst_stride) \
{ \
    const type *src = (const type *) _src; \
    ptrdiff_t src_stride = _src_stride / sizeof(*src); \
    ptrdiff_t dst_stride = _dst_stride / sizeof(*dst); \
    int radius = filt_w / 2; \
    int borders_top = radius; \
    int borders_bottom = h - (filt_w - radius); \
    int i, j, k; \
    int sum = 0; \
    \
    for (i = 0; i < borders_top; i++) { \
        for (j = 0; j < w; j++) { \
            sum = 0; \
            for (k = 0; k < filt_w; k++) { \
                int i_tap = FFABS(i - radius + k); \
                if (i_tap >= h) { \
                    i_tap = h - (i_tap - h + 1); \
                } \
                sum += filter[k] * src[i_tap * src_stride + j]; \
            } \
            dst[i * dst_stride + j] = sum >> bits; \
        } \
    } \
    for (i = borders_top; i < borders_bottom; i++) { \
        for (j = 0; j < w; j++) { \
            sum = 0; \
            for (k = 0; k < filt_w; k++) { \
                sum += filter[k] * src[(i - radius + k) * src_stride + j]; \
            } \
            dst[i * dst_stride + j] = sum >> bits; \
        } \
    } \
    for (i = borders_bottom; i < h; i++) { \
        for (j = 0; j < w; j++) { \
            sum = 0; \
            for (k = 0; k < filt_w; k++) { \
                int i_tap = FFABS(i - radius + k); \
                if (i_tap >= h) { \
                    i_tap = h - (i_tap - h + 1); \
                } \
                sum += filter[k] * src[i_tap * src_stride + j]; \
            } \
            dst[i * dst_stride + j] = sum >> bits; \
        } \
    } \
}

conv_y_fn(uint8_t, 8)
conv_y_fn(uint16_t, 10)

static void vmafmotiondsp_init(VMAFMotionDSPContext *dsp, int bpp) {
    dsp->convolution_x = convolution_x;
    dsp->convolution_y = bpp == 10 ? convolution_y_10bit : convolution_y_8bit;
    dsp->sad = image_sad;
}

double ff_vmafmotion_process(VMAFMotionData *s, AVFrame *ref)
{
    double score;

    s->vmafdsp.convolution_y(s->filter, 5, ref->data[0], s->temp_data,
                             s->width, s->height, ref->linesize[0], s->stride);
    s->vmafdsp.convolution_x(s->filter, 5, s->temp_data, s->blur_data[0],
                             s->width, s->height, s->stride, s->stride);

    if (!s->nb_frames) {
        score = 0.0;
    } else {
        uint64_t sad = s->vmafdsp.sad(s->blur_data[1], s->blur_data[0],
                                      s->width, s->height, s->stride, s->stride);
        // the output score is always normalized to 8 bits
        score = (double) (sad * 1.0 / (s->width * s->height << (BIT_SHIFT - 8)));
    }

    FFSWAP(uint16_t *, s->blur_data[0], s->blur_data[1]);
    s->nb_frames++;
    s->motion_sum += score;

    return score;
}

static void do_vmafmotion(AVFilterContext *ctx, AVFrame *ref)
{
    VMAFMotionContext *s = ctx->priv;
    double score;

    score = ff_vmafmotion_process(&s->data, ref);
    set_meta(&ref->metadata, "lavfi.vmafmotion.score", score);
    if (s->stats_file) {
        fprintf(s->stats_file,
                "n:%"PRId64" motion:%0.2lf\n", s->data.nb_frames, score);
    }
}

static int filter_frame(AVFilterLink *inlink, AVFrame *ref)
{
    AVFilterContext *ctx = inlink->dst;
    do_vmafmotion(ctx, ref);
    return ff_filter_frame(ctx->outputs[0], ref);
}
