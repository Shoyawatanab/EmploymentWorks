/*
	@file	BossBeamAttackEnd.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackEnd.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Game/MathUtil.h"

#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="bossenemy">���L��</param>
/// <param name="beam">�r�[��</param>
/// <param name="beamAttack">�r�[���U��</param>
BossBeamAttackEnd::BossBeamAttackEnd(Actor* bossenemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
	, m_bossEnemy{ bossenemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_time{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackEnd::~BossBeamAttackEnd()
{
	// do nothing.
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossBeamAttackEnd::ActionState BossBeamAttackEnd::Update(const float& elapsedTime)
{

	//float t = m_time / Params::BOSSENEMY_BEAM_SHRINK_TIME;

	//Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	//scale.x = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.x, 0.0f, t);
	//scale.y = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.y, 0.0f, t);

	//m_beam->GetBeamRays()->SetLocalScale(scale);

	//

	//scale = m_beam->GetBeamEnergyBall()->GetLocalScale();

	//scale = Vector3::Lerp(Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, Vector3::Zero, t);

	//scale.x = std::max(scale.x, 0.0f);
	//scale.y = std::max(scale.y, 0.0f);
	//scale.z = std::max(scale.z, 0.0f);


	//m_beam->GetBeamEnergyBall()->SetLocalScale(scale);


	//m_time += elapsedTime;
	//m_time = std::min(m_time, Params::BOSSENEMY_BEAM_SHRINK_TIME);

	//if (m_time == Params::BOSSENEMY_BEAM_SHRINK_TIME)
	//{
	//	return ActionState::END;
	//}


	//m_time += elapsedTime;

	return ActionState::RUNNING;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossBeamAttackEnd::Enter()
{
	m_time = 0;
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackEnd::Exit()
{
}





