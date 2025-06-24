#include "pch.h"
#include "BirdEnemyBulletStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStates.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBulletStateMachine::BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
{

	//IDEL状態の追加
	AddState(BirdEnemyBulletState::IDEL, std::make_unique<BirdEnemyBulletIdle>(this, bullet,birdEnemy));
	//Chage状態の追加
	AddState(BirdEnemyBulletState::CHAGE, std::make_unique<BirdEnemyBulletCharge>(this, bullet,birdEnemy));
	//Shot状態の追加
	AddState(BirdEnemyBulletState::SHOT, std::make_unique<BirdEnemyBulletShot>(this, bullet,birdEnemy));

	//初期ステートの設定
	SetStartState(BirdEnemyBulletState::IDEL);


	Messenger::GetInstance()->Rigister(
		{
			MessageType::BIRD_BULLET_IDLE_STATE
			,MessageType::BIRD_BULLET_CHAGE_STATE
			,MessageType::BIRD_BULLET_SHOT_STATE
		}, this
	);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBulletStateMachine::~BirdEnemyBulletStateMachine()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BirdEnemyBulletStateMachine::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::BIRD_BULLET_IDLE_STATE:
			ChangeState(BirdEnemyBulletState::IDEL);
			break;
		case MessageType::BIRD_BULLET_CHAGE_STATE:
			ChangeState(BirdEnemyBulletState::CHAGE);
			break;
		case MessageType::BIRD_BULLET_SHOT_STATE:
			ChangeState(BirdEnemyBulletState::SHOT);
			break;
		default:
			break;
	}

}
