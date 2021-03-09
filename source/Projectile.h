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
	Projectile();

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

	//xファイルパス
	static constexpr char XFILE_PATH[] = "assets/tama.x";
	//スピード
	static constexpr float SPEED = 1.0f;
	//消える距離
	static constexpr float DISTANCE_LIMIT = 120.0f;
	//隕石のあたり判定
	static constexpr float METEOR_HIT_DISTANCE = 1.5f;

	float calculateDistance(D3DVECTOR a, D3DVECTOR b);
};