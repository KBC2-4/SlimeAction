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
	delete gurepon;
}

AbstractScene* GAMEMAIN::Update()
{
	stage->Update();
	player->Update();
	gurepon->Update();
	

	return this;
}

void GAMEMAIN::Draw() const
{
	//ステージの描画
	stage->Draw();
	//プレイヤーの描画
	player->Draw();
	//グレポンの描画
	gurepon->Draw();
	
}