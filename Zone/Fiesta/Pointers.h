#pragma once
#include "Structures.h"

#define POINTER constexpr unsigned int
#define CAST_POINTER const static auto

namespace Fiesta::Pointers
{
	namespace Patches
	{
		CAST_POINTER LogoutTimer = reinterpret_cast<void*>(0x5585FA);
	}
	
	namespace Structs
	{
		namespace LuaArguments
		{
			constexpr unsigned int Count = 0x14D6FCD8;
			POINTER Interval = 0x14D6FCDC;
			POINTER MaxSkip = 0x14D6FCE0;
			POINTER Summary = 0x14D6FCE4;
			POINTER SkipNumber = 0x14D6FCE8;
			POINTER CertifyArg = 0x14D6FCEC;
		}

		namespace ShineParameters
		{
			POINTER RunSpeed = 0xDA50470;
			POINTER WalkSpeed = 0xDA50474;
		}

		namespace LuaScriptFactor
		{
			POINTER Factor = 0x870DE0;
			POINTER IsFreeze = 0x870DE1;
			POINTER IsRecover = 0x870DD8;
		}

		namespace SetEffect
		{
			POINTER List = 0x14D575C8;
		}
	}
	
	namespace Global
	{
		CAST_POINTER AnnounceSystem = reinterpret_cast<void*>(0x13388678);

		CAST_POINTER SkillDataBox = reinterpret_cast<Structures::SkillDataIndex*>(0x13286828);
		CAST_POINTER PassiveDataBox = reinterpret_cast<struct PassiveDataBox*>(0x13287110);
		CAST_POINTER CharClassDataBox = reinterpret_cast<void*>(0x14D42140);
		CAST_POINTER ItemDataBox = reinterpret_cast<void*>(0x14D4FB90);
		CAST_POINTER ChargedItemEffectDataBox_ChargedItemEffect = reinterpret_cast<void*>(0xAA4280);

		CAST_POINTER ShineObjectManager = reinterpret_cast<void*>(0x132826B8);
		CAST_POINTER ItemAttributClass = reinterpret_cast<Structures::ItemAttributeClassContainer*>(0x150BA478);

		CAST_POINTER FieldContainer = reinterpret_cast<void*>(0xCFD2B70);
		CAST_POINTER ZoneServer = reinterpret_cast<void*>(0x14D45B70);

		CAST_POINTER GlobalProtocolPacket = reinterpret_cast<void*>(0x84D908);
		CAST_POINTER WeaponTitleZone = reinterpret_cast<void*>(0x1328BF78);

		CAST_POINTER GuildStorageManager = reinterpret_cast<void*>(0xD426078);
	}

	namespace Structs2
	{
		const static auto FieldLevelDataBox = reinterpret_cast<void*>(0xD026C30);
	}

	namespace ZoneServer
	{
		POINTER MachineInfo = 0x5A9910;
		POINTER ServiceStart = 0x5AB770;
		POINTER ServiceStartLoop = 0x5AA7A9;
		POINTER StartSky = 0x5AE560;
		POINTER StartEarth = 0x5AD970;
		POINTER StartBlack = 0x5AD910;
		POINTER StartYellow = 0x5AE4E0;
		POINTER StartHome = 0x5ADCE0;
		POINTER StartHouse = 0x5B64E0;
		POINTER StartWide = 0x5AD9A0;
		POINTER StartTough = 0x5B0540;
		POINTER StartSun = 0x5ADBD0;
		POINTER StartMoon = 0x5AE250;
		POINTER StartFull = 0x5B6580;
		POINTER StartSink = 0x5AEFF0;
		POINTER StartStar = 0x5ADFA0;
		POINTER StartSleep = 0x5B67C0;
		POINTER StartOpen = 0x5B6640;
		POINTER StartLong = 0x5B8C00;
		POINTER ServiceIocp = 0x5AA800;
		POINTER ServiceMainThread = 0x5AD780;
		POINTER ServiceAcceptor = 0x5AA7C0;
		POINTER StartStackChecker = 0x5AB800;
		POINTER ServiceCertification = 0x5AC9B0;
		POINTER LuaFromHtml = 0x5B07A0;
		POINTER WorldData = 0x5A9920;
	}

	namespace ZoneConnectionSession
	{
		POINTER Send = 0x5A6ED0;
	}

	namespace LuaScript
	{
		POINTER FunctionCall = 0x5D7BC0;
		POINTER SetFunction = 0x5F5350;
		POINTER SetGlobal = 0x5F8820;
		POINTER PushClosure = 0x5F82D0;
		POINTER PushNumber = 0x5F8110;
		POINTER PushBoolean = 0x5F8360;
		POINTER ToNumber = 0x5F7AD0;
		POINTER ToString = 0x5F7D80;
		POINTER ToBoolean = 0x5F7D00;
		POINTER PushNil = 0x5F80F0;
		POINTER PushString = 0x5F8210;
		POINTER SetTop = 0x5F7300;
		POINTER GetTop = 0x5F72E0;
		POINTER GetTable = 0x5F8430;
		POINTER CreateTable = 0x5F8650;
		POINTER Next = 0x5F90C0;
		POINTER Type = 0x5F7680;
	}

	namespace ClusterManager
	{
		POINTER PlayerIntoInstanceDungeon = 0x486D80;
	}

	namespace ShinePlayer
	{
		namespace Packets
		{
			namespace Actions
			{
				POINTER RoarRequest = 0x5404D0; // NC_ACT_ROAR_REQ
				POINTER ChatRequest = 0x45A400; // NC_ACT_CHAT_REQ
				POINTER ShoutCommand = 0x458E80; // NC_ACT_SHOUT_CMD
				POINTER OpenNpcMenuAck = 0x4C4910; // NC_ACT_NPCMENUOPEN_ACK
			}

			namespace Battle
			{
				POINTER SkillFieldCastRequest = 0x57F400; // NC_BAT_SKILLBASH_FLD_CAST_REQ
				POINTER SkillObjectCastRequest = 0x57FA50; // NC_BAT_SKILLBASH_OBJ_CAST_REQ
			}

			namespace Guild
			{
				POINTER OpenStorageRequest = 0x4762D0; // NC_GUILD_STORAGEOPEN_REQ
			}

			namespace ItemMix
			{
				POINTER ItemRequest = 0x521540; // NC_ITEM_MIX_ITEM_REQ
			}

			namespace Map
			{
				POINTER TownPortalRequest = 0x49FE70; // NC_MAP_TOWNPORTAL_REQ
			}
		}

		POINTER GetInsDunGeonInRegNoAndType = 0x5605F0;
		POINTER FindItemFromInventory = 0x589990;
		POINTER LinkReplyCheck = 0x50EC40;
		POINTER DestroyItem = 0x00527B60;
		POINTER GatherComplete = 0x46B2F0;
		POINTER ClassChange = 0x4521B0;
		POINTER PickupItem = 0x52FAF0;
		POINTER GainFame = 0x42DF00;
		POINTER Revival = 0x57AB90;
		POINTER SetIgnoreCooltime = 0x560220;
		POINTER NotifyParameterChange = 0x503C10;
	}

	namespace ShineObject
	{
		POINTER Logout = 0x54B780;
		POINTER DistanceSquar = 0x4028F0;
	}

	namespace ShineMobileObject
	{
		POINTER SkillBlast = 0x581160;
	}

	namespace ShineMob
	{
		POINTER CanBeGathered = 0x46AF50;
	}

	namespace AmpersandCommand
	{
		POINTER Constructor = 0x425B70;
		POINTER Store = 0x41A310;
		POINTER LinkTo = 0x41A7E0;
		POINTER LearnSkill = 0x41C290;
		POINTER LearnPassive = 0x41F270;
		POINTER MakeItem = 0x41B8A0;
		POINTER IgnoreSkillCoolTime = 0x424EC0;
	}

	namespace ItemDataBox
	{
		/** ItemDataBox::operator[] */
		POINTER FindItemById = 0x419020;
		POINTER ConvertToItemId = 0x418FF0;
	}

	namespace NpcManager
	{
		POINTER Operator = 0x4C52E0;
	}

	namespace OptionReader
	{
		POINTER Constructor = 0x646A30;
		POINTER SelectFromOrder = 0x647A60;
		POINTER Read = 0x646BF0;
	}

	namespace AnnounceSystem
	{
		POINTER ItemUpgrade = 0x5B8E50;
		POINTER ItemTake = 0x5B8F50;
		POINTER LevelMax = 0x5B8F70;
		POINTER ClassUp = 0x5B9030;
		POINTER CharacterTitle = 0x5B9100;
		POINTER Roar = 0x5B91F0;
		POINTER ProposeAccept = 0x5B92A0;
		POINTER WeddingStart = 0x5B9380;
	}

	namespace NpcItemList
	{
		POINTER ReadTable = 0x4C5130;
		POINTER MenuPacket = 0x4C5050;
	}

	namespace ItemListOption
	{
		POINTER PacketMake = 0x4C4DE0;
	}

	namespace FieldContainer
	{
		POINTER GetInstanceDungeonInfoByMapName = 0x4844E0;
		POINTER CanEnterIndun = 0x4624D0;
		POINTER FindMap = 0x466A60;
	}

	namespace FieldLevelDataBox
	{
		POINTER GetFieldLv = 0x46A370;
	}

	namespace Quest
	{
		POINTER IsDoingQuest = 0x6304D0;
	}

	namespace ItemInventoryCell
	{
		POINTER Constructor = 0x6447B0;
		POINTER GetAttributeProc = 0x43C110;
		POINTER ItemIdentify = 0x43C120;
		POINTER GetItemLot = 0x4707E0;
		POINTER Clear = 0x470D20;
		POINTER SaveWeaponTitle = 0x59E8A0;
		POINTER StoreItem = 0x642F60;
	}

	namespace ItemDropFromMob::DropItemListForSpecies
	{
		POINTER DropByRate = 0x48E920;
		POINTER Drop = 0x48EB90;
		POINTER ItemDrop = 0x48EF80;
	}

	namespace ZoneRingPacketFind
	{
		POINTER InstanceDungeonRequest = 0x5A92E0;
	}

	namespace ItemActionObserveManager
	{
		POINTER AddAction = 0x5D17F0;
		POINTER DelAction = 0x5D15E0;
	}

	namespace SkillDataBox
	{
		POINTER Operator = 0x448140;
		POINTER GetActive = 0x50FFF0;
		POINTER NextActive = 0x50FFD0;
		POINTER GetPassive = 0x585D10;
		POINTER NextPassive = 0x584F00;
	}

	namespace CharClassDataBox
	{
		POINTER CheckClass = 0x640E40;
	}

	namespace ItemEquipment
	{
		POINTER GetItemID = 0x643840;
	}

	namespace ShnDataFileCheckSum
	{
		POINTER IsFileLoadAllComplete = 0x6313F0;
	}

	namespace WholeSaver
	{
		POINTER SaveLevel2WorldManager = 0x453580;
	}

	namespace AbnormalStateContainer
	{
		POINTER AbstateListInObject = 0x40CF10;
	}

	namespace ItemAttributeClass
	{
		POINTER ArrayOperator = 0x63E2A0;
	}

	namespace Raid 
	{
		POINTER GetMemberRegNoByIndex = 0x63D410;
	}

	namespace Party 
	{
		POINTER ArrayOperator = 0x645340;
	}

	namespace PartyManufacture
	{
		POINTER FindMember = 0x4CC390;
	}

	namespace CharacterTitleZone
	{
		POINTER CheckNewTitle = 0x5CB5F0;
		POINTER SetTitleUsable = 0x5CB0B0;
	}

	namespace WeaponTitleZone
	{
		POINTER GetLevelData = 0x59D6A0;
	}

	namespace ChargedItemEffectDataBox
	{
		POINTER GetItemID = 0x44FA10;
	}

	namespace GuildStorage
	{
		POINTER GetToken = 0x4749E0;
		POINTER SetToken = 0x4749F0;
		POINTER FindStorage = 0x4751F0;
	}

	namespace Parameter
	{
		namespace Container
		{
			POINTER MakeTotal = 0x4C9A40;
		}
	}

	namespace EngageArgument
	{
		POINTER Construct = 0x42ABF0;
	}

	namespace RulesOfEngagement
	{
		POINTER MinWC = 0x4FDBE0;
		POINTER MaxWC = 0x4FEA10;
		POINTER MinMA = 0x4FD640;
		POINTER MaxMA = 0x4FD910;
		POINTER TH = 0x4FC700;
		POINTER TB = 0x4FC950;
		POINTER AC = 0x4FCBC0;
		POINTER MR = 0x4FD3B0;
	}

	namespace Patches
	{
		static void* DisableSkinBreak = reinterpret_cast<void*>(0x5209C4);
		static void* DisableSkinBreakShield = reinterpret_cast<void*>(0x520BF6);
		static void* AbstateLimitPlayer = reinterpret_cast<void*>(0x0040CF58);
	}
}