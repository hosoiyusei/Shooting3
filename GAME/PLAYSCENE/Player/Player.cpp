#include"Player.h"
#include"../../GameMain.h"
#include<math.h>
#include"../BulletManager/BulletManager.h"
#include"../BulletManager/BulletType.h"
#include"../Effect/Effect.h"
#include"../../Framework/ResourceManager.h"
#include"../Grid/Grid.h"
#include"../../SaveData/SaveData.h"

Player::Player()
	:mPos()
	, mSpeed(1.5f)
	, mAngle(0.0f)
	, mX(0.0f)
	, mY(0.0f)
	, mX2(0.0f)
	, mY2(0.0f)
	, mX3(0.0f)
	, mY3(0.0f)
	, mMouseX(0)
	, mMouseY(0)
	, mpBulletManager(nullptr)
	, mShotTimer(0)
	, mCollision()
	, mHp(100.0f)
	, mActive(true)
	, mpEffect(nullptr)
	, mHp2(100.0f)
	, mExplosionSE(0)
	, mpGrid(nullptr)
	, mHitFlag(false)
	, mHitTimer(0)
	, mHitTimer_2(0)
	, mRed(255)
	, mGreen(0)
	, mBlue(0)
	, mColorswitch(0)
	,mpSaveData(nullptr)
{

}

Player::~Player()
{

}

void Player::Initialize(BulletManager* pBulletManager,Effect* pEffect,Grid* pGrid, SaveData* pSaveData)
{
	mPos.x = 0.0f;
	mPos.y = 0.0f;

	mpBulletManager = pBulletManager;
	mpEffect = pEffect;
	mpGrid = pGrid;
	mpSaveData = pSaveData;

	//当たり判定の初期化
	mCollision.mRadius = 50.0f - (mpGrid->Size() / 2);
	mCollision.mPos.mX = SCREEN_CENTER_X;
	mCollision.mPos.mY = SCREEN_CENTER_Y;
	ResourceManager* pRm = ResourceManager::GetInstance();
	mExplosionSE = pRm->GetResource("Explosion.mp3", TYPE::Audio);
}

void Player::Update()
{
	if (mActive == true)
	{
		GetMousePoint(&mMouseX, &mMouseY);

		SetMouseAngle();

		BulletShot();
	}
	if (mHp2 > mHp)
		mHp2 -= 0.2f;
	if (mHp2 <= 0.0f)
		mHp2 = 0.0f;
	mCollision.mRadius = 25.0f - (mpGrid->Size() / 3);

	if (mHitFlag == true)
	{
		++mHitTimer %= 5;
		mHitTimer_2++;
	}

	if (mHitTimer_2 > 50)
	{
		mHitFlag = false;
		mHitTimer = 0;
		mHitTimer_2 = 0;
	}
	if (mHp == 100.0f)
		Rainbow();
}

void Player::Draw()
{
	if (mActive == true)
	{
		if (mHitTimer == 0)
		{
			DrawTriangle3D(
				VGet(0.0f + mX, 0.0f - mY, -0.1f),
				VGet(0.0f + mX2, 0.0f - mY2, -0.1f),
				VGet(0.0f + mX3, 0.0f - mY3, -0.1f),
				GetColor(255, 255, 255),
				TRUE
			);
		}
		

		DrawCircle(mMouseX, mMouseY, 10, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 9, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 8, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 7, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 10, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 9, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 8, GetColor(0, 225, 0), FALSE);
		DrawCircle(mMouseX, mMouseY, 7, GetColor(0, 225, 0), FALSE);
	}

	//プレイヤーのHPバー
	if (mHp == 100.0f)
		DrawRoundRect(17, 17, 183, 43, 12, 12, GetColor(mRed, mGreen, mBlue), TRUE);
	DrawRoundRect(20, 20, 180, 40, 10, 10, GetColor(0, 0, 0), TRUE);
	DrawRoundRect(20, 20, 20 + static_cast<int>(mHp2 * 1.6f), 40, 10, 10, GetColor(255, 0, 0), TRUE);
	DrawRoundRect(20, 20, 20 + static_cast<int>(mHp * 1.6f), 40, 10, 10, GetColor(0, 255, 0), TRUE);
	if (mHp != 100.0f)
		DrawRoundRect(20, 20, 180, 40, 10, 10, GetColor(255, 255, 255), FALSE);
}

void Player::Finalize()
{
	if (mHp == 100.0f)
	{
		mpSaveData->DamageScore(1000);
	}
	else
	{
		mpSaveData->DamageScore(0);
	}
}

void Player::SetMouseAngle()
{
	mAngle = atan2f(static_cast<float>(mMouseY - SCREEN_CENTER_Y), static_cast<float>(mMouseX - SCREEN_CENTER_X));
	
	mX = mSpeed * static_cast<float>(cos(mAngle));
	mY = mSpeed * static_cast<float>(sin(mAngle));

	mAngle = atan2f((SCREEN_CENTER_Y + mY) - SCREEN_CENTER_Y, (SCREEN_CENTER_X + mX) - SCREEN_CENTER_X);

	mX2 = -mSpeed * static_cast<float>(cos(mAngle - 1));
	mY2 = -mSpeed * static_cast<float>(sin(mAngle - 1));

	mAngle = atan2f((SCREEN_CENTER_Y + mY) - SCREEN_CENTER_Y, (SCREEN_CENTER_X + mX) - SCREEN_CENTER_X);

	mX3 = -mSpeed * static_cast<float>(cos(mAngle + 1));
	mY3 = -mSpeed * static_cast<float>(sin(mAngle + 1));
}

void Player::BulletShot()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (mShotTimer < 2)
			mShotTimer++;
	}
	else
	{
		mShotTimer = 0;
	}

	if (mShotTimer == 1)
	{
		if (mpBulletManager != nullptr)
			mpBulletManager->Shot(
				SCREEN_CENTER_X,
				SCREEN_CENTER_Y,
				0.0f + mX,
				0.0f - mY,
				static_cast<float>(mMouseX), static_cast<float>(mMouseY),
				BULLET_TYPE::TYPE_PLAYER);
	}
}

void Player::IsDamage()
{
	mHp -= 10;
	mHitFlag = true;
	if (mHp <= 0&&mActive==true)
	{
		PlaySoundMem(mExplosionSE, DX_PLAYTYPE_BACK, TRUE);
		mActive = false;
		mpEffect->Play(0.0f, 0.0f, EFFECT_NUM::EFFECT_1);
	}
}

void Player::Rainbow()
{
	switch (mColorswitch)
	{
		case 0:
		{
			mGreen += 5;
			if (mGreen > 250)
				mColorswitch = 1;
			break;
		}
		case 1:
		{
			mRed -= 5;

			if (mRed < 5)
				mColorswitch = 5;
			break;
		}
		case 2:
		{
			mGreen -= 5;
			if (mGreen < 5)
				mColorswitch = 3;
			break;
		}
		case 3:
		{
			mRed += 5;
			if (mRed > 250)
				mColorswitch = 4;
			break;
		}
		case 4:
		{
			mBlue -= 5;
			if (mBlue < 5)
				mColorswitch = 0;
			break;
		}
		case 5:
		{
			mBlue += 5;
			if (mBlue > 250)
				mColorswitch = 2;
			break;
		}
		default:
			break;
	}
}