/*
	@file	SoundManager.cpp
	@brief	
*/
#include "pch.h"
#include "SoundManager.h"
#include "GameBase/Common/Commons.h"
#include <cassert>
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"


#include <fstream>
#include "nlohmann/json.hpp"



//サウンドのJsonファイル
const wchar_t* SoundManager::SOUND_JSON = L"Resources//Dates/SoundData.json";
const char*    SoundManager::SOUND_BASE_PATH = "Resources/Sounds/";


/// <summary>
/// コンストラク
/// </summary>
SoundManager::SoundManager()
	:
	m_sound{}
	,m_channelBGM{}
	,m_channelSE{}
{

	// システムをインスタンス化する
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	//システムの初期化
	m_system->init(32, FMOD_INIT_NORMAL, nullptr);

	//音の読み込み
	LoadSound();

}

/// <summary>
/// デストラクタ
/// </summary>
SoundManager::~SoundManager()
{
	// do nothing.
	m_system->release();
	

}

/// <summary>
/// 初期化
/// </summary>
void SoundManager::Initialize()
{



}


/// <summary>
/// 更新処理
/// </summary>
void SoundManager::Update()
{

	m_system->update();

}


/// <summary>
/// BGMの再生
/// </summary>
/// <param name="key"></param>
void SoundManager::PlaySoundBGM(std::string key)
{

	if (m_channelBGM)
	{
		return;
	}



	m_system->playSound(m_soundList[key], nullptr, false, &m_channelBGM);

	//m_channelBGM->setVolume(100);


}


/// <summary>
/// SEの再生
/// </summary>
/// <param name="key"></param>
void SoundManager::PlaySoundSE(std::string key)
{
	m_system->playSound(m_soundList[key], nullptr, false, &m_channelSE);

}


/// <summary>
/// 音の読み込み
/// </summary>
void SoundManager::LoadSound()
{
	//Jsonファイルを開く
	std::ifstream ifs(SOUND_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "SoundJsonファイルが見つかりません", "エラー", MB_OK);
		return; // 処理を終了
	}

	// Jsonファイルを読み込む
	nlohmann::json json = nlohmann::json::parse(ifs);


	FMOD::System* system;
	// システムをインスタンス化する
	FMOD_RESULT result = FMOD::System_Create(&system);
	// システムを初期化する
	system->init(32, FMOD_INIT_NORMAL, nullptr);
	//BGMの読み込み
	for (const auto& bgmDatas : json["BGM"])
	{
		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{
			// キーと値を取得
			std::string key = it.key();
			std::string pathStr = it.value();
			// std::stringをstd::wstringに変換
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());
			FMOD::Sound* sound;
			system->createSound(path.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);

			m_soundList[key] = sound;

		}

	}


	//SEの読み込み
	for (const auto& bgmDatas : json["SE"])
	{

		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{

			// キーと値を取得
			std::string key = it.key();
			std::string pathStr = it.value();

			// std::stringをstd::wstringに変換
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());

			FMOD::Sound* sound;
			
			system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &sound);



			m_soundList[key] = sound;

		}

	}
}






