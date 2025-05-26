
#include "pch.h"
#include "BirdEnemyMove.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include "Game/Player/Player.h"
#include <cmath>
#include <random>

#include "Game/Params.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEnemyMove::BirdEnemyMove()
	:
	m_commonResources{},
	m_player{}
	,m_birdEnemy{}
	,m_startPosition{}
	,m_endPosition{}
	,m_time{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyMove::~BirdEnemyMove()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyMove::Initialize(CommonResources* resoure,BirdEnemy* owner)
{

	m_commonResources = resoure;

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//������
	m_startPosition = m_birdEnemy->GetPosition();
	m_time = 0;

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyMove::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_time = std::min(m_time,Params::BIRDENEMY_MOVE_TIME);

	float ratio = m_time / Params::BIRDENEMY_MOVE_TIME;

	DirectX::SimpleMath::Vector3 pos = Vector3::Lerp(m_startPosition, m_endPosition, ratio);

	m_birdEnemy->SetPosition(pos);

	m_birdEnemy->Rotate(elapsedTime);


	m_time += elapsedTime;

	if (ratio == 1.0f)
	{
		m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyldling());
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyMove::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyMove::Enter()
{
	//������
	m_startPosition = m_birdEnemy->GetPosition();
	m_time = 0;

	//�V�[�h�l�𐶐�
	std::random_device rd;
	std::mt19937 gen(rd());
	//���m���Ɏ����𐶐�
	std::uniform_real_distribution<float> angleDist(0.0f, DirectX::XM_2PI); // 0 ~ 2�΂̊p�x�𐶐�

	// �����_���Ȋp�x�𐶐�
	float angle = angleDist(gen);

	//�ړ��ϐ�
	DirectX::SimpleMath::Vector3 offsetPosition;
	offsetPosition.x = Params::BIRDENEMY_MOVE_RADIUS * cos(angle);
	offsetPosition.y = Params::BIRDENEMY_MOVE_RADIUS * sin(angle);


	//�I���̍��W�����߂�
	m_endPosition = m_startPosition  + offsetPosition;



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyMove::Exit()
{

}




