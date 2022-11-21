#include "ThrowSlime.h"
#include "PadInput.h"
#include"PLAYER.h"
#include<math.h>

ThrowSlime::ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y) {
	if ((image = LoadGraph("Resource/Images/Player/Slime_Bullet.png")) == -1) {
		throw "Resource/Images/Player/Slime_Bullet.png";
	}

	throw_x = _throw_x;
	throw_y = _throw_y;
	throw_cnt = _throw_x.size();
	for (int i = 0; i < throw_cnt; i++) {
		throw_x[i] -= STAGE::GetScrollX();
		throw_y[i] -= STAGE::GetScrollY();
	}
	move_type = 0;
	move_x = 0;
	move_y = 0;
	throw_index = 0;
	throw_end = false;
	throw_fall = false;
}

void ThrowSlime::Update(STAGE* stage) {
	if (!throw_end) {
		if (move_type == 0) {
			throw_x[0] = throw_x[throw_index];
		}
		//else {
		throw_y[0] = throw_y[throw_index];

		/*if (throw_index >= throw_cnt)throw_end = true;*/


		if (++throw_index >= throw_cnt) {
			throw_end = true;
			return;
		}
		if (throw_y[0] < throw_y[throw_index])throw_fall = true;
		//throw_x[0] += move_x;
		//throw_y[0] += move_y;
		//move_y += 4.8f;
	//}

		if (HitBlock(stage)) {
			//Drop = true;
			throw_end = true;
		}
	}

}

void ThrowSlime::Draw() const {
	//DrawGraph(throw_x[0] + STAGE::GetScrollX(), throw_y[0], image, TRUE);
	DrawRotaGraph(throw_x[0] + STAGE::GetScrollX(), throw_y[0] + STAGE::GetScrollY(), 1, 1, image, TRUE);
	//printfDx("throw_y[0] = %f",throw_y[0]);
	//printfDx("throw_bottom = %f", throw_bottom);

}

int ThrowSlime::HitBlock(STAGE* stage) {
	if (throw_y[0] <= 0) {
		return false;
	}
	//if (throw_y[0] >= throw_y[throw_index + 1])throw_fall = true;
	int object = stage->GetMapDat(static_cast<int>(floor((throw_y[0] / MAP_CEllSIZE))), static_cast<int>(throw_x[0] / MAP_CEllSIZE));
	/*if (object == 23 && move_type != 1) {
		move_type = 1;
		move_x = 0;
		move_y = 1;
		if (throw_x[0] < throw_x[1]) {
			throw_x[0] += 20;
		}
		else {
			throw_x[0] -= 20;
		}
		return false;
	}
	else */if (throw_fall == true && stage->HitThrowSlime(static_cast<int>(floor(throw_y[0] / MAP_CEllSIZE)), static_cast<int>(throw_x[0] / MAP_CEllSIZE))) {
		if (object == 91 || object == 92 || object == 13 || object == 23) {
			return false;
		}
		//printfDx("%d\n", stage->GetMapDat(static_cast<int>(floor((throw_y[0] / MAP_CEllSIZE))), static_cast<int>(throw_x[0] / MAP_CEllSIZE)));
		throw_bottom = (static_cast<int>(throw_y[0])/* - MAP_CEllSIZE*/) % MAP_CEllSIZE;//throw_y[0] - ((throw_y[0]- MAP_CEllSIZE) / MAP_CEllSIZE)* MAP_CEllSIZE;
		if (throw_bottom <= 0) {
			return false;
		}
		throw_y[0] -= throw_bottom + 10;
		return true;
	}
	return false;
}


