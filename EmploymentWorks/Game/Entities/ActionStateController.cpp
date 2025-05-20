#include "pch.h"
#include "ActionStateController.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
ActionStateController::ActionStateController()
	:
	m_actionState{}
	,m_currentIndex{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
ActionStateController::~ActionStateController()
{
	m_actionState.clear();
}

/// <summary>
/// 初期化
/// </summary>
void ActionStateController::Initialize(std::vector<IAction*> actions)
{

	m_actionState = actions;

	m_currentIndex = 0;

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
IAction::ActionState ActionStateController::Update(const float& elapsedTime)
{
	//状態の更新
	if(m_actionState[m_currentIndex]->Update(elapsedTime) == IAction::ActionState::END)
	{
		//状態が終わったら
		ChangeState();
		//すべての状態が終わった
		if (m_currentIndex >= m_actionState.size())
		{

			return IAction::ActionState::END;

		}

	}


	return IAction::ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void ActionStateController::Enter()
{

	m_currentIndex = 0;


	if (!m_actionState.empty())
	{
		m_actionState[m_currentIndex]->Enter();
	}


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void ActionStateController::Exit()
{
	m_currentIndex = 0;
}

/// <summary>
/// 状態の切り替え
/// </summary>
void ActionStateController::ChangeState()
{
	//初期化段階では行わないように
	if (m_currentIndex != 0)
	{
		//状態を抜けた時の処理
		m_actionState[m_currentIndex]->Exit();
	}

	m_currentIndex++;

	//最後のStateが終わったら
	if (m_currentIndex >= m_actionState.size())
	{
		return;
	}
	//状態に入った時の処理
	m_actionState[m_currentIndex]->Enter();
}

