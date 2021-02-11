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
	ID_COUNT//�T�E���h�̎�ސ�
};

class Sound {
public:
	//������
	static bool Initialize(HWND hwnd);
	//�I������
	static void Finalize();
	//�Đ�
	static void Play(SoundID id);

	
private:
	//wav�t�@�C���̃f�[�^���ꂱ��
	struct WaveData {
		WAVEFORMATEX WavFormat;
		char* SoundBuffer;
		DWORD Size;
	};

	//wav�t�@�C���ǂݍ���
	static WaveData&& LoadWave(SoundID id);

	//�C���^�[�t�F�[�X
	static LPDIRECTSOUND8 directSound;
	//�Z�J���_���o�b�t�@
	static array<LPDIRECTSOUNDBUFFER, (size_t)SoundID::ID_COUNT> secondaryBuffer;

	//wav�t�@�C���̃p�X
	static constexpr array<LPWSTR, (size_t)SoundID::ID_COUNT> FILE_PATH = {
		(LPWSTR)L"assets/Thinking_Hero.wav" ,
		(LPWSTR)L"assets/pochi.wav" ,
		(LPWSTR)L"assets/hit.wav" ,
		(LPWSTR)L"assets/buun.wav"
	};
};

