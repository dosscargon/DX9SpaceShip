#include "DirectX.h"
#include "Window.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LPDIRECT3D9 DirectX::d3dInterface;
LPDIRECT3DDEVICE9 DirectX::d3dDevice;

//デバイスとか作る
bool DirectX::Initialize(HWND hWnd, int width, int height, bool isFullscreen) {
	if (d3dInterface != NULL || d3dDevice != NULL) return false;

	//インターフェース作成
	d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3dInterface == NULL) {
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	//デバイスの設定
	d3dpp.Windowed = !isFullscreen;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.Flags = 0;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//デバイス生成
	if (FAILED(d3dInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&d3dpp,
		&d3dDevice))) {
		d3dInterface = NULL;
		return false;
	}

	return true;
}

//終了処理
void DirectX::Finalize(void) {
	if (d3dDevice != NULL) {
		d3dDevice->Release();
		d3dDevice = NULL;
	}
	if (d3dInterface != NULL) {
		d3dInterface->Release();
		d3dInterface = NULL;
	}
}

//DirectXインターフェース
IDirect3D9& DirectX::GetDirect3D(void) { return *d3dInterface; }
//DirectXデバイス
IDirect3DDevice9& DirectX::GetDirect3DDevice(void) { return *d3dDevice; }