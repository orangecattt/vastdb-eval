#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <arpa/inet.h>

#define TRUE            1
#define FALSE           0

#define OS_SIZE_65536   65536
#define OS_SIZE_6144    6144
#define OS_SIZE_2048    2048
#define OS_SIZE_128     128
#define OS_SIZE_256     256

#define OS_MAXSTR       OS_SIZE_65536
#define OS_BUFFER_SIZE  OS_SIZE_2048

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__
#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif
#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type)   type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllimport) type CJSON_STDCALL
#endif
#else
#define CJSON_CDECL
#define CJSON_STDCALL
#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 12

#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

#ifndef CJSON_NESTING_LIMIT
#define CJSON_NESTING_LIMIT 1000
#endif

typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;
    int type;
    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;
} cJSON;

typedef struct cJSON_Hooks
{
      void *(CJSON_CDECL *malloc_fn)(size_t sz);
      void (CJSON_CDECL *free_fn)(void *ptr);
} cJSON_Hooks;

typedef int cJSON_bool;

CJSON_PUBLIC(const char*) cJSON_Version(void);
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item);
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item);
CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
CJSON_PUBLIC(void) cJSON_Delete(cJSON *c);
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);
CJSON_PUBLIC(char *) cJSON_GetStringValue(cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char **strings, int count);
CJSON_PUBLIC(void) cJSON_AddItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(void) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
CJSON_PUBLIC(void) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
CJSON_PUBLIC(void) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(void) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(void) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(void) cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(void) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);
CJSON_PUBLIC(void) cJSON_Minify(char *json);
CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name);

#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number);
#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

CJSON_PUBLIC(void *) cJSON_malloc(size_t size);
CJSON_PUBLIC(void) cJSON_free(void *object);

static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == NULL) || (string2 == NULL))
    {
        return 1;
    }

    if (string1 == string2)
    {
        return 0;
    }

    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }

    return tolower(*string1) - tolower(*string2);
}

#ifndef __GNUC__
#define __attribute__(x)
#endif

#ifndef LOGFILE
#ifndef WIN32
#define LOGFILE   "logs/ossec.log"
#define LOGJSONFILE "logs/ossec.json"
#define _PRINTF_FORMAT printf
#else
#define LOGFILE "ossec.log"
#define LOGJSONFILE "ossec.json"
#define _PRINTF_FORMAT __MINGW_PRINTF_FORMAT
#endif
#endif

#define mdebug1(msg, ...) _mdebug1(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define mdebug2(msg, ...) _mdebug2(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)

void _mdebug1(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _mdebug2(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _merror(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _merror_exit(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull)) __attribute__ ((noreturn));

#define MEM_ERROR "Out of memory: '%s' (%d): %s"

#define os_calloc(x,y,z) ((z = (__typeof__(z)) calloc(x,y)))?(void)1:_merror_exit(__FILE__, __LINE__, __func__, MEM_ERROR, errno, strerror(errno))

typedef struct _Eventinfo Eventinfo;
typedef struct _RuleInfo RuleInfo;

typedef struct _OSListNode {
    struct _OSListNode *next;
    struct _OSListNode *prev;
    void *data;
} OSListNode;

typedef struct _OSList {
    OSListNode *first_node;
    OSListNode *last_node;
    OSListNode *cur_node;
    int currently_size;
    int max_size;
    volatile int count;
    volatile int pending_remove;
    void (*free_data_function)(void *data);
    pthread_rwlock_t wr_mutex;
    pthread_mutex_t mutex;
} OSList;

typedef struct label_flags_t {
    unsigned int hidden:1;
    unsigned int system:1;
} label_flags_t;

typedef struct wlabel_t {
    char *key;
    char *value;
    label_flags_t flags;
} wlabel_t;

typedef struct {
    int sub_strings_size;
    int *prts_str_size;
    int prts_str_alloc_size;
} regex_dynamic_size;

typedef struct regex_matching {
    char **sub_strings;
    const char ***prts_str;
    regex_dynamic_size d_size;
} regex_matching;

typedef struct _OSStoreNode {
    struct _OSStoreNode *next;
    char *key;
    void *data;
} OSStoreNode;

typedef struct _OSStore {
    OSStoreNode *first_node;
    OSStoreNode *last_node;
    OSStoreNode *cur_node;
    int currently_size;
} OSStore;

typedef struct _OSHashNode {
    struct _OSHashNode *next;
    char *key;
    void *data;
} OSHashNode;

typedef struct _OSHash {
    unsigned int rows;
    OSHashNode **table;
} OSHash;

#define AFTER_PARENT    0x001
#define AFTER_PREMATCH  0x002
#define AFTER_PREVREGEX 0x004
#define AFTER_ERROR     0x010
#define AFTER_ERR_VAL   (AFTER_ERROR << 1)
#define AFTER_ERR_NAME  (AFTER_ERROR << 2)

#define JSON_TREAT_NULL_AS_DISCARD     (0x1 << 0)
#define JSON_TREAT_NULL_AS_STRING      (0x1 << 1)
#define JSON_TREAT_ARRAY_AS_CSV_STRING (0x1 << 2)
#define JSON_TREAT_ARRAY_AS_ARRAY      (0x1 << 3)
#define JSON_TREAT_NULL_MASK           (JSON_TREAT_NULL_AS_DISCARD | JSON_TREAT_NULL_AS_STRING)
#define JSON_TREAT_ARRAY_MASK          (JSON_TREAT_ARRAY_AS_CSV_STRING | JSON_TREAT_ARRAY_AS_ARRAY)
#define JSON_TREAT_ARRAY_DEFAULT       JSON_TREAT_ARRAY_AS_ARRAY
#define JSON_TREAT_NULL_DEFAULT        JSON_TREAT_NULL_AS_STRING

typedef struct {
    u_int8_t  get_next;
    u_int8_t  type;
    u_int8_t  use_own_name;
    u_int8_t  flags;
    u_int16_t id;
    u_int16_t regex_offset;
    u_int16_t prematch_offset;
    u_int16_t plugin_offset;
    int fts;
    int accumulate;
    char *parent;
    char *name;
    char *ftscomment;
    char **fields;
    char *fts_fields;
    void *regex;
    void *prematch;
    void *program_name;
    void (*plugindecoder)(void *lf, void *rule_hash, void *decoder_match);
    void* (**order)(Eventinfo *, char *, const char *);
    bool internal_saving;
} OSDecoderInfo;

typedef struct _OSDecoderNode {
    struct _OSDecoderNode *next;
    struct _OSDecoderNode *child;
    OSDecoderInfo *osdecoder;
} OSDecoderNode;

#define CISCAT_MOD          "ciscat"

struct _RuleInfo {
    int rule_id;
    int level;
    int maxsize;
    int frequency;
    int timeframe;
    int ignore_time;
    u_int32_t context;
    int s_level;
    int category;
    char *group;
    char *comment;
    char *info_details;
    char *cve;
    char *info;
    OSList *last_events;
    time_t time_ignored;
    int count;
    int frequency_count;
    struct timespec fire_time;
    int firedtimes;
    void *event_search;
    void *regex;
    void *match;
    void *decoder;
    int prev_matched;
    int matched_event_ids;
    void *rule_prev_matched;
    int rule_group;
    OSList *group_list;
    int ar_level;
    void *ar;
    void *compiled_rule;
    int if_matched_sid;
    int if_matched_group;
    int if_matched_id;
};

typedef enum syscheck_event_t { FIM_ADDED, FIM_MODIFIED, FIM_READDED, FIM_DELETED } syscheck_event_t;
typedef struct _EventNode EventNode;

typedef struct _DynamicField {
    char *key;
    char *value;
} DynamicField;

struct _Eventinfo {
    char *log;
    char *full_log;
    const char * log_after_parent;
    const char * log_after_prematch;
    char *agent_id;
    char *location;
    char *hostname;
    char *program_name;
    char *comment;
    char *dec_timestamp;
    char *srcip;
    char *srcgeoip;
    char *dstip;
    char *dstgeoip;
    char *srcport;
    char *dstport;
    char *protocol;
    char *action;
    char *srcuser;
    char *dstuser;
    char *id;
    char *status;
    char *url;
    char *data;
    char *extra_data;
    char *systemname;
    DynamicField *fields;
    int nfields;
    RuleInfo *generated_rule;
    OSDecoderInfo *decoder_info;
    OSListNode *sid_node_to_delete;
    OSListNode **group_node_to_delete;
    size_t size;
    size_t p_name_size;
    int matched;
    time_t generate_time;
    struct timespec time;
    int day;
    int year;
    char hour[10];
    char mon[4];
    char *previous;
    wlabel_t *labels;
    u_int16_t decoder_syscheck_id;
    int rootcheck_fts;
    int is_a_copy;
    char **last_events;
    int r_firedtimes;
    int queue_added;
    EventNode *node;
    int tid;
    void *prev_rule;
};

struct _EventNode {
    Eventinfo *event;
    pthread_mutex_t mutex;
    volatile int count;
    EventNode *next;
    EventNode *prev;
};

#define UNKNOWN         0
#define SYSLOG          1
#define IDS             2
#define FIREWALL        3
#define WEBLOG          7
#define SQUID           8
#define DECODER_WINDOWS 9
#define HOST_INFO       10
#define OSSEC_RL        11
#define OSSEC_ALERT     12

void *JSON_Decoder_Init(void);
void *JSON_Decoder_Exec(Eventinfo *lf, regex_matching *decoder_match);
void fillData(Eventinfo *lf, const char *key, const char *value);
int wm_strcat(char **str1, const char *str2, char sep);

typedef enum wdbc_result {
        WDBC_OK,
        WDBC_DUE,
        WDBC_ERROR,
        WDBC_IGNORE,
        WDBC_UNKNOWN
} wdbc_result;

extern const char* WDBC_RESULT[];

int wdbc_connect(void);
int wdbc_connect_with_attempts(int max_attempts);
int wdbc_query(const int sock, const char *query, char *response, const int len);
int wdbc_query_ex(int *sock, const char *query, char *response, const int len);
int wdbc_parse_result(char *result, char **payload);
cJSON * wdbc_query_parse_json(int *sock, const char *query, char *response, const int len);
wdbc_result wdbc_query_parse(int *sock, const char *query, char *response, const int len, char** payload);
int wdbc_close(int* sock);

#define VAR_LENGTH  32

static OSDecoderInfo *ciscat_decoder = NULL;

static cJSON *get_object_item(const cJSON * const object, const char * const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element = NULL;

    if ((object == NULL) || (name == NULL))
    {
        return NULL;
    }

    current_element = object->child;
    if (case_sensitive)
    {
        while ((current_element != NULL) && (current_element->string != NULL) && (strcmp(name, current_element->string) != 0))
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while ((current_element != NULL) && (case_insensitive_strcmp((const unsigned char*)name, (const unsigned char*)(current_element->string)) != 0))
        {
            current_element = current_element->next;
        }
    }

    if ((current_element == NULL) || (current_element->string == NULL)) {
        return NULL;
    }

    return current_element;
}

CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, false);
}

int DecodeCiscat(Eventinfo *lf, int *socket)
{
    cJSON *logJSON;
    char *msg_type = NULL;

    // Decode JSON
    JSON_Decoder_Exec(lf, NULL);

    lf->decoder_info = ciscat_decoder;

    // Check location
    if (lf->location[0] == '(') {
        char* search;
        search = strchr(lf->location, '>');
        if (!search) {
            mdebug1("Invalid received event.");
            return (0);
        }
        else if (strcmp(search + 1, "wodle_cis-cat") != 0) {
            mdebug1("Invalid received event. Not CIS-CAT.");
            return (0);
        }
    } else if (strcmp(lf->location, "wodle_cis-cat") != 0) {
        mdebug1("Invalid received event. (Location)");
        return (0);
    }

    // Parsing event.
    const char *jsonErrPtr;
    logJSON = cJSON_ParseWithOpts(lf->log, &jsonErrPtr, 0);
    if (!logJSON) {
        mdebug1("Error parsing JSON event.");
        mdebug2("Input JSON: '%s", lf->log);
        return (0);
    }

    // Detect message type
    msg_type = cJSON_GetStringValue(cJSON_GetObjectItem(logJSON, "type"));
    if (!msg_type) {
        mdebug1("Invalid message. Type not found or not a string.");
        cJSON_Delete(logJSON);
        return (0);
    }

    if (strcmp(msg_type, "scan_info") == 0) {
        char *msg = NULL;
        cJSON * cis_data;

        os_calloc(OS_MAXSTR, sizeof(char), msg);

        if (cis_data = cJSON_GetObjectItem(logJSON, "cis"), cis_data) {
            cJSON * scan_id = cJSON_GetObjectItem(logJSON, "scan_id");
            cJSON * scan_time = cJSON_GetObjectItem(cis_data, "timestamp");
            cJSON * benchmark = cJSON_GetObjectItem(cis_data, "benchmark");
            cJSON * profile = cJSON_GetObjectItem(cis_data, "profile");
            cJSON * pass = cJSON_GetObjectItem(cis_data, "pass");
            cJSON * fail = cJSON_GetObjectItem(cis_data, "fail");
            cJSON * error = cJSON_GetObjectItem(cis_data, "error");
            cJSON * notchecked = cJSON_GetObjectItem(cis_data, "notchecked");
            cJSON * unknown = cJSON_GetObjectItem(cis_data, "unknown");
            cJSON * score = cJSON_GetObjectItem(cis_data, "score");

            snprintf(msg, OS_MAXSTR - 1, "agent %s ciscat save", lf->agent_id);

            if (scan_id) {
                char id[OS_MAXSTR];
                snprintf(id, OS_MAXSTR - 1, "%d", scan_id->valueint);
                wm_strcat(&msg, id, ' ');
            } else {
                wm_strcat(&msg, "NULL", ' ');
            }

            if (scan_time && cJSON_IsString(scan_time)) {
                wm_strcat(&msg, scan_time->valuestring, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (benchmark && cJSON_IsString(benchmark)) {
                wm_strcat(&msg, benchmark->valuestring, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (profile && cJSON_IsString(profile)) {
                wm_strcat(&msg, profile->valuestring, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (pass) {
                char _pass[VAR_LENGTH];
                snprintf(_pass, VAR_LENGTH - 1, "%d", pass->valueint);
                wm_strcat(&msg, _pass, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (fail) {
                char _fail[VAR_LENGTH];
                snprintf(_fail, VAR_LENGTH - 1, "%d", fail->valueint);
                wm_strcat(&msg, _fail, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (error) {
                char _error[VAR_LENGTH];
                snprintf(_error, VAR_LENGTH - 1, "%d", error->valueint);
                wm_strcat(&msg, _error, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (notchecked) {
                char _notchecked[VAR_LENGTH];
                snprintf(_notchecked, VAR_LENGTH - 1, "%d", notchecked->valueint);
                wm_strcat(&msg, _notchecked, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (unknown) {
                char _unknown[VAR_LENGTH];
                snprintf(_unknown, VAR_LENGTH - 1, "%d", unknown->valueint);
                wm_strcat(&msg, _unknown, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            if (score && cJSON_IsString(score)) {
                char *endptr;
                char _score[VAR_LENGTH];
                int score_i = strtoul(score->valuestring, &endptr, 10);
                snprintf(_score, VAR_LENGTH - 1, "%d", score_i);
                wm_strcat(&msg, _score, '|');
            } else {
                wm_strcat(&msg, "NULL", '|');
            }

            char *response;
            char *message;
            os_calloc(OS_SIZE_6144, sizeof(char), response);
            if (wdbc_query_ex(socket, msg, response, OS_SIZE_6144) == 0) {
                if (wdbc_parse_result(response, &message) != WDBC_OK) {
                    cJSON_Delete(logJSON);
                    free(response);
                    return (0);
                }
            } else {
                cJSON_Delete(logJSON);
                free(response);
                return (0);
            }
            free(response);
            free(msg);
        } else {
            mdebug1("Unable to parse CIS-CAT event for agent '%s'", lf->agent_id);
            cJSON_Delete(logJSON);
            free(msg);
            return (0);
        }
    }

    cJSON_Delete (logJSON);
    return (1);
}
