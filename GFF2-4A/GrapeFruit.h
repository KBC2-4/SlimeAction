#pragma once
#include"Enemy.h"
class GRAPEFRUIT :
	public ENEMY
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GRAPEFRUIT();
	/// <summary>
	/// 移動
	/// </summary>
	void Move() override;
	/// <summary>
	/// 果汁を発射
	/// </summary>
	void ShotFruitJuice()override;
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
	virtual void Draw()const override;
};

