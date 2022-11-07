#include "ThrowSlime.h"
#include "PadInput.h"

ThrowSlime::ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y) {
	if ((image = LoadGraph("Resource/Images/Player/SlimeBullet.png")) == -1) {
		throw "Resource/Images/Player/SlimeBullet.png";
	}

	throw_x = _throw_x;
	throw_y = _throw_y;
	throw_cnt = _throw_x.size();
	throw_index = 0;
	throw_end = false;
}

void ThrowSlime::Update() {
	if (!throw_end) {
		throw_x[0] = throw_x[throw_index];
		throw_y[0] = throw_y[throw_index++];
		if (throw_index >= throw_cnt)throw_end = true;
	}
}

void ThrowSlime::Draw() const {
	if (PAD_INPUT::GetNowKey() != XINPUT_BUTTON_RIGHT_THUMB) {
		DrawGraph(throw_x[0], throw_y[0], image, TRUE);
	}
}