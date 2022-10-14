#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include <math.h>

//���S����240 �t�b�N


/*�R���X�g���N�^*/
Player::Player() {
	player_x = 20.0f;
	player_y = 550.0f;
	map_x = 0;
	map_y = 0;
	life = 5;
	jump_mode = 0;
	player_state = PLAYER_STATE::IDLE;
	LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, image);
	animation_frame = 0;
	animation_type = 0;
}

/// <summary>
/// �v���C���[�̍X�V
/// </summary>
void Player::Update() {
	Move();
	JumpMove();
}

/// <summary>
/// �v���C���[�̕\��
/// </summary>
void Player::Draw()const {
	DrawRotaGraphF(player_x, player_y, 1.0, 0.0, image[animation_type], TRUE, move_type);

	//�O���b�h�̕\��(�f�o�b�O�p)
	/*for (int i = 0; i < 32; i++) {
		DrawLine(i * 40, 0, i * 40, 720, 0xFFFFFF, 2);
	}*/
}

/// <summary>
/// �v���C���[�̈ړ�
/// </summary>
void Player::Move() {
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//�ړ�����Ƃ�
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		float move_x = input_lx > 0 ? 1.0f : -1.0f;	//�ړ������̃Z�b�g
		if (move_x > 0) move_type = 0;			//�E�ړ��̎�
		else move_type = 1;						//���ړ��̎�
		if (player_state != PLAYER_STATE::JUMP) {
			player_x += move_x;
			player_state = PLAYER_STATE::MOVE;	//�X�e�[�g��Move�ɐ؂�ւ�
		}
		else {
			//��~�W�����v��������
			if (jump_mode == 1) {
				player_x += move_x / 2;
			}
			//�ړ��W�����v��������
			else {
				player_x += move_x;
			}
		}
		MoveAnimation();
	}
	else {
		if (player_state != PLAYER_STATE::JUMP) {
			player_state = PLAYER_STATE::IDLE;	//�X�e�[�g��Idle�ɐ؂�ւ�
		}
	}
	map_x = round(player_x / 40.0f);
	map_y = round(player_y / 40.0f);
}

void Player::HookMove() {

}

/// <summary>
/// �v���C���[�̃W�����v����
/// </summary>
void Player::JumpMove() {
	static int jump_type = 0;
	static int jump_y = 0;
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) {
		if (player_state != PLAYER_STATE::JUMP) {
			jump_type = 1;
			jump_y = player_y - 80;
			if (player_state == PLAYER_STATE::IDLE) {
				jump_mode = 1;
			}
			else if (player_state == PLAYER_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_STATE::JUMP;
		}
	}
	if (jump_type == 1) {
		if (--player_y < jump_y) {
			jump_type = 2;
		}
	}
	else {
		SetFontSize(40);
		DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));
		if (STAGE::GetMapDat(map_y, map_x) == 0) {
			++player_y;
		}
		else {
			player_state = PLAYER_STATE::IDLE;
		}
	}

}

void Player::Throw() {

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
void Player::MoveAnimation() {
	//�摜�̐؂�ւ��^�C�~���O�̂Ƃ�
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
		//�摜�̗v�f�����I�[�o�[�����ꍇ 0�ɖ߂�
		if (++animation_type >= IMAGE_MAX_NUM) animation_type = 0;
	}
}

