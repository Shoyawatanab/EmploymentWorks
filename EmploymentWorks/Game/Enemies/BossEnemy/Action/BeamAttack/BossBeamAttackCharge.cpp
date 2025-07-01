
#include "pch.h"
#include "BossBeamAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackCharge::BossBeamAttackCharge(BossEnemy* bossenemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
	,m_bossEnemy{bossenemy}
	,m_beam{beam}
	,m_particleCreateTime{}
	,m_time{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackCharge::~BossBeamAttackCharge()
{
	// do nothing.
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossBeamAttackCharge::ActionState BossBeamAttackCharge::Update(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//�i�s���������߂�
	float ratio = m_time / Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;

	ratio = std::min(ratio, 1.0f);

	////�T�C�Y�̕��
	Vector3 scale = Vector3::Lerp(Vector3::Zero, Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, ratio);

	m_beam->GetEnergyBall()->GetTransform()->SetScale(scale);

	m_time += deltaTime;

	m_bossEnemy->Rotation(deltaTime);
	

	if (m_time > Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME)
	{
		return ActionState::END;

	}


	return ActionState::RUNNING;

}


void BossBeamAttackCharge::Enter()
{
	using namespace DirectX::SimpleMath;

	m_time = 0;
	//�{�[���̗L��
	m_beam->GetEnergyBall()->SetActive(true);
	//�����̑傫�����[����
	m_beam->GetEnergyBall()->GetTransform()->SetScale(Vector3::Zero);


}


void BossBeamAttackCharge::Exit()
{


}



