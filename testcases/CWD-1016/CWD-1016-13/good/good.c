#include <stddef.h>
#include <stdlib.h>

#if !defined(inline) && !defined(__cplusplus)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define ossl_inline inline
#elif defined(__GNUC__) && __GNUC__ >= 2
#define ossl_inline __inline__
#elif defined(_MSC_VER)
#define ossl_inline __inline
#else
#define ossl_inline
#endif
#else
#define ossl_inline inline
#endif

#if defined(__GNUC__)
#define ossl_unused __attribute__((unused))
#else
#define ossl_unused
#endif

#ifndef OSSL_CRYPTO_ALLOC
#if defined(__GNUC__)
#define OSSL_CRYPTO_ALLOC __attribute__((__malloc__))
#elif defined(_MSC_VER)
#define OSSL_CRYPTO_ALLOC __declspec(restrict)
#else
#define OSSL_CRYPTO_ALLOC
#endif
#endif

#ifndef OPENSSL_FILE
#define OPENSSL_FILE __FILE__
#define OPENSSL_LINE __LINE__
#endif

OSSL_CRYPTO_ALLOC void *CRYPTO_malloc(size_t num, const char *file, int line);

#define OPENSSL_malloc(num) \
    CRYPTO_malloc(num, OPENSSL_FILE, OPENSSL_LINE)

void OPENSSL_free(void *addr);

char *OPENSSL_uni2asc(const unsigned char *uni, int unilen);

typedef enum {
    SURROGATE_MIN = 0xd800UL,
    SURROGATE_MAX = 0xdfffUL,
    UNICODE_MAX = 0x10ffffUL,
    UNICODE_LIMIT
} UNICODE_CONSTANTS;

int is_unicode_surrogate(unsigned long value);

int UTF8_putc(unsigned char *str, int len, unsigned long value)
{
    if (!str)
        len = 4; /* Maximum we will need */
    else if (len <= 0)
        return -1;
    if (value < 0x80) {
        if (str)
            *str = (unsigned char)value;
        return 1;
    }
    if (value < 0x800) {
        if (len < 2)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 6) & 0x1f) | 0xc0);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 2;
    }
    if (value < 0x10000) {
        if (is_unicode_surrogate(value))
            return -2;
        if (len < 3)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 12) & 0xf) | 0xe0);
            *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 3;
    }
    if (value < UNICODE_LIMIT) {
        if (len < 4)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 18) & 0x7) | 0xf0);
            *str++ = (unsigned char)(((value >> 12) & 0x3f) | 0x80);
            *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 4;
    }
    return -2;
}

static int bmp_to_utf8(char *str, const unsigned char *utf16, int len)
{
    unsigned long utf32chr;

    if (len == 0)
        return 0;

    if (len < 2)
        return -1;

    /* pull UTF-16 character in big-endian order */
    utf32chr = (utf16[0] << 8) | utf16[1];

    if (utf32chr >= 0xD800 && utf32chr < 0xE000) { /* two chars */
        unsigned int lo;

        if (len < 4)
            return -1;

        utf32chr -= 0xD800;
        utf32chr <<= 10;
        lo = (utf16[2] << 8) | utf16[3];
        if (lo < 0xDC00 || lo >= 0xE000)
            return -1;
        utf32chr |= lo - 0xDC00;
        utf32chr += 0x10000;
    }

    return UTF8_putc((unsigned char *)str, len > 4 ? 4 : len, utf32chr);
}

char *OPENSSL_uni2utf8(const unsigned char *uni, int unilen)
{
    int asclen, i, j;
    char *asctmp;

    /* string must contain an even number of bytes */
    if (unilen & 1)
        return NULL;

    for (asclen = 0, i = 0; i < unilen;) {
        j = bmp_to_utf8(NULL, uni + i, unilen - i);
        /*
         * falling back to OPENSSL_uni2asc makes lesser sense [than
         * falling back to OPENSSL_asc2uni in OPENSSL_utf82uni above],
         * it's done rather to maintain symmetry...
         */
        if (j < 0)
            return OPENSSL_uni2asc(uni, unilen);
        if (j == 4)
            i += 4;
        else
            i += 2;
        asclen += j;
    }

    /* If no terminating zero allow for one */
    if (!unilen || (uni[unilen - 2] || uni[unilen - 1]))
        asclen++;

    if ((asctmp = OPENSSL_malloc(asclen)) == NULL)
        return NULL;

    /* re-run the loop emitting UTF-8 string */
    for (asclen = 0, i = 0; i < unilen;) {
        j = bmp_to_utf8(asctmp + asclen, uni + i, unilen - i);
        /* when UTF8_putc fails */
        if (j < 0) {
            OPENSSL_free(asctmp);
            return NULL;
        }
        if (j == 4)
            i += 4;
        else
            i += 2;
        asclen += j;
    }

    /* If no terminating zero write one */
    if (!unilen || (uni[unilen - 2] || uni[unilen - 1]))
        asctmp[asclen] = '\0';

    return asctmp;
}
