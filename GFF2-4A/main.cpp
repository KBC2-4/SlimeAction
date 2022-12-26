#include "DxLib.h"
#include"PadInput.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	double dNextTime = GetNowCount();

	SetMainWindowText("�X���C���A�N�V����");
	SetMainWindowClassName("SlimeAction");
	SetWindowIconID(01);

	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
	SetGraphMode(1280, 720, 32);

	SetWindowVisibleFlag(FALSE);// �E�B���h�E��\�������Ȃ�

	SetAlwaysRunFlag(true);		//��ɃA�N�e�B�u�ɂ���

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);		//�t�H���g���A���`�G�C���A�X�Ή��ɂ���B

	SetJoypadDeadZone(DX_INPUT_PAD1, 0.0);

	;	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

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
		PAD_INPUT::UpdateKey();	//�p�b�h�̓��͏�Ԃ̍X�V
		sceneMng->Draw();

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
		SetWindowVisibleFlag(TRUE);// �E�B���h�E��\��������

		//�t���[�����[�g�̐ݒ�
		dNextTime += static_cast<double>(1.0 / 60.0 * 1000.0);
		if (dNextTime > GetNowCount()) {
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//�␳

		//Back�{�^�����������狭���I��
		if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_DPAD_DOWN) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
		{
			break;
		}
		//START�{�^���Ń^�C�g����ʂֈڍs
		//if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) { sceneMng = new SceneManager((AbstractScene*)new Title()); }
	}

	InitFontToHandle();	//�S�Ẵt�H���g�f�[�^���폜
	InitGraph();		//�ǂݍ��񂾑S�ẴO���t�B�b�N�f�[�^���폜
	InitSoundMem();		//�ǂݍ��񂾑S�ẴT�E���h�f�[�^���폜
	DxLib_End();
	return 0;
}