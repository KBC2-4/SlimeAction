#pragma once
#include"PadInput.h"
#include "Element.h"
#include <vector>
#include "ThrowSlime.h"

#define MAX_LIFE				5		//�v���C���[�̍ő僉�C�t
#define SPEED					3.0f	//�v���C���[�̃X�s�[�h
#define DEVIATION				2000	//�X�e�B�b�N���͂̌���͈͂̔�
//#define ANIMATION_SWITCH_FRAME	1		//�摜��؂�ւ���^�C�~���O(�t���[��)
//#define IMAGE_MAX_NUM			10		//�摜�̖���
#define JUMP_VELOCITY			-5.8f	//�W�����v�X�s�[�h
#define HOOK_MAX_DISTANCE		280
#define ANIMATION_TYPE			4

#define PI 3.1415926535897932384626433832795
#define LENGTH      200                 // �R�̒���
#define CLENGTH     (LENGTH * 2 * PI)   // �R��L�΂��Ĉ���������ꍇ�ɏo����~�̉~���̒���
#define G           9.81                // �d�͉����x

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
	MOVE,	 //�ړ��A�j���[�V����
	THROW,	 //������A�j���[�V����
	HOOK,
};

class PLAYER
{

private:
	bool is_death;
	static float player_x, player_y;
	int map_x, map_y;
	float player_left = 0, player_right = 0;
	float player_top = 0, player_bottom = 0;
	float rebound_x;
	float jump_move_x;
	int life;
	int now_image;			//�`�悷��摜
	int images[ANIMATION_TYPE][10];		//�A�j���[�V�����̉摜
	int move_type;			//�����E�̈ړ�(���]�p)
	float move_x;
	int animation_frame;	//�A�j���[�V�����̃t���[���̃J�E���g
	int animation_type[ANIMATION_TYPE];		//���̃A�j���[�V�����̓Y����
	int animation_phase[ANIMATION_TYPE];	//�A�j���[�V�����̒i�K(0: �O��, 1: �㔼)
	int animation_mode;
	int jump_mode;			//��~�W�����v(1)���ړ��W�����v(2)��
	bool jump_request;
	bool is_hook_move;
	float hook_angle;
	float hook_distance;

	float hook_y, hook_x;

	double x;     // �R��L�΂��Ĉ���������ꍇ�ɏo����~�̐���̍��W�A�O�͕R�����̐^���ɐL�т��ʒu
	double speed; // x�̕ω����x
	double angle;
	int nx, ny;
	double b = 8.0;		//�f�t�H���g8
	double mass = 4.0;

	//Throw
	int throw_ball_image;
	bool is_throw_anim;
	//double throw_x[100];// = 100;
	//double throw_y[100];// = 560;
	float throw_rad;

	/*bool pressBtn = false;*/
	std::vector<ThrowSlime> throw_slime;
	std::vector<float>throw_x = {0};
	std::vector<float>throw_y = {0};
	int throw_index = 0;

	float ve, vx0, vy0, vx, vy;
	float g, dt, t,x0, y0;

	//�摜��؂�ւ���^�C�~���O(�t���[��)
	const int animation_switch_frame[ANIMATION_TYPE] = {
		3,	//�A�C�h��
		1,	//�ړ�
		3,	//������
		1,
	};

	//�A�j���[�V�����̍Đ��̎d��
	// 0: �ꖇ�ڂ���Đ�������t�Đ�����
	// 1: �ꖇ�ڂ���Đ�������ꖇ�ڂɖ߂�
	const int animation_play_type[ANIMATION_TYPE] = {
		1,	//�A�C�h��
		0,	//�ړ�
		1,	//������
		2,
	};

	//�A�j���[�V�����摜�̖���
	const int animation_image_num[ANIMATION_TYPE] = {
		9,	//�A�C�h��
		10,	//�ړ�
		7,	//������
		1,
	};

	//�X�e�[�g�ϐ�
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;

public:
	PLAYER();

	void Move();
	void Draw() const;
	void HookMove(ELEMENT* element);
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update(ELEMENT*element);
	void HitBlock();
	void Scroll(float move_x);

	/*�ϐ��̃Z�b�g�ƃQ�b�g*/
	int GetLife() { return life; };
	bool IsDeath() { return is_death; }
	static float GetPlayerX() { return player_x; }
	static float GetPlayerY() { return player_y; }

	void SetPlayerX(float x) { player_x = x; }
	void SetPlayerY(float y) { player_y = y; }

	int GetThrowCnt() { return throw_slime.size(); }
	ThrowSlime GetThrowSlime(int index) { return throw_slime[index]; }

	void SetLife(int);
};

