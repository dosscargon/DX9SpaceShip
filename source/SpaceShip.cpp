#include "SpaceShip.h"

//��]�X�s�[�h
const float SpaceShip::SPEED = 2;

bool SpaceShip::Initialize() {
	return GameObject::Initialize("assets/spaceship.x");
}

void SpaceShip::Update(const Scene& scene) {
	//��]
	if (Input::GetKey(Keys::RIGHT_KEY)) {
		angle += D3DXToRadian(SPEED);
	} else if (Input::GetKey(Keys::LEFT_KEY)) {
		angle += D3DXToRadian(-SPEED);
	}

	D3DXMatrixRotationY(&worldMatrix, angle);
}

//�����擾
float SpaceShip::GetAngle() {
	return angle;
}
