#pragma once
#include"PadInput.h"

#define MAX_LIFE				5		//�v���C���[�̍ő僉�C�t
#define SPEED					3.0f	//�v���C���[�̃X�s�[�h
#define DEVIATION				2000	//�X�e�B�b�N���͂̌���͈͂̔�
#define ANIMATION_SWITCH_FRAME	1		//�摜��؂�ւ���^�C�~���O(�t���[��)
#define IMAGE_MAX_NUM			10		//�摜�̖���
#define JUMP_VELOCITY			-5.8f	//�W�����v�X�s�[�h

//�ړ��X�e�[�g
enum class PLAYER_MOVE_STATE {
	IDLE = 0,//��~���Ă���Ƃ�
	MOVE,    //�����Ă�Ƃ�
	JUMP,    //����
	FALL,	 //����
	THROW,   //�����鎞
	HOOK,    //�t�b�N�����ނƂ�
	DAMAGE,  //�_���[�W���󂯂���
	DEAD     //���񂾂Ƃ�
};

//�A�j���[�V�����X�e�[�g
enum class PLAYER_ANIM_STATE {
	IDLE = 0,//�A�C�h���A�j���[�V����
	MOVE	 //�ړ��A�j���[�V����
};

class PLAYER
{

private:
	float player_x,player_y;
	int map_x, map_y;
	float player_left = 0, player_right = 0;
	float player_top = 0, player_bottom = 0;
	float rebound_x;
	int life;
	int now_image;			//�`�悷��摜
	int images[2][10];		//�A�j���[�V�����̉摜
	int move_type;			//�����E�̈ړ�(���]�p)
	int animation_frame;	//�A�j���[�V�����̃t���[���̃J�E���g
	int animation_type[2];		//���̃A�j���[�V�����̓Y����
	int animation_phase[2];	//�A�j���[�V�����̒i�K(0: �O��, 1: �㔼)
	int animation_mode;
	int jump_mode;			//��~�W�����v(1)���ړ��W�����v(2)��
	//�X�e�[�g�ϐ�
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;

public:
	PLAYER();

	void Move();
	void Draw() const;
	void HookMove();
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update();
	void HitBlock();

	/*�ϐ��̃Z�b�g�ƃQ�b�g*/
	int GetLife() { return life; };
	float GetPlayerX() { return player_x; };
	float GetPlayerY() { return player_y; };

	void SetLife(int);
};

