#include"EnemyManager.h"
#include"Enemy/Enemy_0.h"
#include"../BulletManager/Bullet/Bullet_0.h"
#include"../BulletManager/BulletType.h"
#include <random>
#include"../Stage/Stage.h"
#include"../../Framework/ResourceManager.h"
#include"../../SaveData/SaveData.h"

EnemyManager::EnemyManager()
	:mpPlayer(nullptr)
	,mpStage(nullptr)
	, mpBulletManager(nullptr)
	,mpEffect(nullptr)
	,mpEnemy()
	, mCreateTimeer(0)
	, mCreateInterval(318)
	,mExplosionSE(0)
	,mpGrid(nullptr)
	,mpSaveData(nullptr)
	, mScore(0)
	, mDefeatScore(0)
{

}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Initialize(Player* pPlayer,Stage* pStage, BulletManager* pBulletManager,Effect* pEffect,Grid* pGrid, SaveData* pSaveData)
{
	mpPlayer = pPlayer;
	mpStage = pStage;
	mpBulletManager = pBulletManager;
	mpEffect = pEffect;
	mpGrid = pGrid;
	mpSaveData = pSaveData;
	ResourceManager* pRm = ResourceManager::GetInstance();
	mExplosionSE = pRm->GetResource("Explosion.mp3", TYPE::Audio);
}

void EnemyManager::Update()
{
	for (std::list<Enemy*>::iterator itr = mpEnemy.begin(); itr != mpEnemy.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Update();
	}
	CreateEnemy();
	DeleteEnemy();

	ChangeVolumeSoundMem(100, mExplosionSE);
}

void EnemyManager::Draw()
{
	for (std::list<Enemy*>::iterator itr = mpEnemy.begin(); itr != mpEnemy.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Draw();
	}
}

void EnemyManager::Finalize()
{
	for (std::list<Enemy*>::iterator itr = mpEnemy.begin(); itr != mpEnemy.end(); itr++)
	{
		if ((*itr) != nullptr)
		{
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
		}
	}
	mpEnemy.clear();
}

bool EnemyManager::HitEnemy(std::list<Bullet*>::iterator pBulletitr)
{
	for (std::list<Enemy*>::iterator itr = mpEnemy.begin(); itr != mpEnemy.end(); itr++)
	{
		if ((*itr)->Collision().CheckHit((*pBulletitr)->Collision()) == true)
		{
			(*itr)->IsDamage();
			return true;
		}
	}

	return false;
}

void EnemyManager::CreateEnemy()
{
	++mCreateTimeer %= mCreateInterval;
	std::mt19937 mt{ std::random_device{}() };
	int X = 0, Y = 0;
	if (mCreateTimeer == 0)
	{
		mpEnemy.push_back(new Enemy_0);
		std::list<Enemy*>::iterator itr = mpEnemy.end();
		(--itr);
		std::uniform_int_distribution<int> distX(static_cast<int>(mpStage->LEFT()), static_cast<int>(mpStage->RIGHT()));
		X = distX(mt);
		std::uniform_int_distribution<int> distY(static_cast<int>(mpStage->BOTTOM()), static_cast<int>(mpStage->TOP()));
		Y = distY(mt);
		if (mpPlayer != nullptr && mpStage != nullptr && mpBulletManager != nullptr && mpEffect != nullptr)
			(*itr)->Initialize(mpPlayer, mpStage, mpBulletManager, mpEffect, mpGrid, static_cast<float>(X), static_cast<float>(Y));
		std::uniform_int_distribution<int> distI(100, 300);
		mCreateInterval = distI(mt);
	}
}

void EnemyManager::DeleteEnemy()
{
	for (std::list<Enemy*>::iterator itr = mpEnemy.begin(); itr != mpEnemy.end();)
	{
		if ((*itr) == nullptr || mpSaveData == nullptr)
		{
			itr++;
			continue;
		}
		if ((*itr)->Active()==false)
		{
			PlaySoundMem(mExplosionSE, DX_PLAYTYPE_BACK, TRUE);
			(*itr)->Finalize();
			delete (*itr);
			itr=mpEnemy.erase(itr);
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<int> distS(100, 300);
			mScore += distS(mt);
			mDefeatScore += 100;
			mpSaveData->Save(mScore);
			mpSaveData->DefeatScore(mDefeatScore);
			continue;;
		}
		itr++;
	}
}