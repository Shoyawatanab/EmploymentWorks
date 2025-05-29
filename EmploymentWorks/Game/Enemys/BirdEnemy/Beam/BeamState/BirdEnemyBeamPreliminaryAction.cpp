
#include "pch.h"
#include "BirdEnemyBeamPreliminaryAction.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="birdEnemy">���̓G</param>
/// <param name="beam">�r�[��</param>
BirdEnemyBeamPreliminaryAction::BirdEnemyBeamPreliminaryAction(BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_player{}
	,m_time{}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamPreliminaryAction::~BirdEnemyBeamPreliminaryAction()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyBeamPreliminaryAction::Initialize()
{


	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBeamPreliminaryAction::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�ő�̑傫���ɂȂ�܂ł̎��Ԃ̎擾
	float maxSizeTime = m_beam->GetBeamEnergyBall()->GetMaxSizeTime();
	//��Ԃ̎��Ԃ̌v�Z
	float t = m_time / maxSizeTime;
	//�G�l���M�[�e�̑傫���̕��
	Vector3 scale = Vector3::Lerp(m_beam->GetBeamEnergyBall()->GetInitialScale(), m_beam->GetBeamEnergyBall()->GetMaxScale(), t);
	//�傫����K�p
	m_beam->GetBeamEnergyBall()->SetLocalScale(scale);
	//�o�ߎ��Ԃ����Z
	m_time += elapsedTime;

	//�ő�̑傫���ɂȂ�����
	if (m_time >= maxSizeTime)
	{
		m_beam->GetStateMahine()->ChangeState(m_beam->GetStateMahine()->GetBirdEnemyBeamAttack());
	}
	//�r�[���̍��W�̍X�V
	m_beam->UpdateBirdEnemyBeamPosition();


}
/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyBeamPreliminaryAction::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBeamPreliminaryAction::Enter()
{
	//���Ԃ̏�����
	m_time = 0;


}
/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBeamPreliminaryAction::Exit()
{

}



