#pragma once

#include "DirectX.h"

//�N���X�̃v���g�^�C�v�錾�i�z�Q�Ɖ���j
class Scene;

class GameObject {
public:
	//�������D�h���N���X����Ăяo����x�t�@�C���p�X���w�肳���悤
	virtual bool Initialize() = 0;
	//�X�V
	virtual void Update(const Scene& scene) = 0;
	//�`��
	void Render();
	//�������\�肩
	bool GetDelete();
	//�I�u�W�F�N�g�����̗\��
	void DeleteThis();

	~GameObject();
protected:
	//x�t�@�C���̓ǂݍ��݂Ƃ�������
	//�h���N���X��Initialize()����Ă�
	bool Initialize(const char* filePath);

	//���[���h���W
	D3DXMATRIX worldMatrix;

private:
	//x�t�@�C���̂��ꂱ����܂Ƃ߂��\����
	struct XFile {
		DWORD MaterialNum;
		LPD3DXMESH Meshes;
		LPD3DXBUFFER Materials;
	};
	XFile xfileData;

	//�������\�肩
	bool deleteFlag;
};

