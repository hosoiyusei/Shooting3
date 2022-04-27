/*
タイトルシーン
*/
#pragma once

#include "../IScene.h"

class SoundWave;
class SaveData;

class TitleScene : public IScene
{
private:

	SoundWave* mpSoundWave;

	SaveData* mpSaveData;

	int mTest;

	float mAngle;

public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;
};