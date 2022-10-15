#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include <math.h>

//���S����240 �t�b�N


/*�R���X�g���N�^*/
Player::Player() {
	player_x = 20.0f;
	player_y = 500.0f;
	map_x = 0;
	map_y = 0;
	life = 5;
	jump_mode = 0;
	player_state = PLAYER_STATE::IDLE;
	LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, image);
	animation_frame = 0;
	animation_type = 0;
	animation_phase = 0;
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
	//for (int i = 0; i < 32; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xFFFFFF, 2);	//��
	//	DrawLine(i * 80, 0, i * 80,  720,0xFFFFFF, 2);		//�c
	//}
	
	//�}�b�v�`�b�v�̍��W�̕\��(�f�o�b�O�p)
	/*SetFontSize(40);
	DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));*/
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
			//�A�j���[�V�������O���̂Ƃ�
			if (animation_phase == 0 || true)
				player_x += move_x * SPEED;
			//�A�j���[�V�������㔼�̂Ƃ�
			else
				player_x += move_x * SPEED / 2;
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
		MoveAnimation();
	}
	//�ړ����ĂȂ���
	else {
		//�A�j���[�V�������㔼�ֈڍs
		if (animation_type > 1) {
			animation_phase = 1;
			MoveAnimation();
		}
		//�W�����v������Ȃ���������X�e�[�g��؂�ւ���
		if (player_state != PLAYER_STATE::JUMP) {
			player_state = PLAYER_STATE::IDLE;	//�X�e�[�g��Idle�ɐ؂�ւ�
		}
	}
	//�}�b�v�`�b�v�̍��W�̃Z�b�g
	map_x = round(player_x / (float)MAP_CEllSIZE);
	map_y = round(player_y / (float)MAP_CEllSIZE);
}

void Player::HookMove() {

}

/// <summary>
/// �v���C���[�̃W�����v����
/// </summary>
void Player::JumpMove() {
	static bool isJump = false;	//�W�����v����
	static int jump_y = 0;		//�W�����v�̍���
	//A�{�^�����������Ƃ�
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) {
		//�W�����v������Ȃ��Ƃ�
		if (player_state != PLAYER_STATE::JUMP) {
			isJump = true;			//�W�����v���Ɉڍs
			jump_y = player_y - (float)MAP_CEllSIZE; //�W�����v�̍����̃Z�b�g
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
	if (isJump) {
		if (--player_y < jump_y) {
			isJump = false;
		}
	}
	//������
	else {
		//��������
		if (STAGE::GetMapDat(map_y, map_x) == 0) {
			++player_y;
		}
		//�n�ʂɂ�����
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
		//�O���̃A�j���[�V����
		if (animation_phase == 0) {
			animation_type++;
		}
		//�㔼�̃A�j���[�V����
		else {
			animation_type--;
		}
		//�O���ƌ㔼�̐؂�ւ�
		if (animation_type >= IMAGE_MAX_NUM - 1 || animation_type <= 0) animation_phase = (animation_phase + 1) % 2;
	}
}

