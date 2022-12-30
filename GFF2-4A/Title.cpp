#include "Title.h"
#include "GameMain.h"
#include "StageSelect.h"
#include "DrawRanking.h"
#include "DxLib.h"
#include "Option.h"

#define _USE_MATH_DEFINES
#include <math.h>

//�^�C�g���A�j���[�V����������N�����̂ݗL�������邽�߂̃t���O
static bool animation_flg = false;


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

	int se_random = GetRand(1);
	char dis_exit_se[30];
	sprintf_s(dis_exit_se, sizeof(dis_exit_se), "Resource/Sounds/SE/exit0%d.wav", se_random + 1);

	if ((exit_se = LoadSoundMem(dis_exit_se)) == -1) {
		throw dis_exit_se;
	}

	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 120, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	guid_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	selectmenu = 0;
	input_margin = 0;
	timer = 0;
	exit_flg = false;

	title_anitimer[0] = 0;

	//�^�C�g���A�j���[�V����������N�����̂ݗL����
	if (animation_flg == false) {
		title_anitimer[1] = 180;
		animation_flg = true;
	}
	else { title_anitimer[1] = 0; }

	option = new Option();

	

	//BGM
	ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.6, cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, exit_se);
}

Title::~Title()
{
	delete option;

	DeleteGraph(background_image);
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	DeleteSoundMem(exit_se);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteFontToHandle(guid_font);
}

AbstractScene* Title::Update()
{
	if (option->GetOptionFlg() == true) {
		option->Update();
		//BGM
		ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music);

		//SE
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.6, cursor_move_se);
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.2, ok_se);
		ChangeVolumeSoundMem(Option::GetSEVolume() * 1.3, exit_se);
	}
	else {

		if (input_margin < 20) {
			input_margin++;
		}
		else {

			//�^�C�g���A�j���[�V�������I����Ă���BGM���Đ�����
			if (title_anitimer[1] == 0 && !CheckSoundMem(background_music)) {
				PlaySoundMem(background_music, DX_PLAYTYPE_LOOP);
			}


			if (title_anitimer[1] <= 0) {
				if (PAD_INPUT::GetPadThumbLY() > 20000)
				{

					selectmenu = (selectmenu + 3) % 4;
					input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
					StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
				}

				if (PAD_INPUT::GetPadThumbLY() < -20000)
				{

					selectmenu = (selectmenu + 1) % 4; input_margin = 0;
					PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
					StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1);
				}
			}
		}

		if ((PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
		{

			if (title_anitimer[1] <= 0) {
				PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
				//ok_se����I����Ă����ʐ��ڂ���B
				while (CheckSoundMem(ok_se)) {}
				StartJoypadVibration(DX_INPUT_PAD1,  OK_VIBRATION_POWER, OK_VIBRATION_TIME, -1);

				switch (static_cast<MENU>(selectmenu))
				{

				case MENU::GAME_SELECT:
					return new STAGE_SELECT();
					break;

				case MENU::RANKING:
					return new DRAW_RANKING();
					break;

				case MENU::OPTION:
					option->ChangeOptionFlg();
					break;

				case MENU::END:
					exit_flg = true;
					PlaySoundMem(exit_se, DX_PLAYTYPE_BACK, FALSE);
					break;

				default:
					break;
				}

			}
			else { title_anitimer[1] = 0; }
		}
		timer++;

		if (exit_flg == true && !CheckSoundMem(exit_se)) { return nullptr; }

		//���v�t���[��
		if (title_anitimer[1] > 0) { title_anitimer[1]--; }

		//��]
		if (title_anitimer[0] < 180 && title_anitimer[1] > 0) { title_anitimer[0]++; }
		else { title_anitimer[0] = 0; }
	}

	return this;
}

void Title::Draw()const
{

	DrawGraph(0, 0, background_image, false);

	//�I�v�V������ʂ֓���
	if (option->GetOptionFlg() == true) {
		option->Draw();
	}
	else {

		DrawRotaStringToHandle(GetDrawCenterX("�X���C���A�N�V����", title_font, 600 - title_anitimer[1] * 3), 200 + title_anitimer[1] * 3, 1.0 - title_anitimer[1] * 0.01, 1.0 - title_anitimer[1] * 0.01, 600, 100, 10 * title_anitimer[0] * (M_PI / 180), 0x56F590, title_font, 0xFFFFFF, FALSE, "�X���C���A�N�V����");
		//DrawStringToHandle(GetDrawCenterX("�X���C���A�N�V����",title_font), 100, "�X���C���A�N�V����", 0x56F590, title_font, 0xFFFFFF);

		//�{�b�N�X
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		//DrawBoxAA(400.0f, 300.0f, 800.0f, 680.0f, 0xF3F589, TRUE, 5.0f);
		//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

		//���
		//DrawCircleAA(475.0f, 398.0f + selectmenu * 90, 20, 3, 0xffffff, TRUE, 3.0f);

		if (title_anitimer[1] > 0) { return; }

		//�I�����j���[
		DrawStringToHandle(GetDrawCenterX("�v���C", menu_font), 360, "�v���C", selectmenu == 0 ? 0xB3E0F5 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("�����L���O", menu_font), 450, "�����L���O", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("�I�v�V����", menu_font), 540, "�I�v�V����", selectmenu == 2 ? 0x5FEBB6 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(GetDrawCenterX("�I��", menu_font, 8), 630, "�I��", selectmenu == 3 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);



		//����ē�
		if (timer % 120 < 60)
		{

			if (GetJoypadNum() == 0) {
				DrawStringToHandle(GetDrawCenterX("�R���g���[���[��ڑ����Ă�������", guid_font), 280, "�R���g���[���[��ڑ����Ă�������", 0xFF5446, guid_font, 0xF53E27);
			}
			else {

				DrawCircleAA(530.0f, 311.0f, 30, 20, 0xFFFFFF, 1);

				DrawStringToHandle(510, 283, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
				DrawStringToHandle(570, 280, "�Ō���", 0xEBA05E, guid_font, 0xFFFFFF);
			}
		}
	}
}