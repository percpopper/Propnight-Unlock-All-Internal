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

	/*
		If your wondering how I obtained the IDs.

		Place hook on W_PlayerSkins.W_PlayerSkins_C.SkinSelectButton, Its parameter is UW_PlayerSkinInfo_C*.
		Knowing that we are able to read int32_t SkinID using the parameter when the function is called.
		It is called when you are pressing on the button to preview other skins in the customization menu.
		
		As for the avatars, tags, and banners, these 3 functions were hooked and the 'this' pointer was used to find the ID.
		W_CustomizeAvatarInfo.W_CustomizeAvatarInfo_C.BndEvt__W_CustomizeBannerInfo_Button_69_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
		W_CutomizeTagInfo.W_CutomizeTagInfo_C.BndEvt__W_CutomizeTagInfo_Button_132_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
		W_CustomizeBannerInfo.W_CustomizeBannerInfo_C.BndEvt__W_CustomizeBannerInfo_Button_69_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
		They are called when hovering over the avatar, tag or banner.
	*/


	/////////////////////
	/// SKINS 
	/////////////////////

	TArray<int32_t> SkinIDThatsPlayerOwns;

	SkinIDThatsPlayerOwns.AllocateInt32(71); 

	// ISAAC
	SkinIDThatsPlayerOwns[0] = 111; // BASIC
	SkinIDThatsPlayerOwns[1] = 121; // AUTUMN JACKET
	SkinIDThatsPlayerOwns[2] = 122; // SPRING JACKET
	SkinIDThatsPlayerOwns[3] = 123; // SUMMER JACKET
	SkinIDThatsPlayerOwns[4] = 124; // WINTER JACKET
	SkinIDThatsPlayerOwns[5] = 131; // FULL GOLD
	SkinIDThatsPlayerOwns[6] = 132; // FULL SILVER
	SkinIDThatsPlayerOwns[7] = 133; // SUMMER FAN
	SkinIDThatsPlayerOwns[8] = 134; // WINTER ENJOYER
	SkinIDThatsPlayerOwns[9] = 141; // MARATHON
	SkinIDThatsPlayerOwns[10] = 142; // SPRINT
	SkinIDThatsPlayerOwns[11] = 143; // CHRISTMAS

	// TAIGA
	SkinIDThatsPlayerOwns[12] = 211; // BASIC
	SkinIDThatsPlayerOwns[13] = 221; // AQUA
	SkinIDThatsPlayerOwns[14] = 222; // BUBBLE GUM
	SkinIDThatsPlayerOwns[15] = 223; // CITRUS
	SkinIDThatsPlayerOwns[16] = 224; // SPARK
	SkinIDThatsPlayerOwns[17] = 231; // SUNRISE
	SkinIDThatsPlayerOwns[18] = 234; // SUNSET
	SkinIDThatsPlayerOwns[19] = 233; // RED CHROME
	SkinIDThatsPlayerOwns[20] = 232; // BLUE GOLD
	SkinIDThatsPlayerOwns[21] = 241; // MAJOR LEAGUE
	SkinIDThatsPlayerOwns[22] = 242; // PREMIER LEAGUE
	SkinIDThatsPlayerOwns[23] = 243; // BASEBALL STAR
	SkinIDThatsPlayerOwns[24] = 244; // CHRISTMAS

	// CHRIS
	SkinIDThatsPlayerOwns[25] = 311; // BASIC
	SkinIDThatsPlayerOwns[26] = 321; // TEAM FOXES
	SkinIDThatsPlayerOwns[27] = 322; // TEAM LIONS
	SkinIDThatsPlayerOwns[28] = 323; // TEAM SNAKES
	SkinIDThatsPlayerOwns[29] = 324; // TEAM WOLVES
	SkinIDThatsPlayerOwns[30] = 331; // SUNSHINE
	SkinIDThatsPlayerOwns[31] = 332; // SKYLIGHT
	SkinIDThatsPlayerOwns[32] = 333; // DARK SIDE
	SkinIDThatsPlayerOwns[33] = 334; // LIGHT SIDE
	SkinIDThatsPlayerOwns[34] = 341; // TRACER
	SkinIDThatsPlayerOwns[35] = 342; // PARKOUR
	SkinIDThatsPlayerOwns[36] = 343; // CHRISTMAS

	// MABLE
	SkinIDThatsPlayerOwns[37] = 411; // BASIC
	SkinIDThatsPlayerOwns[38] = 421; // MANGO
	SkinIDThatsPlayerOwns[39] = 422; // MINT
	SkinIDThatsPlayerOwns[40] = 423; // PISTACHIO
	SkinIDThatsPlayerOwns[41] = 424; // STRAWBERRY
	SkinIDThatsPlayerOwns[42] = 431; // DOUBLE CHOCOLATE
	SkinIDThatsPlayerOwns[43] = 433; // RED CHOCOLATE
	SkinIDThatsPlayerOwns[44] = 432; // COZY MORNING
	SkinIDThatsPlayerOwns[45] = 434; // COZY EVENING
	SkinIDThatsPlayerOwns[46] = 441; // FOOTBALL STAR
	SkinIDThatsPlayerOwns[47] = 442; // STREET KID
	SkinIDThatsPlayerOwns[48] = 443; // STREET ARTIST
	SkinIDThatsPlayerOwns[49] = 444; // CHRISTMAS

	// KATE
	SkinIDThatsPlayerOwns[50] = 511; // BASIC
	SkinIDThatsPlayerOwns[51] = 521; // CARAMEL
	SkinIDThatsPlayerOwns[52] = 522; // ICE CREAM
	SkinIDThatsPlayerOwns[53] = 523; // MERMAID
	SkinIDThatsPlayerOwns[54] = 524; // RASPBERRY
	SkinIDThatsPlayerOwns[55] = 531; // FASHION MODEL
	SkinIDThatsPlayerOwns[56] = 534; // FASHION DESIGNER
	SkinIDThatsPlayerOwns[57] = 533; // BLEU DE FRANCE
	SkinIDThatsPlayerOwns[58] = 535; // LE ROGUE FRANCAIS 
	SkinIDThatsPlayerOwns[59] = 541; // ROCKET
	SkinIDThatsPlayerOwns[60] = 542; // GLIDER
	SkinIDThatsPlayerOwns[61] = 532; // GAMER GIRL
	SkinIDThatsPlayerOwns[62] = 543; // CHRISTMAS

	// BANSHEE
	SkinIDThatsPlayerOwns[63] = 611; // BASIC
	SkinIDThatsPlayerOwns[64] = 631; // NURSE

	// GRANNY
	// None Yet...

	// IMPOSTOR
	SkinIDThatsPlayerOwns[65] = 811; // BASIC
	SkinIDThatsPlayerOwns[66] = 841; // GENTLEMAN
	SkinIDThatsPlayerOwns[67] = 851; // PUPPET

	// AKASHA
	SkinIDThatsPlayerOwns[68] = 911; // BASIC
	SkinIDThatsPlayerOwns[69] = 941; // BLOOD MAIDEN

	// IGOR
	SkinIDThatsPlayerOwns[70] = 101100; // BASIC
	SkinIDThatsPlayerOwns[71] = 104100; // BEAR

	GameInstance->SkinIDThatsPlayerOwns = SkinIDThatsPlayerOwns;


	/////////////////////
	/// AVATARS 
	/////////////////////

	TArray<int32_t> ArrAvatarPlayerOwn;

	ArrAvatarPlayerOwn.AllocateInt32(31);

	ArrAvatarPlayerOwn[0] = 10001; // PIXEL PARTY
	ArrAvatarPlayerOwn[1] = 10002; // PARKOUR HERO
	ArrAvatarPlayerOwn[2] = 10003; // PONY ISLAND
	ArrAvatarPlayerOwn[3] = 10004; // BANSHEE
	ArrAvatarPlayerOwn[4] = 10005; // HALLOWEEN
	ArrAvatarPlayerOwn[5] = 10006; // KING OF THE HILL
	ArrAvatarPlayerOwn[6] = 10007; // MR. FISH
	ArrAvatarPlayerOwn[7] = 10008; // GRANNY
	ArrAvatarPlayerOwn[8] = 10009; // IMPOSTOR STREET ART
	ArrAvatarPlayerOwn[9] = 10010; // HIDDEN IN THE GRASS
	ArrAvatarPlayerOwn[10] = 10011; // LITTLE HAPPINESS
	ArrAvatarPlayerOwn[11] = 10012; // VEGGIE PROPS
	ArrAvatarPlayerOwn[12] = 10013; // SAY CHEESE
	ArrAvatarPlayerOwn[13] = 10014; // MABLE-CHAN
	ArrAvatarPlayerOwn[14] = 10015; // FROG SURPREMACY
	ArrAvatarPlayerOwn[15] = 10016; // GAME ON
	ArrAvatarPlayerOwn[16] = 10017; // DREAM CATCHER
	ArrAvatarPlayerOwn[17] = 10018; // GOLD RUSH
	ArrAvatarPlayerOwn[18] = 10019; // BANSHEE STREET ART
	ArrAvatarPlayerOwn[19] = 10020; // GRANNY STREET ART
	ArrAvatarPlayerOwn[20] = 10021; // RABBIT STREET ART
	ArrAvatarPlayerOwn[21] = 10022; // KEYMASTER
	ArrAvatarPlayerOwn[22] = 10023; // AKASHA POP ART
	ArrAvatarPlayerOwn[23] = 10024; // AKASHA STREET ART
	ArrAvatarPlayerOwn[24] = 10025; // BANSHEE POP ART
	ArrAvatarPlayerOwn[25] = 10026; // CHRIS COMIC STYLE
	ArrAvatarPlayerOwn[26] = 10027; // GRANNY POP ART
	ArrAvatarPlayerOwn[27] = 10028; // IGOR POP ART
	ArrAvatarPlayerOwn[28] = 10029; // IMPOSTOR POP ART
	ArrAvatarPlayerOwn[29] = 10030; // ISSAC COMIC STYLE
	ArrAvatarPlayerOwn[30] = 10031; // KATE COMIC STYLE
	ArrAvatarPlayerOwn[31] = 10032; // MABLE COMIC STYLE

	GameInstance->ArrAvatarPlayerOwn = ArrAvatarPlayerOwn;
	

	/////////////////////
	/// BANNERS 
	/////////////////////

	TArray<int32_t> ArrBannerPlayerOwn;

	ArrBannerPlayerOwn.AllocateInt32(31);

	ArrBannerPlayerOwn[0] = 11; // PIXEL PARTY
	ArrBannerPlayerOwn[1] = 12; // PARKOUR HERO
	ArrBannerPlayerOwn[2] = 13; // PONY ISLAND
	ArrBannerPlayerOwn[3] = 14; // BANSHEE
	ArrBannerPlayerOwn[4] = 15; // HALLOWEEN
	ArrBannerPlayerOwn[5] = 16; // KING OF THE HILL
	ArrBannerPlayerOwn[6] = 17; // MR. FISH
	ArrBannerPlayerOwn[7] = 18; // GRANNY
	ArrBannerPlayerOwn[8] = 19; // IMPOSTOR STREET ART
	ArrBannerPlayerOwn[9] = 20; // HIDDEN IN THE GRASS
	ArrBannerPlayerOwn[10] = 21; // LITTLE HAPPINESS
	ArrBannerPlayerOwn[11] = 22; // VEGGIE PROPS
	ArrBannerPlayerOwn[12] = 23; // SAY CHEESE
	ArrBannerPlayerOwn[13] = 24; // MABLE-CHAN
	ArrBannerPlayerOwn[14] = 25; // FROG SUPREMACY
	ArrBannerPlayerOwn[15] = 26; // GAME ON
	ArrBannerPlayerOwn[16] = 27; // DREAM CATCHER
	ArrBannerPlayerOwn[17] = 28; // GOLD RUSH
	ArrBannerPlayerOwn[18] = 29; // BANSHEE STREET ART
	ArrBannerPlayerOwn[19] = 30; // GRANNY STREET ART
	ArrBannerPlayerOwn[20] = 31; // RABBIT STREET ART
	ArrBannerPlayerOwn[21] = 32; // KEYMASTER
	ArrBannerPlayerOwn[22] = 33; // AKASHA POP ART
	ArrBannerPlayerOwn[23] = 34; // AKASHA STREET ART 
	ArrBannerPlayerOwn[24] = 35; // BANSHEE POP ART
	ArrBannerPlayerOwn[25] = 36; // CHRIS COMIC STYLE
	ArrBannerPlayerOwn[26] = 37; // GRANNY POP ART 
	ArrBannerPlayerOwn[27] = 38; // IGOR POP ART
	ArrBannerPlayerOwn[28] = 39; // IMPOSTOR POP ART
	ArrBannerPlayerOwn[29] = 40; // ISAAC COMIC STYLE
	ArrBannerPlayerOwn[30] = 41; // KATE COMIC STYLE
	ArrBannerPlayerOwn[31] = 42; // MABLE COMIC STYLE

	GameInstance->ArrBannerPlayerOwn = ArrBannerPlayerOwn;


	/////////////////////
	/// TAGS 
	/////////////////////

	TArray<int32_t> ArrTagsPlayerOwn;

	ArrTagsPlayerOwn.AllocateInt32(37);

	ArrTagsPlayerOwn[0] = 1000; // HIDE
	ArrTagsPlayerOwn[1] = 1001; // PROP GOD
	ArrTagsPlayerOwn[2] = 1002; // PROP KING 
	ArrTagsPlayerOwn[3] = 1003; // PROP QUEEN
	ArrTagsPlayerOwn[4] = 1004; // LEGENDARY PROP
	ArrTagsPlayerOwn[5] = 1005; // TOP PROP
	ArrTagsPlayerOwn[6] = 1006; // HOP PROP
	ArrTagsPlayerOwn[7] = 1007; // PROPHEAD
	ArrTagsPlayerOwn[8] = 1008; // PROP HUNTER
	ArrTagsPlayerOwn[9] = 1009; // PROP CRUSHER
	ArrTagsPlayerOwn[10] = 1010; // PROP PROPHET
	ArrTagsPlayerOwn[11] = 1011; // SLY PROP
	ArrTagsPlayerOwn[12] = 1012; // PROP TALES
	ArrTagsPlayerOwn[13] = 1013; // GAME OF PROPS
	ArrTagsPlayerOwn[14] = 1014; // MY LITTLE PROP
	ArrTagsPlayerOwn[15] = 1015; // PROPOPHOBIA
	ArrTagsPlayerOwn[16] = 1016; // SMELLS LIKE PROP SPIRIT
	ArrTagsPlayerOwn[17] = 1017; // SILENCE OF THE PROPS
	ArrTagsPlayerOwn[18] = 1018; // PROP N ROLL
	ArrTagsPlayerOwn[19] = 1019; // LORD OF THE PROPS
	ArrTagsPlayerOwn[20] = 1020; // HAIL TO THE KING
	ArrTagsPlayerOwn[21] = 1021; // HAIL TO THE QUEEN
	ArrTagsPlayerOwn[22] = 1022; // FART AND FURIOUS
	ArrTagsPlayerOwn[23] = 1023; // CATCH ME IF YOU CAN
	ArrTagsPlayerOwn[24] = 1024; // HIDE AND SEEK MASTER
	ArrTagsPlayerOwn[25] = 1025; // PARKOUR MASTER
	ArrTagsPlayerOwn[26] = 1026; // MIND GAMER
	ArrTagsPlayerOwn[27] = 1027; // UNTOUCHABLE
	ArrTagsPlayerOwn[28] = 1028; // TRICK OR TREAT
	ArrTagsPlayerOwn[29] = 1029; // SEARCH AND DESTROY
	ArrTagsPlayerOwn[30] = 1030; // RIP AND TEAR
	ArrTagsPlayerOwn[31] = 1031; // SUPERSTAR
	ArrTagsPlayerOwn[32] = 1032; // VETERAN
	ArrTagsPlayerOwn[33] = 1033; // YOUR MOM
	ArrTagsPlayerOwn[34] = 1034; // WANTED
	ArrTagsPlayerOwn[35] = 1035; // POTATO
	ArrTagsPlayerOwn[36] = 1036; // GIT GUD
	ArrTagsPlayerOwn[37] = 1037; // FREE HUGS
	
	GameInstance->ArrTagsPlayerOwn = ArrTagsPlayerOwn;

	return TRUE;
}
