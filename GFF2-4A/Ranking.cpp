#include "Ranking.h"
#include "DxLib.h"


int RANKING::best_time[3];
void RANKING::Insert(int time , int stage)
{
	ReadRanking();
	if ((time < best_time[stage - 1]) || (best_time[stage - 1] == -1))
	{
		best_time[stage - 1] = time;
		SaveRanking();
	}
}

void RANKING::SaveRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, "Resource/BestTime/BestTime.txt", "w") != 0)
	{
		throw "Resource/BestTime/BestTime.txt";
	}
	//ベストタイムを書き込む
	for (int i = 0; i < 3; i++)
	{
		fprintf_s(fp, "%d\n", best_time[i]);
	}
	fclose(fp);
}

void RANKING::ReadRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, "Resource/BestTime/BestTime.txt", "r") != 0)
	{
		throw "Resource/BestTime/BestTime.txt";
	}
	//ベストタイムを読み込む
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%d", &best_time[i]);
	}
	fclose(fp);
}

