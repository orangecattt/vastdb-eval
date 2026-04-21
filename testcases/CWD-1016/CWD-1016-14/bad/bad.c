#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define OPENSSL_FILE __FILE__
#define OPENSSL_LINE __LINE__
#define OPENSSL_FUNC __func__

typedef int ASN1_BOOLEAN;
typedef struct ASN1_VALUE_st ASN1_VALUE;
typedef struct asn1_object_st ASN1_OBJECT;
typedef struct asn1_string_st ASN1_STRING;
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
typedef struct asn1_type_st ASN1_TYPE;
typedef struct x509_algor_st X509_ALGOR;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct ASN1_ITEM_st ASN1_ITEM;

struct asn1_string_st {
    int length;
    int type;
    unsigned char *data;
    long flags;
};

#define V_ASN1_SEQUENCE 16

struct ASN1_VALUE_st {
    int dummy;
};

struct asn1_object_st {
    int nid;
    int length;
    const unsigned char *data;
    const char *sn;
    const char *ln;
    int flags;
};

struct x509_algor_st {
    ASN1_OBJECT *algorithm;
    ASN1_TYPE *parameter;
};

struct ASN1_ITEM_st {
    char itype;
    long utype;
    const void *templates;
    long tcount;
    const void *funcs;
    long size;
    const char *sname;
};

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
        ASN1_STRING *set;
        ASN1_STRING *sequence;
        ASN1_VALUE *asn1_value;
    } value;
};

#define EVP_MAX_IV_LENGTH 16
#define EVP_MAX_BLOCK_LENGTH 16
#define EVP_CIPH_FLAG_CUSTOM_ASN1 0x1000000
#define EVP_CIPH_WRAP_MODE 0x10000
#define EVP_CIPH_GCM_MODE 0x10001
#define EVP_CIPH_CCM_MODE 0x10002
#define EVP_CIPH_XTS_MODE 0x10003
#define EVP_CIPH_OCB_MODE 0x10004

#define ERR_LIB_ASN1 13
#define ERR_LIB_EVP 6

#define ASN1_R_DATA_IS_WRONG 109

#define EVP_R_CIPHER_PARAMETER_ERROR 122
#define EVP_R_UNSUPPORTED_CIPHER 107

#define ERR_raise(lib, reason) ((void)0)

struct evp_cipher_st {
    int nid;
    size_t block_size;
    size_t key_len;
    size_t iv_len;
    unsigned long flags;
    void *prov;
    void *init;
    void *cleanup;
    void *do_cipher;
    void *set_asn1_parameters;
    int (*get_asn1_parameters)(EVP_CIPHER_CTX *c, ASN1_TYPE *type);
    void *ctrl;
    size_t ctx_size;
    void *update;
};

struct evp_cipher_ctx_st {
    const EVP_CIPHER *cipher;
    void *engine;
    int encrypt;
    int buf_len;
    unsigned char oiv[EVP_MAX_IV_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char buf[EVP_MAX_BLOCK_LENGTH];
    int num;
    void *app_data;
    int key_len;
    int iv_len;
    unsigned long flags;
    void *cipher_data;
    int final_used;
    int block_mask;
    unsigned char final[EVP_MAX_BLOCK_LENGTH];
    size_t numpipes;
    void *algctx;
    EVP_CIPHER *fetched_cipher;
};

typedef struct {
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned int iv_len;
    unsigned int tag_len;
} evp_cipher_aead_asn1_params;

typedef struct {
    ASN1_OCTET_STRING *oct;
    int32_t num;
} asn1_oct_int;

#define ASN1_ITEM_rptr(ref) (ref##_it())

#define M_ASN1_free_of(x, type) ASN1_item_free((ASN1_VALUE *)(x), ASN1_ITEM_rptr(type))

int ASN1_STRING_length(const ASN1_STRING *x);
const unsigned char *ASN1_STRING_get0_data(const ASN1_STRING *x);
void *ASN1_TYPE_unpack_sequence(const ASN1_ITEM *it, const ASN1_TYPE *t);
ASN1_TYPE *ASN1_TYPE_pack_sequence(const ASN1_ITEM *it, void *s, ASN1_TYPE **t);
void *ASN1_item_new(const ASN1_ITEM *it);
void ASN1_item_free(ASN1_VALUE *val, const ASN1_ITEM *it);

unsigned long EVP_CIPHER_get_flags(const EVP_CIPHER *cipher);
int EVP_CIPHER_get_mode(const EVP_CIPHER *cipher);
int EVP_CIPHER_get_asn1_iv(EVP_CIPHER_CTX *c, ASN1_TYPE *type);
int EVP_CIPHER_CTX_set_algor_params(EVP_CIPHER_CTX *ctx, const X509_ALGOR *alg);

extern const ASN1_ITEM *asn1_oct_int_it(void);

static int asn1_type_get_int_oct(ASN1_OCTET_STRING *oct, int32_t anum,
    long *num, unsigned char *data, int max_len)
{
    int ret = ASN1_STRING_length(oct), n;

    if (num != NULL)
        *num = anum;

    if (max_len > ret)
        n = ret;
    else
        n = max_len;

    if (data != NULL)
        memcpy(data, ASN1_STRING_get0_data(oct), n);

    return ret;
}

int ossl_asn1_type_get_octetstring_int(const ASN1_TYPE *a, long *num,
    unsigned char *data, int max_len)
{
    asn1_oct_int *atmp = NULL;
    int ret = -1;

    if ((a->type != V_ASN1_SEQUENCE) || (a->value.sequence == NULL))
        goto err;

    atmp = ASN1_TYPE_unpack_sequence(ASN1_ITEM_rptr(asn1_oct_int), a);

    if (atmp == NULL)
        goto err;

    ret = asn1_type_get_int_oct(atmp->oct, atmp->num, num, data, max_len);

    if (ret == -1) {
    err:
        ERR_raise(ERR_LIB_ASN1, ASN1_R_DATA_IS_WRONG);
    }
    M_ASN1_free_of(atmp, asn1_oct_int);
    return ret;
}

int evp_cipher_get_asn1_aead_params(EVP_CIPHER_CTX *c, ASN1_TYPE *type,
    evp_cipher_aead_asn1_params *asn1_params)
{
    int i = 0;
    long tl;
    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (type == NULL || asn1_params == NULL)
        return 0;

    i = ossl_asn1_type_get_octetstring_int(type, &tl, NULL, EVP_MAX_IV_LENGTH);
    if (i <= 0)
        return -1;
    ossl_asn1_type_get_octetstring_int(type, &tl, iv, i);

    memcpy(asn1_params->iv, iv, i);
    asn1_params->iv_len = i;

    return i;
}

int evp_cipher_asn1_to_param_ex(EVP_CIPHER_CTX *c, ASN1_TYPE *type,
    evp_cipher_aead_asn1_params *asn1_params)
{
    int ret = -1; /* Assume the worst */
    const EVP_CIPHER *cipher;

    if (c == NULL || c->cipher == NULL)
        goto err;

    cipher = c->cipher;
    /*
     * For legacy implementations, we detect custom AlgorithmIdentifier
     * parameter handling by checking if there the function pointer
     * cipher->get_asn1_parameters is set.  We know that this pointer
     * is NULL for provided implementations.
     *
     * Otherwise, for any implementation, we check the flag
     * EVP_CIPH_FLAG_CUSTOM_ASN1.  If it isn't set, we apply
     * default AI parameter creation.
     *
     * Otherwise, for provided implementations, we get the AI parameter
     * in DER encoded form from the implementation by requesting the
     * appropriate OSSL_PARAM and converting the result to a ASN1_TYPE.
     *
     * If none of the above applies, this operation is unsupported.
     */
    if (cipher->get_asn1_parameters != NULL) {
        ret = cipher->get_asn1_parameters(c, type);
    } else if ((EVP_CIPHER_get_flags(cipher) & EVP_CIPH_FLAG_CUSTOM_ASN1) == 0) {
        switch (EVP_CIPHER_get_mode(cipher)) {
        case EVP_CIPH_WRAP_MODE:
            ret = 1;
            break;

        case EVP_CIPH_GCM_MODE:
            ret = evp_cipher_get_asn1_aead_params(c, type, asn1_params);
            break;

        case EVP_CIPH_CCM_MODE:
        case EVP_CIPH_XTS_MODE:
        case EVP_CIPH_OCB_MODE:
            ret = -2;
            break;

        default:
            ret = EVP_CIPHER_get_asn1_iv(c, type) >= 0 ? 1 : -1;
        }
    } else if (cipher->prov != NULL) {
        /* We cheat, there's no need for an object ID for this use */
        X509_ALGOR alg;

        alg.algorithm = NULL;
        alg.parameter = type;

        ret = EVP_CIPHER_CTX_set_algor_params(c, &alg);
    } else {
        ret = -2;
    }

err:
    if (ret == -2)
        ERR_raise(ERR_LIB_EVP, EVP_R_UNSUPPORTED_CIPHER);
    else if (ret <= 0)
        ERR_raise(ERR_LIB_EVP, EVP_R_CIPHER_PARAMETER_ERROR);
    if (ret < -1)
        ret = -1;
    return ret;
}
