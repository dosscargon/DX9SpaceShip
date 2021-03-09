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

	//xファイルパス
	static constexpr char XFILE_PATH[] = "assets/meteor.x";
	//スピード
	static constexpr float SPEED = 0.5f;
	//消える距離
	static constexpr float INITIAL_DISTANCE = 120.0f;
	//スペースシップとぶつかる距離
	static constexpr float HIT_DISTANCE = 2.0f;
};