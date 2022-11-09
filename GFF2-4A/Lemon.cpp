#include "DxLib.h"
#include "Lemon.h"

LEMON::LEMON()
{
	x = 0;
	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/lemoner.png")) == -1)
	{
		throw "Resource/Images/Enemy/lemoner.png";
	}
}


LEMON::LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//ƒXƒ|[ƒ“êŠ‚ÌÝ’è
	x = spawn_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	y = spawn_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	this->player = player;
	this->stage = stage;

	state = ENEMY_STATE::IDOL;

	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/lemoner.png")) == -1)
	{
		throw "Resource/Images/Enemy/lemoner.png";
	}
}

void LEMON::Update()
{
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280)) {
		if (++shootcount % 180 == 0) {
			if (flag == false) {
				bullet= new ENEMYBULLET(player, x, y, 0.0, stage->GetScrollX());
				flag = true;
			}
		}
		if (flag)
		{
			bullet->Update();
		}
		if (shootcount % 360 == 0) {
			if (flag)
			{
				delete bullet;
				flag = false;
			}
		}
	}

	Move();
	Animation();
	Hit();
}
void LEMON::Move()
{

}

void LEMON::ShotFruitJuice()
{

}

void LEMON::Hit()
{

}

void LEMON::Animation()
{

}

void LEMON::Draw() const
{
	DrawRotaGraph2(x + stage->GetScrollX(), y, 40, 0, 1, rad + (-90 * (PI / 180)), image[0], TRUE);
	bullet->Draw();
}