/*
	@file	BossBeamAttackCharge.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackCharge::BossBeamAttackCharge(Actor* bossenemy
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
BossBeamAttackCharge::ActionState BossBeamAttackCharge::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//�i�s���������߂�
	float ratio = m_time / Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;

	ratio = std::min(ratio, 1.0f);

	////�T�C�Y�̕��
	Vector3 scale = Vector3::Lerp(Vector3::Zero, Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, ratio);

	m_beam->GetEnergyBall()->GetTransform()->SetScale(scale);

	//std::vector<std::unique_ptr<BeamChargeEffect>>& effect = m_beam->GetBeamChargeEffect();

	//for (auto& eff : effect)
	//{
	//	eff->Update(elapsedTime);

	//}

	//if (m_particleCreateTime >= Params::BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME)
	//{
	//	m_beam->CreateParticle();
	//	m_particleCreateTime = 0;
	//}


	if (m_time > Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME)
	{
		return ActionState::END;

	}

	m_time += elapsedTime;
	//m_particleCreateTime += elapsedTime;

	return ActionState::RUNNING;

}


void BossBeamAttackCharge::Enter()
{
	using namespace DirectX::SimpleMath;

	m_time = 0;

	m_beam->GetEnergyBall()->SetActive(true);

	m_beam->GetEnergyBall()->GetTransform()->SetScale(Vector3::Zero);


}


void BossBeamAttackCharge::Exit()
{
	////�G�t�F�N�g�̎擾
	//auto& effects = m_beam->GetBeamChargeEffect();
	////�S�Ė�����
	//for (auto& effect : effects)
	//{
	//	effect->SetIsEntityActive(false);
	//}

}

