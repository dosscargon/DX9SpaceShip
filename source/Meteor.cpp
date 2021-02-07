#include "Meteor.h"

//スピード
const float Meteor::SPEED = 0.5f;
//出現位置
const float Meteor::INITIAL_DISTANCE = 120.0f;
//スペースシップとぶつかる距離
const float Meteor::HIT_DISTANCE = 2.0f;

bool Meteor::Initialize() {
	random_device rand;
	angle = ((float)(rand() % 30) - 15.0f) * std::acosf(-1) / 180.0f;
	return GameObject::Initialize("assets/meteor.x");
}

void Meteor::Update(const Scene& scene) {
	//進む
	distance -= SPEED;

	//ワールド座標生成
	D3DXMATRIX transMat, rotMat;
	D3DXMatrixTranslation(&transMat, distance * sin(angle), 0.0f, distance * cos(angle));
	D3DXMatrixRotationY(&rotMat, angle);

	D3DXMatrixMultiply(&worldMatrix, &rotMat, &transMat);
}

//方向決定
void Meteor::SetAngle(float angle) {
	this->angle = angle;
}

D3DVECTOR&& Meteor::GetPosition() {
	return D3DVECTOR{ distance * sin(angle), 0.0f, distance * cos(angle) };
}

bool Meteor::GetHitSpaceShip(SpaceShip& spaceship) {
	if (distance < HIT_DISTANCE) {
		DeleteThis();
		spaceship.DeleteThis();

		Sound::Play(SoundID::DAMAGE);

		return true;
	}
	return false;
}
