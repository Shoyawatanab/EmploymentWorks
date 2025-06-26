#include "pch.h"
#include "BirdEnemyMove.h"
#include <cmath>
#include <random>
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/MathUtil.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
BirdEnemyMove::BirdEnemyMove(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_birdEnemy{ birdEnemy }
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
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyMove::Update(const float& deltaTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_time = std::min(m_time, Params::BIRDENEMY_MOVE_TIME);

	float ratio = m_time / Params::BIRDENEMY_MOVE_TIME;

	ratio = std::min(ratio, 1.0f);

	DirectX::SimpleMath::Vector3 pos = Vector3::Lerp(m_startPosition, m_endPosition, ratio);

	auto transform = m_birdEnemy->GetTransform();

	transform->SetPosition(pos);

	//transform->Rotate(elapsedTime);


	m_time += deltaTime;

	if (ratio == 1.0f)
	{

		m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::IDEL);

	}

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyMove::Enter()
{

	//������
	m_startPosition = m_birdEnemy->GetTransform()->GetWorldPosition();
	m_time = 0;

	// �����_���Ȋp�x�𐶐�
	float angle = MathUtil::GetRandom(0.0f, DirectX::XM_2PI);

	//�ړ��ϐ�
	DirectX::SimpleMath::Vector3 offsetPosition;
	offsetPosition.x = Params::BIRDENEMY_MOVE_RADIUS * cos(angle);
	offsetPosition.y = Params::BIRDENEMY_MOVE_RADIUS * sin(angle);


	//�I���̍��W�����߂�
	m_endPosition = m_startPosition + offsetPosition;


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyMove::Exit()
{
}
