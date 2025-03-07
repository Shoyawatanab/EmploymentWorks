#include "pch.h"
#include "BarrierStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BarrierStateMachine::BarrierStateMachine(CommonResources* resources
	, Barrier* barrier)
	:
	m_currentState{}
{
	m_generate = std::make_unique<BarrierGenerate>(resources,barrier);
	m_shrink = std::make_unique<BarrierShrink>(resources, barrier);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierStateMachine::~BarrierStateMachine()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
void BarrierStateMachine::AddPointer(Player* player)
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="startState">�����X�e�[�g</param>
void BarrierStateMachine::Initialize(CommonResources* resources, IState* startState)
{


	m_currentState = startState;

	m_currentState = m_generate.get();

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BarrierStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void BarrierStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// �X�e�[�g�̐؂�ւ�
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void BarrierStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


