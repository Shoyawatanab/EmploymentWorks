#include "pch.h"
#include "StageOneButtom.h"
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
StageOneButtom::StageOneButtom(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	, m_button{}
{
	using namespace DirectX::SimpleMath;

	m_button = GetScene()->AddActor<Button>(canvas, "Tutorial");
	m_button->GetTransform()->SetScale(SCALE);
	m_button->GetTransform()->SetPosition(POSITOIN);

	auto comp = m_button->GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageOneButtom::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageOneButtom::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageOneButtom::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
StageOneButtom::~StageOneButtom()
{
}

/// <summary>
/// クリック時
/// </summary>
void StageOneButtom::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//選択ステージ番号のセット
	GlobalGameData::GetInstance()->SetSelectStateNumber(1);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void StageOneButtom::InRange()
{
	m_button->GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void StageOneButtom::OutOfRange()
{
	m_button->GetTransform()->SetScale(SCALE);

}
