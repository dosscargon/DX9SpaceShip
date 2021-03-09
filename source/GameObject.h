#pragma once

#include "DirectX.h"

//クラスのプロトタイプ宣言（循環参照回避）
class Scene;

//xファイルのID
enum class XFileID {
	SPACE_SHIP,
	PROJECTILE,
	METEOR,
	ID_COUNT//種類数
};

class GameObject {
public:
	//各xファイルの読み込み
	static void Initialize();
	//終了処理
	static void Finalize();
	//更新
	virtual void Update(const Scene& scene) = 0;
	//描画
	void Render();
	//消される予定か
	bool GetDelete();
	//オブジェクト消去の予約
	void DeleteThis();
protected:
	//ワールド座標
	D3DXMATRIX worldMatrix;

	//xファイルパス
	static constexpr const char* FILE_PATH[] = {
		"assets/spaceship.x",
		"assets/tama.x",
		"assets/meteor.x"
	};

	//xファイルのあれこれをまとめた構造体
	struct XFile {
		DWORD MaterialNum = -1;
		LPD3DXMESH Meshes = NULL;
		LPD3DXBUFFER Materials = NULL;
	};
	//各xファイル
	static XFile xFileDatas[(int)XFileID::ID_COUNT];
	//使用するxファイルID
	XFileID xfileID;

private:
	//消される予定か
	bool deleteFlag = false;

	//xファイル読み込み
	static XFile& LoadXFile(const char* filePath);
};

