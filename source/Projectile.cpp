#include "Projectile.h"
//�X�s�[�h
const float Projectile::SPEED = 1.0f;
//�����鋗��
const float Projectile::DISTANCE_LIMIT = 120.0f;

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
	D3DXMATRIX trans, rot;
	D3DXMatrixRotationY(&rot, angle);
	D3DXMatrixTranslation(&trans, 0.0f, 0.0f, distance);

	D3DXMatrixMultiply(&worldMatrix, &trans, &rot);
}

//��������
void Projectile::SetAngle(float angle) {
	this->angle = angle;
}
