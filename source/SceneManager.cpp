#include "SceneManager.h"
#include "GameScene.h"
#include <windows.h>

unique_ptr<Scene> SceneManager::CurrentScene;

//�V�[����ύX����
void SceneManager::ChangeScene(Scene* scene) {
	CurrentScene.reset(scene);
	CurrentScene->Initialize();
}

//�V�[���擾
Scene& SceneManager::GetScene() {
	return *CurrentScene;
}