#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
#include "Game/Messenger/Messenger.h"

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
	AddState(BirdEnemyState::BEAM_ATTACK, std::make_unique<BirdEnemyBeamAttack>(this, birdEnemy));

	//�����X�e�[�g�̐ݒ�
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
/// �f�X�g���N�^
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
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
