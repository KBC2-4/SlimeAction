#include "Title.h"
#include "GameMain.h"
#include "DxLib.h"


Title::Title()
{
	if ((background_image = LoadGraph("Resource/Images/Stage/BackImage.png")) == -1) {
		throw "Resource/Images/Stage/BackImage.png";
	}

	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	selectmenu = 0;
}

Title::~Title() 
{
	DeleteGraph(background_image);
	InitFontToHandle();	//�S�Ẵt�H���g�f�[�^���폜
}

AbstractScene* Title::Update()
{
	static int input_margin;
	input_margin++;
	if (PAD_INPUT::GetPadThumbLY() > 300 && input_margin > 10) { selectmenu = (selectmenu + 2) % 3; input_margin = 0; }
	if (PAD_INPUT::GetPadThumbLY() < -300 && input_margin > 10) { selectmenu = (selectmenu + 1) % 3; input_margin = 0; }

	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B)return new GAMEMAIN();
	return this;
}

void Title::Draw()const
{
	DrawGraph(0, 0, background_image, false);
	DrawStringToHandle(318, 100, "�^�C�g��", 0x56F590, title_font ,0xFFFFFF);

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	//DrawBoxAA(400.0f, 300.0f, 800.0f, 680.0f, 0xF3F589, TRUE, 5.0f);
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

	//���
	//DrawCircleAA(475.0f, 398.0f + selectmenu * 90, 20, 3, 0xffffff, TRUE, 3.0f);

	//�I�����j���[
	DrawStringToHandle(510, 360, "�v���C", selectmenu == 0 ? 0xB3E0F5 : 0xEB8F63, menu_font ,0xFFFFFF);
	DrawStringToHandle(432, 450, "�����L���O", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);
	DrawStringToHandle(550, 540, "�I��", selectmenu == 2 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);


	//����ē�
	static int timer = 0;
	if (timer++ < 60) {
		DrawCircleAA(579.0f, 324.0f, 15, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(572, 310, 0.4f, 0.4f, "B", 0xEBA05E, menu_font, 0xFFFFFF);
		DrawExtendStringToHandle(600, 310, 0.4f, 0.4f, "�Ō���", 0xEBA05E, menu_font, 0xFFFFFF);
	}
	else if (timer > 120) { timer = 0; }
	

}