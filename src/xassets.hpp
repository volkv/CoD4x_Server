/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/



#ifndef __XASSETS_H__
#define __XASSETS_H__

#include "qshared.hpp"
#include "dobj.hpp"
#include "xassets/weapondef.hpp"
#include "xassets/material.hpp"
#include "world.hpp"


typedef struct
{
  const char *name;
  int allocFlags;
  int freeFlags;
}XZoneInfo;

enum XAssetType
{
  ASSET_TYPE_XMODELPIECES,
  ASSET_TYPE_PHYSPRESET,
  ASSET_TYPE_XANIMPARTS,
  ASSET_TYPE_XMODEL,
  ASSET_TYPE_MATERIAL,
  ASSET_TYPE_TECHNIQUE_SET,
  ASSET_TYPE_IMAGE,
  ASSET_TYPE_SOUND,
  ASSET_TYPE_SOUND_CURVE,
  ASSET_TYPE_LOADED_SOUND,
  ASSET_TYPE_CLIPMAP,
  ASSET_TYPE_CLIPMAP_PVS,
  ASSET_TYPE_COMWORLD,
  ASSET_TYPE_GAMEWORLD_SP,
  ASSET_TYPE_GAMEWORLD_MP,
  ASSET_TYPE_MAP_ENTS,
  ASSET_TYPE_GFXWORLD,
  ASSET_TYPE_LIGHT_DEF,
  ASSET_TYPE_UI_MAP,
  ASSET_TYPE_FONT,
  ASSET_TYPE_MENULIST,
  ASSET_TYPE_MENU,
  ASSET_TYPE_LOCALIZE_ENTRY,
  ASSET_TYPE_WEAPON,
  ASSET_TYPE_SNDDRIVER_GLOBALS,
  ASSET_TYPE_FX,
  ASSET_TYPE_IMPACT_FX,
  ASSET_TYPE_AITYPE,
  ASSET_TYPE_MPTYPE,
  ASSET_TYPE_CHARACTER,
  ASSET_TYPE_XMODELALIAS,
  ASSET_TYPE_RAWFILE,
  ASSET_TYPE_STRINGTABLE,
  ASSET_TYPE_COUNT
};

union XAssetHeader
{
  struct XModelPieces *xmodelPieces;
  struct PhysPreset *physPreset;
  struct XAnimParts *parts;
  struct XModel *model;
  struct Material *material;
  struct MaterialPixelShader *pixelShader;
  struct MaterialVertexShader *vertexShader;
  struct MaterialTechniqueSet *techniqueSet;
  struct GfxImage *image;
  struct snd_alias_list_t *sound;
  struct SndCurve *sndCurve;
  struct LoadedSound_s* loadedsound;
  struct clipMap_s *clipMap;
  struct ComWorld *comWorld;
  struct GameWorldSp *gameWorldSp;
  GameWorldMp *gameWorldMp;
  struct MapEnts *mapEnts;
  struct GfxWorld *gfxWorld;
  struct GfxLightDef *lightDef;
  struct Font_s *font;
  struct MenuList *menuList;
  struct menuDef_t *menu;
  struct LocalizeEntry *localize;
  struct WeaponDef *weapon;
  struct SndDriverGlobals *sndDriverGlobals;
  struct FxEffectDef *fx;
  struct FxImpactTable *impactFx;
  struct RawFile *rawfile;
  struct StringTable *stringTable;
  void *data;
};

struct XAsset
{
  enum XAssetType type;
  union XAssetHeader header;
};

#ifdef __cplusplus
extern "C"
{
#endif

void R_Init();
void CCDECL DB_SetInitializing(bool);
qboolean CCDECL DB_FileExists(const char* filename, int mode);
qboolean CCDECL DB_ModFileExists(void);
void CCDECL DB_LoadXAssets(XZoneInfo*, unsigned int assetscount, int);
int CCDECL DB_GetXAssetTypeSize(int type);
void CCDECL XAnimInit(void);
void XAssets_PatchLimits(void);
void Material_DirtyTechniqueSetOverrides();
void BG_FillInAllWeaponItems();
void DB_FreeUnusedResources();
void DB_LoadXAssets_Hook(XZoneInfo*, unsigned int assetscount);
void DB_BuildOverallocatedXAssetList(char* configstring, int len);
void DB_SyncXAssets();
void DB_PostLoadXZone();
void DB_UpdateDebugZone();
void DB_AddUserMapDir(const char *dir);
void DB_ReferencedFastFiles(char* g_zoneSumList, char* g_zoneNameList, int maxsize);
int CCDECL DB_GetAllXAssetOfType(enum XAssetType type, union XAssetHeader *assets, int maxCount);
void CCDECL DB_ConvertOffsetToPointer(void *data);
void CCDECL Load_Stream(bool atStreamStart, const void *ptr, int size);
byte *CCDECL DB_AllocStreamPos(int alignment);
void CCDECL DB_LoadXFileData(byte *pos, int count);
void CCDECL DB_LoadDelayedImages();
void Load_XAssetListCustom();
void CCDECL Load_XAsset(bool atStreamStart);
void CCDECL Load_XStringCustom(const char **str);
void CCDECL Load_ScriptStringList(bool atStreamStart);
void CCDECL DB_IncStreamPos(int size);
void CCDECL DB_PushStreamPos(unsigned int index);
void CCDECL DB_PopStreamPos();
void CCDECL Load_MaterialHandle(bool atStreamStart);
void CCDECL Load_FxEffectDefHandle(bool atStreamStart);
void CCDECL Load_ScriptStringCustom(uint16_t *var);
void CCDECL Load_XModelPtr(bool atStreamStart);
void CCDECL Load_XString(bool atStreamStart);
void CCDECL Load_XAssetHeader(bool atStreamStart);
const char* DB_GetXAssetName(struct XAsset*);
void CCDECL Load_ScriptStringArray(bool atStreamStart, int count);
void CCDECL DB_EnumXAssets_FastFile(enum XAssetType type, void (CCDECL *func)(void* header, void *), void *inData, bool includeOverride);
void CCDECL DB_EnumXAssets(enum XAssetType type, void (CCDECL *func)(union XAssetHeader, void *), void *inData, bool includeOverride);
union XAssetHeader CCDECL DB_FindXAssetHeader(enum XAssetType type, const char *name, bool errorIfMissing, int waitTime);
XAssetHeader CCDECL DB_AddXAsset(enum XAssetType type, union XAssetHeader header);

/*
#if defined( __GNUC__ ) && !defined( __MINGW32__ )
//For GCC
void* CCDECL DB_FindXAssetHeaderReal(enum XAssetType type, const char *name);
static inline __attribute__((always_inline)) union XAssetHeader DB_FindXAssetHeader(enum XAssetType type, const char *name)
{
    union XAssetHeader r;

    r.data = DB_FindXAssetHeaderReal(type, name);
    return r;
}

#else

//For MSVC & MinGW
union XAssetHeader CCDECL DB_FindXAssetHeaderReal(enum XAssetType type, const char *name);
#define DB_FindXAssetHeader DB_FindXAssetHeaderReal

#endif

*/

void CCDECL Load_XStringPtr(bool atStreamstart);





#ifdef __cplusplus
}
#endif



struct ScriptStringList
{
  int count;
  const char **strings;
};


struct XAssetList
{
  struct ScriptStringList stringList;
  int assetCount;
  struct XAsset *assets;
};


/*
------------------------------------------------------------------------
Just structures here I am too lazy to create headerfiles for now
------------------------------------------------------------------------
*/

typedef struct
{
  AILSOUNDINFO ailInfo;
  byte *data;
}MssSound;


#endif

