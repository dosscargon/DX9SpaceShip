#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include<cmath>

class SpaceShip : public GameObject{
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//方向取得
	float GetAngle();
private:
	//方向
	float angle = 0.0f;

	//回転スピード
	static const float SPEED;
	//回転限界
	static const float ANGLE_LIMIT;
};