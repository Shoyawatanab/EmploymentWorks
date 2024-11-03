/*
	@file	CSV.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "Animation.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Animation::Animation()
	:
	m_animation{}
	,m_playBackType{}
	,m_totalTime{}
	,m_keyFrameIndex{}
	,m_state{AnimationState::None}
{
}

Animation::~Animation()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns> Animation���@Time�͌o�ߎ��� </returns>
Animation::AnimationState Animation::Update(float elapsdTime)
{
	

	if (m_animation.empty() || m_state == AnimationState::End)
	{	
		return m_state;
	}

	m_state = Animation::AnimationState::Running;

	//���Ԃ̊��������߂�
	float ratio = m_totalTime / m_animation[m_keyFrameIndex + 1].Time;
	//�������P�𒴂��Ȃ��悤�ɂ���
	ratio = std::min(ratio, 1.0f);
	//Lerp�֐��ŉ�]���X�V
	m_animationRotate = Quaternion::Lerp(m_animation[m_keyFrameIndex].Rotation, m_animation[m_keyFrameIndex + 1].Rotation, ratio);
	
	//���Ԃ̉��Z
	m_totalTime += elapsdTime;

	//��؂肪�I�������
	if (ratio >= 1)
	{
		//���Ԃ̏�����
		m_totalTime = 0;
		//���̃A�j���[�V�����ɍs�����߂�
		m_keyFrameIndex++;

		//�Ō�܂ōs������
		if (m_keyFrameIndex >= m_animation.size() -1)
		{
			switch (m_playBackType)
			{
				case Animation::Loop:
					//���߂ɖ߂�
					m_keyFrameIndex = 0;
					break;
				case Animation::Once:
					//�I���ɂ���
					m_state = AnimationState::End;
					break;
				default:
					break;
			}
			m_keyFrameIndex = 0;
		}

	}




	return m_state;
}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animations">�A�j���[�V�������</param>
/// <param name="PlayBackType">�Đ��̎��</param>
void Animation::SetAnimation(std::vector<AnimationKeyFrame> animations, AnimationPlayBackType PlayBackType)
{

	m_animation = animations;

	m_playBackType = PlayBackType;

}

void Animation::ResetAnimation()
{

	m_keyFrameIndex = 0;
	m_totalTime = 0;
	m_state = AnimationState::None;

}
