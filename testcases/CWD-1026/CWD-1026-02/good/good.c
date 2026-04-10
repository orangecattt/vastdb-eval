#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

#define av_cold
#define av_always_inline static inline
#define av_const

#define av_assert0(cond) do {                                           \
    if (!(cond)) {                                                      \
        fprintf(stderr, "Assertion failed: %s\n", #cond);               \
    }                                                                   \
} while (0)

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))
#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

#define MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA        (-('I' | ('N' << 8) | ('D' << 16) | (unsigned)('A' << 24)))
#define AVERROR_PATCHWELCOME       (-('P' | ('A' << 8) | ('W' << 16) | (unsigned)('E' << 24)))
#define AVERROR_INVALIDDATA_NUM    (-1094995529)
#define ENOMEM 12

#define AV_INPUT_BUFFER_PADDING_SIZE 64

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_PAL8,
    AV_PIX_FMT_RGB565,
};

#define AV_FRAME_FLAG_CORRUPT       (1 << 0)
#define AV_FRAME_FLAG_KEY           (1 << 1)

enum AVPictureType {
    AV_PICTURE_TYPE_NONE = 0,
    AV_PICTURE_TYPE_I,
    AV_PICTURE_TYPE_P,
};

#define AV_LOG_ERROR   16
#define AV_LOG_WARNING 24
#define AV_LOG_DEBUG   48

#define av_bswap16(x) (((x) >> 8) | ((x) << 8))
#define av_le2ne16(x) av_bswap16(x)

static inline void av_freep(void *ptr) {
    void **p = (void **)ptr;
    if (*p) {
        free(*p);
        *p = NULL;
    }
}

void *av_malloc(size_t size);
void av_free(void *ptr);

static inline void av_fast_padded_mallocz(void *ptr, unsigned int *size, size_t min_size) {
    void **p = (void **)ptr;
    if (*p) {
        memset(*p, 0, *size);
        return;
    }
    *size = min_size;
    *p = calloc(1, min_size);
}

static inline void av_memcpy_backptr(uint8_t *dst, int back, int cnt) {
    for (; cnt > 0; cnt--) {
        dst[0] = dst[-back];
        dst++;
    }
}

static inline uint8_t av_clip_uint8_c(int a) {
    if (a & (~0xFF)) return (~a) >> 31;
    else             return a;
}
#define av_clip_uint8 av_clip_uint8_c

void av_log(void *avcl, int level, const char *fmt, ...);

typedef struct AVPacket {
    uint8_t *data;
    int   size;
} AVPacket;

typedef struct AVFrame {
    uint8_t *data[8];
    int linesize[8];
    int width, height;
    int nb_samples;
    int format;
    enum AVPictureType pict_type;
    int flags;
    void *buf[8];
} AVFrame;

typedef struct AVCodecContext {
    void *priv_data;
    int width;
    int height;
    enum AVPixelFormat pix_fmt;
    void *extradata;
    int extradata_size;
} AVCodecContext;

typedef struct GetByteContext {
    const uint8_t *buffer, *buffer_end, *buffer_start;
} GetByteContext;

av_always_inline uint16_t bytestream2_get_le16u(GetByteContext *g);
av_always_inline uint16_t bytestream2_get_le16(GetByteContext *g);
av_always_inline uint32_t bytestream2_get_le32u(GetByteContext *g);
av_always_inline uint32_t bytestream2_get_be32u(GetByteContext *g);
av_always_inline uint32_t bytestream2_get_be32(GetByteContext *g);
av_always_inline unsigned int bytestream2_get_be24u(GetByteContext *g);
av_always_inline unsigned int bytestream2_get_be24(GetByteContext *g);
av_always_inline unsigned int bytestream2_get_byteu(GetByteContext *g);
av_always_inline unsigned int bytestream2_get_byte(GetByteContext *g);
av_always_inline uint16_t bytestream2_get_be16u(GetByteContext *g);
av_always_inline uint16_t bytestream2_get_be16(GetByteContext *g);
av_always_inline void bytestream2_skip(GetByteContext *g, unsigned int size);
av_always_inline void bytestream2_init(GetByteContext *g, const uint8_t *buf, int buf_size);
av_always_inline int bytestream2_get_bytes_left(const GetByteContext *g);
av_always_inline int bytestream2_tell(const GetByteContext *g);
av_always_inline int bytestream2_seek(GetByteContext *g, int offset, int whence);
av_always_inline unsigned int bytestream2_get_bufferu(GetByteContext *g, uint8_t *dst, unsigned int size);

av_always_inline av_const int av_clip_c(int a, int amin, int amax) {
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}
#define av_clip av_clip_c

#define AV_RL16(x) (*(const uint16_t*)(x))
#define AV_RL32(x) (*(const uint32_t*)(x))

#define NGLYPHS 256
#define GLYPH_COORD_VECT_SIZE 16
#define PALETTE_SIZE 256
#define PALETTE_DELTA 768

typedef struct SANMVideoContext {
    AVCodecContext *avctx;
    GetByteContext gb;

    int version, subversion, have_dimensions, first_fob;
    uint32_t pal[PALETTE_SIZE];
    int16_t delta_pal[PALETTE_DELTA];

    ptrdiff_t pitch;
    int width, height;
    int aligned_width, aligned_height;
    int prev_seq;

    AVFrame *frame;
    uint16_t *fbuf, *frm0, *frm1, *frm2;
    uint8_t *stored_frame;
    uint32_t fbuf_size, frm0_size, frm1_size, frm2_size;
    uint32_t stor_size;
    uint32_t stored_frame_size;

    uint8_t *rle_buf;
    unsigned int rle_buf_size;

    int rotate_code;

    long npixels, buf_size;

    uint16_t codebook[256];
    uint16_t small_codebook[4];

    int8_t p4x4glyphs[NGLYPHS][16];
    int8_t p8x8glyphs[NGLYPHS][64];
    uint8_t c47itbl[0x10000];
    uint8_t c23lut[256];
    uint8_t c4tbl[2][256][16];
    uint16_t c4param;
} SANMVideoContext;

typedef struct SANMFrameHeader {
    int seq_num, codec, rotate_code, rle_output_size;
    uint16_t bg_color;
    uint32_t width, height;
} SANMFrameHeader;

static int process_frame_obj(SANMVideoContext *ctx, GetByteContext *gb,
                             int xoff, int yoff);
static int process_ftch(SANMVideoContext *ctx, int size);
static int process_xpal(SANMVideoContext *ctx, int size);
static int decode_frame(AVCodecContext *avctx, AVFrame *frame,
                        int *got_frame_ptr, AVPacket *pkt);
static int read_frame_header(SANMVideoContext *ctx, SANMFrameHeader *hdr);
static void fill_frame(uint16_t *pbuf, int buf_size, uint16_t color);
static void rotate_bufs(SANMVideoContext *ctx, int rotate_code);
static void init_sizes(SANMVideoContext *ctx, int width, int height);
static int init_buffers(SANMVideoContext *ctx);
static void destroy_buffers(SANMVideoContext *ctx);
static int copy_output(SANMVideoContext *ctx, SANMFrameHeader *hdr);
static int old_codec1(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h, int bit);
static int old_codec2(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h);
static int old_codec4(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h, uint8_t param, uint16_t parm2, int codec);
static int old_codec20(SANMVideoContext *ctx, int w, int h);
static int old_codec21(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h);
static int old_codec23(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h, uint8_t param, uint16_t parm2);
static int old_codec31(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h, uint8_t param, int bit);
static int old_codec37(SANMVideoContext *ctx, int width, int height);
static int old_codec47(SANMVideoContext *ctx, int width, int height);
static int old_codec48(SANMVideoContext *ctx, int width, int height);

typedef int (*frm_decoder)(SANMVideoContext *ctx);

static int decode_nop(SANMVideoContext *ctx);
static int decode_0(SANMVideoContext *ctx);
static int decode_2(SANMVideoContext *ctx);
static int decode_3(SANMVideoContext *ctx);
static int decode_4(SANMVideoContext *ctx);
static int decode_5(SANMVideoContext *ctx);
static int decode_6(SANMVideoContext *ctx);
static int decode_8(SANMVideoContext *ctx);

static const frm_decoder v1_decoders[] = {
    decode_0, decode_nop, decode_2, decode_3, decode_4, decode_5,
    decode_6, decode_nop, decode_8
};

static int old_codec1(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h, int bit);
static int old_codec2(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h);
static int old_codec4(SANMVideoContext *ctx, GetByteContext *gb, int top,
                      int left, int w, int h, uint8_t param, uint16_t parm2, int codec);
static int old_codec20(SANMVideoContext *ctx, int w, int h);
static int old_codec21(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h);
static int old_codec23(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h, uint8_t param, uint16_t parm2);
static int old_codec31(SANMVideoContext *ctx, GetByteContext *gb, int top,
                       int left, int w, int h, uint8_t param, int bit);
static int old_codec37(SANMVideoContext *ctx, int width, int height);
static int old_codec47(SANMVideoContext *ctx, int width, int height);
static int old_codec48(SANMVideoContext *ctx, int width, int height);

static void init_sizes(SANMVideoContext *ctx, int width, int height) {
    ctx->width   = width;
    ctx->height  = height;
    ctx->npixels = width * height;

    ctx->aligned_width  = FFALIGN(width, 8);
    ctx->aligned_height = FFALIGN(height, 8);

    ctx->buf_size = ctx->aligned_width * ctx->aligned_height * sizeof(ctx->frm0[0]);
    ctx->pitch    = width;
}

static void destroy_buffers(SANMVideoContext *ctx) {
    av_freep(&ctx->fbuf);
    av_freep(&ctx->frm0);
    av_freep(&ctx->frm1);
    av_freep(&ctx->frm2);
    av_freep(&ctx->stored_frame);
    av_freep(&ctx->rle_buf);
    ctx->frm0_size =
    ctx->frm1_size =
    ctx->frm2_size = 0;
    init_sizes(ctx, 0, 0);
}

static int init_buffers(SANMVideoContext *ctx) {
    av_fast_padded_mallocz(&ctx->fbuf, &ctx->fbuf_size, ctx->buf_size);
    av_fast_padded_mallocz(&ctx->frm0, &ctx->frm0_size, ctx->buf_size);
    av_fast_padded_mallocz(&ctx->frm1, &ctx->frm1_size, ctx->buf_size);
    av_fast_padded_mallocz(&ctx->frm2, &ctx->frm2_size, ctx->buf_size);
    if (!ctx->version) {
        av_fast_padded_mallocz(&ctx->stored_frame,
                              &ctx->stored_frame_size, ctx->buf_size);
        ctx->stor_size = 0;
    }

    if (!ctx->frm0 || !ctx->frm1 || !ctx->frm2 ||
        (!ctx->stored_frame && !ctx->version)) {
        destroy_buffers(ctx);
        return AVERROR(ENOMEM);
    }

    return 0;
}

static void rotate_bufs(SANMVideoContext *ctx, int rotate_code) {
    if (rotate_code == 2)
        FFSWAP(uint16_t*, ctx->frm1, ctx->frm2);
    FFSWAP(uint16_t*, ctx->frm2, ctx->frm0);
}

static void fill_frame(uint16_t *pbuf, int buf_size, uint16_t color) {
    if (buf_size--) {
        *pbuf++ = color;
        av_memcpy_backptr((uint8_t*)pbuf, 2, 2*buf_size);
    }
}

static int copy_output(SANMVideoContext *ctx, SANMFrameHeader *hdr) {
    uint8_t *dst;
    const uint8_t *src = hdr ? (uint8_t *)ctx->frm0 : (uint8_t *)ctx->fbuf;
    int ret, height = ctx->height;
    ptrdiff_t dstpitch, srcpitch = ctx->pitch * (hdr ? sizeof(ctx->frm0[0]) : 1);

    /* Stub for ff_get_buffer - just allocate data */
    if (!ctx->frame->data[0]) {
        ctx->frame->data[0] = malloc(ctx->height * ctx->pitch);
        ctx->frame->linesize[0] = ctx->pitch;
    }

    dst      = ctx->frame->data[0];
    dstpitch = ctx->frame->linesize[0];

    while (height--) {
        memcpy(dst, src, srcpitch);
        src += srcpitch;
        dst += dstpitch;
    }

    return 0;
}

static int process_xpal(SANMVideoContext *ctx, int size) {
    int16_t *dp = ctx->delta_pal;
    uint32_t *pal = ctx->pal;
    uint16_t cmd;
    uint8_t c[3];
    int i, j;

    bytestream2_skip(&ctx->gb, 2);
    cmd = bytestream2_get_be16(&ctx->gb);

    if (cmd == 1) {
        for (i = 0; i < PALETTE_DELTA; i += 3) {
            c[0] = (*pal >> 16) & 0xFF;
            c[1] = (*pal >>  8) & 0xFF;
            c[2] = (*pal >>  0) & 0xFF;
            for (j = 0; j < 3; j++) {
                int cl = (c[j] * 129) + *dp++;
                c[j] = av_clip_uint8(cl / 128) & 0xFF;
            }
            *pal++ = 0xFFU << 24 | c[0] << 16 | c[1] << 8 | c[2];
        }
    } else if (cmd == 0 || cmd == 2) {
        if (size < PALETTE_DELTA * 2 + 4) {
            av_log(ctx->avctx, AV_LOG_ERROR,
                   "Incorrect palette change block size %u.\n", (unsigned)size);
            return AVERROR_INVALIDDATA;
        }
        for (i = 0; i < PALETTE_DELTA; i++)
            dp[i] = bytestream2_get_le16u(&ctx->gb);

        if (size >= PALETTE_DELTA * 2 + 4 + PALETTE_SIZE * 3) {
            for (i = 0; i < PALETTE_SIZE; i++)
                ctx->pal[i] = 0xFFU << 24 | bytestream2_get_be24u(&ctx->gb);
            if (ctx->subversion < 2)
                ctx->pal[0] = 0xFFU << 24;
        }
    }
    return 0;
}

static int read_frame_header(SANMVideoContext *ctx, SANMFrameHeader *hdr) {
    int i, ret;

    if ((ret = bytestream2_get_bytes_left(&ctx->gb)) < 560) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Input frame too short (%d bytes).\n",
               ret);
        return AVERROR_INVALIDDATA;
    }
    bytestream2_skip(&ctx->gb, 8);

    hdr->width  = bytestream2_get_le32u(&ctx->gb);
    hdr->height = bytestream2_get_le32u(&ctx->gb);

    if (hdr->width != ctx->width || hdr->height != ctx->height) {
        return AVERROR_PATCHWELCOME;
    }

    hdr->seq_num     = bytestream2_get_le16u(&ctx->gb);
    hdr->codec       = bytestream2_get_byteu(&ctx->gb);
    hdr->rotate_code = bytestream2_get_byteu(&ctx->gb);

    bytestream2_skip(&ctx->gb, 4);

    for (i = 0; i < 4; i++)
        ctx->small_codebook[i] = bytestream2_get_le16u(&ctx->gb);
    hdr->bg_color = bytestream2_get_le16u(&ctx->gb);

    bytestream2_skip(&ctx->gb, 2);

    hdr->rle_output_size = bytestream2_get_le32u(&ctx->gb);
    for (i = 0; i < 256; i++)
        ctx->codebook[i] = bytestream2_get_le16u(&ctx->gb);

    bytestream2_skip(&ctx->gb, 8);

    return 0;
}

av_always_inline void bytestream2_skip(GetByteContext *g, unsigned int size) {
    g->buffer += FFMIN(g->buffer_end - g->buffer, size);
}

av_always_inline void bytestream2_init(GetByteContext *g,
                                              const uint8_t *buf,
                                              int buf_size) {
    av_assert0(buf_size >= 0);
    g->buffer       = buf;
    g->buffer_start = buf;
    g->buffer_end   = buf + buf_size;
}

av_always_inline int bytestream2_get_bytes_left(const GetByteContext *g) {
    return (int)(g->buffer_end - g->buffer);
}

av_always_inline int bytestream2_tell(const GetByteContext *g) {
    return (int)(g->buffer - g->buffer_start);
}

av_always_inline int bytestream2_seek(GetByteContext *g, int offset, int whence) {
    switch (whence) {
    case 1: /* SEEK_CUR */
        offset += g->buffer - g->buffer_start;
        break;
    case 2: /* SEEK_END */
        offset += g->buffer_end - g->buffer_start;
        break;
    case 0: /* SEEK_SET */
        break;
    default:
        return AVERROR(22); /* EINVAL */
    }
    if (offset < 0 || offset > g->buffer_end - g->buffer_start)
        return AVERROR(22);
    g->buffer = g->buffer_start + offset;
    return bytestream2_tell(g);
}

static int process_ftch(SANMVideoContext *ctx, int size)
{
    int xoff, yoff, ret;
    GetByteContext gb;

    /* FTCH defines additional x/y offsets */
    if (size == 6) {
        if (bytestream2_get_bytes_left(&ctx->gb) < 6)
            return AVERROR_INVALIDDATA;
        bytestream2_skip(&ctx->gb, 2);
        xoff = bytestream2_get_le16u(&ctx->gb);
        yoff = bytestream2_get_le16u(&ctx->gb);
    } else if (size == 12) {
        av_assert0(bytestream2_get_bytes_left(&ctx->gb) >= 12);
        bytestream2_skip(&ctx->gb, 4);
        xoff = bytestream2_get_be32u(&ctx->gb);
        yoff = bytestream2_get_be32u(&ctx->gb);
    } else
        return 1;

    if (ctx->stor_size > 0) {
        /* decode the stored FOBJ */
        uint8_t *bitstream = av_malloc(ctx->stor_size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!bitstream)
            return AVERROR(ENOMEM);
        memcpy(bitstream, ctx->stored_frame + 4, ctx->stor_size);
        bytestream2_init(&gb, bitstream, ctx->stor_size);
        ret = process_frame_obj(ctx, &gb, xoff, yoff);
        av_free(bitstream);
    } else {
        /* this happens a lot in RA1: The individual files are meant to
         * be played in sequence, with some referencing objects STORed
         * by previous files, e.g. the cockpit codec21 object in RA1 LVL8.
         * But spamming the log with errors is also not helpful, so
         * here we simply ignore this case.
         */
         ret = 0;
    }
    return ret;
}

static int decode_frame(AVCodecContext *avctx, AVFrame *frame,
                        int *got_frame_ptr, AVPacket *pkt)
{
    SANMVideoContext *ctx = avctx->priv_data;
    int i, ret;

    ctx->frame = frame;
    bytestream2_init(&ctx->gb, pkt->data, pkt->size);

    if (!ctx->version) {
        int to_store = 0, have_img = 0;

        ctx->first_fob = 1;

        while (bytestream2_get_bytes_left(&ctx->gb) >= 8) {
            uint32_t sig, size;
            int pos;

            sig  = bytestream2_get_be32u(&ctx->gb);
            size = bytestream2_get_be32u(&ctx->gb);
            pos  = bytestream2_tell(&ctx->gb);

            if (bytestream2_get_bytes_left(&ctx->gb) < size) {
                av_log(avctx, AV_LOG_ERROR, "Incorrect chunk size %u.\n", (unsigned)size);
                break;
            }
            switch (sig) {
            case MKBETAG('N', 'P', 'A', 'L'):
                if (size != PALETTE_SIZE * 3) {
                    av_log(avctx, AV_LOG_ERROR,
                           "Incorrect palette block size %u.\n", (unsigned)size);
                    return AVERROR_INVALIDDATA;
                }
                for (i = 0; i < PALETTE_SIZE; i++)
                    ctx->pal[i] = 0xFFU << 24 | bytestream2_get_be24u(&ctx->gb);
                if (ctx->subversion < 2)
                    ctx->pal[0] = 0xFFU << 24;
                break;
            case MKBETAG('F', 'O', 'B', 'J'):
                if (size < 16)
                    return AVERROR_INVALIDDATA;
                if ((ret = process_frame_obj(ctx, &ctx->gb, 0, 0))) {
                    return ret;
                }
                have_img = 1;

                /* STOR: for ANIMv0/1 store the whole FOBJ datablock, as it
                 * needs to be replayed on FTCH, since none of the codecs
                 * it uses work on the full buffer.
                 * For ANIMv2, it's enough to store the current framebuffer.
                 */
                if (to_store) {
                    to_store = 0;
                    if (ctx->subversion < 2) {
                        if (size <= ctx->stored_frame_size) {
                            int pos2 = bytestream2_tell(&ctx->gb);
                            bytestream2_seek(&ctx->gb, pos, SEEK_SET);
                            bytestream2_get_bufferu(&ctx->gb, ctx->stored_frame, size);
                            bytestream2_seek(&ctx->gb, pos2, SEEK_SET);
                            ctx->stor_size = size;
                        } else {
                            av_log(avctx, AV_LOG_ERROR, "FOBJ too large for STOR\n");
                            ret = AVERROR(ENOMEM);
                        }
                    } else {
                        memcpy(ctx->stored_frame, ctx->fbuf, ctx->buf_size);
                    }
                }
                break;
            case MKBETAG('X', 'P', 'A', 'L'):
                if ((ret = process_xpal(ctx, size)))
                    return ret;
                break;
            case MKBETAG('S', 'T', 'O', 'R'):
                to_store = 1;
                break;
            case MKBETAG('F', 'T', 'C', 'H'):
                if (ctx->subversion < 2) {
                    if ((ret = process_ftch(ctx, size)))
                        return ret;
                } else {
                    memcpy(ctx->fbuf, ctx->stored_frame, ctx->buf_size);
                }
                have_img = 1;
                break;
            default:
                bytestream2_skip(&ctx->gb, size);
                av_log(avctx, AV_LOG_DEBUG,
                       "Unknown/unsupported chunk %08x.\n", (unsigned)sig);
                break;
            }

            /* the sizes of chunks are usually a multiple of 2. However
             * there are a few unaligned FOBJs in RA1 L2PLAY.ANM only (looks
             * like a game bug) and IACT audio chunks which have odd sizes
             * but are padded with a zero byte.
             */
            bytestream2_seek(&ctx->gb, pos + size, SEEK_SET);
            if ((pos + size) & 1) {
                if (0 != bytestream2_get_byteu(&ctx->gb))
                    bytestream2_seek(&ctx->gb, pos + size, SEEK_SET);
            }
        }

        if (have_img) {
            if ((ret = copy_output(ctx, NULL)))
                return ret;
            memcpy(ctx->frame->data[1], ctx->pal, 1024);
            *got_frame_ptr = 1;
        }
    } else {
        SANMFrameHeader header;

        if ((ret = read_frame_header(ctx, &header)))
            return ret;

        ctx->rotate_code = header.rotate_code;
        if (!header.seq_num) {
            ctx->frame->flags |= AV_FRAME_FLAG_KEY;
            ctx->frame->pict_type = AV_PICTURE_TYPE_I;
            fill_frame(ctx->frm1, ctx->npixels, header.bg_color);
            fill_frame(ctx->frm2, ctx->npixels, header.bg_color);
        } else {
            ctx->frame->flags &= ~AV_FRAME_FLAG_KEY;
            ctx->frame->pict_type = AV_PICTURE_TYPE_P;
        }

        if (header.codec < FF_ARRAY_ELEMS(v1_decoders)) {
            if ((ret = v1_decoders[header.codec](ctx))) {
                av_log(avctx, AV_LOG_ERROR,
                       "Subcodec %d: error decoding frame.\n", header.codec);
                return ret;
            }
        } else {
            return AVERROR_PATCHWELCOME;
        }

        if ((ret = copy_output(ctx, &header)))
            return ret;

        *got_frame_ptr = 1;

    }
    if (ctx->rotate_code)
        rotate_bufs(ctx, ctx->rotate_code);

    return pkt->size;
}

static int process_frame_obj(SANMVideoContext *ctx, GetByteContext *gb,
                             int xoff, int yoff)
{
    uint16_t w, h, parm2;
    uint8_t codec, param;
    int16_t left, top;
    int fsc, sote, ret;

    codec = bytestream2_get_byteu(gb);
    param = bytestream2_get_byteu(gb);
    left  = bytestream2_get_le16u(gb) + xoff;
    top   = bytestream2_get_le16u(gb) + yoff;
    w     = bytestream2_get_le16u(gb);
    h     = bytestream2_get_le16u(gb);
    bytestream2_skip(gb, 2);
    parm2 = bytestream2_get_le16u(gb);

    if (w < 1 || h < 1 || w > 640 || h > 480 || left > 640 || top > 480 || left + w <= 0 || top + h <= 0) {
        av_log(ctx->avctx, AV_LOG_WARNING,
               "ignoring invalid fobj dimensions: c%d %d %d @ %d %d\n",
               codec, w, h, left, top);
        return 0;
    }

    /* codecs with their own buffers */
    fsc = (codec == 37 || codec == 47 || codec == 48);

    /* special case for "Shadows of the Empire" videos */
    sote = ((w == 640) && (h == 272) && (codec == 47));
    if (sote)
        left = top = 0;

    if (!ctx->have_dimensions) {
        int xres, yres;
        if (ctx->subversion < 2) {
            /* Rebel Assault 1: 384x242 internal size */
            xres = 384;
            yres = 242;
            if (w > xres || h > yres)
                return AVERROR_INVALIDDATA;
            ctx->have_dimensions = 1;
        } else if (fsc) {
            /* these codecs work on full frames, trust their dimensions */
            xres = w;
            yres = h;
            ctx->have_dimensions = 1;
        } else {
            /* detect common sizes */
            xres = w + left;
            yres = h + top;
            if (sote) {
                /* SotE: has top=60 at all times to center video
                 * inside the 640x480 game window
                 */
                xres = w;
                yres = h;
                ctx->have_dimensions = 1;
            } else if (((xres == 424) && (yres == 260)) ||
                       ((xres == 320) && (yres == 200)) ||
                       ((xres == 640) && (yres == 480))) {
                ctx->have_dimensions = 1;
            }

            xres = FFMAX(xres, ctx->width);
            yres = FFMAX(yres, ctx->height);
        }

        if (ctx->width < xres || ctx->height < yres) {
            int ret = -1; /* ff_set_dimensions stub */
            if (ret < 0)
                return ret;
            init_sizes(ctx, xres, yres);
            if (init_buffers(ctx)) {
                av_log(ctx->avctx, AV_LOG_ERROR, "Error resizing buffers.\n");
                return AVERROR(ENOMEM);
            }
        }
    } else {
        if (((left + w > ctx->width) || (top + h > ctx->height)) && (fsc || codec == 20)) {
            /* correct unexpected overly large frames: this happens
             * for instance with The Dig's sq1.san video: it has a few
             * (all black) 640x480 frames halfway in, while the rest is
             * 320x200.
             */
            av_log(ctx->avctx, AV_LOG_WARNING,
                   "resizing too large fobj: c%d  %d %d @ %d %d\n", codec, w, h, left, top);
            w = ctx->width;
            h = ctx->height;
        }
    }

    if (fsc)
        ctx->subversion = 2;

    /* clear the main buffer on the first fob */
    if (ctx->first_fob) {
        ctx->first_fob = 0;
        if (!fsc)
            memset(ctx->fbuf, 0, ctx->frm0_size);
    }

    if (w + FFMAX(left, 0) > ctx->avctx->width || h + FFMAX(top, 0) > ctx->avctx->height) {
        return AVERROR_PATCHWELCOME;
    }

    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, gb, top, left, w, h, codec == 3);
    case 2:
        return old_codec2(ctx, gb, top, left, w, h);
    case 4:
    case 5:
    case 33:
    case 34:
        return old_codec4(ctx, gb, top, left, w, h, param, parm2, codec);
    case 20:
        return old_codec20(ctx, w, h);
    case 21:
        return old_codec21(ctx, gb, top, left, w, h);
    case 23:
        return old_codec23(ctx, gb, top, left, w, h, param, parm2);
    case 31:
    case 32:
        return old_codec31(ctx, gb, top, left, w, h, param, (codec == 32));
    case 37:
        ret = old_codec37(ctx, w, h); break;
    case 45:
        return 0;
    case 47:
        ret = old_codec47(ctx, w, h); break;
    case 48:
        ret = old_codec48(ctx, w, h); break;
    default:
        ctx->frame->flags |= AV_FRAME_FLAG_CORRUPT;
        return 0;
    }
    if (ret)
        return ret;

    /* copy the codec37/47/48 result to main buffer */
    if ((w == ctx->width) && (h == ctx->height)) {
        memcpy(ctx->fbuf, ctx->frm0, ctx->fbuf_size);
    } else {
        const uint8_t *src = (uint8_t *)ctx->frm0;
        const int cw = FFMIN(w, ctx->width - left);
        const int ch = FFMIN(h, ctx->height - top);
        if ((cw > 0) && (ch > 0) && (left >= 0) && (top >= 0)) {
            uint8_t *dst = (uint8_t *)ctx->fbuf + left + top * ctx->pitch;
            for (int i = 0; i < ch; i++) {
                memcpy(dst, src, cw);
                dst += ctx->pitch;
                src += w;
            }
        }
    }
    return 0;
}
