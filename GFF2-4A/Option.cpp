#include "Option.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"

int Option::bgm_vol = 255 * 50 / 100;
int Option::se_vol = 255 * 50 / 100;
bool Option::input_mode = true;

Option::Option() {
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	buttonguid_font = CreateFontToHandle("メイリオ", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1)
	{
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((mute_se = LoadSoundMem("Resource/Sounds/SE/mute.wav")) == -1)
	{
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);

	selectmenu = 0;
	input_margin = 0;

	//SE
	ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);

	option_flg = false;
}


Option::~Option() {

	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(buttonguid_font);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(mute_se);
	selectmenu = 0;
	option_flg = false;
}


void Option::Update() {

	input_margin++;
	if (input_margin > 20) {
		if ((PAD_INPUT::GetPadThumbLY() > 20000) || (PAD_INPUT::GetPadThumbLY() < -20000) || (PAD_INPUT::GetPadThumbLX() > 20000) || (PAD_INPUT::GetPadThumbLX() < -20000)) {
			input_margin = 0;
			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
		}

		if (PAD_INPUT::GetPadThumbLY() > 20000) { selectmenu = (selectmenu + 2) % 3; }

		if (PAD_INPUT::GetPadThumbLY() < -20000) { selectmenu = (selectmenu + 1) % 3; }

		if (PAD_INPUT::GetPadThumbLX() > 20000) {
			if (selectmenu == 0 && bgm_vol < 255 * 90 / 100) { bgm_vol += 255 * 10 / 100; }
			else if (selectmenu == 1 && se_vol < 255 * 90 / 100) { se_vol += 255 * 10 / 100; }

			ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);
		}

		if (PAD_INPUT::GetPadThumbLX() < -20000) {
			if (selectmenu == 0 && bgm_vol > 255 * 10 / 100) { bgm_vol -= 255 * 10 / 100; }
			else if (selectmenu == 1 && se_vol > 255 * 10 / 100) { se_vol -= 255 * 10 / 100; }
		}

		////SE停止・バイブレーション停止
		//if()

		//}
	}


	//Aボタンでミュートまたは50%に設定する
	if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		if (static_cast<MENU>(selectmenu) == MENU::BGM) {
			PlaySoundMem(mute_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
			if (bgm_vol > 2) { bgm_vol = 2; }
			else { bgm_vol = 255 * 50 / 100; }
		}
		else if (static_cast<MENU>(selectmenu) == MENU::SE) {
			PlaySoundMem(mute_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
			if (se_vol > 2) { se_vol = 2; }
			else { se_vol = 255 * 50 / 100; }
		}
	}


	//入力方式の切り替え
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_BACK) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		input_mode = !input_mode;
	}

	//戻る(戻るメニューにカーソルを合わせなくても)
	if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_A : XINPUT_BUTTON_B)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		ChangeOptionFlg();
	}

	ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);
	ChangeVolumeSoundMem(GetSEVolume(), mute_se);
}


void Option::Draw() {

	//選択メニュー

	//BGM
	DrawStringToHandle(555, 250, "BGM", selectmenu == 0 ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);

	DrawOvalAA(620, 350, 180, 10, 30, 0x000000, FALSE, 2.0F);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawOvalAA(620, 350, 180, 10, 30, 0xFFFFFF, TRUE, 0.0F);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawOvalAA(620, 350, 180 * bgm_vol / 255, 10 * bgm_vol / 255, 30, 0xFFEB91, TRUE, 0.0F);

	DrawFormatString(620, 344, 0x000000, "%d", ((110 * bgm_vol / 255) - 1) / 10);


	//SE
	DrawStringToHandle(580, 380, "SE", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);

	DrawOvalAA(620, 480, 180, 10, 30, 0x000000, FALSE, 2.0F);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawOvalAA(620, 480, 180, 10, 30, 0xFFFFFF, TRUE, 0.0F);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawOvalAA(620, 480, 180 * se_vol / 255, 10 * se_vol / 255, 30, 0x11A7ED, TRUE, 0.0F);

	DrawFormatString(620, 474, 0x000000, "%d", ((110 * se_vol / 255) - 1) / 10);

	DrawStringToHandle(548, 540, "戻る", selectmenu == 2 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);

	//入力方式の切り替え

	//BACKボタン
	const int start_x = 220;
	const int start_y = 300;

	DrawBoxAA(start_x, start_y, start_x + 70, start_y + 30, 0xFFFFFF, TRUE, 1.0F);
	DrawCircleAA(start_x + 5, start_y + 14.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//左端
	DrawCircleAA(start_x + 65, start_y + 14.6, 15, 20, 0xFFFFFF, TRUE, 1.0F);	//右端
	DrawStringToHandle(start_x + 2, start_y + 3, "BACK", BACK_COLOR, buttonguid_font, 0xFFFFFF);

	DrawStringToHandle(100, 300, "入力方式", 0xEB8F63, buttonguid_font, 0xFFFFFF);
	DrawCircleAA(167, 362, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(160, 350, "A", A_COLOR, buttonguid_font, 0xFFFFFF);
	DrawStringToHandle(190, 350, Option::GetInputMode() ? "戻る" : "決定／アクション", B_COLOR, buttonguid_font, 0xFFFFFF);
	DrawCircleAA(167, 402, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(160, 390, "B", B_COLOR, buttonguid_font, 0xFFFFFF);
	DrawStringToHandle(190, 390, Option::GetInputMode() ? "決定" : "戻る", B_COLOR, buttonguid_font, 0xFFFFFF);



	//ガイド表示
	DrawStringToHandle(400, 668, "ミュート／ミュート解除", 0xFFA15C, buttonguid_font, 0x000000);
	DrawCircleAA(380, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(373, 668, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, buttonguid_font, 0xFFFFFF);
	
	DrawStringToHandle(780, 668, "戻る", 0xFFA15C, buttonguid_font, 0x000000);
	DrawCircleAA(760, 680, 15, 20, 0xFFFFFF, 1);
	DrawStringToHandle(753, 668, Option::GetInputMode() ? "A" : "B", Option::GetInputMode() ? A_COLOR : B_COLOR, buttonguid_font, 0xFFFFFF);
}