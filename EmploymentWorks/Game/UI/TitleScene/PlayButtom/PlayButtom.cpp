#include "pch.h"
#include "PlayButtom.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
PlayButtom::PlayButtom(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_exitButton{}
{
	using namespace DirectX::SimpleMath;

	m_exitButton = GetScene()->AddActor<Button>(canvas, "PLAY");
	m_exitButton->GetTransform()->SetScale(SCALE);
	m_exitButton->GetTransform()->SetPosition(POSITOIN);

	auto comp = m_exitButton->GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&PlayButtom::OnClick, this));
	comp->SetInRangeFunction(std::bind(&PlayButtom::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&PlayButtom::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayButtom::~PlayButtom()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void PlayButtom::OnClick()
{
	
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_SELECT_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void PlayButtom::InRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void PlayButtom::OutOfRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE);

}
