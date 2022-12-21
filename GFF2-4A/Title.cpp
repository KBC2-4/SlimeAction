#include "Title.h"
#include "GameMain.h"
#include "StageSelect.h"
#include "DrawRanking.h"
#include "DxLib.h"
#include "Option.h"


Title::Title()
{

	if ((background_image = LoadGraph("Resource/Images/Stage/BackImage1.png")) == -1) 
	{
		throw "Resource/Images/Stage/BackImage1.png";
	}

	if ((background_music = LoadSoundMem("Resource/Sounds/BGM/title.wav")) == -1) {
		throw "Resource/Sounds/BGM/title.wav";
	}

	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) 
	{
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) 
	{
		throw "Resource/Sounds/SE/ok.wav";
	}

	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 120, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	selectmenu = 0;
	input_margin = 0;
	timer = 0;

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);

	//BGM
	ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);

	option = new Option();
}

Title::~Title() 
{
	delete option;

	DeleteGraph(background_image);
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
}

AbstractScene* Title::Update()
{
	if (option->GetOptionFlg() == true) {
		option->Update();
		//BGM
		ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

		//SE
		ChangeVolumeSoundMem(Option::GetSEVolume(), cursor_move_se);
		ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);
	}
	else {

		if (input_margin < 20) {
			input_margin++;
		}
		else {

			if (PAD_INPUT::GetPadThumbLY() > 20000)
			{

				selectmenu = (selectmenu + 3) % 4;
				input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
				StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
			}

			if (PAD_INPUT::GetPadThumbLY() < -20000)
			{

				selectmenu = (selectmenu + 1) % 4; input_margin = 0;
				PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
				StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
			}
		}

		if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
		{
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1);

			switch (static_cast<MENU>(selectmenu))
			{

			case MENU::GAME_SELECT:
				return new STAGE_SELECT();
				break;

			case MENU::RANKING:
				return new DRAW_RANKING();
				break;

			case MENU::OPTION:
				option->ChangeOptionFlg();
				break;

			case MENU::END:
				return nullptr;
				break;

			default:
				break;
			}
		}
		timer++;
	}
	
	return this;
}

void Title::Draw()const
{

	DrawGraph(0, 0, background_image, false);

	//オプション画面へ入る
	if (option->GetOptionFlg() == true) { 
		option->Draw(); 
	}
	else {

		DrawStringToHandle(GetDrawCenterX("スライムアクション",title_font), 100, "スライムアクション", 0x56F590, title_font, 0xFFFFFF);

		//ボックス
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		//DrawBoxAA(400.0f, 300.0f, 800.0f, 680.0f, 0xF3F589, TRUE, 5.0f);
		//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

		//矢印
		//DrawCircleAA(475.0f, 398.0f + selectmenu * 90, 20, 3, 0xffffff, TRUE, 3.0f);

		//選択メニュー
		DrawStringToHandle(GetDrawCenterX("プレイ",menu_font), 360, "プレイ", selectmenu == 0 ? 0xB3E0F5 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("ランキング",menu_font), 450, "ランキング", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("オプション",menu_font), 540, "オプション", selectmenu == 2 ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("終了",menu_font), 630, "終了", selectmenu == 3 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);


		//操作案内
		if (timer % 120 < 60)
		{
			DrawCircleAA(579.0f, 324.0f, 15, 20, 0xFFFFFF, 1);

			DrawExtendStringToHandle(572, 310, 0.4f, 0.4f, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, menu_font, 0xFFFFFF);
			DrawExtendStringToHandle(600, 310, 0.4f, 0.4f, "で決定", 0xEBA05E, menu_font, 0xFFFFFF);
		}
	}
}