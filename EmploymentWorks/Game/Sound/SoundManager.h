#pragma once
/*
	@file	SoundManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Libraries/WataLib/Singleton.h"


namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}


class SoundManager : public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;

public:
	//�T�E���h��Json�t�@�C��
	static const wchar_t* SOUND_JSON;
	static const char* SOUND_BASE_PATH;


public:
	//�R���X�g���N
	SoundManager();
	//�f�X�g���N�^
	~SoundManager() override ;
	//������
	void Initialize();
	//�X�V����
	void  Update() ;
	//BGM�̍Đ�
	void PlaySoundBGM(std::string key);
	//SE�̍Đ�
	void PlaySoundSE(std::string key);


private:
	//���̓ǂݍ���
	void LoadSound();

private:
	//�V�X�e��
	FMOD::System* m_system;
	//�T�E���h
	FMOD::Sound* m_sound;
	//SE�`�����l��
	FMOD::Channel* m_channelSE;
	//BGM�`�����l��
	FMOD::Channel* m_channelBGM;
	//���̕ۑ����X�g
	std::unordered_map<std::string, FMOD::Sound*> m_soundList;

};
