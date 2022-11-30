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

	if ((image = (LoadGraph("Resource/Images/Result/Best_time_Image.png"))) == -1)
	{
		throw "Resource/Images/Result/Best_time_Image.png";
	}
}

AbstractScene* DRAW_RANKING::Update()
{

	++wait_time;

	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
	{
		return new Title();
	}

	return this;
}

void DRAW_RANKING::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetFontSize(140);
	DrawRotaGraph(640, 300, 1, 0, image, TRUE);

	SetFontSize(64);
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(300, 300 + (75 * i), 0x000000, "%dステージ :", i+1);
		if (best_time[i] != -1)
		{
			if (best_time[i] / 1000 >= 60)
			{
				DrawFormatString(700, 300 + (75 * i), 0x000000, "%4d:%2d.%.3d", (best_time[i] / 1000) / 60, (best_time[i] / 1000) % 60, best_time[i] % 1000);
			}
			else 
			{
				DrawFormatString(600, 300 + (75 * i), 0x000000, "%5d.%.3d秒", best_time[i] / 1000, best_time[i] % 1000);
			}
		}
		
	}
	if (wait_time % 120 < 60)
	{
		DrawString(300, 600, "Bボタンでタイトルに戻る", 0x000000);
	}
	SetFontSize(-1);
}