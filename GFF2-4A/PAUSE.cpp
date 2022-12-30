#include "PAUSE.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"
#include "Option.h"

PAUSE::PAUSE() {
	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) {
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}

	if ((memu_open_se = LoadSoundMem("Resource/Sounds/SE/pause_open.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}

	if ((memu_close_se = LoadSoundMem("Resource/Sounds/SE/pause_close.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	buttonguid_font = CreateFontToHandle("メイリオ", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	selectmenu = 0;
	nextmenu = 0;
	input_margin = 0;
	pause_graph = 0;
	pause_effect_timer = 0;
	pause_flg = false;

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.6, cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, memu_open_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, memu_close_se);

	option = new Option();
}

PAUSE::~PAUSE() {

	delete option;
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(buttonguid_font);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	DeleteSoundMem(memu_open_se);
	DeleteSoundMem(memu_close_se);

	DeleteGraph(pause_graph);
}

int PAUSE::Update(void) {

	if (GetWindowActiveFlag() == FALSE || GetWindowMinSizeFlag() == TRUE) { pause_flg = true; }

	//STARTボタンでポーズ
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		
		if (pause_flg == true) {
			PlaySoundMem(memu_close_se, DX_PLAYTYPE_BACK, TRUE);
			//デリート処理
			DeleteGraph(pause_graph);
			pause_graph = 0;
			pause_effect_timer = 0;
		}else{ PlaySoundMem(memu_open_se, DX_PLAYTYPE_BACK, TRUE); }
		SetPause();
	}

	if (pause_flg == true)
	{



		if (pause_graph == 0) {
			pause_graph = MakeGraph(1280, 720);
			GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);
		}

		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.6, cursor_move_se);
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, memu_open_se);
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, memu_close_se);

		if (option->GetOptionFlg() == true) {
			option->Update();
		}
		else {
			if (input_margin < 20) {
				input_margin++;
			}
			else {

				if (PAD_INPUT::GetPadThumbLY() > 20000) { selectmenu = (selectmenu + 3) % 4;  input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }
				if (PAD_INPUT::GetPadThumbLY() < -20000) { selectmenu = (selectmenu + 1) % 4; input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }
			}

			if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
				PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
				//ok_seが鳴り終わってから画面推移する。
				while (CheckSoundMem(ok_se)) {}
				StartJoypadVibration(DX_INPUT_PAD1, OK_VIBRATION_POWER, OK_VIBRATION_TIME, -1);

				//デリート処理
				if (static_cast<MENU>(selectmenu) != MENU::OPTION) {
					DeleteGraph(pause_graph);
					pause_graph = 0;
					pause_effect_timer = 0;
				}
				nextmenu = selectmenu;

				if (static_cast<MENU>(selectmenu) == MENU::RETURN) {
					pause_flg = !pause_flg;
				}
				else if (static_cast<MENU>(selectmenu) == MENU::OPTION) { option->ChangeOptionFlg(); }
				else if (static_cast<MENU>(selectmenu) == MENU::STAGE_SELECT) { option->~Option(); }
			}

			//Aボタンでもポーズを戻す
			if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_A : XINPUT_BUTTON_B)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
				//デリート処理
				DeleteGraph(pause_graph);
				selectmenu = 0;
				pause_graph = 0;
				pause_effect_timer = 0;
				pause_flg = !pause_flg;

				// Aボタンを一定時間無効化する
				int disable_time = 100;  // Aボタンを無効化する時間（単位：ミリ秒）
				int start_time = GetNowCount();  // Aボタンを押した時間
				while (!pause_flg) {
					// Aボタンを無効化する時間を超えた場合、while文を抜ける
					if (GetNowCount() - start_time > disable_time) {
						break;
					}
				}
			}
		}
	}
	return 0;
}

void PAUSE::Draw() {

	if (pause_effect_timer < 50) {
		pause_effect_timer++;
		if (pause_effect_timer % 5 == 0) {
			GraphFilter(pause_graph, DX_GRAPH_FILTER_GAUSS, 16, 70);
		}
	}

	DrawGraph(0, 0, pause_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawFillBox(0, 0, 1280, 720, 0x000000);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//オプション画面へ入る
	if (option->GetOptionFlg() == true) {
		option->Draw();
	}
	else {

		DrawStringToHandle(GetDrawCenterX("ポーズ", title_font), 100, "ポーズ", 0x56F590, title_font, 0xFFFFFF);
		//選択メニュー
		DrawStringToHandle(GetDrawCenterX("ゲームへ戻る", menu_font), 270, "ゲームへ戻る", static_cast<MENU>(selectmenu) == MENU::RETURN ? 0xB3E0F5 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("リスタート", menu_font), 360, "リスタート", static_cast<MENU>(selectmenu) == MENU::RESTART ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("オプション", menu_font), 450, "オプション", static_cast<MENU>(selectmenu) == MENU::OPTION ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("ステージ選択へ", menu_font), 540, "ステージ選択へ", static_cast<MENU>(selectmenu) == MENU::STAGE_SELECT ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);

		//ガイド表示
		DrawStringToHandle(580, 668, "ゲームへ戻る", 0xFFA15C, buttonguid_font, 0x000000);
		DrawCircleAA(560, 680, 15, 20, 0xFFFFFF, 1);
		DrawStringToHandle(553, 668, Option::GetInputMode() ? "A" : "B", Option::GetInputMode() ? A_COLOR : B_COLOR, buttonguid_font, 0xFFFFFF);
	}
}

int PAUSE::GetDrawCenterX(const char* string, int font_handle)const {

	//画面幅
	const int screenX = 1280;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}