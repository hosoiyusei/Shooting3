#pragma once
#include"../../../Utility.h"
#include"../../Collision/Collision.h"

class Player;
class Stage;
class BulletManager;
class Effect;
class Grid;

class Enemy
{
public:

	virtual ~Enemy() = default;

	virtual void Initialize(
		Player* pPlayer,
		Stage* pStage,
		BulletManager* pBulletManager,
		Effect* pEffect, 
		Grid* pGrid,
		float x, 
		float y) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual void IsDamage() = 0;

	virtual bool Active() = 0;

	virtual VECTOR GetPos() = 0;

	virtual CircleCollider Collision() = 0;

	virtual int DeleteTimer() = 0;
};