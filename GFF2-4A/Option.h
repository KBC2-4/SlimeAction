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
    int bgm_vol;        //BGM�̉���
    int se_vol;         //SE�̉���
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

    int GetBGMVolume(void) { return bgm_vol; }
    int GetSEVolume(void) { return se_vol; }
};

