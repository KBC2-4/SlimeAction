#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
private:
	int animation_timer;	//アニメーションの切り替え時間用変数
	int animation_type;		//アニメーションの画像タイプ
	int spawn_map_x;		//スポーン地点(x)
	int spawn_map_y;		//スポーン地点(y)
	double image_rate;			//画像サイズ
	const int ANIMATION_TIME = 5;	//アニメーションの切り替え時間
	const int WALL_SPEED = 10;		//落下速度
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TOMATO();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	/// <param name="stage">ステージのアドレス</param>
	/// <param name="spawn_y">マップ上のスポーン地点(y)</param>
	/// <param name="spawn_x">マップ上のスポーン地点(x)</param>
	TOMATO(PLAYER* player,STAGE* stage,int spawn_y,int spawn_x);
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

