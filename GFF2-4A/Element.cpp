
#include "Element.h"

Element::Element() {
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			ELEMENT_DATA data = { j * MAP_CEllSIZE, i * MAP_CEllSIZE };
			if (map_data[i][j] == 70)hook.push_back(data);
		}
	}
}

