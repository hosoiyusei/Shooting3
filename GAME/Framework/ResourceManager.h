#pragma once
#include <vector>
#include<string>
#include <map>

enum class TYPE :int
{
	Textures,
	Audio,
	Effect,
};

class ResourceManager
{
public:

	//�C�����C���֐�
	static ResourceManager* GetInstance()
	{
		static ResourceManager Rm;

		return &Rm;
	}

private:

	std::map<std::string, int> mTexturesHandles;

	std::map<std::string, int> mAudioHandles;

	std::map<std::string, int> mEffectHandles;

public:

	//�e�N�X�`���̎擾
	int GetResource(std::string fileName, TYPE type,float size=1.0f);

	//�e�N�X�`���̍폜
	void DeleteResource();
};