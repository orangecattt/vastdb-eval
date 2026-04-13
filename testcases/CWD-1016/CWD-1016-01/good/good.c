#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AVClass AVClass;
typedef struct AVFrame AVFrame;
typedef struct AVCodecContext AVCodecContext;
typedef struct AVDictionary AVDictionary;
typedef struct AVPacket AVPacket;
typedef struct AVBufferRef AVBufferRef;
typedef struct AVPixFmtDescriptor AVPixFmtDescriptor;

typedef struct AVRational {
    int num;
    int den;
} AVRational;

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_GBRAPF32,
    AV_PIX_FMT_GBRPF32,
    AV_PIX_FMT_GRAYF32,
    AV_PIX_FMT_RGBA64,
    AV_PIX_FMT_YA16,
    AV_PIX_FMT_RGB48,
    AV_PIX_FMT_GRAY16,
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_UNSPECIFIED,
};

#define AV_LOG_ERROR      16
#define AV_LOG_WARNING    24
#define AV_LOG_INFO       32
#define AV_LOG_DEBUG      48

#define av_unused __attribute__((unused))
#define av_always_inline __inline__ __attribute__((always_inline))
#define av_const __attribute__((const))

#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))

#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA (-1094995529)
#define AVERROR_PATCHWELCOME (-1414092869)
#define AVERROR_ENOMEM (-12)
#define ENOMEM 12
#define EINVAL 22

struct AVFrame {
    uint8_t *data[8];
    int linesize[8];
    int width;
    int height;
    int format;
    int pict_type;
    AVDictionary *metadata;
};

struct AVPacket {
    uint8_t *data;
    int size;
};

struct AVCodecContext {
    AVClass *av_class;
    int width;
    int height;
    enum AVPixelFormat pix_fmt;
    enum AVColorTransferCharacteristic color_trc;
    void *priv_data;
    int (*execute2)(struct AVCodecContext *c, int (*func)(struct AVCodecContext *c2, void *arg, int jobnr, int threadnr), void *arg, int *ret, int job_count);
    AVClass *child_class;
};

typedef struct GetByteContext {
    const uint8_t *buffer, *buffer_end, *buffer_start;
} GetByteContext;

typedef struct PutByteContext {
    uint8_t *buffer, *buffer_end, *buffer_start;
    int eof;
} PutByteContext;

typedef struct ThreadFrame {
    AVFrame *f;
    AVCodecContext *owner[2];
    AVBufferRef *progress;
} ThreadFrame;

enum ExrCompr {
    EXR_RAW,
    EXR_RLE,
    EXR_ZIP1,
    EXR_ZIP16,
    EXR_PIZ,
    EXR_PXR24,
    EXR_B44,
    EXR_B44A,
    EXR_DWA,
    EXR_DWB,
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
    int ysize, xsize;
    int channel_line_size;
} EXRThreadData;

typedef struct ExrDSPContext {
    void (*predictor)(uint8_t *dst, int size);
    void (*reorder_pixels)(uint8_t *dst, const uint8_t *src, int size);
} ExrDSPContext;

typedef union av_intfloat32 {
    uint32_t i;
    float f;
} av_intfloat32;

typedef struct EXRContext {
    AVClass *class;
    AVFrame *picture;
    AVCodecContext *avctx;
    ExrDSPContext dsp;
    enum ExrCompr compression;
    enum ExrPixelType pixel_type;
    int channel_offsets[4];
    const AVPixFmtDescriptor *desc;
    int w, h;
    int32_t xmax, xmin;
    int32_t ymax, ymin;
    uint32_t xdelta, ydelta;
    int scan_lines_per_block;
    EXRTileAttribute tile_attr;
    int is_tile;
    int is_luma;
    GetByteContext gb;
    const uint8_t *buf;
    int buf_size;
    EXRChannel *channels;
    int nb_channels;
    int current_channel_offset;
    EXRThreadData *thread_data;
    const char *layer;
    enum AVColorTransferCharacteristic apply_trc_type;
    float gamma;
    av_intfloat32 gamma_table[65536];
} EXRContext;

#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)

#define AV_PIX_FMT_FLAG_FLOAT 0x0002

struct AVPixFmtDescriptor {
    const char *name;
    uint8_t nb_components;
    uint8_t log2_chroma_w;
    uint8_t log2_chroma_h;
    uint8_t flags;
};

#define AV_PICTURE_TYPE_I 1

static av_always_inline uint64_t bytestream2_get_le64(GetByteContext *g);
static av_always_inline unsigned int bytestream2_get_le32(GetByteContext *g);
static av_always_inline unsigned int bytestream2_get_le24(GetByteContext *g);
static av_always_inline unsigned int bytestream2_get_le16(GetByteContext *g);
static av_always_inline unsigned int bytestream2_get_byte(GetByteContext *g);
static av_always_inline void bytestream2_skip(GetByteContext *g, unsigned int size);
static av_always_inline int bytestream2_get_bytes_left(GetByteContext *g);
static av_always_inline void bytestream2_init(GetByteContext *g, const uint8_t *buf, int buf_size);
static av_always_inline void bytestream2_init_writer(PutByteContext *p, uint8_t *buf, int buf_size);
static av_always_inline int bytestream2_tell(GetByteContext *g);
static av_always_inline void bytestream2_seek(GetByteContext *g, int pos, int whence);
static av_always_inline unsigned int bytestream2_peek_le64(GetByteContext *g);
static av_always_inline void bytestream2_put_le64(PutByteContext *p, const uint64_t value);
static av_always_inline void bytestream2_get_buffer(GetByteContext *g, uint8_t *buf, int size);

void av_log(void *avcl, int level, const char *fmt, ...);
void avpriv_report_missing_feature(void *avcl, const char *feature, ...);

int av_opt_set_defaults(void *s);

void *av_realloc(void *ptr, size_t size);
int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags);
void av_dict_free(AVDictionary **pm);
const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt);
AVRational av_d2q(double d, int max_denominator);
static av_always_inline av_const float av_int2float(uint32_t i);

int ff_set_dimensions(AVCodecContext *s, int width, int height);
int ff_set_sar(AVCodecContext *avctx, AVRational sar);
int ff_thread_get_buffer(AVCodecContext *avctx, ThreadFrame *f, int flags);

static av_always_inline uint64_t bytestream2_get_le64(GetByteContext *g)
{
    const uint8_t *b = g->buffer;
    if (g->buffer_end - g->buffer < 8) {
        g->buffer = g->buffer_end;
        return 0;
    }
    g->buffer += 8;
    return ((uint64_t)b[0]) | ((uint64_t)b[1] << 8) | ((uint64_t)b[2] << 16) |
           ((uint64_t)b[3] << 24) | ((uint64_t)b[4] << 32) | ((uint64_t)b[5] << 40) |
           ((uint64_t)b[6] << 48) | ((uint64_t)b[7] << 56);
}

static av_always_inline unsigned int bytestream2_get_le32(GetByteContext *g)
{
    const uint8_t *b = g->buffer;
    if (g->buffer_end - g->buffer < 4) {
        g->buffer = g->buffer_end;
        return 0;
    }
    g->buffer += 4;
    return ((uint32_t)b[0]) | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

static av_always_inline unsigned int bytestream2_get_le24(GetByteContext *g)
{
    const uint8_t *b = g->buffer;
    if (g->buffer_end - g->buffer < 3) {
        g->buffer = g->buffer_end;
        return 0;
    }
    g->buffer += 3;
    return ((uint32_t)b[0]) | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16);
}

static av_always_inline unsigned int bytestream2_get_le16(GetByteContext *g)
{
    const uint8_t *b = g->buffer;
    if (g->buffer_end - g->buffer < 2) {
        g->buffer = g->buffer_end;
        return 0;
    }
    g->buffer += 2;
    return ((uint32_t)b[0]) | ((uint32_t)b[1] << 8);
}

static av_always_inline unsigned int bytestream2_get_byte(GetByteContext *g)
{
    if (g->buffer_end - g->buffer < 1) {
        g->buffer = g->buffer_end;
        return 0;
    }
    return *g->buffer++;
}

static av_always_inline void bytestream2_skip(GetByteContext *g, unsigned int size)
{
    unsigned int available = g->buffer_end - g->buffer;
    g->buffer += (size < available) ? size : available;
}

static av_always_inline int bytestream2_get_bytes_left(GetByteContext *g)
{
    return g->buffer_end - g->buffer;
}

static av_always_inline void bytestream2_init(GetByteContext *g, const uint8_t *buf, int buf_size)
{
    g->buffer = buf;
    g->buffer_start = buf;
    g->buffer_end = buf + buf_size;
}

static av_always_inline void bytestream2_init_writer(PutByteContext *p, uint8_t *buf, int buf_size)
{
    p->buffer = buf;
    p->buffer_start = buf;
    p->buffer_end = buf + buf_size;
    p->eof = 0;
}

static av_always_inline int bytestream2_tell(GetByteContext *g)
{
    return (int)(g->buffer - g->buffer_start);
}

static av_always_inline void bytestream2_seek(GetByteContext *g, int pos, int whence)
{
    const uint8_t *base = g->buffer_start;
    int new_pos;

    switch (whence) {
    case 0: /* SEEK_SET */
        new_pos = pos;
        break;
    case 1: /* SEEK_CUR */
        new_pos = (g->buffer - base) + pos;
        break;
    case 2: /* SEEK_END */
        new_pos = (g->buffer_end - base) + pos;
        break;
    default:
        return;
    }

    if (new_pos >= 0 && new_pos <= (g->buffer_end - base))
        g->buffer = base + new_pos;
}

static av_always_inline unsigned int bytestream2_peek_le64(GetByteContext *g)
{
    const uint8_t *b = g->buffer;
    if (g->buffer_end - g->buffer < 8)
        return 0;
    return ((uint32_t)b[0]) | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) |
           ((uint32_t)b[3] << 24) | ((uint64_t)((uint32_t)b[4]) << 32) |
           ((uint64_t)((uint32_t)b[5]) << 40) | ((uint64_t)((uint32_t)b[6]) << 48) |
           ((uint64_t)((uint32_t)b[7]) << 56);
}

static av_always_inline void bytestream2_put_le64(PutByteContext *p, const uint64_t value)
{
    if (!p->eof && (p->buffer_end - p->buffer >= 8)) {
        p->buffer[0] = value & 0xff;
        p->buffer[1] = (value >> 8) & 0xff;
        p->buffer[2] = (value >> 16) & 0xff;
        p->buffer[3] = (value >> 24) & 0xff;
        p->buffer[4] = (value >> 32) & 0xff;
        p->buffer[5] = (value >> 40) & 0xff;
        p->buffer[6] = (value >> 48) & 0xff;
        p->buffer[7] = (value >> 56) & 0xff;
        p->buffer += 8;
    } else {
        p->eof = 1;
    }
}

static av_always_inline void bytestream2_get_buffer(GetByteContext *g, uint8_t *buf, int size)
{
    int available = g->buffer_end - g->buffer;
    int to_copy = (size < available) ? size : available;
    memcpy(buf, g->buffer, to_copy);
    g->buffer += to_copy;
}

static int check_header_variable(EXRContext *s, const char *value_name,
                                 const char *value_type, unsigned int minimum_length);
static int decode_block(AVCodecContext *avctx, void *arg, int jobnr, int threadnr);

static int check_header_variable(EXRContext *s,
                                 const char *value_name,
                                 const char *value_type,
                                 unsigned int minimum_length)
{
    int var_size = -1;

    if (bytestream2_get_bytes_left(&s->gb) >= minimum_length &&
        !strcmp(s->gb.buffer, value_name)) {
        s->gb.buffer += strlen(value_name) + 1;
        if (!strcmp(s->gb.buffer, value_type)) {
            s->gb.buffer += strlen(value_type) + 1;
            var_size = bytestream2_get_le32(&s->gb);
            if (var_size > bytestream2_get_bytes_left(&s->gb))
                var_size = 0;
        } else {
            s->gb.buffer -= strlen(value_name) + 1;
        }
    }

    return var_size;
}

static int av_strcasecmp(const char *a, const char *b)
{
    uint8_t c1, c2;
    do {
        c1 = *a++;
        c2 = *b++;
        if (c1 >= 'A' && c1 <= 'Z')
            c1 ^= 0x20;
        if (c2 >= 'A' && c2 <= 'Z')
            c2 ^= 0x20;
    } while (c1 && c1 == c2);
    return c1 - c2;
}

static int decode_header(EXRContext *s, AVFrame *frame)
{
    AVDictionary *metadata = NULL;
    int magic_number, version, i, flags, sar = 0;
    int layer_match = 0;
    int ret;
    int dup_channels = 0;

    s->current_channel_offset = 0;
    s->xmin               = ~0;
    s->xmax               = ~0;
    s->ymin               = ~0;
    s->ymax               = ~0;
    s->xdelta             = ~0;
    s->ydelta             = ~0;
    s->channel_offsets[0] = -1;
    s->channel_offsets[1] = -1;
    s->channel_offsets[2] = -1;
    s->channel_offsets[3] = -1;
    s->pixel_type         = EXR_UNKNOWN;
    s->compression        = EXR_UNKN;
    s->nb_channels        = 0;
    s->w                  = 0;
    s->h                  = 0;
    s->tile_attr.xSize    = -1;
    s->tile_attr.ySize    = -1;
    s->is_tile            = 0;
    s->is_luma            = 0;

    if (bytestream2_get_bytes_left(&s->gb) < 10) {
        av_log(s->avctx, AV_LOG_ERROR, "Header too short to parse.\n");
        return AVERROR_INVALIDDATA;
    }

    magic_number = bytestream2_get_le32(&s->gb);
    if (magic_number != 20000630) {
        /* As per documentation of OpenEXR, it is supposed to be
         * int 20000630 little-endian */
        av_log(s->avctx, AV_LOG_ERROR, "Wrong magic number %d.\n", magic_number);
        return AVERROR_INVALIDDATA;
    }

    version = bytestream2_get_byte(&s->gb);
    if (version != 2) {
        avpriv_report_missing_feature(s->avctx, "Version %d", version);
        return AVERROR_PATCHWELCOME;
    }

    flags = bytestream2_get_le24(&s->gb);

    if (flags & 0x02)
        s->is_tile = 1;
    if (flags & 0x08) {
        avpriv_report_missing_feature(s->avctx, "deep data");
        return AVERROR_PATCHWELCOME;
    }
    if (flags & 0x10) {
        avpriv_report_missing_feature(s->avctx, "multipart");
        return AVERROR_PATCHWELCOME;
    }

    // Parse the header
    while (bytestream2_get_bytes_left(&s->gb) > 0 && *s->gb.buffer) {
        int var_size;
        if ((var_size = check_header_variable(s, "channels",
                                              "chlist", 38)) >= 0) {
            GetByteContext ch_gb;
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            bytestream2_init(&ch_gb, s->gb.buffer, var_size);

            while (bytestream2_get_bytes_left(&ch_gb) >= 19) {
                EXRChannel *channel;
                enum ExrPixelType current_pixel_type;
                int channel_index = -1;
                int xsub, ysub;

                if (strcmp(s->layer, "") != 0) {
                    if (strncmp(ch_gb.buffer, s->layer, strlen(s->layer)) == 0) {
                        layer_match = 1;
                        av_log(s->avctx, AV_LOG_INFO,
                               "Channel match layer : %s.\n", ch_gb.buffer);
                        ch_gb.buffer += strlen(s->layer);
                        if (*ch_gb.buffer == '.')
                            ch_gb.buffer++;         /* skip dot if not given */
                    } else {
                        layer_match = 0;
                        av_log(s->avctx, AV_LOG_INFO,
                               "Channel doesn't match layer : %s.\n", ch_gb.buffer);
                    }
                } else {
                    layer_match = 1;
                }

                if (layer_match) { /* only search channel if the layer match is valid */
                    if (!av_strcasecmp(ch_gb.buffer, "R") ||
                        !av_strcasecmp(ch_gb.buffer, "X") ||
                        !av_strcasecmp(ch_gb.buffer, "U")) {
                        channel_index = 0;
                        s->is_luma = 0;
                    } else if (!av_strcasecmp(ch_gb.buffer, "G") ||
                               !av_strcasecmp(ch_gb.buffer, "V")) {
                        channel_index = 1;
                        s->is_luma = 0;
                    } else if (!av_strcasecmp(ch_gb.buffer, "Y")) {
                        channel_index = 1;
                        s->is_luma = 1;
                    } else if (!av_strcasecmp(ch_gb.buffer, "B") ||
                               !av_strcasecmp(ch_gb.buffer, "Z") ||
                               !av_strcasecmp(ch_gb.buffer, "W")) {
                        channel_index = 2;
                        s->is_luma = 0;
                    } else if (!av_strcasecmp(ch_gb.buffer, "A")) {
                        channel_index = 3;
                    } else {
                        av_log(s->avctx, AV_LOG_WARNING,
                               "Unsupported channel %.256s.\n", ch_gb.buffer);
                    }
                }

                /* skip until you get a 0 */
                while (bytestream2_get_bytes_left(&ch_gb) > 0 &&
                       bytestream2_get_byte(&ch_gb))
                    continue;

                if (bytestream2_get_bytes_left(&ch_gb) < 4) {
                    av_log(s->avctx, AV_LOG_ERROR, "Incomplete header.\n");
                    ret = AVERROR_INVALIDDATA;
                    goto fail;
                }

                current_pixel_type = bytestream2_get_le32(&ch_gb);
                if (current_pixel_type >= EXR_UNKNOWN) {
                    avpriv_report_missing_feature(s->avctx, "Pixel type %d",
                                                  current_pixel_type);
                    ret = AVERROR_PATCHWELCOME;
                    goto fail;
                }

                bytestream2_skip(&ch_gb, 4);
                xsub = bytestream2_get_le32(&ch_gb);
                ysub = bytestream2_get_le32(&ch_gb);

                if (xsub != 1 || ysub != 1) {
                    avpriv_report_missing_feature(s->avctx,
                                                  "Subsampling %dx%d",
                                                  xsub, ysub);
                    ret = AVERROR_PATCHWELCOME;
                    goto fail;
                }

                if (channel_index >= 0 && s->channel_offsets[channel_index] == -1) { /* channel has not been previously assigned */
                    if (s->pixel_type != EXR_UNKNOWN &&
                        s->pixel_type != current_pixel_type) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "RGB channels not of the same depth.\n");
                        ret = AVERROR_INVALIDDATA;
                        goto fail;
                    }
                    s->pixel_type                     = current_pixel_type;
                    s->channel_offsets[channel_index] = s->current_channel_offset;
                } else if (channel_index >= 0) {
                    av_log(s->avctx, AV_LOG_WARNING,
                            "Multiple channels with index %d.\n", channel_index);
                    if (++dup_channels > 10) {
                        ret = AVERROR_INVALIDDATA;
                        goto fail;
                    }
                }

                s->channels = av_realloc(s->channels,
                                         ++s->nb_channels * sizeof(EXRChannel));
                if (!s->channels) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                channel             = &s->channels[s->nb_channels - 1];
                channel->pixel_type = current_pixel_type;
                channel->xsub       = xsub;
                channel->ysub       = ysub;

                if (current_pixel_type == EXR_HALF) {
                    s->current_channel_offset += 2;
                } else {/* Float or UINT32 */
                    s->current_channel_offset += 4;
                }
            }

            /* Check if all channels are set with an offset or if the channels
             * are causing an overflow  */
            if (!s->is_luma) {/* if we expected to have at least 3 channels */
                if (FFMIN3(s->channel_offsets[0],
                           s->channel_offsets[1],
                           s->channel_offsets[2]) < 0) {
                    if (s->channel_offsets[0] < 0)
                        av_log(s->avctx, AV_LOG_ERROR, "Missing red channel.\n");
                    if (s->channel_offsets[1] < 0)
                        av_log(s->avctx, AV_LOG_ERROR, "Missing green channel.\n");
                    if (s->channel_offsets[2] < 0)
                        av_log(s->avctx, AV_LOG_ERROR, "Missing blue channel.\n");
                    ret = AVERROR_INVALIDDATA;
                    goto fail;
                }
            }

            // skip one last byte and update main gb
            s->gb.buffer = ch_gb.buffer + 1;
            continue;
        } else if ((var_size = check_header_variable(s, "dataWindow", "box2i",
                                                     31)) >= 0) {
            int xmin, ymin, xmax, ymax;
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            xmin   = bytestream2_get_le32(&s->gb);
            ymin   = bytestream2_get_le32(&s->gb);
            xmax   = bytestream2_get_le32(&s->gb);
            ymax   = bytestream2_get_le32(&s->gb);

            if (xmin > xmax || ymin > ymax ||
                (unsigned)xmax - xmin >= INT_MAX ||
                (unsigned)ymax - ymin >= INT_MAX) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            s->xmin = xmin;
            s->xmax = xmax;
            s->ymin = ymin;
            s->ymax = ymax;
            s->xdelta = (s->xmax - s->xmin) + 1;
            s->ydelta = (s->ymax - s->ymin) + 1;

            continue;
        } else if ((var_size = check_header_variable(s, "displayWindow",
                                                     "box2i", 34)) >= 0) {
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            bytestream2_skip(&s->gb, 8);
            s->w = bytestream2_get_le32(&s->gb) + 1;
            s->h = bytestream2_get_le32(&s->gb) + 1;

            continue;
        } else if ((var_size = check_header_variable(s, "lineOrder",
                                                     "lineOrder", 25)) >= 0) {
            int line_order;
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            line_order = bytestream2_get_byte(&s->gb);
            av_log(s->avctx, AV_LOG_DEBUG, "line order: %d.\n", line_order);
            if (line_order > 2) {
                av_log(s->avctx, AV_LOG_ERROR, "Unknown line order.\n");
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            continue;
        } else if ((var_size = check_header_variable(s, "pixelAspectRatio",
                                                     "float", 31)) >= 0) {
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            sar = bytestream2_get_le32(&s->gb);

            continue;
        } else if ((var_size = check_header_variable(s, "compression",
                                                     "compression", 29)) >= 0) {
            if (!var_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            if (s->compression == EXR_UNKN)
                s->compression = bytestream2_get_byte(&s->gb);
            else
                av_log(s->avctx, AV_LOG_WARNING,
                       "Found more than one compression attribute.\n");

            continue;
        } else if ((var_size = check_header_variable(s, "tiles",
                                                     "tiledesc", 22)) >= 0) {
            char tileLevel;

            if (!s->is_tile)
                av_log(s->avctx, AV_LOG_WARNING,
                       "Found tile attribute and scanline flags. Exr will be interpreted as scanline.\n");

            s->tile_attr.xSize = bytestream2_get_le32(&s->gb);
            s->tile_attr.ySize = bytestream2_get_le32(&s->gb);

            tileLevel = bytestream2_get_byte(&s->gb);
            s->tile_attr.level_mode = tileLevel & 0x0f;
            s->tile_attr.level_round = (tileLevel >> 4) & 0x0f;

            if (s->tile_attr.level_mode >= EXR_TILE_LEVEL_UNKNOWN) {
                avpriv_report_missing_feature(s->avctx, "Tile level mode %d",
                                              s->tile_attr.level_mode);
                ret = AVERROR_PATCHWELCOME;
                goto fail;
            }

            if (s->tile_attr.level_round >= EXR_TILE_ROUND_UNKNOWN) {
                avpriv_report_missing_feature(s->avctx, "Tile level round %d",
                                              s->tile_attr.level_round);
                ret = AVERROR_PATCHWELCOME;
                goto fail;
            }

            continue;
        } else if ((var_size = check_header_variable(s, "writer",
                                                     "string", 1)) >= 0) {
            uint8_t key[256] = { 0 };

            bytestream2_get_buffer(&s->gb, key, FFMIN(sizeof(key) - 1, var_size));
            av_dict_set(&metadata, "writer", key, 0);

            continue;
        }

        // Check if there are enough bytes for a header
        if (bytestream2_get_bytes_left(&s->gb) <= 9) {
            av_log(s->avctx, AV_LOG_ERROR, "Incomplete header\n");
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        // Process unknown variables
        for (i = 0; i < 2; i++) // value_name and value_type
            while (bytestream2_get_byte(&s->gb) != 0);

        // Skip variable length
        bytestream2_skip(&s->gb, bytestream2_get_le32(&s->gb));
    }

    ff_set_sar(s->avctx, av_d2q(av_int2float(sar), 255));

    if (s->compression == EXR_UNKN) {
        av_log(s->avctx, AV_LOG_ERROR, "Missing compression attribute.\n");
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (s->is_tile) {
        if (s->tile_attr.xSize < 1 || s->tile_attr.ySize < 1) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid tile attribute.\n");
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
    }

    if (bytestream2_get_bytes_left(&s->gb) <= 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Incomplete frame.\n");
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    frame->metadata = metadata;

    // aaand we are done
    bytestream2_skip(&s->gb, 1);
    return 0;
fail:
    av_dict_free(&metadata);
    return ret;
}

static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    EXRContext *s = avctx->priv_data;
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

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    if ((ret = decode_header(s, picture)) < 0)
        return ret;

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
        s->scan_lines_per_block = 32;
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

    if (bytestream2_get_bytes_left(&s->gb)/8 < nb_blocks)
        return AVERROR_INVALIDDATA;

    // check offset table and recreate it if need
    if (!s->is_tile && bytestream2_peek_le64(&s->gb) == 0) {
        av_log(s->avctx, AV_LOG_DEBUG, "recreating invalid scanline offset table\n");

        start_offset_table = bytestream2_tell(&s->gb);
        start_next_scanline = start_offset_table + nb_blocks * 8;
        bytestream2_init_writer(&offset_table_writer, &avpkt->data[start_offset_table], nb_blocks * 8);

        for (y = 0; y < nb_blocks; y++) {
            /* write offset of prev scanline in offset table */
            bytestream2_put_le64(&offset_table_writer, start_next_scanline);

            /* get len of next scanline */
            bytestream2_seek(&s->gb, start_next_scanline + 4, SEEK_SET);/* skip line number */
            start_next_scanline += (bytestream2_get_le32(&s->gb) + 8);
        }
        bytestream2_seek(&s->gb, start_offset_table, SEEK_SET);
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
