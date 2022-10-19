#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{

}


void TOMATO::Updata()
{

}
TOMATO::TOMATO(PLAYER* player)
{
	x = 200;
	this->player = player;
}


void TOMATO::Updata()
{
	Move();
}

void TOMATO::Move()
{
	y += 2;
}

void TOMATO::ShotFruitJuice()
{

}

void TOMATO::Hit()
{

}

void TOMATO::Animation()
{

}


void TOMATO::Draw()const
{
	DrawCircle(x, y, 30, 0xff0000, TRUE);
	//DrawGraph(x, y, image, TRUE);
}