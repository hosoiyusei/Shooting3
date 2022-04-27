#pragma once

class SaveData
{
private:

	int mScore;

	int mDamageScore;

	int mDefeatScore;

public:

	SaveData();
	~SaveData();

	void Save(int score);

	int Road(int i);

	void DamageScore(int score);

	void DefeatScore(int score);
};