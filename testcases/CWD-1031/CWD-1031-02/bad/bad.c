#include <stdint.h>
#include <limits.h>
#include <stddef.h>

// FROM: libavutil/error.h
#define AVERROR_INVALIDDATA        (-0x3ebbb1b7)

// FROM: libavutil/attributes.h
#if defined(__GNUC__)
#define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > x || __GNUC__ == x && __GNUC_MINOR__ >= y)
#else
#define AV_GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1)
#define av_always_inline __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define av_always_inline __forceinline
#else
#define av_always_inline inline
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1)
#define av_noinline __attribute__((noinline))
#elif defined(_MSC_VER)
#define av_noinline __declspec(noinline)
#else
#define av_noinline
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1)
#define av_pure __attribute__((pure))
#else
#define av_pure
#endif

#if AV_GCC_VERSION_AT_LEAST(2,6)
#define av_const __attribute__((const))
#else
#define av_const
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1)
#define attribute_deprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#define attribute_deprecated __declspec(deprecated)
#else
#define attribute_deprecated
#endif

#if defined(__GNUC__)
#define av_unused __attribute__((unused))
#else
#define av_unused
#endif

#if AV_GCC_VERSION_AT_LEAST(3,1)
#define av_used __attribute__((used))
#else
#define av_used
#endif

#if AV_GCC_VERSION_AT_LEAST(3,3)
#define av_alias __attribute__((may_alias))
#else
#define av_alias
#endif

#if defined(__GNUC__)
#define av_uninit(x) x=x
#else
#define av_uninit(x) x
#endif

#ifdef __GNUC__
#define av_builtin_constant_p __builtin_constant_p
#define av_printf_format(fmtpos, attrpos) __attribute__((__format__(__printf__, fmtpos, attrpos)))
#else
#define av_builtin_constant_p(x) 0
#define av_printf_format(fmtpos, attrpos)
#endif

#if AV_GCC_VERSION_AT_LEAST(2,5)
#define av_noreturn __attribute__((noreturn))
#else
#define av_noreturn
#endif

// FROM: libavcodec/vlc.h
#define VLC_TYPE int16_t

typedef struct VLC {
    int bits;
    VLC_TYPE (*table)[2];
    int table_size, table_allocated;
} VLC;

typedef struct RL_VLC_ELEM {
    int16_t level;
    int8_t len;
    uint8_t run;
} RL_VLC_ELEM;

// FROM: libavcodec/mathops.h
#ifndef sign_extend
static inline av_const int sign_extend(int val, unsigned bits)
{
    unsigned shift = 8 * sizeof(int) - bits;
    union { unsigned u; int s; } v = { (unsigned) val << shift };
    return v.s >> shift;
}
#endif

#ifndef zero_extend
static inline av_const unsigned zero_extend(unsigned val, unsigned bits)
{
    return (val << ((8 * sizeof(int)) - bits)) >> ((8 * sizeof(int)) - bits);
}
#endif

#ifndef NEG_USR32
#define NEG_USR32(a,s) (((uint32_t)(a))>>(32-(s)))
#endif

// FROM: libavutil/common.h
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFSIGN(a) ((a) > 0 ? 1 : -1)

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

// FROM: libavutil/intmath.h
extern const uint8_t ff_log2_tab[256];

#ifndef ff_log2
#ifndef ff_log2_c
#define ff_log2 ff_log2_c
static av_always_inline av_const int ff_log2_c(unsigned int v)
{
    int n = 0;
    if (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    if (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    return n;
}
#endif
#endif

#ifndef ff_log2_16bit
#ifndef ff_log2_16bit_c
#define ff_log2_16bit ff_log2_16bit_c
static av_always_inline av_const int ff_log2_16bit_c(unsigned int v)
{
    int n = 0;
    if (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    return n;
}
#endif
#endif

#define av_log2       ff_log2
#define av_log2_16bit ff_log2_16bit

// FROM: libavutil/log2_tab.c
extern const uint8_t ff_log2_tab[256];

// FROM: libavutil/bswap.h
#define AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#define AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#define AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#define AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#ifndef av_bswap16
static av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    return x;
}
#endif

#ifndef av_bswap32
static av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    return AV_BSWAP32C(x);
}
#endif

#ifndef av_bswap64
static inline uint64_t av_const av_bswap64(uint64_t x)
{
    return (uint64_t)av_bswap32(x) << 32 | av_bswap32(x >> 32);
}
#endif

// FROM: libavutil/intreadwrite.h
typedef union {
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8 [8];
    double   f64;
    float    f32[2];
} av_alias av_alias64;

typedef union {
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8 [4];
    float    f32;
} av_alias av_alias32;

typedef union {
    uint16_t u16;
    uint8_t  u8 [2];
} av_alias av_alias16;

#ifndef AV_RB32
#define AV_RB32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[0] << 24) |    \
               (((const uint8_t*)(x))[1] << 16) |    \
               (((const uint8_t*)(x))[2] <<  8) |    \
                ((const uint8_t*)(x))[3])
#endif

#ifndef AV_RB64
#define AV_RB64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[0] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[1] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[6] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[7])
#endif

#ifndef AV_RL32
#define AV_RL32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[3] << 24) |    \
               (((const uint8_t*)(x))[2] << 16) |    \
               (((const uint8_t*)(x))[1] <<  8) |    \
                ((const uint8_t*)(x))[0])
#endif

#ifndef AV_RL64
#define AV_RL64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[7] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[6] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[1] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[0])
#endif

// FROM: libavcodec/get_bits.h
#ifndef UNCHECKED_BITSTREAM_READER
#define CONFIG_SAFE_BITSTREAM_READER 1
#define UNCHECKED_BITSTREAM_READER !CONFIG_SAFE_BITSTREAM_READER
#endif

typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
#if !UNCHECKED_BITSTREAM_READER
    int size_in_bits_plus8;
#endif
} GetBitContext;

#ifdef LONG_BITSTREAM_READER
#   define MIN_CACHE_BITS 32
#else
#   define MIN_CACHE_BITS 25
#endif

#define OPEN_READER_NOSIZE(name, gb)            \
    unsigned int name ## _index = (gb)->index;  \
    unsigned int av_unused name ## _cache = 0

#if UNCHECKED_BITSTREAM_READER
#define OPEN_READER(name, gb) OPEN_READER_NOSIZE(name, gb)

#define BITS_AVAILABLE(name, gb) 1
#else
#define OPEN_READER(name, gb)                   \
    OPEN_READER_NOSIZE(name, gb);               \
    unsigned int name ## _size_plus8 = (gb)->size_in_bits_plus8

#define BITS_AVAILABLE(name, gb) name ## _index < name ## _size_plus8
#endif

#define CLOSE_READER(name, gb) (gb)->index = name ## _index

#ifdef BITSTREAM_READER_LE

# ifdef LONG_BITSTREAM_READER
#   define UPDATE_CACHE(name, gb) name ## _cache = \
        AV_RL64((gb)->buffer + (name ## _index >> 3)) >> (name ## _index & 7)
# else
#   define UPDATE_CACHE(name, gb) name ## _cache = \
        AV_RL32((gb)->buffer + (name ## _index >> 3)) >> (name ## _index & 7)
# endif

# define SKIP_CACHE(name, gb, num) name ## _cache >>= (num)

#else

# ifdef LONG_BITSTREAM_READER
#   define UPDATE_CACHE(name, gb) name ## _cache = \
        AV_RB64((gb)->buffer + (name ## _index >> 3)) >> (32 - (name ## _index & 7))
# else
#   define UPDATE_CACHE(name, gb) name ## _cache = \
        AV_RB32((gb)->buffer + (name ## _index >> 3)) << (name ## _index & 7)
# endif

# define SKIP_CACHE(name, gb, num) name ## _cache <<= (num)

#endif

#if UNCHECKED_BITSTREAM_READER
#   define SKIP_COUNTER(name, gb, num) name ## _index += (num)
#else
#   define SKIP_COUNTER(name, gb, num) \
    name ## _index = FFMIN(name ## _size_plus8, name ## _index + (num))
#endif

#define SKIP_BITS(name, gb, num)                \
    do {                                        \
        SKIP_CACHE(name, gb, num);              \
        SKIP_COUNTER(name, gb, num);            \
    } while (0)

#define LAST_SKIP_BITS(name, gb, num) SKIP_COUNTER(name, gb, num)

#ifdef BITSTREAM_READER_LE
#   define SHOW_UBITS(name, gb, num) zero_extend(name ## _cache, num)
#   define SHOW_SBITS(name, gb, num) sign_extend(name ## _cache, num)
#else
#   define SHOW_UBITS(name, gb, num) NEG_USR32(name ## _cache, num)
#   define SHOW_SBITS(name, gb, num) sign_extend(name ## _cache, num)
#endif

#define GET_CACHE(name, gb) ((uint32_t) name ## _cache)

// FROM: libavcodec/golomb.c
extern const uint8_t ff_golomb_vlc_len[512];
extern const uint8_t ff_ue_golomb_vlc_code[512];

// FROM: libavcodec/h264.h
#define QP_MAX_NUM (51 + 2 * 6)

enum {
    H264_NAL_SLICE           = 1,
    H264_NAL_DPA             = 2,
    H264_NAL_DPB             = 3,
    H264_NAL_DPC             = 4,
    H264_NAL_IDR_SLICE       = 5,
    H264_NAL_SEI             = 6,
    H264_NAL_SPS             = 7,
    H264_NAL_PPS             = 8,
    H264_NAL_AUD             = 9,
    H264_NAL_END_SEQUENCE    = 10,
    H264_NAL_END_STREAM      = 11,
    H264_NAL_FILLER_DATA     = 12,
    H264_NAL_SPS_EXT         = 13,
    H264_NAL_AUXILIARY_SLICE = 19,
};

// FROM: libavcodec/h2645_parse.h
typedef struct H2645NAL {
    uint8_t *rbsp_buffer;
    int rbsp_buffer_size;

    int size;
    const uint8_t *data;

    int size_bits;

    int raw_size;
    const uint8_t *raw_data;

    GetBitContext gb;

    int type;

    int temporal_id;

    int ref_idc;
} H2645NAL;

typedef struct H2645Packet {
    H2645NAL *nals;
    int nb_nals;
    int nals_allocated;
} H2645Packet;

// FROM: libavcodec/h264dec.h (partial - only needed fields)
#define H264_MAX_PICTURE_COUNT 32
#define MAX_DELAYED_PIC_COUNT 16
#define MAX_SLICES 32
#define MAX_MMCO_COUNT 64

typedef struct H264Context {
    H2645Packet pkt;
} H264Context;

// FROM: vastdb-eval/cves/2017-1000460/snippet.c
static inline int init_get_bits(GetBitContext *s, const uint8_t *buffer,
                                int bit_size)
{
    int buffer_size;
    int ret = 0;

    if (bit_size > INT_MAX - 7 || bit_size < 0 || !buffer) {
        bit_size    = 0;
        buffer      = NULL;
        ret         = AVERROR_INVALIDDATA;
    }

    buffer_size = (bit_size + 7) >> 3;

    s->buffer             = buffer;
    s->size_in_bits       = bit_size;
#if !UNCHECKED_BITSTREAM_READER
    s->size_in_bits_plus8 = bit_size + 8;
#endif
    s->buffer_end         = buffer + buffer_size;
    s->index              = 0;

    return ret;
}

static inline int get_ue_golomb(GetBitContext *gb)
{
    unsigned int buf;

    OPEN_READER(re, gb);
    UPDATE_CACHE(re, gb);
    buf = GET_CACHE(re, gb);

    if (buf >= (1 << 27)) {
        buf >>= 32 - 9;
        LAST_SKIP_BITS(re, gb, ff_golomb_vlc_len[buf]);
        CLOSE_READER(re, gb);

        return ff_ue_golomb_vlc_code[buf];
    } else {
        int log = 2 * av_log2(buf) - 31;
        buf >>= log;
        buf--;
        LAST_SKIP_BITS(re, gb, 32 - log);
        CLOSE_READER(re, gb);

        return buf;
    }
}

static int get_last_needed_nal(H264Context *h)
{
    int nals_needed = 0;
    int i;

    for (i = 0; i < h->pkt.nb_nals; i++) {
        H2645NAL *nal = &h->pkt.nals[i];
        GetBitContext gb;

        switch (nal->type) {
        case H264_NAL_SPS:
        case H264_NAL_PPS:
            nals_needed = i;
            break;
        case H264_NAL_DPA:
        case H264_NAL_IDR_SLICE:
        case H264_NAL_SLICE:
            init_get_bits(&gb, nal->data + 1, (nal->size - 1) * 8);
            if (!get_ue_golomb(&gb))
                nals_needed = i;
        }
    }

    return nals_needed;
}
