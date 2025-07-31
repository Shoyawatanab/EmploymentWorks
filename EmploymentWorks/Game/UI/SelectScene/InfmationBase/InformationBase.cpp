/*
	クラス名     : InformationBase
	説明         : セレクトシーンの右の情報のまとめクラス
	補足・注意点 :
*/
#include "pch.h"
#include "InformationBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"
#include "Game/UI/SelectScene/InfmationBase/BackGraund/InformationBackGraund.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
InformationBase::InformationBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;


	//背景
	GetScene()->AddActor<InformationBackGraund>(canvas);




}

/// <summary>
/// デストラクタ
/// </summary>
InformationBase::~InformationBase()
{
}

