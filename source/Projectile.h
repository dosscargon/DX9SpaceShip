#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"

class Projectile : public GameObject {
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//方向決定
	void SetAngle(float angle);
private:
	//進んだ距離
	float distance = 0.0f;
	//方向
	float angle = 0.0f;

	//スピード
	static const float SPEED;
	//消える距離
	static const float DISTANCE_LIMIT;
};