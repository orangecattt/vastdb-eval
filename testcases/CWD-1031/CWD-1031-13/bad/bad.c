#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <locale.h>
#include <sys/types.h>

#if defined(__clang__) || (__GNUC__ >= 4)
#  define MagickExport __attribute__ ((visibility ("default")))
#  define MagickPrivate __attribute__((visibility("hidden")))
#else
#  define MagickExport
#  define MagickPrivate
#endif

#define magick_attribute __attribute__

#define MagickPathExtent  4096
#define MagickMaxRecursionDepth  600

typedef enum { MagickFalse = 0, MagickTrue = 1 } MagickBooleanType;
typedef unsigned int MagickStatusType;

typedef enum { OptionError = 410, DrawError = 460 } ExceptionType;
typedef enum { UniformNoise = 0 } NoiseType;
typedef enum { UndefinedAlign, LeftAlign, CenterAlign, RightAlign } AlignType;
typedef enum { UndefinedStretch, NormalStretch } StretchType;
typedef enum { UndefinedStyle, NormalStyle } StyleType;
typedef enum { UndefinedGravity, CenterGravity } GravityType;
typedef enum { OverCompositeOp, CopyAlphaCompositeOp, DissolveCompositeOp } CompositeOperator;
typedef enum { UndefinedChannel = 0, DefaultChannels = 0x7FFFFFF } ChannelType;
typedef enum { UndefinedPixelTrait = 0 } PixelTrait;

typedef enum
{
  UndefinedClass,
  DirectClass,
  PseudoClass
} ClassType;

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

typedef enum
{
  UndefinedEndian,
  LSBEndian,
  MSBEndian
} EndianType;

typedef enum
{
  UnrecognizedDispose,
  UndefinedDispose = 0,
  NoneDispose = 1,
  BackgroundDispose = 2,
  PreviousDispose = 3
} DisposeType;

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

typedef struct _ErrorInfo
{
  double
    mean_error_per_pixel,
    normalized_mean_error,
    normalized_maximum_error;
} ErrorInfo;

typedef enum
{
  UndefinedTimerState,
  StoppedTimerState,
  RunningTimerState
} TimerState;

typedef struct _Timer
{
  double
    start,
    stop,
    total;
} Timer;

typedef struct _TimerInfo
{
  Timer
    user,
    elapsed;

  TimerState
    state;

  size_t
    signature;
} TimerInfo;

typedef MagickBooleanType
  (*MagickProgressMonitor)(const char *,const long long,
    const unsigned long long,void *);

typedef struct _ProfileInfo
  ProfileInfo;

typedef struct _ExceptionInfo ExceptionInfo;
typedef struct _Image Image;
typedef struct _ImageInfo ImageInfo;
typedef struct _DrawInfo DrawInfo;
typedef struct _PixelInfo PixelInfo;
typedef struct _SemaphoreInfo SemaphoreInfo;
typedef struct _BlobInfo BlobInfo;
typedef struct _Ascii85Info Ascii85Info;
typedef struct _PixelChannelMap PixelChannelMap;
typedef struct _RectangleInfo RectangleInfo;
typedef struct _AffineMatrix AffineMatrix;
typedef struct _GeometryInfo GeometryInfo;
typedef struct _CacheView CacheView;
typedef struct _MSLGroupInfo MSLGroupInfo;
typedef struct _MSLInfo MSLInfo;

typedef unsigned char xmlChar;
typedef struct _xmlParserCtxt { void *_private; } *xmlParserCtxtPtr;

typedef enum {
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
  ExceptionEvent = 0x00100, /* Log Errors and Warnings immediately */
  ImageEvent = 0x00200,
  LocaleEvent = 0x00400,
  ModuleEvent = 0x00800, /* Log coder and filter modules */
  PixelEvent = 0x01000,
  PolicyEvent = 0x02000,
  ResourceEvent = 0x04000,
  TraceEvent = 0x08000,
  TransformEvent = 0x10000,
  UserEvent = 0x20000,
  WandEvent = 0x40000, /* Log MagickWand */
  X11Event = 0x80000,
  CommandEvent = 0x100000, /* Log Command Processing (CLI & Scripts) */
  AllEvents = 0x7fffffff
} LogEventType;

typedef enum {
  UndefinedCompliance,
  NoCompliance = 0x0000,
  CSSCompliance = 0x0001,
  SVGCompliance = 0x0001,
  X11Compliance = 0x0002,
  XPMCompliance = 0x0004,
  MVGCompliance = 0x0008,
  AllCompliance = 0x7fffffff
} ComplianceType;

typedef enum {
  UndefinedIlluminant = 5,
  AIlluminant = 0,
  BIlluminant = 1,
  CIlluminant = 2,
  D50Illuminant = 3,
  D55Illuminant = 4,
  D65Illuminant = 5,
  D75Illuminant = 6,
  EIlluminant = 7,
  F2Illuminant = 8,
  F7Illuminant = 9,
  F11Illuminant = 10
} IlluminantType;

typedef enum {
  UndefinedPathUnits,
  UserSpace,
  UserSpaceOnUse,
  ObjectBoundingBox
} ClipPathUnits;

typedef enum {
  UndefinedDecoration,
  NoDecoration,
  UnderlineDecoration,
  OverlineDecoration,
  LineThroughDecoration
} DecorationType;

typedef enum {
  UndefinedDirection,
  RightToLeftDirection,
  LeftToRightDirection,
  TopToBottomDirection
} DirectionType;

typedef enum {
  UndefinedRule,
  EvenOddRule,
  NonZeroRule
} FillRule;

typedef enum {
  UndefinedLayer,
  CoalesceLayer,
  CompareAnyLayer,
  CompareClearLayer,
  CompareOverlayLayer,
  DisposeLayer,
  OptimizeLayer,
  OptimizeImageLayer,
  OptimizePlusLayer,
  OptimizeTransLayer,
  RemoveDupsLayer,
  RemoveZeroLayer,
  CompositeLayer,
  MergeLayer,
  FlattenLayer,
  MosaicLayer,
  TrimBoundsLayer
} LayerMethod;

typedef enum { UndefinedGradient, LinearGradient, RadialGradient } GradientType;

typedef enum { UndefinedCap, ButtCap, RoundCap, SquareCap } LineCap;

typedef enum { UndefinedJoin, MiterJoin, RoundJoin, BevelJoin } LineJoin;

typedef enum {
  UndefinedMethod,
  PointMethod,
  ReplaceMethod,
  FloodfillMethod,
  FillToBorderMethod,
  ResetMethod
} PaintMethod;

typedef enum {
  UndefinedPrimitive,
  AlphaPrimitive,
  ArcPrimitive,
  BezierPrimitive,
  CirclePrimitive,
  ColorPrimitive,
  EllipsePrimitive,
  ImagePrimitive,
  LinePrimitive,
  PathPrimitive,
  PointPrimitive,
  PolygonPrimitive,
  PolylinePrimitive,
  RectanglePrimitive,
  RoundRectanglePrimitive,
  TextPrimitive
} PrimitiveType;

typedef enum {
  UndefinedColorspace,
  CMYColorspace,  /* negated linear RGB colorspace */
  CMYKColorspace, /* CMY with Black separation */
  GRAYColorspace, /* Single Channel greyscale (non-linear) image */
  HCLColorspace,
  HCLpColorspace,
  HSBColorspace,
  HSIColorspace,
  HSLColorspace,
  HSVColorspace, /* alias for HSB */
  HWBColorspace,
  LabColorspace,
  LCHColorspace,   /* alias for LCHuv */
  LCHabColorspace, /* Cylindrical (Polar) Lab */
  LCHuvColorspace, /* Cylindrical (Polar) Luv */
  LogColorspace,
  LMSColorspace,
  LuvColorspace,
  OHTAColorspace,
  Rec601YCbCrColorspace,
  Rec709YCbCrColorspace,
  RGBColorspace,   /* Linear RGB colorspace */
  scRGBColorspace, /* ??? */
  sRGBColorspace,  /* Default: non-linear sRGB colorspace */
  TransparentColorspace,
  xyYColorspace,
  XYZColorspace, /* IEEE Color Reference colorspace */
  YCbCrColorspace,
  YCCColorspace,
  YDbDrColorspace,
  YIQColorspace,
  YPbPrColorspace,
  YUVColorspace,
  LinearGRAYColorspace, /* Single Channel greyscale (linear) image */
  JzazbzColorspace,
  DisplayP3Colorspace,
  Adobe98Colorspace,
  ProPhotoColorspace,
  OklabColorspace,
  OklchColorspace,
  CAT02LMSColorspace
} ColorspaceType;

typedef enum {
  UndefinedCompression,
  B44ACompression,
  B44Compression,
  BZipCompression,
  DXT1Compression,
  DXT3Compression,
  DXT5Compression,
  FaxCompression,
  Group4Compression,
  JBIG1Compression,    /* ISO/IEC std 11544 / ITU-T rec T.82 */
  JBIG2Compression,    /* ISO/IEC std 14492 / ITU-T rec T.88 */
  JPEG2000Compression, /* ISO/IEC std 15444-1 */
  JPEGCompression,
  LosslessJPEGCompression,
  LZMACompression, /* Lempel-Ziv-Markov chain algorithm */
  LZWCompression,
  NoCompression,
  PizCompression,
  Pxr24Compression,
  RLECompression,
  ZipCompression,
  ZipSCompression,
  ZstdCompression,
  WebPCompression,
  DWAACompression,
  DWABCompression,
  BC7Compression,
  BC5Compression,
  LERCCompression /* https://github.com/Esri/lerc */
} CompressionType;

typedef enum { UndefinedReference, GradientReference } ReferenceType;

typedef enum {
  UndefinedSpread,
  PadSpread,
  ReflectSpread,
  RepeatSpread
} SpreadMethod;

typedef enum {
  UndefinedWordBreakType,
  NormalWordBreakType,
  BreakWordBreakType
} WordBreakType;

typedef enum {
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

typedef enum {
  UndefinedInterlace,
  NoInterlace,
  LineInterlace,
  PlaneInterlace,
  PartitionInterlace,
  GIFInterlace,
  JPEGInterlace,
  PNGInterlace
} InterlaceType;

typedef enum {
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

typedef enum {
  UndefinedResolution,
  PixelsPerInchResolution,
  PixelsPerCentimeterResolution
} ResolutionType;

typedef enum {
  UndefinedIntent,
  SaturationIntent,
  PerceptualIntent,
  AbsoluteIntent,
  RelativeIntent
} RenderingIntent;

typedef enum {
  UndefinedFilter,
  PointFilter,
  BoxFilter,
  TriangleFilter,
  HermiteFilter,
  HannFilter,
  HammingFilter,
  BlackmanFilter,
  GaussianFilter,
  QuadraticFilter,
  CubicFilter,
  CatromFilter,
  MitchellFilter,
  JincFilter,
  SincFilter,
  SincFastFilter,
  KaiserFilter,
  WelchFilter,
  ParzenFilter,
  BohmanFilter,
  BartlettFilter,
  LagrangeFilter,
  LanczosFilter,
  LanczosSharpFilter,
  Lanczos2Filter,
  Lanczos2SharpFilter,
  RobidouxFilter,
  RobidouxSharpFilter,
  CosineFilter,
  SplineFilter,
  LanczosRadiusFilter,
  CubicSplineFilter,
  MagicKernelSharp2013Filter,
  MagicKernelSharp2021Filter,
  SentinelFilter /* a count of all the filters, not a real filter */
} FilterType;

typedef enum {
#undef NoValue
  NoValue = 0x0000,
#undef XValue
  XValue = 0x0001,
  XiValue = 0x0001,
#undef YValue
  YValue = 0x0002,
  PsiValue = 0x0002,
#undef WidthValue
  WidthValue = 0x0004,
  RhoValue = 0x0004,
#undef HeightValue
  HeightValue = 0x0008,
  SigmaValue = 0x0008,
  ChiValue = 0x0010,
  XiNegative = 0x0020,
#undef XNegative
  XNegative = 0x0020,
  PsiNegative = 0x0040,
#undef YNegative
  YNegative = 0x0040,
  ChiNegative = 0x0080,
  PercentValue = 0x1000,   /* '%'  percentage of something */
  AspectValue = 0x2000,    /* '!'  resize no-aspect - special use flag */
  NormalizeValue = 0x2000, /* '!'  ScaleKernelValue() in morphology.c */
  LessValue = 0x4000,      /* '<'  resize smaller - special use flag */
  GreaterValue = 0x8000,   /* '>'  resize larger - spacial use flag */
  MinimumValue = 0x10000,  /* '^'  special handling needed */
  CorrelateNormalizeValue = 0x10000, /* '^' see ScaleKernelValue() */
  AreaValue = 0x20000,         /* '@'  resize to area - special use flag */
  DecimalValue = 0x40000,      /* '.'  floating point numbers found */
  SeparatorValue = 0x80000,    /* 'x'  separator found */
  AspectRatioValue = 0x100000, /* '~'  special handling needed */
  AlphaValue = 0x200000,       /* '/'  alpha */
  MaximumValue = 0x400000,     /* '#'  special handling needed */
#undef AllValues
  AllValues = 0x7fffffff
} GeometryFlags;

typedef enum {
  MagickUndefinedOptions = -1,
  MagickAlignOptions = 0,
  MagickAlphaChannelOptions,
  MagickBooleanOptions,
  MagickCacheOptions,
  MagickChannelOptions,
  MagickClassOptions,
  MagickClipPathOptions,
  MagickCoderOptions,
  MagickColorOptions,
  MagickColorspaceOptions,
  MagickCommandOptions,
  MagickComplexOptions,
  MagickComplianceOptions,
  MagickComposeOptions,
  MagickCompressOptions,
  MagickConfigureOptions,
  MagickDataTypeOptions,
  MagickDebugOptions,
  MagickDecorateOptions,
  MagickDelegateOptions,
  MagickDirectionOptions,
  MagickDisposeOptions,
  MagickDistortOptions,
  MagickDitherOptions,
  MagickEndianOptions,
  MagickEvaluateOptions,
  MagickFillRuleOptions,
  MagickFilterOptions,
  MagickFontOptions,
  MagickFontsOptions,
  MagickFormatOptions,
  MagickFunctionOptions,
  MagickGradientOptions,
  MagickGravityOptions,
  MagickIntensityOptions,
  MagickIntentOptions,
  MagickInterlaceOptions,
  MagickInterpolateOptions,
  MagickKernelOptions,
  MagickLayerOptions,
  MagickLineCapOptions,
  MagickLineJoinOptions,
  MagickListOptions,
  MagickLocaleOptions,
  MagickLogEventOptions,
  MagickLogOptions,
  MagickMagicOptions,
  MagickMethodOptions,
  MagickMetricOptions,
  MagickMimeOptions,
  MagickModeOptions,
  MagickModuleOptions,
  MagickMorphologyOptions,
  MagickNoiseOptions,
  MagickOrientationOptions,
  MagickPixelChannelOptions,
  MagickPixelIntensityOptions,
  MagickPixelMaskOptions,
  MagickPixelTraitOptions,
  MagickPolicyOptions,
  MagickPolicyDomainOptions,
  MagickPolicyRightsOptions,
  MagickPreviewOptions,
  MagickPrimitiveOptions,
  MagickQuantumFormatOptions,
  MagickResolutionOptions,
  MagickResourceOptions,
  MagickSparseColorOptions,
  MagickStatisticOptions,
  MagickStorageOptions,
  MagickStretchOptions,
  MagickStyleOptions,
  MagickThresholdOptions,
  MagickTypeOptions,
  MagickValidateOptions,
  MagickVirtualPixelOptions,
  MagickWeightOptions,
  MagickAutoThresholdOptions,
  MagickToolOptions,
  MagickCLIOptions,
  MagickIlluminantOptions,
  MagickWordBreakOptions,
  MagickPagesizeOptions
} CommandOption;

typedef size_t MagickSizeType;
typedef double MagickDoubleType;
typedef MagickDoubleType MagickRealType;
typedef float MagickFloatType;
typedef MagickFloatType Quantum;

struct _AffineMatrix {
  double sx, rx, ry, sy, tx, ty;
};

struct _GeometryInfo {
  double rho, sigma, xi, psi, chi;
};

struct _RectangleInfo {
  size_t width, height;
  long x, y;
};

typedef struct _PointInfo {
  double x, y;
} PointInfo;

typedef struct _PixelInfo {
  ClassType storage_class;

  ColorspaceType colorspace;

  PixelTrait alpha_trait;

  double fuzz;

  size_t depth;

  MagickSizeType count;

  MagickRealType red, green, blue, black, alpha, index;
} PixelInfo;

typedef struct _SegmentInfo {
  double x1, y1, x2, y2;
} SegmentInfo;

typedef struct _StopInfo {
  PixelInfo color;
  double offset;
} StopInfo;

struct _ExceptionInfo {
  ExceptionType severity;
  int error_number;
  char *reason, *description;
  void *exceptions;
  MagickBooleanType relinquish;
  SemaphoreInfo *semaphore;
  size_t signature;
};

struct _ImageInfo {
  CompressionType
      compression; /* compression method when reading/saving image */

  OrientationType orientation; /* orientation setting */

  MagickBooleanType
      temporary, /* image file to be deleted after read "ephemeral:" */
      adjoin,    /* save images to separate scene files */
      affirm, antialias;

  char *size,         /* image generation size */
      *extract,       /* crop/resize string on image read */
      *page, *scenes; /* scene numbers that is to be read in */

  size_t scene,      /* starting value for image save numbering */
      number_scenes, /* total number of images in list - for escapes */
      depth;         /* current read/save depth of images */

  InterlaceType interlace; /* interlace for image write */

  EndianType endian; /* integer endian order for raw image data */

  ResolutionType units; /* density pixels/inch or pixel/cm */

  size_t quality; /* compression quality */

  char *sampling_factor, /* Chroma subsampling ratio string */
      *server_name,      /* X windows server name - display/animate */
      *font,             /* DUP for draw_info */
      *texture,          /* montage/display background tile */
      *density;          /* DUP for image and draw_info */

  double pointsize, fuzz; /* current color fuzz attribute */

  PixelInfo alpha_color, /* deprecated */
      background_color,  /* user set background color */
      border_color,      /* user set border color */
      transparent_color; /* color for transparent index in color tables */
                         /* NB: fill color is only needed in draw_info! */
                         /* the same for undercolor (for font drawing) */

  MagickBooleanType dither, /* dither enable-disable */
      monochrome;           /* read/write pcl,pdf,ps,xps as monochrome image */

  ColorspaceType colorspace;

  CompositeOperator compose;

  ImageType type;

  MagickBooleanType ping, /* fast read image attributes, not image data */
      verbose;            /* verbose output enable/disable */

  ChannelType channel;

  void *options; /* splay tree of global options */

  void *profile;

  MagickBooleanType synchronize;

  MagickProgressMonitor progress_monitor;

  void *client_data, *cache;

  FILE *file;

  void *blob;

  size_t length;

  char magick[MagickPathExtent],  /* image file format (file magick) */
      unique[MagickPathExtent],   /* unique temporary filename - delegates */
      filename[MagickPathExtent]; /* filename when reading/writing image */

  MagickBooleanType debug;

  size_t signature;

  PixelInfo matte_color; /* matte (frame) color */
};

struct _MSLGroupInfo {
  char *id;
  size_t numImages;
  Image *image;
};


typedef struct _PrimaryInfo {
  double x, y, z;
} PrimaryInfo;

typedef struct _ChromaticityInfo
{
  PrimaryInfo
    red_primary,
    green_primary,
    blue_primary,
    white_point;
} ChromaticityInfo;

struct _Image {
  ClassType storage_class;

  ColorspaceType colorspace; /* colorspace of image data */

  CompressionType compression; /* compression of image when read/write */

  size_t quality; /* compression quality setting, meaning varies */

  OrientationType orientation; /* photo orientation of image */

  MagickBooleanType taint; /* has image been modified since reading */

  size_t columns,  /* physical size of image */
      rows, depth, /* depth of image on read/write */
      colors;      /* Size of color table, or actual color count */
                   /* Only valid if image is not DirectClass */

  PixelInfo *colormap, alpha_color, /* deprecated */
      background_color,             /* current background color attribute */
      border_color,                 /* current bordercolor attribute */
      transparent_color; /* color for 'transparent' color index in GIF */

  double gamma;

  ChromaticityInfo chromaticity;

  RenderingIntent rendering_intent;

  void *profiles;

  ResolutionType units; /* resolution/density  ppi or ppc */

  char *montage, *directory, *geometry;

  ssize_t offset; /* ??? */

  PointInfo resolution; /* image resolution/density */

  RectangleInfo page, /* virtual canvas size and offset of image */
      extract_info;

  double fuzz; /* current color fuzz attribute - move to image_info */

  FilterType filter; /* resize/distort filter to apply */

  PixelIntensityMethod
      intensity; /* method to generate an intensity value from a pixel */

  InterlaceType interlace;

  EndianType endian; /* raw data integer ordering on read/write */

  GravityType gravity; /* Gravity attribute for positioning in image */

  CompositeOperator compose; /* alpha composition method for layered images */

  DisposeType dispose; /* GIF animation disposal method */

  size_t scene, /* index of image in multi-image file */
      delay,    /* Animation delay time */
      duration; /* Total animation duration sum(delay*iterations) */

  ssize_t ticks_per_second; /* units for delay time, default 100 for GIF */

  size_t iterations, /* number of interactions for GIF animations */
      total_colors;

  ssize_t start_loop; /* ??? */

  PixelInterpolateMethod
      interpolate; /* Interpolation of color for between pixel lookups */

  MagickBooleanType black_point_compensation;

  RectangleInfo tile_offset;

  ImageType type;

  MagickBooleanType dither; /* dithering on/off */

  MagickSizeType extent; /* Size of image read from disk */

  MagickBooleanType ping; /* no image data read, just attributes */

  MagickBooleanType read_mask, write_mask;

  PixelTrait alpha_trait; /* is transparency channel defined and active */

  size_t number_channels, number_meta_channels, metacontent_extent;

  ChannelType channel_mask;

  PixelChannelMap *channel_map;

  void *cache;

  ErrorInfo error;

  TimerInfo timer;

  MagickProgressMonitor progress_monitor;

  void *client_data;

  Ascii85Info *ascii85;

  ProfileInfo *generic_profile;

  void *properties, /* general settings, to save with image */
      *artifacts;   /* general operational/coder settings, not saved */

  char filename[MagickPathExtent],       /* images input filename */
      magick_filename[MagickPathExtent], /* given image filename (with read
                                            mods) */
      magick[MagickPathExtent];          /* images file format (file magic) */

  size_t magick_columns, /* size of image when read/created */
      magick_rows;

  BlobInfo *blob; /* image file as in-memory string of 'extent' */

  time_t timestamp;

  MagickBooleanType debug; /* debug output attribute */

  ssize_t reference_count; /* image data sharing memory management */

  SemaphoreInfo *semaphore;

  struct _ImageInfo
      *image_info; /* (Optional) Image belongs to this ImageInfo 'list'
                    * For access to 'global options' when no per-image
                    * attribute, prosperity, or artifact has been set.
                    */

  struct _Image *list, /* Undo/Redo image processing list (for display) */
      *previous,       /* Image list links */
      *next;

  size_t signature;

  PixelInfo matte_color; /* current mattecolor attribute */

  MagickBooleanType composite_mask;

  PixelTrait mask_trait; /* apply the clip or composite mask */

  ChannelType channels;

  time_t ttl;
};

typedef struct _GradientInfo {
  GradientType type;

  RectangleInfo bounding_box;

  SegmentInfo gradient_vector;

  StopInfo *stops;

  size_t number_stops;

  SpreadMethod spread;

  MagickBooleanType debug;

  PointInfo center, radii;

  double radius, angle;

  size_t signature;
} GradientInfo;

typedef struct _ElementReference {
  char *id;

  ReferenceType type;

  GradientInfo gradient;

  struct _ElementReference *previous, *next;

  size_t signature;
} ElementReference;

typedef struct _FrameInfo {
  size_t width, height;

  ssize_t x, y, inner_bevel, outer_bevel;
} FrameInfo;

struct _DrawInfo
{
  char
    *primitive,
    *geometry;

  RectangleInfo
    viewbox;

  AffineMatrix
    affine;

  PixelInfo
    fill,
    stroke,
    undercolor,
    border_color;

  Image
    *fill_pattern,
    *stroke_pattern;

  double
    stroke_width;

  GradientInfo
    gradient;

  MagickBooleanType
    stroke_antialias,
    text_antialias;

  FillRule
    fill_rule;

  LineCap
    linecap;

  LineJoin
    linejoin;

  size_t
    miterlimit;

  double
    dash_offset;

  DecorationType
    decorate;

  CompositeOperator
    compose;

  char
    *text,
    *font,
    *metrics,
    *family;

  size_t
    face;

  StyleType
    style;

  StretchType
    stretch;

  size_t
    weight;

  char
    *encoding;

  double
    pointsize;

  char
    *density;

  AlignType
    align;

  GravityType
    gravity;

  char
    *server_name;

  double
    *dash_pattern;

  char
    *clip_mask;

  SegmentInfo
    bounds;

  ClipPathUnits
    clip_units;

  Quantum
    alpha;

  MagickBooleanType
    render;

  ElementReference
    element_reference;

  double
    kerning,
    interword_spacing,
    interline_spacing;

  DirectionType
    direction;

  MagickBooleanType
    debug;

  size_t
    signature;

  double
    fill_alpha,
    stroke_alpha;

  MagickBooleanType
    clip_path;

  Image
    *clipping_mask;

  ComplianceType
    compliance;

  Image
    *composite_mask;

  char
    *id;

  WordBreakType
    word_break;

  ImageInfo
    *image_info;
};

#define GetMagickModule() __FILE__, __func__, (unsigned long)__LINE__
extern MagickExport MagickBooleanType IsEventLogging(void);
extern MagickExport int LogMagickEvent(const int, const char *, const char *, ...);
extern MagickExport int ThrowMagickException(ExceptionInfo *,const char *,const char *,const size_t, const ExceptionType,const char *,const char *,...);
extern MagickExport ExceptionInfo *AcquireExceptionInfo(void);
extern MagickExport ExceptionInfo *DestroyExceptionInfo(ExceptionInfo *);
extern MagickExport char *DestroyString(char *);
extern MagickExport void CloneString(char **, const char *);
extern MagickExport int LocaleCompare(const char *, const char *);
extern MagickExport double StringToDouble(const char *, char **);
extern MagickExport long StringToLong(const char *);
extern MagickExport DrawInfo *CloneDrawInfo(ImageInfo *, DrawInfo *);
extern MagickExport DrawInfo *DestroyDrawInfo(DrawInfo *);
extern MagickExport void GetAffineMatrix(AffineMatrix *);
extern MagickExport ChannelType SetImageChannelMask(Image *, const int);
extern MagickExport int SetPixelChannelMask(Image *, ChannelType);
extern MagickExport Image *AddNoiseImage(Image *, int, double, ExceptionInfo *);
extern MagickExport char *InterpretImageProperties(const ImageInfo *, const Image *, const char *, ExceptionInfo *);
extern MagickExport Image *CloneImage(const Image *, const size_t, const size_t, const MagickBooleanType, ExceptionInfo *);
extern MagickExport Image *DestroyImage(Image *);
extern MagickExport void SetGeometryInfo(GeometryInfo *);
extern MagickExport Image *AppendImages(Image *, MagickBooleanType, ExceptionInfo *);
extern MagickExport Image *AutoOrientImage(Image *, int, ExceptionInfo *);
extern MagickExport Image *BlurImage(Image *, double, double, ExceptionInfo *);
extern MagickExport void SetGeometry(Image *, RectangleInfo *);
extern MagickExport Image *BorderImage(Image *, RectangleInfo *, CompositeOperator, ExceptionInfo *);
extern MagickExport void GetPixelInfo(Image *, PixelInfo *);
extern MagickExport void CopyMagickString(char *, const char *, const size_t);
extern MagickExport Image *CharcoalImage(Image *, double, double, ExceptionInfo *);
extern MagickExport Image *ChopImage(Image *, RectangleInfo *, ExceptionInfo *);
extern MagickExport Image *ColorizeImage(Image *, const char *, PixelInfo *, ExceptionInfo *);
extern MagickExport int FloodfillPaintImage(Image *, DrawInfo *, PixelInfo *, long, long, MagickBooleanType, ExceptionInfo *);
extern MagickExport int GetOneVirtualPixelInfo(Image *, int, long, long, PixelInfo *, ExceptionInfo *);
extern MagickExport Image *RotateImage(Image *, double, ExceptionInfo *);
extern MagickExport MagickBooleanType SetImageAlpha(Image *, int, ExceptionInfo *);
extern MagickExport CacheView *AcquireAuthenticCacheView(Image *, ExceptionInfo *);
extern MagickExport Quantum *GetCacheViewAuthenticPixels(CacheView *, long, long, size_t, size_t, ExceptionInfo *);
extern MagickExport int GetPixelAlpha(Image *, void *);
extern MagickExport void SetPixelAlpha(Image *, int, void *);
extern MagickExport MagickBooleanType SyncCacheViewAuthenticPixels(CacheView *, ExceptionInfo *);
extern MagickExport CacheView *DestroyCacheView(CacheView *);
extern MagickExport MagickBooleanType CompositeImage(Image *, Image *, CompositeOperator, MagickBooleanType, long, long, ExceptionInfo *);
extern MagickExport Image *NewImageList(void);
extern MagickExport const char *GetImageProperty(const Image *, const char *, ExceptionInfo *);
extern MagickExport ImageInfo *CloneImageInfo(const ImageInfo *);
extern MagickExport ImageInfo *DestroyImageInfo(ImageInfo *);
extern MagickExport void *SetImageArtifact(Image *, const char *, const char *);
extern MagickExport void SetImageType(Image *, ImageType, ExceptionInfo *);
extern MagickExport int ClampToQuantum(double);
extern MagickExport size_t GetPixelChannels(Image *);
extern MagickExport int FormatLocaleString(char *, size_t, const char *, ...);
extern MagickExport int QueryColorCompliance(const char *, int, PixelInfo *, ExceptionInfo *);
extern MagickExport MagickStatusType ParseGeometry(const char *, GeometryInfo *);
extern MagickExport MagickBooleanType AnnotateImage(Image *, DrawInfo *, ExceptionInfo *);
extern MagickExport void *ConcatenateString(char **, const char *);
extern MagickExport double cos(double), sin(double), tan(double), fmod(double, double), floor(double), ceil(double);
extern MagickExport void *memset(void *, int, size_t);
extern MagickExport void xmlStopParser(xmlParserCtxtPtr);
extern MagickExport MagickExport MagickBooleanType ContrastImage(Image *image, const MagickBooleanType sharpen,ExceptionInfo *exception);
extern MagickExport Image *CropImage(const Image *, const RectangleInfo *, ExceptionInfo *);
extern MagickExport MagickExport MagickBooleanType CycleColormapImage(Image *, const ssize_t, ExceptionInfo *);
extern MagickExport Image *DespeckleImage(const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType DisplayImages(const ImageInfo *, Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType DrawImage(Image *, const DrawInfo *, ExceptionInfo *);
extern MagickExport Image* EdgeImage(const Image *,const double,ExceptionInfo *);
extern MagickExport Image* EmbossImage(const Image *, const double, const double, ExceptionInfo *);
extern MagickExport Image *EnhanceImage(const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType EqualizeImage(Image *, ExceptionInfo *);
extern MagickExport Image *MergeImageLayers(Image *, const LayerMethod, ExceptionInfo *);
extern MagickExport Image *FlipImage(const Image *image, ExceptionInfo *exception);
extern MagickExport Image *FlopImage(const Image *image,ExceptionInfo *exception);
extern MagickExport Image *ResizeImage(const Image *image,const size_t columns,
  const size_t rows,const FilterType filter,ExceptionInfo *exception);
extern MagickExport Image *RollImage(const Image *image,const ssize_t x_offset,
  const ssize_t y_offset,ExceptionInfo *exception);
extern MagickExport ssize_t GetCommandOptionFlags(const CommandOption,
                                                  const MagickBooleanType,
                                                  const char *),
    ParseChannelOption(const char *), ParsePixelChannelOption(const char *),
    ParseCommandOption(const int, const MagickBooleanType,
                       const char *);

#define DegreesToRadians(x) ((x)*3.14159265358979323846/180.0)
#define AllCompliance 7
#define TileVirtualPixelMethod 5
#define MagickNoiseOptions 8
#define MagickGravityOptions 6
#define MagickStretchOptions 9
#define MagickStyleOptions 10
#define MagickComposeOptions 4
#define MagickChannelOptions 7
#define MagickColorspaceOptions 11
#define MagickDitherOptions 12
#define ReadPixelMask 0x000001
#define TransparentAlpha 0
#define FileOpenError 430
#define OpaqueAlpha 65535
#define QuantumRange 65535.0
#define AlphaChannel 0x0010
#define DefaultResolution 72.0

#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__) > 4)
#  define magick_fallthrough  __attribute__((fallthrough))
#else
#  define magick_fallthrough  /* nothing */
#endif

typedef enum
{
  NoDitherMethod = 0,
  RiemersmaDitherMethod = 1
} DitherMethod;

typedef enum {
  UndefinedStatistic,
  GradientStatistic,
  MaximumStatistic,
  MeanStatistic,
  MedianStatistic,
  MinimumStatistic,
  ModeStatistic,
  NonpeakStatistic,
  RootMeanSquareStatistic,
  StandardDeviationStatistic,
  ContrastStatistic
} StatisticType;

typedef struct _QuantizeInfo
{
  size_t number_colors;
  int dither_method;
  MagickBooleanType dither;
  int colorspace;
  MagickBooleanType measure_error;
  size_t tree_depth;
  size_t signature;
} QuantizeInfo;

typedef struct _StringInfo
{
  size_t length;
  unsigned char *data;
  size_t signature;
} StringInfo;

typedef struct _TypeMetric {
  PointInfo pixels_per_em;

  double ascent, descent, width, height, max_advance, underline_position,
      underline_thickness;

  SegmentInfo bounds;

  PointInfo origin;
} TypeMetric;

typedef struct _MSLInfo {
  ExceptionInfo *exception;

  ssize_t depth, n, number_groups;

  ImageInfo **image_info;

  DrawInfo **draw_info;

  Image **attributes, **image;

  char *content;

  MSLGroupInfo *group_info;
} MSLInfo;

extern MagickExport Image *FrameImage(const Image *, const FrameInfo *, const CompositeOperator, ExceptionInfo *);
extern MagickExport MagickBooleanType GammaImage(Image *, const double, ExceptionInfo *);
extern MagickExport MagickBooleanType SetImageProperty(Image *, const char *, const char *, ExceptionInfo *);
extern MagickExport void *ResizeQuantumMemory(void *, const size_t, const size_t);
extern MagickExport char *ConcatenateMagickString(char *, const char *, const size_t);
extern MagickExport Image *ReadImage(const ImageInfo *, ExceptionInfo *);
extern MagickExport void CatchException(ExceptionInfo *);
extern MagickExport Image *GetNextImageInList(const Image *);
extern MagickExport MagickBooleanType SetMSLAttributes(MSLInfo *, const char *, const char *);
extern MagickExport Image *ImplodeImage(const Image *, const double, const double, ExceptionInfo *);
extern MagickExport MagickBooleanType LevelImage(Image *, const double, const double, const double, ExceptionInfo *);
extern MagickExport Image *MagnifyImage(const Image *, ExceptionInfo *);
extern MagickExport QuantizeInfo *AcquireQuantizeInfo(const ImageInfo *);
extern MagickExport Image *MinifyImage(const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType ModulateImage(Image *, const char *, ExceptionInfo *);
extern MagickExport MagickBooleanType NegateImage(Image *, MagickBooleanType, ExceptionInfo *);
extern MagickExport MagickBooleanType NormalizeImage(Image *, ExceptionInfo *);
extern MagickExport Image *OilPaintImage(const Image *, const double, const double, ExceptionInfo *);
extern MagickExport MagickBooleanType OpaquePaintImage(Image *, const PixelInfo *, const PixelInfo *, MagickBooleanType, ExceptionInfo *);
extern MagickExport int FormatLocaleFile(FILE *, const char *, ...);
extern MagickExport MagickBooleanType RemapImages(const QuantizeInfo *, Image *, const Image *, ExceptionInfo *);
extern MagickExport QuantizeInfo *DestroyQuantizeInfo(QuantizeInfo *);
extern MagickExport Image *StatisticImage(const Image *, const StatisticType, const size_t, const size_t, ExceptionInfo *);
extern MagickExport MagickBooleanType ProfileImage(Image *, const char *, const void *, const size_t, ExceptionInfo *);
extern MagickExport const StringInfo *GetImageProfile(const Image *, const char *);
extern MagickExport Image *GetImageCache(const ImageInfo *, const char *, ExceptionInfo *);
extern MagickExport int IsPathDirectory(const char *);
extern MagickExport int IsPathAccessible(const char *);
extern MagickExport StringInfo *FileToStringInfo(const char *, size_t, ExceptionInfo *);
extern MagickExport void ResetImageProfileIterator(const Image *);
extern MagickExport char *GetNextImageProfile(const Image *);
extern MagickExport StringInfo *CloneStringInfo(const StringInfo *);
extern MagickExport unsigned char *GetStringInfoDatum(const StringInfo *);
extern MagickExport size_t GetStringInfoLength(const StringInfo *);
extern MagickExport StringInfo *DestroyStringInfo(StringInfo *);
extern MagickExport void GetQuantizeInfo(QuantizeInfo *);
extern MagickExport MagickBooleanType QuantizeImage(const QuantizeInfo *, Image *, ExceptionInfo *);
extern MagickExport Image *SampleImage(const Image *, const size_t, const size_t, ExceptionInfo *);
extern MagickExport Image *ScaleImage(const Image *, const size_t, const size_t, ExceptionInfo *);
extern MagickExport MagickBooleanType GetTypeMetrics(Image *, const DrawInfo *, TypeMetric *, ExceptionInfo *);
extern MagickExport MagickBooleanType RaiseImage(Image *, const RectangleInfo *,
                                                 const MagickBooleanType,
                                                 ExceptionInfo *);
extern MagickExport Image *SegmentImage(Image *, const int, const MagickBooleanType, const double, const double, ExceptionInfo *);
extern MagickExport MagickBooleanType SetImageMask(Image *, const int, const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType TransformImageColorspace(Image *, const int, ExceptionInfo *);
extern MagickExport char *GetImageArtifact(const Image *, const char *);
extern MagickExport MagickBooleanType SetImageOption(ImageInfo *, const char *, const char *);
extern MagickExport char *GetPageGeometry(const char *);
extern MagickExport Image *ShadeImage(const Image *, const MagickBooleanType, const double, const double, ExceptionInfo *);
extern MagickExport Image *ShadowImage(const Image *, const double, const double, const ssize_t, const ssize_t, ExceptionInfo *);
extern MagickExport Image *SharpenImage(const Image *, const double, const double, ExceptionInfo *);
extern MagickExport Image *ShaveImage(const Image *, const RectangleInfo *, ExceptionInfo *);
extern MagickExport Image *ShearImage(const Image *, const double, const double, ExceptionInfo *);
extern MagickExport void SignatureImage(Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType SolarizeImage(Image *, const double, ExceptionInfo *);
extern MagickExport Image *SpreadImage(const Image *, const int, const double, ExceptionInfo *);
extern MagickExport Image *SteganoImage(const Image *, const Image *, ExceptionInfo *);
extern MagickExport Image *StereoImage(const Image *, const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType StripImage(Image *, ExceptionInfo *);
extern MagickExport void AppendImageToList(Image **, const Image *);
extern MagickExport Image *GetImageFromList(const Image *, const ssize_t);
extern MagickExport Image *GetFirstImageInList(const Image *);
extern MagickExport void ReplaceImageInList(Image **, Image *);
extern MagickExport Image *SwirlImage(const Image *, double, const int, ExceptionInfo *);
extern MagickExport MagickBooleanType SyncImage(Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType TextureImage(Image *, const Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType BilevelImage(Image *, const double, ExceptionInfo *);
extern MagickExport MagickBooleanType SetImageInfo(ImageInfo *, const unsigned int, ExceptionInfo *);
extern MagickExport MagickBooleanType WriteImage(const ImageInfo *, Image *, ExceptionInfo *);
extern MagickExport MagickBooleanType TransparentPaintImage(Image *, const PixelInfo *, const Quantum, const MagickBooleanType, ExceptionInfo *);
extern MagickExport MagickStatusType GetGeometry(const char *, ssize_t *,
                                                 ssize_t *, size_t *, size_t *),
    ParseAbsoluteGeometry(const char *, RectangleInfo *);
extern MagickExport MagickStatusType GetGeometry(const char *, ssize_t *,
                                                 ssize_t *, size_t *, size_t *),
    ParseAbsoluteGeometry(const char *, RectangleInfo *),
    ParseAffineGeometry(const char *, AffineMatrix *, ExceptionInfo *),
    ParseGeometry(const char *, GeometryInfo *),
    ParseGravityGeometry(const Image *, const char *, RectangleInfo *,
                         ExceptionInfo *),
    ParseMetaGeometry(const char *, ssize_t *, ssize_t *, size_t *, size_t *),
    ParsePageGeometry(const Image *, const char *, RectangleInfo *,
                      ExceptionInfo *),
    ParseRegionGeometry(const Image *, const char *, RectangleInfo *,
                        ExceptionInfo *);

extern MagickPrivate ssize_t FormatLocaleFileList(FILE *,
                                                  const char *magick_restrict,
                                                  va_list)
    magick_attribute((__format__(__printf__, 2, 0))),
    FormatLocaleStringList(char *magick_restrict, const size_t,
                           const char *magick_restrict2, va_list)
        magick_attribute((__format__(__printf__, 3, 0)));

MagickExport MagickBooleanType FormatImageProperty(Image *image,
                                                   const char *property,
                                                   const char *format, ...) {
  char value[MagickPathExtent];

  ExceptionInfo *exception;

  MagickBooleanType status;

  ssize_t n;

  va_list operands;

  va_start(operands, format);
  n = FormatLocaleStringList(value, MagickPathExtent, format, operands);
  (void)n;
  va_end(operands);
  exception = AcquireExceptionInfo();
  status = SetImageProperty(image, property, value, exception);
  exception = DestroyExceptionInfo(exception);
  return (status);
}

static inline unsigned long
StringToUnsignedLong(const char * value) {
  if (value == (const char *)NULL)
    return (0);
  return (strtoul(value, (char **)NULL, 10));
}

static void MSLPushImage(MSLInfo *msl_info, Image *image)
{
  ssize_t n;
  msl_info->n++;
  n = msl_info->n;
  msl_info->image_info = (ImageInfo **) ResizeQuantumMemory(msl_info->image_info, (size_t)(n + 1), sizeof(*msl_info->image_info));
  msl_info->draw_info = (DrawInfo **) ResizeQuantumMemory(msl_info->draw_info, (size_t)(n + 1), sizeof(*msl_info->draw_info));
  msl_info->attributes = (Image **) ResizeQuantumMemory(msl_info->attributes, (size_t)(n + 1), sizeof(*msl_info->attributes));
  msl_info->image = (Image **) ResizeQuantumMemory(msl_info->image, (size_t)(n + 1), sizeof(*msl_info->image));
  msl_info->image[n] = image;
}

#define ThrowMSLException(severity,tag,reason) \
  (void) ThrowMagickException(msl_info->exception,GetMagickModule(),severity,tag,"`%s'",reason)

static void MSLStartElement(void *context, const xmlChar *tag,
                                const xmlChar **attributes) {
  AffineMatrix affine, current;

  ChannelType channel;

  ChannelType channel_mask;

  char *attribute, key[MagickPathExtent], *value;

  const char *keyword;

  double angle;

  DrawInfo *draw_info;

  ExceptionInfo *exception;

  GeometryInfo geometry_info;

  Image *image;

  MagickStatusType flags;

  MSLInfo *msl_info;

  RectangleInfo geometry;

  size_t height, width;

  ssize_t i, j, n, option, x, y;

  xmlParserCtxtPtr parser;

  /*
    Called when an opening tag has been processed.
  */
  (void)LogMagickEvent(CoderEvent, GetMagickModule(), "  SAX.startElement(%s",
                       tag);
  exception = AcquireExceptionInfo();
  parser = (xmlParserCtxtPtr)context;
  msl_info = (MSLInfo *)parser->_private;
  if (msl_info->depth++ >= MagickMaxRecursionDepth) {
    (void)ThrowMagickException(msl_info->exception, GetMagickModule(),
                               DrawError, "VectorGraphicsNestedTooDeeply",
                               "`%s'", tag);
    xmlStopParser((xmlParserCtxtPtr)context);
    return;
  }
  n = msl_info->n;
  keyword = (const char *)NULL;
  value = (char *)NULL;
  SetGeometryInfo(&geometry_info);
  (void)memset(&geometry, 0, sizeof(geometry));
  channel = DefaultChannels;
  switch (*tag) {
  case 'A':
  case 'a': {
    if (LocaleCompare((const char *)tag, "add-noise") == 0) {
      Image *noise_image;

      NoiseType noise;

      /*
        Add noise image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      noise = UniformNoise;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'N':
          case 'n': {
            if (LocaleCompare(keyword, "noise") == 0) {
              option =
                  ParseCommandOption(MagickNoiseOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedNoiseType", value);
              noise = (NoiseType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      channel_mask = SetImageChannelMask(msl_info->image[n], channel);
      noise_image =
          AddNoiseImage(msl_info->image[n], noise, 1.0, msl_info->exception);
      (void)SetPixelChannelMask(msl_info->image[n], channel_mask);
      if (noise_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = noise_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "annotate") == 0) {
      char text[MagickPathExtent];

      /*
        Annotate image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      draw_info =
          CloneDrawInfo(msl_info->image_info[n], msl_info->draw_info[n]);
      angle = 0.0;
      current = draw_info->affine;
      GetAffineMatrix(&affine);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'A':
          case 'a': {
            if (LocaleCompare(keyword, "affine") == 0) {
              char *p;

              p = value;
              draw_info->affine.sx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.rx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ry = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.sy = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.tx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ty = StringToDouble(p, &p);
              break;
            }
            if (LocaleCompare(keyword, "align") == 0) {
              option =
                  ParseCommandOption(MagickAlignOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedAlignType", value);
              draw_info->align = (AlignType)option;
              break;
            }
            if (LocaleCompare(keyword, "antialias") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              draw_info->stroke_antialias = (MagickBooleanType)option;
              draw_info->text_antialias = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "density") == 0) {
              CloneString(&draw_info->density, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'E':
          case 'e': {
            if (LocaleCompare(keyword, "encoding") == 0) {
              CloneString(&draw_info->encoding, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &draw_info->fill,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "family") == 0) {
              CloneString(&draw_info->family, value);
              break;
            }
            if (LocaleCompare(keyword, "font") == 0) {
              CloneString(&draw_info->font, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGravityGeometry(msl_info->image[n], value, &geometry,
                                           exception);
              break;
            }
            if (LocaleCompare(keyword, "gravity") == 0) {
              option =
                  ParseCommandOption(MagickGravityOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedGravityType",
                                  value);
              draw_info->gravity = (GravityType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'P':
          case 'p': {
            if (LocaleCompare(keyword, "pointsize") == 0) {
              draw_info->pointsize = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "rotate") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.sx = cos(DegreesToRadians(fmod(angle, 360.0)));
              affine.rx = sin(DegreesToRadians(fmod(angle, 360.0)));
              affine.ry = (-sin(DegreesToRadians(fmod(angle, 360.0))));
              affine.sy = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "scale") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.sx = geometry_info.rho;
              affine.sy = geometry_info.sigma;
              break;
            }
            if (LocaleCompare(keyword, "skewX") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.ry = tan(DegreesToRadians(fmod((double)angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "skewY") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.rx = tan(DegreesToRadians(fmod((double)angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "stretch") == 0) {
              option =
                  ParseCommandOption(MagickStretchOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStretchType",
                                  value);
              draw_info->stretch = (StretchType)option;
              break;
            }
            if (LocaleCompare(keyword, "stroke") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->stroke, exception);
              break;
            }
            if (LocaleCompare(keyword, "strokewidth") == 0) {
              draw_info->stroke_width = (double)StringToLong(value);
              break;
            }
            if (LocaleCompare(keyword, "style") == 0) {
              option =
                  ParseCommandOption(MagickStyleOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStyleType", value);
              draw_info->style = (StyleType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "text") == 0) {
              CloneString(&draw_info->text, value);
              break;
            }
            if (LocaleCompare(keyword, "translate") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.tx = geometry_info.rho;
              affine.ty = geometry_info.sigma;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'U':
          case 'u': {
            if (LocaleCompare(keyword, "undercolor") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->undercolor, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "weight") == 0) {
              draw_info->weight = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)FormatLocaleString(text, MagickPathExtent,
                               "%.20gx%.20g%+.20g%+.20g",
                               (double)geometry.width, (double)geometry.height,
                               (double)geometry.x, (double)geometry.y);
      CloneString(&draw_info->geometry, text);
      draw_info->affine.sx = affine.sx * current.sx + affine.ry * current.rx;
      draw_info->affine.rx = affine.rx * current.sx + affine.sy * current.rx;
      draw_info->affine.ry = affine.sx * current.ry + affine.ry * current.sy;
      draw_info->affine.sy = affine.rx * current.ry + affine.sy * current.sy;
      draw_info->affine.tx =
          affine.sx * current.tx + affine.ry * current.ty + affine.tx;
      draw_info->affine.ty =
          affine.rx * current.tx + affine.sy * current.ty + affine.ty;
      (void)AnnotateImage(msl_info->image[n], draw_info, msl_info->exception);
      draw_info = DestroyDrawInfo(draw_info);
      break;
    }
    if (LocaleCompare((const char *)tag, "append") == 0) {
      Image *append_image;

      MagickBooleanType stack;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      stack = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "stack") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              stack = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      append_image =
          AppendImages(msl_info->image[n], stack, msl_info->exception);
      if (append_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = append_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "autoorient") == 0) {
      Image *new_image;

      /*
        Adjusts an image's orientation
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }

      new_image = AutoOrientImage(msl_info->image[n],
                                  msl_info->image[n]->orientation, exception);
      if (new_image == (Image *)NULL)
        break;

      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = new_image;
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'B':
  case 'b': {
    if (LocaleCompare((const char *)tag, "blur") == 0) {
      Image *blur_image;

      /*
        Blur image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sigma") == 0) {
              geometry_info.sigma = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      channel_mask = SetImageChannelMask(msl_info->image[n], channel);
      blur_image = BlurImage(msl_info->image[n], geometry_info.rho,
                             geometry_info.sigma, msl_info->exception);
      (void)SetPixelChannelMask(msl_info->image[n], channel_mask);
      if (blur_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = blur_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "border") == 0) {
      Image *border_image;

      /*
        Border image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "compose") == 0) {
              option =
                  ParseCommandOption(MagickComposeOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedComposeType",
                                  value);
              msl_info->image[n]->compose = (CompositeOperator)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &msl_info->image[n]->border_color,
                                         exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      border_image =
          BorderImage(msl_info->image[n], &geometry,
                      msl_info->image[n]->compose, msl_info->exception);
      if (border_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = border_image;
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'C':
  case 'c': {
    if (LocaleCompare((const char *)tag, "colorize") == 0) {
      char blend[MagickPathExtent];

      Image *colorize_image;

      PixelInfo target;

      /*
        Add noise image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      GetPixelInfo(msl_info->image[n], &target);
      (void)CopyMagickString(blend, "100", MagickPathExtent);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "blend") == 0) {
              (void)CopyMagickString(blend, value, MagickPathExtent);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &target,
                                         msl_info->exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      colorize_image = ColorizeImage(msl_info->image[n], blend, &target,
                                     msl_info->exception);
      if (colorize_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = colorize_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "charcoal") == 0) {
      double radius = 0.0, sigma = 1.0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      /*
        NOTE: charcoal can have no attributes, since we use all the defaults!
      */
      if (attributes != (const xmlChar **)NULL) {
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              radius = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sigma") == 0) {
              sigma = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      }

      /*
        charcoal image.
      */
      {
        Image *newImage;

        newImage = CharcoalImage(msl_info->image[n], radius, sigma,
                                 msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      }
    }
    if (LocaleCompare((const char *)tag, "chop") == 0) {
      Image *chop_image;

      /*
        Chop image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      chop_image =
          ChopImage(msl_info->image[n], &geometry, msl_info->exception);
      if (chop_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = chop_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "color-floodfill") == 0) {
      PaintMethod paint_method;

      PixelInfo target;

      /*
        Color floodfill image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      draw_info =
          CloneDrawInfo(msl_info->image_info[n], msl_info->draw_info[n]);
      SetGeometry(msl_info->image[n], &geometry);
      paint_method = FloodfillMethod;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "bordercolor") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &target,
                                         exception);
              paint_method = FillToBorderMethod;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &draw_info->fill,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "fuzz") == 0) {
              msl_info->image[n]->fuzz = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)FloodfillPaintImage(
          msl_info->image[n], draw_info, &target, geometry.x, geometry.y,
          paint_method == FloodfillMethod ? MagickFalse : MagickTrue,
          msl_info->exception);
      draw_info = DestroyDrawInfo(draw_info);
      break;
    }
    if (LocaleCompare((const char *)tag, "comment") == 0)
      break;
    if (LocaleCompare((const char *)tag, "composite") == 0) {
      char composite_geometry[MagickPathExtent];

      CompositeOperator compose;

      Image *composite_image, *rotate_image;

      /*
        Composite image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      composite_image = NewImageList();
      compose = OverCompositeOp;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "compose") == 0) {
              option =
                  ParseCommandOption(MagickComposeOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedComposeType",
                                  value);
              compose = (CompositeOperator)option;
              break;
            }
            break;
          }
          case 'I':
          case 'i': {
            if (LocaleCompare(keyword, "image") == 0)
              for (j = 0; j < msl_info->n; j++) {
                const char *prop;

                prop =
                    GetImageProperty(msl_info->attributes[j], "id", exception);
                if ((prop != (const char *)NULL) &&
                    (LocaleCompare(prop, value) == 0)) {
                  composite_image = CloneImage(msl_info->image[j], 0, 0,
                                               MagickFalse, exception);
                  break;
                }
              }
            break;
          }
          default:
            break;
          }
        }
      if (composite_image == (Image *)NULL)
        break;
      rotate_image = NewImageList();
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "blend") == 0) {
              (void)SetImageArtifact(composite_image, "compose:args", value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            if (LocaleCompare(keyword, "color") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &composite_image->background_color,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "compose") == 0)
              break;
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            if (LocaleCompare(keyword, "gravity") == 0) {
              option =
                  ParseCommandOption(MagickGravityOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedGravityType",
                                  value);
              msl_info->image[n]->gravity = (GravityType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'I':
          case 'i': {
            if (LocaleCompare(keyword, "image") == 0)
              break;
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'M':
          case 'm': {
            if (LocaleCompare(keyword, "mask") == 0)
              for (j = 0; j < msl_info->n; j++) {
                const char *prop;

                prop =
                    GetImageProperty(msl_info->attributes[j], "id", exception);
                if ((prop != (const char *)NULL) &&
                    (LocaleCompare(value, value) == 0)) {
                  SetImageType(composite_image, TrueColorAlphaType, exception);
                  (void)CompositeImage(composite_image, msl_info->image[j],
                                       CopyAlphaCompositeOp, MagickTrue, 0, 0,
                                       exception);
                  break;
                }
              }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'O':
          case 'o': {
            if (LocaleCompare(keyword, "opacity") == 0) {
              ssize_t opacity, k, r;

              Quantum *q;

              CacheView *composite_view;

              opacity = StringToLong(value);
              if (compose != DissolveCompositeOp) {
                (void)SetImageAlpha(composite_image, (Quantum)opacity,
                                    exception);
                break;
              }
              (void)SetImageArtifact(msl_info->image[n], "compose:args", value);
              if (composite_image->alpha_trait == UndefinedPixelTrait)
                (void)SetImageAlpha(composite_image, OpaqueAlpha, exception);
              composite_view =
                  AcquireAuthenticCacheView(composite_image, exception);
              for (r = 0; r < (ssize_t)composite_image->rows; r++) {
                q = GetCacheViewAuthenticPixels(composite_view, 0, r,
                                                composite_image->columns, 1,
                                                exception);
                for (k = 0; k < (ssize_t)composite_image->columns; k++) {
                  if (GetPixelAlpha(composite_image, q) == OpaqueAlpha)
                    SetPixelAlpha(composite_image,
                                  ClampToQuantum((MagickRealType)opacity), q);
                  q += (ptrdiff_t)GetPixelChannels(composite_image);
                }
                if (SyncCacheViewAuthenticPixels(composite_view, exception) ==
                    MagickFalse)
                  break;
              }
              composite_view = DestroyCacheView(composite_view);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "rotate") == 0) {
              rotate_image =
                  RotateImage(composite_image,
                              StringToDouble(value, (char **)NULL), exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "tile") == 0) {
              MagickBooleanType tile;

              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              tile = (MagickBooleanType)option;
              (void)tile;
              if (rotate_image != (Image *)NULL)
                (void)SetImageArtifact(rotate_image, "compose:outside-overlay",
                                       "false");
              else
                (void)SetImageArtifact(composite_image,
                                       "compose:outside-overlay", "false");
              image = msl_info->image[n];
              height = composite_image->rows;
              width = composite_image->columns;
              for (y = 0; y < (ssize_t)image->rows; y += (ssize_t)height)
                for (x = 0; x < (ssize_t)image->columns; x += (ssize_t)width) {
                  if (rotate_image != (Image *)NULL)
                    (void)CompositeImage(image, rotate_image, compose,
                                         MagickTrue, x, y, exception);
                  else
                    (void)CompositeImage(image, composite_image, compose,
                                         MagickTrue, x, y, exception);
                }
              if (rotate_image != (Image *)NULL)
                rotate_image = DestroyImage(rotate_image);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      image = msl_info->image[n];
      (void)FormatLocaleString(
          composite_geometry, MagickPathExtent, "%.20gx%.20g%+.20g%+.20g",
          (double)composite_image->columns, (double)composite_image->rows,
          (double)geometry.x, (double)geometry.y);
      flags =
          ParseGravityGeometry(image, composite_geometry, &geometry, exception);
      channel_mask = SetImageChannelMask(image, channel);
      if (rotate_image == (Image *)NULL)
        CompositeImage(image, composite_image, compose, MagickTrue, geometry.x,
                       geometry.y, exception);
      else {
        /*
          Rotate image.
        */
        geometry.x -=
            (ssize_t)(rotate_image->columns - composite_image->columns) / 2;
        geometry.y -= (ssize_t)(rotate_image->rows - composite_image->rows) / 2;
        CompositeImage(image, rotate_image, compose, MagickTrue, geometry.x,
                       geometry.y, exception);
        rotate_image = DestroyImage(rotate_image);
      }
      (void)SetImageChannelMask(image, channel_mask);
      composite_image = DestroyImage(composite_image);
      break;
    }
    if (LocaleCompare((const char *)tag, "contrast") == 0) {
      MagickBooleanType sharpen;

      /*
        Contrast image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      sharpen = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sharpen") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              sharpen = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)ContrastImage(msl_info->image[n], sharpen, msl_info->exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "crop") == 0) {
      Image *crop_image;

      /*
        Crop image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGravityGeometry(msl_info->image[n], value, &geometry,
                                           exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      crop_image =
          CropImage(msl_info->image[n], &geometry, msl_info->exception);
      if (crop_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = crop_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "cycle-colormap") == 0) {
      ssize_t display;

      /*
        Cycle-colormap image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      display = 0;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "display") == 0) {
              display = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)CycleColormapImage(msl_info->image[n], display, exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'D':
  case 'd': {
    if (LocaleCompare((const char *)tag, "despeckle") == 0) {
      Image *despeckle_image;

      /*
        Despeckle image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      despeckle_image = DespeckleImage(msl_info->image[n], msl_info->exception);
      if (despeckle_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = despeckle_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "display") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      (void)DisplayImages(msl_info->image_info[n], msl_info->image[n],
                          msl_info->exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "draw") == 0) {
      char text[MagickPathExtent];

      /*
        Annotate image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      draw_info =
          CloneDrawInfo(msl_info->image_info[n], msl_info->draw_info[n]);
      angle = 0.0;
      current = draw_info->affine;
      GetAffineMatrix(&affine);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'A':
          case 'a': {
            if (LocaleCompare(keyword, "affine") == 0) {
              char *p;

              p = value;
              draw_info->affine.sx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.rx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ry = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.sy = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.tx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ty = StringToDouble(p, &p);
              break;
            }
            if (LocaleCompare(keyword, "align") == 0) {
              option =
                  ParseCommandOption(MagickAlignOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedAlignType", value);
              draw_info->align = (AlignType)option;
              break;
            }
            if (LocaleCompare(keyword, "antialias") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              draw_info->stroke_antialias = (MagickBooleanType)option;
              draw_info->text_antialias = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "density") == 0) {
              CloneString(&draw_info->density, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'E':
          case 'e': {
            if (LocaleCompare(keyword, "encoding") == 0) {
              CloneString(&draw_info->encoding, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &draw_info->fill,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "family") == 0) {
              CloneString(&draw_info->family, value);
              break;
            }
            if (LocaleCompare(keyword, "font") == 0) {
              CloneString(&draw_info->font, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            if (LocaleCompare(keyword, "gravity") == 0) {
              option =
                  ParseCommandOption(MagickGravityOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedGravityType",
                                  value);
              draw_info->gravity = (GravityType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'P':
          case 'p': {
            if (LocaleCompare(keyword, "points") == 0) {
              if (LocaleCompare(draw_info->primitive, "path") == 0) {
                (void)ConcatenateString(&draw_info->primitive, " '");
                ConcatenateString(&draw_info->primitive, value);
                (void)ConcatenateString(&draw_info->primitive, "'");
              } else {
                (void)ConcatenateString(&draw_info->primitive, " ");
                ConcatenateString(&draw_info->primitive, value);
              }
              break;
            }
            if (LocaleCompare(keyword, "pointsize") == 0) {
              draw_info->pointsize = StringToDouble(value, (char **)NULL);
              break;
            }
            if (LocaleCompare(keyword, "primitive") == 0) {
              CloneString(&draw_info->primitive, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "rotate") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.sx = cos(DegreesToRadians(fmod(angle, 360.0)));
              affine.rx = sin(DegreesToRadians(fmod(angle, 360.0)));
              affine.ry = (-sin(DegreesToRadians(fmod(angle, 360.0))));
              affine.sy = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "scale") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.sx = geometry_info.rho;
              affine.sy = geometry_info.sigma;
              break;
            }
            if (LocaleCompare(keyword, "skewX") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.ry = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "skewY") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.rx = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "stretch") == 0) {
              option =
                  ParseCommandOption(MagickStretchOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStretchType",
                                  value);
              draw_info->stretch = (StretchType)option;
              break;
            }
            if (LocaleCompare(keyword, "stroke") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->stroke, exception);
              break;
            }
            if (LocaleCompare(keyword, "strokewidth") == 0) {
              draw_info->stroke_width = (double)StringToLong(value);
              break;
            }
            if (LocaleCompare(keyword, "style") == 0) {
              option =
                  ParseCommandOption(MagickStyleOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStyleType", value);
              draw_info->style = (StyleType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "text") == 0) {
              (void)ConcatenateString(&draw_info->primitive, " '");
              (void)ConcatenateString(&draw_info->primitive, value);
              (void)ConcatenateString(&draw_info->primitive, "'");
              break;
            }
            if (LocaleCompare(keyword, "translate") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.tx = geometry_info.rho;
              affine.ty = geometry_info.sigma;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'U':
          case 'u': {
            if (LocaleCompare(keyword, "undercolor") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->undercolor, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "weight") == 0) {
              draw_info->weight = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)FormatLocaleString(text, MagickPathExtent,
                               "%.20gx%.20g%+.20g%+.20g",
                               (double)geometry.width, (double)geometry.height,
                               (double)geometry.x, (double)geometry.y);
      CloneString(&draw_info->geometry, text);
      draw_info->affine.sx = affine.sx * current.sx + affine.ry * current.rx;
      draw_info->affine.rx = affine.rx * current.sx + affine.sy * current.rx;
      draw_info->affine.ry = affine.sx * current.ry + affine.ry * current.sy;
      draw_info->affine.sy = affine.rx * current.ry + affine.sy * current.sy;
      draw_info->affine.tx =
          affine.sx * current.tx + affine.ry * current.ty + affine.tx;
      draw_info->affine.ty =
          affine.rx * current.tx + affine.sy * current.ty + affine.ty;
      (void)DrawImage(msl_info->image[n], draw_info, exception);
      draw_info = DestroyDrawInfo(draw_info);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'E':
  case 'e': {
    if (LocaleCompare((const char *)tag, "edge") == 0) {
      Image *edge_image;

      /*
        Edge image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      edge_image =
          EdgeImage(msl_info->image[n], geometry_info.rho, msl_info->exception);
      if (edge_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = edge_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "emboss") == 0) {
      Image *emboss_image;

      /*
        Emboss image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sigma") == 0) {
              geometry_info.sigma = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      emboss_image = EmbossImage(msl_info->image[n], geometry_info.rho,
                                 geometry_info.sigma, msl_info->exception);
      if (emboss_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = emboss_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "enhance") == 0) {
      Image *enhance_image;

      /*
        Enhance image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      enhance_image = EnhanceImage(msl_info->image[n], msl_info->exception);
      if (enhance_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = enhance_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "equalize") == 0) {
      /*
        Equalize image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      (void)EqualizeImage(msl_info->image[n], msl_info->exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'F':
  case 'f': {
    if (LocaleCompare((const char *)tag, "flatten") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }

      /* no attributes here */

      /* process the image */
      {
        Image *newImage;

        newImage = MergeImageLayers(msl_info->image[n], FlattenLayer,
                                    msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      }
    }
    if (LocaleCompare((const char *)tag, "flip") == 0) {
      Image *flip_image;

      /*
        Flip image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      flip_image = FlipImage(msl_info->image[n], msl_info->exception);
      if (flip_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = flip_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "flop") == 0) {
      Image *flop_image;

      /*
        Flop image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      flop_image = FlopImage(msl_info->image[n], msl_info->exception);
      if (flop_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = flop_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "frame") == 0) {
      FrameInfo frame_info;

      Image *frame_image;

      /*
        Frame image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      (void)memset(&frame_info, 0, sizeof(frame_info));
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "compose") == 0) {
              option =
                  ParseCommandOption(MagickComposeOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedComposeType",
                                  value);
              msl_info->image[n]->compose = (CompositeOperator)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &msl_info->image[n]->matte_color,
                                         exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              frame_info.width = geometry.width;
              frame_info.height = geometry.height;
              frame_info.outer_bevel = geometry.x;
              frame_info.inner_bevel = geometry.y;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              frame_info.height = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'I':
          case 'i': {
            if (LocaleCompare(keyword, "inner") == 0) {
              frame_info.inner_bevel = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'O':
          case 'o': {
            if (LocaleCompare(keyword, "outer") == 0) {
              frame_info.outer_bevel = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              frame_info.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      frame_info.x = (ssize_t)frame_info.width;
      frame_info.y = (ssize_t)frame_info.height;
      frame_info.width =
          (size_t)((ssize_t)msl_info->image[n]->columns + 2 * frame_info.x);
      frame_info.height =
          (size_t)((ssize_t)msl_info->image[n]->rows + 2 * frame_info.y);
      frame_image =
          FrameImage(msl_info->image[n], &frame_info,
                     msl_info->image[n]->compose, msl_info->exception);
      if (frame_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = frame_image;
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'G':
  case 'g': {
    if (LocaleCompare((const char *)tag, "gamma") == 0) {
      char gamma[MagickPathExtent];

      PixelInfo pixel;

      /*
        Gamma image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      channel = UndefinedChannel;
      pixel.red = 0.0;
      pixel.green = 0.0;
      pixel.blue = 0.0;
      *gamma = '\0';
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "blue") == 0) {
              pixel.blue = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "gamma") == 0) {
              (void)CopyMagickString(gamma, value, MagickPathExtent);
              break;
            }
            if (LocaleCompare(keyword, "green") == 0) {
              pixel.green = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "red") == 0) {
              pixel.red = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      if (*gamma == '\0')
        (void)FormatLocaleString(gamma, MagickPathExtent, "%g,%g,%g",
                                 (double)pixel.red, (double)pixel.green,
                                 (double)pixel.blue);
      (void)GammaImage(msl_info->image[n], strtod(gamma, (char **)NULL),
                       msl_info->exception);
      break;
    } else if (LocaleCompare((const char *)tag, "get") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        CloneString(&value, (const char *)attributes[i]);
        (void)CopyMagickString(key, value, MagickPathExtent);
        switch (*keyword) {
        case 'H':
        case 'h': {
          if (LocaleCompare(keyword, "height") == 0) {
            (void)FormatLocaleString(value, MagickPathExtent, "%.20g",
                                     (double)msl_info->image[n]->rows);
            (void)SetImageProperty(msl_info->attributes[n], key, value,
                                   exception);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          magick_fallthrough;
        }
        case 'W':
        case 'w': {
          if (LocaleCompare(keyword, "width") == 0) {
            (void)FormatLocaleString(value, MagickPathExtent, "%.20g",
                                     (double)msl_info->image[n]->columns);
            (void)SetImageProperty(msl_info->attributes[n], key, value,
                                   exception);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          magick_fallthrough;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }
      break;
    } else if (LocaleCompare((const char *)tag, "group") == 0) {
      msl_info->number_groups++;
      msl_info->group_info = (MSLGroupInfo *)ResizeQuantumMemory(
          msl_info->group_info, (size_t)(msl_info->number_groups + 1),
          sizeof(*msl_info->group_info));
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'I':
  case 'i': {
    if (LocaleCompare((const char *)tag, "image") == 0) {
      MSLPushImage(msl_info, (Image *)NULL);
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'C':
        case 'c': {
          if (LocaleCompare(keyword, "color") == 0) {
            Image *next_image;

            (void)CopyMagickString(msl_info->image_info[n]->filename,
                                   "xc:", MagickPathExtent);
            (void)ConcatenateMagickString(msl_info->image_info[n]->filename,
                                          value, MagickPathExtent);
            next_image = ReadImage(msl_info->image_info[n], exception);
            CatchException(exception);
            if (next_image == (Image *)NULL)
              continue;
            if (msl_info->image[n] == (Image *)NULL)
              msl_info->image[n] = next_image;
            else {
              Image *p;

              /*
                Link image into image list.
              */
              p = msl_info->image[n];
              while (p->next != (Image *)NULL)
                p = GetNextImageInList(p);
              next_image->previous = p;
              p->next = next_image;
            }
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          break;
        }
        default: {
          (void)SetMSLAttributes(msl_info, keyword, value);
          break;
        }
        }
      }
      break;
    }
    if (LocaleCompare((const char *)tag, "implode") == 0) {
      Image *implode_image;

      /*
        Implode image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'A':
          case 'a': {
            if (LocaleCompare(keyword, "amount") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      implode_image =
          ImplodeImage(msl_info->image[n], geometry_info.rho,
                       msl_info->image[n]->interpolate, msl_info->exception);
      if (implode_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = implode_image;
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'L':
  case 'l': {
    if (LocaleCompare((const char *)tag, "label") == 0)
      break;
    if (LocaleCompare((const char *)tag, "level") == 0) {
      double levelBlack = 0, levelGamma = 1, levelWhite = QuantumRange;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        CloneString(&value, (const char *)attributes[i]);
        (void)CopyMagickString(key, value, MagickPathExtent);
        switch (*keyword) {
        case 'B':
        case 'b': {
          if (LocaleCompare(keyword, "black") == 0) {
            levelBlack = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'G':
        case 'g': {
          if (LocaleCompare(keyword, "gamma") == 0) {
            levelGamma = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'W':
        case 'w': {
          if (LocaleCompare(keyword, "white") == 0) {
            levelWhite = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /* process image */
      LevelImage(msl_info->image[n], levelBlack, levelWhite, levelGamma,
                 msl_info->exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'M':
  case 'm': {
    if (LocaleCompare((const char *)tag, "magnify") == 0) {
      Image *magnify_image;

      /*
        Magnify image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      magnify_image = MagnifyImage(msl_info->image[n], msl_info->exception);
      if (magnify_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = magnify_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "map") == 0) {
      Image *affinity_image;

      MagickBooleanType dither;

      QuantizeInfo *quantize_info;

      /*
        Map image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      affinity_image = NewImageList();
      dither = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "dither") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              dither = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'I':
          case 'i': {
            if (LocaleCompare(keyword, "image") == 0)
              for (j = 0; j < msl_info->n; j++) {
                const char *prop;

                prop =
                    GetImageProperty(msl_info->attributes[j], "id", exception);
                if ((prop != (const char *)NULL) &&
                    (LocaleCompare(prop, value) == 0)) {
                  affinity_image = CloneImage(msl_info->image[j], 0, 0,
                                              MagickFalse, exception);
                  break;
                }
              }
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      quantize_info = AcquireQuantizeInfo(msl_info->image_info[n]);
      quantize_info->dither_method =
          dither != MagickFalse ? RiemersmaDitherMethod : NoDitherMethod;
      (void)RemapImages(quantize_info, msl_info->image[n], affinity_image,
                        exception);
      quantize_info = DestroyQuantizeInfo(quantize_info);
      affinity_image = DestroyImage(affinity_image);
      break;
    }
    if (LocaleCompare((const char *)tag, "matte-floodfill") == 0) {
      double opacity;

      PixelInfo target;

      PaintMethod paint_method;

      /*
        Matte floodfill image.
      */
      opacity = 0.0;
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      SetGeometry(msl_info->image[n], &geometry);
      paint_method = FloodfillMethod;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "bordercolor") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &target,
                                         exception);
              paint_method = FillToBorderMethod;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fuzz") == 0) {
              msl_info->image[n]->fuzz = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'O':
          case 'o': {
            if (LocaleCompare(keyword, "opacity") == 0) {
              opacity = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              (void)GetOneVirtualPixelInfo(msl_info->image[n],
                                           TileVirtualPixelMethod, geometry.x,
                                           geometry.y, &target, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      draw_info =
          CloneDrawInfo(msl_info->image_info[n], msl_info->draw_info[n]);
      draw_info->fill.alpha = ClampToQuantum(opacity);
      channel_mask = SetImageChannelMask(msl_info->image[n], AlphaChannel);
      (void)FloodfillPaintImage(
          msl_info->image[n], draw_info, &target, geometry.x, geometry.y,
          paint_method == FloodfillMethod ? MagickFalse : MagickTrue,
          msl_info->exception);
      (void)SetPixelChannelMask(msl_info->image[n], channel_mask);
      draw_info = DestroyDrawInfo(draw_info);
      break;
    }
    if (LocaleCompare((const char *)tag, "median-filter") == 0) {
      Image *median_image;

      /*
        Median-filter image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      median_image = StatisticImage(
          msl_info->image[n], MedianStatistic, (size_t)geometry_info.rho,
          (size_t)geometry_info.sigma, msl_info->exception);
      if (median_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = median_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "minify") == 0) {
      Image *minify_image;

      /*
        Minify image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      minify_image = MinifyImage(msl_info->image[n], msl_info->exception);
      if (minify_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = minify_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "msl") == 0)
      break;
    if (LocaleCompare((const char *)tag, "modulate") == 0) {
      char modulate[MagickPathExtent];

      /*
        Modulate image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      geometry_info.rho = 100.0;
      geometry_info.sigma = 100.0;
      geometry_info.xi = 100.0;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'B':
          case 'b': {
            if (LocaleCompare(keyword, "blackness") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            if (LocaleCompare(keyword, "brightness") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "factor") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "hue") == 0) {
              geometry_info.xi = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'L':
          case 'l': {
            if (LocaleCompare(keyword, "lightness") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "saturation") == 0) {
              geometry_info.sigma = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "whiteness") == 0) {
              geometry_info.sigma = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)FormatLocaleString(modulate, MagickPathExtent, "%g,%g,%g",
                               geometry_info.rho, geometry_info.sigma,
                               geometry_info.xi);
      (void)ModulateImage(msl_info->image[n], modulate, msl_info->exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'N':
  case 'n': {
    if (LocaleCompare((const char *)tag, "negate") == 0) {
      MagickBooleanType gray;

      /*
        Negate image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      gray = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "gray") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              gray = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      channel_mask = SetImageChannelMask(msl_info->image[n], channel);
      (void)NegateImage(msl_info->image[n], gray, msl_info->exception);
      (void)SetPixelChannelMask(msl_info->image[n], channel_mask);
      break;
    }
    if (LocaleCompare((const char *)tag, "normalize") == 0) {
      /*
        Normalize image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)NormalizeImage(msl_info->image[n], msl_info->exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'O':
  case 'o': {
    if (LocaleCompare((const char *)tag, "oil-paint") == 0) {
      Image *paint_image;

      /*
        Oil-paint image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      paint_image = OilPaintImage(msl_info->image[n], geometry_info.rho,
                                  geometry_info.sigma, msl_info->exception);
      if (paint_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = paint_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "opaque") == 0) {
      PixelInfo fill_color, target;

      /*
        Opaque image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      (void)QueryColorCompliance("none", AllCompliance, &target, exception);
      (void)QueryColorCompliance("none", AllCompliance, &fill_color, exception);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "channel") == 0) {
              option = ParseChannelOption(value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedChannelType",
                                  value);
              channel = (ChannelType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &fill_color,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "fuzz") == 0) {
              msl_info->image[n]->fuzz = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      channel_mask = SetImageChannelMask(msl_info->image[n], channel);
      (void)OpaquePaintImage(msl_info->image[n], &target, &fill_color,
                             MagickFalse, msl_info->exception);
      (void)SetPixelChannelMask(msl_info->image[n], channel_mask);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'P':
  case 'p': {
    if (LocaleCompare((const char *)tag, "print") == 0) {
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'O':
        case 'o': {
          if (LocaleCompare(keyword, "output") == 0) {
            (void)FormatLocaleFile(stdout, "%s", value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }
      break;
    }
    if (LocaleCompare((const char *)tag, "profile") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        const char *profile_name;

        const StringInfo *profile;

        Image *profile_image;

        ImageInfo *profile_info;

        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        if (*keyword == '!') {
          /*
            Remove a profile from the image.
          */
          (void)ProfileImage(msl_info->image[n], keyword,
                             (const unsigned char *)NULL, 0, exception);
          continue;
        }
        /*
          Associate a profile with the image.
        */
        profile_info = CloneImageInfo(msl_info->image_info[n]);
        profile = GetImageProfile(msl_info->image[n], "iptc");
        if (profile != (StringInfo *)NULL)
          profile_info->profile = (void *)CloneStringInfo(profile);
        profile_image = GetImageCache(profile_info, keyword, exception);
        profile_info = DestroyImageInfo(profile_info);
        if (profile_image == (Image *)NULL) {
          char name[MagickPathExtent], filename[MagickPathExtent];

          char *p;

          StringInfo *new_profile;

          (void)CopyMagickString(filename, keyword, MagickPathExtent);
          (void)CopyMagickString(name, keyword, MagickPathExtent);
          for (p = filename; *p != '\0'; p++)
            if ((*p == ':') && (IsPathDirectory(keyword) < 0) &&
                (IsPathAccessible(keyword) == MagickFalse)) {
              char *q;

              /*
                Look for profile name (e.g. name:profile).
              */
              (void)CopyMagickString(name, filename,
                                     (size_t)(p - filename + 1));
              for (q = filename; *q != '\0'; q++)
                *q = (*++p);
              break;
            }
          new_profile = FileToStringInfo(filename, ~0UL, exception);
          if (new_profile != (StringInfo *)NULL) {
            (void)ProfileImage(
                msl_info->image[n], name, GetStringInfoDatum(new_profile),
                (size_t)GetStringInfoLength(new_profile), exception);
            new_profile = DestroyStringInfo(new_profile);
          }
          continue;
        }
        ResetImageProfileIterator(profile_image);
        profile_name = GetNextImageProfile(profile_image);
        while (profile_name != (const char *)NULL) {
          profile = GetImageProfile(profile_image, profile_name);
          if (profile != (StringInfo *)NULL)
            (void)ProfileImage(msl_info->image[n], profile_name,
                               GetStringInfoDatum(profile),
                               (size_t)GetStringInfoLength(profile), exception);
          profile_name = GetNextImageProfile(profile_image);
        }
        profile_image = DestroyImage(profile_image);
      }
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'Q':
  case 'q': {
    if (LocaleCompare((const char *)tag, "quantize") == 0) {
      QuantizeInfo quantize_info;

      /*
        Quantize image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      GetQuantizeInfo(&quantize_info);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "colors") == 0) {
              quantize_info.number_colors = (size_t)StringToLong(value);
              break;
            }
            if (LocaleCompare(keyword, "colorspace") == 0) {
              option = ParseCommandOption(MagickColorspaceOptions, MagickFalse,
                                          value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedColorspaceType",
                                  value);
              quantize_info.colorspace = (ColorspaceType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "dither") == 0) {
              option =
                  ParseCommandOption(MagickDitherOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              quantize_info.dither_method = (DitherMethod)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'M':
          case 'm': {
            if (LocaleCompare(keyword, "measure") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              quantize_info.measure_error = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "treedepth") == 0) {
              quantize_info.tree_depth = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)QuantizeImage(&quantize_info, msl_info->image[n], exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "query-font-metrics") == 0) {
      char text[MagickPathExtent];

      MagickBooleanType status;

      TypeMetric metrics;

      /*
        Query font metrics.
      */
      draw_info =
          CloneDrawInfo(msl_info->image_info[n], msl_info->draw_info[n]);
      angle = 0.0;
      current = draw_info->affine;
      GetAffineMatrix(&affine);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'A':
          case 'a': {
            if (LocaleCompare(keyword, "affine") == 0) {
              char *p;

              p = value;
              draw_info->affine.sx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.rx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ry = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.sy = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.tx = StringToDouble(p, &p);
              if (*p == ',')
                p++;
              draw_info->affine.ty = StringToDouble(p, &p);
              break;
            }
            if (LocaleCompare(keyword, "align") == 0) {
              option =
                  ParseCommandOption(MagickAlignOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedAlignType", value);
              draw_info->align = (AlignType)option;
              break;
            }
            if (LocaleCompare(keyword, "antialias") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedBooleanType",
                                  value);
              draw_info->stroke_antialias = (MagickBooleanType)option;
              draw_info->text_antialias = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "density") == 0) {
              CloneString(&draw_info->density, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'E':
          case 'e': {
            if (LocaleCompare(keyword, "encoding") == 0) {
              CloneString(&draw_info->encoding, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance, &draw_info->fill,
                                         exception);
              break;
            }
            if (LocaleCompare(keyword, "family") == 0) {
              CloneString(&draw_info->family, value);
              break;
            }
            if (LocaleCompare(keyword, "font") == 0) {
              CloneString(&draw_info->font, value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            if (LocaleCompare(keyword, "gravity") == 0) {
              option =
                  ParseCommandOption(MagickGravityOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedGravityType",
                                  value);
              draw_info->gravity = (GravityType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'P':
          case 'p': {
            if (LocaleCompare(keyword, "pointsize") == 0) {
              draw_info->pointsize = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "rotate") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.sx = cos(DegreesToRadians(fmod(angle, 360.0)));
              affine.rx = sin(DegreesToRadians(fmod(angle, 360.0)));
              affine.ry = (-sin(DegreesToRadians(fmod(angle, 360.0))));
              affine.sy = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "scale") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.sx = geometry_info.rho;
              affine.sy = geometry_info.sigma;
              break;
            }
            if (LocaleCompare(keyword, "skewX") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.ry = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "skewY") == 0) {
              angle = StringToDouble(value, (char **)NULL);
              affine.rx = cos(DegreesToRadians(fmod(angle, 360.0)));
              break;
            }
            if (LocaleCompare(keyword, "stretch") == 0) {
              option =
                  ParseCommandOption(MagickStretchOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStretchType",
                                  value);
              draw_info->stretch = (StretchType)option;
              break;
            }
            if (LocaleCompare(keyword, "stroke") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->stroke, exception);
              break;
            }
            if (LocaleCompare(keyword, "strokewidth") == 0) {
              draw_info->stroke_width = (double)StringToLong(value);
              break;
            }
            if (LocaleCompare(keyword, "style") == 0) {
              option =
                  ParseCommandOption(MagickStyleOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedStyleType", value);
              draw_info->style = (StyleType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "text") == 0) {
              CloneString(&draw_info->text, value);
              break;
            }
            if (LocaleCompare(keyword, "translate") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              affine.tx = geometry_info.rho;
              affine.ty = geometry_info.sigma;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'U':
          case 'u': {
            if (LocaleCompare(keyword, "undercolor") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &draw_info->undercolor, exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "weight") == 0) {
              draw_info->weight = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)FormatLocaleString(text, MagickPathExtent,
                               "%.20gx%.20g%+.20g%+.20g",
                               (double)geometry.width, (double)geometry.height,
                               (double)geometry.x, (double)geometry.y);
      CloneString(&draw_info->geometry, text);
      draw_info->affine.sx = affine.sx * current.sx + affine.ry * current.rx;
      draw_info->affine.rx = affine.rx * current.sx + affine.sy * current.rx;
      draw_info->affine.ry = affine.sx * current.ry + affine.ry * current.sy;
      draw_info->affine.sy = affine.rx * current.ry + affine.sy * current.sy;
      draw_info->affine.tx =
          affine.sx * current.tx + affine.ry * current.ty + affine.tx;
      draw_info->affine.ty =
          affine.rx * current.tx + affine.sy * current.ty + affine.ty;
      status = GetTypeMetrics(msl_info->attributes[n], draw_info, &metrics,
                              msl_info->exception);
      if (status != MagickFalse) {
        Image *target;

        target = msl_info->attributes[n];
        FormatImageProperty(target, "msl:font-metrics.pixels_per_em.x", "%g",
                            metrics.pixels_per_em.x);
        FormatImageProperty(target, "msl:font-metrics.pixels_per_em.y", "%g",
                            metrics.pixels_per_em.y);
        FormatImageProperty(target, "msl:font-metrics.ascent", "%g",
                            metrics.ascent);
        FormatImageProperty(target, "msl:font-metrics.descent", "%g",
                            metrics.descent);
        FormatImageProperty(target, "msl:font-metrics.width", "%g",
                            metrics.width);
        FormatImageProperty(target, "msl:font-metrics.height", "%g",
                            metrics.height);
        FormatImageProperty(target, "msl:font-metrics.max_advance", "%g",
                            metrics.max_advance);
        FormatImageProperty(target, "msl:font-metrics.bounds.x1", "%g",
                            metrics.bounds.x1);
        FormatImageProperty(target, "msl:font-metrics.bounds.y1", "%g",
                            metrics.bounds.y1);
        FormatImageProperty(target, "msl:font-metrics.bounds.x2", "%g",
                            metrics.bounds.x2);
        FormatImageProperty(target, "msl:font-metrics.bounds.y2", "%g",
                            metrics.bounds.y2);
        FormatImageProperty(target, "msl:font-metrics.origin.x", "%g",
                            metrics.origin.x);
        FormatImageProperty(target, "msl:font-metrics.origin.y", "%g",
                            metrics.origin.y);
      }
      draw_info = DestroyDrawInfo(draw_info);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'R':
  case 'r': {
    if (LocaleCompare((const char *)tag, "raise") == 0) {
      MagickBooleanType raise;

      /*
        Raise image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      raise = MagickFalse;
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "raise") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedNoiseType", value);
              raise = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)RaiseImage(msl_info->image[n], &geometry, raise,
                       msl_info->exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "read") == 0) {
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'F':
        case 'f': {
          if (LocaleCompare(keyword, "filename") == 0) {
            Image *next;

            if (value == (char *)NULL)
              break;
            (void)CopyMagickString(msl_info->image_info[n]->filename, value,
                                   MagickPathExtent);
            next = ReadImage(msl_info->image_info[n], exception);
            CatchException(exception);
            if (next == (Image *)NULL)
              continue;
            AppendImageToList(&msl_info->image[n], next);
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          break;
        }
        default: {
          (void)SetMSLAttributes(msl_info, keyword, value);
          break;
        }
        }
      }
      break;
    }
    if (LocaleCompare((const char *)tag, "reduce-noise") == 0) {
      Image *paint_image;

      /*
        Reduce-noise image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      paint_image = StatisticImage(
          msl_info->image[n], NonpeakStatistic, (size_t)geometry_info.rho,
          (size_t)geometry_info.sigma, msl_info->exception);
      if (paint_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = paint_image;
      break;
    } else if (LocaleCompare((const char *)tag, "repage") == 0) {
      /* init the values */
      width = msl_info->image[n]->page.width;
      height = msl_info->image[n]->page.height;
      x = msl_info->image[n]->page.x;
      y = msl_info->image[n]->page.y;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'G':
        case 'g': {
          if (LocaleCompare(keyword, "geometry") == 0) {
            RectangleInfo region;

            flags = ParseAbsoluteGeometry(value, &region);
            if ((flags & WidthValue) != 0) {
              if ((flags & HeightValue) == 0)
                region.height = region.width;
              width = region.width;
              height = region.height;
            }
            if ((flags & AspectValue) != 0) {
              if ((flags & XValue) != 0)
                x += region.x;
              if ((flags & YValue) != 0)
                y += region.y;
            } else {
              if ((flags & XValue) != 0) {
                x = region.x;
                if ((width == 0) && (region.x > 0))
                  width =
                      (size_t)((ssize_t)msl_info->image[n]->columns + region.x);
              }
              if ((flags & YValue) != 0) {
                y = region.y;
                if ((height == 0) && (region.y > 0))
                  height =
                      (size_t)((ssize_t)msl_info->image[n]->rows + region.y);
              }
            }
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'H':
        case 'h': {
          if (LocaleCompare(keyword, "height") == 0) {
            height = (size_t)StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'W':
        case 'w': {
          if (LocaleCompare(keyword, "width") == 0) {
            width = (size_t)StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'X':
        case 'x': {
          if (LocaleCompare(keyword, "x") == 0) {
            x = StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'Y':
        case 'y': {
          if (LocaleCompare(keyword, "y") == 0) {
            y = StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      msl_info->image[n]->page.width = width;
      msl_info->image[n]->page.height = height;
      msl_info->image[n]->page.x = x;
      msl_info->image[n]->page.y = y;
      break;
    } else if (LocaleCompare((const char *)tag, "resample") == 0) {
      double x_resolution, y_resolution;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      x_resolution = DefaultResolution;
      y_resolution = DefaultResolution;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'G':
        case 'g': {
          if (LocaleCompare(keyword, "geometry") == 0) {
            flags = ParseGeometry(value, &geometry_info);
            if ((flags & SigmaValue) == 0)
              geometry_info.sigma *= geometry_info.rho;
            x_resolution = geometry_info.rho;
            y_resolution = geometry_info.sigma;
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'X':
        case 'x': {
          if (LocaleCompare(keyword, "x-resolution") == 0) {
            x_resolution = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'Y':
        case 'y': {
          if (LocaleCompare(keyword, "y-resolution") == 0) {
            y_resolution = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }
      /*
        Resample image.
      */
      {
        double factor;

        Image *resample_image;

        factor = 1.0;
        if (msl_info->image[n]->units == PixelsPerCentimeterResolution)
          factor = 2.54;
        width =
            (size_t)(x_resolution * msl_info->image[n]->columns /
                         (factor * (msl_info->image[n]->resolution.x == 0.0
                                        ? DefaultResolution
                                        : msl_info->image[n]->resolution.x)) +
                     0.5);
        height =
            (size_t)(y_resolution * msl_info->image[n]->rows /
                         (factor * (msl_info->image[n]->resolution.y == 0.0
                                        ? DefaultResolution
                                        : msl_info->image[n]->resolution.y)) +
                     0.5);
        resample_image =
            ResizeImage(msl_info->image[n], width, height,
                        msl_info->image[n]->filter, msl_info->exception);
        if (resample_image == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = resample_image;
      }
      break;
    }
    if (LocaleCompare((const char *)tag, "resize") == 0) {
      FilterType filter;

      Image *resize_image;

      /*
        Resize image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      filter = UndefinedFilter;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "filter") == 0) {
              option =
                  ParseCommandOption(MagickFilterOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedNoiseType", value);
              filter = (FilterType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseRegionGeometry(msl_info->image[n], value, &geometry,
                                          exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToUnsignedLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      resize_image = ResizeImage(msl_info->image[n], geometry.width,
                                 geometry.height, filter, msl_info->exception);
      if (resize_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = resize_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "roll") == 0) {
      Image *roll_image;

      /*
        Roll image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      SetGeometry(msl_info->image[n], &geometry);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParsePageGeometry(msl_info->image[n], value, &geometry,
                                        exception);
              if ((flags & HeightValue) == 0)
                geometry.height = geometry.width;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry.x = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry.y = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      roll_image = RollImage(msl_info->image[n], geometry.x, geometry.y,
                             msl_info->exception);
      if (roll_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = roll_image;
      break;
    } else if (LocaleCompare((const char *)tag, "roll") == 0) {
      /* init the values */
      width = msl_info->image[n]->columns;
      height = msl_info->image[n]->rows;
      x = y = 0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'G':
        case 'g': {
          if (LocaleCompare(keyword, "geometry") == 0) {
            (void)ParseMetaGeometry(value, &x, &y, &width, &height);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'X':
        case 'x': {
          if (LocaleCompare(keyword, "x") == 0) {
            x = StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'Y':
        case 'y': {
          if (LocaleCompare(keyword, "y") == 0) {
            y = StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      {
        Image *newImage;

        newImage = RollImage(msl_info->image[n], x, y, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
      }

      break;
    }
    if (LocaleCompare((const char *)tag, "rotate") == 0) {
      Image *rotate_image;

      /*
        Rotate image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "degrees") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      rotate_image = RotateImage(msl_info->image[n], geometry_info.rho,
                                 msl_info->exception);
      if (rotate_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = rotate_image;
      break;
    } else if (LocaleCompare((const char *)tag, "rotate") == 0) {
      /* init the values */
      double degrees = 0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'D':
        case 'd': {
          if (LocaleCompare(keyword, "degrees") == 0) {
            degrees = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      {
        Image *newImage;

        newImage =
            RotateImage(msl_info->image[n], degrees, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
      }

      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'S':
  case 's': {
    if (LocaleCompare((const char *)tag, "sample") == 0) {
      Image *sample_image;

      /*
        Sample image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseRegionGeometry(msl_info->image[n], value, &geometry,
                                          exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToUnsignedLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      sample_image = SampleImage(msl_info->image[n], geometry.width,
                                 geometry.height, msl_info->exception);
      if (sample_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = sample_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "scale") == 0) {
      Image *scale_image;

      /*
        Scale image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseRegionGeometry(msl_info->image[n], value, &geometry,
                                          exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'H':
          case 'h': {
            if (LocaleCompare(keyword, "height") == 0) {
              geometry.height = (size_t)StringToUnsignedLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'W':
          case 'w': {
            if (LocaleCompare(keyword, "width") == 0) {
              geometry.width = (size_t)StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      scale_image = ScaleImage(msl_info->image[n], geometry.width,
                               geometry.height, msl_info->exception);
      if (scale_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = scale_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "segment") == 0) {
      ColorspaceType colorspace;

      MagickBooleanType verbose;

      /*
        Segment image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      geometry_info.rho = 1.0;
      geometry_info.sigma = 1.5;
      colorspace = sRGBColorspace;
      verbose = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'C':
          case 'c': {
            if (LocaleCompare(keyword, "cluster-threshold") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            if (LocaleCompare(keyword, "colorspace") == 0) {
              option = ParseCommandOption(MagickColorspaceOptions, MagickFalse,
                                          value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedColorspaceType",
                                  value);
              colorspace = (ColorspaceType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.5;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "smoothing-threshold") == 0) {
              geometry_info.sigma = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)SegmentImage(msl_info->image[n], colorspace, verbose,
                         geometry_info.rho, geometry_info.sigma, exception);
      break;
    } else if (LocaleCompare((const char *)tag, "set") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }

      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'C':
        case 'c': {
          if (LocaleCompare(keyword, "clip-mask") == 0) {
            for (j = 0; j < msl_info->n; j++) {
              const char *property;

              property =
                  GetImageProperty(msl_info->attributes[j], "id", exception);
              if (LocaleCompare(property, value) == 0) {
                SetImageMask(msl_info->image[n], ReadPixelMask,
                             msl_info->image[j], exception);
                break;
              }
            }
            break;
          }
          if (LocaleCompare(keyword, "clip-path") == 0) {
            for (j = 0; j < msl_info->n; j++) {
              const char *property;

              property =
                  GetImageProperty(msl_info->attributes[j], "id", exception);
              if (LocaleCompare(property, value) == 0) {
                SetImageMask(msl_info->image[n], ReadPixelMask,
                             msl_info->image[j], exception);
                break;
              }
            }
            break;
          }
          if (LocaleCompare(keyword, "colorspace") == 0) {
            ssize_t colorspace;

            colorspace = (ColorspaceType)ParseCommandOption(
                MagickColorspaceOptions, MagickFalse, value);
            if (colorspace < 0)
              ThrowMSLException(OptionError, "UnrecognizedColorspace", value);
            (void)TransformImageColorspace(
                msl_info->image[n], (ColorspaceType)colorspace, exception);
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          (void)SetImageProperty(msl_info->image[n], keyword, value, exception);
          break;
        }
        case 'D':
        case 'd': {
          if (LocaleCompare(keyword, "density") == 0) {
            flags = ParseGeometry(value, &geometry_info);
            msl_info->image[n]->resolution.x = geometry_info.rho;
            msl_info->image[n]->resolution.y = geometry_info.sigma;
            if ((flags & SigmaValue) == 0)
              msl_info->image[n]->resolution.y =
                  msl_info->image[n]->resolution.x;
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          (void)SetImageProperty(msl_info->image[n], keyword, value, exception);
          break;
        }
        case 'O':
        case 'o': {
          if (LocaleCompare(keyword, "opacity") == 0) {
            Quantum opac = OpaqueAlpha;
            ssize_t len = (ssize_t)strlen(value);

            if (value[len - 1] == '%') {
              char tmp[100];
              (void)CopyMagickString(tmp, value, (size_t)len);
              opac = (Quantum)StringToLong(tmp);
              opac = (Quantum)(QuantumRange * ((float)opac / 100));
            } else
              opac = (Quantum)StringToLong(value);
            (void)SetImageAlpha(msl_info->image[n], (Quantum)opac, exception);
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          (void)SetImageProperty(msl_info->image[n], keyword, value,
                                 msl_info->exception);
          break;
        }
        case 'P':
        case 'p': {
          if (LocaleCompare(keyword, "page") == 0) {
            char page[MagickPathExtent];

            const char *image_option;

            RectangleInfo page_geometry;

            (void)memset(&page_geometry, 0, sizeof(page_geometry));
            image_option = GetImageArtifact(msl_info->image[n], "page");
            if (image_option != (const char *)NULL)
              flags = ParseAbsoluteGeometry(image_option, &page_geometry);
            flags = ParseAbsoluteGeometry(value, &page_geometry);
            (void)FormatLocaleString(page, MagickPathExtent, "%.20gx%.20g",
                                     (double)page_geometry.width,
                                     (double)page_geometry.height);
            if (((flags & XValue) != 0) || ((flags & YValue) != 0))
              (void)FormatLocaleString(
                  page, MagickPathExtent, "%.20gx%.20g%+.20g%+.20g",
                  (double)page_geometry.width, (double)page_geometry.height,
                  (double)page_geometry.x, (double)page_geometry.y);
            (void)SetImageOption(msl_info->image_info[n], keyword, page);
            msl_info->image_info[n]->page = GetPageGeometry(page);
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          (void)SetImageProperty(msl_info->image[n], keyword, value,
                                 msl_info->exception);
          break;
        }
        default: {
          (void)SetMSLAttributes(msl_info, keyword, value);
          (void)SetImageProperty(msl_info->image[n], keyword, value,
                                 msl_info->exception);
          break;
        }
        }
      }
      break;
    }
    if (LocaleCompare((const char *)tag, "shade") == 0) {
      Image *shade_image;

      MagickBooleanType gray;

      /*
        Shade image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      gray = MagickFalse;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'A':
          case 'a': {
            if (LocaleCompare(keyword, "azimuth") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'E':
          case 'e': {
            if (LocaleCompare(keyword, "elevation") == 0) {
              geometry_info.sigma = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            if (LocaleCompare(keyword, "gray") == 0) {
              option =
                  ParseCommandOption(MagickBooleanOptions, MagickFalse, value);
              if (option < 0)
                ThrowMSLException(OptionError, "UnrecognizedNoiseType", value);
              gray = (MagickBooleanType)option;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      shade_image = ShadeImage(msl_info->image[n], gray, geometry_info.rho,
                               geometry_info.sigma, msl_info->exception);
      if (shade_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = shade_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "shadow") == 0) {
      Image *shadow_image;

      /*
        Shear image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'O':
          case 'o': {
            if (LocaleCompare(keyword, "opacity") == 0) {
              geometry_info.rho = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sigma") == 0) {
              geometry_info.sigma = StringToLong(value);
              break;
            }
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry_info.xi = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry_info.psi = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      shadow_image = ShadowImage(
          msl_info->image[n], geometry_info.rho, geometry_info.sigma,
          (ssize_t)ceil(geometry_info.xi - 0.5),
          (ssize_t)ceil(geometry_info.psi - 0.5), msl_info->exception);
      if (shadow_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = shadow_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "sharpen") == 0) {
      double radius = 0.0, sigma = 1.0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      /*
      NOTE: sharpen can have no attributes, since we use all the defaults!
      */
      if (attributes != (const xmlChar **)NULL) {
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              radius = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'S':
          case 's': {
            if (LocaleCompare(keyword, "sigma") == 0) {
              sigma = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      }

      /*
        sharpen image.
      */
      {
        Image *newImage;

        newImage = SharpenImage(msl_info->image[n], radius, sigma,
                                msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      }
    } else if (LocaleCompare((const char *)tag, "shave") == 0) {
      /* init the values */
      width = height = 0;
      x = y = 0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'G':
        case 'g': {
          if (LocaleCompare(keyword, "geometry") == 0) {
            (void)ParseMetaGeometry(value, &x, &y, &width, &height);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'H':
        case 'h': {
          if (LocaleCompare(keyword, "height") == 0) {
            height = (size_t)StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        case 'W':
        case 'w': {
          if (LocaleCompare(keyword, "width") == 0) {
            width = (size_t)StringToLong(value);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      {
        Image *newImage;
        RectangleInfo rectInfo;

        rectInfo.height = height;
        rectInfo.width = width;
        rectInfo.x = x;
        rectInfo.y = y;

        newImage =
            ShaveImage(msl_info->image[n], &rectInfo, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
      }

      break;
    }
    if (LocaleCompare((const char *)tag, "shear") == 0) {
      Image *shear_image;

      /*
        Shear image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'F':
          case 'f': {
            if (LocaleCompare(keyword, "fill") == 0) {
              (void)QueryColorCompliance(value, AllCompliance,
                                         &msl_info->image[n]->background_color,
                                         exception);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'X':
          case 'x': {
            if (LocaleCompare(keyword, "x") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'Y':
          case 'y': {
            if (LocaleCompare(keyword, "y") == 0) {
              geometry_info.sigma = StringToLong(value);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      shear_image = ShearImage(msl_info->image[n], geometry_info.rho,
                               geometry_info.sigma, msl_info->exception);
      if (shear_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = shear_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "signature") == 0) {
      /*
        Signature image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      (void)SignatureImage(msl_info->image[n], exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "solarize") == 0) {
      /*
        Solarize image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      geometry_info.rho = (double)QuantumRange / 2.0;
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'T':
          case 't': {
            if (LocaleCompare(keyword, "threshold") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)SolarizeImage(msl_info->image[n], geometry_info.rho,
                          msl_info->exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "spread") == 0) {
      Image *spread_image;

      /*
        Spread image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'R':
          case 'r': {
            if (LocaleCompare(keyword, "radius") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      spread_image =
          SpreadImage(msl_info->image[n], msl_info->image[n]->interpolate,
                      geometry_info.rho, msl_info->exception);
      if (spread_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = spread_image;
      break;
    } else if (LocaleCompare((const char *)tag, "stegano") == 0) {
      Image *watermark = (Image *)NULL;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'I':
        case 'i': {
          if (LocaleCompare(keyword, "image") == 0) {
            for (j = 0; j < msl_info->n; j++) {
              const char *theAttr =
                  GetImageProperty(msl_info->attributes[j], "id", exception);
              if (theAttr && LocaleCompare(theAttr, value) == 0) {
                watermark = msl_info->image[j];
                break;
              }
            }
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      if (watermark != (Image *)NULL) {
        Image *newImage;

        newImage =
            SteganoImage(msl_info->image[n], watermark, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      } else
        ThrowMSLException(OptionError, "MissingWatermarkImage", keyword);
    } else if (LocaleCompare((const char *)tag, "stereo") == 0) {
      Image *stereoImage = (Image *)NULL;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'I':
        case 'i': {
          if (LocaleCompare(keyword, "image") == 0) {
            for (j = 0; j < msl_info->n; j++) {
              const char *theAttr =
                  GetImageProperty(msl_info->attributes[j], "id", exception);
              if (theAttr && LocaleCompare(theAttr, value) == 0) {
                stereoImage = msl_info->image[j];
                break;
              }
            }
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      if (stereoImage != (Image *)NULL) {
        Image *newImage;

        newImage =
            StereoImage(msl_info->image[n], stereoImage, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      } else
        ThrowMSLException(OptionError, "Missing stereo image", keyword);
    }
    if (LocaleCompare((const char *)tag, "strip") == 0) {
      /*
        Strip image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      (void)StripImage(msl_info->image[n], msl_info->exception);
      break;
    }
    if (LocaleCompare((const char *)tag, "swap") == 0) {
      Image *p, *q, *swap;

      ssize_t index, swap_index;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      index = (-1);
      swap_index = (-2);
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "indexes") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              index = (ssize_t)geometry_info.rho;
              if ((flags & SigmaValue) == 0)
                swap_index = (ssize_t)geometry_info.sigma;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      /*
        Swap images.
      */
      p = GetImageFromList(msl_info->image[n], index);
      q = GetImageFromList(msl_info->image[n], swap_index);
      if ((p == (Image *)NULL) || (q == (Image *)NULL)) {
        ThrowMSLException(OptionError, "NoSuchImage", (const char *)tag);
        break;
      }
      swap = CloneImage(p, 0, 0, MagickTrue, msl_info->exception);
      ReplaceImageInList(&p,
                         CloneImage(q, 0, 0, MagickTrue, msl_info->exception));
      ReplaceImageInList(&q, swap);
      msl_info->image[n] = GetFirstImageInList(q);
      break;
    }
    if (LocaleCompare((const char *)tag, "swirl") == 0) {
      Image *swirl_image;

      /*
        Swirl image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'D':
          case 'd': {
            if (LocaleCompare(keyword, "degrees") == 0) {
              geometry_info.rho = StringToDouble(value, (char **)NULL);
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          case 'G':
          case 'g': {
            if (LocaleCompare(keyword, "geometry") == 0) {
              flags = ParseGeometry(value, &geometry_info);
              if ((flags & SigmaValue) == 0)
                geometry_info.sigma = 1.0;
              break;
            }
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      swirl_image =
          SwirlImage(msl_info->image[n], geometry_info.rho,
                     msl_info->image[n]->interpolate, msl_info->exception);
      if (swirl_image == (Image *)NULL)
        break;
      msl_info->image[n] = DestroyImage(msl_info->image[n]);
      msl_info->image[n] = swirl_image;
      break;
    }
    if (LocaleCompare((const char *)tag, "sync") == 0) {
      /*
        Sync image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
        }
      (void)SyncImage(msl_info->image[n], exception);
      break;
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'T':
  case 't': {
    if (LocaleCompare((const char *)tag, "map") == 0) {
      Image *texture_image;

      /*
        Texture image.
      */
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      texture_image = NewImageList();
      if (attributes != (const xmlChar **)NULL)
        for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
          keyword = (const char *)attributes[i++];
          attribute = InterpretImageProperties(
              msl_info->image_info[n], msl_info->attributes[n],
              (const char *)attributes[i], exception);
          CloneString(&value, attribute);
          attribute = DestroyString(attribute);
          switch (*keyword) {
          case 'I':
          case 'i': {
            if (LocaleCompare(keyword, "image") == 0)
              for (j = 0; j < msl_info->n; j++) {
                const char *prop;

                prop =
                    GetImageProperty(msl_info->attributes[j], "id", exception);
                if ((prop != (const char *)NULL) &&
                    (LocaleCompare(prop, value) == 0)) {
                  texture_image = CloneImage(msl_info->image[j], 0, 0,
                                             MagickFalse, exception);
                  break;
                }
              }
            break;
          }
          default: {
            ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
            break;
          }
          }
        }
      (void)TextureImage(msl_info->image[n], texture_image, exception);
      texture_image = DestroyImage(texture_image);
      break;
    } else if (LocaleCompare((const char *)tag, "threshold") == 0) {
      /* init the values */
      double threshold = 0;

      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'T':
        case 't': {
          if (LocaleCompare(keyword, "threshold") == 0) {
            threshold = StringToDouble(value, (char **)NULL);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }

      /*
        process image.
      */
      {
        BilevelImage(msl_info->image[n], threshold, exception);
        break;
      }
    } else if (LocaleCompare((const char *)tag, "transparent") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'C':
        case 'c': {
          if (LocaleCompare(keyword, "color") == 0) {
            PixelInfo target;

            (void)QueryColorCompliance(value, AllCompliance, &target,
                                       exception);
            (void)TransparentPaintImage(msl_info->image[n], &target,
                                        TransparentAlpha, MagickFalse,
                                        msl_info->exception);
            break;
          }
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        default: {
          ThrowMSLException(OptionError, "UnrecognizedAttribute", keyword);
          break;
        }
        }
      }
      break;
    } else if (LocaleCompare((const char *)tag, "trim") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }

      /* no attributes here */

      /* process the image */
      {
        Image *newImage;
        RectangleInfo rectInfo;

        /* all zeros on a crop == trim edges! */
        rectInfo.height = rectInfo.width = 0;
        rectInfo.x = rectInfo.y = 0;

        newImage =
            CropImage(msl_info->image[n], &rectInfo, msl_info->exception);
        if (newImage == (Image *)NULL)
          break;
        msl_info->image[n] = DestroyImage(msl_info->image[n]);
        msl_info->image[n] = newImage;
        break;
      }
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  case 'W':
  case 'w': {
    if (LocaleCompare((const char *)tag, "write") == 0) {
      if (msl_info->image[n] == (Image *)NULL) {
        ThrowMSLException(OptionError, "NoImagesDefined", (const char *)tag);
        break;
      }
      if (attributes == (const xmlChar **)NULL)
        break;
      for (i = 0; (attributes[i] != (const xmlChar *)NULL); i++) {
        keyword = (const char *)attributes[i++];
        attribute = InterpretImageProperties(
            msl_info->image_info[n], msl_info->attributes[n],
            (const char *)attributes[i], exception);
        CloneString(&value, attribute);
        attribute = DestroyString(attribute);
        switch (*keyword) {
        case 'F':
        case 'f': {
          if (LocaleCompare(keyword, "filename") == 0) {
            (void)CopyMagickString(msl_info->image[n]->filename, value,
                                   MagickPathExtent);
            break;
          }
          (void)SetMSLAttributes(msl_info, keyword, value);
          magick_fallthrough;
        }
        default: {
          (void)SetMSLAttributes(msl_info, keyword, value);
          break;
        }
        }
      }

      /* process */
      {
        (void)CopyMagickString(msl_info->image_info[n]->filename,
                               msl_info->image[n]->filename, MagickPathExtent);
        (void)SetImageInfo(msl_info->image_info[n], 1, exception);
        if (LocaleCompare(msl_info->image_info[n]->magick, "msl") != 0) {
          *msl_info->image_info[n]->magick = '\0';
          (void)WriteImage(msl_info->image_info[n], msl_info->image[n],
                           msl_info->exception);
        } else
          (void)ThrowMagickException(msl_info->exception, GetMagickModule(),
                                     FileOpenError, "UnableToWriteFile", "`%s'",
                                     msl_info->image[n]->filename);
        break;
      }
    }
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  default: {
    ThrowMSLException(OptionError, "UnrecognizedElement", (const char *)tag);
    break;
  }
  }
  if (value != (char *)NULL)
    value = DestroyString(value);
  (void)DestroyExceptionInfo(exception);
  (void)LogMagickEvent(CoderEvent, GetMagickModule(), "  )");
}

MagickExport Image *DestroyImage(Image *image) {
  assert(image != (Image *) NULL);
  assert(image->signature == 0xabacadabUL);
  if (IsEventLogging() != MagickFalse) (void) LogMagickEvent(0,GetMagickModule(),"%s",image->filename);
  
  if (image->semaphore) {}
  image->signature=(~0xabacadabUL);
  image=(Image *) NULL;
  return(image);
}

MagickExport Image *CloneImage(const Image *image,const size_t columns,const size_t rows,const MagickBooleanType detach,ExceptionInfo *exception) {
  double scale_x, scale_y;
  Image *clone_image;
  size_t length;
  assert(image != (const Image *) NULL);
  assert(image->signature == 0xabacadabUL);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == 0xabacadabUL);
  if (IsEventLogging() != MagickFalse) (void) LogMagickEvent(0,GetMagickModule(),"%s",image->filename);
  if ((image->columns == 0) || (image->rows == 0)) {
    (void) ThrowMagickException(exception,GetMagickModule(),425,"NegativeOrZeroImageSize","`%s'",image->filename);
    return((Image *) NULL);
  }
  clone_image=(Image *) malloc(sizeof(*clone_image));
  (void) memset(clone_image,0,sizeof(*clone_image));
  clone_image->signature=0xabacadabUL;
  clone_image->storage_class=image->storage_class;
  clone_image->number_channels=image->number_channels;
  clone_image->number_meta_channels=image->number_meta_channels;
  clone_image->metacontent_extent=image->metacontent_extent;
  clone_image->colorspace=image->colorspace;
  clone_image->alpha_trait=image->alpha_trait;
  clone_image->channels=image->channels;
  clone_image->mask_trait=image->mask_trait;
  clone_image->columns=image->columns;
  clone_image->rows=image->rows;
  clone_image->dither=image->dither;
  clone_image->image_info=CloneImageInfo(image->image_info);
  
  clone_image->magick_columns=image->magick_columns;
  clone_image->magick_rows=image->magick_rows;
  
  clone_image->channel_mask=image->channel_mask;
  clone_image->channel_map=NULL;
  (void) CopyMagickString(clone_image->magick_filename,image->magick_filename,MagickPathExtent);
  (void) CopyMagickString(clone_image->magick,image->magick,MagickPathExtent);
  (void) CopyMagickString(clone_image->filename,image->filename,MagickPathExtent);
  clone_image->progress_monitor=image->progress_monitor;
  clone_image->client_data=image->client_data;
  clone_image->reference_count=1;
  clone_image->next=image->next;
  clone_image->previous=image->previous;
  clone_image->list=NewImageList();
  clone_image->ping=image->ping;
  clone_image->timestamp=image->timestamp;
  clone_image->ttl=image->ttl;
  clone_image->debug=image->debug;
  clone_image->semaphore=NULL;
  if (image->colormap != (PixelInfo *) NULL) {
    clone_image->colors=image->colors;
    length=(size_t) image->colors;
    clone_image->colormap=(PixelInfo *) malloc((length+1)*sizeof(*clone_image->colormap));
    if (clone_image->colormap == (PixelInfo *) NULL) { clone_image=DestroyImage(clone_image); return((Image *) NULL); }
    (void) memcpy(clone_image->colormap,image->colormap,length*sizeof(*clone_image->colormap));
  }
  if ((columns == 0) || (rows == 0)) {
    if (image->montage != (char *) NULL) (void) CloneString(&clone_image->montage,image->montage);
    if (image->directory != (char *) NULL) (void) CloneString(&clone_image->directory,image->directory);
    return(clone_image);
  }
  scale_x=1.0; scale_y=1.0;
  if (image->columns != 0) scale_x=(double) columns/(double) image->columns;
  if (image->rows != 0) scale_y=(double) rows/(double) image->rows;
  clone_image->page.width=(size_t) floor(scale_x*image->page.width+0.5);
  clone_image->page.height=(size_t) floor(scale_y*image->page.height+0.5);
  if (fabs(scale_x-scale_y) < 2.0) scale_x=scale_y=fmin(scale_x,scale_y);
  clone_image->page.x=ceil(scale_x*image->page.x-0.5);
  clone_image->tile_offset.x=ceil(scale_x*image->tile_offset.x-0.5);
  clone_image->page.y=ceil(scale_y*image->page.y-0.5);
  clone_image->tile_offset.y=ceil(scale_y*image->tile_offset.y-0.5);
  return(clone_image);
}

MagickExport Image *NewImageList(void) { return((Image *) NULL); }
