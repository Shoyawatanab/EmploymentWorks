#include "pch.h"
#include "Boomerang.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

Boomerang::Boomerang(Scene* scene,Player* player)
	:
	WeaponBase(scene)
{

	//当たり判定の作成
	auto aabbCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOOMERANG_BOX_COLLIDER_SIZE
		, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);
	//当たり判定を無効に
	aabbCollider->SetActive(false);

	//初期情報の適用
	GetTransform()->SetScale(Params::BOOMERANG_SCALE);
	GetTransform()->Translate(Params::Params::BOOMERANG_POSITION);
	GetTransform()->SetRotate(Params::Params::BOOMERANG_ROTATION);



	auto model = AddComponent<ModelComponent>(this, "Boomerang");

	m_stateMachine = std::make_unique<BoomerangStateMachine>(this, player);

}

Boomerang::~Boomerang()
{
}

void Boomerang::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);
}

void Boomerang::OnCollisionEnter(ColliderComponent* collider)
{
}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="state">次のステート</param>
void Boomerang::ActorChangeState(WeaponState nextState)
{

	switch (nextState)
	{
		case WeaponBase::WeaponState::BOOMERANG_IDLE:
			m_stateMachine->ChangeState(BoomerangState::IDEL);
			break;
		case WeaponBase::WeaponState::BOOMERANG_GET_READY:
			m_stateMachine->ChangeState(BoomerangState::GET_READY);
			break;
		case WeaponBase::WeaponState::BOOMERANG_THROW:
			m_stateMachine->ChangeState(BoomerangState::THROW);
			break;
		default:
			break;
	}

}
