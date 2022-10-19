#pragma once
#include"PLAYER.h"

enum class ENEMY_STATE
{
	IDOL = 0,	//�A�C�h�����
	MOVE,		//�v���C���[��W�������킹�����Ă���Ƃ�
	STANDBY,	//���ˏ���
	RETURN,		//���ˉ\��Ԃɖ߂�
	PRESS,		//���ˏ��
	DETH		//���S���
};

class ENEMY
{
protected:
	int x, y;			//���W
	int map_x, map_y;	//�}�b�v���ł̍��W
	int image;			//�摜
	int w, h;			//���A����
	int angle;			//�p�x
	ENEMY_STATE state;	//�G�l�~�[�̏��

	PLAYER* player;
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
		delete player;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Updata() = 0;
	/// <summary>
	/// �ړ�
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// �v���C���[�Ƃ̊p�x�����߂�
	/// </summary>
	void ChangeAngle();
	/// <summary>
	/// �ʏ`�𔭎�
	/// </summary>
	virtual void ShotFruitJuice() = 0;
	/// <summary>
	/// �����蔻��
	/// </summary>
	virtual void Hit() = 0;
	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	virtual void Animation() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw()const = 0;

	/// <summary>
	/// �v���C���[�Ƃ̊p�x�̎擾
	/// </summary>
	/// <returns>�p�x</returns>
	int GetAngle()const { return angle; }
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