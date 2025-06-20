#include "pch.h"
#include "BoomerangGetReady.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMahine">�X�e�[�g�}�V�[��</param>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
BoomerangGetReady::BoomerangGetReady(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	, m_player{ player }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangGetReady::Update(const float& deltaTime)
{



}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangGetReady::Enter()
{
	//���[�J����]�̐ݒ�
	m_boomerang->GetTransform()->SetRotate(Params::BOOMERANG_GETREADY_ROTATION);
	//���[�J�����W�̐ݒ�
	m_boomerang->GetTransform()->SetPosition(Params::BOOMERANG_GETREADY_POSITION);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangGetReady::Exit()
{
}
