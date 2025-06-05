
#include "pch.h"
#include "BirdEnemyIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include <random>

#include "Game/Params.h"
#include "Game/InstanceRegistry.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyldling::BirdEnemyldling(BirdEnemy* owner)
	:
	m_player{}
	,m_time{}
	,m_attackInterval{}
	, m_birdEnemy{ owner }
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
void BirdEnemyldling::Initialize()
{
	
	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

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


			Messenger::GetInstance()->Notify<EnemyMessageType>(m_birdEnemy->GetID(), EnemyMessageType::MOVEING);
			
		}
		else
		{


			Messenger::GetInstance()->Notify<EnemyMessageType>(m_birdEnemy->GetID(), EnemyMessageType::BEAM_ATTACK);

		}
	}


	m_time += elapsedTime;


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



