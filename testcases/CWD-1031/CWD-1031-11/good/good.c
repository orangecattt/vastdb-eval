#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <inttypes.h>

#define av_unused __attribute__((unused))
#define av_printf_format(fmt, args) __attribute__((format(gnu_printf, fmt, args)))
#define av_always_inline static inline
#define av_extern extern

#ifndef FFMIN
#define FFMIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef FFMAX
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#define FFNABS(x) ((x) < 0 ? -(x) : (x))

#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

#define FF_COMPLIANCE_STRICT 100

#define AV_LOG_WARNING 16
#define AV_LOG_ERROR 8
#define AV_LOG_VERBOSE 24
#define AV_LOG_TRACE 48

#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA (-22)
#define AVERROR_EOF (-541478725)
#define AVERROR_ENOMEM (-12)

#define EINVAL 22
#define ENOMEM 12
#define ENOENT 2

#define AV_NOPTS_VALUE ((int64_t)UINT64_C(0x8000000000000000))

#define AVINDEX_KEYFRAME 0x0001

#define AVDISCARD_ALL 0x100

#define AVFMT_EVENT_FLAG_METADATA_UPDATED 1
#define AVFMT_FLAG_IGNIDX 0x0002

#define AVIO_SEEKABLE_NORMAL 0x0001

#define SEEK_CUR 1
#define SEEK_SET 0

typedef struct AVFormatContext AVFormatContext;
typedef struct AVStream AVStream;
typedef struct AVIOContext AVIOContext;
typedef struct AVClass AVClass;
typedef struct AVCodecParameters AVCodecParameters;
typedef struct AVDictionary AVDictionary;

typedef struct AVRational {
    int num;
    int den;
} AVRational;

enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_H264,
    AV_CODEC_ID_MP3,
    AV_CODEC_ID_HEVC,
};

enum AVMediaType {
    AVMEDIA_TYPE_VIDEO = 0,
    AVMEDIA_TYPE_AUDIO = 1,
    AVMEDIA_TYPE_DATA = 4,
};

struct AVIOContext {
    int eof_reached;
    int seekable;
    void *buffer;
    size_t buffer_size;
};

struct AVCodecParameters {
    enum AVMediaType codec_type;
    enum AVCodecID codec_id;
    int width;
    int height;
    int bits_per_coded_sample;
    uint32_t codec_tag;
    int sample_rate;
    int extradata_size;
    uint8_t *extradata;
};

struct AVIndexEntry {
    int64_t pos;
    int64_t timestamp;
    int flags;
    int size;
    int min_distance;
};

struct AVStream {
    int index;
    int id;
    void *priv_data;
    AVCodecParameters *codecpar;
    AVRational time_base;
    AVRational sample_aspect_ratio;
    AVRational r_frame_rate;
    int64_t start_time;
    int64_t duration;
    int64_t nb_frames;
    int discard;
    struct AVIndexEntry *index_entries;
    int nb_index_entries;
};

typedef struct FFStream {
    int64_t nb_index_entries;
    struct AVIndexEntry *index_entries;
    size_t index_entries_allocated_size;
    int need_parsing;
    int64_t skip_samples;
} FFStream;

#define AVSTREAM_PARSE_FULL 2
#define AVSTREAM_PARSE_HEADERS 1

static inline FFStream *ffstream(AVStream *st);
static inline const FFStream *cffstream(const AVStream *st);

struct AVFormatContext {
    const AVClass *av_class;
    struct AVIOContext *pb;
    AVStream **streams;
    unsigned int nb_streams;
    char *url;
    int flags;
    int strict_std_compliance;
    int event_flags;
    AVDictionary *metadata;
    struct AVIOContext *(*io_open)(struct AVFormatContext *s, struct AVIOContext **pb,
                                   const char *url, int flags, AVDictionary **options);
};

typedef struct AVDictionary {
    int count;
} AVDictionary;

typedef struct MOVTimeToSample {
    unsigned int count;
    unsigned int duration;
    int offset;
} MOVTimeToSample;

typedef struct MOVStts {
    unsigned int count;
    unsigned int duration;
} MOVStts;

typedef struct MOVCtts {
    unsigned int count;
    int offset;
} MOVCtts;

typedef struct MOVStsc {
    int first;
    int count;
    int id;
} MOVStsc;

typedef struct MOVElst {
    int64_t duration;
    int64_t time;
    float rate;
} MOVElst;

typedef struct MOVDref {
    uint32_t type;
    char *path;
    char *dir;
    char volume[28];
    char filename[64];
    int16_t nlvl_to, nlvl_from;
} MOVDref;

typedef struct MOVAtom {
    uint32_t type;
    int64_t size;
} MOVAtom;

typedef struct MOVFragment {
    int found_tfhd;
    unsigned track_id;
    uint64_t base_data_offset;
    uint64_t moof_offset;
    uint64_t implicit_offset;
    unsigned stsd_id;
    unsigned duration;
    unsigned size;
    unsigned flags;
} MOVFragment;

typedef struct MOVTrackExt {
    unsigned track_id;
    unsigned stsd_id;
    unsigned duration;
    unsigned size;
    unsigned flags;
} MOVTrackExt;

typedef struct MOVSbgp {
    unsigned int count;
    unsigned int index;
} MOVSbgp;

typedef struct MOVFragmentStreamInfo {
    int id;
    int64_t sidx_pts;
    int64_t first_tfra_pts;
    int64_t tfdt_dts;
    int64_t next_trun_dts;
    int index_base;
    int index_entry;
    void *encryption_index;
    int stsd_id;
} MOVFragmentStreamInfo;

typedef struct MOVFragmentIndexItem {
    int64_t moof_offset;
    int headers_read;
    int current;
    int nb_stream_info;
    MOVFragmentStreamInfo *stream_info;
} MOVFragmentIndexItem;

typedef struct MOVFragmentIndex {
    int allocated_size;
    int complete;
    int current;
    int nb_items;
    MOVFragmentIndexItem *item;
} MOVFragmentIndex;

typedef struct MOVIndexRange {
    int64_t start;
    int64_t end;
} MOVIndexRange;

struct IAMFDemuxContext;

typedef struct MOVStreamContext {
    AVIOContext *pb;
    int refcount;
    int pb_is_copied;
    int id;
    int ffindex;
    int next_chunk;
    unsigned int chunk_count;
    int64_t *chunk_offsets;
    unsigned int tts_count;
    unsigned int tts_allocated_size;
    MOVTimeToSample *tts_data;
    unsigned int stts_count;
    unsigned int stts_allocated_size;
    MOVStts *stts_data;
    unsigned int sdtp_count;
    uint8_t *sdtp_data;
    unsigned int ctts_count;
    unsigned int ctts_allocated_size;
    MOVCtts *ctts_data;
    unsigned int stsc_count;
    MOVStsc *stsc_data;
    unsigned int stsc_index;
    int stsc_sample;
    unsigned int stps_count;
    unsigned *stps_data;
    MOVElst *elst_data;
    unsigned int elst_count;
    int tts_index;
    int tts_sample;
    unsigned int sample_size;
    unsigned int stsz_sample_size;
    unsigned int sample_count;
    unsigned int *sample_sizes;
    int keyframe_absent;
    unsigned int keyframe_count;
    int *keyframes;
    int time_scale;
    int64_t time_offset;
    int64_t min_corrected_pts;
    int current_sample;
    int64_t current_index;
    MOVIndexRange *index_ranges;
    MOVIndexRange *current_index_range;
    unsigned int bytes_per_frame;
    unsigned int samples_per_frame;
    int dv_audio_container;
    int pseudo_stream_id;
    int16_t audio_cid;
    unsigned drefs_count;
    MOVDref *drefs;
    int dref_id;
    unsigned tref_flags;
    int tref_id;
    int timecode_track;
    int width;
    int height;
    int h_spacing;
    int v_spacing;
    int dts_shift;
    uint32_t palette[256];
    int has_palette;
    int64_t data_size;
    uint32_t tmcd_flags;
    uint8_t tmcd_nb_frames;
    int64_t track_end;
    int start_pad;
    unsigned int rap_group_count;
    MOVSbgp *rap_group;
    unsigned int sync_group_count;
    MOVSbgp *sync_group;
    uint8_t *sgpd_sync;
    uint32_t sgpd_sync_count;
    int32_t *sample_offsets;
    int sample_offsets_count;
    int *open_key_samples;
    int open_key_samples_count;
    uint32_t min_sample_duration;

    int nb_frames_for_fps;
    int64_t duration_for_fps;

    uint8_t **extradata;
    int *extradata_size;
    int last_stsd_index;
    int stsd_count;
    int stsd_version;

    int32_t *display_matrix;
    void *stereo3d;
    size_t stereo3d_size;
    void *spherical;
    size_t spherical_size;
    void *mastering;
    size_t mastering_size;
    void *coll;
    size_t coll_size;
    void *ambient;
    size_t ambient_size;

    uint32_t format;

    int has_sidx;
    struct {
        struct AVAESCTR *aes_ctr;
        struct AVAES *aes_ctx;
        unsigned int per_sample_iv_size;
        void *default_encrypted_sample;
        void *encryption_index;
    } cenc;

    struct IAMFDemuxContext *iamf;
} MOVStreamContext;

typedef struct MOVContext {
    const AVClass *class;
    AVFormatContext *fc;
    int time_scale;
    int64_t duration;
    int found_moov;
    int found_iloc;
    int found_iinf;
    int found_mdat;
    int found_hdlr_mdta;
    int trak_index;
    char **meta_keys;
    unsigned meta_keys_count;
    void *dv_demux;
    AVFormatContext *dv_fctx;
    int isom;
    MOVFragment fragment;
    MOVTrackExt *trex_data;
    unsigned trex_count;
    int itunes_metadata;
    int handbrake_version;
    int *chapter_tracks;
    unsigned int nb_chapter_tracks;
    int use_absolute_path;
    int ignore_editlist;
    int advanced_editlist;
    int advanced_editlist_autodisabled;
    int ignore_chapters;
    int seek_individually;
    int64_t next_root_atom;
    int export_all;
    int export_xmp;
    int *bitrates;
    int bitrates_count;
    int moov_retry;
    int use_mfra_for;
    int has_looked_for_mfra;
    int use_tfdt;
    MOVFragmentIndex frag_index;
    int atom_depth;
    unsigned int aax_mode;
    uint8_t file_key[20];
    uint8_t file_iv[20];
    void *activation_bytes;
    int activation_bytes_size;
    void *audible_fixed_key;
    int audible_fixed_key_size;
    void *audible_key;
    int audible_key_size;
    void *audible_iv;
    int audible_iv_size;
    struct AVAES *aes_decrypt;
    uint8_t *decryption_key;
    int decryption_key_len;
    int enable_drefs;
    int32_t movie_display_matrix[3][3];
    int have_read_mfra_size;
    uint32_t mfra_size;
    uint32_t max_stts_delta;
    int primary_item_id;
    int cur_item_id;
    void **heif_item;
    int nb_heif_item;
    void *heif_grid;
    int nb_heif_grid;
    int thmb_item_id;
    int64_t idat_offset;
    int interleaved_read;
} MOVContext;

typedef struct MOVParseTableEntry {
    uint32_t type;
    int (*parse)(MOVContext *ctx, AVIOContext *pb, MOVAtom atom);
} MOVParseTableEntry;

static void av_log(void *avcl, int level, const char *fmt, ...);

static inline uint8_t avio_r8(AVIOContext *s);
static inline uint16_t avio_rb16(AVIOContext *s);
static inline uint32_t avio_rb24(AVIOContext *s);
static inline uint32_t avio_rb32(AVIOContext *s);
static inline uint64_t avio_rb64(AVIOContext *s);
static inline uint32_t avio_rl32(AVIOContext *s);
static inline void avio_skip(AVIOContext *s, int64_t offset);
static inline int64_t avio_tell(AVIOContext *s);
static inline int64_t avio_size(AVIOContext *s);
static inline int avio_feof(AVIOContext *s);
static inline int avio_seek(AVIOContext *s, int64_t offset, int whence);
static inline int avio_read(AVIOContext *s, unsigned char *buf, int size);
static inline void *av_malloc(size_t size);
static inline void *av_mallocz(size_t size);
static inline void *av_realloc(void *ptr, size_t size);
static inline void *av_calloc(size_t nmemb, size_t size);
static inline void *av_malloc_array(size_t nmemb, size_t size);
static inline void *av_reallocp_array(void *ptr, size_t nmemb, size_t size);
static inline void av_free(void *ptr);
static inline void av_freep(void *ptr);
static inline void *av_fast_realloc(void *ptr, unsigned int *size, size_t min_size);
static inline int av_reduce(int *dst_num, int *dst_den, int64_t num, int64_t den, int64_t max);
static inline int64_t av_rescale(int64_t a, int64_t b, int64_t c);
static inline int64_t av_sat_add64(int64_t a, int64_t b);
static inline int64_t av_sat_sub64(int64_t a, int64_t b);
static inline int av_strlcat(char *dst, const char *src, size_t siz);
static inline void *av_memcpy(void *dest, const void *src, size_t n);
static inline int av_cmp_i64(int64_t a, int64_t b);
static inline int ffio_read_size(AVIOContext *s, unsigned char *buf, int size);
static inline AVStream *avformat_new_stream(AVFormatContext *s, void *c);
static inline void avpriv_set_pts_info(AVStream *st, int pts_bits, int rel, int base);
static inline void ff_rfps_add_frame(AVFormatContext *fc, AVStream *st, int64_t dts);
static inline int ff_generate_avci_extradata(AVStream *st);
static inline void av_url_split(char *proto, int proto_size, char *auth, int auth_size,
                                char *host, int host_size, int *port_ptr,
                                const char *path, int path_size, const char *url);
static inline int test_same_origin(const char *src, const char *ref);

#define TAG_IS_AVCI(tag)                    \
    ((tag) == MKTAG('a', 'i', '5', 'p') ||  \
     (tag) == MKTAG('a', 'i', '5', 'q') ||  \
     (tag) == MKTAG('a', 'i', '5', '2') ||  \
     (tag) == MKTAG('a', 'i', '5', '3') ||  \
     (tag) == MKTAG('a', 'i', '5', '5') ||  \
     (tag) == MKTAG('a', 'i', '5', '6') ||  \
     (tag) == MKTAG('a', 'i', '1', 'p') ||  \
     (tag) == MKTAG('a', 'i', '1', 'q') ||  \
     (tag) == MKTAG('a', 'i', '1', '2') ||  \
     (tag) == MKTAG('a', 'i', '1', '3') ||  \
     (tag) == MKTAG('a', 'i', '1', '5') ||  \
     (tag) == MKTAG('a', 'i', '1', '6') ||  \
     (tag) == MKTAG('a', 'i', 'v', 'x') ||  \
     (tag) == MKTAG('A', 'V', 'i', 'n'))

static void fix_timescale(MOVContext *c, MOVStreamContext *sc);
static void mov_build_index(MOVContext *mov, AVStream *st);
static int mov_open_dref(MOVContext *c, AVIOContext **pb, const char *src, MOVDref *ref);
static int mov_update_iamf_streams(MOVContext *c, AVStream *st);

static int mov_read_aclr(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_avid(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ares(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_avss(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_glbl(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_chpl(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stco(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_colr(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ctts(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dref(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_elst(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_enda(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_fiel(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_adrm(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ftyp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_hdlr(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ilst(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_jp2h(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_mdat(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_mdhd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_meta(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_moof(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_moov(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_mvhd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_svq3(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_alac(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_pasp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_clap(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sbas(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sidx(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stps(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_strf(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stsc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stsd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stss(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_stsz(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_tkhd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_tfdt(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_tfhd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_tmcd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_chap(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_trex(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_trun(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_wave(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_esds(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dac3(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dec3(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ddts(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_wide(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_wfex(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_cmov(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_chan(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_chnl(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dvc1(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sgpd(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sbgp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_uuid(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_targa_y216(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_free(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_custom(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_frma(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_senc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_saiz(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_saio(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_pssh(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_schm(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_tenc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dfla(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_st3d(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sv3d(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_vexu(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_hfov(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dops(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dmlp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_smdm(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_coll(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_vpcc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_mdcv(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_clli(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dvcc_dvvc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_kind(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_SA3D(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_SAND(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_iloc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_pcmc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_pitm(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_idat(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_imir(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_iref(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_iprp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_iinf(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_amve(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_lhvc(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_iacb(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_udta_string(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_keys(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_dpxe(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_sdtp(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_ispe(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_irot(MOVContext *c, AVIOContext *pb, MOVAtom atom);

static int mov_read_stts(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_trak(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static int mov_read_default(MOVContext *c, AVIOContext *pb, MOVAtom atom);
static const char *av_fourcc2str(uint32_t fourcc);

#define CONFIG_IAMFDEC 0
#define FF_API_R_FRAME_RATE 0
#define CONFIG_H261_DECODER 0
#define CONFIG_H263_DECODER 0
#define CONFIG_MPEG4_DECODER 0

static const MOVParseTableEntry mov_default_parse_table[] = {
    { MKTAG('s','t','c','o'), mov_read_stco },
    { MKTAG('s','t','t','s'), mov_read_stts },
    { MKTAG('t','r','a','k'), mov_read_trak },
    { MKTAG('m','o','o','v'), mov_read_moov },
    { MKTAG('m','d','a','t'), mov_read_mdat },
    { 0, NULL }
};

static int mov_read_stts(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    unsigned int i, entries;
    int64_t duration = 0;
    int64_t total_sample_count = 0;
    int64_t current_dts = 0;
    int64_t corrected_dts = 0;

    if (c->trak_index < 0) {
        av_log(c->fc, AV_LOG_WARNING, "STTS outside TRAK\n");
        return 0;
    }

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    avio_r8(pb); /* version */
    avio_rb24(pb); /* flags */
    entries = avio_rb32(pb);

    av_log(c->fc, AV_LOG_TRACE, "track[%u].stts.entries = %u\n",
            c->fc->nb_streams-1, entries);

    if (sc->stts_data)
        av_log(c->fc, AV_LOG_WARNING, "Duplicated STTS atom\n");
    av_freep(&sc->stts_data);
    sc->stts_count = 0;
    if (entries >= INT_MAX / sizeof(*sc->stts_data))
        return AVERROR(ENOMEM);

    for (i = 0; i < entries && !pb->eof_reached; i++) {
        unsigned int sample_duration;
        unsigned int sample_count;
        unsigned int min_entries = FFMIN(FFMAX(i + 1, 1024 * 1024), entries);
        MOVStts *stts_data = av_fast_realloc(sc->stts_data, &sc->stts_allocated_size,
                                             min_entries * sizeof(*sc->stts_data));
        if (!stts_data) {
            av_freep(&sc->stts_data);
            sc->stts_count = 0;
            return AVERROR(ENOMEM);
        }
        sc->stts_count = min_entries;
        sc->stts_data = stts_data;

        sample_count    = avio_rb32(pb);
        sample_duration = avio_rb32(pb);

        sc->stts_data[i].count= sample_count;
        sc->stts_data[i].duration= sample_duration;

        av_log(c->fc, AV_LOG_TRACE, "sample_count=%u, sample_duration=%u\n",
                sample_count, sample_duration);

        /* STTS sample offsets are uint32 but some files store it as int32
         * with negative values used to correct DTS delays.
           There may be abnormally large values as well. */
        if (sample_duration > c->max_stts_delta) {
            // assume high delta is a correction if negative when cast as int32
            int32_t delta_magnitude = (int32_t)sample_duration;
            av_log(c->fc, AV_LOG_WARNING, "Too large sample offset %u in stts entry %u with count %u in st:%d. Clipping to 1.\n",
                   sample_duration, i, sample_count, st->index);
            sc->stts_data[i].duration = 1;
            corrected_dts += (delta_magnitude < 0 ? (int64_t)delta_magnitude : 1) * sample_count;
        } else {
            corrected_dts += sample_duration * (uint64_t)sample_count;
        }

        current_dts += sc->stts_data[i].duration * (uint64_t)sample_count;

        if (current_dts > corrected_dts) {
            int64_t drift = (current_dts - corrected_dts)/FFMAX(sample_count, 1);
            uint32_t correction = (sc->stts_data[i].duration > drift) ? drift : sc->stts_data[i].duration - 1;
            current_dts -= correction * (uint64_t)sample_count;
            sc->stts_data[i].duration -= correction;
        }

        duration+=(int64_t)sc->stts_data[i].duration*(uint64_t)sc->stts_data[i].count;
        total_sample_count+=sc->stts_data[i].count;
    }

    sc->stts_count = i;

    if (duration > 0 &&
        duration <= INT64_MAX - sc->duration_for_fps &&
        total_sample_count <= INT_MAX - sc->nb_frames_for_fps) {
        sc->duration_for_fps  += duration;
        sc->nb_frames_for_fps += total_sample_count;
    }

    if (pb->eof_reached) {
        av_log(c->fc, AV_LOG_WARNING, "reached eof, corrupted STTS atom\n");
        return AVERROR_EOF;
    }

    st->nb_frames= total_sample_count;
    if (duration)
        st->duration= FFMIN(st->duration, duration);

    // All samples have zero duration. They have higher chance be chose by
    // mov_find_next_sample, which leads to seek again and again.
    //
    // It's AVERROR_INVALIDDATA actually, but such files exist in the wild.
    // So only mark data stream as discarded for safety.
    if (!duration && sc->stts_count &&
            st->codecpar->codec_type == AVMEDIA_TYPE_DATA) {
        av_log(c->fc, AV_LOG_WARNING,
               "All samples in data stream index:id [%d:%d] have zero "
               "duration, stream set to be discarded by default. Override "
               "using AVStream->discard or -discard for ffmpeg command.\n",
               st->index, sc->id);
        st->discard = AVDISCARD_ALL;
    }
    sc->track_end = duration;
    return 0;
}

static int mov_read_trak(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    int ret;

    st = avformat_new_stream(c->fc, NULL);
    if (!st) return AVERROR(ENOMEM);
    st->id = -1;
    sc = av_mallocz(sizeof(MOVStreamContext));
    if (!sc) return AVERROR(ENOMEM);

    st->priv_data = sc;
    st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
    sc->ffindex = st->index;
    c->trak_index = st->index;
    sc->tref_flags = 0;
    sc->tref_id = -1;
    sc->refcount = 1;

    if ((ret = mov_read_default(c, pb, atom)) < 0)
        return ret;

    c->trak_index = -1;

    // Here stsc refers to a chunk not described in stco. This is technically invalid,
    // but we can overlook it (clearing stsc) whenever stts_count == 0 (indicating no samples).
    if (!sc->chunk_count && !sc->stts_count && sc->stsc_count) {
        sc->stsc_count = 0;
        av_freep(&sc->stsc_data);
    }

    /* sanity checks */
    if ((sc->chunk_count && (!sc->stts_count || !sc->stsc_count ||
                            (!sc->sample_size && !sc->sample_count))) ||
        (!sc->chunk_count && sc->sample_count)) {
        av_log(c->fc, AV_LOG_ERROR, "stream %d, missing mandatory atoms, broken header\n",
               st->index);
        return 0;
    }
    if (sc->stsc_count && sc->stsc_data[ sc->stsc_count - 1 ].first > sc->chunk_count) {
        av_log(c->fc, AV_LOG_ERROR, "stream %d, contradictionary STSC and STCO\n",
               st->index);
        return AVERROR_INVALIDDATA;
    }

    fix_timescale(c, sc);

    avpriv_set_pts_info(st, 64, 1, sc->time_scale);

    /*
     * Advanced edit list support does not work with fragemented MP4s, which
     * have stsc, stsz, stco, and stts with zero entries in the moov atom.
     * In these files, trun atoms may be streamed in.
     */
    if (!sc->stts_count && c->advanced_editlist) {

        av_log(c->fc, AV_LOG_VERBOSE, "advanced_editlist does not work with fragmented "
                                      "MP4. disabling.\n");
        c->advanced_editlist = 0;
        c->advanced_editlist_autodisabled = 1;
    }

    mov_build_index(c, st);

#if CONFIG_IAMFDEC
    if (sc->iamf) {
        ret = mov_update_iamf_streams(c, st);
        if (ret < 0)
            return ret;
    }
#endif

    if (sc->dref_id-1 < sc->drefs_count && sc->drefs[sc->dref_id-1].path) {
        MOVDref *dref = &sc->drefs[sc->dref_id - 1];
        if (c->enable_drefs) {
            if (mov_open_dref(c, &sc->pb, c->fc->url, dref) < 0)
                av_log(c->fc, AV_LOG_ERROR,
                       "stream %d, error opening alias: path='%s', dir='%s', "
                       "filename='%s', volume='%s', nlvl_from=%d, nlvl_to=%d\n",
                       st->index, dref->path, dref->dir, dref->filename,
                       dref->volume, dref->nlvl_from, dref->nlvl_to);
        } else {
            av_log(c->fc, AV_LOG_WARNING,
                   "Skipped opening external track: "
                   "stream %d, alias: path='%s', dir='%s', "
                   "filename='%s', volume='%s', nlvl_from=%d, nlvl_to=%d."
                   "Set enable_drefs to allow this.\n",
                   st->index, dref->path, dref->dir, dref->filename,
                   dref->volume, dref->nlvl_from, dref->nlvl_to);
        }
    } else {
        sc->pb = c->fc->pb;
        sc->pb_is_copied = 1;
    }

    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        int stts_constant = !!sc->stts_count;
        if (sc->h_spacing && sc->v_spacing)
            av_reduce(&st->sample_aspect_ratio.num, &st->sample_aspect_ratio.den,
                      sc->h_spacing, sc->v_spacing, INT_MAX);
        if (!st->sample_aspect_ratio.num && st->codecpar->width && st->codecpar->height &&
            sc->height && sc->width &&
            (st->codecpar->width != sc->width || st->codecpar->height != sc->height)) {
            av_reduce(&st->sample_aspect_ratio.num, &st->sample_aspect_ratio.den,
                      (int64_t)st->codecpar->height * sc->width,
                      (int64_t)st->codecpar->width  * sc->height, INT_MAX);
        }

#if FF_API_R_FRAME_RATE
        for (unsigned i = 1; sc->stts_count && i + 1 < sc->tts_count; i++) {
            if (sc->tts_data[i].duration == sc->tts_data[0].duration)
                continue;
            stts_constant = 0;
        }
        if (stts_constant)
            av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den,
                      sc->time_scale, sc->tts_data[0].duration, INT_MAX);
#endif
    }

    // done for ai5q, ai52, ai55, ai1q, ai12 and ai15.
    if (!st->codecpar->extradata_size && st->codecpar->codec_id == AV_CODEC_ID_H264 &&
        TAG_IS_AVCI(st->codecpar->codec_tag)) {
        ret = ff_generate_avci_extradata(st);
        if (ret < 0)
            return ret;
    }

    switch (st->codecpar->codec_id) {
#if CONFIG_H261_DECODER
    case AV_CODEC_ID_H261:
#endif
#if CONFIG_H263_DECODER
    case AV_CODEC_ID_H263:
#endif
#if CONFIG_MPEG4_DECODER
    case AV_CODEC_ID_MPEG4:
#endif
        st->codecpar->width = 0; /* let decoder init width/height */
        st->codecpar->height= 0;
        break;
    }

    // If the duration of the mp3 packets is not constant, then they could need a parser
    if (st->codecpar->codec_id == AV_CODEC_ID_MP3
        && sc->time_scale == st->codecpar->sample_rate) {
        int stts_constant = 1;
        for (int i = 1; sc->stts_count && i < sc->tts_count; i++) {
            if (sc->tts_data[i].duration == sc->tts_data[0].duration)
                continue;
            stts_constant = 0;
        }
        if (!stts_constant)
            ffstream(st)->need_parsing = AVSTREAM_PARSE_FULL;
    }
    /* Do not need those anymore. */
    av_freep(&sc->chunk_offsets);
    av_freep(&sc->sample_sizes);
    av_freep(&sc->keyframes);
    av_freep(&sc->stps_data);
    av_freep(&sc->elst_data);
    av_freep(&sc->rap_group);
    av_freep(&sc->sync_group);
    av_freep(&sc->sgpd_sync);

    return 0;
}

static const MOVParseTableEntry mov_default_parse_table_full[] = {
{ MKTAG('A','C','L','R'), mov_read_aclr },
{ MKTAG('A','P','R','G'), mov_read_avid },
{ MKTAG('A','A','L','P'), mov_read_avid },
{ MKTAG('A','R','E','S'), mov_read_ares },
{ MKTAG('a','v','s','s'), mov_read_avss },
{ MKTAG('a','v','1','C'), mov_read_glbl },
{ MKTAG('c','h','p','l'), mov_read_chpl },
{ MKTAG('c','o','6','4'), mov_read_stco },
{ MKTAG('c','o','l','r'), mov_read_colr },
{ MKTAG('c','t','t','s'), mov_read_ctts }, /* composition time to sample */
{ MKTAG('d','i','n','f'), mov_read_default },
{ MKTAG('D','p','x','E'), mov_read_dpxe },
{ MKTAG('d','r','e','f'), mov_read_dref },
{ MKTAG('e','d','t','s'), mov_read_default },
{ MKTAG('e','l','s','t'), mov_read_elst },
{ MKTAG('e','n','d','a'), mov_read_enda },
{ MKTAG('f','i','e','l'), mov_read_fiel },
{ MKTAG('a','d','r','m'), mov_read_adrm },
{ MKTAG('f','t','y','p'), mov_read_ftyp },
{ MKTAG('g','l','b','l'), mov_read_glbl },
{ MKTAG('h','d','l','r'), mov_read_hdlr },
{ MKTAG('i','l','s','t'), mov_read_ilst },
{ MKTAG('j','p','2','h'), mov_read_jp2h },
{ MKTAG('m','d','a','t'), mov_read_mdat },
{ MKTAG('m','d','h','d'), mov_read_mdhd },
{ MKTAG('m','d','i','a'), mov_read_default },
{ MKTAG('m','e','t','a'), mov_read_meta },
{ MKTAG('m','i','n','f'), mov_read_default },
{ MKTAG('m','o','o','f'), mov_read_moof },
{ MKTAG('m','o','o','v'), mov_read_moov },
{ MKTAG('m','v','e','x'), mov_read_default },
{ MKTAG('m','v','h','d'), mov_read_mvhd },
{ MKTAG('S','M','I',' '), mov_read_svq3 },
{ MKTAG('a','l','a','c'), mov_read_alac }, /* alac specific atom */
{ MKTAG('a','v','c','C'), mov_read_glbl },
{ MKTAG('p','a','s','p'), mov_read_pasp },
{ MKTAG('c','l','a','p'), mov_read_clap },
{ MKTAG('s','b','a','s'), mov_read_sbas },
{ MKTAG('s','i','d','x'), mov_read_sidx },
{ MKTAG('s','t','b','l'), mov_read_default },
{ MKTAG('s','t','c','o'), mov_read_stco },
{ MKTAG('s','t','p','s'), mov_read_stps },
{ MKTAG('s','t','r','f'), mov_read_strf },
{ MKTAG('s','t','s','c'), mov_read_stsc },
{ MKTAG('s','t','s','d'), mov_read_stsd }, /* sample description */
{ MKTAG('s','t','s','s'), mov_read_stss }, /* sync sample */
{ MKTAG('s','t','s','z'), mov_read_stsz }, /* sample size */
{ MKTAG('s','t','t','s'), mov_read_stts },
{ MKTAG('s','t','z','2'), mov_read_stsz }, /* compact sample size */
{ MKTAG('s','d','t','p'), mov_read_sdtp }, /* independent and disposable samples */
{ MKTAG('t','k','h','d'), mov_read_tkhd }, /* track header */
{ MKTAG('t','f','d','t'), mov_read_tfdt },
{ MKTAG('t','f','h','d'), mov_read_tfhd }, /* track fragment header */
{ MKTAG('t','r','a','k'), mov_read_trak },
{ MKTAG('t','r','a','f'), mov_read_default },
{ MKTAG('t','r','e','f'), mov_read_default },
{ MKTAG('t','m','c','d'), mov_read_tmcd },
{ MKTAG('c','h','a','p'), mov_read_chap },
{ MKTAG('t','r','e','x'), mov_read_trex },
{ MKTAG('t','r','u','n'), mov_read_trun },
{ MKTAG('u','d','t','a'), mov_read_default },
{ MKTAG('w','a','v','e'), mov_read_wave },
{ MKTAG('e','s','d','s'), mov_read_esds },
{ MKTAG('d','a','c','3'), mov_read_dac3 }, /* AC-3 info */
{ MKTAG('d','e','c','3'), mov_read_dec3 }, /* EAC-3 info */
{ MKTAG('d','d','t','s'), mov_read_ddts }, /* DTS audio descriptor */
{ MKTAG('w','i','d','e'), mov_read_wide }, /* place holder */
{ MKTAG('w','f','e','x'), mov_read_wfex },
{ MKTAG('c','m','o','v'), mov_read_cmov },
{ MKTAG('c','h','a','n'), mov_read_chan }, /* channel layout from quicktime */
{ MKTAG('c','h','n','l'), mov_read_chnl }, /* channel layout from ISO-14496-12 */
{ MKTAG('d','v','c','1'), mov_read_dvc1 },
{ MKTAG('s','g','p','d'), mov_read_sgpd },
{ MKTAG('s','b','g','p'), mov_read_sbgp },
{ MKTAG('h','v','c','C'), mov_read_glbl },
{ MKTAG('v','v','c','C'), mov_read_glbl },
{ MKTAG('u','u','i','d'), mov_read_uuid },
{ MKTAG('C','i','n', 0x8e), mov_read_targa_y216 },
{ MKTAG('f','r','e','e'), mov_read_free },
{ MKTAG('-','-','-','-'), mov_read_custom },
{ MKTAG('s','i','n','f'), mov_read_default },
{ MKTAG('f','r','m','a'), mov_read_frma },
{ MKTAG('s','e','n','c'), mov_read_senc },
{ MKTAG('s','a','i','z'), mov_read_saiz },
{ MKTAG('s','a','i','o'), mov_read_saio },
{ MKTAG('p','s','s','h'), mov_read_pssh },
{ MKTAG('s','c','h','m'), mov_read_schm },
{ MKTAG('s','c','h','i'), mov_read_default },
{ MKTAG('t','e','n','c'), mov_read_tenc },
{ MKTAG('d','f','L','a'), mov_read_dfla },
{ MKTAG('s','t','3','d'), mov_read_st3d }, /* stereoscopic 3D video box */
{ MKTAG('s','v','3','d'), mov_read_sv3d }, /* spherical video box */
{ MKTAG('v','e','x','u'), mov_read_vexu }, /* video extension usage */
{ MKTAG('h','f','o','v'), mov_read_hfov },
{ MKTAG('d','o','p','s'), mov_read_dops },
{ MKTAG('d','m','l','p'), mov_read_dmlp },
{ MKTAG('S','m','D','m'), mov_read_smdm },
{ MKTAG('C','o','L','L'), mov_read_coll },
{ MKTAG('v','p','c','C'), mov_read_vpcc },
{ MKTAG('m','d','c','v'), mov_read_mdcv },
{ MKTAG('c','l','l','i'), mov_read_clli },
{ MKTAG('d','v','c','C'), mov_read_dvcc_dvvc },
{ MKTAG('d','v','v','C'), mov_read_dvcc_dvvc },
{ MKTAG('d','v','w','C'), mov_read_dvcc_dvvc },
{ MKTAG('k','i','n','d'), mov_read_kind },
{ MKTAG('S','A','3','D'), mov_read_SA3D }, /* ambisonic audio box */
{ MKTAG('S','A','N','D'), mov_read_SAND }, /* non diegetic audio box */
{ MKTAG('i','l','o','c'), mov_read_iloc },
{ MKTAG('p','c','m','C'), mov_read_pcmc }, /* PCM configuration box */
{ MKTAG('p','i','t','m'), mov_read_pitm },
{ MKTAG('e','v','c','C'), mov_read_glbl },
{ MKTAG('i','d','a','t'), mov_read_idat },
{ MKTAG('i','m','i','r'), mov_read_imir },
{ MKTAG('i','r','e','f'), mov_read_iref },
{ MKTAG('i','s','p','e'), mov_read_ispe },
{ MKTAG('i','r','o','t'), mov_read_irot },
{ MKTAG('i','p','r','p'), mov_read_iprp },
{ MKTAG('i','i','n','f'), mov_read_iinf },
{ MKTAG('a','m','v','e'), mov_read_amve }, /* ambient viewing environment box */
{ MKTAG('l','h','v','C'), mov_read_lhvc },
{ MKTAG('l','v','c','C'), mov_read_glbl },
#if CONFIG_IAMFDEC
{ MKTAG('i','a','c','b'), mov_read_iacb },
#endif
{ 0, NULL }
};

static int mov_read_default(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int64_t total_size = 0;
    MOVAtom a;
    int i;

    if (c->atom_depth > 10) {
        av_log(c->fc, AV_LOG_ERROR, "Atoms too deeply nested\n");
        return AVERROR_INVALIDDATA;
    }
    c->atom_depth ++;

    if (atom.size < 0)
        atom.size = INT64_MAX;
    while (total_size <= atom.size - 8) {
        int (*parse)(MOVContext*, AVIOContext*, MOVAtom) = NULL;
        a.size = avio_rb32(pb);
        a.type = avio_rl32(pb);
        if (avio_feof(pb))
            break;
        if (((a.type == MKTAG('f','r','e','e') && c->moov_retry) ||
              a.type == MKTAG('h','o','o','v')) &&
            a.size >= 8 &&
            c->fc->strict_std_compliance < FF_COMPLIANCE_STRICT) {
                uint32_t type;
                avio_skip(pb, 4);
                type = avio_rl32(pb);
                if (avio_feof(pb))
                    break;
                avio_seek(pb, -8, SEEK_CUR);
                if (type == MKTAG('m','v','h','d') ||
                    type == MKTAG('c','m','o','v')) {
                    av_log(c->fc, AV_LOG_ERROR, "Detected moov in a free or hoov atom.\n");
                    a.type = MKTAG('m','o','o','v');
                }
        }
        if (atom.type != MKTAG('r','o','o','t') &&
            atom.type != MKTAG('m','o','o','v')) {
            if (a.type == MKTAG('t','r','a','k') ||
                a.type == MKTAG('m','d','a','t')) {
                av_log(c->fc, AV_LOG_ERROR, "Broken file, trak/mdat not at top-level\n");
                avio_skip(pb, -8);
                c->atom_depth --;
                return 0;
            }
        }
        total_size += 8;
        if (a.size == 1 && total_size + 8 <= atom.size) { /* 64 bit extended size */
            a.size = avio_rb64(pb) - 8;
            total_size += 8;
        }
        av_log(c->fc, AV_LOG_TRACE, "type:'%s' parent:'%s' sz: %"PRId64" %"PRId64" %"PRId64"\n",
               av_fourcc2str(a.type), av_fourcc2str(atom.type), a.size, total_size, atom.size);
        if (a.size == 0) {
            a.size = atom.size - total_size + 8;
        }
        if (a.size < 0)
            break;
        a.size -= 8;
        if (a.size < 0)
            break;
        a.size = FFMIN(a.size, atom.size - total_size);

        for (i = 0; mov_default_parse_table_full[i].type; i++)
            if (mov_default_parse_table_full[i].type == a.type) {
                parse = mov_default_parse_table_full[i].parse;
                break;
            }

        // container is user data
        if (!parse && (atom.type == MKTAG('u','d','t','a') ||
                       atom.type == MKTAG('i','l','s','t')))
            parse = mov_read_udta_string;

        // Supports parsing the QuickTime Metadata Keys.
        // https://developer.apple.com/library/mac/documentation/QuickTime/QTFF/Metadata/Metadata.html
        if (!parse && c->found_hdlr_mdta &&
            atom.type == MKTAG('m','e','t','a') &&
            a.type == MKTAG('k','e','y','s') &&
            c->meta_keys_count == 0) {
            parse = mov_read_keys;
        }

        if (!parse) { /* skip leaf atoms data */
            avio_skip(pb, a.size);
        } else {
            int64_t start_pos = avio_tell(pb);
            int64_t left;
            int err = parse(c, pb, a);
            if (err < 0) {
                c->atom_depth --;
                return err;
            }
            if (c->found_moov && c->found_mdat && a.size <= INT64_MAX - start_pos &&
                ((!(pb->seekable & AVIO_SEEKABLE_NORMAL) || c->fc->flags & AVFMT_FLAG_IGNIDX || c->frag_index.complete) ||
                 start_pos + a.size == avio_size(pb))) {
                if (!(pb->seekable & AVIO_SEEKABLE_NORMAL) || c->fc->flags & AVFMT_FLAG_IGNIDX || c->frag_index.complete)
                    c->next_root_atom = start_pos + a.size;
                c->atom_depth --;
                return 0;
            }
            left = a.size - avio_tell(pb) + start_pos;
            if (left > 0) /* skip garbage at atom end */
                avio_skip(pb, left);
            else if (left < 0) {
                av_log(c->fc, AV_LOG_WARNING,
                       "overread end of atom '%s' by %"PRId64" bytes\n",
                       av_fourcc2str(a.type), -left);
                avio_seek(pb, left, SEEK_CUR);
            }
        }

        total_size += a.size;
    }

    if (total_size < atom.size && atom.size < 0x7ffff)
        avio_skip(pb, atom.size - total_size);

    c->atom_depth --;
    return 0;
}
