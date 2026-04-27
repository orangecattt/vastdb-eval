#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef REVISION
#define REVISION "undefined"
#endif
#ifndef __SCFILENAME__
#define __SCFILENAME__ "undefined"
#endif

#if defined(__MINGW32__)
#define ATTR_FMT_PRINTF(x, y) __attribute__((format(__MINGW_PRINTF_FORMAT, (x), (y))))
#elif defined(__GNUC__)
#define ATTR_FMT_PRINTF(x, y) __attribute__((format(printf, (x), (y))))
#else
#define ATTR_FMT_PRINTF(x, y)
#endif

void SCLog(int x, const char *file, const char *func, const int line, const char *module,
        const char *fmt, ...) ATTR_FMT_PRINTF(6, 7);
void SCLogErr(int x, const char *file, const char *func, const int line, const char *module,
        const char *fmt, ...) ATTR_FMT_PRINTF(6, 7);

static const char *_sc_module __attribute__((unused)) = __SCFILENAME__;

typedef enum {
    SC_LOG_NOTSET = -1,
    SC_LOG_NONE = 0,
    SC_LOG_ERROR,
    SC_LOG_WARNING,
    SC_LOG_NOTICE,
    SC_LOG_INFO,
    SC_LOG_PERF,
    SC_LOG_CONFIG,
    SC_LOG_DEBUG,
    SC_LOG_LEVEL_MAX,
} SCLogLevel;

#define SCLogWarning(...)                                                                          \
    SCLogErr(SC_LOG_WARNING, __FILE__, __FUNCTION__, __LINE__, _sc_module, __VA_ARGS__)
#define SCLogWarningRaw(file, func, line, ...)                                                     \
    SCLogErr(SC_LOG_WARNING, (file), (func), (line), _sc_module, __VA_ARGS__)

#define SCLogDebug(...)                 do { } while (0)

#define SCEnter(...)

#define SCReturn                        return
#define SCReturnInt(x)                  return x
#define SCReturnUInt(x)                 return x
#define SCReturnDbl(x)                  return x
#define SCReturnChar(x)                 return x
#define SCReturnCharPtr(x)              return x
#define SCReturnCT(x, type)             return x
#define SCReturnPtr(x, type)            return x
#define SCReturnBool(x)                 return x
#define SCReturnStruct(x)               return x

#define KEYWORD_PROFILING_SET_LIST(a,b)
#define KEYWORD_PROFILING_START
#define KEYWORD_PROFILING_END(a,b,c)

#if CPPCHECK==1
#define likely
#define unlikely
#else
#ifndef likely
#define likely(expr) __builtin_expect(!!(expr), 1)
#endif
#ifndef unlikely
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#endif
#endif

#define BIT_U8(n)  ((uint8_t)(1 << (n)))
#define BIT_U16(n) ((uint16_t)(1 << (n)))
#define BIT_U32(n) ((uint32_t)(1UL << (n)))
#define BIT_U64(n) (1ULL << (n))

#define DETECT_TRANSFORMS_MAX 16

#define DETECT_CONTENT_NOCASE            BIT_U32(0)
#define DETECT_CONTENT_DISTANCE          BIT_U32(1)
#define DETECT_CONTENT_WITHIN            BIT_U32(2)
#define DETECT_CONTENT_OFFSET            BIT_U32(3)
#define DETECT_CONTENT_DEPTH             BIT_U32(4)
#define DETECT_CONTENT_FAST_PATTERN      BIT_U32(5)
#define DETECT_CONTENT_FAST_PATTERN_ONLY BIT_U32(6)
#define DETECT_CONTENT_FAST_PATTERN_CHOP BIT_U32(7)
#define DETECT_CONTENT_RAWBYTES          BIT_U32(8)
#define DETECT_CONTENT_NEGATED           BIT_U32(9)
#define DETECT_CONTENT_ENDS_WITH         BIT_U32(10)
#define DETECT_CONTENT_OFFSET_VAR        BIT_U32(11)
#define DETECT_CONTENT_DEPTH_VAR         BIT_U32(12)
#define DETECT_CONTENT_DISTANCE_VAR      BIT_U32(13)
#define DETECT_CONTENT_WITHIN_VAR        BIT_U32(14)
#define DETECT_CONTENT_REPLACE           BIT_U32(15)
#define DETECT_CONTENT_NO_DOUBLE_INSPECTION_REQUIRED BIT_U32(16)
#define DETECT_CONTENT_WITHIN_NEXT      BIT_U32(17)
#define DETECT_CONTENT_DISTANCE_NEXT    BIT_U32(18)
#define DETECT_CONTENT_STARTS_WITH      BIT_U32(19)
#define DETECT_CONTENT_MPM              BIT_U32(20)
#define DETECT_CONTENT_WITHIN2DEPTH     BIT_U32(21)
#define DETECT_CONTENT_DISTANCE2OFFSET  BIT_U32(22)

#define DETECT_CONTENT_RELATIVE_NEXT    (DETECT_CONTENT_WITHIN_NEXT|DETECT_CONTENT_DISTANCE_NEXT)

#define DETECT_CONTENT_IS_SINGLE(c) (!( ((c)->flags & DETECT_CONTENT_DISTANCE) || \
                                        ((c)->flags & DETECT_CONTENT_WITHIN) || \
                                        ((c)->flags & DETECT_CONTENT_RELATIVE_NEXT) || \
                                        ((c)->flags & DETECT_CONTENT_DEPTH) || \
                                        ((c)->flags & DETECT_CONTENT_OFFSET) ))

#define DETECT_PCRE_RELATIVE            0x00001
/* no-op other than in parsing */
#define DETECT_PCRE_RAWBYTES            0x00002
#define DETECT_PCRE_CASELESS            0x00004

#define DETECT_PCRE_RELATIVE_NEXT       0x00040
#define DETECT_PCRE_NEGATE              0x00080

#define DETECT_CI_FLAGS_START                                                                      \
    BIT_U8(0) /**< indication that current buffer is the start of the data */
#define DETECT_CI_FLAGS_END     BIT_U8(1)   /**< indication that current buffer
                                             *   is the end of the data */
#define DETECT_CI_FLAGS_DCE_LE  BIT_U8(2)   /**< DCERPC record in little endian */
#define DETECT_CI_FLAGS_DCE_BE  BIT_U8(3)   /**< DCERPC record in big endian */

#define DETECT_BYTETEST_LITTLE     BIT_U16(0) /**< "little" endian value */
#define DETECT_BYTETEST_BIG        BIT_U16(1) /**< "bi" endian value */
#define DETECT_BYTETEST_STRING     BIT_U16(2) /**< "string" value */
#define DETECT_BYTETEST_RELATIVE   BIT_U16(3) /**< "relative" offset */
#define DETECT_BYTETEST_DCE        BIT_U16(4) /**< dce enabled */
#define DETECT_BYTETEST_BITMASK    BIT_U16(5) /**< bitmask supplied*/
#define DETECT_BYTETEST_VALUE_VAR  BIT_U16(6) /**< byte extract value enabled */
#define DETECT_BYTETEST_OFFSET_VAR BIT_U16(7) /**< byte extract value enabled */
#define DETECT_BYTETEST_NBYTES_VAR BIT_U16(8) /**< byte extract value enabled */

#define DETECT_BYTEJUMP_BEGIN     BIT_U16(0) /**< "from_beginning" jump */
#define DETECT_BYTEJUMP_LITTLE    BIT_U16(1) /**< "little" endian value */
#define DETECT_BYTEJUMP_BIG       BIT_U16(2) /**< "big" endian value */
#define DETECT_BYTEJUMP_STRING    BIT_U16(3) /**< "string" value */
#define DETECT_BYTEJUMP_RELATIVE  BIT_U16(4) /**< "relative" offset */
#define DETECT_BYTEJUMP_ALIGN     BIT_U16(5) /**< "align" offset */
#define DETECT_BYTEJUMP_DCE       BIT_U16(6) /**< "dce" enabled */
#define DETECT_BYTEJUMP_OFFSET_BE BIT_U16(7) /**< "byte extract" enabled */
#define DETECT_BYTEJUMP_END       BIT_U16(8) /**< "from_end" jump */
#define DETECT_BYTEJUMP_NBYTES_VAR BIT_U16(9) /**< nbytes string*/
#define DETECT_BYTEJUMP_OFFSET_VAR BIT_U16(10) /**< byte extract value enabled */

#define ISDATAAT_RELATIVE   0x01
#define ISDATAAT_RAWBYTES   0x02
#define ISDATAAT_NEGATED    0x04
#define ISDATAAT_OFFSET_VAR 0x08

#define DETECT_BYTE_EXTRACT_FLAG_RELATIVE 0x01
#define DETECT_BYTE_EXTRACT_FLAG_STRING 0x02
#define DETECT_BYTE_EXTRACT_FLAG_ALIGN 0x04
#define DETECT_BYTE_EXTRACT_FLAG_ENDIAN 0x08
#define DETECT_BYTE_EXTRACT_FLAG_SLICE 0x10
#define DETECT_BYTE_EXTRACT_FLAG_MULTIPLIER 0x20
#define DETECT_BYTE_EXTRACT_FLAG_NBYTES 0x40
#define DETECT_BYTE_EXTRACT_FLAG_OFFSET 0x80
#define DETECT_BYTE_EXTRACT_FLAG_BASE 0x100

#define DETECT_BYTEMATH_FLAG_RELATIVE 0x01
#define DETECT_BYTEMATH_FLAG_STRING 0x02
#define DETECT_BYTEMATH_FLAG_BITMASK 0x04
#define DETECT_BYTEMATH_FLAG_ENDIAN 0x08
#define DETECT_BYTEMATH_FLAG_RVALUE_VAR 0x10
#define DETECT_BYTEMATH_FLAG_NBYTES_VAR 0x20

#define DETECT_CI_FLAGS_START                                                                      \
    BIT_U8(0) /**< indication that current buffer is the start of the data */
#define DETECT_CI_FLAGS_END     BIT_U8(1)   /**< indication that current buffer
                                             *   is the end of the data */
#define DETECT_CI_FLAGS_DCE_LE  BIT_U8(2)   /**< DCERPC record in little endian */
#define DETECT_CI_FLAGS_DCE_BE  BIT_U8(3)   /**< DCERPC record in big endian */

#define DETECT_CI_FLAGS_SINGLE  (DETECT_CI_FLAGS_START|DETECT_CI_FLAGS_END)

#define SIG_FLAG_REQUIRE_PACKET         BIT_U32(9)  /**< signature is requiring packet match */
#define SIG_FLAG_REQUIRE_STREAM         BIT_U32(10) /**< signature is requiring stream match */

#define SIG_FLAG_REQUIRE_STREAM_ONLY                                                               \
    BIT_U32(13) /**< signature is requiring stream match. Stream match is not optional, so no      \
                   fallback to packet payload. */

#define SIG_FLAG_INIT_PACKET                BIT_U32(1)  /**< signature has matches against a packet (as opposed to app layer) */
#define SIG_FLAG_INIT_FLOW                  BIT_U32(2)  /**< signature has a flow setting */
#define SIG_FLAG_INIT_BIDIREC               BIT_U32(3)  /**< signature has bidirectional operator */
#define SIG_FLAG_INIT_FIRST_IPPROTO_SEEN                                                           \
    BIT_U32(4) /** < signature has seen the first ip_proto keyword */
#define SIG_FLAG_INIT_STATE_MATCH           BIT_U32(6)  /**< signature has matches that require stateful inspection */
#define SIG_FLAG_INIT_NEED_FLUSH            BIT_U32(7)
#define SIG_FLAG_INIT_PRIO_EXPLICIT                                                                \
    BIT_U32(8) /**< priority is explicitly set by the priority keyword */
#define SIG_FLAG_INIT_FILEDATA       BIT_U32(9)  /**< signature has filedata keyword */
#define SIG_FLAG_INIT_FORCE_TOCLIENT BIT_U32(10) /**< signature now takes keywords toclient */
#define SIG_FLAG_INIT_FORCE_TOSERVER BIT_U32(11) /**< signature now takes keywords toserver */
#define SIG_FLAG_INIT_TXDIR_STREAMING_TOSERVER                                                     \
    BIT_U32(12) /**< transactional signature uses a streaming buffer to server */
#define SIG_FLAG_INIT_TXDIR_FAST_TOCLIENT                                                          \
    BIT_U32(13) /**< transactional signature uses a fast pattern to client */

#define SIG_FLAG_SRC_ANY                BIT_U32(0)  /**< source is any */
#define SIG_FLAG_DST_ANY                BIT_U32(1)  /**< destination is any */
#define SIG_FLAG_SP_ANY                 BIT_U32(2)  /**< source port is any */
#define SIG_FLAG_DP_ANY                 BIT_U32(3)  /**< destination port is any */

#define SIG_FLAG_FIREWALL BIT_U32(4) /**< sig is a firewall rule */

#define SIG_FLAG_DSIZE                  BIT_U32(5)  /**< signature has a dsize setting */
#define SIG_FLAG_APPLAYER               BIT_U32(6) /**< signature applies to app layer instead of packets */
#define SIG_FLAG_TXBOTHDIR              BIT_U32(7) /**< signature needs tx with both directions to match */

#define PKT_REBUILT_FRAGMENT                                                                       \
    BIT_U32(25) /**< Packet is rebuilt from                                                        \
                 * fragments. */
#define PKT_DETECT_HAS_STREAMDATA                                                                  \
    BIT_U32(26) /**< Set by Detect() if raw stream data is available. */

#define PKT_STREAM_ADD BIT_U32(5)
#define PKT_STREAM_EST BIT_U32(6)

#define PKT_NOPACKET_INSPECTION BIT_U32(0)

#define PKT_NOPAYLOAD_INSPECTION BIT_U32(2)

#define PKT_HAS_FLOW   BIT_U32(8)
#define PKT_PSEUDO_STREAM_END BIT_U32(9)
#define PKT_STREAM_MODIFIED BIT_U32(10)

#define PKT_PSEUDO_DETECTLOG_FLUSH BIT_U32(27) /**< Detect/log flush for protocol upgrade */

#define PACKET_ALERT_FLAG_APPLY_ACTION_TO_FLOW BIT_U8(0)
#define PACKET_ALERT_FLAG_STATE_MATCH BIT_U8(1)
#define PACKET_ALERT_FLAG_STREAM_MATCH BIT_U8(2)
#define PACKET_ALERT_FLAG_TX BIT_U8(3)
#define PACKET_ALERT_FLAG_RATE_FILTER_MODIFIED BIT_U8(4)
#define PACKET_ALERT_FLAG_FRAME BIT_U8(5)
#define PACKET_ALERT_FLAG_TX_GUESSED BIT_U8(6)
#define PACKET_ALERT_FLAG_APPLY_ACTION_TO_PACKET BIT_U8(7)

#define DETECT_ENGINE_INSPECT_SIG_NO_MATCH 0
#define DETECT_ENGINE_INSPECT_SIG_MATCH 1
#define DETECT_ENGINE_INSPECT_SIG_CANT_MATCH 2
#define DETECT_ENGINE_INSPECT_SIG_CANT_MATCH_FILES 3
#define DETECT_ENGINE_INSPECT_SIG_MATCH_MORE_FILES 4

#define SigIntId uint32_t
#define PatIntId uint32_t

#define SignatureMask uint8_t

#define SGH_PROFILING_RECORD(det_ctx, sgh)

#define RULE_PROFILING_START(p)
#define RULE_PROFILING_END(a, b, c, p)

#define FLOW_ACTION_PASS BIT_U32(28)

#define FLOW_TS_APP_UPDATED BIT_U32(29)
#define FLOW_TC_APP_UPDATED BIT_U32(30)

#define FLOW_ACTION_ACCEPT BIT_U32(4)

#define FLOW_ACTION_DROP                BIT_U32(7)

#define FLOW_PKT_TOSERVER               0x01
#define FLOW_PKT_TOCLIENT               0x02
#define FLOW_PKT_ESTABLISHED            0x04
#define FLOW_PKT_TOSERVER_FIRST         0x08
#define FLOW_PKT_TOCLIENT_FIRST         0x10

#define STREAM_START     0x01
#define STREAM_EOF       0x02
#define STREAM_TOSERVER  0x04
#define STREAM_TOCLIENT  0x08
#define STREAM_GAP       0x10
#define STREAM_DEPTH     0x20
#define STREAM_MIDSTREAM 0x40

#define PACKET_ALERT_NOTX UINT64_MAX

#define IPPROTO_UDP 17
#define IPPROTO_TCP 6

#define DE_STATE_CHUNK_SIZE             15
#define DETECT_FILESTORE_MAX 15

#define PMQ_RESET(pmq) (pmq)->rule_id_array_cnt = 0

#define ACTION_ALERT        0x01
#define ACTION_DROP         0x02
#define ACTION_REJECT       0x04
#define ACTION_REJECT_DST   0x08
#define ACTION_REJECT_BOTH  0x10
#define ACTION_PASS         0x20
#define ACTION_CONFIG       0x40
#define ACTION_ACCEPT       0x80 /**< firewall 'accept' rule */

#define ACTION_REJECT_ANY   (ACTION_REJECT|ACTION_REJECT_DST|ACTION_REJECT_BOTH)

#define ACTION_DROP_REJECT (ACTION_REJECT_ANY | ACTION_DROP)

#define DEBUG_ASSERT_FLOW_LOCKED(f)
#define DEBUG_VALIDATE_FLOW(f)
#define DEBUG_VALIDATE_PACKET(p)
#define DEBUG_VALIDATE_BUG_ON(exp)

#define PACKET_PROFILING_DETECT_START(p, id)
#define PACKET_PROFILING_DETECT_END(p, id)

#define DETECT_ENGINE_STATE_FLAG_FILE_NEW       BIT_U8(0)

#define DE_STATE_FLAG_FULL_INSPECT              BIT_U32(0)
#define DE_STATE_FLAG_SIG_CANT_MATCH            BIT_U32(1)
#define DE_STATE_ID_FILE_INSPECT                2UL
#define DE_STATE_FLAG_FILE_INSPECT              BIT_U32(DE_STATE_ID_FILE_INSPECT)

#define APP_LAYER_TX_SKIP_INSPECT_TS BIT_U8(0)
#define APP_LAYER_TX_SKIP_INSPECT_TC BIT_U8(1)
#define APP_LAYER_TX_INSPECTED_TS BIT_U8(2)
#define APP_LAYER_TX_INSPECTED_TC BIT_U8(3)
#define APP_LAYER_TX_ACCEPT BIT_U8(4)

#define APP_LAYER_PARSER_NO_INSPECTION         BIT_U16(1)
#define APP_LAYER_PARSER_NO_REASSEMBLY         BIT_U16(2)
#define APP_LAYER_PARSER_NO_INSPECTION_PAYLOAD BIT_U16(3)
#define APP_LAYER_PARSER_BYPASS_READY          BIT_U16(4)
#define APP_LAYER_PARSER_EOF_TS                BIT_U16(5)
#define APP_LAYER_PARSER_EOF_TC                BIT_U16(6)
/* 2x vacancy */
#define APP_LAYER_PARSER_SFRAME_TS             BIT_U16(9)
#define APP_LAYER_PARSER_SFRAME_TC             BIT_U16(10)

#define PKT_IS_TCP(p)       (((p)->tcph != NULL))
#define PKT_IS_UDP(p)       (((p)->udph != NULL))
#define PKT_IS_ICMPV4(p)    (((p)->icmpv4h != NULL))
#define PKT_IS_ICMPV6(p)    (((p)->icmpv6h != NULL))
#define PKT_IS_TOSERVER(p)  (((p)->flowflags & FLOW_PKT_TOSERVER))
#define PKT_IS_TOCLIENT(p)  (((p)->flowflags & FLOW_PKT_TOCLIENT))

#define PKT_WANTS_FLOW BIT_U32(22)

#define STREAM_FLAGS_FOR_PACKET(p) (PKT_IS_TOSERVER((p)) ? STREAM_TOSERVER : STREAM_TOCLIENT)

#define STREAMTCP_FLAG_APP_LAYER_DISABLED BIT_U32(13)

#define PKT_IS_PSEUDOPKT(p) \
    ((p)->flags & (PKT_PSEUDO_STREAM_END|PKT_PSEUDO_DETECTLOG_FLUSH))

#define SCAtomicCompareAndSwap(addr, tv, nv) \
    __sync_bool_compare_and_swap((addr), (tv), (nv))

#define SC_ATOMIC_CAS(name, cmpval, newval) \
    SCAtomicCompareAndSwap((name ## _sc_atomic__), cmpval, newval)

#define SC_ATOMIC_GET(name) \
    (name ## _sc_atomic__)

#define SC_ATOMIC_LOAD_EXPLICIT(name, order) \
    (name ## _sc_atomic__)

/**
 *  \brief Set the value for the atomic variable.
 *
 *  \retval var value
 */
#define SC_ATOMIC_SET(name, val) ({       \
    while (SC_ATOMIC_CAS(&name, SC_ATOMIC_GET(name), val) == 0) \
        ;                                                       \
        })

#define SC_ATOMIC_DECLARE(type, name) \
    type name ## _sc_atomic__

#define FLOWWORKER_PROFILING_START(p, id)
#define FLOWWORKER_PROFILING_END(p, id)

#define PKT_PSEUDO_DETECTLOG_FLUSH BIT_U32(27) /**< Detect/log flush for protocol upgrade */

/** Packet is part of stream in known bad condition (loss, wrong thread),
 *  so flag it for not setting stream events */
#define PKT_STREAM_NO_EVENTS BIT_U32(28)

/** We had no alert on flow before this packet */
#define PKT_FIRST_ALERTS BIT_U32(29)
#define PKT_FIRST_TAG    BIT_U32(30)

#define PKT_PSEUDO_LOG_FLUSH BIT_U32(31) /**< Detect/log flush for protocol upgrade */

/** \brief return 1 if the packet is a pseudo packet */
#define PKT_IS_PSEUDOPKT(p) \
    ((p)->flags & (PKT_PSEUDO_STREAM_END|PKT_PSEUDO_DETECTLOG_FLUSH))
#define PKT_IS_FLUSHPKT(p) ((p)->flags & (PKT_PSEUDO_LOG_FLUSH))

#define PKT_SET_SRC(p, src_val) ((p)->pkt_src = src_val)

#define SCMutex pthread_mutex_t
#define SCMutexAttr pthread_mutexattr_t
#define SCMutexInit(mut, mutattr ) pthread_mutex_init(mut, mutattr)
#define SCMutexLock(mut) pthread_mutex_lock(mut)
#define SCMutexTrylock(mut) pthread_mutex_trylock(mut)
#define SCMutexUnlock(mut) pthread_mutex_unlock(mut)
#define SCMutexDestroy pthread_mutex_destroy
#define SCMUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define FLOWLOCK_INIT(fb) SCMutexInit(&(fb)->m, NULL)
#define FLOWLOCK_DESTROY(fb) SCMutexDestroy(&(fb)->m)
#define FLOWLOCK_RDLOCK(fb) SCMutexLock(&(fb)->m)
#define FLOWLOCK_WRLOCK(fb) SCMutexLock(&(fb)->m)
#define FLOWLOCK_TRYRDLOCK(fb) SCMutexTrylock(&(fb)->m)
#define FLOWLOCK_TRYWRLOCK(fb) SCMutexTrylock(&(fb)->m)
#define FLOWLOCK_UNLOCK(fb) SCMutexUnlock(&(fb)->m)

#define FLOW_TS_APP_UPDATED BIT_U32(29)
#define FLOW_TC_APP_UPDATED BIT_U32(30)
#define FLOW_TS_APP_UPDATE_NEXT BIT_U32(31)
#define FLOW_TC_APP_UPDATE_NEXT BIT_U32(2)

enum ActionScope {
    ACTION_SCOPE_AUTO = 0,
    ACTION_SCOPE_PACKET, /**< apply action to packet */
    ACTION_SCOPE_FLOW,   /**< apply drop/pass/accept action to flow */
    ACTION_SCOPE_HOOK,   /**< apply action to current hook */
    ACTION_SCOPE_TX,     /**< apply action to current tx */
};

typedef struct {
    uint64_t secs : 44;
    uint64_t usecs : 20;
} SCTime_t;

typedef struct Packet_
{
    uint8_t proto;
    uint8_t flowflags;
    uint8_t app_update_direction; // enum StreamUpdateDir
    /** sig mask flags this packet has, used in signature matching */
    SignatureMask sig_mask;
    /* Pkt Flags */
    uint32_t flags;
    struct Flow_ *flow;
    SCTime_t ts;
    /* ptr to the payload of the packet
     * with it's length. */
    uint8_t *payload;
    uint16_t payload_len;
    /* IPS action to take */
    uint8_t action;
    /** tenant id for this packet, if any. If 0 then no tenant was assigned. */
    uint32_t tenant_id;
} Packet;

typedef struct SpmThreadCtx_ {
    uint8_t matcher;
    void *ctx;
} SpmThreadCtx;

typedef struct DetectReplaceList_ {
    const struct DetectContentData_ *cd;
    uint8_t *found;
    struct DetectReplaceList_ *next;
} DetectReplaceList;

typedef struct Signature_ Signature;
typedef struct ThreadVars_ ThreadVars;
typedef struct DetectEngineThreadCtx_ DetectEngineThreadCtx;

typedef uint8_t (*DetectPacketHookFunc)(ThreadVars *tv, DetectEngineThreadCtx *det_ctx, Packet *p);

typedef struct DetectEngineCtx_ {
    Signature **sig_array;
    uint32_t sig_array_len;  /* size in array members */
    /* maximum recursion depth for content inspection */
    int inspection_recursion_limit;
    /* maximum number of times a tx will get logged for rules not using app-layer keywords */
    uint8_t guess_applayer_log_limit;
    /* force app-layer tx finding for alerts with signatures not having app-layer keywords */
    bool guess_applayer;
    /* Hook for pre_stream engine if it is used. */
    DetectPacketHookFunc PreStreamHook;
    /** TCP pre_stream hook rule groups. One per direction. */
    struct SigGroupHead_ *pre_stream_sgh[2];
    /* Hook for pre_flow engine if it is used. */
    DetectPacketHookFunc PreFlowHook;
    /** pre_flow hook rule groups. Before flow we don't know a direction yet. */
    struct SigGroupHead_ *pre_flow_sgh;
} DetectEngineCtx;

typedef struct PostRuleMatchWorkQueueItem {
    int sm_type;    /**< sigmatch type e.g. DETECT_FLOWBITS */
    uint32_t value; /**< value to be interpreted by the sm_type
                     *   implementation. E.g. flowbit id. */
#ifdef DEBUG
    SigIntId id;
#endif
} PostRuleMatchWorkQueueItem;

typedef struct PostRuleMatchWorkQueue {
    PostRuleMatchWorkQueueItem *q; /**< array pointer */
    uint32_t len;                  /**< number of array elements in use. */
    uint32_t size;                 /**< allocation size in number of elements. */
} PostRuleMatchWorkQueue;

typedef struct PrefilterRuleStore_ {
    /* used for storing rule id's */

    /* Array of rule IDs found. */
    SigIntId *rule_id_array;
    /* Number of rule IDs in the array. */
    uint32_t rule_id_array_cnt;
    /* The number of slots allocated for storing rule IDs */
    uint32_t rule_id_array_size;

} PrefilterRuleStore;

typedef struct RuleMatchCandidateTx {
    SigIntId id;            /**< internal signature id */
    uint32_t *flags;        /**< inspect flags ptr */
    union {
        struct {
            bool stream_stored;
            uint8_t stream_result;
        };
        uint32_t stream_reset;
    };

    const Signature *s;     /**< ptr to sig */
} RuleMatchCandidateTx;

typedef struct HashTable_ HashTable;

typedef struct DetectEngineThreadCtx_ {
    SC_ATOMIC_DECLARE(int, so_far_used_by_detect);
    uint32_t mt_det_ctxs_cnt;
    HashTable *mt_det_ctxs_hash;
    uint32_t (*TenantGetId)(const void *, const Packet *p);
    /** offset into the payload of the end of the last match by: content, pcre, etc */
    uint32_t buffer_offset;
    /** used by pcre match function alone: normally in sync with buffer_offset, but
     *  points to 1 byte after the start of the last pcre match if a pcre match happened. */
    uint32_t pcre_match_start_offset;
    /** SPM thread context used for scanning. This has been cloned from the
     * prototype held by DetectEngineCtx. */
    SpmThreadCtx *spm_thread_ctx;
    /* byte_* values */
    uint64_t *byte_values;
    /* true if tx_id is set */
    bool tx_id_set;
    /** ID of the transaction currently being inspected. */
    uint64_t tx_id;
    int64_t frame_id;
    uint64_t frame_inspect_progress; /**< used to set Frame::inspect_progress after all inspection
                                        on a frame is complete. */
    Packet *p;

    uint8_t *base64_decoded;
    int base64_decoded_len;
    /** array of signature pointers we're going to inspect in the detection
     *  loop. */
    Signature **match_array;
    /** size of the array in items (mem size if * sizeof(Signature *)
     *  Only used during initialization. */
    uint32_t match_array_len;
    /** size in use */
    SigIntId match_array_cnt;
    RuleMatchCandidateTx *tx_candidates;
    uint32_t tx_candidates_size;
    /* work queue for post-rule matching affecting prefilter */
    PostRuleMatchWorkQueue post_rule_work_queue;
    PrefilterRuleStore pmq;
    /* string to replace */
    DetectReplaceList *replist;
    /* Array in which the filestore keyword stores file id and tx id. If the
     * full signature matches, these are processed by a post-match filestore
     * function to finalize the store. */
    struct {
        uint32_t file_id;
        uint64_t tx_id;
    } filestore[DETECT_FILESTORE_MAX];
    DetectEngineCtx *de_ctx;
} DetectEngineThreadCtx;

typedef struct SigMatchCtx_ {
    int foo;
} SigMatchCtx;

typedef struct SigMatchData_ {
    uint16_t type;   /**< match type */
    bool is_last;    /**< Last element of the list */
    SigMatchCtx *ctx; /**< plugin specific data */
} SigMatchData;

enum DetectSigmatchListEnum {
    /* list for non-payload per packet matches, e.g. ttl, flow keyword */
    DETECT_SM_LIST_MATCH = 0,
    /* list for payload and stream match */
    DETECT_SM_LIST_PMATCH,

    /* base64_data keyword uses some hardcoded logic so consider
     * built-in
     * TODO convert to inspect engine */
    DETECT_SM_LIST_BASE64_DATA,

    /* list for post match actions: flowbit set, flowint increment, etc */
    DETECT_SM_LIST_POSTMATCH,

    DETECT_SM_LIST_TMATCH, /**< post-detection tagging */

    /* lists for alert thresholding and suppression */
    DETECT_SM_LIST_SUPPRESS,
    DETECT_SM_LIST_THRESHOLD,

    DETECT_SM_LIST_MAX,

    /* start of dynamically registered lists */
    DETECT_SM_LIST_DYNAMIC_START = DETECT_SM_LIST_MAX,
};

typedef struct InspectionBuffer InspectionBuffer;

typedef struct TransformData_ {
    int transform;
    void *options;
} TransformData;

typedef struct DetectEngineTransforms {
    TransformData transforms[DETECT_TRANSFORMS_MAX];
    int cnt;
} DetectEngineTransforms;

typedef struct DetectEnginePktInspectionEngine DetectEnginePktInspectionEngine;

typedef int (*InspectionBufferPktInspectFunc)(
        struct DetectEngineThreadCtx_ *,
        const struct DetectEnginePktInspectionEngine *engine,
        const struct Signature_ *s,
        Packet *p, uint8_t *alert_flags);

typedef InspectionBuffer *(*InspectionBufferGetPktDataPtr)(
        struct DetectEngineThreadCtx_ *det_ctx,
        const DetectEngineTransforms *transforms,
        Packet *p, const int list_id);

typedef struct DetectEnginePktInspectionEngine {
    SigMatchData *smd;
    bool mpm;
    uint16_t sm_list;
    uint16_t sm_list_base;
    struct {
        InspectionBufferGetPktDataPtr GetData;
        InspectionBufferPktInspectFunc Callback;
        /** pointer to the transforms in the 'DetectBuffer entry for this list */
        const DetectEngineTransforms *transforms;
    } v1;
    struct DetectEnginePktInspectionEngine *next;
} DetectEnginePktInspectionEngine;

typedef struct SignatureInitData_ {
    /* used to hold flags that are used during init */
    uint32_t init_flags;
} SignatureInitData;

typedef struct DetectProto_ {
    uint8_t proto[256/8]; /**< bit array for 256 protocol bits */
    uint8_t flags;
} DetectProto;

typedef struct DetectEngineAppInspectionEngine_ DetectEngineAppInspectionEngine;
typedef struct DetectEngineFrameInspectionEngine DetectEngineFrameInspectionEngine;

enum SignatureType {
    SIG_TYPE_NOT_SET = 0,
    SIG_TYPE_IPONLY,      // rule is handled by IPONLY engine
    SIG_TYPE_LIKE_IPONLY, // rule is handled by pkt engine, has action effect like ip-only
    /** Proto detect only signature.
     *  Inspected once per direction when protocol detection is done. */
    SIG_TYPE_PDONLY, // rule is handled by PDONLY engine
    SIG_TYPE_DEONLY,
    SIG_TYPE_PKT,
    SIG_TYPE_PKT_STREAM,
    SIG_TYPE_STREAM,

    SIG_TYPE_APPLAYER, // app-layer but not tx, e.g. appproto
    SIG_TYPE_APP_TX,   // rule is handled by TX engine

    SIG_TYPE_MAX,
};

typedef uint16_t AppProto;

typedef struct Signature_ {
    uint32_t flags;
    /* coccinelle: Signature:flags:SIG_FLAG_ */
    enum SignatureType type;
    AppProto alproto;
    SignatureMask mask;
    SigIntId iid; /**< signature internal id */
    /** inline -- action */
    uint8_t action;
    /** addresses, ports and proto this sig matches on */
    DetectProto proto;
    /* scope setting for the action: enum ActionScope */
    uint8_t action_scope;
    /** firewall: progress value for this signature */
    uint8_t app_progress_hook;
    DetectEngineAppInspectionEngine *app_inspect;
    DetectEnginePktInspectionEngine *pkt_inspect;
    DetectEngineFrameInspectionEngine *frame_inspect;
    /* Matching structures for the built-ins. The others are in
     * their inspect engines. */
    SigMatchData *sm_arrays[DETECT_SM_LIST_MAX];
    char *msg;
    SignatureInitData *init_data;
} Signature;


typedef struct DetectEntropyData {
    uint32_t fv_idx;
} DetectEntropyData;

typedef struct AppLayerParserState_ AppLayerParserState;

typedef struct Flow_
{
    uint8_t proto;
    uint32_t flags;         /**< generic flags */
    SCMutex m;
    /** protocol specific data pointer, e.g. for TcpSession */
    void *protoctx;
    AppProto alproto; /**< \brief application level protocol */
    AppProto alproto_ts;
    AppProto alproto_tc;
    /** original application level protocol. Used to indicate the previous
       protocol when changing to another protocol , e.g. with STARTTLS. */
    AppProto alproto_orig;
    /** expected app protocol: used in protocol change/upgrade like in
     *  STARTTLS. */
    AppProto alproto_expect;
    /** application level storage ptrs.
     *
     */
    AppLayerParserState *alparser;     /**< parser internal state */
    void *alstate;      /**< application layer state */
} Flow;

struct DetectEngineContentInspectionCtx {
    struct {
        uint32_t count;
        const uint32_t limit;
    } recursion;
};

enum DetectContentInspectionType {
    DETECT_ENGINE_CONTENT_INSPECTION_MODE_PAYLOAD = 0, /* enables 'replace' logic */
    DETECT_ENGINE_CONTENT_INSPECTION_MODE_HEADER,      /* indicates a header is being inspected */
    DETECT_ENGINE_CONTENT_INSPECTION_MODE_STREAM,      /* enables "stream" inspection logic */
    DETECT_ENGINE_CONTENT_INSPECTION_MODE_FRAME,       /* enables "frame" inspection logic */
    DETECT_ENGINE_CONTENT_INSPECTION_MODE_STATE, /* enables "state" - used for buffers coming from
                                                    the app-layer state. */
};

enum DetectKeywordId {
    DETECT_CONTENT,
    DETECT_PCRE,
    DETECT_BYTETEST,
    DETECT_BYTEJUMP,
    DETECT_BYTEMATH,
    DETECT_BYTE_EXTRACT,
    DETECT_DATASET,
    DETECT_DATAREP,
    DETECT_BASE64_DECODE,
    DETECT_BSIZE,
    DETECT_ASN1,
    DETECT_LUA,
    DETECT_ISDATAAT,
    DETECT_URILEN,
    DETECT_ABSENT,
    DETECT_ENTROPY,
};

typedef struct SpmCtx_ {
    uint8_t matcher;
    void *ctx;
} SpmCtx;

typedef struct DetectContentData_ {
    uint8_t *content;
    uint16_t content_len;
    uint16_t replace_len;
    /* for chopped fast pattern, the length */
    uint16_t fp_chop_len;
    /* for chopped fast pattern, the offset */
    uint16_t fp_chop_offset;
    /* would want to move PatIntId here and flags down to remove the padding
     * gap, but I think the first four members was used as a template for
     * casting.  \todo check this and fix it if possible */
    uint32_t flags;
    uint16_t depth;
    uint16_t offset;
    int32_t distance;
    int32_t within;
    /* SPM search context. */
    SpmCtx *spm_ctx;
    /* pointer to replacement data */
    uint8_t *replace;
} DetectContentData;

typedef struct DetectIsdataatData_ {
    uint16_t dataat;     /* data offset to match */
    uint8_t flags; /* isdataat options*/
} DetectIsdataatData;

typedef struct DetectAbsentData_ {
    /** absent or try to match with other keywords (false means only absent) */
    bool or_else;
} DetectAbsentData;

typedef struct DetectPcreData_ {
    uint16_t flags;
} DetectPcreData;

typedef struct DetectBytetestData_ {
    uint8_t nbytes;                   /**< Number of bytes to compare */
    uint8_t op;                       /**< Operator used to compare */
    uint8_t base;                     /**< String value base (oct|dec|hex) */
    uint8_t bitmask_shift_count;      /**< bitmask trailing 0 count */
    uint16_t flags;                   /**< Flags (big|little|relative|string|bitmask) */
    bool neg_op;
    int32_t offset;                   /**< Offset in payload */
    uint32_t bitmask;                 /**< bitmask value */
    uint64_t value;                   /**< Value to compare against */
} DetectBytetestData;

typedef struct DetectBytejumpData_ {
    uint8_t nbytes;                   /**< Number of bytes to compare */
    uint8_t base;                     /**< String value base (oct|dec|hex) */
    uint16_t flags;                   /**< Flags (big|little|relative|string) */
    int32_t offset;                   /**< Offset in payload to extract value */
    int32_t post_offset;              /**< Offset to adjust post-jump */
    uint16_t multiplier;              /**< Multiplier for nbytes (multiplier n)*/
} DetectBytejumpData;

typedef enum ByteEndian {
    BigEndian = 1,
    LittleEndian = 2,
    EndianDCE = 3,
} ByteEndian;

typedef enum ByteBase {
    BaseOct = 8,
    BaseDec = 10,
    BaseHex = 16,
} ByteBase;

typedef struct SCDetectByteExtractData {
    uint8_t local_id;
    uint8_t nbytes;
    int16_t offset;
    const char *name;
    uint16_t flags;
    ByteEndian endian; // big, little, dce
    ByteBase base;     // From string or dce
    uint8_t align_value;
    uint16_t multiplier_value;
    uint16_t id;
} SCDetectByteExtractData;

typedef struct DetectByteMathData {
    const char *rvalue_str;
    const char *result;
    const char *nbytes_str;
    uint32_t rvalue;
    int32_t offset;
    uint32_t bitmask_val;
    uint16_t bitmask_shift_count;
    uint16_t id;
    uint8_t flags;
    uint8_t local_id;
    uint8_t nbytes;
    // ByteMathOperator oper;
    ByteEndian endian; // big, little, dce
    ByteBase base;     // From string or dce
} DetectByteMathData;

typedef struct DetectDatasetData_ DetectDatasetData;

enum DetectDatarepOp {
    DATAREP_OP_GT,  /* rep is greater than requested */
    DATAREP_OP_LT,  /* rep is smaller than requested */
    DATAREP_OP_EQ,  /* rep is smaller than requested */
};

typedef struct DetectDatarepData_ {
    uint8_t cmd;
    enum DetectDatarepOp op;
} DetectDatarepData;

typedef struct DetectUintData_u64 DetectUintData_u64;
typedef struct DetectUintData_u32 DetectUintData_u32;
typedef struct DetectUintData_u16 {
    uint16_t arg1;
    uint16_t arg2;
} DetectUintData_u16;
typedef struct DetectUintData_u8 DetectUintData_u8;

typedef DetectUintData_u64 DetectU64Data;
typedef DetectUintData_u32 DetectU32Data;
typedef DetectUintData_u16 DetectU16Data;
typedef DetectUintData_u8 DetectU8Data;

typedef struct DetectUrilenData {
    DetectU16Data du16;
    bool raw_buffer;
} DetectUrilenData;

typedef int (*InspectionBufferPktInspectFunc)(
        struct DetectEngineThreadCtx_ *,
        const struct DetectEnginePktInspectionEngine *engine,
        const struct Signature_ *s,
        Packet *p, uint8_t *alert_flags);

typedef struct ThreadVars_ {
    /** local id */
    int id;
} ThreadVars;

typedef struct PrefilterEngine_ PrefilterEngine;

typedef struct SigGroupHead_ {
    PrefilterEngine *tx_engines;
} SigGroupHead;

typedef struct DetectRunScratchpad {
    const AppProto alproto;
    const uint8_t flow_flags; /* flow/state flags: STREAM_* */
    const uint8_t default_action;
    const SigGroupHead *sgh;
} DetectRunScratchpad;

enum AppProtoEnum {
    ALPROTO_UNKNOWN = 0,
    /* used by the probing parser when alproto detection fails
     * permanently for that particular stream */
    // Update of this value should be reflected in rust, where we also define it
    ALPROTO_FAILED = 1,

    // Beginning of real/normal protocols
    ALPROTO_HTTP1,
    ALPROTO_FTP,
    ALPROTO_SMTP,
    ALPROTO_TLS, /* SSLv2, SSLv3 & TLSv1 */
    ALPROTO_SSH,
    ALPROTO_IMAP,
    ALPROTO_JABBER,
    ALPROTO_SMB,
    ALPROTO_DCERPC,
    ALPROTO_IRC,

    ALPROTO_DNS,
    ALPROTO_MODBUS,
    ALPROTO_ENIP,
    ALPROTO_DNP3,
    ALPROTO_NFS,
    ALPROTO_NTP,
    ALPROTO_FTPDATA,
    ALPROTO_TFTP,
    ALPROTO_IKE,
    ALPROTO_KRB5,
    ALPROTO_QUIC,
    ALPROTO_DHCP,
    ALPROTO_SIP,
    ALPROTO_RFB,
    ALPROTO_MQTT,
    ALPROTO_PGSQL,
    ALPROTO_TELNET,
    ALPROTO_WEBSOCKET,
    ALPROTO_LDAP,
    ALPROTO_DOH2,
    ALPROTO_TEMPLATE,
    ALPROTO_RDP,
    ALPROTO_HTTP2,
    ALPROTO_BITTORRENT_DHT,
    ALPROTO_POP3,
    ALPROTO_MDNS,

    // signature-only (ie not seen in flow)
    // HTTP for any version (ALPROTO_HTTP1 (version 1) or ALPROTO_HTTP2)
    ALPROTO_HTTP,

    /* keep last */
    ALPROTO_MAX_STATIC,
    // After this ALPROTO_MAX_STATIC can come dynamic alproto ids
    // For example, ALPROTO_SNMP is now dynamic
};

typedef struct AppLayerParserState_ AppLayerParserState;

typedef struct AppLayerTxData {
    uint8_t flags;
    uint8_t guessed_applayer_logged;
} AppLayerTxData;

enum PacketDropReason {
    PKT_DROP_REASON_NOT_SET = 0,
    PKT_DROP_REASON_DECODE_ERROR,
    PKT_DROP_REASON_DEFRAG_ERROR,
    PKT_DROP_REASON_DEFRAG_MEMCAP,
    PKT_DROP_REASON_FLOW_MEMCAP,
    PKT_DROP_REASON_FLOW_DROP,
    PKT_DROP_REASON_APPLAYER_ERROR,
    PKT_DROP_REASON_APPLAYER_MEMCAP,
    PKT_DROP_REASON_RULES,
    PKT_DROP_REASON_RULES_THRESHOLD, /**< detection_filter in action */
    PKT_DROP_REASON_STREAM_ERROR,
    PKT_DROP_REASON_STREAM_MEMCAP,
    PKT_DROP_REASON_STREAM_MIDSTREAM,
    PKT_DROP_REASON_STREAM_REASSEMBLY,
    PKT_DROP_REASON_STREAM_URG,
    PKT_DROP_REASON_NFQ_ERROR,             /**< no nfq verdict, must be error */
    PKT_DROP_REASON_INNER_PACKET,          /**< drop issued by inner (tunnel) packet */
    PKT_DROP_REASON_DEFAULT_PACKET_POLICY, /**< drop issued by default packet policy */
    PKT_DROP_REASON_DEFAULT_APP_POLICY,    /**< drop issued by default app policy */
    PKT_DROP_REASON_STREAM_PRE_HOOK,       /**< drop issued in the pre_stream hook */
    PKT_DROP_REASON_FLOW_PRE_HOOK,         /**< drop issued in the pre_flow hook */
    PKT_DROP_REASON_MAX,
};

typedef struct AppLayerGetTxIterTuple {
    // tx_ptr: *mut std::os::raw::c_void,
    void *tx_ptr;
    uint64_t tx_id;
    bool has_next;
} AppLayerGetTxIterTuple;

typedef struct AppLayerGetTxIterState {
    union {
        void *ptr;
        uint64_t u64;
    } un;
} AppLayerGetTxIterState;

typedef AppLayerGetTxIterTuple (*AppLayerGetTxIteratorFunc)
       (const uint8_t ipproto, const AppProto alproto,
        void *alstate, uint64_t min_tx_id, uint64_t max_tx_id,
        AppLayerGetTxIterState *state);

typedef struct DeStateStoreItem_ {
    uint32_t flags;
    SigIntId sid;
} DeStateStoreItem;

typedef struct DeStateStore_ {
    DeStateStoreItem store[DE_STATE_CHUNK_SIZE];
    struct DeStateStore_ *next;
} DeStateStore;

typedef struct DetectEngineStateDirection_ {
    DeStateStore *head; /**< head of the list */
    DeStateStore *cur;  /**< current active store */
    DeStateStore *tail; /**< tail of the list */
    SigIntId cnt;
    uint16_t filestore_cnt;
    uint8_t flags;
    /* coccinelle: DetectEngineStateDirection:flags:DETECT_ENGINE_STATE_FLAG_ */
} DetectEngineStateDirection;

typedef struct DetectTransaction_ {
    void *tx_ptr;
    const uint64_t tx_id;
    struct AppLayerTxData *tx_data_ptr;
    DetectEngineStateDirection *de_state;

    /* tracking detect progress. Holds the value of
     * the last completed "progress" + 1. */
    uint8_t detect_progress;
    /* original value to track changes. */
    const uint8_t detect_progress_orig;

    const int tx_progress;
    const int tx_end_state;
} DetectTransaction;

typedef struct TcpSession_ {
    /* coccinelle: TcpSession:flags:STREAMTCP_FLAG */
    uint32_t flags;
} TcpSession;

typedef enum {
    TM_ECODE_OK = 0,    /**< Thread module exits OK*/
    TM_ECODE_FAILED,    /**< Thread module exits due to failure*/
    TM_ECODE_DONE,    /**< Thread module task is finished*/
} TmEcode;

typedef struct TcpReassemblyThreadCtx_ {
    void *app_tctx;
} TcpReassemblyThreadCtx;

typedef struct StreamTcpThread_ {
    /** tcp reassembly thread data */
    TcpReassemblyThreadCtx *ra_ctx;
} StreamTcpThread;

typedef struct PacketQueueNoLock_ {
    struct Packet_ *top;
    struct Packet_ *bot;
    uint32_t len;
#ifdef DBG_PERF
    uint32_t dbg_maxlen;
#endif /* DBG_PERF */
} PacketQueueNoLock;

typedef DetectEngineThreadCtx *DetectEngineThreadCtxPtr;
typedef struct DecodeThreadVars_ DecodeThreadVars;

typedef struct FlowLookupStruct_ // TODO name
{
} FlowLookupStruct;

typedef struct FlowWorkerThreadData_ {
    DecodeThreadVars *dtv;

    union {
        StreamTcpThread *stream_thread;
        void *stream_thread_ptr;
    };

    SC_ATOMIC_DECLARE(DetectEngineThreadCtxPtr, detect_thread);

    SC_ATOMIC_DECLARE(bool, flush_ack);

    void *output_thread; /* Output thread data. */
    void *output_thread_flow; /* Output thread data. */
    
    /** Queue to put pseudo packets that have been created by the stream (RST response) and by the
     * flush logic following a protocol change. */
    PacketQueueNoLock pq;
    FlowLookupStruct fls;

} FlowWorkerThreadData;

typedef struct AppLayerThreadCtx_ AppLayerThreadCtx;

bool SCDetectEntropyMatch(const uint8_t *data, const uint32_t data_len, const DetectEntropyData *ded, double *entropy);
void FlowVarAddFloat(Flow *, uint32_t, double);
uint8_t *SpmScan(const SpmCtx *ctx, SpmThreadCtx *thread_ctx,
                 const uint8_t *haystack, uint32_t haystack_len);
DetectReplaceList *DetectReplaceAddToList(
        DetectReplaceList *replist, uint8_t *found, const DetectContentData *cd);
int DetectPcrePayloadMatch(DetectEngineThreadCtx *,
        const Signature *, const SigMatchData *,
        Packet *, Flow *, const uint8_t *, uint32_t);
int DetectBytetestDoMatch(DetectEngineThreadCtx *, const Signature *, const SigMatchCtx *ctx,
        const uint8_t *, uint32_t, uint16_t, int32_t, int32_t, uint64_t);
bool DetectBytejumpDoMatch(DetectEngineThreadCtx *, const Signature *, const SigMatchCtx *,
        const uint8_t *, uint32_t, uint16_t, int32_t, int32_t);
int DetectByteExtractDoMatch(DetectEngineThreadCtx *, const SigMatchData *, const Signature *,
        const uint8_t *, uint32_t, uint64_t *, uint8_t);
int DetectByteMathDoMatch(DetectEngineThreadCtx *, const DetectByteMathData *, const Signature *,
        const uint8_t *, const uint32_t, uint8_t, uint64_t, uint64_t *, uint8_t);
int DetectBsizeMatch(const SigMatchCtx *ctx, const uint64_t buffer_size, bool eof);
int DetectDatasetBufferMatch(DetectEngineThreadCtx *det_ctx,
    const DetectDatasetData *sd,
    const uint8_t *data, const uint32_t data_len);
int DetectDatarepBufferMatch(DetectEngineThreadCtx *det_ctx,
    const DetectDatarepData *sd,
    const uint8_t *data, const uint32_t data_len);
int DetectU16Match(const uint16_t parg, const DetectUintData_u16 *du16);
int DetectLuaMatchBuffer(DetectEngineThreadCtx *det_ctx,
        const Signature *s, const SigMatchData *smd,
        const uint8_t *buffer, uint32_t buffer_len, uint32_t offset,
        Flow *f);
int DetectBase64DecodeDoMatch(DetectEngineThreadCtx *, const Signature *,
    const SigMatchData *, const uint8_t *, uint32_t);
bool DetectAsn1Match(const SigMatchData *smd, const uint8_t *buffer, const uint32_t buffer_len,
        const uint32_t offset);
int DetectEngineInspectStreamPayload(DetectEngineCtx *,
        DetectEngineThreadCtx *, const Signature *, Flow *,
        Packet *);
int DetectEnginePktInspectionAppend(Signature *s, InspectionBufferPktInspectFunc Callback,
        SigMatchData *data, const int list_id);
int DetectEngineInspectRulePacketMatches(
    DetectEngineThreadCtx *det_ctx,
    const DetectEnginePktInspectionEngine *engine,
    const Signature *s,
    Packet *p, uint8_t *_alert_flags);
bool EngineModeIsFirewall(void);
bool SigDsizePrefilter(const Packet *p, const Signature *s, uint32_t sflags);
bool AppProtoEquals(AppProto sigproto, AppProto alproto);
bool DetectRunInspectRuleHeader(const Packet *p, const Flow *f, const Signature *s,
        const uint32_t sflags, const uint8_t s_proto_flags);
void DetectRunPostMatch(ThreadVars *tv,
                               DetectEngineThreadCtx *det_ctx, Packet *p,
                               const Signature *s);
uint64_t AppLayerParserGetTransactionInspectId(AppLayerParserState *pstate, uint8_t direction);
bool IsOnlyTxInDirection(Flow *f, uint64_t txid, uint8_t dir);
void *AppLayerParserGetTx(uint8_t ipproto, AppProto alproto, void *alstate, uint64_t tx_id);
AppLayerTxData *AppLayerParserGetTxData(uint8_t ipproto, AppProto alproto, void *tx);
void AlertQueueAppend(DetectEngineThreadCtx *det_ctx, const Signature *s, Packet *p, uint64_t tx_id,
        uint8_t alert_flags);
void PrefilterPostRuleMatch(
        DetectEngineThreadCtx *det_ctx, const SigGroupHead *sgh, Packet *p, Flow *f);
void DetectVarProcessList(DetectEngineThreadCtx *det_ctx, Flow *f, Packet *p);
void DetectReplaceFree(DetectEngineThreadCtx *det_ctx);
void PacketDrop(Packet *p, const uint8_t action, enum PacketDropReason r);
uint64_t AppLayerParserGetTxCnt(const Flow *, void *alstate);
int AppLayerParserGetStateProgressCompletionStatus(AppProto alproto, uint8_t direction);
AppLayerGetTxIteratorFunc AppLayerGetTxIterator(const uint8_t ipproto,
         const AppProto alproto);
DetectTransaction GetDetectTx(const uint8_t ipproto, const AppProto alproto,
        const uint64_t tx_id, void *tx_ptr, const int tx_end_state, const uint8_t flow_flags);
void DetectRunPrefilterTx(DetectEngineThreadCtx *det_ctx,
        const SigGroupHead *sgh,
        Packet *p,
        const uint8_t ipproto,
        const uint8_t flow_flags,
        const AppProto alproto,
        void *alstate,
        DetectTransaction *tx);
bool RuleMatchCandidateTxArrayHasSpace(const DetectEngineThreadCtx *det_ctx,
        const uint32_t need);
int RuleMatchCandidateTxArrayExpand(DetectEngineThreadCtx *det_ctx, const uint32_t needed);
void RuleMatchCandidateMergeStateRules(
        DetectEngineThreadCtx *det_ctx, uint32_t *array_idx);
int DetectRunTxSortHelper(const void *a, const void *b);
void DetectRunAppendDefaultAccept(DetectEngineThreadCtx *det_ctx, Packet *p);
int SortHelper(const void *a, const void *b);
bool ApplyAcceptToPacket(
        const uint64_t total_txs, const DetectTransaction *tx, const Signature *s);
bool ApplyAccept(Packet *p, const uint8_t flow_flags, const Signature *s,
        DetectTransaction *tx, const int tx_end_state, const bool fw_next_progress_missing,
        bool *tx_fw_verdict, bool *skip_fw_hook, uint8_t *skip_before_progress);
bool DetectRunTxInspectRule(ThreadVars *tv,
        DetectEngineCtx *de_ctx,
        DetectEngineThreadCtx *det_ctx,
        Packet *p,
        Flow *f,
        const uint8_t in_flow_flags,   // direction, EOF, etc
        void *alstate,
        DetectTransaction *tx,
        const Signature *s,
        uint32_t *stored_flags,
        RuleMatchCandidateTx *can,
        DetectRunScratchpad *scratch);
int DetectRunTxCheckFirewallPolicy(DetectEngineThreadCtx *det_ctx, Packet *p, Flow *f,
        DetectTransaction *tx, const Signature *s, const uint32_t can_idx, const uint32_t can_size,
        bool *skip_fw_hook, const uint8_t skip_before_progress, bool *last_for_progress,
        bool *fw_next_progress_missing);
DetectRunScratchpad DetectRunSetup(const DetectEngineCtx *de_ctx,
        DetectEngineThreadCtx *det_ctx, Packet *const p, Flow *const pflow,
        const uint8_t default_action);
void DetectRunInspectIPOnly(ThreadVars *tv, const DetectEngineCtx *de_ctx,
        DetectEngineThreadCtx *det_ctx, Flow * const pflow, Packet * const p);
void DetectRunGetRuleGroup(const DetectEngineCtx *de_ctx,
        Packet * const p, Flow * const pflow, DetectRunScratchpad *scratch);
void StoreDetectProgress(
        DetectTransaction *tx, const uint8_t flow_flags, const uint8_t progress);
void DetectRunPrefilterPkt(ThreadVars *tv, const DetectEngineCtx *de_ctx,
        DetectEngineThreadCtx *det_ctx, Packet *p, DetectRunScratchpad *scratch);
void InspectionBufferClean(DetectEngineThreadCtx *det_ctx);
uint16_t SCAppLayerParserStateIssetFlag(AppLayerParserState *pstate, uint16_t flag);
void DetectRunFrames(ThreadVars *tv, DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
        Packet *p, Flow *f, DetectRunScratchpad *scratch);
void AppLayerParserSetTransactionInspectId(const Flow *f, AppLayerParserState *pstate,
                                void *alstate, const uint8_t flags, bool tag_txs_as_inspected);
void DetectRunPostRules(ThreadVars *tv, const DetectEngineCtx *de_ctx,
        DetectEngineThreadCtx *det_ctx, Packet *const p, Flow *const pflow,
        DetectRunScratchpad *scratch);
void DetectRunCleanup(DetectEngineThreadCtx *det_ctx,
        Packet *p, Flow * const pflow);
uint8_t FlowGetDisruptionFlags(const Flow *f, uint8_t flags);
void DetectNoFlow(ThreadVars *tv,
                         DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
                         Packet *p);
DetectEngineThreadCtx *GetTenantById(HashTable *h, uint32_t id);
TmEcode StreamTcp (ThreadVars *, Packet *, void *, PacketQueueNoLock *);
int FlowChangeProto(Flow *);
void StreamTcpDetectLogFlush(ThreadVars *tv, StreamTcpThread *stt, Flow *f, Packet *p, PacketQueueNoLock *pq);
void FlowSetNoPayloadInspectionFlag(Flow *f);
void SCAppLayerParserStateSetFlag(AppLayerParserState *pstate, uint16_t flag);
struct Packet_ *PacketDequeueNoLock (PacketQueueNoLock *qnl);
TmEcode OutputLoggerLog(ThreadVars *, Packet *, void *);
void FramesPrune(Flow *f, Packet *p);
void StreamTcpPruneSession(Flow *, uint8_t);
void FlowDeReference(Flow **d);
void PacketPoolReturnPacket(Packet *p);
void TmqhOutputPacketpool(ThreadVars *, Packet *);
TmEcode OutputLoggerFlush(ThreadVars *, Packet *, void *);
void FlowHandlePacket (ThreadVars *, FlowLookupStruct *, Packet *);
TmEcode FlowUpdate(ThreadVars *tv, FlowWorkerThreadData *fw, Packet *p);
void TimeSetByThread(const int thread_id, SCTime_t tv);
bool PacketIsTCP(const Packet *p);
void DisableDetectFlowFileFlags(Flow *f);
void PacketAppUpdate2FlowFlags(Packet *p);
bool PacketCheckAction(const Packet *p, const uint8_t a);
int AppLayerHandleUdp(ThreadVars *tv, AppLayerThreadCtx *app_tctx,
                      Packet *p, Flow *f);
void PacketUpdateEngineEventCounters(ThreadVars *tv,
        DecodeThreadVars *dtv, Packet *p);
bool FlowIsBypassed(const Flow *f);
void FlowCleanupAppLayer(Flow *);
void StreamTcpSessionCleanup(TcpSession *ssn);
void AppLayerParserTransactionsCleanup(Flow *f, const uint8_t pkt_dir);
void FlowWorkerProcessInjectedFlows(
        ThreadVars *tv, FlowWorkerThreadData *fw, Packet *p);
void FlowWorkerProcessLocalFlows(ThreadVars *tv, FlowWorkerThreadData *fw, Packet *p);

bool DetectEntropyDoMatch(DetectEngineThreadCtx *det_ctx, const Signature *s,
        const SigMatchCtx *ctx, const uint8_t *buffer, const uint32_t buffer_len)
{
    double entropy = -1.0;
    bool rc = SCDetectEntropyMatch(buffer, buffer_len, (const DetectEntropyData *)ctx, &entropy);

    if (entropy != -1.0) {
        DetectEntropyData *ded = (DetectEntropyData *)ctx;
        FlowVarAddFloat(det_ctx->p->flow, ded->fv_idx, entropy);
    }

    return rc;
}

static int DetectEngineContentInspectionInternal(DetectEngineThreadCtx *det_ctx,
        struct DetectEngineContentInspectionCtx *ctx, const Signature *s, const SigMatchData *smd,
        Packet *p, Flow *f, const uint8_t *buffer, const uint32_t buffer_len,
        const uint64_t stream_start_offset, const uint8_t flags,
        const enum DetectContentInspectionType inspection_mode)
{
    SCEnter();
    KEYWORD_PROFILING_START;

    ctx->recursion.count++;
    if (unlikely(ctx->recursion.count == ctx->recursion.limit)) {
        KEYWORD_PROFILING_END(det_ctx, smd->type, 0);
        SCReturnInt(-1);
    }

    // we want the ability to match on bsize: 0
    if (smd == NULL || buffer == NULL) {
        KEYWORD_PROFILING_END(det_ctx, smd->type, 0);
        SCReturnInt(0);
    }

    if (smd->type == DETECT_CONTENT) {
        const DetectContentData *cd = (const DetectContentData *)smd->ctx;
        SCLogDebug("inspecting content %"PRIu32" buffer_len %"PRIu32, cd->id, buffer_len);

        /* we might have already have this content matched by the mpm.
         * (if there is any other reason why we'd want to avoid checking
         *  it here, please fill it in) */
        //if (cd->flags & DETECT_CONTENT_NO_DOUBLE_INSPECTION_REQUIRED) {
        //    goto match;
        //}

        /* rule parsers should take care of this */
#ifdef DEBUG
        BUG_ON(cd->depth != 0 && cd->depth <= cd->offset);
#endif

        /* search for our pattern, checking the matches recursively.
         * if we match we look for the next SigMatch as well */
        uint32_t prev_offset = 0; /**< used in recursive searching */
        uint32_t prev_buffer_offset = det_ctx->buffer_offset;

        do {
            uint32_t depth = buffer_len;
            uint32_t offset = 0;
            if ((cd->flags & DETECT_CONTENT_DISTANCE) ||
                (cd->flags & DETECT_CONTENT_WITHIN)) {
                SCLogDebug("det_ctx->buffer_offset %" PRIu32, det_ctx->buffer_offset);
                offset = prev_buffer_offset;

                int distance = cd->distance;
                if (cd->flags & DETECT_CONTENT_DISTANCE) {
                    if (cd->flags & DETECT_CONTENT_DISTANCE_VAR) {
                        // This cast is wrong if a 64-bit value was extracted
                        distance = (uint32_t)det_ctx->byte_values[cd->distance];
                    }
                    if (distance < 0 && (uint32_t)(abs(distance)) > offset)
                        offset = 0;
                    else
                        offset += distance;

                    SCLogDebug("cd->distance %"PRIi32", offset %"PRIu32", depth %"PRIu32,
                               distance, offset, depth);
                }

                if (cd->flags & DETECT_CONTENT_WITHIN) {
                    if (cd->flags & DETECT_CONTENT_WITHIN_VAR) {
                        // This cast is wrong if a 64-bit value was extracted for within
                        if ((int32_t)depth > (int32_t)(prev_buffer_offset + det_ctx->byte_values[cd->within] + distance)) {
                            depth = prev_buffer_offset +
                                    (uint32_t)det_ctx->byte_values[cd->within] + distance;
                        }
                    } else {
                        if ((int32_t)depth > (int32_t)(prev_buffer_offset + cd->within + distance)) {
                            depth = prev_buffer_offset + cd->within + distance;
                        }

                        SCLogDebug("cd->within %"PRIi32", det_ctx->buffer_offset %"PRIu32", depth %"PRIu32,
                                   cd->within, prev_buffer_offset, depth);
                    }

                    if (stream_start_offset != 0 && prev_buffer_offset == 0) {
                        if (depth <= stream_start_offset) {
                            goto no_match;
                        } else if (depth >= (stream_start_offset + buffer_len)) {
                            ;
                        } else {
                            depth = depth - (uint32_t)stream_start_offset;
                        }
                    }
                }

                if (cd->flags & DETECT_CONTENT_DEPTH_VAR) {
                    if ((det_ctx->byte_values[cd->depth] + prev_buffer_offset) < depth) {
                        // ok to cast as we checked the byte value fits in a u32
                        depth = prev_buffer_offset + (uint32_t)det_ctx->byte_values[cd->depth];
                    }
                } else {
                    if (cd->depth != 0) {
                        if ((cd->depth + prev_buffer_offset) < depth) {
                            depth = prev_buffer_offset + cd->depth;
                        }

                        SCLogDebug("cd->depth %"PRIu32", depth %"PRIu32, cd->depth, depth);
                    }
                }

                if (cd->flags & DETECT_CONTENT_OFFSET_VAR) {
                    if (det_ctx->byte_values[cd->offset] > offset) {
                        // This cast is wrong if a 64-bit value was extracted
                        offset = (uint32_t)det_ctx->byte_values[cd->offset];
                    }
                } else {
                    if (cd->offset > offset) {
                        offset = cd->offset;
                        SCLogDebug("setting offset %"PRIu32, offset);
                    }
                }
            } else { /* implied no relative matches */
                /* set depth */
                if (cd->flags & DETECT_CONTENT_DEPTH_VAR) {
                    // This cast is wrong if a 64-bit value was extracted
                    depth = (uint32_t)det_ctx->byte_values[cd->depth];
                } else {
                    if (cd->depth != 0) {
                        depth = cd->depth;
                    }
                }

                if (stream_start_offset != 0 && cd->flags & DETECT_CONTENT_DEPTH) {
                    if (depth <= stream_start_offset) {
                        goto no_match;
                    } else if (depth >= (stream_start_offset + buffer_len)) {
                        ;
                    } else {
                        depth = (uint32_t)(depth - stream_start_offset);
                    }
                }

                /* set offset */
                if (cd->flags & DETECT_CONTENT_OFFSET_VAR) {
                    // This cast is wrong if a 64-bit value was extracted
                    offset = (uint32_t)det_ctx->byte_values[cd->offset];
                } else {
                    offset = cd->offset;
                }
                prev_buffer_offset = 0;
            }

            /* If the value came from a variable, make sure to adjust the depth so it's relative
             * to the offset value.
             */
            if (cd->flags & (DETECT_CONTENT_OFFSET_VAR | DETECT_CONTENT_DEPTH_VAR)) {
                depth += offset;
            }

            /* update offset with prev_offset if we're searching for
             * matches after the first occurrence. */
            SCLogDebug("offset %"PRIu32", prev_offset %"PRIu32, offset, prev_offset);
            if (prev_offset != 0)
                offset = prev_offset;

            SCLogDebug("offset %"PRIu32", depth %"PRIu32, offset, depth);

            if (depth > buffer_len)
                depth = buffer_len;

            /* if offset is bigger than depth we can never match on a pattern.
             * We can however, "match" on a negated pattern. */
            if (offset > depth || depth == 0) {
                if (cd->flags & DETECT_CONTENT_NEGATED) {
                    goto match;
                } else {
                    goto no_match;
                }
            }

            const uint8_t *sbuffer = buffer + offset;
            uint32_t sbuffer_len = depth - offset;
            SCLogDebug("sbuffer_len %" PRIu32 " depth: %" PRIu32 ", buffer_len: %" PRIu32,
                    sbuffer_len, depth, buffer_len);
#ifdef DEBUG
            BUG_ON(sbuffer_len > buffer_len);
#endif
            const uint8_t *found;
            if (cd->flags & DETECT_CONTENT_ENDS_WITH && depth < buffer_len) {
                SCLogDebug("depth < buffer_len while DETECT_CONTENT_ENDS_WITH is set. Can't possibly match.");
                found = NULL;
            } else if (cd->content_len > sbuffer_len) {
                found = NULL;
            } else {
                /* do the actual search */
                found = SpmScan(cd->spm_ctx, det_ctx->spm_thread_ctx, sbuffer,
                        sbuffer_len);
            }

            /* next we evaluate the result in combination with the
             * negation flag. */
            SCLogDebug("found %p cd negated %s", found, cd->flags & DETECT_CONTENT_NEGATED ? "true" : "false");

            if (found == NULL) {
                if (!(cd->flags & DETECT_CONTENT_NEGATED)) {
                    if ((cd->flags & (DETECT_CONTENT_DISTANCE | DETECT_CONTENT_WITHIN)) == 0) {
                        /* independent match from previous matches, so failure is fatal */
                        goto no_match_discontinue;
                    }

                    goto no_match;
                } else {
                    goto match;
                }
            }

            uint32_t match_offset = (uint32_t)((found - buffer) + cd->content_len);
            if (cd->flags & DETECT_CONTENT_NEGATED) {
                SCLogDebug("content %" PRIu32 " matched at offset %" PRIu32
                           ", but negated so no match",
                        cd->id, match_offset);
                /* don't bother carrying recursive matches now, for preceding
                 * relative keywords */

                /* found a match but not at the end of the buffer */
                if (cd->flags & DETECT_CONTENT_ENDS_WITH) {
                    if (sbuffer_len != match_offset) {
                        SCLogDebug("content \"%s\" %" PRIu32 " matched at offset %" PRIu32
                                   ", but not at end of buffer so match",
                                cd->content, cd->id, match_offset);
                        goto match;
                    }
                }
                if (DETECT_CONTENT_IS_SINGLE(cd)) {
                    goto no_match_discontinue;
                }
                goto no_match;
            }

            SCLogDebug("content %" PRIu32 " matched at offset %" PRIu32 "", cd->id, match_offset);
            det_ctx->buffer_offset = match_offset;

            if ((cd->flags & DETECT_CONTENT_ENDS_WITH) == 0 || match_offset == buffer_len) {
                /* Match branch, add replace to the list if needed */
                if (unlikely(cd->flags & DETECT_CONTENT_REPLACE)) {
                    if (inspection_mode == DETECT_ENGINE_CONTENT_INSPECTION_MODE_PAYLOAD) {
                        /* we will need to replace content if match is confirmed
                         * cast to non-const as replace writes to it. */
                        det_ctx->replist =
                                DetectReplaceAddToList(det_ctx->replist, (uint8_t *)found, cd);
                    } else {
                        SCLogWarning("Can't modify payload without packet");
                    }
                }

                /* if this is the last match we're done */
                if (smd->is_last) {
                    goto match;
                }

                SCLogDebug("content %" PRIu32, cd->id);
                KEYWORD_PROFILING_END(det_ctx, smd->type, 1);

                /* see if the next buffer keywords match. If not, we will
                 * search for another occurrence of this content and see
                 * if the others match then until we run out of matches */
                int r = DetectEngineContentInspectionInternal(det_ctx, ctx, s, smd + 1, p, f,
                        buffer, buffer_len, stream_start_offset, flags, inspection_mode);
                if (r == 1) {
                    SCReturnInt(1);
                } else if (r == -1) {
                    SCLogDebug("'next sm' said to discontinue this right now");
                    SCReturnInt(-1);
                }
                SCLogDebug("no match for 'next sm'");

                /* no match and no reason to look for another instance */
                if ((cd->flags & DETECT_CONTENT_WITHIN_NEXT) == 0) {
                    SCLogDebug("'next sm' does not depend on me, so we can give up");
                    SCReturnInt(-1);
                }

                SCLogDebug("'next sm' depends on me %p, lets see what we can do (flags %u)", cd,
                        cd->flags);
            }
            /* set the previous match offset to the start of this match + 1 */
            prev_offset = (match_offset - (cd->content_len - 1));
            SCLogDebug("trying to see if there is another match after prev_offset %" PRIu32,
                    prev_offset);
        } while(1);

    } else if (smd->type == DETECT_ABSENT) {
        const DetectAbsentData *id = (DetectAbsentData *)smd->ctx;
        if (!id->or_else) {
            // we match only on absent buffer
            goto no_match;
        }
        goto match;
    } else if (smd->type == DETECT_ISDATAAT) {
        SCLogDebug("inspecting isdataat");

        const DetectIsdataatData *id = (DetectIsdataatData *)smd->ctx;
        uint32_t dataat = id->dataat;
        if (id->flags & ISDATAAT_OFFSET_VAR) {
            uint64_t be_value = det_ctx->byte_values[dataat];
            if (be_value >= 100000000) {
                if ((id->flags & ISDATAAT_NEGATED) == 0) {
                    SCLogDebug("extracted value %"PRIu64" very big: no match", be_value);
                    goto no_match;
                }
                SCLogDebug("extracted value way %"PRIu64" very big: match", be_value);
                goto match;
            }
            dataat = (uint32_t)be_value;
            SCLogDebug("isdataat: using value %u from byte_extract local_id %u", dataat, id->dataat);
        }

        if (id->flags & ISDATAAT_RELATIVE) {
            if (det_ctx->buffer_offset + dataat > buffer_len) {
                SCLogDebug("det_ctx->buffer_offset + dataat %"PRIu32" > %"PRIu32, det_ctx->buffer_offset + dataat, buffer_len);
                if (id->flags & ISDATAAT_NEGATED)
                    goto match;
                if ((id->flags & ISDATAAT_OFFSET_VAR) == 0) {
                    goto no_match_discontinue;
                }
                goto no_match;
            } else {
                SCLogDebug("relative isdataat match");
                if (id->flags & ISDATAAT_NEGATED) {
                    goto no_match;
                }
                goto match;
            }
        } else {
            if (dataat < buffer_len) {
                SCLogDebug("absolute isdataat match");
                if (id->flags & ISDATAAT_NEGATED) {
                    if ((id->flags & ISDATAAT_OFFSET_VAR) == 0) {
                        goto no_match_discontinue;
                    }
                    goto no_match;
                }
                goto match;
            } else {
                SCLogDebug("absolute isdataat mismatch, id->isdataat %"PRIu32", buffer_len %"PRIu32"", dataat, buffer_len);
                if (id->flags & ISDATAAT_NEGATED)
                    goto match;
                if ((id->flags & ISDATAAT_OFFSET_VAR) == 0) {
                    goto no_match_discontinue;
                }
                goto no_match;
            }
        }

    } else if (smd->type == DETECT_PCRE) {
        SCLogDebug("inspecting pcre");
        const DetectPcreData *pe = (const DetectPcreData *)smd->ctx;
        uint32_t prev_buffer_offset = det_ctx->buffer_offset;
        uint32_t prev_offset = 0;

        det_ctx->pcre_match_start_offset = 0;
        do {
            int r = DetectPcrePayloadMatch(det_ctx, s, smd, p, f, buffer, buffer_len);
            if (r == 0) {
                goto no_match;
            }
            if (!(pe->flags & DETECT_PCRE_RELATIVE_NEXT)) {
                SCLogDebug("no relative match coming up, so this is a match");
                goto match;
            }
            KEYWORD_PROFILING_END(det_ctx, smd->type, 1);

            /* save it, in case we need to do a pcre match once again */
            prev_offset = det_ctx->pcre_match_start_offset;

            /* see if the next payload keywords match. If not, we will
             * search for another occurrence of this pcre and see
             * if the others match, until we run out of matches */
            r = DetectEngineContentInspectionInternal(det_ctx, ctx, s, smd + 1, p, f, buffer,
                    buffer_len, stream_start_offset, flags, inspection_mode);
            if (r == 1) {
                SCReturnInt(1);
            } else if (r == -1) {
                SCReturnInt(-1);
            }

            if (prev_offset == 0) {
                // This happens for negated PCRE
                // We do not search for another occurrence of this pcre
                SCReturnInt(0);
            }
            det_ctx->buffer_offset = prev_buffer_offset;
            det_ctx->pcre_match_start_offset = prev_offset;
        } while (1);

    } else if (smd->type == DETECT_ENTROPY) {
        if (!DetectEntropyDoMatch(det_ctx, s, smd->ctx, buffer, buffer_len)) {
            goto no_match;
        }
        goto match;
    } else if (smd->type == DETECT_BYTETEST) {
        const DetectBytetestData *btd = (const DetectBytetestData *)smd->ctx;
        uint16_t btflags = btd->flags;
        int32_t offset = btd->offset;
        uint64_t value = btd->value;
        int32_t nbytes = btd->nbytes;
        if (btflags & DETECT_BYTETEST_OFFSET_VAR) {
            // This cast is wrong if a 64-bit value was extracted
            offset = (int32_t)det_ctx->byte_values[offset];
        }
        if (btflags & DETECT_BYTETEST_VALUE_VAR) {
            value = det_ctx->byte_values[value];
        }
        if (btflags & DETECT_BYTETEST_NBYTES_VAR) {
            // This cast is wrong if a 64-bit value was extracted
            nbytes = (int32_t)det_ctx->byte_values[nbytes];
        }

        /* if we have dce enabled we will have to use the endianness
         * specified by the dce header */
        if (btflags & DETECT_BYTETEST_DCE) {
            /* enable the endianness flag temporarily.  once we are done
             * processing we reset the flags to the original value*/
            btflags |= ((flags & DETECT_CI_FLAGS_DCE_LE) ?
                      DETECT_BYTETEST_LITTLE: 0);
        }

        if (DetectBytetestDoMatch(det_ctx, s, smd->ctx, buffer, buffer_len, btflags, offset, nbytes,
                    value) != 1) {
            goto no_match;
        }

        goto match;

    } else if (smd->type == DETECT_BYTEJUMP) {
        const DetectBytejumpData *bjd = (const DetectBytejumpData *)smd->ctx;
        uint16_t bjflags = bjd->flags;
        int32_t offset = bjd->offset;
        int32_t nbytes;

        if (bjflags & DETECT_BYTEJUMP_OFFSET_VAR) {
            // This cast is wrong if a 64-bit value was extracted
            offset = (int32_t)det_ctx->byte_values[offset];
            SCLogDebug("[BJ] using offset value %d", offset);
        }

        if (bjflags & DETECT_BYTEJUMP_NBYTES_VAR) {
            // This cast is wrong if a 64-bit value was extracted
            nbytes = (int32_t)det_ctx->byte_values[bjd->nbytes];
            SCLogDebug("[BJ] using nbytes value %d [index %d]", nbytes, bjd->nbytes);
        } else {
            nbytes = bjd->nbytes;
            SCLogDebug("[BJ] using nbytes value %d [index n/a]", nbytes);
        }

        /* if we have dce enabled we will have to use the endianness
         * specified by the dce header */
        if (bjflags & DETECT_BYTEJUMP_DCE) {
            /* enable the endianness flag temporarily.  once we are done
             * processing we reset the flags to the original value*/
            bjflags |= ((flags & DETECT_CI_FLAGS_DCE_LE) ?
                      DETECT_BYTEJUMP_LITTLE: 0);
        }

        if (!DetectBytejumpDoMatch(
                    det_ctx, s, smd->ctx, buffer, buffer_len, bjflags, nbytes, offset)) {
            goto no_match;
        }

        goto match;

    } else if (smd->type == DETECT_BYTE_EXTRACT) {

        const SCDetectByteExtractData *bed = (const SCDetectByteExtractData *)smd->ctx;
        uint8_t endian = bed->endian;

        /* if we have dce enabled we will have to use the endianness
         * specified by the dce header */
        if ((bed->flags & DETECT_BYTE_EXTRACT_FLAG_ENDIAN) && endian == EndianDCE &&
                flags & (DETECT_CI_FLAGS_DCE_LE | DETECT_CI_FLAGS_DCE_BE)) {

            /* enable the endianness flag temporarily.  once we are done
             * processing we reset the flags to the original value*/
            endian |= ((flags & DETECT_CI_FLAGS_DCE_LE) ? LittleEndian : BigEndian);
        }

        if (DetectByteExtractDoMatch(det_ctx, smd, s, buffer, buffer_len,
                    &det_ctx->byte_values[bed->local_id], endian) != 1) {
            goto no_match;
        }

        SCLogDebug("[BE] Fetched value for index %d: %"PRIu64,
                   bed->local_id, det_ctx->byte_values[bed->local_id]);
        goto match;

    } else if (smd->type == DETECT_BYTEMATH) {

        const DetectByteMathData *bmd = (const DetectByteMathData *)smd->ctx;
        uint8_t endian = bmd->endian;

        /* if we have dce enabled we will have to use the endianness
         * specified by the dce header */
        if ((bmd->flags & DETECT_BYTEMATH_FLAG_ENDIAN) && endian == (int)EndianDCE &&
                flags & (DETECT_CI_FLAGS_DCE_LE | DETECT_CI_FLAGS_DCE_BE)) {
            /* enable the endianness flag temporarily.  once we are done
             * processing we reset the flags to the original value*/
            endian = (uint8_t)((flags & DETECT_CI_FLAGS_DCE_LE) ? LittleEndian : BigEndian);
        }
        uint64_t rvalue;
        if (bmd->flags & DETECT_BYTEMATH_FLAG_RVALUE_VAR) {
            rvalue = det_ctx->byte_values[bmd->rvalue];
        } else {
            rvalue = bmd->rvalue;
        }

        uint8_t nbytes;
        if (bmd->flags & DETECT_BYTEMATH_FLAG_NBYTES_VAR) {
            nbytes = (uint8_t)det_ctx->byte_values[bmd->nbytes];
        } else {
            nbytes = bmd->nbytes;
        }

        if (DetectByteMathDoMatch(det_ctx, bmd, s, buffer, buffer_len, nbytes, rvalue,
                    &det_ctx->byte_values[bmd->local_id], endian) != 1) {
            goto no_match;
        }

        SCLogDebug("[BM] Fetched value for index %d: %"PRIu64,
                   bmd->local_id, det_ctx->byte_values[bmd->local_id]);
        goto match;

    } else if (smd->type == DETECT_BSIZE) {

        const bool eof = (flags & DETECT_CI_FLAGS_END);
        const uint64_t data_size = buffer_len + stream_start_offset;
        int r = DetectBsizeMatch(smd->ctx, data_size, eof);
        if (r < 0) {
            goto no_match_discontinue;
        } else if (r == 0) {
            goto no_match;
        }
        goto match;

    } else if (smd->type == DETECT_DATASET) {

        //PrintRawDataFp(stdout, buffer, buffer_len);
        const DetectDatasetData *sd = (const DetectDatasetData *) smd->ctx;
        int r = DetectDatasetBufferMatch(det_ctx, sd, buffer, buffer_len); //TODO buffer offset?
        if (r == 1) {
            goto match;
        }
        goto no_match_discontinue;

    } else if (smd->type == DETECT_DATAREP) {

        //PrintRawDataFp(stdout, buffer, buffer_len);
        const DetectDatarepData *sd = (const DetectDatarepData *) smd->ctx;
        int r = DetectDatarepBufferMatch(det_ctx, sd, buffer, buffer_len); //TODO buffer offset?
        if (r == 1) {
            goto match;
        }
        goto no_match_discontinue;

    } else if (smd->type == DETECT_URILEN) {
        SCLogDebug("inspecting uri len");

        int r;
        const DetectUrilenData *urilend = (const DetectUrilenData *)smd->ctx;
        if (buffer_len > UINT16_MAX) {
            r = DetectU16Match(UINT16_MAX, &urilend->du16);
        } else {
            r = DetectU16Match((uint16_t)buffer_len, &urilend->du16);
        }

        if (r == 1) {
            goto match;
        }
        goto no_match_discontinue;
    } else if (smd->type == DETECT_LUA) {
        SCLogDebug("lua starting");

        if (DetectLuaMatchBuffer(det_ctx, s, smd, buffer, buffer_len,
                    det_ctx->buffer_offset, f) != 1)
        {
            SCLogDebug("lua no_match");
            goto no_match;
        }
        SCLogDebug("lua match");
        goto match;
    } else if (smd->type == DETECT_BASE64_DECODE) {
        if (DetectBase64DecodeDoMatch(det_ctx, s, smd, buffer, buffer_len)) {
            if (s->sm_arrays[DETECT_SM_LIST_BASE64_DATA] != NULL) {
                if (det_ctx->base64_decoded_len) {
                    KEYWORD_PROFILING_END(det_ctx, smd->type, 1);
                    int r = DetectEngineContentInspectionInternal(det_ctx, ctx, s,
                            s->sm_arrays[DETECT_SM_LIST_BASE64_DATA], NULL, f,
                            det_ctx->base64_decoded, det_ctx->base64_decoded_len, 0,
                            DETECT_CI_FLAGS_SINGLE, DETECT_ENGINE_CONTENT_INSPECTION_MODE_STATE);
                    if (r == 1) {
                        /* Base64 is a terminal list. */
                        goto final_match;
                    }
                }
            }
        }
    } else if (smd->type == DETECT_ASN1) {
        if (!DetectAsn1Match(smd, buffer, buffer_len, det_ctx->buffer_offset)) {
            SCLogDebug("asn1 no_match");
            goto no_match;
        }
        SCLogDebug("asn1 match");
        goto match;
    } else {
        SCLogDebug("sm->type %u", smd->type);
#ifdef DEBUG
        BUG_ON(1);
#endif
    }

no_match:
    KEYWORD_PROFILING_END(det_ctx, smd->type, 0);
    SCReturnInt(0);

no_match_discontinue:
    KEYWORD_PROFILING_END(det_ctx, smd->type, 0);
    SCReturnInt(-1);

match:
    /* this sigmatch matched, inspect the next one. If it was the last,
     * the buffer portion of the signature matched. */
    if (!smd->is_last) {
        KEYWORD_PROFILING_END(det_ctx, smd->type, 1);
        int r = DetectEngineContentInspectionInternal(det_ctx, ctx, s, smd + 1, p, f, buffer,
                buffer_len, stream_start_offset, flags, inspection_mode);
        SCReturnInt(r);
    }
final_match:
    KEYWORD_PROFILING_END(det_ctx, smd->type, 1);
    SCReturnInt(1);
}

bool DetectEngineContentInspection(DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
        const Signature *s, const SigMatchData *smd, Packet *p, Flow *f, const uint8_t *buffer,
        const uint32_t buffer_len, const uint64_t stream_start_offset, const uint8_t flags,
        const enum DetectContentInspectionType inspection_mode)
{
    struct DetectEngineContentInspectionCtx ctx = { .recursion.count = 0,
        .recursion.limit = de_ctx->inspection_recursion_limit };
    det_ctx->buffer_offset = 0;

    int r = DetectEngineContentInspectionInternal(det_ctx, &ctx, s, smd, p, f, buffer, buffer_len,
            stream_start_offset, flags, inspection_mode);
#ifdef UNITTESTS
    ut_inspection_recursion_counter = ctx.recursion.count;
#endif
    if (r == 1)
        return true;
    else
        return false;
}

uint8_t DetectEngineInspectPacketPayload(DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
        const Signature *s, Flow *f, Packet *p)
{
    SCEnter();

    if (s->sm_arrays[DETECT_SM_LIST_PMATCH] == NULL) {
        SCReturnInt(0);
    }
#ifdef DEBUG
    det_ctx->payload_persig_cnt++;
    det_ctx->payload_persig_size += p->payload_len;
#endif
    const bool match = DetectEngineContentInspection(de_ctx, det_ctx, s,
            s->sm_arrays[DETECT_SM_LIST_PMATCH], p, f, p->payload, p->payload_len, 0,
            DETECT_CI_FLAGS_SINGLE, DETECT_ENGINE_CONTENT_INSPECTION_MODE_PAYLOAD);
    if (match) {
        SCReturnInt(1);
    }
    SCReturnInt(0);
}

static int DetectEngineInspectRulePayloadMatches(
     DetectEngineThreadCtx *det_ctx,
     const DetectEnginePktInspectionEngine *engine,
     const Signature *s, Packet *p, uint8_t *alert_flags)
{
    SCEnter();

    DetectEngineCtx *de_ctx = det_ctx->de_ctx;

    KEYWORD_PROFILING_SET_LIST(det_ctx, DETECT_SM_LIST_PMATCH);
    /* if we have stream msgs, inspect against those first,
     * but not for a "dsize" signature */
    if (s->flags & SIG_FLAG_REQUIRE_STREAM) {
        int pmatch = 0;
        if (p->flags & PKT_DETECT_HAS_STREAMDATA) {
            pmatch = DetectEngineInspectStreamPayload(de_ctx, det_ctx, s, p->flow, p);
            if (pmatch) {
                *alert_flags |= PACKET_ALERT_FLAG_STREAM_MATCH;
            }
        }
        /* no match? then inspect packet payload */
        if (pmatch == 0) {
            SCLogDebug("no match in stream, fall back to packet payload");

            /* skip if we don't have to inspect the packet and segment was
             * added to stream */
            if (!(s->flags & SIG_FLAG_REQUIRE_PACKET) && (p->flags & PKT_STREAM_ADD)) {
                return DETECT_ENGINE_INSPECT_SIG_NO_MATCH;
            }
            if (s->flags & SIG_FLAG_REQUIRE_STREAM_ONLY) {
                SCLogDebug("SIG_FLAG_REQUIRE_STREAM_ONLY, so no match");
                return DETECT_ENGINE_INSPECT_SIG_NO_MATCH;
            }
            if (DetectEngineInspectPacketPayload(de_ctx, det_ctx, s, p->flow, p) != 1) {
                return DETECT_ENGINE_INSPECT_SIG_NO_MATCH;
            }
        }
    } else {
        if (DetectEngineInspectPacketPayload(de_ctx, det_ctx, s, p->flow, p) != 1) {
            return DETECT_ENGINE_INSPECT_SIG_NO_MATCH;
        }
    }
    return DETECT_ENGINE_INSPECT_SIG_MATCH;
}

int DetectEnginePktInspectionSetup(Signature *s)
{
    /* only handle PMATCH here if we're not an app inspect rule */
    if (s->sm_arrays[DETECT_SM_LIST_PMATCH] && (s->init_data->init_flags & SIG_FLAG_INIT_STATE_MATCH) == 0) {
        if (DetectEnginePktInspectionAppend(
                    s, DetectEngineInspectRulePayloadMatches, NULL, DETECT_SM_LIST_PMATCH) < 0)
            return -1;
        SCLogDebug("sid %u: DetectEngineInspectRulePayloadMatches appended", s->id);
    }

    if (s->sm_arrays[DETECT_SM_LIST_MATCH]) {
        if (DetectEnginePktInspectionAppend(
                    s, DetectEngineInspectRulePacketMatches, NULL, DETECT_SM_LIST_MATCH) < 0)
            return -1;
        SCLogDebug("sid %u: DetectEngineInspectRulePacketMatches appended", s->id);
    }

    return 0;
}

bool DetectEnginePktInspectionRun(ThreadVars *tv,
        DetectEngineThreadCtx *det_ctx, const Signature *s,
        Flow *f, Packet *p,
        uint8_t *alert_flags)
{
    SCEnter();

    for (DetectEnginePktInspectionEngine *e = s->pkt_inspect; e != NULL; e = e->next) {
        if (e->v1.Callback(det_ctx, e, s, p, alert_flags) != DETECT_ENGINE_INSPECT_SIG_MATCH) {
            SCLogDebug("sid %u: e %p Callback returned no match", s->id, e);
            return false;
        }
        SCLogDebug("sid %u: e %p Callback returned true", s->id, e);
    }

    SCLogDebug("sid %u: returning true", s->id);
    return true;
}

static inline uint8_t DetectRulePacketRules(ThreadVars *const tv,
        const DetectEngineCtx *const de_ctx, DetectEngineThreadCtx *const det_ctx, Packet *const p,
        Flow *const pflow, const DetectRunScratchpad *scratch)
{
    uint8_t action = 0;
    bool fw_verdict = false;
    const bool have_fw_rules = EngineModeIsFirewall();
    const Signature *next_s = NULL;

    /* inspect the sigs against the packet */
    /* Prefetch the next signature. */
    SigIntId match_cnt = det_ctx->match_array_cnt;
#ifdef PROFILING
    if (tv) {
        StatsAddUI64(tv, det_ctx->counter_match_list,
                             (uint64_t)match_cnt);
    }
#endif
    Signature **match_array = det_ctx->match_array;

    SGH_PROFILING_RECORD(det_ctx, scratch->sgh);
#ifdef PROFILING
    if (match_cnt >= de_ctx->profile_match_logging_threshold)
        RulesDumpMatchArray(det_ctx, scratch->sgh, p);
#endif

    bool skip_fw = false;
    uint32_t sflags, next_sflags = 0;
    if (match_cnt) {
        next_s = *match_array++;
        next_sflags = next_s->flags;
    }
    while (match_cnt--) {
        RULE_PROFILING_START(p);
        bool break_out_of_packet_filter = false;
        uint8_t alert_flags = 0;
#ifdef PROFILE_RULES
        bool smatch = false; /* signature match */
#endif
        const Signature *s = next_s;
        sflags = next_sflags;
        if (match_cnt) {
            next_s = *match_array++;
            next_sflags = next_s->flags;
        }
        const uint8_t s_proto_flags = s->proto.flags;

        SCLogDebug("packet %" PRIu64 ": inspecting signature id %" PRIu32 "", p->pcap_cnt, s->id);

        /* if we accept:hook'd the `packet_filter` hook, we skip the rest of the firewall rules. */
        if (s->flags & SIG_FLAG_FIREWALL) {
            if (skip_fw) {
                SCLogDebug("skipping firewall rule %u", s->id);
                goto next;
            }
        } else if (have_fw_rules) {
            /* fw mode, we skip anything after the fw rules if:
             * - flow pass is set
             * - packet pass (e.g. exception policy) */
            if (p->flags & PKT_NOPACKET_INSPECTION ||
                    (pflow != NULL && pflow->flags & (FLOW_ACTION_PASS))) {
                SCLogDebug("skipping firewall rule %u", s->id);
                break_out_of_packet_filter = true;
                goto next;
            }
        }

        if (s->app_inspect != NULL) {
            goto next; // handle sig in DetectRunTx
        }
        if (s->frame_inspect != NULL) {
            goto next; // handle sig in DetectRunFrame
        }

        /* skip pkt sigs for flow end packets */
        if ((p->flags & PKT_PSEUDO_STREAM_END) != 0 && s->type == SIG_TYPE_PKT)
            goto next;

        /* don't run mask check for stateful rules.
         * There we depend on prefilter */
        if ((s->mask & p->sig_mask) != s->mask) {
            SCLogDebug("mask mismatch %x & %x != %x", s->mask, p->sig_mask, s->mask);
            goto next;
        }

        if (SigDsizePrefilter(p, s, sflags))
            goto next;

        /* if the sig has alproto and the session as well they should match */
        if (likely(sflags & SIG_FLAG_APPLAYER)) {
            if (s->alproto != ALPROTO_UNKNOWN && !AppProtoEquals(s->alproto, scratch->alproto)) {
                SCLogDebug("alproto mismatch");
                goto next;
            }
        }

        if (!DetectRunInspectRuleHeader(p, pflow, s, sflags, s_proto_flags)) {
            goto next;
        }

        if (!DetectEnginePktInspectionRun(tv, det_ctx, s, pflow, p, &alert_flags)) {
            goto next;
        }

#ifdef PROFILE_RULES
        smatch = true;
#endif
        DetectRunPostMatch(tv, det_ctx, p, s);

        uint64_t txid = PACKET_ALERT_NOTX;
        if (pflow && pflow->alstate) {
            uint8_t dir = (p->flowflags & FLOW_PKT_TOCLIENT) ? STREAM_TOCLIENT : STREAM_TOSERVER;
            txid = AppLayerParserGetTransactionInspectId(pflow->alparser, dir);
            if ((s->alproto != ALPROTO_UNKNOWN && pflow->proto == IPPROTO_UDP) ||
                    (de_ctx->guess_applayer && IsOnlyTxInDirection(pflow, txid, dir))) {
                // if there is a UDP specific app-layer signature,
                // or only one live transaction
                // try to use the good tx for the packet direction
                void *tx_ptr =
                        AppLayerParserGetTx(pflow->proto, pflow->alproto, pflow->alstate, txid);
                AppLayerTxData *txd =
                        tx_ptr ? AppLayerParserGetTxData(pflow->proto, pflow->alproto, tx_ptr)
                               : NULL;
                if (txd && txd->guessed_applayer_logged < de_ctx->guess_applayer_log_limit) {
                    alert_flags |= PACKET_ALERT_FLAG_TX;
                    if (pflow->proto != IPPROTO_UDP) {
                        alert_flags |= PACKET_ALERT_FLAG_TX_GUESSED;
                    }
                    txd->guessed_applayer_logged++;
                }
            }
        }
        AlertQueueAppend(det_ctx, s, p, txid, alert_flags);

        if (det_ctx->post_rule_work_queue.len > 0) {
            /* run post match prefilter engines on work queue */
            PrefilterPostRuleMatch(det_ctx, scratch->sgh, p, pflow);

            if (det_ctx->pmq.rule_id_array_cnt > 0) {
                /* undo "prefetch" */
                if (next_s)
                    match_array--;
                /* create temporary rule pointer array starting
                 * at where we are in the current match array */
                const Signature *replace[de_ctx->sig_array_len]; // TODO heap?
                SCLogDebug("sig_array_len %u det_ctx->pmq.rule_id_array_cnt %u",
                        de_ctx->sig_array_len, det_ctx->pmq.rule_id_array_cnt);
                const Signature **r = replace;
                for (uint32_t x = 0; x < match_cnt; x++) {
                    *r++ = match_array[x];
                    SCLogDebug("appended %u", match_array[x]->id);
                }
                /* append the prefilter results, then sort it */
                for (uint32_t x = 0; x < det_ctx->pmq.rule_id_array_cnt; x++) {
                    SCLogDebug("adding iid %u", det_ctx->pmq.rule_id_array[x]);
                    Signature *ts = de_ctx->sig_array[det_ctx->pmq.rule_id_array[x]];
                    SCLogDebug("adding id %u", ts->id);
                    if (ts->app_inspect == NULL) {
                        *r++ = ts;
                        match_cnt++;
                    }
                }
                if (match_cnt > 1) {
                    qsort(replace, match_cnt, sizeof(Signature *), SortHelper);
                }
                /* rewrite match_array to include the new additions, and deduplicate
                 * while at it. */
                Signature **m = match_array;
                Signature *last_sig = NULL;
                uint32_t skipped = 0;
                for (uint32_t x = 0; x < match_cnt; x++) {
                    /* de-duplicate */
                    if (last_sig == *m) {
                        skipped++;
                        continue;
                    }
                    last_sig = *m;
                    *m++ = (Signature *)replace[x];
                }
                match_cnt -= skipped;
                /* prefetch next */
                next_s = *match_array++;
                next_sflags = next_s->flags;
                SCLogDebug("%u rules added", det_ctx->pmq.rule_id_array_cnt);
                det_ctx->post_rule_work_queue.len = 0;
                PMQ_RESET(&det_ctx->pmq);
            }
        }

        /* firewall logic in the packet:filter table:
         * 1. firewall rules preceed the packet:td rules in the list
         * 2. if no rule issues an accept, we drop
         * 3. drop is immediate
         * 4. accept:
         *    - hook: skip rest of fw rules, inspect packet:td rules
         *    - packet: immediate accept, no packet:td or app:* inspect
         *    - flow: as packet, but applied to all future packets in the
         *            flow as well
         */
        if (s->flags & SIG_FLAG_FIREWALL) {
            if (s->action & (ACTION_ACCEPT)) {
                fw_verdict = true;

                enum ActionScope as = s->action_scope;
                if (as == ACTION_SCOPE_HOOK) {
                    /* accept:hook: jump to first TD. Implemented as:
                     * skip until the first TD rule.
                     * Don't update action as we're just continuing to the next hook. */
                    skip_fw = true;

                } else if (as == ACTION_SCOPE_PACKET) {
                    /* accept:packet: break loop, return accept */
                    action |= s->action;
                    break_out_of_packet_filter = true;

                } else if (as == ACTION_SCOPE_FLOW) {
                    /* accept:flow: break loop, return accept */
                    action |= s->action;
                    break_out_of_packet_filter = true;

                    /* set immediately, as we're in hook "packet_filter" */
                    if (pflow) {
                        pflow->flags |= FLOW_ACTION_ACCEPT;
                    }
                }
            } else if (s->action & ACTION_DROP) {
                /* apply a drop immediately here */
                fw_verdict = true;
                action |= s->action;
                break_out_of_packet_filter = true;
            }
        }
next:
        DetectVarProcessList(det_ctx, pflow, p);
        DetectReplaceFree(det_ctx);
        RULE_PROFILING_END(det_ctx, s, smatch, p);

        /* fw accept:packet or accept:flow means we're done here */
        if (break_out_of_packet_filter)
            break;

        continue;
    }

    /* if no rule told us to accept, and no rule explicitly dropped, we invoke the default drop
     * policy
     */
    if (have_fw_rules && scratch->default_action == ACTION_DROP) {
        if (!fw_verdict) {
            DEBUG_VALIDATE_BUG_ON(action & ACTION_DROP);
            PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_DEFAULT_PACKET_POLICY);
            action |= ACTION_DROP;
        } else {
            /* apply fw action */
            p->action |= action;
        }
    }
    return action;
}

static void DetectRunTx(ThreadVars *tv,
                    DetectEngineCtx *de_ctx,
                    DetectEngineThreadCtx *det_ctx,
                    Packet *p,
                    Flow *f,
                    DetectRunScratchpad *scratch)
{
    const uint8_t flow_flags = scratch->flow_flags;
    const SigGroupHead * const sgh = scratch->sgh;
    void * const alstate = f->alstate;
    const uint8_t ipproto = f->proto;
    const AppProto alproto = f->alproto;

    const uint64_t total_txs = AppLayerParserGetTxCnt(f, alstate);
    uint64_t tx_id_min = AppLayerParserGetTransactionInspectId(f->alparser, flow_flags);
    const int tx_end_state = AppLayerParserGetStateProgressCompletionStatus(alproto, flow_flags);

    AppLayerGetTxIteratorFunc IterFunc = AppLayerGetTxIterator(ipproto, alproto);
    AppLayerGetTxIterState state = { 0 };

    uint32_t fw_verdicted = 0;
    uint32_t tx_inspected = 0;
    const bool have_fw_rules = EngineModeIsFirewall();

    SCLogDebug("packet %" PRIu64, p->pcap_cnt);

    while (1) {
        AppLayerGetTxIterTuple ires = IterFunc(ipproto, alproto, alstate, tx_id_min, total_txs, &state);
        if (ires.tx_ptr == NULL)
            break;

        DetectTransaction tx =
                GetDetectTx(ipproto, alproto, ires.tx_id, ires.tx_ptr, tx_end_state, flow_flags);
        if (tx.tx_ptr == NULL) {
            SCLogDebug("%p/%"PRIu64" no transaction to inspect",
                    tx.tx_ptr, tx_id_min);

            tx_id_min++; // next (if any) run look for +1
            goto next;
        }
        tx_id_min = tx.tx_id + 1; // next look for cur + 1
        tx_inspected++;

        SCLogDebug("%p/%" PRIu64 " txd flags %02x", tx.tx_ptr, tx_id_min, tx.tx_data_ptr->flags);

        det_ctx->tx_id = tx.tx_id;
        det_ctx->tx_id_set = true;
        det_ctx->p = p;

        bool do_sort = false; // do we need to sort the tx candidate list?
        uint32_t array_idx = 0;
        uint32_t total_rules = det_ctx->match_array_cnt;
        total_rules += (tx.de_state ? tx.de_state->cnt : 0);

        /* run prefilter engines and merge results into a candidates array */
        if (sgh->tx_engines) {
            PACKET_PROFILING_DETECT_START(p, PROF_DETECT_PF_TX);
            DetectRunPrefilterTx(det_ctx, sgh, p, ipproto, flow_flags, alproto,
                    alstate, &tx);
            PACKET_PROFILING_DETECT_END(p, PROF_DETECT_PF_TX);
            SCLogDebug("%p/%"PRIu64" rules added from prefilter: %u candidates",
                    tx.tx_ptr, tx.tx_id, det_ctx->pmq.rule_id_array_cnt);

            total_rules += det_ctx->pmq.rule_id_array_cnt;
            if (!(RuleMatchCandidateTxArrayHasSpace(det_ctx, total_rules))) {
                RuleMatchCandidateTxArrayExpand(det_ctx, total_rules);
            }

            for (uint32_t i = 0; i < det_ctx->pmq.rule_id_array_cnt; i++) {
                const Signature *s = de_ctx->sig_array[det_ctx->pmq.rule_id_array[i]];
                const SigIntId id = s->iid;
                det_ctx->tx_candidates[array_idx].s = s;
                det_ctx->tx_candidates[array_idx].id = id;
                det_ctx->tx_candidates[array_idx].flags = NULL;
                det_ctx->tx_candidates[array_idx].stream_reset = 0;
                array_idx++;
            }
            PMQ_RESET(&det_ctx->pmq);
        } else {
            if (!(RuleMatchCandidateTxArrayHasSpace(det_ctx, total_rules))) {
                RuleMatchCandidateTxArrayExpand(det_ctx, total_rules);
            }
        }

        /* merge 'state' rules from the regular prefilter */
#ifdef PROFILING
        uint32_t x = array_idx;
#endif
        RuleMatchCandidateMergeStateRules(det_ctx, &array_idx);

        /* merge stored state into results */
        if (tx.de_state != NULL) {
            const uint32_t old = array_idx;

            /* if tx.de_state->flags has 'new file' set and sig below has
             * 'file inspected' flag, reset the file part of the state */
            const bool have_new_file = (tx.de_state->flags & DETECT_ENGINE_STATE_FLAG_FILE_NEW);
            if (have_new_file) {
                SCLogDebug("%p/%"PRIu64" destate: need to consider new file",
                        tx.tx_ptr, tx.tx_id);
                tx.de_state->flags &= ~DETECT_ENGINE_STATE_FLAG_FILE_NEW;
            }

            SigIntId state_cnt = 0;
            DeStateStore *tx_store = tx.de_state->head;
            for (; tx_store != NULL; tx_store = tx_store->next) {
                SCLogDebug("tx_store %p", tx_store);

                SigIntId store_cnt = 0;
                for (store_cnt = 0;
                        store_cnt < DE_STATE_CHUNK_SIZE && state_cnt < tx.de_state->cnt;
                        store_cnt++, state_cnt++)
                {
                    DeStateStoreItem *item = &tx_store->store[store_cnt];
                    SCLogDebug("rule id %u, inspect_flags %u", item->sid, item->flags);
                    if (have_new_file && (item->flags & DE_STATE_FLAG_FILE_INSPECT)) {
                        /* remove part of the state. File inspect engine will now
                         * be able to run again */
                        item->flags &= ~(DE_STATE_FLAG_SIG_CANT_MATCH|DE_STATE_FLAG_FULL_INSPECT|DE_STATE_FLAG_FILE_INSPECT);
                        SCLogDebug("rule id %u, post file reset inspect_flags %u", item->sid, item->flags);
                    }
                    det_ctx->tx_candidates[array_idx].s = de_ctx->sig_array[item->sid];
                    det_ctx->tx_candidates[array_idx].id = item->sid;
                    det_ctx->tx_candidates[array_idx].flags = &item->flags;
                    det_ctx->tx_candidates[array_idx].stream_reset = 0;
                    array_idx++;
                }
            }
            do_sort |= (old && old != array_idx); // sort if continue list adds sids
            SCLogDebug("%p/%" PRIu64 " rules added from 'continue' list: %u", tx.tx_ptr, tx.tx_id,
                    array_idx - old);
        }
        if (do_sort) {
            qsort(det_ctx->tx_candidates, array_idx, sizeof(RuleMatchCandidateTx),
                    DetectRunTxSortHelper);
        }

#ifdef PROFILING
        if (array_idx >= de_ctx->profile_match_logging_threshold)
            RulesDumpTxMatchArray(det_ctx, scratch->sgh, p, tx.tx_id, array_idx, x);
#endif

#ifdef DEBUG
        for (uint32_t i = 0; i < array_idx; i++) {
            RuleMatchCandidateTx *can = &det_ctx->tx_candidates[i];
            const Signature *s = det_ctx->tx_candidates[i].s;
            SCLogDebug("%u: sid %u flags %p", i, s->id, can->flags);
        }
#endif
        bool skip_fw_hook = false;
        uint8_t skip_before_progress = 0;
        bool fw_next_progress_missing = false;

        /* if there are no rules / rule candidates, make sure we don't
         * invoke the default drop */
        if (have_fw_rules && array_idx == 0 && (tx.tx_data_ptr->flags & APP_LAYER_TX_ACCEPT)) {
            fw_verdicted++;

            /* current tx is the last we have, append a blank accept:packet */
            if (total_txs == tx.tx_id + 1) {
                DetectRunAppendDefaultAccept(det_ctx, p);
                return;
            }
            goto next;
        }

        bool tx_fw_verdict = false;
        /* run rules: inspect the match candidates */
        for (uint32_t i = 0; i < array_idx; i++) {
            RuleMatchCandidateTx *can = &det_ctx->tx_candidates[i];
            const Signature *s = det_ctx->tx_candidates[i].s;
            uint32_t *inspect_flags = det_ctx->tx_candidates[i].flags;
            bool break_out_of_app_filter = false;

            SCLogDebug("%" PRIu64 ": sid:%u: %s tx %u/%u/%u sig %u", p->pcap_cnt, s->id,
                    flow_flags & STREAM_TOSERVER ? "toserver" : "toclient", tx.tx_progress,
                    tx.detect_progress, tx.detect_progress_orig, s->app_progress_hook);

            /* deduplicate: rules_array is sorted, but not deduplicated:
             * both mpm and stored state could give us the same sid.
             * As they are back to back in that case we can check for it
             * here. We select the stored state one as that comes first
             * in the array. */
            while ((i + 1) < array_idx &&
                    det_ctx->tx_candidates[i].s == det_ctx->tx_candidates[i + 1].s) {
                SCLogDebug("%p/%" PRIu64 " inspecting SKIP NEXT: sid %u (%u), flags %08x",
                        tx.tx_ptr, tx.tx_id, s->id, s->iid, inspect_flags ? *inspect_flags : 0);
                i++;
            }

            /* skip fw rules if we're in accept:tx mode */
            if (have_fw_rules && (tx.tx_data_ptr->flags & APP_LAYER_TX_ACCEPT)) {
                /* append a blank accept:packet action for the APP_LAYER_TX_ACCEPT,
                 * if this is the last tx */
                if (!tx_fw_verdict) {
                    const bool accept_tx_applies_to_packet = total_txs == tx.tx_id + 1;
                    if (accept_tx_applies_to_packet) {
                        SCLogDebug("accept:(tx|hook): should be applied to the packet");
                        DetectRunAppendDefaultAccept(det_ctx, p);
                    }
                }
                tx_fw_verdict = true;

                if (s->flags & SIG_FLAG_FIREWALL) {
                    SCLogDebug("APP_LAYER_TX_ACCEPT, so skip rule");
                    continue;
                }

                /* threat detect rules will be inspected */
            }

            SCLogDebug("%p/%" PRIu64 " inspecting: sid %u (%u), flags %08x", tx.tx_ptr, tx.tx_id,
                    s->id, s->iid, inspect_flags ? *inspect_flags : 0);

            if (inspect_flags) {
                if (*inspect_flags & DE_STATE_FLAG_FULL_INSPECT) {
                    SCLogDebug("%p/%" PRIu64
                               " inspecting: sid %u (%u), flags %08x DE_STATE_FLAG_FULL_INSPECT",
                            tx.tx_ptr, tx.tx_id, s->id, s->iid, *inspect_flags);

                    /* if we're still in the same progress state as an earlier full
                     * match, we need to apply the same accept */
                    if (have_fw_rules && (s->flags & SIG_FLAG_FIREWALL) &&
                            (s->action & ACTION_ACCEPT) && s->app_progress_hook == tx.tx_progress) {
                        const bool fw_accept_to_packet = ApplyAcceptToPacket(total_txs, &tx, s);
                        break_out_of_app_filter = ApplyAccept(p, flow_flags, s, &tx, tx_end_state,
                                fw_next_progress_missing, &tx_fw_verdict, &skip_fw_hook,
                                &skip_before_progress);
                        if (fw_accept_to_packet)
                            DetectRunAppendDefaultAccept(det_ctx, p);
                        if (break_out_of_app_filter)
                            break;
                    }
                    continue;
                }
                if (*inspect_flags & DE_STATE_FLAG_SIG_CANT_MATCH) {
                    SCLogDebug("%p/%" PRIu64
                               " inspecting: sid %u (%u), flags %08x DE_STATE_FLAG_SIG_CANT_MATCH",
                            tx.tx_ptr, tx.tx_id, s->id, s->iid, *inspect_flags);
                    continue;
                }
            }

            if (inspect_flags) {
                /* continue previous inspection */
                SCLogDebug("%p/%" PRIu64 " Continuing sid %u", tx.tx_ptr, tx.tx_id, s->id);
            } else {
                /* start new inspection */
                SCLogDebug("%p/%"PRIu64" Start sid %u", tx.tx_ptr, tx.tx_id, s->id);
            }

            bool last_for_progress = false;
            if (have_fw_rules) {
                int fw_r = DetectRunTxCheckFirewallPolicy(det_ctx, p, f, &tx, s, i, array_idx,
                        &skip_fw_hook, skip_before_progress, &last_for_progress,
                        &fw_next_progress_missing);
                if (fw_r == -1)
                    continue;
                if (fw_r == 1)
                    break;
            }

            /* call individual rule inspection */
            RULE_PROFILING_START(p);
            const int r = DetectRunTxInspectRule(tv, de_ctx, det_ctx, p, f, flow_flags,
                    alstate, &tx, s, inspect_flags, can, scratch);
            if (r == 1) {
                /* match */
                DetectRunPostMatch(tv, det_ctx, p, s);

                /* see if we need to apply tx/hook accept to the packet. This can be needed when
                 * we've completed the inspection so far for an incomplete tx, and an accept:tx or
                 * accept:hook is the last match.*/
                const bool fw_accept_to_packet = ApplyAcceptToPacket(total_txs, &tx, s);

                uint8_t alert_flags = (PACKET_ALERT_FLAG_STATE_MATCH | PACKET_ALERT_FLAG_TX);
                if (fw_accept_to_packet) {
                    SCLogDebug("accept:(tx|hook): should be applied to the packet");
                    alert_flags |= PACKET_ALERT_FLAG_APPLY_ACTION_TO_PACKET;
                }

                SCLogDebug(
                        "%p/%" PRIu64 " sig %u (%u) matched", tx.tx_ptr, tx.tx_id, s->id, s->iid);
                AlertQueueAppend(det_ctx, s, p, tx.tx_id, alert_flags);

                if ((s->flags & SIG_FLAG_FIREWALL) && (s->action & ACTION_ACCEPT)) {
                    break_out_of_app_filter = ApplyAccept(p, flow_flags, s, &tx, tx_end_state,
                            fw_next_progress_missing, &tx_fw_verdict, &skip_fw_hook,
                            &skip_before_progress);
                }
            } else if (last_for_progress) {
                SCLogDebug("sid %u: not a match: %s rule, last_for_progress %s", s->id,
                        (s->flags & SIG_FLAG_FIREWALL) ? "firewall" : "regular",
                        BOOL2STR(last_for_progress));
                if (s->flags & SIG_FLAG_FIREWALL) {
                    SCLogDebug("%" PRIu64 ": %s default drop for progress", p->pcap_cnt,
                            flow_flags & STREAM_TOSERVER ? "toserver" : "toclient");
                    /* if this rule was the last for our progress state, and it didn't match,
                     * we have to invoke the default drop policy. */
                    PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_DEFAULT_APP_POLICY);
                    p->flow->flags |= FLOW_ACTION_DROP;
                    break_out_of_app_filter = true;
                    tx_fw_verdict = true;
                }
            }
            DetectVarProcessList(det_ctx, p->flow, p);
            RULE_PROFILING_END(det_ctx, s, r, p);

            if (det_ctx->post_rule_work_queue.len > 0) {
                SCLogDebug("%p/%" PRIu64 " post_rule_work_queue len %u", tx.tx_ptr, tx.tx_id,
                        det_ctx->post_rule_work_queue.len);
                /* run post match prefilter engines on work queue */
                PrefilterPostRuleMatch(det_ctx, scratch->sgh, p, f);

                uint32_t prev_array_idx = array_idx;
                for (uint32_t j = 0; j < det_ctx->pmq.rule_id_array_cnt; j++) {
                    const Signature *ts = de_ctx->sig_array[det_ctx->pmq.rule_id_array[j]];
                    if (ts->app_inspect != NULL) {
                        const SigIntId id = ts->iid;
                        det_ctx->tx_candidates[array_idx].s = ts;
                        det_ctx->tx_candidates[array_idx].id = id;
                        det_ctx->tx_candidates[array_idx].flags = NULL;
                        det_ctx->tx_candidates[array_idx].stream_reset = 0;
                        array_idx++;

                        SCLogDebug("%p/%" PRIu64 " rule %u (%u) added from 'post match' prefilter",
                                tx.tx_ptr, tx.tx_id, ts->id, id);
                    }
                }
                SCLogDebug("%p/%" PRIu64 " rules added from 'post match' prefilter: %u", tx.tx_ptr,
                        tx.tx_id, array_idx - prev_array_idx);
                if (prev_array_idx != array_idx) {
                    /* sort, but only part of array we're still going to process */
                    qsort(det_ctx->tx_candidates + i, array_idx - i, sizeof(RuleMatchCandidateTx),
                            DetectRunTxSortHelper);
                }
                det_ctx->post_rule_work_queue.len = 0;
                PMQ_RESET(&det_ctx->pmq);
            }

            if (break_out_of_app_filter)
                break;
        }
        if (tx_fw_verdict)
            fw_verdicted++;

        det_ctx->tx_id = 0;
        det_ctx->tx_id_set = false;
        det_ctx->p = NULL;

        /* see if we have any updated state to store in the tx */

        /* this side of the tx is done */
        if (tx.tx_progress >= tx.tx_end_state) {
            SCLogDebug("%" PRIu64 ": %s tx done", p->pcap_cnt,
                    flow_flags & STREAM_TOSERVER ? "toserver" : "toclient");
            const uint8_t inspected_flag = (flow_flags & STREAM_TOSERVER)
                                                   ? APP_LAYER_TX_INSPECTED_TS
                                                   : APP_LAYER_TX_INSPECTED_TC;
            tx.tx_data_ptr->flags |= inspected_flag;
            SCLogDebug("%p/%" PRIu64 " tx is done for direction %s. Progress %02x", tx.tx_ptr,
                    tx.tx_id, flow_flags & STREAM_TOSERVER ? "toserver" : "toclient",
                    tx.detect_progress);
        }

        if (tx.detect_progress != tx.detect_progress_orig) {
            SCLogDebug("%" PRIu64 ": %s tx state change %u -> %u", p->pcap_cnt,
                    flow_flags & STREAM_TOSERVER ? "toserver" : "toclient", tx.detect_progress_orig,
                    tx.detect_progress);
            SCLogDebug("%p/%" PRIu64 " Storing new progress %02x (was %02x)", tx.tx_ptr, tx.tx_id,
                    tx.detect_progress, tx.detect_progress_orig);

            StoreDetectProgress(&tx, flow_flags, tx.detect_progress);
        }

        InspectionBufferClean(det_ctx);

    next:
        if (!ires.has_next)
            break;
    }

    /* apply default policy if there were txs to inspect, we have fw rules and non of the rules
     * applied a policy. */
    SCLogDebug("packet %" PRIu64 ": tx_inspected %u fw_verdicted %u", p->pcap_cnt, tx_inspected,
            fw_verdicted);
    if (tx_inspected && have_fw_rules && tx_inspected != fw_verdicted) {
        SCLogDebug("%" PRIu64 ": %s default drop", p->pcap_cnt,
                flow_flags & STREAM_TOSERVER ? "toserver" : "toclient");
        PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_DEFAULT_APP_POLICY);
        p->flow->flags |= FLOW_ACTION_DROP;
        return;
    }
    /* if all tables have been bypassed, we accept:packet */
    if (tx_inspected == 0 && fw_verdicted == 0 && have_fw_rules) {
        DetectRunAppendDefaultAccept(det_ctx, p);
    }
}

static void DetectRun(ThreadVars *th_v,
        DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
        Packet *p)
{
    SCEnter();
    SCLogDebug("p->pcap_cnt %" PRIu64 " direction %s pkt_src %s", p->pcap_cnt,
            p->flow ? (FlowGetPacketDirection(p->flow, p) == TOSERVER ? "toserver" : "toclient")
                    : "noflow",
            PktSrcToString(p->pkt_src));

    /* Load the Packet's flow early, even though it might not be needed.
     * Mark as a constant pointer, although the flow itself can change. */
    Flow * const pflow = p->flow;

    DetectRunScratchpad scratch = DetectRunSetup(de_ctx, det_ctx, p, pflow, ACTION_DROP);

    /* run the IPonly engine */
    DetectRunInspectIPOnly(th_v, de_ctx, det_ctx, pflow, p);

    /* get our rule group */
    DetectRunGetRuleGroup(de_ctx, p, pflow, &scratch);
    /* if we didn't get a sig group head, we
     * have nothing to do.... */
    if (scratch.sgh == NULL) {
        SCLogDebug("no sgh for this packet, nothing to match against");
        goto end;
    }

    /* run the prefilters for packets */
    DetectRunPrefilterPkt(th_v, de_ctx, det_ctx, p, &scratch);

    PACKET_PROFILING_DETECT_START(p, PROF_DETECT_RULES);
    /* inspect the rules against the packet */
    const uint8_t pkt_policy = DetectRulePacketRules(th_v, de_ctx, det_ctx, p, pflow, &scratch);
    PACKET_PROFILING_DETECT_END(p, PROF_DETECT_RULES);

    /* Only FW rules will already have set the action, IDS rules go through PacketAlertFinalize
     *
     * If rules told us to drop or accept:packet/accept:flow, we skip app_filter and app_td.
     *
     * accept:hook won't have set the pkt_policy, so we simply continue.
     *
     * TODO what about app state progression, cleanup and such? */
    if (pkt_policy & (ACTION_DROP | ACTION_ACCEPT)) {
        goto end;
    }

    /* run tx/state inspection. Don't call for ICMP error msgs. */
    if (pflow && pflow->alstate && likely(pflow->proto == p->proto)) {
        if (p->proto == IPPROTO_TCP) {
            if ((p->flags & PKT_STREAM_EST) == 0) {
                SCLogDebug("packet %" PRIu64 ": skip tcp non-established", p->pcap_cnt);
                DetectRunAppendDefaultAccept(det_ctx, p);
                goto end;
            }
            const TcpSession *ssn = p->flow->protoctx;
            bool setting_nopayload = p->flow->alparser &&
                                     SCAppLayerParserStateIssetFlag(
                                             p->flow->alparser, APP_LAYER_PARSER_NO_INSPECTION) &&
                                     !(p->flags & PKT_NOPAYLOAD_INSPECTION);
            // we may be right after disabling app-layer (ssh)
            if (ssn &&
                    ((ssn->flags & STREAMTCP_FLAG_APP_LAYER_DISABLED) == 0 || setting_nopayload)) {
                // PACKET_PROFILING_DETECT_START(p, PROF_DETECT_TX);
                DetectRunFrames(th_v, de_ctx, det_ctx, p, pflow, &scratch);
                // PACKET_PROFILING_DETECT_END(p, PROF_DETECT_TX);
            }
            // no update to transactions
            if (!PKT_IS_PSEUDOPKT(p) && p->app_update_direction == 0 &&
                    ((PKT_IS_TOSERVER(p) && (p->flow->flags & FLOW_TS_APP_UPDATED) == 0) ||
                            (PKT_IS_TOCLIENT(p) && (p->flow->flags & FLOW_TC_APP_UPDATED) == 0))) {
                SCLogDebug("packet %" PRIu64 ": no app-layer update", p->pcap_cnt);
                DetectRunAppendDefaultAccept(det_ctx, p);
                goto end;
            }
        } else if (p->proto == IPPROTO_UDP) {
            DetectRunFrames(th_v, de_ctx, det_ctx, p, pflow, &scratch);
        }

        PACKET_PROFILING_DETECT_START(p, PROF_DETECT_TX);
        DetectRunTx(th_v, de_ctx, det_ctx, p, pflow, &scratch);
        PACKET_PROFILING_DETECT_END(p, PROF_DETECT_TX);
        /* see if we need to increment the inspect_id and reset the de_state */
        PACKET_PROFILING_DETECT_START(p, PROF_DETECT_TX_UPDATE);
        AppLayerParserSetTransactionInspectId(
                pflow, pflow->alparser, pflow->alstate, scratch.flow_flags, (scratch.sgh == NULL));
        PACKET_PROFILING_DETECT_END(p, PROF_DETECT_TX_UPDATE);
    } else {
        SCLogDebug("packet %" PRIu64 ": no flow / app-layer", p->pcap_cnt);
        DetectRunAppendDefaultAccept(det_ctx, p);
    }

end:
    DetectRunPostRules(th_v, de_ctx, det_ctx, p, pflow, &scratch);

    DetectRunCleanup(det_ctx, p, pflow);
    SCReturn;
}

static void DetectFlow(ThreadVars *tv,
                       DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
                       Packet *p)
{
    Flow *const f = p->flow;

    /* we check the flow drop here, and not the packet drop. This is
     * to allow stream engine "invalid" drop packets to still be
     * evaluated by the stream event rules. */
    if (f->flags & FLOW_ACTION_DROP) {
        DEBUG_VALIDATE_BUG_ON(!(PKT_IS_PSEUDOPKT(p)) && !PacketCheckAction(p, ACTION_DROP));
        SCReturn;
    }

    /* in firewall mode, we still need to run the fw rulesets even for exception policy pass */
    bool skip = false;
    if (EngineModeIsFirewall()) {
        skip = (f->flags & (FLOW_ACTION_ACCEPT));

    } else {
        skip = (p->flags & PKT_NOPACKET_INSPECTION || f->flags & (FLOW_ACTION_PASS));
    }
    if (skip) {
        /* enfore prior accept:flow */
        if (f->flags & FLOW_ACTION_ACCEPT) {
            p->action |= ACTION_ACCEPT;
        }
        /* hack: if we are in pass the entire flow mode, we need to still
         * update the inspect_id forward. So test for the condition here,
         * and call the update code if necessary. */
        const int pass = (f->flags & (FLOW_ACTION_PASS | FLOW_ACTION_ACCEPT));
        if (pass) {
            uint8_t flags = STREAM_FLAGS_FOR_PACKET(p);
            flags = FlowGetDisruptionFlags(f, flags);
            if (f->alstate) {
                AppLayerParserSetTransactionInspectId(f, f->alparser, f->alstate, flags, true);
            }
        }
        SCLogDebug("p->pcap %"PRIu64": no detection on packet, "
                "PKT_NOPACKET_INSPECTION is set", p->pcap_cnt);
        return;
    }

    /* see if the packet matches one or more of the sigs */
    DetectRun(tv, de_ctx, det_ctx, p);
}

TmEcode Detect(ThreadVars *tv, Packet *p, void *data)
{
    DEBUG_VALIDATE_PACKET(p);

    DetectEngineCtx *de_ctx = NULL;
    DetectEngineThreadCtx *det_ctx = (DetectEngineThreadCtx *)data;
    if (det_ctx == NULL) {
        printf("ERROR: Detect has no thread ctx\n");
        goto error;
    }

    if (unlikely(SC_ATOMIC_GET(det_ctx->so_far_used_by_detect) == 0)) {
        (void)SC_ATOMIC_SET(det_ctx->so_far_used_by_detect, 1);
        SCLogDebug("Detect Engine using new det_ctx - %p",
                  det_ctx);
    }

    /* if in MT mode _and_ we have tenants registered, use
     * MT logic. */
    if (det_ctx->mt_det_ctxs_cnt > 0 && det_ctx->TenantGetId != NULL)
    {
        uint32_t tenant_id = p->tenant_id;
        if (tenant_id == 0)
            tenant_id = det_ctx->TenantGetId(det_ctx, p);
        if (tenant_id > 0 && tenant_id < det_ctx->mt_det_ctxs_cnt) {
            p->tenant_id = tenant_id;
            det_ctx = GetTenantById(det_ctx->mt_det_ctxs_hash, tenant_id);
            if (det_ctx == NULL)
                return TM_ECODE_OK;
            de_ctx = det_ctx->de_ctx;
            if (de_ctx == NULL)
                return TM_ECODE_OK;

            if (unlikely(SC_ATOMIC_GET(det_ctx->so_far_used_by_detect) == 0)) {
                (void)SC_ATOMIC_SET(det_ctx->so_far_used_by_detect, 1);
                SCLogDebug("MT de_ctx %p det_ctx %p (tenant %u)", de_ctx, det_ctx, tenant_id);
            }
        } else {
            /* use default if no tenants are registered for this packet */
            de_ctx = det_ctx->de_ctx;
        }
    } else {
        de_ctx = det_ctx->de_ctx;
    }

    if (p->flow) {
        DetectFlow(tv, de_ctx, det_ctx, p);
    } else {
        DetectNoFlow(tv, de_ctx, det_ctx, p);
    }

#ifdef PROFILE_RULES
    /* aggregate statistics */
    struct timeval ts;
    gettimeofday(&ts, NULL);
    if (ts.tv_sec != det_ctx->rule_perf_last_sync) {
        SCProfilingRuleThreatAggregate(det_ctx);
        det_ctx->rule_perf_last_sync = ts.tv_sec;
    }
#endif

    return TM_ECODE_OK;
error:
    return TM_ECODE_FAILED;
}

static inline void FlowWorkerStreamTCPUpdate(ThreadVars *tv, FlowWorkerThreadData *fw, Packet *p,
        DetectEngineThreadCtx *det_ctx, const bool timeout)
{
    if (det_ctx != NULL && det_ctx->de_ctx->PreStreamHook != NULL) {
        const uint8_t action = det_ctx->de_ctx->PreStreamHook(tv, det_ctx, p);
        if (action & ACTION_DROP) {
            PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_STREAM_PRE_HOOK);
            return;
        }
    }

    FLOWWORKER_PROFILING_START(p, PROFILE_FLOWWORKER_STREAM);
    StreamTcp(tv, p, fw->stream_thread, &fw->pq);
    FLOWWORKER_PROFILING_END(p, PROFILE_FLOWWORKER_STREAM);

    // this is the first packet that sets no payload inspection
    bool setting_nopayload =
            p->flow->alparser &&
            SCAppLayerParserStateIssetFlag(p->flow->alparser, APP_LAYER_PARSER_NO_INSPECTION) &&
            !(p->flags & PKT_NOPAYLOAD_INSPECTION);
    if (FlowChangeProto(p->flow) || setting_nopayload) {
        StreamTcpDetectLogFlush(tv, fw->stream_thread, p->flow, p, &fw->pq);
        if (setting_nopayload) {
            FlowSetNoPayloadInspectionFlag(p->flow);
        }
        SCAppLayerParserStateSetFlag(p->flow->alparser, APP_LAYER_PARSER_EOF_TS);
        SCAppLayerParserStateSetFlag(p->flow->alparser, APP_LAYER_PARSER_EOF_TC);
    }

    /* Packets here can safely access p->flow as it's locked */
    SCLogDebug("packet %"PRIu64": extra packets %u", p->pcap_cnt, fw->pq.len);
    Packet *x;
    while ((x = PacketDequeueNoLock(&fw->pq))) {
        SCLogDebug("packet %"PRIu64" extra packet %p", p->pcap_cnt, x);

        if (det_ctx != NULL) {
            FLOWWORKER_PROFILING_START(x, PROFILE_FLOWWORKER_DETECT);
            Detect(tv, x, det_ctx);
            FLOWWORKER_PROFILING_END(x, PROFILE_FLOWWORKER_DETECT);
        }

        OutputLoggerLog(tv, x, fw->output_thread);

        FramesPrune(x->flow, x);
        /*  Release tcp segments. Done here after alerting can use them. */
        FLOWWORKER_PROFILING_START(x, PROFILE_FLOWWORKER_TCPPRUNE);
        StreamTcpPruneSession(
                x->flow, x->flowflags & FLOW_PKT_TOSERVER ? STREAM_TOSERVER : STREAM_TOCLIENT);
        FLOWWORKER_PROFILING_END(x, PROFILE_FLOWWORKER_TCPPRUNE);

        /* no need to keep a flow ref beyond this point */
        FlowDeReference(&x->flow);

        /* no further work to do for this pseudo packet, so we can return
         * it to the pool immediately. */
        if (timeout) {
            PacketPoolReturnPacket(x);
        } else {
            /* to support IPS verdict logic, in the non-timeout case we need to do a bit more */
            TmqhOutputPacketpool(tv, x);
        }
    }
    if (FlowChangeProto(p->flow) && p->flow->flags & FLOW_ACTION_DROP) {
        // in case f->flags & FLOW_ACTION_DROP was set by one of the dequeued packets
        PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_FLOW_DROP);
    }
}

static TmEcode FlowWorker(ThreadVars *tv, Packet *p, void *data)
{
    FlowWorkerThreadData *fw = data;
    DetectEngineThreadCtx *det_ctx = SC_ATOMIC_GET(fw->detect_thread);

    DEBUG_VALIDATE_BUG_ON(p == NULL);
    DEBUG_VALIDATE_BUG_ON(tv->flow_queue == NULL);

    SCLogDebug("packet %"PRIu64, p->pcap_cnt);

    if ((PKT_IS_FLUSHPKT(p))) {
        SCLogDebug("thread %s flushing", tv->printable_name);
        OutputLoggerFlush(tv, p, fw->output_thread);
        /* Ack if a flush was requested */
        bool notset = false;
        SC_ATOMIC_CAS(&fw->flush_ack, notset, true);
        return TM_ECODE_OK;
    }

    /* handle Flow */
    if (det_ctx != NULL && det_ctx->de_ctx->PreFlowHook != NULL) {
        const uint8_t action = det_ctx->de_ctx->PreFlowHook(tv, det_ctx, p);
        if (action & ACTION_DROP) {
            PacketDrop(p, ACTION_DROP, PKT_DROP_REASON_FLOW_PRE_HOOK);
            goto pre_flow_drop;
        }
    }

    if (p->flags & PKT_WANTS_FLOW) {
        FLOWWORKER_PROFILING_START(p, PROFILE_FLOWWORKER_FLOW);

        FlowHandlePacket(tv, &fw->fls, p);
        if (likely(p->flow != NULL)) {
            DEBUG_ASSERT_FLOW_LOCKED(p->flow);
            if (FlowUpdate(tv, fw, p) == TM_ECODE_DONE) {
                /* update time */
                if (!(PKT_IS_PSEUDOPKT(p))) {
                    TimeSetByThread(tv->id, p->ts);
                }
                goto housekeeping;
            }
        }
        /* Flow is now LOCKED */

        FLOWWORKER_PROFILING_END(p, PROFILE_FLOWWORKER_FLOW);

    /* if PKT_WANTS_FLOW is not set, but PKT_HAS_FLOW is, then this is a
     * pseudo packet created by the flow manager. */
    } else if (p->flags & PKT_HAS_FLOW) {
        FLOWLOCK_WRLOCK(p->flow);
        DEBUG_VALIDATE_BUG_ON(p->pkt_src != PKT_SRC_FFR);
    }

    /* update time */
    if (!(PKT_IS_PSEUDOPKT(p))) {
        TimeSetByThread(tv->id, p->ts);
    }

    SCLogDebug("packet %"PRIu64" has flow? %s", p->pcap_cnt, p->flow ? "yes" : "no");

    /* handle TCP and app layer */
    if (p->flow) {
        SCLogDebug("packet %" PRIu64
                   ": direction %s FLOW_TS_APP_UPDATE_NEXT %s FLOW_TC_APP_UPDATE_NEXT %s",
                p->pcap_cnt, PKT_IS_TOSERVER(p) ? "toserver" : "toclient",
                BOOL2STR((p->flow->flags & FLOW_TS_APP_UPDATE_NEXT) != 0),
                BOOL2STR((p->flow->flags & FLOW_TC_APP_UPDATE_NEXT) != 0));
        /* see if need to consider flags set by prev packets */
        if (PKT_IS_TOSERVER(p) && (p->flow->flags & FLOW_TS_APP_UPDATE_NEXT)) {
            p->flow->flags |= FLOW_TS_APP_UPDATED;
            p->flow->flags &= ~FLOW_TS_APP_UPDATE_NEXT;
            SCLogDebug("FLOW_TS_APP_UPDATED");
        } else if (PKT_IS_TOCLIENT(p) && (p->flow->flags & FLOW_TC_APP_UPDATE_NEXT)) {
            p->flow->flags |= FLOW_TC_APP_UPDATED;
            p->flow->flags &= ~FLOW_TC_APP_UPDATE_NEXT;
            SCLogDebug("FLOW_TC_APP_UPDATED");
        }

        if (PacketIsTCP(p)) {
            SCLogDebug("packet %" PRIu64 " is TCP. Direction %s", p->pcap_cnt,
                    PKT_IS_TOSERVER(p) ? "TOSERVER" : "TOCLIENT");
            DEBUG_ASSERT_FLOW_LOCKED(p->flow);

            /* if detect is disabled, we need to apply file flags to the flow
             * here on the first packet. */
            if (det_ctx == NULL &&
                    ((PKT_IS_TOSERVER(p) && (p->flowflags & FLOW_PKT_TOSERVER_FIRST)) ||
                            (PKT_IS_TOCLIENT(p) && (p->flowflags & FLOW_PKT_TOCLIENT_FIRST)))) {
                DisableDetectFlowFileFlags(p->flow);
            }

            FlowWorkerStreamTCPUpdate(tv, fw, p, det_ctx, false);
            PacketAppUpdate2FlowFlags(p);

            /* handle the app layer part of the UDP packet payload */
        } else if (p->proto == IPPROTO_UDP && !PacketCheckAction(p, ACTION_DROP)) {
            FLOWWORKER_PROFILING_START(p, PROFILE_FLOWWORKER_APPLAYERUDP);
            AppLayerHandleUdp(tv, fw->stream_thread->ra_ctx->app_tctx, p, p->flow);
            FLOWWORKER_PROFILING_END(p, PROFILE_FLOWWORKER_APPLAYERUDP);
            PacketAppUpdate2FlowFlags(p);
        }
    }

    PacketUpdateEngineEventCounters(tv, fw->dtv, p);

    /* handle Detect */
    DEBUG_ASSERT_FLOW_LOCKED(p->flow);
    SCLogDebug("packet %"PRIu64" calling Detect", p->pcap_cnt);
    if (det_ctx != NULL) {
        FLOWWORKER_PROFILING_START(p, PROFILE_FLOWWORKER_DETECT);
        Detect(tv, p, det_ctx);
        FLOWWORKER_PROFILING_END(p, PROFILE_FLOWWORKER_DETECT);
    }

pre_flow_drop:
    // Outputs.
    OutputLoggerLog(tv, p, fw->output_thread);

    /*  Release tcp segments. Done here after alerting can use them. */
    if (p->flow != NULL) {
        DEBUG_ASSERT_FLOW_LOCKED(p->flow);

        if (FlowIsBypassed(p->flow)) {
            FlowCleanupAppLayer(p->flow);
            if (p->proto == IPPROTO_TCP) {
                StreamTcpSessionCleanup(p->flow->protoctx);
            }
        } else if (p->proto == IPPROTO_TCP && p->flow->protoctx && p->flags & PKT_STREAM_EST) {
            if ((p->flow->flags & FLOW_TS_APP_UPDATED) && PKT_IS_TOSERVER(p)) {
                FramesPrune(p->flow, p);
            } else if ((p->flow->flags & FLOW_TC_APP_UPDATED) && PKT_IS_TOCLIENT(p)) {
                FramesPrune(p->flow, p);
            }
            FLOWWORKER_PROFILING_START(p, PROFILE_FLOWWORKER_TCPPRUNE);
            StreamTcpPruneSession(p->flow, p->flowflags & FLOW_PKT_TOSERVER ?
                    STREAM_TOSERVER : STREAM_TOCLIENT);
            FLOWWORKER_PROFILING_END(p, PROFILE_FLOWWORKER_TCPPRUNE);
        } else if (p->proto == IPPROTO_UDP) {
            FramesPrune(p->flow, p);
        }

        if ((PKT_IS_PSEUDOPKT(p)) ||
                (p->flow->flags & (FLOW_TS_APP_UPDATED | FLOW_TC_APP_UPDATED))) {
            if ((p->flags & PKT_STREAM_EST) || p->proto != IPPROTO_TCP) {
                if (PKT_IS_TOSERVER(p)) {
                    if (PKT_IS_PSEUDOPKT(p) || (p->flow->flags & (FLOW_TS_APP_UPDATED))) {
                        AppLayerParserTransactionsCleanup(p->flow, STREAM_TOSERVER);
                        p->flow->flags &= ~FLOW_TS_APP_UPDATED;
                        SCLogDebug("~FLOW_TS_APP_UPDATED");
                    }
                } else {
                    if (PKT_IS_PSEUDOPKT(p) || (p->flow->flags & (FLOW_TC_APP_UPDATED))) {
                        AppLayerParserTransactionsCleanup(p->flow, STREAM_TOCLIENT);
                        p->flow->flags &= ~FLOW_TC_APP_UPDATED;
                        SCLogDebug("~FLOW_TC_APP_UPDATED");
                    }
                }
            }
        } else {
            SCLogDebug("not pseudo, no app update: skip");
        }

        if (p->flow->flags & FLOW_ACTION_DROP) {
            SCLogDebug("flow drop in place: remove app update flags");
            p->flow->flags &= ~(FLOW_TS_APP_UPDATED | FLOW_TC_APP_UPDATED);
        }

        Flow *f = p->flow;
        FlowDeReference(&p->flow);
        FLOWLOCK_UNLOCK(f);
    }

housekeeping:

    /* take injected flows and add them to our local queue */
    FlowWorkerProcessInjectedFlows(tv, fw, p);

    /* process local work queue */
    FlowWorkerProcessLocalFlows(tv, fw, p);

    return TM_ECODE_OK;
}
