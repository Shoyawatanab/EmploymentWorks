/*
	@file	CollisionManager.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "CollisionManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"
#include "Libraries/MyLib/CollisionMesh.h"

#include "Game/Object/Enemy/Beam.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CollisionManager::CollisionManager()
	:
	m_commonResources{},
	m_collsionObjects{},
	m_player{},
	m_enemy{}
	,m_tpsCamera{}
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Initialize(CommonResources* resources, Player* player, Enemy* enemy)
{

	m_commonResources = resources;
	m_player = player;
	m_enemy = enemy;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();



	// �R���W�������b�V���𐶐�����
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	//�傫�����[0.1���ĕǂɂ߂荞�܂Ȃ��悤�ɂ��Ă���
	m_collisionMesh->Initialize(device, context, L"Stage", DirectX::SimpleMath::Vector3::Zero, 7.9f);



}



//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void CollisionManager::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�o�E���f�B���O�̐F�̃��Z�b�g
	for (auto& object : m_collsionObjects)
	{
		object->GetBounding()->SetIsBoxHit(false);
		object->GetBounding()->SetIsSphereHit(false);

	}

	//�o�^���ꂽ�I�u�W�F�N�g�S�ĂƓ����蔻������
	for (int i = 0; i < m_collsionObjects.size() - 1; i++)
	{

		CollsionObjectTag tagI = m_collsionObjects[i]->GetCollsionTag();


		for (int j = i + 1; j < m_collsionObjects.size(); j++)
		{

			CollsionObjectTag tagJ = m_collsionObjects[j]->GetCollsionTag();

			uint32_t kind = static_cast<uint32_t>(tagI) | static_cast<uint32_t>(tagJ);



			//�X�t�B�A�̓����蔻��
			if (!CheckIsSphere(m_collsionObjects[i], m_collsionObjects[j]))
			{
				continue;
			}


			//�ǂ�ȏ���������̂�
			switch (kind)
			{
				case static_cast<uint32_t>(CollisionType::Player_Enemy):
					break;
				case static_cast<uint32_t>(CollisionType::Player_Boomerang):
					break;
				case static_cast<uint32_t>(CollisionType::Player_Stage):

					//�{�b�N�X�Ƃ̓����蔻��
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						//�����o������
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						//���ꂼ��̃N���X�̔���
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}
					break;
				case static_cast<uint32_t>(CollisionType::Player_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}
					break;
				case static_cast<uint32_t>(CollisionType::Player_Pillar):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}


					break;
				case static_cast<uint32_t>(CollisionType::Player_Artillery):
					break;
				case static_cast<uint32_t>(CollisionType::Player_ArtilleryBullet):
					break;


				case static_cast<uint32_t>(CollisionType::Enemy_Boomerang):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Stage):

					//if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					//{
					//	BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					//	m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
					//	m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					//}

					//�G�̂ق�����ɓo�^����Ă��邩�������J�@I�@�̏���
					if (CheckIsOrientexdBoxToBox(m_collsionObjects[j], m_collsionObjects[i]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						//�����o������
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Pillar):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Artillery):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_ArtilleryBullet):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;


				case static_cast<uint32_t>(CollisionType::Boomerang_Stage):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Pillar):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Artillery):

					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}
					break;

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_ArtilleryBullet):
					break;

				case static_cast<uint32_t>(CollisionType::ArtilleryBullet_Stage):
					
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;


				

				case static_cast<uint32_t>(CollisionType::EnemyParts_Boomerang):
					if (CheckIsOrientexdBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}
					break;
				default:
					continue;
			}

		}
	}

	BeamAndPlayerCollision();


	DirectX::SimpleMath::Vector3 targetPosition = m_tpsCamera->GetTargetPosition();
	DirectX::SimpleMath::Vector3 eyePosition = m_tpsCamera->GetEyePosition();

	float distance = Vector3::Distance(targetPosition, eyePosition);

	//�J�����̓����蔻��
	for (int i = 0; i < m_collsionObjects.size(); i++)
	{

		CollsionObjectTag tag = m_collsionObjects[i]->GetCollsionTag();


		//���̂ɂ����Ray�̒������ς�邩��tag�Ŕ��肷��
		switch (tag)
		{
			case CollsionObjectTag::Stage:
				CameraCollision(m_collsionObjects[i], distance);
				break;
			case CollsionObjectTag::Floor:
				CameraCollision(m_collsionObjects[i],distance);
				break;
			default:
				break;
		}


	}

}

/// <summary>
///�z��ɃI�u�W�F�N�g�̓o�^ 
/// </summary>
/// <param name="object"></param>
void CollisionManager::AddCollsion(ICollisionObject* object)
{
	m_collsionObjects.emplace_back(object);
}




/// <summary>
/// �����o������
/// </summary>
/// <param name="Object1">�����o�����I�u�W�F�N�g</param>
/// <param name="Object2">������Ȃ��I�u�W�F�N�g</param>
void CollisionManager::BoxExtrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = Object2->GetBounding()->GetBoundingBox();



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

	//�����o��
	//�������Ɖ�����鑤���ǂ����邩�@
	//���W�̍X�V�̎d��
	Vector3 a = Object1->GetPosition();
	a += pushBackVec;
	Object1->SetPosition(a);


}

/// <summary>
/// AABB�̓����蔻��
/// </summary>
/// <param name="Object1"></param>
/// <param name="Object2"></param>
/// <returns></returns>
bool CollisionManager::CheckIsBoxToBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = Object2->GetBounding()->GetBoundingBox();

	//�o�E���f�B���O�{�b�N�X�Ɠ����������ǂ���
	if (Box1->Intersects(*Box2))
	{
#ifdef _DEBUG

		//�{�b�N�X�̐F�̕ύX
		Object1->GetBounding()->SetIsBoxHit(true);
		Object2->GetBounding()->SetIsBoxHit(true);
#endif
		return true;
	}
	return false;

	
}

/// <summary>
/// OBB  BoundingBox To BoundingOrientexsBox
/// </summary>
/// <param name="Object1">BoundingBox</param>
/// <param name="Object2">BoundingOrientedBox</param>
/// <returns></returns>
bool CollisionManager::CheckIsOrientexdBoxToBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingOrientedBox* Box2 = Object2->GetBounding()->GetOrientedBox();

	//�o�E���f�B���O�{�b�N�X�Ɠ����������ǂ���
	if (Box1->Intersects(*Box2))
	{
#ifdef _DEBUG

		//�{�b�N�X�̐F�̕ύX
		Object1->GetBounding()->SetIsBoxHit(true);
		Object2->GetBounding()->SetIsBoxHit(true);
#endif
		return true;
	}

	return false;

}

/// <summary>
/// OBB  BoundingOrientexsBox To BoundingOrientexsBox
/// </summary>
/// <param name="Object1">BoundingOrientexsBox</param>
/// <param name="Object2">BoundingOrientexsBox</param>
/// <returns></returns>
bool CollisionManager::CheckIsOrientexdBoxToOrientexdBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingOrientedBox* Box1 = Object1->GetBounding()->GetOrientedBox();
	DirectX::BoundingOrientedBox* Box2 = Object2->GetBounding()->GetOrientedBox();

	//�o�E���f�B���O�{�b�N�X�Ɠ����������ǂ���
	if (Box1->Intersects(*Box2))
	{
#ifdef _DEBUG

		//�{�b�N�X�̐F�̕ύX
		Object1->GetBounding()->SetIsBoxHit(true);
		Object2->GetBounding()->SetIsBoxHit(true);
#endif
		return true;
	}

	return false;
}

bool CollisionManager::CheckIsSphere(ICollisionObject* Object1, ICollisionObject* Object2)
{

	//�o�E���f�B���O�X�t�B�A�̎擾
	DirectX::BoundingSphere* Sphere1 = Object1->GetBounding()->GetBoundingSphere();
	DirectX::BoundingSphere* Sphere2 = Object2->GetBounding()->GetBoundingSphere();

	//�X�t�B�A���������Ă��邩�ǂ���
	//�O�Ɂ���u������G���[���������@���㗝������
	if (Sphere1->Intersects(*Sphere2))
	{
#ifdef _DEBUG
		//�X�t�B�A�̐F�̕ύX
		Object1->GetBounding()->SetIsSphereHit(true);
		Object2->GetBounding()->SetIsSphereHit(true);
#endif
		return true;
	}

	return false;
}


//�ǂƂ̔���@�����ɉ����o��
bool CollisionManager::WallExtrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{
	using namespace DirectX::SimpleMath;

	//Ray�̕���
	Vector3 Direction = Object2->GetPosition() - Object1->GetPosition();
	Direction.Normalize();

	//Ray�̍쐬
	Ray ray{ Object1->GetPosition(),Direction };


	if (m_collisionMesh->IntersectRay(ray, &m_hitPosition))
	{

		Object1->SetPosition(m_hitPosition);

		return true;
	}

	return false;
}

void CollisionManager::BeamAndPlayerCollision()
{

	//�v���C���ƃr�[��
	if (m_player->GetPlayerState() != m_player->GetPlayerUsually() && !m_enemy->GetIsAttack())
	{
		return;
	}



	//�r�[����Boundin�̎擾
	std::vector<std::unique_ptr<Bounding>>& BeamBounding = m_enemy->GetBeam()->GetBounding();

	//�v���C����BoundingSphere�̎擾
	DirectX::BoundingSphere* PlayerBoundingSphere = m_player->GetBounding()->GetBoundingSphere();

	for (auto& beam : BeamBounding)
	{

		DirectX::BoundingSphere* Sphere = beam->GetBoundingSphere();

		//����������
		if (PlayerBoundingSphere->Intersects(*Sphere))
		{
			if (m_player->GetPlayerState() == m_player->GetPlayerUsually() && !m_player->GetIsInvincible())
			{
				float hp = m_player->GetPlayerHP();
				hp--;
				m_player->SetPlayerHP(hp);
				//�v���C���𖳓G��Ԃ�
				m_player->SetIsInvincible(true);

			}

			//��ԕ��������߂�
			m_player->DemandBlownAwayDirection(Sphere->Center);

			//�v���C���̏�Ԃ��΂����ɕύX
			m_player->ChangeState(m_player->GetPlayerBlownAway());

			return;
		}

	}


}

/// <summary>
/// �J�����Ƃ̓����蔻��
/// </summary>
/// <param name="object"></param>
void CollisionManager::CameraCollision(ICollisionObject* object, float rayDistance)
{


	DirectX::BoundingBox* box = object->GetBounding()->GetBoundingBox();


	DirectX::SimpleMath::Vector3 direction = m_tpsCamera->GetEyePosition() - m_tpsCamera->GetTargetPosition();
	direction.Normalize();
	//�J�����̍��W�ƒ����_����̐�����Ray�Ƃ��č쐬
	DirectX::SimpleMath::Ray ray { m_tpsCamera->GetTargetPosition(), direction };
	//Ray(����)�̋��������߂�
	float distance = DirectX::SimpleMath::Vector3::Distance(m_tpsCamera->GetEyePosition(), m_tpsCamera->GetTargetPosition());
	distance = 1;
	//�������Ă��Ȃ�
	if (!ray.Intersects(*box, distance))
	{
		return;
	}

	//�����ɂ���ē����������ǂ�������
	if (distance > rayDistance)
	{
		return;
	}

	//distance /= 4.5f;

	//�^�[�Q�b�g�̍��W���擾
	DirectX::SimpleMath::Vector3 pos = m_tpsCamera->GetTargetPosition();
	//�^�[�Q�b�g�ɕ����Ɠ����������������������̂𑫂���Eye�̍��W�����߂�
	pos += direction * distance;


	m_tpsCamera->SetEyePosition(pos);

}

