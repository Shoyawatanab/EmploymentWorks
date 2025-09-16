/*
	�N���X��     : PlayButton
	����         : �^�C�g���V�[����Play�{�^����UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayButton.h"
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
	
	//�V�[���؂�ւ�
	GetScene()->ChangeScene(SceneManager::SceneID::STAGESELECT);


	FadeManager::GetInstance()->StartFadeIn(FadeManager::FadeInKinds::BOMERANG_FADE_IN);

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
