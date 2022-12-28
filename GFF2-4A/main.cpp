#include "DxLib.h"
#include"PadInput.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	double dNextTime = GetNowCount();

	SetMainWindowText("スライムアクション");
	SetMainWindowClassName("SlimeAction");
	SetWindowIconID(01);

	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動
	SetGraphMode(1280, 720, 32);

	SetWindowVisibleFlag(FALSE);// ウィンドウを表示させない

	SetAlwaysRunFlag(true);		//常にアクティブにする

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);		//フォントをアンチエイリアス対応にする。

	SetJoypadDeadZone(DX_INPUT_PAD1, 0.0);

	;	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

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
		SetWindowVisibleFlag(TRUE);// ウィンドウを表示させる

		//フレームレートの設定
		dNextTime += static_cast<double>(1.0 / 60.0 * 1000.0);
		if (dNextTime > GetNowCount()) {
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//補正


	}

	InitFontToHandle();	//全てのフォントデータを削除
	InitGraph();		//読み込んだ全てのグラフィックデータを削除
	InitSoundMem();		//読み込んだ全てのサウンドデータを削除
	DxLib_End();
	return 0;
}