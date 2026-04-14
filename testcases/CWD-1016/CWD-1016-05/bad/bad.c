#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#if defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#else
#    define av_builtin_constant_p(x) 0
#endif

#define AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))

#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
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
    AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_MONOWHITE,
    AV_PIX_FMT_MONOBLACK,
    AV_PIX_FMT_PAL8,
};

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
    const void *class;
    struct plane_info planes[3];
    int filter_planes;
    int nb_planes;
    double   low, high;
    uint8_t  low_u8, high_u8;
    int mode;
} EdgeDetectContext;

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
} AVPixFmtDescriptor;

typedef struct AVClass AVClass;
typedef struct AVFilter AVFilter;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterInternal AVFilterInternal;

#define AV_NUM_DATA_POINTERS 8
typedef struct AVFrame {
    uint8_t *data[AV_NUM_DATA_POINTERS];
    int linesize[AV_NUM_DATA_POINTERS];
    uint8_t **extended_data;
    int width, height;
    int nb_samples;
    int format;
} AVFrame;

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink AVFilterLink;
typedef struct AVFilterPad AVFilterPad;

struct AVFilterContext {
    const AVClass *av_class;
    const AVFilter *filter;
    char *name;
    void *input_pads;
    AVFilterLink **inputs;
    unsigned    nb_inputs;
    void *output_pads;
    AVFilterLink **outputs;
    unsigned    nb_outputs;
    void *priv;
    struct AVFilterGraph *graph;
    int thread_type;
    AVFilterInternal *internal;
};

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

struct AVFilterLink {
    AVFilterContext *src;
    AVFilterPad *srcpad;
    AVFilterContext *dst;
    AVFilterPad *dstpad;
    enum AVMediaType type;
    int w;
    int h;
    int sample_aspect_ratio_num;
    int sample_aspect_ratio_den;
    uint64_t channel_layout;
    int sample_rate;
    int format;
    int time_base_num;
    int time_base_den;
    AVFilterFormats *in_formats;
    AVFilterFormats *out_formats;
    AVFilterFormats  *in_samplerates;
    AVFilterFormats *out_samplerates;
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
};

const AVPixFmtDescriptor *av_pix_fmt_desc_get(int pix_fmt);
void *av_malloc(size_t size);
void *av_calloc(size_t nmemb, size_t size);
int av_frame_is_writable(AVFrame *frame);
void av_frame_free(AVFrame **frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
void av_image_copy_plane(uint8_t *dst, int dst_linesize, const uint8_t *src, int src_linesize, int width, int height);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);

static void sobel(int w, int h, uint16_t *dst, int dst_linesize, int8_t *dir, int dir_linesize, const uint8_t *src, int src_linesize);
static void non_maximum_suppression(int w, int h, uint8_t *dst, int dst_linesize, const int8_t *dir, int dir_linesize, const uint16_t *src, int src_linesize);
static void double_threshold(int low, int high, int w, int h, uint8_t *dst, int dst_linesize, const uint8_t *src, int src_linesize);
static void color_mix(int w, int h, uint8_t *dst, int dst_linesize, const uint8_t *src, int src_linesize);

static int config_props(AVFilterLink *inlink)
{
    int p;
    AVFilterContext *ctx = inlink->dst;
    EdgeDetectContext *edgedetect = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    edgedetect->nb_planes = inlink->format == AV_PIX_FMT_GRAY8 ? 1 : 3;
    for (p = 0; p < edgedetect->nb_planes; p++) {
        struct plane_info *plane = &edgedetect->planes[p];
        int vsub = p ? desc->log2_chroma_h : 0;
        int hsub = p ? desc->log2_chroma_w : 0;

        plane->width      = AV_CEIL_RSHIFT(inlink->w, hsub);
        plane->height     = AV_CEIL_RSHIFT(inlink->h, vsub);
        plane->tmpbuf     = av_malloc(plane->width * plane->height);
        plane->gradients  = av_calloc(plane->width * plane->height, sizeof(*plane->gradients));
        plane->directions = av_malloc(plane->width * plane->height);
        if (!plane->tmpbuf || !plane->gradients || !plane->directions)
            return AVERROR(ENOMEM);
    }
    return 0;
}

static void gaussian_blur(AVFilterContext *ctx, int w, int h,
                                uint8_t *dst, int dst_linesize,
                          const uint8_t *src, int src_linesize)
{
    int i, j;

    memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    if (h > 1) {
        memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    }
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
    if (h > 2) {
        memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    }
    if (h > 3)
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
        int8_t   *directions = plane->directions;
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

static const AVFilterPad edgedetect_inputs[] = {
    {
        .name         = "default",
        .type         = AVMEDIA_TYPE_VIDEO,
        .config_props = config_props,
        .filter_frame = filter_frame,
    },
    { NULL }
};
