#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	//とまとんの生成場所の数用の変数
	int spawn_tomaton_count = 0;
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
				spawn_tomaton_count++;
			}
		}
	}
	if (spawn_tomaton_count > 0)
	{
		tomaton = new TOMATO[spawn_tomaton_count];
	}
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
	delete tomaton;
}

AbstractScene* GAMEMAIN::Update()
{
	stage->Update();
	player->Update(element);
	tomaton->Update();
	return this;
}

void GAMEMAIN::Draw() const
{
	//ステージの描画
	stage->Draw();
	//プレイヤーの描画
	player->Draw();
	//とまとんの描画
	tomaton->Draw();
}