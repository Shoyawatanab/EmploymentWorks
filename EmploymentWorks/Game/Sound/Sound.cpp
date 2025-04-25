/*
* 
	@file	Sound.cpp
	@brief	
*/
#include "pch.h"
#include "Sound.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Libraries/FMOD/inc/fmod.hpp"


#include "Game/StageObject/Floor.h"
#include "Game/StageObject/Wall.h"
#include "Game/Sound/SoundManager.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Sound::Sound(SoundType type, std::string soundName, bool isPlay)
	:
	m_type{type}
	,m_channel{nullptr}
	,m_sound{}
	,m_volum{ 1.0f }
{

	m_manager = SoundManager::GetInstance();
	if (soundName != "")
	{
		LoadSoound(soundName);
	}

	if (isPlay)
	{
		Play();
	}


}



//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Sound::~Sound()
{
	// do nothing.
	m_sound->release();
	m_manager->DeleteSound(this);


}


void Sound::Play()
{
	if (m_sound == nullptr)
	{
		return;
	}

	m_manager->PlaySound(&m_sound);




}

void Sound::Stop()
{

	if (m_sound == nullptr)
	{
		return;
	}

	m_manager->

}


void Sound::SetVolume(float volume)
{

	m_volum = volume;

}



void Sound::LoadSoound(std::string soundName)
{

	m_manager->CreateSound(this, soundName, &m_sound);

}




