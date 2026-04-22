#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>

#ifndef likely
#define likely(expr) __builtin_expect(!!(expr), 1)
#endif
#ifndef unlikely
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#endif

#define WARN_UNUSED __attribute__((warn_unused_result))

void *SCMallocFunc(const size_t sz);
#define SCMalloc(sz) SCMallocFunc((sz))
void *SCCallocFunc(const size_t nm, const size_t sz);
#define SCCalloc(nm, sz) SCCallocFunc((nm), (sz))
char *SCStrdupFunc(const char *s);
#define SCStrdup(s) SCStrdupFunc((s))

#define SCFree(p) free((p))

#define SCMutex pthread_mutex_t
#define SCMutexLock(mut) pthread_mutex_lock(mut)
#define SCMutexUnlock(mut) pthread_mutex_unlock(mut)
#define SCMUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define SCLogDebug(...)                 do { } while (0)
#define SCReturnInt(x)                  return x

enum VarTypes {
    VAR_TYPE_NOT_SET,
    VAR_TYPE_PKT_BIT,
    VAR_TYPE_PKT_INT,
    VAR_TYPE_PKT_VAR,
    VAR_TYPE_PKT_VAR_KV,
    VAR_TYPE_FLOW_BIT,
    VAR_TYPE_FLOW_INT,
    VAR_TYPE_FLOW_FLOAT,
    VAR_TYPE_FLOW_VAR,
    VAR_TYPE_HOST_BIT,
    VAR_TYPE_HOST_INT,
    VAR_TYPE_HOST_VAR,
    VAR_TYPE_IPPAIR_BIT,
    VAR_TYPE_IPPAIR_INT,
    VAR_TYPE_IPPAIR_VAR,
    VAR_TYPE_TX_BIT,
    VAR_TYPE_ALERT_VAR,
};

typedef struct {
    uint64_t secs : 44;
    uint64_t usecs : 20;
} SCTime_t;

typedef struct HashListTableBucket_ {
    void *data;
    uint16_t size;
    struct HashListTableBucket_ *bucknext;
    struct HashListTableBucket_ *listnext;
    struct HashListTableBucket_ *listprev;
} HashListTableBucket;

typedef struct HashListTable_ {
    HashListTableBucket **array;
    HashListTableBucket *listhead;
    HashListTableBucket *listtail;
    uint32_t array_size;
    uint32_t (*Hash)(struct HashListTable_ *, void *, uint16_t);
    char (*Compare)(void *, uint16_t, void *, uint16_t);
    void (*Free)(void *);
} HashListTable;

int HashListTableAdd(HashListTable *, void *, uint16_t);
void *HashListTableLookup(HashListTable *, void *, uint16_t);

typedef struct DetectEngineCtx_ DetectEngineCtx;
typedef struct Signature_ Signature;
typedef struct SigMatchCtx_ SigMatchCtx;
typedef struct SigMatch_ SigMatch;
typedef struct Flow_ Flow;
typedef struct ThreadVars_ ThreadVars;
typedef struct Packet_ Packet;
typedef struct DetectEngineThreadCtx_ DetectEngineThreadCtx;

struct SigMatchCtx_ {
    int foo;
};

struct SigMatch_ {
    uint16_t type;
    uint16_t idx;
    SigMatchCtx *ctx;
    struct SigMatch_ *next;
    struct SigMatch_ *prev;
};

typedef struct TransformData_ {
    int transform;
    void *options;
} TransformData;

typedef struct DetectEngineTransforms {
    TransformData transforms[16];
    int cnt;
} DetectEngineTransforms;

typedef struct DetectBufferType_ {
    char name[64];
    char description[128];
    int id;
    int parent_id;
    bool mpm;
    bool packet;
    bool frame;
    bool supports_transforms;
    bool multi_instance;
    void (*SetupCallback)(const struct DetectEngineCtx_ *, struct Signature_ *);
    bool (*ValidateCallback)(
            const struct Signature_ *, const char **sigerror, const struct DetectBufferType_ *);
    DetectEngineTransforms transforms;
} DetectBufferType;

typedef struct SignatureInitData_ {
    int list;
} SignatureInitData;

struct Signature_ {
    SignatureInitData *init_data;
};

const DetectBufferType *DetectEngineBufferTypeGetById(const DetectEngineCtx *de_ctx, const int id);

SigMatch *SCSigMatchAppendSMToList(DetectEngineCtx *, Signature *, uint16_t, SigMatchCtx *, int);

int DetectBufferGetActiveList(DetectEngineCtx *de_ctx, Signature *s);

uint32_t VarNameStoreRegister(const char *name, const enum VarTypes type);

typedef struct VariableName_ {
    char *name;
    enum VarTypes type;
    uint32_t id;
    uint32_t ref_cnt;
} VariableName;

typedef struct VarNameStore_ {
    HashListTable *names;
    HashListTable *ids;
    uint32_t max_id;
    SCTime_t free_after;
} VarNameStore;

static SCMutex base_lock = SCMUTEX_INITIALIZER;
static VarNameStore base = { .names = NULL, .ids = NULL, .max_id = 0 };

enum DetectKeywordId {
    DETECT_SID = 0,
    DETECT_PRIORITY,
    DETECT_REV,
    DETECT_CLASSTYPE,
    DETECT_APP_LAYER_PROTOCOL,
    DETECT_ACK,
    DETECT_SEQ,
    DETECT_WINDOW,
    DETECT_IPOPTS,
    DETECT_IPADDR_SRC,
    DETECT_IPADDR_DST,
    DETECT_FLAGS,
    DETECT_FRAGBITS,
    DETECT_FRAGOFFSET,
    DETECT_TTL,
    DETECT_TOS,
    DETECT_ITYPE,
    DETECT_ICODE,
    DETECT_ICMP_ID,
    DETECT_ICMP_SEQ,
    DETECT_ICMPV4HDR,
    DETECT_DSIZE,
    DETECT_FLOW,
    DETECT_THRESHOLD,
    DETECT_FLOWBITS,
    DETECT_FLOWVAR,
    DETECT_FLOWVAR_POSTMATCH,
    DETECT_FLOWINT,
    DETECT_HOSTBITS,
    DETECT_XBITS,
    DETECT_PKTVAR,
    DETECT_CONTENT,
    DETECT_URICONTENT,
    DETECT_PCRE,
    DETECT_DEPTH,
    DETECT_STARTS_WITH,
    DETECT_ENDS_WITH,
    DETECT_DISTANCE,
    DETECT_WITHIN,
    DETECT_OFFSET,
    DETECT_REPLACE,
    DETECT_NOCASE,
    DETECT_FAST_PATTERN,
    DETECT_RAWBYTES,
    DETECT_BYTETEST,
    DETECT_BYTEJUMP,
    DETECT_BYTEMATH,
    DETECT_BYTE_EXTRACT,
    DETECT_DATASET,
    DETECT_DATAREP,
    DETECT_BASE64_DECODE,
    DETECT_BASE64_DATA,
    DETECT_BSIZE,
    DETECT_ASN1,
    DETECT_LUA,
    DETECT_ISDATAAT,
    DETECT_URILEN,
    DETECT_ABSENT,
    DETECT_ENTROPY,
};

enum DetectSigmatchListEnum {
    DETECT_SM_LIST_MATCH = 0,
    DETECT_SM_LIST_PMATCH,
    DETECT_SM_LIST_BASE64_DATA,
    DETECT_SM_LIST_POSTMATCH,
    DETECT_SM_LIST_TMATCH,
    DETECT_SM_LIST_SUPPRESS,
    DETECT_SM_LIST_THRESHOLD,
    DETECT_SM_LIST_MAX,
    DETECT_SM_LIST_DYNAMIC_START = DETECT_SM_LIST_MAX,
};

#define DETECT_SM_LIST_NOTSET INT_MAX
#define DEBUG_VALIDATE_BUG_ON(exp)

typedef struct DetectFloatData {
    double arg1;
    double arg2;
    int mode;
} DetectFloatData;

typedef struct DetectEntropyData {
    int32_t offset;
    int32_t nbytes;
    int32_t fv_idx;
    DetectFloatData value;
} DetectEntropyData;

DetectEntropyData *SCDetectEntropyParse(const char *arg);
void SCDetectEntropyFree(void *ptr);
bool SCDetectEntropyMatch(const void *c_data, int length, const DetectEntropyData *ctx, double *entropy);

const char *DetectEngineBufferTypeGetNameById(const DetectEngineCtx *de_ctx, const int id)
{
    const DetectBufferType *res = DetectEngineBufferTypeGetById(de_ctx, id);
    return res ? res->name : NULL;
}

uint32_t VarNameStoreRegister(const char *name, const enum VarTypes type)
{
    SCMutexLock(&base_lock);
    uint32_t id = 0;

    SCLogDebug("registering: name %s type %u", name, type);
    VariableName lookup = { .type = type, .name = (char *)name };
    VariableName *found = (VariableName *)HashListTableLookup(base.names, (void *)&lookup, 0);
    if (found == NULL) {
        VariableName *vn = SCCalloc(1, sizeof(VariableName));
        if (likely(vn != NULL)) {
            vn->type = type;
            vn->name = SCStrdup(name);
            if (vn->name != NULL) {
                vn->ref_cnt = 1;
                id = vn->id = ++base.max_id;
                HashListTableAdd(base.names, (void *)vn, 0);
                HashListTableAdd(base.ids, (void *)vn, 0);
                SCLogDebug(
                        "new registration %s id %u type %u -> %u", vn->name, vn->id, vn->type, id);
            } else {
                SCFree(vn);
            }
        }
    } else {
        id = found->id;
        found->ref_cnt++;
        SCLogDebug("existing registration %s ref_cnt %u -> %u", name, found->ref_cnt, id);
    }
    SCMutexUnlock(&base_lock);
    return id;
}

static int DetectEntropySetup(DetectEngineCtx *de_ctx, Signature *s, const char *arg)
{
    DetectEntropyData *ded = SCDetectEntropyParse(arg);
    if (ded == NULL) {
        goto error;
    }

    int sm_list = DETECT_SM_LIST_PMATCH;
    if (s->init_data->list != DETECT_SM_LIST_NOTSET) {
        /* sticky buffer */
        if (DetectBufferGetActiveList(de_ctx, s) == -1)
            goto error;

        sm_list = s->init_data->list;
        const char *name;
        if (sm_list == DETECT_SM_LIST_BASE64_DATA) {
            name = "base64_data";
        } else {
            name = DetectEngineBufferTypeGetNameById(de_ctx, sm_list);
            if (name == NULL) {
                DEBUG_VALIDATE_BUG_ON(1);
                name = "unknown";
            }
        }
        ded->fv_idx = VarNameStoreRegister(name, VAR_TYPE_FLOW_FLOAT);
    } else {
        ded->fv_idx = VarNameStoreRegister("content", VAR_TYPE_FLOW_FLOAT);
    }

    if (SCSigMatchAppendSMToList(de_ctx, s, DETECT_ENTROPY, (SigMatchCtx *)ded, sm_list) != NULL) {
        SCReturnInt(0);
    }

    /* fall through */

error:
    SCLogDebug("error during entropy setup");
    if (ded != NULL) {
        SCDetectEntropyFree(ded);
    }
    SCReturnInt(-1);
}
