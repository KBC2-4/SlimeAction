#pragma once
#include"PadInput.h"
#include "Element.h"
#include <vector>
#include "ThrowSlime.h"
#include "STAGE.h"

#define MAX_LIFE				5		//プレイヤーの最大ライフ
#define SPEED					3.0f	//プレイヤーのスピード
#define DEVIATION				2000	//スティック入力の誤入力の範囲
#define JUMP_VELOCITY			-5.8f	//ジャンプスピード
#define HOOK_MAX_DISTANCE		280
#define ANIMATION_TYPE			7

#define PI 3.1415926535897932384626433832795
#define LENGTH      200                 // 紐の長さ
#define CLENGTH     (LENGTH * 2 * PI)   // 紐を伸ばして一周させた場合に出来る円の円周の長さ
#define G           9.81                // 重力加速度

#define MIN_SIZE_SCALE		0.8f	//プレイヤーの最小サイズ(倍率)

//移動ステート
enum class PLAYER_MOVE_STATE {
	IDLE = 0,//停止しているとき
	MOVE,    //動いてるとき
	JUMP,    //跳ぶ
	FALL,	 //落下
	THROW,   //投げる時
	HOOK,    //フックをつかむとき
	DAMAGE,  //ダメージを受けた時
	DEAD,     //死んだとき
};

//アニメーションステート
enum class PLAYER_ANIM_STATE {
	IDLE = 0,//アイドルアニメーション
	MOVE,	 //移動アニメーション
	THROW,	 //投げるアニメーション
	HOOK,
	JUMP,	//ジャンプアニメーション
	FALL,
	LANDING,
};

class PLAYER
{

private:
	bool is_death;
	static float player_x, player_y;
	float old_player_x, old_player_y;
	int map_x, map_y;
	float jump_move_x;
	bool is_ground;		//地面についてるかどうか
	bool hit_ceil;

	int life;
	int images[ANIMATION_TYPE][10];		//アニメーションの画像
	int hp_img;
	int hand_img;
	int move_type;			//左か右の移動(反転用)
	float move_x;
	int jump_mode;			//停止ジャンプ(1)か移動ジャンプ(2)か
	bool is_jump;
	bool jump_request;
	float jumppower;
	float jump_velocity;

	//hook
	bool is_hook_move;
	float hook_angle;
	float hook_distance;
	float hook_y, hook_x;
	int hook_index;
	
	double x;     // 紐を伸ばして一周させた場合に出来る円の線上の座標、０は紐が軸の真下に伸びた位置
	double speed; // xの変化速度
	double angle;
	int nx, ny;
	double b = 8.0;		//デフォルト8
	double mass = 4.0;

	//Throw
	bool throw_preparation;
	int throw_ball_image;
	float throw_rad;

	std::vector<ThrowSlime> throw_slime;
	std::vector<float>throw_x;
	std::vector<float>throw_y;
	int throw_index = 0;

	//点滅用
	bool is_damage;
	int alpha_param;	//パラーメーター
	int alpha_time;		//点滅時間

	//プレイヤーのサイズ(倍率)
	float player_scale;

	typedef struct Animation {
		//画像を切り替えるタイミング(フレーム)
		const int switch_frame;

		//アニメーションの再生の仕方
		//-1: 固定
		// 0: 一枚目から再生したら逆再生する
		// 1: 一枚目から再生したら一枚目に戻す
		// 2: 最後までされたら最後の画像で固定
		const int play_type;

		//アニメーション画像の枚数
		const int image_num;

		//アニメーションの優先度
		const int priority;

		//アニメーションのフレームのカウント
		int frame = 0;

		//今のアニメーションの添え字
		int type = 0;

		//play_typeが0のアニメーションの段階(0: 前半, 1: 後半)
		int phase = 0;

		//ループ再生かどうか(0: ループ再生)
		int playMode;

		//アニメーションの終了判定
		bool endAnim;
	};
	Animation animation[ANIMATION_TYPE]{
		{  3,  1,  9, 0 },	//アイドル
		{  1,  0, 10, 0 },	//移動
		{  3,  1,  7, 2 },	//投げる
		{  1, -1,  1, 0 },	//フック
		{ 20,  1,  4, 1 },	//ジャンプ
		{ 20,  2,  4, 1 },	//落下
		{  2,  1, 10, 1 },	//着地
	};

	//ステート変数
	PLAYER_MOVE_STATE player_state;
	PLAYER_ANIM_STATE animation_state;
	STAGE *stage;

public:
	PLAYER(STAGE* stage);

	void Move();
	void Draw(STAGE* stage) const;
	void HookMove(ELEMENT* element, STAGE* stage);
	void JumpMove();
	void Throw(STAGE* stage);
	void MoveAnimation();
	void Update(ELEMENT*element, STAGE* stage);
	void HitBlock(ELEMENT* element, STAGE* stage);
	void ChangeAnimation(PLAYER_ANIM_STATE anim, bool compelChange = false);

	/*変数のセットとゲット*/
	int GetLife() { return life; };
	bool IsDeath() { return is_death; }
	float GetPlayerX() { return player_x + stage->GetScrollX(); }
	float GetPlayerY() { return player_y+stage->GetScrollY(); }

	void SetPlayerX(float x) { player_x = x - stage->GetScrollX(); }
	void SetPlayerY(float y) { player_y = y; }
	void SetPlayer_Screen(POINT screen) { player_x = screen.y; player_y = screen.x; }

	int GetThrowCnt() { return throw_slime.size(); }
	ThrowSlime GetThrowSlime(int index) { return throw_slime[index]; }

	double GetSpeed() { return speed; }
	float GetMoveX() { return move_x; }

	float GetPlayerScale() { return player_scale; }

	float GetJumpVelocity() { return jump_velocity; }

	void SetLife(int a);

	PLAYER_MOVE_STATE GetPlayerMoveState() { return player_state; }
};
