/*
�^�C�g���V�[��
*/
#include "TitleScene.h"

#include "../GameMain.h"
#include"../Framework/ResourceManager.h"
#include"../SoundWave/SoundWave.h"
#include"../SaveData/SaveData.h"
#include<math.h>

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
TitleScene::TitleScene()
	:mTest(0)
	, mpSoundWave(nullptr)
	, mpSaveData(nullptr)
	, mAngle(0.0f)
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
TitleScene::~TitleScene()
{
}

/*--------------------------------------------------
������
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
�X�V
�߂�l	:���̃V�[���ԍ�
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
�`��
--------------------------------------------------*/
void TitleScene::Draw()
{
	mpSoundWave->DrawWave();

	
	//DrawString(0, 20, "Input ZKey", GetColor(255, 0, 0));

	SetFontSize(50);
	DrawString(210, 60, "Shooting", GetColor(205 - (50 * sin(mAngle)), 205 - (50 * sin(mAngle)), 205 - (50 * sin(mAngle))));

	//DrawRectRotaGraph(
	//	SCREEN_CENTER_X,//X�̈ʒu
	//	SCREEN_CENTER_Y-50,//Y�̈ʒu
	//	0,//�؂���J�n�̈ʒu
	//	0,//�؂���J�n�̈ʒu
	//	2500,//�؂���I���̈ʒu
	//	1500,//�؂���I���̈ʒu
	//	0.655,//�g��
	//	0.0,//��]
	//	mTest,//�A�h���X
	//	TRUE
	//);
	SetFontSize(20);
	DrawString(110, 300, "�O��̃X�R�A", GetColor(255, 255, 255));
	if (mpSaveData != nullptr)
		DrawFormatString(110, 330, GetColor(255, 255, 255), "%d", mpSaveData->Road(0));
	DrawString(410, 300, "�X�^�[�g", GetColor(255, 255, 255));
	DrawString(410, 330, "Push Z Key", GetColor(255, 255, 255));
}

/*--------------------------------------------------
�I������
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
