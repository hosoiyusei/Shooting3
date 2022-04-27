#pragma once
#include"Bullet.h"

class Bullet_1 :public Bullet
{
private:

	VECTOR mShooterPos;

	VECTOR mShotPos;

	Float2 mSetPos;

	VECTOR mCollisionPos;

	VECTOR mPos;

	CircleCollider mCollision;

	BULLET_TYPE mType;

	float mSpeed;

	float mAngle;

	float mX, mY, mX2, mY2;

	float mSize;

	Stage* mpStage;

public:

	Bullet_1();
	~Bullet_1();

	void Initialize(Stage* pStage,
		float ShooterPosX,
		float ShooterPosY,
		float ShotPosX,
		float ShotPosY,
		float TargetPosX,
		float TargetPosY,
		BULLET_TYPE type) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	float GetPosX() override;
	float GetPosY() override;

	BULLET_TYPE TYPE() override
	{
		return mType;
	}

	CircleCollider Collision() override
	{
		return mCollision;
	}
};