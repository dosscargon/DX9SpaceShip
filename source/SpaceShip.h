#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"

class SpaceShip : public GameObject{
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//�����擾
	float GetAngle();
private:
	//����
	float angle = 0.0f;

	//��]�X�s�[�h
	static const float SPEED;
};