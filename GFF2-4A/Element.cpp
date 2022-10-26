
#include "Element.h"

ELEMENT::ELEMENT() {
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map_data[i][j])
			{
			case 70:
				ELEMENT_DATA data = { j * MAP_CEllSIZE + MAP_CEllSIZE / 2, i * MAP_CEllSIZE + MAP_CEllSIZE / 2 };
				hook.push_back(data);
				break;

			case 61:
				ELEMENT_DATA data = { (j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25, i * MAP_CEllSIZE + MAP_CEllSIZE / 2 ,1 };
				button.push_back(data);
				break;

			case 62:
				ELEMENT_DATA data = { (j * MAP_CEllSIZE + MAP_CEllSIZE / 2), (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25 ,2 };
				button.push_back(data);
				break;

			case 63:
				ELEMENT_DATA data = { (j * MAP_CEllSIZE + MAP_CEllSIZE / 2), (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25 ,3 };
				button.push_back(data);
				break;

			case 64:
				ELEMENT_DATA data = { j * MAP_CEllSIZE + MAP_CEllSIZE / 2, i * MAP_CEllSIZE + MAP_CEllSIZE / 2 };
				door.push_back(data);
				break;


			default:
				break;
			}

		}
			
	}
}


void ELEMENT::Button() {
	for (int i = 0; i < button.size(); i++) {
		if (button[i].type == 1) {
			
		}
		if (button[i].type == 2) {

		}

		if (button[i].type == 3) {
			if (button[i].flg == false) {

			}
		}
	}
}