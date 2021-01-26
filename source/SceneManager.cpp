#include "SceneManager.h"
#include "GameScene.h"
#include <windows.h>

unique_ptr<Scene> SceneManager::CurrentScene;

//シーンを変更する
void SceneManager::ChangeScene(Scene* scene) {
	CurrentScene.reset(scene);
	CurrentScene->Initialize();
}

//シーン取得
Scene& SceneManager::GetScene() {
	return *CurrentScene;
}