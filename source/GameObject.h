#pragma once

#include "DirectX.h"

//クラスのプロトタイプ宣言（循環参照回避）
class Scene;

class GameObject {
public:
	//初期化．派生クラスから呼び出してxファイルパスを指定させよう
	virtual bool Initialize() = 0;
	//更新
	virtual void Update(const Scene& scene) = 0;
	//描画
	void Render();
	//消される予定か
	bool GetDelete();
	//オブジェクト消去の予約
	void DeleteThis();

	~GameObject();
protected:
	//xファイルの読み込みとかをする
	//派生クラスのInitialize()から呼ぶ
	bool Initialize(const char* filePath);

	//ワールド座標
	D3DXMATRIX worldMatrix;

private:
	//xファイルのあれこれをまとめた構造体
	struct XFile {
		DWORD MaterialNum;
		LPD3DXMESH Meshes;
		LPD3DXBUFFER Materials;
	};
	XFile xfileData;

	//消される予定か
	bool deleteFlag;
};

