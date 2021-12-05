#include <Windows.h>
#include <cstdint>
#include "UE4.h"
#include "PatternScan.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return FALSE;

	static byte WorldSig[] = { 0x48, 0x8B, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xDB, 0x74, 0x3B, 0x41, 0xB0, 0x01, 0x33, 0xD2, 0x48, 0x8B, 0xCB, 0xE8 };
	void* WRLD = FindPointer(GetModuleHandleA(NULL), WorldSig, sizeof(WorldSig), 0);
	if (!WRLD) return false;

	UWorld* World = *(UWorld**)(WRLD);
	if (!World) return FALSE;

	UGameInstance* OwningGameInstance = World->OwningGameInstance;
	if (!OwningGameInstance) return FALSE;

	TArray<UPlayer*> LocalPlayers = OwningGameInstance->LocalPlayers;

	UPlayer* LocalPlayer = LocalPlayers[0];
	if (!LocalPlayer) return FALSE;

	UGameViewportClient* ViewportClient = LocalPlayer->ViewportClient;
	if (!ViewportClient) return FALSE;

	UGameInstance* GameInstance = ViewportClient->GameInstance;
	if (!GameInstance) return FALSE;

	TArray<int32_t> OwnedSkins;

	// We Need 54 Elements ( The amount of skins in the game we want to unlock )
	OwnedSkins.Allocate(54); 


	/*
		If your wondering how I obtained the ID of each skin.

		Place hook on W_PlayerSkins.W_PlayerSkins_C.SkinSelectButton, Its parameter is UW_PlayerSkinInfo_C*.
		Knowing that we are able to read int32_t SkinID using the parameter when the function is called. 

		It is called when you are pressing on the button to preview other skins in the customization menu.
	*/

	// ISAAC
	OwnedSkins[0] = 111;
	OwnedSkins[1] = 121;
	OwnedSkins[2] = 122;
	OwnedSkins[3] = 123;
	OwnedSkins[4] = 124;
	OwnedSkins[5] = 131;
	OwnedSkins[6] = 132;
	OwnedSkins[7] = 133;
	OwnedSkins[8] = 134;
	OwnedSkins[9] = 141;
	OwnedSkins[10] = 142;

	// TAIGA
	OwnedSkins[11] = 211;
	OwnedSkins[12] = 221;
	OwnedSkins[13] = 222;
	OwnedSkins[14] = 223;
	OwnedSkins[15] = 224;
	OwnedSkins[16] = 231;
	OwnedSkins[17] = 234;
	OwnedSkins[18] = 233;
	OwnedSkins[19] = 232;
	OwnedSkins[20] = 241;
	OwnedSkins[21] = 242;
	OwnedSkins[22] = 243;

	// CHRIS
	OwnedSkins[23] = 311;
	OwnedSkins[24] = 321;
	OwnedSkins[25] = 322;
	OwnedSkins[26] = 323;
	OwnedSkins[27] = 324;
	OwnedSkins[28] = 331;
	OwnedSkins[29] = 332;
	OwnedSkins[30] = 333;
	OwnedSkins[31] = 334;
	OwnedSkins[32] = 341;
	OwnedSkins[33] = 342;

	// MABLE
	OwnedSkins[34] = 411;
	OwnedSkins[35] = 421;
	OwnedSkins[36] = 422;
	OwnedSkins[37] = 423;
	OwnedSkins[38] = 424;
	OwnedSkins[39] = 431;
	OwnedSkins[40] = 433;
	OwnedSkins[41] = 432;
	OwnedSkins[42] = 434;

	// KATE
	OwnedSkins[43] = 511;
	OwnedSkins[44] = 521;
	OwnedSkins[45] = 522;
	OwnedSkins[46] = 523;
	OwnedSkins[47] = 524;
	OwnedSkins[48] = 531;
	OwnedSkins[49] = 534;
	OwnedSkins[50] = 533;
	OwnedSkins[51] = 535;
	OwnedSkins[52] = 541;
	OwnedSkins[53] = 542;
	OwnedSkins[54] = 532;

	GameInstance->SkinIDThatsPlayerOwns = OwnedSkins;

	return TRUE;
}

