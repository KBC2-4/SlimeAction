#pragma once
#include"PadInput.h"

#define MAX_LIFE				5		//プレイヤーの最大ライフ
#define SPEED					3.0f	//プレイヤーのスピード
#define DEVIATION				2000	//スティック入力の誤入力の範囲
#define ANIMATION_SWITCH_FRAME	1		//画像を切り替えるタイミング(フレーム)
#define IMAGE_MAX_NUM			10		//画像の枚数
#define JUMP_VELOCITY			-5.8f	//ジャンプスピード

enum class PLAYER_STATE {
	IDLE = 0,//停止しているとき
	MOVE,    //動いてるとき
	JUMP,    //跳ぶ
	FALL,	 //落下
	THROW,   //投げる時
	HOOK,    //フックをつかむとき
	DAMAGE,  //ダメージを受けた時
	DEAD     //死んだとき
};

class Player
{

private:
	float player_x,player_y;
	int map_x, map_y;
	int life;
	int image[100];
	int move_type;			//左か右の移動(反転用)
	int animation_frame;	//アニメーションのフレームのカウント
	int animation_type;		//今のアニメーションの添え字
	int animation_phase;	//アニメーションの段階(0: 前半, 1: 後半)
	int jump_mode;			//停止ジャンプ(1)か移動ジャンプ(2)か

	PLAYER_STATE player_state;		//ステート変数

public:
	Player();

	void Move();
	void Draw() const;
	void HookMove();
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update();


	/*変数のセットとゲット*/
	int GetLife() { return life; };
	float GetPlayerX() { return player_x; };
	float GetPlayerY() { return player_y; };

	void SetLife(int);
};

