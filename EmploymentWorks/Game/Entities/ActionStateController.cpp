#include "pch.h"
#include "ActionStateController.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
ActionStateController::ActionStateController()
	:
	m_actionState{}
	,m_currentIndex{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ActionStateController::~ActionStateController()
{
	m_actionState.clear();
}

/// <summary>
/// ������
/// </summary>
void ActionStateController::Initialize(std::vector<IAction*> actions)
{

	m_actionState = actions;

	m_currentIndex = 0;

}

IAction::ActionState ActionStateController::Update(const float& elapsedTime)
{

	if(m_actionState[m_currentIndex]->Update(elapsedTime) == IAction::ActionState::End)
	{
		ChangeState();

		if (m_currentIndex >= m_actionState.size())
		{

			return IAction::ActionState::End;

		}

	}


	return IAction::ActionState::Running;

}

void ActionStateController::Enter()
{

	m_currentIndex = 0;


	if (!m_actionState.empty())
	{
		m_actionState[m_currentIndex]->Enter();
	}


}

void ActionStateController::Exit()
{
	m_currentIndex = 0;
}

void ActionStateController::ChangeState()
{
	//�������i�K�ł͍s��Ȃ��悤��
	if (m_currentIndex != 0)
	{
		m_actionState[m_currentIndex]->Exit();
	}

	m_currentIndex++;

	//�Ō��State���I�������
	if (m_currentIndex >= m_actionState.size())
	{
		return;
	}
	
	m_actionState[m_currentIndex]->Enter();
}

