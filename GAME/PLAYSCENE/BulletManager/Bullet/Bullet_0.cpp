#include"Bullet_0.h"
#include<math.h>
#include"../../Stage/Stage.h"

Bullet_0::Bullet_0()
	:mShooterPos()
	,mSpeed(0.3f)
	, mAngle(0.0f)
	,mX(0.0f)
	,mY(0.0f)
	,mX2(0.0f)
	,mY2(0.0f)
	, mpStage(nullptr)
	, mSetPos()
	, mShotPos()
	,mSize(11.0f)
	, mCollision()
	, mCollisionPos()
{

}

Bullet_0::~Bullet_0()
{

}

void Bullet_0::Initialize(Stage* pStage,
	float ShooterPosX,
	float ShooterPosY,
	float ShotPosX,
	float ShotPosY,
	float TargetPosX,
	float TargetPosY,
	BULLET_TYPE type)
{
	mType = BULLET_TYPE::TYPE_PLAYER;

	mShooterPos.mX = ShooterPosX;
	mShooterPos.mY = ShooterPosY;

	mX = TargetPosX;
	mY = TargetPosY;

	mAngle = atan2f(mY - mShooterPos.mY, mX - mShooterPos.mX);
	
	mX2 = mSpeed * static_cast<float>(cos(mAngle));
	mY2 = mSpeed * static_cast<float>(sin(mAngle));

	mpStage = pStage;

	mSetPos.mX = mpStage->GetPos().mX;
	mSetPos.mY = mpStage->GetPos().mY;

	mShotPos.x = ShotPosX;
	mShotPos.y = ShotPosY;

	mCollisionPos = ConvWorldPosToScreenPos(
		VGet(
			mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX),
			mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY),
			mShotPos.z
		));

	//“–‚½‚è”»’è‚Ì‰Šú‰»
	mCollision.mRadius = 3.5f;
}

void Bullet_0::Update()
{
	mShotPos.x += mX2;
	mShotPos.y -= mY2;

	if (mSize > 5)
		mSize--;

	mCollisionPos = ConvWorldPosToScreenPos(
		VGet(
		mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX),
		mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY),
		mShotPos.z
	));

	mCollision.mPos.mX = mCollisionPos.x;
	mCollision.mPos.mY = mCollisionPos.y;
}
void Bullet_0::Draw()
{
	mShotPos.z = 0.0f;

	DrawSphere3D(
		VGet(
			mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX),
			mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY),
			mShotPos.z
		),
		mSize * 0.1f,//”¼Œa‚Ì‘å‚«‚³
		16,//ƒ|ƒŠƒSƒ“‚Ì×‚©‚³
		GetColor(255, 255, 255),//Šî–{‚ÌF
		GetColor(255, 255, 255),//–¾‚©‚è‚ÌF
		TRUE);
}

void Bullet_0::Finalize()
{

}

float Bullet_0::GetPosX()
{
	return mShotPos.x - (mSetPos.mX - mpStage->GetPos().mX);
}

float Bullet_0::GetPosY()
{
	return mShotPos.y - (mSetPos.mY - mpStage->GetPos().mY);
}