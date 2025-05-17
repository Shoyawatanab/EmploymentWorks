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

IAction::ActionState ActionStateController::Update(const float& elapsedTime)
{

	if(m_actionState[m_currentIndex]->Update(elapsedTime) == IAction::ActionState::End)
	{
		ChangeState();

		if (m_currentIndex >= m_actionState.size())
		{

			return IAction::ActionState::End;

		}

	}


	return IAction::ActionState::Running;

}

void ActionStateController::Enter()
{

	m_currentIndex = 0;


	if (!m_actionState.empty())
	{
		m_actionState[m_currentIndex]->Enter();
	}


}

void ActionStateController::Exit()
{
	m_currentIndex = 0;
}

void ActionStateController::ChangeState()
{
	//初期化段階では行わないように
	if (m_currentIndex != 0)
	{
		m_actionState[m_currentIndex]->Exit();
	}

	m_currentIndex++;

	//最後のStateが終わったら
	if (m_currentIndex >= m_actionState.size())
	{
		return;
	}
	
	m_actionState[m_currentIndex]->Enter();
}

