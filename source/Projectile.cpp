#include "Projectile.h"

using std::sin;
using std::cos;

Projectile::Projectile() {
	xfileID = XFileID::PROJECTILE;
}

void Projectile::Update(const Scene& scene) {
	//進む
	distance += SPEED;

	//たくさん進んだら消える
	if (distance >= DISTANCE_LIMIT) {
		DeleteThis();
		return;
	}

	//ワールド座標生成
	D3DXMATRIX transMat, rotMat;
	D3DXMatrixTranslation(&transMat, distance * sin(angle), 0.0f, distance * cos(angle));
	D3DXMatrixRotationY(&rotMat, angle);

	D3DXMatrixMultiply(&worldMatrix, &rotMat, &transMat);
}

//方向決定
void Projectile::SetAngle(float angle) {
	this->angle = angle;
}

bool Projectile::GetHitMeteor(forward_list<weak_ptr<Meteor>>& meteors) {
	for (auto& meteor : meteors) {
		if (calculateDistance(GetPosition(), meteor.lock()->GetPosition()) < 1.5f) {
 			meteor.lock()->DeleteThis();
			DeleteThis();

			Sound::Play(SoundID::HIT);

			return true;
		}
	}
	return false;
}

D3DVECTOR&& Projectile::GetPosition() {
	return D3DVECTOR{ distance * sin(angle), 0.0f, distance * cos(angle) };
}

float Projectile::calculateDistance(D3DVECTOR a, D3DVECTOR b) {
	return sqrtf(powf(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

