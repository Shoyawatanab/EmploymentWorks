/*
	クラス名     : IdleingAction
	説明         : ボス敵の通常のコントローラー
	補足・注意点 :
*/
#include "pch.h"
#include "IdleingActionComtroller.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/Idle/IdleingAction.h"




/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
IdleingActionComtroller::IdleingActionComtroller()
{

	m_idle = std::make_unique<IdleingAction>();

	AddAction(
		{
			m_idle.get()
		}
	);

}

/// <summary>
/// デストラクタ
/// </summary>
IdleingActionComtroller::~IdleingActionComtroller()
{
	// do nothing.
}


