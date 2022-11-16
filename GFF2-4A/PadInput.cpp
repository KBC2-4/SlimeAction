#include "PadInput.h"


int PAD_INPUT::NowKey = -1;
int PAD_INPUT::OldKey = -1;
PAD_STATE PAD_INPUT::state = PAD_STATE::NOT;
XINPUT_STATE PAD_INPUT::Input;

void PAD_INPUT::UpdateKey()
{
	// ì¸óÕÉLÅ[éÊìæ
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
	OldKey = NowKey;
	for (int i = 0; i < BUTTONS; i++)
	{
		if (Input.Buttons[i])
		{
			NowKey = i;
			break;
		}
		NowKey = -1;
	}
	if (NowKey != -1)
	{
		//âüÇ≥ÇÍÇΩèuä‘
		if (NowKey != OldKey)
		{
			state = PAD_STATE::ON;
		}

		//âüÇ≥ÇÍÇƒÇ¢ÇÈä‘
		if (NowKey == OldKey)
		{
			state = PAD_STATE::DOWN;
		}
	}
	else
	{
		//âüÇ≥ÇÍÇƒÇ¢Ç»Ç¢
		state = PAD_STATE::NOT;
	}
	
}
