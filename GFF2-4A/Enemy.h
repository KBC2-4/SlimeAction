#pragma once
#include"PLAYER.h"

enum class ENEMY_STATE
{
	IDOL = 0,	//アイドル状態
	MOVE,		//プレイヤーを標準を合わせ続けているとき
	STANDBY,	//発射準備
	RETURN,		//発射可能状態に戻る
	PRESS,		//発射状態
	DETH		//死亡状態
};

class ENEMY
{
protected:
	int x, y;			//座標
	int map_x, map_y;	//マップ内での座標
	int image;			//画像
	int w, h;			//幅、高さ
	int angle;			//角度
	ENEMY_STATE state;	//エネミーの状態

	PLAYER* player;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ENEMY();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ENEMY()
	{
		delete player;
	}
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Updata() = 0;
	/// <summary>
	/// 移動
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// プレイヤーとの角度を求める
	/// </summary>
	void ChangeAngle();
	/// <summary>
	/// 果汁を発射
	/// </summary>
	virtual void ShotFruitJuice() = 0;
	/// <summary>
	/// 当たり判定
	/// </summary>
	virtual void Hit() = 0;
	/// <summary>
	/// アニメーション
	/// </summary>
	virtual void Animation() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw()const = 0;

	/// <summary>
	/// プレイヤーとの角度の取得
	/// </summary>
	/// <returns>角度</returns>
	int GetAngle()const { return angle; }
	/// <summary>
	/// X座標の取得
	/// </summary>
	/// <returns>x座標</returns>
	int GetX()const { return x; }
	/// <summary>
	/// Y座標の取得
	/// </summary>
	/// <returns>y座標</returns>
	int GetY()const { return y; }
};