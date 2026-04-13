#include <stddef.h>
#include <stdint.h>

#define LIBAVUTIL_VERSION_INT 0x371c0d
#define LIBAVFILTER_VERSION_INT 0x082c64

#if defined(__GNUC__) || defined(__clang__)
    #define av_cold __attribute__((cold))
    #define av_alloc_size(...) __attribute__((alloc_size(__VA_ARGS__)))
    #define av_printf_format(fmtp, firstp) __attribute__((format(__printf__, fmtp, firstp)))
#else
    #define av_cold
    #define av_alloc_size(...)
    #define av_printf_format(fmtp, firstp)
#endif

#define av_default_item_name NULL

#define AVERROR(e) (-(e))
#define ENOMEM 12
#define EINVAL 22
#define EAGAIN 11

#define AV_OPT_TYPE_IMAGE_SIZE 1
#define AV_OPT_TYPE_INT 2
#define AV_OPT_TYPE_COLOR 3
#define AV_OPT_FLAG_VIDEO_PARAM 1
#define AV_OPT_FLAG_FILTERING_PARAM 2
#define OFFSET(x) offsetof(TileContext, x)
#define FLAGS (AV_OPT_FLAG_VIDEO_PARAM|AV_OPT_FLAG_FILTERING_PARAM)

#define AV_LOG_ERROR 16
#define AV_CLASS_CATEGORY_FILTER 56

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
};

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
};

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVClass {
    const char *class_name;
    const char *(*item_name)(void *ctx);
    const void *option;
    int version;
    int category;
} AVClass;

typedef struct AVOption {
    const char *name;
    const char *help;
    int offset;
    int type;
    union {
        int64_t i64;
        double dbl;
        const char *str;
    } default_val;
    int min;
    int max;
    int flags;
} AVOption;

typedef struct AVFrame {
    uint8_t *data[8];
    int linesize[8];
    int width, height;
    int format;
    int64_t pts;
} AVFrame;

typedef struct AVFilterContext {
    const AVClass *av_class;
    const struct AVFilter *filter;
    void *priv;
    struct AVFilterPad *input_pads;
    struct AVFilterLink **inputs;
    unsigned nb_inputs;
    struct AVFilterPad *output_pads;
    struct AVFilterLink **outputs;
    unsigned nb_outputs;
} AVFilterContext;

typedef struct AVFilterLink {
    struct AVFilterContext *src;
    struct AVFilterContext *dst;
    struct AVFilterPad *srcpad;
    struct AVFilterPad *dstpad;
    int w;
    int h;
    enum AVPixelFormat format;
    AVRational sample_aspect_ratio;
    AVRational frame_rate;
} AVFilterLink;

typedef struct AVFilterPad {
    const char *name;
    enum AVMediaType type;
    int (*filter_frame)(struct AVFilterLink *link, struct AVFrame *frame);
    int (*config_props)(struct AVFilterLink *link);
    int (*request_frame)(struct AVFilterLink *link);
} AVFilterPad;

typedef struct AVFilter {
    const char *name;
    const char *description;
    const AVFilterPad *inputs;
    const AVFilterPad *outputs;
    const AVClass *priv_class;
    int flags;
    int (*init)(AVFilterContext *ctx);
    void (*uninit)(AVFilterContext *ctx);
    int (*query_formats)(AVFilterContext *);
    int priv_size;
} AVFilter;

#define MAX_PLANES 4

typedef struct AVPixFmtDescriptor {
    const char *name;
    uint8_t nb_components;
    uint8_t log2_chroma_w;
    uint8_t log2_chroma_h;
} AVPixFmtDescriptor;

typedef struct FFDrawContext {
    const AVPixFmtDescriptor *desc;
    enum AVPixelFormat format;
    unsigned nb_planes;
    int pixelstep[MAX_PLANES];
    uint8_t comp_mask[MAX_PLANES];
    uint8_t hsub[MAX_PLANES];
    uint8_t vsub[MAX_PLANES];
    uint8_t hsub_max;
    uint8_t vsub_max;
    int full_range;
    unsigned flags;
} FFDrawContext;

typedef struct FFDrawColor {
    uint8_t rgba[4];
    union {
        uint32_t u32[4];
        uint16_t u16[8];
        uint8_t  u8[16];
    } comp[MAX_PLANES];
} FFDrawColor;

typedef struct TileContext {
    const AVClass *class;
    unsigned w, h;
    unsigned margin;
    unsigned padding;
    unsigned overlap;
    unsigned init_padding;
    unsigned current;
    unsigned nb_frames;
    FFDrawContext draw;
    FFDrawColor blank;
    AVFrame *out_ref;
    AVFrame *prev_out_ref;
    uint8_t rgba_color[4];
} TileContext;

#define NULL_IF_CONFIG_SMALL(s) s
#define AVFILTER_DEFINE_CLASS(fname)            \
    static const AVClass fname##_class = {      \
        .class_name = #fname,                   \
        .item_name  = av_default_item_name,     \
        .option     = fname##_options,          \
        .version    = LIBAVUTIL_VERSION_INT,    \
        .category   = AV_CLASS_CATEGORY_FILTER, \
    }

void av_frame_free(AVFrame **frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
AVFrame *av_frame_clone(const AVFrame *frame);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
void ff_fill_rectangle(FFDrawContext *draw, FFDrawColor *color,
                       uint8_t *dst[], int dst_linesize[],
                       int dst_x, int dst_y, int w, int h);
void ff_copy_rectangle2(FFDrawContext *draw,
                        uint8_t *dst[], int dst_linesize[],
                        uint8_t *src[], int src_linesize[],
                        int dst_x, int dst_y, int src_x, int src_y,
                        int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);
int ff_request_frame(AVFilterLink *link);
int av_log(void *avcl, int level, const char *fmt, ...);

static const AVOption tile_options[] = {
    { "layout", "set grid size", OFFSET(w), AV_OPT_TYPE_IMAGE_SIZE,
        {.str = "6x5"}, 0, 0, FLAGS },
    { "nb_frames", "set maximum number of frame to render", OFFSET(nb_frames),
        AV_OPT_TYPE_INT, {.i64 = 0}, 0, 0x7fffffff, FLAGS },
    { "margin",  "set outer border margin in pixels",    OFFSET(margin),
        AV_OPT_TYPE_INT, {.i64 = 0}, 0, 1024, FLAGS },
    { "padding", "set inner border thickness in pixels", OFFSET(padding),
        AV_OPT_TYPE_INT, {.i64 = 0}, 0, 1024, FLAGS },
    { "color",   "set the color of the unused area", OFFSET(rgba_color), AV_OPT_TYPE_COLOR, {.str = "black"}, .flags = FLAGS },
    { "overlap", "set how many frames to overlap for each render", OFFSET(overlap),
        AV_OPT_TYPE_INT, {.i64 = 0}, 0, 0x7fffffff, FLAGS },
    { "init_padding", " set how many frames to initially pad", OFFSET(init_padding),
        AV_OPT_TYPE_INT, {.i64 = 0}, 0, 0x7fffffff, FLAGS },
    { NULL }
};

AVFILTER_DEFINE_CLASS(tile);

static int end_last_frame(AVFilterContext *ctx);
static void get_tile_pos(AVFilterContext *ctx, unsigned *x, unsigned *y, unsigned current);

static int filter_frame(AVFilterLink *inlink, AVFrame *picref)
{
    AVFilterContext *ctx  = inlink->dst;
    TileContext *tile     = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    unsigned x0, y0;

    if (!tile->out_ref) {
        tile->out_ref = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!tile->out_ref) {
            av_frame_free(&picref);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(tile->out_ref, picref);
        tile->out_ref->width  = outlink->w;
        tile->out_ref->height = outlink->h;

        /* fill surface once for margin/padding */
        if (tile->margin || tile->padding || tile->init_padding)
            ff_fill_rectangle(&tile->draw, &tile->blank,
                              tile->out_ref->data,
                              tile->out_ref->linesize,
                              0, 0, outlink->w, outlink->h);
        tile->init_padding = 0;
    }

    if (tile->prev_out_ref) {
        unsigned x1, y1, i;

        for (i = tile->nb_frames - tile->overlap; i < tile->nb_frames; i++) {
            get_tile_pos(ctx, &x1, &y1, i);
            get_tile_pos(ctx, &x0, &y0, i - (tile->nb_frames - tile->overlap));
            ff_copy_rectangle2(&tile->draw,
                               tile->out_ref->data, tile->out_ref->linesize,
                               tile->prev_out_ref->data, tile->prev_out_ref->linesize,
                               x0, y0, x1, y1, inlink->w, inlink->h);

        }
    }

    get_tile_pos(ctx, &x0, &y0, tile->current);
    ff_copy_rectangle2(&tile->draw,
                       tile->out_ref->data, tile->out_ref->linesize,
                       picref->data, picref->linesize,
                       x0, y0, 0, 0, inlink->w, inlink->h);

    av_frame_free(&picref);
    if (++tile->current == tile->nb_frames)
        return end_last_frame(ctx);

    return 0;
}

static av_cold void uninit(AVFilterContext *ctx)
{
    TileContext *tile = ctx->priv;

    av_frame_free(&tile->prev_out_ref);
}
