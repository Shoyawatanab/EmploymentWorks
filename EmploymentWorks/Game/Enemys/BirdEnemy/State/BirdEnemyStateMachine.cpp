#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Observer/Messenger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyStateMachine::BirdEnemyStateMachine(BirdEnemy* owner, std::vector<std::unique_ptr<BirdEnemyBeam>>& beam)
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_move{}
{
	m_idle = std::make_unique<BirdEnemyldling>(owner);
	m_attack = std::make_unique<BirdEnemyAttack>(owner, beam);
	m_move = std::make_unique<BirdEnemyMove>(owner);


	Messenger::GetInstance()->Rigister(owner->GetID(), this);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{



}




/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="startState">s�����̃X�e�[�g</param>
void BirdEnemyStateMachine::Initialize()
{

	m_idle->Initialize();
	m_attack->Initialize();
	m_move->Initialize();

	m_currentState = m_idle.get();



}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// �X�e�[�g�̐؂�ւ�
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void BirdEnemyStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}



void BirdEnemyStateMachine::Notify(const Telegram<EnemyMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case EnemyMessageType::IDLING:
			ChangeState(m_idle.get());
			break;

		case EnemyMessageType::MOVEING:
			ChangeState(m_move.get());
			break;
		case EnemyMessageType::BEAM_ATTACK:
			ChangeState(m_attack.get());
			break;
		default:
			break;
	}

}


