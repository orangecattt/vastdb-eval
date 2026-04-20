#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

typedef enum {
    GF_OK = 0,
    GF_BAD_PARAM = -1,
    GF_OUT_OF_MEM = -2,
    GF_CORRUPTED_DATA = -5,
    GF_EOS = 1,
} GF_Err;

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef long long s64;
typedef unsigned long long u64;
typedef int Bool;
#define GF_TRUE 1
#define GF_FALSE 0

#define GF_UTF8_FAIL 0xFFFFFFFF

#define GF_EXPORT __attribute__((visibility("default")))

#define GF_SAFEALLOC(__ptr, __struct) {\
    (__ptr) = (__struct *) gf_malloc(sizeof(__struct));\
    if (__ptr) {\
        memset((void *) (__ptr), 0, sizeof(__struct));\
    }\
}

#define XML_INPUT_SIZE 4096

typedef struct _tag_array GF_List;
typedef struct _tag_sax_parser GF_SAXParser;

typedef struct
{
    char *name;
    char *value;
} GF_XMLAttribute;

typedef struct
{
    u32 name_start, name_end;
    u32 val_start, val_end;
    Bool has_entities;
} GF_XMLSaxAttribute;

typedef struct
{
    char *name;
    char *value;
    u32 namelen;
    u8 sep;
} XML_Entity;

enum
{
    SAX_STATE_ATT_NAME,
    SAX_STATE_ATT_VALUE,
    SAX_STATE_ELEMENT,
    SAX_STATE_COMMENT,
    SAX_STATE_TEXT_CONTENT,
    SAX_STATE_ENTITY,
    SAX_STATE_SKIP_DOCTYPE,
    SAX_STATE_CDATA,
    SAX_STATE_DONE,
    SAX_STATE_XML_PROC,
    SAX_STATE_SYNTAX_ERROR,
    SAX_STATE_ALLOC_ERROR,
};

struct _tag_sax_parser
{
    s32 unicode_type;
    char *buffer;
    u32 alloc_size, line_size, current_pos;
    u32 node_depth;

#ifdef NO_GZIP
    FILE *f_in;
#else
    void *gz_in;
#endif
    u32 line, file_size, file_pos;

    void (*sax_node_start)(void *sax_cbck, const char *node_name, const char *name_space, const GF_XMLAttribute *attributes, u32 nb_attributes);
    void (*sax_node_end)(void *sax_cbck, const char *node_name, const char *name_space);
    void (*sax_text_content)(void *sax_cbck, const char *content, Bool is_cdata);
    void *sax_cbck;
    void (*on_progress)(void *cbck, u64 done, u64 total);

    u32 sax_state;
    u32 init_state;
    GF_List *entities;
    char att_sep;
    Bool in_entity, suspended;
    u32 in_quote;

    u32 elt_start_pos, elt_end_pos;

    char err_msg[1000];

    u32 att_name_start, elt_name_start, elt_name_end, text_start, text_end;
    u32 text_check_escapes;

    GF_XMLAttribute *attrs;
    GF_XMLSaxAttribute *sax_attrs;
    u32 nb_attrs, nb_alloc_attrs;
    u32 ent_rec_level;
};

typedef struct {
    u64 num;
    u64 den;
} GF_Fraction64;

void* gf_malloc(size_t size);
void* gf_realloc(void *ptr, size_t size);
void gf_free(void *ptr);
char* gf_strdup(const char *str);
GF_Err gf_dynstrcat(char **str, const char *to_append, const char *sep);

GF_List *gf_list_new();
void gf_list_del(GF_List *ptr);
u32 gf_list_count(const GF_List *ptr);
GF_Err gf_list_add(GF_List *ptr, void* item);
void *gf_list_get(GF_List *ptr, u32 position);
void *gf_list_last(GF_List *ptr);

u32 gf_utf8_wcslen(const unsigned short *s);
u32 gf_utf8_wcstombs(char* dst, size_t dst_len, const unsigned short** srcp);

static void xml_sax_swap(GF_SAXParser *parser);
static void xml_sax_node_start(GF_SAXParser *parser);
static void xml_sax_node_end(GF_SAXParser *parser, Bool had_children);
static void xml_sax_store_text(GF_SAXParser *parser, u32 txt_len);
static char *xml_get_current_text(GF_SAXParser *parser);
static void xml_sax_flush_text(GF_SAXParser *parser);
static void xml_sax_skip_doctype(GF_SAXParser *parser);
static void xml_sax_skip_xml_proc(GF_SAXParser *parser);
static Bool xml_sax_parse_attribute(GF_SAXParser *parser);
static Bool xml_sax_parse_comments(GF_SAXParser *parser);
static void xml_sax_cdata(GF_SAXParser *parser);

static GF_Err xml_sax_append_string(GF_SAXParser *parser, char *string)
{
	u32 size = parser->line_size;
	u32 nl_size = (u32) strlen(string);

	if (!nl_size) return GF_OK;

	if ( (parser->alloc_size < size+nl_size+1)
	        /*		|| (parser->alloc_size / 2 ) > size+nl_size+1 */
	   )
	{
		parser->alloc_size = size+nl_size+1;
		parser->alloc_size = 3 * parser->alloc_size / 2;
		parser->buffer = (char*)gf_realloc(parser->buffer, sizeof(char) * parser->alloc_size);
		if (!parser->buffer ) return GF_OUT_OF_MEM;
	}
	memcpy(parser->buffer+size, string, sizeof(char)*nl_size);
	parser->buffer[size+nl_size] = 0;
	parser->line_size = size+nl_size;
	return GF_OK;
}

static void xml_sax_parse_entity(GF_SAXParser *parser)
{
	char szC[2];
	char *ent_name=NULL;
	u32 i = 0;
	XML_Entity *ent = (XML_Entity *)gf_list_last(parser->entities);
	char *skip_chars = " \t\n\r";
	i=0;
	if (ent && ent->value) ent = NULL;
	if (ent) skip_chars = NULL;
	szC[1]=0;

	while (parser->current_pos+i < parser->line_size) {
		u8 c = parser->buffer[parser->current_pos+i];
		if (skip_chars && strchr(skip_chars, c)) {
			if (c=='\n') parser->line++;
			parser->current_pos++;
			continue;
		}
		if (!ent && (c=='%')) {
			parser->current_pos+=i+1;
			parser->sax_state = SAX_STATE_SKIP_DOCTYPE;
			if (ent_name) gf_free(ent_name);
			return;
		}
		else if (!ent && ((c=='\"') || (c=='\'')) ) {
			GF_SAFEALLOC(ent, XML_Entity);
			if (!ent) {
				parser->sax_state = SAX_STATE_ALLOC_ERROR;
				if (ent_name) gf_free(ent_name);
				return;
			}
			if (!ent_name) gf_dynstrcat(&ent_name, "", NULL);

			ent->name = ent_name;
			ent_name=NULL;
			ent->namelen = (u32) strlen(ent->name);
			ent->sep = c;
			parser->current_pos += 1+i;
			assert(parser->current_pos < parser->line_size);
			xml_sax_swap(parser);
			i=0;
			gf_list_add(parser->entities, ent);
			skip_chars = NULL;
		} else if (ent && c==ent->sep) {
			if (ent_name) gf_free(ent_name);
			xml_sax_store_text(parser, i);

			ent->value = xml_get_current_text(parser);
			if (!ent->value) ent->value = gf_strdup("");

			parser->current_pos += 1;
			assert(parser->current_pos < parser->line_size);
			xml_sax_swap(parser);
			parser->sax_state = SAX_STATE_SKIP_DOCTYPE;
			return;
		} else if (!ent) {
			szC[0] = c;
			gf_dynstrcat(&ent_name, szC, NULL);
			i++;
		} else {
			i++;
		}
	}
	if (ent_name) gf_free(ent_name);
	xml_sax_store_text(parser, i);
}

static XML_Entity *gf_xml_locate_entity(GF_SAXParser *parser, char *ent_start, Bool *needs_text)
{
	u32 i, count;
	u32 len = (u32) strlen(ent_start);

	*needs_text = GF_FALSE;
	count = gf_list_count(parser->entities);

	for (i=0; i<count; i++) {
		XML_Entity *ent = (XML_Entity *)gf_list_get(parser->entities, i);
		if (len < ent->namelen + 1) {
			if (strncmp(ent->name, ent_start, len))
			 	return NULL;

			*needs_text = GF_TRUE;
			return NULL;
		}
		if (!strncmp(ent->name, ent_start, ent->namelen) && (ent_start[ent->namelen]==';')) {
			return ent;
		}
	}
	return NULL;
}

static GF_Err gf_xml_sax_parse_intern(GF_SAXParser *parser, char *current);

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
					if ((parser->line_size>=2*XML_INPUT_SIZE) && !parser->init_state)
						parser->sax_state = SAX_STATE_SYNTAX_ERROR;

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
				assert(parser->current_pos < parser->line_size);
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
			assert(parser->elt_start_pos <= parser->file_pos + parser->current_pos);
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
			else {
				xml_sax_flush_text(parser);
				if (parser->init_state) {
					parser->init_state = 0;
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
							e = GF_BAD_PARAM;
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
	xml_sax_swap(parser);

	if (parser->sax_state==SAX_STATE_SYNTAX_ERROR)
		return GF_CORRUPTED_DATA;
	else
		return GF_OK;
}

static GF_Err gf_xml_sax_parse_intern(GF_SAXParser *parser, char *current)
{
	u32 count;
	count = gf_list_count(parser->entities);
	while (count) {
		char *entityEnd;
		XML_Entity *ent;
		char *entityStart = strstr(current, "&");
		Bool needs_text;
		u32 line_num;

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

			if (!ent && !needs_text) {
				xml_sax_append_string(parser, current);
				xml_sax_parse(parser, GF_TRUE);
				entityEnd[0] = ';';
				current = entityEnd;
				continue;
			}
			assert(ent);
			parser->line_size -= (u32) strlen(entityStart);
			entityStart[0] = 0;

			parser->in_entity = GF_FALSE;
			entityEnd[0] = ';';
			current = entityEnd+1;
		} else {
			if (!entityStart) break;

			ent = gf_xml_locate_entity(parser, entityStart+1, &needs_text);

			entityStart[0] = 0;
			xml_sax_append_string(parser, current);
			xml_sax_parse(parser, GF_TRUE);
			entityStart[0] = '&';

			if (!ent && !needs_text) {
				xml_sax_append_string(parser, "&");
				current = entityStart+1;
				continue;
			}

			if (!ent) {
				parser->in_entity = GF_TRUE;
				return xml_sax_append_string(parser, entityStart);
			}
			current = entityStart + ent->namelen + 2;
		}
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
