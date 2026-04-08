#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MKTAG(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA        (-(int)MKTAG( 'I','N','D','A'))
#define AVERROR_PATCHWELCOME       (-(int)MKTAG( 'P','A','W','E'))
#define AVERROR_ENOMEM             (-12)
#define EINVAL                     22

// FROM: libavutil/log.h
#define AV_LOG_WARNING  24

// FROM: libavcodec/avcodec.h
#define AV_INPUT_BUFFER_PADDING_SIZE 32
#define AV_CH_LOW_FREQUENCY          0x00000008

// FROM: libavutil/mem.h
void *av_mallocz(size_t size);

// FROM: libavutil/log.h
void av_log(void *avc, int level, const char *fmt, ...);

// FROM: libavutil/internal.h
void avpriv_request_sample(void *avc, const char *msg, ...);

// FROM: libavcodec/avcodec.h
typedef struct AVBufferRef {
    uint8_t *data;
    size_t   size;
    void *opaque;
    void (*ref)(void *opaque, uint8_t *data);
    void (*unref)(void *opaque, uint8_t *data);
} AVBufferRef;

// FROM: libavcodec/avcodec.h
typedef struct AVPacketSideData {
    uint8_t *data;
    int      size;
    int      type;
} AVPacketSideData;

// FROM: libavcodec/avcodec.h
typedef struct AVPacket {
    AVBufferRef *buf;
    int64_t pts;
    int64_t dts;
    uint8_t *data;
    int   size;
    int   stream_index;
    int   flags;
    AVPacketSideData *side_data;
    int side_data_elems;
    int64_t duration;
    int64_t pos;
} AVPacket;

// FROM: libavcodec/get_bits.h
typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

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

// FROM: libavcodec/ac3.h
typedef enum AC3DolbySurroundMode {
    AC3_DSURMOD_NOTINDICATED = 0,
    AC3_DSURMOD_OFF,
    AC3_DSURMOD_ON,
    AC3_DSURMOD_RESERVED
} AC3DolbySurroundMode;

// FROM: libavcodec/ac3.h
typedef enum {
    EAC3_FRAME_TYPE_INDEPENDENT = 0,
    EAC3_FRAME_TYPE_DEPENDENT,
    EAC3_FRAME_TYPE_AC3_CONVERT,
    EAC3_FRAME_TYPE_RESERVED
} EAC3FrameType;

// FROM: libavcodec/ac3.h
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

// FROM: libavcodec/ac3_parser.h
int avpriv_ac3_parse_header(GetBitContext *gbc, AC3HeaderInfo **hdr);

// FROM: libavformat/movenc.h
typedef struct MOVTrack {
    int mode;
    int entry;
    unsigned timescale;
    uint64_t time;
    int64_t track_duration;
    int last_sample_is_subtitle_end;
    long sample_count;
    long sample_size;
    long chunkCount;
    int has_keyframes;
    uint32_t flags;
    uint32_t timecode_flags;
    int language;
    int track_id;
    int tag;
    void *st;
    void *par;
    int multichannel_as_mono;
    int vos_len;
    uint8_t *vos_data;
    void *cluster;
    unsigned cluster_capacity;
    int audio_vbr;
    int height;
    uint32_t tref_tag;
    int tref_id;
    int64_t start_dts;
    int64_t start_cts;
    int64_t end_pts;
    int end_reliable;
    int hint_track;
    int src_track;
    void *rtp_ctx;
    uint32_t prev_rtp_ts;
    int64_t cur_rtp_ts_unwrapped;
    uint32_t max_packet_size;
    int64_t default_duration;
    uint32_t default_sample_flags;
    uint32_t default_size;
    void *sample_queue;
    void *mdat_buf;
    int64_t data_offset;
    int64_t frag_start;
    int frag_discont;
    int entries_flushed;
    int nb_frag_info;
    void *frag_info;
    unsigned frag_info_capacity;
    struct {
        int first_packet_seq;
        int first_packet_entry;
        int first_packet_seen;
        int first_frag_written;
        int packet_seq;
        int packet_entry;
        int slices;
    } vc1_info;
    void *eac3_priv;
    void *cenc;
    uint32_t palette[256];
    int pal_done;
    int is_unaligned_qt_rgb;
} MOVTrack;

// FROM: libavformat/movenc.h
typedef struct MOVMuxContext {
    const void *av_class;
    int mode;
    int64_t time;
    int nb_streams;
    int nb_meta_tmcd;
    int chapter_track;
    int64_t mdat_pos;
    uint64_t mdat_size;
    MOVTrack *tracks;
    int flags;
    int rtp_flags;
    int iods_skip;
    int iods_video_profile;
    int iods_audio_profile;
    int moov_written;
    int fragments;
    int max_fragment_duration;
    int min_fragment_duration;
    int max_fragment_size;
    int ism_lookahead;
    void *mdat_buf;
    int first_trun;
    int reserved_moov_size;
    int64_t reserved_header_pos;
    char *major_brand;
    int per_stream_grouping;
    void *fc;
    int use_editlist;
    float gamma;
    int frag_interleave;
    int missing_duration_warned;
    char *encryption_scheme_str;
    int encryption_scheme;
    uint8_t *encryption_key;
    int encryption_key_len;
    uint8_t *encryption_kid;
    int encryption_kid_len;
    int need_rewrite_extradata;
    int use_stream_ids_as_track_ids;
    int track_ids_ok;
    int write_tmcd;
} MOVMuxContext;

// FROM: libavformat/movenc.c
struct eac3_info {
    AVPacket pkt;
    uint8_t ec3_done;
    uint8_t num_blocks;
    uint16_t data_rate;
    uint8_t  num_ind_sub;
    struct {
        uint8_t fscod;
        uint8_t bsid;
        uint8_t bsmod;
        uint8_t acmod;
        uint8_t lfeon;
        uint8_t num_dep_sub;
        uint16_t chan_loc;
    } substream[1];
};

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

// FROM: libavutil/common.h
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))

// FROM: libavcodec/ac3tab.c
static const uint16_t ff_ac3_frame_size_tab[38][3];
static const uint8_t ff_ac3_channels_tab[8];
static const uint16_t ff_ac3_sample_rate_tab[3];
static const uint16_t ff_ac3_bitrate_tab[19];
static const uint16_t avpriv_ac3_channel_layout_tab[8];

// FROM: libavcodec/ac3_parser.c
#define AC3_HEADER_SIZE 7

static const uint8_t eac3_blocks[4];
static const uint8_t center_levels[4];
static const uint8_t surround_levels[4];

// FROM: libavcodec/get_bits.h
static inline unsigned int get_bits(GetBitContext *s, int n)
{
    unsigned int tmp;
    int i;
    tmp = 0;
    for (i = 0; i < n; i++) {
        tmp = (tmp << 1) | ((s->buffer[s->index >> 3] >> (7 - (s->index & 7))) & 1);
        s->index++;
    }
    return tmp;
}

// FROM: libavcodec/get_bits.h
static inline unsigned int show_bits_long(GetBitContext *s, int n)
{
    GetBitContext gb = *s;
    return get_bits(&gb, n);
}

// FROM: libavcodec/get_bits.h
static inline void skip_bits(GetBitContext *s, int n)
{
    s->index += n;
}

// FROM: libavcodec/get_bits.h
static inline unsigned int get_bits1(GetBitContext *s)
{
    unsigned int result;
    result = (s->buffer[s->index >> 3] >> (7 - (s->index & 7))) & 1;
    s->index++;
    return result;
}

// FROM: libavcodec/get_bits.h
static inline int init_get_bits(GetBitContext *s, const uint8_t *buffer, int bit_size)
{
    s->buffer = buffer;
    s->size_in_bits = bit_size;
    s->size_in_bits_plus8 = bit_size + 8;
    s->buffer_end = buffer + (bit_size + 7) / 8;
    s->index = 0;
    return 0;
}

// FROM: libavcodec/avpacket.c
int av_copy_packet(AVPacket *dst, const AVPacket *src);

// FROM: libavcodec/avpacket.c
int av_grow_packet(AVPacket *pkt, int grow_by);

// FROM: libavcodec/avpacket.c
int av_copy_packet_side_data(AVPacket *dst, const AVPacket *src);

// FROM: libavcodec/avpacket.c
void av_packet_unref(AVPacket *pkt);

// FROM: libavcodec/avpacket.c
int av_copy_packet(AVPacket *dst, const AVPacket *src)
{
    *dst = *src;
    if (src->size > 0) {
        dst->data = malloc(src->size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!dst->data)
            return -12;
        memcpy(dst->data, src->data, src->size);
        memset(dst->data + src->size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    }
    return 0;
}

// FROM: libavcodec/avpacket.c
int av_grow_packet(AVPacket *pkt, int grow_by)
{
    int new_size;
    uint8_t *new_data;
    
    if (grow_by < 0)
        return -1;
    
    new_size = pkt->size + grow_by + AV_INPUT_BUFFER_PADDING_SIZE;
    new_data = realloc(pkt->data, new_size);
    if (!new_data)
        return -12;
    
    pkt->data = new_data;
    pkt->size += grow_by;
    memset(pkt->data + pkt->size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    return 0;
}

// FROM: libavcodec/avpacket.c
int av_copy_packet_side_data(AVPacket *dst, const AVPacket *src)
{
    if (src->side_data_elems > 0) {
        dst->side_data = malloc(src->side_data_elems * sizeof(AVPacketSideData));
        if (!dst->side_data)
            return -12;
        memcpy(dst->side_data, src->side_data, src->side_data_elems * sizeof(AVPacketSideData));
        dst->side_data_elems = src->side_data_elems;
    }
    return 0;
}

// FROM: libavcodec/avpacket.c
void av_packet_unref(AVPacket *pkt)
{
    if (pkt->data) {
        free(pkt->data);
        pkt->data = NULL;
    }
    if (pkt->side_data) {
        free(pkt->side_data);
        pkt->side_data = NULL;
    }
    pkt->size = 0;
    pkt->side_data_elems = 0;
}

// FROM: libavformat/movenc.c
static int handle_eac3(MOVMuxContext *mov, AVPacket *pkt, MOVTrack *track)
{
    GetBitContext gbc;
    AC3HeaderInfo tmp, *hdr = &tmp;
    struct eac3_info *info;
    int num_blocks;

    if (!track->eac3_priv && !(track->eac3_priv = av_mallocz(sizeof(*info))))
        return AVERROR_ENOMEM;
    info = track->eac3_priv;

    init_get_bits(&gbc, pkt->data, pkt->size * 8);
    if (avpriv_ac3_parse_header(&gbc, &hdr) < 0) {
        /* drop the packets until we see a good one */
        if (!track->entry) {
            av_log(mov, AV_LOG_WARNING, "Dropping invalid packet from start of the stream\n");
            return 0;
        }
        return AVERROR_INVALIDDATA;
    }

    info->data_rate = FFMAX(info->data_rate, hdr->bit_rate / 1000);
    num_blocks = hdr->num_blocks;

    if (!info->ec3_done) {
        /* AC-3 substream must be the first one */
        if (hdr->bitstream_id <= 10 && hdr->substreamid != 0)
            return AVERROR(EINVAL);

        /* this should always be the case, given that our AC-3 parser
         * concatenates dependent frames to their independent parent */
        if (hdr->frame_type == EAC3_FRAME_TYPE_INDEPENDENT) {
            /* substream ids must be incremental */
            if (hdr->substreamid > info->num_ind_sub + 1)
                return AVERROR(EINVAL);

            if (hdr->substreamid == info->num_ind_sub + 1) {
                //info->num_ind_sub++;
                avpriv_request_sample(track->par, "Multiple independent substreams");
                return AVERROR_PATCHWELCOME;
            } else if (hdr->substreamid < info->num_ind_sub ||
                       hdr->substreamid == 0 && info->substream[0].bsid) {
                info->ec3_done = 1;
                goto concatenate;
            }
        } else {
            if (hdr->substreamid != 0) {
                avpriv_request_sample(mov->fc, "Multiple non EAC3 independent substreams");
                return AVERROR_PATCHWELCOME;
            }
        }

        /* fill the info needed for the "dec3" atom */
        info->substream[hdr->substreamid].fscod = hdr->sr_code;
        info->substream[hdr->substreamid].bsid  = hdr->bitstream_id;
        info->substream[hdr->substreamid].bsmod = hdr->bitstream_mode;
        info->substream[hdr->substreamid].acmod = hdr->channel_mode;
        info->substream[hdr->substreamid].lfeon = hdr->lfe_on;

        /* Parse dependent substream(s), if any */
        if (pkt->size != hdr->frame_size) {
            int cumul_size = hdr->frame_size;
            int parent = hdr->substreamid;

            while (cumul_size != pkt->size) {
                int i;
                init_get_bits(&gbc, pkt->data + cumul_size, (pkt->size - cumul_size) * 8);
                if (avpriv_ac3_parse_header(&gbc, &hdr) < 0)
                    return AVERROR_INVALIDDATA;
                if (hdr->frame_type != EAC3_FRAME_TYPE_DEPENDENT)
                    return AVERROR(EINVAL);
                cumul_size += hdr->frame_size;
                info->substream[parent].num_dep_sub++;

                /* header is parsed up to lfeon, but custom channel map may be needed */
                /* skip bsid */
                skip_bits(&gbc, 5);
                /* skip volume control params */
                for (i = 0; i < (hdr->channel_mode ? 1 : 2); i++) {
                    skip_bits(&gbc, 5); // skip dialog normalization
                    if (get_bits1(&gbc)) {
                        skip_bits(&gbc, 8); // skip compression gain word
                    }
                }
                /* get the dependent stream channel map, if exists */
                if (get_bits1(&gbc))
                    info->substream[parent].chan_loc |= (get_bits(&gbc, 16) >> 5) & 0x1f;
                else
                    info->substream[parent].chan_loc |= hdr->channel_mode;
            }
        }
    }

concatenate:
    if (!info->num_blocks && num_blocks == 6)
        return pkt->size;
    else if (info->num_blocks + num_blocks > 6)
        return AVERROR_INVALIDDATA;

    if (!info->num_blocks) {
        int ret;
        if ((ret = av_copy_packet(&info->pkt, pkt)) < 0)
            return ret;
        info->num_blocks = num_blocks;
        return 0;
    } else {
        int ret;
        if ((ret = av_grow_packet(&info->pkt, pkt->size)) < 0)
            return ret;
        memcpy(info->pkt.data + info->pkt.size - pkt->size, pkt->data, pkt->size);
        info->num_blocks += num_blocks;
        info->pkt.duration += pkt->duration;
        if ((ret = av_copy_packet_side_data(&info->pkt, pkt)) < 0)
            return ret;
        if (info->num_blocks != 6)
            return 0;
        av_packet_unref(pkt);
        if ((ret = av_copy_packet(pkt, &info->pkt)) < 0)
            return ret;
        av_packet_unref(&info->pkt);
        info->num_blocks = 0;
    }

    return pkt->size;
}

// FROM: libavcodec/ac3_parser.c
int avpriv_ac3_parse_header(GetBitContext *gbc, AC3HeaderInfo **phdr)
{
    int frame_size_code;
    AC3HeaderInfo *hdr;

    if (!*phdr)
        *phdr = av_mallocz(sizeof(AC3HeaderInfo));
    if (!*phdr)
        return AVERROR_ENOMEM;
    hdr = *phdr;

    memset(hdr, 0, sizeof(*hdr));

    hdr->sync_word = get_bits(gbc, 16);
    if(hdr->sync_word != 0x0B77)
        return AAC_AC3_PARSE_ERROR_SYNC;

    /* read ahead to bsid to distinguish between AC-3 and E-AC-3 */
    hdr->bitstream_id = show_bits_long(gbc, 29) & 0x1F;
    if(hdr->bitstream_id > 16)
        return AAC_AC3_PARSE_ERROR_BSID;

    hdr->num_blocks = 6;

    /* set default mix levels */
    hdr->center_mix_level   = 5;  // -4.5dB
    hdr->surround_mix_level = 6;  // -6.0dB

    /* set default dolby surround mode */
    hdr->dolby_surround_mode = AC3_DSURMOD_NOTINDICATED;

    if(hdr->bitstream_id <= 10) {
        /* Normal AC-3 */
        hdr->crc1 = get_bits(gbc, 16);
        hdr->sr_code = get_bits(gbc, 2);
        if(hdr->sr_code == 3)
            return AAC_AC3_PARSE_ERROR_SAMPLE_RATE;

        frame_size_code = get_bits(gbc, 6);
        if(frame_size_code > 37)
            return AAC_AC3_PARSE_ERROR_FRAME_SIZE;

        skip_bits(gbc, 5); // skip bsid, already got it

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
        hdr->frame_type = EAC3_FRAME_TYPE_AC3_CONVERT; //EAC3_FRAME_TYPE_INDEPENDENT;
        hdr->substreamid = 0;
    } else {
        /* Enhanced AC-3 */
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
