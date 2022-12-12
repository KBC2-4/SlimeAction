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
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	selectmenu = 0;
	nextmenu = 0;

	pause_flg = false;

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);

	option = new Option();
}

PAUSE::~PAUSE() {
	delete option;
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
}

int PAUSE::Update(void) {

	if (option->GetOptionFlg() == true) {
		option->Update();
	}
	else {
		static int input_margin;
		input_margin++;
		if (PAD_INPUT::GetPadThumbLY() > 20000 && input_margin > 20) { selectmenu = (selectmenu + 3) % 4;  input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }
		if (PAD_INPUT::GetPadThumbLY() < -20000 && input_margin > 20) { selectmenu = (selectmenu + 1) % 4; input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }

		if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1);
			if (selectmenu == 0 || selectmenu == 1) { pause_flg = !pause_flg; }
			else if (selectmenu == 2) { option->ChangeOptionFlg(); }
			nextmenu = selectmenu;
		}
	}
		return 0;
}

void PAUSE::Draw(int pause_graph) {
	GraphFilter(pause_graph, DX_GRAPH_FILTER_GAUSS, 16, 1000);
	DrawGraph(0, 0, pause_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawFillBox(0, 0, 1280, 720, 0x000000);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(380, 100, "ポーズ", 0x56F590, title_font, 0xFFFFFF);
	//選択メニュー
	DrawStringToHandle(400, 270, "ゲームへ戻る", selectmenu == 0 ? 0xB3E0F5 : 0xEB8F63, menu_font, 0xFFFFFF);
	DrawStringToHandle(440, 360, "リスタート", selectmenu == 1 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);
	DrawStringToHandle(440, 450, "オプション", selectmenu == 2 ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);
	DrawStringToHandle(362, 540, "タイトルへ戻る", selectmenu == 3 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);
	
	if (option->GetOptionFlg() == true) { option->Draw(); }
}