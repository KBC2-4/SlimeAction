#pragma once
class RANKING
{
private:
	RANKING();
public:

	static void Insert(int time, int stage);

	static void SortRanking();		//�����L���O���בւ�
	static void SaveRanking();		//�����L���O�f�[�^�̕ۑ�
	static int ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
};

