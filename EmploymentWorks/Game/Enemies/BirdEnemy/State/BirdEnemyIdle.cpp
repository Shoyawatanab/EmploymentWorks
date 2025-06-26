#include "pch.h"
#include "BirdEnemyIdle.h"
#include <random>
#include "Game/Params.h"

#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/MathUtil.h"

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

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyIdle::~BirdEnemyIdle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyIdle::Update(const float& deltaTime)
{
	//�C���^�[�o���𒴂�����
	if (m_time >= m_attackInterval)
	{

		//�m��
		float ratio = MathUtil::GetRandom<float>(0, 100);


		if (ratio < Params::BIRDENEMY_ATTACK_RATIO)
		{
			//������Ԃ�
			m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::MOVE);
		}
		else
		{
			//�e�U����
			m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::BULLET_ATTACK);

		}
	}


	m_time += deltaTime;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
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

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyIdle::Exit()
{
}
