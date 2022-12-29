#include"DxLib.h"
#include "GrapeFruit.h"
#include<math.h>
#define _USE_MATH_DEFINES
#include <vector>
#include"Option.h"

//�R���X�g���N�^

GRAPEFRUIT::GRAPEFRUIT()
{
	image = new int[100];
	if (image[0] = LoadGraph("Resource/Images/Enemy/gurepon.png") == -1)
		throw "Resource/Images/Enemy/gurepon.png";
	shootcount = 0;
	delete_flg = false;
	rad = 0.0;
	for (int i = 0; i < 3; i++)
	{
		flag[i] = false;
	}
	x = 0;
	spawn_map_x = 0;
	spawn_map_y = 0;
	target_x = 200;
	animation_timer = 0;
	animation_type = 0;
	for (int i = 0; i < 2; i++)
	{
		face_image[i] = 0;
		fruit_image[i] = 0;
	}
	for (int i = 0; i < 3; i++) {
		bullet[i] = nullptr;
	}
	damage_se = 0;
	bullet_count = 3;
}

//�����t�̃R���X�g���N�^

GRAPEFRUIT::GRAPEFRUIT(PLAYER* player, STAGE* stage, int spawn_y, int spawn_x)
{
	spawn_map_x = spawn_x;
	spawn_map_y = spawn_y;
	x = (spawn_map_x * MAP_CEllSIZE + MAP_CEllSIZE / 2);
	y = (spawn_map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2) - 40;
	for (int i = 0; i < 3; i++)
	{
		flag[i] = false;
	}
	delete_flg = false;
	image = new int[24];
	if (LoadDivGraph("Resource/Images/Enemy/gurepon.png", 24, 6, 4, 80, 80, image) == -1)
	{
		throw "Resource/Images/Enemy/gurepon.png";
	}
	if ((damage_se = LoadSoundMem("Resource/Sounds/SE/Enemy/damage.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/damage.wav";
	}
	if ((press_se = LoadSoundMem("Resource/Sounds/SE/Enemy/press.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/press.wav";
	}
	if ((splash_se = LoadSoundMem("Resource/Sounds/SE/Enemy/splash.wav")) == -1) {
		throw "Resource/Sounds/SE/Enemy/splash.wav";
	}
	shootcount = 0;
	target_x = 200;

	for (int i = 0; i < 2; i++)
	{
		face_image[i] = image[i];
		fruit_image[i] = image[(i + 1) * 6];
	}
	for (int i = 0; i < 3; i++)
	{
		bullet[i] = nullptr;
	}
	this->player = player;
	this->stage = stage;
	bullet_count = 3;

	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 1.2), damage_se);
	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 0.9), press_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), splash_se);

}

GRAPEFRUIT::~GRAPEFRUIT()
{

	for (int i = 0; i < 24; i++) {
		DeleteGraph(image[i]);
	}

	delete[] image;

	for (int i = 0; i < 3; i++)
	{
		delete bullet[i];
	}

	DeleteSoundMem(damage_se);
	DeleteSoundMem(press_se);
	DeleteSoundMem(splash_se);

}
//�A�b�v�f�[�g
void GRAPEFRUIT::Update()
{

	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 1.2), damage_se);
	ChangeVolumeSoundMem(static_cast<int>(Option::GetSEVolume() * 0.9), press_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), splash_se);

	//�A�j���[�V�����̎��Ԃ����Z
	if (animation_timer < 80) {
		++animation_timer;
	}

	//�����̃X�e�[�g
	switch (state)
	{
		//�ҋ@���
	case ENEMY_STATE::IDOL:
		break;

		//�����Ă���
	case ENEMY_STATE::MOVE:
		ChangeAngle();
		if ((x + stage->GetScrollX() > 0) && (x + stage->GetScrollX() < 1280))
		{
			if (player->GetMapY() > map_y)
			{

				if (++shootcount % 90 == 0)
				{
					animation_timer = 0;
					state = ENEMY_STATE::PRESS;
				}
			}
		}
		break;

		//�A�j���[�V���������Z�b�g����
	case ENEMY_STATE::RETURN:
		ChangeAngle();
		if (ReturnAnimation())
		{
			animation_timer = 0;
			animation_type = 0;
			state = ENEMY_STATE::MOVE;
		}
		break;

		//�e������
	case ENEMY_STATE::PRESS:
		ChangeAngle();
		if (PressAnimation())
		{
			for (int i = 0; i < 3; i++)
			{
				if (flag[i] == false)
				{
					bullet[i] = new ENEMY_BULLET(player, stage, x, y, i * 100.0, rad, 0);
					flag[i] = true;
				}
			}
			animation_timer = 0;
			animation_type = 0;
			state = ENEMY_STATE::RETURN;
			PlaySoundMem(press_se, DX_PLAYTYPE_BACK);
		}
		break;

		//�����鎞
	case ENEMY_STATE::FALL:
		Move();
		FallAnimation();
		break;

		//��
	case ENEMY_STATE::DETH:
		if (DethAnimation())
		{
			delete_flg = true;
		}
		break;
	default:
		break;
	}

	//�}�b�v��̍��W�̐ݒ�
	map_x = x / MAP_CEllSIZE;
	map_y = (y - IMAGE_SIZE / 2) / MAP_CEllSIZE;

	//�e�����݂��Ă���Ƃ��ɒe�̏������s��
	for (int i = 0; i < 3; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Update();
			if (bullet[i]->GetDeleteFlg())
			{
				delete bullet[i];
				bullet[i] = nullptr;
				flag[i] = false;
			}
		}
	}

	//�����蔻��
	Hit();

	//��ʓ��ɂ��邩�ǂ���
	if (((x + stage->GetScrollX() < -IMAGE_SIZE) || (x + stage->GetScrollX() > 1280 + IMAGE_SIZE) || (y + stage->GetScrollY() < 0) 
		|| (y + stage->GetScrollY() > 720)) && (state != ENEMY_STATE::FALL && state != ENEMY_STATE::DETH))		//��ʊO�ɏo��ƃA�C�h����Ԃɂ���
	{
		state = ENEMY_STATE::IDOL;		//�X�e�[�g���A�C�h����Ԃ�
		//�A�C�h����Ԃ̉摜�ɕύX
		for (int i = 0; i < 2; i++)
		{
			face_image[i] = image[i];
			fruit_image[i] = image[(i + 1) * 6];
		}
	}
	else if (state == ENEMY_STATE::IDOL)	//��ʓ��ɂ��āA�A�C�h����Ԃ̂Ƃ��G�̕����������悤�ɂ���
	{
		//�A�j���[�V�������Ԃ����Z�b�g���A�X�e�[�g�����[�u��
		animation_timer = 0;
		state = ENEMY_STATE::MOVE;
	}
	else {}
}

//�������Ƃ��̓���
void GRAPEFRUIT::Move()
{
	//���֗�����
	y += 10;
	//�e�̃t���O��FALSE��
	for (int i = 0; i < 3; i++)
	{
		if (flag[i])
		{
			flag[i] = false;
		}
	}

}

//�����蔻��

void GRAPEFRUIT::Hit()
{
	//�Ă΂ꂽ���ɃX���C���̃N���X�ϐ����쐬
	ThrowSlime throw_slime;

	float bx1, by1, bx2, by2;
	float gx1, gy1, gx2, gy2;
	//�v���C���[���������̈ꕔ�Ƃ̓����蔻��
	if ((state != ENEMY_STATE::FALL) && (state != ENEMY_STATE::DETH))
	{
		for (int i = 0; i < player->GetThrowCnt(); i++)
		{
			throw_slime = player->GetThrowSlime(i);
			//�X���C���̃{�[���̓����蔻��
			bx1 = throw_slime.GetThrowX();
			by1 = throw_slime.GetThrowY();
			bx2 = throw_slime.GetThrowX() + BALL_W;
			by2 = throw_slime.GetThrowY() - BALL_H;
			//�O���[�v�t���[�c�̓����蔻��
			gx1 = x - IMAGE_SIZE / 2;
			gy1 = y - IMAGE_SIZE / 2;
			gx2 = gx1 + IMAGE_SIZE;
			gy2 = gy1 + IMAGE_SIZE;
			if (((bx2 >= gx1 && bx2 <= gx2) || (bx1 <= gx2 && bx1 >= gx1)) && ((by1 >= gy2 && by1 <= gy1) || (by2 >= gy1 && by2 <= gy2)))
			{
				rad = 90 * (PI / 180);
				state = ENEMY_STATE::FALL;
				PlaySoundMem(damage_se, DX_PLAYTYPE_BACK);

			}
		}
	}

	//�n�ʂ�u���b�N�Ƃ̓����蔻��
	if (state == ENEMY_STATE::FALL)
	{
		if (stage->HitMapDat(map_y + 1, map_x))
		{
			state = ENEMY_STATE::DETH;
			animation_timer = 0;
			animation_type = 0;
			PlaySoundMem(splash_se, DX_PLAYTYPE_BACK);
		}
	}
}

//�e�����Ƃ��̂Ԃ��A�j���[�V����
bool GRAPEFRUIT::PressAnimation()
{

	bool ret = false;
	if (animation_timer < 40) //30�t���[���ԃA�j���[�V����������
	{
		if (animation_timer % (ANIMATION_TIME * 2) == 0)
		{
			animation_type++;

			for (int i = 0; i < 2; i++)
			{
				face_image[i] = image[i];
				if (animation_type % 3 == 0)
				{
					fruit_image[i] = image[(6 * (i + 2) - 1)];
				}
				else
				{
					fruit_image[i] = image[((animation_type % 3) * 2) + (6 * (i + 1))];
				}
			}

		}
	}
	else //�A�j���[�V�����̏I��
	{
		ret = true;
	}
	return ret;
}

//�Ԃꂽ��Ԃ��猳�̏�Ԃɖ߂��A�j���[�V����
bool GRAPEFRUIT::ReturnAnimation()
{
	bool ret = false;
	if (animation_timer < 40) //30�t���[���ԃA�j���[�V����������
	{
		if (animation_timer % (ANIMATION_TIME * 2) == 0)
		{
			animation_type++;

			for (int i = 0; i < 2; i++)
			{
				face_image[i] = image[i];
				if (animation_type % 3 == 0)
				{
					fruit_image[i] = image[(i + 1) * 6];
				}
				else
				{
					fruit_image[i] = image[(6 * (i + 2) - 1) - (animation_type % 6)];
				}
			}
		}
	}
	else //�A�j���[�V�����̏I��
	{
		for (int i = 0; i < 2; i++)
		{
			face_image[i] = image[i];
			fruit_image[i] = image[(i + 1) * 6];
		}
		ret = true;
	}
	return ret;
}


//������A�j���[�V����
void GRAPEFRUIT::FallAnimation()
{
	if (animation_timer % ANIMATION_TIME == 0)
	{
		if (animation_timer % (ANIMATION_TIME * 2) == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				face_image[i] = image[(2 + (animation_type % 2) +  (i  * 2))];
				fruit_image[i] = image[(i + 1) * 6];
			}
			animation_type++;
		}
	}
}

//���ʃA�j���[�V����
bool GRAPEFRUIT::DethAnimation()
{
	bool ret = false;
	if (animation_timer < 30) //30�t���[���ԃA�j���[�V����������
	{
		//�A�j���[�V����
		if (animation_timer % ANIMATION_TIME == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				face_image[i] = 0;
			}
			fruit_image[0] = image[(animation_type % 6) + (6 * 3)];
			fruit_image[1] = 0;
			animation_type++;
		}
	}
	else //�A�j���[�V�����̏I��
	{
		ret = true;
	}
	return ret;
}

//�`��
void GRAPEFRUIT::Draw() const
{
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraphF(x + stage->GetScrollX(), (y + 5 * i) + stage->GetScrollY(), 1, rad + (-90 * (PI / 180)), fruit_image[i], TRUE);
		DrawRotaGraphF(x + stage->GetScrollX(), (y + 5 * i) + stage->GetScrollY(), 1, rad + (-90 * (PI / 180)), face_image[i], TRUE);
	}

	if (flag)
	{
		for (int i = 0; i < bullet_count; i++)
		{
			if (bullet[i] != nullptr)
			{
				bullet[i]->Draw();
			}
		}
	}
}

//X���W���Q�b�g����
int GRAPEFRUIT::GetX()
{
	return x;
}

