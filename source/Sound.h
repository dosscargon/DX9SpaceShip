#pragma once
#include<dsound.h>
#include "DirectX.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound {
public:
	//������
	static bool Initialize(HWND hwnd);
	//�I������
	static void Finalize();
	//wav�t�@�C���ǂݍ���
	static bool LoadWave();
	//�Đ�
	static void Play();
private:
	//wav�t�@�C���̃f�[�^���ꂱ��
	struct WaveData {
		WAVEFORMATEX WavFormat;
		char* SoundBuffer;
		DWORD Size;
	};
	static WaveData waveData;

	//�C���^�[�t�F�[�X
	static LPDIRECTSOUND8 directSound;
	//�Z�J���_���o�b�t�@
	static LPDIRECTSOUNDBUFFER secondaryBuffer;

	//wav�t�@�C���̃p�X
	static const LPWSTR FILE_PATH;
};

