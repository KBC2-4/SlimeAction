#include "Title.h"
#include "GameMain.h"
#include "StageSelect.h"
#include "DrawRanking.h"
#include "DxLib.h"


Title::Title()
{

	if ((background_image = LoadGraph("Resource/Images/Stage/BackImage1.png")) == -1) 
	{
		throw "Resource/Images/Stage/BackImage1.png";
	}

	if ((background_music = LoadSoundMem("Resource/Sounds/BGM/title.wav")) == -1) {
		throw "Resource/Sounds/BGM/title.wav";
	}

	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) 
	{
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) 
	{
		throw "Resource/Sounds/SE/ok.wav";
	}

	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 120, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	selectmenu = 0;
	input_margin = 0;
	timer = 0;

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);
}

Title::~Title() 
{

	DeleteGraph(background_image);
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
}

AbstractScene* Title::Update()
{

	input_margin++;

	if (PAD_INPUT::GetPadThumbLY() > 1000 && input_margin > 20) 
	{ 

		selectmenu = (selectmenu + 2) % 3;  
		input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); 
		StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); 
	}

	if (PAD_INPUT::GetPadThumbLY() < -1000 && input_margin > 20) 
	{ 

		selectmenu = (selectmenu + 1) % 3; input_margin = 0;
		PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
		StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
	}

	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) 
	{

		switch (static_cast<MENU>(selectmenu))
		{

		case MENU::GAME_SELECT:
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); 
			StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1); 
			return new STAGE_SELECT();
			break;

		case MENU::RANKING:
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); 
			StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1); 
			return new DRAW_RANKING();
			break;

		case MENU::END:
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
			StartJoypadVibration(DX_INPUT_PAD1, 180, 160, -1);
			InitFontToHandle();	//�S�Ẵt�H���g�f�[�^���폜
			InitGraph();		//�ǂݍ��񂾑S�ẴO���t�B�b�N�f�[�^���폜
			InitSoundMem();
			return nullptr;
			break;

		default:
			break;
		}
	}
	timer++;
	
	return this;
}

void Title::Draw()const
{

	DrawGraph(0, 0, background_image, false);
	DrawStringToHandle(30, 100, "�X���C���A�N�V����", 0x56F590, title_font ,0xFFFFFF);

	//�{�b�N�X
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
	if (timer % 120 < 60) 
	{
		DrawCircleAA(579.0f, 324.0f, 15, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(572, 310, 0.4f, 0.4f, "B", 0xEB7415, menu_font, 0xFFFFFF);
		DrawExtendStringToHandle(600, 310, 0.4f, 0.4f, "�Ō���", 0xEBA05E, menu_font, 0xFFFFFF);
	}

}