#include "pch.h"
#include "BoomerangStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStates.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="boomerang">�u�[������</param>
BoomerangStateMachine::BoomerangStateMachine(Boomerang* boomerang, Player* player)
{

	//IDLE
	AddState(BoomerangState::IDEL, std::make_unique<BoomerangIdle>(this, boomerang,player));
	AddState(BoomerangState::THROW, std::make_unique<BoomerangThrow>(this, boomerang,player));
	AddState(BoomerangState::GET_READY, std::make_unique<BoomerangGetReady>(this, boomerang,player));

	//�������
	SetStartState(BoomerangState::IDEL);
	




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangStateMachine::~BoomerangStateMachine()
{
}

///// <summary>
///// �ʒm���ɌĂяo�����֐�
///// </summary>
///// <param name="type"></param>
///// <param name="datas"></param>
//void BoomerangStateMachine::Notify(MessageType type, void* datas)
//{
//	
//	switch (type)
//	{
//		case MessageType::BOOMERANG_IDEL_STATE:
//			ChangeState(BoomerangState::IDEL);
//			break;
//		case MessageType::BOOMERANG_GET_READY_STATE:
//			ChangeState(BoomerangState::GET_READY);
//			break;
//		case MessageType::BOOMERANG_THROW_STATE:
//			ChangeState(BoomerangState::THROW);
//			break;
//		default:
//			break;
//	}
//	
//}
