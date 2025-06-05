#include "pch.h"
#include "BirdEnemyBeamStateMachine.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="enemy">鳥の敵</param>
/// <param name="beam">ビーム</param>
BirdEnemyBeamStateMachine::BirdEnemyBeamStateMachine(BirdEnemy* enemy, BirdEnemyBeam* beam)
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_preliminaryAction{}
{
	//各ステートを生成
	m_idle = std::make_unique<BirdEnemyBeamIdling>(enemy,beam);
	m_attack = std::make_unique<BirdEnemyBeamAttack>(enemy,beam);
	m_preliminaryAction = std::make_unique<BirdEnemyBeamPreliminaryAction>( enemy, beam);
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamStateMachine::~BirdEnemyBeamStateMachine()
{



}



/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BirdEnemyBeamStateMachine::Initialize()
{
	//初期化
	m_idle->Initialize();
	m_attack->Initialize();
	m_preliminaryAction->Initialize();
	//初期状態を設定

	m_currentState = m_idle.get();

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeamStateMachine::Update(const float& elapsedTime)
{
	//ステートを更新
	m_currentState->Update(elapsedTime);
}



/// <summary>
/// 状態変更
/// </summary>
/// <param name="nextState">次の状態</param>
void BirdEnemyBeamStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


