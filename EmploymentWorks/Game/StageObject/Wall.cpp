/*
	@file	Wall.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Wall.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Wall::Wall(CommonResources* resources
	,DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	,INotMoveEntity(resources,scale,position,rotation)
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Wall::~Wall()
{
	// do nothing.
}


void Wall::Initialize()
{

	INotMoveEntity::Initialize();


	// ���f����ǂݍ���
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Wall");

	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), 50.0f);

	//��]���܂߂��͈͂����߂�
	Vector3 Extents = Vector3::Transform(BaseEntity::GetScale(), BaseEntity::GetRotation());
	//AABB�Ń}�C�i�X���ƃ_��������
	Extents.x = std::abs(Extents.x);
	Extents.y = std::abs(Extents.y);
	Extents.z = std::abs(Extents.z);

	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Extents);

}

void Wall::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	INotMoveEntity::Render(view, projection);

	//���f���̕`��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//m_bounding->DrawBoundingSphere(view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);
}

void Wall::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	INotMoveEntity::Update(elapsedTime);


}

void Wall::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(tag);

}





//---------------------------------------------------------
