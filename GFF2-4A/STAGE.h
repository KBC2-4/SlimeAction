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
	std::vector<std::vector<int>> door_info;
	std::vector<std::vector<int>> button_info;
	float scroll_x, scroll_y;	//マップスクロール量
	int temporary_hit;		//一時的な当たり判定
	const char* stage_name;		//ステージ名
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	STAGE(const char* stage_name = "StageSelect", bool restert = false);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~STAGE();
	/// <summary>
	/// ステージの更新
	/// </summary>
	void Update(PLAYER* player, ELEMENT* element);
	/// <summary>
	/// ステージの描画
	/// </summary>
	virtual void Draw(ELEMENT* element) const;
	/// <summary>
	/// マップ画像番号Geter
	/// </summary>
	/// <returns>int型：画像整理番号</returns>	
	int GetMapImage(int num) { return block_image1[num]; }
	/// <summary>
	/// マップデータの読み込み
	/// </summary>
	/// <param name="stage_name">ステージのインスタンス</param>
	void LoadMapData(const char* stage_name);
	/// <summary>
	/// マップサイズのGeter
	/// </summary>
	/// <returns>構造体型：マップサイズ</returns>	
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }
	/// <summary>
	/// マップ配列のGetter
	/// </summary>
	/// <param name="y">マップデータの横要素数</param>
	/// <param name="x">マップデータの縦要素数</param>
	/// <returns>int型：マップ配列番号</returns>	
	int GetMapData(int y, int x);
	/// <summary>
	/// マップ配列の値のSetter
	/// </summary>
	/// <param name="y">マップデータの横要素数</param>
	/// <param name="x">マップデータの縦要素数</param>
	/// <param name="mapchip_num">マップ配列番号</param>
	void SetMapData(int y, int x, int mapchip_num) { map_data[y][x] = mapchip_num; }


	/// <summary>
	/// カメラワーク
	/// </summary>
	/// 	/// <param name="player">プレイヤーのインスタンス</param>
	/// <param name="element">エレメントのインスタンス</param>
	void CameraWork(PLAYER* player, ELEMENT* element);
	/// <summary>
	/// スクロールXのSetter
	/// </summary>
	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }
	/// <summary>
	/// スクロールYのSetter
	/// </summary>
	void SetScrollY(float scroll_y) { if (scroll_y < 0) { this->scroll_y = scroll_y; } }
	/// <summary>
	/// 画面スクロール座標XのSetter
	/// </summary>
	bool SetScrollPos(int move_x);
	/// <summary>
	/// 画面スクロール座標XのGetter
	/// </summary>
	float GetScrollX() { return scroll_x; };
	/// <summary>
	/// 画面スクロール座標YのGetter
	/// </summary>
	float GetScrollY() { return scroll_y; }


	/// <summary>
	/// マップの当たり判定
	/// </summary>
	/// <param name="y">マップデータの横要素数</param>
	/// <param name="x">マップデータの縦要素数</param>
	bool HitMapDat(int y, int x);
	/// <summary>
	/// スライムのかけらの当たり判定
	/// </summary>
 	/// <param name="y">マップデータの横要素数</param>
	/// <param name="x">マップデータの縦要素数</param>
	bool HitThrowSlime(int y, int x);

	/// <summary>
	/// スポーン地点座標のGetter
	/// </summary>
	/// <returns>構造体型：スポーン地点座標</returns>	
	POINT GetSpawnPoint(void) { return spawn_point; }
	/// <summary>
	/// ステージクリア判定処理
	/// </summary>
	void StageClear(PLAYER* player);
	/// <summary>
	/// クリアしたかのフラグのGetter
	/// </summary>
	bool GetClearFlg(void) { return clearflg; };
	/// <summary>
	/// 中間地点判定処理
	/// </summary>
	void HalfwayPoint(PLAYER* player);
	/// <summary>
	/// 中間地点座標のGetter
	/// </summary>
	/// <returns>構造体型：中間地点座標</returns>	
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }
	/// <summary>
	/// 中間地点通過したか判定フラグのGetter
	/// </summary>
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }
	/// <summary>
	/// 一時的な当たり判定のSetter
	/// </summary>
	/// <param name="mapdata">マップ配列番号</param>
	void SetTemporary_Hit(int mapdata) { temporary_hit = mapdata; }
};

