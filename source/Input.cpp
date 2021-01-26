#include "Input.h"

LPDIRECTINPUT8 Input::inputInterface;
LPDIRECTINPUTDEVICE8 Input::keyDevice;

array<bool, (size_t)Keys::KEY_COUNT> Input::keyDataNow;
array<bool, (size_t)Keys::KEY_COUNT> Input::keyDataOld;

//�f�o�C�X�Ƃ��擾
bool Input::Initialize(HINSTANCE instance_handle, HWND hwnd) {
	//�C���^�[�t�F�[�X�̎擾
	if (FAILED(DirectInput8Create(instance_handle,
			   DIRECTINPUT_VERSION,
			   IID_IDirectInput8,
			   (void**)(&inputInterface),
			   NULL))) {
		return false;
	}

	//�f�o�C�X�̎擾
	if (FAILED(inputInterface->CreateDevice(GUID_SysKeyboard, &keyDevice, NULL))) {
		return false;
	}

	//�L�[�{�[�h���g�p���邱�Ƃ�`����
	if (FAILED(keyDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return false;
	}

	//���̃A�v���P�[�V�����Ƃ̌��ˍ���
	if (FAILED(keyDevice->SetCooperativeLevel(
		hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		return false;
	}

	//���͂̎擾�J�n
	keyDevice->Acquire();

	return true;
}

//�I������
void Input::Finalize() {
	keyDevice->Unacquire();
	keyDevice->Release();
	inputInterface->Release();
}

//�L�[���X�V
void Input::Update() {
	// �L�[����i�[�p
	BYTE KeyState[256];

	if (SUCCEEDED(keyDevice->GetDeviceState(256, KeyState))) {
		keyDataOld = keyDataNow;
		keyDataNow = {  };

		// ���L�[
		if (KeyState[DIK_LEFT] & 0x80) {
			keyDataNow[(int)Keys::LEFT_KEY] = true;
		}

		// �E�L�[
		if (KeyState[DIK_RIGHT] & 0x80) {
			keyDataNow[(int)Keys::RIGHT_KEY] = true;
		}

		// ���˃L�[
		if (KeyState[DIK_SPACE] & 0x80) {
			keyDataNow[(int)Keys::SHOOT_KEY] = true;
		}
	} else {
		//���s������擾���Ȃ���
		keyDevice->Acquire();
	}
}

//�L�[��������Ă邩
bool Input::GetKey(Keys key) {
	return keyDataNow[(int)key];
}
//�L�[�������ꂽ��
bool Input::GetKeyDown(Keys key) {
	return keyDataNow[(int)key] && !keyDataOld[(int)key];
}
//�L�[�������ꂽ��
bool Input::GetKeyUp(Keys key) {
	return !keyDataNow[(int)key] && keyDataOld[(int)key];
}
