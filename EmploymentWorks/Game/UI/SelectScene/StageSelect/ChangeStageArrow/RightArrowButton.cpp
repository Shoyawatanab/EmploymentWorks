/*
	�N���X��     : RightArrowButton
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̉E���UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "RightArrowButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"


#include "Game/Messenger/Messengers.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
RightArrowButton::RightArrowButton(Canvas* canvas)
	:
	Button(canvas, "SelectSceneArow")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(
		ROTATE.y, ROTATE.x, ROTATE.z));

	auto image = GetComponent<ImageComponent>();
	image->SetAngle(DirectX::XMConvertToRadians(270.0f));


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&RightArrowButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&RightArrowButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&RightArrowButton::OutOfRange,this));




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RightArrowButton::~RightArrowButton()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void RightArrowButton::OnClick()
{

	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::STAGE_UP);
}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void RightArrowButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void RightArrowButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
