#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Enemy.h"



ENEMY::ENEMY()
{
	player = nullptr;
	stage = nullptr;
	rad = 0.0;
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;
	image = nullptr;
	now_image = 0;
	state = ENEMY_STATE::IDOL;
}

void ENEMY::ChangeAngle()
{
	//自分を原点にプレイヤーとの角度を計算
	rad = atan2f(player->GetPlayerY() - y, player->GetPlayerX() - (x + stage->GetScrollX()));
}