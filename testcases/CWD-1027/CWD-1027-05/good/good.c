#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

typedef int Bool;

typedef float Float;
typedef Float Fixed;
typedef double Double;

#define GF_TRUE 1
#define GF_FALSE 0

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
    GF_IP_UDP_TIMEOUT = -46,
    GF_AUTHENTICATION_FAILURE = -50,
    GF_NOT_READY = -51,
    GF_PENDING_PACKET = 2,
    GF_EOS = 1,
} GF_Err;

typedef enum {
    GF_LOG_QUIET = 0,
    GF_LOG_ERROR,
    GF_LOG_WARNING,
    GF_LOG_INFO,
    GF_LOG_DEBUG
} GF_LOG_Level;

typedef enum {
    GF_LOG_CORE = 0,
    GF_LOG_CODING,
    GF_LOG_CONTAINER,
    GF_LOG_NETWORK,
    GF_LOG_HTTP,
    GF_LOG_RTP,
    GF_LOG_CODEC,
    GF_LOG_PARSER,
    GF_LOG_MEDIA,
    GF_LOG_SCENE,
    GF_LOG_SCRIPT,
    GF_LOG_INTERACT,
    GF_LOG_COMPOSE,
    GF_LOG_COMPTIME,
    GF_LOG_CACHE,
    GF_LOG_MMIO,
    GF_LOG_RTI,
    GF_LOG_MEMORY,
    GF_LOG_AUDIO,
    GF_LOG_FILTER,
} GF_LOG_Tool;

#define GF_EXPORT __attribute__((visibility("default")))

#define gf_fatal_assert(_cond) if (! (_cond)) { fprintf(stderr, "Fatal error " #_cond " file %s line %d, exiting\n", __FILE__, __LINE__ ); exit(10); }
#define gf_assert(_cond) assert(_cond)

#define gf_mx_p(_mx) 1
#define gf_mx_v(_mx)

#define safe_int_inc(__v) __atomic_add_fetch((int *) (__v), 1, __ATOMIC_SEQ_CST)
#define safe_int_dec(__v) __atomic_sub_fetch((int *) (__v), 1, __ATOMIC_SEQ_CST)

#define GF_LOG(_log_level, _log_tools, __args)

typedef struct tagIS {
    void *data;
    struct tagIS *next;
} ItemSlot;

typedef struct _tag_array {
    void **slots;
    u32 entryCount;
    u32 allocSize;
} GF_List;

typedef struct __gf_filter_queue {
    void *items;
    u32 head;
    u32 tail;
    u32 count;
    u32 capacity;
    const void *mx;
} GF_FilterQueue;

typedef struct {
	s32 num;
	u32 den;
} GF_Fraction;

typedef struct _tag_fraction64 {
    s64 num;
    u32 den;
} GF_Fraction64;

typedef struct
{
	/*! x coord */
	s32 x;
	/*! y coord */
	s32 y;
} GF_PropVec2i;

typedef struct
{
	/*! x coord */
	Double x;
	/*! y coord */
	Double y;
} GF_PropVec2;

typedef struct
{
	/*! x coord */
	s32 x;
	/*! y coord */
	s32 y;
	/*! z coord */
	s32 z;
} GF_PropVec3i;

typedef struct
{
	/*! x coord */
	s32 x;
	/*! y coord */
	s32 y;
	/*! z coord */
	s32 z;
	/*! w coord */
	s32 w;
} GF_PropVec4i;

typedef struct
{
	/*! array of unsigned integers */
	char **vals;
	/*! number of items in array */
	u32 nb_items;
} GF_PropStringList;


/*! List of unsigned int property - do not change field order !*/
typedef struct
{
	/*! array of unsigned integers */
	u32 *vals;
	/*! number of items in array */
	u32 nb_items;
} GF_PropUIntList;

/*! List of signed int property - do not change field order !*/
typedef struct
{
	/*! array of signed integers */
	s32 *vals;
	/*! number of items in array */
	u32 nb_items;
} GF_PropIntList;

/*! List of unsigned int property*/
typedef struct
{
	/*! array of vec2i  */
	GF_PropVec2i *vals;
	/*! number of items in array */
	u32 nb_items;
} GF_PropVec2iList;

/*! Data property*/
typedef struct
{
	/*! data pointer */
	u8 *ptr;
	/*! data size */
	u32 size;
} GF_PropData;

typedef struct __gf_filter GF_Filter;

typedef struct __gf_filter_session {
    u32 flags;
    Bool use_locks;
    Bool direct_mode;
    volatile u32 tasks_in_process;
    Bool requires_solved_graph;
    u32 non_blocking;
    GF_List *registry;
    GF_List *filters;
    GF_FilterQueue *tasks;
    GF_FilterQueue *main_thread_tasks;
    GF_FilterQueue *tasks_reservoir;
    volatile Bool in_main_sem_wait;
    volatile u32 active_threads;
    void *filters_mx;
    GF_FilterQueue *prop_maps_reservoir;
    GF_FilterQueue *prop_maps_entry_reservoir;
    GF_FilterQueue *prop_maps_entry_data_alloc_reservoir;
    GF_FilterQueue *pcks_refprops_reservoir;
    void *props_mx;
    void *info_mx;
    void *ui_mx;
    GF_List *threads;
    void *main_th;
    void *tasks_mx;
    void *semaphore_main;
    void *semaphore_other;
    volatile u32 tasks_pending;
    u32 nb_threads_stopped;
    GF_Err run_status;
    u32 blocking_mode;
    Bool in_final_flush;
    Bool reporting_on;
    void *ui_opaque;
    Bool (*ui_event_proc)(void *opaque, void *event);
    volatile u32 pid_connect_tasks_pending;
    GF_List *event_listeners;
    void *evt_mx;
    u32 in_event_listener;
    void *download_manager;
    void *font_manager;
    u32 default_pid_buffer_max_us, decoder_pid_buffer_max_us;
    u32 default_pid_buffer_max_units;
    Bool check_allocs;
    u32 nb_alloc_pck, nb_realloc_pck;
    GF_Err last_connect_error, last_process_error;
    void *caps;
    u64 hint_clock_us;
    GF_Fraction64 hint_timestamp;
    u32 max_resolve_chain_len;
    u32 max_sleep;
    void *links_mx;
    GF_List *links;
    GF_List *parsed_args;
    char sep_args, sep_name, sep_frag, sep_list, sep_neg;
    char *blacklist;
    Bool init_done;
    GF_List *auto_inc_nums;
    GF_List *gl_providers;
    volatile u32 nb_gl_filters;
    void *gl_driver;
    void *js_ctx;
    GF_List *jstasks;
    void *new_f_task, *del_f_task, *on_evt_task, *on_auth_task;
    void (*on_filter_create_destroy)(void *udta, GF_Filter *filter, Bool is_destroy);
    void *rt_udta;
    Bool force_main_thread_tasks;
    void *ext_gl_udta;
    void (*ext_gl_callback)(void *udta, Bool do_activate);
    GF_List *uri_relocators;
    void *locales;
    Bool is_worker;
    volatile u32 pending_threads;
    u32 dbg_flags;
} GF_FilterSession;
typedef struct __gf_filter_pid GF_FilterPid;
typedef struct __gf_filter_pck GF_FilterPacket;
typedef struct __gf_filter_pid_inst GF_FilterPidInst;

typedef struct
{
#if 0
    GF_List *hash_table[0];
#else
    GF_List *properties;
#endif
    volatile u32 reference_count;
    volatile u32 pckrefs_reference_count;
    GF_FilterSession *session;
    u32 timescale;
} GF_PropertyMap;

typedef enum {
    GF_FILTER_CLOCK_TYPE_NONE = 0,
    GF_FILTER_CLOCK_TYPE_SYSTEM,
    GF_FILTER_CLOCK_TYPE_MEDIA,
} GF_FilterClockType;

struct __gf_filter_pid_inst
{
    struct __gf_filter_pid *pid;
    GF_Filter *filter;
    GF_PropertyMap *props;
    GF_FilterQueue *packets;
    void *pck_mx;
    GF_List *pck_reassembly;
    Bool requires_full_data_block;
    Bool last_block_ended;
    Bool first_block_started;
    volatile u32 discard_packets;
    Bool force_reconfig;
    u32 discard_inputs;
    volatile s64 buffer_duration;
    volatile s32 detach_pending;
    Bool force_flush;
    void *udta;
    u32 udta_flags;
    u64 last_pck_fetch_time;
    u64 stats_start_ts, stats_start_us;
    u32 cur_bit_size, avg_bit_rate, max_bit_rate, avg_process_rate, max_process_rate;
    u32 nb_processed, nb_sap_processed, nb_reagg_pck;
    u64 total_process_time, total_sap_process_time;
    u64 max_process_time, max_sap_process_time;
    u64 first_frame_time;
    Bool is_end_of_stream;
    Bool keepalive_signaled;
    Bool is_playing, is_paused;
    u8 play_queued, stop_queued;
    volatile u32 nb_eos_signaled;
    Bool is_encoder_input;
    Bool is_decoder_input;
    GF_PropertyMap *reconfig_pid_props;
    Bool handles_clock_references;
    volatile u32 nb_clocks_signaled;
    u64 last_clock_value;
    u32 last_clock_timescale;
    GF_FilterClockType last_clock_type;
    GF_Filter *alias_orig;
    GF_Fraction64 last_ts_drop;
    u64 last_buf_query_clock;
    u64 last_buf_query_dur;
    u64 last_rt_report;
    u32 rtt;
    u32 jitter;
    u32 loss_rate;
};

typedef struct __gf_filter_queue GF_FilterQueue;

struct __gf_filter_pid
{
    struct __gf_filter_pid *pid;
    GF_Filter *filter;
    char *name;
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
    volatile u32 init_task_pending;
    volatile Bool props_changed_since_connect;
    volatile u32 nb_shared_packets_out;
    GF_PropertyMap *infos;
    Bool has_seen_eos;
    Bool eos_keepalive;
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
    GF_PropertyMap *caps_negotiate;
    Bool caps_negotiate_direct;
    GF_List *caps_negotiate_pidi_list;
    GF_List *adapters_blacklist;
    GF_Filter *caps_dst_filter;
    Bool ext_not_trusted;
    Bool user_buffer_forced;
    Bool require_source_id;
    GF_PropertyMap *local_props;
    volatile u32 num_pidinst_del_pending;
    u32 link_flags;
};

struct __gf_filter
{
    const void *freg;
    char *name;
    char *id;
    char *source_ids;
    char *dynamic_source_ids;
    char *restricted_source_id;
    GF_FilterSession *session;
    u32 max_extra_pids;
    volatile u32 nb_sparse_pids;
    u32 subsession_id, subsource_id;
    Bool (*on_setup_error)(GF_Filter *f, void *on_setup_error_udta, GF_Err e);
    void *on_setup_error_udta;
    GF_Filter *on_setup_error_filter;
    char *orig_args;
    u32 arg_type;
    char *src_args;
    char *dst_args;
    char *tag;
    char *itag;
    char *netcap_id;
    GF_FilterQueue *tasks;
    volatile Bool scheduled_for_next_task;
    volatile Bool in_process;
    u32 process_th_id, restrict_th_idx;
    void *filter_udta;
    Bool has_out_caps;
    Bool in_force_flush;
    u32 disabled;
    Bool in_process_callback;
    Bool no_probe;
    Bool no_inputs;
    Bool is_blocking_source;
    u32 force_demux;
    s32 nb_pids_playing;
    GF_List *input_pids;
    u32 num_input_pids;
    GF_List *output_pids;
    u32 num_output_pids;
    u32 num_out_pids_not_connected;
    GF_FilterQueue *pcks_alloc_reservoir;
    GF_FilterQueue *pcks_shared_reservoir;
    GF_FilterQueue *pcks_inst_reservoir;
    void *pcks_mx;
    void *tasks_mx;
    Bool has_pending_pids;
    GF_FilterQueue *pending_pids;
    volatile u32 in_pid_connection_pending;
    volatile u32 out_pid_connection_pending;
    volatile u32 pending_packets;
    volatile u32 nb_ref_packets;
    volatile u64 ref_bytes;
    volatile u32 stream_reset_pending;
    volatile u32 num_events_queued;
    volatile u32 detach_pid_tasks_pending;
    volatile u32 nb_shared_packets_out;
    volatile u32 abort_pending;
    GF_List *postponed_packets;
    GF_List *blacklisted;
    GF_Filter *cloned_from;
    GF_Filter *dst_filter;
    GF_Filter *target_filter;
    GF_List *destination_filters;
    GF_List *destination_links;
    GF_List *temp_input_pids;
    u64 nb_tasks_done;
    u64 nb_pck_processed;
    u64 nb_bytes_processed;
    u64 nb_pck_sent;
    u64 nb_hw_pck_sent;
    u32 nb_errors;
    u64 nb_bytes_sent;
    u64 time_process;
    volatile u32 would_block;
    u32 pid_buffer_max_us, pid_buffer_max_units, pid_decode_buffer_max_us;
    Bool prevent_blocking;
    Bool in_eos_resume;
    Bool finalized;
    u32 removed;
    Bool setup_notified;
    u32 dynamic_filter;
    Bool block_eos;
    Bool marked_for_removal;
    u32 sticky;
    u32 clonable;
    Bool in_link_resolution;
    volatile u32 nb_caps_renegotiate;
    Bool process_task_queued;
    Bool reconfigure_outputs;
};

typedef enum
{
	/*! not allowed*/
	GF_PROP_FORBIDDEN	=	0,
	/*! signed 32 bit integer*/
	GF_PROP_SINT		=	1,
	/*! unsigned 32 bit integer*/
	GF_PROP_UINT		=	2,
	/*! signed 64 bit integer*/
	GF_PROP_LSINT		=	3,
	/*! unsigned 64 bit integer*/
	GF_PROP_LUINT		=	4,
	/*! boolean*/
	GF_PROP_BOOL		=	5,
	/*! 32 bit / 32 bit fraction*/
	GF_PROP_FRACTION	=	6,
	/*! 64 bit / 64 bit fraction*/
	GF_PROP_FRACTION64	=	7,
	/*! float (Fixed) number*/
	GF_PROP_FLOAT		=	8,
	/*! double number*/
	GF_PROP_DOUBLE		=	9,
	/*! 2D signed integer vector*/
	GF_PROP_VEC2I		=	10,
	/*! 2D double number vector*/
	GF_PROP_VEC2		=	11,
	/*! 3D signed integer vector*/
	GF_PROP_VEC3I		=	12,
	/*! 4D signed integer vector*/
	GF_PROP_VEC4I		=	13,
	/*! string property, memory is duplicated when setting the property and managed internally*/
	GF_PROP_STRING		=	14,
	/*! string property, memory is NOT duplicated when setting the property but is then managed (and free) internally.
	Only used when setting a property, the type then defaults to GF_PROP_STRING
	DO NOT USE the associate string field upon return from setting the property, it might have been destroyed*/
	GF_PROP_STRING_NO_COPY=	15,
	/*! data property, memory is duplicated when setting the property and managed internally*/
	GF_PROP_DATA		=	16,
	/*! const string property, memory is NOT duplicated when setting the property, stays user-managed*/
	GF_PROP_NAME		=	17,
	/*! data property, memory is NOT duplicated when setting the property but is then managed (and free) internally.
	Only used when setting a property, the type then defaults to GF_PROP_DATA
	DO NOT USE the associate data field upon return from setting the property, it might have been destroyed*/
	GF_PROP_DATA_NO_COPY=	18,
	/*! const data property, memory is NOT duplicated when setting the property, stays user-managed*/
	GF_PROP_CONST_DATA	=	19,
	/*! user-managed pointer*/
	GF_PROP_POINTER		=	20,
	/*! string list, memory is NOT duplicated when setting the property, the passed array is directly assigned to the new property and will be and managed internally (freed by the filter session)
	DO NOT USE the associate string array field upon return from setting the property, it might have been destroyed*/
	GF_PROP_STRING_LIST	=	21,
	/*! unsigned 32 bit integer list, memory is ALWAYS duplicated when setting the property*/
	GF_PROP_UINT_LIST	=	22,
	/*! signed 32 bit integer list, memory is ALWAYS duplicated when setting the property*/
	GF_PROP_SINT_LIST	=	23,
	/*! 2D signed integer vector list, memory is ALWAYS duplicated when setting the property*/
	GF_PROP_VEC2I_LIST	=	24,
	/*! 4CC on unsigned 32 bit integer*/
	GF_PROP_4CC			=	25,
	/*! 4CC list on unsigned 32 bit integer, memory is ALWAYS duplicated when setting the property*/
	GF_PROP_4CC_LIST	=	26,
	/*! string list, memory is duplicated when setting the property - to use only with property assignment functions*/
	GF_PROP_STRING_LIST_COPY = 27,
	
	/*! last non-enum property*/
	GF_PROP_LAST_NON_ENUM,

	/*! All constants are defined after this - constants are stored as  u32*/
	GF_PROP_FIRST_ENUM	=	40, //GSF will code prop type using vlen, try to keep all values between 1 and 127 to only use 1 byte

	/*! Video Pixel format*/
	GF_PROP_PIXFMT			=	GF_PROP_FIRST_ENUM,
	/*! Audio PCM format*/
	GF_PROP_PCMFMT			=	GF_PROP_FIRST_ENUM+1,
	/*! CICP Color Primaries*/
	GF_PROP_CICP_COL_PRIM	=	GF_PROP_FIRST_ENUM+2,
	/*! CICP Color Transfer Characteristics*/
	GF_PROP_CICP_COL_TFC	=	GF_PROP_FIRST_ENUM+3,
	/*! CICP Color Matrix*/
	GF_PROP_CICP_COL_MX		=	GF_PROP_FIRST_ENUM+4,
	/*! not allowed*/
	GF_PROP_LAST_DEFINED
} GF_PropType;

typedef struct __gf_prop_val
{
	/*! type of the property */
	GF_PropType type;
	/*! union of all possible property data types */
	union {
		/*! 64 bit unsigned integer value of property */
		u64 longuint;
		/*! 64 bit signed integer value of property */
		s64 longsint;
		/*! 32 bit signed integer value of property */
		s32 sint;
		/*! 32 bit unsigned integer value of property */
		u32 uint;
		/*! boolean value of property */
		Bool boolean;
		/*! fraction (32/32 bits) value of property */
		GF_Fraction frac;
		/*! fraction (64/64 bits) value of property */
		GF_Fraction64 lfrac;
		/*! fixed number (float or 32 bit depending on compilation settings) value of property */
		Fixed fnumber;
		/*! double value of property */
		Double number;
		/*! 2D signed integer vector value of property */
		GF_PropVec2i vec2i;
		/*! 2D double vector value of property */
		GF_PropVec2 vec2;
		/*! 3D signed integer vector value of property */
		GF_PropVec3i vec3i;
		/*! 4D signed integer vector value of property */
		GF_PropVec4i vec4i;
		/*! data value of property. For non const data type, the memory is freed by filter session.
		Otherwise caller is responsible to free it at end of filter/session*/
		GF_PropData data;
		/*! string value of property. For non const string / names, the memory is freed by filter session, otherwise handled as const char *. */
		char *string;
		/*! pointer value of property */
		void *ptr;
		/*! string list value of property - memory is handled by filter session (always copy)*/
		GF_PropStringList string_list;
		/*! unsigned integer list value of property - memory is handled by filter session (always copy)*/
		GF_PropUIntList uint_list;
		/*! signed integer list value of property - memory is handled by filter session (always copy)*/
		GF_PropIntList sint_list;
		/*! vec2i list value of property - memory is handled by filter session (always copy)*/
		GF_PropVec2iList v2i_list;
	} value;
} GF_PropertyValue;

typedef struct
{
    GF_FilterSession *session;
    volatile u32 reference_count;
    u32 p4cc;
    Bool name_alloc;
    char *pname;
    GF_PropertyValue prop;
    u32 alloc_size;
} GF_PropertyEntry;

typedef Bool (*gf_filter_prop_filter)(void *cbk, u32 prop_4cc, const char *prop_name, const GF_PropertyValue *src_prop);

#define PID_IS_INPUT(__pid) ((__pid->pid==__pid) ? GF_FALSE : GF_TRUE)

void *gf_fq_pop(GF_FilterQueue *fq);
void *gf_list_last(GF_List *ptr);
void *gf_list_get(GF_List *ptr, u32 position);
GF_List *gf_list_new();
GF_Err gf_list_add(GF_List *ptr, void* item);
s32 gf_list_del_item(GF_List *ptr, void *item);

GF_PropertyMap * gf_props_new(GF_Filter *filter);
void gf_props_del(GF_PropertyMap *prop);
void gf_props_reset(GF_PropertyMap *prop);
GF_Err gf_props_merge_property(GF_PropertyMap *dst_props, GF_PropertyMap *src_props, gf_filter_prop_filter filter_prop, void *cbk);

void gf_filter_pid_set_name(GF_FilterPid *PID, const char *name);

#define MALLOC malloc
#define FREE free

GF_EXPORT
void *gf_malloc(size_t size)
{
	return MALLOC(size);
}

GF_EXPORT
void gf_free(void *ptr)
{
	FREE(ptr);
}

#define GF_SAFEALLOC(__ptr, __struct) {\
        (__ptr) = (__struct *) gf_malloc(sizeof(__struct));\
        if (__ptr) {\
            memset((void *) (__ptr), 0, sizeof(__struct));\
        }\
    }

GF_EXPORT
u32 gf_list_count(const GF_List *ptr)
{
	if (!ptr) return 0;
	return ptr->entryCount;
}

GF_EXPORT
GF_Err gf_list_rem_last(GF_List *ptr)
{
	if ( !ptr || !ptr->slots || !ptr->entryCount) return GF_BAD_PARAM;
	ptr->slots[ptr->entryCount-1] = NULL;
	ptr->entryCount -= 1;
	return GF_OK;
}

GF_EXPORT
void* gf_list_pop_back(GF_List *ptr) {
	void * item;
	if (!ptr) return NULL;

	item = gf_list_last(ptr);
	gf_list_rem_last(ptr);

	return item;
}

Bool gf_fq_res_add(GF_FilterQueue *fq, void *item);

void gf_props_del_property(GF_PropertyEntry *it)
{
	gf_assert(it->reference_count);
	if (safe_int_dec(&it->reference_count) == 0 ) {
		if (it->pname && it->name_alloc)
			gf_free(it->pname);

		it->name_alloc = GF_FALSE;

		if (it->prop.type==GF_PROP_STRING) {
			gf_free(it->prop.value.string);
			it->prop.value.string = NULL;
		}
		else if (it->prop.type==GF_PROP_DATA) {
			gf_assert(it->alloc_size);
			//DATA props are collected at session level for future reuse
		}
		//string list are destroyed
		else if (it->prop.type==GF_PROP_STRING_LIST) {
			u32 i;
			for (i=0; i<it->prop.value.string_list.nb_items; i++) {
				char *s = it->prop.value.string_list.vals[i];
				gf_free(s);
			}
			gf_free(it->prop.value.string_list.vals);
			it->prop.value.string_list.vals = NULL;
			it->prop.value.string_list.nb_items = 0;
		}
		//use uint_list as base type for list
		else if ((it->prop.type==GF_PROP_UINT_LIST) || (it->prop.type==GF_PROP_4CC_LIST) || (it->prop.type==GF_PROP_SINT_LIST) || (it->prop.type==GF_PROP_VEC2I_LIST)) {
			if (it->prop.value.uint_list.vals)
				gf_free(it->prop.value.uint_list.vals);
			it->prop.value.uint_list.nb_items = 0;
			it->prop.value.uint_list.vals = NULL;
		}
		it->prop.value.data.size = 0;
		if (it->alloc_size) {
			gf_assert(it->prop.type==GF_PROP_DATA);
			if (gf_fq_res_add(it->session->prop_maps_entry_data_alloc_reservoir, it)) {
				if (it->prop.value.data.ptr) gf_free(it->prop.value.data.ptr);
				gf_free(it);
			}
		} else {
			if (gf_fq_res_add(it->session->prop_maps_entry_reservoir, it)) {
				gf_free(it);
			}
		}
	}
}

static GF_PropertyMap *check_new_pid_props(GF_FilterPid *pid, Bool merge_props)
{
	u32 i, nb_recf;
	GF_PropertyMap *old_map;
	GF_PropertyMap *map;

	gf_mx_p(pid->filter->tasks_mx);
	old_map = gf_list_last(pid->properties);
	gf_mx_v(pid->filter->tasks_mx);

	pid->props_changed_since_connect = GF_TRUE;
	if (old_map && !pid->request_property_map) {
		return old_map;
	}
	map = gf_props_new(pid->filter);
	if (!map)
		return NULL;
	gf_mx_p(pid->filter->tasks_mx);
	gf_list_add(pid->properties, map);
	gf_mx_v(pid->filter->tasks_mx);

	pid->request_property_map = GF_FALSE;
	pid->pid_info_changed = GF_FALSE;

	if (old_map) {
		if (merge_props)
			gf_props_merge_property(map, old_map, NULL, NULL);

		gf_assert(old_map->reference_count);
		if (safe_int_dec(&old_map->reference_count) == 0) {
			gf_mx_p(pid->filter->tasks_mx);
			gf_list_del_item(pid->properties, old_map);
			gf_mx_v(pid->filter->tasks_mx);
			gf_props_del(old_map);
		}
	}

	nb_recf = 0;
	for (i=0; i<pid->num_destinations; i++) {
		GF_FilterPidInst *pidi = gf_list_get(pid->destinations, i);
		if (!pidi->filter->process_task_queued) {
			pidi->reconfig_pid_props = map;
			nb_recf++;
		}
	}
	if (nb_recf)
		pid->filter->reconfigure_outputs = GF_TRUE;
	return map;
}

GF_PropertyMap * gf_props_new(GF_Filter *filter)
{
	GF_PropertyMap *map;

	map = gf_fq_pop(filter->session->prop_maps_reservoir);

	if (!map) {
		GF_SAFEALLOC(map, GF_PropertyMap);
		if (!map) return NULL;

		map->session = filter->session;
#if GF_PROPS_HASHTABLE_SIZE
#else
		map->properties = gf_list_new();
#endif
	}
	gf_assert(!map->reference_count);
	map->reference_count = 1;
	return map;
}

static GF_Err gf_filter_pid_merge_properties_internal(GF_FilterPid *dst_pid, GF_FilterPid *src_pid, gf_filter_prop_filter filter_prop, void *cbk, Bool is_merge)
{
	GF_PropertyMap *dst_props, *src_props = NULL, *old_dst_props=NULL;
	if (PID_IS_INPUT(dst_pid)) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("Attempt to reset all properties on input PID in filter %s - ignoring\n", dst_pid->filter->name));
		return GF_BAD_PARAM;
	}
	if (is_merge) {
		gf_mx_p(src_pid->filter->tasks_mx);
		old_dst_props = gf_list_last(dst_pid->properties);
		gf_mx_v(src_pid->filter->tasks_mx);
	}

	dst_props = check_new_pid_props(dst_pid, GF_FALSE);

	if (!dst_props) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_FILTER, ("No properties for destination pid in filter %s, ignoring reset\n", dst_pid->filter->name));
		return GF_OUT_OF_MEM;
	}
	if (PID_IS_INPUT(src_pid)) {
		GF_FilterPidInst *pidi = (GF_FilterPidInst *)src_pid;
		if (!pidi->props) {
			gf_mx_p(src_pid->filter->tasks_mx);
			pidi->props = gf_list_get(src_pid->pid->properties, 0);
			gf_mx_v(src_pid->filter->tasks_mx);
			gf_fatal_assert(pidi->props);
			safe_int_inc(&pidi->props->reference_count);
		}
		src_props = pidi->props;
	}
	src_pid = src_pid->pid;
	if (!src_props) {
		gf_mx_p(src_pid->filter->tasks_mx);
		src_props = gf_list_last(src_pid->properties);
		gf_mx_v(src_pid->filter->tasks_mx);
		if (!src_props) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_FILTER, ("No properties to copy from pid %s in filter %s, ignoring merge\n", src_pid->name, src_pid->filter->name));
			gf_free(dst_props);
			return GF_OK;
		}
	}
	if (src_pid->name && !old_dst_props)
		gf_filter_pid_set_name(dst_pid, src_pid->name);

	if (!is_merge) {
		gf_props_reset(dst_props);
	} else {
		if (old_dst_props && (old_dst_props!=dst_props)) {
			GF_Err e = gf_props_merge_property(dst_props, old_dst_props, NULL, NULL);
			if (e) return e;
		}
	}
	return gf_props_merge_property(dst_props, src_props, filter_prop, cbk);
}

GF_Err gf_props_merge_property(GF_PropertyMap *dst_props, GF_PropertyMap *src_props, gf_filter_prop_filter filter_prop, void *cbk)
{
	GF_Err e;
	u32 i, count;
#if GF_PROPS_HASHTABLE_SIZE
	u32 idx;
#endif
	GF_List *list;
	if (src_props->timescale)
		dst_props->timescale = src_props->timescale;

#if GF_PROPS_HASHTABLE_SIZE
	for (idx=0; idx<GF_PROPS_HASHTABLE_SIZE; idx++) {
		if (src_props->hash_table[idx]) {
			list = src_props->hash_table[idx];
#else
			list = src_props->properties;
#endif
			count = gf_list_count(list);
			for (i=0; i<count; i++) {
				GF_PropertyEntry *prop = gf_list_get(list, i);
				gf_assert(prop->reference_count);
				if (!filter_prop || filter_prop(cbk, prop->p4cc, prop->pname, &prop->prop)) {
					safe_int_inc(&prop->reference_count);

#if GF_PROPS_HASHTABLE_SIZE
					if (!dst_props->hash_table[idx]) {
						dst_props->hash_table[idx] = gf_props_get_list(dst_props);
						if (!dst_props->hash_table[idx]) return GF_OUT_OF_MEM;
					}
					e = gf_list_add(dst_props->hash_table[idx], prop);
					if (e) return e;
#else
					e = gf_list_add(dst_props->properties, prop);
					if (e) return e;
#endif
				}
			}
#if GF_PROPS_HASHTABLE_SIZE
		}
	}
#endif
	return GF_OK;
}

void gf_props_reset(GF_PropertyMap *prop)
{
#if GF_PROPS_HASHTABLE_SIZE
	u32 i;
	for (i=0; i<GF_PROPS_HASHTABLE_SIZE; i++) {
		if (prop->hash_table[i]) {
			GF_List *l = prop->hash_table[i];
			while (gf_list_count(l)) {
				gf_props_del_property((GF_PropertyEntry *) gf_list_pop_back(l) );
			}
			prop->hash_table[i] = NULL;
			if (gf_fq_res_add(prop->session->prop_maps_list_reservoir, l)) {
				gf_list_del(l);
			}
		}
	}
#else
	while (gf_list_count(prop->properties)) {
		gf_props_del_property( (GF_PropertyEntry *) gf_list_pop_back(prop->properties) );
	}
#endif
}
