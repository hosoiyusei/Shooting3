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
	//�ړ�
	int inputUD = 0;
	int inputLR = 0;

	//�㉺
	if (IsButtonDown(PAD_INPUT_8) == TRUE && mPos.mY > -46.0f)
	{
		inputUD = -1;
	}

	if (IsButtonDown(PAD_INPUT_5) == TRUE && mPos.mY < 48.0f)
	{
		inputUD = 1;
	}

	//���E
	if (IsButtonDown(PAD_INPUT_4) == TRUE && mPos.mX < 48.0f)
	{
		inputLR = 1;
	}

	if (IsButtonDown(PAD_INPUT_6) == TRUE && mPos.mX > -46.0f)
	{
		inputLR = -1;
	}

	//���͂���Ă��Ȃ��Ȃ炱��ȏ㏈�����Ȃ�
	if (inputUD == 0 && inputLR == 0)
	{
		return;
	}

	//���͏����x�N�g���v�Z�p��float�^�֕ϊ�
	float vx = (float)inputLR;
	float vy = (float)inputUD;

	//�x�N�g���̒������擾
	float vl = sqrtf((vx * vx) + (vy * vy));

	//�P�ʃx�N�g��(������1�̃x�N�g��)���v�Z
	vx /= vl;
	vy /= vl;

	//�ړ��x�N�g����ړI�̑傫��(�ړ���)�ɃX�P�[�����O
	vx *= mSpeed;
	vy *= mSpeed;

	//�ړ��ʂ����W�ɉ��Z
	mPos.mX += vx;
	mPos.mY += vy;
}