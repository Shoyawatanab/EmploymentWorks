#include "pch.h"
#include "Boomerang.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Libraries/WataLib/CSV.h"
#include "Game/CollisiionManager.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Params.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
Boomerang::Boomerang(CommonResources* resources
	, BaseEntity* parent,
	DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_parent{parent}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_stateMachine{}
	,m_throwbasePosition{}
	,m_prevPosition{}
	,ItemEntity(resources,scale,position,rotation)
{

	m_stateMachine = std::make_unique<BoomerangStateMachine>();

	m_shadow = std::make_unique<WataLib::Shadow>();

	BaseEntity::SetParent(parent);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Boomerang::~Boomerang()
{
}

void Boomerang::OnAcquired()
{

	m_stateMachine->ChangeState(m_stateMachine->GetBoomerangIdel());

}

/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="targetMarker">�^�[�Q�b�g�}�[�J�[</param>
/// <param name="tpsCamera">TPS�J����</param>
void Boomerang::AddPointer(Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera)
{

	m_stateMachine->AddPointer(this,player,targetMarker,tpsCamera);

}

/// <summary>
/// ������
/// </summary>
void Boomerang::Initialize()
{
	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	ItemEntity::Initialize();

	//// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *fx);

	//CSV�������W�̎擾
	m_throwbasePosition = WataLib::CSV::LoadCSVBoomerang();

	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetBoomerangIdel());



	//���[���h�s��̌v�Z
	BaseEntity::SetWorldMatrix(Matrix::CreateScale(BaseEntity::GetScale()) *
		Matrix::CreateFromQuaternion(BaseEntity::GetRotation()) *
		Matrix::CreateTranslation(BaseEntity::GetPosition()));

	//�e�q�֌W������ΐe�̍s��̌v�Z���s��
	if (m_parent)
	{
		BaseEntity::SetWorldMatrix(BaseEntity::GetWorldMatrix() * m_parent->GetWorldMatrix());
	}

	Vector3 position;
	Vector3 scale;
	Quaternion rotation;

	Matrix matrix =  BaseEntity::GetWorldMatrix();
	matrix.Decompose(scale, rotation, position);


	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(position, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(position, Params::BOOMERANG_BOX_COLLIDER_SIZE);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	m_shadow->Initialize(device, context, states);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void Boomerang::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	ItemEntity::Render(view, projection);

	//���f���̕`��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);


	m_stateMachine->Render(view, projection);


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = 0.1f;


	if (m_stateMachine->GetCurrentState() != m_stateMachine->GetBoomerangIdel())
	{
		// ���@�̉e��`�悷��
		m_shadow->Render(context, states, view, projection, shadowPos, 0.5f);

	}

	m_prevPosition = BaseEntity::GetPosition();

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void Boomerang::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
			if (m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangRepelled())
			{
				m_stateMachine->ChangeState(m_stateMachine->GetBoomerangDrop());

			}
			break;
		case CollisionEntity::CollisionTag::Enemy:
			break;
		case CollisionEntity::CollisionTag::EnemyParts:
			break;
		case CollisionEntity::CollisionTag::Barrier:
			m_stateMachine->ChangeState(m_stateMachine->GetBoomerangRepelled());
			break;
		default:
			break;
	}


}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Boomerang::Update(const float& elapsedTime)
{
	ItemEntity::Update(elapsedTime);

	m_stateMachine->Update(elapsedTime);


}


