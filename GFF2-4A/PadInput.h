#pragma once
#include"DxLib.h"

#define BUTTONS 16

enum class PADSTATE
{
	NOT = 0,
	ON,
	DOWN
};

class PAD_INPUT
{
private:
	static int NowKey;
	static int OldKey;
	static PADSTATE state;
	static XINPUT_STATE Input;
	PAD_INPUT();
public:
	static void UpdateKey();
	static int GetPadThumbLX(){ return Input.ThumbLX; }
	static int GetPadThumbLY() { return Input.ThumbLY; }
	static int GetNowKey() { return NowKey; }
	static int GetOldKey() { return OldKey; }
	static int GetPadState() { return static_cast<int>(state); }
};

