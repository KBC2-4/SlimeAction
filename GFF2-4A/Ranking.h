#pragma once
class RANKING
{
private:
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SaveRanking(int best_time);		//�����L���O�f�[�^�̕ۑ�
	static int ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
};

