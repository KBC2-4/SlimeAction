#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
private:
	int animation_timer;	//�A�j���[�V�����̐؂�ւ����ԗp�ϐ�
	int animation_type;		//�A�j���[�V�����̉摜�^�C�v
	const int ANIMATION_TIME = 5;	//�A�j���[�V�����̐؂�ւ�����
	const int WALL_SPEED = 1;		//�������x
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TOMATO();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	TOMATO(PLAYER* player,STAGE* stage);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TOMATO();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move() override;
	/// <summary>
	/// �����蔻��
	/// </summary>
	void Hit() override;
	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void Animation() override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const override;
};

