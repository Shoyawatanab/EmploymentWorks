#pragma once
/*
	@file	Sound.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"

// �O���錾
class SoundManager;

namespace FMOD
{
	class System;
	class Sound;
}


class Sound 
{
public:

	enum class SoundType
	{
		BGM
		,SE
	};

public:

	SoundType* GetSoundType() { m_type; }

public:

	Sound(SoundType type,std::string soundName,bool isPlay = false);

	~Sound() ;

	void Play();

	void Stop();

	void SetVolume(float volume);


private:

	void LoadSoound(std::string soundName);


private:	
	SoundManager* m_manager;

	SoundType m_type;

	FMOD::Sound* m_sound;

	float m_volum;


};
