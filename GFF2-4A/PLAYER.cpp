#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include "Element.h"
#define _USE_MATH_DEFINES
#include <math.h>

//���S����240 �t�b�N

float PLAYER::player_x, PLAYER::player_y;

/*�R���X�g���N�^*/
PLAYER::PLAYER() {
	player_x = 20.0f;
	player_y = 520.0f;
	rebound_x = SPEED;
	map_x = 0;
	map_y = 0;
	life = 5;
	jump_mode = 0;
	jump_move_x = 0;
	jump_request = false;
	is_hook_move = false;
	player_state = PLAYER_MOVE_STATE::IDLE;
	// �����ʒu�͎��̐^�����獶������45�x�X�����ʒu
		x = CLENGTH / b;
		// �������x�͂O
		speed = 0;
	if (LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, images[1]) == -1) {
		throw "Resource/Images/Player/Slime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Slimest.png", 10, 10, 1, 80, 80, images[0]) == -1) {
		throw "Resource/Images/Player/Slimest.png";
	}
	animation_state = PLAYER_ANIM_STATE::IDLE;
	animation_frame = 0;
	animation_mode = 0;
	animation_type[0] = 0;
	animation_type[1] = 0;
	animation_phase[0] = 0;
	animation_phase[1] = 0;
}

/// <summary>
/// �v���C���[�̍X�V
/// </summary>
void PLAYER::Update(ELEMENT* element) {
	clsDx();
	Move();
	JumpMove();
	HookMove(element);
	Throw();
	HitBlock();

	//��ʒ[�̔���
	if (player_left <= 0) player_x = 40;
	if (player_right + STAGE::GetScrollX() >= 1280) player_x = 1240;

	//�`�悷��摜�̃Z�b�g
	int image_type = 0;
	if (player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		image_type = static_cast<int>(animation_state);
	}
	now_image = images[image_type][animation_type[image_type]];
}

/// <summary>
/// �v���C���[�̕\��
/// </summary>
void PLAYER::Draw()const {
	//�v���C���[�̕\��
	if (player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		DrawRotaGraphF(player_x, player_y, 1.0, 0.0, now_image, TRUE, move_type);
	}
	else {
		if (player_state == PLAYER_MOVE_STATE::HOOK) 
			DrawRotaGraphF(hook_x + STAGE::GetScrollX() + nx, hook_y + ny, 1.0, 0.0, now_image, TRUE, move_type);
		else {
			DrawRotaGraph3F(player_x, player_y, 40, 80,
				1, hook_distance / (MAP_CEllSIZE / 2), (double)hook_angle,
				now_image, TRUE, move_type);
		}
	}
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_THUMB) {
		for (int i = 0; i < 100; i++) {
			DrawCircle(throw_x[i], throw_y[i], 10, 0xFFFFFF, TRUE);
		}
	}
	else {
		DrawCircle(throw_x[0], throw_y[0], 10, 0xFFFFFF, TRUE);
	}

	printfDx("hook: %f %f\n", hook_x, hook_y);
	printfDx("input.lx: %d\n", PAD_INPUT::GetPadThumbLX());

	//�O���b�h�̕\��(�f�o�b�O�p)
	//for (int i = 0; i < 128; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xFFFFFF, 2);	//��
	//	DrawLine(i * 80 + STAGE::GetScrollX(), 0, i * 80 + STAGE::GetScrollX(),  720,0xFFFFFF, 2);		//�c
	//}

	//���W(�f�o�b�O�p)
	/*printfDx("x1: %d, x2: %d\n", (int)(player_left / MAP_CEllSIZE), (int)player_right / MAP_CEllSIZE);
	printfDx("y1: %d, y2: %d\n", (int)(player_top / MAP_CEllSIZE), (int)player_bottom / MAP_CEllSIZE);
	printfDx("x : %d, y : %d\n", (int)(player_x / MAP_CEllSIZE), (int)player_y / MAP_CEllSIZE);*/

	//�}�b�v�`�b�v�̍��W�̕\��(�f�o�b�O�p)
	/*SetFontSize(40);
	DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));*/
}

/// <summary>
/// �v���C���[�̈ړ�
/// </summary>
void PLAYER::Move() {
	if (is_hook_move || player_state == PLAYER_MOVE_STATE::HOOK) return;
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//�ړ�����Ƃ�
	move_x = input_lx > 0 ? 1.0f : -1.0f;	//�ړ������̃Z�b�g
	if ((input_lx < -DEVIATION || input_lx > DEVIATION) && player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		animation_state = PLAYER_ANIM_STATE::MOVE;
		animation_mode = 1;							//�A�j���[�V�����̐؂�ւ�
		move_type = move_x > 0 ? 0 : 1;				//�ړ������̃Z�b�g(0: �E, 1: ��)
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) {
			//�A�j���[�V�������O���̂Ƃ�
			if (animation_phase == 0 || true) {
				player_x += move_x * SPEED;
			}
			//�A�j���[�V�������㔼�̂Ƃ�
			else {
				player_x += move_x * SPEED / 2;
			}
			jump_move_x = move_x;
			player_state = PLAYER_MOVE_STATE::MOVE;	//�X�e�[�g��Move�ɐ؂�ւ�
		}
		else {
			if (jump_move_x == 0) jump_move_x = move_x;
			move_type = jump_move_x > 0 ? 0 : 1;
			//��~�W�����v��������
			if (jump_mode == 1) {
				player_x += jump_move_x * SPEED / 2;
			}
			//�ړ��W�����v��������
			else {
				move_type = jump_move_x > 0 ? 0 : 1;
				//�W�����v���ɔ��Ε����Ɉړ�����Ƃ�
				if (jump_move_x != move_x) {
					player_x += jump_move_x * SPEED / 2;
				}
				else {
					player_x += jump_move_x * SPEED;
				}
			}
		}
		MoveAnimation();
		Scroll(move_x);
	}

	//�ړ����ĂȂ���
	else {
		move_x = 0;
		//�ړ��A�j���[�V�������㔼�ֈڍs
		if (animation_type[1] > 1) {
			animation_phase[1] = 1;
			MoveAnimation();
		}
		//�ړ��A�j���[�V�������I�������A�C�h���A�j���[�V�����̍Đ�
		else {
			animation_state = PLAYER_ANIM_STATE::IDLE;
			animation_mode = 0;
			MoveAnimation();
		}
		//�W�����v������Ȃ���������X�e�[�g��؂�ւ���
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && 
			player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
			jump_move_x = 0;
			player_state = PLAYER_MOVE_STATE::IDLE;	//�X�e�[�g��Idle�ɐ؂�ւ�
		}
	}
}

void PLAYER::Scroll(float move_x) {
	//�X�N���[���̏���
	bool isScroll = false;
	//�v���C���[�̈ʒu�����S��������
	if (move_x > 0 && player_x >= 680 || move_x < 0 && player_x <= 600) {
		//�X�N���[�����[�܂ōs���ĂȂ���
		if (!(isScroll = STAGE::SetScrollPos(move_x))) {
			//�v���C���[�̈ʒu�𒆐S�ɖ߂�
			rebound_x = SPEED * 2;
			player_x -= move_x * rebound_x;
		}
	}
	//�X�N���[�����ĂȂ���
	if (!isScroll) {
		rebound_x = SPEED; //�����͂�ύX
	}
}

/// <summary>
/// �t�b�N�̈ړ�����
/// </summary>
void PLAYER::HookMove(ELEMENT* element) {
	//�t�b�N�̈ړ�����
	static float move_x = 0;
	static float move_y = 0;
	//�t�b�N�܂ł̈ړ��I������
	static bool end_move = false;
	//�߂��Ƀt�b�N�����邩�ǂ���
	bool is_hook = false;
	
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	
	
	//B�{�^���������Ƃ�
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) {
		//�t�b�N�̍��W
		//float hook_y, hook_x;
		//�t�b�N�܂ł̋���
		float min_distance = HOOK_MAX_DISTANCE;
		
		//�t�b�N�̈ʒu
		std::vector<ELEMENT::ELEMENT_DATA> hook_pos = element->GetHookPos();
		for (int i = 0; i < hook_pos.size(); i++) {
			ELEMENT::ELEMENT_DATA pos = hook_pos[i];
			//�����v�Z
			float diff_x = pos.x - (player_x - STAGE::GetScrollX());
			float diff_y = pos.y - player_y;
			float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
			//�������ŒZ�������߂��Ƃ�
			if (distance <= min_distance) {
				//�t�b�N�̊p�x
				float angle = atan2f(diff_y, diff_x);
				//�ړ��̌v�Z
				move_x = cosf(angle) * SPEED * 3;
				move_y = sinf(angle) * SPEED * 3;
				//�v���C���[�̌��݂̈ʒu
				float x = player_x - STAGE::GetScrollX();
				float y = player_y;
				//�t�b�N�܂ł̈ړ��o�H�ɏ�Q�����Ȃ���
				while (!STAGE::HitMapDat(y / MAP_CEllSIZE, x / MAP_CEllSIZE)) {
					x += move_x;
					y += move_y;
				}
				//�z��ɕϊ�
				int hook_map_x = x / MAP_CEllSIZE;
				int hook_map_y = y / MAP_CEllSIZE;
				//��Q��������ꍇ�͈ړ������Ȃ�
				if (STAGE::GetMapDat(hook_map_y, hook_map_x) != 70) {
					continue;
				}
				//�ŒZ�����̍X�V
				min_distance = distance;
				//�t�b�N�̍��W�̍X�V
				hook_x = pos.x;
				hook_y = pos.y;
				//�t�b�N���������������true
				is_hook = true;
			}
		}
		//�t�b�N������������
		if (is_hook) {
			//�ړ����̎�
			if (!end_move) {
				//�t�b�N�܂ł̋����̌v�Z
				float y = hook_y - player_y;
				float x = hook_x - (player_x - STAGE::GetScrollX());
				hook_distance = sqrt(x * x + y * y);
				//�t�b�N�ړ����ĂȂ���
				if (!is_hook_move) {
					//�p�x�̌v�Z
					hook_angle = atan2f(y, x) + 90.0f * (DX_PI_F / 180.0f);
					//�ړ������̌v�Z
					move_x = cosf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					move_y = sinf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					//�����I�ȓz
					jump_move_x = move_x > 0 ? 1 : -1;
					jump_mode == 2;
				}
				//�t�b�N�ɂ��ĂȂ���
				if (hook_distance > 40) {
					player_x += move_x;
					player_y += move_y;
					Scroll(jump_move_x);
				}
				//�t�b�N�ɂ�����ړ������̏I��
				else end_move = true;
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
				//player_x = hook_x + STAGE::GetScrollX();
				//player_y = hook_y;

				// �����ɏ]���đ��x�����Z
				speed += -mass * (G / 60) * sin(x / LENGTH);
				x += speed;
				// �������_�Ƃ����ꍇ�̂Ԃ牺�����Ă��镨�̍��W���Z�o
				angle = x / LENGTH + PI / 2.0;
				nx = cos(angle) * LENGTH;
				ny = sin(angle) * LENGTH;
				if (speed >= 0) {
					if (input_lx < -15000) {
						speed += 0.05;
					}
					if (input_lx > 15000) {
						speed -= 0.09;
					}
				}
				else if (speed < 0) {
					if (input_lx < -15000) {
						speed += 0.09;
					}
					if (input_lx > 15000) {
						speed -= 0.05;
					}
				}
				if (hook_y + ny < hook_y) {
					ny = 0;
					speed = 0.0;
				}
				if (input_lx < 15000 && input_lx >- 15000) {	//�����Ă���Ԃ͊p�x�������A�X�s�[�h��x�����Ă���
					if (speed > 0)speed -= 0.05;
					if (speed < 0)speed += 0.05;
				}
			}
		}
	}
	//�t�b�N��������Ȃ�������
	if (!is_hook) {
		//������
		end_move = false;
		is_hook_move = false;
		if (player_state == PLAYER_MOVE_STATE::HOOK) {
			player_x = hook_x + STAGE::GetScrollX() + nx;
			player_y = hook_y + ny;
			player_y += 1;
			jump_request = true;
			player_state = PLAYER_MOVE_STATE::JUMP;
		}
	}
}

/// <summary>
/// �v���C���[�̃W�����v����
/// </summary>
void PLAYER::JumpMove() {
	if (CheckHitKey(KEY_INPUT_SPACE))return;		//�f�o�b�O�p
	static bool is_jump = false;		//�W�����v����
	static float jump_y = 0;			//�W�����v�̍���
	static float velocity = 0.0f;	//�W�����v�Ɨ����̃X�s�[�h
	//A�{�^�����������Ƃ�
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A || jump_request) {
		//�W�����v������Ȃ��Ƃ�
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && player_state != PLAYER_MOVE_STATE::HOOK
			|| jump_request) {
			jump_request = false;
			is_jump = true;			//�W�����v���Ɉڍs
			jump_y = player_y - MAP_CEllSIZE; //�W�����v�̍����̃Z�b�g
			velocity = JUMP_VELOCITY;
			//���ړ����ĂȂ���
			if (player_state == PLAYER_MOVE_STATE::IDLE) {
				jump_mode = 1;
			}
			//���ړ����Ă�Ƃ�
			else if (player_state == PLAYER_MOVE_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_MOVE_STATE::JUMP;
		}
	}
	//�W�����v��
	if (is_jump) {
		velocity += 0.2f;
		player_y += velocity;
		bool is_block = false;
		if (STAGE::HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_y / MAP_CEllSIZE), (int)((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE)))
			is_block = true;
		if (STAGE::HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_y / MAP_CEllSIZE), (int)((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE)))
			is_block = true;
		if (STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE))) player_x -= rebound_x;
		if (STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE))) player_x += rebound_x;

		if (player_y <= jump_y && velocity >= 0 || is_block || player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
			is_jump = false;
			velocity = 0;
		}
	}
	//������
	else {
		//�n�ʂ̔���
		bool is_ground = false;
		if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) == 0) is_ground = true;
		if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) == 0) is_ground = true;
		if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) is_ground = true;
		//�n�ʂ���Ȃ����͗���
		if (!is_ground) {
			velocity += 0.2f;
			player_y += velocity;
			player_state = PLAYER_MOVE_STATE::FALL;
		}
		//�n�ʂɂ�����
		else {
			if ((player_state == PLAYER_MOVE_STATE::FALL || player_state == PLAYER_MOVE_STATE::JUMP) && !is_hook_move) {
				float new_y = (float)(map_y - 1) * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				if (fabsf(player_y - new_y) <= 10) {
					player_y = new_y;
					velocity = 0;
					player_state = PLAYER_MOVE_STATE::IDLE;
				}
				else {
					bool is_wall = false;
					if (move_x < 0 &&
						STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
						STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) == 0) is_wall = true;
					if (move_x > 0 &&
						STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
						STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) == 0) is_wall = true;

					if (!is_wall) {
						player_y = new_y;
					}

					if (move_type == 0)
						player_x -= SPEED;
					else
						player_x += SPEED;
				}
			}
			if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
				velocity = 0;
			}
		}
	}

}

void PLAYER::Throw() {
	static bool push = false;
	static int i = 0;
	//�O���̌v�Z
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_THUMB) {
		push = true;
		i = 0;
		throw_rad = atan2(PAD_INPUT::GetPadThumbRY(), PAD_INPUT::GetPadThumbRX());
		for (int j = 0; j < 100; j++) {
			//�����x�̌v�Z
			int V = 40 - 9.8 * (j * 0.1);
			//���W
			throw_x[j] = 40 * cos(throw_rad) * (j * 0.1);
			throw_y[j] = 9.8 * pow(j * 0.1, 2) / 2 - V * sin(throw_rad) * (j * 0.1);
			if (j > 0) {
				throw_x[j] += throw_x[j - 1];
				throw_y[j] += throw_y[j - 1];
			}
			else {
				throw_x[j] += player_x;
				throw_y[j] += player_y;
			}
		}
	}
	else {
		//�����鏈��
		if (push) {
			int V = 40 - 9.8 * (i * 0.1);
			throw_x[0] += 40 * cos(throw_rad) * (i * 0.1);
			throw_y[0] -= -9.8 * pow(i * 0.1, 2) / 2 + V * sin(throw_rad) * (i * 0.1);
			if (++i >= 100) {
				i = 0;
				push = false;
			}
		}
	}
	/*if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_THUMB) {
		int V = 30 - 0.1 * (i * 0.1);
		x += 30 * cos(rad) * (i * 0.1);
		y -= -9.8 * pow(i * 0.1, 2) / 2 + V * sin(rad) * (i * 0.1);
		DrawCircle(x, y, 10, 0xFFFFFF, TRUE);
		i++;
	}*/
}

/// <summary>
/// ���ړ��̓����蔻��
/// </summary>
void PLAYER::HitBlock() {
	//�}�b�v�`�b�v�̍��W�̃Z�b�g
	map_x = (int)roundf((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE);
	map_y = (int)floorf((player_y + MAP_CEllSIZE / 2) / MAP_CEllSIZE);
	player_left = (player_x - STAGE::GetScrollX() - 35);
	player_right = (player_x - STAGE::GetScrollX() + 35);
	player_top = (player_y - MAP_CEllSIZE / 2);
	player_bottom = (player_y + MAP_CEllSIZE / 2);

	if (player_state == PLAYER_MOVE_STATE::JUMP || player_state == PLAYER_MOVE_STATE::FALL) {
		if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE))) {
			if (STAGE::HitMapDat(map_y - 1, (int)(player_right / MAP_CEllSIZE))) {
				player_x -= rebound_x;
			}
			else {
				player_x += rebound_x;
			}
		}
		else if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE))) {
			if (STAGE::HitMapDat(map_y - 1, (int)(player_left / MAP_CEllSIZE))) {
				player_x += rebound_x;
			}
			else {
				player_x -= rebound_x;
			}
		}
	}
	else {
		if (STAGE::HitMapDat(map_y - 1, (int)(player_left / MAP_CEllSIZE))) {
			if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE))) {
				player_x += rebound_x;
			}
			else {
				player_x -= rebound_x;
			}
		}
		else if (STAGE::HitMapDat(map_y - 1, (int)(player_right / MAP_CEllSIZE))) {
			if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE))) {
				player_x -= rebound_x;
			}
			else {
				player_x += rebound_x;
			}
		}
	}
}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
void PLAYER::MoveAnimation() {
	//�摜�̐؂�ւ��^�C�~���O�̂Ƃ�
	int type = static_cast<int>(animation_state);
	if (++animation_frame % animation_switch_frame[type] == 0) {
		//�O���̃A�j���[�V����
		if (animation_phase[type] == 0) {
			animation_type[type]++;
		}
		//�㔼�̃A�j���[�V����
		else {
			if (animation_play_type[type] == 0) {
				animation_type[type]--;
			}
			else {
				animation_phase[type] = 0;
				animation_type[type] = 1;
			}
		}
		//�O���ƌ㔼�̐؂�ւ�
		if (animation_type[type] >= animation_image_num[type] - 1 || animation_type[type] <= 0) {
			animation_phase[type] = (animation_phase[type] + 1) % 2;
		}
	}
}

