#include "GameScene.h"

bool GameScene::Initialize() {
	//���C�e�B���O�ݒ�
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9)); 
	light.Type = D3DLIGHT_DIRECTIONAL; 
	light.Direction = D3DXVECTOR3(0, -20, 10);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	DirectX::GetDirect3DDevice().SetLight(0, &light);
	DirectX::GetDirect3DDevice().LightEnable(0, true);
	DirectX::GetDirect3DDevice().SetRenderState(D3DRS_LIGHTING, true);
	DirectX::GetDirect3DDevice().LightEnable(0, true);

	DirectX::GetDirect3DDevice().SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�X�y�[�X�V�b�v����
	shared_ptr<SpaceShip> ptr=make_shared<SpaceShip>();
	spaceShip = ptr;
	gameObjects.push_front(move(ptr));

	//�I�u�W�F�N�g������
	for (auto& gameobject : gameObjects) {
		gameobject->Initialize();
	}

	return true;
}

void GameScene::Update() {
	//�v���W�F�N�V�������W
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix,
		D3DXToRadian(45.0f),
		640.0f / 480.0f,
		0.01f,
		1000.0f
	);

	//�r���[���W
	D3DXVECTOR3 cameraPos(0.0f, 10.0f, -15.0f);
	D3DXVECTOR3 targetPos(0.0f, 0.0f, 10.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPos, &targetPos, &upVec);

	//�L�[�������ꂽ��e����
	if (Input::GetKeyDown(Keys::SHOOT_KEY)) {
		shared_ptr<Projectile> ptr = make_shared<Projectile>();
		ptr->Initialize();
		ptr->SetAngle(spaceShip.lock()->GetAngle());
		gameObjects.push_front(move(ptr));

		Sound::Play();
	}

	//�I�u�W�F�N�g�X�V
	for (auto& gameObject : gameObjects) {
		gameObject->Update(*this);
	}

	//�폜���ׂ��I�u�W�F�N�g���폜
	gameObjects.remove_if([](auto& x) {return x->GetDelete(); });
}