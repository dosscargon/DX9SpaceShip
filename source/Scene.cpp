#include "Scene.h"

//描画
void Scene::Render() {
	//プロジェクション・ビュー座標設定
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_VIEW, &viewMatrix);
	DirectX::GetDirect3DDevice().SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	//オブジェクトごとの描画
	for (auto& gameObject : gameObjects) {
		gameObject->Render();
	}
}
