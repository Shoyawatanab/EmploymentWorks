#include "pch.h"
#include "Boomerangidle.h"
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
BoomerangIdle::BoomerangIdle(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{stateMahine}
	,m_boomerang{boomerang}
	,m_player{player}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangIdle::~BoomerangIdle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangIdle::Update(const float& deltaTime)
{



}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangIdle::Enter()
{
	//�e�̐ݒ�
	m_boomerang->GetTransform()->SetParent(m_player->GetTransform());
	//�e�p�����[�^�[�ݒ�
	m_boomerang->GetTransform()->SetPosition(Params::BOOMERANG_IDLE_POSITION);
	m_boomerang->GetTransform()->SetRotate(Params::BOOMERANG_IDLE_ROTATION);
	m_boomerang->GetTransform()->SetScale(Params::BOOMERANG_IDLE_SCALE);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangIdle::Exit()
{
}
