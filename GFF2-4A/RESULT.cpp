#include "Result.h"
#include "DxLib.h"

RESULT::RESULT() {
	if ((background_image = LoadGraph("Resource/Images/Enemy/gurepon.png")) == -1) {
		throw "Resource/Images/Enemy/gurepon.png";
	}
}


AbstractScene* RESULT::Update() {

}

void RESULT::Draw() const {
	DrawExtendGraph(0, 0, 1280,720, background_image, true);
}