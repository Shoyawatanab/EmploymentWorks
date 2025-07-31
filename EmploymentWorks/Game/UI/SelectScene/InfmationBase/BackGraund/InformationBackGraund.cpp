/*
	クラス名     : InformationBackGraund
	説明         : セレクトシーンの右の情報の背景
	補足・注意点 :
*/
#include "pch.h"
#include "InformationBackGraund.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
InformationBackGraund::InformationBackGraund(Canvas* canvas)
	:
	Image(canvas, "SelectInfBase")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// デストラクタ
/// </summary>
InformationBackGraund::~InformationBackGraund()
{
}

