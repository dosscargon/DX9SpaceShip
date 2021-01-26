#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <memory>

using std::unique_ptr;

class DirectX {
public:
	//デバイスとか作る
	static bool Initialize(HWND hWnd, int width, int height, bool isFullscreen);
	//終了処理
	static void Finalize(void);
	//DirectXインターフェース
	static IDirect3D9& GetDirect3D(void);
	//DirectXデバイス
	static IDirect3DDevice9& GetDirect3DDevice(void);
private:
	//DirectXインターフェース
	static LPDIRECT3D9 d3dInterface;
	//DirectXデバイス
	static LPDIRECT3DDEVICE9 d3dDevice;
};