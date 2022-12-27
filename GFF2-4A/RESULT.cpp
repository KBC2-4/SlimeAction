#include "RESULT.h"
#include "GameMain.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "Option.h"
#include "Ranking.h"

RESULT::RESULT(bool issue, int clear_time, const char* stage_name)
{

	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	guid_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 70, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	button_guid_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 40, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	time_font = LoadFontDataToHandle("Resource/Fonts/TimeAttack.dft", 2);

	if ((title_image = LoadGraph("Resource/Images/Result/GameClear_title.png")) == -1) {
		throw "Resource/Images/Result/GameClear_title.png";
	}

	if ((background_image = LoadGraph("Resource/Images/Result/GameClear_background.png")) == -1) {
		throw "Resource/Images/Result/GameClear_background.png";
	}
	int bgm_randum = GetRand(1);
	char dis_good_bgm[36];
	sprintf_s(dis_good_bgm, sizeof(dis_good_bgm), "Resource/Sounds/BGM/gameclear0%d.wav", bgm_randum + 1);

	if ((background_music = LoadSoundMem(dis_good_bgm)) == -1) {
		throw dis_good_bgm;
	}

	if ((count_se = LoadSoundMem("Resource/Sounds/SE/321.wav")) == -1) {
		throw "Resource/Sounds/SE/321.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}


	se_randnum = GetRand(3);

	char dis_good_se[30];
	sprintf_s(dis_good_se, sizeof(dis_good_se), "Resource/Sounds/SE/good%d.wav", se_randnum + 1);

	if ((good_se[se_randnum] = LoadSoundMem(dis_good_se)) == -1) {
		throw dis_good_se;
	}



	if (issue == true) { timer = 10 * 60; }
	else { timer = 8 * 60; }

	win = issue;

	this->clear_time = clear_time;

	*effect_timer = 0;
	guide_timer = 0;

	ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), count_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, good_se[se_randnum]);

	PlaySoundMem(background_music, DX_PLAYTYPE_BACK, FALSE);
	PlaySoundMem(good_se[se_randnum], DX_PLAYTYPE_BACK, FALSE);


	//ランキング登録
	if (stage_name == "Stage01")
	{
		RANKING::Insert(this->clear_time, 1);
	}
	else if (stage_name == "Stage02")
	{
		RANKING::Insert(this->clear_time, 2);
	}
	else if (stage_name == "Stage03")
	{
		RANKING::Insert(this->clear_time, 3);
	}
	else {}
}

RESULT::~RESULT()
{

	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(guid_font);
	DeleteFontToHandle(button_guid_font);
	DeleteFontToHandle(time_font);
	DeleteGraph(title_image);
	DeleteSoundMem(background_music);
	DeleteSoundMem(count_se);
	DeleteSoundMem(ok_se);
	DeleteSoundMem(good_se[se_randnum]);
}

AbstractScene* RESULT::Update()
{
	if (timer <= 5 * 60) { if (CheckSoundMem(count_se) == FALSE)PlaySoundMem(count_se, DX_PLAYTYPE_BACK, FALSE); }

	if (timer <= 60) { return new STAGE_SELECT(); }
	else { --timer; }

	//ガイド点滅表示
	if (guide_timer < 100)
	{

		guide_timer++;
	}
	else
	{

		guide_timer = 0;
	}

	if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A) && PAD_INPUT::GetPadState() == PAD_STATE::ON)
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1);
		return new STAGE_SELECT();
	}

	return this;
}


void RESULT::Draw() const {

	if (win == true)
	{

		DrawFillBox(0, 0, 1280, 720, 0x000000);
		//DrawExtendGraph(0, 0, 1280, 720, title_image, true);
		DrawGraph(0, 0, background_image, FALSE);
		DrawGraph(180, 90, title_image, TRUE);

		char dis_clear_time[20];	//文字列合成バッファー

		//文字列合成
		if (clear_time / 1000 >= 60)
		{

			sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%02d.%.3d",
				(clear_time / 1000) / 60, (clear_time / 1000) % 60, clear_time % 1000);
		}
		else
		{

			sprintf_s(dis_clear_time, sizeof(dis_clear_time),
				"%5d.%.3d", clear_time / 1000, clear_time % 1000);
		}

		//クリアタイム
		DrawStringToHandle(GetDrawCenterX("クリアタイム",menu_font), 300, "クリアタイム", 0x1aff00, menu_font, 0x000000);

		DrawStringToHandle(GetDrawCenterX(dis_clear_time, time_font,-20), 410, dis_clear_time, 0x1aff00, time_font, 0xFFFFFF);

		DrawFormatStringToHandle(GetDrawCenterX("%2d秒後にリスタートします",guid_font,120), 540, 0x56F590, guid_font, "%2d秒後にリスタートします", timer / 60);
	}

	if (guide_timer < 50)
	{

		DrawCircleAA(530.0f, 668.0f, 20, 20, 0xFFFFFF, 1);
		DrawStringToHandle(520, 650, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, button_guid_font, 0xFFFFFF);
		DrawStringToHandle(560, 650, "でスキップ", 0x76F567, button_guid_font, 0xFFFFFF);
	}
}