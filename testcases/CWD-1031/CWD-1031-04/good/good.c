#include <stddef.h>
#include <stdint.h>

// from: include/internal/nelem.h:14
#define OSSL_NELEM(x) (sizeof(x) / sizeof((x)[0]))

// from: include/internal/cryptlib.h:150
#define OSSL_BSEARCH_VALUE_ON_NOMATCH 0x01
// from: include/internal/cryptlib.h:151
#define OSSL_BSEARCH_FIRST_VALUE_ON_MATCH 0x02

// from: ssl/ssl_local.h:239
#define SSL_QUIC 0x00040000U

// from: ssl/ssl_local.h:254
#define SSL3_CK_CIPHERSUITE_FLAG 0x03000000

// from: include/openssl/tls1.h:620
#define TLS1_3_CK_AES_128_GCM_SHA256 0x03001301
// from: include/openssl/tls1.h:704
#define TLS1_3_RFC_AES_128_GCM_SHA256 "TLS_AES_128_GCM_SHA256"
// from: include/openssl/tls1.h:621
#define TLS1_3_CK_AES_256_GCM_SHA384 0x03001302
// from: include/openssl/tls1.h:705
#define TLS1_3_RFC_AES_256_GCM_SHA384 "TLS_AES_256_GCM_SHA384"
// from: include/openssl/tls1.h:622
#define TLS1_3_CK_CHACHA20_POLY1305_SHA256 0x03001303
// from: include/openssl/tls1.h:706
#define TLS1_3_RFC_CHACHA20_POLY1305_SHA256 "TLS_CHACHA20_POLY1305_SHA256"
// from: include/openssl/tls1.h:623
#define TLS1_3_CK_AES_128_CCM_SHA256 0x03001304
// from: include/openssl/tls1.h:707
#define TLS1_3_RFC_AES_128_CCM_SHA256 "TLS_AES_128_CCM_SHA256"
// from: include/openssl/tls1.h:624
#define TLS1_3_CK_AES_128_CCM_8_SHA256 0x03001305
// from: include/openssl/tls1.h:708
#define TLS1_3_RFC_AES_128_CCM_8_SHA256 "TLS_AES_128_CCM_8_SHA256"

// from: include/openssl/prov_ssl.h:27
#define TLS1_3_VERSION 0x0304

// from: ssl/ssl_local.h:104
#define SSL_kANY 0x00000000U
// from: ssl/ssl_local.h:124
#define SSL_aANY 0x00000000U
// from: ssl/ssl_local.h:142
#define SSL_AES128GCM 0x00001000U
// from: ssl/ssl_local.h:143
#define SSL_AES256GCM 0x00002000U
// from: ssl/ssl_local.h:149
#define SSL_CHACHA20POLY1305 0x00080000U
// from: ssl/ssl_local.h:175
#define SSL_AEAD 0x00000040U
// from: ssl/ssl_local.h:210
#define SSL_HANDSHAKE_MAC_SHA256 SSL_MD_SHA256_IDX
// from: ssl/ssl_local.h:191
#define SSL_MD_SHA256_IDX 4
// from: ssl/ssl_local.h:192
#define SSL_MD_SHA384_IDX 5
// from: ssl/ssl_local.h:211
#define SSL_HANDSHAKE_MAC_SHA384 SSL_MD_SHA384_IDX
// from: ssl/ssl_local.h:247
#define SSL_HIGH 0x00000008U
// from: ssl/ssl_local.h:244
#define SSL_STRONG_NONE 0x00000001U
// from: ssl/ssl_local.h:246
#define SSL_MEDIUM 0x00000004U
// from: ssl/ssl_local.h:249
#define SSL_NOT_DEFAULT 0x00000020U

// from: include/openssl/ssl.h:236
typedef struct ssl_cipher_st SSL_CIPHER;

// from: ssl/ssl_local.h:381
struct ssl_cipher_st {
  uint32_t valid;
  const char *name;
  const char *stdname;
  uint32_t id;
  uint32_t algorithm_mkey;
  uint32_t algorithm_auth;
  uint32_t algorithm_enc;
  uint32_t algorithm_mac;
  int min_tls;
  int max_tls;
  int min_dtls;
  int max_dtls;
  uint32_t algo_strength;
  uint32_t algorithm2;
  int32_t strength_bits;
  uint32_t alg_bits;
};

// from: ssl/s3_lib.c:39
SSL_CIPHER tls13_ciphers[] = {
    {
        1,
        TLS1_3_RFC_AES_128_GCM_SHA256,
        TLS1_3_RFC_AES_128_GCM_SHA256,
        TLS1_3_CK_AES_128_GCM_SHA256,
        SSL_kANY,
        SSL_aANY,
        SSL_AES128GCM,
        SSL_AEAD,
        TLS1_3_VERSION,
        TLS1_3_VERSION,
        0,
        0,
        SSL_HIGH,
        SSL_HANDSHAKE_MAC_SHA256 | SSL_QUIC,
        128,
        128,
    },
    {
        1,
        TLS1_3_RFC_AES_256_GCM_SHA384,
        TLS1_3_RFC_AES_256_GCM_SHA384,
        TLS1_3_CK_AES_256_GCM_SHA384,
        SSL_kANY,
        SSL_aANY,
        SSL_AES256GCM,
        SSL_AEAD,
        TLS1_3_VERSION,
        TLS1_3_VERSION,
        0,
        0,
        SSL_HIGH,
        SSL_HANDSHAKE_MAC_SHA384 | SSL_QUIC,
        256,
        256,
    },
    {
        1,
        TLS1_3_RFC_CHACHA20_POLY1305_SHA256,
        TLS1_3_RFC_CHACHA20_POLY1305_SHA256,
        TLS1_3_CK_CHACHA20_POLY1305_SHA256,
        SSL_kANY,
        SSL_aANY,
        SSL_CHACHA20POLY1305,
        SSL_AEAD,
        TLS1_3_VERSION,
        TLS1_3_VERSION,
        0,
        0,
        SSL_HIGH,
        SSL_HANDSHAKE_MAC_SHA256 | SSL_QUIC,
        256,
        256,
    },
    {
        1,
        TLS1_3_RFC_AES_128_CCM_SHA256,
        TLS1_3_RFC_AES_128_CCM_SHA256,
        TLS1_3_CK_AES_128_CCM_SHA256,
        SSL_kANY,
        SSL_aANY,
        0x00004000U,
        SSL_AEAD,
        TLS1_3_VERSION,
        TLS1_3_VERSION,
        0,
        0,
        SSL_NOT_DEFAULT | SSL_HIGH,
        SSL_HANDSHAKE_MAC_SHA256,
        128,
        128,
    },
    {
        1,
        TLS1_3_RFC_AES_128_CCM_8_SHA256,
        TLS1_3_RFC_AES_128_CCM_8_SHA256,
        TLS1_3_CK_AES_128_CCM_8_SHA256,
        SSL_kANY,
        SSL_aANY,
        0x00010000U,
        SSL_AEAD,
        TLS1_3_VERSION,
        TLS1_3_VERSION,
        0,
        0,
        SSL_NOT_DEFAULT | SSL_MEDIUM,
        SSL_HANDSHAKE_MAC_SHA256,
        64,
        128,
    },
};

// from: ssl/s3_lib.c:26
#define TLS13_NUM_CIPHERS OSSL_NELEM(tls13_ciphers)
// from: ssl/s3_lib.c:27
#define SSL3_NUM_CIPHERS 256
// from: ssl/s3_lib.c:28
#define SSL3_NUM_SCSVS 2

// from: ssl/s3_lib.c:180
extern SSL_CIPHER ssl3_ciphers[];
// from: ssl/s3_lib.c:3679
extern SSL_CIPHER ssl3_scsvs[];

// from: ssl/s3_lib.c:39 (simplified, 5 of 7 elements)
// from: ssl/ssl_lib.c:3223
int ssl_cipher_id_cmp(const SSL_CIPHER *a, const SSL_CIPHER *b) {
  if (a->id > b->id)
    return 1;
  if (a->id < b->id)
    return -1;
  return 0;
}

// from: crypto/objects/obj_dat.c:693
const void *OBJ_bsearch_ex_(const void *key, const void *base, int num,
                            int size, int (*cmp)(const void *, const void *),
                            int flags);

// from: include/openssl/objects.h:134
#define IMPLEMENT_OBJ_BSEARCH_GLOBAL_CMP_FN(type1, type2, nm)                  \
  static int nm##_cmp_BSEARCH_CMP_FN(const void *a_, const void *b_) {         \
    type1 const *a = (type1 const *)a_;                                        \
    type2 const *b = (type2 const *)b_;                                        \
    return nm##_cmp(a, b);                                                     \
  }                                                                            \
  type2 *OBJ_bsearch_##nm(type1 *key, type2 const *base, int num) {            \
    return (type2 *)OBJ_bsearch_(key, base, num, sizeof(type2),                \
                                 nm##_cmp_BSEARCH_CMP_FN);                     \
  }                                                                            \
  extern void dummy_prototype(void)

// from: crypto/objects/obj_dat.c:687
const void *OBJ_bsearch_(const void *key, const void *base, int num, int size,
                         int (*cmp)(const void *, const void *));

// from: crypto/bsearch.c:13
const void *ossl_bsearch(const void *key, const void *base, int num, int size,
                         int (*cmp)(const void *, const void *), int flags) {
  const char *base_ = (const char *)base;
  int l, h, i = 0, c = 0;
  const char *p = NULL;

  if (num == 0)
    return NULL;
  l = 0;
  h = num;
  while (l < h) {
    i = (l + h) / 2;
    p = &(base_[i * size]);
    c = (*cmp)(key, p);
    if (c < 0)
      h = i;
    else if (c > 0)
      l = i + 1;
    else
      break;
  }
  if (c != 0 && !(flags & OSSL_BSEARCH_VALUE_ON_NOMATCH))
    p = NULL;
  else if (c == 0 && (flags & OSSL_BSEARCH_FIRST_VALUE_ON_MATCH)) {
    while (i > 0 && (*cmp)(key, &(base_[(i - 1) * size])) == 0)
      i--;
    p = &(base_[i * size]);
  }
  return p;
}

// from: crypto/objects/obj_dat.c:687
const void *OBJ_bsearch_(const void *key, const void *base, int num, int size,
                         int (*cmp)(const void *, const void *)) {
  return OBJ_bsearch_ex_(key, base, num, size, cmp, 0);
}

// from: crypto/objects/obj_dat.c:693
const void *OBJ_bsearch_ex_(const void *key, const void *base, int num,
                            int size, int (*cmp)(const void *, const void *),
                            int flags) {
  const char *p = (const char *)ossl_bsearch(key, base, num, size, cmp, flags);

#ifdef CHARSET_EBCDIC
  if (p == NULL) {
    const char *base_ = base;
    int l, h, i = 0, c = 0;
    char *p1;

    for (i = 0; i < num; ++i) {
      p1 = &(base_[i * size]);
      c = (*cmp)(key, p1);
      if (c == 0 || (c < 0 && (flags & 0x01)))
        return p1;
    }
  }
#endif
  return p;
}

// from: ssl/ssl_lib.c:6324
IMPLEMENT_OBJ_BSEARCH_GLOBAL_CMP_FN(SSL_CIPHER, SSL_CIPHER, ssl_cipher_id);

// from: ssl/s3_lib.c:4645
const SSL_CIPHER *ssl3_get_cipher_by_id(uint32_t id) {
  SSL_CIPHER c;
  const SSL_CIPHER *cp;

  c.id = id;
  cp = OBJ_bsearch_ssl_cipher_id(&c, tls13_ciphers, TLS13_NUM_CIPHERS);
  if (cp != NULL)
    return cp;
  cp = OBJ_bsearch_ssl_cipher_id(&c, ssl3_ciphers, SSL3_NUM_CIPHERS);
  if (cp != NULL)
    return cp;
  return OBJ_bsearch_ssl_cipher_id(&c, ssl3_scsvs, SSL3_NUM_SCSVS);
}

// from: ssl/s3_lib.c:4683
const SSL_CIPHER *ssl3_get_cipher_by_char(const unsigned char *p) {
  return ssl3_get_cipher_by_id(SSL3_CK_CIPHERSUITE_FLAG |
                               ((uint32_t)p[0] << 8L) | (uint32_t)p[1]);
}

// from: ssl/quic/quic_impl.c:5078
const SSL_CIPHER *ossl_quic_get_cipher_by_char(const unsigned char *p) {
  const SSL_CIPHER *ciph = ssl3_get_cipher_by_char(p);
  if (ciph == NULL)
    return NULL;

  if ((ciph->algorithm2 & SSL_QUIC) == 0)
    return NULL;

  return ciph;
}
