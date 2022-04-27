//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"

#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"
#include"RESULTSCENE/Resultscene.h"


// �萔�̒�` ==============================================================



// �֐��̒�` ==============================================================

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
GameMain::GameMain()
	: mNextScene(GAME_SCENE::NONE)
	, mpScene(nullptr)
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
GameMain::~GameMain()
{
}

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::InitializeGame()
{
	// �^�C�g���V�[���̍쐬
	mpScene = new TitleScene();
	mpScene->Initialize();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::UpdateGame()
{
	// ���̃V�[�����ݒ肳��Ă�����V�[���؂�ւ�
	if (mNextScene != GAME_SCENE::NONE)
	{
		// �V�[���폜
		DeleteScene();
		
		// �V�[���쐬
		CreateScene();
	}

	// ���Ԃ�����΍X�V
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update();
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::RenderGame()
{
	// ���Ԃ�����Ε`��
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::FinalizeGame()
{
	DeleteScene();
}

/*--------------------------------------------------
�V�[���̍쐬
--------------------------------------------------*/
void GameMain::CreateScene()
{
	// �V�[�����쐬����Ă���Ƃ��͏������Ȃ�
	if (mpScene != nullptr)
	{
		return;
	}

	// ���V�[���̍쐬
	switch (mNextScene)
	{
		case GAME_SCENE::TITLE:
		{
			mpScene = new TitleScene();
			break;
		}
		case GAME_SCENE::PLAY:
		{
			mpScene = new PlayScene();
			break;
		}
		case GAME_SCENE::RESULT:
		{
			mpScene = new ResultScene();
			break;
		}
		default:
		{
			// ��O�Ȃ̂ŏ����𒆒f
			return;
		}
	}

	// �쐬�����V�[����������
	mpScene->Initialize();
}

/*--------------------------------------------------
�V�[���̍폜
--------------------------------------------------*/
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (mpScene == nullptr)
	{
		return;
	}

	// ���V�[���̏I������
	mpScene->Finalize();

	// ���V�[���̍폜
	delete mpScene;
	mpScene = nullptr;
}
