#include "pch.h"
#include "ActionManager.h"
#include "ActionController.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ActionManager::ActionManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ActionManager::~ActionManager()
{
	//m_action.first.clear();
	//m_actionList.clear();
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
/// <returns>true: ���s�I��  false:�@���s��</returns>
bool ActionManager::Update(const float& deltaTime)
{
	if(	m_action.second->Update(deltaTime) == IAction::ActionState::END)
	{
		return true;
	}

	return false;
}

void ActionManager::SetStartAction(const std::string& actionName)
{
	m_action.first = actionName;
	m_action.second = m_actionList[actionName].get();
}

/// <summary>
/// �A�N�V�����̕ύX
/// </summary>
/// <param name="actionName">�A�N�V������</param>
void ActionManager::ChangeAction(const std::string& actionName)
{
	//���X�g���獲��}
	auto it = m_actionList.find(actionName);

	//�����
	if (it != m_actionList.end())
	{
		//�؂�ւ��O�̍s�������邩�ǂ���
		if (m_action.second != nullptr)
		{
			//��Ԃ𔲂���Ƃ��̏���
			m_action.second->Exit();
		}
		//���s�s���̖��O�̐؂�ւ�
		m_action.first = actionName;
		//���s�s���̐؂�ւ�
		m_action.second = it->second.get();
		//��Ԃɓ��������̏���
		m_action.second->Enter();


	}

}

/// <summary>
/// �A�N�V�����̒ǉ�
/// </summary>
/// <param name="">�A�N�V������</param>
/// <param name=""></param>
void ActionManager::AddAction(const std::string& name, std::unique_ptr<ActionController>action)
{

	m_actionList[name] = std::move(action);

}
