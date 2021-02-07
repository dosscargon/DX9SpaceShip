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
	shared_ptr<SpaceShip> newSpaceShip=make_shared<SpaceShip>();
	spaceShip = newSpaceShip;
	gameObjects.push_front(move(newSpaceShip));

	//オブジェクト初期化
	for (auto& gameobject : gameObjects) {
		gameobject->Initialize();
	}

	Sound::Play(SoundID::BGM);

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

	if (!spaceShip.expired()) {
		//キーを押されたら弾生成
		if (Input::GetKeyDown(Keys::SHOOT_KEY)) {
			shared_ptr<Projectile> newProjectile = make_shared<Projectile>();
			newProjectile->Initialize();
			newProjectile->SetAngle(spaceShip.lock()->GetAngle());
			projectiles.push_front(newProjectile);
			gameObjects.push_front(move(newProjectile));

			Sound::Play(SoundID::SHOOT);
		}

		//一定時間ごとに隕石生成
		static int counter = 0;
		++counter;
		if (counter > 180) {
			shared_ptr<Meteor> newMeteor = make_shared<Meteor>();
			newMeteor->Initialize();
			meteors.push_front(newMeteor);
			gameObjects.push_front(move(newMeteor));
			counter = 0;
		}


		//オブジェクト更新
		for (auto& gameObject : gameObjects) {
			gameObject->Update(*this);
		}

		//衝突判定
		for (auto& projectile : projectiles) {
			projectile.lock()->GetHitMeteor(meteors);
		}
		for (auto& meteor : meteors) {
			meteor.lock()->GetHitSpaceShip(*spaceShip.lock());
		}
	}

	//削除すべきオブジェクトを削除
	gameObjects.remove_if([](auto& x) {return x->GetDelete(); });
	projectiles.remove_if([](auto& x) {return x.expired(); });
	meteors.remove_if([](auto& x) {return x.expired(); });
}
