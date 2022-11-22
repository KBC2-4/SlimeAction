#include "StageSelect.h"
#include "DxLib.h"

STAGE_SELECT::STAGE_SELECT()
{
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	player = new PLAYER;
	stage = new STAGE;
	element = new ELEMENT();

	int scrollx = -(1460 - 500);
	stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
	player->SetPlayerX(80); //�v���C���[�̉�ʓ����W���Z�b�g
}

STAGE_SELECT::~STAGE_SELECT()
{
	delete player;
	delete stage;
	delete element;
}

AbstractScene* STAGE_SELECT::Update()
{
	DeleteGraph(background_image[0]);
	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player,stage);
	
	//�������烊�X�^�[�g
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}

	return this;
}

void STAGE_SELECT::Draw() const
{
	//�X�e�[�W�w�i
	DrawGraph(int(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw();
	stage->Draw();

	//�v���C���[�̕`��
	player->Draw(stage);
}