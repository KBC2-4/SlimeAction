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
	rad = 0.0;
	for (int i = 0; i < 2; i++)
		rads[i] = 0.0;
	flag = false;
	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	animation_timer = 0;
	animation_type = 0;
	throw_slime = nullptr;
	
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
	y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	flag = false;
	image = new int[100];
	if (LoadDivGraph("Resource/Images/Enemy/gurepon.png", 1, 1, 1, 80, 80, image) == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;

	for (int i = 0; i < 2; i++)
	{
		rads[i] = 0.0;
	}
	for (int i = 0; i < 3; i++)
	{
		bullet[i] = nullptr;
	}
	throw_slime = nullptr;
	this->player = player;
	this->stage = stage;
	bullet_count = 3;
}

void GRAPEFRUIT::Update()
{
	ChangeAngle();
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280)) {
		if (++shootcount % 180 == 0) {
			if (flag == false) {
				bullet[0] = new ENEMYBULLET(player, stage, x, y, 0.0,stage->GetScrollX());
				bullet[1] = new ENEMYBULLET(player, stage, x, y, 200.0, stage->GetScrollX());
				bullet[2] = new ENEMYBULLET(player, stage, x, y, -200.0, stage->GetScrollX());
				flag = true;
			}
		}
		if (flag)
		{
   			for (int i = 0; i < 3; i++)
			{
				bullet[i]->Update();
			}
		}
		if (flag)
		{
				for (int i = 0; i < 3; i++)
				{
					if (bullet[i]->GetBulletFlg())
					{
						delete bullet[i];
						bullet[i] = nullptr;
					}
				}
				flag = false;
		}	
	}

	Move();
	Animation();
	Hit();
}

void GRAPEFRUIT::Move()
{

}



void GRAPEFRUIT::Hit()
{
	ThrowSlime throw_slime;
	
	for (int i = 0; i < player->GetThrowCnt(); i++)
	{
		throw_slime = player->GetThrowSlime(i);	
		if(throw_slime.GetThrowX)
	}

	
}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw() const
{
	DrawRotaGraph2(x + stage->GetScrollX(), y, 40, 0, 1, rad + (-90*(PI/180)), image[0], TRUE);
	
	if (flag)
	{
		for (int i = 0; i < bullet_count; i++) 
		{
			bullet[i]->Draw();
		}
	}
}

