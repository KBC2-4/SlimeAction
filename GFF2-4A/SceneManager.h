#pragma once
#include "AbstractScene.h"

class SceneManager :
    public AbstractScene
{
private:
    AbstractScene* mScene;
public:
    //コンストラクタ
    SceneManager(AbstractScene* scene) :mScene(scene) {};
    //デストラクタ
    ~SceneManager()
    {
        delete mScene;
    }
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;
};
