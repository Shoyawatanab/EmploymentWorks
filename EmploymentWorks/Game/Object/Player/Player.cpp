/*
	@file	Player.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"

#include "Libraries/MyLib/Camera/TPS_Camera.h"

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION( 0.0f,0.0f,-1.0f); //�����̌����Ă������
//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_direction{INITIAL_DIRECTION},
	m_enemy{ },
	m_graivty{},
	m_isLockOn{}
	,m_currentState{}
	,m_hp{}
	,m_boomerangIndex{}
	,m_scrollWheelValue{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Player::~Player()
{
	// do nothing.



}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);

	m_position = position;

	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.4f, 0.8f, 0.4f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

	//�X�g�b�N
	for (auto& boomerang : m_boomerang)
	{
		boomerang->Initialize(m_commonResources);
	}



	m_usually->Initialize();

	m_blownAway->Initialize();

	m_currentState = m_usually.get();


	m_graivty = 0.05f;
	m_isLockOn = false;

	m_hp = 3;
	
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);;


	m_boomerangIndex = 0;

	m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Using);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(cameraRotation);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Using);

	// �}�E�X�̃z�C�[���l���擾
	m_scrollWheelValue = state.scrollWheelValue;

	if (m_scrollWheelValue > 0)
	{
		//�������Ă��Ȃ��Ȃ��Ԃ��X�g�b�N�ɖ߂�
		if (m_boomerang[m_boomerangIndex]->GetBoomerangState() == m_boomerang[m_boomerangIndex]->GetBoomerangIdling())
		{
			m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
		}

		//�g�p���̃u�[��������؂�ւ���
		m_boomerangIndex++;


		m_boomerangIndex = std::min(m_boomerangIndex, 2);

		//��Ԃ��g�p����
		m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Using);



		Mouse::Get().ResetScrollWheelValue();

	}
	if (m_scrollWheelValue < 0)
	{
		//�������Ă��Ȃ��Ȃ��Ԃ��X�g�b�N�ɖ߂�
		if (m_boomerang[m_boomerangIndex]->GetBoomerangState() == m_boomerang[m_boomerangIndex]->GetBoomerangIdling())
		{
			m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
		}



		m_boomerangIndex--;
		m_boomerangIndex = std::max(m_boomerangIndex, 0);

		//��Ԃ��g�p����
		m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Using);


		Mouse::Get().ResetScrollWheelValue();



	}

	m_currentState->Update(elapsedTime);



	for(std::unique_ptr<Boomerang>& boomerang : m_boomerang)
	{



		//�u�[�������������Ă���Ȃ�
		if(boomerang->GetBoomerangState() == boomerang->GetBoomerangDrop())
		{

			float distance = DirectX::SimpleMath::Vector3::Distance(boomerang->GetPos(), m_position);

			if(distance <= 1)
			{

				const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

				if (kbTracker->released.F)
				{

					boomerang->ChangeState(boomerang->GetBoomerangIdling());

					boomerang->SetUseState(Boomerang::UseState::Stock);

				}
			}
		}
	}

	for(auto& boomerang : m_boomerang)
	{
		boomerang->Update(elapsedTime);

	}

	
	//m_boomerang[m_boomerangIndex]->Update(elapsedTime);



}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{

	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//	�������`��w��
	//ID3D11BlendState* blendstate = states->NonPremultiplied();

	// ���f����`�悷��
	m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection,
		false,
		[&]()
		{

			//DirectX::Colors::White.v;

			//DirectX::FXMVECTOR colorValues {1.0f, 1.0f, 1.0f, 0.5f};

			//m_basicEffect->SetDiffuseColor(colorValues);

			//// �u�����h�X�e�[�g��ݒ肷��
			//context->OMSetBlendState(blendstate, nullptr, 0xffffffff);

			//context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	�V�F�[�_�̓o�^���������Ă���
			//context->PSSetShader(nullptr, nullptr, 0);

		}
	);
	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);

	for (auto& boomerang : m_boomerang)
	{

		//�g�p���Ă���u�[������
		if (boomerang->GetUseState() == Boomerang::UseState::Using)
		{

			boomerang->Render(view, projection);


		}

	}

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	// do nothing.
}

void Player::ChangeState(IPlayerState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


void Player::RegistrationInformation(Enemy* enemy)
{
	m_enemy = enemy;

	m_usually->RegistrationInformation(this);
	m_blownAway->RegistrationInformation(this);


	//�X�g�b�N
	for (auto& stock : m_boomerang)
	{
		stock->RegistrationInformation(this, m_enemy);
	}

}

void Player::Instances()
{

	//m_usingBoomerang = std::make_unique<Boomerang>();
	m_bounding = std::make_unique<Bounding>();
	m_usually = std::make_unique<PlayerUsually>();
	m_blownAway = std::make_unique<PlayerBlownAway>();

	
	//�X�g�b�N�̃u�[������
	for (int i = 0; i < 3; i++)
	{
		auto stock = std::make_unique<Boomerang>();
		stock->Instances();
		m_boomerang.push_back(std::move(stock));

	}

}

void Player::DemandBlownAwayDirection(DirectX::SimpleMath::Vector3 pos)
{

	m_blownAwayDirection = m_position - pos;

	m_blownAwayDirection.Normalize();

	//m_position += m_blownAwayDirection;
}




void Player::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	//m_usingBoomerang->RegistrationCollionManager(collsionManager);

	for (auto& boomerang : m_boomerang)
	{
		boomerang->RegistrationCollionManager(collsionManager);
	}
}


void Player::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	//�����땔�W�F�N�g�̃^�O��
	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::NotMoveObject:
			break;
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Wall:
			break;
		case CollsionObjectTag::Floor:

			if (m_currentState == m_blownAway.get())
			{
				ChangeState(m_usually.get());
			}

			break;
		default:
			break;
	}


}
