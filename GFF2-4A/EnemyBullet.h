#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"


class ENEMY_BULLET
{
private:
    int my_x, my_y;                   //���̓G�̍��W
    double bullet_x, bullet_y, hypote;//�e�ׂ̍������W�ƎO�p�`�̎Ε�
    double player_x, player_y;        //�v���C���[�̍��W
    double dis_x, dis_y;              //�v���C���[�ƓG�̋���
    double bullet_sx, bullet_sy;      //�e��X�AY���ꂼ��̃X�s�[�h
    int map_x, map_y;
    float mapd_x, mapd_y;
    bool end_flg;                     //�e�̏�����A�j���[�V���������邩�ǂ���
    bool bullet_flag;                 //�e���������ǂ���
    double rad_x;                     //�p�x�ύX�p�ϐ�
    float now_scroll_x;
    float old_scroll_x;
    float scroll_x;
    float GetDrawX() const;
    bool delete_flg;
    bool hit_flg;
    int bullet_images[4];
    int bullet_end_images[20];
    double rad;
    int image_index;
    int image;
    int animation_timer;
    int animation_type;
    PLAYER* player;
    STAGE* stage;

    const int ANIMATION_TIMER = 5;
    const int IMAGE_Y_SIZE = 20;
public:
    ENEMY_BULLET();
    ENEMY_BULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis, float scroll,double,int);
    ~ENEMY_BULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// �e��������A�j���[�V����
    /// </summary>
    /// <returns>�A�j���[�V�����̏I������</returns>
    bool EndAnimation();
    /// <summary>
    /// �ړ��A�j���[�V����
    /// </summary>
    void MoveAnimation();
    void Draw() const;

    bool GetDeleteFlg(){return delete_flg;}
};

