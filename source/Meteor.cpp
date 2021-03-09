#include "Meteor.h"

Meteor::Meteor() {
	random_device rand;
	angle = ((float)(rand() % 30) - 15.0f) * std::acosf(-1) / 180.0f;
	xfileID = XFileID::METEOR;
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
