#pragma once
#include "AbstractScene.h"
#include "Title.h"

enum class GAMEOVER_MENU
{

	ReSelect=0,	//GameSelect
	NewGame		//Restart
};

class GameOver : public AbstractScene
{
private:
	int GameOverImage;	//画像用変数
	int SelectCount;	//Select用変数
	int Select_font;	//Select_font用変数
	int Input_WaitTime;	//SelectcursorのWaitTime
	
public:
	//コンストラクタ
	GameOver();
	//デストラクタ
	~GameOver(){}
	//描画以外の処理
	AbstractScene* Update() override;
	//描画処理
	void Draw() const override;
};