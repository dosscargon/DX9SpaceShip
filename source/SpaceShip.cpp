#include "SpaceShip.h"

//回転スピード
const float SpaceShip::SPEED = 2;
const float SpaceShip::ANGLE_LIMIT = 30;

bool SpaceShip::Initialize() {
	return GameObject::Initialize("assets/spaceship.x");
}

void SpaceShip::Update(const Scene& scene) {
	//回転
	if (Input::GetKey(Keys::RIGHT_KEY)) {
		angle += D3DXToRadian(SPEED);
		if (angle >= ANGLE_LIMIT * std::acosf(-1) / 180) {
			angle = ANGLE_LIMIT * std::acosf(-1) / 180;
		}
	} else if (Input::GetKey(Keys::LEFT_KEY)) {
		angle += D3DXToRadian(-SPEED);
		if (angle <= -ANGLE_LIMIT * std::acosf(-1) / 180) {
			angle = -ANGLE_LIMIT * std::acosf(-1) / 180;
		}
	}


	D3DXMatrixRotationY(&worldMatrix, angle);
}

//方向取得
float SpaceShip::GetAngle() {
	return angle;
}
