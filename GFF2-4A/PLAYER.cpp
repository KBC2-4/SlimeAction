#include "PLAYER.h"
#include"DxLib.h"
#include "STAGE.h"
#include "Element.h"
#define _USE_MATH_DEFINES
#include <math.h>

//中心から240 フック

float PLAYER::player_x, PLAYER::player_y;

/*コンストラクタ*/
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
	is_throw_anim = false;
	is_death = false;
	player_state = PLAYER_MOVE_STATE::IDLE;
	// 初期位置は軸の真下から左方向に45度傾いた位置
		x = CLENGTH / b;
		// 初期速度は０
		speed = 0;

		ve = 90.0;
	if (LoadDivGraph("Resource/Images/Player/IdorSlime.png", 9, 9, 1, 80, 80, images[0]) == -1) {
		throw "Resource/Images/Player/IdorSlime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, images[1]) == -1) {
		throw "Resource/Images/Player/Slime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/ThrowSlime.png", 7, 7, 1, 80, 80, images[2]) == -1) {
		throw "Resource/Images/Player/ThrowSlime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/JumpSlime.png", 10, 10, 1, 80, 80, images[3]) == -1) {
		throw "Resource/Images/Player/JumpSlime.png";
	}
	if ((throw_ball_image = LoadGraph("Resource/Images/Player/SlimeBullet.png")) == -1) {
		throw "Resource/Images/Player/SlimeBullet.png";
	}

	animation_state = PLAYER_ANIM_STATE::IDLE;
	animation_frame = 0;
	animation_mode = 0;
	for (int i = 0; i < ANIMATION_TYPE; i++) {
		animation_type[i] = 0;
		animation_phase[i] = 0;
	}
}

/// <summary>
/// プレイヤーの更新
/// </summary>
void PLAYER::Update(ELEMENT* element) {
	clsDx();
	Move();
	JumpMove();
	HookMove(element);
	Throw();
	HitBlock();

	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Update();
	}

	if (STAGE::GetMapDat(map_y, map_x) == -1) {
		is_death = true;
	}

	//画面端の判定
	if (player_left <= 0) player_x = 40;
	if (player_right + STAGE::GetScrollX() >= 1280) player_x = 1240;

	//描画する画像のセット
	int image_type = 0;
	if (player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		image_type = static_cast<int>(animation_state);
	}
	now_image = images[image_type][animation_type[image_type]];
}

/// <summary>
/// プレイヤーの表示
/// </summary>
void PLAYER::Draw()const {
	//プレイヤーの表示
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
	


	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Draw();
	}
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_THUMB) {
		for (int i = 0; i < throw_x.size(); i += 5) {
			//DrawCircle(throw_x[i], throw_y[i], 10, 0xFFFFFF, TRUE);
			DrawGraph(throw_x[i], throw_y[i], throw_ball_image, TRUE);
		}
	}
	//else {
	//	//DrawCircle(throw_x[0], throw_y[0], 10, 0xFFFFFF, TRUE);
	//	DrawGraph(throw_x[0], throw_y[0], throw_ball_image, TRUE);
	//}


	/*for (int i = 0; i < 10; i++) {
		printfDx("throw_x[%d]: %f\n", i,throw_x[i]);
	}
	for (int i = 0; i < 10; i++) {
		printfDx("throw_y[%d]: %f\n", i, throw_y[i]);
	}*/
	printfDx("throw_rad: %f\n", throw_rad);
	//printfDx("hook: %f %f\n", hook_x, hook_y);
	//printfDx("input.lx: %d\n", PAD_INPUT::GetPadThumbLX());

	//グリッドの表示(デバッグ用)
	//for (int i = 0; i < 128; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xFFFFFF, 2);	//横
	//	DrawLine(i * 80 + STAGE::GetScrollX(), 0, i * 80 + STAGE::GetScrollX(),  720,0xFFFFFF, 2);		//縦
	//}

	//座標(デバッグ用)
	/*printfDx("x1: %d, x2: %d\n", (int)(player_left / MAP_CEllSIZE), (int)player_right / MAP_CEllSIZE);
	printfDx("y1: %d, y2: %d\n", (int)(player_top / MAP_CEllSIZE), (int)player_bottom / MAP_CEllSIZE);
	printfDx("x : %d, y : %d\n", (int)(player_x / MAP_CEllSIZE), (int)player_y / MAP_CEllSIZE);*/

	//マップチップの座標の表示(デバッグ用)
	/*SetFontSize(40);
	DrawFormatString(0, 0, 0xFF, "%d, %d: %d", map_x, map_y, STAGE::GetMapDat(map_y, map_x));*/
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void PLAYER::Move() {
	if (is_hook_move || player_state == PLAYER_MOVE_STATE::HOOK) return;
	if (is_throw_anim) return;
	//スティック入力の取得
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//移動するとき
	move_x = input_lx > 0 ? 1.0f : -1.0f;	//移動方向のセット
	if ((input_lx < -DEVIATION || input_lx > DEVIATION) && player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		animation_state = PLAYER_ANIM_STATE::MOVE;
		animation_mode = 1;							//アニメーションの切り替え
		move_type = move_x > 0 ? 0 : 1;				//移動向きのセット(0: 右, 1: 左)
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) {
			//アニメーションが前半のとき
			if (animation_phase == 0 || true) {
				player_x += move_x * SPEED;
			}
			//アニメーションが後半のとき
			else {
				player_x += move_x * SPEED / 2;
			}
			jump_move_x = move_x;
			player_state = PLAYER_MOVE_STATE::MOVE;	//ステートをMoveに切り替え
		}
		else {
			if (jump_move_x == 0) jump_move_x = move_x;
			move_type = jump_move_x > 0 ? 0 : 1;
			//停止ジャンプだった時
			if (jump_mode == 1) {
				player_x += jump_move_x * SPEED / 2;
			}
			//移動ジャンプだった時
			else {
				move_type = jump_move_x > 0 ? 0 : 1;
				//ジャンプ中に反対方向に移動するとき
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

	//移動してない時
	else {
		move_x = 0;
		//移動アニメーションを後半へ移行
		if (animation_type[1] > 1) {
			animation_phase[1] = 1;
			MoveAnimation();
		}
		//移動アニメーションが終わったらアイドルアニメーションの再生
		else {
			animation_state = PLAYER_ANIM_STATE::IDLE;
			animation_mode = 0;
			MoveAnimation();
		}
		//ジャンプ中じゃないかったらステートを切り替える
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && 
			player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
			jump_move_x = 0;
			player_state = PLAYER_MOVE_STATE::IDLE;	//ステートをIdleに切り替え
		}
	}
}

void PLAYER::Scroll(float move_x) {
	//スクロールの処理
	bool isScroll = false;
	//プレイヤーの位置が中心だったら
	if (move_x > 0 && player_x >= 680 || move_x < 0 && player_x <= 600) {
		//スクロールが端まで行ってない時
		if (!(isScroll = STAGE::SetScrollPos(move_x))) {
			//プレイヤーの位置を中心に戻す
			rebound_x = SPEED * 1.3f;
			player_x -= move_x * rebound_x;
		}
	}
	//スクロールしてない時
	if (!isScroll) {
		rebound_x = SPEED; //反発力を変更
	}
}

/// <summary>
/// フックの移動処理
/// </summary>
void PLAYER::HookMove(ELEMENT* element) {
	//フックの移動方向
	static float move_x = 0;
	static float move_y = 0;
	//フックまでの移動終了判定
	static bool end_move = false;
	//近くにフックがあるかどうか
	bool is_hook = false;
	
	//スティック入力の取得
	int input_lx = PAD_INPUT::GetPadThumbLX();
	
	
	//Bボタン押したとき
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) {
		//フックの座標
		//float hook_y, hook_x;
		//フックまでの距離
		float min_distance = HOOK_MAX_DISTANCE;
		
		//フックの位置
		std::vector<ELEMENT::ELEMENT_DATA> hook_pos = element->GetHookPos();
		for (int i = 0; i < hook_pos.size(); i++) {
			ELEMENT::ELEMENT_DATA pos = hook_pos[i];
			//距離計算
			float diff_x = pos.x - (player_x - STAGE::GetScrollX());
			float diff_y = pos.y - player_y;
			float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
			//距離が最短距離より近いとき
			if (distance <= min_distance) {
				//フックの角度
				float angle = atan2f(diff_y, diff_x);
				//移動の計算
				move_x = cosf(angle) * SPEED * 3;
				move_y = sinf(angle) * SPEED * 3;
				//プレイヤーの現在の位置
				float x = player_x - STAGE::GetScrollX();
				float y = player_y;
				//フックまでの移動経路に障害物がないか
				while (!STAGE::HitMapDat(y / MAP_CEllSIZE, x / MAP_CEllSIZE)) {
					x += move_x;
					y += move_y;
				}
				//配列に変換
				int hook_map_x = x / MAP_CEllSIZE;
				int hook_map_y = y / MAP_CEllSIZE;
				//障害物がある場合は移動させない
				if (STAGE::GetMapDat(hook_map_y, hook_map_x) != 75) {
					continue;
				}
				//最短距離の更新
				min_distance = distance;
				//フックの座標の更新
				hook_x = pos.x;
				hook_y = pos.y;
				//フックが見つかった判定をtrue
				is_hook = true;
			}
		}
		//フックが見つかった時
		if (is_hook) {
			//移動中の時
			if (!end_move) {
				//フックまでの距離の計算
				float y = hook_y - player_y;
				float x = hook_x - (player_x - STAGE::GetScrollX());
				hook_distance = sqrt(x * x + y * y);
				//フック移動してない時
				if (!is_hook_move) {
					//角度の計算
					hook_angle = atan2f(y, x) + 90.0f * (DX_PI_F / 180.0f);
					//移動方向の計算
					move_x = cosf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					move_y = sinf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					//慣性的な奴
					jump_move_x = move_x > 0 ? 1 : -1;
					jump_mode == 2;
				}
				//フックについてない時
				if (hook_distance > 40) {
					player_x += move_x;
					player_y += move_y;
					Scroll(jump_move_x);
				}
				//フックについたら移動処理の終了
				else end_move = true;
				//フックまでの移動判定
				is_hook_move = true;
			}
			//移動が終わった時
			else {
				//フックまでの移動判定
				is_hook_move = false;
				//ステートの変更
				player_state = PLAYER_MOVE_STATE::HOOK;
				//フックの座標にプレイヤーを移動
				//player_x = hook_x + STAGE::GetScrollX();
				//player_y = hook_y;
				// 速度を加算
				speed += -mass * (G / 60) * sin(x / LENGTH);
				x += speed;
				// 軸を原点としてぶら下がっている物の座標を計算
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
				if (input_lx < 15000 && input_lx >- 15000) {	//離している間は角度を狭く、スピードを遅くしていく
					if (speed > 0)speed -= 0.05;
					if (speed < 0)speed += 0.05;
				}
			}
		}
	}
	//フックが見つからなかったら
	if (!is_hook) {
		//初期化
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
/// プレイヤーのジャンプ処理
/// </summary>
void PLAYER::JumpMove() {
	if (CheckHitKey(KEY_INPUT_SPACE))return;		//デバッグ用
	static bool is_jump = false;		//ジャンプ中か
	static float jump_y = 0;			//ジャンプの高さ
	static float velocity = 0.0f;	//ジャンプと落下のスピード
	//Aボタンを押したとき
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A || jump_request) {
		//ジャンプ中じゃないとき
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && player_state != PLAYER_MOVE_STATE::HOOK
			|| jump_request) {
			jump_request = false;
			is_jump = true;			//ジャンプ中に移行
			jump_y = player_y - MAP_CEllSIZE; //ジャンプの高さのセット
			velocity = JUMP_VELOCITY;
			//横移動してない時
			if (player_state == PLAYER_MOVE_STATE::IDLE) {
				jump_mode = 1;
			}
			//横移動してるとき
			else if (player_state == PLAYER_MOVE_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_MOVE_STATE::JUMP;
		}
	}
	//ジャンプ中
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
	//落下中
	else {
		//地面の判定
		bool is_ground = false;
		if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) == 0) is_ground = true;
		if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			STAGE::HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) == 0) is_ground = true;
		if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) is_ground = true;
		//地面じゃない時は落下
		if (!is_ground) {
			velocity += 0.2f;
			player_y += velocity;
			player_state = PLAYER_MOVE_STATE::FALL;
		}
		//地面についた時
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
	static bool is_throw = true;
	//軌道の計算
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_THUMB) {
		is_throw = false;
		is_throw_anim = true;
		//アニメーションのリセット
		animation_type[2] = 0;
		
		throw_index = 0;
		throw_x.clear();
		throw_y.clear();
		int input_ry = PAD_INPUT::GetPadThumbRY();
		int input_rx = PAD_INPUT::GetPadThumbRX();
		if ((abs(input_rx) <= DEVIATION && abs(input_ry) <= DEVIATION) || input_ry < DEVIATION) {
			is_throw = true;
			is_throw_anim = false;
			return;
		}
		//角度取得
		throw_rad = atan2(input_ry, input_rx);
		float angle = throw_rad * 180.0f / M_PI;
		//角度の制限
		if (move_type == 0) {
			if (angle > 90) throw_rad = 90 * M_PI / 180.0f;
			else if (angle < 60) throw_rad = 60 * M_PI / 180.0f;
		}
		else {
			if (angle > 120) throw_rad = 120 * M_PI / 180.0f;
			else if (angle < 90) throw_rad = 90 * M_PI / 180.0f;
		}

		vx0 = ve * (float)cos(throw_rad);
		vy0 = ve * (float)sin(throw_rad);

		g = 9.8;
		dt = 0.15f;

		x0 = player_x;
		y0 = player_y;

		vx = vx0; vy = vy0;

		for (t = 0.0; y0 <= 720; t = t + dt) {
			x0 = x0 + vx * dt;
			y0 = y0 - vy * dt;
			vy = vy - g * dt;
			if (vy < 0) {
				g += 0.2f;
			}
			throw_x.push_back(x0);
			throw_y.push_back(y0);
		}
	}
	else {
		if (life > 1 || is_throw) {
			if (!is_throw) {
				throw_slime.push_back(ThrowSlime(throw_x, throw_y));
				life--;
				is_throw = true;
			}
			//投げる処理
			if (is_throw_anim) {
				int throw_anim = static_cast<int>(PLAYER_ANIM_STATE::THROW);
				if (animation_type[throw_anim] >= animation_image_num[throw_anim] - 1) {
					is_throw_anim = false;
				}
				else {
					animation_state = PLAYER_ANIM_STATE::THROW;
					MoveAnimation();
				}
			}
		}
		else {
			is_throw = true;
			is_throw_anim = false;
		}
	}
}

/// <summary>
/// 横移動の当たり判定
/// </summary>
void PLAYER::HitBlock() {
	//マップチップの座標のセット
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
			else if (move_x < 0) {
				player_x += rebound_x;
			}
		}
		else if (STAGE::HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE))) {
			if (STAGE::HitMapDat(map_y - 1, (int)(player_left / MAP_CEllSIZE))) {
				player_x += rebound_x;
			}
			else if (move_x > 0) {
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
/// アニメーションの切り替え
/// </summary>
void PLAYER::MoveAnimation() {
	//画像の切り替えタイミングのとき
	int type = static_cast<int>(animation_state);
	if (++animation_frame % animation_switch_frame[type] == 0) {
		//前半のアニメーション
		if (animation_phase[type] == 0) {
			animation_type[type]++;
		}
		//後半のアニメーション
		else {
			if (animation_play_type[type] == 0) {
				animation_type[type]--;
			}
			else {
				animation_phase[type] = 0;
				animation_type[type] = 1;
			}
		}
		//前半と後半の切り替え
		if (animation_type[type] >= animation_image_num[type] - 1 || animation_type[type] <= 0) {
			animation_phase[type] = (animation_phase[type] + 1) % 2;
		}
	}
}

