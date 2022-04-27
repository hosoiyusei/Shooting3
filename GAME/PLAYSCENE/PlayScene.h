/*
プレイシーン
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

	// コンストラクタ
	PlayScene();

	// デストラクタ
	~PlayScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:

	void ScoreUI();
};