#include "DxLib.h"
#include "Lemon.h"

LEMON::LEMON()
{
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;
	if (LoadGraph("") == -1)
	{
		throw "image/Lemon";
	}
}

void LEMON::Move()
{

}

void LEMON::ShotFruitJuice()
{

}

void LEMON::Animation()
{

}

void LEMON::Draw() const
{

}