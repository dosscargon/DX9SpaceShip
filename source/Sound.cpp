#include "Sound.h"

LPDIRECTSOUND8 Sound::directSound;
LPDIRECTSOUNDBUFFER Sound::secondaryBuffer;
Sound::WaveData Sound::waveData;

const LPWSTR Sound::FILE_PATH = (LPWSTR)L"assets/pochi.wav";

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

	//wavファイル読み込み
	if (LoadWave() == false) {
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
	if (FAILED(directSound->CreateSoundBuffer(&desc, &secondaryBuffer, NULL))) {
		delete[] waveData.SoundBuffer;
		return false;
	}

	//波形データ書き込み
	void* buffer;
	DWORD buffer_size;
	if (FAILED(secondaryBuffer->Lock(0, waveData.Size, &buffer, &buffer_size, NULL, NULL, 0))) {
		delete[] waveData.SoundBuffer;
		return false;
	}
	memcpy(buffer, waveData.SoundBuffer, buffer_size);
	secondaryBuffer->Unlock(&buffer, buffer_size, NULL, NULL);

	delete[] waveData.SoundBuffer;

	return true;
}

void Sound::Finalize() {
	//セカンダリバッファの解放
	if (secondaryBuffer != NULL) {
		secondaryBuffer->Stop();
		secondaryBuffer->Release();
		secondaryBuffer = NULL;
	}

	//インターフェースの解放
	if (directSound != NULL) {
		directSound->Release();
		directSound = NULL;
	}
}

//wavファイル読み込み
bool Sound::LoadWave() {
	//APIのハンドル
	HMMIO mmioHandle = NULL;

	//チャンク情報
	MMCKINFO chunkInfo;
	//RIFFチャンク情報
	MMCKINFO riffChunkInfo;

	//サンプル数
	DWORD dwWavSize = 0;

	//ファイルを開く
	mmioHandle = mmioOpen(FILE_PATH, NULL, MMIO_READ);
	if (mmioHandle == NULL) {
		return false;
	}

	//RIFFチャンクに侵入
	riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &riffChunkInfo, NULL, MMIO_FINDRIFF)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmtデータの読み込み
	chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}
	LONG readSize = mmioRead(mmioHandle, (HPSTR)&waveData.WavFormat, sizeof(waveData.WavFormat));
	if (readSize != sizeof(waveData.WavFormat)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//フォーマットチェック
	if (waveData.WavFormat.wFormatTag != WAVE_FORMAT_PCM) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmtチャンクを退出
	if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//dataチャンクに進入
	chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}
	waveData.Size = chunkInfo.cksize;

	//データ読み込み
	waveData.SoundBuffer = new char[chunkInfo.cksize];
	readSize = mmioRead(mmioHandle, (HPSTR)waveData.SoundBuffer, chunkInfo.cksize);
	if (readSize != chunkInfo.cksize) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] waveData.SoundBuffer;
		return false;
	}

	// ファイルを閉じる
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return true;
}

//再生
void Sound::Play() {
  	if (secondaryBuffer == NULL) {
		return;
	}

	// 再生
	secondaryBuffer->SetCurrentPosition(0);
	secondaryBuffer->Play(0, 0, 0);
}

