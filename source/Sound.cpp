#include "Sound.h"

LPDIRECTSOUND8 Sound::directSound;
LPDIRECTSOUNDBUFFER Sound::secondaryBuffer;
Sound::WaveData Sound::waveData;

const LPWSTR Sound::FILE_PATH = (LPWSTR)L"assets/pochi.wav";

//������
bool Sound::Initialize(HWND hwnd) {
	//�C���^�[�t�F�[�X�̐���
	if (FAILED(DirectSoundCreate8(NULL, &directSound, NULL))) {
		return false;
	}
	//�������x���̐ݒ�
	if (FAILED(directSound->SetCooperativeLevel(hwnd, DSSCL_NORMAL))) {
		return false;
	}

	//wav�t�@�C���ǂݍ���
	if (LoadWave() == false) {
		return false;
	}

	// �o�b�t�@���̐ݒ�
	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = waveData.Size;
	desc.guid3DAlgorithm = DS3DALG_DEFAULT;
	desc.lpwfxFormat = &waveData.WavFormat;

	//�Z�J���_���o�b�t�@�쐬
	if (FAILED(directSound->CreateSoundBuffer(&desc, &secondaryBuffer, NULL))) {
		delete[] waveData.SoundBuffer;
		return false;
	}

	//�g�`�f�[�^��������
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
	//�Z�J���_���o�b�t�@�̉��
	if (secondaryBuffer != NULL) {
		secondaryBuffer->Stop();
		secondaryBuffer->Release();
		secondaryBuffer = NULL;
	}

	//�C���^�[�t�F�[�X�̉��
	if (directSound != NULL) {
		directSound->Release();
		directSound = NULL;
	}
}

//wav�t�@�C���ǂݍ���
bool Sound::LoadWave() {
	//API�̃n���h��
	HMMIO mmioHandle = NULL;

	//�`�����N���
	MMCKINFO chunkInfo;
	//RIFF�`�����N���
	MMCKINFO riffChunkInfo;

	//�T���v����
	DWORD dwWavSize = 0;

	//�t�@�C�����J��
	mmioHandle = mmioOpen(FILE_PATH, NULL, MMIO_READ);
	if (mmioHandle == NULL) {
		return false;
	}

	//RIFF�`�����N�ɐN��
	riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &riffChunkInfo, NULL, MMIO_FINDRIFF)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmt�f�[�^�̓ǂݍ���
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

	//�t�H�[�}�b�g�`�F�b�N
	if (waveData.WavFormat.wFormatTag != WAVE_FORMAT_PCM) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmt�`�����N��ޏo
	if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//data�`�����N�ɐi��
	chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}
	waveData.Size = chunkInfo.cksize;

	//�f�[�^�ǂݍ���
	waveData.SoundBuffer = new char[chunkInfo.cksize];
	readSize = mmioRead(mmioHandle, (HPSTR)waveData.SoundBuffer, chunkInfo.cksize);
	if (readSize != chunkInfo.cksize) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] waveData.SoundBuffer;
		return false;
	}

	// �t�@�C�������
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return true;
}

//�Đ�
void Sound::Play() {
  	if (secondaryBuffer == NULL) {
		return;
	}

	// �Đ�
	secondaryBuffer->SetCurrentPosition(0);
	secondaryBuffer->Play(0, 0, 0);
}

