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
	//���������_�Ƀv���C���[�Ƃ̊p�x���v�Z
	rad = atan2f(player->GetPlayerY() - y, player->GetPlayerX() - (x + stage->GetScrollX()));
}