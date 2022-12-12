#pragma once
#include "AbstractScene.h"



class Option
{
private:
    int menu_font;
    int background_image;
    int cursor_move_se;
    int input_margin;
    static int bgm_vol;        //BGM�̉���
    static int se_vol;         //SE�̉���
    int selectmenu;     //�I�����Ă��郁�j���[
    bool option_flg;	//�I�v�V������ʕ\���t���O

public:

    //�R���X�g���N�^
    Option();
    //�f�X�g���N�^
    ~Option();
    //�`��ȊO�̍X�V�����s
    void Update();
    //�`��Ɋւ��邱�Ƃ�����
    void Draw();

    static int GetBGMVolume(void) { return bgm_vol; }
    static int GetSEVolume(void) { return se_vol; }
    bool GetOptionFlg(void) { return option_flg; }
    void ChangeOptionFlg(void) { option_flg = !option_flg; }
};

