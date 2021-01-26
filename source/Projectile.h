#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"

class Projectile : public GameObject {
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//��������
	void SetAngle(float angle);
private:
	//�i�񂾋���
	float distance = 0.0f;
	//����
	float angle = 0.0f;

	//�X�s�[�h
	static const float SPEED;
	//�����鋗��
	static const float DISTANCE_LIMIT;
};