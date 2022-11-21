#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"
#include "Lemon.h"
#include "GrapeFruit.h"
#include "Tomato.h"
#include "Element.h"
#include "RESULT.h"
#include "PAUSE.h"
#include "ITEMBALL.h"
class GAMEMAIN :
    public AbstractScene
{
private:
	int background_image[5];
	int title_font, menu_font;	//フォント
	int cursor_move_se, ok_se;	//SE
	int time;		//経過時間
	int halfway_time; //中間地点経過時の時間

	//レモナーの数用の変数
	int lemoner_count;

	//とまとんの数用の変数
	int tomaton_count;

	//グレポンの数用の変数
	int gurepon_count;

	//アイテムの数用変数
	int item_count;
	int item_num;

	bool restart;	//復活フラグ

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	PAUSE* pause;	//ポーズ
	LEMON** lemoner;	//レモナー
	GRAPEFRUIT** gurepon;	//グレぽん
	TOMATO** tomaton;	//とまトン
	ITEMBALL** item;     //アイテム
	ELEMENT* element;	//ステージ内要素
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GAMEMAIN(bool restert = false, int halfway_time = 0);
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

