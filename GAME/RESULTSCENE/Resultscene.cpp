#include "Resultscene.h"

#include "../GameMain.h"
#include"../SaveData/SaveData.h"
#include"../PLAYSCENE/Stage/Stage.h"
#include"../PLAYSCENE/Grid/Grid.h"
#include"../Framework/ResourceManager.h"
#include<math.h>

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
ResultScene::ResultScene()
	:mpSaveData(nullptr)
	, mpStage(nullptr)
	, mpGrid(nullptr)
	, mpPlayer(nullptr)
	, mScore(0)
	, mDamageScore(0)
	, mDefeatScore(0)
	, mScoreswitch(0)
	, mAllScore(0)
	, mTitleFlag(false)
	, mScoreTexture(0)
	, mAngle(0.0f)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
ResultScene::~ResultScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void ResultScene::Initialize()
{
	mpSaveData = new SaveData();
	mpStage = new Stage();
	mpGrid = new Grid();

	mpStage->Initialize(mpPlayer);

	SetDrawBright(255, 255, 255);

	ResourceManager* pRm = ResourceManager::GetInstance();

	mScoreTexture = pRm->GetResource("all.png", TYPE::Textures);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE ResultScene::Update()
{
	if (mpSaveData != nullptr)
		Score();
	if (mpGrid != nullptr)
		mpGrid->Update();

	mAngle += 0.1f;

	if (IsButtonPressed(PAD_INPUT_1)&&mTitleFlag==true)
	{
		return GAME_SCENE::TITLE;
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void ResultScene::Draw()
{
	if (mpGrid != nullptr)
		mpGrid->Draw();
	if (mpStage != nullptr)
		mpStage->Draw();

	SetFontSize(60);
	DrawString(230, 30, "Result", GetColor(0, 255, 255));
	SetFontSize(16);

	DrawString(400, 400, "Input ZKey", GetColor(
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle))),
		static_cast<int>(205 - (50 * sin(mAngle)))));

	DrawString(50, 120, "獲得スコア", GetColor(255, 255, 255));
	ScoreUI(0, mScore);
	DrawString(50, 170, "残りライフスコア", GetColor(255, 255, 255));
	ScoreUI(1, mDamageScore);
	DrawString(50, 220, "撃破数スコア", GetColor(255, 255, 255));
	ScoreUI(2, mDefeatScore);
	DrawString(50, 300, "スコア", GetColor(255, 255, 255));
	ScoreUI(3,mAllScore);
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void ResultScene::Finalize()
{
	
	if (mpSaveData != nullptr)
		mpSaveData->Save(mAllScore);
	delete mpSaveData;
	mpSaveData = nullptr;

	if (mpStage != nullptr)
		mpStage->Finalize();
	delete mpStage;
	mpStage = nullptr;
}

void ResultScene::Score()
{
	switch (mScoreswitch)
	{
		case 0:
		{
			if (mpSaveData->Road(0) - 100 > mScore)
			{
				mScore += 100;
			}
			else if (mpSaveData->Road(0) - 10 > mScore)
			{
				mScore += 10;
			}
			else if (mpSaveData->Road(0) > mScore)
			{
				mScore++;
			}
			else
				mScoreswitch = 1;

			break;
		}
		case 1:
		{
			if (mpSaveData->Road(1) - 100 > mDamageScore)
			{
				mDamageScore += 100;
			}
			else if (mpSaveData->Road(1) - 10 > mDamageScore)
			{
				mDamageScore += 10;
			}
			else if (mpSaveData->Road(1) > mDamageScore)
			{
				mDamageScore++;
			}
			else
				mScoreswitch = 2;
			break;
		}
		case 2:
		{
			if (mpSaveData->Road(2) - 100 > mDefeatScore)
			{
				mDefeatScore += 100;
			}
			else if (mpSaveData->Road(2) - 10 > mDefeatScore)
			{
				mDefeatScore += 10;
			}
			else if (mpSaveData->Road(2) > mDefeatScore)
			{
				mDefeatScore++;
			}
			else
				mScoreswitch = 3;
			break;
		}
		case 3:
		{
			if (mAllScore < (mScore + mDamageScore + mDefeatScore-100))
			{
				mAllScore+=100;
			}
			else if (mAllScore < (mScore + mDamageScore + mDefeatScore - 10))
			{
				mAllScore += 10;
			}
			else if (mAllScore < (mScore + mDamageScore + mDefeatScore))
			{
				mAllScore++;
			}
			else
			{
				mTitleFlag = true;
			}
			break;
		}
		default:
			break;
	}
}

void ResultScene::ScoreUI(int num , int score)
{
	int PosX = 300;
	int PosY = 0;
	if (num == 0)
		PosY = 120;
	if (num == 1)
		PosY = 170;
	if (num == 2)
		PosY = 220;
	if (num == 3)
		PosY = 300;

	int x = score;

	for (int i = 0; i < 5; i++)
	{
		int a = 0;

		a = x % 10;
		
		DrawRectRotaGraph(
			PosX,//Xの位置
			PosY,//Yの位置
			0 + a * 16,//切り取り開始の位置
			32,//切り取り開始の位置
			16,//切り取り終わりの位置
			23,//切り取り終わりの位置
			1.0f,//拡大
			0.0,//回転
			mScoreTexture,//アドレス
			TRUE
		);
		PosX -= 15;
		x /= 10;
	}
}