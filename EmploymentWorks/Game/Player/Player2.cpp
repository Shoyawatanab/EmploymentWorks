#include "pch.h"
#include "Player2.h"
#include "GameBase/Managers.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Params.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Player/Animation/PlayerAnimationController.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
Player2::Player2(Scene* scene)
	:
	Actor(scene)
	,m_playSceneCamera{}
	,m_rigidBody{}
{

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//当たり判定の作成
	auto aABBCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
	, Params::PLAYER_BOX_COLLIDER_SIZE
	, Params::PLAYER_SPHERE_COLLIDER_SIZE);
	//初期情報の適用
	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	//モデルの作成
	m_model =  GetScene()->AddActor<PlayerModel>(GetScene());
	m_model->GetTransform()->SetParent(GetTransform());
	//ステートの作成
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);

	//アニメーションコンポーネントの追加
	m_animation  = AddComponent<AnimatorComponent>(this, std::make_unique<PlayerAnimationController>(this));
	
	m_animation->SetTrigger("GetReady");
}

/// <summary>
/// デストラクタ
/// </summary>
Player2::~Player2()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Player2::UpdateActor(const float& deltaTime)
{

	m_stateMachine->Update(deltaTime);

	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();


	if (tracker->leftButton ==DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
	}
	m_animation->SetFloat("Move", 1.0f);


}

void Player2::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
		{
			int a = 1;
		}
			break;
		default:
			break;
	}

}

void Player2::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			//重力のリセット
			m_rigidBody->ResetGravity();
		break;
		default:
			break;
	}
}
