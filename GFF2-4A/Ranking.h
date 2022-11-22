#pragma once
class RANKING
{
private:
	static int best_time[3];
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SaveRanking(void);		//ランキングデータの保存
	static void ReadRanking(void);		//ランキングデータ読み込み
};

