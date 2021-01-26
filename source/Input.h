#pragma once
#include "DirectX.h"
#include <array>
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using std::array;

enum class Keys {
	SHOOT_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	KEY_COUNT //�L�[�̎�ސ�
};

class Input {
public:
	//�f�o�C�X�Ƃ��擾
	static bool Initialize(HINSTANCE hInstance, HWND hWnd);
	//�I������
	static void Finalize();
	//�L�[���X�V
	static void Update();
	//�L�[��������Ă邩 
	static bool GetKey(Keys key);
	//�L�[�������ꂽ��
	static bool GetKeyDown(Keys key);
	//�L�[�������ꂽ��
	static bool GetKeyUp(Keys key);
private:
	//�C���v�b�g�C���^�[�t�F�[�X
	static LPDIRECTINPUT8 inputInterface;
	//�L�[�f�o�C�X
	static LPDIRECTINPUTDEVICE8 keyDevice;

	//���݂̃L�[�f�[�^
	static array<bool, (size_t)Keys::KEY_COUNT> keyDataNow;
	//1F�O�̃L�[�f�[�^
	static array<bool, (size_t)Keys::KEY_COUNT> keyDataOld;
};