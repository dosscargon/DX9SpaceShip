#pragma once
#include<cmath>
#include<random>
#include "GameObject.h"
#include "SpaceShip.h"
#include "Scene.h"
#include "Input.h"
#include "Sound.h"

using std::sin;
using std::cos;
using std::random_device;

class Meteor : public GameObject {
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//��������
	void SetAngle(float angle);

	//���W���v�Z
	D3DVECTOR&& GetPosition();

	bool GetHitSpaceShip(SpaceShip& spaceship);

private:
	//�i�񂾋���
	float distance = INITIAL_DISTANCE;
	//����
	float angle;

	//�X�s�[�h
	static const float SPEED;
	//�����鋗��
	static const float INITIAL_DISTANCE;
	//�X�y�[�X�V�b�v�ƂԂ��鋗��
	static const float HIT_DISTANCE;
};