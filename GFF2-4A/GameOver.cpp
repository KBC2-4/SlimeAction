#include "GameOver.h"
#include "GameMain.h"
#include "DxLib.h"

GameOver::GameOver()
{

	//GameOverImage��������
	if ((GameOverImage = (LoadGraph("Resource/Images/Result/GameOver_Image.png"))) == -1)
	{
		throw "Resource/Images/Result/GameOver_Image.png";
	}

	//Select�pfont��������
	Select_font = CreateFontToHandle("���C���I", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	//B�{�^���������̂𑣂�������pfont��������
	Button_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//Input_WaitTime��������
	Input_WaitTime= 0;

	//Selectcursor�̈ړ������J�E���g����ϐ���������
	SelectCount = 0;

	timer=0;
}

GameOver::~GameOver()
{
	DeleteGraph(GameOverImage);
	DeleteFontToHandle(Select_font);
}

AbstractScene* GameOver::Update()
{
	//WaitTime�����Z
	Input_WaitTime++;

	/*����͂���WaitTime��20���傫����cursor����ɁA
	�ŏ�̏ꍇ�͉���*/
	if (PAD_INPUT::GetPadThumbLY() > 1000 && Input_WaitTime > 20)
	{

		SelectCount = (SelectCount + 1) % 2;
		Input_WaitTime = 0;
	}

	/*�����͂���WaitTime��20���傫����cursor�����ɁA
	�ŏ�̏ꍇ�͏��*/
	if (PAD_INPUT::GetPadThumbLY() < -1000 && Input_WaitTime > 20)
	{

		SelectCount = (SelectCount + 1) % 2;
		Input_WaitTime = 0;
	}

	/*B�{�^������͂���PadState��ON�̂Ƃ��A
	SelectCount���w�肳�ꂽcase�̒l�Ȃ炻�̃R���X�g���N�^��new����B*/
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

		default:
			break;
		}
	}
	timer++;

	return this;
}

void GameOver::Draw() const
{

	//GameOver�pImage
	DrawGraph(0, 0, GameOverImage, FALSE);

	//�f�o�b�O�pLine
	DrawLine(0, 360, 1280, 360, 0x000000);
	DrawLine(640, 0, 640, 720, 0x000000);
	DrawLine(0, 460, 1280, 460, 0x000000);

	//Select�pString
	DrawStringToHandle(330, 360, "GameSelect", SelectCount == 0 ? 0x95ff89 : 0x000000, Select_font, 0x000000);
	DrawStringToHandle(445, 460, "Restart", SelectCount == 1 ? 0x95ff89 : 0x000000, Select_font, 0x000000);

	if (timer % 120 < 60)
	{

		//B�{�^�����������Ƃ𑣂�(�\����\����؂�ւ�)
		DrawCircleAA(580.5f, 627.5f, 20, 20, 0x000000, 1);
		DrawExtendStringToHandle(572, 610, 0.4f, 0.4f, "B", 0x20ff07, Button_font, 0x000000);
		DrawExtendStringToHandle(600, 610, 0.4f, 0.4f, "�Ō���", 0x95ff89, Button_font, 0x000000);
	}
}