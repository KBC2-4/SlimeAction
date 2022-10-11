#pragma once
#include"PadInput.h"

enum class PLAYER_STATE {
	IDLE = 0,//停止しているとき
	MOVE,    //動いてるとき
	JUMP,    //跳ぶ
	THROW,   //投げる時
	HOOK,    //フックをつかむとき
	DAMAGE,  //ダメージを受けた時
	DEAD     //死んだとき
};

class PLAYER
{

private:
	int player_x,player_y;
	int map_x, map_y;
	int life;
	int image[100];
	const int MAX_LIFE = 5;
public:
	PLAYER();

	void Move();
	void Draw() const;
	void HookMove();
	void JumpMove();
	void Throw();
	void MoveAnimation();



	/*変数のセットとゲット*/
	int GetLife() { return life; };

	void SetLife(int);
};

