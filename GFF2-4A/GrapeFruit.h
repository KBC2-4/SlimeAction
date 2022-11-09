#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
#include"STAGE.h"
#include<math.h>

#define GURAFRU_W 80
#define GURAFRU_H 80
#define BALL_W 10
#define BALL_H 10


class GRAPEFRUIT :
	public ENEMY
{
private:
	bool hitflg;
	bool flag;
	int shootcount;
	double rads[2];
	int animation_timer;
	int animation_type;
	int spawn_map_x;
	int spawn_map_y;
	int bullet_count;
	int check_hit_count;
	bool hit_flg;
	bool delete_flg;
	ENEMYBULLET* bullet[3];
	//ThrowSlime* throw_slime;
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

	bool GetDeleteFlg() { return delete_flg; }
};

