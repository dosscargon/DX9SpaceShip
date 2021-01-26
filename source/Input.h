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
	KEY_COUNT //キーの種類数
};

class Input {
public:
	//デバイスとか取得
	static bool Initialize(HINSTANCE hInstance, HWND hWnd);
	//終了処理
	static void Finalize();
	//キー情報更新
	static void Update();
	//キーが押されてるか 
	static bool GetKey(Keys key);
	//キーが押されたか
	static bool GetKeyDown(Keys key);
	//キーが離されたか
	static bool GetKeyUp(Keys key);
private:
	//インプットインターフェース
	static LPDIRECTINPUT8 inputInterface;
	//キーデバイス
	static LPDIRECTINPUTDEVICE8 keyDevice;

	//現在のキーデータ
	static array<bool, (size_t)Keys::KEY_COUNT> keyDataNow;
	//1F前のキーデータ
	static array<bool, (size_t)Keys::KEY_COUNT> keyDataOld;
};