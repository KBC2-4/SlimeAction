#include "GameMain.h"
#include <vector>

GAMEMAIN::GAMEMAIN()
{
	std::vector<std::vector<int>> spawn_point;
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	time = 0.0;
	tomaton_count = 0;
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = nullptr;
	tomaton = nullptr;

	//とまトン生成する数を数える
	for (int i = 0,point = 0 ; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 93)
			{
				tomaton_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}
	//とまトンの生成
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO*[tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player,stage, spawn_point[i][0],spawn_point[i][1]);
		}
	}

	//スポーンポイントを削除
	spawn_point.clear();

	//グレポンを生成する数を数える
	for (int i = 0, point = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 92)
			{
				gurepon_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}

	//グレポンの生成
	if (gurepon_count > 0)
	{
		gurepon = new GRAPEFRUIT * [gurepon_count];
		for (int i = 0; i < gurepon_count; i++)
		{
			gurepon[i] = new GRAPEFRUIT(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
	//とまトンの削除
	for (int i = 0; i < tomaton_count; i++)
	{
		delete tomaton[i];
	}
	delete[] tomaton;
	//グレポンの削除
	for (int i = 0; i < gurepon_count; i++) {
		delete gurepon[i];
	}
	delete[] gurepon;
	delete element;
}

AbstractScene* GAMEMAIN::Update()
{
	
	player->Update(element);
	if (player->IsDeath()) {
		return new GAMEMAIN();
	}
	element->Update(player);
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Update();
	}
	for (int i = 0; i < gurepon_count; i++)
	{
		gurepon[i]->Update();
	}
	element->Update(player);

	return this;
}

void GAMEMAIN::Draw() const
{
	DrawGraph(int(STAGE::GetScrollX()) % 3840 + 3840, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(STAGE::GetScrollX()) % 3840, /*scroll_y*/0, background_image[0], FALSE);

	//ステージの描画

	player->Draw();
	element->Draw();
	stage->Draw();
	//プレイヤーの描画
	player->Draw();
	//とまトンの描画
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Draw();
	}
	//グレポンの描画
	for (int i = 0; i < gurepon_count; i++)
	{
		gurepon[i]->Draw();
	}
	
}