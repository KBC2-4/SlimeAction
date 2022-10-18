#pragma once
#include"Enemy.h"
class GRAPEFRUIT :
	public ENEMY
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GRAPEFRUIT();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	GRAPEFRUIT(PLAYER* player);
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move() override;
	/// <summary>
	/// �ʏ`�𔭎�
	/// </summary>
	void ShotFruitJuice()override;
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
	virtual void Draw()const override;
};

