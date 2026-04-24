#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define TRUE            1
#define FALSE           0

#define OS_SIZE_1024    1024

#define MEM_ERROR     "(1102): Could not acquire memory due to [(%d)-(%s)]."

#define _PRINTF_FORMAT printf

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

#define CJSON_PUBLIC(type) type

typedef int cJSON_bool;

/* The cJSON structure: */
typedef struct cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct cJSON *next;
    struct cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==cJSON_String  and type == cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} cJSON;

CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);

typedef struct _RuleInfo RuleInfo;
typedef struct _OSDecoderInfo OSDecoderInfo;
typedef struct _OSListNode OSListNode;
typedef struct _EventNode EventNode;
typedef struct wlabel_t wlabel_t;

typedef struct _DynamicField {
    char *key;
    char *value;
} DynamicField;

/* Event Information structure */
typedef struct _Eventinfo {
    /* Extracted from the event */
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

    /* Extracted from the decoders */
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

    /* Pointer to the rule that generated it */
    RuleInfo *generated_rule;

    /* Pointer to the decoder that matched */
    OSDecoderInfo *decoder_info;

    /* Sid node to delete */
    OSListNode *sid_node_to_delete;

    /* Group node to delete */
    OSListNode **group_node_to_delete;

    /* Extract when the event fires a rule */
    size_t size;
    size_t p_name_size;

    /* Other internal variables */
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

    // Node reference
    EventNode *node;
    // Process thread id
    int tid;

    /* Pointer to the previous rule matched */
    void *prev_rule;

} Eventinfo;

/* Case insensitive string comparison, doesn't consider two NULL pointers equal though */
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

void _merror(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _merror_exit(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull)) __attribute__ ((noreturn));

#define merror(msg, ...) _merror(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define merror_exit(msg, ...) _merror_exit(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)

/* for calloc: x = calloc(4,sizeof(char)) -> os_calloc(4,sizeof(char),x) */
#define os_calloc(x,y,z) ((z = (__typeof__(z)) calloc(x,y)))?(void)1:merror_exit(MEM_ERROR, errno, strerror(errno))

/// Enumeration of communication with Wazuh DB status.
typedef enum wdbc_result {
        WDBC_OK,        ///< Command processed successfully
        WDBC_DUE,       ///< Command processed successfully with pending data
        WDBC_ERROR,     ///< An error occurred
        WDBC_IGNORE,    ///< Command ignored
        WDBC_UNKNOWN    ///< Unknown status
} wdbc_result;

int wdbc_query_ex(int *sock, const char *query, char *response, const int len);
int wdbc_parse_result(char *result, char **payload);
void fillData(Eventinfo *lf, const char *key, const char *value);

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

int decode_hotfix(Eventinfo *lf, cJSON * logJSON, int *socket) {
    char * msg = NULL;
    cJSON * hotfix = cJSON_GetObjectItem(logJSON, "hotfix");
    cJSON * scan_id = cJSON_GetObjectItem(logJSON, "ID");
    cJSON * scan_time = cJSON_GetObjectItem(logJSON, "timestamp");
    char response[4096];

    if (!cJSON_IsNumber(scan_id)) {
        return -1;
    }

    os_calloc(OS_SIZE_1024, sizeof(char), msg);

    if (cJSON_IsString(hotfix) && cJSON_IsString(scan_time)) {
        snprintf(msg, OS_SIZE_1024, "agent %s hotfix save %d|%s|%s|",
                lf->agent_id,
                scan_id->valueint,
                scan_time->valuestring,
                hotfix->valuestring);

        fillData(lf, "hotfix", hotfix->valuestring);
        if (wdbc_query_ex(socket, msg, response, sizeof(response)) != 0 || wdbc_parse_result(response, NULL) != WDBC_OK) {
            free(msg);
            return -1;
        }
    } else {
        // Looking for 'end' message.
        char * msg_type = NULL;

        msg_type = cJSON_GetObjectItem(logJSON, "type")->valuestring;

        if (!msg_type) {
            merror("Invalid message. Type not found."); // LCOV_EXCL_LINE
            free(msg);                                  // LCOV_EXCL_LINE
            return -1;                                  // LCOV_EXCL_LINE                 
        } else if (strcmp(msg_type, "hotfix_end") == 0) {
            snprintf(msg, OS_SIZE_1024 - 1, "agent %s hotfix del %d", lf->agent_id, scan_id->valueint);

            if (wdbc_query_ex(socket, msg, response, sizeof(response)) != 0 || wdbc_parse_result(response, NULL) != WDBC_OK) {
                free(msg);
                return -1;
            }
        }
    }

    free(msg);

    return 0;
}
