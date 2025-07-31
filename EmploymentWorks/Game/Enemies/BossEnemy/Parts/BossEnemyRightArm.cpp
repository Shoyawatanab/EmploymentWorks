/*
	�N���X��     : BossEnemyRightArm
	����         : �{�X�G�̉E�r���f��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

BossEnemyRightArm::BossEnemyRightArm(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArm"
		, Params::BOSSENEMY_RIGHTARM_HP
		, Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE
		, boss)
{



	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARM_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARM_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARM_ROTATION);

	//�������̍쐬
	m_hitSE = AddComponent<SoundComponent>(this, "AttackHit", SoundComponent::SoundType::SE);


}

/// <summary>
///�@�f�X�g���N�^
/// </summary>
BossEnemyRightArm::~BossEnemyRightArm()
{
}


/// <summary>
/// �ʂ̓����������̊֐�
/// </summary>
/// <param name="collider"></param>
void BossEnemyRightArm::OnCollisionEnterActor(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			//SwingDown��Ԃ̎�
			if (GetBossEnemy()->GetCurrentActionType() == BossEnemy::ActionType::SWINGDOWN)
			{
				
				DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

				position.y = 0.1f;
				//�p�[�e�B�N���̒ʒm
				Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
				m_hitSE->Play();
			}
		break;
		default:
			break;
	}

}



