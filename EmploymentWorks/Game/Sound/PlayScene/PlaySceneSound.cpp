/*
	�N���X��     : PlaySceneSound
	����         : �v���C�V�[���̉�
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlaySceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneSound::PlaySceneSound(Scene* scene)
	:
	Actor(scene)
{

	std::string BGMName ="Stage1";

	switch (GlobalGameData::GetInstance()->GetSelectStageNumber())
	{
		case 1:
			BGMName = "Stage1";
			break;
		case 2:
			BGMName = "Stage2";
			break;
		default:
			break;
	}

	//BGM�̍쐬
	m_bgm = AddComponent<SoundComponent>(this, BGMName, SoundComponent::SoundType::BGM);
	//�Đ�
	m_bgm->Play();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneSound::~PlaySceneSound()
{
	//BGM�̒�~
	m_bgm->Stop();
}
