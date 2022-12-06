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
		
		float lift_init_x, lift_init_y;			//�������̏������W
		int lift_vector_x;					//�������̈ړ�����(��)
		int lift_vector_y;					//�������̈ړ�����(�c)
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
	
	//mutable int animtimer;
	bool keep_pushing;						//�{�^�������������Ă��邩�t���O
	bool hook_flg; //�߂��ɂ���t�b�N�ɃK�C�h�\��������ׂ̃t���O�B
	int door_close_se, press_the_button_se, switch_se, walk_puddle_se;

public:
	ELEMENT(const char* stage_name = "StageSelect");
	~ELEMENT();
	void Draw(STAGE* stage);
	void Update(PLAYER* player,STAGE*stage);
	void Button(PLAYER* player);		//3��ނ̃{�^��
	void Door(STAGE*stage);						//�h�A�̏���
	void Lift(PLAYER* player, STAGE* stage);			//�������̏���
	bool HitLift(PLAYER* player);						//�������̓����蔻��
	void Manhole(PLAYER* player, STAGE* stage);		//�}���z�[���̏���
	void Acidrain_puddles(PLAYER* player);		//�_���J�̐����܂�̏���
	void Hook_Distance(PLAYER* player, STAGE* stage);	//�t�b�N�̃K�C�h�\���p�����v�Z
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	std::vector<ELEMENT_DATA>GetAcidrain_puddles() { return acidrain_puddles; }
	//float GetLift_SpeedX() { return lift_speedX; }
	//float GetLift_SpeedY() { return lift_speedY; }
};

