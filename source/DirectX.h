#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <memory>

using std::unique_ptr;

class DirectX {
public:
	//�f�o�C�X�Ƃ����
	static bool Initialize(HWND hWnd, int width, int height, bool isFullscreen);
	//�I������
	static void Finalize(void);
	//DirectX�C���^�[�t�F�[�X
	static IDirect3D9& GetDirect3D(void);
	//DirectX�f�o�C�X
	static IDirect3DDevice9& GetDirect3DDevice(void);
private:
	//DirectX�C���^�[�t�F�[�X
	static LPDIRECT3D9 d3dInterface;
	//DirectX�f�o�C�X
	static LPDIRECT3DDEVICE9 d3dDevice;
};