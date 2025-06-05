#include "pch.h"
#include "UIStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
UIStateMachine::UIStateMachine()
	:
	m_currentState{}
	, m_playUi{}
{

	m_playUi = std::make_unique<GamePlayUI>();
	m_gameEndUI = std::make_unique<GameEndUI>();

}

/// <summary>
/// デストラクタ
/// </summary>
UIStateMachine::~UIStateMachine()
{
}



/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="playScene">プレイシーン</param>
/// <param name="enemyManager">エネミーマネージャー</param>
void UIStateMachine::AddPointer(PlayScene* playScene)
{
	m_gameEndUI->AddPointer(playScene);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void UIStateMachine::Initialize(CommonResources* resources, IUIState* startState)
{

	m_playUi->Initialize(resources);
	m_gameEndUI->Initialize(resources);

	m_currentState = startState;



}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void UIStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void UIStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}


/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void UIStateMachine::ChangeState(IUIState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


