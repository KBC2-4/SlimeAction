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
}

AbstractScene* GAMEMAIN::Update()
{
	player->Update(element,stage);
	if (player->IsDeath()) {
		return new GAMEMAIN();
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
	
}