#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="birdEnemy">���G</param>
BirdEnemyStateMachine::BirdEnemyStateMachine(BirdEnemy* birdEnemy)
{

	//IDEL��Ԃ̒ǉ�
	AddState(BirdEnemyState::IDEL, std::make_unique<BirdEnemyIdle>(this, birdEnemy));
	//Move��Ԃ̒ǉ�
	AddState(BirdEnemyState::MOVE, std::make_unique<BirdEnemyMove>(this, birdEnemy));
	//BeamAttack��Ԃ̒ǉ�
	AddState(BirdEnemyState::BULLET_ATTACK, std::make_unique<BirdEnemyBeamAttack>(this, birdEnemy));

	//�����X�e�[�g�̐ݒ�
	SetStartState(BirdEnemyState::IDEL);





}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{
}

