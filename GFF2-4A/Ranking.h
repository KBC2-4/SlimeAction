#pragma once
class RANKING
{
private:
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SortRanking();		//ランキング並べ替え
	static void SaveRanking();		//ランキングデータの保存
	static int ReadRanking(void);		//ランキングデータ読み込み
};

