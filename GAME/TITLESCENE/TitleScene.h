/*
�^�C�g���V�[��
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

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;
};