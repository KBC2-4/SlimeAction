#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	time = 0.0;

	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = new TOMATO(player);
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
	delete element;
	delete gurepon;
}

AbstractScene* GAMEMAIN::Update()
{
	stage->Update();
	player->Update();
	player->Update(element);
	if (player->IsDeath()) {
		return new GAMEMAIN();
	}
	stage->Update();
	player->Update();
	gurepon->Update();
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
	//プレイヤーの描画	player->Draw();
	player->Draw();
	//グレポンの描画
	gurepon->Draw();
	
}