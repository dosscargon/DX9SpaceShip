#pragma once
#include<memory>
#include "Scene.h"

using std::unique_ptr;

class SceneManager {
public:
	//�V�[����ύX����
	static void ChangeScene(Scene* scene);
	//�V�[���擾
	static Scene& GetScene();
private:
	//���݂̃V�[��
	static unique_ptr<Scene> CurrentScene;
};
