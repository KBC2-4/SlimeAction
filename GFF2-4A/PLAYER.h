#pragma once
#include"PadInput.h"

#define MAX_LIFE				5		//�v���C���[�̍ő僉�C�t
#define SPEED					3.0f	//�v���C���[�̃X�s�[�h
#define DEVIATION				2000	//�X�e�B�b�N���͂̌���͈͂̔�
#define ANIMATION_SWITCH_FRAME	1		//�摜��؂�ւ���^�C�~���O(�t���[��)
#define IMAGE_MAX_NUM			10		//�摜�̖���
#define JUMP_VELOCITY			-5.8f	//�W�����v�X�s�[�h

enum class PLAYER_STATE {
	IDLE = 0,//��~���Ă���Ƃ�
	MOVE,    //�����Ă�Ƃ�
	JUMP,    //����
	FALL,	 //����
	THROW,   //�����鎞
	HOOK,    //�t�b�N�����ނƂ�
	DAMAGE,  //�_���[�W���󂯂���
	DEAD     //���񂾂Ƃ�
};

class Player
{

private:
	float player_x,player_y;
	int map_x, map_y;
	int life;
	int image[100];
	int move_type;			//�����E�̈ړ�(���]�p)
	int animation_frame;	//�A�j���[�V�����̃t���[���̃J�E���g
	int animation_type;		//���̃A�j���[�V�����̓Y����
	int animation_phase;	//�A�j���[�V�����̒i�K(0: �O��, 1: �㔼)
	int jump_mode;			//��~�W�����v(1)���ړ��W�����v(2)��

	PLAYER_STATE player_state;		//�X�e�[�g�ϐ�

public:
	Player();

	void Move();
	void Draw() const;
	void HookMove();
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update();


	/*�ϐ��̃Z�b�g�ƃQ�b�g*/
	int GetLife() { return life; };
	float GetPlayerX() { return player_x; };
	float GetPlayerY() { return player_y; };

	void SetLife(int);
};

