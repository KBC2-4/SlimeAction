#pragma once
#include "STAGE.h"
#include <vector>


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

	};
private:
	int guid_font,guid_timer;
	std::vector<ELEMENT_DATA> hook;			//フック
	std::vector<ELEMENT_DATA> button;		//ボタン
	std::vector<ELEMENT_DATA> door;			//ドア
	std::vector<ELEMENT_DATA> lift;			//動く床
	std::vector<ELEMENT_DATA>lift_goal;		//動く床のゴール地点
	std::vector<ELEMENT_DATA> manhole;		//マンホール
	std::vector<ELEMENT_DATA> acidrain_puddles;			//酸性雨の水たまり
	float player_map_x, player_map_y;
	int player_state;
	int lift_vector;
	//mutable int animtimer;
	bool hook_flg; //近くにあるフックにガイド表示させる為のフラグ。
	int door_close_se, press_the_button_se, switch_se, walk_puddle_se;

public:
	ELEMENT(const char* stage_name = "StageSelect");
	~ELEMENT();
	void Draw(STAGE* stage);
	void Update(PLAYER* player,STAGE*stage);
	void Button(PLAYER* player);		//3種類のボタン
	void Door(STAGE*stage);						//ドアの処理
	void Lift(PLAYER* player);			//動く床の処理
	bool HitLift(PLAYER* player, float player_scale);						//動く床の当たり判定
	void Manhole(PLAYER* player);		//マンホールの処理
	void Acidrain_puddles(PLAYER* player);		//酸性雨の水たまりの処理
	void Hook_Distance(PLAYER* player, STAGE* stage);	//フックのガイド表示用距離計算
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	std::vector<ELEMENT_DATA>GetAcidrain_puddles() { return acidrain_puddles; }
};

