#include "AbstractScene.h"
#include "DxLib.h"

int AbstractScene::GetDrawCenterX(int screenX, const char* string, int font_handle)const {
	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}