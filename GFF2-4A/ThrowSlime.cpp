#include "ThrowSlime.h"
#include "PadInput.h"
#include"PLAYER.h"
#include<math.h>

ThrowSlime::ThrowSlime(float player_x, float player_y, float throw_rad, STAGE* stage) : ve(110.0f) {
	if ((image = LoadGraph("Resource/Images/Player/Slime_Bullet.png")) == -1) {
		throw "Resource/Images/Player/Slime_Bullet.png";
	}

	throw_del = false;

	vx0 = ve * cosf(throw_rad);
	vy0 = ve * sinf(throw_rad);

	x0 = player_x;
	y0 = player_y;

	vx = vx0;
	vy = vy0;

	time = 0.0f;
	maxY = stage->GetMapSize().y * MAP_CEllSIZE;
}

void ThrowSlime::Finalize() {
	DeleteGraph(image);
}

void ThrowSlime::Update(STAGE* stage, ELEMENT* element) {
	x0 = x0 + vx * dt;
	y0 = y0 - vy * dt;
	vy = vy - g * dt;
	if (vy < 0) {
		g += 0.2f;
	}
	time += dt;

	if (maxY < y0) {
		throw_del = true;
	}
	else {
		Hit(stage, element);
	}
}

void ThrowSlime::Draw(STAGE *stage) const {
	DrawRotaGraph(x0 + stage->GetScrollX(), y0 + stage->GetScrollY(), 1.0, 0.0, image, TRUE);
}

void ThrowSlime::Hit(STAGE* stage, ELEMENT* element) {
	//マップの上部を越えたら当たり判定を無視
	if (y0 <= 0) {
		return;
	}

	//リフトの当たり判定
	std::vector<ELEMENT::ELEMENT_DATA> lift = element->GetLift();
	for (int i = 0; i < lift.size(); i++) {
		if (x0 - BULLETRADIUS <= lift[i].x + LIFT_SIZE && x0 + BULLETRADIUS >= lift[i].x
			&& y0 - BULLETRADIUS <= lift[i].y + MAP_CEllSIZE / 2 && y0 + BULLETRADIUS >= lift[i].y) {
			throw_del = true;
			return;
		}
	}
	
	int object = stage->GetMapData(static_cast<int>(floor((y0 / MAP_CEllSIZE))), static_cast<int>(x0 / MAP_CEllSIZE));
	if (stage->HitThrowSlime(static_cast<int>(floor(y0 / MAP_CEllSIZE)), static_cast<int>(x0 / MAP_CEllSIZE)) == true) {
		if (object == 91 || object == 92) { return; } //敵
		if (object == 51 || object == 52 || object == 53 || object == 54) return; //リフト
		if (object == 21 || object == 22 || object == 23 || object == 24) { return; } //木
		if (object == 64 || object == 65) { return; } //開いたドア

		throw_del = true;
	}

	return;
}