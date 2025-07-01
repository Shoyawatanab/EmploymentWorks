
#include "pch.h"
#include "BossBeamAttackEnd.h"
#include "GameBase/Common/Commons.h"
#include "Game/MathUtil.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"
#include "GameBase/Component/Components.h"


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
	,m_initalScale{}
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
BossBeamAttackEnd::ActionState BossBeamAttackEnd::Update(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//�i�s���������߂�
	float ratio = m_time / Params::BOSSENEMY_BEAM_SHRINK_TIME;
	//1.0�𒴂��Ȃ��悤��
	ratio = std::min(ratio, 1.0f);
	//�傫���̎擾
	Vector3 scale = m_beam->GetTransform()->GetScale();
	//�i�s�����ɉ������傫��
	scale.x = MathUtil::Lerp(m_initalScale.x, 0.0f, ratio);
	scale.y = MathUtil::Lerp(m_initalScale.y, 0.0f, ratio);
	//�傫���̃Z�b�g
	m_beam->GetTransform()->SetScale(scale);


	m_time += deltaTime;

	m_time = std::min(m_time, END_TIME);


	if (m_time == END_TIME)
	{
		//�I��
		return ActionState::END;
	}

	//���s��
	return ActionState::RUNNING;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossBeamAttackEnd::Enter()
{
	m_time = 0;
	m_initalScale = m_beam->GetTransform()->GetScale();
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackEnd::Exit()
{
	m_beam->GetTransform()->SetScale(DirectX::SimpleMath::Vector3::One);
	m_beam->SetActive(false);
}





