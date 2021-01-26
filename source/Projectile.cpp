#include "Projectile.h"
//スピード
const float Projectile::SPEED = 1.0f;
//消える距離
const float Projectile::DISTANCE_LIMIT = 120.0f;

bool Projectile::Initialize() {
	return GameObject::Initialize("assets/tama.x");
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
	D3DXMATRIX trans, rot;
	D3DXMatrixRotationY(&rot, angle);
	D3DXMatrixTranslation(&trans, 0.0f, 0.0f, distance);

	D3DXMatrixMultiply(&worldMatrix, &trans, &rot);
}

//方向決定
void Projectile::SetAngle(float angle) {
	this->angle = angle;
}
