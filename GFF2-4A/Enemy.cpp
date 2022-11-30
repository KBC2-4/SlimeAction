#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Enemy.h"

ENEMY::ENEMY()
{
	player = nullptr;
	stage = nullptr;
	item = nullptr;

	rad = 0.0;
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;
	image = nullptr;
	animation_timer = 0;
	animation_type = 0;

	state = ENEMY_STATE::IDOL;
}

void ENEMY::ChangeAngle()
{
	//自分を原点にプレイヤーとの角度を計算
	rad = atan2f(player->GetPlayerY() - (y + stage->GetScrollY()), player->GetPlayerX() - (x + stage->GetScrollX()));
	if (rad > 170 * (PI / 180))
	{
		rad = 170 * (PI / 180);
	}

	if (rad < 10 * (PI / 180))
	{
		rad = 10 * (PI / 180);
	}
}