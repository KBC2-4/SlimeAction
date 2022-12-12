#pragma once
#include "AbstractScene.h"



class Option :	public AbstractScene
{
private:
    int menu_font;
    int background_image;
    int background_music;
    int cursor_move_se;
    int input_margin;
    static int bgm_vol;        //BGM�̉���
    static int se_vol;         //SE�̉���
    int selectmenu;     //�I�����Ă��郁�j���[

public:

    //�R���X�g���N�^
    Option();
    //�f�X�g���N�^
    ~Option();
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    static int GetBGMVolume(void) { return bgm_vol; }
    static int GetSEVolume(void) { return se_vol; }
};

