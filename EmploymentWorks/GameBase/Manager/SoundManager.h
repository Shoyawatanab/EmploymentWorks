/*
	�N���X��     : SoundManager
	����         : �T�E���h�}�l�[�W���[
	�⑫�E���ӓ_ : Scene�Ő錾
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"
#include "GameBase/Component/Sound/SoundComponent.h"

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
	//�R���X�g���N
	SoundManager();
	//�f�X�g���N�^
	~SoundManager() override;

	//�X�V����
	void Update();

	//BGM�̍Đ�
	void PlayBGM(FMOD::Sound** sound);
	//SE�̍Đ�
	void PlaySE(FMOD::Sound** sound);
	//BGM�̒�~
	void StopBGM();

	//�T�E���h�̍쐬
	void MakeSound(const std::string& soundName, SoundComponent::SoundType type,FMOD::Sound** sound);

private:

	//�f�[�^�̓ǂݍ���
	void LoadSound();

private:

	//�V�X�e��
	FMOD::System* m_system;
	//BGM�`�����l��
	FMOD::Channel* m_channel;
	//���̃p�X�̕ۑ����X�g
	std::unordered_map<std::string, std::string> m_soundPathList;


};