#pragma once
#include"../../Utility.h"

//�~�̔���p�\����
struct CircleCollider
{
	//�ϐ�=====================================

	//���a
	float mRadius;

	//���W
	Float2 mPos;

	//�֐�======================================

	CircleCollider()
		:mRadius(0.0f)
		,mPos()
	{

	}

	//�ق��̉~�Ƃ̓����蔻��
	bool CheckHit(CircleCollider collider);
};