#include "PLAYER.h"
#include"DxLib.h"
#include "Element.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Option.h"

//#define _NDEBUG

/*コンストラクタ*/
PLAYER::PLAYER(STAGE* stage) {
	this->stage = stage;
	player_x = 0.0f;
	player_y = 0.0f;
	map_x = 0;
	map_y = 0;
	life = MAX_LIFE;
	jumppower = 0.0f;
	jump_velocity = 0.0f;
	jump_mode = 0;
	jump_move_x = 0;
	jump_request = false;
	is_jump = false;
	is_hook_move = false;
	is_death = false;
	is_damage = false;
	throw_preparation = false;
	throw_interval = 0.0f;
	player_state = PLAYER_MOVE_STATE::IDLE;
	hook_flag.clear();
	// 初期位置は軸の真下から左方向に45度傾いた位置
	x = CLENGTH / b;
	// 初期速度は０
	speed = 0;

	if (LoadDivGraph("Resource/Images/Player/IdorSlime.png", 9, 9, 1, 80, 80, images[0]) == -1) {
		throw "Resource/Images/Player/IdorSlime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Slime.png", 10, 10, 1, 80, 80, images[1]) == -1) {
		throw "Resource/Images/Player/Slime.png";
	}
	if (LoadDivGraph("Resource/Images/Player/ThrowSlime.png", 7, 7, 1, 80, 80, images[2]) == -1) {
		throw "Resource/Images/Player/ThrowSlime.png";
	}
	if ((images[3][0] = LoadGraph("Resource/Images/Player/nobi.png")) == -1) {
		throw "Resource/Images/Player/nobi.png";
	}
	if ((images[3][1] = LoadGraph("Resource/Images/Player/nobi2.png")) == -1) {
		throw "Resource/Images/Player/nobi2.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime01.png", 4, 4, 1, 80, 80, images[4]) == -1) {
		throw "Resource/Images/Player/JumpSlime01.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime02.png", 4, 4, 1, 80, 80, images[5]) == -1) {
		throw "Resource/Images/Player/JumpSlime02.png";
	}

	if (LoadDivGraph("Resource/Images/Player/JumpSlime2.png", 10, 10, 1, 80, 80, images[6]) == -1) {
		throw "Resource/Images/Player/JumpSlime1.png";
	}
	if ((throw_ball_image = LoadGraph("Resource/Images/Player/Slime_Bullet.png")) == -1) {
		throw "Resource/Images/Player/Slime_Bullet.png";
	}
	if ((hp_img = LoadGraph("Resource/Images/Player/hp.png")) == -1) {
		throw "Resource/Images/Player/hp.png";
	}
	if ((idle_nobi_img = LoadGraph("Resource/Images/Player/FuckAnim2.png")) == -1) {
		throw "Resource/Images/Player/FuckAnim2.png";
	}

	if ((damageSE = LoadSoundMem("Resource/Sounds/SE/Player/damage.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/damage.wav";
	}
	if ((jumpSE = LoadSoundMem("Resource/Sounds/SE/Player/jump.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/jump.wav";
	}
	if ((landingSE = LoadSoundMem("Resource/Sounds/SE/Player/landing.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/jump2.wav";
	}
	if ((hook_moveSE = LoadSoundMem("Resource/Sounds/SE/Player/hook_move.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/hook_move.wav";
	}
	if ((hook_pendulumSE = LoadSoundMem("Resource/Sounds/SE/Player/hook_pendulum.wav")) == -1) {
		throw "Resource/Sounds/SE/Player/hook_pendulum.wav";
	}


	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), damageSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), jumpSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), landingSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), hook_moveSE);
	ChangeVolumeSoundMem(Option::GetSEVolume(), hook_pendulumSE);
	
	animation_state = PLAYER_ANIM_STATE::IDLE;
	for (int i = 0; i < ANIMATION_TYPE; i++) {
		animation[i].frame = 0;
		animation[i].type = 0;
		animation[i].phase = 0;
		animation[i].playMode = 0;
		animation[i].endAnim = false;
	}

	animation[static_cast<int>(PLAYER_ANIM_STATE::THROW)].playMode = 1;
	animation[static_cast<int>(PLAYER_ANIM_STATE::LANDING)].playMode = 1;
}

PLAYER::~PLAYER() {
	DeleteGraph(throw_ball_image);
	DeleteGraph(hp_img);
	DeleteGraph(idle_nobi_img);
	for (int i = 0; i < ANIMATION_TYPE; i++) {
		for (int j = 0; j < 10; j++) {
			DeleteGraph(images[i][j]);
		}
	}

	DeleteSoundMem(damageSE);
	DeleteSoundMem(jumpSE);
	DeleteSoundMem(landingSE);
	DeleteSoundMem(hook_moveSE);
	DeleteSoundMem(hook_pendulumSE);
}

/// <summary>
/// プレイヤーの更新
/// </summary>
void PLAYER::Update(ELEMENT* element, STAGE* stage) {

		ChangeVolumeSoundMem(Option::GetSEVolume(), damageSE);
		ChangeVolumeSoundMem(Option::GetSEVolume(), jumpSE);
		ChangeVolumeSoundMem(Option::GetSEVolume(), landingSE);
		ChangeVolumeSoundMem(Option::GetSEVolume(), hook_moveSE);
		ChangeVolumeSoundMem(Option::GetSEVolume(), hook_pendulumSE);


	//移動処理
	Move();

	//ジャンプ処理
	JumpMove();

	//フック処理
	HookMove(element, stage);

	//投げる処理
	Throw(stage);

	//アニメーションの再生
	MoveAnimation();

	//ブロックとの当たり判定
	HitBlock(element, stage);

	//球を消す処理
	for (int i = 0; i < throw_slime.size(); i++) {
		if (throw_slime[i].checkdel() == true) {
			throw_slime[i].Finalize();
			throw_slime.erase(throw_slime.begin() + i);
		}
	}

	//球の更新
	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Update(stage);
	}

	//死判定
	if (stage->GetMapData(map_y, map_x) == -1 || life <= 0) {
		is_death = true;
	}
	if (player_y + stage->GetScrollY() > 720 && player_state != PLAYER_MOVE_STATE::HOOK){
		is_death = true;
	}

	//画面端の判定
	if (player_x <= 40 * player_scale) {
		player_x = 40 * player_scale;
	}
	if (player_x + stage->GetScrollX() >= 1280 - MAP_CEllSIZE / 2 * player_scale) {
		player_x = 1280 - MAP_CEllSIZE / 2 * player_scale - stage->GetScrollX();
	}

	//点滅処理
	if (is_damage) {
		if (alpha_time > 0) {
			if (alpha_time % 20 < 10) {
				alpha_param -= 25;
			}
			else {
				alpha_param += 25;
			}
			alpha_time--;
		}
		else {
			is_damage = false;
		}
	}

	//プレイヤーのサイズの更新
	player_scale = static_cast<float>(life - 1) / static_cast<float>(MAX_LIFE) + MIN_SIZE_SCALE;
}

/// <summary>
/// プレイヤーの表示
/// </summary>
void PLAYER::Draw(STAGE *stage)const {
	static float dis = 0.0f;

	if (is_damage) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_param);
	}

	//プレイヤーの表示
	//フック中じゃない時
	if (player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move) {
		dis = 0.0f;
		//描画する画像のセット
		int image_type = static_cast<int>(animation_state);
		int now_image = images[image_type][animation[image_type].type];

		DrawRotaGraphF(player_x + stage->GetScrollX(), (player_y - 20 + stage->GetScrollY()) + (1.6 - player_scale) * 40, player_scale, 0.0, now_image, TRUE, move_type);
	}
	else {
		//振り子中
		if (player_state == PLAYER_MOVE_STATE::HOOK) {
			float diff_x = nx;
			float diff_y = ny;
			float distance = sqrt(diff_y * diff_y + diff_x * diff_x);
			float angle = atan2(diff_y, diff_x) + DX_PI_F;
			if (move_type == 0) {
				DrawRotaGraph3F(hook_x + nx + stage->GetScrollX(), hook_y + ny + stage->GetScrollY(), 80, 80,
					(distance) / MAP_CEllSIZE / 2, 0.6f, (double)angle,
					images[3][1], TRUE, move_type);
			}
			else {
				DrawRotaGraph3F(hook_x + nx + stage->GetScrollX(), hook_y + ny + stage->GetScrollY(), 80, 80,
					(distance) / MAP_CEllSIZE / 2, 0.6f, (double)angle,
					images[3][0], TRUE, move_type);
			}
		}
		//伸びる時
		else {
			dis += hook_distance / 10.0f;
			DrawRotaGraph3F(player_x + stage->GetScrollX() + 20, (player_y + stage->GetScrollY()) + (1.6 - player_scale) * 40, 80, 40,
				(dis / (MAP_CEllSIZE * 3.0)) * player_scale, 1 * player_scale, (double)hook_angle + M_PI,
				idle_nobi_img, TRUE, move_type);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ボールの描画
	int throw_cnt = throw_slime.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_slime[i].Draw(stage);
	}

	//ボールの軌道の描画
	for (int i = 0; i < throw_x.size(); i += 5) {
		DrawGraph(throw_x[i], throw_y[i], throw_ball_image, TRUE);
	}

	//ライフの描画
	for (int i = 0; i < life - 1; i++) {
		DrawRotaGraph(30 + 50 * i, 20, 1, 0, hp_img, TRUE);
	}
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void PLAYER::Move() 
{
	player_speed = SPEED + (MAX_LIFE - life) * 0.4f;
	if (is_hook_move || player_state == PLAYER_MOVE_STATE::HOOK) return;
	
	//スティック入力の取得
	old_player_x = player_x;
	old_player_y = player_y;
	int input_lx = PAD_INPUT::GetPadThumbLX();
	//移動するとき
	move_x = input_lx > 0 ? 1.0f : -1.0f;	//移動方向のセット
	if (input_lx < -DEVIATION || input_lx > DEVIATION) 
	{
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) 
		{
			move_type = (move_x > 0) ? 0 : 1;				//移動向きのセット(0: 右, 1: 左)
			player_x += move_x * player_speed;
			jump_move_x = move_x;
			player_state = PLAYER_MOVE_STATE::MOVE;	//ステートをMoveに切り替え
			ChangeAnimation(PLAYER_ANIM_STATE::MOVE); //アニメーションの切り替え
		}
		else 
		{
			if (jump_move_x == 0) jump_move_x = move_x;
			move_type = (jump_move_x > 0) ? 0 : 1;
			if (jump_mode == 1) //停止ジャンプだった時
			{
				player_x += jump_move_x * player_speed / 2.0f;
			}
			else //移動ジャンプだった時
			{
				move_type = (jump_move_x > 0) ? 0 : 1;

				//ジャンプ中に反対方向に移動するとき
				if (jump_move_x != move_x) 
				{
					player_x += jump_move_x * player_speed / 2.0f;
				}
				else 
				{
					player_x += jump_move_x * player_speed;
				}
			}
		}
	}
	else //移動してない時
	{
		move_x = 0;
		//移動アニメーションを後半へ移行
		int move = static_cast<int>(PLAYER_ANIM_STATE::MOVE);
		if (animation[move].type > 1 && animation_state == PLAYER_ANIM_STATE::MOVE)
		{
			animation[move].phase = 1;
		}
		else //移動アニメーションが終わったらアイドルアニメーションの再生
		{
			ChangeAnimation(PLAYER_ANIM_STATE::IDLE);
		}
		//ジャンプ中じゃないかったらステートを切り替える
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL) {
			jump_move_x = 0;
			player_state = PLAYER_MOVE_STATE::IDLE;	//ステートをIdleに切り替え
		}
	}

	if (player_x < old_player_x) {
		move_x = -1.0f;
	}
	else if (player_x > old_player_x) {
		move_x = 1.0f;
	}
}

/// <summary>
/// フックの移動処理
/// </summary>
void PLAYER::HookMove(ELEMENT* element, STAGE* stage) {
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
		if (player_state != PLAYER_MOVE_STATE::HOOK) {
			if (--hook_interval > 0) return;
			//フックまでの距離
			float min_distance = HOOK_MAX_DISTANCE;
			//フックの位置
			std::vector<ELEMENT::ELEMENT_DATA> hook_pos = element->GetHook();
			for (int i = 0; i < hook_pos.size(); i++) {
				//if (std::find(hook_flag.begin(), hook_flag.end(), i) != hook_flag.end()) continue;
				ELEMENT::ELEMENT_DATA pos = hook_pos[i];
				//距離計算
				float diff_x = pos.x - (player_x);
				float diff_y = pos.y - player_y;
				float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
				//距離が最短距離より近いとき
				if (distance <= min_distance) {
					//フックの角度
					float angle = atan2f(diff_y, diff_x);
					//移動の計算
					move_x = cosf(angle) * player_speed * 3;
					move_y = sinf(angle) * player_speed * 3;
					//プレイヤーの現在の位置
					float x = player_x;
					float y = player_y;
					//フックまでの移動経路に障害物がないか
					while (!stage->HitMapDat(y / MAP_CEllSIZE, x / MAP_CEllSIZE)) {
						if (stage->GetMapData(y / MAP_CEllSIZE, x / MAP_CEllSIZE) == 72) {
							break;
						}
						x += move_x;
						y += move_y;
					}
					//配列に変換
					int hook_map_x = x / MAP_CEllSIZE;
					int hook_map_y = y / MAP_CEllSIZE;
					//障害物がある場合は移動させない
					if (stage->GetMapData(hook_map_y, hook_map_x) != 72) {		//フックの配列番号を入れる
						continue;
					}
					//最短距離の更新
					min_distance = distance;
					hook_index = i;
					//フックの座標の更新
					hook_x = pos.x;
					hook_y = pos.y;
					//フックが見つかった判定をtrue
					is_hook = true;
				}
			}
		}
		else {
			is_hook = true;
		}
		//フックが見つかった時
		if (is_hook) {
			//ステートの変更
			player_state = PLAYER_MOVE_STATE::GROW_HOOK;
			ChangeAnimation(PLAYER_ANIM_STATE::IDLE, false);
			//移動中の時
			if (!end_move) {
				//フックまでの距離の計算
				float y = hook_y - player_y;
				float x = hook_x - (player_x);
				hook_distance = sqrt(x * x + y * y);
				//角度の計算
				hook_angle = atan2f(y, x) + 180.0f * (DX_PI_F / 180.0f);
				//フック移動してない時
				if (!is_hook_move) {
					//移動方向の計算
					move_x = cosf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					move_y = sinf(hook_angle - 90.0f * (DX_PI_F / 180.0f)) * SPEED * 3;
					//慣性的な奴
					jump_move_x = move_x > 0 ? 1 : -1;
					jump_mode == 2;
					//PlaySoundMem(hook_moveSE, DX_PLAYTYPE_BACK);
				}
				//フックについてない時
				if (hook_distance > 40) {
					player_x += move_x;
					player_y += move_y;
				}
				//フックについたら移動処理の終了
				else {
					//StopSoundMem(hook_moveSE);
					//PlaySoundMem(hook_pendulumSE, DX_PLAYTYPE_LOOP);
					end_move = true;
					//振り子の開始角度の設定
					double angle = (double)hook_angle * (180.0 / M_PI) - 90.0;
					if (angle > 90 && angle < 180) angle = 90.0;
					else if (angle < -90 || angle > 180) angle = -90.0;
					this->x = (CLENGTH / 360.0) * angle;
					//スピードの初期化
					speed = 0;
				}
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
				player_x = hook_x + nx;
				player_y = hook_y + ny;
				// 速度を加算
				speed += -mass * (G / 60) * sin(x / LENGTH);
				x += speed;
				// 軸を原点としてぶら下がっている物の座標を計算
				angle = x / LENGTH + PI / 2.0;
				nx = cos(angle) * LENGTH;
				ny = sin(angle) * LENGTH;
				if (speed >= 0) {
					if (input_lx < -15000) {
						speed += 0.05 * 2.0f;
					}
					if (input_lx > 15000) {
						speed -= 0.09 * 2.0f;
					}
				}
				else if (speed < 0) {
					if (input_lx < -15000) {
						speed += 0.09 * 2.0f;
					}
					if (input_lx > 15000) {
						speed -= 0.05 * 2.0f;
					}
				}
				if (hook_y + ny < hook_y) {
					ny = 0;
					speed = 0.0;
				}
				if (input_lx < 15000 && input_lx >-15000) {	//離している間は角度を狭く、スピードを遅くしていく
					if (speed > 0)speed -= 0.05;
					if (speed < 0)speed += 0.05;
				}
				StartJoypadVibration(DX_INPUT_PAD1, static_cast<int>(abs(speed) / 18.0 * 500.0), 1, -1);
			}
		}
	}
	//フックが見つからなかったら
	if (!is_hook) {
		//初期化		
		end_move = false;
		if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
			//フック後のジャンプ方向の修正
			//StopSoundMem(hook_pendulumSE);
			hook_interval = HOOK_INTERVAL;
			hook_flag.push_back(hook_index);
			//printfDx("%d\n", hook_index);
			if (input_lx < -DEVIATION) {
				jump_move_x = -1;
			}
			else if (input_lx > DEVIATION) {
				jump_move_x = 1;
			}
			else {
				player_state = PLAYER_MOVE_STATE::FALL;
			}
			if (player_state == PLAYER_MOVE_STATE::HOOK) {
				player_x = hook_x + nx;
				player_y = hook_y + ny;
				player_y += 1;
				jumppower = fabs(static_cast<float>(nx) / LENGTH);
				if (fabsf(nx) > LENGTH / 2) {
					jump_request = true;
				}
			}
			player_state = PLAYER_MOVE_STATE::FALL;
		}
		hook_index = -1;
		is_hook_move = false;
	}
}

/// <summary>
/// プレイヤーのジャンプ処理
/// </summary>
void PLAYER::JumpMove() {
#ifndef _NDEBUG
	if (PAD_INPUT::GetNowKey()== XINPUT_BUTTON_Y || CheckHitKey(KEY_INPUT_SPACE))return;		//デバッグ用
#endif
	//Aボタンを押したとき
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A || jump_request) {
		//ジャンプ中じゃないとき
		if (player_state != PLAYER_MOVE_STATE::JUMP && player_state != PLAYER_MOVE_STATE::FALL && player_state != PLAYER_MOVE_STATE::HOOK && is_ground
			|| jump_request) {
			jump_request = false;
			is_jump = true;			//ジャンプ中に移行
			jump_velocity = JUMP_VELOCITY * jumppower;
			//横移動してない時
			if (player_state == PLAYER_MOVE_STATE::IDLE) {
				jump_mode = 1;
			}
			//横移動してるとき
			else if (player_state == PLAYER_MOVE_STATE::MOVE) {
				jump_mode = 2;
			}
			player_state = PLAYER_MOVE_STATE::JUMP;
			ChangeAnimation(PLAYER_ANIM_STATE::JUMP);
			PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK);
		}
	}
	//ジャンプ中
	if (is_jump) {
		jump_velocity += 0.2f;
		player_y += jump_velocity;

		ChangeAnimation(PLAYER_ANIM_STATE::JUMP);

		if (jump_velocity >= 0.0f || hit_ceil || player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
			is_jump = false;
			hit_ceil = false;
			jump_velocity = 0;
		}
	}
	//落下中
	else {
		//地面じゃない時は落下
		if (!is_ground) {
			jump_velocity += 0.2f;
			player_y += jump_velocity;
			player_state = PLAYER_MOVE_STATE::FALL;
			ChangeAnimation(PLAYER_ANIM_STATE::FALL);
		}
		//地面についた時
		else {
			if ((player_state == PLAYER_MOVE_STATE::FALL || player_state == PLAYER_MOVE_STATE::JUMP) && !is_hook_move) {
				jumppower = 1.0;
				float new_y = (float)(map_y - 1) * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				if (fabsf(new_y - player_y) <= jump_velocity) {
					player_y = new_y;
				}
				jump_velocity = 0;
				hook_flag.clear();
				player_state = PLAYER_MOVE_STATE::IDLE;
				ChangeAnimation(PLAYER_ANIM_STATE::LANDING);
				PlaySoundMem(landingSE, DX_PLAYTYPE_BACK);
			}
			if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
				jump_velocity = 0;
			}
		}
		if (animation_state == PLAYER_ANIM_STATE::LANDING) {
			if (animation[static_cast<int>(animation_state)].endAnim) {
				ChangeAnimation(PLAYER_ANIM_STATE::IDLE);
			}
		}
	}

}

void PLAYER::Throw(STAGE* stage) {
	static bool push_button = false;
	//軌道の計算
	throw_index = 0;
	throw_x.clear();
	throw_y.clear();

	if (--throw_interval > 0) return;

	int input_ry = PAD_INPUT::GetPadThumbRY();
	int input_rx = PAD_INPUT::GetPadThumbRX();
	if ((abs(input_rx) <= DEVIATION && abs(input_ry) <= DEVIATION) || input_ry < DEVIATION) {
		return;
	}
	//角度取得
	throw_rad = atan2(input_ry, input_rx);
	float angle = throw_rad * 180.0f / M_PI;
	//角度の制限
	if (move_type == 0) {
		if (angle > 90) throw_rad = 90 * M_PI / 180.0f;
		else if (angle < 30) throw_rad = 30 * M_PI / 180.0f;
	}
	else {
		if (angle > 150) throw_rad = 150 * M_PI / 180.0f;
		else if (angle < 90) throw_rad = 90 * M_PI / 180.0f;
	}

	float ve = 110;

	float vx0 = ve * (float)cos(throw_rad);
	float vy0 = ve * (float)sin(throw_rad);

	float g = 9.8;
	float dt = 0.15f;

	float x0 = player_x + stage->GetScrollX();
	float y0 = player_y + stage->GetScrollY();

	float vx = vx0;
	float vy = vy0;

	float maxY = stage->GetMapSize().y * MAP_CEllSIZE;

	for (float t = 0.0; y0 <= maxY; t = t + dt) {
		x0 = x0 + vx * dt;
		y0 = y0 - vy * dt;
		vy = vy - g * dt;
		if (vy < 0) {
			g += 0.2f;
		}
		throw_x.push_back(x0);
		throw_y.push_back(y0);
	}
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_RIGHT_SHOULDER) {
		if (!push_button) {
			push_button = true;
			//投げる処理
			throw_interval = THROW_INTERVAL;
			throw_slime.push_back(ThrowSlime(throw_x, throw_y, stage));
			ChangeAnimation(PLAYER_ANIM_STATE::THROW, true);
		}
	}
	else {
		push_button = false;
	}
}

/// <summary>
/// 横移動の当たり判定
/// </summary>
void PLAYER::HitBlock(ELEMENT* element,STAGE* stage) {
	//マップチップの座標のセット
	map_x = (int)roundf((player_x) / MAP_CEllSIZE);
	map_y = (int)floorf((player_y + MAP_CEllSIZE / 2) / MAP_CEllSIZE);
	float player_left = (player_x - 30 * player_scale);
	float player_right = (player_x + 30 * player_scale);
	float player_top = (player_y - (player_scale - 0.6f) * MAP_CEllSIZE / 2);
	float player_bottom = (player_y + MAP_CEllSIZE / 2);

	//天井の判定
	bool hit_ceil_center = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
	bool hit_ceil_left = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)((player_left + player_speed) / MAP_CEllSIZE));
	bool hit_ceil_right = stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)((player_right - player_speed) / MAP_CEllSIZE));
	hit_ceil = hit_ceil_center || hit_ceil_left || hit_ceil_right;
	
	//地面の判定
	is_ground = false;
	if (player_state == PLAYER_MOVE_STATE::HOOK || is_hook_move) {
		is_ground = true;
		return;
	}
	if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) &&
		!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE)) &&
		!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE))) {
		is_ground = true;
	}
	float diff_y = fabsf(player_y - old_player_y);
	if (fmodf(player_y, MAP_CEllSIZE / 2) <= diff_y) {
		bool is_manhole = false;
		if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_left / MAP_CEllSIZE))) {
			is_ground = true;
		}
		if (stage->HitMapDat((int)(player_bottom / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_top / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) &&
			!stage->HitMapDat((int)(player_y / MAP_CEllSIZE), (int)(player_right / MAP_CEllSIZE)) && !is_manhole) {
			is_ground = true;
		}
		int block_type_center = stage->GetMapData((int)(player_y / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
		int block_type_top = stage->GetMapData((int)(player_top / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
		int block_type_bottom = stage->GetMapData((int)(player_bottom / MAP_CEllSIZE), (int)(player_x / MAP_CEllSIZE));
		if (block_type_center == 98 || block_type_top == 98 || block_type_bottom == 98) {
			float diff = fabsf((float)((int)(player_x / MAP_CEllSIZE) * MAP_CEllSIZE) - player_left);
			if (diff < player_speed) {
				is_manhole = true;
				is_ground = false;
			}
		}
	}

	if (!is_ground && element->HitLift(this)) {
		if (animation_state != PLAYER_ANIM_STATE::THROW) {
			//ChangeAnimation(PLAYER_ANIM_STATE::IDLE, true);
		}
		is_ground = true;
	}

	if (is_ground) {
		hook_interval = 0;
	}

	//壁の判定
	int screen_left = static_cast<int>(-stage->GetScrollX() / MAP_CEllSIZE);
	for (int i = 0; i < stage->GetMapSize().x; i++) {
		for (int j = screen_left; j < screen_left + 20; j++) {
			if (j >= stage->GetMapSize().y) break;
			if (!stage->HitMapDat(i, j)) continue;
			
			float block_left = j * MAP_CEllSIZE;
			float block_right = block_left + MAP_CEllSIZE;
			float block_top = i * MAP_CEllSIZE;
			float block_bottom = block_top + MAP_CEllSIZE;

			if (player_right > block_left && player_left < block_right) {
				if (player_bottom > block_top && player_top < block_bottom) {
					int block_type = stage->GetMapData(i, j);
					int y = static_cast<int>(player_top / MAP_CEllSIZE);
					if (hit_ceil && y == i) continue;
					//ドアの判定
					if ((block_type == 66 || block_type == 67) && move_x > 0) {
						if (fabsf(player_left - block_right) < player_speed) {
							return;
						}
					}
					player_x = old_player_x;
					break;
				}
			}
		}
	}
}

void PLAYER::ChangeAnimation(PLAYER_ANIM_STATE anim, bool compelChange) {
	int now_anim_type = static_cast<int>(animation_state);
	int next_anim_type = static_cast<int>(anim);
	if (animation_state != anim && player_state != PLAYER_MOVE_STATE::HOOK && !is_hook_move || compelChange) {
		if (animation[now_anim_type].priority <= animation[next_anim_type].priority || animation[now_anim_type].endAnim || compelChange) {
			animation_state = anim;
			int anim_type = static_cast<int>(anim);
			animation[anim_type].frame = 0;
			animation[anim_type].type = 0;
			animation[anim_type].phase = 0;
			animation[anim_type].endAnim = false;
		}
	}
}

/// <summary>
/// アニメーションの切り替え
/// </summary>
void PLAYER::MoveAnimation() {
	//画像の切り替えタイミングのとき
	int type = static_cast<int>(animation_state);
	if (++animation[type].frame % animation[type].switch_frame == 0) {
		//前半のアニメーション
		if (animation[type].phase == 0 && animation[type].type < animation[type].image_num - 1) {
			animation[type].type++;
		}
		//後半のアニメーション
		else {
			if (animation[type].play_type == 0) {
				animation[type].type--;
			}
			else if (animation[type].play_type == 1) {
				//animation[type].phase = 0;
				animation[type].type = 0;
			}
		}
		//前半と後半の切り替え
		if (animation[type].type >= animation[type].image_num - 1 || animation[type].type <= 0) {
			if (animation[type].play_type == 0) {
				if (animation[type].phase == 1) {
					animation[type].endAnim = true;
				}
			}
			else if (animation[type].play_type == 1) {
				animation[type].endAnim = true;
			}
			animation[type].phase = (animation[type].phase + 1) % 2;
		}
	}
}

void PLAYER::SetLife(int a)
{
	if (life > a && !is_damage) {
		//player_state = PLAYER_MOVE_STATE::DAMAGE;
		alpha_time = 120;
		is_damage = true;
		StartJoypadVibration(DX_INPUT_PAD1, 360, 320, -1);
		PlaySoundMem(damageSE, DX_PLAYTYPE_BACK);
	}
	life = a;
}