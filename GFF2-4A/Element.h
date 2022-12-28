#pragma once
#include "STAGE.h"
#include <vector>

#define LIFT_SIZE 160

class PLAYER;
class STAGE;

class ELEMENT :
    public STAGE
{
public:
	struct ELEMENT_DATA
	{
		float x, y;
		int type;
		bool flg = false;
		int animtimer = 0;
		
		float lift_init_x, lift_init_y;		//動く床の初期座標
		float lift_goal_x, lift_goal_y;		//動く床の目標位置
		int lift_vector_x;					//動く床の移動方向(横)
		int lift_vector_y;					//動く床の移動方向(縦)
		int lift_wait_time;					//動く床待機時間
		
		int pair_num;						//ボタンとドアのペア番号
	};
	
private:
	int guid_font,guid_timer;
	std::vector<ELEMENT_DATA> hook;			//フック
	std::vector<ELEMENT_DATA> button;		//ボタン
	std::vector<ELEMENT_DATA> door;			//ドア
	std::vector<ELEMENT_DATA> lift;			//動く床
	std::vector<ELEMENT_DATA> manhole;		//マンホール
	std::vector<ELEMENT_DATA> acidrain_puddles;			//酸性雨の水たまり
	float player_map_x, player_map_y;
	int player_state;
	
	//mutable int animtimer;
	bool keep_pushing;						//ボタンを押し続けているかフラグ
	bool hook_flg; //近くにあるフックにガイド表示させる為のフラグ。
	int door_close_se, press_the_button_se, switch_se, walk_puddle_se, manhole_opened_se;
	int acidrain_puddles_anitimer;		//酸性雨の水たまりの切り替えアニメーション用タイマー
	int underground_effects;			//地下エフェクト用タイマー

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ELEMENT(const char* stage_name = "StageSelect");
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ELEMENT();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(STAGE* stage, PLAYER* player);
	/// <summary>
	/// 更新
	/// </summary>
	void Update(PLAYER* player,STAGE*stage);
	/// <summary>
	/// 3種類のボタンの処理
	/// </summary>
	void Button(PLAYER* player);
	/// <summary>
	/// ドアの処理
	/// </summary>
	void Door(STAGE* stage);
	/// <summary>
	/// 動く床の処理
	/// </summary>
	void Lift(PLAYER* player, STAGE* stage);
	/// <summary>
	/// 動く床の当たり判定
	/// </summary>
	bool HitLift(PLAYER* player);
	/// <summary>
	/// マンホールの処理
	/// </summary>
	void Manhole(PLAYER* player, STAGE* stage);
	/// <summary>
	/// 酸性雨の水たまりの処理
	/// </summary>
	void Acidrain_puddles(PLAYER* player);
	/// <summary>
	/// フックのガイド表示用距離計算
	/// </summary>
	void Hook_Distance(PLAYER* player, STAGE* stage);


	/// <summary>
	/// フック構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	/// <summary>
	/// ボタン構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	/// <summary>
	/// ドア構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	/// <summary>
	/// 動く床構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	/// <summary>
	/// マンホール構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	/// <summary>
	/// 酸性雨の水たまり構造体のGetter
	/// </summary>
	std::vector<ELEMENT_DATA>GetAcidrain_puddles() { return acidrain_puddles; }
};

