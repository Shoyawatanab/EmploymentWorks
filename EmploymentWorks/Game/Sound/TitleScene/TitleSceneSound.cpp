/*
	�N���X��     : TitleSceneSound
	����         : �^�C�g���V�[���̉�
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "TitleSceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
TitleSceneSound::TitleSceneSound(Scene* scene)
	:
	Actor(scene)
{

	//BGM�̍쐬
	m_bgm = AddComponent<SoundComponent>(this, "Title", SoundComponent::SoundType::BGM);
	//�Đ�
	m_bgm->Play();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleSceneSound::~TitleSceneSound()
{
	//BGM�̒�~
	m_bgm->Stop();
}
