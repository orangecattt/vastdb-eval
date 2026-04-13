#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

// ============================================================================
// MACROS (from project)
// ============================================================================

// from: libtransmission/tr-macros.h:175
#define TR_BAD_SIZE ((size_t)-1)

// from: libtransmission/file.h:34
#define TR_BAD_SYS_FILE (-1)

// from: libtransmission/file.h:39
#define TR_NATIVE_EOL_STR "\n"

// from: libtransmission/log.h:23
#define TR_LOG_MAX_QUEUE_LENGTH 10000

// from: libtransmission/tr-macros.h:70
#define TR_LIKELY(x) (x)

// from: libtransmission/utils.h:38
#define _(a) (a)

// from: libtransmission/tr-assert.h:19
#define TR_ASSERT(x) ((void)(TR_LIKELY(x) || tr_assert_report(__FILE__, __LINE__, "%s", #x)))

// from: libtransmission/tr-macros.h:99
#define TR_GNUC_PRINTF(fmt, args)

// from: libtransmission/tr-macros.h:105
#define TR_GNUC_NONNULL(...)

// from: libtransmission/utils.h:173
#define tr_new(struct_type, n_structs) \
    ((struct_type*)tr_malloc(sizeof(struct_type) * (size_t)(n_structs)))

// from: libtransmission/utils.h:176
#define tr_new0(struct_type, n_structs) \
    ((struct_type*)tr_malloc0(sizeof(struct_type) * (size_t)(n_structs)))

// from: libtransmission/utils.h:179
#define tr_renew(struct_type, mem, n_structs) \
    ((struct_type*)tr_realloc((mem), sizeof(struct_type) * (size_t)(n_structs)))

// from: libtransmission/log.h:30
#define tr_logAddNamed(level, name, ...) \
    do \
    { \
        if (tr_logLevelIsActive(level)) \
        { \
            tr_logAddMessage(__FILE__, __LINE__, level, name, __VA_ARGS__); \
        } \
    } \
    while (0)

// from: libtransmission/log.h:53
#define tr_logAdd(level, ...) tr_logAddNamed(level, NULL, __VA_ARGS__)

// from: libtransmission/log.h:55
#define tr_logAddError(...) tr_logAdd(TR_LOG_ERROR, __VA_ARGS__)

// ============================================================================
// TYPE DEFINITIONS (must be complete)
// ============================================================================

// from: libtransmission/quark.h:18
typedef size_t tr_quark;

// from: libtransmission/variant.h:35
typedef enum
{
    TR_STRING_TYPE_QUARK,
    TR_STRING_TYPE_HEAP,
    TR_STRING_TYPE_BUF
}
tr_string_type;

// from: libtransmission/variant.h:62
enum
{
    TR_VARIANT_TYPE_INT = 1,
    TR_VARIANT_TYPE_STR = 2,
    TR_VARIANT_TYPE_LIST = 4,
    TR_VARIANT_TYPE_DICT = 8,
    TR_VARIANT_TYPE_BOOL = 16,
    TR_VARIANT_TYPE_REAL = 32
};

// from: libtransmission/variant.h:46
struct tr_variant_string
{
    tr_string_type type;
    tr_quark quark;
    size_t len;
    union
    {
        char buf[16];
        char const* str;
    }
    str;
};

// from: libtransmission/variant.h:75
typedef struct tr_variant
{
    char type;
    tr_quark key;
    union
    {
        bool b;
        double d;
        int64_t i;
        struct tr_variant_string s;
        struct
        {
            size_t alloc;
            size_t count;
            struct tr_variant* vals;
        } l;
    }
    val;
}
tr_variant;

// from: libtransmission/file.h:32
typedef int tr_sys_file_t;

// from: libtransmission/file.h:56
typedef enum
{
    TR_STD_SYS_FILE_IN,
    TR_STD_SYS_FILE_OUT,
    TR_STD_SYS_FILE_ERR
}
tr_std_sys_file_t;

// from: libtransmission/log.h
typedef enum {
  TR_LOG_ERROR = 1,
  TR_LOG_INFO = 2,
  TR_LOG_DEBUG = 3,
  TR_LOG_FIREHOSE = 4
} tr_log_level;

// from: libtransmission/transmission.h:733
typedef struct tr_log_message
{
    tr_log_level level;
    int line;
    time_t when;
    char* name;
    char* message;
    char const* file;
    struct tr_log_message* next;
}
tr_log_message;

// from: libtransmission/platform.h
#include <pthread.h>
typedef struct tr_lock
{
    pthread_mutex_t lock;
    int depth;
    pthread_t lockThread;
} tr_lock;

// Forward declaration for tr_error
struct tr_error;

// from: libtransmission/variant-common.h:15
typedef void (* VariantWalkFunc)(tr_variant const* val, void* user_data);

// from: libtransmission/variant-common.h:17
struct VariantWalkFuncs
{
    VariantWalkFunc intFunc;
    VariantWalkFunc boolFunc;
    VariantWalkFunc realFunc;
    VariantWalkFunc stringFunc;
    VariantWalkFunc dictBeginFunc;
    VariantWalkFunc listBeginFunc;
    VariantWalkFunc containerEndFunc;
};

// from: libtransmission/variant.c:744
struct KeyIndex
{
    char const* keystr;
    tr_variant* val;
};

// from: libtransmission/variant.c:758
struct SaveNode
{
    tr_variant const* v;
    tr_variant* sorted;
    size_t childIndex;
    bool isVisited;
};

// ============================================================================
// FUNCTION DECLARATIONS (not in snippet/context - declaration only)
// ============================================================================

// from: libtransmission/quark.h:425
char const* tr_quark_get_string(tr_quark quark, size_t* len);

// from: libtransmission/variant-common.h:34
void tr_variantInit(tr_variant* v, char type);

// from: libtransmission/variant-common.h
void tr_variantInitDict(tr_variant* initme, size_t reserve_count);

// from: libtransmission/variant.c
static void tr_variant_string_set_quark(struct tr_variant_string* str, tr_quark const quark);

// from: libtransmission/log.h:23
tr_log_level tr_logGetLevel(void);

// from: libtransmission/log.h
static tr_lock* getMessageLock(void);

// from: libtransmission/platform.h
void tr_lockLock(tr_lock* l);
void tr_lockUnlock(tr_lock* l);
tr_lock* tr_lockNew(void);

// from: libtransmission/log.h
void tr_logAddMessage(char const* file, int line, tr_log_level level, char const* name, char const* fmt, ...) \
    TR_GNUC_PRINTF(5, 6) TR_GNUC_NONNULL(1, 4);

// from: libtransmission/log.h
bool tr_logGetQueueEnabled(void);
void tr_logFreeQueue(tr_log_message* freeme);
tr_sys_file_t tr_logGetFile(void);

// from: libtransmission/file.h
tr_sys_file_t tr_sys_file_get_std(tr_std_sys_file_t std_file, struct tr_error** error);
bool tr_sys_file_write_fmt(tr_sys_file_t handle, char const* format, struct tr_error** error, ...) TR_GNUC_PRINTF(2, 4);
bool tr_sys_file_flush(tr_sys_file_t handle, struct tr_error** error);
void tr_logGetTimeStr(char* buf, size_t buflen) TR_GNUC_NONNULL(1);

// from: libtransmission/utils.h
time_t tr_time(void);
char* tr_strdup(void const* in);
void* tr_malloc(size_t size);
void* tr_malloc0(size_t size);
void* tr_realloc(void* p, size_t size);
void tr_free(void* p);

// from: libtransmission/tr-assert.h
bool tr_assert_report(char const* file, int line, char const* message_fmt, ...) TR_GNUC_PRINTF(3, 4);

// from: libevent/event2/util.h
int evutil_vsnprintf(char* dst, size_t size, char const* format, va_list args);

// ============================================================================
// INLINE HELPERS (from headers)
// ============================================================================

// from: libtransmission/utils.h
static inline bool tr_str_is_empty(char const* value)
{
    return value == NULL || *value == '\0';
}

// from: libtransmission/log.h
static inline bool tr_logLevelIsActive(tr_log_level level)
{
    return tr_logGetLevel() >= level;
}

// from: libtransmission/variant.h
static inline bool tr_variantIsDict(tr_variant const* v)
{
    return v != NULL && v->type == TR_VARIANT_TYPE_DICT;
}

// from: libtransmission/variant.h
static inline bool tr_variantIsList(tr_variant const* v)
{
    return v != NULL && v->type == TR_VARIANT_TYPE_LIST;
}

// from: libtransmission/utils.c:126
void* tr_malloc(size_t size)
{
    return size != 0 ? malloc(size) : NULL;
}

// from: libtransmission/utils.c:131
void* tr_malloc0(size_t size)
{
    return size != 0 ? calloc(1, size) : NULL;
}

// from: libtransmission/utils.c:136
void* tr_realloc(void* p, size_t size)
{
    void* result = size != 0 ? realloc(p, size) : NULL;
    if (result == NULL)
    {
        tr_free(p);
    }
    return result;
}

// from: libtransmission/utils.c:148
void tr_free(void* p)
{
    if (p != NULL)
    {
        free(p);
    }
}

// from: libtransmission/log.c:46
tr_log_level tr_logGetLevel(void)
{
    return TR_LOG_ERROR;
}

// from: libtransmission/platform.c:157
tr_lock* tr_lockNew(void)
{
    tr_lock* l = tr_new0(tr_lock, 1);
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&l->lock, &attr);
    return l;
}

// from: libtransmission/platform.c:188
void tr_lockLock(tr_lock* l)
{
    pthread_mutex_lock(&l->lock);
    l->lockThread = 0;
    ++l->depth;
}

// from: libtransmission/platform.c:208
void tr_lockUnlock(tr_lock* l)
{
    --l->depth;
    pthread_mutex_unlock(&l->lock);
}

// from: libtransmission/log.c:55
static tr_lock* getMessageLock(void)
{
    static tr_lock* l = NULL;
    if (l == NULL)
    {
        l = tr_lockNew();
    }
    return l;
}

// from: libtransmission/log.c:103
bool tr_logGetQueueEnabled(void)
{
    return false;
}

// from: libtransmission/log.c:122
void tr_logFreeQueue(tr_log_message* list)
{
    tr_log_message* next;
    while (list != NULL)
    {
        next = list->next;
        tr_free(list->message);
        tr_free(list->name);
        tr_free(list);
        list = next;
    }
}

// from: libtransmission/log.c:67
tr_sys_file_t tr_logGetFile(void)
{
    static bool initialized = false;
    static tr_sys_file_t file = TR_BAD_SYS_FILE;
    if (!initialized)
    {
        initialized = true;
    }
    return file;
}

// from: libtransmission/log.c:140
void tr_logGetTimeStr(char* buf, size_t buflen)
{
    if (buf && buflen > 0)
        buf[0] = '\0';
}

// from: libtransmission/file.c
tr_sys_file_t tr_sys_file_get_std(tr_std_sys_file_t std_file, struct tr_error** error)
{
    (void)error;
    switch (std_file)
    {
    case TR_STD_SYS_FILE_IN:
        return 0;
    case TR_STD_SYS_FILE_OUT:
        return 1;
    case TR_STD_SYS_FILE_ERR:
        return 2;
    }
    return TR_BAD_SYS_FILE;
}

// from: libtransmission/file.c
bool tr_sys_file_write_fmt(tr_sys_file_t handle, char const* format, struct tr_error** error, ...)
{
    (void)error;
    FILE* fp = NULL;
    switch (handle)
    {
    case 1:
        fp = stdout;
        break;
    case 2:
        fp = stderr;
        break;
    }
    if (fp == NULL)
        return false;
    va_list args;
    va_start(args, error);
    vfprintf(fp, format, args);
    va_end(args);
    return true;
}

// from: libtransmission/file.c
bool tr_sys_file_flush(tr_sys_file_t handle, struct tr_error** error)
{
    (void)error;
    FILE* fp = NULL;
    switch (handle)
    {
    case 1:
        fp = stdout;
        break;
    case 2:
        fp = stderr;
        break;
    }
    if (fp == NULL)
        return false;
    return fflush(fp) == 0;
}

// from: libtransmission/utils.c
time_t __tr_current_time = 0;
time_t tr_time(void)
{
    return __tr_current_time;
}

// from: libtransmission/utils.c
char* tr_strdup(void const* in)
{
    if (in == NULL)
        return NULL;
    size_t len = strlen((char const*)in) + 1;
    char* result = (char*)tr_malloc(len);
    if (result)
        memcpy(result, in, len);
    return result;
}

// from: libtransmission/tr-assert.h
bool tr_assert_report(char const* file, int line, char const* message_fmt, ...)
{
    (void)file;
    (void)line;
    (void)message_fmt;
    return false;
}

// from: libtransmission/quark.c:511
char const* tr_quark_get_string(tr_quark q, size_t* len)
{
    (void)q;
    if (len != NULL)
        *len = 0;
    return "";
}

// from: libtransmission/variant.c:123
void tr_variantInit(tr_variant* v, char type)
{
    v->type = type;
    memset(&v->val, 0, sizeof(v->val));
}

// from: libtransmission/variant.c:529
void tr_variantInitDict(tr_variant* v, size_t reserve_count)
{
    tr_variantInit(v, TR_VARIANT_TYPE_DICT);
    v->val.l.count = 0;
    v->val.l.alloc = reserve_count;
    if (reserve_count > 0)
        v->val.l.vals = (tr_variant*)tr_malloc(sizeof(tr_variant) * reserve_count);
    else
        v->val.l.vals = NULL;
}

// from: libtransmission/variant.c:177
static void tr_variant_string_set_quark(struct tr_variant_string* str, tr_quark const quark)
{
    str->type = TR_STRING_TYPE_QUARK;
    str->quark = quark;
    str->len = 0;
    str->str.str = tr_quark_get_string(quark, &str->len);
}

// from: libtransmission/variant.c:465
void tr_variantInitQuark(tr_variant* v, tr_quark const q)
{
    tr_variantInit(v, TR_VARIANT_TYPE_STR);
    tr_variant_string_set_quark(&v->val.s, q);
}

// from: libtransmission/log.c:213
void tr_logAddMessage(char const* file, int line, tr_log_level level, char const* name, char const* fmt, ...)
{
    int const err = errno;
    char buf[1024];
    int buf_len;
    va_list ap;
    tr_lockLock(getMessageLock());

    *buf = '\0';
    va_start(ap, fmt);
    buf_len = evutil_vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    if (buf_len >= 0 && !tr_str_is_empty(buf))
    {
        if (tr_logGetQueueEnabled())
        {
            tr_log_message* newmsg = tr_new0(tr_log_message, 1);
            newmsg->level = level;
            newmsg->when = tr_time();
            newmsg->message = tr_strdup(buf);
            newmsg->file = file;
            newmsg->line = line;
            newmsg->name = tr_strdup(name);
            tr_logFreeQueue(newmsg);
        }
        else
        {
            tr_sys_file_t fp = tr_logGetFile();
            if (fp == TR_BAD_SYS_FILE)
            {
                fp = tr_sys_file_get_std(TR_STD_SYS_FILE_ERR, NULL);
            }
            char timestr[64];
            tr_logGetTimeStr(timestr, sizeof(timestr));
            if (name != NULL)
            {
                tr_sys_file_write_fmt(fp, "[%s] %s: %s" TR_NATIVE_EOL_STR, NULL, timestr, name, buf);
            }
            else
            {
                tr_sys_file_write_fmt(fp, "[%s] %s" TR_NATIVE_EOL_STR, NULL, timestr, buf);
            }
            tr_sys_file_flush(fp, NULL);
        }
    }

    tr_lockUnlock(getMessageLock());
    errno = err;
}

// from: libtransmission/variant.c:750
static int compareKeyIndex(void const* va, void const* vb)
{
    struct KeyIndex const* a = (struct KeyIndex const*)va;
    struct KeyIndex const* b = (struct KeyIndex const*)vb;
    return strcmp(a->keystr, b->keystr);
}

// from: libtransmission/variant.c:766
static void nodeConstruct(struct SaveNode* node, tr_variant const* v, bool sort_dicts)
{
    node->isVisited = false;
    node->childIndex = 0;

    if (sort_dicts && tr_variantIsDict(v))
    {
        size_t const n = v->val.l.count;
        struct KeyIndex* tmp = tr_new(struct KeyIndex, n);

        for (size_t i = 0; i < n; i++)
        {
            tmp[i].val = v->val.l.vals + i;
            tmp[i].keystr = tr_quark_get_string(tmp[i].val->key, NULL);
        }

        qsort(tmp, n, sizeof(struct KeyIndex), compareKeyIndex);

        node->sorted = tr_new(tr_variant, 1);
        tr_variantInitDict(node->sorted, n);

        for (size_t i = 0; i < n; ++i)
        {
            node->sorted->val.l.vals[i] = *tmp[i].val;
        }

        node->sorted->val.l.count = n;
        tr_free(tmp);
        v = node->sorted;
    }
    else
    {
        node->sorted = NULL;
    }
    node->v = v;
}

// from: libtransmission/variant.c:805
static void nodeDestruct(struct SaveNode* node)
{
    TR_ASSERT(node != NULL);

    if (node->sorted != NULL)
    {
        tr_free(node->sorted->val.l.vals);
        tr_free(node->sorted);
    }
}

// from: libtransmission/variant.c
static bool tr_variantIsContainer(tr_variant const* v)
{
    return tr_variantIsList(v) || tr_variantIsDict(v);
}

// from: libtransmission/variant.c:818
void tr_variantWalk(tr_variant const* v, struct VariantWalkFuncs const* walkFuncs, void* user_data, bool sort_dicts)
{
    int stackSize = 0;
    int stackAlloc = 64;
    struct SaveNode* stack = tr_new(struct SaveNode, stackAlloc);

    nodeConstruct(&stack[stackSize++], v, sort_dicts);

    while (stackSize > 0)
    {
        struct SaveNode* node = &stack[stackSize - 1];
        tr_variant const* v;

        if (!node->isVisited)
        {
            v = node->v;
            node->isVisited = true;
        }
        else if (tr_variantIsContainer(node->v) && node->childIndex < node->v->val.l.count)
        {
            int const index = node->childIndex;
            ++node->childIndex;

            v = node->v->val.l.vals + index;

            if (tr_variantIsDict(node->v))
            {
                tr_variant tmp;
                tr_variantInitQuark(&tmp, v->key);
                walkFuncs->stringFunc(&tmp, user_data);
            }
        }
        else /* done with this node */
        {
            if (tr_variantIsContainer(node->v))
            {
                walkFuncs->containerEndFunc(node->v, user_data);
            }

            --stackSize;
            nodeDestruct(node);
            continue;
        }

        if (v != NULL)
        {
            switch (v->type)
            {
            case TR_VARIANT_TYPE_INT:
                walkFuncs->intFunc(v, user_data);
                break;

            case TR_VARIANT_TYPE_BOOL:
                walkFuncs->boolFunc(v, user_data);
                break;

            case TR_VARIANT_TYPE_REAL:
                walkFuncs->realFunc(v, user_data);
                break;

            case TR_VARIANT_TYPE_STR:
                walkFuncs->stringFunc(v, user_data);
                break;

            case TR_VARIANT_TYPE_LIST:
                if (v == node->v)
                {
                    walkFuncs->listBeginFunc(v, user_data);
                }
                else
                {
                    if (stackAlloc == stackSize)
                    {
                        stackAlloc *= 2;
                        stack = tr_renew(struct SaveNode, stack, stackAlloc);
                    }

                    nodeConstruct(&stack[stackSize++], v, sort_dicts);
                }

                break;

            case TR_VARIANT_TYPE_DICT:
                if (v == node->v)
                {
                    walkFuncs->dictBeginFunc(v, user_data);
                }
                else
                {
                    if (stackAlloc == stackSize)
                    {
                        stackAlloc *= 2;
                        stack = tr_renew(struct SaveNode, stack, stackAlloc);
                    }

                    nodeConstruct(&stack[stackSize++], v, sort_dicts);
                }

                break;

            default:
                /* did caller give us an uninitialized val? */
                tr_logAddError("%s", _("Invalid metadata"));
                break;
            }
        }
    }

    tr_free(stack);
}
