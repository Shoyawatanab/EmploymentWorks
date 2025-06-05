#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Observer/Messenger.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BossEnemy::BossEnemy(Scene* scene)
	:
	Actor(scene)
{

	using namespace DirectX::SimpleMath;

	//Body�̍쐬
	auto body = GetScene()->AddActor<BossEnemyBottom>(GetScene());
	body->GetTransform()->SetParent(GetTransform());
	


	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(Vector3(0,5,0));
	GetTransform()->SetRotate(Quaternion::Identity);

	auto parts = GetTransform()->GetAllDescendants();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{

}

void BossEnemy::UpdateActor(const float& deltaTime)
{
}

void BossEnemy::OnCollisionEnter(ColliderComponent* collider)
{
}

void BossEnemy::OnCollisionStay(ColliderComponent* collider)
{
}

void BossEnemy::OnCollisionExit(ColliderComponent* collider)
{
}

//void BossEnemy::Notify(const Telegram<GamePlayMessageType>& telegram)
//{
//}
//
//void BossEnemy::Notify(const Telegram<EnemyMessageType>& telegram)
//{
//}













