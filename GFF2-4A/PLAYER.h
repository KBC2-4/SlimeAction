#pragma once
#include"PadInput.h"
#include "Element.h"

#define MAX_LIFE				5		//プレイヤーの最大ライフ
#define SPEED					3.0f	//プレイヤーのスピード
#define DEVIATION				2000	//スティック入力の誤入力の範囲
#define ANIMATION_SWITCH_FRAME	1		//画像を切り替えるタイミング(フレーム)
#define IMAGE_MAX_NUM			10		//画像の枚数
#define JUMP_VELOCITY			-5.8f	//ジャンプスピード
#define HOOK_MAX_DISTANCE		480

#define PI 3.1415926535897932384626433832795
#define LENGTH      200                 // 紐の長さ
#define CLENGTH     (LENGTH * 2 * PI)   // 紐を伸ばして一周させた場合に出来る円の円周の長さ
#define G           9.81                // 重力加速度

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
	static float player_x, player_y;
	int map_x, map_y;
	float player_left = 0, player_right = 0;
	float player_top = 0, player_bottom = 0;
	float rebound_x;
	float jump_move_x;
	int life;
	int now_image;			//描画する画像
	int images[2][10];		//アニメーションの画像
	int move_type;			//左か右の移動(反転用)
	int animation_frame;	//アニメーションのフレームのカウント
	int animation_type[2];		//今のアニメーションの添え字
	int animation_phase[2];	//アニメーションの段階(0: 前半, 1: 後半)
	int animation_mode;
	int jump_mode;			//停止ジャンプ(1)か移動ジャンプ(2)か
	bool jump_request;
	bool is_hook_move;
	float hook_angle;
	float hook_distance;

	float hook_y, hook_x;

	double x;     // 紐を伸ばして一周させた場合に出来る円の線上の座標、０は紐が軸の真下に伸びた位置
	double speed; // xの変化速度
	double angle;
	int nx, ny;
	double b = 8.0;		//デフォルト8
	double mass = 4.0;

	//ステート変数
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;

public:
	PLAYER();

	void Move();
	void Draw() const;
	void HookMove(ELEMENT* element);
	void JumpMove();
	void Throw();
	void MoveAnimation();
	void Update(ELEMENT*element);
	void HitBlock();
	void Scroll(float move_x);

	/*変数のセットとゲット*/
	int GetLife() { return life; };
	static float GetPlayerX() { return player_x; };
	static float GetPlayerY() { return player_y; };

	void SetLife(int);
};

