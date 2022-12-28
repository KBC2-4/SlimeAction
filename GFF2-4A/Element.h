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
		
		float lift_init_x, lift_init_y;		//�������̏������W
		float lift_goal_x, lift_goal_y;		//�������̖ڕW�ʒu
		int lift_vector_x;					//�������̈ړ�����(��)
		int lift_vector_y;					//�������̈ړ�����(�c)
		int lift_wait_time;					//�������ҋ@����
		
		int pair_num;						//�{�^���ƃh�A�̃y�A�ԍ�
	};
	
private:
	int guid_font,guid_timer;
	std::vector<ELEMENT_DATA> hook;			//�t�b�N
	std::vector<ELEMENT_DATA> button;		//�{�^��
	std::vector<ELEMENT_DATA> door;			//�h�A
	std::vector<ELEMENT_DATA> lift;			//������
	std::vector<ELEMENT_DATA> manhole;		//�}���z�[��
	std::vector<ELEMENT_DATA> acidrain_puddles;			//�_���J�̐����܂�
	float player_map_x, player_map_y;
	int player_state;
	
	//mutable int animtimer;
	bool keep_pushing;						//�{�^�������������Ă��邩�t���O
	bool hook_flg; //�߂��ɂ���t�b�N�ɃK�C�h�\��������ׂ̃t���O�B
	int door_close_se, press_the_button_se, switch_se, walk_puddle_se, manhole_opened_se;
	int acidrain_puddles_anitimer;		//�_���J�̐����܂�̐؂�ւ��A�j���[�V�����p�^�C�}�[
	int underground_effects;			//�n���G�t�F�N�g�p�^�C�}�[

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ELEMENT(const char* stage_name = "StageSelect");
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ELEMENT();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(STAGE* stage, PLAYER* player);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(PLAYER* player,STAGE*stage);
	/// <summary>
	/// 3��ނ̃{�^���̏���
	/// </summary>
	void Button(PLAYER* player);
	/// <summary>
	/// �h�A�̏���
	/// </summary>
	void Door(STAGE* stage);
	/// <summary>
	/// �������̏���
	/// </summary>
	void Lift(PLAYER* player, STAGE* stage);
	/// <summary>
	/// �������̓����蔻��
	/// </summary>
	bool HitLift(PLAYER* player);
	/// <summary>
	/// �}���z�[���̏���
	/// </summary>
	void Manhole(PLAYER* player, STAGE* stage);
	/// <summary>
	/// �_���J�̐����܂�̏���
	/// </summary>
	void Acidrain_puddles(PLAYER* player);
	/// <summary>
	/// �t�b�N�̃K�C�h�\���p�����v�Z
	/// </summary>
	void Hook_Distance(PLAYER* player, STAGE* stage);


	/// <summary>
	/// �t�b�N�\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA> GetHook() { return hook; }
	/// <summary>
	/// �{�^���\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA>GetButton() { return button; }
	/// <summary>
	/// �h�A�\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA>GetDoor() { return door; }
	/// <summary>
	/// �������\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA>GetLift() { return lift; }
	/// <summary>
	/// �}���z�[���\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA>GetManhole() { return manhole; }
	/// <summary>
	/// �_���J�̐����܂�\���̂�Getter
	/// </summary>
	std::vector<ELEMENT_DATA>GetAcidrain_puddles() { return acidrain_puddles; }
};

