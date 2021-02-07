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
	virtual bool Initialize() override;
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

	//�X�s�[�h
	static const float SPEED;
	//�����鋗��
	static const float DISTANCE_LIMIT;
	//覐΂̂����蔻��
	static const float METEOR_HIT_DISTANCE;

	float calculateDistance(D3DVECTOR a, D3DVECTOR b);
};