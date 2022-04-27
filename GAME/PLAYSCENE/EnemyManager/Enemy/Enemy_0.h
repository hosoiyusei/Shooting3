#pragma once
#include"Enemy.h"

class Enemy_0 :public Enemy
{
private:

	Float2 mSetPos;

	VECTOR mPos;

	VECTOR mCollisionPos;

	CircleCollider mCollision;

	float mAngle;

	float mSize;

	const float mEnemySpeed;

	float mX, mY, mX2, mY2, mX3, mY3, mX4, mY4;

	const int mShotInterval;

	int mShotTimer;

	bool mActive;

	int mHp;

	int mDeleteTimer;

	bool mDeleteFlag;

	int mHitTimer, mHitTimer_2;

	bool mHitFlag;

	Player* mpPlayer;

	Stage* mpStage;

	BulletManager* mpBulletManager;

	Effect* mpEffect;

	Grid* mpGrid;

public:

	Enemy_0();
	~Enemy_0();

	void Initialize(Player* pPlayer, Stage* pStage, BulletManager* pBulletManager,Effect* pEffect,Grid* pGrid, float x,float y) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void IsDamage() override;

	bool Active() override
	{
		return mActive;
	}

	VECTOR GetPos() override
	{
		return mPos;
	}

	CircleCollider Collision() override
	{
		return mCollision;
	}

	int DeleteTimer() override
	{
		return mDeleteTimer;
	}

private:

	void SetAngle();

	void Move();

	void Shot();
};