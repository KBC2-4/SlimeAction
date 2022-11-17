#pragma once
#include"PLAYER.h"
#include"STAGE.h"
#include"ITEMBALL.h"


#define BALL_W 10
#define BALL_H 10

enum class ENEMY_STATE
{
	IDOL = 0,	//�A�C�h�����
	MOVE,		//�v���C���[��W�������킹�����Ă���Ƃ�
	RETURN,		//���ˉ\��Ԃɖ߂�
	PRESS,		//���ˏ��
	FALL,		//�������
	DETH		//���S���
};

class ENEMY
{
protected:
	int x, y;			//���W
	int map_x, map_y;	//�}�b�v���ł̍��W
	int* image;			//�摜�ۑ��p
	int animation_timer;//�A�j���[�V�����̎���
	int animation_type;	//�A�j���[�V�����̎��
	double rad;          //���W�A��
	ENEMY_STATE state;	//�G�l�~�[�̏��
	STAGE* stage;		//�X�e�[�W
	PLAYER* player;		//�X�e�[�W
	ITEMBALL* item;     //�h���b�v����A�C�e��

	const int IMAGE_SIZE = 80;
	const int ANIMATION_TIME = 5;	//�A�j���[�V�����̐؂�ւ�����

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ENEMY();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ENEMY()
	{
	}
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �ړ�
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// �v���C���[�Ƃ̊p�x�����߂�
	/// </summary>
	void ChangeAngle();
	/// <summary>
	/// �����蔻��
	/// </summary>
	virtual void Hit() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw()const = 0;

	/// <summary>
	/// �v���C���[�Ƃ̊p�x�̎擾
	/// </summary>
	/// <returns>�p�x</returns>
	double GetRadian()const { return rad; }
	/// <summary>
	/// X���W�̎擾
	/// </summary>
	/// <returns>x���W</returns>
	int GetX()const { return x; }
	/// <summary>
	/// Y���W�̎擾
	/// </summary>
	/// <returns>y���W</returns>
	int GetY()const { return y; }
};