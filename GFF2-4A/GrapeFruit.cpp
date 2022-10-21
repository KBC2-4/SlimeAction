#include"DxLib.h"
#include "GrapeFruit.h"

GRAPEFRUIT::GRAPEFRUIT()
{
	gurepon = LoadGraph("images/Gurepon.png");
	shootcount = 0;
}

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player)
{
	gurepon = LoadGraph("images/Gurepon.png");
	shootcount = 0;
	this->player = player;
}

void GRAPEFRUIT::Updata()
{

}

void GRAPEFRUIT::Move()
{
	DrawRotaGraph2(0, 0, 40, 0, 1, angle, gurepon, TRUE);
	ChangeAngle();
}

void GRAPEFRUIT::ShotFruitJuice()
{
	if (shootcount++ % 120 == 0) 
	{

	}
}

void GRAPEFRUIT::Hit()
{

}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw() const
{

}