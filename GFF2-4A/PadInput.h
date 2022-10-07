#pragma once
#include"DxLib.h"

#define BUTTONS 16

enum class PAD_STATE
{
	NOT = 0, //������Ă��Ȃ�
	ON,		//�����ꂽ�u��
	DOWN	//������Ă����
};

class PAD_INPUT
{
private:
	static int NowKey;
	static int OldKey;
	static PAD_STATE state;
	static XINPUT_STATE Input;
	PAD_INPUT(); //�R���X�g���N�^
public:
	static void UpdateKey();	//�p�b�h���͂̍X�V
	static int GetPadThumbLX(){ return Input.ThumbLX; }	 //���X�e�B�b�N�̉����l
	static int GetPadThumbLY() { return Input.ThumbLY; }	//���X�e�B�b�N�̏c���l
	static int GetPadThumbRX() { return Input.ThumbRX; }	//�E�X�e�B�b�N�̉����l
	static int GetPadThumbRY() { return Input.ThumbRY; }	//�E�X�e�B�b�N�̏c���l
	static int GetNowKey() { return NowKey; }
	static PAD_STATE GetPadState() { return state; }
};

