#pragma once

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline T& operator[](int i)
	{
		return Data[i];
	};

	void Allocate(INT NumOfElements)
	{
		NumOfElements += 1;

		Data = (int32_t*)malloc(sizeof(T) * NumOfElements); 
		/*
		   This isnt freed nor do I care (neither will UE4). 
		   So just relaunch game after your done so it gets freed automatically. This unlocker is persistent so relaunch is ok.
		*/
		Count = NumOfElements;
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

// Class Engine.GameInstance
struct UGameInstance {
	char pad_0000[0x38];
	TArray<struct UPlayer*> LocalPlayers;
	char pad_0001[0x5C0];
	TArray<int32_t> SkinIDThatsPlayerOwns;

};

// Class Engine.GameViewportClient
struct UGameViewportClient {
	char pad_0000[0x80];
	struct UGameInstance* GameInstance;
};

// Class Engine.Player
struct UPlayer {
	char pad_0000[0x70];
	struct UGameViewportClient* ViewportClient;
};

// Class Engine.World 
struct UWorld {
	char pad_0000[0x180];
	struct UGameInstance* OwningGameInstance;
};
