#include <cerrno>
#include <cstddef>
#include <cstring>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include <sys/types.h>

// from: MagickCore/studio.h:87 (empty for C++)
#define magick_restrict

// from: MagickCore/method-attribute.h:66-73
#if defined(__clang__) || (__GNUC__ >= 4)
#define MagickExport __attribute__ ((visibility ("default")))
#else
#define MagickExport
#endif

// from: MagickCore/method-attribute.h:76
#define MagickCoreSignature  0xabacadabUL

// from: MagickCore/magick-type.h:161-166
typedef enum
{
  UndefinedClass,
  DirectClass,
  PseudoClass
} ClassType;

// from: MagickCore/magick-type.h:168-172
typedef enum
{
  MagickFalse = 0,
  MagickTrue = 1
} MagickBooleanType;

// from: MagickCore/magick-type.h:124-143
typedef ssize_t MagickOffsetType;
typedef size_t MagickSizeType;

// from: MagickCore/magick-type.h:64-89
#define MAGICKCORE_QUANTUM_DEPTH  16
#define MaxColormapSize  65536UL
#define MaxMap  65535UL
typedef unsigned short Quantum;
#define QuantumRange  ((Quantum) 65535)
#define QuantumScale  ((double) 1.0/(double) QuantumRange)

// from: MagickCore/magick-type.h:152
typedef MagickSizeType QuantumAny;

// from: MagickCore/exception.h:28-99
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

// from: MagickCore/exception.h:102-119
typedef struct _ExceptionInfo
{
  ExceptionType
    severity;

  int
    error_number;

  char
    reason[256],
    description[256];

  void
    *semaphore;

  unsigned long
    signature;
} ExceptionInfo;

// from: MagickCore/geometry.h:28-44
typedef enum
{
  UndefinedGravity,
  ForgetGravity,
  NorthWestGravity,
  NorthGravity,
  NorthEastGravity,
  WestGravity,
  CenterGravity,
  EastGravity,
  SouthWestGravity,
  SouthGravity,
  SouthEastGravity,
  StaticGravity,
  CenterSidesGravity
} GravityType;

// from: MagickCore/geometry.h:46-64
typedef struct _RectangleInfo
{
  size_t
    width,
    height,
    x,
    y;
} RectangleInfo;

// from: MagickCore/geometry.h:66-80
typedef struct _PointInfo
{
  double
    x,
    y;
} PointInfo;

// from: MagickCore/geometry.h:82-90
typedef struct _AffineMatrix
{
  double
    sx,
    rx,
    ry,
    sy,
    tx,
    ty;
} AffineMatrix;

// from: MagickCore/pixel.h:38-76
typedef enum
{
  UndefinedChannel = 0x0000,
  RedChannel = 0x0001,
  GrayChannel = 0x0001,
  CyanChannel = 0x0001,
  GreenChannel = 0x0002,
  MagentaChannel = 0x0002,
  BlueChannel = 0x0004,
  YellowChannel = 0x0004,
  BlackChannel = 0x0008,
  AlphaChannel = 0x0010,
  OpacityChannel = 0x0010,
  IndexChannel = 0x0020,
  ReadMaskChannel = 0x0040,
  WriteMaskChannel = 0x0080,
  MetaChannel = 0x0100,
  CompositeMaskChannel = 0x0200,
  CompositeChannels = 0x001F,
  AllChannels = 0X7FFFFFF,
  TrueAlphaChannel = 0x0100,
  RGBChannels = 0x0200,
  GrayChannels = 0x0400,
  SyncChannels = 0x20000,
  DefaultChannels = AllChannels
} ChannelType;

// from: MagickCore/pixel.h:78-106
typedef enum
{
  UndefinedPixelChannel = 0,
  RedPixelChannel = 0,
  CyanPixelChannel = 0,
  GrayPixelChannel = 0,
  GreenPixelChannel = 1,
  MagentaPixelChannel = 1,
  BluePixelChannel = 2,
  YellowPixelChannel = 2,
  BlackPixelChannel = 3,
  AlphaPixelChannel = 4,
  IndexPixelChannel = 5,
  ReadMaskPixelChannel = 6,
  WriteMaskPixelChannel = 7,
  MetaPixelChannel = 8,
  CompositeMaskPixelChannel = 9,
  MetaPixelChannels = 10,
  IntensityPixelChannel = 64,
  CompositePixelChannel = 64,
  SyncPixelChannel = 65
} PixelChannel;

// from: MagickCore/pixel.h:108-120
typedef enum
{
  UndefinedPixelIntensityMethod = 0,
  AveragePixelIntensityMethod,
  BrightnessPixelIntensityMethod,
  LightnessPixelIntensityMethod,
  MSPixelIntensityMethod,
  Rec601LumaPixelIntensityMethod,
  Rec601LuminancePixelIntensityMethod,
  Rec709LumaPixelIntensityMethod,
  Rec709LuminancePixelIntensityMethod,
  RMSPixelIntensityMethod
} PixelIntensityMethod;

// from: MagickCore/pixel.h:122-136
typedef enum
{
  UndefinedInterpolatePixel,
  AverageInterpolatePixel,
  Average9InterpolatePixel,
  Average16InterpolatePixel,
  BackgroundInterpolatePixel,
  BilinearInterpolatePixel,
  BlendInterpolatePixel,
  CatromInterpolatePixel,
  IntegerInterpolatePixel,
  MeshInterpolatePixel,
  NearestInterpolatePixel,
  SplineInterpolatePixel
} PixelInterpolateMethod;

// from: MagickCore/pixel.h:138-144
typedef enum
{
  UndefinedPixelMask = 0x000000,
  ReadPixelMask = 0x000001,
  WritePixelMask = 0x000002,
  CompositePixelMask = 0x000004
} PixelMask;

// from: MagickCore/pixel.h:146-160
typedef enum
{
  UndefinedPixelTrait = 0x000000,
  CopyPixelTrait = 0x000001,
  UpdatePixelTrait = 0x000002,
  BlendPixelTrait = 0x000004,
  UndefinedPixelTraits = 0x000008
} PixelTrait;

// from: MagickCore/pixel.h:162-174
typedef struct _PixelInfo
{
  MagickBooleanType
    mask;

  ChannelType
    channel;

  PixelChannel
    channel_map[64];

  PixelTrait
    channel_traits[64];

  double
    channel_value[64];
} PixelInfo;

// from: MagickCore/colorspace.h:28-56
typedef enum
{
  UndefinedColorspace,
  RGBColorspace,
  XYZColorspace,
  YCbCrColorspace,
  YCCColorspace,
  YIQColorspace,
  YPbPrColorspace,
  YUVColorspace,
  CMYKColorspace,
  HSLColorspace,
  HWBColorspace,
  LABColorspace,
  LCHColorspace,
  LMSColorspace,
  LogColorspace,
  LuvColorspace,
  OHTAColorspace,
  Rec601LumaColorspace,
  Rec601YCbCrColorspace,
  Rec709LumaColorspace,
  Rec709YCbCrColorspace,
  sRGBColorspace,
  HSVColorspace,
  HCLColorspace,
  HCLpColorspace,
  xyYColorspace,
  LinearGrayColorspace,
  scRGBColorspace
} ColorspaceType;

// from: MagickCore/composite.h:28-87 (removed duplicate HardMixCompositeOp)
typedef enum
{
  UndefinedCompositeOp,
  NoCompositeOp,
  ModulusAddCompositeOp,
  AtopCompositeOp,
  BlendCompositeOp,
  BlurAlphaCompositeOp,
  BumpmapCompositeOp,
  ChangeMaskCompositeOp,
  ClearCompositeOp,
  ColorBurnCompositeOp,
  ColorDodgeCompositeOp,
  ColorizeCompositeOp,
  CopyBlackCompositeOp,
  CopyBlueCompositeOp,
  CopyCompositeOp,
  CopyCyanCompositeOp,
  CopyGreenCompositeOp,
  CopyMagentaCompositeOp,
  CopyOpacityCompositeOp,
  CopyRedCompositeOp,
  CopyYellowCompositeOp,
  DarkenCompositeOp,
  DarkenIntensityCompositeOp,
  DifferenceCompositeOp,
  DisplaceCompositeOp,
  DissolveCompositeOp,
  DistortCompositeOp,
  DivideCompositeOp,
  DstCompositeOp,
  ExclusionCompositeOp,
  HardLightCompositeOp,
  HardMixCompositeOp,
  HueCompositeOp,
  InCompositeOp,
  LightenCompositeOp,
  LightenIntensityCompositeOp,
  LinearBurnCompositeOp,
  LinearDodgeCompositeOp,
  LinearLightCompositeOp,
  LuminizeCompositeOp,
  MathematicsCompositeOp,
  MinusCompositeOp,
  ModulateCompositeOp,
  ModulusSubtractCompositeOp,
  MultiplyCompositeOp,
  NoneCompositeOp,
  OutCompositeOp,
  OverCompositeOp,
  OverlayCompositeOp,
  PegtopLightCompositeOp,
  PinLightCompositeOp,
  PlusCompositeOp,
  ReplaceCompositeOp,
  VividLightCompositeOp,
  SaturationCompositeOp,
  ScreenCompositeOp,
  SoftLightCompositeOp,
  SrcCompositeOp,
  SrcAtopCompositeOp,
  SrcInCompositeOp,
  SrcOutCompositeOp,
  SrcOverCompositeOp,
  ThresholdCompositeOp,
  XorCompositeOp,
  StereoCompositeOp,
  FreezeCompositeOp,
  InterpolateCompositeOp,
  NegateCompositeOp,
  ReflectCompositeOp,
  SoftBurnCompositeOp,
  SoftDodgeCompositeOp,
  StampCompositeOp,
  RMSECompositeOp,
  MaskCompositeOp,
  CopyAlphaCompositeOp,
  DivideDstCompositeOp,
  DivSrcCompositeOp
} CompositeOperator;

// from: MagickCore/cache-view.h:28-46
typedef enum
{
  UndefinedVirtualPixelMethod,
  BackgroundVirtualPixelMethod,
  DitherVirtualPixelMethod,
  EdgeVirtualPixelMethod,
  MirrorVirtualPixelMethod,
  RandomVirtualPixelMethod,
  TileVirtualPixelMethod,
  TransparentVirtualPixelMethod,
  MaskVirtualPixelMethod,
  BlackVirtualPixelMethod,
  GrayVirtualPixelMethod,
  WhiteVirtualPixelMethod,
  HorizontalTileVirtualPixelMethod,
  VerticalTileVirtualPixelMethod,
  HorizontalTileEdgeVirtualPixelMethod,
  VerticalTileEdgeVirtualPixelMethod,
  CheckerTileVirtualPixelMethod
} VirtualPixelMethod;

// from: MagickCore/cache-view.h:48-49
typedef struct _CacheView
  CacheView;

// from: MagickCore/profile.h:27-34
typedef struct _ProfileInfo
  ProfileInfo;

// from: MagickCore/stream.h:27-30
typedef struct _StreamInfo
  StreamInfo;

// from: MagickCore/image.h:28-42
typedef enum
{
  UndefinedType,
  BilevelType,
  GrayscaleType,
  GrayscaleAlphaType,
  PaletteType,
  PaletteAlphaType,
  TrueColorType,
  TrueColorAlphaType,
  ColorSeparationType,
  ColorSeparationAlphaType,
  OptimizeType,
  PaletteBilevelAlphaType
} ImageType;

// from: MagickCore/image.h:44-55
typedef enum
{
  UndefinedInterlace,
  NoInterlace,
  LineInterlace,
  PlaneInterlace,
  PartitionInterlace,
  GIFInterlace,
  JPEGInterlace,
  PNGInterlace
} InterlaceType;

// from: MagickCore/image.h:56-67
typedef enum
{
  UndefinedOrientation,
  TopLeftOrientation,
  TopRightOrientation,
  BottomRightOrientation,
  BottomLeftOrientation,
  LeftTopOrientation,
  RightTopOrientation,
  RightBottomOrientation,
  LeftBottomOrientation
} OrientationType;

// from: MagickCore/image.h:69-75
typedef enum
{
  UndefinedResolution,
  PixelsPerInchResolution,
  PixelsPerCentimeterResolution
} ResolutionType;

// from: MagickCore/image.h:76-82
typedef struct _PrimaryInfo
{
  double
    x,
    y,
    z;
} PrimaryInfo;

// from: MagickCore/image.h:84-91
typedef struct _SegmentInfo
{
  double
    x1,
    y1,
    x2,
    y2;
} SegmentInfo;

// from: MagickCore/image.h:93-99
typedef enum
{
  UndefinedTransmitType,
  FileTransmitType,
  BlobTransmitType,
  StreamTransmitType,
  ImageTransmitType
} TransmitType;

// from: MagickCore/image.h:101-109
typedef struct _ChromaticityInfo
{
  PrimaryInfo
    red_primary,
    green_primary,
    blue_primary,
    white_point;
} ChromaticityInfo;

// from: MagickCore/compress.h:27-38
typedef enum
{
  UndefinedCompression,
  BZipCompression,
  FaxCompression,
  Group4Compression,
  Group3Compression,
  JBIG1Compression,
  JBIG2Compression,
  JPEG2000Compression,
  JPEGCompression,
  LosslessJPEGCompression,
  LosslessWebPCompression,
  LZMACompression,
  LZWCompression,
  NoCompression,
  PizCompression,
  Pxr24Compression,
  RLECompression,
  WebPCompression,
  ZipCompression,
  ZipSCompression,
  DXTCompression,
  DXTCCompression,
  DXTRCompression,
  DXT5RGBCompression,
  BC4Compression,
  BC5Compression,
  WebPLLCompression,
  WebPLCompression
} CompressionType;

// from: MagickCore/timer.h:27-34
typedef struct _Timer
{
  double
    user,
    elapsed;
} Timer;

// from: MagickCore/image.h:131-290 (partial - key fields only)
typedef struct _Image
{
  ClassType
    storage_class;

  ColorspaceType
    colorspace;

  CompressionType
    compression;

  size_t
    quality;

  OrientationType
    orientation;

  MagickBooleanType
    taint;

  MagickBooleanType
    matte;

  size_t
    columns,
    rows,
    depth;

  double
    gamma;

  size_t
    colors;

  ChannelType
    channel;

  ImageType
    type;

  ResolutionType
    resolution;

  double
    x_resolution,
    y_resolution;

  RectangleInfo
    page;

  AffineMatrix
    affine;

  GravityType
    gravity;

  ColorspaceType
    matte_color;

  char
    filename[256],
    magick[256],
    exception_reason[256];

  MagickBooleanType
    ping;

  size_t
    scene;

  size_t
    delay;

  size_t
    dispose;

  size_t
    iterations;

  ImageType
    matte_type;

  InterlaceType
    interlace;

  MagickBooleanType
    endian;

  PixelInfo
    background_color,
    border_color,
    matte_color_value,
    transparent_color;

  ProfileInfo
    *profile;

  StreamInfo
    *stream;

  Timer
    timer;

  MagickSizeType
    extent;

  void
    *cache;

  void
    *pixels;

  MagickBooleanType
    progress_monitor_set;

  int
    (*progress_monitor)(const char *,const MagickOffsetType,const MagickSizeType,void *);

  void
    *client_data;

  void
    (*destroy)(void *);

  unsigned long
    signature;

  size_t number_channels, number_meta_channels, metacontent_extent;
} Image;

// from: MagickCore/memory_.h:37-69
typedef void
  *(*AcquireMemoryHandler)(size_t),
  (*DestroyMemoryHandler)(void *),
  *(*ResizeMemoryHandler)(void *,size_t),
  *(*AcquireAlignedMemoryHandler)(const size_t,const size_t),
  (*RelinquishAlignedMemoryHandler)(void *);

// from: MagickCore/memory.c:147-161
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

// from: MagickCore/monitor.h:25-27
typedef MagickBooleanType
  (*MagickProgressMonitor)(const char *,const MagickOffsetType,
    const MagickSizeType,void *);

// from: MagickCore/resource_.h:28-42
typedef enum
{
  UndefinedResource,
  AreaResource,
  DiskResource,
  FileResource,
  MapResource,
  MemoryResource,
  HeightResource,
  WidthResource,
  ListLengthResource,
  ThreadResource
} ResourceType;

// from: MagickCore/memory.c:205-213
static MagickMemoryMethods
  memory_methods =
  {
    (AcquireMemoryHandler) malloc,
    (ResizeMemoryHandler) realloc,
    (DestroyMemoryHandler) free,
    (AcquireAlignedMemoryHandler) NULL,
    (RelinquishAlignedMemoryHandler) NULL
  };

extern MagickExport void
  *AcquireQuantumMemory(const size_t,const size_t),
  *RelinquishMagickMemory(void *);

// from: MagickCore/cache-view.h:51-98
extern MagickExport CacheView
  *AcquireAuthenticCacheView(const Image *,ExceptionInfo *),
  *AcquireVirtualCacheView(const Image *,ExceptionInfo *),
  *DestroyCacheView(CacheView *);

extern MagickExport const Quantum
  *GetCacheViewVirtualPixels(const CacheView *,const ssize_t,const ssize_t,
    const size_t,const size_t,ExceptionInfo *);

extern MagickExport MagickBooleanType
  SyncCacheViewAuthenticPixels(CacheView *,ExceptionInfo *);

extern MagickExport Quantum
  *QueueCacheViewAuthenticPixels(CacheView *,const ssize_t,const ssize_t,
    const size_t,const size_t,ExceptionInfo *);

// from: MagickCore/image.h:307-370 (partial)
extern MagickExport Image
  *CloneImage(const Image *,const size_t,const size_t,const MagickBooleanType,
    ExceptionInfo *),
  *DestroyImage(Image *);

extern MagickExport MagickBooleanType
  SetImageStorageClass(Image *,const ClassType,ExceptionInfo *);

// from: MagickCore/log.h:51-54
extern MagickExport MagickBooleanType
  IsEventLogging(void);

extern MagickExport void
  LogMagickEvent(const int, const char *, const char *, const size_t, const char *, ...);

extern MagickExport MagickSizeType
  GetMagickResourceLimit(const ResourceType);

// from: MagickCore/string_.h:27-30
extern MagickExport const char
  *GetExceptionMessage(const int);

// from: MagickCore/log.h:57-58
#define GetMagickModule() __FILE__, __func__, (unsigned long)__LINE__
#define TraceEvent  0

// from: MagickCore/exception.h
extern MagickExport int ThrowMagickException(ExceptionInfo *,const char *,const char *,const size_t, const ExceptionType,const char *,const char *,...);

static inline double GetPixelIntensity(const Image *image,const Quantum *pixel);

static inline double GetPixelAlpha(const Image *image,const Quantum *pixel);

static inline void SetPixelChannel(Image *image,PixelChannel channel, const double value,Quantum *pixel);

static inline PixelChannel GetPixelChannelChannel(const Image *image,size_t i);

static inline PixelTrait GetPixelChannelTraits(const Image *image, PixelChannel channel);

// from: MagickCore/pixel-accessor.h:84-108
static inline size_t GetPixelChannels(const Image *magick_restrict image) {
  return (image->number_channels);
}

// from: MagickCore/quantum.h:127-130
static inline unsigned char ScaleQuantumToChar(const Quantum quantum)
{
  return((unsigned char) (quantum >> 8));
}

static inline Quantum ClampToQuantum(const double value)
{
  if (value <= 0.0)
    return((Quantum) 0);
  if (value >= (double) QuantumRange)
    return((Quantum) QuantumRange);
  return((Quantum) (value + 0.5));
}

// from: MagickCore/memory-private.h:27-30
static inline double MagickSafeReciprocal(const double value)
{
  return(value == 0.0 ? 0.0 : 1.0/value);
}

// from: MagickCore/geometry.h:92-95
static inline size_t MagickMax(const size_t x,const size_t y)
{
  return(x > y ? x : y);
}

// from: MagickCore/color-private.h:27-30
static inline double BlurGaussian(const double distance,const double sigma)
{
  return(exp(-(distance*distance)/(2.0*sigma*sigma)));
}

// from: MagickCore/color-private.h:33-36
static inline double BlurDistance(const ssize_t x1,const ssize_t y1,
  const ssize_t x2,const ssize_t y2)
{
  return(sqrt((double) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))));
}

// from: MagickCore/monitor-private.h:27-30
extern MagickExport MagickBooleanType
  SetImageProgress(const Image *,const char *,const MagickOffsetType,
    const MagickSizeType);

// from: MagickCore/thread-private.h:27-30
extern MagickExport int
  GetOpenMPThreadId(void);

// from: MagickCore/exception.h:130-133
extern MagickExport void
  SetMagickExceptionInfo(ExceptionInfo *,const ExceptionType,const char *);

// from: effect.c:897 (OffsetInfo definition)
typedef struct _OffsetInfo
{
  ssize_t
    x,
    y;
} OffsetInfo;

// from: exception-private.h
#define ThrowImageException(severity,tag) \
{ \
  (void) ThrowMagickException(exception,GetMagickModule(),severity,tag, \
    "`%s'",image->filename); \
  return((Image *) NULL); \
}

static inline MagickBooleanType
HeapOverflowSanityCheckGetSize(const size_t count, const size_t quantum,
                               size_t *const extent) {
  size_t length;

  if ((count == 0) || (quantum == 0))
    return (MagickTrue);
  length = count * quantum;
  if (quantum != (length / count)) {
    errno = ENOMEM;
    return (MagickTrue);
  }
  if (extent != NULL)
    *extent = length;
  return (MagickFalse);
}

static double **DestroyBilateralTLS(const size_t number_threads,
  double **weights)
{
  ssize_t
    i;

  assert(weights != (double **) NULL);
  for (i=0; i <= (ssize_t) number_threads; i++)
    if (weights[i] != (double *) NULL)
      weights[i]=(double *) RelinquishMagickMemory(weights[i]);
  weights=(double **) RelinquishMagickMemory(weights);
  return(weights);
}

static double **AcquireBilateralTLS(const size_t number_threads,
  const size_t width,const size_t height)
{
  double
    **weights;

  size_t
    count;

  ssize_t
    i;
  
  if (HeapOverflowSanityCheckGetSize(height,sizeof(**weights),&count) != MagickFalse)
    return((double **) NULL);

  weights=(double **) AcquireQuantumMemory(number_threads+1,sizeof(*weights));
  if (weights == (double **) NULL)
    return((double **) NULL);
  (void) memset(weights,0,(number_threads+1)*sizeof(*weights));
  for (i=0; i <= (ssize_t) number_threads; i++)
  {
    weights[i]=(double *) AcquireQuantumMemory(width,count);
    if (weights[i] == (double *) NULL)
      return(DestroyBilateralTLS(number_threads,weights));
  }
  return(weights);
}

MagickExport Image *BilateralBlurImage(const Image *image,const size_t width,
  const size_t height,const double intensity_sigma,const double spatial_sigma,
  ExceptionInfo *exception)
{
#define MaxIntensity  (255)
#define BilateralBlurImageTag  "Blur/Image"

  CacheView
    *blur_view,
    *image_view;

  double
    intensity_gaussian[2*(MaxIntensity+1)],
    *spatial_gaussian,
    **weights;

  Image
    *blur_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  OffsetInfo
    mid;

  size_t
    number_threads;

  ssize_t
    w,
    y;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  blur_image=CloneImage(image,0,0,MagickTrue,exception);
  if (blur_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(blur_image,DirectClass,exception) == MagickFalse)
    {
      blur_image=DestroyImage(blur_image);
      return((Image *) NULL);
    }
  number_threads=(size_t) GetMagickResourceLimit(ThreadResource);
  weights=AcquireBilateralTLS(number_threads,MagickMax(width,1),
    MagickMax(height,1));
  if (weights == (double **) NULL)
    {
      blur_image=DestroyImage(blur_image);
      ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
    }
  for (w=(-MaxIntensity); w < MaxIntensity; w++)
    intensity_gaussian[w+MaxIntensity]=BlurGaussian((double) w,intensity_sigma);
  spatial_gaussian=weights[number_threads];
  {
    ssize_t
      n,
      v;

    n=0;
    mid.x=(ssize_t) (MagickMax(width,1)/2L);
    mid.y=(ssize_t) (MagickMax(height,1)/2L);
    for (v=0; v < (ssize_t) MagickMax(height,1); v++)
    {
      ssize_t
        u;

      for (u=0; u < (ssize_t) MagickMax(width,1); u++)
        spatial_gaussian[n++]=BlurGaussian(BlurDistance(0,0,u-mid.x,v-mid.y),
          spatial_sigma);
    }
  }
  /*
    Bilateral blur image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  blur_view=AcquireAuthenticCacheView(blur_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,blur_image,blur_image->rows,1)
#endif
  for (y=0; y < (ssize_t) blur_image->rows; y++)
  {
    const int
      id = GetOpenMPThreadId();

    Quantum
      *magick_restrict q;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    q=QueueCacheViewAuthenticPixels(blur_view,0,y,blur_image->columns,1,
      exception);
    if (q == (Quantum *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) blur_image->columns; x++)
    {
      const Quantum
        *magick_restrict p,
        *magick_restrict r;

      double
        gamma,
        pixel;

      ssize_t
        i,
        n,
        u,
        v;

      /*
        Tonal weighting preserves edges while smoothing in the flat regions.
      */
      p=GetCacheViewVirtualPixels(image_view,x-mid.x,y-mid.y,MagickMax(width,1),
        MagickMax(height,1),exception);
      if (p == (const Quantum *) NULL)
        break;
      p+=(ptrdiff_t) (GetPixelChannels(image)*MagickMax(width,1)*(size_t) mid.y+
        GetPixelChannels(image)*(size_t) mid.x);
      n=0;
      for (v=0; v < (ssize_t) MagickMax(height,1); v++)
      {
        for (u=0; u < (ssize_t) MagickMax(width,1); u++)
        {
          double
            intensity;

          r=p+(ssize_t) (GetPixelChannels(image)*MagickMax(width,1)*
            (size_t) (mid.y-v)+GetPixelChannels(image)*(size_t) (mid.x-u));
          intensity=ScaleQuantumToChar((const Quantum) GetPixelIntensity(image,r))-
            (double) ScaleQuantumToChar((const Quantum) GetPixelIntensity(image,p));
          if ((intensity >= -MaxIntensity) && (intensity <= MaxIntensity))
            weights[id][n]=intensity_gaussian[(ssize_t) intensity+MaxIntensity]*
              spatial_gaussian[n];
          else
            weights[id][n]=BlurGaussian(intensity,intensity_sigma)*
              BlurGaussian(BlurDistance(x,y,x+u-mid.x,y+v-mid.y),spatial_sigma);
          n++;
        }
      }
      for (i=0; i < (ssize_t) GetPixelChannels(blur_image); i++)
      {
        PixelChannel
          channel;

        PixelTrait
          blur_traits,
          traits;

        channel=GetPixelChannelChannel(image,i);
        traits=GetPixelChannelTraits(image,channel);
        blur_traits=GetPixelChannelTraits(blur_image,channel);
        if ((traits == UndefinedPixelTrait) ||
            (blur_traits == UndefinedPixelTrait))
          continue;
        if ((blur_traits & CopyPixelTrait) != 0)
          {
            SetPixelChannel(blur_image,channel,p[i],q);
            continue;
          }
        pixel=0.0;
        gamma=0.0;
        n=0;
        if ((blur_traits & BlendPixelTrait) == 0)
          {
            /*
              No alpha blending.
            */
            for (v=0; v < (ssize_t) MagickMax(height,1); v++)
            {
              for (u=0; u < (ssize_t) MagickMax(width,1); u++)
              {
                r=p+GetPixelChannels(image)*MagickMax(width,1)*(size_t)
                  (mid.y-v)+GetPixelChannels(image)*(size_t) (mid.x-u);
                pixel+=weights[id][n]*(double) r[i];
                gamma+=weights[id][n];
                n++;
              }
            }
            SetPixelChannel(blur_image,channel,ClampToQuantum(
              MagickSafeReciprocal(gamma)*pixel),q);
            continue;
          }
        /*
          Alpha blending.
        */
        for (v=0; v < (ssize_t) MagickMax(height,1); v++)
        {
          for (u=0; u < (ssize_t) MagickMax(width,1); u++)
          {
            double
              alpha,
              beta;

            r=p+GetPixelChannels(image)*MagickMax(width,1)*(size_t) (mid.y-v)+
              GetPixelChannels(image)*(size_t) (mid.x-u);
            alpha=(double) (QuantumScale*(double) GetPixelAlpha(image,p));
            beta=(double) (QuantumScale*(double) GetPixelAlpha(image,r));
            pixel+=weights[id][n]*(double) r[i];
            gamma+=weights[id][n]*alpha*beta;
            n++;
          }
        }
        SetPixelChannel(blur_image,channel,ClampToQuantum(
          MagickSafeReciprocal(gamma)*pixel),q);
      }
      q+=(ptrdiff_t) GetPixelChannels(blur_image);
    }
    if (SyncCacheViewAuthenticPixels(blur_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != 0)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,BilateralBlurImageTag,progress,
          image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  blur_image->type=image->type;
  blur_view=DestroyCacheView(blur_view);
  image_view=DestroyCacheView(image_view);
  weights=DestroyBilateralTLS(number_threads,weights);
  if (status == MagickFalse)
    blur_image=DestroyImage(blur_image);
  return(blur_image);
}

extern __attribute__ ((visibility ("default"))) void *RelinquishMagickMemory(void *memory) {
  if (memory == (void *)NULL)
    return ((void *)NULL);
#if !defined(MAGICKCORE_ANONYMOUS_MEMORY_SUPPORT)
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
