#include "Option.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"

int Option::bgm_vol = 255 * 50 / 100;
int Option::se_vol = 255 * 50 / 100;

Option::Option() {
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

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

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);

	selectmenu = 0;
	input_margin = 0;

	//BGM
	ChangeVolumeSoundMem(GetBGMVolume(), background_music);

	//SE
	ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);

	option_flg = false;
}


Option::~Option() {

	DeleteGraph(background_image);
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteFontToHandle(menu_font);
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
			if (selectmenu == 0 && bgm_vol < 255 * 90 / 100) { bgm_vol += 255 * 10 / 100;}
			else if (selectmenu == 1 && se_vol < 255 * 90 / 100) { se_vol += 255 * 10 / 100; }
			
			ChangeVolumeSoundMem(GetBGMVolume(), background_music);
			ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);
		}

		if (PAD_INPUT::GetPadThumbLX() < -20000) {
			if (selectmenu == 0 && bgm_vol > 255 * 10 / 100) { bgm_vol -= 255 * 10 / 100; }
			else if (selectmenu == 1 && se_vol > 255 * 10 / 100) { se_vol -= 255 * 10 / 100; }
			
			ChangeVolumeSoundMem(GetBGMVolume(), background_music);
			ChangeVolumeSoundMem(GetSEVolume(), cursor_move_se);
		}
	}

	//戻る
	if ((selectmenu == 2) && (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) {
		ChangeOptionFlg();
	}
}


void Option::Draw() {

	DrawGraph(0, 0, background_image, false);

	//選択メニュー
	DrawStringToHandle(555, 250, "BGM", selectmenu == 0 ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);

	DrawOvalAA(620, 350, 180, 10, 30, 0x000000, FALSE, 2.0F);
	DrawOvalAA(620, 350, 180 * bgm_vol / 255, 10 * bgm_vol / 255, 30, 0xFFEB91, TRUE, 0.0F);

	DrawStringToHandle(580, 380, "SE", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);

	DrawOvalAA(620, 480, 180, 10, 30, 0x000000, FALSE, 2.0F);
	DrawOvalAA(620, 480, 180 * se_vol / 255, 10 * se_vol / 255, 30, 0x11A7ED, TRUE, 0.0F);

	DrawStringToHandle(548, 540, "戻る", selectmenu == 2 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);
}