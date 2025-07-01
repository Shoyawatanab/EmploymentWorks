#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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

	//�ȉ��ǉ����ʂ̍쐬


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
		{

			DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

			position.y = 0.1f;

			SceneMessenger::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
		}
		break;
		default:
			break;
	}

}



