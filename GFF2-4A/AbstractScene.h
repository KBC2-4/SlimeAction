#pragma once

class AbstractScene
{
public:
	//�R���X�g���N�^
	AbstractScene();
	// CommonProcess�����s���Ȃ��悤�ɂ�������L��̋�R���X�g���N�^
	AbstractScene(bool not_initialized) {};
	//�f�X�g���N�^
	virtual ~AbstractScene() {};
	//�`��ȊO�̍X�V�����s
	virtual AbstractScene* Update() = 0;
	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const = 0;

	/// <summary>
	/// �S�V�[�����ʂ̃R���X�g���N�^�ōs������
	/// </summary>
	void CommonProcess();

	/// <summary>
	/// �����̕`�悷��X���W�����S�ɂȂ�X���W���擾����B
	/// </summary>
	/// <param name="string">�`�悷�镶����</param>
	/// <param name="font_handle">�`��Ɏg�p����t�H���g�n���h��(�����͖���0�̏ꍇ�̓f�t�H���g�t�H���g�n���h�����g�p</param>
	/// <param name="margin">������X���W�ɊԊu���󂯂�l</param>
	int GetDrawCenterX(const char* string, int font_handle = 0, int margin = 0)const;
};