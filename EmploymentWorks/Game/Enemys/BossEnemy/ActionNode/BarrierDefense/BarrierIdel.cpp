
#include "pch.h"
#include "BarrierIdel.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
BarrierIdel::BarrierIdel(BarrierDefenseAction* barrierDefenseAction)
	:
	m_commonResources{}
	, m_barrierDefenseAction{ barrierDefenseAction }
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierIdel::~BarrierIdel()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BarrierIdel::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
IBehaviorNode::State BarrierIdel::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierPreliminaryAction());

	return IBehaviorNode::State::Runngin;


}




/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BarrierIdel::Enter()
{


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BarrierIdel::Exit()
{

}



