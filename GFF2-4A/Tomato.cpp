#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	x = 0;
	image_rate = 0.;
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

	image_rate = 0.;
	animation_timer = 0;
	animation_type = 0;
	state = ENEMY_STATE::IDOL;

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
	//画像サイズが元の大きさ一定以上になったら
	if (image_rate >= 1)
	{
		//プレイヤーが一定範囲以内に入っている間落ちる
		if ((fabsf(player->GetPlayerX() - (x + stage->GetScrollX())) < 240) && (state == ENEMY_STATE::IDOL))
		{
			animation_timer = 0; 
			state = ENEMY_STATE::WALL;
		}
		else if ((state != ENEMY_STATE::WALL) && (state != ENEMY_STATE::DETH))
		{
			state = ENEMY_STATE::IDOL;
		}
	}
	//マップ上の座標の設定
	map_x = x / MAP_CEllSIZE;
	map_y = y / MAP_CEllSIZE;
	
	Move();
	Animation();
	Hit();

	//爆発し終え時または、画面外に出たらアイドル状態にする
	if(((state==ENEMY_STATE::DETH) && (animation_timer > 60)) || (y > 720))
	{
		state = ENEMY_STATE::IDOL;
		image_rate = 0;
		//スポーン地点に移動
		x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
		y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	}

	
}

void TOMATO::Move()
{
	//落下状態の時の処理
	if (state == ENEMY_STATE::WALL)
	{
		y += FALL_SPEED;
	}
}


void TOMATO::Hit()
{
	//地面やブロックとの当たり判定
	if (state == ENEMY_STATE::WALL)
	{
		if ((stage->GetMapDat(map_y, map_x) != 0) && stage->GetMapDat(map_y, map_x) != 93)
		{
			state = ENEMY_STATE::DETH;
			animation_timer = 0;
		}
	}
}

void TOMATO::Animation()
{

	if (++animation_timer % ANIMATION_TIME == 0)
	{
		//アイドル状態ならアイドルの時の画像を使用
		if (state == ENEMY_STATE::IDOL)
		{
			if (image_rate < 1.0)
			{
				image_rate += 0.1;
			}
			else
			{
				image_rate = 1.0;
			}
			now_image = image[0];
		}
		//落下状態の時の画像の入れ替え
		if (state == ENEMY_STATE::WALL)
		{
			now_image = image[(++animation_type % 2) + 1];
		}
		//ブロックに当たった時
		if (state == ENEMY_STATE::DETH)
		{
	
		}
	}
}


void TOMATO::Draw()const
{
	//画面外に出たら描画しない
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280))
	{
		DrawRotaGraph(x + stage->GetScrollX(), y, image_rate, 0, now_image, TRUE);
	}
}