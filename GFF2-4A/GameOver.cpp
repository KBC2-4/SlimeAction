#include "GameOver.h"
#include "GameMain.h"
#include "DxLib.h"

GameOver::GameOver()
{

	//GameOverImageを初期化
	if ((GameOverImage = (LoadGraph("Resource/Images/Result/GameOver_Image.png"))) == -1)
	{
		throw "Resource/Images/Result/GameOver_Image.png";
	}

	//Select用fontを初期化
	Select_font = CreateFontToHandle("メイリオ", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//Input_WaitTimeを初期化
	Input_WaitTime= 0;

	//Selectcursorの移動数をカウントする変数を初期化
	SelectCount = 0;
}

AbstractScene* GameOver::Update()
{
	//WaitTimeを加算
	Input_WaitTime++;

	/*上入力かつWaitTimeが20より大きい時cursorを上に、
	最上の場合は下へ*/
	if (PAD_INPUT::GetPadThumbLY() > 1000 && Input_WaitTime > 20)
	{

		SelectCount = (SelectCount + 1) % 2;
		Input_WaitTime = 0;
	}

	/*下入力かつWaitTimeが20より大きい時cursorを下に、
	最上の場合は上へ*/
	if (PAD_INPUT::GetPadThumbLY() < -1000 && Input_WaitTime > 20)
	{

		SelectCount = (SelectCount + 1) % 2;
		Input_WaitTime = 0;
	}

	/*Bボタンを入力かつPadStateがONのとき、
	SelectCountが指定されたcaseの値ならそのコンストラクタをnewする。*/
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
	{

		switch (static_cast<GAMEOVER_MENU>(SelectCount))
		{

		case  GAMEOVER_MENU::ReSelect:
			return new Title();
			break;

		case GAMEOVER_MENU::NewGame:
			return new GAMEMAIN();
			break;
		}
	}

	return this;
}

void GameOver::Draw() const
{

	//GameOver用Image
	DrawGraph(0, 0, GameOverImage, FALSE);

	//デバッグ用Line
	DrawLine(0, 360, 1280, 360, 0x000000);
	DrawLine(640, 0, 640, 720, 0x000000);
	DrawLine(0, 460, 1280, 460, 0x000000);

	//Select用String
	DrawStringToHandle(330, 360, "GameSelect", SelectCount == 0 ? 0x95ff89 : 0x000000, Select_font, 0x000000);
	DrawStringToHandle(445, 460, "Restart", SelectCount == 1 ? 0x95ff89 : 0x000000, Select_font, 0x000000);
}