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

TOMATO::TOMATO(PLAYER* player)
{
	x = 200;
	this->player = player;
	animation_timer = 0;
	animation_type = 0;
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
	Move();
	Animation();

}

void TOMATO::Move()
{
	state = ENEMY_STATE::WALL;
	//落下状態の時の処理
	if (state == ENEMY_STATE::WALL)
	{
		y += WALL_SPEED;
	}
}


void TOMATO::Hit()
{
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
	DrawGraph(x, y, now_image, TRUE);
	DrawCircle(x + IMAGE_SIZE / 2, y + IMAGE_SIZE / 2, 33, 0xffffff, FALSE);
}