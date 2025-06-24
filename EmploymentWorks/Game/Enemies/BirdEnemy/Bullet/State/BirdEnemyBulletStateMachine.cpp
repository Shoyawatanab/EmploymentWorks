#include "pch.h"
#include "BirdEnemyBulletStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStates.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="birdEnemy">���G</param>
BirdEnemyBulletStateMachine::BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
{

	//IDEL��Ԃ̒ǉ�
	AddState(BirdEnemyBulletState::IDEL, std::make_unique<BirdEnemyBulletIdle>(this, bullet,birdEnemy));
	//Chage��Ԃ̒ǉ�
	AddState(BirdEnemyBulletState::CHAGE, std::make_unique<BirdEnemyBulletCharge>(this, bullet,birdEnemy));
	//Shot��Ԃ̒ǉ�
	AddState(BirdEnemyBulletState::SHOT, std::make_unique<BirdEnemyBulletShot>(this, bullet,birdEnemy));

	//�����X�e�[�g�̐ݒ�
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
/// �f�X�g���N�^
/// </summary>
BirdEnemyBulletStateMachine::~BirdEnemyBulletStateMachine()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
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
