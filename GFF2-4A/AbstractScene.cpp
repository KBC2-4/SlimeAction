#include "AbstractScene.h"
#include "DxLib.h"

AbstractScene::AbstractScene() {
	static short initialized = 0;

	//�v���O�����J�n����2��Ă΂��̂𖳌���
	if (initialized > 1 ) {
		CommonProcess();
	}
	else {
		initialized++;
	}
}


void AbstractScene::CommonProcess() {
	
	//���\�[�X�����Z�b�g
	InitFontToHandle();
	InitGraph();
	InitSoundMem();
}

int AbstractScene::GetDrawCenterX(const char* string, int font_handle, int margin)const {

	//��ʕ�
	const int screenX = 1280;

	if (margin >= screenX || margin <= -screenX) {
		margin = 0;
	}

	if (font_handle == 0) {
		font_handle = DX_DEFAULT_FONT_HANDLE;
	}


	const int w = screenX / 2 + margin - (GetDrawFormatStringWidthToHandle(font_handle, string) / 2);
	return w;
}