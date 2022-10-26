#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Enemy.h"



ENEMY::ENEMY()
{
	this->player = nullptr;
	rad = 0.0f;
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;
	angle = 0;
	image = nullptr;
	now_image = 0;
	state = ENEMY_STATE::IDOL;
}

void ENEMY::ChangeAngle()
{
	//プレイヤーを原点としてプレイヤーと自分の角度の計算
	rad = atan2f(y - player->GetPlayerY(), x - player->GetPlayerX());
	//ラジアンを角度に変換
	angle = 180 / M_PI * rad;
	if (angle < 90)
	{
		angle = 90;
	}
	if (angle > 180)
	{
		angle = 180;
	}

}