#pragma once
#include <Windows.h>
#include <vector>

#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class PLAYER;
class ELEMENT;

class STAGE
{
private:
	
	int stage_image[5];			//ステージ背景画像
	int halfwaypoint_se;		//中間地点SE
	float map_x, map_y;			//マップ描画座標
	POINT clearbox;		//クリアになるボックス状範囲の座標
	int anitimer;
	POINT halfwaypointbox;		//中間地点座標

	bool clearflg;			//クリア判定フラグ
	bool halfwaypoint;		//中間地点フラグ
	float player_x_old, player_y_old;		//旧プレイヤー座標
	float player_vector_x;					//プレイヤーの移動方向x
	float player_vector_y;					//プレイヤーの移動方向y

protected:
	int block_image1[100];		//ステージブロック画像
	std::vector<std::vector<int>> map_data;
	static float scroll_x, scroll_y;	//マップスクロール量
public:
	STAGE();
	//マップ情報の更新
	void Update(PLAYER* player, ELEMENT* element);
	//ステージの描画
	virtual void Draw() const;
	//ステージの初期化
	//void InitStage();

	//カメラワーク
	void CameraWork(PLAYER* player);
	
	//水たまりの処理
	void PuddleProcess();
	//フックの処理
	void HookProcess();
	//////マップ配列の値を取得
	int GetMapData(int y, int x) { return map_data.at(y).at(x); }
	//マップの当たり判定 );
	bool HitMapDat(int y, int x); 
	//スライムのかけらの当たり判定
	bool HitThrowSlime(int y, int x);
	//画面スクロール座標Xをセット
	static bool SetScrollPos(int move_x);
	//画面スクロール座標Xの取得
	float GetScrollX() { return scroll_x; };	
	//画面スクロール座標Yの取得
	float GetScrollY() { return scroll_y; }
	//マップデータの読み込み
	void LoadMapData(void);	

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };

	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }

	void HalfwayPoint(PLAYER* player);
	//中間地点座標のGeter
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }

	//中間地点通過したか判定フラグのGeter
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }
};

