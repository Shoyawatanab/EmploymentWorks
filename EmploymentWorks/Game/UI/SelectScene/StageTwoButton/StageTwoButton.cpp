#include "pch.h"
#include "StageTwoButton.h"
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
StageTwoButton::StageTwoButton(Canvas* canvas)
	:
	Button(canvas, "Stage1")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageTwoButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageTwoButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageTwoButton::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageTwoButton::~StageTwoButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void StageTwoButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//�I���X�e�[�W�ԍ��̃Z�b�g
	GlobalGameData::GetInstance()->SetSelectStateNumber(2);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void StageTwoButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void StageTwoButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
