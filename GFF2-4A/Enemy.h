#pragma once

enum class CITRUS_STATE
{
	IDOL = 0,	//アイドル状態
	MOVE,		//プレイヤーを標準を合わせ続けているとき
	STANDBY,	//発射準備
	RETURN,		//発射可能状態に戻る
	PRESS		//発射状態
};

class ENEMY
{
protected:
	int x, y;			//座標
	int map_x, map_y;	//マップ内での座標
	int image;			//画像

public:

	/// <summary>
	/// 移動
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// 果汁を発射
	/// </summary>
	virtual void ShotFruitJuice() = 0;
	/// <summary>
	/// アニメーション
	/// </summary>
	virtual void Animation() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw()const = 0 ;
	
};

