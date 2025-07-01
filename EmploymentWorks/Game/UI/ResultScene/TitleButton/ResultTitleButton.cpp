#include "pch.h"
#include "ResultTitleButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
ResultTitleButton::ResultTitleButton(Canvas* canvas)
	:
	Button(canvas, "ResultTitle")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);



	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ResultTitleButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ResultTitleButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&ResultTitleButton::OutOfRange, this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultTitleButton::~ResultTitleButton()
{
}



/// <summary>
/// �N���b�N��
/// </summary>
void ResultTitleButton::OnClick()
{
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_TITLE_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void ResultTitleButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void ResultTitleButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}


