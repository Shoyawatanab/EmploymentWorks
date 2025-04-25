#pragma once
/*
	@file	SoundManager.h.h
	@brief	プレイシーンクラス
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
	//サウンドのJsonファイル
	static const wchar_t* SOUND_JSON;
	static const char* SOUND_BASE_PATH;


public:
	SoundManager();
	~SoundManager() ;

	void Initialize();

	//更新処理
	void  Update() ;
	//BGMの再生
	void PlaySoundBGM(std::string key);
	//SEの再生
	void PlaySoundSE(std::string key);
	//サウンド情報の削除
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
