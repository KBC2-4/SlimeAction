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
	std::vector<ELEMENT_DATA> tunnel;		//トンネル
	std::vector<ELEMENT_DATA> acid;			//酸
	float player_map_x, player_map_y;
	//mutable int animtimer;

public:
	ELEMENT();
	void Draw() const override;
	void Update(PLAYER* player);
	void Button();
	void Door();
	std::vector<ELEMENT_DATA> GetHookPos() { return hook; }
	std::vector<ELEMENT_DATA>GetButtonPos() { return button; }
	std::vector<ELEMENT_DATA>GetDoorPos() { return door; }
	std::vector<ELEMENT_DATA>GetLiftPos() { return lift; }
	std::vector<ELEMENT_DATA>GetTunnel() { return tunnel; }
};

