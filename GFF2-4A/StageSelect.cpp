#include "StageSelect.h"
#include "DxLib.h"

STAGE_SELECT::STAGE_SELECT()
{
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImpause_cash.bmp");
	player = new PLAYER;
	stage = new STAGE("StageSelect");
	element = new ELEMENT();

	int scrollx = -(1460 - 500);
	stage->SetScrollX(scrollx);	//スポーン地点をセット
	player->SetPlayerX(80); //プレイヤーの画面内座標をセット
}

STAGE_SELECT::~STAGE_SELECT()
{
	DeleteGraph(background_image[0]);
	delete player;
	delete stage;
	delete element;
}

AbstractScene* STAGE_SELECT::Update()
{
	
	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player,stage);
	
	//落ちたらリスタート
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}

	return this;
}

void STAGE_SELECT::Draw() const
{
	//ステージ背景
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(static_cast<int>(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//ステージの描画
	element->Draw();
	stage->Draw();

	//プレイヤーの描画
	player->Draw(stage);
}