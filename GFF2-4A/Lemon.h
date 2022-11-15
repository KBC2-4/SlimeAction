#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"

class LEMON :
    public ENEMY
{
private:
	bool hitflg;
	bool delete_flag;
	int shootcount;
	double rads[2];
	int animation_timer;
	int animation_type;
	int spawn_map_x;
	int spawn_map_y;

	ENEMYBULLET* bullet;

	const int ANIMATION_TIME = 5;	//�A�j���[�V�����̐؂�ւ�����

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LEMON();

	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <param name="stage">�X�e�[�W�̃A�h���X</param>
	/// <param name="spawn_y">�}�b�v��̃X�|�[���n�_(y)</param>
	/// <param name="spawn_x">�}�b�v��̃X�|�[���n�_(x)</param>
	LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LEMON();
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
	/// ���̌`�ɖ߂�A�j���[�V����
	/// </summary>
	/// <returns>�A�j���[�V�����̏I������</returns>
	bool ReturnAnimation();
	/// <summary>
	/// �����A�j���[�V����
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// ���S�A�j���[�V����
	/// </summary>
	/// <returns>�A�j���V�������I��������ǂ���</returns>
	bool DethAnimation();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const override;

	bool GetDeleteFlag() { return delete_flag; }
};

