#include "Ranking.h"
#include "DxLib.h"

#define FILEPATH "Resource/BestTime/BestTime.bin"

int RANKING::best_time[3];
void RANKING::Insert(int time, int stage)
{
	ReadRanking();
	if ((time < best_time[stage - 1]) || (best_time[stage - 1] == NULL))
	{
		best_time[stage - 1] = time;
		SaveRanking();
	}
}

void RANKING::SaveRanking(void) {
	FILE* fp = NULL;

	//�t�@�C���I�[�v��
	if (fopen_s(&fp, FILEPATH, "wb") != 0)
	{
		fopen_s(&fp, FILEPATH, "wb");

		if (fp == NULL)
		{
			throw FILEPATH;
		}

	}

	//�x�X�g�^�C������������
	for (int i = 0; i < 3; i++)
	{
		fwrite(&best_time[i], sizeof(best_time) / sizeof(best_time[0]), 3, fp);
	}
	fclose(fp);
}


void RANKING::ReadRanking(void) {
	FILE* fp = NULL;

	//�t�@�C���I�[�v��
	if (fopen_s(&fp, FILEPATH, "rb") != 0)
	{
		fopen_s(&fp, FILEPATH, "wb");

		if (fp == NULL)
		{
			throw FILEPATH;
		}
	}
	//�x�X�g�^�C����ǂݍ���
	for (int i = 0; i < 3; i++)
	{
		fread(&best_time[i], sizeof(best_time) / sizeof(best_time[0]), 3, fp);
	}
	fclose(fp);
}