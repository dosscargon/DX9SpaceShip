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
	//方向決定
	void SetAngle(float angle);

	//隕石との衝突判定
	bool GetHitMeteor(forward_list<weak_ptr<Meteor>>& meteors);

	//座標を計算
	D3DVECTOR&& GetPosition();
private:
	//進んだ距離
	float distance = 0.0f;
	//方向
	float angle = 0.0f;

	//スピード
	static const float SPEED;
	//消える距離
	static const float DISTANCE_LIMIT;
	//隕石のあたり判定
	static const float METEOR_HIT_DISTANCE;

	float calculateDistance(D3DVECTOR a, D3DVECTOR b);
};