
#include "pch.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamAttackEnd.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Object/Enemy/Beam/Beam.h"
#include "Game/Object/Enemy/Beam/BeamRays.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"

const float SPEED = 1.0f;                                        //収縮のスピード



float Lerp(float a, float b, float t) 
{
	return a + t * (b - a);
}

// コンストラクタ
BeamAttackEnd::BeamAttackEnd()
	:
	m_commonResources{}
{



}

// デストラクタ
BeamAttackEnd::~BeamAttackEnd()
{

}

// 初期化する
void BeamAttackEnd::Initialize()
{
}


// 更新する
void BeamAttackEnd::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;	


	float t = m_time / m_beam->GetBeamParamater()->ShrinkTime;

	Vector3 scale = m_beam->GetBeamRays()->GetScale();

	scale.x = Lerp(m_beam->GerBeamRaysParameter()->MaxScale.x, m_beam->GerBeamRaysParameter()->InitialScale.x, t);
	scale.y = Lerp(m_beam->GerBeamRaysParameter()->MaxScale.y, m_beam->GerBeamRaysParameter()->InitialScale.y, t);

	m_beam->GetBeamRays()->SetScale(scale);



	scale = m_beam->GetBeamEnergyBall()->GetScale();

	scale = Vector3::Lerp(m_beam->GetBeamParamater()->MaxScale, m_beam->GetBeamParamater()->InitialScale, t);

	scale.x = std::max(scale.x, m_beam->GetBeamParamater()->InitialScale.x);
	scale.y = std::max(scale.y, m_beam->GetBeamParamater()->InitialScale.y);
	scale.z = std::max(scale.z, m_beam->GetBeamParamater()->InitialScale.z);


	m_beam->GetBeamEnergyBall()->SetScale(scale);


	m_time += elapsedTime;
	m_time = std::min(m_time, m_beam->GetBeamParamater()->ShrinkTime);

	if (m_time == m_beam->GetBeamParamater()->ShrinkTime)
	{
		m_beam->ChangeState(m_beam->GetBeamIdling());
	}

}


void BeamAttackEnd::Enter()
{

	//xを太さとして取得　ｘ　ｙは同じ値
	//m_thickness = m_beam->GetBeamRays()->GetScale().x;

	m_time = 0;

	m_beam->SetClassState(Beam::CurrentClassState::AttackEnd);

}

void BeamAttackEnd::Exit()
{

}

void BeamAttackEnd::RegistrationInformation(CommonResources* resoure, Beam* beam)
{
	m_commonResources = resoure;
	m_beam = beam;

}

