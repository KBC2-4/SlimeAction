#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{

}

TOMATO::TOMATO(PLAYER* player)
{
	this->player = player;
}

void TOMATO::Move()
{

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
	DrawCircle(x, y, 10, 0xff0000, TRUE);
	//DrawGraph(x, y, image, TRUE);
}