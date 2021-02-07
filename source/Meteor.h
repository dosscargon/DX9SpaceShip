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
	//方向決定
	void SetAngle(float angle);

	//座標を計算
	D3DVECTOR&& GetPosition();

	bool GetHitSpaceShip(SpaceShip& spaceship);

private:
	//進んだ距離
	float distance = INITIAL_DISTANCE;
	//方向
	float angle;

	//スピード
	static const float SPEED;
	//消える距離
	static const float INITIAL_DISTANCE;
	//スペースシップとぶつかる距離
	static const float HIT_DISTANCE;
};