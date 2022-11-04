#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	x = 200;
	animation_timer = 0;
	animation_type = 0;
	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::TOMATO(PLAYER* player, STAGE* stage)
{
	x = 200;
	this->player = player;
	this->stage = stage;
	animation_timer = 0;
	animation_type = 0;
	state = ENEMY_STATE::WALL;

	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::~TOMATO()
{
	delete[] image;
}
void TOMATO::Update()
{

	//�}�b�v��̍��W�̐ݒ�
	map_x = x / MAP_CEllSIZE;
	map_y = y / MAP_CEllSIZE;
	Move();
	Animation();
	Hit();

	if ((fabsf(player->GetPlayerX() - x) < 240) && (state != ENEMY_STATE::DETH))
	{
		state = ENEMY_STATE::WALL;
	}

	//��ʊO�ɏo������
	if (y > 720)
	{
		state = ENEMY_STATE::IDOL;
	}
}

void TOMATO::Move()
{
	//������Ԃ̎��̏���
	if (state == ENEMY_STATE::WALL)
	{
		y += WALL_SPEED;
	}
}


void TOMATO::Hit()
{
	//�n�ʂ�u���b�N�Ƃ̓����蔻��
	if (state == ENEMY_STATE::WALL)
	{
		if (stage->GetMapDat(map_y, map_x) != 0)
		{
			state = ENEMY_STATE::DETH;
		}
	}
}

void TOMATO::Animation()
{
	//�A�C�h����ԂȂ�A�C�h���̎��̉摜���g�p
	if (state == ENEMY_STATE::IDOL)
	{
		now_image = image[0];
	}
	//������Ԃ̎��̉摜�̓���ւ�
	if (state == ENEMY_STATE::WALL)
	{
		if (++animation_timer % ANIMATION_TIME == 0)
		{
			now_image = image[(++animation_type % 2) + 1];
		}
	}
}


void TOMATO::Draw()const
{
	DrawRotaGraph(x + stage->GetScrollX(), y, 1, 0, now_image, TRUE);
	DrawCircle(x, y, 33, 0xffffff, FALSE);
	DrawFormatString(100, 100, 0xffffff, "%d,%d", map_x, map_y);
}