#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"
#include "Element.h"
#include "RESULT.h"
#include"ITEMBALL.h"
class GAMEMAIN :
    public AbstractScene
{
private:
	int background_image[5];
	int time;		//経過時間

	//レモナーの数用の変数
	int lemoner_count;

	//とまとんの数用の変数
	int tomaton_count;

	//グレポンの数用の変数
	int gurepon_count;

	//アイテムの数用変数
	int item_count;

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	LEMON** lemoner;	//レモナー
	GRAPEFRUIT** gurepon;	//グレぽん
	TOMATO** tomaton;	//とまトン
	ITEMBALL** item;     //アイテム
	ELEMENT* element;	//ステージ内要素
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

