#include "EnemyBullet.h"
#include <math.h>
#include"Option.h"

//コンストラクタ
ENEMY_BULLET::ENEMY_BULLET()
{
	player = nullptr;
	stage = nullptr;
	player_x = 0.0;
	player_y = 0.0;
	bullet_x = 0.0;
	bullet_y = 0.0;
	hypote = 0.0;
	my_x = 0.0;
	my_y = 0.0;
	dis_x = 0.0;
	dis_y = 0.0;
	draw_x = 0;
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	hit_rad = 0.0;
	end_flg = false;
	delete_flg = false;
	hit_flg = false;
	right_side_hit = false;
	left_side_hit = false;
	image = 0;
	rad_x = 0.0;
	map_x = 0;
	map_y = 0;
	mapd_x = 0.0;
	mapd_y = 0.0;
	o_map_x = 0;
	o_map_y = 0;
	image_index = 0;
	animation_timer = 0;
	animation_type = 0;
	splash_se = 0;
	for (int i = 0; i < 4; i++)
	{
		bullet_images[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		bullet_end_images[i] = 0;
	}
}

//引数付きコンストラクタ
ENEMY_BULLET::ENEMY_BULLET(PLAYER* argu_player, STAGE* aug_stage, int x, int y, double dis, double p_rad, int index)
{
	if (LoadDivGraph("Resource/images/Enemy/Enemy_Bullet.png", 4, 4, 1, 20, 20, bullet_images) == -1)
	{
		throw "Resource/Images/Enemy/Enemy_Bullet.png";
	}
	if (LoadDivGraph("Resource/images/Enemy/Bullet_End.png", 20, 10, 2, 60, 30, bullet_end_images) == -1)
	{
		throw "Resource/Images/Enemy/Bullet_End.png";
	}
	if ((splash_se = LoadSoundMem("Resource/Sounds/SE/Enemy/bullet.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/bullet.wav";
	}
	player = argu_player;
	if (player->GetMoveX() > 0)
	{
		player_x = player->GetPlayerX();
	}
	else
	{
		player_x = player->GetPlayerX();
	}

	player_y = player->GetPlayerY();
	bullet_x = x;
	bullet_y = y;
	hypote = 0.0;
	my_x = x;
	my_y = y;
	dis_x = 0.0;
	dis_y = 0.0;
	draw_x = 0;
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	hit_rad = -90 * (PI / 180);
	end_flg = false;
	delete_flg = false;
	hit_flg = false;
	right_side_hit = false;
	left_side_hit = false;
	rad_x = dis;
	stage = aug_stage;
	this->scroll_x = abs(stage->GetScrollX());
	this->scroll_y = abs(stage->GetScrollY());

	map_x = 0;
	map_y = 0;
	mapd_x = 0.0;
	mapd_y = 0.0;
	o_map_x = 0;
	o_map_y = 0;
	rad = p_rad;
	image_index = index;
	image = 0;
	animation_timer = 0;
	animation_type = 0;
	dis_x = (player_x + rad_x) - (my_x - static_cast<double>(scroll_x));
	dis_y = player_y - (my_y - static_cast<double>(scroll_y) - stage->GetSpawnPoint().y);

	hypote = sqrt((dis_x * dis_x) + (dis_y * dis_y));

	bullet_sx = dis_x / hypote * BULLET_SPEED;
	bullet_sy = dis_y / hypote * BULLET_SPEED;

	ChangeVolumeSoundMem(Option::GetSEVolume(), splash_se);
}

ENEMY_BULLET::~ENEMY_BULLET() {

	for (int i = 0; i < 4; i++) {
		DeleteGraph(bullet_images[i]);
	}

	for (int i = 0; i < 20; i++) {
		DeleteGraph(bullet_end_images[i]);
	}

	DeleteSoundMem(splash_se);
}

//描画
void ENEMY_BULLET::Draw() const
{
	DrawRotaGraph(static_cast<int>(GetDrawX()) - draw_x, static_cast<int>(GetDrawY()), 2, rad + hit_rad, image, TRUE);
}

//アップデート
void ENEMY_BULLET::Update()
{

	animation_timer++;        //アニメーションの時間を加算
	//アニメーションを終わらせる
	if (end_flg)
	{
		if (EndAnimation())
		{
			delete_flg = true;
		}
	}
	else
	{
		Move();	//あにめーしょんのうごき
		Hit();  //プレイヤーとの当たり判定
	}
	//弾がプレイヤーに当たっていたら
	if (hit_flg)
	{
		if (player->GetLife() > 0)
		{
			player->SetLife(player->GetLife() - 1);
		}
		else
		{
			player->SetLife(0);
		}
	}

	if (GetDrawX() < 0 || GetDrawX() > 1280 || (bullet_y + stage->GetScrollY()) < 0 || (bullet_y + stage->GetScrollY()) > 720)
	{
		delete_flg = true;
	}
}

void ENEMY_BULLET::Move()
{

	//弾の移動
	bullet_x += bullet_sx;
	bullet_y += bullet_sy;

	//マップ上の値を代入
	mapd_x = bullet_x / MAP_CEllSIZE;
	mapd_y = (bullet_y + IMAGE_Y_SIZE) / MAP_CEllSIZE;

	//自分が前いたマップ座標
	o_map_x = map_x;
	o_map_y = map_y;

	//ダブル型のマップ上の値をイント型に
	map_x = (int)(mapd_x);
	map_y = (int)(mapd_y);
	MoveAnimation();
}

//アニメーションを終わらせる
bool ENEMY_BULLET::EndAnimation()
{
	bool ret = false;           //アニメーションが終わっているかどうかのフラグ
	if (animation_timer < 50)	//50フレーム間アニメーションをする
	{
		if (animation_timer % ANIMATION_TIMER == 0)
		{
			image = bullet_end_images[(image_index * 10) + (animation_type++ % 10)];
		}
	}
	else  //アニメーションの終了
	{
		ret = true;
	}

	return ret;
}
void ENEMY_BULLET::MoveAnimation()
{
	if (animation_timer % ANIMATION_TIMER == 0)
	{
		image = bullet_images[(image_index * 2) + (animation_type++ % 2)];
	}
}

void ENEMY_BULLET::Hit()
{

	float px1, py1, px2, py2;
	float bx1, by1, bx2, by2;

	px1 = player->GetPlayerX() - (20 * (player->GetPlayerScale()));
	px2 = px1 + (50 * (player->GetPlayerScale()));
	py1 = player->GetPlayerY() + (20 * (2 - player->GetPlayerScale()));
	py2 = py1 + (25 * (player->GetPlayerScale()));

	bx1 = GetDrawX();
	bx2 = bx1 + 20;
	by1 = GetDrawY();
	by2 = by1 + 20;

	if (px1 < bx2 && bx1 < px2 && py1 < by2 && by1 < py2)
	{
		delete_flg = true;
		hit_flg = true;
	}
	if (stage->HitMapDat(map_y, map_x))
	{
		PlaySoundMem(splash_se, DX_PLAYTYPE_BACK);
		end_flg = true;
		animation_timer = 0;
		animation_type = 0;
		if (stage->GetMapData(o_map_y + 1, o_map_x) != stage->GetMapData(map_y, map_x))
		{
			if (rad > 90 * (PI / 180))
			{
				hit_rad = 0;
				draw_x = -40;
			}
			else {}
			if (rad < 90 * (PI / 180))
			{
				hit_rad = 180 * (PI / 180);
				draw_x = 40;
			}
			else {}
		}
		rad = 1.6;
	}
}

float ENEMY_BULLET::GetDrawX() const
{
	float ret = (bullet_x - scroll_x) + (static_cast<double>(scroll_x) + stage->GetScrollX());
	return ret;
}

float ENEMY_BULLET::GetDrawY() const
{
	float ret = (bullet_y - scroll_y) + (static_cast<double>(scroll_y) + stage->GetScrollY());

	return ret;
}

