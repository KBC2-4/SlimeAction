#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include <math.h>

//中心から240 フック
float map_left, map_right;
float map_top, map_bottom;

/*コンストラクタ*/
Player::Player() {
	player_x = 20.0f;
	player_y = 520.0f;
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
/// プレイヤーの更新
/// </summary>
void Player::Update() {
	clsDx();
	Move();
	JumpMove();
}

/// <summary>
/// プレイヤーの表示
/// </summary>
void Player::Draw()const {
	DrawRotaGraphF((player_x-16), player_y, 1.0, 0.0, image[animation_type], TRUE, move_type);
	//グリッドの表示(デバッグ用)
	//for (int i = 0; i < 32; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xFFFFFF, 2);	//横
	//	DrawLine(i * 80, 0, i * 80,  720,0xFFFFFF, 2);		//縦
	//}

	//座標(デバッグ用)
	/*printfDx("x1: %d, x2: %d\n", (int)(map_left / MAP_CEllSIZE), (int)map_right / MAP_CEllSIZE);
	printfDx("y1: %d, y2: %d\n", (int)(map_top / MAP_CEllSIZE), (int)map_bottom / MAP_CEllSIZE);
	printfDx("x : %d, y : %d\n", (int)(player_x / MAP_CEllSIZE), (int)player_y / MAP_CEllSIZE);*/
	
	//マップチップの座標の表示(デバッグ用)
	/*SetFontSize(40);
	DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));*/
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void Player::Move() {
	//スティック入力の取得
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//移動するとき
	float move_x = input_lx > 0 ? 1.0f : -1.0f;	//移動方向のセット
	if (input_lx < -DEVIATION || input_lx > DEVIATION) {
		move_type = move_x > 0 ? 0 : 1;				//移動向きのセット(0: 右, 1: 左)
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			//アニメーションが前半のとき
			if (animation_phase == 0 || true) {
				player_x += move_x * SPEED;
			}
			//アニメーションが後半のとき
			else {
				player_x += move_x * SPEED / 2;
			}
			player_state = PLAYER_STATE::MOVE;	//ステートをMoveに切り替え
		}
		else {
			//停止ジャンプだった時
			if (jump_mode == 1) {
				player_x += move_x * SPEED / 2;
			}
			//移動ジャンプだった時
			else {
				player_x += move_x * SPEED;
			}
		}
		MoveAnimation();
		STAGE::SetScrollPos(move_type);
	}
	
	//移動してない時
	else {
		//アニメーションを後半へ移行
		if (animation_type > 1) {
			animation_phase = 1;
			MoveAnimation();
		}
		//ジャンプ中じゃないかったらステートを切り替える
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			player_state = PLAYER_STATE::IDLE;	//ステートをIdleに切り替え
		}
	}
	//マップチップの座標のセット
	map_x = (int)roundf(player_x / MAP_CEllSIZE);
	map_y = (int)floorf((player_y + MAP_CEllSIZE / 2) / MAP_CEllSIZE);
	map_left = (player_x - 35);
	map_right = (player_x + 35);
	map_top = (player_y - MAP_CEllSIZE / 2);
	map_bottom = (player_y + MAP_CEllSIZE / 2);
	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::FALL) {
		if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_left / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_y - 1, map_right / MAP_CEllSIZE) != 0) {
				player_x -= SPEED;
			}
			else {
				player_x += SPEED;
			}
		}
		else if(STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_right / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_y - 1, map_left / MAP_CEllSIZE) != 0) {
				player_x += SPEED;
			}
			else {
				player_x -= SPEED;
			}
		}
	}
	else {
		if (STAGE::GetMapDat(map_y - 1, map_left / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_right / MAP_CEllSIZE) != 0) {
				player_x += SPEED;
			}
			else {
				player_x -= SPEED;
			}
		}
		else if (STAGE::GetMapDat(map_y - 1, map_right / MAP_CEllSIZE) != 0) {
			if (STAGE::GetMapDat(map_bottom / MAP_CEllSIZE, map_left / MAP_CEllSIZE) != 0) {
				player_x -= SPEED;
			}
			else {
				player_x += SPEED;
			}
		}
	}
}

void Player::HookMove() {

}

/// <summary>
/// プレイヤーのジャンプ処理
/// </summary>
void Player::JumpMove() {
	static bool is_jump = false;		//ジャンプ中か
	static float jump_y = 0;			//ジャンプの高さ
	static float velocity = 0.0f;	//ジャンプと落下のスピード
	//Aボタンを押したとき
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) {
		//ジャンプ中じゃないとき
		if (player_state != PLAYER_STATE::JUMP && player_state != PLAYER_STATE::FALL) {
			is_jump = true;			//ジャンプ中に移行
			jump_y = player_y - MAP_CEllSIZE; //ジャンプの高さのセット
			velocity = JUMP_VELOCITY;
			//横移動してない時
			if (player_state == PLAYER_STATE::IDLE) {
				jump_mode = 1;
			}
			//横移動してるとき
			else if (player_state == PLAYER_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_STATE::JUMP;
		}
	}
	//ジャンプ中
	if (is_jump) {
		velocity += 0.2f;
		player_y += velocity;
		bool is_block = false;
		if (STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) != 0)
			is_block = true;
		if (STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) != 0 &&
			STAGE::GetMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) != 0)
			is_block = true;
		if (STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_right / MAP_CEllSIZE)) != 0) player_x -= SPEED;
		if (STAGE::GetMapDat((int)(map_top / MAP_CEllSIZE), (int)(map_left / MAP_CEllSIZE)) != 0) player_x += SPEED;

		if (player_y <= jump_y && velocity >= 0 || is_block) {
			is_jump = false;
			velocity = 0;
		}
	}
	//落下中
	else {
		//落下処理
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
		//地面についた時
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

void Player::Throw() {

}

/// <summary>
/// アニメーションの切り替え
/// </summary>
void Player::MoveAnimation() {
	//画像の切り替えタイミングのとき
	if (++animation_frame % ANIMATION_SWITCH_FRAME == 0) {
		//前半のアニメーション
		if (animation_phase == 0) {
			animation_type++;
		}
		//後半のアニメーション
		else {
			animation_type--;
		}
		//前半と後半の切り替え
		if (animation_type >= IMAGE_MAX_NUM - 1 || animation_type <= 0) animation_phase = (animation_phase + 1) % 2;
	}
}

