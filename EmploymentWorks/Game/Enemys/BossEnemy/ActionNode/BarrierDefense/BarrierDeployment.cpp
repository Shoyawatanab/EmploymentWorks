
#include "pch.h"
#include "BarrierDeployment.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierStateMachine.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BarrierDeployment::BarrierDeployment(BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier)
	:
	m_commonResources{}
	,m_barrierDefenseAction{ barrierDefenseAction }
	,m_barrier{barrier}
	,m_time{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierDeployment::~BarrierDeployment()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BarrierDeployment::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
IBehaviorNode::State BarrierDeployment::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	
	if (m_time >= 5.0f)
	{
		m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierClose());
	}
	else if (m_time >= 4.0f)
	{
		m_barrier->GetBarrierStateMachine()->ChangeState(m_barrier->GetBarrierStateMachine()->GetBarrierShrink());
	}


	m_time += elapsedTime;


	return IBehaviorNode::State::Runngin;

}




/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BarrierDeployment::Enter()
{
	m_time = 0;

	m_barrier->SetIsEntityActive(true);


}



/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BarrierDeployment::Exit()
{

}



