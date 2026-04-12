#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <cstddef>
#include <sys/stat.h>
#include <cerrno>
#include <cmath>
#include <pthread.h>

#define MAGICKCORE_THREAD_SUPPORT

// from: MagickCore/magick-type.h:125
typedef unsigned int MagickStatusType;

// from: MagickCore/magick-type.h:129-134
#if defined(__LP64__) || defined(_WIN64)
typedef unsigned long long MagickSizeType;
#else
typedef size_t MagickSizeType;
#endif

// from: MagickCore/magick-type.h:161-166
typedef enum
{
  MagickFalse = 0,
  MagickTrue = 1
} MagickBooleanType;

// from: MagickCore/method-attribute.h:76
#define MagickCoreSignature  0xabacadabUL

// from: MagickCore/method-attribute.h:77-78
#if !defined(MagickPathExtent)
#  define MagickPathExtent  4096
#endif

// from: MagickCore/image-private.h:26
#define MagickMin(x,y)  (((x) < (y)) ? (x) : (y))
#define CastDoubleToSsizeT(x) ((ssize_t)(x))
#define MagickAbsoluteValue(x) ((x) < 0 ? -(x) : (x))

// from: MagickCore/exception.h:103
typedef enum {
  UndefinedException,
  WarningException = 300,
  ResourceLimitWarning = 300,
  TypeWarning = 305,
  OptionWarning = 310,
  DelegateWarning = 315,
  MissingDelegateWarning = 320,
  CorruptImageWarning = 325,
  FileOpenWarning = 330,
  BlobWarning = 335,
  StreamWarning = 340,
  CacheWarning = 345,
  CoderWarning = 350,
  FilterWarning = 352,
  ModuleWarning = 355,
  DrawWarning = 360,
  ImageWarning = 365,
  WandWarning = 370,
  RandomWarning = 375,
  XServerWarning = 380,
  MonitorWarning = 385,
  RegistryWarning = 390,
  ConfigureWarning = 395,
  PolicyWarning = 399,
  ErrorException = 400,
  ResourceLimitError = 400,
  TypeError = 405,
  OptionError = 410,
  DelegateError = 415,
  MissingDelegateError = 420,
  CorruptImageError = 425,
  FileOpenError = 430,
  BlobError = 435,
  StreamError = 440,
  CacheError = 445,
  CoderError = 450,
  FilterError = 452,
  ModuleError = 455,
  DrawError = 460,
  ImageError = 465,
  WandError = 470,
  RandomError = 475,
  XServerError = 480,
  MonitorError = 485,
  RegistryError = 490,
  ConfigureError = 495,
  PolicyError = 499,
  FatalErrorException = 700,
  ResourceLimitFatalError = 700,
  TypeFatalError = 705,
  OptionFatalError = 710,
  DelegateFatalError = 715,
  MissingDelegateFatalError = 720,
  CorruptImageFatalError = 725,
  FileOpenFatalError = 730,
  BlobFatalError = 735,
  StreamFatalError = 740,
  CacheFatalError = 745,
  CoderFatalError = 750,
  FilterFatalError = 752,
  ModuleFatalError = 755,
  DrawFatalError = 760,
  ImageFatalError = 765,
  WandFatalError = 770,
  RandomFatalError = 775,
  XServerFatalError = 780,
  MonitorFatalError = 785,
  RegistryFatalError = 790,
  ConfigureFatalError = 795,
  PolicyFatalError = 799
} ExceptionType;

// from: MagickCore/blob.c (StreamType enum)
typedef enum
{
  UndefinedStream,
  StandardStream,
  FileStream,
  PipeStream,
  BlobStream,
  ZipStream,
  BZipStream
} StreamType;

// from: MagickCore/blob.c (FileInfo union)
typedef union _FileInfo
{
  FILE *fp;
  void *gzfile;
  void *bzfile;
} FileInfo;

// Forward declarations
typedef struct _ExceptionInfo ExceptionInfo;
typedef struct _Image Image;
typedef struct _ImageInfo ImageInfo;
typedef struct _DrawInfo DrawInfo;
typedef struct _SemaphoreInfo SemaphoreInfo;
typedef struct _BlobInfo BlobInfo;

// from: MagickCore/blob.h:36
typedef ssize_t (*CustomStreamHandler)(Image *,void *,const size_t);
typedef ssize_t (*StreamHandler)(Image *,void *,const size_t);

// from: MagickCore/thread-private.h:43-47
#if defined(MAGICKCORE_THREAD_SUPPORT)
typedef pthread_mutex_t MagickMutexType;
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
typedef CRITICAL_SECTION MagickMutexType;
#else
typedef size_t MagickMutexType;
#endif

// from: MagickCore/thread_.h:30-34
#if defined(MAGICKCORE_THREAD_SUPPORT)
typedef pthread_t MagickThreadType;
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
typedef DWORD MagickThreadType;
#else
typedef pid_t MagickThreadType;
#endif

// from: MagickCore/semaphore.c:59-75
typedef struct _SemaphoreInfo
{
  MagickMutexType mutex;
  MagickThreadType id;
  ssize_t reference_count;
  size_t signature;
} SemaphoreInfo;

// from: MagickCore/blob.c:135-196
typedef struct _BlobInfo
{
  size_t length, extent, quantum;
  int mode;
  MagickBooleanType mapped, eof;
  int error, error_number;
  ssize_t offset;
  size_t size;
  MagickBooleanType exempt, synchronize, temporary;
  int status;
  StreamType type;
  FileInfo file_info;
  struct stat properties;
  StreamHandler stream;
  void *custom_stream;
  unsigned char *data;
  MagickBooleanType debug;
  SemaphoreInfo *semaphore;
  ssize_t reference_count;
  size_t signature;
} BlobInfo;

// from: MagickCore/exception.h:101-124
struct _ExceptionInfo
{
  ExceptionType severity;
  int error_number;
  char *reason, *description;
  void *exceptions;
  MagickBooleanType relinquish;
  SemaphoreInfo *semaphore;
  size_t signature;
};

// from: MagickCore/image.h:263-350
struct _Image
{
  size_t columns, rows, storage_class, number_channels, number_meta_channels;
  size_t metacontent_extent, colors, extent, magick_columns, magick_rows;
  size_t signature, reference_count, channel_mask, channels, mask_trait;
  size_t alpha_trait, dither, ping, timestamp, ttl, debug, type;
  char filename[MagickPathExtent], magick_filename[MagickPathExtent], magick[MagickPathExtent];
  char *montage, *directory, *geometry;
  ImageInfo *image_info;
  Image *list, *previous, *next;
  void *colorspace, *channel_map, *colormap, *ascii85, *cache;
  void *profiles, *properties, *artifacts, *progress_monitor, *client_data;
  void *tile_offset, *page, *timer, *semaphore, *blob;
};

// from: MagickCore/image.h:358-421
struct _ImageInfo
{
  char filename[MagickPathExtent], magick[MagickPathExtent], unique[MagickPathExtent];
  char *size, *extract, *page, *scenes, *sampling_factor, *server_name;
  char *font, *texture, *density;
  size_t scene, number_scenes, depth, quality, signature;
  double pointsize, fuzz;
  MagickBooleanType temporary, adjoin, antialias, dither, monochrome;
  MagickBooleanType ping, verbose, flatten, shrink;
  void *compression, *orientation, *interlace, *endian, *units;
  void *colorspace, *compose, *gravity, *type, *cache, *file, *blob;
  void *profile, *stream, *custom_stream, *client_data, *progress_monitor;
  void *wizard, *options, *map, *mask, *profiles_ptr, *psd_layer;
  size_t length, channel, width, height, canvas_offset, scene_offset;
  size_t number_objects, objects_offset, seed, width_offset, height_offset;
  size_t raw_offset, raw_size;
  double x_resolution, y_resolution;
  FILE *file_ptr;
  MagickBooleanType affirm, ignore, coalesce, fractal, net, zero, precise;
  MagickBooleanType raw, skip, debug;
  char *debug_str, *label, *title, *background_color_str, *id, *coder;
  void *delegate, *interpolate, *intent, *endianness;
  MagickBooleanType background, loop;
  void *dispose, *matte_color;
  unsigned char endian_byte;
};

// from: MagickCore/draw.h:209-258
struct _DrawInfo
{
  char *primitive, *geometry, *font, *family, *text, *server_name;
  char *density, *id, *metrics, *encoding;
  void *viewbox, *affine, *fill_pattern, *stroke_pattern, *gradient;
  void *fill_rule, *linecap, *linejoin, *decorate, *compose, *align;
  void *anchor, *gravity, *clip_mask, *units, *interlace, *endian;
  void *fill, *stroke, *undercolor, *border_color, *background_color;
  void *matte_color, *transparent_color, *colorspace_info, *intent;
  void *dash_pattern, *alpha_trait, *cache_ptr;
  Image *clip_mask_image;
  double stroke_width, pointsize, kerning, letter_spacing, word_spacing;
  double blur_factor, text_orientation, x_resolution, y_resolution;
  double alpha, dash_offset;
  size_t miterlimit, stretch, style, weight, depth, number_stops;
  MagickBooleanType stroke_antialias, text_antialias, clip_mask_flag;
  MagickBooleanType verbose_info, monochrome_info, debug;
  void *client_data;
};

// from: coders/msl.c:114-145
typedef struct _MSLGroupInfo { size_t numImages; } MSLGroupInfo;

typedef struct _MSLInfo
{
  ExceptionInfo *exception;
  ssize_t depth, n, number_groups;
  ImageInfo **image_info;
  DrawInfo **draw_info;
  Image **attributes, **image;
  char *content;
  MSLGroupInfo *group_info;
} MSLInfo;

// from: MagickCore/memory-private.h (macros)
#define SizeOfBlock(ptr) (*(size_t*)((char*)(ptr)-2*sizeof(size_t)))
#define BlockHeader(ptr) ((size_t*)(ptr))
#define BlockFooter(ptr,size) ((size_t*)((char*)(ptr)+(size)-sizeof(size_t)))
#define NextBlock(ptr) ((void*)((char*)(ptr)+SizeOfBlock(ptr)))
#define PreviousBlock(ptr) ((void*)((char*)(ptr)-SizeOfBlock((char*)(ptr)-2*sizeof(size_t))))
#define PreviousBlockBit 1
#define SizeMask (~(size_t)3)
#define AllocationPolicy(x) (x)
static inline void RemoveFreeBlock(void *p, size_t s) { (void)p; (void)s; }
static inline void InsertFreeBlock(void *p, size_t s) { (void)p; (void)s; }
static void *memory_semaphore = NULL;

typedef void
  *(*AcquireMemoryHandler)(size_t),
  (*DestroyMemoryHandler)(void *),
  *(*ResizeMemoryHandler)(void *,size_t),
  *(*AcquireAlignedMemoryHandler)(const size_t,const size_t),
  (*RelinquishAlignedMemoryHandler)(void *);

typedef struct _MagickMemoryMethods
{
  AcquireMemoryHandler
    acquire_memory_handler;

  ResizeMemoryHandler
    resize_memory_handler;

  DestroyMemoryHandler
    destroy_memory_handler;

  AcquireAlignedMemoryHandler
    acquire_aligned_memory_handler;

  RelinquishAlignedMemoryHandler
    relinquish_aligned_memory_handler;
} MagickMemoryMethods;

static MagickMemoryMethods
  memory_methods =
  {
    (AcquireMemoryHandler) malloc,
    (ResizeMemoryHandler) realloc,
    (DestroyMemoryHandler) free,
    (AcquireAlignedMemoryHandler) NULL,
    (RelinquishAlignedMemoryHandler) NULL
  };

// from: MagickCore/exception.h
extern __attribute__ ((visibility ("default"))) ExceptionInfo *AcquireExceptionInfo(void),
    *CloneExceptionInfo(ExceptionInfo *),
    *DestroyExceptionInfo(ExceptionInfo *);
extern __attribute__ ((visibility ("default"))) char
  *GetExceptionMessage(const int);
extern __attribute__ ((visibility ("default"))) MagickBooleanType
  ThrowException(ExceptionInfo *,const ExceptionType,const char *,
    const char *),
  ThrowMagickExceptionList(ExceptionInfo *,const char *,const char *,
    const size_t,const ExceptionType,const char *,const char *,va_list),
  ThrowMagickException(ExceptionInfo *,const char *,const char *,const size_t,
    const ExceptionType,const char *,const char *,...)
    __attribute__((__format__ (__printf__,7,8)));
extern __attribute__ ((visibility ("default"))) void
  CatchException(ExceptionInfo *);

// from: MagickCore/magick.h:150
extern __attribute__((visibility("default"))) void
MagickCoreGenesis(const char *, const MagickBooleanType),
    MagickCoreTerminus(void);

// from: MagickCore/log.h
extern __attribute__ ((visibility ("default"))) MagickBooleanType IsEventLogging(void);

// from: MagickCore/memory.c:530-574
extern __attribute__ ((visibility ("default"))) void *AcquireMagickMemory(const size_t size)
{
  void *memory = malloc(size == 0 ? 1UL : size);
  return(memory);
}

// from: MagickCore/memory.c:604-616
extern __attribute__ ((visibility ("default"))) void *AcquireCriticalMemory(const size_t size)
{
  void *memory = AcquireMagickMemory(size);
  if (memory == (void *) NULL) { fprintf(stderr,"MemoryAllocationFailed\n"); exit(1); }
  return(memory);
}

// from: MagickCore/memory.c:638-686
extern __attribute__ ((visibility ("default"))) void *AcquireQuantumMemory(const size_t count,const size_t quantum)
{
  MagickSizeType size = (MagickSizeType)count * (MagickSizeType)quantum;
  if ((count != 0) && (size/count != quantum)) { fprintf(stderr,"MemoryAllocationFailed\n"); exit(1); }
  if (size > (MagickSizeType)0x7fffffffL) { fprintf(stderr,"MemoryAllocationFailed\n"); exit(1); }
  return(AcquireMagickMemory((size_t)size));
}

// from: MagickCore/memory.c:810-862
extern __attribute__ ((visibility ("default"))) void *ResizeQuantumMemory(void *memory,const size_t count,const size_t quantum)
{
  if (memory == (void *) NULL) return(AcquireQuantumMemory(count,quantum));
  MagickSizeType size = (MagickSizeType)count * (MagickSizeType)quantum;
  if ((count != 0) && (size/count != quantum)) { fprintf(stderr,"MemoryAllocationFailed\n"); exit(1); }
  if (size > (MagickSizeType)0x7fffffffL) { fprintf(stderr,"MemoryAllocationFailed\n"); exit(1); }
  return(realloc(memory,(size_t)size));
}

// from: MagickCore/memory.c:1198-1241
extern __attribute__ ((visibility ("default"))) void *RelinquishMagickMemory(void *memory) {
  if (memory == (void *)NULL)
    return ((void *)NULL);
#if !defined(MAGICKCORE_ANONYMOUS_MEMORY_SUPPORT)
  memory_methods.destroy_memory_handler(memory);
#else
  LockSemaphoreInfo(memory_semaphore);
  assert((SizeOfBlock(memory) % (4 * sizeof(size_t))) == 0);
  assert((*BlockHeader(NextBlock(memory)) & PreviousBlockBit) != 0);
  if ((*BlockHeader(memory) & PreviousBlockBit) == 0) {
    void *previous;

    /*
      Coalesce with previous adjacent block.
    */
    previous = PreviousBlock(memory);
    RemoveFreeBlock(previous, AllocationPolicy(SizeOfBlock(previous)));
    *BlockHeader(previous) = (SizeOfBlock(previous) + SizeOfBlock(memory)) |
                             (*BlockHeader(previous) & ~SizeMask);
    memory = previous;
  }
  if ((*BlockHeader(NextBlock(NextBlock(memory))) & PreviousBlockBit) == 0) {
    void *next;

    /*
      Coalesce with next adjacent block.
    */
    next = NextBlock(memory);
    RemoveFreeBlock(next, AllocationPolicy(SizeOfBlock(next)));
    *BlockHeader(memory) = (SizeOfBlock(memory) + SizeOfBlock(next)) |
                           (*BlockHeader(memory) & ~SizeMask);
  }
  *BlockFooter(memory, SizeOfBlock(memory)) = SizeOfBlock(memory);
  *BlockHeader(NextBlock(memory)) &= (~PreviousBlockBit);
  InsertFreeBlock(memory, AllocationPolicy(SizeOfBlock(memory)));
  UnlockSemaphoreInfo(memory_semaphore);
#endif
  return ((void *)NULL);
}

// from: MagickCore/string.c:329-367
extern __attribute__ ((visibility ("default"))) char *DestroyString(char *string)
{
  if (string != (char *) NULL) string = (char *)RelinquishMagickMemory(string);
  return((char *) NULL);
}

// from: MagickCore/string.c:167-210
extern __attribute__ ((visibility ("default"))) char *AcquireString(const char *source)
{
  size_t length = source ? strlen(source) : 0;
  if (~length < MagickPathExtent) { fprintf(stderr,"UnableToAcquireString\n"); exit(1); }
  char *destination = (char *)AcquireMagickMemory(length+MagickPathExtent);
  if (destination == (char *) NULL) { fprintf(stderr,"UnableToAcquireString\n"); exit(1); }
  if (length != 0) (void)memcpy(destination,source,length*sizeof(*destination));
  destination[length] = '\0';
  return(destination);
}

// from: MagickCore/string.c:252-280
extern __attribute__ ((visibility ("default"))) char *CloneString(char **destination,const char *source)
{
  assert(destination != (char **) NULL);
  if (source == (const char *) NULL) {
    if (*destination != (char *) NULL) *destination = DestroyString(*destination);
    return(*destination);
  }
  if (*destination == (char *) NULL) { *destination = AcquireString(source); return(*destination); }
  size_t length = strlen(source);
  if (~length < MagickPathExtent) { fprintf(stderr,"UnableToAcquireString\n"); exit(1); }
  *destination = (char *)ResizeQuantumMemory(*destination,length+MagickPathExtent,sizeof(**destination));
  if (*destination == (char *) NULL) { fprintf(stderr,"UnableToAcquireString\n"); exit(1); }
  if (length != 0) (void)memcpy(*destination,source,length*sizeof(**destination));
  (*destination)[length] = '\0';
  return(*destination);
}

// from: MagickCore/string.c:679-699
extern __attribute__ ((visibility ("default"))) char *ConstantString(const char *source)
{
  size_t length = source ? strlen(source) : 0;
  char *destination = (char *)AcquireQuantumMemory(length+1UL,sizeof(*destination));
  if (destination == (char *) NULL) { fprintf(stderr,"UnableToAcquireString\n"); exit(1); }
  if (source != (const char *) NULL) (void)memcpy(destination,source,length*sizeof(*destination));
  destination[length] = '\0';
  return(destination);
}

// from: MagickCore/string.c:908-942
extern __attribute__ ((visibility ("default"))) void CopyMagickString(char *destination,const char *source,const size_t length)
{
  assert(destination != (char *) NULL);
  assert(source != (const char *) NULL);
  (void)strncpy(destination,source,length-1);
  destination[length-1] = '\0';
  size_t count = strlen(destination);
  if (count < length) (void)memset(destination+count,' ',length-count-1);
}

// from: MagickCore/exception.c:523-542
extern __attribute__ ((visibility ("default"))) char *GetExceptionMessage(const int error)
{
  char exception[MagickPathExtent];
  *exception = '\0';
#if defined(MAGICKCORE_HAVE_STRERROR_R)
#if !defined(MAGICKCORE_STRERROR_R_CHAR_P)
  (void)strerror_r(error,exception,sizeof(exception));
#else
  (void)CopyMagickString(exception,strerror_r(error,exception,sizeof(exception)),sizeof(exception));
#endif
#else
  (void)CopyMagickString(exception,strerror(error),sizeof(exception));
#endif
  return(ConstantString(exception));
}

// from: MagickCore/mutex.h:33
#if defined(MAGICKCORE_OPENMP_SUPPORT)
static MagickBooleanType
  translation_unit_initialized = MagickFalse;

static omp_lock_t
  translation_unit_mutex;
#elif defined(MAGICKCORE_THREAD_SUPPORT)
static pthread_mutex_t
  translation_unit_mutex = PTHREAD_MUTEX_INITIALIZER;
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
static LONG
  translation_unit_mutex = 0;
#endif

// from: MagickCore/log.h:27
#if !defined(GetMagickModule)
# define GetMagickModule()  __FILE__,__func__,(unsigned long) __LINE__
#endif

// from: MagickCore/exception-private.h:35
#define ThrowFatalException(severity, tag)                                     \
  {                                                                            \
    char *fatal_message;                                                       \
                                                                               \
    ExceptionInfo *fatal_exception;                                            \
                                                                               \
    fatal_exception = AcquireExceptionInfo();                                  \
    fatal_message = GetExceptionMessage(errno);                                \
    (void)ThrowMagickException(fatal_exception, GetMagickModule(), (ExceptionType)severity,   \
                               tag, "`%s'", fatal_message);                    \
    fatal_message = DestroyString(fatal_message);                              \
    CatchException(fatal_exception);                                           \
    (void)DestroyExceptionInfo(fatal_exception);                               \
    MagickCoreTerminus();                                                      \
    exit((int)(severity - FatalErrorException) + 1);                          \
  }

// from: MagickCore/semaphore.c:293-327
extern __attribute__ ((visibility ("default"))) void LockSemaphoreInfo(SemaphoreInfo *semaphore_info) {
  assert(semaphore_info != (SemaphoreInfo *)NULL);
  assert(semaphore_info->signature == MagickCoreSignature);
#if defined(MAGICKCORE_DEBUG)
  if ((semaphore_info->reference_count > 0) &&
      (IsMagickThreadEqual(semaphore_info->id) != MagickFalse)) {
    (void)FormatLocaleFile(stderr, "Warning: unexpected recursive lock!\n");
    (void)fflush(stderr);
  }
#endif
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  omp_set_lock((omp_lock_t *)&semaphore_info->mutex);
#elif defined(MAGICKCORE_THREAD_SUPPORT)
  {
    int status;

    status = pthread_mutex_lock(&semaphore_info->mutex);
    if (status != 0) {
      errno = status;
      perror("unable to lock mutex");
      exit(1);
    }
  }
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
  EnterCriticalSection(&semaphore_info->mutex);
#endif
#if defined(MAGICKCORE_DEBUG)
  semaphore_info->id = GetMagickThreadId();
  semaphore_info->reference_count++;
#endif
}

// from: MagickCore/semaphore.c:449-482
extern __attribute__ ((visibility ("default"))) void UnlockSemaphoreInfo(SemaphoreInfo *semaphore_info)
{
  assert(semaphore_info != (SemaphoreInfo *) NULL);
  assert(semaphore_info->signature == MagickCoreSignature);
#if defined(MAGICKCORE_DEBUG)
  assert(IsMagickThreadEqual(semaphore_info->id) != MagickFalse);
  if (semaphore_info->reference_count == 0)
    {
      (void) FormatLocaleFile(stderr,
        "Warning: semaphore lock already unlocked!\n");
      (void) fflush(stderr);
      return;
    }
  semaphore_info->reference_count--;
#endif
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  omp_unset_lock((omp_lock_t *) &semaphore_info->mutex);
#elif defined(MAGICKCORE_THREAD_SUPPORT)
  {
    int
      status;

    status=pthread_mutex_unlock(&semaphore_info->mutex);
    if (status != 0)
      {
        errno=status;
        perror("unable to unlock mutex");
        exit(1);
      }
  }
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
  LeaveCriticalSection(&semaphore_info->mutex);
#endif
}

static inline void LockMagickMutex(void)
{
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  if (translation_unit_initialized == MagickFalse)
    InitializeMagickMutex();
  omp_set_lock(&translation_unit_mutex);
#elif defined(MAGICKCORE_THREAD_SUPPORT)
  {
    int
      status;

    status=pthread_mutex_lock(&translation_unit_mutex);
    if (status != 0)
      {
        errno=status;
        ThrowFatalException(ResourceLimitFatalError,"UnableToLockSemaphore");
      }
  }
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
  while (InterlockedCompareExchange(&translation_unit_mutex,1L,0L) != 0)
    Sleep(10);
#endif
}

static inline void UnlockMagickMutex(void)
{
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  if (translation_unit_initialized == MagickFalse)
    InitializeMagickMutex();
  omp_unset_lock(&translation_unit_mutex);
#elif defined(MAGICKCORE_THREAD_SUPPORT)
  {
    int
      status;

    status=pthread_mutex_unlock(&translation_unit_mutex);
    if (status != 0)
      {
        errno=status;
        ThrowFatalException(ResourceLimitFatalError,"UnableToUnlockSemaphore");
      }
  }
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
  InterlockedExchange(&translation_unit_mutex,0L);
#endif
}

static void *RelinquishSemaphoreMemory(void *memory)
{
  if (memory == (void *) NULL)
    return((void *) NULL);
#if defined(MAGICKCORE_HAVE_POSIX_MEMALIGN)
  free(memory);
#elif defined(MAGICKCORE_HAVE__ALIGNED_MALLOC)
  _aligned_free(memory);
#else
  free(*((void **) memory-1));
#endif
  return(NULL);
}

// from: MagickCore/semaphore.c:351-378
extern __attribute__ ((visibility ("default"))) void RelinquishSemaphoreInfo(SemaphoreInfo **semaphore_info) {
  assert(semaphore_info != (SemaphoreInfo **)NULL);
  assert((*semaphore_info) != (SemaphoreInfo *)NULL);
  assert((*semaphore_info)->signature == MagickCoreSignature);
  LockMagickMutex();
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  omp_destroy_lock((omp_lock_t *)&(*semaphore_info)->mutex);
#elif defined(MAGICKCORE_THREAD_SUPPORT)
  {
    int status;

    status = pthread_mutex_destroy(&(*semaphore_info)->mutex);
    if (status != 0) {
      errno = status;
      perror("unable to destroy mutex");
      exit(1);
    }
  }
#elif defined(MAGICKCORE_WINDOWS_SUPPORT)
  DeleteCriticalSection(&(*semaphore_info)->mutex);
#endif
  (*semaphore_info)->signature = (~MagickCoreSignature);
  *semaphore_info = (SemaphoreInfo *)RelinquishSemaphoreMemory(*semaphore_info);
  UnlockMagickMutex();
}

// from: MagickCore/log.c:388-478
extern __attribute__ ((visibility ("default"))) void LogMagickEvent(const size_t event,const char *module,const char *function,
  const size_t line,const char *format,...)
{
  va_list args;
  (void)event; (void)module; (void)function; (void)line;
  va_start(args,format);
  vfprintf(stderr,format,args);
  va_end(args);
  fprintf(stderr,"\n");
}

// from: MagickCore/option.c:1500-1544
extern __attribute__ ((visibility ("default"))) const char *GetImageOption(const ImageInfo *image_info,const char *key)
{
  (void)image_info; (void)key;
  return((const char *)NULL);
}

// from: MagickCore/string.c:1234-1278
extern __attribute__ ((visibility ("default"))) MagickBooleanType IsStringTrue(const char *value)
{
  if (value == (const char *) NULL) return(MagickFalse);
  return(MagickFalse);
}

// from: MagickCore/blob.c:3956-4010
extern __attribute__ ((visibility ("default"))) ssize_t ReadBlob(Image *image,const size_t count,void *data)
{
  BlobInfo *blob_info;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(image->blob != (BlobInfo *) NULL);
  blob_info = (BlobInfo *)image->blob;
  if (blob_info->type == FileStream || blob_info->type == StandardStream || blob_info->type == PipeStream) {
    ssize_t count_read = fread(data,1,count,blob_info->file_info.fp);
    if (count_read == 0 && ferror(blob_info->file_info.fp) != 0) {
      blob_info->error_number = errno;
      blob_info->status = (-1);
    }
    return(count_read);
  } else if (blob_info->type == BlobStream) {
    ssize_t count_read = 0;
    if (blob_info->offset < (ssize_t)blob_info->length) {
      ssize_t n = MagickMin((ssize_t)count,blob_info->length-blob_info->offset);
      (void)memcpy(data,(unsigned char*)blob_info->data+blob_info->offset,(size_t)n);
      count_read = n;
      blob_info->offset += n;
    }
    if (blob_info->offset >= (ssize_t)blob_info->length) blob_info->eof = MagickTrue;
    return(count_read);
  }
  return(0);
}

// from: MagickCore/blob.c:4025-4080
extern __attribute__ ((visibility ("default"))) int ReadBlobByte(Image *image)
{
  BlobInfo *blob_info;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(image->blob != (BlobInfo *) NULL);
  blob_info = (BlobInfo *)image->blob;
  if (blob_info->type == FileStream || blob_info->type == StandardStream || blob_info->type == PipeStream) {
    int c = getc(blob_info->file_info.fp);
    if (c == EOF && ferror(blob_info->file_info.fp) != 0) {
      blob_info->error_number = errno;
      blob_info->status = (-1);
    }
    return(c);
  } else if (blob_info->type == BlobStream) {
    if (blob_info->offset >= (ssize_t)blob_info->length) { blob_info->eof = MagickTrue; return(EOF); }
    int c = (int)((unsigned char*)blob_info->data)[blob_info->offset];
    blob_info->offset++;
    return(c);
  }
  unsigned char buffer[1];
  ssize_t count = ReadBlob(image,1,buffer);
  if (count != 1) return(EOF);
  return((int)buffer[0]);
}

// from: MagickCore/blob.c:622-720
extern __attribute__ ((visibility ("default"))) MagickBooleanType CloseBlob(Image *image)
{
  BlobInfo *blob_info;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  blob_info = (BlobInfo *)image->blob;
  if ((blob_info == (BlobInfo *) NULL) || (blob_info->type == UndefinedStream)) return(MagickTrue);
  if (blob_info->type == FileStream || blob_info->type == StandardStream || blob_info->type == PipeStream) {
    if (blob_info->synchronize != MagickFalse) {
      int status = fflush(blob_info->file_info.fp);
      if (status != 0) { blob_info->error_number = errno; blob_info->status = (-1); }
    }
  }
  if (blob_info->semaphore != (SemaphoreInfo *) NULL)
    RelinquishSemaphoreInfo(&blob_info->semaphore);
  blob_info->signature = (~MagickCoreSignature);
  image->blob = (BlobInfo *)RelinquishMagickMemory(blob_info);
  return(MagickTrue);
}

// from: MagickCore/blob.c:3267-3450
extern __attribute__ ((visibility ("default"))) MagickStatusType OpenBlob(const ImageInfo *image_info,Image *image,
  const size_t mode,ExceptionInfo *exception)
{
  (void)exception;
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image_info->filename);
  image->blob = (BlobInfo *)AcquireCriticalMemory(sizeof(BlobInfo));
  (void)memset(image->blob,0,sizeof(BlobInfo));
  ((BlobInfo *)image->blob)->signature = MagickCoreSignature;
  ((BlobInfo *)image->blob)->semaphore = (SemaphoreInfo *)AcquireCriticalMemory(sizeof(SemaphoreInfo));
  (void)memset(((BlobInfo *)image->blob)->semaphore,0,sizeof(SemaphoreInfo));
  ((BlobInfo *)image->blob)->semaphore->signature = MagickCoreSignature;
  ((BlobInfo *)image->blob)->reference_count = 1;
  ((BlobInfo *)image->blob)->mode = (int)mode;
  return(MagickTrue);
}

// from: MagickCore/blob.c:4909-4980
extern __attribute__ ((visibility ("default"))) char *ReadBlobString(Image *image,char *string)
{
  BlobInfo *blob_info;
  int c = -1;
  size_t i = 0;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(image->blob != (BlobInfo *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  *string = '\0';
  blob_info = (BlobInfo *)image->blob;
  if (blob_info->type == FileStream || blob_info->type == StandardStream) {
    char *p = fgets(string,MagickPathExtent,blob_info->file_info.fp);
    if (p == (char *) NULL) {
      if (ferror(blob_info->file_info.fp) != 0) {
        blob_info->error_number = errno;
        blob_info->status = (-1);
      }
      return((char *)NULL);
    }
    i = strlen(string);
  } else {
    do {
      c = ReadBlobByte(image);
      if (c == EOF) { blob_info->eof = MagickTrue; if (i == 0) return((char *)NULL); break; }
      string[i] = (char)c;
      i++;
    } while ((c != '\n') && (c != '\r') && (i < (MagickPathExtent-1)));
  }
  if (i != 0) {
    if (string[i-1] == '\n' || string[i-1] == '\r') string[i-1] = '\0';
    else string[i] = '\0';
  }
  return(string);
}

// from: MagickCore/blob.c:957-994
extern __attribute__ ((visibility ("default"))) void DestroyBlob(Image *image)
{
  BlobInfo *blob_info;
  MagickBooleanType destroy;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(image->blob != (BlobInfo *) NULL);
  assert(((BlobInfo *)image->blob)->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  blob_info = (BlobInfo *)image->blob;
  destroy = MagickFalse;
  LockSemaphoreInfo(blob_info->semaphore);
  blob_info->reference_count--;
  assert(blob_info->reference_count >= 0);
  if (blob_info->reference_count == 0) destroy = MagickTrue;
  UnlockSemaphoreInfo(blob_info->semaphore);
  if (destroy == MagickFalse) { image->blob = (BlobInfo *)NULL; return; }
  (void)CloseBlob(image);
  if (blob_info->semaphore != (SemaphoreInfo *) NULL)
    RelinquishSemaphoreInfo(&blob_info->semaphore);
  blob_info->signature = (~MagickCoreSignature);
  image->blob = (BlobInfo *)RelinquishMagickMemory(blob_info);
}

// from: MagickCore/image.c:331-382
extern __attribute__ ((visibility ("default"))) ImageInfo *AcquireImageInfo(void)
{
  ImageInfo *image_info = (ImageInfo *)AcquireCriticalMemory(sizeof(ImageInfo));
  (void)memset(image_info,0,sizeof(ImageInfo));
  image_info->signature = MagickCoreSignature;
  return(image_info);
}

// from: MagickCore/image.c:134-233
extern __attribute__ ((visibility ("default"))) Image *AcquireImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  (void)exception;
  Image *image = (Image *)AcquireCriticalMemory(sizeof(Image));
  (void)memset(image,0,sizeof(Image));
  image->signature = MagickCoreSignature;
  image->reference_count = 1;
  if (image_info != (const ImageInfo *) NULL) {
    (void)CopyMagickString(image->filename,image_info->filename,MagickPathExtent);
    (void)CopyMagickString(image->magick_filename,image_info->filename,MagickPathExtent);
    (void)CopyMagickString(image->magick,image_info->magick,MagickPathExtent);
    image->image_info = (ImageInfo *)image_info;
  }
  return(image);
}

// from: MagickCore/image.c:945-1019
extern __attribute__ ((visibility ("default"))) ImageInfo *CloneImageInfo(const ImageInfo *image_info)
{
  ImageInfo *clone_info = AcquireImageInfo();
  if (image_info == (ImageInfo *) NULL) return(clone_info);
  clone_info->compression = image_info->compression;
  clone_info->temporary = image_info->temporary;
  clone_info->adjoin = image_info->adjoin;
  clone_info->antialias = image_info->antialias;
  clone_info->scene = image_info->scene;
  clone_info->number_scenes = image_info->number_scenes;
  clone_info->depth = image_info->depth;
  if (image_info->size != (char *) NULL) (void)CloneString(&clone_info->size,image_info->size);
  if (image_info->extract != (char *) NULL) (void)CloneString(&clone_info->extract,image_info->extract);
  if (image_info->scenes != (char *) NULL) (void)CloneString(&clone_info->scenes,image_info->scenes);
  if (image_info->page != (char *) NULL) (void)CloneString(&clone_info->page,image_info->page);
  clone_info->interlace = image_info->interlace;
  clone_info->endian = image_info->endian;
  clone_info->units = image_info->units;
  clone_info->quality = image_info->quality;
  if (image_info->sampling_factor != (char *) NULL)
    (void)CloneString(&clone_info->sampling_factor,image_info->sampling_factor);
  if (image_info->server_name != (char *) NULL)
    (void)CloneString(&clone_info->server_name,image_info->server_name);
  if (image_info->font != (char *) NULL)
    (void)CloneString(&clone_info->font,image_info->font);
  if (image_info->texture != (char *) NULL)
    (void)CloneString(&clone_info->texture,image_info->texture);
  if (image_info->density != (char *) NULL)
    (void)CloneString(&clone_info->density,image_info->density);
  clone_info->pointsize = image_info->pointsize;
  clone_info->fuzz = image_info->fuzz;
  clone_info->dither = image_info->dither;
  clone_info->monochrome = image_info->monochrome;
  clone_info->colorspace = image_info->colorspace;
  clone_info->orientation = image_info->orientation;
  clone_info->ping = image_info->ping;
  clone_info->verbose = image_info->verbose;
  clone_info->debug = image_info->debug;
  clone_info->signature = image_info->signature;
  (void)CopyMagickString(clone_info->magick,image_info->magick,MagickPathExtent);
  (void)CopyMagickString(clone_info->unique,image_info->unique,MagickPathExtent);
  (void)CopyMagickString(clone_info->filename,image_info->filename,MagickPathExtent);
  return(clone_info);
}

// from: MagickCore/draw.c:270-369
extern __attribute__ ((visibility ("default"))) DrawInfo *CloneDrawInfo(const ImageInfo *image_info,const DrawInfo *draw_info)
{
  DrawInfo *clone_info = (DrawInfo *)AcquireCriticalMemory(sizeof(DrawInfo));
  (void)memset(clone_info,0,sizeof(DrawInfo));
  if (draw_info != (const DrawInfo *) NULL) {
    if (draw_info->primitive != (char *) NULL)
      (void)CloneString(&clone_info->primitive,draw_info->primitive);
    if (draw_info->geometry != (char *) NULL)
      (void)CloneString(&clone_info->geometry,draw_info->geometry);
    clone_info->stroke_width = draw_info->stroke_width;
    clone_info->fill = draw_info->fill;
    clone_info->stroke = draw_info->stroke;
    if (draw_info->font != (char *) NULL)
      (void)CloneString(&clone_info->font,draw_info->font);
    clone_info->pointsize = draw_info->pointsize;
  }
  (void)image_info;
  return(clone_info);
}

// from: MagickCore/draw.c:968-1012
extern __attribute__ ((visibility ("default"))) DrawInfo *DestroyDrawInfo(DrawInfo *draw_info)
{
  assert(draw_info != (DrawInfo *) NULL);
  if (draw_info->primitive != (char *) NULL)
    draw_info->primitive = DestroyString(draw_info->primitive);
  if (draw_info->geometry != (char *) NULL)
    draw_info->geometry = DestroyString(draw_info->geometry);
  if (draw_info->font != (char *) NULL)
    draw_info->font = DestroyString(draw_info->font);
  if (draw_info->text != (char *) NULL)
    draw_info->text = DestroyString(draw_info->text);
  draw_info = (DrawInfo *)RelinquishMagickMemory(draw_info);
  return((DrawInfo *)NULL);
}

// CloneImage dependencies
extern __attribute__ ((visibility ("default"))) void *ClonePixelChannelMap(void *channel_map);
extern __attribute__ ((visibility ("default"))) void *AcquireSemaphoreInfo(void);
extern __attribute__ ((visibility ("default"))) void *ReferencePixelCache(void *cache);

// from: MagickCore/image.c:792-943 (simplified)
extern __attribute__ ((visibility ("default"))) Image *CloneImage(const Image *image,const size_t columns,
  const size_t rows,const MagickBooleanType detach,ExceptionInfo *exception)
{
  (void)columns; (void)rows; (void)detach; (void)exception;
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  Image *clone_image = (Image *)AcquireCriticalMemory(sizeof(Image));
  (void)memset(clone_image,0,sizeof(Image));
  clone_image->signature = MagickCoreSignature;
  clone_image->columns = image->columns;
  clone_image->rows = image->rows;
  clone_image->reference_count = 1;
  clone_image->image_info = CloneImageInfo(image->image_info);
  (void)CopyMagickString(clone_image->magick_filename,image->magick_filename,MagickPathExtent);
  (void)CopyMagickString(clone_image->magick,image->magick,MagickPathExtent);
  (void)CopyMagickString(clone_image->filename,image->filename,MagickPathExtent);
  clone_image->storage_class = image->storage_class;
  clone_image->colorspace = image->colorspace;
  clone_image->alpha_trait = image->alpha_trait;
  clone_image->channels = image->channels;
  clone_image->dither = image->dither;
  clone_image->type = image->type;
  clone_image->channel_map = ClonePixelChannelMap(image->channel_map);
  clone_image->colormap = image->colormap;
  clone_image->cache = ReferencePixelCache(image->cache);
  clone_image->semaphore = AcquireSemaphoreInfo();
  return(clone_image);
}

// from: MagickCore/image.c:2694-2714
extern __attribute__ ((visibility ("default"))) MagickBooleanType SetImageExtent(Image *image,const size_t columns,
  const size_t rows,ExceptionInfo *exception)
{
  (void)exception;
  if ((columns == 0) || (rows == 0)) return(MagickFalse);
  image->columns = columns;
  image->rows = rows;
  return(MagickTrue);
}

// from: MagickCore/list.c:486-524
extern __attribute__ ((visibility ("default"))) Image *DestroyImageList(Image *images)
{
  Image *next;
  while (images != (Image *) NULL) {
    next = images->next;
    images->next = (Image *)NULL;
    images = next;
  }
  return((Image *)NULL);
}

// from: MagickCore/cache.c:936-954
extern __attribute__ ((visibility ("default"))) void DestroyImagePixels(Image *image)
{
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  assert(image->cache != (void *) NULL);
  image->cache = RelinquishMagickMemory(image->cache);
}

// from: MagickCore/pixel.c:349-355
extern __attribute__ ((visibility ("default"))) void *DestroyPixelChannelMap(void *channel_map)
{
  assert(channel_map != (void *) NULL);
  channel_map = RelinquishMagickMemory(channel_map);
  return((void *)NULL);
}

// from: MagickCore/profile.c:240-244
extern __attribute__ ((visibility ("default"))) void DestroyImageProfiles(Image *image)
{
  if (image->profiles != (void *) NULL)
    image->profiles = RelinquishMagickMemory(image->profiles);
}

// from: MagickCore/property.c:329-338
extern __attribute__ ((visibility ("default"))) void DestroyImageProperties(Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  if (image->properties != (void *) NULL)
    image->properties = RelinquishMagickMemory(image->properties);
}

// from: MagickCore/artifact.c:249-258
extern __attribute__ ((visibility ("default"))) void DestroyImageArtifacts(Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  if (image->artifacts != (void *) NULL)
    image->artifacts = RelinquishMagickMemory(image->artifacts);
}

// from: MagickCore/image.c:1257-1310
extern __attribute__ ((visibility ("default"))) ImageInfo *DestroyImageInfo(ImageInfo *image_info)
{
  assert(image_info != (ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image_info->filename);
  if (image_info->size != (char *) NULL)
    image_info->size = DestroyString(image_info->size);
  if (image_info->extract != (char *) NULL)
    image_info->extract = DestroyString(image_info->extract);
  if (image_info->scenes != (char *) NULL)
    image_info->scenes = DestroyString(image_info->scenes);
  if (image_info->page != (char *) NULL)
    image_info->page = DestroyString(image_info->page);
  if (image_info->sampling_factor != (char *) NULL)
    image_info->sampling_factor = DestroyString(image_info->sampling_factor);
  if (image_info->server_name != (char *) NULL)
    image_info->server_name = DestroyString(image_info->server_name);
  if (image_info->font != (char *) NULL)
    image_info->font = DestroyString(image_info->font);
  if (image_info->texture != (char *) NULL)
    image_info->texture = DestroyString(image_info->texture);
  if (image_info->density != (char *) NULL)
    image_info->density = DestroyString(image_info->density);
  image_info = (ImageInfo *)RelinquishMagickMemory(image_info);
  return((ImageInfo *)NULL);
}

// from: MagickCore/image.c:1186-1232
extern __attribute__ ((visibility ("default"))) Image *DestroyImage(Image *image)
{
  MagickBooleanType destroy;
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  destroy = MagickFalse;
  LockSemaphoreInfo((SemaphoreInfo *)image->semaphore);
  image->reference_count--;
  if (image->reference_count == 0) destroy = MagickTrue;
  UnlockSemaphoreInfo((SemaphoreInfo *)image->semaphore);
  if (destroy == MagickFalse) return((Image *)NULL);
  DestroyImagePixels(image);
  image->channel_map = DestroyPixelChannelMap(image->channel_map);
  if (image->montage != (char *) NULL)
    image->montage = DestroyString(image->montage);
  if (image->directory != (char *) NULL)
    image->directory = DestroyString(image->directory);
  if (image->colormap != (void *) NULL)
    image->colormap = RelinquishMagickMemory(image->colormap);
  if (image->geometry != (char *) NULL)
    image->geometry = DestroyString(image->geometry);
  DestroyImageProfiles(image);
  DestroyImageProperties(image);
  DestroyImageArtifacts(image);
  if (image->ascii85 != (void *) NULL)
    image->ascii85 = RelinquishMagickMemory(image->ascii85);
  if (image->image_info != (ImageInfo *) NULL)
    image->image_info = DestroyImageInfo(image->image_info);
  DestroyBlob(image);
  if (image->semaphore != (SemaphoreInfo *) NULL)
    RelinquishSemaphoreInfo((SemaphoreInfo **)&image->semaphore);
  image->signature = (~MagickCoreSignature);
  image = (Image *)RelinquishMagickMemory(image);
  return(image);
}

// from: MagickCore/exception-private.h:53-62
extern __attribute__ ((visibility ("default"))) void ThrowFileException(ExceptionInfo *exception,const size_t severity,
  const char *tag,const char *context)
{
  char *file_message = GetExceptionMessage(errno);
  (void)severity;
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"'%s': %s",context,file_message);
  file_message = DestroyString(file_message);
}

// libxml2 types
typedef void *xmlSAXHandlerPtr;
typedef void *xmlParserCtxtPtr;
typedef void *xmlDocPtr;

// libxml2 declares (external library, not in project)
extern __attribute__ ((visibility ("default"))) void xmlInitParser(void);
extern __attribute__ ((visibility ("default"))) int xmlSAXVersion(void *hdlr,int version);
extern __attribute__ ((visibility ("default"))) xmlParserCtxtPtr xmlCreatePushParserCtxt(xmlSAXHandlerPtr hdlr,void *chunk,const char *filename,int size,const char *enc);
extern __attribute__ ((visibility ("default"))) int xmlParseChunk(xmlParserCtxtPtr ctx,const char *chunk,int size,int terminate);
extern __attribute__ ((visibility ("default"))) int xmlCtxtUseOptions(xmlParserCtxtPtr ctx,int opts);
extern __attribute__ ((visibility ("default"))) void xmlFreeParserCtxt(xmlParserCtxtPtr ctx);

// Forward declarations for MSL functions
static void MSLStartElement(void *,const unsigned char *,const unsigned char **);
static void MSLEndElement(void *,const unsigned char *);
static void MSLCharacters(void *,const unsigned char *,int);
static void MSLWarning(void *,const char *,...);
static void MSLError(void *,const char *,...);
static void DestroyMSLInfo(MSLInfo *);
static ssize_t MSLPushImage(MSLInfo *,Image *);
static MagickBooleanType ProcessMSLScript(const ImageInfo *,Image **,ExceptionInfo *);

// from: coders/msl.c:7938-7957
static MagickBooleanType WriteMSLImage(const ImageInfo *image_info,Image *image,
  ExceptionInfo *exception)
{
  Image *msl_image;
  MagickBooleanType status;
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  msl_image = CloneImage(image,0,0,MagickTrue,exception);
  status = ProcessMSLScript(image_info,&msl_image,exception);
  return(status);
}

// from: coders/msl.c:7386-7527
static MagickBooleanType ProcessMSLScript(const ImageInfo *image_info,
  Image **image,ExceptionInfo *exception)
{
  char message[MagickPathExtent];
  const char *option;
  Image *msl_image;
  MagickStatusType status;
  MSLInfo msl_info;
  ssize_t n;
  struct { void *startElement; void *endElement; void *reference; void *characters;
    void *ignorableWhitespace; void *processingInstruction; void *comment;
    void *warning; void *error; void *fatalError; void *cdataBlock; } sax_modules;
  xmlSAXHandlerPtr sax_handler;
  xmlParserCtxtPtr parser;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image **) NULL);
  if (IsEventLogging() != MagickFalse)
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image_info->filename);
  msl_image = AcquireImage(image_info,exception);
  status = OpenBlob(image_info,msl_image,0,exception);
  if (status == MagickFalse) {
    ThrowFileException(exception,0,"UnableToOpenFile",msl_image->filename);
    msl_image = DestroyImageList(msl_image);
    *image = DestroyImage(*image);
    return(MagickFalse);
  }
  msl_image->columns = 1;
  msl_image->rows = 1;
  (void)memset(&msl_info,0,sizeof(msl_info));
  msl_info.exception = exception;
  msl_info.image_info = (ImageInfo **)AcquireQuantumMemory(1,sizeof(*msl_info.image_info));
  msl_info.draw_info = (DrawInfo **)AcquireQuantumMemory(1,sizeof(*msl_info.draw_info));
  msl_info.image = (Image **)AcquireMagickMemory(sizeof(*msl_info.image));
  msl_info.attributes = (Image **)AcquireQuantumMemory(1,sizeof(*msl_info.attributes));
  msl_info.group_info = (MSLGroupInfo *)AcquireQuantumMemory(1,sizeof(*msl_info.group_info));
  if ((msl_info.image_info == (ImageInfo **) NULL) || (msl_info.draw_info == (DrawInfo **) NULL) ||
      (msl_info.image == (Image **) NULL) || (msl_info.attributes == (Image **) NULL) ||
      (msl_info.group_info == (MSLGroupInfo *) NULL))
    ThrowFatalException(0,"UnableToInterpretMSLImage");
  *msl_info.image_info = CloneImageInfo(image_info);
  *msl_info.draw_info = CloneDrawInfo(image_info,(DrawInfo *)NULL);
  *msl_info.attributes = AcquireImage(image_info,exception);
  (void)SetImageExtent(*msl_info.attributes,1,1,exception);
  msl_info.group_info[0].numImages = 0;
  *msl_info.image = msl_image;
  if (*image != (Image *) NULL) MSLPushImage(&msl_info,*image);
  xmlInitParser();
  xmlSAXVersion(&sax_modules,1);
  sax_modules.startElement = (void*)MSLStartElement;
  sax_modules.endElement = (void*)MSLEndElement;
  sax_modules.reference = (void*)NULL;
  sax_modules.characters = (void*)MSLCharacters;
  sax_modules.ignorableWhitespace = (void*)NULL;
  sax_modules.processingInstruction = (void*)NULL;
  sax_modules.comment = (void*)NULL;
  sax_modules.warning = (void*)MSLWarning;
  sax_modules.error = (void*)MSLError;
  sax_modules.fatalError = (void*)MSLError;
  sax_modules.cdataBlock = (void*)MSLCharacters;
  sax_handler = (xmlSAXHandlerPtr)(&sax_modules);
  parser = xmlCreatePushParserCtxt(sax_handler,NULL,msl_image->filename,0,NULL);
  if (parser == (xmlParserCtxtPtr) NULL) {
    DestroyMSLInfo(&msl_info);
    ThrowFileException(exception,0,"MemoryAllocationFailed","");
  }
  option = GetImageOption(image_info,"msl:parse-huge");
  if ((option != (char *) NULL) && (IsStringTrue(option) != MagickFalse))
    (void)xmlCtxtUseOptions(parser,0);
  option = GetImageOption(image_info,"msl:substitute-entities");
  if ((option != (char *) NULL) && (IsStringTrue(option) != MagickFalse))
    (void)xmlCtxtUseOptions(parser,0);
  while (ReadBlobString(msl_image,message) != (char *) NULL) {
    n = (ssize_t)strlen(message);
    if (n == 0) continue;
    status = (MagickStatusType)xmlParseChunk(parser,message,(int)n,MagickFalse);
    if (status != 0) break;
    status = (MagickStatusType)xmlParseChunk(parser," ",1,MagickFalse);
    if (status != 0) break;
    if (msl_info.exception->severity >= ErrorException) break;
  }
  if (msl_info.exception->severity == UndefinedException)
    (void)xmlParseChunk(parser," ",1,MagickTrue);
  xmlFreeParserCtxt(parser);
  (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s","end SAX");
  if (*image == (Image *) NULL)
    *image = CloneImage(*msl_info.image,0,0,MagickTrue,exception);
  DestroyMSLInfo(&msl_info);
  if (msl_info.exception->severity != UndefinedException) return(MagickFalse);
  return(MagickTrue);
}

// from: coders/msl.c:245-280
static ssize_t MSLPushImage(MSLInfo *msl_info,Image *image)
{
  ssize_t n;
  if ((IsEventLogging() != MagickFalse) && (image != (Image *) NULL))
    (void)LogMagickEvent(0,"",__FILE__,__LINE__,"%s",image->filename);
  assert(msl_info != (MSLInfo *) NULL);
  msl_info->n++;
  n = msl_info->n;
  msl_info->image_info = (ImageInfo **)ResizeQuantumMemory(msl_info->image_info,(size_t)(n+1),sizeof(*msl_info->image_info));
  msl_info->draw_info = (DrawInfo **)ResizeQuantumMemory(msl_info->draw_info,(size_t)(n+1),sizeof(*msl_info->draw_info));
  msl_info->attributes = (Image **)ResizeQuantumMemory(msl_info->attributes,(size_t)(n+1),sizeof(*msl_info->attributes));
  msl_info->image = (Image **)ResizeQuantumMemory(msl_info->image,(size_t)(n+1),sizeof(*msl_info->image));
  if ((msl_info->image_info == (ImageInfo **) NULL) || (msl_info->draw_info == (DrawInfo **) NULL) ||
      (msl_info->attributes == (Image **) NULL) || (msl_info->image == (Image **) NULL))
    ThrowFatalException(0,"MemoryAllocationFailed");
  msl_info->image_info[n] = CloneImageInfo(msl_info->image_info[n-1]);
  msl_info->draw_info[n] = CloneDrawInfo(msl_info->image_info[n-1],msl_info->draw_info[n-1]);
  msl_info->attributes[n] = CloneImage(msl_info->attributes[n-1],0,0,MagickTrue,msl_info->exception);
  msl_info->image[n] = (Image *)image;
  if ((msl_info->image_info[n] == (ImageInfo *) NULL) || (msl_info->attributes[n] == (Image *) NULL))
    ThrowFatalException(0,"MemoryAllocationFailed");
  if (msl_info->number_groups != 0)
    msl_info->group_info[msl_info->number_groups].numImages++;
  return(n);
}

// from: coders/msl.c:7366-7384
static void DestroyMSLInfo(MSLInfo *msl_info)
{
  while (msl_info->n >= 0) {
    if (msl_info->image[msl_info->n] != (Image *) NULL)
      msl_info->image[msl_info->n] = DestroyImage(msl_info->image[msl_info->n]);
    msl_info->attributes[msl_info->n] = DestroyImage(msl_info->attributes[msl_info->n]);
    msl_info->draw_info[msl_info->n] = DestroyDrawInfo(msl_info->draw_info[msl_info->n]);
    msl_info->image_info[msl_info->n] = DestroyImageInfo(msl_info->image_info[msl_info->n]);
    msl_info->n--;
  }
  msl_info->draw_info = (DrawInfo **)RelinquishMagickMemory(msl_info->draw_info);
  msl_info->image = (Image **)RelinquishMagickMemory(msl_info->image);
  msl_info->attributes = (Image **)RelinquishMagickMemory(msl_info->attributes);
  msl_info->image_info = (ImageInfo **)RelinquishMagickMemory(msl_info->image_info);
  msl_info->group_info = (MSLGroupInfo *)RelinquishMagickMemory(msl_info->group_info);
  if (msl_info->content != (char *) NULL)
    msl_info->content = DestroyString(msl_info->content);
}
