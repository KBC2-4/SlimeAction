#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new Title());

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
		FPSC.All();
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		if ((PAD_INPUT::GetPadFlag()) && (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_BACK) || (CheckHitKey(KEY_INPUT_ESCAPE) == 1))
		{
			break;
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	return 0;
}