#pragma once
#include<forward_list>
#include<memory>

#include "Sound.h"
#include "Scene.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Projectile.h"

using std::forward_list;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::move;

class GameScene : public Scene {
public:
	virtual bool Initialize() override;
	virtual void Update() override;
private:
	//�X�y�[�X�V�b�v�̎Q��
	weak_ptr<SpaceShip> spaceShip;
};

