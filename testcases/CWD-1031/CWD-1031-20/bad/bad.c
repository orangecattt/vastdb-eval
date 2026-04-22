#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;

typedef enum {
    GF_FALSE = 0,
    GF_TRUE
} Bool;

typedef struct { s32 num; u32 den; } GF_Fraction;
typedef struct { s64 num; u64 den; } GF_Fraction64;
typedef double Double;

#define ABS(a) (((a) > 0) ? (a) : -(a))
#define LLU "llu"

typedef enum {
    GF_OK = 0,
    GF_BAD_PARAM = -1,
    GF_OUT_OF_MEM = -2,
    GF_IO_ERR = -3,
    GF_NOT_SUPPORTED = -4,
    GF_CORRUPTED_DATA = -5,
    GF_SG_UNKNOWN_NODE = -6,
    GF_SG_INVALID_PROTO = -7,
    GF_SCRIPT_ERROR = -8,
    GF_BUFFER_TOO_SMALL = -9,
    GF_NON_COMPLIANT_BITSTREAM = -10,
    GF_FILTER_NOT_FOUND = -11,
    GF_URL_ERROR = -12,
    GF_SERVICE_ERROR = -13,
    GF_REMOTE_SERVICE_ERROR = -14,
    GF_STREAM_NOT_FOUND = -15,
    GF_URL_REMOVED = -16,
    GF_ISOM_INVALID_FILE = -20,
    GF_ISOM_INCOMPLETE_FILE = -21,
    GF_ISOM_INVALID_MEDIA = -22,
    GF_ISOM_INVALID_MODE = -23,
    GF_ISOM_UNKNOWN_DATA_REF = -24,
    GF_ODF_INVALID_DESCRIPTOR = -30,
    GF_ODF_FORBIDDEN_DESCRIPTOR = -31,
    GF_ODF_INVALID_COMMAND = -32,
    GF_BIFS_UNKNOWN_VERSION = -33,
    GF_IP_ADDRESS_NOT_FOUND = -40,
    GF_IP_CONNECTION_FAILURE = -41,
    GF_IP_NETWORK_FAILURE = -42,
    GF_IP_CONNECTION_CLOSED = -43,
    GF_IP_NETWORK_EMPTY = -44,
    GF_IP_SOCK_WOULD_BLOCK = -45,
    GF_IP_UDP_TIMEOUT = -46,
    GF_AUTHENTICATION_FAILURE = -50,
    GF_SCRIPT_NOT_READY = -51,
    GF_INVALID_CONFIGURATION = -52,
    GF_NOT_FOUND = -53,
    GF_PROFILE_NOT_SUPPORTED = -54,
    GF_REQUIRES_NEW_INSTANCE = -56,
    GF_FILTER_NOT_SUPPORTED = -57,
    GF_EOS = -1000,
    GF_PENDING_PACKET = -1001,
} GF_Err;

const char *gf_error_to_string(GF_Err e);

#define GF_SAFEALLOC(__ptr, __struct) { \
    (__ptr) = (__struct *) gf_malloc(sizeof(__struct)); \
    if (__ptr) { memset((void *) (__ptr), 0, sizeof(__struct)); } \
}

void *gf_malloc(u64 size);
void gf_free(void *ptr);
void *gf_realloc(void *ptr, u64 size);

typedef struct _tag_array GF_List;
GF_List *gf_list_new(void);
void gf_list_del(GF_List *ptr);
u32 gf_list_count(const GF_List *ptr);
GF_Err gf_list_add(GF_List *ptr, void *item);
GF_Err gf_list_insert(GF_List *ptr, void *item, u32 position);
GF_Err gf_list_rem(GF_List *ptr, u32 position);
void *gf_list_get(GF_List *ptr, u32 position);
s32 gf_list_find(GF_List *ptr, void *item);
s32 gf_list_del_item(GF_List *ptr, void *item);
void gf_list_reset(GF_List *ptr);
void *gf_list_pop_front(GF_List *ptr);
void *gf_list_pop_back(GF_List *ptr);

typedef struct __tag_bitstream GF_BitStream;
GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode);
GF_Err gf_bs_reassign_buffer(GF_BitStream *bs, const u8 *buffer, u64 size);
void gf_bs_del(GF_BitStream *bs);
void gf_bs_write_u8(GF_BitStream *bs, u32 value);
void gf_bs_write_u32(GF_BitStream *bs, u32 value);
void gf_bs_write_int(GF_BitStream *bs, s32 value, u32 nb_bits);
GF_Err gf_bs_set_logger(GF_BitStream *bs, void (*on_bs_log)(void *udta, const char *field_name, u32 nb_bits, u64 field_val, s32 idx1, s32 idx2, s32 idx3), void *udta);

typedef struct __gf_filter_session GF_FilterSession;
typedef struct __gf_filter_pck GF_FilterPacket;
typedef struct __gf_filter_register GF_FilterRegister;

typedef struct { u8 *ptr; u32 size; } GF_PropData;

typedef struct {
    GF_List *properties;
    volatile u32 reference_count;
    volatile u32 pckrefs_reference_count;
    GF_FilterSession *session;
    u32 timescale;
} GF_PropertyMap;

typedef struct __gf_prop_val {
    u32 type;
    union {
        u64 longuint;
        s64 longsint;
        s32 sint;
        u32 uint;
        Bool boolean;
        GF_Fraction frac;
        GF_Fraction64 lfrac;
        double number;
        float fnumber;
        const char *string;
        GF_PropData data;
        void *ptr;
    } value;
} GF_PropertyValue;

typedef struct __gf_filter_event {
    struct {
        u32 type;
        void *on_pid;
        struct { Bool pid_only; u64 max_buffer_us; } buffer_req;
    } base;
} GF_FilterEvent;

typedef struct __gf_filter_pid_inst {
    struct __gf_filter *filter;
    struct __gf_filter_pid *pid;
    struct __gf_filter *alias_orig;
    void *props;
    int detach_pending;
} GF_FilterPidInst;

typedef struct __gf_filter_pid {
    struct __gf_filter_pid *pid;
    struct __gf_filter *filter;
    const char *name;
    GF_List *destinations;
    u32 num_destinations;
    GF_List *properties;
    Bool request_property_map;
    Bool pid_info_changed;
    Bool destroyed;
    u32 not_connected;
    Bool not_connected_ok;
    Bool removed;
    Bool direct_dispatch;
    volatile u32 discard_input_packets;
    volatile u32 init_task_pending;
    volatile Bool props_changed_since_connect;
    volatile u32 nb_shared_packets_out;
    GF_PropertyMap *infos;
    Bool has_seen_eos;
    u32 nb_reaggregation_pending;
    u32 max_buffer_unit;
    volatile u32 nb_buffer_unit;
    u64 max_buffer_time;
    u32 user_max_buffer_time, user_max_playout_time, user_min_playout_time;
    u64 buffer_duration;
    Bool raw_media;
    Bool is_sparse;
    u32 stream_type, codecid;
    volatile u32 would_block;
    volatile u32 nb_decoder_inputs;
    Bool duration_init;
    u64 last_pck_dts, last_pck_cts, min_pck_cts, max_pck_cts;
    u32 min_pck_duration, nb_unreliable_dts, last_pck_dur;
    Bool recompute_dts;
    Bool ignore_blocking;
    u32 nb_pck_sent;
    u32 playback_speed_scaler;
    GF_Fraction64 last_ts_sent;
    Bool initial_play_done;
    Bool is_playing;
    void *udta;
    u32 udta_flags;
    GF_PropertyMap *caps_negociate;
    Bool caps_negociate_direct;
    GF_List *caps_negociate_pidi_list;
    GF_List *adapters_blacklist;
    struct __gf_filter *caps_dst_filter;
    Bool ext_not_trusted;
    Bool require_source_id;
    GF_PropertyMap *local_props;
    volatile u32 num_pidinst_del_pending;
    int out_pid_connection_pending;
    void *pending_packets;
    void *postponed_packets;
    u32 nb_caps_renegociate;
    void *tasks_mx;
} GF_FilterPid;

typedef struct __gf_fs_task {
    struct __gf_filter *filter;
    void (*run_task)(struct __gf_fs_task *task);
    int can_swap;
    int requeue_request;
    u64 schedule_next_time;
    GF_FilterPid *pid;
} GF_FSTask;

typedef struct __gf_filter {
    GF_FilterSession *session;
    const char *name;
    GF_FilterRegister *freg;
    void *filter_udta;
    void *tasks_mx;
    int process_task_queued;
    int disabled;
    int out_pid_connection_pending;
    GF_List *detached_pid_inst;
    int caps_negociate;
    int removed;
    int finalized;
    int prevent_blocking;
    int would_block;
    int num_out_pids_not_connected;
    int num_output_pids;
    int stream_reset_pending;
    struct __gf_filter *multi_sink_target;
    void *postponed_packets;
    u32 nb_pck_io;
    u32 nb_caps_renegociate;
    int in_process_callback;
    int has_pending_pids;
    void *pending_pids;
    u64 schedule_next_time;
    int nb_tasks_done;
    int max_nb_consecutive_process;
    int nb_consecutive_process;
    int nb_process_since_reset;
    int stats_nb_alloc;
    int stats_nb_calloc;
    int stats_nb_realloc;
    int stats_nb_free;
    u64 stats_mem_allocated;
    int max_nb_process;
    int max_stats_nb_alloc;
    int max_stats_nb_calloc;
    int max_stats_nb_realloc;
    int max_stats_nb_free;
    GF_List *input_pids;
    u32 num_input_pids;
    struct __gf_filter *single_source;
    GF_List *output_pids;
    GF_Err in_connect_err;
    GF_FilterPidInst *swap_pidinst_src;
    GF_FilterPidInst *swap_pidinst_dst;
    int has_out_caps;
    GF_List *blacklisted;
    int sticky;
    int is_pid_adaptation_filter;
    int on_setup_error;
    int requires_solved_graph;
    void *rmt_hash;
    void *tasks;
    void *pending_packets;
} GF_Filter;

#define GF_EXPORT

struct __gf_filter_session {
    u32 flags;
    int in_final_flush;
    int last_connect_error;
    int check_allocs;
    int requires_solved_graph;
};

typedef enum {
    GF_PROP_PID_CODECID = 0x636F6463,
    GF_PROP_PID_TIMESCALE = 0x7473636C,
    GF_PROP_PID_FPS = 0x66707320,
    GF_PROP_PID_MIME = 0x6D696D65,
    GF_PROP_PID_FILE_EXT = 0x66657874,
    GF_PROP_PID_STREAM_TYPE = 0x73747970,
    GF_PROP_PID_UNFRAMED = 0x756E6672,
    GF_PROP_PID_UNFRAMED_FULL_AU = 0x75666175,
    GF_PROP_PID_ID = 0x69642020,
    GF_PROP_PID_MAX_NALU_SIZE = 0x6D6E6C73,
    GF_PROP_PID_DOLBY_VISION = 0x64766366,
    GF_PROP_PID_PROTECTION_SCHEME_TYPE = 0x70736368,
    GF_PROP_PID_TILE_BASE = 0x74626173,
} GF_PropertyID;

enum {
    GF_STREAM_VISUAL = 4,
    GF_STREAM_FILE = 16,
    GF_STREAM_ENCRYPTED = 20,
};

enum {
    GF_CODECID_AVC = 0x61766331,
    GF_CODECID_AVC_PS = 0x61766370,
    GF_CODECID_HEVC = 0x68766331,
    GF_CODECID_LHVC = 0x6C687663,
    GF_CODECID_VVC = 0x76766331,
    GF_CODECID_SVC = 0x73766331,
    GF_CODECID_MVC = 0x6D766331,
};

#define PROP_UINT(_v) (GF_PropertyValue){.type=1, .value.uint=_v}
#define PROP_DATA(_d, _s) (GF_PropertyValue){.type=10, .value.string=(const char*)(_d)}
#define PROP_BOOL(_v) (GF_PropertyValue){.type=6, .value.boolean=_v}
#define PROP_FRAC(_n, _d) (GF_PropertyValue){.type=8, .value.frac={.num=_n, .den=_d}}
#define PROP_STRING(_s) (GF_PropertyValue){.type=7, .value.string=_s}

#define GF_FILTER_NO_BO 0xFFFFFFFFFFFFFFFFUL
#define GF_FILTER_NO_TS 0xFFFFFFFFFFFFFFFFUL

typedef enum {
    GF_FILTER_SAP_NONE = 0,
    GF_FILTER_SAP_1 = 1,
    GF_FILTER_SAP_2 = 2,
    GF_FILTER_SAP_3 = 3,
    GF_FILTER_SAP_4 = 4,
} GF_FilterSAPType;

typedef enum {
    GF_PID_CONF_CONNECT = 0,
    GF_PID_CONF_REMOVE = 1,
    GF_PID_CONF_RECONFIG = 2,
} GF_PidConnectType;

typedef struct {
    u32 code;
    GF_PropertyValue val;
    const char *name;
    u32 flags;
    u8 priority;
} GF_FilterCapability;

typedef enum {
    GF_FS_ARG_HINT_BASIC = 0,
    GF_FS_ARG_HINT_ADVANCED = 1<<8,
    GF_FS_ARG_HINT_EXPERT = 1<<9,
    GF_FS_ARG_HINT_HIDE = 1<<10,
    GF_FS_ARG_META = 1<<11,
    GF_FS_ARG_READ_ONLY = 1<<12,
    GF_FS_ARG_NOSAVE = 1<<13,
} GF_FSArgumentFlags;

typedef struct {
    const char *arg_name;
    s32 offset_in_private;
    const char *arg_desc;
    u32 arg_type;
    const char *arg_default_val;
    const char *min_max_enum;
    GF_FSArgumentFlags flags;
} GF_FilterArgs;

enum {
    GF_CAPFLAG_IN_BUNDLE = 1,
    GF_CAPFLAG_INPUT = 1<<1,
    GF_CAPFLAG_OUTPUT = 1<<2,
    GF_CAPFLAG_EXCLUDED = 1<<3,
    GF_CAPFLAG_LOADED_FILTER = 1<<4,
    GF_CAPFLAG_STATIC = 1<<5,
    GF_CAPFLAG_OPTIONAL = 1<<6,
};

#define GF_CAPS_INPUT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT)
#define GF_CAPS_INPUT_OPT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_OPTIONAL)
#define GF_CAPS_INPUT_STATIC (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_STATIC)
#define GF_CAPS_INPUT_STATIC_OPT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_STATIC|GF_CAPFLAG_OPTIONAL)
#define GF_CAPS_INPUT_EXCLUDED (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_EXCLUDED)
#define GF_CAPS_INPUT_LOADED_FILTER (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_LOADED_FILTER)
#define GF_CAPS_OUTPUT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_OUTPUT)
#define GF_CAPS_OUTPUT_LOADED_FILTER (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_LOADED_FILTER)
#define GF_CAPS_OUTPUT_EXCLUDED (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_EXCLUDED)
#define GF_CAPS_OUTPUT_STATIC (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_STATIC)
#define GF_CAPS_OUTPUT_STATIC_EXCLUDED (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_EXCLUDED|GF_CAPFLAG_STATIC)
#define GF_CAPS_INPUT_OUTPUT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_OUTPUT)
#define GF_CAPS_INPUT_OUTPUT_OPT (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_OPTIONAL)
#define GF_CAPS_IN_OUT_EXCLUDED (GF_CAPFLAG_IN_BUNDLE|GF_CAPFLAG_INPUT|GF_CAPFLAG_OUTPUT|GF_CAPFLAG_EXCLUDED)

#define CAP_SINT(_f, _a, _b) { .code=_a, .val={.type=2, .value.sint=_b}, .flags=(_f) }
#define CAP_UINT(_f, _a, _b) { .code=_a, .val={.type=1, .value.uint=_b}, .flags=(_f) }
#define CAP_4CC(_f, _a, _b) { .code=_a, .val={.type=3, .value.uint=_b}, .flags=(_f) }
#define CAP_LSINT(_f, _a, _b) { .code=_a, .val={.type=4, .value.longsint=_b}, .flags=(_f) }
#define CAP_LUINT(_f, _a, _b) { .code=_a, .val={.type=5, .value.longuint=_b}, .flags=(_f) }
#define CAP_BOOL(_f, _a, _b) { .code=_a, .val={.type=6, .value.boolean=_b}, .flags=(_f) }
#define CAP_FIXED(_f, _a, _b) { .code=_a, .val={.type=7, .value.fnumber=_b}, .flags=(_f) }
#define CAP_FLOAT(_f, _a, _b) { .code=_a, .val={.type=7, .value.fnumber=_b}, .flags=(_f) }
#define CAP_FRAC_INT(_f, _a, _b, _c) { .code=_a, .val={.type=8, .value.frac={.num=_b, .den=_c}}, .flags=(_f) }
#define CAP_FRAC(_f, _a, _b) { .code=_a, .val={.type=8, .value.frac=_b}, .flags=(_f) }
#define CAP_DOUBLE(_f, _a, _b) { .code=_a, .val={.type=9, .value.number=_b}, .flags=(_f) }
#define CAP_NAME(_f, _a, _b) { .code=_a, .val={.type=10, .value.string=_b}, .flags=(_f) }
#define CAP_STRING(_f, _a, _b) { .code=_a, .val={.type=11, .value.string=_b}, .flags=(_f) }
#define CAP_UINT_PRIORITY(_f, _a, _b, _p) { .code=_a, .val={.type=1, .value.uint=_b}, .flags=(_f), .priority=_p}

#define SETCAPS(__struct) .caps = __struct, .nb_caps = sizeof(__struct)/sizeof(GF_FilterCapability)

typedef enum {
    GF_FS_REG_NONE = 0,
    GF_FS_REG_STATIC = 0x10000000,
    GF_FS_REG_DYNAMIC = 0x20000000,
    GF_FS_REG_CUSTOM = 0x40000000,
} GF_FSRegisterFlags;

struct __gf_filter_register {
    const char *name;
    u32 private_size;
    u32 max_extra_pids;
    GF_FSRegisterFlags flags;
    const GF_FilterCapability *caps;
    u32 nb_caps;
    const GF_FilterArgs *args;
    GF_Err (*process)(GF_Filter *filter);
    GF_Err (*configure_pid)(GF_Filter *filter, GF_FilterPid *PID, Bool is_remove);
    GF_Err (*initialize)(GF_Filter *filter);
    void (*finalize)(GF_Filter *filter);
    GF_Err (*update_arg)(GF_Filter *filter, const char *arg_name, const GF_PropertyValue *new_val);
    Bool (*process_event)(GF_Filter *filter, const GF_FilterEvent *evt);
    GF_Err (*reconfigure_output)(GF_Filter *filter, GF_FilterPid *PID);
    const char *description;
    const char *help;
    const char *(*probe_data)(const u8 *data, u32 size, void *score);
    u8 priority;
    void (*register_free)(GF_FilterSession *session, struct __gf_filter_register *freg);
};

#define GF_FS_SET_DESCRIPTION(_desc) .description = _desc,
#define GF_FS_SET_HELP(_help) .help = _help,

void *gf_filter_get_udta(GF_Filter *filter);
GF_Err gf_filter_pid_check_caps(GF_FilterPid *pid);
const GF_PropertyValue *gf_filter_pid_get_property(GF_FilterPid *pid, u32 prop_4cc);
GF_Err gf_filter_pid_remove(GF_FilterPid *pid);
GF_FilterPid *gf_filter_pid_new(GF_Filter *filter);
GF_Err gf_filter_pid_copy_properties(GF_FilterPid *dst, GF_FilterPid *src);
GF_Err gf_filter_pid_set_property(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *val);
GF_Err gf_filter_pid_send_event(GF_FilterPid *pid, GF_FilterEvent *evt);
GF_Err gf_filter_pid_update_caps(GF_FilterPid *pid);
GF_FilterPidInst *gf_filter_pid_inst_new(GF_Filter *filter, GF_FilterPid *pid);
void gf_filter_pid_inst_swap(GF_Filter *filter, GF_FilterPidInst *pidinst);
void gf_filter_pid_inst_del(GF_FilterPidInst *pidinst);
void gf_filter_pid_post_init_task(GF_Filter *filter, GF_FilterPid *pid);
void gf_filter_pid_post_connect_task(GF_Filter *new_filter, GF_FilterPid *pid);
GF_Err gf_filter_pid_send_event_internal(GF_FilterPid *pid, GF_FilterEvent *evt, Bool internal_only);
void gf_filter_pid_set_eos(GF_FilterPid *pid);
GF_Err gf_filter_pid_set_info(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *val);
GF_Err gf_filter_pid_set_info_str(GF_FilterPid *pid, const char *prop_name, const GF_PropertyValue *val);
Bool gf_filter_pid_would_block(GF_FilterPid *pid);
GF_FilterPacket *gf_filter_pid_get_packet(GF_FilterPid *pid);
Bool gf_filter_pid_is_eos(GF_FilterPid *pid);
GF_Err gf_filter_pid_drop_packet(GF_FilterPid *pid);
void gf_filter_relink_dst(GF_FilterPidInst *pidinst);
void gf_filter_renegociate_output(GF_Filter *filter, Bool force);
Bool gf_filter_reporting_enabled(GF_Filter *filter);
void gf_filter_update_status(GF_Filter *filter, s32 progress, const char *status);
void gf_filter_reset_pending_packets(GF_Filter *filter);
void gf_filter_post_remove(GF_Filter *filter);
GF_Filter *gf_filter_clone(GF_Filter *filter, GF_Filter *src_filter);
void gf_filter_check_pending_tasks(GF_Filter *filter, GF_FSTask *task);
void gf_filter_notification_failure(GF_Filter *filter, GF_Err e, Bool fatal);
void gf_filter_instance_detach_pid(GF_FilterPidInst *pidinst);
const u8 *gf_filter_pck_get_data(GF_FilterPacket *pck, u32 *size);
u64 gf_filter_pck_get_byte_offset(GF_FilterPacket *pck);
u64 gf_filter_pck_get_dts(GF_FilterPacket *pck);
u64 gf_filter_pck_get_cts(GF_FilterPacket *pck);
void gf_filter_pck_set_cts(GF_FilterPacket *pck, u64 cts);
GF_Err gf_filter_pck_send_internal(GF_FilterPacket *pck, Bool force);
void gf_filter_pck_unref(GF_FilterPacket *pck);
GF_Err gf_filter_pid_configure(GF_Filter *filter, GF_FilterPid *pid, GF_PidConnectType ctype);
void gf_filter_process_task(GF_FSTask *task);

u32 gf_sys_clock_high_res(void);
u32 gf_fq_count(void *fq);
void *gf_fq_pop(void *fq);
void *gf_fq_get(void *fq, u32 idx);
void gf_fs_post_task(GF_FilterSession *session, void (*task_func)(GF_FSTask *), GF_Filter *filter, GF_FilterPid *pid, const char *name, void *udta);
void gf_filter_post_process_task(GF_Filter *filter);

typedef struct {
    u32 nal_unit_type;
    void *sps;
    u32 vps_id;
    s32 poc;
    u32 slice_type;
    Bool field_pic_flag;
    Bool bottom_field_flag;
    u32 redundant_pic_cnt;
} AVCSliceInfo;

typedef struct {
    AVCSliceInfo s_info;
    struct { struct { Bool valid; u32 frame_cnt; } recovery_point; } sei;
} AVCState;

typedef struct { u32 vps_id; } HEVC_SPS;
typedef struct { u32 vps_id; u32 max_sub_layers; } HEVC_VPS;
typedef struct {
    u32 last_parsed_vps_id;
    u32 last_parsed_sps_id;
    u32 last_parsed_pps_id;
    struct {
        u32 nal_unit_type;
        HEVC_SPS *sps;
        s32 poc;
        u32 slice_type;
        Bool non_ref_pic;
        Bool irap_or_gdr_pic;
        Bool gdr_pic;
        Bool recovery_point_valid;
        u32 gdr_recovery_count;
    } s_info;
    struct { struct { Bool valid; u32 frame_cnt; } recovery_point; } sei;
    HEVC_VPS vps[16];
} HEVCState;

typedef struct {
    struct {
        u32 nal_unit_type;
        s32 poc;
        u32 slice_type;
        Bool non_ref_pic;
        Bool irap_or_gdr_pic;
        Bool gdr_pic;
        Bool recovery_point_valid;
        u32 gdr_recovery_count;
    } s_info;
} VVCState;

typedef struct { u32 parallelism_type; } GF_HEVCConfig;

s32 gf_hevc_parse_nalu_bs(GF_BitStream *bs, HEVCState *hevc, u8 *nal_unit_type, u8 *temporal_id, u8 *layer_id);
void gf_hevc_parse_sei(u8 *data, u32 size, HEVCState *hevc);
s32 gf_hevc_read_vps_ex(u8 *data, u32 *size, HEVCState *hevc, Bool parse_ext);
Bool gf_hevc_slice_is_IDR(HEVCState *hevc);
Bool gf_hevc_slice_is_intra(HEVCState *hevc);
Bool gf_avc_slice_is_intra(AVCState *avc);
Bool gf_vvc_slice_is_ref(VVCState *vvc);
s32 gf_media_nalu_next_start_code(const u8 *data, u32 size, u32 *sc_size);
u32 gf_dolby_vision_level(u32 width, u32 height, u32 fps_num, u32 fps_den, u32 codecid);

enum {
    GF_HEVC_NALU_VID_PARAM = 32,
    GF_HEVC_NALU_SEQ_PARAM = 33,
    GF_HEVC_NALU_PIC_PARAM = 34,
    GF_HEVC_NALU_SEI_PREFIX = 39,
    GF_HEVC_NALU_SEI_SUFFIX = 40,
    GF_HEVC_NALU_SLICE_TRAIL_N = 0,
    GF_HEVC_NALU_SLICE_TRAIL_R = 1,
    GF_HEVC_NALU_SLICE_TSA_N = 2,
    GF_HEVC_NALU_SLICE_TSA_R = 3,
    GF_HEVC_NALU_SLICE_STSA_N = 4,
    GF_HEVC_NALU_SLICE_STSA_R = 5,
    GF_HEVC_NALU_SLICE_RADL_N = 6,
    GF_HEVC_NALU_SLICE_RADL_R = 7,
    GF_HEVC_NALU_SLICE_RASL_N = 8,
    GF_HEVC_NALU_SLICE_RASL_R = 9,
    GF_HEVC_NALU_SLICE_RSV_VCL_N10 = 10,
    GF_HEVC_NALU_SLICE_RSV_VCL_N12 = 12,
    GF_HEVC_NALU_SLICE_RSV_VCL_N14 = 14,
    GF_HEVC_NALU_SLICE_BLA_W_LP = 16,
    GF_HEVC_NALU_SLICE_BLA_W_DLP = 17,
    GF_HEVC_NALU_SLICE_BLA_N_LP = 18,
    GF_HEVC_NALU_SLICE_IDR_W_DLP = 19,
    GF_HEVC_NALU_SLICE_IDR_N_LP = 20,
    GF_HEVC_NALU_SLICE_CRA = 21,
    GF_HEVC_NALU_ACCESS_UNIT = 35,
    GF_HEVC_NALU_FILLER_DATA = 36,
    GF_HEVC_NALU_END_OF_SEQ = 37,
    GF_HEVC_NALU_END_OF_STREAM = 38,
    GF_HEVC_NALU_DV_RPU = 62,
    GF_HEVC_NALU_DV_EL = 63,
};

enum {
    GF_HEVC_SLICE_TYPE_P = 1,
    GF_HEVC_SLICE_TYPE_B = 0,
    GF_HEVC_SLICE_TYPE_I = 2,
};

enum {
    GF_VVC_NALU_OPI = 12,
    GF_VVC_NALU_DEC_PARAM = 13,
    GF_VVC_NALU_VID_PARAM = 14,
    GF_VVC_NALU_SEQ_PARAM = 15,
    GF_VVC_NALU_PIC_PARAM = 16,
    GF_VVC_NALU_SEI_PREFIX = 25,
    GF_VVC_NALU_SEI_SUFFIX = 26,
    GF_VVC_NALU_APS_PREFIX = 27,
    GF_VVC_NALU_APS_SUFFIX = 28,
    GF_VVC_NALU_PIC_HEADER = 29,
    GF_VVC_NALU_SLICE_TRAIL = 0,
    GF_VVC_NALU_SLICE_STSA = 1,
    GF_VVC_NALU_SLICE_RADL = 2,
    GF_VVC_NALU_SLICE_RASL = 3,
    GF_VVC_NALU_SLICE_IDR_W_RADL = 7,
    GF_VVC_NALU_SLICE_IDR_N_LP = 8,
    GF_VVC_NALU_SLICE_CRA = 9,
    GF_VVC_NALU_SLICE_GDR = 10,
};

enum {
    GF_AVC_NALU_IDR_SLICE = 5,
    GF_AVC_NALU_SVC_PREFIX_NALU = 14,
    GF_AVC_NALU_SVC_SLICE = 20,
};

enum {
    GF_AVC_TYPE_B = 0,
    GF_AVC_TYPE2_B = 5,
};

#define GF_BITSTREAM_READ 0
#define GF_BITSTREAM_WRITE 1

#define GF_LOG_DEBUG 0
#define GF_LOG_INFO 1
#define GF_LOG_WARNING 2
#define GF_LOG_ERROR 3
#define GF_LOG_MEDIA 0x01
#define GF_LOG_FILTER 0x10
Bool gf_log_tool_level_on(u32 tool, u32 level);
#define GF_LOG(_level, _tool, _args) do { if (gf_log_tool_level_on(_tool, _level)) gf_log_fmt _args; } while (0)
void gf_log_fmt(const char *format, ...);

#define GF_FEVT_PLAY 1
#define GF_FEVT_STOP 2
#define GF_FEVT_BUFFER_REQ 3
#define GF_FEVT_CONNECT_FAIL 4
#define GF_FEVT_INFO_UPDATE 5

#define GF_FEVT_INIT(_evt, _type, _pid) memset(&_evt, 0, sizeof(_evt)); _evt.base.type = _type; _evt.base.on_pid = _pid;

enum {
    GF_FS_FLAG_NO_REASSIGN = 1<<4,
};

enum {
    GF_RMT_AGGREGATE = 0,
};

void gf_rmt_begin_hash(const char *name, u32 flags, void **hash);
void gf_rmt_end(void);

typedef struct _gf_mutex GF_Mutex;
GF_Mutex *gf_mx_new(const char *name);
void gf_mx_p(GF_Mutex *mx);
void gf_mx_v(GF_Mutex *mx);

enum {
    DVMODE_NONE = 0,
    DVMODE_AUTO,
    DVMODE_FORCE,
    DVMODE_CLEAN,
    DVMODE_SINGLE,
};

enum {
    STRICT_POC_OFF = 0,
    STRICT_POC_ON,
    STRICT_POC_ERROR,
};

typedef struct {
    u64 pos;
    Double duration;
    u32 roll_count;
} NALUIdx;

typedef struct {
    u32 layer_id_plus_one;
    u32 min_temporal_id, max_temporal_id;
} LHVCLayerInfo;

typedef struct {
    GF_Fraction fps;
    Double index;
    Bool explicit, force_sync, nosei, importer, subsamples, nosvc, novpsext, deps, seirw, audelim, analyze, notime;
    u32 nal_length;
    u32 strict_poc;
    u32 bsdbg;
    GF_Fraction dur;
    u32 dv_mode, dv_profile, dv_compatid;
    GF_FilterPid *ipid;
    GF_FilterPid *opid;
    GF_BitStream *bs_r;
    GF_BitStream *bs_w;
    u64 cts, dts, prev_dts, prev_cts;
    u32 pck_duration;
    u32 width, height;
    u32 crc_cfg, crc_cfg_enh;
    GF_Fraction sar;
    GF_Fraction cur_fps;
    GF_Fraction64 duration;
    Double start_range;
    Bool in_seek;
    u32 seek_gdr_count;
    Bool first_gdr;
    Bool is_playing;
    Bool is_file, file_loaded;
    Bool initial_play_done;
    NALUIdx *indexes;
    u32 index_alloc_size, index_size;
    u32 timescale;
    Bool input_is_au_start;
    GF_FilterPacket *src_pck;
    Bool full_au_source;
    s32 max_total_delay;
    u32 max_nalu_size_allowed;
    u32 resume_from;
    Bool nal_adjusted;
    u32 codecid;
    const char *log_name;
    GF_List *pck_queue;
    u64 dts_last_IDR;
    u32 max_nalu_size;
    u8 *nal_store;
    u32 nal_store_size, nal_store_alloc;
    GF_List *sps, *pps, *vps, *sps_ext, *pps_svc, *vvc_aps_pre, *vvc_dci;
    Bool ps_modified;
    u32 nb_idr, nb_i, nb_p, nb_b, nb_sp, nb_si, nb_sei, nb_nalus, nb_aud, nb_cra;
    Bool has_islice;
    GF_FilterSAPType au_sap;
    Bool first_slice_in_au;
    Bool au_sap2_poc_reset;
    Bool is_paff;
    Bool bottom_field_flag;
    s32 sei_recovery_frame_count;
    u32 use_opengop_gdr;
    s32 last_poc, max_last_poc, max_last_b_poc, poc_diff, prev_last_poc, min_poc, poc_shift;
    Bool poc_probe_done;
    GF_FilterPacket *first_pck_in_au;
    Bool has_ref_slices;
    Bool has_redundant;
    Bool last_frame_is_idr;
    char *sei_buffer;
    u32 sei_buffer_size, sei_buffer_alloc;
    u32 subsamp_buffer_alloc, subsamp_buffer_size, subs_mapped_bytes;
    char *subsamp_buffer;
    AVCState *avc_state;
    char *svc_prefix_buffer;
    u32 svc_prefix_buffer_size, svc_prefix_buffer_alloc;
    u32 svc_nalu_prefix_reserved;
    u8 svc_nalu_prefix_priority;
    HEVCState *hevc_state;
    u32 nb_e_idr, nb_e_i, nb_e_p, nb_e_b;
    Bool vvc_no_stats;
    LHVCLayerInfo linf[64];
    u8 max_temporal_id[64];
    u8 min_layer_id;
    VVCState *vvc_state;
    Bool has_initial_aud;
    char init_aud[3];
    Bool interlaced;
    Bool is_mvc;
    u32 bitrate;
    u32 nb_frames;
    u8 last_layer_id, last_temporal_id;
    u32 clli_crc, mdcv_crc;
    u32 nb_dv_rpu, nb_dv_el;
} GF_NALUDmxCtx;

static void naludmx_enqueue_or_dispatch(GF_NALUDmxCtx *ctx, GF_FilterPacket *n_pck, Bool flush_ref);
static void naludmx_finalize_au_flags(GF_NALUDmxCtx *ctx);
static void naludmx_reset_param_sets(GF_NALUDmxCtx *ctx, Bool do_free);
static void naludmx_set_dolby_vision(GF_NALUDmxCtx *ctx);
static void naludmx_check_dur(GF_Filter *filter, GF_NALUDmxCtx *ctx);
static void naludmx_check_pid(GF_Filter *filter, GF_NALUDmxCtx *ctx, Bool force_au_flush);
static void naludmx_end_access_unit(GF_NALUDmxCtx *ctx);
GF_Err naludmx_set_hevc_oinf(GF_NALUDmxCtx *ctx, u8 *max_temporal_id);
static void naludmx_set_hevc_linf(GF_NALUDmxCtx *ctx);
GF_FilterPacket *naludmx_start_nalu(GF_NALUDmxCtx *ctx, u32 nal_size, Bool skip_nal_field, Bool *au_start, u8 **pck_data);
void naludmx_add_subsample(GF_NALUDmxCtx *ctx, u32 subs_size, u8 subs_priority, u32 subs_reserved);
static void naludmx_push_prefix(GF_NALUDmxCtx *ctx, u8 *data, u32 size, Bool avc_sei_rewrite);
static s32 naludmx_parse_nal_hevc(GF_NALUDmxCtx *ctx, char *data, u32 size, Bool *skip_nal, Bool *is_slice, Bool *is_islice);
static s32 naludmx_parse_nal_vvc(GF_NALUDmxCtx *ctx, char *data, u32 size, Bool *skip_nal, Bool *is_slice, Bool *is_islice);
static s32 naludmx_parse_nal_avc(GF_NALUDmxCtx *ctx, char *data, u32 size, u32 nal_type, Bool *skip_nal, Bool *is_slice, Bool *is_islice);
static void naldmx_switch_timestamps(GF_NALUDmxCtx *ctx, GF_FilterPacket *pck);
static void naldmx_check_timestamp_switch(GF_NALUDmxCtx *ctx, u32 *nalu_store_before, u32 bytes_drop, Bool *drop_packet, GF_FilterPacket *pck);
static void naldmx_bs_log(void *udta, const char *field_name, u32 nb_bits, u64 field_val, s32 idx1, s32 idx2, s32 idx3);
static void naludmx_queue_param_set(GF_NALUDmxCtx *ctx, char *data, u32 size, u32 ps_type, s32 ps_id);

static void check_filter_error(GF_Filter *filter, GF_Err e, Bool is_process);
static Bool session_should_abort(GF_FilterSession *session);
static int safe_int_dec(volatile int *val);
static void task_canceled(GF_FSTask *task);
static void gf_filter_pid_inst_delete_task(GF_FSTask *task);
static GF_PropertyMap *check_new_pid_props(GF_FilterPid *pid, Bool merge_props);
#ifdef GPAC_MEMORY_TRACKING
static GF_Err gf_filter_process_check_alloc(GF_Filter *filter);
#endif

#define FSESS_CHECK_THREAD(f)

const GF_PropertyValue *gf_filter_pid_get_property_str(GF_FilterPid *PID, const char *prop_name);
Bool gf_props_equal_strict(const GF_PropertyValue *p1, const GF_PropertyValue *p2);
GF_PropertyMap *gf_props_new(GF_Filter *filter);
void gf_props_reset_single(GF_PropertyValue *prop);
GF_Err gf_props_set_property(GF_PropertyMap *map, u32 p4cc, const char *name, char *dyn_name, const GF_PropertyValue *value);
void gf_filter_pid_set_name(GF_FilterPid *PID, const char *name);

enum {
    GF_PROP_STRING_NO_COPY = 15,
    GF_PROP_DATA_NO_COPY = 18,
    GF_PROP_STRING_LIST = 21,
};

static const GF_FilterCapability NALUDmxCaps[] = {
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_STREAM_TYPE, GF_STREAM_FILE),
    CAP_STRING(GF_CAPS_INPUT, GF_PROP_PID_FILE_EXT, "264|h264|26L|h26L|h26l|avc|svc|mvc|hevc|hvc|265|h265|shvc|lvhc|mhvc|266|vvc|lvvc"),
    CAP_STRING(GF_CAPS_INPUT, GF_PROP_PID_MIME, "video/avc|video/h264|video/svc|video/mvc|video/hevc|video/lhvc|video/shvc|video/mhvc|video/vvc"),
    CAP_UINT(GF_CAPS_OUTPUT, GF_PROP_PID_STREAM_TYPE, GF_STREAM_VISUAL),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_AVC),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_AVC_PS),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_SVC),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_MVC),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_HEVC),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_LHVC),
    CAP_UINT(GF_CAPS_OUTPUT_STATIC, GF_PROP_PID_CODECID, GF_CODECID_VVC),
    CAP_BOOL(GF_CAPS_OUTPUT_STATIC_EXCLUDED, GF_PROP_PID_UNFRAMED, GF_TRUE),
    {0},
    CAP_UINT(GF_CAPS_INPUT_OUTPUT, GF_PROP_PID_STREAM_TYPE, GF_STREAM_VISUAL),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_AVC),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_AVC_PS),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_SVC),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_MVC),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_HEVC),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_LHVC),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_VVC),
    CAP_BOOL(GF_CAPS_INPUT, GF_PROP_PID_UNFRAMED, GF_TRUE),
    {0},
    CAP_UINT(GF_CAPS_INPUT_OUTPUT, GF_PROP_PID_STREAM_TYPE, GF_STREAM_ENCRYPTED),
    CAP_4CC(GF_CAPS_INPUT, GF_PROP_PID_PROTECTION_SCHEME_TYPE, 0x73616573),
    CAP_UINT(GF_CAPS_INPUT, GF_PROP_PID_CODECID, GF_CODECID_AVC),
    CAP_BOOL(GF_CAPS_INPUT, GF_PROP_PID_UNFRAMED, GF_TRUE),
};

#define OFFS(_n) #_n, offsetof(GF_NALUDmxCtx, _n)
static const GF_FilterArgs NALUDmxArgs[] = {
    { OFFS(fps), "import frame rate", 12, "0/1000", NULL, 0},
    { OFFS(index), "indexing window length", 9, "-1.0", NULL, 0},
    { OFFS(explicit), "use explicit layered import", 6, "false", NULL, 1<<8},
    { OFFS(strict_poc), "delay frame output", 1, "off", "off|on|error", 1<<8},
    { OFFS(nosei), "remove all sei messages", 6, "false", NULL, 1<<8},
    { OFFS(nosvc), "remove all SVC/MVC/LHVC data", 6, "false", NULL, 1<<8},
    { OFFS(novpsext), "remove all VPS extensions", 6, "false", NULL, 1<<8},
    { OFFS(importer), "compatibility with old importer", 6, "false", NULL, 1<<8},
    { OFFS(dur), "compatibility with old importer", 12, "0", NULL, 1<<10},
    { OFFS(nal_length), "set number of bytes for length field", 1, "4", NULL, 1<<9},
    { OFFS(subsamples), "import subsamples information", 6, "false", NULL, 1<<9},
    { OFFS(deps), "import sample dependency information", 6, "false", NULL, 1<<9},
    { OFFS(seirw), "rewrite AVC sei messages", 6, "true", NULL, 1<<9},
    { OFFS(audelim), "keep Access Unit delimiter", 6, "false", NULL, 1<<9},
    { OFFS(analyze), "skip reformat", 1, "off", "off|on|bs|full", 1<<10},
    { OFFS(notime), "ignore input timestamps", 6, "false", NULL, 1<<8},
    { OFFS(dv_mode), "signaling for DolbyVision", 1, "auto", "none|auto|force|clean|single", 1<<8},
    { OFFS(dv_profile), "profile for DolbyVision", 1, "5", NULL, 1<<8},
    { OFFS(dv_compatid), "cross-compatibility ID for DolbyVision", 1, "none", "none|hdr10|bt709|hlg709|hlg2100|bt2020|brd", 1<<8},
    { OFFS(bsdbg), "debug NAL parsing", 1, "off", "off|on|full", 1<<9},
    {0}
};

GF_Err naludmx_configure_pid(GF_Filter *filter, GF_FilterPid *pid, Bool is_remove);
GF_Err naludmx_process(GF_Filter *filter);
GF_Err naludmx_initialize(GF_Filter *filter);
void naludmx_finalize(GF_Filter *filter);
Bool naludmx_process_event(GF_Filter *filter, const GF_FilterEvent *evt);
const char *naludmx_probe_data(const u8 *data, u32 size, void *score);

GF_FilterRegister NALUDmxRegister = {
	.name = "rfnalu",
	GF_FS_SET_DESCRIPTION("AVC/HEVC reframer")
	GF_FS_SET_HELP("This filter parses AVC|H264 and HEVC files/data and outputs corresponding video PID and frames.\n"
	"This filter produces ISOBMFF-compatible output: start codes are removed, NALU length field added and avcC/hvcC config created.\n"
	"Note: The filter uses negative CTS offsets: CTS is correct, but some frames may have DTS greater than CTS.")
	.private_size = sizeof(GF_NALUDmxCtx),
	.args = NALUDmxArgs,
	.initialize = naludmx_initialize,
	.finalize = naludmx_finalize,
	SETCAPS(NALUDmxCaps),
	.configure_pid = naludmx_configure_pid,
	.process = naludmx_process,
	.process_event = naludmx_process_event,
	.probe_data = naludmx_probe_data,
};

GF_Err naludmx_configure_pid(GF_Filter *filter, GF_FilterPid *pid, Bool is_remove)
{
	const GF_PropertyValue *p;
	u32 old_codecid;
	GF_NALUDmxCtx *ctx = gf_filter_get_udta(filter);

	if (is_remove) {
		ctx->ipid = NULL;
		if (ctx->opid) {
			gf_filter_pid_remove(ctx->opid);
			ctx->opid = NULL;
		}
		return GF_OK;
	}
	if (! gf_filter_pid_check_caps(pid))
		return GF_NOT_SUPPORTED;

	ctx->ipid = pid;
	p = gf_filter_pid_get_property(pid, GF_PROP_PID_TIMESCALE);
	if (p) {
		ctx->timescale = p->value.uint;
		p = gf_filter_pid_get_property(pid, GF_PROP_PID_FPS);
		if (p) {
			ctx->cur_fps = p->value.frac;
		} else {
			ctx->cur_fps.den = 0;
			ctx->cur_fps.num = ctx->timescale;
		}
	}

	old_codecid = ctx->codecid;
	p = gf_filter_pid_get_property(pid, GF_PROP_PID_CODECID);
	if (p) {
		switch (p->value.uint) {
		case GF_CODECID_HEVC:
		case GF_CODECID_LHVC:
			ctx->codecid = GF_CODECID_HEVC;
			break;
		case GF_CODECID_VVC:
			ctx->codecid = GF_CODECID_VVC;
			break;
		case GF_CODECID_AVC:
		case GF_CODECID_AVC_PS:
		case GF_CODECID_SVC:
		case GF_CODECID_MVC:
			ctx->codecid = GF_CODECID_AVC;
			break;
		default:
			return GF_NOT_SUPPORTED;
		}
	}
	else {
		p = gf_filter_pid_get_property(pid, GF_PROP_PID_MIME);
		if (p && p->value.string && (
			strstr(p->value.string, "hvc")
			|| strstr(p->value.string, "hevc")
			|| strstr(p->value.string, "265")
			|| strstr(p->value.string, "shvc")
			|| strstr(p->value.string, "mhvc")
			|| strstr(p->value.string, "lhvc")
		) )
			ctx->codecid = GF_CODECID_HEVC;
		else if (p && p->value.string && (
			strstr(p->value.string, "vvc")
		) )
			ctx->codecid = GF_CODECID_VVC;
		else {
			p = gf_filter_pid_get_property(pid, GF_PROP_PID_FILE_EXT);
			if (p && p->value.string && (
				 strstr(p->value.string, "hvc")
				 || strstr(p->value.string, "hevc")
				 || strstr(p->value.string, "265")
				 || strstr(p->value.string, "shvc")
				 || strstr(p->value.string, "mhvc")
				 || strstr(p->value.string, "lhvc")
			 ) )
				ctx->codecid = GF_CODECID_HEVC;
			else if (p && p->value.string && (
				 strstr(p->value.string, "vvc")
				 || strstr(p->value.string, "266")
				 || strstr(p->value.string, "lvvc")
			 ) )
				ctx->codecid = GF_CODECID_VVC;
			else
				ctx->codecid = GF_CODECID_AVC;
		}
	}

	if (old_codecid && (old_codecid != ctx->codecid)) {
		naludmx_reset_param_sets(ctx, GF_FALSE);
	}

	if (ctx->codecid==GF_CODECID_HEVC) {
#ifdef GPAC_DISABLE_HEVC
		return GF_NOT_SUPPORTED;
#else
		ctx->log_name = "HEVC";
		if (ctx->avc_state) { gf_free(ctx->avc_state); ctx->avc_state = NULL; }
		if (ctx->vvc_state) { gf_free(ctx->vvc_state); ctx->vvc_state = NULL; }
		if (!ctx->hevc_state) GF_SAFEALLOC(ctx->hevc_state, HEVCState);
		ctx->min_layer_id = 0xFF;
#endif
	} else if (ctx->codecid==GF_CODECID_VVC) {
		ctx->log_name = "VVC";
		if (ctx->hevc_state) { gf_free(ctx->hevc_state); ctx->hevc_state = NULL; }
		if (ctx->avc_state) { gf_free(ctx->avc_state); ctx->avc_state = NULL; }
		if (!ctx->vvc_state) GF_SAFEALLOC(ctx->vvc_state, VVCState);
	} else {
		ctx->log_name = "AVC|H264";
		if (ctx->hevc_state) { gf_free(ctx->hevc_state); ctx->hevc_state = NULL; }
		if (ctx->vvc_state) { gf_free(ctx->vvc_state); ctx->vvc_state = NULL; }
		if (!ctx->avc_state) GF_SAFEALLOC(ctx->avc_state, AVCState);
	}
	if (ctx->timescale && !ctx->opid) {
		ctx->opid = gf_filter_pid_new(filter);
		ctx->first_slice_in_au = GF_TRUE;
	}
	ctx->full_au_source = GF_FALSE;
	p = gf_filter_pid_get_property(pid, GF_PROP_PID_UNFRAMED_FULL_AU);
	if (p && p->value.boolean) {
		GF_FilterEvent fevt;
		GF_FEVT_INIT(fevt, GF_FEVT_BUFFER_REQ, ctx->ipid);
		fevt.base.buffer_req.pid_only = GF_TRUE;
		fevt.base.buffer_req.max_buffer_us = 1000000;
		gf_filter_pid_send_event(ctx->ipid, &fevt);
		ctx->full_au_source = GF_TRUE;
	}

	if (!ctx->timescale) ctx->notime = GF_TRUE;

	if (ctx->opid) {
		if (ctx->poc_probe_done) {
			if (ctx->full_au_source && ctx->first_pck_in_au)
				naludmx_finalize_au_flags(ctx);

			naludmx_enqueue_or_dispatch(ctx, NULL, GF_TRUE);
		}
		ctx->nal_store_size = 0;
		gf_filter_pid_copy_properties(ctx->opid, ctx->ipid);
		if (!ctx->timescale)
			gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_STREAM_TYPE, & PROP_UINT(GF_STREAM_VISUAL));
		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_CODECID, & PROP_UINT(ctx->codecid));

		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_UNFRAMED, NULL);
		gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_UNFRAMED_FULL_AU, NULL);
		if (!gf_filter_pid_get_property(ctx->ipid, GF_PROP_PID_ID))
			gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_ID, &PROP_UINT(1));

		ctx->ps_modified = GF_TRUE;
		ctx->crc_cfg = ctx->crc_cfg_enh = 0;
	}

	return GF_OK;
}

GF_Err gf_filter_pid_configure(GF_Filter *filter, GF_FilterPid *pid, GF_PidConnectType ctype)
{
	u32 i, count;
	GF_Err e;
	Bool new_pid_inst=GF_FALSE;
	Bool remove_filter=GF_FALSE;
	GF_FilterPidInst *pidinst=NULL;
	GF_Filter *alias_orig = NULL;

	if (filter->multi_sink_target) {
		alias_orig = filter;
		filter = filter->multi_sink_target;
	}

	assert(filter->freg->configure_pid);
	if (filter->finalized) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Trying to configure PID %s in finalized filter %s\n",  pid->name, filter->name));
		if (ctype==GF_PID_CONF_CONNECT) {
			assert(pid->filter->out_pid_connection_pending);
			safe_int_dec(&pid->filter->out_pid_connection_pending);
		}
		return GF_SERVICE_ERROR;
	}

	if (filter->detached_pid_inst) {
		count = gf_list_count(filter->detached_pid_inst);
		for (i=0; i<count; i++) {
			pidinst = gf_list_get(filter->detached_pid_inst, i);
			if (pidinst->filter==filter) {
				gf_list_rem(filter->detached_pid_inst, i);
				pidinst->filter = filter;
				pidinst->pid = pid;

				assert(!pidinst->props);

				if (ctype == GF_PID_CONF_CONNECT) {
					new_pid_inst=GF_TRUE;
				}
				assert(pidinst->detach_pending);
				safe_int_dec(&pidinst->detach_pending);
				break;
			}
			pidinst=NULL;
		}
		if (! gf_list_count(filter->detached_pid_inst)) {
			gf_list_del(filter->detached_pid_inst);
			filter->detached_pid_inst = NULL;
		}
	}
	if (!pidinst) {
		count = pid->num_destinations;
		for (i=0; i<count; i++) {
			pidinst = gf_list_get(pid->destinations, i);
			if (pidinst->filter==filter) {
				break;
			}
			pidinst=NULL;
		}
	}

	if (!pidinst) {
		if (ctype != GF_PID_CONF_CONNECT) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Trying to disconnect PID %s not present in filter %s inputs\n",  pid->name, filter->name));
			return GF_SERVICE_ERROR;
		}
		pidinst = gf_filter_pid_inst_new(filter, pid);
		new_pid_inst=GF_TRUE;
	}
	if (!pidinst->alias_orig)
		pidinst->alias_orig = alias_orig;

	if (new_pid_inst) {
		assert(pidinst);
		gf_mx_p(pid->filter->tasks_mx);

		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Registering %s:%s as destination for %s:%s\n", pid->filter->name, pid->name, pidinst->filter->name, pidinst->pid->name));
		gf_list_add(pid->destinations, pidinst);
		pid->num_destinations = gf_list_count(pid->destinations);

		gf_mx_v(pid->filter->tasks_mx);

		gf_mx_p(filter->tasks_mx);
		if (!filter->input_pids) filter->input_pids = gf_list_new();
		gf_list_add(filter->input_pids, pidinst);
		filter->num_input_pids = gf_list_count(filter->input_pids);
		if (filter->num_input_pids==1) {
			filter->single_source = pidinst->pid->filter;
		} else if (filter->single_source != pidinst->pid->filter) {
			filter->single_source = NULL;
		}
		gf_mx_v(filter->tasks_mx);

		gf_filter_pid_update_caps(pid);
	}

	if (filter->swap_pidinst_src || filter->swap_pidinst_dst) {
		gf_filter_pid_inst_swap(filter, pidinst);
	}

	filter->in_connect_err = GF_EOS;

	GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s PID %s reconfigure\n", pidinst->filter->name, pidinst->pid->name));
	e = filter->freg->configure_pid(filter, (GF_FilterPid*) pidinst, (ctype==GF_PID_CONF_REMOVE) ? GF_TRUE : GF_FALSE);

	if ((e==GF_OK) && (filter->in_connect_err<GF_OK))
		e = filter->in_connect_err;

	filter->in_connect_err = GF_OK;
	
	if (e==GF_OK) {
		if (new_pid_inst) {
			GF_LOG(GF_LOG_INFO, GF_LOG_FILTER, ("Filter %s (%p) PID %s (%p) (%d fan-out) connected to filter %s (%p)\n", pid->filter->name, pid->filter, pid->name, pid, pid->num_destinations, filter->name, filter));
		}
	}
	else if ((ctype==GF_PID_CONF_RECONFIG) && (e != GF_FILTER_NOT_SUPPORTED)) {
		if (e==GF_BAD_PARAM) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Failed to reconfigure PID %s:%s in filter %s: %s\n", pid->filter->name, pid->name, filter->name, gf_error_to_string(e) ));

			filter->session->last_connect_error = e;
		} else {
			GF_LOG(GF_LOG_INFO, GF_LOG_FILTER, ("Failed to reconfigure PID %s:%s in filter %s: %s, reloading filter graph\n", pid->filter->name, pid->name, filter->name, gf_error_to_string(e) ));
			gf_filter_relink_dst(pidinst);
		}
	} else {

		gf_mx_p(filter->tasks_mx);
		gf_list_del_item(filter->input_pids, pidinst);
		filter->num_input_pids = gf_list_count(filter->input_pids);
		if (!filter->num_input_pids)
			filter->single_source = NULL;
		filter->freg->configure_pid(filter, (GF_FilterPid *) pidinst, GF_TRUE);
		gf_mx_v(filter->tasks_mx);

		gf_mx_p(pidinst->pid->filter->tasks_mx);
		gf_list_del_item(pidinst->pid->destinations, pidinst);
		pidinst->pid->num_destinations = gf_list_count(pidinst->pid->destinations);
		gf_filter_instance_detach_pid(pidinst);
		gf_mx_v(pidinst->pid->filter->tasks_mx);

		if (new_pid_inst) {
			gf_mx_p(pid->filter->tasks_mx);
			gf_list_del_item(pid->destinations, pidinst);
			pid->num_destinations = gf_list_count(pid->destinations);

			gf_mx_p(pid->filter->tasks_mx);
			count = gf_fq_count(pid->filter->tasks);
			for (i=0; i<count; i++) {
				GF_FSTask *t = gf_fq_get(pid->filter->tasks, i);
				if (t->pid == (GF_FilterPid *) pidinst) {
					t->run_task = task_canceled;
				}
			}
			gf_mx_v(pid->filter->tasks_mx);

			gf_filter_pid_inst_del(pidinst);
			gf_mx_v(pid->filter->tasks_mx);
		}


		if (e==GF_REQUIRES_NEW_INSTANCE) {
			GF_Filter *new_filter = gf_filter_clone(filter, pid->filter);
			if (new_filter) {
				GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Clone filter %s, new instance for pid %s\n", filter->name, pid->name));
				gf_filter_pid_post_connect_task(new_filter, pid);
				return GF_OK;
			} else {
				GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Failed to clone filter %s\n", filter->name));
				e = GF_OUT_OF_MEM;
			}
		}
		if (e && (ctype==GF_PID_CONF_REMOVE)) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Failed to disconnect filter %s PID %s from filter %s: %s\n", pid->filter->name, pid->name, filter->name, gf_error_to_string(e) ));
		}
		else if (e) {
			if (e!= GF_EOS) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Failed to connect filter %s PID %s to filter %s: %s\n", pid->filter->name, pid->name, filter->name, gf_error_to_string(e) ));
			}

			if ((e==GF_BAD_PARAM)
				|| (e==GF_SERVICE_ERROR)
				|| (e==GF_REMOTE_SERVICE_ERROR)
				|| (e==GF_FILTER_NOT_SUPPORTED)
				|| (e==GF_EOS)
				|| (filter->session->flags & GF_FS_FLAG_NO_REASSIGN)
			) {
				if (filter->session->flags & GF_FS_FLAG_NO_REASSIGN) {
					GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Filter reassignment disabled, skippping chain reload for filter %s PID %s\n", pid->filter->name, pid->name ));
				}
				if (e!= GF_EOS) {
					filter->session->last_connect_error = e;
				}

				if (ctype==GF_PID_CONF_CONNECT) {
					GF_FilterEvent evt;
					GF_FEVT_INIT(evt, GF_FEVT_PLAY, pid);
					gf_filter_pid_send_event_internal(pid, &evt, GF_TRUE);

					GF_FEVT_INIT(evt, GF_FEVT_STOP, pid);
					gf_filter_pid_send_event_internal(pid, &evt, GF_TRUE);

					gf_filter_pid_set_eos(pid);

					if (pid->filter->freg->process_event) {
						GF_FEVT_INIT(evt, GF_FEVT_CONNECT_FAIL, pid);
						gf_filter_pid_send_event_internal(pid, &evt, GF_TRUE);
					}
					if (!filter->num_input_pids && !filter->num_output_pids) {
						remove_filter = GF_TRUE;
					}
				}
			} else if (filter->has_out_caps) {
				Bool unload_filter = GF_TRUE;
				GF_LOG(GF_LOG_WARNING, GF_LOG_FILTER, ("Blacklisting %s as output from %s and retrying connections\n", filter->name, pid->filter->name));
				gf_list_add(pid->filter->blacklisted, (void *) filter->freg);
				gf_mx_p(filter->tasks_mx);
				while (gf_list_count(filter->input_pids)) {
					GF_FilterPidInst *a_pidinst = gf_list_pop_back(filter->input_pids);
					FSESS_CHECK_THREAD(filter)
					filter->num_input_pids--;
					filter->freg->configure_pid(filter, (GF_FilterPid *) a_pidinst, GF_TRUE);

					gf_filter_pid_post_init_task(a_pidinst->pid->filter, a_pidinst->pid);
					gf_fs_post_task(filter->session, gf_filter_pid_inst_delete_task, a_pidinst->pid->filter, a_pidinst->pid, "pid_inst_delete", a_pidinst);

					unload_filter = GF_FALSE;
				}
				filter->num_input_pids = 0;
				filter->single_source = NULL;
				filter->removed = 1;
				filter->has_pending_pids = GF_FALSE;
				gf_mx_v(filter->tasks_mx);

				if (ctype==GF_PID_CONF_CONNECT) {
					assert(pid->filter->out_pid_connection_pending);
					safe_int_dec(&pid->filter->out_pid_connection_pending);
				}
				gf_filter_pid_post_init_task(pid->filter, pid);

				if (unload_filter) {
					assert(!gf_list_count(filter->input_pids));

					if (filter->num_output_pids) {
						for (i=0; i<filter->num_output_pids; i++) {
							u32 j;
							GF_FilterPid *opid = gf_list_get(filter->output_pids, i);
							for (j=0; j< opid->num_destinations; j++) {
								GF_FilterPidInst *a_pidi = gf_list_get(opid->destinations, j);
								a_pidi->pid = NULL;
							}
							gf_list_reset(opid->destinations);
							opid->num_destinations = 0;
							gf_filter_pid_remove(opid);
						}
					}
					filter->swap_pidinst_src = NULL;
					if (filter->swap_pidinst_dst) {
						GF_Filter *target = filter->swap_pidinst_dst->filter;
						assert(target);
						if (!target->detached_pid_inst) {
							target->detached_pid_inst = gf_list_new();
						}
						if (filter->swap_pidinst_dst->props) {
							filter->swap_pidinst_dst->props = NULL;
						}
						filter->swap_pidinst_dst->pid = NULL;
						if (gf_list_find(target->detached_pid_inst, filter->swap_pidinst_dst)<0)
							gf_list_add(target->detached_pid_inst, filter->swap_pidinst_dst);
					}
					filter->swap_pidinst_dst = NULL;
					if (filter->on_setup_error) {
						gf_filter_notification_failure(filter, e, GF_TRUE);
					} else {
						gf_filter_post_remove(filter);
					}
				}
				return e;
			} else {
				GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Failed to reconfigure input of sink %s, cannot rebuild graph\n", filter->name));
				if (pid->filter->freg->process_event) {
					GF_FilterEvent evt;
					GF_FEVT_INIT(evt, GF_FEVT_CONNECT_FAIL, pid);
					pid->filter->freg->process_event(pid->filter, &evt);
				}
				filter->session->last_connect_error = e;
			}
		} else {
			filter->session->last_connect_error = GF_OK;
		}

		if (filter->session->requires_solved_graph)
			return e;
	}

	if (filter->has_pending_pids) {
		filter->has_pending_pids = GF_FALSE;
		while (gf_fq_count(filter->pending_pids)) {
			GF_FilterPid *a_pid=gf_fq_pop(filter->pending_pids);
			if (pid->is_playing && filter->is_pid_adaptation_filter)
				a_pid->is_playing = GF_TRUE;

			gf_filter_pid_post_init_task(filter, a_pid);
		}
	}

	if (ctype==GF_PID_CONF_REMOVE) {
		gf_mx_p(filter->tasks_mx);
		gf_list_del_item(filter->input_pids, pidinst);
		filter->num_input_pids = gf_list_count(filter->input_pids);
		if (!filter->num_input_pids)
			filter->single_source = NULL;
		gf_mx_v(filter->tasks_mx);

		gf_mx_p(pidinst->pid->filter->tasks_mx);
		pidinst->pid->num_pidinst_del_pending ++;
		gf_list_del_item(pidinst->pid->destinations, pidinst);
		pidinst->pid->num_destinations = gf_list_count(pidinst->pid->destinations);
		gf_filter_instance_detach_pid(pidinst);
		gf_mx_v(pidinst->pid->filter->tasks_mx);

		if (!filter->num_input_pids && !filter->sticky) {
			gf_filter_reset_pending_packets(filter);
			filter->removed = 1;
		}
		gf_fs_post_task(filter->session, gf_filter_pid_inst_delete_task, pid->filter, pid, "pid_inst_delete", pidinst);

		return e;
	}

	if (ctype==GF_PID_CONF_CONNECT) {
		assert(pid->filter->out_pid_connection_pending);
		if (safe_int_dec(&pid->filter->out_pid_connection_pending) == 0) {

			if (e==GF_OK) {
				if (pid->filter->postponed_packets || pid->filter->pending_packets || pid->filter->nb_caps_renegociate) {
					gf_filter_post_process_task(pid->filter);
				}
			}
		}
		if (remove_filter && !filter->sticky)
			gf_filter_post_remove(filter);
	}
	gf_filter_pid_update_caps(pid);
	return e;
}

#define PID_IS_INPUT(__pid) ((__pid->pid==__pid) ? GF_FALSE : GF_TRUE)

static GF_Err gf_filter_pid_set_property_full(GF_FilterPid *pid, u32 prop_4cc, const char *prop_name, char *dyn_name, const GF_PropertyValue *value, Bool is_info)
{
	GF_PropertyMap *map;
	const GF_PropertyValue *oldp;
	if (PID_IS_INPUT(pid)) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Attempt to write property on input PID in filter %s - ignoring\n", pid->filter->name));
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

	if (value && (prop_4cc == GF_PROP_PID_ID) && !pid->name) {
		char szName[100];
		sprintf(szName, "PID%d", value->value.uint);
		gf_filter_pid_set_name(pid, szName);
	}
	return gf_props_set_property(map, prop_4cc, prop_name, dyn_name, value);
}

GF_EXPORT
GF_Err gf_filter_pid_set_property(GF_FilterPid *pid, u32 prop_4cc, const GF_PropertyValue *value)
{
	if (!prop_4cc) return GF_BAD_PARAM;
	return gf_filter_pid_set_property_full(pid, prop_4cc, NULL, NULL, value, GF_FALSE);
}

static void naludmx_set_dolby_vision(GF_NALUDmxCtx *ctx)
{
	u8 dv_cfg[24];

	switch (ctx->dv_mode) {
	case DVMODE_NONE:
	case DVMODE_CLEAN:
		return;
	case DVMODE_AUTO:
		if (!ctx->nb_dv_rpu && !ctx->nb_dv_el) return;
		break;
	}

	u32 dv_level = gf_dolby_vision_level(ctx->width, ctx->height, ctx->cur_fps.num, ctx->cur_fps.den, ctx->codecid);

	if (ctx->dv_profile==8) {
		if (!ctx->dv_compatid) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_MEDIA, ("[%s] DV profile 8 used but dv_compatid not set, defaulting to bt709 (=2)\n", ctx->log_name));
			ctx->dv_compatid = 2;
		}
	}

	memset(dv_cfg, 0, sizeof(u8)*24);
	GF_BitStream *bs = gf_bs_new(dv_cfg, 24, GF_BITSTREAM_WRITE);
	gf_bs_write_u8(bs, 1);
	gf_bs_write_u8(bs, 0);
	gf_bs_write_int(bs, ctx->dv_profile, 7);
	gf_bs_write_int(bs, dv_level, 6);
	gf_bs_write_int(bs, ctx->nb_dv_rpu ? 1 : 0, 1);
	gf_bs_write_int(bs, ctx->nb_dv_el ? 1 : 0, 1);
	gf_bs_write_int(bs, 1, 1);
	gf_bs_write_int(bs, ctx->dv_compatid, 4);
	gf_bs_write_int(bs, 0, 28);
	gf_bs_write_u32(bs, 0);
	gf_bs_write_u32(bs, 0);
	gf_bs_write_u32(bs, 0);
	gf_bs_write_u32(bs, 0);
	gf_bs_del(bs);
	gf_filter_pid_set_property(ctx->opid, GF_PROP_PID_DOLBY_VISION, &PROP_DATA(dv_cfg, 24));
}

static s32 naludmx_parse_nal_hevc(GF_NALUDmxCtx *ctx, char *data, u32 size, Bool *skip_nal, Bool *is_slice, Bool *is_islice)
{
#ifdef GPAC_DISABLE_HEVC
	return -1;
#else
	s32 ps_idx = 0;
	s32 res;
	u8 nal_unit_type, temporal_id, layer_id;
	*skip_nal = GF_FALSE;

	if (size<2) return -1;

	gf_bs_reassign_buffer(ctx->bs_r, data, size);
	res = gf_hevc_parse_nalu_bs(ctx->bs_r, ctx->hevc_state, &nal_unit_type, &temporal_id, &layer_id);
	ctx->nb_nalus++;

	if (res < 0) {
		if (res == -1) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Warning: Error parsing NAL unit\n", ctx->log_name));
		}
		*skip_nal = GF_TRUE;
	}

	if (layer_id && ctx->nosvc) {
		*skip_nal = GF_TRUE;
		return 0;
	}

	switch (nal_unit_type) {
	case GF_HEVC_NALU_VID_PARAM:
		if (ctx->novpsext) {
			ps_idx = gf_hevc_read_vps_ex(data, &size, ctx->hevc_state, GF_TRUE);
		} else {
			ps_idx = ctx->hevc_state->last_parsed_vps_id;
		}
		if (ps_idx<0) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Error parsing Video Param Set\n", ctx->log_name));
		} else {
			naludmx_queue_param_set(ctx, data, size, GF_HEVC_NALU_VID_PARAM, ps_idx);
		}
		*skip_nal = GF_TRUE;
		break;
	case GF_HEVC_NALU_SEQ_PARAM:
		ps_idx = ctx->hevc_state->last_parsed_sps_id;
		if (ps_idx<0) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Error parsing Sequence Param Set\n", ctx->log_name));
		} else {
			naludmx_queue_param_set(ctx, data, size, GF_HEVC_NALU_SEQ_PARAM, ps_idx);
		}
		*skip_nal = GF_TRUE;
		break;
	case GF_HEVC_NALU_PIC_PARAM:
		ps_idx = ctx->hevc_state->last_parsed_pps_id;
		if (ps_idx<0) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Error parsing Picture Param Set\n", ctx->log_name));
		} else {
			naludmx_queue_param_set(ctx, data, size, GF_HEVC_NALU_PIC_PARAM, ps_idx);
		}
		*skip_nal = GF_TRUE;
		break;
	case GF_HEVC_NALU_SEI_PREFIX:
		gf_hevc_parse_sei(data, size, ctx->hevc_state);
		if (!ctx->nosei) {
			ctx->nb_sei++;
			naludmx_push_prefix(ctx, data, size, GF_FALSE);
		} else {
			ctx->nb_nalus--;
		}
		*skip_nal = GF_TRUE;
		break;
	case GF_HEVC_NALU_SEI_SUFFIX:
		if (! ctx->is_playing) return 0;
		if (ctx->nosei) {
			*skip_nal = GF_TRUE;
			ctx->nb_nalus--;
		} else {
			ctx->nb_sei++;
		}
		break;

	case GF_HEVC_NALU_SLICE_STSA_N:
	case GF_HEVC_NALU_SLICE_STSA_R:
	case GF_HEVC_NALU_SLICE_RADL_R:
	case GF_HEVC_NALU_SLICE_RASL_R:
	case GF_HEVC_NALU_SLICE_RADL_N:
	case GF_HEVC_NALU_SLICE_RASL_N:
	case GF_HEVC_NALU_SLICE_TRAIL_N:
	case GF_HEVC_NALU_SLICE_TRAIL_R:
	case GF_HEVC_NALU_SLICE_TSA_N:
	case GF_HEVC_NALU_SLICE_TSA_R:
	case GF_HEVC_NALU_SLICE_BLA_W_LP:
	case GF_HEVC_NALU_SLICE_BLA_W_DLP:
	case GF_HEVC_NALU_SLICE_BLA_N_LP:
	case GF_HEVC_NALU_SLICE_IDR_W_DLP:
	case GF_HEVC_NALU_SLICE_IDR_N_LP:
	case GF_HEVC_NALU_SLICE_CRA:
		if (! ctx->is_playing) return 0;
		*is_slice = GF_TRUE;
		ctx->last_layer_id = layer_id;
		ctx->last_temporal_id = temporal_id;
		if (! *skip_nal) {
			switch (ctx->hevc_state->s_info.slice_type) {
			case GF_HEVC_SLICE_TYPE_P:
				if (layer_id) ctx->nb_e_p++;
				else ctx->nb_p++;
				break;
			case GF_HEVC_SLICE_TYPE_I:
				if (layer_id) ctx->nb_e_i++;
				else ctx->nb_i++;
				*is_islice = GF_TRUE;
				break;
			case GF_HEVC_SLICE_TYPE_B:
				if (layer_id) ctx->nb_e_b++;
				else ctx->nb_b++;
				break;
			}
		}
		break;

	case GF_HEVC_NALU_ACCESS_UNIT:
		ctx->nb_aud++;
		if (!ctx->audelim) {
			*skip_nal = GF_TRUE;
		} else if (!ctx->opid) {
			ctx->has_initial_aud = GF_TRUE;
			memcpy(ctx->init_aud, data, 3);
		}
		break;
	case GF_HEVC_NALU_FILLER_DATA:
	case GF_HEVC_NALU_END_OF_SEQ:
	case GF_HEVC_NALU_END_OF_STREAM:
		*skip_nal = GF_TRUE;
		break;

	case GF_HEVC_NALU_DV_RPU:
		if (ctx->dv_mode==DVMODE_CLEAN) {
			*skip_nal = GF_TRUE;
		} else {
			ctx->nb_dv_rpu ++;
			if (ctx->nb_dv_rpu==1)
				naludmx_set_dolby_vision(ctx);
		}
		break;
	case GF_HEVC_NALU_DV_EL:
		if ((ctx->dv_mode==DVMODE_CLEAN) || (ctx->dv_mode==DVMODE_SINGLE)) {
			*skip_nal = GF_TRUE;
		} else {
			ctx->nb_dv_el ++;
			if (ctx->nb_dv_el==1)
				naludmx_set_dolby_vision(ctx);
		}
		break;

	default:
		if (! ctx->is_playing) return 0;
		GF_LOG(GF_LOG_WARNING, GF_LOG_MEDIA, ("[%s] NAL Unit type %d not handled - adding\n", ctx->log_name, nal_unit_type));
		break;
	}
	if (*skip_nal) return res;

	ctx->linf[layer_id].layer_id_plus_one = layer_id + 1;
	if (! ctx->linf[layer_id].max_temporal_id ) ctx->linf[layer_id].max_temporal_id = temporal_id;
	else if (ctx->linf[layer_id].max_temporal_id < temporal_id) ctx->linf[layer_id].max_temporal_id = temporal_id;

	if (! ctx->linf[layer_id].min_temporal_id ) ctx->linf[layer_id].min_temporal_id = temporal_id;
	else if (ctx->linf[layer_id].min_temporal_id > temporal_id) ctx->linf[layer_id].min_temporal_id = temporal_id;

	if (ctx->max_temporal_id[layer_id] < temporal_id)
		ctx->max_temporal_id[layer_id] = temporal_id;
	if (ctx->min_layer_id > layer_id) ctx->min_layer_id = layer_id;
	return res;
#endif
}

GF_EXPORT
void *gf_filter_get_udta(GF_Filter *filter)
{
	assert(filter);

	return filter->filter_udta;
}

GF_Err naludmx_process(GF_Filter *filter)
{
	GF_NALUDmxCtx *ctx = gf_filter_get_udta(filter);
	GF_FilterPacket *pck;
	u8 *start;
	u32 nalu_before = ctx->nb_nalus;
	u32 nalu_store_before = 0;
	s32 remain;
	Bool is_eos = GF_FALSE;
	Bool drop_packet = GF_FALSE;
	u64 byte_offset = GF_FILTER_NO_BO;

	if (!ctx->file_loaded)
		naludmx_check_dur(filter, ctx);

	pck = gf_filter_pid_get_packet(ctx->ipid);
	if (!ctx->resume_from && !pck) {
		if (gf_filter_pid_is_eos(ctx->ipid)) {
			if (ctx->nal_store_size) {
				if (!ctx->is_playing)
					return GF_OK;

				start = ctx->nal_store;
				remain = ctx->nal_store_size;
				is_eos = GF_TRUE;
				goto naldmx_flush;
			}
			if (ctx->first_pck_in_au) {
				naludmx_finalize_au_flags(ctx);
			}
			if (!ctx->poc_diff) ctx->poc_diff = 1;
			ctx->strict_poc = STRICT_POC_OFF;
			naludmx_enqueue_or_dispatch(ctx, NULL, GF_TRUE);
			if (ctx->src_pck) gf_filter_pck_unref(ctx->src_pck);
			ctx->src_pck = NULL;
			if (!ctx->opid) return GF_EOS;

			gf_filter_pid_set_info(ctx->opid, GF_PROP_PID_MAX_NALU_SIZE, &PROP_UINT(ctx->max_nalu_size) );
			if (ctx->codecid==GF_CODECID_HEVC) {
				naludmx_set_hevc_oinf(ctx, ctx->max_temporal_id);
				naludmx_set_hevc_linf(ctx);
				gf_filter_pid_set_info_str(ctx->opid, "hevc:min_lid", &PROP_UINT(ctx->min_layer_id) );
			}
			if (ctx->opid)
				gf_filter_pid_set_eos(ctx->opid);
			return GF_EOS;
		}
		return GF_OK;
	}

	if (!ctx->is_playing && ctx->opid)
		return GF_OK;

	if (!ctx->nal_store_size)
		naldmx_switch_timestamps(ctx, pck);

	nalu_store_before = ctx->nal_store_size;
	if (!ctx->resume_from && pck) {
		u32 pck_size;
		const u8 *data = gf_filter_pck_get_data(pck, &pck_size);
		if (ctx->nal_store_alloc < ctx->nal_store_size + pck_size) {
			ctx->nal_store_alloc = ctx->nal_store_size + pck_size;
			ctx->nal_store = gf_realloc(ctx->nal_store, sizeof(char)*ctx->nal_store_alloc);
			if (!ctx->nal_store) {
				ctx->nal_store_alloc = 0;
				return GF_OUT_OF_MEM;
			}
		}
		byte_offset = gf_filter_pck_get_byte_offset(pck);
		if (byte_offset != GF_FILTER_NO_BO)
			byte_offset -= ctx->nal_store_size;
		memcpy(ctx->nal_store + ctx->nal_store_size, data, sizeof(char)*pck_size);
		ctx->nal_store_size += pck_size;
		drop_packet = GF_TRUE;
	}
	start = ctx->nal_store;
	remain = ctx->nal_store_size;

	if (ctx->resume_from) {
		if (ctx->opid && gf_filter_pid_would_block(ctx->opid))
			return GF_OK;

		assert(ctx->resume_from < ctx->nal_store_size);
		start += ctx->resume_from;
		remain -= ctx->resume_from;
		ctx->resume_from = 0;

		if (!pck && gf_filter_pid_is_eos(ctx->ipid))
			is_eos = GF_TRUE;
	}

naldmx_flush:
	if (!ctx->bs_r) {
		ctx->bs_r = gf_bs_new(start, remain, GF_BITSTREAM_READ);

#ifndef GPAC_DISABLE_LOG
		if (ctx->bsdbg && gf_log_tool_level_on(GF_LOG_MEDIA, GF_LOG_DEBUG))
			gf_bs_set_logger(ctx->bs_r, naldmx_bs_log, ctx);
#endif

	} else {
		gf_bs_reassign_buffer(ctx->bs_r, start, remain);
	}

    assert(remain>=0);

	while (remain) {
		u8 *pck_data;
		u8 *nal_data;
		u32 nal_size;
		s32 current;
		Bool skip_nal = GF_FALSE;
		u32 sc_size=0;
		u32 nal_type = 0;
		u32 nal_ref_idc = 0;
		s32 next=0;
		u32 next_sc_size=0;
		s32 nal_parse_result;
		Bool slice_is_idr, slice_force_ref;
		Bool is_slice = GF_FALSE;
		Bool is_islice = GF_FALSE;
		Bool bottom_field_flag = GF_FALSE;
		Bool au_start;
		u32 avc_svc_subs_reserved = 0;
		u8 avc_svc_subs_priority = 0;
		Bool recovery_point_valid = GF_FALSE;
		u32 recovery_point_frame_cnt = 0;
		Bool bIntraSlice = GF_FALSE;
		GF_FilterSAPType au_sap_type = GF_FILTER_SAP_NONE;
		Bool slice_is_b = GF_FALSE;
		Bool check_dep = GF_FALSE;
		Bool force_au_flush = GF_FALSE;
		s32 slice_poc = 0;

		if (!is_eos && (remain<6)) {
			break;
		}

		current = gf_media_nalu_next_start_code(start, remain, &sc_size);
		if (current == remain)
			current = -1;

		if (current<0) {
			break;
		}

		assert(current>=0);

		if (current) {
			assert(remain>=current);
			start += current;
			remain -= current;
			current = 0;
			naldmx_check_timestamp_switch(ctx, &nalu_store_before, current, &drop_packet, pck);
		}

		if (!remain)
			break;

		if (!is_eos && (remain<6)) {
			break;
		}

		nal_data = start + sc_size;
		nal_size = remain - sc_size;

		if (ctx->codecid==GF_CODECID_HEVC) {
			nal_type = nal_data[0];
			nal_type = (nal_type & 0x7E) >> 1;

			switch (nal_type) {
			case GF_HEVC_NALU_VID_PARAM:
			case GF_HEVC_NALU_SEQ_PARAM:
			case GF_HEVC_NALU_PIC_PARAM:
				force_au_flush = GF_TRUE;
			case GF_HEVC_NALU_SEI_PREFIX:
			case GF_HEVC_NALU_SEI_SUFFIX:
				break;
			case GF_HEVC_NALU_SLICE_TRAIL_N:
			case GF_HEVC_NALU_SLICE_TSA_N:
			case GF_HEVC_NALU_SLICE_STSA_N:
			case GF_HEVC_NALU_SLICE_RADL_N:
			case GF_HEVC_NALU_SLICE_RASL_N:
			case GF_HEVC_NALU_SLICE_RSV_VCL_N10:
			case GF_HEVC_NALU_SLICE_RSV_VCL_N12:
			case GF_HEVC_NALU_SLICE_RSV_VCL_N14:
				check_dep = GF_TRUE;
				break;
			default:
				if (nal_type<GF_HEVC_NALU_VID_PARAM)
					nal_ref_idc = GF_TRUE;
				break;
			}
			if (force_au_flush) {
				if (!ctx->first_pck_in_au) {
					force_au_flush = GF_FALSE;
				} else {
					u8 layer_id = nal_data[0] & 1;
					layer_id<<=5;
					layer_id |= (nal_data[1] & 0xF8) >> 3;
					u8 temporal_id = nal_data[2] & 0x7;
					if (ctx->last_layer_id < layer_id)
						force_au_flush = GF_FALSE;
					else if (ctx->last_layer_id == layer_id) {
						if (ctx->last_temporal_id < temporal_id)
							force_au_flush = GF_FALSE;
					}
				}
			}
		} else if (ctx->codecid==GF_CODECID_VVC) {
			nal_type = nal_data[1]>>3;
			switch (nal_type) {
			case GF_VVC_NALU_OPI:
			case GF_VVC_NALU_DEC_PARAM:
			case GF_VVC_NALU_VID_PARAM:
			case GF_VVC_NALU_SEQ_PARAM:
			case GF_VVC_NALU_PIC_PARAM:
				force_au_flush = GF_TRUE;
			case GF_VVC_NALU_SEI_PREFIX:
			case GF_VVC_NALU_SEI_SUFFIX:
			case GF_VVC_NALU_APS_PREFIX:
			case GF_VVC_NALU_APS_SUFFIX:
			case GF_VVC_NALU_PIC_HEADER:
				break;

			case GF_VVC_NALU_SLICE_TRAIL:
			case GF_VVC_NALU_SLICE_STSA:
			case GF_VVC_NALU_SLICE_RADL:
			case GF_VVC_NALU_SLICE_RASL:
			case GF_VVC_NALU_SLICE_IDR_W_RADL:
			case GF_VVC_NALU_SLICE_IDR_N_LP:
			case GF_VVC_NALU_SLICE_CRA:
			case GF_VVC_NALU_SLICE_GDR:
				if (ctx->deps) {
					check_dep = GF_TRUE;
				}
				break;
			default:
				if (nal_type<GF_HEVC_NALU_VID_PARAM)
					nal_ref_idc = GF_TRUE;
				break;
			}

			if (force_au_flush) {
				if (!ctx->first_pck_in_au) {
					force_au_flush = GF_FALSE;
				} else {
					u8 layer_id = nal_data[0] & 0x3f;
					u8 temporal_id = (nal_data[1] & 0x7);
					if (ctx->last_layer_id < layer_id)
						force_au_flush = GF_FALSE;
					else if (ctx->last_layer_id == layer_id) {
						if (ctx->last_temporal_id < temporal_id)
							force_au_flush = GF_FALSE;
					}
				}
			}
		} else {
			nal_type = nal_data[0] & 0x1F;
			nal_ref_idc = (nal_data[0] & 0x60) >> 5;
		}

		next = gf_media_nalu_next_start_code(nal_data, nal_size, &next_sc_size);
		if (!is_eos && (next == nal_size) && !ctx->full_au_source) {
			next = -1;
		}

		if (next<0) {
			break;
		}

		nal_size = next;

		if (ctx->codecid==GF_CODECID_HEVC) {
			nal_parse_result = naludmx_parse_nal_hevc(ctx, nal_data, nal_size, &skip_nal, &is_slice, &is_islice);
		} else if (ctx->codecid==GF_CODECID_VVC) {
			nal_parse_result = naludmx_parse_nal_vvc(ctx, nal_data, nal_size, &skip_nal, &is_slice, &is_islice);
		} else {
			nal_parse_result = naludmx_parse_nal_avc(ctx, nal_data, nal_size, nal_type, &skip_nal, &is_slice, &is_islice);
		}

		if (ctx->analyze) {
			skip_nal = GF_FALSE;
			ctx->sei_buffer_size = 0;
		}

		if ((nal_parse_result>0) && !ctx->first_slice_in_au) {
			naludmx_end_access_unit(ctx);
		}

		naludmx_check_pid(filter, ctx, force_au_flush);
		if (!ctx->opid) skip_nal = GF_TRUE;

		if (skip_nal) {
			nal_size += sc_size;
			assert((u32) remain >= nal_size);
			start += nal_size;
			remain -= nal_size;
			naldmx_check_timestamp_switch(ctx, &nalu_store_before, nal_size, &drop_packet, pck);
			continue;
		}

		if (!ctx->is_playing) {
			ctx->resume_from = (u32) (start - ctx->nal_store);
            assert(ctx->resume_from<=ctx->nal_store_size);
			GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[%s] not yet playing\n", ctx->log_name));

			if (drop_packet)
				gf_filter_pid_drop_packet(ctx->ipid);
			return GF_OK;
		}
		if (ctx->in_seek) {
			u64 nb_frames_at_seek = (u64) (ctx->start_range * ctx->cur_fps.num);
			if (ctx->cts + ctx->cur_fps.den >= nb_frames_at_seek) {
				if (ctx->seek_gdr_count)
					ctx->seek_gdr_count--;
				else
					ctx->in_seek = GF_FALSE;
			}
		}

		if (nal_parse_result<0) {
			if (byte_offset != GF_FILTER_NO_BO) {
				u64 bo = byte_offset;
				bo += (start - ctx->nal_store);

				GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Error parsing NAL Unit %d (byte offset "LLU" size %d type %d frame %d last POC %d) - skipping\n", ctx->log_name, ctx->nb_nalus, bo, nal_size, nal_type, ctx->nb_frames, ctx->last_poc));
			} else {
				GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[%s] Error parsing NAL Unit %d (size %d type %d frame %d last POC %d) - skipping\n", ctx->log_name, ctx->nb_nalus, nal_size, nal_type, ctx->nb_frames, ctx->last_poc));
			}
			nal_size += sc_size;
			assert((u32) remain >= nal_size);
			start += nal_size;
			remain -= nal_size;
			naldmx_check_timestamp_switch(ctx, &nalu_store_before, nal_size, &drop_packet, pck);
			continue;
		}

		if (check_dep) {
			if ((ctx->codecid==GF_CODECID_HEVC) && ctx->hevc_state->s_info.sps) {
				HEVC_VPS *vps;
				u32 temporal_id = nal_data[1] & 0x7;
				vps = & ctx->hevc_state->vps[ctx->hevc_state->s_info.sps->vps_id];
				if (temporal_id + 1 < vps->max_sub_layers) {
					nal_ref_idc = GF_TRUE;
				}
			} else if (ctx->codecid==GF_CODECID_VVC) {
				if (ctx->vvc_state->s_info.non_ref_pic) {
					nal_ref_idc = GF_FALSE;
				} else {
					nal_ref_idc = GF_TRUE;
				}
			}
		}


		if (is_islice) ctx->has_islice = GF_TRUE;

		if (ctx->codecid==GF_CODECID_HEVC) {
#ifndef GPAC_DISABLE_HEVC
			slice_is_idr = gf_hevc_slice_is_IDR(ctx->hevc_state);

			recovery_point_valid = ctx->hevc_state->sei.recovery_point.valid;
			recovery_point_frame_cnt = ctx->hevc_state->sei.recovery_point.frame_cnt;
			bIntraSlice = gf_hevc_slice_is_intra(ctx->hevc_state);

			au_sap_type = GF_FILTER_SAP_NONE;
			if (gf_hevc_slice_is_IDR(ctx->hevc_state)) {
				au_sap_type = GF_FILTER_SAP_1;
			}
			else {
				switch (ctx->hevc_state->s_info.nal_unit_type) {
				case GF_HEVC_NALU_SLICE_BLA_W_LP:
				case GF_HEVC_NALU_SLICE_BLA_W_DLP:
					au_sap_type = GF_FILTER_SAP_3;
					break;
				case GF_HEVC_NALU_SLICE_BLA_N_LP:
					au_sap_type = GF_FILTER_SAP_1;
					break;
				case GF_HEVC_NALU_SLICE_CRA:
					au_sap_type = GF_FILTER_SAP_3;
					break;
				}
			}

			slice_poc = ctx->hevc_state->s_info.poc;

			switch (ctx->hevc_state->s_info.slice_type) {
			case GF_AVC_TYPE_B:
			case GF_AVC_TYPE2_B:
				slice_is_b = GF_TRUE;
				break;
			}
#endif
		} else if (ctx->codecid==GF_CODECID_VVC) {
			slice_is_idr = gf_vvc_slice_is_ref(ctx->vvc_state);
			recovery_point_valid = ctx->vvc_state->s_info.recovery_point_valid;
			recovery_point_frame_cnt = ctx->vvc_state->s_info.gdr_recovery_count;

			au_sap_type = GF_FILTER_SAP_NONE;
			if (ctx->vvc_state->s_info.irap_or_gdr_pic && !ctx->vvc_state->s_info.gdr_pic) {
				bIntraSlice = GF_TRUE;

				switch (ctx->vvc_state->s_info.nal_unit_type) {
				case GF_VVC_NALU_SLICE_CRA:
					au_sap_type = GF_FILTER_SAP_3;
					slice_is_idr = GF_FALSE;
					break;
				case GF_VVC_NALU_SLICE_IDR_N_LP:
					au_sap_type = GF_FILTER_SAP_1;
					break;
				case GF_VVC_NALU_SLICE_IDR_W_RADL:
					au_sap_type = GF_FILTER_SAP_2;
					slice_is_idr = GF_TRUE;
					break;
				}
			} else {
				switch (ctx->vvc_state->s_info.nal_unit_type) {
				case GF_VVC_NALU_SLICE_IDR_N_LP:
					au_sap_type = GF_FILTER_SAP_1;
					slice_is_idr = GF_TRUE;
					bIntraSlice = GF_TRUE;
					break;
				case GF_VVC_NALU_SLICE_CRA:
					au_sap_type = GF_FILTER_SAP_3;
					bIntraSlice = GF_TRUE;
					break;
				case GF_VVC_NALU_SLICE_IDR_W_RADL:
					bIntraSlice = GF_TRUE;
					if (ctx->vvc_state->s_info.gdr_pic) {
						au_sap_type = GF_FILTER_SAP_3;
					} else {
						au_sap_type = GF_FILTER_SAP_1;
						slice_is_idr = GF_TRUE;
					}
					break;
				}
			}

			slice_poc = ctx->vvc_state->s_info.poc;

			switch (ctx->vvc_state->s_info.slice_type) {
			case GF_AVC_TYPE_B:
			case GF_AVC_TYPE2_B:
				slice_is_b = GF_TRUE;
				break;
			}
		} else {

			if ((nal_type==GF_AVC_NALU_SVC_PREFIX_NALU) || (nal_type==GF_AVC_NALU_SVC_SLICE)) {
				if (!ctx->is_mvc) {
					unsigned char *p = (unsigned char *) start;
					avc_svc_subs_reserved |= (p[0] & 0x60) ? 0x80000000 : 0;
					avc_svc_subs_reserved |= (0) ? 0x40000000 : 0;
					avc_svc_subs_reserved |= (1<=nal_type && nal_type<=5) || (nal_type==GF_AVC_NALU_SVC_PREFIX_NALU) || (nal_type==GF_AVC_NALU_SVC_SLICE) ? 0x20000000 : 0;
					avc_svc_subs_reserved |= p[1] << 16;
					avc_svc_subs_reserved |= p[2] << 8;
					avc_svc_subs_reserved |= p[3] & 0xFC;
					avc_svc_subs_reserved |= (0) ? 0x00000002 : 0;

					avc_svc_subs_priority = (63 - (p[1] & 0x3F)) << 2;
				}
				if (nal_type==GF_AVC_NALU_SVC_PREFIX_NALU) {
                    if (ctx->svc_prefix_buffer_size) {
                        GF_LOG(GF_LOG_WARNING, GF_LOG_MEDIA, ("[%s] broken bitstream, two consecutive SVC prefix NALU without SVC slice in-between\n", ctx->log_name));
                        ctx->svc_prefix_buffer_size = 0;
                    }

					ctx->svc_nalu_prefix_reserved = avc_svc_subs_reserved;
					ctx->svc_nalu_prefix_priority = avc_svc_subs_priority;

					ctx->svc_prefix_buffer_size = nal_size;
					if (ctx->svc_prefix_buffer_size > ctx->svc_prefix_buffer_alloc) {
						ctx->svc_prefix_buffer_alloc = ctx->svc_prefix_buffer_size;
						ctx->svc_prefix_buffer = gf_realloc(ctx->svc_prefix_buffer, ctx->svc_prefix_buffer_size);
					}
					memcpy(ctx->svc_prefix_buffer, start+sc_size, ctx->svc_prefix_buffer_size);

					assert( (u32) remain >= sc_size + nal_size);
					start += sc_size + nal_size;
					remain -= sc_size + nal_size;
					continue;
				}
			} else if (is_slice) {
				avc_svc_subs_reserved |= (start[0] & 0x60) ? 0x80000000 : 0;
				avc_svc_subs_reserved |= (1<=nal_type && nal_type<=5) || (nal_type==GF_AVC_NALU_SVC_PREFIX_NALU) || (nal_type==GF_AVC_NALU_SVC_SLICE) ? 0x20000000 : 0;
				avc_svc_subs_priority = 0;
			}

			if (is_slice && ctx->avc_state->s_info.field_pic_flag) {
				ctx->is_paff = GF_TRUE;
				bottom_field_flag = ctx->avc_state->s_info.bottom_field_flag;
			}

			slice_is_idr = (ctx->avc_state->s_info.nal_unit_type==GF_AVC_NALU_IDR_SLICE) ? GF_TRUE : GF_FALSE;

			recovery_point_valid = ctx->avc_state->sei.recovery_point.valid;
			recovery_point_frame_cnt = ctx->avc_state->sei.recovery_point.frame_cnt;
			bIntraSlice = gf_avc_slice_is_intra(ctx->avc_state);

			au_sap_type = GF_FILTER_SAP_NONE;
			if (ctx->avc_state->s_info.nal_unit_type == GF_AVC_NALU_IDR_SLICE)
				au_sap_type = GF_FILTER_SAP_1;

			slice_poc = ctx->avc_state->s_info.poc;
			switch (ctx->avc_state->s_info.slice_type) {
			case GF_AVC_TYPE_B:
			case GF_AVC_TYPE2_B:
				slice_is_b = GF_TRUE;
				break;
			}
		}

		if (is_slice) {
			Bool first_in_au = ctx->first_slice_in_au;

			if (slice_is_idr)
				ctx->nb_idr++;

			if (au_sap_type==GF_FILTER_SAP_3)
				ctx->nb_cra++;

			slice_force_ref = GF_FALSE;

			if (ctx->first_slice_in_au) {
				ctx->first_slice_in_au = GF_FALSE;
				if (recovery_point_valid) {
					ctx->sei_recovery_frame_count = recovery_point_frame_cnt;

					if (!recovery_point_frame_cnt && bIntraSlice) {
						ctx->has_islice = 1;
						if (ctx->use_opengop_gdr == 1) {
							ctx->use_opengop_gdr = 2;
							GF_LOG(GF_LOG_WARNING, GF_LOG_MEDIA, ("[%s] No valid SEI Recovery Point found although needed - forcing\n", ctx->log_name));
						}
					}
					if (ctx->codecid==GF_CODECID_HEVC) {
						ctx->hevc_state->sei.recovery_point.valid = 0;
					} else if (ctx->codecid==GF_CODECID_VVC) {
						ctx->vvc_state->s_info.recovery_point_valid = 0;
					} else {
						ctx->avc_state->sei.recovery_point.valid = 0;
					}
					if (bIntraSlice && ctx->force_sync && (ctx->sei_recovery_frame_count==0))
						slice_force_ref = GF_TRUE;
				}
				ctx->au_sap = au_sap_type;
				ctx->bottom_field_flag = bottom_field_flag;
			}

			if (slice_poc < ctx->poc_shift) {

				u32 i, count = gf_list_count(ctx->pck_queue);
				for (i=0; i<count; i++) {
					u64 dts, cts;
					GF_FilterPacket *q_pck = gf_list_get(ctx->pck_queue, i);
					assert(q_pck);
					dts = gf_filter_pck_get_dts(q_pck);
					if (dts == GF_FILTER_NO_TS) continue;
					cts = gf_filter_pck_get_cts(q_pck);
					cts += ctx->poc_shift;
					cts -= slice_poc;
					gf_filter_pck_set_cts(q_pck, cts);
				}

				ctx->poc_shift = slice_poc;
			}

			if (slice_poc != ctx->last_poc) {
				s32 pdiff = ABS(ctx->last_poc - slice_poc);

				if ((slice_poc < 0) && !ctx->last_poc)
					ctx->poc_diff = 0;
				else if ((slice_poc < 0) && (-slice_poc < ctx->poc_diff)) {
					pdiff = -slice_poc;
					ctx->poc_diff = 0;
				}

				if (!ctx->poc_diff || (ctx->poc_diff > (s32) pdiff ) ) {
					ctx->poc_diff = pdiff;
					ctx->poc_probe_done = GF_FALSE;
				} else if (first_in_au) {
					ctx->poc_probe_done = GF_TRUE;
				}
				ctx->last_poc = slice_poc;
			}
			GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[%s] POC is %d - min poc diff %d - slice is IDR %d (SAP %d)\n", ctx->log_name, slice_poc, ctx->poc_diff, slice_is_idr, au_sap_type));

			if (slice_is_idr) {
				if (first_in_au) {
					Bool temp_poc_diff = GF_FALSE;
					if (ctx->last_frame_is_idr && !ctx->poc_diff) {
						temp_poc_diff = GF_TRUE;
						ctx->poc_diff = 1;
					}
					naludmx_enqueue_or_dispatch(ctx, NULL, GF_TRUE);

					if ((au_sap_type == GF_FILTER_SAP_2) && (ctx->max_last_poc >= ctx->last_poc) ){
						ctx->au_sap2_poc_reset = GF_TRUE;
					}

					if ((au_sap_type == GF_FILTER_SAP_1) || ctx->au_sap2_poc_reset) {
						if (!ctx->au_sap2_poc_reset)
							ctx->last_poc = 0;

						ctx->max_last_poc = ctx->last_poc;
						ctx->max_last_b_poc = ctx->last_poc;
						ctx->poc_shift = 0;
						ctx->poc_probe_done = 0;
					}
					ctx->last_frame_is_idr = GF_TRUE;
					if (temp_poc_diff)
						ctx->poc_diff = 0;
				}
			}
			else if (slice_force_ref) {
				ctx->last_frame_is_idr = GF_FALSE;
				if (first_in_au) {
					naludmx_enqueue_or_dispatch(ctx, NULL, GF_TRUE);

					ctx->poc_shift = slice_poc;

					ctx->poc_probe_done = 0;
				}
			}
			else if (ctx->max_last_poc < ctx->last_poc) {
				ctx->max_last_b_poc = 0;
				ctx->max_last_poc = ctx->last_poc;
				ctx->last_frame_is_idr = GF_FALSE;
			}
			else if (slice_is_b && (ctx->max_last_poc > ctx->last_poc)) {
				ctx->last_frame_is_idr = GF_FALSE;
				if (!ctx->max_last_b_poc) {
					ctx->max_last_b_poc = ctx->last_poc;
				}
				else if (ctx->last_poc > ctx->max_last_b_poc) {
					ctx->max_last_b_poc = ctx->last_poc;
				}
			} else {
				ctx->last_frame_is_idr = GF_FALSE;
			}


			if (ctx->deps) {
				if (nal_ref_idc) {
					ctx->has_ref_slices = GF_TRUE;
				}
				if ((ctx->codecid==GF_CODECID_AVC) && (ctx->avc_state->s_info.redundant_pic_cnt) ) {
					ctx->has_redundant = GF_TRUE;
				}
			}
		}


		au_start = ctx->first_pck_in_au ? GF_FALSE : GF_TRUE;

		if (ctx->has_initial_aud) {
			u32 audelim_size = (ctx->codecid!=GF_CODECID_AVC) ? 3 : 2;
			naludmx_start_nalu(ctx, audelim_size, GF_FALSE, &au_start, &pck_data);
			memcpy(pck_data + ctx->nal_length , ctx->init_aud, audelim_size);
			ctx->has_initial_aud = GF_FALSE;
			if (ctx->subsamples) {
				naludmx_add_subsample(ctx, audelim_size, avc_svc_subs_priority, avc_svc_subs_reserved);
			}
		}
		if (ctx->sei_buffer_size) {
			naludmx_start_nalu(ctx, ctx->sei_buffer_size, GF_TRUE, &au_start, &pck_data);
			memcpy(pck_data, ctx->sei_buffer, ctx->sei_buffer_size);
			if (ctx->subsamples) {
				naludmx_add_subsample(ctx, ctx->sei_buffer_size - ctx->nal_length, avc_svc_subs_priority, avc_svc_subs_reserved);
			}
			ctx->sei_buffer_size = 0;
		}

		if (ctx->svc_prefix_buffer_size) {
			naludmx_start_nalu(ctx, ctx->svc_prefix_buffer_size, GF_FALSE, &au_start, &pck_data);
			memcpy(pck_data + ctx->nal_length, ctx->svc_prefix_buffer, ctx->svc_prefix_buffer_size);
			if (ctx->subsamples) {
				naludmx_add_subsample(ctx, ctx->svc_prefix_buffer_size, ctx->svc_nalu_prefix_priority, ctx->svc_nalu_prefix_reserved);
			}
			ctx->svc_prefix_buffer_size = 0;
		}

		naludmx_start_nalu(ctx, (u32) nal_size, GF_FALSE, &au_start, &pck_data);
		pck_data += ctx->nal_length;

		if (ctx->subsamples) {
			naludmx_add_subsample(ctx, (u32) nal_size, avc_svc_subs_priority, avc_svc_subs_reserved);
		}


		memcpy(pck_data, nal_data, (size_t) nal_size);

		nal_size += sc_size;
		start += nal_size;
		remain -= nal_size;
		naldmx_check_timestamp_switch(ctx, &nalu_store_before, nal_size, &drop_packet, pck);

		if (remain && gf_filter_pid_would_block(ctx->opid)) {
			ctx->resume_from = (u32) (start - ctx->nal_store);
			assert(ctx->resume_from <= ctx->nal_store_size);
			assert(ctx->resume_from == ctx->nal_store_size - remain);
			if (drop_packet)
				gf_filter_pid_drop_packet(ctx->ipid);
			return GF_OK;
		}
	}

	if (remain) {
		if (is_eos && (remain == ctx->nal_store_size)) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_MEDIA, ("[%s] Incomplete last NAL and eos, discarding\n", ctx->log_name));
			remain = 0;
		} else {
			assert((u32) remain<=ctx->nal_store_size);
			memmove(ctx->nal_store, start, remain);
		}
	}
	ctx->nal_store_size = remain;

	if (drop_packet)
		gf_filter_pid_drop_packet(ctx->ipid);

	if (is_eos)
		return naludmx_process(filter);

	if ((ctx->nb_nalus>nalu_before) && gf_filter_reporting_enabled(filter)) {
		char szStatus[1024];

		sprintf(szStatus, "%s %dx%d % 10d NALU % 8d I % 8d P % 8d B % 8d SEI", ctx->log_name, ctx->width, ctx->height, ctx->nb_nalus, ctx->nb_i, ctx->nb_p, ctx->nb_b, ctx->nb_sei);
		gf_filter_update_status(filter, -1, szStatus);
	}
	if (ctx->full_au_source && ctx->poc_probe_done) {
		if (ctx->first_pck_in_au)
			naludmx_finalize_au_flags(ctx);

		naludmx_enqueue_or_dispatch(ctx, NULL, GF_TRUE);
	}
	return GF_OK;
}

void gf_filter_process_task(GF_FSTask *task)
{
	GF_Err e;
	Bool skip_block_mode = GF_FALSE;
	GF_Filter *filter = task->filter;
	Bool force_block_state_check=GF_FALSE;
	assert(task->filter);
	assert(filter->freg);
	assert(filter->freg->process);
	task->can_swap = 1;

	filter->schedule_next_time = 0;

	if (filter->disabled) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s is disabled, cancelling process\n", filter->name));
		gf_mx_p(task->filter->tasks_mx);
		task->filter->process_task_queued = 0;
		gf_mx_v(task->filter->tasks_mx);
		return;
	}

	if (filter->out_pid_connection_pending || filter->detached_pid_inst || filter->caps_negociate) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s has %s pending, requeuing process\n", filter->name, filter->out_pid_connection_pending ? "connections" : filter->caps_negociate ? "caps negociation" : "input pid reassignments"));
		task->requeue_request = GF_TRUE;

 		assert(filter->process_task_queued);
		if (!filter->out_pid_connection_pending) {
			task->schedule_next_time = gf_sys_clock_high_res() + 10000;
			check_filter_error(filter, GF_OK, GF_TRUE);
		}
		return;
	}
	if (filter->removed || filter->finalized) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s has been %s, skipping process\n", filter->name, filter->finalized ? "finalized" : "removed"));
		return;
	}

	if (filter->prevent_blocking) skip_block_mode = GF_TRUE;
	else if (filter->session->in_final_flush) skip_block_mode = GF_TRUE;

	if (!skip_block_mode && filter->would_block && (filter->would_block + filter->num_out_pids_not_connected == filter->num_output_pids ) ) {
		gf_mx_p(task->filter->tasks_mx);
		if (filter->would_block) {
			filter->nb_tasks_done--;
			task->filter->process_task_queued = 0;
			GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s blocked, skipping process\n", filter->name));
			gf_mx_v(task->filter->tasks_mx);
			return;
		}
		gf_mx_v(task->filter->tasks_mx);
	}
	if (filter->stream_reset_pending) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s has stream reset pending, postponing process\n", filter->name));
		filter->nb_tasks_done--;
		task->requeue_request = GF_TRUE;
		assert(filter->process_task_queued);
		return;
	}
	assert(filter->process_task_queued);
	assert(!filter->multi_sink_target);

	if (task->filter->postponed_packets) {
		while (gf_list_count(task->filter->postponed_packets)) {
			GF_FilterPacket *pck = gf_list_pop_front(task->filter->postponed_packets);
			e = gf_filter_pck_send_internal(pck, GF_FALSE);
			if (e==GF_PENDING_PACKET) {
				gf_list_del_item(task->filter->postponed_packets, pck);
				gf_list_insert(task->filter->postponed_packets, pck, 0);
				task->requeue_request = GF_TRUE;
				GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s still has postponed packets, postponing process\n", filter->name));
				return;
			}
		}
		gf_list_del(task->filter->postponed_packets);
		task->filter->postponed_packets = NULL;
	}
	FSESS_CHECK_THREAD(filter)

	filter->nb_pck_io = 0;

	if (filter->nb_caps_renegociate) {
		gf_filter_renegociate_output(filter, GF_FALSE);
	}

	GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("Filter %s process\n", filter->name));
	gf_rmt_begin_hash(filter->name, GF_RMT_AGGREGATE, &filter->rmt_hash);

	filter->in_process_callback = GF_TRUE;

#ifdef GPAC_MEMORY_TRACKING
	if (filter->session->check_allocs)
		e = gf_filter_process_check_alloc(filter);
	else
#endif
		e = filter->freg->process(filter);

	filter->in_process_callback = GF_FALSE;
	gf_rmt_end();

	if (filter->has_pending_pids) {
		filter->has_pending_pids=GF_FALSE;
		while (gf_fq_count(filter->pending_pids)) {
			GF_FilterPid *pid=gf_fq_pop(filter->pending_pids);
			gf_filter_pid_post_init_task(filter, pid);
		}
	}
	if (session_should_abort(filter->session)) {
		return;
	}
	if (e==GF_EOS) {
		if (filter->postponed_packets) {
		 	e = GF_OK;
		} else if (filter->process_task_queued) {
			e = GF_OK;
			force_block_state_check = GF_TRUE;
		}
	}

	if ((e==GF_EOS) || filter->removed || filter->finalized) {
		gf_mx_p(filter->tasks_mx);
		filter->process_task_queued = 0;
		gf_mx_v(filter->tasks_mx);
		return;
	}

	if ((e==GF_PROFILE_NOT_SUPPORTED) && filter->has_out_caps && !(filter->session->flags & GF_FS_FLAG_NO_REASSIGN)) {
		u32 i;
		gf_mx_p(filter->tasks_mx);
		for (i=0; i<filter->num_input_pids; i++) {
			GF_FilterPidInst *a_pidinst = gf_list_get(filter->input_pids, i);

			GF_LOG(GF_LOG_WARNING, GF_LOG_FILTER, ("Codec/Profile not supported for filter %s - blacklisting as output from %s and retrying connections\n", filter->name, a_pidinst->pid->filter->name));

			gf_list_add(a_pidinst->pid->filter->blacklisted, (void *) filter->freg);

			gf_filter_relink_dst(a_pidinst);
		}
		filter->process_task_queued = 0;
		gf_mx_v(filter->tasks_mx);
		return;
	}
	check_filter_error(filter, e, GF_FALSE);

	if ( (!filter->num_output_pids || (filter->would_block + filter->num_out_pids_not_connected < filter->num_output_pids) )
		&& !filter->input_pids
		&& (e!=GF_EOS)
		&& !force_block_state_check
	) {
		if (filter->schedule_next_time)
			task->schedule_next_time = filter->schedule_next_time;
		task->requeue_request = GF_TRUE;
		assert(filter->process_task_queued);
	}
	else if (filter->schedule_next_time) {
		if (!filter->session->in_final_flush) {
			task->schedule_next_time = filter->schedule_next_time;
			task->requeue_request = GF_TRUE;
			assert(filter->process_task_queued);
		}
	}
	else if ((filter->would_block < filter->num_output_pids)
			&& filter->pending_packets
			&& (gf_fq_count(filter->tasks)<=1)
	) {
		if (filter->pending_packets && filter->session->in_final_flush) {
			u32 i;
			for (i=0; i<filter->num_input_pids; i++) {
				GF_FilterPidInst *pidi = gf_list_get(filter->input_pids, i);
				gf_filter_pid_get_packet((GF_FilterPid *)pidi);
			}
			if (!filter->num_input_pids)
				filter->pending_packets = 0;
		}
		task->requeue_request = GF_TRUE;
		task->can_swap = 2;
		assert(filter->process_task_queued);
	}
	else {
		assert (!filter->schedule_next_time);
		gf_filter_check_pending_tasks(filter, task);
		if (task->requeue_request) {
			task->can_swap = 2;
			assert(filter->process_task_queued);
		}
	}
}

void test(void)
{
	GF_FilterSession session;
	GF_Filter src_filter;
	GF_Filter dst_filter;
	GF_NALUDmxCtx ctx;
	GF_FilterPid src_pid;
	GF_FilterPid *saved_ipid;
	GF_FSTask task;

	memset(&session, 0, sizeof(session));
	memset(&src_filter, 0, sizeof(src_filter));
	memset(&dst_filter, 0, sizeof(dst_filter));
	memset(&ctx, 0, sizeof(ctx));
	memset(&src_pid, 0, sizeof(src_pid));
	memset(&task, 0, sizeof(task));

	src_filter.session = &session;
	src_filter.name = "src";
	src_filter.tasks_mx = gf_mx_new("src");

	dst_filter.session = &session;
	dst_filter.freg = &NALUDmxRegister;
	dst_filter.filter_udta = &ctx;
	dst_filter.name = "rfnalu";
	dst_filter.tasks_mx = gf_mx_new("rfnalu");

	src_pid.filter = &src_filter;
	src_pid.name = "src_pid";
	src_pid.destinations = gf_list_new();

	ctx.is_playing = GF_TRUE;
	ctx.dv_mode = DVMODE_AUTO;
	ctx.dv_profile = 8;
	ctx.width = 1920;
	ctx.height = 1080;
	ctx.cur_fps.num = 25;
	ctx.cur_fps.den = 1;
	ctx.codecid = GF_CODECID_HEVC;

	gf_filter_pid_configure(&dst_filter, &src_pid, GF_PID_CONF_CONNECT);
	saved_ipid = ctx.ipid;

	gf_filter_pid_configure(&dst_filter, &src_pid, GF_PID_CONF_REMOVE);

	ctx.ipid = saved_ipid;

	task.filter = &dst_filter;
	dst_filter.process_task_queued = 1;
	gf_filter_process_task(&task);
}
