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
		bool flg;

	};
private:
	std::vector<ELEMENT_DATA> hook;			//�t�b�N
	std::vector<ELEMENT_DATA> button;		//�{�^��
	std::vector<ELEMENT_DATA> door;			//�h�A
	std::vector<ELEMENT_DATA> lift;			//������
	std::vector<ELEMENT_DATA> tunnel;		//�g���l��
	std::vector<ELEMENT_DATA> acid;			//�_

public:
	ELEMENT();
	void Update(PLAYER* player);
	void Button(float player_x,float player_y);
	std::vector<ELEMENT_DATA> GetHookPos() { return hook; }
	std::vector<ELEMENT_DATA>GetButtonPos() { return button; }
	std::vector<ELEMENT_DATA>GetDoorPos() { return door; }
	std::vector<ELEMENT_DATA>GetLiftPos() { return lift; }
	std::vector<ELEMENT_DATA>GetTunnel() { return tunnel; }
};

