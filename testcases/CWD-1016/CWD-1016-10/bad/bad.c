#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
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

typedef struct AVRational {
    int num;
    int den;
} AVRational;

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_YUV422P,
    AV_PIX_FMT_YUV444P,
    AV_PIX_FMT_GBRP,
    AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_NB
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1,
    AVCOL_RANGE_JPEG        = 2,
    AVCOL_RANGE_NB
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
    AVCOL_PRI_SMPTE431    = 11,
    AVCOL_PRI_SMPTE432    = 12,
    AVCOL_PRI_EBU3213     = 22,
    AVCOL_PRI_NB
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
    AVCOL_TRC_SMPTE428     = 17,
    AVCOL_TRC_ARIB_STD_B67 = 18,
    AVCOL_TRC_NB
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
    AVCOL_SPC_BT2020_NCL  = 9,
    AVCOL_SPC_BT2020_CL   = 10,
    AVCOL_SPC_SMPTE2085   = 11,
    AVCOL_SPC_CHROMA_DERIVED_NCL = 12,
    AVCOL_SPC_CHROMA_DERIVED_CL = 13,
    AVCOL_SPC_ICTCP       = 14,
    AVCOL_SPC_NB
};

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1,
    AVCHROMA_LOC_CENTER      = 2,
    AVCHROMA_LOC_TOPLEFT     = 3,
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_BOTTOM      = 6,
    AVCHROMA_LOC_NB
};

#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#endif

#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

#define av_always_inline __attribute__((always_inline)) inline
#define av_const __attribute__((const))
#define av_builtin_constant_p __builtin_constant_p
#define av_clip_uint8 av_clip_uint8_c

static av_always_inline av_const uint8_t av_clip_uint8_c(int a)
{
    if (a&(~0xFF)) return (~a)>>31;
    else           return a;
}

#define AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                         : ((a) + (1<<(b)) - 1) >> (b))

#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

#define AV_LOG_QUIET -8
#define AV_LOG_PANIC 0
#define AV_LOG_FATAL 8
#define AV_LOG_ERROR 16
#define AV_LOG_WARNING 24
#define AV_LOG_INFO 32
#define AV_LOG_VERBOSE 40
#define AV_LOG_DEBUG 48

const char* av_default_item_name(void* ctx);

#define AV_OPT_FLAG_FILTERING_PARAM (1 << 0)
#define AV_OPT_FLAG_VIDEO_PARAM     (1 << 1)

enum AVOptionType {
    AV_OPT_TYPE_FLAGS,
    AV_OPT_TYPE_INT,
    AV_OPT_TYPE_INT64,
    AV_OPT_TYPE_DOUBLE,
    AV_OPT_TYPE_FLOAT,
    AV_OPT_TYPE_STRING,
    AV_OPT_TYPE_RATIONAL,
    AV_OPT_TYPE_BINARY,
    AV_OPT_TYPE_DICT,
};

typedef struct AVOption {
    const char *name;
    const char *help;
    enum AVOptionType type;
    int offset;
    double default_val;
    double min;
    double max;
    int flags;
    const char *unit;
} AVOption;

#define OFFSET(x) offsetof(EdgeDetectContext, x)
#define FLAGS AV_OPT_FLAG_FILTERING_PARAM|AV_OPT_FLAG_VIDEO_PARAM

typedef struct AVBufferRef {
    uint8_t *data;
    size_t   size;
    void *opaque;
    void (*free)(void *opaque, uint8_t *data);
} AVBufferRef;

typedef struct AVDictionary {
    int count;
    void *elems;
} AVDictionary;

#define AV_NUM_DATA_POINTERS 8

typedef struct AVFrameSideData {
    int type;
    uint8_t *data;
    int      size;
    AVDictionary *metadata;
    AVBufferRef *buf;
} AVFrameSideData;

#define AV_FRAME_FLAG_CORRUPT     (1 << 0)
#define AV_FRAME_FLAG_DISCARD     (1 << 2)

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

int av_frame_is_writable(AVFrame *frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
void av_frame_free(AVFrame **frame);

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterCommand AVFilterCommand;

typedef struct AVClass {
    const char *class_name;
    const char *(*item_name)(void *);
    const struct AVOption *option;
    int version;
    int category;
} AVClass;

#define AVFILTER_FLAG_DYNAMIC_INPUTS        (1 << 0)
#define AVFILTER_FLAG_DYNAMIC_OUTPUTS       (1 << 1)
#define AVFILTER_FLAG_SLICE_THREADS         (1 << 2)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC  (1 << 16)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL (1 << 17)
#define AVFILTER_FLAG_SUPPORT_TIMELINE (AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC | AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL)

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
    void *internal;
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

struct AVFilterPad {
    const char *name;
    enum AVMediaType type;
    AVFrame*(*get_video_buffer)(AVFilterLink *link, int w, int h);
    AVFrame*(*get_audio_buffer)(AVFilterLink *link, int nb_samples);
    int (*filter_frame)(AVFilterLink *link, AVFrame *frame);
    int (*poll_frame)(AVFilterLink *link);
    int (*request_frame)(AVFilterLink *link);
    int (*config_props)(AVFilterLink *link);
    int needs_fifo;
    int needs_writable;
};

#define AVFILTER_DEFINE_CLASS(fname)            \
    static const AVClass fname##_class = {      \
        .class_name = #fname,                   \
        .item_name  = av_default_item_name,     \
        .option     = fname##_options,          \
        .version    = 0,                        \
        .category   = 0,                        \
    }

AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);
void av_image_copy_plane(uint8_t       *dst, int dst_linesize,
                         const uint8_t *src, int src_linesize,
                         int bytewidth, int height);

#define PLANE_R 0x4
#define PLANE_G 0x1
#define PLANE_B 0x2
#define PLANE_Y 0x1
#define PLANE_U 0x2
#define PLANE_V 0x4
#define PLANE_A 0x8

enum FilterMode {
    MODE_WIRES,
    MODE_COLORMIX,
    MODE_CANNY,
    NB_MODE
};

struct plane_info {
    uint8_t  *tmpbuf;
    uint16_t *gradients;
    char     *directions;
    int      width, height;
};

typedef struct EdgeDetectContext {
    const AVClass *class;
    struct plane_info planes[3];
    int filter_planes;
    int nb_planes;
    double   low, high;
    uint8_t  low_u8, high_u8;
    int mode;
} EdgeDetectContext;

static void gaussian_blur(AVFilterContext *ctx, int w, int h,
                                uint8_t *dst, int dst_linesize,
                          const uint8_t *src, int src_linesize);
static void sobel(int w, int h,
                       uint16_t *dst, int dst_linesize,
                         char *dir, int dir_linesize,
                  const uint8_t *src, int src_linesize);
static void non_maximum_suppression(int w, int h,
                                          uint8_t  *dst, int dst_linesize,
                                    const  char   *dir, int dir_linesize,
                                    const uint16_t *src, int src_linesize);
static void double_threshold(int low, int high, int w, int h,
                                   uint8_t *dst, int dst_linesize,
                             const uint8_t *src, int src_linesize);
static void color_mix(int w, int h,
                            uint8_t *dst, int dst_linesize,
                      const uint8_t *src, int src_linesize);
static int filter_frame(AVFilterLink *inlink, AVFrame *in);

static void gaussian_blur(AVFilterContext *ctx, int w, int h,
                                uint8_t *dst, int dst_linesize,
                          const uint8_t *src, int src_linesize)
{
    int i, j;

    memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    for (j = 2; j < h - 2; j++) {
        dst[0] = src[0];
        dst[1] = src[1];
        for (i = 2; i < w - 2; i++) {
            /* Gaussian mask of size 5x5 with sigma = 1.4 */
            dst[i] = ((src[-2*src_linesize + i-2] + src[2*src_linesize + i-2]) * 2
                    + (src[-2*src_linesize + i-1] + src[2*src_linesize + i-1]) * 4
                    + (src[-2*src_linesize + i  ] + src[2*src_linesize + i  ]) * 5
                    + (src[-2*src_linesize + i+1] + src[2*src_linesize + i+1]) * 4
                    + (src[-2*src_linesize + i+2] + src[2*src_linesize + i+2]) * 2

                    + (src[  -src_linesize + i-2] + src[  src_linesize + i-2]) *  4
                    + (src[  -src_linesize + i-1] + src[  src_linesize + i-1]) *  9
                    + (src[  -src_linesize + i  ] + src[  src_linesize + i  ]) * 12
                    + (src[  -src_linesize + i+1] + src[  src_linesize + i+1]) *  9
                    + (src[  -src_linesize + i+2] + src[  src_linesize + i+2]) *  4

                    + src[i-2] *  5
                    + src[i-1] * 12
                    + src[i  ] * 15
                    + src[i+1] * 12
                    + src[i+2] *  5) / 159;
        }
        dst[i    ] = src[i    ];
        dst[i + 1] = src[i + 1];

        dst += dst_linesize;
        src += src_linesize;
    }
    memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    memcpy(dst, src, w);
}

static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    EdgeDetectContext *edgedetect = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int p, direct = 0;
    AVFrame *out;

    if (edgedetect->mode != MODE_COLORMIX && av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    for (p = 0; p < edgedetect->nb_planes; p++) {
        struct plane_info *plane = &edgedetect->planes[p];
        uint8_t  *tmpbuf     = plane->tmpbuf;
        uint16_t *gradients  = plane->gradients;
        char     *directions = plane->directions;
        const int width      = plane->width;
        const int height     = plane->height;

        if (!((1 << p) & edgedetect->filter_planes)) {
            if (!direct)
                av_image_copy_plane(out->data[p], out->linesize[p],
                                    in->data[p], in->linesize[p],
                                    width, height);
            continue;
        }

        /* gaussian filter to reduce noise  */
        gaussian_blur(ctx, width, height,
                      tmpbuf,      width,
                      in->data[p], in->linesize[p]);

        /* compute the 16-bits gradients and directions for the next step */
        sobel(width, height,
              gradients, width,
              directions,width,
              tmpbuf,    width);

        /* non_maximum_suppression() will actually keep & clip what's necessary and
         * ignore the rest, so we need a clean output buffer */
        memset(tmpbuf, 0, width * height);
        non_maximum_suppression(width, height,
                                tmpbuf,    width,
                                directions,width,
                                gradients, width);

        /* keep high values, or low values surrounded by high values */
        double_threshold(edgedetect->low_u8, edgedetect->high_u8,
                         width, height,
                         out->data[p], out->linesize[p],
                         tmpbuf,       width);

        if (edgedetect->mode == MODE_COLORMIX) {
            color_mix(width, height,
                      out->data[p], out->linesize[p],
                      in->data[p], in->linesize[p]);
        }
    }

    if (!direct)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}
