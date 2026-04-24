#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define OS_SIZE_128     128

#define MEM_ERROR     "(1102): Could not acquire memory due to [(%d)-(%s)]."

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define _PRINTF_FORMAT printf

#define mdebug1(msg, ...) _mdebug1(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define merror(msg, ...) _merror(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define merror_exit(msg, ...) _merror_exit(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)

void _mdebug1(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _merror(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull));
void _merror_exit(const char * file, int line, const char * func, const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 4, 5))) __attribute__((nonnull)) __attribute__ ((noreturn));
void print_out(const char *msg, ...) __attribute__((format(_PRINTF_FORMAT, 1, 2))) __attribute__((nonnull));

#define os_strdup(x,y) ((y = strdup(x)))?(void)1:merror_exit(MEM_ERROR, errno, strerror(errno))

typedef struct _os_ipv4 {
    unsigned int ip_address;
    unsigned int netmask;
} os_ipv4;

typedef struct _os_ipv6 {
    uint8_t ip_address[16];
    uint8_t netmask[16];
} os_ipv6;

typedef struct _os_ip {
    char * ip;
    union {
        os_ipv4 * ipv4;
        os_ipv6 * ipv6;
    };
    bool is_ipv6;
} os_ip;

typedef struct _OSMatch {
    short int negate;
    char *raw;
    int error;
    size_t *size;
    char **patterns;
    int (**match_fp)(const char *str, const char *str2, size_t str_len, size_t size);
} OSMatch;

typedef struct _OSHashNode {
    struct _OSHashNode *next;
    struct _OSHashNode *prev;
    char *key;
    void *data;
} OSHashNode;

typedef struct _OSHash {
    unsigned int rows;
    unsigned int initial_seed;
    unsigned int constant;
    pthread_rwlock_t mutex;
    unsigned int elements;
    void (*free_data_function)(void *data);
    OSHashNode **table;
} OSHash;

typedef struct _OSStore OSStore;
typedef struct _OSList OSList;
typedef struct regex_matching regex_matching;

typedef struct label_flags_t {
    unsigned int hidden:1;
    unsigned int system:1;
} label_flags_t;

typedef struct wlabel_t {
    char *key;
    char *value;
    label_flags_t flags;
} wlabel_t;

typedef struct _socket_forwarder {
    char   *name;
    char   *location;
    int    mode;
    char   *prefix;
    int    socket;
    time_t last_attempt;
} socket_forwarder;

typedef struct __eps {
    unsigned int maximum;
    unsigned int timeframe;
    bool maximum_found;
} _eps;

typedef struct _OSListNode OSListNode;
typedef struct _RuleInfo RuleInfo;
typedef struct _OSDecoderInfo OSDecoderInfo;

typedef struct __Config {
    u_int8_t logall;
    u_int8_t logall_json;
    u_int8_t stats;
    u_int8_t integrity;
    u_int8_t syscheck_auto_ignore;
    int syscheck_ignore_frequency;
    int syscheck_ignore_time;
    u_int8_t syscheck_alert_new;
    u_int8_t rootcheck;
    u_int8_t hostinfo;
    u_int8_t mailbylevel;
    u_int8_t logbylevel;
    u_int8_t logfw;
    u_int8_t update_check;
    int decoder_order_size;
    long agents_disconnection_time;
    long agents_disconnection_alert_time;
    u_int8_t prelude;
    u_int8_t prelude_log_level;
    char *prelude_profile;
    char *geoipdb_file;
    u_int8_t zeromq_output;
    char *zeromq_output_uri;
    char *zeromq_output_server_cert;
    char *zeromq_output_client_cert;
    u_int8_t jsonout_output;
    u_int8_t alerts_log;
    u_int8_t keeplogdate;
    short int mailnotify;
    short int custom_alert_output;
    char *custom_alert_output_format;
    int ar;
    int memorysize;
    char **syscheck_ignore;
    os_ip **white_list;
    OSMatch **hostname_white_list;
    char **includes;
    char **lists;
    char **decoders;
    OSHash *g_rules_hash;
    char** forwarders_list;
    socket_forwarder *socket_list;
#ifdef LIBGEOIP_ENABLED
    u_int8_t loggeoip;
    char *geoip_db_path;
    char *geoip6_db_path;
    int geoip_jsonout;
#endif
    wlabel_t *labels;
    int label_cache_maxage;
    int show_hidden_labels;
    char *cluster_name;
    char *node_name;
    char *node_type;
    unsigned char hide_cluster_info;
    int rotate_interval;
    int min_rotate_interval;
    ssize_t max_output_size;
    long queue_size;
    _eps eps;
    char *cti_url;
} _Config;

extern _Config Config;

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

typedef struct _EventNode EventNode;

typedef struct _DynamicField {
    char *key;
    char *value;
} DynamicField;

typedef struct _Eventinfo {
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
} Eventinfo;

#ifdef TESTRULE
extern int alert_only;
#endif

char *GetGeoInfobyIP(char *ip_addr);

void fillData(Eventinfo *lf, const char *key, const char *value)
{

    if (!key)
        return;

    if (strcmp(key, "srcip") == 0){
        os_strdup(value, lf->srcip);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       srcip: '%s'", lf->srcip);
        }
#endif

#ifdef LIBGEOIP_ENABLED
    if (!lf->srcgeoip) {
        lf->srcgeoip = GetGeoInfobyIP(lf->srcip);
#ifdef TESTRULE
        if (lf->srcgeoip && !alert_only) {
            print_out("       srcgeoip: '%s'", lf->srcgeoip);
        }
#endif
    }
#endif
        return;
    }

    if (strcmp(key, "dstip") == 0){
        os_strdup(value, lf->dstip);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       dstip: '%s'", lf->dstip);
        }
#endif

#ifdef LIBGEOIP_ENABLED
    if(!lf->dstgeoip) {
        lf->dstgeoip = GetGeoInfobyIP(lf->dstip);
#ifdef TESTRULE
            if (lf->dstgeoip && !alert_only)
                print_out("       dstgeoip: '%s'", lf->dstgeoip);
#endif
    }
#endif
    return;
    }

    if (strcmp(key, "dstport") == 0){
        os_strdup(value, lf->dstport);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       dstport: '%s'", lf->dstport);
        }
#endif
        return;
    }

    if (strcmp(key, "srcport") == 0){
        os_strdup(value, lf->srcport);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       srcport: '%s'", lf->srcport);
        }
#endif
        return;
    }

    if (strcmp(key, "protocol") == 0){
        os_strdup(value, lf->protocol);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       protocol: '%s'", lf->protocol);
        }
#endif
        return;
    }

    if (strcmp(key, "action") == 0){
        os_strdup(value, lf->action);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       action: '%s'", lf->action);
        }
#endif
        return;
    }

    if (strcmp(key, "srcuser") == 0){
        os_strdup(value, lf->srcuser);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       srcuser: '%s'", lf->srcuser);
        }
#endif
        return;
    }

    if (strcmp(key, "dstuser") == 0){
        os_strdup(value, lf->dstuser);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       dstuser: '%s'", lf->dstuser);
        }
#endif
        return;
    }

    if (strcmp(key, "id") == 0){
        os_strdup(value, lf->id);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       id: '%s'", lf->id);
        }
#endif
        return;
    }

    if (strcmp(key, "status") == 0){
        os_strdup(value, lf->status);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       status: '%s'", lf->status);
        }
#endif
        return;
    }

    if (strcmp(key, "url") == 0){
        os_strdup(value, lf->url);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       url: '%s'", lf->url);
        }
#endif
        return;
    }

    if (strcmp(key, "data") == 0){
        os_strdup(value, lf->data);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       data: '%s'", lf->data);
        }
#endif
        return;
    }

    if (strcmp(key, "extra_data") == 0){
        os_strdup(value, lf->extra_data);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       extra_data: '%s'", lf->extra_data);
        }
#endif
        return;
    }

    if (strcmp(key, "systemname") == 0){
        os_strdup(value, lf->systemname);
#ifdef TESTRULE
        if (!alert_only) {
            print_out("       systemname: '%s'", lf->systemname);
        }
#endif
        return;
    }

    // Dynamic fields
    if (lf->nfields >= Config.decoder_order_size) {
        merror("Too many fields for JSON decoder.");
        return;
    }
#ifdef TESTRULE
    if (!alert_only) {
        print_out("       %s: '%s'", key, value);
    }
#endif

    os_strdup(key, lf->fields[lf->nfields].key);
    os_strdup(value, lf->fields[lf->nfields].value);
    lf->nfields++;

}

static void FillScanInfo(Eventinfo *lf,cJSON *scan_id,cJSON *name,cJSON *description,cJSON *pass,cJSON *failed,cJSON *invalid,cJSON *total_checks,cJSON *score,cJSON *file,cJSON *policy_id) {
    assert(lf);
    fillData(lf, "sca.type", "summary");

    if(scan_id) {
        char value[OS_SIZE_128];

        if(scan_id->valueint >= 0){
            sprintf(value, "%d", scan_id->valueint);
        } else if (scan_id->valuedouble) {
            sprintf(value, "%lf", scan_id->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.scan_id' type: %d.", scan_id->type);
            return;
        }

        fillData(lf, "sca.scan_id", value);
    }

    if(name) {
        fillData(lf, "sca.policy", name->valuestring);
    }

    if(description) {
        fillData(lf, "sca.description", description->valuestring);
    }

    if(policy_id) {
        fillData(lf, "sca.policy_id", policy_id->valuestring);
    }

    if(pass) {
        char value[OS_SIZE_128];

        if(pass->valueint >= 0){
            sprintf(value, "%d", pass->valueint);
        } else if (pass->valuedouble >= 0) {
            sprintf(value, "%lf", pass->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.passed' type: %d", pass->type);
            return;
        }

        fillData(lf, "sca.passed", value);
    }

    if(failed) {
        char value[OS_SIZE_128];

        if(failed->valueint >= 0){
            sprintf(value, "%d", failed->valueint);
        } else if (failed->valuedouble >= 0) {
            sprintf(value, "%lf", failed->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.failed' type: %d", failed->type);
            return;
        }

        fillData(lf, "sca.failed", value);
    }

    if(invalid) {
        char value[OS_SIZE_128];

        if(invalid->valueint >= 0){
            sprintf(value, "%d", invalid->valueint);
        } else if (invalid->valuedouble >= 0) {
            sprintf(value, "%lf", invalid->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.invalid' type: %d", invalid->type);
            return;
        }

        fillData(lf, "sca.invalid", value);
    }

    if(total_checks) {
        char value[OS_SIZE_128];

        if(total_checks->valueint >= 0){
            sprintf(value, "%d", total_checks->valueint);
        } else if (total_checks->valuedouble >= 0) {
            sprintf(value, "%lf", total_checks->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.total_checks' type: %d", total_checks->type);
            return;
        }

        fillData(lf, "sca.total_checks", value);
    }

    if(score) {
        char value[OS_SIZE_128];

        if(score->valueint >= 0){
            sprintf(value, "%d", score->valueint);
        } else if (score->valuedouble >= 0) {
            sprintf(value, "%lf", score->valuedouble);
        } else {
            mdebug1("Unexpected 'sca.score' type: %d", score->type);
            return;
        }

        fillData(lf, "sca.score", value);
    }

    if(file){
        fillData(lf, "sca.file", file->valuestring);
    }
}
