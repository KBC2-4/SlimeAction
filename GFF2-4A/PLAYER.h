#pragma once
#include"PadInput.h"

enum class PLAYER_STATE {
	IDLE = 0,//��~���Ă���Ƃ�
	MOVE,    //�����Ă�Ƃ�
	JUMP,    //����
	THROW,   //�����鎞
	HOOK,    //�t�b�N�����ނƂ�
	DAMAGE,  //�_���[�W���󂯂���
	DEAD     //���񂾂Ƃ�
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



	/*�ϐ��̃Z�b�g�ƃQ�b�g*/
	int GetLife() { return life; };

	void SetLife(int);
};

