#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA (-1)
#define AVERROR_ENOMEM (-2)
#define ENOMEM 12

#define av_malloc_attrib __attribute__((__malloc__))
#define av_alloc_size(a) __attribute__((alloc_size(a)))
#define av_always_inline static inline __attribute__((always_inline))

#define av_assert0(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)

#define AV_LOG_ERROR 16
#define AV_LOG_VERBOSE 24

typedef struct AVClass {
    const char *class_name;
    const char *(*item_name)(void *);
    const char *version;
    const void *option;
    void *child_next;
    void *child_class_iterate;
    void *child_next_deprecated;
    void *category;
    void *compare_values;
    void *version_offset;
    void *parent_log_context_offset;
} AVClass;

const char* av_default_item_name(void *ctx);

void av_log(void *avcl, int level, const char *fmt, ...);

void *av_mallocz(size_t size) av_malloc_attrib av_alloc_size(1);
void av_free(void *ptr);
void *av_realloc_array(void *ptr, size_t nmemb, size_t size);
void av_freep(void *ptr);

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVChannelLayout {
    int nb_channels;
    int order;
    uint64_t mask;
    void *u;
} AVChannelLayout;

typedef struct AVDictionary AVDictionary;

#define AV_OPT_FLAG_ENCODING_PARAM 0x0002
#define AV_OPT_TYPE_UINT 1
#define AV_OPT_TYPE_INT 2
#define AV_OPT_TYPE_RATIONAL 3
#define AV_OPT_TYPE_FLAGS 4
#define AV_OPT_TYPE_CHLAYOUT 7
#define AV_OPT_TYPE_DICT 8
#define AV_OPT_TYPE_CONST (1 << 18)

typedef struct AVOption {
    const char *name;
    const char *help;
    int offset;
    int type;
    union {
        int64_t i64;
        double dbl;
        const char *str;
    } default_val;
    double min;
    double max;
    int flags;
    const char *unit;
} AVOption;

void av_opt_set_defaults(void *s);
void av_opt_free(void *obj);

typedef struct AVIOContext AVIOContext;
unsigned long long avio_r8(AVIOContext *s);
unsigned int avio_rb16(AVIOContext *s);
unsigned int avio_rb32(AVIOContext *s);
int64_t avio_tell(AVIOContext *s);
int64_t avio_skip(AVIOContext *s, int64_t offset);

unsigned int ffio_read_leb(AVIOContext *s);

enum AVIAMFAnimationType {
    AV_IAMF_ANIMATION_TYPE_STEP,
    AV_IAMF_ANIMATION_TYPE_LINEAR,
    AV_IAMF_ANIMATION_TYPE_BEZIER,
};

typedef struct AVIAMFMixGain {
    const AVClass *av_class;
    unsigned int subblock_duration;
    enum AVIAMFAnimationType animation_type;
    AVRational start_point_value;
    AVRational end_point_value;
    AVRational control_point_value;
    AVRational control_point_relative_time;
} AVIAMFMixGain;

typedef struct AVIAMFDemixingInfo {
    const AVClass *av_class;
    unsigned int subblock_duration;
    unsigned int dmixp_mode;
} AVIAMFDemixingInfo;

typedef struct AVIAMFReconGain {
    const AVClass *av_class;
    unsigned int subblock_duration;
    uint8_t recon_gain[6][12];
} AVIAMFReconGain;

enum AVIAMFParamDefinitionType {
    AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN,
    AV_IAMF_PARAMETER_DEFINITION_DEMIXING,
    AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN,
};

typedef struct AVIAMFParamDefinition {
    const AVClass *av_class;
    size_t subblocks_offset;
    size_t subblock_size;
    unsigned int nb_subblocks;
    enum AVIAMFParamDefinitionType type;
    unsigned int parameter_id;
    unsigned int parameter_rate;
    unsigned int duration;
    unsigned int constant_subblock_duration;
} AVIAMFParamDefinition;

av_always_inline void*
av_iamf_param_definition_get_subblock(const AVIAMFParamDefinition *par, unsigned int idx)
{
    av_assert0(idx < par->nb_subblocks);
    return (void *)((uint8_t *)par + par->subblocks_offset + idx * par->subblock_size);
}

enum AVIAMFAmbisonicsMode {
    AV_IAMF_AMBISONICS_MODE_MONO,
    AV_IAMF_AMBISONICS_MODE_PROJECTION,
};

#define AV_IAMF_LAYER_FLAG_RECON_GAIN (1 << 0)

typedef struct AVIAMFLayer {
    const AVClass *av_class;
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
    const AVClass *av_class;
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
    const AVClass *av_class;
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
    const AVClass *av_class;
    enum AVIAMFSubmixLayoutType layout_type;
    AVChannelLayout sound_system;
    AVRational integrated_loudness;
    AVRational digital_peak;
    AVRational true_peak;
    AVRational dialogue_anchored_loudness;
    AVRational album_anchored_loudness;
} AVIAMFSubmixLayout;

typedef struct AVIAMFSubmix {
    const AVClass *av_class;
    AVIAMFSubmixElement **elements;
    unsigned int nb_elements;
    AVIAMFSubmixLayout **layouts;
    unsigned int nb_layouts;
    AVIAMFParamDefinition *output_mix_config;
    AVRational default_mix_gain;
} AVIAMFSubmix;

typedef struct AVIAMFMixPresentation {
    const AVClass *av_class;
    AVIAMFSubmix **submixes;
    unsigned int nb_submixes;
    AVDictionary *annotations;
} AVIAMFMixPresentation;

typedef struct IAMFAudioElement {
    const AVIAMFAudioElement *celement;
    AVIAMFAudioElement *element;
    unsigned int audio_element_id;
    void *substreams;
    unsigned int nb_substreams;
    unsigned int codec_config_id;
    void *layers;
    unsigned int nb_layers;
} IAMFAudioElement;

typedef struct IAMFParamDefinition {
    const IAMFAudioElement *audio_element;
    AVIAMFParamDefinition *param;
    int mode;
    size_t param_size;
} IAMFParamDefinition;

typedef struct IAMFContext {
    void **codec_configs;
    int nb_codec_configs;
    IAMFAudioElement **audio_elements;
    int nb_audio_elements;
    void **mix_presentations;
    int nb_mix_presentations;
    IAMFParamDefinition **param_definitions;
    int nb_param_definitions;
} IAMFContext;

const char* av_default_item_name(void *ctx) { return "stub"; }
void av_log(void *avcl, int level, const char *fmt, ...) { }
void *av_mallocz(size_t size) { return malloc(size); }
void av_free(void *ptr) { free(ptr); }
void *av_realloc_array(void *ptr, size_t nmemb, size_t size) { return realloc(ptr, nmemb * size); }
void av_freep(void *ptr) { if (ptr) { *(void**)ptr = NULL; } }
void av_opt_set_defaults(void *s) { }
void av_opt_free(void *obj) { }
unsigned long long avio_r8(AVIOContext *s) { return 0; }
unsigned int avio_rb16(AVIOContext *s) { return 0; }
unsigned int avio_rb32(AVIOContext *s) { return 0; }
int64_t avio_tell(AVIOContext *s) { return 0; }
int64_t avio_skip(AVIOContext *s, int64_t offset) { return 0; }
unsigned int ffio_read_leb(AVIOContext *s) { return 0; }

static const AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .item_name      = av_default_item_name,
};

static const AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .item_name      = av_default_item_name,
};

static const AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .item_name      = av_default_item_name,
};

static const AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .item_name           = av_default_item_name,
};

AVIAMFParamDefinition *av_iamf_param_definition_alloc(enum AVIAMFParamDefinitionType type,
                                                      unsigned int nb_subblocks, size_t *out_size)
{

    struct MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    struct DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    struct ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_offset, subblock_size;
    size_t size;
    AVIAMFParamDefinition *par;

    switch (type) {
    case AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_offset = offsetof(struct MixGainStruct, m);
        subblock_size = sizeof(AVIAMFMixGain);
        break;
    case AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_offset = offsetof(struct DemixStruct, d);
        subblock_size = sizeof(AVIAMFDemixingInfo);
        break;
    case AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_offset = offsetof(struct ReconGainStruct, r);
        subblock_size = sizeof(AVIAMFReconGain);
        break;
    default:
        return NULL;
    }

    size = subblocks_offset;
    if (nb_subblocks > (SIZE_MAX - size) / subblock_size)
        return NULL;
    size += subblock_size * nb_subblocks;

    par = av_mallocz(size);
    if (!par)
        return NULL;

    par->av_class = &param_definition_class;
    av_opt_set_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_size = subblock_size;
    par->subblocks_offset = subblocks_offset;

    for (int i = 0; i < nb_subblocks; i++) {
        void *subblock = av_iamf_param_definition_get_subblock(par, i);

        switch (type) {
        case AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            break;
        case AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            break;
        case AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            break;
        default:
            av_assert0(0);
        }

        av_opt_set_defaults(subblock);
    }

    if (out_size)
        *out_size = size;

    return par;
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
    unsigned int total_duration = 0;
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
        else {
            nb_subblocks = duration / constant_subblock_duration;
            total_duration = duration;
        }
    }

    param = av_iamf_param_definition_alloc(type, nb_subblocks, &param_size);
    if (!param)
        return AVERROR(ENOMEM);

    for (int i = 0; i < nb_subblocks; i++) {
        void *subblock = av_iamf_param_definition_get_subblock(param, i);
        unsigned int subblock_duration = constant_subblock_duration;

        if (constant_subblock_duration == 0) {
            subblock_duration = ffio_read_leb(pb);
            total_duration += subblock_duration;
        } else if (i == nb_subblocks - 1)
            subblock_duration = duration - i * constant_subblock_duration;

        switch (type) {
        case AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN: {
            AVIAMFMixGain *mix = subblock;
            mix->subblock_duration = subblock_duration;
            break;
        }
        case AV_IAMF_PARAMETER_DEFINITION_DEMIXING: {
            AVIAMFDemixingInfo *demix = subblock;
            demix->subblock_duration = subblock_duration;
            // DefaultDemixingInfoParameterData
            av_assert0(audio_element);
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

    if (!mode && !constant_subblock_duration && total_duration != duration) {
        av_log(s, AV_LOG_ERROR, "Invalid subblock durations in parameter_id %u\n", parameter_id);
        av_free(param);
        return AVERROR_INVALIDDATA;
    }

    param->parameter_id = parameter_id;
    param->parameter_rate = parameter_rate;
    param->duration = duration;
    param->constant_subblock_duration = constant_subblock_duration;
    param->nb_subblocks = nb_subblocks;

    if (param_definition) {
        if (param_definition->param_size != param_size || memcmp(param_definition->param, param, param_size)) {
            av_log(s, AV_LOG_ERROR, "Incosistent parameters for parameter_id %u\n", parameter_id);
            av_free(param);
            return AVERROR_INVALIDDATA;
        }
    } else {
        IAMFParamDefinition **tmp = av_realloc_array(c->param_definitions, c->nb_param_definitions + 1,
                                                     sizeof(*c->param_definitions));
        if (!tmp) {
            av_free(param);
            return AVERROR(ENOMEM);
        }
        c->param_definitions = tmp;

        param_definition = av_mallocz(sizeof(*param_definition));
        if (!param_definition) {
            av_free(param);
            return AVERROR(ENOMEM);
        }
        param_definition->param = param;
        param_definition->mode = !mode;
        param_definition->param_size = param_size;
        param_definition->audio_element = audio_element;

        c->param_definitions[c->nb_param_definitions++] = param_definition;
    }

    av_assert0(out_param_definition);
    *out_param_definition = param;

    return 0;
}
