#pragma once

// グリッドクラス
class Grid
{
private:

	// グリッドまでのカメラの距離
	float m_dis;

public:

	// コンストラクタ
	Grid();
	~Grid();

	// 更新
	void Update();

	// 描画
	void Draw();

	float Size()
	{
		return m_dis;
	}
};