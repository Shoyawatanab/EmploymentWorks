#include "pch.h"
#include "PlayButtom.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
PlayButtom::PlayButtom(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_exitButton{}
{
	using namespace DirectX::SimpleMath;

	m_exitButton = GetScene()->AddActor<Button>(canvas, "PLAY");
	m_exitButton->GetTransform()->SetScale(SCALE);
	m_exitButton->GetTransform()->SetPosition(POSITOIN);

	auto comp = m_exitButton->GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&PlayButtom::OnClick, this));
	comp->SetInRangeFunction(std::bind(&PlayButtom::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&PlayButtom::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
PlayButtom::~PlayButtom()
{
}

/// <summary>
/// クリック時
/// </summary>
void PlayButtom::OnClick()
{
	
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_SELECT_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
}

/// <summary>
/// 範囲内になった時
/// </summary>
void PlayButtom::InRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void PlayButtom::OutOfRange()
{
	m_exitButton->GetTransform()->SetScale(SCALE);

}
