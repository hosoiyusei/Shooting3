#include"ResourceManager.h"
#include "EffekseerForDXLib.h"

/*=============================================================================
�e�N�X�`���̒ǉ�
=============================================================================*/
int ResourceManager::GetResource(std::string fileName, TYPE type,float size)
{
	switch (type)
	{
		//�e�N�X�`��===========================================================
		case TYPE::Textures:
		{
			std::string fullPath = "Resources/Textures/" + fileName;  //�n���h��

			if (mTexturesHandles.find("Resources/Textures/" + fileName) != mTexturesHandles.end())   //���łɂ������炻���Ԃ�
			{
				return mTexturesHandles["Resources/Textures/" + fileName];
			}

			mTexturesHandles["Resources/Textures/" + fileName] = LoadGraph(fullPath.c_str());//�n���h����o�^����

			return mTexturesHandles["Resources/Textures/" + fileName];//�n���h����Ԃ�

			break;
		}
		//�T�E���h============================================================
		case TYPE::Audio:
		{
			std::string fullPath = "Resources/Audio/" + fileName;//�n���h��

			if (mAudioHandles.find("Resources/Audio/" + fileName) != mAudioHandles.end())//���łɂ������炻���Ԃ�
			{
				return mAudioHandles["Resources/Audio/" + fileName];
			}

			mAudioHandles["Resources/Audio/" + fileName] = LoadSoundMem(fullPath.c_str());//�n���h����o�^����

			return mAudioHandles["Resources/Audio/" + fileName];//�n���h����Ԃ�

			break;
		}
		//�G�t�F�N�g============================================================
		case TYPE::Effect:
		{
			std::string fullPath = "Resources/Effect/" + fileName;//�n���h��

			if (mEffectHandles.find("Resources/Effect/" + fileName) != mEffectHandles.end())//���łɂ������炻���Ԃ�
			{
				return mEffectHandles["Resources/Effect/" + fileName];
			}

			mEffectHandles["Resources/Effect/" + fileName] = LoadEffekseerEffect(fullPath.c_str(), size);//�n���h����o�^����

			return mEffectHandles["Resources/Effect/" + fileName];//�n���h����Ԃ�

			break;
		}
		default:
			break;
	}

	return 0;
}

/*===========================================================================
�e�N�X�`���̍폜
===========================================================================*/
void ResourceManager::DeleteResource()
{
	mTexturesHandles.clear();//�S�Ė���
	mAudioHandles.clear();
	mEffectHandles.clear();
}