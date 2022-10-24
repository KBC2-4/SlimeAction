#pragma once

#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int block_image1[100];		//ステージブロック画像
	int stage_image[5];			//ステージ背景画像
	float map_x, map_y;			//マップ描画座標
	static float scroll_x, scroll_y;	//マップスクロール量

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//マップ情報の更新
	void Update();
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
	static bool HitMapDat(int y, int x);
	static bool SetScrollPos(int move_x);
	static float GetScrollX() { return scroll_x; };
	void LoadMapData(void);
};

