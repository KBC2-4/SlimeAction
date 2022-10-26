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
	is_hook_move = false;
	player_state = PLAYER_MOVE_STATE::IDLE;
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
void PLAYER::Update(Element* element) {
	clsDx();
	Move();
	JumpMove();
	HookMove(element);
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
			DrawRotaGraphF(player_x, player_y, 1.0, 0.0, now_image, TRUE, move_type);
		else {
			DrawRotaGraph3F(player_x, player_y, 40, 80,
				1, hook_distance / (MAP_CEllSIZE / 2), (double)hook_angle,
				now_image, TRUE, move_type);
		}
	}
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
	if (is_hook_move) return;
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//�ړ�����Ƃ�
	float move_x = input_lx > 0 ? 1.0f : -1.0f;	//�ړ������̃Z�b�g
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
			//��~�W�����v��������
			if (jump_mode == 1) {
				player_x += move_x * SPEED / 2;
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

void PLAYER::HookMove(Element* element) {
	static float move_x = 0;
	static float move_y = 0;
	static bool end_move = false;
	bool is_hook = false;
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) {
		float hook_y, hook_x;
		float min_distance = HOOK_MAX_DISTANCE;
		std::vector<Element::ELEMENT_DATA> hook_pos = element->GetHookPos();
		for (int i = 0; i < hook_pos.size(); i++) {
			Element::ELEMENT_DATA pos = hook_pos[i];
			float diff_x = pos.x - (player_x - STAGE::GetScrollX());
			float diff_y = pos.y - player_y;
			float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
			if (distance <= min_distance) {
				float angle = atan2f(diff_y, diff_x);
				move_x = cosf(angle) * SPEED * 3;
				move_y = sinf(angle) * SPEED * 3;
				float x = player_x - STAGE::GetScrollX();
				float y = player_y;
				while (!STAGE::HitMapDat(y / MAP_CEllSIZE, x / MAP_CEllSIZE)) {
					x += move_x;
					y += move_y;
				}
				int hook_map_x = x / MAP_CEllSIZE;
				int hook_map_y = y / MAP_CEllSIZE;
				if (STAGE::GetMapDat(hook_map_y, hook_map_x) != 70) {
					continue;
				}

				min_distance = distance;
				hook_x = pos.x;
				hook_y = pos.y;
				is_hook = true;
			}
		}
		if (is_hook) {
			if (!end_move) {
				float y = hook_y - player_y;
				float x = hook_x - (player_x - STAGE::GetScrollX());
				if (!is_hook_move) {
					hook_angle = atan2f(y, x) + 90.0f * (DX_PI_F / 180.0f);
					move_x = cosf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					move_y = sinf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					jump_move_x = move_x > 0 ? 1 : -1;
					jump_mode == 2;
				}
				hook_distance = sqrt(x * x + y * y);
				if (hook_distance > 40) {
					player_x += move_x;
					player_y += move_y;
					Scroll(jump_move_x);
				}
				else end_move = true;
				is_hook_move = true;
			}
			else {
				is_hook_move = false;
				player_state = PLAYER_MOVE_STATE::HOOK;
				player_x = hook_x + STAGE::GetScrollX();
				player_y = hook_y;
			}
		}
	}
	if (!is_hook) {
		end_move = false;
		is_hook_move = false;
		if (player_state == PLAYER_MOVE_STATE::HOOK) {
			player_y += 1;
			player_state = PLAYER_MOVE_STATE::IDLE;
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
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) {
		//�W�����v������Ȃ��Ƃ�
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) {
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
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
		int type = static_cast<int>(animation_state);
		//�O���̃A�j���[�V����
		if (animation_phase[type] == 0) {
			animation_type[type]++;
		}
		//�㔼�̃A�j���[�V����
		else {
			(animation_type[type])--;
		}
		//�O���ƌ㔼�̐؂�ւ�
		if (animation_type[type] >= IMAGE_MAX_NUM - 1 || animation_type[type] <= 0) animation_phase[type] = (animation_phase[type] + 1) % 2;
	}
}

