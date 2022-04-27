#include"Stage.h"
#include"../../GameMain.h"
#include<corecrt_math.h>
#include"../Player/Player.h"

Stage::Stage()
	:mPos()
	,mSize(50)
	, mSpeed(0.2f)
	,mpPlayer(nullptr)
	,mLeft(0.0f)
	,mRight(0.0f)
	,mTop(0.0f)
	,mBottom(0.0f)
{

}

Stage::~Stage()
{

}

void Stage::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
	mPos.mX = 0;
	mPos.mY = 0;
}

void Stage::Update()
{
	if (mpPlayer != nullptr)
		if (mpPlayer->Active() == true)
			Move();

	mLeft = mPos.mX - 48.0f;
	mRight = mPos.mX + 46.0f;
	mTop = mPos.mY + 46.0f;
	mBottom = mPos.mY - 48.0f;
}

void Stage::Draw()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 || j == 0 || i == 49 || j == 49)
			{
					
			}
			else
			{
					mDrawBox3D.Draw(1.0f,
						(mPos.mX - 50) + (j * 2),
						(mPos.mY - 50) + (i * 2)
					);
			}
		}
	}
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 || j == 0 || i == 49 || j == 49)
			{
				mDrawBox3D.Draw2(1.0f,
					(mPos.mX - 50) + (j * 2),
					(mPos.mY - 50) + (i * 2)
				);
			}
		}
	}
}

void Stage::Finalize()
{

}

void Stage::Move()
{
	//移動
	int inputUD = 0;
	int inputLR = 0;

	//上下
	if (IsButtonDown(PAD_INPUT_8) == TRUE && mPos.mY > -46.0f)
	{
		inputUD = -1;
	}

	if (IsButtonDown(PAD_INPUT_5) == TRUE && mPos.mY < 48.0f)
	{
		inputUD = 1;
	}

	//左右
	if (IsButtonDown(PAD_INPUT_4) == TRUE && mPos.mX < 48.0f)
	{
		inputLR = 1;
	}

	if (IsButtonDown(PAD_INPUT_6) == TRUE && mPos.mX > -46.0f)
	{
		inputLR = -1;
	}

	//入力されていないならこれ以上処理しない
	if (inputUD == 0 && inputLR == 0)
	{
		return;
	}

	//入力情報をベクトル計算用にfloat型へ変換
	float vx = (float)inputLR;
	float vy = (float)inputUD;

	//ベクトルの長さを取得
	float vl = sqrtf((vx * vx) + (vy * vy));

	//単位ベクトル(長さが1のベクトル)を計算
	vx /= vl;
	vy /= vl;

	//移動ベクトルを目的の大きさ(移動量)にスケーリング
	vx *= mSpeed;
	vy *= mSpeed;

	//移動量を座標に加算
	mPos.mX += vx;
	mPos.mY += vy;
}