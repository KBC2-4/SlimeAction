#define _USE_MATH_DEFINES
#include<math.h>
#include "EnemyBullet.h"

ENEMYBULLET::ENEMYBULLET() 
{
	player = nullptr;
	stage = nullptr;
	player_x = 0.0;
	player_y = 0.0;
	x = 0;
	y = 0;
	rad = 0.0;
	map_x = 0;
	map_y = 0;
}

ENEMYBULLET::ENEMYBULLET(PLAYER* argu_player ,STAGE* aug_stage,int x,int y ,double rad,float scroll)
{
	player = argu_player;
	player_x = player->GetPlayerX();
	player_y = player->GetPlayerY();
	this->x = x;
	this->y = y;
	this->rad = rad;
	delete_flg = false;
	scroll_x = scroll;
	map_x = 0;
	map_y = 0;
}

void ENEMYBULLET::Draw() const 
{
	DrawBox(x + scroll_x, y, x + scroll_x + 40, y + 40, 0xff00ff, TRUE);
}

void ENEMYBULLET::Update() 
{
	Move();
	Hit();
	if (delete_flg)
	{
		if (player->GetLife() > 0)
		{
			//player->SetLife(player->GetLife() - 1);
		}
		else
		{
			player->SetLife(0);
		}
	}

}

void ENEMYBULLET::Move() 
{
	//’e‚ÌˆÚ“®
	x += BULLET_SPEED * cos(rad);
	y += BULLET_SPEED * sin(rad);

}

void ENEMYBULLET::Animation() 
{

}

void ENEMYBULLET::Hit()
{
	double px1, py1, px2, py2;
	double bx1, by1, bx2, by2;

	px1 = player_x;
	px2 = px1 + 80.0;
	py1 = player_y;
	py2 = py1 + 40.0;

	bx1 = x + scroll_x;
	bx2 = bx1 + 20.0;
	by1 = y;
	by2 = by1 + 20.0;

	if (((px2 >= bx1 && px1 <= bx1) || (px1 <= bx2 && px2 >= bx2)) && ((py1 <= by2 && py2 >= by2) || (by1 <= py2 && by1 >= py1)))
	{
		delete_flg = true;
	}

	if (stage->HitMapDat(map_y, map_x))
	{
		delete_flg = true;
	}
}
