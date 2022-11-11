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
    bool bullet_flag;                 //�e���������ǂ���
    double rad_x;                     //�p�x�ύX�p�ϐ�
    float now_scroll_x;
    float old_scroll_x;
    float scroll_x;
    float GetDrawX() const;
    bool delete_flg;
    PLAYER* player;
    STAGE* stage;

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis, float scroll);
    ~ENEMYBULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// �A�j���[�V����
    /// </summary>
    void Animation();
    void Draw() const;

    bool GetDeleteFlg(){return delete_flg;}
};

