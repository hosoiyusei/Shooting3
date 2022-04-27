#include "Grid.h"

// コンストラクタ
Grid::Grid()
	: m_dis(10.0f)
{
}

Grid::~Grid()
{

}

// 更新
void Grid::Update()
{
	// マウスのフォイールでカメラの距離を調整する
	float dis = m_dis;
	dis -= (float)GetMouseWheelRotVol();
	if (dis < 10.0f) dis = 10.0f;
	if (dis > 50.0f) dis = 50.0f;
	m_dis = dis;
}

// 描画
void Grid::Draw()
{
	// nearクリップとfarクリップの設定
	SetCameraNearFar(1.0f, 100.0f);

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(VGet(0.0f, 0.0f, -m_dis), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}