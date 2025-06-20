#include "pch.h"
#include "ActionController.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="actions">���s���z��</param>
ActionController::ActionController()
	:
	m_actionList{}
	,m_currentIndex{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ActionController::~ActionController()
{
	m_actionList.clear();
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
IAction::ActionState ActionController::Update(const float& elapsedTime)
{
	//��Ԃ̍X�V
	if(m_actionList[m_currentIndex]->Update(elapsedTime) == IAction::ActionState::END)
	{
		//��Ԃ��I�������
		ChangeState();
		//���ׂĂ̏�Ԃ��I�����
		if (m_currentIndex >= m_actionList.size())
		{
			m_currentIndex = 0;
			return IAction::ActionState::END;

		}

	}


	return IAction::ActionState::RUNNING;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void ActionController::Enter()
{

	m_currentIndex = 0;


	if (!m_actionList.empty())
	{
		m_actionList[m_currentIndex]->Enter();
	}


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void ActionController::Exit()
{
	m_currentIndex = 0;
}

/// <summary>
/// ��Ԃ̐؂�ւ�
/// </summary>
void ActionController::ChangeState()
{
	//�������i�K�ł͍s��Ȃ��悤��
	if (m_currentIndex != 0)
	{
		//��Ԃ𔲂������̏���
		m_actionList[m_currentIndex]->Exit();
	}

	m_currentIndex++;

	//�Ō��State���I�������
	if (m_currentIndex >= m_actionList.size())
	{
		return;
	}
	//��Ԃɓ��������̏���
	m_actionList[m_currentIndex]->Enter();
}

/// <summary>
/// �A�N�V�����̒ǉ�
/// </summary>
/// <param name="actions">�A�N�V�����z��</param>
void ActionController::AddAction(std::vector<IAction*> actions)
{

	m_actionList = std::move(actions);

}

