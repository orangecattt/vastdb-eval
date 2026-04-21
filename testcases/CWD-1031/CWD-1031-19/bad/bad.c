#include <stddef.h>

#define __owur
#define OSSL_DEPRECATEDIN_1_1_0
#define OSSL_DEPRECATEDIN_3_0

#ifndef OPENSSL_FILE
#ifdef OPENSSL_NO_FILENAMES
#define OPENSSL_FILE ""
#define OPENSSL_LINE 0
#else
#define OPENSSL_FILE __FILE__
#define OPENSSL_LINE __LINE__
#endif
#endif

#ifndef OPENSSL_FUNC
#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 199901L
#define OPENSSL_FUNC __func__
#elif defined(__GNUC__) && __GNUC__ >= 2
#define OPENSSL_FUNC __FUNCTION__
#endif
#elif defined(_MSC_VER)
#define OPENSSL_FUNC __FUNCTION__
#endif

#ifndef OPENSSL_FUNC
#define OPENSSL_FUNC "(unknown function)"
#endif
#endif

#define STACK_OF(type) struct stack_st_##type

typedef struct asn1_string_st ASN1_INTEGER;
typedef struct asn1_string_st ASN1_ENUMERATED;
typedef struct asn1_string_st ASN1_BIT_STRING;
typedef struct asn1_string_st ASN1_OCTET_STRING;
typedef struct asn1_string_st ASN1_PRINTABLESTRING;
typedef struct asn1_string_st ASN1_T61STRING;
typedef struct asn1_string_st ASN1_IA5STRING;
typedef struct asn1_string_st ASN1_GENERALSTRING;
typedef struct asn1_string_st ASN1_UNIVERSALSTRING;
typedef struct asn1_string_st ASN1_BMPSTRING;
typedef struct asn1_string_st ASN1_UTCTIME;
typedef struct asn1_string_st ASN1_TIME;
typedef struct asn1_string_st ASN1_GENERALIZEDTIME;
typedef struct asn1_string_st ASN1_VISIBLESTRING;
typedef struct asn1_string_st ASN1_UTF8STRING;
typedef struct asn1_string_st ASN1_STRING;
typedef int ASN1_BOOLEAN;
typedef int ASN1_NULL;

typedef struct asn1_type_st ASN1_TYPE;
typedef struct asn1_object_st ASN1_OBJECT;
typedef struct ASN1_ITEM_st ASN1_ITEM;
typedef struct ossl_lib_ctx_st OSSL_LIB_CTX;
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
typedef struct evp_md_st EVP_MD;
typedef struct evp_pkey_st EVP_PKEY;
typedef struct engine_st ENGINE;
typedef struct hmac_ctx_st HMAC_CTX;
typedef struct x509_st X509;
typedef struct X509_algor_st X509_ALGOR;
typedef struct X509_crl_st X509_CRL;
typedef struct X509_name_st X509_NAME;
typedef struct x509_attributes_st X509_ATTRIBUTE;
typedef struct X509_sig_st X509_SIG;
typedef struct PKCS12_MAC_DATA_st PKCS12_MAC_DATA;
typedef struct PKCS12_st PKCS12;
typedef struct PKCS12_SAFEBAG_st PKCS12_SAFEBAG;
typedef struct pkcs12_bag_st PKCS12_BAGS;

struct asn1_string_st {
    int length;
    int type;
    unsigned char *data;
    /*
     * The value of the following field depends on the type being held.  It
     * is mostly being used for BIT_STRING so if the input data has a
     * non-zero 'unused bits' value, it will be handled correctly
     */
    long flags;
};

#define ASN1_ITEM_rptr(ref) (ref##_it())

typedef struct ASN1_VALUE_st ASN1_VALUE;

struct asn1_type_st {
    int type;
    union {
        char *ptr;
        ASN1_BOOLEAN boolean;
        ASN1_STRING *asn1_string;
        ASN1_OBJECT *object;
        ASN1_INTEGER *integer;
        ASN1_ENUMERATED *enumerated;
        ASN1_BIT_STRING *bit_string;
        ASN1_OCTET_STRING *octet_string;
        ASN1_PRINTABLESTRING *printablestring;
        ASN1_T61STRING *t61string;
        ASN1_IA5STRING *ia5string;
        ASN1_GENERALSTRING *generalstring;
        ASN1_BMPSTRING *bmpstring;
        ASN1_UNIVERSALSTRING *universalstring;
        ASN1_UTCTIME *utctime;
        ASN1_GENERALIZEDTIME *generalizedtime;
        ASN1_VISIBLESTRING *visiblestring;
        ASN1_UTF8STRING *utf8string;
        /*
         * set and sequence are left complete and still contain the set or
         * sequence bytes
         */
        ASN1_STRING *set;
        ASN1_STRING *sequence;
        ASN1_VALUE *asn1_value;
    } value;
};

struct X509_algor_st {
    ASN1_OBJECT *algorithm;
    ASN1_TYPE *parameter;
} /* X509_ALGOR */;

typedef struct PBKDF2PARAM_st {
    /* Usually OCTET STRING but could be anything */
    ASN1_TYPE *salt;
    ASN1_INTEGER *iter;
    ASN1_INTEGER *keylength;
    X509_ALGOR *prf;
} PBKDF2PARAM;

typedef struct {
    X509_ALGOR *keyDerivationFunc;
    X509_ALGOR *messageAuthScheme;
} PBMAC1PARAM;

typedef struct PKCS7_CTX_st {
    OSSL_LIB_CTX *libctx;
    char *propq;
} PKCS7_CTX;

typedef struct pkcs7_issuer_and_serial_st {
    X509_NAME *issuer;
    ASN1_INTEGER *serial;
} PKCS7_ISSUER_AND_SERIAL;

typedef struct pkcs7_signer_info_st {
    ASN1_INTEGER *version; /* version 1 */
    PKCS7_ISSUER_AND_SERIAL *issuer_and_serial;
    X509_ALGOR *digest_alg;
    STACK_OF(X509_ATTRIBUTE) *auth_attr; /* [ 0 ] */
    X509_ALGOR *digest_enc_alg; /* confusing name, actually used for signing */
    ASN1_OCTET_STRING *enc_digest; /* confusing name, actually signature */
    STACK_OF(X509_ATTRIBUTE) *unauth_attr; /* [ 1 ] */
    /* The private key to sign with */
    EVP_PKEY *pkey;
    const PKCS7_CTX *ctx;
} PKCS7_SIGNER_INFO;

typedef struct pkcs7_recip_info_st {
    ASN1_INTEGER *version; /* version 0 */
    PKCS7_ISSUER_AND_SERIAL *issuer_and_serial;
    X509_ALGOR *key_enc_algor;
    ASN1_OCTET_STRING *enc_key;
    X509 *cert; /* get the pub-key from this */
    const PKCS7_CTX *ctx;
} PKCS7_RECIP_INFO;

typedef struct pkcs7_signed_st {
    ASN1_INTEGER *version; /* version 1 */
    STACK_OF(X509_ALGOR) *md_algs; /* md used */
    STACK_OF(X509) *cert; /* [ 0 ] */ /* name should be 'certificates' */
    STACK_OF(X509_CRL) *crl; /* [ 1 ] */ /* name should be 'crls' */
    STACK_OF(PKCS7_SIGNER_INFO) *signer_info;
    struct pkcs7_st *contents;
} PKCS7_SIGNED;

typedef struct pkcs7_enc_content_st {
    ASN1_OBJECT *content_type;
    X509_ALGOR *algorithm;
    ASN1_OCTET_STRING *enc_data; /* [ 0 ] */
    const EVP_CIPHER *cipher;
    const PKCS7_CTX *ctx;
} PKCS7_ENC_CONTENT;

typedef struct pkcs7_enveloped_st {
    ASN1_INTEGER *version; /* version 0 */
    STACK_OF(PKCS7_RECIP_INFO) *recipientinfo;
    PKCS7_ENC_CONTENT *enc_data;
} PKCS7_ENVELOPE;

typedef struct pkcs7_signedandenveloped_st {
    ASN1_INTEGER *version; /* version 1 */
    STACK_OF(X509_ALGOR) *md_algs; /* md used */
    STACK_OF(X509) *cert; /* [ 0 ] */ /* name should be 'certificates' */
    STACK_OF(X509_CRL) *crl; /* [ 1 ] */ /* name should be 'crls' */
    STACK_OF(PKCS7_SIGNER_INFO) *signer_info;
    PKCS7_ENC_CONTENT *enc_data;
    STACK_OF(PKCS7_RECIP_INFO) *recipientinfo;
} PKCS7_SIGN_ENVELOPE;

typedef struct pkcs7_digest_st {
    ASN1_INTEGER *version; /* version 0 */
    X509_ALGOR *md; /* md used */
    struct pkcs7_st *contents;
    ASN1_OCTET_STRING *digest;
} PKCS7_DIGEST;

typedef struct pkcs7_encrypted_st {
    ASN1_INTEGER *version; /* version 0 */
    PKCS7_ENC_CONTENT *enc_data;
} PKCS7_ENCRYPT;

typedef struct pkcs7_st {
    /*
     * The following is non NULL if it contains ASN1 encoding of this
     * structure
     */
    unsigned char *asn1;
    long length;
#define PKCS7_S_HEADER 0
#define PKCS7_S_BODY 1
#define PKCS7_S_TAIL 2
    int state; /* used during processing */
    int detached;
    ASN1_OBJECT *type;
    /* content as defined by the type */
    /*
     * all encryption/message digests are applied to the 'contents', leaving
     * out the 'type' field.
     */
    union {
        char *ptr;
        /* NID_pkcs7_data */
        ASN1_OCTET_STRING *data;
        /* NID_pkcs7_signed */
        PKCS7_SIGNED *sign; /* field name 'signed' would clash with C keyword */
        /* NID_pkcs7_enveloped */
        PKCS7_ENVELOPE *enveloped;
        /* NID_pkcs7_signedAndEnveloped */
        PKCS7_SIGN_ENVELOPE *signed_and_enveloped;
        /* NID_pkcs7_digest */
        PKCS7_DIGEST *digest;
        /* NID_pkcs7_encrypted */
        PKCS7_ENCRYPT *encrypted;
        /* Anything else */
        ASN1_TYPE *other;
    } d;
    PKCS7_CTX ctx;
} PKCS7;

struct X509_sig_st {
    X509_ALGOR *algor;
    ASN1_OCTET_STRING *digest;
};

struct PKCS12_MAC_DATA_st {
    X509_SIG *dinfo;
    ASN1_OCTET_STRING *salt;
    ASN1_INTEGER *iter; /* defaults to 1 */
};

struct PKCS12_st {
    ASN1_INTEGER *version;
    PKCS12_MAC_DATA *mac;
    PKCS7 *authsafes;
};

struct PKCS12_SAFEBAG_st {
    ASN1_OBJECT *type;
    union {
        struct pkcs12_bag_st *bag; /* secret, crl and certbag */
        struct pkcs8_priv_key_info_st *keybag; /* keybag */
        X509_SIG *shkeybag; /* shrouded key bag */
        STACK_OF(PKCS12_SAFEBAG) *safes;
        ASN1_TYPE *other;
    } value;
    STACK_OF(X509_ATTRIBUTE) *attrib;
};

struct pkcs12_bag_st {
    ASN1_OBJECT *type;
    union {
        ASN1_OCTET_STRING *x509cert;
        ASN1_OCTET_STRING *x509crl;
        ASN1_OCTET_STRING *octet;
        ASN1_IA5STRING *sdsicert;
        ASN1_TYPE *other; /* Secret or other bag */
    } value;
};

#define EVP_MAX_MD_SIZE 64 /* longest known is SHA512 */

#define NID_undef                       0
#define NID_pbmac1              162
#define NID_pkcs7_data          21
#define NID_hmacWithSHA1                163
#define NID_id_GostR3411_94             809
#define NID_id_GostR3411_2012_256               982
#define NID_id_GostR3411_2012_512               983

#define PKCS12_MAC_ID 3

#define TK26_MAC_KEY_LEN 32

#define ERR_LIB_PKCS12 35
#define ERR_RFLAGS_OFFSET 18L
#define ERR_RFLAGS_MASK 0x1F
#define ERR_REASON_MASK 0X7FFFFF
#define ERR_RFLAG_FATAL (0x1 << ERR_RFLAGS_OFFSET)
#define ERR_RFLAG_COMMON (0x2 << ERR_RFLAGS_OFFSET)
#define ERR_R_FATAL (ERR_RFLAG_FATAL | ERR_RFLAG_COMMON)
#define ERR_R_INTERNAL_ERROR (259 | ERR_R_FATAL)
#define ERR_R_UNSUPPORTED (268 | ERR_RFLAG_COMMON)
#define ERR_R_FETCH_FAILED (269 | ERR_RFLAG_COMMON)

#define PKCS12_R_CONTENT_TYPE_NOT_DATA 121
#define PKCS12_R_DECODE_ERROR 101
#define PKCS12_R_KEY_GEN_ERROR 107
#define PKCS12_R_MAC_ABSENT 108
#define PKCS12_R_MAC_GENERATION_ERROR 109
#define PKCS12_R_UNKNOWN_DIGEST_ALGORITHM 118

#define PKCS7_type_is_data(a) (OBJ_obj2nid((a)->type) == NID_pkcs7_data)

#define EVP_get_digestbynid(a) EVP_get_digestbyname(OBJ_nid2sn(a))

void ERR_new(void);
void ERR_set_debug(const char *file, int line, const char *func);
void ERR_set_error(int lib, int reason, const char *fmt, ...);

/* Main error raising functions */
#define ERR_raise(lib, reason) ERR_raise_data((lib), (reason), NULL)
#define ERR_raise_data                                           \
    (ERR_new(),                                                  \
        ERR_set_debug(OPENSSL_FILE, OPENSSL_LINE, OPENSSL_FUNC), \
        ERR_set_error)

int ERR_set_mark(void);
int ERR_pop_to_mark(void);
int ERR_clear_last_mark(void);

extern const ASN1_ITEM *PBKDF2PARAM_it(void);
extern const ASN1_ITEM *PBMAC1PARAM_it(void);

ASN1_OBJECT *OBJ_nid2obj(int n);
const char *OBJ_nid2sn(int n);
int OBJ_obj2nid(const ASN1_OBJECT *o);
int OBJ_obj2txt(char *buf, int buf_len, const ASN1_OBJECT *a, int no_name);

void *ASN1_TYPE_unpack_sequence(const ASN1_ITEM *it, const ASN1_TYPE *t);
int ASN1_STRING_length(const ASN1_STRING *x);
const unsigned char *ASN1_STRING_get0_data(const ASN1_STRING *x);
long ASN1_INTEGER_get(const ASN1_INTEGER *a);

void X509_ALGOR_get0(const ASN1_OBJECT **paobj, int *pptype,
    const void **ppval, const X509_ALGOR *algor);
void X509_SIG_get0(const X509_SIG *sig, const X509_ALGOR **palg,
    const ASN1_OCTET_STRING **pdigest);

int EVP_MD_get_type(const EVP_MD *md);
int EVP_MD_get_size(const EVP_MD *md);
__owur EVP_MD *EVP_MD_fetch(OSSL_LIB_CTX *ctx, const char *algorithm,
    const char *properties);
void EVP_MD_free(EVP_MD *md);
const EVP_MD *EVP_get_digestbyname(const char *name);

OSSL_DEPRECATEDIN_3_0 HMAC_CTX *HMAC_CTX_new(void);
OSSL_DEPRECATEDIN_3_0 void HMAC_CTX_free(HMAC_CTX *ctx);
OSSL_DEPRECATEDIN_3_0 int HMAC_Init_ex(HMAC_CTX *ctx, const void *key, int len,
    const EVP_MD *md, ENGINE *impl);
OSSL_DEPRECATEDIN_3_0 int HMAC_Update(HMAC_CTX *ctx, const unsigned char *data,
    size_t len);
OSSL_DEPRECATEDIN_3_0 int HMAC_Final(HMAC_CTX *ctx, unsigned char *md,
    unsigned int *len);

void OPENSSL_cleanse(void *ptr, size_t len);
int CRYPTO_memcmp(const void *in_a, const void *in_b, size_t len);

char *ossl_safe_getenv(const char *name);
int ossl_hmac2mdnid(int hmac_nid);

PBKDF2PARAM *PBMAC1_get1_pbkdf2_param(const X509_ALGOR *macalg);
void PBKDF2PARAM_free(PBKDF2PARAM *a);
void PBMAC1PARAM_free(PBMAC1PARAM *a);

int PKCS5_PBKDF2_HMAC(const char *pass, int passlen,
    const unsigned char *salt, int saltlen, int iter,
    const EVP_MD *digest, int keylen, unsigned char *out);
int PKCS12_key_gen_utf8_ex(const char *pass, int passlen, unsigned char *salt,
    int saltlen, int id, int iter, int n,
    unsigned char *out, const EVP_MD *md_type,
    OSSL_LIB_CTX *ctx, const char *propq);

static int pkcs12_gen_gost_mac_key(const char *pass, int passlen,
    const unsigned char *salt, int saltlen,
    int iter, int keylen, unsigned char *key,
    const EVP_MD *digest);

static int PBMAC1_PBKDF2_HMAC(OSSL_LIB_CTX *ctx, const char *propq,
    const char *pass, int passlen,
    const X509_ALGOR *macalg, unsigned char *key)
{
    PBKDF2PARAM *pbkdf2_param = NULL;
    const ASN1_OBJECT *kdf_hmac_oid;
    int kdf_hmac_nid;
    int ret = -1;
    int keylen = 0;
    EVP_MD *kdf_md = NULL;
    const ASN1_OCTET_STRING *pbkdf2_salt = NULL;

    pbkdf2_param = PBMAC1_get1_pbkdf2_param(macalg);
    if (pbkdf2_param == NULL) {
        ERR_raise(ERR_LIB_PKCS12, ERR_R_UNSUPPORTED);
        goto err;
    }
    keylen = ASN1_INTEGER_get(pbkdf2_param->keylength);
    pbkdf2_salt = pbkdf2_param->salt->value.octet_string;

    if (pbkdf2_param->prf == NULL) {
        kdf_hmac_nid = NID_hmacWithSHA1;
    } else {
        X509_ALGOR_get0(&kdf_hmac_oid, NULL, NULL, pbkdf2_param->prf);
        kdf_hmac_nid = OBJ_obj2nid(kdf_hmac_oid);
    }

    kdf_md = EVP_MD_fetch(ctx, OBJ_nid2sn(ossl_hmac2mdnid(kdf_hmac_nid)), propq);
    if (kdf_md == NULL) {
        ERR_raise(ERR_LIB_PKCS12, ERR_R_FETCH_FAILED);
        goto err;
    }

    if (PKCS5_PBKDF2_HMAC(pass, passlen, pbkdf2_salt->data, pbkdf2_salt->length,
            ASN1_INTEGER_get(pbkdf2_param->iter), kdf_md, keylen, key)
        <= 0) {
        ERR_raise(ERR_LIB_PKCS12, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    ret = keylen;

err:
    EVP_MD_free(kdf_md);
    PBKDF2PARAM_free(pbkdf2_param);

    return ret;
}

static int pkcs12_gen_mac(PKCS12 *p12, const char *pass, int passlen,
    unsigned char *mac, unsigned int *maclen,
    int pbmac1_md_nid, int pbmac1_kdf_nid,
    int (*pkcs12_key_gen)(const char *pass, int passlen,
        unsigned char *salt, int slen,
        int id, int iter, int n,
        unsigned char *out,
        const EVP_MD *md_type))
{
    int ret = 0;
    const EVP_MD *md;
    EVP_MD *md_fetch;
    HMAC_CTX *hmac = NULL;
    unsigned char key[EVP_MAX_MD_SIZE], *salt;
    int saltlen, iter;
    char md_name[80];
    int keylen = 0;
    int md_nid = NID_undef;
    const X509_ALGOR *macalg;
    const ASN1_OBJECT *macoid;

    if (!PKCS7_type_is_data(p12->authsafes)) {
        ERR_raise(ERR_LIB_PKCS12, PKCS12_R_CONTENT_TYPE_NOT_DATA);
        return 0;
    }

    if (p12->authsafes->d.data == NULL) {
        ERR_raise(ERR_LIB_PKCS12, PKCS12_R_DECODE_ERROR);
        return 0;
    }

    salt = p12->mac->salt->data;
    saltlen = p12->mac->salt->length;
    if (p12->mac->iter == NULL)
        iter = 1;
    else
        iter = ASN1_INTEGER_get(p12->mac->iter);
    X509_SIG_get0(p12->mac->dinfo, &macalg, NULL);
    X509_ALGOR_get0(&macoid, NULL, NULL, macalg);
    if (OBJ_obj2nid(macoid) == NID_pbmac1) {
        if (OBJ_obj2txt(md_name, sizeof(md_name), OBJ_nid2obj(pbmac1_md_nid), 0) < 0)
            return 0;
    } else {
        if (OBJ_obj2txt(md_name, sizeof(md_name), macoid, 0) < 0)
            return 0;
    }
    (void)ERR_set_mark();
    md = md_fetch = EVP_MD_fetch(p12->authsafes->ctx.libctx, md_name,
        p12->authsafes->ctx.propq);
    if (md == NULL)
        md = EVP_get_digestbynid(OBJ_obj2nid(macoid));

    if (md == NULL) {
        (void)ERR_clear_last_mark();
        ERR_raise(ERR_LIB_PKCS12, PKCS12_R_UNKNOWN_DIGEST_ALGORITHM);
        return 0;
    }
    (void)ERR_pop_to_mark();

    keylen = EVP_MD_get_size(md);
    md_nid = EVP_MD_get_type(md);
    if (keylen <= 0)
        goto err;

    /* For PBMAC1 we use a special keygen callback if not provided (e.g. on verification) */
    if (pbmac1_md_nid != NID_undef && pkcs12_key_gen == NULL) {
        keylen = PBMAC1_PBKDF2_HMAC(p12->authsafes->ctx.libctx, p12->authsafes->ctx.propq,
            pass, passlen, macalg, key);
        if (keylen < 0)
            goto err;
    } else if ((md_nid == NID_id_GostR3411_94
                   || md_nid == NID_id_GostR3411_2012_256
                   || md_nid == NID_id_GostR3411_2012_512)
        && ossl_safe_getenv("LEGACY_GOST_PKCS12") == NULL) {
        keylen = TK26_MAC_KEY_LEN;
        if (!pkcs12_gen_gost_mac_key(pass, passlen, salt, saltlen, iter,
                keylen, key, md)) {
            ERR_raise(ERR_LIB_PKCS12, PKCS12_R_KEY_GEN_ERROR);
            goto err;
        }
    } else {
        EVP_MD *hmac_md = (EVP_MD *)md;
        int fetched = 0;

        if (pbmac1_kdf_nid != NID_undef) {
            char hmac_md_name[128];

            if (OBJ_obj2txt(hmac_md_name, sizeof(hmac_md_name), OBJ_nid2obj(pbmac1_kdf_nid), 0) < 0)
                goto err;
            hmac_md = EVP_MD_fetch(NULL, hmac_md_name, NULL);
            if (hmac_md == NULL)
                goto err;
            fetched = 1;
        }
        if (pkcs12_key_gen != NULL) {
            int res = (*pkcs12_key_gen)(pass, passlen, salt, saltlen, PKCS12_MAC_ID,
                iter, keylen, key, hmac_md);

            if (fetched)
                EVP_MD_free(hmac_md);
            if (res != 1) {
                ERR_raise(ERR_LIB_PKCS12, PKCS12_R_KEY_GEN_ERROR);
                goto err;
            }
        } else {
            if (fetched)
                EVP_MD_free(hmac_md);
            /* Default to UTF-8 password */
            if (!PKCS12_key_gen_utf8_ex(pass, passlen, salt, saltlen, PKCS12_MAC_ID,
                    iter, keylen, key, md,
                    p12->authsafes->ctx.libctx, p12->authsafes->ctx.propq)) {
                ERR_raise(ERR_LIB_PKCS12, PKCS12_R_KEY_GEN_ERROR);
                goto err;
            }
        }
    }
    if ((hmac = HMAC_CTX_new()) == NULL
        || !HMAC_Init_ex(hmac, key, keylen, md, NULL)
        || !HMAC_Update(hmac, p12->authsafes->d.data->data,
            p12->authsafes->d.data->length)
        || !HMAC_Final(hmac, mac, maclen)) {
        goto err;
    }
    ret = 1;

err:
    OPENSSL_cleanse(key, sizeof(key));
    HMAC_CTX_free(hmac);
    EVP_MD_free(md_fetch);
    return ret;
}

int PKCS12_verify_mac(PKCS12 *p12, const char *pass, int passlen)
{
    unsigned char mac[EVP_MAX_MD_SIZE];
    unsigned int maclen;
    const ASN1_OCTET_STRING *macoct;
    const X509_ALGOR *macalg;
    const ASN1_OBJECT *macoid;

    if (p12->mac == NULL) {
        ERR_raise(ERR_LIB_PKCS12, PKCS12_R_MAC_ABSENT);
        return 0;
    }

    X509_SIG_get0(p12->mac->dinfo, &macalg, NULL);
    X509_ALGOR_get0(&macoid, NULL, NULL, macalg);
    if (OBJ_obj2nid(macoid) == NID_pbmac1) {
        PBMAC1PARAM *param = NULL;
        const ASN1_OBJECT *hmac_oid;
        int md_nid = NID_undef;

        param = ASN1_TYPE_unpack_sequence(ASN1_ITEM_rptr(PBMAC1PARAM), macalg->parameter);
        if (param == NULL) {
            ERR_raise(ERR_LIB_PKCS12, ERR_R_UNSUPPORTED);
            return 0;
        }
        X509_ALGOR_get0(&hmac_oid, NULL, NULL, param->messageAuthScheme);
        md_nid = ossl_hmac2mdnid(OBJ_obj2nid(hmac_oid));

        if (!pkcs12_gen_mac(p12, pass, passlen, mac, &maclen, md_nid, NID_undef, NULL)) {
            ERR_raise(ERR_LIB_PKCS12, PKCS12_R_MAC_GENERATION_ERROR);
            PBMAC1PARAM_free(param);
            return 0;
        }
        PBMAC1PARAM_free(param);
    } else {
        if (!pkcs12_gen_mac(p12, pass, passlen, mac, &maclen, NID_undef, NID_undef, NULL)) {
            ERR_raise(ERR_LIB_PKCS12, PKCS12_R_MAC_GENERATION_ERROR);
            return 0;
        }
    }
    X509_SIG_get0(p12->mac->dinfo, NULL, &macoct);
    if ((maclen != (unsigned int)ASN1_STRING_length(macoct))
        || CRYPTO_memcmp(mac, ASN1_STRING_get0_data(macoct), maclen) != 0)
        return 0;

    return 1;
}
