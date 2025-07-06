#include "pch.h"
#include "PlaySceneSound.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneSound::PlaySceneSound(Scene* scene)
	:
	Actor(scene)
{
	//BGM�̍쐬
	m_bgm = AddComponent<SoundComponent>(this, "Play", SoundComponent::SoundType::BGM);
	//�Đ�
	//m_bgm->Play();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneSound::~PlaySceneSound()
{
	//BGM�̒�~
	m_bgm->Stop();
}
