#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"

class LEMON :
    public ENEMY
{
private:
	bool hitflg;
	bool delete_flag;
	int shootcount;
	double rads[2];
	int animation_timer;
	int animation_type;
	int spawn_map_x;
	int spawn_map_y;

	ENEMYBULLET* bullet;

	const int ANIMATION_TIME = 5;	//アニメーションの切り替え時間

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
	/// デストラクタ
	/// </summary>
	~LEMON();
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
	/// 元の形に戻るアニメーション
	/// </summary>
	/// <returns>アニメーションの終了判定</returns>
	bool ReturnAnimation();
	/// <summary>
	/// 落下アニメーション
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	/// <returns>アニメションが終わったかどうか</returns>
	bool DethAnimation();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const override;

	bool GetDeleteFlag() { return delete_flag; }
};

