#pragma once

#define MAP_HEIGHT 9
#define MAP_WIDTH 16
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int image1[100];

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//ステージの描画
	void Draw() const;
	//ステージの初期化
	void InitStage();
	//ボタンの処理
	void ButtonProcess();
	//水たまりの処理
	void PuddleProcess();
	//フックの処理
	void HookProcess();
	////マップデータ取得関数
	static int GetMapDat(int y, int x) { return map_data[y][x]; }
};

