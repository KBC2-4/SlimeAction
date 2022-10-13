#include "PLAYER.h"
#include"DxLib.h"




/*コンストラクタ*/
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
/// プレイヤーの更新
/// </summary>
void Player::Update() {
	Move();
	JumpMove();
}

/// <summary>
/// プレイヤーの表示
/// </summary>
void Player::Draw()const {
	//DrawBox(player_x, player_y, player_x + 40, player_y + 40, 0xffffff, TRUE);
	DrawRotaGraph(player_x, player_y, 1.0, 0.0, image[animation_type], TRUE, move_type);
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void Player::Move() {
	//スティック入力の取得
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//誤入力じゃないとき
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		int move_x = input_lx > 0 ? 1 : -1;	//移動方向のセット
		if (move_x > 0) move_type = 0;		//右移動の時
		else move_type = 1;					//左移動の時
		player_x += move_x;
		player_state = PLAYER_STATE::MOVE;	//ステートの切り替え
		MoveAnimation();
	}
	else {
		player_state = PLAYER_STATE::IDLE;	//ステートの切り替え
	}
}

void Player::HookMove() {

}

void Player::JumpMove() {

}

void Player::Throw() {

}

/// <summary>
/// アニメーションの切り替え
/// </summary>
void Player::MoveAnimation() {
	//画像の切り替えタイミングのとき
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
		//画像の要素数がオーバーした場合 0に戻す
		if (++animation_type >= IMAGE_MAX_NUM) animation_type = 0;
	}
}

