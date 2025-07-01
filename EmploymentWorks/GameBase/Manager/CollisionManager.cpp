#include "pch.h"
#include "CollisionManager.h"
#include "GameBase/Component/Collider/ColliderComponent.h"
#include "GameBase/Component/Collider/DetectionCollision2.h"
#include <algorithm> 

/// <summary>
/// �R���|�[�l���g
/// </summary>
CollisionManager::CollisionManager()
	:
	m_colliderList{}
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update(const float& deltaTime)
{

	if (m_colliderList.empty()) { return; }


	for (int i = 0; i < m_colliderList.size() - 1; i++)
	{
		//�L���o�Ȃ��Ȃ�
		if (!m_colliderList[i]->GetActive())
		{
			continue;
		}

		for (int j = i + 1 ; j < m_colliderList.size(); j++)
		{
			//�L���ł��Ȃ��Ȃ�
			if (!m_colliderList[j]->GetActive()){continue;}
			//�����I�u�W�F�N�g�Ȃ�
			if (m_colliderList[i]->GetActor() == m_colliderList[j]->GetActor())	{continue;}
			//�Œ�I�u�W�F�N�g���m�Ȃ�
			if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::FIXED) { continue; }

			//�^�O�̎擾
			auto tag = m_colliderList[i]->GetActor()->GetObjectTag();

			//�����蔻����s��Ȃ��^�O�̎擾
			auto notHitObjectTag = m_colliderList[j]->GetNotHitObjectTag();

			//�����蔻����s��Ȃ��^�O�̔���
			if (std::find(notHitObjectTag.begin(), notHitObjectTag.end(), tag) != notHitObjectTag.end())
			{
				//�s��Ȃ�
				continue;
			}



			//�ړ��I�u�W�F�N�g���m
			if (m_colliderList[i]->GetCollisionType() == CollisionType::COLLISION && m_colliderList[j]->GetCollisionType() == CollisionType::COLLISION)
			{
				Collision_Collision(m_colliderList[i], m_colliderList[j]);
			}
			//�Œ�I�u�W�F�N�g���m
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::FIXED)
			{
				Fixed_Fixed(m_colliderList[i], m_colliderList[j]);
			}
			//���蔲���I�u�W�F�N�g���m
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::TRIGGER && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Trigger_Trigger(m_colliderList[i], m_colliderList[j]);
			}
			//�Œ�I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::COLLISION)
			{
				Fixed_Collision(m_colliderList[i], m_colliderList[j]);
			}
			//�Œ�I�u�W�F�N�g�Ƃ��蔲���I�u�W�F�N�g
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Fixed_Trigger(m_colliderList[i], m_colliderList[j]);
			}
			//�ړ��I�u�W�F�N�g�Ƃ��蔲���I�u�W�F�N�g
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::COLLISION && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Collision_Trigger(m_colliderList[i], m_colliderList[j]);
			}
		}
	}


}


/// <summary>
/// �R���C�_�[�̒ǉ�
/// </summary>
/// <param name="collider"></param>
void CollisionManager::AddCollider(ColliderComponent* collider)
{
	//���łɒǉ�����Ă��邩
	auto it = std::find(m_colliderList.begin(), m_colliderList.end(), collider);
	//�����
	if (it != m_colliderList.end())
	{
		return;
	}

	//�ǉ�
	m_colliderList.push_back(collider);

	//���ёւ�
	std::sort(
		m_colliderList.begin(),
		m_colliderList.end(),
		[](ColliderComponent* a, ColliderComponent* b) {
			return a->GetCollisionType() < b->GetCollisionType();  // ���������ɕ��ׂ�
		}
	);

}

/// <summary>
/// �R���C�_�[�̍폜
/// </summary>
/// <param name="collider"></param>
void CollisionManager::RemoveCollider(ColliderComponent* collider)
{
	//���łɒǉ�����Ă��邩
	auto it = std::find(m_colliderList.begin(), m_colliderList.end(), collider);

	//�Ȃ����
	if (it == m_colliderList.end())
	{
		return;
	}

	m_colliderList.erase(it);

}

void CollisionManager::Collision_Collision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	//�����蔻��t���O
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//�ʒm�𑗂�
	SendNotification(collider1, collider2,isHit);

}

void CollisionManager::Fixed_Fixed(ColliderComponent* collider1, ColliderComponent* collider2)
{
}

void CollisionManager::Trigger_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{
}

/// <summary>
/// �Œ�I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
/// </summary>
/// <param name="collider1">�R���C�_�[�P</param>
/// <param name="collider2">�R���C�_�[�Q</param>
void CollisionManager::Fixed_Collision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	using namespace DirectX::SimpleMath;
	//�����蔻��t���O
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//����������
	if (isHit)
	{
		//�������Ă�����
		//�߂荞�ݗʂ̌v�Z
		Vector3 pushVector = DetectionCollision2::Extrusion(collider1, collider2);
		//�����o���@���ёւ��Ă��邩��Q�������o���Ă����v
		//collider2->GetActor()->GetTransform()->Translate(-pushVector);
		collider2->SetPushBack(-pushVector);
	}

	//�ʒm�𑗂�
	SendNotification(collider1, collider2, isHit);
	


}

void CollisionManager::Fixed_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{

	//�����蔻��t���O
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);
	//�ʒm�𑗂�
	SendNotification(collider1, collider2, isHit);

}

void CollisionManager::Collision_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{

	//�����蔻��t���O
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//�ʒm�𑗂�
	SendNotification(collider1, collider2, isHit);


}

/// <summary>
/// �ʒm�𑗂�
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="isHit">�����蔻��̌���</param>
void CollisionManager::SendNotification(ColliderComponent* collider1, ColliderComponent* collider2,bool isHit)
{

	//����������
	if (isHit)
	{
		//���������I�u�W�F�N�g�̎擾
		std::vector<ColliderComponent*> ob = collider1->GetHitObject();

		//���łɓ������Ă��邩�ǂ���
		if (std::find(ob.begin(), ob.end(), collider2) != ob.end())
		{
			//�������Ă���ԌĂяo�����֐�
			collider1->GetActor()->OnCollisionStay(collider2);
			collider2->GetActor()->OnCollisionStay(collider1);
		}
		else
		{
			//���������������ĂԊ֐�
			collider1->GetActor()->OnCollisionEnter(collider2);
			collider2->GetActor()->OnCollisionEnter(collider1);
			//���������I�u�W�F�N�g�̃|�C���^��o�^
			collider1->SetHitObject(collider2);
			collider2->SetHitObject(collider1);

		}

	}
	//�������Ă��Ȃ��Ȃ�
	else
	{
		//�폜
		bool isDelete = collider1->DleteHitObject(collider2);
		
		//�폜�ł�����
		if (isDelete)
		{
			//���ꂽ���ɌĂԊ֐�
			collider1->GetActor()->OnCollisionExit(collider2);
			collider2->GetActor()->OnCollisionExit(collider1);

		}

	}



}
