#pragma once
class RANKING
{
private:
	static int best_time[3];
private:
	RANKING();
	/// <summary>
	/// ランキングデータの保存
	/// </summary>
	static void SaveRanking();
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="stage"></param>
	static void Insert(int time, int stage);
	/// <summary>
	/// ランキングデータ読み込み
	/// </summary>
	static void ReadRanking();
	/// <summary>
	/// ベストタイムの取得
	/// </summary>
	/// <param name="n">引数</param>
	/// <returns>ベストタイムの値</returns>
	static int GetBestTime(int n) { return best_time[n]; }
};

