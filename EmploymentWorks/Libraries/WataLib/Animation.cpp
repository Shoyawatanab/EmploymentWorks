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


/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::Animation::Animation()
	:
	m_animationData{}
	,m_currentAnimationData{}
	,m_position{}
	,m_rotation{}
	,m_time{}
	,m_normalAnimationType{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WataLib::Animation::~Animation()
{



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>ture:  �A�j���[�V�����I�� false:�@�A�j���[�V������</returns>
bool WataLib::Animation::Update(const float& elapsedTime)
{
	//���W�X�V
	PositionUpdate(elapsedTime);
	//��]�X�V
	RotationUpdate(elapsedTime);

	//�A�j���[�V�������I�������
	if (m_time > m_currentAnimationData.TotalTime)
	{
		//���[�v�Ȃ�
		if (m_currentAnimationData.IsLoop)
		{
			//���[�v
			m_time = 0;

		}
		//���[�v����Ȃ��Ȃ�
		else
		{
			//�Đ��A�j���[�V������ʏ�A�j���[�V�����ɕω�
			InitializAnimationData(m_normalAnimationType);

		}

		//�A�j���[�V�����I��
		return true;
	}

	m_time += elapsedTime;
	//�A�j���[�V������
	return false;
}

/// <summary>
/// ���W�̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::Animation::PositionUpdate(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;
	//���߂̎���
	float startTime = m_fromToPosition.first.keyFrame.Time;
	//�b�̎���
	float endTime = m_fromToPosition.second.keyFrame.Time;
	//����
	float raito  = ( m_time - startTime ) / (endTime - startTime ) ;
	
	raito = std::min(raito, 1.0f);
	//���W�����߂�
	m_position = Vector3::SmoothStep(m_fromToPosition.first.keyFrame.Data, m_fromToPosition.second.keyFrame.Data, raito);

	//�A�j���[�V�����̐؂�ւ�
	if (m_time >= endTime)
	{
		ChangePositionKeyFrame();
		
	}
	
}

/// <summary>
/// ��]�̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::Animation::RotationUpdate(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	//���߂̎���
	float startTime = m_fromToRotation.first.keyFrame.Time;
	//�I���̎���
	float endTime = m_fromToRotation.second.keyFrame.Time;
	//���߂̃f�[�^
	Vector3 startData = m_fromToRotation.first.keyFrame.Data;
	//�I���̃f�[�^
	Vector3 endData = m_fromToRotation.second.keyFrame.Data;

	//����
	float raito = 0;
	//�O�����ł͌v�Z�����Ȃ�����
	if (endTime != startTime)
	{
		raito = (m_time - startTime) / (endTime - startTime);
	}



	raito = std::min(raito, 1.0f);
	
	//�f�[�^�����]���쐬
	Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(startData.y),
		DirectX::XMConvertToRadians(startData.x),
		DirectX::XMConvertToRadians(startData.z)
	);
	Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(endData.y),
		DirectX::XMConvertToRadians(endData.x),
		DirectX::XMConvertToRadians(endData.z)
	);

	//��]
	m_rotation = Quaternion::Slerp(startRotation, endRotation, raito);

	//�A�j���[�V�����̐؂�ւ�
	if (m_time >= endTime)
	{
		ChangeRotationKeyFrame();

	}


}


/// <summary>
/// �A�j���[�V����
/// </summary>
/// <param name="animationType"></param>
/// <param name="data"></param>
/// <param name="isNormalAnimation"></param>
void WataLib::Animation::SetAnimationData(const std::string& animationType, const WataLib::Json::AnimationData& data, bool isNormalAnimation)
{
	

	auto it = m_animationData.find(animationType);

	//����ꍇ
	if (it != m_animationData.end())
	{
		return;
	}

// Position Rotation���Ƃɕ�����

	//Json����̃t���[���̏��
	std::vector<WataLib::Json::AnimationKeyFram> frameDatas = data.FramDatas;

	//�A�j���[�V�������̕ۑ��ϐ�
	AnimationData animationData;

	//�K�v������
	animationData.TypeName = animationType;
	animationData.TotalTime = data.TotalTime;
	animationData.Speed = data.Speed;
	animationData.IsLoop = data.IsLoop;


	//���߂̃t���[���ɒl�����邩�ǂ���
	bool isStartFrame = false;
	//�I���̃t���[���ɒl�����邩�ǂ���
	bool isEndFrame = false;


	//�t���[���̏��̐��������[�v
	for (auto& frameData : frameDatas)
	{

		//���߂̃f�[�^������Ȃ�
		if (frameData.Time == 0.0f)
		{
			isStartFrame = true;
		}
		//�I���̃f�[�^������Ȃ�
		else if (frameData.Time == animationData.TotalTime)
		{
			isEndFrame = true;
		}

		//�l����Ȃ�
		if (frameData.Position != std::nullopt)
		{
			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = frameData.Time;
			//�t���[���̍��W�̑��
			frame.Data = frameData.Position.value();
			//���ɑ��
			animationData.Position.push_back(frame);

			//animationData.Position.insert(animationData.Position.end() - 1, frame);
		}
		//���߁i0.0�b���j�Ƀf�[�^���Ȃ��ꍇ
		else if (frameData.Time == 0.0f)
		{
			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = 0.0f;
			//�t���[���̉�]�̑��
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//�͂��߂̃f�[�^�Ƃ��ĂO�������̑��
			animationData.Position.insert(animationData.Position.begin(), frame);

		}
		//�A�j���[�V�����̏I��莞�ɃA�j���[�V�����̂��Ȃ��ꍇ
		else if (frameData.Time == animationData.TotalTime)
		{
			
			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = animationData.TotalTime;
			//�t���[���̉�]�̑��
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//�I���̃f�[�^�Ƃ��ĂO�������̑��
			animationData.Position.push_back(frame);

		}


		//�l������Ȃ�
		if (frameData.Rotation != std::nullopt)
		{
			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = frameData.Time;
			//�t���[���̉�]�̑��
			frame.Data = frameData.Rotation.value();
			//���ɑ��
			animationData.Rotation.push_back(frame);
		}
		//���߁i0.0�b���j�Ƀf�[�^���Ȃ��ꍇ
		else if (frameData.Time == 0.0f)
		{
			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = 0.0f;
			//�t���[���̉�]�̑��
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//�͂��߂̃f�[�^�Ƃ��ĂO�������̑��
			animationData.Rotation.insert(animationData.Rotation.begin(), frame);

		}
		//�A�j���[�V�����̏I��莞�ɃA�j���[�V�����̂��Ȃ��ꍇ
		else if (frameData.Time == animationData.TotalTime)
		{

			//�ꎞ�I�Ȓl�ۑ��ϐ�
			KeyFram frame;
			//�t���[�����Ԃ̑��
			frame.Time = animationData.TotalTime;
			//�t���[���̉�]�̑��
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//�I���̃f�[�^�Ƃ��ĂO�������̑��
			animationData.Rotation.push_back(frame);

		}


	}

	//�A�j���[�V�����̏��߂Ƀf�[�^���Ȃ��Ȃ�
	if (!isStartFrame)
	{
		//�ꎞ�I�Ȓl�ۑ��ϐ�
		KeyFram frame;
		//�t���[�����Ԃ̑��
		frame.Time = 0.0f;
		//�t���[���̉�]�̑��
		frame.Data = DirectX::SimpleMath::Vector3::Zero;
		//�͂��߂̃f�[�^�Ƃ��ĂO�������̑��
		animationData.Position.insert(animationData.Position.begin(), frame);
		animationData.Rotation.insert(animationData.Rotation.begin(), frame);


	}

	//�A�j���[�V�����̏I���Ƀf�[�^���Ȃ��Ȃ�
	if (!isEndFrame)
	{
		//�ꎞ�I�Ȓl�ۑ��ϐ�
		KeyFram frame;
		//�t���[�����Ԃ̑��
		frame.Time = animationData.TotalTime;
		//�t���[���̉�]�̑��
		frame.Data = DirectX::SimpleMath::Vector3::Zero;
		//�I���̃f�[�^�Ƃ��ĂO�������̑��
		animationData.Position.push_back(frame);
		animationData.Rotation.push_back(frame);

	}


	//���W�@��]���Ƃɕ������f�[�^�Ƒ��
	m_animationData[animationType] = animationData;


	//�����A�j���[�V�����̓o�^
	if (isNormalAnimation)
	{
		m_currentAnimationData = animationData;
		//�ʏ�A�j���[�V������type�̓o�^
		m_normalAnimationType = animationType;
		//�Đ��A�j���[�V�����̏����l
		InitializAnimationData(animationType);

	}

	

}


/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animationType">�o�ߎ���</param>
void WataLib::Animation::ChangeAnimation(const std::string& animationType)
{

	auto it = m_animationData.find(animationType);

	if (it == m_animationData.end())
	{
		//�Ȃ��Ȃ���Ȃ�
		return;
	}

	InitializAnimationData(animationType);

}

/// <summary>
/// �A�j���[�V�����̏�����
/// </summary>
/// <param name="animationType"></param>
void WataLib::Animation::InitializAnimationData(const std::string& animationType)
{
	//�Đ��A�j���[�V�������̕ύX
	//���W
	m_currentAnimationData = m_animationData[animationType];
	m_fromToPosition.first.keyFrame = m_currentAnimationData.Position[0];
	m_fromToPosition.first.Index = 0;
	m_fromToPosition.second.keyFrame = m_currentAnimationData.Position[1];
	m_fromToPosition.second.Index = 1;
	//��]
	m_fromToRotation.first.keyFrame = m_currentAnimationData.Rotation[0];
	m_fromToRotation.first.Index = 0;
	m_fromToRotation.second.keyFrame = m_currentAnimationData.Rotation[1];
	m_fromToRotation.second.Index = 1;

	m_time = 0;
}

/// <summary>
/// ���W�̃L�[�t���[���̐؂�ւ�
/// </summary>
void WataLib::Animation::ChangePositionKeyFrame()
{

	m_fromToPosition.first = m_fromToPosition.second;

	int index = m_fromToPosition.second.Index;
	
	//Index�͈̔̓C���N�������g�@
	index++;
	//�ő�𒴂�����O�ɂ���
	index = index % m_currentAnimationData.Position.size();

	m_fromToPosition.second.Index = index;
	m_fromToPosition.second.keyFrame = m_currentAnimationData.Position[index];
}

/// <summary>
/// ��]�̃L�[�t���[���̐؂�ւ�
/// </summary>
void WataLib::Animation::ChangeRotationKeyFrame()
{
	m_fromToRotation.first = m_fromToRotation.second;

	int index = m_fromToRotation.second.Index;

	//Index�͈̔̓C���N�������g�@
	index++;
	//�ő�𒴂�����O�ɂ���
	index = index % m_currentAnimationData.Rotation.size();

	m_fromToRotation.second.Index = index;
	m_fromToRotation.second.keyFrame = m_currentAnimationData.Rotation[index];

}

