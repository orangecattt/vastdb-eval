#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdlib.h>

// FROM: libavutil/attributes.h
#ifdef __GNUC__
#    define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#endif

#ifndef av_always_inline
#if AV_GCC_VERSION_AT_LEAST(3,1)
#    define av_always_inline __attribute__((always_inline)) inline
#else
#    define av_always_inline inline
#endif
#endif

#ifndef av_const
#if AV_GCC_VERSION_AT_LEAST(2,6)
#    define av_const __attribute__((const))
#else
#    define av_const
#endif
#endif

// FROM: libavutil/error.h
#if EDOM > 0
#define AVERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#endif

#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_ENOMEM AVERROR(ENOMEM)

// FROM: libavutil/log.h
#define AV_LOG_ERROR 16

// FROM: libavcodec/avcodec.h
#define AV_INPUT_BUFFER_PADDING_SIZE 32

// FROM: libavcodec/parser.h
#define END_NOT_FOUND (-100)

// FROM: libavutil/rational.h
typedef struct AVRational{
    int num;
    int den;
} AVRational;

// FROM: libavutil/log.h
typedef struct AVClass {
    const char* class_name;
    const char* (*item_name)(void* ctx);
    const struct AVOption *option;
    int version;
    int log_level_offset_offset;
    int parent_log_context_offset;
    void* (*child_next)(void *obj, void *prev);
    const struct AVClass* (*child_class_next)(const struct AVClass *prev);
} AVClass;

// FROM: libavcodec/avcodec.h
enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_DNXHD,
};

typedef struct AVCodec AVCodec;
typedef struct AVCodecParser AVCodecParser;
typedef struct AVOption AVOption;

typedef struct AVCodecContext {
    const AVClass *av_class;
    int log_level_offset;
    enum AVMediaType codec_type;
    const struct AVCodec  *codec;
    enum AVCodecID     codec_id;
    unsigned int codec_tag;
} AVCodecContext;

typedef struct AVCodecParserContext {
    void *priv_data;
    struct AVCodecParser *parser;
    int64_t frame_offset;
    int64_t cur_offset;
    int64_t next_frame_offset;
    int pict_type;
    int repeat_pict;
    int64_t pts;
    int64_t dts;
    int64_t last_pts;
    int64_t last_dts;
    int fetch_timestamp;
#define AV_PARSER_PTS_NB 4
    int cur_frame_start_index;
    int64_t cur_frame_offset[AV_PARSER_PTS_NB];
    int64_t cur_frame_pts[AV_PARSER_PTS_NB];
    int64_t cur_frame_dts[AV_PARSER_PTS_NB];
    int flags;
#define PARSER_FLAG_COMPLETE_FRAMES           0x0001
#define PARSER_FLAG_ONCE                      0x0002
#define PARSER_FLAG_FETCHED_OFFSET            0x0004
#define PARSER_FLAG_USE_CODEC_TS              0x1000
    int64_t offset;
    int64_t cur_frame_end[AV_PARSER_PTS_NB];
    int key_frame;
} AVCodecParserContext;

// FROM: libavcodec/parser.h
typedef struct ParseContext{
    uint8_t *buffer;
    int index;
    int last_index;
    unsigned int buffer_size;
    uint32_t state;
    int frame_start_found;
    int overread;
    int overread_index;
    uint64_t state64;
} ParseContext;

// FROM: libavcodec/dnxhddata.h
typedef struct CIDEntry {
    int cid;
    unsigned int width, height;
    unsigned int frame_size;
    unsigned int coding_unit_size;
    uint16_t flags;
    int index_bits;
    int bit_depth;
    int eob_index;
    const uint8_t *luma_weight, *chroma_weight;
    const uint8_t *dc_codes, *dc_bits;
    const uint16_t *ac_codes;
    const uint8_t *ac_bits, *ac_info;
    const uint16_t *run_codes;
    const uint8_t *run_bits, *run;
    int bit_rates[5];
    AVRational frame_rates[5];
    AVRational packet_scale;
} CIDEntry;

typedef struct {
    ParseContext pc;
    int cur_byte;
    int remaining;
    int w, h;
} DNXHDParserContext;

// FROM: libavutil/mem.h
void *av_fast_realloc(void *ptr, unsigned int *size, size_t min_size);

// FROM: libavutil/log.h
void av_log(void *avcl, int level, const char *fmt, ...);

// FROM: libavcodec/parser.h
void ff_parse_close(AVCodecParserContext *s);

// FROM: libavcodec/dnxhddata.h
int avpriv_dnxhd_get_frame_size(int cid);

static av_always_inline uint64_t ff_dnxhd_check_header_prefix_hr(uint64_t prefix)
{
    uint64_t data_offset = prefix >> 16;
    if ((prefix & 0xFFFF0000FFFFLL) == 0x0300 &&
         data_offset >= 0x0280 && data_offset <= 0x2170 &&
         (data_offset & 3) == 0)
        return prefix;
    return 0;
}

static av_always_inline uint64_t ff_dnxhd_check_header_prefix(uint64_t prefix)
{
#define DNXHD_HEADER_INITIAL 0x000002800100
#define DNXHD_HEADER_444     0x000002800200
    if (prefix == DNXHD_HEADER_INITIAL ||
        prefix == DNXHD_HEADER_444     ||
        ff_dnxhd_check_header_prefix_hr(prefix))
        return prefix;
    return 0;
}

// FROM: libavutil/mem.c
void *av_fast_realloc(void *ptr, unsigned int *size, size_t min_size)
{
    void *tmp;

    if (min_size < *size)
        return ptr;

    tmp = realloc(ptr, min_size);
    if (!tmp && min_size > 0) {
        *size = 0;
        return NULL;
    }
    *size = min_size;
    return tmp;
}

// FROM: libavutil/log.c
void av_log(void *avcl, int level, const char *fmt, ...)
{
}

// FROM: libavcodec/parser.c
#define ff_dlog(a, ...) while(0)

int ff_combine_frame(ParseContext *pc, int next,
                     const uint8_t **buf, int *buf_size)
{
    if (pc->overread) {
        ff_dlog(NULL, "overread %d, state:%"PRIX32" next:%d index:%d o_index:%d\n",
                pc->overread, pc->state, next, pc->index, pc->overread_index);
        ff_dlog(NULL, "%X %X %X %X\n",
                (*buf)[0], (*buf)[1], (*buf)[2], (*buf)[3]);
    }

    /* Copy overread bytes from last frame into buffer. */
    for (; pc->overread > 0; pc->overread--)
        pc->buffer[pc->index++] = pc->buffer[pc->overread_index++];

    /* flush remaining if EOF */
    if (!*buf_size && next == END_NOT_FOUND)
        next = 0;

    pc->last_index = pc->index;

    /* copy into buffer end return */
    if (next == END_NOT_FOUND) {
        void *new_buffer = av_fast_realloc(pc->buffer, &pc->buffer_size,
                                           *buf_size + pc->index +
                                           AV_INPUT_BUFFER_PADDING_SIZE);

        if (!new_buffer) {
            av_log(NULL, AV_LOG_ERROR, "Failed to reallocate parser buffer to %d\n", *buf_size + pc->index + AV_INPUT_BUFFER_PADDING_SIZE);
            pc->index = 0;
            return AVERROR(ENOMEM);
        }
        pc->buffer = new_buffer;
        memcpy(&pc->buffer[pc->index], *buf, *buf_size);
        pc->index += *buf_size;
        return -1;
    }

    *buf_size          =
    pc->overread_index = pc->index + next;

    /* append to buffer */
    if (pc->index) {
        void *new_buffer = av_fast_realloc(pc->buffer, &pc->buffer_size,
                                           next + pc->index +
                                           AV_INPUT_BUFFER_PADDING_SIZE);
        if (!new_buffer) {
            av_log(NULL, AV_LOG_ERROR, "Failed to reallocate parser buffer to %d\n", next + pc->index + AV_INPUT_BUFFER_PADDING_SIZE);
            pc->overread_index =
            pc->index = 0;
            return AVERROR(ENOMEM);
        }
        pc->buffer = new_buffer;
        if (next > -AV_INPUT_BUFFER_PADDING_SIZE)
            memcpy(&pc->buffer[pc->index], *buf,
                   next + AV_INPUT_BUFFER_PADDING_SIZE);
        pc->index = 0;
        *buf      = pc->buffer;
    }

    /* store overread bytes */
    for (; next < 0; next++) {
        pc->state   = pc->state   << 8 | pc->buffer[pc->last_index + next];
        pc->state64 = pc->state64 << 8 | pc->buffer[pc->last_index + next];
        pc->overread++;
    }

    if (pc->overread) {
        ff_dlog(NULL, "overread %d, state:%"PRIX32" next:%d index:%d o_index:%d\n",
                pc->overread, pc->state, next, pc->index, pc->overread_index);
        ff_dlog(NULL, "%X %X %X %X\n",
                (*buf)[0], (*buf)[1], (*buf)[2], (*buf)[3]);
    }

    return 0;
}

// FROM: libavcodec/dnxhd_parser.c
static int dnxhd_get_hr_frame_size(int cid, int w, int h)
{
    int result, i;

    i = 0;

    if (i < 0)
        return i;

    result = ((h + 15) / 16) * ((w + 15) / 16) * 1 / 1;
    result = (result + 2048) / 4096 * 4096;

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
    return FFMAX(result, 8192);
}

static int dnxhd_find_frame_end(DNXHDParserContext *dctx,
                                const uint8_t *buf, int buf_size)
{
    ParseContext *pc = &dctx->pc;
    uint64_t state = pc->state64;
    int pic_found = pc->frame_start_found;
    int i = 0;

    if (!pic_found) {
        for (i = 0; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            if (ff_dnxhd_check_header_prefix(state & 0xffffffffff00LL) != 0) {
                i++;
                pic_found = 1;
                dctx->cur_byte = 0;
                dctx->remaining = 0;
                break;
            }
        }
    }

    if (pic_found && !dctx->remaining) {
        if (!buf_size)
            return 0;
        for (; i < buf_size; i++) {
            dctx->cur_byte++;
            state = (state << 8) | buf[i];

            if (dctx->cur_byte == 24) {
                dctx->h = (state >> 32) & 0xFFFF;
            } else if (dctx->cur_byte == 26) {
                dctx->w = (state >> 32) & 0xFFFF;
            } else if (dctx->cur_byte == 42) {
                int cid = (state >> 32) & 0xFFFFFFFF;
                int remaining;

                if (cid <= 0)
                    continue;

                remaining = avpriv_dnxhd_get_frame_size(cid);
                if (remaining <= 0) {
                    remaining = dnxhd_get_hr_frame_size(cid, dctx->w, dctx->h);
                    if (remaining <= 0)
                        continue;
                }
                dctx->remaining = remaining;
                if (buf_size - i + 47 >= dctx->remaining) {
                    int remaining = dctx->remaining;

                    pc->frame_start_found = 0;
                    pc->state64 = -1;
                    dctx->cur_byte = 0;
                    dctx->remaining = 0;
                    return remaining;
                } else {
                    dctx->remaining -= buf_size;
                }
            }
        }
    } else if (pic_found) {
        if (dctx->remaining > buf_size) {
            dctx->remaining -= buf_size;
        } else {
            int remaining = dctx->remaining;

            pc->frame_start_found = 0;
            pc->state64 = -1;
            dctx->cur_byte = 0;
            dctx->remaining = 0;
            return remaining;
        }
    }
    pc->frame_start_found = pic_found;
    pc->state64 = state;
    return END_NOT_FOUND;
}

static int dnxhd_parse(AVCodecParserContext *s,
                       AVCodecContext *avctx,
                       const uint8_t **poutbuf, int *poutbuf_size,
                       const uint8_t *buf, int buf_size)
{
    DNXHDParserContext *dctx = s->priv_data;
    ParseContext *pc = &dctx->pc;
    int next;

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        next = buf_size;
    } else {
        next = dnxhd_find_frame_end(dctx, buf, buf_size);
        if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
            *poutbuf      = NULL;
            *poutbuf_size = 0;
            return buf_size;
        }
    }
    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
