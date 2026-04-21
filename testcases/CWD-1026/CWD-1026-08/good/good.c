#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

/* External type declarations (from cstring.h) */
struct cstring_t
{
	const char *p;
	size_t n;
};

/* External type declarations (from sys/locker.h) */
typedef void* locker_t;

/* External function declarations (from sys/locker.h) */
int locker_lock(locker_t *locker);
int locker_unlock(locker_t *locker);

/* External function declarations (from sys/atomic.h) */
int32_t atomic_decrement32(int32_t *v);
int32_t atomic_increment32(int32_t *v);

/* External function declarations (from cstring.h) */
long cstrtol(const struct cstring_t *s, char **endptr, int base);

/* External variable declaration (from sip-internal.h) */
struct sip_gc_t
{
	int32_t uac;
	int32_t uas;
	int32_t dialog;
	int32_t message;
	int32_t subscribe;
};
extern struct sip_gc_t s_gc;

/* Macros */
#ifndef NULL
#define NULL ((void*)0)
#endif

enum {
	DIALOG_ERALY = 0,
	DIALOG_CONFIRMED,
	DIALOG_TERMINATED,
};

/* darray stub (needed for sip_params_t, etc.) */
struct darray_t
{
	void *elements;
	int count;
	int capacity;
	int item_size;
	void (*free)(struct darray_t *arr);
	void *(*alloc)(struct darray_t *arr, size_t size);
};

/* list.h types and functions */
struct list_head
{
	struct list_head *next, *prev;
};

static inline void list_insert_after(struct list_head *item, struct list_head *head)
{
	struct list_head *prev, *next;
	prev = head;
	next = head->next;

	item->prev = prev;
	item->next = next;
	next->prev = item;
	prev->next = item;
}

static inline void list_remove(struct list_head *item)
{
	struct list_head *prev, *next;
	prev = item->prev;
	next = item->next;

	prev->next = next;
	next->prev = prev;

	item->prev = item->next = 0;
}

/* SIP header types (from sip-header.h) */
struct sip_param_t
{
	struct cstring_t name;
	struct cstring_t value;
};

struct sip_params_t
{
	struct darray_t arr;
};

struct sip_uri_t
{
	struct cstring_t scheme;
	struct cstring_t host;
	struct sip_params_t parameters;
	struct cstring_t transport;
	struct cstring_t method;
	struct cstring_t maddr;
	struct cstring_t user;
	int ttl;
	int lr;
	int rport;
	struct sip_params_t headers;
};

struct sip_contact_t
{
	struct sip_uri_t uri;
	struct cstring_t nickname;
	struct cstring_t tag;
	double q;
	int64_t expires;
	struct sip_params_t params;
};

struct sip_requestline_t
{
	struct cstring_t method;
	struct sip_uri_t uri;
};

struct sip_statusline_t
{
	int code;
	int verminor, vermajor;
	char protocol[64];
	struct cstring_t reason;
};

struct sip_cseq_t
{
	uint32_t id;
	struct cstring_t method;
};

struct sip_substate_t
{
	struct cstring_t state;
	struct cstring_t reason;
	uint32_t expires;
	uint32_t retry;
	struct sip_params_t params;
};

struct sip_vias_t
{
	struct darray_t arr;
};

struct sip_contacts_t
{
	struct darray_t arr;
};

struct sip_uris_t
{
	struct darray_t arr;
};

/* SIP message type (from sip-message.h) */
struct sip_message_t
{
	int mode;
	union
	{
		struct sip_requestline_t c;
		struct sip_statusline_t s;
	} u;

	struct sip_contact_t to;
	struct sip_contact_t from;
	struct sip_vias_t vias;
	struct cstring_t callid;
	struct sip_cseq_t cseq;
	int maxforwards;

	struct sip_contacts_t contacts;
	struct sip_uris_t routers;
	struct sip_uris_t record_routers;

	uint32_t rseq;
	struct cstring_t recv_info;
	struct cstring_t info_package;
	struct sip_contact_t referto;
	struct cstring_t event;
	struct cstring_t allow_events;
	struct sip_substate_t substate;
	struct sip_params_t headers;

	const void *payload;
	int size;

	struct
	{
		char* ptr;
		char* end;
	} ptr;
};

/* SIP dialog type (from sip-dialog.h) */
struct sip_dialog_t
{
	int state;

	struct cstring_t callid;
	struct
	{
		uint32_t id;
		uint32_t rseq;
		struct sip_contact_t uri;
		struct sip_uri_t target;
	} local, remote;
	int secure;

	struct sip_uris_t routers;

	void* session;
	void (*ondestroy)(void* param);
	void* ondestroyparam;
	struct list_head link;
	char* ptr;
	int32_t ref;
};

/* SIP UAS handler type */
struct sip_uas_handler_t
{
	void *send;
	void *onregister;
	void *oninvite;
	void *onack;
	void *onprack;
	void *onupdate;
	void *oninfo;
	void *onbye;
	void *oncancel;
	void *onsubscribe;
	void *onnotify;
	void *onpublish;
	void *onmessage;
	void *onrefer;
};

/* SIP agent type (from sip-internal.h) */
struct sip_agent_t
{
	int32_t ref;
	locker_t locker;

	struct list_head dialogs;
	struct list_head subscribes;

	struct list_head uac;
	struct list_head uas;
	struct sip_uas_handler_t handler;
};

/* SIP transport type */
struct sip_transport_t
{
	int type;
};

/* Forward declarations */
struct sip_uac_transaction_t;

/* SIP subscribe type (from sip-subscribe.h) */
struct sip_subscribe_t
{
	struct sip_dialog_t* dialog;
	int state;

	uint64_t expires;
	char event[128];

	struct list_head link;
	void* evtsession;
	int32_t ref;
	int newdiaolog;
};

/* SIP UAC transaction type (from sip-uac-transaction.h) */
typedef int (*sip_uac_onsubscribe)(void* param, const struct sip_message_t* reply, struct sip_uac_transaction_t* t, struct sip_subscribe_t* subscribe, int code, void** session);

struct sip_uac_transaction_t
{
	struct list_head link;
	locker_t locker;
	int32_t ref;

	struct sip_message_t* req;
	uint8_t data[4096];
	int size;
	int reliable;
	int retransmission;

	int status;
	int retries;
	int t2;
	void *timera;
	void *timerb;
	void *timerd;

	struct sip_agent_t* agent;
	struct sip_dialog_t* dialog;
	int (*onhandle)(struct sip_uac_transaction_t* t, int code);
	sip_uac_onsubscribe onsubscribe;
	void *oninvite;
	void *onreply;
	void* param;
	void *ondestroy;
	void* ondestroyparam;

	struct sip_transport_t transport;
	void* transportptr;
};

/* Function declarations from codebase */
struct sip_subscribe_t* sip_subscribe_create(const struct cstring_t* event);
int sip_subscribe_release(struct sip_subscribe_t* subscribe);
int sip_subscribe_addref(struct sip_subscribe_t* subscribe);
int sip_subscribe_remove(struct sip_agent_t* sip, struct sip_subscribe_t* subscribe);
struct sip_subscribe_t* sip_subscribe_find(struct sip_agent_t* sip, const struct cstring_t* callid, const struct cstring_t* local, const struct cstring_t* remote, const struct cstring_t *event);
struct sip_dialog_t* sip_dialog_internal_fetch(struct sip_agent_t* sip, const struct sip_message_t* msg, int uac, int* added);
int sip_dialog_release(struct sip_dialog_t* dialog);
int sip_dialog_remove(struct sip_agent_t* sip, struct sip_dialog_t* dialog);
const struct cstring_t* sip_message_get_header_by_name(const struct sip_message_t* msg, const char* name);

/* === Original content from bad.c === */

struct sip_subscribe_t* sip_subscribe_internal_fetch(struct sip_agent_t* sip, const struct sip_message_t* msg, const struct cstring_t* event, int uac, int* added)
{
	struct sip_subscribe_t* subscribe;

	*added = 0;
	locker_lock(&sip->locker);
    subscribe = sip_subscribe_find(sip, &msg->callid, uac ? &msg->from.tag : &msg->to.tag, uac ? &msg->to.tag : &msg->from.tag, event);
	if (NULL == subscribe)
	{
		subscribe = sip_subscribe_create(event);
		if (!subscribe)
		{
			locker_unlock(&sip->locker);
			return NULL; // exist
		}

		subscribe->dialog = sip_dialog_internal_fetch(sip, msg, uac, &subscribe->newdiaolog);
		if (!subscribe->dialog)
		{
			locker_unlock(&sip->locker);
			sip_subscribe_release(subscribe);
			return NULL; // exist
		}
		subscribe->dialog->state = DIALOG_CONFIRMED; // confirm dialog

		// link to tail (add ref later)
		list_insert_after(&subscribe->link, sip->subscribes.prev);
		*added = 1;
	}

	assert(subscribe->dialog);
	locker_unlock(&sip->locker);
	sip_subscribe_addref(subscribe); // for sip link dialog / fetch
	return subscribe;
}

int sip_subscribe_release(struct sip_subscribe_t* subscribe)
{
	if (!subscribe)
		return -1;

	assert(subscribe->ref > 0);
	if (0 != atomic_decrement32(&subscribe->ref))
		return 0;

	if (subscribe->dialog)
		sip_dialog_release(subscribe->dialog);
	free(subscribe);
	atomic_decrement32(&s_gc.subscribe);
	return 0;
}

int sip_subscribe_remove(struct sip_agent_t* sip, struct sip_subscribe_t* subscribe)
{
	// unlink dialog
	locker_lock(&sip->locker);
	if (subscribe->link.next == NULL)
	{
		// fix remove twice
		locker_unlock(&sip->locker);
		return 0;
	}

	//assert(1 == subscribe->ref);
	if (subscribe->newdiaolog)
	{
		subscribe->newdiaolog = 0;
		sip_dialog_remove(sip, subscribe->dialog);
	}
	list_remove(&subscribe->link);
	locker_unlock(&sip->locker);
	sip_subscribe_release(subscribe);
	return 0;
}

int sip_uac_subscribe_onreply(struct sip_uac_transaction_t* t, const struct sip_message_t* reply)
{
	int r;
	int added;
	const struct cstring_t *h;
	struct sip_subscribe_t* subscribe;

	if (reply->u.s.code < 200)
		return 0; // ignore

	r = 0;
	subscribe = NULL;
	if (200 <= reply->u.s.code && reply->u.s.code < 300)
	{
		subscribe = sip_subscribe_internal_fetch(t->agent, reply, &t->req->event, 1, &added);

		// call once only
		//if (added)
			r = t->onsubscribe(t->param, reply, t, subscribe, reply->u.s.code, &subscribe->evtsession);
	}
	else
	{
		r = t->onsubscribe(t->param, reply, t, NULL, reply->u.s.code, NULL);
	}

	if (subscribe)
	{
		// delete subscribe if expires is 0
		// h = sip_message_get_header_by_name(t->req, "Expires");
		// if (h && 0 == cstrtol(h, NULL, 10))
		// {
		// 	sip_subscribe_remove(t->agent, subscribe);
		// 	assert(1 == subscribe->ref);
		// }

		sip_subscribe_release(subscribe);
	}

	return r;
}
