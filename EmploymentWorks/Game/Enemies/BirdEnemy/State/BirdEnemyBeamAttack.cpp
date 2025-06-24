#include "pch.h"
#include "BirdEnemyBeamAttack.h"
#include "Game/Messenger/Messenger.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBeamAttack::BirdEnemyBeamAttack(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_birdEnemy{ birdEnemy }
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamAttack::~BirdEnemyBeamAttack()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBeamAttack::Update(const float& deltaTime)
{
	
	//弾が発射されたらステートを切り替える



}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBeamAttack::Enter()
{
	//弾をチャージに
	Messenger::GetInstance()->Notify(MessageType::BIRD_BULLET_CHAGE_STATE);
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBeamAttack::Exit()
{
}
