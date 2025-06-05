
#include "pch.h"
#include "BirdEnemyBeamIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/InstanceRegistry.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="birdEnemy">���̓G</param>
/// <param name="beam">�r�[��</param>
BirdEnemyBeamIdling::BirdEnemyBeamIdling(BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_player{}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamIdling::~BirdEnemyBeamIdling()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyBeamIdling::Initialize()
{

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBeamIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�r�[���̍��W��o�^
 	m_beam->SetPosition( m_birdEnemy->GetPosition());


}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBeamIdling::Enter()
{

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBeamIdling::Exit()
{

}



