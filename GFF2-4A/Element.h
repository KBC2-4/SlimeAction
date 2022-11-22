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
	std::vector<ELEMENT_DATA> hook;			//�t�b�N
	std::vector<ELEMENT_DATA> button;		//�{�^��
	std::vector<ELEMENT_DATA> door;			//�h�A
	std::vector<ELEMENT_DATA> lift;			//������
	std::vector<ELEMENT_DATA>lift_goal;		//�������̃S�[���n�_
	std::vector<ELEMENT_DATA> manhole;		//�}���z�[��
	std::vector<ELEMENT_DATA> acidrain_puddles;			//�_���J�̐����܂�
	float player_map_x, player_map_y;
	int player_state;
	int lift_vector;
	//mutable int animtimer;
	int door_close_se, press_the_button_se, switch_se, walk_puddle_se;

public:
	ELEMENT();
	void Draw() const override;
	void Update(PLAYER* player,STAGE*stage);
	void Button(PLAYER* player);		//3��ނ̃{�^��
	void Door(STAGE*stage);						//�h�A�̏���
	void Lift(PLAYER* player);			//�������̏���
	bool HitLift(PLAYER* player, float player_scale);						//�������̓����蔻��
	void Manhole(PLAYER* player);		//�}���z�[���̏���
	void Acidrain_puddles(PLAYER* player);		//�_���J�̐����܂�̏���
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	std::vector<ELEMENT_DATA>GetAcidrain_puddles() { return acidrain_puddles; }
};

