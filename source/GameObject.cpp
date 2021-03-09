#include "GameObject.h"
#include "Input.h"

GameObject::XFile GameObject::xFileDatas[(int)XFileID::ID_COUNT];

//xファイル読み込み
GameObject::XFile& GameObject::LoadXFile(const char* filePath) {
	XFile newXFileData;

	if (FAILED(D3DXLoadMeshFromXA(
		filePath,
		D3DXMESH_SYSTEMMEM,
		&DirectX::GetDirect3DDevice(),
		nullptr,
		&newXFileData.Materials,
		nullptr,
		&newXFileData.MaterialNum,
		&newXFileData.Meshes
	))) {
		return newXFileData;
	};

	return newXFileData;
}

//各xファイルの読み込みをする
void GameObject::Initialize() {
	for (int i = 0; i < (int)XFileID::ID_COUNT; ++i) {
		xFileDatas[i] = LoadXFile(FILE_PATH[i]);
	}
}

//終了処理
void GameObject::Finalize() {
	for (auto& data : xFileDatas) {
		if (data.Materials != NULL) {
			data.Materials->Release();
			data.Materials=NULL;
		}
		if (data.Meshes != NULL) {
			data.Meshes->Release();
			data.Meshes = NULL;
		}
	}
}

//描画
void GameObject::Render() {
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_WORLD, &worldMatrix);

	D3DXMATERIAL* materials = (D3DXMATERIAL*)xFileDatas[(int)xfileID].Materials->GetBufferPointer();
	for (DWORD i = 0; i < xFileDatas[(int)xfileID].MaterialNum; i++) {
		//マテリアル設定
		DirectX::GetDirect3DDevice().SetMaterial(&materials[i].MatD3D);
		//描画
		xFileDatas[(int)xfileID].Meshes->DrawSubset(i);
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
