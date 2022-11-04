#include"DxLib.h"
#include "GrapeFruit.h"
#include<math.h>

GRAPEFRUIT::GRAPEFRUIT()
{
	image = new int[100];
	if (image[0] = LoadGraph("Resource/Images/Enemy/gurepon.png") == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	hitflg = false;
}

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player)
{
	image = new int [100];
	if(LoadDivGraph("Resource/Images/Enemy/gurepon.png",1,1,1,80,80,image) == -1) 
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	this->player = player;
}

void GRAPEFRUIT::Update()
{
	ChangeAngle();
	ShotFruitJuice();
}

void GRAPEFRUIT::Move()
{

	
}

void GRAPEFRUIT::ShotFruitJuice()
{
	if (++shootcount % 120 == 0) 
	{
		
	}
}

void GRAPEFRUIT::Hit()
{

}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw(float scroll_x) const
{
	DrawRotaGraph2(640, 40, 40, 0, 2, rad, image[0], TRUE);
	SetFontSize(24);
	DrawFormatString(50, 50, 0xff0000, "%lf", rad);
	//DrawGraph(0, 0, image[0],TRUE);
}