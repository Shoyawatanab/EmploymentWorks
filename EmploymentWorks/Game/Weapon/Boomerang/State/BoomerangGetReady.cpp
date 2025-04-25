#include "pch.h"
#include "BoomerangGetReady.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangGetReady::BoomerangGetReady()
	:
	m_commonResources{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="boomerang">�u�[������</param>
void BoomerangGetReady::AddPointer(Boomerang* boomerang)
{
	m_boomerang = boomerang;
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangGetReady::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangGetReady::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);



}

void BoomerangGetReady::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangGetReady::Enter()
{
	//���[�J����]�̐ݒ�
	m_boomerang->SetLocalRotation(Params::BOOMERANG_GETREADY_ROTATION);
	//���[�J�����W�̐ݒ�
	m_boomerang->SetLocalPosition(Params::BOOMERANG_GETREADY_POSITION);
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangGetReady::Exit()
{


}



