#include "PLAYER.h"
#include"DxLib.h"




/*�R���X�g���N�^*/
Player::Player() {
	player_x = 20;
	player_y = 600;
	map_x = 0;
	map_y = 0;
	life = 5;
	player_state = PLAYER_STATE::IDLE;
	LoadDivGraph("Resource/Images/Player/Slime.png", 5, 5, 1, 40, 40, image);
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
	//DrawBox(player_x, player_y, player_x + 40, player_y + 40, 0xffffff, TRUE);
	DrawRotaGraph(player_x, player_y, 1.0, 0.0, image[animation_type], TRUE, move_type);
}

/// <summary>
/// �v���C���[�̈ړ�
/// </summary>
void Player::Move() {
	//�X�e�B�b�N���͂̎擾
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//����͂���Ȃ��Ƃ�
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		int move_x = input_lx > 0 ? 1 : -1;	//�ړ������̃Z�b�g
		if (move_x > 0) move_type = 0;		//�E�ړ��̎�
		else move_type = 1;					//���ړ��̎�
		player_x += move_x;
		player_state = PLAYER_STATE::MOVE;	//�X�e�[�g�̐؂�ւ�
		MoveAnimation();
	}
	else {
		player_state = PLAYER_STATE::IDLE;	//�X�e�[�g�̐؂�ւ�
	}
}

void Player::HookMove() {

}

void Player::JumpMove() {

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

