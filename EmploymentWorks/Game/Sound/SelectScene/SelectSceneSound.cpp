/*
	�N���X��     : SelectSceneSound
	����         : �^�C�g���V�[���̉�
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "SelectSceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
SelectSceneSound::SelectSceneSound(Scene* scene)
	:
	Actor(scene)
{

	//BGM�̍쐬
	m_bgm = AddComponent<SoundComponent>(this, "StageSelect", SoundComponent::SoundType::BGM);
	//�Đ�
	//m_bgm->Play();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectSceneSound::~SelectSceneSound()
{
	//BGM�̒�~
	m_bgm->Stop();
}
