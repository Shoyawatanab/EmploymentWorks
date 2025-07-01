#include "pch.h"
#include "GameOverUI.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"

#include "Game/UI/PlayScene/GameOver/BackGraund/GameOverBackGraund.h"
#include "Game/UI/PlayScene/GameOver/RetryButton/RetryButton.h"
#include "Game/UI/PlayScene/GameOver/TitleButton/TitleButton.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
GameOverUI::GameOverUI(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_backGraund{}
	,m_retryButton{}
	,m_titleButton{}
{

	m_backGraund = GetScene()->AddActor<GameOverBackGraund>(canvas);
	m_backGraund->GetTransform()->SetParent(GetTransform());
	m_backGraund->SetActive(false);

	m_retryButton = GetScene()->AddActor<RetryButton>(canvas);
	m_retryButton->GetTransform()->SetParent(GetTransform());
	m_retryButton->SetActive(false);

	m_titleButton = GetScene()->AddActor<TitleButton>(canvas);
	m_titleButton->GetTransform()->SetParent(GetTransform());
	m_titleButton->SetActive(false);

	m_backGraund->SetActor(
		{
			m_retryButton
			,m_titleButton
		}
	);



	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::GAME_OVER
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOverUI::~GameOverUI()
{
}

/// <summary>
/// �P�̍X�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void GameOverUI::UpdateActor(const float& deltaTime)
{



}


/// <summary>
/// �A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
/// </summary>
void GameOverUI::OnEnable()
{



}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void GameOverUI::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::GAME_OVER:
			if (!m_backGraund->GetActive())
			{
				m_backGraund->SetActive(true);

			}
			break;
		default:
			break;
	}

}
