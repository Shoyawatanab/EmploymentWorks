/*
	@file	Boomerang.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Boomerang.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/Microsoft/DebugDraw.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"


const float SCALE = 4.0f; //�I�u�W�F�N�g�̑傫��


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Boomerang::Boomerang()
	:
	m_player{},
	m_commonResources{},
	m_model{},
	m_position{},
	m_currentState{},
	m_idling{},
	m_throw{},
	m_scale{},
	m_enemy{},
	m_orbit{}
	, m_repelled{}
	, m_previousFramePos{}
	, m_drop{}
	,m_onCollisionTag{}
	,m_useState{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Boomerang::~Boomerang()
{
	// do nothing.

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Boomerang::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	
	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *fx);


	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_idling->Initialize();
	m_throw->Initialize();
	m_getReady->Initialize();

	m_repelled->Initialize();

	m_drop->Initialize();


	m_currentState = m_idling.get();
	
	m_position = m_player->GetPosition();
	m_scale = SCALE;

	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.2f, 0.5f, 0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 0.9f);

	m_orbit = std::make_unique<BoomerangOrbit>(this, m_player, m_enemy);
	m_orbit->Initialize(m_commonResources);

	m_onCollisionTag = CollsionObjectTag::None;

	m_useState = UseState::Stock;



}


//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Boomerang::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);

	m_previousFramePos = m_position;

	m_currentState->Update(elapsedTime);

	if (m_currentState == m_getReady.get())
	{
		m_orbit->Update(elapsedTime);

	}

	m_bounding->Update(m_position);


}


//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Boomerang::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();



	// ���f����`�悷��
	m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	if (m_currentState == m_getReady.get())
	{
		m_orbit->Render();

	}



	// �v���~�e�B�u�`����J�n����


	//// �f�o�b�O����\������
	//auto debugString = m_commonResources->GetDebugString();
	////debugString->AddString("Rotate : %f", m_rotate.x);
	//debugString->AddString("BoomeerangSpherePos : %f, %f, %f", m_position.x, m_position.y, m_position.z);
	//debugString->AddString("BoomerangRotate : %f, %f, %f", m_rotate.x, m_rotate.y, m_rotate.z);

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Boomerang::Finalize()
{
	// do nothing.
}

void Boomerang::ChangeState(IBoomerangState* nextState)
{
	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();
}

void Boomerang::DemandBounceDirection(DirectX::SimpleMath::Vector3 pos, CollsionObjectTag& tag)
{

	switch (tag)
	{
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::NotMoveObject:
			m_bounceDirection = m_position - pos;
			break;
		case CollsionObjectTag::Wall:
			m_bounceDirection = m_previousFramePos - m_position;
			break;
		case CollsionObjectTag::Floor:
			break;
		default:
			break;
	}


}


void Boomerang::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	switch (PartnerTag)
	{
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Floor:
			if (m_currentState == m_repelled.get())
			{
				ChangeState(m_drop.get());
			}
			break;
		case CollsionObjectTag::NotMoveObject:
			DemandBounceDirection(Pos, PartnerTag);

			if (m_currentState == m_throw.get())
			{
				//�e����鏈���ɐ؂�ւ�
				ChangeState(m_repelled.get());
			}
			break;
		case CollsionObjectTag::Wall:
			DemandBounceDirection(Pos, PartnerTag);
			if (m_currentState == m_throw.get())
			{
				ChangeState(m_repelled.get());
			}
			break;
		default:
			break;
	}



}

void Boomerang::RegistrationInformation(Player* player, Enemy* enemy)
{

	m_player = player;
	m_enemy = enemy;

	m_idling->RegistrationInformation(this, m_player);
	m_throw->RegistrationInformation(this, m_player, m_enemy);
	m_getReady->RegistrationInformation(this, m_player);
	m_repelled->RegistrationInformation(this);
	m_drop->RegistrationInformation(this);
	
}

void Boomerang::Instances()
{

	m_idling = std::make_unique<BoomerangIdling>();
	m_throw = std::make_unique<BoomerangThrow>();
	m_getReady = std::make_unique<BoomerangGetReady>();
	m_repelled = std::make_unique<BoomerangRepelled>();
	m_drop = std::make_unique<BoomerangDrop>();
	m_bounding = std::make_unique<Bounding>();


}





// ���`��Ԃ��s��
DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}
void Boomerang::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}
