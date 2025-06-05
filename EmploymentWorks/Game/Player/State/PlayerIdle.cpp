#include "pch.h"
#include "PlayerIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player2.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Observer/Messenger.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerIdle::PlayerIdle(PlayerStateMachine* stateMachine, Player2* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
{


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerIdle::~PlayerIdle()
{
}




/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerIdle::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;



	////���{�^���������ꂽ��
	//if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	//{
	//	Messenger::GetInstance()->Notify<PlayerMessageType>(m_player->GetID(), PlayerMessageType::ATTACK);

	//}





}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerIdle::Enter()
{



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerIdle::Exit()
{
}



