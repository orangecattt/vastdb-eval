#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/* from: setup.h:87 */
typedef short s16;
/* from: setup.h:83 */
typedef int s32;
/* from: setup.h:79 */
typedef long long s64;
/* from: setup.h:89 */
typedef unsigned char u8;
/* from: setup.h:81 */
typedef unsigned int u32;
/* from: setup.h:85 */
typedef unsigned short u16;
/* from: setup.h:77 */
typedef unsigned long long u64;

/* from: mpegts.h:37 */
typedef enum {
	GF_FALSE = 0,
	GF_TRUE,
} Bool;

/* from: dmx_m2ts.c:36 */
typedef double Double;

/* from: setup.h:450 */
typedef struct {
	s64 num;
	u64 den;
} GF_Fraction64;

/* from: setup.h:826 */
#define gf_fatal_assert(_cond) if (! (_cond)) { fprintf(stderr, "Fatal error " #_cond " file %s line %d, exiting\n", (strstr(__FILE__, "gpac") ? strstr(__FILE__, "gpac") + 5 : __FILE__), __LINE__ ); exit(10); }

/* from: setup.h:548 */
#define LLD "%" LLD_SUF
/* from: setup.h:464 */
#define LLD_SUF "lld"
/* from: setup.h:550 */
#define LLU "%" LLU_SUF
/* from: setup.h:466 */
#define LLU_SUF "llu"

/* from: setup.h:567 */
#define GF_EXPORT

/* from: tools.h:235 */
#define GF_SAFEALLOC(__ptr, __struct) {\
        (__ptr) = (__struct *) gf_malloc(sizeof(__struct));\
        if (__ptr) {\
                memset((void *) (__ptr), 0, sizeof(__struct));\
        }\
        }

/* from: filters.h:1591 */
#define PROP_BOOL(_val) (GF_PropertyValue){.type=GF_PROP_BOOL, .value.boolean = _val}
/* from: filters.h:1601 */
#define PROP_FRAC64_INT(_num, _den) (GF_PropertyValue){.type=GF_PROP_FRACTION64, .value.lfrac.num = _num, .value.lfrac.den = _den}
/* from: filters.h:1743 */
#define GF_FEVT_INIT(_a, _type, _on_pid)	{ memset(&_a, 0, sizeof(GF_FilterEvent)); _a.base.type = _type; _a.base.on_pid = _on_pid; }

/* from: list.h:37 */
typedef struct __gf_list GF_List;
/* from: filters.h:87 */
typedef struct gf_filter_packet GF_FilterPacket;
/* from: filters.h:88 */
typedef struct gf_filter_pid GF_FilterPid;
/* from: filters.h:89 */
typedef struct gf_filter GF_Filter;
/* from: filters.h:90 */
typedef struct gf_filter_session GF_FilterSession;
/* from: filters.h:152 */
typedef struct __gf_filter_register GF_FilterRegister;
/* from: filters.h:2350 */
#define GF_FS_REG_DYNAMIC_PIDS (1<<7)
/* from: filters.h:2351 */
#define GF_FS_REG_CONFIGURE_MAIN_THREAD (1<<2)

/* from: mpegts.h:343 */
typedef struct tag_m2ts_demux GF_M2TS_Demuxer;
/* from: mpegts.h:345 */
typedef struct tag_m2ts_es GF_M2TS_ES;
/* from: mpegts.h:347 */
typedef struct tag_m2ts_section_es GF_M2TS_SECTION_ES;

/* from: dmx_m2ts.c:43 */
typedef enum
{
	M2TS_TEMI_INFO,
	M2TS_ID3,
	M2TS_SCTE35
} GF_M2TS_PropType;

/* from: dmx_m2ts.c:50 */
#define GF_M2TS_PROP       \
	GF_M2TS_PropType type; \
	u32 len;               \
	u8 *data;              \

/* from: dmx_m2ts.c:55 */
typedef struct {
	GF_M2TS_PROP
} GF_M2TS_Prop;

/* from: dmx_m2ts.c:59 */
typedef struct {
	GF_M2TS_PROP
	u32 timeline_id;
	Bool is_loc;
} GF_M2TS_Prop_TEMIInfo;

/* from: dmx_m2ts.c:65 */
enum
{
	DMX_TUNE_DONE=0,
	DMX_TUNE_INIT,
	DMX_TUNE_WAIT_PROGS,
	DMX_TUNE_WAIT_SEEK,
};

/* from: dmx_m2ts.c:73 */
typedef struct
{
	const char *temi_url;
	Bool dsmcc, seeksrc, sigfrag, dvbtxt;
	Double index;

	GF_Filter *filter;
	GF_FilterPid *ipid;

	GF_M2TS_Demuxer *ts;

	GF_FilterPid *eit_pid;

	Bool is_file;
	u64 file_size;
	Bool in_seek;
	Bool initial_play_done;
	u32 nb_playing, nb_stop_pending;

	GF_Fraction64 duration;
	u64 first_pcr_found;
	u16 pcr_pid;
	u64 nb_pck_at_pcr;

	u32 map_time_on_prog_id;
	Double media_start_range;

	u32 mux_tune_state;
	u32 wait_for_progs;

	Bool is_dash;
	u32 nb_stopped_at_init;
} GF_M2TSDmxCtx;

/* from: filters.h:1579 */
typedef enum {
	GF_PROP_BOOL = 0,
	GF_PROP_UINT,
	GF_PROP_SINT,
	GF_PROP_FLOAT,
	GF_PROP_FRACTION,
	GF_PROP_STRING,
	GF_PROP_DATA,
	GF_PROP_4CC,
	GF_PROP_LSINT,
	GF_PROP_LUINT,
	GF_PROP_FRACTION64,
	GF_PROP_DOUBLE,
	GF_PROP_STRING_NO_COPY,
	GF_PROP_NAME,
	GF_PROP_DATA_NO_COPY,
	GF_PROP_CONST_DATA,
	GF_PROP_VEC2,
	GF_PROP_VEC2I,
	GF_PROP_VEC3I,
	GF_PROP_VEC4I,
	GF_PROP_POINTER,
	GF_PROP_STRUCT,
	GF_PROP_DATE,
	GF_PROP_BITMASK,
	GF_PROP_UINT_RANGE,
	GF_PROP_ENUM,
	GF_PROP_FILTER_CAPS,
} GF_PropertyType;

/* from: filters.h:1544 */
typedef struct {
	union {
		u8 boolean;
		u32 uint;
		s32 sint;
		u64 longuint;
		s64 longsint;
		s64 number;
		u32 fnumber;
		char *string;
		struct {
			u8 *ptr;
			u32 size;
		} data;
		struct {
			s32 num;
			u32 den;
		} frac;
		struct {
			s64 num;
			u64 den;
		} lfrac;
		struct {
			s32 x, y;
		} vec2i;
		struct {
			s32 x, y, z;
		} vec3i;
		struct {
			s32 x, y, z, w;
		} vec4i;
		void *ptr;
	} value;
	GF_PropertyType type;
} GF_PropertyValue;

/* from: tools.h:115 */
typedef enum
{
	GF_EOS = 1,
	GF_OK = 0,
	GF_BAD_PARAM = -1,
	GF_OUT_OF_MEM = -2,
	GF_IO_ERR = -3,
	GF_NOT_SUPPORTED = -4,
	GF_CORRUPTED_DATA = -5,
} GF_Err;

/* from: filters.h:2196 */
typedef struct
{
	u32 code;
	GF_PropertyValue val;
	const char *name;
	u32 flags;
	u8 priority;
} GF_FilterCapability;

/* from: filters.h:2388 */
struct __gf_filter_register
{
	const char *name;
	u32 private_size;
	u32 max_extra_pids;
	u32 flags;
	const GF_FilterCapability *caps;
	u32 nb_caps;
	const void *args;
	GF_Err (*process)(GF_Filter *filter);
	const void *configure_pid;
	const void *process_event;
	const void *probe_data;
	const void *initialize;
	const void *finalize;
	const char *description;
	const char *help;
};

/* from: filters.h:1682 */
typedef enum {
	GF_FEVT_NONE = 0,
	GF_FEVT_PLAY,
	GF_FEVT_STOP,
	GF_FEVT_PAUSE,
	GF_FEVT_RESUME,
	GF_FEVT_SET_SPEED,
	GF_FEVT_SOURCE_SEEK,
	GF_FEVT_QUALITY_SWITCH,
	GF_FEVT_FILE_DELETE,
	GF_FEVT_SOURCE_SWITCH,
	GF_FEVT_USER,
} GF_FilterEventType;

/* from: filters.h:1697 */
typedef struct {
	GF_FilterEventType type;
	GF_FilterPid *on_pid;
} GF_FilterEventBase;

/* from: filters.h:1702 */
typedef struct {
	GF_FilterEventBase base;
	union {
		struct {
			Double speed;
			Bool is_instant;
		} speed;
		struct {
			s64 seek_to;
			Bool is_in_frame;
			Bool flush_buffers;
		} seek;
		struct {
			const char *new_url;
			Bool switch_done;
		} source_switch;
		struct {
			u32 quality;
		} quality;
		void *udta;
	} content;
} GF_FilterEvent;

/* from: mpegts.h:660 */
typedef struct
{
	GF_M2TS_Demuxer *ts;
	GF_List *streams;
	u32 pmt_pid;
	u32 pcr_pid;
	u32 number;
	void *pmt_iod;
	GF_List *additional_ods;
	u64 first_dts;
	u64 last_pcr_value;
	u32 last_pcr_value_pck_number;
	u64 before_last_pcr_value;
	u32 before_last_pcr_value_pck_number;
	Bool tdt_found;
	u32 pid_playing;
	Bool is_scalable;
	void *metadata_pointer_descriptor;
	s16 pcr_cc;
	void *user;
} GF_M2TS_Program;

/* from: mpegts.h:765 */
struct tag_m2ts_es
{
	GF_M2TS_Program *program;
	u32 flags;
	u32 pid;
	u32 stream_type;
	u32 mpeg4_es_id;
	void *slcfg;
	s16 component_tag;
	void *user;
	GF_List *props;
	u64 first_dts;
	Bool is_seg_start;
	u32 service_id;
};

/* from: mpegts.h:835 */
typedef struct tag_m2ts_pes
{
	GF_M2TS_Program *program;
	u32 flags;
	u32 pid;
	u32 stream_type;
	u32 mpeg4_es_id;
	void *slcfg;
	s16 component_tag;
	void *user;
	GF_List *props;
	u64 first_dts;
	Bool is_seg_start;
	u32 service_id;

	s16 cc;
	u32 lang;
	u32 depends_on_pid;

	u8 *pck_data;
	u32 pck_alloc_len;
	u32 pck_data_len;
	u32 pes_len;
	Bool rap;
	u64 PTS;
	u64 DTS;
	u8 *prev_data;
	u32 prev_data_len;
	u32 pes_start_packet_number;
	u32 pes_end_packet_number;
	u64 last_pcr_value;
	u32 last_pcr_value_pck_number;
	u64 before_last_pcr_value;
	u32 before_last_pcr_value_pck_number;
	u32 last_pat_packet_number, before_last_pat_pn, before_last_pes_start_pn;

	void (*reframe)(struct tag_m2ts_demux *ts, struct tag_m2ts_pes *pes, Bool same_pts, u8 *data, u32 data_len, void *hdr);

	void *sub;
	void *metadata_descriptor;

	u8 *temi_tc_desc;
	u32 temi_tc_desc_len;
	u32 temi_tc_desc_alloc_size;
	void *temi_tc;
	Bool temi_pending;

	Bool is_resume;

	u8 dv_info[25];

	u64 map_utc, map_utc_pcr, map_pcr;
	u8 *gpac_meta_dsi;
	u32 gpac_meta_dsi_size;
} GF_M2TS_PES;

/* from: mpegts.h:1050 */
typedef struct
{
	u8 *data;
	u32 data_len;
	u32 flags;
	u64 PTS, DTS;
	GF_M2TS_PES *stream;
} GF_M2TS_PES_PCK;

/* from: mpegts.h:1060 */
typedef struct
{
	u8 *data;
	u32 data_len;
	u8 version_number;
	GF_M2TS_ES *stream;
} GF_M2TS_SL_PCK;

/* from: mpegts.h:951 */
typedef struct
{
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
} GF_M2TS_TDT_TOT;

/* from: mpegts.h:632 */
typedef struct
{
	u32 pid;
	u32 timeline_id;
	const char *external_URL;
	Bool is_announce, is_splicing;
	Bool reload_external;
	struct {
		s32 num;
		u32 den;
	} activation_countdown;
} GF_M2TS_TemiLocationDescriptor;

/* from: mpegts.h:645 */
typedef struct
{
	u32 pid;
	u32 timeline_id;
	u32 media_timescale;
	u64 media_timestamp;
	u64 pes_pts;
	Bool force_reload;
	Bool is_paused;
	Bool is_discontinuity;
	u64 ntp;
} GF_M2TS_TemiTimecodeDescriptor;

/* from: mpegts.h:705 */
enum
{
	GF_M2TS_ES_IS_PES = 1,
	GF_M2TS_ES_IS_SECTION = 1<<1,
	GF_M2TS_ES_IS_FMC = 1<<2,
	GF_M2TS_ES_IS_SL = 1<<3,
	GF_M2TS_ES_IS_MPEG4_OD = 1<<4,
	GF_M2TS_ES_IS_MPE = 1<<5,
	GF_M2TS_INHERIT_PCR = 1<<6,
	GF_M2TS_FAKE_PCR = 1<<7,
	GF_M2TS_GPAC_CODEC_ID = 1<<8,
	GF_M2TS_ES_IS_PMT = 1<<9,
	GF_M2TS_ES_IS_PCR_REUSE = 1<<10,
};

/* from: mpegts.h:408 */
enum
{
	GF_M2TS_PES_PCK_RAP = 1,
	GF_M2TS_PES_PCK_AU_START = 1<<1,
	GF_M2TS_PES_PCK_I_FRAME = 1<<2,
	GF_M2TS_PES_PCK_P_FRAME = 1<<3,
	GF_M2TS_PES_PCK_B_FRAME = 1<<4,
	GF_M2TS_PES_PCK_DISCONTINUITY = 1<<5
};

/* from: mpegts.h:435 */
enum
{
	GF_M2TS_EVT_PAT_FOUND = 0,
	GF_M2TS_EVT_PAT_UPDATE,
	GF_M2TS_EVT_PAT_REPEAT,
	GF_M2TS_EVT_PMT_FOUND,
	GF_M2TS_EVT_PMT_REPEAT,
	GF_M2TS_EVT_PMT_UPDATE,
	GF_M2TS_EVT_SDT_FOUND,
	GF_M2TS_EVT_SDT_REPEAT,
	GF_M2TS_EVT_SDT_UPDATE,
	GF_M2TS_EVT_INT_FOUND,
	GF_M2TS_EVT_INT_REPEAT,
	GF_M2TS_EVT_INT_UPDATE,
	GF_M2TS_EVT_PES_PCK,
	GF_M2TS_EVT_PES_PCR,
	GF_M2TS_EVT_PES_TIMING,
	GF_M2TS_EVT_SL_PCK,
	GF_M2TS_EVT_IP_DATAGRAM,
	GF_M2TS_EVT_DURATION_ESTIMATED,
	GF_M2TS_EVT_PCK,
	GF_M2TS_EVT_AAC_CFG,
	GF_M2TS_EVT_TDT,
	GF_M2TS_EVT_TOT,
	GF_M2TS_EVT_DVB_GENERAL,
	GF_M2TS_EVT_DVB_MPE,
	GF_M2TS_EVT_CAT_FOUND,
	GF_M2TS_EVT_CAT_REPEAT,
	GF_M2TS_EVT_CAT_UPDATE,
	GF_M2TS_EVT_AIT_FOUND,
	GF_M2TS_EVT_DSMCC_FOUND,
	GF_M2TS_EVT_TEMI_LOCATION,
	GF_M2TS_EVT_TEMI_TIMECODE,
	GF_M2TS_EVT_SCTE35_SPLICE_INFO,
	GF_M2TS_EVT_ID3,
	GF_M2TS_EVT_STREAM_REMOVED
};

/* from: mpegts.h:515 */
enum
{
	GF_M2TS_TABLE_START		= 1,
	GF_M2TS_TABLE_END		= 1<<1,
	GF_M2TS_TABLE_FOUND		= 1<<2,
	GF_M2TS_TABLE_UPDATE	= 1<<3,
	GF_M2TS_TABLE_REPEAT	= 1<<4,
};

/* from: mpegts.h:579 */
typedef struct GF_M2TS_SectionFilter
{
	s16 cc;
	u8 *section;
	u16 length;
	u16 received;
	void *table;
	Bool process_individual;
	Bool direct_dispatch;
	u32 service_id;
	void (*process_section)(GF_M2TS_Demuxer *demux, GF_M2TS_SECTION_ES *es, GF_List *sections, u8 table_id, u16 ex_table_id, u8 version_number, u8 last_section_number, u32 status);
	Bool demux_restarted;
} GF_M2TS_SectionFilter;

/* from: mpegts.h:750 */
#define ABSTRACT_ES \
	GF_M2TS_Program *program; \
	u32 flags; \
	u32 pid; \
	u32 stream_type; \
	u32 mpeg4_es_id; \
	void *slcfg; \
	s16 component_tag; \
	void *user; \
	GF_List *props; \
	u64 first_dts; \
	Bool is_seg_start; \
	u32 service_id;

/* from: mpegts.h:789 */
struct tag_m2ts_section_es
{
	ABSTRACT_ES
	GF_M2TS_SectionFilter *sec;
};

/* from: mpegts.h:550 */
typedef struct __m2ts_demux_table
{
	struct __m2ts_demux_table *next;
	u8 is_init;
	u8 is_repeat;
	u8 table_id;
	u16 ex_table_id;
	u8 version_number;
	u8 last_version_number;
	u8 current_next_indicator;
	u8 section_number;
	u8 last_section_number;
	GF_List *sections;
	u32 table_size;
} GF_M2TS_Table;

/* from: mpegts.h:543 */
typedef struct __m2ts_demux_section
{
	u8 *data;
	u32 data_size;
} GF_M2TS_Section;

/* from: mpegts.h:1089 */
struct tag_m2ts_demux
{
	GF_M2TS_ES *ess[8192];
	GF_List *programs;
	u32 nb_prog_pmt_received;
	Bool all_prog_pmt_received;
	Bool all_prog_processed;
	GF_List *SDTs;
	GF_M2TS_TDT_TOT *TDT_time;

	void (*on_event)(struct tag_m2ts_demux *ts, u32 evt_type, void *par);
	void *user;

	u8 *buffer;
	u32 buffer_size;
	u32 alloc_size;
	GF_M2TS_SectionFilter *pat;
	GF_M2TS_SectionFilter *cat;
	GF_M2TS_SectionFilter *nit;
	GF_M2TS_SectionFilter *sdt;
	GF_M2TS_SectionFilter *eit;
	GF_M2TS_SectionFilter *tdt_tot;
	Bool has_4on2;
	void *pes_out;

	Bool seek_mode;
	Bool prefix_present;
	Bool direct_mpe;
	Bool dvb_h_demux;
	Bool notify_pes_timing;

	void (*on_mpe_event)(struct tag_m2ts_demux *ts, u32 evt_type, void *par);
	void *ip_platform;
	u32 pck_number;

	u32 last_pat_start_num;
	void *dnload;
	const char *dvb_channels_conf_path;

	GF_List* ChannelAppList;

	Bool process_dmscc;
	char* dsmcc_root_dir;
	GF_List* dsmcc_controler;
	Bool table_reset;

	Bool split_mode;
};

/* from: mpegts.h:939 */
typedef struct
{
	u16 original_network_id;
	u16 transport_stream_id;
	u32 service_id;
	u32 EIT_schedule;
	u32 EIT_present_following;
	u32 running_status;
	u32 free_CA_mode;
	u8 service_type;
	char *provider, *service;
} GF_M2TS_SDT;

/* from: filters.h:1395 */
typedef enum
{
	GF_STREAM_NONE = 0,
	GF_STREAM_AUDIO,
	GF_STREAM_VISUAL,
	GF_STREAM_SCENE,
	GF_STREAM_SYSTEM,
	GF_STREAM_TEXT,
	GF_STREAM_OD,
	GF_STREAM_FILE,
	GF_STREAM_UNKNOWN,
} GF_StreamType;

/* from: filters.h:122 */
typedef enum
{
	GF_PROP_PID_STREAM_TYPE = 0,
	GF_PROP_PID_CODECID,
	GF_PROP_PID_DECODER_CONFIG,
	GF_PROP_PID_DURATION,
	GF_PROP_PID_TIMESCALE,
	GF_PROP_PID_FRAME_RATE,
	GF_PROP_PID_BITRATE,
	GF_PROP_PID_LANGUAGE,
	GF_PROP_PID_NAME,
	GF_PROP_PID_SERVICE_NAME,
	GF_PROP_PID_SERVICE_PROVIDER,
	GF_PROP_PID_SERVICE_TYPE,
	GF_PROP_PID_PCR_PID,
	GF_PROP_PID_PMT_PID,
	GF_PROP_PID_PROGRAM_NUMBER,
	GF_PROP_PID_SCTE35_PID,
	GF_PROP_PID_HAS_TEMI,
	GF_PROP_PID_DOWN_SIZE,
	GF_PROP_PID_URL,
} GF_PIDProperty;

/* from: filters.h:238 */
typedef enum
{
	GF_PROP_PCK_CUE_START,
	GF_PROP_PCK_UTC_TIME,
	GF_PROP_PCK_MEDIA_TIME,
	GF_PROP_PCK_CTS,
	GF_PROP_PCK_DTS,
	GF_PROP_PCK_SAP,
	GF_PROP_PCK_FRAMING,
	GF_PROP_PCK_CLOCK_TYPE,
	GF_PROP_PCK_FRAG_RANGE,
} GF_PCKProperty;

/* from: filters.h:253 */
typedef enum
{
	GF_FILTER_CLOCK_PCR = 0,
	GF_FILTER_CLOCK_PCR_DISC,
	GF_FILTER_CLOCK_LOCAL,
	GF_FILTER_CLOCK_PCR_ONLY,
} GF_FilterClockType;

/* from: filters.h:260 */
typedef enum
{
	GF_FILTER_SAP_NONE = 0,
	GF_FILTER_SAP_1,
	GF_FILTER_SAP_2,
	GF_FILTER_SAP_3,
	GF_FILTER_SAP_4,
	GF_FILTER_SAP_UNKNOWN,
} GF_FilterSAPType;

/* from: list.h:76 */
u32 gf_list_count(const GF_List *ptr);
/* from: list.h:83 */
void *gf_list_get(const GF_List *ptr, u32 item);
/* from: list.h:71 */
GF_List *gf_list_new();
/* from: list.h:72 */
void gf_list_del(GF_List *ptr);
/* from: list.h:77 */
void gf_list_add(GF_List *ptr, void *item);
/* from: list.h:79 */
void *gf_list_pop_front(GF_List *ptr);
/* from: list.h:80 */
void *gf_list_pop_back(GF_List *ptr);

/* from: filters.h:1254 */
void *gf_filter_get_udta(GF_Filter *filter);
/* from: filters.h:1261 */
GF_FilterPid *gf_filter_get_opid(GF_Filter *filter, u32 index);
/* from: filters.h:1268 */
u32 gf_filter_get_opid_count(GF_Filter *filter);
/* from: filters.h:1356 */
const GF_PropertyValue *gf_filter_pid_get_property(GF_FilterPid *pid, GF_PIDProperty prop);
/* from: filters.h:1405 */
void gf_filter_pid_set_property(GF_FilterPid *pid, GF_PIDProperty prop, const GF_PropertyValue *val);
/* from: filters.h:1412 */
void gf_filter_pid_set_discard(GF_FilterPid *pid, Bool discard);
/* from: filters.h:1419 */
Bool gf_filter_pid_is_playing(GF_FilterPid *pid);
/* from: filters.h:1426 */
Bool gf_filter_pid_would_block(GF_FilterPid *pid);
/* from: filters.h:1433 */
Bool gf_filter_pid_is_eos(GF_FilterPid *pid);
/* from: filters.h:1440 */
void gf_filter_pid_set_eos(GF_FilterPid *pid);
/* from: filters.h:1447 */
GF_FilterPacket *gf_filter_pid_get_packet(GF_FilterPid *pid);
/* from: filters.h:1454 */
void gf_filter_pid_drop_packet(GF_FilterPid *pid);
/* from: filters.h:1461 */
void gf_filter_pid_send_event(GF_FilterPid *pid, GF_FilterEvent *evt);
/* from: filters.h:1468 */
void gf_filter_ask_rt_reschedule(GF_Filter *filter, u32 ms);

/* from: filters.h:87 */
typedef struct gf_filter_packet GF_FilterPacket;
/* from: filters.h:1507 */
GF_FilterPacket *gf_filter_pck_new_alloc(GF_FilterPid *pid, u32 size, u8 **data);
/* from: filters.h:1514 */
GF_FilterPacket *gf_filter_pck_new_shared(GF_FilterPid *pid, const u8 *data, u32 size, u8 **mapped_data);
/* from: filters.h:1521 */
void gf_filter_pck_set_framing(GF_FilterPacket *pck, Bool start, Bool end);
/* from: filters.h:1528 */
void gf_filter_pck_set_cts(GF_FilterPacket *pck, u64 cts);
/* from: filters.h:1535 */
void gf_filter_pck_set_dts(GF_FilterPacket *pck, u64 dts);
/* from: filters.h:1542 */
void gf_filter_pck_set_sap(GF_FilterPacket *pck, GF_FilterSAPType sap_type);
/* from: filters.h:1549 */
void gf_filter_pck_set_clock_type(GF_FilterPacket *pck, GF_FilterClockType clock_type);
/* from: filters.h:1556 */
void gf_filter_pck_set_property(GF_FilterPacket *pck, GF_PCKProperty prop, const GF_PropertyValue *val);
/* from: filters.h:1563 */
void gf_filter_pck_set_property_dyn(GF_FilterPacket *pck, const char *prop_name, const GF_PropertyValue *val);
/* from: filters.h:1570 */
void gf_filter_pck_send(GF_FilterPacket *pck);
/* from: filters.h:1577 */
void gf_filter_pck_get_framing(GF_FilterPacket *pck, Bool *start, Bool *end);

/* from: mpegts.h:1181 */
GF_M2TS_Demuxer *gf_m2ts_demux_new();
/* from: mpegts.h:1185 */
void gf_m2ts_demux_del(GF_M2TS_Demuxer *demux);
/* from: mpegts.h:1190 */
void gf_m2ts_reset_parsers(GF_M2TS_Demuxer *demux);
/* from: mpegts.h:1195 */
void gf_m2ts_mark_seg_start(GF_M2TS_Demuxer *demux);
/* from: mpegts.h:1201 */
void gf_m2ts_reset_parsers_for_program(GF_M2TS_Demuxer *demux, GF_M2TS_Program *program);
/* from: mpegts.h:1207 */
void gf_m2ts_flush_all(GF_M2TS_Demuxer *demux, Bool is_dash);
/* from: mpegts.h:1227 */
GF_M2TS_SDT *gf_m2ts_get_sdt_info(GF_M2TS_Demuxer *demux, u32 program_id);
/* from: mpegts.h:1252 */
void gf_m2ts_demux_dmscc_init(GF_M2TS_Demuxer *demux);

/* from: tools.h:1306 */
u64 gf_net_get_utc_ts(u32 year, u32 month, u32 day, u32 hour, u32 min, u32 sec);

/* from: tools.h:1052 */
void *gf_malloc(size_t size);
/* from: tools.h:1059 */
void gf_free(void *ptr);

/* from: tools.h:951 */
#define GF_LOG(_log_level, _log_tools, __args) if (gf_log_tool_level_on(_log_tools, _log_level) ) { gf_log_lt(_log_level, _log_tools); gf_log __args ;}

/* from: setup.h:431 */
#define ABS(a) ( ( (a) > 0 ) ? (a) : - (a) )

/* from: setup.h:830 */
#define gf_assert(_cond) gf_fatal_assert(_cond)

/* from: mpegts.h:365 */
#define GF_M2TS_MAX_PCR 2576980377811ULL

/* from: mpegts.h:744 */
#define GF_M2TS_CHECK_DISC (1<<21)

/* from: mpegts.h:149 */
#define GF_M2TS_PID_PAT 0x0000
/* from: mpegts.h:150 */
#define GF_M2TS_PID_CAT 0x0001
/* from: mpegts.h:153 */
#define GF_M2TS_PID_NIT_ST 0x0010
/* from: mpegts.h:154 */
#define GF_M2TS_PID_SDT_BAT_ST 0x0011
/* from: mpegts.h:155 */
#define GF_M2TS_PID_EIT_ST_CIT 0x0012
/* from: mpegts.h:157 */
#define GF_M2TS_PID_TDT_TOT_ST 0x0014

/* from: mpegts.h:1244 */
typedef struct
{
	u8 sync;
	u8 error;
	u8 payload_start;
	u8 priority;
	u16 pid;
	u8 scrambling_ctrl;
	u8 adaptation_field;
	u8 continuity_counter;
} GF_M2TS_Header;

/* from: mpegts.h:1265 */
typedef struct
{
	u32 discontinuity_indicator;
	u32 random_access_indicator;
	u32 priority_indicator;
	u32 PCR_flag;
	u64 PCR_base;
	u64 PCR_ext;
	u32 OPCR_flag;
	u64 OPCR_base;
	u64 OPCR_ext;
	u32 splicing_point_flag;
	u32 transport_private_data_flag;
	u32 adaptation_field_extension_flag;
} GF_M2TS_AdaptationField;

/* from: mpegts.h:1071 */
typedef struct
{
	u8 *data;
	u32 pid;
	GF_M2TS_ES *stream;
} GF_M2TS_TSPCK;

/* from: filters.h:4454 */
const u8 *gf_filter_pck_get_data(GF_FilterPacket *pck, u32 *size);

/* from: mpegts.c:174 */
static u32 gf_m2ts_sync(GF_M2TS_Demuxer *ts, char *data, u32 size, Bool simple_check);
/* from: mpegts.c:2308 */
static void gf_m2ts_get_adaptation_field(GF_M2TS_Demuxer *ts, GF_M2TS_AdaptationField *paf, u8 *data, u32 size, u32 pid);
/* from: mpegts.c:2198 */
static void gf_m2ts_process_pes(GF_M2TS_Demuxer *ts, GF_M2TS_PES *pes, GF_M2TS_Header *hdr, unsigned char *data, u32 data_size, GF_M2TS_AdaptationField *paf);

/* from: tools.h:696 */
typedef enum {
	GF_LOG_ERROR = 0,
	GF_LOG_WARNING,
	GF_LOG_INFO,
	GF_LOG_DEBUG,
} GF_LOG_Level;

/* from: tools.h:712 */
typedef enum {
	GF_LOG_SYNC = 0,
	GF_LOG_CODEC,
	GF_LOG_CONTAINER,
	GF_LOG_NETWORK,
	GF_LOG_RTP,
	GF_LOG_APP,
	GF_LOG_SCENE,
	GF_LOG_INTERACT,
	GF_LOG_AUTH,
	GF_LOG_DB,
	GF_LOG_X3D,
	GF_LOG_SVG,
	GF_LOG_MEDIA,
	GF_LOG_FILTERS,
	GF_LOG_ROUTE,
	GF_LOG_DASH,
	GF_LOG_GLES,
	GF_LOG_SHADER,
	GF_LOG_TEXTURE,
	GF_LOG_AI,
} GF_LOG_Tool;

/* from: tools.h:886 */
Bool gf_log_tool_level_on(GF_LOG_Tool log_tool, GF_LOG_Level log_level);
/* from: tools.h:931 */
void gf_log_lt(GF_LOG_Level level, GF_LOG_Tool tool);
void gf_log(const char *fmt, ...);

/* from: dmx_m2ts.c:182 */
static void m2tsdmx_update_sdt(GF_M2TS_Demuxer *ts, void *for_pid);
/* from: dmx_m2ts.c:614 */
static void m2tsdmx_setup_program(GF_M2TSDmxCtx *ctx, GF_M2TS_Program *prog);
/* from: dmx_m2ts.c:686 */
static void m2tsdmx_send_packet(GF_M2TSDmxCtx *ctx, GF_M2TS_PES_PCK *pck);
/* from: dmx_m2ts.c:818 */
static void m2tsdmx_send_sl_packet(GF_M2TSDmxCtx *ctx, GF_M2TS_SL_PCK *pck);

/* from: dmx_m2ts.c:170 */
static void m2tsdmx_on_event_duration_probe(GF_M2TS_Demuxer *ts, u32 evt_type, void *param);
/* from: dmx_m2ts.c:110 */
static void m2tsdmx_estimate_duration(GF_M2TSDmxCtx *ctx, GF_M2TS_ES *stream);

/* from: dmx_m2ts.c:590 */
static void m2tsdmx_setup_scte35(GF_M2TSDmxCtx *ctx, GF_M2TS_Program *prog);
/* from: dmx_m2ts.c:207 */
static void m2tsdmx_declare_pid(GF_M2TSDmxCtx *ctx, GF_M2TS_PES *stream, void *esd);

static void *gf_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
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
			gf_fatal_assert(ctx->wait_for_progs);
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
	case GF_M2TS_EVT_SL_PCK:
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

		gf_fatal_assert(pck->stream);
		if (!ctx->sigfrag && ctx->index) {
			m2tsdmx_estimate_duration(ctx, (GF_M2TS_ES *) pck->stream);
		}

		if (ctx->map_time_on_prog_id && (ctx->map_time_on_prog_id==pck->stream->program->number)) {
			map_time = GF_TRUE;
		}

		pcr = ((GF_M2TS_PES_PCK *) param)->PTS;
		pcr /= 300;
		count = gf_list_count(pck->stream->program->streams);
		for (i=0; i<count; i++) {
			GF_FilterPacket *dst_pck;
			GF_M2TS_PES *stream = gf_list_get(pck->stream->program->streams, i);
			if (!stream->user) continue;

			dst_pck = gf_filter_pck_new_shared(stream->user, NULL, 0, NULL);
			if (!dst_pck) continue;

			gf_filter_pck_set_cts(dst_pck, pcr);
			gf_filter_pck_set_clock_type(dst_pck, discontinuity ? GF_FILTER_CLOCK_PCR_DISC : GF_FILTER_CLOCK_PCR);
			if (pck->stream->is_seg_start) {
				pck->stream->is_seg_start = GF_FALSE;
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
					gf_filter_pid_set_property(stream->user, GF_PROP_PID_DURATION, & PROP_FRAC64_INT(duration, 1000) );
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
		void *bs;
		GF_M2TS_ES *es=NULL;
		GF_M2TS_Prop_TEMIInfo *t;
		if ((temi_l->pid<8192) && (ctx->ts->ess[temi_l->pid])) {
			es = ctx->ts->ess[temi_l->pid];
		}
		if (!es || !es->user) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] TEMI location not assigned to a given PID, not supported\n"));
			break;
		}
		GF_SAFEALLOC(t, GF_M2TS_Prop_TEMIInfo);
		if (!t) break;
		t->timeline_id = temi_l->timeline_id;
		t->is_loc = GF_TRUE;

		bs = NULL;
		if (ctx->temi_url)
			url = ctx->temi_url;
		else
			url = temi_l->external_URL;
		len = url ? (u32) strlen(url) : 0;
		t->data = (u8*)gf_malloc(len + 1);
		if (url) memcpy(t->data, url, len);
		t->data[len] = 0;
		t->len = len + 4;

		if (!es->props) {
			es->props = gf_list_new();
		}
		gf_list_add(es->props, t);
	}
	break;
	case GF_M2TS_EVT_TEMI_TIMECODE:
	{
		GF_M2TS_TemiTimecodeDescriptor *temi_t = (GF_M2TS_TemiTimecodeDescriptor*)param;
		void *bs;
		GF_M2TS_Prop_TEMIInfo *t;
		GF_M2TS_ES *es=NULL;
		if ((temi_t->pid<8192) && (ctx->ts->ess[temi_t->pid])) {
			es = ctx->ts->ess[temi_t->pid];
		}
		if (!es || !es->user) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] TEMI timing not assigned to a given PID, not supported\n"));
			break;
		}
		GF_SAFEALLOC(t, GF_M2TS_Prop_TEMIInfo);
		if (!t) break;
		t->type = M2TS_TEMI_INFO;
		t->timeline_id = temi_t->timeline_id;

		t->data = (u8*)gf_malloc(25);
		memset(t->data, 0, 25);
		t->len = 25;

		if (!es->props) {
			es->props = gf_list_new();
		}
		gf_list_add(es->props, t);
	}
	break;
	case GF_M2TS_EVT_ID3:
	{
		GF_M2TS_PES_PCK *pck = (GF_M2TS_PES_PCK*)param;
		void *bs;
		GF_M2TS_Prop *t;
		if (!pck->stream) return;
		u32 count = gf_list_count(pck->stream->program->streams);
		for (i=0; i<count; i++) {
			GF_M2TS_PES *es = gf_list_get(pck->stream->program->streams, i);
			if (!es->user) {
				GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] ID3 metadata not assigned to a given PID, not supported\n"));
				continue;
			}

			GF_FilterPid *opid = (GF_FilterPid *)es->user;
			const GF_PropertyValue *p = gf_filter_pid_get_property(opid, GF_PROP_PID_STREAM_TYPE);
			if (!p) return;
			if (p->value.uint != GF_STREAM_AUDIO)
				continue;

			GF_SAFEALLOC(t, GF_M2TS_Prop);
			if (!t) break;
			t->type = M2TS_ID3;
			t->data = (u8*)gf_malloc(pck->data_len + 12);
			memcpy(t->data, &pck->PTS, 8);
			memcpy(t->data + 8, &pck->data_len, 4);
			memcpy(t->data + 12, pck->data, pck->data_len);
			t->len = pck->data_len + 12;

			if (!es->props) {
				es->props = gf_list_new();
			}
			gf_list_add(es->props, t);
		}
	}
	break;
	case GF_M2TS_EVT_SCTE35_SPLICE_INFO:
	{
		GF_M2TS_SL_PCK *pck = (GF_M2TS_SL_PCK*)param;
		void *bs;
		GF_M2TS_Prop *t;

		u32 count = gf_list_count(pck->stream->program->streams);
		for (i=0; i<count; i++) {
			GF_M2TS_PES *es = gf_list_get(pck->stream->program->streams, i);
			if (!es->user) {
				GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[M2TSDmx] SCTE35 section not assigned to a given PID, not supported\n"));
				continue;
			}

			GF_FilterPid *opid = (GF_FilterPid *)es->user;
			const GF_PropertyValue *p = gf_filter_pid_get_property(opid, GF_PROP_PID_STREAM_TYPE);
			if (!p) return;
			if (p->value.uint != GF_STREAM_VISUAL)
				continue;

			GF_SAFEALLOC(t, GF_M2TS_Prop);
			if (!t) break;
			t->type = M2TS_SCTE35;
			t->data = (u8*)gf_malloc(pck->data_len);
			memcpy(t->data, pck->data, pck->data_len);
			t->len = pck->data_len;

			if (!es->props) {
				es->props = gf_list_new();
			}
			gf_list_add(es->props, t);

			break;
		}
	}
	break;
	case GF_M2TS_EVT_STREAM_REMOVED:
	{
		GF_M2TS_ES *es = (GF_M2TS_ES *)param;
		if (es && es->props) {
			while (gf_list_count(es->props)) {
				GF_M2TS_Prop *t = gf_list_pop_back(es->props);
				gf_free(t->data);
				gf_free(t);
			}
			gf_list_del(es->props);
		}
	}
		break;
	}
}

static void gf_m2ts_section_complete(GF_M2TS_Demuxer *ts, GF_M2TS_SectionFilter *sec, GF_M2TS_SECTION_ES *ses)
{
	if (ts->seek_mode && (sec->section[0] != 0x00) && (sec->section[0] != 0x02)) {
		if (sec->section) gf_free(sec->section);
		sec->section = NULL;
		sec->length = sec->received = 0;
		return;
	}

	if (!sec->process_section) {
		if ((ts->on_event && (sec->section[0]==0x74)) ) {
			GF_M2TS_SL_PCK pck;
			pck.data_len = sec->length;
			pck.data = sec->section;
			pck.stream = (GF_M2TS_ES *)ses;
		} else if ((ts->on_event && (sec->section[0]==0x3A || sec->section[0]==0x3B ||
		                             sec->section[0]==0x3C || sec->section[0]==0x3D || sec->section[0]==0x3E)) ) {

			GF_M2TS_SL_PCK pck;
			pck.data_len = sec->length;
			pck.data = sec->section;
			pck.stream = (GF_M2TS_ES *)ses;
		}
		else if ((ts->on_event && (sec->section[0]==0xFC)) ) {
			GF_M2TS_SL_PCK pck;
			pck.data_len = sec->length;
			pck.data = sec->section;
			pck.stream = (GF_M2TS_ES *)ses;
			ts->on_event(ts, 30, &pck);
		}
		else if (ts->on_event) {
			GF_M2TS_SL_PCK pck;
			pck.data_len = sec->length;
			pck.data = sec->section;
			pck.stream = (GF_M2TS_ES *)ses;
			ts->on_event(ts, 24, &pck);
		}
	} else {
		Bool has_syntax_indicator;
		u8 table_id;
		u16 extended_table_id;
		u32 status, section_start, i;
		GF_M2TS_Table *t, *prev_t;
		unsigned char *data;
		Bool section_valid = 0;

		status = 0;
		data = (u8 *)sec->section;

		if (sec->length < 2) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] M2TS Table parsing error, length %d is too small\n", sec->length) );
			return;
		}

		table_id = data[0];

		if (ts->on_event) {
			switch (table_id) {
			case 0x00:
			case 0x42:
			case 0x02:
			case 0x40:
			case 0x70:
			case 0x73:
			{
				GF_M2TS_SL_PCK pck;
				pck.data_len = sec->length;
				pck.data = sec->section;
				pck.stream = (GF_M2TS_ES *)ses;
				ts->on_event(ts, 24, &pck);
			}
			}
		}

		has_syntax_indicator = (data[1] & 0x80) ? 1 : 0;
		if (has_syntax_indicator) {
			if (sec->length < 5) {
				GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] M2TS Table parsing error, length %d is too small\n", sec->length) );
				return;
			}
			extended_table_id = (data[3]<<8) | data[4];
		} else {
			extended_table_id = 0;
		}

		prev_t = NULL;
		t = sec->table;
		while (t) {
			if ((t->table_id==table_id) && (t->ex_table_id == extended_table_id)) break;
			prev_t = t;
			t = t->next;
		}

		if (!t) {
			GF_SAFEALLOC(t, GF_M2TS_Table);
			if (!t) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Fail to alloc table %d %d\n", table_id, extended_table_id));
				return;
			}
			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] Creating table %d %d\n", table_id, extended_table_id));
			t->table_id = table_id;
			t->ex_table_id = extended_table_id;
			t->last_version_number = 0xFF;
			t->sections = gf_list_new();
			if (prev_t) prev_t->next = t;
			else sec->table = t;
		}

		if (has_syntax_indicator) {
			if (sec->length < 4) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] corrupted section length %d less than CRC \n", sec->length));
			} else {
				sec->length -= 4;
				if (1) {
					s32 cur_sec_num;
					t->version_number = (data[5] >> 1) & 0x1f;
					if (t->last_section_number && t->section_number && (t->version_number != t->last_version_number)) {
						GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] table transmission interrupted: previous table (v=%d) %d/%d sections - new table (v=%d) %d/%d sections\n", t->last_version_number, t->section_number, t->last_section_number, t->version_number, data[6] + 1, data[7] + 1) );
						t->section_number = 0;
					}

					t->current_next_indicator = (data[5] & 0x1) ? 1 : 0;
					cur_sec_num = data[6] + 1;
					t->last_section_number = data[7] + 1;
					section_start = 8;
					if (!sec->process_individual && t->section_number + 1 != cur_sec_num) {
						section_valid = 0;
						if (t->is_init) {
							GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] corrupted table (lost section %d)\n", cur_sec_num ? cur_sec_num-1 : 31) );
						}
					} else {
						section_valid = 1;
						t->section_number = cur_sec_num;
					}
				} else {
					GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] corrupted section (CRC32 failed)\n"));
				}
			}
		} else {
			section_valid = 1;
			section_start = 3;
		}
		if (section_valid) {
			GF_M2TS_Section *section;

			GF_SAFEALLOC(section, GF_M2TS_Section);
			if (!section) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Fail to create section\n"));
				return;
			}
			section->data_size = sec->length - section_start;
			section->data = (unsigned char*)gf_malloc(sizeof(unsigned char)*section->data_size);
			memcpy(section->data, sec->section + section_start, sizeof(unsigned char)*section->data_size);
			gf_list_add(t->sections, section);

			if (t->section_number == 1) {
				status |= 1;
				if (t->last_version_number == t->version_number) {
					t->is_repeat = 1;
				} else {
					t->is_repeat = 0;
				}
				t->last_version_number = t->version_number;
			}

			if (t->is_init) {
				if (t->is_repeat) {
					status |=  1<<3;
				} else {
					status |=  1<<2;
				}
			} else {
				status |=  1<<1;
			}

			if (t->last_section_number == t->section_number) {
				u32 table_size;

				status |= 1<<0;

				table_size = 0;
				for (i=0; i<gf_list_count(t->sections); i++) {
					GF_M2TS_Section *a_sec = gf_list_get(t->sections, i);
					table_size += a_sec->data_size;
				}
				if (t->is_repeat) {
					if (t->table_size != table_size) {
						status |= 1<<2;
						GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] Repeated section found with different sizes (old table %d bytes, new table %d bytes)\n", t->table_size, table_size) );

						t->table_size = table_size;
					}
				} else {
					t->table_size = table_size;
				}

				t->is_init = 1;
				t->section_number = 0;

				t->is_repeat = 0;

			}

			if (sec->process_individual) {
				if (sec->process_section)
					sec->process_section(ts, ses, t->sections, t->table_id, t->ex_table_id, t->version_number, (u8) (t->last_section_number - 1), status);

				t->section_number = 0;
			} else {
				if (status& (1<<0)) {
					if (sec->process_section)
						sec->process_section(ts, ses, t->sections, t->table_id, t->ex_table_id, t->version_number, (u8) (t->last_section_number - 1), status);

					t->section_number = 0;
				}
			}

		} else {
			sec->cc = -1;
			t->section_number = 0;
		}
	}
	if (sec->section) gf_free(sec->section);
	sec->section = NULL;
	sec->length = sec->received = 0;
}

static void gf_m2ts_gather_section(GF_M2TS_Demuxer *ts, GF_M2TS_SectionFilter *sec, GF_M2TS_SECTION_ES *ses, void *hdr, unsigned char *data, u32 data_size)
{
	u32 payload_size = data_size;
	u8 expect_cc = (sec->cc<0) ? ((u8*)hdr)[3] & 0xf : (sec->cc + 1) & 0xf;
	Bool disc = (expect_cc == ((u8*)hdr)[3] & 0xf) ? 0 : 1;
	sec->cc = expect_cc;

	if (!data_size) return;

	if (((u8*)hdr)[1] & 0x40) {
		u32 ptr_field;

		ptr_field = data[0];
		if (ptr_field+1>data_size) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid section start (@ptr_field=%d, @data_size=%d)\n", ptr_field, data_size) );
			return;
		}

		if (!hdr)
			ts->last_pat_start_num = ts->pck_number-1;

		if (!sec->length && sec->received) {
			if (sec->received == 1)
				sec->length = (sec->section[0] << 8) | data[1];
			else
				sec->length = (sec->section[0] << 8) | sec->section[1];
			sec->section = (char*)gf_realloc(sec->section, sizeof(char)*sec->length);
		}

		if (sec->length && sec->received + ptr_field >= sec->length) {
			u32 len = sec->length - sec->received;
			memcpy(sec->section + sec->received, data+1, sizeof(char)*len);
			sec->received += len;
			if (ptr_field > len)
				GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] Invalid pointer field (@ptr_field=%d, @remaining=%d)\n", ptr_field, len) );
			gf_m2ts_section_complete(ts, sec, ses);
		}
		data += ptr_field+1;
		data_size -= ptr_field+1;
		payload_size -= ptr_field+1;

aggregated_section:

		if (sec->section) gf_free(sec->section);
		sec->length = sec->received = 0;
		sec->section = (char*)gf_malloc(sizeof(char)*data_size);
		memcpy(sec->section, data, sizeof(char)*data_size);
		sec->received = data_size;
	} else if (disc) {
		if (sec->section) gf_free(sec->section);
		sec->section = NULL;
		sec->received = sec->length = 0;
		return;
	} else if (!sec->section) {
		return;
	} else {
		if (sec->length && sec->received+data_size > sec->length)
			data_size = sec->length - sec->received;

		if (sec->length) {
			memcpy(sec->section + sec->received, data, sizeof(char)*data_size);
		} else {
			sec->section = (char*)gf_realloc(sec->section, sizeof(char)*(sec->received+data_size));
			memcpy(sec->section + sec->received, data, sizeof(char)*data_size);
		}
		sec->received += data_size;
	}
	if (!sec->length && (sec->received >= 3)) {
		sec->length = (sec->section[0] << 8) | sec->section[1];
		sec->section = (char*)gf_realloc(sec->section, sizeof(char)*sec->length);

		if (sec->received > sec->length) {
			data_size -= sec->received - sec->length;
			sec->received = sec->length;
		}
	}
	if (!sec->length || sec->received < sec->length) return;

	gf_m2ts_section_complete(ts, sec, ses);

	if (payload_size > data_size) {
		data += data_size;
		if (data[0] != 0xFF) {
			data_size = payload_size - data_size;
			payload_size = data_size;
			goto aggregated_section;
		}
	}
}

static GF_Err gf_m2ts_process_packet(GF_M2TS_Demuxer *ts, unsigned char *data)
{
	GF_M2TS_ES *es;
	GF_M2TS_Header hdr;
	GF_M2TS_AdaptationField af, *paf;
	u32 payload_size, af_size;
	u32 pos = 0;

	ts->pck_number++;

	/* read TS packet header*/
	hdr.sync = data[0];
	if (hdr.sync != 0x47) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d does not start with sync marker\n", ts->pck_number));
		return GF_CORRUPTED_DATA;
	}
	hdr.error = (data[1] & 0x80) ? 1 : 0;
	hdr.payload_start = (data[1] & 0x40) ? 1 : 0;
	hdr.priority = (data[1] & 0x20) ? 1 : 0;
	hdr.pid = ( (data[1]&0x1f) << 8) | data[2];
	hdr.scrambling_ctrl = (data[3] >> 6) & 0x3;
	hdr.adaptation_field = (data[3] >> 4) & 0x3;
	hdr.continuity_counter = data[3] & 0xf;

	if (hdr.error) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d has error (PID could be %d)\n", ts->pck_number, hdr.pid));
		return GF_CORRUPTED_DATA;
	}
//#if DEBUG_TS_PACKET
	GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d PID %d CC %d Encrypted %d\n", ts->pck_number, hdr.pid, hdr.continuity_counter, hdr.scrambling_ctrl));
//#endif

	if (hdr.scrambling_ctrl) {
		//TODO add decyphering
		GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d is scrambled - not supported\n", ts->pck_number, hdr.pid));
		return GF_NOT_SUPPORTED;
	}

	paf = NULL;
	payload_size = 184;
	pos = 4;
	switch (hdr.adaptation_field) {
	/*adaptation+data*/
	case 3:
		af_size = data[4];
		if (af_size>183) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d AF field larger than 183  for AF type 3!\n", ts->pck_number));
			//error
			return GF_CORRUPTED_DATA;
		}
		paf = &af;
		memset(paf, 0, sizeof(GF_M2TS_AdaptationField));
		if (af_size) gf_m2ts_get_adaptation_field(ts, paf, data+5, af_size, hdr.pid);
		pos += 1+af_size;
		payload_size = 183 - af_size;
		break;
	/*adaptation only - still process in case of PCR*/
	case 2:
		af_size = data[4];
		if (af_size != 183) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] TS Packet %d AF size is %d when it must be 183 for AF type 2\n", ts->pck_number, af_size));
			return GF_CORRUPTED_DATA;
		}
		paf = &af;
		memset(paf, 0, sizeof(GF_M2TS_AdaptationField));
		gf_m2ts_get_adaptation_field(ts, paf, data+5, af_size, hdr.pid);
		payload_size = 0;
		/*no payload and no PCR, return*/
		if (!paf->PCR_flag)
			return GF_OK;
		break;
	/*reserved*/
	case 0:
		return GF_OK;
	default:
		break;
	}
	data += pos;

	/*PAT*/
	if (hdr.pid == GF_M2TS_PID_PAT) {
		gf_m2ts_gather_section(ts, ts->pat, NULL, &hdr, data, payload_size);
		return GF_OK;
	}

	es = ts->ess[hdr.pid];
	//we work in split mode
	if (ts->split_mode) {
		GF_M2TS_TSPCK tspck;
		//process PMT table
		if (es && (es->flags & GF_M2TS_ES_IS_PMT)) {
			GF_M2TS_SECTION_ES *ses = (GF_M2TS_SECTION_ES *)es;
			if (ses->sec) gf_m2ts_gather_section(ts, ses->sec, ses, &hdr, data, payload_size);
		}
		//and forward every packet other than PAT
		tspck.stream = es;
		tspck.pid = hdr.pid;
		tspck.data = data - pos;
		ts->on_event(ts, GF_M2TS_EVT_PCK, &tspck);
		return GF_OK;
	}

	if (hdr.pid == GF_M2TS_PID_CAT) {
		gf_m2ts_gather_section(ts, ts->cat, NULL, &hdr, data, payload_size);
		return GF_OK;
	}

	if (paf && paf->PCR_flag) {
		if (!es) {
			u32 i, j;
			for(i=0; i<gf_list_count(ts->programs); i++) {
				GF_M2TS_PES *first_pes = NULL;
				GF_M2TS_Program *program = (GF_M2TS_Program *)gf_list_get(ts->programs,i);
				if(program->pcr_pid != hdr.pid) continue;
				for (j=0; j<gf_list_count(program->streams); j++) {
					GF_M2TS_PES *pes = (GF_M2TS_PES *) gf_list_get(program->streams, j);
					if (pes->flags & GF_M2TS_INHERIT_PCR) {
						ts->ess[hdr.pid] = (GF_M2TS_ES *) pes;
						pes->flags |= GF_M2TS_FAKE_PCR | GF_M2TS_ES_IS_PCR_REUSE;
						break;
					}
					if (pes->flags & GF_M2TS_ES_IS_PES) {
						first_pes = pes;
					}
				}
				//non found, use the first media stream as a PCR destination - Q: is it legal to have PCR only streams not declared in PMT ?
				if (!es && first_pes) {
					es = (GF_M2TS_ES *) first_pes;
					first_pes->flags |= GF_M2TS_FAKE_PCR;
				}
				break;
			}
			if (!es)
				es = ts->ess[hdr.pid];
		}
		if (es) {
			GF_M2TS_PES_PCK pck;
			s64 prev_diff_in_us;
			Bool discontinuity;
			s32 cc = -1;

			if (es->flags & GF_M2TS_FAKE_PCR) {
				cc = es->program->pcr_cc;
				es->program->pcr_cc = hdr.continuity_counter;
			}
			else if (es->flags & GF_M2TS_ES_IS_PES) cc = ((GF_M2TS_PES*)es)->cc;
			else if (((GF_M2TS_SECTION_ES*)es)->sec) cc = ((GF_M2TS_SECTION_ES*)es)->sec->cc;

			discontinuity = paf->discontinuity_indicator;
			if ((cc>=0) && es->program->before_last_pcr_value) {
				//no increment of CC if AF only packet
				if (hdr.adaptation_field == 2) {
					if (hdr.continuity_counter != cc) {
						discontinuity = GF_TRUE;
					}
				} else if (hdr.continuity_counter != ((cc + 1) & 0xF)) {
					discontinuity = GF_TRUE;
				}
			}

			memset(&pck, 0, sizeof(GF_M2TS_PES_PCK));
			prev_diff_in_us = (s64) (es->program->last_pcr_value /27- es->program->before_last_pcr_value/27);
			es->program->before_last_pcr_value = es->program->last_pcr_value;
			es->program->before_last_pcr_value_pck_number = es->program->last_pcr_value_pck_number;
			es->program->last_pcr_value_pck_number = ts->pck_number;
			es->program->last_pcr_value = paf->PCR_base * 300 + paf->PCR_ext;
			if (!es->program->last_pcr_value) es->program->last_pcr_value =  1;

			GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR found "LLU" ("LLU" at 90kHz) - PCR diff is %d us\n", hdr.pid, es->program->last_pcr_value, es->program->last_pcr_value/300, (s32) (es->program->last_pcr_value - es->program->before_last_pcr_value)/27 ));

			pck.PTS = es->program->last_pcr_value;
			pck.stream = (GF_M2TS_PES *)es;

			//try to ignore all discontinuities that are less than 200 ms (seen in some HLS setup ...)
			if (discontinuity) {
				s64 diff_in_us = (s64) (es->program->last_pcr_value - es->program->before_last_pcr_value) / 27;
				u64 diff = ABS(diff_in_us - prev_diff_in_us);

				if ((diff_in_us<0) && (diff_in_us >= -200000)) {
					GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d new PCR, with discontinuity signaled, is less than previously received PCR (diff %d us) but not too large, trying to ignore discontinuity\n", hdr.pid, diff_in_us));
				}

				//ignore PCR discontinuity indicator if PCR found is larger than previously received PCR and diffence between PCR before and after discontinuity indicator is smaller than 50ms
				else if ((diff_in_us > 0) && (diff < 200000)) {
					GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR discontinuity signaled but diff is small (diff %d us - PCR diff %d vs prev PCR diff %d) - ignore it\n", hdr.pid, diff, diff_in_us, prev_diff_in_us));
				} else if (paf->discontinuity_indicator) {
					GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR discontinuity signaled (diff %d us - PCR diff %d vs prev PCR diff %d)\n", hdr.pid, diff, diff_in_us, prev_diff_in_us));
					pck.flags = GF_M2TS_PES_PCK_DISCONTINUITY;
				} else {
					GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR discontinuity not signaled (diff %d us - PCR diff %d vs prev PCR diff %d)\n", hdr.pid, diff, diff_in_us, prev_diff_in_us));
					pck.flags = GF_M2TS_PES_PCK_DISCONTINUITY;
				}
			}
			else if ((es->flags & GF_M2TS_CHECK_DISC) && (es->program->last_pcr_value < es->program->before_last_pcr_value) ) {
				s64 diff_in_us = (s64) (es->program->last_pcr_value - es->program->before_last_pcr_value) / 27;
				//if less than 200 ms before PCR loop at the last PCR, this is a PCR loop
				if (GF_M2TS_MAX_PCR - es->program->before_last_pcr_value < 5400000 /*2*2700000*/) {
					GF_LOG(GF_LOG_INFO, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR loop found from "LLU" to "LLU" \n", hdr.pid, es->program->before_last_pcr_value, es->program->last_pcr_value));
				} else if ((diff_in_us<0) && (diff_in_us >= -200000)) {
					GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d new PCR, without discontinuity signaled, is less than previously received PCR (diff %d us) but not too large, trying to ignore discontinuity\n", hdr.pid, diff_in_us));
				} else {
					GF_LOG(GF_LOG_WARNING, GF_LOG_CONTAINER, ("[MPEG-2 TS] PID %d PCR found "LLU" is less than previously received PCR "LLU" (PCR diff %g sec) but no discontinuity signaled\n", hdr.pid, es->program->last_pcr_value, es->program->before_last_pcr_value, (GF_M2TS_MAX_PCR - es->program->before_last_pcr_value + es->program->last_pcr_value) / 27000000.0));

					pck.flags = GF_M2TS_PES_PCK_DISCONTINUITY;
				}
			}

			if (pck.flags & GF_M2TS_PES_PCK_DISCONTINUITY) {
				gf_m2ts_reset_parsers_for_program(ts, es->program);
			}

			if (ts->on_event) {
				ts->on_event(ts, GF_M2TS_EVT_PES_PCR, &pck);
			}
		}
	}

	/*check for DVB reserved PIDs*/
	if (!es) {
		if (hdr.pid == GF_M2TS_PID_SDT_BAT_ST) {
			gf_m2ts_gather_section(ts, ts->sdt, NULL, &hdr, data, payload_size);
			return GF_OK;
		} else if (hdr.pid == GF_M2TS_PID_NIT_ST) {
			/*ignore them, unused at application level*/
			gf_m2ts_gather_section(ts, ts->nit, NULL, &hdr, data, payload_size);
			return GF_OK;
		} else if (hdr.pid == GF_M2TS_PID_EIT_ST_CIT) {
			/* ignore EIT messages for the moment */
			gf_m2ts_gather_section(ts, ts->eit, NULL, &hdr, data, payload_size);
			return GF_OK;
		} else if (hdr.pid == GF_M2TS_PID_TDT_TOT_ST) {
			gf_m2ts_gather_section(ts, ts->tdt_tot, NULL, &hdr, data, payload_size);
		} else {
			/* ignore packet */
		}
	} else if (es->flags & GF_M2TS_ES_IS_SECTION) { 	/* The stream uses sections to carry its payload */
		GF_M2TS_SECTION_ES *ses = (GF_M2TS_SECTION_ES *)es;
		if (ses->sec) gf_m2ts_gather_section(ts, ses->sec, ses, &hdr, data, payload_size);
	} else {
		GF_M2TS_PES *pes = (GF_M2TS_PES *)es;
		/* regular stream using PES packets */
		if (pes->reframe && payload_size) gf_m2ts_process_pes(ts, pes, &hdr, data, payload_size, paf);
	}

	return GF_OK;
}

GF_EXPORT
GF_Err gf_m2ts_process_data(GF_M2TS_Demuxer *ts, u8 *data, u32 data_size)
{
	GF_Err e=GF_OK;
	u32 pos, pck_size;
	Bool is_align = 1;

	if (ts->buffer_size) {
		//we are sync, copy remaining bytes
		if ( (ts->buffer[0]==0x47) && (ts->buffer_size<200)) {
			u32 copy_size;
			pck_size = ts->prefix_present ? 192 : 188;

			if (ts->alloc_size < 200) {
				ts->alloc_size = 200;
				ts->buffer = (char*)gf_realloc(ts->buffer, sizeof(char)*ts->alloc_size);
			}
			copy_size = pck_size - ts->buffer_size;
			if (copy_size > data_size) {
				memcpy(ts->buffer + ts->buffer_size, data, data_size);
				ts->buffer_size += data_size;
				return GF_OK;
			}
			memcpy(ts->buffer + ts->buffer_size, data, copy_size);
			e |= gf_m2ts_process_packet(ts, (unsigned char *)ts->buffer);
			data += copy_size;
			data_size = data_size - copy_size;
			gf_assert((s32)data_size >= 0);
		}
		//not sync, copy over the complete buffer
		else {
			if (ts->alloc_size < ts->buffer_size+data_size) {
				ts->alloc_size = ts->buffer_size+data_size;
				ts->buffer = (char*)gf_realloc(ts->buffer, sizeof(char)*ts->alloc_size);
			}
			memcpy(ts->buffer + ts->buffer_size, data, sizeof(char)*data_size);
			ts->buffer_size += data_size;
			is_align = 0;
			data = ts->buffer;
			data_size = ts->buffer_size;
		}
	}

	/*sync input data*/
	pos = gf_m2ts_sync(ts, data, data_size, is_align);
	if (pos==data_size) {
		if (is_align) {
			if (ts->alloc_size<data_size) {
				ts->buffer = (char*)gf_realloc(ts->buffer, sizeof(char)*data_size);
				ts->alloc_size = data_size;
			}
			memcpy(ts->buffer, data, sizeof(char)*data_size);
			ts->buffer_size = data_size;
		}
		return GF_OK;
	}
	pck_size = ts->prefix_present ? 192 : 188;
	for (;;) {
		/*wait for a complete packet*/
		if (data_size < pos  + pck_size) {
			ts->buffer_size = data_size - pos;
			data += pos;
			if (!ts->buffer_size) {
				return e;
			}
			gf_assert(ts->buffer_size<pck_size);

			if (is_align) {
				u32 s = ts->buffer_size;
				if (s<200) s = 200;

				if (ts->alloc_size < s) {
					ts->alloc_size = s;
					ts->buffer = (char*)gf_realloc(ts->buffer, sizeof(char)*ts->alloc_size);
				}
				memcpy(ts->buffer, data, sizeof(char)*ts->buffer_size);
			} else {
				memmove(ts->buffer, data, sizeof(char)*ts->buffer_size);
			}
			return e;
		}
		/*process*/
		GF_Err pck_e = gf_m2ts_process_packet(ts, (unsigned char *)data + pos);
		if (pck_e==GF_NOT_SUPPORTED) pck_e = GF_OK;
		e |= pck_e;

		pos += pck_size;
	}
	return e;
}

static GF_Err m2tsdmx_process(GF_Filter *filter)
{
	GF_M2TSDmxCtx *ctx = gf_filter_get_udta(filter);
	GF_FilterPacket *pck;
	Bool check_block = GF_TRUE;
	const char *data;
	u32 size;

restart:
	pck = gf_filter_pid_get_packet(ctx->ipid);
	if (!pck) {
		if (gf_filter_pid_is_eos(ctx->ipid)) {
			u32 i, nb_streams = gf_filter_get_opid_count(filter);

			gf_m2ts_flush_all(ctx->ts, ctx->is_dash);
			for (i=0; i<nb_streams; i++) {
				GF_FilterPid *opid = gf_filter_get_opid(filter, i);
				gf_filter_pid_set_eos(opid);
			}
			return GF_EOS;
		}
		return GF_OK;
	}
	if (ctx->sigfrag) {
		Bool is_start;
		gf_filter_pck_get_framing(pck, &is_start, NULL);
		if (is_start) {
			gf_m2ts_mark_seg_start(ctx->ts);
		}
	}
	//we process even if no stream playing: since we use unframed dispatch we may need to send packets to configure reframers
	//which will in turn connect to the sink which will send the PLAY event marking stream(s) as playing
	if (ctx->in_seek) {
		gf_m2ts_reset_parsers(ctx->ts);
		ctx->in_seek = GF_FALSE;
	} else if (check_block && !ctx->wait_for_progs) {
		u32 i, nb_streams, would_block = 0;
		nb_streams = gf_filter_get_opid_count(filter);
		for (i=0; i<nb_streams; i++) {
			GF_FilterPid *opid = gf_filter_get_opid(filter, i);
			if (!gf_filter_pid_is_playing(opid)) {
				would_block++;
			} else if ( gf_filter_pid_would_block(opid) ) {
				would_block++;
			}
		}
		if (would_block && (would_block==nb_streams)) {
			//keep filter alive
			if (ctx->nb_playing) {
				gf_filter_ask_rt_reschedule(filter, 0);
			}
			if (ctx->nb_stopped_at_init==nb_streams) {
				gf_filter_pid_set_discard(ctx->ipid, GF_TRUE);
				return GF_EOS;
			}
			return GF_OK;
		}

		check_block = GF_FALSE;
	}

	data = gf_filter_pck_get_data(pck, &size);
	if (data && size)
		gf_m2ts_process_data(ctx->ts, (char*) data, size);

	gf_filter_pid_drop_packet(ctx->ipid);

	if (ctx->mux_tune_state==DMX_TUNE_WAIT_SEEK) {
		GF_FilterEvent fevt;
		GF_FEVT_INIT(fevt, GF_FEVT_SOURCE_SEEK, ctx->ipid);
		gf_filter_pid_send_event(ctx->ipid, &fevt);
		ctx->mux_tune_state = DMX_TUNE_DONE;
		gf_m2ts_reset_parsers(ctx->ts);
	} else {
		goto restart;
	}
	return GF_OK;
}

/* from: filters.h:2315 */
#define GF_FS_SET_DESCRIPTION(_desc) .description = _desc,
/* from: filters.h:2319 */
#define GF_FS_SET_HELP(_help) .help = _help,
/* from: filters.h:2339 */
#define SETCAPS(_caps) .caps = _caps, .nb_caps = 0

/* from: filters.h:1248 */
typedef struct {
	const char *name;
	const char *help;
	u32 flags;
	u32 private_size;
	void *initialize;
	void *finalize;
	void *args;
	void *caps;
	u32 nb_caps;
	void *configure_pid;
	void *process;
	void *process_event;
	void *probe_data;
} GF_FilterRegisterInit;

static const void *M2TSDmxArgs;
static const GF_FilterCapability M2TSDmxCaps[];
static GF_Err m2tsdmx_initialize(GF_Filter *filter);
static GF_Err m2tsdmx_finalize(GF_Filter *filter);
static GF_Err m2tsdmx_configure_pid(GF_FilterPid *pid, GF_FilterPid *out);
static GF_Err m2tsdmx_process(GF_Filter *filter);
static GF_Err m2tsdmx_process_event(GF_Filter *filter, GF_FilterEvent *evt);
static Bool m2tsdmx_probe_data(GF_Filter *filter, const u8 *data, u32 size);

GF_FilterRegister M2TSDmxRegister = {
	.name = "m2tsdmx",
	GF_FS_SET_DESCRIPTION("MPEG-2 TS demultiplexer")
	GF_FS_SET_HELP("This filter demultiplexes MPEG-2 Transport Stream files/data into a set of media PIDs and frames.")
	.private_size = sizeof(GF_M2TSDmxCtx),
	.initialize = m2tsdmx_initialize,
	.finalize = m2tsdmx_finalize,
	.args = NULL,
#ifdef GPAC_CONFIG_EMSCRIPTEN
	.flags = GF_FS_REG_DYNAMIC_PIDS | GF_FS_REG_CONFIGURE_MAIN_THREAD,
#else
	.flags = GF_FS_REG_DYNAMIC_PIDS,
#endif
	SETCAPS(M2TSDmxCaps),
	.configure_pid = m2tsdmx_configure_pid,
	.process = m2tsdmx_process,
	.process_event = m2tsdmx_process_event,
	.probe_data = m2tsdmx_probe_data,
};

static GF_Err m2tsdmx_initialize(GF_Filter *filter)
{
	GF_M2TSDmxCtx *ctx = gf_filter_get_udta(filter);

	ctx->ts = gf_m2ts_demux_new();
	if (!ctx->ts) return GF_OUT_OF_MEM;

	ctx->ts->on_event = m2tsdmx_on_event;
	ctx->ts->user = filter;

	ctx->filter = filter;
	if (ctx->dsmcc) {
		gf_m2ts_demux_dmscc_init(ctx->ts);
	}

	return GF_OK;
}
