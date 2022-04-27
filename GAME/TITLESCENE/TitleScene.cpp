/*
タイトルシーン
*/
#include "TitleScene.h"

#include "../GameMain.h"
#include"../Framework/ResourceManager.h"
#include"../SoundWave/SoundWave.h"
#include"../SaveData/SaveData.h"
#include<math.h>

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
TitleScene::TitleScene()
	:mTest(0)
	, mpSoundWave(nullptr)
	, mpSaveData(nullptr)
	, mAngle(0.0f)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
TitleScene::~TitleScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void TitleScene::Initialize()
{
	mpSoundWave = new SoundWave();
	mpSaveData = new SaveData();

	mpSoundWave->Initialize();

	ResourceManager* pRm = ResourceManager::GetInstance();

	//mTest = pRm->GetResource("TridentLogo.png", TYPE::Textures);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE TitleScene::Update()
{
	if (mpSoundWave != nullptr)
		mpSoundWave->Update();

	mAngle += 0.1f;

	if (IsButtonPressed(PAD_INPUT_1))
	{
		return GAME_SCENE::PLAY;
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void TitleScene::Draw()
{
	mpSoundWave->DrawWave();

	
	//DrawString(0, 20, "Input ZKey", GetColor(255, 0, 0));

	SetFontSize(50);
	DrawString(210, 60, "Shooting", GetColor(205 - (50 * sin(mAngle)), 205 - (50 * sin(mAngle)), 205 - (50 * sin(mAngle))));

	//DrawRectRotaGraph(
	//	SCREEN_CENTER_X,//Xの位置
	//	SCREEN_CENTER_Y-50,//Yの位置
	//	0,//切り取り開始の位置
	//	0,//切り取り開始の位置
	//	2500,//切り取り終わりの位置
	//	1500,//切り取り終わりの位置
	//	0.655,//拡大
	//	0.0,//回転
	//	mTest,//アドレス
	//	TRUE
	//);
	SetFontSize(20);
	DrawString(110, 300, "前回のスコア", GetColor(255, 255, 255));
	if (mpSaveData != nullptr)
		DrawFormatString(110, 330, GetColor(255, 255, 255), "%d", mpSaveData->Road(0));
	DrawString(410, 300, "スタート", GetColor(255, 255, 255));
	DrawString(410, 330, "Push Z Key", GetColor(255, 255, 255));
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void TitleScene::Finalize()
{
	if (mpSoundWave != nullptr)
		mpSoundWave->Finalize();
	delete mpSoundWave;
	mpSoundWave = nullptr;

	if (mpSaveData != nullptr)
		delete mpSaveData;
	mpSaveData = nullptr;
}
