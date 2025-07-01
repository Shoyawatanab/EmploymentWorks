#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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
