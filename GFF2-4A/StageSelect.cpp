#include "StageSelect.h"
#include "Title.h"
#include "GameMain.h"
#include "DxLib.h"
#include "Option.h"

STAGE_SELECT::STAGE_SELECT()
{
	//background_image[0] = LoadGraph("Resource/Images/Stage/BackImpause_cash.bmp");
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage1.png");
	if ((background_music = LoadSoundMem("Resource/Sounds/BGM/title.wav")) == -1) {
		throw "Resource/Sounds/BGM/title.wav";
	}
	guid_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	buttonguid_font = CreateFontToHandle("メイリオ", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	stagename_font = CreateFontToHandle("メイリオ", 36, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	stage = new STAGE("StageSelect");
	player = new PLAYER(stage);
	element = new ELEMENT();

	//スポーン地点をセット
	stage->SetScrollX(-(stage->GetSpawnPoint().y - MAP_CEllSIZE));
	stage->SetScrollY(-(stage->GetSpawnPoint().x - MAP_CEllSIZE * stage->GetMapSize().y));
	player->SetPlayer_Screen(stage->GetSpawnPoint());

	player_map_x = 0;
	player_map_y = 0;

	effect_timer = 0;
	stage_return = { 0,0 };
	*stage_move = { 0,0 };

	for (int i = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			switch (stage->GetMapData(i, j))
			{

			case 101:
				stage_return.x = j * MAP_CEllSIZE;
				stage_return.y = i * MAP_CEllSIZE;

			case 102:
			case 103:
				stage_move[1].x = j * MAP_CEllSIZE;
				stage_move[1].y = i * MAP_CEllSIZE;

			case 104:
			case 105:
				stage_move[2].x = j * MAP_CEllSIZE;
				stage_move[2].y = i * MAP_CEllSIZE;

			case 106:
			case 107:
				stage_move[3].x = j * MAP_CEllSIZE;
				stage_move[3].y = i * MAP_CEllSIZE;
			}
		}
	}

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);

	//BGM
	ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);
}

STAGE_SELECT::~STAGE_SELECT()
{
	DeleteFontToHandle(guid_font);
	DeleteFontToHandle(buttonguid_font);
	DeleteFontToHandle(stagename_font);
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteGraph(background_image[0]);
	delete player;
	delete stage;
	delete element;
}

AbstractScene* STAGE_SELECT::Update()
{

	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player, stage);

	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY());

	//落ちたらリスタート
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}


	if ((player_map_x >= stage_return.x - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new Title(); }
	}

	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(false, 0, "Stage01"); }
	}

	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(false, 0, "Stage02"); }
	}

	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(false, 0, "Stage03"); }
	}

	if ((player_map_x >= 11 * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= 11 * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(false, 0, "MapData1"); }
	}

	if (effect_timer < 255) { effect_timer++; }
	else { effect_timer = 0; }

	//デバッグ
	/*if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_X) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		return new GAMEMAIN(false, 0, "DebugStage");
	}*/

	return this;
}

void STAGE_SELECT::Draw() const
{
	//ステージ背景
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[0], FALSE);
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[0], FALSE);


	//ステージの描画
	element->Draw(stage);
	stage->Draw(element);

	//ガイド表示
	DrawStringToHandle(880, 668, "[ゲーム中]ポーズ", 0x91EB52, buttonguid_font, 0x000000);
	DrawBoxAA(790, 665, 860, 695, 0xFFFFFF, TRUE, 1.0F);
	DrawCircleAA(795, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//左端
	DrawCircleAA(855, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//右端
	DrawStringToHandle(785, 668, "START", 0xFFD64A, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(630, 668, "アクション", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(610, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(603, 668, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(450, 668, "ジャンプ", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(430, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(423, 668, "A", 0x89FE17, buttonguid_font, 0xFFFFFF);

	//戻る
	if ((player_map_x >= (stage_return.x) - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		const int x = 40;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(stage_return.x + MAP_CEllSIZE / 2 + stage->GetScrollX() - x, stage_return.y - MAP_CEllSIZE + stage->GetScrollY() - 30, 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_return.x + MAP_CEllSIZE / 2 + stage->GetScrollX() - x, stage_return.y - MAP_CEllSIZE + stage->GetScrollY() - 30, 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_return.x + MAP_CEllSIZE / 2, stage_return.y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawStringToHandle(stage_return.x + stage->GetScrollX() - 52 - x, stage_return.y - MAP_CEllSIZE + stage->GetScrollY() - 50, "タイトルへ", 0x6AF6C5, stagename_font, 0x000000);
		DrawStringToHandle(stage_return.x + stage->GetScrollX() - 2 - x, stage_return.y - MAP_CEllSIZE + stage->GetScrollY() - 10, "戻る", 0x6AF6C5, stagename_font, 0x000000);

		DrawCircleAA(stage_return.x + stage->GetScrollX() - x, stage_return.y + stage->GetScrollY() - 30, 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_return.x + stage->GetScrollX() - 7 - x, stage_return.y + stage->GetScrollY() - 42, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}

	//ステージ1 ポータル描画
	SetDrawBright(0, 255, 255 - effect_timer);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(101), TRUE);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), stage->GetMapImage(102), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ2 ポータル描画
	SetDrawBright(0, 255, 420 - effect_timer);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(103), TRUE);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + stage->GetScrollY(), stage->GetMapImage(104), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ3 ポータル描画
	SetDrawBright(255 - effect_timer, 255, 255);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(105), TRUE);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + stage->GetScrollY(), stage->GetMapImage(106), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ1
	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(stage_move[1].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_move[1].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[1].x + MAP_CEllSIZE / 2, stage_move[1].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawStringToHandle(stage_move[1].x + stage->GetScrollX() - 55, stage_move[1].y - MAP_CEllSIZE - 10 + stage->GetScrollY(), "１ステージ", 0xD65701, stagename_font, 0x000000);

		DrawCircleAA(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_move[1].x + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}

	//ステージ2
	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(stage_move[2].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[2].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_move[2].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[2].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[2].x + MAP_CEllSIZE / 2, stage_move[2].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawStringToHandle(stage_move[2].x + stage->GetScrollX() - 55, stage_move[2].y - MAP_CEllSIZE - 10 + stage->GetScrollY(), "２ステージ", 0xFA5A47, stagename_font, 0x000000);

		DrawCircleAA(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_move[2].x + stage->GetScrollX() - 7, stage_move[2].y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}

	//ステージ3
	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(stage_move[3].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[3].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(stage_move[3].x + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[3].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[3].x + MAP_CEllSIZE / 2, stage_move[3].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawStringToHandle(stage_move[3].x + stage->GetScrollX() - 55, stage_move[3].y - MAP_CEllSIZE - 10 + stage->GetScrollY(), "３ステージ", 0x9511D9, stagename_font, 0x000000);

		DrawCircleAA(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(stage_move[3].x + stage->GetScrollX() - 7, stage_move[3].y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}

	//サンプルステージ
	if ((player_map_x >= 11 * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= 11 * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(11 * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(11 * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[1].x + MAP_CEllSIZE / 2, stage_move[1].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendStringToHandle(11 * MAP_CEllSIZE + stage->GetScrollX() - 55, stage_move[1].y - MAP_CEllSIZE - 10 + stage->GetScrollY(), 0.4f, 0.4f, "Sampleステージ", 0x856AF6, guid_font, 0x000000);

		DrawCircleAA(11 * MAP_CEllSIZE + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(11 * MAP_CEllSIZE + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, "B", 0xEB7415, buttonguid_font, 0xFFFFFF);
	}



	//プレイヤーの描画
	player->Draw(stage);
}