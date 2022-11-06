#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"
class GRAPEFRUIT :
	public ENEMY
{
private:
	bool hitflg;
	int shootcount;
	double rads[2];
	ENEMYBULLET* bullet;
	STAGE* stages;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GRAPEFRUIT();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	GRAPEFRUIT(PLAYER* player,STAGE* stage);


	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move() override;
	/// <summary>
	/// �ʏ`�𔭎�
	/// </summary>
	void ShotFruitJuice();
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
    void Draw(float scroll_x)const override;
};

