#include "pch.h"
#include "BoomerangIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangIdle::BoomerangIdle()
	:
	m_commonResources{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangIdle::~BoomerangIdle()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="boomerang">�u�[������</param>
void BoomerangIdle::AddPointer(Player* player, Boomerang* boomerang)
{
	m_boomerang = boomerang;
	m_player = player;
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangIdle::Initialize(CommonResources* resources)
{
	m_commonResources = resources;




}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangIdle::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);


}

void BoomerangIdle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangIdle::Enter()
{
	//�e��o�^
	m_boomerang->SetParent(m_player);
	//���[�J����]�̐ݒ�
	m_boomerang->SetLocalRotation(Params::BOOMERANG_IDLE_ROTATION);
	//���[�J�����W�̐ݒ�
	m_boomerang->SetLocalPosition(Params::BOOMERANG_IDLE_POSITION);
	//���[�J���T�C�Y�̐ݒ�
	m_boomerang->SetLocalScale(Vector3(10,10,10));
	//�ʒm������
	Messenger::GetInstance()->Notify(MessageType::GetBoomerang, nullptr);

	
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangIdle::Exit()
{
}



