#include "StageSelect.h"
#include "DxLib.h"

STAGE_SELECT::STAGE_SELECT()
{
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	player = new PLAYER;
	stage = new STAGE;
	element = new ELEMENT();
}

STAGE_SELECT::~STAGE_SELECT()
{
	delete player;
	delete stage;
	delete element;
}

AbstractScene* STAGE_SELECT::Update()
{
	DeleteGraph(background_image[0]);
	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player, stage);
	
	return this;
}

void STAGE_SELECT::Draw() const
{
	//ステージ背景
	DrawGraph(int(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//ステージの描画
	element->Draw();
	stage->Draw();

	//プレイヤーの描画
	player->Draw(stage);
}