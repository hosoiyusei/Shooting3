/*
プレイシーン
*/
#include "PlayScene.h"

#include "../GameMain.h"
#include"Player/Player.h"
#include"Stage/Stage.h"
#include"BulletManager/BulletManager.h"
#include"EnemyManager/EnemyManager.h"
#include"Effect/Effect.h"
#include"Grid/Grid.h"
#include"../SaveData/SaveData.h"
#include"../Framework/ResourceManager.h"
#include<math.h>

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
PlayScene::PlayScene()
	:mpPlayer(nullptr)
	, mpStage(nullptr)
	, mpBulletManager(nullptr)
	, mpEnemyManager(nullptr)
	, mpEffect(nullptr)
	, mpGrid(nullptr)
	, mpSaveData(nullptr)
	, mScene(SCENE::COUNT)
	, mCountTimer(240)
	, mFontSize(0)
	, mFontInterval(60)
	, mPlayTimer(3600)
	, mTimeUpTimer(0)
	, mFadeTimer(255)
	, mScore(0)
	, mScoreTexture(0)
	, mScoreAngle(0.0f)
	,mBGM(0)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
PlayScene::~PlayScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void PlayScene::Initialize()
{
	mpPlayer = new Player;
	mpStage = new Stage();
	mpBulletManager = new BulletManager();
	mpEnemyManager = new EnemyManager;
	mpEffect = new Effect();
	mpGrid = new Grid();
	mpSaveData = new SaveData();

	mpPlayer->Initialize(mpBulletManager, mpEffect,mpGrid,mpSaveData);
	mpStage->Initialize(mpPlayer);
	mpBulletManager->Initialize(mpStage, mpEnemyManager, mpPlayer, mpEffect);
	mpEnemyManager->Initialize(mpPlayer, mpStage, mpBulletManager,mpEffect,mpGrid,mpSaveData);
	mpEffect->Initialize(mpStage,mpGrid);
	mpSaveData->Save(0);
	mpSaveData->DamageScore(0);
	mpSaveData->DefeatScore(0);

	ResourceManager* pRm = ResourceManager::GetInstance();

	mScoreTexture = pRm->GetResource("all.png", TYPE::Textures);
	mBGM = pRm->GetResource("PlayBGM.mp3", TYPE::Audio);
	PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE PlayScene::Update()
{
	--mCountTimer;
	switch (mScene)
	{
		case SCENE::COUNT:
		{
			++mFontSize %= mFontInterval;
			if (mCountTimer < 60)
			{
				mFontSize = 0;
				mScene = SCENE::PLAY;
			}
			break;
		}
		case SCENE::PLAY:
		{
			if (mPlayTimer > 0)
				mPlayTimer--;

			if (mpGrid != nullptr)
				mpGrid->Update();
			if (mpPlayer != nullptr)
				mpPlayer->Update();
			if (mpStage != nullptr)
				mpStage->Update();
			if (mpBulletManager != nullptr)
				mpBulletManager->Update();
			if (mpEnemyManager != nullptr)
				mpEnemyManager->Update();

			if (mPlayTimer == 0)
				mScene = SCENE::TIMEUP;

			if (mpPlayer != nullptr)
				if (mpPlayer->Active() == false)
					mScene = SCENE::TIMEUP;
			break;
		}
		case SCENE::TIMEUP:
		{
			if (mpPlayer != nullptr)
				if (mpPlayer->Active() == false)
					mpPlayer->Update();//HPばー動かす

			if (mFontSize < 200)
				mFontSize += 10;

			if (mTimeUpTimer < 300)
				mTimeUpTimer++;
			if (mTimeUpTimer > 100)
				mFadeTimer -= 5;
			if(mTimeUpTimer ==300)
				return GAME_SCENE::RESULT;
			break;
		}
		default:
			break;
	}

	mScoreAngle += 0.1f;

	if (mpSaveData != nullptr)
		if (mScore < mpSaveData->Road(0))
			mScore++;
	if (mpEffect != nullptr)
		mpEffect->Update();

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void PlayScene::Draw()
{
	if (mpGrid != nullptr)
		mpGrid->Draw();
	if (mpStage != nullptr)
		mpStage->Draw();
	if (mpEnemyManager != nullptr)
		mpEnemyManager->Draw();
	if (mpBulletManager != nullptr)
		mpBulletManager->Draw();
	if (mpPlayer != nullptr)
		mpPlayer->Draw();
	if (mpEffect != nullptr)
		mpEffect->Draw();
	
	switch (mScene)
	{
		case SCENE::COUNT:
		{
			int Font = mFontSize * 3;
			SetFontSize(Font);
			DrawFormatString(SCREEN_CENTER_X - (Font / 4), SCREEN_CENTER_Y - (Font / 2), GetColor(255, 255, 255), "%d", mCountTimer / 60);
			SetFontSize(16);
			break;
		}
		case SCENE::PLAY:
		{
			break;
		}
		case SCENE::TIMEUP:
		{

			SetFontSize(mFontSize);
			if (mpPlayer != nullptr)
				if (mpPlayer->Active() == false)
				{
					mFontSize = static_cast<int>(mFontSize * 0.9f);
					SetFontSize(mFontSize);
					DrawFormatString(SCREEN_CENTER_X - (mFontSize / 3) * 6, SCREEN_CENTER_Y - mFontSize / 2, GetColor(255, 0, 0), "GAME OVER");
				}
				else
					DrawFormatString(SCREEN_CENTER_X - (mFontSize / 4) * 6, SCREEN_CENTER_Y - mFontSize / 2, GetColor(255, 255, 255), "TIMEUP");
			SetFontSize(16);

			break;
		}
		default:
			break;
	}
	if (mPlayTimer > 600)
		DrawFormatString(620, 5, GetColor(255, 255, 255), "%d", mPlayTimer / 60);
	if (mPlayTimer < 600)
		DrawFormatString(630, 5, GetColor(255, 255, 255), "%d", mPlayTimer / 60);

	ScoreUI();

	SetDrawBright(mFadeTimer, mFadeTimer, mFadeTimer);
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void PlayScene::Finalize()
{
	delete mpGrid;
	mpGrid = nullptr;
	if (mpPlayer != nullptr)
		mpPlayer->Finalize();
	delete mpPlayer;
	mpPlayer = nullptr;

	if (mpStage != nullptr)
		mpStage->Finalize();
	delete mpStage;
	mpStage = nullptr;

	if (mpBulletManager != nullptr)
		mpBulletManager->Finalize();
	delete mpBulletManager;
	mpBulletManager = nullptr;

	if (mpEnemyManager != nullptr)
		mpEnemyManager->Finalize();
	delete mpEnemyManager;
	mpEnemyManager = nullptr;

	if (mpEffect != nullptr)
		mpEffect->Finalize();
	delete mpEffect;
	mpEffect = nullptr;

	if (mpSaveData != nullptr)
		delete mpSaveData;
	mpSaveData = nullptr;

	StopSoundMem(mBGM);
	ResourceManager* pRm = ResourceManager::GetInstance();
	pRm->DeleteResource();
}

void PlayScene::ScoreUI()
{
	int PosX = 100;
	int PosY = 60;

	int x = mScore;
	int Y = 0;
	
	for (int i = 0; i < 5; i++)
	{
		int a = 0;

		a = x % 10;
		if (i == 0 || i == 2 || i == 4)
			Y = PosY + (1 * sin(mScoreAngle));
		if(i==1||i==3)
			Y = PosY + (1 * cos(mScoreAngle));
		DrawRectRotaGraph(
			PosX,//Xの位置
			Y,//Yの位置
			0 + a * 16,//切り取り開始の位置
			32,//切り取り開始の位置
			16,//切り取り終わりの位置
			23,//切り取り終わりの位置
			1,//拡大
			0.0,//回転
			mScoreTexture,//アドレス
			TRUE
		);
		PosX -= 15;
		x /= 10;
	}
}