/*
	@file	SoundManager.cpp
	@brief	
*/
#include "pch.h"
#include "SoundManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"


#include <fstream>
#include "nlohmann/json.hpp"



//�T�E���h��Json�t�@�C��
const wchar_t* SoundManager::SOUND_JSON = L"Resources//Dates/SoundData.json";
const char*    SoundManager::SOUND_BASE_PATH = "Resources/Sounds/";



//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SoundManager::SoundManager()
	:
	m_sound{}
	,m_channelBGM{}
	,m_channelSE{}
{

	// �V�X�e�����C���X�^���X������
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	//�V�X�e���̏�����
	m_system->init(32, FMOD_INIT_NORMAL, nullptr);

	LoadSound();

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SoundManager::~SoundManager()
{
	// do nothing.
	m_system->release();
	

}

void SoundManager::Initialize()
{



}


void SoundManager::Update()
{

	m_system->update();

}



void SoundManager::PlaySoundBGM(std::string key)
{

	if (m_channelBGM)
	{
		return;
	}


	m_system->playSound(m_soundList[key], nullptr, false, &m_channelBGM);

}


void SoundManager::PlaySoundSE(std::string key)
{
	m_system->playSound(m_soundList[key], nullptr, false, &m_channelSE);

}

void SoundManager::DeleteSound()
{



}

void SoundManager::ChangeVolume()
{



}

void SoundManager::LoadSound()
{
	//Json�t�@�C�����J��
	std::ifstream ifs(SOUND_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "SoundJson�t�@�C����������܂���", "�G���[", MB_OK);
		return; // �������I��
	}

	// Json�t�@�C����ǂݍ���
	nlohmann::json json = nlohmann::json::parse(ifs);


	FMOD::System* system;
	// �V�X�e�����C���X�^���X������
	FMOD_RESULT result = FMOD::System_Create(&system);
	// �V�X�e��������������
	system->init(32, FMOD_INIT_NORMAL, nullptr);
	//BGM�̓ǂݍ���
	for (const auto& bgmDatas : json["BGM"])
	{
		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{
			// �L�[�ƒl���擾
			std::string key = it.key();
			std::string pathStr = it.value();
			// std::string��std::wstring�ɕϊ�
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());
			FMOD::Sound* sound;
			system->createSound(path.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);

			m_soundList[key] = sound;

		}

	}


	//SE�̓ǂݍ���
	for (const auto& bgmDatas : json["SE"])
	{

		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{

			// �L�[�ƒl���擾
			std::string key = it.key();
			std::string pathStr = it.value();

			// std::string��std::wstring�ɕϊ�
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());

			FMOD::Sound* sound;
			system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &sound);

			m_soundList[key] = sound;

		}

	}
}






