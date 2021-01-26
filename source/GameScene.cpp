#include "GameScene.h"

bool GameScene::Initialize() {
	//ライティング設定
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

	//スペースシップ生成
	shared_ptr<SpaceShip> ptr=make_shared<SpaceShip>();
	spaceShip = ptr;
	gameObjects.push_front(move(ptr));

	//オブジェクト初期化
	for (auto& gameobject : gameObjects) {
		gameobject->Initialize();
	}

	return true;
}

void GameScene::Update() {
	//プロジェクション座標
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix,
		D3DXToRadian(45.0f),
		640.0f / 480.0f,
		0.01f,
		1000.0f
	);

	//ビュー座標
	D3DXVECTOR3 cameraPos(0.0f, 10.0f, -15.0f);
	D3DXVECTOR3 targetPos(0.0f, 0.0f, 10.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPos, &targetPos, &upVec);

	//キーを押されたら弾生成
	if (Input::GetKeyDown(Keys::SHOOT_KEY)) {
		shared_ptr<Projectile> ptr = make_shared<Projectile>();
		ptr->Initialize();
		ptr->SetAngle(spaceShip.lock()->GetAngle());
		gameObjects.push_front(move(ptr));

		Sound::Play();
	}

	//オブジェクト更新
	for (auto& gameObject : gameObjects) {
		gameObject->Update(*this);
	}

	//削除すべきオブジェクトを削除
	gameObjects.remove_if([](auto& x) {return x->GetDelete(); });
}
