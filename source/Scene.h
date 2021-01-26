#pragma once
#include<forward_list>
#include<memory>

#include "DirectX.h"
#include "GameObject.h"

using std::forward_list;
using std::shared_ptr;

class Scene {
public:
	//������
	virtual bool Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Render();

protected:
	D3DXMATRIX viewMatrix;//�r���[���W
	D3DXMATRIX projectionMatrix;//�v���W�F�N�V�������W

	forward_list<shared_ptr<GameObject>> gameObjects;//�I�u�W�F�N�g���X�g
};