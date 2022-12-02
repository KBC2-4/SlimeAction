#pragma once
#include <Windows.h>
#include <vector>

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
	POINT spawn_point;			//スポーン地点座標

	bool clearflg;			//クリア判定フラグ
	int clear_count;		//ステージクリア時のカウントタイマー
	bool halfwaypoint;		//中間地点フラグ
	int halfway_timer;		//中間地点用タイマー
	float player_x_old, player_y_old;		//旧プレイヤー座標
	float player_longold;	//数フレーム前のプレイヤー座標
	int count_timer;		//カウント用タイマー
	float player_vector_x;					//プレイヤーの移動方向x
	float player_vector_y;					//プレイヤーの移動方向y
	float scroll_speed_x;					//スクロール移動量(x)
	float scroll_speed_y;					//スクロール移動量(y)

protected:
	int block_image1[110];		//ステージブロック画像
	std::vector<std::vector<int>> map_data;
	float scroll_x, scroll_y;	//マップスクロール量
public:
	STAGE(const char* stage_name = "StageSelect");
	//マップ情報の更新
	void Update(PLAYER* player, ELEMENT* element);
	//ステージの描画
	virtual void Draw() const;
	//ステージの初期化
	//void InitStage();

	//マップサイズのGeter
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }

	//マップ画像番号Geter
	int GetMapImage(int num) { return block_image1[num]; }

	//カメラワーク
	void CameraWork(PLAYER* player, ELEMENT* element);
	
	//水たまりの処理
	void PuddleProcess();
	//フックの処理
	void HookProcess();
	//////マップ配列の値を取得
	int GetMapData(int y, int x);
	//マップ配列の値を設定
	void SetMapData(int y, int x, int mapchip_num) { map_data[y][x] = mapchip_num; }
	//マップの当たり判定 
	bool HitMapDat(int y, int x); 
	//スライムのかけらの当たり判定
	bool HitThrowSlime(int y, int x);
	//画面スクロール座標Xをセット
	bool SetScrollPos(int move_x);
	//画面スクロール座標Xの取得
	float GetScrollX() { return scroll_x; };	
	//画面スクロール座標Yの取得
	float GetScrollY() { return scroll_y; }
	//マップデータの読み込み
	void LoadMapData(const char* stage_name);

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };

	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }
	void SetScrollY(float scroll_y) { if (scroll_y < 0) { this->scroll_y = scroll_y; } }

	void HalfwayPoint(PLAYER* player);
	//中間地点座標のGeter
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }

	//中間地点通過したか判定フラグのGeter
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }

	//スポーン地点のGeter
	POINT GetSpawnPoint(void) { return spawn_point; }
};

