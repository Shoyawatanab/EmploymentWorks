
#include "pch.h"
#include "RisingPillarIdel.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarvAction.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
RisingPillarIdel::RisingPillarIdel(RisingPillarvAction* risingPillarvAction )
	:
	m_commonResources{}
	,m_risingPillarvAction{risingPillarvAction}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RisingPillarIdel::~RisingPillarIdel()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void RisingPillarIdel::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
IBehaviorNode::State RisingPillarIdel::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_risingPillarvAction->ChangeState(m_risingPillarvAction->GetPillarpreliminaryAction());

	return IBehaviorNode::State::Runngin;


}




/// <summary>
/// ��Ԃɓ�������
/// </summary>
void RisingPillarIdel::Enter()
{


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void RisingPillarIdel::Exit()
{

}



