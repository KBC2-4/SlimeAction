#pragma once
#include"PadInput.h"

#define MAX_LIFE				5		//プレイヤーの最大ライフ
#define SPEED					3.0f	//プレイヤーのスピード
#define DEVIATION				2000	//スティック入力の誤入力の範囲
#define ANIMATION_SWITCH_FRAME	1		//画像を切り替えるタイミング(フレーム)
#define IMAGE_MAX_NUM			10		//画像の枚数
#define JUMP_VELOCITY			-5.8f	//ジャンプスピード

//移動ステート
enum class PLAYER_MOVE_STATE {
	IDLE = 0,//停止しているとき
	MOVE,    //動いてるとき
	JUMP,    //跳ぶ
	FALL,	 //落下
	THROW,   //投げる時
	HOOK,    //フックをつかむとき
	DAMAGE,  //ダメージを受けた時
	DEAD     //死んだとき
};

//アニメーションステート
enum class PLAYER_ANIM_STATE {
	IDLE = 0,//アイドルアニメーション
	MOVE	 //移動アニメーション
};

class PLAYER
{

private:
	float player_x,player_y;
	int map_x, map_y;
	float player_left = 0, player_right = 0;
	float player_top = 0, player_bottom = 0;
	float rebound_x;
	int life;
	int now_image;			//描画する画像
	int images[2][10];		//アニメーションの画像
	int move_type;			//左か右の移動(反転用)
	int animation_frame;	//アニメーションのフレームのカウント
	int animation_type[2];		//今のアニメーションの添え字
	int animation_phase[2];	//アニメーションの段階(0: 前半, 1: 後半)
	int animation_mode;
	int jump_mode;			//停止ジャンプ(1)か移動ジャンプ(2)か
	//ステート変数
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;

public:
	PLAYER();

	void Move();
	void Draw() const;
	void HookMove();
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update();
	void HitBlock();

	/*変数のセットとゲット*/
	int GetLife() { return life; };
	float GetPlayerX() { return player_x; };
	float GetPlayerY() { return player_y; };

	void SetLife(int);
};

