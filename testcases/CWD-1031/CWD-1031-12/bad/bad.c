#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>

#ifndef HAVE_AV_CONFIG_H
#define HAVE_AV_CONFIG_H 1
#endif

#define av_cold __attribute__((cold))
#define AVERROR_INVALIDDATA (-1094995529)
#define AVERROR_PATCHWELCOME (-1297349680)
#define AVERROR(ENOSPC) (-(ENOSPC))
#define ENOMEM 12
#define AV_LOG_ERROR 16
#define AV_LOG_WARNING 24
#define AV_CHANNEL_ORDER_UNSPEC 0
#define AV_SAMPLE_FMT_S16 1
#define AV_SAMPLE_FMT_S32 2
#define AV_SAMPLE_FMT_FLT 3
#define FF_SANE_NB_CHANNELS 128
#define FFMIN(a,b) ((a) < (b) ? (a) : (b))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
#define MUL64(a,b) ((int64_t)(a) * (b))
#define AV_RB32(x) (((const uint8_t*)(x))[0] << 24 | \
                    (((const uint8_t*)(x))[1]) << 16 | \
                    (((const uint8_t*)(x))[2]) <<  8 | \
                    (((const uint8_t*)(x))[3]))
#define HAVE_BIGENDIAN 0
#define PTRDIFF_SPECIFIER "ld"
#define av_assert0(x) do { } while (0)
#define AV_EF_CRCCHECK 1
#define AV_EF_CAREFUL 2
#define AV_EF_EXPLODE 4

typedef struct AVChannelLayout {
    int order;
    int nb_channels;
} AVChannelLayout;

typedef struct AVFrame {
    int nb_samples;
    uint8_t *data[8];
} AVFrame;

typedef struct AVPacket {
    const uint8_t *data;
    int size;
} AVPacket;

typedef struct AVCodecContext {
    AVChannelLayout ch_layout;
    void *priv_data;
    const uint8_t *extradata;
    int extradata_size;
    int sample_fmt;
    int bits_per_raw_sample;
    int sample_rate;
    int err_recognition;
} AVCodecContext;

#define EXP_BIAS 127
#define MANT_BITS 23

typedef struct SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  exp;
} SoftFloat_IEEE754;

static const SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
static const SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

static inline SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    while( sf.mant >= 0x1000000UL ) {
        sf.exp++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    return sf;
}

static inline SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, int e) {
    int sign = 0;
    if (n < 0) {
        sign = 1;
        n    *= -1;
    }
    return av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_BITS, 0 + e});
}

static inline SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    return ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

static inline int av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    if(a.exp >= 0) return a.mant <<  a.exp ;
    else           return a.mant >>(-a.exp);
}

static inline SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, exp, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_BITS) / (b.mant| 0x00800000UL));
    exp  = a.exp - b.exp;
    return av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, exp});
}

static inline int av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    if (a.sign != b.sign) return 0;
    if (a.mant != b.mant) return 0;
    if (a.exp  != b.exp ) return 0;
    return 1;
}

typedef struct GetBitContext {
    const uint8_t *buffer;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

static inline int get_bits_left(GetBitContext *gb) {
    return gb->size_in_bits - gb->index;
}

static inline void skip_bits_long(GetBitContext *gb, int n) {
    gb->index += n;
}

static inline int get_bits1(GetBitContext *gb) {
    int bit = (gb->buffer[gb->index / 8] >> (7 - (gb->index & 7))) & 1;
    gb->index += 1;
    return bit;
}

static inline void align_get_bits(GetBitContext *gb) {
    gb->index = (gb->index + 7) & ~7;
}

static inline unsigned int get_bits(GetBitContext *gb, int n) {
    unsigned int result = 0;
    for (int i = 0; i < n; i++) {
        result = (result << 1) | get_bits1(gb);
    }
    return result;
}

static inline int32_t get_sbits_long(GetBitContext *gb, int n) {
    uint32_t val = get_bits(gb, n);
    if (val & (1U << (n - 1)))
        return val | ~((1U << n) - 1);
    return val;
}

static inline uint32_t get_bits_long(GetBitContext *gb, int n) {
    return get_bits(gb, n);
}

static inline int get_bitsz(GetBitContext *gb, int n) {
    return get_bits(gb, n);
}

static inline void skip_bits(GetBitContext *gb, int n) {
    gb->index += n;
}

static inline int init_get_bits8(GetBitContext *gb, const uint8_t *buffer, int byte_size) {
    gb->buffer = buffer;
    gb->index = 0;
    gb->size_in_bits = byte_size * 8;
    gb->size_in_bits_plus8 = (byte_size + 1) * 8;
    return 0;
}

enum RA_Flag {
    RA_FLAG_NONE,
    RA_FLAG_FRAMES,
    RA_FLAG_HEADER
};

typedef struct ALSpecificConfig {
    uint32_t samples;
    int resolution;
    int floating;
    int msb_first;
    int frame_length;
    int ra_distance;
    enum RA_Flag ra_flag;
    int adapt_order;
    int coef_table;
    int long_term_prediction;
    int max_order;
    int block_switching;
    int bgmc;
    int sb_part;
    int joint_stereo;
    int mc_coding;
    int chan_config;
    int chan_sort;
    int rlslms;
    int chan_config_info;
    int *chan_pos;
    int crc_enabled;
} ALSSpecificConfig;

typedef struct ALSChannelData {
    int stop_flag;
    int master_channel;
    int time_diff_flag;
    int time_diff_sign;
    int time_diff_index;
    int weighting[6];
} ALSChannelData;

typedef struct BswapDSPContext {
    void (*bswap_buf)(uint32_t *dst, const uint32_t *src, int w);
    void (*bswap16_buf)(uint16_t *dst, const uint16_t *src, int len);
} BswapDSPContext;

typedef struct MLZ {
    int dic_code_bit;
    int current_dic_index_max;
    unsigned int bump_code;
    unsigned int flush_code;
    int next_code;
    int freeze_flag;
    void* dict;
    void* context;
} MLZ;

typedef struct ALSDecContext {
    AVCodecContext *avctx;
    ALSSpecificConfig sconf;
    GetBitContext gb;
    BswapDSPContext bdsp;
    const void *crc_table;
    uint32_t crc_org;
    uint32_t crc;
    unsigned int cur_frame_length;
    unsigned int frame_id;
    unsigned int js_switch;
    unsigned int cs_switch;
    unsigned int num_blocks;
    unsigned int s_max;
    uint8_t *bgmc_lut;
    int *bgmc_lut_status;
    int ltp_lag_length;
    int *const_block;
    unsigned int *shift_lsbs;
    unsigned int *opt_order;
    int *store_prev_samples;
    int *use_ltp;
    int *ltp_lag;
    int **ltp_gain;
    int *ltp_gain_buffer;
    int32_t **quant_cof;
    int32_t *quant_cof_buffer;
    int32_t **lpc_cof;
    int32_t *lpc_cof_buffer;
    int32_t *lpc_cof_reversed_buffer;
    ALSChannelData **chan_data;
    ALSChannelData *chan_data_buffer;
    int *reverted_channels;
    int32_t *prev_raw_samples;
    int32_t **raw_samples;
    int32_t *raw_buffer;
    uint8_t *crc_buffer;
    MLZ* mlz;
    SoftFloat_IEEE754 *acf;
    int *last_acf_mantissa;
    int *shift_value;
    int *last_shift_value;
    int **raw_mantissa;
    unsigned char *larray;
    int *nbits;
    int highest_decoded_channel;
} ALSDecContext;

typedef struct ALSBlockData {
    unsigned int block_length;
    unsigned int ra_block;
    int          *const_block;
    int          js_blocks;
    unsigned int *shift_lsbs;
    unsigned int *opt_order;
    int          *store_prev_samples;
    int          *use_ltp;
    int          *ltp_lag;
    int          *ltp_gain;
    int32_t      *quant_cof;
    int32_t      *lpc_cof;
    int32_t      *raw_samples;
    int32_t      *prev_raw_samples;
    int32_t      *raw_other;
} ALSBlockData;

int ff_bgmc_init(void *logctx, uint8_t **cf_lut, int **cf_lut_status);
void ff_bgmc_decode_init(GetBitContext *gb, unsigned int *h, unsigned int *l, unsigned int *v);
void ff_bgmc_decode_end(GetBitContext *gb);
void ff_bgmc_decode(GetBitContext *gb, unsigned int num, int32_t *dst,
                    int delta, unsigned int sx,
                    unsigned int *h, unsigned int *l, unsigned int *v,
                    uint8_t *cf_lut, int *cf_lut_status);
int ff_mlz_init_dict(void *context, MLZ *mlz);
void ff_mlz_flush_dict(MLZ *mlz);
int ff_mlz_decompression(MLZ* mlz, GetBitContext* gb, int size, unsigned char *buff);
void ff_bswapdsp_init(BswapDSPContext *c);
int avpriv_mpeg4audio_get_config2(void *c, const uint8_t *buf, int size, int sync_extension, void *logctx);
void av_channel_layout_uninit(AVChannelLayout *chl);

static const int8_t parcor_rice_table[3][20][2] = {
    { {-52, 4}, {-29, 5}, {-31, 4}, { 19, 4}, {-16, 4},
      { 12, 3}, { -7, 3}, {  9, 3}, { -5, 3}, {  6, 3},
      { -4, 3}, {  3, 3}, { -3, 2}, {  3, 2}, { -2, 2},
      {  3, 2}, { -1, 2}, {  2, 2}, { -1, 2}, {  2, 2} },
    { {-58, 3}, {-42, 4}, {-46, 4}, { 37, 5}, {-36, 4},
      { 29, 4}, {-29, 4}, { 25, 4}, {-23, 4}, { 20, 4},
      {-17, 4}, { 16, 4}, {-12, 4}, { 12, 3}, {-10, 4},
      {  7, 3}, { -4, 4}, {  3, 3}, { -1, 3}, {  1, 3} },
    { {-59, 3}, {-45, 5}, {-50, 4}, { 38, 4}, {-39, 4},
      { 32, 4}, {-30, 4}, { 25, 3}, {-23, 3}, { 20, 3},
      {-20, 3}, { 16, 3}, {-13, 3}, { 10, 3}, { -7, 3},
      {  3, 3}, {  0, 3}, { -1, 3}, {  2, 3}, { -1, 2} }
};

static const int16_t parcor_scaled_values[] = {
    -1048544 / 32, -1048288 / 32, -1047776 / 32, -1047008 / 32,
    -1045984 / 32, -1044704 / 32, -1043168 / 32, -1041376 / 32,
    -1039328 / 32, -1037024 / 32, -1034464 / 32, -1031648 / 32,
    -1028576 / 32, -1025248 / 32, -1021664 / 32, -1017824 / 32,
    -1013728 / 32, -1009376 / 32, -1004768 / 32,  -999904 / 32,
     -994784 / 32,  -989408 / 32,  -983776 / 32,  -977888 / 32,
     -971744 / 32,  -965344 / 32,  -958688 / 32,  -951776 / 32,
     -944608 / 32,  -937184 / 32,  -929504 / 32,  -921568 / 32,
     -913376 / 32,  -904928 / 32,  -896224 / 32,  -887264 / 32,
     -878048 / 32,  -868576 / 32,  -858848 / 32,  -848864 / 32,
     -838624 / 32,  -828128 / 32,  -817376 / 32,  -806368 / 32,
     -795104 / 32,  -783584 / 32,  -771808 / 32,  -759776 / 32,
     -747488 / 32,  -734944 / 32,  -722144 / 32,  -709088 / 32,
     -695776 / 32,  -682208 / 32,  -668384 / 32,  -654304 / 32,
     -639968 / 32,  -625376 / 32,  -610528 / 32,  -595424 / 32,
     -580064 / 32,  -564448 / 32,  -548576 / 32,  -532448 / 32,
     -516064 / 32,  -499424 / 32,  -482528 / 32,  -465376 / 32,
     -447968 / 32,  -430304 / 32,  -412384 / 32,  -394208 / 32,
     -375776 / 32,  -357088 / 32,  -338144 / 32,  -318944 / 32,
     -299488 / 32,  -279776 / 32,  -259808 / 32,  -239584 / 32,
     -219104 / 32,  -198368 / 32,  -177376 / 32,  -156128 / 32,
     -134624 / 32,  -112864 / 32,   -90848 / 32,   -68576 / 32,
      -46048 / 32,   -23264 / 32,     -224 / 32,    23072 / 32,
       46624 / 32,    70432 / 32,    94496 / 32,   118816 / 32,
      143392 / 32,   168224 / 32,   193312 / 32,   218656 / 32,
      244256 / 32,   270112 / 32,   296224 / 32,   322592 / 32,
      349216 / 32,   376096 / 32,   403232 / 32,   430624 / 32,
      458272 / 32,   486176 / 32,   514336 / 32,   542752 / 32,
      571424 / 32,   600352 / 32,   629536 / 32,   658976 / 32,
      688672 / 32,   718624 / 32,   748832 / 32,   779296 / 32,
      810016 / 32,   840992 / 32,   872224 / 32,   903712 / 32,
      935456 / 32,   967456 / 32,   999712 / 32,  1032224 / 32
};

static const uint8_t ltp_gain_values [4][4] = {
    { 0,  8, 16,  24},
    {32, 40, 48,  56},
    {64, 70, 76,  82},
    {88, 92, 96, 100}
};

static const int16_t mcc_weightings[] = {
    204,  192,  179,  166,  153,  140,  128,  115,
    102,   89,   76,   64,   51,   38,   25,   12,
      0,  -12,  -25,  -38,  -51,  -64,  -76,  -89,
   -102, -115, -128, -140, -153, -166, -179, -192
};

static const uint8_t tail_code[16][6] = {
    { 74, 44, 25, 13,  7, 3},
    { 68, 42, 24, 13,  7, 3},
    { 58, 39, 23, 13,  7, 3},
    {126, 70, 37, 19, 10, 5},
    {132, 70, 37, 20, 10, 5},
    {124, 70, 38, 20, 10, 5},
    {120, 69, 37, 20, 11, 5},
    {116, 67, 37, 20, 11, 5},
    {108, 66, 36, 20, 10, 5},
    {102, 62, 36, 20, 10, 5},
    { 88, 58, 34, 19, 10, 5},
    {162, 89, 49, 25, 13, 7},
    {156, 87, 49, 26, 14, 7},
    {150, 86, 47, 26, 14, 7},
    {142, 84, 47, 26, 14, 7},
    {131, 79, 46, 26, 14, 7}
};

int ff_bgmc_init(void *logctx, uint8_t **cf_lut, int **cf_lut_status);
void ff_bgmc_decode_init(GetBitContext *gb, unsigned int *h, unsigned int *l, unsigned int *v);
void ff_bgmc_decode_end(GetBitContext *gb);
void ff_bgmc_decode(GetBitContext *gb, unsigned int num, int32_t *dst,
                    int delta, unsigned int sx, unsigned int *h, unsigned int *l, unsigned int *v,
                    uint8_t *cf_lut, int *cf_lut_status);
int ff_mlz_init_dict(void *context, MLZ *mlz);
void ff_mlz_flush_dict(MLZ *mlz);
int ff_mlz_decompression(MLZ* mlz, GetBitContext* gb, int size, unsigned char *buff);
void ff_bswapdsp_init(BswapDSPContext *c);
int avpriv_mpeg4audio_get_config2(void *c, const uint8_t *buf, int size, int sync_extension, void *logctx);
void av_channel_layout_uninit(AVChannelLayout *chl);

void av_log(void *avcl, int level, const char *fmt, ...);

void* av_malloc_array(size_t nmemb, size_t size);
void* av_calloc(size_t nmemb, size_t size);
void* av_mallocz(size_t size);

int av_log2(unsigned int v);

const void* av_crc_get_table(int crc_type);
uint32_t av_crc(const void *table, uint32_t start_crc, const uint8_t *buffer, size_t length);

int ff_get_buffer(void *avctx, void *frame, int flags);

int av_ceil_log2(int x);

int av_clip(int a, int amin, int amax);

static int read_frame_data(ALSDecContext *ctx, unsigned int ra_frame);
static int read_diff_float_data(ALSDecContext *ctx, unsigned int ra_frame);
static int decode_frame(AVCodecContext *avctx, AVFrame *frame,
                        int *got_frame_ptr, AVPacket *avpkt);

static int read_specific_config(ALSDecContext *ctx);
static int check_specific_config(ALSDecContext *ctx);
unsigned int get_unary(GetBitContext *gb, int skip, int max);
static inline int get_bits_count(GetBitContext *gb);
int32_t decode_rice(GetBitContext *gb, unsigned int k);

uint32_t av_bswap32(uint32_t x);
uint16_t av_bswap16(uint16_t x);

int av_get_bytes_per_sample(int sample_fmt);

SoftFloat_IEEE754 multiply(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b);

void parcor_to_lpc(unsigned int k, const int32_t *par, int32_t *cof);
void parse_bs_info(const uint32_t bs_info, unsigned int n,
                   unsigned int div, unsigned int **div_blocks,
                   unsigned int *num_blocks);
void get_block_sizes(ALSDecContext *ctx, unsigned int *div_blocks, uint32_t *bs_info);
int read_const_block_data(ALSDecContext *ctx, ALSBlockData *bd);
void decode_const_block_data(ALSDecContext *ctx, ALSBlockData *bd);
int read_var_block_data(ALSDecContext *ctx, ALSBlockData *bd);
int decode_var_block_data(ALSDecContext *ctx, ALSBlockData *bd);
int read_block(ALSDecContext *ctx, ALSBlockData *bd);
int decode_block(ALSDecContext *ctx, ALSBlockData *bd);
void zero_remaining(unsigned int b, unsigned int b_max, const unsigned int *div_blocks, int32_t *buf);
int decode_blocks_ind(ALSDecContext *ctx, unsigned int ra_frame,
                      unsigned int c, const unsigned int *div_blocks,
                      unsigned int *js_blocks);
int decode_blocks(ALSDecContext *ctx, unsigned int ra_frame,
                  unsigned int c, const unsigned int *div_blocks,
                  unsigned int *js_blocks);
int read_channel_data(ALSDecContext *ctx, ALSChannelData *cd, int c);
int revert_channel_correlation(ALSDecContext *ctx, ALSBlockData *bd,
                                ALSChannelData **cd, int *reverted,
                                unsigned int offset, int c);
int als_weighting(GetBitContext *gb, int k, int off);

static int read_frame_data(ALSDecContext *ctx, unsigned int ra_frame)
{
    ALSSpecificConfig *sconf = &ctx->sconf;
    AVCodecContext *avctx    = ctx->avctx;
    GetBitContext *gb = &ctx->gb;
    unsigned int div_blocks[32];                ///< block sizes.
    int c;
    unsigned int js_blocks[2];
    int channels = avctx->ch_layout.nb_channels;
    uint32_t bs_info = 0;
    int ret;

    // skip the size of the ra unit if present in the frame
    if (sconf->ra_flag == RA_FLAG_FRAMES && ra_frame)
        skip_bits_long(gb, 32);

    if (sconf->mc_coding && sconf->joint_stereo) {
        ctx->js_switch = get_bits1(gb);
        align_get_bits(gb);
    }

    if (!sconf->mc_coding || ctx->js_switch) {
        int independent_bs = !sconf->joint_stereo;
        if (get_bits_left(gb) < 7*channels*ctx->num_blocks)
            return AVERROR_INVALIDDATA;
        for (c = 0; c < channels; c++) {
            js_blocks[0] = 0;
            js_blocks[1] = 0;

            get_block_sizes(ctx, div_blocks, &bs_info);

            // if joint_stereo and block_switching is set, independent decoding
            // is signaled via the first bit of bs_info
            if (sconf->joint_stereo && sconf->block_switching)
                if (bs_info >> 31)
                    independent_bs = 2;

            // if this is the last channel, it has to be decoded independently
            if (c == channels - 1 || (c & 1))
                independent_bs = 1;

            if (independent_bs) {
                ret = decode_blocks_ind(ctx, ra_frame, c,
                                        div_blocks, js_blocks);
                if (ret < 0)
                    return ret;
                independent_bs--;
            } else {
                ret = decode_blocks(ctx, ra_frame, c, div_blocks, js_blocks);
                if (ret < 0)
                    return ret;

                c++;
            }

            // store carryover raw samples
            memmove(ctx->raw_samples[c] - sconf->max_order,
                    ctx->raw_samples[c] - sconf->max_order + sconf->frame_length,
                    sizeof(*ctx->raw_samples[c]) * sconf->max_order);
            ctx->highest_decoded_channel = c;
        }
    } else { // multi-channel coding
        ALSBlockData   bd = { 0 };
        int            b, ret;
        int            *reverted_channels = ctx->reverted_channels;
        unsigned int   offset             = 0;

        for (c = 0; c < channels; c++)
            if (ctx->chan_data[c] < ctx->chan_data_buffer) {
                av_log(ctx->avctx, AV_LOG_ERROR, "Invalid channel data.\n");
                return AVERROR_INVALIDDATA;
            }

        memset(reverted_channels, 0, sizeof(*reverted_channels) * channels);

        bd.ra_block         = ra_frame;
        bd.prev_raw_samples = ctx->prev_raw_samples;

        get_block_sizes(ctx, div_blocks, &bs_info);

        for (b = 0; b < ctx->num_blocks; b++) {
            bd.block_length = div_blocks[b];
            if (bd.block_length <= 0) {
                av_log(ctx->avctx, AV_LOG_WARNING,
                       "Invalid block length %u in channel data!\n",
                       bd.block_length);
                continue;
            }

            for (c = 0; c < channels; c++) {
                bd.const_block = ctx->const_block + c;
                bd.shift_lsbs  = ctx->shift_lsbs + c;
                bd.opt_order   = ctx->opt_order + c;
                bd.store_prev_samples = ctx->store_prev_samples + c;
                bd.use_ltp     = ctx->use_ltp + c;
                bd.ltp_lag     = ctx->ltp_lag + c;
                bd.ltp_gain    = ctx->ltp_gain[c];
                bd.lpc_cof     = ctx->lpc_cof[c];
                bd.quant_cof   = ctx->quant_cof[c];
                bd.raw_samples = ctx->raw_samples[c] + offset;
                bd.raw_other   = NULL;

                if ((ret = read_block(ctx, &bd)) < 0)
                    return ret;
                if ((ret = read_channel_data(ctx, ctx->chan_data[c], c)) < 0)
                    return ret;
            }

            for (c = 0; c < channels; c++) {
                ret = revert_channel_correlation(ctx, &bd, ctx->chan_data,
                                                 reverted_channels, offset, c);
                if (ret < 0)
                    return ret;
            }
            for (c = 0; c < channels; c++) {
                bd.const_block = ctx->const_block + c;
                bd.shift_lsbs  = ctx->shift_lsbs + c;
                bd.opt_order   = ctx->opt_order + c;
                bd.store_prev_samples = ctx->store_prev_samples + c;
                bd.use_ltp     = ctx->use_ltp + c;
                bd.ltp_lag     = ctx->ltp_lag + c;
                bd.ltp_gain    = ctx->ltp_gain[c];
                bd.lpc_cof     = ctx->lpc_cof[c];
                bd.quant_cof   = ctx->quant_cof[c];
                bd.raw_samples = ctx->raw_samples[c] + offset;

                if ((ret = decode_block(ctx, &bd)) < 0)
                    return ret;

                ctx->highest_decoded_channel = FFMAX(ctx->highest_decoded_channel, c);
            }

            memset(reverted_channels, 0, channels * sizeof(*reverted_channels));
            offset      += div_blocks[b];
            bd.ra_block  = 0;
        }

        // store carryover raw samples
        for (c = 0; c < channels; c++)
            memmove(ctx->raw_samples[c] - sconf->max_order,
                    ctx->raw_samples[c] - sconf->max_order + sconf->frame_length,
                    sizeof(*ctx->raw_samples[c]) * sconf->max_order);
    }

    if (sconf->floating) {
        read_diff_float_data(ctx, ra_frame);
    }

    if (get_bits_left(gb) < 0) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Overread %d\n", -get_bits_left(gb));
        return AVERROR_INVALIDDATA;
    }

    return 0;
}

static av_cold int decode_init(AVCodecContext *avctx)
{
    unsigned int c;
    unsigned int channel_size;
    int num_buffers, ret;
    int channels;
    ALSDecContext *ctx = avctx->priv_data;
    ALSSpecificConfig *sconf = &ctx->sconf;
    ctx->avctx = avctx;

    if (!avctx->extradata) {
        av_log(avctx, AV_LOG_ERROR, "Missing required ALS extradata.\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = read_specific_config(ctx)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Reading ALSSpecificConfig failed.\n");
        return ret;
    }
    channels = avctx->ch_layout.nb_channels;

    if ((ret = check_specific_config(ctx)) < 0) {
        return ret;
    }

    if (sconf->bgmc) {
        ret = ff_bgmc_init(avctx, &ctx->bgmc_lut, &ctx->bgmc_lut_status);
        if (ret < 0)
            return ret;
    }
    if (sconf->floating) {
        avctx->sample_fmt          = AV_SAMPLE_FMT_FLT;
        avctx->bits_per_raw_sample = 32;
    } else {
        avctx->sample_fmt          = sconf->resolution > 1
                                     ? AV_SAMPLE_FMT_S32 : AV_SAMPLE_FMT_S16;
        avctx->bits_per_raw_sample = (sconf->resolution + 1) * 8;
        if (avctx->bits_per_raw_sample > 32) {
            av_log(avctx, AV_LOG_ERROR, "Bits per raw sample %d larger than 32.\n",
                   avctx->bits_per_raw_sample);
            return AVERROR_INVALIDDATA;
        }
    }

    // set maximum Rice parameter for progressive decoding based on resolution
    // This is not specified in 14496-3 but actually done by the reference
    // codec RM22 revision 2.
    ctx->s_max = sconf->resolution > 1 ? 31 : 15;

    // set lag value for long-term prediction
    ctx->ltp_lag_length = 8 + (avctx->sample_rate >=  96000) +
                              (avctx->sample_rate >= 192000);

    // allocate quantized parcor coefficient buffer
    num_buffers = sconf->mc_coding ? channels : 1;
    if (num_buffers * (uint64_t)num_buffers > INT_MAX) // protect chan_data_buffer allocation
        return AVERROR_INVALIDDATA;

    ctx->quant_cof        = av_malloc_array(num_buffers, sizeof(*ctx->quant_cof));
    ctx->lpc_cof          = av_malloc_array(num_buffers, sizeof(*ctx->lpc_cof));
    ctx->quant_cof_buffer = av_malloc_array(num_buffers * sconf->max_order,
                                            sizeof(*ctx->quant_cof_buffer));
    ctx->lpc_cof_buffer   = av_malloc_array(num_buffers * sconf->max_order,
                                            sizeof(*ctx->lpc_cof_buffer));
    ctx->lpc_cof_reversed_buffer = av_malloc_array(sconf->max_order,
                                                   sizeof(*ctx->lpc_cof_buffer));

    if (!ctx->quant_cof              || !ctx->lpc_cof        ||
        !ctx->quant_cof_buffer       || !ctx->lpc_cof_buffer ||
        !ctx->lpc_cof_reversed_buffer) {
        av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
        return AVERROR(ENOMEM);
    }

    // assign quantized parcor coefficient buffers
    for (c = 0; c < num_buffers; c++) {
        ctx->quant_cof[c] = ctx->quant_cof_buffer + c * sconf->max_order;
        ctx->lpc_cof[c]   = ctx->lpc_cof_buffer   + c * sconf->max_order;
    }

    // allocate and assign lag and gain data buffer for ltp mode
    ctx->const_block     = av_malloc_array(num_buffers, sizeof(*ctx->const_block));
    ctx->shift_lsbs      = av_malloc_array(num_buffers, sizeof(*ctx->shift_lsbs));
    ctx->opt_order       = av_malloc_array(num_buffers, sizeof(*ctx->opt_order));
    ctx->store_prev_samples = av_malloc_array(num_buffers, sizeof(*ctx->store_prev_samples));
    ctx->use_ltp         = av_calloc(num_buffers, sizeof(*ctx->use_ltp));
    ctx->ltp_lag         = av_malloc_array(num_buffers, sizeof(*ctx->ltp_lag));
    ctx->ltp_gain        = av_malloc_array(num_buffers, sizeof(*ctx->ltp_gain));
    ctx->ltp_gain_buffer = av_malloc_array(num_buffers * 5, sizeof(*ctx->ltp_gain_buffer));

    if (!ctx->const_block || !ctx->shift_lsbs ||
        !ctx->opt_order || !ctx->store_prev_samples ||
        !ctx->use_ltp  || !ctx->ltp_lag ||
        !ctx->ltp_gain || !ctx->ltp_gain_buffer) {
        av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
        return AVERROR(ENOMEM);
    }

    for (c = 0; c < num_buffers; c++)
        ctx->ltp_gain[c] = ctx->ltp_gain_buffer + c * 5;

    // allocate and assign channel data buffer for mcc mode
    if (sconf->mc_coding) {
        ctx->chan_data_buffer  = av_calloc(num_buffers * num_buffers,
                                           sizeof(*ctx->chan_data_buffer));
        ctx->chan_data         = av_calloc(num_buffers, sizeof(*ctx->chan_data));
        ctx->reverted_channels = av_malloc_array(num_buffers,
                                                 sizeof(*ctx->reverted_channels));

        if (!ctx->chan_data_buffer || !ctx->chan_data || !ctx->reverted_channels) {
            av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
            return AVERROR(ENOMEM);
        }

        for (c = 0; c < num_buffers; c++)
            ctx->chan_data[c] = ctx->chan_data_buffer + c * num_buffers;
    } else {
        ctx->chan_data         = NULL;
        ctx->chan_data_buffer  = NULL;
        ctx->reverted_channels = NULL;
    }

    if (sconf->floating) {
        ctx->acf               = av_malloc_array(channels, sizeof(*ctx->acf));
        ctx->shift_value       = av_calloc(channels, sizeof(*ctx->shift_value));
        ctx->last_shift_value  = av_calloc(channels, sizeof(*ctx->last_shift_value));
        ctx->last_acf_mantissa = av_calloc(channels, sizeof(*ctx->last_acf_mantissa));
        ctx->raw_mantissa      = av_calloc(channels, sizeof(*ctx->raw_mantissa));

        ctx->larray = av_malloc_array(ctx->cur_frame_length * 4, sizeof(*ctx->larray));
        ctx->nbits  = av_malloc_array(ctx->cur_frame_length, sizeof(*ctx->nbits));
        ctx->mlz    = av_mallocz(sizeof(*ctx->mlz));

        if (!ctx->mlz || !ctx->acf || !ctx->shift_value || !ctx->last_shift_value
            || !ctx->last_acf_mantissa || !ctx->raw_mantissa) {
            av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
            return AVERROR(ENOMEM);
        }

        ret = ff_mlz_init_dict(avctx, ctx->mlz);
        if (ret < 0)
            return ret;
        ff_mlz_flush_dict(ctx->mlz);

        for (c = 0; c < channels; ++c) {
            ctx->raw_mantissa[c] = av_calloc(ctx->cur_frame_length, sizeof(**ctx->raw_mantissa));
        }
    }

    channel_size      = sconf->frame_length + sconf->max_order;

    // allocate previous raw sample buffer
    ctx->prev_raw_samples = av_malloc_array(sconf->max_order, sizeof(*ctx->prev_raw_samples));
    ctx->raw_buffer       = av_calloc(channels * channel_size, sizeof(*ctx->raw_buffer));
    ctx->raw_samples      = av_malloc_array(channels, sizeof(*ctx->raw_samples));
    if (!ctx->prev_raw_samples || !ctx->raw_buffer|| !ctx->raw_samples) {
        av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
        return AVERROR(ENOMEM);
    }

    // assign raw samples buffers
    ctx->raw_samples[0] = ctx->raw_buffer + sconf->max_order;
    for (c = 1; c < channels; c++)
        ctx->raw_samples[c] = ctx->raw_samples[c - 1] + channel_size;

    // allocate crc buffer
    if (HAVE_BIGENDIAN != sconf->msb_first && sconf->crc_enabled &&
        (avctx->err_recognition & (AV_EF_CRCCHECK|AV_EF_CAREFUL))) {
        ctx->crc_buffer = av_malloc_array(ctx->cur_frame_length *
                                          channels *
                                          av_get_bytes_per_sample(avctx->sample_fmt),
                                          sizeof(*ctx->crc_buffer));
        if (!ctx->crc_buffer) {
            av_log(avctx, AV_LOG_ERROR, "Allocating buffer memory failed.\n");
            return AVERROR(ENOMEM);
        }
    }

    ff_bswapdsp_init(&ctx->bdsp);

    return 0;
}

static int read_diff_float_data(ALSDecContext *ctx, unsigned int ra_frame) {
    AVCodecContext *avctx   = ctx->avctx;
    GetBitContext *gb       = &ctx->gb;
    SoftFloat_IEEE754 *acf  = ctx->acf;
    int *shift_value        = ctx->shift_value;
    int *last_shift_value   = ctx->last_shift_value;
    int *last_acf_mantissa  = ctx->last_acf_mantissa;
    int **raw_mantissa      = ctx->raw_mantissa;
    int *nbits              = ctx->nbits;
    unsigned char *larray   = ctx->larray;
    int frame_length        = ctx->cur_frame_length;
    SoftFloat_IEEE754 scale = av_int2sf_ieee754(0x1u, 23);
    unsigned int partA_flag;
    unsigned int highest_byte;
    unsigned int shift_amp;
    uint32_t tmp_32;
    int use_acf;
    int nchars;
    int i;
    int c;
    long k;
    long nbits_aligned;
    unsigned long acc;
    unsigned long j;
    uint32_t sign;
    uint32_t e;
    uint32_t mantissa;

    skip_bits_long(gb, 32); //num_bytes_diff_float
    use_acf = get_bits1(gb);

    if (ra_frame) {
        memset(last_acf_mantissa, 0, avctx->ch_layout.nb_channels * sizeof(*last_acf_mantissa));
        memset(last_shift_value,  0, avctx->ch_layout.nb_channels * sizeof(*last_shift_value) );
        ff_mlz_flush_dict(ctx->mlz);
    }

    if (avctx->ch_layout.nb_channels * 8 > get_bits_left(gb))
        return AVERROR_INVALIDDATA;

    for (c = 0; c < avctx->ch_layout.nb_channels; ++c) {
        if (use_acf) {
            //acf_flag
            if (get_bits1(gb)) {
                tmp_32 = get_bits(gb, 23);
                last_acf_mantissa[c] = tmp_32;
            } else {
                tmp_32 = last_acf_mantissa[c];
            }
            acf[c] = av_bits2sf_ieee754(tmp_32);
        } else {
            acf[c] = FLOAT_1;
        }

        highest_byte = get_bits(gb, 2);
        partA_flag   = get_bits1(gb);
        shift_amp    = get_bits1(gb);

        if (shift_amp) {
            shift_value[c] = get_bits(gb, 8);
            last_shift_value[c] = shift_value[c];
        } else {
            shift_value[c] = last_shift_value[c];
        }

        if (partA_flag) {
            if (!get_bits1(gb)) { //uncompressed
                for (i = 0; i < frame_length; ++i) {
                    if (ctx->raw_samples[c][i] == 0) {
                        ctx->raw_mantissa[c][i] = get_bits_long(gb, 32);
                    }
                }
            } else { //compressed
                nchars = 0;
                for (i = 0; i < frame_length; ++i) {
                    if (ctx->raw_samples[c][i] == 0) {
                        nchars += 4;
                    }
                }

                tmp_32 = ff_mlz_decompression(ctx->mlz, gb, nchars, larray);
                if(tmp_32 != nchars) {
                    av_log(ctx->avctx, AV_LOG_ERROR, "Error in MLZ decompression (%"PRId32", %d).\n", tmp_32, nchars);
                    return AVERROR_INVALIDDATA;
                }

                for (i = 0; i < frame_length; ++i) {
                    ctx->raw_mantissa[c][i] = AV_RB32(larray);
                }
            }
        }

        //decode part B
        if (highest_byte) {
            for (i = 0; i < frame_length; ++i) {
                if (ctx->raw_samples[c][i] != 0) {
                    //The following logic is taken from Tabel 14.45 and 14.46 from the ISO spec
                    if (av_cmp_sf_ieee754(acf[c], FLOAT_1)) {
                        nbits[i] = 23 - av_log2(abs(ctx->raw_samples[c][i]));
                    } else {
                        nbits[i] = 23;
                    }
                    nbits[i] = FFMIN(nbits[i], highest_byte*8);
                }
            }

            if (!get_bits1(gb)) { //uncompressed
                for (i = 0; i < frame_length; ++i) {
                    if (ctx->raw_samples[c][i] != 0) {
                        raw_mantissa[c][i] = get_bitsz(gb, nbits[i]);
                    }
                }
            } else { //compressed
                nchars = 0;
                for (i = 0; i < frame_length; ++i) {
                    if (ctx->raw_samples[c][i]) {
                        nchars += (int) nbits[i] / 8;
                        if (nbits[i] & 7) {
                            ++nchars;
                        }
                    }
                }

                tmp_32 = ff_mlz_decompression(ctx->mlz, gb, nchars, larray);
                if(tmp_32 != nchars) {
                    av_log(ctx->avctx, AV_LOG_ERROR, "Error in MLZ decompression (%"PRId32", %d).\n", tmp_32, nchars);
                    return AVERROR_INVALIDDATA;
                }

                j = 0;
                for (i = 0; i < frame_length; ++i) {
                    if (ctx->raw_samples[c][i]) {
                        if (nbits[i] & 7) {
                            nbits_aligned = 8 * ((unsigned int)(nbits[i] / 8) + 1);
                        } else {
                            nbits_aligned = nbits[i];
                        }
                        acc = 0;
                        for (k = 0; k < nbits_aligned/8; ++k) {
                            acc = (acc << 8) + larray[j++];
                        }
                        acc >>= (nbits_aligned - nbits[i]);
                        raw_mantissa[c][i] = acc;
                    }
                }
            }
        }

        for (i = 0; i < frame_length; ++i) {
            SoftFloat_IEEE754 pcm_sf = av_int2sf_ieee754(ctx->raw_samples[c][i], 0);
            pcm_sf = av_div_sf_ieee754(pcm_sf, scale);

            if (ctx->raw_samples[c][i] != 0) {
                if (!av_cmp_sf_ieee754(acf[c], FLOAT_1)) {
                    pcm_sf = multiply(acf[c], pcm_sf);
                }

                sign = pcm_sf.sign;
                e = pcm_sf.exp;
                mantissa = (pcm_sf.mant | 0x800000) + raw_mantissa[c][i];

                while(mantissa >= 0x1000000) {
                    e++;
                    mantissa >>= 1;
                }

                if (mantissa) e += (shift_value[c] - 127);
                mantissa &= 0x007fffffUL;

                tmp_32 = (sign << 31) | ((e + EXP_BIAS) << 23) | (mantissa);
                ctx->raw_samples[c][i] = tmp_32;
            } else {
                ctx->raw_samples[c][i] = raw_mantissa[c][i] & 0x007fffffUL;
            }
        }
        align_get_bits(gb);
    }
    return 0;
}

static int decode_frame(AVCodecContext *avctx, AVFrame *frame,
                        int *got_frame_ptr, AVPacket *avpkt)
{
    ALSDecContext *ctx       = avctx->priv_data;
    ALSSpecificConfig *sconf = &ctx->sconf;
    const uint8_t *buffer    = avpkt->data;
    int buffer_size          = avpkt->size;
    int invalid_frame, ret;
    int channels = avctx->ch_layout.nb_channels;
    unsigned int c, sample, ra_frame, bytes_read, shift;

    if ((ret = init_get_bits8(&ctx->gb, buffer, buffer_size)) < 0)
        return ret;

    // In the case that the distance between random access frames is set to zero
    // (sconf->ra_distance == 0) no frame is treated as a random access frame.
    // For the first frame, if prediction is used, all samples used from the
    // previous frame are assumed to be zero.
    ra_frame = sconf->ra_distance && !(ctx->frame_id % sconf->ra_distance);

    // the last frame to decode might have a different length
    if (sconf->samples != 0xFFFFFFFF)
        ctx->cur_frame_length = FFMIN(sconf->samples - ctx->frame_id * (uint64_t) sconf->frame_length,
                                      sconf->frame_length);
    else
        ctx->cur_frame_length = sconf->frame_length;

    ctx->highest_decoded_channel = -1;
    // decode the frame data
    if ((invalid_frame = read_frame_data(ctx, ra_frame)) < 0)
        av_log(ctx->avctx, AV_LOG_WARNING,
               "Reading frame data failed. Skipping RA unit.\n");

    if (ctx->highest_decoded_channel == -1) {
        av_log(ctx->avctx, AV_LOG_WARNING,
               "No channel data decoded.\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->frame_id++;

    /* get output buffer */
    frame->nb_samples = ctx->cur_frame_length;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    // transform decoded frame into output format
    #define INTERLEAVE_OUTPUT(bps)                                                   \
    {                                                                                \
        int##bps##_t *dest = (int##bps##_t*)frame->data[0];                          \
        int32_t *raw_samples = ctx->raw_samples[0];                                  \
        int raw_step = channels > 1 ? ctx->raw_samples[1] - raw_samples : 1;         \
        shift = bps - ctx->avctx->bits_per_raw_sample;                               \
        if (!ctx->cs_switch) {                                                       \
            for (sample = 0; sample < ctx->cur_frame_length; sample++)               \
                for (c = 0; c < channels; c++)                                       \
                    *dest++ = raw_samples[c*raw_step + sample] * (1U << shift);      \
        } else {                                                                     \
            for (sample = 0; sample < ctx->cur_frame_length; sample++)               \
                for (c = 0; c < channels; c++)                                       \
                    *dest++ = raw_samples[sconf->chan_pos[c]*raw_step + sample] * (1U << shift);\
        }                                                                            \
    }

    if (ctx->avctx->bits_per_raw_sample <= 16) {
        INTERLEAVE_OUTPUT(16)
    } else {
        INTERLEAVE_OUTPUT(32)
    }

    // update CRC
    if (sconf->crc_enabled && (avctx->err_recognition & (AV_EF_CRCCHECK|AV_EF_CAREFUL))) {
        int swap = HAVE_BIGENDIAN != sconf->msb_first;

        if (ctx->avctx->bits_per_raw_sample == 24) {
            int32_t *src = (int32_t *)frame->data[0];

            for (sample = 0;
                 sample < ctx->cur_frame_length * channels;
                 sample++) {
                int32_t v;

                if (swap)
                    v = av_bswap32(src[sample]);
                else
                    v = src[sample];
                if (!HAVE_BIGENDIAN)
                    v >>= 8;

                ctx->crc = av_crc(ctx->crc_table, ctx->crc, (uint8_t*)(&v), 3);
            }
        } else {
            uint8_t *crc_source;

            if (swap) {
                if (ctx->avctx->bits_per_raw_sample <= 16) {
                    int16_t *src  = (int16_t*) frame->data[0];
                    int16_t *dest = (int16_t*) ctx->crc_buffer;
                    for (sample = 0;
                         sample < ctx->cur_frame_length * channels;
                         sample++)
                        *dest++ = av_bswap16(src[sample]);
                } else {
                    ctx->bdsp.bswap_buf((uint32_t *) ctx->crc_buffer,
                                        (uint32_t *) frame->data[0],
                                        ctx->cur_frame_length * channels);
                }
                crc_source = ctx->crc_buffer;
            } else {
                crc_source = frame->data[0];
            }

            ctx->crc = av_crc(ctx->crc_table, ctx->crc, crc_source,
                              ctx->cur_frame_length * channels *
                              av_get_bytes_per_sample(avctx->sample_fmt));
        }


        // check CRC sums if this is the last frame
        if (ctx->cur_frame_length != sconf->frame_length &&
            ctx->crc_org != ctx->crc) {
            av_log(avctx, AV_LOG_ERROR, "CRC error.\n");
            if (avctx->err_recognition & AV_EF_EXPLODE)
                return AVERROR_INVALIDDATA;
        }
    }

    *got_frame_ptr = 1;

    bytes_read = invalid_frame ? buffer_size :
                                 (get_bits_count(&ctx->gb) + 7) >> 3;

    return bytes_read;
}
