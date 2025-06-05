#include "pch.h"
#include "BoomerangIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"
#include "Game/InstanceRegistry.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangIdle::BoomerangIdle(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_boomerang{boomerang}
	,m_player{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangIdle::~BoomerangIdle()
{
}



/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangIdle::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangIdle::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);


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
	Messenger::GetInstance()->Notify(GamePlayMessageType::GET_BOOMERANG, nullptr);

	
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangIdle::Exit()
{
}



