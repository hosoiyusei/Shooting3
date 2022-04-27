#pragma once
#include"../../Utility.h"
#include"DrawBox.h"

class Player;

class Stage
{
private:

	Float2 mPos;

	const int mSize;

	const float mSpeed;

	float mLeft, mRight, mTop, mBottom;

	Player* mpPlayer;

	DrawBox3D mDrawBox3D;

public:

	Stage();
	~Stage();

	void Initialize(Player* pPlayer);

	void Update();

	void Draw();

	void Finalize();

	Float2 GetPos()
	{
		return mPos;
	}

	float LEFT()
	{
		return mLeft;
	}

	float RIGHT()
	{
		return mRight;
	}

	float TOP()
	{
		return mTop;
	}

	float BOTTOM()
	{
		return mBottom;
	}

private:

	void Move();
};