#include "pch.h"
#include "BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyBullet::BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy)
	:
	Actor(scene)
	,m_birdEnemy{birdEnemy}
{

	using namespace DirectX::SimpleMath;

	//�R���|�[�l���g�̒ǉ�
	AddComponent<ModelComponent>(this, "BeamEnergyBall");

	//�����蔻��̍쐬
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, BOX_COLLIDER_SIZE
		, SPHERE_COLLIDER_SIZE);



	GetTransform()->SetScale(Vector3(0.3f,0.3f,0.3f));
	GetTransform()->SetPosition(Vector3(0,0,1));

	//�e�q�֌W������
	GetTransform()->SetParent(birdEnemy->GetTransform());

	m_stateMachine = std::make_unique<BirdEnemyBulletStateMachine>(this,birdEnemy);

}


/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBullet::~BirdEnemyBullet()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyBullet::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);
}

/// <summary>
/// �����������̊֐�
/// </summary>
/// <param name="collider"></param>
void BirdEnemyBullet::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_stateMachine->ChangeState(BirdEnemyBulletState::IDEL);
			break;
		default:
			break;
	}


}


