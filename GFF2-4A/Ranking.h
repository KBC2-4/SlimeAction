#pragma once
class RANKING
{
private:
	static int best_time[3];
private:
	RANKING();
	/// <summary>
	/// �����L���O�f�[�^�̕ۑ�
	/// </summary>
	static void SaveRanking();
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="stage"></param>
	static void Insert(int time, int stage);
	/// <summary>
	/// �����L���O�f�[�^�ǂݍ���
	/// </summary>
	static void ReadRanking();
	/// <summary>
	/// �x�X�g�^�C���̎擾
	/// </summary>
	/// <param name="n">����</param>
	/// <returns>�x�X�g�^�C���̒l</returns>
	static int GetBestTime(int n) { return best_time[n]; }
};

