#pragma once

// �O���b�h�N���X
class Grid
{
private:

	// �O���b�h�܂ł̃J�����̋���
	float m_dis;

public:

	// �R���X�g���N�^
	Grid();
	~Grid();

	// �X�V
	void Update();

	// �`��
	void Draw();

	float Size()
	{
		return m_dis;
	}
};