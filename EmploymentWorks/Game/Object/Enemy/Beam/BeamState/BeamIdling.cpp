
#include "pch.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Object/Enemy/Beam/Beam.h"
#include "Game/Object/Enemy/Beam/BeamRays.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"
#include "Game/Object/Enemy/Beam/BeamChargeEffect.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向


// コンストラクタ
Beamldling::Beamldling()
	:
	m_commonResources{}
{



}

// デストラクタ
Beamldling::~Beamldling()
{

}

// 初期化する
void Beamldling::Initialize()
{
}


// 更新する
void Beamldling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();
	if (kbTracker->released.Q)
	{
		//予備動作に移動
		m_beam->ChangeState(m_beam->GetBeamPreliminaryAction());
	}

	

}


void Beamldling::Enter()
{

	m_beam->SetClassState(Beam::CurrentClassState::Idling);

	m_beam->GetBeamRays()->SetScale(m_beam->GerBeamRaysParameter()->InitialScale);

	m_beam->GetBeamEnergyBall()->SetScale(m_beam->GetBeamParamater()->InitialScale);

	m_beam->GetBeamEnergyBall()->SetPosition(m_beam->GetPosition());

}

void Beamldling::Exit()
{
	m_beam->SetScale(m_beam->GetInitialScale());

}

void Beamldling::RegistrationInformation(CommonResources* resoure, Beam* beam)
{
	m_commonResources = resoure;
	m_beam = beam;

}

