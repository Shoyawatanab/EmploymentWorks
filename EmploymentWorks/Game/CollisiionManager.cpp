#include "pch.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/DetectionCollision.h"

#include "Libraries/WataLib/Bounding.h"

using namespace DirectX::SimpleMath;


std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2)>> CollisionManager::m_extrusionFunction = {
	{(int)CollisionEntity::CollisionType::AABB | (int)CollisionEntity::CollisionType::AABB,CollisionManager::AABB_AABB_Extrusion}

};




/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void CollisionManager::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

}

/// <summary>
/// �X�V
/// </summary>
void CollisionManager::Update()
{

	for (int i = 0; i < m_collisionObjects.size() - 1; i++)
	{
		//�A�N�e�B�u��ԂŔv�ꍇ
		if (!m_collisionObjects[i]->GetIsEntityActive())
		{
			continue;
		}

		//�����蔻����s��Ȃ�Tag�̎擾
		std::vector<CollisionEntity::CollisionTag> tags = m_collisionObjects[i]->GetNoHitDetectionTag();

		for (int j = i + 1; j < m_collisionObjects.size(); j++)
		{

			//�A�N�e�B�u��ԂŔv�ꍇ
			if (!m_collisionObjects[j]->GetIsEntityActive())
			{
				continue;
			}


			//Tag�̎擾
			CollisionEntity::CollisionTag tag = m_collisionObjects[j]->GetCollisionTag();

			//�����蔻����s��Ȃ����ǂ����̔���
			if (std::find(tags.begin(), tags.end(),tag) != tags.end())
			{
				//�s��Ȃ�
				continue;
			}

			bool isHit = false;

			//�����������ǂ���
			WataLib::DetectionCollision::CheckHit(m_collisionObjects[i], m_collisionObjects[j], isHit);
			
			//����������
			if (isHit)
			{
				//�����o��
				Extrusion(m_collisionObjects[i], m_collisionObjects[j]);

				//���������I�u�W�F�N�g�̎擾
				std::vector<CollisionEntity*> ob = m_collisionObjects[i]->GetHitObject();

				//���łɓ������Ă��邩�ǂ���
				if (std::find(ob.begin(), ob.end(), m_collisionObjects[j]) != ob.end())
				{
					//�����葱���Ă���Ƃ��̌ĂԊ֐�

				}
				else
				{
					//���������������ĂԊ֐�
					m_collisionObjects[i]->OnCollisionEnter(m_collisionObjects[j], m_collisionObjects[j]->GetCollisionTag());
					m_collisionObjects[j]->OnCollisionEnter(m_collisionObjects[i], m_collisionObjects[i]->GetCollisionTag());
					//���������I�u�W�F�N�g�̃|�C���^��o�^
					m_collisionObjects[i]->SetHitObject(m_collisionObjects[j]);

				}


			}
			//�������Ă��Ȃ��Ȃ�
			else
			{
				bool isDelete = false;
				m_collisionObjects[i]->DleteHitObject(m_collisionObjects[j],isDelete);
				//�폜�ł�����
				if (isDelete)
				{
					//���ꂽ���ɌĂԊ֐�

				}

			}



		}

	}

}

/// <summary>
/// �����蔻��̒ǉ�
/// </summary>
/// <param name="object">�ǉ�����N���X</param>
void CollisionManager::AddCollsion(CollisionEntity* object)
{

	m_collisionObjects.push_back(object);

}

/// <summary>
/// �����o��
/// </summary>
/// <param name="object1">�I�u�W�F�N�g�P</param>
/// <param name="object2">�I�u�W�F�N�g�Q</param>
void CollisionManager::Extrusion(CollisionEntity* object1, CollisionEntity* object2)
{

	int type = (int)object1->GetCollisionType() | (int)object2->GetCollisionType();

	//�����蔻��̎�ނ����邩
	auto it = m_extrusionFunction.find(type);


	if (it != m_extrusionFunction.end())
	{
		//����Γo�^���ꂽ�֐����Ă�
		m_extrusionFunction[type](object1,object2);

	}





}

/// <summary>
/// AABB�̉����o��
/// </summary>
/// <param name="object1">�I�u�W�F�N�g�P</param>
/// <param name="object2">�I�u�W�F�N�g�Q</param>
void CollisionManager::AABB_AABB_Extrusion(CollisionEntity* object1, CollisionEntity* object2)
{

	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = object2->GetBounding()->GetBoundingBox();


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

	//�����o�������邩�ǂ���
	if (object1->GetIsExtrusion())
	{
		Vector3 position = object1->GetPosition();

		position += pushBackVec;

		object1->SetPosition(position);
	}

	if (object2->GetIsExtrusion())
	{
		Vector3 position = object2->GetPosition();

		position -= pushBackVec;

		object2->SetPosition(position);
	}

}
