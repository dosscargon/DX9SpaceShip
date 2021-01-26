#include "GameObject.h"
#include "Input.h"

//xファイルの読み込みとかをする
//派生クラスのInitialize()から呼ぶ
bool GameObject::Initialize(const char* filePath) {
	//xファイル読み込み
	if (FAILED(D3DXLoadMeshFromXA(
		filePath,
		D3DXMESH_SYSTEMMEM,
		&DirectX::GetDirect3DDevice(),
		nullptr,
		&xfileData.Materials,
		nullptr,
		&xfileData.MaterialNum,
		&xfileData.Meshes
	))) {
		return false;
	}

	//マテリアル読み込み
	D3DXMATERIAL* materials = (D3DXMATERIAL*)xfileData.Materials->GetBufferPointer();

	return true;
}

//描画
void GameObject::Render() {
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_WORLD, &worldMatrix);

	D3DXMATERIAL* materials = (D3DXMATERIAL*)xfileData.Materials->GetBufferPointer();
	for (DWORD i = 0; i < xfileData.MaterialNum; i++) {
		//マテリアル設定
		DirectX::GetDirect3DDevice().SetMaterial(&materials[i].MatD3D);
		//描画
		xfileData.Meshes->DrawSubset(i);
	}
}

//消される予定か
bool GameObject::GetDelete() {
	return deleteFlag;
}

//オブジェクト消去の予約
void GameObject::DeleteThis() {
	deleteFlag = true;
}

GameObject::~GameObject() {
	if (xfileData.Materials != NULL) {
		xfileData.Materials->Release();
		xfileData.Materials = NULL;
	}
	if (xfileData.Meshes != NULL) {
		xfileData.Meshes->Release();
		xfileData.Meshes = NULL;
	}
}