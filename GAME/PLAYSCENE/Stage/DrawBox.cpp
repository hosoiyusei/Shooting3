#include"DrawBox.h"

DrawBox3D::DrawBox3D()
{

}

DrawBox3D::~DrawBox3D()
{

}

void DrawBox3D::Draw(float size, float x, float y)
{
	DrawLine3D(//上
		VGet(static_cast<float>(x - size), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x + size), static_cast<float>(y - size), -0.1f),
		GetColor(0, 100, 0));

	DrawLine3D(//左
		VGet(static_cast<float>(x - size), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x - size), static_cast<float>(y + size), -0.1f),
		GetColor(0, 100, 0));

	DrawLine3D(//右
		VGet(static_cast<float>(x + size-0.01), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x + size-0.01), static_cast<float>(y + size), -0.1f),
		GetColor(0, 100, 0));

	DrawLine3D(//下
		VGet(static_cast<float>(x - size), static_cast<float>(y + size-0.01), -0.1f),
		VGet(static_cast<float>(x + size), static_cast<float>(y + size-0.01), -0.1f),
		GetColor(0, 100, 0));
}

void DrawBox3D::Draw2(float size, float x, float y)
{
	DrawLine3D(//上
		VGet(static_cast<float>(x - size), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x + size), static_cast<float>(y - size), -0.1f),
		GetColor(255, 255, 255));

	DrawLine3D(//左
		VGet(static_cast<float>(x - size), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x - size), static_cast<float>(y + size), -0.1f),
		GetColor(255, 255, 255));

	DrawLine3D(//右
		VGet(static_cast<float>(x + size - 0.01), static_cast<float>(y - size), -0.1f),
		VGet(static_cast<float>(x + size - 0.01), static_cast<float>(y + size), -0.1f),
		GetColor(255, 255, 255));

	DrawLine3D(//下
		VGet(static_cast<float>(x - size), static_cast<float>(y + size - 0.01), -0.1f),
		VGet(static_cast<float>(x + size), static_cast<float>(y + size - 0.01), -0.1f),
		GetColor(255, 255, 255));
}