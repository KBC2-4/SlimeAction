#include "RESULT.h"
#include "GameMain.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "Option.h"
#include "Ranking.h"

RESULT::RESULT(bool issue, int clear_time, const char* stage_name)
{

	Result_font = CreateFontToHandle("���C���I", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	time_font = LoadFontDataToHandle("Resource/Fonts/TimeAttack.dft", 2);

	if ((Result_Image = LoadGraph("Resource/Images/Result/GameClear.png")) == -1) {
		throw "Resource/Images/Enemy/mi_hasya_kao.png";
	}

	if ((count_se = LoadSoundMem("Resource/Sounds/SE/321.wav")) == -1) {
		throw "Resource/Sounds/SE/321.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}


	se_randnum = GetRand(3);

	char dis_good_se[30];
	sprintf_s(dis_good_se, sizeof(dis_good_se), "Resource/Sounds/SE/good%d.wav", se_randnum + 1);

	if ((good_se[se_randnum] = LoadSoundMem(dis_good_se)) == -1) {
		throw dis_good_se;
	}


	char dis_bad_se[30];
	sprintf_s(dis_bad_se, sizeof(dis_bad_se), "Resource/Sounds/SE/bad%d.wav", se_randnum + 1);

	if ((bad_se[se_randnum] = LoadSoundMem(dis_bad_se)) == -1) {
		throw dis_bad_se;
	}



	if (issue == true) { timer = 10 * 60; }
	else { timer = 8 * 60; }

	win = issue;

	this->clear_time = clear_time;

	*effect_timer = 0;
	guide_timer = 0;

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), count_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), good_se[se_randnum]);
	ChangeVolumeSoundMem(Option::GetSEVolume(), bad_se[se_randnum]);


	//�����L���O�o�^
	if (stage_name == "Stage01")
	{
		RANKING::Insert(this->clear_time, 1);
	}
	else if (stage_name == "Stage02")
	{
		RANKING::Insert(this->clear_time, 2);
	}
	else if (stage_name == "Stage03")
	{
		RANKING::Insert(this->clear_time, 3);
	}
	else {}
}

RESULT::~RESULT()
{

	DeleteFontToHandle(Result_font);
	DeleteFontToHandle(time_font);
	DeleteGraph(Result_Image);
	DeleteSoundMem(count_se);
	DeleteSoundMem(ok_se);
	DeleteSoundMem(good_se[se_randnum]);
	DeleteSoundMem(bad_se[se_randnum]);
}

AbstractScene* RESULT::Update()
{

	if (win == true && timer == 10 * 60) { PlaySoundMem(good_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if (win == false && timer == 8 * 80) { PlaySoundMem(bad_se[se_randnum], DX_PLAYTYPE_BACK, FALSE); }
	if (timer <= 5 * 60) { if (CheckSoundMem(count_se) == FALSE)PlaySoundMem(count_se, DX_PLAYTYPE_BACK, FALSE); }

	if (timer <= 60) { return new STAGE_SELECT(); }
	else { --timer; }

	//�K�C�h�_�ŕ\��
	if (guide_timer < 100)
	{

		guide_timer++;
	}
	else
	{

		guide_timer = 0;
	}

	if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A) && PAD_INPUT::GetPadState() == PAD_STATE::ON)
	{

		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE); return new STAGE_SELECT();
	}

	return this;
}


void RESULT::Draw() const {

	if (win == true)
	{
		DrawFillBox(0, 0, 1280, 720, 0x000000);
		DrawExtendGraph(0, 0, 1280, 720, Result_Image, true);

		char dis_clear_time[20];	//�����񍇐��o�b�t�@�[

		//�����񍇐�
		if (clear_time / 1000 >= 60)
		{

			sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%02d.%.3d",
				(clear_time / 1000) / 60, (clear_time / 1000) % 60, clear_time % 1000);
		}
		else
		{

			sprintf_s(dis_clear_time, sizeof(dis_clear_time),
				"%5d.%.3d", clear_time / 1000, clear_time % 1000);
		}

		//�N���A�^�C��
		DrawStringToHandle(330, 300, "�N���A�^�C��", 0x1aff00, Result_font, 0x000000);

		DrawStringToHandle(GetDrawCenterX(dis_clear_time, time_font), 400, dis_clear_time, 0x1aff00, time_font, 0xFFFFFF);

		DrawFormatStringToHandle(30, 540, 0x56F590, Result_font, "%2d�b��Ƀ��X�^�[�g���܂�", timer / 60);
	}

	if (guide_timer < 50)
	{

		DrawCircleAA(530.0f, 668.0f, 22, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(518, 650, 0.4f, 0.4f, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, Result_font, 0xFFFFFF);
		DrawExtendStringToHandle(560, 650, 0.4f, 0.4f, "�ŃX�L�b�v", 0x76F567, Result_font, 0xFFFFFF);
	}
}