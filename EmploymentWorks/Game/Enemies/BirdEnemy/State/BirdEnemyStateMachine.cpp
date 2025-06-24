#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
#include "Game/Messenger/Messenger.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyStateMachine::BirdEnemyStateMachine(BirdEnemy* birdEnemy)
{

	//IDEL状態の追加
	AddState(BirdEnemyState::IDEL, std::make_unique<BirdEnemyIdle>(this, birdEnemy));
	//Move状態の追加
	AddState(BirdEnemyState::MOVE, std::make_unique<BirdEnemyMove>(this, birdEnemy));
	//BeamAttack状態の追加
	AddState(BirdEnemyState::BEAM_ATTACK, std::make_unique<BirdEnemyBeamAttack>(this, birdEnemy));

	//初期ステートの設定
	SetStartState(BirdEnemyState::IDEL);


	Messenger::GetInstance()->Rigister(
		{
			MessageType::BIRD_IDLE_STATE
			,MessageType::BIRD_MOVE_STATE
			,MessageType::BIRD_BEAM_ATTACK_STATE
		}, this
	);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BirdEnemyStateMachine::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::BIRD_IDLE_STATE:
			ChangeState(BirdEnemyState::IDEL);
			break;
		case MessageType::BIRD_MOVE_STATE:
			ChangeState(BirdEnemyState::MOVE);
			break;
		case MessageType::BIRD_BEAM_ATTACK_STATE:
			ChangeState(BirdEnemyState::BEAM_ATTACK);
			break;
		default:
			break;
	}

}
