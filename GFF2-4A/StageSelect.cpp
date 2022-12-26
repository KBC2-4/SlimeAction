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
	guid_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	buttonguid_font = CreateFontToHandle("���C���I", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	stagename_font = CreateFontToHandle("���C���I", 31, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);
	stage = new STAGE("StageSelect");
	player = new PLAYER(stage);
	element = new ELEMENT();
	lemoner = nullptr;

	
	std::vector<std::vector<int>> spawn_point;
	//�����i�[�������鐔�𐔂���
	for (int i = 0, point = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			if (stage->GetMapData(i, j) == 91)
			{
				lemoner_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}

	//�����i�[�̐���
	if (lemoner_count > 0)
	{
		lemoner = new LEMON * [lemoner_count];
		for (int i = 0; i < lemoner_count; i++)
		{
			lemoner[i] = new LEMON(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//�X�|�[���n�_���Z�b�g
	stage->SetScrollX(-(stage->GetSpawnPoint().y - MAP_CEllSIZE));
	stage->SetScrollY(-(stage->GetSpawnPoint().x - MAP_CEllSIZE * stage->GetMapSize().y));
	player->SetPlayer_Screen(stage->GetSpawnPoint());

	player_map_x = 0;
	player_map_y = 0;

	*effect_timer = 0;
	stage_return = { 0,0 };
	*stage_move = { 0,0 };
	effect_delta = false;


	joys_anitimer = 0;
	joystick_delta = false;

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

	for (int i = 0; i < lemoner_count; i++)
	{
		delete lemoner[i];
	}
	delete[] lemoner;
}

AbstractScene* STAGE_SELECT::Update()
{

	player->Update(element, stage, nullptr, 0);
	stage->Update(player, element);
	element->Update(player, stage);

	//�v���C���[�����Ȃ��Ȃ��B
	if (player->GetLife() < 2) { player->SetLife(2); }

	for (int i = 0; i < lemoner_count; i++)
	{
		if (lemoner[i] != nullptr)
		{
			lemoner[i]->Update();
			if (lemoner[i]->GetDeleteFlag())
			{
				//item_rand = GetRand(5);
				//�A�C�e���𐶐�
				/*if (item_rand == 0)
				{
					item[item_num++] = new ITEMBALL(lemoner[i]->GetX(), lemoner[i]->GetY(), lemoner[i]->GetMapX(), lemoner[i]->GetMapY(), player, stage, stage->GetScrollX(), stage->GetScrollY());
				}*/
				delete lemoner[i];
				lemoner[i] = nullptr;
			}
		}
	}
	

	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY());

	//�������烊�X�^�[�g
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}

	//�߂�
	if ((player_map_x >= stage_return.x - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new Title(); }
	}

	//�X�e�[�W1
	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage01"); }
	}


	//�X�e�[�W2
	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage02"); }
	}


	//�X�e�[�W3
	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "Stage03"); }
	}


	//�T���v���X�e�[�W
	if ((player_map_x >= 11 * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= 11 * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
		if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { return new GAMEMAIN(false, 0, "MapData1"); }
	}

	//�|�[�^���̃A�j���[�V�����^�C�}�[
	if (effect_timer[1] >= 255) { effect_delta = true; }
	if (effect_timer[1] <= 0) { effect_delta = false; }

	if (effect_delta) { effect_timer[1]--; }
	else if (!effect_delta) { effect_timer[1]++; }


	//�W���C�X�e�B�b�N�̃A�j���[�V�����^�C�}�[
	if (joys_anitimer >= 15) { joystick_delta = true; }
	if (joys_anitimer <= -15) { joystick_delta = false; }

	if (effect_timer[1] % 2 == 0) {
		if (joystick_delta) { joys_anitimer--; }
		else if (!joystick_delta) { joys_anitimer++; }
	}


	//�f�o�b�O
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_X) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		//return new GAMEMAIN(false, 0, "DebugStage");
	}

	return this;
}

void STAGE_SELECT::Draw() const
{
	//�X�e�[�W�w�i
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[0], FALSE);
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw(stage, player);
	stage->Draw(element);
	
	for (int i = 0; i < lemoner_count; i++)
	{
		if (lemoner[i] != nullptr)
		{
			lemoner[i]->Draw();

		}
	}

	//DrawCircleAA(player->GetPlayerX(), player->GetPlayerY(), 900.0F, 32, 0x000000, FALSE, 1200.0F);

	//if (effect_timer[0] < 100) {
	//	DrawCircleAA(player->GetPlayerX(), player->GetPlayerY(), 60 + effect_timer[0] * 20, 28, 0x000000, FALSE, 80.0F + effect_timer[0] * 20);
	//	SetDrawArea(player->GetPlayerX() - MAP_CEllSIZE / 2 - effect_timer[0] * 10, player->GetPlayerY() - MAP_CEllSIZE / 2 - effect_timer[0] * 10,
	//		player->GetPlayerX() + MAP_CEllSIZE / 2 + effect_timer[0] * 10, player->GetPlayerY() + MAP_CEllSIZE / 2 + effect_timer[0] * 10);
	//	
	//}

	//�K�C�h�\��

	const int joystick_x = 300;
	const int joystick_y = 670;

	DrawOvalAA(joystick_x, joystick_y + 6, 18, 10, 20, 0x000000, TRUE);
	//�A�j���[�V�����L��
	//DrawOval(joystick_x + joys_anitimer * 0.8, joystick_y + 6 + abs(joys_anitimer * 0.6), 18, 10, 0x000000, 1);
	DrawBoxAA(joystick_x - 5, joystick_y, joystick_x + 7, joystick_y + 23, 0x000000, TRUE);
	//�A�j���[�V�����L��
	//DrawQuadrangle(joystick_x - 5 + joys_anitimer, joystick_y + abs(joys_anitimer * 0.5), joystick_x + 7 + joys_anitimer, joystick_y + abs(joys_anitimer * 0.5), joystick_x + 7, joystick_y + 23, joystick_x - 5, joystick_y + 23, 0x000000, TRUE);
	DrawOvalAA(joystick_x, joystick_y + 23, 22, 8, 20, 0x000000, TRUE);
	DrawString(joystick_x - 2, joystick_y - 2, "L", 0xFFFFFF);
	//�A�j���[�V�����L��
	//DrawString(joystick_x - 5 + joys_anitimer, joystick_y + abs(joys_anitimer * 0.5), "L", 0xFFFFFF);
	DrawStringToHandle(330, 668, "�ړ�", 0x91EB52, buttonguid_font, 0x000000);

	DrawStringToHandle(880, 668, "[�Q�[����]�|�[�Y", 0x91EB52, buttonguid_font, 0x000000);
	DrawBoxAA(790, 665, 860, 695, 0xFFFFFF, TRUE, 1.0F);
	DrawCircleAA(795, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//���[
	DrawCircleAA(855, 679.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//�E�[
	DrawStringToHandle(785, 668, "START", START_COLOR, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(630, 668, "�A�N�V����", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(610, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(603, 668, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(450, 668, "�W�����v", 0x91EB52, buttonguid_font, 0x000000);
	DrawCircleAA(430, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(423, 668, Option::GetInputMode() ? "A" : "B", Option::GetInputMode() ? A_COLOR : B_COLOR, buttonguid_font, 0xFFFFFF);

	//�߂�
	if ((player_map_x >= (stage_return.x) - (MAP_CEllSIZE * 3) / 2) && (player_map_x <= stage_return.x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("�^�C�g����", stage_return.x - MAP_CEllSIZE / 2, stage_return.y - 30, stagename_font, 0x6AF6C5, 0xFFFFFF, 0, -10, -1, "�߂�", 55, 30);
	}

	//�X�e�[�W1 �|�[�^���`��
	SetDrawBright(0, 255, 255 - effect_timer[1]);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(101), TRUE);
	DrawGraph(stage_move[1].x + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), stage->GetMapImage(102), TRUE);
	SetDrawBright(255, 255, 255);

	//�X�e�[�W2 �|�[�^���`��
	SetDrawBright(85 + (155 - 85) * effect_timer[1] / 255, 177 + (153 - 177) * effect_timer[1] / 255, 82 + (148 - 82) * effect_timer[1] / 255);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(103), TRUE);
	DrawGraph(stage_move[2].x + stage->GetScrollX(), stage_move[2].y + stage->GetScrollY(), stage->GetMapImage(104), TRUE);
	SetDrawBright(255, 255, 255);

	//�X�e�[�W3 �|�[�^���`��
	SetDrawBright(255 - effect_timer[1], 255, 255);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + -MAP_CEllSIZE + stage->GetScrollY(), stage->GetMapImage(105), TRUE);
	DrawGraph(stage_move[3].x + stage->GetScrollX(), stage_move[3].y + stage->GetScrollY(), stage->GetMapImage(106), TRUE);
	SetDrawBright(255, 255, 255);

	//�X�e�[�W1
	if ((player_map_x >= stage_move[1].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[1].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("�P�X�e�[�W", stage_move[1].x, stage_move[1].y, stagename_font, 0xFA5A47);
	}

	//�X�e�[�W2
	if ((player_map_x >= stage_move[2].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[2].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("�Q�X�e�[�W", stage_move[2].x, stage_move[2].y, stagename_font, 0xBF700F);
	}

	//�X�e�[�W3
	if ((player_map_x >= stage_move[3].x - MAP_CEllSIZE / 2) && (player_map_x <= stage_move[3].x + (MAP_CEllSIZE * 3) / 2)) {
		DrawStageGuid("�R�X�e�[�W", stage_move[3].x, stage_move[3].y, stagename_font, 0x9511D9);
	}

	//�T���v���X�e�[�W
	if ((player_map_x >= 11 * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= 11 * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawOvalAA(11 * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
		DrawOvalAA(11 * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
		//DrawString(stage_move[1].x + MAP_CEllSIZE / 2, stage_move[1].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendStringToHandle(11 * MAP_CEllSIZE + stage->GetScrollX() - 55, stage_move[1].y - MAP_CEllSIZE - 10 + stage->GetScrollY(), 0.4f, 0.4f, "Sample�X�e�[�W", 0x856AF6, guid_font, 0x000000);

		DrawCircleAA(11 * MAP_CEllSIZE + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(11 * MAP_CEllSIZE + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);
	}

	//�`���[�g���A��
	if (lemoner[0] != nullptr){
		const int x = 31;
		const int x_map = x * MAP_CEllSIZE + +stage->GetScrollX();
		const int y_map = stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY();
		if ((player_map_x >= x * MAP_CEllSIZE - MAP_CEllSIZE / 2) && (player_map_x <= x * MAP_CEllSIZE + (MAP_CEllSIZE * 3) / 2)) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawTriangleAA(x_map + 100, y_map - 62, x_map + 140, y_map, x_map + 300, y_map - 200, 0xFFFFFF, TRUE,2.0F);
			DrawOvalAA(x * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 100, 80, 30, 0x000000, FALSE, 1.0F);
			DrawOvalAA(x * MAP_CEllSIZE + MAP_CEllSIZE / 2 + stage->GetScrollX(), stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY(), 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);
			//DrawString(stage_move[1].x + MAP_CEllSIZE / 2, stage_move[1].y + MAP_CEllSIZE, "STAGE 1" , 0x6AF6C5, 0x000000);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//DrawCircleAA(x * MAP_CEllSIZE + stage->GetScrollX(), stage_move[1].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
			//DrawStringToHandle(x * MAP_CEllSIZE + stage->GetScrollX() - 7, stage_move[1].y + stage->GetScrollY() - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);

			const int joystick_x = x * MAP_CEllSIZE + +stage->GetScrollX() - 10;
			const int joystick_y = stage_move[1].y - MAP_CEllSIZE + stage->GetScrollY() - 10;
			const int joystick_size = 15;


			DrawOvalAA(joystick_x + joys_anitimer * 0.8, joystick_y + 6 + abs(joys_anitimer * 0.6), joystick_size + 8, 20, joystick_size, 0x000000, TRUE);
			//DrawBox(joystick_x - 5, joystick_y, joystick_x + 7, joystick_y + 23, 0x000000, 1);
			DrawQuadrangle(joystick_x - 5 + joys_anitimer, joystick_y + abs(joys_anitimer * 0.5), joystick_x + 7 + joys_anitimer, joystick_y + abs(joys_anitimer * 0.5), joystick_x + 7, joystick_y + 23, joystick_x - 5, joystick_y + 23, 0x000000, TRUE);
			DrawOval(joystick_x, joystick_y + joystick_size + 13, joystick_size + 12, 8, 0x000000, 1);
			DrawStringToHandle(joystick_x - 8 + joys_anitimer, joystick_y + -8 + abs(joys_anitimer * 0.5), "R", 0xFFFFFF, buttonguid_font);

			DrawStringToHandle(joystick_x + 30, joystick_y, " + ", 0xFFFFFF, buttonguid_font, 0x000000);
			//RB�{�^��
			DrawBoxAA(joystick_x + 70, joystick_y - 10, joystick_x + 130, joystick_y + 30, 0x000000, TRUE, 1.0F);
			DrawStringToHandle(joystick_x + 83, joystick_y + 0, "RB", 0xFFFFFF, buttonguid_font);
		}
	}



	//�v���C���[�̕`��
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