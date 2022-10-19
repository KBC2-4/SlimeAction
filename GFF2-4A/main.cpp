#include "DxLib.h"
#include"PadInput.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	double dNextTime = GetNowCount();

	SetMainWindowText("");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);		//フォントをアンチエイリアス対応にする。

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

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
		//ファイルオープン
		fopen_s(&fp, "data/ErrLog/ErrLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {


		ClearDrawScreen();		// 画面の初期化
		PAD_INPUT::UpdateKey();	//パッドの入力状態の更新
		sceneMng->Draw();

		ScreenFlip();			// 裏画面の内容を表画面に反映

		//フレームレートの設定
		dNextTime += 16.66;
		if (dNextTime > GetNowCount()) {
			WaitTimer((int)dNextTime - GetNowCount());
		}

		//Backボタンを押したら強制終了
		if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_BACK) && (PAD_INPUT::GetPadState() == PAD_STATE::ON))
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}