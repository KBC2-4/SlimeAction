#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	time = 0.0;
	tomaton_count = 0;
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = nullptr;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 93)
			{
				tomaton_count++;
			}
		}
	}
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO*[tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player);
		}

	}
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;

	//とまとんの削除
	for (int i = 0; i < tomaton_count; i++)
	{
		delete tomaton[i];
	}
	delete[] tomaton;
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
	//とまとんの描画
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Draw();
	}
	
}