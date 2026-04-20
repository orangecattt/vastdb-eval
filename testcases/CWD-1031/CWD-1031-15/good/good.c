#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define av_const __attribute__((const))
#define av_always_inline __attribute__((always_inline))
#define av_unused __attribute__((unused))

#define AV_STRINGIFY(x) AV_TOSTRING(x)
#define AV_TOSTRING(x) #x

#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

av_const int av_log2(unsigned v);

#define av_assert0(cond) do { if (!(cond)) __builtin_unreachable(); } while(0)

#define AV_LOG_VERBOSE 24
#define AV_LOG_DEBUG 48
#define AV_LOG_ERROR 16
#define AV_LOG_INFO 32

#define AV_NOPTS_VALUE ((int64_t)UINT64_C(0x8000000000000000))

enum AVRounding {
    AV_ROUND_ZERO     = 0,
    AV_ROUND_INF      = 1,
    AV_ROUND_DOWN     = 2,
    AV_ROUND_UP       = 3,
    AV_ROUND_NEAR_INF = 5,
};

typedef struct AVRational {
    int num;
    int den;
} AVRational;

extern int64_t av_rescale(int64_t a, int64_t b, int64_t c) av_const;
extern int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, enum AVRounding rnd) av_const;

av_const uint16_t av_clip_uint16_c(int a);
#define av_clip_uint16 av_clip_uint16_c

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
};

enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_MPEG2VIDEO,
    AV_CODEC_ID_DNXHD,
    AV_CODEC_ID_PRORES,
    AV_CODEC_ID_DVVIDEO,
    AV_CODEC_ID_H264,
    AV_CODEC_ID_PCM_S24LE,
    AV_CODEC_ID_PCM_S16LE,
    /* ... other codecs ... */
};

typedef struct AVProfile {
    int profile;
    const char *name;
} AVProfile;

#define FF_PROFILE_PRORES_PROXY     0
#define FF_PROFILE_PRORES_LT        1
#define FF_PROFILE_PRORES_STANDARD  2
#define FF_PROFILE_PRORES_HQ        3
#define FF_PROFILE_PRORES_4444      4
#define FF_PROFILE_PRORES_XQ        5

#define FF_PROFILE_UNKNOWN (-99)

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB,
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1,
    AVCOL_RANGE_JPEG        = 2,
    AVCOL_RANGE_NB          = 3,
};

enum AVPacketSideDataType {
    AV_PKT_DATA_PALETTE,
    AV_PKT_DATA_NEW_EXTRADATA,
    AV_PKT_DATA_PARAM_CHANGE,
    AV_PKT_DATA_H263_MB_INFO,
    AV_PKT_DATA_REPLAYGAIN,
    AV_PKT_DATA_DISPLAYMATRIX,
    AV_PKT_DATA_STEREO3D,
    AV_PKT_DATA_AUDIO_SERVICE_TYPE,
    AV_PKT_DATA_QUALITY_STATS,
    AV_PKT_DATA_FALLBACK_TRACK,
    AV_PKT_DATA_CPB_PROPERTIES,
    AV_PKT_DATA_REFERCING_FRAME,
    AV_PKT_DATA_SKIP_SAMPLES,
    AV_PKT_DATA_JP_DUALMONO,
    AV_PKT_DATA_STRINGS_METADATA,
    AV_PKT_DATA_SUBTITLE_POSITION,
    AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL,
    AV_PKT_DATA_WEBVTT_IDENTIFIER,
    AV_PKT_DATA_WEBVTT_SETTINGS,
    AV_PKT_DATA_METADATA_UPDATE,
    AV_PKT_DATA_MPEGTS_STREAM_ID,
    AV_PKT_DATA_MASTERING_DISPLAY_METADATA,
    AV_PKT_DATA_SPHERICAL,
    AV_PKT_DATA_CONTENT_LIGHT_LEVEL,
    AV_PKT_DATA_ICC_PROFILE,
    AV_PKT_DATA_DOVI_CONF,
    AV_PKT_DATA_ENCRYPTION_INIT_INFO,
    AV_PKT_DATA_ENCRYPTION_INFO,
    AV_PKT_DATA_A53_CC,
    AV_PKT_DATA_AFD,
    AV_PKT_DATA_PRFT,
    AV_PKT_DATA_NB,
};

typedef struct AVMasteringDisplayMetadata {
    AVRational display_primaries[3][2];
    AVRational white_point[2];
    AVRational min_luminance;
    AVRational max_luminance;
    int has_primaries;
    int has_luminance;
} AVMasteringDisplayMetadata;

typedef struct AVBufferRef {
    uint8_t *data;
    size_t size;
    /* ... internal fields ... */
} AVBufferRef;

typedef struct AVPacket {
    int stream_index;
    int flags;
    uint8_t *data;
    int size;
    int64_t pts;
    int64_t dts;
    int64_t duration;
    int64_t pos;
    int64_t side_data_elems;
    struct {
        enum AVPacketSideDataType type;
        uint8_t *data;
        size_t size;
    } *side_data;
} AVPacket;

typedef struct AVCodecParameters {
    enum AVMediaType codec_type;
    enum AVCodecID codec_id;
    enum AVPixelFormat format;
    int width;
    int height;
    int profile;
    int color_primaries;
    int color_trc;
    int color_space;
    int color_range;
    uint8_t *extradata;
    int extradata_size;
    /* ... other fields ... */
} AVCodecParameters;

typedef struct AVDictionary {
    int count;
    struct AVDictionaryEntry **elems;
} AVDictionary;

typedef struct AVDictionaryEntry {
    char *key;
    char *value;
} AVDictionaryEntry;

typedef struct AVDictionaryEntry AVDictionaryEntry;

typedef struct AVStream {
    int index;
    int id;
    void *priv_data;
    AVRational time_base;
    AVCodecParameters *codecpar;
    AVRational sample_aspect_ratio;
    AVDictionary *metadata;
    /* ... other fields ... */
} AVStream;

typedef struct AVIOContext {
    uint8_t *buffer;
    int buffer_size;
    uint8_t *buf_ptr;
    uint8_t *buf_end;
    uint8_t *buf_start;
    /* ... other fields ... */
} AVIOContext;

typedef struct AVClass {
    const char *class_name;
    /* ... other fields ... */
} AVClass;

typedef struct AVOutputFormat {
    const char *name;
    const char *long_name;
    /* ... other fields ... */
} AVOutputFormat;

typedef struct AVFormatContext {
    const AVClass *av_class;
    const AVOutputFormat *oformat;
    void *priv_data;
    AVIOContext *pb;
    int nb_streams;
    AVStream **streams;
    AVDictionary *metadata;
    int flags;
    /* ... other fields ... */
} AVFormatContext;

#define AVFMT_FLAG_BITEXACT 0x00100000

extern uint8_t *av_stream_get_side_data(const AVStream *st,
                                        enum AVPacketSideDataType type,
                                        size_t *size);
extern AVDictionaryEntry *av_dict_get(const AVDictionary *dict,
                                       const char *key,
                                       const AVDictionaryEntry *prev,
                                       int flags);
extern void av_log(void *avcl, int level, const char *fmt, ...);

typedef uint8_t UID[16];

enum MXFMetadataSetType {
    AnyType,
    MaterialPackage,
    SourcePackage,
    SourceClip,
    TimecodeComponent,
    PulldownComponent,
    Sequence,
    MultipleDescriptor,
    Descriptor,
    Track,
    CryptoContext,
    Preface,
    Identification,
    ContentStorage,
    SubDescriptor,
    IndexTableSegment,
    EssenceContainerData,
    EssenceGroup,
    TaggedValue,
    TapeDescriptor,
    AVCSubDescriptor,
};

enum MXFFrameLayout {
    FullFrame = 0,
    SeparateFields,
    OneField,
    MixedFields,
    SegmentedFrame,
};

typedef struct MXFCodecUL {
    UID uid;
    unsigned matching_len;
    int id;
    const char *desc;
    unsigned wrapping_indicator_pos;
    /* ... other fields ... */
} MXFCodecUL;

typedef struct MXFLocalTagPair {
    int local_tag;
    UID uid;
} MXFLocalTagPair;

#define FF_MXF_MASTERING_CHROMA_DEN 50000
#define FF_MXF_MASTERING_LUMA_DEN   10000

typedef struct KLVPacket {
    UID key;
    int64_t offset;
    uint64_t length;
    int64_t next_klv;
} KLVPacket;

typedef struct MXFStreamContext {
    int64_t pkt_cnt;
    UID track_essence_element_key;
    int index;
    const UID *codec_ul;
    const UID *container_ul;
    int order;
    int interlaced;
    int field_dominance;
    int component_depth;
    int color_siting;
    int signal_standard;
    int h_chroma_sub_sample;
    int v_chroma_sub_sample;
    int temporal_reordering;
    AVRational aspect_ratio;
    int closed_gop;
    int video_bit_rate;
    int slice_offset;
    int frame_size;
    int seq_closed_gop;
    int max_gop;
    int b_picture_count;
    int low_delay;
    int avc_intra;
} MXFStreamContext;

typedef struct MXFContainerEssenceEntry {
    UID container_ul;
    UID element_ul;
    UID codec_ul;
    void (*write_desc)(AVFormatContext *, AVStream *);
} MXFContainerEssenceEntry;

typedef struct MXFPackage {
    char *name;
    enum MXFMetadataSetType type;
    int instance;
    struct MXFPackage *ref;
} MXFPackage;

typedef struct MXFIndexEntry {
    uint64_t offset;
    unsigned slice_offset;
    uint16_t temporal_ref;
    uint8_t flags;
} MXFIndexEntry;

typedef struct MXFContext {
    AVClass *av_class;
    int64_t footer_partition_offset;
    int essence_container_count;
    AVRational time_base;
    int header_written;
    MXFIndexEntry *index_entries;
    unsigned edit_units_count;
    uint64_t timestamp;
    uint8_t slice_count;
    int last_indexed_edit_unit;
    uint64_t *body_partition_offset;
    unsigned body_partitions_count;
    int last_key_index;
    uint64_t duration;
    void *tc;
    AVStream *timecode_track;
    int timecode_base;
    int edit_unit_byte_count;
    int content_package_rate;
    uint64_t body_offset;
    uint32_t instance_number;
    uint8_t umid[16];
    int channel_count;
    int signal_standard;
    uint32_t tagged_value_count;
    AVRational audio_edit_rate;
    int store_user_comments;
    int track_instance_count;
    int cbr_index;
    uint8_t unused_tags[100];
} MXFContext;

extern const MXFCodecUL ff_mxf_color_primaries_uls[];
extern const MXFCodecUL ff_mxf_color_trc_uls[];
extern const MXFCodecUL ff_mxf_color_space_uls[];
extern const MXFCodecUL ff_mxf_data_definition_uls[];

extern AVOutputFormat ff_mxf_d10_muxer;
extern AVOutputFormat ff_mxf_opatom_muxer;

enum AVIODataMarkerType {
    AVIO_DATA_MARKER_SYNC_POINT,
    AVIO_DATA_MARKER_BOUNDARY_POINT,
    AVIO_DATA_MARKER_FLUSH_POINT,
    AVIO_DATA_MARKER_UNINTERRUPTED,
    AVIO_DATA_MARKER_UNKNOWN,
};

extern void avio_write(struct AVIOContext *s, const uint8_t *buf, int size);
extern void avio_w8(struct AVIOContext *s, int b);
extern void avio_wb16(struct AVIOContext *s, unsigned int w);
extern void avio_wb24(struct AVIOContext *s, unsigned int w);
extern void avio_wb32(struct AVIOContext *s, unsigned int w);
extern void avio_wb64(struct AVIOContext *s, uint64_t w);
extern int64_t avio_tell(struct AVIOContext *s);
extern int64_t avio_seek(struct AVIOContext *s, int64_t offset, int whence);
extern int avio_put_str16be(struct AVIOContext *s, const char *str);
extern void avio_write_marker(struct AVIOContext *s, int64_t time, enum AVIODataMarkerType type);

#define KAG_SIZE 512
#define EDIT_UNITS_PER_BODY 250

static const uint8_t uuid_base[]            = { 0xAD,0xAB,0x44,0x24,0x2f,0x25,0x4d,0xc7,0x92,0xff,0x29,0xbd };
static const uint8_t umid_ul[]              = { 0x06,0x0A,0x2B,0x34,0x01,0x01,0x01,0x05,0x01,0x01,0x0D,0x00,0x13 };

static const uint8_t op1a_ul[]                     = { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x01,0x09,0x00 };
static const uint8_t opatom_ul[]                   = { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x02,0x0D,0x01,0x02,0x01,0x10,0x03,0x00,0x00,0x00 };
static const uint8_t footer_partition_key[]        = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x04,0x04,0x00 };
static const uint8_t primer_pack_key[]             = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x05,0x01,0x00 };
static const uint8_t index_table_segment_key[]     = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x02,0x01,0x01,0x10,0x01,0x00 };
static const uint8_t header_open_partition_key[]   = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x02,0x01,0x00 };
static const uint8_t header_closed_partition_key[] = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x02,0x04,0x00 };
static const uint8_t klv_fill_key[]                = { 0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x03,0x01,0x02,0x10,0x01,0x00,0x00,0x00 };
static const uint8_t body_partition_key[]          = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x03,0x04,0x00 };

static const uint8_t header_metadata_key[]  = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0D,0x01,0x01,0x01,0x01 };
static const uint8_t multiple_desc_ul[]     = { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x03,0x0D,0x01,0x03,0x01,0x02,0x7F,0x01,0x00 };

static const UID mxf_cdci_descriptor_key      = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0D,0x01,0x01,0x01,0x01,0x01,0x28,0x00 };
static const UID mxf_generic_sound_descriptor_key = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0D,0x01,0x01,0x01,0x01,0x01,0x42,0x00 };
static const UID mxf_avc_subdescriptor_key = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x6E,0x00 };

#define FF_MXF_MasteringDisplay_PREFIX 0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x0e,0x04,0x20,0x04,0x01,0x01
#define FF_MXF_MasteringDisplayPrimaries { FF_MXF_MasteringDisplay_PREFIX,0x01,0x00,0x00 }
#define FF_MXF_MasteringDisplayWhitePointChromaticity { FF_MXF_MasteringDisplay_PREFIX,0x02,0x00,0x00 }
#define FF_MXF_MasteringDisplayMaximumLuminance { FF_MXF_MasteringDisplay_PREFIX,0x03,0x00,0x00 }
#define FF_MXF_MasteringDisplayMinimumLuminance { FF_MXF_MasteringDisplay_PREFIX,0x04,0x00,0x00 }

static const MXFLocalTagPair mxf_local_tag_batch[] = {
    { 0x3C0A, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x01,0x01,0x01,0x15,0x02,0x00,0x00,0x00,0x00}},
    { 0x3B02, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x01,0x10,0x02,0x04,0x00,0x00}},
    { 0x3B05, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x03,0x01,0x02,0x01,0x05,0x00,0x00,0x00}},
    { 0x3B07, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x03,0x01,0x02,0x01,0x04,0x00,0x00,0x00}},
    { 0x3B06, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x06,0x04,0x00,0x00}},
    { 0x3B03, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x02,0x01,0x00,0x00}},
    { 0x3B09, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x05,0x01,0x02,0x02,0x03,0x00,0x00,0x00,0x00}},
    { 0x3B0A, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x05,0x01,0x02,0x02,0x10,0x02,0x01,0x00,0x00}},
    { 0x3B0B, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x05,0x01,0x02,0x02,0x10,0x02,0x02,0x00,0x00}},
    { 0x3C09, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x01,0x00,0x00,0x00}},
    { 0x3C01, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x02,0x01,0x00,0x00}},
    { 0x3C02, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x03,0x01,0x00,0x00}},
    { 0x3C03, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x04,0x00,0x00,0x00}},
    { 0x3C04, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x05,0x01,0x00,0x00}},
    { 0x3C05, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x07,0x00,0x00,0x00}},
    { 0x3C06, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x01,0x10,0x02,0x03,0x00,0x00}},
    { 0x3C07, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x0A,0x00,0x00,0x00}},
    { 0x3C08, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x20,0x07,0x01,0x06,0x01,0x00,0x00}},
    { 0x1901, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x05,0x01,0x00,0x00}},
    { 0x1902, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x05,0x02,0x00,0x00}},
    { 0x2701, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x06,0x01,0x00,0x00,0x00}},
    { 0x3F07, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x04,0x01,0x03,0x04,0x04,0x00,0x00,0x00,0x00}},
    { 0x4401, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x01,0x01,0x01,0x15,0x10,0x00,0x00,0x00,0x00}},
    { 0x4405, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x01,0x10,0x01,0x03,0x00,0x00}},
    { 0x4404, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x01,0x10,0x02,0x05,0x00,0x00}},
    { 0x4402, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x02,0x01,0x00,0x00,0x00}},
    { 0x4403, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x06,0x05,0x00,0x00}},
    { 0x4701, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x02,0x03,0x00,0x00}},
    { 0x4801, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x01,0x07,0x01,0x01,0x00,0x00,0x00,0x00}},
    { 0x4804, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x01,0x04,0x01,0x03,0x00,0x00,0x00,0x00}},
    { 0x4B01, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x05,0x30,0x04,0x05,0x00,0x00,0x00,0x00}},
    { 0x4B02, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x01,0x03,0x01,0x03,0x00,0x00}},
    { 0x4803, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x02,0x04,0x00,0x00}},
    { 0x0201, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x07,0x01,0x00,0x00,0x00,0x00,0x00}},
    { 0x0202, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x07,0x02,0x02,0x01,0x01,0x03,0x00,0x00}},
    { 0x1001, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x06,0x01,0x01,0x04,0x06,0x09,0x00,0x00}},
    { 0x3201, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x02,0x00,0x00}},
    { 0x3202, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x03,0x00,0x00}},
    { 0x3216, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0B,0x00,0x00}},
    { 0x3213, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x08,0x00,0x00}},
    { 0x3214, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x09,0x00,0x00}},
    { 0x3205, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x05,0x00,0x00}},
    { 0x3204, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x04,0x00,0x00}},
    { 0x3206, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x06,0x00,0x00}},
    { 0x3207, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x07,0x00,0x00}},
    { 0x3209, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x02,0x00,0x00}},
    { 0x3208, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0A,0x00,0x00}},
    { 0x320A, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0C,0x00,0x00}},
    { 0x320B, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0D,0x00,0x00}},
    { 0x3217, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0E,0x00,0x00}},
    { 0x3301, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x12,0x00,0x00}},
    { 0x3302, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x13,0x00,0x00}},
    { 0x3308, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x14,0x00,0x00}},
    { 0x3303, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x15,0x00,0x00}},
    { 0x3307, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x16,0x00,0x00}},
    { 0x3304, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x17,0x00,0x00}},
    { 0x3305, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x18,0x00,0x00}},
    { 0x3306, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x19,0x00,0x00}},
    { 0x3215, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0A,0x00,0x00}},
    { 0x320C, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x0F,0x00,0x00}},
    { 0x320D, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x1A,0x00,0x00}},
    { 0x320E, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x10,0x00,0x00}},
    { 0x3219, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x1B,0x00,0x00}},
    { 0x3210, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x1C,0x00,0x00}},
    { 0x321A, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x1D,0x00,0x00}},
    { 0x3212, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x02,0x04,0x01,0x02,0x02,0x01,0x1E,0x00,0x00}},
    { 0x8100, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x0E,0x04,0x01,0x06,0x06,0x01,0x02,0x00,0x00}},
    { 0x8200, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x0E,0x04,0x01,0x06,0x06,0x01,0x0E,0x00,0x00}},
    { 0x8201, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x0E,0x04,0x01,0x06,0x06,0x01,0x0A,0x00,0x00}},
    { 0x8202, {0x06,0x0E,0x2B,0x34,0x01,0x01,0x01,0x0E,0x04,0x01,0x06,0x06,0x01,0x0D,0x00,0x00}},
    { 0x8301, FF_MXF_MasteringDisplayPrimaries },
    { 0x8302, FF_MXF_MasteringDisplayWhitePointChromaticity },
    { 0x8303, FF_MXF_MasteringDisplayMaximumLuminance },
    { 0x8304, FF_MXF_MasteringDisplayMinimumLuminance },
};

#define MXF_NUM_TAGS FF_ARRAY_ELEMS(mxf_local_tag_batch)

static const struct {
    int profile;
    UID codec_ul;
} mxf_prores_codec_uls[] = {
    { FF_PROFILE_PRORES_PROXY,    { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x01,0x00 } },
    { FF_PROFILE_PRORES_LT,       { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x02,0x00 } },
    { FF_PROFILE_PRORES_STANDARD, { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x03,0x00 } },
    { FF_PROFILE_PRORES_HQ,       { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x04,0x00 } },
    { FF_PROFILE_PRORES_4444,     { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x05,0x00 } },
    { FF_PROFILE_PRORES_XQ,       { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x06,0x00 } },
};

int klv_ber_length(uint64_t len);
int klv_encode_ber_length(AVIOContext *pb, uint64_t len);
void klv_encode_ber4_length(AVIOContext *pb, int len);
unsigned klv_fill_size(uint64_t size);
uint64_t mxf_utf16len(const char *utf8_str);
static const MXFLocalTagPair* mxf_lookup_local_tag(int tag);
void mxf_write_local_tag(AVFormatContext *s, int size, int tag);
void mxf_write_refs_count(AVIOContext *pb, int ref_count);
void mxf_write_uuid(AVIOContext *pb, enum MXFMetadataSetType type, int value);
void mxf_write_umid(AVFormatContext *s, int type);
void mxf_write_metadata_key(AVIOContext *pb, unsigned int value);
void mxf_update_klv_size(AVIOContext *pb, int64_t pos);
const MXFCodecUL *mxf_get_codec_ul_by_id(const MXFCodecUL *uls, int id);
uint16_t rescale_mastering_chroma(AVRational q);
uint32_t rescale_mastering_luma(AVRational q);
void mxf_write_local_tag_utf16(AVFormatContext *s, int tag, const char *value);
void mxf_write_klv_fill(AVFormatContext *s);

int64_t mxf_write_generic_desc(AVFormatContext *s, AVStream *st, const UID key);
void mxf_write_track(AVFormatContext *s, AVStream *st, MXFPackage *package);
void mxf_write_sequence(AVFormatContext *s, AVStream *st, MXFPackage *package);
void mxf_write_timecode_component(AVFormatContext *s, AVStream *st, MXFPackage *package);
void mxf_write_structural_component(AVFormatContext *s, AVStream *st, MXFPackage *package);
void mxf_write_preface(AVFormatContext *s);
void mxf_write_identification(AVFormatContext *s);
void mxf_write_content_storage(AVFormatContext *s, MXFPackage *packages, int package_count);
void mxf_write_essence_container_data(AVFormatContext *s);
static void mxf_write_package(AVFormatContext *s, MXFPackage *package);
void mxf_write_tape_descriptor(AVFormatContext *s);
void mxf_write_multi_descriptor(AVFormatContext *s);
void mxf_write_avc_subdesc(AVFormatContext *s, AVStream *st);
void mxf_write_index_table_segment(AVFormatContext *s);
void mxf_write_system_item(AVFormatContext *s);
void mxf_write_d10_audio_packet(AVFormatContext *s, AVStream *st, AVPacket *pkt);

void mxf_write_mpegvideo_desc(AVFormatContext *s, AVStream *st);
void mxf_write_aes3_desc(AVFormatContext *s, AVStream *st);
void mxf_write_wav_desc(AVFormatContext *s, AVStream *st);
void mxf_write_h264_desc(AVFormatContext *s, AVStream *st);
void mxf_write_s436m_anc_desc(AVFormatContext *s, AVStream *st);
void mxf_write_generic_sound_desc(AVFormatContext *s, AVStream *st);
int mxf_utf16_local_tag_length(const char *utf8_str);
int mxf_write_user_comments(AVFormatContext *s, const AVDictionary *m);
void mxf_write_essence_container_refs(AVFormatContext *s);
void mxf_write_primer_pack(AVFormatContext *s);
int mxf_write_opatom_body_partition(AVFormatContext *s);
int mxf_parse_mpeg2_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt, MXFIndexEntry *ie);
int mxf_parse_dnxhd_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt);
int mxf_parse_dv_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt);
int mxf_parse_h264_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt, MXFIndexEntry *ie);
void mxf_compute_edit_unit_byte_count(AVFormatContext *s);

#define AV_DICT_IGNORE_SUFFIX 1
#define AVERROR_PATCHWELCOME (-553750699)

#ifdef DEBUG
#define PRINT_KEY(pc, s, x) av_log(pc, AV_LOG_DEBUG, "%s\n", s)
#else
#define PRINT_KEY(pc, s, x) do { } while(0)
#endif

#define DESCRIPTOR_COUNT(essence_container_count) \
    (essence_container_count > 1 ? essence_container_count + 1 : essence_container_count)

#define LIBAVFORMAT_VERSION_MAJOR 61
#define LIBAVFORMAT_VERSION_MINOR 3
#define LIBAVFORMAT_VERSION_MICRO 100

#ifndef OS_NAME
#define OS_NAME "Linux"
#endif

int av_reallocp_array(void *ptr, size_t nmemb, size_t size);

static int mxf_parse_prores_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt)
{
    MXFContext *mxf = s->priv_data;
    MXFStreamContext *sc = st->priv_data;
    int i, profile;

    if (mxf->header_written)
        return 1;

    profile = st->codecpar->profile;
    for (i = 0; i < FF_ARRAY_ELEMS(mxf_prores_codec_uls); i++) {
        if (profile == mxf_prores_codec_uls[i].profile) {
            sc->codec_ul = &mxf_prores_codec_uls[i].codec_ul;
            break;
        }
    }
    if (i == FF_ARRAY_ELEMS(mxf_prores_codec_uls))
        return 0;

    sc->frame_size = pkt->size;

    return 1;
}

static int64_t mxf_write_cdci_common(AVFormatContext *s, AVStream *st, const UID key)
{
    MXFStreamContext *sc = st->priv_data;
    AVIOContext *pb = s->pb;
    int stored_width = 0;
    int stored_height = (st->codecpar->height+15)/16*16;
    int display_height;
    int f1, f2;
    const MXFCodecUL *color_primaries_ul;
    const MXFCodecUL *color_trc_ul;
    const MXFCodecUL *color_space_ul;
    int64_t pos = mxf_write_generic_desc(s, st, key);
    uint8_t *side_data;

    color_primaries_ul = mxf_get_codec_ul_by_id(ff_mxf_color_primaries_uls, st->codecpar->color_primaries);
    color_trc_ul       = mxf_get_codec_ul_by_id(ff_mxf_color_trc_uls, st->codecpar->color_trc);
    color_space_ul     = mxf_get_codec_ul_by_id(ff_mxf_color_space_uls, st->codecpar->color_space);

    if (st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO) {
        if (st->codecpar->height == 1080)
            stored_width = 1920;
        else if (st->codecpar->height == 720)
            stored_width = 1280;
    }
    if (!stored_width)
        stored_width = (st->codecpar->width+15)/16*16;

    mxf_write_local_tag(s, 4, 0x3203);
    avio_wb32(pb, stored_width);

    mxf_write_local_tag(s, 4, 0x3202);
    avio_wb32(pb, stored_height>>sc->interlaced);

    if (s->oformat == &ff_mxf_d10_muxer) {
        //Stored F2 Offset
        mxf_write_local_tag(s, 4, 0x3216);
        avio_wb32(pb, 0);

        //Image Start Offset
        mxf_write_local_tag(s, 4, 0x3213);
        avio_wb32(pb, 0);

        //Image End Offset
        mxf_write_local_tag(s, 4, 0x3214);
        avio_wb32(pb, 0);
    }

    //Sampled width
    mxf_write_local_tag(s, 4, 0x3205);
    avio_wb32(pb, stored_width);

    //Samples height
    mxf_write_local_tag(s, 4, 0x3204);
    avio_wb32(pb, st->codecpar->height>>sc->interlaced);

    //Sampled X Offset
    mxf_write_local_tag(s, 4, 0x3206);
    avio_wb32(pb, 0);

    //Sampled Y Offset
    mxf_write_local_tag(s, 4, 0x3207);
    avio_wb32(pb, 0);

    mxf_write_local_tag(s, 4, 0x3209);
    avio_wb32(pb, stored_width);

    if (st->codecpar->height == 608) // PAL + VBI
        display_height = 576;
    else if (st->codecpar->height == 512)  // NTSC + VBI
        display_height = 486;
    else
        display_height = st->codecpar->height;

    mxf_write_local_tag(s, 4, 0x3208);
    avio_wb32(pb, display_height>>sc->interlaced);

    // display X offset
    mxf_write_local_tag(s, 4, 0x320A);
    avio_wb32(pb, 0);

    // display Y offset
    mxf_write_local_tag(s, 4, 0x320B);
    avio_wb32(pb, (st->codecpar->height - display_height)>>sc->interlaced);

    if (sc->interlaced) {
        //Display F2 Offset
        mxf_write_local_tag(s, 4, 0x3217);
        avio_wb32(pb, -((st->codecpar->height - display_height)&1));
    }

    // component depth
    mxf_write_local_tag(s, 4, 0x3301);
    avio_wb32(pb, sc->component_depth);

    // horizontal subsampling
    mxf_write_local_tag(s, 4, 0x3302);
    avio_wb32(pb, sc->h_chroma_sub_sample);

    // vertical subsampling
    mxf_write_local_tag(s, 4, 0x3308);
    avio_wb32(pb, sc->v_chroma_sub_sample);

    // color siting
    mxf_write_local_tag(s, 1, 0x3303);
    avio_w8(pb, sc->color_siting);

    // Padding Bits
    mxf_write_local_tag(s, 2, 0x3307);
    avio_wb16(pb, 0);

    if (st->codecpar->color_range != AVCOL_RANGE_UNSPECIFIED) {
        int black = 0,
            white = (1<<sc->component_depth) - 1,
            color = (1<<sc->component_depth);
        if (st->codecpar->color_range == AVCOL_RANGE_MPEG) {
            black = 1   << (sc->component_depth - 4);
            white = 235 << (sc->component_depth - 8);
            color = (14 << (sc->component_depth - 4)) + 1;
        }
        mxf_write_local_tag(s, 4, 0x3304);
        avio_wb32(pb, black);
        mxf_write_local_tag(s, 4, 0x3305);
        avio_wb32(pb, white);
        mxf_write_local_tag(s, 4, 0x3306);
        avio_wb32(pb, color);
    }

    if (sc->signal_standard) {
        mxf_write_local_tag(s, 1, 0x3215);
        avio_w8(pb, sc->signal_standard);
    }

    // frame layout
    mxf_write_local_tag(s, 1, 0x320C);
    avio_w8(pb, sc->interlaced);

    // video line map
    switch (st->codecpar->height) {
    case  576: f1 = 23; f2 = st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO ? 335 : 336; break;
    case  608: f1 =  7; f2 = 320; break;
    case  480: f1 = 20; f2 = st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO ? 285 : 283; break;
    case  512: f1 =  7; f2 = 270; break;
    case  720: f1 = 26; f2 =   0; break; // progressive
    case 1080: f1 = 21; f2 = 584; break;
    default:   f1 =  0; f2 =   0; break;
    }

    if (!sc->interlaced && f2) {
        f2  = 0;
        f1 *= 2;
    }


    mxf_write_local_tag(s, 16, 0x320D);
    avio_wb32(pb, 2);
    avio_wb32(pb, 4);
    avio_wb32(pb, f1);
    avio_wb32(pb, f2);

    mxf_write_local_tag(s, 8, 0x320E);
    avio_wb32(pb, sc->aspect_ratio.num);
    avio_wb32(pb, sc->aspect_ratio.den);

    if (color_primaries_ul->uid[0]) {
        mxf_write_local_tag(s, 16, 0x3219);
        avio_write(pb, color_primaries_ul->uid, 16);
    };

    if (color_trc_ul->uid[0]) {
        mxf_write_local_tag(s, 16, 0x3210);
        avio_write(pb, color_trc_ul->uid, 16);
    };

    if (color_space_ul->uid[0]) {
        mxf_write_local_tag(s, 16, 0x321A);
        avio_write(pb, color_space_ul->uid, 16);
    };

    mxf_write_local_tag(s, 16, 0x3201);
    avio_write(pb, *sc->codec_ul, 16);

    // Mastering Display metadata
    side_data = av_stream_get_side_data(st, AV_PKT_DATA_MASTERING_DISPLAY_METADATA, NULL);
    if (side_data) {
        const AVMasteringDisplayMetadata *metadata = (const AVMasteringDisplayMetadata*)side_data;
        if (metadata->has_primaries) {
            mxf_write_local_tag(s, 12, 0x8301);
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[0][0]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[0][1]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[1][0]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[1][1]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[2][0]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->display_primaries[2][1]));
            mxf_write_local_tag(s, 4, 0x8302);
            avio_wb16(pb, rescale_mastering_chroma(metadata->white_point[0]));
            avio_wb16(pb, rescale_mastering_chroma(metadata->white_point[1]));
        } else {
            av_log(NULL, AV_LOG_VERBOSE, "Not writing mastering display primaries. Missing data.\n");
        }
        if (metadata->has_luminance) {
            mxf_write_local_tag(s, 4, 0x8303);
            avio_wb32(pb, rescale_mastering_luma(metadata->max_luminance));
            mxf_write_local_tag(s, 4, 0x8304);
            avio_wb32(pb, rescale_mastering_luma(metadata->min_luminance));
        } else {
            av_log(NULL, AV_LOG_VERBOSE, "Not writing mastering display luminances. Missing data.\n");
        }
    }

    if (sc->interlaced && sc->field_dominance) {
        mxf_write_local_tag(s, 1, 0x3212);
        avio_w8(pb, sc->field_dominance);
    }

    if (st->codecpar->codec_id == AV_CODEC_ID_H264 && !sc->avc_intra) {
        // write avc sub descriptor ref
        mxf_write_local_tag(s, 8 + 16, 0x8100);
        mxf_write_refs_count(pb, 1);
        mxf_write_uuid(pb, AVCSubDescriptor, 0);
    }

    return pos;
}

static void mxf_write_cdci_desc(AVFormatContext *s, AVStream *st)
{
    int64_t pos = mxf_write_cdci_common(s, st, mxf_cdci_descriptor_key);
    mxf_update_klv_size(s->pb, pos);

    if (st->codecpar->codec_id == AV_CODEC_ID_H264) {
        mxf_write_avc_subdesc(s, st);
    }
}

static const MXFContainerEssenceEntry mxf_essence_container_uls[] = {
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x02,0x0D,0x01,0x03,0x01,0x02,0x04,0x60,0x01 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x15,0x01,0x05,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x03,0x04,0x01,0x02,0x02,0x01,0x00,0x00,0x00 },
      mxf_write_mpegvideo_desc },
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x06,0x03,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x16,0x01,0x03,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x04,0x02,0x02,0x01,0x00,0x00,0x00,0x00 },
      mxf_write_aes3_desc },
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x06,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x16,0x01,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x04,0x02,0x02,0x01,0x00,0x00,0x00,0x00 },
      mxf_write_wav_desc },
    // D-10 Video
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x01,0x01,0x01 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x05,0x01,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x04,0x01,0x02,0x02,0x01,0x02,0x01,0x01 },
      mxf_write_cdci_desc },
    // D-10 Audio
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x01,0x01,0x01 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x06,0x01,0x10,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x04,0x02,0x02,0x01,0x00,0x00,0x00,0x00 },
      mxf_write_generic_sound_desc },
    // DV
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x02,0x7F,0x01 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x18,0x01,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x04,0x01,0x02,0x02,0x02,0x00,0x00,0x00 },
      mxf_write_cdci_desc },
    // DNxHD
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x03,0x01,0x02,0x11,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x15,0x01,0x05,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0A,0x04,0x01,0x02,0x02,0x71,0x01,0x00,0x00 },
      mxf_write_cdci_desc },
    // JPEG2000
    { { 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x07,0x0d,0x01,0x03,0x01,0x02,0x0c,0x01,0x00 },
      { 0x06,0x0e,0x2b,0x34,0x01,0x02,0x01,0x01,0x0d,0x01,0x03,0x01,0x15,0x01,0x08,0x00 },
      { 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x07,0x04,0x01,0x02,0x02,0x03,0x01,0x01,0x00 },
      mxf_write_cdci_desc },
    // H.264
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0a,0x0D,0x01,0x03,0x01,0x02,0x10,0x60,0x01 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x15,0x01,0x05,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0a,0x04,0x01,0x02,0x02,0x01,0x00,0x00,0x00 },
      mxf_write_h264_desc },
    // S436M ANC
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0a,0x0D,0x01,0x03,0x01,0x02,0x0e,0x00,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x17,0x01,0x02,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0a,0x04,0x01,0x02,0x02,0x01,0x01,0x5C,0x00 },
      mxf_write_s436m_anc_desc },
    // ProRes
    { { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x0d,0x01,0x03,0x01,0x02,0x1c,0x01,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0d,0x01,0x03,0x01,0x15,0x01,0x17,0x00 },
      { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x02,0x02,0x03,0x06,0x03,0x00 },
      mxf_write_cdci_desc },
    { { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
      { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
      { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
      NULL },
};

static void mxf_write_package(AVFormatContext *s, MXFPackage *package)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int i, track_count = s->nb_streams+1;
    int name_size = mxf_utf16_local_tag_length(package->name);
    int user_comment_count = 0;

    if (package->type == MaterialPackage) {
        if (mxf->store_user_comments)
            user_comment_count = mxf_write_user_comments(s, s->metadata);
        mxf_write_metadata_key(pb, 0x013600);
        PRINT_KEY(s, "Material Package key", pb->buf_ptr - 16);
        klv_encode_ber_length(pb, 92 + name_size + (16*track_count) + (16*user_comment_count) + 12LL*mxf->store_user_comments);
    } else {
        mxf_write_metadata_key(pb, 0x013700);
        PRINT_KEY(s, "Source Package key", pb->buf_ptr - 16);
        klv_encode_ber_length(pb, 112 + name_size + (16*track_count) + 12LL*mxf->store_user_comments); // 20 bytes length for descriptor reference
    }

    // write uid
    mxf_write_local_tag(s, 16, 0x3C0A);
    mxf_write_uuid(pb, package->type, package->instance);
    av_log(s, AV_LOG_DEBUG, "package type:%d\n", package->type);
    PRINT_KEY(s, "package uid", pb->buf_ptr - 16);

    // write package umid
    mxf_write_local_tag(s, 32, 0x4401);
    mxf_write_umid(s, package->instance);
    PRINT_KEY(s, "package umid second part", pb->buf_ptr - 16);

    // package name
    if (name_size)
        mxf_write_local_tag_utf16(s, 0x4402, package->name);

    // package creation date
    mxf_write_local_tag(s, 8, 0x4405);
    avio_wb64(pb, mxf->timestamp);

    // package modified date
    mxf_write_local_tag(s, 8, 0x4404);
    avio_wb64(pb, mxf->timestamp);

    // write track refs
    mxf_write_local_tag(s, track_count*16 + 8, 0x4403);
    mxf_write_refs_count(pb, track_count);
    // these are the uuids of the tracks the will be written in mxf_write_track
    for (i = 0; i < track_count; i++)
        mxf_write_uuid(pb, Track,  mxf->track_instance_count + i);

    // write user comment refs
    if (mxf->store_user_comments) {
        mxf_write_local_tag(s, user_comment_count*16 + 8, 0x4406);
        mxf_write_refs_count(pb, user_comment_count);
        for (i = 0; i < user_comment_count; i++)
            mxf_write_uuid(pb, TaggedValue, mxf->tagged_value_count - user_comment_count + i);
    }

    // write multiple descriptor reference
    if (package->type == SourcePackage && package->instance == 1) {
        mxf_write_local_tag(s, 16, 0x4701);
        if (s->nb_streams > 1) {
            mxf_write_uuid(pb, MultipleDescriptor, 0);
            mxf_write_multi_descriptor(s);
        } else
            mxf_write_uuid(pb, SubDescriptor, 0);
    } else if (package->type == SourcePackage && package->instance == 2) {
        mxf_write_local_tag(s, 16, 0x4701);
        mxf_write_uuid(pb, TapeDescriptor, 0);
        mxf_write_tape_descriptor(s);
    }

    /*
     * for every 1 track in a package there is 1 sequence and 1 component.
     * all 3 of these elements share the same instance number for generating
     * there instance uuids. mxf->track_instance_count stores this value.
     * mxf->track_instance_count is incremented after a group of all 3 of
     * these elements are written.
     */

    // write timecode track
    mxf_write_track(s, mxf->timecode_track, package);
    mxf_write_sequence(s, mxf->timecode_track, package);
    mxf_write_timecode_component(s, mxf->timecode_track, package);
    mxf->track_instance_count++;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        mxf_write_track(s, st, package);
        mxf_write_sequence(s, st, package);
        mxf_write_structural_component(s, st, package);
        mxf->track_instance_count++;

        if (package->type == SourcePackage && package->instance == 1) {
            MXFStreamContext *sc = st->priv_data;
            mxf_essence_container_uls[sc->index].write_desc(s, st);
        }
    }
}

static int mxf_write_header_metadata_sets(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVDictionaryEntry *entry = NULL;
    AVStream *st = NULL;
    int i;
    MXFPackage packages[3] = {{0}};
    int package_count = 2;
    packages[0].type = MaterialPackage;
    packages[1].type = SourcePackage;
    packages[1].instance = 1;
    packages[0].ref = &packages[1];


    if (entry = av_dict_get(s->metadata, "material_package_name", NULL, 0))
       packages[0].name = entry->value;

    if (entry = av_dict_get(s->metadata, "file_package_name", NULL, 0)) {
        packages[1].name = entry->value;
    } else {
        /* check if any of the streams contain a file_package_name */
        for (i = 0; i < s->nb_streams; i++) {
            st = s->streams[i];
            if (entry = av_dict_get(st->metadata, "file_package_name", NULL, 0)) {
                packages[1].name = entry->value;
                break;
            }
        }
    }

    entry = av_dict_get(s->metadata, "reel_name", NULL, 0);
    if (entry) {
        packages[2].name = entry->value;
        packages[2].type = SourcePackage;
        packages[2].instance = 2;
        packages[1].ref = &packages[2];
        package_count = 3;
    }

    mxf_write_preface(s);
    mxf_write_identification(s);
    mxf_write_content_storage(s, packages, package_count);
    mxf->track_instance_count = 0;
    for (i = 0; i < package_count; i++)
        mxf_write_package(s, &packages[i]);
    mxf_write_essence_container_data(s);
    return 0;
}

static int mxf_write_partition(AVFormatContext *s, int bodysid,
                                int indexsid,
                                const uint8_t *key, int write_metadata)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t header_byte_count_offset;
    unsigned index_byte_count = 0;
    uint64_t partition_offset = avio_tell(pb);
    int err;

    if (!mxf->edit_unit_byte_count && mxf->edit_units_count)
        index_byte_count = 85 + 12+(s->nb_streams+1)*6 +
            12+mxf->edit_units_count*15;
    else if (mxf->edit_unit_byte_count && indexsid)
        index_byte_count = 80;

    if (index_byte_count) {
        index_byte_count += 16 + 4; // add encoded ber4 length
        index_byte_count += klv_fill_size(index_byte_count);
    }

    if (key && !memcmp(key, body_partition_key, 16)) {
        if ((err = av_reallocp_array(&mxf->body_partition_offset, mxf->body_partitions_count + 1,
                                     sizeof(*mxf->body_partition_offset))) < 0) {
            mxf->body_partitions_count = 0;
            return err;
        }
        mxf->body_partition_offset[mxf->body_partitions_count++] = partition_offset;
    }

    // write klv
    if (key)
        avio_write(pb, key, 16);
    else
        avio_write(pb, body_partition_key, 16);

    klv_encode_ber4_length(pb, 88 + 16LL * DESCRIPTOR_COUNT(mxf->essence_container_count));

    // write partition value
    avio_wb16(pb, 1); // majorVersion
    avio_wb16(pb, 3); // minorVersion
    avio_wb32(pb, KAG_SIZE); // KAGSize

    avio_wb64(pb, partition_offset); // ThisPartition

    if (key && !memcmp(key, body_partition_key, 16) && mxf->body_partitions_count > 1)
        avio_wb64(pb, mxf->body_partition_offset[mxf->body_partitions_count-2]); // PreviousPartition
    else if (key && !memcmp(key, footer_partition_key, 16) && mxf->body_partitions_count)
        avio_wb64(pb, mxf->body_partition_offset[mxf->body_partitions_count-1]); // PreviousPartition
    else
        avio_wb64(pb, 0);

    avio_wb64(pb, mxf->footer_partition_offset); // footerPartition

    // set offset
    header_byte_count_offset = avio_tell(pb);
    avio_wb64(pb, 0); // headerByteCount, update later

    // indexTable
    avio_wb64(pb, index_byte_count); // indexByteCount
    avio_wb32(pb, index_byte_count ? indexsid : 0); // indexSID

    // BodyOffset
    if (bodysid && mxf->edit_units_count && mxf->body_partitions_count && s->oformat != &ff_mxf_opatom_muxer)
        avio_wb64(pb, mxf->body_offset);
    else
        avio_wb64(pb, 0);

    avio_wb32(pb, bodysid); // bodySID

    // operational pattern
    if (s->oformat == &ff_mxf_opatom_muxer)
        avio_write(pb, opatom_ul, 16);
    else
        avio_write(pb, op1a_ul, 16);

    // essence container
    mxf_write_essence_container_refs(s);

    if (write_metadata) {
        // mark the start of the headermetadata and calculate metadata size
        int64_t pos, start;
        unsigned header_byte_count;

        mxf_write_klv_fill(s);
        start = avio_tell(s->pb);
        mxf_write_primer_pack(s);
        mxf_write_klv_fill(s);
        mxf_write_header_metadata_sets(s);
        pos = avio_tell(s->pb);
        header_byte_count = pos - start + klv_fill_size(pos);

        // update header_byte_count
        avio_seek(pb, header_byte_count_offset, SEEK_SET);
        avio_wb64(pb, header_byte_count);
        avio_seek(pb, pos, SEEK_SET);
    }

    if(key)
        avio_write_marker(pb, AV_NOPTS_VALUE, AVIO_DATA_MARKER_FLUSH_POINT);

    return 0;
}

static int mxf_write_opatom_packet(AVFormatContext *s, AVPacket *pkt, MXFIndexEntry *ie)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;

    int err;

    if (!mxf->header_written) {
        if ((err = mxf_write_partition(s, 0, 0, header_open_partition_key, 1)) < 0)
            return err;
        mxf_write_klv_fill(s);

        if ((err = mxf_write_opatom_body_partition(s)) < 0)
            return err;
        mxf->header_written = 1;
    }

    if (!mxf->edit_unit_byte_count) {
        mxf->index_entries[mxf->edit_units_count].offset = mxf->body_offset;
        mxf->index_entries[mxf->edit_units_count].flags = ie->flags;
        mxf->index_entries[mxf->edit_units_count].temporal_ref = ie->temporal_ref;
    }
    mxf->edit_units_count++;
    avio_write(pb, pkt->data, pkt->size);
    mxf->body_offset += pkt->size;

    return 0;
}

static int mxf_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[pkt->stream_index];
    MXFStreamContext *sc = st->priv_data;
    MXFIndexEntry ie = {0};
    int err;

    if (!mxf->cbr_index && !mxf->edit_unit_byte_count && !(mxf->edit_units_count % EDIT_UNITS_PER_BODY)) {
        if ((err = av_reallocp_array(&mxf->index_entries, mxf->edit_units_count
                                     + EDIT_UNITS_PER_BODY, sizeof(*mxf->index_entries))) < 0) {
            mxf->edit_units_count = 0;
            av_log(s, AV_LOG_ERROR, "could not allocate index entries\n");
            return err;
        }
    }

    if (st->codecpar->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        if (!mxf_parse_mpeg2_frame(s, st, pkt, &ie)) {
            av_log(s, AV_LOG_ERROR, "could not get mpeg2 profile and level\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_DNXHD) {
        if (!mxf_parse_dnxhd_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get dnxhd profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_PRORES) {
        if (!mxf_parse_prores_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get prores profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO) {
        if (!mxf_parse_dv_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get dv profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_H264) {
        if (!mxf_parse_h264_frame(s, st, pkt, &ie)) {
            av_log(s, AV_LOG_ERROR, "could not get h264 profile\n");
            return -1;
        }
    }

    if (mxf->cbr_index) {
        if (pkt->size != sc->frame_size && st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            av_log(s, AV_LOG_ERROR, "track %d: frame size does not match index unit size, %d != %d\n",
                   st->index, pkt->size, sc->frame_size);
            return -1;
        }
        if (!mxf->header_written)
            mxf_compute_edit_unit_byte_count(s);
    }

    if (s->oformat == &ff_mxf_opatom_muxer)
        return mxf_write_opatom_packet(s, pkt, &ie);

    if (!mxf->header_written) {
        if (mxf->edit_unit_byte_count) {
            if ((err = mxf_write_partition(s, 1, 2, header_open_partition_key, 1)) < 0)
                return err;
            mxf_write_klv_fill(s);
            mxf_write_index_table_segment(s);
        } else {
            if ((err = mxf_write_partition(s, 0, 0, header_open_partition_key, 1)) < 0)
                return err;
        }
        mxf->header_written = 1;
    }

    if (st->index == 0) {
        if (!mxf->edit_unit_byte_count &&
            (!mxf->edit_units_count || mxf->edit_units_count > EDIT_UNITS_PER_BODY) &&
            !(ie.flags & 0x33)) { // I-frame, GOP start
            mxf_write_klv_fill(s);
            if ((err = mxf_write_partition(s, 1, 2, body_partition_key, 0)) < 0)
                return err;
            mxf_write_klv_fill(s);
            mxf_write_index_table_segment(s);
        }

        mxf_write_klv_fill(s);
        mxf_write_system_item(s);

        if (!mxf->edit_unit_byte_count) {
            mxf->index_entries[mxf->edit_units_count].offset = mxf->body_offset;
            mxf->index_entries[mxf->edit_units_count].flags = ie.flags;
            mxf->index_entries[mxf->edit_units_count].temporal_ref = ie.temporal_ref;
            mxf->body_offset += KAG_SIZE; // size of system element
        }
        mxf->edit_units_count++;
    } else if (!mxf->edit_unit_byte_count && st->index == 1) {
        if (!mxf->edit_units_count) {
            av_log(s, AV_LOG_ERROR, "No packets in first stream\n");
            return AVERROR_PATCHWELCOME;
        }
        mxf->index_entries[mxf->edit_units_count-1].slice_offset =
            mxf->body_offset - mxf->index_entries[mxf->edit_units_count-1].offset;
    }

    mxf_write_klv_fill(s);
    avio_write(pb, sc->track_essence_element_key, 16); // write key
    if (s->oformat == &ff_mxf_d10_muxer &&
        st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        mxf_write_d10_audio_packet(s, st, pkt);
    } else {
        klv_encode_ber4_length(pb, pkt->size); // write length
        avio_write(pb, pkt->data, pkt->size);
        mxf->body_offset += 16+4+pkt->size + klv_fill_size(16+4+pkt->size);
    }

    return 0;
}
