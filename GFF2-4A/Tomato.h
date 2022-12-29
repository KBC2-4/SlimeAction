#pragma once
#include "Enemy.h"
class TOMATO :
	public ENEMY
{
private:
	int spawn_map_x;		//�X�|�[���n�_(x)
	int spawn_map_y;		//�X�|�[���n�_(y)

	int splash_se;		//�e����Ƃ���SE

	int now_image;			//���݂̉摜
	double image_rate;			//�摜�T�C�Y
	const int ANIMATION_TIME = 5;	//�A�j���[�V�����̐؂�ւ�����
	const int FALL_SPEED = 10;		//�������x
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TOMATO();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <param name="stage">�X�e�[�W�̃A�h���X</param>
	/// <param name="spawn_y">�}�b�v��̃X�|�[���n�_(y)</param>
	/// <param name="spawn_x">�}�b�v��̃X�|�[���n�_(x)</param>
	TOMATO(PLAYER* player,STAGE* stage,int spawn_y,int spawn_x);
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
	/// �����A�j���[�V����
	/// </summary>
	void FallAnimation();
	/// <summary>
	/// �A�C�h���A�j���V����
	/// </summary>
	/// <returns>�A�j���V�������I��������ǂ���</returns>
	bool IdolAnimation();
	/// <summary>
	/// ���S�A�j���[�V����
	/// </summary>
	/// <returns>�A�j���V�������I��������ǂ���</returns>
	bool DethAnimation();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const override;
};

