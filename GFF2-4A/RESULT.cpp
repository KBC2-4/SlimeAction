#include "Result.h"
#include "GameMain.h"
#include "DxLib.h"

RESULT::RESULT(bool issue, int clear_time) {
	if ((clear_background_image = LoadGraph("Resource/Images/Result/mi_hasya_kao.png")) == -1) {
		throw "Resource/Images/Enemy/mi_hasya_kao.png";
	}

	if ((gameover_background_image = LoadGraph("Resource/Images/Result/gurepon.png")) == -1) {
		throw "Resource/Images/Enemy/gurepon.png";
	}

	if ((count_se = LoadSoundMem("Resource/Sounds/SE/321.wav")) == -1) {
		throw "Resource/Sounds/SE/321.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}

	
	for (int i = 0; i < 4; i++) {
		char dis_good_se[30];
		sprintf_s(dis_good_se, sizeof(dis_good_se), "Resource/Sounds/SE/good%d.wav", i + 1);

		if ((good_se[i] = LoadSoundMem(dis_good_se)) == -1) {
		throw dis_good_se;
		}
	}

	for (int i = 0; i < 4; i++) {
		char dis_bad_se[30];
		sprintf_s(dis_bad_se, sizeof(dis_bad_se), "Resource/Sounds/SE/bad%d.wav", i + 1);

		if ((bad_se[i] = LoadSoundMem(dis_bad_se)) == -1) {
			throw dis_bad_se;
		}
	}

	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8,-1,8);
	menu_font = CreateFontToHandle("メイリオ", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	time_font = CreateFontToHandle("メイリオ", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8,-1,5);

	if (issue == true) { timer = 10 * 60; }
	else{ timer = 8 * 60; }
	
	win = issue;

	this->clear_time =  GetNowCount() - clear_time;
	se_randnum = GetRand(3);
}

RESULT::~RESULT() {
	DeleteGraph(clear_background_image);
	DeleteGraph(gameover_background_image);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(time_font);
	DeleteSoundMem(count_se);
	DeleteSoundMem(ok_se);
	for(int i = 0; i < 4; i++)DeleteSoundMem(good_se[i]);
	for (int i = 0; i < 4; i++)DeleteSoundMem(bad_se[i]);
}

AbstractScene* RESULT::Update() {
	if (win == true && timer > 8 * 60) { PlaySoundMem(good_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if(win == false && timer > 5 * 80){ PlaySoundMem(bad_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if (timer <= 5 * 60) { if (CheckSoundMem(count_se) == FALSE)PlaySoundMem(count_se, DX_PLAYTYPE_BACK, FALSE); }

	if (--timer <= 60) { return new GAMEMAIN(); }

	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); return new GAMEMAIN(); }

	return this;
}

void RESULT::Draw() const {

	if (win == true) {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		DrawExtendGraph(0, 0, 1280, 720, clear_background_image, true);
		DrawStringToHandle(170, 200, "ゲームクリア", 0xF5F2B4, title_font, 0xF5EA1D);
		DrawStringToHandle(330, 350, "クリアタイム", 0xF5EB67, time_font, 0xFFFFFF);
		char dis_clear_time[20];	//文字列合成バッファー
		//文字列合成
		if (clear_time / 1000 >= 60) { sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%2d分%2d秒%.3dミリ秒", (clear_time / 1000) / 60, (clear_time / 1000) % 60, clear_time % 1000); }
		else { sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%5d秒%.3dミリ秒", clear_time / 1000, clear_time % 1000); }
		DrawStringToHandle(160, 450, dis_clear_time, 0xF5EB67, time_font, 0xFFFFFF);	//クリアタイム
		DrawFormatStringToHandle(20, 560, 0x56F590, menu_font , "%2d秒後にリスタートします", timer / 60);
	}
	else {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(0, 0, 1280, 720, gameover_background_image, true);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawStringToHandle(90, 200, "ゲームオーバー", 0xEB8A95, title_font , 0xEB3D49);
		DrawFormatStringToHandle(20, 400, 0x56F590, menu_font, "%2d秒後にリスタートします", timer / 60);
	}

	static int timer = 0;
	if (timer++ < 50) {
		DrawCircleAA(530.0f, 668.0f, 22, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(518, 650, 0.4f, 0.4f, "B", 0xEB7415, menu_font, 0xFFFFFF);
		DrawExtendStringToHandle(560, 650, 0.4f, 0.4f, "でスキップ", 0x76F567, menu_font, 0xFFFFFF);
	}
	else if (timer > 100) { timer = 0; }
}