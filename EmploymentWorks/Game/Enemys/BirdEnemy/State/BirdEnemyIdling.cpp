
#include "pch.h"
#include "BirdEnemyIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include <random>

#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyldling::BirdEnemyldling()
	:
	m_commonResources{},
	m_player{}
	,m_time{}
	,m_attackInterval{}
	,m_birdEnemy{}
{



}

/// <summary>
/// �f�X�g���N
/// </summary>
BirdEnemyldling::~BirdEnemyldling()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyldling::Initialize(CommonResources* resoure)
{
	m_commonResources = resoure;


}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyldling::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//��]�̍X�V
	m_birdEnemy->Rotate(elapsedTime);


	if (m_time >= m_attackInterval)
	{

		//	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
		std::random_device seed;
		//	��L�̊��S�ȃ����_���͓��삪�x�����߁Aseed�l�̌���݂̂Ɏg�p����
		//	���udefault_random_engine�v��using�Łumt19937�v�ƂȂ��Ă���
		std::default_random_engine engine(seed());
		//	�������ė~���������_���͈̔͂�Distribution�ɔC����B�����0�`2PI
		std::uniform_real_distribution<> dist(0, 100);

		float ratio = static_cast<float>(dist(engine));
		
		if (ratio < Params::BIRDENEMY_ATTACK_RATIO)
		{

			m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyMove());

		}
		else
		{
			m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyAttack());

		}
	}


	m_time += elapsedTime;


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyldling::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyldling::Enter()
{
	//������
	m_time = 0;

	//�����_���ŃC���^�[�o���̍쐬
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Params::BIRDENEMY_ACTIONS_MIN_TIME, Params::BIRDENEMY_ACTIONS_MAX_TIME);

	m_attackInterval = dis(gen);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyldling::Exit()
{

}

/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="birdEnemy">���̓G</param>
void BirdEnemyldling::AddPointer(Player* player, BirdEnemy* birdEnemy)
{
	m_player = player;
	m_birdEnemy = birdEnemy;

}

