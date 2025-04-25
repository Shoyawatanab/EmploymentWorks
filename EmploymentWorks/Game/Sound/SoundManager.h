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

public:
	//�T�E���h��Json�t�@�C��
	static const wchar_t* SOUND_JSON;
	static const char* SOUND_BASE_PATH;


public:
	SoundManager();
	~SoundManager() ;

	void Initialize();

	//�X�V����
	void  Update() ;
	//BGM�̍Đ�
	void PlaySoundBGM(std::string key);
	//SE�̍Đ�
	void PlaySoundSE(std::string key);
	//�T�E���h���̍폜
	void DeleteSound();
	//
	void ChangeVolume();

private:

	void LoadSound();

private:

	FMOD::System* m_system;
	FMOD::Sound* m_sound;

	FMOD::Channel* m_channelSE;
	FMOD::Channel* m_channelBGM;


	std::unordered_map<std::string, FMOD::Sound*> m_soundList;

};
