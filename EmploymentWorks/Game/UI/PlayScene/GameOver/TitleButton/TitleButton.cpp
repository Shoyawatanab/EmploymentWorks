#include "pch.h"
#include "TitleButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
TitleButton::TitleButton(Canvas* canvas)
	:
	Button(canvas, "ClearTitleTex")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&TitleButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&TitleButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&TitleButton::OutOfRange, this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleButton::~TitleButton()
{
}



/// <summary>
/// �N���b�N��
/// </summary>
void TitleButton::OnClick()
{
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_TITLE_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void TitleButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void TitleButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}


