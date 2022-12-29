#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"
#include "Lemon.h"

class STAGE_SELECT :
	public AbstractScene
{
private:
	//�w�i�摜
	int background_image[5];
	//BGM
	int background_music;

	int ok_se;
	//�t�H���g
	int guid_font, buttonguid_font, stagename_font, move_to_title_font;
	int guid_timer;		//�K�C�h�\���^�C�}�[
	bool effect_delta;
	int effect_timer[2];	//[0:�o���G�t�F�N�g, 1:�X�e�[�W�|�[�^���G�t�F�N�g]

	//�`���[�g���A���p
	int joys_anitimer;
	bool joystick_delta;

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	ELEMENT* element;	//�X�e�[�W���v�f
	LEMON** lemoner;	//�����i�[
	int lemoner_count;

	float player_map_x, player_map_y;	//�v���C���[�}�b�v�����W�v�Z�p
	POINT stage_return;		//�^�C�g���֖߂���W
	POINT stage_move[4];	//�X�e�[�W�|�[�^�����W

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	STAGE_SELECT();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~STAGE_SELECT();
	/// <summary>
	/// �`��ȊO�̍X�V�����s
	/// </summary>
	/// <returns>�V�[���̃A�h���X��Ԃ�</returns>
	AbstractScene* Update() override;
	/// <summary>
	/// �`��Ɋւ��邱�Ƃ�����
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// �X�e�[�W�ɓ��鎞��Update
	/// </summary>
	void StageIn(void);
	/// <summary>
	/// �X�e�[�W�ɓ��鎞�̃A�j���[�V����
	/// </summary>
	void StageIn_Animation(void);
	/// <summary>
	/// �X�e�[�W�|�[�^���K�C�h�\��
	/// </summary>
	/// <param name="stage_name">�\������������</param>
	/// <param name="x">�`��ʒuX</param>
	/// <param name="y">�`��ʒuY</param>
	/// <param name="stagename_font">�\�����镶���̃t�H���g</param>
	/// <param name="text_color">�\�����镶���F</param>
	/// <param name="textback_color">�\�����镶���̗֊s�F (-1�̏ꍇ��0xFFFFFF)</param>
	/// <param name="text_margin_x">�\�����镶��X�ʒu���덷�C�� (�f�t�H���g��0)</param>
	/// <param name="text_margin_y">�\�����镶��Y�ʒu���덷�C�� (�f�t�H���g��0)</param>
	/// <param name="backcolor">�`�悷��ȉ~�̐F (-1�̏ꍇ��0xFFFFFF)</param>
	/// <param name="second_title">2�Ԗڂɕ\�����镶�� (""�󔒂Ŗ�����)</param>
	/// <param name="secont_margin_x">2�Ԗڂɕ\�����镶��X�ʒu���덷�C�� (�f�t�H���g��0)</param>
	/// <param name="secont_margin_y">2�Ԗڂɕ\�����镶��Y�ʒu���덷�C�� (�f�t�H���g��25 : 0�ɂ����stage_name�Əd�Ȃ�)</param>
	void DrawStageGuid(const char* stage_name, const float x, const float y, const int stagename_font, const int text_color, const int textback_color = -1,
		const int text_margin_x = 0, const int text_margin_y = 0, const int backcolor = -1, const char* second_title = "", const int secont_margin_x = 0, const int secont_margin_y = 25) const;
};

