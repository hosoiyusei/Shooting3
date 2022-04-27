#pragma once
#include<list>

class Enemy;
class Player;
class Stage;
class BulletManager;
class Bullet;
class Effect;
class Grid;
class SaveData;

class EnemyManager
{
private:

	std::list<Enemy*> mpEnemy;
	//std::list<Enemy*>::iterator itr;

	Player* mpPlayer;

	Stage* mpStage;

	BulletManager* mpBulletManager;

	Effect* mpEffect;

	Grid* mpGrid;

	SaveData* mpSaveData;

	int mCreateTimeer;

	int mCreateInterval;

	int mExplosionSE;

	int mScore;

	int mDefeatScore;

public:

	EnemyManager();
	~EnemyManager();

	void Initialize(Player* pPlayer,Stage* pStage,BulletManager* pBulletManager,Effect* pEffect,Grid* pGrid, SaveData* pSaveData);

	void Update();

	void Draw();

	void Finalize();

	bool HitEnemy(std::list<Bullet*>::iterator pBulletitr);

private:

	void CreateEnemy();

	void DeleteEnemy();
};