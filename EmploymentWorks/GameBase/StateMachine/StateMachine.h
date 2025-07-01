#pragma once

#include "GameBase/Interface/IState.h"
#include <unordered_map>

//�X�e�[�g�N���X�ƃX�e�[�g�̗񋓌^�̎��
template<typename StateType,typename StateEnumType>
class StateMachine
{

public:

	//���݂̏�Ԃ̎擾
	StateEnumType GetCurrentState() { return m_currentState.first; }

public:

	//�R���X�g���N�^
	StateMachine()
		:
		m_currentState{}
		,m_stateList{}
	{
	};

	//�f�X�g���N�^
	virtual ~StateMachine() {};

	/// <summary>
	/// �X�e�[�g�̒ǉ�
	/// </summary>
	/// <param name="enumType">�X�e�[�g�̎��</param>
	/// <param name="state">�X�e�[�g�N���X</param>
	void AddState(StateEnumType enumType,std::unique_ptr<StateType> state)
	{
		//���łɓo�^�ς݂Ȃ�
		if (GetIsRegister(enumType))
		{
			return;
		}
		//�ǉ�
		m_stateList.insert({ enumType,std::move(state) });

	}

	// �X�V����
	void Update(const float& deltaTime)
	{

		m_currentState.second->Update(deltaTime);
		
	};

	/// <summary>
	/// �X�e�[�g�̕ύX
	/// </summary>
	/// <param name="enumType">�X�e�[�g�̎��</param>
	void ChangeState(StateEnumType enumType)
	{
		//�X�e�[�g���Ȃ����
		if (m_currentState.second == nullptr)
		{
			return;
		}
		//�X�e�[�g�̏I������
		m_currentState.second->Exit();
		//���s�X�e�[�g�̏��̕ύX
		m_currentState.first = enumType;
		m_currentState.second = m_stateList[enumType].get();
		//�X�e�[�g�̊J�n����
		m_currentState.second->Enter();

		DerivationChangeState(enumType);

	}

	//�����X�e�[�g�̃Z�b�g
	void SetStartState(StateEnumType enumTye)
	{
		//�X�e�[�g���Ȃ����
		if (!GetIsRegister(enumTye))
		{
			return;
		}

		//�����X�e�[�g�̃Z�b�g
		m_currentState.first = enumTye;
		m_currentState.second = m_stateList[enumTye].get();
		////�X�e�[�g�̊J�n����
		m_currentState.second->Enter();

	}

	//�h�����ChangeState���̏���
	virtual void DerivationChangeState(StateEnumType enumType) {};

private:

	/// <summary>
	/// �o�^����Ă��邩
	/// </summary>
	/// <param name="enumType">�X�e�[�g�̎��</param>
	/// <returns>true : ����Ă��� false : ����Ă��Ȃ�</returns>
	bool GetIsRegister(StateEnumType enumType)
	{
		//�T��
		auto it = m_stateList.find(enumType);
		//�����
		if (it != m_stateList.end())
		{
			//����
			return true;
		}
		//�Ȃ�
		return false;
	}



private:

	//���s���X�e�[�g
	std::pair<StateEnumType, StateType*> m_currentState;
	//�X�e�[�g�̕ۑ����X�g
	std::unordered_map<StateEnumType, std::unique_ptr<StateType>> m_stateList;




};