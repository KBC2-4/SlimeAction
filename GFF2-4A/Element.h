#pragma once
#include "STAGE.h"
#include <vector>



class ELEMENT :
    public STAGE
{
public:
	struct ELEMENT_DATA
	{
		float x, y;
		int type;
		bool flg;

	};
private:
	std::vector<ELEMENT_DATA> hook;			//フック
	std::vector<ELEMENT_DATA> button;		//ボタン
	std::vector<ELEMENT_DATA> door;			//ドア
	std::vector<ELEMENT_DATA> lift;			//動く床
	std::vector<ELEMENT_DATA> tunnel;		//トンネル

public:
	ELEMENT();
	void Button();
	std::vector<ELEMENT_DATA> GetHookPos() { return hook; }
	std::vector<ELEMENT_DATA>GetButtonPos() { return button; }
	std::vector<ELEMENT_DATA>GetDoorPos() { return door; }
	std::vector<ELEMENT_DATA>GetLiftPos() { return lift; }
	std::vector<ELEMENT_DATA>GetTunnel() { return tunnel; }
};

