#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

/* BITCODE type definitions */
typedef unsigned char BITCODE_RC;
typedef unsigned char BITCODE_B;
typedef unsigned char BITCODE_BB;
typedef unsigned char BITCODE_3B;
typedef unsigned char BITCODE_4BITS;
typedef uint16_t BITCODE_BS;
typedef int16_t BITCODE_BSd;
typedef uint16_t BITCODE_RS;
typedef uint32_t BITCODE_BL;
typedef int32_t BITCODE_BLd;
typedef uint32_t BITCODE_RL;
typedef uint64_t BITCODE_RLL;
typedef uint64_t BITCODE_BLL;
typedef double BITCODE_BD;
typedef double BITCODE_RD;
typedef double BITCODE_DD;
typedef double BITCODE_BT;
typedef long BITCODE_MC;
typedef unsigned long BITCODE_UMC;
typedef BITCODE_BL BITCODE_MS;
typedef unsigned char* BITCODE_TF;
typedef char* BITCODE_TV;
typedef BITCODE_TV BITCODE_T;
typedef uint16_t* BITCODE_TU;

/* 3D point type */
typedef struct { BITCODE_BD x, y, z; } BITCODE_3BD;

/* Version type enum */
typedef enum {
  R_INVALID = 0, R_1_1, R_1_2, R_1_3, R_1_4, R_2_0b, R_2_0, R_2_10, R_2_21,
  R_2_22, R_2_4, R_2_5, R_2_6, R_9, R_9c1, R_10, R_11b1, R_11b2, R_11, R_12 = R_11,
  R_13b1, R_13b2, R_13, R_13c3, R_14, R_2000b, R_2000, R_2000i, R_2002,
  R_2004a, R_2004b, R_2004c, R_2004, R_2005, R_2006, R_2007b, R_2007,
  R_2008, R_2009, R_2010b, R_2010, R_2011, R_2012, R_2013b, R_2013,
  R_2014, R_2015, R_2016, R_2017, R_2018b, R_2018, R_2019, R_2020, R_2021, R_2022,
  R_AFTER
} Dwg_Version_Type;

/* Object supertype */
typedef enum { DWG_SUPERTYPE_ENTITY, DWG_SUPERTYPE_OBJECT } Dwg_Object_Supertype;

/* Object type enum (partial) */
typedef enum {
  DWG_TYPE_FREED = 0xfffd,
  DWG_TYPE_UNKNOWN_ENT = 0xfffe,
  DWG_TYPE_UNKNOWN_OBJ = 0xffff,
} Dwg_Object_Type;

/* Error codes */
typedef enum {
  DWG_NOERR = 0,
  DWG_ERR_WRONGCRC = 1,
  DWG_ERR_NOTYETSUPPORTED = 2,
  DWG_ERR_UNHANDLEDCLASS = 4,
  DWG_ERR_INVALIDTYPE = 8,
  DWG_ERR_INVALIDHANDLE = 16,
  DWG_ERR_INVALIDEED = 32,
  DWG_ERR_VALUEOUTOFBOUNDS = 64,
} Dwg_Error;

/* Handle structure */
typedef struct _dwg_handle {
  unsigned char code;
  unsigned char size;
  BITCODE_RL value;
  BITCODE_B is_global;
} Dwg_Handle;

/* Object reference */
typedef struct _dwg_object_ref {
  struct _dwg_object *obj;
  Dwg_Handle handleref;
  unsigned long absolute_ref;
  uint16_t r11_idx;
} Dwg_Object_Ref;

typedef Dwg_Object_Ref* BITCODE_H;

/* Color structure */
typedef struct _dwg_color {
  BITCODE_BSd index;
  BITCODE_BS flag;
  BITCODE_BS raw;
  BITCODE_BL rgb;
  unsigned method;
  BITCODE_T name;
  BITCODE_T book_name;
  BITCODE_H handle;
} Dwg_Color;

/* Bit chain structure */
typedef struct _bit_chain {
  unsigned char *chain;
  long unsigned int size;
  long unsigned int byte;
  unsigned char bit;
  unsigned char opts;
  Dwg_Version_Type version;
  Dwg_Version_Type from_version;
  FILE *fh;
} Bit_Chain;

/* Forward declarations */
struct _dwg_struct;
typedef struct _dwg_class Dwg_Class;
typedef struct _dwg_entity_3DSOLID Dwg_Entity__3DSOLID;
#define Dwg_Entity_3DSOLID Dwg_Entity__3DSOLID
typedef struct _dwg_entity_PLANESURFACE Dwg_Entity_PLANESURFACE;

/* 3DSOLID sub-structures */
typedef struct _dwg_3DSOLID_wire {
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_RC type;
  BITCODE_BLd selection_marker;
  BITCODE_BL color;
  BITCODE_BLd acis_index;
  BITCODE_BL num_points;
  BITCODE_3BD* points;
  BITCODE_B transform_present;
  BITCODE_3BD axis_x, axis_y, axis_z;
  BITCODE_3BD translation, scale;
  BITCODE_B has_rotation, has_reflection, has_shear;
} Dwg_3DSOLID_wire;

typedef struct _dwg_3DSOLID_silhouette {
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_BL vp_id;
  BITCODE_3BD vp_target, vp_dir_from_target, vp_up_dir;
  BITCODE_B vp_perspective, has_wires;
  BITCODE_BL num_wires;
  Dwg_3DSOLID_wire *wires;
} Dwg_3DSOLID_silhouette;

typedef struct _dwg_3DSOLID_material {
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_BL array_index, mat_absref;
  BITCODE_H material_handle;
} Dwg_3DSOLID_material;

/* 3DSOLID fields macro */
#define _3DSOLID_FIELDS \
  BITCODE_B acis_empty, unknown; \
  BITCODE_BS version; \
  BITCODE_BL num_blocks; \
  BITCODE_BL* block_size; \
  char** encr_sat_data; \
  BITCODE_BL sab_size; \
  BITCODE_RC* acis_data; \
  BITCODE_B wireframe_data_present, point_present; \
  BITCODE_3BD point; \
  BITCODE_BL isolines, num_wires; \
  BITCODE_B isoline_present; \
  Dwg_3DSOLID_wire *wires; \
  BITCODE_BL num_silhouettes; \
  Dwg_3DSOLID_silhouette *silhouettes; \
  BITCODE_B acis_empty_bit; \
  BITCODE_BL num_materials; \
  Dwg_3DSOLID_material *materials; \
  BITCODE_B has_revision_guid; \
  char revision_guid[38]; \
  BITCODE_BL revision_major; \
  BITCODE_BS revision_minor1, revision_minor2; \
  BITCODE_RC revision_bytes[8]; \
  BITCODE_BL end_marker; \
  BITCODE_H history_id

/* Entity structures */
typedef struct _dwg_object_entity {
  BITCODE_RL size;
  unsigned int type;
  BITCODE_RL index;
  union {
    Dwg_Entity__3DSOLID *_3DSOLID;
    Dwg_Entity_PLANESURFACE *PLANESURFACE;
    void *token;
  } tio;
} Dwg_Object_Entity;

typedef struct _dwg_object_object {
  BITCODE_RL size;
  unsigned int type;
  BITCODE_RL index;
} Dwg_Object_Object;

/* Main Object structure */
typedef struct _dwg_object {
  BITCODE_RL size;
  unsigned long address;
  unsigned int type;
  BITCODE_RL index;
  Dwg_Object_Type fixedtype;
  char *name, *dxfname;
  Dwg_Object_Supertype supertype;
  union {
    Dwg_Object_Entity *entity;
    Dwg_Object_Object *object;
  } tio;
  Dwg_Handle handle;
  struct _dwg_struct *parent;
  Dwg_Class *klass;
  BITCODE_RL bitsize;
  unsigned long bitsize_pos, hdlpos;
  BITCODE_B was_bitsize_set, has_strings;
  BITCODE_RL stringstream_size;
  BITCODE_UMC handlestream_size;
  unsigned long common_size;
  BITCODE_RL num_unknown_bits;
  BITCODE_TF unknown_bits;
} Dwg_Object;

/* Dwg_Data structure (simplified) */
typedef struct _dwg_struct {
  long num_objects;
  long num_allocated_objects;
  Dwg_Object *object;
  unsigned int opts;
  struct {
    Dwg_Version_Type version, from_version;
  } header;
} Dwg_Data;

/* PLANESURFACE entity */
typedef struct _dwg_entity_PLANESURFACE {
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version, u_isolines, v_isolines;
  BITCODE_BL class_version;
} Dwg_Entity_PLANESURFACE;

/* 3DSOLID entity (simplified) */
struct _dwg_entity_3DSOLID {
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
};

/* Logging macros */
#define DWG_LOGLEVEL_NONE 0
#define DWG_LOGLEVEL_ERROR 1
#define DWG_LOGLEVEL_INFO 2
#define DWG_LOGLEVEL_TRACE 3
#define DWG_LOGLEVEL_HANDLE 4
#define DWG_LOGLEVEL_INSANE 5
#define DWG_LOGLEVEL_ALL 9

#ifndef DWG_LOGLEVEL
#define DWG_LOGLEVEL DWG_LOGLEVEL_ERROR
#endif

#define HANDLER fprintf
#define OUTPUT stderr

#define LOG(level, args...) \
  { if (DWG_LOGLEVEL >= DWG_LOGLEVEL_##level) { HANDLER (OUTPUT, args); } }

#define LOG_ERROR(args...) \
  { if (DWG_LOGLEVEL >= DWG_LOGLEVEL_ERROR) { \
      HANDLER (OUTPUT, "ERROR: "); LOG (ERROR, args) HANDLER (OUTPUT, "\n"); } }

#define LOG_INFO(args...) LOG (INFO, args)
#define LOG_TRACE(args...) LOG (TRACE, args)
#define LOG_HANDLE(args...) LOG (HANDLE, args)
#define LOG_INSANE(args...) LOG (INSANE, args)

#define DWG_OPTS_LOGLEVEL 0xf

/* CHK_OVERFLOW macro */
#define CHK_OVERFLOW(func, retval) \
  if (dat->byte >= dat->size) { \
    loglevel = dat->opts & DWG_OPTS_LOGLEVEL; \
    LOG_ERROR ("%s buffer overflow at %lu >= %lu", func, dat->byte, dat->size) \
    return retval; \
  }

/* Static loglevel variable */
static unsigned int loglevel;

/* External function declarations */
void bit_advance_position (Bit_Chain *dat, long advance);
unsigned long bit_position (Bit_Chain *dat);
void bit_set_position (Bit_Chain *dat, unsigned long bitpos);
BITCODE_B bit_read_B (Bit_Chain *dat);
void bit_write_B (Bit_Chain *dat, unsigned char value);
BITCODE_RC bit_read_RC (Bit_Chain *dat);
void bit_write_RC (Bit_Chain *dat, unsigned char value);
void bit_chain_init (Bit_Chain *dat, const int size);
void bit_chain_init_dat (Bit_Chain *restrict dat, const int size, const Bit_Chain *restrict from_dat);
void bit_chain_alloc (Bit_Chain *dat);
void bit_chain_alloc_size (Bit_Chain *dat, const size_t size);
void bit_chain_free (Bit_Chain *dat);
void bit_copy_chain (Bit_Chain *restrict orig_dat, Bit_Chain *restrict tmp_dat);
int dwg_encode_entity (Dwg_Object *restrict obj, Bit_Chain *dat, Bit_Chain *hdl_dat, Bit_Chain *str_dat);
int has_entity_DD (const Dwg_Object* obj);
int obj_has_strings (const Dwg_Object* obj);
void dxf_3dsolid_revisionguid (Dwg_Entity_3DSOLID *_obj);
void bit_write_BL (Bit_Chain *dat, BITCODE_BL value);
void bit_write_BS (Bit_Chain *dat, BITCODE_BS value);
void bit_write_BD (Bit_Chain *dat, BITCODE_BD value);
void bit_write_TF (Bit_Chain *restrict dat, BITCODE_TF restrict chain, unsigned int length);
void bit_write_H (Bit_Chain *restrict dat, Dwg_Handle *restrict handle);
void bit_write_3BD (Bit_Chain *dat, BITCODE_3BD value);
void bit_write_TV (Bit_Chain *restrict dat, BITCODE_TV restrict value);
int dwg_encode_common_entity_handle_data (Bit_Chain *dat, Bit_Chain *hdl_dat, Dwg_Object *obj);

/* Encoding macros */
#define FIELD_VALUE(nam) _obj->nam

#define FIELDG(nam, type, dxf) \
  { bit_write_##type (dat, (BITCODE_##type)_obj->nam); \
    LOG_TRACE (#nam ": " FORMAT_##type " [%d]", _obj->nam, dxf); LOG_POS }

#define FIELD_CAST(nam, type, cast, dxf) \
  { bit_write_##type (dat, (BITCODE_##cast)_obj->nam); \
    LOG_TRACE (#nam ": " FORMAT_##cast " [%d]", (BITCODE_##cast)_obj->nam, dxf); LOG_POS }

#define FIELD_B(nam, dxf) FIELDG (nam, B, dxf)
#define FIELD_BB(nam, dxf) FIELDG (nam, BB, dxf)
#define FIELD_3B(nam, dxf) FIELDG (nam, 3B, dxf)
#define FIELD_BS(nam, dxf) FIELDG (nam, BS, dxf)
#define FIELD_BL(nam, dxf) FIELDG (nam, BL, dxf)
#define FIELD_BD(nam, dxf) FIELDG (nam, BD, dxf)
#define FIELD_RC(nam, dxf) FIELDG (nam, RC, dxf)
#define FIELD_RS(nam, dxf) FIELDG (nam, RS, dxf)
#define FIELD_RD(nam, dxf) FIELDG (nam, RD, dxf)
#define FIELD_RL(nam, dxf) FIELDG (nam, RL, dxf)
#define FIELD_MC(nam, dxf) FIELDG (nam, MC, dxf)
#define FIELD_MS(nam, dxf) FIELDG (nam, MS, dxf)
#define FIELD_TV(nam, dxf) \
  { bit_write_TV (dat, _obj->nam); LOG_TRACE (#nam ": \"%s\" [TV %d]", _obj->nam, dxf); LOG_POS }
#define FIELD_TF(nam, len, dxf) \
  { bit_write_TF (dat, (BITCODE_TF)_obj->nam, len); LOG_TRACE (#nam ": [TF %d %d]", len, dxf); LOG_POS }
#define FIELD_TFF(nam, len, dxf) FIELD_TF(nam, len, dxf)
#define FIELD_TFFx(nam, len, dxf) FIELD_TF(nam, len, dxf)
#define FIELD_3BD(nam, dxf) \
  { bit_write_3BD (dat, _obj->nam); LOG_TRACE (#nam ": [3BD %d]", dxf); LOG_POS }

#define FORMAT_RC "0x%hhx"
#define FORMAT_B "%d"
#define FORMAT_BB "%u"
#define FORMAT_3B "%u"
#define FORMAT_BS "%" PRIu16
#define FORMAT_RS "%" PRIu16
#define FORMAT_BL "%" PRIu32
#define FORMAT_RL "%" PRIu32
#define FORMAT_BD "%f"
#define FORMAT_RD "%f"
#define FORMAT_MC "%ld"
#define FORMAT_MS "%" PRIu32

/* Sub-field macros */
#define SUB_FIELD_BL(o, nam, dxf) FIELDG (o.nam, BL, dxf)
#define SUB_FIELD_3BD(o, nam, dxf) FIELD_3BD (o.nam, dxf)
#define SUB_FIELD_B(o, nam, dxf) FIELDG (o.nam, B, dxf)

#define VALUE_HANDLE(value, nam, handle_code, dxf) \
  { /* stub - would write handle */ (void)value; (void)handle_code; (void)dxf; }
#define FIELD_HANDLE(nam, handle_code, dxf) VALUE_HANDLE (_obj->nam, nam, handle_code, dxf)
#define SUB_FIELD_HANDLE(o, nam, handle_code, dxf) VALUE_HANDLE (_obj->o.nam, nam, handle_code, dxf)

/* Control flow macros for encode context */
#define DXF if (0)
#define DXF_OR_PRINT if (0)
#define DECODER if (0)
#define ENCODER if (0)
#define JSON if (0)
#define FREE if (0)
#define PRINT if (0)

#define SET_PARENT(field, obj)
#define SET_PARENT_OBJ(field)

/* Version checking macros */
static unsigned int cur_ver = 0;
#define SINCE(v) if (dat->from_version >= v)
#define VERSIONS(x, y) if (dat->from_version >= x && dat->from_version <= y)
#define PRE(v) if (dat->from_version < v)
#define RESET_VER cur_ver = dat->version;

/* REPEAT macros for encode */
#define OVERFLOW_CHECK(nam, size) /* stub */
#define _REPEAT_N(times, nam, type, idx) \
  for (rcount##idx = 0; rcount##idx < (BITCODE_BL)(times); rcount##idx++)
#define _REPEAT(times, nam, type, idx) _REPEAT_N (_obj->times, nam, type, idx)
#define REPEAT(times, nam, type) _REPEAT (times, nam, type, 1)
#define REPEAT2(times, nam, type) _REPEAT_N (times, nam, type, 2)
#define REPEAT_BLOCK {
#define END_REPEAT_BLOCK }
#define END_REPEAT(nam)

/* 3DSOLID support macros */
#define SUBCLASS(name)
#define DXF_3DSOLID
#define DECODE_3DSOLID
#define ENCODE_3DSOLID
#define JSON_3DSOLID
#define FREE_3DSOLID
#define WIRESTRUCT_fields(w) /* stub for wire struct fields */
#define DECODE_UNKNOWN_BITS

/* Logging position macro */
#define LOG_POS \
  LOG_INSANE (" @%lu.%u", obj ? dat->byte - obj->address : dat->byte, dat->bit) \
  LOG_TRACE ("\n")

/* Encode common handles stub */
#define ENCODE_COMMON_HANDLES \
  if (obj->supertype == DWG_SUPERTYPE_OBJECT && dat->version >= R_13) { } \
  else if (obj->supertype == DWG_SUPERTYPE_ENTITY && dat->version >= R_13) { }
BITCODE_RC
bit_read_RC (Bit_Chain *dat)
{
  unsigned char result;
  unsigned char byte;

  CHK_OVERFLOW (__FUNCTION__, 0)
  byte = dat->chain[dat->byte];
  if (dat->bit == 0)
    result = byte;
  else
    {
      result = byte << dat->bit;
      if (dat->byte < dat->size - 1)
        {
          byte = dat->chain[dat->byte + 1];
          result |= byte >> (8 - dat->bit);
        }
      else
        {
          loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
          LOG_ERROR ("%s buffer overflow at %lu", __FUNCTION__, dat->byte + 1)
          return 0;
        }
    }

  bit_advance_position (dat, 8);
  return ((unsigned char)result);
}

void
bit_chain_alloc_size (Bit_Chain *dat, const size_t size)
{
  if (dat->size == 0)
    {
      bit_chain_init (dat, size);
    }
  else
    {
      dat->chain = (unsigned char *)realloc (dat->chain, dat->size + size);
      if (!dat->chain)
        {
          loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
          LOG_ERROR ("Out of memory")
          abort ();
        }
      memset (&dat->chain[dat->size], 0, size);
      dat->size += size;
    }
}

#define CHAIN_BLOCK 4096
void
bit_chain_alloc (Bit_Chain *dat)
{
  bit_chain_alloc_size (dat, CHAIN_BLOCK);
}

void
bit_copy_chain (Bit_Chain *restrict dat, Bit_Chain *restrict tmp_dat)
{
  unsigned long i;
  unsigned long dat_bits = bit_position (tmp_dat);
  unsigned long size = tmp_dat->byte;
  if (dat->chain == tmp_dat->chain){
    LOG_ERROR("bit_copy_chain: dat->chain == tmp_dat->chain");
    return;
  }
  while (dat->byte + size > dat->size)
    bit_chain_alloc (dat);
  // check if dat is byte aligned, tmp_dat always is. we can use memcpy then.
  if (!dat->bit)
    {
      assert (!tmp_dat->bit);
      memcpy (&dat->chain[dat->byte], &tmp_dat->chain[0], size);
      dat->byte += size;
    }
  else
    {
      bit_set_position (tmp_dat, 0);
      for (i = 0; i < size; i++)
        {
          bit_write_RC (dat, bit_read_RC (tmp_dat));
        }
      for (i = 0; i < dat_bits % 8; i++)
        {
          bit_write_B (dat, bit_read_B (tmp_dat));
        }
    }
  bit_set_position (tmp_dat, 0);
}

static void
obj_flush_hdlstream (Dwg_Object *restrict obj, Bit_Chain *restrict dat,
                     Bit_Chain *restrict hdl_dat)
{
  unsigned long datpos = bit_position (dat);
  unsigned long hdlpos = bit_position (hdl_dat);
  unsigned long objpos = obj->address * 8;
#if 0
  unsigned char* oldchain = dat->chain;
#endif
  LOG_TRACE ("Flush handle stream of size %lu (@%lu.%u) to @%lu.%lu\n", hdlpos,
             hdl_dat->byte, hdl_dat->bit, (datpos - objpos) / 8,
             (datpos - objpos) % 8);
  // This might change dat->chain
  bit_copy_chain (dat, hdl_dat);
}

#define START_HANDLE_STREAM                                                   \
  LOG_INSANE ("HANDLE_STREAM @%lu.%u\n", dat->byte - obj->address, dat->bit)  \
  if (!obj->bitsize || /* DD sizes can vary, but let unknown_bits asis */     \
      has_entity_DD (obj) || /* strings may be zero-terminated or not */      \
      obj_has_strings (obj)                                                   \
      || (dwg->header.version != dwg->header.from_version                     \
          && obj->fixedtype != DWG_TYPE_UNKNOWN_OBJ                           \
          && obj->fixedtype != DWG_TYPE_UNKNOWN_ENT))                         \
    {                                                                         \
      obj->bitsize = bit_position (dat) - (obj->address * 8);                 \
      LOG_TRACE (                                                             \
          "-bitsize calc from HANDLE_STREAM " FORMAT_RL " @%lu.%u (%lu)\n",   \
          obj->bitsize, dat->byte - obj->address, dat->bit, obj->address);    \
      obj->was_bitsize_set = 1;                                               \
    }                                                                         \
  if (!obj->hdlpos)                                                           \
    obj->hdlpos = bit_position (dat);                                         \
  {                                                                           \
    unsigned long _hpos = bit_position (hdl_dat);                             \
    if (_hpos > 0)                                                            \
      {                                                                       \
        /* save away special accumulated hdls, need to write common first */  \
        Bit_Chain dat1 = *hdl_dat;                                            \
        Bit_Chain dat2;                                                       \
        bit_chain_init_dat (&dat2, 12, dat);                                  \
        hdl_dat = &dat2;                                                      \
        ENCODE_COMMON_HANDLES                                                 \
        obj_flush_hdlstream (obj, dat, hdl_dat); /* common */                 \
        obj_flush_hdlstream (obj, dat, &dat1);   /* special accumulated */    \
        bit_chain_free (&dat1);                                               \
        bit_chain_free (&dat2);                                               \
        *hdl_dat = *dat;                                                      \
        hdl_dat = dat;                                                        \
      }                                                                       \
    else                                                                      \
      {                                                                       \
        if (hdl_dat != dat)                                                   \
          bit_chain_free (hdl_dat);                                           \
        hdl_dat = dat;                                                        \
        ENCODE_COMMON_HANDLES                                                 \
      }                                                                       \
  }                                                                           \
  RESET_VER

#define COMMON_ENTITY_HANDLE_DATA                                             \
  SINCE (R_13)                                                                \
  {                                                                           \
    START_HANDLE_STREAM;                                                      \
  }                                                                           \
  RESET_VER

#define ACTION_3DSOLID \
  SUBCLASS (AcDbModelerGeometry); \
  DXF_OR_PRINT { \
    DXF_3DSOLID \
  } \
  DECODER { \
    DECODE_3DSOLID \
  } \
  ENCODER { \
    ENCODE_3DSOLID \
  } \
  JSON { \
    JSON_3DSOLID \
  } \
  FREE_3DSOLID \
  COMMON_3DSOLID

#define COMMON_3DSOLID                                                        \
  FIELD_B (wireframe_data_present, 0);                                        \
  if (FIELD_VALUE (wireframe_data_present))                                   \
    {                                                                         \
      FIELD_B (point_present, 0);                                             \
      if (FIELD_VALUE (point_present))                                        \
        {                                                                     \
          FIELD_3BD (point, 0);                                               \
        }                                                                     \
      else                                                                    \
        {                                                                     \
          FIELD_VALUE (point.x) = 0;                                          \
          FIELD_VALUE (point.y) = 0;                                          \
          FIELD_VALUE (point.z) = 0;                                          \
        }                                                                     \
      FIELD_BL (isolines, 0);                                                 \
      FIELD_B (isoline_present, 0);                                           \
      if (FIELD_VALUE (isoline_present))                                      \
        {                                                                     \
          FIELD_BL (num_wires, 0);                                            \
          REPEAT (num_wires, wires, Dwg_3DSOLID_wire)                         \
          REPEAT_BLOCK                                                        \
            WIRESTRUCT_fields (wires[rcount1])                                \
            SET_PARENT (wires[rcount1], (Dwg_Entity__3DSOLID *)_obj);         \
          END_REPEAT_BLOCK                                                    \
          END_REPEAT (wires);                                                 \
          FIELD_BL (num_silhouettes, 0);                                      \
          REPEAT (num_silhouettes, silhouettes, Dwg_3DSOLID_silhouette)       \
          REPEAT_BLOCK                                                        \
            SUB_FIELD_BL (silhouettes[rcount1], vp_id, 0);                    \
            SUB_FIELD_3BD (silhouettes[rcount1], vp_target, 0); /* ?? */      \
            SUB_FIELD_3BD (silhouettes[rcount1], vp_dir_from_target, 0);      \
            SUB_FIELD_3BD (silhouettes[rcount1], vp_up_dir, 0);               \
            SUB_FIELD_B (silhouettes[rcount1], vp_perspective, 0);            \
            SUB_FIELD_B (silhouettes[rcount1], has_wires, 0);                 \
            if (_obj->silhouettes[rcount1].has_wires)                         \
              {                                                               \
                SUB_FIELD_BL (silhouettes[rcount1], num_wires, 0);            \
                REPEAT2 (silhouettes[rcount1].num_wires,                      \
                         silhouettes[rcount1].wires, Dwg_3DSOLID_wire)        \
                REPEAT_BLOCK                                                  \
                  WIRESTRUCT_fields (silhouettes[rcount1].wires[rcount2])     \
                  SET_PARENT (silhouettes[rcount1].wires[rcount2], (Dwg_Entity__3DSOLID *)_obj); \
                END_REPEAT_BLOCK                                              \
                END_REPEAT (silhouettes[rcount1].wires);                      \
              }                                                               \
            SET_PARENT (silhouettes[rcount1], (Dwg_Entity__3DSOLID *)_obj);    \
          END_REPEAT_BLOCK                                                    \
          END_REPEAT (silhouettes);                                           \
        }                                                                     \
    }                                                                         \
                                                                              \
  FIELD_B (acis_empty_bit, 0); /* ?? */                                       \
  if (FIELD_VALUE (version) > 1)                                              \
    {                                                                         \
      SINCE (R_2007)                                                          \
      {                                                                       \
        FIELD_BL (num_materials, 0);                                          \
        REPEAT (num_materials, materials, Dwg_3DSOLID_material)               \
        REPEAT_BLOCK                                                          \
          SUB_FIELD_BL (materials[rcount1], array_index, 0);                  \
          SUB_FIELD_BL (materials[rcount1], mat_absref, 0); /* ?? */          \
          SUB_FIELD_HANDLE (materials[rcount1], material_handle, 5, 0);       \
          SET_PARENT (materials[rcount1], (Dwg_Entity__3DSOLID *)_obj);        \
        END_REPEAT_BLOCK                                                      \
        END_REPEAT (materials);                                               \
      }                                                                       \
    }                                                                         \
  SINCE (R_2013)                                                              \
  {                                                                           \
    FIELD_B (has_revision_guid, 0);                                           \
    DXF { FIELD_TFF (revision_guid, 38, 2); }                                 \
    else                                                                      \
    {                                                                         \
      FIELD_BL (revision_major, 0);                                           \
      FIELD_BS (revision_minor1, 0);                                          \
      FIELD_BS (revision_minor2, 0);                                          \
      FIELD_TFFx (revision_bytes, 8, 0);                                      \
      DECODER { dxf_3dsolid_revisionguid ((Dwg_Entity_3DSOLID *)_obj); }      \
    }                                                                         \
    FIELD_BL (end_marker, 0);                                                 \
  }                                                                           \
                                                                              \
  COMMON_ENTITY_HANDLE_DATA;                                                  \
  DXF {                                                                       \
    SINCE (R_2007) {                                                          \
      SUBCLASS (AcDb3dSolid);                                                 \
      FIELD_HANDLE (history_id, 4, 350);                                      \
    }                                                                         \
  } else if (FIELD_VALUE (version) > 1) {                                     \
      FIELD_HANDLE (history_id, 4, 350);                                      \
  }                                                                           \
  FREE { FIELD_HANDLE (history_id, 4, 350); }

#define DWG_ENTITY(token)                                                     \
  static int dwg_encode_##token##_private (                                   \
      Bit_Chain *dat, Bit_Chain *hdl_dat, Bit_Chain *str_dat,                 \
      Dwg_Object *restrict obj);                                              \
  static int dwg_encode_##token (Bit_Chain *restrict dat,                     \
                                 Dwg_Object *restrict obj)                    \
  {                                                                           \
    int error;                                                                \
    Bit_Chain _hdl_dat = { 0 };                                               \
    Bit_Chain *hdl_dat = &_hdl_dat; /* a new copy */                          \
    Bit_Chain *str_dat = dat;       /* a ref */                               \
    LOG_INFO ("Encode entity " #token "\n");                                  \
    bit_chain_init_dat (hdl_dat, 128, dat);                                   \
    error = dwg_encode_entity (obj, dat, hdl_dat, str_dat);                   \
    if (error)                                                                \
      {                                                                       \
        LOG_HANDLE ("Early DWG_ENTITY exit\n");                               \
        if (hdl_dat != dat && hdl_dat->chain != dat->chain)                   \
          bit_chain_free (hdl_dat);                                           \
        return error;                                                         \
      }                                                                       \
    error = dwg_encode_##token##_private (dat, hdl_dat, str_dat, obj);        \
    if (error & DWG_ERR_VALUEOUTOFBOUNDS && hdl_dat != dat                    \
        && hdl_dat->chain != dat->chain)                                      \
      {                                                                       \
        LOG_HANDLE ("VALUEOUTOFBOUNDS bypassed DWG_ENTITY_END\n");            \
        /*bit_chain_free (hdl_dat);*/                                         \
      }                                                                       \
    return error;                                                             \
  }                                                                           \
  static int dwg_encode_##token##_private (                                   \
      Bit_Chain *dat, Bit_Chain *hdl_dat, Bit_Chain *str_dat,                 \
      Dwg_Object *restrict obj)                                               \
  {                                                                           \
    int error = 0;                                                            \
    BITCODE_BL vcount, rcount1, rcount2, rcount3, rcount4;                    \
    Dwg_Data *dwg = obj->parent;                                              \
    Dwg_Object_Entity *_ent = obj->tio.entity;                                \
    Dwg_Entity_##token *_obj = _ent->tio.token; \
    Dwg_3DSOLID_wire *wires = _obj->wires; Dwg_3DSOLID_silhouette *silhouettes = _obj->silhouettes; Dwg_3DSOLID_material *materials = _obj->materials

#define DWG_ENTITY_END                                                        \
    if (hdl_dat->byte > dat->byte)                                            \
      {                                                                       \
        dat->byte = hdl_dat->byte;                                            \
        dat->bit = hdl_dat->bit;                                              \
      }                                                                       \
    if (hdl_dat != dat && hdl_dat->chain != dat->chain)                       \
      bit_chain_free (hdl_dat);                                               \
    return error;                                                             \
  }

DWG_ENTITY (PLANESURFACE)
  DECODE_UNKNOWN_BITS
  ACTION_3DSOLID;
  FIELD_BS (modeler_format_version, 70); //def 1
  //FIELD_BL (bindata_size, 90);
  //FIELD_TF (bindata, FIELD_VALUE (bindata_size), 1); // in DXF as encrypted ASCII

  SUBCLASS (AcDbSurface)
  FIELD_BS (u_isolines, 71);
  FIELD_BS (v_isolines, 72);
  //SUBCLASS (AcDbPlaneSurface)
  //FIELD_BL (class_version, 90);
  //if (FIELD_VALUE (class_version) > 10)
  //  return DWG_ERR_VALUEOUTOFBOUNDS;
  COMMON_ENTITY_HANDLE_DATA;
DWG_ENTITY_END
