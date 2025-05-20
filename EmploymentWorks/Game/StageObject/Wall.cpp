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


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
Wall::Wall(CommonResources* resources
	,DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	,INotMoveEntity(resources,scale,position,rotation)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void Wall::Initialize()
{
	using namespace DirectX::SimpleMath;

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

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
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


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Wall::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	INotMoveEntity::Update(elapsedTime);


}







//---------------------------------------------------------
