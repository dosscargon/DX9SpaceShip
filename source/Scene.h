#pragma once
#include<forward_list>
#include<memory>

#include "DirectX.h"
#include "GameObject.h"

using std::forward_list;
using std::shared_ptr;

class Scene {
public:
	//初期化
	virtual bool Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Render();

protected:
	D3DXMATRIX viewMatrix;//ビュー座標
	D3DXMATRIX projectionMatrix;//プロジェクション座標

	forward_list<shared_ptr<GameObject>> gameObjects;//オブジェクトリスト
};