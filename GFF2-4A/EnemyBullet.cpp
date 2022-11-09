#include "EnemyBullet.h"

ENEMYBULLET::ENEMYBULLET() 
{
	player = nullptr;
	stage = nullptr;
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
	hit_flg = false;
	old_hit_flg = false;
	rad_x = 0.0;
	map_x = 0;
	map_y = 0;
}

ENEMYBULLET::ENEMYBULLET(PLAYER* argu_player ,STAGE* aug_stage,int x,int y ,double dis ,float scroll) 
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
	hit_flg = false;
	old_hit_flg = false;
	rad_x = dis;
	scroll_x = scroll;
	map_x = 0;
	map_y = 0;
}

void ENEMYBULLET::Draw() const 
{
	DrawBox(bullet_x + scroll_x, bullet_y, bullet_x + scroll_x + 40, bullet_y + 40, 0xff00ff, FALSE);
}

void ENEMYBULLET::Update() 
{
   	dis_x = (player_x - rad_x) - (my_x + scroll_x);
	dis_y = player_y - my_y;
	
	hypote = sqrt((dis_x*dis_x) + (dis_y*dis_y));

	bullet_sx = dis_x / hypote * 20;
	bullet_sy = dis_y / hypote * 20;

	Move();
	Hit();
	if (hit_flg)
	{
		if (player->GetLife() > 0)
		{
			player->SetLife(player->GetLife() - 1);
			old_hit_flg = true;
		}
		else
		{
			player->SetLife(0);
		}
	}

}

void ENEMYBULLET::Move() 
{
	//弾の移動
	bullet_x += bullet_sx;
	bullet_y += bullet_sy;

	//弾が画面外に行ったら消えるフラグを真に
	mapd_x = (bullet_x - scroll_x) / 80;
	mapd_y = bullet_y / 80;
	
	map_x = (int)floor(mapd_x);
 	map_y = (int)floor(mapd_y);

	if (stage->HitMapDat(map_y + 1, map_x) != 0)
	{
		bullet_flag = true;
	}
}

void ENEMYBULLET::Animation() 
{

}

void ENEMYBULLET::Hit()
{
	float px1, py1, px2, py2;
	float bx1, by1, bx2, by2;

	px1 = player_x;
	px2 = px1 + 80;
	py1 = player_y;
	py2 = py1 + 40;

	bx1 = bullet_x + scroll_x;
	bx2 = bx1 + 40;
	by1 = bullet_y;
	by2 = by1 + 40;

	DrawBox(px1, py1, px2, py2, 0xff0000, TRUE);
	DrawBox(bx1, by1, bx2, by2, 0x00ffff, TRUE);

	if (((px2 >= bx1 && px1 <= bx1) || (px1 <= bx2 && px2 >= bx2)) && ((py1 <= by2 && py2 >= by2) || (by1 <= py2 && by1 >= py1)))
	{
		if (!old_hit_flg)
		{
			hit_flg = true;
		}
	}
	else
	{
		hit_flg = false;
		old_hit_flg = false;
	}
	
}
