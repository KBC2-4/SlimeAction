#include "StageSelect.h"
#include "Title.h"
#include "GameMain.h"
#include "DxLib.h"

STAGE_SELECT::STAGE_SELECT()
{
	//background_image[0] = LoadGraph("Resource/Images/Stage/BackImpause_cash.bmp");
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	guid_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	buttonguid_font = CreateFontToHandle("���C���I", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	player = new PLAYER;
	stage = new STAGE("StageSelect");
	element = new ELEMENT();

	int scrollx = -(1460 - 500);
	stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
	player->SetPlayerX(80); //�v���C���[�̉�ʓ����W���Z�b�g

	player_map_x = 0;
	player_map_y = 0;


	for (int i = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			switch (stage->GetMapData(i,j))
			{

			case 101:
				stage_return.x = j * MAP_CEllSIZE;
				stage_return.y = i * MAP_CEllSIZE;

			case 102:
			case 103:
				stage_move[1].x = j * MAP_CEllSIZE;
				stage_move[1].y = i * MAP_CEllSIZE;
			}
		}
	}
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

	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY());
	
	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player,stage);
	
	//�������烊�X�^�[�g
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}


	if ((player_map_x >= stage_return.x  - MAP_CEllSIZE / 2) && (player_map_x <= stage_return.x + MAP_CEllSIZE / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new Title(); }
	}

	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + MAP_CEllSIZE / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(false, 0, "Stage01"); }
	}
	
	return this;
}

void STAGE_SELECT::Draw() const
{
	//�X�e�[�W�w�i
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(static_cast<int>(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw();
	stage->Draw();

	//�v���C���[�̕`��
	player->Draw(stage);

	if ((player_map_x >= stage_return.x - MAP_CEllSIZE / 2) && (player_map_x <= stage_return.x + MAP_CEllSIZE / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawOvalAA(stage_return.x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_return.y - MAP_CEllSIZE, 100, 80, 18, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_return.x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_return.y - MAP_CEllSIZE, 99, 79, 18, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_return.x + MAP_CEllSIZE / 2, stage_return.y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawStringToHandle(stage_return.x + stage->GetScrollX() - 20, stage_return.y - MAP_CEllSIZE - 20, "�߂�", 0x6AF6C5, guid_font, 0x000000);

		DrawCircleAA(stage_return.x + stage->GetScrollX(), stage_return.y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_return.x + stage->GetScrollX() - 7, stage_return.y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}

	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + MAP_CEllSIZE / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawOvalAA(stage_move[1].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE, 100, 80, 18, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_move[1].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE, 99, 79, 18, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[1].x + MAP_CEllSIZE / 2, stage_move[1].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendStringToHandle(stage_move[1].x + stage->GetScrollX() - 55, stage_move[1].y - MAP_CEllSIZE - 10, 0.6f , 0.6f, "�P�X�e�[�W", 0xD65701, guid_font, 0x000000);

		DrawCircleAA(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_move[1].x + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}
}