#include "pch.h"
#include "DetectionCollision2.h"



//�֐��̓o�^
std::unordered_map<int, std::function<bool(ColliderComponent& object1, ColliderComponent& object2)>> DetectionCollision2::m_checkCollisionFunction = {
	{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::AABB,    DetectionCollision2::AABB_AABB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::OBB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::OBB_OBB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::SPHERE | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::SPHERE_SPHERE_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::AABB_OBB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::AABB_SPHERE_CheckCollision}

};

std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(ColliderComponent& Collider1, ColliderComponent& Collider2)>> DetectionCollision2::m_extrusionFunction = {
	{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::AABB,    DetectionCollision2::AABB_AABB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::OBB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::OBB_OBB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::SPHERE | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::SPHERE_SPHERE_Extrusion}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::AABB_OBB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::AABB_SPHERE_Extrusion}
};


/// <summary>
/// �����������ǂ����̃`�F�b�N 
/// </summary>
/// <param name="collider1">�R���C�_�[�P</param>
/// <param name="collier2">�R���C�_�[�Q</param>
/// <returns>true : ��������  false : �������ĂȂ�</returns>
bool DetectionCollision2::ChecOnCollision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	bool isHit = false;

	//���̃f�[�^�ɉe����^���Ȃ����߁@����ւ������邽��
	ColliderComponent* localObject1 = collider1;
	ColliderComponent* localObject2 = collider2;

	//���ёւ��@�������ق���Object1�ɂ���悤�ɂ���
	(int)localObject1->GetCollisionTag() > (int)localObject2->GetCollisionTag() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionTag() | (int)localObject2->GetCollisionTag();

	//�����蔻��̎�ނ����邩
	auto it = m_checkCollisionFunction.find(type);


	if (it != m_checkCollisionFunction.end())
	{
		//����Γo�^���ꂽ�֐����Ă�
		isHit = m_checkCollisionFunction[type](*localObject1, *localObject2);
	}

	//�������Ă��Ȃ�
	return isHit;

}



const DirectX::SimpleMath::Vector3 DetectionCollision2::Extrusion(ColliderComponent* collider1, ColliderComponent* collider2)
{
	using namespace DirectX::SimpleMath;

	//���̃f�[�^�ɉe����^���Ȃ����߁@����ւ������邽��
	ColliderComponent* localObject1 = collider1;
	ColliderComponent* localObject2 = collider2;

	//���ёւ��@�������ق���Object1�ɂ���悤�ɂ���
	(int)localObject1->GetCollisionTag() > (int)localObject2->GetCollisionTag() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionTag() | (int)localObject2->GetCollisionTag();

	//�����蔻��̎�ނ����邩
	auto it = m_extrusionFunction.find(type);


	if (it != m_extrusionFunction.end())
	{
		//����Γo�^���ꂽ�֐����Ă�
		return m_extrusionFunction[type](*localObject1, *localObject2);
	}

	//�������Ă��Ȃ�
	return Vector3::Zero;
	

}

//�t���[�X�^�C���@�@�T�N�V�[�h

/// <summary>
/// AABB���m�̔���
/// </summary>
/// <param name="collider1">�R���C�_�[�P</param>
/// <param name="collider2">�R���C�_�[�Q</param>
/// <returns>true : ��������  false : �������ĂȂ�</returns>
bool DetectionCollision2::AABB_AABB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{

	using namespace DirectX;

	//AABB�ɃL���X�g
	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);
	//�X�t�B�A�̎擾
	BoundingSphere* sphere1 = aabb1.GetBoundingSphere();
	BoundingSphere* sphere2 = aabb2.GetBoundingSphere();
	//�X�t�B�A�̔���
	if (!sphere1->Intersects(*sphere2))
	{
		return false;
	}

	//�f�[�^�̎擾
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingBox* Box2 = aabb2.GetBoundingBox();

	//����
	if (Box1->Intersects(*Box2))
	{
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}

bool DetectionCollision2::OBB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{

	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

bool DetectionCollision2::SPHERE_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

bool DetectionCollision2::AABB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	using namespace DirectX;


	//AABB�ɃL���X�g
	AABB& aabb1 = static_cast<AABB&>(collider1);
	OBB& aabb2 = static_cast<OBB&>(collider2);
	//�X�t�B�A�̎擾
	BoundingSphere* sphere1 = aabb1.GetBoundingSphere();
	BoundingSphere* sphere2 = aabb2.GetBoundingSphere();
	//�X�t�B�A�̔���
	if (!sphere1->Intersects(*sphere2))
	{
		return false;
	}

	////�f�[�^�̎擾
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingOrientedBox* Box2 = aabb2.GetBoundingOrientedBox();

	//����
	if (Box1->Intersects(*Box2))
	{
		//��������
		return true;
	}


	return false;
}

bool DetectionCollision2::AABB_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

/// <summary>
/// AABB���m�̉����o���̌v�Z
/// </summary>
/// <param name="collider1">�R���C�_�[�P</param>
/// <param name="collider2">�R���C�_�[�Q</param>
/// <returns>�����o����</returns>
DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_AABB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//AABB�ɃL���X�g
	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);

	//�{�b�N�X�̎擾
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingBox* Box2 = aabb2.GetBoundingBox();

	Vector3 Min1 = Box1->Center - Box1->Extents;
	Vector3 Max1 = Box1->Center + Box1->Extents;
	Vector3 Min2 = Box2->Center - Box2->Extents;
	Vector3 Max2 = Box2->Center + Box2->Extents;

	//�e���̍����̌v�Z
	float dx1 = Max2.x - Min1.x;
	float dx2 = Min2.x - Max1.x;
	float dy1 = Max2.y - Min1.y;
	float dy2 = Min2.y - Max1.y;
	float dz1 = Max2.z - Min1.z;
	float dz2 = Min2.z - Max1.z;

	//�e���̐�Βl�̏������������̂߂荞�݂ɂ���
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// �����߂��x�N�g��
	Vector3 pushBackVec = Vector3::Zero;

	// �߂荞�݂���ԏ��������������߂�
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	return pushBackVec;

}

DirectX::SimpleMath::Vector3 DetectionCollision2::OBB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::SPHERE_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}
