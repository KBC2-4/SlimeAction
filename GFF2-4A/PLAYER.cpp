#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include <math.h>

//���S����240 �t�b�N

/*�R���X�g���N�^*/
PLAYER::PLAYER() {
	player_x = 20.0f;
	player_y = 520.0f;
	map_x = 0;
	map_y = 0;
	life = 5;
	jump_mode = 0;
	player_state = PLAYER_STATE::IDLE;
	LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, move_images);
	LoadDivGraph("Resource/Images/Player/Slimest.png", 10, 10, 1, 80, 80, idle_images);
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
void PLAYER::Update() {
	clsDx();
	Move();
	JumpMove();
}

/// <summary>
/// �v���C���[�̕\��
/// </summary>
void PLAYER::Draw()const {
	if (animation_mode == 0)
		DrawRotaGraphF(player_x, player_y, 1.0, 0.0, idle_images[animation_type[0]], TRUE, move_type);
	else
		DrawRotaGraphF(player_x, player_y, 1.0, 0.0, move_images[animation_type[1]], TRUE, move_type);
	//�O���b�h�̕\��(�f�o�b�O�p)
	//for (int i = 0; i < 32; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xFFFFFF, 2);	//��
	//	DrawLine(i * 80, 0, i * 80,  720,0xFFFFFF, 2);		//�c
	//}

	//���W(�f�o�b�O�p)
	/*printfDx("x1: %d, x2: %d\n", (int)(map_left / MAP_CEllSIZE), (int)map_right / MAP_CEllSIZE);
	printfDx("y1: %d, y2: %d\n", (int)(map_top / MAP_CEllSIZE), (int)map_bottom / MAP_CEllSIZE);
	printfDx("x : %d, y : %d\n", (int)(player_x / MAP_CEllSIZE), (int)player_y / MAP_CEllSIZE);*/
	
	//�}�b�v�`�b�v�̍��W�̕\��(�f�o�b�O�p)
	/*SetFontSize(40);
	DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));*/
}

/// <summary>
/// �v���C���[�̈ړ�
/// </summary>
void PLAYER::Move() {
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//�ړ�����Ƃ�
	float move_x = input_lx > 0 ? 1.0f : -1.0f;	//�ړ������̃Z�b�g
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		animation_mode = 1;
		move_type = move_x > 0 ? 0 : 1;				//�ړ������̃Z�b�g(0: �E, 1: ��)
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			//�A�j���[�V�������O���̂Ƃ�
			if (animation_phase == 0 || true) {
				player_x += move_x * SPEED;
			}
			//�A�j���[�V�������㔼�̂Ƃ�
			else {
				player_x += move_x * SPEED / 2;
			}
			player_state = PLAYER_STATE::MOVE;	//�X�e�[�g��Move�ɐ؂�ւ�
		}
		else {
			//��~�W�����v��������
			if (jump_mode == 1) {
				player_x += move_x * SPEED / 2;
			}
			//�ړ��W�����v��������
			else {
				player_x += move_x * SPEED;
			}
		}
		MoveAnimation(1);
		STAGE::SetScrollPos(move_x);
	}
	
	//�ړ����ĂȂ���
	else {
		//�A�j���[�V�������㔼�ֈڍs
		if (animation_type[1] > 1) {
			animation_phase[1] = 1;
			MoveAnimation(1);
		}
		else {
			animation_mode = 0;
			MoveAnimation(0);
		}
		//�W�����v������Ȃ���������X�e�[�g��؂�ւ���
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			player_state = PLAYER_STATE::IDLE;	//�X�e�[�g��Idle�ɐ؂�ւ�
		}
	}
	//�}�b�v�`�b�v�̍��W�̃Z�b�g
	map_x = (int)roundf((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE);
	map_y = (int)floorf((player_y + MAP_CEllSIZE / 2) / MAP_CEllSIZE);
	map_left = (player_x - STAGE::GetScrollX() - 35);
	map_right = (player_x - STAGE::GetScrollX() + 35);
	map_top = (player_y - MAP_CEllSIZE / 2);
	map_bottom = (player_y + MAP_CEllSIZE / 2);
	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::FALL) {
		if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_left / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_y - 1, map_right / MAP_CEllSIZE) != 0) {
				player_x -= SPEED * 2;
			}
			else {
				player_x += SPEED * 2;
			}
		}
		else if(STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_right / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_y - 1, map_left / MAP_CEllSIZE) != 0) {
				player_x += SPEED * 2;
			}
			else {
				player_x -= SPEED * 2;
			}
		}
	}
	else {
		if (STAGE::GetMapDat(map_y - 1, map_left / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_right / MAP_CEllSIZE) != 0) {
				player_x += SPEED * 2;
			}
			else {
				player_x -= SPEED * 2;
			}
		}
		else if (STAGE::GetMapDat(map_y - 1, map_right / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_left / MAP_CEllSIZE) != 0) {
				player_x -= SPEED * 2;
			}
			else {
				player_x += SPEED * 2;
			}
		}
	}
}

void PLAYER::HookMove() {

}

/// <summary>
/// �v���C���[�̃W�����v����
/// </summary>
void PLAYER::JumpMove() {
	static bool is_jump = false;		//�W�����v����
	static float jump_y = 0;			//�W�����v�̍���
	static float velocity = 0.0f;	//�W�����v�Ɨ����̃X�s�[�h
	//A�{�^�����������Ƃ�
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) {
		//�W�����v������Ȃ��Ƃ�
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			is_jump = true;			//�W�����v���Ɉڍs
			jump_y = player_y - MAP_CEllSIZE; //�W�����v�̍����̃Z�b�g
			velocity = JUMP_VELOCITY;
			//���ړ����ĂȂ���
			if (player_state == PLAYER_STATE::IDLE) {
				jump_mode = 1;
			}
			//���ړ����Ă�Ƃ�
			else if (player_state == PLAYER_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_STATE::JUMP;
		}
	}
	//�W�����v��
	if (is_jump) {
		velocity += 0.2f;
		player_y += velocity;
		bool is_block = false;
		if (STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE)) != 0)
			is_block = true;
		if (STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)((player_x - STAGE::GetScrollX()) / MAP_CEllSIZE)) != 0)
			is_block = true;
		if (STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) != 0) player_x -= SPEED * 2;
		if (STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) != 0) player_x += SPEED * 2;

		if (player_y <= jump_y && velocity >= 0 || is_block) {
			is_jump = false;
			velocity = 0;
		}
	}
	//������
	else {
		//��������
		bool is_ground = false;
		if (STAGE::GetMapDat((int)(map_bottom / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) == 0) is_ground = true;
		if (STAGE::GetMapDat((int)(map_bottom / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) == 0) is_ground = true;
		if (!is_ground) {
			velocity += 0.2f;
			player_y += velocity;
			player_state = PLAYER_STATE::FALL;
		}
		//�n�ʂɂ�����
		else {
			if (player_state == PLAYER_STATE::FALL || player_state == PLAYER_STATE::JUMP) {
				float new_y = (float)(map_y - 1) * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				if (fabsf(player_y - new_y) <= 10) {
					player_y = new_y;
					velocity = 0;
					player_state = PLAYER_STATE::IDLE;
				}
				else {
					if (move_type == 0)
						player_x -= SPEED;
					else
						player_x += SPEED;
				}
			}
		}
	}

}

void PLAYER::Throw() {

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
void PLAYER::MoveAnimation(int type) {
	//�摜�̐؂�ւ��^�C�~���O�̂Ƃ�
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
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

