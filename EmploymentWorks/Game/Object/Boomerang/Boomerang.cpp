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
#include "FrameWork/Resources.h"
#include "Libraries/MyLib/CollisionMesh.h"


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
	,m_ray{}
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
	

	// ���f����ǂݍ���
	//m_model = Resources::GetInstance()->GetBoomerangModel();

		// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> boomerangFx = std::make_unique<DirectX::EffectFactory>(device);
	boomerangFx->SetDirectory(L"Resources/Models");
	// �u�u�[�������v���f�������[�h����
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *boomerangFx);


	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_idling->Initialize();
	m_throw->Initialize();
	m_getReady->Initialize();

	m_repelled->Initialize();

	m_drop->Initialize();


	m_currentState = m_idling.get();
	
	m_position = m_player->GetPosition();
	m_scale = SCALE;

	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.5f, 0.2f, 0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 0.9f);

	m_orbit = std::make_unique<BoomerangOrbit>(this, m_player, m_enemy);
	m_orbit->Initialize(m_commonResources);

	m_onCollisionTag = CollsionObjectTag::None;

	m_useState = UseState::Stock;

	// �R���W�������b�V���𐶐�����
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	//��̃��b�V���̓ǂݍ���
	m_collisionMesh->Initialize(device, context, L"Rock", m_position, 3.0f);


	for (int i = 0; i < 3; i++)
	{
		//90Ray�̏����p�x�@

		float a = 90 + (120 * i);

		auto ray = std::make_unique<RayParameter>();
		ray->TipPosition.x = (0.12f) * std::cos(DirectX::XMConvertToRadians(a));
		ray->TipPosition.z = (0.12f) * std::sin(DirectX::XMConvertToRadians(a));
		ray->InitialPosition = ray->TipPosition;

		m_ray.push_back(std::move(ray));

	}


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

	for (auto& ray : m_ray)
	{
		ray->BoomerangCenter = m_position;
		ray->TipPosition = Vector3::Transform(ray->InitialPosition, m_currentState->GetMatrix());

	}

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


	for (int i = 0; i < 3; i++)
	{

		//1�u�[��������Matrix��Ray�ɂ��K�p
	}


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
		case CollsionObjectTag::Floor:
		case CollsionObjectTag::Rock:
		case CollsionObjectTag::Tree1:
			m_bounceDirection = m_previousFramePos - m_position;

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
		case CollsionObjectTag::Rock:
		case CollsionObjectTag::Tree1:
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
