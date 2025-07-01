#include "pch.h"
#include "ExitButton.h"
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
ExitButton::ExitButton(Canvas* canvas)
	:
	Button(canvas, "EXIT")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ExitButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ExitButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&ExitButton::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ExitButton::~ExitButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void ExitButton::OnClick()
{
	
	PostQuitMessage(0);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void ExitButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void ExitButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
