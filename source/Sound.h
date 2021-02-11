#pragma once
#include<dsound.h>
#include <array>
#include "DirectX.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

using std::move;
using std::array;

enum class SoundID {
	BGM,
	SHOOT,
	HIT,
	DAMAGE,
	ID_COUNT//サウンドの種類数
};

class Sound {
public:
	//初期化
	static bool Initialize(HWND hwnd);
	//終了処理
	static void Finalize();
	//再生
	static void Play(SoundID id);

	
private:
	//wavファイルのデータあれこれ
	struct WaveData {
		WAVEFORMATEX WavFormat;
		char* SoundBuffer;
		DWORD Size;
	};

	//wavファイル読み込み
	static WaveData&& LoadWave(SoundID id);

	//インターフェース
	static LPDIRECTSOUND8 directSound;
	//セカンダリバッファ
	static array<LPDIRECTSOUNDBUFFER, (size_t)SoundID::ID_COUNT> secondaryBuffer;

	//wavファイルのパス
	static constexpr array<LPWSTR, (size_t)SoundID::ID_COUNT> FILE_PATH = {
		(LPWSTR)L"assets/Thinking_Hero.wav" ,
		(LPWSTR)L"assets/pochi.wav" ,
		(LPWSTR)L"assets/hit.wav" ,
		(LPWSTR)L"assets/buun.wav"
	};
};

