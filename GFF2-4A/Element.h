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
	std::vector<ELEMENT_DATA> hook;			//�t�b�N
	std::vector<ELEMENT_DATA> button;		//�{�^��
	std::vector<ELEMENT_DATA> door;			//�h�A
	std::vector<ELEMENT_DATA> lift;			//������
	std::vector<ELEMENT_DATA> tunnel;		//�g���l��
	std::vector<ELEMENT_DATA> acid;			//�_
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

