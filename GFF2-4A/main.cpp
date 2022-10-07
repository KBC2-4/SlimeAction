#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("");
	ChangeWindowMode(TRUE);

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

	if (DxLib_Init() == -1)return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && GameState != 99) {

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();


		DrawBoxAA(50, 50, 600, 600, 0xFFFFFF, TRUE, 3.0f);


		ScreenFlip();





	}
	DxLib_End();

	return 0;
}