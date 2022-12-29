#include "DxLib.h"
#include "Lemon.h"
#include "Option.h"

LEMON::LEMON()
{
	//画像の取得
	image = nullptr;
	damage_se = 0;

	shootcount = 0;
	hitflg = false;
	delete_flag = false;
	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	now_image = 0;

	state = ENEMY_STATE::IDOL;
	bullet = nullptr;
}


LEMON::LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//スポーン場所の設定
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = (spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2);
	y = spawn_map_y * MAP_CEllSIZE;
	hitflg = false;
	delete_flag = false;

	//画像の取得
	image = new int[15];
	if (LoadDivGraph("Resource/Images/Enemy/lemon.png", 9, 9, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/lemon.png";
	}
	if (LoadDivGraph("Resource/Images/Enemy/lemon_break.png", 6, 6, 1, 80, 80, image + 9) == -1)
	{
		throw "Resource/Images/Enemy/lemon_break.png";
	}
	//SEの取得
	if ((damage_se = LoadSoundMem("Resource/Sounds/SE/Enemy/damage.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/damage.wav";
	}
	if ((press_se = LoadSoundMem("Resource/Sounds/SE/Enemy/press.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/press.wav";
	}
	if ((splash_se = LoadSoundMem("Resource/Sounds/SE/Enemy/splash.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/splash.wav";
	}
	shootcount = 0;

	bullet = nullptr;
	this->player = player;
	this->stage = stage;


	now_image = image[3];
	state = ENEMY_STATE::IDOL;
	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 1.2), damage_se);
	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 0.9), press_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), splash_se);
}


LEMON::~LEMON()
{

	for (int i = 0; i < 15; i++)
	{
		DeleteGraph(image[i]);
	}


	delete[] image;
	if (bullet != nullptr)
	{
		delete bullet;
	}

	DeleteSoundMem(damage_se);
	DeleteSoundMem(press_se);
	DeleteSoundMem(splash_se);
}

void LEMON::Update()
{

	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 1.2), damage_se);
	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 0.9), press_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), splash_se);

	if (animation_timer < 80) {
		++animation_timer;
	}

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		ChangeAngle();
		if (player->GetMapY() > map_y)
		{
			if (++shootcount % 60 == 0)
			{
				animation_timer = 0;
				state = ENEMY_STATE::PRESS;

			}
		}
		break;
	case ENEMY_STATE::RETURN:
		ChangeAngle();
		if (ReturnAnimation())
		{
			animation_timer = 0;
			animation_type = 0;
			state = ENEMY_STATE::MOVE;
		}
		break;
	case ENEMY_STATE::PRESS:
		ChangeAngle();
		if (PressAnimation())
		{
			bullet = new ENEMY_BULLET(player, stage, x, y, 0, rad, 1);
			animation_timer = 0;
			animation_type = 0;
			state = ENEMY_STATE::RETURN;
			PlaySoundMem(press_se, DX_PLAYTYPE_BACK);
		}
		break;
	case ENEMY_STATE::FALL:
		Move();
		FallAnimation();
		break;
	case ENEMY_STATE::DETH:
		if (DethAnimation())
		{
			delete_flag = true;
		}
		break;
	default:
		break;
	}


	//マップ上の座標の設定
	map_x = x / MAP_CEllSIZE;
	map_y = (y - IMAGE_SIZE / 2) / MAP_CEllSIZE;

	//弾が存在しているときに弾の処理を行う
	if (bullet != nullptr)
	{
		bullet->Update();

		//弾が画面外に出るか、何かに当たったら弾を削除
		if (bullet->GetDeleteFlg())
		{
			delete bullet;
			bullet = nullptr;
		}
	}

	Hit();

	if (((x + stage->GetScrollX() < -IMAGE_SIZE) || (x + stage->GetScrollX() > 1280 + IMAGE_SIZE) || (y + stage->GetScrollY() < 0)
		|| (y + stage->GetScrollY() > 720)) && (state != ENEMY_STATE::FALL && state != ENEMY_STATE::DETH))		//画面外に出るとアイドル状態にする
	{
		state = ENEMY_STATE::IDOL;	//ステートをアイドル状態へ
		//アイドル状態の画像に変更
		now_image = image[3];
	}
	else if (state == ENEMY_STATE::IDOL)	//画面内にいて、アイドル状態のとき敵の方向を向くようにする
	{
		// アニメーション時間をリセットし、ステートをムーブへ
		animation_timer = 0;
		state = ENEMY_STATE::MOVE;
	}
	else {}
}


void LEMON::Move()
{
	y += 10;
}

void LEMON::Hit()
{
	ThrowSlime throw_slime;

	float bx1, by1, bx2, by2;
	float gx1, gy1, gx2, gy2;
	//プレイヤーが投げた体の一部との当たり判定
	if ((state != ENEMY_STATE::FALL) && (state != ENEMY_STATE::DETH))
	{
		for (int i = 0; i < player->GetThrowCnt(); i++)
		{
			throw_slime = player->GetThrowSlime(i);
			//スライムのボールの当たり判定
			bx1 = throw_slime.GetThrowX();
			by1 = throw_slime.GetThrowY();
			bx2 = throw_slime.GetThrowX() + BALL_W;
			by2 = throw_slime.GetThrowY() - BALL_H;
			//レモナーの当たり判定
			gx1 = x - IMAGE_SIZE / 2.5;
			gy1 = y - IMAGE_SIZE / 2;
			gx2 = gx1 + IMAGE_SIZE / 1.25;
			gy2 = gy1 + IMAGE_SIZE;
			if (((bx2 >= gx1 && bx2 <= gx2) || (bx1 <= gx2 && bx1 >= gx1)) && ((by1 >= gy2 && by1 <= gy1) || (by2 >= gy1 && by2 <= gy2)))
			{
				rad = 90 * (PI / 180);
				state = ENEMY_STATE::FALL;
				PlaySoundMem(damage_se, DX_PLAYTYPE_BACK);
			}
		}
	}

	//地面やブロックとの当たり判定
	if (state == ENEMY_STATE::FALL)
	{
		if (stage->HitMapDat(map_y + 1, map_x))
		{
			state = ENEMY_STATE::DETH;
			animation_timer = 0;
			animation_type = 0;
			PlaySoundMem(splash_se, DX_PLAYTYPE_BACK);
		}
	}
}
bool LEMON::PressAnimation()
{

	bool ret = false;
	if (animation_timer < 40) //40フレーム間アニメーションをする
	{
		if (animation_timer % (ANIMATION_TIME * 2) == 0)
		{
			if (animation_type < 2)
			{
				now_image = image[(animation_type++ % 7) + 4];
			}
			else
			{
				now_image = image[0];
			}

		}
	}
	else //アニメーションの終了
	{
		ret = true;
	}
	return ret;
}

bool LEMON::ReturnAnimation()
{
	bool ret = false;
	if (animation_timer < 50) //50フレーム間アニメーションをする
	{
		if (animation_timer % (ANIMATION_TIME * 2) == 0)
		{
			now_image = image[(animation_type++ % 7)];
		}
	}
	else //アニメーションの終了
	{
		ret = true;
	}
	return ret;
}

void LEMON::FallAnimation()
{
	if (animation_timer % ANIMATION_TIME == 0)
	{
		now_image = image[(++animation_type % 2) + 7];
	}
}

bool LEMON::DethAnimation()
{
	bool ret = false;
	if (animation_timer < 30) //30フレーム間アニメーションをする
	{
		//アニメーション
		if (animation_timer % ANIMATION_TIME == 0)
		{
			now_image = image[(++animation_type % 6) + 9];
		}
	}
	else //アニメーションの終了
	{
		ret = true;
	}
	return ret;
}

void LEMON::Draw() const
{
	float gx1, gy1, gx2, gy2;

	if (bullet != nullptr)		//弾が存在するとき弾を描画する
	{
		bullet->Draw();
	}
	DrawRotaGraphF(x + stage->GetScrollX(), y + stage->GetScrollY(), 1, rad + (-90 * (PI / 180)), now_image, TRUE);
}