#pragma once
class RANKING
{
private:
	static int best_time[3];
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
	static void ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
};

