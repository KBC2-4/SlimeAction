#pragma once
#include "AbstractScene.h"
#include "STAGE.h"
class Title :
    public AbstractScene
{
private:
    STAGE stage;
public:
    //�R���X�g���N�^
    Title();
    //�f�X�g���N�^
    ~Title()
    {
    }
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

