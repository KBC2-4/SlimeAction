#include"DxLib.h"
#include "GrapeFruit.h"
#include<math.h>
#define _USE_MATH_DEFINES

int i = 0;

double cos_x = 0.0;

double sin_y = 0.0;
int a = 0;
bool flag = false;

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

	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	animation_timer = 0;
	animation_type = 0;
	
	for (int i = 0; i < 3; i++) {
		bullet[i] = nullptr;
	}
	
}

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

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
	this->player = player;
	this->stage = stage;
    
}

void GRAPEFRUIT::Update()
{
	ChangeAngle();
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280)) {
		if (++shootcount % 180 == 0) {
			if (flag == false) {
				bullet[0] = new ENEMYBULLET(player, x, y, 0.0);
				bullet[1] = new ENEMYBULLET(player, x, y, 200.0);
				bullet[2] = new ENEMYBULLET(player, x, y, -200.0);
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
		if (shootcount % 360 == 0) {
			if (flag)
			{
				for (int i = 0; i < 3; i++)
				{
					bullet[i] = nullptr;
				}
				flag = false;
			}
		}
	}

	Move();
	Animation();
	Hit();
}

void GRAPEFRUIT::Move()
{

}

void GRAPEFRUIT::ShotFruitJuice()
{

}

void GRAPEFRUIT::Hit()
{

}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw() const
{
	DrawRotaGraph2(x, y, 40, 0, 1, rad+(-90*(PI/180)), image[0], TRUE);
	
	if (flag)
	{
		for (int i = 0; i < 3; i++) 
		{
			bullet[i]->Draw();
		}
	}
}