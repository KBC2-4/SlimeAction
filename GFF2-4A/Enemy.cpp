#include "DxLib.h"
#define _USE_MATH_DEFINES
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
	image = nullptr;
	now_image = 0;
	state = ENEMY_STATE::IDOL;
}

void ENEMY::ChangeAngle()
{
	//プレイヤーを原点としてプレイヤーと自分の角度の計算
	float rad = atan2f(y - player->GetPlayerY(), x - player->GetPlayerX());
	//ラジアンを角度に変換
	angle = 180 / M_PI * rad;
}