#pragma once
#include "STAGE.h"
#include <vector>


class PLAYER;

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
	std::vector<ELEMENT_DATA> hook;			//フック
	std::vector<ELEMENT_DATA> button;		//ボタン
	std::vector<ELEMENT_DATA> door;			//ドア
	std::vector<ELEMENT_DATA> lift;			//動く床
	std::vector<ELEMENT_DATA>lift_goal;		//動く床のゴール地点
	std::vector<ELEMENT_DATA> manhole;		//マンホール
	std::vector<ELEMENT_DATA> acid;			//酸
	float player_map_x, player_map_y;
	int lift_vector;
	//mutable int animtimer;

public:
	ELEMENT();
	void Draw() const override;
	void Update(PLAYER* player);
	void Button(PLAYER* player);	//3種類のボタン
	void Door();					//ドア
	void Lift();					//動く床
	bool HitLift();					//動く床の当たり判定
	void Manhole(PLAYER* player);	//マンホール
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	int GetLiftVector() { return lift_vector; }
};

