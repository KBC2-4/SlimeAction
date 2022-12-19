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
	stagename_font = CreateFontToHandle("メイリオ", 31, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);
	stage = new STAGE("StageSelect");
	player = new PLAYER(stage);
	element = new ELEMENT();

	//スポーン地点をセット
	stage->SetScrollX(-(stage->GetSpawnPoint().y - MAP_CEllSIZE));
	stage->SetScrollY(-(stage->GetSpawnPoint().x - MAP_CEllSIZE * stage->GetMapSize().y));
	player->SetPlayer_Screen(stage->GetSpawnPoint());

	player_map_x = 0;
	player_map_y = 0;

	*effect_timer = 0;
	stage_return = { 0,0 };
	*stage_move = { 0,0 };
	effect_delta = false;

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

	//戻る
	if ((player_map_x >= stage_return.x - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new Title(); }
	}

	//ステージ1
	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage01"); }
	}


	//ステージ2
	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage02"); }
	}


	//ステージ3
	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage03"); }
	}


	//サンプルステージ
	if ((player_map_x >= 11 * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= 11 * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "MapData1"); }
	}


	if (effect_timer[1] >= 255) { effect_delta = true; }
	if (effect_timer[1] <= 0) { effect_delta = false; }

	if (effect_delta) { effect_timer[1]--; }
	else if(!effect_delta){ effect_timer[1]++; }


	//デバッグ
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_X) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		//return new GAMEMAIN(false, 0, "DebugStage");
	}

	//if (effect_timer[0] < 100) {
	//	effect_timer[0]++;
	//}
	//else { SetDrawAreaFull(); }

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

	//if (effect_timer[0] < 100) {
	//	DrawCircleAA(player->GetPlayerX(), player->GetPlayerY(), 60 + effect_timer[0] * 20, 28, 0x000000, FALSE, 80.0F + effect_timer[0] * 20);
	//	SetDrawArea(player->GetPlayerX() - MAP_CEllSIZE / 2 - effect_timer[0] * 10, player->GetPlayerY() - MAP_CEllSIZE / 2 - effect_timer[0] * 10,
	//		player->GetPlayerX() + MAP_CEllSIZE / 2 + effect_timer[0] * 10, player->GetPlayerY() + MAP_CEllSIZE / 2 + effect_timer[0] * 10);
	//	
	//}

	//ガイド表示
	DrawStringToHandle(880, 668, "[ゲーム中]ポーズ", 0x91EB52, buttonguid_font, 0x000000);
	DrawBoxAA(790, 665, 860, 695, 0xFFFFFF, TRUE, 1.0F);
	DrawCircleAA(795, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//左端
	DrawCircleAA(855, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//右端
	DrawStringToHandle(785, 668, "START", START_COLOR, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(630, 668, "アクション", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(610, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(603, 668, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(450, 668, "ジャンプ", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(430, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(423, 668, Option::GetInputMode() ? "A" : "B", Option::GetInputMode() ? A_COLOR : B_COLOR, buttonguid_font, 0xFFFFFF);

	//戻る
	if ((player_map_x >= (stage_return.x) - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("タイトルへ", stage_return.x - MAP_CEllSIZE / 2, stage_return.y - 30, stagename_font, 0x6AF6C5, 0xFFFFFF, 0, -10, -1, "戻る", 55, 30);
	}

	//ステージ1 ポータル描画
	SetDrawBright(0, 255, 255 - effect_timer[1]);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(101), TRUE);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), stage->GetMapImage(102), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ2 ポータル描画
	SetDrawBright(85 + (155 - 85) * effect_timer[1] / 255, 177 + (153 - 177) * effect_timer[1] / 255, 82 + (148 - 82) * effect_timer[1] / 255);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(103), TRUE);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + stage->GetScrollY(), stage->GetMapImage(104), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ3 ポータル描画
	SetDrawBright(255 - effect_timer[1], 255, 255);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(105), TRUE);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + stage->GetScrollY(), stage->GetMapImage(106), TRUE);
	SetDrawBright(255, 255, 255);

	//ステージ1
	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("１ステージ", stage_move[1].x, stage_move[1].y, stagename_font, 0xFA5A47);
	}

	//ステージ2
	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("２ステージ", stage_move[2].x, stage_move[2].y, stagename_font, 0xBF700F);
	}

	//ステージ3
	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("３ステージ", stage_move[3].x, stage_move[3].y, stagename_font, 0x9511D9);
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
		DrawStringToHandle(11 * MAP_CEllSIZE + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);
	}



	//プレイヤーの描画
	player->Draw(stage);
}


void STAGE_SELECT::DrawStageGuid(const char* stage_name, const float x, const float y, const int stagename_font, const int text_color, const int textback_color,
	const int text_margin_x, const int text_margin_y, const int backcolor, const char* second_title, const int secont_margin_x, const int secont_margin_y) const {

	if (textback_color == -1) { const int textback_color = 0xFFFFFF; }
	if (backcolor == -1) { const int backcolor = 0xFFFFFF; }

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawOvalAA(x + MAP_CEllSIZE / 2 + stage->GetScrollX(), y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
	DrawOvalAA(x + MAP_CEllSIZE / 2 + stage->GetScrollX(), y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, backcolor, TRUE, 0.0F);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(x + stage->GetScrollX() - 55 + text_margin_x, y - MAP_CEllSIZE - 10 + stage->GetScrollY() + text_margin_y, stage_name, text_color, stagename_font, textback_color);
	if (second_title != "") { DrawStringToHandle(x + stage->GetScrollX() - 55 + secont_margin_x, y - MAP_CEllSIZE - 10 + stage->GetScrollY() + secont_margin_y, second_title, text_color, stagename_font, textback_color); }

	DrawCircleAA(x + stage->GetScrollX(), y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(x + stage->GetScrollX() - 7, y + stage->GetScrollY() - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);
}