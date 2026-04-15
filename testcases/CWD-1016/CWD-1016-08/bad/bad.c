#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define av_always_inline __attribute__((always_inline)) inline
#define av_unused __attribute__((unused))

#define LIBAVUTIL_VERSION_MAJOR 56
#define LIBAVUTIL_VERSION_MINOR 31
#define LIBAVUTIL_VERSION_MICRO 100

#define AV_VERSION_INT(a, b, c) ((a)<<16 | (b)<<8 | (c))
#define LIBAVUTIL_VERSION_INT AV_VERSION_INT(LIBAVUTIL_VERSION_MAJOR, LIBAVUTIL_VERSION_MINOR, LIBAVUTIL_VERSION_MICRO)

#define AV_HAVE_BIGENDIAN 0

typedef struct AVBPrint AVBPrint;

#define AV_ERROR_MAX_STRING_SIZE 64

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

#define AVERROR(e) (-(e))
#define ENOMEM 12
#define EINVAL 22

#define AV_LOG_ERROR   16
#define AV_LOG_DEBUG   48
#define AV_LOG_TRACE   56

void av_log(void *avcl, int level, const char *fmt, ...);

void *av_malloc(size_t size);
void *av_mallocz(size_t size);
void *av_malloc_array(size_t nmemb, size_t size);
void *av_mallocz_array(size_t nmemb, size_t size);
void av_free(void *ptr);
void av_freep(void *ptr);

#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#define RSHIFT(a,b) ((a) > 0 ? ((a) + ((1<<(b))>>1))>>(b) : ((a) + ((1<<(b))>>1)-1)>>(b))
#define AV_CEIL_RSHIFT(a,b) (((a) + (1<<(b)) - 1) >> (b))

static inline int av_clip_c(int a, int amin, int amax) {
    if (a < amin) return amin;
    else if (a > amax) return amax;
    else return a;
}
#define av_clip(a, amin, amax) av_clip_c(a, amin, amax)

static inline uint8_t av_clip_uint8_c(int a) {
    if (a & (~0xFF)) return (-a) >> 31;
    else return a;
}
#define av_clip_uint8 av_clip_uint8_c

#define av_builtin_constant_p(x) __builtin_constant_p(x)

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
    AV_PIX_FMT_ARGB,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_ABGR,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_GRAY16BE,
    AV_PIX_FMT_GRAY16LE,
    AV_PIX_FMT_YUV440P,
    AV_PIX_FMT_YUVJ440P,
    AV_PIX_FMT_YUVA420P,
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
    AV_PIX_FMT_GBRP,
    AV_PIX_FMT_GBRP9BE,
    AV_PIX_FMT_GBRP9LE,
    AV_PIX_FMT_GBRP10BE,
    AV_PIX_FMT_GBRP10LE,
    AV_PIX_FMT_GBRP16BE,
    AV_PIX_FMT_GBRP16LE,
    AV_PIX_FMT_YUVA422P,
    AV_PIX_FMT_YUVA444P,
    AV_PIX_FMT_YUVA420P16LE,
    AV_PIX_FMT_YUVA420P16BE,
    AV_PIX_FMT_YUVA422P16LE,
    AV_PIX_FMT_YUVA422P16BE,
    AV_PIX_FMT_YUVA444P16LE,
    AV_PIX_FMT_YUVA444P16BE,
    AV_PIX_FMT_NB
};

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
    uint8_t flags;
    AVComponentDescriptor comp[4];
} AVPixFmtDescriptor;

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);

typedef struct AVBuffer AVBuffer;
typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    size_t size;
} AVBufferRef;

typedef struct AVFrameSideData {
    int type;
    uint8_t *data;
    int size;
    void *metadata;
    AVBufferRef *buf;
} AVFrameSideData;

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
    int64_t pts;
    int64_t pkt_dts;
    int64_t pkt_pos;
    int pkt_duration;
    int pkt_size;
    int sample_rate;
    int channels;
    void *opaque;
    uint64_t channel_layout;
    AVBufferRef *buf[AV_NUM_DATA_POINTERS];
    AVBufferRef *extended_buf;
    int nb_extended_buf;
    AVFrameSideData **side_data;
    int nb_side_data;
    int flags;
    int color_range;
    int color_primaries;
    int color_trc;
    int colorspace;
    int chroma_location;
    int best_effort_timestamp;
    int64_t coded_picture_number;
    int64_t display_picture_number;
    int repeat_pict;
    int interlaced_frame;
    int top_field_first;
    int palette_has_changed;
    int sample_aspect_ratio;
} AVFrame;

int av_frame_is_writable(AVFrame *frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVDictionary AVDictionary;
typedef struct AVBufferRef AVBufferRef;
typedef struct AVFilter AVFilter;
typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink AVFilterLink;
typedef struct AVFilterPad AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterCommand AVFilterCommand;
typedef struct AVFilterInternal AVFilterInternal;

struct AVFilterContext {
    const void *av_class;
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
    AVFilterInternal *internal;
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
    AVFilterContext *dst;
    AVFilterPad *srcpad;
    AVFilterPad *dstpad;
    enum AVMediaType type;
    int w;
    int h;
    AVRational sample_aspect_ratio;
    int64_t channel_layout;
    int sample_rate;
    int format;
    AVRational time_base;
    AVFilterFormats *in_formats;
    AVFilterFormats *out_formats;
    int64_t current_pts;
    int64_t current_pts_us;
    int64_t last_pts;
    int64_t last_dts;
    unsigned int frame_count;
    int64_t frame_duration;
    void *av_log;
    int frame_wanted_out;
    int status;
    int64_t status_pts;
    unsigned long long ready;
};

#define AVFILTER_FLAG_DYNAMIC_INPUTS        (1 << 0)
#define AVFILTER_FLAG_DYNAMIC_OUTPUTS       (1 << 1)
#define AVFILTER_FLAG_SLICE_THREADS         (1 << 2)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC  (1 << 16)
#define AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL (1 << 17)
#define AVFILTER_FLAG_SUPPORT_TIMELINE (AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC | AVFILTER_FLAG_SUPPORT_TIMELINE_INTERNAL)

typedef struct AVFilterCommand {
    double time;
    char *command;
    char *arg;
    int flags;
    struct AVFilterCommand *next;
} AVFilterCommand;

struct AVFilterInternal {
    void (*execute)(AVFilterContext *ctx, int (*func)(AVFilterContext *ctx2, void *arg2, int jobnr, int nb_jobs), void *arg, void *ret, int nb_jobs);
};

int ff_filter_get_nb_threads(AVFilterContext *ctx);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);
int ff_filter_frame(AVFilterLink *link, AVFrame *frame);

typedef struct ColorConstancyContext {
    const void *class;
    int difford;
    int minknorm;
    double sigma;
    int nb_threads;
    int planeheight[4];
    int planewidth[4];
    int filtersize;
    double *gauss[3];
    double white[3];
} ColorConstancyContext;

#define NUM_PLANES    3
#define MAX_DIFF_ORD  2
#define MAX_META_DATA 4
#define MAX_DATA      4

#define INDEX_TEMP 0
#define INDEX_DX   1
#define INDEX_DY   2
#define INDEX_DXY  3
#define INDEX_NORM INDEX_DX
#define INDEX_SRC  0
#define INDEX_DST  1
#define INDEX_ORD  2
#define INDEX_DIR  3
#define DIR_X 0
#define DIR_Y 1

typedef struct ThreadData {
    AVFrame *in, *out;
    int meta_data[MAX_META_DATA];
    double  *data[MAX_DATA][NUM_PLANES];
} ThreadData;

#define GINDX(s, i) ( (i) - ((s) >> 2) )
#define CLAMP(x, mx) av_clip((x), 0, (mx-1))
#define INDX2D(r, c, w) ( (r) * (w) + (c) )
#define GAUSS(s, sr, sc, sls, sh, sw, g) ( (s)[ INDX2D(CLAMP((sr), (sh)), CLAMP((sc), (sw)), (sls)) ] * (g) )

static int setup_derivative_buffers(AVFilterContext* ctx, ThreadData *td);
static void cleanup_derivative_buffers(ThreadData *td, int nb_buff, int nb_planes);
static int slice_normalize(AVFilterContext* ctx, void* arg, int jobnr, int nb_jobs);
static int filter_slice_grey_edge(AVFilterContext* ctx, void* arg, int jobnr, int nb_jobs);
static void normalize_light(double *light);
static void chromatic_adaptation(AVFilterContext *ctx, AVFrame *in, AVFrame *out);

static int set_gauss(AVFilterContext *ctx)
{
    ColorConstancyContext *s = ctx->priv;
    int filtersize = s->filtersize;
    int difford    = s->difford;
    double sigma   = s->sigma;
    double sum1, sum2;
    int i;

    for (i = 0; i <= difford; ++i) {
        s->gauss[i] = av_mallocz_array(filtersize, sizeof(*s->gauss[i]));
        if (!s->gauss[i]) {
            for (; i >= 0; --i) {
                av_freep(&s->gauss[i]);
            }
            av_log(ctx, AV_LOG_ERROR, "Out of memory while allocating gauss buffers.\n");
            return AVERROR(ENOMEM);
        }
    }

    // Order 0
    av_log(ctx, AV_LOG_TRACE, "Setting 0-d gauss with filtersize = %d.\n", filtersize);
    sum1 = 0.0;
    if (!sigma) {
        s->gauss[0][0] = 1; // Copying data to double instead of convolution
    } else {
        for (i = 0; i < filtersize; ++i) {
            s->gauss[0][i] = exp(- pow(GINDX(filtersize, i), 2.) / (2 * sigma * sigma)) / ( sqrt(2 * M_PI) * sigma );
            sum1 += s->gauss[0][i];
        }
        for (i = 0; i < filtersize; ++i) {
            s->gauss[0][i] /= sum1;
        }
    }
    // Order 1
    if (difford > 0) {
        av_log(ctx, AV_LOG_TRACE, "Setting 1-d gauss with filtersize = %d.\n", filtersize);
        sum1 = 0.0;
        for (i = 0; i < filtersize; ++i) {
            s->gauss[1][i] = - (GINDX(filtersize, i) / pow(sigma, 2)) * s->gauss[0][i];
            sum1 += s->gauss[1][i] * GINDX(filtersize, i);
        }

        for (i = 0; i < filtersize; ++i) {
            s->gauss[1][i] /= sum1;
        }

        // Order 2
        if (difford > 1) {
            av_log(ctx, AV_LOG_TRACE, "Setting 2-d gauss with filtersize = %d.\n", filtersize);
            sum1 = 0.0;
            for (i = 0; i < filtersize; ++i) {
                s->gauss[2][i] = ( pow(GINDX(filtersize, i), 2) / pow(sigma, 4) - 1/pow(sigma, 2) )
                                 * s->gauss[0][i];
                sum1 += s->gauss[2][i];
            }

            sum2 = 0.0;
            for (i = 0; i < filtersize; ++i) {
                s->gauss[2][i] -= sum1 / (filtersize);
                sum2 += (0.5 * GINDX(filtersize, i) * GINDX(filtersize, i) * s->gauss[2][i]);
            }
            for (i = 0; i < filtersize ; ++i) {
                s->gauss[2][i] /= sum2;
            }
        }
    }
    return 0;
}

static int config_props(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ColorConstancyContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const double break_off_sigma = 3.0;
    double sigma = s->sigma;
    int ret;

    if (!floor(break_off_sigma * sigma + 0.5) && s->difford) {
        av_log(ctx, AV_LOG_ERROR, "floor(%f * sigma) must be > 0 when difford > 0.\n", break_off_sigma);
        return AVERROR(EINVAL);
    }

    s->filtersize = 2 * floor(break_off_sigma * sigma + 0.5) + 1;
    if (ret=set_gauss(ctx)) {
        return ret;
    }

    s->nb_threads = ff_filter_get_nb_threads(ctx);
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;
    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    return 0;
}

static int slice_get_derivative(AVFilterContext* ctx, void* arg, int jobnr, int nb_jobs)
{
    ColorConstancyContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    const int ord = td->meta_data[INDEX_ORD];
    const int dir = td->meta_data[INDEX_DIR];
    const int src_index  = td->meta_data[INDEX_SRC];
    const int dst_index  = td->meta_data[INDEX_DST];
    const int filtersize = s->filtersize;
    const double *gauss  = s->gauss[ord];
    int plane;

    for (plane = 0; plane < NUM_PLANES; ++plane) {
        const int height      = s->planeheight[plane];
        const int width       = s->planewidth[plane];
        const int in_linesize = in->linesize[plane];
        double *dst = td->data[dst_index][plane];
        int slice_start, slice_end;
        int r, c, g;

        if (dir == DIR_X) {
            /** Applying gauss horizontally along each row */
            const uint8_t *src = in->data[plane];
            slice_start = (height * jobnr      ) / nb_jobs;
            slice_end   = (height * (jobnr + 1)) / nb_jobs;

            for (r = slice_start; r < slice_end; ++r) {
                for (c = 0; c < width; ++c) {
                    dst[INDX2D(r, c, width)] = 0;
                    for (g = 0; g < filtersize; ++g) {
                        dst[INDX2D(r, c, width)] += GAUSS(src, r,                        c + GINDX(filtersize, g),
                                                          in_linesize, height, width, gauss[GINDX(filtersize, g)]);
                    }
                }
            }
        } else {
            /** Applying gauss vertically along each column */
            const double *src = td->data[src_index][plane];
            slice_start = (width * jobnr      ) / nb_jobs;
            slice_end   = (width * (jobnr + 1)) / nb_jobs;

            for (c = slice_start; c < slice_end; ++c) {
                for (r = 0; r < height; ++r) {
                    dst[INDX2D(r, c, width)] = 0;
                    for (g = 0; g < filtersize; ++g) {
                        dst[INDX2D(r, c, width)] += GAUSS(src, r + GINDX(filtersize, g), c,
                                                          width, height, width, gauss[GINDX(filtersize, g)]);
                    }
                }
            }
        }

    }
    return 0;
}

static void av_always_inline
get_deriv(AVFilterContext *ctx, ThreadData *td, int ord, int dir,
          int src, int dst, int dim, int nb_threads) {
    td->meta_data[INDEX_ORD] = ord;
    td->meta_data[INDEX_DIR] = dir;
    td->meta_data[INDEX_SRC] = src;
    td->meta_data[INDEX_DST] = dst;
    ctx->internal->execute(ctx, slice_get_derivative, td, NULL, FFMIN(dim, nb_threads));
}

static int get_derivative(AVFilterContext *ctx, ThreadData *td)
{
    ColorConstancyContext *s = ctx->priv;
    int nb_threads = s->nb_threads;
    int height = s->planeheight[1];
    int width  = s->planewidth[1];

    switch(s->difford) {
    case 0:
        if (!s->sigma) { // Only copy once
            get_deriv(ctx, td, 0, DIR_X, 0         , INDEX_NORM, height, nb_threads);
        } else {
            get_deriv(ctx, td, 0, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
            get_deriv(ctx, td, 0, DIR_Y, INDEX_TEMP, INDEX_NORM, width , nb_threads);
            // save to INDEX_NORM because this will not be normalied and
            // end gry edge filter expects result to be found in INDEX_NORM
        }
        return 0;

    case 1:
        get_deriv(ctx, td, 1, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
        get_deriv(ctx, td, 0, DIR_Y, INDEX_TEMP, INDEX_DX,   width , nb_threads);

        get_deriv(ctx, td, 0, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
        get_deriv(ctx, td, 1, DIR_Y, INDEX_TEMP, INDEX_DY,   width , nb_threads);
        return 0;

    case 2:
        get_deriv(ctx, td, 2, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
        get_deriv(ctx, td, 0, DIR_Y, INDEX_TEMP, INDEX_DX,   width , nb_threads);

        get_deriv(ctx, td, 0, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
        get_deriv(ctx, td, 2, DIR_Y, INDEX_TEMP, INDEX_DY,   width , nb_threads);

        get_deriv(ctx, td, 1, DIR_X, 0,          INDEX_TEMP, height, nb_threads);
        get_deriv(ctx, td, 1, DIR_Y, INDEX_TEMP, INDEX_DXY,  width , nb_threads);
        return 0;

    default:
        av_log(ctx, AV_LOG_ERROR, "Unsupported difford value: %d.\n", s->difford);
        return AVERROR(EINVAL);
    }

}

static int filter_grey_edge(AVFilterContext *ctx, AVFrame *in)
{
    ColorConstancyContext *s = ctx->priv;
    ThreadData td;
    int minknorm  = s->minknorm;
    int difford   = s->difford;
    double *white = s->white;
    int nb_jobs   = FFMIN3(s->planeheight[1], s->planewidth[1], s->nb_threads);
    int plane, job, ret;

    td.in = in;
    ret = setup_derivative_buffers(ctx, &td);
    if (ret) {
        return ret;
    }
    get_derivative(ctx, &td);
    if (difford > 0) {
        ctx->internal->execute(ctx, slice_normalize, &td, NULL, nb_jobs);
    }

    ctx->internal->execute(ctx, filter_slice_grey_edge, &td, NULL, nb_jobs);
    if (!minknorm) {
        for (plane = 0; plane < NUM_PLANES; ++plane) {
            white[plane] = 0; // All values are absolute
            for (job = 0; job < nb_jobs; ++job) {
                white[plane] = FFMAX(white[plane] , td.data[INDEX_DST][plane][job]);
            }
        }
    } else {
        for (plane = 0; plane < NUM_PLANES; ++plane) {
            white[plane] = 0;
            for (job = 0; job < nb_jobs; ++job) {
                white[plane] += td.data[INDEX_DST][plane][job];
            }
            white[plane] = pow(white[plane], 1./minknorm);
        }
    }

    cleanup_derivative_buffers(&td, difford + 1, NUM_PLANES);
    return 0;
}

static int illumination_estimation(AVFilterContext *ctx, AVFrame *in)
{
    ColorConstancyContext *s = ctx->priv;
    int ret;

    ret = filter_grey_edge(ctx, in);

    av_log(ctx, AV_LOG_DEBUG, "Estimated illumination= %f %f %f\n",
           s->white[0], s->white[1], s->white[2]);
    normalize_light(s->white);
    av_log(ctx, AV_LOG_DEBUG, "Estimated illumination after normalization= %f %f %f\n",
           s->white[0], s->white[1], s->white[2]);

    return ret;
}

static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int ret;

    ret = illumination_estimation(ctx, in);
    if (ret) {
        return ret;
    }

    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_log(ctx, AV_LOG_ERROR, "Out of memory while allocating output video buffer.\n");
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }
    chromatic_adaptation(ctx, in, out);

    return ff_filter_frame(outlink, out);
}
