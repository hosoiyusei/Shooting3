#include"Enemy_0.h"
#include"../../Player/Player.h"
#include<math.h>
#include"../../Stage/Stage.h"
#include"../../BulletManager/BulletType.h"
#include"../../BulletManager/BulletManager.h"
#include"../../Effect/Effect.h"
#include"../../Grid/Grid.h"

Enemy_0::Enemy_0()
	:mPos()
	, mSetPos()
	, mpPlayer(nullptr)
	, mSize(0.0f)
	, mAngle(0.0f)
	, mX(0.0f)
	, mY(0.0f)
	, mX2(0.0f)
	, mY2(0.0f)
	, mX3(0.0f)
	, mY3(0.0f)
	, mX4(0.0f)
	, mY4(0.0f)
	, mEnemySpeed(0.04f)
	, mpStage(nullptr)
	, mCollision()
	, mShotInterval(100)
	, mShotTimer(0)
	, mpBulletManager(nullptr)
	, mActive(true)
	, mHp(5)
	, mpEffect(nullptr)
	, mCollisionPos()
	, mpGrid(nullptr)
	, mDeleteFlag(false)
	, mDeleteTimer(0)
	, mHitFlag(false)
	, mHitTimer(0)
	, mHitTimer_2(0)
{

}

Enemy_0::~Enemy_0()
{

}

void Enemy_0::Initialize(Player* pPlayer, Stage* pStage, BulletManager* pBulletManager, Effect* pEffect, Grid* pGrid, float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mpPlayer = pPlayer;
	mpStage = pStage;
	mpBulletManager = pBulletManager;
	mpEffect = pEffect;
	mpGrid = pGrid;

	mSetPos.mX = mpStage->GetPos().mX;
	mSetPos.mY = mpStage->GetPos().mY;

	mCollisionPos = ConvWorldPosToScreenPos(mPos);

	//“–‚½‚è”»’è‚Ì‰Šú‰»
	mCollision.mRadius = 40.0f - (mpGrid->Size() / 3);
	mCollision.mPos.mX = mCollisionPos.x;
	mCollision.mPos.mY = mCollisionPos.y;
}

void Enemy_0::Update()
{
	SetAngle();

	if (mSize < 2.2f)
		mSize += 0.015f;

	mPos.x += mX4;
	mPos.y += mY4;

	mCollisionPos = ConvWorldPosToScreenPos(VGet(
		mPos.x - (mSetPos.mX - mpStage->GetPos().mX),
		mPos.y - (mSetPos.mY - mpStage->GetPos().mY),
		-0.1f
	));

	if (mHitFlag == true)
	{
		++mHitTimer %= 5;
		mHitTimer_2++;
	}

	if (mHitTimer_2 > 30)
	{
		mHitFlag = false;
		mHitTimer = 0;
		mHitTimer_2 = 0;
	}

	if (mActive == true)
	{
		Move();
		Shot();
		mCollision.mRadius = 40.0f - (mpGrid->Size() / 1.5f);
		mCollision.mPos.mX = mCollisionPos.x;
		mCollision.mPos.mY = mCollisionPos.y;
	}
	else
	{
		mCollision.mRadius = 0.0f;
		mCollision.mPos.mX = -3000;
		mCollision.mPos.mY = -3000;
	}
}

void Enemy_0::Draw()
{
	if (mActive == true)
	{
		if (mHitTimer == 0)
		DrawTriangle3D(
			VGet(
				(mPos.x + mX) - (mSetPos.mX - mpStage->GetPos().mX),
				(mPos.y + mY) - (mSetPos.mY - mpStage->GetPos().mY),
				-0.1f),
			VGet(
				(mPos.x + mX2) - (mSetPos.mX - mpStage->GetPos().mX),
				(mPos.y + mY2) - (mSetPos.mY - mpStage->GetPos().mY),
				-0.1f),
			VGet(
				(mPos.x + mX3) - (mSetPos.mX - mpStage->GetPos().mX),
				(mPos.y + mY3) - (mSetPos.mY - mpStage->GetPos().mY),
				-0.1f),
			GetColor(255, 0, 0), TRUE);
	}
}

void Enemy_0::Finalize()
{

}

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

void Enemy_0::SetAngle()
{
	mAngle = atan2f(
		0.0f - mPos.y + (mSetPos.mY - mpStage->GetPos().mY),
		0.0f - mPos.x + (mSetPos.mX - mpStage->GetPos().mX));
	
	mX = mSize * static_cast<float>(cos(mAngle));
	mY = mSize * static_cast<float>(sin(mAngle));

	mAngle = atan2f((mPos.y + mY) - mPos.y, (mPos.x + mX) - mPos.x);

	mX2 = -mSize * static_cast<float>(cos(mAngle-1.0f));
	mY2 = -mSize * static_cast<float>(sin(mAngle-1.0f));

	mAngle = atan2f((mPos.y + mY) - mPos.y, (mPos.x + mX) - mPos.x);

	mX3 = -mSize * static_cast<float>(cos(mAngle+1.0f));
	mY3 = -mSize * static_cast<float>(sin(mAngle+1.0f));
}

void Enemy_0::Move()
{
	float Angle = atan2f(
		0.0f - mPos.y + (mSetPos.mY - mpStage->GetPos().mY),
		0.0f - mPos.x + (mSetPos.mX - mpStage->GetPos().mX));
	mX4 = mEnemySpeed * static_cast<float>(cos(Angle));
	mY4 = mEnemySpeed * static_cast<float>(sin(Angle));
}

void Enemy_0::Shot()
{
	++mShotTimer %= mShotInterval;
	if (mShotTimer == 0)
	{
		if (mpBulletManager != nullptr)
			mpBulletManager->Shot_2(
				mPos.x - (mSetPos.mX - mpStage->GetPos().mX),
				mPos.y - (mSetPos.mY - mpStage->GetPos().mY),
				(mPos.x + mX) - (mSetPos.mX - mpStage->GetPos().mX),
				(mPos.y + mY) - (mSetPos.mY - mpStage->GetPos().mY),
				0.0f, 0.0f,
				BULLET_TYPE::TYPE_ENEMY);
	}
}

void Enemy_0::IsDamage()
{
	mHp--;
	mHitFlag = true;
	if (mHp < 1 && mActive == true)
	{
		mActive = false;
		mpEffect->Play(
			mPos.x - (mSetPos.mX - mpStage->GetPos().mX),
			mPos.y - (mSetPos.mY - mpStage->GetPos().mY),
			EFFECT_NUM::EFFECT_3
		);
	}		
}