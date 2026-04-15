#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <zlib.h>
#include <assert.h>

typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

#define XML_INPUT_SIZE 4096
static u32 XML_MAX_CONTENT_SIZE = 0;

#define GF_SM_LOAD_XSR 7
#define GF_SM_LOAD_FOR_PLAYBACK 0x20
#define GF_SM_LOAD_CONTEXT_READY 0x10

#define GF_ODF_ESD_TAG 3
#define GF_ODF_IOD_TAG 1
#define GF_ODF_OD_TAG 2
#define GF_ODF_DCD_TAG 4
#define GF_ODF_SLC_TAG 5
#define GF_ODF_ISOM_IOD_TAG 6
#define GF_ODF_ISOM_OD_TAG 7
#define GF_ODF_SEGMENT_TAG 8
#define GF_ODF_MUXINFO_TAG 9
#define GF_ODF_BIFS_CFG_TAG 10
#define GF_ODF_UI_CFG_TAG 11
#define GF_ODF_TEXT_CFG_TAG 12
#define GF_ODF_TX3G_TAG 13
#define GF_ODF_ELEM_MASK_TAG 14
#define GF_ODF_LASER_CFG_TAG 15
#define GF_ODF_AUX_VIDEO_DATA 16
#define GF_ODF_LANG_TAG 17
#define GF_ODF_GPAC_LANG 18
#define GF_ODF_ESD_INC_TAG 19
#define GF_ODF_ESD_REF_TAG 20
#define GF_ODF_MEDIATIME_TAG 21
#define GF_ODF_CC_TAG 22
#define GF_ODF_CC_DATE_TAG 23
#define GF_ODF_CC_NAME_TAG 24
#define GF_ODF_CI_TAG 25
#define GF_ODF_TEXT_TAG 26
#define GF_ODF_EXT_PL_TAG 27
#define GF_ODF_IPI_PTR_TAG 28
#define GF_ODF_ISOM_IPI_PTR_TAG 29
#define GF_ODF_IPMP_TAG 30
#define GF_ODF_IPMP_PTR_TAG 31
#define GF_ODF_KW_TAG 32
#define GF_ODF_OCI_DATE_TAG 33
#define GF_ODF_OCI_NAME_TAG 34
#define GF_ODF_PL_IDX_TAG 35
#define GF_ODF_QOS_TAG 36
#define GF_ODF_RATING_TAG 37
#define GF_ODF_REG_TAG 38
#define GF_ODF_SHORT_TEXT_TAG 39
#define GF_ODF_SMPTE_TAG 40
#define GF_ODF_SCI_TAG 41
#define GF_ODF_IPMP_TL_TAG 42
#define GF_ODF_IPMP_TOOL_TAG 43

#define GF_ODF_ESD_UPDATE_TAG 1
#define GF_ODF_OD_UPDATE_TAG 2
#define GF_ODF_IPMP_UPDATE_TAG 3

#define GF_SG_ROUTE_INSERT 1
#define GF_SG_SCENE_REPLACE 2
#define GF_SG_GLOBAL_QUANTIZER 3
#define GF_SG_NODE_INSERT 4
#define GF_SG_INDEXED_INSERT 5
#define GF_SG_INDEXED_REPLACE 6
#define GF_SG_NODE_REPLACE 7
#define GF_SG_FIELD_REPLACE 8
#define GF_SG_MULTIPLE_REPLACE 9
#define GF_SG_PROTO_INSERT 10

#define GF_SG_VRML_SFCOMMANDBUFFER 20
#define GF_SG_VRML_SFNODE 18
#define GF_SG_VRML_MFNODE 19

#define TAG_ProtoNode 100
#define TAG_MPEG4_Script 50
#define TAG_X3D_Script 51

#define XMT_STATE_INIT 0
#define XMT_STATE_HEAD 1
#define XMT_STATE_BODY 2
#define XMT_STATE_COMMANDS 3
#define XMT_STATE_ELEMENTS 4
#define XMT_STATE_BODY_END 5
#define XMT_STATE_END 6

#define SAX_STATE_ELEMENT 0
#define SAX_STATE_TEXT_CONTENT 1
#define SAX_STATE_ATT_NAME 3
#define SAX_STATE_ATT_VALUE 4
#define SAX_STATE_ENTITY 8
#define SAX_STATE_SKIP_DOCTYPE 9
#define SAX_STATE_XML_PROC 11
#define SAX_STATE_CDATA 10
#define SAX_STATE_COMMENT 7
#define SAX_STATE_SYNTAX_ERROR 12
#define SAX_STATE_ALLOC_ERROR 13
#define SAX_STATE_DONE 14

#define GF_UTF8_FAIL -1

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

typedef enum
{
	GF_EOS = 1,
	GF_OK = 0,
	GF_BAD_PARAM = -1,
	GF_OUT_OF_MEM = -2,
	GF_IO_ERR = -3,
	GF_NOT_SUPPORTED = -4,
	GF_CORRUPTED_DATA = -5,
	GF_URL_ERROR = -12,
	GF_NON_COMPLIANT_BITSTREAM = -10,
} GF_Err;

#define GF_EXPORT
#define GF_SAFEALLOC(__ptr, __struct) {\
		(__ptr) = (__struct *) gf_malloc(sizeof(__struct));\
		if (__ptr) memset((void *) (__ptr), 0, sizeof(__struct));\
	}

#define gf_assert(cond) assert(cond)
#define gf_fatal_assert(cond) assert(cond)
#define GF_LOG(level, tool, args)
#define GF_ARRAY_LENGTH(__a) (sizeof((__a))/sizeof((__a)[0]))
#define stricmp strcasecmp

typedef struct { char *name; char *value; } GF_XMLAttribute;
typedef struct _tag_sax_attribute { char *name; char *value; } GF_XMLSaxAttribute;
typedef void (*gf_xml_sax_node_start)(void*,const char*,const char*,const GF_XMLAttribute*,u32);
typedef void (*gf_xml_sax_node_end)(void*,const char*,const char*);
typedef void (*gf_xml_sax_text_content)(void*,const char*,Bool);
typedef void (*gf_xml_sax_progress)(void*,u64,u64);

typedef struct _tag_list GF_List;

typedef struct {
	void *name;
	u32 fieldType;
	void *far_ptr;
} ContainerField;

typedef struct { void *tag; } SGPrivate;
typedef struct { void *node; SGPrivate *sgprivate; } GF_Node2;

typedef struct {
	GF_Node2 *node;
	ContainerField container_field;
	void *last;
} XMTNodeStack;

typedef struct { char *URLString; void *ESDescriptors; void *OCIDescriptors; void *IPMP_Descriptors; void *extensionDescriptors; void *IPMPToolList; } GF_InitialObjectDescriptor;
typedef struct { void *ESDescriptors; void *OCIDescriptors; void *IPMP_Descriptors; void *extensionDescriptors; void *IPMPToolList; } GF_ObjectDescriptor;
typedef struct { void *ESDescriptors; } GF_IsomInitialObjectDescriptor;
typedef struct { void *objectDescriptors; } GF_IsomObjectDescriptor;
typedef struct { void *command_fields; u32 tag; void *node; void *scripts_to_load; u32 fromNodeID; } GF_Command;
typedef struct { void *buffer; u32 bufferSize; void *commandList; } SFCommandBuffer;
typedef struct { void *buffer; u32 fieldType; void *field_ptr; void *node_list; void *new_node; } GF_CommandField;
typedef struct { void *node; void *sgprivate; } XMTNodeStack2;
typedef struct { u32 tag; void *userpriv; void *parent_graph; } GF_Proto;
typedef struct { void *commands; } GF_AUContext;
typedef struct { u32 tag; } GF_Descriptor;
typedef struct { u32 field; GF_Node2 *RootNode; } GF_SceneGraph;
typedef struct { void *root_od; } GF_SceneManagerCtx;
typedef struct { GF_SceneManagerCtx *ctx; u32 is_pixel_metrics; GF_SceneGraph *scene_graph; u32 flags; } GF_SceneManager;
typedef struct { void *children; } M_Group;
typedef struct { u32 timeScale; } GF_StreamContext;
typedef struct { char *name; u32 namelen; char *value; } XML_Entity;
typedef void *GF_Node;
typedef struct { u32 streamType; u32 objectTypeIndication; } GF_DecoderConfig;
typedef struct { u32 timestampResolution; } GF_SLConfig;
typedef struct { u32 ESID; GF_DecoderConfig *decoderConfig; GF_SLConfig *slConfig; } GF_ESD;
typedef struct { void *ESDescriptors; } GF_ESDUpdate;
typedef struct { void *objectDescriptors; } GF_ODUpdate;
typedef struct { u32 tag; void *objectDescriptors; } GF_ODCom;
typedef struct { void *buffer; u32 bufferSize; void *commandList; } SFCommandBuffer2;
typedef struct { u32 ESID; u16 OCRESID; u16 dependsOnESID; } ESD;
typedef struct { char *desc_name; u32 ESID; ESD *esd; char *OCR_Name; char *Depends_Name; } XMT_ESDLink;
typedef struct { char *url; u16 OD_ID; } SFURL;
typedef struct { SFURL *vals; u32 count; } MFURL;
typedef struct { u16 objectDescriptorID; } OD;
typedef struct { char *desc_name; u32 ID; MFURL *mf_urls; OD *od; } XMT_ODLink;

typedef struct {
	void *sax_parser;
	void *nodes;
	void *descriptors;
	GF_List *esd_links;
	GF_List *od_links;
	GF_Err last_error;
	GF_SceneManager *load;
	u32 doc_type;
	u32 state;
	GF_Command *command;
	SFCommandBuffer *command_buffer;
	GF_ODCom *od_command;
	GF_Proto *parsing_proto;
	void *proto_field;
	GF_AUContext *scene_au;
	void *script_to_load;
	u32 current_node_tag;
	XMTNodeStack *x3d_root;
	Bool in_com;
	void *def_nodes;
	void *peeked_nodes;
	void *inserted_routes;
	void *unresolved_routes;
} GF_XMTParser;

struct _tag_sax_parser
{
	/*0: UTF-8, 1: UTF-16 BE, 2: UTF-16 LE. String input is always converted back to utf8*/
	s32 unicode_type;
	char *buffer;
	/*alloc size, line size and current position*/
	u32 alloc_size, line_size, current_pos;
	/*current node depth*/
	u32 node_depth;

	/*gz input file*/
#ifdef NO_GZIP
	FILE *f_in;
#else
	gzFile gz_in;
#endif
	/*current line , file size and pos for user notif*/
	u32 line, file_size, file_pos;

	/*SAX callbacks*/
	gf_xml_sax_node_start sax_node_start;
	gf_xml_sax_node_end sax_node_end;
	gf_xml_sax_text_content sax_text_content;
	void *sax_cbck;
	gf_xml_sax_progress on_progress;

	u32 sax_state;
	u32 init_state;
	GF_List *entities;
	char att_sep;
	Bool in_entity, suspended;
	u32 in_quote;

	u32 elt_start_pos, elt_end_pos;

	/*last error found*/
	char err_msg[1000];

	u32 att_name_start, elt_name_start, elt_name_end, text_start, text_end;
	u32 text_check_escapes;

	GF_XMLAttribute *attrs;
	GF_XMLSaxAttribute *sax_attrs;
	u32 nb_attrs, nb_alloc_attrs;
	u32 ent_rec_level;
};

typedef struct _tag_sax_parser GF_SAXParser;

typedef struct { void *loader_priv; const char *fileName; GF_SceneManager *ctx; u32 type; u32 flags; void *scene_graph; } GF_SceneLoader;

#define MALLOC malloc
#define CALLOC calloc
#define REALLOC realloc
#define FREE free
#define STRDUP(a) return strdup(a);

static void *gf_malloc(size_t size);
static void *gf_realloc(void *ptr, size_t size);
static void gf_free(void *ptr);
static char *gf_strdup(const char *str);
static GF_List *gf_list_new(void);
static void gf_list_del(void *list);
static void *gf_list_enum(void *list, u32 *index);
static void *gf_list_get(void *list, u32 index);
static void gf_list_rem(void *list, u32 index);
static u32 gf_list_count(void *list);
static u32 gf_list_add(void *list, void *item);
static void *gf_list_last(void *list);
static void *gf_list_rem_last(void *list);
static void *gf_list_del_item(void *list, void *item);
static u32 gf_opts_get_int(const char *secName, const char *keyName);
static void gf_log_tool_level_on(u32 tool, u32 level);
static GF_Err gf_xml_sax_init(GF_SAXParser *parser, unsigned char *BOM);
static GF_Err gf_xml_sax_parse(GF_SAXParser *parser, const void *string);
static GF_Err gf_xml_sax_parse_intern(GF_SAXParser *parser, char *current);
static GF_Err xml_sax_read_file(GF_SAXParser *parser);
static GF_Err xml_sax_parse(GF_SAXParser *parser, Bool force_parse);
static GF_Err xml_sax_parse_comments(GF_SAXParser *parser);
static GF_Err xml_sax_parse_attribute(GF_SAXParser *parser);
static void xml_sax_parse_entity(GF_SAXParser *parser);
static void xml_sax_skip_doctype(GF_SAXParser *parser);
static void xml_sax_skip_xml_proc(GF_SAXParser *parser);
static void xml_sax_cdata(GF_SAXParser *parser);
static void xml_sax_swap(GF_SAXParser *parser);
static void xml_sax_flush_text(GF_SAXParser *parser);
static void xml_sax_store_text(GF_SAXParser *parser, u32 i);
static void xml_sax_node_start(GF_SAXParser *parser);
static void xml_sax_node_end(GF_SAXParser *parser, Bool had_children);
static GF_Err xml_sax_append_string(GF_SAXParser *parser, char *str);
static void format_sax_error(GF_SAXParser *parser, u32 linepos, const char* fmt, ...);
static char *gf_xml_sax_get_error(GF_SAXParser *parser);
static u32 gf_xml_sax_get_line(GF_SAXParser *parser);
static void xmt_node_start(void *sax_cbck, const char *node_name, const char *name_space, const GF_XMLAttribute *attributes, u32 nb_attributes);
static void xmt_node_end(void *sax_cbck, const char *name, const char *name_space);
static void xmt_text_content(void *sax_cbck, const char *content, Bool is_cdata);
static void xmt_progress(void *cbk, u64 done, u64 total);
static void xmt_resolve_routes(GF_XMTParser *parser);
static GF_Err xmt_restore_context(GF_SceneLoader *load);
static u32 xmt_get_node_tag(GF_XMTParser *parser, const char *name);
static u32 gf_odf_get_tag_by_name(char *name);
static void *gf_node_new(void *sg, u32 tag);
static void gf_node_register(void *node, void *ref);
static void gf_node_unregister(void *node, void *ref);
static void gf_node_init(void *node);
static void gf_sg_set_root_node(void *sg, void *node);
static GF_Err gf_sg_script_load(void *node);
static void *gf_sg_command_field_new(void *cmd);
static void gf_node_list_add_child(void **list, void *node);
static void *gf_sg_get_root_node(void *sg);
static char *gf_node_get_class_name(void *node);
static void *gf_sm_stream_new(void *ctx, u32 ESID, u32 streamType, u32 objectType);
static void gf_sg_proto_add_node_code(void *proto, void *node);
static GF_Err gf_odf_delete_descriptor(GF_Descriptor *desc);
static GF_Err gf_odf_del_iod(GF_InitialObjectDescriptor *iod);
static GF_Err gf_odf_del_od(GF_ObjectDescriptor *od);
static GF_Err gf_odf_del_esd(GF_ESD *esd);
static GF_Err gf_odf_del_dcd(GF_DecoderConfig *dcd);
static GF_Err gf_odf_del_slc(GF_SLConfig *slc);
static GF_Err gf_odf_del_isom_iod(GF_IsomInitialObjectDescriptor *iod);
static GF_Err gf_odf_del_isom_od(GF_IsomObjectDescriptor *od);
static GF_Err gf_odf_del_segment(void *seg);
static GF_Err gf_odf_del_muxinfo(void *mux);
static GF_Err gf_odf_del_bifs_cfg(void *cfg);
static GF_Err gf_odf_del_ui_cfg(void *cfg);
static GF_Err gf_odf_del_text_cfg(void *cfg);
static GF_Err gf_odf_del_tx3g(void *tx3g);
static GF_Err gf_odf_del_ElemMask(void *mask);
static GF_Err gf_odf_del_laser_cfg(void *cfg);
static GF_Err gf_odf_del_auxvid(void *aux);
static GF_Err gf_odf_del_lang(void *lang);
static GF_Err gf_odf_del_esd_inc(void *inc);
static GF_Err gf_odf_del_esd_ref(void *ref);
static GF_Err gf_odf_del_mediatime(void *mt);
static GF_Err gf_odf_del_cc(void *cc);
static GF_Err gf_odf_del_cc_date(void *date);
static GF_Err gf_odf_del_cc_name(void *name);
static GF_Err gf_odf_del_ci(void *ci);
static GF_Err gf_odf_del_exp_text(void *text);
static GF_Err gf_odf_del_pl_ext(void *ext);
static GF_Err gf_odf_del_ipi_ptr(void *ptr);
static GF_Err gf_odf_del_ipmp(void *ipmp);
static GF_Err gf_odf_del_ipmp_ptr(void *ptr);
static GF_Err gf_odf_del_kw(void *kw);
static GF_Err gf_odf_del_oci_date(void *date);
static GF_Err gf_odf_del_oci_name(void *name);
static GF_Err gf_odf_del_pl_idx(void *idx);
static GF_Err gf_odf_del_qos(void *qos);
static GF_Err gf_odf_del_rating(void *rating);
static GF_Err gf_odf_del_reg(void *reg);
static GF_Err gf_odf_del_short_text(void *text);
static GF_Err gf_odf_del_smpte_camera(void *cam);
static GF_Err gf_odf_del_sup_cid(void *cid);
static GF_Err gf_odf_del_ipmp_tool_list(void *list);
static GF_Err gf_odf_del_ipmp_tool(void *tool);
static GF_Err gf_odf_del_default(void *def);
static GF_Err gf_odf_delete_descriptor_list(GF_List *list);
static XML_Entity *gf_xml_locate_entity(GF_SAXParser *parser, char *name, Bool *needs_text);
static u32 gf_utf8_wcslen(const u16 *wide_str);
static u32 gf_utf8_wcstombs(char *outbuf, u32 out_len, const u16 **inbuf);
static FILE *gf_fopen(const char *filename, const char *mode);
static void gf_fclose(FILE *stream);
static u64 gf_fsize(FILE *stream);
static u32 gf_fread(void *ptr, u32 size, FILE *stream);
static gzFile gf_gzopen(const char *path, const char *mode);
static int gf_gzread(gzFile file, voidp buf, unsigned int len);
static int gf_gzclose(gzFile file);
static Bool gf_gzeof(gzFile file);
static s32 gf_feof(FILE *stream);
static s32 gf_ftell(FILE *stream);
static void gf_set_progress(const char *title, u64 done, u64 total);
static GF_Err gf_blob_get(const char *blob_url, u8 **out_data, u32 *out_size, u32 *blob_flags);
static GF_Err gf_blob_release(const char *blob_url);

static void *gf_malloc(size_t size) { return malloc(size); }
static void *gf_realloc(void *ptr, size_t size) { return realloc(ptr, size); }
static void gf_free(void *ptr);
static char *gf_strdup(const char *str) { return strdup(str); }
static FILE *gf_fopen(const char *filename, const char *mode) { return fopen(filename, mode); }
static void gf_fclose(FILE *stream) { fclose(stream); }
static u64 gf_fsize(FILE *stream);
static u32 gf_fread(void *ptr, u32 size, FILE *stream) { return fread(ptr, 1, size, stream); }
static gzFile gf_gzopen(const char *path, const char *mode) { return gzopen(path, mode); }
static int gf_gzread(gzFile file, voidp buf, unsigned int len) { return gzread(file, buf, len); }
static int gf_gzclose(gzFile file) { return gzclose(file); }
static Bool gf_gzeof(gzFile file) { return gzeof(file); }
static s32 gf_feof(FILE *stream) { return feof(stream); }
static s32 gf_ftell(FILE *stream) { return ftell(stream); }

static GF_List *gf_list_new(void);
static void gf_list_del(void *list);
static void *gf_list_enum(void *list, u32 *index);
static void *gf_list_get(void *list, u32 index);
static void gf_list_rem(void *list, u32 index);
static u32 gf_list_count(void *list);
static u32 gf_list_add(void *list, void *item);
static void *gf_list_last(void *list);
static void *gf_list_rem_last(void *list);
static void *gf_list_del_item(void *list, void *item);
static u32 gf_opts_get_int(const char *secName, const char *keyName);
static void gf_log_tool_level_on(u32 tool, u32 level);
static char *gf_xml_sax_get_error(GF_SAXParser *parser);
static u32 gf_xml_sax_get_line(GF_SAXParser *parser);
static void xmt_node_start(void *sax_cbck, const char *node_name, const char *name_space, const GF_XMLAttribute *attributes, u32 nb_attributes);
static void xmt_node_end(void *sax_cbck, const char *name, const char *name_space);
static void xmt_text_content(void *sax_cbck, const char *content, Bool is_cdata);
static void xmt_progress(void *cbk, u64 done, u64 total);
static void xmt_resolve_routes(GF_XMTParser *parser);
static GF_Err xmt_restore_context(GF_SceneLoader *load);
static u32 xmt_get_node_tag(GF_XMTParser *parser, const char *name);
static u32 gf_odf_get_tag_by_name(char *name);
static void *gf_node_new(void *sg, u32 tag);
static void gf_node_register(void *node, void *ref);
static void gf_node_unregister(void *node, void *ref);
static void gf_node_init(void *node);
static void gf_sg_set_root_node(void *sg, void *node);
static GF_Err gf_sg_script_load(void *node);
static void *gf_sg_command_field_new(void *cmd);
static void gf_node_list_add_child(void **list, void *node);
static void *gf_sg_get_root_node(void *sg);
static char *gf_node_get_class_name(void *node);
static void *gf_sm_stream_new(void *ctx, u32 ESID, u32 streamType, u32 objectType);
static void gf_sg_proto_add_node_code(void *proto, void *node);
static GF_Err gf_odf_delete_descriptor_list(GF_List *list);
static XML_Entity *gf_xml_locate_entity(GF_SAXParser *parser, char *name, Bool *needs_text);
static u32 gf_utf8_wcslen(const u16 *wide_str);
static u32 gf_utf8_wcstombs(char *outbuf, u32 out_len, const u16 **inbuf);
static void gf_set_progress(const char *title, u64 done, u64 total);
static GF_Err gf_blob_get(const char *blob_url, u8 **out_data, u32 *out_size, u32 *blob_flags);
static GF_Err gf_blob_release(const char *blob_url);
static GF_Err gf_xml_sax_init(GF_SAXParser *parser, unsigned char *BOM);
static GF_Err gf_xml_sax_parse(GF_SAXParser *parser, const void *string);
static GF_Err gf_xml_sax_parse_intern(GF_SAXParser *parser, char *current);
static GF_Err xml_sax_read_file(GF_SAXParser *parser);
static GF_Err xml_sax_parse(GF_SAXParser *parser, Bool force_parse);
static GF_Err xml_sax_parse_comments(GF_SAXParser *parser);
static GF_Err xml_sax_parse_attribute(GF_SAXParser *parser);
static void xml_sax_parse_entity(GF_SAXParser *parser);
static void xml_sax_skip_doctype(GF_SAXParser *parser);
static void xml_sax_skip_xml_proc(GF_SAXParser *parser);
static void xml_sax_cdata(GF_SAXParser *parser);
static void xml_sax_swap(GF_SAXParser *parser);
static void xml_sax_flush_text(GF_SAXParser *parser);
static void xml_sax_store_text(GF_SAXParser *parser, u32 i);
static void xml_sax_node_start(GF_SAXParser *parser);
static void xml_sax_node_end(GF_SAXParser *parser, Bool had_children);
static GF_Err xml_sax_append_string(GF_SAXParser *parser, char *str);
static void format_sax_error(GF_SAXParser *parser, u32 linepos, const char* fmt, ...);

static GF_Err xmt_report(GF_XMTParser *parser, GF_Err e, const char *format, ...) {
	va_list args; va_start(args, format); va_end(args);
	if (e) parser->last_error = e;
	return e;
}

static Bool xmt_esid_available(GF_XMTParser *parser, u16 ESID);
static Bool xmt_odid_available(GF_XMTParser *parser, u16 ODID);

static Bool xmt_esid_available(GF_XMTParser *parser, u16 ESID) {
	u32 i; XMT_ESDLink *esdl;
	i=0;
	while ((esdl = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &i))) {
		if (esdl->ESID == ESID) return 0;
	}
	return 1;
}

static Bool xmt_odid_available(GF_XMTParser *parser, u16 ODID) {
	return 1;
}

GF_EXPORT
GF_SAXParser *gf_xml_sax_new(gf_xml_sax_node_start on_node_start,
                              gf_xml_sax_node_end on_node_end,
                              gf_xml_sax_text_content on_text_content,
                              void *cbck)
{
	GF_SAXParser *parser;
	GF_SAFEALLOC(parser, GF_SAXParser);
	if (!parser) return NULL;
	parser->entities = gf_list_new();
	parser->unicode_type = -1;
	parser->sax_node_start = on_node_start;
	parser->sax_node_end = on_node_end;
	parser->sax_text_content = on_text_content;
	parser->sax_cbck = cbck;
	return parser;
}

static GF_XMTParser *xmt_new_parser(GF_SceneLoader *load)
{
	GF_XMTParser *parser;
	if ((load->type==GF_SM_LOAD_XSR) && !load->ctx) return NULL;
	GF_SAFEALLOC(parser, GF_XMTParser);
	if (!parser) return NULL;

	parser->nodes = gf_list_new();
	parser->descriptors = gf_list_new();
	parser->od_links = gf_list_new();
	parser->esd_links = gf_list_new();
	parser->def_nodes = gf_list_new();
	parser->peeked_nodes = gf_list_new();
	parser->inserted_routes = gf_list_new();
	parser->unresolved_routes = gf_list_new();

	parser->sax_parser = gf_xml_sax_new(xmt_node_start, xmt_node_end, xmt_text_content, parser);
	parser->load = load;
	load->loader_priv = parser;
	if (load->ctx) load->ctx->is_pixel_metrics = 1;

	return parser;
}

static GF_Err load_xmt_initialize(GF_SceneLoader *load, const char *str_data)
{
	GF_Err e;
	GF_XMTParser *parser;

	if (str_data) {
		char BOM[5];
		if (strlen(str_data)<4) return GF_BAD_PARAM;
		BOM[0] = str_data[0];
		BOM[1] = str_data[1];
		BOM[2] = str_data[2];
		BOM[3] = str_data[3];
		BOM[4] = 0;
		parser = xmt_new_parser(load);
		e = gf_xml_sax_init(parser->sax_parser, (unsigned char*)BOM);
		if (e) {
			xmt_report(parser, e, "Error initializing SAX parser");
			return e;
		}
		str_data += 4;
	} else if (load->fileName) {
		parser = xmt_new_parser(load);
	} else {
		return GF_BAD_PARAM;
	}

	/*chunk parsing*/
	if (load->flags & GF_SM_LOAD_CONTEXT_READY) {
		GF_LOG(GF_LOG_INFO, GF_LOG_PARSER, ("XMT: MPEG-4 (XMT) Chunk Parsing\n"));

		e = xmt_restore_context(load);
		if (e) return e;

	} else {
		GF_LOG(GF_LOG_INFO, GF_LOG_PARSER, ("XMT: MPEG-4 (XMT) Scene Parsing\n"));
	}

	if (str_data) {
		return gf_xml_sax_parse(parser->sax_parser, str_data);
	}
	return GF_OK;
}

GF_Err gf_odf_delete_descriptor(GF_Descriptor *desc)
{
	switch (desc->tag) {
	case GF_ODF_IOD_TAG :
		return gf_odf_del_iod((GF_InitialObjectDescriptor *)desc);
	case GF_ODF_OD_TAG:
		return gf_odf_del_od((GF_ObjectDescriptor *)desc);
	case GF_ODF_ESD_TAG :
		return gf_odf_del_esd((GF_ESD *)desc);
	case GF_ODF_DCD_TAG :
		return gf_odf_del_dcd((GF_DecoderConfig *)desc);
	case GF_ODF_SLC_TAG:
		return gf_odf_del_slc((GF_SLConfig *)desc);

	case GF_ODF_ISOM_IOD_TAG:
		return gf_odf_del_isom_iod((GF_IsomInitialObjectDescriptor *)desc);
	case GF_ODF_ISOM_OD_TAG:
		return gf_odf_del_isom_od((GF_IsomObjectDescriptor *)desc);

	case GF_ODF_SEGMENT_TAG:
		return gf_odf_del_segment((void *) desc);

	case GF_ODF_MUXINFO_TAG:
		return gf_odf_del_muxinfo((void *)desc);
	case GF_ODF_BIFS_CFG_TAG:
		return gf_odf_del_bifs_cfg((void *)desc);
	case GF_ODF_UI_CFG_TAG:
		return gf_odf_del_ui_cfg((void *)desc);
	case GF_ODF_TEXT_CFG_TAG:
		return gf_odf_del_text_cfg((void *)desc);
	case GF_ODF_TX3G_TAG:
		return gf_odf_del_tx3g((void *)desc);
	case GF_ODF_ELEM_MASK_TAG:
		return gf_odf_del_ElemMask((void *)desc);
	case GF_ODF_LASER_CFG_TAG:
		return gf_odf_del_laser_cfg((void *)desc);

	case GF_ODF_AUX_VIDEO_DATA:
		return gf_odf_del_auxvid((void *)desc);

	case GF_ODF_LANG_TAG:
	case GF_ODF_GPAC_LANG:
		return gf_odf_del_lang((void *)desc);

	case GF_ODF_ESD_INC_TAG:
		return gf_odf_del_esd_inc((void *)desc);
	case GF_ODF_ESD_REF_TAG:
		return gf_odf_del_esd_ref((void *)desc);

#ifndef GPAC_MINIMAL_ODF
	case GF_ODF_MEDIATIME_TAG:
		return gf_odf_del_mediatime((void *) desc);
	case GF_ODF_CC_TAG:
		return gf_odf_del_cc((void *)desc);
	case GF_ODF_CC_DATE_TAG:
		return gf_odf_del_cc_date((void *)desc);
	case GF_ODF_CC_NAME_TAG:
		return gf_odf_del_cc_name((void *)desc);
	case GF_ODF_CI_TAG:
		return gf_odf_del_ci((void *)desc);
	case GF_ODF_TEXT_TAG:
		return gf_odf_del_exp_text((void *)desc);
	case GF_ODF_EXT_PL_TAG:
		return gf_odf_del_pl_ext((void *)desc);
	case GF_ODF_IPI_PTR_TAG:
	case GF_ODF_ISOM_IPI_PTR_TAG:
		return gf_odf_del_ipi_ptr((void *)desc);
	case GF_ODF_IPMP_TAG:
		return gf_odf_del_ipmp((void *)desc);
	case GF_ODF_IPMP_PTR_TAG:
		return gf_odf_del_ipmp_ptr((void *)desc);
	case GF_ODF_KW_TAG:
		return gf_odf_del_kw((void *)desc);
	case GF_ODF_OCI_DATE_TAG:
		return gf_odf_del_oci_date((void *)desc);
	case GF_ODF_OCI_NAME_TAG:
		return gf_odf_del_oci_name((void *)desc);
	case GF_ODF_PL_IDX_TAG:
		return gf_odf_del_pl_idx((void *)desc);
	case GF_ODF_QOS_TAG:
		return gf_odf_del_qos((void *)desc);
	case GF_ODF_RATING_TAG:
		return gf_odf_del_rating((void *)desc);
	case GF_ODF_REG_TAG:
		return gf_odf_del_reg((void *)desc);
	case GF_ODF_SHORT_TEXT_TAG:
		return gf_odf_del_short_text((void *)desc);
	case GF_ODF_SMPTE_TAG:
		return gf_odf_del_smpte_camera((void *)desc);
	case GF_ODF_SCI_TAG:
		return gf_odf_del_sup_cid((void *)desc);

	case GF_ODF_IPMP_TL_TAG:
		return gf_odf_del_ipmp_tool_list((void *)desc);
	case GF_ODF_IPMP_TOOL_TAG:
		return gf_odf_del_ipmp_tool((void *)desc);

#endif /*GPAC_MINIMAL_ODF*/

	default:
		return gf_odf_del_default((void *)desc);
	}
	return GF_OK;
}

GF_EXPORT
void gf_odf_desc_del(GF_Descriptor *desc)
{
	if (desc) gf_odf_delete_descriptor(desc);
}

static void xmt_remove_link_for_descriptor(GF_XMTParser* parser, GF_Descriptor* desc) {

	u32 i=0;
	XMT_ODLink *l, *to_del=NULL;
	while ((l = (XMT_ODLink*)gf_list_enum(parser->od_links, &i)) ) {
		if (l->od && l->od == (GF_ObjectDescriptor*)desc) {
			l->od = NULL;
			to_del = l;
			break;
		}
	}
	if (to_del) {

		i=0;
		GF_Descriptor* subdesc;
		while ((subdesc = gf_list_enum(((GF_ObjectDescriptor*)desc)->ESDescriptors, &i))) {
			if (subdesc) xmt_remove_link_for_descriptor(parser, subdesc);
		}

		gf_list_del_item(parser->od_links, to_del);
		if (to_del->desc_name) gf_free(to_del->desc_name);
		gf_list_del(to_del->mf_urls);
		gf_free(to_del);
	}

	XMT_ESDLink *esdl, *esdl_del=NULL;
	i=0;
	while ((esdl = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &i))) {
		if (esdl->esd && esdl->esd == (GF_ESD*)desc) {
			esdl->esd = NULL;
			esdl_del = esdl;
			break;
		}
	}

	if (esdl_del) {
		gf_list_del_item(parser->esd_links, esdl_del);
		if (esdl_del->desc_name) gf_free(esdl_del->desc_name);
		gf_free(esdl_del);
	}

}

static void xmt_node_end(void *sax_cbck, const char *name, const char *name_space)
{
	u32 tag;
	GF_XMTParser *parser = (GF_XMTParser *)sax_cbck;
	XMTNodeStack *top;
	GF_Descriptor *desc;
	GF_Node *node = NULL;
	if (!parser->doc_type || !parser->state) return;

	top = (XMTNodeStack *)gf_list_last(parser->nodes);

	if (!top) {
		/*check descr*/
		desc = (GF_Descriptor*)gf_list_last(parser->descriptors);
		if (desc && (desc->tag == gf_odf_get_tag_by_name((char *)name)) ) {

			/*assign timescales once the ESD has been parsed*/
			if (desc->tag == GF_ODF_ESD_TAG) {
				GF_ESD *esd = (GF_ESD*)desc;
				GF_StreamContext *sc = gf_sm_stream_new(parser->load->ctx, esd->ESID, esd->decoderConfig ? esd->decoderConfig->streamType : 0, esd->decoderConfig ? esd->decoderConfig->objectTypeIndication : 0);
				if (sc && esd->slConfig && esd->slConfig->timestampResolution)
					sc->timeScale = esd->slConfig->timestampResolution;
			}

			gf_list_rem_last(parser->descriptors);
			if (gf_list_count(parser->descriptors)) return;

			if ((parser->doc_type==1) && (parser->state==XMT_STATE_HEAD) && parser->load->ctx && !parser->load->ctx->root_od) {
				parser->load->ctx->root_od = (GF_ObjectDescriptor *)desc;
			}
			else if (!parser->od_command) {
				xmt_report(parser, GF_OK, "Warning: descriptor %s defined outside scene scope - skipping", name);
				xmt_remove_link_for_descriptor(parser, desc);
				gf_odf_desc_del(desc);
			} else {
				switch (parser->od_command->tag) {
				case GF_ODF_ESD_UPDATE_TAG:
					gf_list_add( ((GF_ESDUpdate *)parser->od_command)->ESDescriptors, desc);
					break;
				/*same struct for OD update and IPMP update*/
				case GF_ODF_OD_UPDATE_TAG:
				case GF_ODF_IPMP_UPDATE_TAG:
					gf_list_add( ((GF_ODUpdate *)parser->od_command)->objectDescriptors, desc);
					break;
				}
			}

			return;
		}
		if (parser->state == XMT_STATE_HEAD) {
			if ((parser->doc_type == 1) && !strcmp(name, "Header")) parser->state = XMT_STATE_BODY;
			/*X3D header*/
			else if ((parser->doc_type == 2) && !strcmp(name, "head")) {
				parser->state = XMT_STATE_BODY;
				/*create a group at root level*/
				tag = xmt_get_node_tag(parser, "Group");
				node = gf_node_new(parser->load->scene_graph, tag);
				gf_node_register(node, NULL);
				gf_sg_set_root_node(parser->load->scene_graph, node);
				gf_node_init(node);

				/*create a default top for X3D*/
				GF_SAFEALLOC(parser->x3d_root, XMTNodeStack);
				if (!parser->x3d_root) {
					GF_LOG(GF_LOG_ERROR, GF_LOG_PARSER, ("Failed to allocate X3D root\n"));
					return;
				}
				parser->x3d_root->node = node;
			}
			/*XMT-O header*/
			else if ((parser->doc_type == 3) && !strcmp(name, "head")) parser->state = XMT_STATE_BODY;
		}
		else if (parser->state == XMT_STATE_ELEMENTS) {
			gf_assert((parser->doc_type != 1) || parser->command);
			if (!strcmp(name, "Replace") || !strcmp(name, "Insert") || !strcmp(name, "Delete")) {
				parser->command = NULL;
				parser->state = XMT_STATE_COMMANDS;
			}
			else if (!strcmp(name, "repField")) {
				parser->state = XMT_STATE_COMMANDS;
			}
			/*end proto*/
			else if (!strcmp(name, "ProtoDeclare") || !strcmp(name, "ExternProtoDeclare"))  {
				GF_Proto *cur = parser->parsing_proto;
				xmt_resolve_routes(parser);
				parser->parsing_proto = (GF_Proto*)cur->userpriv;
				parser->load->scene_graph = cur->parent_graph;
				cur->userpriv = NULL;
			}
			else if (parser->proto_field && !strcmp(name, "field")) parser->proto_field = NULL;
			/*end X3D body*/
			else if ((parser->doc_type == 2) && !strcmp(name, "Scene")) parser->state = XMT_STATE_BODY_END;
		}
		else if (parser->state == XMT_STATE_COMMANDS) {
			/*end XMT-A body*/
			if ((parser->doc_type == 1) && !strcmp(name, "Body")) parser->state = XMT_STATE_BODY_END;
			/*end X3D body*/
			else if ((parser->doc_type == 2) && !strcmp(name, "Scene")) parser->state = XMT_STATE_BODY_END;
			/*end XMT-O body*/
			else if ((parser->doc_type == 3) && !strcmp(name, "body")) parser->state = XMT_STATE_BODY_END;

			/*end scene command*/
			else if (!strcmp(name, "Replace") || !strcmp(name, "Insert") || !strcmp(name, "Delete") )  {
				/*restore parent command if in CommandBuffer*/
				if (parser->command && parser->command_buffer && parser->command_buffer->buffer) {
					//empty <Insert>
					if ((parser->command->tag==GF_SG_ROUTE_INSERT) && !parser->command->fromNodeID) {
						gf_list_del_item(parser->command_buffer->commandList, parser->command);
					}

					parser->command = (GF_Command*) parser->command_buffer->buffer;
					parser->command_buffer->buffer = NULL;
					parser->command_buffer = NULL;
				} else {
					//empty <Insert>
					if (parser->command && (parser->command->tag==GF_SG_ROUTE_INSERT) && !parser->command->fromNodeID) {
						gf_list_del_item(parser->scene_au->commands, parser->command);
					}
					parser->command = NULL;
				}
			}
			/*end OD command*/
			else if (!strcmp(name, "ObjectDescriptorUpdate") || !strcmp(name, "ObjectDescriptorRemove")
			         || !strcmp(name, "ES_DescriptorUpdate") || !strcmp(name, "ES_DescriptorRemove")
			         || !strcmp(name, "IPMP_DescriptorUpdate") || !strcmp(name, "IPMP_DescriptorRemove") ) {
				parser->od_command = NULL;
			}

			else if (!strcmp(name, "par"))
				parser->in_com = 1;


		}
		else if (parser->state == XMT_STATE_BODY_END) {
			/*end XMT-A*/
			if ((parser->doc_type == 1) && !strcmp(name, "XMT-A")) parser->state = XMT_STATE_END;
			/*end X3D*/
			else if ((parser->doc_type == 2) && !strcmp(name, "X3D")) {
				while (1) {
					GF_Node *n = (GF_Node *)gf_list_last(parser->script_to_load);
					if (!n) break;
					gf_list_rem_last(parser->script_to_load);
					gf_sg_script_load(n);
				}
				gf_list_del(parser->script_to_load);
				parser->script_to_load = NULL;
				parser->state = XMT_STATE_END;
			}
			/*end XMT-O*/
			else if ((parser->doc_type == 3) && !strcmp(name, "XMT-O")) parser->state = XMT_STATE_END;
		}
		return;
	}
	/*only remove created nodes ... */
	tag = xmt_get_node_tag(parser, name);
	if (!tag) {
		if (top->container_field.name) {
			if (!strcmp(name, top->container_field.name)) {
				if (top->container_field.fieldType==GF_SG_VRML_SFCOMMANDBUFFER) {
					parser->state = XMT_STATE_ELEMENTS;
					parser->command = (GF_Command *) (void *) parser->command_buffer->buffer;
					parser->command_buffer->buffer = NULL;
					parser->command_buffer = NULL;
				}
				top->container_field.far_ptr = NULL;
				top->container_field.name = NULL;
				top->last = NULL;
			}
			/*end of command inside an command (conditional.buffer replace)*/
			else if (!strcmp(name, "Replace") || !strcmp(name, "Insert") || !strcmp(name, "Delete") )  {
				if (parser->command_buffer) {
					if (parser->command_buffer->bufferSize) {
						parser->command_buffer->bufferSize--;
					} else {
						SFCommandBuffer *prev = (SFCommandBuffer *) parser->command_buffer->buffer;
						parser->command_buffer->buffer = NULL;
						parser->command_buffer = prev;
					}
					/*stay in command parsing mode (state 3) until we find </buffer>*/
					parser->state = XMT_STATE_COMMANDS;
				}
			}
			/*end of protofield node(s) content*/
			else if (!strcmp(name, "node") || !strcmp(name, "nodes")) {
				top->container_field.far_ptr = NULL;
				top->container_field.name = NULL;
				top->last = NULL;
			}
		}
		/*SF/MFNode proto field, just pop node stack*/
		else if (!top->node && !strcmp(name, "field")) {
			gf_list_rem_last(parser->nodes);
			gf_free(top);
		} else if (top->node && top->node->sgprivate->tag == TAG_ProtoNode) {
			if (!strcmp(name, "node") || !strcmp(name, "nodes")) {
				top->container_field.far_ptr = NULL;
				top->container_field.name = NULL;
				top->last = NULL;
			} else if (!strcmp(name, "ProtoInstance")) {
				gf_list_rem_last(parser->nodes);
				node = top->node;
				gf_free(top);
				goto attach_node;
			}
		}
	} else if (top->node->sgprivate->tag==tag) {
		node = top->node;
		gf_list_rem_last(parser->nodes);
		gf_free(top);

attach_node:
		top = (XMTNodeStack*)gf_list_last(parser->nodes);
		/*add node to command*/
		if (!top || (top->container_field.fieldType==GF_SG_VRML_SFCOMMANDBUFFER)) {
			if (parser->doc_type == 1) {
				GF_CommandField *inf;
				Bool single_node = 0;
				if (!parser->command) {
					gf_assert(0);
					return;
				}
				switch (parser->command->tag) {
				case GF_SG_SCENE_REPLACE:
					if (parser->parsing_proto) {
						gf_sg_proto_add_node_code(parser->parsing_proto, node);
						gf_node_register(node, NULL);
					} else if (!parser->command->node) {
						parser->command->node = node;
						gf_node_register(node, NULL);
					} else if (parser->command->node != node) {
						xmt_report(parser, GF_OK, "Warning: top-node already assigned - discarding node %s", name);
						gf_node_register(node, NULL);
						gf_node_unregister(node, NULL);
					}
					break;
				case GF_SG_GLOBAL_QUANTIZER:
				case GF_SG_NODE_INSERT:
				case GF_SG_INDEXED_INSERT:
				case GF_SG_INDEXED_REPLACE:
					single_node = 1;
				case GF_SG_NODE_REPLACE:
				case GF_SG_FIELD_REPLACE:
				case GF_SG_MULTIPLE_REPLACE:
					inf = (GF_CommandField*)gf_list_last(parser->command->command_fields);
					if (!inf) {
						inf = gf_sg_command_field_new(parser->command);
						inf->fieldType = GF_SG_VRML_SFNODE;
					}
					if ((inf->fieldType==GF_SG_VRML_MFNODE) && !inf->node_list) {
						inf->field_ptr = &inf->node_list;
						if (inf->new_node) {
							gf_node_list_add_child(& inf->node_list, inf->new_node);
							inf->new_node = NULL;
						}
					}

					if (inf->new_node) {
						if (single_node) {
							gf_node_unregister(inf->new_node, NULL);
						} else {
							inf->field_ptr = &inf->node_list;
							gf_node_list_add_child(& inf->node_list, inf->new_node);
							inf->fieldType = GF_SG_VRML_MFNODE;
						}
						inf->new_node = NULL;
					}
					gf_node_register(node, NULL);
					if (inf->node_list) {
						gf_node_list_add_child(& inf->node_list, node);
					} else {
						inf->new_node = node;
						inf->field_ptr = &inf->new_node;
					}
					break;
				case GF_SG_PROTO_INSERT:
					if (parser->parsing_proto) {
						gf_sg_proto_add_node_code(parser->parsing_proto, node);
						gf_node_register(node, NULL);
						break;
					}
				default:
					xmt_report(parser, GF_OK, "Warning: node %s defined outside scene scope - skipping", name);
					gf_node_register(node, NULL);
					gf_node_unregister(node, NULL);
					break;

				}
			}
			/*X3D*/
			else if (parser->doc_type == 2) {
				if (parser->parsing_proto) {
					gf_sg_proto_add_node_code(parser->parsing_proto, node);
					gf_node_register(node, NULL);
				} else {
					M_Group *gr = (M_Group *)gf_sg_get_root_node(parser->load->scene_graph);
					if (!gr) {
						xmt_report(parser, GF_OK, "Warning: node %s defined outside scene scope - skipping", name);
						gf_node_register(node, NULL);
						gf_node_unregister(node, NULL);
					} else {
						//node has already been added to its parent with X3d parsing, because of the default container resolving
//						gf_node_list_add_child(& gr->children, node);
//						gf_node_register(node, NULL);
					}
				}
			}
			/*special case: replace scene has already been applied (progressive loading)*/
			else if ((parser->load->flags & GF_SM_LOAD_FOR_PLAYBACK) && (parser->load->scene_graph->RootNode!=node) ) {
				gf_node_register(node, NULL);
			} else {
				xmt_report(parser, GF_OK, "Warning: node %s defined outside scene scope - skipping", name);
				gf_node_register(node, NULL);
				gf_node_unregister(node, NULL);
			}
		}
		if (parser->load->flags & GF_SM_LOAD_FOR_PLAYBACK) {
			/*load scripts*/
			if (!parser->parsing_proto) {
				if ((tag==TAG_MPEG4_Script)
#ifndef GPAC_DISABLE_X3D
				        || (tag==TAG_X3D_Script)
#endif
				   ) {
					/*it may happen that the script uses itself as a field (not sure this is compliant since this
					implies a cyclic structure, but happens in some X3D conformance seq)*/
					if (!top || (top->node != node)) {
						if (parser->command) {
							if (!parser->command->scripts_to_load) parser->command->scripts_to_load = gf_list_new();
							gf_list_add(parser->command->scripts_to_load, node);
						}
						/*do not load script until all routes are established!!*/
						else if (parser->doc_type==2) {
							gf_list_add(parser->script_to_load, node);
						} else {
							gf_sg_script_load(node);
						}
					}
				}
			}
		}
	} else if (parser->current_node_tag==tag) {
		gf_list_rem_last(parser->nodes);
		gf_free(top);
	} else {
		xmt_report(parser, GF_NON_COMPLIANT_BITSTREAM, "Warning: closing element %s doesn't match created node %s", name, gf_node_get_class_name(top->node) );
	}
}

static void xml_sax_node_end(GF_SAXParser *parser, Bool had_children)
{
	char *name, c;

	gf_assert(parser->elt_name_start);
	gf_assert(parser->elt_name_end);
	if (!parser->node_depth) {
		format_sax_error(parser, 0, "Markup error");
		return;
	}
	c = parser->buffer[parser->elt_name_end - 1];
	parser->buffer[parser->elt_name_end - 1] = 0;
	name = parser->buffer + parser->elt_name_start - 1;

	if (parser->sax_node_end) {
		char *sep = strchr(name, ':');
		if (sep) {
			sep[0] = 0;
			parser->sax_node_end(parser->sax_cbck, sep+1, name);
			sep[0] = ':';
		} else {
			parser->sax_node_end(parser->sax_cbck, name, NULL);
		}
	}
	parser->buffer[parser->elt_name_end - 1] = c;
	parser->node_depth--;
	if (!parser->init_state && !parser->node_depth && parser->sax_state<SAX_STATE_SYNTAX_ERROR) parser->sax_state = SAX_STATE_DONE;
	xml_sax_swap(parser);
	parser->text_start = parser->text_end = 0;
}

static GF_Err xml_sax_parse(GF_SAXParser *parser, Bool force_parse)
{
	u32 i = 0;
	Bool is_text;
	u32 is_end;
	u8 c;
	char *elt, sep;
	u32 cdata_sep;

	while (parser->current_pos<parser->line_size) {
		if (!force_parse && parser->suspended) goto exit;

restart:
		is_text = GF_FALSE;
		switch (parser->sax_state) {
		/*load an XML element*/
		case SAX_STATE_TEXT_CONTENT:
			is_text = GF_TRUE;
		case SAX_STATE_ELEMENT:
			elt = NULL;
			i=0;
			while ((c = parser->buffer[parser->current_pos+i]) !='<') {
				if ((parser->init_state==2) && (c ==']')) {
					parser->sax_state = SAX_STATE_ATT_NAME;
					parser->current_pos+=i+1;
					goto restart;
				}
				i++;
				if (c=='\n') parser->line++;
				if (is_text) {
					if (c=='&') parser->text_check_escapes |= 1;
					else if (c==';') parser->text_check_escapes |= 2;
				}

				if (parser->current_pos+i==parser->line_size) {
					if ((parser->line_size >= XML_MAX_CONTENT_SIZE) && !parser->init_state) {
						GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("[XML] Content size larger than max allowed %u, try increasing limit using `-xml-max-csize`\n", XML_MAX_CONTENT_SIZE));
						parser->sax_state = SAX_STATE_SYNTAX_ERROR;
					}

					goto exit;
				}
			}
			if (is_text && i) {
				u32 has_esc = parser->text_check_escapes;
				xml_sax_store_text(parser, i);
				parser->text_check_escapes = has_esc;
				parser->sax_state = SAX_STATE_ELEMENT;
			} else if (i) {
				parser->current_pos += i;
				gf_assert(parser->current_pos < parser->line_size);
			}
			is_end = 0;
			i = 0;
			cdata_sep = 0;
			while (1) {
				c = parser->buffer[parser->current_pos+1+i];
				if (!strncmp(parser->buffer+parser->current_pos+1+i, "!--", 3)) {
					parser->sax_state = SAX_STATE_COMMENT;
					i += 3;
					break;
				}
				if (!c) {
					goto exit;
				}
				if ((c=='\t') || (c=='\r') || (c==' ') ) {
					if (i) break;
					else parser->current_pos++;
				}
				else if (c=='\n') {
					parser->line++;
					if (i) break;
					else parser->current_pos++;
				}
				else if (c=='>') break;
				else if (c=='=') break;
				else if (c=='[') {
					i++;
					if (!cdata_sep) cdata_sep = 1;
					else {
						break;
					}
				}
				else if (c=='/') {
					is_end = !i ? 1 : 2;
					i++;
				} else if (c=='<') {
					if (parser->sax_state != SAX_STATE_COMMENT) {
						parser->sax_state = SAX_STATE_SYNTAX_ERROR;
						return GF_CORRUPTED_DATA;
					}
				} else {
					i++;
				}
				/*				if ((c=='[') && (parser->buffer[parser->elt_name_start-1 + i-2]=='A') ) break; */
				if (parser->current_pos+1+i==parser->line_size) {
					goto exit;
				}
			}
			if (i) {
				parser->elt_name_start = parser->current_pos+1 + 1;
				if (is_end==1) parser->elt_name_start ++;
				if (is_end==2) parser->elt_name_end = parser->current_pos+1+i;
				else parser->elt_name_end = parser->current_pos+1+i + 1;
			}
			if (is_end) {
				xml_sax_flush_text(parser);
				parser->elt_end_pos = parser->file_pos + parser->current_pos + i;
				if (is_end==2) {
					parser->sax_state = SAX_STATE_ELEMENT;
					xml_sax_node_start(parser);
					xml_sax_node_end(parser, GF_FALSE);
				} else {
					parser->elt_end_pos += parser->elt_name_end - parser->elt_name_start;
					xml_sax_node_end(parser, GF_TRUE);
				}
				if (parser->sax_state == SAX_STATE_SYNTAX_ERROR) break;
				parser->current_pos+=2+i;
				parser->sax_state = SAX_STATE_TEXT_CONTENT;
				break;
			}
			if (!parser->elt_name_end) {
				return GF_CORRUPTED_DATA;
			}
			sep = parser->buffer[parser->elt_name_end-1];
			parser->buffer[parser->elt_name_end-1] = 0;
			elt = parser->buffer + parser->elt_name_start-1;

			parser->sax_state = SAX_STATE_ATT_NAME;
			gf_assert(parser->elt_start_pos <= parser->file_pos + parser->current_pos);
			parser->elt_start_pos = parser->file_pos + parser->current_pos;

			if (!strncmp(elt, "!--", 3)) {
				xml_sax_flush_text(parser);
				parser->sax_state = SAX_STATE_COMMENT;
				if (i>3) parser->current_pos -= (i-3);
			}
			else if (!strcmp(elt, "?xml")) parser->init_state = 1;
			else if (!strcmp(elt, "!DOCTYPE")) parser->init_state = 2;
			else if (!strcmp(elt, "!ENTITY")) parser->sax_state = SAX_STATE_ENTITY;
			else if (!strcmp(elt, "!ATTLIST") || !strcmp(elt, "!ELEMENT")) parser->sax_state = SAX_STATE_SKIP_DOCTYPE;
			else if (!strcmp(elt, "![CDATA["))
				parser->sax_state = SAX_STATE_CDATA;
			else if (elt[0]=='?') {
				i--;
				parser->sax_state = SAX_STATE_XML_PROC;
			}
			/*node found*/
			else {
				xml_sax_flush_text(parser);
				if (parser->init_state) {
					parser->init_state = 0;
					/*that's a bit ugly: since we solve entities when appending text, we need to
					reparse the current buffer*/
					if (gf_list_count(parser->entities)) {
						char *orig_buf;
						GF_Err e;
						parser->buffer[parser->elt_name_end-1] = sep;
						orig_buf = gf_strdup(parser->buffer + parser->current_pos);
						parser->current_pos = 0;
						parser->line_size = 0;
						parser->elt_start_pos = 0;
						parser->sax_state = SAX_STATE_TEXT_CONTENT;
						parser->ent_rec_level++;
						if (parser->ent_rec_level>100) {
							GF_LOG(GF_LOG_WARNING, GF_LOG_CORE, ("[XML] Too many recursions in entity solving, max 100 allowed\n"));
							e = GF_NOT_SUPPORTED;
						} else {
							e = gf_xml_sax_parse_intern(parser, orig_buf);
							parser->ent_rec_level--;
						}
						gf_free(orig_buf);
						return e;
					}
				}
			}
			parser->current_pos+=1+i;
			parser->buffer[parser->elt_name_end-1] = sep;
			break;
		case SAX_STATE_COMMENT:
			if (!xml_sax_parse_comments(parser)) {
				xml_sax_swap(parser);
				goto exit;
			}
			break;
		case SAX_STATE_ATT_NAME:
		case SAX_STATE_ATT_VALUE:
			if (xml_sax_parse_attribute(parser))
				goto exit;
			break;
		case SAX_STATE_ENTITY:
			xml_sax_parse_entity(parser);
			break;
		case SAX_STATE_SKIP_DOCTYPE:
			xml_sax_skip_doctype(parser);
			break;
		case SAX_STATE_XML_PROC:
			xml_sax_skip_xml_proc(parser);
			break;
		case SAX_STATE_CDATA:
			xml_sax_cdata(parser);
			break;
		case SAX_STATE_SYNTAX_ERROR:
			return GF_CORRUPTED_DATA;
		case SAX_STATE_ALLOC_ERROR:
			return GF_OUT_OF_MEM;
		case SAX_STATE_DONE:
			return GF_EOS;
		}
	}
exit:
#if 0
	if (is_text) {
		if (i) xml_sax_store_text(parser, i);
		/*DON'T FLUSH TEXT YET, wait for next '<' to do so otherwise we may corrupt xml base entities (&apos;, ...)*/
	}
#endif
	xml_sax_swap(parser);

	if (parser->sax_state==SAX_STATE_SYNTAX_ERROR)
		return GF_CORRUPTED_DATA;
	else
		return GF_OK;
}

static GF_Err gf_xml_sax_parse_intern(GF_SAXParser *parser, char *current)
{
	u32 count;
	/*solve entities*/
	count = gf_list_count(parser->entities);
	while (count) {
		char *entityEnd;
		XML_Entity *ent;
		char *entityStart = strstr(current, "&");
		Bool needs_text;
		u32 line_num;

		/*if in entity, the start of the entity is in the buffer !!*/
		if (parser->in_entity) {
			u32 len;
			char *name;
			entityEnd = strstr(current, ";");
			if (!entityEnd) return xml_sax_append_string(parser, current);
			entityStart = strrchr(parser->buffer, '&');

			entityEnd[0] = 0;
			len = (u32) strlen(entityStart) + (u32) strlen(current) + 1;
			name = (char*)gf_malloc(sizeof(char)*len);
			sprintf(name, "%s%s;", entityStart+1, current);

			ent = gf_xml_locate_entity(parser, name, &needs_text);
			gf_free(name);

			//entity not found, parse as regular string
			if (!ent && !needs_text) {
				xml_sax_append_string(parser, current);
				xml_sax_parse(parser, GF_TRUE);
				entityEnd[0] = ';';
				current = entityEnd;
				parser->in_entity = GF_FALSE;
				continue;
			}
			gf_assert(ent);
			/*truncate input buffer*/
			parser->line_size -= (u32) strlen(entityStart);
			entityStart[0] = 0;

			parser->in_entity = GF_FALSE;
			entityEnd[0] = ';';
			current = entityEnd+1;
		} else {
			if (!entityStart) break;

			ent = gf_xml_locate_entity(parser, entityStart+1, &needs_text);

			/*store current string before entity start*/
			entityStart[0] = 0;
			xml_sax_append_string(parser, current);
			xml_sax_parse(parser, GF_TRUE);
			entityStart[0] = '&';

			/*this is not an entitiy*/
			if (!ent && !needs_text) {
				xml_sax_append_string(parser, "&");
				current = entityStart+1;
				continue;
			}

			if (!ent) {
				parser->in_entity = GF_TRUE;
				/*store entity start*/
				return xml_sax_append_string(parser, entityStart);
			}
			current = entityStart + ent->namelen + 2;
		}
		/*append entity*/
		line_num = parser->line;
		xml_sax_append_string(parser, ent->value);
		GF_Err e = xml_sax_parse(parser, GF_TRUE);
		parser->line = line_num;
		if (e) return e;

	}
	xml_sax_append_string(parser, current);
	return xml_sax_parse(parser, GF_FALSE);
}

GF_EXPORT
GF_Err gf_xml_sax_parse(GF_SAXParser *parser, const void *string)
{
	GF_Err e;
	char *current;
	char *utf_conv = NULL;

	if (parser->unicode_type < 0) return GF_BAD_PARAM;

	if (parser->unicode_type>1) {
		const u16 *sptr = (const u16 *)string;
		u32 len = 2 * gf_utf8_wcslen(sptr);
		utf_conv = (char *)gf_malloc(sizeof(char)*(len+1));
		len = gf_utf8_wcstombs(utf_conv, len, &sptr);
		if (len == GF_UTF8_FAIL) {
			parser->sax_state = SAX_STATE_SYNTAX_ERROR;
			gf_free(utf_conv);
			return GF_CORRUPTED_DATA;
		}
		utf_conv[len] = 0;
		current = utf_conv;
	} else {
		current = (char *)string;
	}

	e = gf_xml_sax_parse_intern(parser, current);
	if (utf_conv) gf_free(utf_conv);
	return e;
}

static GF_Err xml_sax_read_file(GF_SAXParser *parser)
{
	GF_Err e = GF_EOS;
	unsigned char szLine[XML_INPUT_SIZE+2];

#ifdef NO_GZIP
	if (!parser->f_in) return GF_BAD_PARAM;
#else
	if (!parser->gz_in) return GF_BAD_PARAM;
#endif


	while (!parser->suspended) {
#ifdef NO_GZIP
		s32 read = (s32)gf_fread(szLine, XML_INPUT_SIZE, parser->f_in);
#else
		s32 read = gf_gzread(parser->gz_in, szLine, XML_INPUT_SIZE);
#endif
		if ((read<=0) /*&& !parser->node_depth*/) break;
		szLine[read] = 0;
		szLine[read+1] = 0;
		e = gf_xml_sax_parse(parser, szLine);
		if (e) break;
		if (parser->file_pos > parser->file_size) parser->file_size = parser->file_pos + 1;
		if (parser->on_progress) parser->on_progress(parser->sax_cbck, parser->file_pos, parser->file_size);
	}

#ifdef NO_GZIP
	if (gf_feof(parser->f_in)) {
#else
	if (gf_gzeof(parser->gz_in)) {
#endif
		if (!e) e = GF_EOS;
		if (parser->on_progress) parser->on_progress(parser->sax_cbck, parser->file_size, parser->file_size);

#ifdef NO_GZIP
		gf_fclose(parser->f_in);
		parser->f_in = NULL;
#else
		gf_gzclose(parser->gz_in);
		parser->gz_in = 0;
#endif

		parser->elt_start_pos = parser->elt_end_pos = 0;
		parser->elt_name_start = parser->elt_name_end = 0;
		parser->att_name_start = 0;
		parser->current_pos = 0;
		parser->line_size = 0;
		parser->att_sep = 0;
		parser->file_pos = 0;
		parser->file_size = 0;
		parser->line_size = 0;
	}
	return e;
}

GF_EXPORT
GF_Err gf_xml_sax_parse_file(GF_SAXParser *parser, const char *fileName, gf_xml_sax_progress OnProgress)
{
	FILE *test;
	GF_Err e;
	u64 filesize;
#ifndef NO_GZIP
	gzFile gzInput;
#endif
	unsigned char szLine[6];

	parser->on_progress = OnProgress;

	if (!strncmp(fileName, "gmem://", 7)) {
		u32 size;
		u8 *xml_mem_address;
		e = gf_blob_get(fileName, &xml_mem_address, &size, NULL);
		if (e) return e;

		parser->file_size = size;
		//copy possible BOM
		memcpy(szLine, xml_mem_address, 4);
		szLine[4] = szLine[5] = 0;

		parser->file_pos = 0;
		parser->elt_start_pos = 0;
		parser->current_pos = 0;

		e = gf_xml_sax_init(parser, szLine);
        if (!e) {
            e = gf_xml_sax_parse(parser, xml_mem_address+4);
            if (parser->on_progress) parser->on_progress(parser->sax_cbck, parser->file_pos, parser->file_size);
        }
        gf_blob_release(fileName);

		parser->elt_start_pos = parser->elt_end_pos = 0;
		parser->elt_name_start = parser->elt_name_end = 0;
		parser->att_name_start = 0;
		parser->current_pos = 0;
		parser->line_size = 0;
		parser->att_sep = 0;
		parser->file_pos = 0;
		parser->file_size = 0;
		parser->line_size = 0;
		return e;
	}

	/*check file exists and gets its size (zlib doesn't support SEEK_END)*/
	test = gf_fopen(fileName, "rb");
	if (!test) return GF_URL_ERROR;

	filesize = gf_fsize(test);
	gf_fatal_assert(filesize < 0x80000000);
	parser->file_size = (u32) filesize;
	gf_fclose(test);

	parser->file_pos = 0;
	parser->elt_start_pos = 0;
	parser->current_pos = 0;
	//open file and copy possible BOM
#ifdef NO_GZIP
	parser->f_in = gf_fopen(fileName, "rt");
	if (gf_fread(szLine, 4, parser->f_in) != 4) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CORE, ("[XML] Error loading BOM\n"));
	}
#else
	gzInput = gf_gzopen(fileName, "rb");
	if (!gzInput) return GF_IO_ERR;
	parser->gz_in = gzInput;
	/*init SAX parser (unicode setup)*/
	gf_gzread(gzInput, szLine, 4);
#endif

	szLine[4] = szLine[5] = 0;
	e = gf_xml_sax_init(parser, szLine);
	if (e) return e;

	return xml_sax_read_file(parser);
}

static void xmt_resolve_od_links(GF_XMTParser *parser)
{
	u32 i, j;
	XMT_ESDLink *esdl, *esdl2;
	XMT_ODLink *l;
	char szURL[5000];

	i=0;
	while ((esdl = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &i))) {
		if (!esdl->esd) {
			xmt_report(parser, GF_BAD_PARAM, "Stream %s ID %d has no associated ES descriptor\n", esdl->desc_name ? esdl->desc_name : "", esdl->ESID);
			i--;
			gf_list_rem(parser->esd_links, i);
			if (esdl->desc_name) gf_free(esdl->desc_name);
			gf_free(esdl);
			continue;
		}
		if (esdl->ESID) esdl->esd->ESID = esdl->ESID;
		else if (!esdl->esd->ESID) {
			u16 ESID = 1;
			while (!xmt_esid_available(parser, ESID)) ESID++;
			esdl->esd->ESID = ESID;
		}
	}

	i=0;
	while ((esdl = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &i))) {
		Bool use_old_fmt;
		u16 ocr_id;
		char szTest[50];

		esdl->esd->OCRESID = 0;
		if (!esdl->OCR_Name) continue;

		use_old_fmt = 0;
		ocr_id = atoi(esdl->OCR_Name);
		sprintf(szTest, "%d", ocr_id);
		if (!stricmp(szTest, esdl->OCR_Name)) use_old_fmt = 1;

		j=0;
		while ((esdl2 = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &j))) {
			if (esdl2->desc_name && !strcmp(esdl2->desc_name, esdl->OCR_Name)) {
				esdl->esd->OCRESID = esdl2->esd->ESID;
				break;
			}
			if (use_old_fmt && (esdl2->esd->ESID==ocr_id)) {
				esdl->esd->OCRESID = ocr_id;
				break;
			}
		}
		if (!esdl->esd->OCRESID) {
			xmt_report(parser, GF_OK, "WARNING: Could not find clock reference %s for ES %s - forcing self-synchronization", esdl->OCR_Name, esdl->desc_name);
		}
		gf_free(esdl->OCR_Name);
		esdl->OCR_Name = NULL;
	}

	i=0;
	while ((esdl = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &i))) {
		Bool use_old_fmt;
		u16 dep_id;
		char szTest[50];

		esdl->esd->dependsOnESID = 0;
		if (!esdl->Depends_Name) continue;

		use_old_fmt = 0;
		dep_id = atoi(esdl->Depends_Name);
		sprintf(szTest, "%d", dep_id);
		if (!stricmp(szTest, esdl->Depends_Name)) use_old_fmt = 1;

		j=0;
		while ((esdl2 = (XMT_ESDLink *)gf_list_enum(parser->esd_links, &j))) {
			if (esdl2->desc_name && !strcmp(esdl2->desc_name, esdl->Depends_Name)) {
				esdl->esd->dependsOnESID = esdl2->esd->ESID;
				break;
			}
			if (use_old_fmt && (esdl2->esd->ESID==dep_id)) {
				esdl->esd->dependsOnESID = dep_id;
				break;
			}
		}
		if (!esdl->esd->dependsOnESID) {
			xmt_report(parser, GF_OK, "WARNING: Could not find stream dependence %s for ES %s - forcing self-synchronization", esdl->Depends_Name, esdl->desc_name);
		}
		gf_free(esdl->Depends_Name);
		esdl->Depends_Name = NULL;
	}

	while (gf_list_count(parser->esd_links)) {
		esdl = (XMT_ESDLink *)gf_list_get(parser->esd_links, 0);
		gf_list_rem(parser->esd_links, 0);
		if (esdl->desc_name) gf_free(esdl->desc_name);
		gf_free(esdl);
	}

	i=0;
	while ((l = (XMT_ODLink*)gf_list_enum(parser->od_links, &i))) {
		if (l->od && !l->od->objectDescriptorID) {
			u16 ODID = 1;
			while (!xmt_odid_available(parser, ODID)) ODID++;
			l->od->objectDescriptorID = ODID;
		}
		if (l->od) {
			if (!l->ID) l->ID = l->od->objectDescriptorID;
			gf_assert(l->ID == l->od->objectDescriptorID);
		}
	}

	i=0;
	while ((l = (XMT_ODLink*)gf_list_enum(parser->od_links, &i))) {
		XMT_ODLink *l2;
		if (!l->ID) continue;
		j=i+1;
		while ((l2 = (XMT_ODLink*)gf_list_enum(parser->od_links, &j))) {
			if (!l2->ID) continue;
			if (l->ID == l2->ID) {
				while (gf_list_count(l2->mf_urls)) {
					MFURL *url = (MFURL *)gf_list_get(l2->mf_urls, 0);
					gf_list_rem(l2->mf_urls, 0);
					gf_list_add(l->mf_urls, url);
				}
				j--;
				gf_list_rem(parser->od_links, j);
				if (l2->desc_name) gf_free(l2->desc_name);
				gf_list_del(l2->mf_urls);
				gf_free(l2);
			}
		}
	}

	while (gf_list_count(parser->od_links) ) {
		l = (XMT_ODLink*)gf_list_get(parser->od_links, 0);
		if (!l->od) {
			if (l->ID) {
				if (l->desc_name) {
					xmt_report(parser, GF_OK, "WARNING: OD \"%s\" (ID %d) not assigned", l->desc_name, l->ID);
				} else {
					xmt_report(parser, GF_OK, "WARNING: OD ID %d not assigned", l->ID);
				}
			}
		} else {
			MFURL *the_url;
			j=0;
			while ((the_url = (MFURL *)gf_list_enum(l->mf_urls, &j))) {
				u32 k;
				char *seg = NULL;
				for (k=0; k<the_url->count; k++) {
					SFURL *url = &the_url->vals[k];
					if (url->url) seg = strstr(url->url, "#");
					if (seg) {
						sprintf(szURL, "od:%d#%s", l->od->objectDescriptorID, seg+1);
						gf_free(url->url);
						url->url = gf_strdup(szURL);
					} else {
						if (url->url) gf_free(url->url);
						url->url = NULL;
						url->OD_ID = l->od->objectDescriptorID;
					}
				}
			}
		}

		if (l->desc_name) gf_free(l->desc_name);
		gf_list_del(l->mf_urls);
		gf_free(l);
		gf_list_rem(parser->od_links, 0);
	}
}

static GF_Err load_xmt_run(GF_SceneLoader *load)
{
	GF_Err e;
	GF_XMTParser *parser = (GF_XMTParser *)load->loader_priv;
	if (!parser) {
		e = load_xmt_initialize(load, NULL);
		if (e) return e;
		parser = (GF_XMTParser *)load->loader_priv;
		if (!parser) return GF_OUT_OF_MEM;
	}

	e = gf_xml_sax_parse_file(parser->sax_parser, (const char *)load->fileName, xmt_progress);
	if (e==GF_OK) e = parser->last_error;

	xmt_resolve_routes(parser);
	xmt_resolve_od_links(parser);

	parser->last_error=GF_OK;
	if (e<0) return xmt_report(parser, e, "Invalid XML document: %s", gf_xml_sax_get_error(parser->sax_parser));

	return GF_OK;
}
