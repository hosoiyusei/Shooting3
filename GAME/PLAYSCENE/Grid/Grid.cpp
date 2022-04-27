#include "Grid.h"

// �R���X�g���N�^
Grid::Grid()
	: m_dis(10.0f)
{
}

Grid::~Grid()
{

}

// �X�V
void Grid::Update()
{
	// �}�E�X�̃t�H�C�[���ŃJ�����̋����𒲐�����
	float dis = m_dis;
	dis -= (float)GetMouseWheelRotVol();
	if (dis < 10.0f) dis = 10.0f;
	if (dis > 50.0f) dis = 50.0f;
	m_dis = dis;
}

// �`��
void Grid::Draw()
{
	// near�N���b�v��far�N���b�v�̐ݒ�
	SetCameraNearFar(1.0f, 100.0f);

	// �J�����̐ݒ�
	SetCameraPositionAndTargetAndUpVec(VGet(0.0f, 0.0f, -m_dis), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}