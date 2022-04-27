#include"SaveData.h"
#include <fstream>   // ifstream, ofstream
#include<iostream>

SaveData::SaveData()
	: mScore(0)
	, mDamageScore(0)
	, mDefeatScore(0)
{

}

SaveData::~SaveData()
{

}

void SaveData::Save(int scere)
{
	std::ofstream writing_file;
	writing_file.open("Resources/SaveData/SaveData.txt", std::ios::out);
	mScore = scere;
	writing_file << scere << std::endl;
	writing_file << mDamageScore << std::endl;
	writing_file << mDefeatScore << std::endl;

	writing_file.close();
}

int SaveData::Road(int i)
{
	std::ifstream ifs("Resources/SaveData/SaveData.txt");

	int data[3] = {};
	for (int a = 0; a < 3; a++)
		ifs >> data[a];

	if (i == 0)
	{
		return data[0];
		ifs.close();
	}
	else if (i == 1)
	{
		return data[1];
		ifs.close();
	}
	else
	{
		return data[2];
		ifs.close();
	}
		
	return 0;
}

void SaveData::DamageScore(int score)
{
	std::ofstream writing_file;
	writing_file.open("Resources/SaveData/SaveData.txt", std::ios::out);
	mDamageScore = score;
	writing_file << mScore << std::endl;
	writing_file << mDamageScore << std::endl;
	writing_file << mDefeatScore << std::endl;
	writing_file.close();
}

void SaveData::DefeatScore(int score)
{
	std::ofstream writing_file;
	writing_file.open("Resources/SaveData/SaveData.txt", std::ios::out);
	mDefeatScore = score;
	writing_file << mScore << std::endl;
	writing_file << mDamageScore << std::endl;
	writing_file << mDefeatScore << std::endl;
	writing_file.close();
}