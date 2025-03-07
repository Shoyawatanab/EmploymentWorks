/*
	@file	Pillar.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Pillar.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
Pillar::Pillar(CommonResources* resources)
	:
	MoveEntity(resources,Vector3::One,Vector3::Zero,Quaternion::Identity)
	,m_initialScale{}
	
{
	BaseEntity::SetIsEntityActive(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Pillar::~Pillar()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void Pillar::Initialize()
{
	MoveEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Beam.cmo", *fx);

	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), 2.0f);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), BaseEntity::GetScale());

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void Pillar::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	MoveEntity::Render(view, projection);

	//���f���̕`��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//m_bounding->DrawBoundingSphere(view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);



}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Pillar::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


}

void Pillar::AddCollision(CollisionManager* collsionManager)
{
}

void Pillar::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
}




void Pillar::ChangeState(IState* nextState)
{
}






