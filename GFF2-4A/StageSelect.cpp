#include "StageSelect.h"
#include "Title.h"
#include "DxLib.h"

STAGE_SELECT::STAGE_SELECT()
{
	//background_image[0] = LoadGraph("Resource/Images/Stage/BackImpause_cash.bmp");
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	player = new PLAYER;
	stage = new STAGE("StageSelect");
	element = new ELEMENT();

	int scrollx = -(1460 - 500);
	stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
	player->SetPlayerX(80); //�v���C���[�̉�ʓ����W���Z�b�g

	player_map_x = 0;
	player_map_y = 0;

}

STAGE_SELECT::~STAGE_SELECT()
{
	DeleteGraph(background_image[0]);
	delete player;
	delete stage;
	delete element;
}

AbstractScene* STAGE_SELECT::Update()
{

	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY());
	
	player->Update(element, stage);
	stage->Update(player, element);
	element->Update(player,stage);
	
	//�������烊�X�^�[�g
	if (player->IsDeath() == true) {
		return new STAGE_SELECT();
	}

	if ((player_map_x >= 20 * MAP_CEllSIZE  - MAP_CEllSIZE / 2) && (player_map_x <= 20 * MAP_CEllSIZE + MAP_CEllSIZE / 2)) {
		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { return new Title(); }
	}
	return this;
}

void STAGE_SELECT::Draw() const
{
	//�X�e�[�W�w�i
	DrawGraph(static_cast<int>(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(static_cast<int>(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw();
	stage->Draw();

	//�v���C���[�̕`��
	player->Draw(stage);
}