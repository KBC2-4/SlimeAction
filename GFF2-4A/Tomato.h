#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
private:
	int animation_timer;	//アニメーションの切り替え時間用変数
	int animation_type;		//アニメーションの画像タイプ
	const int ANIMATION_TIME = 5;	//アニメーションの切り替え時間
	const int WALL_SPEED = 1;		//落下速度
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TOMATO();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	TOMATO(PLAYER* player,STAGE* stage);
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
	/// アニメーション
	/// </summary>
	void Animation() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const override;
};

