#pragma once
#include"../../Utility.h"

enum class EFFECT_NUM :int
{
	EFFECT_1,
	EFFECT_2,
	EFFECT_3,

	EFFECT_START,
};

class Stage;
class Grid;

class Effect
{
private:

	Float2 mPos[4];
	Float2 mPos2[4];
	Float2 mSetPos;

	int mEffectResourceHandle;
	int mEffectResourceHandle2;
	int mEffectResourceHandle3;
	int mEffectResourceHandle4;

	int mEffect1;
	int mEffect2;
	int mEffect3;

	int mTimer;

	int mStartTimer;

	Stage* mpStage;

	Grid* mpGrid;

public:

	Effect();
	~Effect();

	void Initialize(Stage* pStage,Grid* pGrid);

	void Update();

	void Draw();

	void Finalize();

	void Play(float x,float y, EFFECT_NUM num);
};