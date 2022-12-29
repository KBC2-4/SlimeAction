#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"

class LEMON :
    public ENEMY
{
private:
	bool hitflg;		//ダメージ受けたかどうか
	bool delete_flag;	//敵を削除するかどうか
	int shootcount;		//弾を撃つ感覚
	
	int now_image;		//使用している画像

	int damage_se;		//ダメージを受けた時のSE
	int press_se;		//プレスアニメーション時のSE
	int splash_se;		//弾けるときのSE

	int spawn_map_x;	//スポーン地点(x)
	int spawn_map_y;	//スポーン地点(y)

	ENEMY_BULLET* bullet;

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
	/// 弾の発射時のアニメーション
	/// </summary>
	/// <returns>アニメーションの終了判定</returns>
	bool PressAnimation();
	/// <summary>
	/// 落下アニメーション
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	/// <returns>アニメーションの終了判定</returns>
	bool DethAnimation();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const override;

	bool GetDeleteFlag() { return delete_flag; }
	int GetMapX() { return map_x; }
	int GetMapY() { return map_y; }
};

