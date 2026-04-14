// Minimal reproducible unit for GPAC dasher_configure_pid
// Compile: clang -std=c99 -x c -c bad.cpp
// All code from snippet.txt and context.txt preserved unchanged

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64; typedef int64_t s64; typedef uint32_t u32; typedef int32_t s32;
typedef uint16_t u16; typedef int16_t s16; typedef uint8_t u8; typedef int8_t s8;
typedef double Double; typedef float Float;
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;
typedef enum { GF_EOS=1, GF_OK=0, GF_BAD_PARAM=-1, GF_OUT_OF_MEM=-2, GF_NOT_SUPPORTED=-4, GF_NON_COMPLIANT_BITSTREAM=-10, GF_NOT_FOUND=-53 } GF_Err;
typedef struct { s32 num; u32 den; } GF_Fraction;
typedef struct { s64 num; u64 den; } GF_Fraction64;
typedef struct { u32 timescale; } GF_PropertyMap;
typedef enum { GF_PROP_UINT=1, GF_PROP_SINT, GF_PROP_LONGUINT, GF_PROP_LONGSINT, GF_PROP_BOOL, GF_PROP_FLOAT, GF_PROP_DOUBLE, GF_PROP_STRING, GF_PROP_DATA, GF_PROP_DATA_NO_COPY=100, GF_PROP_STRING_NO_COPY=101, GF_PROP_STRING_LIST=102, GF_PROP_FRAC, GF_PROP_LFRAC, GF_PROP_VEC2I, GF_PROP_VEC4I } GF_PropType;
typedef struct __gf_prop_val { GF_PropType type; union { u32 uint; s32 sint; u64 longuint; s64 longsint; Bool boolean; Float f; Double d; char *string; struct { u8 *ptr; u32 size; } data; GF_Fraction frac; GF_Fraction64 lfrac; struct { s32 x, y; } vec2i; struct { s32 x, y, z, w; } vec4i; } value; } GF_PropertyValue;
typedef struct { u32 code; GF_PropertyValue val; u32 flags; } GF_FilterCapability;
typedef struct __gf_filter_register { u32 nb_caps; GF_FilterCapability *caps; } GF_FilterRegister;
typedef struct __gf_filter { char *name; GF_FilterRegister *freg; void *cap_dst_filter; void *destination_filters; void *destination_links; s32 cap_idx_at_resolution; u32 nb_forced_caps; GF_FilterCapability *forced_caps; void *dst_filter; u32 num_output_pids; void *output_pids; } GF_Filter;
typedef struct __gf_filter_pid_inst { GF_Filter *filter; u32 nb_forced_caps; GF_FilterCapability *forced_caps; u32 num_output_pids; void *output_pids; GF_PropertyMap *caps_negotiate; } GF_FilterPidInst;
typedef struct __gf_filter_pid { GF_PropertyMap *infos; GF_FilterPidInst *pid; GF_Filter *filter; Bool pid_info_changed; char *name; u32 num_destinations; void *destinations; } GF_FilterPid;
typedef union __gf_filter_event { u32 type; struct { u32 type; Double speed; } play; } GF_FilterEvent;
typedef struct __gf_file_io { char *url; } GF_FileIO;
typedef struct __gf_list { int dummy; } GF_List;
typedef struct __gf_mpd_period { char *ID; void *adaptation_sets; } GF_MPD_Period;
typedef struct __gf_mpd { GF_List *periods; } GF_MPD;
typedef struct __gf_mpd_segment_template { char *media; } GF_MPD_SegmentTemplate;
typedef struct __gf_mpd_representation { GF_MPD_SegmentTemplate *segment_template; } GF_MPD_Representation;
typedef struct __gf_mpd_adaptation_set { s32 id; GF_MPD_SegmentTemplate *segment_template; } GF_MPD_AdaptationSet;
typedef struct __gf_crypt_info { int dummy; } GF_CryptInfo;
typedef struct __gf_track_crypt_info { int dummy; } GF_TrackCryptInfo;
typedef struct __gf_dash_cue_info { int dummy; } GF_DASHCueInfo;
typedef struct __gf_dash_segment_context { int dummy; } GF_DASH_SegmentContext;

enum { GF_STREAM_UNKNOWN=0, GF_STREAM_VISUAL=1, GF_STREAM_AUDIO=2, GF_STREAM_SCENE=3, GF_STREAM_OD=4, GF_STREAM_TEXT=5, GF_STREAM_METADATA=6, GF_STREAM_FILE=7, GF_STREAM_ENCRYPTED=8 };
enum { GF_CODECID_NONE=0, GF_CODECID_AVC=1, GF_CODECID_SVC=2, GF_CODECID_MVC=3, GF_CODECID_HEVC=4, GF_CODECID_HEVC_TILES=5, GF_CODECID_LHVC=6, GF_CODECID_AAC_MPEG4=7, GF_CODECID_AAC_MPEG2_MP=8, GF_CODECID_AAC_MPEG2_LCP=9, GF_CODECID_AAC_MPEG2_SSRP=10, GF_CODECID_USAC=11, GF_CODECID_AC3=12, GF_CODECID_EAC3=13, GF_CODECID_AV1=14, GF_CODECID_VP8=15, GF_CODECID_VP9=16 };

#define GF_4CC(a,b,c,d) ((((u32)(a))<<24)|(((u32)(b))<<16)|(((u32)(c))<<8)|((u32)(d)))
#define GF_FS_SEP_NAME '/'
#define GF_SAFEALLOC(p,t) do{(p)=(t*)malloc(sizeof(t));if(p)memset(p,0,sizeof(t));}while(0)
#define GF_LOG(l,t,a) do{}while(0)
#define GF_FEVT_INIT(e,t,p) memset(&(e),0,sizeof(GF_FilterEvent))
#define GF_EXPORT __attribute__((visibility("default")))
#define PID_IS_INPUT(p) GF_FALSE
#define GF_CAPFLAG_IN_BUNDLE 1
#define GF_CAPFLAG_INPUT 2
#define GF_CAPFLAG_OPTIONAL 4

enum { DASHER_BOUNDS_OUT=0, DASHER_BOUNDS_CLOSEST, DASHER_BOUNDS_IN };
enum { DASHER_SYNC_UNKNOWN=0, DASHER_SYNC_NONE, DASHER_SYNC_PRESENT };
enum { DASHER_PSWITCH_SINGLE=0, DASHER_PSWITCH_FORCE, DASHER_PSWITCH_STSD };
enum { DASHER_HDR_NONE=0, DASHER_HDR_PQ10, DASHER_HDR_HLG };
enum { IDXMODE_NONE=0, IDXMODE_ALL, IDXMODE_MANIFEST, IDXMODE_CHILD, IDXMODE_INIT, IDXMODE_SEG };
enum { GF_DASH_PROFILE_MAIN=1, GF_DASH_PROFILE_AVC264_LIVE, GF_DASH_PROFILE_AVC264_ONDEMAND, GF_DASH_PROFILE_DASHIF_LL };
enum { GF_FEVT_PLAY=GF_4CC('P','L','A','Y'), GF_HEVC_NALU_VID_PARAM=0, GF_HEVC_NALU_SEQ_PARAM=1 };

typedef struct { s32 x,y,z,w; } GF_PropVec4i;
typedef enum { DASHER_HDR_NONE_E=0, DASHER_HDR_PQ10_E, DASHER_HDR_HLG_E } DasherHDRType;
typedef struct { GF_List *streams; GF_MPD_Period *period; } GF_DasherPeriod;
typedef struct _dash_stream GF_DashStream;

typedef struct {
    u32 bs_switch,profile,spd,cp,ntp,sigfrag,do_index,sbound,pswitch;
    s32 subs_sidx,buf,timescale; Bool sfile,sseg,no_sar,mix_codecs,stl,tpl,align,sap;
    Bool no_frag_def,sidx,split,hlsc,strict_cues,force_flush,last_seg_merge,check_connections;
    u32 mha_compat,strict_sap,pssh,cmaf,dkid,dmode,llhls,hls_absu,seg_sync,from_index,def_template;
    GF_Fraction segdur,cdur; char *template_str,*segext,*initext,*profX,*ast,*state,*cues;
    char *title,*source,*info,*cprt,*lang,*chain,*chain_fbk,*styp,*utcs,*mname,*hlsdrm,*ckurl,*out_path;
    struct{char **strings;u32 count;}location,base,hlsx;
    Bool check_dur,skip_seg,loop,reschedule,scope_deps,keep_src,tpl_force,keep_segs;
    Bool cmpd,dual,sreg,ll_preload_hint,ll_rend_rep,gencues,force_init,gxns,hls_ap;
    Bool in_error,is_eos,on_demand_done,subdur_done,first_context_load,store_init_params;
    Bool do_m3u8,do_mpd,is_period_restore,is_empty_period,store_seg_states;
    Bool use_xlink,use_cenc,check_main_role,use_clearkey,no_fragments_defaults;
    Bool explicit_mode,move_to_static,use_cues,dyn_rate,force_hls_ll_manifest,purge_segments,is_playing,no_seg_dur;
    Double refresh,tsb,subdur,asto,ll_part_hb,nb_secs_to_discard; GF_Err setup_failure;
    u32 nb_seg_url_pending,last_dyn_period_id,next_pid_id_in_period,utc_initialized,def_max_seg_dur,index_max_seg_dur;
    u64 last_evt_check_time,min_segment_start_time,last_min_segment_start_time,index_media_duration;
    s32 update_report,utc_diff,period_idx; u64 *_p_gentime,*_p_mpdtime; void *utc_sess; u32 forward_mode;
    GF_Fraction64 min_cts_period; u8 last_hls_signature[20],last_mpd_signature[20],last_hls2_signature[20];
    GF_CryptInfo *cinfo; GF_FilterPid *opid,*opid_alt; GF_Filter *alt_dst; Bool opid_alt_m3u8;
    GF_MPD *mpd; GF_DasherPeriod *current_period,*next_period; GF_List *pids,*tpl_records,*postponed_pids;
    Bool template_use_source; GF_List *multi_pids;
} GF_DasherCtx;

struct _dash_stream {
    GF_FilterPid *ipid,*opid; u32 codec_id,timescale,stream_type,dsi_crc,dsi_enh_crc,id,dep_id,src_id;
    GF_Fraction sar,fps; u32 width,height,sr,nb_ch,bitrate,view_id,nb_surround,nb_lfe,atmos_complexity_type;
    char *lang,*template_str,*xlink,*hls_vp_name,*period_id,*period_continuity_id,*rep_id,*src_url;
    char *init_seg,*seg_template,*idx_template; u64 ch_layout; GF_PropVec4i srd; DasherHDRType hdr_type;
    Bool sscale,interlaced,rawmux,is_av,is_encrypted,rep_init,forced_period_switch,splitable,tile_base;
    Bool tile_dep_id_merged,clamp_done,reschedule,inband_cues,owns_set,segment_started,subdur_done;
    Bool dyn_bitrate,stl,set_period_switch,transcode_detected,no_seg_dur,skip_tpl_reuse,cues_use_edits;
    u32 as_id,sync_as_id,nb_comp,nb_comp_done,nb_rep,nb_rep_done,startNumber,seg_number;
    u32 pid_id,dep_pid_id,nb_samples_in_source,sync_points_type,nb_sap_3,nb_sap_4,moof_sn_inc,moof_sn;
    u32 cues_timescale,nb_cues,nb_segments_purged,gm_nb_segments,loop_state,split_dur_next,tpl_use_time;
    u32 all_stsd_crc,request_period_switch,dcd_not_ready,hls_absu,done,seg_done,inband_params,force_timescale,mpd_timescale;
    u32 nb_sap_in_queue,sbound,key_idx,nb_crypt_seg; s32 cues_ts_offset; s64 pts_minus_cts;
    u64 first_cts,first_dts,presentation_time_offset,seg_start_time,max_period_dur,next_seg_start;
    u64 adjusted_next_seg_start,force_rep_end,first_cts_in_seg,first_cts_in_next_seg,min_cts_in_seg_plus_one;
    u64 est_first_cts_in_next_seg,last_cts,last_dts,cumulated_dur,nb_pck,est_next_dts,seek_to_pck,ts_offset;
    u64 rate_first_dts_plus_one,rate_last_dts,rate_media_size,period_continuity_next_cts,last_min_segment_start_time;
    u64 frag_start_offset,frag_first_ftdt,iv_low,iv_high;
    Double set_seg_duration,cumulated_subdur,gm_duration_total,gm_duration_min,gm_duration_max,dur_purged;
    GF_Fraction dash_dur; GF_Fraction64 period_start,period_dur,duration,clamped_dur;
    GF_DasherPeriod *period; GF_MPD_Period *last_period; GF_MPD_Representation *rep;
    GF_MPD_AdaptationSet *set; GF_DashStream *muxed_base,*merged_tile_dep;
    GF_List *complementary_streams,*comp_pids,*multi_pids,*multi_tracks;
    GF_List *pending_segment_urls,*pending_segment_states,*packet_queue;
    GF_Filter *dst_filter; const GF_PropertyValue *p_role,*p_period_desc,*p_as_desc,*p_as_any_desc,*p_rep_desc,*p_base_url;
    GF_DASHCueInfo *cues; GF_DASH_SegmentContext *current_seg_state; GF_CryptInfo *cinfo; GF_TrackCryptInfo *tci; u64 hls_ref_id;
};

enum {
    GF_PROP_PID_ID=GF_4CC('P','I','D','I'),GF_PROP_PID_DEPENDENCY_ID=GF_4CC('D','P','I','D'),
    GF_PROP_PID_STREAM_TYPE=GF_4CC('P','M','S','T'),GF_PROP_PID_ORIG_STREAM_TYPE=GF_4CC('P','O','S','T'),
    GF_PROP_PID_CODECID=GF_4CC('P','O','T','I'),GF_PROP_PID_UNFRAMED=GF_4CC('P','F','R','M'),
    GF_PROP_PID_DURATION=GF_4CC('P','D','U','R'),GF_PROP_PID_NB_FRAMES=GF_4CC('N','F','R','M'),
    GF_PROP_PID_TIMESCALE=GF_4CC('T','I','M','S'),GF_PROP_PID_DECODER_CONFIG=GF_4CC('D','C','F','G'),
    GF_PROP_PID_DECODER_CONFIG_ENHANCEMENT=GF_4CC('E','C','F','G'),GF_PROP_PID_BITRATE=GF_4CC('P','B','R','T'),
    GF_PROP_PID_WIDTH=GF_4CC('P','W','D','T'),GF_PROP_PID_HEIGHT=GF_4CC('P','H','G','T'),
    GF_PROP_PID_SAR=GF_4CC('P','S','A','R'),GF_PROP_PID_FPS=GF_4CC('P','F','P','S'),
    GF_PROP_PID_TILE_BASE=GF_4CC('S','A','B','T'),GF_PROP_PID_CROP_POS=GF_4CC('P','C','P','S'),
    GF_PROP_PID_SRD=GF_4CC('P','S','R','D'),GF_PROP_PID_SAMPLE_RATE=GF_4CC('P','S','M','R'),
    GF_PROP_PID_NUM_CHANNELS=GF_4CC('P','N','C','H'),GF_PROP_PID_CHANNEL_LAYOUT=GF_4CC('P','C','H','L'),
    GF_PROP_PID_URL=GF_4CC('P','U','R','L'),GF_PROP_PID_FILEPATH=GF_4CC('P','F','P','T'),
    GF_PROP_PID_FILE_EXT=GF_4CC('P','F','E','X'),GF_PROP_PID_MIME=GF_4CC('P','M','I','M'),
    GF_PROP_PID_HAS_SYNC=GF_4CC('H','S','Y','N'),GF_PROP_PID_ISOM_STSD_ALL_TEMPLATES=GF_4CC('P','S','T','D'),
    GF_PROP_PID_ISOM_STSD_TEMPLATE=GF_4CC('P','S','T','E'),GF_PROP_PID_ISOM_SUBTYPE=GF_4CC('P','I','S','T'),
    GF_PROP_PID_TEMPLATE=GF_4CC('P','T','M','P'),GF_PROP_PID_LANGUAGE=GF_4CC('L','A','N','G'),
    GF_PROP_PID_INTERLACED=GF_4CC('P','I','N','T'),GF_PROP_PID_AS_COND_DESC=GF_4CC('P','A','S','C'),
    GF_PROP_PID_AS_ANY_DESC=GF_4CC('P','A','S','A'),GF_PROP_PID_REP_DESC=GF_4CC('P','R','P','D'),
    GF_PROP_PID_BASE_URL=GF_4CC('P','B','S','U'),GF_PROP_PID_ROLE=GF_4CC('P','R','O','L'),
    GF_PROP_PID_HLS_PLAYLIST=GF_4CC('P','H','L','S'),GF_PROP_PID_SINGLE_SCALE=GF_4CC('P','S','S','C'),
    GF_PROP_PID_START_NUMBER=GF_4CC('P','S','T','N'),GF_PROP_PID_CLAMP_DUR=GF_4CC('P','C','D','U'),
    GF_PROP_PID_DELAY=GF_4CC('P','D','L','Y'),GF_PROP_PID_DASH_CUE=GF_4CC('P','D','C','U'),
    GF_PROP_PID_DASH_FWD=GF_4CC('P','D','F','W'),GF_PROP_PID_XLINK=GF_4CC('P','X','L','N'),
    GF_PROP_PID_PERIOD_ID=GF_4CC('P','P','I','D'),GF_PROP_PID_PERIOD_DESC=GF_4CC('P','P','D','S'),
    GF_PROP_PID_PERIOD_START=GF_4CC('P','P','S','T'),GF_PROP_PID_PERIOD_DUR=GF_4CC('P','P','D','U'),
    GF_PROP_PID_MUX_SRC=GF_4CC('P','M','S','R'),GF_PROP_PID_IS_MANIFEST=GF_4CC('P','I','S','M'),
    GF_PROP_PID_PREMUX_STREAM_TYPE=GF_4CC('P','P','M','T'),GF_PROP_PID_LLHLS=GF_4CC('P','L','L','H'),
    GF_PROP_PID_REP_ID=GF_4CC('P','R','I','D'),GF_PROP_PID_DASH_DUR=GF_4CC('P','D','D','U'),
    GF_PROP_PCK_HLS_REF=GF_4CC('P','H','R','F'),
};

static GF_PropertyValue _pv_uint,_pv_str,_pv_frac,_pv_longuint;
#define PROP_UINT(v) (_pv_uint.type=GF_PROP_UINT,_pv_uint.value.uint=(v),&_pv_uint)
#define PROP_LONGUINT(v) (_pv_longuint.type=GF_PROP_LONGUINT,_pv_longuint.value.longuint=(v),&_pv_longuint)
#define PROP_STRING(v) (_pv_str.type=GF_PROP_STRING,_pv_str.value.string=(char*)(v),&_pv_str)
#define PROP_FRAC(v) (_pv_frac.type=GF_PROP_FRAC,_pv_frac.value.frac=(v),&_pv_frac)
#define DEFAULT_PERIOD_ID "_gf_dash_def_period"

typedef struct { Bool colour_description_present_flag; u8 colour_primaries,transfer_characteristic,matrix_coeffs,frame_mbs_only_flag; } HEVC_SPS;
typedef struct { HEVC_SPS sps[16]; s32 sps_active_idx; } HEVCState;
typedef HEVCState AVCState;
typedef struct { Bool interlaced_source_flag; } GF_HEVCConfig;
typedef struct { GF_List *sequenceParameterSets; } GF_AVCConfig;
typedef struct { u8 *data; u32 size; } GF_NALUFFParam;
typedef struct { struct { u8 acmod,lfon,nb_dep_sub,chan_loc; } streams[1]; Bool is_ec3; u8 complexity_index_type; } GF_AC3Config;

#ifdef __cplusplus
extern "C" {
#endif

void *gf_malloc(u32 size);
void gf_free(void *ptr);
char *gf_strdup(const char *str);
u32 gf_sys_clock(void);
u32 gf_crc_32(const void *buffer, u32 size);
void gf_assert(int);

GF_List *gf_list_new(void);
void gf_list_del(GF_List *l);
GF_Err gf_list_add(GF_List *l, void *item);
GF_Err gf_list_del_item(GF_List *l, void *item);
void *gf_list_get(GF_List *l, u32 item);
void *gf_list_last(GF_List *l);
u32 gf_list_count(GF_List *l);
s32 gf_list_find(GF_List *l, void *item);

const GF_PropertyValue *gf_filter_pid_get_property(GF_FilterPid *pid, u32 prop_4cc);
const GF_PropertyValue *gf_filter_pid_get_property_str(GF_FilterPid *pid, const char *name);
const GF_PropertyValue *gf_filter_pid_caps_query(GF_FilterPid *pid, u32 prop_4cc);
GF_Err gf_filter_pid_set_property(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *value);
void gf_filter_pid_copy_properties(GF_FilterPid *dst, GF_FilterPid *src);
void gf_filter_pid_set_name(GF_FilterPid *pid, const char *name);
const char *gf_filter_pid_get_name(GF_FilterPid *pid);
void *gf_filter_pid_get_udta(GF_FilterPid *pid);
void gf_filter_pid_set_udta(GF_FilterPid *pid, void *udta);
void gf_filter_pid_set_framing_mode(GF_FilterPid *pid, Bool framing);
void gf_filter_pid_disable_clone(GF_FilterPid *pid);
char *gf_filter_pid_get_destination(GF_FilterPid *pid);
void gf_filter_pid_set_discard(GF_FilterPid *pid, Bool discard);
void gf_filter_pid_discard_block(GF_FilterPid *pid);
void gf_filter_pid_remove(GF_FilterPid *pid);
GF_FilterPid *gf_filter_pid_new(GF_Filter *filter);
const char *gf_filter_pid_orig_src_args(GF_FilterPid *pid, Bool use_cache);
void gf_filter_pid_set_property_str(GF_FilterPid *pid, const char *name, const char *val);
void gf_filter_pid_send_event(GF_FilterPid *pid, GF_FilterEvent *evt);

void *gf_filter_get_udta(GF_Filter *filter);
GF_Filter *gf_filter_connect_destination(GF_Filter *filter, const char *dst_url, GF_Err *err);
void gf_filter_reset_source(GF_Filter *filter);
void gf_filter_set_source(GF_Filter *filter, GF_Filter *src, const char *name);
char gf_filter_get_sep(GF_Filter *filter, char sep_type);
void gf_filter_post_process_task(GF_Filter *filter);

GF_FileIO *gf_fileio_from_url(const char *url);
const char *gf_fileio_resource_url(GF_FileIO *gfio);
const char *gf_fileio_factory(GF_FileIO *gfio, const char *new_res_url);
const char *gf_file_basename(const char *filename);
char *gf_file_ext_start(const char *filename);
const char *gf_error_to_string(GF_Err e);

Bool gf_props_equal_strict(const GF_PropertyValue *a, const GF_PropertyValue *b);
void gf_props_reset_single(GF_PropertyValue *v);
GF_PropertyMap *gf_props_new(GF_Filter *filter);
GF_Err gf_props_set_property(GF_PropertyMap *map, u32 prop_4cc, const char *prop_name, char *dyn_name, const GF_PropertyValue *value);
GF_PropertyValue *gf_props_get_property(GF_PropertyMap *map, u32 prop_4cc, const char *name);
GF_PropertyMap *check_new_pid_props(GF_FilterPid *pid, Bool create);

GF_HEVCConfig *gf_odf_hevc_cfg_read(const u8 *data, u32 size, Bool is_lhvc);
void gf_odf_hevc_cfg_del(GF_HEVCConfig *cfg);
void gf_hevc_parse_ps(GF_HEVCConfig *cfg, HEVCState *hevc, u32 nalu_type);
GF_AVCConfig *gf_odf_avc_cfg_read(const u8 *data, u32 size);
void gf_odf_avc_cfg_del(GF_AVCConfig *cfg);
s32 gf_avc_read_sps(const u8 *data, u32 size, HEVCState *avc, u32 layer, u32 *nal_size);
GF_Err gf_odf_ac3_config_parse(const u8 *data, u32 size, Bool is_eac3, GF_AC3Config *ac3);
u32 gf_ac3_get_surround_channels(u8 acmod);
u32 gf_ac3_get_total_channels(u8 acmod);
u32 gf_eac3_get_chan_loc_count(u8 chan_loc);

static void dasher_update_bitrate(GF_DasherCtx *ctx, GF_DashStream *ds);
static void dasher_reset_stream(GF_Filter *filter, GF_DashStream *ds, Bool is_destroy);
static void dasher_check_outpath(GF_DasherCtx *ctx);
static GF_Err dasher_hls_setup_crypto(GF_DasherCtx *ctx, GF_DashStream *ds);
static void dasher_get_dash_dur(GF_DasherCtx *ctx, GF_DashStream *ds);
static void dasher_send_encode_hints(GF_DasherCtx *ctx, GF_DashStream *ds);
static GF_Err dasher_stream_period_changed(GF_Filter *filter, GF_DasherCtx *ctx, GF_DashStream *ds, Bool is_new_period_request);
static void dasher_update_rep(GF_DasherCtx *ctx, GF_DashStream *ds);
static GF_Err dasher_get_audio_info_with_m4a_sbr_ps(GF_DashStream *ds, const GF_PropertyValue *dsi, u32 *sr, u32 *ch);
static Bool dasher_template_use_source_url(const char *tpl);
static GF_Err dasher_setup_profile(GF_DasherCtx *ctx);
static GF_Err gf_mpd_load_cues(const char *f, u32 id, u32 *ts, Bool *ue, s32 *to, GF_DASHCueInfo **c, u32 *n);
static GF_Err gf_filter_pid_set_property_full(GF_FilterPid *pid, u32 prop_4cc, const char *pn, char *dn, const GF_PropertyValue *v, Bool is_info);

static GF_Err dasher_configure_pid(GF_Filter *filter, GF_FilterPid *pid, Bool is_remove)
{
	Bool period_switch = GF_FALSE;
	const GF_PropertyValue *p, *dsi=NULL;
	u32 dc_crc, dc_enh_crc;
	GF_Err e;
	GF_DashStream *ds;
	Bool old_period_switch;
	u32 prev_stream_type;
	Bool new_period_request = GF_FALSE;
	const char *cue_file=NULL;
	s64 old_clamp_dur = 0;
	GF_DasherCtx *ctx = gf_filter_get_udta(filter);

	if (is_remove) {
		ds = gf_filter_pid_get_udta(pid);
		if (ds) {
			if (ds->dyn_bitrate) dasher_update_bitrate(ctx, ds);
			gf_list_del_item(ctx->pids, ds);
			gf_list_del_item(ctx->current_period->streams, ds);
			if (ctx->next_period)
				gf_list_del_item(ctx->next_period->streams, ds);
			dasher_reset_stream(filter, ds, GF_TRUE);
			gf_free(ds);
		}
		return GF_OK;
	}
	ctx->check_connections = GF_TRUE;
	if (!ctx->opid && !ctx->gencues) {
		u32 i, nb_opids = ctx->dual ? 2 : 1;
		for (i=0; i < nb_opids; i++) {
			char *segext=NULL;
			char *force_ext=NULL;
			GF_FilterPid *opid=NULL;
			if (i==0) {
				ctx->opid = gf_filter_pid_new(filter);
				gf_filter_pid_set_name(ctx->opid, "MANIFEST");
				opid = ctx->opid;
			} else if (!ctx->alt_dst && (ctx->out_path || ctx->mname)) {
				char szSRC[100];
				GF_FileIO *gfio = NULL;
				char *mpath = ctx->out_path ? ctx->out_path : ctx->mname;
				u32 len;
				if (!strncmp(mpath, "gfio://", 7)) {
					gfio = gf_fileio_from_url(mpath);
					if (!gfio) return GF_BAD_PARAM;
					//only use basename as we will create the new resource through factory
					mpath = (char *) gf_file_basename(gf_fileio_resource_url(gfio));
					if (!mpath) return GF_OUT_OF_MEM;
				}

				len = (u32) strlen(mpath);
				char *out_path = gf_malloc(len+10);
				if (!out_path) return GF_OUT_OF_MEM;
				memcpy(out_path, mpath, len);
				out_path[len]=0;
				char *sep = gf_file_ext_start(out_path);
				if (sep) sep[0] = 0;
				if (ctx->do_m3u8) {
					strcat(out_path, ".mpd");
					force_ext = "mpd";
				} else {
					ctx->opid_alt_m3u8 = GF_TRUE;
					ctx->do_m3u8 = GF_TRUE;
					strcat(out_path, ".m3u8");
					force_ext = "m3u8";
				}
				if (gfio) {
					const char *rel = gf_fileio_factory(gfio, out_path);
					gf_free(out_path);
					out_path = gf_strdup(rel);
					if (!out_path) return GF_OUT_OF_MEM;
				}

				ctx->alt_dst = gf_filter_connect_destination(filter, out_path, &e);
				if (e) {
					GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[Dasher] Couldn't create secondary manifest output %s: %s\n", out_path, gf_error_to_string(e) ));
					gf_free(out_path);
					break;
				}
				gf_free(out_path);

				//reset any sourceID given in the dst_arg and assign sourceID to be the dasher filter
				gf_filter_reset_source(ctx->alt_dst);
				snprintf(szSRC, 100, "MuxSrc%cdasher_%p", gf_filter_get_sep(filter, GF_FS_SEP_NAME), ctx->alt_dst);
				gf_filter_set_source(ctx->alt_dst, filter, szSRC);

				ctx->opid_alt = gf_filter_pid_new(filter);
				gf_filter_pid_set_name(ctx->opid_alt, "MANIFEST_ALT");

				snprintf(szSRC, 100, "dasher_%p", ctx->alt_dst);
				gf_filter_pid_set_property(ctx->opid_alt, GF_PROP_PID_MUX_SRC, PROP_STRING(szSRC) );
				//we also need to set the property on main output just to avoid the connection
				snprintf(szSRC, 100, "dasher_%p", ctx);
				gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_MUX_SRC, PROP_STRING(szSRC) );
				opid = ctx->opid_alt;
			} else {
				GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[Dasher] Cannot guess output file name when explicitly loaded, disabling dual output mode."
					"\n\tUse --mname=URL to specify output location for alternate manifest\n"));
			}
			if (!opid)
				continue;

			//copy properties at init or reconfig
			gf_filter_pid_copy_properties(opid, pid);
			gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_DECODER_CONFIG_ENHANCEMENT, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_CODECID, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_UNFRAMED, NULL);
			gf_filter_pid_set_property(opid, GF_PROP_PID_STREAM_TYPE, PROP_UINT(GF_STREAM_FILE) );
			//for routeout
			gf_filter_pid_set_property(opid, GF_PROP_PID_PREMUX_STREAM_TYPE, PROP_UINT(GF_STREAM_FILE) );

			dasher_check_outpath(ctx);

			p = gf_filter_pid_caps_query(pid, GF_PROP_PID_FILE_EXT);
			if (p) {
				gf_filter_pid_set_property(opid, GF_PROP_PID_FILE_EXT, p );
				segext = p->value.string;
			} else {
				segext = NULL;
				if (ctx->out_path) {
					segext = gf_file_ext_start(ctx->out_path);
				} else if (ctx->mname) {
					segext = gf_file_ext_start(ctx->mname);
				}
				if (!segext) {
					if (!ctx->dual && ctx->do_m3u8) segext = "m3u8" ;
					else segext = i ? "m3u8" : "mpd";
				} else {
					segext++;
				}
				if (force_ext)
					segext = force_ext;
				gf_filter_pid_set_property(opid, GF_PROP_PID_FILE_EXT, PROP_STRING(segext) );

				if (ctx->explicit_mode) {
					//prevent the second pid from linking to another output in case of a graph such as
					// dasher:dual -o live.mpd
					//the explicit dasher will link mpd to mpd and will try to clone fout(live.mpd) for the manifest pid
					//since the default ext is * and cloning is enabled by default in implicit linking
					if (i)
						gf_filter_pid_disable_clone(opid);

					//override URL/path when loaded dynamically in case output filter(s) do not set a manifest name
					gf_filter_pid_set_property(opid, GF_PROP_PID_URL, ctx->out_path ? PROP_STRING(ctx->out_path) : NULL );
					gf_filter_pid_set_property(opid, GF_PROP_PID_FILEPATH, ctx->out_path ? PROP_STRING(ctx->out_path) : NULL );
				}

				if (!strcmp(segext, "m3u8")) {
					gf_filter_pid_set_property(opid, GF_PROP_PID_MIME, PROP_STRING("video/mpegurl"));
				} else if (!strcmp(segext, "ghi")) {
					gf_filter_pid_set_property(opid, GF_PROP_PID_MIME, PROP_STRING("application/x-gpac-ghi"));
				} else if (!strcmp(segext, "ghix")) {
					gf_filter_pid_set_property(opid, GF_PROP_PID_MIME, PROP_STRING("application/x-gpac-ghix"));
				} else {
					gf_filter_pid_set_property(opid, GF_PROP_PID_MIME, PROP_STRING("application/dash+xml"));
				}
			}

			u32 manifest_type = 0;
			if (!strcmp(segext, "m3u8")) {
				ctx->do_m3u8 = GF_TRUE;
				gf_filter_pid_set_name(opid, "manifest_m3u8" );
				manifest_type = 2;
			} else if (!strcmp(segext, "ghix") || !strcmp(segext, "ghi")) {
				ctx->do_index = !strcmp(segext, "ghix") ? 2 : 1;
				ctx->sigfrag = GF_FALSE;
				ctx->align = ctx->sap = GF_TRUE;
				ctx->sseg = ctx->sfile = ctx->tpl = GF_FALSE;
				if (ctx->state) {
					gf_free(ctx->state);
					ctx->state = NULL;
					GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[Dasher] Index generation mode, disabling state\n" ));
				}
				if (!ctx->template_str)
					ctx->template_str = gf_strdup("$RepresentationID$-$Number$$Init=init$");

				gf_filter_pid_set_name(opid, "dash_index" );
				manifest_type = 3;
			} else {
				ctx->do_mpd = GF_TRUE;
				gf_filter_pid_set_name(opid, "manifest_mpd" );
				manifest_type = 1;
			}
			gf_filter_pid_set_property(opid, GF_PROP_PID_IS_MANIFEST, PROP_UINT(manifest_type));
		}

		ctx->store_seg_states = GF_FALSE;
		//in m3u8 mode, always store all seg states. In MPD only if state, not ondemand
		if (((ctx->state || ctx->purge_segments) && !ctx->sseg) || ctx->do_m3u8) ctx->store_seg_states = GF_TRUE;
	}

	ds = gf_filter_pid_get_udta(pid);
	if (!ds) {
		GF_SAFEALLOC(ds, GF_DashStream);
		if (!ds) return GF_OUT_OF_MEM;
		ds->ipid = pid;
		gf_list_add(ctx->pids, ds);
		ds->complementary_streams = gf_list_new();
		period_switch = GF_TRUE;
		gf_filter_pid_set_udta(pid, ds);
		ds->sbound = ctx->sbound;
		ds->startNumber = 1;
		if (ctx->sbound!=DASHER_BOUNDS_OUT)
			ds->packet_queue = gf_list_new();

		/*initial connection and we already have sent play event, send a PLAY on this new PID
		TODO: we need to send STOP/PLAY depending on period
		*/
		if (ctx->is_playing) {
			GF_FilterEvent evt;

			dasher_send_encode_hints(ctx, ds);

			GF_FEVT_INIT(evt, GF_FEVT_PLAY, ds->ipid);
			evt.play.speed = 1.0;
			gf_filter_pid_send_event(ds->ipid, &evt);
		}
		//don't create pid at this time except in gencues mode

		if (ctx->gencues) {
			ds->opid = gf_filter_pid_new(filter);
			gf_filter_pid_copy_properties(ds->opid, pid);
			gf_filter_pid_set_property(ds->opid, GF_PROP_PID_DASH_CUE, PROP_STRING("inband") );
		}
	}

	gf_filter_pid_set_framing_mode(pid, GF_TRUE);

#define CHECK_PROP(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && (p->value.uint != _mem) && _mem) period_switch = GF_TRUE; \
	if (p) _mem = p->value.uint; \

#define CHECK_PROPL(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && (p->value.longuint != _mem) && _mem) period_switch = GF_TRUE; \
	if (p) _mem = p->value.longuint; \

#define CHECK_PROP_BOOL(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && (p->value.boolean != _mem) && _mem) period_switch = GF_TRUE; \
	if (p) _mem = p->value.uint; \

#define CHECK_PROP_FRAC(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && (p->value.frac.num * _mem.den != p->value.frac.den * _mem.num) && _mem.den && _mem.num) period_switch = GF_TRUE; \
	if (p) _mem = p->value.frac; \

#define CHECK_PROP_FRAC64(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && (p->value.lfrac.num * _mem.den != p->value.lfrac.den * _mem.num) && _mem.den && _mem.num) period_switch = GF_TRUE; \
	if (p) _mem = p->value.lfrac; \


#define CHECK_PROP_STR(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p && p->value.string && _mem && strcmp(_mem, p->value.string)) period_switch = GF_TRUE; \
	if (p) { \
		if (_mem) gf_free(_mem); \
		_mem = gf_strdup(p->value.string); \
	}\


#define CHECK_PROP_PROP(_type, _mem, _e) \
	p = gf_filter_pid_get_property(pid, _type); \
	if (!p && (_e<=0) ) return _e; \
	if (p != _mem) period_switch = GF_TRUE;\
	_mem = p; \


	prev_stream_type = ds->stream_type;
	CHECK_PROP(GF_PROP_PID_STREAM_TYPE, ds->stream_type, GF_NOT_SUPPORTED)

	if (ctx->sigfrag) {
		p = gf_filter_pid_get_property_str(pid, "nofrag");
		if (p && p->value.boolean) {
			p = gf_filter_pid_get_property(pid, GF_PROP_PID_URL);
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[IsoMedia] sigfrag requested but file %s is not fragmented\n", p->value.string));
			return GF_BAD_PARAM;
		}
	}

	ds->tile_base = GF_FALSE;

	if (ds->stream_type != GF_STREAM_FILE) {
		u32 prev_bitrate = ds->bitrate;
		if (ds->stream_type==GF_STREAM_ENCRYPTED) {
			CHECK_PROP(GF_PROP_PID_ORIG_STREAM_TYPE, ds->stream_type, GF_EOS)
			ds->is_encrypted = GF_TRUE;
		}
		if (prev_stream_type==ds->stream_type)
			period_switch = GF_FALSE;

		CHECK_PROP(GF_PROP_PID_BITRATE, ds->bitrate, GF_EOS)
		if (!ds->bitrate && prev_bitrate) {
			ds->bitrate = prev_bitrate;
			period_switch = GF_FALSE;
		}
		if (ds->bitrate && period_switch) {
			//allow 20% variation in bitrate, otherwise force period switch
			if ((ds->bitrate <= 120 * prev_bitrate / 100) && (ds->bitrate >= 80 * prev_bitrate / 100)) {
				period_switch = GF_FALSE;
			}
		}

		CHECK_PROP(GF_PROP_PID_CODECID, ds->codec_id, GF_NOT_SUPPORTED)
		CHECK_PROP(GF_PROP_PID_TIMESCALE, ds->timescale, GF_NOT_SUPPORTED)

		if (!ds->timescale) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[Dasher] Input PID %s has no timescale, cannot dash\n", gf_filter_pid_get_name(pid) ));
			return GF_NON_COMPLIANT_BITSTREAM;
		}

		if (ds->stream_type==GF_STREAM_VISUAL) {
			CHECK_PROP(GF_PROP_PID_WIDTH, ds->width, GF_EOS)
			CHECK_PROP(GF_PROP_PID_HEIGHT, ds->height, GF_EOS)
			//don't return if not defined
			CHECK_PROP_FRAC(GF_PROP_PID_SAR, ds->sar, GF_EOS)
			if (!ds->sar.num) ds->sar.num = ds->sar.den = 1;
			CHECK_PROP_FRAC(GF_PROP_PID_FPS, ds->fps, GF_EOS)


			p = gf_filter_pid_get_property(pid, GF_PROP_PID_TILE_BASE);
			if (p) {
				ds->srd.x = ds->srd.y = 0;
				ds->srd.z = ds->width;
				ds->srd.w = ds->height;
				ds->tile_base = GF_TRUE;
			} else {
				p = gf_filter_pid_get_property(pid, GF_PROP_PID_CROP_POS);
				if (p && ((p->value.vec2i.x != ds->srd.x) || (p->value.vec2i.y != ds->srd.y) ) ) period_switch = GF_TRUE;
				if (p) {
					ds->srd.x = p->value.vec2i.x;
					ds->srd.y = p->value.vec2i.y;
					ds->srd.z = ds->width;
					ds->srd.w = ds->height;
				} else {
					p = gf_filter_pid_get_property(pid, GF_PROP_PID_SRD);
					if (p && (
						(p->value.vec4i.x != ds->srd.x)
						|| (p->value.vec4i.y != ds->srd.y)
						|| (p->value.vec4i.z != ds->srd.z)
						|| (p->value.vec4i.w != ds->srd.w)
					) )
						period_switch = GF_TRUE;

					if (p) {
						ds->srd.x = p->value.vec4i.x;
						ds->srd.y = p->value.vec4i.y;
						ds->srd.z = p->value.vec4i.z;
						ds->srd.w = p->value.vec4i.w;
					}
				}
			}
		} else if (ds->stream_type==GF_STREAM_AUDIO) {
			CHECK_PROP(GF_PROP_PID_SAMPLE_RATE, ds->sr, GF_EOS)
			CHECK_PROP(GF_PROP_PID_NUM_CHANNELS, ds->nb_ch, GF_EOS)
			CHECK_PROPL(GF_PROP_PID_CHANNEL_LAYOUT, ds->ch_layout, GF_EOS)
		}

		old_period_switch = period_switch;

		//these ones can change without triggering period switch
		CHECK_PROP(GF_PROP_PID_NB_FRAMES, ds->nb_samples_in_source, GF_EOS)
		CHECK_PROP_FRAC64(GF_PROP_PID_DURATION, ds->duration, GF_EOS)
		CHECK_PROP_STR(GF_PROP_PID_URL, ds->src_url, GF_EOS)
		period_switch = old_period_switch;
		if (ds->duration.num<0) ds->duration.num = 0;

		CHECK_PROP(GF_PROP_PID_ID, ds->id, GF_EOS)
		CHECK_PROP(GF_PROP_PID_DEPENDENCY_ID, ds->dep_id, GF_EOS)

		p = gf_filter_pid_get_property(pid, GF_PROP_PID_HAS_SYNC);
		u32 sync_type = DASHER_SYNC_UNKNOWN;
		if (p) sync_type = p->value.boolean ? DASHER_SYNC_PRESENT : DASHER_SYNC_NONE;
		if ((sync_type != DASHER_SYNC_UNKNOWN) && (sync_type != ds->sync_points_type)) {
			period_switch = GF_TRUE;
			ds->sync_points_type = sync_type;
		}

		if (ds->inband_cues)
			period_switch = old_period_switch;

		if (ctx->scope_deps) {
			const char *src_args = gf_filter_pid_orig_src_args(pid, GF_TRUE);
			if (src_args) {
				ds->src_id = gf_crc_32(src_args, (u32) strlen(src_args));
			}
		}

		//check if we had up-front declarations of codec configs
		if (ctx->pswitch==DASHER_PSWITCH_STSD) {
			p = gf_filter_pid_get_property(pid, GF_PROP_PID_ISOM_STSD_ALL_TEMPLATES);
			if (p) {
				u32 all_stsd_crc = gf_crc_32(p->value.data.ptr, p->value.data.size);
				//same config, we assume the muxer dealt with this at setup, reset dsi crc to skip period switch test below
				if (all_stsd_crc==ds->all_stsd_crc) {
					ds->dsi_crc = 0;
					ds->dsi_enh_crc = 0;
				} else {
					ds->all_stsd_crc = all_stsd_crc;
				}
			} else {
				ds->all_stsd_crc = 0;
			}
		}

		dc_crc = 0;
		dsi = p = gf_filter_pid_get_property(pid, GF_PROP_PID_DECODER_CONFIG);
		if (p && (p->type==GF_PROP_DATA))
			dc_crc = gf_crc_32(p->value.data.ptr, p->value.data.size);

		dc_enh_crc = 0;
		p = gf_filter_pid_get_property(pid, GF_PROP_PID_DECODER_CONFIG_ENHANCEMENT);
		if (p && (p->type==GF_PROP_DATA)) dc_enh_crc = gf_crc_32(p->value.data.ptr, p->value.data.size);

		if (((dc_crc != ds->dsi_crc) && ds->dsi_crc)
			|| ((dc_enh_crc != ds->dsi_enh_crc) && ds->dsi_enh_crc)
		) {
			//check which codecs can support inband param sets
			switch (ds->codec_id) {
			case GF_CODECID_AVC:
			case GF_CODECID_SVC:
			case GF_CODECID_MVC:
			case GF_CODECID_HEVC:
			case GF_CODECID_LHVC:
				if (!ctx->bs_switch)
					period_switch = GF_TRUE;
				break;
			default:
				period_switch = GF_TRUE;
				break;
			}
		}
		//check if input is ready
		ds->dcd_not_ready = 0;
		if (!dc_crc && !dc_enh_crc) {
			switch (ds->codec_id) {
			case GF_CODECID_AVC:
			case GF_CODECID_SVC:
			case GF_CODECID_MVC:
			case GF_CODECID_HEVC:
			case GF_CODECID_LHVC:
			case GF_CODECID_AAC_MPEG4:
			case GF_CODECID_AAC_MPEG2_MP:
			case GF_CODECID_AAC_MPEG2_LCP:
			case GF_CODECID_AAC_MPEG2_SSRP:
			case GF_CODECID_USAC:
			case GF_CODECID_AC3:
			case GF_CODECID_EAC3:
			case GF_CODECID_AV1:
			case GF_CODECID_VP8:
			case GF_CODECID_VP9:
				ds->dcd_not_ready = gf_sys_clock();
				break;
			default:
				break;
			}
		}
		ds->dsi_crc = dc_crc;

		CHECK_PROP_STR(GF_PROP_PID_TEMPLATE, ds->template_str, GF_EOS)
		CHECK_PROP_STR(GF_PROP_PID_LANGUAGE, ds->lang, GF_EOS)
		CHECK_PROP_BOOL(GF_PROP_PID_INTERLACED, ds->interlaced, GF_EOS)
		CHECK_PROP_PROP(GF_PROP_PID_AS_COND_DESC, ds->p_as_desc, GF_EOS)
		CHECK_PROP_PROP(GF_PROP_PID_AS_ANY_DESC, ds->p_as_any_desc, GF_EOS)
		CHECK_PROP_PROP(GF_PROP_PID_REP_DESC, ds->p_rep_desc, GF_EOS)
		CHECK_PROP_PROP(GF_PROP_PID_BASE_URL, ds->p_base_url, GF_EOS)
		CHECK_PROP_PROP(GF_PROP_PID_ROLE, ds->p_role, GF_EOS)
		CHECK_PROP_STR(GF_PROP_PID_HLS_PLAYLIST, ds->hls_vp_name, GF_EOS)
		CHECK_PROP_BOOL(GF_PROP_PID_SINGLE_SCALE, ds->sscale, GF_EOS)

		//if manifest generation mode with template_str and no template_str at PID or filter level, switch to main profile
		if (ctx->sigfrag && ctx->tpl && !ctx->template_str && !ds->template_str) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[Dasher] Warning, manifest generation only mode requested for live-based profile but no template_str provided, switching to main profile.\n"));
			ctx->profile = GF_DASH_PROFILE_MAIN;
			ctx->tpl = GF_FALSE;
			dasher_setup_profile(ctx);
			//we force single file in this mode, but we will replace byte ranges by source URL
			ctx->sfile = GF_TRUE;
		}

		if (ds->rate_first_dts_plus_one)
			dasher_update_bitrate(ctx, ds);

		if (!ds->bitrate) {
			char *tpl = ds->template_str ? ds->template_str : ctx->template_str;
			if (tpl && strstr(tpl, "$Bandwidth$")) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[Dasher] No bitrate property assigned to PID %s but template_str uses $Bandwidth$, cannot initialize !\n\tTry specifying bitrate property after your source, e.g. -i source.raw:#Bitrate=VAL\n", gf_filter_pid_get_name(ds->ipid)));
				ctx->in_error = GF_TRUE;
				return GF_BAD_PARAM;
			} else {
				GF_LOG(GF_LOG_INFO, GF_LOG_DASH, ("[Dasher] No bitrate property assigned to PID %s, computing from bitstream\n", gf_filter_pid_get_name(ds->ipid)));
				ds->dyn_bitrate = GF_TRUE;
				ds->rate_first_dts_plus_one = 0;
				ds->rate_media_size = 0;
			}
		} else {
			ds->dyn_bitrate = GF_FALSE;
		}

		if (!ds->src_url)
			ds->src_url = gf_strdup("file");

		CHECK_PROP(GF_PROP_PID_START_NUMBER, ds->startNumber, GF_EOS)

		ds->no_seg_dur = ctx->no_seg_dur;
		dasher_get_dash_dur(ctx, ds);

		ds->splitable = GF_FALSE;
		ds->is_av = GF_FALSE;
		switch (ds->stream_type) {
		case GF_STREAM_TEXT:
		case GF_STREAM_METADATA:
		case GF_STREAM_OD:
		case GF_STREAM_SCENE:
			ds->splitable = ctx->split;
			break;
		case GF_STREAM_VISUAL:
		case GF_STREAM_AUDIO:
			ds->is_av = GF_TRUE;
			break;
		}

		old_clamp_dur = ds->clamped_dur.num;
		ds->clamped_dur.num = 0;
		ds->clamped_dur.den = 1;
		p = gf_filter_pid_get_property(pid, GF_PROP_PID_CLAMP_DUR);
		if (p && p->value.lfrac.den) ds->clamped_dur = p->value.lfrac;

		//HDR
#if !defined(GPAC_DISABLE_AV_PARSERS)
		if (dsi) {
			if (ds->codec_id == GF_CODECID_LHVC || ds->codec_id == GF_CODECID_HEVC_TILES || ds->codec_id == GF_CODECID_HEVC) {
				GF_HEVCConfig* hevccfg = gf_odf_hevc_cfg_read(dsi->value.data.ptr, dsi->value.data.size, GF_FALSE);
				if (hevccfg) {
					Bool is_interlaced;
					HEVCState hevc;
					HEVC_SPS* sps;
					memset(&hevc, 0, sizeof(HEVCState));
					gf_hevc_parse_ps(hevccfg, &hevc, GF_HEVC_NALU_VID_PARAM);
					gf_hevc_parse_ps(hevccfg, &hevc, GF_HEVC_NALU_SEQ_PARAM);
					sps = &hevc.sps[hevc.sps_active_idx];
					if (sps && sps->colour_description_present_flag) {
						DasherHDRType old_hdr_type = ds->hdr_type;
						if (sps->colour_primaries == 9 && sps->matrix_coeffs == 9) {
							if (sps->transfer_characteristic == 14) ds->hdr_type = DASHER_HDR_HLG; //TODO: parse alternative_transfer_characteristics SEI
							if (sps->transfer_characteristic == 16) ds->hdr_type = DASHER_HDR_PQ10;
						}
						if (old_hdr_type != ds->hdr_type) period_switch = GF_TRUE;
					}
					is_interlaced = hevccfg->interlaced_source_flag ? GF_TRUE : GF_FALSE;
					if (ds->interlaced != is_interlaced) period_switch = GF_TRUE;
					ds->interlaced = is_interlaced;

					gf_odf_hevc_cfg_del(hevccfg);
				}
			}
			else if (ds->codec_id == GF_CODECID_AVC || ds->codec_id == GF_CODECID_SVC || ds->codec_id == GF_CODECID_MVC) {
				AVCState avc;
				GF_AVCConfig* avccfg = gf_odf_avc_cfg_read(dsi->value.data.ptr, dsi->value.data.size);
				if (avccfg) {
					GF_NALUFFParam *sl = (GF_NALUFFParam *)gf_list_get(avccfg->sequenceParameterSets, 0);
					if (sl) {
						s32 idx;
						memset(&avc, 0, sizeof(AVCState));
						idx = gf_avc_read_sps(sl->data, sl->size, &avc, 0, NULL);
						if (idx>=0) {
							Bool is_interlaced = avc.sps[idx].frame_mbs_only_flag ? GF_FALSE : GF_TRUE;
							if (ds->interlaced != is_interlaced) period_switch = GF_TRUE;
							ds->interlaced = is_interlaced;
						}
					}
					gf_odf_avc_cfg_del(avccfg);
				}
			}
		}
#endif /*!GPAC_DISABLE_AV_PARSERS*/

		if (ds->stream_type==GF_STREAM_AUDIO) {
			u32 _sr=0, _nb_ch=0;
#ifndef GPAC_DISABLE_AV_PARSERS
			switch (ds->codec_id) {
			case GF_CODECID_AAC_MPEG4:
			case GF_CODECID_AAC_MPEG2_MP:
			case GF_CODECID_AAC_MPEG2_LCP:
			case GF_CODECID_AAC_MPEG2_SSRP:
			case GF_CODECID_USAC:
				//DASH-IF and MPEG disagree here:
				if ((ctx->profile == GF_DASH_PROFILE_AVC264_LIVE)
					|| (ctx->profile == GF_DASH_PROFILE_AVC264_ONDEMAND)
					|| (ctx->profile == GF_DASH_PROFILE_DASHIF_LL)
				) {
					GF_Err res = dasher_get_audio_info_with_m4a_sbr_ps(ds, dsi, &_sr, &_nb_ch);
					if (res) {
						//DASH-IF IOP 3.3 mandates the SBR/PS info
						GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[Dasher] Could not get AAC info, %s\n", gf_error_to_string(res)));
					}
				} else if (dsi) {
					dasher_get_audio_info_with_m4a_sbr_ps(ds, dsi, NULL, &_nb_ch);
				}
				break;
			case GF_CODECID_AC3:
			case GF_CODECID_EAC3:
				if (dsi) {
					GF_AC3Config ac3;
					gf_odf_ac3_config_parse(dsi->value.data.ptr, dsi->value.data.size, (ds->codec_id==GF_CODECID_EAC3) ? GF_TRUE : GF_FALSE, &ac3);

					ds->nb_lfe = ac3.streams[0].lfon ? 1 : 0;
					ds->nb_surround = gf_ac3_get_surround_channels(ac3.streams[0].acmod);
					ds->atmos_complexity_type = ac3.is_ec3 ? ac3.complexity_index_type : 0;
					_nb_ch = gf_ac3_get_total_channels(ac3.streams[0].acmod);
					if (ac3.streams[0].nb_dep_sub) {
						_nb_ch += gf_eac3_get_chan_loc_count(ac3.streams[0].chan_loc);
					}
                    if (ds->nb_lfe) _nb_ch++;
				}
				break;
			}
#endif
			if (_sr > ds->sr) ds->sr = _sr;
			if (_nb_ch > ds->nb_ch) ds->nb_ch = _nb_ch;
		}


		ds->pts_minus_cts = 0;
		p = gf_filter_pid_get_property(ds->ipid, GF_PROP_PID_DELAY);
		if (p && p->value.longsint) {
			ds->pts_minus_cts = p->value.longsint;
		}

		//only reload queues if we detected a period switch
		if (period_switch) {
			cue_file = ctx->cues;
			if (!cue_file || strcmp(cue_file, "none") ) {
				p = gf_filter_pid_get_property(pid, GF_PROP_PID_DASH_CUE);
				if (p) cue_file = p->value.string;
			}

			if (ds->cues) gf_free(ds->cues);
			ds->cues = NULL;
			ds->nb_cues = 0;
			ds->inband_cues = GF_FALSE;
			if (cue_file) {
				if (!strcmp(cue_file, "inband")) {
					ds->inband_cues = GF_TRUE;
					//if manifest generation mode, do not setup dash forward mode
					if (!ctx->sigfrag) {
						p = gf_filter_pid_get_property(pid, GF_PROP_PID_DASH_FWD);
						if (p && p->value.uint)
							ctx->forward_mode = p->value.uint;
					}
				} else if (!strcmp(cue_file, "idx_all")) {
					ds->inband_cues = GF_TRUE;
					ctx->from_index = IDXMODE_ALL;
				} else if (!strcmp(cue_file, "idx_man")) {
					ds->inband_cues = GF_TRUE;
					ctx->from_index = IDXMODE_MANIFEST;
				} else if (!strcmp(cue_file, "idx_init")) {
					ds->inband_cues = GF_TRUE;
					ctx->from_index = IDXMODE_INIT;
				} else if (!strcmp(cue_file, "idx_child")) {
					ds->inband_cues = GF_TRUE;
					ctx->from_index = IDXMODE_CHILD;
				} else if (!strcmp(cue_file, "idx_seg")) {
					ds->inband_cues = GF_TRUE;
					ctx->from_index = IDXMODE_SEG;
				} else if (strcmp(cue_file, "none")) {
					e = gf_mpd_load_cues(cue_file, ds->id, &ds->cues_timescale, &ds->cues_use_edits, &ds->cues_ts_offset, &ds->cues, &ds->nb_cues);
					if (e) return e;
					if (!ds->cues_timescale)
						ds->cues_timescale = ds->timescale;
				}


				if (ctx->from_index==IDXMODE_CHILD) {
					p = gf_filter_pid_get_property_str(ds->ipid, "idx_out");
					if (p) {
						if (ds->hls_vp_name) gf_free(ds->hls_vp_name);
						ds->hls_vp_name = gf_strdup(p->value.string);
					}
				}

			}
		}
	} else {

		p = gf_filter_pid_get_property(pid, GF_PROP_PID_URL);
		if (!p) p = gf_filter_pid_get_property(pid, GF_PROP_PID_FILEPATH);
		if (p) return GF_NOT_SUPPORTED;

		CHECK_PROP_STR(GF_PROP_PID_XLINK, ds->xlink, GF_EOS)
	}


	if (ctx->do_index || ctx->from_index) {
		if (!ds->template_str && ctx->def_template) {
			p = gf_filter_pid_get_property_str(ds->ipid, "idx_template");
			if (p) {
				ds->template_str = gf_strdup(p->value.string);
				GF_LOG(GF_LOG_INFO, GF_LOG_DASH, ("[Dasher] Using template_str from index pass %s\n", ds->template_str));
			}
		}
		char *template_str = ds->template_str;

		if (!ds->template_str) {
			if ((ctx->def_template==1) && ctx->do_index) {
				gf_free(ctx->template_str);
				ctx->template_str = gf_strdup("$RepresentationID$-$Number$$Init=init$");
				ctx->def_template = 2;
				GF_LOG(GF_LOG_INFO, GF_LOG_DASH, ("[Dasher] No template_str assigned in index mode, using %s\n", ctx->template_str));
			}
			template_str = ctx->template_str;
		}

		if (dasher_template_use_source_url(template_str)) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[Dasher] Cannot use file-based templates with index mode\n"));
			return GF_BAD_PARAM;
		}
	}

	//stream representation was not yet setup but is scheduled for this period, do not trigger period switch
	//this typically happens when we post-poned representation setup waiting for the decoder config
	if (!ds->rep && (gf_list_find(ctx->current_period->streams, ds)>=0))
		period_switch = GF_FALSE;

	old_period_switch = period_switch;
	period_switch = GF_FALSE;
	CHECK_PROP_STR(GF_PROP_PID_PERIOD_ID, ds->period_id, GF_EOS)
	CHECK_PROP_PROP(GF_PROP_PID_PERIOD_DESC, ds->p_period_desc, GF_EOS)
	if (!period_switch && (ctx->pswitch==DASHER_PSWITCH_FORCE))
		period_switch = GF_TRUE;

	if (gf_filter_pid_get_property_str(pid, "period_switch"))
		period_switch = GF_TRUE;

	p = gf_filter_pid_get_property(pid, GF_PROP_PID_PERIOD_START);
	if (p && p->value.lfrac.den) {
		if (ds->period_start.num * p->value.lfrac.den != p->value.lfrac.num * ds->period_start.den) period_switch = GF_TRUE;
		ds->period_start = p->value.lfrac;
	} else {
		if (ds->period_start.num) period_switch = GF_TRUE;
		ds->period_start.num = 0;
		ds->period_start.den = 1000;
	}
	gf_assert(ds->period_start.den);

	if (period_switch) {
		new_period_request = GF_TRUE;
	} else {
		period_switch = old_period_switch;
	}

	if (ds->period_continuity_id) gf_free(ds->period_continuity_id);
	ds->period_continuity_id = NULL;
	p = gf_filter_pid_get_property_str(ds->ipid, "period_resume");
	if (!ctx->mpd || (gf_list_find(ctx->mpd->periods, ds->last_period)<0))
		ds->last_period = NULL;

	if (p && p->value.string && ds->last_period) {
		if (!ds->last_period->ID) {
			if (p->value.string[0]) {
				ds->last_period->ID = p->value.string;
			} else {
				char szPName[50];
				sprintf(szPName, "P%d", 1 + gf_list_find(ctx->mpd->periods, ds->last_period));
				ds->last_period->ID = gf_strdup(szPName);
			}
		}
		if (ds->set && (ds->set->id<0)) {
			//period may be NULL (no longer scheduled)
			if (!ds->as_id && ds->period && ds->period->period)
				ds->as_id = gf_list_find(ds->period->period->adaptation_sets, ds->set) + 1;
			ds->set->id = ds->as_id;
		}
		ds->period_continuity_id = gf_strdup(ds->last_period->ID);
	}
	ds->last_period = NULL;

	ds->period_dur.num = 0;
	ds->period_dur.den = 1;
	p = gf_filter_pid_get_property(pid, GF_PROP_PID_PERIOD_DUR);
	if (p) ds->period_dur = p->value.lfrac;

	p = gf_filter_pid_get_property_str(pid, "max_seg_dur");
	ctx->index_max_seg_dur = p ? p->value.uint : 0;
	p = gf_filter_pid_get_property_str(pid, "mpd_duration");
	ctx->index_media_duration = p ? p->value.longuint : 0;

	if (ds->stream_type==GF_STREAM_FILE) {
		if (!ds->xlink && !ds->period_start.num && !ds->period_dur.num) {
			ds->done = 1;
			GF_LOG(GF_LOG_WARNING, GF_LOG_DASH, ("[Dasher] null PID specified without any XLINK/start/duration, ignoring\n"));
		} else if (ds->xlink) {
			ctx->use_xlink = GF_TRUE;
		}
	} else {
		if (ds->xlink) gf_free(ds->xlink);
		ds->xlink = NULL;
		CHECK_PROP_STR(GF_PROP_PID_XLINK, ds->xlink, GF_EOS)
		if (ds->xlink)
			ctx->use_xlink = GF_TRUE;
	}

	//input was done due to clamp but forced to new period, reschedule
	if (new_period_request && ds->done && old_clamp_dur) {
		gf_list_del_item(ctx->next_period->streams, ds);
		//reset discard, blocking mode on output (set by EOS) and reset dasher EOS state
		gf_filter_pid_set_discard(ds->ipid, GF_FALSE);
		if (ds->opid && !ctx->gencues) {
			gf_filter_pid_discard_block(ds->opid);
			gf_filter_pid_remove(ds->opid);
			ds->opid = NULL;
		}
		if (ctx->is_eos) {
			ctx->is_eos = GF_FALSE;
			gf_filter_pid_discard_block(ctx->opid);
			if (ctx->opid_alt)
			gf_filter_pid_discard_block(ctx->opid_alt);
		}
		ds->rep_init = GF_FALSE;
		ds->presentation_time_offset = 0;
		ds->rep = NULL;
		ds->set = NULL;
		ds->period = NULL;
		ds->done = 0;
//		gf_filter_post_process_task(filter);
//		dasher_reset_stream(filter, ds, GF_FALSE);
	}

	//our stream is already scheduled for next period, don't do anything
	if (gf_list_find(ctx->next_period->streams, ds)>=0)
		period_switch = GF_FALSE;

	//assign default ID
	if (!ds->period_id)
		ds->period_id = gf_strdup(DEFAULT_PERIOD_ID);

	e = dasher_hls_setup_crypto(ctx, ds);
	if (e) return e;

	if (!period_switch) {
		if (ds->opid) {
			gf_filter_pid_copy_properties(ds->opid, pid);
			//for route out
			if (ctx->do_m3u8)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PCK_HLS_REF, PROP_LONGUINT( ds->hls_ref_id ) );
			if (ctx->llhls)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PID_LLHLS, PROP_UINT(ctx->llhls) );
			if (ds->rep && ds->rep->segment_template)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PID_TEMPLATE, PROP_STRING(ds->rep->segment_template->media));
			else if (ds->set && ds->set->segment_template)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PID_TEMPLATE, PROP_STRING(ds->set->segment_template->media));
			if (ctx->do_m3u8)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PCK_HLS_REF, PROP_LONGUINT( ds->hls_ref_id ) );
			gf_filter_pid_set_property(ds->opid, GF_PROP_PID_REP_ID, PROP_STRING( ds->rep_id ) );
			gf_filter_pid_set_property(ds->opid, GF_PROP_PID_DASH_DUR, PROP_FRAC( ds->dash_dur ) );
			gf_filter_pid_set_property(ds->opid, GF_PROP_PID_PREMUX_STREAM_TYPE, PROP_UINT(ds->stream_type) );
			//end route
			if (ctx->gencues)
				gf_filter_pid_set_property(ds->opid, GF_PROP_PID_DASH_CUE, PROP_STRING("inband") );
		}
		if (ds->rep)
			dasher_update_rep(ctx, ds);
		return GF_OK;
	}
	//period switch !

	//we have queued packets (sbound modes), we cannot switch period for this stream now, force queue flush
	if (gf_list_count(ds->packet_queue)) {
		ds->request_period_switch = new_period_request ? 2 : 1;
		return GF_OK;
	}
	//done for this stream
	return dasher_stream_period_changed(filter, ctx, ds, new_period_request);
}

GF_EXPORT
GF_Err gf_filter_pid_set_property(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *value)
{
	if (!prop_4cc) return GF_BAD_PARAM;
	return gf_filter_pid_set_property_full(pid, prop_4cc, NULL, NULL, value, GF_FALSE);
}

static GF_Err gf_filter_pid_set_property_full(GF_FilterPid *pid, u32 prop_4cc, const char *prop_name, char *dyn_name, const GF_PropertyValue *value, Bool is_info)
{
	GF_PropertyMap *map;
	const GF_PropertyValue *oldp;
	if (PID_IS_INPUT(pid)) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Attempt to write property on input PID in filter %s - ignoring\n", pid->filter->name ? pid->filter->name : pid->filter->freg->name));
		return GF_BAD_PARAM;
	}

	if (prop_4cc) {
		oldp = gf_filter_pid_get_property(pid, prop_4cc);
	} else {
		oldp = gf_filter_pid_get_property_str(pid, prop_name ? prop_name : dyn_name);
	}
	if (!oldp && !value)
		return GF_OK;
	if (oldp && value) {
		if (gf_props_equal_strict(oldp, value)) {
			if (value->type==GF_PROP_DATA_NO_COPY) gf_free(value->value.data.ptr);
			else if (value->type==GF_PROP_STRING_NO_COPY) gf_free(value->value.string);
			else if (value->type==GF_PROP_STRING_LIST) gf_props_reset_single((GF_PropertyValue *) value);
			return GF_OK;
		}
	}

	//info property, do not request a new property map
	if (is_info) {
		map = pid->infos;
		if (!map) {
			map = pid->infos = gf_props_new(pid->filter);
		}
		pid->pid_info_changed = GF_TRUE;
	} else {
		//always merge properties
		map = check_new_pid_props(pid, GF_TRUE);
	}
	if (!map) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_FILTER, ("No properties for destination pid in filter %s, ignoring reset\n", pid->filter->name));
		return GF_OUT_OF_MEM;
	}
	if (value && (prop_4cc==GF_PROP_PID_TIMESCALE))
		map->timescale = value->value.uint;

	//if change of codecid or streamtype, remove ISOBMFF templates and subtype for codec
	if (oldp && value) {
		u32 reset=0;
		if (prop_4cc == GF_PROP_PID_CODECID) {
			reset = 2;
		} else if (prop_4cc == GF_PROP_PID_STREAM_TYPE) {
			if ((oldp->value.uint==GF_STREAM_ENCRYPTED) || (value->value.uint==GF_STREAM_ENCRYPTED))
				reset = 1;
		}
		if (reset) {
			gf_props_set_property(map, GF_PROP_PID_ISOM_STSD_ALL_TEMPLATES, NULL, NULL, NULL);
			if (reset==2) {
				gf_props_set_property(map, GF_PROP_PID_ISOM_STSD_TEMPLATE, NULL, NULL, NULL);
				gf_props_set_property(map, GF_PROP_PID_ISOM_SUBTYPE, NULL, NULL, NULL);
			}
		}
	}

	if (value && (prop_4cc == GF_PROP_PID_ID) && !pid->name) {
		char szName[100];
		sprintf(szName, "PID%d", value->value.uint);
		gf_filter_pid_set_name(pid, szName);
	}
	return gf_props_set_property(map, prop_4cc, prop_name, dyn_name, value);
}

GF_EXPORT
const GF_PropertyValue *gf_filter_pid_caps_query(GF_FilterPid *pid, u32 prop_4cc)
{
	u32 i;
	GF_PropertyMap *map = pid->pid->caps_negotiate;
	if (PID_IS_INPUT(pid)) {
		u32 k;
		GF_Filter *dst = pid->filter->cap_dst_filter;
		//the first entry in destination filters may be the final destination and won't hold any caps query
		//we therefore use the last entry which points to the next filter in the chain
		if (!dst) dst = gf_list_last(pid->filter->destination_filters);
		if (!dst) dst = gf_list_get(pid->filter->destination_links, 0);

		if (!dst || (dst->cap_idx_at_resolution<0) ) {
			GF_LOG(GF_LOG_INFO, GF_LOG_FILTER, ("Reconfig caps query on input PID %s in filter %s with no destination filter set\n", pid->pid->name, pid->filter->name));
			return NULL;
		}
		for (k=dst->cap_idx_at_resolution; k<dst->freg->nb_caps; k++) {
			const GF_FilterCapability *cap = &dst->freg->caps[k];
			if (!(cap->flags & GF_CAPFLAG_IN_BUNDLE)) return NULL;

			if (!(cap->flags & GF_CAPFLAG_INPUT)) continue;
			if (cap->flags & GF_CAPFLAG_OPTIONAL) continue;
			if (cap->code == prop_4cc) return &cap->val;
		}
		return NULL;
	}
	if (map) return gf_props_get_property(map, prop_4cc, NULL);
	for (i=0; i<pid->num_destinations; i++) {
		u32 j;
		GF_FilterPidInst *pidi = gf_list_get(pid->destinations, i);
		for (j=0; j<pidi->filter->nb_forced_caps; j++) {
			if (pidi->filter->forced_caps[j].code==prop_4cc)
				return &pidi->filter->forced_caps[j].val;
		}
		//walk up the chain
		for (j=0; j<pidi->filter->num_output_pids; j++) {
			GF_FilterPid *apid = gf_list_get(pidi->filter->output_pids, j);
			if (apid) {
				const GF_PropertyValue *p = gf_filter_pid_caps_query(apid, prop_4cc);
				if (p) return p;
			}
		}

	}

	//trick here: we may not be connected yet (called during a configure_pid), use the target destination
	//of the filter as caps source
	if (gf_list_count(pid->filter->destination_filters) ) {
		GF_Filter *a_filter = gf_list_get(pid->filter->destination_filters, 0);
		while (a_filter) {
			for (i=0; i<a_filter->nb_forced_caps; i++) {
				if (a_filter->forced_caps[i].code==prop_4cc)
					return &a_filter->forced_caps[i].val;
			}
			a_filter = gf_list_get(a_filter->destination_filters, 0);
		}
	}

	//second trick here: we may not be connected yet (called during a configure_pid), use the target destination
	//of the filter as caps source
	if (pid->filter->cap_dst_filter) {
		GF_Filter *a_filter = pid->filter->cap_dst_filter;
		for (i=0; i<a_filter->nb_forced_caps; i++) {
			if (a_filter->forced_caps[i].code==prop_4cc)
				return &a_filter->forced_caps[i].val;
		}
		//not found, check if dst filter is alread linked to a dest - may happen when loading muxes with different chain length:
		//-i obu -i mp4a -o file.ts
		//the link fin->mp4dmx->m2tsmx->file.ts is solved before fin->rfav1->ufobu->m2tsmx->ts
		a_filter = a_filter->dst_filter;
		while (a_filter) {
			for (i=0; i<a_filter->nb_forced_caps; i++) {
				if (a_filter->forced_caps[i].code==prop_4cc)
					return &a_filter->forced_caps[i].val;
			}
			a_filter = a_filter->dst_filter;
		}
	}

	return NULL;
}

GF_EXPORT
char* gf_file_ext_start(const char* filename)
{
	char* basename;

	if (filename && !strncmp(filename, "gfio://", 7)) {
		GF_FileIO *gfio = gf_fileio_from_url(filename);
		filename = gf_fileio_resource_url(gfio);
	}
	basename = gf_file_basename(filename);

	if (basename) {
		char *ext = strrchr(basename, '.');
		if (ext && !strcmp(ext, ".gz")) {
			ext[0] = 0;
			char *ext2 = strrchr(basename, '.');
			ext[0] = '.';
			if (ext2) return ext2;
		}
		return ext;
	}
	return NULL;
}
