/*
	@file	BossBeamAttackCharge.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackCharge::BossBeamAttackCharge(Actor* bossenemy
	, Beam* beam
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
/// ������
/// </summary>
void BossBeamAttackCharge::Initialize()
{



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossBeamAttackCharge::ActionState BossBeamAttackCharge::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//Vector3 beamPosition = Params::BOSSENEMY_BEAM_SHOT_POSITION;

	//beamPosition = Vector3::Transform(beamPosition, m_bossEnemy->GetRotation());

	//m_beam->SetPosition(beamPosition + m_bossEnemy->GetPosition());



	////�i�s���������߂�
	//float t = m_time / Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;

	//t = std::min(t, 1.0f);

	////�T�C�Y�̕��
	//Vector3 scale = Vector3::Lerp(Vector3::Zero, Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, t);

	//m_beam->GetBeamEnergyBall()->SetLocalScale(scale);

	//m_beam->GetBeamEnergyBall()->Update(elapsedTime);


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


	//if (m_time > Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME)
	//{
	//	return ActionState::END;

	//}

	//m_time += elapsedTime;
	//m_particleCreateTime += elapsedTime;

	return ActionState::RUNNING;

}


void BossBeamAttackCharge::Enter()
{
	//m_time = 0;

	//m_particleCreateTime = 0;

	////�r�[���̍��W�̐ݒ�

	//Vector3 beamPosition = Params::BOSSENEMY_BEAM_SHOT_POSITION;

	//beamPosition = Vector3::Transform(beamPosition, m_bossEnemy->GetRotation());

	//m_beam->SetPosition(beamPosition + m_bossEnemy->GetPosition());

	//m_beam->CreateParticle();

	//m_beam->GetBeamEnergyBall()->SetLocalPosition(Vector3::Zero);

	//m_beam->GetBeamRays()->SetLocalPosition(Vector3::Zero);

	//m_beam->SetIsEntityActive(true);
	//m_beam->GetBeamEnergyBall()->SetIsEntityActive(true);

	////�G�t�F�N�g�̎擾
	//auto& effects = m_beam->GetBeamChargeEffect();
	////�S�ėL����
	//for (auto& effect : effects)
	//{
	//	effect->SetIsEntityActive(true);
	//}


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

