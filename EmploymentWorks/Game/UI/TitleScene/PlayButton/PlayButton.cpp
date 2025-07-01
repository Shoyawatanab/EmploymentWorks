#include "pch.h"
#include "PlayButton.h"
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
PlayButton::PlayButton(Canvas* canvas)
	:
	Button(canvas, "PLAY")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&PlayButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&PlayButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&PlayButton::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayButton::~PlayButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void PlayButton::OnClick()
{
	
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_SELECT_SCENE);

	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void PlayButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void PlayButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
