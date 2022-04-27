//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   WinMain.cpp
//!
//! @brief  �Q�[���v���O�����̃G���g���[�|�C���g
//!
//! @date   2019/3/26
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"
#include "EffekseerForDXLib.h"

// �֐���` ================================================================

//----------------------------------------------------------------------
//! @brief �v���O�����̃G���g���[�|�C���g
//!
//! @param[in] hInstance     ���݂̃C���X�^���X�̃n���h��
//! @param[in] hPrevInstance �ȑO�̃C���X�^���X�̃n���h��(���NULL)
//! @param[in] lpCmdLine     �R�}���h���C��
//! @param[in] nCmdShow      �E�B���h�E�̕\�����
//!
//! @retval  0 ����I��
//! @retval -1 �ُ�I��
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// �������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif


	// �f�o�b�O���p���O�t�@�C���̏o�̗͂}��
	SetOutApplicationLogValidFlag(FALSE);


	// �N�����[�h�̐ݒ�

	ChangeWindowMode(TRUE);	          // �E�C���h�E���[�h�Ŏ��s
	SetMainWindowText(GAME_TITLE);    // �E�C���h�E�^�C�g���̐ݒ�
	SetWindowIconID(IDI_ICON1);       // �E�C���h�E�A�C�R���̐ݒ�



	// ������Ԃ̉�ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);


	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���N���X�̍쐬
	GameMain* pGameMain = new GameMain();
	
	// �Q�[���̏���
	pGameMain->InitializeGame();    // �Q�[���̏���������
	
	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{ 
		UpdateSystem();        // �V�X�e���̍X�V
		
		pGameMain->UpdateGame();          // �Q�[���̍X�V����
		pGameMain->RenderGame();          // �Q�[���̕`�揈��

		ScreenFlip();          // ����ʂ̓��e��\��ʂɔ��f
		ClearDrawScreen();     // ����ʂ̏���
	}

	pGameMain->FinalizeGame();      // �Q�[���̏I������

	// �Q�[���N���X�̍폜
	delete pGameMain;

	pGameMain = nullptr;

	Effkseer_End();

	// DX���C�u�����̏I������
	if (DxLib_End() == -1)
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}


	return 0;    // ����I��
}
