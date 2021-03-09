#include "Sound.h"

LPDIRECTSOUND8 Sound::directSound;
LPDIRECTSOUNDBUFFER Sound::secondaryBuffer[(int)SoundID::ID_COUNT];

//初期化
bool Sound::Initialize(HWND hwnd) {
	//インターフェースの生成
	if (FAILED(DirectSoundCreate8(NULL, &directSound, NULL))) {
		return false;
	}
	//協調レベルの設定
	if (FAILED(directSound->SetCooperativeLevel(hwnd, DSSCL_NORMAL))) {
		return false;
	}

	for (int i = 0; i < (int)SoundID::ID_COUNT; ++i) {
		WaveData waveData = LoadWave((SoundID)i);
		//wavファイル読み込み
		if (waveData.SoundBuffer == NULL) {
			return false;
		}

		// バッファ情報の設定
		DSBUFFERDESC desc;
		ZeroMemory(&desc, sizeof(DSBUFFERDESC));
		desc.dwSize = sizeof(DSBUFFERDESC);
		desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
		desc.dwBufferBytes = waveData.Size;
		desc.guid3DAlgorithm = DS3DALG_DEFAULT;
		desc.lpwfxFormat = &waveData.WavFormat;

		//セカンダリバッファ作成
		if (FAILED(directSound->CreateSoundBuffer(&desc, &secondaryBuffer[i], NULL))) {
			delete[] waveData.SoundBuffer;
			return false;
		}

		//波形データ書き込み
		void* buffer;
		DWORD buffer_size;
		if (FAILED(secondaryBuffer[i]->Lock(0, waveData.Size, &buffer, &buffer_size, NULL, NULL, 0))) {
			delete[] waveData.SoundBuffer;
			return false;
		}
		memcpy(buffer, waveData.SoundBuffer, buffer_size);
		secondaryBuffer[i]->Unlock(&buffer, buffer_size, NULL, NULL);

		delete[] waveData.SoundBuffer;
	}

	return true;
}

void Sound::Finalize() {
	//セカンダリバッファの解放
	for (auto buffer : secondaryBuffer) {
		if (buffer != NULL) {
			buffer->Stop();
			buffer->Release();
			buffer = NULL;
		}
	}

	//インターフェースの解放
	if (directSound != NULL) {
		directSound->Release();
		directSound = NULL;
	}
}

//wavファイル読み込み
Sound::WaveData&& Sound::LoadWave(SoundID id) {
	WaveData waveData;

	//APIのハンドル
	HMMIO mmioHandle = NULL;

	//チャンク情報
	MMCKINFO chunkInfo;
	//RIFFチャンク情報
	MMCKINFO riffChunkInfo;

	//サンプル数
	DWORD dwWavSize = 0;

	//ファイルを開く
	mmioHandle = mmioOpen(FILE_PATH[(int)id], NULL, MMIO_READ);
	if (mmioHandle == NULL) {
		return WaveData{};
	}

	//RIFFチャンクに侵入
	riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &riffChunkInfo, NULL, MMIO_FINDRIFF)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//fmtデータの読み込み
	chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}
	LONG readSize = mmioRead(mmioHandle, (HPSTR)&waveData.WavFormat, sizeof(waveData.WavFormat));
	if (readSize != sizeof(waveData.WavFormat)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//フォーマットチェック
	if (waveData.WavFormat.wFormatTag != WAVE_FORMAT_PCM) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//fmtチャンクを退出
	if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//dataチャンクに進入
	chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}
	waveData.Size = chunkInfo.cksize;

	//データ読み込み
	waveData.SoundBuffer = new char[chunkInfo.cksize];
	readSize = mmioRead(mmioHandle, (HPSTR)waveData.SoundBuffer, chunkInfo.cksize);
	if (readSize != chunkInfo.cksize) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] waveData.SoundBuffer;
		return WaveData{};
	}

	// ファイルを閉じる
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return move(waveData);
}

//再生
void Sound::Play(SoundID id) {
  	if (secondaryBuffer[(int)id] == NULL) {
		return;
	}

	// 再生
	secondaryBuffer[(int)id]->SetCurrentPosition(0);
	secondaryBuffer[(int)id]->Play(0, 0, 0);
}

