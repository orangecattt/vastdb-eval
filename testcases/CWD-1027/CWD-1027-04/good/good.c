#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>

#define av_always_inline __attribute__((always_inline)) inline
#define av_noinline __attribute__((noinline))
#define av_const __attribute__((const))
#define av_unused __attribute__((unused))
#define av_likely(x) __builtin_expect(!!(x), 1)
#define av_unlikely(x) __builtin_expect(!!(x), 0)
#define av_builtin_constant_p __builtin_constant_p

#define attribute_deprecated __attribute__((deprecated))

#define LIBAVUTIL_VERSION_MAJOR  58
#define LIBAVUTIL_VERSION_MINOR  29
#define LIBAVUTIL_VERSION_MICRO 100

#define AV_VERSION_INT(a, b, c) ((a)<<16 | (b)<<8 | (c))
#define AV_VERSION(a, b, c) #a "." #b "." #c

#define FF_API_FRAME_GET_SET (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_API_FRAME_QP (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_API_ERROR_FRAME (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_API_PKT_PTS (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_API_LAVR_OPTS (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_API_NEXT (LIBAVUTIL_VERSION_INT < AV_VERSION_INT(59, 0, 100))
#define FF_INTERNAL_FIELDS 0

#define AV_STRINGIFY(s)         AV_TOSTRING(s)
#define AV_TOSTRING(s) #s
#define FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

enum AVColorPrimaries {
    AVCOL_PRI_UNSPECIFIED    = 0,
    AVCOL_PRI_BT709          = 1,
    AVCOL_PRI_BT470M         = 4,
    AVCOL_PRI_BT470BG        = 5,
    AVCOL_PRI_SMPTE170M      = 6,
    AVCOL_PRI_SMPTE240M      = 7,
    AVCOL_PRI_BT2020         = 9,
    AVCOL_PRI_NB
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_UNSPECIFIED    = 0,
    AVCOL_TRC_BT709          = 1,
    AVCOL_TRC_GAMMA22        = 4,
    AVCOL_TRC_GAMMA28        = 5,
    AVCOL_TRC_SMPTE170M      = 6,
    AVCOL_TRC_SMPTE240M      = 7,
    AVCOL_TRC_BT2020_10      = 14,
    AVCOL_TRC_BT2020_12      = 15,
    AVCOL_TRC_NB
};

enum AVColorSpace {
    AVCOL_SPC_RGB            = 0,
    AVCOL_SPC_BT709          = 1,
    AVCOL_SPC_UNSPECIFIED    = 2,
    AVCOL_SPC_BT470BG        = 5,
    AVCOL_SPC_SMPTE170M      = 6,
    AVCOL_SPC_SMPTE240M      = 7,
    AVCOL_SPC_BT2020_NCL     = 9,
    AVCOL_SPC_BT2020_CL      = 10,
    AVCOL_SPC_NB
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED  = 0,
    AVCOL_RANGE_MPEG         = 1,
    AVCOL_RANGE_JPEG         = 2,
    AVCOL_RANGE_NB
};

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
    AV_PIX_FMT_NB
};

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
    AV_SAMPLE_FMT_NB
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

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT,
    AVCHROMA_LOC_CENTER,
    AVCHROMA_LOC_TOPLEFT,
    AVCHROMA_LOC_TOP,
    AVCHROMA_LOC_BOTTOMLEFT,
    AVCHROMA_LOC_BOTTOM,
    AVCHROMA_LOC_NB
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
    AV_FRAME_DATA_SKIP_SAMPLES,
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

#define AV_NUM_DATA_POINTERS 8

const char *av_color_space_name(enum AVColorSpace cs);

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVOption AVOption;

typedef struct AVClass {
    const char *class_name;
    const char *(*item_name)(void *ptr);
    const AVOption *option;
    int version;
    int category;
} AVClass;

const char *av_default_item_name(void *ptr);

typedef struct AVBuffer AVBuffer;

typedef struct AVBufferRef {
    AVBuffer *buffer;
    uint8_t *data;
    size_t size;
} AVBufferRef;

typedef struct AVBufferPool AVBufferPool;

AVBufferRef *av_buffer_alloc(int size);
AVBufferRef *av_buffer_allocz(int size);
void av_buffer_unref(AVBufferRef **buf);
AVBufferRef *av_buffer_ref(AVBufferRef *buf);
int av_buffer_is_writable(const AVBufferRef *buf);

typedef AVBufferRef* (*AVBufferAllocFunc)(int size);
typedef struct AVDictionary AVDictionary;

typedef struct AVComponentDescriptor {
    unsigned plane  : 2;
    unsigned depth  : 5;
    unsigned offset : 11;
    unsigned shift  : 10;
    unsigned step   : 4;
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

typedef struct AVFrameSideData {
    enum AVFrameSideDataType type;
    uint8_t *data;
    int      size;
    AVDictionary *metadata;
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

AVFrame *av_frame_alloc(void);
void av_frame_free(AVFrame **frame);
int av_frame_copy_props(AVFrame *dst, const AVFrame *src);
int av_frame_copy(AVFrame *dst, const AVFrame *src);

typedef struct AVHWDeviceInternal AVHWDeviceInternal;
typedef struct AVHWFramesInternal AVHWFramesInternal;

typedef enum AVHWDeviceType {
    AV_HWDEVICE_TYPE_NONE,
    AV_HWDEVICE_TYPE_VDPAU,
    AV_HWDEVICE_TYPE_CUDA,
    AV_HWDEVICE_TYPE_VAAPI,
    AV_HWDEVICE_TYPE_DXVA2,
    AV_HWDEVICE_TYPE_QSV,
    AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    AV_HWDEVICE_TYPE_D3D11VA,
    AV_HWDEVICE_TYPE_DRM,
    AV_HWDEVICE_TYPE_OPENCL,
    AV_HWDEVICE_TYPE_MEDIACODEC,
} AVHWDeviceType;

typedef struct AVHWDeviceContext {
    const AVClass *av_class;
    AVHWDeviceInternal *internal;
    enum AVHWDeviceType type;
    void *hwctx;
    void (*free)(struct AVHWDeviceContext *ctx);
    void *user_opaque;
} AVHWDeviceContext;

typedef struct AVHWFramesContext {
    const AVClass *av_class;
    AVHWFramesInternal *internal;
    AVBufferRef *device_ref;
    AVHWDeviceContext *device_ctx;
    void *hwctx;
    void (*free)(struct AVHWFramesContext *ctx);
    void *user_opaque;
    AVBufferPool *pool;
    int initial_pool_size;
    enum AVPixelFormat format;
    enum AVPixelFormat sw_format;
    int width;
    int height;
} AVHWFramesContext;

int av_hwframe_get_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame, int flags);

#define DECLARE_ALIGNED(n,t,v)      t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_ALIGNED(n,t,v)  t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_CONST(n,t,v)    const t __attribute__ ((aligned (n))) v

void *av_malloc(size_t size);
void *av_mallocz(size_t size);
void *av_calloc(size_t nmemb, size_t size);
void *av_realloc(void *ptr, size_t size);
void av_free(void *ptr);
void av_freep(void *ptr);

#define av_malloc(a) malloc(a)
#define av_mallocz(a) calloc(1, a)
#define av_free(a) free(a)
#define av_freep(p) do { free(*(p)); *(p) = NULL; } while (0)

#define AVERROR(e) (-(e))
#define AVERROR_EOF AVERROR(EIO)
#define AVERROR_ENOMEM AVERROR(ENOMEM)
#define AVERROR_INVALIDDATA AVERROR(EINVAL)

#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)
#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

static inline int av_clip_c(int a, int amin, int amax) {
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}

#define av_clip av_clip_c

#define AV_LOG_QUIET    -8
#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  32
#define AV_LOG_INFO     40
#define AV_LOG_VERBOSE  48
#define AV_LOG_DEBUG    56

void av_log(void *avcl, int level, const char *fmt, ...);

#define LIBAVFILTER_VERSION_MAJOR  9
#define LIBAVFILTER_VERSION_MINOR  12
#define LIBAVFILTER_VERSION_MICRO 100

typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
typedef struct AVFilterPad     AVFilterPad;
typedef struct AVFilterFormats AVFilterFormats;
typedef struct AVFilterChannelLayouts AVFilterChannelLayouts;
typedef struct AVFilterGraph AVFilterGraph;
typedef struct AVFilterInternal AVFilterInternal;
typedef struct AVClass AVClass;

typedef int (avfilter_action_func)(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs);

typedef int (avfilter_execute_func)(AVFilterContext *ctx, avfilter_action_func *func,
                                    void *arg, int *ret, int nb_jobs);

typedef struct AVFilterPad {
    const char *name;
    enum AVMediaType type;
    AVFrame *(*get_video_buffer)(AVFilterLink *link, int w, int h);
    int (*filter_frame)(AVFilterLink *link, AVFrame *frame);
    int (*poll_frame)(AVFilterLink *link);
    int (*request_frame)(AVFilterLink *link);
    int (*config_props)(AVFilterLink *link);
    int needs_fifo;
    int needs_writable;
} AVFilterPad;

typedef struct AVFilterCommand {
    double time;
    char *command;
    char *arg;
    int flags;
    struct AVFilterCommand *next;
} AVFilterCommand;

typedef struct AVFilterContext {
    const AVClass *av_class;
    const struct AVFilter *filter;
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

typedef struct FFFrameQueue FFFrameQueue;

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
    AVFilterChannelLayouts  *in_channel_layouts;
    AVFilterChannelLayouts *out_channel_layouts;
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
#if FF_INTERNAL_FIELDS
    FFFrameQueue fifo;
    int frame_blocked_in;
    int status_in;
    int64_t status_in_pts;
    int status_out;
#else
    char reserved[0xF000];
#endif
};

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

struct AVFilterInternal {
    avfilter_execute_func *execute;
};

typedef struct FFFramePool FFFramePool;

FFFramePool *ff_frame_pool_video_init(AVBufferRef* (*alloc)(int size),
                                      int width,
                                      int height,
                                      enum AVPixelFormat format,
                                      int align);

FFFramePool *ff_frame_pool_audio_init(AVBufferRef* (*alloc)(int size),
                                      int channels,
                                      int samples,
                                      enum AVSampleFormat format,
                                      int align);

void ff_frame_pool_uninit(FFFramePool **pool);

int ff_frame_pool_get_video_config(FFFramePool *pool,
                                   int *width,
                                   int *height,
                                   enum AVPixelFormat *format,
                                   int *align);

int ff_frame_pool_get_audio_config(FFFramePool *pool,
                                   int *channels,
                                   int *nb_samples,
                                   enum AVSampleFormat *format,
                                   int *align);

AVFrame *ff_frame_pool_get(FFFramePool *pool);
AVFrame *ff_default_get_video_buffer(AVFilterLink *link, int w, int h);
AVFrame *ff_null_get_video_buffer(AVFilterLink *link, int w, int h);
AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h);

#define FF_TPRINTF_START(ctx, func) ff_tlog(NULL, "%-16s: ", #func)

int ff_filter_frame(AVFilterLink *link, AVFrame *frame);
int ff_filter_get_nb_threads(AVFilterContext *ctx);

char *ff_get_ref_perms_string(char *buf, size_t buf_size, int perms);
void ff_tlog(void *ctx, const char *fmt, ...);
void ff_tlog_link(void *ctx, AVFilterLink *link, int is_out);

typedef int (avfilter_action_func)(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs);

typedef int (avfilter_execute_func)(AVFilterContext *ctx, avfilter_action_func *func,
                                    void *arg, int *ret, int nb_jobs);

enum DitherMode {
    DITHER_NONE,
    DITHER_FSB,
    DITHER_NB,
};

enum Colorspace {
    CS_UNSPECIFIED,
    CS_BT470M,
    CS_BT470BG,
    CS_BT601_6_525,
    CS_BT601_6_625,
    CS_BT709,
    CS_SMPTE170M,
    CS_SMPTE240M,
    CS_BT2020,
    CS_NB,
};

enum Whitepoint {
    WP_D65,
    WP_C,
    WP_DCI,
    WP_E,
    WP_NB,
};

enum WhitepointAdaptation {
    WP_ADAPT_BRADFORD,
    WP_ADAPT_VON_KRIES,
    NB_WP_ADAPT_NON_IDENTITY,
    WP_ADAPT_IDENTITY = NB_WP_ADAPT_NON_IDENTITY,
    NB_WP_ADAPT,
};

struct PrimaryCoefficients {
    double xr, yr, xg, yg, xb, yb, xw, yw;
};

struct ColorPrimaries {
    enum Whitepoint wp;
    struct PrimaryCoefficients coeff;
};

struct LumaCoefficients {
    double lr, lg, lb;
};

struct TransferCharacteristics {
    double alpha, beta, gamma, delta;
};

typedef struct ColorSpaceDSPContext {
    void *yuv2rgb[2][6];
    void *rgb2yuv[2][6];
    void *yuv2yuv[3][3][6];
} ColorSpaceDSPContext;

typedef struct ColorSpaceContext {
    const AVClass *class;
    ColorSpaceDSPContext dsp;
    enum Colorspace user_all, user_iall;
    enum AVColorSpace in_csp, out_csp, user_csp, user_icsp;
    enum AVColorRange in_rng, out_rng, user_rng, user_irng;
    enum AVColorTransferCharacteristic in_trc, out_trc, user_trc, user_itrc;
    enum AVColorPrimaries in_prm, out_prm, user_prm, user_iprm;
    enum AVPixelFormat in_format, user_format;
    int fast_mode;
    enum DitherMode dither;
    enum WhitepointAdaptation wp_adapt;
    int16_t *rgb[3];
    ptrdiff_t rgb_stride;
    unsigned rgb_sz;
    int *dither_scratch[3][2], *dither_scratch_base[3][2];
    const struct ColorPrimaries *in_primaries, *out_primaries;
    int lrgb2lrgb_passthrough;
    DECLARE_ALIGNED(16, int16_t, lrgb2lrgb_coeffs)[3][3][8];
    const struct TransferCharacteristics *in_txchr, *out_txchr;
    int rgb2rgb_passthrough;
    int16_t *lin_lut, *delin_lut;
    const struct LumaCoefficients *in_lumacoef, *out_lumacoef;
    int yuv2yuv_passthrough, yuv2yuv_fastmode;
    DECLARE_ALIGNED(16, int16_t, yuv2rgb_coeffs)[3][3][8];
    DECLARE_ALIGNED(16, int16_t, rgb2yuv_coeffs)[3][3][8];
    DECLARE_ALIGNED(16, int16_t, yuv2yuv_coeffs)[3][3][8];
    DECLARE_ALIGNED(16, int16_t, yuv_offset)[2][8];
    void *yuv2rgb;
    void *rgb2yuv;
    void *rgb2yuv_fsb;
    void *yuv2yuv;
    double yuv2rgb_dbl_coeffs[3][3], rgb2yuv_dbl_coeffs[3][3];
    int in_y_rng, in_uv_rng, out_y_rng, out_uv_rng;
    int did_warn_range;
} ColorSpaceContext;

typedef struct ThreadData {
    const AVFrame *in;
    AVFrame *out;
    ptrdiff_t in_linesize[3];
    ptrdiff_t out_linesize[3];
    int in_ss_h;
    int out_ss_h;
} ThreadData;

#define BUFFER_ALIGN 32

static const enum AVColorTransferCharacteristic default_trc[CS_NB + 1] = {
    [CS_UNSPECIFIED] = AVCOL_TRC_UNSPECIFIED,
    [CS_BT470M]      = AVCOL_TRC_GAMMA22,
    [CS_BT470BG]     = AVCOL_TRC_GAMMA28,
    [CS_BT601_6_525] = AVCOL_TRC_SMPTE170M,
    [CS_BT601_6_625] = AVCOL_TRC_SMPTE170M,
    [CS_BT709]       = AVCOL_TRC_BT709,
    [CS_SMPTE170M]   = AVCOL_TRC_SMPTE170M,
    [CS_SMPTE240M]   = AVCOL_TRC_SMPTE240M,
    [CS_BT2020]      = AVCOL_TRC_BT2020_10,
    [CS_NB]          = AVCOL_TRC_UNSPECIFIED,
};

static const enum AVColorPrimaries default_prm[CS_NB + 1] = {
    [CS_UNSPECIFIED] = AVCOL_PRI_UNSPECIFIED,
    [CS_BT470M]      = AVCOL_PRI_BT470M,
    [CS_BT470BG]     = AVCOL_PRI_BT470BG,
    [CS_BT601_6_525] = AVCOL_PRI_SMPTE170M,
    [CS_BT601_6_625] = AVCOL_PRI_BT470BG,
    [CS_BT709]       = AVCOL_PRI_BT709,
    [CS_SMPTE170M]   = AVCOL_PRI_SMPTE170M,
    [CS_SMPTE240M]   = AVCOL_PRI_SMPTE240M,
    [CS_BT2020]      = AVCOL_PRI_BT2020,
    [CS_NB]          = AVCOL_PRI_UNSPECIFIED,
};

static const enum AVColorSpace default_csp[CS_NB + 1] = {
    [CS_UNSPECIFIED] = AVCOL_SPC_UNSPECIFIED,
    [CS_BT470M]      = AVCOL_SPC_SMPTE170M,
    [CS_BT470BG]     = AVCOL_SPC_BT470BG,
    [CS_BT601_6_525] = AVCOL_SPC_SMPTE170M,
    [CS_BT601_6_625] = AVCOL_SPC_BT470BG,
    [CS_BT709]       = AVCOL_SPC_BT709,
    [CS_SMPTE170M]   = AVCOL_SPC_SMPTE170M,
    [CS_SMPTE240M]   = AVCOL_SPC_SMPTE240M,
    [CS_BT2020]      = AVCOL_SPC_BT2020_NCL,
    [CS_NB]          = AVCOL_SPC_UNSPECIFIED,
};

static void uninit(AVFilterContext *ctx);
static int convert(AVFilterContext *ctx, void *data, int job_nr, int n_jobs);
static int create_filtergraph(AVFilterContext *ctx, AVFrame *in, AVFrame *out);

void ff_tlog(void *ctx, const char *fmt, ...) { (void)ctx; (void)fmt; }
void ff_tlog_link(void *ctx, AVFilterLink *link, int is_out) { (void)ctx; (void)link; (void)is_out; }
int ff_filter_frame(AVFilterLink *link, AVFrame *frame) { (void)link; (void)frame; return 0; }
int ff_filter_get_nb_threads(AVFilterContext *ctx) { (void)ctx; return 1; }
const struct AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt) { (void)pix_fmt; return NULL; }
AVFrame *av_frame_alloc(void) { return NULL; }
void av_frame_free(AVFrame **frame) { (void)frame; }
int av_frame_copy_props(AVFrame *dst, const AVFrame *src) { (void)dst; (void)src; return 0; }
int av_frame_copy(AVFrame *dst, const AVFrame *src) { (void)dst; (void)src; return 0; }
int av_hwframe_get_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame, int flags) { (void)hwframe_ctx; (void)frame; (void)flags; return 0; }
const char *av_color_space_name(enum AVColorSpace cs) { (void)cs; return NULL; }
const char *av_default_item_name(void *ptr) { (void)ptr; return NULL; }

static void uninit(AVFilterContext *ctx) { (void)ctx; }
static int convert(AVFilterContext *ctx, void *data, int job_nr, int n_jobs) { (void)ctx; (void)data; (void)job_nr; (void)n_jobs; return 0; }
static int create_filtergraph(AVFilterContext *ctx, AVFrame *in, AVFrame *out) { (void)ctx; (void)in; (void)out; return 0; }

AVFrame *ff_default_get_video_buffer(AVFilterLink *link, int w, int h)
{
    AVFrame *frame = NULL;
    int pool_width = 0;
    int pool_height = 0;
    int pool_align = 0;
    enum AVPixelFormat pool_format = AV_PIX_FMT_NONE;

    if (link->hw_frames_ctx &&
        ((AVHWFramesContext*)link->hw_frames_ctx->data)->format == link->format) {
        int ret;
        AVFrame *frame = av_frame_alloc();

        if (!frame)
            return NULL;

        ret = av_hwframe_get_buffer(link->hw_frames_ctx, frame, 0);
        if (ret < 0)
            av_frame_free(&frame);

        return frame;
    }

    if (!link->frame_pool) {
        link->frame_pool = ff_frame_pool_video_init(av_buffer_allocz, w, h,
                                                    link->format, BUFFER_ALIGN);
        if (!link->frame_pool)
            return NULL;
    } else {
        if (ff_frame_pool_get_video_config(link->frame_pool,
                                           &pool_width, &pool_height,
                                           &pool_format, &pool_align) < 0) {
            return NULL;
        }

        if (pool_width != w || pool_height != h ||
            pool_format != link->format || pool_align != BUFFER_ALIGN) {

            ff_frame_pool_uninit((FFFramePool **)&link->frame_pool);
            link->frame_pool = ff_frame_pool_video_init(av_buffer_allocz, w, h,
                                                        link->format, BUFFER_ALIGN);
            if (!link->frame_pool)
                return NULL;
        }
    }

    frame = ff_frame_pool_get(link->frame_pool);
    if (!frame)
        return NULL;

    frame->sample_aspect_ratio = link->sample_aspect_ratio;

    return frame;
}

AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h)
{
    AVFrame *ret = NULL;

    FF_TPRINTF_START(NULL, get_video_buffer); ff_tlog_link(NULL, link, 0);

    if (link->dstpad->get_video_buffer)
        ret = link->dstpad->get_video_buffer(link, w, h);

    if (!ret)
        ret = ff_default_get_video_buffer(link, w, h);

    return ret;
}

static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    AVFilterContext *ctx = link->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ColorSpaceContext *s = ctx->priv;
    // FIXME if yuv2yuv_passthrough, don't get a new buffer but use the
    // input one if it is writable *OR* the actual literal values of in_*
    // and out_* are identical (not just their respective properties)
    AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    int res;
    ptrdiff_t rgb_stride = FFALIGN(in->width * sizeof(int16_t), 32);
    unsigned rgb_sz = rgb_stride * in->height;
    ThreadData td;

    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    res = av_frame_copy_props(out, in);
    if (res < 0) {
        av_frame_free(&in);
        av_frame_free(&out);
        return res;
    }

    out->color_primaries = s->user_prm == AVCOL_PRI_UNSPECIFIED ?
                           default_prm[FFMIN(s->user_all, CS_NB)] : s->user_prm;
    if (s->user_trc == AVCOL_TRC_UNSPECIFIED) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(out->format);

        out->color_trc   = default_trc[FFMIN(s->user_all, CS_NB)];
        if (out->color_trc == AVCOL_TRC_BT2020_10 && desc && desc->comp[0].depth >= 12)
            out->color_trc = AVCOL_TRC_BT2020_12;
    } else {
        out->color_trc   = s->user_trc;
    }
    out->colorspace      = s->user_csp == AVCOL_SPC_UNSPECIFIED ?
                           default_csp[FFMIN(s->user_all, CS_NB)] : s->user_csp;
    out->color_range     = s->user_rng == AVCOL_RANGE_UNSPECIFIED ?
                           in->color_range : s->user_rng;
    if (rgb_sz != s->rgb_sz) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(out->format);
        int uvw = in->width >> desc->log2_chroma_w;

        av_freep(&s->rgb[0]);
        av_freep(&s->rgb[1]);
        av_freep(&s->rgb[2]);
        s->rgb_sz = 0;
        av_freep(&s->dither_scratch_base[0][0]);
        av_freep(&s->dither_scratch_base[0][1]);
        av_freep(&s->dither_scratch_base[1][0]);
        av_freep(&s->dither_scratch_base[1][1]);
        av_freep(&s->dither_scratch_base[2][0]);
        av_freep(&s->dither_scratch_base[2][1]);

        s->rgb[0] = av_malloc(rgb_sz);
        s->rgb[1] = av_malloc(rgb_sz);
        s->rgb[2] = av_malloc(rgb_sz);
        s->dither_scratch_base[0][0] =
            av_malloc(sizeof(*s->dither_scratch_base[0][0]) * (in->width + 4));
        s->dither_scratch_base[0][1] =
            av_malloc(sizeof(*s->dither_scratch_base[0][1]) * (in->width + 4));
        s->dither_scratch_base[1][0] =
            av_malloc(sizeof(*s->dither_scratch_base[1][0]) * (uvw + 4));
        s->dither_scratch_base[1][1] =
            av_malloc(sizeof(*s->dither_scratch_base[1][1]) * (uvw + 4));
        s->dither_scratch_base[2][0] =
            av_malloc(sizeof(*s->dither_scratch_base[2][0]) * (uvw + 4));
        s->dither_scratch_base[2][1] =
            av_malloc(sizeof(*s->dither_scratch_base[2][1]) * (uvw + 4));
        s->dither_scratch[0][0] = &s->dither_scratch_base[0][0][1];
        s->dither_scratch[0][1] = &s->dither_scratch_base[0][1][1];
        s->dither_scratch[1][0] = &s->dither_scratch_base[1][0][1];
        s->dither_scratch[1][1] = &s->dither_scratch_base[1][1][1];
        s->dither_scratch[2][0] = &s->dither_scratch_base[2][0][1];
        s->dither_scratch[2][1] = &s->dither_scratch_base[2][1][1];
        if (!s->rgb[0] || !s->rgb[1] || !s->rgb[2] ||
            !s->dither_scratch_base[0][0] || !s->dither_scratch_base[0][1] ||
            !s->dither_scratch_base[1][0] || !s->dither_scratch_base[1][1] ||
            !s->dither_scratch_base[2][0] || !s->dither_scratch_base[2][1]) {
            uninit(ctx);
            av_frame_free(&in);
            av_frame_free(&out);
            return AVERROR(ENOMEM);
        }
        s->rgb_sz = rgb_sz;
    }
    res = create_filtergraph(ctx, in, out);
    if (res < 0) {
        av_frame_free(&in);
        av_frame_free(&out);
        return res;
    }
    s->rgb_stride = rgb_stride / sizeof(int16_t);
    td.in = in;
    td.out = out;
    td.in_linesize[0] = in->linesize[0];
    td.in_linesize[1] = in->linesize[1];
    td.in_linesize[2] = in->linesize[2];
    td.out_linesize[0] = out->linesize[0];
    td.out_linesize[1] = out->linesize[1];
    td.out_linesize[2] = out->linesize[2];
    td.in_ss_h = av_pix_fmt_desc_get(in->format)->log2_chroma_h;
    td.out_ss_h = av_pix_fmt_desc_get(out->format)->log2_chroma_h;
    if (s->yuv2yuv_passthrough) {
        res = av_frame_copy(out, in);
        if (res < 0) {
            av_frame_free(&in);
            av_frame_free(&out);
            return res;
        }
    } else {
        ctx->internal->execute(ctx, convert, &td, NULL,
                               FFMIN((in->height + 1) >> 1, ff_filter_get_nb_threads(ctx)));
    }
    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}
