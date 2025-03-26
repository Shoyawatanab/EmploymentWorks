#include "pch.h"
#include "DetectionCollision.h"
#include "Libraries/WataLib/Bounding.h"

using namespace DirectX::SimpleMath;


std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)>> WataLib::DetectionCollision::m_detectionFunction = {
	{(int)CollisionEntity::CollisionType::AABB    | (int)CollisionEntity::CollisionType::AABB,    DetectionCollision::AABB_AABB}
	,{(int)CollisionEntity::CollisionType::OBB    | (int)CollisionEntity::CollisionType::OBB,     DetectionCollision::OBB_OBB}
	,{(int)CollisionEntity::CollisionType::SPHERE | (int)CollisionEntity::CollisionType::SPHERE,  DetectionCollision::SPHERE_SPHERE}
	,{(int)CollisionEntity::CollisionType::AABB   | (int)CollisionEntity::CollisionType::OBB,     DetectionCollision::AABB_OBB}
	,{(int)CollisionEntity::CollisionType::AABB   | (int)CollisionEntity::CollisionType::SPHERE,  DetectionCollision::AABB_SPHERE}

};


void WataLib::DetectionCollision::CheckHit(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{

	//���̃f�[�^�ɉe����^���Ȃ����߁@����ւ������邽��
	CollisionEntity* localObject1 = object1;
	CollisionEntity* localObject2 = object2;

	//���ёւ��@�������ق���Object1�ɂ���悤�ɂ���
	(int)localObject1->GetCollisionType() > (int)localObject2->GetCollisionType() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionType() | (int)localObject2->GetCollisionType();

	//�����蔻��̎�ނ����邩
	auto it = m_detectionFunction.find(type);

	
	if (it != m_detectionFunction.end())
	{
		//����Γo�^���ꂽ�֐����Ă�
		m_detectionFunction[type](localObject1, localObject2, isHit);

	}

}

void WataLib::DetectionCollision::AABB_AABB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//�X�t�B�A���m�̔���
	SPHERE_SPHERE(object1, object2,isHit);

	//�������Ă��Ȃ�
	if (!isHit)
	{
		//�t���O�𓖂����Ă��Ȃ���
		isHit = false;
		return;
	}

	//�t���O�𓖂����Ă��Ȃ���
	isHit = false;

	//�f�[�^�̎擾
	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = object2->GetBounding()->GetBoundingBox();

	//����
	if (Box1->Intersects(*Box2))
	{
		//��������
		isHit = true;
		return;
	}

	//�������ĂȂ�
	isHit = false;
}

void WataLib::DetectionCollision::OBB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{

	//�X�t�B�A���m�̔���
	SPHERE_SPHERE(object1, object2, isHit);

	//�������Ă��Ȃ�
	if (!isHit)
	{
		//�t���O�𓖂����Ă��Ȃ���
		isHit = false;
		return;
	}
	//�t���O�𓖂����Ă��Ȃ���
	isHit = false;

	//�f�[�^�̎擾
	DirectX::BoundingOrientedBox* Box1 = object1->GetBounding()->GetOrientedBox();
	DirectX::BoundingOrientedBox* Box2 = object2->GetBounding()->GetOrientedBox();

	//����
	if (Box1->Intersects(*Box2))
	{
		//��������
		isHit = true;
		return;
	}

	//�������ĂȂ�
	isHit = false;

}

void WataLib::DetectionCollision::SPHERE_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	DirectX::BoundingSphere* Sphere1 = object1->GetBounding()->GetBoundingSphere();
	DirectX::BoundingSphere* Sphere2 = object2->GetBounding()->GetBoundingSphere();

	//����
	if (Sphere1->Intersects(*Sphere2))
	{
		//��������
		isHit = true;
		return;
	}

	//�������ĂȂ�
	isHit = false;

}

void WataLib::DetectionCollision::AABB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//�X�t�B�A���m�̔���
	SPHERE_SPHERE(object1, object2, isHit);

	//�������Ă��Ȃ�
	if (!isHit)
	{
		//�t���O�𓖂����Ă��Ȃ���
		isHit = false;
		return;
	}
	//�t���O�𓖂����Ă��Ȃ���
	isHit = false;

	//�f�[�^�̎擾
	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingOrientedBox* Box2 = object2->GetBounding()->GetOrientedBox();

	//����
	if (Box1->Intersects(*Box2))
	{		
		//��������
		isHit = true;
		return;
	}

	//�������ĂȂ�
	isHit = false;

}

void WataLib::DetectionCollision::AABB_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//�X�t�B�A���m�̔���
	SPHERE_SPHERE(object1, object2, isHit);

	//�������Ă��Ȃ�
	if (!isHit)
	{
		//�t���O�𓖂����Ă��Ȃ���
		isHit = false;
		return;
	}
	//�t���O�𓖂����Ă��Ȃ���
	isHit = false;

	//�f�[�^�̎擾
	DirectX::BoundingBox* Box = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingSphere* Sphere = object2->GetBounding()->GetBoundingSphere();

	//����
	if (Box->Intersects(*Sphere))
	{
		//��������
		isHit = true;
		return;
	}

	//�������ĂȂ�
	isHit = false;

}

bool WataLib::DetectionCollision::Circle_RectCheckHit(const DirectX::SimpleMath::Vector2& circleCenter, float circleRadius,
	const DirectX::SimpleMath::Vector2& rectCenter, float rectWidth, float rectHeight)
{
	

	// �l�p�`�̋��E���W���v�Z
	float rectLeft = rectCenter.x - rectWidth / 2;
	float rectRight = rectCenter.x + rectWidth / 2;
	float rectTop = rectCenter.y - rectHeight / 2;
	float rectBottom = rectCenter.y + rectHeight / 2;

	// �~�̒��S�ɍł��߂��l�p�`�̓_�����߂�
	float closestX = std::max(rectLeft, std::min(circleCenter.x, rectRight));
	float closestY = std::max(rectTop, std::min(circleCenter.y, rectBottom));

	// �~�̒��S�ƍŋߐړ_�̋������v�Z
	Vector2 diff = circleCenter - Vector2(closestX, closestY);
	float distanceSquared = diff.LengthSquared();

	// �����蔻��i�����̓�悪���a�̓��ȉ��Ȃ�Փˁj
	return distanceSquared <= (circleRadius * circleRadius);

}
