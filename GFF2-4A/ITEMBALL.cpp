#include "ITEMBALL.h"

ITEMBALL::ITEMBALL() 
{
	item_x = 0;
	item_y = 0;
	item = 0;
}

ITEMBALL::ITEMBALL(float enemy_x, float enemy_y)
{
	if (item = (LoadGraph("Resource/Images/Enemy/ThrowSlime.png")) == -1)
	{
		throw "Resource/Images/Enemy/ThrowSlime.png";
	}
	item_x = enemy_x;
	item_y = enemy_y;
}

ITEMBALL::~ITEMBALL() {};

void ITEMBALL::Draw() const 
{
	DrawGraph(item_x, item_y, item, TRUE);
}

void ITEMBALL::Update()
{

}

void ITEMBALL::PlayerHit()
{

}
