#pragma once
#include"../../Utility.h"
#include"../Collision/Collision.h"

class BulletManager;
class Effect;
class Grid;
class SaveData;

class Player
{
private:

	VECTOR mPos;

	CircleCollider mCollision;

	const float mSpeed;

	float mAngle;

	float mX, mY, mX2, mY2, mX3, mY3;

	int mMouseX, mMouseY;

	int mShotTimer;

	float mHp;
	float mHp2;

	bool mActive;

	int mExplosionSE;

	int mHitTimer, mHitTimer_2;

	bool mHitFlag;

	int mRed, mGreen, mBlue;
	int mColorswitch;

	BulletManager* mpBulletManager;

	Effect* mpEffect;

	Grid* mpGrid;

	SaveData* mpSaveData;

public:

	Player();
	~Player();

	void Initialize(BulletManager* pBulletManager,Effect* pEffect,Grid* pGrid,SaveData* pSaveData);

	void Update();

	void Draw();

	void Finalize();

	void IsDamage();

	bool Active()
	{
		return mActive;
	}

	VECTOR GetPos()
	{
		return mPos;
	}

	CircleCollider Collision()
	{
		return mCollision;
	}

private:

	void SetMouseAngle();

	void BulletShot();

	void Rainbow();
};