#include "pch.h"
#include "BirdEnemyIdle.h"
#include <random>
#include "Game/Params.h"

#include "Game/Messenger/Messenger.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
BirdEnemyIdle::BirdEnemyIdle(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{stateMachine}
	,m_birdEnemy{birdEnemy}
	,m_time{}
	,m_attackInterval{}
{
}

BirdEnemyIdle::~BirdEnemyIdle()
{
}

void BirdEnemyIdle::Update(const float& deltaTime)
{

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


			Messenger::GetInstance()->Notify(MessageType::BIRD_MOVE_STATE);

		}
		else
		{

			Messenger::GetInstance()->Notify(MessageType::BIRD_BEAM_ATTACK_STATE);

		}
	}


	m_time += deltaTime;

}

void BirdEnemyIdle::Enter()
{
	//������
	m_time = 0;

	//�����_���ŃC���^�[�o���̍쐬
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Params::BIRDENEMY_ACTIONS_MIN_TIME, Params::BIRDENEMY_ACTIONS_MAX_TIME);

	m_attackInterval = dis(gen);

}

void BirdEnemyIdle::Exit()
{
}
