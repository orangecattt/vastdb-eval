#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <stdatomic.h>

struct AVCodecContext;
struct AVCodec;
typedef struct AVCodecContext AVCodecContext;
typedef struct AVCodec AVCodec;
typedef struct AVClass AVClass;
typedef struct AVDictionary AVDictionary;
typedef struct AVFrame AVFrame;
typedef struct AVPacket AVPacket;
typedef struct AVBufferRef AVBufferRef;
typedef struct AVBSFContext AVBSFContext;
typedef struct AVFifoBuffer AVFifoBuffer;
typedef struct AVCodecDefault AVCodecDefault;
typedef struct AVCodecHWConfigInternal AVCodecHWConfigInternal;
typedef struct AVSubtitle AVSubtitle;
typedef struct AVHWAccel AVHWAccel;
typedef struct RcOverride RcOverride;

#define AV_NUM_DATA_POINTERS 8

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,
    // AVMEDIA_TYPE_VIDEO,
    // AVMEDIA_TYPE_AUDIO,
    // AVMEDIA_TYPE_DATA,
    // AVMEDIA_TYPE_SUBTITLE,
    // AVMEDIA_TYPE_ATTACHMENT,
    // AVMEDIA_TYPE_NB
};

enum AVCodecID {
    AV_CODEC_ID_NONE,
    AV_CODEC_ID_MJPEG,
    AV_CODEC_ID_HUFFYUV,
    AV_CODEC_ID_FFVHUFF,
};

enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
};

enum AVColorPrimaries {
    AVCOL_PRI_RESERVED0   = 0,
    AVCOL_PRI_BT709       = 1,  ///< also ITU-R BT1361 / IEC 61966-2-4 / SMPTE RP 177 Annex B
    AVCOL_PRI_UNSPECIFIED = 2,
    AVCOL_PRI_RESERVED    = 3,
    AVCOL_PRI_BT470M      = 4,  ///< also FCC Title 47 Code of Federal Regulations 73.682 (a)(20)

    AVCOL_PRI_BT470BG     = 5,  ///< also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM
    AVCOL_PRI_SMPTE170M   = 6,  ///< also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC
    AVCOL_PRI_SMPTE240M   = 7,  ///< identical to above, also called "SMPTE C" even though it uses D65
    AVCOL_PRI_FILM        = 8,  ///< colour filters using Illuminant C
    AVCOL_PRI_BT2020      = 9,  ///< ITU-R BT2020
    AVCOL_PRI_SMPTE428    = 10, ///< SMPTE ST 428-1 (CIE 1931 XYZ)
    AVCOL_PRI_SMPTEST428_1 = AVCOL_PRI_SMPTE428,
    AVCOL_PRI_SMPTE431    = 11, ///< SMPTE ST 431-2 (2011) / DCI P3
    AVCOL_PRI_SMPTE432    = 12, ///< SMPTE ST 432-1 (2010) / P3 D65 / Display P3
    AVCOL_PRI_EBU3213     = 22, ///< EBU Tech. 3213-E (nothing there) / one of JEDEC P22 group phosphors
    AVCOL_PRI_JEDEC_P22   = AVCOL_PRI_EBU3213,
    AVCOL_PRI_NB                ///< Not part of ABI
};

enum AVColorTransferCharacteristic {
    AVCOL_TRC_RESERVED0    = 0,
    AVCOL_TRC_BT709        = 1,  ///< also ITU-R BT1361
    AVCOL_TRC_UNSPECIFIED  = 2,
    AVCOL_TRC_RESERVED     = 3,
    AVCOL_TRC_GAMMA22      = 4,  ///< also ITU-R BT470M / ITU-R BT1700 625 PAL & SECAM
    AVCOL_TRC_GAMMA28      = 5,  ///< also ITU-R BT470BG
    AVCOL_TRC_SMPTE170M    = 6,  ///< also ITU-R BT601-6 525 or 625 / ITU-R BT1358 525 or 625 / ITU-R BT1700 NTSC
    AVCOL_TRC_SMPTE240M    = 7,
    AVCOL_TRC_LINEAR       = 8,  ///< "Linear transfer characteristics"
    AVCOL_TRC_LOG          = 9,  ///< "Logarithmic transfer characteristic (100:1 range)"
    AVCOL_TRC_LOG_SQRT     = 10, ///< "Logarithmic transfer characteristic (100 * Sqrt(10) : 1 range)"
    AVCOL_TRC_IEC61966_2_4 = 11, ///< IEC 61966-2-4
    AVCOL_TRC_BT1361_ECG   = 12, ///< ITU-R BT1361 Extended Colour Gamut
    AVCOL_TRC_IEC61966_2_1 = 13, ///< IEC 61966-2-1 (sRGB or sYCC)
    AVCOL_TRC_BT2020_10    = 14, ///< ITU-R BT2020 for 10-bit system
    AVCOL_TRC_BT2020_12    = 15, ///< ITU-R BT2020 for 12-bit system
    AVCOL_TRC_SMPTE2084    = 16, ///< SMPTE ST 2084 for 10-, 12-, 14- and 16-bit systems
    AVCOL_TRC_SMPTEST2084  = AVCOL_TRC_SMPTE2084,
    AVCOL_TRC_SMPTE428     = 17, ///< SMPTE ST 428-1
    AVCOL_TRC_SMPTEST428_1 = AVCOL_TRC_SMPTE428,
    AVCOL_TRC_ARIB_STD_B67 = 18, ///< ARIB STD-B67, known as "Hybrid log-gamma"
    AVCOL_TRC_NB                 ///< Not part of ABI
};

enum AVColorSpace {
    AVCOL_SPC_RGB         = 0,  ///< order of coefficients is actually GBR, also IEC 61966-2-1 (sRGB), YZX and ST 428-1
    AVCOL_SPC_BT709       = 1,  ///< also ITU-R BT1361 / IEC 61966-2-4 xvYCC709 / derived in SMPTE RP 177 Annex B
    AVCOL_SPC_UNSPECIFIED = 2,
    AVCOL_SPC_RESERVED    = 3,  ///< reserved for future use by ITU-T and ISO/IEC just like 15-255 are
    AVCOL_SPC_FCC         = 4,  ///< FCC Title 47 Code of Federal Regulations 73.682 (a)(20)
    AVCOL_SPC_BT470BG     = 5,  ///< also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM / IEC 61966-2-4 xvYCC601
    AVCOL_SPC_SMPTE170M   = 6,  ///< also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC / functionally identical to above
    AVCOL_SPC_SMPTE240M   = 7,  ///< derived from 170M primaries and D65 white point, 170M is derived from BT470 System M's primaries
    AVCOL_SPC_YCGCO       = 8,  ///< used by Dirac / VC-2 and H.264 FRext, see ITU-T SG16
    AVCOL_SPC_YCOCG       = AVCOL_SPC_YCGCO,
    AVCOL_SPC_BT2020_NCL  = 9,  ///< ITU-R BT2020 non-constant luminance system
    AVCOL_SPC_BT2020_CL   = 10, ///< ITU-R BT2020 constant luminance system
    AVCOL_SPC_SMPTE2085   = 11, ///< SMPTE 2085, Y'D'zD'x
    AVCOL_SPC_CHROMA_DERIVED_NCL = 12, ///< Chromaticity-derived non-constant luminance system
    AVCOL_SPC_CHROMA_DERIVED_CL = 13, ///< Chromaticity-derived constant luminance system
    AVCOL_SPC_ICTCP       = 14, ///< ITU-R BT.2100-0, ICtCp
    AVCOL_SPC_NB                ///< Not part of ABI
};

enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
};

enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1, ///< MPEG-2/4 4:2:0, H.264 default for 4:2:0
    AVCHROMA_LOC_CENTER      = 2, ///< MPEG-1 4:2:0, JPEG 4:2:0, H.263 4:2:0
    AVCHROMA_LOC_TOPLEFT     = 3, ///< ITU-R 601, SMPTE 274M 296M S314M(DV 4:1:1), mpeg2 4:2:2
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_BOTTOM      = 6,
    AVCHROMA_LOC_NB               ///< Not part of ABI
};

enum AVSampleFormat {
    AV_SAMPLE_FMT_NONE = -1,
    AV_SAMPLE_FMT_U8,          ///< unsigned 8 bits
    AV_SAMPLE_FMT_S16,         ///< signed 16 bits
    AV_SAMPLE_FMT_S32,         ///< signed 32 bits
    AV_SAMPLE_FMT_FLT,         ///< float
    AV_SAMPLE_FMT_DBL,         ///< double

    AV_SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
    AV_SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
    AV_SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
    AV_SAMPLE_FMT_FLTP,        ///< float, planar
    AV_SAMPLE_FMT_DBLP,        ///< double, planar
    AV_SAMPLE_FMT_S64,         ///< signed 64 bits
    AV_SAMPLE_FMT_S64P,        ///< signed 64 bits, planar

    AV_SAMPLE_FMT_NB           ///< Number of sample formats. DO NOT USE if linking dynamically
};

enum AVFieldOrder {
    AV_FIELD_UNKNOWN,
    AV_FIELD_PROGRESSIVE,
    AV_FIELD_TT,          //< Top coded_first, top displayed first
    AV_FIELD_BB,          //< Bottom coded first, bottom displayed first
    AV_FIELD_TB,          //< Top coded first, bottom displayed first
    AV_FIELD_BT,          //< Bottom coded first, top displayed first
};

enum AVAudioServiceType {
    AV_AUDIO_SERVICE_TYPE_MAIN              = 0,
    AV_AUDIO_SERVICE_TYPE_EFFECTS           = 1,
    AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED = 2,
    AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED  = 3,
    AV_AUDIO_SERVICE_TYPE_DIALOGUE          = 4,
    AV_AUDIO_SERVICE_TYPE_COMMENTARY        = 5,
    AV_AUDIO_SERVICE_TYPE_EMERGENCY         = 6,
    AV_AUDIO_SERVICE_TYPE_VOICE_OVER        = 7,
    AV_AUDIO_SERVICE_TYPE_KARAOKE           = 8,
    AV_AUDIO_SERVICE_TYPE_NB                   , ///< Not part of ABI
};

#define AV_CODEC_CAP_FRAME_THREADS       (1 << 12)
#define AV_CODEC_FLAG_QSCALE             (1 <<  1)
#define AV_CODEC_FLAG_PASS1              (1 <<  9)
#define MAX_THREADS 64
#define BUFFER_SIZE (MAX_THREADS + 2)
#define AV_LOG_QUIET    -8
#define AV_LOG_PANIC     0
#define AV_LOG_FATAL     8
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48
#define AV_LOG_TRACE    56
#if EDOM > 0
#define AVERROR(e) (-(e))
#define AVUNERROR(e) (-(e))
#else
#define AVERROR(e) (e)
#define AVUNERROR(e) (e)
#endif
#define av_assert0(cond) do { \
    if (!(cond)) { \
        av_log(NULL, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n", \
               #cond, __FILE__, __LINE__); \
        abort(); \
    } \
} while (0)
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define AV_STRINGIFY(s) AV_TOSTRING(s)
#define AV_TOSTRING(s) #s
#define AV_NOWARN_DEPRECATED(res) _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
    res \
    _Pragma("GCC diagnostic pop")

typedef struct AVRational {
    int num;
    int den;
} AVRational;

typedef struct AVProfile {
    int profile;
    const char *name;
} AVProfile;

typedef struct DecodeSimpleContext {
    AVPacket *in_pkt;
} DecodeSimpleContext;

typedef struct EncodeSimpleContext {
    AVFrame *in_frame;
} EncodeSimpleContext;

typedef struct AVCodecInternal {
    int is_copy;
    int last_audio_frame;
    AVBufferRef *pool;
    void *thread_ctx;
    DecodeSimpleContext ds;
    AVBSFContext *bsf;
    AVPacket *last_pkt_props;
    AVFifoBuffer *pkt_props;
    uint8_t *byte_buffer;
    unsigned int byte_buffer_size;
    void *frame_thread_encoder;
    EncodeSimpleContext es;
    int needs_close;
    int skip_samples;
    void *hwaccel_priv_data;
    int draining;
    AVPacket *buffer_pkt;
    AVFrame *buffer_frame;
    int draining_done;
    int showed_multi_packet_warning;
    int skip_samples_multiplier;
    int nb_draining_errors;
    int changed_frames_dropped;
    int initial_format;
    int initial_width, initial_height;
    int initial_sample_rate;
    int initial_channels;
    uint64_t initial_channel_layout;
} AVCodecInternal;

typedef struct AVCodec {
    const char *name;
    const char *long_name;
    enum AVMediaType type;
    enum AVCodecID id;
    int capabilities;
    const AVRational *supported_framerates;
    const enum AVPixelFormat *pix_fmts;
    const int *supported_samplerates;
    const enum AVSampleFormat *sample_fmts;
    const uint64_t *channel_layouts;
    uint8_t max_lowres;
    const AVClass *priv_class;
    const AVProfile *profiles;
    const char *wrapper_name;
    int priv_data_size;
    int (*update_thread_context)(struct AVCodecContext *dst, const struct AVCodecContext *src);
    int (*update_thread_context_for_user)(struct AVCodecContext *dst, const struct AVCodecContext *src);
    const AVCodecDefault *defaults;
    void (*init_static_data)(struct AVCodec *codec);
    int (*init)(struct AVCodecContext *);
    int (*encode_sub)(struct AVCodecContext *, uint8_t *buf, int buf_size,
                      const struct AVSubtitle *sub);
    int (*encode2)(struct AVCodecContext *avctx, struct AVPacket *avpkt,
                   const struct AVFrame *frame, int *got_packet_ptr);
    int (*decode)(struct AVCodecContext *avctx, void *outdata,
                  int *got_frame_ptr, struct AVPacket *avpkt);
    int (*close)(struct AVCodecContext *);
    int (*receive_packet)(struct AVCodecContext *avctx, struct AVPacket *avpkt);
    int (*receive_frame)(struct AVCodecContext *avctx, struct AVFrame *frame);
    void (*flush)(struct AVCodecContext *);
    int caps_internal;
    const char *bsfs;
    const struct AVCodecHWConfigInternal *const *hw_configs;
    const uint32_t *codec_tags;
} AVCodec;

typedef struct AVCodecContext {
    /**
     * information on struct for av_log
     * - set by avcodec_alloc_context3
     */
    const AVClass *av_class;
    int log_level_offset;

    enum AVMediaType codec_type; /* see AVMEDIA_TYPE_xxx */
    const struct AVCodec  *codec;
    enum AVCodecID     codec_id; /* see AV_CODEC_ID_xxx */

    /**
     * fourcc (LSB first, so "ABCD" -> ('D'<<24) + ('C'<<16) + ('B'<<8) + 'A').
     * This is used to work around some encoder bugs.
     * A demuxer should set this to what is stored in the field used to identify the codec.
     * If there are multiple such fields in a container then the demuxer should choose the one
     * which maximizes the information about the used codec.
     * If the codec tag field in a container is larger than 32 bits then the demuxer should
     * remap the longer ID to 32 bits with a table or other structure. Alternatively a new
     * extra_codec_tag + size could be added but for this a clear advantage must be demonstrated
     * first.
     * - encoding: Set by user, if not then the default based on codec_id will be used.
     * - decoding: Set by user, will be converted to uppercase by libavcodec during init.
     */
    unsigned int codec_tag;

    void *priv_data;

    /**
     * Private context used for internal data.
     *
     * Unlike priv_data, this is not codec-specific. It is used in general
     * libavcodec functions.
     */
    struct AVCodecInternal *internal;

    /**
     * Private data of the user, can be used to carry app specific stuff.
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    void *opaque;

    /**
     * the average bitrate
     * - encoding: Set by user; unused for constant quantizer encoding.
     * - decoding: Set by user, may be overwritten by libavcodec
     *             if this info is available in the stream
     */
    int64_t bit_rate;

    /**
     * number of bits the bitstream is allowed to diverge from the reference.
     *           the reference can be CBR (for CBR pass1) or VBR (for pass2)
     * - encoding: Set by user; unused for constant quantizer encoding.
     * - decoding: unused
     */
    int bit_rate_tolerance;

    /**
     * Global quality for codecs which cannot change it per frame.
     * This should be proportional to MPEG-1/2/4 qscale.
     * - encoding: Set by user.
     * - decoding: unused
     */
    int global_quality;

    /**
     * - encoding: Set by user.
     * - decoding: unused
     */
    int compression_level;
#define FF_COMPRESSION_DEFAULT -1

    /**
     * AV_CODEC_FLAG_*.
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int flags;

    /**
     * AV_CODEC_FLAG2_*
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int flags2;

    /**
     * some codecs need / can use extradata like Huffman tables.
     * MJPEG: Huffman tables
     * rv10: additional flags
     * MPEG-4: global headers (they can be in the bitstream or here)
     * The allocated memory should be AV_INPUT_BUFFER_PADDING_SIZE bytes larger
     * than extradata_size to avoid problems if it is read with the bitstream reader.
     * The bytewise contents of extradata must not depend on the architecture or CPU endianness.
     * Must be allocated with the av_malloc() family of functions.
     * - encoding: Set/allocated/freed by libavcodec.
     * - decoding: Set/allocated/freed by user.
     */
    uint8_t *extradata;
    int extradata_size;

    /**
     * This is the fundamental unit of time (in seconds) in terms
     * of which frame timestamps are represented. For fixed-fps content,
     * timebase should be 1/framerate and timestamp increments should be
     * identically 1.
     * This often, but not always is the inverse of the frame rate or field rate
     * for video. 1/time_base is not the average frame rate if the frame rate is not
     * constant.
     *
     * Like containers, elementary streams also can store timestamps, 1/time_base
     * is the unit in which these timestamps are specified.
     * As example of such codec time base see ISO/IEC 14496-2:2001(E)
     * vop_time_increment_resolution and fixed_vop_rate
     * (fixed_vop_rate == 0 implies that it is different from the framerate)
     *
     * - encoding: MUST be set by user.
     * - decoding: the use of this field for decoding is deprecated.
     *             Use framerate instead.
     */
    AVRational time_base;

    /**
     * For some codecs, the time base is closer to the field rate than the frame rate.
     * Most notably, H.264 and MPEG-2 specify time_base as half of frame duration
     * if no telecine is used ...
     *
     * Set to time_base ticks per frame. Default 1, e.g., H.264/MPEG-2 set it to 2.
     */
    int ticks_per_frame;

    /**
     * Codec delay.
     *
     * Encoding: Number of frames delay there will be from the encoder input to
     *           the decoder output. (we assume the decoder matches the spec)
     * Decoding: Number of frames delay in addition to what a standard decoder
     *           as specified in the spec would produce.
     *
     * Video:
     *   Number of frames the decoded output will be delayed relative to the
     *   encoded input.
     *
     * Audio:
     *   For encoding, this field is unused (see initial_padding).
     *
     *   For decoding, this is the number of samples the decoder needs to
     *   output before the decoder's output is valid. When seeking, you should
     *   start decoding this many samples prior to your desired seek point.
     *
     * - encoding: Set by libavcodec.
     * - decoding: Set by libavcodec.
     */
    int delay;


    /* video only */
    /**
     * picture width / height.
     *
     * @note Those fields may not match the values of the last
     * AVFrame output by avcodec_receive_frame() due frame
     * reordering.
     *
     * - encoding: MUST be set by user.
     * - decoding: May be set by the user before opening the decoder if known e.g.
     *             from the container. Some decoders will require the dimensions
     *             to be set by the caller. During decoding, the decoder may
     *             overwrite those values as required while parsing the data.
     */
    int width, height;

    /**
     * Bitstream width / height, may be different from width/height e.g. when
     * the decoded frame is cropped before being output or lowres is enabled.
     *
     * @note Those field may not match the value of the last
     * AVFrame output by avcodec_receive_frame() due frame
     * reordering.
     *
     * - encoding: unused
     * - decoding: May be set by the user before opening the decoder if known
     *             e.g. from the container. During decoding, the decoder may
     *             overwrite those values as required while parsing the data.
     */
    int coded_width, coded_height;

    /**
     * the number of pictures in a group of pictures, or 0 for intra_only
     * - encoding: Set by user.
     * - decoding: unused
     */
    int gop_size;

    /**
     * Pixel format, see AV_PIX_FMT_xxx.
     * May be set by the demuxer if known from headers.
     * May be overridden by the decoder if it knows better.
     *
     * @note This field may not match the value of the last
     * AVFrame output by avcodec_receive_frame() due frame
     * reordering.
     *
     * - encoding: Set by user.
     * - decoding: Set by user if known, overridden by libavcodec while
     *             parsing the data.
     */
    enum AVPixelFormat pix_fmt;

    /**
     * If non NULL, 'draw_horiz_band' is called by the libavcodec
     * decoder to draw a horizontal band. It improves cache usage. Not
     * all codecs can do that. You must check the codec capabilities
     * beforehand.
     * When multithreading is used, it may be called from multiple threads
     * at the same time; threads might draw different parts of the same AVFrame,
     * or multiple AVFrames, and there is no guarantee that slices will be drawn
     * in order.
     * The function is also used by hardware acceleration APIs.
     * It is called at least once during frame decoding to pass
     * the data needed for hardware render.
     * In that mode instead of pixel data, AVFrame points to
     * a structure specific to the acceleration API. The application
     * reads the structure and can change some fields to indicate progress
     * or mark state.
     * - encoding: unused
     * - decoding: Set by user.
     * @param height the height of the slice
     * @param y the y position of the slice
     * @param type 1->top field, 2->bottom field, 3->frame
     * @param offset offset into the AVFrame.data from which the slice should be read
     */
    void (*draw_horiz_band)(struct AVCodecContext *s,
                            const AVFrame *src, int offset[AV_NUM_DATA_POINTERS],
                            int y, int type, int height);

    /**
     * Callback to negotiate the pixel format. Decoding only, may be set by the
     * caller before avcodec_open2().
     *
     * Called by some decoders to select the pixel format that will be used for
     * the output frames. This is mainly used to set up hardware acceleration,
     * then the provided format list contains the corresponding hwaccel pixel
     * formats alongside the "software" one. The software pixel format may also
     * be retrieved from \ref sw_pix_fmt.
     *
     * This callback will be called when the coded frame properties (such as
     * resolution, pixel format, etc.) change and more than one output format is
     * supported for those new properties. If a hardware pixel format is chosen
     * and initialization for it fails, the callback may be called again
     * immediately.
     *
     * This callback may be called from different threads if the decoder is
     * multi-threaded, but not from more than one thread simultaneously.
     *
     * @param fmt list of formats which may be used in the current
     *            configuration, terminated by AV_PIX_FMT_NONE.
     * @warning Behavior is undefined if the callback returns a value other
     *          than one of the formats in fmt or AV_PIX_FMT_NONE.
     * @return the chosen format or AV_PIX_FMT_NONE
     */
    enum AVPixelFormat (*get_format)(struct AVCodecContext *s, const enum AVPixelFormat * fmt);

    /**
     * maximum number of B-frames between non-B-frames
     * Note: The output will be delayed by max_b_frames+1 relative to the input.
     * - encoding: Set by user.
     * - decoding: unused
     */
    int max_b_frames;

    /**
     * qscale factor between IP and B-frames
     * If > 0 then the last P-frame quantizer will be used (q= lastp_q*factor+offset).
     * If < 0 then normal ratecontrol will be done (q= -normal_q*factor+offset).
     * - encoding: Set by user.
     * - decoding: unused
     */
    float b_quant_factor;

    /**
     * qscale offset between IP and B-frames
     * - encoding: Set by user.
     * - decoding: unused
     */
    float b_quant_offset;

    /**
     * Size of the frame reordering buffer in the decoder.
     * For MPEG-2 it is 1 IPB or 0 low delay IP.
     * - encoding: Set by libavcodec.
     * - decoding: Set by libavcodec.
     */
    int has_b_frames;

    /**
     * qscale factor between P- and I-frames
     * If > 0 then the last P-frame quantizer will be used (q = lastp_q * factor + offset).
     * If < 0 then normal ratecontrol will be done (q= -normal_q*factor+offset).
     * - encoding: Set by user.
     * - decoding: unused
     */
    float i_quant_factor;

    /**
     * qscale offset between P and I-frames
     * - encoding: Set by user.
     * - decoding: unused
     */
    float i_quant_offset;

    /**
     * luminance masking (0-> disabled)
     * - encoding: Set by user.
     * - decoding: unused
     */
    float lumi_masking;

    /**
     * temporary complexity masking (0-> disabled)
     * - encoding: Set by user.
     * - decoding: unused
     */
    float temporal_cplx_masking;

    /**
     * spatial complexity masking (0-> disabled)
     * - encoding: Set by user.
     * - decoding: unused
     */
    float spatial_cplx_masking;

    /**
     * p block masking (0-> disabled)
     * - encoding: Set by user.
     * - decoding: unused
     */
    float p_masking;

    /**
     * darkness masking (0-> disabled)
     * - encoding: Set by user.
     * - decoding: unused
     */
    float dark_masking;

    /**
     * slice count
     * - encoding: Set by libavcodec.
     * - decoding: Set by user (or 0).
     */
    int slice_count;

    /**
     * slice offsets in the frame in bytes
     * - encoding: Set/allocated by libavcodec.
     * - decoding: Set/allocated by user (or NULL).
     */
    int *slice_offset;

    /**
     * sample aspect ratio (0 if unknown)
     * That is the width of a pixel divided by the height of the pixel.
     * Numerator and denominator must be relatively prime and smaller than 256 for some video standards.
     * - encoding: Set by user.
     * - decoding: Set by libavcodec.
     */
    AVRational sample_aspect_ratio;

    /**
     * motion estimation comparison function
     * - encoding: Set by user.
     * - decoding: unused
     */
    int me_cmp;
    /**
     * subpixel motion estimation comparison function
     * - encoding: Set by user.
     * - decoding: unused
     */
    int me_sub_cmp;
    /**
     * macroblock comparison function (not supported yet)
     * - encoding: Set by user.
     * - decoding: unused
     */
    int mb_cmp;
    /**
     * interlaced DCT comparison function
     * - encoding: Set by user.
     * - decoding: unused
     */
    int ildct_cmp;
#define FF_CMP_SAD          0
#define FF_CMP_SSE          1
#define FF_CMP_SATD         2
#define FF_CMP_DCT          3
#define FF_CMP_PSNR         4
#define FF_CMP_BIT          5
#define FF_CMP_RD           6
#define FF_CMP_ZERO         7
#define FF_CMP_VSAD         8
#define FF_CMP_VSSE         9
#define FF_CMP_NSSE         10
#define FF_CMP_W53          11
#define FF_CMP_W97          12
#define FF_CMP_DCTMAX       13
#define FF_CMP_DCT264       14
#define FF_CMP_MEDIAN_SAD   15
#define FF_CMP_CHROMA       256

    /**
     * ME diamond size & shape
     * - encoding: Set by user.
     * - decoding: unused
     */
    int dia_size;

    /**
     * amount of previous MV predictors (2a+1 x 2a+1 square)
     * - encoding: Set by user.
     * - decoding: unused
     */
    int last_predictor_count;

    /**
     * motion estimation prepass comparison function
     * - encoding: Set by user.
     * - decoding: unused
     */
    int me_pre_cmp;

    /**
     * ME prepass diamond size & shape
     * - encoding: Set by user.
     * - decoding: unused
     */
    int pre_dia_size;

    /**
     * subpel ME quality
     * - encoding: Set by user.
     * - decoding: unused
     */
    int me_subpel_quality;

    /**
     * maximum motion estimation search range in subpel units
     * If 0 then no limit.
     *
     * - encoding: Set by user.
     * - decoding: unused
     */
    int me_range;

    /**
     * slice flags
     * - encoding: unused
     * - decoding: Set by user.
     */
    int slice_flags;
#define SLICE_FLAG_CODED_ORDER    0x0001 ///< draw_horiz_band() is called in coded order instead of display
#define SLICE_FLAG_ALLOW_FIELD    0x0002 ///< allow draw_horiz_band() with field slices (MPEG-2 field pics)
#define SLICE_FLAG_ALLOW_PLANE    0x0004 ///< allow draw_horiz_band() with 1 component at a time (SVQ1)

    /**
     * macroblock decision mode
     * - encoding: Set by user.
     * - decoding: unused
     */
    int mb_decision;
#define FF_MB_DECISION_SIMPLE 0        ///< uses mb_cmp
#define FF_MB_DECISION_BITS   1        ///< chooses the one which needs the fewest bits
#define FF_MB_DECISION_RD     2        ///< rate distortion

    /**
     * custom intra quantization matrix
     * Must be allocated with the av_malloc() family of functions, and will be freed in
     * avcodec_free_context().
     * - encoding: Set/allocated by user, freed by libavcodec. Can be NULL.
     * - decoding: Set/allocated/freed by libavcodec.
     */
    uint16_t *intra_matrix;

    /**
     * custom inter quantization matrix
     * Must be allocated with the av_malloc() family of functions, and will be freed in
     * avcodec_free_context().
     * - encoding: Set/allocated by user, freed by libavcodec. Can be NULL.
     * - decoding: Set/allocated/freed by libavcodec.
     */
    uint16_t *inter_matrix;

    /**
     * precision of the intra DC coefficient - 8
     * - encoding: Set by user.
     * - decoding: Set by libavcodec
     */
    int intra_dc_precision;

    /**
     * Number of macroblock rows at the top which are skipped.
     * - encoding: unused
     * - decoding: Set by user.
     */
    int skip_top;

    /**
     * Number of macroblock rows at the bottom which are skipped.
     * - encoding: unused
     * - decoding: Set by user.
     */
    int skip_bottom;

    /**
     * minimum MB Lagrange multiplier
     * - encoding: Set by user.
     * - decoding: unused
     */
    int mb_lmin;

    /**
     * maximum MB Lagrange multiplier
     * - encoding: Set by user.
     * - decoding: unused
     */
    int mb_lmax;

    /**
     * - encoding: Set by user.
     * - decoding: unused
     */
    int bidir_refine;

    /**
     * minimum GOP size
     * - encoding: Set by user.
     * - decoding: unused
     */
    int keyint_min;

    /**
     * number of reference frames
     * - encoding: Set by user.
     * - decoding: Set by lavc.
     */
    int refs;

    /**
     * Note: Value depends upon the compare function used for fullpel ME.
     * - encoding: Set by user.
     * - decoding: unused
     */
    int mv0_threshold;

    /**
     * Chromaticity coordinates of the source primaries.
     * - encoding: Set by user
     * - decoding: Set by libavcodec
     */
    enum AVColorPrimaries color_primaries;

    /**
     * Color Transfer Characteristic.
     * - encoding: Set by user
     * - decoding: Set by libavcodec
     */
    enum AVColorTransferCharacteristic color_trc;

    /**
     * YUV colorspace type.
     * - encoding: Set by user
     * - decoding: Set by libavcodec
     */
    enum AVColorSpace colorspace;

    /**
     * MPEG vs JPEG YUV range.
     * - encoding: Set by user
     * - decoding: Set by libavcodec
     */
    enum AVColorRange color_range;

    /**
     * This defines the location of chroma samples.
     * - encoding: Set by user
     * - decoding: Set by libavcodec
     */
    enum AVChromaLocation chroma_sample_location;

    /**
     * Number of slices.
     * Indicates number of picture subdivisions. Used for parallelized
     * decoding.
     * - encoding: Set by user
     * - decoding: unused
     */
    int slices;

    /** Field order
     * - encoding: set by libavcodec
     * - decoding: Set by user.
     */
    enum AVFieldOrder field_order;

    /* audio only */
    int sample_rate; ///< samples per second
    int channels;    ///< number of audio channels

    /**
     * audio sample format
     * - encoding: Set by user.
     * - decoding: Set by libavcodec.
     */
    enum AVSampleFormat sample_fmt;  ///< sample format

    /* The following data should not be initialized. */
    /**
     * Number of samples per channel in an audio frame.
     *
     * - encoding: set by libavcodec in avcodec_open2(). Each submitted frame
     *   except the last must contain exactly frame_size samples per channel.
     *   May be 0 when the codec has AV_CODEC_CAP_VARIABLE_FRAME_SIZE set, then the
     *   frame size is not restricted.
     * - decoding: may be set by some decoders to indicate constant frame size
     */
    int frame_size;

    /**
     * Frame counter, set by libavcodec.
     *
     * - decoding: total number of frames returned from the decoder so far.
     * - encoding: total number of frames passed to the encoder so far.
     *
     *   @note the counter is not incremented if encoding/decoding resulted in
     *   an error.
     */
    int frame_number;

    /**
     * number of bytes per packet if constant and known or 0
     * Used by some WAV based audio codecs.
     */
    int block_align;

    /**
     * Audio cutoff bandwidth (0 means "automatic")
     * - encoding: Set by user.
     * - decoding: unused
     */
    int cutoff;

    /**
     * Audio channel layout.
     * - encoding: set by user.
     * - decoding: set by user, may be overwritten by libavcodec.
     */
    uint64_t channel_layout;

    /**
     * Request decoder to use this channel layout if it can (0 for default)
     * - encoding: unused
     * - decoding: Set by user.
     */
    uint64_t request_channel_layout;

    /**
     * Type of service that the audio stream conveys.
     * - encoding: Set by user.
     * - decoding: Set by libavcodec.
     */
    enum AVAudioServiceType audio_service_type;

    /**
     * desired sample format
     * - encoding: Not used.
     * - decoding: Set by user.
     * Decoder will decode to this format if it can.
     */
    enum AVSampleFormat request_sample_fmt;

    /**
     * This callback is called at the beginning of each frame to get data
     * buffer(s) for it. There may be one contiguous buffer for all the data or
     * there may be a buffer per each data plane or anything in between. What
     * this means is, you may set however many entries in buf[] you feel necessary.
     * Each buffer must be reference-counted using the AVBuffer API (see description
     * of buf[] below).
     *
     * The following fields will be set in the frame before this callback is
     * called:
     * - format
     * - width, height (video only)
     * - sample_rate, channel_layout, nb_samples (audio only)
     * Their values may differ from the corresponding values in
     * AVCodecContext. This callback must use the frame values, not the codec
     * context values, to calculate the required buffer size.
     *
     * This callback must fill the following fields in the frame:
     * - data[]
     * - linesize[]
     * - extended_data:
     *   * if the data is planar audio with more than 8 channels, then this
     *     callback must allocate and fill extended_data to contain all pointers
     *     to all data planes. data[] must hold as many pointers as it can.
     *     extended_data must be allocated with av_malloc() and will be freed in
     *     av_frame_unref().
     *   * otherwise extended_data must point to data
     * - buf[] must contain one or more pointers to AVBufferRef structures. Each of
     *   the frame's data and extended_data pointers must be contained in these. That
     *   is, one AVBufferRef for each allocated chunk of memory, not necessarily one
     *   AVBufferRef per data[] entry. See: av_buffer_create(), av_buffer_alloc(),
     *   and av_buffer_ref().
     * - extended_buf and nb_extended_buf must be allocated with av_malloc() by
     *   this callback and filled with the extra buffers if there are more
     *   buffers than buf[] can hold. extended_buf will be freed in
     *   av_frame_unref().
     *
     * If AV_CODEC_CAP_DR1 is not set then get_buffer2() must call
     * avcodec_default_get_buffer2() instead of providing buffers allocated by
     * some other means.
     *
     * Each data plane must be aligned to the maximum required by the target
     * CPU.
     *
     * @see avcodec_default_get_buffer2()
     *
     * Video:
     *
     * If AV_GET_BUFFER_FLAG_REF is set in flags then the frame may be reused
     * (read and/or written to if it is writable) later by libavcodec.
     *
     * avcodec_align_dimensions2() should be used to find the required width and
     * height, as they normally need to be rounded up to the next multiple of 16.
     *
     * Some decoders do not support linesizes changing between frames.
     *
     * If frame multithreading is used, this callback may be called from a
     * different thread, but not from more than one at once. Does not need to be
     * reentrant.
     *
     * @see avcodec_align_dimensions2()
     *
     * Audio:
     *
     * Decoders request a buffer of a particular size by setting
     * AVFrame.nb_samples prior to calling get_buffer2(). The decoder may,
     * however, utilize only part of the buffer by setting AVFrame.nb_samples
     * to a smaller value in the output frame.
     *
     * As a convenience, av_samples_get_buffer_size() and
     * av_samples_fill_arrays() in libavutil may be used by custom get_buffer2()
     * functions to find the required data size and to fill data pointers and
     * linesize. In AVFrame.linesize, only linesize[0] may be set for audio
     * since all planes must be the same size.
     *
     * @see av_samples_get_buffer_size(), av_samples_fill_arrays()
     *
     * - encoding: unused
     * - decoding: Set by libavcodec, user can override.
     */
    int (*get_buffer2)(struct AVCodecContext *s, AVFrame *frame, int flags);

    /* - encoding parameters */
    float qcompress;  ///< amount of qscale change between easy & hard scenes (0.0-1.0)
    float qblur;      ///< amount of qscale smoothing over time (0.0-1.0)

    /**
     * minimum quantizer
     * - encoding: Set by user.
     * - decoding: unused
     */
    int qmin;

    /**
     * maximum quantizer
     * - encoding: Set by user.
     * - decoding: unused
     */
    int qmax;

    /**
     * maximum quantizer difference between frames
     * - encoding: Set by user.
     * - decoding: unused
     */
    int max_qdiff;

    /**
     * decoder bitstream buffer size
     * - encoding: Set by user.
     * - decoding: unused
     */
    int rc_buffer_size;

    /**
     * ratecontrol override, see RcOverride
     * - encoding: Allocated/set/freed by user.
     * - decoding: unused
     */
    int rc_override_count;
    RcOverride *rc_override;

    /**
     * maximum bitrate
     * - encoding: Set by user.
     * - decoding: Set by user, may be overwritten by libavcodec.
     */
    int64_t rc_max_rate;

    /**
     * minimum bitrate
     * - encoding: Set by user.
     * - decoding: unused
     */
    int64_t rc_min_rate;

    /**
     * Ratecontrol attempt to use, at maximum, <value> of what can be used without an underflow.
     * - encoding: Set by user.
     * - decoding: unused.
     */
    float rc_max_available_vbv_use;

    /**
     * Ratecontrol attempt to use, at least, <value> times the amount needed to prevent a vbv overflow.
     * - encoding: Set by user.
     * - decoding: unused.
     */
    float rc_min_vbv_overflow_use;

    /**
     * Number of bits which should be loaded into the rc buffer before decoding starts.
     * - encoding: Set by user.
     * - decoding: unused
     */
    int rc_initial_buffer_occupancy;

    /**
     * trellis RD quantization
     * - encoding: Set by user.
     * - decoding: unused
     */
    int trellis;

    /**
     * pass1 encoding statistics output buffer
     * - encoding: Set by libavcodec.
     * - decoding: unused
     */
    char *stats_out;

    /**
     * pass2 encoding statistics input buffer
     * Concatenated stuff from stats_out of pass1 should be placed here.
     * - encoding: Allocated/set/freed by user.
     * - decoding: unused
     */
    char *stats_in;

    /**
     * Work around bugs in encoders which sometimes cannot be detected automatically.
     * - encoding: Set by user
     * - decoding: Set by user
     */
    int workaround_bugs;
#define FF_BUG_AUTODETECT       1  ///< autodetection
#define FF_BUG_XVID_ILACE       4
#define FF_BUG_UMP4             8
#define FF_BUG_NO_PADDING       16
#define FF_BUG_AMV              32
#define FF_BUG_QPEL_CHROMA      64
#define FF_BUG_STD_QPEL         128
#define FF_BUG_QPEL_CHROMA2     256
#define FF_BUG_DIRECT_BLOCKSIZE 512
#define FF_BUG_EDGE             1024
#define FF_BUG_HPEL_CHROMA      2048
#define FF_BUG_DC_CLIP          4096
#define FF_BUG_MS               8192 ///< Work around various bugs in Microsoft's broken decoders.
#define FF_BUG_TRUNCATED       16384
#define FF_BUG_IEDGE           32768

    /**
     * strictly follow the standard (MPEG-4, ...).
     * - encoding: Set by user.
     * - decoding: Set by user.
     * Setting this to STRICT or higher means the encoder and decoder will
     * generally do stupid things, whereas setting it to unofficial or lower
     * will mean the encoder might produce output that is not supported by all
     * spec-compliant decoders. Decoders don't differentiate between normal,
     * unofficial and experimental (that is, they always try to decode things
     * when they can) unless they are explicitly asked to behave stupidly
     * (=strictly conform to the specs)
     */
    int strict_std_compliance;
#define FF_COMPLIANCE_VERY_STRICT   2 ///< Strictly conform to an older more strict version of the spec or reference software.
#define FF_COMPLIANCE_STRICT        1 ///< Strictly conform to all the things in the spec no matter what consequences.
#define FF_COMPLIANCE_NORMAL        0
#define FF_COMPLIANCE_UNOFFICIAL   -1 ///< Allow unofficial extensions
#define FF_COMPLIANCE_EXPERIMENTAL -2 ///< Allow nonstandardized experimental things.

    /**
     * error concealment flags
     * - encoding: unused
     * - decoding: Set by user.
     */
    int error_concealment;
#define FF_EC_GUESS_MVS   1
#define FF_EC_DEBLOCK     2
#define FF_EC_FAVOR_INTER 256

    /**
     * debug
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int debug;
#define FF_DEBUG_PICT_INFO   1
#define FF_DEBUG_RC          2
#define FF_DEBUG_BITSTREAM   4
#define FF_DEBUG_MB_TYPE     8
#define FF_DEBUG_QP          16
#define FF_DEBUG_DCT_COEFF   0x00000040
#define FF_DEBUG_SKIP        0x00000080
#define FF_DEBUG_STARTCODE   0x00000100
#define FF_DEBUG_ER          0x00000400
#define FF_DEBUG_MMCO        0x00000800
#define FF_DEBUG_BUGS        0x00001000
#define FF_DEBUG_BUFFERS     0x00008000
#define FF_DEBUG_THREADS     0x00010000
#define FF_DEBUG_GREEN_MD    0x00800000
#define FF_DEBUG_NOMC        0x01000000

    /**
     * Error recognition; may misdetect some more or less valid parts as errors.
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int err_recognition;

/**
 * Verify checksums embedded in the bitstream (could be of either encoded or
 * decoded data, depending on the codec) and print an error message on mismatch.
 * If AV_EF_EXPLODE is also set, a mismatching checksum will result in the
 * decoder returning an error.
 */
#define AV_EF_CRCCHECK  (1<<0)
#define AV_EF_BITSTREAM (1<<1)          ///< detect bitstream specification deviations
#define AV_EF_BUFFER    (1<<2)          ///< detect improper bitstream length
#define AV_EF_EXPLODE   (1<<3)          ///< abort decoding on minor error detection

#define AV_EF_IGNORE_ERR (1<<15)        ///< ignore errors and continue
#define AV_EF_CAREFUL    (1<<16)        ///< consider things that violate the spec, are fast to calculate and have not been seen in the wild as errors
#define AV_EF_COMPLIANT  (1<<17)        ///< consider all spec non compliances as errors
#define AV_EF_AGGRESSIVE (1<<18)        ///< consider things that a sane encoder should not do as an error


    /**
     * opaque 64-bit number (generally a PTS) that will be reordered and
     * output in AVFrame.reordered_opaque
     * - encoding: Set by libavcodec to the reordered_opaque of the input
     *             frame corresponding to the last returned packet. Only
     *             supported by encoders with the
     *             AV_CODEC_CAP_ENCODER_REORDERED_OPAQUE capability.
     * - decoding: Set by user.
     */
    int64_t reordered_opaque;

    /**
     * Hardware accelerator in use
     * - encoding: unused.
     * - decoding: Set by libavcodec
     */
    const struct AVHWAccel *hwaccel;

    /**
     * Hardware accelerator context.
     * For some hardware accelerators, a global context needs to be
     * provided by the user. In that case, this holds display-dependent
     * data FFmpeg cannot instantiate itself. Please refer to the
     * FFmpeg HW accelerator documentation to know how to fill this.
     * - encoding: unused
     * - decoding: Set by user
     */
    void *hwaccel_context;

    /**
     * error
     * - encoding: Set by libavcodec if flags & AV_CODEC_FLAG_PSNR.
     * - decoding: unused
     */
    uint64_t error[AV_NUM_DATA_POINTERS];

    /**
     * DCT algorithm, see FF_DCT_* below
     * - encoding: Set by user.
     * - decoding: unused
     */
    int dct_algo;
#define FF_DCT_AUTO    0
#define FF_DCT_FASTINT 1
#define FF_DCT_INT     2
#define FF_DCT_MMX     3
#define FF_DCT_ALTIVEC 5
#define FF_DCT_FAAN    6

    /**
     * IDCT algorithm, see FF_IDCT_* below.
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int idct_algo;
#define FF_IDCT_AUTO          0
#define FF_IDCT_INT           1
#define FF_IDCT_SIMPLE        2
#define FF_IDCT_SIMPLEMMX     3
#define FF_IDCT_ARM           7
#define FF_IDCT_ALTIVEC       8
#define FF_IDCT_SIMPLEARM     10
#define FF_IDCT_XVID          14
#define FF_IDCT_SIMPLEARMV5TE 16
#define FF_IDCT_SIMPLEARMV6   17
#define FF_IDCT_FAAN          20
#define FF_IDCT_SIMPLENEON    22
#define FF_IDCT_NONE          24 /* Used by XvMC to extract IDCT coefficients with FF_IDCT_PERM_NONE */
#define FF_IDCT_SIMPLEAUTO    128

    /**
     * bits per sample/pixel from the demuxer (needed for huffyuv).
     * - encoding: Set by libavcodec.
     * - decoding: Set by user.
     */
     int bits_per_coded_sample;

    /**
     * Bits per sample/pixel of internal libavcodec pixel/sample format.
     * - encoding: set by user.
     * - decoding: set by libavcodec.
     */
    int bits_per_raw_sample;

    /**
     * low resolution decoding, 1-> 1/2 size, 2->1/4 size
     * - encoding: unused
     * - decoding: Set by user.
     */
     int lowres;

    /**
     * thread count
     * is used to decide how many independent tasks should be passed to execute()
     * - encoding: Set by user.
     * - decoding: Set by user.
     */
    int thread_count;

    /**
     * Which multithreading methods to use.
     * Use of FF_THREAD_FRAME will increase decoding delay by one frame per thread,
     * so clients which cannot provide future frames should not use it.
     *
     * - encoding: Set by user, otherwise the default is used.
     * - decoding: Set by user, otherwise the default is used.
     */
    int thread_type;
#define FF_THREAD_FRAME   1 ///< Decode more than one frame at once
#define FF_THREAD_SLICE   2 ///< Decode more than one part of a single frame at once

    /**
     * Which multithreading methods are in use by the codec.
     * - encoding: Set by libavcodec.
     * - decoding: Set by libavcodec.
     */
    int active_thread_type;
} AVCodecContext;

typedef struct {
    AVFrame  *indata;
    AVPacket *outdata;
    int       return_code;
    int       finished;
} Task;

typedef struct {
    AVCodecContext *parent_avctx;
    pthread_mutex_t buffer_mutex;
    pthread_mutex_t task_fifo_mutex;
    pthread_cond_t task_fifo_cond;
    unsigned max_tasks;
    Task tasks[BUFFER_SIZE];
    pthread_mutex_t finished_task_mutex;
    pthread_cond_t finished_task_cond;
    unsigned next_task_index;
    unsigned task_index;
    unsigned finished_task_index;
    pthread_t worker[MAX_THREADS];
    atomic_int exit;
} ThreadContext;

void *av_malloc(size_t size);
void *av_mallocz(size_t size);
void av_free(void *ptr);
int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
int avcodec_close(AVCodecContext *avctx);
void av_log(void *avcl, int level, const char *fmt, ...);
int av_cpu_count(void);
AVFrame *av_frame_alloc(void);
AVPacket *av_packet_alloc(void);
int av_opt_copy(void *dest, const void *src);
int av_opt_get_int(void *obj, const char *name, int search_flags, int64_t *out_val);
void ff_frame_thread_encoder_free(AVCodecContext *avctx);
AVCodecContext *avcodec_alloc_context3(const AVCodec *codec);
int ff_frame_thread_encoder_init(AVCodecContext *avctx);
int init_context_defaults(AVCodecContext *s, const AVCodec *codec);
void *worker(void *v);

AVCodecContext *avcodec_alloc_context3(const AVCodec *codec)
{
    AVCodecContext *avctx= av_malloc(sizeof(AVCodecContext));

    if (!avctx)
        return NULL;

    if (init_context_defaults(avctx, codec) < 0) {
        av_free(avctx);
        return NULL;
    }

    return avctx;
}

int ff_frame_thread_encoder_init(AVCodecContext *avctx)
{
    int i=0;
    ThreadContext *c;


    if(   !(avctx->thread_type & FF_THREAD_FRAME)
       || !(avctx->codec->capabilities & AV_CODEC_CAP_FRAME_THREADS))
        return 0;

    if(   !avctx->thread_count
       && avctx->codec_id == AV_CODEC_ID_MJPEG
       && !(avctx->flags & AV_CODEC_FLAG_QSCALE)) {
        av_log(avctx, AV_LOG_DEBUG,
               "Forcing thread count to 1 for MJPEG encoding, use -thread_type slice "
               "or a constant quantizer if you want to use multiple cpu cores\n");
        avctx->thread_count = 1;
    }
    if(   avctx->thread_count > 1
       && avctx->codec_id == AV_CODEC_ID_MJPEG
       && !(avctx->flags & AV_CODEC_FLAG_QSCALE))
        av_log(avctx, AV_LOG_WARNING,
               "MJPEG CBR encoding works badly with frame multi-threading, consider "
               "using -threads 1, -thread_type slice or a constant quantizer.\n");

    if (avctx->codec_id == AV_CODEC_ID_HUFFYUV ||
        avctx->codec_id == AV_CODEC_ID_FFVHUFF) {
        int warn = 0;
        int64_t tmp;

        if (avctx->flags & AV_CODEC_FLAG_PASS1)
            warn = 1;
        else if (av_opt_get_int(avctx->priv_data, "context", 0, &tmp) >= 0 &&
                 tmp > 0) {
            warn = av_opt_get_int(avctx->priv_data, "non_deterministic", 0, &tmp) < 0
                   || !tmp;
        }
        // huffyuv does not support these with multiple frame threads currently
        if (warn) {
            av_log(avctx, AV_LOG_WARNING,
               "Forcing thread count to 1 for huffyuv encoding with first pass or context 1\n");
            avctx->thread_count = 1;
        }
    }

    if(!avctx->thread_count) {
        avctx->thread_count = av_cpu_count();
        avctx->thread_count = FFMIN(avctx->thread_count, MAX_THREADS);
    }

    if(avctx->thread_count <= 1)
        return 0;

    if(avctx->thread_count > MAX_THREADS)
        return AVERROR(EINVAL);

    av_assert0(!avctx->internal->frame_thread_encoder);
    c = avctx->internal->frame_thread_encoder = av_mallocz(sizeof(ThreadContext));
    if(!c)
        return AVERROR(ENOMEM);

    c->parent_avctx = avctx;

    pthread_mutex_init(&c->task_fifo_mutex, NULL);
    pthread_mutex_init(&c->finished_task_mutex, NULL);
    pthread_mutex_init(&c->buffer_mutex, NULL);
    pthread_cond_init(&c->task_fifo_cond, NULL);
    pthread_cond_init(&c->finished_task_cond, NULL);
    atomic_init(&c->exit, 0);

    c->max_tasks = avctx->thread_count + 2;
    for (unsigned i = 0; i < c->max_tasks; i++) {
        if (!(c->tasks[i].indata  = av_frame_alloc()) ||
            !(c->tasks[i].outdata = av_packet_alloc()))
            goto fail;
    }

    for(i=0; i<avctx->thread_count ; i++){
        int ret;
        void *tmpv;
        AVCodecContext *thread_avctx = avcodec_alloc_context3(avctx->codec);
        if(!thread_avctx)
            goto fail;
        tmpv = thread_avctx->priv_data;
        *thread_avctx = *avctx;
        ret = av_opt_copy(thread_avctx, avctx);
        if (ret < 0)
            goto fail;
        thread_avctx->priv_data = tmpv;
        thread_avctx->internal = NULL;
        if (avctx->codec->priv_class) {
            int ret = av_opt_copy(thread_avctx->priv_data, avctx->priv_data);
            if (ret < 0)
                goto fail;
        }
        thread_avctx->thread_count = 1;
        thread_avctx->active_thread_type &= ~FF_THREAD_FRAME;

        if (avcodec_open2(thread_avctx, avctx->codec, NULL) < 0)
            goto fail;
        av_assert0(!thread_avctx->internal->frame_thread_encoder);
        thread_avctx->internal->frame_thread_encoder = c;
        if(pthread_create(&c->worker[i], NULL, worker, thread_avctx)) {
            goto fail;
        }
    }

    avctx->active_thread_type = FF_THREAD_FRAME;

    return 0;
fail:
    avctx->thread_count = i;
    av_log(avctx, AV_LOG_ERROR, "ff_frame_thread_encoder_init failed\n");
    ff_frame_thread_encoder_free(avctx);
    return -1;
}
