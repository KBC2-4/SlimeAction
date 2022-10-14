#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include <math.h>

//中心から240 フック


/*コンストラクタ*/
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
	DrawRotaGraphF(player_x, player_y, 1.0, 0.0, image[animation_type], TRUE, move_type);

	//グリッドの表示(デバッグ用)
	/*for (int i = 0; i < 32; i++) {
		DrawLine(i * 40, 0, i * 40, 720, 0xFFFFFF, 2);
	}*/
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void Player::Move() {
	//スティック入力の取得
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//移動するとき
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		float move_x = input_lx > 0 ? 1.0f : -1.0f;	//移動方向のセット
		if (move_x > 0) move_type = 0;			//右移動の時
		else move_type = 1;						//左移動の時
		if (player_state != PLAYER_STATE::JUMP) {
			player_x += move_x;
			player_state = PLAYER_STATE::MOVE;	//ステートをMoveに切り替え
		}
		else {
			//停止ジャンプだった時
			if (jump_mode == 1) {
				player_x += move_x / 2;
			}
			//移動ジャンプだった時
			else {
				player_x += move_x;
			}
		}
		MoveAnimation();
	}
	else {
		if (player_state != PLAYER_STATE::JUMP) {
			player_state = PLAYER_STATE::IDLE;	//ステートをIdleに切り替え
		}
	}
	map_x = round(player_x / 40.0f);
	map_y = round(player_y / 40.0f);
}

void Player::HookMove() {

}

/// <summary>
/// プレイヤーのジャンプ処理
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
/// アニメーションの切り替え
/// </summary>
void Player::MoveAnimation() {
	//画像の切り替えタイミングのとき
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
		//画像の要素数がオーバーした場合 0に戻す
		if (++animation_type >= IMAGE_MAX_NUM) animation_type = 0;
	}
}

