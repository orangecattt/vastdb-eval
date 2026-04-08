// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

#include <cstddef>
#include <cstdint>
#include <pthread.h>

// from: icu4c/source/common/unicode/umachine.h:236
typedef int8_t UBool;
#define TRUE 1
#define FALSE 0

// from: icu4c/source/common/unicode/umachine.h:347
typedef char16_t UChar;

// from: icu4c/source/common/unicode/umachine.h:80
#define U_CDECL_BEGIN extern "C" {
#define U_CDECL_END }
// from: icu4c/source/common/unicode/umachine.h:76
#define U_CFUNC

// from: icu4c/source/common/unicode/umachine.h:109
#define U_CAPI U_CFUNC U_EXPORT


// from: icu4c/source/common/unicode/uversion.h:119
#define U_NAMESPACE_BEGIN namespace icu {
#define U_NAMESPACE_END }
#define U_NAMESPACE_USE using namespace icu;

// from: icu4c/source/common/unicode/platform.h:797
#ifndef U_EXPORT
#define U_EXPORT
#endif

// from: icu4c/source/common/unicode/platform.h:804
#ifndef U_EXPORT2
#define U_EXPORT2
#endif

// from: icu4c/source/common/unicode/utypes.h:293
#define U_STATIC_IMPLEMENTATION

// from: icu4c/source/common/unicode/utypes.h:303
#define U_COMMON_API

// from: icu4c/source/common/unicode/platform.h:836
#ifndef U_CALLCONV
#define U_CALLCONV U_EXPORT2
#endif

// from: icu4c/source/common/unicode/uobject.h:44
#define U_NO_THROW throw()

// from: icu4c/source/common/unicode/uobject.h:93
typedef void* UClassID;

// from: icu4c/source/common/unicode/utypes.h:396
typedef enum UErrorCode {
    U_ZERO_ERROR = 0,
    U_ILLEGAL_ARGUMENT_ERROR = 1,
    U_MEMORY_ALLOCATION_ERROR = 7,
} UErrorCode;

// from: icu4c/source/common/unicode/utypes.h:604
#define U_SUCCESS(x) ((x)<=U_ZERO_ERROR)
#define U_FAILURE(x) ((x)>U_ZERO_ERROR)

// from: icu4c/source/common/uelement.h:39
union UElement {
    void*   pointer;
    int32_t integer;
};
typedef union UElement UElement;
typedef UElement UHashTok;

// from: icu4c/source/common/uelement.h:51
typedef UBool UHashFunction(const UElement key);

// from: icu4c/source/common/uelement.h:51
typedef UBool UElementsAreEqual(const UElement e1, const UElement e2);
typedef UElementsAreEqual UKeyComparator;
typedef UElementsAreEqual UValueComparator;

// from: icu4c/source/common/uelement.h:59
typedef int8_t U_CALLCONV UElementComparator(UElement e1, UElement e2);

// from: icu4c/source/common/cmemory.h:114
typedef void U_CALLCONV UObjectDeleter(void* obj);

// from: icu4c/source/common/uhash.h:96
struct UHashElement {
    int32_t  hashcode;
    UHashTok value;
    UHashTok key;
};
typedef struct UHashElement UHashElement;

// from: icu4c/source/common/uhash.h:132
enum UHashResizePolicy {
    U_GROW,
    U_GROW_AND_SHRINK,
    U_FIXED
};

// from: icu4c/source/common/uhash.h:154
struct UHashtable {
    UHashElement *elements;
    UHashFunction *keyHasher;
    UKeyComparator *keyComparator;
    UValueComparator *valueComparator;
    UObjectDeleter *keyDeleter;
    UObjectDeleter *valueDeleter;
    int32_t count;
    int32_t length;
    int32_t lowWaterMark;
    int32_t highWaterMark;
    UHashResizePolicy resizePolicy;
    int32_t tokeneater;
};
typedef struct UHashtable UHashtable;

// from: icu4c/source/common/unicode/uobject.h:112
class U_COMMON_API UMemory {
public:
    static void * U_EXPORT2 operator new(size_t size) U_NO_THROW;
    static void * U_EXPORT2 operator new[](size_t size) U_NO_THROW;
    static void U_EXPORT2 operator delete(void *p) U_NO_THROW;
    static void U_EXPORT2 operator delete[](void *p) U_NO_THROW;
};

// from: icu4c/source/common/unicode/uobject.h:207
class U_COMMON_API UObject : public UMemory {
public:
    virtual ~UObject();
    virtual UClassID getDynamicClassID() const = 0;
    static UClassID U_EXPORT2 getStaticClassID();
    UObject() {}
    UObject(const UObject &other);
    UObject &operator=(const UObject &other);
    UBool operator==(const UObject &other) const { return this == &other; }
    UBool operator!=(const UObject &other) const { return this != &other; }
};

// from: icu4c/source/common/uhash.cpp:115
#define HASH_DELETED    ((int32_t) 0x80000000)
#define HASH_EMPTY      ((int32_t) HASH_DELETED + 1)

// from: icu4c/source/common/uhash.cpp:118
#define IS_EMPTY_OR_DELETED(x) ((x) < 0)

// from: icu4c/source/common/uhash.cpp:122
#define HASH_DELETE_KEY_VALUE(hash, keypointer, valuepointer) \
            if (hash->keyDeleter != NULL && keypointer != NULL) { \
                (*hash->keyDeleter)(keypointer); \
            } \
            if (hash->valueDeleter != NULL && valuepointer != NULL) { \
                (*hash->valueDeleter)(valuepointer); \
            }

// from: icu4c/source/common/uhash.cpp:135
#define HINT_KEY_POINTER   (1)

// from: icu4c/source/common/uhash.cpp:136
#define HINT_VALUE_POINTER (2)

// from: icu4c/source/common/umutex.h:31
struct UMutex {
    pthread_mutex_t  fMutex;
};

// from: icu4c/source/common/umutex.h:189
U_CDECL_BEGIN
typedef void U_CALLCONV UMutexFn(UMutex *mutex);
U_CDECL_END

// from: icu4c/source/common/umutex.h:203
U_CDECL_BEGIN
U_CAPI void U_EXPORT2 umtx_lock(UMutex *mutex);
U_CAPI void U_EXPORT2 umtx_unlock(UMutex *mutex);
U_CDECL_END

// from: icu4c/source/common/umutex.h:382
#define U_MUTEX_INITIALIZER { PTHREAD_MUTEX_INITIALIZER }

// from: icu4c/source/common/uhash.h:201
U_CAPI void uhash_init(UHashtable* hash, UHashFunction* keyHash, UKeyComparator* keyComp, UValueComparator* valueComp, UErrorCode* status);
U_CAPI void uhash_close(UHashtable* hash);
U_CAPI void* uhash_put(UHashtable* hash, void* key, void* value, UErrorCode* status);
U_CAPI void* uhash_get(const UHashtable* hash, const void* key);
U_CAPI void* uhash_remove(UHashtable* hash, const void* key);
U_CAPI void uhash_removeAll(UHashtable* hash);
U_CAPI const UHashElement* uhash_nextElement(UHashtable* hash, int32_t* pos);
U_CAPI int32_t uhash_count(const UHashtable* hash);
U_CAPI void uhash_setKeyDeleter(UHashtable* hash, UObjectDeleter* keyDeleter);
U_CAPI void uhash_setValueDeleter(UHashtable* hash, UObjectDeleter* valueDeleter);
U_CAPI int32_t uhash_hashUnicodeString(const UElement key);
U_CAPI UBool uhash_compareUnicodeString(const UElement key1, const UElement key2);
U_CDECL_BEGIN
UHashTok _uhash_put(UHashtable* hash, UHashTok key, UHashTok value, int8_t hint, UErrorCode* status);
UHashTok _uhash_setElement(UHashtable* hash, UHashElement* e, int32_t hashcode, UHashTok key, UHashTok value, int8_t hint);
UHashTok _uhash_remove(UHashtable* hash, UHashTok key);
UHashElement* _uhash_find(UHashtable* hash, UHashTok key, int32_t hashcode);
void _uhash_rehash(UHashtable* hash, UErrorCode* status);
U_CDECL_END

// from: icu4c/source/common/cmemory.h:120
static void deleteUObject(void* obj) { delete (UObject*)obj; }

namespace icu {

// from: icu4c/source/common/unicode/locid.h:331
class U_COMMON_API Locale : public UObject {
public:
    static const Locale& getDefault();
    UClassID getDynamicClassID() const override;
    static UClassID U_EXPORT2 getStaticClassID();
};

// from: icu4c/source/common/unicode/unistr.h:852
class U_COMMON_API UnicodeString : public UObject {
public:
    UnicodeString();
    UnicodeString(const UnicodeString& text);
    UnicodeString& operator=(const UnicodeString& text);
    ~UnicodeString();

    UnicodeString& remove();
    UnicodeString& remove(int32_t start, int32_t count);
    UnicodeString& append(const UnicodeString& text);
    UnicodeString& append(const UnicodeString& text, int32_t start, int32_t count);
    int32_t indexOf(UChar c) const;
    int32_t length() const;
    UBool isBogus() const;
    void setToBogus();
    const UChar* getBuffer() const;
    const UChar* getUnsafeBuffer() const;
    UChar* getBuffer(int32_t capacity);
    UBool operator==(const UnicodeString& text) const;
    UBool operator!=(const UnicodeString& text) const { return !operator==(text); }

    UClassID getDynamicClassID() const override;
    static UClassID U_EXPORT2 getStaticClassID();

private:
    union {
        struct { int32_t length; int32_t capacity; UChar* array; } heap;
        struct { int32_t length; UChar array[1]; } stack;
    } u;
    UBool fBogus;
    UBool fHeap;
};

// from: icu4c/source/common/hash.h:30
class U_COMMON_API Hashtable : public UMemory {
    UHashtable* hash;
    UHashtable hashObj;

    inline void init(UHashFunction *keyHash, UKeyComparator *keyComp, UValueComparator *valueComp, UErrorCode& status);
    inline void initSize(UHashFunction *keyHash, UKeyComparator *keyComp, UValueComparator *valueComp, int32_t size, UErrorCode& status);

public:
    Hashtable();
    Hashtable(UErrorCode& status);
    ~Hashtable();

    UObjectDeleter *setValueDeleter(UObjectDeleter *fn);

    int32_t count() const;

    void* put(const UnicodeString& key, void* value, UErrorCode& status);

    void* get(const UnicodeString& key) const;

    void* remove(const UnicodeString& key);

    void removeAll(void);

    const UHashElement* nextElement(int32_t& pos) const;

    UKeyComparator* setKeyComparator(UKeyComparator*keyComp);

    UValueComparator* setValueComparator(UValueComparator* valueComp);

    UBool equals(const Hashtable& that) const;
private:
    Hashtable(const Hashtable &other);
    Hashtable &operator=(const Hashtable &other);
};

// from: icu4c/source/common/hash.h:198
inline void* Hashtable::put(const UnicodeString& key, void* value, UErrorCode& status) {
    return uhash_put(hash, new UnicodeString(key), value, &status);
}

// from: icu4c/source/common/uvector.h:75
class U_COMMON_API UVector : public UObject {
private:
    int32_t count;

    int32_t capacity;

    UElement* elements;

    UObjectDeleter *deleter;

    UElementsAreEqual *comparer;

public:
    UVector(UErrorCode &status);

    UVector(int32_t initialCapacity, UErrorCode &status);

    UVector(UObjectDeleter *d, UElementsAreEqual *c, UErrorCode &status);

    UVector(UObjectDeleter *d, UElementsAreEqual *c, int32_t initialCapacity, UErrorCode &status);

    ~UVector();

    void* elementAt(int32_t index) const;

    void* elementAti(int32_t index) const;

    int32_t indexOf(const void* key) const;

    int32_t indexOfi(int32_t key) const;

    UBool contains(const void* key) const;

    UBool containsi(int32_t key) const;

    void addElement(void* element, UErrorCode& status);

    void addElementi(int32_t element, UErrorCode& status);

    void insertElementAt(void* element, int32_t index, UErrorCode& status);

    void insertElementAti(int32_t element, int32_t index, UErrorCode& status);

    void setElementAt(void* element, int32_t index);

    void setElementAti(int32_t element, int32_t index);

    void removeElementAt(int32_t index);

    void removeElementAti(int32_t index);

    void* removeElementAt(int32_t index, UErrorCode &status);

    int32_t removeElementAti(int32_t index, UErrorCode &status);

    void removeAllElements();

    void sort();

    void sort(UElementComparator *cmp);

    int32_t size() const;

    void setSize(int32_t newSize, void* filler, UErrorCode& status);

    void setSizei(int32_t newSize, int32_t filler, UErrorCode& status);

    UBool equals(const UVector& other) const;

    void setDeleter(UObjectDeleter *d);

    void setComparer(UElementsAreEqual *c);

    UElement* allocateElements(int32_t count, UErrorCode &status);

    UClassID getDynamicClassID() const override { return getStaticClassID(); }
    static UClassID U_EXPORT2 getStaticClassID();

private:
    UVector(const UVector &other);

    UVector &operator=(const UVector &other);

    UBool grow(UErrorCode& status);

    void checkIndex(int32_t index) const;
};

// from: icu4c/source/common/mutex.h:53
class U_COMMON_API Mutex : public UMemory {
public:
  inline Mutex(UMutex *mutex = NULL);
  inline ~Mutex();

private:
  UMutex   *fMutex;

  Mutex(const Mutex &other);
  Mutex &operator=(const Mutex &other);
};

inline Mutex::Mutex(UMutex *mutex)
  : fMutex(mutex)
{
  umtx_lock(fMutex);
}

inline Mutex::~Mutex()
{
  umtx_unlock(fMutex);
}

// from: icu4c/source/common/servnotf.h:36
class U_COMMON_API EventListener : public UObject {
public: 
    virtual ~EventListener();

public:
    static UClassID U_EXPORT2 getStaticClassID();

    virtual UClassID getDynamicClassID() const;
};

// from: icu4c/source/common/servnotf.h:74
class U_COMMON_API ICUNotifier : public UMemory  {
private: UVector* listeners;
         
public: 
    ICUNotifier(void);
    
    virtual ~ICUNotifier(void);
    
    virtual void addListener(const EventListener* l, UErrorCode& status);
    
    virtual void removeListener(const EventListener* l, UErrorCode& status);
    
    virtual void notifyChanged(void);
    
protected:
    virtual UBool acceptsListener(const EventListener& l) const;
    
    virtual void notifyListener(EventListener& l) const;
};

// from: icu4c/source/common/serv.h:45
class ICUServiceKey;
class ICUServiceFactory;
class SimpleFactory;
class ServiceListener;
class ICUService;

class DNCache;

// from: icu4c/source/common/serv.h:956
typedef const void* URegistryKey;

// from: icu4c/source/common/serv.h:72
class U_COMMON_API ICUServiceKey : public UObject {
 private: 
   const UnicodeString _id;

 public:
   static const UChar PREFIX_DELIMITER;

   ICUServiceKey(const UnicodeString& id);
   virtual ~ICUServiceKey();

   virtual const UnicodeString& getID() const;
   virtual UnicodeString& canonicalID(UnicodeString& result) const;
   virtual UnicodeString& currentID(UnicodeString& result) const;
   virtual UnicodeString& currentDescriptor(UnicodeString& result) const;
   virtual UBool fallback();
   virtual UBool isFallbackOf(const UnicodeString& id) const;
   virtual UnicodeString& prefix(UnicodeString& result) const;
   static UnicodeString& parsePrefix(UnicodeString& result);
   static UnicodeString& parseSuffix(UnicodeString& result);

public:
   static UClassID U_EXPORT2 getStaticClassID();
   virtual UClassID getDynamicClassID() const;
};

// from: icu4c/source/common/serv.h:214
class U_COMMON_API ICUServiceFactory : public UObject {
 public:
     virtual ~ICUServiceFactory();

     virtual UObject* create(const ICUServiceKey& key, const ICUService* service, UErrorCode& status) const = 0;
     virtual void updateVisibleIDs(Hashtable& result, UErrorCode& status) const = 0;
     virtual UnicodeString& getDisplayName(const UnicodeString& id, const Locale& locale, UnicodeString& result) const = 0;
};

// from: icu4c/source/common/serv.h:526
class U_COMMON_API ICUService : public ICUNotifier {
 protected: 
    const UnicodeString name;

 private:
    uint32_t timestamp;
    UVector* factories;
    Hashtable* serviceCache;
    Hashtable* idCache;
    DNCache* dnCache;

 public:
    ICUService();
    ICUService(const UnicodeString& name);
    virtual ~ICUService();

    UnicodeString& getName(UnicodeString& result) const;
    UObject* get(const UnicodeString& descriptor, UErrorCode& status) const;
    UObject* get(const UnicodeString& descriptor, UnicodeString* actualReturn, UErrorCode& status) const;
    UObject* getKey(ICUServiceKey& key, UErrorCode& status) const;
    virtual UObject* getKey(ICUServiceKey& key, UnicodeString* actualReturn, UErrorCode& status) const;
    UObject* getKey(ICUServiceKey& key, UnicodeString* actualReturn, const ICUServiceFactory* factory, UErrorCode& status) const;

    UVector& getVisibleIDs(UVector& result, UErrorCode& status) const;
    UVector& getVisibleIDs(UVector& result, const UnicodeString* matchID, UErrorCode& status) const;

    UnicodeString& getDisplayName(const UnicodeString& id, UnicodeString& result) const;
    UnicodeString& getDisplayName(const UnicodeString& id, UnicodeString& result, const Locale& locale) const;

    UVector& getDisplayNames(UVector& result, UErrorCode& status) const;
    UVector& getDisplayNames(UVector& result, const Locale& locale, UErrorCode& status) const;
    UVector& getDisplayNames(UVector& result,
                             const Locale& locale, 
                             const UnicodeString* matchID, 
                             UErrorCode& status) const;

    URegistryKey registerInstance(UObject* objToAdopt, const UnicodeString& id, UErrorCode& status);
    virtual URegistryKey registerInstance(UObject* objToAdopt, const UnicodeString& id, UBool visible, UErrorCode& status);
    virtual URegistryKey registerFactory(ICUServiceFactory* factoryToAdopt, UErrorCode& status);
    virtual UBool unregister(URegistryKey rkey, UErrorCode& status);
    virtual void reset(void);
    virtual UBool isDefault(void) const;
    virtual ICUServiceKey* createKey(const UnicodeString* id, UErrorCode& status) const;
    virtual UObject* cloneInstance(UObject* instance) const = 0;

 protected:
    virtual ICUServiceFactory* createSimpleFactory(UObject* instanceToAdopt, const UnicodeString& id, UBool visible, UErrorCode& status);
    virtual void reInitializeFactories(void);
    virtual UObject* handleDefault(const ICUServiceKey& key, UnicodeString* actualReturn, UErrorCode& status) const;
    virtual void clearCaches(void);
    virtual UBool acceptsListener(const EventListener& l) const;
    virtual void notifyListener(EventListener& l) const;
    void clearServiceCache(void);
    const Hashtable* getVisibleIDMap(UErrorCode& status) const;
    int32_t getTimestamp(void) const;
    int32_t countFactories(void) const;

private:
    // friend class ::ICUServiceTest;
};

// from: icu4c/source/common/serv.cpp:205
class CacheEntry : public UMemory {
private:
    int32_t refcount;

public:
    UnicodeString actualDescriptor;
    UObject* service;

    ~CacheEntry() {
        delete service;
    }

    CacheEntry(const UnicodeString& _actualDescriptor, UObject* _service) 
        : refcount(1), actualDescriptor(_actualDescriptor), service(_service) {
    }

    CacheEntry* ref() {
        ++refcount;
        return this;
    }

    CacheEntry* unref() {
        if ((--refcount) == 0) {
            delete this;
            return NULL;
        }
        return this;
    }

    UBool isShared() const {
        return refcount > 1;
    }
};

// from: icu4c/source/common/serv.cpp:260
U_CDECL_BEGIN
static void U_CALLCONV
cacheDeleter(void* obj) {
    U_NAMESPACE_USE ((CacheEntry*)obj)->unref();
}

static void U_CALLCONV
deleteUObject(void *obj) {
    U_NAMESPACE_USE delete (UObject*) obj;
}
U_CDECL_END

// from: icu4c/source/common/serv.cpp:279
class DNCache : public UMemory {
public:
    Hashtable cache;
    const Locale locale;

    DNCache(const Locale& _locale) 
        : cache(), locale(_locale) 
    {
    }
};

// from: icu4c/source/common/serv.cpp:404
class XMutex : public UMemory {
public:
    inline XMutex(UMutex *mutex, UBool reentering) 
        : fMutex(mutex)
        , fActive(!reentering) 
    {
        if (fActive) umtx_lock(fMutex);
    }
    inline ~XMutex() {
        if (fActive) umtx_unlock(fMutex);
    }

private:
    UMutex  *fMutex;
    UBool fActive;
};

// from: icu4c/source/common/serv.cpp:421
struct UVectorDeleter {
    UVector* _obj;
    UVectorDeleter() : _obj(NULL) {}
    ~UVectorDeleter() { delete _obj; }
};

// from: icu4c/source/common/serv.cpp:27
const UChar ICUServiceKey::PREFIX_DELIMITER = 0x002F;

static UMutex lock = U_MUTEX_INITIALIZER;

// from: icu4c/source/common/uhash.cpp:691
U_CAPI void* U_EXPORT2
uhash_put(UHashtable *hash,
          void* key,
          void* value,
          UErrorCode *status) {
    UHashTok keyholder, valueholder;
    keyholder.pointer = key;
    valueholder.pointer = value;
    return _uhash_put(hash, keyholder, valueholder,
                      HINT_KEY_POINTER | HINT_VALUE_POINTER,
                      status).pointer;
}

// from: icu4c/source/common/uhash.cpp:463
static UHashTok
_uhash_put(UHashtable *hash,
           UHashTok key,
           UHashTok value,
           int8_t hint,
           UErrorCode *status) {

    /* Put finds the position in the table for the new value.  If the
     * key is already in the table, it is deleted, if there is a
     * non-NULL keyDeleter.  Then the key, the hash and the value are
     * all put at the position in their respective arrays.
     */
    int32_t hashcode;
    UHashElement* e;
    UHashTok emptytok;

    if (U_FAILURE(*status)) {
        goto err;
    }
    (void)(hash != NULL);
    /* Cannot always check pointer here or iSeries sees NULL every time. */
    if ((hint & HINT_VALUE_POINTER) && value.pointer == NULL) {
        /* Disallow storage of NULL values, since NULL is returned by
         * get() to indicate an absent key.  Storing NULL == removing.
         */
        return _uhash_remove(hash, key);
    }
    if (hash->count > hash->highWaterMark) {
        _uhash_rehash(hash, status);
        if (U_FAILURE(*status)) {
            goto err;
        }
    }

    hashcode = (*hash->keyHasher)(key);
    e = _uhash_find(hash, key, hashcode);
    (void)(e != NULL);

    if (IS_EMPTY_OR_DELETED(e->hashcode)) {
        /* Important: We must never actually fill the table up.  If we
         * do so, then _uhash_find() will return NULL, and we'll have
         * to check for NULL after every call to _uhash_find().  To
         * avoid this we make sure there is always at least one empty
         * or deleted slot in the table.  This only is a problem if we
         * are out of memory and rehash isn't working.
         */
        ++hash->count;
        if (hash->count == hash->length) {
            /* Don't allow count to reach length */
            --hash->count;
            *status = U_MEMORY_ALLOCATION_ERROR;
            goto err;
        }
    }

    /* We must in all cases handle storage properly.  If there was an
     * old key, then it must be deleted (if the deleter != NULL).
     * Make hashcodes stored in table positive.
     */
    return _uhash_setElement(hash, e, hashcode & 0x7FFFFFFF, key, value, hint);

 err:
    /* If the deleters are non-NULL, this method adopts its key and/or
     * value arguments, and we must be sure to delete the key and/or
     * value in all cases, even upon failure.
     */
    HASH_DELETE_KEY_VALUE(hash, key.pointer, value.pointer);
    emptytok.pointer = NULL; emptytok.integer = 0;
    return emptytok;
}

// from: icu4c/source/common/serv.cpp:429
UObject* 
ICUService::getKey(ICUServiceKey& key, UnicodeString* actualReturn, const ICUServiceFactory* factory, UErrorCode& status) const 
{
    if (U_FAILURE(status)) {
        return NULL;
    }

    if (isDefault()) {
        return handleDefault(key, actualReturn, status);
    }

    ICUService* ncthis = (ICUService*)this;

    CacheEntry* result = NULL;
    {
        XMutex mutex(&lock, factory != NULL);

        if (serviceCache == NULL) {
            ncthis->serviceCache = new Hashtable(status);
            if (ncthis->serviceCache == NULL) {
                return NULL;
            }
            if (U_FAILURE(status)) {
                delete serviceCache;
                return NULL;
            }
            serviceCache->setValueDeleter(cacheDeleter);
        }

        UnicodeString currentDescriptor;
        UVectorDeleter cacheDescriptorList;
        UBool putInCache = FALSE;

        int32_t startIndex = 0;
        int32_t limit = factories->size();
        UBool cacheResult = TRUE;

        if (factory != NULL) {
            for (int32_t i = 0; i < limit; ++i) {
                if (factory == (const ICUServiceFactory*)factories->elementAt(i)) {
                    startIndex = i + 1;
                    break;
                }
            }
            if (startIndex == 0) {
                status = U_ILLEGAL_ARGUMENT_ERROR;
                return NULL;
            }
            cacheResult = FALSE;
        }

        do {
            currentDescriptor.remove();
            key.currentDescriptor(currentDescriptor);
            result = (CacheEntry*)serviceCache->get(currentDescriptor);
            if (result != NULL) {
                break;
            }

            putInCache = TRUE;

            int32_t index = startIndex;
            while (index < limit) {
                ICUServiceFactory* f = (ICUServiceFactory*)factories->elementAt(index++);
                UObject* service = f->create(key, this, status);
                if (U_FAILURE(status)) {
                    delete service;
                    return NULL;
                }
                if (service != NULL) {
                    result = new CacheEntry(currentDescriptor, service);
                    if (result == NULL) {
                        delete service;
                        status = U_MEMORY_ALLOCATION_ERROR;
                        return NULL;
                    }

                    goto outerEnd;
                }
            }

            if (cacheDescriptorList._obj == NULL) {
                cacheDescriptorList._obj = new UVector(deleteUObject, NULL, 5, status);
                if (U_FAILURE(status)) {
                    return NULL;
                }
            }
            UnicodeString* idToCache = new UnicodeString(currentDescriptor);
            if (idToCache == NULL || idToCache->isBogus()) {
                status = U_MEMORY_ALLOCATION_ERROR;
                return NULL;
            }

            cacheDescriptorList._obj->addElement(idToCache, status);
            if (U_FAILURE(status)) {
                return NULL;
            }
        } while (key.fallback());
outerEnd:

        if (result != NULL) {
            if (putInCache && cacheResult) {
                serviceCache->put(result->actualDescriptor, result, status);
                if (U_FAILURE(status)) {
                    delete result;
                    return NULL;
                }

                if (cacheDescriptorList._obj != NULL) {
                    for (int32_t i = cacheDescriptorList._obj->size(); --i >= 0;) {
                        UnicodeString* desc = (UnicodeString*)cacheDescriptorList._obj->elementAt(i);
                        serviceCache->put(*desc, result, status);
                        if (U_FAILURE(status)) {
                            delete result;
                            return NULL;
                        }

                        result->ref();
                        cacheDescriptorList._obj->removeElementAt(i);
                    }
                }
            }

            if (actualReturn != NULL) {
                if (result->actualDescriptor.indexOf((UChar)0x2f) == 0) {
                    actualReturn->remove();
                    actualReturn->append(result->actualDescriptor, 
                        1, 
                        result->actualDescriptor.length() - 1);
                } else {
                    *actualReturn = result->actualDescriptor;
                }

                if (actualReturn->isBogus()) {
                    status = U_MEMORY_ALLOCATION_ERROR;
                    delete result;
                    return NULL;
                }
            }

            UObject* service = cloneInstance(result->service);
            if (putInCache && !cacheResult) {
                delete result;
            }
            return service;
        }
    }

    return handleDefault(key, actualReturn, status);
}

} // namespace icu
