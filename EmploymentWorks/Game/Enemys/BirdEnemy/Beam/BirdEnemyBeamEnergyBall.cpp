/*
	@file	BirdEnemyBeamEnergyBall.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BirdEnemyBeamEnergyBall.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Game/Observer/Messenger.h"

#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BirdEnemyBeamEnergyBall::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
BirdEnemyBeamEnergyBall::BirdEnemyBeamEnergyBall(CommonResources* resources, BaseEntity* parent, BirdEnemyBeam* beam)
	:
	CollisionEntity(resources,Vector3::Zero, Vector3(0, 100, 0),Quaternion::Identity)
	,m_model{}
	,m_initialScale{}
	,m_iniialPosition{}
	,m_initialRotate{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_target{}
	,m_maxScale{}
	,m_beam{beam}
	,m_maxSizeTime{}
	,m_time{}
{
	BaseEntity::SetParent(parent);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamEnergyBall::~BirdEnemyBeamEnergyBall()
{
	// do nothing.
}


/// <summary>
/// ������
/// </summary>
void BirdEnemyBeamEnergyBall::Initialize()
{

	CollisionEntity::Initialize();


	// ���f����ǂݍ���
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BeamEnergyBall");

	m_maxScale = Params::BIRDENEMY_BEAM_BALL_MAX_SIZE;


	m_maxSizeTime = Params::BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME;

	m_time = 0;

	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), 1.0f);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Vector3(0.5, 0.5, 0.5));


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyBeamEnergyBall::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	//m_rotation = m_initialRotate;

	CollisionEntity::Render(view, projection);


	//���f����`�悷��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
		{
		});

	Vector3 scale;
	Quaternion roatation;

	Matrix a = BaseEntity::GetWorldMatrix();

	a.Decompose(scale, roatation, m_wordlPosition);

	CollisionEntity::GetBounding()->DrawBoundingSphere(m_wordlPosition, view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(m_wordlPosition, view, projection);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBeamEnergyBall::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	CollisionEntity::Update(elapsedTime);

}


/// <summary>
/// �����蔻��ɒǉ�
/// </summary>
/// <param name="collsionManager"></param>
void BirdEnemyBeamEnergyBall::AddCollision(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

/// <summary>
/// �����������ɌĂяo���֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BirdEnemyBeamEnergyBall::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Player:
		case CollisionEntity::CollisionTag::Stage:
		{
			m_beam->GetStateMahine()->ChangeState(m_beam->GetStateMahine()->GetBirdEnemyBeamIdle());

			//���W�����߂�
			Vector3 position = m_wordlPosition;
			Vector3 scale = Vector3::One;
			UnknownDataTwo aa = { &position , &scale };
			Messenger::GetInstance()->Notify(GameMessageType::CreateExplosion, &aa);

		}
		break;
		default:
			break;
	}
}




