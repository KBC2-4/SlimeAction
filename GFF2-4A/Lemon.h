#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"

class LEMON :
    public ENEMY
{
private:
	bool hitflg;		//�_���[�W�󂯂����ǂ���
	bool delete_flag;	//�G���폜���邩�ǂ���
	int shootcount;		//�e�������o
	
	int now_image;		//�g�p���Ă���摜

	int damage_se;		//�_���[�W���󂯂�����SE
	int press_se;		//�v���X�A�j���[�V��������SE
	int splash_se;		//�e����Ƃ���SE

	int spawn_map_x;	//�X�|�[���n�_(x)
	int spawn_map_y;	//�X�|�[���n�_(y)

	ENEMY_BULLET* bullet;

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
	/// �e�̔��ˎ��̃A�j���[�V����
	/// </summary>
	/// <returns>�A�j���[�V�����̏I������</returns>
	bool PressAnimation();
	/// <summary>
	/// �����A�j���[�V����
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// ���S�A�j���[�V����
	/// </summary>
	/// <returns>�A�j���[�V�����̏I������</returns>
	bool DethAnimation();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const override;

	bool GetDeleteFlag() { return delete_flag; }
	int GetMapX() { return map_x; }
	int GetMapY() { return map_y; }
};

