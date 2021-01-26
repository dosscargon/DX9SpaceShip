#pragma once
#include<dsound.h>
#include "DirectX.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound {
public:
	//初期化
	static bool Initialize(HWND hwnd);
	//終了処理
	static void Finalize();
	//wavファイル読み込み
	static bool LoadWave();
	//再生
	static void Play();
private:
	//wavファイルのデータあれこれ
	struct WaveData {
		WAVEFORMATEX WavFormat;
		char* SoundBuffer;
		DWORD Size;
	};
	static WaveData waveData;

	//インターフェース
	static LPDIRECTSOUND8 directSound;
	//セカンダリバッファ
	static LPDIRECTSOUNDBUFFER secondaryBuffer;

	//wavファイルのパス
	static const LPWSTR FILE_PATH;
};

