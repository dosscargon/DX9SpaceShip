#pragma once
#include<forward_list>
#include<memory>

#include "Sound.h"
#include "Scene.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Meteor.h"

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
	//スペースシップの参照
	weak_ptr<SpaceShip> spaceShip;
	//弾参照リスト
	forward_list<weak_ptr<Projectile>> projectiles;
	//隕石参照リスト
	forward_list<weak_ptr<Meteor>> meteors;

};

