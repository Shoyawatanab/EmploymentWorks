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
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
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
/// デストラクタ
/// </summary>
StageTwoButtom::~StageTwoButtom()
{
}

/// <summary>
/// クリック時
/// </summary>
void StageTwoButtom::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//選択ステージ番号のセット
	GlobalGameData::GetInstance()->SetSelectStateNumber(2);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void StageTwoButtom::InRange()
{
	m_button->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void StageTwoButtom::OutOfRange()
{
	m_button->GetTransform()->SetScale(SCALE);

}
