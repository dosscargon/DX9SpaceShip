#include "Input.h"

LPDIRECTINPUT8 Input::inputInterface;
LPDIRECTINPUTDEVICE8 Input::keyDevice;

array<bool, (size_t)Keys::KEY_COUNT> Input::keyDataNow;
array<bool, (size_t)Keys::KEY_COUNT> Input::keyDataOld;

//デバイスとか取得
bool Input::Initialize(HINSTANCE instance_handle, HWND hwnd) {
	//インターフェースの取得
	if (FAILED(DirectInput8Create(instance_handle,
			   DIRECTINPUT_VERSION,
			   IID_IDirectInput8,
			   (void**)(&inputInterface),
			   NULL))) {
		return false;
	}

	//デバイスの取得
	if (FAILED(inputInterface->CreateDevice(GUID_SysKeyboard, &keyDevice, NULL))) {
		return false;
	}

	//キーボードを使用することを伝える
	if (FAILED(keyDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return false;
	}

	//他のアプリケーションとの兼ね合い
	if (FAILED(keyDevice->SetCooperativeLevel(
		hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		return false;
	}

	//入力の取得開始
	keyDevice->Acquire();

	return true;
}

//終了処理
void Input::Finalize() {
	keyDevice->Unacquire();
	keyDevice->Release();
	inputInterface->Release();
}

//キー情報更新
void Input::Update() {
	// キー情報取格納用
	BYTE KeyState[256];

	if (SUCCEEDED(keyDevice->GetDeviceState(256, KeyState))) {
		keyDataOld = keyDataNow;
		keyDataNow = {  };

		// 左キー
		if (KeyState[DIK_LEFT] & 0x80) {
			keyDataNow[(int)Keys::LEFT_KEY] = true;
		}

		// 右キー
		if (KeyState[DIK_RIGHT] & 0x80) {
			keyDataNow[(int)Keys::RIGHT_KEY] = true;
		}

		// 発射キー
		if (KeyState[DIK_SPACE] & 0x80) {
			keyDataNow[(int)Keys::SHOOT_KEY] = true;
		}
	} else {
		//失敗したら取得しなおす
		keyDevice->Acquire();
	}
}

//キーが押されてるか
bool Input::GetKey(Keys key) {
	return keyDataNow[(int)key];
}
//キーが押されたか
bool Input::GetKeyDown(Keys key) {
	return keyDataNow[(int)key] && !keyDataOld[(int)key];
}
//キーが離されたか
bool Input::GetKeyUp(Keys key) {
	return !keyDataNow[(int)key] && keyDataOld[(int)key];
}
