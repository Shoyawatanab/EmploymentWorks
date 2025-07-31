/*
	�N���X��     : DecisionButton
	����         : �Z���N�g�V�[���̌���̃{�^��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "DecisionButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
DecisionButton::DecisionButton(Canvas* canvas)
	:
	Button(canvas, "SelectPlay")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&DecisionButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&DecisionButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&DecisionButton::OutOfRange,this));


	//NormalGraund

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DecisionButton::~DecisionButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void DecisionButton::OnClick()
{

	//GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	GetScene()->ChangeScene(SceneManager::SceneID::PLAY);

	FadeManager::GetInstance()->StartFadeIn();


}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void DecisionButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void DecisionButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
