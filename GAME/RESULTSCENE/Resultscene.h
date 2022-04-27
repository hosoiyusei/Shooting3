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

	// �R���X�g���N�^
	ResultScene();

	// �f�X�g���N�^
	~ResultScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:

	void Score();

	void ScoreUI(int num, int score);
};