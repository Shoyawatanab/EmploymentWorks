#include "pch.h"
#include "PlayerStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerStateMachine::PlayerStateMachine()
	:
	m_currentState{}
	,m_idle{}
{
	m_idle = std::make_unique<PlayerIdle>();
	m_attack = std::make_unique<PlayerAttack>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
void PlayerStateMachine::AddPointer(Player* player)
{
	m_idle->AddPointer(player);
	m_attack->AddPointer(player);
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="startState">�����X�e�[�g</param>
void PlayerStateMachine::Initialize(CommonResources* resources, IState* startState)
{

	m_idle->Initialize(resources);
	m_attack->Initialize(resources);

	m_currentState = startState;



}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void PlayerStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// �X�e�[�g�̐؂�ւ�
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void PlayerStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


