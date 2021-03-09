#pragma once

#include "DirectX.h"

//�N���X�̃v���g�^�C�v�錾�i�z�Q�Ɖ���j
class Scene;

//x�t�@�C����ID
enum class XFileID {
	SPACE_SHIP,
	PROJECTILE,
	METEOR,
	ID_COUNT//��ސ�
};

class GameObject {
public:
	//�ex�t�@�C���̓ǂݍ���
	static void Initialize();
	//�I������
	static void Finalize();
	//�X�V
	virtual void Update(const Scene& scene) = 0;
	//�`��
	void Render();
	//�������\�肩
	bool GetDelete();
	//�I�u�W�F�N�g�����̗\��
	void DeleteThis();
protected:
	//���[���h���W
	D3DXMATRIX worldMatrix;

	//x�t�@�C���p�X
	static constexpr const char* FILE_PATH[] = {
		"assets/spaceship.x",
		"assets/tama.x",
		"assets/meteor.x"
	};

	//x�t�@�C���̂��ꂱ����܂Ƃ߂��\����
	struct XFile {
		DWORD MaterialNum = -1;
		LPD3DXMESH Meshes = NULL;
		LPD3DXBUFFER Materials = NULL;
	};
	//�ex�t�@�C��
	static XFile xFileDatas[(int)XFileID::ID_COUNT];
	//�g�p����x�t�@�C��ID
	XFileID xfileID;

private:
	//�������\�肩
	bool deleteFlag = false;

	//x�t�@�C���ǂݍ���
	static XFile& LoadXFile(const char* filePath);
};

