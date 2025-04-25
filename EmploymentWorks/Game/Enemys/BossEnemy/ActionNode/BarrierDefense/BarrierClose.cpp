
#include "pch.h"
#include "BarrierClose.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BarrierClose::BarrierClose(BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier
	, BossEnemy* bossEnemy)
	:
	m_commonResources{}
	,m_barrierDefenseAction{ barrierDefenseAction }
	,m_barrier{barrier}
	,m_time{}
	,m_bossEnemy{bossEnemy}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierClose::~BarrierClose()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BarrierClose::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
IBehaviorNode::State BarrierClose::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	
	if (m_time >= 1.0f)
	{
		m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierIdel());
		return IBehaviorNode::State::Success;
	}



	m_time += elapsedTime;


	return IBehaviorNode::State::Runngin;

}




/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BarrierClose::Enter()
{

	m_bossEnemy->ChangeAnimation("BarrierEnd");

	m_time = 0;

}



/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BarrierClose::Exit()
{
	m_barrier->SetIsEntityActive(false);

}



