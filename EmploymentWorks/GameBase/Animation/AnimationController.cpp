#include "pch.h"
#include "AnimationController.h"
#include "GameBase/Animation/Animation2.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
AnimationController::AnimationController()
	:
	m_animations{}
	,m_currentAnimation{}
	,m_stateTransitionList{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AnimationController::~AnimationController()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void AnimationController::Update(const float& deltaTime)
{
	m_currentAnimation->Update(deltaTime);
}



/// <summary>
/// �A�j���[�V�����̒ǉ�
/// </summary>
/// <param name="animatino"></param>
void AnimationController::AddAnimatoin(std::unique_ptr<Animation2> animatino)
{
	//���ɑ��݂��邩�T��
	auto it = std::find(m_animations.begin(), m_animations.end(), animatino);

	//���łɂ����
	if (it != m_animations.end())
	{
		return;
	}
	//�ǉ�
	m_animations.push_back(std::move(animatino));

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ��@1�񂾂����s
/// </summary>
/// <param name="animationName">�A�j���[�V������</param>
void AnimationController::SetTrigger(std::string animationName)
{
}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animationName"></param>
/// <param name="value"></param>
void AnimationController::SetFloat(std::string animationName, float value)
{
}


/// <summary>
/// ��ԑJ�ڂ̍쐬�@�Е����̎��͂P����Q�̃t���[���쐬�@
/// </summary>
/// <param name="state1">��ԂP</param>
/// <param name="state2">��Q</param>
/// <param name="transitionState">�Е������o������</param>
void AnimationController::CreateTransitionFlow(std::string state1, std::string state2, TransitionState transitionState)
{

	switch (transitionState)
	{
		case AnimationController::TransitionState::UNIDIRECTIONAL:
			//�Е���
			AddTransitionList(state1, state2);
			break;
		case AnimationController::TransitionState::BIDIRECTIONAL:
			//�������ǉ�
			AddTransitionList(state1, state2);
			AddTransitionList(state2, state1);
			break;
		default:
			break;
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
