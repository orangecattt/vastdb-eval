#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>

#define TRUE            1
#define FALSE           0
#define OS_SIZE_1048576 1048576
#define OS_SIZE_65536   65536
#define OS_SIZE_61440   61440
#define OS_SIZE_32768   32768
#define OS_SIZE_20480   20480
#define OS_SIZE_8192    8192
#define OS_SIZE_6144    6144
#define OS_SIZE_4096    4096
#define OS_SIZE_2048    2048
#define OS_SIZE_1024    1024
#define OS_SIZE_512     512
#define OS_SIZE_256     256
#define OS_SIZE_128     128
#define OS_SIZE_64      64
#define OS_SIZE_32      32
#define OS_SIZE_16      16
#define OS_MAXSTR       OS_SIZE_65536
#define OS_BUFFER_SIZE  OS_SIZE_2048
#define OS_FLSIZE       OS_SIZE_256
#define OS_HEADER_SIZE  OS_SIZE_128
#define OS_LOG_HEADER   OS_SIZE_256
#define OS_SK_HEADER    OS_SIZE_6144

#define SYSCHECK        "syscheck"
#define SYSCHECK_REG    "syscheck-registry"

#define OSSEC_RL        11

#ifndef __GNUC__
#define __attribute__(x)
#endif
#define mdebug1(msg, ...) _mdebug1(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define mdebug2(msg, ...) _mdebug2(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define merror(msg, ...) _merror(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define mwarn(msg, ...) _mwarn(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
#define merror_exit(msg, ...) _merror_exit(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
void _mdebug1(const char *file, int line, const char *func, const char *msg, ...) __attribute__((format(printf, 4, 5)));
void _mdebug2(const char *file, int line, const char *func, const char *msg, ...) __attribute__((format(printf, 4, 5)));
void _merror(const char *file, int line, const char *func, const char *msg, ...) __attribute__((format(printf, 4, 5)));
void _mwarn(const char *file, int line, const char *func, const char *msg, ...) __attribute__((format(printf, 4, 5)));
void _merror_exit(const char *file, int line, const char *func, const char *msg, ...) __attribute__((format(printf, 4, 5))) __attribute__((noreturn));

#define MEM_ERROR "Memory error: %d (%s)"
#define os_calloc(x,y,z) ((z = (__typeof__(z)) calloc(x,y)))?(void)1:merror_exit(MEM_ERROR, errno, strerror(errno))
#define os_strdup(x,y) ((y = strdup(x)))?(void)1:merror_exit(MEM_ERROR, errno, strerror(errno))
#define os_free(x) if(x){free(x);x=NULL;}

#define w_long_str(x) ({char *do_str; os_calloc(32, sizeof(char),do_str); snprintf(do_str, 31, "%ld", x); do_str;})
int wm_strcat(char **str1, const char *str2, char sep);
char *wstr_replace(const char *string, const char *search, const char *replace);
char *wstr_chr(const char *str, char character);

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

void *OSHash_Get_ex(const OSHash *self, const char *key);
int OSHash_Add_ex(OSHash *hash, const char *key, void *data);
OSHash *OSHash_Create(void);

typedef struct _OSListNode {
    struct _OSListNode *next;
    struct _OSListNode *prev;
    void *data;
} OSListNode;

typedef struct _RuleInfo RuleInfo;

struct _Eventinfo;
typedef struct {
    uint8_t  get_next;
    uint8_t  type;
    uint8_t  use_own_name;
    uint8_t  flags;
    uint16_t id;
    uint16_t regex_offset;
    uint16_t prematch_offset;
    uint16_t plugin_offset;
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
    void* (**order)(struct _Eventinfo *, char *, const char *);
    bool internal_saving;
} OSDecoderInfo;

typedef enum label_flags_t {
    LABEL_FL_NONE = 0,
} label_flags_t;

typedef struct wlabel_t {
    char *key;
    char *value;
    label_flags_t flags;
} wlabel_t;

typedef enum syscheck_event_t { FIM_ADDED, FIM_MODIFIED, FIM_READDED, FIM_DELETED } syscheck_event_t;

typedef struct _DynamicField {
    char *key;
    char *value;
} DynamicField;

typedef struct _Eventinfo {
    char *log;
    char *full_log;
    const char *log_after_parent;
    const char *log_after_prematch;
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
    uint16_t decoder_syscheck_id;
    int rootcheck_fts;
    int is_a_copy;
    char **last_events;
    int r_firedtimes;
    int queue_added;
    void *node;
    int tid;
    void *prev_rule;
} Eventinfo;

extern const char *SYSCHECK_EVENT_STRINGS[];

typedef enum fim_fields {
    FIM_FILE,
    FIM_HARD_LINKS,
    FIM_MODE,
    FIM_SIZE,
    FIM_SIZE_BEFORE,
    FIM_PERM,
    FIM_PERM_BEFORE,
    FIM_UID,
    FIM_UID_BEFORE,
    FIM_GID,
    FIM_GID_BEFORE,
    FIM_MD5,
    FIM_MD5_BEFORE,
    FIM_SHA1,
    FIM_SHA1_BEFORE,
    FIM_UNAME,
    FIM_UNAME_BEFORE,
    FIM_GNAME,
    FIM_GNAME_BEFORE,
    FIM_MTIME,
    FIM_MTIME_BEFORE,
    FIM_INODE,
    FIM_INODE_BEFORE,
    FIM_SHA256,
    FIM_SHA256_BEFORE,
    FIM_DIFF,
    FIM_ATTRS,
    FIM_ATTRS_BEFORE,
    FIM_CHFIELDS,
    FIM_USER_ID,
    FIM_USER_NAME,
    FIM_GROUP_ID,
    FIM_GROUP_NAME,
    FIM_PROC_NAME,
    FIM_PROC_PNAME,
    FIM_AUDIT_CWD,
    FIM_AUDIT_PCWD,
    FIM_AUDIT_ID,
    FIM_AUDIT_NAME,
    FIM_EFFECTIVE_UID,
    FIM_EFFECTIVE_NAME,
    FIM_PPID,
    FIM_PROC_ID,
    FIM_TAG,
    FIM_SYM_PATH,
    FIM_REGISTRY_ARCH,
    FIM_REGISTRY_VALUE_NAME,
    FIM_REGISTRY_VALUE_TYPE,
    FIM_REGISTRY_HASH,
    FIM_ENTRY_TYPE,
    FIM_EVENT_TYPE,
    FIM_NFIELDS
} fim_fields;

typedef struct __sdb {
    char comment[OS_MAXSTR + 1];
    char size[OS_FLSIZE + 1];
    char perm[OS_FLSIZE + 1];
    char owner[OS_FLSIZE + 1];
    char gowner[OS_FLSIZE + 1];
    char md5[OS_FLSIZE + 1];
    char sha1[OS_FLSIZE + 1];
    char sha256[OS_FLSIZE + 1];
    char mtime[OS_FLSIZE + 1];
    char inode[OS_FLSIZE + 1];
    char attrs[OS_SIZE_1024 + 1];
    char sym_path[OS_FLSIZE + 1];
    char user_id[OS_FLSIZE + 1];
    char user_name[OS_FLSIZE + 1];
    char group_id[OS_FLSIZE + 1];
    char group_name[OS_FLSIZE + 1];
    char process_name[OS_FLSIZE + 1];
    char audit_uid[OS_FLSIZE + 1];
    char audit_name[OS_FLSIZE + 1];
    char effective_uid[OS_FLSIZE + 1];
    char effective_name[OS_FLSIZE + 1];
    char ppid[OS_FLSIZE + 1];
    char process_id[OS_FLSIZE + 1];
    int db_err;
    int socket;
} _sdb;

typedef struct sk_sum_wdata {
    char *user_id;
    char *user_name;
    char *group_id;
    char *group_name;
    char *process_name;
    char *cwd;
    char *audit_uid;
    char *audit_name;
    char *effective_uid;
    char *effective_name;
    char *parent_name;
    char *parent_cwd;
    char *ppid;
    char *process_id;
} sk_sum_wdata;

typedef struct sk_sum_t {
    char *size;
    int perm;
    char *win_perm;
    char *uid;
    char *gid;
    char *md5;
    char *sha1;
    char *sha256;
    char *attributes;
    char *uname;
    char *gname;
    long mtime;
    long inode;
    char *tag;
    char *symbolic_path;
    sk_sum_wdata wdata;
    int changes;
    char silent;
    long date_alert;
} sk_sum_t;

int sk_decode_sum(sk_sum_t *sum, char *c_sum, char *w_sum);
void sk_fill_event(Eventinfo *lf, const char *f_name, const sk_sum_t *sum);
void sk_sum_clean(sk_sum_t *sum);
char *escape_syscheck_field(char *field);
char *unescape_syscheck_field(char *sum);
int wdbc_query_ex(int *sock, const char *query, char *response, const int len);
char *agent_file_perm(mode_t mode);

typedef struct __Config {
    uint8_t logall;
    uint8_t logall_json;
    uint8_t stats;
    uint8_t integrity;
    uint8_t syscheck_auto_ignore;
    int syscheck_ignore_frequency;
    int syscheck_ignore_time;
    uint8_t syscheck_alert_new;
    uint8_t rootcheck;
    uint8_t hostinfo;
    uint8_t mailbylevel;
    uint8_t logbylevel;
    uint8_t logfw;
    uint8_t update_check;
    int decoder_order_size;
    long agents_disconnection_time;
    long agents_disconnection_alert_time;
    uint8_t prelude;
    uint8_t prelude_log_level;
    char *prelude_profile;
    char *geoipdb_file;
    uint8_t zeromq_output;
    char *zeromq_output_uri;
    char *zeromq_output_server_cert;
    char *zeromq_output_client_cert;
    uint8_t jsonout_output;
    uint8_t alerts_log;
    uint8_t keeplogdate;
    short int mailnotify;
    short int custom_alert_output;
    char *custom_alert_output_format;
    int ar;
    int memorysize;
    char **syscheck_ignore;
    void **white_list;
    void **hostname_white_list;
    char **includes;
    char **lists;
    char **decoders;
    OSHash *g_rules_hash;
    char** forwarders_list;
    void *socket_list;
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
    char *cti_url;
} _Config;

extern _Config Config;
extern OSHash *fim_agentinfo;

typedef enum DECODER_TYPE { FILE_DECODER, REGISTRY_KEY_DECODER, REGISTRY_VALUE_DECODER } DECODER_TYPE;

typedef struct _fim_decoders_t {
    int add_id;
    char *add_name;
    int modify_id;
    char *modify_name;
    int delete_id;
    char *delete_name;
} fim_decoders_t;

extern fim_decoders_t *fim_decoders[];

void InsertWhodata(const sk_sum_t *sum, _sdb *localsdb);
int SumCompare(const char *s1, const char *s2);
int fim_check_changes(int saved_frequency, long saved_time, Eventinfo *lf);
void fim_adjust_checksum(sk_sum_t *newsum, char **checksum);
int fim_update_date(char *file, Eventinfo *lf, _sdb *sdb);
int fim_get_scantime(long *ts, Eventinfo *lf, _sdb *sdb, const char *param);

int fim_alert (char *f_name, sk_sum_t *oldsum, sk_sum_t *newsum, Eventinfo *lf, _sdb *localsdb, syscheck_event_t event_type) {
    int changes = 0;
    char msg_type[OS_FLSIZE];
    char buf_ptr[26];

    if (event_type == FIM_DELETED) {
        snprintf(msg_type, sizeof(msg_type), "was deleted.");
        lf->decoder_info->id = fim_decoders[FILE_DECODER]->delete_id;
        lf->decoder_syscheck_id = lf->decoder_info->id;
        lf->decoder_info->name = fim_decoders[FILE_DECODER]->delete_name;
        changes = 1;
    } else if (event_type == FIM_ADDED) {
        snprintf(msg_type, sizeof(msg_type), "was added.");
        lf->decoder_info->id = fim_decoders[FILE_DECODER]->add_id;
        lf->decoder_syscheck_id = lf->decoder_info->id;
        lf->decoder_info->name = fim_decoders[FILE_DECODER]->add_name;
        changes = 1;
    } else if (event_type == FIM_MODIFIED) {
        snprintf(msg_type, sizeof(msg_type), "checksum changed.");
        lf->decoder_info->id = fim_decoders[FILE_DECODER]->modify_id;
        lf->decoder_syscheck_id = lf->decoder_info->id;
        lf->decoder_info->name = fim_decoders[FILE_DECODER]->modify_name;
        if (oldsum->size && newsum->size) {
            if (strcmp(oldsum->size, newsum->size) == 0) {
                localsdb->size[0] = '\0';
            } else {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "size", ',');
                snprintf(localsdb->size, OS_FLSIZE,
                            "Size changed from '%s' to '%s'\n",
                            oldsum->size, newsum->size);

                os_strdup(oldsum->size, lf->fields[FIM_SIZE_BEFORE].value);
            }
        }

        /* Permission message */
        if (oldsum->perm && newsum->perm) {
            if (oldsum->perm == newsum->perm) {
                localsdb->perm[0] = '\0';
            } else if (oldsum->perm > 0 && newsum->perm > 0) {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "perm", ',');
                char opstr[10];
                char npstr[10];
                lf->fields[FIM_PERM_BEFORE].value = agent_file_perm(oldsum->perm);
                char *new_perm = agent_file_perm(newsum->perm);

                strncpy(opstr, lf->fields[FIM_PERM_BEFORE].value, sizeof(opstr) - 1);
                strncpy(npstr, new_perm, sizeof(npstr) - 1);
                free(new_perm);

                opstr[9] = npstr[9] = '\0';
                snprintf(localsdb->perm, OS_FLSIZE, "Permissions changed from "
                            "'%9.9s' to '%9.9s'\n", opstr, npstr);
            }
        } else if (oldsum->win_perm && newsum->win_perm) { // Check for Windows permissions
            // We need to unescape the old permissions at this point
            char *unesc_perms = wstr_replace(oldsum->win_perm, "\\:", ":");
            free(oldsum->win_perm);
            oldsum->win_perm = unesc_perms;
            if (strcmp(oldsum->win_perm, newsum->win_perm) == 0) {
                localsdb->perm[0] = '\0';
            } else if (*oldsum->win_perm != '\0' && *newsum->win_perm != '\0') {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "perm", ',');
                snprintf(localsdb->perm, OS_FLSIZE, "Permissions changed.\n");
                os_strdup(oldsum->win_perm, lf->fields[FIM_PERM_BEFORE].value);
            }
        }

        /* Ownership message */
        if (newsum->uid && oldsum->uid) {
            if (strcmp(newsum->uid, oldsum->uid) == 0) {
                localsdb->owner[0] = '\0';
            } else {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "uid", ',');
                if (oldsum->uname && newsum->uname) {
                    snprintf(localsdb->owner, OS_FLSIZE, "Ownership was '%s (%s)', now it is '%s (%s)'\n", oldsum->uname, oldsum->uid, newsum->uname, newsum->uid);
                    os_strdup(oldsum->uname, lf->fields[FIM_UNAME_BEFORE].value);
                } else {
                    snprintf(localsdb->owner, OS_FLSIZE, "Ownership was '%s', now it is '%s'\n", oldsum->uid, newsum->uid);
                }
                os_strdup(oldsum->uid, lf->fields[FIM_UID_BEFORE].value);
            }
        }

        /* Group ownership message */
        if (newsum->gid && oldsum->gid) {
            if (strcmp(newsum->gid, oldsum->gid) == 0) {
                localsdb->gowner[0] = '\0';
            } else {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "gid", ',');
                if (oldsum->gname && newsum->gname) {
                    snprintf(localsdb->gowner, OS_FLSIZE, "Group ownership was '%s (%s)', now it is '%s (%s)'\n", oldsum->gname, oldsum->gid, newsum->gname, newsum->gid);
                    os_strdup(oldsum->gname, lf->fields[FIM_GNAME_BEFORE].value);
                } else {
                    snprintf(localsdb->gowner, OS_FLSIZE, "Group ownership was '%s', now it is '%s'\n", oldsum->gid, newsum->gid);
                }
                os_strdup(oldsum->gid, lf->fields[FIM_GID_BEFORE].value);
            }
        }
        /* MD5 message */
        if (newsum->md5 == NULL || newsum->md5[0] == '\0' || oldsum->md5 == NULL || oldsum->md5[0] == '\0'
            || strcmp(newsum->md5, oldsum->md5) == 0) {
            localsdb->md5[0] = '\0';
        } else {
            changes = 1;
            wm_strcat(&lf->fields[FIM_CHFIELDS].value, "md5", ',');
            snprintf(localsdb->md5, OS_FLSIZE, "Old md5sum was: '%s'\nNew md5sum is : '%s'\n",
                        oldsum->md5, newsum->md5);
            os_strdup(oldsum->md5, lf->fields[FIM_MD5_BEFORE].value);
        }

        /* SHA-1 message */
        if (newsum->sha1 == NULL || newsum->sha1[0] == '\0' || oldsum->sha1 == NULL || oldsum->sha1[0] == '\0'
            || strcmp(newsum->sha1, oldsum->sha1) == 0) {
            localsdb->sha1[0] = '\0';
        } else {
            changes = 1;
            wm_strcat(&lf->fields[FIM_CHFIELDS].value, "sha1", ',');
            snprintf(localsdb->sha1, OS_FLSIZE, "Old sha1sum was: '%s'\nNew sha1sum is : '%s'\n",
                        oldsum->sha1, newsum->sha1);
            os_strdup(oldsum->sha1, lf->fields[FIM_SHA1_BEFORE].value);
        }

        /* SHA-256 message */
        if(newsum->sha256 && newsum->sha256[0] != '\0') {
            if(oldsum->sha256) {
                if (strcmp(newsum->sha256, oldsum->sha256) == 0) {
                    localsdb->sha256[0] = '\0';
                } else {
                    changes = 1;
                    wm_strcat(&lf->fields[FIM_CHFIELDS].value, "sha256", ',');
                    snprintf(localsdb->sha256, OS_FLSIZE, "Old sha256sum was: '%s'\nNew sha256sum is : '%s'\n",
                            oldsum->sha256, newsum->sha256);
                    os_strdup(oldsum->sha256, lf->fields[FIM_SHA256_BEFORE].value);
                }
            } else {
                changes = 1;
                wm_strcat(&lf->fields[FIM_CHFIELDS].value, "sha256", ',');
                snprintf(localsdb->sha256, OS_FLSIZE, "New sha256sum is : '%s'\n", newsum->sha256);
            }
        } else {
            localsdb->sha256[0] = '\0';
        }

        /* Modification time message */
        if (oldsum->mtime && newsum->mtime && oldsum->mtime != newsum->mtime) {
            changes = 1;
            wm_strcat(&lf->fields[FIM_CHFIELDS].value, "mtime", ',');
            char *old_ctime = strdup(ctime_r(&oldsum->mtime, buf_ptr));
            char *new_ctime = strdup(ctime_r(&newsum->mtime, buf_ptr));
            old_ctime[strlen(old_ctime) - 1] = '\0';
            new_ctime[strlen(new_ctime) - 1] = '\0';

            snprintf(localsdb->mtime, OS_FLSIZE, "Old modification time was: '%s', now it is '%s'\n", old_ctime, new_ctime);
            lf->fields[FIM_MTIME_BEFORE].value = w_long_str(oldsum->mtime);
            os_free(old_ctime);
            os_free(new_ctime);
        } else {
            localsdb->mtime[0] = '\0';
        }

        /* Inode message */
        if (oldsum->inode && newsum->inode && oldsum->inode != newsum->inode) {
            changes = 1;
            wm_strcat(&lf->fields[FIM_CHFIELDS].value, "inode", ',');
            snprintf(localsdb->inode, OS_FLSIZE, "Old inode was: '%ld', now it is '%ld'\n", oldsum->inode, newsum->inode);
            lf->fields[FIM_INODE_BEFORE].value = w_long_str(oldsum->inode);
        } else {
            localsdb->inode[0] = '\0';
        }

        /* Attributes message */
        if (oldsum->attributes && newsum->attributes
            && strcmp(oldsum->attributes, newsum->attributes)) {
            changes = 1;
            wm_strcat(&lf->fields[FIM_CHFIELDS].value, "attributes", ',');
            snprintf(localsdb->attrs, OS_SIZE_1024, "Old attributes were: '%s'\nNow they are '%s'\n", oldsum->attributes, newsum->attributes);
            os_strdup(oldsum->attributes, lf->fields[FIM_ATTRS_BEFORE].value);
        } else {
            localsdb->attrs[0] = '\0';
        }
    } else {
        return (-1);
    }

    /* Symbolic path message */
    if (newsum->symbolic_path && *newsum->symbolic_path) {
        snprintf(localsdb->sym_path, OS_FLSIZE, "Symbolic path: '%s'.\n", newsum->symbolic_path);
    } else {
        *localsdb->sym_path = '\0';
    }

    // Provide information about the file
    snprintf(localsdb->comment, OS_MAXSTR, "File"
            " '%.756s' "
            "%s\n"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s"
            "%s",
            f_name,
            msg_type,
            localsdb->sym_path,
            localsdb->size,
            localsdb->perm,
            localsdb->owner,
            localsdb->gowner,
            localsdb->md5,
            localsdb->sha1,
            localsdb->sha256,
            localsdb->attrs,
            localsdb->mtime,
            localsdb->inode
    );
    if(!changes) {
        os_free(lf->data);
        return(-1);
    } else if (lf->fields[FIM_CHFIELDS].value != NULL) {
        wm_strcat(&lf->fields[FIM_CHFIELDS].value, ",", '\0');
    }

    // Create a new log message
    free(lf->full_log);
    os_strdup(localsdb->comment, lf->full_log);
    lf->log = lf->full_log;
    // Force clean event
    lf->program_name = NULL;
    lf->dec_timestamp = NULL;

    return (0);
}

int sk_decode_extradata(sk_sum_t *sum, char *c_sum) {
    char *changes;
    char *date_alert;
    char *sym_path;

    assert(sum != NULL);
    assert(c_sum != NULL);

    if (changes = strchr(c_sum, '!'), !changes) {
        return 0;
    }
    *changes++ = '\0';

    if (date_alert = strchr(changes, ':'), !date_alert) {
        return 0;
    }
    *(date_alert++) = '\0';

    if (sym_path = strchr(date_alert, ':'), sym_path) {
        *(sym_path++) = '\0';
        sum->symbolic_path = unescape_syscheck_field(sym_path);
    }

    sum->changes = atoi(changes);
    sum->date_alert = atol(date_alert);

    return 1;
}

int fim_db_search(char *f_name, char *c_sum, char *w_sum, Eventinfo *lf, _sdb *sdb) {
    int decode_newsum = 0;
    int db_result = 0;
    int changes = 0;
    int i = 0;
    char *ttype[OS_SIZE_128];
    char *wazuhdb_query = NULL;
    char *new_check_sum = NULL;
    char *old_check_sum = NULL;
    char *response = NULL;
    char *check_sum = NULL;
    char *sym_path = NULL;
    sk_sum_t oldsum = { .size = NULL };
    sk_sum_t newsum = { .size = NULL };
    time_t *end_first_scan = NULL;
    time_t end_scan = 0;
    syscheck_event_t event_type;

    memset(&oldsum, 0, sizeof(sk_sum_t));
    memset(&newsum, 0, sizeof(sk_sum_t));

    os_calloc(OS_SIZE_6144 + 1, sizeof(char), wazuhdb_query);
    os_strdup(c_sum, new_check_sum);

    snprintf(wazuhdb_query, OS_SIZE_6144, "agent %s syscheck load %s", lf->agent_id, f_name);

    os_calloc(OS_SIZE_6144, sizeof(char), response);
    db_result = wdbc_query_ex(&sdb->socket, wazuhdb_query, response, OS_SIZE_6144);

    // Fail trying load info from DDBB

    switch (db_result) {
    case -2:
        merror("FIM decoder: Bad load query: '%s'.", wazuhdb_query);
        // Fallthrough
    case -1:
        os_free(lf->data);
        goto exit_fail;
    }

    if(check_sum = wstr_chr(response, ' '), !check_sum) {
        merror("FIM decoder: Bad response: '%s' '%s'.", wazuhdb_query, response);
        goto exit_fail;
    }
    *(check_sum++) = '\0';

    if (strcmp(response, "ok") != 0) {
        goto exit_fail;
    }

    //extract changes and date_alert fields only available from wazuh_db
    sk_decode_extradata(&oldsum, check_sum);

    os_strdup(check_sum, old_check_sum);
    mdebug2("Agent '%s' File '%s'", lf->agent_id, f_name);
    mdebug2("Agent '%s' Old checksum '%s'", lf->agent_id, old_check_sum);
    mdebug2("Agent '%s' New checksum '%s'", lf->agent_id, new_check_sum);

    if (decode_newsum = sk_decode_sum(&newsum, c_sum, w_sum), decode_newsum != -1) {
        InsertWhodata(&newsum, sdb);
    }

    fim_adjust_checksum(&newsum, &new_check_sum);

    // Checksum match, we can just return and keep going
    if (SumCompare(old_check_sum, new_check_sum) == 0) {
        mdebug1("Agent '%s' Alert discarded '%s' same check_sum", lf->agent_id, f_name);
        fim_update_date (f_name, lf, sdb);
        goto exit_ok;
    }

    wazuhdb_query[0] = '\0';
    switch (decode_newsum) {
        case 1: // File deleted
            os_strdup(SYSCHECK_EVENT_STRINGS[FIM_DELETED], lf->fields[FIM_EVENT_TYPE].value);
            event_type = FIM_DELETED;

            if(!*old_check_sum){
                mdebug2("Agent '%s' Alert already reported (double delete alert)", lf->agent_id);
                goto exit_ok;
            }

            snprintf(wazuhdb_query, OS_SIZE_6144, "agent %s syscheck delete %s",
                    lf->agent_id,
                    f_name
            );

            db_result = wdbc_query_ex(&sdb->socket, wazuhdb_query, response, OS_SIZE_6144);

            switch (db_result) {
            case -2:
                merror("FIM decoder: Bad delete query: '%s'.", wazuhdb_query);
                // Fallthrough
            case -1:
                goto exit_fail;
            }

            mdebug2("Agent '%s' File %s deleted from FIM DDBB", lf->agent_id, f_name);

            break;
        case 0:
            if (*old_check_sum) {
                // File modified
                os_strdup(SYSCHECK_EVENT_STRINGS[FIM_MODIFIED], lf->fields[FIM_EVENT_TYPE].value);
                event_type = FIM_MODIFIED;
                changes = fim_check_changes(oldsum.changes, oldsum.date_alert, lf);
                sk_decode_sum(&oldsum, old_check_sum, NULL);

                // Alert discarded, frequency exceeded
                if (changes == -1) {
                    mdebug1("Agent '%s' Alert discarded '%s' frequency exceeded", lf->agent_id, f_name);
                    goto exit_ok;
                }
            } else {
                // File added
                os_strdup(SYSCHECK_EVENT_STRINGS[FIM_ADDED], lf->fields[FIM_EVENT_TYPE].value);
                event_type = FIM_ADDED;
            }

            if (strstr(lf->location, "syscheck-registry")) {
                *ttype = "registry";
            } else {
                *ttype = "file";
            }

            if (newsum.symbolic_path) {
                sym_path = escape_syscheck_field(newsum.symbolic_path);
            }

            // We need to escape the checksum because it will have
            // spaces if the event comes from Windows
            char *checksum_esc = wstr_replace(new_check_sum, " ", "\\ ");
            snprintf(wazuhdb_query, OS_SIZE_6144, "agent %s syscheck save %s %s!%d:%ld:%s %s",
                    lf->agent_id,
                    *ttype,
                    checksum_esc,
                    changes,
                    lf->time.tv_sec,
                    sym_path ? sym_path : "",
                    f_name
            );
            os_free(sym_path);
            os_free(checksum_esc);
            db_result = wdbc_query_ex(&sdb->socket, wazuhdb_query, response, OS_SIZE_6144);

            switch (db_result) {
            case -2:
                merror("FIM decoder: Bad save/update query: '%s'.", wazuhdb_query);
                // Fallthrough
            case -1:
                goto exit_fail;
            }

            mdebug2("Agent '%s' File %s saved/updated in FIM DDBB", lf->agent_id, f_name);

            if (end_first_scan = (time_t *)OSHash_Get_ex(fim_agentinfo, lf->agent_id), end_first_scan == NULL) {
                fim_get_scantime(&end_scan, lf, sdb, "end_scan");
                os_calloc(1, sizeof(time_t), end_first_scan);
                *end_first_scan = end_scan;
                int res;
                if (res = OSHash_Add_ex(fim_agentinfo, lf->agent_id, end_first_scan), res != 2) {
                    os_free(end_first_scan);
                    if (res == 0) {
                        merror("Unable to add scan_info to hash table for agent: %s", lf->agent_id);
                    }
                }
            } else {
                end_scan = *end_first_scan;
            }

            if (event_type == FIM_ADDED) {
                if (end_scan == 0) {
                    mdebug2("Agent '%s' Alert discarded, first scan. File '%s'", lf->agent_id, f_name);
                    goto exit_ok;
                } else if (lf->time.tv_sec < end_scan) {
                    mdebug2("Agent '%s' Alert discarded, first scan (delayed event). File '%s'", lf->agent_id, f_name);
                    goto exit_ok;
                } else if (Config.syscheck_alert_new == 0) {
                    mdebug2("Agent '%s' Alert discarded (alert_new_files = no). File '%s'", lf->agent_id, f_name);
                    goto exit_ok;
                }
            }

            mdebug2("Agent '%s' End end_scan is '%ld' (lf->time: '%ld')", lf->agent_id, end_scan, lf->time.tv_sec);
            break;

        default: // Error in fim check sum
            mwarn("at fim_db_search: Agent '%s' Couldn't decode fim sum '%s' from file '%s'.",
                    lf->agent_id, new_check_sum, f_name);
            goto exit_fail;
    }

    if (!newsum.silent) {
        sk_fill_event(lf, f_name, &newsum);

        /* Dyanmic Fields */
        lf->nfields = FIM_NFIELDS;
        for (i = 0; i < FIM_NFIELDS; i++) {
            os_strdup(lf->decoder_info->fields[i], lf->fields[i].key);
        }

        if(fim_alert(f_name, &oldsum, &newsum, lf, sdb, event_type) == -1) {
            //No changes in checksum
            goto exit_ok;
        }
        sk_sum_clean(&newsum);
        sk_sum_clean(&oldsum);
        os_free(response);
        os_free(new_check_sum);
        os_free(old_check_sum);
        os_free(wazuhdb_query);

        return (1);
    } else {
        mdebug2("Ignoring FIM event on '%s'.", f_name);
    }

exit_ok:
    sk_sum_clean(&newsum);
    sk_sum_clean(&oldsum);
    os_free(response);
    os_free(new_check_sum);
    os_free(old_check_sum);
    os_free(wazuhdb_query);
    return (0);

exit_fail:
    sk_sum_clean(&newsum);
    sk_sum_clean(&oldsum);
    os_free(response);
    os_free(new_check_sum);
    os_free(old_check_sum);
    os_free(wazuhdb_query);
    return (-1);
}
