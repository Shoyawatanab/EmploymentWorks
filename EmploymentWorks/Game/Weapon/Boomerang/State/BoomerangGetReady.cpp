#include "pch.h"
#include "BoomerangGetReady.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"


#include "Libraries/Microsoft/DebugDraw.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangGetReady::BoomerangGetReady(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_boomerang{boomerang}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
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



