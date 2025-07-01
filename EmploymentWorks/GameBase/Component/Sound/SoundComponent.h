#pragma once
#include "GameBase/Component.h"

class SoundManager;

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class SoundComponent : public Component
{
public:
	//�Đ��̎��
	enum class SoundType : int
	{
		BGM = 0
		,SE 
	};

public:
	//�R���X�g���N�^
	SoundComponent(Actor* owner,const std::string& soundName,SoundType type);
	//�f�X�g���N�^
	~SoundComponent() override;

	//�Đ�
	void Play();
	//��~
	void Stop();

private:
	//�}�l�[�W���[
	SoundManager* m_manager;

	//�Đ��̎��
	SoundType m_soundType;
	//�T�E���h
	FMOD::Sound* m_sound;
	//SE�`�����l��
	FMOD::Channel* m_channelSE;

};

