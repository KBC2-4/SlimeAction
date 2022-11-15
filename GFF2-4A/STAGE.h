#pragma once


#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class PLAYER;

class STAGE
{
private:
	
	int stage_image[5];			//ステージ背景画像
	float map_x, map_y;			//マップ描画座標
	int clearbox[2];		//クリアになるボックス状範囲	0=x,1=y
	bool clearflg;			//クリア判定フラグ
	float player_x_old, player_y_old;		//旧プレイヤー座標(x、y)
	/*int player_vector_x;
	int player_vector_y;*/

protected:
	int block_image1[100];		//ステージブロック画像
	static int map_data[MAP_HEIGHT][MAP_WIDTH];
	static float scroll_x, scroll_y;	//マップスクロール量
public:
	STAGE();
	//マップ情報の更新
	void Update(PLAYER *player);
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
	static int GetMapDat(int y, int x) { return map_data[y][x]; }
	//マップの当たり判定 
	static bool HitMapDat(int y, int x); 
	//スライムのかけらの当たり判定
	bool HitThrowSlime(int y, int x);
	//画面スクロール座標Xをセット
	static bool SetScrollPos(int move_x);
	//画面スクロール座標Xの取得
	static float GetScrollX() { return scroll_x; };	
	//マップデータの読み込み
	void LoadMapData(void);	

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };
};

