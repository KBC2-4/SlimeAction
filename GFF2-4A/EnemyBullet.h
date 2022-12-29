#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"
#define BULLET_SPEED 12

class ENEMY_BULLET
{
private:
    int my_x, my_y;                   //���̓G�̍��W
    int draw_x;                       //�ǂɓ����������ɕ`��ꏊ�����炷���߂̕ϐ�
    double bullet_x, bullet_y, hypote;//�e�ׂ̍������W�ƎO�p�`�̎Ε�
    double player_x, player_y;        //�v���C���[�̍��W
    double dis_x, dis_y;              //�v���C���[�ƓG�̋���
    double bullet_sx, bullet_sy;      //�e��X�AY���ꂼ��̃X�s�[�h
    int map_x, map_y;                 //�e�̃}�b�v���X, Y�iint�^�j
    float mapd_x, mapd_y;             //�e�̃}�b�v���X,Y�idouble�j
    int o_map_x, o_map_y;             //�e�̃}�b�v��̌Â����W
    bool end_flg;                     //�e�̏�����A�j���[�V���������邩�ǂ���
    double rad_x;                     //�p�x�ύX�p�ϐ�
    float scroll_x;                   //�X�N���[���̒l(x)
    float scroll_y;                   //�X�N���[���̒l(y)
    bool delete_flg;                  //�f���[�g���邽�߂̃t���O
    bool hit_flg;                     //�v���C���[�̓������{�[���ɓ����������ǂ����̃t���O
    bool right_side_hit;              //���̂̉E���ʂɓ����������ǂ����̃t���O
    bool left_side_hit;               //���̂̍����ʂɂ����������ǂ����̃t���O
    double hit_rad;                   //�e�����̂ɓ����������ɂł�A�j���[�V�����̊p�x�̕ϐ�
    int bullet_images[4];             //�e�̃A�j���[�V�����p�̕ϐ�
    int bullet_end_images[20];        //�e���n�ʂɓ����������ɂł�A�j���[�V�����̕ϐ�
    double rad;                       //�p�x�̕ϐ�
    int image_index;                  //�摜�̔��ʗp�̕ϐ�
    int image;                        //�摜�̕ϐ�
    int animation_timer;              //�A�j���[�V�����̎���
    int animation_type;               //�A�j���[�V�����̔���
    int splash_se;                    //�e����Ƃ���SE

    PLAYER* player;                   //�v���C���[�̃N���X�̕ϐ�
    STAGE* stage;                     //�X�e�[�W�̃N���X�̕ϐ�

    const int ANIMATION_TIMER = 5;    //�A�j���[�V�����̎���
    const int IMAGE_Y_SIZE = 20;      //�摜�̏c�̃T�C�Y

private:
    float GetDrawX() const;           //�X�N���[���̒l���v�Z����֐�
    float GetDrawY() const;           //�X�N���[���̒l���v�Z����֐�

public:
    ENEMY_BULLET();                   //�ŏ��̃R���X�g���N�^
    ENEMY_BULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis,double,int); //�����A���̃R���X�g���N�^
    ~ENEMY_BULLET();               //�f�X�g���N�^

    void Update();                    //�e�̃A�b�v�f�[�g
    void Move();                      //�e�̓���
    void Hit();                       //�e�̓����蔻��
    /// <summary>
    /// �e��������A�j���[�V����
    /// </summary>
    /// <returns>�A�j���[�V�����̏I������</returns>
    bool EndAnimation();
    /// <summary>
    /// �ړ��A�j���[�V����
    /// </summary>
    void MoveAnimation();
    void Draw() const;                 //�e�̕`��
    bool GetDeleteFlg(){return delete_flg;}//�f���[�g�t���O�̃Q�b�g
};

