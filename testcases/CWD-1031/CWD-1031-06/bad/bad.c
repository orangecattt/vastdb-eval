#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>

// FROM: libavutil/macros.h
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

// FROM: libavutil/internal.h
#ifndef emms_c
#   define emms_c() do {} while(0)
#endif

// FROM: libavutil/common.h
static inline int av_clip_c(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}
#define av_clip(a, amin, amax) av_clip_c(a, amin, amax)

// FROM: libavutil/frame.h
#define AV_NUM_DATA_POINTERS 8

// FROM: libavcodec/vp3.c
#define MODE_INTER_NO_MV      0
#define MODE_INTRA            1
#define MODE_INTER_PLUS_MV    2
#define MODE_INTER_LAST_MV    3
#define MODE_INTER_PRIOR_LAST 4
#define MODE_USING_GOLDEN     5
#define MODE_GOLDEN_MV        6
#define MODE_INTER_FOURMV     7
#define CODING_MODE_COUNT     8

// FROM: libavcodec/vp3.c
#define MODE_COPY             8

// FROM: libavcodec/vp3.c
typedef struct Vp3Fragment {
    int16_t dc;
    uint8_t coding_method;
    uint8_t qpi;
} Vp3Fragment;

// FROM: libavutil/frame.h (simplified AVFrame)
typedef struct AVFrame {
    uint8_t *data[AV_NUM_DATA_POINTERS];
    int linesize[AV_NUM_DATA_POINTERS];
    uint8_t **extended_data;
    int width, height;
    int nb_samples;
    int format;
    int key_frame;
    int pict_type;
    int crop_left;
    int crop_right;
    int crop_top;
    int crop_bottom;
} AVFrame;

// FROM: libavcodec/thread.h (simplified)
typedef struct ThreadFrame {
    AVFrame *f;
} ThreadFrame;

// FROM: libavcodec/hpeldsp.h (simplified HpelDSPContext)
typedef struct HpelDSPContext {
    void (*put_pixels_tab[4][4])(uint8_t *dst, const uint8_t *src, ptrdiff_t stride, int h);
    void (*put_no_rnd_pixels_tab[4][4])(uint8_t *dst, const uint8_t *src, ptrdiff_t stride, int h);
} HpelDSPContext;

// FROM: libavcodec/videodsp.h (simplified VideoDSPContext)
typedef struct VideoDSPContext {
    void (*emulated_edge_mc)(uint8_t *dst, const uint8_t *src, ptrdiff_t dst_stride, ptrdiff_t src_stride, int block_w, int block_h, int src_x, int src_y, int w, int h);
} VideoDSPContext;

// FROM: libavcodec/vp3dsp.h
typedef struct VP3DSPContext {
    void (*put_no_rnd_pixels_l2)(uint8_t *dst,
                                 const uint8_t *a,
                                 const uint8_t *b,
                                 ptrdiff_t stride, int h);

    void (*idct_put)(uint8_t *dest, ptrdiff_t stride, int16_t *block);
    void (*idct_add)(uint8_t *dest, ptrdiff_t stride, int16_t *block);
    void (*idct_dc_add)(uint8_t *dest, ptrdiff_t stride, int16_t *block);
    void (*v_loop_filter)(uint8_t *src, ptrdiff_t stride, int *bounding_values);
    void (*h_loop_filter)(uint8_t *src, ptrdiff_t stride, int *bounding_values);
    void (*v_loop_filter_unaligned)(uint8_t *src, ptrdiff_t stride, int *bounding_values);
    void (*h_loop_filter_unaligned)(uint8_t *src, ptrdiff_t stride, int *bounding_values);
} VP3DSPContext;

// FROM: libavcodec/vp3.c
static const uint8_t hilbert_offset[16][2] = {
    { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 },
    { 0, 2 }, { 0, 3 }, { 1, 3 }, { 1, 2 },
    { 2, 2 }, { 2, 3 }, { 3, 3 }, { 3, 2 },
    { 3, 1 }, { 2, 1 }, { 2, 0 }, { 3, 0 }
};

// FROM: libavcodec/get_bits.h (simplified GetBitContext)
typedef struct GetBitContext {
    const uint8_t *buffer;
    int size;
    int index;
} GetBitContext;

// FROM: libavcodec/packet.h (simplified AVPacket)
typedef struct AVPacket {
    const uint8_t *data;
    int size;
} AVPacket;

// FROM: libavcodec/avcodec.h (simplified AVCodecContext)
typedef struct AVCodecContext {
    void *priv_data;
    int flags;
    int debug;
    int coded_width;
    int coded_height;
    int width;
    int height;
    int frame_number;
    int skip_loop_filter;
    int skip_frame;
    int active_thread_type;
    void (*draw_horiz_band)(struct AVCodecContext *avctx, const AVFrame *frame, int offset[AV_NUM_DATA_POINTERS], int y, int type, int h);
} AVCodecContext;

// FROM: libavcodec/vp3.c
typedef struct Vp3DecodeContext {
    AVCodecContext *avctx;
    int theora, theora_tables, theora_header;
    int version;
    int width, height;
    int chroma_x_shift, chroma_y_shift;
    ThreadFrame golden_frame;
    ThreadFrame last_frame;
    ThreadFrame current_frame;
    int keyframe;
    uint8_t idct_permutation[64];
    uint8_t idct_scantable[64];
    HpelDSPContext hdsp;
    VideoDSPContext vdsp;
    VP3DSPContext vp3dsp;
    int16_t block[64];
    int flipped_image;
    int last_slice_end;
    int skip_loop_filter;

    int qps[3];
    int nqps;
    int last_qps[3];

    int superblock_count;
    int y_superblock_width;
    int y_superblock_height;
    int y_superblock_count;
    int c_superblock_width;
    int c_superblock_height;
    int c_superblock_count;
    int u_superblock_start;
    int v_superblock_start;
    unsigned char *superblock_coding;

    int macroblock_count;
    int macroblock_width;
    int macroblock_height;
    int c_macroblock_count;
    int c_macroblock_width;
    int c_macroblock_height;
    int yuv_macroblock_count;

    int fragment_count;
    int fragment_width[2];
    int fragment_height[2];

    Vp3Fragment *all_fragments;
    int fragment_start[3];
    int data_offset[3];
    uint8_t offset_x;
    uint8_t offset_y;
    int offset_x_warned;

    int8_t (*motion_val[2])[2];

    uint16_t coded_dc_scale_factor[2][64];
    uint32_t coded_ac_scale_factor[64];
    uint8_t base_matrix[384][64];
    uint8_t qr_count[2][3];
    uint8_t qr_size[2][3][64];
    uint16_t qr_base[2][3][64];

    int16_t *dct_tokens[3][64];
    int16_t *dct_tokens_base;

    int num_coded_frags[3][64];
    int total_num_coded_frags;

    int *coded_fragment_list[3];

    int *kf_coded_fragment_list;
    int *nkf_coded_fragment_list;
    int num_kf_coded_fragment[3];

    void *coeff_vlc;

    void *superblock_run_length_vlc;
    void *fragment_run_length_vlc;
    void *block_pattern_vlc[2];
    void *mode_code_vlc;
    void *motion_vector_vlc;
    void *vp4_mv_vlc[2][7];

    int16_t qmat[3][2][3][64];

    int *superblock_fragments;

    unsigned char *macroblock_coding;

    uint8_t *edge_emu_buffer;

    void *huffman_table[5 * 16];

    uint8_t filter_limit_values[64];
    int bounding_values_array[256 + 2];

    void *dc_pred_row;
} Vp3DecodeContext;

// FROM: libavcodec/vp3.c (stub functions for external dependencies)
static void ff_thread_report_progress(ThreadFrame *f, int progress, int field) {}
static void ff_thread_await_progress(ThreadFrame *f, int progress, int field) {}
static int ff_thread_get_ext_buffer(AVCodecContext *avctx, ThreadFrame *f, int flags) { return 0; }
static void ff_thread_release_ext_buffer(AVCodecContext *avctx, ThreadFrame *f) {}
static int ff_thread_ref_frame(ThreadFrame *dst, const ThreadFrame *src) { return 0; }
static void ff_thread_finish_setup(AVCodecContext *avctx) {}
static int init_get_bits8(GetBitContext *s, const uint8_t *buffer, int byte_size) { return 0; }
static int get_bits1(GetBitContext *s) { return 0; }
static int get_bits(GetBitContext *s, int n) { return 0; }
static void skip_bits(GetBitContext *s, int n) {}
static void skip_bits_long(GetBitContext *s, int n) {}
static void *av_malloc(size_t size) { return malloc(size); }
static void av_log(void *avcl, int level, const char *fmt, ...) {}
static int av_frame_ref(AVFrame *dst, const AVFrame *src) { return 0; }
static void av_frame_unref(AVFrame *frame) {}
static int vp3_decode_end(AVCodecContext *avctx) { return 0; }
static int vp3_decode_init(AVCodecContext *avctx) { return 0; }
static int theora_decode_header(AVCodecContext *avctx, GetBitContext *gb) { return 0; }
static int theora_decode_tables(AVCodecContext *avctx, GetBitContext *gb) { return 0; }
static void init_loop_filter(Vp3DecodeContext *s) {}
static void init_dequantizer(Vp3DecodeContext *s, int i) {}
static int unpack_superblocks(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int vp4_unpack_macroblocks(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int unpack_modes(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int unpack_vectors(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int unpack_block_qpis(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int unpack_dct_coeffs(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int vp4_unpack_dct_coeffs(Vp3DecodeContext *s, GetBitContext *gb) { return 0; }
static int update_frames(AVCodecContext *avctx) { return 0; }
static int vp4_mc_loop_filter(Vp3DecodeContext *s, int plane, int motion_x, int motion_y, int bx, int by, uint8_t *motion_source, int stride, int src_x, int src_y, uint8_t *temp) { return 0; }

// FROM: libavcodec/vp3.c
static void apply_loop_filter(Vp3DecodeContext *s, int plane,
                              int ystart, int yend)
{
    int x, y;
    int *bounding_values = s->bounding_values_array + 127;

    int width           = s->fragment_width[!!plane];
    int height          = s->fragment_height[!!plane];
    int fragment        = s->fragment_start[plane] + ystart * width;
    ptrdiff_t stride    = s->current_frame.f->linesize[plane];
    uint8_t *plane_data = s->current_frame.f->data[plane];
    if (!s->flipped_image)
        stride = -stride;
    plane_data += s->data_offset[plane] + 8 * ystart * stride;

    for (y = ystart; y < yend; y++) {
        for (x = 0; x < width; x++) {
            if (s->all_fragments[fragment].coding_method != MODE_COPY) {
                if (x > 0) {
                    s->vp3dsp.h_loop_filter(
                        plane_data + 8 * x,
                        stride, bounding_values);
                }

                if (y > 0) {
                    s->vp3dsp.v_loop_filter(
                        plane_data + 8 * x,
                        stride, bounding_values);
                }

                if ((x < width - 1) &&
                    (s->all_fragments[fragment + 1].coding_method == MODE_COPY)) {
                    s->vp3dsp.h_loop_filter(
                        plane_data + 8 * x + 8,
                        stride, bounding_values);
                }

                if ((y < height - 1) &&
                    (s->all_fragments[fragment + width].coding_method == MODE_COPY)) {
                    s->vp3dsp.v_loop_filter(
                        plane_data + 8 * x + 8 * stride,
                        stride, bounding_values);
                }
            }

            fragment++;
        }
        plane_data += 8 * stride;
    }
}

// FROM: libavcodec/vp3.c
static inline int vp3_dequant(Vp3DecodeContext *s, Vp3Fragment *frag,
                              int plane, int inter, int16_t block[64])
{
    int16_t *dequantizer = s->qmat[frag->qpi][inter][plane];
    uint8_t *perm = s->idct_scantable;
    int i = 0;

    do {
        int token = *s->dct_tokens[plane][i];
        switch (token & 3) {
        case 0:
            if (--token < 4)
                s->dct_tokens[plane][i]++;
            else
                *s->dct_tokens[plane][i] = token & ~3;
            goto end;
        case 1:
            s->dct_tokens[plane][i]++;
            i += (token >> 2) & 0x7f;
            if (i > 63) {
                return i;
            }
            block[perm[i]] = (token >> 9) * dequantizer[perm[i]];
            i++;
            break;
        case 2:
            block[perm[i]] = (token >> 2) * dequantizer[perm[i]];
            s->dct_tokens[plane][i++]++;
            break;
        default:
            return i;
        }
    } while (i < 64);
    i--;
end:
    block[0] = frag->dc * s->qmat[0][inter][plane][0];
    return i;
}

// FROM: libavcodec/vp3.c
static void vp3_draw_horiz_band(Vp3DecodeContext *s, int y)
{
    int h, cy, i;
    int offset[AV_NUM_DATA_POINTERS];

    if (0 && s->avctx->active_thread_type & 0x0002) {
        int y_flipped = s->flipped_image ? s->height - y : y;

        ff_thread_report_progress(&s->current_frame,
                                  y_flipped == s->height ? INT_MAX
                                                         : y_flipped - 1,
                                  0);
    }

    if (!s->avctx->draw_horiz_band)
        return;

    h = y - s->last_slice_end;
    s->last_slice_end = y;
    y -= h;

    if (!s->flipped_image)
        y = s->height - y - h;

    cy        = y >> s->chroma_y_shift;
    offset[0] = s->current_frame.f->linesize[0] * y;
    offset[1] = s->current_frame.f->linesize[1] * cy;
    offset[2] = s->current_frame.f->linesize[2] * cy;
    for (i = 3; i < AV_NUM_DATA_POINTERS; i++)
        offset[i] = 0;

    emms_c();
    s->avctx->draw_horiz_band(s->avctx, s->current_frame.f, offset, y, 3, h);
}

// FROM: libavcodec/vp3.c
static void await_reference_row(Vp3DecodeContext *s, Vp3Fragment *fragment,
                                int motion_y, int y)
{
    ThreadFrame *ref_frame;
    int ref_row;
    int border = motion_y & 1;

    if (fragment->coding_method == MODE_USING_GOLDEN ||
        fragment->coding_method == MODE_GOLDEN_MV)
        ref_frame = &s->golden_frame;
    else
        ref_frame = &s->last_frame;

    ref_row = y + (motion_y >> 1);
    ref_row = FFMAX(FFABS(ref_row), ref_row + 8 + border);

    ff_thread_await_progress(ref_frame, ref_row, 0);
}

// FROM: libavcodec/vp3.c
static void render_slice(Vp3DecodeContext *s, int slice)
{
    int x, y, i, j, fragment;
    int16_t *block = s->block;
    int motion_x = 0xdeadbeef, motion_y = 0xdeadbeef;
    int motion_halfpel_index;
    uint8_t *motion_source;
    int plane, first_pixel;

    if (slice >= s->c_superblock_height)
        return;

    for (plane = 0; plane < 3; plane++) {
        uint8_t *output_plane = s->current_frame.f->data[plane] +
                                s->data_offset[plane];
        uint8_t *last_plane = s->last_frame.f->data[plane] +
                              s->data_offset[plane];
        uint8_t *golden_plane = s->golden_frame.f->data[plane] +
                                s->data_offset[plane];
        ptrdiff_t stride = s->current_frame.f->linesize[plane];
        int plane_width  = s->width  >> (plane && s->chroma_x_shift);
        int plane_height = s->height >> (plane && s->chroma_y_shift);
        int8_t(*motion_val)[2] = s->motion_val[!!plane];

        int sb_x, sb_y = slice << (!plane && s->chroma_y_shift);
        int slice_height = sb_y + 1 + (!plane && s->chroma_y_shift);
        int slice_width  = plane ? s->c_superblock_width
                                 : s->y_superblock_width;

        int fragment_width  = s->fragment_width[!!plane];
        int fragment_height = s->fragment_height[!!plane];
        int fragment_start  = s->fragment_start[plane];

        int do_await = !plane && 0 &&
                       (s->avctx->active_thread_type & 0x0002);

        if (!s->flipped_image)
            stride = -stride;
        if (0 && plane && (s->avctx->flags & 0x0001))
            continue;

        for (; sb_y < slice_height; sb_y++) {
            for (sb_x = 0; sb_x < slice_width; sb_x++) {
                for (j = 0; j < 16; j++) {
                    x        = 4 * sb_x + hilbert_offset[j][0];
                    y        = 4 * sb_y + hilbert_offset[j][1];
                    fragment = y * fragment_width + x;

                    i = fragment_start + fragment;

                    if (x >= fragment_width || y >= fragment_height)
                        continue;

                    first_pixel = 8 * y * stride + 8 * x;

                    if (do_await &&
                        s->all_fragments[i].coding_method != MODE_INTRA)
                        await_reference_row(s, &s->all_fragments[i],
                                            motion_val[fragment][1],
                                            (16 * y) >> s->chroma_y_shift);

                    if (s->all_fragments[i].coding_method != MODE_COPY) {
                        if ((s->all_fragments[i].coding_method == MODE_USING_GOLDEN) ||
                            (s->all_fragments[i].coding_method == MODE_GOLDEN_MV))
                            motion_source = golden_plane;
                        else
                            motion_source = last_plane;

                        motion_source       += first_pixel;
                        motion_halfpel_index = 0;

                        if ((s->all_fragments[i].coding_method > MODE_INTRA) &&
                            (s->all_fragments[i].coding_method != MODE_USING_GOLDEN)) {
                            int src_x, src_y;
                            int standard_mc = 1;
                            motion_x = motion_val[fragment][0];
                            motion_y = motion_val[fragment][1];
#if CONFIG_VP4_DECODER
                            if (plane && s->version >= 2) {
                                motion_x = (motion_x >> 1) | (motion_x & 1);
                                motion_y = (motion_y >> 1) | (motion_y & 1);
                            }
#endif

                            src_x = (motion_x >> 1) + 8 * x;
                            src_y = (motion_y >> 1) + 8 * y;

                            motion_halfpel_index = motion_x & 0x01;
                            motion_source       += (motion_x >> 1);

                            motion_halfpel_index |= (motion_y & 0x01) << 1;
                            motion_source        += ((motion_y >> 1) * stride);

#if CONFIG_VP4_DECODER
                            if (s->version >= 2) {
                                uint8_t *temp = s->edge_emu_buffer;
                                if (stride < 0)
                                    temp -= 8 * stride;
                                if (vp4_mc_loop_filter(s, plane, motion_val[fragment][0], motion_val[fragment][1], x, y, motion_source, stride, src_x, src_y, temp)) {
                                    motion_source = temp;
                                    standard_mc = 0;
                                }
                            }
#endif

                            if (standard_mc && (
                                src_x < 0 || src_y < 0 ||
                                src_x + 9 >= plane_width ||
                                src_y + 9 >= plane_height)) {
                                uint8_t *temp = s->edge_emu_buffer;
                                if (stride < 0)
                                    temp -= 8 * stride;

                                s->vdsp.emulated_edge_mc(temp, motion_source,
                                                         stride, stride,
                                                         9, 9, src_x, src_y,
                                                         plane_width,
                                                         plane_height);
                                motion_source = temp;
                            }
                        }

                        if (s->all_fragments[i].coding_method != MODE_INTRA) {
                            if (motion_halfpel_index != 3) {
                                ((void (*)(uint8_t *, const uint8_t *, ptrdiff_t, int))s->hdsp.put_no_rnd_pixels_tab[1][motion_halfpel_index])(
                                    output_plane + first_pixel,
                                    motion_source, stride, 8);
                            } else {
                                int d = (motion_x ^ motion_y) >> 31;
                                s->vp3dsp.put_no_rnd_pixels_l2(output_plane + first_pixel,
                                                               motion_source - d,
                                                               motion_source + stride + 1 + d,
                                                               stride, 8);
                            }
                        }

                        if (s->all_fragments[i].coding_method == MODE_INTRA) {
                            vp3_dequant(s, s->all_fragments + i,
                                        plane, 0, block);
                            s->vp3dsp.idct_put(output_plane + first_pixel,
                                               stride,
                                               block);
                        } else {
                            if (vp3_dequant(s, s->all_fragments + i,
                                            plane, 1, block)) {
                                s->vp3dsp.idct_add(output_plane + first_pixel,
                                                   stride,
                                                   block);
                            } else {
                                s->vp3dsp.idct_dc_add(output_plane + first_pixel,
                                                      stride, block);
                            }
                        }
                    } else {
                        ((void (*)(uint8_t *, const uint8_t *, ptrdiff_t, int))s->hdsp.put_pixels_tab[1][0])(
                            output_plane + first_pixel,
                            last_plane + first_pixel,
                            stride, 8);
                    }
                }
            }

            if (s->version < 2 && !s->skip_loop_filter)
                apply_loop_filter(s, plane, 4 * sb_y - !!sb_y,
                                  FFMIN(4 * sb_y + 3, fragment_height - 1));
        }
    }

    vp3_draw_horiz_band(s, FFMIN((32 << s->chroma_y_shift) * (slice + 1) - 16,
                                 s->height - 16));
}

// FROM: libavcodec/vp3.c
static int vp3_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AVFrame     *frame  = data;
    const uint8_t *buf  = avpkt->data;
    int buf_size        = avpkt->size;
    Vp3DecodeContext *s = avctx->priv_data;
    GetBitContext gb;
    int i, ret;

    if ((ret = init_get_bits8(&gb, buf, buf_size)) < 0)
        return ret;

#if CONFIG_THEORA_DECODER
    if (s->theora && get_bits1(&gb)) {
        int type = get_bits(&gb, 7);
        skip_bits_long(&gb, 6*8);

        if (s->avctx->active_thread_type&0x0002) {
            return -1;
        }
        if (type == 0) {
            vp3_decode_end(avctx);
            ret = theora_decode_header(avctx, &gb);

            if (ret >= 0)
                ret = vp3_decode_init(avctx);
            if (ret < 0) {
                vp3_decode_end(avctx);
                return ret;
            }
            return buf_size;
        } else if (type == 2) {
            vp3_decode_end(avctx);
            ret = theora_decode_tables(avctx, &gb);
            if (ret >= 0)
                ret = vp3_decode_init(avctx);
            if (ret < 0) {
                vp3_decode_end(avctx);
                return ret;
            }
            return buf_size;
        }

        return -1;
    }
#endif

    s->keyframe = !get_bits1(&gb);
    if (!s->all_fragments) {
        return -1;
    }
    if (!s->theora)
        skip_bits(&gb, 1);
    for (i = 0; i < 3; i++)
        s->last_qps[i] = s->qps[i];

    s->nqps = 0;
    do {
        s->qps[s->nqps++] = get_bits(&gb, 6);
    } while (s->theora >= 0x030200 && s->nqps < 3 && get_bits1(&gb));
    for (i = s->nqps; i < 3; i++)
        s->qps[i] = -1;

    if (s->avctx->debug & 0x0001)
        av_log(s->avctx, 0, " VP3 %sframe #%d: Q index = %d\n",
               s->keyframe ? "key" : "", avctx->frame_number + 1, s->qps[0]);

    s->skip_loop_filter = !s->filter_limit_values[s->qps[0]] ||
                          avctx->skip_loop_filter >= (s->keyframe ? 3
                                                                  : 2);

    if (s->qps[0] != s->last_qps[0])
        init_loop_filter(s);

    for (i = 0; i < s->nqps; i++)
        if (s->qps[i] != s->last_qps[i] || s->qps[0] != s->last_qps[0])
            init_dequantizer(s, i);

    if (avctx->skip_frame >= 2 && !s->keyframe)
        return buf_size;

    s->current_frame.f->pict_type = s->keyframe ? 1
                                                : 2;
    s->current_frame.f->key_frame = s->keyframe;
    if ((ret = ff_thread_get_ext_buffer(avctx, &s->current_frame,
                                        0x0001)) < 0)
        goto error;

    if (!s->edge_emu_buffer)
        s->edge_emu_buffer = av_malloc(9 * FFABS(s->current_frame.f->linesize[0]));

    if (s->keyframe) {
        if (!s->theora) {
            skip_bits(&gb, 4);
            skip_bits(&gb, 4);
            if (s->version) {
                int version = get_bits(&gb, 5);
#if !CONFIG_VP4_DECODER
                if (version >= 2) {
                    return -1;
                }
#endif
                s->version = version;
                if (avctx->frame_number == 0)
                    av_log(s->avctx, 0,
                           "VP version: %d\n", s->version);
            }
        }
        if (s->version || s->theora) {
            if (get_bits1(&gb))
                av_log(s->avctx, 0,
                       "Warning, unsupported keyframe coding type?!\n");
            skip_bits(&gb, 2);

#if CONFIG_VP4_DECODER
            if (s->version >= 2) {
                int mb_height, mb_width;
                int mb_width_mul, mb_width_div, mb_height_mul, mb_height_div;

                mb_height = get_bits(&gb, 8);
                mb_width  = get_bits(&gb, 8);
                if (mb_height != s->macroblock_height ||
                    mb_width != s->macroblock_width)
                    ;

                mb_width_mul = get_bits(&gb, 5);
                mb_width_div = get_bits(&gb, 3);
                mb_height_mul = get_bits(&gb, 5);
                mb_height_div = get_bits(&gb, 3);
                if (mb_width_mul != 1 || mb_width_div != 1 || mb_height_mul != 1 || mb_height_div != 1)
                    ;

                if (get_bits(&gb, 2))
                    ;
            }
#endif
        }
    } else {
        if (!s->golden_frame.f->data[0]) {
            av_log(s->avctx, 0,
                   "vp3: first frame not a keyframe\n");

            s->golden_frame.f->pict_type = 1;
            if ((ret = ff_thread_get_ext_buffer(avctx, &s->golden_frame,
                                                0x0001)) < 0)
                goto error;
            ff_thread_release_ext_buffer(avctx, &s->last_frame);
            if ((ret = ff_thread_ref_frame(&s->last_frame,
                                           &s->golden_frame)) < 0)
                goto error;
            ff_thread_report_progress(&s->last_frame, INT_MAX, 0);
        }
    }

    memset(s->all_fragments, 0, s->fragment_count * sizeof(Vp3Fragment));
    ff_thread_finish_setup(avctx);

    if (s->version < 2) {
        if ((ret = unpack_superblocks(s, &gb)) < 0) {
            av_log(s->avctx, 0, "error in unpack_superblocks\n");
            goto error;
        }
#if CONFIG_VP4_DECODER
    } else {
        if ((ret = vp4_unpack_macroblocks(s, &gb)) < 0) {
            av_log(s->avctx, 0, "error in vp4_unpack_macroblocks\n");
            goto error;
    }
#endif
    }
    if ((ret = unpack_modes(s, &gb)) < 0) {
        av_log(s->avctx, 0, "error in unpack_modes\n");
        goto error;
    }
    if ((ret = unpack_vectors(s, &gb))) {
        av_log(s->avctx, 0, "error in unpack_vectors\n");
        goto error;
    }
    if ((ret = unpack_block_qpis(s, &gb)) < 0) {
        av_log(s->avctx, 0, "error in unpack_block_qpis\n");
        goto error;
    }

    if (s->version < 2) {
        if ((ret = unpack_dct_coeffs(s, &gb)) < 0) {
            av_log(s->avctx, 0, "error in unpack_dct_coeffs\n");
            goto error;
        }
#if CONFIG_VP4_DECODER
    } else {
        if ((ret = vp4_unpack_dct_coeffs(s, &gb)) < 0) {
            av_log(s->avctx, 0, "error in vp4_unpack_dct_coeffs\n");
            goto error;
        }
#endif
    }

    for (i = 0; i < 3; i++) {
        int height = s->height >> (i && s->chroma_y_shift);
        if (s->flipped_image)
            s->data_offset[i] = 0;
        else
            s->data_offset[i] = (height - 1) * s->current_frame.f->linesize[i];
    }

    s->last_slice_end = 0;
    for (i = 0; i < s->c_superblock_height; i++)
        render_slice(s, i);

    if (s->version < 2)
        for (i = 0; i < 3; i++) {
            int row = (s->height >> (3 + (i && s->chroma_y_shift))) - 1;
            apply_loop_filter(s, i, row, row + 1);
        }
    vp3_draw_horiz_band(s, s->height);

    if ((ret = av_frame_ref(data, s->current_frame.f)) < 0)
        return ret;

    frame->crop_left   = s->offset_x;
    frame->crop_right  = avctx->coded_width - avctx->width - s->offset_x;
    frame->crop_top    = s->offset_y;
    frame->crop_bottom = avctx->coded_height - avctx->height - s->offset_y;

    *got_frame = 1;

    if (!0 || !(s->avctx->active_thread_type & 0x0002)) {
        ret = update_frames(avctx);
        if (ret < 0)
            return ret;
    }

    return buf_size;

error:
    ff_thread_report_progress(&s->current_frame, INT_MAX, 0);

    if (!0 || !(s->avctx->active_thread_type & 0x0002))
        av_frame_unref(s->current_frame.f);

    return ret;
}
