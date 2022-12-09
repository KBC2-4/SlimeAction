#pragma once
#include "AbstractScene.h"
#include "STAGE.h"
#include "GameOver.h"
#include "PadInput.h"

enum class MENU
{

    GAME_SELECT=0,
    RANKING,
    END
};
class Title : public AbstractScene
{
private:

    int background_image;
    int background_music;
    int cursor_move_se, ok_se;
    int title_font, menu_font;
    int selectmenu;
    int input_margin;
    int timer;

public:

    //コンストラクタ
    Title();
    //デストラクタ
    ~Title();
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;
};