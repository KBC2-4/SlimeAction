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
    LEMON();

	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <param name="stage">ステージのアドレス</param>
	/// <param name="spawn_y">マップ上のスポーン地点(y)</param>
	/// <param name="spawn_x">マップ上のスポーン地点(x)</param>
	LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>

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
	void ShotFruitJuice();
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

