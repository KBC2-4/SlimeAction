#include "Title.h"
#include "GameMain.h"
#include "DxLib.h"


Title::Title()
{
	if ((background_image = LoadGraph("Resource/Images/Stage/BackImage.png")) == -1) {
		throw "Resource/Images/Stage/BackImage.png";
	}
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	SetFontSize(135);
}

Title::~Title() 
{
	SetFontSize(DEFAULT_FONT_SIZE);
	DeleteGraph(background_image);
}

AbstractScene* Title::Update()
{
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B)return new GAMEMAIN();
	return this;
}

void Title::Draw()const
{
	DrawGraph(0, 0, background_image, false);
	DrawString(360, 100, "タイトル", 0x56F590, 0xFFFFFF);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	DrawBoxAA(460.0f, 300.0f, 800.0f, 600.0f, 0xF3F589, TRUE, 2.0f);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

	DrawExtendString(500, 400, 0.65f, 0.65f, "プレイ", 0xEB8F63, 0xFFFFFF);


	DrawCircleAA(612, 347, 30, 20, 0xFFFFFF, 1);
	DrawExtendString(600, 320, 0.4f, 0.4f, "B", 0xEBA05E, 0xFFFFFF);
	DrawExtendString(650, 320, 0.4f, 0.4f, "で", 0xEBA05E, 0xFFFFFF);
	

}