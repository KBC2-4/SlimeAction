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
	//背景画像
	int background_image[3];
	int background_music[3];		//BGM
	int start_time_font, time_font;	//フォント
	int cursor_move_se, ok_se, count_se, start_se, clear_se;	//SE
	int start_time;		//開始までの遅延時間
	int start_effect_timer;
	int start_addtime;
	int elapsed_time;	//経過時間
	const char* stage_name;	//リスタート時のステージ選択用
	int now_graph;		//リスタート時の今現在の画面
	int clear_interval;	//クリア時の画面推移までの時間

	//プレイヤーのライフの画像
	int hp_img;

	//レモナーの数用の変数
	int lemoner_count;

	//とまとんの数用の変数
	int tomaton_count;

	//グレポンの数用の変数
	int gurepon_count;

	//アイテムの数用変数
	int item_count;
	int item_num;
	int item_rand;

	bool restart;	//復活フラグ

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	PAUSE* pause;	//ポーズ
	LEMON** lemoner;	//レモナー
	GRAPEFRUIT** gurepon;	//グレぽん
	TOMATO** tomaton;	//とまトン
	ITEMBALL** item;     //アイテム
	ELEMENT* element;	//ステージ内要素


	//PV制作用（完成次第即座に消去）
	int input_margin;
	int scroll_speed;
	bool player_visible;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GAMEMAIN(bool restart = false, int halfway_time = 0, const char* stage_name = "StageSelect");
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

