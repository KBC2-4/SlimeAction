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
	float lift_speed;
	//mutable int animtimer;

public:
	ELEMENT();
	void Draw() const override;
	void Update(PLAYER* player);
	void Button();
	void Door();
	void Lift();
	bool HitLift();
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	std::vector<ELEMENT_DATA>GetTunnel() { return tunnel; }
	float GetLiftSpeed() { return lift_speed; }
};

