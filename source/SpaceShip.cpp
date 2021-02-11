#include "SpaceShip.h"
//
////��]�X�s�[�h
//constexpr float SpaceShip::SPEED = 2;
//constexpr float SpaceShip::ANGLE_LIMIT = 30;

bool SpaceShip::Initialize() {
	return GameObject::Initialize(XFILE_PATH);
}

void SpaceShip::Update(const Scene& scene) {
	//��]
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

//�����擾
float SpaceShip::GetAngle() {
	return angle;
}
