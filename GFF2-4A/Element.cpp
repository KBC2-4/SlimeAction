
#include "Element.h"

ELEMENT::ELEMENT() {
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			ELEMENT_DATA data = { j * MAP_CEllSIZE + MAP_CEllSIZE / 2, i * MAP_CEllSIZE + MAP_CEllSIZE / 2 };
			if (map_data[i][j] == 70)hook.push_back(data);

		}
	}
}

