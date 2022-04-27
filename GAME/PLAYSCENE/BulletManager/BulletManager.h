#pragma once
#include"../../Utility.h"
#include<list>
#include"BulletType.h"

class Bullet;
class Stage;
class EnemyManager;
class Player;
class Effect;

class BulletManager
{
private:

	std::list<Bullet*> mpBullet;
	//std::list<Bullet*>::iterator itr;

	Stage* mpStage;

	EnemyManager* mpEnemyManager;

	Player* mpPlayer;

	Effect* mpEffect;

	int mHitSE;

	int mShotSE;

public:

	BulletManager();
	~BulletManager();

	void Initialize(Stage* pStage, EnemyManager* pEnemyManager, Player* pPlayer, Effect* pEffect);

	void Update();

	void Draw();

	void Finalize();

	void Shot(
		float ShooterPosX,
		float ShooterPosY,
		float ShotPosX,
		float ShotPosY,
		float TargetPosX,
		float TargetPosY,
		BULLET_TYPE type);

	void Shot_2(
		float ShooterPosX,
		float ShooterPosY,
		float ShotPosX,
		float ShotPosY,
		float TargetPosX,
		float TargetPosY,
		BULLET_TYPE type);

private:

	void DeleteBullet();

	void HitEnemy();

	void HitPlayer();
};