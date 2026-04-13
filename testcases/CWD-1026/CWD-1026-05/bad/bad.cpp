#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <sys/mman.h>

#define MAGICKCORE_HAVE_MMAP

// from: MagickCore/method-attribute.h:77-80
#define MagickExport __attribute__ ((visibility ("default")))

// from: MagickCore/magick-type.h:158-163
typedef enum
{
  MagickFalse = 0,
  MagickTrue = 1
} MagickBooleanType;

// from: MagickCore/magick-type.h:125-130
typedef unsigned long long MagickSizeType;

// from: MagickCore/magick-type.h:120-125
typedef long long MagickOffsetType;

// from: MagickCore/magick-type.h:120-125
typedef long MagickSSizeType;

// from: MagickCore/resource_.h:25-39
typedef enum
{
  UndefinedResource,
  AreaResource,
  DiskResource,
  FileResource,
  HeightResource,
  MapResource,
  MemoryResource,
  ThreadResource,
  ThrottleResource,
  TimeResource,
  WidthResource,
  ListLengthResource
} ResourceType;

// from: MagickCore/semaphore.h:25
typedef struct _SemaphoreInfo SemaphoreInfo;

// from: MagickCore/blob-private.h:29-44
typedef enum
{
  UndefinedBlobMode,
  ReadBlobMode,
  ReadBinaryBlobMode,
  WriteBlobMode,
  WriteBinaryBlobMode,
  AppendBlobMode,
  AppendBinaryBlobMode
} BlobMode;

// from: MagickCore/blob-private.h:46-57
typedef enum
{
  UndefinedStream,
  FileStream,
  StandardStream,
  PipeStream,
  ZipStream,
  BZipStream,
  FifoStream,
  BlobStream,
  CustomStream
} StreamType;

// from: MagickCore/stream.h:30-31
typedef size_t
  (*StreamHandler)(const void *,const void *,const size_t);

// from: MagickCore/blob.h:35-39
typedef ssize_t
  (*CustomStreamHandler)(unsigned char *,const size_t,void *);

// from: MagickCore/blob.h:38-39
typedef MagickOffsetType
  (*CustomStreamSeeker)(const MagickOffsetType,const int,void *);

// from: MagickCore/blob.h:41-42
typedef MagickOffsetType
  (*CustomStreamTeller)(void *);

// from: MagickCore/blob.h:44-45
typedef struct _CustomStreamInfo
  CustomStreamInfo;

// from: MagickCore/log.h:33-59
typedef enum
{
  UndefinedEvents = 0x000000,
  NoEvents = 0x00000,
  AccelerateEvent = 0x00001,
  AnnotateEvent = 0x00002,
  BlobEvent = 0x00004,
  CacheEvent = 0x00008,
  CoderEvent = 0x00010,
  ConfigureEvent = 0x00020,
  DeprecateEvent = 0x00040,
  DrawEvent = 0x00080,
  ExceptionEvent = 0x00100,
  ImageEvent = 0x00200,
  LocaleEvent = 0x00400,
  ModuleEvent = 0x00800,
  PixelEvent = 0x01000,
  PolicyEvent = 0x02000,
  ResourceEvent = 0x04000,
  TraceEvent = 0x08000,
  TransformEvent = 0x10000,
  UserEvent = 0x20000,
  WandEvent = 0x40000,
  X11Event = 0x80000,
  CommandEvent = 0x100000,
  AllEvents = 0x7fffffff
} LogEventType;

// from: MagickCore/exception.h:29-99
typedef enum
{
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

// Forward declarations
typedef struct _Image Image;
typedef struct _ImageInfo ImageInfo;
typedef struct _ExceptionInfo ExceptionInfo;
typedef struct _MagickInfo MagickInfo;
typedef struct _BlobInfo BlobInfo;

// from: MagickCore/exception.h:101-124
struct _ExceptionInfo
{
  ExceptionType
    severity;

  int
    error_number;

  char
    *reason,
    *description;

  void
    *exceptions;

  MagickBooleanType
    relinquish;

  SemaphoreInfo
    *semaphore;

  size_t
    signature;
};

// from: MagickCore/blob.c:100-114
typedef union FileInfo
{
  FILE
    *file;
} FileInfo;

// from: MagickCore/blob.c:116-174
struct _BlobInfo
{
  size_t
    length,
    extent,
    quantum;

  BlobMode
    mode;

  MagickBooleanType
    mapped,
    eof;

  int
    error;

  MagickOffsetType
    offset;

  MagickSizeType
    size;

  MagickBooleanType
    exempt,
    synchronize,
    status,
    temporary;

  StreamType
    type;

  FileInfo
    file_info;

  StreamHandler
    stream;

  CustomStreamInfo
    *custom_stream;

  unsigned char
    *data;

  MagickBooleanType
    debug;

  SemaphoreInfo
    *semaphore;

  ssize_t
    reference_count;

  size_t
    signature;
};

// from: MagickCore/magick.h:61-97
typedef struct _MagickInfo
{
  char
    *name,
    *description,
    *version,
    *mime_type,
    *note,
    *module;

  void
    *decoder;

  void
    *encoder;

  ImageInfo
    *image_info;

  void
    *magick;

  int
    format_type;

  int
    flags;

  SemaphoreInfo
    *semaphore;

  size_t
    signature;

  void
    *client_data;
} MagickInfo;

// from: MagickCore/image.h:342-375 (simplified)
struct _ImageInfo
{
  char
    filename[4096],
    magick[4096];

  void
    *blob;

  size_t
    length;

  FILE
    *file;

  MagickBooleanType
    debug;

  size_t
    signature;
};

// from: MagickCore/image.h (simplified Image structure)
struct _Image
{
  char
    filename[4096],
    magick[4096];

  BlobInfo
    *blob;

  ExceptionInfo
    *exception;

  MagickBooleanType
    debug;

  size_t
    signature;
};

// from: MagickCore/method-attribute.h:86-89
#define MagickCoreSignature  0xabacadabUL
#define MagickPathExtent  4096

// from: MagickCore/resource_.h:41
#define MagickResourceInfinity  (MagickULLConstant(~0) >> 1)
#define MagickULLConstant(c)  ((MagickSizeType) (c ## ULL))

// from: MagickCore/log.h:27-28
#define GetMagickModule()  __FILE__,__func__,(unsigned long) __LINE__

// from: MagickCore/memory-private.h (resource_info structure)
typedef struct
{
  ssize_t disk;
  ssize_t file;
  ssize_t map;
  ssize_t memory;
  ssize_t time;
  ssize_t disk_limit;
  ssize_t file_limit;
  ssize_t map_limit;
  ssize_t memory_limit;
  ssize_t time_limit;
} ResourceInfo;

// Global variables (from MagickCore/resource_.c)
extern MagickExport SemaphoreInfo *resource_semaphore;
extern MagickExport ResourceInfo resource_info;

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

// Function declarations

// from: MagickCore/memory_.h
extern MagickExport void *AcquireQuantumMemory(const size_t,const size_t);
extern MagickExport void *ResizeQuantumMemory(void *,const size_t,const size_t);
extern MagickExport void *RelinquishMagickMemory(void *);

// from: MagickCore/string_.h
extern MagickExport char *CopyMagickString(char *,const char *,const size_t);
extern MagickExport ssize_t FormatLocaleString(char *,const size_t,const char *,...);
extern MagickExport ssize_t FormatMagickSize(const MagickSizeType,const MagickBooleanType,
  const char *,const size_t,char *);

// from: MagickCore/log.h
extern MagickExport void LogMagickEvent(const LogEventType,const char *,const char *,
  const unsigned long,const char *,...);
extern MagickExport MagickBooleanType IsEventLogging(void);

// from: MagickCore/option.h
extern MagickExport const char *CommandOptionToMnemonic(const void *,const ssize_t);

// from: MagickCore/resource_.h
extern MagickExport void ActivateSemaphoreInfo(SemaphoreInfo **);
extern MagickExport void LockSemaphoreInfo(SemaphoreInfo *);
extern MagickExport void UnlockSemaphoreInfo(SemaphoreInfo *);

// from: MagickCore/exception.h
extern MagickExport void ThrowFileException(ExceptionInfo *,const ExceptionType,
  const char *,const char *);
extern MagickExport MagickBooleanType ThrowMagickException(ExceptionInfo *,const char *,
  const char *,const unsigned long,const ExceptionType,const char *,
  const char *,...);

// from: MagickCore/blob.h
extern MagickExport void *DetachBlob(BlobInfo *);

// from: MagickCore/resource_.h
extern MagickExport void RelinquishMagickResource(const ResourceType,const MagickSizeType);

// from: MagickCore/utility-private.h
extern MagickExport int AcquireUniqueFileResource(char *);
extern MagickExport MagickBooleanType RelinquishUniqueFileResource(const char *);

// from: MagickCore/magick.h
extern MagickExport const MagickInfo *GetMagickInfo(const char *,ExceptionInfo *);
extern MagickExport MagickBooleanType GetMagickAdjoin(const MagickInfo *);
extern MagickExport MagickBooleanType GetMagickBlobSupport(const MagickInfo *);

// from: MagickCore/image.h
extern MagickExport ImageInfo *CloneImageInfo(const ImageInfo *);
extern MagickExport ImageInfo *DestroyImageInfo(ImageInfo *);
extern MagickExport MagickBooleanType SetImageInfo(ImageInfo *,const unsigned int,
  ExceptionInfo *);
extern MagickExport size_t GetImageListLength(const Image *);
extern MagickExport MagickBooleanType WriteImages(const ImageInfo *,Image *,const char *,
  ExceptionInfo *);
extern MagickExport void *ImageToBlob(const ImageInfo *,Image *,size_t *,ExceptionInfo *);
extern MagickExport MagickBooleanType CloseBlob(Image *);

// from: MagickCore/memory_.h
extern MagickExport void *FileToBlob(const char *,const size_t,size_t *,ExceptionInfo *);

MagickExport MagickBooleanType UnmapBlob(void *map,const size_t length)
{
#if defined(MAGICKCORE_HAVE_MMAP)
  int
    status;

  status=munmap(map,length);
  return(status == -1 ? MagickFalse : MagickTrue);
#else
  (void) map;
  (void) length;
  return(MagickFalse);
#endif
}

MagickExport void RelinquishMagickResource(const ResourceType type,
  const MagickSizeType size)
{
  MagickBooleanType
    bi;

  MagickSizeType
    current,
    limit;

  switch (type)
  {
    case AreaResource:
    case HeightResource:
    case ListLengthResource:
    case ThreadResource:
    case ThrottleResource:
    case WidthResource:
      return;
    default:
      break;
  }
  bi=MagickFalse;
  limit=0;
  if (resource_semaphore == (SemaphoreInfo *) NULL)
    ActivateSemaphoreInfo(&resource_semaphore);
  LockSemaphoreInfo(resource_semaphore);
  switch (type)
  {
    case DiskResource:
    {
      bi=MagickTrue;
      resource_info.disk-=size;
      current=(MagickSizeType) resource_info.disk;
      limit=resource_info.disk_limit;
      assert(resource_info.disk >= 0);
      break;
    }
    case FileResource:
    {
      resource_info.file-=size;
      current=(MagickSizeType) resource_info.file;
      limit=resource_info.file_limit;
      assert(resource_info.file >= 0);
      break;
    }
    case MapResource:
    {
      bi=MagickTrue;
      resource_info.map-=size;
      current=(MagickSizeType) resource_info.map;
      limit=resource_info.map_limit;
      assert(resource_info.map >= 0);
      break;
    }
    case MemoryResource:
    {
      bi=MagickTrue;
      resource_info.memory-=size;
      current=(MagickSizeType) resource_info.memory;
      limit=resource_info.memory_limit;
      assert(resource_info.memory >= 0);
      break;
    }
    case TimeResource:
    {
      bi=MagickTrue;
      resource_info.time-=size;
      current=(MagickSizeType) resource_info.time;
      limit=resource_info.time_limit;
      assert(resource_info.time >= 0);
      break;
    }
    default:
    {
      current=0;
      break;
    }
  }
  UnlockSemaphoreInfo(resource_semaphore);
  if (IsEventLogging() != MagickFalse)
    {
      char
        resource_current[4096],
        resource_limit[4096],
        resource_request[4096];

      (void) FormatMagickSize(size,bi,(bi != MagickFalse) ? "B" :
        (const char *) NULL,4096,resource_request);
      (void) FormatMagickSize(current,bi,(bi != MagickFalse) ? "B" :
        (const char *) NULL,4096,resource_current);
      (void) FormatMagickSize(limit,bi,(bi != MagickFalse) ? "B" :
        (const char *) NULL,4096,resource_limit);
      (void) LogMagickEvent(ResourceEvent,__FILE__,__func__,__LINE__,"%s: %s/%s/%s",
        CommandOptionToMnemonic(NULL,(ssize_t) type),
          resource_request,resource_current,resource_limit);
    }
}

MagickExport void *DetachBlob(BlobInfo *blob_info)
{
  void
    *data;

  assert(blob_info != (BlobInfo *) NULL);
  if (blob_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,__FILE__,__func__,__LINE__,"...");
  if (blob_info->mapped != MagickFalse)
    {
      (void) UnmapBlob(blob_info->data,blob_info->length);
      RelinquishMagickResource(MapResource,blob_info->length);
    }
  blob_info->mapped=MagickFalse;
  blob_info->length=0;
  blob_info->offset=0;
  blob_info->eof=MagickFalse;
  blob_info->error=0;
  blob_info->exempt=MagickFalse;
  blob_info->type=UndefinedStream;
  blob_info->file_info.file=(FILE *) NULL;
  data=blob_info->data;
  blob_info->data=(unsigned char *) NULL;
  blob_info->stream=(StreamHandler) NULL;
  blob_info->custom_stream=(CustomStreamInfo *) NULL;
  return(data);
}

extern __attribute__ ((visibility ("default"))) void *RelinquishMagickMemory(void *memory) {
  if (memory == (void *)NULL)
    return ((void *)NULL);
#if !defined(MAGICKCORE_ANONYMOUS_MEMORY_SUPPORT)
  extern MagickMemoryMethods memory_methods;
  memory_methods.destroy_memory_handler(memory);
#else
  extern void *memory_semaphore;
  extern void LockSemaphoreInfo(void *);
  extern size_t SizeOfBlock(void *);
  extern size_t *BlockHeader(void *);
  extern void *NextBlock(void *);
  extern void *PreviousBlock(void *);
  extern size_t PreviousBlockBit;
  extern void RemoveFreeBlock(void *,size_t);
  extern size_t AllocationPolicy(size_t);
  extern void *BlockFooter(void *,size_t);
  extern void InsertFreeBlock(void *,size_t);
  extern void UnlockSemaphoreInfo(void *);
  LockSemaphoreInfo(memory_semaphore);
  assert((SizeOfBlock(memory) % (4 * sizeof(size_t))) == 0);
  assert((*BlockHeader(NextBlock(memory)) & PreviousBlockBit) != 0);
  if ((*BlockHeader(memory) & PreviousBlockBit) == 0) {
    void *previous;
    previous = PreviousBlock(memory);
    RemoveFreeBlock(previous, AllocationPolicy(SizeOfBlock(previous)));
    *BlockHeader(previous) = (SizeOfBlock(previous) + SizeOfBlock(memory)) |
                             (*BlockHeader(previous) & ~SizeMask);
    memory = previous;
  }
  if ((*BlockHeader(NextBlock(NextBlock(memory))) & PreviousBlockBit) == 0) {
    void *next;
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

MagickExport void *ImagesToBlob(const ImageInfo *image_info,Image *images,
  size_t *length,ExceptionInfo *exception)
{
  const MagickInfo
    *magick_info;

  ImageInfo
    *clone_info;

  MagickBooleanType
    status;

  void
    *blob;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,__FILE__,__func__,__LINE__,"%s",
      image_info->filename);
  assert(images != (Image *) NULL);
  assert(images->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  *length=0;
  blob=(unsigned char *) NULL;
  clone_info=CloneImageInfo(image_info);
  (void) SetImageInfo(clone_info,(unsigned int) GetImageListLength(images),
    exception);
  if (*clone_info->magick != '\0')
    (void) CopyMagickString(images->magick,clone_info->magick,MagickPathExtent);
  magick_info=GetMagickInfo(images->magick,exception);
  if (magick_info == (const MagickInfo *) NULL)
    {
      (void) ThrowMagickException(exception,__FILE__,__func__,__LINE__,
        MissingDelegateError,"NoDecodeDelegateForThisImageFormat","`%s'",
        images->magick);
      clone_info=DestroyImageInfo(clone_info);
      return(blob);
    }
  if (GetMagickAdjoin(magick_info) == MagickFalse)
    {
      clone_info=DestroyImageInfo(clone_info);
      return(ImageToBlob(image_info,images,length,exception));
    }
  (void) CopyMagickString(clone_info->magick,images->magick,MagickPathExtent);
  if (GetMagickBlobSupport(magick_info) != MagickFalse)
    {
      /*
        Native blob support for this images format.
      */
      clone_info->length=0;
      clone_info->blob=(void *) AcquireQuantumMemory(8*8192,
        sizeof(unsigned char));
      if (clone_info->blob == (void *) NULL)
        (void) ThrowMagickException(exception,__FILE__,__func__,__LINE__,
          ResourceLimitError,"MemoryAllocationFailed","`%s'",images->filename);
      else
        {
          (void) CloseBlob(images);
          images->blob->exempt=MagickTrue;
          *images->filename='\0';
          status=WriteImages(clone_info,images,images->filename,exception);
          *length=images->blob->length;
          blob=DetachBlob(images->blob);
          if (blob == (void *) NULL)
            clone_info->blob=RelinquishMagickMemory(clone_info->blob);
          else if (status == MagickFalse)
            blob=RelinquishMagickMemory(blob);
          else
            blob=ResizeQuantumMemory(blob,*length+1,sizeof(unsigned char));
        }
    }
  else
    {
      char
        filename[4096],
        unique[4096];

      int
        file;

      /*
        Write file to disk in blob images format.
      */
      file=AcquireUniqueFileResource(unique);
      if (file == -1)
        {
          ThrowFileException(exception,FileOpenError,"UnableToWriteBlob",
            image_info->filename);
        }
      else
        {
          clone_info->file=fdopen(file,"wb");
          if (clone_info->file != (FILE *) NULL)
            {
              (void) FormatLocaleString(filename,4096,"%s:%s",
                images->magick,unique);
              status=WriteImages(clone_info,images,filename,exception);
              (void) CloseBlob(images);
              (void) fclose(clone_info->file);
              if (status != MagickFalse)
                blob=FileToBlob(unique,~0UL,length,exception);
            }
          (void) RelinquishUniqueFileResource(unique);
        }
    }
  clone_info=DestroyImageInfo(clone_info);
  return(blob);
}
