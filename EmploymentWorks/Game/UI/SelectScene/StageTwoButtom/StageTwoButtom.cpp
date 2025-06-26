#include "pch.h"
#include "StageTwoButtom.h"
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
StageTwoButtom::StageTwoButtom(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	, m_button{}
{
	using namespace DirectX::SimpleMath;

	m_button = GetScene()->AddActor<Button>(canvas, "Stage1");
	m_button->GetTransform()->SetScale(SCALE);
	m_button->GetTransform()->SetPosition(POSITOIN);

	auto comp = m_button->GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageTwoButtom::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageTwoButtom::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageTwoButtom::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageTwoButtom::~StageTwoButtom()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void StageTwoButtom::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//�I���X�e�[�W�ԍ��̃Z�b�g
	GlobalGameData::GetInstance()->SetSelectStateNumber(2);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void StageTwoButtom::InRange()
{
	m_button->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void StageTwoButtom::OutOfRange()
{
	m_button->GetTransform()->SetScale(SCALE);

}
