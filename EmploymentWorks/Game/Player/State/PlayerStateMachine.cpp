/*
	�N���X��     : PlayerStateMachine
	����         : �v���C���̃u�[�������̃X�e�[�g�}�V�[��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Player//State/PlayerStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerStateMachine::PlayerStateMachine(Player* player)
{
	//Messenger::GetInstance()->Rigister<PlayerMessageType>(player->GetID(), this);
	
	//IDEL��Ԃ̒ǉ�
	AddState(PlayerState::IDEL,std::make_unique<PlayerIdle>(this, player));
	//BOOMERANG_ATTACK��Ԃ̒ǉ�
	AddState(PlayerState::BOOMERANG_ATTACK, std::make_unique<PlayerBoomerangAttack>(this, player));
	//BOOMERANG_GETREADY���
	AddState(PlayerState::BOOMERANG_GET_READY, std::make_unique<PlayerBoomerangGetReady>(this, player));

	SetStartState(PlayerState::IDEL);


	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = player->AddComponent<ObserverComponent<SceneMessageType>>(player);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			 SceneMessageType::PLAYER_IDLE_STATE
			,SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE
			,SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE
		}
		, std::bind(&PlayerStateMachine::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerStateMachine::Notify(SceneMessageType type, void* datas)
{

	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::PLAYER_IDLE_STATE:
			ChangeState(PlayerState::IDEL);
			break;
		case SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE:
			ChangeState(PlayerState::BOOMERANG_GET_READY);
			break;
		case SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE:
			ChangeState(PlayerState::BOOMERANG_ATTACK);
			break;
		default:
			break;
	}

}


