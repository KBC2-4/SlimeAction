#include"DxLib.h"
#include "GrapeFruit.h"
#include<math.h>
#define _USE_MATH_DEFINES

#include <vector>



GRAPEFRUIT::GRAPEFRUIT()
{
	image = new int[100];
	if (image[0] = LoadGraph("Resource/Images/Enemy/gurepon.png") == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	hitflg = false;
	delete_flg = false;
	rad = 0.0;
	for (int i = 0; i < 2; i++)
		rads[i] = 0.0;
	flag[3] = false;
	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	target_x = 200;
	animation_timer = 0;
	animation_type = 0;
	check_hit_count = 0;
	hit_flg = false;

	for (int i = 0; i < 3; i++) {
		bullet[i] = nullptr;
	}
	bullet_count = 3;
}

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = (spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2);
	y = (spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2) - 40;
	for (int i = 0; i < 3; i++)
	{
		flag[i] = false;
	}
	delete_flg = false;
	image = new int[100];
	if (LoadDivGraph("Resource/Images/Enemy/gurepon.png", 1, 1, 1, 80, 80, image) == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	target_x = 200;

	for (int i = 0; i < 2; i++)
	{
		rads[i] = 0.0;
	}
	for (int i = 0; i < 3; i++)
	{
		bullet[i] = nullptr;
	}
	this->player = player;
	this->stage = stage;
	bullet_count = 3;

	hit_flg = false;
}

void GRAPEFRUIT::Update()
{
	Hit();
	if (hit_flg == false)
	{
		ChangeAngle();
		if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280)) {
			if (++shootcount % 300 == 0) {
				for (int i = 0; i < 3; i++)
				{
					if (flag[i] == false)
					{
						bullet[i] = new ENEMYBULLET(player, stage, x, y, i * 100.0, stage->GetScrollX() ,rad, 0);
						flag[i] = true;
					}
				}
			}
		}
	}
	else
	{
		Move();
	}

	for (int i = 0; i < 3; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Update();
			if (bullet[i]->GetDeleteFlg())
			{
				delete bullet[i];
				bullet[i] = nullptr;
				flag[i] = false;
			}
		}
	}


	Animation();
}

void GRAPEFRUIT::Move()
{
	y += 5;
	for (int i = 0; i < 3; i++)
	{
		flag[i] = false;
	}
	spawn_map_y = y / 80;
	if (stage->GetMapDat(spawn_map_y + 1, spawn_map_x) != 0 && stage->GetMapDat(spawn_map_y + 1, map_x) != 92)
	{
		delete_flg = true;
	}
}



void GRAPEFRUIT::Hit()
{
	ThrowSlime throw_slime;
	float bx1, by1, bx2, by2;
	float gx1, gy1, gx2, gy2;

	for (int i = 0; i < player->GetThrowCnt(); i++)
	{
		throw_slime = player->GetThrowSlime(i);

		//スライムのボールの当たり判定
		bx1 = throw_slime.GetThrowX();
		by1 = throw_slime.GetThrowY();
		bx2 = throw_slime.GetThrowX() + BALL_W;
		by2 = throw_slime.GetThrowY() - BALL_H;

		//グレープフルーツの当たり判定
		gx1 = x;
		gy1 = y;
		gx2 = gx1 + GURAFRU_W;
		gy2 = gy1 + GURAFRU_H;
		if (((bx2 >= gx1 && bx2 <= gx2) || (bx1 <= gx2 && bx1 >= gx1)) && ((by1 >= gy2 && by1 <= gy1) || (by2 >= gy1 && by2 <= gy2)))
		{
			hit_flg = true;
			rad = 90 * (PI / 180);
		}
	}
}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw() const
{
	DrawRotaGraph2(x + stage->GetScrollX(), y+stage->GetScrollY(), 40, 0, 1, rad + (-90 * (PI / 180)), image[0], TRUE);

	if (flag)
	{
		for (int i = 0; i < bullet_count; i++)
		{
			if (bullet[i] != nullptr)
			{
				bullet[i]->Draw();
			}
		}
	}
}

