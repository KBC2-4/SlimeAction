#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DRAW_RANKING::DRAW_RANKING()
{
	wait_time = 0;

	best_time = RANKING::ReadRanking();

}

AbstractScene* DRAW_RANKING::Update()
{

	++wait_time;

	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_A) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
	{
		return new Title();
	}

	return this;
}

void DRAW_RANKING::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetFontSize(80);
	DrawString(300, 100, "BestTime",0x000000);

	SetFontSize(64);

	DrawString(100,300,"1ステージ : ", 0x000000);
	if (best_time != -1)
	{
		DrawFormatString(300, 300, 0x000000, "%5d.%.3d", best_time / 1000, best_time % 1000);
	}
	if (wait_time % 120 < 60)
	{
		DrawString(200, 500, "Aボタンでタイトルに戻る", 0x000000);
	}
}