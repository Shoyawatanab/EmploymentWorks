#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Observer/Messenger.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BossEnemy::BossEnemy(Scene* scene)
	:
	Actor(scene)
{

	using namespace DirectX::SimpleMath;

	//Bodyの作成
	auto body = GetScene()->AddActor<BossEnemyBottom>(GetScene());
	body->GetTransform()->SetParent(GetTransform());
	


	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(Vector3(0,5,0));
	GetTransform()->SetRotate(Quaternion::Identity);

	auto parts = GetTransform()->GetAllDescendants();


}

/// <summary>
/// デストラクタ
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













