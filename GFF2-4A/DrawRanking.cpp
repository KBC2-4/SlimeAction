#include "DrawRanking.h"

DRAW_RANKING::DRAW_RANKING()
{
	wait_time = 0;

	if ((Image = LoadGraph("images/Ranking.bmp")) == -1)
	{
		throw "\nRanking Image Err\n\n";
	}
	data = Ranking::ReadRanking();

}

AbstractScene* DRAW_RANKING::Update()
{
	if (++wait_time > 60)
	{
		wait_time = 0;
	}
	// スペースキーでメニューに戻る
	if (KeyFlagManager::GetKeyFlag() & PAD_INPUT_M)
	{
		return new Title();
	}
	return this;
}

void DRAW_RANKING::Draw() const
{

	//ランキング画像表示
	DrawGraph(0, 0, Image, FALSE);

	// ランキング一覧を表示
	SetFontSize(30);
	for (int i = 0; i < 10; i++) {
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s     %10d",
			data[i].no, data[i].name, data[i].score);
	}

	// 文字の表示(点滅)
	if (wait_time < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press [SPACE] Key  --", 0xFF0000);
	}
}