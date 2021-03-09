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
	Meteor();

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

	//x�t�@�C���p�X
	static constexpr char XFILE_PATH[] = "assets/meteor.x";
	//�X�s�[�h
	static constexpr float SPEED = 0.5f;
	//�����鋗��
	static constexpr float INITIAL_DISTANCE = 120.0f;
	//�X�y�[�X�V�b�v�ƂԂ��鋗��
	static constexpr float HIT_DISTANCE = 2.0f;
};