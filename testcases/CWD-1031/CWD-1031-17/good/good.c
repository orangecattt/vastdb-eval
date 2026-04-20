/*
 * Auto-generated dependency-extracted file
 * Original file: tmp.c (lines 33+)
 * Codebase: /home/yibozhang/src/mlir/cxx-real/src/gpac
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

/* ========== Basic Types ========== */
typedef uint64_t u64; typedef int64_t s64;
typedef uint32_t u32; typedef int32_t s32;
typedef uint16_t u16; typedef int16_t s16;
typedef uint8_t u8; typedef int8_t s8;
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;
typedef enum { GF_OK = 0, GF_EOS = 1, GF_BAD_PARAM = -1, GF_OUT_OF_MEM = -2, GF_NOT_SUPPORTED = -4, GF_BUFFER_TOO_SMALL = -9, GF_FILTER_NOT_FOUND = -11 } GF_Err;
typedef double Double; typedef float Float;
typedef u8 bin128[16];
#define LLD "lld"
typedef struct { s32 num; u32 den; } GF_Fraction;
typedef struct { s64 num; u64 den; } GF_Fraction64;
#define GF_SAFEALLOC(__ptr, __struct) { (__ptr) = (__struct *) gf_malloc(sizeof(__struct)); if (__ptr) { memset((void *) (__ptr), 0, sizeof(__struct)); } }

/* ========== Log Types ========== */
typedef enum { GF_LOG_QUIET = 0, GF_LOG_ERROR, GF_LOG_WARNING, GF_LOG_INFO, GF_LOG_DEBUG } GF_LOG_Level;
typedef enum { GF_LOG_CORE = 0, GF_LOG_CODING, GF_LOG_CONTAINER, GF_LOG_MEDIA, GF_LOG_FILTER, GF_LOG_ALL } GF_LOG_Tool;
void gf_log_lt(GF_LOG_Level ll, GF_LOG_Tool lt);
Bool gf_log_tool_level_on(GF_LOG_Tool log_tool, GF_LOG_Level log_level);
void gf_log_check_error(GF_LOG_Level ll, GF_LOG_Tool lt);
void gf_log(const char *fmt, ...);
#define GF_LOG(_log_level, _log_tools, __args) if (gf_log_tool_level_on(_log_tools, _log_level)) { gf_log_lt(_log_level, _log_tools); gf_log __args ;}

/* ========== List Types ========== */
typedef struct _tag_array GF_List;
GF_List *gf_list_new(void); void gf_list_del(GF_List *ptr); u32 gf_list_count(const GF_List *ptr);
void *gf_list_get(const GF_List *ptr, u32 item); GF_Err gf_list_add(GF_List *ptr, void* item);
void *gf_list_pop_front(GF_List *ptr); void *gf_list_pop_back(GF_List *ptr);

/* ========== BitStream Types ========== */
typedef struct __tag_bitstream GF_BitStream;
enum { GF_BITSTREAM_READ = 0, GF_BITSTREAM_WRITE, GF_BITSTREAM_WRITE_DYN };
GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode); void gf_bs_del(GF_BitStream *bs);
void gf_bs_write_int(GF_BitStream *bs, u32 value, u32 nBits); void gf_bs_write_u8(GF_BitStream *bs, u32 value);
void gf_bs_write_u32(GF_BitStream *bs, u32 value); void gf_bs_write_u64(GF_BitStream *bs, u64 value);
void gf_bs_write_data(GF_BitStream *bs, const u8 *data, u32 size);
GF_Err gf_bs_get_content(GF_BitStream *bs, u8 **out_data, u32 *out_size);
u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits); u32 gf_bs_read_u8(GF_BitStream *bs);
u32 gf_bs_read_u16(GF_BitStream *bs); u32 gf_bs_read_u32(GF_BitStream *bs); u64 gf_bs_read_u64(GF_BitStream *bs);
void gf_bs_read_data(GF_BitStream *bs, u8 *data, u32 size);
u64 gf_bs_get_position(GF_BitStream *bs); void gf_bs_skip_bytes(GF_BitStream *bs, u64 nbBytes);
char *gf_bs_read_utf8(GF_BitStream *bs);

/* ========== Sync Layer Types ========== */
typedef struct {
    u8 tag; u8 predefined; u8 useAccessUnitStartFlag; u8 useAccessUnitEndFlag;
    u8 useRandomAccessPointFlag; u8 hasRandomAccessUnitsOnlyFlag; u8 usePaddingFlag;
    u8 useTimestampsFlag; u8 useIdleFlag; u8 durationFlag;
    u32 timestampResolution; u32 OCRResolution; u8 timestampLength; u8 OCRLength;
    u8 AULength; u8 instantBitrateLength; u8 degradationPriorityLength;
    u8 AUSeqNumLength; u8 packetSeqNumLength; u32 timeScale;
    u16 AUDuration; u16 CUDuration; u64 startDTS; u64 startCTS;
    Bool no_dts_signaling; u32 carousel_version;
} GF_SLConfig;

/* ========== MPEG-4 ODF Types ========== */
#define BASE_DESCRIPTOR u8 tag;
typedef struct { BASE_DESCRIPTOR } GF_Descriptor;
typedef struct {
    BASE_DESCRIPTOR; u16 objectDescriptorID; char *URLString; GF_List *ESDescriptors;
    GF_List *OCIDescriptors; GF_List *IPMP_Descriptors; GF_List *extensionDescriptors;
    u16 ServiceID; Bool RedirectOnly; Bool fake_remote;
    u8 inlineProfileFlag; u8 OD_profileAndLevel; u8 scene_profileAndLevel;
    u8 audio_profileAndLevel; u8 visual_profileAndLevel; u8 graphics_profileAndLevel;
    GF_List *IPMPToolList;
} GF_InitialObjectDescriptor;
enum { GF_ODF_IOD_TAG = 0x02 };
GF_Descriptor *gf_odf_desc_new(u8 tag); void gf_odf_desc_del(GF_Descriptor *desc);
GF_Err gf_odf_parse_descriptor(GF_BitStream *bs, GF_Descriptor **desc, u32 *size);

/* ========== Filter Types ========== */
typedef struct __gf_filter_pid GF_FilterPid; typedef struct __gf_filter_pck GF_FilterPacket;
typedef struct __gf_prop_val GF_PropertyValue;
typedef struct __gf_dec_spec_info { u32 dataLength; u8 *data; } GF_DecSpecificInfo;
typedef struct __gf_dec_cfg { u32 streamType; u32 objectTypeIndication; u32 bufferSizeDB; u32 maxBitrate; u32 avgBitrate; GF_DecSpecificInfo *decoderSpecificInfo; } GF_DecoderConfig;
typedef struct __gf_sl_cfg { u32 timestampResolution; } GF_SLConfigDef;
typedef struct __gf_esd { u8 tag; u16 ESID; u8 streamType; u8 streamFormat; u32 bufferSize; u32 maxBitrate; u32 avgBitrate; GF_DecoderConfig *decoderConfig; u16 OCRESID; u16 dependsOnESID; GF_SLConfigDef *slConfig; } GF_ESD;
typedef enum { GF_PROP_VOID = 0, GF_PROP_UINT, GF_PROP_INT, GF_PROP_FLOAT, GF_PROP_DOUBLE, GF_PROP_BOOLEAN, GF_PROP_STRING, GF_PROP_DATA, GF_PROP_BINARY, GF_PROP_FRACTION, GF_PROP_FRACTION64, GF_PROP_4CC, GF_PROP_BOOL = GF_PROP_BOOLEAN, GF_PROP_STRING_NO_COPY = 15 } GF_PropertyType;
typedef struct { u32 size; const u8 *data; } GF_PropertyData;
#define PROP_UINT(_v) (GF_PropertyValue){.type=GF_PROP_UINT, .value.uint = _v}
#define PROP_DATA(_d, _s) (GF_PropertyValue){.type=GF_PROP_DATA, .value.data = {.size = _s, .data = (const u8*)_d}}
struct __gf_prop_val { GF_PropertyType type; union { u32 uint; s32 sint; Float ffloat; Double ddouble; Bool boolean; const char *string; GF_Fraction64 lfrac; u32 _4cc; GF_PropertyData data; } value; };
#define GF_PROP_BOOL GF_PROP_BOOLEAN
#define PROP_BOOL(_val) (GF_PropertyValue){.type=GF_PROP_BOOL, .value.boolean = _val}
#define PROP_FRAC64_INT(_num, _den) (GF_PropertyValue){.type=GF_PROP_FRACTION64, .value.lfrac.num = _num, .value.lfrac.den = _den}
typedef enum {
    GF_PidProperty_Dummy = 0
} GF_PidProperty;
GF_Err gf_filter_pid_set_property(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *v);
GF_Err gf_filter_pck_set_property(GF_FilterPacket *pck, u32 prop_4cc, const GF_PropertyValue *v);
GF_Err gf_filter_pck_send(GF_FilterPacket *pck);

/* ========== Network/Memory ========== */
u64 gf_net_get_utc_ts(u16 year, u8 month, u8 day, u8 hour, u8 minute, u8 second);
void *gf_malloc(size_t size); void *gf_free(void *ptr); void *gf_realloc(void *ptr, size_t size);
const char *gf_opts_get_bool(const char *sec, const char *key);
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))
const char *gf_4cc_to_str(u32 type);

/* ========== MPEG-TS Types ========== */
#define GF_M2TS_MAX_STREAMS 8192
typedef struct __m2ts_demux_section { u8 *data; u32 data_size; } GF_M2TS_Section;
typedef struct GF_M2TS_SectionFilter {
    s16 cc; u8 *section; u16 length; u16 received; void *table;
    Bool process_individual; Bool direct_dispatch; u32 service_id;
    void (*process_section)(void *demux, void *es, GF_List *sections, u8 table_id, u16 ex_table_id, u8 version_number, u8 last_section_number, u32 status);
    Bool demux_restarted;
} GF_M2TS_SectionFilter;
typedef struct {
    u16 application_format; u32 application_format_identifier; u8 format; u32 format_identifier;
    u8 service_id; u8 locator_record_flag; u32 locator_length; char *locator_data;
    u8 carriage_flag; u16 program_number; u16 ts_location; u16 ts_id; u8 *data; u32 data_size;
} GF_M2TS_MetadataPointerDescriptor;
typedef struct { u32 pid; u32 timeline_id; const char *external_URL; Bool is_announce, is_splicing; Bool reload_external; GF_Fraction activation_countdown; } GF_M2TS_TemiLocationDescriptor;
typedef struct { u32 pid; u32 timeline_id; u32 media_timescale; u64 media_timestamp; u64 pes_pts; Bool force_reload; Bool is_paused; Bool is_discontinuity; u64 ntp; } GF_M2TS_TemiTimecodeDescriptor;
typedef struct { u16 year; u8 month; u8 day; u8 hour; u8 minute; u8 second; } GF_M2TS_TDT_TOT;
typedef struct { u32 timeline_id; Bool is_loc; u32 len; u8 *data; } GF_TEMIInfo;
typedef struct { char language[3]; u8 type; u16 composition_page_id; u16 ancillary_page_id; } GF_M2TS_DVB_Subtitling_Descriptor;
typedef struct { u8 *data; u32 data_len; u32 flags; u64 PTS, DTS; void *stream; } GF_M2TS_PES_PCK;
typedef struct { u8 *data; u32 data_len; u8 version_number; void *stream; } GF_M2TS_SL_PCK;
typedef struct tag_m2ts_pes GF_M2TS_PES;
typedef struct {
    void *ts; GF_List *streams; u32 pmt_pid; u32 pcr_pid; u32 number;
    GF_InitialObjectDescriptor *pmt_iod; GF_List *additional_ods; u64 first_dts;
    u64 last_pcr_value; u32 last_pcr_value_pck_number; u64 before_last_pcr_value;
    u32 before_last_pcr_value_pck_number; Bool tdt_found; u32 pid_playing; Bool is_scalable;
    GF_M2TS_MetadataPointerDescriptor *metadata_pointer_descriptor; s16 pcr_cc; void *user;
    void (*on_event)(void *ts, u32 event, void *param);
} GF_M2TS_Program;
enum {
    GF_M2TS_ES_IS_PES = 1, GF_M2TS_ES_IS_SECTION = 1<<1, GF_M2TS_ES_IS_FMC = 1<<2,
    GF_M2TS_ES_IS_SL = 1<<3, GF_M2TS_ES_IS_MPEG4_OD = 1<<4, GF_M2TS_ES_IS_MPE = 1<<5,
    GF_M2TS_INHERIT_PCR = 1<<6, GF_M2TS_FAKE_PCR = 1<<7, GF_M2TS_GPAC_CODEC_ID = 1<<8, GF_M2TS_ES_IS_PMT = 1<<9
};
#define ABSTRACT_ES \
    GF_M2TS_Program *program; u32 flags; u32 pid; u32 stream_type; u32 mpeg4_es_id; \
    GF_SLConfig *slcfg; s16 component_tag; void *user; GF_List *props; u64 first_dts; Bool is_seg_start; u32 service_id;
typedef struct tag_m2ts_es { ABSTRACT_ES } GF_M2TS_ES;
typedef struct tag_m2ts_section_es { ABSTRACT_ES; GF_M2TS_SectionFilter *sec; } GF_M2TS_SECTION_ES;
typedef struct tag_m2ts_pes {
    ABSTRACT_ES; s16 cc; u32 lang; u32 depends_on_pid; u8 *pck_data; u32 pck_alloc_len;
    u32 pck_data_len; u32 pes_len; Bool rap; u64 PTS; u64 DTS; u8 *prev_data; u32 prev_data_len;
    u32 pes_start_packet_number; u32 pes_end_packet_number; u64 last_pcr_value;
    u32 last_pcr_value_pck_number; u64 before_last_pcr_value; u32 before_last_pcr_value_pck_number;
    u32 (*reframe)(void *ts, void *pes, Bool same_pts, u8 *data, u32 data_len, void *hdr);
    GF_M2TS_DVB_Subtitling_Descriptor sub; void *metadata_descriptor; u8 *temi_tc_desc; u32 temi_tc_desc_len;
    u32 temi_tc_desc_alloc_size; GF_M2TS_TemiTimecodeDescriptor temi_tc; Bool temi_pending;
    Bool is_resume; u8 dv_info[25]; u64 map_utc, map_utc_pcr, map_pcr; u8 *gpac_meta_dsi; u32 gpac_meta_dsi_size;
} GF_M2TS_PES;
struct __gf_dvb_mpe_ip_platform { int dummy; };
typedef struct __gf_download_session { int dummy; } GF_DownloadSession;
typedef struct { int dummy; } GF_M2TS_DSMCCController;
struct tag_m2ts_demux {
    GF_M2TS_ES *ess[GF_M2TS_MAX_STREAMS]; GF_List *programs; u32 nb_prog_pmt_received;
    Bool all_prog_pmt_received; Bool all_prog_processed; GF_List *SDTs; GF_M2TS_TDT_TOT *TDT_time;
    void (*on_event)(void *ts, u32 evt_type, void *par); void *user;
    u8 *buffer; u32 buffer_size; u32 alloc_size;
    GF_M2TS_SectionFilter *pat, *cat, *nit, *sdt, *eit, *tdt_tot;
    Bool has_4on2; FILE *pes_out; Bool seek_mode; Bool prefix_present; Bool direct_mpe;
    Bool dvb_h_demux; Bool notify_pes_timing;
    void (*on_mpe_event)(void *ts, u32 evt_type, void *par);
    struct __gf_dvb_mpe_ip_platform *ip_platform; u32 pck_number;
    GF_DownloadSession *dnload; const char *dvb_channels_conf_path;
    GF_List* ChannelAppList; Bool process_dmscc; char* dsmcc_root_dir;
    GF_List* dsmcc_controler; Bool table_reset; Bool split_mode;
};
typedef struct tag_m2ts_demux GF_M2TS_Demuxer;
enum { GF_M2TS_MPEG4_IOD_DESCRIPTOR = 0x1D, GF_M2TS_METADATA_POINTER_DESCRIPTOR = 0x25 };
enum { GF_M2TS_TABLE_START = 1, GF_M2TS_TABLE_END = 1<<1, GF_M2TS_TABLE_FOUND = 1<<2, GF_M2TS_TABLE_UPDATE = 1<<3, GF_M2TS_TABLE_REPEAT = 1<<4 };
enum {
    GF_M2TS_EVT_PAT_FOUND = 0, GF_M2TS_EVT_PAT_UPDATE, GF_M2TS_EVT_PAT_REPEAT,
    GF_M2TS_EVT_PMT_FOUND, GF_M2TS_EVT_PMT_REPEAT, GF_M2TS_EVT_PMT_UPDATE,
    GF_M2TS_EVT_SDT_FOUND, GF_M2TS_EVT_SDT_REPEAT, GF_M2TS_EVT_SDT_UPDATE,
    GF_M2TS_EVT_INT_FOUND, GF_M2TS_EVT_INT_REPEAT, GF_M2TS_EVT_INT_UPDATE,
    GF_M2TS_EVT_PES_PCK, GF_M2TS_EVT_PES_PCR, GF_M2TS_EVT_PES_TIMING,
    GF_M2TS_EVT_SL_PCK, GF_M2TS_EVT_IP_DATAGRAM, GF_M2TS_EVT_DURATION_ESTIMATED,
    GF_M2TS_EVT_PCK,  GF_M2TS_EVT_AAC_CFG, GF_M2TS_EVT_TDT, GF_M2TS_EVT_TOT,
    GF_M2TS_EVT_DVB_GENERAL, GF_M2TS_EVT_DVB_MPE, GF_M2TS_EVT_CAT_FOUND,
    GF_M2TS_EVT_CAT_REPEAT, GF_M2TS_EVT_CAT_UPDATE, GF_M2TS_EVT_AIT_FOUND,
    GF_M2TS_EVT_DSMCC_FOUND, GF_M2TS_EVT_TEMI_LOCATION, GF_M2TS_EVT_TEMI_TIMECODE,
    GF_M2TS_EVT_STREAM_REMOVED
};
enum {
    GF_M2TS_PES_PCK_RAP = 1, GF_M2TS_PES_PCK_AU_START = 1<<1, GF_M2TS_PES_PCK_I_FRAME = 1<<2,
    GF_M2TS_PES_PCK_P_FRAME = 1<<3, GF_M2TS_PES_PCK_B_FRAME = 1<<4, GF_M2TS_PES_PCK_DISCONTINUITY = 1<<5
};
enum {
    GF_M2TS_VIDEO_MPEG1 = 0x01, GF_M2TS_VIDEO_MPEG2 = 0x02, GF_M2TS_AUDIO_MPEG1 = 0x03,
    GF_M2TS_AUDIO_MPEG2 = 0x04, GF_M2TS_PRIVATE_SECTION = 0x05, GF_M2TS_PRIVATE_DATA = 0x06,
    GF_M2TS_VIDEO_MPEG4 = 0x10, GF_M2TS_SYSTEMS_MPEG4_PES = 0x12, GF_M2TS_VIDEO_H264 = 0x1B,
    GF_M2TS_VIDEO_HEVC = 0x24, GF_M2TS_VIDEO_HEVC_MCTS = 0x31, GF_M2TS_VIDEO_SVC = 0x1F,
    GF_M2TS_VIDEO_MVCD = 0x26, GF_M2TS_VIDEO_DCII = 0x80, GF_M2TS_VIDEO_VC1 = 0xEA,
    GF_M2TS_VIDEO_SHVC = 0x28, GF_M2TS_VIDEO_MHVC = 0x2A, GF_M2TS_VIDEO_VVC = 0x33,
    GF_M2TS_VIDEO_JPEG_XS = 0x32, GF_M2TS_JPEG_XS = 0x32, GF_M2TS_VIDEO_HEVC_TEMPORAL = 0x25, GF_M2TS_VIDEO_SHVC_TEMPORAL = 0x29, GF_M2TS_VIDEO_MHVC_TEMPORAL = 0x2B, GF_M2TS_VIDEO_VVC_TEMPORAL = 0x34, GF_M2TS_METADATA_PES = 0x15, GF_M2TS_METADATA_SECTION = 0x16, GF_M2TS_AUDIO_AAC = 0x0F, GF_M2TS_AUDIO_LATM_AAC = 0x11,
    GF_M2TS_AUDIO_AC3 = 0x81, GF_M2TS_AUDIO_DTS = 0x82, GF_M2TS_AUDIO_TRUEHD = 0x83,
    GF_M2TS_AUDIO_EC3 = 0x84, GF_M2TS_AUDIO_OPUS = 0x101, GF_M2TS_VIDEO_AV1 = 0x102,
    GF_M2TS_SUBTITLE_DVB = 0x100, GF_M2TS_DVB_TELETEXT = 0x152, GF_M2TS_DVB_VBI = 0x153,
    GF_M2TS_DVB_SUBTITLE = 0x154, GF_M2TS_METADATA_ID3_HLS = 0x155, GF_M2TS_TEMI = 0x27,
    GF_M2TS_MHAS_MAIN = 0x2D, GF_M2TS_MHAS_AUX = 0x2E, GF_M2TS_GREEN = 0x2C,
    GF_M2TS_HLS_AC3_CRYPT = 0xc1, GF_M2TS_HLS_EC3_CRYPT = 0xc2, GF_M2TS_HLS_AAC_CRYPT = 0xcf,
    GF_M2TS_HLS_AVC_CRYPT = 0xdb, GF_M2TS_SYSTEMS_MPEG4_SECTIONS = 0x13, GF_M2TS_13818_6_ANNEX_A = 0x0A, GF_M2TS_13818_6_ANNEX_B = 0x0B, GF_M2TS_13818_6_ANNEX_C = 0x0C, GF_M2TS_13818_6_ANNEX_D = 0x0D,  GF_M2TS_MPE_SECTIONS = 0x90, GF_M2TS_QUALITY_SEC = 0x2F, GF_M2TS_MORE_SEC = 0x30, GF_M2TS_ES_SEND_REPEATED_SECTIONS = 1<<16, GF_M2TS_ES_ALREADY_DECLARED = 1<<18, GF_M2TS_ES_FULL_AU = 1<<20, GF_M2TS_CHECK_DISC = 1<<21, GF_M2TS_CHECK_VC1 = 1<<22, GF_M2TS_ES_STATIC_FLAGS_MASK = 0x0000FFFF, GF_STREAM_AUDIO = 1, GF_STREAM_VISUAL = 2, GF_STREAM_SCENE = 3, GF_STREAM_OD = 4, GF_STREAM_MPEGJ = 5, GF_STREAM_SYSTEM = 6, GF_STREAM_TEXT = 7, GF_STREAM_METADATA = 9, GF_STREAM_USER_PRIVATE = 8, GF_STREAM_ENCRYPTED = 16, GF_CODECID_NONE = 0, GF_CODECID_MPEG1 = 1, GF_CODECID_MPEG2_MAIN = 2, GF_CODECID_MPEG4_PART2 = 3, GF_CODECID_AVC = 4, GF_CODECID_HEVC = 5, GF_CODECID_SVC = 6, GF_CODECID_LHVC = 7, GF_CODECID_VVC = 8, GF_CODECID_SMPTE_VC1 = 9, GF_CODECID_AV1 = 10, GF_CODECID_MPEG_AUDIO = 11, GF_CODECID_MPEG2_PART3 = 12, GF_CODECID_AAC_MPEG2_MP = 13, GF_CODECID_AAC_MPEG2_LCP = 14, GF_CODECID_AAC_MPEG2_SSRP = 23, GF_CODECID_AAC_MPEG4 = 16, GF_CODECID_MHAS = 17, GF_CODECID_AC3 = 18, GF_CODECID_EAC3 = 19, GF_CODECID_TRUEHD = 20, GF_CODECID_DTS_X = 21, GF_CODECID_OPUS = 22, GF_CODECID_SIMPLE_TEXT = 23, GF_CODECID_DVB_SUBS = 24, GF_CODECID_DVB_TELETEXT = 25, GF_PROP_PID_DECODER_CONFIG = 0x50444346, GF_PROP_PID_IN_IOD = 0x50494F44, GF_PROP_PID_TIMESCALE = 0x50545343, GF_PROP_PID_SCALABLE = 0x5053434C, GF_PROP_PID_SUBLAYER = 0x5053424C,  GF_CODECID_BIFS = 26, GF_PROP_PID_CODECID = 0x50434F44, GF_PROP_PID_CLOCK_ID = 0x50434C4B, GF_PROP_PID_DEPENDENCY_ID = 0x50444550, GF_PROP_PID_ID = 0x50494420, GF_PROP_PID_ESID = 0x50455349, GF_PROP_PID_STREAM_TYPE = 0x50535459, GF_FILTER_CLOCK_PCR = 0, GF_FILTER_CLOCK_PCR_DISC = 1, GF_FILTER_CLOCK_ODT = 2, GF_M2TS_RA_STREAM_AC3 = 0x41432d33, GF_M2TS_RA_STREAM_EAC3 = 0x45414333, GF_M2TS_RA_STREAM_VC1 = 0x56432d31, GF_M2TS_RA_STREAM_HEVC = 0x48455643, GF_M2TS_RA_STREAM_DTS1 = 0x44545331, GF_M2TS_RA_STREAM_DTS2 = 0x44545332, GF_M2TS_RA_STREAM_DTS3 = 0x44545333, GF_M2TS_RA_STREAM_OPUS = 0x4f707573, GF_M2TS_RA_STREAM_DOVI = 0x444f5649, GF_M2TS_RA_STREAM_AV1 = 0x41563031, GF_M2TS_RA_STREAM_GPAC = 0x47504143, GF_M2TS_DVB_EAC3_DESCRIPTOR = 0x7A, GF_M2TS_DVB_DATA_BROADCAST_ID_DESCRIPTOR = 0x66, GF_M2TS_DVB_SUBTITLING_DESCRIPTOR = 0x59, GF_M2TS_DVB_TELETEXT_DESCRIPTOR = 0x56, GF_M2TS_DVB_VBI_DATA_DESCRIPTOR = 0x45, GF_M2TS_DVB_STREAM_IDENTIFIER_DESCRIPTOR = 0x52, GF_M2TS_ISO_639_LANGUAGE_DESCRIPTOR = 0x0A, GF_M2TS_REGISTRATION_DESCRIPTOR = 0x05, GF_M2TS_DATA_STREAM_ALIGNEMENT_DESCRIPTOR = 0x06, GF_M2TS_AVC_VIDEO_DESCRIPTOR = 0x28, GF_M2TS_HEVC_VIDEO_DESCRIPTOR = 0x38, GF_M2TS_DVB_LOGICAL_CHANNEL_DESCRIPTOR = 0x83, GF_M2TS_DOLBY_VISION_DESCRIPTOR = 0xB0, GF_M2TS_MPEG4_SL_DESCRIPTOR = 0x1E, GF_M2TS_MPEG4_ODUPDATE_DESCRIPTOR = 0x35, GF_M2TS_SVC_EXTENSION_DESCRIPTOR = 0x30, GF_M2TS_HIERARCHY_DESCRIPTOR = 0x04, GF_M2TS_METADATA_DESCRIPTOR = 0x26, GF_M2TS_PES_FRAMING_SKIP = 0, GF_M2TS_PES_FRAMING_RAW = 2, GF_M2TS_PES_FRAMING_DEFAULT = 3
};
enum { GF_M2TS_META_ID3 = 0x49443330 };
enum { METADATA_CARRIAGE_SAME_TS = 0, METADATA_CARRIAGE_DIFFERENT_TS = 1, METADATA_CARRIAGE_PS = 2, METADATA_CARRIAGE_OTHER = 3 };
enum { GF_PLAYBACK_MODE_FASTFORWARD = 1 };
enum { GF_PROP_PCK_CUE_START = 0x50435553 };
enum {
    GF_PROP_PID_DURATION = 0x50445552, GF_PROP_PID_UNFRAMED = 0x50554E46,
    GF_PROP_PID_ORIG_STREAM_TYPE = 0x504F5354, GF_PROP_PID_PROTECTION_SCHEME_TYPE = 0x5050524F,
    GF_PROP_PID_SERVICE_ID = 0x50535256, GF_PROP_PID_LANGUAGE = 0x504C4E47,
    GF_PROP_PID_WIDTH = 0x50574944, GF_PROP_PID_HEIGHT = 0x50484549,
    GF_PROP_PID_SAMPLE_RATE = 0x50534152, GF_PROP_PID_NUM_CHANNELS = 0x504E4348,
    GF_PROP_PID_DOLBY_VISION = 0x50445649, GF_PROP_PID_ISOM_SUBTYPE = 0x50495354,
    GF_PROP_PID_PLAYBACK_MODE = 0x5050424B, GF_PROP_PID_META_DEMUX_CODEC_ID = 0x504D4349,
    GF_PROP_PID_META_DEMUX_CODEC_NAME = 0x504D434E, GF_PROP_PID_META_DEMUX_OPAQUE = 0x504D4351,
    GF_PROP_PID_UNFRAMED_LATM = 0x50554E4C
};
GF_M2TS_MetadataPointerDescriptor *gf_m2ts_read_metadata_pointer_descriptor(GF_BitStream *bs, u32 len);
typedef struct __gf_filter GF_Filter;
enum { DMX_TUNE_DONE=0, DMX_TUNE_INIT, DMX_TUNE_WAIT_PROGS, DMX_TUNE_WAIT_SEEK };
typedef struct {
    const char *temi_url;
    Bool dsmcc, seeksrc, sigfrag, dvbtxt;
    GF_Filter *filter;
    void *ipid;
    GF_M2TS_Demuxer *ts;
    void *eit_pid;
    Bool is_file; u64 file_size; Bool in_seek; Bool initial_play_done;
    u32 nb_playing, nb_stop_pending;
    GF_Fraction64 duration; u64 first_pcr_found; u16 pcr_pid; u64 nb_pck_at_pcr;
    u32 map_time_on_prog_id; Double media_start_range;
    u32 mux_tune_state; u32 wait_for_progs; Bool is_dash;
} GF_M2TSDmxCtx;
void *gf_filter_get_udta(GF_Filter *f);
typedef struct { u16 application_format; u32 application_format_identifier; u8 format; u32 format_identifier; u8 service_id; u8 locator_record_flag; u32 locator_length; char *locator_data; u8 decoder_config_flags; Bool dsmcc_flag; u8 service_id_record_length; char *service_id_record; u8 decoder_config_length; u8 *decoder_config; u8 decoder_config_id_length; u8 *decoder_config_id; u8 decoder_config_service_id; } GF_M2TS_MetadataDescriptor;
void gf_m2ts_process_mpeg4section(void *d, void *e, void *s, u8 t, u16 et, u8 v, u8 l, u32 st);
void *gf_m2ts_section_filter_new(void *cbk, u32 service_id);
void gf_m2ts_section_filter_del(void *sec);
void gf_m2ts_metadata_pointer_descriptor_del(GF_M2TS_MetadataPointerDescriptor *desc);
GF_Err gf_list_del_item(GF_List *ptr, void *item);
static void gf_m2ts_metadata_descriptor_del(GF_M2TS_MetadataDescriptor *metad) {
	if (metad) {
		if (metad->service_id_record) gf_free(metad->service_id_record);
		if (metad->decoder_config) gf_free(metad->decoder_config);
		if (metad->decoder_config_id) gf_free(metad->decoder_config_id);
		gf_free(metad);
	}
}
static GF_M2TS_MetadataDescriptor *gf_m2ts_read_metadata_descriptor(GF_BitStream *bs, u32 length) {
	GF_M2TS_MetadataDescriptor *d;
	GF_SAFEALLOC(d, GF_M2TS_MetadataDescriptor);
	if (!d) return NULL;
	d->application_format = gf_bs_read_u16(bs);
	if (d->application_format == 0xFFFF) { d->application_format_identifier = gf_bs_read_u32(bs); }
	d->format = gf_bs_read_u8(bs);
	if (d->format == 0xFF) { d->format_identifier = gf_bs_read_u32(bs); }
	d->service_id = gf_bs_read_u8(bs);
	d->decoder_config_flags = gf_bs_read_int(bs, 3);
	d->dsmcc_flag = (gf_bs_read_int(bs, 1) ? GF_TRUE : GF_FALSE);
	gf_bs_read_int(bs, 4);
	if (d->dsmcc_flag) {
		d->service_id_record_length = gf_bs_read_u8(bs);
		d->service_id_record = (char *)gf_malloc(d->service_id_record_length);
		gf_bs_read_data(bs, d->service_id_record, d->service_id_record_length);
	}
	if (d->decoder_config_flags == 1) {
		d->decoder_config_length = gf_bs_read_u8(bs);
		d->decoder_config = (char *)gf_malloc(d->decoder_config_length);
		gf_bs_read_data(bs, d->decoder_config, d->decoder_config_length);
	}
	if (d->decoder_config_flags == 3) {
		d->decoder_config_id_length = gf_bs_read_u8(bs);
		d->decoder_config_id = (char *)gf_malloc(d->decoder_config_id_length);
		gf_bs_read_data(bs, d->decoder_config_id, d->decoder_config_id_length);
	}
	if (d->decoder_config_flags == 4) { d->decoder_config_service_id = gf_bs_read_u8(bs); }
	return d;
}
static void gf_m2ts_es_del(GF_M2TS_ES *es, GF_M2TS_Demuxer *ts) {
	gf_list_del_item(es->program->streams, es);
	if (ts->on_event) ts->on_event(ts, GF_M2TS_EVT_STREAM_REMOVED, es);
	if (es->flags & GF_M2TS_ES_IS_SECTION) {
		GF_M2TS_SECTION_ES *ses = (GF_M2TS_SECTION_ES *)es;
		if (ses->sec) gf_m2ts_section_filter_del(ses->sec);
	} else if (es->pid != es->program->pmt_pid) {
		GF_M2TS_PES *pes = (GF_M2TS_PES *)es;
		if ((pes->flags & GF_M2TS_INHERIT_PCR) && ts->ess[es->program->pcr_pid] == es)
			ts->ess[es->program->pcr_pid] = NULL;
		if (pes->pck_data) gf_free(pes->pck_data);
		if (pes->prev_data) gf_free(pes->prev_data);
		if (pes->temi_tc_desc) gf_free(pes->temi_tc_desc);
		if (pes->metadata_descriptor) gf_m2ts_metadata_descriptor_del(pes->metadata_descriptor);
	}
	if (es->slcfg) gf_free(es->slcfg);
	gf_free(es);
}
void gf_m2ts_set_pes_framing(GF_M2TS_PES *pes, u32 mode);
void *gf_list_last(GF_List *ptr); void *gf_list_rem_last(GF_List *ptr); void *gf_list_rem(GF_List *ptr, u32 item);
s32 gf_list_find(GF_List *ptr, void *item);
void m2tsdmx_setup_program(GF_M2TSDmxCtx *ctx, GF_M2TS_Program *prog);
void m2tsdmx_declare_pid(GF_M2TSDmxCtx *ctx, GF_M2TS_PES *stream, GF_ESD *esd);
void m2tsdmx_update_sdt(GF_M2TS_Demuxer *ts, GF_FilterPid *opid);
void m2tsdmx_send_packet(GF_M2TSDmxCtx *ctx, void *param);
void m2tsdmx_send_sl_packet(GF_M2TSDmxCtx *ctx, void *param);
void m2tsdmx_estimate_duration(GF_M2TSDmxCtx *ctx, GF_M2TS_ES *es);
GF_FilterPacket *gf_filter_pck_new_alloc(GF_FilterPid *PID, u32 data_size, u8 **data);
GF_FilterPacket *gf_filter_pck_new_shared(GF_FilterPid *PID, const u8 *data, u32 data_size, void *destruct);
GF_Err gf_filter_pck_set_cts(GF_FilterPacket *pck, u64 cts);
typedef int GF_FilterClockType;
GF_Err gf_filter_pck_set_clock_type(GF_FilterPacket *pck, GF_FilterClockType ctype);
GF_FilterPid *gf_filter_pid_new(GF_Filter *filter);
u32 gf_filter_get_opid_count(GF_Filter *filter);
GF_FilterPid *gf_filter_get_opid(GF_Filter *filter, u32 idx);
const GF_PropertyValue *gf_filter_pid_get_property(GF_FilterPid *PID, u32 prop_4cc);
void gf_filter_pid_set_name(GF_FilterPid *PID, const char *name);
u32 gf_codecid_type(u32 codecid);
const char *gf_stream_type_name(u32 streamType);
GF_M2TS_Demuxer *gf_m2ts_demux_new(void);
void gf_m2ts_demux_del(GF_M2TS_Demuxer *demux);
void gf_m2ts_demux_dmscc_init(GF_M2TS_Demuxer *demux);
void *gf_dvb_mpe_section_new(void);
void gf_dvb_mpe_section_del(void *es);
#define GF_HLS_SAMPLE_AES_SCHEME GF_4CC('s','a','e','s')
#define PROP_STRING_NO_COPY(_val) (GF_PropertyValue){.type=15, .value.string = _val}
#define PROP_FRAC64(_val) (GF_PropertyValue){.type=GF_PROP_FRACTION64, .value.lfrac = _val}
#define PROP_4CC(_v) (GF_PropertyValue){.type=GF_PROP_4CC, .value._4cc = _v}
#define PROP_STRING(_val) (GF_PropertyValue){.type=7, .value.string = _val}

static void gf_m2ts_process_pmt(GF_M2TS_Demuxer *ts, GF_M2TS_SECTION_ES *pmt, GF_List *sections, u8 table_id, u16 ex_table_id, u8 version_number, u8 last_section_number, u32 status)
{
	u32 info_length, pos, desc_len, evt_type, nb_es,i;
	u32 nb_sections;
	u32 data_size;
	u32 nb_hevc, nb_hevc_temp, nb_shvc, nb_shvc_temp, nb_mhvc, nb_mhvc_temp;
	unsigned char *data;
	GF_M2TS_Section *section;
	GF_Err e = GF_OK;

	/*wait for the last section */
	if (!(status&GF_M2TS_TABLE_END)) return;

	nb_es = 0;

	/*skip if already received but no update detected (eg same data) */
	if ((status&GF_M2TS_TABLE_REPEAT) && !(status&GF_M2TS_TABLE_UPDATE))  {
		if (ts->on_event) ts->on_event(ts, GF_M2TS_EVT_PMT_REPEAT, pmt->program);
		return;
	}

	if (pmt->sec->demux_restarted) {
		pmt->sec->demux_restarted = 0;
		return;
	}
	GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] PMT Found or updated\n"));

	nb_sections = gf_list_count(sections);
	if (nb_sections > 1) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("PMT on multiple sections not supported\n"));
	}

	section = (GF_M2TS_Section *)gf_list_get(sections, 0);
	data = section->data;
	data_size = section->data_size;

	if (data_size < 6) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PMT header data size %d\n", data_size ) );
		return;
	}

	pmt->program->pcr_pid = ((data[0] & 0x1f) << 8) | data[1];

	info_length = ((data[2]&0xf)<<8) | data[3];
	if (info_length + 4 > data_size) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("Broken PMT first loop, %d bytes avail but first loop size %d\n", data_size, info_length));
		return;
	} else if (info_length != 0) {
		/* ...Read Descriptors ... */
		u32 tag, len;
		u32 first_loop_len = 0;
		tag = (u32) data[4];
		len = (u32) data[5];
		while (info_length > first_loop_len) {
			if (tag == GF_M2TS_MPEG4_IOD_DESCRIPTOR) {
				if ((len>2) && (len - 2 <= info_length)) {
					u32 size;
					GF_BitStream *iod_bs;
					iod_bs = gf_bs_new((char *)data+8, len-2, GF_BITSTREAM_READ);
					if (pmt->program->pmt_iod) gf_odf_desc_del((GF_Descriptor *)pmt->program->pmt_iod);
					pmt->program->pmt_iod = NULL;
					e = gf_odf_parse_descriptor(iod_bs , (GF_Descriptor **) &pmt->program->pmt_iod, &size);
					gf_bs_del(iod_bs );
					if (pmt->program->pmt_iod && pmt->program->pmt_iod->tag != GF_ODF_IOD_TAG) {
						GF_LOG( GF_LOG_ERROR, GF_LOG_CONTAINER, ("pmt iod has wrong tag %d\n", pmt->program->pmt_iod->tag) );
						gf_odf_desc_del((GF_Descriptor *)pmt->program->pmt_iod);
						pmt->program->pmt_iod = NULL;
					}
					if (e==GF_OK) {
						/*remember program number for service/program selection*/
						if (pmt->program->pmt_iod) {
							pmt->program->pmt_iod->ServiceID = pmt->program->number;
							/*if empty IOD (freebox case), discard it and use dynamic declaration of object*/
							if (!gf_list_count(pmt->program->pmt_iod->ESDescriptors)) {
								gf_odf_desc_del((GF_Descriptor *)pmt->program->pmt_iod);
								pmt->program->pmt_iod = NULL;
							}
						}
					}
				} else {
					GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("Broken IOD! len %d less than 2 bytes to declare IOD\n", len));
				}
			} else if (tag == GF_M2TS_METADATA_POINTER_DESCRIPTOR) {
				GF_BitStream *metadatapd_bs;
				GF_M2TS_MetadataPointerDescriptor *metapd;

				if (data_size <= 8 || data_size-6 < (u32)len)
					break;

				metadatapd_bs = gf_bs_new((char *)data+6, len, GF_BITSTREAM_READ);
				metapd = gf_m2ts_read_metadata_pointer_descriptor(metadatapd_bs, len);
				gf_bs_del(metadatapd_bs);
				if (metapd->application_format_identifier == GF_M2TS_META_ID3 &&
				        metapd->format_identifier == GF_M2TS_META_ID3 &&
				        metapd->carriage_flag == METADATA_CARRIAGE_SAME_TS) {
					/*HLS ID3 Metadata */
					if (pmt->program->metadata_pointer_descriptor)
						gf_m2ts_metadata_pointer_descriptor_del(pmt->program->metadata_pointer_descriptor);
					pmt->program->metadata_pointer_descriptor = metapd;
				} else {
					/* don't know what to do with it for now, delete */
					gf_m2ts_metadata_pointer_descriptor_del(metapd);
				}
			} else {
				GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] Skipping descriptor (0x%x) and others not supported\n", tag));
			}
			first_loop_len += 2 + len;
		}
	}
	if (data_size <= 4 + info_length) return;
	data += 4 + info_length;
	data_size -= 4 + info_length;
	pos = 0;

	/* count de number of program related PMT received */
	for(i=0; i<gf_list_count(ts->programs); i++) {
		GF_M2TS_Program *prog = (GF_M2TS_Program *)gf_list_get(ts->programs,i);
		if(prog->pmt_pid == pmt->pid) {
			break;
		}
	}

	nb_hevc = nb_hevc_temp = nb_shvc = nb_shvc_temp = nb_mhvc = nb_mhvc_temp = 0;
	while (pos<data_size) {
		GF_M2TS_PES *pes = NULL;
		GF_M2TS_SECTION_ES *ses = NULL;
		GF_M2TS_ES *es = NULL;
		Bool inherit_pcr = 0;
		Bool pmt_pid_reused = GF_FALSE;
		u32 pid, stream_type, reg_desc_format;

		if (pos + 5 > data_size) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("Broken PMT! size %d but position %d and need at least 5 bytes to declare es\n", data_size, pos));
			break;
		}

		stream_type = data[0];
		pid = ((data[1] & 0x1f) << 8) | data[2];
		desc_len = ((data[3] & 0xf) << 8) | data[4];

		if (!pid) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID 0 for es descriptor in PMT of program %d, reserved for PAT\n", pmt->pid) );
			break;
		}
		if (pid==1) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID 1 for es descriptor in PMT of program %d, reserved for CAT\n", pmt->pid) );
			break;
		}

		if (pid==pmt->pid) {
			pmt_pid_reused = GF_TRUE;
		} else {
			u32 pcount = gf_list_count(ts->programs);
			for(i=0; i<pcount; i++) {
				GF_M2TS_Program *prog = (GF_M2TS_Program *)gf_list_get(ts->programs,i);
				if(prog->pmt_pid == pid) {
					pmt_pid_reused = GF_TRUE;
					break;
				}
			}
		}
		if (pmt_pid_reused) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID %d for es descriptor in PMT of program %d, this PID is already assigned to a PMT\n", pid, pmt->pid) );
			break;
		}

		if (desc_len > data_size-5) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PMT es descriptor size for PID %d\n", pid ) );
			break;
		}

		if (!pid) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID 0 for es descriptor in PMT of program %d, reserved for PAT\n", pmt->pid) );
			break;
		}
		if (pid==1) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID 1 for es descriptor in PMT of program %d, reserved for CAT\n", pmt->pid) );
			break;
		}

		if (pid==pmt->pid) {
			pmt_pid_reused = GF_TRUE;
		} else {
			u32 pcount = gf_list_count(ts->programs);
			for(i=0; i<pcount; i++) {
				GF_M2TS_Program *prog = (GF_M2TS_Program *)gf_list_get(ts->programs,i);
				if(prog->pmt_pid == pid) {
					pmt_pid_reused = GF_TRUE;
					break;
				}
			}
		}

		if (pmt_pid_reused) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PID %d for es descriptor in PMT of program %d, this PID is already assigned to a PMT\n", pid, pmt->pid) );
			break;
		}

		GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("stream_type :%d \n",stream_type));
		if ((stream_type==GF_M2TS_JPEG_XS) && gf_opts_get_bool("core", "m2ts-vvc-old"))
			stream_type = GF_M2TS_VIDEO_VVC;

		switch (stream_type) {

		/* PES */
		case GF_M2TS_VIDEO_MPEG1:
		case GF_M2TS_VIDEO_MPEG2:
		case GF_M2TS_VIDEO_DCII:
		case GF_M2TS_VIDEO_MPEG4:
		case GF_M2TS_SYSTEMS_MPEG4_PES:
		case GF_M2TS_VIDEO_H264:
		case GF_M2TS_VIDEO_SVC:
		case GF_M2TS_VIDEO_MVCD:
		case GF_M2TS_VIDEO_HEVC:
		case GF_M2TS_VIDEO_HEVC_MCTS:
		case GF_M2TS_VIDEO_HEVC_TEMPORAL:
		case GF_M2TS_VIDEO_SHVC:
		case GF_M2TS_VIDEO_SHVC_TEMPORAL:
		case GF_M2TS_VIDEO_MHVC:
		case GF_M2TS_VIDEO_MHVC_TEMPORAL:
		case GF_M2TS_VIDEO_VVC:
		case GF_M2TS_VIDEO_VVC_TEMPORAL:
		case GF_M2TS_VIDEO_VC1:
		case GF_M2TS_HLS_AVC_CRYPT:
			inherit_pcr = 1;
		case GF_M2TS_AUDIO_MPEG1:
		case GF_M2TS_AUDIO_MPEG2:
		case GF_M2TS_AUDIO_AAC:
		case GF_M2TS_AUDIO_LATM_AAC:
		case GF_M2TS_AUDIO_AC3:
		case GF_M2TS_AUDIO_EC3:
		case GF_M2TS_AUDIO_DTS:
		case GF_M2TS_AUDIO_TRUEHD:
		case GF_M2TS_AUDIO_OPUS:
		case GF_M2TS_MHAS_MAIN:
		case GF_M2TS_MHAS_AUX:
		case GF_M2TS_SUBTITLE_DVB:
		case GF_M2TS_METADATA_PES:
		case GF_M2TS_HLS_AAC_CRYPT:
		case GF_M2TS_HLS_AC3_CRYPT:
		case GF_M2TS_HLS_EC3_CRYPT:
		case 0xA1:
			GF_SAFEALLOC(pes, GF_M2TS_PES);
			if (!pes) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG2TS] Failed to allocate ES for pid %d\n", pid));
				return;
			}
			pes->cc = -1;
			pes->flags = GF_M2TS_ES_IS_PES;
			if (inherit_pcr)
				pes->flags |= GF_M2TS_INHERIT_PCR;
			es = (GF_M2TS_ES *)pes;
			break;
		case GF_M2TS_PRIVATE_DATA:
			GF_SAFEALLOC(pes, GF_M2TS_PES);
			if (!pes) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG2TS] Failed to allocate ES for pid %d\n", pid));
				return;
			}
			pes->cc = -1;
			pes->flags = GF_M2TS_ES_IS_PES;
			es = (GF_M2TS_ES *)pes;
			break;
		/* Sections */
		case GF_M2TS_SYSTEMS_MPEG4_SECTIONS:
			GF_SAFEALLOC(ses, GF_M2TS_SECTION_ES);
			if (!ses) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG2TS] Failed to allocate ES for pid %d\n", pid));
				return;
			}
			es = (GF_M2TS_ES *)ses;
			es->flags |= GF_M2TS_ES_IS_SECTION;
			/* carriage of ISO_IEC_14496 data in sections */
			if (stream_type == GF_M2TS_SYSTEMS_MPEG4_SECTIONS) {
				/*MPEG-4 sections need to be fully checked: if one section is lost, this means we lost
				one SL packet in the AU so we must wait for the complete section again*/
				ses->sec = gf_m2ts_section_filter_new(gf_m2ts_process_mpeg4section, 0);
				/*create OD container*/
				if (!pmt->program->additional_ods) {
					pmt->program->additional_ods = gf_list_new();
					ts->has_4on2 = 1;
				}
			}
			break;

		case GF_M2TS_13818_6_ANNEX_A:
		case GF_M2TS_13818_6_ANNEX_B:
		case GF_M2TS_13818_6_ANNEX_C:
		case GF_M2TS_13818_6_ANNEX_D:
		case GF_M2TS_PRIVATE_SECTION:
		case GF_M2TS_QUALITY_SEC:
		case GF_M2TS_MORE_SEC:
			GF_SAFEALLOC(ses, GF_M2TS_SECTION_ES);
			if (!ses) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG2TS] Failed to allocate ES for pid %d\n", pid));
				return;
			}
			es = (GF_M2TS_ES *)ses;
			es->flags |= GF_M2TS_ES_IS_SECTION;
			es->pid = pid;
			es->service_id = pmt->program->number;
			if (stream_type == GF_M2TS_PRIVATE_SECTION) {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("AIT sections on pid %d\n", pid));
			} else if (stream_type == GF_M2TS_QUALITY_SEC) {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("Quality metadata sections on pid %d\n", pid));
			} else if (stream_type == GF_M2TS_MORE_SEC) {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("MORE sections on pid %d\n", pid));
			} else {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("stream type DSM CC user private sections on pid %d \n", pid));
			}
			/* NULL means: trigger the call to on_event with DVB_GENERAL type and the raw section as payload */
			ses->sec = gf_m2ts_section_filter_new(NULL, 1);
			//ses->sec->service_id = pmt->program->number;
			break;

		case GF_M2TS_MPE_SECTIONS:
			if (! ts->prefix_present) {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("stream type MPE found : pid = %d \n", pid));
#ifdef GPAC_ENABLE_MPE
				es = gf_dvb_mpe_section_new();
				if (es->flags & GF_M2TS_ES_IS_SECTION) {
					/* NULL means: trigger the call to on_event with DVB_GENERAL type and the raw section as payload */
					((GF_M2TS_SECTION_ES*)es)->sec = gf_m2ts_section_filter_new(NULL, 1);
				}
#endif
				break;
			}

		default:
			GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] Stream type (0x%x) for PID %d not supported\n", stream_type, pid ) );
			break;
		}

		if (es) {
			es->stream_type = (stream_type==GF_M2TS_PRIVATE_DATA) ? 0 : stream_type;
			es->program = pmt->program;
			es->pid = pid;
			es->component_tag = -1;
		}

		pos += 5;
		data += 5;

		while (desc_len) {
			if (pos + 2 > data_size) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("Broken PMT descriptor! size %d but position %d and need at least 2 bytes to parse descriptor\n", data_size, pos));
				break;
			}
			u8 tag = data[0];
			u32 len = data[1];

			if (pos + 2 + len > data_size) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("Broken PMT descriptor! size %d, desc size %d but position %d\n", data_size, len, pos));
				break;
			}

			if (es) {
				switch (tag) {
				case GF_M2TS_ISO_639_LANGUAGE_DESCRIPTOR:
					if (pes && (len>=3) )
						pes->lang = GF_4CC(' ', data[2], data[3], data[4]);
					break;
				case GF_M2TS_MPEG4_SL_DESCRIPTOR:
					if (len>=2) {
						es->mpeg4_es_id = ( (u32) data[2] & 0x1f) << 8  | data[3];
						es->flags |= GF_M2TS_ES_IS_SL;
					}
					break;
				case GF_M2TS_REGISTRATION_DESCRIPTOR:
					if (len>=4) {
						reg_desc_format = GF_4CC(data[2], data[3], data[4], data[5]);
						/* cf https://smpte-ra.org/registered-mpeg-ts-ids */
						switch (reg_desc_format) {
						case GF_M2TS_RA_STREAM_AC3:
							//don't overwrite if alread EAC3 or TrueHD
							if ((es->stream_type != GF_M2TS_AUDIO_EC3) && (es->stream_type != GF_M2TS_AUDIO_TRUEHD))
								es->stream_type = GF_M2TS_AUDIO_AC3;
							break;
						case GF_M2TS_RA_STREAM_EAC3:
							//don't overwrite if alread AC3 or TrueHD
							if ((es->stream_type != GF_M2TS_AUDIO_AC3) && (es->stream_type != GF_M2TS_AUDIO_TRUEHD))
								es->stream_type = GF_M2TS_AUDIO_EC3;
							break;
						case GF_M2TS_RA_STREAM_VC1:
							es->stream_type = GF_M2TS_VIDEO_VC1;
							break;
						case GF_M2TS_RA_STREAM_HEVC:
							es->stream_type = GF_M2TS_VIDEO_HEVC;
							break;
						case GF_M2TS_RA_STREAM_DTS1:
						case GF_M2TS_RA_STREAM_DTS2:
						case GF_M2TS_RA_STREAM_DTS3:
							es->stream_type = GF_M2TS_AUDIO_DTS;
							break;
						case GF_M2TS_RA_STREAM_OPUS:
							es->stream_type = GF_M2TS_AUDIO_OPUS;
							break;
						case GF_M2TS_RA_STREAM_DOVI:
							break;
						case GF_M2TS_RA_STREAM_AV1:
							es->stream_type = GF_M2TS_VIDEO_AV1;
							break;

						case GF_M2TS_RA_STREAM_GPAC:
							if (len<8) break;
							es->stream_type = GF_4CC(data[6], data[7], data[8], data[9]);
							es->flags |= GF_M2TS_GPAC_CODEC_ID;
							if ((len>12) && (es->flags & GF_M2TS_ES_IS_PES)) {
								pes = (GF_M2TS_PES*)es;
								pes->gpac_meta_dsi_size = len-4;
								pes->gpac_meta_dsi = gf_realloc(pes->gpac_meta_dsi, pes->gpac_meta_dsi_size);
								if (pes->gpac_meta_dsi)
									memcpy(pes->gpac_meta_dsi, data+6, pes->gpac_meta_dsi_size);
							}
							break;
						default:
							GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("Unknown registration descriptor %s\n", gf_4cc_to_str(reg_desc_format) ));
							break;
						}
					}
					break;
				case GF_M2TS_DVB_EAC3_DESCRIPTOR:
					es->stream_type = GF_M2TS_AUDIO_EC3;
					break;
				case GF_M2TS_DVB_DATA_BROADCAST_ID_DESCRIPTOR:
					if (len>=2) {
						u32 id = data[2]<<8 | data[3];
						if ((id == 0xB) && ses && !ses->sec) {
							ses->sec = gf_m2ts_section_filter_new(NULL, 1);
						}
					}
					break;
				case GF_M2TS_DVB_SUBTITLING_DESCRIPTOR:
					if (pes && (len>=8)) {
						pes->sub.language[0] = data[2];
						pes->sub.language[1] = data[3];
						pes->sub.language[2] = data[4];
						pes->sub.type = data[5];
						pes->sub.composition_page_id = (data[6]<<8) | data[7];
						pes->sub.ancillary_page_id = (data[8]<<8) | data[9];
					}
					es->stream_type = GF_M2TS_DVB_SUBTITLE;
					break;
				case GF_M2TS_DVB_STREAM_IDENTIFIER_DESCRIPTOR:
					if (len>=1) {
						es->component_tag = data[2];
						GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("Component Tag: %d on Program %d\n", es->component_tag, es->program->number));
					}
					break;
				case GF_M2TS_DVB_TELETEXT_DESCRIPTOR:
					es->stream_type = GF_M2TS_DVB_TELETEXT;
					break;
				case GF_M2TS_DVB_VBI_DATA_DESCRIPTOR:
					es->stream_type = GF_M2TS_DVB_VBI;
					break;
				case GF_M2TS_HIERARCHY_DESCRIPTOR:
					if (pes && (len>=4)) {
						u8 hierarchy_embedded_layer_index;
						GF_BitStream *hbs = gf_bs_new((const char *)data, data_size, GF_BITSTREAM_READ);
						/*u32 skip = */gf_bs_read_int(hbs, 16);
						/*u8 res1 = */gf_bs_read_int(hbs, 1);
						/*u8 temp_scal = */gf_bs_read_int(hbs, 1);
						/*u8 spatial_scal = */gf_bs_read_int(hbs, 1);
						/*u8 quality_scal = */gf_bs_read_int(hbs, 1);
						/*u8 hierarchy_type = */gf_bs_read_int(hbs, 4);
						/*u8 res2 = */gf_bs_read_int(hbs, 2);
						/*u8 hierarchy_layer_index = */gf_bs_read_int(hbs, 6);
						/*u8 tref_not_present = */gf_bs_read_int(hbs, 1);
						/*u8 res3 = */gf_bs_read_int(hbs, 1);
						hierarchy_embedded_layer_index = gf_bs_read_int(hbs, 6);
						/*u8 res4 = */gf_bs_read_int(hbs, 2);
						/*u8 hierarchy_channel = */gf_bs_read_int(hbs, 6);
						gf_bs_del(hbs);

						pes->depends_on_pid = 1+hierarchy_embedded_layer_index;
					}
					break;
				case GF_M2TS_METADATA_DESCRIPTOR:
				{
					GF_BitStream *metadatad_bs;
					GF_M2TS_MetadataDescriptor *metad;
					metadatad_bs = gf_bs_new((char *)data+2, len, GF_BITSTREAM_READ);
					metad = gf_m2ts_read_metadata_descriptor(metadatad_bs, len);
					gf_bs_del(metadatad_bs);
					if (metad->application_format_identifier == GF_M2TS_META_ID3 &&
					        metad->format_identifier == GF_M2TS_META_ID3) {
						/*HLS ID3 Metadata */
						if (pes) {
							if (pes->metadata_descriptor)
								gf_m2ts_metadata_descriptor_del(pes->metadata_descriptor);
							pes->metadata_descriptor = metad;
							pes->stream_type = GF_M2TS_METADATA_ID3_HLS;
						}
					} else {
						/* don't know what to do with it for now, delete */
						gf_m2ts_metadata_descriptor_del(metad);
					}
				}
				break;
				case GF_M2TS_HEVC_VIDEO_DESCRIPTOR:
					if (es) es->stream_type = GF_M2TS_VIDEO_HEVC;
					break;

				case GF_M2TS_AVC_VIDEO_DESCRIPTOR:
					if (es) es->stream_type = GF_M2TS_VIDEO_H264;
					break;

				case GF_M2TS_DOLBY_VISION_DESCRIPTOR:
					if (pes && (len>=5)) {
						GF_BitStream *hbs = gf_bs_new((const char *)data+2, len, GF_BITSTREAM_READ);
						pes->dv_info[0] = gf_bs_read_u8(hbs);
						pes->dv_info[1] = gf_bs_read_u8(hbs);
						pes->dv_info[2] = gf_bs_read_u8(hbs);
						pes->dv_info[3] = gf_bs_read_u8(hbs);
						if (! (pes->dv_info[3] & 0x1) ) {
							pes->depends_on_pid = gf_bs_read_int(hbs, 13);
							gf_bs_read_int(hbs, 3);
						}
						pes->dv_info[4] = gf_bs_read_u8(hbs);
						gf_bs_del(hbs);
					}
					break;

				default:
					GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] skipping descriptor (0x%x) not supported\n", tag));
					break;
				}
			}

			data += len+2;
			pos += len+2;
			if (desc_len < len+2) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid PMT es descriptor size for PID %d\n", pid ) );
				break;
			}
			desc_len-=len+2;
		}
		if (es && !es->stream_type) {
			gf_free(es);
			es = NULL;
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Private Stream type (0x%x) for PID %d not supported\n", stream_type, pid ) );
		}
		if (!es) continue;

		if (pes && (stream_type==GF_M2TS_PRIVATE_DATA) && (es->stream_type!=stream_type) && pes->dv_info[0]) {
			//non-compatible base layer dolby vision
			pes->dv_info[24] = 1;
		}

		if (ts->ess[pid]) {
			//this is component reuse across programs, overwrite the previously declared stream ...
			if (status & GF_M2TS_TABLE_FOUND) {
				GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d reused across programs %d and %d, not completely supported\n", pid, ts->ess[pid]->program->number, es->program->number ) );

				//add stream to program but don't reassign the pid table until the stream is playing (>GF_M2TS_PES_FRAMING_SKIP)
				gf_list_add(pmt->program->streams, es);
				if (!(es->flags & GF_M2TS_ES_IS_SECTION) ) gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_SKIP);

				nb_es++;
				//skip assignment below
				es = NULL;
			}
			/*watchout for pmt update - FIXME this likely won't work in most cases*/
			else {

				GF_M2TS_ES *o_es = ts->ess[es->pid];

				if ((o_es->stream_type == es->stream_type)
				        && ((o_es->flags & GF_M2TS_ES_STATIC_FLAGS_MASK) == (es->flags & GF_M2TS_ES_STATIC_FLAGS_MASK))
				        && (o_es->mpeg4_es_id == es->mpeg4_es_id)
				        && ((o_es->flags & GF_M2TS_ES_IS_SECTION) || ((GF_M2TS_PES *)o_es)->lang == ((GF_M2TS_PES *)es)->lang)
				   ) {
					gf_free(es);
					es = NULL;
				} else {
					gf_m2ts_es_del(o_es, ts);
					ts->ess[es->pid] = NULL;
				}
			}
		}

		if (es) {
			ts->ess[es->pid] = es;
			gf_list_add(pmt->program->streams, es);
			if (!(es->flags & GF_M2TS_ES_IS_SECTION) ) gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_SKIP);

			nb_es++;

			if (es->stream_type == GF_M2TS_VIDEO_HEVC) nb_hevc++;
			else if (es->stream_type == GF_M2TS_VIDEO_HEVC_TEMPORAL) nb_hevc_temp++;
			else if (es->stream_type == GF_M2TS_VIDEO_SHVC) nb_shvc++;
			else if (es->stream_type == GF_M2TS_VIDEO_SHVC_TEMPORAL) nb_shvc_temp++;
			else if (es->stream_type == GF_M2TS_VIDEO_MHVC) nb_mhvc++;
			else if (es->stream_type == GF_M2TS_VIDEO_MHVC_TEMPORAL) nb_mhvc_temp++;
		}
	}

	//Table 2-139, implied hierarchy indexes
	if (nb_hevc_temp + nb_shvc + nb_shvc_temp + nb_mhvc+ nb_mhvc_temp) {
		for (i=0; i<gf_list_count(pmt->program->streams); i++) {
			GF_M2TS_PES *es = (GF_M2TS_PES *)gf_list_get(pmt->program->streams, i);
			if ( !(es->flags & GF_M2TS_ES_IS_PES)) continue;
			if (es->depends_on_pid) continue;

			switch (es->stream_type) {
			case GF_M2TS_VIDEO_HEVC_TEMPORAL:
				es->depends_on_pid = 1;
				break;
			case GF_M2TS_VIDEO_SHVC:
				if (!nb_hevc_temp) es->depends_on_pid = 1;
				else es->depends_on_pid = 2;
				break;
			case GF_M2TS_VIDEO_SHVC_TEMPORAL:
				es->depends_on_pid = 3;
				break;
			case GF_M2TS_VIDEO_MHVC:
				if (!nb_hevc_temp) es->depends_on_pid = 1;
				else es->depends_on_pid = 2;
				break;
			case GF_M2TS_VIDEO_MHVC_TEMPORAL:
				if (!nb_hevc_temp) es->depends_on_pid = 2;
				else es->depends_on_pid = 3;
				break;
			}
		}
	}

	if (nb_es) {
		//translate hierarchy descriptors indexes into PIDs - check whether the PMT-index rules are the same for HEVC
		for (i=0; i<gf_list_count(pmt->program->streams); i++) {
			GF_M2TS_PES *an_es = NULL;
			GF_M2TS_PES *es = (GF_M2TS_PES *)gf_list_get(pmt->program->streams, i);
			if ( !(es->flags & GF_M2TS_ES_IS_PES)) continue;
			if (!es->depends_on_pid) continue;

			//fixeme we are not always assured that hierarchy_layer_index matches the stream index...
			//+1 is because our first stream is the PMT
			an_es =  (GF_M2TS_PES *)gf_list_get(pmt->program->streams, es->depends_on_pid);
			if (an_es) {
				es->depends_on_pid = an_es->pid;
			} else {
				GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[M2TS] Wrong dependency index in hierarchy descriptor, assuming non-scalable stream\n"));
				es->depends_on_pid = 0;
			}
		}

		evt_type = (status&GF_M2TS_TABLE_FOUND) ? GF_M2TS_EVT_PMT_FOUND : GF_M2TS_EVT_PMT_UPDATE;
		if (ts->on_event) ts->on_event(ts, evt_type, pmt->program);
	} else {
		/* if we found no new ES it's simply a repeat of the PMT */
		if (ts->on_event) ts->on_event(ts, GF_M2TS_EVT_PMT_REPEAT, pmt->program);
	}
}

static void m2tsdmx_on_event(GF_M2TS_Demuxer *ts, u32 evt_type, void *param)
{
	u32 i, count;
	GF_Filter *filter = (GF_Filter *) ts->user;
	GF_M2TSDmxCtx *ctx = gf_filter_get_udta(filter);

	switch (evt_type) {
	case GF_M2TS_EVT_PAT_UPDATE:
		break;
	case GF_M2TS_EVT_AIT_FOUND:
		break;
	case GF_M2TS_EVT_PAT_FOUND:
		if (ctx->mux_tune_state==DMX_TUNE_INIT) {
			ctx->mux_tune_state = DMX_TUNE_WAIT_PROGS;
			ctx->wait_for_progs = gf_list_count(ts->programs);
		}
		break;
	case GF_M2TS_EVT_DSMCC_FOUND:
		break;
	case GF_M2TS_EVT_PMT_FOUND:
		m2tsdmx_setup_program(ctx, param);
		if (ctx->mux_tune_state == DMX_TUNE_WAIT_PROGS) {
			assert(ctx->wait_for_progs);
			ctx->wait_for_progs--;
			if (!ctx->wait_for_progs) {
				ctx->mux_tune_state = DMX_TUNE_WAIT_SEEK;
			}
		}
		break;
	case GF_M2TS_EVT_PMT_REPEAT:
		break;
	case GF_M2TS_EVT_PMT_UPDATE:
		m2tsdmx_setup_program(ctx, param);
		break;

	case GF_M2TS_EVT_SDT_FOUND:
	case GF_M2TS_EVT_SDT_UPDATE:
//	case GF_M2TS_EVT_SDT_REPEAT:
		m2tsdmx_update_sdt(ts, NULL);
		break;
	case GF_M2TS_EVT_DVB_GENERAL:
		if (ctx->eit_pid) {
			GF_M2TS_SL_PCK *pck = (GF_M2TS_SL_PCK *)param;
			u8 *data;
			GF_FilterPacket *dst_pck = gf_filter_pck_new_alloc(ctx->eit_pid, pck->data_len, &data);
			if (dst_pck) {
				memcpy(data, pck->data, pck->data_len);
				gf_filter_pck_send(dst_pck);
			}
		}
		break;
	case GF_M2TS_EVT_PES_PCK:
		if (ctx->mux_tune_state) break;
		m2tsdmx_send_packet(ctx, param);
		break;
	case GF_M2TS_EVT_SL_PCK: /* DMB specific */
		if (ctx->mux_tune_state) break;
		m2tsdmx_send_sl_packet(ctx, param);
		break;
	case GF_M2TS_EVT_PES_PCR:
		if (ctx->mux_tune_state) break;
	{
		u64 pcr;
		Bool map_time = GF_FALSE;
		GF_M2TS_PES_PCK *pck = ((GF_M2TS_PES_PCK *) param);
		Bool discontinuity = ( ((GF_M2TS_PES_PCK *) param)->flags & GF_M2TS_PES_PCK_DISCONTINUITY) ? 1 : 0;

		assert(pck->stream);
		m2tsdmx_estimate_duration(ctx, (GF_M2TS_ES *) pck->stream);

		if (ctx->map_time_on_prog_id && (ctx->map_time_on_prog_id==((GF_M2TS_PES*)pck->stream)->program->number)) {
			map_time = GF_TRUE;
		}

		//we forward the PCR on each pid
		pcr = ((GF_M2TS_PES_PCK *) param)->PTS;
		pcr /= 300;
		count = gf_list_count(((GF_M2TS_PES*)pck->stream)->program->streams);
		for (i=0; i<count; i++) {
			GF_FilterPacket *dst_pck;
			GF_M2TS_PES *stream = gf_list_get(((GF_M2TS_PES*)pck->stream)->program->streams, i);
			if (!stream->user) continue;

			dst_pck = gf_filter_pck_new_shared(stream->user, NULL, 0, NULL);
			if (!dst_pck) continue;

			gf_filter_pck_set_cts(dst_pck, pcr);
			gf_filter_pck_set_clock_type(dst_pck, discontinuity ? GF_FILTER_CLOCK_PCR_DISC : GF_FILTER_CLOCK_PCR);
			if (((GF_M2TS_PES*)pck->stream)->is_seg_start) {
				((GF_M2TS_PES*)pck->stream)->is_seg_start = GF_FALSE;
				gf_filter_pck_set_property(dst_pck, GF_PROP_PCK_CUE_START, &PROP_BOOL(GF_TRUE));
			}
			gf_filter_pck_send(dst_pck);

			if (map_time && (stream->flags & GF_M2TS_ES_IS_PES) ) {
				((GF_M2TS_PES*)stream)->map_pcr = pcr;
			}
		}

		if (map_time) {
			ctx->map_time_on_prog_id = 0;
		}
	}
		break;

	case GF_M2TS_EVT_TDT:
		if (ctx->mux_tune_state) break;
	{
		GF_M2TS_TDT_TOT *tdt = (GF_M2TS_TDT_TOT *)param;
		u64 utc_ts = gf_net_get_utc_ts(tdt->year, tdt->month, tdt->day, tdt->hour, tdt->minute, tdt->second);
		count = gf_list_count(ts->programs );
		for (i=0; i<count; i++) {
			GF_M2TS_Program *prog = gf_list_get(ts->programs, i);
			u32 j, count2 = gf_list_count(prog->streams);
			for (j=0; j<count2; j++) {
				GF_M2TS_ES * stream = gf_list_get(prog->streams, j);
				if (stream->user && (stream->flags & GF_M2TS_ES_IS_PES)) {
					GF_M2TS_PES*pes = (GF_M2TS_PES*)stream;
					pes->map_utc = utc_ts;
					pes->map_utc_pcr = prog->last_pcr_value/300;
				}
			}
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TS In] Mapping TDT Time %04d-%02d-%02dT%02d:%02d:%02d and PCR time "LLD" on program %d\n",
				                                       tdt->year, tdt->month+1, tdt->day, tdt->hour, tdt->minute, tdt->second, prog->last_pcr_value/300, prog->number));
		}
	}
		break;
	case GF_M2TS_EVT_TOT:
		break;

	case GF_M2TS_EVT_DURATION_ESTIMATED:
	{
		u64 duration = ((GF_M2TS_PES_PCK *) param)->PTS;
		count = gf_list_count(ts->programs);
		for (i=0; i<count; i++) {
			GF_M2TS_Program *prog = gf_list_get(ts->programs, i);
			u32 j, count2;
			count2 = gf_list_count(prog->streams);
			for (j=0; j<count2; j++) {
				GF_M2TS_ES * stream = gf_list_get(prog->streams, j);
				if (stream->user) {
					GF_PropertyValue _pv = {.type=GF_PROP_FRACTION64, .value.lfrac.num = duration, .value.lfrac.den = 1000}; gf_filter_pid_set_property(stream->user, GF_PROP_PID_DURATION, &_pv);
				}
			}
		}
	}
	break;

	case GF_M2TS_EVT_TEMI_LOCATION:
	{
		GF_M2TS_TemiLocationDescriptor *temi_l = (GF_M2TS_TemiLocationDescriptor *)param;
		const char *url;
		u32 len;
		GF_BitStream *bs;
		GF_M2TS_ES *es=NULL;
		GF_TEMIInfo *t;
		if ((temi_l->pid<8192) && (ctx->ts->ess[temi_l->pid])) {
			es = ctx->ts->ess[temi_l->pid];
		}
		if (!es || !es->user) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] TEMI location not assigned to a given PID, not supported\n"));
			break;
		}
		GF_SAFEALLOC(t, GF_TEMIInfo);
		if (!t) break;
		t->timeline_id = temi_l->timeline_id;
		t->is_loc = GF_TRUE;

		bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		if (ctx->temi_url)
			url = ctx->temi_url;
		else
			url = temi_l->external_URL;
		len = url ? (u32) strlen(url) : 0;
		gf_bs_write_data(bs, url, len);
		gf_bs_write_u8(bs, 0);
		gf_bs_write_int(bs, temi_l->is_announce, 1);
		gf_bs_write_int(bs, temi_l->is_splicing, 1);
		gf_bs_write_int(bs, temi_l->reload_external, 1);
		gf_bs_write_int(bs, 0, 5);
		if (temi_l->is_announce) {
			gf_bs_write_u32(bs, temi_l->activation_countdown.den);
			gf_bs_write_u32(bs, temi_l->activation_countdown.num);
		}
		gf_bs_get_content(bs, &t->data, &t->len);
		gf_bs_del(bs);

		if (!es->props) {
			es->props = gf_list_new();
		}
		gf_list_add(es->props, t);
	}
	break;
	case GF_M2TS_EVT_TEMI_TIMECODE:
	{
		GF_M2TS_TemiTimecodeDescriptor *temi_t = (GF_M2TS_TemiTimecodeDescriptor*)param;
		GF_BitStream *bs;
		GF_TEMIInfo *t;
		GF_M2TS_ES *es=NULL;
		if ((temi_t->pid<8192) && (ctx->ts->ess[temi_t->pid])) {
			es = ctx->ts->ess[temi_t->pid];
		}
		if (!es || !es->user) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] TEMI timing not assigned to a given PID, not supported\n"));
			break;
		}
		GF_SAFEALLOC(t, GF_TEMIInfo);
		if (!t) break;
		t->timeline_id = temi_t->timeline_id;

		bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		gf_bs_write_u32(bs, temi_t->media_timescale);
		gf_bs_write_u64(bs, temi_t->media_timestamp);
		gf_bs_write_u64(bs, temi_t->pes_pts);
		gf_bs_write_int(bs, temi_t->force_reload, 1);
		gf_bs_write_int(bs, temi_t->is_paused, 1);
		gf_bs_write_int(bs, temi_t->is_discontinuity, 1);
		gf_bs_write_int(bs, temi_t->ntp ? 1 : 0, 1);
		gf_bs_write_int(bs, 0, 4);
		if (temi_t->ntp)
			gf_bs_write_u64(bs, temi_t->ntp);

		gf_bs_get_content(bs, &t->data, &t->len);
		gf_bs_del(bs);

		if (!es->props) {
			es->props = gf_list_new();
		}
		gf_list_add(es->props, t);
	}
	break;
	case GF_M2TS_EVT_STREAM_REMOVED:
	{
		GF_M2TS_ES *es = (GF_M2TS_ES *)param;
		if (es && es->props) {
			while (gf_list_count(es->props)) {
				GF_TEMIInfo *t = gf_list_pop_back(es->props);
				gf_free(t->data);
				gf_free(t);
			}
			gf_list_del(es->props);
		}
	}
		break;
	}
}

void m2tsdmx_setup_program(GF_M2TSDmxCtx *ctx, GF_M2TS_Program *prog)
{
	u32 i, count;

	count = gf_list_count(prog->streams);
	for (i=0; i<count; i++) {
		GF_M2TS_PES *es = gf_list_get(prog->streams, i);
		if (es->pid==prog->pmt_pid) continue;
		if (! (es->flags & GF_M2TS_ES_IS_PES)) continue;

		if (es->stream_type == GF_M2TS_VIDEO_HEVC_TEMPORAL ) continue;
		if (es->depends_on_pid ) {
			prog->is_scalable = GF_TRUE;
			break;
		}
	}

	for (i=0; i<count; i++) {
		u32 ncount;
		GF_M2TS_ES *es = gf_list_get(prog->streams, i);
		if (es->pid==prog->pmt_pid) continue;

		if (! (es->flags & GF_M2TS_ES_ALREADY_DECLARED)) {
			m2tsdmx_declare_pid(ctx, (GF_M2TS_PES *)es, NULL);
		}
		ncount = gf_list_count(prog->streams);
		while (ncount<count) {
			i--;
			count--;
		}
	}
}

void m2tsdmx_declare_pid(GF_M2TSDmxCtx *ctx, GF_M2TS_PES *stream, GF_ESD *esd)
{
	u32 i, count, codecid=0, stype=0, orig_stype=0;
	GF_FilterPid *opid;
	Bool m4sys_stream = GF_FALSE;
	Bool m4sys_iod_stream = GF_FALSE;
	Bool has_scal_layer = GF_FALSE;
	Bool unframed = GF_FALSE;
	Bool unframed_latm = GF_FALSE;
	char szName[20];
	const char *stname;
	if (stream->user) return;

	if (stream->flags & GF_M2TS_GPAC_CODEC_ID) {
		codecid = stream->stream_type;
		stype = gf_codecid_type(codecid);
		if (stream->gpac_meta_dsi)
			stype = stream->gpac_meta_dsi[4];
		if (!stype) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[M2TSDmx] Unrecognized gpac codec %s - ignoring pid\n", gf_4cc_to_str(codecid) ));
			return;
		}
	} else {
		switch (stream->stream_type) {
		case GF_M2TS_VIDEO_MPEG1:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_MPEG1;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_MPEG2:
		case GF_M2TS_VIDEO_DCII:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_MPEG2_MAIN;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_MPEG4:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_MPEG4_PART2;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_H264:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_AVC;
			unframed = GF_TRUE;
			if (stream->program->is_scalable)
				has_scal_layer = GF_TRUE;
			break;
		case GF_M2TS_HLS_AVC_CRYPT:
			stype = GF_STREAM_ENCRYPTED;
			orig_stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_AVC;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_SVC:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_SVC;
			has_scal_layer = GF_TRUE;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_HEVC:
		case GF_M2TS_VIDEO_HEVC_TEMPORAL:
		case GF_M2TS_VIDEO_HEVC_MCTS:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_HEVC;
			unframed = GF_TRUE;
			if (stream->program->is_scalable)
				has_scal_layer = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_SHVC:
		case GF_M2TS_VIDEO_SHVC_TEMPORAL:
		case GF_M2TS_VIDEO_MHVC:
		case GF_M2TS_VIDEO_MHVC_TEMPORAL:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_LHVC;
			has_scal_layer = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_VVC:
		case GF_M2TS_VIDEO_VVC_TEMPORAL:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_VVC;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_VIDEO_VC1:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_SMPTE_VC1;
			stream->flags |= GF_M2TS_CHECK_VC1;
			break;
		case GF_M2TS_VIDEO_AV1:
			stype = GF_STREAM_VISUAL;
			codecid = GF_CODECID_AV1;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_MPEG1:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_MPEG_AUDIO;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_MPEG2:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_MPEG2_PART3;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_AAC:
		case GF_CODECID_AAC_MPEG2_MP:
		case GF_CODECID_AAC_MPEG2_LCP:
		case GF_CODECID_AAC_MPEG2_SSRP:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_AAC_MPEG4;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_LATM_AAC:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_AAC_MPEG4;
			unframed = GF_TRUE;
			unframed_latm = GF_TRUE;
			break;

		case GF_M2TS_MHAS_MAIN:
		case GF_M2TS_MHAS_AUX:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_MHAS;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_AC3:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_AC3;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_EC3:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_EAC3;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_TRUEHD:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_TRUEHD;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_AUDIO_DTS:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_DTS_X;
			break;
		case GF_M2TS_AUDIO_OPUS:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_OPUS;
			break;
		case GF_M2TS_SYSTEMS_MPEG4_SECTIONS:
			((GF_M2TS_ES*)stream)->flags |= GF_M2TS_ES_SEND_REPEATED_SECTIONS;
			//fallthrough
		case GF_M2TS_SYSTEMS_MPEG4_PES:
			if (!esd) {
				m4sys_iod_stream = GF_TRUE;
				count = stream->program->pmt_iod ? gf_list_count(stream->program->pmt_iod->ESDescriptors) : 0;
				for (i=0; i<count; i++) {
					esd = gf_list_get(stream->program->pmt_iod->ESDescriptors, i);
					if (esd->ESID == stream->mpeg4_es_id) break;
					esd = NULL;
				}
			}
			m4sys_stream = GF_TRUE;
			//cannot setup stream yet
			if (!esd) return;
			break;
		case GF_M2TS_METADATA_PES:
		case GF_M2TS_METADATA_ID3_HLS:
			stype = GF_STREAM_METADATA;
			codecid = GF_CODECID_SIMPLE_TEXT;
			break;
		case 0xA1:
			stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_EAC3;
			break;

		case GF_M2TS_HLS_AAC_CRYPT:
			stype = GF_STREAM_ENCRYPTED;
			orig_stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_AAC_MPEG4;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_HLS_AC3_CRYPT:
			stype = GF_STREAM_ENCRYPTED;
			orig_stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_AC3;
			unframed = GF_TRUE;
			break;
		case GF_M2TS_HLS_EC3_CRYPT:
			stype = GF_STREAM_ENCRYPTED;
			orig_stype = GF_STREAM_AUDIO;
			codecid = GF_CODECID_EAC3;
			break;
		case GF_M2TS_DVB_SUBTITLE:
			stype = GF_STREAM_TEXT;
			codecid = GF_CODECID_DVB_SUBS;
			stream->flags |= GF_M2TS_ES_FULL_AU;
			break;
		case GF_M2TS_DVB_TELETEXT:
			if (!ctx->dvbtxt) {
				GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[M2TSDmx] DVB teletext pid skipped, use --dvbtxt to enable\n", stream->stream_type));
				return;
			}
			stype = GF_STREAM_TEXT;
			codecid = GF_CODECID_DVB_TELETEXT;
			stream->flags |= GF_M2TS_ES_FULL_AU;
			break;
		default:
			GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[M2TSDmx] Stream type 0x%02X not supported - ignoring pid\n", stream->stream_type));
			return;
		}
	}

	opid = NULL;
	for (i=0; i<gf_filter_get_opid_count(ctx->filter); i++) {
		opid = gf_filter_get_opid(ctx->filter, i);
		const GF_PropertyValue *p = gf_filter_pid_get_property(opid, GF_PROP_PID_ID);
		if (p && (p->value.uint == stream->pid))
			break;
		opid = NULL;
	}

	if (!opid)
		opid = gf_filter_pid_new(ctx->filter);

	stream->user = opid;
	stream->flags |= GF_M2TS_ES_ALREADY_DECLARED;

	u32 d_type = orig_stype ? orig_stype : stype;
	switch (d_type) {
	case GF_STREAM_AUDIO:
	case GF_STREAM_VISUAL:
		stream->flags |= GF_M2TS_CHECK_DISC;
		break;
	default:
		stream->flags &= ~GF_M2TS_CHECK_DISC;
		break;
	}

	stname = gf_stream_type_name(stype);
	sprintf(szName, "P%d%c%d", stream->program->number, stname[0], 1+gf_list_find(stream->program->streams, stream));
	gf_filter_pid_set_name(opid, szName);

	gf_filter_pid_set_property(opid, GF_PROP_PID_ID, &PROP_UINT(stream->pid) );
	gf_filter_pid_set_property(opid, GF_PROP_PID_ESID, stream->mpeg4_es_id ? &PROP_UINT(stream->mpeg4_es_id) : NULL);

	if (m4sys_stream) {
		if (stream->slcfg) gf_free(stream->slcfg);

		stream->slcfg = esd->slConfig;
		esd->slConfig = NULL;

		gf_filter_pid_set_property(opid, GF_PROP_PID_STREAM_TYPE, &PROP_UINT(esd->decoderConfig ? esd->decoderConfig->streamType : GF_STREAM_SCENE) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_CODECID, &PROP_UINT(esd->decoderConfig ? esd->decoderConfig->objectTypeIndication : GF_CODECID_BIFS) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_CLOCK_ID, &PROP_UINT(esd->OCRESID ? esd->OCRESID : esd->ESID) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_DEPENDENCY_ID, &PROP_UINT(esd->dependsOnESID) );
		if (esd->decoderConfig && esd->decoderConfig->decoderSpecificInfo  && esd->decoderConfig->decoderSpecificInfo->dataLength)
			gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG, &PROP_DATA(esd->decoderConfig->decoderSpecificInfo->data, esd->decoderConfig->decoderSpecificInfo->dataLength) );

		gf_filter_pid_set_property(opid, GF_PROP_PID_IN_IOD, &PROP_BOOL(m4sys_iod_stream) );

		gf_filter_pid_set_property(opid, GF_PROP_PID_TIMESCALE, &PROP_UINT(((GF_M2TS_ES*)stream)->slcfg->timestampResolution) );
		if (esd->decoderConfig && (esd->decoderConfig->streamType==GF_STREAM_OD))
			stream->flags |= GF_M2TS_ES_IS_MPEG4_OD;
	} else {
		gf_filter_pid_set_property(opid, GF_PROP_PID_STREAM_TYPE, &PROP_UINT(stype) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_CODECID, &PROP_UINT(codecid) );

		gf_filter_pid_set_property(opid, GF_PROP_PID_UNFRAMED, unframed ? &PROP_BOOL(GF_TRUE) : NULL);
		gf_filter_pid_set_property(opid, GF_PROP_PID_UNFRAMED_LATM, unframed_latm ? &PROP_BOOL(GF_TRUE) : NULL );

		if (orig_stype) {
			gf_filter_pid_set_property(opid, GF_PROP_PID_ORIG_STREAM_TYPE, &PROP_UINT(orig_stype) );
			gf_filter_pid_set_property(opid, GF_PROP_PID_PROTECTION_SCHEME_TYPE, &PROP_UINT(GF_HLS_SAMPLE_AES_SCHEME) );
		} else {
			gf_filter_pid_set_property(opid, GF_PROP_PID_ORIG_STREAM_TYPE, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_PROTECTION_SCHEME_TYPE, NULL);
		}

		gf_filter_pid_set_property(opid, GF_PROP_PID_TIMESCALE, &PROP_UINT(90000) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_CLOCK_ID, &PROP_UINT(stream->program->pcr_pid) );

		if ((stream->flags&GF_M2TS_ES_IS_PES) && stream->gpac_meta_dsi) {
			char *cname;
			GF_BitStream *bs = gf_bs_new(stream->gpac_meta_dsi, stream->gpac_meta_dsi_size, GF_BITSTREAM_READ);
			u32 val = gf_bs_read_u32(bs); //codec ID (meta codec identifier)
			gf_filter_pid_set_property(opid, GF_PROP_PID_CODECID, &PROP_UINT(val) );
			gf_bs_read_u8(bs); //stream type
			gf_bs_read_u8(bs); //version
			val = gf_bs_read_u32(bs); //codecID for meta codec, e.g. an AVCodecID or other
			gf_filter_pid_set_property(opid, GF_PROP_PID_META_DEMUX_CODEC_ID, &PROP_UINT(val) );
			cname = gf_bs_read_utf8(bs); //meta codec name
			gf_filter_pid_set_property(opid, GF_PROP_PID_META_DEMUX_CODEC_NAME, cname ? &PROP_STRING_NO_COPY(cname) : NULL );
			val = gf_bs_read_u32(bs); //meta opaque
			gf_filter_pid_set_property(opid, GF_PROP_PID_META_DEMUX_OPAQUE, &PROP_UINT(val) );
			u32 dsi_len = gf_bs_read_u32(bs);
			if (dsi_len) {
				u32 pos = gf_bs_get_position(bs);
				gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG, &PROP_DATA(stream->gpac_meta_dsi+pos, dsi_len) );
				gf_bs_skip_bytes(bs, dsi_len);
			} else {
				gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG, NULL);
			}
			if (stype==GF_STREAM_VISUAL) {
				val = gf_bs_read_u32(bs);
				gf_filter_pid_set_property(opid, GF_PROP_PID_WIDTH, &PROP_UINT(val) );
				val = gf_bs_read_u32(bs);
				gf_filter_pid_set_property(opid, GF_PROP_PID_HEIGHT, &PROP_UINT(val) );
			} else if (stype==GF_STREAM_AUDIO) {
				val = gf_bs_read_u32(bs);
				gf_filter_pid_set_property(opid, GF_PROP_PID_SAMPLE_RATE, &PROP_UINT(val) );
				val = gf_bs_read_u32(bs);
				gf_filter_pid_set_property(opid, GF_PROP_PID_NUM_CHANNELS, &PROP_UINT(val) );
			}
			gf_bs_del(bs);
		}
	}
	gf_filter_pid_set_property(opid, GF_PROP_PID_SCALABLE, has_scal_layer ? &PROP_BOOL(GF_TRUE) : NULL);

	gf_filter_pid_set_property(opid, GF_PROP_PID_SERVICE_ID, &PROP_UINT(stream->program->number) );

	if ((stream->flags&GF_M2TS_ES_IS_PES) && stream->lang) {
		char szLang[4];
		szLang[0] = (stream->lang>>16) & 0xFF;
		szLang[1] = (stream->lang>>8) & 0xFF;
		szLang[2] = stream->lang & 0xFF;
		szLang[3] = 0;
		if (szLang[2]==' ') szLang[2] = 0;
		gf_filter_pid_set_property(opid, GF_PROP_PID_LANGUAGE, &PROP_STRING(szLang) );
	}
	if (codecid == GF_CODECID_DVB_SUBS) {
		char szLang[4];
		memcpy(szLang, stream->sub.language, 3);
		szLang[3]=0;
		gf_filter_pid_set_property(opid, GF_PROP_PID_LANGUAGE, &PROP_STRING(szLang) );

		u8 dsi[5];
		dsi[0] = stream->sub.composition_page_id>>8;
		dsi[1] = stream->sub.composition_page_id & 0xFF;
		dsi[2] = stream->sub.ancillary_page_id>>8;
		dsi[3] = stream->sub.ancillary_page_id & 0xFF;
		dsi[4] = stream->sub.type;
		gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG, &PROP_DATA(dsi, 5));
	}

	if (ctx->duration.num>1) {
		gf_filter_pid_set_property(opid, GF_PROP_PID_DURATION, &PROP_FRAC64(ctx->duration) );
		gf_filter_pid_set_property(opid, GF_PROP_PID_PLAYBACK_MODE, &PROP_UINT(GF_PLAYBACK_MODE_FASTFORWARD ) );
	}
	/*indicate our coding dependencies if any*/
	if (!m4sys_stream) {
		if ((stream->flags&GF_M2TS_ES_IS_PES) && stream->depends_on_pid) {
			gf_filter_pid_set_property(opid, GF_PROP_PID_DEPENDENCY_ID, &PROP_UINT(stream->depends_on_pid) );
			if ((stream->stream_type == GF_M2TS_VIDEO_HEVC_TEMPORAL) || (stream->stream_type == GF_M2TS_VIDEO_HEVC_MCTS)) {
				gf_filter_pid_set_property(opid, GF_PROP_PID_SUBLAYER, &PROP_BOOL(GF_TRUE) );
			}
		} else {
			gf_filter_pid_set_property(opid, GF_PROP_PID_DEPENDENCY_ID, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_SUBLAYER, NULL);
		}
	}

	if ((stream->flags & GF_M2TS_ES_IS_PES) && (stream->dv_info[0])) {
		gf_filter_pid_set_property(opid, GF_PROP_PID_DOLBY_VISION, &PROP_DATA(stream->dv_info, 24) );
		u32 dvtype=0;
		if (stream->dv_info[24]) {
			if (stream->stream_type == GF_M2TS_VIDEO_H264)
				dvtype = GF_4CC('d','a','v','1');
			else
				dvtype = GF_4CC('d','v','h','1');
		}
		gf_filter_pid_set_property(opid, GF_PROP_PID_ISOM_SUBTYPE, dvtype ? &PROP_4CC(dvtype) : NULL);
	} else {
		gf_filter_pid_set_property(opid, GF_PROP_PID_DOLBY_VISION, NULL);
	}

	m2tsdmx_update_sdt(ctx->ts, opid);

	gf_m2ts_set_pes_framing((GF_M2TS_PES *)stream, GF_M2TS_PES_FRAMING_DEFAULT);
}

static GF_Err m2tsdmx_initialize(GF_Filter *filter)
{
	GF_M2TSDmxCtx *ctx = gf_filter_get_udta(filter);

	ctx->ts = gf_m2ts_demux_new();
	if (!ctx->ts) return GF_OUT_OF_MEM;

	ctx->ts->on_event = (void (*)(void *, u32, void *))m2tsdmx_on_event;
	ctx->ts->user = filter;

	ctx->filter = filter;
	if (ctx->dsmcc) {
		gf_m2ts_demux_dmscc_init(ctx->ts);
	}

	return GF_OK;
}