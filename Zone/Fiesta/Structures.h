#pragma once

#include "Enums.h"
#include "Custom.h"
#include <WinSock2.h>
#include <ctime>
#include <stdio.h>
#include <cstdint>

#pragma warning( disable : 4200 )

namespace Fiesta::Structures
{
	class ItemActionObserveManagerListEffect;
	struct ClientPacket;
	struct ZoneBaseSession;
	struct ShineObject;
	struct SkillDataIndex;
	struct PassiveDataBox;
	struct FieldMap;
	struct SHINE_ITEM_STRUCT;
	struct BoothItemInfo;
	struct CharacterInventory;
	struct InvenCellReleaser;
	struct ItemBag;
	struct TargetAnalyser;
	struct ORColumnHeader;
	struct ORField;
	struct CharClass;
	struct CDataReader;
	struct CallBackEvent_vtbl;
	struct PacketContainerBase;
	struct NPCRoleBase;
	struct NPCRoleBase_vtbl;
	struct CQuestParserScript;
	struct CQuest;
	struct Raid;
	struct StreetBooth;
	struct ItemBoxIterator;
	struct IObserver_vtbl;
	struct ItemActionObserve;
	struct IActCondition;
	struct IObjectTypeValidator;
	struct IActEffect;
	struct IActCondition_vtbl;
	struct MobCondition;
	struct ItemAttributeClassVtbl;
	struct ItemAttributeClass;
	struct FreeStatStr;
	struct FreeStatMen;
	struct FreeStatCon;
	struct FreeStatDex;
	struct FreeStatInt;

	namespace MobTacticElement
	{
		struct MobActionBase;
		struct MobActionArgument;
	}

	namespace NPCAction
	{
		struct IAction_vtbl;
	}

	template<typename S>
	struct List;

	template<typename S>
	struct ItemSmallBag;

	namespace ShineObjectClass
	{
		struct ShineObject;
		struct ShineMobileObject;
		struct ShinePlayer;
		struct ShineMob;
	}

	namespace AttackRhythm
	{
		struct AttackRhythmBase;
	}

	namespace InventoryLocking
	{
		struct InvenCellReleaser;
		struct LockedCell;
		struct ReservedQuantity;
	}

	namespace UseEffect
	{
		struct UseItemBase;
	}

	namespace SpyNet
	{
		struct IntelligenceOffice;
	}

	namespace MobRegenClass
	{
		struct MobBreederGroup;
	}

	template<typename T>
	struct ListStruct
	{
		T* content;
		unsigned short next;
		unsigned short prev;
		char is_active;
		unsigned short event;
	};

	template<typename T>
	struct ListArray
	{
		T* elements;
		int size;
	};


	template<typename T>
	struct ListVtable
	{
		void* (__thiscall* destructor)(List<T>* self, unsigned int);
		T* (__thiscall* allocate_at_start)(List<T>* self, unsigned short);
		T* (__thiscall* allocate_at_end)(List<T>* self, unsigned short);
		char (__thiscall* free_element)(List<T>* self, unsigned short);
		char (__thiscall* push_at_start)(List<T>* self, T* element);
		char (__thiscall* push_at_end)(List<T>* self, T* element);
		char (__thiscall* pop_from_start)(List<T>* self, T* element);
		char (__thiscall* pop_from_end)(List<T>* self, T* element);
	};

#pragma pack(push, 4)
	template<typename S>
	struct List
	{
		struct ListCursor
		{
			unsigned short current_index;
			unsigned short sotred_index;
		};

		ListVtable<S>* vtable;
		unsigned short max_size;
		ListStruct<S>* elements;
		ListCursor cursor;
		ListArray<S>* sub_lists;
		unsigned short sub_list_count;
	};
#pragma pack(pop)

	union NetworkCommand
	{
		unsigned short protocol;
		struct
		{
			unsigned short command : 10;
			unsigned short department : 6;
		} str;
	};

	struct CiocpProcessInterfece
	{
		void* vtable;
	};

	struct CiocpProcessSocket : CiocpProcessInterfece {};

	struct IocpProcessSession : CiocpProcessInterfece {};

	struct CiocpProcess
	{
		CiocpProcessInterfece* m_pProcess;
		CiocpProcessInterfece m_DefautProcess;
	};

	union DummyUnionOverlapped2
	{
		unsigned int Offset;
		void* Pointer;
	};

	struct _OVERLAPPED2
	{
		unsigned int Internal;
		unsigned int InternalHigh;
		DummyUnionOverlapped2 ___u2;
		unsigned int OffsetHigh;
		void* hEvent;
	};

	struct CSocket_IOCP
	{
		enum IOCP_WORK_TYPE
		{
			READ = 0x0,
			WRITE = 0x1,
			CLOSE = 0x2,
			STOP = 0x3,
		};

		struct IOCP_OVERLAPPED : _OVERLAPPED2
		{
			IOCP_WORK_TYPE Type;
			CiocpProcess* pIOCP_Process;
			void* pData;
		};

		unsigned int m_Socket;
		sockaddr m_SocketAddr;
		CiocpProcessSocket m_IOCP_Process_Socket;
		CiocpProcess m_Write_IOCP_Process;
		CiocpProcess m_Read_IOCP_Process;
		CiocpProcess m_Close_IOCP_Process;
		IOCP_OVERLAPPED m_Overlapped_Write;
		IOCP_OVERLAPPED m_Overlapped_Read;
		IOCP_OVERLAPPED m_Overlapped_Close;
		_RTL_CRITICAL_SECTION m_Write_CS;
		int m_nPendingWrite;
		void* m_pFirstBuf;
		void* m_pLastBuf;
	};

	struct ZoneBaseSessionVtbl
	{
		int(__thiscall* check_heart_beat)(ZoneBaseSession* self, int);
		void(__thiscall* parsing)(ZoneBaseSession* self, void*, unsigned short);
		void(__thiscall* send_packet)(ZoneBaseSession* self);
	};

	struct ClientPacketVtable
	{
		void(__thiscall* encode)(ClientPacket* self);
		int(__thiscall* is_valid_header)(ClientPacket* self);
		void* unknown;
		int(__thiscall* is_valid_packet)(ClientPacket* self);
		int(__thiscall* get_packet_size)(ClientPacket* self, int*);
		unsigned short(__thiscall* get_data_size)(ClientPacket* self);
		unsigned short* (__thiscall* get_id_ptr)(ClientPacket* self);
		char* (__thiscall* get_data_ptr)(ClientPacket* self);
		int(__thiscall* get_packet)(ClientPacket* self, unsigned short*, char**, int*);
		void(__thiscall* take_next_packet)(ClientPacket* self);
		int(__thiscall* remove_all_used_packets)(ClientPacket* self);
		void(__thiscall* clear)(ClientPacket* self);
		ClientPacket* (__thiscall* set_id)(ClientPacket* self, unsigned short, int, char*);
		unsigned short(__thiscall* get_id)(ClientPacket* self);
	};

	// CPacket
	struct ClientPacket
	{
		#pragma pack(push, 1)
		struct Packet1
		{
			char size;
			unsigned short id;
			char data[];
		};

		struct Packet2
		{
			char size;
			unsigned short secondary_size;
			unsigned short id;
			char data[];
		};
		#pragma pack(pop)

		union Packet
		{
			Packet1 type1;
			Packet2 type2;
		};

		ClientPacketVtable* vtable;
		char* packet_buffer;
		int max_packet_size;
		Packet* packet_header;
		int read_position;
		int write_position;
	};

	struct ZoneBaseSession
	{
		enum SESSION_STATUS
		{
			SESSION_STATUS_EMPTY = 0x0,
			SESSION_STATUS_CONNECTED = 0x1,
			SESSION_STATUS_CONNECTING = 0x2,
			SESSION_STATUS_CLOSEING = 0x3,
		};

		ZoneBaseSessionVtbl* vtable;
		SESSION_STATUS status;
		int connected_server_id;
		int connected_world;
		int connected_zone;
		_SYSTEMTIME connected_time;
		unsigned int last_receive_time;
		unsigned int last_send_time;
		CSocket_IOCP socket_iocp;
		ClientPacket packet;
		IocpProcessSession iocp_process;
		unsigned int last_heart_beat_send_time;
	};

	struct $E0C9EB0EB1F220819204DDF41838D7D6
	{
		unsigned int notuse : 9;
		unsigned int method : 4;
		unsigned int zone : 5;
		unsigned int serial : 8;
		unsigned int second : 6;
		unsigned int minute : 6;
		unsigned int hour : 5;
		unsigned int day : 5;
		unsigned int month : 4;
		unsigned int year : 5;
		unsigned int world : 6;
		unsigned int mrsv : 1;
	};

	union SHINE_ITEM_REGISTNUMBER
	{
		$E0C9EB0EB1F220819204DDF41838D7D6 binary;
		unsigned int dwrdkey[2];
		unsigned long long key;
	};

	struct DiceTaiSaiBetting
	{
		Enums::DICE_TAISAI_BETTING nBetting;
		unsigned int nMoney;
	};

	enum DICE_TAISAI_BETTING_TYPE
	{
		DTBT_BETTING = 0x0,
		DTBT_BETTING_CANCEL = 0x1,
		MAX_DICE_TAISAI_BETTING_TYPE = 0x2,
	};

	struct FURNITURE_EMOTION_INFO
	{
		unsigned short nPlayerHandle;
		unsigned short nFurnitureHnd;
		char nPosition;
		char nEmotionNo;
	};
	union ORToken
	{
		char ort_Name[20];
		unsigned int ort_Code[5];
	};

#pragma pack(push, 1)
	struct InstanceDungeonInfo
	{
		ORToken Argument;
		char IDNo;
		char ZoneNumber;
		char MapIDClient[13];
		char ScriptName[32];
		char ModeIDLv;
		char EntranceType;
		char Guild;
		char Individual;
		unsigned short NeedQuest;
		char NeedItem[32];
		char Consume;
		char LimitTime;
		char MaxUseCount;
		char CheckSum;
		unsigned short NeedItemID;
	};
#pragma pack(pop)

	struct POSTYPEITEMINVEN
	{
		unsigned short Pos : 10;
		unsigned short Type : 6;
	};

	union ITEM_INVEN
	{
		unsigned short Inven;
		POSTYPEITEMINVEN str;
	};

	struct FieldLvCondition
	{
		char MapIndex[33];
		char ModeIDLv;
		unsigned short LvFrom;
		unsigned short LvTo;
	};

	struct PROTO_WM_UPDATE_SERVERQUEST_REQ
	{
		unsigned short OPCode;
		int ObjectID;
		int Ammount;
	};
	struct SHINE_XY_TYPE
	{
		unsigned int x;
		unsigned int y;
	};

	struct Parameter_Cluster
	{
		int Str;
		int Con;
		int Dex;
		int Int;
		int Men;
		int WCmin;
		int WCmax;
		int AC;
		int TH;
		int TB;
		int MAmin;
		int MAmax;
		int MR;
		int MH;
		int MB;
		int AbsoluteAttack;
		int AbsoluteDefend;
		int AbsoluteHit;
		int AbsoluteBlock;
		int MoveSpeed;
		int HPRecover;
		int SPRecover;
		int CastingTime;
		int Critical;
		int PhisycalWeaponMastery;
		int MagicalWeaponMastery;
		int ShieldAC;
		int HitRate;
		int EvaRate;
		int MACri;
		int CriDam;
		int MagCriDam;
		int CriDamRate;
		int MagCriDamRate;
		int AttSpeed;
		int MaxHP;
		int MaxHP_2;
		int MaxSP;
		int HPAbsorption_Hitted;
		int SPAbsorption_Hitted;
		int HPAbsorption_Hit;
		int SPAbsorption_Hit;
		int CriticalTB;
		int RegistNone;
		int ResistPoison;
		int ResistDeaseas;
		int ResistCurse;
		int ResistMoveSpdDown;
		int ResistGTI;
		int MaxLP;
		int LPRecover;
	};

	struct PROTO_NC_CHARSAVE_PKCOUNT_CMD
	{
		unsigned int chrregnum;
		unsigned int pkcount;
	};

	union MapNameStruct
	{
		char name[12];
		unsigned int code[3];
	};

	struct PROTO_NC_CHARSAVE_LOCATION_CMD
	{
		unsigned int chrregnum;
		MapNameStruct map;
		SHINE_XY_TYPE coord;
		unsigned int kqhandle;
		MapNameStruct map_kq;
		SHINE_XY_TYPE coord_kq;
	};

#pragma pack(push, 1)
	struct PROTO_NC_CHARSAVE_LEVEL_CMD
	{
		unsigned int chrregnum;
		char level;
		unsigned long long exp;
		unsigned int fame;
	};

	struct PLAYER_QUEST_DATA
	{
		long long StartTime;
		long long EndTime;
		unsigned int RepeatCount;
		char ProgressStep;
		char End_NPCMobCount[5];
		char End_Location : 1;
		char End_Scenario : 1;
		unsigned short End_RunningTimeSec;
	};
#pragma pack(pop)

	struct PLAYER_QUEST_INFO
	{
		unsigned short ID;
		char Status;
		PLAYER_QUEST_DATA Data;
	};

#pragma pack(push, 2)
	struct tagQUESTDOING
	{
		unsigned int chrregnum;
		char bNeedClear;
		char nNumOfDoingQuest;
		PLAYER_QUEST_INFO QuestDoingArray[];
	};
#pragma pack(pop)

	struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD
	{
		unsigned short wldmanhandle;
		tagQUESTDOING questdoing;
	};
#pragma pack(push, 2)
	struct  PROTO_NC_CHARSAVE_ALL_ACK
	{
		unsigned short bufferlocation;
		unsigned int chrregnum;
	};
#pragma pack(pop)

	struct PROTO_NC_CHARSAVE_QUEST_DOING_REQ
	{
		PROTO_NC_CHARSAVE_ALL_ACK handle;
		char bNeedClear;
		char nNumOfDoingQuest;
		PLAYER_QUEST_INFO QuestDoingArray[];
	};

#pragma pack(push, 2)
	struct tagQUESTREAD
	{
		unsigned int chrregnum;
		unsigned short nNumOfReadQuest;
		unsigned short QuestReadIDArray[];
	};
#pragma pack(pop)

	struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD
	{
		unsigned short wldmanhandle;
		tagQUESTREAD questread;
	};

#pragma pack(push, 2)
	struct tagQUESTREPEAT
	{
		unsigned int chrregnum;
		unsigned short nNumOfRepeatQuest;
		PLAYER_QUEST_INFO QuestRepeatArray[];
	};
#pragma pack(pop)

	struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD
	{
		unsigned short wldmanhandle;
		tagQUESTREPEAT questrepeat;
	};
	union Name5
	{
		char n5_name[20];
		unsigned int n5_code[5];
	};
	struct $3E4B5BB2A6E91072587D81F6FFAE5F75
	{
		Parameter_Cluster Plus;
		Parameter_Cluster Rate;
	};
	struct $C93639B857142A0E935706D3FF30EE44
	{
		short Burn;
		short Poison;
		short Desease;
		short Blooding;
		short PitBlooding;
	};
	struct Parameter_ChangeByConditionParam
	{
		unsigned short cbcp_nID;
		unsigned int cbcp_nCondition;
		unsigned int cbcp_nChange;
		int cbcp_nChangeParam;
		int cbcp_nCharged;
		char cbcp_nMaxValueNum;
		int* cbcp_pValue;
	};
	struct $AEE396C9230C78117AB14F21ABF19664
	{
		char cannotmove_stun : 1;
		char cannotmove_entangle : 1;
		char cannotattack : 1;
	};

#pragma pack(push, 4)
	struct Parameter_Container
	{
		Parameter_Cluster PureCharParam;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 Item;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 ItemPowerRate;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 Upgrade;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 WeaponTitle;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 PassiveSkill;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 AbnormalState;
		$3E4B5BB2A6E91072587D81F6FFAE5F75 LastTune;
		Parameter_Cluster Total;
		$C93639B857142A0E935706D3FF30EE44 DotDamagePlus;
		short SPRate;
		short RangeEvasion;
		$AEE396C9230C78117AB14F21ABF19664 flag;
		unsigned short MissPercentFix;
		unsigned short DamageReflection;
		unsigned short ChangeAbilityInfo;
		unsigned short HealRate;
		unsigned short PassiveBuffKeepTimeUPRate;
		unsigned short PassiveHealRate;
		unsigned short PassiveCriDamageRatePlus;
		Parameter_ChangeByConditionParam PassiveHPDownRateWCMin;
		Parameter_ChangeByConditionParam PassiveHPDownRateWCMax;
		Parameter_ChangeByConditionParam PassiveHPDownRateMAMin;
		Parameter_ChangeByConditionParam PassiveHPDownRateMAMax;
		Parameter_ChangeByConditionParam PassiveHPDownRateAC;
		Parameter_ChangeByConditionParam PassiveHPDownRateMR;
		Parameter_ChangeByConditionParam PassiveMovingTBPlus;
		unsigned short PhysicalImmuneRate;
		unsigned short MagicalImmuneRate;
		unsigned int RangeOver;
		unsigned short DMGMinusRate;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ActiveSkillInfo
	{
		unsigned short ID;
		char InxName[32];
		char Name[64];
		unsigned int Grade;
		unsigned int Step;
		unsigned int MaxStep;
		Enums::WeaponDemandType DemandType;
		char DemandSk[32];
		unsigned short UseItem;
		unsigned int ItemNumber;
		unsigned int ItemOption;
		unsigned short DemandItem1;
		unsigned short DemandItem2;
		unsigned int SP;
		unsigned int SPRate;
		unsigned int HP;
		unsigned int HPRate;
		unsigned int LP;
		unsigned int Range;
		Enums::TargetType First;
		Enums::TargetType Last;
		char IsMovingSkill;
		unsigned short UsableDegree;
		unsigned short DirectionRotate;
		unsigned short SkillDegree;
		Enums::TargetState SkillTargetState;
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
		Enums::UseClassType UseClass;
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
		Enums::SkillEffectType EffectType;
		Enums::SkillSpecial SpecialIndexA;
		unsigned int SpecialValueA;
		Enums::SkillSpecial SpecialIndexB;
		unsigned int SpecialValueB;
		Enums::SkillSpecial SpecialIndexC;
		unsigned int SpecialValueC;
		Enums::SkillSpecial SpecialIndexD;
		unsigned int SpecialValueD;
		Enums::SkillSpecial SpecialIndexE;
		unsigned int SpecialValueE;
		char SkillClassifierA[32];
		char SkillClassifierB[32];
		char SkillClassifierC[32];
		char CannotInside;
		char DemandSoul;
		unsigned short HitID;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct ActiveSkillInfoServer
	{
		unsigned short ID;
		char InxName[32];
		char UsualAttack;
		unsigned int SkilPyHitRate;
		unsigned int SkilMaHitRate;
		unsigned int PsySucRate;
		unsigned int MagSucRate;
		char StaLevel;
		unsigned int DmgIncRate;
		unsigned short DmgIncValue;
		Enums::SkillHitTp SkillHitType;
		char ItremUseSkill;
		unsigned int AggroPerDamage;
		unsigned int AbsoluteAggro;
		char AttackStart;
		char AttackEnd;
		unsigned short SwingTime;
		unsigned short HitTime;
		char AddSoul;
	};
#pragma pack(pop)

	struct SKILL_EMPOWER
	{
		unsigned short damage : 4;
		unsigned short sp : 4;
		unsigned short keeptime : 4;
		unsigned short cooltime : 4;
	};
	struct $788B0942AF912ED5BADA1DB55B235793
	{
		int mha_AbStateRate;
		Enums::ABSTATEINDEX mha_AbStateIndex;
		int mha_AbStateStrength;
	};
	const struct MultiHitArgument
	{
		int mha_HitStep;
		int mha_DamageRate;
		int mha_AraeStep;
		$788B0942AF912ED5BADA1DB55B235793 mha_AbState[4];
	};
	struct EngageArgument
	{
		void* att;
		void* def;
		SkillDataIndex* sklinfo;
		SKILL_EMPOWER empower;
		char actionnumber;
		char attackcode;
		char iscritical;
		char ismiss;
		char isdead;
		char isshieldblock;
		char isresist;
		char isDamege2Heal;
		char isImmune;
		SHINE_XY_TYPE* attackloc;
		int damagerate;
		int crirateadd;
		MultiHitArgument* pMultiHitArg;
		int nBMPDamageRate;
	};
	struct PROTO_NC_ITEM_BUY_REQ
	{
		unsigned short itemid;
		unsigned int lot;
	};
#pragma region ShineObjectVtable

	typedef void* (__thiscall* Hook_GetRTTI)(void* self);
	typedef void* (__thiscall* destructor)(void* self, unsigned int);
	typedef char(__thiscall* clear_dice_betting_info)(void* self);
	typedef char(__thiscall* Hook_so_mh_SetDiceHistory)(void* self);
	typedef char(__thiscall* Hook_so_mh_ClearGamerBettingInfo)(void* self);
	typedef char(__thiscall* Hook_so_mh_GetTaiSaiGamerCnt)(void* self);
	typedef char(__thiscall* Hook_so_mh_RankSort)(void* self);
	typedef char(__thiscall* Hook_so_mh_SetIsCreateDice)(void* self, char, SHINE_ITEM_REGISTNUMBER);
	typedef char(__thiscall* Hook_so_mh_IsCreateDice)(void* self, SHINE_ITEM_REGISTNUMBER);
	typedef char(__thiscall* Hook_so_mh_SetIsDeleteDice)(void* self, char, SHINE_ITEM_REGISTNUMBER);
	typedef char(__thiscall* Hook_so_mh_IsDeleteDice)(void* self, SHINE_ITEM_REGISTNUMBER);
	typedef char(__thiscall* Hook_so_mh_SetIsBlowGame)(void* self, char);
	typedef char(__thiscall* Hook_so_mh_IsBlowGame)(void* self);
	typedef char(__thiscall* Hook_so_mh_SetIsLeaveOwner)(void* self, char);
	typedef char(__thiscall* Hook_so_mh_IsLeaveOwner)(void* self);
	typedef char(__thiscall* Hook_so_mh_ExcuteLeaveRoom)(void* self);
	typedef char(__thiscall* Hook_so_mh_ExcuteLeaveGame)(void* self);
	typedef char(__thiscall* Hook_so_mh_ExcuteBlowGame)(void* self);
	typedef char(__thiscall* Hook_so_mh_IsActiveDiceTaiSai)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_SendTaiSaiGameInfo)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_SendTaiSaiBettingInfo)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_CanEnter)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_Enter)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadEnter)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_Out)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadOut)(void* self, void*, char);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_ModeChange)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadModeChange)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_ModeChangeLeave)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadModeChangeLeave)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadSetTimer)(void* self, DiceTaiSaiBetting*, DICE_TAISAI_BETTING_TYPE);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_CanBetting)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_Betting)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadBetting)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_CanBettingCancel)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BettingCancel)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadBettingCancel)(void* self, void*, DiceTaiSaiBetting*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_CanDiceRoll)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_CanAutoDiceRoll)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_DiceRoll)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadDiceRoll)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_MoneyResult_DiceRoll)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_Result_DiceRoll)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_ResultLog_DiceRoll)(void* self, int);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadResult_DiceRoll)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_BroadEmotion_DiceRoll)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_PrepareNextGame)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_GetExpectIncomeMoney)(void* self, ITEM_INVEN);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_GetReceiptIncomeMoney)(void* self, ITEM_INVEN);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_GetRank)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mh_DiceTaiSai_SendRank)(void* self, void*);
	typedef char(__thiscall* Hook_so_mh_DiceTaiSai_BroadLargeAmount)(void* self);
	typedef char(__thiscall* Hook_so_mh_DiceTaiSai_BroadGameFold)(void* self);
	typedef void(__thiscall* Hook_so_mh_DiceTaiSai_GetGameStatus)(void* self);
	typedef void(__thiscall* Hook_so_mh_DiceTaiSai_GetGameMode)(void* self);
	typedef char(__thiscall* Hook_so_mh_SetDiceRewardMoney)(void* self, void*);
	typedef FURNITURE_EMOTION_INFO* (__thiscall* Hook_so_ply_MH_GetFurnitureEmotionInfo)(void* self);
	typedef char(__thiscall* Hook_so_ply_MH_InitFurnitureEmotionInfo)(void* self);
	typedef char(__thiscall* Hook_so_ply_MH_IsFurnitureEmotion)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_ply_MH_IsFurnitureEmotionPosition)(void* self, unsigned short, char);
	typedef char(__thiscall* Hook_so_ply_MH_IsFurnitureEmotionNo)(void* self, char);
	typedef unsigned short(__thiscall* Hook_so_ply_MH_GetFurnitureEmotion)(void* self);
	typedef char(__thiscall* Hook_so_ply_MH_GetFurnitureEmotionPosition)(void* self);
	typedef char(__thiscall* Hook_so_ply_MH_GetFurnitureEmotionNo)(void* self);
	typedef char(__thiscall* Hook_so_ply_MH_SetFurnitureEmotion)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_ply_MH_SetFurnitureEmotionPosition)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_MH_SetFurnitureEmotionNo)(void* self, char);
	typedef unsigned short(__thiscall* Hook_so_mh_CanFurnitureEmotion)(void* self, void*, void*);
	typedef char(__thiscall* Hook_so_mh_IsFurnitureEmotion)(void* self, unsigned short, char);
	typedef char(__thiscall* Hook_so_mh_FurnitureEmotionStop)(void* self, unsigned short, void*);
	typedef char(__thiscall* Hook_so_mh_SendInnerPlayerFurnitureEmotion)(void* self, void*);
	typedef char(__thiscall* Hook_so_PacketBufferFlush)(void* self);
	typedef void(__thiscall* Hook_so_SetRegistNumber)(void* self, void*);
	typedef void(__thiscall* Hook_so_SetSocketSession)(void* self, void*);
	typedef int(__thiscall* Hook_so_EncSeedSet)(void* self);
	typedef void* (__thiscall* Hook_so_GetDataSocketStream)(void* self);
	typedef void* (__thiscall* Hook_so_GetGameSocketStream)(void* self);
	typedef char(__thiscall* Hook_so_IsEmpty)(void* self);
	typedef void(__thiscall* Hook_so_SendProtocol)(void* self, int, int);
	typedef void(__thiscall* Hook_so_SendErrorCode)(void* self, int, int, int);
	typedef void(__thiscall* Hook_so_FirstActionAfterSocketConnect)(void* self);
	typedef void(__thiscall* Hook_so_CloseByLink)(void* self);
	typedef void* (__thiscall* Hook_so_GetLastUpgradeInfo)(void* self);
	typedef char(__thiscall* Hook_so_door_DoorAction)(void* self, char*, void*);
	typedef void* (__thiscall* Hook_so_TradeStructure)(void* self);
	typedef void* (__thiscall* Hook_so_TradeBoard)(void* self);
	typedef bool(__thiscall* Hook_so_GetWaitTradeResFromDB)(void* self);
	typedef void(__thiscall* Hook_so_SetWaitTradeResFromDB)(void* self, bool);
	typedef void(__thiscall* Hook_so_ply_ItemMakeItem)(void* self, void*);
	typedef void(__thiscall* Hook_so_SetPossibleNewConnect)(void* self, char);
	typedef char(__thiscall* Hook_so_GetPossibleNewConnect)(void* self);
	typedef void(__thiscall* Hook_so_RefreshWMSSocket)(void* self);
	typedef void(__thiscall* Hook_so_Unmark)(void* self, void*, char, char);
	typedef unsigned short(__thiscall* Hook_so_GetWMSHandle)(void* self);
	typedef unsigned int(__thiscall* Hook_so_GetCharRegistNumber)(void* self);
	typedef unsigned int(__thiscall* Hook_so_GetUserRegistNumber)(void* self);
	typedef void(__thiscall* Hook_so_NC_ITEMDB_ADMINCREATEFAIL_ACK)(void* self, void*);
	typedef void(__thiscall* Hook_so_NC_ITEMDB_fail)(void* self, int, int, unsigned short);
	typedef void(__thiscall* Hook_so_NC_ITEMDB_USE_ACK)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_BackupParameter)(void* self, Parameter_Cluster*);
	typedef void(__thiscall* Hook_so_RecalcEquipParam)(void* self);
	typedef void(__thiscall* Hook_so_RecalcAbstateParam)(void* self);
	typedef void(__thiscall* Hook_so_RecalcPassiveParam)(void* self);
	typedef void(__thiscall* Hook_so_RecalcLastParam)(void* self);
	typedef void(__thiscall* Hook_so_ply_ItemEffect)(void* self, Enums::UseEffectType, unsigned short, void*);
	typedef void(__thiscall* Hook_so_ply_ChargedBuff)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_NewSkillCoolTime)(void* self, unsigned short, int);
	typedef void(__thiscall* Hook_so_ply_InitFreeStat)(void* self);
	typedef void(__thiscall* Hook_so_ply_InitSkillEmpow)(void* self);
	typedef void(__thiscall* Hook_so_ply_SkillEmpowerSetResult)(void* self, unsigned short, unsigned short);
	typedef int(__thiscall* Hook_so_ply_IncNGet_PKCount)(void* self);
	typedef int(__thiscall* Hook_so_ply_SavePKCount)(void* self, PROTO_NC_CHARSAVE_PKCOUNT_CMD*);
	typedef int(__thiscall* Hook_so_SaveLocation)(void* self, PROTO_NC_CHARSAVE_LOCATION_CMD*);
	typedef int(__thiscall* Hook_so_SaveLevel)(void* self, PROTO_NC_CHARSAVE_LEVEL_CMD*);
	typedef int(__thiscall* Hook_so_SaveQuestDoing)(void* self, PROTO_NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD*);
	typedef int(__thiscall* Hook_so_SaveQuestDoing1)(void* self, PROTO_NC_CHARSAVE_QUEST_DOING_REQ*);
	typedef int(__thiscall* Hook_so_SaveQuestRead)(void* self, PROTO_NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD*);
	typedef int(__thiscall* Hook_so_SaveQuestRepeat)(void* self, PROTO_NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD*);
	typedef int(__thiscall* Hook_so_SaveAbstate)(void* self, void*, Name5*, bool);
	typedef int(__thiscall* Hook_so_SaveSkill)(void* self, void*, int);
	typedef int(__thiscall* Hook_so_SaveStat)(void* self, void*);
	typedef int(__thiscall* Hook_so_SaveGameData)(void* self, void*);
	typedef int(__thiscall* Hook_so_SaveItem)(void* self, void*);
	typedef char(__thiscall* Hook_so_SaveItem_Part)(void* self, NetworkCommand*, void*);
	typedef int(__thiscall* Hook_so_SaveChestInfo)(void* self, void*);
	typedef int(__thiscall* Hook_so_SaveCharTitle)(void* self, void*);
	typedef int(__thiscall* Hook_so_SaveMisc2WMS)(void* self, void*);
	typedef int(__thiscall* Hook_so_SaveToDB_CharTitle)(void* self, void*);
	typedef void* (__thiscall* Hook_so_ply_FindJobDungeon)(void* self, char*);
	typedef char(__thiscall* Hook_so_ply_2JobDungeon)(void* self, void*, char*);
	typedef int(__thiscall* Hook_so_ply_FirstJobChange)(void* self);
	typedef int(__thiscall* Hook_so_ply_SilverWingCoolTime)(void* self);
	typedef void(__thiscall* Hook_so_ply_MakeMiniHouse)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_SendBoothSize)(void* self);
	typedef char(__thiscall* Hook_so_AbnormalState_IsSet)(void* self, Enums::ABSTATEINDEX);
	typedef char(__thiscall* Hook_so_AbnormalState_Strength)(void* self, Enums::ABSTATEINDEX);
	typedef unsigned int(__thiscall* Hook_so_AbnormalState_RestTime)(void* self, Enums::ABSTATEINDEX);
	typedef void(__thiscall* Hook_so_AbnormalState_Inform)(void* self, Enums::ABSTATEINDEX, int, char);
	typedef void(__thiscall* Hook_so_RetrateFromMap)(void* self);
	typedef void(__thiscall* Hook_so_RetreatFromMapByImmeditely)(void* self);
	typedef void(__thiscall* Hook_so_LinkToReserv)(void* self, void*, char);
	typedef void(__thiscall* Hook_so_TeleportReserv)(void* self, SHINE_XY_TYPE*);
	typedef bool(__thiscall* Hook_sp_IsLockedRefundReq)(void* self);
	typedef void(__thiscall* Hook_sp_LockRefundReq)(void* self);
	typedef void(__thiscall* Hook_sp_UnlockRefundReq)(void* self);
	typedef bool(__thiscall* Hook_sp_IsLockedRefundCancelReq)(void* self);
	typedef void(__thiscall* Hook_sp_LockRefundCancelReq)(void* self);
	typedef void(__thiscall* Hook_sp_UnlockRefundCancelReq)(void* self);
	typedef unsigned int(__thiscall* Hook_sp_lastpickuptime)(void* self);
	typedef void* (__thiscall* Hook_so_GetCharacterTitle)(void* self);
	typedef void* (__thiscall* Hook_so_GetStatDistStr)(void* self);
	typedef void* (__thiscall* Hook_so_GetBattleStat)(void* self);
	typedef void(__thiscall* Hook_so_GetTargetInfo)(void* self, void*);
	typedef Parameter_Container* (__thiscall* Hook_so_parameter)(void* self);
	typedef unsigned long long(__thiscall* Hook_so_ply_CurrentMoney)(void* self);
	typedef unsigned long long(__thiscall* Hook_so_ply_CurrentExp)(void* self);
	typedef unsigned int(__thiscall* Hook_so_ply_CurrentFame)(void* self);
	typedef void(__thiscall* Hook_so_ply_StoreMoney)(void* self, unsigned long long);
	typedef void(__thiscall* Hook_so_ply_StoreFame)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_ChangeCen)(void* self);
	typedef void(__thiscall* Hook_so_ply_ChangeFame)(void* self);
	typedef void(__thiscall* Hook_so_ply_SaveFame)(void* self);
	typedef void(__thiscall* Hook_so_ply_DepositAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_WithdrawAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildStorageWithdrawAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_InvenCellReleaser_PointStone)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_InvenCellReleaser_QuestReward)(void* self, void*);
	typedef FreeStatStr* (__thiscall* Hook_so_ply_FreeStatStr)(void* self);
	typedef FreeStatInt* (__thiscall* Hook_so_ply_FreeStatInt)(void* self);
	typedef FreeStatDex* (__thiscall* Hook_so_ply_FreeStatDex)(void* self);
	typedef FreeStatCon* (__thiscall* Hook_so_ply_FreeStatCon)(void* self);
	typedef FreeStatMen* (__thiscall* Hook_so_ply_FreeStatMen)(void* self);
	typedef CharacterInventory* (__thiscall* Hook_so_ItemInventory)(void* self);
	typedef void* (__thiscall* Hook_so_SpyAgent)(void* self);
	typedef char(__thiscall* Hook_so_CurMode)(void* self);
	typedef void(__thiscall* Hook_so_ply_ReinforceFoldtent)(void* self);
	typedef int(__thiscall* Hook_so_ply_InventorySize)(void* self);
	typedef int(__thiscall* Hook_so_ply_StorageSize)(void* self);
	typedef int(__thiscall* Hook_so_ply_StreetBoothSlot)(void* self);
	typedef void* (__thiscall* Hook_so_ply_ChargedEffectContainer)(void* self);
	typedef void* (__thiscall* Hook_so_CharacterClass)(void* self);
	typedef void* (__thiscall* Hook_so_Getabstatebit)(void* self);
	typedef unsigned short(__thiscall* Hook_so_RemakeHandle)(void* self, unsigned short);
	typedef void* (__thiscall* Hook_so_PacketEncryptClass)(void* self);
	typedef char(__thiscall* Hook_so_Routine)(void* self, void*, unsigned short);
	typedef char(__thiscall* Hook_so_ply_BanByServerDisconnect)(void* self, void*, unsigned short);
	typedef void(__thiscall* Hook_so_StoreCharData)(void* self, unsigned short, char*);
	typedef int(__thiscall* Hook_so_OverlapFactor)(void* self);
	typedef void* (__thiscall* Hook_so_LoginLocation)(void* self);
	typedef void(__thiscall* Hook_so_datasync)(void* self);
	typedef void(__thiscall* Hook_so_FillBriefInformation)(void* self, void*);
	typedef void(__thiscall* Hook_so_SendMyBriefInfo)(void* self, void*);
	typedef void(__thiscall* Hook_so_SetGateBriefInform)(void* self, char*);
	typedef char(__thiscall* Hook_so_ObjectType)(void* self);
	typedef char(__thiscall* Hook_so_AdministratorLevel)(void* self);
	typedef char(__thiscall* Hook_so_GetLevel)(void* self);
	typedef char(__thiscall* Hook_so_GetClass)(void* self);
	typedef char(__thiscall* Hook_so_TargetType)(void* self);
	typedef void(__thiscall* Hook_so_Heal)(void* self, int);
	typedef unsigned int(__thiscall* Hook_so_GetHP)(void* self);
	typedef unsigned int(__thiscall* Hook_so_GetSP)(void* self);
	typedef unsigned int(__thiscall* Hook_so_MaxHP)(void* self);
	typedef unsigned int(__thiscall* Hook_so_MaxSP)(void* self);
	typedef void(__thiscall* Hook_so_LostSP)(void* self, int);
	typedef void(__thiscall* Hook_so_GainSP)(void* self, int);
	typedef void(__thiscall* Hook_so_LostHP)(void* self, int);
	typedef void(__thiscall* Hook_so_GainHP)(void* self, int);
	typedef int(__thiscall* Hook_so_attackspeed1000)(void* self);
	typedef int(__thiscall* Hook_so_attackspeed1000_packet)(void* self);
	typedef unsigned int(__thiscall* Hook_so_AttackRange)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_WalkSpeed)(void* self);
	typedef unsigned short(__thiscall* Hook_so_RunSpeed)(void* self);
	typedef void(__thiscall* Hook_so_BroadcastLogout)(void* self);
	typedef int(__thiscall* Hook_so_fullbufferitem)(void* self, char*, void*);
	typedef int(__thiscall* Hook_so_fullbufferitem_box)(void* self, char*, void*, int, void*);
	typedef void(__thiscall* Hook_so_RecalcAbstateParamReady)(void* self);
	typedef void* (__thiscall* Hook_so_mobile_AbstateList)(void* self);
	typedef void(__thiscall* Hook_so_Chat)(void* self, unsigned short, char*, int, char, int);
	typedef void(__thiscall* Hook_so_Shout)(void* self, unsigned short, char*, char*, int, int);
	typedef void(__thiscall* Hook_so_drpitm_CanLootingBitSet)(void* self, void*);
	typedef char(__thiscall* Hook_so_drpitm_CanLooting)(void* self, void*);
	typedef char(__thiscall* Hook_so_drpitm_IsIndividualType)(void* self);
	typedef unsigned short(__thiscall* Hook_so_ItemDrop)(void* self, unsigned short, void*, void*, unsigned int, void*, char);
	typedef void* (__thiscall* Hook_so_drpitm_itemview)(void* self);
	typedef void(__thiscall* Hook_so_itempicked)(void* self);
	typedef unsigned short(__thiscall* Hook_so_PartyRegistNumber)(void* self);
	typedef unsigned short(__thiscall* Hook_so_GetRaidNumber)(void* self);
	typedef void(__thiscall* Hook_so_SetRaidNumber)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_GetPartyGroup)(void* self);
	typedef unsigned short(__thiscall* Hook_so_PartyRegistNumber_InAttack)(void* self);
	typedef unsigned int(__thiscall* Hook_so_GetCharRegistNumber_ItemLooter)(void* self);
	/** Gets the handle of the object (GetZoneHandle_ItemLooter) */
	typedef unsigned short(__thiscall* Hook_so_GetZoneHandle_ItemLooter)(void* self);
	typedef Name5* (__thiscall* Hook_so_CharName)(void* self);
	typedef void* (__thiscall* Hook_so_extradata)(void* self);
	typedef void(__thiscall* Hook_so_SetParty)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_SendPartyInformTo)(void* self, void*);
	typedef void(__thiscall* Hook_so_allparametercalculate)(void* self);
	typedef int(__thiscall* Hook_so_attack)(void* self, void*, int);
	typedef int(__thiscall* Hook_so_attack1)(void* self, void*, int, int);
	typedef void(__thiscall* Hook_so_SetLastBattle)(void* self);
	typedef char(__thiscall* Hook_so_isinbattle)(void* self);
	typedef void(__thiscall* Hook_so_SlantedFlag)(void* self, unsigned int, unsigned int, void*, void*);
	typedef int(__thiscall* Hook_so_smash)(void* self, EngageArgument*);
	typedef int(__thiscall* Hook_so_Bash)(void* self, EngageArgument*, int*, Enums::ABSTATEINDEX, int, int, int);
	typedef int(__thiscall* Hook_so_skillsmash)(void* self, void*, void*);
	typedef char(__thiscall* Hook_so_SkillEnchant)(void* self, void*, void*, void*, char*, char);
	typedef char(__thiscall* Hook_so_SkillCure)(void* self, void*, void*, void*);
	typedef char(__thiscall* Hook_so_Dispel)(void* self, void*, void*, void*, unsigned int);
	typedef char(__thiscall* Hook_so_CanSkillTarget)(void* self);
	typedef void(__thiscall* Hook_so_MoveByServer)(void* self, SHINE_XY_TYPE*, int, int, void*, int);
	typedef void(__thiscall* Hook_so_recoverhp)(void* self, int);
	typedef void(__thiscall* Hook_so_recoversp)(void* self, int);
	typedef void(__thiscall* Hook_so_KilledBy)(void* self, void*, int, int, unsigned int);
	typedef void(__thiscall* Hook_so_DamagedBy)(void* self, void*, int, int, char);
	typedef void(__thiscall* Hook_so_GetExperienceFromMob)(void* self, int, unsigned short, unsigned short);
	typedef void(__thiscall* Hook_so_briefequipset)(void* self);
	typedef int(__thiscall* Hook_so_EqualSetitemIndexNameCount)(void* self, const char*);
	typedef void* (__thiscall* Hook_so_GetItemActionObserves)(void* self);
	typedef void(__thiscall* Hook_so_ItemActonAbstateApp)(void* self, void*, void*, void*);
	typedef int(__thiscall* Hook_so_AddItemAction)(void* self, unsigned short, unsigned short);
	typedef int(__thiscall* Hook_so_DelItemAction)(void* self, unsigned short, unsigned short);
	typedef void(__thiscall* Hook_so_ply_ItemAction_UnEquip)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_EnchantActionUse)(void* self, const unsigned short);
	typedef void(__thiscall* Hook_so_ply_GuildStoreFill)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildStoreGradeFill)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_isGuildStoreGrade)(void* self);
	typedef unsigned int(__thiscall* Hook_so_weapontitle)(void* self, unsigned short*);
	typedef void(__thiscall* Hook_so_Disconnect)(void* self, int, void*, int);
	typedef void(__thiscall* Hook_so_banning)(void* self, void*);
	typedef char(__thiscall* Hook_so_LinkTo)(void* self, void*, int, int, int);
	typedef void(__thiscall* Hook_so_ply_ChangeCell)(void* self, ITEM_INVEN*, void*, ITEM_INVEN*);
	typedef void(__thiscall* Hook_so_ply_ChangeBriefInfo)(void* self, void*, int);
	typedef SHINE_XY_TYPE* (__thiscall* Hook_so_mobile_Move2Where)(void* self);
	typedef char(__thiscall* Hook_so_mobile_IsInMoving)(void* self);
	typedef SHINE_XY_TYPE* (__thiscall* Hook_so_mob_RegenLocation)(void* self);
	typedef SHINE_XY_TYPE* (__thiscall* Hook_so_mob_LastHittedLocation)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mob_ChaseRangeSquar)(void* self);
	typedef void(__thiscall* Hook_so_LearnPassive)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_LearnSkill)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_TradeBoardreset)(void* self);
	typedef void(__thiscall* Hook_so_tradestart)(void* self, void*);
	typedef char(__thiscall* Hook_so_tradepropose_timecheck)(void* self);
	typedef char(__thiscall* Hook_so_AbnormalState_Resist)(void* self, void*);
	typedef char(__thiscall* Hook_so_AbnormalState_Set)(void* self, void*, Enums::ABSTATEINDEX, int, void*, unsigned int, int, int, int, void*, void*);
	typedef char(__thiscall* Hook_so_AbnormalState_Set_CharAllMode)(void* self, void*, Enums::ABSTATEINDEX, int, void*, unsigned int, int, int, int, void*);
	typedef char(__thiscall* Hook_so_AbnormalState_Set_Simple)(void* self, void*, Enums::ABSTATEINDEX, int, bool, int, int, void*);
	typedef char(__thiscall* Hook_so_AbnormalState_Set_Simple1)(void* self, void*, Enums::ABSTATEINDEX, int, bool);
	typedef char(__thiscall* Hook_so_AbnormalState_Set_SS_SETABSTATEME)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_EscapeFromTarget)(void* self);
	typedef void(__thiscall* Hook_so_AbnormalState_Reset)(void* self, Enums::ABSTATEINDEX);
	typedef void(__thiscall* Hook_so_batobj_DamageReserv)(void* self, int);
	typedef void(__thiscall* Hook_so_batobj_DamageApply)(void* self, int);
	typedef int(__thiscall* Hook_so_batobj_GetDamage)(void* self);
	typedef void(__thiscall* Hook_so_mobile_MoveReserve)(void* self, SHINE_XY_TYPE*, int, void*, void*);
	typedef void* (__thiscall* Hook_so_fill_PROTO_NC_CHAR_MAPLOGIN_ACK)(void* self, void*);
	typedef void* (__thiscall* Hook_so_fill_CHAR_PARAMETER_DATA)(void* self, void*);
	typedef void* (__thiscall* Hook_so_AllOfRange_Getthis)(void* self);
	typedef void(__thiscall* Hook_so_safm_SetCinema)(void* self, void*);
	typedef void(__thiscall* Hook_so_charbasedata)(void* self, void*);
	typedef void(__thiscall* Hook_so_charsharpdata)(void* self, void*);
	typedef void(__thiscall* Hook_so_StoreQuestDoing)(void* self, void*);
	typedef void(__thiscall* Hook_so_StoreQuestDone)(void* self, void*);
	typedef void(__thiscall* Hook_so_StoreQuestRead)(void* self, void*);
	typedef void(__thiscall* Hook_so_StoreQuestRepeat)(void* self, void*);
	typedef void(__thiscall* Hook_so_CharAbstateData)(void* self, void*);
	typedef void(__thiscall* Hook_so_charskilldata)(void* self, void*);
	typedef void(__thiscall* Hook_so_CharChargedBuffData)(void* self, void*);
	typedef void(__thiscall* Hook_so_charpassivedata)(void* self, void*);
	typedef void(__thiscall* Hook_so_StoreInventoryFromServer)(void* self, void*);
	typedef void(__thiscall* Hook_so_Storegamedata)(void* self, void*);
	typedef void(__thiscall* Hook_so_accountstoragefill)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_reinforce_reloc)(void* self, void*, char*, int, int);
	typedef char(__thiscall* Hook_so_ply_dupmenu_canmenuopen)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_dupmenu_Set)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_dupmenu_close)(void* self, unsigned short);
	typedef int(__thiscall* Hook_so_ply_TotalSkillEmpower)(void* self);
	typedef void(__thiscall* Hook_so_ply_skillempowerclear)(void* self);
	typedef void(__thiscall* Hook_so_ply_itempickresult)(void* self, unsigned short, unsigned short);
	typedef void(__thiscall* Hook_so_ply_Getchestinform)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ClassChange)(void* self, char);
	typedef unsigned int(__thiscall* Hook_so_BodySize)(void* self);
	typedef void* (__thiscall* Hook_so_GetCharBriefInfo)(void* self);
	typedef void(__thiscall* Hook_so_mobile_Teleport)(void* self, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_mobile_Teleport1)(void* self);
	typedef void(__thiscall* Hook_so_door_Build)(void* self, MapNameStruct*, int, int, int, unsigned short, unsigned short, int, unsigned long long);
	typedef void(__thiscall* Hook_so_mob_Regenerate)(void* self, MapNameStruct*, int, int, int, unsigned short, unsigned short, void*, unsigned int, void*, void*, int, char, unsigned long long);
	typedef void(__thiscall* Hook_so_effect_EffectBlast)(void* self, unsigned short, MapNameStruct*, void*, void*, unsigned int, int, int);
	typedef void(__thiscall* Hook_so_effect_EffectBlast1)(void* self, unsigned short, MapNameStruct*, int, int, int, void*, unsigned int, int, int);
	typedef unsigned int(__thiscall* Hook_so_mob_DistanceFromHome)(void* self);
	typedef void(__thiscall* Hook_so_effect_BlastComplete)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_mob_RegenComplete)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_door_BuildComplete)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_mob_ViewAggroList)(void* self, void*);
	typedef void(__thiscall* Hook_so_mob_AppendAggro)(void* self, void*, int);
	typedef void(__thiscall* Hook_so_mob_DecreaseAggro)(void* self, void*, int);
	typedef unsigned short(__thiscall* Hook_so_mob_MobID)(ShineObjectClass::ShineObject* self);
	typedef void* (__thiscall* Hook_so_mob_DataBox)(void* self);
	typedef void* (__thiscall* Hook_so_mob_DataBoxforQuest)(void* self, void*);
	typedef Enums::MobRace(__thiscall* Hook_so_mob_Race)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mob_SetWeaponHitTime)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mob_SetWeaponAniTime)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mob_CanGathered)(void* self, void*, unsigned short*);
	typedef void(__thiscall* Hook_so_mob_CanRecover)(void* self, char);
	typedef void(__thiscall* Hook_so_mob_MobAggro)(void* self, char);
	typedef char(__thiscall* Hook_so_mobile_IsEnemy)(void* self, void*);
	typedef void(__thiscall* Hook_so_mobile_DamageOverTime)(void* self, void*, int, Enums::ABSTATEINDEX, bool, int*);
	typedef void(__thiscall* Hook_so_mobile_HPHealOverTime)(void* self, void*, int, Enums::ABSTATEINDEX);
	typedef void(__thiscall* Hook_so_mobile_SPHealOverTime)(void* self, void*, int);
	typedef int(__thiscall* Hook_so_mob_SelectWeapon)(void* self, void*, char);
	typedef int(__thiscall* Hook_so_mob_CurSelectWeapon)(void* self);
	typedef void* (__thiscall* Hook_so_mob_FalimyList)(void* self);
	typedef void* (__thiscall* Hook_so_mob_FindMyRaceTarget)(void* self, void*, int);
	typedef void* (__thiscall* Hook_so_mob_CanMyTarget)(void* self, void*, int);
	typedef void* (__thiscall* Hook_so_mob_CanNPCTarget)(void* self, void*, int);
	typedef unsigned short(__thiscall* Hook_so_CurrentTargetHandle)(void* self);
	typedef void(__thiscall* Hook_so_EquitEnd)(void* self);
	typedef ShineObjectClass::ShineObject* (__thiscall* Hook_so_CurrentTargetObject)(void* self);
	typedef void* (__thiscall* Hook_so_ply_CanMyTarget)(void* self, void*, int);
	typedef void(__thiscall* Hook_so_mob_RescueObject)(void* self, void*, char);
	typedef char(__thiscall* Hook_so_TentDistance)(void* self, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_ply_KQRewardStruct)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_KQRewardIndex)(void* self, char*);
	typedef void(__thiscall* Hook_so_ply_Setpartyslot)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_partymemberlogin)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_NewPartyMemberJoin)(void* self);
	typedef void(__thiscall* Hook_so_ply_SaveWeaponTitle)(void* self);
	typedef void(__thiscall* notice)(void* self, const char*); //so_ply_Notice
	typedef void(__thiscall* Hook_so_ply_WeaponSpeedSet)(void* self);
	typedef void(__thiscall* Hook_so_ply_WeaponRangeSet)(void* self);
	typedef void(__thiscall* Hook_so_ply_PickupMoney)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_IncDecMoney)(void* self, unsigned int, char);
	typedef char(__thiscall* Hook_so_ply_PickupItem)(void* self, void*, void*, unsigned short);
	typedef char(__thiscall* Hook_so_ply_SoloingMode)(void* self);
	typedef void(__thiscall* Hook_so_ply_PartyRecharge)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_FillChargedInven)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ChargedWithdraw)(void* self, void*);
	typedef void* (__thiscall* Hook_so_ply_EquipWeapon)(void* self, ITEM_INVEN*);
	typedef int(__thiscall* Hook_so_mobile_MoveSpeed)(void* self);
	typedef void(__thiscall* Hook_so_mobile_MoveState)(void* self);
	typedef void(__thiscall* Hook_so_RecalcSpeed)(void* self, int);
	typedef void(__thiscall* Hook_so_mobile_SpeedChange)(void* self);
	typedef char(__thiscall* Hook_so_mobile_DuringFlying)(void* self);
	typedef void(__thiscall* Hook_so_mobile_MoveHalt)(void* self);
	typedef void(__thiscall* Hook_so_ply_ShowBoothItem)(void* self, void*, void*, char);
	typedef void(__thiscall* Hook_so_ply_BoothTrade)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_ply_TradeBoardUnlock)(void* self, void*);
	typedef void* (__thiscall* Hook_so_ply_GetInventoryLockList)(void* self);
	typedef void(__thiscall* Hook_so_mgcfld_MagicFieldSpread)(void* self, unsigned short, void*, void*, SHINE_XY_TYPE*, SKILL_EMPOWER*);
	typedef void(__thiscall* Hook_so_mgcfld_MagicFieldSpread_Friend)(void* self, unsigned short, void*, void*, SHINE_XY_TYPE*, SKILL_EMPOWER*);
	typedef void(__thiscall* Hook_so_ply_Revival)(void* self);
	typedef char(__thiscall* Hook_so_mobile_TargetModeCheck)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_mobile_GetHPChangeOrder)(void* self);
	typedef void(__thiscall* Hook_so_ply_StatIncrease)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_StatDecrease)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_QuestCheck)(void* self, void(__thiscall*)(void* self, void*, void*, void*), void*, void*, void*);
	typedef void(__thiscall* Hook_so_ply_ItemLotChange)(void* self, unsigned short, int);
	typedef void(__thiscall* Hook_so_ply_KQSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_KQFail)(void* self);
	typedef char(__thiscall* Hook_so_ply_GetGender)(void* self);
	typedef void* (__thiscall* Hook_so_ply_QuestDiary)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mobile_WhoIsKillMe)(void* self);
	typedef unsigned short(__thiscall* Hook_so_mobile_WhoIsClickMe)(void* self);
	typedef void(__thiscall* Hook_so_mobile_SetClicker)(void* self, unsigned short);
	typedef unsigned int(__thiscall* Hook_so_ply_GetMyGuildNo)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetMyGuildNo)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_SetMyGuild)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_BroadcastGuildInfo)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mobile_GetGuildRegnum)(void* self);
	typedef void(__thiscall* Hook_so_ply_GuildStorageDeactivate)(void* self);
	typedef unsigned short* (__thiscall* Hook_so_ply_GetMyGuildStorageHandle)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetMyGuildStorageHandle)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_ItemBuyGuildToken)(void* self, unsigned int, PROTO_NC_ITEM_BUY_REQ*);
	typedef unsigned short* (__thiscall* Hook_so_ply_GetMyGuildAcademyRewardStorageHandle)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetMyGuildAcademyRewardStorageHandle)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStorageDeactivate)(void* self);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStorageWithdrawAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStorageDepositAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStorageRewardAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_BroadcastGuildAcademyInfo)(void* self);
	typedef char(__thiscall* Hook_so_ply_isAcademyGuildMember)(void* self);
	typedef unsigned int(__thiscall* Hook_so_ply_GetMyGuildAcademyNo)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetMyGuildAcademyNo)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_SetMyGuildAcademy)(void* self, void*);
	typedef char(__thiscall* Hook_so_ply_isIAmGuildAcademyMaster)(void* self);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStoreFill)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStoreGradeFill)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_isGuildAcademyRewardStoreGrade)(void* self);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewardStorageRewardZoneRng)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_GuildAcademyRewordSrorageItemInfoCmd)(void* self, void*, char);
	typedef void(__thiscall* Hook_so_ply_GuildReName)(void* self, char, void*);
	typedef void(__thiscall* Hook_so_ply_GuildReType)(void* self, char, char);
	typedef void(__thiscall* Hook_so_ply_GuildReNameItemUseSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_GuildReTypeItemUseSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_BriefLink)(void* self, MapNameStruct*, SHINE_XY_TYPE*);
	typedef char* (__thiscall* Hook_so_mobile_GetIdxName)(void* self);
	typedef void(__thiscall* Hook_so_bandit_ChangeType)(void* self, char);
	typedef char(__thiscall* Hook_so_IsMob)(void* self);
	typedef void(__thiscall* Hook_so_relink)(void* self, int);
	typedef int(__thiscall* Hook_so_Prison_Go)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_Prison_End)(void* self, MapNameStruct*, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_scene_MovePathSet)(void* self, int, int, void*);
	typedef void(__thiscall* Hook_so_scene_ItemAttrSet)(void* self, unsigned short, char*);
	typedef void(__thiscall* Hook_so_scene_CreateItem)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_scene_EraseItem)(void* self, unsigned short, int);
	typedef void(__thiscall* Hook_so_scene_DetectRange)(void* self, int);
	typedef void(__thiscall* Hook_so_scene_Duplicate)(void* self, int);
	typedef char(__thiscall* Hook_so_scene_IsIdle)(void* self);
	typedef void(__thiscall* Hook_so_ply_HorseFeed)(void* self);
	typedef void(__thiscall* Hook_so_mobile_BattleCamp)(void* self);
	typedef void(__thiscall* Hook_so_ply_AllCastCancel)(void* self);
	typedef void(__thiscall* Hook_so_mobile_DeadCheck)(void* self, void*);
	typedef void(__thiscall* Hook_so_SendInform2Admin)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_PartyInformInit)(void* self);
	typedef int(__thiscall* Hook_so_ply_ChargedStatPlus)(void* self);
	typedef void(__thiscall* Hook_so_ply_RoarItemUseSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_SkillEraseItemUseSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_RemoveWhen)(void* self);
	typedef void(__thiscall* Hook_so_ply_KeepFromChat)(void* self, void*);
	typedef SHINE_XY_TYPE* (__thiscall* Hook_so_mob_SightCenter)(void* self, int, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_mob_TargetChange)(void* self);
	typedef void(__thiscall* Hook_so_ply_Return2Quest)(void* self, int);
	typedef void(__thiscall* Hook_so_mob_SetGuildRegNum)(void* self, unsigned int);
	typedef char(__thiscall* Hook_so_mobile_MobAggroRate)(void* self);
	typedef void(__thiscall* Hook_so_ply_ItemBreakSuccess)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ItemBreakFail)(void* self, void*);
	typedef void(__thiscall* Hook_so_LogoutLog)(void* self, char*);
	typedef void(__thiscall* Hook_so_ply_SparrowWingExpand)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_SparrowWingFly)(void* self);
	typedef void(__thiscall* Hook_so_ply_ItemUseResultPacket)(void* self, int, char);
	typedef void(__thiscall* Hook_so_ply_ChestBoxOpenAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_Summon2GuildTournament)(void* self, void*, void*, void*);
	typedef void(__thiscall* Hook_so_ply_Send2GuildTournamentLogIn)(void* self, void*, char);
	typedef void(__thiscall* Hook_so_ply_GuildTournament_isSummon)(void* self);
	typedef void(__thiscall* Hook_so_ply_FlagCaptureCast)(void* self, unsigned short);
	typedef unsigned short(__thiscall* Hook_so_ply_GuildTournamentJoinNew)(void* self, void*);
	typedef unsigned short(__thiscall* Hook_so_IsInWeapon)(void* self);
	typedef void(__thiscall* Hook_so_ply_LoginIPSet)(void* self, int, int, int, int);
	typedef void(__thiscall* Hook_so_ply_FromWhere)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_GetFromWhere)(void* self);
	typedef char(__thiscall* Hook_so_ply_Script_CostumeCreate)(void* self, unsigned short, unsigned short, char*);
	typedef char(__thiscall* Hook_so_ply_Script_CostumeTakeOff)(void* self, unsigned short, unsigned short);
	typedef char(__thiscall* Hook_so_ply_WeddingPrepareItem)(void* self);
	typedef void(__thiscall* Hook_so_ply_WeddingData)(void* self, void*);
	typedef void* (__thiscall* Hook_so_ply_WeddingStatus)(void* self);
	typedef void(__thiscall* Hook_so_ply_WeddingInfoUpdate)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_DivorceProcess)(void* self);
	typedef void(__thiscall* Hook_so_ply_AdminCommand)(void* self, char*, int);
	typedef char(__thiscall* Hook_so_ply_ItemLotInspecting)(void* self, char);
	typedef void* (__thiscall* Hook_so_ply_GetItemLotInspector)(void* self);
	typedef int(__thiscall* Hook_so_ply_CalcTotalLot)(void* self, unsigned short, char*, char);
	typedef unsigned short(__thiscall* Hook_so_ply_ItemLotCheck)(void* self, SHINE_ITEM_REGISTNUMBER*);
	typedef char(__thiscall* Hook_so_ply_ServerMenuactor_sma_IsReady)(void* self);
	typedef void(__thiscall* Hook_so_UnlearnSkillAck)(void* self, void*);
	typedef char(__thiscall* Hook_so_mobile_ICanDamageTo)(void* self, void*, char*);
	typedef void* (__thiscall* Hook_so_MiscTable)(void* self);
	typedef void(__thiscall* Hook_so_serv_SetMaster)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_serv_SetTarget)(void* self, void*);
	typedef void(__thiscall* Hook_so_mob_AggroAdjust)(void* self, void*, int);
	typedef void(__thiscall* Hook_so_ply_Volley)(void* self);
	typedef void(__thiscall* Hook_so_ply_TargetChange)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_AbstateMatchEquip)(void* self);
	typedef void(__thiscall* Hook_so_ply_ReinforceRemoveWeapon)(void* self);
	typedef void(__thiscall* Hook_so_ply_ReinforceRemoveShield)(void* self);
	typedef void(__thiscall* Hook_so_ply_ReinforceRemoveEquip)(void* self, void*);
	typedef int(__thiscall* Hook_so_smo_CrossCounterDamage)(void* self, void*);
	typedef void* (__thiscall* Hook_so_serv_FindMaster)(void* self);
	typedef void(__thiscall* Hook_so_serv_ServantMissionSet)(void* self, void*);
	typedef char(__thiscall* Hook_so_mob_CanBeAttackedByPlayer)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_FillRewardInven)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseSet)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseCenUseTry)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseCenUseSuccess)(void* self);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseCenFrom)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseGetCenReward)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_HolyPromiseWithdrawCenReward)(void* self, void*);
	typedef void(__thiscall* Hook_so_mobile_SetNaturalEnemy)(void* self, void*);
	typedef void* (__thiscall* Hook_so_mobile_GetNaturalEnemy)(void* self);
	typedef char(__thiscall* Hook_sp_IsPreventAttack)(void* self);
	typedef char(__thiscall* Hook_sp_IsEthereal)(void* self);
	typedef char(__thiscall* Hook_so_mobile_IsInFear)(void* self);
	typedef char(__thiscall* Hook_so_ply_IsInBoothInterior)(void* self);
	typedef char(__thiscall* Hook_so_ply_RegistNumberVarifyCheck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_WeaponEndureChangeAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ShieldEndureChangeAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ChangeCharIDUseAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_mobile_Broadcast2ndTarget)(void* self, void*, int);
	typedef void* (__thiscall* Hook_so_GetTargetObject)(void* self);
	typedef void(__thiscall* Hook_so_Mob_SetSendTagetInfo)(void* self, char);
	typedef char(__thiscall* Hook_so_IsTarget)(void* self);
	typedef void(__thiscall* Hook_so_mobile_SendMyMoveInfo)(void* self, void*);
	typedef void(__thiscall* Hook_so_mob_RoamingPathSet)(void* self, void*);
	typedef void* (__thiscall* Hook_so_mob_RoamingPathGet)(void* self);
	typedef void(__thiscall* Hook_so_ply_StoreItem)(void* self, ITEM_INVEN*, void*, ITEM_INVEN*);
	typedef char(__thiscall* Hook_InteractWithNPC)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ToNormalLoc)(void* self, int);
	typedef void(__thiscall* Hook_so_ReinforceMove)(void* self, SHINE_XY_TYPE*, int, void*, void*, char);
	typedef void(__thiscall* Hook_registerObsersver)(void* self, void*);
	typedef void(__thiscall* Hook_unregisterObsersver)(void* self, void*);
	typedef void(__thiscall* Hook_unregisterObsersvers)(void* self, void*);
	typedef void(__thiscall* Hook_notifyObservers)(void* self, void*, unsigned int, int);
	typedef bool(__thiscall* Hook_hasObserver)(void* self, void*);
	typedef void(__thiscall* Hook_sp_DoEmotion)(void* self, unsigned short, char);
	typedef void(__thiscall* Hook_sm_UseSkillSimple)(void* self, void*, void*, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_mobile_StopHere)(void* self);
	typedef void(__thiscall* Hook_so_ply_SendMoveFail)(void* self);
	typedef void(__thiscall* Hook_smo_ply_ReinforceStopHere)(void* self);
	typedef unsigned short(__thiscall* Hook_so_getDetectRange)(void* self);
	typedef void(__thiscall* Hook_so_ply_InvenWrite)(void* self, char*);
	typedef void(__thiscall* Hook_so_smo_AbStateKeepTimeAdd)(void* self, Enums::SubState, int);
	typedef int(__thiscall* Hook_so_smo_SPExhByAbState)(void* self);
	typedef char(__thiscall* Hook_so_smo_AbnormalStateAttribute)(void* self, void*);
	typedef int(__thiscall* Hook_so_smo_RangeEvation)(void* self);
	typedef char(__thiscall* Hook_so_smo_CanEnchant)(void* self, Enums::ABSTATEINDEX, int);
	typedef void* (__thiscall* Hook_so_ply_GetClientSession)(void* self);
	typedef char(__thiscall* Hook_so_ply_IsLink_OutMap_AndSendErrorMsg)(void* self);
	typedef char(__thiscall* Hook_so_ply_IsLink_In_MapAndSendErrorMsg)(void* self);
	typedef void(__thiscall* Hook_so_NPCRevive)(void* self, void*);
	typedef void(__thiscall* Hook_so_npc_FromTable)(void* self);
	typedef Raid* (__thiscall* Hook_so_GetRaid)(void* self);
	typedef void(__thiscall* Hook_so_SetRaid)(void* self, void*);
	typedef bool(__thiscall* Hook_so_GetInsDunGeonInRegNoAndType)(void* self, void*, unsigned int*);
	typedef void(__thiscall* Hook_so_mob_ReturnToRegen)(void* self);
	typedef void(__thiscall* Hook_so_FillBriefABState)(void* self, void*, char*);
	typedef void(__thiscall* Hook_so_ReviveByItem)(void* self);
	typedef void(__thiscall* Hook_so_AmpersandCommand_LevelUp)(void* self);
	typedef char(__thiscall* Hook_so_DiceItemPickInit)(void* self, void*);
	typedef char(__thiscall* Hook_so_DiceItemStart)(void* self, void*, bool, unsigned short*);
	typedef char(__thiscall* Hook_so_IsDiceGamePlay)(void* self);
	typedef void(__thiscall* Hook_so_SetHP)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_GtItemEffectMsg)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_SpamRecvDataFromWM)(void* self, void*);
	typedef void(__thiscall* Hook_so_SpamSendDataToCharDB)(void* self);
	typedef void(__thiscall* Hook_so_mob_SetLifeTime)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_SetAutoSaveTime)(void* self, unsigned int, int);
	typedef char(__thiscall* Hook_sp_FreeStat_Get_DecreaseNum)(void* self, void*);
	typedef char(__thiscall* Hook_sp_CharFreeStat_IsLock)(void* self);
	typedef void(__thiscall* Hook_sp_CharFreeStat_Lock)(void* self);
	typedef void(__thiscall* Hook_sp_CharFreeStat_UnLock)(void* self);
	typedef void(__thiscall* Hook_so_ply_FreeStat_Increase)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_FreeStat_Decrease)(void* self, void*);
	typedef void(__thiscall* Hook_so_BashStop)(void* self);
	typedef char(__thiscall* Hook_so_GetIsQuestRewardReq)(void* self);
	typedef void(__thiscall* Hook_so_SetIsQuestRewardReq)(void* self, char);
	typedef void(__thiscall* Hook_so_SetSpamerChatBan)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_Send_NC_CHARSAVE_2WLDMAN_SKILL_CMD)(void* self, NetworkCommand*);
	typedef char(__thiscall* Hook_so_mob_GetbUseNextSkill)(void* self);
	typedef void(__thiscall* Hook_so_mob_SetbUseNextSkill)(void* self, char);
	typedef char(__thiscall* Hook_so_Gamble_IsGambleHouse)(void* self);
	typedef void(__thiscall* Hook_so_Gamble_SetPrevMapName)(void* self, MapNameStruct);
	typedef void(__thiscall* Hook_so_Gamble_CharCoinData)(void* self, void*);
	typedef unsigned long long(__thiscall* Hook_so_Gamble_CurrentCoin)(void* self);
	typedef void(__thiscall* Hook_so_Gamble_StoreCoin)(void* self, unsigned long long);
	typedef void(__thiscall* Hook_so_Gamble_ChangeCoin)(void* self);
	typedef unsigned long long(__thiscall* Hook_so_Gamble_CurrentExchangedCoin)(void* self);
	typedef void(__thiscall* Hook_so_Gamble_StoreExchangedCoin)(void* self, unsigned long long);
	typedef void(__thiscall* Hook_so_Gamble_ChangeExchangedCoin)(void* self);
	typedef char(__thiscall* Hook_so_Gamble_CanJoinGamble)(void* self, void*);
	typedef char(__thiscall* Hook_so_Gamble_IsJoinThisGamble)(void* self, void*);
	typedef char(__thiscall* Hook_so_Gamble_IsJoinAnyGamble)(void* self, void*);
	typedef char(__thiscall* Hook_so_Gamble_SetGambleType)(void* self, void*);
	typedef char(__thiscall* Hook_so_Gamble_IsCanSessionCloseing)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mob_GetNextRoamingWaitTime)(void* self);
	typedef void(__thiscall* Hook_so_mob_SetNextRoamingWaitTime)(void* self, unsigned int);
	typedef char(__thiscall* Hook_so_mob_CheckNextRoamingWait)(void* self);
	typedef void(__thiscall* Hook_so_ply_EndofTrade)(void* self, unsigned short, int);
	typedef void(__thiscall* Hook_so_ply_ReactionNpcHandle)(void* self);
	typedef void(__thiscall* Hook_so_ply_NpcReaction)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_CapsuleItemOpenAck)(void* self, void*);
	typedef void(__thiscall* Hook_so_npc_SetLocation)(void* self, MapNameStruct, int, int, int);
	typedef void(__thiscall* Hook_so_ply_SlotMachineDBResult)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_IBurstJackPot)(void* self, unsigned long long);
	typedef char* (__thiscall* Hook_so_ply_GodOfSlotMachine)(void* self);
	typedef void(__thiscall* Hook_so_AITraining)(void* self, void*);
	typedef void(__thiscall* Hook_so_AILearn)(void* self, void*);
	typedef int(__thiscall* Hook_so_AIScriptFuncExec)(void* self, char*, void*);
	typedef int(__thiscall* Hook_so_AIScriptFuncExec1)(void* self, void*, void*, void*, void*);
	typedef int(__thiscall* Hook_so_AIScriptFuncExec2)(void* self, char*, char*);
	typedef char(__thiscall* Hook_so_LuaFunctionSet)(void* self, void*, void*, void*, const char*);
	typedef int(__thiscall* Hook_so_mob_SetWeaponAsScript)(void* self, char);
	typedef unsigned short(__thiscall* Hook_so_mob_CurrentTarget)(void* self);
	typedef char(__thiscall* Hook_so_mob_SkillRegistAtScript)(void* self, void*, unsigned short);
	typedef char(__thiscall* Hook_so_mob_ParamSetAtScript)(void* self, const char*, int);
	typedef char(__thiscall* Hook_so_mob_SkillBlastAtScript)(void* self, void*, unsigned short);
	typedef int(__thiscall* Hook_so_mob_GetAggroList)(void* self, void*, void*);
	typedef void* (__thiscall* Hook_so_ShineMobileObject)(void* self);
	typedef char(__thiscall* Hook_so_mob_SkillParameterSet)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_mob_SkillParameterSetAtScript)(void* self, void*);
	typedef void(__thiscall* Hook_so_mgcfld_FirstTickDelay)(void* self);
	typedef unsigned int(__thiscall* Hook_so_mob_GetMonEXP)(void* self);
	typedef void(__thiscall* Hook_so_mob_SetMobResist)(void* self, unsigned short*, unsigned short);
	typedef void(__thiscall* Hook_so_mob_SetEnemyDetect)(void* self, Enums::EnemyDetect);
	typedef void(__thiscall* Hook_so_mob_SetEnemyDetect1)(void* self, char*);
	typedef void(__thiscall* Hook_so_mob_SetIsPlayerSide)(void* self, int);
	typedef void(__thiscall* Hook_so_mob_IsItemDropSetAtScript)(void* self, char);
	typedef void(__thiscall* Hook_so_mob_SetItemDropMobID)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_SetMovePacket)(void* self, unsigned short, void*);
	typedef ShineObjectClass::ShinePlayer* (__thiscall* Hook_so_ToShinePlayer)(void* self);
	typedef char(__thiscall* Hook_so_GetItemLot)(void* self, const char*, unsigned long long*, char*);
	typedef char(__thiscall* Hook_so_ply_ToggleSkill_IsOn)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_ToggleSkill_On)(void* self, void*, SKILL_EMPOWER*);
	typedef void(__thiscall* Hook_so_ply_ToggleSkill_Off)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ToggleSkill_AllOff)(void* self);
	typedef void(__thiscall* Hook_so_ply_DmgCoolTimeDown)(void* self);
	typedef int(__thiscall* Hook_so_ply_GetDamageAbsorb)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetDamageAbsorb)(void* self, int);
	typedef int(__thiscall* Hook_so_ply_GetRemainingDamageAbsorb)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetRemainingDamageAbsorb)(void* self, int);
	typedef int(__thiscall* Hook_so_ply_CheckDamageAbsorption)(void* self, int);
	typedef char(__thiscall* Hook_smo_GetFlagDamageAbsorb)(void* self);
	typedef void(__thiscall* Hook_smo_SetFlagDamageAbsorb)(void* self, char);
	typedef void(__thiscall* Hook_smo_LightningWaveSkill)(void* self, void*, unsigned short, void*, void*, unsigned short, int);
	typedef void(__thiscall* Hook_so_ply_PassiveSetAbstate)(void* self, void*, void*, char, unsigned int);
	typedef void(__thiscall* Hook_so_ply_CardCollect)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_CardCollectBookMark)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_CardCollectReward)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_CollectCardOpen)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_CardRegist)(void* self, unsigned short, unsigned int, int, void*);
	typedef void(__thiscall* Hook_so_ply_CardBookmarkRegist)(void* self, void*);
	typedef void(__thiscall* Hook_so_InitAIScript)(void* self);
	typedef void* (__thiscall* Hook_so_mob_GetTopAggroTarget)(void* self);
	typedef void* (__thiscall* Hook_so_smo_GetRandomTarget_Object)(void* self, void*, unsigned int, void*);
	typedef char(__thiscall* Hook_so_smo_GetRandomTarget_Locate)(void* self, void*, SHINE_XY_TYPE*);
	typedef void(__thiscall* Hook_so_CameraMoveSendBriefInfo)(void* self, SHINE_XY_TYPE, int);
	typedef ShineObjectClass::ShineMob* (__thiscall* Hook_so_ToShineMob)(void* self);
	typedef void(__thiscall* Hook_so_ply_SendMenuOpenReq)(void* self, void*);
	typedef void(__thiscall* Hook_so_SetAnimation)(void* self, const char*);
	typedef void(__thiscall* Hook_so_ResetAnimation)(void* self);
	typedef void(__thiscall* Hook_so_SetForcedAnimation)(void* self, const char*);
	typedef void(__thiscall* Hook_so_mob_SetDeadDelayTime)(void* self, unsigned int);
	typedef char(__thiscall* Hook_so_mob_SkillParameterSet_WeaponIndex)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_IsRebirth)(void* self);
	typedef void(__thiscall* Hook_so_ply_setIsRebirth)(void* self, char);
	typedef int(__thiscall* Hook_so_ply_HealRate)(void* self);
	typedef void(__thiscall* Hook_so_ply_setHealRate)(void* self, int);
	typedef void(__thiscall* Hook_so_serv_SetRoamingData)(void* self, void*, int, int, SHINE_XY_TYPE);
	typedef char(__thiscall* Hook_so_serv_ServantRoaming)(void* self, int*, int*);
	typedef int(__thiscall* Hook_so_serv_GetRoamingType)(void* self);
	typedef void(__thiscall* Hook_so_serv_LastExplosionReady)(void* self);
	typedef void(__thiscall* Hook_so_ply_setSwingTime)(void* self, unsigned int);
	typedef unsigned int(__thiscall* Hook_so_ply_getSwingTime)(void* self);
	typedef char(__thiscall* Hook_so_MoverSystem_GetOff)(void* self, int);
	typedef char(__thiscall* Hook_so_MoverSystem_NoDamage)(void* self);
	typedef void* (__thiscall* Hook_so_MoverSystem_GetMover)(void* self);
	typedef void(__thiscall* Hook_so_MoverSystem_SetMover)(void* self, void*);
	typedef char(__thiscall* Hook_so_MoverSystem_GetMoverSlot)(void* self);
	typedef void(__thiscall* Hook_so_MoverSystem_SetMoverSlot)(void* self, char);
	typedef void(__thiscall* Hook_so_MoverSystem_GetLinkData)(void* self, void*);
	typedef void(__thiscall* Hook_so_MoverSystem_SetLinkData)(void* self, void*);
	typedef void(__thiscall* Hook_so_MoverSystem_ClearLinkData)(void* self);
	typedef void(__thiscall* Hook_so_MoverSystem_Feeding)(void* self);
	typedef char(__thiscall* Hook_so_MoverSystem_ChargedMoverNotHungry)(void* self);
	typedef void(__thiscall* Hook_so_smo_SetLocation)(void* self, SHINE_XY_TYPE, char);
	typedef void(__thiscall* Hook_so_smv_ClearMoverInfo)(void* self);
	typedef char(__thiscall* Hook_so_smv_SummonMover)(void* self, MapNameStruct*, int, int, int, unsigned int, unsigned int, unsigned long long);
	typedef void(__thiscall* Hook_so_smv_SetMaster_RegNum)(void* self, unsigned int);
	typedef unsigned int(__thiscall* Hook_so_smv_GetMaster_RegNum)(void* self);
	typedef void(__thiscall* Hook_so_smv_SetMaster_Object)(void* self, void*);
	typedef void* (__thiscall* Hook_so_smv_GetMaster_Object)(void* self);
	typedef void(__thiscall* Hook_so_smv_SetMoverItemInfo)(void* self, void*, void*);
	typedef char(__thiscall* Hook_so_smv_GetOn)(void* self, void*, int);
	typedef char(__thiscall* Hook_so_smv_GetOff)(void* self, void*, int);
	typedef void(__thiscall* Hook_so_smv_GetOffAll)(void* self, int);
	typedef unsigned short(__thiscall* Hook_so_smv_CanUseFeedItem)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_smv_Feeding)(void* self);
	typedef char(__thiscall* Hook_so_smv_MoveWalk)(void* self, void*, void*);
	typedef char(__thiscall* Hook_so_smv_MoveRun)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_smv_MoveStop)(void* self, void*, void*);
	typedef char(__thiscall* Hook_so_smv_GetMaxSlotNum)(void* self);
	typedef void* (__thiscall* Hook_so_smv_GetPassenger)(void* self, char);
	typedef void(__thiscall* Hook_so_smv_PassengerNotice)(void* self, const char*);
	typedef unsigned int(__thiscall* Hook_so_smv_GetMoverID)(void* self);
	typedef char(__thiscall* Hook_so_smv_GetMyBookingSlot)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_smv_SkillBash_Object)(void* self, unsigned short, unsigned short, void*);
	typedef void(__thiscall* Hook_so_smv_SkillBash_Location)(void* self, unsigned short, SHINE_XY_TYPE, void*);
	typedef char(__thiscall* Hook_so_smv_MasterSetAbsCheck)(void* self, void*, Enums::ABSTATEINDEX, int, void*, unsigned int, int, int, int, void*, void*);
	typedef void(__thiscall* Hook_so_smv_MasterResetAbsCheck)(void* self, Enums::ABSTATEINDEX);
	typedef char(__thiscall* Hook_so_smv_GetMoverGrade)(void* self);
	typedef void(__thiscall* Hook_so_smv_SetMoverGrade)(void* self, char);
	typedef void(__thiscall* Hook_so_ply_getBanditBriefinfo)(void* self, void*);
	typedef int(__thiscall* Hook_so_ply_CheckCharType)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ArrangeInvenInit)(void* self);
	typedef char(__thiscall* Hook_so_ply_ArrangeInvenDelayCheck)(void* self);
	typedef int(__thiscall* Hook_so_ply_IsArrangeInven)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetArrangeInven)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_ArrangeInven)(void* self);
	typedef void(__thiscall* Hook_so_Send_NC_CHARSAVE_2WLDMAN_QUEST_DONE_CMD)(void* self, NetworkCommand*);
	typedef void(__thiscall* Hook_so_AccountStorageAnywhereOpen)(void* self);
	typedef void(__thiscall* Hook_so_AccountStorageAnywhereClose)(void* self);
	typedef int(__thiscall* Hook_so_ply_JobChangeDamageUp)(void* self, void*, int);
	typedef int(__thiscall* Hook_so_ply_IsEquipItem)(void* self, unsigned int, unsigned int);
	typedef int(__thiscall* Hook_so_ply_DecreaseDmgPassiveSkill)(void* self, void*, int);
	typedef void* (__thiscall* Hook_so_ply_GetQuestZone)(void* self);
	typedef void(__thiscall* Hook_so_ply_SendFieldAttribute)(void* self);
	typedef void(__thiscall* Hook_so_mob_SetAnimationLevel)(void* self, char);
	typedef char(__thiscall* Hook_so_mob_GetAnimationLevel)(void* self);
	typedef char(__thiscall* Hook_so_mob_IsNPC)(void* self);
	typedef void(__thiscall* Hook_so_SendSpeedInformation)(void* self, char);
	typedef void(__thiscall* Hook_smo_GetMoveState)(void* self);
	typedef unsigned int(__thiscall* Hook_smo_GetMoveStateStartTime)(void* self);
	typedef void(__thiscall* Hook_so_ply_PartyZoneJoinCmd)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_PartyZoneLeaveCmd)(void* self);
	typedef void(__thiscall* Hook_so_ply_EquipmentChange)(void* self, unsigned short, int, void*, char);
	typedef void(__thiscall* Hook_so_ply_ViewSlot_Equip)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_ply_ViewSlot_UnEquip)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_ViewSlot_UnEquipAll)(void* self, char);
	typedef void(__thiscall* Hook_so_ply_ViewSlot_EquipInfoSend)(void* self);
	typedef void(__thiscall* Hook_so_ply_ViewSlot_EquipInfoClear)(void* self);
	typedef void(__thiscall* Hook_so_ply_DecoActList_Cehck)(void* self);
	typedef void(__thiscall* Hook_so_ply_PlaySound)(void* self, const char*);
	typedef void(__thiscall* Hook_so_ply_ShowCinematicText)(void* self, const char*);
	typedef void(__thiscall* Hook_so_ply_EndCinematicText)(void* self);
	typedef void(__thiscall* Hook_so_ply_EffectMsg)(void* self, unsigned int);
	typedef void(__thiscall* Hook_so_ply_Sen_InitLP)(void* self);
	typedef unsigned int(__thiscall* Hook_so_ply_Sen_GetLP)(void* self);
	typedef unsigned int(__thiscall* Hook_so_ply_Sen_MaxLP)(void* self);
	typedef void(__thiscall* Hook_so_ply_Sen_GainLP)(void* self, int);
	typedef void(__thiscall* Hook_so_ply_Sen_LostLP)(void* self, int);
	typedef unsigned int(__thiscall* Hook_so_ply_Sen_GetLPRecover)(void* self);
	typedef void(__thiscall* Hook_so_ply_Sen_RecalcLPRecover)(void* self);
	typedef unsigned int(__thiscall* Hook_so_ply_Sen_GetLPRecoverInterval)(void* self);
	typedef char(__thiscall* Hook_so_ply_Sen_LP_Tick)(void* self);
	typedef void(__thiscall* Hook_so_RecoverAlreadyDead)(void* self);
	typedef int(__thiscall* Hook_so_smo_LastDamageOperation)(void* self, int, bool);
	typedef unsigned long long(__thiscall* Hook_so_ply_MakeLayerRegNum)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_ply_MoveNewLayer)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_ply_MoveOtherLayer)(void* self, unsigned long long);
	typedef void(__thiscall* Hook_so_ply_DeleteObject_AllOfRange)(void* self);
	typedef void(__thiscall* Hook_so_ply_MoveNewLayer_AllInMap)(void* self, void*, void*);
	typedef void(__thiscall* Hook_so_ply_MoveOtherLayer_AllInMap)(void* self, unsigned long long);
	typedef void(__thiscall* Hook_so_ply_DeleteObject_AllInMap)(void* self);
	typedef void(__thiscall* Hook_so_ply_LayerMoverRideOn)(void* self, void*, int);
	typedef void(__thiscall* Hook_so_ply_SendBriefInfo_MoveLayer)(void* self);
	typedef void(__thiscall* Hook_so_smo_StaticDamage)(void* self, int);
	typedef void(__thiscall* Hook_so_serv_SetFlag)(void* self, const char*, char);
	typedef void(__thiscall* Hook_so_serv_InitFlag)(void* self);
	typedef void(__thiscall* Hook_so_serv_SetMobCanDamageTo)(void* self, int);
	typedef int(__thiscall* Hook_so_serv_GetMobCanDamageTo)(void* self);
	typedef void(__thiscall* Hook_so_mob_SendReallyKill)(void* self);
	typedef int(__thiscall* Hook_so_ply_LoginTutorialMap)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetTutorialInfo)(void* self, void*);
	typedef void* (__thiscall* Hook_so_ply_GetTutorialInfo)(void* self);
	typedef void(__thiscall* Hook_so_ply_LevelUpAtLua)(void* self);
	typedef void(__thiscall* Hook_so_SetKQTeamType)(void* self, char);
	typedef char(__thiscall* Hook_so_GetKQTeamType)(void* self);
	typedef char(__thiscall* Hook_so_smo_TargetIsEnemyKQTeam)(void* self, void*);
	typedef char(__thiscall* Hook_so_ply_IsKQJoiner)(void* self);
	typedef void(__thiscall* Hook_so_ply_SendCanUseReviveItem)(void* self);
	typedef void(__thiscall* Hook_so_ply_ItemBuyItemMoney)(void* self, PROTO_NC_ITEM_BUY_REQ*, unsigned short, unsigned int);
	typedef void(__thiscall* Hook_so_ply_DePorymorph)(void* self);
	typedef void(__thiscall* Hook_so_drpitm_bQuestDropItem_Set)(void* self, char);
	typedef char(__thiscall* Hook_so_drpitm_bQuestDropItem_Get)(void* self);
	typedef char(__thiscall* Hook_so_ply_QuestItemCheck)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_ply_GetChatFontColorID)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetChatFontColorID)(void* self, char);
	typedef char(__thiscall* Hook_so_ply_GetChatBalloonColorID)(void* self);
	typedef void(__thiscall* Hook_so_ply_SetChatBalloonColorID)(void* self, char);
	typedef void(__thiscall* Hook_so_ply_ChatColorInfoApply)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_ChatColorInfoClear)(void* self, void*);
	typedef void* (__thiscall* Hook_so_PetSystem_GetPet)(void* self);
	typedef void(__thiscall* Hook_so_SetAnimationBriefInfo)(void* self, const char*);
	typedef void* (__thiscall* Hook_so_mob_FindLooter)(void* self, void* result);
	typedef void(__thiscall* Hook_so_ply_SetUseItemMinimon)(void* self, void*);
	typedef char(__thiscall* Hook_so_ply_UseItemMinimon_IsUse)(void* self);
	typedef void(__thiscall* Hook_so_ply_UseItemMinimon_Off)(void* self);
	typedef void(__thiscall* Hook_so_ply_UseItemMinimon_SlotItemCheck)(void* self, unsigned short);
	typedef char(__thiscall* Hook_so_IsAlliance)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_SetSellItemInfo)(void* self, void*);
	typedef void(__thiscall* Hook_so_ply_SendSellItemInfo_Client)(void* self);
	typedef char(__thiscall* Hook_so_ply_CanItemRepurchase)(void* self);
	typedef void(__thiscall* Hook_so_ply_SellItemList_Insert)(void* self, SHINE_ITEM_REGISTNUMBER, void*);
	typedef void(__thiscall* Hook_so_ply_SellItemList_Delete)(void* self, unsigned short);
	typedef void(__thiscall* Hook_so_Init)(void* self);
	typedef void(__thiscall* Hook_so_smo_SetStaticWalkSpeed)(void* self, char, unsigned short);
	typedef void(__thiscall* Hook_so_smo_SetStaticRunSpeed)(void* self, char, unsigned short);
	typedef char(__thiscall* Hook_so_smo_IsStaticWalkSpeed)(void* self);
	typedef char(__thiscall* Hook_so_smo_IsStaticRunSpeed)(void* self);
	typedef unsigned short(__thiscall* Hook_so_smo_GetStaticWalkSpeed)(void* self);
	typedef unsigned short(__thiscall* Hook_so_smo_GetStaticRunSpeed)(void* self);

	struct ShineObjectVtable
	{
		Hook_GetRTTI Org_GetRTTI;
		destructor Destructor;
		int gap8[115];
		clear_dice_betting_info ClearDiceBettingInfo;
		Hook_so_mh_SetDiceHistory Org_so_mh_SetDiceHistory;
		Hook_so_mh_ClearGamerBettingInfo Org_so_mh_ClearGamerBettingInfo;
		Hook_so_mh_GetTaiSaiGamerCnt Org_so_mh_GetTaiSaiGamerCnt;
		Hook_so_mh_RankSort Org_so_mh_RankSort;
		Hook_so_mh_SetIsCreateDice Org_so_mh_SetIsCreateDice;
		Hook_so_mh_IsCreateDice Org_so_mh_IsCreateDice;
		Hook_so_mh_SetIsDeleteDice Org_so_mh_SetIsDeleteDice;
		Hook_so_mh_IsDeleteDice Org_so_mh_IsDeleteDice;
		Hook_so_mh_SetIsBlowGame Org_so_mh_SetIsBlowGame;
		Hook_so_mh_IsBlowGame Org_so_mh_IsBlowGame;
		Hook_so_mh_SetIsLeaveOwner Org_so_mh_SetIsLeaveOwner;
		Hook_so_mh_IsLeaveOwner Org_so_mh_IsLeaveOwner;
		Hook_so_mh_ExcuteLeaveRoom Org_so_mh_ExcuteLeaveRoom;
		Hook_so_mh_ExcuteLeaveGame Org_so_mh_ExcuteLeaveGame;
		Hook_so_mh_ExcuteBlowGame Org_so_mh_ExcuteBlowGame;
		Hook_so_mh_IsActiveDiceTaiSai Org_so_mh_IsActiveDiceTaiSai;
		Hook_so_mh_SendTaiSaiGameInfo Org_so_mh_SendTaiSaiGameInfo;
		Hook_so_mh_SendTaiSaiBettingInfo Org_so_mh_SendTaiSaiBettingInfo;
		Hook_so_mh_DiceTaiSai_CanEnter Org_so_mh_DiceTaiSai_CanEnter;
		Hook_so_mh_DiceTaiSai_Enter Org_so_mh_DiceTaiSai_Enter;
		Hook_so_mh_DiceTaiSai_BroadEnter Org_so_mh_DiceTaiSai_BroadEnter;
		Hook_so_mh_DiceTaiSai_Out Org_so_mh_DiceTaiSai_Out;
		Hook_so_mh_DiceTaiSai_BroadOut Org_so_mh_DiceTaiSai_BroadOut;
		Hook_so_mh_DiceTaiSai_ModeChange Org_so_mh_DiceTaiSai_ModeChange;
		Hook_so_mh_DiceTaiSai_BroadModeChange Org_so_mh_DiceTaiSai_BroadModeChange;
		Hook_so_mh_DiceTaiSai_ModeChangeLeave Org_so_mh_DiceTaiSai_ModeChangeLeave;
		Hook_so_mh_DiceTaiSai_BroadModeChangeLeave Org_so_mh_DiceTaiSai_BroadModeChangeLeave;
		Hook_so_mh_DiceTaiSai_BroadSetTimer Org_so_mh_DiceTaiSai_BroadSetTimer;
		Hook_so_mh_DiceTaiSai_CanBetting Org_so_mh_DiceTaiSai_CanBetting;
		Hook_so_mh_DiceTaiSai_Betting Org_so_mh_DiceTaiSai_Betting;
		Hook_so_mh_DiceTaiSai_BroadBetting Org_so_mh_DiceTaiSai_BroadBetting;
		Hook_so_mh_DiceTaiSai_CanBettingCancel Org_so_mh_DiceTaiSai_CanBettingCancel;
		Hook_so_mh_DiceTaiSai_BettingCancel Org_so_mh_DiceTaiSai_BettingCancel;
		Hook_so_mh_DiceTaiSai_BroadBettingCancel Org_so_mh_DiceTaiSai_BroadBettingCancel;
		Hook_so_mh_DiceTaiSai_CanDiceRoll Org_so_mh_DiceTaiSai_CanDiceRoll;
		Hook_so_mh_DiceTaiSai_CanAutoDiceRoll Org_so_mh_DiceTaiSai_CanAutoDiceRoll;
		Hook_so_mh_DiceTaiSai_DiceRoll Org_so_mh_DiceTaiSai_DiceRoll;
		Hook_so_mh_DiceTaiSai_BroadDiceRoll Org_so_mh_DiceTaiSai_BroadDiceRoll;
		Hook_so_mh_DiceTaiSai_MoneyResult_DiceRoll Org_so_mh_DiceTaiSai_MoneyResult_DiceRoll;
		Hook_so_mh_DiceTaiSai_Result_DiceRoll Org_so_mh_DiceTaiSai_Result_DiceRoll;
		Hook_so_mh_DiceTaiSai_ResultLog_DiceRoll Org_so_mh_DiceTaiSai_ResultLog_DiceRoll;
		Hook_so_mh_DiceTaiSai_BroadResult_DiceRoll Org_so_mh_DiceTaiSai_BroadResult_DiceRoll;
		Hook_so_mh_DiceTaiSai_BroadEmotion_DiceRoll Org_so_mh_DiceTaiSai_BroadEmotion_DiceRoll;
		Hook_so_mh_DiceTaiSai_PrepareNextGame Org_so_mh_DiceTaiSai_PrepareNextGame;
		Hook_so_mh_DiceTaiSai_GetExpectIncomeMoney Org_so_mh_DiceTaiSai_GetExpectIncomeMoney;
		Hook_so_mh_DiceTaiSai_GetReceiptIncomeMoney Org_so_mh_DiceTaiSai_GetReceiptIncomeMoney;
		Hook_so_mh_DiceTaiSai_GetRank Org_so_mh_DiceTaiSai_GetRank;
		Hook_so_mh_DiceTaiSai_SendRank Org_so_mh_DiceTaiSai_SendRank;
		Hook_so_mh_DiceTaiSai_BroadLargeAmount Org_so_mh_DiceTaiSai_BroadLargeAmount;
		Hook_so_mh_DiceTaiSai_BroadGameFold Org_so_mh_DiceTaiSai_BroadGameFold;
		Hook_so_mh_DiceTaiSai_GetGameStatus Org_so_mh_DiceTaiSai_GetGameStatus;
		Hook_so_mh_DiceTaiSai_GetGameMode Org_so_mh_DiceTaiSai_GetGameMode;
		Hook_so_mh_SetDiceRewardMoney Org_so_mh_SetDiceRewardMoney;
		Hook_so_ply_MH_GetFurnitureEmotionInfo Org_so_ply_MH_GetFurnitureEmotionInfo;
		Hook_so_ply_MH_InitFurnitureEmotionInfo Org_so_ply_MH_InitFurnitureEmotionInfo;
		Hook_so_ply_MH_IsFurnitureEmotion Org_so_ply_MH_IsFurnitureEmotion;
		Hook_so_ply_MH_IsFurnitureEmotionPosition Org_so_ply_MH_IsFurnitureEmotionPosition;
		Hook_so_ply_MH_IsFurnitureEmotionNo Org_so_ply_MH_IsFurnitureEmotionNo;
		Hook_so_ply_MH_GetFurnitureEmotion Org_so_ply_MH_GetFurnitureEmotion;
		Hook_so_ply_MH_GetFurnitureEmotionPosition Org_so_ply_MH_GetFurnitureEmotionPosition;
		Hook_so_ply_MH_GetFurnitureEmotionNo Org_so_ply_MH_GetFurnitureEmotionNo;
		Hook_so_ply_MH_SetFurnitureEmotion Org_so_ply_MH_SetFurnitureEmotion;
		Hook_so_ply_MH_SetFurnitureEmotionPosition Org_so_ply_MH_SetFurnitureEmotionPosition;
		Hook_so_ply_MH_SetFurnitureEmotionNo Org_so_ply_MH_SetFurnitureEmotionNo;
		Hook_so_mh_CanFurnitureEmotion Org_so_mh_CanFurnitureEmotion;
		Hook_so_mh_IsFurnitureEmotion Org_so_mh_IsFurnitureEmotion;
		Hook_so_mh_FurnitureEmotionStop Org_so_mh_FurnitureEmotionStop;
		Hook_so_mh_SendInnerPlayerFurnitureEmotion Org_so_mh_SendInnerPlayerFurnitureEmotion;
		Hook_so_PacketBufferFlush Org_so_PacketBufferFlush;
		Hook_so_SetRegistNumber Org_so_SetRegistNumber;
		Hook_so_SetSocketSession Org_so_SetSocketSession;
		Hook_so_EncSeedSet Org_so_EncSeedSet;
		Hook_so_GetDataSocketStream Org_so_GetDataSocketStream;
		Hook_so_GetGameSocketStream Org_so_GetGameSocketStream;
		Hook_so_IsEmpty Org_so_IsEmpty;
		Hook_so_SendProtocol Org_so_SendProtocol;
		Hook_so_SendErrorCode Org_so_SendErrorCode;
		Hook_so_FirstActionAfterSocketConnect Org_so_FirstActionAfterSocketConnect;
		Hook_so_CloseByLink Org_so_CloseByLink;
		Hook_so_GetLastUpgradeInfo Org_so_GetLastUpgradeInfo;
		Hook_so_door_DoorAction Org_so_door_DoorAction;
		Hook_so_TradeStructure Org_so_TradeStructure;
		Hook_so_TradeBoard Org_so_TradeBoard;
		Hook_so_GetWaitTradeResFromDB Org_so_GetWaitTradeResFromDB;
		Hook_so_SetWaitTradeResFromDB Org_so_SetWaitTradeResFromDB;
		Hook_so_ply_ItemMakeItem Org_so_ply_ItemMakeItem;
		Hook_so_SetPossibleNewConnect Org_so_SetPossibleNewConnect;
		Hook_so_GetPossibleNewConnect Org_so_GetPossibleNewConnect;
		Hook_so_RefreshWMSSocket Org_so_RefreshWMSSocket;
		Hook_so_Unmark Org_so_Unmark;
		Hook_so_GetWMSHandle Org_so_GetWMSHandle;
		Hook_so_GetCharRegistNumber Org_so_GetCharRegistNumber;
		Hook_so_GetUserRegistNumber Org_so_GetUserRegistNumber;
		Hook_so_NC_ITEMDB_ADMINCREATEFAIL_ACK Org_so_NC_ITEMDB_ADMINCREATEFAIL_ACK;
		Hook_so_NC_ITEMDB_fail Org_so_NC_ITEMDB_fail;
		Hook_so_NC_ITEMDB_USE_ACK Org_so_NC_ITEMDB_USE_ACK;
		Hook_so_BackupParameter Org_so_BackupParameter;
		Hook_so_RecalcEquipParam Org_so_RecalcEquipParam;
		Hook_so_RecalcAbstateParam Org_so_RecalcAbstateParam;
		Hook_so_RecalcPassiveParam Org_so_RecalcPassiveParam;
		Hook_so_RecalcLastParam Org_so_RecalcLastParam;
		Hook_so_ply_ItemEffect Org_so_ply_ItemEffect;
		Hook_so_ply_ChargedBuff Org_so_ply_ChargedBuff;
		Hook_so_ply_NewSkillCoolTime Org_so_ply_NewSkillCoolTime;
		Hook_so_ply_InitFreeStat Org_so_ply_InitFreeStat;
		Hook_so_ply_InitSkillEmpow Org_so_ply_InitSkillEmpow;
		Hook_so_ply_SkillEmpowerSetResult Org_so_ply_SkillEmpowerSetResult;
		Hook_so_ply_IncNGet_PKCount Org_so_ply_IncNGet_PKCount;
		Hook_so_ply_SavePKCount Org_so_ply_SavePKCount;
		Hook_so_SaveLocation Org_so_SaveLocation;
		Hook_so_SaveLevel Org_so_SaveLevel;
		Hook_so_SaveQuestDoing Org_so_SaveQuestDoing;
		Hook_so_SaveQuestDoing1 Org_so_SaveQuestDoing1;
		Hook_so_SaveQuestRead Org_so_SaveQuestRead;
		Hook_so_SaveQuestRepeat Org_so_SaveQuestRepeat;
		Hook_so_SaveAbstate Org_so_SaveAbstate;
		Hook_so_SaveSkill Org_so_SaveSkill;
		Hook_so_SaveStat Org_so_SaveStat;
		Hook_so_SaveGameData Org_so_SaveGameData;
		Hook_so_SaveItem Org_so_SaveItem;
		Hook_so_SaveItem_Part Org_so_SaveItem_Part;
		Hook_so_SaveChestInfo Org_so_SaveChestInfo;
		Hook_so_SaveCharTitle Org_so_SaveCharTitle;
		Hook_so_SaveMisc2WMS Org_so_SaveMisc2WMS;
		Hook_so_SaveToDB_CharTitle Org_so_SaveToDB_CharTitle;
		Hook_so_ply_FindJobDungeon Org_so_ply_FindJobDungeon;
		Hook_so_ply_2JobDungeon Org_so_ply_2JobDungeon;
		Hook_so_ply_FirstJobChange Org_so_ply_FirstJobChange;
		Hook_so_ply_SilverWingCoolTime Org_so_ply_SilverWingCoolTime;
		Hook_so_ply_MakeMiniHouse Org_so_ply_MakeMiniHouse;
		Hook_so_ply_SendBoothSize Org_so_ply_SendBoothSize;
		Hook_so_AbnormalState_IsSet Org_so_AbnormalState_IsSet;
		Hook_so_AbnormalState_Strength Org_so_AbnormalState_Strength;
		Hook_so_AbnormalState_RestTime Org_so_AbnormalState_RestTime;
		Hook_so_AbnormalState_Inform Org_so_AbnormalState_Inform;
		Hook_so_RetrateFromMap Org_so_RetrateFromMap;
		Hook_so_RetreatFromMapByImmeditely Org_so_RetreatFromMapByImmeditely;
		Hook_so_LinkToReserv Org_so_LinkToReserv;
		Hook_so_TeleportReserv Org_so_TeleportReserv;
		Hook_sp_IsLockedRefundReq Org_sp_IsLockedRefundReq;
		Hook_sp_LockRefundReq Org_sp_LockRefundReq;
		Hook_sp_UnlockRefundReq Org_sp_UnlockRefundReq;
		Hook_sp_IsLockedRefundCancelReq Org_sp_IsLockedRefundCancelReq;
		Hook_sp_LockRefundCancelReq Org_sp_LockRefundCancelReq;
		Hook_sp_UnlockRefundCancelReq Org_sp_UnlockRefundCancelReq;
		Hook_sp_lastpickuptime Org_sp_lastpickuptime;
		Hook_so_GetCharacterTitle Org_so_GetCharacterTitle;
		Hook_so_GetStatDistStr Org_so_GetStatDistStr;
		Hook_so_GetBattleStat Org_so_GetBattleStat;
		Hook_so_GetTargetInfo Org_so_GetTargetInfo;
		Hook_so_parameter Org_so_parameter;
		Hook_so_ply_CurrentMoney Org_so_ply_CurrentMoney;
		Hook_so_ply_CurrentExp Org_so_ply_CurrentExp;
		Hook_so_ply_CurrentFame Org_so_ply_CurrentFame;
		Hook_so_ply_StoreMoney Org_so_ply_StoreMoney;
		Hook_so_ply_StoreFame Org_so_ply_StoreFame;
		Hook_so_ply_ChangeCen Org_so_ply_ChangeCen;
		Hook_so_ply_ChangeFame Org_so_ply_ChangeFame;
		Hook_so_ply_SaveFame Org_so_ply_SaveFame;
		Hook_so_ply_DepositAck Org_so_ply_DepositAck;
		Hook_so_ply_WithdrawAck Org_so_ply_WithdrawAck;
		Hook_so_ply_GuildStorageWithdrawAck Org_so_ply_GuildStorageWithdrawAck;
		Hook_so_ply_InvenCellReleaser_PointStone Org_so_ply_InvenCellReleaser_PointStone;
		Hook_so_ply_InvenCellReleaser_QuestReward Org_so_ply_InvenCellReleaser_QuestReward;
		Hook_so_ply_FreeStatStr Org_so_ply_FreeStatStr;
		Hook_so_ply_FreeStatInt Org_so_ply_FreeStatInt;
		Hook_so_ply_FreeStatDex Org_so_ply_FreeStatDex;
		Hook_so_ply_FreeStatCon Org_so_ply_FreeStatCon;
		Hook_so_ply_FreeStatMen Org_so_ply_FreeStatMen;
		Hook_so_ItemInventory Org_so_ItemInventory;
		Hook_so_SpyAgent Org_so_SpyAgent;
		Hook_so_CurMode Org_so_CurMode;
		Hook_so_ply_ReinforceFoldtent Org_so_ply_ReinforceFoldtent;
		Hook_so_ply_InventorySize Org_so_ply_InventorySize;
		Hook_so_ply_StorageSize Org_so_ply_StorageSize;
		Hook_so_ply_StreetBoothSlot Org_so_ply_StreetBoothSlot;
		Hook_so_ply_ChargedEffectContainer Org_so_ply_ChargedEffectContainer;
		Hook_so_CharacterClass Org_so_CharacterClass;
		Hook_so_Getabstatebit Org_so_Getabstatebit;
		Hook_so_RemakeHandle Org_so_RemakeHandle;
		Hook_so_PacketEncryptClass Org_so_PacketEncryptClass;
		Hook_so_Routine Org_so_Routine;
		Hook_so_ply_BanByServerDisconnect Org_so_ply_BanByServerDisconnect;
		Hook_so_StoreCharData Org_so_StoreCharData;
		Hook_so_OverlapFactor Org_so_OverlapFactor;
		Hook_so_LoginLocation Org_so_LoginLocation;
		Hook_so_datasync Org_so_datasync;
		Hook_so_FillBriefInformation Org_so_FillBriefInformation;
		Hook_so_SendMyBriefInfo Org_so_SendMyBriefInfo;
		Hook_so_SetGateBriefInform Org_so_SetGateBriefInform;
		Hook_so_ObjectType Org_so_ObjectType;
		Hook_so_AdministratorLevel Org_so_AdministratorLevel;
		Hook_so_GetLevel Org_so_GetLevel;
		Hook_so_GetClass Org_so_GetClass;
		Hook_so_TargetType Org_so_TargetType;
		Hook_so_Heal Org_so_Heal;
		Hook_so_GetHP Org_so_GetHP;
		Hook_so_GetSP Org_so_GetSP;
		Hook_so_MaxHP Org_so_MaxHP;
		Hook_so_MaxSP Org_so_MaxSP;
		Hook_so_LostSP Org_so_LostSP;
		Hook_so_GainSP Org_so_GainSP;
		Hook_so_LostHP Org_so_LostHP;
		Hook_so_GainHP Org_so_GainHP;
		Hook_so_attackspeed1000 Org_so_attackspeed1000;
		Hook_so_attackspeed1000_packet Org_so_attackspeed1000_packet;
		Hook_so_AttackRange Org_so_AttackRange;
		Hook_so_WalkSpeed Org_so_WalkSpeed;
		Hook_so_RunSpeed Org_so_RunSpeed;
		Hook_so_BroadcastLogout Org_so_BroadcastLogout;
		Hook_so_fullbufferitem Org_so_fullbufferitem;
		Hook_so_fullbufferitem_box Org_so_fullbufferitem_box;
		Hook_so_RecalcAbstateParamReady Org_so_RecalcAbstateParamReady;
		Hook_so_mobile_AbstateList Org_so_mobile_AbstateList;
		Hook_so_Chat Org_so_Chat;
		Hook_so_Shout Org_so_Shout;
		Hook_so_drpitm_CanLootingBitSet Org_so_drpitm_CanLootingBitSet;
		Hook_so_drpitm_CanLooting Org_so_drpitm_CanLooting;
		Hook_so_drpitm_IsIndividualType Org_so_drpitm_IsIndividualType;
		Hook_so_ItemDrop Org_so_ItemDrop;
		Hook_so_drpitm_itemview Org_so_drpitm_itemview;
		Hook_so_itempicked Org_so_itempicked;
		Hook_so_PartyRegistNumber GetPartyRegistNumber;
		Hook_so_GetRaidNumber Org_so_GetRaidNumber;
		Hook_so_SetRaidNumber Org_so_SetRaidNumber;
		Hook_so_GetPartyGroup Org_so_GetPartyGroup;
		Hook_so_PartyRegistNumber_InAttack Org_so_PartyRegistNumber_InAttack;
		Hook_so_GetCharRegistNumber_ItemLooter Org_so_GetCharRegistNumber_ItemLooter;
		Hook_so_GetZoneHandle_ItemLooter GetZoneHandle;
		Hook_so_CharName Org_so_CharName;
		Hook_so_extradata Org_so_extradata;
		Hook_so_SetParty Org_so_SetParty;
		Hook_so_ply_SendPartyInformTo Org_so_ply_SendPartyInformTo;
		Hook_so_allparametercalculate Org_so_allparametercalculate;
		Hook_so_attack Org_so_attack;
		Hook_so_attack1 Org_so_attack1;
		Hook_so_SetLastBattle Org_so_SetLastBattle;
		Hook_so_isinbattle Org_so_isinbattle;
		Hook_so_SlantedFlag Org_so_SlantedFlag;
		Hook_so_smash Org_so_smash;
		Hook_so_Bash Org_so_Bash;
		Hook_so_skillsmash Org_so_skillsmash;
		Hook_so_SkillEnchant Org_so_SkillEnchant;
		Hook_so_SkillCure Org_so_SkillCure;
		Hook_so_Dispel Org_so_Dispel;
		Hook_so_CanSkillTarget Org_so_CanSkillTarget;
		Hook_so_MoveByServer Org_so_MoveByServer;
		Hook_so_recoverhp Org_so_recoverhp;
		Hook_so_recoversp Org_so_recoversp;
		Hook_so_KilledBy Org_so_KilledBy;
		Hook_so_DamagedBy Org_so_DamagedBy;
		Hook_so_GetExperienceFromMob Org_so_GetExperienceFromMob;
		Hook_so_briefequipset Org_so_briefequipset;
		Hook_so_EqualSetitemIndexNameCount Org_so_EqualSetitemIndexNameCount;
		Hook_so_GetItemActionObserves Org_so_GetItemActionObserves;
		Hook_so_ItemActonAbstateApp Org_so_ItemActonAbstateApp;
		Hook_so_AddItemAction Org_so_AddItemAction;
		Hook_so_DelItemAction Org_so_DelItemAction;
		Hook_so_ply_ItemAction_UnEquip Org_so_ply_ItemAction_UnEquip;
		Hook_so_ply_EnchantActionUse Org_so_ply_EnchantActionUse;
		Hook_so_ply_GuildStoreFill Org_so_ply_GuildStoreFill;
		Hook_so_ply_GuildStoreGradeFill Org_so_ply_GuildStoreGradeFill;
		Hook_so_ply_isGuildStoreGrade Org_so_ply_isGuildStoreGrade;
		Hook_so_weapontitle Org_so_weapontitle;
		Hook_so_Disconnect Org_so_Disconnect;
		Hook_so_banning Org_so_banning;
		Hook_so_LinkTo Org_so_LinkTo;
		Hook_so_ply_ChangeCell Org_so_ply_ChangeCell;
		Hook_so_ply_ChangeBriefInfo Org_so_ply_ChangeBriefInfo;
		Hook_so_mobile_Move2Where Org_so_mobile_Move2Where;
		Hook_so_mobile_IsInMoving Org_so_mobile_IsInMoving;
		Hook_so_mob_RegenLocation Org_so_mob_RegenLocation;
		Hook_so_mob_LastHittedLocation Org_so_mob_LastHittedLocation;
		Hook_so_mob_ChaseRangeSquar Org_so_mob_ChaseRangeSquar;
		Hook_so_LearnPassive Org_so_LearnPassive;
		Hook_so_LearnSkill Org_so_LearnSkill;
		Hook_so_TradeBoardreset Org_so_TradeBoardreset;
		Hook_so_tradestart Org_so_tradestart;
		Hook_so_tradepropose_timecheck Org_so_tradepropose_timecheck;
		Hook_so_AbnormalState_Resist Org_so_AbnormalState_Resist;
		Hook_so_AbnormalState_Set Org_so_AbnormalState_Set;
		Hook_so_AbnormalState_Set_CharAllMode Org_so_AbnormalState_Set_CharAllMode;
		Hook_so_AbnormalState_Set_Simple Org_so_AbnormalState_Set_Simple;
		Hook_so_AbnormalState_Set_Simple1 Org_so_AbnormalState_Set_Simple1;
		Hook_so_AbnormalState_Set_SS_SETABSTATEME Org_so_AbnormalState_Set_SS_SETABSTATEME;
		Hook_so_EscapeFromTarget Org_so_EscapeFromTarget;
		Hook_so_AbnormalState_Reset Org_so_AbnormalState_Reset;
		Hook_so_batobj_DamageReserv Org_so_batobj_DamageReserv;
		Hook_so_batobj_DamageApply Org_so_batobj_DamageApply;
		Hook_so_batobj_GetDamage Org_so_batobj_GetDamage;
		Hook_so_mobile_MoveReserve Org_so_mobile_MoveReserve;
		Hook_so_fill_PROTO_NC_CHAR_MAPLOGIN_ACK Org_so_fill_PROTO_NC_CHAR_MAPLOGIN_ACK;
		Hook_so_fill_CHAR_PARAMETER_DATA Org_so_fill_CHAR_PARAMETER_DATA;
		Hook_so_AllOfRange_Getthis Org_so_AllOfRange_Getthis;
		Hook_so_safm_SetCinema Org_so_safm_SetCinema;
		Hook_so_charbasedata Org_so_charbasedata;
		Hook_so_charsharpdata Org_so_charsharpdata;
		Hook_so_StoreQuestDoing Org_so_StoreQuestDoing;
		Hook_so_StoreQuestDone Org_so_StoreQuestDone;
		Hook_so_StoreQuestRead Org_so_StoreQuestRead;
		Hook_so_StoreQuestRepeat Org_so_StoreQuestRepeat;
		Hook_so_CharAbstateData Org_so_CharAbstateData;
		Hook_so_charskilldata Org_so_charskilldata;
		Hook_so_CharChargedBuffData Org_so_CharChargedBuffData;
		Hook_so_charpassivedata Org_so_charpassivedata;
		Hook_so_StoreInventoryFromServer Org_so_StoreInventoryFromServer;
		Hook_so_Storegamedata Org_so_Storegamedata;
		Hook_so_accountstoragefill Org_so_accountstoragefill;
		Hook_so_ply_reinforce_reloc Org_so_ply_reinforce_reloc;
		Hook_so_ply_dupmenu_canmenuopen Org_so_ply_dupmenu_canmenuopen;
		Hook_so_ply_dupmenu_Set Org_so_ply_dupmenu_Set;
		Hook_so_ply_dupmenu_close Org_so_ply_dupmenu_close;
		Hook_so_ply_TotalSkillEmpower Org_so_ply_TotalSkillEmpower;
		Hook_so_ply_skillempowerclear Org_so_ply_skillempowerclear;
		Hook_so_ply_itempickresult Org_so_ply_itempickresult;
		Hook_so_ply_Getchestinform Org_so_ply_Getchestinform;
		Hook_so_ply_ClassChange Org_so_ply_ClassChange;
		Hook_so_BodySize Org_so_BodySize;
		Hook_so_GetCharBriefInfo Org_so_GetCharBriefInfo;
		Hook_so_mobile_Teleport Org_so_mobile_Teleport;
		Hook_so_mobile_Teleport1 Org_so_mobile_Teleport1;
		Hook_so_door_Build Org_so_door_Build;
		Hook_so_mob_Regenerate Org_so_mob_Regenerate;
		Hook_so_effect_EffectBlast Org_so_effect_EffectBlast;
		Hook_so_effect_EffectBlast1 Org_so_effect_EffectBlast1;
		Hook_so_mob_DistanceFromHome Org_so_mob_DistanceFromHome;
		Hook_so_effect_BlastComplete Org_so_effect_BlastComplete;
		Hook_so_mob_RegenComplete Org_so_mob_RegenComplete;
		Hook_so_door_BuildComplete Org_so_door_BuildComplete;
		Hook_so_mob_ViewAggroList Org_so_mob_ViewAggroList;
		Hook_so_mob_AppendAggro Org_so_mob_AppendAggro;
		Hook_so_mob_DecreaseAggro Org_so_mob_DecreaseAggro;
		Hook_so_mob_MobID Org_so_mob_MobID;
		Hook_so_mob_DataBox Org_so_mob_DataBox;
		Hook_so_mob_DataBoxforQuest Org_so_mob_DataBoxforQuest;
		Hook_so_mob_Race Org_so_mob_Race;
		Hook_so_mob_SetWeaponHitTime Org_so_mob_SetWeaponHitTime;
		Hook_so_mob_SetWeaponAniTime Org_so_mob_SetWeaponAniTime;
		Hook_so_mob_CanGathered Org_so_mob_CanGathered;
		Hook_so_mob_CanRecover Org_so_mob_CanRecover;
		Hook_so_mob_MobAggro Org_so_mob_MobAggro;
		Hook_so_mobile_IsEnemy Org_so_mobile_IsEnemy;
		Hook_so_mobile_DamageOverTime Org_so_mobile_DamageOverTime;
		Hook_so_mobile_HPHealOverTime Org_so_mobile_HPHealOverTime;
		Hook_so_mobile_SPHealOverTime Org_so_mobile_SPHealOverTime;
		Hook_so_mob_SelectWeapon Org_so_mob_SelectWeapon;
		Hook_so_mob_CurSelectWeapon Org_so_mob_CurSelectWeapon;
		Hook_so_mob_FalimyList Org_so_mob_FalimyList;
		Hook_so_mob_FindMyRaceTarget Org_so_mob_FindMyRaceTarget;
		Hook_so_mob_CanMyTarget Org_so_mob_CanMyTarget;
		Hook_so_mob_CanNPCTarget Org_so_mob_CanNPCTarget;
		Hook_so_CurrentTargetHandle Org_so_CurrentTargetHandle;
		Hook_so_EquitEnd Org_so_EquitEnd;
		Hook_so_CurrentTargetObject Org_so_CurrentTargetObject;
		Hook_so_ply_CanMyTarget Org_so_ply_CanMyTarget;
		Hook_so_mob_RescueObject Org_so_mob_RescueObject;
		Hook_so_TentDistance Org_so_TentDistance;
		Hook_so_ply_KQRewardStruct Org_so_ply_KQRewardStruct;
		Hook_so_ply_KQRewardIndex Org_so_ply_KQRewardIndex;
		Hook_so_ply_Setpartyslot Org_so_ply_Setpartyslot;
		Hook_so_ply_partymemberlogin Org_so_ply_partymemberlogin;
		Hook_so_ply_NewPartyMemberJoin Org_so_ply_NewPartyMemberJoin;
		Hook_so_ply_SaveWeaponTitle Org_so_ply_SaveWeaponTitle;
		notice SendNotice;
		Hook_so_ply_WeaponSpeedSet Org_so_ply_WeaponSpeedSet;
		Hook_so_ply_WeaponRangeSet Org_so_ply_WeaponRangeSet;
		Hook_so_ply_PickupMoney Org_so_ply_PickupMoney;
		Hook_so_ply_IncDecMoney Org_so_ply_IncDecMoney;
		Hook_so_ply_PickupItem Org_so_ply_PickupItem;
		Hook_so_ply_SoloingMode Org_so_ply_SoloingMode;
		Hook_so_ply_PartyRecharge Org_so_ply_PartyRecharge;
		Hook_so_ply_FillChargedInven Org_so_ply_FillChargedInven;
		Hook_so_ply_ChargedWithdraw Org_so_ply_ChargedWithdraw;
		Hook_so_ply_EquipWeapon Org_so_ply_EquipWeapon;
		Hook_so_mobile_MoveSpeed Org_so_mobile_MoveSpeed;
		Hook_so_mobile_MoveState Org_so_mobile_MoveState;
		Hook_so_RecalcSpeed Org_so_RecalcSpeed;
		Hook_so_mobile_SpeedChange Org_so_mobile_SpeedChange;
		Hook_so_mobile_DuringFlying Org_so_mobile_DuringFlying;
		Hook_so_mobile_MoveHalt Org_so_mobile_MoveHalt;
		Hook_so_ply_ShowBoothItem Org_so_ply_ShowBoothItem;
		Hook_so_ply_BoothTrade Org_so_ply_BoothTrade;
		Hook_so_ply_TradeBoardUnlock Org_so_ply_TradeBoardUnlock;
		Hook_so_ply_GetInventoryLockList Org_so_ply_GetInventoryLockList;
		Hook_so_mgcfld_MagicFieldSpread Org_so_mgcfld_MagicFieldSpread;
		Hook_so_mgcfld_MagicFieldSpread_Friend Org_so_mgcfld_MagicFieldSpread_Friend;
		Hook_so_ply_Revival Org_so_ply_Revival;
		Hook_so_mobile_TargetModeCheck Org_so_mobile_TargetModeCheck;
		Hook_so_mobile_GetHPChangeOrder Org_so_mobile_GetHPChangeOrder;
		Hook_so_ply_StatIncrease Org_so_ply_StatIncrease;
		Hook_so_ply_StatDecrease Org_so_ply_StatDecrease;
		Hook_so_ply_QuestCheck Org_so_ply_QuestCheck;
		Hook_so_ply_ItemLotChange Org_so_ply_ItemLotChange;
		Hook_so_ply_KQSuccess Org_so_ply_KQSuccess;
		Hook_so_ply_KQFail Org_so_ply_KQFail;
		Hook_so_ply_GetGender Org_so_ply_GetGender;
		Hook_so_ply_QuestDiary Org_so_ply_QuestDiary;
		Hook_so_mobile_WhoIsKillMe Org_so_mobile_WhoIsKillMe;
		Hook_so_mobile_WhoIsClickMe Org_so_mobile_WhoIsClickMe;
		Hook_so_mobile_SetClicker Org_so_mobile_SetClicker;
		Hook_so_ply_GetMyGuildNo GetGuildNumber;
		Hook_so_ply_SetMyGuildNo Org_so_ply_SetMyGuildNo;
		Hook_so_ply_SetMyGuild Org_so_ply_SetMyGuild;
		Hook_so_ply_BroadcastGuildInfo Org_so_ply_BroadcastGuildInfo;
		Hook_so_mobile_GetGuildRegnum Org_so_mobile_GetGuildRegnum;
		Hook_so_ply_GuildStorageDeactivate Org_so_ply_GuildStorageDeactivate;
		Hook_so_ply_GetMyGuildStorageHandle Org_so_ply_GetMyGuildStorageHandle;
		Hook_so_ply_SetMyGuildStorageHandle Org_so_ply_SetMyGuildStorageHandle;
		Hook_so_ply_ItemBuyGuildToken Org_so_ply_ItemBuyGuildToken;
		Hook_so_ply_GetMyGuildAcademyRewardStorageHandle Org_so_ply_GetMyGuildAcademyRewardStorageHandle;
		Hook_so_ply_SetMyGuildAcademyRewardStorageHandle Org_so_ply_SetMyGuildAcademyRewardStorageHandle;
		Hook_so_ply_GuildAcademyRewardStorageDeactivate Org_so_ply_GuildAcademyRewardStorageDeactivate;
		Hook_so_ply_GuildAcademyRewardStorageWithdrawAck Org_so_ply_GuildAcademyRewardStorageWithdrawAck;
		Hook_so_ply_GuildAcademyRewardStorageDepositAck Org_so_ply_GuildAcademyRewardStorageDepositAck;
		Hook_so_ply_GuildAcademyRewardStorageRewardAck Org_so_ply_GuildAcademyRewardStorageRewardAck;
		Hook_so_ply_BroadcastGuildAcademyInfo Org_so_ply_BroadcastGuildAcademyInfo;
		Hook_so_ply_isAcademyGuildMember Org_so_ply_isAcademyGuildMember;
		Hook_so_ply_GetMyGuildAcademyNo Org_so_ply_GetMyGuildAcademyNo;
		Hook_so_ply_SetMyGuildAcademyNo Org_so_ply_SetMyGuildAcademyNo;
		Hook_so_ply_SetMyGuildAcademy Org_so_ply_SetMyGuildAcademy;
		Hook_so_ply_isIAmGuildAcademyMaster Org_so_ply_isIAmGuildAcademyMaster;
		Hook_so_ply_GuildAcademyRewardStoreFill Org_so_ply_GuildAcademyRewardStoreFill;
		Hook_so_ply_GuildAcademyRewardStoreGradeFill Org_so_ply_GuildAcademyRewardStoreGradeFill;
		Hook_so_ply_isGuildAcademyRewardStoreGrade Org_so_ply_isGuildAcademyRewardStoreGrade;
		Hook_so_ply_GuildAcademyRewardStorageRewardZoneRng Org_so_ply_GuildAcademyRewardStorageRewardZoneRng;
		Hook_so_ply_GuildAcademyRewordSrorageItemInfoCmd Org_so_ply_GuildAcademyRewordSrorageItemInfoCmd;
		Hook_so_ply_GuildReName Org_so_ply_GuildReName;
		Hook_so_ply_GuildReType Org_so_ply_GuildReType;
		Hook_so_ply_GuildReNameItemUseSuccess Org_so_ply_GuildReNameItemUseSuccess;
		Hook_so_ply_GuildReTypeItemUseSuccess Org_so_ply_GuildReTypeItemUseSuccess;
		Hook_so_ply_BriefLink Org_so_ply_BriefLink;
		Hook_so_mobile_GetIdxName GetInxName;
		Hook_so_bandit_ChangeType Org_so_bandit_ChangeType;
		Hook_so_IsMob Org_so_IsMob;
		Hook_so_relink Org_so_relink;
		Hook_so_Prison_Go Org_so_Prison_Go;
		Hook_so_Prison_End Org_so_Prison_End;
		Hook_so_scene_MovePathSet Org_so_scene_MovePathSet;
		Hook_so_scene_ItemAttrSet Org_so_scene_ItemAttrSet;
		Hook_so_scene_CreateItem Org_so_scene_CreateItem;
		Hook_so_scene_EraseItem Org_so_scene_EraseItem;
		Hook_so_scene_DetectRange Org_so_scene_DetectRange;
		Hook_so_scene_Duplicate Org_so_scene_Duplicate;
		Hook_so_scene_IsIdle Org_so_scene_IsIdle;
		Hook_so_ply_HorseFeed Org_so_ply_HorseFeed;
		Hook_so_mobile_BattleCamp Org_so_mobile_BattleCamp;
		Hook_so_ply_AllCastCancel Org_so_ply_AllCastCancel;
		Hook_so_mobile_DeadCheck Org_so_mobile_DeadCheck;
		Hook_so_SendInform2Admin Org_so_SendInform2Admin;
		Hook_so_ply_PartyInformInit Org_so_ply_PartyInformInit;
		Hook_so_ply_ChargedStatPlus Org_so_ply_ChargedStatPlus;
		Hook_so_ply_RoarItemUseSuccess Org_so_ply_RoarItemUseSuccess;
		Hook_so_ply_SkillEraseItemUseSuccess Org_so_ply_SkillEraseItemUseSuccess;
		Hook_so_ply_RemoveWhen Org_so_ply_RemoveWhen;
		Hook_so_ply_KeepFromChat Org_so_ply_KeepFromChat;
		Hook_so_mob_SightCenter Org_so_mob_SightCenter;
		Hook_so_mob_TargetChange Org_so_mob_TargetChange;
		Hook_so_ply_Return2Quest Org_so_ply_Return2Quest;
		Hook_so_mob_SetGuildRegNum Org_so_mob_SetGuildRegNum;
		Hook_so_mobile_MobAggroRate Org_so_mobile_MobAggroRate;
		Hook_so_ply_ItemBreakSuccess Org_so_ply_ItemBreakSuccess;
		Hook_so_ply_ItemBreakFail Org_so_ply_ItemBreakFail;
		Hook_so_LogoutLog Org_so_LogoutLog;
		Hook_so_ply_SparrowWingExpand Org_so_ply_SparrowWingExpand;
		Hook_so_ply_SparrowWingFly Org_so_ply_SparrowWingFly;
		Hook_so_ply_ItemUseResultPacket Org_so_ply_ItemUseResultPacket;
		Hook_so_ply_ChestBoxOpenAck Org_so_ply_ChestBoxOpenAck;
		Hook_so_ply_Summon2GuildTournament Org_so_ply_Summon2GuildTournament;
		Hook_so_ply_Send2GuildTournamentLogIn Org_so_ply_Send2GuildTournamentLogIn;
		Hook_so_ply_GuildTournament_isSummon Org_so_ply_GuildTournament_isSummon;
		Hook_so_ply_FlagCaptureCast Org_so_ply_FlagCaptureCast;
		Hook_so_ply_GuildTournamentJoinNew Org_so_ply_GuildTournamentJoinNew;
		Hook_so_IsInWeapon Org_so_IsInWeapon;
		Hook_so_ply_LoginIPSet Org_so_ply_LoginIPSet;
		Hook_so_ply_FromWhere Org_so_ply_FromWhere;
		Hook_so_ply_GetFromWhere Org_so_ply_GetFromWhere;
		Hook_so_ply_Script_CostumeCreate Org_so_ply_Script_CostumeCreate;
		Hook_so_ply_Script_CostumeTakeOff Org_so_ply_Script_CostumeTakeOff;
		Hook_so_ply_WeddingPrepareItem Org_so_ply_WeddingPrepareItem;
		Hook_so_ply_WeddingData Org_so_ply_WeddingData;
		Hook_so_ply_WeddingStatus Org_so_ply_WeddingStatus;
		Hook_so_ply_WeddingInfoUpdate Org_so_ply_WeddingInfoUpdate;
		Hook_so_ply_DivorceProcess Org_so_ply_DivorceProcess;
		Hook_so_ply_AdminCommand Org_so_ply_AdminCommand;
		Hook_so_ply_ItemLotInspecting Org_so_ply_ItemLotInspecting;
		Hook_so_ply_GetItemLotInspector Org_so_ply_GetItemLotInspector;
		Hook_so_ply_CalcTotalLot Org_so_ply_CalcTotalLot;
		Hook_so_ply_ItemLotCheck Org_so_ply_ItemLotCheck;
		Hook_so_ply_ServerMenuactor_sma_IsReady Org_so_ply_ServerMenuactor_sma_IsReady;
		Hook_so_UnlearnSkillAck Org_so_UnlearnSkillAck;
		Hook_so_mobile_ICanDamageTo Org_so_mobile_ICanDamageTo;
		Hook_so_MiscTable Org_so_MiscTable;
		Hook_so_serv_SetMaster Org_so_serv_SetMaster;
		Hook_so_serv_SetTarget Org_so_serv_SetTarget;
		Hook_so_mob_AggroAdjust Org_so_mob_AggroAdjust;
		Hook_so_ply_Volley Org_so_ply_Volley;
		Hook_so_ply_TargetChange Org_so_ply_TargetChange;
		Hook_so_ply_AbstateMatchEquip Org_so_ply_AbstateMatchEquip;
		Hook_so_ply_ReinforceRemoveWeapon Org_so_ply_ReinforceRemoveWeapon;
		Hook_so_ply_ReinforceRemoveShield Org_so_ply_ReinforceRemoveShield;
		Hook_so_ply_ReinforceRemoveEquip Org_so_ply_ReinforceRemoveEquip;
		Hook_so_smo_CrossCounterDamage Org_so_smo_CrossCounterDamage;
		Hook_so_serv_FindMaster Org_so_serv_FindMaster;
		Hook_so_serv_ServantMissionSet Org_so_serv_ServantMissionSet;
		Hook_so_mob_CanBeAttackedByPlayer Org_so_mob_CanBeAttackedByPlayer;
		Hook_so_ply_FillRewardInven Org_so_ply_FillRewardInven;
		Hook_so_ply_HolyPromiseSet Org_so_ply_HolyPromiseSet;
		Hook_so_ply_HolyPromiseCenUseTry Org_so_ply_HolyPromiseCenUseTry;
		Hook_so_ply_HolyPromiseCenUseSuccess Org_so_ply_HolyPromiseCenUseSuccess;
		Hook_so_ply_HolyPromiseCenFrom Org_so_ply_HolyPromiseCenFrom;
		Hook_so_ply_HolyPromiseGetCenReward Org_so_ply_HolyPromiseGetCenReward;
		Hook_so_ply_HolyPromiseWithdrawCenReward Org_so_ply_HolyPromiseWithdrawCenReward;
		Hook_so_mobile_SetNaturalEnemy Org_so_mobile_SetNaturalEnemy;
		Hook_so_mobile_GetNaturalEnemy Org_so_mobile_GetNaturalEnemy;
		Hook_sp_IsPreventAttack Org_sp_IsPreventAttack;
		Hook_sp_IsEthereal Org_sp_IsEthereal;
		Hook_so_mobile_IsInFear Org_so_mobile_IsInFear;
		Hook_so_ply_IsInBoothInterior Org_so_ply_IsInBoothInterior;
		Hook_so_ply_RegistNumberVarifyCheck Org_so_ply_RegistNumberVarifyCheck;
		Hook_so_ply_WeaponEndureChangeAck Org_so_ply_WeaponEndureChangeAck;
		Hook_so_ply_ShieldEndureChangeAck Org_so_ply_ShieldEndureChangeAck;
		Hook_so_ply_ChangeCharIDUseAck Org_so_ply_ChangeCharIDUseAck;
		Hook_so_mobile_Broadcast2ndTarget Org_so_mobile_Broadcast2ndTarget;
		Hook_so_GetTargetObject Org_so_GetTargetObject;
		Hook_so_Mob_SetSendTagetInfo Org_so_Mob_SetSendTagetInfo;
		Hook_so_IsTarget Org_so_IsTarget;
		Hook_so_mobile_SendMyMoveInfo Org_so_mobile_SendMyMoveInfo;
		Hook_so_mob_RoamingPathSet Org_so_mob_RoamingPathSet;
		Hook_so_mob_RoamingPathGet Org_so_mob_RoamingPathGet;
		Hook_so_ply_StoreItem Org_so_ply_StoreItem;
		Hook_InteractWithNPC Org_InteractWithNPC;
		Hook_so_ply_ToNormalLoc Org_so_ply_ToNormalLoc;
		Hook_so_ReinforceMove Org_so_ReinforceMove;
		Hook_registerObsersver Org_registerObsersver;
		Hook_unregisterObsersver Org_unregisterObsersver;
		Hook_unregisterObsersvers Org_unregisterObsersvers;
		Hook_notifyObservers Org_notifyObservers;
		Hook_hasObserver Org_hasObserver;
		Hook_sp_DoEmotion Org_sp_DoEmotion;
		Hook_sm_UseSkillSimple Org_sm_UseSkillSimple;
		Hook_so_mobile_StopHere Org_so_mobile_StopHere;
		Hook_so_ply_SendMoveFail Org_so_ply_SendMoveFail;
		Hook_smo_ply_ReinforceStopHere Org_smo_ply_ReinforceStopHere;
		Hook_so_getDetectRange Org_so_getDetectRange;
		Hook_so_ply_InvenWrite Org_so_ply_InvenWrite;
		Hook_so_smo_AbStateKeepTimeAdd Org_so_smo_AbStateKeepTimeAdd;
		Hook_so_smo_SPExhByAbState Org_so_smo_SPExhByAbState;
		Hook_so_smo_AbnormalStateAttribute Org_so_smo_AbnormalStateAttribute;
		Hook_so_smo_RangeEvation Org_so_smo_RangeEvation;
		Hook_so_smo_CanEnchant Org_so_smo_CanEnchant;
		Hook_so_ply_GetClientSession Org_so_ply_GetClientSession;
		Hook_so_ply_IsLink_OutMap_AndSendErrorMsg Org_so_ply_IsLink_OutMap_AndSendErrorMsg;
		Hook_so_ply_IsLink_In_MapAndSendErrorMsg Org_so_ply_IsLink_In_MapAndSendErrorMsg;
		Hook_so_NPCRevive Org_so_NPCRevive;
		Hook_so_npc_FromTable Org_so_npc_FromTable;
		Hook_so_GetRaid Org_so_GetRaid;
		Hook_so_SetRaid Org_so_SetRaid;
		Hook_so_GetInsDunGeonInRegNoAndType Org_so_GetInsDunGeonInRegNoAndType;
		Hook_so_mob_ReturnToRegen Org_so_mob_ReturnToRegen;
		Hook_so_FillBriefABState Org_so_FillBriefABState;
		/** Revives the player via the Tear of Legel revival */
		Hook_so_ReviveByItem ReviveByItem;
		Hook_so_AmpersandCommand_LevelUp Org_so_AmpersandCommand_LevelUp;
		Hook_so_DiceItemPickInit Org_so_DiceItemPickInit;
		Hook_so_DiceItemStart Org_so_DiceItemStart;
		Hook_so_IsDiceGamePlay Org_so_IsDiceGamePlay;
		Hook_so_SetHP Org_so_SetHP;
		Hook_so_ply_GtItemEffectMsg Org_so_ply_GtItemEffectMsg;
		Hook_so_SpamRecvDataFromWM Org_so_SpamRecvDataFromWM;
		Hook_so_SpamSendDataToCharDB Org_so_SpamSendDataToCharDB;
		Hook_so_mob_SetLifeTime Org_so_mob_SetLifeTime;
		Hook_so_SetAutoSaveTime Org_so_SetAutoSaveTime;
		Hook_sp_FreeStat_Get_DecreaseNum Org_sp_FreeStat_Get_DecreaseNum;
		Hook_sp_CharFreeStat_IsLock Org_sp_CharFreeStat_IsLock;
		Hook_sp_CharFreeStat_Lock Org_sp_CharFreeStat_Lock;
		Hook_sp_CharFreeStat_UnLock Org_sp_CharFreeStat_UnLock;
		Hook_so_ply_FreeStat_Increase Org_so_ply_FreeStat_Increase;
		Hook_so_ply_FreeStat_Decrease Org_so_ply_FreeStat_Decrease;
		Hook_so_BashStop Org_so_BashStop;
		Hook_so_GetIsQuestRewardReq Org_so_GetIsQuestRewardReq;
		Hook_so_SetIsQuestRewardReq Org_so_SetIsQuestRewardReq;
		Hook_so_SetSpamerChatBan Org_so_SetSpamerChatBan;
		Hook_so_Send_NC_CHARSAVE_2WLDMAN_SKILL_CMD Org_so_Send_NC_CHARSAVE_2WLDMAN_SKILL_CMD;
		Hook_so_mob_GetbUseNextSkill Org_so_mob_GetbUseNextSkill;
		Hook_so_mob_SetbUseNextSkill Org_so_mob_SetbUseNextSkill;
		Hook_so_Gamble_IsGambleHouse Org_so_Gamble_IsGambleHouse;
		Hook_so_Gamble_SetPrevMapName Org_so_Gamble_SetPrevMapName;
		Hook_so_Gamble_CharCoinData Org_so_Gamble_CharCoinData;
		Hook_so_Gamble_CurrentCoin Org_so_Gamble_CurrentCoin;
		Hook_so_Gamble_StoreCoin Org_so_Gamble_StoreCoin;
		Hook_so_Gamble_ChangeCoin Org_so_Gamble_ChangeCoin;
		Hook_so_Gamble_CurrentExchangedCoin Org_so_Gamble_CurrentExchangedCoin;
		Hook_so_Gamble_StoreExchangedCoin Org_so_Gamble_StoreExchangedCoin;
		Hook_so_Gamble_ChangeExchangedCoin Org_so_Gamble_ChangeExchangedCoin;
		Hook_so_Gamble_CanJoinGamble Org_so_Gamble_CanJoinGamble;
		Hook_so_Gamble_IsJoinThisGamble Org_so_Gamble_IsJoinThisGamble;
		Hook_so_Gamble_IsJoinAnyGamble Org_so_Gamble_IsJoinAnyGamble;
		Hook_so_Gamble_SetGambleType Org_so_Gamble_SetGambleType;
		Hook_so_Gamble_IsCanSessionCloseing Org_so_Gamble_IsCanSessionCloseing;
		Hook_so_mob_GetNextRoamingWaitTime Org_so_mob_GetNextRoamingWaitTime;
		Hook_so_mob_SetNextRoamingWaitTime Org_so_mob_SetNextRoamingWaitTime;
		Hook_so_mob_CheckNextRoamingWait Org_so_mob_CheckNextRoamingWait;
		Hook_so_ply_EndofTrade Org_so_ply_EndofTrade;
		Hook_so_ply_ReactionNpcHandle Org_so_ply_ReactionNpcHandle;
		Hook_so_ply_NpcReaction Org_so_ply_NpcReaction;
		Hook_so_ply_CapsuleItemOpenAck Org_so_ply_CapsuleItemOpenAck;
		Hook_so_npc_SetLocation Org_so_npc_SetLocation;
		Hook_so_ply_SlotMachineDBResult Org_so_ply_SlotMachineDBResult;
		Hook_so_ply_IBurstJackPot Org_so_ply_IBurstJackPot;
		Hook_so_ply_GodOfSlotMachine Org_so_ply_GodOfSlotMachine;
		Hook_so_AITraining Org_so_AITraining;
		Hook_so_AILearn Org_so_AILearn;
		Hook_so_AIScriptFuncExec Org_so_AIScriptFuncExec;
		Hook_so_AIScriptFuncExec1 Org_so_AIScriptFuncExec1;
		Hook_so_AIScriptFuncExec2 Org_so_AIScriptFuncExec2;
		Hook_so_LuaFunctionSet Org_so_LuaFunctionSet;
		Hook_so_mob_SetWeaponAsScript Org_so_mob_SetWeaponAsScript;
		Hook_so_mob_CurrentTarget Org_so_mob_CurrentTarget;
		Hook_so_mob_SkillRegistAtScript Org_so_mob_SkillRegistAtScript;
		Hook_so_mob_ParamSetAtScript Org_so_mob_ParamSetAtScript;
		Hook_so_mob_SkillBlastAtScript Org_so_mob_SkillBlastAtScript;
		Hook_so_mob_GetAggroList Org_so_mob_GetAggroList;
		Hook_so_ShineMobileObject Org_so_ShineMobileObject;
		Hook_so_mob_SkillParameterSet Org_so_mob_SkillParameterSet;
		Hook_so_mob_SkillParameterSetAtScript Org_so_mob_SkillParameterSetAtScript;
		Hook_so_mgcfld_FirstTickDelay Org_so_mgcfld_FirstTickDelay;
		Hook_so_mob_GetMonEXP Org_so_mob_GetMonEXP;
		Hook_so_mob_SetMobResist Org_so_mob_SetMobResist;
		Hook_so_mob_SetEnemyDetect Org_so_mob_SetEnemyDetect;
		Hook_so_mob_SetEnemyDetect1 Org_so_mob_SetEnemyDetect1;
		Hook_so_mob_SetIsPlayerSide Org_so_mob_SetIsPlayerSide;
		Hook_so_mob_IsItemDropSetAtScript Org_so_mob_IsItemDropSetAtScript;
		Hook_so_mob_SetItemDropMobID Org_so_mob_SetItemDropMobID;
		Hook_so_SetMovePacket Org_so_SetMovePacket;
		Hook_so_ToShinePlayer Org_so_ToShinePlayer;
		Hook_so_GetItemLot Org_so_GetItemLot;
		Hook_so_ply_ToggleSkill_IsOn Org_so_ply_ToggleSkill_IsOn;
		Hook_so_ply_ToggleSkill_On Org_so_ply_ToggleSkill_On;
		Hook_so_ply_ToggleSkill_Off Org_so_ply_ToggleSkill_Off;
		Hook_so_ply_ToggleSkill_AllOff Org_so_ply_ToggleSkill_AllOff;
		Hook_so_ply_DmgCoolTimeDown Org_so_ply_DmgCoolTimeDown;
		Hook_so_ply_GetDamageAbsorb Org_so_ply_GetDamageAbsorb;
		Hook_so_ply_SetDamageAbsorb Org_so_ply_SetDamageAbsorb;
		Hook_so_ply_GetRemainingDamageAbsorb Org_so_ply_GetRemainingDamageAbsorb;
		Hook_so_ply_SetRemainingDamageAbsorb Org_so_ply_SetRemainingDamageAbsorb;
		Hook_so_ply_CheckDamageAbsorption Org_so_ply_CheckDamageAbsorption;
		Hook_smo_GetFlagDamageAbsorb Org_smo_GetFlagDamageAbsorb;
		Hook_smo_SetFlagDamageAbsorb Org_smo_SetFlagDamageAbsorb;
		Hook_smo_LightningWaveSkill Org_smo_LightningWaveSkill;
		Hook_so_ply_PassiveSetAbstate Org_so_ply_PassiveSetAbstate;
		Hook_so_ply_CardCollect Org_so_ply_CardCollect;
		Hook_so_ply_CardCollectBookMark Org_so_ply_CardCollectBookMark;
		Hook_so_ply_CardCollectReward Org_so_ply_CardCollectReward;
		Hook_so_ply_CollectCardOpen Org_so_ply_CollectCardOpen;
		Hook_so_ply_CardRegist Org_so_ply_CardRegist;
		Hook_so_ply_CardBookmarkRegist Org_so_ply_CardBookmarkRegist;
		Hook_so_InitAIScript Org_so_InitAIScript;
		Hook_so_mob_GetTopAggroTarget Org_so_mob_GetTopAggroTarget;
		Hook_so_smo_GetRandomTarget_Object Org_so_smo_GetRandomTarget_Object;
		Hook_so_smo_GetRandomTarget_Locate Org_so_smo_GetRandomTarget_Locate;
		Hook_so_CameraMoveSendBriefInfo Org_so_CameraMoveSendBriefInfo;
		Hook_so_ToShineMob Org_so_ToShineMob;
		Hook_so_ply_SendMenuOpenReq Org_so_ply_SendMenuOpenReq;
		Hook_so_SetAnimation Org_so_SetAnimation;
		Hook_so_ResetAnimation Org_so_ResetAnimation;
		Hook_so_SetForcedAnimation Org_so_SetForcedAnimation;
		Hook_so_mob_SetDeadDelayTime Org_so_mob_SetDeadDelayTime;
		Hook_so_mob_SkillParameterSet_WeaponIndex Org_so_mob_SkillParameterSet_WeaponIndex;
		Hook_so_ply_IsRebirth Org_so_ply_IsRebirth;
		Hook_so_ply_setIsRebirth Org_so_ply_setIsRebirth;
		Hook_so_ply_HealRate Org_so_ply_HealRate;
		Hook_so_ply_setHealRate Org_so_ply_setHealRate;
		Hook_so_serv_SetRoamingData Org_so_serv_SetRoamingData;
		Hook_so_serv_ServantRoaming Org_so_serv_ServantRoaming;
		Hook_so_serv_GetRoamingType Org_so_serv_GetRoamingType;
		Hook_so_serv_LastExplosionReady Org_so_serv_LastExplosionReady;
		Hook_so_ply_setSwingTime Org_so_ply_setSwingTime;
		Hook_so_ply_getSwingTime Org_so_ply_getSwingTime;
		Hook_so_MoverSystem_GetOff Org_so_MoverSystem_GetOff;
		Hook_so_MoverSystem_NoDamage Org_so_MoverSystem_NoDamage;
		Hook_so_MoverSystem_GetMover Org_so_MoverSystem_GetMover;
		Hook_so_MoverSystem_SetMover Org_so_MoverSystem_SetMover;
		Hook_so_MoverSystem_GetMoverSlot Org_so_MoverSystem_GetMoverSlot;
		Hook_so_MoverSystem_SetMoverSlot Org_so_MoverSystem_SetMoverSlot;
		Hook_so_MoverSystem_GetLinkData Org_so_MoverSystem_GetLinkData;
		Hook_so_MoverSystem_SetLinkData Org_so_MoverSystem_SetLinkData;
		Hook_so_MoverSystem_ClearLinkData Org_so_MoverSystem_ClearLinkData;
		Hook_so_MoverSystem_Feeding Org_so_MoverSystem_Feeding;
		Hook_so_MoverSystem_ChargedMoverNotHungry Org_so_MoverSystem_ChargedMoverNotHungry;
		Hook_so_smo_SetLocation Org_so_smo_SetLocation;
		Hook_so_smv_ClearMoverInfo Org_so_smv_ClearMoverInfo;
		Hook_so_smv_SummonMover Org_so_smv_SummonMover;
		Hook_so_smv_SetMaster_RegNum Org_so_smv_SetMaster_RegNum;
		Hook_so_smv_GetMaster_RegNum Org_so_smv_GetMaster_RegNum;
		Hook_so_smv_SetMaster_Object Org_so_smv_SetMaster_Object;
		Hook_so_smv_GetMaster_Object Org_so_smv_GetMaster_Object;
		Hook_so_smv_SetMoverItemInfo Org_so_smv_SetMoverItemInfo;
		Hook_so_smv_GetOn Org_so_smv_GetOn;
		Hook_so_smv_GetOff Org_so_smv_GetOff;
		Hook_so_smv_GetOffAll Org_so_smv_GetOffAll;
		Hook_so_smv_CanUseFeedItem Org_so_smv_CanUseFeedItem;
		Hook_so_smv_Feeding Org_so_smv_Feeding;
		Hook_so_smv_MoveWalk Org_so_smv_MoveWalk;
		Hook_so_smv_MoveRun Org_so_smv_MoveRun;
		Hook_so_smv_MoveStop Org_so_smv_MoveStop;
		Hook_so_smv_GetMaxSlotNum Org_so_smv_GetMaxSlotNum;
		Hook_so_smv_GetPassenger Org_so_smv_GetPassenger;
		Hook_so_smv_PassengerNotice Org_so_smv_PassengerNotice;
		Hook_so_smv_GetMoverID Org_so_smv_GetMoverID;
		Hook_so_smv_GetMyBookingSlot Org_so_smv_GetMyBookingSlot;
		Hook_so_smv_SkillBash_Object Org_so_smv_SkillBash_Object;
		Hook_so_smv_SkillBash_Location Org_so_smv_SkillBash_Location;
		Hook_so_smv_MasterSetAbsCheck Org_so_smv_MasterSetAbsCheck;
		Hook_so_smv_MasterResetAbsCheck Org_so_smv_MasterResetAbsCheck;
		Hook_so_smv_GetMoverGrade Org_so_smv_GetMoverGrade;
		Hook_so_smv_SetMoverGrade Org_so_smv_SetMoverGrade;
		Hook_so_ply_getBanditBriefinfo Org_so_ply_getBanditBriefinfo;
		Hook_so_ply_CheckCharType Org_so_ply_CheckCharType;
		Hook_so_ply_ArrangeInvenInit Org_so_ply_ArrangeInvenInit;
		Hook_so_ply_ArrangeInvenDelayCheck Org_so_ply_ArrangeInvenDelayCheck;
		Hook_so_ply_IsArrangeInven Org_so_ply_IsArrangeInven;
		Hook_so_ply_SetArrangeInven Org_so_ply_SetArrangeInven;
		Hook_so_ply_ArrangeInven Org_so_ply_ArrangeInven;
		Hook_so_Send_NC_CHARSAVE_2WLDMAN_QUEST_DONE_CMD Org_so_Send_NC_CHARSAVE_2WLDMAN_QUEST_DONE_CMD;
		Hook_so_AccountStorageAnywhereOpen Org_so_AccountStorageAnywhereOpen;
		Hook_so_AccountStorageAnywhereClose Org_so_AccountStorageAnywhereClose;
		Hook_so_ply_JobChangeDamageUp Org_so_ply_JobChangeDamageUp;
		Hook_so_ply_IsEquipItem Org_so_ply_IsEquipItem;
		Hook_so_ply_DecreaseDmgPassiveSkill Org_so_ply_DecreaseDmgPassiveSkill;
		Hook_so_ply_GetQuestZone Org_so_ply_GetQuestZone;
		Hook_so_ply_SendFieldAttribute Org_so_ply_SendFieldAttribute;
		Hook_so_mob_SetAnimationLevel Org_so_mob_SetAnimationLevel;
		Hook_so_mob_GetAnimationLevel Org_so_mob_GetAnimationLevel;
		Hook_so_mob_IsNPC Org_so_mob_IsNPC;
		Hook_so_SendSpeedInformation Org_so_SendSpeedInformation;
		Hook_smo_GetMoveState Org_smo_GetMoveState;
		Hook_smo_GetMoveStateStartTime Org_smo_GetMoveStateStartTime;
		Hook_so_ply_PartyZoneJoinCmd Org_so_ply_PartyZoneJoinCmd;
		Hook_so_ply_PartyZoneLeaveCmd Org_so_ply_PartyZoneLeaveCmd;
		Hook_so_ply_EquipmentChange Org_so_ply_EquipmentChange;
		Hook_so_ply_ViewSlot_Equip Org_so_ply_ViewSlot_Equip;
		Hook_so_ply_ViewSlot_UnEquip Org_so_ply_ViewSlot_UnEquip;
		Hook_so_ply_ViewSlot_UnEquipAll Org_so_ply_ViewSlot_UnEquipAll;
		Hook_so_ply_ViewSlot_EquipInfoSend Org_so_ply_ViewSlot_EquipInfoSend;
		Hook_so_ply_ViewSlot_EquipInfoClear Org_so_ply_ViewSlot_EquipInfoClear;
		Hook_so_ply_DecoActList_Cehck Org_so_ply_DecoActList_Cehck;
		Hook_so_ply_PlaySound Org_so_ply_PlaySound;
		Hook_so_ply_ShowCinematicText Org_so_ply_ShowCinematicText;
		Hook_so_ply_EndCinematicText Org_so_ply_EndCinematicText;
		Hook_so_ply_EffectMsg Org_so_ply_EffectMsg;
		Hook_so_ply_Sen_InitLP Org_so_ply_Sen_InitLP;
		Hook_so_ply_Sen_GetLP Org_so_ply_Sen_GetLP;
		Hook_so_ply_Sen_MaxLP Org_so_ply_Sen_MaxLP;
		Hook_so_ply_Sen_GainLP Org_so_ply_Sen_GainLP;
		Hook_so_ply_Sen_LostLP Org_so_ply_Sen_LostLP;
		Hook_so_ply_Sen_GetLPRecover Org_so_ply_Sen_GetLPRecover;
		Hook_so_ply_Sen_RecalcLPRecover Org_so_ply_Sen_RecalcLPRecover;
		Hook_so_ply_Sen_GetLPRecoverInterval Org_so_ply_Sen_GetLPRecoverInterval;
		Hook_so_ply_Sen_LP_Tick Org_so_ply_Sen_LP_Tick;
		Hook_so_RecoverAlreadyDead Org_so_RecoverAlreadyDead;
		Hook_so_smo_LastDamageOperation Org_so_smo_LastDamageOperation;
		Hook_so_ply_MakeLayerRegNum Org_so_ply_MakeLayerRegNum;
		Hook_so_ply_MoveNewLayer Org_so_ply_MoveNewLayer;
		Hook_so_ply_MoveOtherLayer Org_so_ply_MoveOtherLayer;
		Hook_so_ply_DeleteObject_AllOfRange Org_so_ply_DeleteObject_AllOfRange;
		Hook_so_ply_MoveNewLayer_AllInMap Org_so_ply_MoveNewLayer_AllInMap;
		Hook_so_ply_MoveOtherLayer_AllInMap Org_so_ply_MoveOtherLayer_AllInMap;
		Hook_so_ply_DeleteObject_AllInMap Org_so_ply_DeleteObject_AllInMap;
		Hook_so_ply_LayerMoverRideOn Org_so_ply_LayerMoverRideOn;
		Hook_so_ply_SendBriefInfo_MoveLayer Org_so_ply_SendBriefInfo_MoveLayer;
		Hook_so_smo_StaticDamage Org_so_smo_StaticDamage;
		Hook_so_serv_SetFlag Org_so_serv_SetFlag;
		Hook_so_serv_InitFlag Org_so_serv_InitFlag;
		Hook_so_serv_SetMobCanDamageTo Org_so_serv_SetMobCanDamageTo;
		Hook_so_serv_GetMobCanDamageTo Org_so_serv_GetMobCanDamageTo;
		Hook_so_mob_SendReallyKill Org_so_mob_SendReallyKill;
		Hook_so_ply_LoginTutorialMap Org_so_ply_LoginTutorialMap;
		Hook_so_ply_SetTutorialInfo Org_so_ply_SetTutorialInfo;
		Hook_so_ply_GetTutorialInfo Org_so_ply_GetTutorialInfo;
		Hook_so_ply_LevelUpAtLua Org_so_ply_LevelUpAtLua;
		Hook_so_SetKQTeamType Org_so_SetKQTeamType;
		Hook_so_GetKQTeamType Org_so_GetKQTeamType;
		Hook_so_smo_TargetIsEnemyKQTeam Org_so_smo_TargetIsEnemyKQTeam;
		Hook_so_ply_IsKQJoiner Org_so_ply_IsKQJoiner;
		Hook_so_ply_SendCanUseReviveItem Org_so_ply_SendCanUseReviveItem;
		Hook_so_ply_ItemBuyItemMoney Org_so_ply_ItemBuyItemMoney;
		Hook_so_ply_DePorymorph Org_so_ply_DePorymorph;
		Hook_so_drpitm_bQuestDropItem_Set Org_so_drpitm_bQuestDropItem_Set;
		Hook_so_drpitm_bQuestDropItem_Get Org_so_drpitm_bQuestDropItem_Get;
		Hook_so_ply_QuestItemCheck Org_so_ply_QuestItemCheck;
		Hook_so_ply_GetChatFontColorID Org_so_ply_GetChatFontColorID;
		Hook_so_ply_SetChatFontColorID Org_so_ply_SetChatFontColorID;
		Hook_so_ply_GetChatBalloonColorID Org_so_ply_GetChatBalloonColorID;
		Hook_so_ply_SetChatBalloonColorID Org_so_ply_SetChatBalloonColorID;
		Hook_so_ply_ChatColorInfoApply Org_so_ply_ChatColorInfoApply;
		Hook_so_ply_ChatColorInfoClear Org_so_ply_ChatColorInfoClear;
		Hook_so_PetSystem_GetPet Org_so_PetSystem_GetPet;
		Hook_so_SetAnimationBriefInfo Org_so_SetAnimationBriefInfo;
		Hook_so_mob_FindLooter Org_so_mob_FindLooter;
		Hook_so_ply_SetUseItemMinimon Org_so_ply_SetUseItemMinimon;
		Hook_so_ply_UseItemMinimon_IsUse Org_so_ply_UseItemMinimon_IsUse;
		Hook_so_ply_UseItemMinimon_Off Org_so_ply_UseItemMinimon_Off;
		Hook_so_ply_UseItemMinimon_SlotItemCheck Org_so_ply_UseItemMinimon_SlotItemCheck;
		Hook_so_IsAlliance Org_so_IsAlliance;
		Hook_so_ply_SetSellItemInfo Org_so_ply_SetSellItemInfo;
		Hook_so_ply_SendSellItemInfo_Client Org_so_ply_SendSellItemInfo_Client;
		Hook_so_ply_CanItemRepurchase Org_so_ply_CanItemRepurchase;
		Hook_so_ply_SellItemList_Insert Org_so_ply_SellItemList_Insert;
		Hook_so_ply_SellItemList_Delete Org_so_ply_SellItemList_Delete;
		Hook_so_Init Org_so_Init;
		Hook_so_smo_SetStaticWalkSpeed Org_so_smo_SetStaticWalkSpeed;
		Hook_so_smo_SetStaticRunSpeed Org_so_smo_SetStaticRunSpeed;
		Hook_so_smo_IsStaticWalkSpeed Org_so_smo_IsStaticWalkSpeed;
		Hook_so_smo_IsStaticRunSpeed Org_so_smo_IsStaticRunSpeed;
		Hook_so_smo_GetStaticWalkSpeed Org_so_smo_GetStaticWalkSpeed;
		Hook_so_smo_GetStaticRunSpeed Org_so_smo_GetStaticRunSpeed;
	};

	struct ShineObjectHandleUnion
	{
		unsigned short handle;
	};

#pragma pack(push, 4)
	struct Layer
	{
		unsigned int l_Main;
		char l_Sub;
	};
#pragma pack(pop)

	struct $C7AF70B47C699662F9010C1970821EBE
	{
		Layer templyr;
		Layer* layer;
	};

	struct $5E684959B77675D5191741C5366AF829
	{
		SHINE_XY_TYPE* location;
		char* direct;
	};

	struct ObjectCoordNodeVtbl
	{
		int(__thiscall* ocn_type)(void* self);
		int(__thiscall* ocn_Getlocation)(void* self);
	};

	struct ObjectCoordNode
	{
		ObjectCoordNodeVtbl* vfptr;
		ShineObject* ocn_obj;
	};

	struct ObjectXCoordNode : ObjectCoordNode
	{
	};

	struct ObjectYCoordNode : ObjectCoordNode
	{
	};

	struct CoordedNode
	{
		ObjectCoordNode* cn_node;
		CoordedNode* cn_prev;
		CoordedNode* cn_next;
	};

	struct ListCheckStruct
	{
		unsigned int lcs_ListCheck[4];
	};

	struct LayerRegistPartInfo
	{
		unsigned int nLayerNumber;
		unsigned short nLayerNumberType;
		unsigned short nLayerType;
	};
	union $51411A5BB4A7359E655E425B581FD8DF
	{
		LayerRegistPartInfo LayerPartInfo;
		unsigned long long LayerRegNumber;
	};

#pragma pack(push, 4)
	struct  LayerValue
	{
		unsigned int nLayerTypeValue;
		char nLayerType;
	};
#pragma pack(pop)

#pragma pack(push, 8)
	struct  LayerRegistInfo
	{
		$51411A5BB4A7359E655E425B581FD8DF LayerRegNumberUnion;
		char nViewType;
		LayerValue LayerTypeValue;
	};
#pragma pack(pop)

	struct $13BC111DC65433BF9F06B1A52F67E675
	{
		ObjectXCoordNode Xnode;
		ObjectYCoordNode Ynode;
		CoordedNode Xlist;
		CoordedNode Ylist;
		unsigned int eventnumber[4];
		ListCheckStruct listcheck;
		LayerRegistInfo LayerRegistInfo;
	};

	struct $4D50583F9C6B1E276B0E7AEDD2EE78C2
	{
		unsigned int regenx;
		unsigned int regeny;
	};

	struct $AF1340EFDCFC3111DD295147A2BD06C0
	{
		char PKer;
		char EnemyGuild;
		char PartyMember;
		char Mob;
		char Summoned;
	};

#pragma pack(push, 1)
	struct FieldAttr
	{
		MapNameStruct mapidclient;
		char delimiter;
		char subfrom[4];
		char subto[4];
		char serial;
		char _mapname[32];
		char KingdomQuestMap;
		unsigned int width;
		unsigned int height;
		unsigned short immortal_millisec;
		char script[32];
		char ItemDropByKilled;
		$AF1340EFDCFC3111DD295147A2BD06C0 attack;
		char ispkkq;
		char isfreepk;
		char ispartybattle;
		char NameHide;
		char LinkIn;
		char LinkOut;
		char SystemMap;
		MapNameStruct regencity;
		$4D50583F9C6B1E276B0E7AEDD2EE78C2 regenloc[4];
		char regenspots;
		char canrestart;
		char cantrade;
		char byCanMiniHouset;
		char byCanItem;
		char byCanSkill;
		char byCanChat;
		char byCanShout;
		char byBooth;
		char byProduce;
		char byCanRide;
		char canstoneuse;
		char canparty;
		unsigned short explost_atdead_bymob;
		unsigned short explost_atdead_byply;
		char playersublayer;
		char checksum;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct MapInfo
	{
		unsigned short ID;
		MapNameStruct MapName;
		char Name[32];
		Enums::WM_Link IsWMLink;
		unsigned int RegenX;
		unsigned int RegenY;
		char KingdomMap;
		MapNameStruct MapFolderName;
		char InSide;
		unsigned int Sight;
	};
#pragma pack(pop)

	union Name8
	{
		char n8_name[32];
		unsigned int n8_code[8];
	};
	struct IAreaData
	{
		void* vfptr;
		Name8 Name;
		int nAreaType;
	};
	struct AreaInfoData
	{
		void* vfptr;
		IAreaData* m_pData[256];
		unsigned int m_uiTotalDataCnt;
	};

#pragma pack(push, 4)
	struct BlockingDistribute
	{
		unsigned short bd_Top;
		unsigned short bd_Bottom;
		unsigned short bd_Left;
		unsigned short bd_Right;
		BlockingDistribute* bd_Brench[4];
		unsigned short bd_Brenchs;
		unsigned short bd_EmptyCellNum;
		char bd_Act;
	};
#pragma pack(pop)

	struct MapDoorBlockElement
	{
		Name8 mdbe_BlockName;
		unsigned int mdbe_StartX;
		unsigned int mdbe_StartY;
		unsigned int mdbe_EndX;
		unsigned int mdbe_EndY;
		unsigned int mdbe_DataSize;
		unsigned int mdbe_Address;
	};
	struct MapDoorArray
	{
		unsigned int mda_TotalHeadCnt;
		MapDoorBlockElement mda_Array[32];
		int mda_Number;
		char* mda_BlockBuffer;
	};
	struct MapBlockInformation
	{
		unsigned int mbi_mapxsize;
		unsigned int mbi_mapysize;
		unsigned int mbi_blockxsize;
		unsigned int mbi_blockysize;
		unsigned int mbi_xbyte;
		char* mbi_MoveBlockBuffer;
		char* mbi_AttackBlockBuffer;
		unsigned int mbi_uiRealOneSideDataSize;
		unsigned int mbi_uiOneSideBlockCnt;
		AreaInfoData mbi_AreaData;
		BlockingDistribute* mbi_BlockDistribute;
		MapDoorArray mbi_DoorBlockInform;
	};
	struct $70E7122D3FEE8B7C6F78D3C5EA0F573E
	{
		ShineObject* zero;
		ShineObject* infinite;
		ShineObject* flag[5];
	};
	struct MobDeadCount
	{
		unsigned short* mdc_Counter;
	};
	struct FieldBonus
	{
		int fb_Experience;
		int fb_DropRate;
	};
	struct AxialListIterator
	{
		void* vfptr;
	};

	struct BroadcastFunc
	{
		char(__thiscall* fm_fp_AllInMap1)(ShineObject* Object, char(__thiscall*)(ShineObject* Object, ShineObject*, unsigned int), char);
		char(__thiscall* fm_fp_AllInMap2)(ShineObject* Object, AxialListIterator*, char);
		char(__thiscall* fm_fp_AllOfRange1)(ShineObject* Object, unsigned int, SHINE_XY_TYPE*, int, void*, char(__thiscall*)(ShineObject* Object, ShineObject*, unsigned int), char, unsigned short);
		char(__thiscall* fm_fp_AllOfRange2)(ShineObject* Object, unsigned int, SHINE_XY_TYPE*, int, void*, AxialListIterator*, char, unsigned short);
	};
	struct $054780A91BF37A2F1A0D085DD9DE9609
	{
		char seed;
		unsigned int guildA;
		unsigned int guildB;
	};
	struct VirtualMap
	{
		FieldMap* vm_Map;
	};

#pragma pack(push, 1)
	struct LinkInformTemplete
	{
		char index[20];
		char linktoserver[33];
		char linktoclient[33];
		unsigned int coordx;
		unsigned int coordy;
		unsigned short direct;
		char Party;
	};
#pragma pack(pop)

	struct LuaField
	{
		void* LuaScript;
		Custom::string PlyMapLogin;
		Custom::string PlyItemUse;
		Custom::string TutorialStep;
		Custom::string PlyMapLogout;
		Custom::string ObjectDied;
		Custom::string ServantSummon;
		Custom::string RankingValue;
	};
	struct BoothItemManager
	{
		Custom::list<BoothItemInfo, Custom::allocator<BoothItemInfo> > bim_ItemList;
		unsigned int bim_nLastCreatedHandleNo;
	};

#pragma pack(push, 4)
	struct SellItemKeyNHandle
	{
		SHINE_ITEM_REGISTNUMBER nKey;
		unsigned int nItemHandle;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct BoothStoreInfo
	{
		unsigned short bsi_nOwnerHandle;
		SHINE_XY_TYPE bsi_Position;
		Custom::list<SellItemKeyNHandle, Custom::allocator<SellItemKeyNHandle> > bsi_SellItemList;
	};
#pragma pack(pop)

	struct BoothStoreManager
	{
		Custom::list<BoothStoreInfo, Custom::allocator<BoothStoreInfo> > bsm_StoreList;
	};

	struct BoothManager
	{
		BoothStoreManager bm_BoothStoreManager;
		BoothItemManager bm_BoothItemManager;
	};
	struct FieldFlag
	{
		char ff_CanUseReviveItem : 1;
		char ff_CanUseReviveSkill : 1;
	};

#pragma pack(push, 4)
	struct FieldMap
	{
		MapNameStruct fm_MapID;
		FieldAttr* fm_FieldOption;
		MapInfo* fm_MapInfo;
		MapBlockInformation* fm_BlockInfo;
		unsigned int fm_XSize;
		unsigned int fm_YSize;
		$70E7122D3FEE8B7C6F78D3C5EA0F573E fm_SlantedListPoint;
		unsigned int fm_KQHandle;
		unsigned short fm_KQID;
		void* fm_Multiflex;
		MobDeadCount fm_MobDeadCount;
		FieldBonus fm_FieldBonus;
		char fm_PKField;
		BroadcastFunc fm_BroadFunc;
		$054780A91BF37A2F1A0D085DD9DE9609 fm_GuildTournamentInform;
		VirtualMap fm_NavigatorMap;
		void* fm_pGuildTournamentSystem;
		int m_nGuildTournamentMapFlag;
		LinkInformTemplete m_SaveLinktoData;
		Custom::set<enum Enums::ABSTATEINDEX, Custom::less<enum Enums::ABSTATEINDEX>, Custom::allocator<enum Enums::ABSTATEINDEX> > fm_RefuseAbstate;
		Enums::CameraState fm_CameraState;
		LuaField fm_LuaScript;
		BoothManager fm_BoothManager;
		FieldFlag fm_FieldFlag;
		unsigned int fm_ReviveDelaySec;
		Enums::ID_LEVEL_TYPE fm_eLevelType;
	};
#pragma pack(pop)

	struct LuaAi
	{
		int test[57];
	};

#pragma endregion

	struct PROTO_NC_ITEM_MIX_ITEM_REQ
	{
		NetworkCommand netcmd;
		char nSubRaw;
		char nRawLeft;
		char nRawRight;
	};
	struct PROTO_NC_BAT_SKILLBASH_OBJ_CAST_REQ
	{
		NetworkCommand netcmd;
		unsigned short skill;
		unsigned short target;
	};

	struct PROTO_NC_BAT_SKILLBASH_FLD_CAST_REQ
	{
		NetworkCommand netcmd;
		unsigned short skill;
		SHINE_XY_TYPE locate;
	};
	struct EnumStruct
	{
		char exist;
		int value;
	};
	struct $735F3433F4102FB3A9B9C51174C7A94D
	{
		Enums::ABSTATEINDEX abstateidx;
		int strength;
		int sucrate;
	};

	struct RulesOfEngagement
	{
		void* vfptr;
	};
	struct ActiveSkillGroup
	{
		char InxName[32];
		Enums::ActiveSkillGroupIndex ActiveSkillGroupIndex;
	};

#pragma pack(push, 2)
	struct ToggleSkill
	{
		char TS_SkillInx[32];
		Enums::ToggleSkillEnum TS_Condition;
		unsigned short TS_Value;
	};
#pragma pack(pop)

	struct AreaSkillInfo
	{
		char AreaStep;
		char BMPIndex[32];
		Enums::ImagePinType EffectTarget;
		char bIsDirection;
		int AreaCenter_X;
		int AreaCenter_Y;
		int AreaSize;
		int AreaSize_X;
		int AreaSize_Y;
		char** AreaBMP;
	};
	struct SkillDataIndex
	{
		ActiveSkillInfoServer* sdi_ServInf;
		ActiveSkillInfo* sdi_Activ;
		Custom::vector<ActiveSkillGroup*, Custom::allocator<ActiveSkillGroup*>> sdi_ActiveSkillGroups;
		Custom::vector<ToggleSkill*, Custom::allocator<ToggleSkill*> > sdi_ToggleData;
		Custom::vector<AreaSkillInfo, Custom::allocator<AreaSkillInfo> > sdi_Area;
		SkillDataIndex* sdi_PrevSkill;
		SkillDataIndex* sdi_NextSkill;
		$735F3433F4102FB3A9B9C51174C7A94D sdi_Abstate[4];
		RulesOfEngagement* sdi_DamageRule;
		unsigned int sdi_AttackDist;
		EnumStruct sdi_HEALAMOUNT;
		EnumStruct sdi_CURE;
		EnumStruct sdi_DISPEL;
		EnumStruct sdi_TELEPORT;
		EnumStruct sdi_WHOLEHEALAMOUNT;
		EnumStruct sdi_MANABURN;
		EnumStruct sdi_UNDEADTODMG;
		EnumStruct sdi_DISPELALL;
		EnumStruct sdi_DISPELONE;
		EnumStruct sdi_DISPELRANDOM;
		EnumStruct sdi_WHOLEAGGRORATE;
		EnumStruct sdi_WHOLEAGGRORANGE;
		EnumStruct sdi_WARPING;
		EnumStruct sdi_DETECT;
		EnumStruct sdi_CROSSCOUNTER;
		EnumStruct sdi_THHPUP;
		EnumStruct sdi_DIEHPUP;
		EnumStruct sdi_REVIVAL;
		EnumStruct sdi_MAGICFIELD_TICK;
		EnumStruct sdi_MAGICFIELD_KEEP;
		EnumStruct sdi_STEALENCHANT;
		EnumStruct sdi_HPCONVERTSP;
		EnumStruct sdi_HPUPRATE;
		EnumStruct sdi_FLYDURINGCAST;
		EnumStruct sdi_SILVERWING;
		EnumStruct sdi_DISPELDEBUFF;
		EnumStruct sdi_DISPELCURSE;
		EnumStruct sdi_DISPELPOISON;
		EnumStruct sdi_DISPELDISEASE;
		EnumStruct sdi_DISPELDEEPER;
		EnumStruct sdi_WARPING_TARGET;
		EnumStruct sdi_JWALK;
		EnumStruct sdi_SHOOTME;
		EnumStruct sdi_FIRETIMEADD;
		EnumStruct sdi_CURSETIMEADD;
		EnumStruct sdi_HOLDME;
		EnumStruct sdi_POSIONTIMEADD;
		EnumStruct sdi_DMGCOLLTIMEDOWN;
		EnumStruct sdi_AREATYPE;
		EnumStruct sdi_BOMBDISPELALL;
		EnumStruct sdi_MAGICFIELD_PARTY;
		EnumStruct sdi_HEALFRIENDRATE;
		EnumStruct sdi_SETABSTATEFRIEND;
		EnumStruct sdi_RANDOMTARGETNUMBER;
		EnumStruct sdi_NEXTTARGETAREA;
		EnumStruct sdi_DMGDOWNRATE;
		EnumStruct sdi_MAXDMGDOWNRATE;
		EnumStruct sdi_SHOTSPEED;
		EnumStruct sdi_TARGETHPDOWNDMGUPRATE;
		EnumStruct sdi_JUMP;
		EnumStruct sdi_SETABSTATEME;
		EnumStruct sdi_NOTTARGET;
		EnumStruct sdi_ABKEEPTIME;
		EnumStruct sdi_RANDOMTARGET;
		EnumStruct sdi_TOPAGGRONO;
		EnumStruct sdi_MAGICFIELD_DELAY_START_TIME;
		EnumStruct sdi_BMP_MAGICFIELD_ROTATIONSPEED_RIGHT;
		EnumStruct sdi_DISPELABSTATE;
		EnumStruct sdi_RECALL;
		EnumStruct sdi_DMGSHARE;
		EnumStruct sdi_SUCKHP;
		EnumStruct sdi_RANDOMTARGETSPOT;
	};
	struct ShineItemAttr_ByteLot
	{
		char lot;
	};
	struct ShineItemAttr_WordLot
	{
		unsigned short lot;
	};
	struct ShineItemAttr_DwrdLot
	{
		unsigned int lot;
	};

	struct ShineItemAttr_QuestItem
	{
		unsigned short lot;
	};

	struct ShineDateTime
	{
		unsigned int year : 8;
		unsigned int month : 5;
		unsigned int date : 6;
		unsigned int hour : 6;
		unsigned int minute : 7;
	};

	struct ItemOptionStorage
	{
		struct unnamed_str
		{
			char identify : 1;
			char optionnum : 7;
		};
		union ItemOptionNumber
		{
			unnamed_str str;
			char bin;
		};
		struct FixedInfo
		{
			ItemOptionNumber optionnumber;
		};

#pragma pack(push, 1)
		struct Element
		{
			char itemoption_type;
			unsigned short itemoption_value;
		};
#pragma pack(pop)

		FixedInfo fixed;
		Element optionlist[8];
	};

#pragma pack(push, 2)
	struct ShineItemAttr_Amulet
	{
		ShineDateTime deletetime;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		char upgrade;
		char strengthen;
		char upgradefailcount;
		ItemOptionStorage UpgradeOption;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

	struct $846E78F8F1EB25D46D834A99261B9D61
	{
		unsigned short monster;
		unsigned int killcount : 28;
		unsigned int reserved : 4;
	};
#pragma pack(pop)

#pragma pack(push, 1)

	struct $FD2CF8E9010B3884B2A559AF78033A94
	{
		unsigned short elementalGemID;
		char restCount;
	};

	struct ShineItemAttr_Weapon
	{
		char upgrade;
		char strengthen;
		char upgradefailcount;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		$846E78F8F1EB25D46D834A99261B9D61 mobkills[3];
		unsigned short CharacterTitleMobID;
		char usertitle[21];
		$FD2CF8E9010B3884B2A559AF78033A94 gemSockets[3];
		char maxSocketCount;
		char createdSocketCount;
		ShineDateTime deletetime;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

	struct ShineItemAttr_Armor
	{
		char upgrade;
		char strengthen;
		char upgradefailcount;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		ShineDateTime deletetime;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

	struct ShineItemAttr_Shield
	{
		char upgrade;
		char strengthen;
		char upgradefailcount;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		ShineDateTime deletetime;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

	struct ShineItemAttr_Boot
	{
		char upgrade;
		char strengthen;
		char upgradefailcount;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		ShineDateTime deletetime;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

#pragma pack(pop)
	struct $34E5D5F0CB77496464955B2609C1079E
	{
		char IsPlaced : 1;
	};

#pragma pack(push, 4)
	struct ShineItemAttr_Furniture
	{
		$34E5D5F0CB77496464955B2609C1079E flag;
		unsigned short furnicherID;
		ShineDateTime deletetime;
		float LocX;
		float LocY;
		float LocZ;
		float Direct;
		ShineDateTime dEndureEndTime;
		char nEndureGrade;
		unsigned long long nRewardMoney;
	};
#pragma pack(pop)

	struct ShineItemAttr_Decoration
	{
		ShineDateTime deletetime;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
	};

	struct ShineItemAttr_SkillScroll
	{
	};

	struct ShineItemAttr_RecallScroll : ShineItemAttr_ByteLot
	{
	};

#pragma pack(push, 2)
	struct ShineItemAttr_BindItem_Bind
	{
		unsigned short mapid;
		unsigned int x;
		unsigned int y;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ShineItemAttr_BindItem
	{
		char portalnum;
		ShineItemAttr_BindItem_Bind portal[10];
	};
#pragma pack(pop)

	struct ShineItemAttr_UpSource : ShineItemAttr_ByteLot
	{
	};

	struct $ABC9A29A70D2308B55C82FBE1C48FDF2
	{
		char itemnum : 4;
		char flag : 4;
	};

#pragma pack(push, 1)
	struct ShineItemAttr_ItemChest
	{
		$ABC9A29A70D2308B55C82FBE1C48FDF2 type;
		SHINE_ITEM_REGISTNUMBER content[8];
	};
#pragma pack(pop)

	struct ShineItemAttr_WeaponTitleLicence
	{
	};

	struct ShineItemAttr_KingdomQuest
	{
	};

	struct ShineItemAttr_MiniHouseSkin
	{
		ShineDateTime deletetime;
	};

	struct ShineItemAttr_UpRed : ShineItemAttr_ByteLot
	{
	};

	struct ShineItemAttr_UpBlue : ShineItemAttr_ByteLot
	{
	};

	struct ShineItemAttr_UpGold : ShineItemAttr_ByteLot
	{
	};

	struct ShineItemAttr_KQStep : ShineItemAttr_WordLot
	{
	};

	struct ShineItemAttr_Feed : ShineItemAttr_ByteLot
	{
	};

	struct $424CA90C152D5080B0CCAE285A0AB46B
	{
		unsigned short ridenum : 15;
		unsigned short duringriding : 1;
	};

#pragma pack(push, 1)
	struct ShineItemAttr_Riding
	{
		unsigned short hungrypoint;
		ShineDateTime deletetime;
		$424CA90C152D5080B0CCAE285A0AB46B bitflag;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		unsigned int nHP;
		char nGrade;
		unsigned short nRareFailCount;
	};
#pragma pack(pop)

	struct ShineItemAttr_Amount
	{
		unsigned int amount;
	};

	struct ShineItemAttr_CostumWeapon
	{
		unsigned int CostumCharged;
	};

	struct ShineItemAttr_CostumShield
	{
		unsigned int CostumCharged;
	};

	struct ShineItemAttr_ActionItem
	{
		ShineDateTime deletetime;
	};

	struct ShineItemAttr_Enchant
	{
		char lot;
	};

	struct ShineItemAttr_GBCoin
	{
	};

#pragma pack(push, 4)
	struct ShineItemAttr_Capsule
	{
		SHINE_ITEM_REGISTNUMBER content;
		ShineDateTime useabletime;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ShineItemAttr_MobCardCollect_Unident
	{
		unsigned int SerialNumber;
		unsigned short CardID;
		char Star;
		unsigned short Group;
	};

	struct ShineItemAttr_MobCardCollect
	{
		unsigned int SerialNumber;
		char Star;
	};
#pragma pack(pop)

	struct ShineItemAttr_NoEffect : ShineItemAttr_ByteLot
	{
	};

	struct ShineItemAttr_ActiveSkill
	{
		unsigned short lot;
	};

#pragma pack(push, 2)
	struct ShineItemAttr_Pet
	{
		unsigned int nPetRegNum;
		unsigned int nPetID;
		char sName[17];
		char bSummoning;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ShineItemAttr_Bracelet
	{
		ShineDateTime deletetime;
		Enums::SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
		char upgrade;
		char strengthen;
		char upgradefailcount;
		char randomOptionChangedCount;
		ItemOptionStorage option;
	};

	union SHINE_ITEM_ATTRIBUTE
	{
		ShineItemAttr_ByteLot blot;
		ShineItemAttr_WordLot wlot;
		ShineItemAttr_DwrdLot dlot;
		ShineItemAttr_QuestItem qstitm;
		ShineItemAttr_Amulet amulet;
		ShineItemAttr_Weapon weapon;
		ShineItemAttr_Armor armor;
		ShineItemAttr_Shield shield;
		ShineItemAttr_Boot boot;
		ShineItemAttr_Furniture furniture;
		ShineItemAttr_Decoration decorate;
		ShineItemAttr_SkillScroll skillscroll;
		ShineItemAttr_RecallScroll recallscroll;
		ShineItemAttr_BindItem binditem;
		ShineItemAttr_UpSource upsource;
		ShineItemAttr_ItemChest itemchest;
		ShineItemAttr_WeaponTitleLicence weapontitlelicence;
		ShineItemAttr_KingdomQuest kingdomquest;
		ShineItemAttr_MiniHouseSkin minihouseskin;
		ShineItemAttr_UpRed upgraderedgem;
		ShineItemAttr_UpBlue upgradebluegem;
		ShineItemAttr_UpGold upgradegoldgem;
		ShineItemAttr_KQStep kqstep;
		ShineItemAttr_Feed feed;
		ShineItemAttr_Riding riding;
		ShineItemAttr_Amount amount;
		ShineItemAttr_CostumWeapon costumweapon;
		ShineItemAttr_CostumShield costumshield;
		ShineItemAttr_ActionItem actionitem;
		ShineItemAttr_Enchant Enchant;
		ShineItemAttr_GBCoin GBCoin;
		ShineItemAttr_Capsule Capsule;
		ShineItemAttr_MobCardCollect_Unident MobCard_Unident;
		ShineItemAttr_MobCardCollect MobCard;
		ShineItemAttr_NoEffect NoEffect;
		ShineItemAttr_ActiveSkill ActiveSkill;
		ShineItemAttr_Pet Pet;
		ShineItemAttr_Bracelet Bracelet;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct SHINE_ITEM_STRUCT
	{
		unsigned short ItemID;
		SHINE_ITEM_ATTRIBUTE Attributes;
	};

	struct ItemTotalInformation
	{
		SHINE_ITEM_REGISTNUMBER iti_registnum;
		SHINE_ITEM_STRUCT Structure;
	};

	struct ItemAttributeClassVtbl
	{
		void* (__thiscall* destructor)(ItemAttributeClass*, unsigned int);
		BYTE gap4[24];
		unsigned int(__thiscall* iac_GetLot)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		void(__thiscall* iac_SetLot)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, unsigned int);
		int(__thiscall* iac_equipbriefinfo)(ItemAttributeClass*, unsigned short, NetworkCommand*, SHINE_ITEM_STRUCT*, int, unsigned short*, char*);
		int(__thiscall* iac_ItemClass)(ItemAttributeClass*);
		char(__thiscall* iac_DropItemMake)(ItemAttributeClass*, ItemTotalInformation*, void* ItemGroup, int, unsigned short);
		int(__thiscall* iac_Getupgrade)(ItemAttributeClass*, ItemTotalInformation*);
		ShineDateTime* (__thiscall* iac_GetDeteleDateTime)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		ShineDateTime* (__thiscall* iac_SetDeteleDateTime)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, int, tm*, int);
		void(__thiscall* iac_FoodEat)(ItemAttributeClass*, ItemTotalInformation*, int, int);
		int(__thiscall* iac_GetHungry)(ItemAttributeClass*, ItemTotalInformation*);
		ShineItemAttr_ItemChest* (__thiscall* iac_Getitemchest)(ItemAttributeClass*, ItemTotalInformation*);
		int(__thiscall* iac_wptitle_Setlicense)(ItemAttributeClass*, ItemTotalInformation*, unsigned short, Name5*);
		unsigned int(__thiscall* iac_wptitle_mobkilladd)(ItemAttributeClass*, ItemTotalInformation*, unsigned short, unsigned int);
		char(*(__thiscall* iac_wptitle_Gettitle)(ItemAttributeClass*, ItemTotalInformation*))[21];
		bool(__thiscall* iac_wptitle_Settitle)(ItemAttributeClass*, ItemTotalInformation*, unsigned int, char(*)[21]);
		unsigned short(__thiscall* iac_wptitle_Getlicencemob)(ItemAttributeClass*, void* MobDataBox, void* ItemDataBox, ItemTotalInformation*);
		int(__thiscall* iac_StepGet)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		char(__thiscall* iac_GetDuringRide)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		void(__thiscall* iac_SetDuringRide)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, char);
		int(__thiscall* iac_GetAmount)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		void(__thiscall* iac_SetAmount)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, int);
		ItemOptionStorage* (__thiscall* iac_GetItemOptionStruct)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		char(__thiscall* iac_GetRandomOptionChangeCount)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		void(__thiscall* iac_SetRandomOptionChangeCount)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, char);
		unsigned short(__thiscall* iac_GetItemOptionUpgrade)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, char);
		void(__thiscall* iac_SetItemOptionUpgrade)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, char, unsigned short);
		void(__thiscall* iac_ClearItemOptionUpgrade)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		void(__thiscall* iac_SetFurnitureKey)(ItemAttributeClass*, ItemTotalInformation*, unsigned short);
		ShineDateTime* (__thiscall* iac_GetEndureEndTime)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		int(__thiscall* iac_SetEndureEndTime)(ItemAttributeClass* self, ItemTotalInformation* totaliteminfo, unsigned short x, unsigned short y, tm* z);
		int(__thiscall* iac_SetEndureEndTime2)(ItemAttributeClass* self, ItemTotalInformation* totaliteminfo, ShineDateTime* date);
		void(__thiscall* iac_SetEndureGrade)(ItemAttributeClass*, ItemTotalInformation*, char);
		int(__thiscall* iac_GetChargedNumber)(ItemAttributeClass*, ItemTotalInformation*);
		void(__thiscall* iac_SetChargedNumber)(ItemAttributeClass*, ItemTotalInformation*, int);
		Enums::SHINE_PUT_ON_BELONGED_ITEM(__thiscall* iac_GetIsPutOnBelonged)(ItemAttributeClass*, ItemTotalInformation*);
		int(__thiscall* iac_SetIsPutOnBelonged)(ItemAttributeClass*, ItemTotalInformation*, Enums::SHINE_PUT_ON_BELONGED_ITEM);
		ShineDateTime* (__thiscall* iac_GetUseableDateTime)(ItemAttributeClass*, SHINE_ITEM_STRUCT*);
		ShineDateTime* (__thiscall* iac_SetUseableDateTime)(ItemAttributeClass*, SHINE_ITEM_STRUCT*, int, tm*, int);
		void(__thiscall* iac_SetHP)(ItemAttributeClass*, ItemTotalInformation*, unsigned int);
		unsigned int(__thiscall* iac_GetHP)(ItemAttributeClass*, ItemTotalInformation*);
		void(__thiscall* iac_SetGrade)(ItemAttributeClass*, ItemTotalInformation*, char);
		char(__thiscall* iac_GetGrade)(ItemAttributeClass*, ItemTotalInformation*);
		void(__thiscall* iac_SetRareFailCount)(ItemAttributeClass*, ItemTotalInformation*, unsigned short);
		unsigned short(__thiscall* iac_GetRareFailCount)(ItemAttributeClass*, ItemTotalInformation*);
	};
#pragma pack(pop)

	struct ItemAttributeClass
	{
		ItemAttributeClassVtbl* vfptr;
	};

	struct ItemInventoryCell
	{
		ItemTotalInformation ItemInformation;
		ItemAttributeClass* iic_AttrProc;
	};

#pragma pack(push,1)
	struct ItemInfo
	{
		unsigned short ID;
		char InxName[32];
		char Name[64];
		Enums::ItemTypeEnum Type;
		Enums::ItemClassEnum Class;
		unsigned int MaxLot;
		Enums::ItemEquipEnum Equip;
		Enums::AuctionGroup ItemAuctionGroup;
		Enums::GradeType ItemGradeType;
		char TwoHand;
		unsigned int AtkSpeed;
		unsigned int DemandLv;
		unsigned int Grade;
		unsigned int MinWC;
		unsigned int MaxWC;
		unsigned int AC;
		unsigned int MinMA;
		unsigned int MaxMA;
		unsigned int MR;
		unsigned int TH;
		unsigned int TB;
		unsigned int WCRate;
		unsigned int MARate;
		unsigned int ACRate;
		unsigned int MRRate;
		unsigned int CriRate;
		unsigned int CriMinWc;
		unsigned int CriMaxWc;
		unsigned int CriMinMa;
		unsigned int CriMaxMa;
		unsigned int CrlTB;
		Enums::UseClassType UseClass;
		unsigned int BuyPrice;
		unsigned int SellPrice;
		char BuyDemandLv;
		unsigned int BuyFame;
		unsigned int BuyGToken;
		unsigned int BuyGBCoin;
		Enums::WeaponTypeEnum WeaponType;
		Enums::ArmorTypeEnum ArmorType;
		char UpLimit;
		unsigned short BasicUpInx;
		unsigned short UpSucRatio;
		unsigned short UpLuckRatio;
		char UpResource;
		unsigned short AddUpInx;
		unsigned int ShieldAC;
		unsigned int HitRatePlus;
		unsigned int EvaRatePlus;
		unsigned int MACriPlus;
		unsigned int CriDamPlus;
		unsigned int MagCriDamPlus;
		Enums::E_BelongType BT_Inx;
		char TitleName[32];
		char ItemUseSkill[32];
		char SetItemIndex[32];
		Enums::ItemFuncEnum ItemFunc;
	};
#pragma pack(pop)
#pragma pack(push,2)
	struct ItemInfoServer
	{
		unsigned int ID;
		char InxName[32];
		char MarketIndex[20];
		char City[1];
		char DropGroupA[40];
		char DropGroupB[40];
		char RandomOptionDropGroup[33];
		unsigned int Vanish;
		unsigned int looting;
		unsigned short DropRateKilledByMob;
		unsigned short DropRateKilledByPlayer;
		Enums::ISEType ISET_Index;
		char ItemSort_Index[32];
		char KQItem;
		char PK_KQ_USE;
		char KQ_Item_Drop;
		char PreventAttack;
	};
#pragma pack(pop)

	struct GradeItemOption
	{
		char ItemIndex[32];
		unsigned short STR;
		unsigned short CON;
		unsigned short DEX;
		unsigned short INT;
		unsigned short MEN;
		unsigned short ResistPoison;
		unsigned short ResistDeaseas;
		unsigned short ResistCurse;
		unsigned short ResistMoveSpdDown;
		unsigned short ToHitRate;
		unsigned short ToBlockRate;
		unsigned short MaxHP;
		unsigned short MaxSP;
		unsigned short WCPlus;
		unsigned short MAPlus;
	};

	struct ItemDropLog
	{
		unsigned int ItemID;
	};

	struct ItemMoney
	{
		char IM_ItemIDX[32];
		char IM_MoneyIDX[32];
		unsigned short IM_MoneyLot;
	};

	struct ItemDataBoxIndex
	{
		ItemInfo* data;
		ItemInfoServer* dataserv;
		GradeItemOption* itemoption;
		char MovingShot;
		unsigned short AttackAngle;
		unsigned short SetItemIndex;
		unsigned short HitTimeArray[3];
		ItemDropLog* itemdroplog;
		char ItemSortOrder;
		Enums::DelConditionType eDelConditionType;
		ItemMoney* pBuyItemData;
	};

	struct Metronome
	{
		unsigned int m_NextTick;
		unsigned int m_TickInterval;
	};

	namespace SetItemData
	{
#pragma pack(push, 2)
		struct PlayerSetEffect
		{
			unsigned short effectarray[10];
			char effectnumber;
		};
#pragma pack(pop)

		struct SetItemAbstateEffect
		{
			struct EffectBuffer
			{
				unsigned short eb_Index;
				unsigned short Argument_Base1000;
			};

			EffectBuffer siae_Buffer[4];
		};
	}

	namespace MiscDataTable
	{
		struct MiscData_AbState
		{
			enum EquipWhere
			{
				EW_NONE = 0x0,
				EW_LEFTHAND = 0x1,
			};

			enum EquipClass
			{
				EC_NONE = 0x0,
				EC_SHIELD = 0x1,
			};

			struct unnamed_type_mdas_ResetCondition
			{
				char run : 1;
				char walk : 1;
				char attack : 1;
				char attacked : 1;
			};

			struct unnamed_type_mdas_ResetEquipment
			{
				EquipWhere eqwhere;
				EquipClass eqclass;
			};

			unsigned short mdas_AbStateID;
			unnamed_type_mdas_ResetCondition mdas_ResetCondition;
			unnamed_type_mdas_ResetEquipment mdas_ResetEquipment;
		};
	}

	struct SubAbStateInfo
	{
		unsigned short ID;
		char InxName[32];
		unsigned int Strength;
		Enums::SubState Type;
		char SubType;
		unsigned int KeepTime;
		Enums::SubAbstateAction ActionIndexA;
		unsigned int ActionArgA;
		Enums::SubAbstateAction ActionIndexB;
		unsigned int ActionArgB;
		Enums::SubAbstateAction ActionIndexC;
		unsigned int ActionArgC;
		Enums::SubAbstateAction ActionIndexD;
		unsigned int ActionArgD;
	};

#pragma pack(push, 1)
	struct AbnormalStateInfo
	{
		unsigned short ID;
		char InxName[32];
		Enums::ABSTATEINDEX AbStataIndex;
		unsigned int KeepTimeRatio;
		char KeepTimePower;
		char StateGrade;
		char PartyState1[32];
		char PartyState2[32];
		char PartyState3[32];
		char PartyState4[32];
		char PartyState5[32];
		unsigned int PartyRange;
		unsigned int PartyEnchantNumber;
		char SubAbState[32];
		Enums::DispelAttr DispelIndex;
		Enums::SubDispelAttr SubDispelIndex;
		Enums::AbStateSaveTypeEnum AbStateSaveType;
		char MainStateInx[32];
		char Duplicate;
	};

	struct AbStateSaveTypeInfo
	{
		Enums::AbStateSaveTypeEnum AbStateSaveType;
		char IsSaveLink;
		char IsSaveDie;
		char IsSaveLogoff;
	};

#pragma pack(pop)

	namespace AbnormalStateDictionary
	{
		namespace AbState
		{
			struct AbStateStr
			{
				struct AbStateStrArgument
				{
					struct unnamed_type_assa_Effect
					{
						Enums::SubAbstateAction action;
						int value;
					};

					SubAbStateInfo* assa_info;
					unnamed_type_assa_Effect assa_Effect[4];
				};

				AbnormalStateInfo* index;
				AbStateSaveTypeInfo* pSaveTypeInfo;
				int* debuffresist;
				AbStateStrArgument subabstate[40];
			};
		}
	}

	namespace AbnormalStateContainer
	{
		struct AbStateElementSetData
		{
			SHINE_XY_TYPE CenterLoc;
		};

		struct AbstateElementInObject
		{
			struct unnamed_type_aeo_Flag
			{
				char f_Cured : 1;
				char f_Dispeled : 1;
				char f_SystemRemove : 1;
			};

			unnamed_type_aeo_Flag aeo_Flag;
			Enums::ABSTATEINDEX aeo_Index;
			struct unnamed_type_aeo_Caster
			{
				ShineObjectClass::ShineObject* obj;
				unsigned int chrregnum;
				char nLevel;
				int nAttackPower;
			};

			unnamed_type_aeo_Caster aeo_Caster;
			char aeo_Strength;
			struct ASE_Tick
			{
				unsigned int start;
				unsigned int terminate;
				Metronome nextaction;
			};

			ASE_Tick aeo_Tick;
			struct unnamed_type_aeo_PartyEnchant
			{
				Enums::ABSTATEINDEX soul;
				AbnormalStateDictionary::AbState::AbStateStr* skillindex;
			};

			unnamed_type_aeo_PartyEnchant aeo_PartyEnchant[5];
			int aeo_RestCount;
			AbStateElementSetData AbsSetData;
			SetItemData::SetItemAbstateEffect aeo_SetItemEffect;
			MiscDataTable::MiscData_AbState* aeo_MiscData;
		};
	}

#pragma pack(push, 2)
	struct BoothItemInfo
	{
		char bii_nDataSize;
		unsigned int bii_nItemHandle;
		unsigned short bii_nOwnerHandle;
		unsigned long long bii_nUnitPrice;
		SHINE_ITEM_STRUCT bii_ItemInfo;
	};
#pragma pack(pop)

	struct ItemBagVtbl
	{
		ItemInventoryCell* (__thiscall* ib_GetInventoryCell)(ItemBag* self, int);
		int(__thiscall* ib_BagSizeInput)(ItemBag* self, void* ChargedEffectContainer);
		int(__thiscall* ib_BagSizeOutput)(ItemBag* self);
		char(__thiscall* ib_GetInvenType)(ItemBag* self);
	};

	struct ItemBag
	{
		ItemBagVtbl* vfptr;
	};

	struct EquipmentViewSlot
	{
		char bEquip;
		char nMainSlot;
		unsigned short nItemID;
	};

#pragma pack(push, 4)
	struct ItemEquipment : ItemBag
	{
		ItemInventoryCell ie_Array[30];
		char ie_DecoActCount;
		unsigned short ie_DecoActList[30];
		EquipmentViewSlot ie_ViewSlot[30];
	};
#pragma pack(pop)

	struct ItemInventory : ItemBag
	{
		ItemInventoryCell ii_Array[192];
	};

	struct ItemQuestItemBox : ItemBag
	{
		ItemInventoryCell iqb_Array[5];
	};

	struct ItemMiniHouseBox : ItemBag
	{
		ItemInventoryCell imhb_Array[35];
	};

#pragma pack(push, 2)
	struct ItemInform_ActionItem
	{
		union unnamed_type_iiai_Attribute
		{
			ShineItemAttr_ActionItem ActionItem;
		};

		SHINE_ITEM_REGISTNUMBER iiai_RegistNumber;
		unsigned short iiai_ItemID;
		unnamed_type_iiai_Attribute iiai_Attribute;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct ChargedEffectContainer
	{
		struct unnamed_type_cec_ProveOfBless
		{
			char bless;
			unsigned short blesshandle;
		};

		char cec_SilverWingCoolTime_Minute;
		unsigned short cec_HPStoneLimit;
		unsigned short cec_SPStoneLimit;
		unnamed_type_cec_ProveOfBless cec_ProveOfBless;
		char cec_MoreInven;
		char cec_MoreStorage;
		char cec_StreetBoothSlot;
		char cec_LighteningPickParts;
		unsigned short cec_MaxHPRate;
		unsigned short cec_MaxSPRate;
		unsigned short cec_AttackForceRate1024;
		unsigned short cec_DefendForceRate1024;
		unsigned short cec_ItemDropRate;
		char cec_MoverNotHungry;
		char cec_MoreStat;
		unsigned short cec_ExpBonus;
		unsigned short cec_ItemPowerAttack;
		unsigned short cec_ItemPowerDefence;
		unsigned short cec_ProductCastTimeRate;
		unsigned short cec_ProductMasteryRate;
		char cec_StorageAnywhere;
		unsigned short cec_MaxLPRate;
		char cec_IsAutoPathFind;
		char cec_ChatFontColor;
		char cec_ChatBalloonColor;
		char cec_ChatColor;
		char cec_ExpHold;
	};
#pragma pack(pop)

	template<typename S>
	struct ItemInventorySmallCell // <ItemInform_ActionItem>
	{
		S iisc_Item;
		ItemAttributeClass* iisc_AttrProc;
	};

	template<typename S>
	struct ItemSmallBag_vtbl // template<typename S>
	{
		ItemInventorySmallCell<S>* (__thiscall* isb_GetInventoryCell)(ItemSmallBag<S>* self, int);
		int(__thiscall* isb_BagSizeInput)(ItemSmallBag<S>* self, ChargedEffectContainer*);
		int(__thiscall* isb_BagSizeOutput)(ItemSmallBag<S>* self);
	};

	template<typename S>
	struct ItemSmallBag // <ItemInform_ActionItem>
	{
		ItemSmallBag_vtbl<S>* vft;
	};

	struct ItemActionItemBox : ItemSmallBag<ItemInform_ActionItem>
	{
		ItemInventorySmallCell<ItemInform_ActionItem> iaib_Array[42];
	};

	struct CharacterInventory
	{
		ItemEquipment ci_Equipment;
		ItemInventory ci_Inventory;
		ItemQuestItemBox ci_QuestBox;
		ItemMiniHouseBox ci_MiniHouse;
		ItemActionItemBox ci_ActionBox;
	};

	struct ReservedQuantity
	{
		int cen;
		int fame;
		int hpstone;
		int spstone;
		int guild_token;
		int gbcoin;
	};

	struct InvenCellReleaserVtbl
	{
		void(__thiscall* icr_Apply)(InvenCellReleaser* self, ShineObject*, InventoryLocking::LockedCell*, char);
		void(__thiscall* icr_Reserv)(InvenCellReleaser* self, ReservedQuantity*, InventoryLocking::LockedCell*);
		char(__thiscall* icr_IsOnlyLock)(InvenCellReleaser* self);
		void(__thiscall* lc_Free)(InvenCellReleaser* self, ShineObject*);
	};

#pragma pack(push, 4)
	struct InventoryCellLock
	{
		void* vfptr;
		unsigned short icl_Index;
	};
#pragma pack(pop)

	struct InvenCellReleaser
	{
		InvenCellReleaserVtbl* vfptr;
	};

#pragma pack(push, 1)
	struct $6880877F8E506DFB757B607B349F32B6
	{
		SHINE_ITEM_REGISTNUMBER nSellItemKey;
		ItemTotalInformation ItemTotalInfo;
	};
#pragma pack(pop)

	struct $E4B97847A3DFD463A4A72B12617C7616
	{
		unsigned short nHandle;
	};

	struct $260390A2FE36DBD69022EEC65CAA984B
	{
		ItemInventoryCell* Cell;
		unsigned short CardID;
		unsigned int Serial;
		int StarNum;
		int Slot;
		Enums::CHARACTER_TITLE_TYPE CharTitle;
	};

#pragma pack(push, 4)
	struct $36FD6762D2EDF94422EB0FBF1B1AFFB5
	{
		ItemTotalInformation Card;
		ItemInventoryCell* Cell;
		ITEM_INVEN InvenLoc;
	};
#pragma pack(pop)

#pragma pack(push, 8)
	struct $4754507F0C56DDB9AFF07542020E9954
	{
		unsigned long long coin;
		short plusminus;
		char exchange;
	};
#pragma pack(pop)

	struct SHINE_INVEN_SLOT_INFO
	{
		SHINE_ITEM_REGISTNUMBER ItmeReg;
		unsigned short ItemID;
		ITEM_INVEN inven;
		unsigned int Lot;
	};

#pragma pack(push, 1)
	struct $FE0AABDF6277674538BFF0BFE645689A
	{
		SHINE_INVEN_SLOT_INFO zr_from;
		SHINE_INVEN_SLOT_INFO zr_to;
		ItemTotalInformation zr_changeiteminfo;
	};
#pragma pack(pop)

#pragma pack(push, 8)
	struct $6B256EFC2D8121C62A1B56A38F74D56B
	{
		unsigned long long cen;
		short plusminus;
	};
#pragma pack(pop)

#pragma pack(push, 4)
	struct $EB1C94DF9FB383166EE4AF121D704A62
	{
		unsigned int fame;
		short plusminus;
	};
#pragma pack(pop)

	struct $65A3D46E44A2EEE6FFA3B430DC90E549
	{
		ItemInventoryCell* cell;
	};

#pragma pack(push, 2)
	struct $7C275992C84AB913A9BDBE9C415F718D
	{
		ItemInventoryCell* cell;
		ItemTotalInformation iti;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct $05E53F9077587ADED4D35AA799008AED
	{
		ITEM_INVEN cell;
		ItemTotalInformation iti;
	};
#pragma pack(pop)

	struct $0102FC4731AA6CDA22676E002271E217
	{
		int equipslot;
		ItemInventoryCell* equipcell;
		int otherslot;
		ItemInventoryCell* othercell;
	};

	struct $71B0E696E25AE5A109BA18C6A9DF0B75
	{
		ItemTotalInformation iti;
		void* useitemclass;
	};

	struct $6A16A3955AC42113F6F1D74869860FB2
	{
		int flag;
		int num;
	};

#pragma pack(push, 4)
	struct $2428498D21A4EE16E5A5FB414E612598
	{
		int exp;
		int fame;
		char ct_type;
		char ct_elementno;
	};
#pragma pack(pop)

	struct $5F42012549A6CF058EFF23E52F7BECFB
	{
		LinkInformTemplete Link;
	};

#pragma pack(push, 2)
	union $A2F39EA2A6D2C55147FFF741C43D4F89
	{
		$6B256EFC2D8121C62A1B56A38F74D56B cenchange;
		$EB1C94DF9FB383166EE4AF121D704A62 famechange;
		$65A3D46E44A2EEE6FFA3B430DC90E549 cellclear;
		$7C275992C84AB913A9BDBE9C415F718D cellchange;
		$05E53F9077587ADED4D35AA799008AED cellchangesmall;
		$0102FC4731AA6CDA22676E002271E217 equipchange;
		$71B0E696E25AE5A109BA18C6A9DF0B75 itemuse;
		$6A16A3955AC42113F6F1D74869860FB2 pointstone;
		$2428498D21A4EE16E5A5FB414E612598 questreward;
		$5F42012549A6CF058EFF23E52F7BECFB linkinfo;
		$FE0AABDF6277674538BFF0BFE645689A zonerng;
		$4754507F0C56DDB9AFF07542020E9954 coinchange;
		$36FD6762D2EDF94422EB0FBF1B1AFFB5 CardOpen;
		$260390A2FE36DBD69022EEC65CAA984B CardRegist;
		$6880877F8E506DFB757B607B349F32B6 ItemSell;
		$E4B97847A3DFD463A4A72B12617C7616 ItemRepurchase;
	};
#pragma pack(pop)

	struct DeadCheck
	{
		enum DC_DeadCause
		{
			DC_LIVE = 0x0,
			DC_DOT = 0x1,
			DC_ATTACK = 0x2,
			DC_ATTACK2 = 0x3,
			DC_SELFKILL = 0x4,
			DC_SKILL = 0x5,
		};

		DC_DeadCause dc_Cause;
	};

#pragma pack(push, 2)
	struct PROTO_NC_ACT_SOMEONEMOVEWALK_CMD
	{
		struct unnamed_type_moveattr
		{
			unsigned short direct : 1;
		};

		unsigned short handle;
		SHINE_XY_TYPE from;
		SHINE_XY_TYPE to;
		unsigned short speed;
		unnamed_type_moveattr moveattr;
	};
#pragma pack(pop)

	namespace AbnormalStateContainer
	{
		struct AbstateListInObject
		{
			AbstateElementInObject asl_Element[28];
			List<AbstateElementInObject> asl_List;
		};
	}

	struct MoveManager
	{
#pragma pack(push, 4)
		struct unnamed_type_mm_vector
		{
			unsigned int x;
			bool xPositive;
			unsigned int y;
			bool yPositive;
		};
#pragma pack(pop)

		enum MMState
		{
			MM_HALT = 0x0,
			MM_WALK = 0x1,
			MM_RUN = 0x2,
			MM_REINFORCEMOVE = 0x3,
		};

		MMState mm_state;
		ShineObjectClass::ShineMobileObject* mm_object;
		int mm_charSpeed;
		SHINE_XY_TYPE mm_startPos;
		SHINE_XY_TYPE mm_goalPos;
		unsigned int mm_startTime_ms;
		unsigned int mm_fullTime_ms;
		unsigned int mm_currTime_ms;
		unsigned int mm_lastTime_ms;
		unsigned int mm_leftTime_ms;
		unnamed_type_mm_vector mm_vector;
	};

	struct BitANDInt
	{
		unsigned int value;
		unsigned int mask;
	};

	namespace SpyNet
	{
		enum SecretReportType
		{
			SRT_EOR = 0x0,
			SRT_GETHEAL = 0x1,
			SRT_SOMEONE_GIVE_ABSTATE = 0x2,
			SRT_SOMEONE_REMOVE_ABSTATE = 0x3,
			SRT_VANISH_ABSTATE = 0x4,
		};

		struct SecretReport
		{
			union unnamed_type_sr_Report
			{
				struct GetHeal
				{
					ShineObjectClass::ShineObject* healer;
					int healingup;
					int aggrorate;
				};

				struct SomeoneGiveAbState
				{
					ShineObjectClass::ShineObject* caster;
					unsigned short stateid;
					char strength;
					int aggropoint;
				};

#pragma pack(push, 2)
				struct SomeoneRemoveABState
				{
					ShineObjectClass::ShineObject* caster;
					unsigned short stateid;
					char strength;
				};
#pragma pack(pop)

				struct VanishAbState
				{
					unsigned short stateid;
				};

				GetHeal getheal;
				SomeoneGiveAbState someonegiveabstate;
				SomeoneRemoveABState someoneremoveabstate;
				VanishAbState vanishabstate;
			};

			SecretReportType sr_Type;
			unnamed_type_sr_Report sr_Report;
		};

		struct EspionageAgent
		{
			SecretReport ea_SecretReport[16];
			BitANDInt ea_Pointer;
		};

		struct IntelligenceOffice_vtbl
		{
			void(__thiscall* IntelligenceOffice_Destructor)(IntelligenceOffice* self);
			void(__thiscall* io_SRT_GETHEAL)(IntelligenceOffice* self, ShineObjectClass::ShineObject*, SecretReport*);
			void(__thiscall* io_SRT_SOMEONE_GIVE_ABSTATE)(IntelligenceOffice* self, ShineObjectClass::ShineObject*, SecretReport*);
			void(__thiscall* io_SRT_SOMEONE_REMOVE_ABSTATE)(IntelligenceOffice* self, ShineObjectClass::ShineObject*, SecretReport*);
			void(__thiscall* io_SRT_VANISH_ABSTATE)(IntelligenceOffice* self, ShineObjectClass::ShineObject*, SecretReport*);
		};

		struct IntelligenceOffice
		{
			IntelligenceOffice_vtbl* vft;
			BitANDInt io_Pointer;
		};

		struct IntelligenceOffice4Mob : IntelligenceOffice
		{
		};
	}

	namespace ShineObjectClass
	{
#pragma pack(push, 1)
		struct ShineObject
		{
			ShineObjectVtable* vtable;
			ShineObjectHandleUnion handleUnion;
			$13BC111DC65433BF9F06B1A52F67E675 so_slantedlist;
			$5E684959B77675D5191741C5366AF829 so_LocateInfo;
			$C7AF70B47C699662F9010C1970821EBE so_layer;
			FieldMap* so_Field;
			LuaAi so_AIScript;
			char so_bIsMapMarking;
			Enums::OBJECT_SIGHT_STATE so_eSightState;
		};
#pragma pack(pop)
	}

#pragma pack(push, 4)
	struct ORErrorMessage
	{
		int orem_Line;
		char* orem_Message;
		char orem_Err;
	};
#pragma pack(pop)

	struct ORDelimiter
	{
		char ord_Array[32];
		int ord_Number;
	};

	struct ORExchange
	{
		struct unnamed_type_ore_Array
		{
			char from;
			char to;
		};

		unnamed_type_ore_Array ore_Array[32];
		int ore_Number;
	};

	struct ORComment
	{
		char orc_Comment;
	};

	struct ORBrace
	{
		char orc_Open;
		char orc_Close;
	};

	struct ORIgnore
	{
		char ori_Array[32];
		int ori_Number;
	};

	struct TokenArgument
	{
		ORErrorMessage errmsg;
		ORDelimiter delimiter;
		ORExchange exchange;
		ORComment comment;
		ORBrace brace;
		ORIgnore ignore;
	};

	struct ORLinebuffer
	{
		_iobuf* orlb_fp;
		char orlb_Buffer[4096];
		int orlb_LineLen;
		int orlb_Pointer;
	};

	struct ORTokenReader
	{
		ORLinebuffer ortr_LineBuffer;
		TokenArgument* ortr_Argument;
		char ortr_Buffer[2048];
	};

	struct ORColumnHeader_vtbl
	{
		int(__thiscall* ortr_SetLength)(ORColumnHeader* self, ORTokenReader*, TokenArgument*);
		int(__thiscall* orch_FieldType)(ORColumnHeader* self);
	};

	struct ORColumnHeader
	{
		ORColumnHeader_vtbl* vtable /*VFT*/;
		int orch_Length;
		ORToken orch_ColumnName;
	};

	struct ORColumnHeaderList
	{
		ORColumnHeader* orchl_fieldname[512];
	};

	struct ORField_vtbl
	{
		char(__thiscall* orf_CompareContent)(ORField* self, char*, ORToken*);
		int(__thiscall* orf_Alloc)(ORField* self, char*);
		char(__thiscall* orf_Read)(ORField* self, ORTokenReader*);
		void* (__thiscall* orf_GetBuffer)(ORField* self);
		int(__thiscall* orf_GetType)(ORField* self);
	};

	struct ORField
	{
		ORField_vtbl* vft;
		ORColumnHeader* orf_Header;
	};

	struct ORRecord
	{
		ORField* orr_FieldArray[512];
		char* orr_Buffer;
		int orr_Pointer;
	};

	struct ORKeyList
	{
		struct KeyElement
		{
			ORToken key;
			ORRecord* rec;
		};

		KeyElement okl_Element[1024];
		int okl_KeyNum;
	};

	struct ORTable
	{
		ORToken ort_TableName;
		int ort_RecordLength;
		ORColumnHeaderList ort_HeaderList;
		ListArray<ORRecord> ort_DataArray;
		List<ORRecord> ort_DataRecord;
		ORKeyList* ort_PrimaryKey;
	};

	struct OptionReader
	{
		TokenArgument or_Argument;
		List<ORTable> or_TableList;
		ORTable or_TableArray[32];
		ORTable* or_CurrentTable;
		Custom::string m_strFileName;
	};

	struct DuringBattle
	{
		unsigned int db_lasthit;
	};

	namespace Parameter
	{
		struct Cluster
		{
			int Str;
			int Con;
			int Dex;
			int Int;
			int Men;
			int WCmin;
			int WCmax;
			int AC;
			int TH;
			int TB;
			int MAmin;
			int MAmax;
			int MR;
			int MH;
			int MB;
			int AbsoluteAttack;
			int AbsoluteDefend;
			int AbsoluteHit;
			int AbsoluteBlock;
			int MoveSpeed;
			int HPRecover;
			int SPRecover;
			int CastingTime;
			int Critical;
			int PhisycalWeaponMastery;
			int MagicalWeaponMastery;
			int ShieldAC;
			int HitRate;
			int EvaRate;
			int MACri;
			int CriDam;
			int MagCriDam;
			int CriDamRate;
			int MagCriDamRate;
			int AttSpeed;
			int MaxHP;
			int MaxHP_2;
			int MaxSP;
			int HPAbsorption_Hitted;
			int SPAbsorption_Hitted;
			int HPAbsorption_Hit;
			int SPAbsorption_Hit;
			int CriticalTB;
			int RegistNone;
			int ResistPoison;
			int ResistDeaseas;
			int ResistCurse;
			int ResistMoveSpdDown;
			int ResistGTI;
			int MaxLP;
			int LPRecover;
		};

		struct ChangeByConditionParam
		{
			unsigned short cbcp_nID;
			unsigned int cbcp_nCondition;
			unsigned int cbcp_nChange;
			int cbcp_nChangeParam;
			int cbcp_nCharged;
			char cbcp_nMaxValueNum;
			int* cbcp_pValue;
		};

#pragma pack(push, 4)
		struct Container
		{
			struct unnamed_type_Item
			{
				Cluster Plus;
				Cluster Rate;
			};

			struct unnamed_type_DotDamagePlus
			{
				short Burn;
				short Poison;
				short Desease;
				short Blooding;
				short PitBlooding;
			};

			struct unnamed_type_flag
			{
				char cannotmove_stun : 1;
				char cannotmove_entangle : 1;
				char cannotattack : 1;
			};

			Cluster PureCharParam;
			unnamed_type_Item Item;
			unnamed_type_Item ItemPowerRate;
			unnamed_type_Item Upgrade;
			unnamed_type_Item WeaponTitle;
			unnamed_type_Item PassiveSkill;
			unnamed_type_Item AbnormalState;
			unnamed_type_Item LastTune;
			Cluster Total;
			unnamed_type_DotDamagePlus DotDamagePlus;
			short SPRate;
			short RangeEvasion;
			unnamed_type_flag flag;
			unsigned short MissPercentFix;
			unsigned short DamageReflection;
			unsigned short ChangeAbilityInfo;
			unsigned short HealRate;
			unsigned short PassiveBuffKeepTimeUPRate;
			unsigned short PassiveHealRate;
			unsigned short PassiveCriDamageRatePlus;
			ChangeByConditionParam PassiveHPDownRateWCMin;
			ChangeByConditionParam PassiveHPDownRateWCMax;
			ChangeByConditionParam PassiveHPDownRateMAMin;
			ChangeByConditionParam PassiveHPDownRateMAMax;
			ChangeByConditionParam PassiveHPDownRateAC;
			ChangeByConditionParam PassiveHPDownRateMR;
			ChangeByConditionParam PassiveMovingTBPlus;
			unsigned short PhysicalImmuneRate;
			unsigned short MagicalImmuneRate;
			unsigned int RangeOver;
			unsigned short DMGMinusRate;
		};
#pragma pack(pop)
	}

	namespace AttackRhythm
	{
#pragma pack(push, 4)
		struct CharArgument
		{
			AttackRhythmBase* ca_attrhythm;
			char ca_group;
			char ca_point;
		};
#pragma pack(pop)

		struct AttackRhythmBase_vtbl
		{
			void(__thiscall* arb_Next)(AttackRhythmBase* self, CharArgument*, int);
			int(__thiscall* arb_ActionNumber)(AttackRhythmBase* self, CharArgument*);
			unsigned int(__thiscall* arb_NextBash)(AttackRhythmBase* self, CharArgument*, int);
		};

		struct AttackRhythmBase
		{
			AttackRhythmBase_vtbl* vft;
		};
	}

	namespace SkillDataBox
	{
		struct SkillDataIndex
		{
			struct AreaSkillInfo
			{
				char AreaStep;
				char BMPIndex[32];
				Enums::ImagePinType EffectTarget;
				char bIsDirection;
				int AreaCenter_X;
				int AreaCenter_Y;
				int AreaSize;
				int AreaSize_X;
				int AreaSize_Y;
				char** AreaBMP;
			};

			struct unnamed_type_sdi_Abstate
			{
				Enums::ABSTATEINDEX abstateidx;
				int strength;
				int sucrate;
			};

			ActiveSkillInfoServer* sdi_ServInf;
			ActiveSkillInfo* sdi_Activ;

			Custom::vector<ActiveSkillGroup*, Custom::allocator<ActiveSkillGroup*> > sdi_ActiveSkillGroups;
			Custom::vector<ToggleSkill*, Custom::allocator<ToggleSkill*> > sdi_ToggleData;
			Custom::vector<AreaSkillInfo, Custom::allocator<AreaSkillInfo> > sdi_Area;

			SkillDataIndex* sdi_PrevSkill;
			SkillDataIndex* sdi_NextSkill;
			unnamed_type_sdi_Abstate sdi_Abstate[4];

			RulesOfEngagement* sdi_DamageRule;
			unsigned int sdi_AttackDist;
			EnumStruct sdi_HEALAMOUNT;
			EnumStruct sdi_CURE;
			EnumStruct sdi_DISPEL;
			EnumStruct sdi_TELEPORT;
			EnumStruct sdi_WHOLEHEALAMOUNT;
			EnumStruct sdi_MANABURN;
			EnumStruct sdi_UNDEADTODMG;
			EnumStruct sdi_DISPELALL;
			EnumStruct sdi_DISPELONE;
			EnumStruct sdi_DISPELRANDOM;
			EnumStruct sdi_WHOLEAGGRORATE;
			EnumStruct sdi_WHOLEAGGRORANGE;
			EnumStruct sdi_WARPING;
			EnumStruct sdi_DETECT;
			EnumStruct sdi_CROSSCOUNTER;
			EnumStruct sdi_THHPUP;
			EnumStruct sdi_DIEHPUP;
			EnumStruct sdi_REVIVAL;
			EnumStruct sdi_MAGICFIELD_TICK;
			EnumStruct sdi_MAGICFIELD_KEEP;
			EnumStruct sdi_STEALENCHANT;
			EnumStruct sdi_HPCONVERTSP;
			EnumStruct sdi_HPUPRATE;
			EnumStruct sdi_FLYDURINGCAST;
			EnumStruct sdi_SILVERWING;
			EnumStruct sdi_DISPELDEBUFF;
			EnumStruct sdi_DISPELCURSE;
			EnumStruct sdi_DISPELPOISON;
			EnumStruct sdi_DISPELDISEASE;
			EnumStruct sdi_DISPELDEEPER;
			EnumStruct sdi_WARPING_TARGET;
			EnumStruct sdi_JWALK;
			EnumStruct sdi_SHOOTME;
			EnumStruct sdi_FIRETIMEADD;
			EnumStruct sdi_CURSETIMEADD;
			EnumStruct sdi_HOLDME;
			EnumStruct sdi_POSIONTIMEADD;
			EnumStruct sdi_DMGCOLLTIMEDOWN;
			EnumStruct sdi_AREATYPE;
			EnumStruct sdi_BOMBDISPELALL;
			EnumStruct sdi_MAGICFIELD_PARTY;
			EnumStruct sdi_HEALFRIENDRATE;
			EnumStruct sdi_SETABSTATEFRIEND;
			EnumStruct sdi_RANDOMTARGETNUMBER;
			EnumStruct sdi_NEXTTARGETAREA;
			EnumStruct sdi_DMGDOWNRATE;
			EnumStruct sdi_MAXDMGDOWNRATE;
			EnumStruct sdi_SHOTSPEED;
			EnumStruct sdi_TARGETHPDOWNDMGUPRATE;
			EnumStruct sdi_JUMP;
			EnumStruct sdi_SETABSTATEME;
			EnumStruct sdi_NOTTARGET;
			EnumStruct sdi_ABKEEPTIME;
			EnumStruct sdi_RANDOMTARGET;
			EnumStruct sdi_TOPAGGRONO;
			EnumStruct sdi_MAGICFIELD_DELAY_START_TIME;
			EnumStruct sdi_BMP_MAGICFIELD_ROTATIONSPEED_RIGHT;
			EnumStruct sdi_DISPELABSTATE;
			EnumStruct sdi_RECALL;
			EnumStruct sdi_DMGSHARE;
			EnumStruct sdi_SUCKHP;
			EnumStruct sdi_RANDOMTARGETSPOT;
		};
	}

#pragma pack(push, 2)
	struct ProduceInfo
	{
		unsigned short ProductID;
		char ProduceIndex[32];
		char Name[64];
		char Product[32];
		unsigned int Lot;
		char Raw0[32];
		unsigned int Quantity0;
		char Raw1[32];
		unsigned int Quantity1;
		char Raw2[32];
		unsigned int Quantity2;
		char Raw3[32];
		unsigned int Quantity3;
		char Raw4[32];
		unsigned int Quantity4;
		char Raw5[32];
		unsigned int Quantity5;
		char Raw6[32];
		unsigned int Quantity6;
		char Raw7[32];
		unsigned int Quantity7;
		Enums::TotalMasteryType MasteryType;
		unsigned int MasteryGain;
		Enums::TotalMasteryType NeededMasteryType;
		unsigned int NeededMasteryGain;
	};
#pragma pack(pop)

	struct CDataReader_vtbl
	{
		void(__thiscall* CDataReader_Destructor)(CDataReader* self);
	};

	struct CDataReader
	{
		enum TYPE_LIST
		{
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

		enum DATA_MODE
		{
			DATA_MODE_NORMAL = 0x0,
			DATA_MODE_ENCRYPTION = 0x1,
		};

		struct FIELD
		{
			char Name[48];
			TYPE_LIST Type;
			unsigned int Size;
		};

		struct HEAD
		{
			unsigned int nVersionKey;
			char sVersion[20];
			unsigned int nReserved;
			DATA_MODE nDataMode;
			unsigned int nFileSize;
			unsigned int nDataSize;
			unsigned int nNumOfRecord;
			unsigned int nFieldSize;
			unsigned int nNumOfField;
			FIELD Field[];
		};

		CDataReader_vtbl* vft;
		unsigned int m_nFileSize;
		unsigned int m_nBFSize;
		unsigned int m_nDataArraySize;
		unsigned int m_nFileCheckSum;
		Name8 m_sFileMD5;
		HEAD* m_pHead;
		char* m_pData;
		char** m_pDataArray;
	};

	struct BinaryData : CDataReader
	{
	};

#pragma pack(push, 4)
	template<typename S>
	struct BinaryDataBox : BinaryData
	{
		S bdb_defaultblock;
	};
#pragma pack(pop)

	namespace GatherProduce
	{
		struct RecipeBook
		{
			struct ProductIndex
			{
				struct unnamed_type_raw
				{
					unsigned short item;
					int quantity;
				};

				ProduceInfo* index;
				unsigned short product;
				int productlot;
				unnamed_type_raw raw[8];
			};

			BinaryDataBox<ProduceInfo> rb_BinData;
			ProductIndex* rb_Array;
			int rb_Number;
		};
	}

#pragma pack(push, 2)
	struct PrimaryParameter
	{
		struct PointSoulStone
		{
			unsigned int soul;
			unsigned int maxsoul;
			unsigned int buysoul;
		};

		unsigned int level;
		unsigned int strength;
		unsigned int constitution;
		unsigned int intelligence;
		unsigned int wizdom;
		unsigned int dexterity;
		unsigned int mentalpower;
		PointSoulStone hpsoulstone;
		PointSoulStone spsoulstone;
		unsigned int aap;
		unsigned int dap;
		unsigned int maxaep;
		unsigned int soulaep;
		unsigned int buysoulaep;
		unsigned int aepwc;
		unsigned int aepma;
		unsigned int maxdep;
		unsigned int souldep;
		unsigned int buysouldep;
		unsigned int depac;
		unsigned int depmr;
		unsigned int painresistance;
		unsigned int restraintresistance;
		unsigned int curseresistance;
		unsigned int shockresistance;
		unsigned short LevelHP;
		unsigned short LevelSP;
		unsigned int CharTitlePt;
		unsigned int SkillPwrPt;
		unsigned short JobChangeDmgUp;
	};
#pragma pack(pop)

	struct CharClass_vtbl
	{
		int(__thiscall* WC)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* AC)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MA)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MR)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* TH)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* TB)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MH)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MB)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MaxHP)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MaxSP)(CharClass* self, ShineObjectClass::ShineObject*, Parameter::Cluster*);
		int(__thiscall* MaxLP)(CharClass* self);
		int(__thiscall* LPRecover)(CharClass* self);
		int(__thiscall* LPTick)(CharClass* self);
		void(__thiscall* LPRecoveryRoutine)(CharClass* self, ShineObjectClass::ShineObject*);
		int(__thiscall* cc_ClassType)(CharClass* self);
		AttackRhythm::AttackRhythmBase* (__thiscall* cc_AttackRhythm)(CharClass* self);
		void(__thiscall* cc_JustAfterSkill)(CharClass* self, ShineObjectClass::ShineMobileObject*);
		int(__thiscall* cc_PromoteClass)(CharClass* self);
		int(__thiscall* cc_BaseClass)(CharClass* self);
		int(__thiscall* cc_NormalHitDelay_AfterSkill)(CharClass* self);
		char(__thiscall* cc_CanNormalAttack)(CharClass* self, ShineObjectClass::ShineObject*);
		bool(__thiscall* cc_IsDescendantsOf)(CharClass* self, int);
	};

	namespace ItemDataBox
	{
		struct ItemDataBoxIndex
		{
			ItemInfo* data;
			ItemInfoServer* dataserv;
			GradeItemOption* itemoption;
			char MovingShot;
			unsigned short AttackAngle;
			unsigned short SetItemIndex;
			unsigned short HitTimeArray[3];
			ItemDropLog* itemdroplog;
			char ItemSortOrder;
			Enums::DelConditionType eDelConditionType;
			ItemMoney* pBuyItemData;
		};
	}

	struct TargetAnalyser_vtbl
	{
		char(__thiscall* ta_me)(TargetAnalyser* self, ShineObjectClass::ShineObject*);
		char(__thiscall* ta_enemy)(TargetAnalyser* self, ShineObjectClass::ShineObject*);
		char(__thiscall* ta_friend)(TargetAnalyser* self, ShineObjectClass::ShineObject*);
	};

	struct TargetAnalyser
	{
		TargetAnalyser_vtbl* vft /*VFT*/;
		ShineObjectClass::ShineMobileObject* ta_body;
	};

#pragma pack(push, 4)
	struct CharClass : OptionReader
	{
		CharClass_vtbl* vft;
		PrimaryParameter* cc_array[151];
		PrimaryParameter cc_def;
	};
#pragma pack(pop)

	namespace ShineObjectClass
	{
		struct ShineMobileObject : ShineObject
		{
			struct unnamed_type_smo_MovePacketBuffer
			{
				unsigned short movecommand;
				PROTO_NC_ACT_SOMEONEMOVEWALK_CMD movepacket;
			};

			struct TA
			{
				TargetAnalyser* analyser;
			};

#pragma pack(push, 4)
			struct AS
			{
				AbnormalStateContainer::AbstateListInObject abstatelist;
				char parameterchange;
			};
#pragma pack(pop)

			struct unnamed_type_smo_Mode
			{
				char tempmode;
				char* mode;
			};

			struct unnamed_type_smo_Recover
			{
				unsigned int lasthp;
				unsigned int lastsp;
				unsigned int maxhp;
				unsigned int maxsp;
			};

			struct unnamed_type_smo_BattleObject
			{
				char alreadydead;
				int damagereserve;
			};

#pragma pack(push, 2)
			struct SkillCastStruct
			{
				struct unnamed_type_scs_BattleSkill
				{
					ShineObject* target;
					SHINE_XY_TYPE locate;
				};

				struct unnamed_type_scs_ProduceSkill
				{
					SkillDataBox::SkillDataIndex* sklidx;
					GatherProduce::RecipeBook::ProductIndex* prdidx;
				};

#pragma pack(push, 4)
				struct unnamed_type_scs_UseItem
				{
					int cooltime_millisec;
					ItemDataBox::ItemDataBoxIndex* itemdata;
					char invenslot;
					char bAutoUse;
				};
#pragma pack(pop)

				unsigned int scs_BlastTime;
				unsigned short scs_Skill;
				unnamed_type_scs_BattleSkill scs_BattleSkill;
				unnamed_type_scs_ProduceSkill scs_ProduceSkill;
				unnamed_type_scs_UseItem scs_UseItem;
				SKILL_EMPOWER scs_Empower;
				char scs_AttackCode;
			};
#pragma pack(pop)

			struct unnamed_type_smo_SceneMoveManager
			{
				struct unnamed_type_buffer
				{
					int x;
					int y;
					MoveManager::MMState stt;
				};

				unnamed_type_buffer buffer[16];
				int point;
			};

			struct unnamed_type_smo_Flag
			{
				char Retrate : 1;
				char DuringFlying : 1;
				char InFear : 1;
				char DeadProcessComplete : 1;
				char InSkillShift : 1;
				char InCaptivate : 1;
				char ChineCast : 1;
				char DamageAbsorb : 1;
			};

			struct MoveStateStruct
			{
				Enums::MOVE_STATE eMoveState;
				SHINE_XY_TYPE PrevLocation;
				unsigned int nStartTime;
				unsigned int nCheckTime;
			};

			unnamed_type_smo_MovePacketBuffer smo_MovePacketBuffer;
			DeadCheck smo_DeadCheck;
			unsigned short smo_WhoKillMe;
			unsigned short smo_WhoClickMe;
			TA smo_TargetAnalyser;
			MoveManager smo_MoveManager;
			AS smo_Abstate;
			unnamed_type_smo_Mode smo_Mode;
			unnamed_type_smo_Recover smo_Recover;
			SpyNet::EspionageAgent smo_Spy;
			DuringBattle smo_duringbattle;
			CharClass* characterClass;
			Parameter::Container parameters;
			AttackRhythm::CharArgument smo_AttackRhythm;
			unsigned short smo_HPChangeOrder;
			unnamed_type_smo_BattleObject smo_BattleObject;
			SkillCastStruct smo_SkillCast;
			unnamed_type_smo_SceneMoveManager smo_SceneMoveManager;
			RulesOfEngagement* smo_RulesOfNormalAttack;
			unnamed_type_smo_Flag smo_Flag;
			int smo_admindamage;
			char smo_NormalAttackSequence[2];
			AbnormalStateDictionary::AbState::AbStateStr::AbStateStrArgument* smo_NaturalEnemy;
			unsigned short smo_NormalSwingIndex;
			unsigned short smo_SkillIndexLastCasting;
			MoveStateStruct smo_moveState;
			char smo_bStaticWalkSpeed;
			unsigned short smo_nStaticWalkSpeed;
			char smo_bStaticRunSpeed;
			unsigned short smo_nStaticRunSpeed;
		};
	}

	struct ItemLotInspector
	{
#pragma pack(push, 4)
		struct InspectNote
		{
			struct unnamed_type_ili_From
			{
				char Activ;
#pragma pack(push, 1)
				ITEM_INVEN Locate;
#pragma pack(pop)
				SHINE_ITEM_STRUCT Item;
			};

			struct unnamed_type_ili_To
			{
				char Activ;
#pragma pack(push, 1)
				ITEM_INVEN Locate;
#pragma pack(pop)
				int Lot;
			};

			int ili_Action;
			unsigned short ili_ItemID;
			unnamed_type_ili_From ili_From[2];
			unnamed_type_ili_To ili_To[2];
			int ili_MoveLot;
			int ili_TotalLot;
			char ili_StorageCount;
		};
#pragma pack(pop)

		int ili_Action;
		InspectNote ili_Array[64];
		BitANDInt ili_ArrayPointer;
	};

	union $8DC038A5D109ACB3FAF3310B3008CC7C
	{
		ShineDateTime SubWhen;
		ShineDateTime ApplicationLimit;
		ShineDateTime DelayLimit;
		ShineDateTime DivorceLimit;
		ShineDateTime NewlyLimit;
	};

#pragma pack(push, 2)
	struct NETPACKETZONEHEADER
	{
		unsigned short clienthandle;
		unsigned int charregistnumber;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_CHAR_WEDDINGDATA_ACK
	{
		struct unnamed_type_Partner
		{
			Name5 Name;
			unsigned int RegisterNumber;
		};

		struct unnamed_type_Status
		{
			char Main : 4;
			char Sub : 4;
		};

		NETPACKETZONEHEADER header;
		unsigned short Error;
		unnamed_type_Status Status;
		ShineDateTime When;
		$8DC038A5D109ACB3FAF3310B3008CC7C ___u4;
		unnamed_type_Partner Partner;
		char WeddingCount;
		char RefusalCount;
	};
#pragma pack(pop)

	struct DiceTaiSaiAllBetting
	{
		unsigned int nBetMoney[52];
		unsigned int nBetSumMoney;
	};

	struct GI_DiceTaiSai
	{
		char bGameLeaveReserve;
		char bRoomLeaveReserve;
		DiceTaiSaiAllBetting BetInfo;
		unsigned long long nTotalDividend;
	};

	struct CallBackEvent
	{
		enum EventType
		{
			ET_NONE = 0x0,
			ET_ROLLBACKPOS = 0x1,
		};

		CallBackEvent_vtbl* vft;
	};

	struct CallBackEvent_vtbl
	{
		void(__thiscall* CallBackEvent_Destructor)(CallBackEvent* self);
		void(__thiscall* doEventRun)(CallBackEvent* self, ShineObjectClass::ShineObject*);
		CallBackEvent::EventType(__thiscall* GetType)(CallBackEvent* self);
	};

	struct ClientSession : ZoneBaseSession
	{
		enum SessionMode
		{
			CLIENT_SESSION_MODE_INACTIVE_MODE = 0xFFFFFFFF,
			CLIENT_SESSION_MODE_BEFORE_MAP_LOGIN_REQ = 0x0,
			CLIENT_SESSION_MODE_BEFORE_MAP_LOGINCOMPLETE_CMD = 0x1,
			CLIENT_SESSION_MODE_AFTER_MAP_LOGINCOMPLETE_CMD = 0x2,
		};

		unsigned short cs_sessionhandle;
		unsigned short cs_clienthandle;
		SessionMode cs_sessionMode;
		unsigned int cs_activeTime;
		int cs_bClosingSession;
	};

	struct TargetAnalyser_Player : TargetAnalyser
	{
	};

	struct ProtocolPacket
	{
		char* pp_Buffer;
		int pp_BufferSize;
		int pp_PacketLength;
	};

	struct PacketContainerBase_vtbl
	{
		void(__thiscall* pcb_SetSocketSession)(PacketContainerBase* self, ClientSession*);
		void(__thiscall* pcb_Clear)(PacketContainerBase* self);
		char(__thiscall* pcb_Flush)(PacketContainerBase* self, ClientSession*);
		void(__thiscall* pcb_Append)(PacketContainerBase* self, ShineObjectClass::ShineObject*, ProtocolPacket*);
	};

	struct PacketContainerBase
	{
		PacketContainerBase_vtbl* vft;
	};

	struct PacketContainer : PacketContainerBase
	{
		ClientSession* pc_Session;
		char pc_Buffer[8192];
		int pc_Pointer;
	};

	struct PROTO_AVATAR_SHAPE_INFO
	{
		char race : 2;
		char chrclass : 5;
		char gender : 1;
		char hairtype : 8;
		char haircolor : 8;
		char faceshape : 8;
	};

#pragma pack(push, 1)
	struct PROTO_EQUIPMENT
	{
		struct unnamed_type_upgrade
		{
			char lefthand : 4;
			char righthand : 4;
			char body : 4;
			char leg : 4;
			char shoes : 4;
		};

		unsigned short Equ_Head;
		unsigned short Equ_Mouth;
		unsigned short Equ_RightHand;
		unsigned short Equ_Body;
		unsigned short Equ_LeftHand;
		unsigned short Equ_Pant;
		unsigned short Equ_Boot;
		unsigned short Equ_AccBoot;
		unsigned short Equ_AccPant;
		unsigned short Equ_AccBody;
		unsigned short Equ_AccHeadA;
		unsigned short Equ_MiniMon_R;
		unsigned short Equ_Eye;
		unsigned short Equ_AccLeftHand;
		unsigned short Equ_AccRightHand;
		unsigned short Equ_AccBack;
		unsigned short Equ_CosEff;
		unsigned short Equ_AccHip;
		unsigned short Equ_Minimon;
		unsigned short Equ_AccShield;
		unnamed_type_upgrade upgrade;
	};
#pragma pack(pop)

	struct CHARBRIEFINFO_CAMP
	{
		unsigned short minihouse;
		char dummy[10];
	};

	struct STREETBOOTH_SIGNBOARD
	{
		char signboard[30];
	};

#pragma pack(push, 1)
	struct CHARBRIEFINFO_BOOTH
	{
		CHARBRIEFINFO_CAMP camp;
		char issell;
		STREETBOOTH_SIGNBOARD signboard;
	};
#pragma pack(pop)

	struct CHARBRIEFINFO_NOTCAMP
	{
		PROTO_EQUIPMENT equip;
	};

#pragma pack(push, 1)
	struct CHARBRIEFINFO_RIDE
	{
		struct RideInfo
		{
			unsigned short horse;
		};

		PROTO_EQUIPMENT equip;
		RideInfo rideinfo;
	};

	struct SHINE_COORD_TYPE
	{
		SHINE_XY_TYPE xy;
		char dir;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct STOPEMOTICON_DESCRIPT
	{
		char emoticonid;
		unsigned short emoticonframe;
	};
#pragma pack(pop)

	struct CHARTITLE_BRIEFINFO
	{
		char Type;
		char ElementNo;
		unsigned short MobID;
	};

	struct ABNORMAL_STATE_BIT
	{
		char statebit[99];
	};

	struct ABNORMAL_STATE_BIT_2
	{
		char statebit[103];
	};

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD
	{
		union unnamed_type_shapedata
		{
			CHARBRIEFINFO_NOTCAMP notcamp;
			CHARBRIEFINFO_CAMP camp;
			CHARBRIEFINFO_BOOTH booth;
			CHARBRIEFINFO_RIDE ride;
		};
		unsigned short handle;
		Name5 charid;
		SHINE_COORD_TYPE coord;
		char mode;
		char chrclass;
		PROTO_AVATAR_SHAPE_INFO shape;
		unnamed_type_shapedata shapedata;
		unsigned short polymorph;
		STOPEMOTICON_DESCRIPT emoticon;
		CHARTITLE_BRIEFINFO chartitle;
		ABNORMAL_STATE_BIT abstatebit;
		unsigned int myguild;
		char type;
		char isGuildAcademyMember;
		char IsAutoPick;
		char Level;
		char sAnimation[32];
		unsigned short nMoverHnd;
		char nMoverSlot;
		char nKQTeamType;
		char IsUseItemMinimon;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct BriefInformationCharacter
	{
		ProtocolPacket bic_pack;
		char bic_array[238];
		NetworkCommand* bic_nc;
		PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD* bic_BriefInfo;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD_2
	{
		union unnamed_type_shapedata
		{
			CHARBRIEFINFO_NOTCAMP notcamp;
			CHARBRIEFINFO_CAMP camp;
			CHARBRIEFINFO_BOOTH booth;
			CHARBRIEFINFO_RIDE ride;
		};
		unsigned short handle;
		Name5 charid;
		SHINE_COORD_TYPE coord;
		char mode;
		char chrclass;
		PROTO_AVATAR_SHAPE_INFO shape;
		unnamed_type_shapedata shapedata;
		unsigned short polymorph;
		STOPEMOTICON_DESCRIPT emoticon;
		CHARTITLE_BRIEFINFO chartitle;
		ABNORMAL_STATE_BIT_2 abstatebit;
		unsigned int myguild;
		char type;
		char isGuildAcademyMember;
		char IsAutoPick;
		char Level;
		char sAnimation[32];
		unsigned short nMoverHnd;
		char nMoverSlot;
		char nKQTeamType;
		char IsUseItemMinimon;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_CHARACTER_CMD
	{
		NetworkCommand netcmd;
		char charnum;
		PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD chars[28];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_CHARACTER_CMD_2
	{
		NetworkCommand netcmd;
		char charnum;
		PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD_2 chars[28];
	};
#pragma pack(pop)


#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD_Old_1
	{
		union unnamed_type_shapedata
		{
			CHARBRIEFINFO_NOTCAMP notcamp;
			CHARBRIEFINFO_CAMP camp;
			CHARBRIEFINFO_BOOTH booth;
			CHARBRIEFINFO_RIDE ride;
		};
		NetworkCommand netcmd;
		unsigned short handle;
		Name5 charid;
		SHINE_COORD_TYPE coord;
		char mode;
		char chrclass;
		PROTO_AVATAR_SHAPE_INFO shape;
		unnamed_type_shapedata shapedata;
		unsigned short polymorph;
		STOPEMOTICON_DESCRIPT emoticon;
		CHARTITLE_BRIEFINFO chartitle;
		ABNORMAL_STATE_BIT abstatebit;
		unsigned int myguild;
		char type;
		char isGuildAcademyMember;
		char IsAutoPick;
		char Level;
		char sAnimation[32];
		unsigned short nMoverHnd;
		char nMoverSlot;
		char nKQTeamType;
		char IsUseItemMinimon;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD_Old_2
	{
		union unnamed_type_shapedata
		{
			CHARBRIEFINFO_NOTCAMP notcamp;
			CHARBRIEFINFO_CAMP camp;
			CHARBRIEFINFO_BOOTH booth;
			CHARBRIEFINFO_RIDE ride;
		};
		NetworkCommand netcmd;
		unsigned short handle;
		Name5 charid;
		SHINE_COORD_TYPE coord;
		char mode;
		char chrclass;
		PROTO_AVATAR_SHAPE_INFO shape;
		unnamed_type_shapedata shapedata;
		unsigned short polymorph;
		STOPEMOTICON_DESCRIPT emoticon;
		CHARTITLE_BRIEFINFO chartitle;
		ABNORMAL_STATE_BIT_2 abstatebit;
		unsigned int myguild;
		char type;
		char isGuildAcademyMember;
		char IsAutoPick;
		char Level;
		char sAnimation[32];
		unsigned short nMoverHnd;
		char nMoverSlot;
		char nKQTeamType;
		char IsUseItemMinimon;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOVER_CMD
	{
		NetworkCommand netcmd;
		unsigned short nHandle;
		unsigned int nID;
		unsigned int nHP;
		SHINE_COORD_TYPE nCoord;
		ABNORMAL_STATE_BIT AbstateBit;
		char nGrade;
		unsigned short nSlotHandle[10];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOVER_CMD_2
	{
		NetworkCommand netcmd;
		unsigned short nHandle;
		unsigned int nID;
		unsigned int nHP;
		SHINE_COORD_TYPE nCoord;
		ABNORMAL_STATE_BIT_2 AbstateBit;
		char nGrade;
		unsigned short nSlotHandle[10];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOVER_CMD_Old
	{
		unsigned short nHandle;
		unsigned int nID;
		unsigned int nHP;
		SHINE_COORD_TYPE nCoord;
		ABNORMAL_STATE_BIT AbstateBit;
		char nGrade;
		unsigned short nSlotHandle[10];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOVER_CMD_Old_2
	{
		unsigned short nHandle;
		unsigned int nID;
		unsigned int nHP;
		SHINE_COORD_TYPE nCoord;
		ABNORMAL_STATE_BIT_2 AbstateBit;
		char nGrade;
		unsigned short nSlotHandle[10];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_MOVER_CMD
	{
		NetworkCommand netcmd;
		char nMoverNum;
		struct PROTO_NC_BRIEFINFO_REGENMOVER_CMD_Old
			Movers[];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_MOVER_CMD_2
	{
		NetworkCommand netcmd;
		char nMoverNum;
		PROTO_NC_BRIEFINFO_REGENMOVER_CMD_Old_2 Movers[];
	};
#pragma pack(pop)

	struct CeaseFireSender
	{
		char cfs_Flag;
	};

	struct PacketEncrypt
	{
		unsigned short pe_point;
		unsigned short pe_mark;
	};

	struct SkillCastFinish
	{
		unsigned short scf_ErrorType;
	};

	struct CHARSTATDISTSTR
	{
		char Strength;
		char Constitute;
		char Dexterity;
		char Intelligence;
		char MentalPower;
		char RedistributePoint;
	};

#pragma pack(push, 1)
	struct PROTO_NC_CHAR_BASE_CMD
	{
		union unnamed_type_flags
		{
			struct unnamed_type_str
			{
				unsigned int skillempower_can_reset : 1;
				unsigned int restunion : 31;
			};

			unsigned int bin;
			unnamed_type_str str;
		};

		struct LoginLocation
		{
			MapNameStruct currentmap;
			SHINE_COORD_TYPE currentcoord;
		};

		unsigned int chrregnum;
		Name5 charid;
		char slotno;
		char Level;
		unsigned long long Experience;
		unsigned short CurPwrStone;
		unsigned short CurGrdStone;
		unsigned short CurHPStone;
		unsigned short CurSPStone;
		unsigned int CurHP;
		unsigned int CurSP;
		unsigned int CurLP;
		unsigned int fame;
		unsigned long long Cen;
		LoginLocation logininfo;
		CHARSTATDISTSTR statdistribute;
		char pkyellowtime;
		unsigned int pkcount;
		unsigned short prisonmin;
		char adminlevel;
		unnamed_type_flags flags;
	};
#pragma pack(pop)

	struct CHARDATA_TO_CLIENT
	{
		PROTO_NC_CHAR_BASE_CMD basedata;
		PROTO_AVATAR_SHAPE_INFO shape;
	};

#pragma pack(push, 1)
	struct ZoneCharData
	{
		unsigned int usrregnum;
		CHARDATA_TO_CLIENT toclient;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_GAMEDATA_CMD
	{
		struct ZoneServer
		{
			char bIsGM;
		};

		struct Client
		{
			unsigned short partyno;
			unsigned short nRaidNo;
		};

		ZoneServer zone;
		Client client;
	};
#pragma pack(pop)

	struct TargetObject
	{
		char to_Type;
		unsigned short to_Handle;
		unsigned int to_RegNum;
		ShineObjectClass::ShineObject* to_Object;
		ShineObjectClass::ShinePlayer* to_MainBody;
		unsigned int to_LastHp;
		unsigned int to_LastSp;
	};

	struct NPCRoleBase
	{
		NPCRoleBase_vtbl* vft /*VFT*/;
		ORToken nrb_argument;
	};

	struct NPCManager
	{
		struct NPCInformTemplete
		{
			char mobname[33];
			char map[20];
#pragma pack(push, 1)
			unsigned int coordx;
			unsigned int coordy;
			short direct_degree;
#pragma pack(pop)
			char npcmenu;
			ORToken role;
			ORToken rolearg;
		};

#pragma pack(push, 1)
		struct LinkInformTemplete
		{
			char index[20];
			char linktoserver[33];
			char linktoclient[33];
			unsigned int coordx;
			unsigned int coordy;
			unsigned short direct;
			char Party;
		};
#pragma pack(pop)
#pragma pack(push, 4)
		struct NPCIndexArray
		{
			NPCInformTemplete* pnt;
			NPCRoleBase* func;
			unsigned short handle;
		};
#pragma pack(pop)

		NPCIndexArray nm_BufferArray[1024];
		int nm_BufferPoint;
		OptionReader nm_NPCInfo;
	};

#pragma pack(push, 2)
	struct ItemUseEffect
	{
		char ItemIndex[32];
		Enums::UseEffectType UseEffectA;
		unsigned short UseValueA;
		Enums::UseEffectType UseEffectB;
		unsigned short UseValueB;
		Enums::UseEffectType UseEffectC;
		unsigned short UseValueC;
		char UseAbstateName[32];
		unsigned int UseAbstateIndex;
	};
#pragma pack(pop)

	struct NPCRoleBase_vtbl
	{
		void(__thiscall* nrb_Role)(NPCRoleBase* self, ShineObjectClass::ShinePlayer*, NPCManager::NPCIndexArray*, unsigned short);
		void(__thiscall* nrb_EndOfTrade)(NPCRoleBase* self, ShineObjectClass::ShinePlayer*);
		NPCManager::LinkInformTemplete* (__thiscall* nrb_linkinform)(NPCRoleBase* self, int);
		unsigned int(__thiscall* nrb_ItemSellPrice)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short);
		unsigned int(__thiscall* nrb_ItemBuyPrice)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short);
		unsigned int(__thiscall* nrb_ItemBuyFame)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short);
		unsigned int(__thiscall* nrb_ItemBuyGBCoin)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short);
		unsigned int(__thiscall* nrb_ItemBuyGuildToken)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short);
		void(__thiscall* nrb_ItemBuyItemMoney)(NPCRoleBase* self, ShineObjectClass::ShineObject*, unsigned short, unsigned short*, unsigned int*);
		NPCManager::LinkInformTemplete* (__thiscall* nrb_SaveLinkData)(NPCRoleBase* self, int);
		int(__thiscall* nrb_GetSaveLinkSize)(NPCRoleBase* self);
		void(__thiscall* nrb_BriefInformSet)(NPCRoleBase* self, ShineObjectClass::ShineObject*, const ORToken*);
		void(__thiscall* nrb_LinkBrench)(NPCRoleBase* self, ShineObjectClass::ShinePlayer*, int, NPCManager::LinkInformTemplete*, unsigned short, unsigned short);
		char(__thiscall* nrb_LinkBrenchCheck)(NPCRoleBase* self, NPCManager::LinkInformTemplete*);
		char(__thiscall* nrb_CanItemRepurchase)(NPCRoleBase* self);
	};

	namespace UseEffect
	{
#pragma pack(push, 4)
		struct UIE_Functions
		{
			ItemUseEffect* useeffectstruct;
			UseItemBase* useitemclass;
			SkillDataBox::SkillDataIndex* useskill;
			char broadcast;
		};
#pragma pack(pop)

		struct UseItemBase_vtbl
		{
			void(__thiscall* UseItemBase_Destructor)(UseItemBase* self);
			unsigned short(__thiscall* uib_CanUseItem)(UseItemBase* self, ShineObjectClass::ShinePlayer*, ItemTotalInformation*);
			char(__thiscall* uib_DirectUse)(UseItemBase* self, ShineObjectClass::ShinePlayer*, int, ItemTotalInformation*);
			void(__thiscall* uib_AfterCast)(UseItemBase* self, ShineObjectClass::ShinePlayer*, ItemBag*, ItemDataBox::ItemDataBoxIndex*, char);
			void(__thiscall* uib_Effect)(UseItemBase* self, ShineObjectClass::ShineObject*, ItemTotalInformation*, UIE_Functions*);
		};

		struct UseItemBase
		{
			UseItemBase_vtbl* vft;
		};
	}

	struct ItemBoxIterator_vtbl
	{
		char(__thiscall* ibi_isvalid)(ItemBoxIterator* self);
	};

	struct ItemBoxIterator
	{
		ItemBoxIterator_vtbl* vft;
		ItemBag* ibi_itembag;
		int ibi_finger;
		int ibi_Limit;
	};

#pragma pack(push, 2)
	struct PROTO_NC_COLLECT_CARDREGIST_ACK
	{
		char invenslot;
		unsigned short CardID;
		char Star;
		unsigned int Serial;
		unsigned short err;
	};

	struct CollectCardTitle
	{
		Enums::CHARACTER_TITLE_TYPE Type;
		char CC_ItemInx[32];
	};

	struct PROTO_NC_COLLECT_REGIST_REQ
	{
		unsigned int clientregnum;
		unsigned short clientzonehandle;
		unsigned short lockindex;
		SHINE_ITEM_REGISTNUMBER CardKey;
		PROTO_NC_COLLECT_CARDREGIST_ACK CardInfo;
	};
#pragma pack(pop)

	namespace InventoryLocking
	{
		struct InventoryCellLock_vtbl
		{
			char(__thiscall* icl_IsLocked1)(InventoryCellLock* self, ITEM_INVEN*, unsigned short);
			char(__thiscall* icl_IsLocked2)(InventoryCellLock* self, int, int, unsigned short);
			char(__thiscall* icl_IsLocked3)(InventoryCellLock* self, ITEM_INVEN*);
			char(__thiscall* icl_IsLocked4)(InventoryCellLock* self, int, int);
			char(__thiscall* icl_IsAnyLock)(InventoryCellLock* self);
			void(__thiscall* icl_LockInventory)(InventoryCellLock* self, char);
			char(__thiscall* icl_IsAnyLocked)(InventoryCellLock* self);
			char(__thiscall* icl_Apply_N_Free)(InventoryCellLock* self, ShineObjectClass::ShineObject*, unsigned short, char);
			char(__thiscall* icl_Apply_N_Free_ItemUseAck)(InventoryCellLock* self, ShineObjectClass::ShineObject*, unsigned short, char);
			void(__thiscall* icl_Free1)(InventoryCellLock* self, int, int);
			void(__thiscall* icl_Free2)(InventoryCellLock* self, unsigned short);
			void(__thiscall* icl_OnlyLock)(InventoryCellLock* self, unsigned short, int, int);
			void(__thiscall* icl_ClearItem)(InventoryCellLock* self, unsigned short, ItemInventoryCell*, ITEM_INVEN*, ITEM_INVEN*);
			void(__thiscall* icl_ClearItemSimple)(InventoryCellLock* self, ItemBoxIterator*);
			void(__thiscall* icl_CardRegist)(InventoryCellLock* self, unsigned short, ItemInventoryCell*, ITEM_INVEN*, ITEM_INVEN*, PROTO_NC_COLLECT_REGIST_REQ*, CollectCardTitle*);
			void(__thiscall* icl_CardOpen)(InventoryCellLock* self, unsigned short, ItemInventoryCell*, ItemTotalInformation*, int);
			void(__thiscall* icl_StoreItem)(InventoryCellLock* self, unsigned short, ItemInventoryCell*, ItemTotalInformation*, ITEM_INVEN*, ITEM_INVEN*);
			void(__thiscall* icl_StoreSmallItem)(InventoryCellLock* self, unsigned short, ITEM_INVEN*, ItemTotalInformation*, ITEM_INVEN*, ITEM_INVEN*);
			void(__thiscall* icl_StoreMoney)(InventoryCellLock* self, unsigned short, unsigned long long, int);
			void(__thiscall* icl_StoreFame)(InventoryCellLock* self, unsigned short, unsigned int, int);
			void(__thiscall* icl_EquipLocation)(InventoryCellLock* self, unsigned short, int, ItemInventoryCell*, int, ItemInventoryCell*);
			void(__thiscall* icl_UnEquipInfo)(InventoryCellLock* self, unsigned short, int, ItemInventoryCell*);
			void(__thiscall* icl_UseItem)(InventoryCellLock* self, unsigned short, ItemTotalInformation*, ITEM_INVEN*, UseEffect::UseItemBase*);
			void(__thiscall* icl_StorePointStone)(InventoryCellLock* self, unsigned short, int, int);
			void(__thiscall* icl_QuestReward)(InventoryCellLock* self, unsigned short, int, int, char, char);
			ReservedQuantity* (__thiscall* icl_ReservedQuantity)(InventoryCellLock* self, ReservedQuantity*);
			void(__thiscall* icl_StoreFurniture)(InventoryCellLock* self, unsigned short, ItemInventoryCell*, ItemTotalInformation*, ITEM_INVEN*, ITEM_INVEN*);
			void(__thiscall* icl_LinktoItem)(InventoryCellLock* self, unsigned short, NPCManager::LinkInformTemplete*);
			void(__thiscall* icl_StoreGBCoin)(InventoryCellLock* self, unsigned short, unsigned long long, int, char);
			void(__thiscall* icl_ItemSell)(InventoryCellLock* self, unsigned short, SHINE_ITEM_REGISTNUMBER, ItemTotalInformation*);
			void(__thiscall* icl_ItemRepurchase)(InventoryCellLock* self, unsigned short, unsigned short);
			void(__thiscall* icl_ItemInfoZoneRng)(InventoryCellLock* self, unsigned short, SHINE_INVEN_SLOT_INFO, SHINE_INVEN_SLOT_INFO, ItemTotalInformation);
		};

#pragma pack(push, 4)
		struct InventoryCellLock
		{
			InventoryCellLock_vtbl* vtable /*VFT*/;
			unsigned short icl_Index;
		};
#pragma pack(pop)

		struct InvenCellReleaser_vtbl
		{
			void(__thiscall* icr_Apply)(InvenCellReleaser* self, ShineObjectClass::ShineObject*, LockedCell*, char);
			void(__thiscall* icr_Reserv)(InvenCellReleaser* self, ReservedQuantity*, LockedCell*);
			char(__thiscall* icr_IsOnlyLock)(InvenCellReleaser* self);
			void(__thiscall* lc_Free)(InvenCellReleaser* self, ShineObjectClass::ShineObject*);
		};

		struct ReservedQuantity
		{
			int cen;
			int fame;
			int hpstone;
			int spstone;
			int guild_token;
			int gbcoin;
		};

		struct LockedCell
		{
#pragma pack(push, 2)
			union __declspec(align(2)) unnamed_type_lc_Argument
			{
#pragma pack(push, 8)
				struct unnamed_type_cenchange
				{
					unsigned long long cen;
					short plusminus;
				};
#pragma pack(pop)
#pragma pack(push, 4)
				struct unnamed_type_famechange
				{
					unsigned int fame;
					short plusminus;
				};
#pragma pack(pop)

				struct unnamed_type_cellclear
				{
					ItemInventoryCell* cell;
				};

#pragma pack(push, 2)
				struct unnamed_type_cellchange
				{
					ItemInventoryCell* cell;
					ItemTotalInformation iti;
				};
#pragma pack(pop)

#pragma pack(push, 1)
				struct unnamed_type_cellchangesmall
				{
					ITEM_INVEN cell;
					ItemTotalInformation iti;
				};
#pragma pack(pop)

				struct unnamed_type_equipchange
				{
					int equipslot;
					ItemInventoryCell* equipcell;
					int otherslot;
					ItemInventoryCell* othercell;
				};

				struct unnamed_type_itemuse
				{
					ItemTotalInformation iti;
					UseEffect::UseItemBase* useitemclass;
				};

				struct unnamed_type_pointstone
				{
					int flag;
					int num;
				};

#pragma pack(push, 4)
				struct unnamed_type_questreward
				{
					int exp;
					int fame;
					char ct_type;
					char ct_elementno;
				};
#pragma pack(pop)

				struct unnamed_type_linkinfo
				{
					NPCManager::LinkInformTemplete Link;
				};

#pragma pack(push, 1)
				struct unnamed_type_zonerng
				{
					SHINE_INVEN_SLOT_INFO zr_from;
					SHINE_INVEN_SLOT_INFO zr_to;
					ItemTotalInformation zr_changeiteminfo;
				};
#pragma pack(pop)
#pragma pack(push, 8)
				struct unnamed_type_coinchange
				{
					unsigned long long coin;
					short plusminus;
					char exchange;
				};
#pragma pack(pop)
#pragma pack(push, 4)
				struct unnamed_type_CardOpen
				{
					ItemTotalInformation Card;
					ItemInventoryCell* Cell;
					ITEM_INVEN InvenLoc;
				};
#pragma pack(pop)

				struct unnamed_type_CardRegist
				{
					ItemInventoryCell* Cell;
					unsigned short CardID;
					unsigned int Serial;
					int StarNum;
					int Slot;
					Enums::CHARACTER_TITLE_TYPE CharTitle;
				};

#pragma pack(push, 1)
				struct unnamed_type_ItemSell
				{
					SHINE_ITEM_REGISTNUMBER nSellItemKey;
					ItemTotalInformation ItemTotalInfo;
				};
#pragma pack(pop)

				struct unnamed_type_ItemRepurchase
				{
					unsigned short nHandle;
				};

				unnamed_type_cenchange cenchange;
				unnamed_type_famechange famechange;
				unnamed_type_cellclear cellclear;
				unnamed_type_cellchange cellchange;
				unnamed_type_cellchangesmall cellchangesmall;
				unnamed_type_equipchange equipchange;
				unnamed_type_itemuse itemuse;
				unnamed_type_pointstone pointstone;
				unnamed_type_questreward questreward;
				unnamed_type_linkinfo linkinfo;
				unnamed_type_zonerng zonerng;
				unnamed_type_coinchange coinchange;
				unnamed_type_CardOpen CardOpen;
				unnamed_type_CardRegist CardRegist;
				unnamed_type_ItemSell ItemSell;
				unnamed_type_ItemRepurchase ItemRepurchase;
			};
#pragma pack(pop)

			struct InvenCellReleaser
			{
				InvenCellReleaser_vtbl* vft;
			};

			unsigned short lc_Index;
			InventoryLocking::InvenCellReleaser* lc_Releaser;
			ITEM_INVEN lc_InvenLocCurrent;
			ITEM_INVEN lc_InvenLocExchange;
			__declspec(align(8)) unnamed_type_lc_Argument lc_Argument;
		};

#pragma pack(push, 8)
		struct InventoryCellLockList : InventoryCellLock
		{
			ShineObjectClass::ShinePlayer* icll_sp;
			List<LockedCell> icll_List;
			unsigned char __align2[4];
			LockedCell icll_Array[192];
			char icll_AllLock;
		};
#pragma pack(pop)
	}

	namespace NormalAttackDamageDelay
	{
		struct NormalAttackDamageElement
		{
			unsigned int nade_Tick;
			ShineObjectClass::ShineObject* nade_Target;
			char nade_AttackSequance;
			unsigned int nade_MissileFlyMilliSec;
		};

		struct NormalAttackDamageTick
		{
			Custom::deque<NormalAttackDamageElement,
				Custom::allocator<NormalAttackDamageElement>> nadt_DamageTime;
		};
	}

#pragma pack(push, 1)
	struct STRUCT_QSC
	{
#pragma pack(push, 2)
		struct tagSTRUCT_QSC_ERROR
		{
			Enums::QUEST_SCRIPT_COMMAND ErrCmd;
			const char* pErrStr;
			unsigned short ErrCode;
		};
#pragma pack(pop)

		struct tagSTRUCT_QSC_END
		{
		};

#pragma pack(push, 2)
		struct tagSTRUCT_QSC_SAY
		{
			unsigned int nID;
			Enums::QUEST_SCRIPT_TALKER TalkerType;
			unsigned short NPCNo;
		};
#pragma pack(pop)

		struct tagSTRUCT_QSC_SCENARIO
		{
			unsigned short nScenarioID;
		};

		struct tagSTRUCT_QSC_CALLPS
		{
			char FileName[64];
			char StartBlockName[32];
		};

		struct tagSTRUCT_QSC_CLEAR
		{
			unsigned short nID;
		};

		struct tagSTRUCT_QSC_ACCEPT
		{
			unsigned short nID;
		};

		struct tagSTRUCT_QSC_CANCEL
		{
			unsigned short nID;
		};

#pragma pack(push, 1)
		struct tagSTRUCT_QSC_PROGRESS
		{
			unsigned short nID;
			char ProgressStep;
		};
#pragma pack(pop)

		struct tagSTRUCT_QSC_FAILED
		{
			unsigned short nID;
		};

		struct tagSTRUCT_QSC_DONE
		{
			unsigned short nID;
		};

		struct tagSTRUCT_QSC_LINK
		{
			unsigned short nID;
		};

		struct tagSTRUCT_QSC_ABORT
		{
			unsigned short nID;
		};

#pragma pack(push, 2)
		struct tagSTRUCT_QSC_DELETE_ITEM
		{
			unsigned short nItemID;
			unsigned int nLot;
		};
#pragma pack(pop)

#pragma pack(push, 2)
		struct tagSTRUCT_QSC_CREATE_ITEM
		{
			unsigned short nItemID;
			unsigned int nLot;
		};
#pragma pack(pop)

#pragma pack(push, 2)
		struct tagSTRUCT_QSC_DROP_ITEM
		{
			unsigned short nItemID;
			unsigned int nLot;
		};
#pragma pack(pop)

		struct tagSTRUCT_QSC_GET_ITEM_LOT
		{
			unsigned short nItemID;
		};

#pragma pack(push, 1)
		struct tagSTRUCT_QSC_SET_ABSTATE
		{
			const char* pAbStateName;
			char nStrength;
			unsigned int nKeepTime;
		};
#pragma pack(pop)

		struct tagSTRUCT_QSC_RESET_ABSTATE
		{
			const char* pAbStateName;
		};

		struct tagSTRUCT_QSC_IS_ABSTATE
		{
			const char* pAbStateName;
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_REMARK
		{
		};

		struct tagSTRUCT_QSC_IF
		{
			Enums::QUEST_SCRIPT_VARIABLE VarID1;
			unsigned int Value1;
			Enums::QUEST_SCRIPT_ARITHMETIC_EXPRESSION ExpressionID;
			Enums::QUEST_SCRIPT_VARIABLE VarID2;
			unsigned int Value2;
		};

		struct tagSTRUCT_QSC_GOTO
		{
			const char* pMarkName;
		};

		struct tagSTRUCT_QSC_MARK
		{
			const char* pMarkName;
			const char* pMarkPoint;
		};

		struct tagSTRUCT_QSC_SET
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
			Enums::QUEST_SCRIPT_VARIABLE SourceVarID;
			unsigned int SourceValue;
		};

		struct tagSTRUCT_QSC_ADD
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
			Enums::QUEST_SCRIPT_VARIABLE SourceVarID;
			unsigned int SourceValue;
		};

		struct tagSTRUCT_QSC_SUB
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
			Enums::QUEST_SCRIPT_VARIABLE SourceVarID;
			unsigned int SourceValue;
		};

		struct tagSTRUCT_QSC_GET_PLAYER_RACE
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_GET_PLAYER_CLASS
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_GET_PLAYER_LEVEL
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_GET_PLAYER_GENDER
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_GET_PLAYER_EMPTY_INVENTORY
		{
			Enums::QUEST_SCRIPT_VARIABLE TargetVarID;
			unsigned int TargetValue;
		};

		struct tagSTRUCT_QSC_REPEAT_QUEST_GIVE_UP
		{
			unsigned short nID;
		};

		union unnamed_type_Data
		{
			tagSTRUCT_QSC_ERROR STRUCT_QSC_ERROR;
			tagSTRUCT_QSC_END STRUCT_QSC_END;
			tagSTRUCT_QSC_SAY STRUCT_QSC_SAY;
			tagSTRUCT_QSC_SCENARIO STRUCT_QSC_SCENARIO;
			tagSTRUCT_QSC_CALLPS STRUCT_QSC_CALLPS;
			tagSTRUCT_QSC_CLEAR STRUCT_QSC_CLEAR;
			tagSTRUCT_QSC_ACCEPT STRUCT_QSC_ACCEPT;
			tagSTRUCT_QSC_CANCEL STRUCT_QSC_CANCEL;
			tagSTRUCT_QSC_PROGRESS STRUCT_QSC_PROGRESS;
			tagSTRUCT_QSC_FAILED STRUCT_QSC_FAILED;
			tagSTRUCT_QSC_DONE STRUCT_QSC_DONE;
			tagSTRUCT_QSC_LINK STRUCT_QSC_LINK;
			tagSTRUCT_QSC_ABORT STRUCT_QSC_ABORT;
			tagSTRUCT_QSC_DELETE_ITEM STRUCT_QSC_DELETE_ITEM;
			tagSTRUCT_QSC_CREATE_ITEM STRUCT_QSC_CREATE_ITEM;
			tagSTRUCT_QSC_DROP_ITEM STRUCT_QSC_DROP_ITEM;
			tagSTRUCT_QSC_GET_ITEM_LOT STRUCT_QSC_GET_ITEM_LOT;
			tagSTRUCT_QSC_SET_ABSTATE STRUCT_QSC_SET_ABSTATE;
			tagSTRUCT_QSC_RESET_ABSTATE STRUCT_QSC_RESET_ABSTATE;
			tagSTRUCT_QSC_IS_ABSTATE STRUCT_QSC_IS_ABSTATE;
			tagSTRUCT_QSC_REMARK STRUCT_QSC_REMARK;
			tagSTRUCT_QSC_IF STRUCT_QSC_IF;
			tagSTRUCT_QSC_GOTO STRUCT_QSC_GOTO;
			tagSTRUCT_QSC_MARK STRUCT_QSC_MARK;
			tagSTRUCT_QSC_SET STRUCT_QSC_SET;
			tagSTRUCT_QSC_ADD STRUCT_QSC_ADD;
			tagSTRUCT_QSC_SUB STRUCT_QSC_SUB;
			tagSTRUCT_QSC_GET_PLAYER_RACE STRUCT_QSC_GET_PLAYER_RACE;
			tagSTRUCT_QSC_GET_PLAYER_CLASS STRUCT_QSC_GET_PLAYER_CLASS;
			tagSTRUCT_QSC_GET_PLAYER_LEVEL STRUCT_QSC_GET_PLAYER_LEVEL;
			tagSTRUCT_QSC_GET_PLAYER_GENDER STRUCT_QSC_GET_PLAYER_GENDER;
			tagSTRUCT_QSC_GET_PLAYER_EMPTY_INVENTORY STRUCT_QSC_GET_PLAYER_EMPTY_INVENTORY;
			tagSTRUCT_QSC_REPEAT_QUEST_GIVE_UP STRUCT_QSC_REPEAT_QUEST_GIVE_UP;
		};

		Enums::QUEST_SCRIPT_COMMAND Cmd;
		char IsPigeonStartType;
		unnamed_type_Data Data;
	};
#pragma pack(pop)

	struct CQuestParserScript_vtbl
	{
		int(__thiscall* CommandRun)(CQuestParserScript* self, STRUCT_QSC*);
	};

	struct CGdp
	{
		enum GDP_TYPE
		{
			GDP_TYPE_MAIN = 0x1A504447,
			GDP_TYPE_LINK = 0x1,
			GDP_TYPE_FILE = 0x2,
			GDP_TYPE_DELETED = 0x3,
			GDP_TYPE_EMPTY = 0x4,
			GDP_TYPE_END = 0x5,
		};

		enum GDP_IO_TYPE
		{
			GDP_IO_WIN32 = 0x0,
			GDP_IO_ANSI = 0x1,
		};

		enum GDP_STORE_TYPE
		{
			GDP_STORE_COPY = 0x0,
			GDP_STORE_DIB = 0x1,
			GDP_STORE_ZIP = 0x2,
		};

		struct GDP_CHUNK
		{
			union unnamed_union
			{
				struct unnamed_type_TYPE_MAIN
				{
					char Comment[260];
					unsigned int NumChunk;
					unsigned int NumNextChunkComes;
				};

				struct unnamed_type_TYPE_LINK
				{
					char Comment[260];
					unsigned int FDirPos;
					unsigned int FDirPosHigh;
					unsigned int NumNextChunkComes;
				};

				struct unnamed_type_TYPE_DIR
				{
					char Name[260];
					GDP_STORE_TYPE StoreType;
					unsigned int FPos;
					int FPosHigh;
					unsigned int SrcSize;
					int SrcSizeHigh;
					unsigned int DatSize;
					int DatSizeHigh;
					_FILETIME ftLastWriteTime;
					unsigned int CHK32;
					unsigned int res0;
					unsigned int res1;
				};

				unnamed_type_TYPE_MAIN TYPE_MAIN;
				unnamed_type_TYPE_LINK TYPE_LINK;
				unnamed_type_TYPE_DIR TYPE_DIR;
			};

			GDP_TYPE Type;
			unsigned int Encrypt;
			unnamed_union ___u2;
		};

		struct GDP_CHUNK_LIST
		{
			unsigned int ChunkFPos;
			int ChunkFPosHigh;
			GDP_CHUNK Chunk;
		};

		int m_bIsGDPOpen;
		GDP_IO_TYPE m_GdpIO;
		void* m_hGDPFile;
		_iobuf* m_fpGDPFile;
		int m_bIsGDPOpenByHandle;
		int m_bIsGDPOpenByFilePointer;
		char m_GDPFileName[260];
		unsigned int m_dwGDPFPos;
		int m_dwGDPFPosHigh;
		unsigned int m_dwNumChunk;
		GDP_CHUNK_LIST* m_pChunkList;
		unsigned int m_dwDefaultNumEmptyMakes;
		int m_bWriteEncryptedHeader;
		int m_bWriteEncryptedData;
		unsigned int m_EncryptKey;
		int m_bIsOpen;
		GDP_STORE_TYPE m_StoreType;
		int m_bNew;
		int m_bWritten;
		void* m_hFile;
		_iobuf* m_fpFile;
		unsigned int m_dwFileNo;
		GDP_CHUNK_LIST* m_pFileChunk;
	};

	struct CToken
	{
		CGdp m_Gdp;
		int m_bIsOpen;
		void* m_hFile;
		unsigned int m_dwFileSize;
		char* m_pFileBF;
		char* m_pSaveTokenPos;
		int m_bOpenByMemory;
		char* m_pOpenMemory;
		char m_szSeprator[256];
		char* m_pResetStart;
		int m_bResetStart;
		int m_bIsStart;
		char* m_pToken;
		char* m_pMyTokenStart;
		char** m_lplpTokenList;
		unsigned int m_dwNumTokens;
	};

	struct PROTO_NC_QUEST_RESET_TIME_CMD
	{
		int tResetYearQuest;
		int tResetMonthQuest;
		int tResetWeekQuest;
		int tResetDayQuest;
	};

	struct QUEST_DATA_HEAD
	{
		unsigned short VersionNo;
		unsigned short NumOfQuest;
	};

	struct QUEST_DATA
	{
		struct QUEST_START_CONDITION
		{
			char bIsWaitListView;
			char bIsWaitListProgress;
			char bLevel;
			char LevelMin;
			char LevelMax;
			char bNPC;
			unsigned short NPCID;
			char bItem;
			unsigned short ItemID;
			unsigned short ItemLot;
			char bLocation;
			unsigned short Location;
			unsigned int LocationX;
			unsigned int LocationY;
			unsigned int LocationRange;
			char bQuest;
			unsigned short QuestID;
			char bRace;
			char Race;
			char bClass;
			char Class;
			char bGender;
			char Gender;
			char bDate;
			char DateMode;
			long long DateStart;
			long long DateEnd;
		};

		struct QUEST_END_CONDITION
		{
#pragma pack(push, 2)
			struct _NPCMobList
			{
				char bNPCMob;
				unsigned short NPCMobID;
				char NPCMobAction;
				char NPCMobCount;
				char TargetGroup;
			};
#pragma pack(pop)

			struct _ItemList
			{
				char bItem;
				unsigned short ItemID;
				unsigned short ItemLot;
			};

			char bIsWaitListProgress;
			char bLevel;
			char Level;
			_NPCMobList NPCMobList[5];
			_ItemList ItemList[5];
			char bLocation;
			unsigned short Location;
			unsigned int LocationX;
			unsigned int LocationY;
			unsigned int LocationRange;
			char bScenario;
			unsigned short ScenarioID;
			char bRace;
			char Race;
			char bClass;
			char Class;
			char bTimeLimit;
			unsigned short TimeLimit;
		};

#pragma pack(push, 4)
		struct QUEST_ACTION
		{
			char IfType;
			unsigned int IfTarget;
			char ThenType;
			unsigned int ThenTarget;
			unsigned int ThenPersent;
			unsigned int ThenCountMin;
			unsigned int ThenCountMax;
			char TargetGroup;
		};
#pragma pack(pop)

		struct QUEST_REWARD
		{
			union VALUE
			{
				struct Item
				{
					unsigned short ItemID;
					unsigned short ItemLot;
				};

#pragma pack(push, 2)
				struct Abstate
				{
					unsigned int AbstateKeepTime;
					unsigned short AbstateID;
					char AbstateStrength;
				};
#pragma pack(pop)

				struct CharacterTitle
				{
					char Type;
					char ElementNo;
				};

				unsigned int Exp;
				unsigned int Money;
				Item Item;
				Abstate Abstate;
				unsigned int Fame;
				unsigned int PetID;
				char MiniHouseID;
				CharacterTitle CharacterTitle;
				unsigned int KillPoint;
			};

			char Use;
			char Type;
			VALUE Value;
		};

		unsigned int nQuestDataSize;
		unsigned short ID;
		unsigned int NameID;
		unsigned int BrifingID;
		char Region;
		char Type;
		char Repeatable;
		char nDailyQuestType;
		QUEST_START_CONDITION Start;
		QUEST_END_CONDITION End;
		char NumOfAction;
		QUEST_ACTION Action[10];
		QUEST_REWARD Reward[12];
		unsigned short SizeOfScriptStart;
		unsigned short SizeOfScriptEnd;
		unsigned short SizeOfScriptDoing;
		char* pScriptStart;
		char* pScriptDoing;
		char* pScriptEnd;
		char DialogData[];
	};

	struct CQuestData
	{
		enum QUEST_DATA_READ_ERROR_VALUE
		{
			QDREV_NO_ERROR = 0x0,
			QDREV_FILE_NOT_FOUND = 0x1,
			QDREV_FILE_IS_NOT_QUEST_DATA = 0x2,
			QDREV_MISS_MATCH_VERSION = 0x3,
			QDREV_DATA_READ_FAILED = 0x4,
		};

		CDataReader* m_pQuestDialog;
		const char* m_pNULLSTR;
		int m_bReadonly;
		char* m_pBF;
		QUEST_DATA_HEAD* m_pDataHead;
		QUEST_DATA** m_ppQuestDataArray;
		QUEST_DATA_READ_ERROR_VALUE m_ReadError;
		CustomExtension::hash_map<unsigned short, QUEST_DATA*, CustomExtension::hash_compare<unsigned short, Custom::less<unsigned short> >, Custom::allocator<Custom::pair<unsigned short const, QUEST_DATA*>>> m_hashmap_QuestData;
		CustomExtension::hash_multimap<unsigned short, QUEST_DATA*, CustomExtension::hash_compare<unsigned short, Custom::less<unsigned short> >, Custom::allocator<Custom::pair<unsigned short const, QUEST_DATA*>>> m_mhmap_QuestDataByMobID;
	};

	struct CQuest_vtbl
	{
		void(__thiscall* _Send_NC_QUEST_CLIENT_SCENARIO_DONE_REQ)(CQuest* self, unsigned short);
		int(__thiscall* QuestPlayer_LevelChange)(CQuest* self, char);
		int(__thiscall* QuestPlayer_NPCMobKill)(CQuest* self, unsigned short, const unsigned short);
		int(__thiscall* QuestPlayer_TakeItem)(CQuest* self, unsigned short, unsigned short);
		int(__thiscall* QuestPlayer_DestroyItem)(CQuest* self, unsigned short, unsigned short);
		int(__thiscall* QuestPlayer_CheckLocation)(CQuest* self);
		int(__thiscall* QuestPlayer_ScenarioDone)(CQuest* self, unsigned short);
		int(__thiscall* QuestPlayer_RaceChange)(CQuest* self, char);
		int(__thiscall* QuestPlayer_ClassChange)(CQuest* self, char);
		int(__thiscall* QuestPlayer_TimeProcess)(CQuest* self);
		int(__thiscall* IsQuestArea)(CQuest* self, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
		void(__thiscall* Occure_NPCMobKill)(CQuest* self, unsigned short, unsigned short, int, int);
		void(__thiscall* Occure_LevelChange)(CQuest* self, unsigned short, char, char);
		void(__thiscall* Occure_TakeItem)(CQuest* self, unsigned short, unsigned short, unsigned short, unsigned short);
		void(__thiscall* Occure_DestroyItem)(CQuest* self, unsigned short, unsigned short, unsigned short, unsigned short);
		void(__thiscall* Occure_CheckLocation)(CQuest* self, unsigned short, unsigned short);
		void(__thiscall* Occure_ScenarioDone)(CQuest* self, unsigned short, unsigned short);
		void(__thiscall* Occure_RaceChange)(CQuest* self, unsigned short, char);
		void(__thiscall* Occure_ClassChange)(CQuest* self, unsigned short, char);
		void(__thiscall* Occure_TimeProcess)(CQuest* self, unsigned short, unsigned short, unsigned short);
		void(__thiscall* Occure_NewStatusReward)(CQuest* self, PLAYER_QUEST_INFO*, QUEST_DATA*);
		void(__thiscall* Occure_NewStatusFailed)(CQuest* self, PLAYER_QUEST_INFO*, QUEST_DATA*);
		void(__thiscall* Occure_NewStatusIng)(CQuest* self, PLAYER_QUEST_INFO*, QUEST_DATA*);
		void(__thiscall* Occure_Quest_Done)(CQuest* self, PLAYER_QUEST_INFO*, QUEST_DATA*);
		void(__thiscall* GetPlayerCurrentLocation)(CQuest* self, unsigned short*, unsigned int*, unsigned int*);
		char(__thiscall* GetQuestPlayerLevel)(CQuest* self);
		unsigned short(__thiscall* GetQuestPlayerItemLot)(CQuest* self, unsigned short);
		char(__thiscall* GetQuestPlayerRace)(CQuest* self);
		char(__thiscall* GetQuestPlayerClass)(CQuest* self);
		char(__thiscall* GetQuestPlayerGender)(CQuest* self);
		char(__thiscall* GetQuestPlayerEmptyInventory)(CQuest* self);
		char(__thiscall* IsQuestPlayerItemLock)(CQuest* self, unsigned short);
		char(__thiscall* IsSoonableDailyQuest)(CQuest* self, PLAYER_QUEST_INFO*);
	};

	struct CQuest
	{
		struct NPC_QUEST_STATUS
		{
			unsigned short hID;
			QUEST_DATA* lpQuestData;
			Enums::PLAYER_QUEST_STATUS eResultState;
			int nLevel;
		};

		CQuest_vtbl* vft;
		CQuestData* m_pQuestData;
		int m_NumOfQuest;
		int m_NumOfQuestBF;
		PLAYER_QUEST_INFO* m_pQuestArray;
		int m_ProcessedTime;
		int m_MaxOfQuestListWithNPC;
		int m_NumOfQuestListWithNPC;
		NPC_QUEST_STATUS* m_pQuestListWithNPC;
		unsigned int m_QuestStatusPriority[21];
		unsigned int m_QuestTypePriority[11];
		PROTO_NC_QUEST_RESET_TIME_CMD m_QuestRestTime;
	};

	struct CQuestParserScript
	{
		struct STRUCT_SQDC_MARK
		{
			char MarkName[16];
			const char* pMarkPoint;
		};

		CQuestParserScript_vtbl* vtable /*VFT*/;
		const char** m_ppQSC;
		const char** m_ppQSV;
		const char** m_ppQSAE;
		const char** m_ppQST;
		const char** m_ppQSIL;
		unsigned int m_Var[8];
		int m_NumOfMark;
		STRUCT_SQDC_MARK m_Mark[64];
		CToken m_Token;
		STRUCT_QSC m_QSC;
		CQuest* m_pQuest;
		unsigned short m_QuestID;
		int m_NumOfError;
	};

	struct CQuestZone : CQuest
	{
		enum QUEST_PARSING_SCRIPT_TYPE
		{
			QPST_START = 0x0,
			QPST_DOING = 0x1,
			QPST_END = 0x2,
		};

		ShineObjectClass::ShinePlayer* m_pPlayer;
		CQuestParserScript m_ScriptParser;
		STRUCT_QSC* m_pQSC;
		int m_bWaitResult;
		unsigned short m_QuestClickNPC;
		unsigned short m_ParsingQuestID;
		QUEST_PARSING_SCRIPT_TYPE m_ParsingQuestScriptType;
		unsigned int m_nSelectedItem;
		unsigned short m_nClickNPCNo;
		int m_ScriptIdent;
	};

	struct ShineQuestDiary
	{
		CQuestZone sqd_QuestDiary;
	};

	struct CharaterSkillList
	{
		struct CharSkill
		{
			unsigned short cs_SkillId;
			unsigned int cs_EndOfCooltime;
			SKILL_EMPOWER cs_Empower;
			unsigned int cs_Mastery;
			int cs_bSave;
		};

#pragma pack(push, 2)
		struct CharacterToggleSkill
		{
			unsigned short cts_nSkillID;
			char cts_bSkillOn;
		};
#pragma pack(pop)

		Custom::vector<CharSkill, Custom::allocator<CharSkill> > csl_Skill;
		int csl_SkillNumber;
		Custom::vector<CharacterToggleSkill, Custom::allocator<CharacterToggleSkill> > csl_ToggleSkill;
	};

	struct BitSet
	{
		char* bs_bitlist;
		unsigned int bs_maxbit;
		unsigned int bs_maxbyte;
	};

#pragma pack(push, 1)
	struct PSkillSetAbstate
	{
		char PS_InxName[32];
		Enums::PS_ConditionEnum PS_Condition;
		unsigned short PS_ConditioRate;
		char PS_AbStateInx[32];
		char Strength;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct PassiveSkillInfo
	{
		unsigned short ID;
		char InxName[32];
		char Name[32];
		unsigned int WeaponMastery;
		char DemandSk[32];
		unsigned int MstRtTmp;
		unsigned int MstRtSword1;
		unsigned int MstRtHammer1;
		unsigned int MstRtSword2;
		unsigned int MstRtAxe2;
		unsigned int MstRtMace1;
		unsigned int MstRtBow2;
		unsigned int MstRtCrossBow2;
		unsigned int MstRtWand2;
		unsigned int MstRtStaff2;
		unsigned int MstRtClaw;
		unsigned int MstRtDSword;
		unsigned int MstPlTmp;
		unsigned int MstPlSword1;
		unsigned int MstPlHammer1;
		unsigned int MstPlSword2;
		unsigned int MstPlAxe2;
		unsigned int MstPlMace1;
		unsigned int MstPlBow2;
		unsigned int MstPlCrossBow2;
		unsigned int MstPlWand2;
		unsigned int MstPlStaff2;
		unsigned int MstPlClaw;
		unsigned int MstPlDSword;
		unsigned int SPRecover;
		unsigned int TB;
		unsigned int MaxSP;
		unsigned int MaxLP;
		unsigned int Intel;
		unsigned int CastingTime;
		unsigned short MACriRate;
		unsigned int WCRateUp;
		unsigned int MARateUp;
		unsigned short HpDownDamegeUp;
		unsigned short DownDamegeHp;
		unsigned short HpDownAcUp;
		unsigned short DownAcHp;
		unsigned short MoveTBUpPlus;
		unsigned short HealUPRate;
		unsigned short KeepTimeBuffUPRate;
		unsigned short CriDmgUpRate;
		Enums::ActiveSkillGroupIndex ActiveSkillGroupInx;
		unsigned short DMG_MinusRate;
	};
#pragma pack(pop)

	struct PassiveDataBox
	{
		struct SpecialSkill
		{
			unsigned short ss_PowerOfLove;
		};

		struct PSSetAbstateIndex
		{
			unsigned short pssabs_nID;
			PSkillSetAbstate* pssabs_pPSkillSetAbstate;
			PSSetAbstateIndex* pssabs_Prev;
			PSSetAbstateIndex* pssabs_Next;
		};

		PassiveSkillInfo* pdb_default;
		BinaryDataBox<PassiveSkillInfo> pdb_databox;
		PassiveSkillInfo** pdb_index;
		int pdb_passivenumber;
		int pdb_maxpassiveID;
		SpecialSkill sdb_SpecSkill;
		__declspec(align(4)) BinaryDataBox<PSkillSetAbstate> pdb_SetAbstateDataBox;
		int pdb_nMaxPSkillSetAbstateNum;
		PSSetAbstateIndex* pdb_pPSkillSetAbstate;
	};

	struct CharacterPassiveList
	{
		BitSet cpl_Passive;
		Custom::list<PassiveDataBox::PSSetAbstateIndex*, Custom::allocator<PassiveDataBox::PSSetAbstateIndex*> > cpl_SetAbstateList;
	};

#pragma pack(push, 1)
	struct TradeStruct
	{
#pragma pack(push, 2)
		struct unnamed_type_proposee
		{
			unsigned short chrhandle;
			unsigned int chrregnum;
		};
#pragma pack(pop)

		unnamed_type_proposee proposee;
		unnamed_type_proposee proposer;
		unsigned int proposetime;
		unsigned short lockindex;
		bool waitingTradeResFromDB;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct TradeBoard
	{
		struct unnamed_type_tb_Bit
		{
			char lock;
			char decide;
		};

		struct unnamed_type_tb_board
		{
			char invenslot;
		};

		ShineObjectClass::ShineObject* tb_opposit;
		unnamed_type_tb_Bit tb_Bit;
		unnamed_type_tb_board tb_board[12];
		unsigned long long tb_cen;
	};
#pragma pack(pop)

	struct CurrentMenu
	{
		NPCRoleBase* cm_NPC;
		SHINE_XY_TYPE cm_MenuLoc;
	};

#pragma pack(push, 2)
	struct PROTO_NC_ITEM_DROP_REQ
	{
		ITEM_INVEN slot;
		unsigned int lot;
		SHINE_XY_TYPE loc;
	};
#pragma pack(pop)

#pragma pack(push, 4)
	union ServerMenuArgument
	{
		struct ServerMenuLink
		{
			NPCManager::LinkInformTemplete sml_lnkinf;
			bool sml_isTemplink;
			unsigned short sml_LevelFrom;
			unsigned short sml_LevelTo;
		};

		struct SilverWingSet
		{
			ITEM_INVEN inven;
		};

		struct ItemBreaker
		{
			ITEM_INVEN invenslot;
			unsigned short lockindex;
		};

		struct ItemDropper
		{
			ITEM_INVEN inven;
			ItemInventoryCell* invcell;
			PROTO_NC_ITEM_DROP_REQ drop;
			unsigned short lockindex;
		};

		struct SelfRevive
		{
			unsigned short healrate;
		};

		struct DeleteInstanceDungeon
		{
			Enums::INSTANCE_DUNGEON::CATEGORY Category;
			unsigned int RegisterNumber;
		};

		struct ServerMenuLinkDungeon
		{
			unsigned int IDRegisterNumber;
			char argument[20];
			char sep;
			Enums::INSTANCE_DUNGEON::CATEGORY category;
		};

		struct ServerMenuLuaInterface
		{
			unsigned short smli_NPCHandle;
			char smli_LuaFunction[20];
		};

		ServerMenuLink sma_link;
		SilverWingSet sma_silverwing;
		ItemBreaker sma_ItemBreak;
		ItemBreaker sma_ImmediateDivorce;
		ItemDropper sma_ItemDrop;
		SelfRevive sma_SelfRevive;
		DeleteInstanceDungeon sma_DeleteInstanceDungeon;
		ServerMenuLinkDungeon sma_linkDungeon;
		ServerMenuLuaInterface sma_LuaInterface;
	};
#pragma pack(pop)

	struct ServerMenuFuncter
	{
	};

	struct DuplicatedMenuControl
	{
		unsigned short dmc_Control;
	};

	struct ServerMenuActor : SHINE_XY_TYPE
	{
		struct _Selected
		{
			ServerMenuArgument smargument;
			void(__thiscall* smfunction)(ServerMenuFuncter* self, ShineObjectClass::ShinePlayer*, ServerMenuArgument*);
		};

		_Selected sma_Selected[10];
		int sma_Subst;
		char sma_bRangeCheck;
		ShineObjectClass::ShinePlayer* sma_pPlayer;
		_Selected sma_ResetFuction;
	};

	struct ItemAccountStorage : ItemBag
	{
		ItemInventoryCell ias_Array[576];
	};

	struct ItemRewardStorage : ItemBag
	{
		ItemInventoryCell irs_Array[24];
	};

#pragma pack(push, 1)
	struct PROTO_PARTY_MEMBER
	{
		unsigned int Register;
		unsigned short ZoneHandle;
		unsigned short WorldHandle;
		Name5 CharacterName;
		char Level;
		char Flag;
		char CharacterClass;
	};
#pragma pack(pop)

	struct PROTO_PARTY_MEMBER_AND_ZONEMERCHINE
	{
		PROTO_PARTY_MEMBER Member;
		char ZoneMerchineNo;
	};

	struct CLooting
	{
		Enums::LOOTING_TYPE m_ItemLootingType[4];
		unsigned int m_Looter;
	};

	struct CParty
	{
#pragma pack(push, 4)
		struct PARTY_SLOT
		{
			struct PARTY_MEMBER_SLOT
			{
				PROTO_PARTY_MEMBER_AND_ZONEMERCHINE MemberInfo;
				ShineObjectClass::ShineObject* memberobj;
			};

			char NumberOfMember;
			PARTY_MEMBER_SLOT Members[5];
			CLooting m_Looting;
			bool IsBelongItemDiceGameIng;
			bool isRaidTypeParty;
		};
#pragma pack(pop)

		PARTY_SLOT* m_Array;
		int m_NumOfParty;
		int m_EmptyPartySearchPoint;
	};

	struct Raid_vtbl
	{
		void(__thiscall* Raid_Destructor)(Raid* self);
	};

	struct Raid
	{
		Raid_vtbl* vft;
		unsigned short m_Raidnum;
		char m_NumOfMember;
		unsigned short m_PartyNos[4];
		unsigned int m_Leader;
		unsigned int m_SubLeader[4];
		CLooting m_Looting;
	};

#pragma pack(push, 1)
	struct LastUpgradeStruct
	{
		SHINE_ITEM_REGISTNUMBER upgrade_item_regnum;
		unsigned short upgrade_item_id;
		char item_old_upgrade_level;
		char item_new_upgrade_level;
		unsigned short left_item_id;
		unsigned short right_item_id;
		unsigned short middle_item_id;
		ItemOptionStorage::Element upgrade_randomoption;
	};
#pragma pack(pop)

	struct BriefInfoBackup
	{
		CHARBRIEFINFO_NOTCAMP bib_BriefInfo;
		char bib_Backuped;
	};

	template<typename S>
	struct CIDEB_Element // <MiniHouse>
	{
		unsigned short ce_ItemID;
		S* ce_Data;
	};

#pragma pack(push, 1)
	struct MiniHouse
	{
		unsigned short Handle;
		char ItemID[32];
		char DummyType[32];
		char Backimage[32];
		unsigned short KeepTime_Hour;
		unsigned short HPTick;
		unsigned short SPTick;
		unsigned short HPRecovery;
		unsigned short SPRecovery;
		unsigned short Casting;
		char Slot;
	};
#pragma pack(pop)

	namespace SubLayer
	{
#pragma pack(push, 4)
		struct Layer
		{
			unsigned int l_Main;
			char l_Sub;
		};
#pragma pack(pop)
	}

#pragma pack(push, 2)
	struct ProtoExtraCharacterData
	{
		unsigned short pecd_worldmanagerhandle;
		SubLayer::Layer pecd_dimension;
	};
#pragma pack(pop)

	struct TreasureChestLocationManager : BitSet
	{
	};

#pragma pack(push, 1)
	struct PROTO_NC_BOOTH_ITEMTRADE_REQ
	{
		unsigned short booth;
		char slot;
		unsigned short itemnum;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BOOTH_OPEN_REQ
	{
#pragma pack(push, 4)
		struct BoothItem
		{
			char invenslot;
			char boardslot;
			unsigned long long unitcost;
			unsigned short totallot;
		};
#pragma pack(pop)

		struct unnamed_type_flag
		{
			char issell : 1;
			char itemnum : 7;
		};

		STREETBOOTH_SIGNBOARD signboard;
		unnamed_type_flag flag;
		BoothItem items[];
	};
#pragma pack(pop)

	struct StreetBooth_vtbl
	{
		char* (__thiscall* sb_Type)(StreetBooth* self);
		void(__thiscall* sb_RefreshError)(StreetBooth* self, ShineObjectClass::ShinePlayer*, unsigned short);
		void(__thiscall* sb_Open)(StreetBooth* self, InventoryLocking::InventoryCellLock*);
		void(__thiscall* sb_Close)(StreetBooth* self, InventoryLocking::InventoryCellLock*);
		void(__thiscall* sb_Clear)(StreetBooth* self);
		void(__thiscall* sb_Boarding)(StreetBooth* self, InventoryLocking::InventoryCellLock*, ItemInventoryCell*, PROTO_NC_BOOTH_OPEN_REQ::BoothItem*, ShineObjectClass::ShineObject*);
		void(__thiscall* sb_Show2Client)(StreetBooth* self, ShineObjectClass::ShineObject*, ShineObjectClass::ShinePlayer*, char);
		void(__thiscall* sb_Trade)(StreetBooth* self, ShineObjectClass::ShinePlayer*, ShineObjectClass::ShinePlayer*, PROTO_NC_BOOTH_ITEMTRADE_REQ*);
		char(__thiscall* sb_IsInInterioring)(StreetBooth* self);
	};

#pragma pack(push, 4)
	struct StreetBooth
	{
		StreetBooth_vtbl* vtable /*VFT*/;
		STREETBOOTH_SIGNBOARD sb_SignBoard;
		char sb_Terminal;
		unsigned short sb_BoothOwner;
	};
#pragma pack(pop)

#pragma pack(push, 8)
	struct StreetBoothSell : StreetBooth
	{
		struct unnamed_type_sbs_BoothCell
		{
			char invenslot;
			ItemInventoryCell* invencell;
			unsigned long long unitcost;
		};

		unnamed_type_sbs_BoothCell sbs_BoothCell[20];
		unsigned short sbs_LockIndex;
	};
#pragma pack(pop)

	struct StreetBoothBuy : StreetBooth
	{
		struct unnamed_type_sbb_BoothCell
		{
			unsigned short item;
			unsigned short quantity;
			unsigned long long unitcost;
		};

		unnamed_type_sbb_BoothCell sbb_BoothCell[20];
	};

	struct PROTO_NC_ACT_MOVESPEED_CMD
	{
		unsigned short walkspeed;
		unsigned short runspeed;
	};

	struct CT_TITLE
	{
		char Element0 : 2;
		char Element1 : 2;
		char Element2 : 2;
		char Element3 : 2;
	};

	struct CCharacterTitleData
	{
		CDataReader m_CharacterTitleData;
	};

	struct CCharacterTitle
	{
		struct CT_VIEW
		{
			char Type;
			char ElementNo;
		};

		CCharacterTitleData* m_pCharacterTitleData;
		CT_TITLE m_Titles[128];
		int m_NumOfView;
		CT_VIEW m_ViewArray[512];
		char m_CurrentTitle;
		char m_CurrentTitleElement;
		unsigned short m_CurrentTitleMobID;
		const char* m_pTitle;
	};

	struct CCharacterTitleZone : CCharacterTitle
	{
#pragma pack(push, 8)
		struct TitleValueStruct
		{
			unsigned long long TitleValue;
			int bTitleSave;
		};
#pragma pack(pop)

		ShineObjectClass::ShineObject* m_pPlayer;
		TitleValueStruct m_TitleValues[128];
		int m_MoneyGiveTimeValue;
		unsigned int m_MoneyGivenToRegNum;
		int m_MoneyBegTimeValue;
		unsigned int m_MoneyBegnFromRegNum;
		unsigned short m_KilledByMobHandle;
		int m_KilledByMobTimeValue;
		unsigned short m_PartyJoinPartyNo;
		int m_PartyJoinTimeValue;
		unsigned int m_BoothSellCharNo;
		unsigned int m_AuctionSellCharNo;
		SHINE_ITEM_REGISTNUMBER m_nUpgradeItemNo;
		char m_nUpgradeItemStatus;
		int m_ProcessedTime;
	};

#pragma pack(push, 1)
	struct GUILD_ZONE
	{
		unsigned int nNo;
		Enums::GuildName sName;
		unsigned long long nMoney;
		char nType;
		char nGrade;
		unsigned int nFame;
		unsigned short nStoneLevel;
		unsigned long long nExp;
		char nWarStatus;
		unsigned int nWarEnemy;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ChargedItemEffect
	{
		unsigned short handle;
		char index[32];
		unsigned short keep_time_hour;
		Enums::EffectEnumerate effect_key;
		unsigned short effect_value;
		char strength;
	};
#pragma pack(pop)

	namespace ChargedItemEffectList
	{
#pragma pack(push, 4)
		struct ChargedItemEffectElement
		{
			ChargedItemEffect* item;
			char ciee_Year;
			char ciee_Month;
			char ciee_Date;
			char ciee_Hour;
			char ciee_Minute;
		};
#pragma pack(pop)

		struct ChargedEffectList : List<ChargedItemEffectElement>
		{
			ChargedItemEffectElement elements[50];
		};

#pragma pack(push, 2)
		struct ChargedItem
		{
			ChargedEffectList list;
			ChargedEffectContainer ci_Effect;
			char ci_bRecalcParam;
		};
	}
#pragma pack(pop)

	struct PROTO_CHARGED_ITEM_INFO
	{
		unsigned int ItemOrderNo;
		unsigned int ItemCode;
		unsigned int ItemAmount;
		ShineDateTime ItemRegisterDate;
	};

	struct CChargedItem
	{
		PROTO_CHARGED_ITEM_INFO m_ChargedItemBF[24];
		int m_NumOfChargedItem;
	};

#pragma pack(push, 2)
	struct RIDING
	{
		unsigned short Handle;
		char ItemID[32];
		char Name[32];
		char BodyType[32];
		char Shape[32];
		unsigned short UseTime;
		char FeedType[32];
		char Texture[32];
		unsigned short FeedGauge;
		unsigned short HGauge;
		unsigned short InitHgauge;
		unsigned short Tick;
		unsigned short UGauge;
		unsigned short RunSpeed;
		unsigned short FootSpeed;
		unsigned short CastingTime;
		unsigned int CoolTime;
		char IconFileN[16];
		unsigned short IconIndex;
		char ImageN[16];
		char ImageH[16];
		char ImageE[16];
		char DummyA[32];
		char DummyB[32];
	};
#pragma pack(pop)

	struct ItemBreaker
	{
	};

	struct ItemDropper
	{
	};

	template<typename S>
	struct CommonList : List<S>
		// <HuntLog::MobHuntElement>
	{
		S* cl_Array;
	};

	namespace HuntLog
	{
		struct MobHuntElement
		{
			unsigned short mobid;
			unsigned short number;
			unsigned int expgain;
		};

		struct MobHuntLog : CommonList<MobHuntElement>
		{
		};
	}

#pragma pack(push, 4)
	struct ProtocolLogger
	{
		struct unnamed_type_pl_NetCommand
		{
			unsigned int tick;
			SHINE_XY_TYPE locate;
			NetworkCommand cmd;
		};

		unnamed_type_pl_NetCommand pl_NetCommand[16];
		char pl_Pointer;
	};
#pragma pack(pop)

	struct SoulCollectStruct
	{
		ShineObjectClass::ShineObject* scs_TargetObject;
		char scs_SoulNumber;
		unsigned int scs_SoulClearTick;
	};

	struct IObserver
	{
		enum Event
		{
			EV_IDLE = 0x0,
			EV_DIE = 0x1,
			EV_SKILL = 0x2,
			EV_ABSTATE = 0x3,
			EV_EMOTION = 0x4,
			EV_DAMAGE = 0x5,
			EV_TICK_PARTY = 0x6,
			EV_LOCATION = 0x7,
			EV_ATTACKMOB = 0x8,
		};

		IObserver_vtbl* vft;
	};

	struct IObserver_vtbl
	{
		void(__thiscall* IObserver_Destructor)(IObserver* self);
		unsigned short(__thiscall* notify)(IObserver* self, ShineObjectClass::ShineObject*, ShineObjectClass::ShineObject*, IObserver::Event, const unsigned int, const int, unsigned int, Metronome*);
		bool(__thiscall* needToAttach)(IObserver* self);
		unsigned int(__thiscall* GetConditionTick)(IObserver* self);
	};

	struct Observer : IObserver
	{
		ShineObjectClass::ShineObject* master_;
		IObserver* next_;
		unsigned int birth_;
		Metronome tick_;
	};

	struct TickTimer
	{
		unsigned int m_CurDelayTime;
		unsigned int m_DelayTime;
		bool m_bEnable;
		unsigned int m_PrevCheckTime;
	};

	struct ItemActionObserve_vtbl
	{
		void(__thiscall* ItemActionObserve_Destructor)(ItemActionObserve* self);
	};

#pragma pack(push, 2)
	struct ItemActionCondition
	{
		unsigned short ConditionID;
		Enums::ActionTargetType SubjectTarget;
		unsigned int SubjectTargetValue;
		Enums::ActionTargetType ObjectTarget;
		unsigned int ObjectTargetValue;
		Enums::ActionActivityType ConditionActivity;
		unsigned int ConditionActivityValue;
		unsigned short ActivityRate;
		unsigned short Range;
	};
#pragma pack(pop)

	struct ItemActionArgument
	{
		struct unnamed_type_effect
		{
			union unnamed_type_subtype
			{
				Enums::AttackType attackType;
				Enums::RecoverType recoverType;
				Enums::ABSTATEINDEX abStateIndexType;
				Enums::DispelAttr dispelAttrType;
				Enums::SkillEffectIncreaseType actionImpowerType;
				Enums::ActionETCType actionEtcType;
				Enums::SetItemEffectType actionEffectType;
				unsigned int spacer;
			};

			Enums::ActionActivityType type;
			unnamed_type_subtype subtype;
		};

		struct unnamed_type_condition
		{
			union unnamed_type_subtype
			{
				Enums::AttackType attackType;
				Enums::ABSTATEINDEX abStateIndexType;
				Enums::TargetAction targetActionType;
				Enums::ActionRangeType actionRangeType;
				Enums::ActiveSkillGroupIndex activeSkillGroupIndexType;
				Enums::ActionETCType actionEtcType;
				unsigned int spacer;
			};

			Enums::ActionActivityType type;
			unnamed_type_subtype subtype;
		};

		unnamed_type_condition condition;
		unnamed_type_effect effect;
		ShineObjectClass::ShineObject* me;
		ShineObjectClass::ShineObject* subject;
		ShineObjectClass::ShineObject* object;
	};

	struct IObjectTypeValidator_vtbl
	{
		void(__thiscall* IObjectTypeValidator_Destructor)(IObjectTypeValidator* self);
		bool(__thiscall* check)(IObjectTypeValidator* self, ShineObjectClass::ShineObject*, ShineObjectClass::ShineObject*);
	};

	struct IObjectTypeValidator
	{
		IObjectTypeValidator_vtbl* vft;
		unsigned int _value;
	};

	struct IActCondition
	{
		IActCondition_vtbl* vft;
		IObjectTypeValidator* _subjectValidator;
		IObjectTypeValidator* _objectValidator;
		ItemActionCondition* _conditionData;
	};

	struct IActCondition_vtbl
	{
		void(__thiscall* IActCondition_Destructor)(IActCondition* self);
		bool(__thiscall* _typeValidationCheck)(IActCondition* self, ItemActionArgument*);
		bool(__thiscall* _check)(IActCondition* self, ItemActionArgument*);
	};

	struct IActEffect_vtbl
	{
		void(__thiscall* IActEffect_Destructor)(IActEffect* self);
		void(__thiscall* takeOn)(IActEffect* self, ShineObjectClass::ShineObject*);
		void(__thiscall* takeOff)(IActEffect* self, ShineObjectClass::ShineObject*);
		void(__thiscall* equipTick)(IActEffect* self, ShineObjectClass::ShineObject*, ShineObjectClass::ShineObject*);
		unsigned int(__thiscall* fallback)(IActEffect* self, ItemActionArgument*);
		unsigned int(__thiscall* _execute)(IActEffect* self, ItemActionArgument*, ShineObjectClass::ShineObject*);
		bool(__thiscall* _typeValidationCheck)(IActEffect* self, ItemActionArgument*);
	};

#pragma pack(push, 2)
	struct ItemActionEffect
	{
		unsigned short EffectID;
		Enums::ActionTargetType EffectTarget;
		unsigned int EffectTargetValue;
		Enums::ActionActivityType EffectActivity;
		unsigned int EffectActivityValue;
		unsigned short Value;
		unsigned short Area;
	};
#pragma pack(pop)

	struct IActEffect
	{
		IActEffect_vtbl* vft;
		ItemActionEffect* _effectData;
	};

	struct Action
	{
		unsigned short _ID;
		unsigned int _coolTime;
		unsigned short _coolGroupID;
		Custom::set<IActCondition*, Custom::less<IActCondition*>, Custom::allocator<IActCondition*> > _conditions;
		Custom::set<IActEffect*, Custom::less<IActEffect*>, Custom::allocator<IActEffect*> > _effects;
	};

#pragma pack(push, 4)
	struct ItemActionObserve
	{
		ItemActionObserve_vtbl* vtable /*VFT*/;
		unsigned short iao_ListHandle;
		Action* iao_pAction;
		unsigned short iao_ActionID;
		unsigned short iao_itemid;
		bool iao_IsEnchant;
	};
#pragma pack(pop)

	struct ItemActionObserveManager
	{
		struct GroupCoolTime
		{
			TickTimer CoolTimer;
			unsigned int ActionGroupID;
			unsigned int ActionID;
			unsigned int LastCheckTime;
		};

		Custom::vector<ItemActionObserve*, Custom::allocator<ItemActionObserve*> > iaom_Observes;
		Custom::vector<GroupCoolTime, Custom::allocator<GroupCoolTime> > iaom_CoolTimeList;
		ShineObjectClass::ShineObject* iaom_pObject;
	};

	struct MobTargetStruct
	{
		unsigned short mts_Handle;
		unsigned int mts_CharRegnum;
		ShineObjectClass::ShineObject* mts_Object;
		int mts_AggroPoint;
		unsigned int mts_LastHit;
		SpyNet::IntelligenceOffice4Mob mts_EnemyAnalyzer;
	};

	struct MobTargetSelector : AxialListIterator
	{
		struct unnamed_type_mts_Current
		{
			MobTargetStruct* target;
			int distsquar;
		};

		unnamed_type_mts_Current mts_Current;
		ShineObjectClass::ShineObject* mts_MyBody;
		int mts_SightRange;
	};

	struct MobAggroManager : List<MobTargetStruct>
	{
		MobTargetStruct mam_Array[10];
	};

	struct MobTargetBout : MobTargetSelector
	{
		MobAggroManager* mtb_targetlist;
	};

	struct MobTargetAggresive : MobTargetBout
	{
		MobTargetStruct mta_InstanceTarget;
	};

	struct MobTargetNoBrain : MobTargetBout
	{
	};

	struct MobTargetAggresive2 : MobTargetAggresive
	{
	};

	struct MobTargetAggresiveALL : MobTargetAggresive
	{
	};

	struct MobTargetAggresiveNoLevel : MobTargetAggresive
	{
	};

	struct MobBrainTargetObject
	{
		ShineObjectClass::ShineObject** mbto_Target;
	};

	namespace MobTacticElement
	{
		struct MobActionBase_vtbl
		{
			MobActionBase* (__thiscall* mab_Think)(MobActionBase* self, MobActionArgument*);
			void(__thiscall* mab_Damaged)(MobActionBase* self, MobActionArgument*);
			unsigned short(__thiscall* mab_GetTargetHandle)(MobActionBase* self);
			ShineObjectClass::ShineObject* (__thiscall* mab_GetTargetObject)(MobActionBase* self);
			MobActionBase* (__thiscall* mab_TargetChange)(MobActionBase* self, MobActionArgument*);
			void(__thiscall* mb_SetTargetPoint)(MobActionBase* self, ShineObjectClass::ShineObject**);
			char(__thiscall* mab_SkillRegistAtScript)(MobActionBase* self, ShineObjectClass::ShineObject*, unsigned short, int);
			char(__thiscall* mab_IsWaiting)(MobActionBase* self);
		};

		struct MobActionBase
		{
			MobActionBase_vtbl* vft;
		};

		struct MobActionInMove : MobActionBase
		{
			MobActionBase* maim_NextReserv;
		};

		struct MobActionInMove_Cancelable : MobActionInMove
		{
		};

		struct MobActionInChase : MobActionBase
		{
			ShineObjectClass::ShineObject* maic_Target;
			MobActionBase* maic_NextAttack;
			MobActionBase* maic_NextChase;
			SHINE_XY_TYPE maic_WhereIsTargetGoing;
		};

		struct MobActionWander : MobActionBase
		{
			Metronome maw_ReturnTick;
			Metronome maw_SearchTick;
			Metronome maw_WanderTick;
		};

		struct MobActionNeededTarget : MobActionBase
		{
			MobBrainTargetObject mant_Target;
		};

		struct MobActionAttack : MobActionNeededTarget
		{
			struct unnamed_type_maa_SkillFromScript
			{
				unsigned short nextskillid;
				int nextskillorder;
				ShineObjectClass::ShineObject* target;
			};

			unsigned int mat_NextAttackTick;
			unnamed_type_maa_SkillFromScript maa_SkillFromScript;
		};

		struct MobActionChase : MobActionNeededTarget
		{
		};

#pragma pack(push, 4)
		struct MobActionBackStep : MobActionNeededTarget
		{
			char mabs_Mode;
		};
#pragma pack(pop)

		struct MobActionAvoidOverlap : MobActionNeededTarget
		{
		};

		struct MobActionWaitSkillEnd : MobActionBase
		{
			unsigned int mawse_EndTime;
			MobActionBase* mawse_NextAction;
			ShineObjectClass::ShineObject* mawse_Target;
		};

		struct MobActionSwingDamage : MobActionBase
		{
			int masd_Delay;
			ShineObjectClass::ShineObject* masd_Target;
			MobActionBase* masd_Next;
		};

		struct MobActionTurning : MobActionBase
		{
			MobActionBase* mat_NextAction;
			ShineObjectClass::ShineObject* mat_Target;
			unsigned short mat_TurnSpeed;
			unsigned int mat_LastTurn;
		};

		struct MobActionArgument
		{
			struct Actor
			{
				MobActionInMove inmove;
				MobActionInMove_Cancelable inmove_cancelable;
				MobActionInChase inmove_chase;
				MobActionWander wander;
				MobActionAttack attack;
				MobActionChase chase;
				MobActionBackStep backstep;
				MobActionAvoidOverlap avoidoverlap;
				MobActionWaitSkillEnd waitskillend;
				MobActionSwingDamage swingdamage;
				MobActionTurning turning;
				MobActionBase* action;
			};

			struct Selector
			{
				MobAggroManager targetlist;
				MobTargetBout bout;
				MobTargetAggresive aggresive;
				MobTargetNoBrain nobrain;
				MobTargetAggresive2 aggresive2;
				MobTargetAggresiveALL aggresiveall;
				MobTargetAggresiveNoLevel aggresiveNoLevel;
				MobTargetSelector* selector;
			};

			unsigned short maa_MobHandle;
			ShineObjectClass::ShineMobileObject* maa_Mob;
			Selector maa_TargetSelect;
			Actor maa_MobActionStruct;
		};
	}

	struct MobTargetPlayerCaptivate : MobTargetAggresive
	{
		MobTargetStruct PlayerTarget;
	};

#pragma pack(push, 2)
	struct PROTO_NC_CHAR_CARDCOLLECT_CMD
	{
#pragma pack(push, 1)
		struct CardInform
		{
			int RegistTime;
			unsigned int SerialNumber;
			unsigned short CardID;
			char StarNumber;
		};
#pragma pack(pop)

		unsigned int chrregnum;
		unsigned short number;
		CardInform CardList[];
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD
	{
		struct CardBookmarkInfo
		{
			unsigned short Slot;
			unsigned short CardID;
		};

		unsigned int chrregnum;
		unsigned short number;
		CardBookmarkInfo ViewList[];
	};
#pragma pack(pop)

	namespace CardCollection
	{
		struct CardCollectionAlbum : Custom::vector<PROTO_NC_CHAR_CARDCOLLECT_CMD::CardInform, Custom::allocator<PROTO_NC_CHAR_CARDCOLLECT_CMD::CardInform> >
		{
		};

		struct CardCollectionBookmark : Custom::vector<PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD::CardBookmarkInfo, Custom::allocator<PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD::CardBookmarkInfo> >
		{
		};

		struct CardCollectionReward : Custom::vector<unsigned short, Custom::allocator<unsigned short> >
		{
		};
	}

#pragma pack(push, 1)
	struct MOVER_LINKDATA
	{
		unsigned int nCharNo;
		int nItemSlot;
		unsigned int nMoverID;
		unsigned int nMoverHP;
		unsigned int nMasterCharNo;
		char nGrade;
		unsigned int nPassenger[10];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_TUTORIAL_INFO
	{
		Enums::TUTORIAL_STATE nTutorialState;
		char nTutorialStep;
	};
#pragma pack(pop)

	struct USEITEM_MINIMON_INFO
	{
		char bNormalItem;
		char bChargedItem;
		unsigned short NormalItemList[12];
		unsigned short ChargedItemList[12];
	};

#pragma pack(push, 2)
	struct SellItemInfo
	{
		unsigned short nHandle;
		SHINE_ITEM_REGISTNUMBER nSellItemKey;
		ItemTotalInformation ItemTotalInfo;
	};
#pragma pack(pop)

	struct CSellItemManager : List<SellItemInfo>
	{
		SellItemInfo simg_SellItemNode[42];
	};

	namespace ShineObjectClass
	{
#pragma pack(push, 8)
		struct ShinePlayer : ShineMobileObject
		{
			struct unnamed_type_sp_MiscFlag
			{
				char JustRevive : 1;
				char JustLink : 1;
				char DataRecieve : 1;
				char SoloingMode : 1;
				char AccountStorage_opened : 1;
				char AStorageAnywhere_opened : 1;
				char LinkReserv_link : 1;
				char InAdminImmortal : 1;
				char TryLinkUntilSuccess : 1;
				char TeleportReserv : 1;
				char BeSummoned : 1;
				char IsAutoPickUp : 1;
				char LockRefundReq : 1;
				char LockRefundCanCelReq : 1;
				char SomeClericReviveMe : 1;
				char bModeIDReqWait : 1;
				char bMoverUpgradeWait : 1;
				char bItemBuyWait : 1;
			};

#pragma pack(push, 2)
			struct MiniHouseEntrance
			{
				unsigned short MHFlag;
				unsigned short MHRegNum;
				char isCastMiniHouse;
			};
#pragma pack(pop)

			struct SHINE_MINI_GAME
			{
#pragma pack(push, 1)
				struct RoomLeave
				{
					char sMapName[13];
					SHINE_XY_TYPE LocateXY;
				};
#pragma pack(pop)

				union GAME_INFO
				{
					GI_DiceTaiSai DiceTaiSai;
				};

				Enums::SHINE_MINIGAME_TYPE nGameType;
				unsigned int nSessionCloseingTime;
				RoomLeave RoomLeavePos;
				GAME_INFO GameInfo;
			};

			struct SocketStream
			{
				PacketContainer stream;
				PacketContainerBase* gamestream;
				PacketContainerBase* datastream;
			};

			struct unnamed_type_sp_Item
			{
				CharacterInventory itembag;
				__declspec(align(8)) InventoryLocking::InventoryCellLockList invenlocklist;
			};

			struct unnamed_type_sp_LastStat
			{
				unsigned int lasthp;
				unsigned int lastsp;
				unsigned int lastmaxhp;
				unsigned int lastmaxsp;
				Parameter::Cluster last;
			};

			struct unnamed_type_sp_HPStoneManager
			{
				unsigned int StoneTick;
				unsigned int StoneReservationTick;
				void(__thiscall* PointStoneCheck)(ShinePlayer* self);
			};

			struct unnamed_type_sp_GuildStorageManager
			{
				unsigned short storagehandle;
			};

#pragma pack(push, 2)
			struct unnamed_type_sp_GuildAcademyRewardStorageManager
			{
				unsigned short storagehandle;
				char GuildAcademyRewardStoreageGrade;
			};
#pragma pack(pop)

			struct unnamed_type_sp_LogoutWait
			{
				unsigned int lastpacket;
			};

#pragma pack(push, 4)
			struct NPCProcess
			{
				unsigned short npchandle;
				unsigned short npcid;
				NPCManager::NPCIndexArray* npc;
				CurrentMenu currentmenu;
				ServerMenuActor servermenuactor;
				DuplicatedMenuControl duplicatemenustate;
			};
#pragma pack(pop)

#pragma pack(push, 8)
			struct AccountStorage
			{
				unsigned long long cen;
				ItemAccountStorage storage;
			};
#pragma pack(pop)

			struct PartyMemberInform
			{
				CParty::PARTY_SLOT* PartySlot;
				int pmi_LastHP;
				int pmi_LastSP;
				int pmi_LastLP;
				char pmi_ChrClass;
				char pmi_Level;
				unsigned int pmi_MaxHP;
				unsigned int pmi_MaxSP;
				unsigned int pmi_MaxLP;
				SHINE_XY_TYPE pmi_Coord;
			};

			struct unnamed_type_sp_attackspeed
			{
				unsigned int nextsmash;
				int attackspeed;
			};

			struct unnamed_type_sp_pickitem
			{
				unsigned short itemid;
				unsigned int itemlot;
			};

#pragma pack(push, 4)
			struct unnamed_type_sp_BashControl
			{
				int actionnumber;
				unsigned int bashrange;
				unsigned short bashinterval;
			};
#pragma pack(pop)

			struct unnamed_type_sp_SkillControl
			{
				char normalattackcontinue : 1;
				char successpacket : 1;
				char duringnormalhit : 1;
			};

#pragma pack(push, 4)
			struct MiniHouseStr
			{
				BriefInfoBackup mhs_Backup;
				CIDEB_Element<MiniHouse>* mhs_SkinHandle;
				CIDEB_Element<MiniHouse>* mhs_DummyObject[10];
				unsigned short mhs_HPTick;
				unsigned short mhs_SPTick;
				int mhs_HPInc;
				int mhs_SPInc;
				int mhs_BoothSlot;
				char mhs_Activ;
			};
#pragma pack(pop)

			struct BoothSell
			{
				unsigned int lastrefresh;
				StreetBooth* boardpnt;
				StreetBoothSell boardsell;
				StreetBoothBuy boardbuy;
			};

			struct SpeedNotice
			{
				NetworkCommand sn_NetCommand;
				PROTO_NC_ACT_MOVESPEED_CMD sn_MoveSpeed;
			};
			struct unnamed_type_sp_GatherStruct
			{
				unsigned short rawobjecthandle;
			};

			struct ChargedInven
			{
				char isopen;
				CChargedItem inven;
				unsigned int ItemOrderNo;
			};

			struct RideCasting
			{
				short castslot;
				short rideslot;
				CIDEB_Element<RIDING>* info;
				unsigned int castend;
				unsigned short lockIndex;
				short walkspd;
				short runspd;
				unsigned short horselockindex;
				unsigned int nexthungrydec;
				char hungry;
				Enums::MOVER_SYSTEM_TYPE eMoverSystemType;
			};

			struct TimeScheduler
			{
				enum TS_ReturnType
				{
					TSRT_DEFAULT = 0x0,
					TSRT_RETURN = 0x1,
				};

				enum TS_CurWork
				{
					TSCW_NONE = 0x0,
					TSCW_MISC = 0x1,
					TSCW_NORMALATTACK_SWING = 0x2,
					TSCW_NORMALATTACK_DAMAGE = 0x3,
					TSCW_LOGOUT = 0x4,
				};
				unsigned int ts_Limit;
				TS_ReturnType(__thiscall* ts_CallFunc)(ShinePlayer* self);
				TS_ReturnType ts_DefaultReturn;
				TS_CurWork ts_CurWork;
				TS_ReturnType(__thiscall* ts_TimerFunc)(TimeScheduler* self, ShinePlayer*);
			};

			struct unnamed_type_sp_PlayTimeDay
			{
				int PlayTimeDay;
			};

			struct SpamChatTimeInfo
			{
				unsigned int* pChatTime;
				int nChatTimePos;
			};

			struct SpamerInfo
			{
				unsigned int BlockTime;
				unsigned int DelayTime;
			};

			struct unnamed_type_sp_RebirthState
			{
				char bIsRebirth;
				int nHealRate;
			};

			struct LPInfo
			{
				unsigned int nCurLP;
				unsigned int nMaxLP;
				unsigned int nCurLPRecover;
				Metronome RecoverTick;
				unsigned int nLastLP;
				unsigned int nLastMaxLP;
			};

			enum PetSummonStateType
			{
				PSST_NONE = 0x0,
				PSST_CASTING = 0x1,
				PSST_CASTED = 0x2,
				PSST_WAIT_CREATING = 0x3,
				PSST_WAIT_1ST_LOADING = 0x4,
				PSST_1ST_SUMMONED = 0x5,
				PSST_RESUMMONED = 0x6,
				PSST_UNSUMMONNING = 0x7,
				PSST_LINKING_RESUMMON = 0x8,
				PSST_MAX = 0x9,
			};

			enum PetNameDecisionMode
			{
				PNDM_NONE = 0x0,
				PNDM_CHECK_NAME = 0x1,
				PNDM_MODIFY_WAIT = 0x2,
				PNDM_MODIFIABLE = 0x3,
				PNDM_FIXED = 0x4,
				PNDM_MAX = 0x5,
			};

			enum PetNameCallingState
			{
				PNCS_NONE = 0x0,
				PNCS_CALLING = 0x1,
				PNCS_MAX = 0x2,
			};

			struct PetInfoPlayer
			{
				PetSummonStateType nSummonState;
				PetNameDecisionMode nNameDecisionMode;
				PetNameCallingState nCallingState;
				unsigned int nCastEndTime;
				unsigned short nCastingLockIndex;
				unsigned short nCastSlot;
				unsigned short nSummonSlot;
				unsigned short nWalkSpeed;
				unsigned short nRunSpeed;
				unsigned int nId;
				unsigned short nHandle;
				unsigned int nRegNum;
				Enums::GuildName sName;
				unsigned int nMindMil;
				unsigned int nStressMil;
				int nMindDiffMil;
				int nStressDiffMil;
			};

#pragma pack(push, 8)
			struct PetInfoForLink
			{
				char bDoResummon;
				unsigned long long xResummonCode;
				unsigned short nSummonSlot;
				unsigned int nId;
				unsigned int nRegNum;
			};
#pragma pack(pop)

			struct UseITemMinimon_LoginSlot
			{
				char NormalSlotList[12];
				char ChargedSlotList[12];
			};

			ItemLotInspector sp_ItemLotInspector;
			unsigned int sp_ScriptCommand;
			unnamed_type_sp_MiscFlag sp_MiscFlag;
			unsigned short sp_ChangeAbilityMobInfo;
			unsigned int sp_NextSwingTick;
			unsigned int sp_LastSwingTick;
			PROTO_NC_CHAR_WEDDINGDATA_ACK sp_WeddingData;
			MiniHouseEntrance sp_MH_InnerInfo;
			SHINE_MINI_GAME sp_MiniGame;
			FURNITURE_EMOTION_INFO sp_FurnitureEmotionInfo;
			unsigned short sp_hGuildTorunamentFlagHandle;
			CallBackEvent* sp_punMarkEvent;
			char sp_bCharFreeStatLock;
			char GuildStoreageGrade;
			char nTournamentSeed;
			ClientSession* sp_SocketSession;
			TargetAnalyser_Player sp_TargetAnalyser;
			SocketStream sp_SocketContainer;
			PacketEncrypt sp_Encryption;
			BriefInformationCharacter sp_CharBriefInfo;
			CeaseFireSender sp_CeaseFireSender;

#pragma pack(push, 1)
			SkillCastFinish sp_SkillFinish;
#pragma pack(pop)

			ZoneCharData sp_CharData;
			unsigned long long sp_NextSaveExp;
			PROTO_GAMEDATA_CMD sp_GameData;
			TargetObject sp_Target;
			unnamed_type_sp_Item sp_Item;
			__declspec(align(8)) unnamed_type_sp_LastStat sp_LastStat;
			unnamed_type_sp_HPStoneManager sp_HPStoneManager;
			unnamed_type_sp_HPStoneManager sp_SPStoneManager;
			char sp_DuringItemEquip;
			NormalAttackDamageDelay::NormalAttackDamageTick sp_NormalAttackDamageTick;
			ShineQuestDiary sp_QuestDiary;
			unnamed_type_sp_GuildStorageManager sp_GuildStorageManager;
			unnamed_type_sp_GuildAcademyRewardStorageManager sp_GuildAcademyRewardStorageManager;
			char sp_bOpenGuildRewardStorageWindow[3];
			CharaterSkillList sp_SkillList;
			CharacterPassiveList sp_Passive;
			unnamed_type_sp_LogoutWait sp_LogoutWait;
			TradeStruct sp_tradestr;
			__declspec(align(1)) TradeBoard sp_tradeboard;
			NPCProcess sp_NPCProcess;
			AccountStorage sp_AccountStorage;
			ItemRewardStorage sp_RewardStorage;
			PartyMemberInform PartyMemberInform;
			Raid* sp_RaidSlot;
			unnamed_type_sp_attackspeed sp_attackspeed;
			unnamed_type_sp_pickitem sp_pickitem;
			unnamed_type_sp_BashControl sp_BashControl;
			unnamed_type_sp_SkillControl sp_SkillControl;
			LastUpgradeStruct sp_LastUpgrade;
			unsigned short sp_Linkreserv;
			SHINE_XY_TYPE sp_TeleportReserv;
			MiniHouseStr sp_MiniHouse;
			void(__thiscall* sp_AdminFunction)(ShinePlayer* self);
			ProtoExtraCharacterData sp_extra;
			__declspec(align(1)) TreasureChestLocationManager sp_ChestItemBox;
			unsigned int sp_LastItemPickup;
			unsigned int sp_LastItemPickupByRaid;
			BoothSell sp_Booth;
			SpeedNotice sp_SpeedNotice;
			void(__thiscall* sp_RecoverPoint)(ShinePlayer* self);
			unsigned int sp_LastEffect;
			unsigned short sp_MoverRecoveryTick;
			unsigned short sp_MoverRecovery;
			void(__thiscall* sp_MoverUpgradeEffect)(ShinePlayer* self);

			CCharacterTitleZone sp_CharacterTitle;
			unnamed_type_sp_GatherStruct sp_GatherStruct;
			Metronome sp_AutoSave;
			Metronome sp_EquipTick;
			unsigned int m_nMyGuildNo;
			GUILD_ZONE* m_pMyGuild;
			char m_isGuildAcademyMaster;
			unsigned int m_nMyGuildAcademyNo;
			GUILD_ZONE* m_pMyGuildAcademy;
			ChargedItemEffectList::ChargedItem premium_items;
			ChargedInven sp_ChargedInven;
			char sp_LastBoothSlotSend;
			RideCasting sp_RideCast;
			ItemBreaker sp_ItemBreaker;
			ItemDropper sp_ItemDropper;
			TimeScheduler sp_TimerStr;

			unsigned int sp_NormalLogoutTick;
			unsigned short sp_RoarFlag;
			unsigned short sp_GuildReNameFlag;
			unsigned short sp_GuildReTypeFlag;
			unsigned short sp_SkillEraseFlag;
			unsigned short sp_SparrowFly;

			HuntLog::MobHuntLog sp_MobHuntLog;
			unsigned short sp_MissileFlyMilliSec;
			unsigned short sp_LastUsedItem;
			unnamed_type_sp_PlayTimeDay sp_PlayTimeDay;
			ItemInventoryCell* sp_WeaponCell;
			char sp_LoginIP[4];
			char sp_ConnectFrom;
			unsigned int sp_ShoutTime;
			char sp_MovingShot;
			unsigned short sp_SetEffectForJustSkill;
			SetItemData::PlayerSetEffect sp_SetItemEffect;
			char sp_PreventAttack;
			ItemTotalInformation* sp_CostumWeaponChargeing;
			ItemTotalInformation* sp_CostumShieldChargeing;
			char sp_isPossibleNewConnect;
			char sp_isIgnoreSkillCoolTime;

			ProtocolLogger sp_ProtocolLog;
			unsigned short sp_MultiHitNotIndex;
			SoulCollectStruct sp_SoulCollect;
			SHINE_XY_TYPE sp_EntrancePoint;
			ItemActionObserveManager sp_ItemActionObserves;
			char sp_WillDisconnect;
			Custom::vector<Observer, Custom::allocator<Observer> > observers_;
			char sp_tempDataForItemSlot;
			ItemTotalInformation sp_tempDataForRandOptChange;
			Enums::ABSTATEINDEX sp_nPolymorphAbstateIndex;
			MobTacticElement::MobActionArgument* m_pCaptivateAI;
			MobTargetPlayerCaptivate m_TargetSelect;
			ShineObject* m_pAITarget;
			SpamChatTimeInfo sp_SpamChatTimeInfo;
			SpamerInfo sp_SpamerInfo;
			int sp_SpamerInfoSaveChack;
			unsigned int tAutoSaveTime;
			char sp_MysteryVaultUI;
			unsigned int sp_NextCharTitleChangeTime;
			unsigned int sp_ReviveReqProcessTime;
			char sp_IsQuestRewardReq;
			unsigned int sp_Spammer_ChatBan;
			MapNameStruct sp_Gamble_PrevMapName;
			unsigned long long sp_Gamble_nTotalExchangedCoin;
			unsigned long long sp_Gamble_nCurCoin;

			Enums::GAMBLE_TYPE sp_Gamble_JoinType;
			unsigned int sp_Gamble_SessionCloseingTime;
			unsigned short nReactionNpcHandle;
			char sp_GodOfSlotMachine[10];
			int sp_nDamageAbsorb;
			int sp_nRemainingDamageAbsorb;

			CardCollection::CardCollectionAlbum sp_CardCollectAlbum;
			CardCollection::CardCollectionBookmark sp_CardCollectBookmark;
			CardCollection::CardCollectionReward sp_CardCollectReward;
			unnamed_type_sp_RebirthState sp_RebirthState;
			unsigned short sp_CastingBarTargetHandle;
			unsigned int sp_SwingTime;
			MOVER_LINKDATA sp_Mover_LinkData;
			char sp_Mover_nSlot;
			ShineObject* sp_Mover_pObject;
			unsigned short sp_ArrangeInvenCnt;
			unsigned int sp_ArrangeInvenDelayCheckTime;
			LPInfo sp_Sen_LP;
			int sp_dLastBoothSearchOpeningTime;
			int sp_dLastBoothSearchReqTime;

			PROTO_TUTORIAL_INFO sp_TutorialInfo;
#pragma pack(push, 1)
			__declspec(align(1)) Name5 sp_LoginCharID;
#pragma pack(pop)
			char sp_nChatFontColor;
			char sp_nChatBalloonColor;
			PetInfoPlayer sp_PetInfo;
			PetInfoForLink sp_PetInfoLink;
			ShineObject* sp_Pet_pObject;
			Metronome sp_Pet_HouseTick;
			Metronome sp_Pet_BoothTick;
			Metronome sp_Pet_DanceTick;
			unsigned int sp_Pet_DanceDataIndex;
			unsigned int sp_UseItemMinimonCheckTime;

			USEITEM_MINIMON_INFO sp_UseItemMinimon;
			UseITemMinimon_LoginSlot sp_UseItemMinimon_LoginSlot;
			CSellItemManager sp_SellItemManager;
		};
#pragma pack(pop)
	}
	struct LockedCell
	{
		unsigned short lc_Index;
		InvenCellReleaser* lc_Releaser;
		ITEM_INVEN lc_InvenLocCurrent;
		ITEM_INVEN lc_InvenLocExchange;
		__declspec(align(8)) $A2F39EA2A6D2C55147FFF741C43D4F89 lc_Argument;
	};
	struct __declspec(align(8)) InventoryCellLockList : InventoryCellLock
	{
		ShineObject* icll_sp;
		//Custom::list<LockedCell> icll_List;
		//LockedCell icll_Array[192];
		//char icll_AllLock;
	};
	struct $8C45B2014413BB31C96D391D509168EF
	{
		CharacterInventory itembag;
		InventoryCellLockList invenlocklist;
	};

	struct LuaScript
	{
		void* vfptr;
		lua_State* ls_LuaObject;
	};
	struct BTree
	{
		unsigned int bt_id;
		BTree* bt_subtree[256];
	};
	struct PROTO_NC_MENU_SHOPOPENTABLE_CMD
	{
		char package[3005];
	};
	struct NPCItemListTable
	{
		PROTO_NC_MENU_SHOPOPENTABLE_CMD* nilt_Packet[100];
		int nilt_TableNumber;
		BTree nilt_Index2Handle;
	};

	struct  ItemListOption : OptionReader
	{
		PROTO_NC_MENU_SHOPOPENTABLE_CMD* ilo_TempBuffer;
	};
	struct KQRegenTable_Element
	{
		MapNameStruct tablename;
		OptionReader* Reader;
	};
	struct KQRegenTable
	{
		KQRegenTable_Element kqrt_Array[50];
		int kqrt_Number;
	};
	struct MobRoamingPoint
	{
		struct unnamed_type_mrp_Val
		{
			unsigned short pointer : 15;
			unsigned short direct : 1;
		};

		unnamed_type_mrp_Val mrp_Val;
	};

	namespace MobRoaming
	{
#pragma pack(push, 2)
		struct PathElement
		{
			unsigned short ID;
			unsigned int x;
			unsigned int y;
			char EventIndex[32];
		};
#pragma pack(pop)

		struct MobRoamingPath : Custom::vector<PathElement, Custom::allocator<PathElement> >
		{
			ORToken mrp_GroupName;
		};
	}

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOB_CMD_Old
	{
		union unnamed_type_flag
		{
			ABNORMAL_STATE_BIT abstatebit;
			char gate2where[12];
		};
		NetworkCommand netcmd;
		unsigned short handle;
		char mode;
		unsigned short mobid;
		SHINE_COORD_TYPE coord;
		char flagstate;
		unnamed_type_flag flag;
		char sAnimation[32];
		char nAnimationLevel;
		char nKQTeamType;
		char bRegenAni;
	};
#pragma pack(pop)


#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOB_CMD_Old_2
	{
		union unnamed_type_flag
		{
			ABNORMAL_STATE_BIT_2 abstatebit;
			char gate2where[12];
		};
		NetworkCommand netcmd;
		unsigned short handle;
		char mode;
		unsigned short mobid;
		SHINE_COORD_TYPE coord;
		char flagstate;
		unnamed_type_flag flag;
		char sAnimation[32];
		char nAnimationLevel;
		char nKQTeamType;
		char bRegenAni;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PROTO_NC_BRIEFINFO_REGENMOB_CMD
	{
		union unnamed_type_flag
		{
			ABNORMAL_STATE_BIT abstatebit;
			char gate2where[12];
		};

		unsigned short handle;
		char mode;
		unsigned short mobid;
		SHINE_COORD_TYPE coord;
		char flagstate;
		unnamed_type_flag flag;
		char sAnimation[32];
		char nAnimationLevel;
		char nKQTeamType;
		char bRegenAni;
	};
#pragma pack(pop)

	struct BriefInformationMob
	{
		ProtocolPacket bim_pack;
		char bim_array[152];
		NetworkCommand* bim_nc;
		PROTO_NC_BRIEFINFO_REGENMOB_CMD* bim_BriefInfo;
	};

#pragma pack(push, 1)
	struct MobInfo
	{
		unsigned short ID;
		char InxName[32];
		char Name[32];
		unsigned int Level;
		unsigned int MaxHP;
		unsigned int WalkSpeed;
		unsigned int RunSpeed;
		char IsNPC;
		unsigned int Size;
		Enums::WeaponTypeEnum WeaponType;
		Enums::ArmorTypeEnum ArmorType;
		Enums::MobGradeType GradeType;
		Enums::MobType Type;
		char IsPlayerSide;
		unsigned int AbsoluteSize;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct MobInfoServer
	{
		unsigned int ID;
		char InxName[32];
		char Visible;
		unsigned short AC;
		unsigned short TB;
		unsigned short MR;
		unsigned short MB;
		Enums::EnemyDetect EnemyDetectType;
		Enums::MobKillType MobKillInx;
		unsigned int MonEXP;
		unsigned short EXPRange;
		unsigned short DetectCha;
		char ResetInterval;
		unsigned short CutInterval;
		unsigned int CutNonAT;
		unsigned int FollowCha;
		unsigned short PceHPRcvDly;
		unsigned short PceHPRcv;
		unsigned short AtkHPRcvDly;
		unsigned short AtkHPRcv;
		unsigned short Str;
		unsigned short Dex;
		unsigned short Con;
		unsigned short Int;
		unsigned short Men;
		Enums::MobRace MobRaceType;
		char Rank;
		unsigned int FamilyArea;
		unsigned int FamilyRescArea;
		char FamilyRescCount;
		unsigned short BloodingResi;
		unsigned short StunResi;
		unsigned short MoveSpeedResi;
		unsigned short FearResi;
		char ResIndex[32];
		unsigned short KQKillPoint;
		char Return2Regen;
		char IsRoaming;
		char RoamingNumber;
		unsigned short RoamingDistance;
		unsigned short RoamingRestTime;
		unsigned short MaxSP;
		char BroadAtDead;
		unsigned short TurnSpeed;
		unsigned short WalkChase;
		char AllCanLoot;
		unsigned short DmgByHealMin;
		unsigned short DmgByHealMax;
		unsigned short RegenInterval;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct MobWeapon
	{
		unsigned int ID;
		char InxName[33];
		char Skill[32];
		unsigned short AtkSpd;
		unsigned short BlastRate;
		unsigned short AtkDly;
		unsigned short SwingTime;
		unsigned short HitTime;
		Enums::ATKTYPE AtkType;
		unsigned int MinWC;
		unsigned int MaxWC;
		unsigned short TH;
		unsigned int MinMA;
		unsigned int MaxMA;
		unsigned short MH;
		unsigned short Range;
		Enums::MOBATTACKTARGET MopAttackTarget;
		Enums::NORMALHITTYPE HitType;
		char StaName[33];
		unsigned short StaStrength;
		unsigned short StaRate;
		unsigned short AggroInitialize;
	};
#pragma pack(pop)

	struct MobSpecies
	{
		unsigned short ID;
		char MobName[4][33];
	};

#pragma pack(push, 1)
	struct QuestSpecies
	{
		unsigned short ID;
		char MobGroupName[5][33];
	};
#pragma pack(pop)

	struct MobKillAnnounce
	{
		unsigned int MobID;
		Enums::MobKillAnnounceType TextIndex;
	};

	struct MobKillLog
	{
		unsigned int MobID;
	};

#pragma pack(push, 1)
	struct MobRegenAni
	{
		char MobIDX[32];
		unsigned short RegenTime;
		char GroupAbStateIDX[32];
		char IsAggro;
	};
#pragma pack(pop)

	namespace MobDataBox
	{
		struct MobDataBoxIndex
		{
			struct unnamed_type_MobIndexFlag
			{
				char IsBufferToBoss : 1;
				char MobAutoAction_Damaged : 1;
			};

			struct _MobWeaponIndex
			{
				MobWeapon* weapon;
				unsigned short skill;
				Enums::ABSTATEINDEX abstate;
			};

			MobInfo* data;
			MobInfoServer* serv;
			_MobWeaponIndex* weapon;
			int weaponnumber;
			MobSpecies* species;
			unsigned short registindex;
			QuestSpecies* questspecies;
			MobKillAnnounce* p_mobkillannounce;
			MobKillLog* p_mobkilllog;
			unsigned int p_MobLifeTime;
			unnamed_type_MobIndexFlag MobIndexFlag;
			MobRegenAni* pRegenAni;
			unsigned int nRegenAbstateGroup;
		};
	}

	struct MobAttackSequence
	{
		struct SkillChange
		{
			unsigned short sc_From;
			unsigned short sc_To;
			unsigned int sc_Value;
			unsigned int sc_ASIndex;
		};

		struct SkillChangeList : List<SkillChange>
		{
			SkillChange scl_Array[100];
		};

#pragma pack(push, 4)
		struct AttackElement4Mob
		{
			unsigned short ae4m_BossMob;
			char ae4m_SequenceLength;
			unsigned short ae4m_skillID[500];
			SkillChangeList ae4m_OutOfRangeBody;
			SkillChangeList ae4m_HPLowBody;
			SkillChangeList ae4m_TargetStateBody;
			SkillChangeList* ae4m_OutOfRange;
			SkillChangeList* ae4m_HPLow;
			SkillChangeList* ae4m_TargetState;
			SkillChangeList* ae4m_SaveNextSkill;
			SkillChangeList ae4m_SaveNextSkillBody;
			SkillChangeList ae4m_HPLow_ChangeOrderBody;
			SkillChangeList* ae4m_HPLow_ChangeOrder;
			char ae4m_StartIndex;
		};
#pragma pack(pop)

		int mas_MobNumber;
		AttackElement4Mob mas_AttackPattern[400];
	};

	namespace MobRegenStruct
	{
		struct RegenRegion
		{
			unsigned int rgs_CenterX;
			unsigned int rgs_CenterY;
			unsigned int rgs_Width;
			unsigned int rgs_Height;
			unsigned int rgs_Rotate;
		};

		struct MobBreedSecond
		{
			unsigned int standard;
			unsigned int minsec;
			unsigned int maxsec;
			int timedist[9];
		};
	}

	namespace MobRegenClass
	{
		struct MobBreeder
		{
			struct unnamed_type_mb_NextRegen
			{
				unsigned int leftregen;
				char waitregen;
				unsigned int currentregensec;
				unsigned int regentime_tick;
				unsigned int deadtime_tick;
			};

			struct unnamed_type_mb_Family
			{
				MobBreeder* prev;
				MobBreeder* next;
			};

			MobBreederGroup* mb_Group;
			char mb_IsRegenEnable;
			unsigned short mb_MobID;
			int mb_Level;
			MobRegenStruct::MobBreedSecond mb_RegenTime;
			unsigned short mb_MobHandle;
			unnamed_type_mb_NextRegen mb_NextRegen;
			int mb_RegenCount;
			unnamed_type_mb_Family mb_Family;
			PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD* mb_BanditTemplete;
		};

		struct MobBreederGroup : List<MobBreeder>
		{
			struct unnamed_type_mbg_RegenRegion
			{
				struct unnamed_type_rectangle
				{
					int width;
					int height;
					int cosD1024;
					int sinD1024;
				};

				struct unnamed_type_circular
				{
					int radious;
					int radioussqr;
				};

				MobRegenStruct::RegenRegion region;
				unnamed_type_rectangle rectangle;
				unnamed_type_circular circular;
			};

			MobBreeder mbg_array[64];
			ORToken mbg_GroupName;
			char mbg_isFamily;
			__declspec(align(1)) MobRegenStruct::MobBreedSecond mbg_regentime;
			__declspec(align(1)) MapNameStruct mbg_RegenMap;
			ORToken mbg_AIType;
			unnamed_type_mbg_RegenRegion mbg_RegenRegion;
			int mbg_RegenDirect;
			MobBreeder* mbg_Leader;
			MobRoaming::MobRoamingPath* mbg_RoamingPath;
		};
	}

	namespace HitMeList
	{
		struct Enemy
		{
			union unnamed_type_e_AttackerInfo
			{
#pragma pack(push, 4)
				struct unnamed_type_soloing
				{
					unsigned int chrregnum;
					unsigned short chrhandle;
				};
#pragma pack(pop)

				unnamed_type_soloing soloing;
				unsigned short partyregnum;
				unsigned short Raidregnum;
			};

			enum unnamed_type_e_Type
			{
				E_PLAYER = 0x0,
				E_PARTY = 0x1,
				E_RAID = 0x2,
			};

			unnamed_type_e_Type e_Type;
			unnamed_type_e_AttackerInfo e_AttackerInfo;
			unsigned int e_LastHitTime;
			int e_TotalDamage;
			ShineObjectClass::ShineObject* e_Attacker;
		};

		struct EnemyPlayer
		{
			unsigned int ei_nCharRegNo;
			ShineObjectClass::ShineObject* ei_Attacker;
			unsigned int ei_LastHitTime;
			unsigned int ei_TotalDamage;
		};

		struct EnemyList : List<Enemy>
		{
			Enemy el_array[16];
			Custom::vector<EnemyPlayer, Custom::allocator<EnemyPlayer> > el_vecEnemyPlayer;
			unsigned int el_nTotalDamage;
		};
	}

	struct FamilyMobList
	{
		ShineObjectClass::ShineMob* fml_Prev;
		ShineObjectClass::ShineMob* fml_Next;
	};

	namespace NPCAction
	{
		struct IAction
		{
			IAction_vtbl* vft;
		};

		struct IAction_vtbl
		{
			void(__thiscall* IAction_Destructor)(IAction* self);
			void(__thiscall* exe)(IAction* self, ShineObjectClass::ShineObject*, ShineObjectClass::ShineObject*);
		};

		struct ICondition : IObserver
		{
		};

		struct Trigger : IObserver
		{
			ICondition* condition_;
			Custom::vector<IAction*, Custom::allocator<IAction*> > actions_;
		};
	}

	struct MobResist
	{
		char InxName[32];
		unsigned short ResDot;
		unsigned short ResStun;
		unsigned short ResMoveSpeed;
		unsigned short ResFear;
		unsigned short ResBinding;
		unsigned short ResReverse;
		unsigned short ResMesmerize;
		unsigned short ResSeverBone;
		unsigned short ResKnockBack;
		unsigned short ResTBMinus;
	};

	struct MobCondition_vtbl
	{
		void(__thiscall* MobCondition_Destructor)(MobCondition* self);
		char(__thiscall* MC_CheckCondition)(MobCondition* self, ShineObjectClass::ShineObject*);
	};

	struct MobCondition
	{
		MobCondition_vtbl* vft;
		char m_nAniLv;
		unsigned int m_nValueMin;
		unsigned int m_nValueMax;
	};

	namespace ShineObjectClass
	{
		struct RoamingInformation
		{
			unsigned short isroaming : 1;
			unsigned short maxroamingnum : 7;
			unsigned short roamingnum : 8;
			unsigned short maxroamingdist : 16;
		};

		struct ShineMob : ShineMobileObject
		{
#pragma pack(push, 2)
			struct unnamed_type_sm_ReadyWeapon
			{
				Custom::vector<unsigned long, Custom::allocator<unsigned long> > nextblast;
				int weaponindex;
				MobAttackSequence::AttackElement4Mob* attacksequence;
				int attacksequenceindex;
				unsigned short NextSaveSkill;
				char bUseNextSaveSkill;
			};
#pragma pack(pop)

			struct unnamed_type_sm_ReallyDead
			{
				char senddeadpacket;
				unsigned short attacker;
			};

			struct unnamed_type_sm_Flag
			{
				char MobAggro : 1;
				char HealAtPiece : 1;
				char InNormalAttack : 1;
				char JustAttacked : 1;
			};

			struct stSM_RESCUE_tag
			{
				struct unnamed_type_bit
				{
					char bitrequest : 1;
					char bitscreamack : 1;
					char bitrescuechat : 1;
				};

				unnamed_type_bit bit;
				ShineObject* rescuewho;
				unsigned int lasthp;
			};

			Metronome sm_WanderChat;
			TargetAnalyser_Player sm_TargetAnalyser;
			MobRoaming::MobRoamingPath* sm_RoamingPath;
			MobRoamingPoint sm_CurrRoamInterval;
			unsigned int sm_MobRegnum;
			unsigned int sm_HP;
			unsigned int sm_SP;
			BriefInformationMob sm_MobBriefInfo;
			PROTO_NC_CHAR_BASE_CMD::LoginLocation sm_LoginLoc;
			MobDataBox::MobDataBoxIndex* sm_MobDataBox;
			char sm_MobLevel;
			__declspec(align(4)) unnamed_type_sm_ReadyWeapon sm_ReadyWeapon;
			unnamed_type_sm_ReallyDead sm_ReallyDead;
			unsigned int sm_DeadTime;
			unsigned int sm_DeadDelayTime;
			MobTacticElement::MobActionArgument sm_ArtificalIntelligence;
			MobRegenClass::MobBreeder* sm_Breeder;
			unsigned int sm_Guild;

			HitMeList::EnemyList sm_HitMeList;
			SHINE_XY_TYPE sm_RegenLoc;
			SHINE_XY_TYPE sm_LastHittedLoc;
			unnamed_type_sm_Flag sm_Flag;
			unsigned short sm_CurrentTarget;
			char sm_DuringFuncIndex;
			__declspec(align(1)) FamilyMobList sm_FamilyList;
			stSM_RESCUE_tag sm_Rescue;

			Custom::vector<unsigned short, Custom::allocator<unsigned short> > sm_WeaponUseRate;
			RoamingInformation sm_RoamingInfo;
			ShineObject* sm_LastTarget;
			ShineObject* sm_MyTarget;
			char sm_bSendTargetInfo;
			char sm_bTarget;

			Custom::vector<NPCAction::Trigger, Custom::allocator<NPCAction::Trigger> >* triggers_;
			TickTimer m_LifeTimer;
			int sm_StaNumberForDrop;
			unsigned int tNextRoamingWaitTime;
			unsigned int sm_MaxHPAtMobInfo;
			unsigned int sm_MonEXPAtMobInfo;
			char sm_IsItemDrop;
			__declspec(align(1)) MobResist sm_MobResist;
			Enums::EnemyDetect sm_EnemyDetect;
			int sm_MobIsPlayerSide;
			int sm_WalkSpeedAtMobInfo;
			int sm_RunSpeedAtMobInfo;
			int sm_HPRegen;
			unsigned short sm_ItemDropMobID;
			Custom::vector<MobCondition*, Custom::allocator<MobCondition*> >* sm_pMobConditionList;
			unsigned int sm_tRegenAniTime;
			char sm_bRegenAniComplete;
		};
	}

	struct ItemAttrCls_ByteLot : ItemAttributeClass
	{
	};

	struct ItemAttrCls_WordLot : ItemAttributeClass
	{
	};

	struct ItemAttrCls_DwrdLot : ItemAttributeClass
	{
	};

	struct ItemAttrCls_QuestLot : ItemAttrCls_WordLot
	{
	};

	struct ItemAttrCls_NotLot : ItemAttributeClass
	{
	};

	struct ItemAttrCls_Amulet : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Weapon : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Armor : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Shield : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Boot : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Furniture : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Decoration : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_SkillScroll : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_RecallScroll : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_BindItem : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_UpSource : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_ItemChest : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_WeaponTitlaLicence : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_KingdomQuestItem : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_MiniHouseSkin : ItemAttributeClass
	{
	};

	struct ItemAttrCls_UpgradeRedGem : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_UpgradeBlueGem : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_UpgradeGoldGem : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_KQStep : ItemAttrCls_WordLot
	{
	};

	struct ItemAttrCls_Feed : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_Riding : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Amount : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_CostumWeapon : ItemAttributeClass
	{
	};

	struct ItemAttrCls_CostumShield : ItemAttributeClass
	{
	};

	struct ItemAttrCls_ActionItem : ItemAttributeClass
	{
	};

	struct ItemAttrCls_Enchant : ItemAttributeClass
	{
	};

	struct ItemAttrCls_GBCoin : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Capsule : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_CardCollect_Close : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_CardCollect : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_NoEffect : ItemAttrCls_ByteLot
	{
	};

	struct ItemAttrCls_ActiveSkill : ItemAttributeClass
	{
	};

	struct ItemAttrCls_Pet : ItemAttrCls_NotLot
	{
	};

	struct ItemAttrCls_Bracelet : ItemAttrCls_NotLot
	{
	};

	struct ItemAttributeClassContainer
	{
		ItemAttributeClass iacc_default;
		ItemAttrCls_ByteLot iacc_bytelot;
		ItemAttrCls_WordLot iacc_wordlot;
		ItemAttrCls_DwrdLot iacc_dwrdlot;
		ItemAttrCls_QuestLot iacc_quest;
		ItemAttrCls_Amulet iacc_amulet;
		ItemAttrCls_Weapon iacc_weapon;
		ItemAttrCls_Armor iacc_armor;
		ItemAttrCls_Shield iacc_shield;
		ItemAttrCls_Boot iacc_boot;
		ItemAttrCls_Furniture iacc_furniture;
		ItemAttrCls_Decoration iacc_decorate;
		ItemAttrCls_SkillScroll iacc_skillscroll;
		ItemAttrCls_RecallScroll iacc_recallscroll;
		ItemAttrCls_BindItem iacc_binditem;
		ItemAttrCls_UpSource iacc_upsource;
		ItemAttrCls_ItemChest iacc_itemchest;
		ItemAttrCls_WeaponTitlaLicence iacc_weapontitlalicence;
		ItemAttrCls_KingdomQuestItem iacc_kingdomquest;
		ItemAttrCls_MiniHouseSkin iacc_minihouseskin;
		ItemAttrCls_UpgradeRedGem iacc_upgraderedgem;
		ItemAttrCls_UpgradeBlueGem iacc_upgradebluegem;
		ItemAttrCls_UpgradeGoldGem iacc_upgradegoldgem;
		ItemAttrCls_KQStep iacc_kqstep;
		ItemAttrCls_Feed iacc_feed;
		ItemAttrCls_Riding iacc_riding;
		ItemAttrCls_Amount iacc_amount;
		ItemAttrCls_CostumWeapon iacc_costumweapon;
		ItemAttrCls_CostumShield iacc_costumshield;
		ItemAttrCls_ActionItem iacc_actionitem;
		ItemAttrCls_Enchant iacc_enchant;
		ItemAttrCls_GBCoin iacc_gbcoin;
		ItemAttrCls_Capsule iacc_capsule;
		ItemAttrCls_CardCollect_Close iacc_closemobcard;
		ItemAttrCls_CardCollect iacc_cardcollect;
		ItemAttrCls_NoEffect iacc_NoEffect;
		ItemAttrCls_ActiveSkill iacc_ActiveSkill;
		ItemAttrCls_Pet iacc_Pet;
		ItemAttrCls_Bracelet iacc_Bracelet;
		ItemAttributeClass* iacc_Array[39];
	};
	struct CommonParameter
	{
		char level;
		char nextexp[50];
#pragma pack(push ,1)
		unsigned short stat[28];
		unsigned int ExpLostAtPvP;
#pragma pack(pop)
		char checksum;
	};

	struct FreeStatStr
	{
		char Stat;
#pragma pack(push ,1)
		unsigned short WCAbsolute;
#pragma pack(pop)
		char checksum;
	};

	struct FreeStatInt
	{
		char Stat;
#pragma pack(push ,1)
		unsigned short MAAbsolute;
#pragma pack(pop)
		char checksum;
	};

	struct FreeStatDex
	{
		char Stat;
#pragma pack(push ,1)
		unsigned short THRate;
		unsigned short TBRate;
#pragma pack(pop)
		char checksum;
	};

	struct FreeStatCon
	{
		char Stat;
#pragma pack(push ,1)
		unsigned short ACAbsoulte;
		unsigned short BlockRate;
		unsigned short MaxHP;
#pragma pack(pop)
		char checksum;
	};

	struct FreeStatMen
	{
		char Stat;
#pragma pack(push ,1)
		unsigned short MRAbsolute;
		unsigned short CriRate;
		unsigned short MaxSP;
#pragma pack(pop)
		char checksum;
	};

	struct ShineParameter
	{
		unsigned int chrrunspeed;
		unsigned int chrwalkspeed;
		unsigned int chrattackspeed;
		unsigned int shoutlevel;
		unsigned int shoutdelay;
		char levellimit;
		long double maxexpbonus;
		unsigned int RestExpRate;
		unsigned int MinNeedTime;
		unsigned int DefaultBonusTime;
		unsigned int IntervalTime;
		unsigned int AddBuffTime;
		unsigned int MaxBuffTime;
		char LostExpLevel;
		char MaxFreeStat;
		unsigned long long nextexp[151];
		CommonParameter* commonparam[151];
		FreeStatStr** freestatStr;
		FreeStatInt** freestatInt;
		FreeStatDex** freestatDex;
		FreeStatCon** freestatCon;
		FreeStatMen** freestatMen;
	};
	struct ShineCommonParameter
	{
		OptionReader scp_or;
		ShineParameter scp_param;
	};

	struct PARTY_MEMBER_SLOT
	{
		PROTO_PARTY_MEMBER_AND_ZONEMERCHINE MemberInform;
		void* memberobj;
	};

	struct  PARTY_SLOT
	{
		char NumOfMember;
		PARTY_MEMBER_SLOT Members[5];
		CLooting m_Looting;
		bool IsBelongItemDiceGameIng;
		bool isRaidTypeParty;
	};
#pragma pack(push,2)
	struct PROTO_RICHPRESENCE_UPDATE
	{
		NetworkCommand cmd;
		char state[64];
		char details[64];
		int64_t StartTimestamp;
		int64_t EndTimestamp;
		char ImageName[13];
		char MapName[32];
	};
#pragma pack(pop)
	struct LiveRankingInfos
	{
		PROTO_AVATAR_SHAPE_INFO shape;
		unsigned int damage;
		Name5 name;
	};
#pragma pack(push,2)
	struct PROTO_LIVEDAMAGE
	{
		NetworkCommand cmd;
		int entrys;
		LiveRankingInfos infos[250];
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct PROTO_NC_BRIEFINFO_MOB_CMD
	{
		NetworkCommand netcmd;
		char mobnum;
		PROTO_NC_BRIEFINFO_REGENMOB_CMD mobs[28];
	};
	struct PROTO_NC_BRIEFINFO_REGENMOB_CMD_2
	{
		union unnamed_type_flag
		{
			ABNORMAL_STATE_BIT_2 abstatebit;
			char gate2where[12];
		};

		unsigned short handle;
		char mode;
		unsigned short mobid;
		SHINE_COORD_TYPE coord;
		char flagstate;
		unnamed_type_flag flag;
		char sAnimation[32];
		char nAnimationLevel;
		char nKQTeamType;
		char bRegenAni;
	};

	struct PROTO_NC_BRIEFINFO_MOB_CMD_2
	{
		NetworkCommand netcmd;
		char mobnum;
		PROTO_NC_BRIEFINFO_REGENMOB_CMD_2 mobs[28];
	};
#pragma pack(pop)

	namespace BriefInfoExchanger
	{
		struct BriefInfoExchangeMob
		{
			ProtocolPacket bixm_Packet;
			char bixm_Packetbuffer[4321];
			NetworkCommand* bixm_nc;
			PROTO_NC_BRIEFINFO_MOB_CMD* bixm_Pointer;
		};

		struct BriefInfoExchangeMob_2
		{
			ProtocolPacket bixm_Packet;
			char bixm_Packetbuffer[4437];
			NetworkCommand* bixm_nc;
			PROTO_NC_BRIEFINFO_MOB_CMD_2* bixm_Pointer;
		};
	}

	struct AxialListPacketBroadcast : AxialListIterator
	{
		ProtocolPacket* alpb_packet;
		int alpb_packetlength;
	};

	struct TEAM_SCORE_INFO
	{
		int nWinFlag;
		int nScore;
	};

#pragma pack(push, 1)
	struct PROTO_NC_KQ_SCORE_BOARD_INFO_CMD_2k17
	{
		NetworkCommand netcmd;
		char bUseRound;
		char nRound;
		TEAM_SCORE_INFO Red;
		TEAM_SCORE_INFO Blue;
		unsigned short KQID;
	};
	struct PROTO_KQ_INFO_CLIENT
	{
		unsigned int Handle;
		char Status;
		unsigned short NumOfJoiner;
		unsigned short ID;
		char Title[64];
		unsigned short LimitTime;
		int StartTime;
		tm tm_StartTime;
		unsigned short StartWaitTime;
		char MinLevel;
		char MaxLevel;
		unsigned short MinPlayers;
		unsigned short MaxPlayers;
		char PlayerRepeatMode;
		unsigned short PlayerRepeatCount;
		char PlayerRevivalMode;
		char PlayerRevivalCount;
		unsigned short DemandQuest;
		unsigned short DemandItem;
		long long DemandClass;
		char DemandGender;
	};
#pragma pack(pop)
#pragma pack(push,2)
	struct PROTO_KQ_MAP_INFO
	{
		char MapIndex;
		MapNameStruct MapBase;
		MapNameStruct MapName;
		char MapClear;
	};
#pragma pack(pop)
#pragma pack(push,1)
	struct PROTO_KQ_INFO : PROTO_KQ_INFO_CLIENT
	{
		char NextStartMode;
		unsigned short NextStartDelayMin;
		char RepeatMode;
		unsigned short RepeatCount;
		unsigned short RewardIndex;
		unsigned short DemandMobKill;
		int ScheduleTime;
		tm tm_ScheduleTime;
		char RunCounter;
		PROTO_KQ_MAP_INFO MapLink[4];
		char ScriptLanguage[32];
		char ScriptInitValue[32];
		char IsTeamPVP;
		SHINE_XY_TYPE TeamRegenXY[2];
	};
#pragma pack(pop)
	struct KQElementMap
	{
		PROTO_KQ_MAP_INFO mapinfo;
		FieldMap* fld;
		MapInfo* mapinf;
	};
	struct PineScriptToken
	{
		char pst_Buffer[256];
	};
	struct BattleStat
	{
		char bs_ClearAtLink;
		unsigned int bs_KillScore;
		unsigned int bs_DamageAmount;
		unsigned int bs_HealAmount;
		unsigned int bs_SkillBlast;
		unsigned int bs_CriticalNum;
		unsigned int bs_HittedNum;
		unsigned int bs_KnockDownNum;
		unsigned int bs_Dead;
		unsigned int bs_Kill;
		unsigned int bs_Score;
	};
	struct  KQPlayerInform
	{
		unsigned int kqpi_PlyRegnum;
		int kqpi_KnockDown;
		BattleStat kqpi_BattleStat;
		char kqpi_IsKQJoiner;
		char kqpi_nTeamType;
	};

	struct KQPlayerInfoList : CommonList<KQPlayerInform>
	{
	};
	struct KQElement
	{
		unsigned int kqe_Stop;
		PROTO_KQ_INFO kqe_kqinfo;
		KQElementMap kqe_mapinfo[4];
		PineScriptToken kqe_Script;
		PineScriptToken kqe_InitValue;
		KQPlayerInfoList kqe_PlayerList;
	};
#pragma pack(push, 1)
	struct ZONERINGLINKAGESTART
	{
		char machine;
		unsigned short handle;
		unsigned int regnum;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	struct PROTO_NC_INSTANCE_DUNGEON_FIND_RNG
	{
		ZONERINGLINKAGESTART Start;
		Enums::INSTANCE_DUNGEON::CATEGORY InstanceCategory;
		unsigned int IDRegisterNumber;
		ORToken Argument;
		char ServerMapName[33];
		unsigned short Error;
	};
#pragma pack(pop)

	struct MY_SERVER
	{
		char* pServiceName;
		char* pDisplayName;
		int nServerID;
		int nWorldNo;
		int nZoneNo;
	};

#pragma pack(push, 2)
	struct PROTO_NC_INSTANCE_DUNGEON_FIND_RNG_CMD
	{
		NetworkCommand cmd;
		ZONERINGLINKAGESTART Start;
		Enums::INSTANCE_DUNGEON::CATEGORY InstanceCategory;
		unsigned int IDRegisterNumber;
		ORToken Argument;
		char ServerMapName[33];
		unsigned short Error;
	};
#pragma pack(pop)

	struct WEAPON_TITLE_DATA
	{
		unsigned short MobID;
		char Level;
		char Prefix[16];
		char Suffix[16];
		
		#pragma pack(push, 1)
		unsigned int MobKillCount;
		unsigned short MinAdd;
		unsigned short MaxAdd;
		#pragma pack(pop)
		
		char SP1_Reference;
		unsigned short SP1_Type;
		
		#pragma pack(push, 1)
		unsigned int SP1_Value;
		#pragma pack(pop)
		
		char SP2_Reference;

		#pragma pack(push, 1)
		unsigned __int16 SP2_Type;
		unsigned int SP2_Value;
		#pragma pack(pop)

		char SP3_Reference;
		unsigned short SP3_Type;
		unsigned int SP3_Value;
	};

#pragma pack(push, 4)
	struct GuildStorageElement
	{
		//ItemGuildStorage
		void* gse_Storage;
		unsigned long long gse_Cen;
		unsigned long long gse_Token;
		unsigned int gse_Guild;
		char gse_Activate;
	};
#pragma pack(pop)
}

#pragma warning(default:4200) 