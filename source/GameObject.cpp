#include "GameObject.h"
#include "Input.h"

//x�t�@�C���̓ǂݍ��݂Ƃ�������
//�h���N���X��Initialize()����Ă�
bool GameObject::Initialize(const char* filePath) {
	//x�t�@�C���ǂݍ���
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

	//�}�e���A���ǂݍ���
	D3DXMATERIAL* materials = (D3DXMATERIAL*)xfileData.Materials->GetBufferPointer();

	return true;
}

//�`��
void GameObject::Render() {
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_WORLD, &worldMatrix);

	D3DXMATERIAL* materials = (D3DXMATERIAL*)xfileData.Materials->GetBufferPointer();
	for (DWORD i = 0; i < xfileData.MaterialNum; i++) {
		//�}�e���A���ݒ�
		DirectX::GetDirect3DDevice().SetMaterial(&materials[i].MatD3D);
		//�`��
		xfileData.Meshes->DrawSubset(i);
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