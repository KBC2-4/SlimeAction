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
	bool flag[3];                   //弾が存在しているかどうかのフラグ
	int shootcount;                 //弾を撃つ感覚
	int animation_timer;            //アニメーションの時間
	int animation_type;             //アニメーションの種類
	int spawn_map_x;                //マップ上のX
	int spawn_map_y;                //マップ上のY
	int target_x;                   //グレポンのターゲット座標
	int bullet_count;               //弾を撃つタイミング
	bool delete_flg;                //消えるフラグ
	int face_image[2];				//顔の画像
	int fruit_image[3];             //果実の画像
	int damage_se;					//ダメージを受けた時のSE
	int press_se;					//プレスアニメーション時のSE
	int splash_se;					//弾けるときのSE

	ENEMY_BULLET* bullet[3];       //弾のクラス
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
	/// デストラクタ
	/// </summary>
	~GRAPEFRUIT();
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


	//ゲット関数
	bool GetDeleteFlg() { return delete_flg; }
	int GetSpawnMapY() { return spawn_map_y; }
	int GetSpawnMapX() { return spawn_map_x; }
	int GetX();
};

