#pragma once

#include <vector>
#include <string>
#include <map>

#pragma warning( disable : 4200 )

struct NiStream;
struct ICharDeadEvent;
struct ItemInfo;
struct Item;
struct ItemViewInfo;

template <typename T>
struct NiTArray;

template <typename S, typename T>
struct NiTListBase;

struct SlideBar;
struct CDataReader;
struct NiAVObject;
struct NiRefObject;
struct NiTimeController;
struct NiNode;
struct IDirectMessenger;
struct NiPaletteRendererData;
struct NiGeometryGroup;
struct NiGeometryData;
struct NiGeometryBufferData;
struct IUnknownCustom;
struct NiVBSet;
struct NiVBChip;
struct NiTextureRendererData;
struct NiTexture;
struct NiPalette;
struct PgFrameWork;
struct NsEffect;
struct NiTexturingPropertyMap;
struct SLWCreateInfoItem;
struct Item;
struct cvftbl;

enum FontType {
	DEFAULT = 0x0,
	BOLD = 0x1,
	SMALL = 0x2,
	MENU = 0x3,
	DLGTEXT = 0x4,
	LARGE = 0x5,
	LARGEBOLD = 0x6,
	MAIN_MENU = 0x7,
	GTFONT = 0x8,
	TITLEBOLD = 0x9,
	NAMEPANEL3D = 0xA,
	GMCHAT = 0xB,
	TYPE_NUM = 0xC,
};

enum MsgBoxButType {
	MSGBOX_NONE = 0x0,
	MSGBOX_OK = 0x1,
	MSGBOX_OKCANCEL = 0x2,
	MSGBOX_CANCEL = 0x3,
	MSGBOX_PRIVATESOTRE_BUY_SELL = 0x4,
	MSGBOX_DENIALCLOSE = 0x5,
	MSGBOX_AGREEREFUSAL = 0x6,
	MSGBOX_BOOTH_SEARCHING = 0x7,
	MSGBOX_RANDOMOPTION = 0x8,
};

struct NiRefObject
{
	cvftbl* niRefObjectVtbl;
	unsigned int m_uiRefCount;
};

struct NiObject : NiRefObject {};

struct NiMatrix3
{
	float m_pEntry[3][3];
};

union Name5
{
	char n5_name[20];
	unsigned int n5_code[5];
};

struct NiPoint3
{
	float x;
	float y;
	float z;
};

template <typename T>
struct NiTAbstractPoolAllocator {
	char dummy[1];
};

template <typename T>
struct NiTPointerAllocator : NiTAbstractPoolAllocator<T> {};

struct NiBound
{
	NiPoint3 m_kCenter;
	float m_fRadius;
};

template <typename T>
struct NiTListItem
{
	NiTListItem<T>* m_pkNext;
	NiTListItem<T>* m_pkPrev;
	T m_element;
};

template <typename S, typename T>
struct NiTListBaseVtbl
{
	void* (__thiscall* __vecDelDtor)(NiTListBase<S, T*>* _this, unsigned int);
	NiTListItem<T*>* (__thiscall* NewItem)(NiTListBase<S, T*>* _this);
	void(__thiscall* DeleteItem)(NiTListBase<S, T*>* _this, NiTListItem<T*>*);
};

template <typename S, typename T>
struct NiTListBase_AntiBloatAllocator {
	unsigned int m_uiCount;
};

template <typename S, typename T>
struct NiTListBase
{
	NiTListBaseVtbl<S, T>* niTListBaseVtbl;
	NiTListItem<T>* m_pkHead;
	NiTListItem<T>* m_pkTail;
	NiTListBase_AntiBloatAllocator<S, T> m_kAllocator;
};

template <typename T>
struct NiTPointerList : NiTListBase<NiTPointerAllocator<unsigned int>, T*> {
};

template <typename T>
struct NiPointer {
	T* m_pObject;
};

template <typename T>
struct NiTArrayVtbl {
	void* (__thiscall* __vecDelDtor)(NiTArray<T*>* _this, unsigned int);
};

template <typename T>
struct NiTArray {
	NiTArrayVtbl<T>* niTArrayVtbl;
	NiPointer<T>* m_pBase;
	unsigned int m_uiMaxSize;
	unsigned int m_uiSize;
	unsigned int m_uiESize;
	unsigned int m_uiGrowBy;
};

struct NiTransform
{
	NiMatrix3 m_Rotate;
	NiPoint3 m_Translate;
	float m_fScale;
};

struct NiExtraData : NiObject
{
	char* m_pcName;
};

struct NiObjectNET : NiObject
{
	char* m_pcName;
	NiPointer<NiTimeController> m_spControllers;
	NiExtraData** m_ppkExtra;
	unsigned int m_uiExtraDataSize;
	unsigned int m_uiMaxSize;
};

struct NiProperty : NiObjectNET {};

/* 1576 */
#pragma pack(push, 4)
struct NiTimeController : NiObject {
	unsigned __int16 m_uFlags;
	float m_fFrequency;
	float m_fPhase;
	float m_fLoKeyTime;
	float m_fHiKeyTime;
	float m_fStartTime;
	float m_fLastTime;
	float m_fWeightedLastTime;
	float m_fScaledTime;
	bool m_bComputeScaledTime;
	NiObjectNET* m_pTarget;
	NiPointer<NiTimeController> m_spNext;
	bool m_bForceUpdate;
};
#pragma pack(pop)

struct NiCollisionObject : NiObject {
	NiAVObject* m_pkSceneObject;
};

struct NiAVObject : NiObjectNET {
	unsigned __int16 m_uFlags;
	NiNode* m_pkParent;
	NiBound m_kWorldBound;
	NiTransform m_kLocal;
	NiTransform m_kWorld;
	NiTPointerList<NiPointer<NiProperty>> m_kPropertyList;
	NiPointer<NiCollisionObject> m_spCollisionObject;
};

struct NiDynamicEffect : NiAVObject {
	bool m_bOn;
	int m_iIndex;
	unsigned int m_uiPushCount;
	unsigned int m_uiRevID;
	NiTPointerList<NiNode*> m_kAffectedNodeList;
	NiTPointerList<NiNode*> m_kUnaffectedNodeList;
};

struct NiNode : NiAVObject {
	NiTArray<NiPointer<NiAVObject>> m_kChildren;
	NiTPointerList<NiDynamicEffect*> m_kEffectList;
	NiBound m_kBound;
};

typedef void(__thiscall* IDirectMessenger_SetMsgHooker)(void* self, void*);
typedef void(__thiscall* IDirectMessenger_SendDirectMessage)(void*, int, void*, void*);
typedef void(__thiscall* IDirectMessenger_SetMessageNum)(void*, unsigned int);
typedef void(__thiscall* IDirectMessenger_DirectMessage)(void*, int, void*, void*);
typedef void(__thiscall* IDirectMessenger_DirectDispatchToChildren)(void*, int, void*, void*);
typedef void(__thiscall* IDirectMessenger_DirectDispatchToParent)(void*, int, void*, void*);

struct IDirectMessengerVtbl {
	IDirectMessenger_SetMsgHooker Org_SetMsgHooker;
	IDirectMessenger_SendDirectMessage Org_SendDirectMessage;
	IDirectMessenger_SetMessageNum Org_SetMessageNum;
	IDirectMessenger_DirectMessage Org_DirectMessage;
	IDirectMessenger_DirectDispatchToChildren Org_DirectDispatchToChildren;
	IDirectMessenger_DirectDispatchToParent Org_DirectDispatchToParent;
};

#pragma pack(push, 4)
struct IDirectMessenger
{
	IDirectMessengerVtbl* vtable;
	IDirectMessenger* m_pkMsgHooker;
	unsigned int m_uiMessageNum;
};
#pragma pack(pop)

union PgWindowWidth {
	int m_iWidth;
	unsigned int m_uiWidth;
};

union PgWindowHeight {
	int m_iHeight;
	unsigned int m_uiHeight;
};

struct NiColor
{
	float r;
	float g;
	float b;
};

struct NiMaterialProperty : NiProperty
{
	int m_iIndex;
	NiColor m_amb;
	NiColor m_diff;
	NiColor m_spec;
	NiColor m_emit;
	float m_fShine;
	float m_fAlpha;
	unsigned int m_uiRevID;
	void* m_pvRendererData;
};

struct PgWin : public NiNode, public IDirectMessenger {

	PgWindowWidth m_width;
	PgWindowHeight m_height;

	bool m_bEnable;
	bool m_bOpenCloseSoundEnable;
	bool m_bDroppable;

	unsigned int m_uiExtStyle;
	unsigned int m_uiDepth;

	NiPointer<NiMaterialProperty> m_spMaterialProp;
	bool m_bResigterFirstHit;

	PgWin* m_pkToolTipWin;
	PgWin* m_pkToolTipParentWin;

	char* m_pcToolTipWinText;
	bool m_bIsUpdate;
};

struct NiGeometry : NiAVObject {
	NiPointer<int> m_spPropertyState;
	NiPointer<int> m_spEffectState;
	NiPointer<int> m_spModelData;
	NiPointer<int> m_spSkinInstance;
	NiPointer<int> m_spShader;
};

struct NiTriBasedGeom : NiGeometry {};

struct NiTriShape : NiTriBasedGeom {};

struct NiScreenElements : NiTriShape {};

struct NiTexturePalette : NiRefObject {};

struct NiScreenElementsDataPolygon
{
	unsigned __int16 m_usNumVertices;
	unsigned __int16 m_usVOffset;
	unsigned __int16 m_usNumTriangles;
	unsigned __int16 m_usIOffset;
};

struct NiTriShapeDataSharedNormalArray
{
	unsigned __int16 m_usNumSharedNormals;
	unsigned __int16* m_pusSharedNormalIndexArray;
};

/* 1699 */
struct NiPoint2
{
	float x;
	float y;
};

/* 1698 */
struct NiColorA
{
	float r;
	float g;
	float b;
	float a;
};

struct NiObjectGroup
{
	unsigned int m_uiSize;
	void* m_pvBuffer;
	void* m_pvFree;
	unsigned int m_uiRefCount;
};

/* 1700 */
struct NiAdditionalGeometryDataNiAGDDataStream
{
	char m_uFlags;
	unsigned int m_uiType;
	unsigned int m_uiUnitSize;
	unsigned int m_uiTotalSize;
	unsigned int m_uiStride;
	unsigned int m_uiBlockIndex;
	unsigned int m_uiBlockOffset;
};

struct NiAdditionalGeometryDataNiAGDDataBlock
{
	unsigned int m_uiDataBlockSize;
	char* m_pucDataBlock;
};

struct NiAdditionalGeometryData : NiObject
{
	unsigned int m_uiRevID;
	unsigned __int16 m_usVertexCount;
	unsigned int m_uiDataStreamCount;
	NiAdditionalGeometryDataNiAGDDataStream* m_pkDataStreamEntries;
	NiTArray<NiAdditionalGeometryDataNiAGDDataBlock*> m_aDataBlocks;
};

struct NiGeometryGroupVtbl
{
	void(__thiscall* Purge)(NiGeometryGroup* _this);
	void(__thiscall* AddObject)(NiGeometryGroup* _this, void*);
	void(__thiscall* AddObject2)(NiGeometryGroup* _this, NiGeometryData*, void*, void*);
	void(__thiscall* RemoveObject)(NiGeometryGroup* _this, void*);
	void(__thiscall* RemoveObject2)(NiGeometryGroup* _this, void*);
	void(__thiscall* RemoveObject3)(NiGeometryGroup* _this, NiGeometryData*);
	void* (__thiscall* CreateChip)(NiGeometryGroup* _this, NiGeometryBufferData*, unsigned int);
	void(__thiscall* ReleaseChip)(NiGeometryGroup* _this, NiGeometryBufferData*, unsigned int);
	bool(__thiscall* IsDynamic)(NiGeometryGroup* _this);
	void* (__thiscall* __vecDelDtor)(NiGeometryGroup* _this, unsigned int);
};

struct IUnknownVtbl
{
	HRESULT(__stdcall* QueryInterface)(IUnknownCustom*, _GUID* const, void**);
	unsigned int(__stdcall* AddRef)(IUnknownCustom*);
	unsigned int(__stdcall* Release)(IUnknownCustom*);
};

struct IUnknownCustom
{
	IUnknownVtbl* lpVtbl;
};

/* 1760 */
struct IDirect3DDevice9 : IUnknownCustom {};

struct NiGeometryGroup
{
	NiGeometryGroupVtbl* vfptr;
	unsigned int m_uiRefCount;
	IDirect3DDevice9* m_pkD3DDevice;
};

struct IDirect3DVertexDeclaration9 : IUnknownCustom {};

struct IDirect3DResource9 : IUnknownCustom {};

struct IDirect3DIndexBuffer9 : IDirect3DResource9 {};

struct IDirect3DVertexBuffer9 : IDirect3DResource9 {};

struct NiVBBlock
{
	NiVBSet* m_pkSet;
	unsigned int m_uiIndex;
	IDirect3DVertexBuffer9* m_pkVB;
	unsigned int m_uiSize;
	unsigned int m_uiFVF;
	unsigned int m_uiFlags;
	unsigned int m_uiUsage;
	int m_ePool;
	unsigned int m_uiCurrOffset;
	unsigned int m_uiFreeBytes;
	unsigned int m_uiTotalFreeBytes;
	NiTArray<NiVBChip*> m_apkChips;
	NiVBBlock* m_pkNextBlock;
	NiVBBlock* m_pkPrevBlock;
};

struct NiVBSet
{
	unsigned int m_uiIndex;
	unsigned int m_uiFVF;
	unsigned int m_uiFlags;
	unsigned int m_uiBlockSize;
	IDirect3DDevice9* m_pkD3DDevice;
	unsigned int m_uiUsage;
	int m_ePool;
	NiTArray<NiVBBlock*> m_apkBlocks;
	NiVBBlock* m_pkBlockList;
	unsigned int m_uiFreeSpaceThreshold;
};

struct NiVBDynamicSet
{
	unsigned int m_uiIndex;
	unsigned int m_uiFVF;
	unsigned int m_uiBlockSize;
	IDirect3DDevice9* m_pkD3DDevice;
	IDirect3DVertexBuffer9* m_pkVB;
	unsigned int m_uiCurrOffset;
};

union NiBlockData {
	NiVBBlock* m_pkBlock;
	NiVBDynamicSet* m_pkDynamicSet;
};

struct NiVBChip
{
	unsigned int m_uiIndex;
	NiBlockData m_blockData;
	IDirect3DVertexBuffer9* m_pkVB;
	unsigned int m_uiOffset;
	unsigned int m_uiLockFlags;
	unsigned int m_uiSize;
	NiVBChip* m_pkNextChip;
	NiVBChip* m_pkPrevChip;
};

struct NiGeometryBufferData
{
	unsigned int m_uiFlags;
	NiGeometryGroup* m_pkGeometryGroup;
	unsigned int m_uiFVF;
	IDirect3DVertexDeclaration9* m_hDeclaration;
	bool m_bSoftwareVP;
	unsigned int m_uiVertCount;
	unsigned int m_uiMaxVertCount;
	unsigned int m_uiStreamCount;
	unsigned int* m_puiVertexStride;
	NiVBChip** m_ppkVBChip;
	unsigned int m_uiIndexCount;
	unsigned int m_uiIBSize;
	IDirect3DIndexBuffer9* m_pkIB;
	unsigned int m_uiBaseVertexIndex;
	int m_eType;
	unsigned int m_uiTriCount;
	unsigned int m_uiMaxTriCount;
	unsigned int m_uiNumArrays;
	const unsigned __int16* m_pusArrayLengths;
	const unsigned __int16* m_pusIndexArray;
};

struct NiGeometryData : NiObject
{
	NiObjectGroup* m_pkGroup;
	unsigned __int16 m_usVertices;
	unsigned __int16 m_usID;
	NiBound m_kBound;
	NiPoint3* m_pkVertex;
	NiPoint3* m_pkNormal;
	NiColorA* m_pkColor;
	NiPoint2* m_pkTexture;
	unsigned __int16 m_usDataFlags;
	unsigned __int16 m_usDirtyFlags;
	char m_ucKeepFlags;
	char m_ucCompressFlags;
	NiPointer<NiAdditionalGeometryData> m_spAdditionalGeomData;
	NiGeometryBufferData* m_pkBuffData;
};

/* 2321 */
struct NiTriShapeDataSNAMemBlock
{
	unsigned __int16* m_pusBlock;
	unsigned __int16* m_pusFreeBlock;
	unsigned int m_uiBlockSize;
	unsigned int m_uiFreeBlockSize;
	NiTriShapeDataSNAMemBlock* m_pkNext;
};

struct NiTriBasedGeomData : NiGeometryData
{
	unsigned __int16 m_usTriangles;
};

/* 2322 */
struct NiTriShapeData : NiTriBasedGeomData {

	unsigned int m_uiTriListLength;
	unsigned __int16* m_pusTriList;
	NiTriShapeDataSharedNormalArray* m_pkSharedNormals;
	unsigned __int16 m_usSharedNormalsArraySize;
	NiTriShapeDataSNAMemBlock* m_pkSNAMemoryBlocks;
};

/* 2324 */
struct NiScreenElementsData : NiTriShapeData {

	NiScreenElementsDataPolygon* m_akPolygon;
	unsigned __int16* m_ausPIndexer;
	unsigned __int16 m_usMaxPQuantity;
	unsigned __int16 m_usPGrowBy;
	unsigned __int16 m_usPQuantity;
	unsigned __int16 m_usMaxVQuantity;
	unsigned __int16 m_usVGrowBy;
	unsigned __int16 m_usMaxIQuantity;
	unsigned __int16 m_usIGrowBy;
	bool m_bBoundNeedsUpdate;
};

struct PgSprDataPgHitTester : NiRefObject
{
	char* m_pucBuff;
	unsigned int m_uiXPos;
	unsigned int m_uiYPos;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiChangedWidth;
	unsigned int m_uiChangedHeight;
	NiPoint2 m_akUVs[4];
	PgSprDataPgHitTester* m_pkNext;
};

template <typename T>
struct NiRect
{
	T m_left;
	T m_right;
	T m_top;
	T m_bottom;
};

/* 2529 */
struct NiFrustum
{
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;
	float m_fNear;
	float m_fFar;
	bool m_bOrtho;
};

/* 2531 */
struct NiCamera : NiAVObject
{
	float m_aafWorldToCam[4][4];
	NiFrustum m_kViewFrustum;
	float m_fMinNearPlaneDist;
	float m_fMaxFarNearRatio;
	NiRect<float> m_kPort;
	float m_fLODAdjust;
};

struct NiAccumulator : NiObject
{
	NiCamera* m_pkCamera;
};

struct NiTextureAccumulator : NiAccumulator
{
	std::vector<NiGeometry*, std::allocator<NiGeometry*>> m_vecItem;
};

struct NiPixelFormatNiComponentSpec
{
	int m_eComponent;
	int m_eRepresentation;
	char m_ucBitsPerComponent;
	bool m_bSigned;
};

struct NiPixelFormat
{
	char m_uFlags;
	char m_ucBitsPerPixel;
	int m_eFormat;
	int m_eTiling;
	unsigned int m_uiRendererHint;
	unsigned int m_uiExtraData;
	NiPixelFormatNiComponentSpec m_akComponents[4];
};

/* 1681 */
struct NiTextureRendererDataVtbl
{
	void* (__thiscall* __vecDelDtor)(NiTextureRendererData* _this, unsigned int);
	unsigned int(__thiscall* GetWidth)(NiTextureRendererData* _this);
	unsigned int(__thiscall* GetHeight)(NiTextureRendererData* _this);
	NiPixelFormat* (__thiscall* GetPixelFormat)(NiTextureRendererData* _this);
};

/* 1679 */
struct NiTextureFormatPrefs
{
	int m_ePixelLayout;
	int m_eAlphaFmt;
	int m_eMipMapped;
};

struct NiTextureRendererData
{
	NiTextureRendererDataVtbl* vfptr;
	NiTexture* m_pkTexture;
};

struct NiTexture : NiObjectNET
{
	NiTextureFormatPrefs m_kFormatPrefs;
	NiTextureRendererData* m_pkRendererData;
	NiTexture* m_pkPrev;
	NiTexture* m_pkNext;
};

struct NiPalettePaletteEntry
{
	char m_ucRed;
	char m_ucGreen;
	char m_ucBlue;
	char m_ucAlpha;
};

struct NiPaletteRendererDataVtbl
{
	void* (__thiscall* __vecDelDtor)(NiPaletteRendererData* _this, unsigned int);
};

/* 1656 */
struct NiPaletteRendererData
{
	NiPaletteRendererDataVtbl* vfptr;
	NiPalette* m_pkPalette;
};

struct NiPalette : NiObject
{
	bool m_bAlpha;
	unsigned int m_uiEntries;
	unsigned int m_uiRevID;
	NiPalettePaletteEntry* m_pkPalette;
	NiPaletteRendererData* m_pkRendererData;
	NiPalette* m_pkPrev;
	NiPalette* m_pkNext;
};

/* 1660 */
struct NiPixelData : NiObject
{
	NiPixelFormat m_kPixelFormat;
	NiPointer<NiPalette> m_spPalette;
	char* m_pucPixels;
	unsigned int* m_puiWidth;
	unsigned int* m_puiHeight;
	unsigned int* m_puiOffsetInBytes;
	unsigned int m_uiMipmapLevels;
	unsigned int m_uiPixelStride;
	unsigned int m_uiRevID;
	unsigned int m_uiFaces;
};

/* 2079 */
struct NiSourceTexture : NiTexture
{
	char* m_pcFilename;
	char* m_pcPlatformFilename;
	NiPointer<NiPixelData> m_spSrcPixelData;
	bool m_bStatic;
	bool m_bLoadDirectToRendererHint;
};

/* 2055 */
struct NiAlphaProperty : NiProperty
{
	unsigned __int16 m_uFlags;
	char m_ucAlphaTestRef;
};

struct PgSprData : NiRefObject {
	NiTArray<NiPointer<NiScreenElementsData>> m_akGeomData;
	NiTArray<NiPointer<PgSprDataPgHitTester>> m_akHitTester;
	NiPointer<NiSourceTexture> m_spTexture;
	NiTArray<NiPointer<NiAlphaProperty>> m_akAlphaPropertyData;
};

struct PgSpr : NiRefObject {
	NiPointer<int> m_spSprData;
	NiTArray<NiPointer<NiScreenElements>> m_akGeom;
};

struct PgWinSpr : PgWin {
	NiPointer<PgSpr> m_spSpr;
	unsigned int m_uiSelectSprIndex;
};

/*  103 */
enum PgWinButType
{
	DOWN = 0x0,
	UP = 0x1,
};

enum EditWinType
{
	NORMAL = 0x50000000,
	PASSWD = 0x50000020,
	NUMBER = 0x50002000,
	MULTILINE = 0x50001004,
};

typedef EditWinType PgWinButButShow;

/* 2412 */
struct PgWinBut : PgWinSpr
{
	unsigned int m_uiCmdMsg;
	unsigned int m_uiCmdMsgParam;
	PgWinButType m_eType;
	PgWinButButShow m_eButShow;
	bool m_bHadBeenPushed;
	unsigned int m_uiButNum;
	bool m_bEnableClickSound;
	bool m_bClickCheck;
};

struct PgWinFrame : PgWinSpr {

	PgWinFrame();
	~PgWinFrame();

	PgFrameWork* m_pkFrameWork;
	int m_iDragOffX;
	int m_iDragOffY;
	bool m_bMovable;
	bool m_bIsDuringMove;
	int m_iOldDragOffX;
	int m_iOldDragOffY;
	int m_iVXPos;
	int m_iVYPos;
	bool m_bLeftLike;
	bool m_bTopLike;
	bool m_bRightLike;
	bool m_bBottomLike;
	bool m_bLeftAttached;
	bool m_bTopAttached;
	bool m_bRightAttached;
	bool m_bBottomAttached;
	float m_fInitXPos;
	float m_fInitYPos;

};

/* 1640 */
struct NsEffectVtbl
{
	void* (__thiscall* __vecDelDtor)(NsEffect* _this, unsigned int);
};

/* 1639 */
struct NsEffect
{
	NsEffectVtbl* vfptr;
	NiAVObject* m_pEffectObject;
	float m_fMinTime;
	float m_fMaxTime;
	float m_uiControllerCount;
	std::vector<NiTimeController*, std::allocator<NiTimeController*>> m_vectorTimeController;
};

/* 2047 */
struct CNSTimer
{
	float m_fStartTime;
	float m_fObjectTime;
	float m_fElapsedTime;
};

/* 2416 */
struct CNSTimer_MarkCheck {
	CNSTimer m_NSTimer;
	float m_fMarkTime;
	int m_eTimeStateCur;
	int m_eTimeStaeKillCondition;
};

/* 2417 */
struct SpEffect
{
	NiPointer<NiNode> m_spEffect;
	CNSTimer_MarkCheck m_kMarkCheck;
	NsEffect m_kEffect;
	bool m_bLive;
	bool m_bLoop;
	bool m_bClamp;
};

/*  690 */
enum SkillEffectType
{
	SE_PHYSICDAMAGE = 0x0,
	SE_MAGICDAMAGE = 0x1,
	SE_FIREDAMAGE = 0x2,
	SE_COLDDAMAGE = 0x3,
	SE_LIGHTNINGDAMAGE = 0x4,
	SE_HEALING = 0x5,
	SE_TELEPORT = 0x6,
	SE_REVIVAL = 0x7,
	SE_CURE = 0x8,
	SE_DISPEL = 0x9,
	SE_WHOLEHEAL = 0xA,
	SE_DEFAULT = 0xB,
	SE_VOLLEY = 0xC,
	SE_SUMMON = 0xD,
	SE_METAMORPHOSIS = 0xE,
	SE_PYRATEDAMAGE = 0xF,
	MAX_SKILLEFFECTTYPE = 0x10,
};

/*  234 */
enum WeaponDemandType
{
	DT_ONEHAND = 0x0,
	DT_TWOHAND = 0x1,
	DT_ALL = 0x2,
	DT_WEAPON = 0x3,
	DT_HAMMER = 0x4,
	DT_MACE = 0x5,
	DT_NONE = 0x6,
	DT_SHIELD = 0x7,
	DT_BOW = 0x8,
	DT_CBOW = 0x9,
	DT_STAFF = 0xA,
	DT_WAND = 0xB,
	DT_CLAW = 0xC,
	DT_DSWORD = 0xD,
	DT_BLADE = 0xE,
	MAX_WEAPONDEMANDTYPE = 0xF,
};

/*  479 */
enum TargetType
{
	TARGET_ENEMY = 0x0,
	TARGET_ME = 0x1,
	TARGET_PARTY = 0x2,
	TARGET_FRIEND = 0x3,
	TARGET_SPOT = 0x4,
	TARGET_ALL = 0x5,
	TARGET_GROUP = 0x6,
	TARGET_ENEMYUSER = 0x7,
	TARGET_EVERY = 0x8,
	TARGET_ENEMYGUILD = 0x9,
	TARGET_MYGUILD = 0xA,
	TARGET_MYNPC = 0xB,
	TARGET_MYRAID = 0xC,
	TARGET_BOX = 0xD,
	TARGET_THISACTION = 0xE,
	TARGET_ATTACKME = 0xF,
	TARGET_DAMAGEBYME = 0x10,
	TARGET_THISSKILL = 0x11,
	TARGET_NONE = 0x12,
	MAX_TARGETTYPE = 0x13,
};

/*  860 */
enum TargetState
{
	TS_LIVE = 0x0,
	TS_CORPSE = 0x1,
	TS_NONE = 0x2,
	MAX_TARGETSTATE = 0x3,
};


/*  409 */
enum UseClassType
{
	UCT_NONE = 0x0,
	UCT_ALL = 0x1,
	UCT_FIGHTER_ALL = 0x2,
	UCT_CLEVERFIGHTER_AND_OVER = 0x3,
	UCT_WARRIOR_AND_OVER = 0x4,
	UCT_WARRIOR_OVER = 0x5,
	UCT_GLADIATOR_ONLY = 0x6,
	UCT_KNIGHT_ONLY = 0x7,
	UCT_CLERIC_ALL = 0x8,
	UCT_HIGHCLERIC_AND_OVER = 0x9,
	UCT_PALADIN_AND_OVER = 0xA,
	UCT_GUARDIAN_ONLY = 0xB,
	UCT_HOLYKNIGHT_ONLY = 0xC,
	UCT_PALADIN_OVER = 0xD,
	UCT_ARCHER_ALL = 0xE,
	UCT_HAWKARCHER_AND_OVER = 0xF,
	UCT_SCOUT_AND_OVER = 0x10,
	UCT_RANGER_ONLY = 0x11,
	UCT_SHARPSHOOTER_ONLY = 0x12,
	UCT_SCOUT_OVER = 0x13,
	UCT_MAGE_ALL = 0x14,
	UCT_WIZMAGE_AND_OVER = 0x15,
	UCT_ENCHANTER_AND_OVER = 0x16,
	UCT_WIZARD_ONLY = 0x17,
	UCT_WARLOCK_ONLY = 0x18,
	UCT_ENCHANTER_OVER = 0x19,
	UCT_SENTINEL_EXCLUDE = 0x1A,
	UCT_JOKER_ALL = 0x1B,
	UCT_CHASER_AND_OVER = 0x1C,
	UCT_CRUEL_AND_OVER = 0x1D,
	UCT_ASSASSIN_ONLY = 0x1E,
	UCT_CLOSER_ONLY = 0x1F,
	UCT_CRUEL_OVER = 0x20,
	UCT_SENTINEL_ALL = 0x21,
	UCT_SAVIOR_ONLY = 0x22,
	UCT_DEEPER_SKILL = 0x23,
	UCT_SHIELD = 0x24,
	UCT_CLASS_CHANGE = 0x25,
	UCT_SHIELD_NOT_GLA = 0x26,
	MAX_USECLASSTYPE = 0x27,
};

enum SkillSpecial
{
	SS_NONE = 0x0,
	SS_HEALAMOUNT = 0x1,
	SS_CURE = 0x2,
	SS_DISPEL = 0x3,
	SS_TELEPORT = 0x4,
	SS_WHOLEHEALAMOUNT = 0x5,
	SS_MANABURN = 0x6,
	SS_UNDEADTODMG = 0x7,
	SS_DISPELALL = 0x8,
	SS_DISPELONE = 0x9,
	SS_THHPUP = 0xA,
	SS_DIEHPUP = 0xB,
	SS_REVIVAL = 0xC,
	SS_MAGICFIELD_TICK = 0xD,
	SS_MAGICFIELD_KEEP = 0xE,
	SS_STEALENCHANT = 0xF,
	SS_HPCONVERTSP = 0x10,
	SS_HPUPRATE = 0x11,
	SS_FLYDURINGCAST = 0x12,
	SS_SILVERWING = 0x13,
	SS_DISPELDEBUFF = 0x14,
	SS_DISPELCURSE = 0x15,
	SS_DISPELPOISON = 0x16,
	SS_DISPELDISEASE = 0x17,
	SS_WHOLEAGGRORATE = 0x18,
	SS_WARPING = 0x19,
	SS_DISPELRANDOM = 0x1A,
	SS_DETECT = 0x1B,
	SS_WHOLEAGGRORANGE = 0x1C,
	SS_HIDE = 0x1D,
	SS_Silience = 0x1E,
	SS_MESMERIZE = 0x1F,
	SS_SUMMON = 0x20,
	SS_METAMORPHOSIS = 0x21,
	SS_CROSSCOUNTER = 0x22,
	SS_DISPELDEEPER = 0x23,
	SS_DASH = 0x24,
	SS_DISPELBUFF = 0x25,
	SS_DASH2 = 0x26,
	SS_HPRATE = 0x27,
	SS_CURSETIMEADD = 0x28,
	SS_FIRETIMEADD = 0x29,
	SS_HOLDME = 0x2A,
	SS_JWALK = 0x2B,
	SS_POSIONTIMEADD = 0x2C,
	SS_SHOOTME = 0x2D,
	SS_DMGCOLLTIMEDOWN = 0x2E,
	SS_AREATYPE = 0x2F,
	SS_BOMBDISPELALL = 0x30,
	SS_MAGICFIELDPARTY = 0x31,
	SS_HEALFRIENDRATE = 0x32,
	SS_SETABSTATEFRIEND = 0x33,
	SS_RANDOMTARGETNUMBER = 0x34,
	SS_NEXTTARGETAREA = 0x35,
	SS_DMGDOWNRATE = 0x36,
	SS_MAXDMGDOWNRATE = 0x37,
	SS_SHOTSPEED = 0x38,
	SS_TARGETHPDOWNDMGUPRATE = 0x39,
	SS_JUMP = 0x3A,
	SS_SETABSTATEME = 0x3B,
	SS_NOTTARGET = 0x3C,
	SS_ABKEEPTIME = 0x3D,
	SS_TOPAGGRONO = 0x3E,
	SS_RANDOMTARGET = 0x3F,
	SS_MAGICFIELD_DELAY_START_TIME = 0x40,
	SS_BMP_MAGICFIELD_ROTATIONSPEED_RIGHT = 0x41,
	SS_DISPELABSTATE = 0x42,
	SS_MOVE_CHR = 0x43,
	SS_HIDE_CHR_START = 0x44,
	SS_HIDE_CHR_END = 0x45,
	SS_RECALL = 0x46,
	SS_DMGSHARE = 0x47,
	SS_SUCKHP = 0x48,
	SS_RANDOMTARGETSPOT = 0x49,
	MAX_SKILLSPECIAL = 0x4A,
};

/* 4039 */
#pragma pack(push, 1)

struct ActiveSkillInfo
{
	unsigned __int16 ID;
	char InxName[32];
	char Name[64];
	unsigned int Grade;
	unsigned int Step;
	unsigned int MaxStep;
	WeaponDemandType DemandType;
	char DemandSk[32];
	unsigned __int16 UseItem;
	unsigned int ItemNumber;
	unsigned int ItemOption;
	unsigned __int16 DemandItem1;
	unsigned __int16 DemandItem2;
	unsigned int SP;
	unsigned int SPRate;
	unsigned int HP;
	unsigned int HPRate;
	unsigned int LP;
	unsigned int Range;
	TargetType First;
	TargetType Last;
	char IsMovingSkill;
	unsigned __int16 UsableDegree;
	unsigned __int16 DirectionRotate;
	unsigned __int16 SkillDegree;
	TargetState SkillTargetState;
	unsigned int CastTime;
	unsigned int DlyTime;
	unsigned int DlyGroupNum;
	unsigned int DlyTimeGroup;
	unsigned int MinWC;
	unsigned int MinWCRate;
	unsigned int MaxWC;
	unsigned int MaxWCRate;
	unsigned int MinMA;
	unsigned int MinMARate;
	unsigned int MaxMA;
	unsigned int MaxMARate;
	unsigned int AC;
	unsigned int MR;
	unsigned int Area;
	unsigned int TargetNumber;
	UseClassType UseClass;
	char StaNameA[32];
	unsigned int StaStrengthA;
	unsigned int StaSucRateA;
	char StaNameB[32];
	unsigned int StaStrengthB;
	unsigned int StaSucRateB;
	char StaNameC[32];
	unsigned int StaStrengthC;
	unsigned int StaSucRateC;
	char StaNameD[32];
	unsigned int StaStrengthD;
	unsigned int StaSucRateD;
	unsigned int nIMPT[4];
	unsigned int nT0[5];
	unsigned int nT1[5];
	unsigned int nT2[5];
	unsigned int nT3[5];
	SkillEffectType EffectType;
	SkillSpecial SpecialIndexA;
	unsigned int SpecialValueA;
	SkillSpecial SpecialIndexB;
	unsigned int SpecialValueB;
	SkillSpecial SpecialIndexC;
	unsigned int SpecialValueC;
	SkillSpecial SpecialIndexD;
	unsigned int SpecialValueD;
	SkillSpecial SpecialIndexE;
	unsigned int SpecialValueE;
	char SkillClassifierA[32];
	char SkillClassifierB[32];
	char SkillClassifierC[32];
	char CannotInside;
	char DemandSoul;
	unsigned __int16 HitID;
};
#pragma pack(pop)

struct ActSkillInfoTab {

	uint32_t pad1[4];

	unsigned int size;

	uint32_t pad2[11];

	ActiveSkillInfo** skills;

};

/* 2414 */
struct ClockShadowWin : PgWin {
	NiPointer<NiTriShape> m_spTriShape;
	bool m_bStart;
	float m_fStartTime;
	float m_fRotateTime;
	bool b_show;
	unsigned __int16 m_kSkillID;
};

struct NiTexturingPropertyMapVtbl {
	void* (__thiscall* __vecDelDtor)(NiTexturingPropertyMap* _this, unsigned int);
	void(__thiscall* LoadBinary)(NiTexturingPropertyMap* _this, void*); //NiStream
	void(__thiscall* SaveBinary)(NiTexturingPropertyMap* _this, void*); //NiStream
};

struct NiTextureTransform {
	NiPoint2 m_kTranslate;
	float m_fRotate;
	NiPoint2 m_kScale;
	NiPoint2 m_kCenter;
	bool m_bMatrixDirty;
	NiMatrix3 m_kMatrix;
	int m_eMethod;
};

struct NiTexturingPropertyMap {
	NiTexturingPropertyMapVtbl* vfptr;
	NiPointer<NiTexture> m_spTexture;
	int m_eClamp;
	int m_eFilter;
	unsigned int m_uiTexCoord;
	NiTextureTransform* m_pkTextureTransform;
};

struct NiTexturingPropertyShaderMap : NiTexturingPropertyMap {
	unsigned int m_uiID;
};

/* 1743 */
struct NiTexturingProperty : NiProperty {

	int m_eApply;
	bool m_bMultiTexture;
	NiTArray<NiTexturingPropertyMap*> m_kMaps;
	unsigned int m_uiDecals;
	NiTArray<NiTexturingPropertyShaderMap*>* m_pkShaderMaps;
};

struct PgWinLRBut : PgWinBut {
	unsigned int m_uiRCmdMsg;
	unsigned int m_uiRCmdMsgParam;
};

/* 2418 */
struct IconWin : PgWinLRBut {

	NiPointer<NiScreenElements> m_spGeom;
	NiPointer<NiTexturingProperty> m_spTexProp;
	unsigned int m_uiIconIndex;
	NiPointer<NiAVObject> m_spOverGeomForRefCount;
	NiPointer<NiAVObject> m_spClickGeomForRefCount;
	NiPointer<NiAVObject> m_spOverGeom;
	NiPointer<NiAVObject> m_spClickGeom;
	bool m_bShowFocus;
	unsigned __int16 m_coolTimeID;
	unsigned __int16 m_CoolGroupItemActionID;
	NiPointer<ClockShadowWin> m_spClockShadowWin;
	SpEffect* m_pkCoolTimeOverEffect;
	bool m_bClockShadowWinActive;
	bool m_bCoolTimeCheckNeeded;
};

template <typename T>
struct PgTQueue
{
	T* m_pBase;
	unsigned int m_uiAlloced;
	unsigned int m_uiHead;
	unsigned int m_uiTail;
};

/* 3524 */
template <typename T>
struct PgTList : NiTPointerList<T> {
};

/* 2341 */
struct PgMsgFrame
{
	unsigned int m_uiDumy[2];
	unsigned int m_uiFrameMsg;
	unsigned int m_uiFrameWParam;
	unsigned int m_uiFramelParam;
};

#pragma pack(push, 4)
struct PgFrameWork : IDirectMessenger
{
	PgTQueue<PgMsgFrame> m_kMsgQ;
	void* m_BackFrameID;
	bool m_bInit;
};
#pragma pack(pop)

struct StrBuffer
{
	char* m_pcStr;
	int m_iBufferSize;
	int m_iStrLen;
};

struct SpScreenText : NiNode
{
	NiPointer<int> m_spFont;
	tagRECT m_kRect;
	void* m_pkFontRenderPass;
	unsigned int m_dwMaxPass;
	unsigned int m_dwShadowOffset;
	NiColorA m_kColor;
	int m_iAlignOption;
	bool m_bAutoWordWrap;
	bool m_bTextCmdOn;
	bool m_bClipEnable;
	StrBuffer m_kString;
	bool m_bInvalidate;
	int m_iVerticalGap;
};

/* 2408 */
struct PgTextGeometry : SpScreenText {
	unsigned int m_uiDrawFormat;
	NiPointer<int> m_spPgFont;
	unsigned int m_uiTextWidth;
	unsigned int m_uiTextHeight;
	bool m_bResetTextAfterDraw;
	int m_nTextIndex;
};

/* 3001 */
struct D3DXCOLOR
{
	float r;
	float g;
	float b;
	float a;
};

struct PgWinText : PgWin {
	NiPointer<PgTextGeometry> m_spTextGeom;
};

enum SLWCreateInfoSprDataType
{
	SPRITE = 0x0,
	BUTTON = 0x1,
	CHECKBUTTON = 0x2,
	ITEMICON = 0x3,
	TEXT = 0x4,
};


template <typename T>
struct std_Allocator_base
{
	char dummy[1];
};

struct boostdetailshared_count
{
	void* pi_;
};

/* 158 */
struct std_Container_base0
{
	char dummy[1];
};

template <typename T>
struct boostshared_ptr
{
	T* px;
	boostdetailshared_count pn;
};

/* 2477 */
struct DecoPlaneColor {
	NiPointer<NiScreenElements> m_spDecoPlane;
	NiPointer<NiScreenElements> m_spSubPlane;
	bool m_bShowDeco;
	bool m_bShowSub;
};

struct DecoPlaneTex {
	NiPointer<NiScreenElements> m_spDecoPlane;
	NiPointer<NiTexturingProperty> m_spDecoTexProp;
	unsigned int m_uiDecoImageIndex;
	bool m_bShowDeco;
};

struct ItemIcon : IconWin {

	PgWinText* m_pkLotText;
	NiPointer<Item> m_spItem;
	bool m_bShowLotText;
	bool m_bShowSubIcon;
	unsigned int m_uiSubIconIndex;
	NiPointer<NiScreenElements> m_spSubImagePlane;
	NiPointer<NiTexturingProperty> m_spSubImageTexProp;
	DecoPlaneColor m_kGradeDeco;
	DecoPlaneTex m_kTermDeco;
	bool m_bgray;
	NiPointer<NiScreenElements> m_spBackPlane;
	NiPointer<NiScreenElements> m_spTopPlane;
	bool m_bInputProcess;
};

struct ItemInfoWinsNameContentsParameter {
	ItemInfo* pkInfo;
	ItemViewInfo* pkViewInfo;
	int iItemUpgrade;
	Item* pkItem;
	bool bNPCShop;
};

struct InvWin : ItemIcon {

	unsigned int m_uiInvIndex;
	unsigned int m_uiInvType;
	bool m_bActive;
	bool m_bLock;
	NiPointer<NiScreenElements> m_spSubImagePlane;
	NiPointer<NiTexturingProperty> m_spSubImageTexProp;
};

struct FrameBoxWinSizeDragBarState
{
	bool bLeft;
	bool bRight;
	bool bTop;
	bool bBottom;
};

struct FrameBoxWin : PgWinFrame {

	unsigned int m_uiOrgWidth;
	unsigned int m_uiOrgHeight;
	unsigned int m_uiEdgeHeight;
	unsigned int m_uiEdgeWidth;
	NiScreenElements* m_pkGeom;
	bool m_bSizeDraggable;
	bool m_bIsDuringSizeDrag;
	int m_iSizeDragOrgX;
	int m_iSizeDragOrgY;
	int m_iSizeDragOrgLeft;
	int m_iSizeDragOrgTop;
	int m_iSizeDragOrgWidth;
	int m_iSizeDragOrgHeight;
	int m_iSizeDragMinWidth;
	int m_iSizeDragMaxWidth;
	int m_iSizeDragMinHeight;
	int m_iSizeDragMaxHeight;
	FrameBoxWinSizeDragBarState m_kSizeDragBarState;
	bool m_bLock;
};

struct FontBucket {
	char w;
	char h;
	unsigned __int16 left;
	unsigned __int16 top;
	char byTextureIndex;
	float tx1;
	float ty1;
	float tx2;
	float ty2;
};

template<typename S>
struct DFALL {
	char dummy[1];
};

union $89DDC50BB909F7422C06791150CFDA06 {
	DFALL<int> baseclass_0;
	unsigned int m_uiCount;
};

/*  768 */
enum UpgradeFactor
{
	UPG_AC = 0x0,
	UPG_WC = 0x1,
	UPG_SHIELDAC = 0x2,
	UPG_MA = 0x3,
	UPG_MR = 0x4,
	UPG_STAT = 0x5,
	UPG_WC_MA = 0x6,
	UPG_AC_MR = 0x7,
	UPG_CRIT = 0x8,
	MAX_UPGRADEFACTOR = 0x9,
};

#pragma pack(push, 1)
struct UpGradeInfo
{
	unsigned __int16 ID;
	char InxName[32];
	UpgradeFactor UpFactor;
	unsigned __int16 Updata[12];
};
#pragma pack(pop)

struct NiTMapBaseDummy {
	$89DDC50BB909F7422C06791150CFDA06 ___u0;
};

template<typename S, typename T, typename U>
struct NiTMapBase {
	void* vfptr;
	unsigned int m_uiHashSize;
	void** m_ppkHashTable;
	NiTMapBaseDummy m_kAllocator;
};

template<typename S, typename T>
struct NiTMap : NiTMapBase<DFALL<T>, S, T> {};

template<typename S, typename T>
struct NiTPointerListBase : NiTListBase<S, T> {};

template<typename S>
struct NiTList : NiTPointerListBase<DFALL<S>, S> {};

struct CBucketBlock {
	FontBucket* m_pkBlock;
	unsigned int m_dwSize;
	unsigned int m_dwUsedCount;
};

struct CBucketPool {
	unsigned int m_dwBlockUnit;
	NiTList<CBucketBlock*> m_kBlockList;
	CBucketBlock* m_pkCurrBlock;
};

struct CBucketBuffer {
	unsigned int m_dwFontSize;
	unsigned int m_dwMaxTexture;
	unsigned int m_dwTextureSize;
	unsigned int m_dwLoadXPos;
	unsigned int m_dwLoadYPos;
	unsigned int m_dwCurrTextureIndex;
	unsigned int m_dwLoadedFontCount;
	NiPointer<NiSourceTexture> m_aspkTextures[32];
	NiTMap<unsigned short, FontBucket*> m_kFontHash;
	CBucketPool* m_pkBucketPool;
};

struct FontRenderStuff {
	HDC__* hDC;
	HBITMAP__* hBitmap;
	HBITMAP__* hOldBitmap;
	unsigned int* pdwDCRenderBuffer;
	unsigned int dwBufferSize;
};

struct CSpFont : NiRefObject {
	CBucketBuffer m_kBucketBuffer;
	HFONT__* m_hFont;
	HFONT__* m_hOldFont;
	FontRenderStuff m_kFontRenderStuff;
	unsigned int m_dwSpacing;
	float m_fTextScale;
	unsigned int m_dwFontSize;
	unsigned int m_dwFontSizeInPixel;
	unsigned int m_dwTextureSize;
	unsigned int m_dwMaxTexture;
	NiTList<SpScreenText*> m_kRegisteredText;
	unsigned int m_dwOutlineOffset;
	char m_acColorToken[128];
};

struct PgFont : CSpFont {
	unsigned int m_uiDefHeight;
};

struct ToolTipWin : FrameBoxWin {
	PgWinText* m_apkTextWin[20];
	bool m_bMultiLine;
};

struct AutoSizingTextWin : PgWinText {};

struct ItemInfoWin : FrameBoxWin {

	unsigned int m_uiMoneyXPos;
	unsigned int m_uiTotalMoneyXPos;
	PgWinText* m_apkTextWin[80]; // 0x1A8
	PgWinSpr* m_pkGemIcon;
	PgWinSpr* m_pkGoldIcon;
	PgWinSpr* m_pkSilverIcon;
	PgWinSpr* m_pkCopperIcon;
	PgWinSpr* m_pkTotalGemIcon;
	PgWinSpr* m_pkTotalGoldIcon;
	PgWinSpr* m_pkTotalSilverIcon;
	PgWinSpr* m_pkTotalCopperIcon;
	unsigned int m_uiIconWidth;
	unsigned int m_uiIconHeight;
	AutoSizingTextWin* m_pkGemText;
	AutoSizingTextWin* m_pkGoldText;
	AutoSizingTextWin* m_pkSilverText;
	AutoSizingTextWin* m_pkCopperText;
	AutoSizingTextWin* m_pkTotalGemText;
	AutoSizingTextWin* m_pkTotalGoldText;
	AutoSizingTextWin* m_pkTotalSilverText;
	AutoSizingTextWin* m_pkTotalCopperText;
	int m_iItemNameLength;
	int m_iFontHeight;
	Item* m_pkItem;
	ItemInfo* m_pkItemInfo;
	const unsigned int m_iLimitRandomOption;
	IconWin* m_pkItemMoneyIcon;
	IconWin* m_pkItemTotalMoneyIcon;
	AutoSizingTextWin* m_pkItemMoneyText;
	AutoSizingTextWin* m_pkItemMoneyNumText;
	AutoSizingTextWin* m_pkItemTotalMoneyText;
	unsigned int m_uiItemMoneyWidth;
	PgWinBut* m_pkCloseBtn;
};

template <typename T, typename S>
struct stdmap
{
	int idc[4];
};

struct SLWCreateInfoItem
{
	int nItemType;
	NiNode* pNode;
	std::vector<NiPointer<PgSprData>, std::allocator<NiPointer<PgSprData>>> vecSprData;

	stdmap<unsigned int, void*> mapSprDataWinState;
	stdmap<unsigned int, std::string> mapSprDataWinStateOrder;

	tagRECT rect;
	std::vector<std::string, std::allocator<std::string>> vecNodeName;
	bool bAbbreviatable;
	int nVisiableTextMaxNums;
};

union Name8 {
	char n8_name[32];
	unsigned int n8_code[8];
};

struct CDataReaderVtbl
{
	void* (__thiscall* __vecDelDtor)(CDataReader* _this, unsigned int);
};

enum TaskType {
	TT_NOTSPECIFIED = 0x0,
	TT_ATTACK_SEQ = 0x1,
};

struct ITask : NiRefObject, IDirectMessenger {

	enum TaskState {
		TS_NONINITIALIZED = 0x0,
		TS_INITIALIZED = 0x1,
		TS_FINISHED = 0x2,
	};

	TaskState m_eTaskState;
	TaskType m_eTaskType;
	ITask* m_pkParentTask;
	NiTList<NiPointer<ITask>> m_kChildTaskList;
	NiTList<NiPointer<ITask>> m_kSerialTaskList;
};


struct StatPointReqTask : ITask {

	enum State
	{
		IDLE = 0x0,
		WAITING_MAKE_ACK = 0x1,
	};

	StatPointReqTask::State m_eState;

};

struct CDataReader {

	enum TYPE_LIST {
		TYPE_LIST_END = 0x0,
		TYPE_LIST_BYTE = 0x1,
		TYPE_LIST_WORD = 0x2,
		TYPE_LIST_DWORD = 0x3,
		TYPE_LIST_QWORD = 0x4,
		TYPE_LIST_FLOAT = 0x5,
		TYPE_LIST_FILENAME = 0x6,
		TYPE_LIST_FILEAUTO = 0x7,
		TYPE_LIST_REMARK = 0x8,
		TYPE_LIST_STR = 0x9,
		TYPE_LIST_STRAUTO = 0xA,
		TYPE_LIST_INX = 0xB,
		TYPE_LIST_INXBYTE = 0xC,
		TYPE_LIST_INXWORD = 0xD,
		TYPE_LIST_INXDWORD = 0xE,
		TYPE_LIST_INXQWORD = 0xF,
		TYPE_LIST_BYTE_BIT = 0x10,
		TYPE_LIST_WORD_BIT = 0x11,
		TYPE_LIST_DWORD_BIT = 0x12,
		TYPE_LIST_QWORD_BIT = 0x13,
		TYPE_LIST_BYTE_ARRAY = 0x14,
		TYPE_LIST_WORD_ARRAY = 0x15,
		TYPE_LIST_DWORD_ARRAY = 0x16,
		TYPE_LIST_QWORD_ARRAY = 0x17,
		TYPE_LIST_STR_ARRAY = 0x18,
		TYPE_LIST_STRAUTO_ARRAY = 0x19,
		TYPE_LIST_VARSTR = 0x1A,
		TYPE_LIST_INXSTR = 0x1B,
		TYPE_LIST_UNKNOWNED = 0x1C,
		TYPE_LIST_TWO_INX = 0x1D,
	};

	enum DATA_MODE {
		DATA_MODE_NORMAL = 0x0,
		DATA_MODE_ENCRYPTION = 0x1,
	};

	struct FIELD
	{
		char Name[48];
		CDataReader::TYPE_LIST Type;
		unsigned int Size;
	};

	struct HEAD {
		unsigned int nVersionKey;
		char sVersion[20];
		unsigned int nReserved;
		CDataReader::DATA_MODE nDataMode;
		unsigned int nFileSize;
		unsigned int nDataSize;
		unsigned int nNumOfRecord;
		unsigned int nFieldSize;
		unsigned int nNumOfField;
		CDataReader::FIELD Field[];
	};

	CDataReaderVtbl* vfptr;
	unsigned int m_nFileSize;
	unsigned int m_nBFSize;
	unsigned int m_nDataArraySize;
	unsigned int m_nFileCheckSum;
	Name8 m_sFileMD5;
	CDataReader::HEAD* m_pHead;
	char* m_pData;
	char** m_pDataArray;
};

struct CCharacterTitleData
{
	CDataReader m_CharacterTitleData;
};

struct CharTitleWin : PgWinFrame {

	struct CTWIN_LIST_INFO {
		char Type;
		char _bf1;
		unsigned __int16 MobID;
	};

	CharTitleWin::CTWIN_LIST_INFO ms_ctWinListInfo[531];
	void* m_pListWin;
	SlideBar* m_pSlideBarEx;
	unsigned int m_uiCurPage;
	CCharacterTitleData pCharTitleData;
	PgFrameWork* m_pkFrameWork;
	PgWinText* m_apkCurrentNickTextWin[7];
	PgWinText* m_apkChoiceNickTextWin[7];
	unsigned int m_uiFontHeight;
};

#pragma pack(push, 1)
struct CHAR_CHANGEBYCONDITION_PARAM {
	char nFlag;
	char nIndex;
	unsigned int nValue;
};
#pragma pack(pop)

struct Char_ChangeCondition {
	CHAR_CHANGEBYCONDITION_PARAM _WCLow[10];
	CHAR_CHANGEBYCONDITION_PARAM _WCHigh[10];
	CHAR_CHANGEBYCONDITION_PARAM _AC[10];
	CHAR_CHANGEBYCONDITION_PARAM _TH[10];
	CHAR_CHANGEBYCONDITION_PARAM _TB[10];
	CHAR_CHANGEBYCONDITION_PARAM _MALow[10];
	CHAR_CHANGEBYCONDITION_PARAM _MAHigh[10];
	CHAR_CHANGEBYCONDITION_PARAM _MR[10];
	std::vector<unsigned short> _vecUsingPassiveSkill;
};

struct StatTitleListItemWin : PgWin
{
};

struct FreeStatView : FrameBoxWin {
	PgWinText* m_apkTextWin[20];
	PgWinBut* m_pkOKBut;
};

/* 5255 */
struct StatTitleWin : PgWinFrame {
	int m_iListCount;
	StatTitleListItemWin* m_apkListItemWin[4];
	IconWin* m_pkStatTitleIconWin;
	PgWinText* m_pkSelectedStatTitle;
};
/* 3117 */
struct SLWCreateInfo {
	int m_arrItem[4] = { 0, 0, 0, 0 };
	bool m_bMakeData = 0;
	int m_nOffX = 0;
	int m_nOffY = 0;
};

/*   47 */
enum SlideBarType
{
	HORIZONTAL = 0x0,
	VERTICAL = 0x1,
};

struct SlideBar : PgWin {
	PgWinSpr* m_pkSlide;
	PgWinSpr* m_pkSlidePoint;
	int m_nSplitCnt;
	int m_nCurPos;
	SlideBarType m_eType;
	unsigned int m_uiID;
	unsigned int m_uiClickMsg;
};

struct UIUtil {

	void* vfptr;

	int m_iXOff;
	int m_iYOff;

	PgWin* m_pkParent;
	NiPointer<NiAVObject> m_spUIGeom;

	UIUtil();

};

namespace {

	typedef bool(__thiscall* tCreate)(void* _this, PgFrameWork* pkFrameWork);
	typedef void(__thiscall* tOnCommand)(void* _this, unsigned int wParam, int lParam);
	typedef void(__thiscall* tUpdateMeWin)(void* _this, float fCurTime);

	typedef void(__thiscall* tPgWinInitPos)(PgWin* _this, unsigned int uiScreenWidth, unsigned int uiScreenHeight, float fXPosRate, float fYPosRate);
	typedef void(__thiscall* tPgWinEnable)(PgWin* _this, bool b);
	typedef void(__thiscall* tPgWinShow)(PgWin* _this, bool b);
	typedef void(__thiscall* tOnClose)(PgWin* _this);

	typedef void* (__thiscall* t_scalar_deleting_destructor)(void* _this, unsigned int a2);

	typedef void(__thiscall* tPgWinGetWinScreenRect)(PgWin* _this, tagRECT* kRect);
	typedef unsigned int(__thiscall* tPgWinSprGetHeight)(PgWin* _this);
	typedef unsigned int(__thiscall* tPgWinSprGetWidth)(PgWin* _this);

	const int PgWinInitPosAddr = 0x00402660;
	const int PgWinEnableAddr = 0x00401FC0;
	const int PgWinShowAddr = 0x00401FE0;
}

struct cvftbl2 {
	int pad[7];
};

struct cvftbl { //91
	t_scalar_deleting_destructor scalar_deleting_destructor;
	int pad3[35];
	tPgWinSprGetWidth PgWinSprGetWidth;
	tPgWinSprGetHeight PgWinSprGetHeight; // [37]

	int pad6[16];
	tPgWinGetWinScreenRect PgWinGetWinScreenRect; // [54]

	int pad5[4];
	tPgWinInitPos PgWinInitPos = reinterpret_cast<tPgWinInitPos>(PgWinInitPosAddr); // [59]
	tPgWinEnable PgWinEnable = reinterpret_cast<tPgWinEnable>(PgWinEnableAddr); // [60]

	int pad4[3];
	tPgWinShow PgWinShow = reinterpret_cast<tPgWinShow>(PgWinShowAddr); // [64]

	int pad0[16]; // [80]
	tUpdateMeWin UpdateMeWin; // [81]

	int pad8[8];

	tOnClose OnClose; // [89]

	int pad1[4];
	tOnCommand OnCommand; // [93]

	int pad2[38];
	tCreate Create;
};

struct HelpWin_PgWinFrame
{
	HWND__* m_hWebWindow;
	int m_uiWebXPos;
	int m_uiWebYPos;
	unsigned int m_uiWebWidth;
	unsigned int m_uiWebHeight;
	bool m_bOpen;
	int m_uiPlaneWebXPos;
	int m_uiPlaneWebYPos;
	unsigned int m_uiPlaneWebWidth;
	unsigned int m_uiPlaneWebHeight;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_kWebAddress;
};

union Name4
{
	char n4_name[16];
	unsigned int n4_code[4];
};

struct GameAngelAccountInfo
{
	char acSidNo[1024];
	char acKey[1024];
	char acID[1024];
};

struct ServerAddr
{
	Name4 m_kAddr;
	int m_iPort;
};

struct PROTO_NC_MISC_GAMETIME_ACK
{
	char hour;
	char minute;
	char second;
};

struct ServerInfo
{
	Name4 kWorldName;
	char kWorldNo;
	char kWorldState;
};

struct FiestaServerList
{
	unsigned int m_uiTotalWorld;
	ServerInfo* pkServerInfo;
};

struct Server
{
	bool m_bDoubleConnected;
	bool m_bCP;
	char m_szCPKey[20480];
	char m_szCPIP[20480];
	char m_szCPData[20480];
	char m_szCPShopUrl[20480];
	bool m_bGameAngelLogin;
	bool m_bTestServer;
	char kServerName[16];
	GameAngelAccountInfo m_GAAccountInfo;
	float m_fOffSetTime;
	char m_acToken[65];
	ServerAddr m_kLoginAddr;
	ServerAddr m_kZoneAddr;
	unsigned int m_uiTotalWorld;
	Name4* m_pakWorldName;
	char* m_pucWorldMgrNo;
	char* m_pucWorldMgrState;
	unsigned __int16 m_kWorldMgrHandle;
	PROTO_NC_MISC_GAMETIME_ACK m_kGameTime;
	float m_fGameTimeWhenSet;
	float m_fAppTimeWhenSet;
	float m_fOldGameTimeWhenSet;
	float m_fOldAppTimeWhenSet;
	float m_fOldOneDayTime;
	float m_fCurGameTime;
	FiestaServerList m_kFiestaServerList;
	int m_nSelectServerIndex;
};

struct Inventory
{
	bool m_bWaitingItemDropAck;
	NiPointer<Item> m_aspInv[192];
	NiPointer<Item> m_aspEquip[30];
	NiPointer<Item> m_aspMiniHouseInv[192];
	NiPointer<Item> m_aspMiniHouseEquip[11];
	NiPointer<Item> m_aspMiniHouseFurnitureItemInv[98];
	NiPointer<Item> m_aspMiniHouseAccessoryItemInv[98];
	NiPointer<Item> m_aspMiniHouseTileAllItemInv[98];
	NiPointer<Item> m_aspMiniHouseMinigameAllItemInv[98];
	NiPointer<Item> m_aspRewardInv[192];
	unsigned int m_uiRewardCount;
	NiPointer<Item> m_aspPremiumActionInv[42];
	unsigned int m_uiPremiumActionCount;
};


struct PROTO_NC_PARTY_MEMBER_LIST_CMD {

#pragma pack(push, 1)
	struct MEMBER_INFO
	{
		Name5 memberid;
		char memberstatus;
		char charclass;
	};
#pragma pack(pop)

	char membercount;
	PROTO_NC_PARTY_MEMBER_LIST_CMD::MEMBER_INFO memberarray[];
};

#pragma pack(push, 1)
struct PROTO_NC_PARTY_JOIN_ACK
{
	Name5 memberid;
	char charclass;
	unsigned __int16 err;
};
#pragma pack(pop)

enum LOOTING_TYPE
{
	LOOTING_TYPE_FREE = 0x0,
	LOOTING_TYPE_ORDER = 0x1,
	LOOTING_TYPE_LOOTER = 0x2,
	LOOTING_TYPE_DICE = 0x3,
	MAX_LOOTING_TYPE = 0x4,
};

enum ITEM_LOOT_TYPE
{
	ITEM_LOOT_NORMAL = 0x0,
	ITEM_LOOT_NAMED = 0x1,
	ITEM_LOOT_RARE_AND_SET = 0x2,
	ITEM_LOOT_UNIQUE = 0x3,
	ITEM_LOOT_MAX = 0x4,
};

struct PartyMemberInfo
{
	Name5 m_kCharID;
	char m_ucStatus;
	int m_iLv;
	int m_iHP;
	int m_iSP;
	int m_iMaxHP;
	int m_iMaxSP;
	int m_iLP;
	int m_iMaxLP;
	char m_byChrClass;
	char m_byInform;
	float m_fX;
	float m_fY;
	bool m_bShow;
};

#pragma pack(push, 1)
struct Party
{
	void* vfptr;
	Name5 m_kPartyMasterID;
	Name5 m_kLooterID;
	int m_iBelongType;
	LOOTING_TYPE m_eLootType;
	ITEM_LOOT_TYPE m_eItemType;
	bool m_bDuringJoinPropose;
	Name5 m_kJoinProposeCharID;
	__declspec(align(4)) float m_fJoinProposeStartTime;
	unsigned int m_uiTotalMember;
	PartyMemberInfo m_akMemberInfo[5];
	bool m_bIsMePartyMaster;
	__declspec(align(4)) LOOTING_TYPE m_eLootingType;
};
#pragma pack(pop)

#pragma pack(push,2)
struct PROTO_RICHPRESENCE_UPDATE
{
	char state[64];
	char details[64];
	int64_t StartTimestamp;
	int64_t EndTimestamp;
	char ImageName[13];
	char MapName[32];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PROTO_NC_PARTY_JOIN_EXISTING_REQ {
	Name5 requester;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PROTO_NC_GLOBAL_PLAYER_COUNT_CMD {
	int playerCount;
};
#pragma pack(pop)

struct STREETBOOTH_SIGNBOARD
{
	char signboard[30];
};

struct LinkedEffect
{
	std::vector<unsigned long, std::allocator<unsigned long>> m_vecEffectHandle;
	bool m_bShowLinkEffect;
};

struct AbStateInfectee
{
	struct AbStateProperty
	{
		int iUnMovableCount;
		int iUnAttackableCount;
		int iFearCount;
		int bVisible;
		int bTrapVisible;
		int iKarenCaptivateStateCount;
		int iCantChatStateCount;
		int iCantHealStateCount;
	};

	struct $237F328CBBEC1C3235B234BBFA51CE91
	{
		char byR;
		char byG;
		char byB;
		char byA;
	};

	union AbstateColor
	{
		unsigned int dwRGB;
		$237F328CBBEC1C3235B234BBFA51CE91 _s1;
	};

	void* vfptr;
	float m_fPrevTime;
	NiTList<void*> m_kAbStateList;
	AbStateProperty m_kAbStateProperty;
	AbstateColor m_kAbstateColor;
};

struct IEffectHolder
{
	void* vfptr;
	bool m_bShow;
	NiTList<void*> m_kAttachEffectList;
};

struct AttackSequenceManager
{
	void* vfptr;
	NiTList<void*> m_kAttSeqList;
	NiTList<void*> m_kSkillSeqList;
	float m_fCurrFrequency;
	float m_fTargetFrequency;
	bool m_bHardStopAttSeq;
	unsigned int m_uiTargetAniCode;
	bool m_bInDuringAttackInServer;
	unsigned __int16 m_kLastTargetHandle;
	int m_iCurrAttSeqCode;
	int m_iLastAttSeqCode;
	float m_fLastSequenceEndTime;
	bool m_bSequenceStarted;
	bool m_bAnimationStopWhenHitTime;
};

struct Char
{
	struct $89E43DFCE8C9D4014785E3686C98831A
	{
		unsigned __int16 kPrevRightHandEquipItemID;
		char byPrevRightHandUpgrade;
		unsigned __int16 kPrevLeftHandEquipItemID;
		char byPrevLeftHandUpgrade;
		unsigned __int16 kPrevRightHandAccItemID;
		unsigned __int16 kPrevLeftHandAccItemID;
		unsigned __int16 kPrevShieldAccItemID;
	};

	struct stEQUIP_BACKUP
	{
		$89E43DFCE8C9D4014785E3686C98831A kCase1;
		bool bUnEquipLeftHand;
		bool bUnEquipRightHand;
		bool bUnEquipLeftHandAcc;
		bool bUnEquipRightHandAcc;
		bool bUnEquipShieldAcc;
		int iBackupCase;
	};

	AbStateInfectee baseclass_0;
	IEffectHolder baseclass_3c;
	AttackSequenceManager baseclass_54;
	unsigned int m_dwCurrHpUpdateSeqNo;
	unsigned int m_dwHpUpdateSkipCount;
	unsigned int m_dwTOTCurrHpUpdateSeqNo;
	unsigned int m_dwTOTHpUpdateSkipCount;
	unsigned int m_uiCurrCharTitleType;
	unsigned __int16 m_byMiniHouseSkinID;
	STREETBOOTH_SIGNBOARD m_stSignboard;
	bool m_bIsSell;
	char m_CharTitleName[256];
	bool m_bUseCharTitle;
	float m_fSaveCharSpeed;
	stEQUIP_BACKUP m_kEquippedBackup;
	stEQUIP_BACKUP m_kAttackEquipBackup;
	unsigned __int16 m_kTargetResourceHandle;
	LinkedEffect kLinkedEffect;
	NiAVObject* m_pOldParent;
	unsigned __int16 m_kHandle;
	int spacer1;
	int spacer2; // Wrong spacing all over the structure
	char m_acName[40];
	char m_acLinkGateName[40];

};

#pragma pack(push, 4)
struct IFrameWorkMessenger
{
	PgFrameWork* framework;
};

struct ICharDeadEvent_vtbl
{
	void(__thiscall* OnDead)(ICharDeadEvent* self);
	bool(__thiscall* MatchProcessingHandle)(ICharDeadEvent* self, unsigned __int16);
};
#pragma pack(pop)

enum DeadEventType
{
	DEventType_BASE = 0x0,
	DEventType_LVUP = 0x1,
	DEventType_DropItem = 0x2,
	DEventType_ExpGain = 0x3,
	DEventType_SomeoneLVUP = 0x4,
	DEventType_InformWhoKilledMe = 0x5,
};

#pragma pack(push, 4)
struct ICharDeadEvent : IFrameWorkMessenger
{
	ICharDeadEvent_vtbl* vtable;
	unsigned short m_kCharHandle;
	DeadEventType m_eEventType;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct PROTO_NC_BAT_EXPGAIN_CMD
{
	unsigned int expgain;
	unsigned __int16 mobhandle;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct CharDeadEventExpGainFIESTA : ICharDeadEvent
{
	PROTO_NC_BAT_EXPGAIN_CMD m_kProto;
};
#pragma pack(pop)

struct NiUnsharedGeometryGroup : NiGeometryGroup
{
};

struct NiStream
{
	void* vtable;
	NiTArray<NiObjectGroup*> m_kGroups;
	unsigned int m_uiNifFileVersion;
	unsigned int m_uiNifFileUserDefinedVersion;
	char m_acFileName[260];
	bool m_bSaveLittleEndian;
	bool m_bSourceIsLittleEndian;
	void* m_pkSearchPath;
	NiTArray<NiPointer<NiObject> > m_kObjects;
	NiTArray<NiPointer<NiObject> > m_kTopObjects;
	void* m_pkIstr;
	void* m_pkOstr;
	void* m_kLinkIDs;
	unsigned int m_uiLinkIndex;
	void* m_kLinkIDBlocks;
	unsigned int m_uiLinkBlockIndex;
	void* m_kRegisterMap;
	NiPointer<NiTexturePalette> m_spTexturePalette;
	unsigned __int16 m_usNiAVObjectFlags;
	unsigned __int16 m_usNiTimeControllerFlags;
	unsigned __int16 m_usNiPropertyFlags;
	void* m_eBackgroundLoadStatus;
	bool m_bBackgroundLoadExitStatus;
	unsigned int m_uiLoad;
	unsigned int m_uiLink;
	unsigned int m_uiPostLink;
	void* m_kSemaphore;
	void* m_pkThread;
	void* m_pkBGLoadProc;
	char m_acLastLoadedRTTI[260];
	unsigned int m_uiLastError;
	char m_acLastErrorMessage[260];
};

struct SkillInfoWin : FrameBoxWin
{
	PgWinText* m_apkTextWin[60];
	std::map<unsigned short, std::string> m_setItemName;
	PgWinSpr* m_pkGemIcon;
	PgWinSpr* m_pkGoldIcon;
	PgWinSpr* m_pkSilverIcon;
	PgWinSpr* m_pkCopperIcon;
};

#pragma warning( default : 4200 )