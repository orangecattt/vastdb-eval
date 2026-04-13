#include <stdint.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define ENOMEM 12
#define Z_OK 0

#define av_assert1(x) assert(x)
#define AVERROR_ENOMEM 12

#define av_always_inline __attribute__((always_inline)) inline
#define av_const __attribute__((const))
#define av_printf_format(fmt, args) __attribute__((format(printf, fmt, args)))

#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)
#define FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFSIGN(a) ((a) > 0 ? 1 : -1)
#define FFABSU(a) ((a) <= 0 ? -(unsigned)(a) : (unsigned)(a))

#define AV_RL64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[7] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[6] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[1] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[0])

#define AV_RL32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[3] << 24) |    \
     ((uint32_t)((const uint8_t*)(x))[2] << 16) |    \
     ((uint32_t)((const uint8_t*)(x))[1] <<  8) |    \
      (uint32_t)((const uint8_t*)(x))[0])

#define AV_RL16(x)                           \
    ((((const uint8_t*)(x))[1] << 8) |          \
      ((const uint8_t*)(x))[0])

#define AV_WL64(p, val) do {                 \
        uint64_t d = (val);                     \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[2] = (d)>>16;           \
        ((uint8_t*)(p))[3] = (d)>>24;           \
        ((uint8_t*)(p))[4] = (d)>>32;           \
        ((uint8_t*)(p))[5] = (d)>>40;           \
        ((uint8_t*)(p))[6] = (d)>>48;           \
        ((uint8_t*)(p))[7] = (d)>>56;           \
    } while(0)

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
    AV_PIX_FMT_YUV420P9BE,
    AV_PIX_FMT_YUV420P9LE,
    AV_PIX_FMT_YUV420P10BE,
    AV_PIX_FMT_YUV420P10LE,
    AV_PIX_FMT_YUV422P10BE,
    AV_PIX_FMT_YUV422P10LE,
    AV_PIX_FMT_YUV444P9BE,
    AV_PIX_FMT_YUV444P9LE,
    AV_PIX_FMT_YUV444P10BE,
    AV_PIX_FMT_YUV444P10LE,
    AV_PIX_FMT_YUV422P16BE,
    AV_PIX_FMT_YUV422P16LE,
    AV_PIX_FMT_YUV444P16BE,
    AV_PIX_FMT_YUV444P16LE,
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
    AV_PIX_FMT_RGB444BE,
    AV_PIX_FMT_RGB444LE,
    AV_PIX_FMT_BGR444BE,
    AV_PIX_FMT_BGR444LE,
    AV_PIX_FMT_Y400A = AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_GRAY8A = AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_GBRP,
    AV_PIX_FMT_GBRP9BE,
    AV_PIX_FMT_GBRP9LE,
    AV_PIX_FMT_GBRP10BE,
    AV_PIX_FMT_GBRP10LE,
    AV_PIX_FMT_GBRP16BE,
    AV_PIX_FMT_GBRP16LE,
    AV_PIX_FMT_GBRAP,
    AV_PIX_FMT_GBRAP10BE,
    AV_PIX_FMT_GBRAP10LE,
    AV_PIX_FMT_GBRAP16BE,
    AV_PIX_FMT_GBRAP16LE,
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
    AV_PIX_FMT_GBRP12BE,
    AV_PIX_FMT_GBRP12LE,
    AV_PIX_FMT_GBRAP12BE,
    AV_PIX_FMT_GBRAP12LE,
    AV_PIX_FMT_RGB444P12BE,
    AV_PIX_FMT_RGB444P12LE,
    AV_PIX_FMT_BGR444P12BE,
    AV_PIX_FMT_BGR444P12LE,
    AV_PIX_FMT_YA8,
    AV_PIX_FMT_YA16BE,
    AV_PIX_FMT_YA16LE,
    AV_PIX_FMT_GBRAPF32,
    AV_PIX_FMT_GBRPF32,
    AV_PIX_FMT_GRAYF32,
    AV_PIX_FMT_RGBA64,
    AV_PIX_FMT_YA16,
    AV_PIX_FMT_RGB48,
    AV_PIX_FMT_GRAY16,
    AV_PIX_FMT_NB
};

#define AV_PIX_FMT_FLAG_FLOAT           (1 << 0)
#define AV_PIX_FMT_FLAG_BITSTREAM       (1 << 5)
#define AV_PIX_FMT_FLAG_HWACCEL         (1 << 6)
#define AV_PIX_FMT_FLAG_PAL             (1 << 7)
#define AV_PIX_FMT_FLAG_PSEUDOPAL       (1 << 8)
#define AV_PIX_FMT_FLAG_ALPHA           (1 << 9)
#define AV_PIX_FMT_FLAG_BAYER           (1 << 10)

#define FFALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))

typedef struct AVPixFmtDescriptor {
    const char *name;
    uint8_t nb_components;
    uint8_t log2_chroma_w;
    uint8_t log2_chroma_h;
    uint8_t flags;
    struct {
        uint8_t plane;
        uint8_t step;
        uint8_t offset;
        uint8_t shift;
        uint8_t depth;
    } comp[4];
} AVPixFmtDescriptor;

typedef struct AVRational {
    int num;
    int den;
} AVRational;

enum AVLogLevel {
    AV_LOG_QUIET   = -8,
    AV_LOG_PANIC   = 0,
    AV_LOG_FATAL   = 8,
    AV_LOG_ERROR   = 16,
    AV_LOG_WARNING = 24,
    AV_LOG_INFO    = 32,
    AV_LOG_VERBOSE = 40,
    AV_LOG_DEBUG   = 48,
    AV_LOG_TRACE   = 56,
};

#define AV_LOG_ERROR 16

enum AVColorTransferCharacteristic {
    AVCOL_TRC_RESERVED0    = 0,
    AVCOL_TRC_BT709        = 1,
    AVCOL_TRC_UNSPECIFIED  = 2,
    AVCOL_TRC_RESERVED     = 2,
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
    AVCOL_TRC_SMPTEST2084  = 16,
    AVCOL_TRC_SMPTEST428_1 = 17,
    AVCOL_TRC_NB           = 18,
};

typedef double (*avpriv_trc_function)(double);

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

typedef struct AVFrame {
    uint8_t *data[8];
    int linesize[8];
    int width;
    int height;
    enum AVPixelFormat format;
    enum AVColorTransferCharacteristic color_trc;
    enum AVPictureType pict_type;
    void *opaque;
    uint64_t pts;
    int coded_picture_number;
    int display_picture_number;
    int quality;
    void *opaque_ref;
} AVFrame;

enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_EXR,
    AV_CODEC_ID_NB
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

#define AV_CODEC_CAP_DR1             (1 << 1)
#define AV_CODEC_CAP_FRAME_THREADS   (1 << 5)
#define AV_CODEC_CAP_SLICE_THREADS   (1 << 6)

typedef struct AVCodecContext {
    const struct AVCodec *codec;
    enum AVCodecID codec_id;
    enum AVMediaType codec_type;
    int width;
    int height;
    enum AVPixelFormat pix_fmt;
    enum AVColorTransferCharacteristic color_trc;
    void *priv_data;
    AVRational time_base;
    AVRational framerate;
    int (*execute)(struct AVCodecContext *c, int (*func)(struct AVCodecContext *c2, void *arg), void *arg2, void *ret, int count, int size);
    int (*execute2)(struct AVCodecContext *c, int (*func)(struct AVCodecContext *c2, void *arg, int jobnr, int threadnr), void *arg2, void *ret, int count);
    int thread_count;
    void *opaque;
} AVCodecContext;

typedef struct AVPacket {
    uint8_t *data;
    int size;
    int64_t pts;
    int64_t dts;
} AVPacket;

typedef struct ThreadFrame {
    AVFrame *f;
} ThreadFrame;

typedef struct GetByteContext {
    const uint8_t *buffer, *buffer_end, *buffer_start;
} GetByteContext;

typedef struct PutByteContext {
    uint8_t *buffer, *buffer_end, *buffer_start;
    int eof;
} PutByteContext;

void bytestream2_init(GetByteContext *g, const uint8_t *buf, int buf_size);
void bytestream2_init_writer(PutByteContext *p,uint8_t *buf, int buf_size);
int bytestream2_get_bytes_left(GetByteContext *g);
void bytestream2_skip(GetByteContext *g, unsigned int size);
int bytestream2_tell(GetByteContext *g);
int bytestream2_seek(GetByteContext *g, int offset, int whence);

uint64_t bytestream2_get_le64(GetByteContext *g);
uint32_t bytestream2_get_le32(GetByteContext *g);
uint16_t bytestream2_get_le16(GetByteContext *g);
uint64_t bytestream2_peek_le64(GetByteContext *g);
void bytestream2_put_le64(PutByteContext *p, const uint64_t value);
uint32_t bytestream_get_le32(const uint8_t **b);
uint16_t bytestream_get_le16(const uint8_t **b);

extern const uint8_t ff_zigzag_direct[64];

typedef struct ExrDSPContext {
    void (*reorder_pixels)(uint8_t *dst, const uint8_t *src, ptrdiff_t size);
    void (*predictor)(uint8_t *src, ptrdiff_t size);
} ExrDSPContext;

enum ExrCompr {
    EXR_RAW,
    EXR_RLE,
    EXR_ZIP1,
    EXR_ZIP16,
    EXR_PIZ,
    EXR_PXR24,
    EXR_B44,
    EXR_B44A,
    EXR_DWAA,
    EXR_DWAB,
    EXR_UNKN,
};

enum ExrPixelType {
    EXR_UINT,
    EXR_HALF,
    EXR_FLOAT,
    EXR_UNKNOWN,
};

enum ExrTileLevelMode {
    EXR_TILE_LEVEL_ONE,
    EXR_TILE_LEVEL_MIPMAP,
    EXR_TILE_LEVEL_RIPMAP,
    EXR_TILE_LEVEL_UNKNOWN,
};

enum ExrTileLevelRound {
    EXR_TILE_ROUND_UP,
    EXR_TILE_ROUND_DOWN,
    EXR_TILE_ROUND_UNKNOWN,
};

typedef struct EXRChannel {
    int xsub, ysub;
    enum ExrPixelType pixel_type;
} EXRChannel;

typedef struct EXRTileAttribute {
    int32_t xSize;
    int32_t ySize;
    enum ExrTileLevelMode level_mode;
    enum ExrTileLevelRound level_round;
} EXRTileAttribute;

typedef struct EXRThreadData {
    uint8_t *uncompressed_data;
    int uncompressed_size;

    uint8_t *tmp;
    int tmp_size;

    uint8_t *bitmap;
    uint16_t *lut;

    uint8_t *ac_data;
    unsigned ac_size;

    uint8_t *dc_data;
    unsigned dc_size;

    uint8_t *rle_data;
    unsigned rle_size;

    uint8_t *rle_raw_data;
    unsigned rle_raw_size;

    float block[3][64];

    int ysize, xsize;

    int channel_line_size;

    int run_sym;
    void *he;
    uint64_t *freq;
    void *vlc;
} EXRThreadData;

typedef struct EXRContext {
    void *class;
    AVFrame *picture;
    AVCodecContext *avctx;
    ExrDSPContext dsp;

    enum ExrCompr compression;
    enum ExrPixelType pixel_type;
    int channel_offsets[4];
    const AVPixFmtDescriptor *desc;

    int w, h;
    uint32_t sar;
    int32_t xmax, xmin;
    int32_t ymax, ymin;
    uint32_t xdelta, ydelta;

    int scan_lines_per_block;

    EXRTileAttribute tile_attr;
    int is_tile;
    int is_multipart;
    int current_part;

    int is_luma;

    GetByteContext gb;
    const uint8_t *buf;
    int buf_size;

    EXRChannel *channels;
    int nb_channels;
    int current_channel_offset;
    uint32_t chunk_count;

    EXRThreadData *thread_data;

    const char *layer;
    int selected_part;

    enum AVColorTransferCharacteristic apply_trc_type;
    float gamma;
    union av_intfloat32 *gamma_table;

    uint32_t mantissatable[2048];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
} EXRContext;

union av_intfloat32 {
    uint32_t i;
    float f;
};

union av_intfloat64 {
    uint64_t i;
    double f;
};

#define AVERROR_INVALIDDATA -1094995529
#define AVERROR_PATCHWELCOME -1414092869
#define AVERROR(x) (-(x))
#define AVERROR_ENOMEM 12

int decode_header(EXRContext *s, AVFrame *frame);
int zip_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td);
int piz_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td);
int pxr24_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                            int uncompressed_size, EXRThreadData *td);
int rle_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td);
int b44_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td);
int dwa_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td);
int decode_block(AVCodecContext *avctx, void *tdata,
                        int jobnr, int threadnr);
int huf_uncompress(EXRContext *s, EXRThreadData *td, GetByteContext *gb,
                          int16_t *dst, int dst_size);
int ac_uncompress(EXRContext *s, GetByteContext *gb, float *block);
void dct_inverse(float *block);
void convert(float y, float u, float v, float *b, float *g, float *r);
float to_linear(float x, float scale);
int rle(uint8_t *dst, const uint8_t *src, int compressed_size, int uncompressed_size);
int uncompress(uint8_t *dst, unsigned long *destLen, const uint8_t *src, unsigned long srcLen);

void ff_exrdsp_init(ExrDSPContext *c);
void ff_set_sar(AVCodecContext *avctx, AVRational sar);
int ff_set_dimensions(AVCodecContext *s, int width, int height);
int ff_thread_get_buffer(AVCodecContext *avctx, ThreadFrame *f, int flags);
const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);
void avpriv_report_missing_feature(void *avc, const char *msg, ...);
void avpriv_request_sample(void *avc, const char *msg, ...);
double avpriv_get_gamma_from_trc(enum AVColorTransferCharacteristic trc);
avpriv_trc_function avpriv_get_trc_function_from_trc(enum AVColorTransferCharacteristic trc);
void av_log(void *avc, int level, const char *fmt, ...);
int av_rescale_q(int64_t a, AVRational bq, AVRational cq);
AVRational av_d2q(double d, int max_denominator);
float av_int2float(uint32_t i);
uint32_t av_float2int(float f);
void av_fast_padded_malloc(void *ptr, unsigned int *size, size_t min_size);
void av_freep(void *arg);

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);

int ff_set_dimensions(AVCodecContext *s, int width, int height);
void ff_set_sar(AVCodecContext *avctx, AVRational sar);
int ff_thread_get_buffer(AVCodecContext *avctx, ThreadFrame *f, int flags);

void avpriv_report_missing_feature(void *avc, const char *msg, ...);
void avpriv_request_sample(void *avc, const char *msg, ...);

void av_log(void *avc, int level, const char *fmt, ...);

double avpriv_get_gamma_from_trc(enum AVColorTransferCharacteristic trc);
avpriv_trc_function avpriv_get_trc_function_from_trc(enum AVColorTransferCharacteristic trc);
AVRational av_d2q(double d, int max_denominator);

float av_int2float(uint32_t i);
uint32_t av_float2int(float f);

void av_fast_padded_malloc(void *ptr, unsigned int *size, size_t min_size);
void av_freep(void *arg);

int huf_uncompress(EXRContext *s, EXRThreadData *td, GetByteContext *gb,
                          int16_t *dst, int dst_size);
int uncompress(uint8_t *dst, unsigned long *destLen, const uint8_t *src, unsigned long srcLen);
int rle(uint8_t *dst, const uint8_t *src, int compressed_size, int uncompressed_size);
int ac_uncompress(EXRContext *s, GetByteContext *gb, float *block);
void dct_inverse(float *block);
void convert(float y, float u, float v, float *b, float *g, float *r);
float to_linear(float x, float scale);

static uint32_t convertmantissa(uint32_t i);
static void half2float_table(uint32_t *mantissatable, uint32_t *exponenttable,
                             uint16_t *offsettable);
static uint32_t half2float(uint16_t h, uint32_t *mantissatable, uint32_t *exponenttable,
                           uint16_t *offsettable);

static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    EXRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    ThreadFrame frame = { .f = data };
    AVFrame *picture = data;
    uint8_t *ptr;

    int i, y, ret, ymax;
    int planes;
    int out_line_size;
    int nb_blocks;   /* nb scanline or nb tile */
    uint64_t start_offset_table;
    uint64_t start_next_scanline;
    PutByteContext offset_table_writer;

    bytestream2_init(gb, avpkt->data, avpkt->size);

    if ((ret = decode_header(s, picture)) < 0)
        return ret;

    if ((s->compression == EXR_DWAA || s->compression == EXR_DWAB) &&
        s->pixel_type == EXR_HALF) {
        s->current_channel_offset *= 2;
        for (int i = 0; i < 4; i++)
            s->channel_offsets[i] *= 2;
    }

    switch (s->pixel_type) {
    case EXR_FLOAT:
    case EXR_HALF:
        if (s->channel_offsets[3] >= 0) {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_GBRAPF32;
            } else {
                /* todo: change this when a floating point pixel format with luma with alpha is implemented */
                avctx->pix_fmt = AV_PIX_FMT_GBRAPF32;
            }
        } else {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_GBRPF32;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GRAYF32;
            }
        }
        break;
    case EXR_UINT:
        if (s->channel_offsets[3] >= 0) {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGBA64;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_YA16;
            }
        } else {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGB48;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            }
        }
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Missing channel list.\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->apply_trc_type != AVCOL_TRC_UNSPECIFIED)
        avctx->color_trc = s->apply_trc_type;

    switch (s->compression) {
    case EXR_RAW:
    case EXR_RLE:
    case EXR_ZIP1:
        s->scan_lines_per_block = 1;
        break;
    case EXR_PXR24:
    case EXR_ZIP16:
        s->scan_lines_per_block = 16;
        break;
    case EXR_PIZ:
    case EXR_B44:
    case EXR_B44A:
    case EXR_DWAA:
        s->scan_lines_per_block = 32;
        break;
    case EXR_DWAB:
        s->scan_lines_per_block = 256;
        break;
    default:
        avpriv_report_missing_feature(avctx, "Compression %d", s->compression);
        return AVERROR_PATCHWELCOME;
    }

    /* Verify the xmin, xmax, ymin and ymax before setting the actual image size.
     * It's possible for the data window can larger or outside the display window */
    if (s->xmin > s->xmax  || s->ymin > s->ymax ||
        s->ydelta == 0xFFFFFFFF || s->xdelta == 0xFFFFFFFF) {
        av_log(avctx, AV_LOG_ERROR, "Wrong or missing size information.\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_set_dimensions(avctx, s->w, s->h)) < 0)
        return ret;

    ff_set_sar(s->avctx, av_d2q(av_int2float(s->sar), 255));

    s->desc          = av_pix_fmt_desc_get(avctx->pix_fmt);
    if (!s->desc)
        return AVERROR_INVALIDDATA;

    if (s->desc->flags & AV_PIX_FMT_FLAG_FLOAT) {
        planes           = s->desc->nb_components;
        out_line_size    = avctx->width * 4;
    } else {
        planes           = 1;
        out_line_size    = avctx->width * 2 * s->desc->nb_components;
    }

    if (s->is_tile) {
        nb_blocks = ((s->xdelta + s->tile_attr.xSize - 1) / s->tile_attr.xSize) *
        ((s->ydelta + s->tile_attr.ySize - 1) / s->tile_attr.ySize);
    } else { /* scanline */
        nb_blocks = (s->ydelta + s->scan_lines_per_block - 1) /
        s->scan_lines_per_block;
    }

    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        return ret;

    if (bytestream2_get_bytes_left(gb)/8 < nb_blocks)
        return AVERROR_INVALIDDATA;

    // check offset table and recreate it if need
    if (!s->is_tile && bytestream2_peek_le64(gb) == 0) {
        av_log(s->avctx, AV_LOG_DEBUG, "recreating invalid scanline offset table\n");

        start_offset_table = bytestream2_tell(gb);
        start_next_scanline = start_offset_table + nb_blocks * 8;
        bytestream2_init_writer(&offset_table_writer, &avpkt->data[start_offset_table], nb_blocks * 8);

        for (y = 0; y < nb_blocks; y++) {
            /* write offset of prev scanline in offset table */
            bytestream2_put_le64(&offset_table_writer, start_next_scanline);

            /* get len of next scanline */
            bytestream2_seek(gb, start_next_scanline + 4, SEEK_SET);/* skip line number */
            start_next_scanline += (bytestream2_get_le32(gb) + 8);
        }
        bytestream2_seek(gb, start_offset_table, SEEK_SET);
    }

    // save pointer we are going to use in decode_block
    s->buf      = avpkt->data;
    s->buf_size = avpkt->size;

    // Zero out the start if ymin is not 0
    for (i = 0; i < planes; i++) {
        ptr = picture->data[i];
        for (y = 0; y < FFMIN(s->ymin, s->h); y++) {
            memset(ptr, 0, out_line_size);
            ptr += picture->linesize[i];
        }
    }

    s->picture = picture;

    avctx->execute2(avctx, decode_block, s->thread_data, NULL, nb_blocks);

    ymax = FFMAX(0, s->ymax + 1);
    // Zero out the end if ymax+1 is not h
    if (ymax < avctx->height)
        for (i = 0; i < planes; i++) {
            ptr = picture->data[i] + (ymax * picture->linesize[i]);
            for (y = ymax; y < avctx->height; y++) {
                memset(ptr, 0, out_line_size);
                ptr += picture->linesize[i];
            }
        }

    picture->pict_type = AV_PICTURE_TYPE_I;
    *got_frame = 1;

    return avpkt->size;
}

int decode_block(AVCodecContext *avctx, void *tdata,
                        int jobnr, int threadnr)
{
    EXRContext *s = avctx->priv_data;
    AVFrame *const p = s->picture;
    EXRThreadData *td = &s->thread_data[threadnr];
    const uint8_t *channel_buffer[4] = { 0 };
    const uint8_t *buf = s->buf;
    uint64_t line_offset, uncompressed_size;
    uint8_t *ptr;
    uint32_t data_size;
    int line, col = 0;
    uint64_t tile_x, tile_y, tile_level_x, tile_level_y;
    const uint8_t *src;
    int step = s->desc->flags & AV_PIX_FMT_FLAG_FLOAT ? 4 : 2 * s->desc->nb_components;
    int bxmin = 0, axmax = 0, window_xoffset = 0;
    int window_xmin, window_xmax, window_ymin, window_ymax;
    int data_xoffset, data_yoffset, data_window_offset, xsize, ysize;
    int i, x, buf_size = s->buf_size;
    int c, rgb_channel_count;
    float one_gamma = 1.0f / s->gamma;
    avpriv_trc_function trc_func = avpriv_get_trc_function_from_trc(s->apply_trc_type);
    int ret;

    line_offset = AV_RL64(s->gb.buffer + jobnr * 8);

    if (s->is_tile) {
        if (buf_size < 20 || line_offset > buf_size - 20)
            return AVERROR_INVALIDDATA;

        src  = buf + line_offset + 20;
        if (s->is_multipart)
            src += 4;

        tile_x = AV_RL32(src - 20);
        tile_y = AV_RL32(src - 16);
        tile_level_x = AV_RL32(src - 12);
        tile_level_y = AV_RL32(src - 8);

        data_size = AV_RL32(src - 4);
        if (data_size <= 0 || data_size > buf_size - line_offset - 20)
            return AVERROR_INVALIDDATA;

        if (tile_level_x || tile_level_y) { /* tile level, is not the full res level */
            avpriv_report_missing_feature(s->avctx, "Subres tile before full res tile");
            return AVERROR_PATCHWELCOME;
        }

        if (tile_x && s->tile_attr.xSize + (int64_t)FFMAX(s->xmin, 0) >= INT_MAX / tile_x )
            return AVERROR_INVALIDDATA;
        if (tile_y && s->tile_attr.ySize + (int64_t)FFMAX(s->ymin, 0) >= INT_MAX / tile_y )
            return AVERROR_INVALIDDATA;

        line = s->ymin + s->tile_attr.ySize * tile_y;
        col = s->tile_attr.xSize * tile_x;

        if (line < s->ymin || line > s->ymax ||
            s->xmin + col  < s->xmin ||  s->xmin + col  > s->xmax)
            return AVERROR_INVALIDDATA;

        td->ysize = FFMIN(s->tile_attr.ySize, s->ydelta - tile_y * s->tile_attr.ySize);
        td->xsize = FFMIN(s->tile_attr.xSize, s->xdelta - tile_x * s->tile_attr.xSize);

        if (td->xsize * (uint64_t)s->current_channel_offset > INT_MAX)
            return AVERROR_INVALIDDATA;

        td->channel_line_size = td->xsize * s->current_channel_offset;/* uncompress size of one line */
        uncompressed_size = td->channel_line_size * (uint64_t)td->ysize;/* uncompress size of the block */
    } else {
        if (buf_size < 8 || line_offset > buf_size - 8)
            return AVERROR_INVALIDDATA;

        src  = buf + line_offset + 8;
        if (s->is_multipart)
            src += 4;
        line = AV_RL32(src - 8);

        if (line < s->ymin || line > s->ymax)
            return AVERROR_INVALIDDATA;

        data_size = AV_RL32(src - 4);
        if (data_size <= 0 || data_size > buf_size - line_offset - 8)
            return AVERROR_INVALIDDATA;

        td->ysize          = FFMIN(s->scan_lines_per_block, s->ymax - line + 1); /* s->ydelta - line ?? */
        td->xsize          = s->xdelta;

        if (td->xsize * (uint64_t)s->current_channel_offset > INT_MAX)
            return AVERROR_INVALIDDATA;

        td->channel_line_size = td->xsize * s->current_channel_offset;/* uncompress size of one line */
        uncompressed_size = td->channel_line_size * (uint64_t)td->ysize;/* uncompress size of the block */

        if ((s->compression == EXR_RAW && (data_size != uncompressed_size ||
                                           line_offset > buf_size - uncompressed_size)) ||
            (s->compression != EXR_RAW && (data_size > uncompressed_size ||
                                           line_offset > buf_size - data_size))) {
            return AVERROR_INVALIDDATA;
        }
    }

    window_xmin = FFMIN(avctx->width, FFMAX(0, s->xmin + col));
    window_xmax = FFMIN(avctx->width, FFMAX(0, s->xmin + col + td->xsize));
    window_ymin = FFMIN(avctx->height, FFMAX(0, line ));
    window_ymax = FFMIN(avctx->height, FFMAX(0, line + td->ysize));
    xsize = window_xmax - window_xmin;
    ysize = window_ymax - window_ymin;

    /* tile or scanline not visible skip decoding */
    if (xsize <= 0 || ysize <= 0)
        return 0;

    /* is the first tile or is a scanline */
    if(col == 0) {
        window_xmin = 0;
        /* pixels to add at the left of the display window */
        window_xoffset = FFMAX(0, s->xmin);
        /* bytes to add at the left of the display window */
        bxmin = window_xoffset * step;
    }

    /* is the last tile or is a scanline */
    if(col + td->xsize == s->xdelta) {
        window_xmax = avctx->width;
         /* bytes to add at the right of the display window */
        axmax = FFMAX(0, (avctx->width - (s->xmax + 1))) * step;
    }

    if (data_size < uncompressed_size || s->is_tile) { /* td->tmp is use for tile reorganization */
        av_fast_padded_malloc(&td->tmp, &td->tmp_size, uncompressed_size);
        if (!td->tmp)
            return AVERROR(ENOMEM);
    }

    if (data_size < uncompressed_size) {
        av_fast_padded_malloc(&td->uncompressed_data,
                              &td->uncompressed_size, uncompressed_size + 64);/* Force 64 padding for AVX2 reorder_pixels dst */

        if (!td->uncompressed_data)
            return AVERROR(ENOMEM);

        ret = AVERROR_INVALIDDATA;
        switch (s->compression) {
        case EXR_ZIP1:
        case EXR_ZIP16:
            ret = zip_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_PIZ:
            ret = piz_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_PXR24:
            ret = pxr24_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_RLE:
            ret = rle_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_B44:
        case EXR_B44A:
            ret = b44_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_DWAA:
        case EXR_DWAB:
            ret = dwa_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        }
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "decode_block() failed.\n");
            return ret;
        }
        src = td->uncompressed_data;
    }

    /* offsets to crop data outside display window */
    data_xoffset = FFABS(FFMIN(0, s->xmin + col)) * (s->pixel_type == EXR_HALF ? 2 : 4);
    data_yoffset = FFABS(FFMIN(0, line));
    data_window_offset = (data_yoffset * td->channel_line_size) + data_xoffset;

    if (!s->is_luma) {
        channel_buffer[0] = src + (td->xsize * s->channel_offsets[0]) + data_window_offset;
        channel_buffer[1] = src + (td->xsize * s->channel_offsets[1]) + data_window_offset;
        channel_buffer[2] = src + (td->xsize * s->channel_offsets[2]) + data_window_offset;
        rgb_channel_count = 3;
    } else { /* put y data in the first channel_buffer */
        channel_buffer[0] = src + (td->xsize * s->channel_offsets[1]) + data_window_offset;
        rgb_channel_count = 1;
    }
     if (s->channel_offsets[3] >= 0)
        channel_buffer[3] = src + (td->xsize * s->channel_offsets[3]) + data_window_offset;

    if (s->desc->flags & AV_PIX_FMT_FLAG_FLOAT) {
        /* todo: change this when a floating point pixel format with luma with alpha is implemented */
        int channel_count = s->channel_offsets[3] >= 0 ? 4 : rgb_channel_count;
        if (s->is_luma) {
            channel_buffer[1] = channel_buffer[0];
            channel_buffer[2] = channel_buffer[0];
        }

        for (c = 0; c < channel_count; c++) {
            int plane = s->desc->comp[c].plane;
            ptr = p->data[plane] + window_ymin * p->linesize[plane] + (window_xmin * 4);

            for (i = 0; i < ysize; i++, ptr += p->linesize[plane]) {
                const uint8_t *src;
                union av_intfloat32 *ptr_x;

                src = channel_buffer[c];
                ptr_x = (union av_intfloat32 *)ptr;

                // Zero out the start if xmin is not 0
                memset(ptr_x, 0, bxmin);
                ptr_x += window_xoffset;

                if (s->pixel_type == EXR_FLOAT ||
                    s->compression == EXR_DWAA ||
                    s->compression == EXR_DWAB) {
                    // 32-bit
                    union av_intfloat32 t;
                    if (trc_func && c < 3) {
                        for (x = 0; x < xsize; x++) {
                            t.i = bytestream_get_le32(&src);
                            t.f = trc_func(t.f);
                            *ptr_x++ = t;
                        }
                    } else if (one_gamma != 1.f) {
                        for (x = 0; x < xsize; x++) {
                            t.i = bytestream_get_le32(&src);
                            if (t.f > 0.0f && c < 3)  /* avoid negative values */
                                t.f = powf(t.f, one_gamma);
                            *ptr_x++ = t;
                        }
                    } else {
                        for (x = 0; x < xsize; x++) {
                            t.i = bytestream_get_le32(&src);
                            *ptr_x++ = t;
                        }
                    }
                } else if (s->pixel_type == EXR_HALF) {
                    // 16-bit
                    if (c < 3 || !trc_func) {
                        for (x = 0; x < xsize; x++) {
                            *ptr_x++ = s->gamma_table[bytestream_get_le16(&src)];
                        }
                    } else {
                        for (x = 0; x < xsize; x++) {
                            ptr_x[0].i = half2float(bytestream_get_le16(&src),
                                                    s->mantissatable,
                                                    s->exponenttable,
                                                    s->offsettable);
                            ptr_x++;
                        }
                    }
                }

                // Zero out the end if xmax+1 is not w
                memset(ptr_x, 0, axmax);
                channel_buffer[c] += td->channel_line_size;
            }
        }
    } else {

        av_assert1(s->pixel_type == EXR_UINT);
        ptr = p->data[0] + window_ymin * p->linesize[0] + (window_xmin * s->desc->nb_components * 2);

        for (i = 0; i < ysize; i++, ptr += p->linesize[0]) {

            const uint8_t * a;
            const uint8_t *rgb[3];
            uint16_t *ptr_x;

            for (c = 0; c < rgb_channel_count; c++) {
                rgb[c] = channel_buffer[c];
            }

            if (channel_buffer[3])
                a = channel_buffer[3];

            ptr_x = (uint16_t *) ptr;

            // Zero out the start if xmin is not 0
            memset(ptr_x, 0, bxmin);
            ptr_x += window_xoffset * s->desc->nb_components;

            for (x = 0; x < xsize; x++) {
                for (c = 0; c < rgb_channel_count; c++) {
                    *ptr_x++ = bytestream_get_le32(&rgb[c]) >> 16;
                }

                if (channel_buffer[3])
                    *ptr_x++ = bytestream_get_le32(&a) >> 16;
            }

            // Zero out the end if xmax+1 is not w
            memset(ptr_x, 0, axmax);

            channel_buffer[0] += td->channel_line_size;
            channel_buffer[1] += td->channel_line_size;
            channel_buffer[2] += td->channel_line_size;
            if (channel_buffer[3])
                channel_buffer[3] += td->channel_line_size;
        }
    }

    return 0;
}

int dwa_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td)
{
    int64_t version, lo_usize, lo_size;
    int64_t ac_size, dc_size, rle_usize, rle_csize, rle_raw_size;
    int64_t ac_count, dc_count, ac_compression;
    const int dc_w = td->xsize >> 3;
    const int dc_h = td->ysize >> 3;
    GetByteContext gb, agb;
    int skip, ret;

    if (compressed_size <= 88)
        return AVERROR_INVALIDDATA;

    version = AV_RL64(src + 0);
    if (version != 2)
        return AVERROR_INVALIDDATA;

    lo_usize = AV_RL64(src + 8);
    lo_size = AV_RL64(src + 16);
    ac_size = AV_RL64(src + 24);
    dc_size = AV_RL64(src + 32);
    rle_csize = AV_RL64(src + 40);
    rle_usize = AV_RL64(src + 48);
    rle_raw_size = AV_RL64(src + 56);
    ac_count = AV_RL64(src + 64);
    dc_count = AV_RL64(src + 72);
    ac_compression = AV_RL64(src + 80);

    if (compressed_size < 88LL + lo_size + ac_size + dc_size + rle_csize)
        return AVERROR_INVALIDDATA;

    bytestream2_init(&gb, src + 88, compressed_size - 88);
    skip = bytestream2_get_le16(&gb);
    if (skip < 2)
        return AVERROR_INVALIDDATA;

    bytestream2_skip(&gb, skip - 2);

    if (lo_size > 0) {
        if (lo_usize > uncompressed_size)
            return AVERROR_INVALIDDATA;
        bytestream2_skip(&gb, lo_size);
    }

    if (ac_size > 0) {
        unsigned long dest_len = ac_count * 2LL;
        GetByteContext agb = gb;

        if (ac_count > 3LL * td->xsize * s->scan_lines_per_block)
            return AVERROR_INVALIDDATA;

        av_fast_padded_malloc(&td->ac_data, &td->ac_size, dest_len);
        if (!td->ac_data)
            return AVERROR(ENOMEM);

        switch (ac_compression) {
        case 0:
            ret = huf_uncompress(s, td, &agb, (int16_t *)td->ac_data, ac_count);
            if (ret < 0)
                return ret;
        case 1:
            if (uncompress(td->ac_data, &dest_len, agb.buffer, ac_size) != Z_OK ||
                dest_len != ac_count * 2LL)
                return AVERROR_INVALIDDATA;
            break;
        default:
            return AVERROR_INVALIDDATA;
        }

        bytestream2_skip(&gb, ac_size);
    }

    {
        unsigned long dest_len = dc_count * 2LL;
        GetByteContext agb = gb;

        if (dc_count != dc_w * dc_h * 3)
            return AVERROR_INVALIDDATA;

        av_fast_padded_malloc(&td->dc_data, &td->dc_size, FFALIGN(dest_len, 64) * 2);
        if (!td->dc_data)
            return AVERROR(ENOMEM);

        if (uncompress(td->dc_data + FFALIGN(dest_len, 64), &dest_len, agb.buffer, dc_size) != Z_OK ||
            (dest_len != dc_count * 2LL))
            return AVERROR_INVALIDDATA;

        s->dsp.predictor(td->dc_data + FFALIGN(dest_len, 64), dest_len);
        s->dsp.reorder_pixels(td->dc_data, td->dc_data + FFALIGN(dest_len, 64), dest_len);

        bytestream2_skip(&gb, dc_size);
    }

    if (rle_raw_size > 0 && rle_csize > 0 && rle_usize > 0) {
        unsigned long dest_len = rle_usize;

        av_fast_padded_malloc(&td->rle_data, &td->rle_size, rle_usize);
        if (!td->rle_data)
            return AVERROR(ENOMEM);

        av_fast_padded_malloc(&td->rle_raw_data, &td->rle_raw_size, rle_raw_size);
        if (!td->rle_raw_data)
            return AVERROR(ENOMEM);

        if (uncompress(td->rle_data, &dest_len, gb.buffer, rle_csize) != Z_OK ||
            (dest_len != rle_usize))
            return AVERROR_INVALIDDATA;

        ret = rle(td->rle_raw_data, td->rle_data, rle_usize, rle_raw_size);
        if (ret < 0)
            return ret;
        bytestream2_skip(&gb, rle_csize);
    }

    bytestream2_init(&agb, td->ac_data, ac_count * 2);

    for (int y = 0; y < td->ysize; y += 8) {
        for (int x = 0; x < td->xsize; x += 8) {
            memset(td->block, 0, sizeof(td->block));

            for (int j = 0; j < 3; j++) {
                float *block = td->block[j];
                const int idx = (x >> 3) + (y >> 3) * dc_w + dc_w * dc_h * j;
                uint16_t *dc = (uint16_t *)td->dc_data;
                union av_intfloat32 dc_val;

                dc_val.i = half2float(dc[idx], s->mantissatable,
                                      s->exponenttable, s->offsettable);

                block[0] = dc_val.f;
                ac_uncompress(s, &agb, block);
                dct_inverse(block);
            }

            {
                const float scale = s->pixel_type == EXR_FLOAT ? 2.f : 1.f;
                const int o = s->nb_channels == 4;
                float *bo = ((float *)td->uncompressed_data) +
                    y * td->xsize * s->nb_channels + td->xsize * (o + 0) + x;
                float *go = ((float *)td->uncompressed_data) +
                    y * td->xsize * s->nb_channels + td->xsize * (o + 1) + x;
                float *ro = ((float *)td->uncompressed_data) +
                    y * td->xsize * s->nb_channels + td->xsize * (o + 2) + x;
                float *yb = td->block[0];
                float *ub = td->block[1];
                float *vb = td->block[2];

                for (int yy = 0; yy < 8; yy++) {
                    for (int xx = 0; xx < 8; xx++) {
                        const int idx = xx + yy * 8;

                        convert(yb[idx], ub[idx], vb[idx], &bo[xx], &go[xx], &ro[xx]);

                        bo[xx] = to_linear(bo[xx], scale);
                        go[xx] = to_linear(go[xx], scale);
                        ro[xx] = to_linear(ro[xx], scale);
                    }

                    bo += td->xsize * s->nb_channels;
                    go += td->xsize * s->nb_channels;
                    ro += td->xsize * s->nb_channels;
                }
            }
        }
    }

    if (s->nb_channels < 4)
        return 0;

    for (int y = 0; y < td->ysize && td->rle_raw_data; y++) {
        uint32_t *ao = ((uint32_t *)td->uncompressed_data) + y * td->xsize * s->nb_channels;
        uint8_t *ai0 = td->rle_raw_data + y * td->xsize;
        uint8_t *ai1 = td->rle_raw_data + y * td->xsize + rle_raw_size / 2;

        for (int x = 0; x < td->xsize; x++) {
            uint16_t ha = ai0[x] | (ai1[x] << 8);

            ao[x] = half2float(ha, s->mantissatable, s->exponenttable, s->offsettable);
        }
    }

    return 0;
}
