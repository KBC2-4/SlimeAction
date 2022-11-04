#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	x = 200;
	animation_timer = 0;
	animation_type = 0;
	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::TOMATO(PLAYER* player, STAGE* stage)
{
	x = 200;
	this->player = player;
	this->stage = stage;
	animation_timer = 0;
	animation_type = 0;
	state = ENEMY_STATE::WALL;

	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::~TOMATO()
{
	delete[] image;
}
void TOMATO::Update()
{

	//マップ上の座標の設定
	map_x = x / MAP_CEllSIZE;
	map_y = y / MAP_CEllSIZE;
	Move();
	Animation();
	Hit();

	if ((fabsf(player->GetPlayerX() - x) < 240) && (state != ENEMY_STATE::DETH))
	{
		state = ENEMY_STATE::WALL;
	}

	//画面外に出た処理
	if (y > 720)
	{
		state = ENEMY_STATE::IDOL;
	}
}

void TOMATO::Move()
{
	//落下状態の時の処理
	if (state == ENEMY_STATE::WALL)
	{
		y += WALL_SPEED;
	}
}


void TOMATO::Hit()
{
	//地面やブロックとの当たり判定
	if (state == ENEMY_STATE::WALL)
	{
		if (stage->GetMapDat(map_y, map_x) != 0)
		{
			state = ENEMY_STATE::DETH;
		}
	}
}

void TOMATO::Animation()
{
	//アイドル状態ならアイドルの時の画像を使用
	if (state == ENEMY_STATE::IDOL)
	{
		now_image = image[0];
	}
	//落下状態の時の画像の入れ替え
	if (state == ENEMY_STATE::WALL)
	{
		if (++animation_timer % ANIMATION_TIME == 0)
		{
			now_image = image[(++animation_type % 2) + 1];
		}
	}
}


void TOMATO::Draw()const
{
	DrawRotaGraph(x + stage->GetScrollX(), y, 1, 0, now_image, TRUE);
	DrawCircle(x, y, 33, 0xffffff, FALSE);
	DrawFormatString(100, 100, 0xffffff, "%d,%d", map_x, map_y);
}