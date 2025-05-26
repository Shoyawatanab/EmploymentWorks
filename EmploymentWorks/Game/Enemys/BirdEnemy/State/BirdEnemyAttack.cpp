
#include "pch.h"
#include "BirdEnemyAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyAttack::BirdEnemyAttack()
	:
	m_commonResources{},
	m_player{}
	,m_birdEnemy{}
	,m_accumulationTime{}
	,m_shotTime{}
	,m_bulletCount{}
{



}



/// <summary>
/// �f�X�g���N
/// </summary>
BirdEnemyAttack::~BirdEnemyAttack()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyAttack::Initialize(CommonResources* resoure, BirdEnemy* owner)
{

	m_commonResources = resoure;

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	m_birdEnemy = owner;

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//��]�̍X�V
	m_birdEnemy->Rotate(elapsedTime);




}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);


}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyAttack::Enter()
{
	//������
	m_accumulationTime = 0;
	m_shotTime = 0;
	m_bulletCount = 0;

	//�r�[���̎擾
	std::vector<std::unique_ptr<BirdEnemyBeam>>& beams = m_birdEnemy->GetBeams();

	for (auto& beam : beams)
	{
		//�ʏ��Ԃ��ǂ���
		if (beam->GetStateMahine()->GetCurrentState() == beam->GetStateMahine()->GetBirdEnemyBeamIdle())
		{
			beam->GetStateMahine()->ChangeState(beam->GetStateMahine()->GetBirdEnemyBeamPreliminaryAction());
			return;
		}

	}


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyAttack::Exit()
{

}


