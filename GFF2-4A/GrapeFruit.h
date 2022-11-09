#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"
#include<math.h>

class GRAPEFRUIT :
	public ENEMY
{
private:
	bool hitflg;
	bool flag;
	int shootcount;
	double rads[2];
	int animation_timer;
	int animation_type;
	int spawn_map_x;
	int spawn_map_y;
	ENEMYBULLET* bullet[3];
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GRAPEFRUIT();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	GRAPEFRUIT(PLAYER* player,STAGE* stage,int,int);


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

