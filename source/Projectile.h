#pragma once
#include<cmath>
#include "GameObject.h"
#include "Meteor.h"
#include "Scene.h"
#include "Input.h"
#include "Sound.h"

using std::weak_ptr;

class Projectile : public GameObject {
public:
	Projectile();

	virtual void Update(const Scene& scene) override;
	//��������
	void SetAngle(float angle);

	//覐΂Ƃ̏Փ˔���
	bool GetHitMeteor(forward_list<weak_ptr<Meteor>>& meteors);

	//���W���v�Z
	D3DVECTOR&& GetPosition();
private:
	//�i�񂾋���
	float distance = 0.0f;
	//����
	float angle = 0.0f;

	//x�t�@�C���p�X
	static constexpr char XFILE_PATH[] = "assets/tama.x";
	//�X�s�[�h
	static constexpr float SPEED = 1.0f;
	//�����鋗��
	static constexpr float DISTANCE_LIMIT = 120.0f;
	//覐΂̂����蔻��
	static constexpr float METEOR_HIT_DISTANCE = 1.5f;

	float calculateDistance(D3DVECTOR a, D3DVECTOR b);
};