
#include "pch.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamPreliminaryAction.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Object/Enemy/Beam/Beam.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"
#include "Game/Object/Enemy/Beam/BeamChargeEffect.h"

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //�����̌����Ă������

//�\������̂��ߎ���
const float PRELIMINARYACTIONTIME = 2.0f;

// �R���X�g���N�^
BeamPreliminaryAction::BeamPreliminaryAction()
	:
	m_commonResources{}

{



}

// �f�X�g���N�^
BeamPreliminaryAction::~BeamPreliminaryAction()
{

}

// ����������
void BeamPreliminaryAction::Initialize()
{
}


// �X�V����
void BeamPreliminaryAction::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//m_beam->GetBeamEnergyBall()->Update(elapsedTime);


	//�i�s���������߂�
	float t = m_time / m_beam->GetBeamParamater()->AccumulationTime;

	t = std::min(t, 1.0f);

	//�T�C�Y�̕��
	Vector3 scale = Vector3::Lerp(m_beam->GetBeamParamater()->InitialScale, m_beam->GetBeamParamater()->MaxScale, t);

	m_beam->GetBeamEnergyBall()->SetScale(scale);

	std::vector<std::unique_ptr<BeamChargeEffect>>& effect = m_beam->GetBeamChargeEffect();

	for (auto& eff : effect)
	{
		eff->Update(elapsedTime);

	}



	if (m_particleCreateTime >= m_beam->GetBeamParamater()->ChargeEffectCreateTime)
	{
		m_beam->CreateParticle();
		m_particleCreateTime = 0;
	}


	if (m_time > m_beam->GetBeamParamater()->MaxPreliminaryActionTime)
	{
		m_beam->ChangeState(m_beam->GetBeamAttack());
	}

	m_time += elapsedTime;
	m_particleCreateTime += elapsedTime;
}


void BeamPreliminaryAction::Enter()
{

	m_time = 0;

	m_particleCreateTime = 0;

	m_beam->CreateParticle();

	m_beam->SetClassState(Beam::CurrentClassState::PreliminaryAction);

	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;



	////m_beam->GetBeamEnergyBall()->SetPosition(m_beam->GetPosition());
	m_beam->GetBeamEnergyBall()->SetPosition(pos);

}

void BeamPreliminaryAction::Exit()
{
	m_beam->DeleteParticle();
}

void BeamPreliminaryAction::RegistrationInformation(CommonResources* resoure, Beam* beam)
{
	m_commonResources = resoure;
	m_beam = beam;

}

