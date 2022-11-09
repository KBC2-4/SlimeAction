#include "ThrowSlime.h"
#include "PadInput.h"
#include "STAGE.h"
#include"PLAYER.h"

ThrowSlime::ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y) {
	if ((image = LoadGraph("Resource/Images/Player/SlimeBullet.png")) == -1) {
		throw "Resource/Images/Player/SlimeBullet.png";
	}

	throw_x = _throw_x;
	throw_y = _throw_y;
	throw_cnt = _throw_x.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_x[i] -= STAGE::GetScrollX();
	}
	throw_index = 0;
	throw_end = false;
	throw_fall = false;
}

void ThrowSlime::Update() {
	if (!throw_end) {
		throw_x[0] = throw_x[throw_index];
		throw_y[0] = throw_y[throw_index];
		
		/*if (throw_index >= throw_cnt)throw_end = true;*/
		

		if (++throw_index >= throw_cnt) {
			throw_end = true;
			return;
		}
		if (throw_y[0] < throw_y[throw_index])throw_fall = true;
		if(HitBlock()) throw_end = true;
	}
}

void ThrowSlime::Draw() const {
	//DrawGraph(throw_x[0] + STAGE::GetScrollX(), throw_y[0], image, TRUE);
	DrawRotaGraph(throw_x[0] + STAGE::GetScrollX(), throw_y[0], 1, 1, image, TRUE);
	printfDx("throw_y[0] = %f",throw_y[0]);
	printfDx("throw_bottom = %f", throw_bottom);
	
}

int ThrowSlime::HitBlock() {
	//if (throw_y[0] >= throw_y[throw_index + 1])throw_fall = true;
	if (throw_fall == true && STAGE::HitMapDat((static_cast<int>(throw_y[0]) / MAP_CEllSIZE), (static_cast<int>(throw_x[0]) - MAP_CEllSIZE*2) / MAP_CEllSIZE)) {
		throw_bottom = (static_cast<int>(throw_y[0]) - MAP_CEllSIZE) % MAP_CEllSIZE;//throw_y[0] - ((throw_y[0]- MAP_CEllSIZE) / MAP_CEllSIZE)* MAP_CEllSIZE;
		throw_y[0] -= throw_bottom+3;
		return true;
	}
	return false;
}