// SADXTitleCardJingles.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "..\sadx-mod-loader\SADXModLoader\include\SADXModLoader.h"

short cardDispTime;
int LoadTitleCardTexture_Wrapper(int minDispTime)
{
	cardDispTime = 0;
	int song;
	switch (CurrentLevel)
	{
	case LevelIDs_StationSquare:
	case 27:
	case 28:
		minDispTime = 348;
		song = MusicIDs_titl_ss;
		break;
	case LevelIDs_EggCarrierOutside:
	case 30:
	case 31:
	case LevelIDs_EggCarrierInside:
		minDispTime = 603;
		song = MusicIDs_titl_egg;
		break;
	case LevelIDs_MysticRuins:
		minDispTime = 484;
		song = MusicIDs_titl_mr1;
		break;
	case LevelIDs_Past:
		minDispTime = 543;
		song = MusicIDs_titl_mr2;
		break;
	default:
		return LoadTitleCardTexture(minDispTime);
	}
	int result = LoadTitleCardTexture(minDispTime);
	ObjectMaster *sm = InitializeSoundManager();
	PlayMusic((MusicIDs)song);
	sm->MainSub(sm);
	sm->MainSub(sm);
	return result;
}

DataPointer(NJS_TEXLIST*, dword_3C53AC4, 0x3C53AC4);
DataPointer(int, dword_3B28114, 0x3B28114);
DataPointer(Uint8, byte_3C53ABF, 0x3C53ABF);
Sint32 __cdecl DisplayTitleCard_r()
{
	if (!(cardDispTime++ <= (unsigned __int16)TitleCardDispTime))
	{
		njReleaseTexture(dword_3C53AC4);
		dword_3B28114 = 1;
		cardDispTime = 0;
		return 1;
	}
	njSetTexture(dword_3C53AC4);
	if (byte_3C53ABF)
	{
		if (byte_3C53ABF == 1)
		{
			DrawBG(0x4000000, (HorizontalStretch * 320.0), (VerticalStretch * 240.0), 1.0, VerticalStretch, VerticalStretch);
			return 0;
		}
		if (byte_3C53ABF == 2)
		{
			DrawBG(0x4000000, (HorizontalStretch * 320.0 + 8.0), (VerticalStretch * 240.0), 1000.0, VerticalStretch, VerticalStretch);
			return 0;
		}
	}
	else
	{
		DrawBG(0x4000000, (HorizontalStretch * 320.0 + 32.0), (VerticalStretch * 240.0), 1.0, VerticalStretch, VerticalStretch);
	}
	return 0;
}

VoidFunc(sub_415210, 0x415210);
void Thing()
{
	SoundManager_Delete2();
	sub_415210();
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_Wrapper);
		WriteJump(DisplayTitleCard, DisplayTitleCard_r);
		WriteCall((void*)0x41749C, Thing);
		WriteCall((void*)0x415B9F, Thing);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}
