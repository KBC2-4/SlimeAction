#include "Result.h"
#include "GameMain.h"
#include "DxLib.h"

RESULT::RESULT(bool issue,int clear_time) {
	if ((clear_background_image = LoadGraph("Resource/Images/Enemy/mi_hasya_kao.png")) == -1) {
		throw "Resource/Images/Enemy/mi_hasya_kao.png";
	}

	if ((gameover_background_image = LoadGraph("Resource/Images/Enemy/gurepon.png")) == -1) {
		throw "Resource/Images/Enemy/gurepon.png";
	}
	//ChangeFont("")
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8,-1,8);
	menu_font = CreateFontToHandle("メイリオ", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	time_font = CreateFontToHandle("メイリオ", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8,-1,5);

	timer = 4 * 60;
	win = issue;

	time = clear_time;
	diff_time = GetNowCount();
}

RESULT::~RESULT() {
	DeleteGraph(clear_background_image);
	DeleteGraph(gameover_background_image);
	InitFontToHandle();	//全てのフォントデータを削除
}

AbstractScene* RESULT::Update() {

	if(--timer  <= 60){
		return new GAMEMAIN();
	}

	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new GAMEMAIN(); }

	return this;
}

void RESULT::Draw() const {

	if (win == true) {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		DrawExtendGraph(0, 0, 1280, 720, clear_background_image, true);
		DrawStringToHandle(170, 200, "ゲームクリア", 0xF5F2B4, title_font, 0xF5EA1D);
		DrawStringToHandle(330, 350, "クリアタイム", 0xF5EB67, time_font, 0xFFFFFF);	//デバッグ
		char dis_clear_time[18];	//文字列合成バッファー
		sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%5d秒%.3dミリ秒", (diff_time - time) / 1000, (diff_time - time) % 1000);	//文字列合成
		DrawStringToHandle(160, 450, dis_clear_time, 0xF5EB67, time_font, 0xFFFFFF);	//デバッグ
		DrawFormatStringToHandle(20, 560, 0x56F590, menu_font , "%2d秒後にリスタートします", timer / 60);
	}
	else {
		DrawFillBox(0, 0, 1280, 720, 0xFFFFFF);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(0, 0, 1280, 720, gameover_background_image, true);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawStringToHandle(90, 200, "ゲームオーバー", 0xEB8A95, title_font , 0xEB3D49);
		DrawFormatStringToHandle(20, 400, 0x56F590, menu_font, "%2d秒後にリスタートします", timer / 60);
	}

	static int timer = 0;
	if (timer++ < 50) {
		DrawCircleAA(530.0f, 668.0f, 22, 20, 0xFFFFFF, 1);
		DrawExtendStringToHandle(518, 650, 0.4f, 0.4f, "B", 0xEB7415, menu_font, 0xFFFFFF);
		DrawExtendStringToHandle(560, 650, 0.4f, 0.4f, "でスキップ", 0x76F567, menu_font, 0xFFFFFF);
	}
	else if (timer > 100) { timer = 0; }
}