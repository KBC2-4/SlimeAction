#include "Result.h"
#include "GameMain.h"
#include "Ranking.h"
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
	AddFontResourceEx(TEXT("./Resource/Fonts/TimeAttack.otf"), FR_PRIVATE, NULL);
	time_font = CreateFontToHandle("TimeAttack", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8,DX_CHARSET_DEFAULT,5);

	if (issue == true) { timer = 10 * 60; }
	else{ timer = 8 * 60; }
	
	win = issue;
	if (issue)
	{
		RANKING::Insert(clear_time, 1);
	}
	this->clear_time =  GetNowCount() - clear_time;
	se_randnum = GetRand(3);

	*effect_timer = 0;
	guide_timer = 0;
}

RESULT::~RESULT() {
	DeleteGraph(clear_background_image);
	DeleteGraph(gameover_background_image);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(time_font);
	RemoveFontResourceEx(TEXT("./Resource/Fonts/TimeAttack.otf"), FR_PRIVATE, NULL);
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

	//ガイド点滅表示
	if (guide_timer < 100) { guide_timer++; }
	else { guide_timer = 0; }

	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B && PAD_INPUT::GetPadState() == PAD_STATE::ON) { PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); return new GAMEMAIN(); }

	return this;
}

const int GetDrawCenterX(int screenX, const char* string, int font_handle) {
	const int w = screenX / 2 - GetDrawStringWidthToHandle(string, strlen(string), font_handle) / 2;
	return w;
}

void RESULT::Draw() const {

	if (win == true) {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		DrawExtendGraph(0, 0, 1280, 720, clear_background_image, true);
		DrawStringToHandle(170, 200, "ゲームクリア", 0xF5F2B4, title_font, 0xF5EA1D);
		DrawStringToHandle(330, 350, "クリアタイム", 0xF5EB67, time_font, 0xFFFFFF);
		char dis_clear_time[20];	//文字列合成バッファー
		//文字列合成
		if (clear_time / 1000 >= 60) { sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%2d.%.3d", (clear_time / 1000) / 60, (clear_time / 1000) % 60, clear_time % 1000); }
		else { sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%5d.%.3d", clear_time / 1000, clear_time % 1000); }
		DrawStringToHandle(100, 400, dis_clear_time, 0xF5EB67, time_font, 0xFFFFFF);	//クリアタイム
		DrawFormatStringToHandle(20, 560, 0x56F590, menu_font , "%2d秒後にリスタートします", timer / 60);
	}
	else {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(0, 0, 1280, 720, gameover_background_image, true);
		SetDrawMode(DX_DRAWMODE_NEAREST); 
		//DrawExtendStringToHandle(GetDrawCenterX(1280, "ゲームオーバー", title_font), 200 , static_cast<float>(effect_timer[0]) / 40, static_cast<float>(effect_timer[0]) / 40, "ゲームオーバー", 0xEB8A95, title_font, 0xEB3D49);
		if (effect_timer[1] > 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, effect_timer[1] * 2.55);
			DrawExtendStringToHandle(GetDrawCenterX(1280, "ゲームオーバー", title_font), 200, static_cast<float>(effect_timer[0]) / 40 * 1.0, static_cast<float>(effect_timer[0]) / 40 * 1.0, "ゲームオーバー", 0xEB8A95, title_font, 0xEB3D49);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//DrawStringToHandle(90, 200, "ゲームオーバー", 0xEB8A95, title_font , 0xEB3D49);
		DrawFormatStringToHandle(GetDrawCenterX(1280, "00秒後にリスタートします", menu_font), 400, 0x56F590, menu_font, "%2d秒後にリスタートします", timer / 60);
	}
	//ガイド点滅表示
	if (guide_timer < 50) {
		DrawCircleAA(530.0f, 668.0f, 22, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(518, 650, 0.4f, 0.4f, "B", 0xEB7415, menu_font, 0xFFFFFF);
		DrawExtendStringToHandle(560, 650, 0.4f, 0.4f, "でスキップ", 0x76F567, menu_font, 0xFFFFFF);
	}
}