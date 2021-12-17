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

	// We Need 63 Elements ( The amount of skins in the game we want to unlock )
	OwnedSkins.AllocateInt32(63); 

	/*
		If your wondering how I obtained the ID of each skin.

		Place hook on W_PlayerSkins.W_PlayerSkins_C.SkinSelectButton, Its parameter is UW_PlayerSkinInfo_C*.
		Knowing that we are able to read int32_t SkinID using the parameter when the function is called. 

		It is called when you are pressing on the button to preview other skins in the customization menu.
	*/

	// ISAAC
	OwnedSkins[0] = 111; // BASIC
	OwnedSkins[1] = 121; // AUTUMN JACKET
	OwnedSkins[2] = 122; // SPRING JACKET
	OwnedSkins[3] = 123; // SUMMER JACKET
	OwnedSkins[4] = 124; // WINTER JACKET
	OwnedSkins[5] = 131; // FULL GOLD
	OwnedSkins[6] = 132; // FULL SILVER
	OwnedSkins[7] = 133; // SUMMER FAN
	OwnedSkins[8] = 134; // WINTER ENJOYER
	OwnedSkins[9] = 141; // MARATHON
	OwnedSkins[10] = 142; // SPRINT

	// TAIGA
	OwnedSkins[11] = 211; // BASIC
	OwnedSkins[12] = 221; // AQUA
	OwnedSkins[13] = 222; // BUBBLE GUM
	OwnedSkins[14] = 223; // CITRUS
	OwnedSkins[15] = 224; // SPARK
	OwnedSkins[16] = 231; // SUNRISE
	OwnedSkins[17] = 234; // SUNSET
	OwnedSkins[18] = 233; // RED CHROME
	OwnedSkins[19] = 232; // BLUE GOLD
	OwnedSkins[20] = 241; // MAJOR LEAGUE
	OwnedSkins[21] = 242; // PREMIER LEAGUE
	OwnedSkins[22] = 243; // BASEBALL STAR

	// CHRIS
	OwnedSkins[23] = 311; // BASIC
	OwnedSkins[24] = 321; // TEAM FOXES
	OwnedSkins[25] = 322; // TEAM LIONS
	OwnedSkins[26] = 323; // TEAM SNAKES
	OwnedSkins[27] = 324; // TEAM WOLVES
	OwnedSkins[28] = 331; // SUNSHINE
	OwnedSkins[29] = 332; // SKYLIGHT
	OwnedSkins[30] = 333; // DARK SIDE
	OwnedSkins[31] = 334; // LIGHT SIDE
	OwnedSkins[32] = 341; // TRACER
	OwnedSkins[33] = 342; // PARKOUR

	// MABLE
	OwnedSkins[34] = 411; // BASIC
	OwnedSkins[35] = 421; // MANGO
	OwnedSkins[36] = 422; // MINT
	OwnedSkins[37] = 423; // PISTACHIO
	OwnedSkins[38] = 424; // STRAWBERRY
	OwnedSkins[39] = 431; // DOUBLE CHOCOLATE
	OwnedSkins[40] = 433; // RED CHOCOLATE
	OwnedSkins[41] = 432; // COZY MORNING
	OwnedSkins[42] = 434; // COZY EVENING
	OwnedSkins[43] = 441; // FOOTBALL STAR
	OwnedSkins[44] = 442; // STREET KID
	OwnedSkins[45] = 443; // STREET ARTIST

	// KATE
	OwnedSkins[46] = 511; // BASIC
	OwnedSkins[47] = 521; // CARAMEL
	OwnedSkins[48] = 522; // ICE CREAM
	OwnedSkins[49] = 523; // MERMAID
	OwnedSkins[50] = 524; // RASPBERRY
	OwnedSkins[51] = 531; // FASHION MODEL
	OwnedSkins[52] = 534; // FASHION DESIGNER
	OwnedSkins[53] = 533; // BLEU DE FRANCE
	OwnedSkins[54] = 535; // LE ROGUE FRANCAIS 
	OwnedSkins[55] = 541; // ROCKET
	OwnedSkins[56] = 542; // GLIDER
	OwnedSkins[57] = 532; // GAMER GIRL

	// BANSHEE
	OwnedSkins[58] = 611; // BASIC
	OwnedSkins[59] = 631; // NURSE

	// AKASHA
	OwnedSkins[60] = 911; // BASIC
	OwnedSkins[61] = 941; // BLOOD MAIDEN

	// IGOR
	OwnedSkins[62] = 101100; // BASIC
	OwnedSkins[63] = 104100; // BEAR

	GameInstance->SkinIDThatsPlayerOwns = OwnedSkins;

	return TRUE;
}
