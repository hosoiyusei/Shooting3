#pragma once

#include "../IScene.h"

class SaveData;
class Stage;
class Grid;
class Player;

class ResultScene : public IScene
{
private:

	SaveData* mpSaveData;

	Stage* mpStage;

	Grid* mpGrid;

	Player* mpPlayer;

	int mScore, mDamageScore, mDefeatScore, mAllScore;

	int mScoreswitch;

	bool mTitleFlag;

	int mScoreTexture;

	float mAngle;

public:

	// コンストラクタ
	ResultScene();

	// デストラクタ
	~ResultScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:

	void Score();

	void ScoreUI(int num, int score);
};