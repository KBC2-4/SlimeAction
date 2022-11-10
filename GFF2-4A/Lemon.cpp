#include "DxLib.h"
#include "Lemon.h"

LEMON::LEMON()
{
	//�摜�̎擾
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

	state = ENEMY_STATE::IDOL;
	bullet = nullptr;
}


LEMON::LEMON(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	//�X�|�[���ꏊ�̐ݒ�
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = (spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2);
	y = spawn_map_y * MAP_CEllSIZE;
	flag = false;
	
	//�摜�̎擾
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

	state = ENEMY_STATE::IDOL;

}

void LEMON::Update()
{

	
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		ChangeAngle();
		if (++shootcount % 180 == 0)
		{
			state = ENEMY_STATE::PRESS;
		}
		break;
	case ENEMY_STATE::RETURN:
		if (ReturnAnimation())
		{
			state = ENEMY_STATE::MOVE;
		}
		break;
	case ENEMY_STATE::PRESS:
		bullet = new ENEMYBULLET(player, stage, x, y, rad, stage->GetScrollX());
		state = ENEMY_STATE::RETURN;
		break;
	case ENEMY_STATE::FALL:
		Move();
		break;
	case ENEMY_STATE::DETH:
		break;
	default:
		break;
	}

	//�}�b�v��̍��W�̐ݒ�
	map_x = x / MAP_CEllSIZE;
	map_y = y / MAP_CEllSIZE;

	//�e�����݂��Ă���Ƃ��ɒe�̏������s��
	if (bullet != nullptr)
	{
		bullet->Update();

		//�e����ʊO�ɏo�邩�A�����ɓ���������e���폜
		if ((x + stage->GetScrollX() < 0) || (x + stage->GetScrollX() > 1280) || (y > 720) ||
			bullet->GetHitFlg())
		{
			delete bullet;
			bullet = nullptr;
		}
	}
	
	Hit();

	if ((x + stage->GetScrollX() < -IMAGE_SIZE) || (x + stage->GetScrollX() > 1280 + IMAGE_SIZE))		//��ʊO�ɏo��ƃA�C�h����Ԃɂ���

	{
		state = ENEMY_STATE::IDOL;
	}
	else if (state == ENEMY_STATE::IDOL)	//��ʓ��ɂ��āA�A�C�h����Ԃ̂Ƃ��G�̕����������悤�ɂ���
	{
		state = ENEMY_STATE::MOVE;
	}
	else
	{ }
}

void LEMON::Move()
{
	y += 5;
}

void LEMON::Hit()
{
	ThrowSlime throw_slime;

	float bx1, by1, bx2, by2;
	float gx1, gy1, gx2, gy2;
	//�v���C���[���������̈ꕔ�Ƃ̓����蔻��
	for (int i = 0; i < player->GetThrowCnt(); i++)
	{
		throw_slime = player->GetThrowSlime(i);
		//�X���C���̃{�[���̓����蔻��
		bx1 = throw_slime.GetThrowX();
		by1 = throw_slime.GetThrowY();
		bx2 = throw_slime.GetThrowX() + BALL_W;
		by2 = throw_slime.GetThrowY() - BALL_H;
		//�O���[�v�t���[�c�̓����蔻��
		gx1 = x;
		gy1 = y;
		gx2 = gx1 + IMAGE_SIZE;
		gy2 = gy1 + IMAGE_SIZE;
		if (((bx2 >= gx1 && bx2 <= gx2) || (bx1 <= gx2 && bx1 >= gx1)) && ((by1 >= gy2 && by1 <= gy1) || (by2 >= gy1 && by2 <= gy2)))
		{
			rad = 90 * (PI / 180);
			state = ENEMY_STATE::FALL;
		}
	}

	//�n�ʂ�u���b�N�Ƃ̓����蔻��
	if (state == ENEMY_STATE::FALL)
	{
		if (stage->HitMapDat(map_y + 1,map_x))
		{
			state = ENEMY_STATE::DETH;
			animation_timer = 0;
		}
	}
}

bool LEMON::ReturnAnimation()
{
	bool ret = false;
	if (++animation_timer < 120) //120�t���[���ԃA�j���[�V����������
	{
	}
	else //�A�j���[�V�����̏I��
	{
		ret = true;
	}
	return ret;
}

void LEMON::Draw() const
{
	DrawRotaGraph2(x + stage->GetScrollX(), y, 40, 0, 1, rad + (-90 * (PI / 180)), image[0], TRUE);
	if (bullet != nullptr)		//�e�����݂���Ƃ��e��`�悷��
	{
		bullet->Draw();
	}
}