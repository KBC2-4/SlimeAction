#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	x = 0;
	image_rate = 1.0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	animation_timer = 0;
	animation_type = 0;
	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::TOMATO(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//スポーン場所の設定
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	this->player = player;
	this->stage = stage;

	image_rate = 1.0;
	animation_timer = 0;
	animation_type = 0;
	state = ENEMY_STATE::IDOL;

	image = new int[9];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
	if (LoadDivGraph("Resource/Images/Enemy/tomaton_Break.png", 6, 6, 1, 80, 80, image + 3) == -1)
	{
		throw "Resource/Images/Enemy/tomaton_Break.png";
	}

}

TOMATO::~TOMATO()
{
	delete[] image;
}
void TOMATO::Update()
{
	++animation_timer;
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		//プレイヤーが一定範囲以内に入っている間落ちる
		if ((fabsf(player->GetPlayerX() - (x + stage->GetScrollX())) < 240) && (IdolAnimation()))
		{
			animation_timer = 0;
			state = ENEMY_STATE::FALL;
		}
		break;
	case ENEMY_STATE::FALL:
		Move();
		FallAnimation();
		break;
	case ENEMY_STATE::DETH:
		//爆発し終え時または、画面外に出たらアイドル状態にする
		if(DethAnimation() || (y > 720))
		{
			state = ENEMY_STATE::IDOL;
			image_rate = 0;
			//スポーン地点に移動
			x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
			y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

		}
		break;
	default:
		break;
	}
	//マップ上の座標の設定
	map_x = x / MAP_CEllSIZE;
	map_y = (y - IMAGE_SIZE / 2) / MAP_CEllSIZE;

	Hit();
}

void TOMATO::Move()
{
	y += FALL_SPEED;
}


void TOMATO::Hit()
{
	float px1, py1, px2, py2;
	float bx1, by1, bx2, by2;

	px1 = player->GetPlayerX() - 30;
	px2 = px1 + 60;
	py1 = player->GetPlayerY();
	py2 = py1 + 40;

	bx1 = x - IMAGE_SIZE / 2;
	bx2 = bx1 + IMAGE_SIZE;
	by1 = y;
	by2 = by1 + IMAGE_SIZE / 2;

	//プレイヤーとの当たり判定
	if (((px2 >= bx1 && px1 <= bx1) || (px1 <= bx2 && px2 >= bx2)) && ((py1 <= by2 && py2 >= by2) || (by1 <= py2 && by1 >= py1)))
	{
		player->SetLife(player->GetLife() - 2);
	}
	//地面やブロックとの当たり判定
	if ((state==ENEMY_STATE::FALL)&&(stage->GetMapDat(map_y + 1, map_x) != 0) && stage->GetMapDat(map_y + 1, map_x) != 93)
	{
		state = ENEMY_STATE::DETH;
		animation_timer = 0;
	}
}

bool TOMATO::IdolAnimation()
{
	bool ret = false;
	//アニメーション
	if (animation_timer % ANIMATION_TIME == 0)
	{
		if (image_rate < 1.0) //とまとんのサイズを大きくする
		{
			image_rate += 0.1;
		}
		else //とまとんのサイズが元のサイズより大きくなったら元のサイズに戻す
		{
			image_rate = 1.0;
			ret = true;
		}
		now_image = image[0];
	}
	return ret;
}
void TOMATO::FallAnimation()
{
	//アニメーション
	if (animation_timer % ANIMATION_TIME == 0)
	{
		now_image = image[(++animation_type % 2) + 1];
	}
}


bool TOMATO::DethAnimation()
{
	bool ret = false;
	//アニメーション
	if (animation_timer % ANIMATION_TIME == 0)
	{
		now_image = image[(++animation_type % 6) + 1];
	}
	//アニメーションの終了
	if (animation_timer > 30)
	{
		ret = true;
	}

	return ret;
}


void TOMATO::Draw()const
{
	//画面外に出たら描画しない
	if ((x + stage->GetScrollX() > -IMAGE_SIZE) && (x + stage->GetScrollX() < 1280 + IMAGE_SIZE))
	{
		DrawRotaGraph(x + stage->GetScrollX(), y, image_rate, 0, now_image, TRUE);
	}
}