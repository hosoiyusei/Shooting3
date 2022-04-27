/*
�v���C�V�[��
*/
#pragma once

#include "../IScene.h"

enum class SCENE :int
{
	COUNT,
	PLAY,
	TIMEUP,
};

class Player;
class Stage;
class BulletManager;
class EnemyManager;
class Effect;
class Grid;
class SaveData;

class PlayScene : public IScene
{
private:

	Player* mpPlayer;

	Stage* mpStage;

	BulletManager* mpBulletManager;

	EnemyManager* mpEnemyManager;

	Effect* mpEffect;

	Grid* mpGrid;

	SaveData* mpSaveData;

	SCENE mScene;

	int mCountTimer;

	int mFontSize;

	int mFontInterval;

	int mPlayTimer;

	int mTimeUpTimer;

	int mFadeTimer;

	int mScore;

	int mScoreTexture;

	float mScoreAngle;

	int mBGM;

public:

	// �R���X�g���N�^
	PlayScene();

	// �f�X�g���N�^
	~PlayScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:

	void ScoreUI();
};