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
	friend class Singleton<SoundManager>;

public:
	//サウンドのJsonファイル
	static const wchar_t* SOUND_JSON;
	static const char* SOUND_BASE_PATH;


public:
	//コンストラク
	SoundManager();
	//デストラクタ
	~SoundManager() override ;
	//初期化
	void Initialize();
	//更新処理
	void  Update() ;
	//BGMの再生
	void PlaySoundBGM(std::string key);
	//SEの再生
	void PlaySoundSE(std::string key);


private:
	//音の読み込み
	void LoadSound();

private:
	//システム
	FMOD::System* m_system;
	//サウンド
	FMOD::Sound* m_sound;
	//SEチャンネル
	FMOD::Channel* m_channelSE;
	//BGMチャンネル
	FMOD::Channel* m_channelBGM;
	//音の保存リスト
	std::unordered_map<std::string, FMOD::Sound*> m_soundList;

};
