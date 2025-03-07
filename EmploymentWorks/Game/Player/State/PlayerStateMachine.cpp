#include "pch.h"
#include "PlayerStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerStateMachine::PlayerStateMachine()
	:
	m_currentState{}
	,m_idle{}
{
	m_idle = std::make_unique<PlayerIdle>();
	m_attack = std::make_unique<PlayerAttack>();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void PlayerStateMachine::AddPointer(Player* player)
{
	m_idle->AddPointer(player);
	m_attack->AddPointer(player);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="startState">初期ステート</param>
void PlayerStateMachine::Initialize(CommonResources* resources, IState* startState)
{

	m_idle->Initialize(resources);
	m_attack->Initialize(resources);

	m_currentState = startState;



}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void PlayerStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void PlayerStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


