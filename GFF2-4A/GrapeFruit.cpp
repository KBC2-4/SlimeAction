#include"DxLib.h"
#include "GrapeFruit.h"
#include<math.h>

GRAPEFRUIT::GRAPEFRUIT()
{
	image = new int[100];
	if (image[0] = LoadGraph("Resource/Images/Enemy/gurepon.png") == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	shootcount = 0;
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
}

void GRAPEFRUIT::Move()
{

	
}

void GRAPEFRUIT::ShotFruitJuice()
{
	/*if (shootcount++ % 120 == 0) 
	{

	}*/
}

void GRAPEFRUIT::Hit()
{

}

void GRAPEFRUIT::Animation()
{

}


void GRAPEFRUIT::Draw() const
{
	DrawRotaGraph2(640, 40, 40, 0, 2, sin(angle), image[0], TRUE);
	//DrawGraph(0, 0, image[0],TRUE);
}