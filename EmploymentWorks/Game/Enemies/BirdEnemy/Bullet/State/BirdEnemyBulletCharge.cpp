#include "pch.h"
#include "BirdEnemyBulletCharge.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
BirdEnemyBulletCharge::BirdEnemyBulletCharge(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_bullet{ bullet }
	,m_birdEnemy{birdEnemy}
	,m_time{}
{
}

BirdEnemyBulletCharge::~BirdEnemyBulletCharge()
{
}

void BirdEnemyBulletCharge::Update(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//��Ԃ̎��Ԃ̌v�Z
	float t = m_time / CHARGE_TIME;
	t = std::min(t, 1.0f);
	
	//�G�l���M�[�e�̑傫���̕��
	Vector3 scale = Vector3::Lerp(Vector3::Zero,Params::BIRDENEMY_BEAM_BALL_MAX_SIZE, t);
	//�傫����K�p
	m_bullet->GetTransform()->SetScale(scale);

	//�ő�̑傫���ɂȂ�����
	if (m_time >= CHARGE_TIME)
	{
		Messenger::GetInstance()->Notify(MessageType::BIRD_BULLET_SHOT_STATE);
		return;
	}


	m_time += deltaTime;
}

void BirdEnemyBulletCharge::Enter()
{
	using namespace DirectX::SimpleMath;

	m_time = 0.0f;

	//�傫�����[����
	m_bullet->GetTransform()->SetScale(Vector3::Zero);
	m_bullet->SetActive(true);
}

void BirdEnemyBulletCharge::Exit()
{
}
