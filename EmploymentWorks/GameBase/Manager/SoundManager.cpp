#include "pch.h"
#include "SoundManager.h"
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"
#include <fstream>
#include "nlohmann/json.hpp"


//�T�E���h��Json�t�@�C��
const wchar_t* SoundManager::SOUND_JSON = L"Resources//Dates/SoundData.json";
const char* SoundManager::SOUND_BASE_PATH = "Resources/Sounds/";


/// <summary>
/// �R���X�g���N
/// </summary>
SoundManager::SoundManager()
	:
	m_channelBGM{}
	,m_soundPathList{}
	,m_system{}
{

	// �V�X�e�����C���X�^���X������
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	//�V�X�e���̏�����
	m_system->init(32, FMOD_INIT_NORMAL, nullptr);

	//���̓ǂݍ���
	LoadSound();


}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundManager::~SoundManager()
{
	m_system->release();

}

/// <summary>
/// �X�V����
/// </summary>
void SoundManager::Update()
{
	m_system->update();

}


void SoundManager::MakeSound(const std::string& soundName, SoundComponent::SoundType type, FMOD::Sound** sound)
{

	auto soundPath = m_soundPathList.find(soundName);

	//�Ȃ����
	if (soundPath == m_soundPathList.end())
	{
		return;
	}

	switch (type)
	{
		case SoundComponent::SoundType::BGM:
			//���[�v�Đ�
			m_system->createSound(soundPath->second.c_str(), FMOD_LOOP_NORMAL, nullptr, sound);
			break;
		case SoundComponent::SoundType::SE:
			//1�񂾂��Đ�
			m_system->createSound(soundPath->second.c_str(), FMOD_DEFAULT, nullptr, sound);

			break;
		default:
			break;
	}




}

/// <summary>
/// BGM�̍Đ�
/// </summary>
/// <param name="sound"></param>
void SoundManager::PlayBGM(FMOD::Sound** sound)
{
	// ���݂�BGM���Đ����Ȃ�~�߂�
	if (m_channelBGM)
	{
		bool isPlaying = false;
		m_channelBGM->isPlaying(&isPlaying);
		//�Đ����Ȃ�~�߂�
		if (isPlaying)
		{
			m_channelBGM->stop();
		}
	}

	m_system->playSound((*sound), nullptr, false, &m_channelBGM);


}


/// <summary>
/// SE�̍Đ�
/// </summary>
/// <param name="sound"></param>
/// <param name="Channel"></param>
void SoundManager::PlaySE(FMOD::Sound** sound, FMOD::Channel** channel)
{
	bool isPlaying;
	//�Đ���Ԃ̎擾
	(*channel)->getPaused(&isPlaying);

	//�Đ����Ȃ�
	if (isPlaying)
	{
		//���߂ɖ߂�
		(*channel)->setPosition(0, FMOD_TIMEUNIT_MS);
		//�Đ�
		m_system->playSound((*sound), nullptr, false, channel);

	}


}

/// <summary>
/// BGM�̒�~
/// </summary>
/// <param name="sound"></param>
void SoundManager::StopBGM(FMOD::Sound** sound)
{

	m_channelBGM->stop();

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
			//���X�g�ɕۑ�
			m_soundPathList[key] = path;

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
			//���X�g�ɕۑ�
			m_soundPathList[key] = path;

		}

	}

}
