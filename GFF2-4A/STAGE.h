#pragma once

#define MAP_HEIGHT 9
#define MAP_WIDTH 48
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int image1[100];
	float map_x, map_y;			//マップ描画座標
	static float scroll_x, scroll_y;	//

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//マップ情報の更新
	void Update(float player_x,float player_y);
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
	static void SetScrollPos(int move_type);
	static float GetScrollX() { return scroll_x; };
};

