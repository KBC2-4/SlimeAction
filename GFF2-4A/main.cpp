#include "DxLib.h"
#include"PadInput.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	double dNextTime = GetNowCount();

	SetMainWindowText("");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);		//�t�H���g���A���`�G�C���A�X�Ή��ɂ���B

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;
	try
	{
		sceneMng = new SceneManager((AbstractScene*)new GAMEMAIN());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "data/ErrLog/ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {


		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();	//�p�b�h�̓��͏�Ԃ̍X�V
		sceneMng->Draw();

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

		//�t���[�����[�g�̐ݒ�
		dNextTime += 16.66;
		if (dNextTime > GetNowCount()) {
			WaitTimer((int)dNextTime - GetNowCount());
		}

		//Back�{�^�����������狭���I��
		if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_BACK) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}