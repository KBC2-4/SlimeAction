#include "DxLib.h"
#include "Lemon.h"

LEMON::LEMON()
{
	//‰æ‘œ‚ÌŽæ“¾
	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/gurepon.png")) == -1)
	{
		throw "Resource/Images/Enemy/gurepon.png";
	}


	shootcount = 0;
	hitflg = false;
	rad = 0.0;
	for (int i = 0; i < 2; i++)
		rads[i] = 0.0;
	flag = false;
	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	animation_timer = 0;
	animation_type = 0;

	
	bullet = nullptr;
}


LEMON::LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//ƒXƒ|[ƒ“êŠ‚ÌÝ’è
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = (spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2);
	y = spawn_map_y * MAP_CEllSIZE;
	flag = false;
	
	//‰æ‘œ‚ÌŽæ“¾
	image = new int;
	if ((*image = LoadGraph("Resource/Images/Enemy/lemoner.png")) == -1)
	{
		throw "Resource/Images/Enemy/lemoner.png";
	}
	shootcount = 0;

	for (int i = 0; i < 2; i++)
	{
		rads[i] = 0.0;
	}
	bullet = nullptr;
	this->player = player;
	this->stage = stage;

	animation_timer = 0;
	animation_type = 0;
}

void LEMON::Update()
{
	ChangeAngle();
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280)) {
		if (++shootcount % 180 == 0) {
			if (flag == false) {
				bullet= new ENEMYBULLET(player,stage, x, y, 0.0, stage->GetScrollX());
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
				bullet = nullptr;
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

void LEMON::Hit()
{

}

void LEMON::Animation()
{

}

void LEMON::Draw() const
{
	DrawRotaGraph2(x + stage->GetScrollX(), y, 40, 0, 1, rad + (-90 * (PI / 180)), image[0], TRUE);
	if (bullet != nullptr)
	{
		bullet->Draw();
	}
}