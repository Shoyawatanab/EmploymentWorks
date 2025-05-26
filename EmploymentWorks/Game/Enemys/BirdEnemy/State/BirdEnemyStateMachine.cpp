#include "pch.h"
#include "BirdEnemyStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyStateMachine::BirdEnemyStateMachine()
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_move{}
{
	m_idle = std::make_unique<BirdEnemyldling>();
	m_attack = std::make_unique<BirdEnemyAttack>();
	m_move = std::make_unique<BirdEnemyMove>();
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
void BirdEnemyStateMachine::Initialize(CommonResources* resources, BirdEnemy* owner)
{

	m_idle->Initialize(resources,owner);
	m_attack->Initialize(resources,owner);
	m_move->Initialize(resources,owner);

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


