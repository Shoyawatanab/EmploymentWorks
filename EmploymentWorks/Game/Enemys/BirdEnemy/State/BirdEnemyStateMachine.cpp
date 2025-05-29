#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Observer/Messenger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyStateMachine::BirdEnemyStateMachine(BirdEnemy* owner, std::vector<std::unique_ptr<BirdEnemyBeam>>& beam)
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_move{}
{
	m_idle = std::make_unique<BirdEnemyldling>(owner);
	m_attack = std::make_unique<BirdEnemyAttack>(owner, beam);
	m_move = std::make_unique<BirdEnemyMove>(owner);


	Messenger::GetInstance()->Rigister(owner->GetID(), this);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{



}




/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="startState">s初期のステート</param>
void BirdEnemyStateMachine::Initialize()
{

	m_idle->Initialize();
	m_attack->Initialize();
	m_move->Initialize();

	m_currentState = m_idle.get();



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



void BirdEnemyStateMachine::Notify(const Telegram<EnemyMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case EnemyMessageType::IDLING:
			ChangeState(m_idle.get());
			break;

		case EnemyMessageType::MOVEING:
			ChangeState(m_move.get());
			break;
		case EnemyMessageType::BEAM_ATTACK:
			ChangeState(m_attack.get());
			break;
		default:
			break;
	}

}


