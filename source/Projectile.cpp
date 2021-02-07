#include "Projectile.h"

using std::sin;
using std::cos;

//�X�s�[�h
const float Projectile::SPEED = 1.0f;
//�����鋗��
const float Projectile::DISTANCE_LIMIT = 120.0f;
//覐΂̂����蔻��
const float Projectile::METEOR_HIT_DISTANCE = 1.5f;

bool Projectile::Initialize() {
	return GameObject::Initialize("assets/tama.x");
}

void Projectile::Update(const Scene& scene) {
	//�i��
	distance += SPEED;

	//��������i�񂾂������
	if (distance >= DISTANCE_LIMIT) {
		DeleteThis();
		return;
	}

	//���[���h���W����
	D3DXMATRIX transMat, rotMat;
	D3DXMatrixTranslation(&transMat, distance * sin(angle), 0.0f, distance * cos(angle));
	D3DXMatrixRotationY(&rotMat, angle);

	D3DXMatrixMultiply(&worldMatrix, &rotMat, &transMat);
}

//��������
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

