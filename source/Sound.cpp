#include "Sound.h"

LPDIRECTSOUND8 Sound::directSound;
LPDIRECTSOUNDBUFFER Sound::secondaryBuffer[(int)SoundID::ID_COUNT];

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

	for (int i = 0; i < (int)SoundID::ID_COUNT; ++i) {
		WaveData waveData = LoadWave((SoundID)i);
		//wav�t�@�C���ǂݍ���
		if (waveData.SoundBuffer == NULL) {
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
		if (FAILED(directSound->CreateSoundBuffer(&desc, &secondaryBuffer[i], NULL))) {
			delete[] waveData.SoundBuffer;
			return false;
		}

		//�g�`�f�[�^��������
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
	//�Z�J���_���o�b�t�@�̉��
	for (auto buffer : secondaryBuffer) {
		if (buffer != NULL) {
			buffer->Stop();
			buffer->Release();
			buffer = NULL;
		}
	}

	//�C���^�[�t�F�[�X�̉��
	if (directSound != NULL) {
		directSound->Release();
		directSound = NULL;
	}
}

//wav�t�@�C���ǂݍ���
Sound::WaveData&& Sound::LoadWave(SoundID id) {
	WaveData waveData;

	//API�̃n���h��
	HMMIO mmioHandle = NULL;

	//�`�����N���
	MMCKINFO chunkInfo;
	//RIFF�`�����N���
	MMCKINFO riffChunkInfo;

	//�T���v����
	DWORD dwWavSize = 0;

	//�t�@�C�����J��
	mmioHandle = mmioOpen(FILE_PATH[(int)id], NULL, MMIO_READ);
	if (mmioHandle == NULL) {
		return WaveData{};
	}

	//RIFF�`�����N�ɐN��
	riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &riffChunkInfo, NULL, MMIO_FINDRIFF)) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//fmt�f�[�^�̓ǂݍ���
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

	//�t�H�[�}�b�g�`�F�b�N
	if (waveData.WavFormat.wFormatTag != WAVE_FORMAT_PCM) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//fmt�`�����N��ޏo
	if (mmioAscend(mmioHandle, &chunkInfo, 0) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}

	//data�`�����N�ɐi��
	chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return WaveData{};
	}
	waveData.Size = chunkInfo.cksize;

	//�f�[�^�ǂݍ���
	waveData.SoundBuffer = new char[chunkInfo.cksize];
	readSize = mmioRead(mmioHandle, (HPSTR)waveData.SoundBuffer, chunkInfo.cksize);
	if (readSize != chunkInfo.cksize) {
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] waveData.SoundBuffer;
		return WaveData{};
	}

	// �t�@�C�������
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return move(waveData);
}

//�Đ�
void Sound::Play(SoundID id) {
  	if (secondaryBuffer[(int)id] == NULL) {
		return;
	}

	// �Đ�
	secondaryBuffer[(int)id]->SetCurrentPosition(0);
	secondaryBuffer[(int)id]->Play(0, 0, 0);
}

