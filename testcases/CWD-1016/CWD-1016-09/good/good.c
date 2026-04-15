#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#define AVERROR(e) (-(e))
#define ENOMEM 12

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

#define AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))

#define AV_RN16A(p) AV_RNA(16, p)

#define AV_RNA(s, p)    (((const av_alias##s*)(p))->u##s)

typedef union av_alias16 {
    uint16_t u16;
    uint8_t  u8[2];
} av_alias16;

typedef union av_alias32 {
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8[4];
} av_alias32;

typedef union av_alias64 {
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8[8];
} av_alias64;

#if defined(__GNUC__)
#define AV_ALIAS __attribute__((may_alias))
#else
#define AV_ALIAS
#endif

typedef AV_ALIAS union { uint16_t l; } av_alias;

#define AV_NUM_DATA_POINTERS 8

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

typedef struct AVDictionary AVDictionary;

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1,
    AVCOL_RANGE_JPEG        = 2,
    AVCOL_RANGE_NB              ,
};

enum AVColorPrimaries {
    AVCOL_PRI_UNSPECIFIED    = 0,
    AVCOL_PRI_BT709          = 1,
    AVCOL_PRI_BT470M         = 4,
    AVCOL_PRI_BT470BG        = 5,
    AVCOL_PRI_SMPTE170M      = 6,
    AVCOL_PRI_SMPTE240M      = 7,
    AVCOL_PRI_FILM           = 8,
    AVCOL_PRI_BT2020         = 9,
    AVCOL_PRI_SMPTE428       = 10,
    AVCOL_PRI_SMPTEST428_1   = 10,
    AVCOL_PRI_SMPTE431       = 11,
    AVCOL_PRI_SMPTE432       = 12,
    AVCOL_PRI_JEDEC_P22      = 22,
    AVCOL_PRI_NB                 ,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_UNSPECIFIED    = 0,
    AVCOL_TRC_BT709          = 1,
    AVCOL_TRC_GAMMA22        = 2,
    AVCOL_TRC_GAMMA28        = 3,
    AVCOL_TRC_SMPTE170M      = 4,
    AVCOL_TRC_SMPTE240M      = 5,
    AVCOL_TRC_LINEAR         = 6,
    AVCOL_TRC_LOG            = 7,
    AVCOL_TRC_LOG_SQRT       = 8,
    AVCOL_TRC_IEC61966_2_4   = 9,
    AVCOL_TRC_BT1361_ECG     = 10,
    AVCOL_TRC_IEC61966_2_1   = 11,
    AVCOL_TRC_BT2020_10      = 12,
    AVCOL_TRC_BT2020_12      = 13,
    AVCOL_TRC_SMPTE2084      = 14,
    AVCOL_TRC_SMPTEST2084    = 14,
    AVCOL_TRC_SMPTE428       = 15,
    AVCOL_TRC_SMPTEST428_1   = 15,
    AVCOL_TRC_ARIB_STD_B67   = 16,
    AVCOL_TRC_NB                 ,
};

enum AVColorSpace {
    AVCOL_SPC_RGB         = 0,
    AVCOL_SPC_BT709       = 1,
    AVCOL_SPC_FCC         = 4,
    AVCOL_SPC_BT470BG     = 5,
    AVCOL_SPC_SMPTE170M   = 6,
    AVCOL_SPC_SMPTE240M   = 7,
    AVCOL_SPC_YCOCG       = 8,
    AVCOL_SPC_BT2020_NCL  = 9,
    AVCOL_SPC_BT2020_CL   = 10,
    AVCOL_SPC_SMPTE2085   = 11,
    AVCOL_SPC_CHROMA_NCL  = 12,
    AVCOL_SPC_CHROMA_CL   = 13,
    AVCOL_SPC_ICTCP       = 14,
    AVCOL_SPC_NB              ,
};

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1,
    AVCHROMA_LOC_CENTER      = 2,
    AVCHROMA_LOC_TOPLEFT     = 3,
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_BOTTOM      = 6,
    AVCHROMA_LOC_NB              ,
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
};

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
    int pkt_size;
    AVBufferRef *hw_frames_ctx;
    AVBufferRef *opaque_ref;
    size_t crop_top;
    size_t crop_bottom;
    size_t crop_left;
    size_t crop_right;
    AVBufferRef *private_ref;
} AVFrame;

typedef struct AVFilter AVFilter;
typedef struct AVFilterPad AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct FFFrameQueue FFFrameQueue;
typedef struct AVFilterCommand AVFilterCommand;
typedef struct AVClass AVClass;
struct AVFilterInternal;
typedef struct AVPixFmtDescriptor AVPixFmtDescriptor;

typedef struct AVFilterContext {
    const AVClass *av_class;
    const AVFilter *filter;
    char *name;
    AVFilterPad   *input_pads;
    void **inputs;
    unsigned    nb_inputs;
    AVFilterPad   *output_pads;
    void **outputs;
    unsigned    nb_outputs;
    void *priv;
    AVFilterGraph *graph;
    int thread_type;
    struct AVFilterInternal *internal;
    struct AVFilterCommand *command_queue;
    char *enable_str;
    void *enable;
    double *var_values;
    int is_disabled;
    AVBufferRef *hw_device_ctx;
    int nb_threads;
    unsigned ready;
    int extra_hw_frames;
} AVFilterContext;

typedef int (avfilter_action_func)(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs);
typedef int (avfilter_execute_func)(AVFilterContext *ctx, avfilter_action_func *func,
                                    void *arg, int *ret, int nb_jobs);

typedef struct AVFilterInternal {
    avfilter_execute_func *execute;
} AVFilterInternal;

typedef struct AVFilterLink {
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
} AVFilterLink;

typedef struct ThreadData {
    AVFrame *in, *out;
} ThreadData;

typedef struct NContext {
    const AVClass *class;
    int planeheight[4];
    int planewidth[4];
    int nb_planes;
    int threshold[4];
    int coordinates;
    int depth;
    int max;
    int bpc;
    void (*filter)(uint8_t *dst, const uint8_t *p1, int width,
                   int threshold, const uint8_t *coordinates[], int coord,
                   int maxc);
} NContext;

void av_image_copy_plane(uint8_t       *dst, int dst_linesize,
                         const uint8_t *src, int src_linesize,
                         int bytewidth, int height);
void av_frame_free(AVFrame **frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);
int av_pix_fmt_count_planes(enum AVPixelFormat pix_fmt);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);
int ff_filter_get_nb_threads(AVFilterContext *ctx);
int ff_set_common_formats(AVFilterContext *ctx, void *formats);
void *ff_make_format_list(const int *fmts);
static inline int av_builtin_constant_p(unsigned v) { return 0; }

static void deflate16(uint8_t *dstp, const uint8_t *p1, int width,
                      int threshold, const uint8_t *coordinates[], int coord,
                      int maxc)
{
    uint16_t *dst = (uint16_t *)dstp;
    int x, i;

    for (x = 0; x < width; x++) {
        int sum = 0;
        int limit = FFMAX(AV_RN16A(&p1[2 * x]) - threshold, 0);

        for (i = 0; i < 8; sum += AV_RN16A(coordinates[i++] + x * 2));

        dst[x] = FFMAX(FFMIN(sum / 8, AV_RN16A(&p1[2 * x])), limit);
    }
}

static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    NContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *out = td->out;
    AVFrame *in = td->in;
    int plane, y;

    for (plane = 0; plane < s->nb_planes; plane++) {
        const int bpc = s->bpc;
        const int threshold = s->threshold[plane];
        const int stride = in->linesize[plane];
        const int dstride = out->linesize[plane];
        const int height = s->planeheight[plane];
        const int width  = s->planewidth[plane];
        const int slice_start = (height * jobnr) / nb_jobs;
        const int slice_end = (height * (jobnr+1)) / nb_jobs;
        const uint8_t *src = (const uint8_t *)in->data[plane] + slice_start * stride;
        uint8_t *dst = out->data[plane] + slice_start * dstride;

        if (!threshold) {
            av_image_copy_plane(dst, dstride, src, stride, width * bpc, slice_end - slice_start);
            continue;
        }

        for (y = slice_start; y < slice_end; y++) {
            const int nh = y > 0;
            const int ph = y < height - 1;
            const uint8_t *coordinates[] = { src - nh * stride, src + 1 * bpc - nh * stride, src + 2 * bpc - nh * stride,
                                             src,                                            src + 2 * bpc,
                                             src + ph * stride, src + 1 * bpc + ph * stride, src + 2 * bpc + ph * stride};

            const uint8_t *coordinateslb[] = { src + 1 * bpc - nh * stride, src - nh * stride, src + 1 * bpc - nh * stride,
                                               src + 1 * bpc,                                  src + 1 * bpc,
                                               src + 1 * bpc + ph * stride, src + ph * stride, src + 1 * bpc + ph * stride};

            const uint8_t *coordinatesrb[] = { src + (width - 2) * bpc - nh * stride, src + (width - 1) * bpc - nh * stride, src + (width - 2) * bpc - nh * stride,
                                               src + (width - 2) * bpc,                                                      src + (width - 2) * bpc,
                                               src + (width - 2) * bpc + ph * stride, src + (width - 1) * bpc + ph * stride, src + (width - 2) * bpc + ph * stride};

            s->filter(dst,                         src,                     1,         threshold, coordinateslb, s->coordinates, s->max);
            if (width > 1) {
                s->filter(dst          + 1  * bpc, src          + 1  * bpc, width - 2, threshold, coordinates,   s->coordinates, s->max);
                s->filter(dst + (width - 1) * bpc, src + (width - 1) * bpc, 1,         threshold, coordinatesrb, s->coordinates, s->max);
            }

            src += stride;
            dst += dstride;
        }
    }

    return 0;
}

static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    NContext *s = ctx->priv;
    ThreadData td;
    AVFrame *out;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    td.in = in;
    td.out = out;
    ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(s->planeheight[1], ff_filter_get_nb_threads(ctx)));

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}
