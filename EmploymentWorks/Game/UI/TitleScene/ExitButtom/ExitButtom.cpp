#include "pch.h"
#include "ExitButtom.h"
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
ExitButtom::ExitButtom(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_exitButton{}
{
	using namespace DirectX::SimpleMath;

	m_exitButton = GetScene()->AddActor<Button>(canvas, "EXIT");
	m_exitButton->GetTransform()->SetScale(SCALE);
	m_exitButton->GetTransform()->SetPosition(POSITOIN);

	auto comp = m_exitButton->GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ExitButtom::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ExitButtom::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&ExitButtom::OutOfRange,this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ExitButtom::~ExitButtom()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void ExitButtom::OnClick()
{
	
	PostQuitMessage(0);

}

/// <summary>
/// �͈͓��ɂȂ�����
/// </summary>
void ExitButtom::InRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// �͈͊O�ɂȂ�����
/// </summary>
void ExitButtom::OutOfRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE);

}
