#include "PLAYER.h"
#include"DxLib.h"
#include "Element.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Option.h"

//�f�o�b�O������
//#define _DEBUG

/*�R���X�g���N�^*/
PLAYER::PLAYER(STAGE* stage) {
	this->stage = stage;
	player_x = 0.0f;
	player_y = 0.0f;
	map_x = 0;
	map_y = 0;
	life = MAX_LIFE;
	jumppower = 0.0f;
	jump_velocity = 0.0f;
	jump_mode = 0;
	jump_move_x = 0;
	jump_request = false;
	is_jump = false;
	is_gravity = true;
	is_hook_move = false;
	is_damage = false;
	is_visible = true;
	throw_preparation = false;
	throw_interval = 0.0f;
	player_state = PLAYER_MOVE_STATE::IDLE;
	grabbed_hook_array.clear();
	// �����ʒu�͎��̐^�����獶������45�x�X�����ʒu
	x = CLENGTH / b;
	// �������x�͂O
	speed = 0;

	is_heal = false;

	//�摜�̓ǂݍ���
	if (LoadDivGraph("Resource/Images/Player/IdorSlime.png", 9, 9, 1, 80, 80, images[0]) == -1) {
		throw "Resource/Images/Player/IdorSlime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, images[1]) == -1) {
		throw "Resource/Images/Player/Slime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/ThrowSlime.png", 7, 7, 1, 80, 80, images[2]) == -1) {
		throw "Resource/Images/Player/ThrowSlime.png";
	}
	if ((images[3][0] = LoadGraph("Resource/Images/Player/nobi.png")) == -1) {
		throw "Resource/Images/Player/nobi.png";
	}
	if ((images[3][1] = LoadGraph("Resource/Images/Player/nobi2.png")) == -1) {
		throw "Resource/Images/Player/nobi2.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime01.png", 4, 4, 1, 80, 80, images[4]) == -1) {
		throw "Resource/Images/Player/JumpSlime01.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime02.png", 4, 4, 1, 80, 80, images[5]) == -1) {
		throw "Resource/Images/Player/JumpSlime02.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime2.png", 10, 10, 1, 80, 80, images[6]) == -1) {
		throw "Resource/Images/Player/JumpSlime1.png";
	}
	if ((throw_ball_image = LoadGraph("Resource/Images/Player/Slime_Bullet.png")) == -1) {
		throw "Resource/Images/Player/Slime_Bullet.png";
	}
	if ((idle_nobi_img = LoadGraph("Resource/Images/Player/FuckAnim2.png")) == -1) {
		throw "Resource/Images/Player/FuckAnim2.png";
	}

	//SE�̓ǂݍ���
	if ((damageSE = LoadSoundMem("Resource/Sounds/SE/Player/damage.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/damage.wav";
	}
	if ((jumpSE = LoadSoundMem("Resource/Sounds/SE/Player/jump.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/jump.wav";
	}
	if ((landingSE = LoadSoundMem("Resource/Sounds/SE/Player/landing.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/jump2.wav";
	}
	if ((hook_moveSE = LoadSoundMem("Resource/Sounds/SE/Player/hook_move.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/hook_move.wav";
	}
	if ((hook_pendulumSE = LoadSoundMem("Resource/Sounds/SE/Player/hook.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/hook_pendulum.wav";
	}
	if ((healSE = LoadSoundMem("Resource/Sounds/SE/Player/heal.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/heal.wav";
	}
	if ((throw_ballSE = LoadSoundMem("Resource/Sounds/SE/Player/throw_ball.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/throw_ball.wav";
	}


	//SE�̃{�����[���ύX
	ChangeVolumeSoundMem(Option::GetSEVolume(), damageSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), jumpSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), landingSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), hook_moveSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), hook_pendulumSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), healSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), throw_ballSE);

	//�A�j���[�V�����̏�����
	animation_state = PLAYER_ANIM_STATE::IDLE;
	for (int i = 0; i < ANIMATION_TYPE; i++) {
		animation[i].frame = 0;
		animation[i].type = 0;
		animation[i].phase = 0;
		animation[i].playMode = 0;
		animation[i].endAnim = false;
	}

	animation[static_cast<int>(PLAYER_ANIM_STATE::THROW)].playMode = 1;
	animation[static_cast<int>(PLAYER_ANIM_STATE::LANDING)].playMode = 1;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PLAYER::~PLAYER() {
	DeleteGraph(throw_ball_image);
	DeleteGraph(idle_nobi_img);
	for (int i = 0; i < ANIMATION_TYPE; i++) {
		for (int j = 0; j < 10; j++) {
			DeleteGraph(images[i][j]);
		}
	}

	DeleteSoundMem(damageSE);
	DeleteSoundMem(jumpSE);
	DeleteSoundMem(landingSE);
	DeleteSoundMem(hook_moveSE);
	DeleteSoundMem(hook_pendulumSE);
	DeleteSoundMem(healSE);
	DeleteSoundMem(throw_ballSE);
}

/// <summary>
/// �v���C���[�̍X�V
/// </summary>
void PLAYER::Update(ELEMENT* element, STAGE* stage, TOMATO** tomaton, int tomaton_count, bool is_stay) {

	ChangeVolumeSoundMem(Option::GetSEVolume(), damageSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), jumpSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), landingSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), hook_moveSE);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 0.7, hook_pendulumSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), healSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), throw_ballSE);

	//�ړ�����
	Move();

	if (is_stay) {
		player_x = old_player_x;
	}
	else {
		//�t�b�N����
		HookMove(element, stage);

		//�����鏈��
		Throw(stage);
	}

	//�W�����v�Ɨ�������
	JumpMove();

	//�A�j���[�V�����̍Đ�
	MoveAnimation();

	//�u���b�N�Ƃ̓����蔻��
	Hit(element, stage);

	//������������
	for (int i = 0; i < throw_slime.size(); i++) {
		if (throw_slime[i].checkdel() == true) {
			throw_slime[i].Finalize();
			throw_slime.erase(throw_slime.begin() + i);
		}
	}

	//���̍X�V
	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Update(stage, element, tomaton, tomaton_count);
	}

	//������
	if (player_y + stage->GetScrollY() > 720 && player_state != PLAYER_MOVE_STATE::HOOK || life <= 0) {
		player_state = PLAYER_MOVE_STATE::DEAD;
		return;
	}

	//��ʒ[�̔���
	if (player_x <= 40 * player_scale) {
		player_x = 40 * player_scale;
	}
	if (player_x + stage->GetScrollX() >= 1280 - MAP_CEllSIZE / 2 * player_scale) {
		player_x = 1280 - MAP_CEllSIZE / 2 * player_scale - stage->GetScrollX();
	}

	//�_�ŏ���
	if (is_damage) {
		if (alpha_time > 0) {
			if (alpha_time % 20 < 10) {
				alpha_param -= 25;
			}
			else {
				alpha_param += 25;
			}
			alpha_time--;
		}
		else {
			is_damage = false;
		}
	}

	//�v���C���[�̃T�C�Y�̍X�V
	player_scale = static_cast<float>(life - 1) / static_cast<float>(MAX_LIFE) + MIN_SIZE_SCALE;
}

/// <summary>
/// �v���C���[�̕\��
/// </summary>
void PLAYER::Draw(STAGE* stage)const {
	//�\���t���O
	if (!is_visible) return;

	if (is_damage) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_param);
	}

	//�v���C���[�̕\��
	if (player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		//�`�悷��摜�̃Z�b�g
		int image_type = static_cast<int>(animation_state);
		int now_image = images[image_type][animation[image_type].type];

		DrawRotaGraphF(player_x + stage->GetScrollX(), (player_y - 20 + stage->GetScrollY()) + (1.6 - player_scale) * 40, player_scale, 0.0, now_image, TRUE, move_type);
	}
	//�t�b�N��
	else {
		//�U��q��
		if (player_state == PLAYER_MOVE_STATE::HOOK) {
			float diff_x = nx;
			float diff_y = ny;
			float distance = sqrt(diff_y * diff_y + diff_x * diff_x);
			float angle = atan2(diff_y, diff_x) + DX_PI_F;
			if (move_type == 0) {
				DrawRotaGraph3F(hook_x + nx + stage->GetScrollX(), hook_y + ny + stage->GetScrollY(), 80, 80,
					(distance) / MAP_CEllSIZE / 2, 0.6f, (double)angle,
					images[3][1], TRUE, move_type);
			}
			else {
				DrawRotaGraph3F(hook_x + nx + stage->GetScrollX(), hook_y + ny + stage->GetScrollY(), 80, 80,
					(distance) / MAP_CEllSIZE / 2, 0.6f, (double)angle,
					images[3][0], TRUE, move_type);
			}
		}
		//�L�т鎞
		else {
			DrawRotaGraph3F(player_x + stage->GetScrollX() + 20, (player_y + stage->GetScrollY()) + (1.6 - player_scale) * 40, 80, 40,
				(hook_move_distance / (MAP_CEllSIZE * 3.0)) * player_scale, 1 * player_scale, (double)hook_angle + M_PI,
				idle_nobi_img, TRUE, move_type);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�{�[���̕`��
	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Draw(stage);
	}

	//�{�[���̋O���̕`��
	for (int i = 0; i < throw_x.size(); i += 5) {
		DrawGraphF(throw_x[i], throw_y[i], throw_ball_image, TRUE);
	}
}

/// <summary>
/// �v���C���[�̈ړ�
/// </summary>
void PLAYER::Move()
{
	//�ړ��O�̍��W
	old_player_x = player_x;
	old_player_y = player_y;

	//�X�s�[�h�̃Z�b�g
	player_speed = SPEED + (MAX_LIFE - life) * 0.4f;

	//�t�b�N���͈ړ������Ȃ�
	if (is_hook_move || player_state == PLAYER_MOVE_STATE::HOOK) return;

	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();

	//�ړ�����
	if (input_lx > 0) {
		move_x = 1.0f;
	}
	move_x = input_lx > 0 ? 1.0f : -1.0f;	//�ړ������̃Z�b�g

	//�ړ�����Ƃ�
	if (input_lx < -DEVIATION || input_lx > DEVIATION)
	{
		//�W�����v��
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL)
		{
			move_type = (move_x > 0) ? 0 : 1;				//�ړ������̃Z�b�g(0: �E, 1: ��)
			player_x += move_x * player_speed;
			jump_move_x = move_x;
			player_state = PLAYER_MOVE_STATE::MOVE;	//�X�e�[�g��Move�ɐ؂�ւ�
			ChangeAnimation(PLAYER_ANIM_STATE::MOVE); //�A�j���[�V�����̐؂�ւ�
		}
		else
		{
			if (jump_move_x == 0) jump_move_x = move_x;
			move_type = (jump_move_x > 0) ? 0 : 1;
			if (jump_mode == 1) //��~�W�����v��������
			{
				player_x += jump_move_x * player_speed / 2.0f;
			}
			else //�ړ��W�����v��������
			{
				move_type = (jump_move_x > 0) ? 0 : 1;

				//�W�����v���ɔ��Ε����Ɉړ�����Ƃ�
				if (jump_move_x != move_x)
				{
					player_x += jump_move_x * player_speed / 2.0f;
				}
				else
				{
					player_x += jump_move_x * player_speed;
				}
			}
		}
	}
	//�ړ����ĂȂ���
	else
	{
		move_x = 0;
		//�ړ��A�j���[�V�������㔼�ֈڍs
		int move = static_cast<int>(PLAYER_ANIM_STATE::MOVE);
		if (animation[move].type > 1 && animation_state == PLAYER_ANIM_STATE::MOVE)
		{
			animation[move].phase = 1;
		}
		else //�ړ��A�j���[�V�������I�������A�C�h���A�j���[�V�����̍Đ�
		{
			ChangeAnimation(PLAYER_ANIM_STATE::IDLE);
		}
		//�W�����v������Ȃ���������X�e�[�g��؂�ւ���
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) {
			jump_move_x = 0;
			player_state = PLAYER_MOVE_STATE::IDLE;	//�X�e�[�g��Idle�ɐ؂�ւ�
		}
	}

	if (player_x < old_player_x) {
		move_x = -1.0f;
	}
	else if (player_x > old_player_x) {
		move_x = 1.0f;
	}
}

/// <summary>
/// �t�b�N�̈ړ�����
/// </summary>
void PLAYER::HookMove(ELEMENT* element, STAGE* stage) {
	//�߂��Ƀt�b�N�����邩�ǂ���
	bool is_hook = false;

	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();


	//B�{�^���������Ƃ�
	if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) {
		if (player_state != PLAYER_MOVE_STATE::HOOK) {
			//�t�b�N�܂ł̋���
			float min_distance = HOOK_MAX_DISTANCE;
			//�t�b�N�̈ʒu
			std::vector<ELEMENT::ELEMENT_DATA> hook_pos = element->GetHook();
			for (int i = 0; i < hook_pos.size(); i++) {
				//�O�ɒ͂񂾃t�b�N�͒��n����܂Œ͂܂Ȃ�
				if (std::find(grabbed_hook_array.begin(), grabbed_hook_array.end(), i) != grabbed_hook_array.end()) continue;
				ELEMENT::ELEMENT_DATA pos = hook_pos[i];
				//�����v�Z
				float diff_x = pos.x - (player_x);
				float diff_y = pos.y - player_y;
				float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
				//�������ŒZ�������߂��Ƃ�
				if (distance <= min_distance) {
					//�t�b�N�̊p�x
					float angle = atan2f(diff_y, diff_x);
					//�ړ��̌v�Z
					hook_move_x = cosf(angle) * player_speed * 3;
					hook_move_y = sinf(angle) * player_speed * 3;
					//�v���C���[�̌��݂̈ʒu
					float x = player_x;
					float y = player_y;
					//�t�b�N�܂ł̈ړ��o�H�ɏ�Q�����Ȃ���
					while (!stage->HitMapDat(y / MAP_CEllSIZE, x / MAP_CEllSIZE)) {
						if (stage->GetMapData(y / MAP_CEllSIZE, x / MAP_CEllSIZE) == 72) {
							break;
						}
						x += hook_move_x;
						y += hook_move_y;
					}
					//�z��ɕϊ�
					int hook_map_x = x / MAP_CEllSIZE;
					int hook_map_y = y / MAP_CEllSIZE;
					//��Q��������ꍇ�͈ړ������Ȃ�
					if (stage->GetMapData(hook_map_y, hook_map_x) != 72) {		//�t�b�N�̔z��ԍ�������
						continue;
					}
					//�ŒZ�����̍X�V
					min_distance = distance;
					hook_index = i;
					//�t�b�N�̍��W�̍X�V
					hook_x = pos.x;
					hook_y = pos.y;
					//�t�b�N���������������true
					is_hook = true;
				}
			}
		}
		else {
			is_hook = true;
		}
		//�t�b�N������������
		if (is_hook) {
			//�X�e�[�g�̕ύX
			player_state = PLAYER_MOVE_STATE::GROW_HOOK;
			ChangeAnimation(PLAYER_ANIM_STATE::IDLE, false);
			//�ړ����̎�
			if (!is_hook_pendulum_move) {
				//�t�b�N�܂ł̋����̌v�Z
				float y = hook_y - player_y;
				float x = hook_x - (player_x);
				hook_distance = sqrt(x * x + y * y);
				//�p�x�̌v�Z
				hook_angle = atan2f(y, x) + 180.0f * (DX_PI_F / 180.0f);
				//�t�b�N�ړ����ĂȂ���
				if (!is_hook_move) {
					//�ړ������̌v�Z
					hook_move_x = cosf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					hook_move_y = sinf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					//�����I�ȓz
					jump_move_x = hook_move_x > 0 ? 1 : -1;
					jump_mode == 2;
					//PlaySoundMem(hook_moveSE, DX_PLAYTYPE_BACK);
				}
				else {
					hook_move_distance += hook_distance / 10.0f;
				}
				//�t�b�N�ɂ��ĂȂ���
				if (hook_distance > 40) {
					player_x += hook_move_x;
					player_y += hook_move_y;
				}
				//�t�b�N�ɂ�����ړ������̏I��
				else {
					//StopSoundMem(hook_moveSE);
					PlaySoundMem(hook_pendulumSE, DX_PLAYTYPE_LOOP);
					is_hook_pendulum_move = true;
					//�U��q�̊J�n�p�x�̐ݒ�
					double angle = (double)hook_angle * (180.0 / M_PI) - 90.0;
					if (angle > 90 && angle < 180) angle = 90.0;
					else if (angle < -90 || angle > 180) angle = -90.0;
					this->x = (CLENGTH / 360.0) * angle;
					//�X�s�[�h�̏�����
					speed = 0;
				}
				//�t�b�N�܂ł̈ړ�����
				is_hook_move = true;
			}
			//�ړ����I�������
			else {
				//�t�b�N�܂ł̈ړ�����
				is_hook_move = false;
				//�X�e�[�g�̕ύX
				player_state = PLAYER_MOVE_STATE::HOOK;
				//�t�b�N�̍��W�Ƀv���C���[���ړ�
				player_x = hook_x + nx;
				player_y = hook_y + ny;
				// ���x�����Z
				speed += -mass * (G / 60) * sin(x / LENGTH);
				x += speed;
				// �������_�Ƃ��ĂԂ牺�����Ă��镨�̍��W���v�Z
				angle = x / LENGTH + PI / 2.0;
				nx = cos(angle) * LENGTH;
				ny = sin(angle) * LENGTH;
				if (speed >= 0) {
					if (input_lx < -15000) {
						speed += 0.05 * 2.0f;
					}
					if (input_lx > 15000) {
						speed -= 0.09 * 2.0f;
					}
				}
				else if (speed < 0) {
					if (input_lx < -15000) {
						speed += 0.09 * 2.0f;
					}
					if (input_lx > 15000) {
						speed -= 0.05 * 2.0f;
					}
				}
				if (hook_y + ny < hook_y) {
					ny = 0;
					speed = 0.0;
				}
				if (input_lx < 15000 && input_lx >-15000) {	//�����Ă���Ԃ͊p�x�������A�X�s�[�h��x�����Ă���
					if (speed > 0)speed -= 0.05;
					if (speed < 0)speed += 0.05;
				}
				StartJoypadVibration(DX_INPUT_PAD1, static_cast<int>(abs(speed) / 18.0 * 500.0), 1, -1);
			}
		}
	}
	//�t�b�N��������Ȃ�������
	if (!is_hook) {
		//������		
		is_hook_pendulum_move = false;
		hook_move_distance = 0.0f;
		if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
			//�t�b�N��̃W�����v�����̏C��
			StopSoundMem(hook_pendulumSE);
			grabbed_hook_array.push_back(hook_index);

			if (input_lx < -DEVIATION) {
				jump_move_x = -1;
			}
			else if (input_lx > DEVIATION) {
				jump_move_x = 1;
			}
			else {
				if (nx < 0) {
					jump_move_x = -1;
				}
				else {
					jump_move_x = 1;
				}
			}
			if (player_state == PLAYER_MOVE_STATE::HOOK) {
				player_x = hook_x + nx;
				player_y = hook_y + ny;
				player_y += 1;
				jump_mode = 2;
				jumppower = fabs(static_cast<float>(nx) / LENGTH);
				if (fabsf(nx) > LENGTH / 2) {
					jump_request = true;
				}
			}
			player_state = PLAYER_MOVE_STATE::FALL;
		}
		hook_index = -1;
		is_hook_move = false;
	}
}

/// <summary>
/// �v���C���[�̃W�����v����
/// </summary>
void PLAYER::JumpMove() {
#ifdef _DEBUG
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_Y || CheckHitKey(KEY_INPUT_SPACE))return;		//�f�o�b�O�p
#endif
	//A�{�^�����������Ƃ�
	if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_A : XINPUT_BUTTON_B) || jump_request) {
		//�W�����v������Ȃ��Ƃ�
		if ((player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && player_state != PLAYER_MOVE_STATE::HOOK && is_ground
			|| jump_request) && is_gravity) {
			jump_request = false;
			is_jump = true;			//�W�����v���Ɉڍs
			jump_velocity = JUMP_VELOCITY * jumppower;
			//���ړ����ĂȂ���
			if (player_state == PLAYER_MOVE_STATE::IDLE) {
				jump_mode = 1;
			}
			//���ړ����Ă�Ƃ�
			else if (player_state == PLAYER_MOVE_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_MOVE_STATE::JUMP;
			ChangeAnimation(PLAYER_ANIM_STATE::JUMP);
			PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK);
		}
	}
	//�W�����v��
	if (is_jump) {
		jump_velocity += 0.2f;
		player_y += jump_velocity;

		ChangeAnimation(PLAYER_ANIM_STATE::JUMP);

		if (jump_velocity >= 0.0f || hit_ceil || player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
			is_jump = false;
			hit_ceil = false;
			jump_velocity = 0;
		}
	}
	//������
	else {
		//�n�ʂ���Ȃ����͗���
		if (!is_ground && is_gravity) {
			jump_velocity += 0.2f;
			player_y += jump_velocity;
			player_state = PLAYER_MOVE_STATE::FALL;
			ChangeAnimation(PLAYER_ANIM_STATE::FALL);
		}
		//�n�ʂɂ�����
		else {
			if ((player_state == PLAYER_MOVE_STATE::FALL || player_state == PLAYER_MOVE_STATE::JUMP) && !is_hook_move) {
				jumppower = 1.0;
				float new_y = (float)(map_y - 1) * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				if (fabsf(new_y - player_y) <= jump_velocity) {
					player_y = new_y;
				}
				jump_velocity = 0;
				grabbed_hook_array.clear();
				player_state = PLAYER_MOVE_STATE::IDLE;
				ChangeAnimation(PLAYER_ANIM_STATE::LANDING);
				PlaySoundMem(landingSE, DX_PLAYTYPE_BACK);
			}
			if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
				jump_velocity = 0;
			}
		}
		if (animation_state == PLAYER_ANIM_STATE::LANDING) {
			if (animation[static_cast<int>(animation_state)].endAnim) {
				ChangeAnimation(PLAYER_ANIM_STATE::IDLE);
			}
		}
	}

}

/// <summary>
/// �����鏈��
/// </summary>
/// <param name="stage">STAGE�N���X�̃|�C���^</param>
void PLAYER::Throw(STAGE* stage) {
	//�O���̌v�Z
	throw_index = 0;
	throw_x.clear();
	throw_y.clear();

	//�N�[���^�C��
	if (--throw_interval > 0) return;

	int input_ry = PAD_INPUT::GetPadThumbRY();
	int input_rx = PAD_INPUT::GetPadThumbRX();
	if ((abs(input_rx) <= DEVIATION && abs(input_ry) <= DEVIATION) || input_ry < DEVIATION) {
		return;
	}
	//�p�x�擾
	throw_rad = atan2(input_ry, input_rx);
	float angle = throw_rad * 180.0f / M_PI;
	//�p�x�̐���
	if (move_type == 0) {
		if (angle > 90) throw_rad = 90 * M_PI / 180.0f;
		else if (angle < 30) throw_rad = 30 * M_PI / 180.0f;
	}
	else {
		if (angle > 150) throw_rad = 150 * M_PI / 180.0f;
		else if (angle < 90) throw_rad = 90 * M_PI / 180.0f;
	}

	//�O���̌v�Z
	float ve = 110;

	float vx0 = ve * (float)cos(throw_rad);
	float vy0 = ve * (float)sin(throw_rad);

	float g = 9.8;
	float dt = 0.15f;

	float x0 = player_x + stage->GetScrollX();
	float y0 = player_y + stage->GetScrollY();

	float vx = vx0;
	float vy = vy0;

	float maxY = stage->GetMapSize().y * MAP_CEllSIZE;

	for (float t = 0.0; y0 <= maxY; t = t + dt) {
		x0 = x0 + vx * dt;
		y0 = y0 - vy * dt;
		vy = vy - g * dt;
		if (vy < 0) {
			g += 0.2f;
		}
		throw_x.push_back(x0);
		throw_y.push_back(y0);
	}

	//������Ƃ�
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_SHOULDER && PAD_INPUT::GetPadState() == PAD_STATE::ON) {
		//�����鏈��
		throw_interval = THROW_INTERVAL;
		throw_slime.push_back(ThrowSlime(player_x, player_y, throw_rad, stage));
		PlaySoundMem(throw_ballSE, DX_PLAYTYPE_BACK);
		ChangeAnimation(PLAYER_ANIM_STATE::THROW, true);
	}
}

/// <summary>
/// �����蔻��
/// </summary>
void PLAYER::Hit(ELEMENT* element, STAGE* stage) {
	//�}�b�v�`�b�v�̍��W�̃Z�b�g
	map_x = (int)roundf(player_x / MAP_CEllSIZE);
	map_y = (int)floorf((player_y + MAP_CEllSIZE / 2) / MAP_CEllSIZE);
	float player_left = player_x - 30 * player_scale;
	float player_right = player_x + 30 * player_scale;
	float old_player_left = old_player_x - 30 * player_scale;
	float old_player_right = old_player_x + 30 * player_scale;
	float player_top = (player_y - (player_scale - 0.6f) * MAP_CEllSIZE / 2);
	float player_bottom = (player_y + MAP_CEllSIZE / 2);

	//�V��̔���
	bool hit_ceil_center = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(old_player_x / MAP_CEllSIZE));
	bool hit_ceil_left = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)((old_player_left + player_speed) / MAP_CEllSIZE));
	bool hit_ceil_right = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)((old_player_right - player_speed) / MAP_CEllSIZE));
	hit_ceil = hit_ceil_center || hit_ceil_left || hit_ceil_right;

	//�n�ʂ̔���
	is_ground = !is_gravity;
	if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
		is_ground = true;
		return;
	}
	if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) &&
		!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) &&
		!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE))) {
		is_ground = true;
	}
	float diff_y = fabsf(player_y - old_player_y);
	if (fmodf(player_y, MAP_CEllSIZE / 2) <= diff_y) {
		if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE))) {
			is_ground = true;
		}
		if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE))) {
			is_ground = true;
		}
	}

	//�}���z�[���̔���
	int block_type_center = stage->GetMapData((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
	int block_type_top = stage->GetMapData((int)(player_top / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
	int block_type_bottom = stage->GetMapData((int)(player_bottom / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
	if (block_type_center == 98 || block_type_top == 98 || block_type_bottom == 98) {
		float diff = fabsf((float)((int)(player_x / MAP_CEllSIZE) * MAP_CEllSIZE) - player_left);
		if (diff < player_speed) {
			is_ground = false;
		}
	}

	//�������̓����蔻��
	if (!hit_ceil) {
		std::vector<ELEMENT::ELEMENT_DATA> lift = element->GetLift();
		int hit_lift_num = -1;
		for (int i = 0; i < lift.size(); i++) {
			if (player_right >= lift[i].x && player_left <= lift[i].x + LIFT_SIZE
				&& player_y >= lift[i].y - 45  && player_y <= lift[i].y && player_state != PLAYER_MOVE_STATE::JUMP) {

				if (((lift[i].type == 1 && !(lift[i].lift_vector_y > 0 && is_ground)) || (lift[i].type == 2 && !is_ground)) &&
					(hit_lift_num == -1 || lift[hit_lift_num].y > lift[i].y)) {
					hit_lift_num = i;
				}
			}
		}
		if (hit_lift_num >= 0) {
			player_y = (lift[hit_lift_num].y - MAP_CEllSIZE / 2 + lift[hit_lift_num].lift_vector_y * 4);
			player_x += lift[hit_lift_num].lift_vector_x * 4;
			is_ground = true;
		}
	}

	//�ǂ̔���
	int screen_left = static_cast<int>(-stage->GetScrollX() / MAP_CEllSIZE);
	for (int i = 0; i < stage->GetMapSize().x; i++) {
		for (int j = screen_left; j < screen_left + 20; j++) {
			if (j >= stage->GetMapSize().y) break;
			if (!stage->HitMapDat(i, j) && stage->GetMapData(i, j) != -1) continue;

			float block_left = j * MAP_CEllSIZE;
			float block_right = block_left + MAP_CEllSIZE;
			float block_top = i * MAP_CEllSIZE;
			float block_bottom = block_top + MAP_CEllSIZE;

			if (player_right > block_left && player_left < block_right) {
				if (player_bottom > block_top && player_top < block_bottom) {
					int block_type = stage->GetMapData(i, j);
					int y = static_cast<int>(player_top / MAP_CEllSIZE);
					//������
					if (block_type == -1) {
						player_state = PLAYER_MOVE_STATE::DEAD;
						return;
					}
					if (hit_ceil && !is_ground && y == i) continue;
					//�h�A�̔���
					if ((block_type == 66 || block_type == 67) && move_x > 0) {
						if (fabsf(player_left - block_right) < player_speed) {
							return;
						}
					}
					player_x = old_player_x;
					if (is_heal) {
						player_x -= move_x * player_speed * 2.0f;
					}
					break;
				}
			}
		}
	}

	is_heal = false;
}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="anim">Enum�N���X �A�j���[�V����</param>
/// <param name="compelChange">�����I�ɐ؂�ւ��邩�ǂ���</param>
void PLAYER::ChangeAnimation(PLAYER_ANIM_STATE anim, bool compelChange) {
	int now_anim_type = static_cast<int>(animation_state);	//���̃A�j���[�V����
	int next_anim_type = static_cast<int>(anim);			//�؂�ւ���A�j���[�V����
	
	if (animation_state != anim && player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move || compelChange) {
		if (animation[now_anim_type].priority <= animation[next_anim_type].priority || animation[now_anim_type].endAnim || compelChange) {
			animation_state = anim;
			int anim_type = static_cast<int>(anim);
			animation[anim_type].frame = 0;
			animation[anim_type].type = 0;
			animation[anim_type].phase = 0;
			animation[anim_type].endAnim = false;
		}
	}
}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
void PLAYER::MoveAnimation() {
	//�摜�̐؂�ւ��^�C�~���O�̂Ƃ�
	int type = static_cast<int>(animation_state);
	if (++animation[type].frame % animation[type].switch_frame == 0) {
		animation[type].frame = 0;
		//�O���̃A�j���[�V����
		if (animation[type].phase == 0 && animation[type].type < animation[type].image_num - 1) {
			animation[type].type++;
		}
		//�㔼�̃A�j���[�V����
		else {
			if (animation[type].play_type == 0) {
				animation[type].type--;
			}
			else if (animation[type].play_type == 1) {
				//animation[type].phase = 0;
				animation[type].type = 0;
			}
		}
		//�O���ƌ㔼�̐؂�ւ�
		if (animation[type].type >= animation[type].image_num - 1 || animation[type].type <= 0) {
			if (animation[type].play_type == 0) {
				if (animation[type].phase == 1) {
					animation[type].endAnim = true;
				}
			}
			else if (animation[type].play_type == 1) {
				animation[type].endAnim = true;
			}
			animation[type].phase = (animation[type].phase + 1) % 2;
		}
	}
}

void PLAYER::SetLife(int _life)
{
	//�_���[�W����
	if (life > _life && is_damage) return;
	//�_���[�W
	if (life > _life) {
		//player_state = PLAYER_MOVE_STATE::DAMAGE;
		alpha_time = 120;
		is_damage = true;
		StartJoypadVibration(DX_INPUT_PAD1, 360, 320, -1);
		PlaySoundMem(damageSE, DX_PLAYTYPE_BACK);
	}
	//��
	else {
		is_heal = true;
		PlaySoundMem(healSE, DX_PLAYTYPE_BACK);
	}
	life = _life;
}