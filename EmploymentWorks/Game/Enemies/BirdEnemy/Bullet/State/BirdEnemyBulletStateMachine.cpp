#include "pch.h"
#include "BirdEnemyBulletStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
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





}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBulletStateMachine::~BirdEnemyBulletStateMachine()
{
}


