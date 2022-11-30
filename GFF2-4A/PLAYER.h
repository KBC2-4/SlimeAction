#pragma once
#include"PadInput.h"
#include "Element.h"
#include <vector>
#include "ThrowSlime.h"
#include "STAGE.h"

#define MAX_LIFE				5		//�v���C���[�̍ő僉�C�t
#define SPEED					3.0f	//�v���C���[�̃X�s�[�h
#define DEVIATION				2000	//�X�e�B�b�N���͂̌���͈͂̔�
#define JUMP_VELOCITY			-5.8f	//�W�����v�X�s�[�h
#define HOOK_MAX_DISTANCE		280
#define ANIMATION_TYPE			7

#define PI 3.1415926535897932384626433832795
#define LENGTH      200                 // �R�̒���
#define CLENGTH     (LENGTH * 2 * PI)   // �R��L�΂��Ĉ���������ꍇ�ɏo����~�̉~���̒���
#define G           9.81                // �d�͉����x

#define MIN_SIZE_SCALE		0.8f	//�v���C���[�̍ŏ��T�C�Y(�{��)

//�ړ��X�e�[�g
enum class PLAYER_MOVE_STATE {
	IDLE = 0,//��~���Ă���Ƃ�
	MOVE,    //�����Ă�Ƃ�
	JUMP,    //����
	FALL,	 //����
	THROW,   //�����鎞
	HOOK,    //�t�b�N�����ނƂ�
	DAMAGE,  //�_���[�W���󂯂���
	DEAD,     //���񂾂Ƃ�
};

//�A�j���[�V�����X�e�[�g
enum class PLAYER_ANIM_STATE {
	IDLE = 0,//�A�C�h���A�j���[�V����
	MOVE,	 //�ړ��A�j���[�V����
	THROW,	 //������A�j���[�V����
	HOOK,
	JUMP,	//�W�����v�A�j���[�V����
	FALL,
	LANDING,
};

class PLAYER
{

private:
	bool is_death;
	static float player_x, player_y;
	float old_player_x, old_player_y;
	int map_x, map_y;
	float jump_move_x;
	bool is_ground;		//�n�ʂɂ��Ă邩�ǂ���
	bool hit_ceil;

	int life;
	int images[ANIMATION_TYPE][10];		//�A�j���[�V�����̉摜
	int hp_img;
	int hand_img;
	int move_type;			//�����E�̈ړ�(���]�p)
	float move_x;
	int jump_mode;			//��~�W�����v(1)���ړ��W�����v(2)��
	bool is_jump;
	bool jump_request;
	float jumppower;
	float jump_velocity;

	//hook
	bool is_hook_move;
	float hook_angle;
	float hook_distance;
	float hook_y, hook_x;
	int hook_index;
	
	double x;     // �R��L�΂��Ĉ���������ꍇ�ɏo����~�̐���̍��W�A�O�͕R�����̐^���ɐL�т��ʒu
	double speed; // x�̕ω����x
	double angle;
	int nx, ny;
	double b = 8.0;		//�f�t�H���g8
	double mass = 4.0;

	//Throw
	bool throw_preparation;
	int throw_ball_image;
	float throw_rad;

	std::vector<ThrowSlime> throw_slime;
	std::vector<float>throw_x;
	std::vector<float>throw_y;
	int throw_index = 0;

	//�_�ŗp
	bool is_damage;
	int alpha_param;	//�p���[���[�^�[
	int alpha_time;		//�_�Ŏ���

	//�v���C���[�̃T�C�Y(�{��)
	float player_scale;

	typedef struct Animation {
		//�摜��؂�ւ���^�C�~���O(�t���[��)
		const int switch_frame;

		//�A�j���[�V�����̍Đ��̎d��
		//-1: �Œ�
		// 0: �ꖇ�ڂ���Đ�������t�Đ�����
		// 1: �ꖇ�ڂ���Đ�������ꖇ�ڂɖ߂�
		// 2: �Ō�܂ł��ꂽ��Ō�̉摜�ŌŒ�
		const int play_type;

		//�A�j���[�V�����摜�̖���
		const int image_num;

		//�A�j���[�V�����̗D��x
		const int priority;

		//�A�j���[�V�����̃t���[���̃J�E���g
		int frame = 0;

		//���̃A�j���[�V�����̓Y����
		int type = 0;

		//play_type��0�̃A�j���[�V�����̒i�K(0: �O��, 1: �㔼)
		int phase = 0;

		//���[�v�Đ����ǂ���(0: ���[�v�Đ�)
		int playMode;

		//�A�j���[�V�����̏I������
		bool endAnim;
	};
	Animation animation[ANIMATION_TYPE]{
		{  3,  1,  9, 0 },	//�A�C�h��
		{  1,  0, 10, 0 },	//�ړ�
		{  3,  1,  7, 2 },	//������
		{  1, -1,  1, 0 },	//�t�b�N
		{ 20,  1,  4, 1 },	//�W�����v
		{ 20,  2,  4, 1 },	//����
		{  2,  1, 10, 1 },	//���n
	};

	//�X�e�[�g�ϐ�
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;
	STAGE *stage;

public:
	PLAYER(STAGE* stage);

	void Move();
	void Draw(STAGE* stage) const;
	void HookMove(ELEMENT* element, STAGE* stage);
	void JumpMove();
	void Throw(STAGE* stage);
	void MoveAnimation();
	void Update(ELEMENT*element, STAGE* stage);
	void HitBlock(ELEMENT* element, STAGE* stage);
	void ChangeAnimation(PLAYER_ANIM_STATE anim, bool compelChange = false);

	/*�ϐ��̃Z�b�g�ƃQ�b�g*/
	int GetLife() { return life; };
	bool IsDeath() { return is_death; }
	float GetPlayerX() { return player_x + stage->GetScrollX(); }
	float GetPlayerY() { return player_y+stage->GetScrollY(); }

	void SetPlayerX(float x) { player_x = x - stage->GetScrollX(); }
	void SetPlayerY(float y) { player_y = y; }
	void SetPlayer_Screen(POINT screen) { player_x = screen.y; player_y = screen.x; }

	int GetThrowCnt() { return throw_slime.size(); }
	ThrowSlime GetThrowSlime(int index) { return throw_slime[index]; }

	double GetSpeed() { return speed; }
	float GetMoveX() { return move_x; }

	float GetPlayerScale() { return player_scale; }

	float GetJumpVelocity() { return jump_velocity; }

	void SetLife(int a);

	PLAYER_MOVE_STATE GetPlayerMoveState() { return player_state; }
};
