#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
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