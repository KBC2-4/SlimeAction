#include "RESULT.h"
#include "GameMain.h"
#include "DxLib.h"

RESULT::RESULT(bool issue, int clear_time) 
{

	if ((Result_Image = LoadGraph("Resource/Images/Result/GameClear.png")) == -1) {
		throw "Resource/Images/Enemy/mi_hasya_kao.png";
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

	Result_font = CreateFontToHandle("メイリオ", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	if (issue == true) { timer = 10 * 60; }
	else{ timer = 8 * 60; }
	
	win = issue;

	this->clear_time =  GetNowCount() - clear_time;
	se_randnum = GetRand(3);

	*effect_timer = 0;
	guide_timer = 0;
}

RESULT::~RESULT() 
{

	DeleteGraph(Result_Image);
	DeleteFontToHandle(Result_font);
	RemoveFontResourceEx(TEXT("./Resource/Fonts/TimeAttack.otf"), FR_PRIVATE, NULL);
	DeleteSoundMem(count_se);
	DeleteSoundMem(ok_se);
	for(int i = 0; i < 4; i++)DeleteSoundMem(good_se[i]);
	for (int i = 0; i < 4; i++)DeleteSoundMem(bad_se[i]);
}

AbstractScene* RESULT::Update() 
{

	if (win == true && timer > 8 * 60) { PlaySoundMem(good_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if(win == false && timer > 5 * 80){ PlaySoundMem(bad_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if (timer <= 5 * 60) { if (CheckSoundMem(count_se) == FALSE)PlaySoundMem(count_se, DX_PLAYTYPE_BACK, FALSE); }

	if (--timer <= 60) { return new GAMEMAIN(); }

	//ガイド点滅表示
	if (guide_timer < 100)
	{ 

		guide_timer++; 
	}
	else 
	{ 

		guide_timer = 0; 
	}

	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B && PAD_INPUT::GetPadState() == PAD_STATE::ON) 
	{

		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); return new GAMEMAIN();
	}

	return this;
}

const int GetDrawCenterX(int screenX, const char* string, int font_handle)
{

	const int w = screenX / 2 - GetDrawStringWidthToHandle(string, strlen(string), font_handle) / 2;
	return w;
}

void RESULT::Draw() const {

	if (win == true) 
	{
		DrawFillBox(0, 0, 1280, 720, 0x000000);
		DrawExtendGraph(0, 0, 1280, 720, Result_Image, true);

		char dis_clear_time[20];	//文字列合成バッファー

		//文字列合成
		if (clear_time / 1000 >= 60) 
		{ 

			sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%2d.%.3d", 
				(clear_time / 1000) / 60, (clear_time / 1000) % 60, clear_time % 1000);
		}
		else 
		{ 

			sprintf_s(dis_clear_time, sizeof(dis_clear_time),
				"%5d.%.3d", clear_time / 1000, clear_time % 1000); 
		}

		//クリアタイム
		DrawStringToHandle(330, 300, "クリアタイム", 0x1aff00, Result_font, 0x000000);
		DrawStringToHandle(340, 400, dis_clear_time, 0x1aff00, Result_font, 0x000000);

		DrawFormatStringToHandle(30, 540, 0x56F590, Result_font, "%2d秒後にリスタートします", timer / 60);
	}
	
	if (guide_timer < 50)
	{

		DrawCircleAA(530.0f, 668.0f, 22, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(518, 650, 0.4f, 0.4f, "B", 0xEB7415, Result_font, 0xFFFFFF);
		DrawExtendStringToHandle(560, 650, 0.4f, 0.4f, "でスキップ", 0x76F567, Result_font, 0xFFFFFF);
	}
}