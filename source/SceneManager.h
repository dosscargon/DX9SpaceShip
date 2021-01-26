#pragma once
#include<memory>
#include "Scene.h"

using std::unique_ptr;

class SceneManager {
public:
	//シーンを変更する
	static void ChangeScene(Scene* scene);
	//シーン取得
	static Scene& GetScene();
private:
	//現在のシーン
	static unique_ptr<Scene> CurrentScene;
};
