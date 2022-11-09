#include "EnemyBullet.h"

ENEMYBULLET::ENEMYBULLET() 
{
	player = nullptr;
	player_x = 0.0;
	player_y = 0.0;
	bullet_x = 0.0;
	bullet_y = 0.0;
	hypote = 0.0;
	my_x = 0.0;
	my_y = 0.0;
	dis_x = 0.0;
	dis_y = 0.0;
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	bullet_flag = false;
	rad_x = 0.0;
}

ENEMYBULLET::ENEMYBULLET(PLAYER* argu_player ,int x,int y ,double dis ,float scroll) 
{
	player = argu_player;
	player_x = player->GetPlayerX();
	player_y = player->GetPlayerY();
	bullet_x = x;
	bullet_y = y;
	hypote = 0.0;
	my_x = x;
	my_y = y;
	dis_x = 0.0;
	dis_y = 0.0;
	bullet_sx = 0.0;
	bullet_sy = 0.0;
	bullet_flag = true;
	rad_x = dis;
	scroll_x = scroll;
}

void ENEMYBULLET::Draw(STAGE* stage) const 
{
	DrawBox(bullet_x + scroll_x, bullet_y, bullet_x + scroll_x + 40, bullet_y + 40, 0xff00ff, TRUE);
}

void ENEMYBULLET::Update() 
{
   	dis_x = (player_x - rad_x) - (my_x + scroll_x);
	dis_y = player_y - my_y;
	
	hypote = sqrt((dis_x*dis_x) + (dis_y*dis_y));

	bullet_sx = dis_x / hypote * 20;
	bullet_sy = dis_y / hypote * 20;

	Move();
}

void ENEMYBULLET::Move() 
{
	//弾の移動
	bullet_x += bullet_sx;
	bullet_y += bullet_sy;

	//弾が画面外に行ったら消えるフラグを真に
	if (bullet_x < 0 || bullet_x>1280 || bullet_y < 0 || bullet_y>720)
		bullet_flag = true;
}

void ENEMYBULLET::Animation() 
{

}

void ENEMYBULLET::Hit()
{

}
