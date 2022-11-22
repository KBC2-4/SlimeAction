#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"

class STAGE_SELECT :
    public AbstractScene
{
private:
	//背景画像
	int background_image[5];

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	ELEMENT* element;	//ステージ内要素

	float player_map_x, player_map_y;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	STAGE_SELECT();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~STAGE_SELECT();
	/// <summary>
	/// 描画以外の更新を実行
	/// </summary>
	/// <returns>シーンのアドレスを返す</returns>
	AbstractScene* Update() override;
	/// <summary>
	/// 描画に関することを実装
	/// </summary>
	void Draw() const override;
};

