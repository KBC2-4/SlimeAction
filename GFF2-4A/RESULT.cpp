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
	string_effect_timer = 0.0f;
	guide_timer = 0;

	ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), count_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.5, good_se[se_randnum]);

	PlaySoundMem(background_music, DX_PLAYTYPE_BACK, FALSE);
	PlaySoundMem(good_se[se_randnum], DX_PLAYTYPE_BACK, FALSE);

	high_score = false;

	//ランキング登録
	if (stage_name == "Stage01")
	{
		if (clear_time < RANKING::GetBestTime(0)) { high_score = true; }
		RANKING::Insert(this->clear_time, 1);
	}
	else if (stage_name == "Stage02")
	{
		if (clear_time < RANKING::GetBestTime(1)) { high_score = true; }
		RANKING::Insert(this->clear_time, 2);
	}
	else if (stage_name == "Stage03")
	{
		if (clear_time < RANKING::GetBestTime(2)) { high_score = true; }
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
		//ok_seが鳴り終わってから画面推移する。
		while (CheckSoundMem(ok_se)) {}
		StartJoypadVibration(DX_INPUT_PAD1, OK_VIBRATION_POWER, OK_VIBRATION_TIME, -1);
		return new STAGE_SELECT();
	}

	if (effect_timer[0] < 180) { effect_timer[0]++; }
	if (string_effect_timer < 10.0f) { string_effect_timer += 0.1f; }

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


		if (high_score == true) {
			const int x = 80;
			const int y = 260;
			const float size = 1.0f + string_effect_timer;
			/*DrawOvalAA(x, y, 100, 80, 30, 0x000000, FALSE, 1.0F);
			DrawOvalAA(x, y, 99, 79, 30, 0xFFFFFF, TRUE, 0.0F);*/
			DrawStringToHandle(x, y, "新記録", 0xFAF300, menu_font, 0xFFFFFF);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75 + effect_timer[0]);
			//DrawExtendStringToHandle(x, y, size, size, "新記録", 0xFAF300, menu_font, 0xFFFFFF);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	if (guide_timer < 50)
	{

		DrawCircleAA(530.0f, 668.0f, 20, 20, 0xFFFFFF, 1);
		DrawStringToHandle(520, 650, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, button_guid_font, 0xFFFFFF);
		DrawStringToHandle(560, 650, "でスキップ", 0x76F567, button_guid_font, 0xFFFFFF);
	}
}