#pragma once
#include "AbstractScene.h"
#include "Title.h"

enum class GAMEOVER_MENU
{


	NewGame = 0,		//Restart
	ReSelect			//GameSelect
};

class GameOver : public AbstractScene
{
private:
	int title_image,background_image;
	int selectmenu;
	int menu_font;
	int guid_font;
	int background_music;
	int bad_se[4], ok_se, cursor_move_se;
	int input_margin;
	int timer,se_randnum;
	const char* stage_name;	//リスタート時のステージ選択用
	
public:
	//コンストラクタ
	GameOver(const char* stage_name);
	//デストラクタ
	~GameOver();
	//描画以外の処理
	AbstractScene* Update() override;
	//描画処理
	void Draw() const override;
};