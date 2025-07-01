#include "pch.h"
#include "StageOneButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageOneButton::StageOneButton(Canvas* canvas)
	:
	Button(canvas, "Tutorial")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageOneButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageOneButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageOneButton::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageOneButton::~StageOneButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void StageOneButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//�I���X�e�[�W�ԍ��̃Z�b�g
	GlobalGameData::GetInstance()->SetSelectStateNumber(1);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void StageOneButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void StageOneButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
