#include "pch.h"
#include "AnimationController.h"
#include "GameBase/Animation/Animator.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
AnimationController::AnimationController()
	:
	m_animations{}
	,m_currentAnimation{}
	,m_normalAnimation{}
	,m_stateTransitionList{}
	,m_state{ ExecutionState::NONE}
	,m_triggerTransitionList{}
	,m_floatTransitionList{}
	,m_transitionParamter{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AnimationController::~AnimationController()
{
	m_animations.clear();
	m_stateTransitionList.clear();
	m_triggerTransitionList.clear();
	m_floatTransitionList.clear();
	m_transitionParamter.clear();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void AnimationController::Update(const float& deltaTime)
{

	//�Đ���ԂłȂ��ꍇ
	if (m_state == ExecutionState::NONE)
	{
		return;
	}

	//�A�j���[�V�����̍Đ����
	if (!m_currentAnimation->Update(deltaTime))
	{
		//�Đ���
		return;
	}


	switch (m_state)
	{
		case AnimationController::ExecutionState::NONE:
			break;
		case AnimationController::ExecutionState::PLAY:

			//���[�v�Đ����ǂ���
			if (m_currentAnimation->GetIsLoop())
			{
				m_currentAnimation->Rerun();
			}
			//���[�v�łȂ��Ƃ�
			else
			{
				m_state = ExecutionState::NONE;

			}
			break;
		case AnimationController::ExecutionState::TRIIGER:
		case AnimationController::ExecutionState::FLOAT:
			//�ʏ�A�j���[�V�����ɂ��ǂ�
			ChangeAnimation(m_normalAnimation);
			//��Ԃ̕ύX
			m_state = ExecutionState::PLAY;
			break;
		default:
			break;
	}



}




/// <summary>
/// �A�j���[�V�����̒ǉ�
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="animationName">�A�j���[�V������</param>
/// <param name="filePath">�t�@�C���p�X</param>
/// <param name="actors">�A�j���[�V�����I�u�W�F�N�g</param>
/// <param name="isNormal">�����A�j���[�V������</param>
void AnimationController::AddAnimatoin(Actor* owner, std::string animationName, std::string filePath, std::vector<std::pair<std::string, Actor*>> actors, bool isNormal)
{

	//���ɑ��݂��邩�T��
	auto it = m_animations.find(animationName);

	//���łɂ����
	if (it != m_animations.end())
	{
		return;
	}
	//�A�j���^�[�̍쐬
	auto animator = std::make_unique<Animator>(owner, animationName, filePath, actors);

	//�ǉ�
	m_animations[animationName] = std::move(animator);


	//�ʏ�A�j���[�V�����Ȃ�
	if (isNormal)
	{
		//�ʏ�A�j���[�V�����Ƃ��ĕێ�
		m_normalAnimation = m_animations[animationName].get();
		//���s�A�j���[�V������
		m_currentAnimation = m_animations[animationName].get();
		m_state = ExecutionState::PLAY;
	}

}

/// <summary>
/// �g���K�[��ԑJ�ڃt���[�̍쐬
/// </summary>
/// <param name="fromAnimationName">�J�ڌ��A�j���[�V������</param>
/// <param name="toAnimationName">�J�ڐ�A�j���[�V������</param>
/// <param name="name">�J�ږ�</param>
void AnimationController::CreateTriggerTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName)
{

	//�Ȃ����
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//�g���K�[���X�g����T��
	auto it = m_triggerTransitionList.find(connectionName);

	//�����
	if (it != m_triggerTransitionList.end())
	{
		return;
	}

	//���X�g�ɒǉ�
	m_triggerTransitionList[connectionName] = { fromAnimationName,toAnimationName };

}

/// <summary>
/// Float��ԑJ�ڃt���[�̍쐬
/// </summary>
/// <param name="fromAnimationName">�J�ڌ��A�j���[�V������</param>
/// <param name="toAnimationName">�J�ڐ�A�j���[�V������</param>
/// <param name="name">�J�ږ�</param>
/// <param name="value">��l</param>
void AnimationController::CreateFloatTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state)
{

	//�Ȃ����
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//�g���K�[���X�g����T��
	auto it = m_floatTransitionList.find(connectionName);

	//�����
	if (it != m_floatTransitionList.end())
	{
		return;
	}

	//���X�g�ɒǉ�
	m_floatTransitionList[connectionName] = { fromAnimationName,toAnimationName,state,value };

}

/// <summary>
/// AnyState����̃g���K�[��ԑJ�ڃt���[�̍쐬 
/// </summary>
/// <param name="toAnimationName">�J�ڐ�A�j���[�V������</param>
/// <param name="name">�J�ږ�</param>
void AnimationController::CreateAnyStateToTriggerTransition(const std::string& toAnimationName, const std::string& connectionName)
{
	//�Ȃ����
	if(!IsFindParameter(connectionName))
	{
		return;
	}

	//�g���K�[���X�g����T��
	auto it = m_triggerTransitionList.find(connectionName);

	//�����
	if (it != m_triggerTransitionList.end())
	{
		return;
	}

	//���X�g�ɒǉ�
	m_triggerTransitionList[connectionName] = { "AnyState",toAnimationName };

}

/// <summary>
/// AnyState�����Float��ԑJ�ڃt���[�̍쐬
/// </summary>
/// <param name="toAnimationName">�J�ڐ�A�j���[�V������</param>
/// <param name="name">�J�ږ�</param>
/// <param name="value">��l</param>
void AnimationController::CreateAnyStateToFloatTransition(const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state)
{
	//�Ȃ����
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//�g���K�[���X�g����T��
	auto it = m_floatTransitionList.find(connectionName);

	//�����
	if (it != m_floatTransitionList.end())
	{
		return;
	}

	//���X�g�ɒǉ�
	m_floatTransitionList[connectionName] = { "AnyState",toAnimationName,state,value };
}



/// <summary>
/// �A�j���[�V�����̍Đ�
/// </summary>
/// <param name="animatioName">�A�j���[�V������</param>
void AnimationController::Play(const std::string& animationName)
{
	//�؂�ւ�����
	if (!IsChangeAnimation(animationName))
	{
		return;
	}

	//�l�Ԃ̕ύX
	m_state = ExecutionState::PLAY;
	//���s�A�j���[�V�����̕ύX
	ChangeAnimation(m_animations[animationName].get());
}

/// <summary>
/// �A�j���[�V�����̐؂�ւ��@1�񂾂����s
/// </summary>
/// <param name="connectionName">��Ԑڑ���</param>
void AnimationController::SetTrigger(const std::string& connectionName)
{
	//�p�����[�^�[�ɂȂ����
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//���s�ł��邩
	if (!CheckTrigger(connectionName))
	{
		//�ł��Ȃ�
		return;
	}

	//�l�Ԃ̕ύX
	m_state = ExecutionState::TRIIGER;
	//���s�A�j���[�V�����̕ύX
	ChangeAnimation(m_animations[m_triggerTransitionList[connectionName].second].get());

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="connectionName">��Ԑڑ���</param>
/// <param name="value">��r�l</param>
void AnimationController::SetFloat(const std::string& connectionName, const float& value)
{
	//�g���K�[��ԂȂ���Ȃ�
	if (m_state == ExecutionState::TRIIGER)
	{
		return;
	}

	//�p�����[�^�[�ɂȂ����
	if (!IsFindParameter(connectionName))
	{
		return;
	}
	//�T��
	auto it = m_floatTransitionList.find(connectionName);
	//���X�g�ɋ������
	if (it == m_floatTransitionList.end())
	{
		return;
	}


	//Anystate���ǂ���
	if (it->second.FromName == "AnyState" ||                                   //AnyState���ǂ���
		m_currentAnimation->GetAnimaiionName() == it->second.FromName)		   //�J�ڌ��̃A�j���[�V�����Ǝ��s�A�j���[�V������������
	{
		if (CheckFloatValue(connectionName, value))
		{
			//�l�Ԃ̕ύX
			m_state = ExecutionState::FLOAT;
			//���s�A�j���[�V�����̕ύX
			ChangeAnimation(m_animations[m_floatTransitionList[connectionName].ToName].get());
			return;
		}
	}



	//���łɃA�j���[�V�����ɐ؂�ւ���Ă���ꍇ
	if (m_currentAnimation->GetAnimaiionName() == it->second.ToName)
	{
		if (!CheckFloatValue(connectionName, value))
		{
			//�l�Ԃ̕ύX
			m_state = ExecutionState::PLAY;
			//���s�A�j���[�V�����̕ύX
			ChangeAnimation(m_normalAnimation);

		}

	}


}



/// <summary>
/// ��ԑJ�ڃ��X�g�ɒǉ�
/// </summary>
/// <param name="state1">��ԂP</param>
/// <param name="state2">��ԂQ</param>
void AnimationController::AddTransitionList(std::string state1, std::string state2)
{
	
	; auto& it = m_stateTransitionList[state1];

	// ���ł� string2 ���o�^����Ă��邩�`�F�b�N
	if (std::find(it.begin(), it.end(), state2) == it.end())
	{
		// �o�^����Ă��Ȃ���Βǉ�
		it.push_back(state2); 
	}

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ����s���Ă��悢��
/// </summary>
/// <param name="animationName">�A�j���[�V������</param>
/// <returns>�@true: �悢  false:�_��</returns>
bool AnimationController::IsChangeAnimation(const std::string& animationName)
{
	//�T��
	auto it = m_animations.find(animationName);

	//�Ȃ����
	if (it == m_animations.end())
	{
		return false;
	}
	//���s���Ɠ����Ȃ�
	if (m_currentAnimation == m_animations[animationName].get())
	{
		return false ;
	}


	return true;
}

/// <summary>
/// �J�ږ������邩
/// </summary>
/// <param name="connectionName">�J�ږ�</param>
/// <returns>true:����    false:�Ȃ�</returns>
bool AnimationController::IsFindParameter(const std::string& connectionName)
{

	auto it = m_transitionParamter.find(connectionName);

	//�Ȃ����
	if (it == m_transitionParamter.end())
	{
		//�Ȃ�
		return false;
	}
	//����
	return true;
}

/// <summary>
/// �g���K�[�̎��s���ł��邩�̔���
/// </summary>
/// <param name="connectionName">�J�ږ�</param>
/// <returns>true:�ł���   false:�ł��Ȃ�</returns>
bool AnimationController::CheckTrigger(const std::string& connectionName)
{
	
	auto it = m_triggerTransitionList.find(connectionName);
	//���X�g�ɋ������
	if (it == m_triggerTransitionList.end())
	{
		return false;
	}

	//Anystate���ǂ���
	if (it->second.first == "AnyState")
	{
		//�ł���
		return true;
	}

	//���s���A�j���[�V�����ƑJ�ڌ��A�j���[�V����������v���邩
	if (m_currentAnimation->GetAnimaiionName() == it->second.first)
	{
		//���Ȃ��ꍇ
		return true;
	}


	return false;
}

/// <summary>
/// Float�̑J�ڃt���[�����邩�̔���
/// </summary>
/// <param name="connectionName">�J�ږ�</param>
/// <returns>true:�ł���   false:�ł��Ȃ�</returns>
bool AnimationController::CheckFloatTransition(const std::string& connectionName, const float& value)
{
	auto it = m_floatTransitionList.find(connectionName);
	//���X�g�ɋ������
	if (it == m_floatTransitionList.end())
	{
		return false;
	}



	//Anystate���ǂ���
	if (it->second.FromName == "AnyState")
	{
		//�ł���
		return true;
	}


	//���s���A�j���[�V�����ƑJ�ڌ��A�j���[�V����������v���邩
	if (m_currentAnimation->GetAnimaiionName() == it->second.FromName)
	{
		//�ł���
		return true;
	}



	//�ł��Ȃ�
	return false;
}

/// <summary>
/// Float�̒l�ɂ���r
/// </summary>
/// <param name="connectionName">�J�ږ�</param>
/// <param name="value">�l</param>
/// <returns>true: �ł���  false:�ł��Ȃ�</returns>
bool AnimationController::CheckFloatValue(const std::string& connectionName, const float& value)
{
	//�l�̔�r
	switch (m_floatTransitionList[connectionName].State)
	{
		//�傫��
		case FloatState::Greater:
			if (value > m_floatTransitionList[connectionName].Value)
			{
				//�ł���
				return true;
			}
			break;
			//������
		case FloatState::Less:
			if (value <= m_floatTransitionList[connectionName].Value)
			{
				//�ł���
				return true;
			}
			break;
		default:
			break;
	}

	return false;
}


/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animatior">���̃A�j���[�V����</param>
void AnimationController::ChangeAnimation(Animator* animatior)
{
	//�����Ȃ�s��Ȃ�
	if (m_currentAnimation == animatior)
	{
		if(!m_currentAnimation->GetIsEnd())
		{
			m_currentAnimation->Rerun();
		}

		return;
	}
	//������
	m_currentAnimation->Rerun();
	//�؂�ւ�
	m_currentAnimation = animatior;

}
