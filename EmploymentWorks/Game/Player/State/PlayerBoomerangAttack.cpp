#include "pch.h"
#include "PlayerBoomerangAttack.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerBoomerangAttack::PlayerBoomerangAttack(PlayerStateMachine* stateMachine, Player* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
	,m_throwState{}
	,m_throwQuantityState{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBoomerangAttack::~PlayerBoomerangAttack()
{
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerBoomerangAttack::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	using namespace DirectX;


	
}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerBoomerangAttack::Enter()
{
	//�v���C���̏�Ԃ�ʏ��
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_IDLE_STATE);

}


/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerBoomerangAttack::Exit()
{


}





