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
}

ITEMBALL::ITEMBALL(float enemy_x, float enemy_y, int e_mapy, int e_mapx, PLAYER* r_player, STAGE* r_stage, float scroolx,float scrooly)
{
	if ((item = (LoadGraph("Resource/Images/Player/SlimeBullet2.png"))) == -1)
	{
		throw "Resource/Images/Enemy/ThrowSlime.png";
	}
	map_x = e_mapx;
	map_y = e_mapy;
	player = r_player;
	scrool_x = scroolx;
	scrool_y = scrooly;
	stage = r_stage;
	item_x = enemy_x;
	item_y = enemy_y;
}

ITEMBALL::~ITEMBALL() {
	DeleteGraph(item);
};

void ITEMBALL::Draw() const
{
	DrawRotaGraph((static_cast<int>(GetDrawX())), (static_cast<int>(GetDrawY())) + 30, 1, 0, item, TRUE);
}

void ITEMBALL::Update()
{
	PlayerHit();
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
	by1 = GetDrawY() + _BALL_RADIUS;
	by2 = by1 + _BALL_RADIUS;


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

float ITEMBALL::GetDrawY() const
{
	float ret = (item_y - scrool_y) + (static_cast<double>(scrool_y) + stage->GetScrollY());

	return ret;
}