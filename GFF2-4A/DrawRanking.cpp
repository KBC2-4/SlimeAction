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
}

DRAW_RANKING::~DRAW_RANKING() {

	DeleteFontToHandle(title_font);
	DeleteFontToHandle(time_font);
	DeleteGraph(image);

}

AbstractScene* DRAW_RANKING::Update()
{

	if (wait_time < 120) {
		++wait_time;
	}
	else { wait_time = 0; }

	if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
	{
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
		DrawFormatStringToHandle(320, 320 + (75 * i), 0xFF8C00, title_font,  "%dステージ :", i+1);
		if (best_time[i] != -1)
		{
			if (best_time[i] / 1000 >= 60)
			{
				DrawFormatStringToHandle(650, 325 + (75 * i), 0xFF8C00, time_font, "%4d:%02d.%.3d", (best_time[i] / 1000) / 60, (best_time[i] / 1000) % 60, best_time[i] % 1000);
			}
			else 
			{
				DrawFormatStringToHandle(705, 325 + (75 * i), 0xFF8C00, time_font, "%4d.%.3d", best_time[i] / 1000, best_time[i] % 1000);
			}
		}
		
	}
	if (wait_time % 120 < 60)
	{
		DrawCircleAA(413.0f, 630.0f, 30, 28, 0x000000, 1);
		DrawStringToHandle(395, 602, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, title_font);
		DrawStringToHandle(450, 600, "でタイトルに戻る", 0x000000,title_font);
	}
	SetFontSize(-1);
}