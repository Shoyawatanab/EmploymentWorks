#include "pch.h"
#include "RetryButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
RetryButton::RetryButton(Canvas* canvas)
	:
	Button(canvas, "ClearReTryTex")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&RetryButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&RetryButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&RetryButton::OutOfRange, this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RetryButton::~RetryButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void RetryButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void RetryButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void RetryButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}
