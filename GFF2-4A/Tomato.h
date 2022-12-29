#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
private:
	int spawn_map_x;		//スポーン地点(x)
	int spawn_map_y;		//スポーン地点(y)

	int splash_se;		//弾けるときのSE

	int now_image;			//現在の画像
	double image_rate;			//画像サイズ
	const int ANIMATION_TIME = 5;	//アニメーションの切り替え時間
	const int FALL_SPEED = 10;		//落下速度
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TOMATO();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <param name="stage">ステージのアドレス</param>
	/// <param name="spawn_y">マップ上のスポーン地点(y)</param>
	/// <param name="spawn_x">マップ上のスポーン地点(x)</param>
	TOMATO(PLAYER* player,STAGE* stage,int spawn_y,int spawn_x);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TOMATO();
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;
	/// <summary>
	/// 移動
	/// </summary>
	void Move() override;
	/// <summary>
	/// 当たり判定
	/// </summary>
	void Hit() override;
	/// <summary>
	/// 落下アニメーション
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// アイドルアニメション
	/// </summary>
	/// <returns>アニメションが終わったかどうか</returns>
	bool IdolAnimation();
	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	/// <returns>アニメションが終わったかどうか</returns>
	bool DethAnimation();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const override;
};

