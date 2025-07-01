#include "pch.h"
#include "SoundComponent.h"
#include "GameBase/Manager/SoundManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="soundName">�T�E���h��</param>
/// <param name="type">�Đ��̎��</param>
SoundComponent::SoundComponent(Actor* owner, const std::string& soundName, SoundType type)
	:
	Component(owner)
	,m_channelSE{}
	,m_soundType{}
	,m_sound{}
	,m_manager{}
{

	//�}�l�[�W���[�̎擾
	m_manager = SoundManager::GetInstance();
	//�}�l�[�W���[�̍쐬
	m_manager->MakeSound(soundName,type,&m_sound);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundComponent::~SoundComponent()
{
}

/// <summary>
/// �Đ�
/// </summary>
void SoundComponent::Play()
{

	switch (m_soundType)
	{
		case SoundComponent::SoundType::BGM:
			//BGM�̍Đ�
			m_manager->PlayBGM(&m_sound);
			break;
		case SoundComponent::SoundType::SE:
			//SE�̍Đ�
			m_manager->PlaySE(&m_sound, &m_channelSE);
			break;
		default:
			break;
	}

}

/// <summary>
/// ��~
/// </summary>
void SoundComponent::Stop()
{

	switch (m_soundType)
	{
		case SoundComponent::SoundType::BGM:
			m_manager->StopBGM(&m_sound);
			break;
		case SoundComponent::SoundType::SE:
			break;
		default:
			break;
	}

}
