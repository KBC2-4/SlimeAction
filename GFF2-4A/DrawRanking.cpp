#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DRAW_RANKING::DRAW_RANKING()
{
	wait_time = 0;
	RANKING::ReadRanking();
	for (int i = 0; i < 3; i++)
	{
		best_time[i] = RANKING::GetBestTime(i);
	}

	title_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_8X8);
	time_font = LoadFontDataToHandle("Resource/Fonts/TimeAttack_BestTime.dft", 0);

	if ((image = (LoadGraph("Resource/Images/Result/Best_time_Image.png"))) == -1)
	{
		throw "Resource/Images/Result/Best_time_Image.png";
	}

	if ((background_image = LoadGraph("Resource/Images/Stage/BackImage1.png")) == -1)
	{
		throw "Resource/Images/Stage/BackImage1.png";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}

	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
}

DRAW_RANKING::~DRAW_RANKING() {

	DeleteFontToHandle(title_font);
	DeleteFontToHandle(time_font);
	DeleteGraph(image);
	DeleteSoundMem(ok_se);

}

AbstractScene* DRAW_RANKING::Update()
{

	if (wait_time < 120) {
		++wait_time;
	}
	else { wait_time = 0; }

	if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		//ok_seが鳴り終わってから画面推移する。
		while (CheckSoundMem(ok_se)) {}
		StartJoypadVibration(DX_INPUT_PAD1,  OK_VIBRATION_POWER, OK_VIBRATION_TIME, -1);
		return new Title();
	}

	return this;
}

void DRAW_RANKING::Draw() const
{
	DrawGraph(0, 0, background_image, false);

	DrawRotaGraph(640, 200, 1, 0, image, TRUE);


	for (int i = 0; i < 3; i++)
	{
		DrawFormatStringToHandle(330, 320 + (75 * i), 0xFF8C00, title_font,  "%dステージ :", i+1);
		if (best_time[i] != -1)
		{
			if (best_time[i] / 1000 >= 60)
			{
				DrawFormatStringToHandle(660, 325 + (75 * i), 0xFF8C00, time_font, "%4d:%02d.%.3d", (best_time[i] / 1000) / 60, (best_time[i] / 1000) % 60, best_time[i] % 1000);
			}
			else 
			{
				DrawFormatStringToHandle(715, 325 + (75 * i), 0xFF8C00, time_font, "%4d.%.3d", best_time[i] / 1000, best_time[i] % 1000);
			}
		}
		
	}
	if (wait_time % 120 < 60)
	{
		DrawCircleAA(393.0f, 630.0f, 30, 28, 0xFFFFFF, 1);
		DrawStringToHandle(375, 602, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, title_font);
		DrawStringToHandle(430, 600, "でタイトルに戻る", 0xFFFFFF,title_font);
	}
	SetFontSize(-1);
}