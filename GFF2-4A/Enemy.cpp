#include "DxLib.h"
#include<math.h>
#include "Enemy.h"



ENEMY::ENEMY()
{
	this->player = nullptr;
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;
	w = 0;
	h = 0;
	angle = 0;
	image = 0;
	state = ENEMY_STATE::IDOL;
}

void ENEMY::ChangeAngle()
{
	float rad = atan2f(player->GetPlayerX() - x, player->GetPlayerY() - y);

	//angle = 
}