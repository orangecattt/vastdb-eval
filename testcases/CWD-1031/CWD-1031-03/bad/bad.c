#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

// FROM: libavutil/avassert.h
#include <assert.h>
#define av_assert2(cond) assert(cond)

#define av_unused __attribute__((unused))

// FROM: libavcodec/avcodec.h
#define AV_INPUT_BUFFER_PADDING_SIZE 64

// FROM: libavutil/common.h
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) < (b) ? (a) : (b))

// FROM: libavutil/intreadwrite.h
#define AV_RB32(x) (\
    (((const uint8_t*)(x))[0] << 24) | \
    (((const uint8_t*)(x))[1] << 16) | \
    (((const uint8_t*)(x))[2] <<  8) | \
    (((const uint8_t*)(x))[3] <<  0) \
)
#define AV_RL32(x) (\
    (((const uint8_t*)(x))[3] << 24) | \
    (((const uint8_t*)(x))[2] << 16) | \
    (((const uint8_t*)(x))[1] <<  8) | \
    (((const uint8_t*)(x))[0] <<  0) \
)
#define AV_RB64(x) (\
    (((uint64_t)((const uint8_t*)(x))[0]) << 56) | \
    (((uint64_t)((const uint8_t*)(x))[1]) << 48) | \
    (((uint64_t)((const uint8_t*)(x))[2]) << 40) | \
    (((uint64_t)((const uint8_t*)(x))[3]) << 32) | \
    (((uint64_t)((const uint8_t*)(x))[4]) << 24) | \
    (((uint64_t)((const uint8_t*)(x))[5]) << 16) | \
    (((uint64_t)((const uint8_t*)(x))[6]) <<  8) | \
    (((uint64_t)((const uint8_t*)(x))[7]) <<  0) \
)
#define AV_RL64(x) (\
    (((uint64_t)((const uint8_t*)(x))[7]) << 56) | \
    (((uint64_t)((const uint8_t*)(x))[6]) << 48) | \
    (((uint64_t)((const uint8_t*)(x))[5]) << 40) | \
    (((uint64_t)((const uint8_t*)(x))[4]) << 32) | \
    (((uint64_t)((const uint8_t*)(x))[3]) << 24) | \
    (((uint64_t)((const uint8_t*)(x))[2]) << 16) | \
    (((uint64_t)((const uint8_t*)(x))[1]) <<  8) | \
    (((uint64_t)((const uint8_t*)(x))[0]) <<  0) \
)

// FROM: libavutil/mathops.h
#define NEG_USR32(a,s) (((uint32_t)(a))>>(32-(s)))
#define NEG_SSR32(a,s) (((int32_t)(a))>>(32-(s)))

// FROM: libavutil/channel_layout.h
#define AV_CH_LAYOUT_MONO          0x00000004
#define AV_CH_LAYOUT_STEREO        0x00000003
#define AV_CH_LAYOUT_SURROUND      0x00000007
#define AV_CH_LAYOUT_2_1           0x0000000B
#define AV_CH_LAYOUT_4POINT0       0x00000037
#define AV_CH_LAYOUT_2_2           0x00000033
#define AV_CH_LAYOUT_5POINT0       0x00000607
#define AV_CH_LOW_FREQUENCY          0x00000008

// FROM: libavcodec/aac_ac3_parser.h
typedef enum {
    AAC_AC3_PARSE_ERROR_SYNC        = -0x1030c0a,
    AAC_AC3_PARSE_ERROR_BSID        = -0x2030c0a,
    AAC_AC3_PARSE_ERROR_SAMPLE_RATE = -0x3030c0a,
    AAC_AC3_PARSE_ERROR_FRAME_SIZE  = -0x4030c0a,
    AAC_AC3_PARSE_ERROR_FRAME_TYPE  = -0x5030c0a,
    AAC_AC3_PARSE_ERROR_CRC         = -0x6030c0a,
    AAC_AC3_PARSE_ERROR_CHANNEL_CFG = -0x7030c0a,
} AACAC3ParseError;

// FROM: libavcodec/ac3.h
typedef enum {
    AC3_CHMODE_DUALMONO = 0,
    AC3_CHMODE_MONO,
    AC3_CHMODE_STEREO,
    AC3_CHMODE_3F,
    AC3_CHMODE_2F1R,
    AC3_CHMODE_3F1R,
    AC3_CHMODE_2F2R,
    AC3_CHMODE_3F2R
} AC3ChannelMode;

typedef enum AC3DolbySurroundMode {
    AC3_DSURMOD_NOTINDICATED = 0,
    AC3_DSURMOD_OFF,
    AC3_DSURMOD_ON,
    AC3_DSURMOD_RESERVED
} AC3DolbySurroundMode;

typedef enum {
    EAC3_FRAME_TYPE_INDEPENDENT = 0,
    EAC3_FRAME_TYPE_DEPENDENT,
    EAC3_FRAME_TYPE_AC3_CONVERT,
    EAC3_FRAME_TYPE_RESERVED
} EAC3FrameType;

typedef struct AC3HeaderInfo {
    uint16_t sync_word;
    uint16_t crc1;
    uint8_t sr_code;
    uint8_t bitstream_id;
    uint8_t bitstream_mode;
    uint8_t channel_mode;
    uint8_t lfe_on;
    uint8_t frame_type;
    int substreamid;
    int center_mix_level;
    int surround_mix_level;
    uint16_t channel_map;
    int num_blocks;
    int dolby_surround_mode;
    uint8_t sr_shift;
    uint16_t sample_rate;
    uint32_t bit_rate;
    uint8_t channels;
    uint16_t frame_size;
    uint64_t channel_layout;
} AC3HeaderInfo;

// FROM: libavcodec/get_bits.h
typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

#define MIN_CACHE_BITS 25

#define UNCHECKED_BITSTREAM_READER 1

#define OPEN_READER_NOSIZE(name, gb)            \
    unsigned int name ## _index = (gb)->index;  \
    unsigned int av_unused name ## _cache

#define OPEN_READER(name, gb) OPEN_READER_NOSIZE(name, gb)

#define CLOSE_READER(name, gb) (gb)->index = name ## _index

#define UPDATE_CACHE_LE(name, gb) name ## _cache = \
      AV_RL64((gb)->buffer + (name ## _index >> 3)) >> (name ## _index & 7)

#define UPDATE_CACHE_BE(name, gb) name ## _cache = \
      AV_RB64((gb)->buffer + (name ## _index >> 3)) >> (32 - (name ## _index & 7))

#define UPDATE_CACHE(name, gb) UPDATE_CACHE_BE(name, gb)

#define SKIP_CACHE(name, gb, num) name ## _cache <<= (num)

#define SKIP_COUNTER(name, gb, num) name ## _index += (num)

#define SKIP_BITS(name, gb, num)                \
    do {                                        \
        SKIP_CACHE(name, gb, num);              \
        SKIP_COUNTER(name, gb, num);            \
    } while (0)

#define LAST_SKIP_BITS(name, gb, num) SKIP_COUNTER(name, gb, num)

#define SHOW_UBITS_BE(name, gb, num) NEG_USR32(name ## _cache, num)
#define SHOW_SBITS_BE(name, gb, num) NEG_SSR32(name ## _cache, num)

#define SHOW_UBITS(name, gb, num) SHOW_UBITS_BE(name, gb, num)
#define SHOW_SBITS(name, gb, num) SHOW_SBITS_BE(name, gb, num)

#define GET_CACHE(name, gb) ((uint32_t) name ## _cache)

// FROM: libavcodec/ac3tab.c
const uint16_t ff_ac3_frame_size_tab[38][3];
const uint8_t ff_ac3_channels_tab[8];
const uint16_t avpriv_ac3_channel_layout_tab[8];
const uint16_t ff_ac3_sample_rate_tab[3];
const uint16_t ff_ac3_bitrate_tab[19];

// FROM: libavcodec/ac3_parser.c
#define AC3_HEADER_SIZE 7

static const uint8_t eac3_blocks[4];
static const uint8_t center_levels[4];
static const uint8_t surround_levels[4];

static inline unsigned int get_bits(GetBitContext *s, int n)
{
    register int tmp;
    OPEN_READER(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE(re, s);
    tmp = SHOW_UBITS(re, s, n);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
    return tmp;
}

static inline void skip_bits(GetBitContext *s, int n)
{
    OPEN_READER(re, s);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
}

static inline unsigned int get_bits1(GetBitContext *s)
{
    unsigned int index = s->index;
    uint8_t result     = s->buffer[index >> 3];
    result <<= index & 7;
    result >>= 8 - 1;
    index++;
    s->index = index;

    return result;
}

static inline int get_bits_count(const GetBitContext *s)
{
    return s->index;
}

static inline unsigned int show_bits(GetBitContext *s, int n)
{
    register int tmp;
    OPEN_READER_NOSIZE(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE(re, s);
    tmp = SHOW_UBITS(re, s, n);
    return tmp;
}

static inline unsigned int show_bits_long(GetBitContext *s, int n)
{
    if (n <= MIN_CACHE_BITS) {
        return show_bits(s, n);
    } else {
        GetBitContext gb = *s;
        return get_bits(&gb, n);
    }
}

static inline int init_get_bits(GetBitContext *s, const uint8_t *buffer,
                                int bit_size)
{
    int buffer_size;
    int ret = 0;

    if (bit_size >= INT_MAX - FFMAX(7, AV_INPUT_BUFFER_PADDING_SIZE*8) || bit_size < 0 || !buffer) {
        bit_size    = 0;
        buffer      = NULL;
        ret         = -22;
    }

    buffer_size = (bit_size + 7) >> 3;

    s->buffer             = buffer;
    s->size_in_bits       = bit_size;
    s->size_in_bits_plus8 = bit_size + 8;
    s->buffer_end         = buffer + buffer_size;
    s->index              = 0;

    return ret;
}

static inline int init_get_bits8(GetBitContext *s, const uint8_t *buffer,
                                 int byte_size)
{
    if (byte_size > INT_MAX / 8 || byte_size < 0)
        byte_size = -1;
    return init_get_bits(s, buffer, byte_size * 8);
}

int ff_ac3_parse_header(GetBitContext *gbc, AC3HeaderInfo *hdr)
{
    int frame_size_code;

    memset(hdr, 0, sizeof(*hdr));

    hdr->sync_word = get_bits(gbc, 16);
    if(hdr->sync_word != 0x0B77)
        return AAC_AC3_PARSE_ERROR_SYNC;

    hdr->bitstream_id = show_bits_long(gbc, 29) & 0x1F;
    if(hdr->bitstream_id > 16)
        return AAC_AC3_PARSE_ERROR_BSID;

    hdr->num_blocks = 6;

    hdr->center_mix_level   = 5;
    hdr->surround_mix_level = 6;

    hdr->dolby_surround_mode = AC3_DSURMOD_NOTINDICATED;

    if(hdr->bitstream_id <= 10) {
        hdr->crc1 = get_bits(gbc, 16);
        hdr->sr_code = get_bits(gbc, 2);
        if(hdr->sr_code == 3)
            return AAC_AC3_PARSE_ERROR_SAMPLE_RATE;

        frame_size_code = get_bits(gbc, 6);
        if(frame_size_code > 37)
            return AAC_AC3_PARSE_ERROR_FRAME_SIZE;

        skip_bits(gbc, 5);

        hdr->bitstream_mode = get_bits(gbc, 3);
        hdr->channel_mode = get_bits(gbc, 3);

        if(hdr->channel_mode == AC3_CHMODE_STEREO) {
            hdr->dolby_surround_mode = get_bits(gbc, 2);
        } else {
            if((hdr->channel_mode & 1) && hdr->channel_mode != AC3_CHMODE_MONO)
                hdr->  center_mix_level =   center_levels[get_bits(gbc, 2)];
            if(hdr->channel_mode & 4)
                hdr->surround_mix_level = surround_levels[get_bits(gbc, 2)];
        }
        hdr->lfe_on = get_bits1(gbc);

        hdr->sr_shift = FFMAX(hdr->bitstream_id, 8) - 8;
        hdr->sample_rate = ff_ac3_sample_rate_tab[hdr->sr_code] >> hdr->sr_shift;
        hdr->bit_rate = (ff_ac3_bitrate_tab[frame_size_code>>1] * 1000) >> hdr->sr_shift;
        hdr->channels = ff_ac3_channels_tab[hdr->channel_mode] + hdr->lfe_on;
        hdr->frame_size = ff_ac3_frame_size_tab[frame_size_code][hdr->sr_code] * 2;
        hdr->frame_type = EAC3_FRAME_TYPE_AC3_CONVERT;
        hdr->substreamid = 0;
    } else {
        hdr->crc1 = 0;
        hdr->frame_type = get_bits(gbc, 2);
        if(hdr->frame_type == EAC3_FRAME_TYPE_RESERVED)
            return AAC_AC3_PARSE_ERROR_FRAME_TYPE;

        hdr->substreamid = get_bits(gbc, 3);

        hdr->frame_size = (get_bits(gbc, 11) + 1) << 1;
        if(hdr->frame_size < AC3_HEADER_SIZE)
            return AAC_AC3_PARSE_ERROR_FRAME_SIZE;

        hdr->sr_code = get_bits(gbc, 2);
        if (hdr->sr_code == 3) {
            int sr_code2 = get_bits(gbc, 2);
            if(sr_code2 == 3)
                return AAC_AC3_PARSE_ERROR_SAMPLE_RATE;
            hdr->sample_rate = ff_ac3_sample_rate_tab[sr_code2] / 2;
            hdr->sr_shift = 1;
        } else {
            hdr->num_blocks = eac3_blocks[get_bits(gbc, 2)];
            hdr->sample_rate = ff_ac3_sample_rate_tab[hdr->sr_code];
            hdr->sr_shift = 0;
        }

        hdr->channel_mode = get_bits(gbc, 3);
        hdr->lfe_on = get_bits1(gbc);

        hdr->bit_rate = 8LL * hdr->frame_size * hdr->sample_rate /
                        (hdr->num_blocks * 256);
        hdr->channels = ff_ac3_channels_tab[hdr->channel_mode] + hdr->lfe_on;
    }
    hdr->channel_layout = avpriv_ac3_channel_layout_tab[hdr->channel_mode];
    if (hdr->lfe_on)
        hdr->channel_layout |= AV_CH_LOW_FREQUENCY;

    return 0;
}

int avpriv_ac3_parse_header(AC3HeaderInfo **phdr, const uint8_t *buf,
                            size_t size)
{
    GetBitContext gb;
    AC3HeaderInfo *hdr;
    int err;

    if (!*phdr)
        *phdr = malloc(sizeof(AC3HeaderInfo));
    if (!*phdr)
        return -12;
    hdr = *phdr;

    memset(hdr, 0, sizeof(AC3HeaderInfo));

    init_get_bits8(&gb, buf, size);
    err = ff_ac3_parse_header(&gb, hdr);
    if (err < 0)
        return -22;

    return get_bits_count(&gb);
}
