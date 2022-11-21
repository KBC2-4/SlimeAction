#pragma once
#include "AbstractScene.h"
#include "STAGE.h"
#include "PadInput.h"

#define VERSION     2.34

class Title :
    public AbstractScene
{
private:
    int background_image;
    int cursor_move_se, ok_se;
    int title_font,menu_font;
    int selectmenu;
    
public:
    //�R���X�g���N�^
    Title();
    //�f�X�g���N�^
    ~Title();
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

