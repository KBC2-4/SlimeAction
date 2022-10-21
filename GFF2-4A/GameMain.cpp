#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = new TOMATO(player);
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
	player->Update();
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