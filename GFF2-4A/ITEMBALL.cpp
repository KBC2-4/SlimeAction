#include "ITEMBALL.h"




ITEMBALL::ITEMBALL() 
{
	map_x = 0;
	map_y = 0;
	player = nullptr;
	item_x = 0;
	item_y = 0;
	item = 0;
	scrool_x = 0;
	test1 = 0;
	test2 = 0;
	test3 = 0;
	test4 = 0;
	test5 = 0;
	test6 = 0;
	test7 = 0;
	test8 = 0;
}

ITEMBALL::ITEMBALL(float enemy_x, float enemy_y, int e_mapy, int e_mapx, PLAYER* r_player, STAGE* r_stage, float scrool)
{
	if ((item = (LoadGraph("Resource/Images/Player/SlimeBullet2.png"))) == -1)
	{
		throw "Resource/Images/Enemy/ThrowSlime.png";
	}
	map_x = e_mapx;
	map_y = e_mapy;
	player = r_player;
	scrool_x = scrool;
	stage = r_stage;
	item_x = enemy_x;
	item_y = enemy_y;
	test1 = 0;
	test2 = 0;
	test3 = 0;
	test4 = 0;
	test5 = 0;
	test6 = 0;
	test7 = 0;
	test8 = 0;
}

ITEMBALL::~ITEMBALL() {};

void ITEMBALL::Draw() const 
{
	DrawRotaGraph((static_cast<int>(GetDrawX())), item_y + 70, 1, 0, item, TRUE);
	DrawBox(test1, test3, test2, test4, 0xff00ff, FALSE);
	DrawBox(test5, test7, test6, test8, 0x00ff00, FALSE);
}

void ITEMBALL::Update()
{
	if ((item_x + stage->GetScrollX() > 0) && (item_x + stage->GetScrollX() < 1280))
	{
		PlayerHit();
	}
}

void ITEMBALL::PlayerHit()
{
	float px1, py1, px2, py2;
	float bx1, by1, bx2, by2;

	px1 = player->GetPlayerX() - 30;
	px2 = px1 + 60;
	py1 = player->GetPlayerY();
	py2 = py1 + 40;

	bx1 = GetDrawX() - 10;
	bx2 = bx1 + _BALL_RADIUS;
	by1 = (item_y + _BALL_RADIUS) + 40;
	by2 = by1 + _BALL_RADIUS;

	test1 = px1;
	test2 = px2;
	test3 = py1;
	test4 = py2;
	test5 = bx1;
	test6 = bx2;
	test7 = by1;
	test8 = by2;

	if (px1 < bx2 && bx1 < px2 && py1 < by2 && by1 < py2)
	{
		if (player->GetLife() < 5)
		{
			player->SetLife(player->GetLife() + 1);
			delete_flg = true;
		}
	}
}

float ITEMBALL::GetDrawX() const
{
	float ret = (item_x - scrool_x) + (static_cast<double>(scrool_x) + stage->GetScrollX());
	return ret;
}
