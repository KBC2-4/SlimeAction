#pragma once
class RANKING
{
private:
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SaveRanking(int best_time);		//ランキングデータの保存
	static int ReadRanking(void);		//ランキングデータ読み込み
};

