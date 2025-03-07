#include "pch.h"
#include "BirdEnemyStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyStateMachine::BirdEnemyStateMachine()
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_move{}
{
	m_idle = std::make_unique<BirdEnemyldling>();
	m_attack = std::make_unique<BirdEnemyAttack>();
	m_move = std::make_unique<BirdEnemyMove>();
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{



}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="enemy">鳥の敵</param>
void BirdEnemyStateMachine::AddPointer(Player* player, BirdEnemy* enemy)
{
	m_idle->AddPointer(player,enemy);
	m_attack->AddPointer(player,enemy);
	m_move->AddPointer(player, enemy);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="startState">s初期のステート</param>
void BirdEnemyStateMachine::Initialize(CommonResources* resources, IState* startState)
{

	m_idle->Initialize(resources);
	m_attack->Initialize(resources);
	m_move->Initialize(resources);

	m_currentState = startState;



}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BirdEnemyStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


