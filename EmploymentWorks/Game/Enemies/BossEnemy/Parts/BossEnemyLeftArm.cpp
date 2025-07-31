/*
	�N���X��     : BossEnemyLeftArm
	����         : �{�X�G�̍��r���f��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

BossEnemyLeftArm::BossEnemyLeftArm(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArm"
		, Params::BOSSENEMY_LEFTARM_HP
		, Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE
		,boss)
{


	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARM_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARM_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARM_ROTATION);

	//�ȉ��ǉ����ʂ̍쐬


	//�������̍쐬
	m_hitSE = AddComponent<SoundComponent>(this, "AttackHit", SoundComponent::SoundType::SE);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyLeftArm::~BossEnemyLeftArm()
{
}

/// <summary>
/// �ʂ̓����������̊֐�
/// </summary>
/// <param name="collider"></param>
void BossEnemyLeftArm::OnCollisionEnterActor(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:

			//SwingDown��ԂȂ�
			if (GetBossEnemy()->GetCurrentActionType() == BossEnemy::ActionType::SWINGDOWN)
			{

				DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

				position.y = 0.1f;
				//�p�[�e�B�N���쐬
				Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
				//�T�E���h�Đ�
				m_hitSE->Play();

			}
		
		
			break;
		default:
			break;
	}

}
