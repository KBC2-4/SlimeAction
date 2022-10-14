#pragma once
#include"PadInput.h"

enum class PLAYER_STATE {
	IDLE = 0,//��~���Ă���Ƃ�
	MOVE,    //�����Ă�Ƃ�
	JUMP,    //����
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
	int jump_mode;			//��~�W�����v(1)���ړ��W�����v(2)��

	PLAYER_STATE player_state;		//�X�e�[�g�ϐ�

	const int MAX_LIFE = 5;
	const int DEVIATION = 2000;				//�X�e�B�b�N���͂̌���͈͂̔�
	const int ANIMATION_SWITCH_FRAME = 10;	//�摜��؂�ւ���^�C�~���O
	const int IMAGE_MAX_NUM = 5;			//�摜�̖���
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

	void SetLife(int);
};

