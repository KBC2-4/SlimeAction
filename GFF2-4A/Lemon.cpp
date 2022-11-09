#include "DxLib.h"
#include "Lemon.h"

LEMON::LEMON()
{
	x = 0;
	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/lemoner.png")) == -1)
	{
		throw "Resource/Images/Enemy/lemoner.png";
	}
}


LEMON::LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//ƒXƒ|[ƒ“êŠ‚ÌÝ’è
	x = spawn_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	y = spawn_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	this->player = player;
	this->stage = stage;

	state = ENEMY_STATE::IDOL;

	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/lemoner.png")) == -1)
	{
		throw "Resource/Images/Enemy/lemoner.png";
	}
}

void LEMON::Update()
{

}
void LEMON::Move()
{

}

void LEMON::ShotFruitJuice()
{

}

void LEMON::Hit()
{

}

void LEMON::Animation()
{

}

void LEMON::Draw() const
{

}