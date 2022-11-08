#include "DxLib.h"
#include "Tomato.h"


TOMATO::TOMATO()
{
	x = 0;
	image_rate = 0.;
	spawn_map_x = 0;
	spawn_map_y = 0;
	animation_timer = 0;
	animation_type = 0;
	image = new int[3];
	if (LoadDivGraph("Resource/Images/Enemy/tomaton.png", 3, 3, 1, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/tomaton.png";
	}
}

TOMATO::TOMATO(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//�X�|�[���ꏊ�̐ݒ�
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
	y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	this->player = player;
	this->stage = stage;

	image_rate = 0.;
	animation_timer = 0;
	animation_type = 0;
	state = ENEMY_STATE::IDOL;

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
	//�摜�T�C�Y�����̑傫�����ȏ�ɂȂ�����
	if (image_rate >= 1)
	{
		//�v���C���[�����͈͈ȓ��ɓ����Ă���ԗ�����
		if ((fabsf(player->GetPlayerX() - (x + stage->GetScrollX())) < 240) && (state == ENEMY_STATE::IDOL))
		{
			animation_timer = 0; 
			state = ENEMY_STATE::WALL;
		}
		else if ((state != ENEMY_STATE::WALL) && (state != ENEMY_STATE::DETH))
		{
			state = ENEMY_STATE::IDOL;
		}
	}
	//�}�b�v��̍��W�̐ݒ�
	map_x = x / MAP_CEllSIZE;
	map_y = y / MAP_CEllSIZE;
	
	Move();
	Animation();
	Hit();

	//�������I�����܂��́A��ʊO�ɏo����A�C�h����Ԃɂ���
	if(((state==ENEMY_STATE::DETH) && (animation_timer > 60)) || (y > 720))
	{
		state = ENEMY_STATE::IDOL;
		image_rate = 0;
		//�X�|�[���n�_�Ɉړ�
		x = spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2;
		y = spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2;

	}

	
}

void TOMATO::Move()
{
	//������Ԃ̎��̏���
	if (state == ENEMY_STATE::WALL)
	{
		y += FALL_SPEED;
	}
}


void TOMATO::Hit()
{
	//�n�ʂ�u���b�N�Ƃ̓����蔻��
	if (state == ENEMY_STATE::WALL)
	{
		if ((stage->GetMapDat(map_y, map_x) != 0) && stage->GetMapDat(map_y, map_x) != 93)
		{
			state = ENEMY_STATE::DETH;
			animation_timer = 0;
		}
	}
}

void TOMATO::Animation()
{

	if (++animation_timer % ANIMATION_TIME == 0)
	{
		//�A�C�h����ԂȂ�A�C�h���̎��̉摜���g�p
		if (state == ENEMY_STATE::IDOL)
		{
			if (image_rate < 1.0)
			{
				image_rate += 0.1;
			}
			else
			{
				image_rate = 1.0;
			}
			now_image = image[0];
		}
		//������Ԃ̎��̉摜�̓���ւ�
		if (state == ENEMY_STATE::WALL)
		{
			now_image = image[(++animation_type % 2) + 1];
		}
		//�u���b�N�ɓ���������
		if (state == ENEMY_STATE::DETH)
		{
	
		}
	}
}


void TOMATO::Draw()const
{
	//��ʊO�ɏo����`�悵�Ȃ�
	if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280))
	{
		DrawRotaGraph(x + stage->GetScrollX(), y, image_rate, 0, now_image, TRUE);
	}
}