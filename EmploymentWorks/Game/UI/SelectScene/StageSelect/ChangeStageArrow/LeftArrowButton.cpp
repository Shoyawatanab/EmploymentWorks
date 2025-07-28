/*
	�N���X��     : LeftArrowButton
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̍����UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "LeftArrowButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
LeftArrowButton::LeftArrowButton(Canvas* canvas)
	:
	Button(canvas, "SelectSceneArow")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(
		ROTATE.y, ROTATE.x, ROTATE.z));

	auto image = GetComponent<ImageComponent>();
	image->SetAngle(DirectX::XMConvertToRadians(90.0f));

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&LeftArrowButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&LeftArrowButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&LeftArrowButton::OutOfRange,this));


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LeftArrowButton::~LeftArrowButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void LeftArrowButton::OnClick()
{

	SceneMessenger::GetInstance()->Notify(SceneMessageType::STAGE_DOWN);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void LeftArrowButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void LeftArrowButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
