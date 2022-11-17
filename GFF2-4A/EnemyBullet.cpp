#include "EnemyBullet.h"
#include <math.h>

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
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	end_flg = false;
	delete_flg = false;
	hit_flg = false;
	rad_x = 0.0;
	map_x = 0;
	map_y = 0;
	image_index = 0;
	animation_timer = 0;
	animation_type = 0;
	for (int i = 0; i < 4; i++)
	{
		bullet_images[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		bullet_end_images[i] = 0;
	}
}

ENEMY_BULLET::ENEMY_BULLET(PLAYER* argu_player, STAGE* aug_stage, int x, int y, double dis, float scroll,double p_rad,int index)
{
	if (LoadDivGraph("Resource/images/Enemy/Enemy_Bullet.png", 4, 4, 1, 20, 20, bullet_images) == -1)
	{
		throw "Resource/Images/Enemy/Enemy_Bullet.png";
	}
	if (LoadDivGraph("Resource/images/Enemy/Bullet_End.png", 20, 10, 2, 60, 30, bullet_end_images) == -1)
	{
		throw "Resource/Images/Enemy/Bullet_End.png";

	}
	player = argu_player;
	player_x = player->GetPlayerX();
	player_y = player->GetPlayerY();
	bullet_x = x;
	bullet_y = y;
	hypote = 0.0;
	my_x = x;
	my_y = y;
	dis_x = 0.0;
	dis_y = 0.0;
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	end_flg = false;
	delete_flg = false;
	hit_flg = false;
	rad_x = dis;
	scroll_x = abs(scroll);
	map_x = 0;
	map_y = 0;
	rad = p_rad;
	image_index = index;
	animation_timer = 0;
	animation_type = 0;
	stage = aug_stage;
	dis_x = (player_x + rad_x) - (my_x - static_cast<double>(scroll_x));
	dis_y = player_y - my_y;

	hypote = sqrt((dis_x * dis_x) + (dis_y * dis_y));

	bullet_sx = dis_x / hypote * 5;
	bullet_sy = dis_y / hypote * 5;
}

void ENEMY_BULLET::Draw() const
{
	DrawRotaGraph(static_cast<int>(GetDrawX()), bullet_y, 2, rad + (-90 * (PI / 180)), image, TRUE);
}

void ENEMY_BULLET::Update()
{

	animation_timer++;
	if (end_flg)
	{
		if (EndAnimation())
		{
			delete_flg = true;
		}
	}
	else
	{
	Move();
	Hit();
	}
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

}

void ENEMY_BULLET::Move()
{

	//弾の移動
	bullet_x += bullet_sx;
	bullet_y += bullet_sy;

	if (GetDrawX() < 0 || GetDrawX() > 1280)
	{
		delete_flg = true;
	}

	mapd_x = bullet_x / MAP_CEllSIZE;
	mapd_y = (bullet_y + IMAGE_Y_SIZE)  / MAP_CEllSIZE;

	map_x = (int)(mapd_x);
	map_y = (int)(mapd_y);
	MoveAnimation();
}

bool ENEMY_BULLET::EndAnimation()
{
	bool ret = false;
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

	px1 = player->GetPlayerX() - 30;
	px2 = px1 + 60;
	py1 = player_y;
	py2 = py1 + 40;

	bx1 = GetDrawX();
	bx2 = bx1 + 20;
	by1 = bullet_y;
   	by2 = by1 + 20;

	if (px1 < bx2 && bx1 < px2 && py1 < by2 && by1 < py2)
	{
		delete_flg = true;
		hit_flg = true;
	}
	if (stage->HitMapDat(map_y, map_x))
	{
		end_flg = true;
		animation_timer = 0;
		animation_type = 0;
		rad = 1.6;
	}
}

float ENEMY_BULLET::GetDrawX() const
{
	float ret = (bullet_x - scroll_x) + (static_cast<double>(scroll_x) + stage->GetScrollX());
	return ret;
}
