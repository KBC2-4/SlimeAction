#include "Result.h"
#include "GameMain.h"
#include "DxLib.h"

RESULT::RESULT() {
	if ((background_image = LoadGraph("Resource/Images/Enemy/gurepon.png")) == -1) {
		throw "Resource/Images/Enemy/gurepon.png";
	}
}

AbstractScene* RESULT::Update() {

	static int count = GetNowCount();
	timer = count - GetNowCount();
	if ((GetNowCount() - count) > 3000) {
		count = GetNowCount();
		return new GAMEMAIN();
		
	}

	return this;
}

void RESULT::Draw() const {
	DrawExtendGraph(0, 0, 1280,720, background_image, true);
	DrawExtendFormatString(20, 200, 5.0f, 5.0f, 0x56F590, "リスタートします。\n　　%d", -timer / 1000);
}