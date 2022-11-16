#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"
#include<math.h>

#define GURAFRU_W 80
#define GURAFRU_H 80


class GRAPEFRUIT :
	public ENEMY
{
private:
	bool hitflg;
	bool flag[3];
	int shootcount;
	double rads[2];
	int animation_timer;
	int animation_type;
	int spawn_map_x;
	int spawn_map_y;
	int target_x;
	int bullet_count;
	int check_hit_count;
	bool hit_flg;
	bool delete_flg;
	ENEMYBULLET* bullet[3];
	//ThrowSlime* throw_slime;
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
	/// 当たり判定
	/// </summary>
	void Hit() override;
	/// <summary>
	/// アニメーション
	/// </summary>
	void Animation();
	/// <summary>
	/// 描画
	/// </summary>
    void Draw()const override;

	bool GetDeleteFlg() { return delete_flg; }
	int GetSpawnMapY() { return spawn_map_y; }
	int GetSpawnMapX() { return spawn_map_x; }
};

