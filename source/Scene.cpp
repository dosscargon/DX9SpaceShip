#include "Scene.h"

//�`��
void Scene::Render() {
	//�v���W�F�N�V�����E�r���[���W�ݒ�
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_VIEW, &viewMatrix);
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	//�I�u�W�F�N�g���Ƃ̕`��
	for (auto& gameObject : gameObjects) {
		gameObject->Render();
	}
}
