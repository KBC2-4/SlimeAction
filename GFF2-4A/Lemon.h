#pragma once
#include"Enemy.h"

class LEMON :
    public ENEMY
{
private:

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="player"></param>
    LEMON();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	LEMON(PLAYER* player);

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
	void ShotFruitJuice() override;
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

