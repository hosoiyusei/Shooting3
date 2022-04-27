#include"Collision.h"

/*--------------------------------------------------------
�ق��̉~�Ƃ̓����蔻��
-----------------------------------------------------------*/
bool CircleCollider::CheckHit(CircleCollider collider)
{
	//2�_�̈ʒu�����_����x�N�g���ɂ���
	float x = collider.mPos.mX - mPos.mX;
	float y = collider.mPos.mY - mPos.mY;

	//�x�N�g���̒������v�Z
	float l = (x * x) + (y * y);

	//���a�̍��v���擾
	float circleLen = mRadius + collider.mRadius;

	//���a�̍��v��2�悷��(sqrt�͏������d�����ߎg��Ȃ����߂̏��u)
	circleLen *= circleLen;

	//�x�N�g����2�̉~�̔��a���Z����Γ������Ă���
	if (l <= circleLen)
	{
		return true;
	}

	return false;
}