#include"Effect.h"
#include "EffekseerForDXLib.h"
#include"../../Framework/ResourceManager.h"
#include"../Stage/Stage.h"

Effect::Effect()
	:mEffectResourceHandle(0)
	, mEffectResourceHandle2(0)
	, mEffectResourceHandle3(0)
	, mEffectResourceHandle4(0)
	, mEffect1(0)
	, mEffect2(0)
	, mEffect3(0)
	, mTimer(0)
	, mPos()
	, mPos2()
	,mStartTimer(0)
	,mpStage(nullptr)
	,mpGrid(nullptr)
{

}

Effect::~Effect()
{

}

void Effect::Initialize(Stage* pStage,Grid* pGrid)
{
	mpStage = pStage;
	mpGrid = pGrid;
	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	ResourceManager* pRm = ResourceManager::GetInstance();

	mEffectResourceHandle = pRm->GetResource("laser.efk", TYPE::Effect, 20);
	mEffectResourceHandle2 = pRm->GetResource("Breakdown.efk", TYPE::Effect, 20);
	mEffectResourceHandle3 = pRm->GetResource("Gohlem1.efk", TYPE::Effect, 20);
	mEffectResourceHandle4 = pRm->GetResource("Test.efk", TYPE::Effect, 20);

	//mEffect1 = PlayEffekseer2DEffect(mEffectResourceHandle);
}

void Effect::Update()
{
	if (mStartTimer < 2)
		mStartTimer++;
	if (mStartTimer == 1)
		Play(-200, -200, EFFECT_NUM::EFFECT_START);

	VECTOR Set = ConvWorldPosToScreenPos(VGet(mpStage->GetPos().mX, mpStage->GetPos().mY, -0.1f));

	mPos2[0].mX = mPos[0].mX - (mSetPos.mX - Set.x);
	mPos2[0].mY = mPos[0].mY - (mSetPos.mY - Set.y);
	mPos2[1].mX = mPos[1].mX - (mSetPos.mX - Set.x);
	mPos2[1].mY = mPos[1].mY - (mSetPos.mY - Set.y);
	mPos2[2].mX = mPos[2].mX - (mSetPos.mX - Set.x);
	mPos2[2].mY = mPos[2].mY - (mSetPos.mY - Set.y);

	SetPosPlayingEffekseer2DEffect(mEffect1, mPos2[0].mX, mPos2[0].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect2, mPos2[1].mX, mPos2[1].mY, 0);
	SetPosPlayingEffekseer2DEffect(mEffect3, mPos2[2].mX, mPos2[2].mY, 0);

	UpdateEffekseer2D();
}

void Effect::Draw()
{
	DrawEffekseer2D();
}

void Effect::Finalize()
{
	//DeleteEffekseerEffect(mEffectResourceHandle);
}

void Effect::Play(float x,float y, EFFECT_NUM num)
{
	if (num == EFFECT_NUM::EFFECT_1)
	{
		mEffect1 = PlayEffekseer2DEffect(mEffectResourceHandle);

		VECTOR Pos = ConvWorldPosToScreenPos(VGet(x,y,-0.1f));
		mPos[0].mX = Pos.x;
		mPos[0].mY = Pos.y;
		VECTOR Set= ConvWorldPosToScreenPos(VGet(mpStage->GetPos().mX, mpStage->GetPos().mY, -0.1f));
		mSetPos.mX = Set.x;
		mSetPos.mY = Set.y;
	}
	else if (num == EFFECT_NUM::EFFECT_2)
	{
		mEffect2 = PlayEffekseer2DEffect(mEffectResourceHandle2);
		VECTOR Pos = ConvWorldPosToScreenPos(VGet(x,y,-0.1f));
		mPos[1].mX = Pos.x;
		mPos[1].mY = Pos.y;
		VECTOR Set = ConvWorldPosToScreenPos(VGet(mpStage->GetPos().mX, mpStage->GetPos().mY, -0.1f));
		mSetPos.mX = Set.x;
		mSetPos.mY = Set.y;
	}
	else if (num == EFFECT_NUM::EFFECT_3)
	{
		mEffect3 = PlayEffekseer2DEffect(mEffectResourceHandle3);
		VECTOR Pos = ConvWorldPosToScreenPos(VGet(x,y,-0.1f));
		mPos[2].mX = Pos.x;
		mPos[2].mY = Pos.y;
		VECTOR Set = ConvWorldPosToScreenPos(VGet(mpStage->GetPos().mX, mpStage->GetPos().mY, -0.1f));
		mSetPos.mX = Set.x;
		mSetPos.mY = Set.y;
	}
	else if (num == EFFECT_NUM::EFFECT_START)
	{
		mEffect3 = PlayEffekseer2DEffect(mEffectResourceHandle4);
		VECTOR Pos = ConvWorldPosToScreenPos(VGet(x,y,-0.1f));
		mPos[3].mX = static_cast<float>(Pos.x);
		mPos[3].mY = static_cast<float>(Pos.y);
		VECTOR Set = ConvWorldPosToScreenPos(VGet(mpStage->GetPos().mX, mpStage->GetPos().mY, -0.1f));
		mSetPos.mX = Set.x;
		mSetPos.mY = Set.y;
	}
}