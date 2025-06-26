#include "pch.h"
#include "FadeManager.h"
#include "Game/Fade/FadeKindss.h"



/// <summary>
/// �R���X�g���N
/// </summary>
FadeManager::FadeManager()
	:
	m_currentFade{}
	,m_fadeState{FadeState::NONE}
	, m_fadeInList{}
	,m_fadeOutList{}
	, m_isFade{ false }
{
	
	//�t�F�[�h�C���̍쐬
	AddFadeIn(FadeInKinds::NORMAL_FADE_IN,std::make_unique<NormalFadeIn>());
	
	//�t�F�[�h�A�E�g�̍쐬
	AddFadeOut(FadeOutKinds::NORMAL_FADE_OUT, std::make_unique<NormalFadeOut>());



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FadeManager::~FadeManager()
{
	
	m_fadeInList.clear();
	m_fadeOutList.clear();
	
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void FadeManager::Update(const float& deltaTime)
{
	//���s���łȂ��Ȃ�
	if (m_fadeState == FadeState::NONE)
	{
		return;
	}

	//�t�F�[�h�̍X�V
	auto isEnd = m_currentFade->Update(deltaTime);
	
	//�I�������
	if (isEnd)
	{
		switch (m_fadeState)
		{
			case FadeManager::FadeState::FADE_IN:
				m_fadeState = FadeState::FADE_IN_END;
				break;
			case FadeManager::FadeState::FADE_OUT:
				m_isFade = false;
				m_fadeState = FadeState::NONE;
				break;
			default:
				break;
		}
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera"></param>
void FadeManager::Render()
{

	//���s���łȂ��Ȃ�
	if (m_fadeState == FadeState::NONE)
	{
		return;
	}

	m_currentFade->Render();

}


/// <summary>
/// �t�F�[�h�̃X�^�[�g
/// </summary>
/// <param name="startFade">���s�t�F�[�h</param>
void FadeManager::StartFadeIn(FadeInKinds kinds)
{
	//�t�F�[�h�����s����Ă��Ȃ��Ȃ�
	if (m_fadeState != FadeState::NONE)
	{
		return;
	}

	//���邩
	auto it = m_fadeInList.find(kinds);
	//�Ȃ����
	if (it == m_fadeInList.end())
	{
		return;
	}

	//���s�t�F�[�h�̐؂�ւ�
	ChangeFade(m_fadeInList[kinds].get());
	//��Ԃ̕ύX
	m_fadeState = FadeState::FADE_IN;
	m_isFade = true;
}

/// <summary>
/// �t�F�[�h�̃X�^�[�g�@�m�[�}���t�F�[�h
/// </summary>
void FadeManager::StartFadeIn()
{
	//�t�F�[�h�����s����Ă��Ȃ��Ȃ�
	if (m_fadeState != FadeState::NONE)
	{
		return;
	}

	//���s�t�F�[�h�̐؂�ւ�
	ChangeFade(m_fadeInList[FadeInKinds::NORMAL_FADE_IN].get());
	//
	m_fadeState = FadeState::FADE_IN;

	m_isFade = true;

}

void FadeManager::StartFadeOut(FadeOutKinds kinds)
{

	//�t�F�[�h�C������Ȃ��Ȃ�
	if (m_fadeState != FadeState::FADE_IN_END)
	{
		return;
	}

	//���邩
	auto it = m_fadeOutList.find(kinds);
	//�Ȃ����
	if (it == m_fadeOutList.end())
	{
		return;
	}

	//���s�t�F�[�h�̐؂�ւ�
	ChangeFade(m_fadeOutList[kinds].get());
	//��Ԃ̕ύX
	m_fadeState = FadeState::FADE_OUT;

}

void FadeManager::StartFadeOut()
{

	//�t�F�[�h�C������Ȃ��Ȃ�
	if (m_fadeState != FadeState::FADE_IN_END)
	{
		return;
	}

	//���s�t�F�[�h�̐؂�ւ�
	ChangeFade(m_fadeOutList[FadeOutKinds::NORMAL_FADE_OUT].get());

	//
	m_fadeState = FadeState::FADE_OUT;
}

/// <summary>
/// �t�F�[�h�C���̒ǉ�
/// </summary>
/// <param name="kinds">�t�F�[�h�̎��</param>
/// <param name="fade">�t�F�[�h�N���X</param>
void FadeManager::AddFadeIn(FadeInKinds kinds, std::unique_ptr<IFade> fade)
{

	m_fadeInList[kinds] = std::move(fade);

}

/// <summary>
/// �t�F�[�h�A�E�g�̒ǉ�
/// </summary>
/// <param name="kinds">�t�F�[�h�̎��</param>
/// <param name="fade">�t�F�[�h�N���X</param>
void FadeManager::AddFadeOut(FadeOutKinds kinds, std::unique_ptr<IFade> fade)
{

	m_fadeOutList[kinds] = std::move(fade);

}



/// <summary>
/// �t�F�[�h�̐؂�ւ�
/// </summary>
/// <param name="fade">�؂�ւ���t�F�[�h</param>
void FadeManager::ChangeFade(IFade* fade)
{
	if (m_currentFade)
	{
		m_currentFade->Exit();
	}
	m_currentFade = fade;
	m_currentFade->Enter();
}





