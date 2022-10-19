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
}

AbstractScene* GAMEMAIN::Update()
{
	//プレイヤーの表示
	int old_playerx = player->GetPlayerX();
	player->Update();
	stage->Update(player->GetPlayerX() - old_playerx, player->GetPlayerY() - 40);
	tomaton->Updata();
	return this;
}

void GAMEMAIN::Draw() const
{
	//プレイヤーの描画
	player->Draw();
	//とまとんの描画
	tomaton->Draw();
	//ステージの描画
	stage->Draw();
}