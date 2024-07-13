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

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"

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

			if (tagI == CollsionObjectTag::Player && tagJ == CollsionObjectTag::Boomerang ||
				tagJ == CollsionObjectTag::Player && tagI == CollsionObjectTag::Boomerang)
			{
				continue;
			}

			//�o�E���f�B���O�N���X�̎擾
			Bounding* bounding1 = m_collsionObjects[i]->GetBounding();
			Bounding* bounding2 = m_collsionObjects[j]->GetBounding();

			//�o�E���f�B���O�X�t�B�A�̎擾
			DirectX::BoundingSphere* Sphere1 = bounding1->GetBoundingSphere();
			DirectX::BoundingSphere* Sphere2 = bounding2->GetBoundingSphere();

			
			//�X�t�B�A���������Ă��邩�ǂ���
			//�O�Ɂ���u������G���[���������@���㗝������
			if (!Sphere1->Intersects(*Sphere2))
			{
				continue;
			}
			if (tagI != CollsionObjectTag::NotMoveObject || tagJ != CollsionObjectTag::NotMoveObject)
			{

			}

			//�X�t�B�A�̐F�̕ύX
			bounding1->SetIsSphereHit(true);
			bounding2->SetIsSphereHit(true);



			//�o�E���f�B���O�{�b�N�X�̎擾
			DirectX::BoundingBox* Box1 = bounding1->GetBoundingBox();
			DirectX::BoundingBox* Box2 = bounding2->GetBoundingBox();

			//�o�E���f�B���O�{�b�N�X�Ɠ����������ǂ���
			if (!Box1->Intersects(*Box2))
			{
				continue;
			}

			//�{�b�N�X�̐F�̕ύX
			bounding1->SetIsBoxHit(true);
			bounding2->SetIsBoxHit(true);


			if (tagI == CollsionObjectTag::Boomerang && tagJ == CollsionObjectTag::Enemy ||
				tagJ == CollsionObjectTag::Boomerang && tagI == CollsionObjectTag::Enemy)
			{

				m_collsionObjects[i]->OnCollision(tagJ);
				m_collsionObjects[j]->OnCollision(tagI);



				return;
			}


			//�{�b�N�X���m�̓����蔻��


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
			Vector3 a = m_collsionObjects[i]->GetPos();
			a += pushBackVec;
			m_collsionObjects[i]->SetPos(a);
	
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

