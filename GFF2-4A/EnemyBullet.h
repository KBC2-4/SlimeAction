#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"
class ENEMYBULLET
{
private:
    int my_x, my_y;                   //���̓G�̍��W
    double bullet_x, bullet_y, hypote;//�e�ׂ̍������W�ƎO�p�`�̎Ε�
    double player_x, player_y;        //�v���C���[�̍��W
    double dis_x, dis_y;              //�v���C���[�ƓG�̋���
    double bullet_sx, bullet_sy;      //�e��X�AY���ꂼ��̃X�s�[�h
    int map_x, map_y;
    float mapd_x, mapd_y;
    bool Hit_flg;                 //�e���������ǂ���
    double rad_x;                     //�p�x�ύX�p�ϐ�
    float scroll_x;
    int i = 0;
    double cos_x = 0.0;
    double sin_y = 0.0;
    PLAYER* player;
    STAGE* stage;

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player, STAGE*, int x, int y, double dis, float);
    ~ENEMYBULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// �A�j���[�V����
    /// </summary>
    void Animation();
    void Draw() const;

    bool GetHitFlg(){return Hit_flg;}

};

