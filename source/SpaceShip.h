#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include<cmath>

class SpaceShip : public GameObject{
public:
	virtual bool Initialize() override;
	virtual void Update(const Scene& scene) override;
	//•ûŒüæ“¾
	float GetAngle();
private:
	//•ûŒü
	float angle = 0.0f;

	//‰ñ“]ƒXƒs[ƒh
	static const float SPEED;
	//‰ñ“]ŒÀŠE
	static const float ANGLE_LIMIT;
};