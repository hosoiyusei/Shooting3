#pragma once
#include"../../../Utility.h"
#include"../BulletType.h"
#include"../../Collision/Collision.h"

class Stage;

class Bullet
{
public:

	virtual ~Bullet() = default;

	virtual void Initialize(Stage* pStage,
		float ShooterPosX,
		float ShooterPosY,
		float ShotPosX,
		float ShotPosY,
		float TargetPosX,
		float TargetPosY,
		BULLET_TYPE type) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual float GetPosX() = 0;
	virtual float GetPosY() = 0;

	virtual BULLET_TYPE TYPE() = 0;

	virtual CircleCollider Collision() = 0;
};