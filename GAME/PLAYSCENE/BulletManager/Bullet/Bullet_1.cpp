#include"Bullet_1.h"
#include<math.h>
#include"../../Stage/Stage.h"

Bullet_1::Bullet_1()
	:mShooterPos()
	, mSpeed(0.2f)
	, mAngle(0.0f)
	, mX(0.0f)
	, mY(0.0f)
	, mX2(0.0f)
	, mY2(0.0f)
	, mpStage(nullptr)
	, mSetPos()
	, mShotPos()
	, mSize(11.0f)
	, mCollision()
	, mCollisionPos()
	, mPos()
{

}

Bullet_1::~Bullet_1()
{

}

void Bullet_1::Initialize(Stage* pStage,
	float ShooterPosX,
	float ShooterPosY,
	float ShotPosX,
	float ShotPosY,
	float TargetPosX,
	float TargetPosY,
	BULLET_TYPE type)
{
	mType = BULLET_TYPE::TYPE_ENEMY;

	mpStage = pStage;

	mSetPos.mX = mpStage->GetPos().mX;
	mSetPos.mY = mpStage->GetPos().mY;

	mShooterPos.x = ShooterPosX;
	mShooterPos.y = ShooterPosY;
	mShooterPos.z = 0.0f;

	mAngle = atan2f(mY - mShooterPos.y, mX - mShooterPos.x);
	
	
	mX2 = mSpeed * static_cast<float>(cos(mAngle));
	mY2 = mSpeed * static_cast<float>(sin(mAngle));

	mShotPos.x = ShotPosX;
	mShotPos.y = ShotPosY;

	mCollision.mRadius = 3.0f;
}

void Bullet_1::Update()
{
	mShotPos.x += mX2;
	mShotPos.y += mY2;

	if (mSize > 5)
		mSize--;

	mCollisionPos = ConvWorldPosToScreenPos(
		VGet(
			mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX),
			mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY),
			mPos.z
		));

	mCollision.mPos.mX = mCollisionPos.x;
	mCollision.mPos.mY = mCollisionPos.y;
}
void Bullet_1::Draw()
{
	DrawSphere3D(
		VGet(
			mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX),
			mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY),
			mShotPos.z
		),
		mSize * 0.1f,//”¼Œa‚Ì‘å‚«‚³
		16,//ƒ|ƒŠƒSƒ“‚Ì×‚©‚³
		GetColor(255, 255, 0),//Šî–{‚ÌF
		GetColor(255, 255, 0),//–¾‚©‚è‚ÌF
		TRUE);
}

void Bullet_1::Finalize()
{

}

float Bullet_1::GetPosX()
{
	return mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX);
}

float Bullet_1::GetPosY()
{
	return mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY);
}