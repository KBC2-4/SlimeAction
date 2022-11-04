#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TOMATO();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	TOMATO(PLAYER* player);

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;
	/// <summary>
	/// 移動
	/// </summary>
	void Move() override;
	/// <summary>
	/// 果汁を発射
	/// </summary>
	void Hit() override;
	/// <summary>
	/// アニメーション
	/// </summary>
	void Animation() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(float scroll_x)const override;
};

