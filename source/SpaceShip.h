#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include<cmath>

class SpaceShip : public GameObject{
public:
	SpaceShip();
	virtual void Update(const Scene& scene) override;
	//方向取得
	float GetAngle();
private:
	//方向
	float angle = 0.0f;

	//xファイルパス
	static constexpr char XFILE_PATH[] = "assets/spaceship.x";
	//回転スピード
	static constexpr float SPEED=2;
	//回転限界
	static constexpr float ANGLE_LIMIT = 30;
};