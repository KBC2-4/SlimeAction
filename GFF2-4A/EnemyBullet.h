#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
class ENEMYBULLET :
    public ENEMY
{
private:    
    int my_x, my_y;                   //���̓G�̍��W
    double bullet_x, bullet_y, hypote;//�e�ׂ̍������W�ƎO�p�`�̎Ε�
    double player_x, player_y;        //�v���C���[�̍��W
    double dis_x, dis_y;              //�v���C���[�ƓG�̋���
    double bullet_sx, bullet_sy;      //�e��X�AY���ꂼ��̃X�s�[�h
    bool bullet_flag;                 //�e���������ǂ���

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player,int x,int y);
    ~ENEMYBULLET() {};

    void Update() override;
    void Move() override;
    void Hit()override;
    /// <summary>
    /// �A�j���[�V����
    /// </summary>
    void Animation()override;
    void Draw() const override;

};

