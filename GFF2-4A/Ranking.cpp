#include "Ranking.h"
#include "DxLib.h"

void RANKING::Insert(int time , int stage)
{
	int best_time;
	best_time = ReadRanking();

	if ((time < best_time) || (best_time == -1))
	{
		SaveRanking(time);
	}
}

void RANKING::SaveRanking(int best_time) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, "Resource/BestTime/BestTime.txt", "w") != 0)
	{
		throw "Resource/BestTime/BestTime.txt";
	}
	//ハイスコアデータを読み込む
	fprintf_s(fp, "%d", best_time);
	fclose(fp);
}

int RANKING::ReadRanking(void) {
	FILE* fp = NULL;

	int best_time;

	//ファイルオープン
	if (fopen_s(&fp, "Resource/BestTime/BestTime.txt", "r") != 0)
	{
		throw "Resource/BestTime/BestTime.txt";
	}
	//ハイスコアデータを読み込む
	fscanf_s(fp, "%d", &best_time);
	fclose(fp);

	return best_time;
}


