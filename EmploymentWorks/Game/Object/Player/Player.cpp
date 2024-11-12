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
#include "Game/Object/Player/PlayerParts/PlayerBody.h"

//const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION( 0.0f,0.0f,-1.0f); //�����̌����Ă������

const DirectX::SimpleMath::Vector3 EYE_TO_POSITION_DIFFERENCE(0.0f, 0.7f, 0.0f); //���W�Ɩڂ̍��W�̍���

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player(CommonResources* resources, IComponent* parent, const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m_commonResources{resources},
	m_scale{initialScale},
	m_rotate{},
	m_initialRotate{initialAngle},
	m_position{initialPosition},
	m_direction{INITIAL_DIRECTION},
	m_enemy{ },
	m_graivty{},
	m_isLockOn{}
	,m_currentState{}
	,m_hp{}
	,m_boomerangIndex{}
	,m_scrollWheelValue{}
	,m_attack{}
	,m_jump{}
	,m_velocity{}
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
void Player::Initialize()
{
	using namespace DirectX::SimpleMath;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	m_eyePosition = m_position + EYE_TO_POSITION_DIFFERENCE;
	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.4f, 0.6f, 0.4f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

	//�X�g�b�N
	for (auto& boomerang : m_boomerang)
	{
		boomerang->Initialize(m_commonResources);
	}

	//����
	m_usually->Initialize();
	//�U��
	m_attack->Initialize();
	//�W�����v
	m_jump->Initialize();
	//������΂�
	m_blownAway->Initialize();
	//�������
	m_idling->Initialize();


	m_currentState = m_idling.get();


	m_graivty = 0.05f;
	m_isLockOn = false;

	m_isJump = false;
	m_hp = 3;
	
	m_isInvincible = false;
	m_invincibleTime = 0;


	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);;

	m_boomerangIndex = 0;

	m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);


	//�uHead�v�𐶐�����
	Attach(std::make_unique<PlayerBody>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.0f, 0.0f, 0.0f),
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	const auto& state = m_commonResources->GetInputManager()->GetMouseState();



	//�������Ă���u�[��������Stock��ԂȂ�
	if (m_boomerang[m_boomerangIndex]->GetUseState() == Boomerang::UseState::Stock)
	{
		m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
	}

	// �}�E�X�̃z�C�[���l���擾
	m_scrollWheelValue = state.scrollWheelValue;

	if (m_scrollWheelValue > 0)
	{
		//�ύX�O�̃u�[������
		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				break;
			case Boomerang::UseState::Have:
			case Boomerang::UseState::GetReady:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
				m_boomerang[m_boomerangIndex]->ChangeState(m_boomerang[m_boomerangIndex]->GetBoomerangIdling());
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		//�g�p���̃u�[��������؂�ւ���
		m_boomerangIndex++;
		m_boomerangIndex = std::min(m_boomerangIndex, 2);

		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
				break;
			case Boomerang::UseState::Have:
			
				break;
			case Boomerang::UseState::GetReady:
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		Mouse::Get().ResetScrollWheelValue();


		if (m_currentState != m_jump.get())
		{
			m_currentState = m_idling.get();

		}

	}
	if (m_scrollWheelValue < 0)
	{

		//�ύX�O�̃u�[������
		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				break;
			case Boomerang::UseState::Have:
			case Boomerang::UseState::GetReady:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
				m_boomerang[m_boomerangIndex]->ChangeState(m_boomerang[m_boomerangIndex]->GetBoomerangIdling());

				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		m_boomerangIndex--;
		m_boomerangIndex = std::max(m_boomerangIndex, 0);

		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
				break;
			case Boomerang::UseState::Have:
				break;
			case Boomerang::UseState::GetReady:
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}



		Mouse::Get().ResetScrollWheelValue();

		if (m_currentState != m_jump.get())
		{
			m_currentState = m_idling.get();

		}


	}

	m_currentState->Update(elapsedTime);
	m_usually->Update(elapsedTime);

	//�ڂ̍��W�̍X�V
	m_eyePosition = m_position + EYE_TO_POSITION_DIFFERENCE;


	for (auto& boomerang : m_boomerang)
	{
		boomerang->Update(elapsedTime);

	}



	for(std::unique_ptr<Boomerang>& boomerang : m_boomerang)
	{


		//�u�[�������������Ă���Ȃ�
		if(boomerang->GetBoomerangState() == boomerang->GetBoomerangDrop())
		{

			float distance = DirectX::SimpleMath::Vector3::Distance(boomerang->GetPosition(), m_position);

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

	//���G��Ԃ̎�
	if (m_isInvincible)
	{
		m_invincibleTime += elapsedTime;

		//���G��Ԃ��I��邩�ǂ���
		if (m_invincibleTime > 3)
		{
			m_invincibleTime = 0;
			m_isInvincible = false;
		}

		//���������
		if (static_cast<int>(m_invincibleTime) % 2 == 0)
		{
			m_isVisible = false;
		}
		else
		{
			m_isVisible = true;
		}
	}


	m_bounding->Update(m_position);

	//���i���X�V����
	PlayerBase::Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	using namespace DirectX::SimpleMath;

	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();

	//	�������`��w��
	//ID3D11BlendState* blendstate = states->NonPremultiplied();

	//// ���f����`�悷��
	//m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection,
	//	false,
	//	[&]()
	//	{

	//		//DirectX::Colors::White.v;

	//		//DirectX::FXMVECTOR colorValues {1.0f, 1.0f, 1.0f, 0.5f};

	//		//m_basicEffect->SetDiffuseColor(colorValues);

	//		//// �u�����h�X�e�[�g��ݒ肷��
	//		//context->OMSetBlendState(blendstate, nullptr, 0xffffffff);

	//		//context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//		//	�V�F�[�_�̓o�^���������Ă���
	//		//context->PSSetShader(nullptr, nullptr, 0);

	//	}
	//);
	
	if (!m_isInvincible)
	{

		//���i��`�悷��
		PlayerBase::Render(view, projection);

		m_bounding->DrawBoundingBox(m_position, view, projection);
		//m_bounding->DrawBoundingSphere(m_position, view, projection);

		for (auto& boomerang : m_boomerang)
		{
			//�g�p���Ă���u�[������
			if (boomerang->GetUseState() != Boomerang::UseState::Stock)
			{
				boomerang->Render(view, projection);
			}
		}
	}
	else
	{
		//�_��
		if (m_isVisible)
		{
			for (auto& boomerang : m_boomerang)
			{

				//���i��`�悷��
				PlayerBase::Render(view, projection);

				m_bounding->DrawBoundingBox(m_position, view, projection);

				//�g�p���Ă���u�[������
				if (boomerang->GetUseState() != Boomerang::UseState::Stock)
				{

					boomerang->Render(view, projection);


				}

			}


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


void Player::RegistrationInformation(Enemy* enemy, mylib::TPS_Camera* tps_Camera, PlayScene* playScene)
{
	m_enemy = enemy;
	m_tpsCamera = tps_Camera;

	m_usually->RegistrationInformation(m_commonResources, this);
	m_idling->RegistrationInformation(m_commonResources, this);
	m_attack->RegistrationInformation(m_commonResources, this);
	m_jump->RegistrationInformation(m_commonResources, this);
	m_blownAway->RegistrationInformation(m_commonResources, this);

	//�X�g�b�N
	for (auto& stock : m_boomerang)
	{
		stock->RegistrationInformation(this, m_enemy,playScene);
	}

}

void Player::Instances()
{

	//m_usingBoomerang = std::make_unique<Boomerang>();
	m_bounding = std::make_unique<Bounding>();
	m_usually = std::make_unique<PlayerUsually>();
	m_blownAway = std::make_unique<PlayerBlownAway>();

	m_attack = std::make_unique<PlayerAttack>();
	m_jump = std::make_unique<PlayerJump>();
	m_idling = std::make_unique<PlayerIdling>();

	
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
		case CollsionObjectTag::Floor:

			if (m_currentState == m_blownAway.get())
			{
				ChangeState(m_usually.get());
			}
			else if (m_currentState == m_jump.get())
			{
				ChangeState(m_idling.get());
			}
			


			m_velocity.y = 0;
			break;
		default:
			break;
	}


}
