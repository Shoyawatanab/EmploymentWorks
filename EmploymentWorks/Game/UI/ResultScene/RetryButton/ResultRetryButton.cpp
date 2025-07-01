#include "pch.h"
#include "ResultRetryButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
ResultRetryButton::ResultRetryButton(Canvas* canvas)
	:
	Button(canvas, "ResultRetry")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ResultRetryButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ResultRetryButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&ResultRetryButton::OutOfRange, this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultRetryButton::~ResultRetryButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void ResultRetryButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void ResultRetryButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void ResultRetryButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}
