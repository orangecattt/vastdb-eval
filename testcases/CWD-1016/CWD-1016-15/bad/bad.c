#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef OPENSSL_FILE
# define OPENSSL_FILE __FILE__
# define OPENSSL_LINE __LINE__
#endif
#ifndef OPENSSL_FUNC
# define OPENSSL_FUNC __func__
#endif

#ifndef __owur
# define __owur
#endif

#ifndef OSSL_CRYPTO_ALLOC
# define OSSL_CRYPTO_ALLOC
#endif

typedef struct ossl_lib_ctx_st OSSL_LIB_CTX;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct evp_md_ctx_st EVP_MD_CTX;
typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;
typedef struct evp_pkey_st EVP_PKEY;
typedef struct evp_md_st EVP_MD;
typedef struct X509_algor_st X509_ALGOR;
typedef struct asn1_object_st ASN1_OBJECT;

struct asn1_string_st {
    int length;
    int type;
    unsigned char *data;
    long flags;
};

typedef struct asn1_string_st ASN1_INTEGER;
typedef struct asn1_string_st ASN1_OCTET_STRING;
typedef struct asn1_string_st ASN1_STRING;
typedef struct asn1_string_st ASN1_BIT_STRING;
typedef struct asn1_type_st ASN1_TYPE;
typedef int ASN1_BOOLEAN;

#define OSSL_MAX_NAME_SIZE 50

struct asn1_type_st {
    int type;
    union {
        char *ptr;
        ASN1_BOOLEAN boolean;
        ASN1_STRING *asn1_string;
        ASN1_OBJECT *object;
        ASN1_INTEGER *integer;
        ASN1_OCTET_STRING *octet_string;
        ASN1_BIT_STRING *bit_string;
        void *other;
    } value;
};

struct X509_algor_st {
    ASN1_OBJECT *algorithm;
    ASN1_TYPE *parameter;
};

typedef struct ASN1_ITEM_st ASN1_ITEM;
extern const ASN1_ITEM *X509_ALGOR_it(void);
#define ASN1_ITEM_rptr(ref) (ref##_it())

#define NID_id_alg_PWRI_KEK 893

#define ERR_LIB_EVP  6
#define ERR_LIB_CMS  46
#define ERR_RFLAG_COMMON (0x1000000)
#define ERR_R_EVP_LIB (ERR_LIB_EVP | ERR_RFLAG_COMMON)

void ERR_new(void);
void ERR_set_debug(const char *file, int line, const char *func);
void ERR_set_error(int lib, int reason, const char *fmt, ...);
#define ERR_raise(lib, reason) ERR_raise_data((lib),(reason),NULL)
#define ERR_raise_data                                         \
    (ERR_new(),                                                 \
     ERR_set_debug(OPENSSL_FILE,OPENSSL_LINE,OPENSSL_FUNC),     \
     ERR_set_error)

#define CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR      102
#define CMS_R_INVALID_KEY_ENCRYPTION_PARAMETER           176
#define CMS_R_NO_PASSWORD                                178
#define CMS_R_UNKNOWN_CIPHER                             148
#define CMS_R_UNSUPPORTED_KEY_ENCRYPTION_ALGORITHM       179
#define CMS_R_UNWRAP_FAILURE                             180

void *CRYPTO_malloc(size_t num, const char *file, int line);
void *CRYPTO_zalloc(size_t num, const char *file, int line);
void CRYPTO_free(void *ptr, const char *file, int line);
void CRYPTO_clear_free(void *ptr, size_t num, const char *file, int line);

#define OPENSSL_malloc(num)        CRYPTO_malloc(num, OPENSSL_FILE, OPENSSL_LINE)
#define OPENSSL_free(addr)         CRYPTO_free(addr, OPENSSL_FILE, OPENSSL_LINE)
#define OPENSSL_clear_free(addr, num) CRYPTO_clear_free(addr, num, OPENSSL_FILE, OPENSSL_LINE)

__owur int EVP_CIPHER_CTX_get_block_size(const EVP_CIPHER_CTX *ctx);
__owur int EVP_DecryptInit_ex(EVP_CIPHER_CTX *ctx,
                              const EVP_CIPHER *cipher, EVP_PKEY *pkey,
                              const unsigned char *key, const unsigned char *iv);
__owur int EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out,
                             int *outl, const unsigned char *in, int inl);
EVP_CIPHER *EVP_CIPHER_fetch(OSSL_LIB_CTX *ctx, const char *algorithm,
                             const char *properties);
void EVP_CIPHER_free(EVP_CIPHER *cipher);
EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void);
void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *c);
int EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *c, int pad);
__owur int EVP_CipherInit_ex(EVP_CIPHER_CTX *ctx,
                             const EVP_CIPHER *cipher, EVP_PKEY *pkey,
                             const unsigned char *key, const unsigned char *iv,
                             int enc);
int EVP_CIPHER_asn1_to_param(EVP_CIPHER_CTX *c, ASN1_TYPE *type);
int EVP_PBE_CipherInit_ex(ASN1_OBJECT *pbe_obj, const char *pass, int passlen,
                          ASN1_TYPE *param, EVP_CIPHER_CTX *ctx, int en_de,
                          OSSL_LIB_CTX *libctx, const char *propq);

int OBJ_obj2nid(const ASN1_OBJECT *o);
int OBJ_obj2txt(char *buf, int buf_len, const ASN1_OBJECT *a, int no_name);

void *ASN1_TYPE_unpack_sequence(const ASN1_ITEM *it, const ASN1_TYPE *t);

void X509_ALGOR_free(X509_ALGOR *a);

typedef struct CMS_CTX_st CMS_CTX;

struct CMS_CTX_st {
    OSSL_LIB_CTX *libctx;
    char *propq;
};

typedef struct CMS_PasswordRecipientInfo_st CMS_PasswordRecipientInfo;

struct CMS_EncryptedContentInfo_st {
    ASN1_OBJECT *contentType;
    X509_ALGOR *contentEncryptionAlgorithm;
    ASN1_OCTET_STRING *encryptedContent;
    const EVP_CIPHER *cipher;
    unsigned char *key;
    size_t keylen;
    unsigned char *tag;
    size_t taglen;
    int debug;
    int havenocert;
};

typedef struct CMS_EncryptedContentInfo_st CMS_EncryptedContentInfo;

struct CMS_PasswordRecipientInfo_st {
    int32_t version;
    X509_ALGOR *keyDerivationAlgorithm;
    X509_ALGOR *keyEncryptionAlgorithm;
    ASN1_OCTET_STRING *encryptedKey;
    unsigned char *pass;
    size_t passlen;
    const CMS_CTX *cms_ctx;
};

struct CMS_RecipientInfo_st {
    int type;
    union {
        void *ktri;
        void *kari;
        void *kekri;
        CMS_PasswordRecipientInfo *pwri;
        void *ori;
    } d;
};

struct CMS_ContentInfo_st {
    ASN1_OBJECT *contentType;
    union {
        ASN1_OCTET_STRING *data;
        void *signedData;
        void *envelopedData;
        void *digestedData;
        void *encryptedData;
        void *authEnvelopedData;
        void *authenticatedData;
        void *compressedData;
        ASN1_TYPE *other;
        void *otherData;
    } d;
    CMS_CTX ctx;
};

typedef struct CMS_ContentInfo_st CMS_ContentInfo;
typedef struct CMS_RecipientInfo_st CMS_RecipientInfo;

const CMS_CTX *ossl_cms_get0_cmsctx(const CMS_ContentInfo *cms);
OSSL_LIB_CTX *ossl_cms_ctx_get0_libctx(const CMS_CTX *ctx);
const char *ossl_cms_ctx_get0_propq(const CMS_CTX *ctx);
CMS_EncryptedContentInfo *ossl_cms_get0_env_enc_content(const CMS_ContentInfo *cms);

/* kek_wrap_key is a static function in the same translation unit;
   forward declaration needed as it is called after ossl_cms_RecipientInfo_pwri_crypt */
static int kek_wrap_key(unsigned char *out, size_t *outlen,
                        const unsigned char *in, size_t inlen,
                        EVP_CIPHER_CTX *ctx, const CMS_CTX *cms_ctx);

static int kek_unwrap_key(unsigned char *out, size_t *outlen,
                          const unsigned char *in, size_t inlen,
                          EVP_CIPHER_CTX *ctx)
{
    size_t blocklen = EVP_CIPHER_CTX_get_block_size(ctx);
    unsigned char *tmp;
    int outl, rv = 0;

    if (blocklen == 0)
        return 0;

    if (inlen < 2 * blocklen) {
        /* too small */
        return 0;
    }
    if (inlen % blocklen) {
        /* Invalid size */
        return 0;
    }
    if ((tmp = OPENSSL_malloc(inlen)) == NULL)
        return 0;
    /* setup IV by decrypting last two blocks */
    if (!EVP_DecryptUpdate(ctx, tmp + inlen - 2 * blocklen, &outl,
                           in + inlen - 2 * blocklen, blocklen * 2)
        /*
         * Do a decrypt of last decrypted block to set IV to correct value
         * output it to start of buffer so we don't corrupt decrypted block
         * this works because buffer is at least two block lengths long.
         */
        || !EVP_DecryptUpdate(ctx, tmp, &outl,
                              tmp + inlen - blocklen, blocklen)
        /* Can now decrypt first n - 1 blocks */
        || !EVP_DecryptUpdate(ctx, tmp, &outl, in, inlen - blocklen)

        /* Reset IV to original value */
        || !EVP_DecryptInit_ex(ctx, NULL, NULL, NULL, NULL)
        /* Decrypt again */
        || !EVP_DecryptUpdate(ctx, tmp, &outl, tmp, inlen))
        goto err;
    /* Check check bytes */
    if (((tmp[1] ^ tmp[4]) & (tmp[2] ^ tmp[5]) & (tmp[3] ^ tmp[6])) != 0xff) {
        /* Check byte failure */
        goto err;
    }
    if (inlen < (size_t)(tmp[0] - 4)) {
        /* Invalid length value */
        goto err;
    }
    *outlen = (size_t)tmp[0];
    memcpy(out, tmp + 4, *outlen);
    rv = 1;
 err:
    OPENSSL_clear_free(tmp, inlen);
    return rv;

}

int ossl_cms_RecipientInfo_pwri_crypt(const CMS_ContentInfo *cms,
                                      CMS_RecipientInfo *ri, int en_de)
{
    CMS_EncryptedContentInfo *ec;
    CMS_PasswordRecipientInfo *pwri;
    int r = 0;
    X509_ALGOR *algtmp, *kekalg = NULL;
    EVP_CIPHER_CTX *kekctx = NULL;
    char name[OSSL_MAX_NAME_SIZE];
    EVP_CIPHER *kekcipher;
    unsigned char *key = NULL;
    size_t keylen;
    const CMS_CTX *cms_ctx = ossl_cms_get0_cmsctx(cms);

    ec = ossl_cms_get0_env_enc_content(cms);

    pwri = ri->d.pwri;

    if (pwri->pass == NULL) {
        ERR_raise(ERR_LIB_CMS, CMS_R_NO_PASSWORD);
        return 0;
    }
    algtmp = pwri->keyEncryptionAlgorithm;

    if (!algtmp || OBJ_obj2nid(algtmp->algorithm) != NID_id_alg_PWRI_KEK) {
        ERR_raise(ERR_LIB_CMS, CMS_R_UNSUPPORTED_KEY_ENCRYPTION_ALGORITHM);
        return 0;
    }

    kekalg = ASN1_TYPE_unpack_sequence(ASN1_ITEM_rptr(X509_ALGOR),
                                       algtmp->parameter);

    if (kekalg == NULL) {
        ERR_raise(ERR_LIB_CMS, CMS_R_INVALID_KEY_ENCRYPTION_PARAMETER);
        return 0;
    }

    OBJ_obj2txt(name, sizeof(name), kekalg->algorithm, 0);
    kekcipher = EVP_CIPHER_fetch(ossl_cms_ctx_get0_libctx(cms_ctx), name,
                                 ossl_cms_ctx_get0_propq(cms_ctx));

    if (kekcipher == NULL) {
        ERR_raise(ERR_LIB_CMS, CMS_R_UNKNOWN_CIPHER);
        goto err;
    }

    kekctx = EVP_CIPHER_CTX_new();
    if (kekctx == NULL) {
        ERR_raise(ERR_LIB_CMS, ERR_R_EVP_LIB);
        goto err;
    }
    /* Fixup cipher based on AlgorithmIdentifier to set IV etc */
    if (!EVP_CipherInit_ex(kekctx, kekcipher, NULL, NULL, NULL, en_de))
        goto err;
    EVP_CIPHER_CTX_set_padding(kekctx, 0);
    if (EVP_CIPHER_asn1_to_param(kekctx, kekalg->parameter) <= 0) {
        ERR_raise(ERR_LIB_CMS, CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR);
        goto err;
    }

    algtmp = pwri->keyDerivationAlgorithm;

    /* Finish password based key derivation to setup key in "ctx" */

    if (EVP_PBE_CipherInit_ex(algtmp->algorithm,
                              (char *)pwri->pass, pwri->passlen,
                              algtmp->parameter, kekctx, en_de,
                              cms_ctx->libctx, cms_ctx->propq) < 0) {
        ERR_raise(ERR_LIB_CMS, ERR_R_EVP_LIB);
        goto err;
    }

    /* Finally wrap/unwrap the key */

    if (en_de) {

        if (!kek_wrap_key(NULL, &keylen, ec->key, ec->keylen, kekctx, cms_ctx))
            goto err;

        key = OPENSSL_malloc(keylen);

        if (key == NULL)
            goto err;

        if (!kek_wrap_key(key, &keylen, ec->key, ec->keylen, kekctx, cms_ctx))
            goto err;
        pwri->encryptedKey->data = key;
        pwri->encryptedKey->length = keylen;
    } else {
        key = OPENSSL_malloc(pwri->encryptedKey->length);
        if (key == NULL)
            goto err;
        if (!kek_unwrap_key(key, &keylen,
                            pwri->encryptedKey->data,
                            pwri->encryptedKey->length, kekctx)) {
            ERR_raise(ERR_LIB_CMS, CMS_R_UNWRAP_FAILURE);
            goto err;
        }

        OPENSSL_clear_free(ec->key, ec->keylen);
        ec->key = key;
        ec->keylen = keylen;

    }

    r = 1;

 err:
    EVP_CIPHER_free(kekcipher);
    EVP_CIPHER_CTX_free(kekctx);

    if (!r)
        OPENSSL_free(key);
    X509_ALGOR_free(kekalg);

    return r;

}
