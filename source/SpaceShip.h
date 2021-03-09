#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include<cmath>

class SpaceShip : public GameObject{
public:
	SpaceShip();
	virtual void Update(const Scene& scene) override;
	//�����擾
	float GetAngle();
private:
	//����
	float angle = 0.0f;

	//x�t�@�C���p�X
	static constexpr char XFILE_PATH[] = "assets/spaceship.x";
	//��]�X�s�[�h
	static constexpr float SPEED=2;
	//��]���E
	static constexpr float ANGLE_LIMIT = 30;
};