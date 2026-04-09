// FROM: libavcodec/mathops.h
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static inline int sign_extend(int val, unsigned bits)
{
    unsigned shift = 8 * sizeof(int) - bits;
    union { unsigned u; int s; } v = { (unsigned) val << shift };
    return v.s >> shift;
}

// FROM: libavutil/rational.h
typedef struct AVRational {
    int num;
    int den;
} AVRational;

static inline AVRational av_make_q(int num, int den)
{
    AVRational q = { num, den };
    return q;
}

// FROM: libavutil/channel_layout.h
enum AVChannelOrder {
    AV_CHANNEL_ORDER_UNSPEC,
    AV_CHANNEL_ORDER_NATIVE,
    AV_CHANNEL_ORDER_CUSTOM,
    AV_CHANNEL_ORDER_AMBISONIC,
};

enum AVChannel {
    AV_CHAN_AMBISONIC_BASE = 1024,
};

typedef struct AVChannelMapEntry {
    int id;
} AVChannelMapEntry;

typedef struct AVChannelLayout {
    enum AVChannelOrder order;
    int nb_channels;
    union {
        AVChannelMapEntry *map;
    } u;
} AVChannelLayout;

#define AV_CHANNEL_LAYOUT_MONO { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 1 }
#define AV_CHANNEL_LAYOUT_STEREO { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 2 }

// FROM: libavutil/dict.h
typedef struct AVDictionary AVDictionary;

// FROM: libavcodec/codec_id.h
enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_OPUS,
    AV_CODEC_ID_AAC,
    AV_CODEC_ID_FLAC,
    AV_CODEC_ID_PCM_S16BE,
    AV_CODEC_ID_PCM_S24BE,
    AV_CODEC_ID_PCM_S32BE,
    AV_CODEC_ID_PCM_S16LE,
    AV_CODEC_ID_PCM_S24LE,
    AV_CODEC_ID_PCM_S32LE,
};

// FROM: libavcodec/codec_par.h
typedef struct AVCodecParameters {
    enum AVCodecID codec_id;
    int codec_type;
    int frame_size;
    int sample_rate;
    int seek_preroll;
    AVChannelLayout ch_layout;
    uint8_t *extradata;
    int extradata_size;
} AVCodecParameters;

// FROM: libavutil/iamf.h
enum AVIAMFAnimationType {
    AV_IAMF_ANIMATION_TYPE_STEP,
    AV_IAMF_ANIMATION_TYPE_LINEAR,
    AV_IAMF_ANIMATION_TYPE_BEZIER,
};

typedef struct AVIAMFMixGain {
    const void *av_class;
    unsigned int subblock_duration;
    enum AVIAMFAnimationType animation_type;
    AVRational start_point_value;
    AVRational end_point_value;
    AVRational control_point_value;
    AVRational control_point_relative_time;
} AVIAMFMixGain;

typedef struct AVIAMFDemixingInfo {
    const void *av_class;
    unsigned int subblock_duration;
    unsigned int dmixp_mode;
} AVIAMFDemixingInfo;

typedef struct AVIAMFReconGain {
    const void *av_class;
    unsigned int subblock_duration;
    uint8_t recon_gain[6][12];
} AVIAMFReconGain;

enum AVIAMFParamDefinitionType {
    AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN,
    AV_IAMF_PARAMETER_DEFINITION_DEMIXING,
    AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN,
};

typedef struct AVIAMFParamDefinition {
    const void *av_class;
    size_t subblocks_offset;
    size_t subblock_size;
    unsigned int nb_subblocks;
    enum AVIAMFParamDefinitionType type;
    unsigned int parameter_id;
    unsigned int parameter_rate;
    unsigned int duration;
    unsigned int constant_subblock_duration;
} AVIAMFParamDefinition;

enum AVIAMFAmbisonicsMode {
    AV_IAMF_AMBISONICS_MODE_MONO,
    AV_IAMF_AMBISONICS_MODE_PROJECTION,
};

#define AV_IAMF_LAYER_FLAG_RECON_GAIN (1 << 0)

typedef struct AVIAMFLayer {
    const void *av_class;
    AVChannelLayout ch_layout;
    unsigned int flags;
    unsigned int output_gain_flags;
    AVRational output_gain;
    enum AVIAMFAmbisonicsMode ambisonics_mode;
    AVRational *demixing_matrix;
} AVIAMFLayer;

enum AVIAMFAudioElementType {
    AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL,
    AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE,
};

typedef struct AVIAMFAudioElement {
    const void *av_class;
    AVIAMFLayer **layers;
    unsigned int nb_layers;
    AVIAMFParamDefinition *demixing_info;
    AVIAMFParamDefinition *recon_gain_info;
    enum AVIAMFAudioElementType audio_element_type;
    unsigned int default_w;
} AVIAMFAudioElement;

enum AVIAMFHeadphonesMode {
    AV_IAMF_HEADPHONES_MODE_STEREO,
    AV_IAMF_HEADPHONES_MODE_BINAURAL,
};

typedef struct AVIAMFSubmixElement {
    const void *av_class;
    unsigned int audio_element_id;
    AVIAMFParamDefinition *element_mix_config;
    AVRational default_mix_gain;
    enum AVIAMFHeadphonesMode headphones_rendering_mode;
    AVDictionary *annotations;
} AVIAMFSubmixElement;

enum AVIAMFSubmixLayoutType {
    AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS = 2,
    AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL = 3,
};

typedef struct AVIAMFSubmixLayout {
    const void *av_class;
    enum AVIAMFSubmixLayoutType layout_type;
    AVChannelLayout sound_system;
    AVRational integrated_loudness;
    AVRational digital_peak;
    AVRational true_peak;
    AVRational dialogue_anchored_loudness;
    AVRational album_anchored_loudness;
} AVIAMFSubmixLayout;

typedef struct AVIAMFSubmix {
    const void *av_class;
    AVIAMFSubmixElement **elements;
    unsigned int nb_elements;
    AVIAMFSubmixLayout **layouts;
    unsigned int nb_layouts;
    AVIAMFParamDefinition *output_mix_config;
    AVRational default_mix_gain;
} AVIAMFSubmix;

typedef struct AVIAMFMixPresentation {
    const void *av_class;
    AVIAMFSubmix **submixes;
    unsigned int nb_submixes;
    AVDictionary *annotations;
} AVIAMFMixPresentation;

// FROM: libavformat/iamf.h
enum IAMF_OBU_Type {
    IAMF_OBU_IA_CODEC_CONFIG        = 0,
    IAMF_OBU_IA_AUDIO_ELEMENT       = 1,
    IAMF_OBU_IA_MIX_PRESENTATION    = 2,
    IAMF_OBU_IA_PARAMETER_BLOCK     = 3,
    IAMF_OBU_IA_TEMPORAL_DELIMITER  = 4,
    IAMF_OBU_IA_AUDIO_FRAME         = 5,
    IAMF_OBU_IA_AUDIO_FRAME_ID0     = 6,
    IAMF_OBU_IA_AUDIO_FRAME_ID1     = 7,
    IAMF_OBU_IA_AUDIO_FRAME_ID2     = 8,
    IAMF_OBU_IA_AUDIO_FRAME_ID3     = 9,
    IAMF_OBU_IA_AUDIO_FRAME_ID4     = 10,
    IAMF_OBU_IA_AUDIO_FRAME_ID5     = 11,
    IAMF_OBU_IA_AUDIO_FRAME_ID6     = 12,
    IAMF_OBU_IA_AUDIO_FRAME_ID7     = 13,
    IAMF_OBU_IA_AUDIO_FRAME_ID8     = 14,
    IAMF_OBU_IA_AUDIO_FRAME_ID9     = 15,
    IAMF_OBU_IA_AUDIO_FRAME_ID10    = 16,
    IAMF_OBU_IA_AUDIO_FRAME_ID11    = 17,
    IAMF_OBU_IA_AUDIO_FRAME_ID12    = 18,
    IAMF_OBU_IA_AUDIO_FRAME_ID13    = 19,
    IAMF_OBU_IA_AUDIO_FRAME_ID14    = 20,
    IAMF_OBU_IA_AUDIO_FRAME_ID15    = 21,
    IAMF_OBU_IA_AUDIO_FRAME_ID16    = 22,
    IAMF_OBU_IA_AUDIO_FRAME_ID17    = 23,
    IAMF_OBU_IA_SEQUENCE_HEADER     = 31,
};

typedef struct IAMFCodecConfig {
    unsigned codec_config_id;
    enum AVCodecID codec_id;
    uint32_t codec_tag;
    unsigned nb_samples;
    int audio_roll_distance;
    int sample_rate;
    int extradata_size;
    uint8_t *extradata;
} IAMFCodecConfig;

typedef struct IAMFLayer {
    unsigned int substream_count;
    unsigned int coupled_substream_count;
} IAMFLayer;

typedef struct IAMFSubStream {
    unsigned int audio_substream_id;
    AVCodecParameters *codecpar;
} IAMFSubStream;

typedef struct IAMFAudioElement {
    const AVIAMFAudioElement *celement;
    AVIAMFAudioElement *element;
    unsigned int audio_element_id;
    IAMFSubStream *substreams;
    unsigned int nb_substreams;
    unsigned int codec_config_id;
    IAMFLayer *layers;
    unsigned int nb_layers;
} IAMFAudioElement;

typedef struct IAMFMixPresentation {
    const AVIAMFMixPresentation *cmix;
    AVIAMFMixPresentation *mix;
    unsigned int mix_presentation_id;
    unsigned int count_label;
    char **language_label;
} IAMFMixPresentation;

typedef struct IAMFParamDefinition {
    const IAMFAudioElement *audio_element;
    AVIAMFParamDefinition *param;
    int mode;
    size_t param_size;
} IAMFParamDefinition;

typedef struct IAMFContext {
    IAMFCodecConfig **codec_configs;
    int nb_codec_configs;
    IAMFAudioElement **audio_elements;
    int nb_audio_elements;
    IAMFMixPresentation **mix_presentations;
    int nb_mix_presentations;
    IAMFParamDefinition **param_definitions;
    int nb_param_definitions;
} IAMFContext;

enum IAMF_Anchor_Element {
    IAMF_ANCHOR_ELEMENT_UNKNWONW,
    IAMF_ANCHOR_ELEMENT_DIALOGUE,
    IAMF_ANCHOR_ELEMENT_ALBUM,
};

enum IAMF_Sound_System {
    SOUND_SYSTEM_A_0_2_0  = 0,
    SOUND_SYSTEM_B_0_5_0  = 1,
    SOUND_SYSTEM_C_2_5_0  = 2,
    SOUND_SYSTEM_D_4_5_0  = 3,
    SOUND_SYSTEM_E_4_5_1  = 4,
    SOUND_SYSTEM_F_3_7_0  = 5,
    SOUND_SYSTEM_G_4_9_0  = 6,
    SOUND_SYSTEM_H_9_10_3 = 7,
    SOUND_SYSTEM_I_0_7_0  = 8,
    SOUND_SYSTEM_J_4_7_0  = 9,
    SOUND_SYSTEM_10_2_7_0 = 10,
    SOUND_SYSTEM_11_2_3_0 = 11,
    SOUND_SYSTEM_12_0_1_0 = 12,
};

struct IAMFSoundSystemMap {
    enum IAMF_Sound_System id;
    AVChannelLayout layout;
};

#define AV_INPUT_BUFFER_PADDING_SIZE 64
#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA AVERROR(74)
#define AVERROR_ENOMEM AVERROR(12)
#define AV_LOG_ERROR 16
#define AV_LOG_DEBUG 48
#define AV_LOG_WARNING 24
#define AV_DICT_DONT_STRDUP_VAL 16
#define AV_DICT_DONT_OVERWRITE 32
#define AVMEDIA_TYPE_AUDIO 0
#define AV_DISPOSITION_DEFAULT 1
#define AV_DISPOSITION_DEPENDENT 256
#define SEEK_CUR 1
#define EEXIST 17
#define AV_CH_LAYOUT_5POINT1POINT4_BACK 0
#define AV_CH_BOTTOM_FRONT_CENTER 0
#define MKBETAG(a,b,c,d) ((uint32_t)(a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define FFMIN(a,b) ((a) < (b) ? (a) : (b))
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
#define AV_RB16(x) ((((const uint8_t*)(x))[0] << 8) | ((const uint8_t*)(x))[1])
#define AV_RB24(x) ((((const uint8_t*)(x))[0] << 16) | (((const uint8_t*)(x))[1] << 8) | ((const uint8_t*)(x))[2])
#define AV_RB32(x) ((((const uint8_t*)(x))[0] << 24) | (((const uint8_t*)(x))[1] << 16) | (((const uint8_t*)(x))[2] << 8) | ((const uint8_t*)(x))[3])
#define AV_WB32A(p,d) do { ((uint8_t*)(p))[0] = (d) >> 24; ((uint8_t*)(p))[1] = ((d) >> 16) & 0xFF; ((uint8_t*)(p))[2] = ((d) >> 8) & 0xFF; ((uint8_t*)(p))[3] = (d) & 0xFF; } while(0)
#define AV_WB8(p,d) do { ((uint8_t*)(p))[0] = (d); } while(0)
#define AV_WL16A(p,d) do { ((uint8_t*)(p))[0] = (d) & 0xFF; ((uint8_t*)(p))[1] = ((d) >> 8) & 0xFF; } while(0)
#define AV_WL32A(p,d) do { ((uint8_t*)(p))[0] = (d) & 0xFF; ((uint8_t*)(p))[1] = ((d) >> 8) & 0xFF; ((uint8_t*)(p))[2] = ((d) >> 16) & 0xFF; ((uint8_t*)(p))[3] = ((d) >> 24) & 0xFF; } while(0)
#define FLAC_STREAMINFO_SIZE 34
#define AOT_ESCAPE 31
#define MP4DecConfigDescrTag 4
#define MP4DecSpecificDescrTag 5
#define IAMF_ANCHOR_ELEMENT_DIALOGUE 1
#define IAMF_ANCHOR_ELEMENT_ALBUM 2
#define MAX_IAMF_OBU_HEADER_SIZE 25

// Additional channel layout macros
#define AV_CHANNEL_LAYOUT_5POINT1_BACK { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 6 }
#define AV_CHANNEL_LAYOUT_5POINT1POINT2_BACK { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 7 }
#define AV_CHANNEL_LAYOUT_5POINT1POINT4_BACK { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 9 }
#define AV_CHANNEL_LAYOUT_7POINT1 { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 8 }
#define AV_CHANNEL_LAYOUT_7POINT1POINT2 { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 10 }
#define AV_CHANNEL_LAYOUT_7POINT1POINT4_BACK { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 12 }
#define AV_CHANNEL_LAYOUT_3POINT1POINT2 { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 6 }
#define AV_CHANNEL_LAYOUT_BINAURAL { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 2 }
#define AV_CHANNEL_LAYOUT_7POINT2POINT3 { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 10 }
#define AV_CHANNEL_LAYOUT_9POINT1POINT4_BACK { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 14 }
#define AV_CHANNEL_LAYOUT_22POINT2 { .order = AV_CHANNEL_ORDER_NATIVE, .nb_channels = 24 }

// FROM: libavformat/avio.h
typedef struct AVIOContext {
    unsigned char *buf;
    int buf_size;
    unsigned char *buf_ptr;
    unsigned char *buf_end;
    void *opaque;
    int (*read_packet)(void *opaque, uint8_t *buf, int buf_size);
    int (*write_packet)(void *opaque, const uint8_t *buf, int buf_size);
    int64_t (*seek)(void *opaque, int64_t offset, int whence);
    int64_t pos;
    int eof_reached;
    int error;
    int write_flag;
} AVIOContext;

typedef struct AVFormatContext {
    void *priv_data;
    struct AVIOContext *pb;
    unsigned int nb_stream_groups;
    void **stream_groups;
} AVFormatContext;

typedef struct AVStreamGroup {
    int type;
    unsigned int id;
    unsigned int nb_streams;
    void **streams;
    union {
        AVIAMFAudioElement *iamf_audio_element;
        AVIAMFMixPresentation *iamf_mix_presentation;
    } params;
} AVStreamGroup;

#define AV_STREAM_GROUP_PARAMS_IAMF_AUDIO_ELEMENT 1
#define AV_STREAM_GROUP_PARAMS_IAMF_MIX_PRESENTATION 2

typedef struct AVStream {
    AVCodecParameters *codecpar;
    int id;
    int disposition;
} AVStream;

// FROM: libavformat/iamf_reader.h
typedef struct IAMFDemuxContext {
    IAMFContext iamf;
    AVIAMFParamDefinition *mix;
    size_t mix_size;
    AVIAMFParamDefinition *demix;
    size_t demix_size;
    AVIAMFParamDefinition *recon;
    size_t recon_size;
} IAMFDemuxContext;

// FROM: libavformat/avio_internal.h
typedef struct FFIOContext {
    AVIOContext pub;
} FFIOContext;

// FROM: libavcodec/get_bits.h
typedef struct GetBitContext {
    const uint8_t *buffer;
    int index;
    int size_in_bits;
    int size_in_bits_max;
} GetBitContext;

// FROM: libavcodec/leb.h

// Stub implementations for missing FFmpeg functions
static inline uint8_t avio_r8(AVIOContext *s) {
    if (s->buf_ptr >= s->buf_end) {
        s->eof_reached = 1;
        return 0;
    }
    return *s->buf_ptr++;
}

static inline int16_t avio_rb16(AVIOContext *s) {
    return (avio_r8(s) << 8) | avio_r8(s);
}

static inline int32_t avio_rb32(AVIOContext *s) {
    return (avio_r8(s) << 24) | (avio_r8(s) << 16) | (avio_r8(s) << 8) | avio_r8(s);
}

static inline int64_t avio_rb64(AVIOContext *s) {
    return ((int64_t)avio_r8(s) << 56) | ((int64_t)avio_r8(s) << 48) |
           ((int64_t)avio_r8(s) << 40) | ((int64_t)avio_r8(s) << 32) |
           ((int64_t)avio_r8(s) << 24) | ((int64_t)avio_r8(s) << 16) |
           ((int64_t)avio_r8(s) << 8) | avio_r8(s);
}

static inline int64_t avio_skip(AVIOContext *s, int64_t offset) {
    s->pos += offset;
    s->buf_ptr += offset;
    return s->pos;
}

static inline int64_t avio_tell(AVIOContext *s) {
    return s->pos;
}

static inline int64_t avio_seek(AVIOContext *s, int64_t offset, int whence) {
    if (whence == SEEK_CUR) {
        s->pos += offset;
        s->buf_ptr += offset;
    } else {
        s->pos = offset;
        s->buf_ptr = s->buf + offset;
    }
    return s->pos;
}

static inline int avio_read(AVIOContext *s, unsigned char *buf, int size) {
    int i;
    for (i = 0; i < size && s->buf_ptr < s->buf_end; i++) {
        buf[i] = *s->buf_ptr++;
    }
    s->pos += i;
    return i;
}

static inline int ffio_read_size(AVIOContext *s, unsigned char *buf, int size) {
    int ret = avio_read(s, buf, size);
    return (ret == size) ? 0 : AVERROR_INVALIDDATA;
}

static inline int avio_get_str(AVIOContext *pb, int maxlen, char *buf, int buflen) {
    int i = 0;
    while (i < maxlen - 1) {
        uint8_t c = avio_r8(pb);
        if (c == 0) break;
        if (i < buflen - 1) buf[i++] = c;
    }
    buf[i] = 0;
    return i;
}

static inline void* av_malloc(size_t size) {
    return malloc(size);
}

static inline void* av_mallocz(size_t size) {
    void *ptr = malloc(size);
    if (ptr) memset(ptr, 0, size);
    return ptr;
}

static inline void* av_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

static inline void* av_realloc_array(void *ptr, size_t nmemb, size_t size) {
    return realloc(ptr, nmemb * size);
}

static inline void* av_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

static inline void av_free(void *ptr) {
    free(ptr);
}

static inline void av_freep(void *ptr) {
    void **p = (void **)ptr;
    if (*p) {
        free(*p);
        *p = NULL;
    }
}

static inline char* av_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *ptr = malloc(len);
    if (ptr) memcpy(ptr, s, len);
    return ptr;
}

static inline void* av_malloc_array(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

static inline int av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src) {
    *dst = *src;
    return 0;
}

static inline int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags) {
    return 0;
}

static inline void av_log(void *avcl, int level, const char *fmt, ...) {
}

static inline AVCodecParameters* avcodec_parameters_alloc(void) {
    return av_mallocz(sizeof(AVCodecParameters));
}

static inline void avcodec_parameters_free(AVCodecParameters **pparams) {
    if (*pparams) {
        av_free((*pparams)->extradata);
        av_free(*pparams);
        *pparams = NULL;
    }
}

static inline int avcodec_parameters_copy(AVCodecParameters *dst, const AVCodecParameters *src) {
    *dst = *src;
    if (src->extradata) {
        dst->extradata = av_malloc(src->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (dst->extradata) {
            memcpy(dst->extradata, src->extradata, src->extradata_size);
        }
    }
    return 0;
}

static inline AVIAMFAudioElement* av_iamf_audio_element_alloc(void) {
    return av_mallocz(sizeof(AVIAMFAudioElement));
}

static inline AVIAMFLayer* av_iamf_audio_element_add_layer(AVIAMFAudioElement *audio_element) {
    AVIAMFLayer **tmp = av_realloc_array(audio_element->layers, audio_element->nb_layers + 1, sizeof(*audio_element->layers));
    if (!tmp) return NULL;
    audio_element->layers = tmp;
    audio_element->layers[audio_element->nb_layers] = av_mallocz(sizeof(AVIAMFLayer));
    return audio_element->layers[audio_element->nb_layers++];
}

static inline void av_iamf_audio_element_free(AVIAMFAudioElement **audio_element) {
    if (!*audio_element) return;
    for (unsigned int i = 0; i < (*audio_element)->nb_layers; i++) {
        av_free((*audio_element)->layers[i]);
    }
    av_free((*audio_element)->layers);
    av_free(*audio_element);
    *audio_element = NULL;
}

static inline AVIAMFMixPresentation* av_iamf_mix_presentation_alloc(void) {
    return av_mallocz(sizeof(AVIAMFMixPresentation));
}

static inline AVIAMFSubmix* av_iamf_mix_presentation_add_submix(AVIAMFMixPresentation *mix_presentation) {
    AVIAMFSubmix **tmp = av_realloc_array(mix_presentation->submixes, mix_presentation->nb_submixes + 1, sizeof(*mix_presentation->submixes));
    if (!tmp) return NULL;
    mix_presentation->submixes = tmp;
    mix_presentation->submixes[mix_presentation->nb_submixes] = av_mallocz(sizeof(AVIAMFSubmix));
    return mix_presentation->submixes[mix_presentation->nb_submixes++];
}

static inline AVIAMFSubmixElement* av_iamf_submix_add_element(AVIAMFSubmix *submix) {
    AVIAMFSubmixElement **tmp = av_realloc_array(submix->elements, submix->nb_elements + 1, sizeof(*submix->elements));
    if (!tmp) return NULL;
    submix->elements = tmp;
    submix->elements[submix->nb_elements] = av_mallocz(sizeof(AVIAMFSubmixElement));
    return submix->elements[submix->nb_elements++];
}

static inline AVIAMFSubmixLayout* av_iamf_submix_add_layout(AVIAMFSubmix *submix) {
    AVIAMFSubmixLayout **tmp = av_realloc_array(submix->layouts, submix->nb_layouts + 1, sizeof(*submix->layouts));
    if (!tmp) return NULL;
    submix->layouts = tmp;
    submix->layouts[submix->nb_layouts] = av_mallocz(sizeof(AVIAMFSubmixLayout));
    return submix->layouts[submix->nb_layouts++];
}

static inline void av_iamf_mix_presentation_free(AVIAMFMixPresentation **mix_presentation) {
    if (!*mix_presentation) return;
    for (unsigned int i = 0; i < (*mix_presentation)->nb_submixes; i++) {
        AVIAMFSubmix *submix = (*mix_presentation)->submixes[i];
        for (unsigned int j = 0; j < submix->nb_elements; j++) {
            av_free(submix->elements[j]);
        }
        av_free(submix->elements);
        for (unsigned int j = 0; j < submix->nb_layouts; j++) {
            av_free(submix->layouts[j]);
        }
        av_free(submix->layouts);
        av_free(submix);
    }
    av_free((*mix_presentation)->submixes);
    av_free(*mix_presentation);
    *mix_presentation = NULL;
}

static inline AVIAMFParamDefinition* av_iamf_param_definition_alloc(enum AVIAMFParamDefinitionType type, unsigned int nb_subblocks, size_t *size) {
    size_t subblock_size;
    switch (type) {
        case AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN: subblock_size = sizeof(AVIAMFMixGain); break;
        case AV_IAMF_PARAMETER_DEFINITION_DEMIXING: subblock_size = sizeof(AVIAMFDemixingInfo); break;
        case AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN: subblock_size = sizeof(AVIAMFReconGain); break;
        default: return NULL;
    }
    size_t total_size = sizeof(AVIAMFParamDefinition) + nb_subblocks * subblock_size;
    AVIAMFParamDefinition *param = av_mallocz(total_size);
    if (param) {
        param->subblocks_offset = sizeof(AVIAMFParamDefinition);
        param->subblock_size = subblock_size;
        param->nb_subblocks = nb_subblocks;
        param->type = type;
        if (size) *size = total_size;
    }
    return param;
}

static inline void* av_iamf_param_definition_get_subblock(const AVIAMFParamDefinition *par, unsigned int idx) {
    return (void *)((uint8_t *)par + par->subblocks_offset + idx * par->subblock_size);
}

static inline void ff_iamf_free_audio_element(IAMFAudioElement **paudio_element) {
    IAMFAudioElement *audio_element = *paudio_element;
    if (!audio_element) return;
    for (int i = 0; i < audio_element->nb_substreams; i++)
        avcodec_parameters_free(&audio_element->substreams[i].codecpar);
    av_free(audio_element->substreams);
    av_free(audio_element->layers);
    av_iamf_audio_element_free(&audio_element->element);
    av_freep(paudio_element);
}

static inline void ff_iamf_free_mix_presentation(IAMFMixPresentation **pmix_presentation) {
    IAMFMixPresentation *mix_presentation = *pmix_presentation;
    if (!mix_presentation) return;
    for (int i = 0; i < mix_presentation->count_label; i++)
        av_free(mix_presentation->language_label[i]);
    av_free(mix_presentation->language_label);
    av_iamf_mix_presentation_free(&mix_presentation->mix);
    av_freep(pmix_presentation);
}

static inline IAMFCodecConfig *ff_iamf_get_codec_config(const IAMFContext *c, unsigned int codec_config_id) {
    IAMFCodecConfig *codec_config = NULL;
    for (int i = 0; i < c->nb_codec_configs; i++) {
        if (c->codec_configs[i]->codec_config_id == codec_config_id)
            codec_config = c->codec_configs[i];
    }
    return codec_config;
}

static inline void ffio_init_context(FFIOContext *s, unsigned char *buffer, int buffer_size, int write_flag, void *opaque, int (*read_packet)(void *opaque, uint8_t *buf, int buf_size), int (*write_packet)(void *opaque, const uint8_t *buf, int buf_size), int64_t (*seek)(void *opaque, int64_t offset, int whence)) {
    s->pub.buf = buffer;
    s->pub.buf_size = buffer_size;
    s->pub.buf_ptr = buffer;
    s->pub.buf_end = buffer + buffer_size;
    s->pub.opaque = opaque;
    s->pub.write_flag = write_flag;
    s->pub.pos = 0;
    s->pub.eof_reached = 0;
    s->pub.error = 0;
}

static inline int ffio_ensure_seekback(AVIOContext *s, int64_t buf_size) {
    return 0;
}

static inline int init_get_bits8(GetBitContext *s, const uint8_t *buffer, int byte_size) {
    s->buffer = buffer;
    s->index = 0;
    s->size_in_bits = byte_size * 8;
    s->size_in_bits_max = byte_size * 8;
    return 0;
}

static inline int get_bits(GetBitContext *s, int n) {
    int val = 0;
    for (int i = 0; i < n; i++) {
        int bit_idx = s->index;
        int byte_idx = bit_idx / 8;
        int bit_pos = 7 - (bit_idx % 8);
        val = (val << 1) | ((s->buffer[byte_idx] >> bit_pos) & 1);
        s->index++;
    }
    return val;
}

static inline int get_bits1(GetBitContext *s) {
    return get_bits(s, 1);
}

static inline int get_bits_count(GetBitContext *s) {
    return s->index;
}

static inline int get_bits_left(GetBitContext *s) {
    return s->size_in_bits - s->index;
}

static inline void skip_bits_long(GetBitContext *s, int n) {
    s->index += n;
}

static inline unsigned int get_leb(GetBitContext *s) {
    unsigned int val = 0;
    unsigned int c;
    do {
        c = get_bits(s, 8);
        val |= (c & 0x7f) << (7 * (val >> 31));
        if (val >> 31)
            break;
    } while (c & 0x80);
    return val;
}

static inline int ff_mp4_read_descr(void *logctx, AVIOContext *pb, int *tag) {
    int len = avio_r8(pb);
    *tag = len;
    if (len & 0x80) {
        len = (len & 0x7f) << 8;
        len |= avio_r8(pb);
        if (len & 0x80) {
            len = (len & 0x7f) << 8;
            len |= avio_r8(pb);
            if (len & 0x80) {
                len = (len & 0x7f) << 8;
                len |= avio_r8(pb);
            }
        }
    }
    return len;
}

static inline unsigned int ffio_read_leb(AVIOContext *s)
{
    unsigned int val = 0;
    unsigned int c;
    do {
        c = avio_r8(s);
        val |= (c & 0x7f) << (7 * (val >> 31));
        if (val >> 31)
            break;
    } while (c & 0x80);
    return val;
}

// FROM: libavformat/iamf.c
const AVChannelLayout ff_iamf_scalable_ch_layouts[10] = {
    AV_CHANNEL_LAYOUT_MONO,
    AV_CHANNEL_LAYOUT_STEREO,
    AV_CHANNEL_LAYOUT_5POINT1_BACK,
    AV_CHANNEL_LAYOUT_5POINT1POINT2_BACK,
    AV_CHANNEL_LAYOUT_5POINT1POINT4_BACK,
    AV_CHANNEL_LAYOUT_7POINT1,
    AV_CHANNEL_LAYOUT_7POINT1POINT2,
    AV_CHANNEL_LAYOUT_7POINT1POINT4_BACK,
    AV_CHANNEL_LAYOUT_3POINT1POINT2,
    AV_CHANNEL_LAYOUT_BINAURAL,
};

const struct IAMFSoundSystemMap ff_iamf_sound_system_map[13] = {
    { SOUND_SYSTEM_A_0_2_0, AV_CHANNEL_LAYOUT_STEREO },
    { SOUND_SYSTEM_B_0_5_0, AV_CHANNEL_LAYOUT_5POINT1_BACK },
    { SOUND_SYSTEM_C_2_5_0, AV_CHANNEL_LAYOUT_5POINT1POINT2_BACK },
    { SOUND_SYSTEM_D_4_5_0, AV_CHANNEL_LAYOUT_5POINT1POINT4_BACK },
    { SOUND_SYSTEM_E_4_5_1, { .nb_channels = 11, .order = AV_CHANNEL_ORDER_NATIVE } },
    { SOUND_SYSTEM_F_3_7_0,  AV_CHANNEL_LAYOUT_7POINT2POINT3 },
    { SOUND_SYSTEM_G_4_9_0,  AV_CHANNEL_LAYOUT_9POINT1POINT4_BACK },
    { SOUND_SYSTEM_H_9_10_3, AV_CHANNEL_LAYOUT_22POINT2 },
    { SOUND_SYSTEM_I_0_7_0,  AV_CHANNEL_LAYOUT_7POINT1 },
    { SOUND_SYSTEM_J_4_7_0,  AV_CHANNEL_LAYOUT_7POINT1POINT4_BACK },
    { SOUND_SYSTEM_10_2_7_0, AV_CHANNEL_LAYOUT_7POINT1POINT2 },
    { SOUND_SYSTEM_11_2_3_0, AV_CHANNEL_LAYOUT_3POINT1POINT2 },
    { SOUND_SYSTEM_12_0_1_0, AV_CHANNEL_LAYOUT_MONO },
};

// FROM: libavformat/iamf_parse.c
static inline AVStreamGroup* avformat_stream_group_create(AVFormatContext *s, int type, void *unused) {
    AVStreamGroup **tmp = av_realloc_array((AVStreamGroup**)s->stream_groups, s->nb_stream_groups + 1, sizeof(*s->stream_groups));
    if (!tmp) return NULL;
    s->stream_groups = (void**)tmp;
    s->stream_groups[s->nb_stream_groups] = av_mallocz(sizeof(AVStreamGroup));
    ((AVStreamGroup*)s->stream_groups[s->nb_stream_groups])->type = type;
    return (AVStreamGroup*)s->stream_groups[s->nb_stream_groups++];
}

static inline AVStream* avformat_new_stream(AVFormatContext *s, void *unused) {
    AVStream *st = av_mallocz(sizeof(AVStream));
    if (st) {
        st->codecpar = avcodec_parameters_alloc();
    }
    return st;
}

static inline int avformat_stream_group_add_stream(AVStreamGroup *stg, AVStream *st) {
    void **tmp = av_realloc_array(stg->streams, stg->nb_streams + 1, sizeof(*stg->streams));
    if (!tmp) return AVERROR_ENOMEM;
    stg->streams = tmp;
    stg->streams[stg->nb_streams++] = st;
    return 0;
}

static int ambisonics_config(void *s, AVIOContext *pb, IAMFAudioElement *audio_element, const IAMFCodecConfig *codec_config);

// FROM: libavformat/iamf_parse.c
static int opus_decoder_config(IAMFCodecConfig *codec_config,
                               AVIOContext *pb, int len)
{
    int ret, left = len - avio_tell(pb);

    if (left < 11 || codec_config->audio_roll_distance >= 0)
        return AVERROR_INVALIDDATA;

    codec_config->extradata = av_malloc(left + 8);
    if (!codec_config->extradata)
        return AVERROR_ENOMEM;

    AV_WB32A(codec_config->extradata,     MKBETAG('O','p','u','s'));
    AV_WB32A(codec_config->extradata + 4, MKBETAG('H','e','a','d'));
    ret = ffio_read_size(pb, codec_config->extradata + 8, left);
    if (ret < 0)
        return ret;

    codec_config->extradata_size = left + 8;
    codec_config->sample_rate = 48000;

    return 0;
}

static int aac_decoder_config(IAMFCodecConfig *codec_config,
                              AVIOContext *pb, int len, void *logctx)
{
    int ret, tag, left;

    if (codec_config->audio_roll_distance >= 0)
        return AVERROR_INVALIDDATA;

    ff_mp4_read_descr(logctx, pb, &tag);
    if (tag != MP4DecConfigDescrTag)
        return AVERROR_INVALIDDATA;

    if (avio_r8(pb) != 0x40)
        return AVERROR_INVALIDDATA;

    avio_skip(pb, 11);

    left = ff_mp4_read_descr(logctx, pb, &tag);
    if (tag != MP4DecSpecificDescrTag ||
        !left || left > (len - avio_tell(pb)))
        return AVERROR_INVALIDDATA;

    codec_config->extradata = av_malloc((size_t)left + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!codec_config->extradata)
        return AVERROR_ENOMEM;

    ret = ffio_read_size(pb, codec_config->extradata, left);
    if (ret < 0)
        return ret;
    codec_config->extradata_size = left;
    memset(codec_config->extradata + codec_config->extradata_size, 0,
           AV_INPUT_BUFFER_PADDING_SIZE);

    codec_config->sample_rate = 48000;

    return 0;
}

static int flac_decoder_config(IAMFCodecConfig *codec_config,
                               AVIOContext *pb, int len)
{
    int ret, left;

    if (codec_config->audio_roll_distance)
        return AVERROR_INVALIDDATA;

    avio_skip(pb, 4);

    left = len - avio_tell(pb);
    if (left < FLAC_STREAMINFO_SIZE)
        return AVERROR_INVALIDDATA;

    codec_config->extradata = av_malloc(left);
    if (!codec_config->extradata)
        return AVERROR_ENOMEM;

    ret = ffio_read_size(pb, codec_config->extradata, left);
    if (ret < 0)
        return ret;

    codec_config->extradata_size = left;
    codec_config->sample_rate = AV_RB24(codec_config->extradata + 10) >> 4;

    return 0;
}

static int ipcm_decoder_config(IAMFCodecConfig *codec_config,
                               AVIOContext *pb, int len)
{
    static const enum AVCodecID sample_fmt[2][3] = {
        { AV_CODEC_ID_PCM_S16BE, AV_CODEC_ID_PCM_S24BE, AV_CODEC_ID_PCM_S32BE },
        { AV_CODEC_ID_PCM_S16LE, AV_CODEC_ID_PCM_S24LE, AV_CODEC_ID_PCM_S32LE },
    };
    int sample_format = avio_r8(pb);
    int sample_size = (avio_r8(pb) / 8 - 2);
    if (sample_format > 1 || sample_size > 2U || codec_config->audio_roll_distance)
        return AVERROR_INVALIDDATA;

    codec_config->codec_id = sample_fmt[sample_format][sample_size];
    codec_config->sample_rate = avio_rb32(pb);

    if (len - avio_tell(pb))
        return AVERROR_INVALIDDATA;

    return 0;
}

static int update_extradata(AVCodecParameters *codecpar)
{
    switch(codecpar->codec_id) {
    case AV_CODEC_ID_OPUS:
        AV_WB8(codecpar->extradata   + 9,  codecpar->ch_layout.nb_channels);
        break;
    }

    return 0;
}

static int scalable_channel_layout_config(void *s, AVIOContext *pb,
                                          IAMFAudioElement *audio_element,
                                          const IAMFCodecConfig *codec_config)
{
    int nb_layers, k = 0;

    nb_layers = avio_r8(pb) >> 5;

    if (nb_layers > 6 || nb_layers == 0)
        return AVERROR_INVALIDDATA;

    audio_element->layers = av_calloc(nb_layers, sizeof(*audio_element->layers));
    if (!audio_element->layers)
        return AVERROR_ENOMEM;

    audio_element->nb_layers = nb_layers;
    for (int i = 0; i < nb_layers; i++) {
        AVIAMFLayer *layer;
        int substream_count, coupled_substream_count;
        int ret, byte = avio_r8(pb);

        layer = av_iamf_audio_element_add_layer(audio_element->element);
        if (!layer)
            return AVERROR_ENOMEM;

        if ((byte >> 2) & 1)
            layer->flags |= AV_IAMF_LAYER_FLAG_RECON_GAIN;
        substream_count = avio_r8(pb);
        coupled_substream_count = avio_r8(pb);

        if (substream_count + k > audio_element->nb_substreams)
            return AVERROR_INVALIDDATA;

        audio_element->layers[i].substream_count         = substream_count;
        audio_element->layers[i].coupled_substream_count = coupled_substream_count;
        if ((byte >> 3) & 1) {
            layer->output_gain_flags = avio_r8(pb) >> 2;
            layer->output_gain = av_make_q(sign_extend(avio_rb16(pb), 16), 1 << 8);
        }

        if ((byte >> 4) < 10)
            av_channel_layout_copy(&layer->ch_layout, &ff_iamf_scalable_ch_layouts[byte >> 4]);
        else
            layer->ch_layout = (AVChannelLayout){ .order = AV_CHANNEL_ORDER_UNSPEC,
                                                          .nb_channels = substream_count +
                                                                         coupled_substream_count };

        for (int j = 0; j < substream_count; j++) {
            IAMFSubStream *substream = &audio_element->substreams[k++];

            substream->codecpar->ch_layout = coupled_substream_count-- > 0 ? (AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO :
                                                                             (AVChannelLayout)AV_CHANNEL_LAYOUT_MONO;

            ret = update_extradata(substream->codecpar);
            if (ret < 0)
                return ret;
        }

    }

    return 0;
}

static int param_parse(void *s, IAMFContext *c, AVIOContext *pb,
                       unsigned int type,
                       const IAMFAudioElement *audio_element,
                       AVIAMFParamDefinition **out_param_definition)
{
    IAMFParamDefinition *param_definition = NULL;
    AVIAMFParamDefinition *param;
    unsigned int parameter_id, parameter_rate, mode;
    unsigned int duration = 0, constant_subblock_duration = 0, nb_subblocks = 0;
    size_t param_size;

    parameter_id = ffio_read_leb(pb);

    for (int i = 0; i < c->nb_param_definitions; i++)
        if (c->param_definitions[i]->param->parameter_id == parameter_id) {
            param_definition = c->param_definitions[i];
            break;
        }

    parameter_rate = ffio_read_leb(pb);
    mode = avio_r8(pb) >> 7;

    if (mode == 0) {
        duration = ffio_read_leb(pb);
        if (!duration)
            return AVERROR_INVALIDDATA;
        constant_subblock_duration = ffio_read_leb(pb);
        if (constant_subblock_duration == 0)
            nb_subblocks = ffio_read_leb(pb);
        else
            nb_subblocks = duration / constant_subblock_duration;
    }

    param = av_iamf_param_definition_alloc(type, nb_subblocks, &param_size);
    if (!param)
        return AVERROR_ENOMEM;

    for (int i = 0; i < nb_subblocks; i++) {
        void *subblock = av_iamf_param_definition_get_subblock(param, i);
        unsigned int subblock_duration = constant_subblock_duration;

        if (constant_subblock_duration == 0)
            subblock_duration = ffio_read_leb(pb);

        switch (type) {
        case AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN: {
            AVIAMFMixGain *mix = subblock;
            mix->subblock_duration = subblock_duration;
            break;
        }
        case AV_IAMF_PARAMETER_DEFINITION_DEMIXING: {
            AVIAMFDemixingInfo *demix = subblock;
            demix->subblock_duration = subblock_duration;
            demix->dmixp_mode = avio_r8(pb) >> 5;
            audio_element->element->default_w = avio_r8(pb) >> 4;
            break;
        }
        case AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN: {
            AVIAMFReconGain *recon = subblock;
            recon->subblock_duration = subblock_duration;
            break;
        }
        default:
            av_free(param);
            return AVERROR_INVALIDDATA;
        }
    }

    param->parameter_id = parameter_id;
    param->parameter_rate = parameter_rate;
    param->duration = duration;
    param->constant_subblock_duration = constant_subblock_duration;
    param->nb_subblocks = nb_subblocks;

    if (param_definition) {
        if (param_definition->param_size != param_size || memcmp(param_definition->param, param, param_size)) {
            av_free(param);
            return AVERROR_INVALIDDATA;
        }
    } else {
        IAMFParamDefinition **tmp = av_realloc_array(c->param_definitions, c->nb_param_definitions + 1,
                                                     sizeof(*c->param_definitions));
        if (!tmp) {
            av_free(param);
            return AVERROR_ENOMEM;
        }
        c->param_definitions = tmp;

        param_definition = av_mallocz(sizeof(*param_definition));
        if (!param_definition) {
            av_free(param);
            return AVERROR_ENOMEM;
        }
        param_definition->param = param;
        param_definition->mode = !mode;
        param_definition->param_size = param_size;
        param_definition->audio_element = audio_element;

        c->param_definitions[c->nb_param_definitions++] = param_definition;
    }

    *out_param_definition = param;

    return 0;
}

static int label_string(AVIOContext *pb, char **label)
{
    uint8_t buf[128];

    avio_get_str(pb, sizeof(buf), buf, sizeof(buf));

    if (pb->error)
        return pb->error;
    if (pb->eof_reached)
        return AVERROR_INVALIDDATA;
    *label = av_strdup(buf);
    if (!*label)
        return AVERROR_ENOMEM;

    return 0;
}

static int codec_config_obu(void *s, IAMFContext *c, AVIOContext *pb, int len)
{
    IAMFCodecConfig **tmp, *codec_config = NULL;
    FFIOContext b;
    AVIOContext *pbc;
    uint8_t *buf;
    enum AVCodecID avcodec_id;
    unsigned codec_config_id, nb_samples, codec_id;
    int16_t audio_roll_distance;
    int ret;

    buf = av_malloc(len);
    if (!buf)
        return AVERROR_ENOMEM;

    ret = ffio_read_size(pb, buf, len);
    if (ret < 0)
        goto fail;

    ffio_init_context(&b, buf, len, 0, NULL, NULL, NULL, NULL);
    pbc = &b.pub;

    codec_config_id = ffio_read_leb(pbc);
    codec_id = avio_rb32(pbc);
    nb_samples = ffio_read_leb(pbc);
    audio_roll_distance = avio_rb16(pbc);

    switch(codec_id) {
    case MKBETAG('O','p','u','s'):
        avcodec_id = AV_CODEC_ID_OPUS;
        break;
    case MKBETAG('m','p','4','a'):
        avcodec_id = AV_CODEC_ID_AAC;
        break;
    case MKBETAG('f','L','a','C'):
        avcodec_id = AV_CODEC_ID_FLAC;
        break;
    default:
        avcodec_id = AV_CODEC_ID_NONE;
        break;
    }

    for (int i = 0; i < c->nb_codec_configs; i++)
        if (c->codec_configs[i]->codec_config_id == codec_config_id) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

    tmp = av_realloc_array(c->codec_configs, c->nb_codec_configs + 1, sizeof(*c->codec_configs));
    if (!tmp) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    c->codec_configs = tmp;

    codec_config = av_mallocz(sizeof(*codec_config));
    if (!codec_config) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }

    codec_config->codec_config_id = codec_config_id;
    codec_config->codec_id = avcodec_id;
    codec_config->nb_samples = nb_samples;
    codec_config->audio_roll_distance = audio_roll_distance;

    switch(codec_id) {
    case MKBETAG('O','p','u','s'):
        ret = opus_decoder_config(codec_config, pbc, len);
        break;
    case MKBETAG('m','p','4','a'):
        ret = aac_decoder_config(codec_config, pbc, len, s);
        break;
    case MKBETAG('f','L','a','C'):
        ret = flac_decoder_config(codec_config, pbc, len);
        break;
    case MKBETAG('i','p','c','m'):
        ret = ipcm_decoder_config(codec_config, pbc, len);
        break;
    default:
        break;
    }
    if (ret < 0)
        goto fail;

    c->codec_configs[c->nb_codec_configs++] = codec_config;

    len -= avio_tell(pbc);
    if (len)
       av_log(s, AV_LOG_WARNING, "Underread in codec_config_obu. %d bytes left at the end\n", len);

    ret = 0;
fail:
    av_free(buf);
    if (ret < 0) {
        if (codec_config)
            av_free(codec_config->extradata);
        av_free(codec_config);
    }
    return ret;
}

static int audio_element_obu(void *s, IAMFContext *c, AVIOContext *pb, int len)
{
    const IAMFCodecConfig *codec_config;
    AVIAMFAudioElement *element;
    IAMFAudioElement **tmp, *audio_element = NULL;
    FFIOContext b;
    AVIOContext *pbc;
    uint8_t *buf;
    unsigned audio_element_id, nb_substreams, codec_config_id, num_parameters;
    int audio_element_type, ret;

    buf = av_malloc(len);
    if (!buf)
        return AVERROR_ENOMEM;

    ret = ffio_read_size(pb, buf, len);
    if (ret < 0)
        goto fail;

    ffio_init_context(&b, buf, len, 0, NULL, NULL, NULL, NULL);
    pbc = &b.pub;

    audio_element_id = ffio_read_leb(pbc);

    for (int i = 0; i < c->nb_audio_elements; i++)
        if (c->audio_elements[i]->audio_element_id == audio_element_id) {
            av_log(s, AV_LOG_ERROR, "Duplicate audio_element_id %d\n", audio_element_id);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

    audio_element_type = avio_r8(pbc) >> 5;
    if (audio_element_type > AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE) {
        ret = 0;
        goto fail;
    }

    codec_config_id = ffio_read_leb(pbc);

    codec_config = ff_iamf_get_codec_config(c, codec_config_id);
    if (!codec_config) {
        av_log(s, AV_LOG_ERROR, "Non existant codec config id %d referenced in an audio element\n", codec_config_id);
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (codec_config->codec_id == AV_CODEC_ID_NONE) {
        ret = 0;
        goto fail;
    }

    tmp = av_realloc_array(c->audio_elements, c->nb_audio_elements + 1, sizeof(*c->audio_elements));
    if (!tmp) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    c->audio_elements = tmp;

    audio_element = av_mallocz(sizeof(*audio_element));
    if (!audio_element) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }

    nb_substreams = ffio_read_leb(pbc);
    audio_element->codec_config_id = codec_config_id;
    audio_element->audio_element_id = audio_element_id;
    audio_element->substreams = av_calloc(nb_substreams, sizeof(*audio_element->substreams));
    if (!audio_element->substreams) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    audio_element->nb_substreams = nb_substreams;

    element = audio_element->element = av_iamf_audio_element_alloc();
    if (!element) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    audio_element->celement = element;

    element->audio_element_type = audio_element_type;

    for (int i = 0; i < audio_element->nb_substreams; i++) {
        IAMFSubStream *substream = &audio_element->substreams[i];

        substream->codecpar = avcodec_parameters_alloc();
        if (!substream->codecpar) {
            ret = AVERROR_ENOMEM;
            goto fail;
        }

        substream->audio_substream_id = ffio_read_leb(pbc);

        substream->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        substream->codecpar->codec_id   = codec_config->codec_id;
        substream->codecpar->frame_size = codec_config->nb_samples;
        substream->codecpar->sample_rate = codec_config->sample_rate;
        substream->codecpar->seek_preroll = -codec_config->audio_roll_distance * codec_config->nb_samples;

        switch(substream->codecpar->codec_id) {
        case AV_CODEC_ID_AAC:
        case AV_CODEC_ID_FLAC:
        case AV_CODEC_ID_OPUS:
            substream->codecpar->extradata = av_malloc(codec_config->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!substream->codecpar->extradata) {
                ret = AVERROR_ENOMEM;
                goto fail;
            }
            memcpy(substream->codecpar->extradata, codec_config->extradata, codec_config->extradata_size);
            memset(substream->codecpar->extradata + codec_config->extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
            substream->codecpar->extradata_size = codec_config->extradata_size;
            break;
        }
    }

    num_parameters = ffio_read_leb(pbc);
    if (num_parameters && audio_element_type != 0) {
        av_log(s, AV_LOG_ERROR, "Audio Element parameter count %u is invalid"
                                " for Scene representations\n", num_parameters);
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    for (int i = 0; i < num_parameters; i++) {
        unsigned type;

        type = ffio_read_leb(pbc);
        if (type == AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN)
            ret = AVERROR_INVALIDDATA;
        else if (type == AV_IAMF_PARAMETER_DEFINITION_DEMIXING)
            ret = param_parse(s, c, pbc, type, audio_element, &element->demixing_info);
        else if (type == AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN)
            ret = param_parse(s, c, pbc, type, audio_element, &element->recon_gain_info);
        else {
            unsigned param_definition_size = ffio_read_leb(pbc);
            avio_skip(pbc, param_definition_size);
        }
        if (ret < 0)
            goto fail;
    }

    if (audio_element_type == AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL) {
        ret = scalable_channel_layout_config(s, pbc, audio_element, codec_config);
        if (ret < 0)
            goto fail;
    } else if (audio_element_type == AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE) {
        ret = ambisonics_config(s, pbc, audio_element, codec_config);
        if (ret < 0)
            goto fail;
    }

    c->audio_elements[c->nb_audio_elements++] = audio_element;

    len -= avio_tell(pbc);
    if (len)
       av_log(s, AV_LOG_WARNING, "Underread in audio_element_obu. %d bytes left at the end\n", len);

    ret = 0;
fail:
    av_free(buf);
    if (ret < 0)
        ff_iamf_free_audio_element(&audio_element);
    return ret;
}

static int mix_presentation_obu(void *s, IAMFContext *c, AVIOContext *pb, int len)
{
    AVIAMFMixPresentation *mix;
    IAMFMixPresentation **tmp, *mix_presentation = NULL;
    FFIOContext b;
    AVIOContext *pbc;
    uint8_t *buf;
    unsigned nb_submixes, mix_presentation_id;
    int ret;

    buf = av_malloc(len);
    if (!buf)
        return AVERROR_ENOMEM;

    ret = ffio_read_size(pb, buf, len);
    if (ret < 0)
        goto fail;

    ffio_init_context(&b, buf, len, 0, NULL, NULL, NULL, NULL);
    pbc = &b.pub;

    mix_presentation_id = ffio_read_leb(pbc);

    for (int i = 0; i < c->nb_mix_presentations; i++)
        if (c->mix_presentations[i]->mix_presentation_id == mix_presentation_id) {
            av_log(s, AV_LOG_ERROR, "Duplicate mix_presentation_id %d\n", mix_presentation_id);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

    tmp = av_realloc_array(c->mix_presentations, c->nb_mix_presentations + 1, sizeof(*c->mix_presentations));
    if (!tmp) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    c->mix_presentations = tmp;

    mix_presentation = av_mallocz(sizeof(*mix_presentation));
    if (!mix_presentation) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }

    mix_presentation->mix_presentation_id = mix_presentation_id;
    mix = mix_presentation->mix = av_iamf_mix_presentation_alloc();
    if (!mix) {
        ret = AVERROR_ENOMEM;
        goto fail;
    }
    mix_presentation->cmix = mix;

    mix_presentation->count_label = ffio_read_leb(pbc);
    mix_presentation->language_label = av_calloc(mix_presentation->count_label,
                                                 sizeof(*mix_presentation->language_label));
    if (!mix_presentation->language_label) {
        mix_presentation->count_label = 0;
        ret = AVERROR_ENOMEM;
        goto fail;
    }

    for (int i = 0; i < mix_presentation->count_label; i++) {
        ret = label_string(pbc, &mix_presentation->language_label[i]);
        if (ret < 0)
            goto fail;
    }

    for (int i = 0; i < mix_presentation->count_label; i++) {
        char *annotation = NULL;
        ret = label_string(pbc, &annotation);
        if (ret < 0)
            goto fail;
        ret = av_dict_set(&mix->annotations, mix_presentation->language_label[i], annotation,
                          AV_DICT_DONT_STRDUP_VAL | AV_DICT_DONT_OVERWRITE);
        if (ret < 0)
            goto fail;
    }

    nb_submixes = ffio_read_leb(pbc);
    for (int i = 0; i < nb_submixes; i++) {
        AVIAMFSubmix *sub_mix;
        unsigned nb_elements, nb_layouts;

        sub_mix = av_iamf_mix_presentation_add_submix(mix);
        if (!sub_mix) {
            ret = AVERROR_ENOMEM;
            goto fail;
        }

        nb_elements = ffio_read_leb(pbc);
        for (int j = 0; j < nb_elements; j++) {
            AVIAMFSubmixElement *submix_element;
            IAMFAudioElement *audio_element = NULL;
            unsigned int rendering_config_extension_size;

            submix_element = av_iamf_submix_add_element(sub_mix);
            if (!submix_element) {
                ret = AVERROR_ENOMEM;
                goto fail;
            }

            submix_element->audio_element_id = ffio_read_leb(pbc);

            for (int k = 0; k < c->nb_audio_elements; k++)
                if (c->audio_elements[k]->audio_element_id == submix_element->audio_element_id) {
                    audio_element = c->audio_elements[k];
                    break;
                }

            if (!audio_element) {
                av_log(s, AV_LOG_ERROR, "Invalid Audio Element with id %u referenced by Mix Parameters %u\n",
                       submix_element->audio_element_id, mix_presentation_id);
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }

            for (int k = 0; k < mix_presentation->count_label; k++) {
                char *annotation = NULL;
                ret = label_string(pbc, &annotation);
                if (ret < 0)
                    goto fail;
                ret = av_dict_set(&submix_element->annotations, mix_presentation->language_label[k], annotation,
                                  AV_DICT_DONT_STRDUP_VAL | AV_DICT_DONT_OVERWRITE);
                if (ret < 0)
                    goto fail;
            }

            submix_element->headphones_rendering_mode = avio_r8(pbc) >> 6;

            rendering_config_extension_size = ffio_read_leb(pbc);
            avio_skip(pbc, rendering_config_extension_size);

            ret = param_parse(s, c, pbc, AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN,
                              NULL,
                              &submix_element->element_mix_config);
            if (ret < 0)
                goto fail;
            submix_element->default_mix_gain = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);
        }

        ret = param_parse(s, c, pbc, AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN, NULL, &sub_mix->output_mix_config);
        if (ret < 0)
            goto fail;
        sub_mix->default_mix_gain = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);

        nb_layouts = ffio_read_leb(pbc);
        for (int j = 0; j < nb_layouts; j++) {
            AVIAMFSubmixLayout *submix_layout;
            int info_type;
            int byte = avio_r8(pbc);

            submix_layout = av_iamf_submix_add_layout(sub_mix);
            if (!submix_layout) {
                ret = AVERROR_ENOMEM;
                goto fail;
            }

            submix_layout->layout_type = byte >> 6;
            if (submix_layout->layout_type < AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS ||
                submix_layout->layout_type > AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL) {
                av_log(s, AV_LOG_ERROR, "Invalid Layout type %u in a submix from Mix Presentation %u\n",
                       submix_layout->layout_type, mix_presentation_id);
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            if (submix_layout->layout_type == 2) {
                int sound_system;
                sound_system = (byte >> 2) & 0xF;
                if (sound_system >= FF_ARRAY_ELEMS(ff_iamf_sound_system_map)) {
                    ret = AVERROR_INVALIDDATA;
                    goto fail;
                }
                av_channel_layout_copy(&submix_layout->sound_system, &ff_iamf_sound_system_map[sound_system].layout);
            } else
                submix_layout->sound_system = (AVChannelLayout)AV_CHANNEL_LAYOUT_BINAURAL;

            info_type = avio_r8(pbc);
            submix_layout->integrated_loudness = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);
            submix_layout->digital_peak = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);

            if (info_type & 1)
                submix_layout->true_peak = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);
            if (info_type & 2) {
                unsigned int num_anchored_loudness = avio_r8(pbc);

                for (int k = 0; k < num_anchored_loudness; k++) {
                    unsigned int anchor_element = avio_r8(pbc);
                    AVRational anchored_loudness = av_make_q(sign_extend(avio_rb16(pbc), 16), 1 << 8);
                    if (anchor_element == IAMF_ANCHOR_ELEMENT_DIALOGUE)
                        submix_layout->dialogue_anchored_loudness = anchored_loudness;
                    else if (anchor_element <= IAMF_ANCHOR_ELEMENT_ALBUM)
                        submix_layout->album_anchored_loudness = anchored_loudness;
                }
            }

            if (info_type & 0xFC) {
                unsigned int info_type_size = ffio_read_leb(pbc);
                avio_skip(pbc, info_type_size);
            }
        }
    }

    c->mix_presentations[c->nb_mix_presentations++] = mix_presentation;

    len -= avio_tell(pbc);
    if (len)
        av_log(s, AV_LOG_WARNING, "Underread in mix_presentation_obu. %d bytes left at the end\n", len);

    ret = 0;
fail:
    av_free(buf);
    if (ret < 0)
        ff_iamf_free_mix_presentation(&mix_presentation);
    return ret;
}

int ff_iamf_parse_obu_header(const uint8_t *buf, int buf_size,
                             unsigned *obu_size, int *start_pos, enum IAMF_OBU_Type *type,
                             unsigned *skip_samples, unsigned *discard_padding)
{
    GetBitContext gb;
    int ret, extension_flag, trimming, start;
    unsigned skip = 0, discard = 0;
    unsigned size;

    ret = init_get_bits8(&gb, buf, FFMIN(buf_size, MAX_IAMF_OBU_HEADER_SIZE));
    if (ret < 0)
        return ret;

    *type          = get_bits(&gb, 5);
    trimming       = get_bits1(&gb);
    extension_flag = get_bits1(&gb);

    *obu_size = get_leb(&gb);
    if (*obu_size > INT_MAX)
        return AVERROR_INVALIDDATA;

    start = get_bits_count(&gb) / 8;

    if (trimming) {
        discard = get_leb(&gb);
        skip = get_leb(&gb);
    }

    if (skip_samples)
        *skip_samples = skip;
    if (discard_padding)
        *discard_padding = discard;

    if (extension_flag) {
        unsigned int extension_bytes;
        extension_bytes = get_leb(&gb);
        if (extension_bytes > INT_MAX / 8)
            return AVERROR_INVALIDDATA;
    }

    size = *obu_size + start;
    if (size > INT_MAX)
        return AVERROR_INVALIDDATA;

    *obu_size -= get_bits_count(&gb) / 8 - start;
    *start_pos = size - *obu_size;

    return size;
}

int ff_iamfdec_read_descriptors(IAMFContext *c, AVIOContext *pb,
                                int max_size, void *log_ctx)
{
    uint8_t header[MAX_IAMF_OBU_HEADER_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    int ret;

    while (1) {
        unsigned obu_size;
        enum IAMF_OBU_Type type;
        int start_pos, len, size;

        if ((ret = ffio_ensure_seekback(pb, FFMIN(MAX_IAMF_OBU_HEADER_SIZE, max_size))) < 0)
            return ret;
        size = avio_read(pb, header, FFMIN(MAX_IAMF_OBU_HEADER_SIZE, max_size));
        if (size < 0)
            return size;
        memset(header + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

        len = ff_iamf_parse_obu_header(header, size, &obu_size, &start_pos, &type, NULL, NULL);
        if (len < 0 || obu_size > max_size) {
            av_log(log_ctx, AV_LOG_ERROR, "Failed to read obu header\n");
            avio_seek(pb, -size, SEEK_CUR);
            return len;
        }

        if (type >= IAMF_OBU_IA_PARAMETER_BLOCK && type < IAMF_OBU_IA_SEQUENCE_HEADER) {
            avio_seek(pb, -size, SEEK_CUR);
            break;
        }

        avio_seek(pb, -(size - start_pos), SEEK_CUR);
        switch (type) {
        case IAMF_OBU_IA_CODEC_CONFIG:
            ret = codec_config_obu(log_ctx, c, pb, obu_size);
            break;
        case IAMF_OBU_IA_AUDIO_ELEMENT:
            ret = audio_element_obu(log_ctx, c, pb, obu_size);
            break;
        case IAMF_OBU_IA_MIX_PRESENTATION:
            ret = mix_presentation_obu(log_ctx, c, pb, obu_size);
            break;
        default: {
            int64_t offset = avio_skip(pb, obu_size);
            if (offset < 0)
                ret = offset;
            break;
        }
        }
        if (ret < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Failed to read obu type %d\n", type);
            return ret;
        }
        max_size -= obu_size + start_pos;
        if (max_size < 0)
            return AVERROR_INVALIDDATA;
        if (!max_size)
            break;
    }

    return 0;
}

static int ambisonics_config(void *s, AVIOContext *pb,
                             IAMFAudioElement *audio_element,
                             const IAMFCodecConfig *codec_config)
{
    AVIAMFLayer *layer;
    unsigned ambisonics_mode;
    int output_channel_count, substream_count, order;
    int ret;

    ambisonics_mode = ffio_read_leb(pb);
    if (ambisonics_mode > 1)
        return 0;

    output_channel_count = avio_r8(pb);
    substream_count = avio_r8(pb);
    if (audio_element->nb_substreams != substream_count)
        return AVERROR_INVALIDDATA;

    order = floor(sqrt(output_channel_count - 1));
    if ((order + 1) * (order + 1) != output_channel_count)
        return AVERROR_INVALIDDATA;

    audio_element->layers = av_mallocz(sizeof(*audio_element->layers));
    if (!audio_element->layers)
        return AVERROR_ENOMEM;

    audio_element->nb_layers = 1;
    audio_element->layers->substream_count = substream_count;

    layer = av_iamf_audio_element_add_layer(audio_element->element);
    if (!layer)
        return AVERROR_ENOMEM;

    layer->ambisonics_mode = ambisonics_mode;
    if (ambisonics_mode == 0) {
        for (int i = 0; i < substream_count; i++) {
            IAMFSubStream *substream = &audio_element->substreams[i];

            substream->codecpar->ch_layout = (AVChannelLayout)AV_CHANNEL_LAYOUT_MONO;

            ret = update_extradata(substream->codecpar);
            if (ret < 0)
                return ret;
        }

        layer->ch_layout.order = AV_CHANNEL_ORDER_CUSTOM;
        layer->ch_layout.nb_channels = output_channel_count;
        layer->ch_layout.u.map = av_calloc(output_channel_count, sizeof(*layer->ch_layout.u.map));
        if (!layer->ch_layout.u.map)
            return AVERROR_ENOMEM;

        for (int i = 0; i < output_channel_count; i++)
            layer->ch_layout.u.map[i].id = avio_r8(pb) + AV_CHAN_AMBISONIC_BASE;
    } else {
        int coupled_substream_count = avio_r8(pb);
        int nb_demixing_matrix = substream_count + coupled_substream_count;
        int demixing_matrix_size = nb_demixing_matrix * output_channel_count;

        audio_element->layers->coupled_substream_count = coupled_substream_count;

        layer->ch_layout = (AVChannelLayout){ .order = AV_CHANNEL_ORDER_AMBISONIC, .nb_channels = output_channel_count };
        layer->demixing_matrix = av_malloc_array(demixing_matrix_size, sizeof(*layer->demixing_matrix));
        if (!layer->demixing_matrix)
            return AVERROR_ENOMEM;

        for (int i = 0; i < demixing_matrix_size; i++)
            layer->demixing_matrix[i] = av_make_q(sign_extend(avio_rb16(pb), 16), 1 << 8);

        for (int i = 0; i < substream_count; i++) {
            IAMFSubStream *substream = &audio_element->substreams[i];

            substream->codecpar->ch_layout = coupled_substream_count-- > 0 ? (AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO :
                                                                             (AVChannelLayout)AV_CHANNEL_LAYOUT_MONO;


            ret = update_extradata(substream->codecpar);
            if (ret < 0)
                return ret;
        }
    }

    return 0;
}

static int iamf_read_header(AVFormatContext *s)
{
    IAMFDemuxContext *const c = s->priv_data;
    IAMFContext *const iamf = &c->iamf;
    int ret;

    ret = ff_iamfdec_read_descriptors(iamf, s->pb, INT_MAX, s);
    if (ret < 0)
        return ret;

    for (int i = 0; i < iamf->nb_audio_elements; i++) {
        IAMFAudioElement *audio_element = iamf->audio_elements[i];
        AVStreamGroup *stg = avformat_stream_group_create(s, AV_STREAM_GROUP_PARAMS_IAMF_AUDIO_ELEMENT, NULL);

        if (!stg)
            return AVERROR_ENOMEM;

        av_iamf_audio_element_free(&stg->params.iamf_audio_element);
        stg->id = audio_element->audio_element_id;
        stg->params.iamf_audio_element = audio_element->element;
        audio_element->element = NULL;

        for (int j = 0; j < audio_element->nb_substreams; j++) {
            IAMFSubStream *substream = &audio_element->substreams[j];
            AVStream *st = avformat_new_stream(s, NULL);

            if (!st)
                return AVERROR_ENOMEM;

            ret = avformat_stream_group_add_stream(stg, st);
            if (ret < 0)
                return ret;

            ret = avcodec_parameters_copy(st->codecpar, substream->codecpar);
            if (ret < 0)
                return ret;

            if (!i && !j && audio_element->layers[0].substream_count == 1)
                st->disposition |= AV_DISPOSITION_DEFAULT;
            else
                st->disposition |= AV_DISPOSITION_DEPENDENT;
            st->id = substream->audio_substream_id;
        }
    }

    for (int i = 0; i < iamf->nb_mix_presentations; i++) {
        IAMFMixPresentation *mix_presentation = iamf->mix_presentations[i];
        AVStreamGroup *stg = avformat_stream_group_create(s, AV_STREAM_GROUP_PARAMS_IAMF_MIX_PRESENTATION, NULL);
        const AVIAMFMixPresentation *mix = mix_presentation->cmix;

        if (!stg)
            return AVERROR_ENOMEM;

        av_iamf_mix_presentation_free(&stg->params.iamf_mix_presentation);
        stg->id = mix_presentation->mix_presentation_id;
        stg->params.iamf_mix_presentation = mix_presentation->mix;
        mix_presentation->mix = NULL;

        for (int j = 0; j < mix->nb_submixes; j++) {
            const AVIAMFSubmix *sub_mix = mix->submixes[j];

            for (int k = 0; k < sub_mix->nb_elements; k++) {
                const AVIAMFSubmixElement *submix_element = sub_mix->elements[k];
                AVStreamGroup *audio_element = NULL;

                for (int l = 0; l < s->nb_stream_groups; l++) {
                    AVStreamGroup *sg = (AVStreamGroup*)s->stream_groups[l];
                    if (sg->type == AV_STREAM_GROUP_PARAMS_IAMF_AUDIO_ELEMENT &&
                        sg->id == submix_element->audio_element_id) {
                        audio_element = sg;
                        break;
                    }
                }

                for (int l = 0; l < audio_element->nb_streams; l++) {
                    ret = avformat_stream_group_add_stream(stg, (AVStream*)audio_element->streams[l]);
                    if (ret < 0 && ret != AVERROR(EEXIST))
                        return ret;
                }
            }
        }
    }

    return 0;
}
