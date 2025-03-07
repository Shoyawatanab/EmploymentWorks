
#include "pch.h"
#include "BirdEnemyBeamIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyBeamIdling::BirdEnemyBeamIdling(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_commonResources{},
	m_player{player}
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
void BirdEnemyBeamIdling::Initialize(CommonResources* resoure)
{
	m_commonResources = resoure;

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
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyBeamIdling::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
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



