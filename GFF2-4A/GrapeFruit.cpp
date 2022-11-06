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

	x = 640;
	y = 40;
	bullet = nullptr;
	stages = nullptr;
}

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player, STAGE* stage)
{
	image = new int[100];
	if (LoadDivGraph("Resource/Images/Enemy/gurepon.png", 1, 1, 1, 80, 80, image) == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;

	for (int i = 0; i < 2; i++)
		rads[i] = 0.0;
	this->player = player;
	x = 640;
	y = 40;
	bullet = nullptr;
	stages = stage;
}

void GRAPEFRUIT::Update()
{
	ChangeAngle();
	if (++shootcount % 120 == 0) {
		if (flag == false) {
			bullet = new ENEMYBULLET;
			bullet->Update();
			flag = true;
		}
	}
	if (flag)bullet->Move();
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
	DrawRotaGraph2(x, y, 40, 0, 2, rad, image[0], TRUE);
	SetFontSize(24);
	DrawFormatString(50, 50, 0xff0000, "%lf", rad);
	if (flag)bullet->Draw();
}