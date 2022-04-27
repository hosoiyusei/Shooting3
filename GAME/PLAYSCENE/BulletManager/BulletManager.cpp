#include"BulletManager.h"
#include"../../Framework/ResourceManager.h"
#include"Bullet/Bullet_0.h"
#include"Bullet/Bullet_1.h"
#include"../Stage/Stage.h"
#include"../EnemyManager/EnemyManager.h"
#include"../Player/Player.h"
#include"../Effect/Effect.h"

BulletManager::BulletManager()
	:mpBullet()
	, mpStage(nullptr)
	,mpEnemyManager(nullptr)
	,mpPlayer(nullptr)
	,mpEffect(nullptr)
	,mHitSE(0)
	,mShotSE(0)
{

}

BulletManager::~BulletManager()
{

}

void BulletManager::Initialize(Stage* pStage,EnemyManager* pEnemyManager,Player* pPlayer,Effect* pEffect)
{
	mpStage = pStage;
	mpEnemyManager = pEnemyManager;
	mpPlayer = pPlayer;
	mpEffect = pEffect;
	ResourceManager* pRm = ResourceManager::GetInstance();
	mHitSE = pRm->GetResource("Hit.mp3", TYPE::Audio);
	mShotSE = pRm->GetResource("Shot.mp3", TYPE::Audio);
}

void BulletManager::Update()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Update();
	}

	HitEnemy();
	HitPlayer();
	ChangeVolumeSoundMem(100, mHitSE);
	ChangeVolumeSoundMem(100, mShotSE);

	DeleteBullet();
}

void BulletManager::Draw()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) != nullptr)
			(*itr)->Draw();
	}
}

void BulletManager::Finalize()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end(); itr++)
	{
		if ((*itr) == nullptr)
			continue;
		(*itr)->Finalize();
		delete (*itr);
	}
	mpBullet.clear();
}

void BulletManager::Shot(
	float ShooterPosX,
	float ShooterPosY,
	float ShotPosX,
	float ShotPosY,
	float TargetPosX,
	float TargetPosY,
	BULLET_TYPE type)
{
	mpBullet.push_back(new Bullet_0());
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr);
	if (mpStage != nullptr)
		(*itr)->Initialize(
			mpStage, ShooterPosX, ShooterPosY, ShotPosX, ShotPosY, TargetPosX, TargetPosY, type);
	PlaySoundMem(mShotSE, DX_PLAYTYPE_BACK, TRUE);
}

void BulletManager::Shot_2(
	float ShooterPosX,
	float ShooterPosY,
	float ShotPosX,
	float ShotPosY,
	float TargetPosX,
	float TargetPosY,
	BULLET_TYPE type)
{
	mpBullet.push_back(new Bullet_1());
	std::list<Bullet*>::iterator itr = mpBullet.end();
	(--itr);
	if (mpStage != nullptr)
		(*itr)->Initialize(
			mpStage, ShooterPosX, ShooterPosY, ShotPosX, ShotPosY, TargetPosX, TargetPosY, type);
	PlaySoundMem(mShotSE, DX_PLAYTYPE_BACK, TRUE);
}

void BulletManager::DeleteBullet()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
		if (
			(*itr)->GetPosX() < -3000 ||
			(*itr)->GetPosX() > 3000 ||
			(*itr)->GetPosY() < -3000 ||
			(*itr)->GetPosY() > 3000)
		{
			if ((*itr) != nullptr)
				(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr=mpBullet.erase(itr);
			continue;
		}
		itr++;
	}
}

void BulletManager::HitEnemy()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
		if ((*itr)->TYPE() == BULLET_TYPE::TYPE_ENEMY)
		{
			itr++;
			continue;
		}

			
		if (mpEnemyManager != nullptr)
		{
			if (mpEnemyManager->HitEnemy(itr) == true)
			{
				mpEffect->Play((*itr)->GetPosX(), (*itr)->GetPosY(), EFFECT_NUM::EFFECT_2);
				PlaySoundMem(mHitSE, DX_PLAYTYPE_BACK, TRUE);

				(*itr)->Finalize();
				delete (*itr);
				(*itr) = nullptr;
				itr=mpBullet.erase(itr);
				continue;
			}
		}
		itr++;
	}
}

void BulletManager::HitPlayer()
{
	for (std::list<Bullet*>::iterator itr = mpBullet.begin(); itr != mpBullet.end();)
	{
		if ((*itr) == nullptr)
		{
			itr++;
			continue;
		}
		if ((*itr)->TYPE() == BULLET_TYPE::TYPE_PLAYER)
		{
			itr++;
			continue;
		}
			
		if (mpPlayer != nullptr)
			if (mpPlayer->Active() == false)
			{
				itr++;
				continue;
			}
				

		if ((*itr)->Collision().CheckHit(mpPlayer->Collision()) == false)
		{
			itr++;
			continue;
		}
			
		if (mpEffect != nullptr)
			mpEffect->Play((*itr)->GetPosX(), (*itr)->GetPosY(), EFFECT_NUM::EFFECT_2);
		mpPlayer->IsDamage();
		PlaySoundMem(mHitSE, DX_PLAYTYPE_BACK, TRUE);

		if ((*itr)->Collision().CheckHit(mpPlayer->Collision()) == true)
		{
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr = mpBullet.erase(itr);
			continue;
		}
		
		itr++;
	}
}