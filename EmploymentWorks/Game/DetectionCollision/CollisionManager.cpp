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
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"
#include "Libraries/MyLib/CollisionMesh.h"

#include "Game/Object/Enemy/Beam.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CollisionManager::CollisionManager()
	:
	m_commonResources{},
	m_collsionObjects{},
	m_player{},
	m_enemy{}
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
		for (int j = i + 1; j < m_collsionObjects.size(); j++)
		{

			CollsionObjectTag tagI = m_collsionObjects[i]->GetCollsionTag();
			CollsionObjectTag tagJ = m_collsionObjects[j]->GetCollsionTag();

			uint32_t kind = static_cast<uint32_t>(tagI) | static_cast<uint32_t>(tagJ);



			if (kind == static_cast<uint32_t>(CollisionType::Player_Wall) ||
				kind == static_cast<uint32_t>(CollisionType::Boomerang_Wall) ||
				kind == static_cast<uint32_t>(CollisionType::Enemy_Wall)
				)
			{
				//����������
				if (WallExtrusion(m_collsionObjects[i], m_collsionObjects[j]))
				{
					m_collsionObjects[i]->OnCollisionEnter(tagJ, m_hitPosition);
					m_collsionObjects[j]->OnCollisionEnter(tagI, m_hitPosition);
				}
				continue;
			}



			if (!CheckIsSphere(m_collsionObjects[i], m_collsionObjects[j]))
			{
				continue;
			}

			if (!CheckIsBox(m_collsionObjects[i], m_collsionObjects[j]))
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
				case static_cast<uint32_t>(CollisionType::Enemy_Boomerang):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					break;
				case static_cast<uint32_t>(CollisionType::Player_NotMoveObject):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_NotMoveObject):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_NotMoveObject):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					break;
				case static_cast<uint32_t>(CollisionType::Player_Wall):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Wall):
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Wall):
					break;
				case static_cast<uint32_t>(CollisionType::Player_Floor):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Floor):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Floor):

					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				default:
					continue;
			}

			m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
			m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

		}
	}

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
			if (m_player->GetPlayerState() == m_player->GetPlayerUsually())
			{
				int hp = m_player->GetPlayerHP();
				hp--;
				m_player->SetPlayerHP(hp);
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
	Vector3 a = Object1->GetPos();
	a += pushBackVec;
	Object1->SetPos(a);


}

bool CollisionManager::CheckIsBox(ICollisionObject* Object1, ICollisionObject* Object2)
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
	Vector3 Direction = Object2->GetPos() - Object1->GetPos();
	Direction.Normalize();

	//Ray�̍쐬
	Ray ray{ Object1->GetPos(),Direction };


	if (m_collisionMesh->IntersectRay(ray, &m_hitPosition))
	{

		Object1->SetPos(m_hitPosition);

		return true;
	}

	return false;
}

