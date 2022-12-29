#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"
#include<math.h>

#define GURAFRU_W 80
#define GURAFRU_H 80


class GRAPEFRUIT :
	public ENEMY
{
private:
	bool flag[3];                   //�e�����݂��Ă��邩�ǂ����̃t���O
	int shootcount;                 //�e�������o
	int animation_timer;            //�A�j���[�V�����̎���
	int animation_type;             //�A�j���[�V�����̎��
	int spawn_map_x;                //�}�b�v���X
	int spawn_map_y;                //�}�b�v���Y
	int target_x;                   //�O���|���̃^�[�Q�b�g���W
	int bullet_count;               //�e�����^�C�~���O
	bool delete_flg;                //������t���O
	int face_image[2];				//��̉摜
	int fruit_image[3];             //�ʎ��̉摜
	int damage_se;					//�_���[�W���󂯂�����SE
	int press_se;					//�v���X�A�j���[�V��������SE
	int splash_se;					//�e����Ƃ���SE

	ENEMY_BULLET* bullet[3];       //�e�̃N���X
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GRAPEFRUIT();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	GRAPEFRUIT(PLAYER* player,STAGE* stage,int,int);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GRAPEFRUIT();
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


	//�Q�b�g�֐�
	bool GetDeleteFlg() { return delete_flg; }
	int GetSpawnMapY() { return spawn_map_y; }
	int GetSpawnMapX() { return spawn_map_x; }
	int GetX();
};

