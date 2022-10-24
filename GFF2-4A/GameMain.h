#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"
#include "Element.h"

class GAMEMAIN :
    public AbstractScene
{
private:

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	LEMON* lemonner;	//レモナー
	GRAPEFRUIT* gurepon;	//グレぽん
	TOMATO* tomaton;	//とまとん
	Element* element;	//ステージ内要素
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GAMEMAIN();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GAMEMAIN();
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

