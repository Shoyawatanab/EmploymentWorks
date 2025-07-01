#include "pch.h"
#include "BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyBullet::BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy)
	:
	Actor(scene)
	,m_birdEnemy{birdEnemy}
	,m_explosionSE{}
{

	using namespace DirectX::SimpleMath;

	//�R���|�[�l���g�̒ǉ�
	AddComponent<ModelComponent>(this, "BeamEnergyBall");

	//�����蔻��̍쐬
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, BOX_COLLIDER_SIZE
		, SPHERE_COLLIDER_SIZE);

	//�ۉe
	auto shadow = AddComponent<RoundShadowComponent>(this, 0.6f);
	//�������̍쐬
	m_explosionSE = AddComponent<SoundComponent>(this, "Explosion", SoundComponent::SoundType::SE);

	//�������
	GetTransform()->SetScale(Vector3(0.5f,0.5f,0.5f));
	GetTransform()->SetPosition(Vector3(0,0,3));

	//�e�q�֌W������
	GetTransform()->SetParent(birdEnemy->GetTransform());

	//�X�e�[�g�}�V�[���̍쐬
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
		case Actor::ObjectTag::PLAYER:
		case Actor::ObjectTag::STAGE:
		{
			//�����G�t�F�N�g�̒ʒm
			ExplosionEffectDatas datas;
			//�ǉ��f�[�^����f�[�^�̃Z�b�g
			datas.Position = GetTransform()->GetWorldPosition();
			datas.Scale = GetTransform()->GetWorldScale();
			SceneMessenger::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT,&datas);
			
			//SE�̍Đ�
			m_explosionSE->Play();
			//��Ԃ̕ω�
			m_stateMachine->ChangeState(BirdEnemyBulletState::IDEL);

		}
			break;
		default:
			break;
	}


}


