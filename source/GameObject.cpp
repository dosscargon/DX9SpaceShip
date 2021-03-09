#include "GameObject.h"
#include "Input.h"

GameObject::XFile GameObject::xFileDatas[(int)XFileID::ID_COUNT];

//x�t�@�C���ǂݍ���
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

//�ex�t�@�C���̓ǂݍ��݂�����
void GameObject::Initialize() {
	for (int i = 0; i < (int)XFileID::ID_COUNT; ++i) {
		xFileDatas[i] = LoadXFile(FILE_PATH[i]);
	}
}

//�I������
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

//�`��
void GameObject::Render() {
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_WORLD, &worldMatrix);

	D3DXMATERIAL* materials = (D3DXMATERIAL*)xFileDatas[(int)xfileID].Materials->GetBufferPointer();
	for (DWORD i = 0; i < xFileDatas[(int)xfileID].MaterialNum; i++) {
		//�}�e���A���ݒ�
		DirectX::GetDirect3DDevice().SetMaterial(&materials[i].MatD3D);
		//�`��
		xFileDatas[(int)xfileID].Meshes->DrawSubset(i);
	}
}

//�������\�肩
bool GameObject::GetDelete() {
	return deleteFlag;
}

//�I�u�W�F�N�g�����̗\��
void GameObject::DeleteThis() {
	deleteFlag = true;
}
